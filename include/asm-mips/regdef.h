multiline_comment|/*&n; * include/asm-mips/regdefs.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 1995 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_REGDEF_H
DECL|macro|__ASM_MIPS_REGDEF_H
mdefine_line|#define __ASM_MIPS_REGDEF_H
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
macro_line|#endif /* __ASM_MIPS_REGDEF_H */
eof
