multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; *  arch/ppc/kernel/irq.c&n; *&n; *  Derived from arch/i386/kernel/irq.c&n; *    Copyright (C) 1992 Linus Torvalds&n; *  Adapted from arch/i386 by Gary Thomas&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *  Updated and modified by Cort Dougan &lt;cort@fsmlabs.com&gt;&n; *    Copyright (C) 1996-2001 Cort Dougan&n; *  Adapted for Power Macintosh by Paul Mackerras&n; *    Copyright (C) 1996 Paul Mackerras (paulus@cs.anu.edu.au)&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *  &n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; *&n; * The MPC8xx has an interrupt mask in the SIU.  If a bit is set, the&n; * interrupt is _enabled_.  As expected, IRQ0 is bit 0 in the 32-bit&n; * mask register (of which only 16 are defined), hence the weird shifting&n; * and compliment of the cached_irq_mask.  I want to be able to stuff&n; * this right into the SIU SMASK register.&n; * Many of the prep/chrp functions are conditional compiled on CONFIG_8xx&n; * to reduce code space and undefined function references.&n; */
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|macro|NR_MASK_WORDS
mdefine_line|#define NR_MASK_WORDS&t;((NR_IRQS + 31) / 32)
r_extern
id|atomic_t
id|ipi_recv
suffix:semicolon
r_extern
id|atomic_t
id|ipi_sent
suffix:semicolon
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
suffix:semicolon
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
suffix:semicolon
r_static
r_void
id|register_irq_proc
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 10000000
DECL|variable|__cacheline_aligned
id|irq_desc_t
id|irq_desc
(braket
id|NR_IRQS
)braket
id|__cacheline_aligned
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NR_IRQS
op_minus
l_int|1
)braket
op_assign
(brace
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
id|SPIN_LOCK_UNLOCKED
)brace
)brace
suffix:semicolon
DECL|variable|ppc_spurious_interrupts
r_int
id|ppc_spurious_interrupts
op_assign
l_int|0
suffix:semicolon
DECL|variable|ppc_irq_action
r_struct
id|irqaction
op_star
id|ppc_irq_action
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|variable|ppc_cached_irq_mask
r_int
r_int
id|ppc_cached_irq_mask
(braket
id|NR_MASK_WORDS
)braket
suffix:semicolon
DECL|variable|ppc_lost_interrupts
r_int
r_int
id|ppc_lost_interrupts
(braket
id|NR_MASK_WORDS
)braket
suffix:semicolon
DECL|variable|ppc_n_lost_interrupts
id|atomic_t
id|ppc_n_lost_interrupts
suffix:semicolon
multiline_comment|/* nasty hack for shared irq&squot;s since we need to do kmalloc calls but&n; * can&squot;t very early in the boot when we need to do a request irq.&n; * this needs to be removed.&n; * -- Cort&n; */
DECL|macro|IRQ_KMALLOC_ENTRIES
mdefine_line|#define IRQ_KMALLOC_ENTRIES 8
DECL|variable|cache_bitmask
r_static
r_int
id|cache_bitmask
op_assign
l_int|0
suffix:semicolon
DECL|variable|malloc_cache
r_static
r_struct
id|irqaction
id|malloc_cache
(braket
id|IRQ_KMALLOC_ENTRIES
)braket
suffix:semicolon
r_extern
r_int
id|mem_init_done
suffix:semicolon
macro_line|#if defined(CONFIG_TAU_INT)
r_extern
r_int
id|tau_interrupts
c_func
(paren
r_int
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_int
id|tau_initialized
suffix:semicolon
macro_line|#endif
DECL|function|irq_kmalloc
r_void
op_star
id|irq_kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|pri
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|pri
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IRQ_KMALLOC_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|cache_bitmask
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
(brace
id|cache_bitmask
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
op_amp
id|malloc_cache
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irq_kfree
r_void
id|irq_kfree
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IRQ_KMALLOC_ENTRIES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ptr
op_eq
op_amp
id|malloc_cache
(braket
id|i
)braket
)paren
(brace
id|cache_bitmask
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
r_int
DECL|function|setup_irq
id|setup_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
(brace
r_int
id|shared
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|irqaction
op_star
id|old
comma
op_star
op_star
id|p
suffix:semicolon
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * Some drivers like serial.c use request_irq() heavily,&n;&t; * so we have to be careful not to interfere with a&n;&t; * running system.&n;&t; */
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
(brace
multiline_comment|/*&n;&t;&t; * This function might sleep, we want to call it first,&n;&t;&t; * outside of the atomic block.&n;&t;&t; * Yes, this might clear the entropy pool if the wrong&n;&t;&t; * driver is attempted to be loaded, without actually&n;&t;&t; * installing a new handler, but is this really a problem,&n;&t;&t; * only the sysadmin is able to do this.&n;&t;&t; */
id|rand_initialize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The following block of code has to be executed atomically&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Can&squot;t share interrupts unless both agree to */
r_if
c_cond
(paren
op_logical_neg
(paren
id|old-&gt;flags
op_amp
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SHIRQ
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* add new interrupt at end of irq queue */
r_do
(brace
id|p
op_assign
op_amp
id|old-&gt;next
suffix:semicolon
id|old
op_assign
op_star
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old
)paren
suffix:semicolon
id|shared
op_assign
l_int|1
suffix:semicolon
)brace
op_star
id|p
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared
)paren
(brace
id|desc-&gt;depth
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;status
op_and_assign
op_complement
(paren
id|IRQ_DISABLED
op_or
id|IRQ_AUTODETECT
op_or
id|IRQ_WAITING
)paren
suffix:semicolon
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|register_irq_proc
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|irq_desc_t
op_star
id|desc
suffix:semicolon
r_struct
id|irqaction
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|desc-&gt;action
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
r_struct
id|irqaction
op_star
op_star
id|pp
op_assign
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* Found it - now remove it from the list of entries */
op_star
id|pp
op_assign
id|action-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;action
)paren
(brace
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|synchronize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irq_kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|request_irq
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
multiline_comment|/*&n;&t;&t; * free_irq() used to be implemented as a call to&n;&t;&t; * request_irq() with handler being NULL.  Now we have&n;&t;&t; * a real free_irq() but need to allow the old behavior&n;&t;&t; * for old code that hasn&squot;t caught up yet.&n;&t;&t; *  -- Cort &lt;cort@fsmlabs.com&gt;&n;&t;&t; */
id|free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|irq_kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;irq_kmalloc() failed for irq %d !&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|action-&gt;handler
op_assign
id|handler
suffix:semicolon
id|action-&gt;flags
op_assign
id|irqflags
suffix:semicolon
id|action-&gt;mask
op_assign
l_int|0
suffix:semicolon
id|action-&gt;name
op_assign
id|devname
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|retval
op_assign
id|setup_irq
c_func
(paren
id|irq
comma
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic enable/disable code: this just calls&n; * down into the PIC-specific version for the actual&n; * hardware disable after having gotten the irq&n; * controller lock. &n; */
multiline_comment|/**&n; *&t;disable_irq_nosync - disable an irq without waiting&n; *&t;@irq: Interrupt to disable&n; *&n; *&t;Disable the selected interrupt line. Disables of an interrupt&n; *&t;stack. Unlike disable_irq(), this function does not ensure existing&n; *&t;instances of the IRQ handler have completed before returning.&n; *&n; *&t;This function may be called from IRQ context.&n; */
DECL|function|disable_irq_nosync
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;depth
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|desc-&gt;status
op_amp
id|IRQ_PER_CPU
)paren
)paren
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;disable_irq - disable an irq and wait for completion&n; *&t;@irq: Interrupt to disable&n; *&n; *&t;Disable the selected interrupt line. Disables of an interrupt&n; *&t;stack. That is for two disables you need two enables. This&n; *&t;function waits for any pending IRQ handlers for this interrupt&n; *&t;to complete before returning. If you use this function while&n; *&t;holding a resource the IRQ handler may need you will deadlock.&n; *&n; *&t;This function may be called - with care - from IRQ context.&n; */
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|disable_irq_nosync
c_func
(paren
id|irq
)paren
suffix:semicolon
id|synchronize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;enable_irq - enable interrupt handling on an irq&n; *&t;@irq: Interrupt to enable&n; *&n; *&t;Re-enables the processing of interrupts on this IRQ line&n; *&t;providing no disable_irq calls are now in effect.&n; *&n; *&t;This function may be called from IRQ context.&n; */
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|desc-&gt;depth
)paren
(brace
r_case
l_int|1
suffix:colon
(brace
r_int
r_int
id|status
op_assign
id|desc-&gt;status
op_amp
op_complement
id|IRQ_DISABLED
suffix:semicolon
id|desc-&gt;status
op_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
id|IRQ_PENDING
op_or
id|IRQ_REPLAY
)paren
)paren
op_eq
id|IRQ_PENDING
)paren
(brace
id|desc-&gt;status
op_assign
id|status
op_or
id|IRQ_REPLAY
suffix:semicolon
id|hw_resend_irq
c_func
(paren
id|desc-&gt;handler
comma
id|irq
)paren
suffix:semicolon
)brace
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* fall-through */
)brace
r_default
suffix:colon
id|desc-&gt;depth
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
id|printk
c_func
(paren
l_string|&quot;enable_irq(%u) unbalanced&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|show_interrupts
r_int
id|show_interrupts
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;           &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_CPUS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|j
)paren
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;CPU%d       &quot;
comma
id|j
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|action
op_assign
id|irq_desc
(braket
id|i
)braket
dot
id|action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
op_logical_or
op_logical_neg
id|action-&gt;handler
)paren
r_continue
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%3d: &quot;
comma
id|i
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_CPUS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|j
)paren
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat.irqs
(braket
id|j
)braket
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#else&t;&t;
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat_irqs
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %s &quot;
comma
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_member_access_from_pointer
r_typename
)paren
suffix:semicolon
r_else
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;  None      &quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%s&quot;
comma
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_amp
id|IRQ_LEVEL
)paren
ques
c_cond
l_string|&quot;Level &quot;
suffix:colon
l_string|&quot;Edge  &quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;    %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;, %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_TAU_INT
r_if
c_cond
(paren
id|tau_initialized
)paren
(brace
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;TAU: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_CPUS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|j
)paren
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|tau_interrupts
c_func
(paren
id|j
)paren
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;  PowerPC             Thermal Assist (cpu temp)&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* should this be per processor send/receive? */
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;IPI (recv/sent): %10u/%u&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|ipi_recv
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|ipi_sent
)paren
)paren
suffix:semicolon
macro_line|#endif&t;&t;
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;BAD: %10u&bslash;n&quot;
comma
id|ppc_spurious_interrupts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|handle_irq_event
id|handle_irq_event
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|irqaction
op_star
id|action
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|status
op_or_assign
id|action-&gt;flags
suffix:semicolon
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Eventually, this should take an array of interrupts and an array size&n; * so it can dispatch multiple interrupts.&n; */
DECL|function|ppc_irq_dispatch_handler
r_void
id|ppc_irq_dispatch_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|irq
)paren
(brace
r_int
id|status
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|kstat.irqs
(braket
id|cpu
)braket
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|ack_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   REPLAY is when Linux resends an IRQ that was dropped earlier&n;&t;   WAITING is used by probe to mark irqs that are being tested&n;&t;   */
id|status
op_assign
id|desc-&gt;status
op_amp
op_complement
(paren
id|IRQ_REPLAY
op_or
id|IRQ_WAITING
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_PER_CPU
)paren
)paren
id|status
op_or_assign
id|IRQ_PENDING
suffix:semicolon
multiline_comment|/* we _want_ to handle it */
multiline_comment|/*&n;&t; * If the IRQ is disabled for whatever reason, we cannot&n;&t; * use the action we have.&n;&t; */
id|action
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
)paren
(brace
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
op_logical_or
op_logical_neg
id|action-&gt;handler
)paren
(brace
id|ppc_spurious_interrupts
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Unhandled interrupt %x, disabled&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* We can&squot;t call disable_irq here, it would deadlock */
op_increment
id|desc-&gt;depth
suffix:semicolon
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* This is a real interrupt, we have to eoi it,&n;&t;&t;&t;   so we jump to out */
r_goto
id|out
suffix:semicolon
)brace
id|status
op_and_assign
op_complement
id|IRQ_PENDING
suffix:semicolon
multiline_comment|/* we commit to handling */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_PER_CPU
)paren
)paren
id|status
op_or_assign
id|IRQ_INPROGRESS
suffix:semicolon
multiline_comment|/* we are handling it */
)brace
id|desc-&gt;status
op_assign
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * If there is no IRQ handler or it was disabled, exit early.&n;&t;   Since we set PENDING, if another processor is handling&n;&t;   a different instance of this same irq, the other processor&n;&t;   will take care of it.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|action
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Edge triggered interrupts need to remember&n;&t; * pending events.&n;&t; * This applies to any hw interrupts that allow a second&n;&t; * instance of the same irq to arrive while we are in do_IRQ&n;&t; * or in the handler. But the code here only handles the _second_&n;&t; * instance of the irq, not the third or fourth. So it is mostly&n;&t; * useful for irq hardware that does not mask cleanly in an&n;&t; * SMP environment.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|handle_irq_event
c_func
(paren
id|irq
comma
id|regs
comma
id|action
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|desc-&gt;status
op_amp
id|IRQ_PENDING
)paren
)paren
)paren
r_break
suffix:semicolon
id|desc-&gt;status
op_and_assign
op_complement
id|IRQ_PENDING
suffix:semicolon
)brace
id|out
suffix:colon
id|desc-&gt;status
op_and_assign
op_complement
id|IRQ_INPROGRESS
suffix:semicolon
multiline_comment|/*&n;&t; * The -&gt;end() handler has to deal with interrupts which got&n;&t; * disabled while the handler was running.&n;&t; */
r_if
c_cond
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
)paren
(brace
r_if
c_cond
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler-&gt;end
)paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_member_access_from_pointer
id|end
c_func
(paren
id|irq
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler-&gt;enable
)paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_member_access_from_pointer
id|enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_PPC_ISERIES&t;/* iSeries version is in iSeries_pic.c */
DECL|function|do_IRQ
r_void
id|do_IRQ
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
comma
id|first
op_assign
l_int|1
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Every platform is required to implement ppc_md.get_irq.&n;&t; * This function will either return an irq number or -1 to&n;&t; * indicate there are no more pending.  But the first time&n;&t; * through the loop this means there wasn&squot;t and IRQ pending.&n;&t; * The value -2 is for buggy hardware and means that this IRQ&n;&t; * has already been handled. -- Tom&n;&t; */
r_while
c_loop
(paren
(paren
id|irq
op_assign
id|ppc_md
dot
id|get_irq
c_func
(paren
id|regs
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|ppc_irq_dispatch_handler
c_func
(paren
id|regs
comma
id|irq
)paren
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ne
op_minus
l_int|2
op_logical_and
id|first
)paren
multiline_comment|/* That&squot;s not SMP safe ... but who cares ? */
id|ppc_spurious_interrupts
op_increment
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_ISERIES */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_irq_off
r_int
id|probe_irq_off
(paren
r_int
r_int
id|irqs
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_irq_mask
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
id|irqs
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|once
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|once
)paren
r_return
suffix:semicolon
r_else
id|once
op_increment
suffix:semicolon
id|ppc_md
dot
id|init_IRQ
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|synchronize_irq
r_void
id|synchronize_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_while
c_loop
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
id|IRQ_INPROGRESS
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
DECL|variable|root_irq_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|root_irq_dir
suffix:semicolon
DECL|variable|irq_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|irq_dir
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|variable|smp_affinity_entry
r_static
r_struct
id|proc_dir_entry
op_star
id|smp_affinity_entry
(braket
id|NR_IRQS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_IRQ_ALL_CPUS
DECL|macro|DEFAULT_CPU_AFFINITY
mdefine_line|#define DEFAULT_CPU_AFFINITY 0xffffffff
macro_line|#else
DECL|macro|DEFAULT_CPU_AFFINITY
mdefine_line|#define DEFAULT_CPU_AFFINITY 0x00000001
macro_line|#endif
DECL|variable|irq_affinity
r_int
r_int
id|irq_affinity
(braket
id|NR_IRQS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NR_IRQS
op_minus
l_int|1
)braket
op_assign
id|DEFAULT_CPU_AFFINITY
)brace
suffix:semicolon
DECL|macro|HEX_DIGITS
mdefine_line|#define HEX_DIGITS 8
DECL|function|irq_affinity_read_proc
r_static
r_int
id|irq_affinity_read_proc
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|count
OL
id|HEX_DIGITS
op_plus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|sprintf
(paren
id|page
comma
l_string|&quot;%08x&bslash;n&quot;
comma
id|irq_affinity
(braket
(paren
r_int
)paren
id|data
)braket
)paren
suffix:semicolon
)brace
DECL|function|parse_hex_value
r_static
r_int
r_int
id|parse_hex_value
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_int
r_int
op_star
id|ret
)paren
(brace
r_int
r_char
id|hexnum
(braket
id|HEX_DIGITS
)braket
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|HEX_DIGITS
)paren
id|count
op_assign
id|HEX_DIGITS
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|hexnum
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t; * Parse the first 8 characters as a hex string, any non-hex char&n;&t; * is end-of-string. &squot;00e1&squot;, &squot;e1&squot;, &squot;00E1&squot;, &squot;E1&squot; are all the same.&n;&t; */
id|value
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|c
op_assign
id|hexnum
(braket
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;0&squot;
dot
dot
dot
l_char|&squot;9&squot;
suffix:colon
id|c
op_sub_assign
l_char|&squot;0&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
dot
dot
dot
l_char|&squot;f&squot;
suffix:colon
id|c
op_sub_assign
l_char|&squot;a&squot;
op_minus
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;A&squot;
dot
dot
dot
l_char|&squot;F&squot;
suffix:colon
id|c
op_sub_assign
l_char|&squot;A&squot;
op_minus
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|out
suffix:semicolon
)brace
id|value
op_assign
(paren
id|value
op_lshift
l_int|4
)paren
op_or
id|c
suffix:semicolon
)brace
id|out
suffix:colon
op_star
id|ret
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|irq_affinity_write_proc
r_static
r_int
id|irq_affinity_write_proc
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|irq
op_assign
(paren
r_int
)paren
id|data
comma
id|full_count
op_assign
id|count
comma
id|err
suffix:semicolon
r_int
r_int
id|new_value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_desc
(braket
id|irq
)braket
dot
id|handler-&gt;set_affinity
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|err
op_assign
id|parse_hex_value
c_func
(paren
id|buffer
comma
id|count
comma
op_amp
id|new_value
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do not allow disabling IRQs completely - it&squot;s a too easy&n;&t; * way to make the system unusable accidentally :-) At least&n;&t; * one online CPU still has to be targeted.&n;&t; *&n;&t; * We assume a 1-1 logical&lt;-&gt;physical cpu mapping here.  If&n;&t; * we assume that the cpu indices in /proc/irq/../smp_affinity&n;&t; * are actually logical cpu #&squot;s then we have no problem.&n;&t; *  -- Cort &lt;cort@fsmlabs.com&gt;&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|new_value
op_amp
id|cpu_online_map
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|irq_affinity
(braket
id|irq
)braket
op_assign
id|new_value
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_member_access_from_pointer
id|set_affinity
c_func
(paren
id|irq
comma
id|new_value
)paren
suffix:semicolon
r_return
id|full_count
suffix:semicolon
)brace
DECL|function|prof_cpu_mask_read_proc
r_static
r_int
id|prof_cpu_mask_read_proc
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
op_star
id|mask
op_assign
(paren
r_int
r_int
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|HEX_DIGITS
op_plus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|sprintf
(paren
id|page
comma
l_string|&quot;%08lx&bslash;n&quot;
comma
op_star
id|mask
)paren
suffix:semicolon
)brace
DECL|function|prof_cpu_mask_write_proc
r_static
r_int
id|prof_cpu_mask_write_proc
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
op_star
id|mask
op_assign
(paren
r_int
r_int
op_star
)paren
id|data
comma
id|full_count
op_assign
id|count
comma
id|err
suffix:semicolon
r_int
r_int
id|new_value
suffix:semicolon
id|err
op_assign
id|parse_hex_value
c_func
(paren
id|buffer
comma
id|count
comma
op_amp
id|new_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
op_star
id|mask
op_assign
id|new_value
suffix:semicolon
r_return
id|full_count
suffix:semicolon
)brace
DECL|macro|MAX_NAMELEN
mdefine_line|#define MAX_NAMELEN 10
DECL|function|register_irq_proc
r_static
r_void
id|register_irq_proc
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_char
id|name
(braket
id|MAX_NAMELEN
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_irq_dir
op_logical_or
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_eq
l_int|NULL
)paren
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|name
comma
l_int|0
comma
id|MAX_NAMELEN
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/1234 */
id|irq_dir
(braket
id|irq
)braket
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|root_irq_dir
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/1234/smp_affinity */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;smp_affinity&quot;
comma
l_int|0600
comma
id|irq_dir
(braket
id|irq
)braket
)paren
suffix:semicolon
id|entry-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|entry-&gt;data
op_assign
(paren
r_void
op_star
)paren
id|irq
suffix:semicolon
id|entry-&gt;read_proc
op_assign
id|irq_affinity_read_proc
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|irq_affinity_write_proc
suffix:semicolon
id|smp_affinity_entry
(braket
id|irq
)braket
op_assign
id|entry
suffix:semicolon
)brace
DECL|variable|prof_cpu_mask
r_int
r_int
id|prof_cpu_mask
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|init_irq_proc
r_void
id|init_irq_proc
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* create /proc/irq */
id|root_irq_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;irq&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/prof_cpu_mask */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;prof_cpu_mask&quot;
comma
l_int|0600
comma
id|root_irq_dir
)paren
suffix:semicolon
id|entry-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|entry-&gt;data
op_assign
(paren
r_void
op_star
)paren
op_amp
id|prof_cpu_mask
suffix:semicolon
id|entry-&gt;read_proc
op_assign
id|prof_cpu_mask_read_proc
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|prof_cpu_mask_write_proc
suffix:semicolon
multiline_comment|/*&n;&t; * Create entries for all existing IRQs.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|register_irq_proc
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|no_action
r_void
id|no_action
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
)brace
eof
