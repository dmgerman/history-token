multiline_comment|/* $Id: paccess.h,v 1.1 2000/04/07 12:55:57 raiko Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997, 1998, 1999, 2000 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; *&n; * Protected memory access.  Used for everything that might take revenge&n; * by sending a DBE error like accessing possibly non-existant memory or&n; * devices.&n; */
macro_line|#ifndef _ASM_PACCESS_H
DECL|macro|_ASM_PACCESS_H
mdefine_line|#define _ASM_PACCESS_H
macro_line|#include &lt;linux/errno.h&gt;
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
mdefine_line|#define __get_dbe(x,ptr,size) ({ &bslash;&n;int __gu_err; &bslash;&n;__typeof(*(ptr)) __gu_val; &bslash;&n;unsigned long __gu_addr; &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_val)); &bslash;&n;__gu_addr = (unsigned long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__gu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __get_dbe_asm(&quot;lb&quot;); break; &bslash;&n;case 2: __get_dbe_asm(&quot;lh&quot;); break; &bslash;&n;case 4: __get_dbe_asm(&quot;lw&quot;); break; &bslash;&n;case 8:  __get_dbe_asm(&quot;ld&quot;); break; &bslash;&n;default: __get_dbe_unknown(); break; &bslash;&n;} x = (__typeof__(*(ptr))) __gu_val; __gu_err; })
DECL|macro|__get_dbe_asm
mdefine_line|#define __get_dbe_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;.set&bslash;tpush&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;insn &quot;&bslash;t%1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;1:&bslash;tmove&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;.set&bslash;tpop&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;tli&bslash;t%0,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;move&bslash;t%1,$0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;j&bslash;t2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__dbe_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t1b-4,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__gu_err), &quot;=r&quot; (__gu_val) &bslash;&n;&t;:&quot;o&quot; (__mp(__gu_addr)), &quot;i&quot; (-EFAULT)); })
r_extern
r_void
id|__get_dbe_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|__put_dbe
mdefine_line|#define __put_dbe(x,ptr,size) ({ &bslash;&n;int __pu_err; &bslash;&n;__typeof__(*(ptr)) __pu_val; &bslash;&n;unsigned long __pu_addr; &bslash;&n;__pu_val = (x); &bslash;&n;__pu_addr = (unsigned long) (ptr); &bslash;&n;__asm__(&quot;&quot;:&quot;=r&quot; (__pu_err)); &bslash;&n;switch (size) { &bslash;&n;case 1: __put_dbe_asm(&quot;sb&quot;); break; &bslash;&n;case 2: __put_dbe_asm(&quot;sh&quot;); break; &bslash;&n;case 4: __put_dbe_asm(&quot;sw&quot;); break; &bslash;&n;case 8: __put_dbe_asm(&quot;sd&quot;); break; &bslash;&n;default: __put_dbe_unknown(); break; &bslash;&n;} __pu_err; })
DECL|macro|__put_dbe_asm
mdefine_line|#define __put_dbe_asm(insn) &bslash;&n;({ &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;.set&bslash;tpush&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot; &bslash;&n;&t;insn &quot;&bslash;t%1,%2&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;1:&bslash;tmove&bslash;t%0,$0&bslash;n&quot; &bslash;&n;&t;&quot;.set&bslash;tpop&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;2:&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t.fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot; &bslash;&n;&t;&quot;3:&bslash;tli&bslash;t%0,%3&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;j&bslash;t2b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.section&bslash;t__dbe_table,&bslash;&quot;a&bslash;&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.word&bslash;t1b-4,3b&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.previous&quot; &bslash;&n;&t;:&quot;=r&quot; (__pu_err) &bslash;&n;&t;:&quot;r&quot; (__pu_val), &quot;o&quot; (__mp(__pu_addr)), &quot;i&quot; (-EFAULT)); })
r_extern
r_void
id|__put_dbe_unknown
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _ASM_PACCESS_H */
eof
