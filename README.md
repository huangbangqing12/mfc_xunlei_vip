# mfc_xunlei_vip
###迅雷VIP账号密码自动获取工具说明
***
#####工具简介:
本工具可以获取最新的迅雷VIP账号和密码---当天的或者前一天的.
另外提供了一个免T dll,防止在使用的过程中被卡掉. 
         *Author:qianghaohao*
         *Version:v1.0*
***
***
#####1.工程目录说明:
          mfc_xunlei_vip\mfc_xunlei_vip\bin     可执行文件目录
          mfc_xunlei_vip\mfc_xunlei_vip         工程目录
          mfc_xunlei_vip\mfc_xunlei_vip\curl    curl库头文件
          mfc_xunlei_vip\mfc_xunlei_vip\lib     curl静态库
          mfc_xunlei_vip\mfc_xunlei_vip\ini     软件配置文件
          mfc_xunlei_vip\mfc_xunlei_vip\res     MFC资源
          mfc_xunlei_vip\mfc_xunlei_vip\doc     工具相关说明
          mfc_xunlei_vip\mfc_xunlei_vip\Debug   工程其他输出文件
          mfc_xunlei_vip\mfc_xunlei_vip\dll     提供一个免T破解DLL
                       ----->注:对使用不当造成的任何损失,本人概不负责.
                       免Tdll使用:将DLL,覆盖迅雷安装目录program下面的同名文件即可
***
#####2.使用说明:
          点击"开始获取按钮"------>获取到VIP----->点击"导出成文件"按钮可以将账号导出成txt文件.
	  点击 "复制账号"或者按ctrl+c复制选中的账号, 点击 "复制密码"或者按ctrl+f复制选中的密码
          #######------->本程序获取到的迅雷VIP账号和密码都是最新的(当天的或者前一天的).
          ****注意:在刚点击"开始获取"后需要稍微等几秒才能显示出获取结果,不要误以为程序失效了或者卡死了.
![image](https://github.com/qianghaohao/mfc_xunlei_vip/raw/master/img/get_vip_demo.png)
![image](https://github.com/qianghaohao/mfc_xunlei_vip/raw/master/img/vip_list.png)
***
***
#####3. ./ini/profile.ini文件:
          此文件为软件的配置文件,主要是正则表达式的配置,由于网页格式经常变化,所以写成配置文件定期更新,无需
          重新编译代码即可实现更新.只需要更改配置文件的内容即可.以下以注释形式说明个字段个键值的含义:
          
             [MAIN_PAGE_URL]         网站主页段 
             INDEX_URL=http://www.521xunlei.com     网站主页URL
             [XL_VIP_URL]       迅雷VIP页面正则段
             VIP_URL=<em>%s</em>.*</a></label> <a href="(.*\.html)   迅雷VIP页面正则表达式
             [REGEX]      提取字段
             REG=账号[ \t]*(\w+:\d).*\D+(\d+)[<br />|</font><br />]   用了获取VIP账号密码的正则表达式
             
          注意:由于在.\mfc_xunlei_vip\ini目录路径不变,因此在执行程序时必须进入到.\mfc_xunlei_vip\bin目录执行,
          否则会获取失败.  ---->如果非要把bin目录的可执行文件放置到桌面等其他地方,可以通过发送快捷方式的方法
          发送的桌面,桌面有个快捷方式即可.
***
#####4.编译环境:
          Windows10+VS2015
***
***
       本程序仅供娱乐，请不要用作商业用途,如果喜欢迅雷,请购买VIP,享受更多私有服务.
       如果有程序问题，希望可以邮件联系。
***
