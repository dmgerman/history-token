multiline_comment|/*&n; * arch/ppc/syslib/ppc85xx_common.c&n; *&n; * MPC85xx support routines&n; *&n; * Maintainer: Kumar Gala &lt;kumar.gala@freescale.com&gt;&n; *&n; * Copyright 2004 Freescale Semiconductor Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mpc85xx.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
multiline_comment|/* ************************************************************************ */
multiline_comment|/* Return the value of CCSRBAR for the current board */
id|phys_addr_t
DECL|function|get_ccsrbar
id|get_ccsrbar
c_func
(paren
r_void
)paren
(brace
r_return
id|BOARD_CCSRBAR
suffix:semicolon
)brace
multiline_comment|/* ************************************************************************ */
multiline_comment|/* Update the 85xx OCP tables paddr field */
r_void
DECL|function|mpc85xx_update_paddr_ocp
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
id|arg
)paren
(brace
id|phys_addr_t
id|ccsrbar
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
(brace
id|ccsrbar
op_assign
op_star
(paren
id|phys_addr_t
op_star
)paren
id|arg
suffix:semicolon
id|dev-&gt;def-&gt;paddr
op_add_assign
id|ccsrbar
suffix:semicolon
)brace
)brace
DECL|variable|get_ccsrbar
id|EXPORT_SYMBOL
c_func
(paren
id|get_ccsrbar
)paren
suffix:semicolon
eof
