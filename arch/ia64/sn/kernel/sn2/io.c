multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003 Silicon Graphics, Inc. All rights reserved.&n; *&n; * The generic kernel requires function pointers to these routines, so&n; * we wrap the inlines from asm/ia64/sn/sn2/io.h here.&n; */
macro_line|#include &lt;asm/sn/io.h&gt;
macro_line|#ifdef CONFIG_IA64_GENERIC
DECL|macro|__sn_inb
macro_line|#undef __sn_inb
DECL|macro|__sn_inw
macro_line|#undef __sn_inw
DECL|macro|__sn_inl
macro_line|#undef __sn_inl
DECL|macro|__sn_outb
macro_line|#undef __sn_outb
DECL|macro|__sn_outw
macro_line|#undef __sn_outw
DECL|macro|__sn_outl
macro_line|#undef __sn_outl
DECL|macro|__sn_readb
macro_line|#undef __sn_readb
DECL|macro|__sn_readw
macro_line|#undef __sn_readw
DECL|macro|__sn_readl
macro_line|#undef __sn_readl
DECL|macro|__sn_readq
macro_line|#undef __sn_readq
DECL|macro|__sn_readb_relaxed
macro_line|#undef __sn_readb_relaxed
DECL|macro|__sn_readw_relaxed
macro_line|#undef __sn_readw_relaxed
DECL|macro|__sn_readl_relaxed
macro_line|#undef __sn_readl_relaxed
DECL|macro|__sn_readq_relaxed
macro_line|#undef __sn_readq_relaxed
DECL|function|__sn_inb
r_int
r_int
id|__sn_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|___sn_inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|__sn_inw
r_int
r_int
id|__sn_inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|___sn_inw
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|__sn_inl
r_int
r_int
id|__sn_inl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|___sn_inl
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|__sn_outb
r_void
id|__sn_outb
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|___sn_outb
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|__sn_outw
r_void
id|__sn_outw
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|___sn_outw
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|__sn_outl
r_void
id|__sn_outl
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|port
)paren
(brace
id|___sn_outl
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|__sn_readb
r_int
r_char
id|__sn_readb
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readb
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__sn_readw
r_int
r_int
id|__sn_readw
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readw
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__sn_readl
r_int
r_int
id|__sn_readl
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readl
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__sn_readq
r_int
r_int
id|__sn_readq
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readq
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__sn_readb_relaxed
r_int
r_char
id|__sn_readb_relaxed
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readb_relaxed
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__sn_readw_relaxed
r_int
r_int
id|__sn_readw_relaxed
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readw_relaxed
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__sn_readl_relaxed
r_int
r_int
id|__sn_readl_relaxed
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readl_relaxed
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|__sn_readq_relaxed
r_int
r_int
id|__sn_readq_relaxed
c_func
(paren
r_void
id|__iomem
op_star
id|addr
)paren
(brace
r_return
id|___sn_readq_relaxed
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
