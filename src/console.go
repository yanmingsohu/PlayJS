package js

type Console struct {
	vm *VM
}


func InstallConsole(vm *VM) {
	console := vm.NewObject()
	g := vm.Global()
	g.Put("console", console)

	logFunc := &Console{ vm:vm }
	console.Put("log", vm.Function(logFunc))
}


func (c *Console) Call(callee *JsRef, iscc bool, av *JsRef, ac int) (*JsRef) {
	return &c.vm.Null
}
