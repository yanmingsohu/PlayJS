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


function __free(object_pool) {
  for (let n in object_pool) {
    let obj = object_pool[n];
    if (obj && obj.free) {
      obj.free();
    }
    delete object_pool[n];
  }
}