multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1985 MIPS Computer Systems, Inc.&n; * Copyright (C) 1994, 95, 99, 2003 by Ralf Baechle&n; * Copyright (C) 1990 - 1992, 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_REGDEF_H
DECL|macro|_ASM_REGDEF_H
mdefine_line|#define _ASM_REGDEF_H
macro_line|#include &lt;asm/sgidefs.h&gt;
macro_line|#if _MIPS_SIM == _MIPS_SIM_ABI32
multiline_comment|/*&n; * Symbolic register names for 32 bit ABI&n; */
DECL|macro|zero
mdefine_line|#define zero    $0      /* wired zero */
DECL|macro|AT
mdefine_line|#define AT      $1      /* assembler temp  - uppercase because of &quot;.set at&quot; */
DECL|macro|v0
mdefine_line|#define v0      $2      /* return value */
DECL|macro|v1
mdefine_line|#define v1      $3
DECL|macro|a0
mdefine_line|#define a0      $4      /* argument registers */
DECL|macro|a1
mdefine_line|#define a1      $5
DECL|macro|a2
mdefine_line|#define a2      $6
DECL|macro|a3
mdefine_line|#define a3      $7
DECL|macro|t0
mdefine_line|#define t0      $8      /* caller saved */
DECL|macro|t1
mdefine_line|#define t1      $9
DECL|macro|t2
mdefine_line|#define t2      $10
DECL|macro|t3
mdefine_line|#define t3      $11
DECL|macro|t4
mdefine_line|#define t4      $12
DECL|macro|t5
mdefine_line|#define t5      $13
DECL|macro|t6
mdefine_line|#define t6      $14
DECL|macro|t7
mdefine_line|#define t7      $15
DECL|macro|s0
mdefine_line|#define s0      $16     /* callee saved */
DECL|macro|s1
mdefine_line|#define s1      $17
DECL|macro|s2
mdefine_line|#define s2      $18
DECL|macro|s3
mdefine_line|#define s3      $19
DECL|macro|s4
mdefine_line|#define s4      $20
DECL|macro|s5
mdefine_line|#define s5      $21
DECL|macro|s6
mdefine_line|#define s6      $22
DECL|macro|s7
mdefine_line|#define s7      $23
DECL|macro|t8
mdefine_line|#define t8      $24     /* caller saved */
DECL|macro|t9
mdefine_line|#define t9      $25
DECL|macro|jp
mdefine_line|#define jp      $25     /* PIC jump register */
DECL|macro|k0
mdefine_line|#define k0      $26     /* kernel scratch */
DECL|macro|k1
mdefine_line|#define k1      $27
DECL|macro|gp
mdefine_line|#define gp      $28     /* global pointer */
DECL|macro|sp
mdefine_line|#define sp      $29     /* stack pointer */
DECL|macro|fp
mdefine_line|#define fp      $30     /* frame pointer */
DECL|macro|s8
mdefine_line|#define s8&t;$30&t;/* same like fp! */
DECL|macro|ra
mdefine_line|#define ra      $31     /* return address */
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI32 */
macro_line|#if _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32
DECL|macro|zero
mdefine_line|#define zero&t;$0&t;/* wired zero */
DECL|macro|AT
mdefine_line|#define AT&t;$at&t;/* assembler temp - uppercase because of &quot;.set at&quot; */
DECL|macro|v0
mdefine_line|#define v0&t;$2&t;/* return value - caller saved */
DECL|macro|v1
mdefine_line|#define v1&t;$3
DECL|macro|a0
mdefine_line|#define a0&t;$4&t;/* argument registers */
DECL|macro|a1
mdefine_line|#define a1&t;$5
DECL|macro|a2
mdefine_line|#define a2&t;$6
DECL|macro|a3
mdefine_line|#define a3&t;$7
DECL|macro|a4
mdefine_line|#define a4&t;$8&t;/* arg reg 64 bit; caller saved in 32 bit */
DECL|macro|ta0
mdefine_line|#define ta0&t;$8
DECL|macro|a5
mdefine_line|#define a5&t;$9
DECL|macro|ta1
mdefine_line|#define ta1&t;$9
DECL|macro|a6
mdefine_line|#define a6&t;$10
DECL|macro|ta2
mdefine_line|#define ta2&t;$10
DECL|macro|a7
mdefine_line|#define a7&t;$11
DECL|macro|ta3
mdefine_line|#define ta3&t;$11
DECL|macro|t0
mdefine_line|#define t0&t;$12&t;/* caller saved */
DECL|macro|t1
mdefine_line|#define t1&t;$13
DECL|macro|t2
mdefine_line|#define t2&t;$14
DECL|macro|t3
mdefine_line|#define t3&t;$15
DECL|macro|s0
mdefine_line|#define s0&t;$16&t;/* callee saved */
DECL|macro|s1
mdefine_line|#define s1&t;$17
DECL|macro|s2
mdefine_line|#define s2&t;$18
DECL|macro|s3
mdefine_line|#define s3&t;$19
DECL|macro|s4
mdefine_line|#define s4&t;$20
DECL|macro|s5
mdefine_line|#define s5&t;$21
DECL|macro|s6
mdefine_line|#define s6&t;$22
DECL|macro|s7
mdefine_line|#define s7&t;$23
DECL|macro|t8
mdefine_line|#define t8&t;$24&t;/* caller saved */
DECL|macro|t9
mdefine_line|#define t9&t;$25&t;/* callee address for PIC/temp */
DECL|macro|jp
mdefine_line|#define jp&t;$25&t;/* PIC jump register */
DECL|macro|k0
mdefine_line|#define k0&t;$26&t;/* kernel temporary */
DECL|macro|k1
mdefine_line|#define k1&t;$27
DECL|macro|gp
mdefine_line|#define gp&t;$28&t;/* global pointer - caller saved for PIC */
DECL|macro|sp
mdefine_line|#define sp&t;$29&t;/* stack pointer */
DECL|macro|fp
mdefine_line|#define fp&t;$30&t;/* frame pointer */
DECL|macro|s8
mdefine_line|#define s8&t;$30&t;/* callee saved */
DECL|macro|ra
mdefine_line|#define ra&t;$31&t;/* return address */
macro_line|#endif /* _MIPS_SIM == _MIPS_SIM_ABI64 || _MIPS_SIM == _MIPS_SIM_NABI32 */
macro_line|#endif /* _ASM_REGDEF_H */
eof
