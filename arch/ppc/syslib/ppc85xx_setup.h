multiline_comment|/*&n; * arch/ppc/syslib/ppc85xx_setup.h&n; *&n; * MPC85XX common board definitions&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#ifndef __PPC_SYSLIB_PPC85XX_SETUP_H
DECL|macro|__PPC_SYSLIB_PPC85XX_SETUP_H
mdefine_line|#define __PPC_SYSLIB_PPC85XX_SETUP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ppcboot.h&gt;
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
r_extern
r_void
id|mpc85xx_early_serial_map
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
r_void
id|mpc85xx_setup_hose
c_func
(paren
r_void
)paren
id|__init
suffix:semicolon
multiline_comment|/* PCI config */
DECL|macro|PCI1_CFG_ADDR_OFFSET
mdefine_line|#define PCI1_CFG_ADDR_OFFSET&t;(0x8000)
DECL|macro|PCI1_CFG_DATA_OFFSET
mdefine_line|#define PCI1_CFG_DATA_OFFSET&t;(0x8004)
DECL|macro|PCI2_CFG_ADDR_OFFSET
mdefine_line|#define PCI2_CFG_ADDR_OFFSET&t;(0x9000)
DECL|macro|PCI2_CFG_DATA_OFFSET
mdefine_line|#define PCI2_CFG_DATA_OFFSET&t;(0x9004)
multiline_comment|/* Additional register for PCI-X configuration */
DECL|macro|PCIX_NEXT_CAP
mdefine_line|#define PCIX_NEXT_CAP&t;0x60
DECL|macro|PCIX_CAP_ID
mdefine_line|#define PCIX_CAP_ID&t;0x61
DECL|macro|PCIX_COMMAND
mdefine_line|#define PCIX_COMMAND&t;0x62
DECL|macro|PCIX_STATUS
mdefine_line|#define PCIX_STATUS&t;0x64
multiline_comment|/* Serial Config */
macro_line|#ifdef CONFIG_SERIAL_MANY_PORTS
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  64
macro_line|#else
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  2
macro_line|#endif
macro_line|#ifndef BASE_BAUD
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD 115200
macro_line|#endif
multiline_comment|/* Offset of CPM register space */
DECL|macro|CPM_MAP_ADDR
mdefine_line|#define CPM_MAP_ADDR&t;(CCSRBAR + MPC85xx_CPM_OFFSET)
macro_line|#endif /* __PPC_SYSLIB_PPC85XX_SETUP_H */
eof
