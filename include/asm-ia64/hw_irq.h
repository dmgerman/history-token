macro_line|#ifndef _ASM_IA64_HW_IRQ_H
DECL|macro|_ASM_IA64_HW_IRQ_H
mdefine_line|#define _ASM_IA64_HW_IRQ_H
multiline_comment|/*&n; * Copyright (C) 2001 Hewlett-Packard Co&n; * Copyright (C) 2001 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
DECL|typedef|ia64_vector
r_typedef
id|u8
id|ia64_vector
suffix:semicolon
multiline_comment|/*&n; * 0 special&n; *&n; * 1,3-14 are reserved from firmware&n; *&n; * 16-255 (vectored external interrupts) are available&n; *&n; * 15 spurious interrupt (see IVR)&n; *&n; * 16 lowest priority, 255 highest priority&n; *&n; * 15 classes of 16 interrupts each.&n; */
DECL|macro|IA64_MIN_VECTORED_IRQ
mdefine_line|#define IA64_MIN_VECTORED_IRQ&t;&t; 16
DECL|macro|IA64_MAX_VECTORED_IRQ
mdefine_line|#define IA64_MAX_VECTORED_IRQ&t;&t;255
DECL|macro|IA64_NUM_VECTORS
mdefine_line|#define IA64_NUM_VECTORS&t;&t;256
DECL|macro|IA64_SPURIOUS_INT_VECTOR
mdefine_line|#define IA64_SPURIOUS_INT_VECTOR&t;0x0f
multiline_comment|/*&n; * Vectors 0x10-0x1f are used for low priority interrupts, e.g. CMCI.&n; */
DECL|macro|IA64_PCE_VECTOR
mdefine_line|#define IA64_PCE_VECTOR&t;&t;&t;0x1e&t;/* platform corrected error interrupt vector */
DECL|macro|IA64_CMC_VECTOR
mdefine_line|#define IA64_CMC_VECTOR&t;&t;&t;0x1f&t;/* correctable machine-check interrupt vector */
multiline_comment|/*&n; * Vectors 0x20-0x2f are reserved for legacy ISA IRQs.&n; */
DECL|macro|IA64_FIRST_DEVICE_VECTOR
mdefine_line|#define IA64_FIRST_DEVICE_VECTOR&t;0x30
DECL|macro|IA64_LAST_DEVICE_VECTOR
mdefine_line|#define IA64_LAST_DEVICE_VECTOR&t;&t;0xe7
DECL|macro|IA64_MCA_RENDEZ_VECTOR
mdefine_line|#define IA64_MCA_RENDEZ_VECTOR&t;&t;0xe8&t;/* MCA rendez interrupt */
DECL|macro|IA64_PERFMON_VECTOR
mdefine_line|#define IA64_PERFMON_VECTOR&t;&t;0xee&t;/* performanc monitor interrupt vector */
DECL|macro|IA64_TIMER_VECTOR
mdefine_line|#define IA64_TIMER_VECTOR&t;&t;0xef&t;/* use highest-prio group 15 interrupt for timer */
DECL|macro|IA64_MCA_WAKEUP_VECTOR
mdefine_line|#define&t;IA64_MCA_WAKEUP_VECTOR&t;&t;0xf0&t;/* MCA wakeup (must be &gt;MCA_RENDEZ_VECTOR) */
DECL|macro|IA64_IPI_RESCHEDULE
mdefine_line|#define IA64_IPI_RESCHEDULE&t;&t;0xfd&t;/* SMP reschedule */
DECL|macro|IA64_IPI_VECTOR
mdefine_line|#define IA64_IPI_VECTOR&t;&t;&t;0xfe&t;/* inter-processor interrupt vector */
multiline_comment|/* IA64 inter-cpu interrupt related definitions */
DECL|macro|IA64_IPI_DEFAULT_BASE_ADDR
mdefine_line|#define IA64_IPI_DEFAULT_BASE_ADDR&t;0xfee00000
multiline_comment|/* Delivery modes for inter-cpu interrupts */
r_enum
(brace
DECL|enumerator|IA64_IPI_DM_INT
id|IA64_IPI_DM_INT
op_assign
l_int|0x0
comma
multiline_comment|/* pend an external interrupt */
DECL|enumerator|IA64_IPI_DM_PMI
id|IA64_IPI_DM_PMI
op_assign
l_int|0x2
comma
multiline_comment|/* pend a PMI */
DECL|enumerator|IA64_IPI_DM_NMI
id|IA64_IPI_DM_NMI
op_assign
l_int|0x4
comma
multiline_comment|/* pend an NMI (vector 2) */
DECL|enumerator|IA64_IPI_DM_INIT
id|IA64_IPI_DM_INIT
op_assign
l_int|0x5
comma
multiline_comment|/* pend an INIT interrupt */
DECL|enumerator|IA64_IPI_DM_EXTINT
id|IA64_IPI_DM_EXTINT
op_assign
l_int|0x7
comma
multiline_comment|/* pend an 8259-compatible interrupt. */
)brace
suffix:semicolon
r_extern
id|__u8
id|isa_irq_to_vector_map
(braket
l_int|16
)braket
suffix:semicolon
DECL|macro|isa_irq_to_vector
mdefine_line|#define isa_irq_to_vector(x)&t;isa_irq_to_vector_map[(x)]
r_extern
r_int
r_int
id|ipi_base_addr
suffix:semicolon
r_extern
r_struct
id|hw_interrupt_type
id|irq_type_ia64_lsapic
suffix:semicolon
multiline_comment|/* CPU-internal interrupt controller */
r_extern
r_int
id|ia64_alloc_irq
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* allocate a free irq */
r_extern
r_void
id|ia64_send_ipi
(paren
r_int
id|cpu
comma
r_int
id|vector
comma
r_int
id|delivery_mode
comma
r_int
id|redirect
)paren
suffix:semicolon
r_extern
r_void
id|register_percpu_irq
(paren
id|ia64_vector
id|vec
comma
r_struct
id|irqaction
op_star
id|action
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|hw_resend_irq
id|hw_resend_irq
(paren
r_struct
id|hw_interrupt_type
op_star
id|h
comma
r_int
r_int
id|vector
)paren
(brace
id|platform_send_ipi
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|vector
comma
id|IA64_IPI_DM_INT
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Default implementations for the irq-descriptor API:&n; */
r_extern
r_struct
id|irq_desc
id|_irq_desc
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_static
r_inline
r_struct
id|irq_desc
op_star
DECL|function|__ia64_irq_desc
id|__ia64_irq_desc
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
id|_irq_desc
op_plus
id|irq
suffix:semicolon
)brace
r_static
r_inline
id|ia64_vector
DECL|function|__ia64_irq_to_vector
id|__ia64_irq_to_vector
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
(paren
id|ia64_vector
)paren
id|irq
suffix:semicolon
)brace
r_static
r_inline
r_int
r_int
DECL|function|__ia64_local_vector_to_irq
id|__ia64_local_vector_to_irq
(paren
id|ia64_vector
id|vec
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|vec
suffix:semicolon
)brace
multiline_comment|/*&n; * Next follows the irq descriptor interface.  On IA-64, each CPU supports 256 interrupt&n; * vectors.  On smaller systems, there is a one-to-one correspondence between interrupt&n; * vectors and the Linux irq numbers.  However, larger systems may have multiple interrupt&n; * domains meaning that the translation from vector number to irq number depends on the&n; * interrupt domain that a CPU belongs to.  This API abstracts such platform-dependent&n; * differences and provides a uniform means to translate between vector and irq numbers&n; * and to obtain the irq descriptor for a given irq number.&n; */
multiline_comment|/* Return a pointer to the irq descriptor for IRQ.  */
r_static
r_inline
r_struct
id|irq_desc
op_star
DECL|function|irq_desc
id|irq_desc
(paren
r_int
id|irq
)paren
(brace
r_return
id|platform_irq_desc
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/* Extract the IA-64 vector that corresponds to IRQ.  */
r_static
r_inline
id|ia64_vector
DECL|function|irq_to_vector
id|irq_to_vector
(paren
r_int
id|irq
)paren
(brace
r_return
id|platform_irq_to_vector
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert the local IA-64 vector to the corresponding irq number.  This translation is&n; * done in the context of the interrupt domain that the currently executing CPU belongs&n; * to.&n; */
r_static
r_inline
r_int
r_int
DECL|function|local_vector_to_irq
id|local_vector_to_irq
(paren
id|ia64_vector
id|vec
)paren
(brace
r_return
id|platform_local_vector_to_irq
c_func
(paren
id|vec
)paren
suffix:semicolon
)brace
macro_line|#endif /* _ASM_IA64_HW_IRQ_H */
eof
