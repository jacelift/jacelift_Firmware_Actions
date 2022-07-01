
grep -irl "wdr6500" target/linux/*

�ο�wdr6500-v2���wdr5800-v1����

���ļ��б�
target/linux/ar71xx/config-4.14
target/linux/ar71xx/generic/config-default
target/linux/ar71xx/config-4.9
target/linux/ar71xx/files/arch/mips/ath79/Makefile
target/linux/ar71xx/files/arch/mips/ath79/mach-tl-wdr5800-v1.c
target/linux/ar71xx/files/arch/mips/ath79/machtypes.h
target/linux/ar71xx/files/arch/mips/ath79/Kconfig.openwrt
target/linux/ar71xx/base-files/etc/board.d/02_network
target/linux/ar71xx/base-files/etc/board.d/01_leds
target/linux/ar71xx/base-files/etc/hotplug.d/firmware/11-ath10k-caldata
target/linux/ar71xx/base-files/etc/diag.sh
target/linux/ar71xx/base-files/lib/ar71xx.sh
target/linux/ar71xx/base-files/lib/upgrade/platform.sh
target/linux/ar71xx/image/generic-tp-link.mk

=========================================








���޸ġ�
target/linux/ar71xx/config-4.14
target/linux/ar71xx/generic/config-default
target/linux/ar71xx/config-4.9
target/linux/ar71xx/files/arch/mips/ath79/Makefile
target/linux/ar71xx/files/arch/mips/ath79/machtypes.h
target/linux/ar71xx/files/arch/mips/ath79/Kconfig.openwrt
target/linux/ar71xx/base-files/etc/board.d/02_network
target/linux/ar71xx/base-files/etc/board.d/01_leds
target/linux/ar71xx/base-files/etc/hotplug.d/firmware/11-ath10k-caldata
target/linux/ar71xx/base-files/etc/diag.sh
target/linux/ar71xx/base-files/lib/ar71xx.sh
target/linux/ar71xx/base-files/lib/upgrade/platform.sh
target/linux/ar71xx/image/generic-tp-link.mk

��������
target/linux/ar71xx/files/arch/mips/ath79/mach-tl-wdr5800-v1.c
===============================================











�����5Ghz��������qca9887��
target/linux/ar71xx/image/generic-tp-link.mk��

define Device/tl-wdr5800-v1
  $(Device/tplink-16mlzma)
  DEVICE_TITLE := TP-LINK TL-WDR5800 v1 (16MB)
  DEVICE_PACKAGES := kmod-ath10k ath10k-firmware-qca9887
  KERNEL := kernel-bin | patch-cmdline | lzma | uImage lzma
  KERNEL_INITRAMFS := kernel-bin | patch-cmdline | lzma | uImage lzma | tplink-v1-header
  BOARDNAME := TL-WDR5800-v1
  DEVICE_PROFILE := TLWDR5800V1
  TPLINK_HWID := 0x58000001
  TPLINK_HEADER_VERSION := 1
endef
TARGET_DEVICES += tl-wdr5800-v1




������LAN��˳��
target/linux/ar71xx/base-files/etc/board.d/02_network��
...
ar71xx_setup_interfaces()
{
	local board="$1"

	case "$board" in
	tl-wdr5800-v1)
		ucidef_set_interfaces_lan_wan "eth1.1" "eth0"
		ucidef_add_switch "switch0" \
			"0@eth1" "1:lan:4" "2:lan:3" "3:lan:2" "4:lan:1"
		;;

===================================



��lede17.01���뱨����������
��step-2��Դ�룺
package/network/utils/iproute2/Makefile��
��Package/ip-full��Package/tc����ȱ�ٵ�����+libcap


========��ǰ��================================================
define Package/ip-full
$(call Package/iproute2/Default)
 TITLE:=Routing control utility (Full)
 VARIANT:=full
 PROVIDES:=ip
 ALTERNATIVES:=300:/sbin/ip:/usr/libexec/ip-full
 DEPENDS:=+libnl-tiny +libelf +(PACKAGE_devlink||PACKAGE_rdma):libmnl
endef

define Package/tc
$(call Package/iproute2/Default)
  TITLE:=Traffic control utility
  VARIANT:=tc
  PROVIDES:=tc
  DEPENDS:=+kmod-sched-core +libxtables +libelf +(PACKAGE_devlink||PACKAGE_rdma):libmnl
endef
===============================================================


=====================================�ĺ�===============================
define Package/ip-full
$(call Package/iproute2/Default)
 TITLE:=Routing control utility (Full)
 VARIANT:=full
 PROVIDES:=ip
 ALTERNATIVES:=300:/sbin/ip:/usr/libexec/ip-full
 DEPENDS:=+libnl-tiny +libelf +libcap +(PACKAGE_devlink||PACKAGE_rdma):libmnl
endef

define Package/tc
$(call Package/iproute2/Default)
  TITLE:=Traffic control utility
  VARIANT:=tc
  PROVIDES:=tc
  DEPENDS:=+kmod-sched-core +libxtables +libelf +libcap +(PACKAGE_devlink||PACKAGE_rdma):libmnl
endef
===========================================================================


��step-3��
make menuconfig����libraries��ѡ��libcap

.config��
CONFIG_PACKAGE_libcap=y