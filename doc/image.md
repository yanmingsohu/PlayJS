# image

读取图片数据.


## load(filename)

从应用程序目录开始读取文件, 返回图像对象, 或在失败后抛出异常.

返回 {
  x: 总宽度像素数量, y: 高度, channels: 每个像素通道数(一个通道8bit)
  data: 字节缓冲区对象
}


## flip_vertically_on_load(bool)

设置在读取时反转 y 轴.