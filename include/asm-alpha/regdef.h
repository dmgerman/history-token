macro_line|#ifndef __alpha_regdef_h__
DECL|macro|__alpha_regdef_h__
mdefine_line|#define __alpha_regdef_h__
DECL|macro|v0
mdefine_line|#define v0&t;$0&t;/* function return value */
DECL|macro|t0
mdefine_line|#define t0&t;$1&t;/* temporary registers (caller-saved) */
DECL|macro|t1
mdefine_line|#define t1&t;$2
DECL|macro|t2
mdefine_line|#define t2&t;$3
DECL|macro|t3
mdefine_line|#define t3&t;$4
DECL|macro|t4
mdefine_line|#define t4&t;$5
DECL|macro|t5
mdefine_line|#define t5&t;$6
DECL|macro|t6
mdefine_line|#define t6&t;$7
DECL|macro|t7
mdefine_line|#define t7&t;$8
DECL|macro|s0
mdefine_line|#define&t;s0&t;$9&t;/* saved-registers (callee-saved registers) */
DECL|macro|s1
mdefine_line|#define&t;s1&t;$10
DECL|macro|s2
mdefine_line|#define&t;s2&t;$11
DECL|macro|s3
mdefine_line|#define&t;s3&t;$12
DECL|macro|s4
mdefine_line|#define&t;s4&t;$13
DECL|macro|s5
mdefine_line|#define&t;s5&t;$14
DECL|macro|s6
mdefine_line|#define&t;s6&t;$15
DECL|macro|fp
mdefine_line|#define&t;fp&t;s6&t;/* frame-pointer (s6 in frame-less procedures) */
DECL|macro|a0
mdefine_line|#define a0&t;$16&t;/* argument registers (caller-saved) */
DECL|macro|a1
mdefine_line|#define a1&t;$17
DECL|macro|a2
mdefine_line|#define a2&t;$18
DECL|macro|a3
mdefine_line|#define a3&t;$19
DECL|macro|a4
mdefine_line|#define a4&t;$20
DECL|macro|a5
mdefine_line|#define a5&t;$21
DECL|macro|t8
mdefine_line|#define t8&t;$22&t;/* more temps (caller-saved) */
DECL|macro|t9
mdefine_line|#define t9&t;$23
DECL|macro|t10
mdefine_line|#define t10&t;$24
DECL|macro|t11
mdefine_line|#define t11&t;$25
DECL|macro|ra
mdefine_line|#define ra&t;$26&t;/* return address register */
DECL|macro|t12
mdefine_line|#define t12&t;$27
DECL|macro|pv
mdefine_line|#define pv&t;t12&t;/* procedure-variable register */
DECL|macro|AT
mdefine_line|#define AT&t;$at&t;/* assembler temporary */
DECL|macro|gp
mdefine_line|#define gp&t;$29&t;/* global pointer */
DECL|macro|sp
mdefine_line|#define sp&t;$30&t;/* stack pointer */
DECL|macro|zero
mdefine_line|#define zero&t;$31&t;/* reads as zero, writes are noops */
macro_line|#endif /* __alpha_regdef_h__ */
eof
