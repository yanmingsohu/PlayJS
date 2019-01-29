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
	js := vm.CreateVm();
	code := "1+1"
	ret, err := js.Eval(code)
	if err != nil {
		fmt.Println("Error", err)
	} else {
		fmt.Println(ret.Int(), ret.Double(), ret.Bool())
	}

	ret, err = js.Eval(" '[1fdsafsdfsadf'+'000]' ")
	fmt.Println(ret.Int(), ret.String(), "<<<")
}