multiline_comment|/*&n; *  linux/include/asm-arm/arch-pxa/lubbock.h&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Jun 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
DECL|macro|LUBBOCK_ETH_PHYS
mdefine_line|#define LUBBOCK_ETH_PHYS&t;PXA_CS3_PHYS
DECL|macro|LUBBOCK_FPGA_PHYS
mdefine_line|#define LUBBOCK_FPGA_PHYS&t;PXA_CS2_PHYS
DECL|macro|LUBBOCK_FPGA_VIRT
mdefine_line|#define LUBBOCK_FPGA_VIRT&t;(0xf0000000)
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
multiline_comment|/* FPGA register virtual addresses */
DECL|macro|LUB_WHOAMI
mdefine_line|#define LUB_WHOAMI&t;&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x000)
DECL|macro|LUB_HEXLED
mdefine_line|#define LUB_HEXLED&t;&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x010)
DECL|macro|LUB_DISC_BLNK_LED
mdefine_line|#define LUB_DISC_BLNK_LED&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x040)
DECL|macro|LUB_CONF_SWITCHES
mdefine_line|#define LUB_CONF_SWITCHES&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x050)
DECL|macro|LUB_USER_SWITCHES
mdefine_line|#define LUB_USER_SWITCHES&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x060)
DECL|macro|LUB_MISC_WR
mdefine_line|#define LUB_MISC_WR&t;&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x080)
DECL|macro|LUB_MISC_RD
mdefine_line|#define LUB_MISC_RD&t;&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x090)
DECL|macro|LUB_IRQ_MASK_EN
mdefine_line|#define LUB_IRQ_MASK_EN&t;&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x0c0)
DECL|macro|LUB_IRQ_SET_CLR
mdefine_line|#define LUB_IRQ_SET_CLR&t;&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x0d0)
DECL|macro|LUB_GP
mdefine_line|#define LUB_GP&t;&t;&t;__LUB_REG(LUBBOCK_FPGA_PHYS + 0x100)
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|lubbock_set_misc_wr
c_func
(paren
r_int
r_int
id|mask
comma
r_int
r_int
id|set
)paren
suffix:semicolon
macro_line|#endif
eof
