macro_line|#ifndef _ASM_IRQ_H
DECL|macro|_ASM_IRQ_H
mdefine_line|#define _ASM_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm/irq.h&n; *&n; *&t;(C) 1992, 1993 Linus Torvalds, (C) 1997 Ingo Molnar&n; *&n; *&t;IRQ/IPI changes taken from work by Thomas Radke&n; *&t;&lt;tomsoft@informatik.tu-chemnitz.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/* include comes from machine specific directory */
macro_line|#include &quot;irq_vectors.h&quot;
macro_line|#include &lt;asm/thread_info.h&gt;
DECL|function|irq_canonicalize
r_static
id|__inline__
r_int
id|irq_canonicalize
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
(paren
(paren
id|irq
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
id|irq
)paren
suffix:semicolon
)brace
r_extern
r_void
id|release_vm86_irqs
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
DECL|macro|ARCH_HAS_NMI_WATCHDOG
macro_line|# define ARCH_HAS_NMI_WATCHDOG&t;&t;/* See include/linux/nmi.h */
macro_line|#endif
macro_line|#ifdef CONFIG_4KSTACKS
r_extern
r_void
id|irq_ctx_init
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
DECL|macro|__ARCH_HAS_DO_SOFTIRQ
macro_line|# define __ARCH_HAS_DO_SOFTIRQ
macro_line|#else
DECL|macro|irq_ctx_init
macro_line|# define irq_ctx_init(cpu) do { } while (0)
macro_line|#endif
macro_line|#endif /* _ASM_IRQ_H */
eof
