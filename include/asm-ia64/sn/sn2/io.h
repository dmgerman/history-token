multiline_comment|/* &n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_SN2_IO_H
DECL|macro|_ASM_SN_SN2_IO_H
mdefine_line|#define _ASM_SN_SN2_IO_H
r_extern
r_void
op_star
id|sn_io_addr
c_func
(paren
r_int
r_int
id|port
)paren
suffix:semicolon
multiline_comment|/* Forward definition */
r_extern
r_void
id|sn_mmiob
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Forward definition */
DECL|macro|__sn_mf_a
mdefine_line|#define __sn_mf_a()   __asm__ __volatile__ (&quot;mf.a&quot; ::: &quot;memory&quot;)
r_extern
r_void
id|sn_dma_flush
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * The following routines are SN Platform specific, called when&n; * a reference is made to inX/outX set macros.  SN Platform&n; * inX set of macros ensures that Posted DMA writes on the&n; * Bridge is flushed.&n; *&n; * The routines should be self explainatory.&n; */
r_static
r_inline
r_int
r_int
DECL|function|__sn_inb
id|__sn_inb
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|sn_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_char
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
id|sn_dma_flush
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__sn_inw
id|__sn_inw
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|sn_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
id|sn_dma_flush
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__sn_inl
id|__sn_inl
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|sn_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
id|sn_dma_flush
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__sn_outb
id|__sn_outb
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
r_volatile
r_int
r_char
op_star
id|addr
op_assign
id|sn_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|sn_mmiob
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__sn_outw
id|__sn_outw
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
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|sn_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|sn_mmiob
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|__sn_outl
id|__sn_outl
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
r_volatile
r_int
r_int
op_star
id|addr
op_assign
id|sn_io_addr
c_func
(paren
id|port
)paren
suffix:semicolon
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|sn_mmiob
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following routines are SN Platform specific, called when &n; * a reference is made to readX/writeX set macros.  SN Platform &n; * readX set of macros ensures that Posted DMA writes on the &n; * Bridge is flushed.&n; * &n; * The routines should be self explainatory.&n; */
r_static
r_inline
r_int
r_char
DECL|function|__sn_readb
id|__sn_readb
(paren
r_void
op_star
id|addr
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|val
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
id|sn_dma_flush
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__sn_readw
id|__sn_readw
(paren
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
id|sn_dma_flush
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__sn_readl
id|__sn_readl
(paren
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
id|sn_dma_flush
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__sn_readq
id|__sn_readq
(paren
r_void
op_star
id|addr
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
id|sn_dma_flush
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * For generic and SN2 kernels, we have a set of fast access&n; * PIO macros.&t;These macros are provided on SN Platform&n; * because the normal inX and readX macros perform an&n; * additional task of flushing Post DMA request on the Bridge.&n; *&n; * These routines should be self explainatory.&n; */
r_static
r_inline
r_int
r_int
DECL|function|sn_inb_fast
id|sn_inb_fast
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_char
op_star
id|addr
op_assign
(paren
r_int
r_char
op_star
)paren
id|port
suffix:semicolon
r_int
r_char
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|sn_inw_fast
id|sn_inw_fast
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|port
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|sn_inl_fast
id|sn_inl_fast
(paren
r_int
r_int
id|port
)paren
(brace
r_volatile
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|port
suffix:semicolon
r_int
r_int
id|ret
suffix:semicolon
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|__sn_mf_a
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_inline
r_int
r_char
DECL|function|sn_readb_fast
id|sn_readb_fast
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|sn_readw_fast
id|sn_readw_fast
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|sn_readl_fast
id|sn_readl_fast
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|sn_readq_fast
id|sn_readq_fast
(paren
r_void
op_star
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
suffix:semicolon
)brace
macro_line|#endif
eof
