import Node from './node.js'

const Yaml = Node.load('boot/js-yaml.js');
const config = Yaml.load(fs.read_txt('playjs.yaml'));
const main = config['main-script'];

global.screen = config.screen;
global.game = config.game || {};

vm.loadModule(main);