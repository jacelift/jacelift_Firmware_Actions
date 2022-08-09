/*
 *  OMYlink TL-AP300C-POE-V1 board support
 *
 *  Copyright (C) 2016 L. D. Pinney <ldpinney@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <linux/platform_device.h>

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-m25p80.h"
#include "dev-wmac.h"
#include "machtypes.h"



#define TL_AP300C_POE_V1_GPIO_LED_POWER	19
#define TL_AP300C_POE_V1_GPIO_LED_WAN	22

#define TL_AP300C_POE_V1_GPIO_BTN_RESET	17

#define TL_AP300C_POE_V1_KEYS_POLL_INTERVAL	20	/* msecs */
#define TL_AP300C_POE_V1_KEYS_DEBOUNCE_INTERVAL (3 * TL_AP300C_POE_V1_KEYS_POLL_INTERVAL)

static const char *tl_ap300c_poe_v1_part_probes[] = {
	"tp-link",
	NULL,
};

static struct flash_platform_data tl_ap300c_poe_v1_flash_data = {
	.part_probes	= tl_ap300c_poe_v1_part_probes,
};

static struct gpio_led tl_ap300c_poe_v1_leds_gpio[] __initdata = {
	{
		.name		= "omy:green:wan",
		.gpio		= TL_AP300C_POE_V1_GPIO_LED_WAN,
		.active_low	= 1,
	}, {
		.name		= "omy:green:power",
		.gpio		= TL_AP300C_POE_V1_GPIO_LED_POWER,
		.active_low	= 1,
	},
};

static struct gpio_keys_button tl_ap300c_poe_v1_gpio_keys[] __initdata = {
	{
		.desc		= "Reset button",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = TL_AP300C_POE_V1_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= TL_AP300C_POE_V1_GPIO_BTN_RESET,
		.active_low	= 1,
	}
};

static void __init tl_ap300c_poe_v1_setup(void)
{
	u8 *mac = (u8 *) KSEG1ADDR(0x1f01fc00);
	u8 *ee = (u8 *) KSEG1ADDR(0x1fff1000);

	ath79_gpio_function_setup(AR934X_GPIO_FUNC_JTAG_DISABLE,
				 AR934X_GPIO_FUNC_CLK_OBS4_EN);

	ath79_register_m25p80(&tl_ap300c_poe_v1_flash_data);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(tl_ap300c_poe_v1_leds_gpio),
				tl_ap300c_poe_v1_leds_gpio);

	ath79_register_gpio_keys_polled(1, TL_AP300C_POE_V1_KEYS_POLL_INTERVAL,
				ARRAY_SIZE(tl_ap300c_poe_v1_gpio_keys),
				tl_ap300c_poe_v1_gpio_keys);

	ath79_setup_ar934x_eth_cfg(AR934X_ETH_CFG_SW_PHY_SWAP);

	ath79_register_mdio(1, 0x0);

	ath79_init_mac(ath79_eth0_data.mac_addr, mac, -1);
	ath79_init_mac(ath79_eth1_data.mac_addr, mac, 0);

	ath79_switch_data.phy4_mii_en = 1;
	ath79_switch_data.phy_poll_mask = BIT(0);
	ath79_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_MII;
	ath79_eth0_data.phy_mask = BIT(0);
	ath79_eth0_data.mii_bus_dev = &ath79_mdio1_device.dev;
	ath79_register_eth(0);

	ath79_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_GMII;
	ath79_register_eth(1);

	ath79_register_wmac(ee, mac);

}

MIPS_MACHINE(ATH79_MACH_TL_AP300C_POE_V1, "TL-AP300C-POE-V1", "TP-LINK TL-AP300C-POE-V1",
	     tl_ap300c_poe_v1_setup);
