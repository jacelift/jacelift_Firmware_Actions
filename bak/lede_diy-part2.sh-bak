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

# 【1】修改默认IP地址，Modify default IP
#sed -i 's/192.168.1.1/192.168.50.5/g' package/base-files/files/bin/config_generate


# 【2】===========START 添加wt600机型到lede源码中（不依赖luci-app-mt-wifi）2022.6.14===============
# make from cudy_wr1300 and newifi-d2
chmod 755 -R files/*

#【2.1】修改文件mt7621.mk：add wt600 to target/linux/ramips/image/mt7621.mk
wt600_mt7621.mk(){

define Device/d-team_newifi-d2
  $(Device/uimage-lzma-loader)
  IMAGE_SIZE := 32448k
  DEVICE_VENDOR := Newifi
  DEVICE_MODEL := D2
  DEVICE_COMPAT_VERSION := 1.1
  DEVICE_PACKAGES := kmod-mt7603e kmod-mt76x2e kmod-usb3 \
	kmod-usb-ledtrig-usbport luci-app-mtwifi -wpad-openssl
endef
TARGET_DEVICES += d-team_newifi-d2

define Device/RX_WT600
  $(Device/uimage-lzma-loader)
  IMAGE_SIZE := 32448k
  DEVICE_VENDOR := RX
  DEVICE_MODEL := WT600
  DEVICE_PACKAGES := kmod-mt7603 kmod-mt76x2 kmod-usb2 kmod-usb3 \
	kmod-usb-ledtrig-usbport
endef
TARGET_DEVICES += RX_WT600

}
sed -i '/TARGET_DEVICES += d-team_newifi-d2/a\\ndefine Device\/RX_WT600\n  \$(Device\/uimage-lzma-loader)\n  IMAGE_SIZE := 32448k\n  DEVICE_VENDOR := RX\n  DEVICE_MODEL := WT600\n  DEVICE_PACKAGES := kmod-mt7603 kmod-mt76x2 kmod-usb2 kmod-usb3 \\\n	kmod-usb-ledtrig-usbport\nendef\nTARGET_DEVICES += RX_WT600' target/linux/ramips/image/mt7621.mk


#【2.2】修改文件01_leds：add wt600 to target/linux/ramips/mt7621/base-files/etc/board.d/01_leds
#==========================================
#在指定字符前后添加内容：https://www.cnblogs.com/bulh/articles/11071783.html
#例如：在1111之前添加AAA,方法如下：
#sed -i 's/指定的字符/要插入的字符&/'  文件
#[root@localhost ~]# sed -i  's/1111/AAA&/' /tmp/input.txt                     
#[root@localhost ~]# cat /tmp/input.txt                   
#null
#0000AAA11112222
#在1111之后添加BBB，方法如下：
#sed -i 's/指定的字符/&要插入的字符/'  文件
#[root@localhost ~]# sed -i  's/1111/&BBB/' /tmp/input.txt    
#[root@localhost ~]# cat /tmp/input.txt                   
#null
#0000AAA1111BBB2222
#==========================================
#在指定字符后添加内容:sed -i 's/d-team,newifi-d2/&|\\\nRX,WT600/' target/linux/ramips/mt7621/base-files/etc/board.d/01_leds
#在指定字符前添加内容:
sed -i 's/d-team,newifi-d2/RX,WT600|\\\n&/' target/linux/ramips/mt7621/base-files/etc/board.d/01_leds

#【2.3】修改文件02_network：add wt600 to target/linux/ramips/mt7621/base-files/etc/board.d/02_network
#在指定字符前添加内容：https://www.cnblogs.com/bulh/articles/11071783.html
#sed -i 's/d-team,newifi-d2/&|\\\n	RX,WT600/' target/linux/ramips/mt7621/base-files/etc/board.d/02_network
#===============【修正LAN口顺序】====================
rm -r target/linux/ramips/mt7621/base-files/etc/board.d/02_network
cp -f files/RX_WT600/02_network-test target/linux/ramips/mt7621/base-files/etc/board.d/02_network
#===============【修正LAN口顺序】====================
#sed -i 's/	d-team,newifi-d2/	RX,WT600|\\\n&/' target/linux/ramips/mt7621/base-files/etc/board.d/02_network

#【2.4】新增文件并修改mt7621_RX_WT600.dts：cp target/linux/ramips/dts/mt7621_cudy_wr1300.dts target/linux/ramips/dts/mt7621_RX_WT600.dts
#sed替换字符串操作，多个替换可以在同一条命令中执行,用分号隔开即可“;”。
#sed -i 's/cudy,wr1300/RX,WT600/g;s/Cudy WR1300/RX WT600/g' target/linux/ramips/dts/mt7621_RX_WT600.dts
cp -f files/lede/RX_WT600/mt7621_RX_WT600.dts target/linux/ramips/dts/mt7621_RX_WT600.dts
# 【2】===========END 添加wt600机型到lede源码中（不依赖luci-app-mt-wifi）2022.6.14===============





# 【3】===========START 添加ZTE_E8822机型到lede源码（不依赖luci-app-mt-wifi）2022.7.6===============
# 参考https://github.com/siwind/openwrt openwrt的zte_e8820-v2
chmod 755 -R files/*

# 【3.1】删除原有文件3个
rm -rf target/linux/ramips/mt7621/base-files/etc/board.d/01_leds
rm -rf target/linux/ramips/mt7621/base-files/etc/board.d/02_network
rm -rf target/linux/ramips/image/mt7621.mk

# 【3.2】拷贝ZTE_E8822相关文件4个
cp -f files/lede/ZTE_E8822/01_leds target/linux/ramips/mt7621/base-files/etc/board.d/01_leds
cp -f files/lede/ZTE_E8822/02_network target/linux/ramips/mt7621/base-files/etc/board.d/02_network
cp -f files/lede/ZTE_E8822/mt7621.mk target/linux/ramips/image/mt7621.mk
cp -f files/lede/ZTE_E8822/mt7621_ZTE_E8822.dts target/linux/ramips/dts/mt7621_ZTE_E8822.dts
# 【3】===========END 添加ZTE_E8822机型到lede源码（不依赖luci-app-mt-wifi）2022.7.6===============






#【99】更改openwrt的主机名，Modify hostname
#sed -i 's/OpenWrt/RX_WT600/g' package/base-files/files/bin/config_generate
sed -i 's/OpenWrt/ZTE_E8822/g' package/base-files/files/bin/config_generate


#【100】删除files目录
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
