multiline_comment|/*&n; * linux/include/asm-arm/arch-versatile/platform.h&n; *&n; * Copyright (c) ARM Limited 2003.  All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __address_h
DECL|macro|__address_h
mdefine_line|#define __address_h                     1
multiline_comment|/*&n; * Memory definitions&n; */
DECL|macro|VERSATILE_BOOT_ROM_LO
mdefine_line|#define VERSATILE_BOOT_ROM_LO          0x30000000&t;&t;/* DoC Base (64Mb)...*/
DECL|macro|VERSATILE_BOOT_ROM_HI
mdefine_line|#define VERSATILE_BOOT_ROM_HI          0x30000000
DECL|macro|VERSATILE_BOOT_ROM_BASE
mdefine_line|#define VERSATILE_BOOT_ROM_BASE        VERSATILE_BOOT_ROM_HI&t; /*  Normal position */
DECL|macro|VERSATILE_BOOT_ROM_SIZE
mdefine_line|#define VERSATILE_BOOT_ROM_SIZE        SZ_64M
DECL|macro|VERSATILE_SSRAM_BASE
mdefine_line|#define VERSATILE_SSRAM_BASE           /* VERSATILE_SSMC_BASE ? */
DECL|macro|VERSATILE_SSRAM_SIZE
mdefine_line|#define VERSATILE_SSRAM_SIZE           SZ_2M
DECL|macro|VERSATILE_FLASH_BASE
mdefine_line|#define VERSATILE_FLASH_BASE           0x34000000
DECL|macro|VERSATILE_FLASH_SIZE
mdefine_line|#define VERSATILE_FLASH_SIZE           SZ_64M
multiline_comment|/* &n; *  SDRAM&n; */
DECL|macro|VERSATILE_SDRAM_BASE
mdefine_line|#define VERSATILE_SDRAM_BASE           0x00000000
multiline_comment|/* &n; *  Logic expansion modules&n; * &n; */
multiline_comment|/* ------------------------------------------------------------------------&n; *  Versatile Registers&n; * ------------------------------------------------------------------------&n; * &n; */
DECL|macro|VERSATILE_SYS_ID_OFFSET
mdefine_line|#define VERSATILE_SYS_ID_OFFSET               0x00
DECL|macro|VERSATILE_SYS_SW_OFFSET
mdefine_line|#define VERSATILE_SYS_SW_OFFSET               0x04
DECL|macro|VERSATILE_SYS_LED_OFFSET
mdefine_line|#define VERSATILE_SYS_LED_OFFSET              0x08
DECL|macro|VERSATILE_SYS_OSC0_OFFSET
mdefine_line|#define VERSATILE_SYS_OSC0_OFFSET             0x0C
macro_line|#if defined(CONFIG_ARCH_VERSATILE_PB)
DECL|macro|VERSATILE_SYS_OSC1_OFFSET
mdefine_line|#define VERSATILE_SYS_OSC1_OFFSET             0x10
DECL|macro|VERSATILE_SYS_OSC2_OFFSET
mdefine_line|#define VERSATILE_SYS_OSC2_OFFSET             0x14
DECL|macro|VERSATILE_SYS_OSC3_OFFSET
mdefine_line|#define VERSATILE_SYS_OSC3_OFFSET             0x18
DECL|macro|VERSATILE_SYS_OSC4_OFFSET
mdefine_line|#define VERSATILE_SYS_OSC4_OFFSET             0x1C
macro_line|#elif defined(CONFIG_MACH_VERSATILE_AB)
DECL|macro|VERSATILE_SYS_OSC1_OFFSET
mdefine_line|#define VERSATILE_SYS_OSC1_OFFSET             0x1C
macro_line|#endif
DECL|macro|VERSATILE_SYS_LOCK_OFFSET
mdefine_line|#define VERSATILE_SYS_LOCK_OFFSET             0x20
DECL|macro|VERSATILE_SYS_100HZ_OFFSET
mdefine_line|#define VERSATILE_SYS_100HZ_OFFSET            0x24
DECL|macro|VERSATILE_SYS_CFGDATA1_OFFSET
mdefine_line|#define VERSATILE_SYS_CFGDATA1_OFFSET         0x28
DECL|macro|VERSATILE_SYS_CFGDATA2_OFFSET
mdefine_line|#define VERSATILE_SYS_CFGDATA2_OFFSET         0x2C
DECL|macro|VERSATILE_SYS_FLAGS_OFFSET
mdefine_line|#define VERSATILE_SYS_FLAGS_OFFSET            0x30
DECL|macro|VERSATILE_SYS_FLAGSSET_OFFSET
mdefine_line|#define VERSATILE_SYS_FLAGSSET_OFFSET         0x30
DECL|macro|VERSATILE_SYS_FLAGSCLR_OFFSET
mdefine_line|#define VERSATILE_SYS_FLAGSCLR_OFFSET         0x34
DECL|macro|VERSATILE_SYS_NVFLAGS_OFFSET
mdefine_line|#define VERSATILE_SYS_NVFLAGS_OFFSET          0x38
DECL|macro|VERSATILE_SYS_NVFLAGSSET_OFFSET
mdefine_line|#define VERSATILE_SYS_NVFLAGSSET_OFFSET       0x38
DECL|macro|VERSATILE_SYS_NVFLAGSCLR_OFFSET
mdefine_line|#define VERSATILE_SYS_NVFLAGSCLR_OFFSET       0x3C
DECL|macro|VERSATILE_SYS_RESETCTL_OFFSET
mdefine_line|#define VERSATILE_SYS_RESETCTL_OFFSET         0x40
DECL|macro|VERSATILE_SYS_PICCTL_OFFSET
mdefine_line|#define VERSATILE_SYS_PICCTL_OFFSET           0x44
DECL|macro|VERSATILE_SYS_MCI_OFFSET
mdefine_line|#define VERSATILE_SYS_MCI_OFFSET              0x48
DECL|macro|VERSATILE_SYS_FLASH_OFFSET
mdefine_line|#define VERSATILE_SYS_FLASH_OFFSET            0x4C
DECL|macro|VERSATILE_SYS_CLCD_OFFSET
mdefine_line|#define VERSATILE_SYS_CLCD_OFFSET             0x50
DECL|macro|VERSATILE_SYS_CLCDSER_OFFSET
mdefine_line|#define VERSATILE_SYS_CLCDSER_OFFSET          0x54
DECL|macro|VERSATILE_SYS_BOOTCS_OFFSET
mdefine_line|#define VERSATILE_SYS_BOOTCS_OFFSET           0x58
DECL|macro|VERSATILE_SYS_24MHz_OFFSET
mdefine_line|#define VERSATILE_SYS_24MHz_OFFSET            0x5C
DECL|macro|VERSATILE_SYS_MISC_OFFSET
mdefine_line|#define VERSATILE_SYS_MISC_OFFSET             0x60
DECL|macro|VERSATILE_SYS_TEST_OSC0_OFFSET
mdefine_line|#define VERSATILE_SYS_TEST_OSC0_OFFSET        0x80
DECL|macro|VERSATILE_SYS_TEST_OSC1_OFFSET
mdefine_line|#define VERSATILE_SYS_TEST_OSC1_OFFSET        0x84
DECL|macro|VERSATILE_SYS_TEST_OSC2_OFFSET
mdefine_line|#define VERSATILE_SYS_TEST_OSC2_OFFSET        0x88
DECL|macro|VERSATILE_SYS_TEST_OSC3_OFFSET
mdefine_line|#define VERSATILE_SYS_TEST_OSC3_OFFSET        0x8C
DECL|macro|VERSATILE_SYS_TEST_OSC4_OFFSET
mdefine_line|#define VERSATILE_SYS_TEST_OSC4_OFFSET        0x90
DECL|macro|VERSATILE_SYS_BASE
mdefine_line|#define VERSATILE_SYS_BASE                    0x10000000
DECL|macro|VERSATILE_SYS_ID
mdefine_line|#define VERSATILE_SYS_ID                      (VERSATILE_SYS_BASE + VERSATILE_SYS_ID_OFFSET)
DECL|macro|VERSATILE_SYS_SW
mdefine_line|#define VERSATILE_SYS_SW                      (VERSATILE_SYS_BASE + VERSATILE_SYS_SW_OFFSET)
DECL|macro|VERSATILE_SYS_LED
mdefine_line|#define VERSATILE_SYS_LED                     (VERSATILE_SYS_BASE + VERSATILE_SYS_LED_OFFSET)
DECL|macro|VERSATILE_SYS_OSC0
mdefine_line|#define VERSATILE_SYS_OSC0                    (VERSATILE_SYS_BASE + VERSATILE_SYS_OSC0_OFFSET)
DECL|macro|VERSATILE_SYS_OSC1
mdefine_line|#define VERSATILE_SYS_OSC1                    (VERSATILE_SYS_BASE + VERSATILE_SYS_OSC1_OFFSET)
macro_line|#if defined(CONFIG_ARCH_VERSATILE_PB)
DECL|macro|VERSATILE_SYS_OSC2
mdefine_line|#define VERSATILE_SYS_OSC2                    (VERSATILE_SYS_BASE + VERSATILE_SYS_OSC2_OFFSET)
DECL|macro|VERSATILE_SYS_OSC3
mdefine_line|#define VERSATILE_SYS_OSC3                    (VERSATILE_SYS_BASE + VERSATILE_SYS_OSC3_OFFSET)
DECL|macro|VERSATILE_SYS_OSC4
mdefine_line|#define VERSATILE_SYS_OSC4                    (VERSATILE_SYS_BASE + VERSATILE_SYS_OSC4_OFFSET)
macro_line|#endif
DECL|macro|VERSATILE_SYS_LOCK
mdefine_line|#define VERSATILE_SYS_LOCK                    (VERSATILE_SYS_BASE + VERSATILE_SYS_LOCK_OFFSET)
DECL|macro|VERSATILE_SYS_100HZ
mdefine_line|#define VERSATILE_SYS_100HZ                   (VERSATILE_SYS_BASE + VERSATILE_SYS_100HZ_OFFSET)
DECL|macro|VERSATILE_SYS_CFGDATA1
mdefine_line|#define VERSATILE_SYS_CFGDATA1                (VERSATILE_SYS_BASE + VERSATILE_SYS_CFGDATA1_OFFSET)
DECL|macro|VERSATILE_SYS_CFGDATA2
mdefine_line|#define VERSATILE_SYS_CFGDATA2                (VERSATILE_SYS_BASE + VERSATILE_SYS_CFGDATA2_OFFSET)
DECL|macro|VERSATILE_SYS_FLAGS
mdefine_line|#define VERSATILE_SYS_FLAGS                   (VERSATILE_SYS_BASE + VERSATILE_SYS_FLAGS_OFFSET)
DECL|macro|VERSATILE_SYS_FLAGSSET
mdefine_line|#define VERSATILE_SYS_FLAGSSET                (VERSATILE_SYS_BASE + VERSATILE_SYS_FLAGSSET_OFFSET)
DECL|macro|VERSATILE_SYS_FLAGSCLR
mdefine_line|#define VERSATILE_SYS_FLAGSCLR                (VERSATILE_SYS_BASE + VERSATILE_SYS_FLAGSCLR_OFFSET)
DECL|macro|VERSATILE_SYS_NVFLAGS
mdefine_line|#define VERSATILE_SYS_NVFLAGS                 (VERSATILE_SYS_BASE + VERSATILE_SYS_NVFLAGS_OFFSET)
DECL|macro|VERSATILE_SYS_NVFLAGSSET
mdefine_line|#define VERSATILE_SYS_NVFLAGSSET              (VERSATILE_SYS_BASE + VERSATILE_SYS_NVFLAGSSET_OFFSET)
DECL|macro|VERSATILE_SYS_NVFLAGSCLR
mdefine_line|#define VERSATILE_SYS_NVFLAGSCLR              (VERSATILE_SYS_BASE + VERSATILE_SYS_NVFLAGSCLR_OFFSET)
DECL|macro|VERSATILE_SYS_RESETCTL
mdefine_line|#define VERSATILE_SYS_RESETCTL                (VERSATILE_SYS_BASE + VERSATILE_SYS_RESETCTL_OFFSET)
DECL|macro|VERSATILE_SYS_PICCTL
mdefine_line|#define VERSATILE_SYS_PICCTL                  (VERSATILE_SYS_BASE + VERSATILE_SYS_PICCTL_OFFSET)
DECL|macro|VERSATILE_SYS_MCI
mdefine_line|#define VERSATILE_SYS_MCI                     (VERSATILE_SYS_BASE + VERSATILE_SYS_MCI_OFFSET)
DECL|macro|VERSATILE_SYS_FLASH
mdefine_line|#define VERSATILE_SYS_FLASH                   (VERSATILE_SYS_BASE + VERSATILE_SYS_FLASH_OFFSET)
DECL|macro|VERSATILE_SYS_CLCD
mdefine_line|#define VERSATILE_SYS_CLCD                    (VERSATILE_SYS_BASE + VERSATILE_SYS_CLCD_OFFSET)
DECL|macro|VERSATILE_SYS_CLCDSER
mdefine_line|#define VERSATILE_SYS_CLCDSER                 (VERSATILE_SYS_BASE + VERSATILE_SYS_CLCDSER_OFFSET)
DECL|macro|VERSATILE_SYS_BOOTCS
mdefine_line|#define VERSATILE_SYS_BOOTCS                  (VERSATILE_SYS_BASE + VERSATILE_SYS_BOOTCS_OFFSET)
DECL|macro|VERSATILE_SYS_24MHz
mdefine_line|#define VERSATILE_SYS_24MHz                   (VERSATILE_SYS_BASE + VERSATILE_SYS_24MHz_OFFSET)
DECL|macro|VERSATILE_SYS_MISC
mdefine_line|#define VERSATILE_SYS_MISC                    (VERSATILE_SYS_BASE + VERSATILE_SYS_MISC_OFFSET)
DECL|macro|VERSATILE_SYS_TEST_OSC0
mdefine_line|#define VERSATILE_SYS_TEST_OSC0               (VERSATILE_SYS_BASE + VERSATILE_SYS_TEST_OSC0_OFFSET)
DECL|macro|VERSATILE_SYS_TEST_OSC1
mdefine_line|#define VERSATILE_SYS_TEST_OSC1               (VERSATILE_SYS_BASE + VERSATILE_SYS_TEST_OSC1_OFFSET)
DECL|macro|VERSATILE_SYS_TEST_OSC2
mdefine_line|#define VERSATILE_SYS_TEST_OSC2               (VERSATILE_SYS_BASE + VERSATILE_SYS_TEST_OSC2_OFFSET)
DECL|macro|VERSATILE_SYS_TEST_OSC3
mdefine_line|#define VERSATILE_SYS_TEST_OSC3               (VERSATILE_SYS_BASE + VERSATILE_SYS_TEST_OSC3_OFFSET)
DECL|macro|VERSATILE_SYS_TEST_OSC4
mdefine_line|#define VERSATILE_SYS_TEST_OSC4               (VERSATILE_SYS_BASE + VERSATILE_SYS_TEST_OSC4_OFFSET)
multiline_comment|/* &n; * Values for VERSATILE_SYS_RESET_CTRL&n; */
DECL|macro|VERSATILE_SYS_CTRL_RESET_CONFIGCLR
mdefine_line|#define VERSATILE_SYS_CTRL_RESET_CONFIGCLR    0x01
DECL|macro|VERSATILE_SYS_CTRL_RESET_CONFIGINIT
mdefine_line|#define VERSATILE_SYS_CTRL_RESET_CONFIGINIT   0x02
DECL|macro|VERSATILE_SYS_CTRL_RESET_DLLRESET
mdefine_line|#define VERSATILE_SYS_CTRL_RESET_DLLRESET     0x03
DECL|macro|VERSATILE_SYS_CTRL_RESET_PLLRESET
mdefine_line|#define VERSATILE_SYS_CTRL_RESET_PLLRESET     0x04
DECL|macro|VERSATILE_SYS_CTRL_RESET_POR
mdefine_line|#define VERSATILE_SYS_CTRL_RESET_POR          0x05
DECL|macro|VERSATILE_SYS_CTRL_RESET_DoC
mdefine_line|#define VERSATILE_SYS_CTRL_RESET_DoC          0x06
DECL|macro|VERSATILE_SYS_CTRL_LED
mdefine_line|#define VERSATILE_SYS_CTRL_LED         (1 &lt;&lt; 0)
multiline_comment|/* ------------------------------------------------------------------------&n; *  Versatile control registers&n; * ------------------------------------------------------------------------&n; */
multiline_comment|/* &n; * VERSATILE_IDFIELD&n; *&n; * 31:24 = manufacturer (0x41 = ARM)&n; * 23:16 = architecture (0x08 = AHB system bus, ASB processor bus)&n; * 15:12 = FPGA (0x3 = XVC600 or XVC600E)&n; * 11:4  = build value&n; * 3:0   = revision number (0x1 = rev B (AHB))&n; */
multiline_comment|/*&n; * VERSATILE_SYS_LOCK&n; *     control access to SYS_OSCx, SYS_CFGDATAx, SYS_RESETCTL, &n; *     SYS_CLD, SYS_BOOTCS&n; */
DECL|macro|VERSATILE_SYS_LOCK_LOCKED
mdefine_line|#define VERSATILE_SYS_LOCK_LOCKED    (1 &lt;&lt; 16)
DECL|macro|VERSATILE_SYS_LOCKVAL_MASK
mdefine_line|#define VERSATILE_SYS_LOCKVAL_MASK&t;0xFFFF&t;&t;/* write 0xA05F to enable write access */
multiline_comment|/*&n; * VERSATILE_SYS_FLASH&n; */
DECL|macro|VERSATILE_FLASHPROG_FLVPPEN
mdefine_line|#define VERSATILE_FLASHPROG_FLVPPEN&t;(1 &lt;&lt; 0)&t;/* Enable writing to flash */
multiline_comment|/*&n; * VERSATILE_INTREG&n; *     - used to acknowledge and control MMCI and UART interrupts &n; */
DECL|macro|VERSATILE_INTREG_WPROT
mdefine_line|#define VERSATILE_INTREG_WPROT        0x00    /* MMC protection status (no interrupt generated) */
DECL|macro|VERSATILE_INTREG_RI0
mdefine_line|#define VERSATILE_INTREG_RI0          0x01    /* Ring indicator UART0 is asserted,              */
DECL|macro|VERSATILE_INTREG_CARDIN
mdefine_line|#define VERSATILE_INTREG_CARDIN       0x08    /* MMCI card in detect                            */
multiline_comment|/* write 1 to acknowledge and clear               */
DECL|macro|VERSATILE_INTREG_RI1
mdefine_line|#define VERSATILE_INTREG_RI1          0x02    /* Ring indicator UART1 is asserted,              */
DECL|macro|VERSATILE_INTREG_CARDINSERT
mdefine_line|#define VERSATILE_INTREG_CARDINSERT   0x03    /* Signal insertion of MMC card                   */
multiline_comment|/*&n; * VERSATILE peripheral addresses&n; */
DECL|macro|VERSATILE_PCI_CORE_BASE
mdefine_line|#define VERSATILE_PCI_CORE_BASE        0x10001000&t;/* PCI core control */
DECL|macro|VERSATILE_I2C_BASE
mdefine_line|#define VERSATILE_I2C_BASE             0x10002000&t;/* I2C control */
DECL|macro|VERSATILE_SIC_BASE
mdefine_line|#define VERSATILE_SIC_BASE             0x10003000&t;/* Secondary interrupt controller */
DECL|macro|VERSATILE_AACI_BASE
mdefine_line|#define VERSATILE_AACI_BASE            0x10004000&t;/* Audio */
DECL|macro|VERSATILE_MMCI0_BASE
mdefine_line|#define VERSATILE_MMCI0_BASE           0x10005000&t;/* MMC interface */
DECL|macro|VERSATILE_KMI0_BASE
mdefine_line|#define VERSATILE_KMI0_BASE            0x10006000&t;/* KMI interface */
DECL|macro|VERSATILE_KMI1_BASE
mdefine_line|#define VERSATILE_KMI1_BASE            0x10007000&t;/* KMI 2nd interface */
DECL|macro|VERSATILE_CHAR_LCD_BASE
mdefine_line|#define VERSATILE_CHAR_LCD_BASE        0x10008000&t;/* Character LCD */
DECL|macro|VERSATILE_UART3_BASE
mdefine_line|#define VERSATILE_UART3_BASE           0x10009000&t;/* UART 3 */
DECL|macro|VERSATILE_SCI1_BASE
mdefine_line|#define VERSATILE_SCI1_BASE            0x1000A000
DECL|macro|VERSATILE_MMCI1_BASE
mdefine_line|#define VERSATILE_MMCI1_BASE           0x1000B000    /* MMC Interface */
multiline_comment|/* 0x1000C000 - 0x1000CFFF = reserved */
DECL|macro|VERSATILE_ETH_BASE
mdefine_line|#define VERSATILE_ETH_BASE             0x10010000&t;/* Ethernet */
DECL|macro|VERSATILE_USB_BASE
mdefine_line|#define VERSATILE_USB_BASE             0x10020000&t;/* USB */
multiline_comment|/* 0x10030000 - 0x100FFFFF = reserved */
DECL|macro|VERSATILE_SMC_BASE
mdefine_line|#define VERSATILE_SMC_BASE             0x10100000&t;/* SMC */
DECL|macro|VERSATILE_MPMC_BASE
mdefine_line|#define VERSATILE_MPMC_BASE            0x10110000&t;/* MPMC */
DECL|macro|VERSATILE_CLCD_BASE
mdefine_line|#define VERSATILE_CLCD_BASE            0x10120000&t;/* CLCD */
DECL|macro|VERSATILE_DMAC_BASE
mdefine_line|#define VERSATILE_DMAC_BASE            0x10130000&t;/* DMA controller */
DECL|macro|VERSATILE_VIC_BASE
mdefine_line|#define VERSATILE_VIC_BASE             0x10140000&t;/* Vectored interrupt controller */
DECL|macro|VERSATILE_PERIPH_BASE
mdefine_line|#define VERSATILE_PERIPH_BASE          0x10150000    /* off-chip peripherals alias from */
multiline_comment|/* 0x10000000 - 0x100FFFFF */
DECL|macro|VERSATILE_AHBM_BASE
mdefine_line|#define VERSATILE_AHBM_BASE            0x101D0000&t;/* AHB monitor */
DECL|macro|VERSATILE_SCTL_BASE
mdefine_line|#define VERSATILE_SCTL_BASE            0x101E0000&t;/* System controller */
DECL|macro|VERSATILE_WATCHDOG_BASE
mdefine_line|#define VERSATILE_WATCHDOG_BASE        0x101E1000&t;/* Watchdog */
DECL|macro|VERSATILE_TIMER0_1_BASE
mdefine_line|#define VERSATILE_TIMER0_1_BASE        0x101E2000&t;/* Timer 0 and 1 */
DECL|macro|VERSATILE_TIMER2_3_BASE
mdefine_line|#define VERSATILE_TIMER2_3_BASE        0x101E3000&t;/* Timer 2 and 3 */
DECL|macro|VERSATILE_GPIO0_BASE
mdefine_line|#define VERSATILE_GPIO0_BASE           0x101E4000&t;/* GPIO port 0 */
DECL|macro|VERSATILE_GPIO1_BASE
mdefine_line|#define VERSATILE_GPIO1_BASE           0x101E5000    /* GPIO port 1 */
DECL|macro|VERSATILE_GPIO2_BASE
mdefine_line|#define VERSATILE_GPIO2_BASE           0x101E6000&t;/* GPIO port 2 */
DECL|macro|VERSATILE_GPIO3_BASE
mdefine_line|#define VERSATILE_GPIO3_BASE           0x101E7000&t;/* GPIO port 3 */
DECL|macro|VERSATILE_RTC_BASE
mdefine_line|#define VERSATILE_RTC_BASE             0x101E8000&t;/* Real Time Clock */
multiline_comment|/* 0x101E9000 - reserved */
DECL|macro|VERSATILE_SCI_BASE
mdefine_line|#define VERSATILE_SCI_BASE             0x101F0000&t;/* Smart card controller */
DECL|macro|VERSATILE_UART0_BASE
mdefine_line|#define VERSATILE_UART0_BASE           0x101F1000&t;/* Uart 0 */
DECL|macro|VERSATILE_UART1_BASE
mdefine_line|#define VERSATILE_UART1_BASE           0x101F2000&t;/* Uart 1 */
DECL|macro|VERSATILE_UART2_BASE
mdefine_line|#define VERSATILE_UART2_BASE           0x101F3000&t;/* Uart 2 */
DECL|macro|VERSATILE_SSP_BASE
mdefine_line|#define VERSATILE_SSP_BASE             0x101F4000&t;/* Synchronous Serial Port */
DECL|macro|VERSATILE_SSMC_BASE
mdefine_line|#define VERSATILE_SSMC_BASE            0x20000000&t;/* SSMC */
DECL|macro|VERSATILE_IB2_BASE
mdefine_line|#define VERSATILE_IB2_BASE             0x24000000&t;/* IB2 module */
DECL|macro|VERSATILE_MBX_BASE
mdefine_line|#define VERSATILE_MBX_BASE             0x40000000&t;/* MBX */
DECL|macro|VERSATILE_PCI_BASE
mdefine_line|#define VERSATILE_PCI_BASE             0x41000000&t;/* PCI Interface */
DECL|macro|VERSATILE_SDRAM67_BASE
mdefine_line|#define VERSATILE_SDRAM67_BASE         0x70000000&t;/* SDRAM banks 6 and 7 */
DECL|macro|VERSATILE_LT_BASE
mdefine_line|#define VERSATILE_LT_BASE              0x80000000&t;/* Logic Tile expansion */
multiline_comment|/*&n; * Disk on Chip&n; */
DECL|macro|VERSATILE_DOC_BASE
mdefine_line|#define VERSATILE_DOC_BASE             0x2C000000
DECL|macro|VERSATILE_DOC_SIZE
mdefine_line|#define VERSATILE_DOC_SIZE             (16 &lt;&lt; 20)
DECL|macro|VERSATILE_DOC_PAGE_SIZE
mdefine_line|#define VERSATILE_DOC_PAGE_SIZE        512
DECL|macro|VERSATILE_DOC_TOTAL_PAGES
mdefine_line|#define VERSATILE_DOC_TOTAL_PAGES     (DOC_SIZE / PAGE_SIZE)
DECL|macro|ERASE_UNIT_PAGES
mdefine_line|#define ERASE_UNIT_PAGES    32
DECL|macro|START_PAGE
mdefine_line|#define START_PAGE          0x80
multiline_comment|/* &n; *  LED settings, bits [7:0]&n; */
DECL|macro|VERSATILE_SYS_LED0
mdefine_line|#define VERSATILE_SYS_LED0             (1 &lt;&lt; 0)
DECL|macro|VERSATILE_SYS_LED1
mdefine_line|#define VERSATILE_SYS_LED1             (1 &lt;&lt; 1)
DECL|macro|VERSATILE_SYS_LED2
mdefine_line|#define VERSATILE_SYS_LED2             (1 &lt;&lt; 2)
DECL|macro|VERSATILE_SYS_LED3
mdefine_line|#define VERSATILE_SYS_LED3             (1 &lt;&lt; 3)
DECL|macro|VERSATILE_SYS_LED4
mdefine_line|#define VERSATILE_SYS_LED4             (1 &lt;&lt; 4)
DECL|macro|VERSATILE_SYS_LED5
mdefine_line|#define VERSATILE_SYS_LED5             (1 &lt;&lt; 5)
DECL|macro|VERSATILE_SYS_LED6
mdefine_line|#define VERSATILE_SYS_LED6             (1 &lt;&lt; 6)
DECL|macro|VERSATILE_SYS_LED7
mdefine_line|#define VERSATILE_SYS_LED7             (1 &lt;&lt; 7)
DECL|macro|ALL_LEDS
mdefine_line|#define ALL_LEDS                  0xFF
DECL|macro|LED_BANK
mdefine_line|#define LED_BANK                  VERSATILE_SYS_LED
multiline_comment|/* &n; * Control registers&n; */
DECL|macro|VERSATILE_IDFIELD_OFFSET
mdefine_line|#define VERSATILE_IDFIELD_OFFSET&t;0x0&t;/* Versatile build information */
DECL|macro|VERSATILE_FLASHPROG_OFFSET
mdefine_line|#define VERSATILE_FLASHPROG_OFFSET&t;0x4&t;/* Flash devices */
DECL|macro|VERSATILE_INTREG_OFFSET
mdefine_line|#define VERSATILE_INTREG_OFFSET&t;&t;0x8&t;/* Interrupt control */
DECL|macro|VERSATILE_DECODE_OFFSET
mdefine_line|#define VERSATILE_DECODE_OFFSET&t;&t;0xC&t;/* Fitted logic modules */
multiline_comment|/* ------------------------------------------------------------------------&n; *  Versatile Interrupt Controller - control registers&n; * ------------------------------------------------------------------------&n; * &n; *  Offsets from interrupt controller base &n; * &n; *  System Controller interrupt controller base is&n; * &n; * &t;VERSATILE_IC_BASE&n; * &n; *  Core Module interrupt controller base is&n; * &n; * &t;VERSATILE_SYS_IC &n; * &n; */
DECL|macro|VIC_IRQ_STATUS
mdefine_line|#define VIC_IRQ_STATUS                  0
DECL|macro|VIC_FIQ_STATUS
mdefine_line|#define VIC_FIQ_STATUS                  0x04
DECL|macro|VIC_IRQ_RAW_STATUS
mdefine_line|#define VIC_IRQ_RAW_STATUS              0x08
DECL|macro|VIC_INT_SELECT
mdefine_line|#define VIC_INT_SELECT                  0x0C&t;/* 1 = FIQ, 0 = IRQ */
DECL|macro|VIC_IRQ_ENABLE
mdefine_line|#define VIC_IRQ_ENABLE                  0x10&t;/* 1 = enable, 0 = disable */
DECL|macro|VIC_IRQ_ENABLE_CLEAR
mdefine_line|#define VIC_IRQ_ENABLE_CLEAR            0x14
DECL|macro|VIC_IRQ_SOFT
mdefine_line|#define VIC_IRQ_SOFT                    0x18
DECL|macro|VIC_IRQ_SOFT_CLEAR
mdefine_line|#define VIC_IRQ_SOFT_CLEAR              0x1C
DECL|macro|VIC_PROTECT
mdefine_line|#define VIC_PROTECT                     0x20
DECL|macro|VIC_VECT_ADDR
mdefine_line|#define VIC_VECT_ADDR                   0x30
DECL|macro|VIC_DEF_VECT_ADDR
mdefine_line|#define VIC_DEF_VECT_ADDR               0x34
DECL|macro|VIC_VECT_ADDR0
mdefine_line|#define VIC_VECT_ADDR0                  0x100&t;/* 0 to 15 */
DECL|macro|VIC_VECT_CNTL0
mdefine_line|#define VIC_VECT_CNTL0                  0x200&t;/* 0 to 15 */
DECL|macro|VIC_ITCR
mdefine_line|#define VIC_ITCR                        0x300   /* VIC test control register */
DECL|macro|VIC_FIQ_RAW_STATUS
mdefine_line|#define VIC_FIQ_RAW_STATUS              0x08
DECL|macro|VIC_FIQ_ENABLE
mdefine_line|#define VIC_FIQ_ENABLE                  0x10&t;/* 1 = enable, 0 = disable */
DECL|macro|VIC_FIQ_ENABLE_CLEAR
mdefine_line|#define VIC_FIQ_ENABLE_CLEAR            0x14
DECL|macro|VIC_FIQ_SOFT
mdefine_line|#define VIC_FIQ_SOFT                    0x18
DECL|macro|VIC_FIQ_SOFT_CLEAR
mdefine_line|#define VIC_FIQ_SOFT_CLEAR              0x1C
DECL|macro|SIC_IRQ_STATUS
mdefine_line|#define SIC_IRQ_STATUS                  0
DECL|macro|SIC_IRQ_RAW_STATUS
mdefine_line|#define SIC_IRQ_RAW_STATUS              0x04
DECL|macro|SIC_IRQ_ENABLE
mdefine_line|#define SIC_IRQ_ENABLE                  0x08
DECL|macro|SIC_IRQ_ENABLE_SET
mdefine_line|#define SIC_IRQ_ENABLE_SET              0x08
DECL|macro|SIC_IRQ_ENABLE_CLEAR
mdefine_line|#define SIC_IRQ_ENABLE_CLEAR            0x0C
DECL|macro|SIC_INT_SOFT_SET
mdefine_line|#define SIC_INT_SOFT_SET                0x10
DECL|macro|SIC_INT_SOFT_CLEAR
mdefine_line|#define SIC_INT_SOFT_CLEAR              0x14
DECL|macro|SIC_INT_PIC_ENABLE
mdefine_line|#define SIC_INT_PIC_ENABLE              0x20&t;/* read status of pass through mask */
DECL|macro|SIC_INT_PIC_ENABLES
mdefine_line|#define SIC_INT_PIC_ENABLES             0x20&t;/* set interrupt pass through bits */
DECL|macro|SIC_INT_PIC_ENABLEC
mdefine_line|#define SIC_INT_PIC_ENABLEC             0x24&t;/* Clear interrupt pass through bits */
DECL|macro|VICVectCntl_Enable
mdefine_line|#define VICVectCntl_Enable&t;&t;(1 &lt;&lt; 5)
multiline_comment|/* ------------------------------------------------------------------------&n; *  Interrupts - bit assignment (primary)&n; * ------------------------------------------------------------------------&n; */
DECL|macro|INT_WDOGINT
mdefine_line|#define INT_WDOGINT                     0&t;/* Watchdog timer */
DECL|macro|INT_SOFTINT
mdefine_line|#define INT_SOFTINT                     1&t;/* Software interrupt */
DECL|macro|INT_COMMRx
mdefine_line|#define INT_COMMRx                      2&t;/* Debug Comm Rx interrupt */
DECL|macro|INT_COMMTx
mdefine_line|#define INT_COMMTx                      3&t;/* Debug Comm Tx interrupt */
DECL|macro|INT_TIMERINT0_1
mdefine_line|#define INT_TIMERINT0_1                 4&t;/* Timer 0 and 1 */
DECL|macro|INT_TIMERINT2_3
mdefine_line|#define INT_TIMERINT2_3                 5&t;/* Timer 2 and 3 */
DECL|macro|INT_GPIOINT0
mdefine_line|#define INT_GPIOINT0                    6&t;/* GPIO 0 */
DECL|macro|INT_GPIOINT1
mdefine_line|#define INT_GPIOINT1                    7&t;/* GPIO 1 */
DECL|macro|INT_GPIOINT2
mdefine_line|#define INT_GPIOINT2                    8&t;/* GPIO 2 */
DECL|macro|INT_GPIOINT3
mdefine_line|#define INT_GPIOINT3                    9&t;/* GPIO 3 */
DECL|macro|INT_RTCINT
mdefine_line|#define INT_RTCINT                      10&t;/* Real Time Clock */
DECL|macro|INT_SSPINT
mdefine_line|#define INT_SSPINT                      11&t;/* Synchronous Serial Port */
DECL|macro|INT_UARTINT0
mdefine_line|#define INT_UARTINT0                    12&t;/* UART 0 on development chip */
DECL|macro|INT_UARTINT1
mdefine_line|#define INT_UARTINT1                    13&t;/* UART 1 on development chip */
DECL|macro|INT_UARTINT2
mdefine_line|#define INT_UARTINT2                    14&t;/* UART 2 on development chip */
DECL|macro|INT_SCIINT
mdefine_line|#define INT_SCIINT                      15&t;/* Smart Card Interface */
DECL|macro|INT_CLCDINT
mdefine_line|#define INT_CLCDINT                     16&t;/* CLCD controller */
DECL|macro|INT_DMAINT
mdefine_line|#define INT_DMAINT                      17&t;/* DMA controller */
DECL|macro|INT_PWRFAILINT
mdefine_line|#define INT_PWRFAILINT                  18&t;/* Power failure */
DECL|macro|INT_MBXINT
mdefine_line|#define INT_MBXINT                      19&t;/* Graphics processor */
DECL|macro|INT_GNDINT
mdefine_line|#define INT_GNDINT                      20&t;/* Reserved */
multiline_comment|/* External interrupt signals from logic tiles or secondary controller */
DECL|macro|INT_VICSOURCE21
mdefine_line|#define INT_VICSOURCE21                 21&t;/* Disk on Chip */
DECL|macro|INT_VICSOURCE22
mdefine_line|#define INT_VICSOURCE22                 22&t;/* MCI0A */
DECL|macro|INT_VICSOURCE23
mdefine_line|#define INT_VICSOURCE23                 23&t;/* MCI1A */
DECL|macro|INT_VICSOURCE24
mdefine_line|#define INT_VICSOURCE24                 24&t;/* AACI */
DECL|macro|INT_VICSOURCE25
mdefine_line|#define INT_VICSOURCE25                 25&t;/* Ethernet */
DECL|macro|INT_VICSOURCE26
mdefine_line|#define INT_VICSOURCE26                 26&t;/* USB */
DECL|macro|INT_VICSOURCE27
mdefine_line|#define INT_VICSOURCE27                 27&t;/* PCI 0 */
DECL|macro|INT_VICSOURCE28
mdefine_line|#define INT_VICSOURCE28                 28&t;/* PCI 1 */
DECL|macro|INT_VICSOURCE29
mdefine_line|#define INT_VICSOURCE29                 29&t;/* PCI 2 */
DECL|macro|INT_VICSOURCE30
mdefine_line|#define INT_VICSOURCE30                 30&t;/* PCI 3 */
DECL|macro|INT_VICSOURCE31
mdefine_line|#define INT_VICSOURCE31                 31&t;/* SIC source */
multiline_comment|/* &n; *  Interrupt bit positions&n; * &n; */
DECL|macro|INTMASK_WDOGINT
mdefine_line|#define INTMASK_WDOGINT                 (1 &lt;&lt; INT_WDOGINT)
DECL|macro|INTMASK_SOFTINT
mdefine_line|#define INTMASK_SOFTINT                 (1 &lt;&lt; INT_SOFTINT)
DECL|macro|INTMASK_COMMRx
mdefine_line|#define INTMASK_COMMRx                  (1 &lt;&lt; INT_COMMRx)
DECL|macro|INTMASK_COMMTx
mdefine_line|#define INTMASK_COMMTx                  (1 &lt;&lt; INT_COMMTx)
DECL|macro|INTMASK_TIMERINT0_1
mdefine_line|#define INTMASK_TIMERINT0_1             (1 &lt;&lt; INT_TIMERINT0_1)
DECL|macro|INTMASK_TIMERINT2_3
mdefine_line|#define INTMASK_TIMERINT2_3             (1 &lt;&lt; INT_TIMERINT2_3)
DECL|macro|INTMASK_GPIOINT0
mdefine_line|#define INTMASK_GPIOINT0                (1 &lt;&lt; INT_GPIOINT0)
DECL|macro|INTMASK_GPIOINT1
mdefine_line|#define INTMASK_GPIOINT1                (1 &lt;&lt; INT_GPIOINT1)
DECL|macro|INTMASK_GPIOINT2
mdefine_line|#define INTMASK_GPIOINT2                (1 &lt;&lt; INT_GPIOINT2)
DECL|macro|INTMASK_GPIOINT3
mdefine_line|#define INTMASK_GPIOINT3                (1 &lt;&lt; INT_GPIOINT3)
DECL|macro|INTMASK_RTCINT
mdefine_line|#define INTMASK_RTCINT                  (1 &lt;&lt; INT_RTCINT)
DECL|macro|INTMASK_SSPINT
mdefine_line|#define INTMASK_SSPINT                  (1 &lt;&lt; INT_SSPINT)
DECL|macro|INTMASK_UARTINT0
mdefine_line|#define INTMASK_UARTINT0                (1 &lt;&lt; INT_UARTINT0)
DECL|macro|INTMASK_UARTINT1
mdefine_line|#define INTMASK_UARTINT1                (1 &lt;&lt; INT_UARTINT1)
DECL|macro|INTMASK_UARTINT2
mdefine_line|#define INTMASK_UARTINT2                (1 &lt;&lt; INT_UARTINT2)
DECL|macro|INTMASK_SCIINT
mdefine_line|#define INTMASK_SCIINT                  (1 &lt;&lt; INT_SCIINT)
DECL|macro|INTMASK_CLCDINT
mdefine_line|#define INTMASK_CLCDINT                 (1 &lt;&lt; INT_CLCDINT)
DECL|macro|INTMASK_DMAINT
mdefine_line|#define INTMASK_DMAINT                  (1 &lt;&lt; INT_DMAINT)
DECL|macro|INTMASK_PWRFAILINT
mdefine_line|#define INTMASK_PWRFAILINT              (1 &lt;&lt; INT_PWRFAILINT)
DECL|macro|INTMASK_MBXINT
mdefine_line|#define INTMASK_MBXINT                  (1 &lt;&lt; INT_MBXINT)
DECL|macro|INTMASK_GNDINT
mdefine_line|#define INTMASK_GNDINT                  (1 &lt;&lt; INT_GNDINT)
DECL|macro|INTMASK_VICSOURCE21
mdefine_line|#define INTMASK_VICSOURCE21             (1 &lt;&lt; INT_VICSOURCE21)
DECL|macro|INTMASK_VICSOURCE22
mdefine_line|#define INTMASK_VICSOURCE22             (1 &lt;&lt; INT_VICSOURCE22)
DECL|macro|INTMASK_VICSOURCE23
mdefine_line|#define INTMASK_VICSOURCE23             (1 &lt;&lt; INT_VICSOURCE23)
DECL|macro|INTMASK_VICSOURCE24
mdefine_line|#define INTMASK_VICSOURCE24             (1 &lt;&lt; INT_VICSOURCE24)
DECL|macro|INTMASK_VICSOURCE25
mdefine_line|#define INTMASK_VICSOURCE25             (1 &lt;&lt; INT_VICSOURCE25)
DECL|macro|INTMASK_VICSOURCE26
mdefine_line|#define INTMASK_VICSOURCE26             (1 &lt;&lt; INT_VICSOURCE26)
DECL|macro|INTMASK_VICSOURCE27
mdefine_line|#define INTMASK_VICSOURCE27             (1 &lt;&lt; INT_VICSOURCE27)
DECL|macro|INTMASK_VICSOURCE28
mdefine_line|#define INTMASK_VICSOURCE28             (1 &lt;&lt; INT_VICSOURCE28)
DECL|macro|INTMASK_VICSOURCE29
mdefine_line|#define INTMASK_VICSOURCE29             (1 &lt;&lt; INT_VICSOURCE29)
DECL|macro|INTMASK_VICSOURCE30
mdefine_line|#define INTMASK_VICSOURCE30             (1 &lt;&lt; INT_VICSOURCE30)
DECL|macro|INTMASK_VICSOURCE31
mdefine_line|#define INTMASK_VICSOURCE31             (1 &lt;&lt; INT_VICSOURCE31)
DECL|macro|VERSATILE_SC_VALID_INT
mdefine_line|#define VERSATILE_SC_VALID_INT               0x003FFFFF
DECL|macro|MAXIRQNUM
mdefine_line|#define MAXIRQNUM                       31
DECL|macro|MAXFIQNUM
mdefine_line|#define MAXFIQNUM                       31
DECL|macro|MAXSWINUM
mdefine_line|#define MAXSWINUM                       31
multiline_comment|/* ------------------------------------------------------------------------&n; *  Interrupts - bit assignment (secondary)&n; * ------------------------------------------------------------------------&n; */
DECL|macro|SIC_INT_MMCI0B
mdefine_line|#define SIC_INT_MMCI0B                  1&t;/* Multimedia Card 0B */
DECL|macro|SIC_INT_MMCI1B
mdefine_line|#define SIC_INT_MMCI1B                  2&t;/* Multimedia Card 1B */
DECL|macro|SIC_INT_KMI0
mdefine_line|#define SIC_INT_KMI0                    3&t;/* Keyboard/Mouse port 0 */
DECL|macro|SIC_INT_KMI1
mdefine_line|#define SIC_INT_KMI1                    4&t;/* Keyboard/Mouse port 1 */
DECL|macro|SIC_INT_SCI3
mdefine_line|#define SIC_INT_SCI3                    5&t;/* Smart Card interface */
DECL|macro|SIC_INT_UART3
mdefine_line|#define SIC_INT_UART3                   6&t;/* UART 3 empty or data available */
DECL|macro|SIC_INT_CLCD
mdefine_line|#define SIC_INT_CLCD                    7&t;/* Character LCD */
DECL|macro|SIC_INT_TOUCH
mdefine_line|#define SIC_INT_TOUCH                   8&t;/* Touchscreen */
DECL|macro|SIC_INT_KEYPAD
mdefine_line|#define SIC_INT_KEYPAD                  9&t;/* Key pressed on display keypad */
multiline_comment|/* 10:20 - reserved */
DECL|macro|SIC_INT_DoC
mdefine_line|#define SIC_INT_DoC                     21&t;/* Disk on Chip memory controller */
DECL|macro|SIC_INT_MMCI0A
mdefine_line|#define SIC_INT_MMCI0A                  22&t;/* MMC 0A */
DECL|macro|SIC_INT_MMCI1A
mdefine_line|#define SIC_INT_MMCI1A                  23&t;/* MMC 1A */
DECL|macro|SIC_INT_AACI
mdefine_line|#define SIC_INT_AACI                    24&t;/* Audio Codec */
DECL|macro|SIC_INT_ETH
mdefine_line|#define SIC_INT_ETH                     25&t;/* Ethernet controller */
DECL|macro|SIC_INT_USB
mdefine_line|#define SIC_INT_USB                     26&t;/* USB controller */
DECL|macro|SIC_INT_PCI0
mdefine_line|#define SIC_INT_PCI0                    27
DECL|macro|SIC_INT_PCI1
mdefine_line|#define SIC_INT_PCI1                    28
DECL|macro|SIC_INT_PCI2
mdefine_line|#define SIC_INT_PCI2                    29
DECL|macro|SIC_INT_PCI3
mdefine_line|#define SIC_INT_PCI3                    30
DECL|macro|SIC_INTMASK_MMCI0B
mdefine_line|#define SIC_INTMASK_MMCI0B              (1 &lt;&lt; SIC_INT_MMCI0B)
DECL|macro|SIC_INTMASK_MMCI1B
mdefine_line|#define SIC_INTMASK_MMCI1B              (1 &lt;&lt; SIC_INT_MMCI1B)
DECL|macro|SIC_INTMASK_KMI0
mdefine_line|#define SIC_INTMASK_KMI0                (1 &lt;&lt; SIC_INT_KMI0)
DECL|macro|SIC_INTMASK_KMI1
mdefine_line|#define SIC_INTMASK_KMI1                (1 &lt;&lt; SIC_INT_KMI1)
DECL|macro|SIC_INTMASK_SCI3
mdefine_line|#define SIC_INTMASK_SCI3                (1 &lt;&lt; SIC_INT_SCI3)
DECL|macro|SIC_INTMASK_UART3
mdefine_line|#define SIC_INTMASK_UART3               (1 &lt;&lt; SIC_INT_UART3)
DECL|macro|SIC_INTMASK_CLCD
mdefine_line|#define SIC_INTMASK_CLCD                (1 &lt;&lt; SIC_INT_CLCD)
DECL|macro|SIC_INTMASK_TOUCH
mdefine_line|#define SIC_INTMASK_TOUCH               (1 &lt;&lt; SIC_INT_TOUCH)
DECL|macro|SIC_INTMASK_KEYPAD
mdefine_line|#define SIC_INTMASK_KEYPAD              (1 &lt;&lt; SIC_INT_KEYPAD)
DECL|macro|SIC_INTMASK_DoC
mdefine_line|#define SIC_INTMASK_DoC                 (1 &lt;&lt; SIC_INT_DoC)
DECL|macro|SIC_INTMASK_MMCI0A
mdefine_line|#define SIC_INTMASK_MMCI0A              (1 &lt;&lt; SIC_INT_MMCI0A)
DECL|macro|SIC_INTMASK_MMCI1A
mdefine_line|#define SIC_INTMASK_MMCI1A              (1 &lt;&lt; SIC_INT_MMCI1A)
DECL|macro|SIC_INTMASK_AACI
mdefine_line|#define SIC_INTMASK_AACI                (1 &lt;&lt; SIC_INT_AACI)
DECL|macro|SIC_INTMASK_ETH
mdefine_line|#define SIC_INTMASK_ETH                 (1 &lt;&lt; SIC_INT_ETH)
DECL|macro|SIC_INTMASK_USB
mdefine_line|#define SIC_INTMASK_USB                 (1 &lt;&lt; SIC_INT_USB)
DECL|macro|SIC_INTMASK_PCI0
mdefine_line|#define SIC_INTMASK_PCI0                (1 &lt;&lt; SIC_INT_PCI0)
DECL|macro|SIC_INTMASK_PCI1
mdefine_line|#define SIC_INTMASK_PCI1                (1 &lt;&lt; SIC_INT_PCI1)
DECL|macro|SIC_INTMASK_PCI2
mdefine_line|#define SIC_INTMASK_PCI2                (1 &lt;&lt; SIC_INT_PCI2)
DECL|macro|SIC_INTMASK_PCI3
mdefine_line|#define SIC_INTMASK_PCI3                (1 &lt;&lt; SIC_INT_PCI3)
multiline_comment|/* &n; *  Application Flash&n; * &n; */
DECL|macro|FLASH_BASE
mdefine_line|#define FLASH_BASE                      VERSATILE_FLASH_BASE
DECL|macro|FLASH_SIZE
mdefine_line|#define FLASH_SIZE                      VERSATILE_FLASH_SIZE
DECL|macro|FLASH_END
mdefine_line|#define FLASH_END                       (FLASH_BASE + FLASH_SIZE - 1)
DECL|macro|FLASH_BLOCK_SIZE
mdefine_line|#define FLASH_BLOCK_SIZE                SZ_128K
multiline_comment|/* &n; *  Boot Flash&n; * &n; */
DECL|macro|EPROM_BASE
mdefine_line|#define EPROM_BASE                      VERSATILE_BOOT_ROM_HI
DECL|macro|EPROM_SIZE
mdefine_line|#define EPROM_SIZE                      VERSATILE_BOOT_ROM_SIZE
DECL|macro|EPROM_END
mdefine_line|#define EPROM_END                       (EPROM_BASE + EPROM_SIZE - 1)
multiline_comment|/* &n; *  Clean base - dummy&n; * &n; */
DECL|macro|CLEAN_BASE
mdefine_line|#define CLEAN_BASE                      EPROM_BASE
multiline_comment|/*&n; * System controller bit assignment&n; */
DECL|macro|VERSATILE_REFCLK
mdefine_line|#define VERSATILE_REFCLK&t;0
DECL|macro|VERSATILE_TIMCLK
mdefine_line|#define VERSATILE_TIMCLK&t;1
DECL|macro|VERSATILE_TIMER1_EnSel
mdefine_line|#define VERSATILE_TIMER1_EnSel&t;15
DECL|macro|VERSATILE_TIMER2_EnSel
mdefine_line|#define VERSATILE_TIMER2_EnSel&t;17
DECL|macro|VERSATILE_TIMER3_EnSel
mdefine_line|#define VERSATILE_TIMER3_EnSel&t;19
DECL|macro|VERSATILE_TIMER4_EnSel
mdefine_line|#define VERSATILE_TIMER4_EnSel&t;21
DECL|macro|MAX_TIMER
mdefine_line|#define MAX_TIMER                       2
DECL|macro|MAX_PERIOD
mdefine_line|#define MAX_PERIOD                      699050
DECL|macro|TICKS_PER_uSEC
mdefine_line|#define TICKS_PER_uSEC                  1
multiline_comment|/* &n; *  These are useconds NOT ticks.  &n; * &n; */
DECL|macro|mSEC_1
mdefine_line|#define mSEC_1                          1000
DECL|macro|mSEC_5
mdefine_line|#define mSEC_5                          (mSEC_1 * 5)
DECL|macro|mSEC_10
mdefine_line|#define mSEC_10                         (mSEC_1 * 10)
DECL|macro|mSEC_25
mdefine_line|#define mSEC_25                         (mSEC_1 * 25)
DECL|macro|SEC_1
mdefine_line|#define SEC_1                           (mSEC_1 * 1000)
DECL|macro|VERSATILE_CSR_BASE
mdefine_line|#define VERSATILE_CSR_BASE             0x10000000
DECL|macro|VERSATILE_CSR_SIZE
mdefine_line|#define VERSATILE_CSR_SIZE             0x10000000
macro_line|#ifdef CONFIG_MACH_VERSATILE_AB
multiline_comment|/*&n; * IB2 Versatile/AB expansion board definitions&n; */
DECL|macro|VERSATILE_IB2_CAMERA_BANK
mdefine_line|#define VERSATILE_IB2_CAMERA_BANK&t;0x24000000
DECL|macro|VERSATILE_IB2_KBD_DATAREG
mdefine_line|#define VERSATILE_IB2_KBD_DATAREG&t;0x25000000
DECL|macro|VERSATILE_IB2_IER
mdefine_line|#define VERSATILE_IB2_IER&t;&t;0x26000000&t;/* for VICINTSOURCE27 */
DECL|macro|VERSATILE_IB2_CTRL
mdefine_line|#define VERSATILE_IB2_CTRL&t;&t;0x27000000
DECL|macro|VERSATILE_IB2_STAT
mdefine_line|#define VERSATILE_IB2_STAT&t;&t;0x27000004
macro_line|#endif
macro_line|#endif
multiline_comment|/* &t;END */
eof
