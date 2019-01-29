package vm

//#include '../deps/ChakraCore/Build/VcBuild/bin/x64_release'
import (
	"syscall"
	"errors"
	// "strconv"
	"unsafe"
	"fmt"
)


const (
		JsRuntimeAttributeNone = uintptr(0x00000000)
		JsRuntimeAttributeDisableBackgroundWork = uintptr(0x00000001)
		JsRuntimeAttributeAllowScriptInterrupt = uintptr(0x00000002)
		JsRuntimeAttributeEnableIdleProcessing = uintptr(0x00000004)
		JsRuntimeAttributeDisableNativeCodeGeneration = uintptr(0x00000008)
		JsRuntimeAttributeDisableEval = uintptr(0x00000010)
		JsRuntimeAttributeEnableExperimentalFeatures = uintptr(0x00000020)
		JsRuntimeAttributeDispatchSetExceptionsToDebugger = uintptr(0x00000040)
		JsRuntimeAttributeDisableFatalOnOOM = uintptr(0x00000080)
		JsRuntimeAttributeDisableExecutablePageAllocation = uintptr(0x00000100)
)
type JsRuntimeAttribute int
const NULL = uintptr(0)


type JsRef struct {
  p uintptr
  vm *VM
}


type VM struct {
	js 									        	*syscall.DLL
	context                       JsRef
	runtime                       JsRef
	iJsCreateObject 		        	*syscall.Proc
	iJsCreateFunction 	        	*syscall.Proc
	iJsCreatePropertyId         	*syscall.Proc
	iJsSetProperty 			        	*syscall.Proc
	iJsGetGlobalObject 	        	*syscall.Proc
	iJsRunScript				        	*syscall.Proc
	iJsCallFunction               *syscall.Proc
	iJsGetUndefinedValue          *syscall.Proc
	iJsGetExternalData            *syscall.Proc
	iJsSerialize                 	*syscall.Proc
	iJsAddRef						        	*syscall.Proc
	iJsRunSerialized		        	*syscall.Proc
	iJsSerializeScript            *syscall.Proc
	iJsCreateContext              *syscall.Proc
	iJsCreateRuntime              *syscall.Proc
  iJsSetCurrentContext          *syscall.Proc
  iJsNumberToInt                *syscall.Proc
  iJsNumberToDouble             *syscall.Proc
  iJsCreateExternalArrayBuffer  *syscall.Proc
  iJsBooleanToBool              *syscall.Proc
  iJsCopyString                 *syscall.Proc
  iJsGetStringLength            *syscall.Proc
}


func CreateVm() (*VM) {
	js := syscall.MustLoadDLL("ChakraCore.dll")
	vm := &VM {js:js}
	vm.iJsCreateObject 							= js.MustFindProc("JsCreateObject")
	vm.iJsCreateFunction 						= js.MustFindProc("JsCreateFunction")
	vm.iJsCreatePropertyId 					= js.MustFindProc("JsCreatePropertyId")
	vm.iJsSetProperty 							= js.MustFindProc("JsSetProperty")
	vm.iJsGetGlobalObject 					= js.MustFindProc("JsGetGlobalObject")
	vm.iJsGetUndefinedValue 				= js.MustFindProc("JsGetUndefinedValue")
	vm.iJsGetExternalData   				= js.MustFindProc("JsGetExternalData")
	vm.iJsRunScript        				  = js.MustFindProc("JsRunScript")
	vm.iJsRunSerialized   					= js.MustFindProc("JsRunSerialized")
	vm.iJsCallFunction      				= js.MustFindProc("JsCallFunction")
	vm.iJsSerialize									= js.MustFindProc("JsSerialize")
	vm.iJsSerializeScript   				= js.MustFindProc("JsSerializeScript")
	vm.iJsAddRef										= js.MustFindProc("JsAddRef")
	vm.iJsCreateContext     				= js.MustFindProc("JsCreateContext")
	vm.iJsCreateRuntime   					= js.MustFindProc("JsCreateRuntime")
	vm.iJsSetCurrentContext 				= js.MustFindProc("JsSetCurrentContext")
  vm.iJsNumberToInt       				= js.MustFindProc("JsNumberToInt")
  vm.iJsNumberToDouble            = js.MustFindProc("JsNumberToDouble")
  vm.iJsCreateExternalArrayBuffer = js.MustFindProc("JsCreateExternalArrayBuffer")
  vm.iJsBooleanToBool             = js.MustFindProc("JsBooleanToBool")
  vm.iJsCopyString                = js.MustFindProc("JsCopyString")
  vm.iJsGetStringLength           = js.MustFindProc("JsGetStringLength")
	initVM(vm)
	return vm
}


