macro_line|#ifndef _ASM_IRQ_VECTORS_LIMITS_H
DECL|macro|_ASM_IRQ_VECTORS_LIMITS_H
mdefine_line|#define _ASM_IRQ_VECTORS_LIMITS_H
macro_line|#ifdef CONFIG_PCI_MSI
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS FIRST_SYSTEM_VECTOR
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS NR_IRQS
macro_line|#else
macro_line|#ifdef CONFIG_X86_IO_APIC
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 224
macro_line|# if (224 &gt;= 32 * NR_CPUS)
DECL|macro|NR_IRQ_VECTORS
macro_line|# define NR_IRQ_VECTORS NR_IRQS
macro_line|# else
DECL|macro|NR_IRQ_VECTORS
macro_line|# define NR_IRQ_VECTORS (32 * NR_CPUS)
macro_line|# endif
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 16
DECL|macro|NR_IRQ_VECTORS
mdefine_line|#define NR_IRQ_VECTORS NR_IRQS
macro_line|#endif
macro_line|#endif
macro_line|#endif /* _ASM_IRQ_VECTORS_LIMITS_H */
eof
