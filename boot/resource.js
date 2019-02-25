//
// 资源加载器, 从配置文件中加载各种资源
// 角色/精灵/场景/摄像机/灯光, 资源往往是多个文件的集合.
// 资源在必要时会被缓存
//
import Node  from './node.js'
import Game  from './game.js'
import Model from './model.js'
import Draw  from './draw.js'
import Anim  from './anim.js'

// const Matrix = Node.load('boot/gl-matrix.js');
const Yaml = Node.load('boot/js-yaml.js');


export default {
  context,
  createCache,
  createLimitCache,
  localBuffer,
};


//
// 一个上下文保护所有加载的资源缓存, 当切换场景时
// 可以调用 free 或直接扔掉上下文.
//
// program  - 编译好的着色器程序
// _animlib - 动画库, 默认 boot/anim.js
//
function context(program, _animlib) {  
  const cache = {
    drawable : createCache(_basic_draw_creator),
  };

  const TYPE_FUNC = {
    camera,
    sprite,
  };

  const animlib = _animlib || Anim;

  return {
    load,
    free,
  };


  function camera(cfg) {
  }


  //
  // 模型和骨骼会在缓存中保存, 精灵是独立的对象
  //
  function sprite(cfg) {
    let dobj = cache.drawable.get(cfg._basepath + cfg.model, cfg);
    let colorCoe, sizeCoe;
    
    if (cfg.colorCoefficient) {
      colorCoe = program.getUniform('colorCoefficient');
    }
    if (cfg.sizeCoefficient) {
      sizeCoe = program.getUniform('sizeCoefficient');
    }

    let anim = Game.createAnimation(dobj);
    for (let i=cfg.pose.length-1; i>=0; --i) {
      let pose = cfg.pose[i];
      if (pose.func) {
        anim.addPose(pose.name, animlib[pose.func]);
      } else {
        throw new Error("unsupport pose: "+ JSON.stringify(pose));
      }
    }
    if (cfg.pose[0]) {
      anim.pose(cfg.pose[0].name);
    }

    let sp = Game.createSprite(dobj, {
      draw : function (used, time) {
        anim.draw(used, time);
        colorCoe && colorCoe.setUniform1f(cfg.colorCoefficient);
        sizeCoe  && sizeCoe.setUniform1f(cfg.sizeCoefficient);
      },
    });

    // 扩展属性
    sp.animation = anim;
    return sp;
  }


  function _basic_draw_creator(key, cfg) {
    let mod = Model.load(cfg._basepath + cfg.model);
    let dobj = Draw.createBasicDrawObject(program);
    dobj.setModelData(mod);
    let sk = Game.readSkeleton(cfg._basepath + cfg.skeleton, mod.vertexCount);
    dobj.setSkeleton(sk);
    return dobj;
  }

  
  //
  // 释放内存, 使上下文不可用.
  //
  function free() {
    __free(cache);
  }


  //
  // 文件支持 JSON/YAML, 从配置文件中解析并加载资源,
  // 必要时会使用缓存
  //
  function load(filename) {
    if (filename.endsWith('.json')) {
      let cfg = JSON.parse(fs.read_txt(filename));
      return parseConfig(cfg, filename);
    }
    else if (filename.endsWith('.yaml')) {
      let cfg = Yaml.load(fs.read_txt(filename));
      return parseConfig(cfg, filename);
    }
    throw new Error("Usupport file type: "+ filename);
  }


  function parseConfig(cfg, filename) {
    if (!cfg.type) {
      throw new Error("Config not found 'type' attribute");
    }
    let func = TYPE_FUNC[ cfg.type ];
    if (!func) {
      throw new Error("Unsupport type: "+ cfg.type);
    }
    try {
      let paths = filename.split("/");
      paths[paths.length-1] = '';
      cfg._basepath = paths.join('/');
      cfg._source = filename;

      return func(cfg);
    } catch(e) {
      throw new Error("Load resource: "+ e.stack);
    }
  }
}


//
// 对象缓冲区, 仅在不存在的时候才调用 creator 来创建新的对象
//
function createCache(creator) {
  const pool = {};
  return {
    get,
    free,
  };

  function get(key, data) {
    let obj = pool[key];
    if (obj) {
      return obj;
    }
    obj = creator(key, data);
    pool[key] = obj;
    return obj;
  }

  //
  // 释放所有对象, 并调用对象的 free()
  //
  function free() {
    __free(pool);
  }
}


//
// 创建一个带有数量上限的对象缓存区, 当缓存达到上限
// 之前的对象会被调用 deleter 被释放.
//
// creator : Function(id, _create_data)
// deleter : Function(id, data)
//
function createLimitCache(creator, deleter, _limit) {
  if (!creator) throw new Error("creator is null");
  if (!deleter) throw new Error("deleter is null");
  const limit = _limit >= 0 ? _limit : 10;
  const cache = [];
  let cptr = 0;

  return {
    get,
    free,
  };

  function _find(id) {
    for (let i=0; i<limit; ++i) {
      if (cache[i] && cache[i].id == id) {
        // console.log("get room from cache", id);
        return cache[i];
      }
    }
  }

  //
  // 尝试获得一个对象, id 是对象识别字符串,
  //  _create_data 用于创建对象的扩展数据可以空.
  //
  function get(id, _create_data) {
    let c = _find(id);
    if (c) return c.p;

    let p = creator(id, _create_data);
    if (!p) return;
    
    if (cache[cptr]) {
      _delete(cptr);
    }

    cache[cptr] = { p, id };
    if (++cptr >= limit) cptr = 0;
    return p;
  }

  function _delete(i) {
    deleter(cache[i].id, cache[i].p);
    cache[i] = null;
  }

  function free() {
    for (let i=0; i<limit; ++i) {
      _delete(i);
    }
  }
}


//
// 创建一个共用缓冲区对象, 该对象始终返回唯一创建的缓冲区, 尽可能复用内存, 
// 适合缓冲区仅在一个函数中分配, 函数结束缓冲区不再使用的情况.
// 缓冲区无需释放.
//
function localBuffer() {
  let swap_buf;

  return {
    // 分配一个 Float32 内存, len 单位是 Float32
    float32(len) {
      return new Float32Array(_get(len << 2), 0, len);
    },

    // 分配 ArrayBuffer 内存, len 单位是 byte
    array(len) {
      return _get(len);
    },
  };

  function _get(bytelen) {
    if (!swap_buf || swap_buf.byteLength < bytelen) {
      swap_buf = new ArrayBuffer(bytelen);
    }
    return swap_buf;
  }
}


function __free(object_pool) {
  for (let n in object_pool) {
    let obj = object_pool[n];
    if (obj && obj.free) {
      obj.free();
    }
    delete object_pool[n];
  }
}