multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999, 2000, 2003 Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SIM_H
DECL|macro|_ASM_SIM_H
mdefine_line|#define _ASM_SIM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/offset.h&gt;
macro_line|#ifdef CONFIG_MIPS32
multiline_comment|/* Used in declaration of save_static functions.  */
DECL|macro|static_unused
mdefine_line|#define static_unused static __attribute__((unused))
DECL|macro|__str2
mdefine_line|#define __str2(x) #x
DECL|macro|__str
mdefine_line|#define __str(x) __str2(x)
DECL|macro|save_static_function
mdefine_line|#define save_static_function(symbol)&t;&t;&t;&t;&t;&bslash;&n;__asm__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.text&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.globl&bslash;t&quot; #symbol &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&bslash;t2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.type&bslash;t&quot; #symbol &quot;, @function&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.ent&bslash;t&quot; #symbol &quot;, 0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;#symbol&quot;:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.frame&bslash;t$29, 0, $31&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$16,&quot;__str(PT_R16)&quot;($29)&bslash;t&bslash;t&bslash;t# save_static_function&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;sw&bslash;t$17,&quot;__str(PT_R17)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$18,&quot;__str(PT_R18)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$19,&quot;__str(PT_R19)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$20,&quot;__str(PT_R20)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$21,&quot;__str(PT_R21)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$22,&quot;__str(PT_R22)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$23,&quot;__str(PT_R23)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;sw&bslash;t$30,&quot;__str(PT_R30)&quot;($29)&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.end&bslash;t&quot; #symbol &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.size&bslash;t&quot; #symbol&quot;,. - &quot; #symbol)
DECL|macro|save_static
mdefine_line|#define save_static(frame)&t;do { } while (0)
DECL|macro|nabi_no_regargs
mdefine_line|#define nabi_no_regargs
macro_line|#endif /* CONFIG_MIPS32 */
macro_line|#ifdef CONFIG_MIPS64
multiline_comment|/* Used in declaration of save_static functions.  */
DECL|macro|static_unused
mdefine_line|#define static_unused static __attribute__((unused))
DECL|macro|__str2
mdefine_line|#define __str2(x) #x
DECL|macro|__str
mdefine_line|#define __str(x) __str2(x)
DECL|macro|save_static_function
mdefine_line|#define save_static_function(symbol)&t;&t;&t;&t;&t;&bslash;&n;__asm__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.text&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.globl&bslash;t&quot; #symbol &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.align&bslash;t2&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.type&bslash;t&quot; #symbol &quot;, @function&bslash;n&bslash;t&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;.ent&bslash;t&quot; #symbol &quot;, 0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;#symbol&quot;:&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.frame&bslash;t$29, 0, $31&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.end&bslash;t&quot; #symbol &quot;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.size&bslash;t&quot; #symbol&quot;,. - &quot; #symbol)
DECL|macro|save_static
mdefine_line|#define save_static(frame)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$16,&quot;__str(PT_R16)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$17,&quot;__str(PT_R17)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$18,&quot;__str(PT_R18)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$19,&quot;__str(PT_R19)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$20,&quot;__str(PT_R20)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$21,&quot;__str(PT_R21)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$22,&quot;__str(PT_R22)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$23,&quot;__str(PT_R23)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;sd&bslash;t$30,&quot;__str(PT_R30)&quot;(%0)&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;&t;: /* No outputs */&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (frame))
DECL|macro|nabi_no_regargs
mdefine_line|#define nabi_no_regargs&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy1,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy2,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy3,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy4,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy5,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy6,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long __dummy7,
macro_line|#endif /* CONFIG_MIPS64 */
macro_line|#endif /* _ASM_SIM_H */
eof
