multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998, 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; *&n; * Protected memory access.  Used for everything that might take revenge&n; * by sending a DBE error like accessing possibly non-existant memory or&n; * devices.&n; */
macro_line|#ifndef _ASM_PACCESS_H
DECL|macro|_ASM_PACCESS_H
mdefine_line|#define _ASM_PACCESS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#ifdef CONFIG_MIPS32
DECL|macro|__PA_ADDR
mdefine_line|#define __PA_ADDR&t;&quot;.word&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
DECL|macro|__PA_ADDR
mdefine_line|#define __PA_ADDR&t;&quot;.dword&quot;
macro_line|#endif
r_extern
id|asmlinkage
r_void
id|handle_ibe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|handle_dbe
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|put_dbe
mdefine_line|#define put_dbe(x,ptr) __put_dbe((x),(ptr),sizeof(*(ptr)))
DECL|macro|get_dbe
mdefine_line|#define get_dbe(x,ptr) __get_dbe((x),(ptr),sizeof(*(ptr)))
DECL|struct|__large_pstruct
DECL|member|buf
r_struct
id|__large_pstruct
(brace
r_int
r_int
id|buf
(braket
l_int|100
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|__mp
mdefine_line|#define __mp(x) (*(struct __large_pstruct *)(x))
DECL|macro|__get_dbe
mdefine_line|#define __get_dbe(x,ptr,size)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof(*(ptr)) __gu_val;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __gu_addr;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val));&t;&t;&t;&t;&t;&bslash;&n;&t;__gu_addr = (unsigned long) (ptr);&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err));&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1: __get_dbe_asm(&quot;lb&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;case 2: __get_dbe_asm(&quot;lh&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;case 4: __get_dbe_asm(&quot;lw&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;case 8:  __get_dbe_asm(&quot;ld&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;default: __get_dbe_unknown(); break;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;x = (__typeof__(*(ptr))) __gu_val;&t;&t;&t;&t;&bslash;&n;&t;__gu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__get_dbe_asm
mdefine_line|#define __get_dbe_asm(insn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;t&quot; insn &quot;&bslash;t%1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&bslash;tli&bslash;t%0,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%1,$0&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;j&bslash;t2b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section&bslash;t__dbe_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;__PA_ADDR &quot;&bslash;t1b, 3b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:&quot;=r&quot; (__gu_err), &quot;=r&quot; (__gu_val)&t;&t;&t;&t;&bslash;&n;&t;:&quot;o&quot; (__mp(__gu_addr)), &quot;i&quot; (-EFAULT));&t;&t;&t;&t;&bslash;&n;})
r_extern
r_void
id|__get_dbe_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_dbe
mdefine_line|#define __put_dbe(x,ptr,size)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__typeof__(*(ptr)) __pu_val;&t;&t;&t;&t;&t;&bslash;&n;&t;long __pu_addr;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_val = (x);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_addr = (long) (ptr);&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err));&t;&t;&t;&t;&t;&bslash;&n;&t;switch (size) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;case 1: __put_dbe_asm(&quot;sb&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;case 2: __put_dbe_asm(&quot;sh&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;case 4: __put_dbe_asm(&quot;sw&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;case 8: __put_dbe_asm(&quot;sd&quot;); break;&t;&t;&t;&t;&bslash;&n;&t;default: __put_dbe_unknown(); break;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pu_err;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__put_dbe_asm
mdefine_line|#define __put_dbe_asm(insn)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;t&quot; insn &quot;&bslash;t%1,%2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;move&bslash;t%0,$0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;3:&bslash;tli&bslash;t%0,%3&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;j&bslash;t2b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.section&bslash;t__dbe_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;__PA_ADDR &quot;&bslash;t1b, 3b&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.previous&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (__pu_err)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (__pu_val), &quot;o&quot; (__mp(__pu_addr)), &quot;i&quot; (-EFAULT));&t;&bslash;&n;})
r_extern
r_void
id|__put_dbe_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|search_dbe_table
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#endif /* _ASM_PACCESS_H */
eof
