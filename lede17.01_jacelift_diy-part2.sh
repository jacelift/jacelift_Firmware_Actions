#!/bin/bash
#
# Copyright (c) 2019-2020 P3TERX <https://p3terx.com>
#
# This is free software, licensed under the MIT License.
# See /LICENSE for more information.
#
# https://github.com/P3TERX/Actions-OpenWrt
# File name: diy-part2.sh
# Description: OpenWrt DIY script part 2 (After Update feeds)
#

# Modify default IP
#sed -i 's/192.168.1.1/192.168.50.5/g' package/base-files/files/bin/config_generate

#【01】删除文件
rm -rf target/linux/ath79/image/tiny-tp-link.mk

# 【02】设置权限
chmod 755 -R files/*




#===================================================================================================




#【97】test
cp -f files/lede17.01/test/tiny-tp-link.mk target/linux/ath79/image/tiny-tp-link.mk
touch target/linux/ath79/image/tiny-tp-link.mk

#【98】更改openwrt的主机名，Modify hostname
#sed -i 's/OpenWrt/TL-WDR5800-V1/g' package/base-files/files/bin/config_generate
#sed -i 's/OpenWrt/RX_WT600/g' package/base-files/files/bin/config_generate
#sed -i 's/OpenWrt/NETGEAR_WNDR4300-V1/g' package/base-files/files/bin/config_generate
sed -i 's/OpenWrt/TL-AP300C-POE-V1/g' package/base-files/files/bin/config_generate

#【99】删除files目录
rm -r files





# sed -i '/xxxx定位需要的字符串xxx/a\xxx在定位字符串后面一行（换行）需要添加的字符串内容xxx' xx路径xx/xx文件xx.txt
# 注意：确保sh脚本是unix（LF）UTF-8，而非Windows（CR LF）UTF-8，或者用sed命令去掉sed -i 's/\r$//' xxx.sh。
# 注意：字符串中遇到特殊字符需要用反斜杠屏蔽掉，\n为换行，/xx/a\为定位字符串之后。

# 特殊字符有：
# 1、$ 美元符
# 2、\ 反斜杠
# 3、· 反引号（位于Tab键上方）
# 4、" 双引号
# 5、* 星号
# 6、[ ] 左右中括号
# 7、? 问号
# 8、< > 左右尖括号
# 9、; 分号

# windows下，每一行的结尾是\n\r，而在linux下文件的结尾是\n，
# 那么你在windows下编辑过的文件在linux下打开看的时候每一行的结尾就会多出来一个字符\r,
# 用cat -A yourfile时你可以看到这个\r字符被显示为^M，
# 这时候只需要删除这个字符就可以了。可以使用命令把 xxxxxxx.sh 中的\r 替换成空白：
# sed -i 's/\r$//' xxx.sh