func initVM(vm *VM) {
	err := jsErr( vm.iJsCreateRuntime.Call(
      JsRuntimeAttributeNone, NULL, vm.runtime.PointAddr()) );
	if err != nil {
		panic(err)
	}
	err = jsErr( vm.iJsCreateContext.Call(
      vm.runtime.Addr(), vm.context.PointAddr()) )
	if err != nil {
		panic(err)
	}
	err = jsErr( vm.iJsSetCurrentContext.Call(vm.context.Addr()) )
	if err != nil {
		panic(err)
	}
}


func (v *VM) JsCreateObject() (*JsRef, error) {
	ref := &JsRef{vm:v}
	code, _, err := v.iJsCreateObject.Call(ref.p)
	if err != nil {
		return nil, err
	}
	if code != 0 {
		return nil, errors.New(JsErrorStr(int(code)))
	}
	return ref, nil
}


func (v *VM) Eval(jscode string) (*JsRef, error) {
	ret := JsRef{vm:v}
	url := "eval()"
	err := jsErr( v.iJsRunScript.Call(
      strPtr(jscode), v.context.Addr(), strPtr(url), ret.PointAddr()) )
	if err != nil {
		return nil, err
	}
	return &ret, nil
}


//
// 返回被包装的整数, 如果数据不是整数返回 0
//
func (r *JsRef) Int() int {
  var i int = 0
  err := jsErr( r.vm.iJsNumberToInt.Call(r.Addr(), uintptr(unsafe.Pointer(&i))) )
  if err != nil {
    return 0
  }
  return i
}


//
// 返回被包装的浮点数, 如果数据不是数字返回 0
//
func (r *JsRef) Double() float64 {
  var f float64 = 0
  err := jsErr( r.vm.iJsNumberToDouble.Call(r.Addr(), uintptr(unsafe.Pointer(&f))) )
  if err != nil {
    return 0
  }
  return f
}


//
// 返回被包装的布尔值, 如果数据不是数字返回 false
//
func (r *JsRef) Bool() bool {
  var v bool = false
  r.vm.iJsBooleanToBool.Call(r.Addr(), uintptr(unsafe.Pointer(&v)))
  return v
}


//
// 返回被包装的字符串, 如果数据不是数字返回空字符串
//
func (r *JsRef) String() string {
  var v string = ""
  var l int32 = -1

  err := jsErr( r.vm.iJsGetStringLength.Call(r.Addr(), uintptr(unsafe.Pointer(&l))) )
  if err != nil {
    fmt.Println(err)
  }

  if l > 0 {
    buf := make([]byte, l)
    err := jsErr( r.vm.iJsCopyString.Call(
                  r.Addr(), uintptr(unsafe.Pointer(&buf[0])), uintptr(l), NULL) )
    if err == nil {
      v = string(buf)
    }
  }
  return v
}


//
// 返回指针的值
//
func (r *JsRef) Addr() uintptr {
	return r.p
}


//
// 返回指向指针的地址值
//
func (r *JsRef) PointAddr() uintptr {
	return uintptr(unsafe.Pointer(&r.p))
}


func jsErr(r1, r2 uintptr, err error) (error) {
	if r1 != 0 {
		str := JsErrorStr(int(r1))
		if str == "" {
			return err
		}
		return errors.New(str)
	}
	return nil
}


func intPtr(n int) uintptr {
	return uintptr(n)
}


func strPtr(s string) uintptr {
  p, _ := syscall.UTF16PtrFromString(s)
	return uintptr(unsafe.Pointer(p))
}


