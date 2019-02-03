//
// PlayJS
//-------------------------------------
//    benchmark_count / use time (ms)
//    10000             12              
//    1000              1               
//
var benchmark_count = 1000;


events.on('error', function(e) {
  console.log('PEER Got error:', e.stack || e);
});


events.on('ms', function(d) {
  console.log('from main:', d);
});


var onlyone = 0;
events.on('ones', onlyOne);
events.on('ones', onlyOne);

events.emit("ps", 'peer start');


function onlyOne() {
  console.log("this message only one print.", ++onlyone);
  if (onlyone>1) throw new Error("not one call.");
  startBench();
}


function startBench() {
  var show = parseInt(benchmark_count/10);
  var i = 0;

  events.on("benchmark", ben);
  
  function ben(c) {
    ++i;
    if (i%show == 0) {
      console.log('benchmark count', i, c);
    }
    if (i >= benchmark_count) {
      events.emit("benchmark-end", i);
      events.off('benchmark', ben);

      thread.sleep(1000);
      startBench();
    }
  }

  events.emit("benchmark-start", benchmark_count);
}


do {
  events.dispatchMessage();
} while (events.getMessage());