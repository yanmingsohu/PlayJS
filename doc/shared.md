# shared

线程共享对象.

# 待实现

* [ ] 创建共用缓冲区
* [ ] js 对象在线程间复制


# 参考 (删除)

## ? createSharedBuffer() *未实现

创建线程间共享缓冲区, 该缓冲区可以发送到其他线程, 
安全且没有多余的复制操作.

### 创建Javascript ArrayBuffer对象以访问外部存储器。

句法
	STDAPI_(JsErrorCode)
		JsCreateExternalArrayBuffer(
		_Pre_maybenull_ _Pre_writable_byte_size_(byteLength) void *data,
		_In_ unsigned int byteLength,
		_In_opt_ JsFinalizeCallback finalizeCallback,
		_In_opt_ void *callbackState,
		_Out_ JsValueRef *result);

### 使用来自JsGetSharedArrayBufferContent的共享内容get创建Javascript SharedArrayBuffer对象。

句法
CHAKRA_API
    JsCreateSharedArrayBufferWithSharedContent(
        _In_ JsSharedArrayBufferContentHandle sharedContents,
        _Out_ JsValueRef *result);

### 从SharedArrayBuffer获取存储对象。

句法
CHAKRA_API
    JsGetSharedArrayBufferContent(
        _In_ JsValueRef sharedArrayBuffer,
        _Out_ JsSharedArrayBufferContentHandle *sharedContents);