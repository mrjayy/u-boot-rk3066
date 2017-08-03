/*
 * Copyright (c) 2017 Paweł Jarosz <paweljarosz3691@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CONFIG_RK3066_COMMON_H
#define __CONFIG_RK3066_COMMON_H

#include <asm/arch/hardware.h>
#include "rockchip-common.h"

#define CONFIG_SKIP_LOWLEVEL_INIT_ONLY
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE			0x2000
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_MALLOC_LEN		(64 << 20)
#define CONFIG_SYS_CBSIZE		256

#define CONFIG_SYS_TIMER_RATE		24000000
#define CONFIG_SYS_TIMER_BASE		0x20038000
#define CONFIG_SYS_TIMER_COUNTER	(CONFIG_SYS_TIMER_BASE + 4)
#define CONFIG_SYS_TIMER_COUNTS_DOWN

#define CONFIG_SPL_BOARD_INIT

#define CONFIG_SYS_TEXT_BASE		0x60408000

#define CONFIG_SYS_INIT_SP_ADDR		0x78000000
#define CONFIG_SYS_LOAD_ADDR		0x70800800

#ifdef CONFIG_TPL_BUILD
#define CONFIG_SPL_TEXT_BASE		0x10080C04
#define CONFIG_SPL_STACK		0x1008FFFF
/* tpl size max 32kb - 4byte RK30 header */
#define CONFIG_SPL_MAX_SIZE		(0x8000 - 0x4)

#define CONFIG_TPL_RAM

#elif defined(CONFIG_SPL_BUILD)
/* spl size max 200k */
#define CONFIG_SPL_MAX_SIZE		0x32000
#define CONFIG_SPL_TEXT_BASE		0x60000000
#define CONFIG_SPL_STACK		0x1008FFFF
#define CONFIG_SPL_STACK_R_ADDR		0x70000000
#define CONFIG_SPL_STACK_R		1
#define CONFIG_SPL_STACK_R_MALLOC_SIMPLE_LEN 0x200000
#define CONFIG_SPL_OF_CONTROL		1
#define CONFIG_SPL_OF_PLATDATA		1
#define CONFIG_SPL_FRAMEWORK		1
#define CONFIG_SPL_CLK			1
#define CONFIG_SPL_PINCTRL		1
#define CONFIG_SPL_REGMAP		1
#define CONFIG_SPL_SYSCON		1
#define CONFIG_SPL_RAM			1
#define CONFIG_SPL_DRIVERS_MISC_SUPPORT	1
#define CONFIG_ROCKCHIP_SERIAL		1
#define CONFIG_SPL_NAND_DRIVERS		1
#define CONFIG_SPL_MMC_SUPPORT		1
#define CONFIG_SPL_FS_LOAD_PAYLOAD_NAME	"u-boot-dtb.bin"
#define CONFIG_SPL_DOS_PARTITION 	1
#define CONFIG_SPL_EXT_SUPPORT		1
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION      1
#define CONFIG_SPL_LIBDISK_SUPPORT	1
#endif

#define CONFIG_SYS_NS16550_MEM32

#define CONFIG_ROCKCHIP_MAX_INIT_SIZE	(0x10000 - 0xC00)
#define CONFIG_ROCKCHIP_CHIP_TAG	"RK30"

/* MMC/SD IP block */
#define CONFIG_BOUNCE_BUFFER

#define CONFIG_CMD_CACHE

#define CONFIG_SYS_SDRAM_BASE		0x60000000
#define CONFIG_NR_DRAM_BANKS		1
#define SDRAM_BANK_SIZE			(1024UL << 20UL)
#define SDRAM_MAX_SIZE			CONFIG_NR_DRAM_BANKS * SDRAM_BANK_SIZE

#ifndef CONFIG_SPL_BUILD
/* usb */
#define CONFIG_USB
#define CONFIG_DM_USB
#define CONFIG_USB_STORAGE
#define CONFIG_CMD_USB
#define CONFIG_USB_DWC2

#define CONFIG_USB_GADGET
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_GADGET_DWC2_OTG
#define CONFIG_USB_GADGET_VBUS_DRAW	0 

#define CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_CMD_USB_MASS_STORAGE

#define CONFIG_USB_GADGET_DOWNLOAD
#define CONFIG_G_DNL_MANUFACTURER	"Rockchip"
#define CONFIG_G_DNL_VENDOR_NUM		0x2207
#define CONFIG_G_DNL_PRODUCT_NUM	0x300a

/* fastboot */
#define CONFIG_FASTBOOT
#define CONFIG_USB_FUNCTION_FASTBOOT
#define CONFIG_CMD_FASTBOOT
#define CONFIG_FASTBOOT_BUF_ADDR 	0x80000000
#define CONFIG_FASTBOOT_BUF_SIZE 	0x1d000000
#define CONFIG_FASTBOOT_FLASH
#define CONFIG_FASTBOOT_FLASH_NAND_DEV	0

/* nand */
#define CONFIG_NAND
#define CONFIG_SYS_NAND_U_BOOT_OFFS		0x01c00000
#define CONFIG_SYS_NAND_U_BOOT_OFFS_REDUND	0x02000000
#define CONFIG_SYS_MAX_NAND_DEVICE	8
#define CONFIG_MTD_DEVICE
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_PARTITIONS
#define MTDIDS_DEFAULT			"nand0=rockchip-nand.0"

/* DFU */
#define CONFIG_DFU_NAND
#define CONFIG_USB_FUNCTION_DFU
#define CONFIG_DFU_RAM
#define CONFIG_CMD_DFU
#define CONFIG_SYS_DFU_DATA_BUF_SIZE SZ_1M
#define DFU_ALT_INFO_NAND \
		"idb part 0 1;" \
		"idb.backup part 0 2;" \
		"spl part 0 3;" \
		"spl.backup1 part 0 4;" \
		"spl.backup2 part 0 5;" \
		"spl.backup3 part 0 6;" \
		"spl.backup4 part 0 7;" \
		"u-boot part 0 8;" \
		"u-boot.backup part 0 9;" \
		"u-boot-env part 0 10;" \
		"u-boot-env.backup part 0 11;" \
		"kernel part 0 12;" \
		"initrd part 0 13;" \
		"rootfs part 0 14"

#define ENV_MEM_LAYOUT_SETTINGS \
	"scriptaddr=0x60000000\0" \
	"pxefile_addr_r=0x60100000\0" \
	"fdt_addr_r=0x61f00000\0" \
	"kernel_addr_r=0x62000000\0" \
	"ramdisk_addr_r=0x64000000\0"

#include <config_distro_bootcmd.h>

#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0x6fffffff\0" \
	"initrd_high=0x6fffffff\0" \
	"partitions=" PARTS_DEFAULT \
	"mtdids=" MTDIDS_DEFAULT "\0" \
	"dfu_alt_info=" DFU_ALT_INFO_NAND "\0" \
	ENV_MEM_LAYOUT_SETTINGS \
	ROCKCHIP_DEVICE_SETTINGS \
	BOOTENV

#include <config_distro_defaults.h>
#endif

#define CONFIG_PREBOOT

#endif
