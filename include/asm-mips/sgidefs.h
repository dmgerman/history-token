multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; *&n; * Definitions commonly used in SGI style code.&n; */
macro_line|#ifndef __ASM_SGIDEFS_H
DECL|macro|__ASM_SGIDEFS_H
mdefine_line|#define __ASM_SGIDEFS_H
multiline_comment|/*&n; * There are compilers out there that don&squot;t define _MIPS_ISA, _MIPS_SIM,&n; * _MIPS_SZINT, _MIPS_SZLONG, _MIPS_SZPTR.  So we notify the user about this&n; * problem.  The kernel sources are aware of this problem, so we don&squot;t warn&n; * when compiling the kernel.&n; */
macro_line|#if !defined(_MIPS_ISA) &amp;&amp; !defined(__KERNEL__)
macro_line|#warning &quot;Macro _MIPS_ISA has not been defined by specs file&quot;
macro_line|#endif
macro_line|#if !defined(_MIPS_SIM) &amp;&amp; !defined(__KERNEL__)
macro_line|#warning &quot;Macro _MIPS_SIM has not been defined by specs file&quot;
macro_line|#endif
macro_line|#if !defined(_MIPS_SZINT) &amp;&amp; !defined(__KERNEL__)
macro_line|#warning &quot;Macro _MIPS_SZINT has not been defined by specs file&quot;
macro_line|#endif
macro_line|#if !defined(_MIPS_SZLONG) &amp;&amp; !defined(__KERNEL__)
macro_line|#warning &quot;Macro _MIPS_SZLONG has not been defined by specs file&quot;
macro_line|#endif
macro_line|#if !defined(_MIPS_SZPTR) &amp;&amp; !defined(__KERNEL__)
macro_line|#warning &quot;Macro _MIPS_SZPTR has not been defined by specs file&quot;
macro_line|#endif
macro_line|#if (!defined(_MIPS_ISA) || &bslash;&n;     !defined(_MIPS_SIM) || &bslash;&n;     !defined(_MIPS_SZINT) || &bslash;&n;     !defined(_MIPS_SZLONG) || &bslash;&n;     !defined(_MIPS_SZPTR)) &amp;&amp; !defined(__KERNEL__)
macro_line|#warning &quot;Please update your GCC to GCC 2.7.2-4 or newer&quot;
macro_line|#endif
multiline_comment|/*&n; * Now let&squot;s try our best to supply some reasonable default values for&n; * whatever defines GCC didn&squot;t supply.  This cannot be done correct for&n; * all possible combinations of options, so be careful with your options&n; * to GCC.  Best bet is to keep your fingers off the a.out GCC and use&n; * ELF GCC 2.7.2-3 where possible.&n; */
macro_line|#ifndef _MIPS_ISA
macro_line|#if __mips == 1
DECL|macro|_MIPS_ISA
mdefine_line|#define _MIPS_ISA&t;_MIPS_ISA_MIPS1
multiline_comment|/* It is impossible to handle the -mips2 case correct.  */
macro_line|#elif __mips == 3
DECL|macro|_MIPS_ISA
mdefine_line|#define _MIPS_ISA&t;_MIPS_ISA_MIPS3
macro_line|#elif __mips == 4
DECL|macro|_MIPS_ISA
mdefine_line|#define _MIPS_ISA&t;_MIPS_ISA_MIPS4
macro_line|#else /* __mips must be 5 */
DECL|macro|_MIPS_ISA
mdefine_line|#define _MIPS_ISA&t;_MIPS_ISA_MIPS5
macro_line|#endif
macro_line|#endif
macro_line|#ifndef _MIPS_SIM
DECL|macro|_MIPS_SIM
mdefine_line|#define _MIPS_SIM&t;_MIPS_SIM_ABI32
macro_line|#endif
macro_line|#ifndef _MIPS_SZINT
DECL|macro|_MIPS_SZINT
mdefine_line|#define _MIPS_SZINT&t;32
macro_line|#endif
macro_line|#ifndef _MIPS_SZLONG
DECL|macro|_MIPS_SZLONG
mdefine_line|#define _MIPS_SZLONG&t;32
macro_line|#endif
macro_line|#ifndef _MIPS_SZPTR
DECL|macro|_MIPS_SZPTR
mdefine_line|#define _MIPS_SZPTR&t;32
macro_line|#endif
multiline_comment|/*&n; * Definitions for the ISA level&n; */
DECL|macro|_MIPS_ISA_MIPS1
mdefine_line|#define _MIPS_ISA_MIPS1 1
DECL|macro|_MIPS_ISA_MIPS2
mdefine_line|#define _MIPS_ISA_MIPS2 2
DECL|macro|_MIPS_ISA_MIPS3
mdefine_line|#define _MIPS_ISA_MIPS3 3
DECL|macro|_MIPS_ISA_MIPS4
mdefine_line|#define _MIPS_ISA_MIPS4 4
DECL|macro|_MIPS_ISA_MIPS5
mdefine_line|#define _MIPS_ISA_MIPS5 5
multiline_comment|/*&n; * Subprogram calling convention&n; *&n; * At the moment only _MIPS_SIM_ABI32 is in use.  This will change rsn.&n; * Until GCC 2.8.0 is released don&squot;t rely on this definitions because the&n; * 64bit code is essentially using the 32bit interface model just with&n; * 64bit registers.&n; */
DECL|macro|_MIPS_SIM_ABI32
mdefine_line|#define _MIPS_SIM_ABI32&t;&t;1
DECL|macro|_MIPS_SIM_NABI32
mdefine_line|#define _MIPS_SIM_NABI32&t;2
DECL|macro|_MIPS_SIM_ABI64
mdefine_line|#define _MIPS_SIM_ABI64&t;&t;3
macro_line|#endif /* __ASM_SGIDEFS_H */
eof
