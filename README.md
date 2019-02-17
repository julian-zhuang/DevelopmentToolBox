# DevelopmentToolBox
开发工具箱

## 介绍

如你所见这是一个开发工具箱，主要面对C/C++的开发人员（QT），集成了常用的小工具。

编译时的QT版本建议不要低于5.0

工作计划
------

功能|状态|备注
---|---|---
创建任务|完成
编辑任务|完成
开始任务|完成
结束任务|完成
删除任务|完成

文件搜索
------
	和everything功能相同
	
功能|状态|备注
---|---|---
文件实时搜索(基础)|完成
文件扩展名过滤|完成|考虑去掉
文件实时搜索(高级)|完成

SocketClient
------
	主要是用于socket客户端的模拟测试  
	支持常见的数据类型：
	char *(Str)  
	char(Int8)\unsigned char(UInt8)  
	short(Int16)\unsigned short(UInt16)  
	int(Int32)\unsigned int(UInt32)  
	long long int(Int64)\unsigned long long int(UInt64)  
	double(Real64)  
	float(Real32)  
	
功能|状态|备注
---|---|---

SocketServer
------

功能|状态|备注
---|---|---

SocketTransfer
------

功能|状态|备注
---|---|---

我会在抽空完成剩余的功能，如果你想的话可以给我发消息，我们可以一起完成这个小工具  
加密部分计划采用openssl进行开发  
文件传输和Http测试部分计划是采用Curl进行开发  
后面还会有一个工具箱在局域网之间快速发送文件的功能，这里的话采用简单的UDP广播发现和TCP传输  
