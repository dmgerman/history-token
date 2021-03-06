multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Low level I/O functions for Jazz family machines.&n; *&n; * Copyright (C) 1997 by Ralf Baechle.&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
multiline_comment|/*&n; * Map an 16mb segment of the EISA address space to 0xe3000000;&n; */
DECL|function|map_eisa_address
r_static
r_inline
r_void
id|map_eisa_address
c_func
(paren
r_int
r_int
id|address
)paren
(brace
multiline_comment|/* XXX */
multiline_comment|/* We&squot;ve got an wired entry in the TLB.  We just need to modify it.&n;     fast and clean.  But since we want to get rid of wired entries&n;     things are a little bit more complicated ... */
)brace
DECL|function|jazz_readb
r_static
r_int
r_char
id|jazz_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_char
id|res
suffix:semicolon
id|map_eisa_address
c_func
(paren
id|addr
)paren
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffff
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|JAZZ_EISA_BASE
op_plus
id|addr
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|jazz_readw
r_static
r_int
r_int
id|jazz_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|res
suffix:semicolon
id|map_eisa_address
c_func
(paren
id|addr
)paren
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffff
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|JAZZ_EISA_BASE
op_plus
id|addr
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|jazz_readl
r_static
r_int
r_int
id|jazz_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|res
suffix:semicolon
id|map_eisa_address
c_func
(paren
id|addr
)paren
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffff
suffix:semicolon
id|res
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|JAZZ_EISA_BASE
op_plus
id|addr
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|jazz_writeb
r_static
r_void
id|jazz_writeb
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_int
id|addr
)paren
(brace
id|map_eisa_address
c_func
(paren
id|addr
)paren
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffff
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|JAZZ_EISA_BASE
op_plus
id|addr
)paren
op_assign
id|val
suffix:semicolon
)brace
DECL|function|jazz_writew
r_static
r_void
id|jazz_writew
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
id|map_eisa_address
c_func
(paren
id|addr
)paren
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffff
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|JAZZ_EISA_BASE
op_plus
id|addr
)paren
op_assign
id|val
suffix:semicolon
)brace
DECL|function|jazz_writel
r_static
r_void
id|jazz_writel
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
id|addr
)paren
(brace
id|map_eisa_address
c_func
(paren
id|addr
)paren
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffff
suffix:semicolon
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
id|JAZZ_EISA_BASE
op_plus
id|addr
)paren
op_assign
id|val
suffix:semicolon
)brace
DECL|function|jazz_memset_io
r_static
r_void
id|jazz_memset_io
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|val
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|waddr
suffix:semicolon
id|waddr
op_assign
id|JAZZ_EISA_BASE
op_or
(paren
id|addr
op_amp
l_int|0xffffff
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
r_int
id|fraglen
suffix:semicolon
id|fraglen
op_assign
(paren
op_complement
id|addr
op_plus
l_int|1
)paren
op_amp
l_int|0xffffff
suffix:semicolon
id|fraglen
op_assign
(paren
id|fraglen
OL
id|len
)paren
ques
c_cond
id|fraglen
suffix:colon
id|len
suffix:semicolon
id|map_eisa_address
c_func
(paren
id|addr
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|waddr
comma
id|val
comma
id|fraglen
)paren
suffix:semicolon
id|addr
op_add_assign
id|fraglen
suffix:semicolon
id|waddr
op_assign
id|waddr
op_plus
id|fraglen
op_minus
l_int|0x1000000
suffix:semicolon
id|len
op_sub_assign
id|fraglen
suffix:semicolon
)brace
)brace
DECL|function|jazz_memcpy_fromio
r_static
r_void
id|jazz_memcpy_fromio
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|waddr
suffix:semicolon
id|waddr
op_assign
id|JAZZ_EISA_BASE
op_or
(paren
id|from
op_amp
l_int|0xffffff
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
r_int
id|fraglen
suffix:semicolon
id|fraglen
op_assign
(paren
op_complement
id|from
op_plus
l_int|1
)paren
op_amp
l_int|0xffffff
suffix:semicolon
id|fraglen
op_assign
(paren
id|fraglen
OL
id|len
)paren
ques
c_cond
id|fraglen
suffix:colon
id|len
suffix:semicolon
id|map_eisa_address
c_func
(paren
id|from
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|to
comma
(paren
r_void
op_star
)paren
id|waddr
comma
id|fraglen
)paren
suffix:semicolon
id|to
op_add_assign
id|fraglen
suffix:semicolon
id|from
op_add_assign
id|fraglen
suffix:semicolon
id|waddr
op_assign
id|waddr
op_plus
id|fraglen
op_minus
l_int|0x1000000
suffix:semicolon
id|len
op_sub_assign
id|fraglen
suffix:semicolon
)brace
)brace
DECL|function|jazz_memcpy_toio
r_static
r_void
id|jazz_memcpy_toio
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
comma
r_int
r_int
id|len
)paren
(brace
r_int
r_int
id|waddr
suffix:semicolon
id|waddr
op_assign
id|JAZZ_EISA_BASE
op_or
(paren
id|to
op_amp
l_int|0xffffff
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_int
r_int
id|fraglen
suffix:semicolon
id|fraglen
op_assign
(paren
op_complement
id|to
op_plus
l_int|1
)paren
op_amp
l_int|0xffffff
suffix:semicolon
id|fraglen
op_assign
(paren
id|fraglen
OL
id|len
)paren
ques
c_cond
id|fraglen
suffix:colon
id|len
suffix:semicolon
id|map_eisa_address
c_func
(paren
id|to
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|to
op_plus
id|JAZZ_EISA_BASE
comma
(paren
r_void
op_star
)paren
id|from
comma
id|fraglen
)paren
suffix:semicolon
id|to
op_add_assign
id|fraglen
suffix:semicolon
id|from
op_add_assign
id|fraglen
suffix:semicolon
id|waddr
op_assign
id|waddr
op_plus
id|fraglen
op_minus
l_int|0x1000000
suffix:semicolon
id|len
op_sub_assign
id|fraglen
suffix:semicolon
)brace
)brace
eof
