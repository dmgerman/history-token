multiline_comment|/*&n; * include/asm-arm/arch-ixp2000/ixdp2x00.h&n; *&n; * Register and other defines for IXDP2[48]00 platforms&n; *&n; * Original Author: Naeem Afzal &lt;naeem.m.afzal@intel.com&gt;&n; * Maintainer: Deepak Saxena &lt;dsaxena@plexity.net&gt;&n; *&n; * Copyright (C) 2002 Intel Corp.&n; * Copyright (C) 2003-2004 MontaVista Software, Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; */
macro_line|#ifndef _IXDP2X00_H_
DECL|macro|_IXDP2X00_H_
mdefine_line|#define _IXDP2X00_H_
multiline_comment|/*&n; * On board CPLD memory map&n; */
DECL|macro|IXDP2X00_PHYS_CPLD_BASE
mdefine_line|#define IXDP2X00_PHYS_CPLD_BASE&t;&t;0xc7000000
DECL|macro|IXDP2X00_VIRT_CPLD_BASE
mdefine_line|#define IXDP2X00_VIRT_CPLD_BASE&t;&t;0xfafff000
DECL|macro|IXDP2X00_CPLD_SIZE
mdefine_line|#define IXDP2X00_CPLD_SIZE&t;&t;0x00001000
DECL|macro|IXDP2X00_CPLD_REG
mdefine_line|#define IXDP2X00_CPLD_REG(x)  &t;&bslash;&n;&t;(volatile unsigned long *)(IXDP2X00_VIRT_CPLD_BASE | x)
multiline_comment|/*&n; * IXDP2400 CPLD registers&n; */
DECL|macro|IXDP2400_CPLD_SYSLED
mdefine_line|#define IXDP2400_CPLD_SYSLED&t;&t;IXDP2X00_CPLD_REG(0x0)  
DECL|macro|IXDP2400_CPLD_DISP_DATA
mdefine_line|#define IXDP2400_CPLD_DISP_DATA&t;&t;IXDP2X00_CPLD_REG(0x4)
DECL|macro|IXDP2400_CPLD_CLOCK_SPEED
mdefine_line|#define IXDP2400_CPLD_CLOCK_SPEED&t;IXDP2X00_CPLD_REG(0x8)
DECL|macro|IXDP2400_CPLD_INT_STAT
mdefine_line|#define IXDP2400_CPLD_INT_STAT&t;&t;IXDP2X00_CPLD_REG(0xc)
DECL|macro|IXDP2400_CPLD_REV
mdefine_line|#define IXDP2400_CPLD_REV&t;&t;IXDP2X00_CPLD_REG(0x10)
DECL|macro|IXDP2400_CPLD_SYS_CLK_M
mdefine_line|#define IXDP2400_CPLD_SYS_CLK_M&t;&t;IXDP2X00_CPLD_REG(0x14)
DECL|macro|IXDP2400_CPLD_SYS_CLK_N
mdefine_line|#define IXDP2400_CPLD_SYS_CLK_N&t;&t;IXDP2X00_CPLD_REG(0x18)
DECL|macro|IXDP2400_CPLD_INT_MASK
mdefine_line|#define IXDP2400_CPLD_INT_MASK&t;&t;IXDP2X00_CPLD_REG(0x48)
multiline_comment|/*&n; * IXDP2800 CPLD registers&n; */
DECL|macro|IXDP2800_CPLD_INT_STAT
mdefine_line|#define IXDP2800_CPLD_INT_STAT&t;&t;IXDP2X00_CPLD_REG(0x0)
DECL|macro|IXDP2800_CPLD_INT_MASK
mdefine_line|#define IXDP2800_CPLD_INT_MASK&t;&t;IXDP2X00_CPLD_REG(0x140)
DECL|macro|IXDP2X00_GPIO_I2C_ENABLE
mdefine_line|#define&t;IXDP2X00_GPIO_I2C_ENABLE&t;0x02
DECL|macro|IXDP2X00_GPIO_SCL
mdefine_line|#define&t;IXDP2X00_GPIO_SCL&t;&t;0x07
DECL|macro|IXDP2X00_GPIO_SDA
mdefine_line|#define&t;IXDP2X00_GPIO_SDA&t;&t;0x06
multiline_comment|/*&n; * PCI devfns for on-board devices. We need these to be able to&n; * properly translate IRQs and for device removal.&n; */
DECL|macro|IXDP2400_SLAVE_ENET_DEVFN
mdefine_line|#define&t;IXDP2400_SLAVE_ENET_DEVFN&t;0x18&t;/* Bus 1 */
DECL|macro|IXDP2400_MASTER_ENET_DEVFN
mdefine_line|#define&t;IXDP2400_MASTER_ENET_DEVFN&t;0x20&t;/* Bus 1 */
DECL|macro|IXDP2400_MEDIA_DEVFN
mdefine_line|#define&t;IXDP2400_MEDIA_DEVFN&t;&t;0x28&t;/* Bus 1 */
DECL|macro|IXDP2400_SWITCH_FABRIC_DEVFN
mdefine_line|#define&t;IXDP2400_SWITCH_FABRIC_DEVFN&t;0x30&t;/* Bus 1 */
DECL|macro|IXDP2800_SLAVE_ENET_DEVFN
mdefine_line|#define&t;IXDP2800_SLAVE_ENET_DEVFN&t;0x20&t;/* Bus 1 */
DECL|macro|IXDP2800_MASTER_ENET_DEVFN
mdefine_line|#define&t;IXDP2800_MASTER_ENET_DEVFN&t;0x18&t;/* Bus 1 */
DECL|macro|IXDP2800_SWITCH_FABRIC_DEVFN
mdefine_line|#define&t;IXDP2800_SWITCH_FABRIC_DEVFN&t;0x30&t;/* Bus 1 */
DECL|macro|IXDP2X00_P2P_DEVFN
mdefine_line|#define&t;IXDP2X00_P2P_DEVFN&t;&t;0x20&t;/* Bus 0 */
DECL|macro|IXDP2X00_21555_DEVFN
mdefine_line|#define&t;IXDP2X00_21555_DEVFN&t;&t;0x30&t;/* Bus 0 */
DECL|macro|IXDP2X00_SLAVE_NPU_DEVFN
mdefine_line|#define IXDP2X00_SLAVE_NPU_DEVFN&t;0x28&t;/* Bus 1 */
DECL|macro|IXDP2X00_PMC_DEVFN
mdefine_line|#define&t;IXDP2X00_PMC_DEVFN&t;&t;0x38&t;/* Bus 1 */
DECL|macro|IXDP2X00_MASTER_NPU_DEVFN
mdefine_line|#define IXDP2X00_MASTER_NPU_DEVFN&t;0x38&t;/* Bus 1 */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Master NPU will always have flash and be PCI master.&n; * Slave NPU may or may not have flash but will never be PCI master.&n; */
DECL|function|ixdp2x00_master_npu
r_static
r_inline
r_int
r_int
id|ixdp2x00_master_npu
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
id|ixp2000_has_flash
c_func
(paren
)paren
)paren
op_logical_and
(paren
id|ixp2000_is_pcimaster
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Helper functions used by ixdp2400 and ixdp2800 specific code&n; */
r_void
id|ixdp2x00_init_irq
c_func
(paren
r_volatile
r_int
r_int
op_star
comma
r_volatile
r_int
r_int
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|ixdp2x00_slave_pci_postinit
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ixdp2x00_init_machine
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ixdp2x00_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /*_IXDP2X00_H_ */
eof
