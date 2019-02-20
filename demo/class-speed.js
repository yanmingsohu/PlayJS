export default {}

//
// class 定义的类要快于闭包定义, 10 倍左右
// 缺少私有域, 每次需要用 this 引用自身属性.
//
class A {
  a() {console.log('aa')}
  b() {console.log('ab')}
  c() {console.log('ac')}
  d() {console.log('ad')}
}


//
// 每次都创建并绑定属性, 效率低, 闭包灵活
//
function B() {
  return {
    a, b, c, d
  };
  function a() {
    console.log('ba')
  }
  function b() {
    console.log('bb')
  }
  function c() {
    console.log('bc')
  }
  function d() {
    console.log('bd')
  }
}

//
// 这样定义完全不可取, 效率低下, 比 B() 方法慢 10 倍
//
function C() {
  var pri = {};

  class _C {
    a() {console.log('ca')}
    b() {console.log('cb')}
    c() {console.log('cc')}
    d() {console.log('cd')}
  }

  return new _C();
}

const c = 100000;

function testA() {
  var arr = []; arr.length = c;
  for (var i=0; i<c; ++i) {
    arr.push(new A());
  }
}

function testB() {
  var arr = []; arr.length = c;
  for (var i=0; i<c; ++i) {
    arr.push(B());
  }
}


function testC() {
  var arr = []; arr.length = c;
  for (var i=0; i<c; ++i) {
    arr.push(C());
  }
}


for (var i=0; i<10; ++i) {
  console.log('\n', i);

  let start = Date.now();
  testA();
  console.log('A used', Date.now() - start, 'ms');

  start = Date.now();
  testB();
  console.log('B used', Date.now() - start, 'ms');

  start = Date.now();
  testC();
  console.log('C used', Date.now() - start, 'ms');
}