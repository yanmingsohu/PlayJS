export default {}


events.on('error', function(e) {
  console.log('Main error:', e.stack || e);
});


events.on('ps', function(d) {
  console.log('from peer:', d);
  events.emit("ones", 1000);
  events.emit("ms", 'main-send');
});


events.on("ms", function(d) {
  console.log("myself:", d);
});


events.on('benchmark-start', function(count) {
  var start = Date.now();
  
  events.on('benchmark-end', bend);
  
  function bend() {
    events.off('benchmark-end', bend);
    var use = Date.now() - start;
    console.log("Benchmark", count, "events, use", 
      use, 'ms', (1000/use).toFixed(1), 'frame/s');
  }

  for (var i=0; i<count; ++i) {
    events.emit('benchmark', i);
  }
});


thread.run('./demo/event-peer.js');


do {
  events.dispatchMessage();
} while (events.getMessage());