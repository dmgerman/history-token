multiline_comment|/*&n; * include/asm-sh/cpu-sh4/sq.h&n; *&n; * Copyright (C) 2001, 2002, 2003  Paul Mundt&n; * Copyright (C) 2001, 2002  M. R. Brown&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH4_SQ_H
DECL|macro|__ASM_CPU_SH4_SQ_H
mdefine_line|#define __ASM_CPU_SH4_SQ_H
macro_line|#include &lt;asm/addrspace.h&gt;
multiline_comment|/*&n; * Store queues range from e0000000-e3fffffc, allowing approx. 64MB to be&n; * mapped to any physical address space. Since data is written (and aligned)&n; * to 32-byte boundaries, we need to be sure that all allocations are aligned.&n; */
DECL|macro|SQ_SIZE
mdefine_line|#define SQ_SIZE                 32
DECL|macro|SQ_ALIGN_MASK
mdefine_line|#define SQ_ALIGN_MASK           (~(SQ_SIZE - 1))
DECL|macro|SQ_ALIGN
mdefine_line|#define SQ_ALIGN(addr)          (((addr)+SQ_SIZE-1) &amp; SQ_ALIGN_MASK)
DECL|macro|SQ_QACR0
mdefine_line|#define SQ_QACR0&t;&t;(P4SEG_REG_BASE  + 0x38)
DECL|macro|SQ_QACR1
mdefine_line|#define SQ_QACR1&t;&t;(P4SEG_REG_BASE  + 0x3c)
DECL|macro|SQ_ADDRMAX
mdefine_line|#define SQ_ADDRMAX              (P4SEG_STORE_QUE + 0x04000000)
DECL|struct|sq_mapping
r_struct
id|sq_mapping
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|sq_addr
r_int
r_int
id|sq_addr
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* arch/sh/kernel/cpu/sh4/sq.c */
r_extern
r_struct
id|sq_mapping
op_star
id|sq_remap
c_func
(paren
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|sq_unmap
c_func
(paren
r_struct
id|sq_mapping
op_star
id|map
)paren
suffix:semicolon
r_extern
r_void
id|sq_clear
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|sq_flush
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|sq_flush_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif /* __ASM_CPU_SH4_SQ_H */
eof
