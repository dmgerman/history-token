macro_line|#ifndef _ASM_IRQ_VECTORS_LIMITS_H
DECL|macro|_ASM_IRQ_VECTORS_LIMITS_H
mdefine_line|#define _ASM_IRQ_VECTORS_LIMITS_H
multiline_comment|/*&n; * For Summit or generic (i.e. installer) kernels, we have lots of I/O APICs,&n; * even with uni-proc kernels, so use a big array.&n; *&n; * This value should be the same in both the generic and summit subarches.&n; * Change one, change &squot;em both.&n; */
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS&t;224
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS&t;1024
macro_line|#endif /* _ASM_IRQ_VECTORS_LIMITS_H */
eof
