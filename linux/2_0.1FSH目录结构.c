Linux文件系统层级结构
Linux的哲学思想是一切皆文件,把几乎所有资源统统抽象为文件形式。

根目录下结构:

/
bin
dev
home
lib
media
opt
root
selinux
sys
usr
boot
etc
lost+found
mut
proc
sbin
srv
tmp
var
解释:

/bin :二进制可执行命令,系统启动必须文件

/dev :存放必要的设备文件

/home :存放普通用户的主目录,包括保存的文件,个人配置,等等

/media :挂载点,linux系统会自动识别一些设备,例如优盘,当识别后,linux会把识别的设备挂载到这个目录下

/opt :附加应用程序的安装位置

/root :系统管理员的家目录

/selinux:安全机制,类似于防火墙

/sys :与/porc相似,主要记录与核心相关资讯

/usr : 应用程序存放目录,/usr/bin存放应用程序, /usr/share存放共享数据,/usr/lib 存放不能直接运行的,却是许多程序运行所必需的一些函数库文件,/usr/local存放软件升级包,/usr/share/doc系统说明文件存放目录

/boot:存放引导加载器(bootstrap loader)使用的文件、

/etc :系统程序的配置文件,均为静态文件

/lib :系统配置文件存放的目录,该目录存放系统的大部分配置文件和子目录

/lost+found :一般为空,系统发生错误时,将遗失的片段放入。

/mut :其他文件系统的临时挂载点

/proc :以文件形式提供进程以及内核信息的虚拟文件系统,如 cpu 硬盘分区 内存信息等

/sbin :供系统管理使用的工具程序的目录,也不可以进行单独分区

/srv :当前主机为服务器提供的数据文件存放的目录

/tmp :存放程序运行产生临时文件 (另见 /var/tmp). 通常在系统重启后删除

/var :针对常态性变动文件,一些随着系统常规操作而持续改变的文件就放在这里

/etc下重要文件,目录。
bashrc	bash环境变量配置,里边添加启动bash时读取的环境
crontab	指定任务的配置文件
fstab	记录开机后要挂载的文件系统
group	用户组信息
gshadow	用户组密码配置文件
hosts	设定用户IP与名字(域名)的对应解析表,相当于本地LAN内的DNS
issue	用户登录前显示的信息
shells	当前系统支持的shell
skel/	新用户默认的环境信息文件
login.defs	设定用户账号限制信息
yum.repos.d	yum仓库配置信息
sysconfig/network	修改机器名,网卡网关等信息
ssh	存放shh服务配置文件
profile	系统全局环境变量设置,可以添加对所有用户组有效的环境变量,系统变量,用户登录后被执行。
profile.d	系统启动后要执行的脚本
/proc 下重要文件 目录
bus	总线设备
cpuinfo	记录了 处理器的信息
meminfo	记录了存储器信息(内存,交换信息)
filesystems	核心配置的文件系统信息
mounts	内核加载的核心模块信息
partitions	里面记录了分区信息
uptime	系统启动时长
/var下重要文件 目录
cache	储存了系统运行本身产生的缓存信息
local	/usr/local/中安装的程序的一些可变数据
lock	锁定的文件,因为某些设备或文件资源一次只能被一个应用程序使用
log	各种日志文件
spool	队列数据,(排队等待后续进程使用的数据,使用后被删除)
tmp	存储应用进程产生的临时文件
lib	程序本身执行过程中,需要的数据文件放置的目录