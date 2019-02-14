
# fs

文件系统, 所有方法都是同步的, 操作失败后都会抛出异常.  
全局对象, 在任意脚本直接使用.


# TODO: 更多函数需要实现

* [ ] 目录操作
  * [ ] 目录创建
  * [ ] 目录遍历
  * [ ] 目录删除
* [ ] 文件删除
* [ ] 文件大小
* [ ] 文件修改日期


## fd open(path, mode)

打开文件, 返回句柄, 失败会抛出异常, path 相对于程序启动目录.
mode可以是 'w' 写文件, 'r' 读文件等.
句柄可以在多个线程间共享, 但是需要自行同步.


## void close(fd)

关闭文件句柄.


## int fpos(fd)

使用文件句柄获得文件当前指针位置.


## int read(fd, buffer, b_offset, b_length[, f_pos])

从文件句柄 fd 引用的文件中读取数据写出到缓冲区 buffer, 
文件开始偏移为 f_pos, 该参数可以省略.
从缓冲区 b_offset 开始最多写 b_length 个字节.


## int write(fd, buffer, b_offset, b_length[, f_pos])

将缓冲区 buffer 中从 b_offset 开始 b_length 个字节的数据;
写入文件句柄 fd 引用的文件中, 文件从 f_pos 开始写, f_pos 参数可以省略.


## int fileSize(path)

返回文件大小(字节)


## bool exists(path)

文件存在返回 true