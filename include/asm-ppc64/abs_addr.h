macro_line|#ifndef _ABS_ADDR_H
DECL|macro|_ABS_ADDR_H
mdefine_line|#define _ABS_ADDR_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/lmb.h&gt;
DECL|typedef|msChunks_entry
r_typedef
id|u32
id|msChunks_entry
suffix:semicolon
DECL|struct|msChunks
r_struct
id|msChunks
(brace
DECL|member|num_chunks
r_int
r_int
id|num_chunks
suffix:semicolon
DECL|member|chunk_size
r_int
r_int
id|chunk_size
suffix:semicolon
DECL|member|chunk_shift
r_int
r_int
id|chunk_shift
suffix:semicolon
DECL|member|chunk_mask
r_int
r_int
id|chunk_mask
suffix:semicolon
DECL|member|abs
id|msChunks_entry
op_star
id|abs
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|msChunks
id|msChunks
suffix:semicolon
r_extern
r_int
r_int
id|msChunks_alloc
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|reloc_offset
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MSCHUNKS
r_static
r_inline
r_int
r_int
DECL|function|chunk_to_addr
id|chunk_to_addr
c_func
(paren
r_int
r_int
id|chunk
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|msChunks
op_star
id|_msChunks
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|msChunks
)paren
suffix:semicolon
r_return
id|chunk
op_lshift
id|_msChunks-&gt;chunk_shift
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|addr_to_chunk
id|addr_to_chunk
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|msChunks
op_star
id|_msChunks
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|msChunks
)paren
suffix:semicolon
r_return
id|addr
op_rshift
id|_msChunks-&gt;chunk_shift
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|chunk_offset
id|chunk_offset
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|msChunks
op_star
id|_msChunks
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|msChunks
)paren
suffix:semicolon
r_return
id|addr
op_amp
id|_msChunks-&gt;chunk_mask
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|abs_chunk
id|abs_chunk
c_func
(paren
r_int
r_int
id|pchunk
)paren
(brace
r_int
r_int
id|offset
op_assign
id|reloc_offset
c_func
(paren
)paren
suffix:semicolon
r_struct
id|msChunks
op_star
id|_msChunks
op_assign
id|PTRRELOC
c_func
(paren
op_amp
id|msChunks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pchunk
op_ge
id|_msChunks-&gt;num_chunks
)paren
(brace
r_return
id|pchunk
suffix:semicolon
)brace
r_return
id|PTRRELOC
c_func
(paren
id|_msChunks-&gt;abs
)paren
(braket
id|pchunk
)braket
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|phys_to_absolute
id|phys_to_absolute
c_func
(paren
r_int
r_int
id|pa
)paren
(brace
r_return
id|chunk_to_addr
c_func
(paren
id|abs_chunk
c_func
(paren
id|addr_to_chunk
c_func
(paren
id|pa
)paren
)paren
)paren
op_plus
id|chunk_offset
c_func
(paren
id|pa
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|physRpn_to_absRpn
id|physRpn_to_absRpn
c_func
(paren
r_int
r_int
id|rpn
)paren
(brace
r_int
r_int
id|pa
op_assign
id|rpn
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|aa
op_assign
id|phys_to_absolute
c_func
(paren
id|pa
)paren
suffix:semicolon
r_return
(paren
id|aa
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|absolute_to_phys
id|absolute_to_phys
c_func
(paren
r_int
r_int
id|aa
)paren
(brace
r_return
id|lmb_abs_to_phys
c_func
(paren
id|aa
)paren
suffix:semicolon
)brace
macro_line|#else  /* !CONFIG_MSCHUNKS */
DECL|macro|chunk_to_addr
mdefine_line|#define chunk_to_addr(chunk) ((unsigned long)(chunk))
DECL|macro|addr_to_chunk
mdefine_line|#define addr_to_chunk(addr) (addr)
DECL|macro|chunk_offset
mdefine_line|#define chunk_offset(addr) (0)
DECL|macro|abs_chunk
mdefine_line|#define abs_chunk(pchunk) (pchunk)
DECL|macro|phys_to_absolute
mdefine_line|#define phys_to_absolute(pa) (pa)
DECL|macro|physRpn_to_absRpn
mdefine_line|#define physRpn_to_absRpn(rpn) (rpn)
DECL|macro|absolute_to_phys
mdefine_line|#define absolute_to_phys(aa) (aa)
macro_line|#endif /* CONFIG_MSCHUNKS */
r_static
r_inline
r_int
r_int
DECL|function|virt_to_absolute
id|virt_to_absolute
c_func
(paren
r_int
r_int
id|ea
)paren
(brace
r_return
id|phys_to_absolute
c_func
(paren
id|__pa
c_func
(paren
id|ea
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|absolute_to_virt
id|absolute_to_virt
c_func
(paren
r_int
r_int
id|aa
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|absolute_to_phys
c_func
(paren
id|aa
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ABS_ADDR_H */
eof
