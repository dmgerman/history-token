multiline_comment|/*&n; * arch/ppc/syslib/ppc85xx_common.h&n; *&n; * MPC85xx support routines&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef __PPC_SYSLIB_PPC85XX_COMMON_H
DECL|macro|__PPC_SYSLIB_PPC85XX_COMMON_H
mdefine_line|#define __PPC_SYSLIB_PPC85XX_COMMON_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
multiline_comment|/* Provide access to ccsrbar for any modules, etc */
id|phys_addr_t
id|get_ccsrbar
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Update the 85xx OCP tables paddr field */
r_void
id|mpc85xx_update_paddr_ocp
c_func
(paren
r_struct
id|ocp_device
op_star
id|dev
comma
r_void
op_star
id|ccsrbar
)paren
suffix:semicolon
macro_line|#endif /* __PPC_SYSLIB_PPC85XX_COMMON_H */
eof
