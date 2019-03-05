import Node from './node.js'

const Yaml = Node.load('boot/js-yaml.js');
const config = Yaml.load(fs.read_txt('playjs.yaml'));
const main = config['main-script'];

global.screen = config.screen;
global.game = config.game || {};


vm.loadModule(main);


//
// ! 未安装到模块, 新线程, 新模块都需要安装
//
function install_console() {
  [
    'debug', 'info', 'log', 'warn', 'error', 'fatal', 'line'
  ].forEach(function(n) {
    console[n] = _wrap_cos(console[n]);
  });
    
  function _wrap_cos(sfn) {
    return function() {
      let out = [];
      for (let i=0, len=arguments.length; i<len; ++i) {
        out.push(JSON.stringify(arguments[i]));
      }
      sfn.apply(console, out);
    }
  }
}