func JsErrorStr(code int) (string) {
	switch (code) {
	case 0x10000:
		return "Category of errors that relates to incorrect usage of the API itself."
	case 0x10000+1:
		return "An argument to a hosting API was invalid."
	case 0x10000+2:
		return "An argument to a hosting API was null in a context where null is not allowed."
	case 0x10000+3:
		return "The hosting API requires that a context be current, but there is no current context."
	case 0x10000+4:
		return "The engine is in an exception state and no APIs can be called until the exception is cleared."
	case 0x10000+5:
		return "A hosting API is not yet implemented."
	case 0x10000+6:
		return "A hosting API was called on the wrong thread."
	case 0x10000+7:
		return "A runtime that is still in use cannot be disposed."
	case 0x10000+8:
		return "A bad serialized script was used, or the serialized script was serialized by a "+
		"different version of the Chakra engine."
	case 0x10000+9:
		return "The runtime is in a disabled state."
	case 0x10000+10:
		return "Runtime does not support reliable script interruption."
	case 0x10000+11:
		return "A heap enumeration is currently underway in the script context."
	case 0x10000+12:
		return "A hosting API that operates on object values was called with a non-object value."
	case 0x10000+13:
		return "A script context is in the middle of a profile callback."
	case 0x10000+14:
		return "A thread service callback is currently underway."
	case 0x10000+15:
		return "Scripts cannot be serialized in debug contexts."
	case 0x10000+16:
		return "The context cannot be put into a debug state because it is already in a debug state."
	case 0x10000+17:
		return "The context cannot start profiling because it is already profiling."
	case 0x10000+18:
		return "Idle notification given when the host did not enable idle processing."
	case 0x10000+19:
		return "The context did not accept the enqueue callback."
	case 0x10000+20:
		return "Failed to start projection."
	case 0x10000+21:
		return "The operation is not supported in an object before collect callback."
	case 0x10000+22:
		return "Object cannot be unwrapped to IInspectable pointer."
	case 0x10000+23:
		return "A hosting API that operates on symbol property ids but was called with a non-symbol property id."+
		       "The error code is returned by JsGetSymbolFromPropertyId if the function is called with non-symbol property id."
	case 0x10000+24:
		return "A hosting API that operates on string property ids but was called with a non-string property id."+
		       "The error code is returned by existing JsGetPropertyNamefromId if the function is called with non-string property id."
	case 0x10000+25:
		return "Module evaluation is called in wrong context."
	case 0x10000+26:
		return "The Module HostInfoKind provided was invalid."
	case 0x10000+27:
		return "Module was parsed already when JsParseModuleSource is called."
	case 0x10000+28:
		return "Argument passed to JsCreateWeakReference is a primitive that is not managed by the GC."+
					 "No weak reference is required, the value will never be collected."
	case 0x10000+29:
		return "The Promise object is still in the pending state."
	case 0x10000+30:
		return "Module was not yet evaluated when JsGetModuleNamespace was called."

	case 0x20000:
		return "Category of errors that relates to errors occurring within the engine itself."
	case 0x20000+1:
		return "The Chakra engine has run out of memory."
	case 0x20000+2:
		return "The Chakra engine failed to set the Floating Point Unit state."

	case 0x30000:
		return "Category of errors that relates to errors in a script."
	case 0x30000+1:
		return "A JavaScript exception occurred while running a script."
	case 0x30000+2:
		return "JavaScript failed to compile."
	case 0x30000+3:
		return "A script was terminated due to a request to suspend a runtime."
	case 0x30000+4:
		return "A script was terminated because it tried to use eval or function and eval was disabled."

	case 0x40000:
		return "Category of errors that are fatal and signify failure of the engine."
	case 0x40000+1:
		return "A fatal error in the engine has occurred."
	case 0x40000+2:
		return "A hosting API was called with object created on different javascript runtime."

	case 0x50000:
		return "Category of errors that are related to failures during diagnostic operations."
	case 0x50000+1:
		return "The object for which the debugging API was called was not found"
	case 0x50000+2:
		return "The debugging API can only be called when VM is in debug mode"
	case 0x50000+3:
		return "The debugging API can only be called when VM is at a break"
	case 0x50000+4:
		return "Debugging API was called with an invalid handle."
	case 0x50000+5:
		return "The object for which the debugging API was called was not found"
	case 0x50000+6:
		return "VM was unable to perform the request action"
	}
	return ""
}