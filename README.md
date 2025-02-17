[中文](README.md) ||  [English](README.en.md)  
# XEngine_IPMac
本仓库有开发和主分支,如果要使用,请使用master分支下的代码  
只要仓库不是在暂停状态,那么就会有人一直维护和开发,请放心使用  

## 介绍
IP地址和MAC地址归属查询  
IP address and MAC address ownership query  

## 软件特性
1. 支持IP地址归属查询
2. 支持MAC地址厂商查询
3. 提供数据库接口方法,不限制使用语言

## 安装教程

#### XEngine环境
想要编译我们的例子,需要XEngine环境,版本需要V8.x或者以上版本,安装XEngine可以参考其Readme文档  
GITEE:https://gitee.com/libxengine/libxengine  
GITHUB:https://github.com/libxengine/libxengine

###### 快速部署
git clone https://gitee.com/libxengine/libxengine.git 或者 git clone https://github.com/libxengine/libxengine.git  
window执行XEngine_WINEnv.bat 脚本.  
Linux执行:sudo ./XEngine_LINEnv.sh -i 3  
macos执行:./XEngine_LINEnv.sh -i 3  

#### Windows编译
直接使用VS即可

#### Linux或者MacOS编译
在XEngine_Source目录下执行命令  
make 编译  
make FLAGS=InstallAll 安装库程序  
make FLAGS=CleanAll 清理编译  

## 数据结构
#### IP数据结构
请参考数据来源
#### MAC数据结构
XENGINE_PROTOCOLHDR头+XENGINE_MACADDRINFO[Array]  
标准协议头里面设定了数据源的类型和个数以及负载大小.后面跟上多个XENGINE_MACADDRINFO数据结构.每个结构保存了MAC地址信息.如下:  
XCHAR为一个字节.MAX_PATH为260字节  
 - XCHAR tszVendorName[MAX_PATH];     //厂商
 - XCHAR tszMACPrefix[64];            //MAC地址
 - XCHAR tszUPTime[16];               //更新时间
 - XCHAR tszBlockType[8];             //类型
 - bool bPrivate;                     //是否是私有的

## 使用说明

1.  切换到MASTER分支
2.  下载代码
3.  编译
4.  安装
5.  运行

## 目录结构
- XEngine_Docment    文档目录结构  
- XEngine_Release    安装目录结构  
- XEngine_Source     源代目录结构  
- XEngine_APPClient  客户端演示代码  

## 参与贡献
希望大家多多提交代码参与贡献  

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request  

## 关注我们
如果你觉得这个软件对你有帮助,请你给我们一个START吧

## 提交问题

如果你有问题或者发现程序有BUG和意见,可以在issues中提交  

## 数据来源
#### IP数据库
@ip2region

#### MAC数据库
@MACLookup 