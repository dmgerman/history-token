multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; * Copyright (C) 2002 Ralf Baechle&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_SIBYTE_64BIT_H
DECL|macro|__ASM_SIBYTE_64BIT_H
mdefine_line|#define __ASM_SIBYTE_64BIT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifdef CONFIG_MIPS32
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * This is annoying...we can&squot;t actually write the 64-bit IO register properly&n; * without having access to 64-bit registers...  which doesn&squot;t work by default&n; * in o32 format...grrr...&n; */
DECL|function|__out64
r_static
r_inline
r_void
id|__out64
c_func
(paren
id|u64
id|val
comma
r_int
r_int
id|addr
)paren
(brace
id|u64
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;mips3&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;dsll32&t;%L0, %L0, 0&t;# __out64&t;&bslash;n&quot;
l_string|&quot;&t;dsrl32&t;%L0, %L0, 0&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;dsll32&t;%M0, %M0, 0&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;or&t;%L0, %L0, %M0&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sd&t;%L0, (%2)&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips0&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|out64
r_static
r_inline
r_void
id|out64
c_func
(paren
id|u64
id|val
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__out64
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__in64
r_static
r_inline
id|u64
id|__in64
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|u64
id|res
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;.set&t;mips3&t;&t;# __in64&t;&bslash;n&quot;
l_string|&quot;&t;ld&t;%L0, (%1)&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;dsra32&t;%M0, %L0, 0&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;sll&t;%L0, %L0, 0&t;&t;&t;&bslash;n&quot;
l_string|&quot;&t;.set&t;mips0&t;&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|res
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|in64
r_static
r_inline
id|u64
id|in64
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u64
id|res
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|res
op_assign
id|__in64
c_func
(paren
id|addr
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MIPS32 */
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/*&n; * These are provided so as to be able to use common&n; * driver code for the 32-bit and 64-bit trees&n; */
DECL|function|out64
r_extern
r_inline
r_void
id|out64
c_func
(paren
id|u64
id|val
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|function|in64
r_extern
r_inline
id|u64
id|in64
c_func
(paren
r_int
r_int
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
DECL|macro|__in64
mdefine_line|#define __in64(a)&t;in64(a)
DECL|macro|__out64
mdefine_line|#define __out64(v,a)&t;out64(v,a)
macro_line|#endif /* CONFIG_MIPS64 */
multiline_comment|/*&n; * Avoid interrupt mucking, just adjust the address for 4-byte access.&n; * Assume the addresses are 8-byte aligned.&n; */
macro_line|#ifdef __MIPSEB__
DECL|macro|__CSR_32_ADJUST
mdefine_line|#define __CSR_32_ADJUST 4
macro_line|#else
DECL|macro|__CSR_32_ADJUST
mdefine_line|#define __CSR_32_ADJUST 0
macro_line|#endif
DECL|macro|csr_out32
mdefine_line|#define csr_out32(v,a) (*(volatile u32 *)((unsigned long)(a) + __CSR_32_ADJUST) = (v))
DECL|macro|csr_in32
mdefine_line|#define csr_in32(a)    (*(volatile u32 *)((unsigned long)(a) + __CSR_32_ADJUST))
macro_line|#endif /* __ASM_SIBYTE_64BIT_H */
eof
