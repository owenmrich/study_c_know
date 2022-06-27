pwd :显示当前所在目录
ls -l
ls -a :查看隐藏文件
mkdir :新建目录  
    mkdir file
    mkdir -p file/filework :连续创建多级目录,父目录/子目录
rmdir :删除目录  注意不能删除非空目录
cd :打开目录 cd /file
    cd .. :返回上级目录
    cd ../.. :切换到上上级路径
    cd - :回到上次路径
    cd ~ :~用户家目录
    绝对路径/home/study
    相对路径./study/work  ../work
ls :查目录下文件信息 ls -a -l -h
    ls -l :显示文件更详细的信息(文件权限,大小)
    ls -a :显示隐藏文件 (如.local)
    ls -h :将文件以kb mb gb 大小显示

touch :新建文件 touch file 注意同一目录无法创建同名文件 是区分大小写的
mv :修改文件名(目录) /移动路径   (当前目录下的操作)
    mv file1 file2 : mv 旧文件名 新文件名
    mv dir1 dira   : mv 旧目录 新目录
    mv file1 dira  : mv 移动文件到指定目录
    //file1 dira 可以是一个相对或是绝对的路径下的文件/目,进行操作
cp :复制文件(目录) cp -i -r -f -d  (当前目录下的操作)
    cp 1.txt 2.txt :1.txt拷贝为 2.txt
    cp 1.txt fiel  :1.txt拷贝到fiel下
    cp -r dira1 diar2 :dira1目录下的内容复制到dira2目录下, -r递归复制全部内容
    cp -i 1.txt fiel :-i会请求是否要覆盖同名的内容
rm :删除文件(目录) rm -i -r -m   (当前目录下的操作)
    注意文件是否可以被删除 很重要
    rm 2.txt 
    rm -i 2.txt :-i会请求是否要覆盖同名的内容
    rm -ir diar :递归删除,每个文件都会请求是否删除
    rm -f dira  :强制删除 
cat :查看文件内容
    cat -n file :将file的内容打印到标准输出,每一行的内容前显示行号
    cat file file2 :file file2 内容串联打印输出

clear :刷新屏幕,保留历史命令的操作记录（本质就是翻页）
reset :清除屏幕,重新初始化屏幕,清除操作记录
man   :查找命令的用法(主要方法,信息最全,工整)
info  :也可查找帮助信息
 --help:查找命令的用法

命令提示符显示 study@study:~$
1)当前登入的用户名
2)用户当前所在的路径

PATH设置
1.临时设置(当前终端有效)
export PATH=$PATH:/home/study
2.永久设置(对当前用户有效)
修改~/.bashrc 在行尾添加
export PATH=$PATH:/home/book
3.永久修改
修改/etc/environment
PATH:/sur/isd:/hmoe/book

find 查找文件
    find 查找的目录 -name "*.txt" 查找文件
        -name 以名字的方式查找
        *.txt 所有的.txt 文件 *为通配符
    find 查找的目录 -name "dira" 查找目录
    find . -name "*.txt"   
    find -name "*.txt" :当前目录下查找

    find 目录 -mtime -2 可以查找两天内改动的文件

grep 查找文件中符合的字符串
    grep -rn "字符串" 文件名 : r递归查找 n显示行号 文件名为* 查找当前目录下的所有文件和目录
    grep -n "bac" 1.txt
    grep -rn "abc" *
    grep -rnw "abc" 1.txt : w全字匹配 只会有abc

file 识别文件类型
    file 文件名 :如果说目录显示directory

which whereis 查找命令/可执行程序所在位置 
    which 命令/可执行程
    which pdw  :显示定位/bin/pwd
    whereis 命令/可执行程
    whereis :显示定位/bin/pwd  手册页的位置

无损压缩
    gzip :单个文件的压缩 -l(列出压缩文件的内容) -k(压缩或者是解压时,保留输入文件) -d(将压缩文件进行解压)
        gzip -l 压缩文件名 :查看压缩文件信息
        gzip -l pwd.1.gz :查看
        gzip -d pwd.1.gz :解压
        gzip -kd pwd.1.gz :保留源文件解压  
        gzip file :压缩该文件,会生成file.gz 并删除file
        注意
            :文件后缀.gz
            :推荐使用 gzip -k file 会保留file 
            :相同文件,不同名字压缩大小会不一样
            :gzip不能压缩目录 
            :小文件使用gzip
    bzip2 : 单个文件的压缩 -k(压缩或者是解压时,保留输入文件) -d(将压缩文件进行解压)
        bzip2 -k mu
        bzip2 -kd mu.bz2
        bzip2 file :压缩该文件,会生成file.bz2 并删除file
        注意 
            :文件后缀.bz2
            :bzip2不能压目录
            :大文件使用bzip2
    tar :对多个目录,文件进行打包压缩 
        -c(create) 表示创建用来生成文件包
        -x:表示提取,从文件包中提取文件
        -t可以查看压缩的文件。
        -z使用gzip方式进行处理, 它与"c"结合就表示压缩,与"x"结合就表示解压。
        -j使用bzip2方式进行处理, 它与"c"结合就表示压缩,与"x"结合就表示解压。
        -v(verbose)详细报告tar处理的信息
        -f(file)表示文件,后面接着一个文件名。
        -C <指定目录> 解压到指定目录

        1. tar打包,gzip压缩
            tar -czvf 压缩文件名 目录名
            tar -czvf dira.tar.gz dira
            tar -tvf dira.tar.gz :查看压缩文件 
            tar -xzvf dira.tar.gz -C 指定目录 :-C解压到指定的目录 若无,择当前目录
        2. tar打包,bzip2压缩 
            tar -cjvf 压缩文件名 目录名
            tar -cjvf dira.tar.bz2 dira