multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/lubbock.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|LUBBOCK_FPGA_PHYS
mdefine_line|#define LUBBOCK_FPGA_PHYS&t;PXA_CS2_PHYS
DECL|macro|LUBBOCK_FPGA_VIRT
mdefine_line|#define LUBBOCK_FPGA_VIRT&t;(0xf0000000)&t;/* phys 0x08000000 */
DECL|macro|LUBBOCK_ETH_BASE
mdefine_line|#define LUBBOCK_ETH_BASE&t;(0xf1000000)&t;/* phys 0x0c000000 */
DECL|macro|LUBBOCK_SA1111_BASE
mdefine_line|#define LUBBOCK_SA1111_BASE&t;(0xf4000000)&t;/* phys 0x10000000 */
DECL|macro|LUB_P2V
mdefine_line|#define LUB_P2V(x)&t;&t;((x) - LUBBOCK_FPGA_PHYS + LUBBOCK_FPGA_VIRT)
DECL|macro|LUB_V2P
mdefine_line|#define LUB_V2P(x)&t;&t;((x) - LUBBOCK_FPGA_VIRT + LUBBOCK_FPGA_PHYS)
macro_line|#ifndef __ASSEMBLY__
DECL|macro|__LUB_REG
macro_line|#  define __LUB_REG(x)&t;&t;(*((volatile unsigned long *)LUB_P2V(x)))
macro_line|#else
DECL|macro|__LUB_REG
macro_line|#  define __LUB_REG(x)&t;&t;LUB_P2V(x)
macro_line|#endif
multiline_comment|/* board level registers in the CPLD: (offsets from CPLD_BASE) */
DECL|macro|WHOAMI
mdefine_line|#define WHOAMI&t;&t;&t;0&t;
singleline_comment|// card ID&squot;s (see programmers manual)
DECL|macro|HEX_LED
mdefine_line|#define HEX_LED&t;&t;&t;0x10&t;
singleline_comment|// R/W access to 8 7 segment displays
DECL|macro|DISC_BLNK_LED
mdefine_line|#define DISC_BLNK_LED&t;&t;0x40 &t;
singleline_comment|// R/W [15-8] enables for hex leds, [7-0] discrete LEDs
DECL|macro|CONF_SWITCHES
mdefine_line|#define CONF_SWITCHES&t;&t;0x50&t;
singleline_comment|// RO [1] flash wrt prot, [0] 0= boot from rom, 1= flash
DECL|macro|USER_SWITCHES
mdefine_line|#define USER_SWITCHES&t;&t;0x60&t;
singleline_comment|// RO [15-8] dip switches, [7-0] 2 hex encoding switches
DECL|macro|MISC_WR
mdefine_line|#define MISC_WR&t;&t;&t;0x80&t;
singleline_comment|// R/W various system controls -see manual
DECL|macro|MISC_RD
mdefine_line|#define MISC_RD&t;&t;&t;0x90&t;
singleline_comment|// RO various system status bits -see manual
singleline_comment|//#define LUB_IRQ_MASK_EN&t;&t;0xC0    // R/W 0= mask, 1= enable of TS, codec, ethernet, USB, SA1111, and card det. irq&squot;s
singleline_comment|//#define LUB_IRQ_SET_CLR&t;&t;0xD0&t;// R/W 1= set, 0 = clear IRQ&squot;s from TS, codec, etc...
singleline_comment|//#define LUB_GP&t;&t;&t;0x100&t;// R/W [15-0] 16 bits of general purpose I/o for hacking
multiline_comment|/* FPGA register physical addresses */
DECL|macro|_LUB_WHOAMI
mdefine_line|#define _LUB_WHOAMI&t;&t;(LUBBOCK_FPGA_PHYS + 0x000)
DECL|macro|_LUB_HEXLED
mdefine_line|#define _LUB_HEXLED&t;&t;(LUBBOCK_FPGA_PHYS + 0x010)
DECL|macro|_LUB_DISC_BLNK_LED
mdefine_line|#define _LUB_DISC_BLNK_LED&t;(LUBBOCK_FPGA_PHYS + 0x040)
DECL|macro|_LUB_CONF_SWITCHES
mdefine_line|#define _LUB_CONF_SWITCHES&t;(LUBBOCK_FPGA_PHYS + 0x050)
DECL|macro|_LUB_USER_SWITCHES
mdefine_line|#define _LUB_USER_SWITCHES&t;(LUBBOCK_FPGA_PHYS + 0x060)
DECL|macro|_LUB_MISC_WR
mdefine_line|#define _LUB_MISC_WR&t;&t;(LUBBOCK_FPGA_PHYS + 0x080)
DECL|macro|_LUB_MISC_RD
mdefine_line|#define _LUB_MISC_RD&t;&t;(LUBBOCK_FPGA_PHYS + 0x090)
DECL|macro|_LUB_IRQ_MASK_EN
mdefine_line|#define _LUB_IRQ_MASK_EN&t;(LUBBOCK_FPGA_PHYS + 0x0C0)
DECL|macro|_LUB_IRQ_SET_CLR
mdefine_line|#define _LUB_IRQ_SET_CLR&t;(LUBBOCK_FPGA_PHYS + 0x0D0)
DECL|macro|_LUB_GP
mdefine_line|#define _LUB_GP&t;&t;&t;(LUBBOCK_FPGA_PHYS + 0x100)
multiline_comment|/* FPGA register virtual addresses */
DECL|macro|LUB_WHOAMI
mdefine_line|#define LUB_WHOAMI&t;&t;__LUB_REG(_LUB_WHOAMI)
DECL|macro|LUB_HEXLED
mdefine_line|#define LUB_HEXLED&t;&t;__LUB_REG(_LUB_HEXLED)
DECL|macro|LUB_DISC_BLNK_LED
mdefine_line|#define LUB_DISC_BLNK_LED&t;__LUB_REG(_LUB_DISC_BLNK_LED)
DECL|macro|LUB_CONF_SWITCHES
mdefine_line|#define LUB_CONF_SWITCHES&t;__LUB_REG(_LUB_CONF_SWITCHES)
DECL|macro|LUB_USER_SWITCHES
mdefine_line|#define LUB_USER_SWITCHES&t;__LUB_REG(_LUB_USER_SWITCHES)
DECL|macro|LUB_MISC_WR
mdefine_line|#define LUB_MISC_WR&t;&t;__LUB_REG(_LUB_MISC_WR)
DECL|macro|LUB_MISC_RD
mdefine_line|#define LUB_MISC_RD&t;&t;__LUB_REG(_LUB_MISC_RD)
DECL|macro|LUB_IRQ_MASK_EN
mdefine_line|#define LUB_IRQ_MASK_EN&t;&t;__LUB_REG(_LUB_IRQ_MASK_EN)
DECL|macro|LUB_IRQ_SET_CLR
mdefine_line|#define LUB_IRQ_SET_CLR&t;&t;__LUB_REG(_LUB_IRQ_SET_CLR)
DECL|macro|LUB_GP
mdefine_line|#define LUB_GP&t;&t;&t;__LUB_REG(_LUB_GP)
multiline_comment|/* GPIOs */
DECL|macro|GPIO_LUBBOCK_IRQ
mdefine_line|#define GPIO_LUBBOCK_IRQ&t;0
DECL|macro|IRQ_GPIO_LUBBOCK_IRQ
mdefine_line|#define IRQ_GPIO_LUBBOCK_IRQ&t;IRQ_GPIO0
multiline_comment|/*&n; * LED macros&n; */
DECL|macro|LEDS_BASE
mdefine_line|#define LEDS_BASE LUB_DISC_BLNK_LED
singleline_comment|// 8 discrete leds available for general use:
DECL|macro|D28
mdefine_line|#define D28&t;0x1
DECL|macro|D27
mdefine_line|#define D27&t;0x2
DECL|macro|D26
mdefine_line|#define D26&t;0x4
DECL|macro|D25
mdefine_line|#define D25&t;0x8
DECL|macro|D24
mdefine_line|#define D24&t;0x10
DECL|macro|D23
mdefine_line|#define D23&t;0x20
DECL|macro|D22
mdefine_line|#define D22&t;0x40
DECL|macro|D21
mdefine_line|#define D21&t;0x80
multiline_comment|/* Note: bits [15-8] are used to enable/blank the 8 7 segment hex displays so&n;*  be sure to not monkey with them here.&n;*/
DECL|macro|HEARTBEAT_LED
mdefine_line|#define HEARTBEAT_LED&t;D28
DECL|macro|SYS_BUSY_LED
mdefine_line|#define SYS_BUSY_LED    D27
DECL|macro|HEXLEDS_BASE
mdefine_line|#define HEXLEDS_BASE LUB_HEXLED
DECL|macro|HEARTBEAT_LED_ON
mdefine_line|#define HEARTBEAT_LED_ON  (LEDS_BASE &amp;= ~HEARTBEAT_LED)
DECL|macro|HEARTBEAT_LED_OFF
mdefine_line|#define HEARTBEAT_LED_OFF (LEDS_BASE |= HEARTBEAT_LED)
DECL|macro|SYS_BUSY_LED_OFF
mdefine_line|#define SYS_BUSY_LED_OFF  (LEDS_BASE |= SYS_BUSY_LED)
DECL|macro|SYS_BUSY_LED_ON
mdefine_line|#define SYS_BUSY_LED_ON   (LEDS_BASE &amp;= ~SYS_BUSY_LED)
singleline_comment|// use x = D26-D21 for these, please...
DECL|macro|DISCRETE_LED_ON
mdefine_line|#define DISCRETE_LED_ON(x) (LEDS_BASE &amp;= ~(x))
DECL|macro|DISCRETE_LED_OFF
mdefine_line|#define DISCRETE_LED_OFF(x) (LEDS_BASE |= (x))
macro_line|#ifndef __ASSEMBLY__
singleline_comment|//extern int hexled_val = 0;
macro_line|#endif
DECL|macro|BUMP_COUNTER
mdefine_line|#define BUMP_COUNTER (HEXLEDS_BASE = hexled_val++)
DECL|macro|DEC_COUNTER
mdefine_line|#define DEC_COUNTER (HEXLEDS_BASE = hexled_val--)
eof
