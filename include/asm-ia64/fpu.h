macro_line|#ifndef _ASM_IA64_FPU_H
DECL|macro|_ASM_IA64_FPU_H
mdefine_line|#define _ASM_IA64_FPU_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* floating point status register: */
DECL|macro|FPSR_TRAP_VD
mdefine_line|#define FPSR_TRAP_VD&t;(1 &lt;&lt; 0)&t;/* invalid op trap disabled */
DECL|macro|FPSR_TRAP_DD
mdefine_line|#define FPSR_TRAP_DD&t;(1 &lt;&lt; 1)&t;/* denormal trap disabled */
DECL|macro|FPSR_TRAP_ZD
mdefine_line|#define FPSR_TRAP_ZD&t;(1 &lt;&lt; 2)&t;/* zero-divide trap disabled */
DECL|macro|FPSR_TRAP_OD
mdefine_line|#define FPSR_TRAP_OD&t;(1 &lt;&lt; 3)&t;/* overflow trap disabled */
DECL|macro|FPSR_TRAP_UD
mdefine_line|#define FPSR_TRAP_UD&t;(1 &lt;&lt; 4)&t;/* underflow trap disabled */
DECL|macro|FPSR_TRAP_ID
mdefine_line|#define FPSR_TRAP_ID&t;(1 &lt;&lt; 5)&t;/* inexact trap disabled */
DECL|macro|FPSR_S0
mdefine_line|#define FPSR_S0(x)&t;((x) &lt;&lt;  6)
DECL|macro|FPSR_S1
mdefine_line|#define FPSR_S1(x)&t;((x) &lt;&lt; 19)
DECL|macro|FPSR_S2
mdefine_line|#define FPSR_S2(x)&t;(__IA64_UL(x) &lt;&lt; 32)
DECL|macro|FPSR_S3
mdefine_line|#define FPSR_S3(x)&t;(__IA64_UL(x) &lt;&lt; 45)
multiline_comment|/* floating-point status field controls: */
DECL|macro|FPSF_FTZ
mdefine_line|#define FPSF_FTZ&t;(1 &lt;&lt; 0)&t;&t;/* flush-to-zero */
DECL|macro|FPSF_WRE
mdefine_line|#define FPSF_WRE&t;(1 &lt;&lt; 1)&t;&t;/* widest-range exponent */
DECL|macro|FPSF_PC
mdefine_line|#define FPSF_PC(x)&t;(((x) &amp; 0x3) &lt;&lt; 2)&t;/* precision control */
DECL|macro|FPSF_RC
mdefine_line|#define FPSF_RC(x)&t;(((x) &amp; 0x3) &lt;&lt; 4)&t;/* rounding control */
DECL|macro|FPSF_TD
mdefine_line|#define FPSF_TD&t;&t;(1 &lt;&lt; 6)&t;&t;/* trap disabled */
multiline_comment|/* floating-point status field flags: */
DECL|macro|FPSF_V
mdefine_line|#define FPSF_V&t;&t;(1 &lt;&lt;  7)&t;&t;/* invalid operation flag */
DECL|macro|FPSF_D
mdefine_line|#define FPSF_D&t;&t;(1 &lt;&lt;  8)&t;&t;/* denormal/unnormal operand flag */
DECL|macro|FPSF_Z
mdefine_line|#define FPSF_Z&t;&t;(1 &lt;&lt;  9)&t;&t;/* zero divide (IEEE) flag */
DECL|macro|FPSF_O
mdefine_line|#define FPSF_O&t;&t;(1 &lt;&lt; 10)&t;&t;/* overflow (IEEE) flag */
DECL|macro|FPSF_U
mdefine_line|#define FPSF_U&t;&t;(1 &lt;&lt; 11)&t;&t;/* underflow (IEEE) flag */
DECL|macro|FPSF_I
mdefine_line|#define FPSF_I&t;&t;(1 &lt;&lt; 12)&t;&t;/* inexact (IEEE) flag) */
multiline_comment|/* floating-point rounding control: */
DECL|macro|FPRC_NEAREST
mdefine_line|#define FPRC_NEAREST&t;0x0
DECL|macro|FPRC_NEGINF
mdefine_line|#define FPRC_NEGINF&t;0x1
DECL|macro|FPRC_POSINF
mdefine_line|#define FPRC_POSINF&t;0x2
DECL|macro|FPRC_TRUNC
mdefine_line|#define FPRC_TRUNC&t;0x3
DECL|macro|FPSF_DEFAULT
mdefine_line|#define FPSF_DEFAULT&t;(FPSF_PC (0x3) | FPSF_RC (FPRC_NEAREST))
multiline_comment|/* This default value is the same as HP-UX uses.  Don&squot;t change it&n;   without a very good reason.  */
DECL|macro|FPSR_DEFAULT
mdefine_line|#define FPSR_DEFAULT&t;(FPSR_TRAP_VD | FPSR_TRAP_DD | FPSR_TRAP_ZD&t;&bslash;&n;&t;&t;&t; | FPSR_TRAP_OD | FPSR_TRAP_UD | FPSR_TRAP_ID&t;&bslash;&n;&t;&t;&t; | FPSR_S0 (FPSF_DEFAULT)&t;&t;&t;&bslash;&n;&t;&t;&t; | FPSR_S1 (FPSF_DEFAULT | FPSF_TD | FPSF_WRE)&t;&bslash;&n;&t;&t;&t; | FPSR_S2 (FPSF_DEFAULT | FPSF_TD)&t;&t;&bslash;&n;&t;&t;&t; | FPSR_S3 (FPSF_DEFAULT | FPSF_TD))
macro_line|# ifndef __ASSEMBLY__
DECL|struct|ia64_fpreg
r_struct
id|ia64_fpreg
(brace
r_union
(brace
DECL|member|bits
r_int
r_int
id|bits
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|16
)paren
)paren
)paren
suffix:semicolon
macro_line|# endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_FPU_H */
eof
