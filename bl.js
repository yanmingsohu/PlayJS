//
// 暴力破解公式
//
// <Buffer 63 6c 34 fc 4f 44 05 06 b9 bf b7 ba d2 c0 ac c6 22 d0 cf d2 ba 26 94 de e1 e4>
// 输入值
// 00 00 00 00 4f 44 05 06 00 00 00 ba 00 00 00 00 00 00 00 d2 00 00 00 00 e1 e4
//var x = [99, 108, 52, 252, 79, 68, 5, 6, 185, 191, 183, 186, 210, 192, 172, 198, 34, 208, 207, 210, 186, 38, 148, 222, 225, 228];
var x = [99, 108, 52, 252, /*79, 68, 5, 6,*/ 185, 191, 183, /*186,*/ 210, 192, 172, 198, 34, 208, 207, /*210,*/ 186, 38, 148, 222, /*225, 228*/];
const xl = x.length;
// 输出值
var y = 0x4ffe75;
// 公式中的符号表
var op = [  
  function(a, b) { return a; /*N*/ },
  function(a, b) { return a+b; /*+*/ },
  //function(a, b) { return a-b; /*-*/ },
  function(a, b) { return a*b; /***/ },
  //function(a, b) { return a/b; /*/*/ },
  function(a, b) { return a|b; /*|*/ },
  function(a, b) { return a&b; /*&*/ },
  //function(a, b) { return a^b; /*^*/ },
];
const opmax = op.length;
const begin = Date.now();
const timeutil = [1e3, 1e3*60, 1e3*60*60];
const f = [];
var fl;


const cluster = require('cluster');

process.on('exit', (code) => {
  console.log(f.join(', '));
});

if (cluster.isMaster) {
  const print_gap = 5e3;
  var total_count = 0;
  var total_use = 0;
  var print_next = Date.now() + print_gap;
  var reports = [];
  
  for (var i=0; i<op.length; ++i) {
    var work = cluster.fork();
    work.send({ start: i, msg:'启动进程' });
    work.on('message', fromWork);
  }

  function fromWork(msg) {
    if (msg.end) {
      process.exit();
    } else if (msg.report) {
      total_count += msg.count;
      total_use += msg.use;
      reports[msg.wid] = msg.report;
      
      if (Date.now() > print_next) {
        console.log('\n总耗时', timeu(total_use), '总次数', countu(total_count), '\n', reports);
        print_next = Date.now() + print_gap;
      }
    }
  }
  
  cluster.on('exit', (worker, code, signal) => {
    console.log(`工作进程 ${worker.process.pid} 已退出`);
  });
} else {
  process.on('message', function(msg) {
    console.log(msg);
    init(msg.start);
    fl = f.length;
    go(cluster.worker.id);
  });
}


function init(cluster_begin) {
  for (var i=0; i<xl; ++i) {
    f.push(x[i], 0);
  }
  f[16*2+1] = cluster_begin;
  return f;
}


function go(cid) {
  var count = 0;
  var now = Date.now();
  
  for (;;) {
    if (value() == y) {
      return ending(true, count);
    }
  
    for (var b=1; b<fl; b+=2) {
      f[b] += 1;
      if (f[b] < opmax) {
        break;
      } else if (b == fl-1) {
        return ending(false, count);
      } else {
        f[b] = 0;
      }
    }
  
    if (++count > 1000001) {
      cluster.worker.send({ report: print(), count: count, wid: cid, use: Date.now()-now });
      now = Date.now();
      count = 0;
      //console.log('集群', cid, '耗时', timeu(Date.now()-begin), '次数', countu(count), print());
    }
  }
}


function ending(find, c) {
  console.log(find ? '找到': '未找到', '循环了', countu(c), '次, 耗时', timeu(Date.now()-begin));
  console.log(print());
  cluster.worker.send({ end:true });
}


function value() {
  var s = f[0];
  for (var i=1; i<xl; i+=2) {
    s = op[ f[i] ](s, f[i+1]);
  }
  return s;
}


function print() {
  var ret = [];
  for (var i=0; i<f.length; i+=2) {
    var o = op[f[i+1]].toString();
    var _b = o.indexOf('/*');
    var _e = o.indexOf('*/', _b);
    if (_e > _b) {
      o = o.substring(_b+2, _e);
    }
    ret.push(f[i], o);
  }
  return ret.join(' ');
}


function timeu(t) {
  if (t < timeutil[0]) {
    return (t).toFixed(0) +'毫秒';
  }
  if (t < timeutil[1]) {
    return (t/timeutil[0]).toFixed(0) +'秒';
  }
  if (t < timeutil[2]) {
    return (t/timeutil[1]).toFixed(0) +'分钟';
  }
  return (t/timeutil[2]).toFixed(1) +'小时';
}


function countu(t) {
  if (t < 1000000) return t;
  if (t < 10000000) return (t/1000000).toFixed(2)+'百万';
  if (t < 100000000) return (t/10000000).toFixed(2)+'千万';
  return (t/100000000).toFixed(3)+'亿';
}