export default {}

try {
  let so = audio.createSoloud();
  let wav = audio.createWavSource();
  let file = "./deps/libnyquist/test_data/2ch/44100/24/test.wav";
  audio.load(wav, file);
  audio.playWav(so, wav);
  let time = audio.getLength(wav);
  console.log('Play', file, 'length', time, 'ms');
  thread.wait(time * 1e3);
} catch(e) {
  console.error('Audio Test Failed ('+ e.code +'),', e.stack);
  throw e;
}