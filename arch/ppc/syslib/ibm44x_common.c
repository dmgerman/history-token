multiline_comment|/*&n; * arch/ppc/syslib/ibm44x_common.c&n; *&n; * PPC44x system library&n; *&n; * Matt Porter &lt;mporter@mvista.com&gt;&n; * Copyright 2002-2003 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ibm44x.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
DECL|function|fixup_bigphys_addr
id|phys_addr_t
id|fixup_bigphys_addr
c_func
(paren
id|phys_addr_t
id|addr
comma
id|phys_addr_t
id|size
)paren
(brace
id|phys_addr_t
id|page_4gb
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Trap the least significant 32-bit portions of an&n;&t; * address in the 440&squot;s 36-bit address space.  Fix&n;&t; * them up with the appropriate ERPN&n;&t; */
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|PPC44x_IO_LO
)paren
op_logical_and
(paren
id|addr
OL
id|PPC44x_IO_HI
)paren
)paren
id|page_4gb
op_assign
id|PPC44x_IO_PAGE
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|PPC44x_PCICFG_LO
)paren
op_logical_and
(paren
id|addr
OL
id|PPC44x_PCICFG_HI
)paren
)paren
id|page_4gb
op_assign
id|PPC44x_PCICFG_PAGE
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|PPC44x_PCIMEM_LO
)paren
op_logical_and
(paren
id|addr
OL
id|PPC44x_PCIMEM_HI
)paren
)paren
id|page_4gb
op_assign
id|PPC44x_PCIMEM_PAGE
suffix:semicolon
r_return
(paren
id|page_4gb
op_or
id|addr
)paren
suffix:semicolon
)brace
suffix:semicolon
eof
