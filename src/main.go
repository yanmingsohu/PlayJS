package main

//
// 包名可以和路径不一致, 路径仅引导编译器加载源文件, 
// 程序中使用包中 package 声明的包名称作为前缀引用包中的 api.
//
import (
	"./src"
	"fmt"
)

func main() {
	vm := js.CreateVm()
	js.InstallConsole(vm)

	b := "console.log('hello')"
	// b := "a={ccc:1};bb=1000;JSON.stringify(this, 0, 2)"
	ret, err := vm.Eval(b)
	fmt.Println(ret, err)

	if vm.HasException() {
		ex := vm.LastException()
		fmt.Println("Exception", ex.ToString(), ex.Stack())
	}

	fmt.Println("<<<<<<<<<<<<<<<<<<<<< GAME OVER >>>>>>>>>>>>>>>>>>>>")
}