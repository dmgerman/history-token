multiline_comment|/*&n; * arch/ppc/platforms/stx8560_gp3.h&n; *&n; * STx GP3 board definitions&n; *&n; * Dan Malek (dan@embeddededge.com)&n; * Copyright 2004 Embedded Edge, LLC&n; *&n; * Ported to 2.6, Matt Porter &lt;mporter@kernel.crashing.org&gt;&n; * Copyright 2004-2005 MontaVista Software, Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __MACH_STX_GP3_H
DECL|macro|__MACH_STX_GP3_H
mdefine_line|#define __MACH_STX_GP3_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
DECL|macro|BOARD_CCSRBAR
mdefine_line|#define BOARD_CCSRBAR&t;&t;((uint)0xe0000000)
DECL|macro|CCSRBAR_SIZE
mdefine_line|#define CCSRBAR_SIZE&t;&t;((uint)1024*1024)
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;&t;(CCSRBAR + MPC85xx_CPM_OFFSET)
DECL|macro|BCSR_ADDR
mdefine_line|#define BCSR_ADDR&t;&t;((uint)0xfc000000)
DECL|macro|BCSR_SIZE
mdefine_line|#define BCSR_SIZE&t;&t;((uint)(16 * 1024))
DECL|macro|BCSR_TSEC1_RESET
mdefine_line|#define BCSR_TSEC1_RESET&t;0x00000080
DECL|macro|BCSR_TSEC2_RESET
mdefine_line|#define BCSR_TSEC2_RESET&t;0x00000040
DECL|macro|BCSR_LED1
mdefine_line|#define BCSR_LED1&t;&t;0x00000008
DECL|macro|BCSR_LED2
mdefine_line|#define BCSR_LED2&t;&t;0x00000004
DECL|macro|BCSR_LED3
mdefine_line|#define BCSR_LED3&t;&t;0x00000002
DECL|macro|BCSR_LED4
mdefine_line|#define BCSR_LED4&t;&t;0x00000001
r_extern
r_void
id|mpc85xx_setup_hose
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
r_extern
r_void
id|mpc85xx_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|mpc85xx_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mpc85xx_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|mpc85xx_show_cpuinfo
c_func
(paren
r_struct
id|seq_file
op_star
id|m
)paren
suffix:semicolon
r_extern
r_void
id|mpc85xx_init_IRQ
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
r_extern
r_int
r_int
id|mpc85xx_find_end_of_memory
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
r_extern
r_void
id|mpc85xx_calibrate_decr
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
DECL|macro|PCI_CFG_ADDR_OFFSET
mdefine_line|#define PCI_CFG_ADDR_OFFSET&t;(0x8000)
DECL|macro|PCI_CFG_DATA_OFFSET
mdefine_line|#define PCI_CFG_DATA_OFFSET&t;(0x8004)
multiline_comment|/* PCI interrupt controller */
DECL|macro|PIRQA
mdefine_line|#define PIRQA&t;&t;MPC85xx_IRQ_EXT1
DECL|macro|PIRQB
mdefine_line|#define PIRQB&t;&t;MPC85xx_IRQ_EXT2
DECL|macro|PIRQC
mdefine_line|#define PIRQC&t;&t;MPC85xx_IRQ_EXT3
DECL|macro|PIRQD
mdefine_line|#define PIRQD&t;&t;MPC85xx_IRQ_EXT4
DECL|macro|PCI_MIN_IDSEL
mdefine_line|#define PCI_MIN_IDSEL&t;16
DECL|macro|PCI_MAX_IDSEL
mdefine_line|#define PCI_MAX_IDSEL&t;19
DECL|macro|PCI_IRQ_SLOT
mdefine_line|#define PCI_IRQ_SLOT&t;4
DECL|macro|MPC85XX_PCI1_LOWER_IO
mdefine_line|#define MPC85XX_PCI1_LOWER_IO&t;0x00000000
DECL|macro|MPC85XX_PCI1_UPPER_IO
mdefine_line|#define MPC85XX_PCI1_UPPER_IO&t;0x00ffffff
DECL|macro|MPC85XX_PCI1_LOWER_MEM
mdefine_line|#define MPC85XX_PCI1_LOWER_MEM&t;0x80000000
DECL|macro|MPC85XX_PCI1_UPPER_MEM
mdefine_line|#define MPC85XX_PCI1_UPPER_MEM&t;0x9fffffff
DECL|macro|MPC85XX_PCI1_IO_BASE
mdefine_line|#define MPC85XX_PCI1_IO_BASE&t;0xe2000000
DECL|macro|MPC85XX_PCI1_MEM_OFFSET
mdefine_line|#define MPC85XX_PCI1_MEM_OFFSET&t;0x00000000
DECL|macro|MPC85XX_PCI1_IO_SIZE
mdefine_line|#define MPC85XX_PCI1_IO_SIZE&t;0x01000000
macro_line|#endif /* __MACH_STX_GP3_H */
eof
