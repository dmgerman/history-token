multiline_comment|/*&n; * linux/arch/ia64/kernel/irq.c&n; *&n; * Copyright (C) 1998-2001 Hewlett-Packard Co&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; *  6/10/99: Updated to bring in sync with x86 version to facilitate&n; *&t;     support for SMP and different interrupt controllers.&n; *&n; * 09/15/00 Goutham Rao &lt;goutham.rao@intel.com&gt; Implemented pci_irq_to_vector&n; *                      PCI to vector allocation routine.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/jiffies.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/random.h&gt;&t;/* for rand_initialize_irq() */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifdef CONFIG_PERFMON
macro_line|# include &lt;asm/perfmon.h&gt;
macro_line|#endif
DECL|macro|IRQ_DEBUG
mdefine_line|#define IRQ_DEBUG&t;0
multiline_comment|/* default base addr of IPI table */
DECL|variable|ipi_base_addr
r_int
r_int
id|ipi_base_addr
op_assign
(paren
id|__IA64_UNCACHED_OFFSET
op_or
id|IA64_IPI_DEFAULT_BASE_ADDR
)paren
suffix:semicolon
multiline_comment|/*&n; * Legacy IRQ to IA-64 vector translation table.&n; */
DECL|variable|isa_irq_to_vector_map
id|__u8
id|isa_irq_to_vector_map
(braket
l_int|16
)braket
op_assign
(brace
multiline_comment|/* 8259 IRQ translation, first 16 entries */
l_int|0x2f
comma
l_int|0x20
comma
l_int|0x2e
comma
l_int|0x2d
comma
l_int|0x2c
comma
l_int|0x2b
comma
l_int|0x2a
comma
l_int|0x29
comma
l_int|0x28
comma
l_int|0x27
comma
l_int|0x26
comma
l_int|0x25
comma
l_int|0x24
comma
l_int|0x23
comma
l_int|0x22
comma
l_int|0x21
)brace
suffix:semicolon
r_int
DECL|function|ia64_alloc_vector
id|ia64_alloc_vector
(paren
r_void
)paren
(brace
r_static
r_int
id|next_vector
op_assign
id|IA64_FIRST_DEVICE_VECTOR
suffix:semicolon
r_if
c_cond
(paren
id|next_vector
OG
id|IA64_LAST_DEVICE_VECTOR
)paren
multiline_comment|/* XXX could look for sharable vectors instead of panic&squot;ing... */
id|panic
c_func
(paren
l_string|&quot;ia64_alloc_vector: out of interrupt vectors!&quot;
)paren
suffix:semicolon
r_return
id|next_vector
op_increment
suffix:semicolon
)brace
r_extern
r_int
r_int
id|do_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n; * That&squot;s where the IVT branches when we get an external&n; * interrupt. This branches to the correct hardware IRQ handler via&n; * function ptr.&n; */
r_void
DECL|function|ia64_handle_irq
id|ia64_handle_irq
(paren
id|ia64_vector
id|vector
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|saved_tpr
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|macro|IS_RESCHEDULE
macro_line|#&t;define IS_RESCHEDULE(vec)&t;(vec == IA64_IPI_RESCHEDULE)
macro_line|#else
macro_line|#&t;define IS_RESCHEDULE(vec)&t;(0)
macro_line|#endif
macro_line|#if IRQ_DEBUG
(brace
r_int
r_int
id|bsp
comma
id|sp
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Note: if the interrupt happened while executing in&n;&t;&t; * the context switch routine (ia64_switch_to), we may&n;&t;&t; * get a spurious stack overflow here.  This is&n;&t;&t; * because the register and the memory stack are not&n;&t;&t; * switched atomically.&n;&t;&t; */
id|asm
(paren
l_string|&quot;mov %0=ar.bsp&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|bsp
)paren
)paren
suffix:semicolon
id|asm
(paren
l_string|&quot;mov %0=sp&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sp
op_minus
id|bsp
)paren
OL
l_int|1024
)paren
(brace
r_static
r_int
r_char
id|count
suffix:semicolon
r_static
r_int
id|last_time
suffix:semicolon
r_if
c_cond
(paren
id|jiffies
op_minus
id|last_time
OG
l_int|5
op_star
id|HZ
)paren
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OL
l_int|5
)paren
(brace
id|last_time
op_assign
id|jiffies
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ia64_handle_irq: DANGER: less than &quot;
l_string|&quot;1KB of free stack space!!&bslash;n&quot;
l_string|&quot;(bsp=0x%lx, sp=%lx)&bslash;n&quot;
comma
id|bsp
comma
id|sp
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* IRQ_DEBUG */
multiline_comment|/*&n;&t; * Always set TPR to limit maximum interrupt nesting depth to&n;&t; * 16 (without this, it would be ~240, which could easily lead&n;&t; * to kernel stack overflows).&n;&t; */
id|saved_tpr
op_assign
id|ia64_get_tpr
c_func
(paren
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|vector
op_ne
id|IA64_SPURIOUS_INT_VECTOR
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|IS_RESCHEDULE
c_func
(paren
id|vector
)paren
)paren
(brace
id|ia64_set_tpr
c_func
(paren
id|vector
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
id|do_IRQ
c_func
(paren
id|local_vector_to_irq
c_func
(paren
id|vector
)paren
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Disable interrupts and send EOI:&n;&t;&t;&t; */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|ia64_set_tpr
c_func
(paren
id|saved_tpr
)paren
suffix:semicolon
)brace
id|ia64_eoi
c_func
(paren
)paren
suffix:semicolon
id|vector
op_assign
id|ia64_get_ivr
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This must be done *after* the ia64_eoi().  For example, the keyboard softirq&n;&t; * handler needs to be able to wait for further keyboard interrupts, which can&squot;t&n;&t; * come through until ia64_eoi() has been done.&n;&t; */
r_if
c_cond
(paren
id|local_softirq_pending
c_func
(paren
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_extern
id|irqreturn_t
id|handle_IPI
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|variable|ipi_irqaction
r_static
r_struct
id|irqaction
id|ipi_irqaction
op_assign
(brace
dot
id|handler
op_assign
id|handle_IPI
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
dot
id|name
op_assign
l_string|&quot;IPI&quot;
)brace
suffix:semicolon
macro_line|#endif
r_void
DECL|function|register_percpu_irq
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
(brace
id|irq_desc_t
op_star
id|desc
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
op_increment
id|irq
)paren
r_if
c_cond
(paren
id|irq_to_vector
c_func
(paren
id|irq
)paren
op_eq
id|vec
)paren
(brace
id|desc
op_assign
id|irq_descp
c_func
(paren
id|irq
)paren
suffix:semicolon
id|desc-&gt;status
op_or_assign
id|IRQ_PER_CPU
suffix:semicolon
id|desc-&gt;handler
op_assign
op_amp
id|irq_type_ia64_lsapic
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
id|setup_irq
c_func
(paren
id|irq
comma
id|action
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|init_IRQ
id|init_IRQ
(paren
r_void
)paren
(brace
id|register_percpu_irq
c_func
(paren
id|IA64_SPURIOUS_INT_VECTOR
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|register_percpu_irq
c_func
(paren
id|IA64_IPI_VECTOR
comma
op_amp
id|ipi_irqaction
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PERFMON
id|pfm_init_percpu
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|platform_irq_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia64_send_ipi
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
(brace
r_int
r_int
id|ipi_addr
suffix:semicolon
r_int
r_int
id|ipi_data
suffix:semicolon
r_int
r_int
id|phys_cpu_id
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|phys_cpu_id
op_assign
id|cpu_physical_id
c_func
(paren
id|cpu
)paren
suffix:semicolon
macro_line|#else
id|phys_cpu_id
op_assign
(paren
id|ia64_get_lid
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * cpu number is in 8bit ID and 8bit EID&n;&t; */
id|ipi_data
op_assign
(paren
id|delivery_mode
op_lshift
l_int|8
)paren
op_or
(paren
id|vector
op_amp
l_int|0xff
)paren
suffix:semicolon
id|ipi_addr
op_assign
id|ipi_base_addr
op_or
(paren
id|phys_cpu_id
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|redirect
op_amp
l_int|1
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|writeq
c_func
(paren
id|ipi_data
comma
id|ipi_addr
)paren
suffix:semicolon
)brace
eof
