multiline_comment|/*  $Id: sun4d_irq.c,v 1.29 2001/12/11 04:55:51 davem Exp $&n; *  arch/sparc/kernel/sun4d_irq.c:&n; *&t;&t;&t;SS1000/SC2000 interrupt handling.&n; *&n; *  Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *  Heavily based on arch/sparc/kernel/irq.c.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/vaddrs.h&gt;
macro_line|#include &lt;asm/timer.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/sbi.h&gt;
multiline_comment|/* If you trust current SCSI layer to handle different SCSI IRQs, enable this. I don&squot;t trust it... -jj */
multiline_comment|/* #define DISTRIBUTE_IRQS */
DECL|variable|sun4d_timers
r_struct
id|sun4d_timer_regs
op_star
id|sun4d_timers
suffix:semicolon
DECL|macro|TIMER_IRQ
mdefine_line|#define TIMER_IRQ&t;10
DECL|macro|MAX_STATIC_ALLOC
mdefine_line|#define MAX_STATIC_ALLOC&t;4
r_extern
r_struct
id|irqaction
id|static_irqaction
(braket
id|MAX_STATIC_ALLOC
)braket
suffix:semicolon
r_extern
r_int
id|static_irq_count
suffix:semicolon
DECL|variable|cpu_leds
r_int
r_char
id|cpu_leds
(braket
l_int|32
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|sbus_tid
r_int
r_char
id|sbus_tid
(braket
l_int|32
)braket
suffix:semicolon
macro_line|#endif
r_extern
r_struct
id|irqaction
op_star
id|irq_action
(braket
)braket
suffix:semicolon
DECL|struct|sbus_action
r_struct
id|sbus_action
(brace
DECL|member|action
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
multiline_comment|/* For SMP this needs to be extended */
DECL|variable|sbus_actions
)brace
op_star
id|sbus_actions
suffix:semicolon
DECL|variable|pil_to_sbus
r_static
r_int
id|pil_to_sbus
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|3
comma
l_int|0
comma
l_int|4
comma
l_int|0
comma
l_int|5
comma
l_int|0
comma
l_int|6
comma
l_int|0
comma
l_int|7
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|sbus_to_pil
r_static
r_int
id|sbus_to_pil
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|2
comma
l_int|3
comma
l_int|5
comma
l_int|7
comma
l_int|9
comma
l_int|11
comma
l_int|13
comma
)brace
suffix:semicolon
DECL|variable|nsbi
r_static
r_int
id|nsbi
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|sun4d_imsk_lock
id|spinlock_t
id|sun4d_imsk_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#endif
DECL|function|show_sun4d_interrupts
r_int
id|show_sun4d_interrupts
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
op_assign
l_int|0
comma
id|k
op_assign
l_int|0
comma
id|sbusl
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_int
id|x
suffix:semicolon
macro_line|#endif
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
id|sbusl
op_assign
id|pil_to_sbus
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbusl
)paren
(brace
id|action
op_assign
op_star
(paren
id|i
op_plus
id|irq_action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_continue
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|nsbi
suffix:semicolon
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|4
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
(paren
id|action
op_assign
id|sbus_actions
(braket
(paren
id|j
op_lshift
l_int|5
)paren
op_plus
(paren
id|sbusl
op_lshift
l_int|2
)paren
op_plus
id|k
)braket
dot
id|action
)paren
)paren
r_goto
id|found_it
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|found_it
suffix:colon
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
macro_line|#ifndef CONFIG_SMP
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
macro_line|#else
r_for
c_loop
(paren
id|x
op_assign
l_int|0
suffix:semicolon
id|x
OL
id|NR_CPUS
suffix:semicolon
id|x
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_online
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
id|cpu_logical_map
c_func
(paren
id|x
)paren
)braket
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%c %s&quot;
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_char|&squot;+&squot;
suffix:colon
l_char|&squot; &squot;
comma
id|action-&gt;name
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;,%s %s&quot;
comma
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
ques
c_cond
l_string|&quot; +&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sbusl
)paren
r_break
suffix:semicolon
id|k
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|k
OL
l_int|4
)paren
id|action
op_assign
id|sbus_actions
(braket
(paren
id|j
op_lshift
l_int|5
)paren
op_plus
(paren
id|sbusl
op_lshift
l_int|2
)paren
op_plus
id|k
)braket
dot
id|action
suffix:semicolon
r_else
(brace
id|j
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|nsbi
)paren
r_break
suffix:semicolon
id|k
op_assign
l_int|0
suffix:semicolon
id|action
op_assign
id|sbus_actions
(braket
(paren
id|j
op_lshift
l_int|5
)paren
op_plus
(paren
id|sbusl
op_lshift
l_int|2
)paren
)braket
dot
id|action
suffix:semicolon
)brace
)brace
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sun4d_free_irq
r_void
id|sun4d_free_irq
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
r_struct
id|irqaction
op_star
id|action
comma
op_star
op_star
id|actionp
suffix:semicolon
r_struct
id|irqaction
op_star
id|tmp
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|15
)paren
id|actionp
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
r_else
id|actionp
op_assign
op_amp
(paren
id|sbus_actions
(braket
id|irq
op_minus
(paren
l_int|1
op_lshift
l_int|5
)paren
)braket
dot
id|action
)paren
suffix:semicolon
id|action
op_assign
op_star
id|actionp
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
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev_id
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dev_id
op_eq
id|dev_id
)paren
r_break
suffix:semicolon
id|tmp
op_assign
id|action
suffix:semicolon
)brace
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
l_string|&quot;Trying to free free shared IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_SHIRQ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free shared IRQ%d with NULL device ID&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|action-&gt;flags
op_amp
id|SA_STATIC_ALLOC
)paren
(brace
multiline_comment|/* This interrupt is marked as specially allocated&n;&t;     * so it is a bad idea to free it.&n;&t;     */
id|printk
c_func
(paren
l_string|&quot;Attempt to free statically allocated IRQ%d (%s)&bslash;n&quot;
comma
id|irq
comma
id|action-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_logical_and
id|tmp
)paren
id|tmp-&gt;next
op_assign
id|action-&gt;next
suffix:semicolon
r_else
op_star
id|actionp
op_assign
id|action-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|actionp
)paren
)paren
id|disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_extern
r_void
id|unexpected_irq
c_func
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
suffix:semicolon
DECL|function|sun4d_handler_irq
r_void
id|sun4d_handler_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
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
multiline_comment|/* SBUS IRQ level (1 - 7) */
r_int
id|sbusl
op_assign
id|pil_to_sbus
(braket
id|irq
)braket
suffix:semicolon
multiline_comment|/* FIXME: Is this necessary?? */
id|cc_get_ipen
c_func
(paren
)paren
suffix:semicolon
id|cc_set_iclr
c_func
(paren
l_int|1
op_lshift
id|irq
)paren
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
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
r_if
c_cond
(paren
op_logical_neg
id|sbusl
)paren
(brace
id|action
op_assign
op_star
(paren
id|irq
op_plus
id|irq_action
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
id|unexpected_irq
c_func
(paren
id|irq
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
r_do
(brace
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
)brace
r_else
(brace
r_int
id|bus_mask
op_assign
id|bw_get_intr_mask
c_func
(paren
id|sbusl
)paren
op_amp
l_int|0x3ffff
suffix:semicolon
r_int
id|sbino
suffix:semicolon
r_struct
id|sbus_action
op_star
id|actionp
suffix:semicolon
r_int
id|mask
comma
id|slot
suffix:semicolon
r_int
id|sbil
op_assign
(paren
id|sbusl
op_lshift
l_int|2
)paren
suffix:semicolon
id|bw_clear_intr_mask
c_func
(paren
id|sbusl
comma
id|bus_mask
)paren
suffix:semicolon
multiline_comment|/* Loop for each pending SBI */
r_for
c_loop
(paren
id|sbino
op_assign
l_int|0
suffix:semicolon
id|bus_mask
suffix:semicolon
id|sbino
op_increment
comma
id|bus_mask
op_rshift_assign
l_int|1
)paren
r_if
c_cond
(paren
id|bus_mask
op_amp
l_int|1
)paren
(brace
id|mask
op_assign
id|acquire_sbi
c_func
(paren
id|SBI2DEVID
c_func
(paren
id|sbino
)paren
comma
l_int|0xf
op_lshift
id|sbil
)paren
suffix:semicolon
id|mask
op_and_assign
(paren
l_int|0xf
op_lshift
id|sbil
)paren
suffix:semicolon
id|actionp
op_assign
id|sbus_actions
op_plus
(paren
id|sbino
op_lshift
l_int|5
)paren
op_plus
(paren
id|sbil
)paren
suffix:semicolon
multiline_comment|/* Loop for each pending SBI slot */
r_for
c_loop
(paren
id|slot
op_assign
(paren
l_int|1
op_lshift
id|sbil
)paren
suffix:semicolon
id|mask
suffix:semicolon
id|slot
op_lshift_assign
l_int|1
comma
id|actionp
op_increment
)paren
r_if
c_cond
(paren
id|mask
op_amp
id|slot
)paren
(brace
id|mask
op_and_assign
op_complement
id|slot
suffix:semicolon
id|action
op_assign
id|actionp-&gt;action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
id|unexpected_irq
c_func
(paren
id|irq
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
r_do
(brace
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
id|release_sbi
c_func
(paren
id|SBI2DEVID
c_func
(paren
id|sbino
)paren
comma
id|slot
)paren
suffix:semicolon
)brace
)brace
)brace
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sun4d_build_irq
r_int
r_int
id|sun4d_build_irq
c_func
(paren
r_struct
id|sbus_dev
op_star
id|sdev
comma
r_int
id|irq
)paren
(brace
r_int
id|sbusl
op_assign
id|pil_to_sbus
(braket
id|irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sbusl
)paren
r_return
(paren
(paren
id|sdev-&gt;bus-&gt;board
op_plus
l_int|1
)paren
op_lshift
l_int|5
)paren
op_plus
(paren
id|sbusl
op_lshift
l_int|2
)paren
op_plus
id|sdev-&gt;slot
suffix:semicolon
r_else
r_return
id|irq
suffix:semicolon
)brace
DECL|function|sun4d_request_irq
r_int
id|sun4d_request_irq
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
comma
op_star
id|tmp
op_assign
l_int|NULL
comma
op_star
op_star
id|actionp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
OG
l_int|14
op_logical_and
id|irq
OL
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
id|actionp
op_assign
op_amp
(paren
id|sbus_actions
(braket
id|irq
op_minus
(paren
l_int|1
op_lshift
l_int|5
)paren
)braket
dot
id|action
)paren
suffix:semicolon
r_else
id|actionp
op_assign
id|irq
op_plus
id|irq_action
suffix:semicolon
id|action
op_assign
op_star
id|actionp
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
r_if
c_cond
(paren
(paren
id|action-&gt;flags
op_amp
id|SA_SHIRQ
)paren
op_logical_and
(paren
id|irqflags
op_amp
id|SA_SHIRQ
)paren
)paren
(brace
r_for
c_loop
(paren
id|tmp
op_assign
id|action
suffix:semicolon
id|tmp-&gt;next
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
op_xor
(paren
id|irqflags
op_amp
id|SA_INTERRUPT
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Attempt to mix fast and slow interrupts on IRQ%d denied&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|action
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Or else! */
)brace
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* If this is flagged as statically allocated then we use our&n;&t; * private struct which is never freed.&n;&t; */
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_STATIC_ALLOC
)paren
(brace
r_if
c_cond
(paren
id|static_irq_count
OL
id|MAX_STATIC_ALLOC
)paren
id|action
op_assign
op_amp
id|static_irqaction
(braket
id|static_irq_count
op_increment
)braket
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;Request for IRQ%d (%s) SA_STATIC_ALLOC failed using kmalloc&bslash;n&quot;
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|action
op_eq
l_int|NULL
)paren
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|kmalloc
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
id|restore_flags
c_func
(paren
id|flags
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
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
id|tmp-&gt;next
op_assign
id|action
suffix:semicolon
r_else
op_star
id|actionp
op_assign
id|action
suffix:semicolon
id|enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sun4d_disable_irq
r_static
r_void
id|sun4d_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
id|tid
op_assign
id|sbus_tid
(braket
(paren
id|irq
op_rshift
l_int|5
)paren
op_minus
l_int|1
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif&t;
r_if
c_cond
(paren
id|irq
OL
id|NR_IRQS
)paren
r_return
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sun4d_imsk_lock
comma
id|flags
)paren
suffix:semicolon
id|cc_set_imsk_other
c_func
(paren
id|tid
comma
id|cc_get_imsk_other
c_func
(paren
id|tid
)paren
op_or
(paren
l_int|1
op_lshift
id|sbus_to_pil
(braket
(paren
id|irq
op_rshift
l_int|2
)paren
op_amp
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sun4d_imsk_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#else&t;&t;
id|cc_set_imsk
c_func
(paren
id|cc_get_imsk
c_func
(paren
)paren
op_or
(paren
l_int|1
op_lshift
id|sbus_to_pil
(braket
(paren
id|irq
op_rshift
l_int|2
)paren
op_amp
l_int|7
)braket
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|sun4d_enable_irq
r_static
r_void
id|sun4d_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
id|tid
op_assign
id|sbus_tid
(braket
(paren
id|irq
op_rshift
l_int|5
)paren
op_minus
l_int|1
)braket
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#endif&t;
r_if
c_cond
(paren
id|irq
OL
id|NR_IRQS
)paren
r_return
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sun4d_imsk_lock
comma
id|flags
)paren
suffix:semicolon
id|cc_set_imsk_other
c_func
(paren
id|tid
comma
id|cc_get_imsk_other
c_func
(paren
id|tid
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
id|sbus_to_pil
(braket
(paren
id|irq
op_rshift
l_int|2
)paren
op_amp
l_int|7
)braket
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sun4d_imsk_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#else&t;&t;
id|cc_set_imsk
c_func
(paren
id|cc_get_imsk
c_func
(paren
)paren
op_amp
op_complement
(paren
l_int|1
op_lshift
id|sbus_to_pil
(braket
(paren
id|irq
op_rshift
l_int|2
)paren
op_amp
l_int|7
)braket
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|sun4d_set_cpu_int
r_static
r_void
id|sun4d_set_cpu_int
c_func
(paren
r_int
id|cpu
comma
r_int
id|level
)paren
(brace
id|sun4d_send_ipi
c_func
(paren
id|cpu
comma
id|level
)paren
suffix:semicolon
)brace
DECL|function|sun4d_clear_ipi
r_static
r_void
id|sun4d_clear_ipi
c_func
(paren
r_int
id|cpu
comma
r_int
id|level
)paren
(brace
)brace
DECL|function|sun4d_set_udt
r_static
r_void
id|sun4d_set_udt
c_func
(paren
r_int
id|cpu
)paren
(brace
)brace
multiline_comment|/* Setup IRQ distribution scheme. */
DECL|function|sun4d_distribute_irqs
r_void
id|__init
id|sun4d_distribute_irqs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef DISTRIBUTE_IRQS
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_int
r_int
id|sbus_serving_map
suffix:semicolon
id|sbus_serving_map
op_assign
id|cpu_present_map
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
r_if
c_cond
(paren
(paren
id|sbus-&gt;board
op_star
l_int|2
)paren
op_eq
id|boot_cpu_id
op_logical_and
(paren
id|cpu_present_map
op_amp
(paren
l_int|1
op_lshift
(paren
id|sbus-&gt;board
op_star
l_int|2
op_plus
l_int|1
)paren
)paren
)paren
)paren
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_assign
(paren
id|sbus-&gt;board
op_star
l_int|2
op_plus
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cpu_present_map
op_amp
(paren
l_int|1
op_lshift
(paren
id|sbus-&gt;board
op_star
l_int|2
)paren
)paren
)paren
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_assign
(paren
id|sbus-&gt;board
op_star
l_int|2
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|cpu_present_map
op_amp
(paren
l_int|1
op_lshift
(paren
id|sbus-&gt;board
op_star
l_int|2
op_plus
l_int|1
)paren
)paren
)paren
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_assign
(paren
id|sbus-&gt;board
op_star
l_int|2
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_ne
l_int|0xff
)paren
id|sbus_serving_map
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
)paren
suffix:semicolon
)brace
id|for_each_sbus
c_func
(paren
id|sbus
)paren
r_if
c_cond
(paren
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_eq
l_int|0xff
)paren
(brace
r_int
id|i
op_assign
l_int|31
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sbus_serving_map
)paren
id|sbus_serving_map
op_assign
id|cpu_present_map
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|sbus_serving_map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
id|i
op_decrement
suffix:semicolon
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_assign
id|i
suffix:semicolon
id|sbus_serving_map
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sbus%d IRQs directed to CPU%d&bslash;n&quot;
comma
id|sbus-&gt;board
comma
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
)paren
suffix:semicolon
id|set_sbi_tid
c_func
(paren
id|sbus-&gt;devid
comma
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_lshift
l_int|3
)paren
suffix:semicolon
)brace
macro_line|#else
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_int
id|cpuid
op_assign
id|cpu_logical_map
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpuid
op_eq
op_minus
l_int|1
)paren
id|cpuid
op_assign
id|cpu_logical_map
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_assign
id|cpuid
suffix:semicolon
id|set_sbi_tid
c_func
(paren
id|sbus-&gt;devid
comma
id|cpuid
op_lshift
l_int|3
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;All sbus IRQs directed to CPU%d&bslash;n&quot;
comma
id|cpuid
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
DECL|function|sun4d_clear_clock_irq
r_static
r_void
id|sun4d_clear_clock_irq
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
id|clear_intr
suffix:semicolon
id|clear_intr
op_assign
id|sun4d_timers-&gt;l10_timer_limit
suffix:semicolon
)brace
DECL|function|sun4d_clear_profile_irq
r_static
r_void
id|sun4d_clear_profile_irq
c_func
(paren
r_int
id|cpu
)paren
(brace
id|bw_get_prof_limit
c_func
(paren
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|sun4d_load_profile_irq
r_static
r_void
id|sun4d_load_profile_irq
c_func
(paren
r_int
id|cpu
comma
r_int
r_int
id|limit
)paren
(brace
id|bw_set_prof_limit
c_func
(paren
id|cpu
comma
id|limit
)paren
suffix:semicolon
)brace
DECL|function|sun4d_init_timers
r_static
r_void
id|__init
id|sun4d_init_timers
c_func
(paren
r_void
(paren
op_star
id|counter_fn
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
)paren
(brace
r_int
id|irq
suffix:semicolon
r_extern
r_struct
id|prom_cpuinfo
id|linux_cpus
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_struct
id|resource
id|r
suffix:semicolon
multiline_comment|/* Map the User Timer registers. */
id|memset
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|r.start
op_assign
id|CSR_BASE
c_func
(paren
id|boot_cpu_id
)paren
op_plus
id|BW_TIMER_LIMIT
suffix:semicolon
macro_line|#else
id|r.start
op_assign
id|CSR_BASE
c_func
(paren
l_int|0
)paren
op_plus
id|BW_TIMER_LIMIT
suffix:semicolon
macro_line|#endif
id|r.flags
op_assign
l_int|0xf
suffix:semicolon
id|sun4d_timers
op_assign
(paren
r_struct
id|sun4d_timer_regs
op_star
)paren
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
id|PAGE_SIZE
comma
l_string|&quot;user timer&quot;
)paren
suffix:semicolon
id|sun4d_timers-&gt;l10_timer_limit
op_assign
(paren
(paren
(paren
l_int|1000000
op_div
id|HZ
)paren
op_plus
l_int|1
)paren
op_lshift
l_int|10
)paren
suffix:semicolon
id|master_l10_counter
op_assign
op_amp
id|sun4d_timers-&gt;l10_cur_count
suffix:semicolon
id|master_l10_limit
op_assign
op_amp
id|sun4d_timers-&gt;l10_timer_limit
suffix:semicolon
id|irq
op_assign
id|request_irq
c_func
(paren
id|TIMER_IRQ
comma
id|counter_fn
comma
(paren
id|SA_INTERRUPT
op_or
id|SA_STATIC_ALLOC
)paren
comma
l_string|&quot;timer&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;time_init: unable to attach IRQ%d&bslash;n&quot;
comma
id|TIMER_IRQ
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable user timer free run for CPU 0 in BW */
multiline_comment|/* bw_set_ctrl(0, bw_get_ctrl(0) | BW_CTRL_USER_TIMER); */
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|linux_num_cpus
suffix:semicolon
id|cpu
op_increment
)paren
(brace
id|sun4d_load_profile_irq
c_func
(paren
(paren
id|linux_cpus
(braket
id|cpu
)braket
dot
id|mid
op_rshift
l_int|3
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
(brace
r_int
r_int
id|flags
suffix:semicolon
r_extern
r_int
r_int
id|lvl14_save
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|tt_entry
op_star
id|trap_table
op_assign
op_amp
id|sparc_ttable
(braket
id|SP_TRAP_IRQ1
op_plus
(paren
l_int|14
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_extern
r_int
r_int
id|real_irq_entry
(braket
)braket
comma
id|smp4d_ticker
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|patchme_maybe_smp_msg
(braket
)braket
suffix:semicolon
multiline_comment|/* Adjust so that we jump directly to smp4d_ticker */
id|lvl14_save
(braket
l_int|2
)braket
op_add_assign
id|smp4d_ticker
op_minus
id|real_irq_entry
suffix:semicolon
multiline_comment|/* For SMP we use the level 14 ticker, however the bootup code&n;&t;&t; * has copied the firmwares level 14 vector into boot cpu&squot;s&n;&t;&t; * trap table, we must fix this now or we get squashed.&n;&t;&t; */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|patchme_maybe_smp_msg
(braket
l_int|0
)braket
op_assign
l_int|0x01000000
suffix:semicolon
multiline_comment|/* NOP out the branch */
id|trap_table-&gt;inst_one
op_assign
id|lvl14_save
(braket
l_int|0
)braket
suffix:semicolon
id|trap_table-&gt;inst_two
op_assign
id|lvl14_save
(braket
l_int|1
)braket
suffix:semicolon
id|trap_table-&gt;inst_three
op_assign
id|lvl14_save
(braket
l_int|2
)braket
suffix:semicolon
id|trap_table-&gt;inst_four
op_assign
id|lvl14_save
(braket
l_int|3
)braket
suffix:semicolon
id|local_flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|sun4d_init_sbi_irq
r_void
id|__init
id|sun4d_init_sbi_irq
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_int
id|mask
suffix:semicolon
id|nsbi
op_assign
l_int|0
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
id|nsbi
op_increment
suffix:semicolon
id|sbus_actions
op_assign
(paren
r_struct
id|sbus_action
op_star
)paren
id|kmalloc
(paren
id|nsbi
op_star
l_int|8
op_star
l_int|4
op_star
r_sizeof
(paren
r_struct
id|sbus_action
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
(paren
id|sbus_actions
comma
l_int|0
comma
(paren
id|nsbi
op_star
l_int|8
op_star
l_int|4
op_star
r_sizeof
(paren
r_struct
id|sbus_action
)paren
)paren
)paren
suffix:semicolon
id|for_each_sbus
c_func
(paren
id|sbus
)paren
(brace
macro_line|#ifdef CONFIG_SMP&t;
r_extern
r_int
r_char
id|boot_cpu_id
suffix:semicolon
id|set_sbi_tid
c_func
(paren
id|sbus-&gt;devid
comma
id|boot_cpu_id
op_lshift
l_int|3
)paren
suffix:semicolon
id|sbus_tid
(braket
id|sbus-&gt;board
)braket
op_assign
id|boot_cpu_id
suffix:semicolon
macro_line|#endif
multiline_comment|/* Get rid of pending irqs from PROM */
id|mask
op_assign
id|acquire_sbi
c_func
(paren
id|sbus-&gt;devid
comma
l_int|0xffffffff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mask
)paren
(brace
id|printk
(paren
l_string|&quot;Clearing pending IRQs %08x on SBI %d&bslash;n&quot;
comma
id|mask
comma
id|sbus-&gt;board
)paren
suffix:semicolon
id|release_sbi
c_func
(paren
id|sbus-&gt;devid
comma
id|mask
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|sun4d_irq_itoa
r_static
r_char
op_star
id|sun4d_irq_itoa
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_static
r_char
id|buff
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%d&quot;
comma
id|irq
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|buff
comma
l_string|&quot;%d,%x&quot;
comma
id|sbus_to_pil
(braket
(paren
id|irq
op_rshift
l_int|2
)paren
op_amp
l_int|7
)braket
comma
id|irq
)paren
suffix:semicolon
r_return
id|buff
suffix:semicolon
)brace
DECL|function|sun4d_init_IRQ
r_void
id|__init
id|sun4d_init_IRQ
c_func
(paren
r_void
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|enable_irq
comma
id|sun4d_enable_irq
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|disable_irq
comma
id|sun4d_disable_irq
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|clear_clock_irq
comma
id|sun4d_clear_clock_irq
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|clear_profile_irq
comma
id|sun4d_clear_profile_irq
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|load_profile_irq
comma
id|sun4d_load_profile_irq
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|__irq_itoa
comma
id|sun4d_irq_itoa
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|sparc_init_timers
op_assign
id|sun4d_init_timers
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|BTFIXUPSET_CALL
c_func
(paren
id|set_cpu_int
comma
id|sun4d_set_cpu_int
comma
id|BTFIXUPCALL_NORM
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|clear_cpu_int
comma
id|sun4d_clear_ipi
comma
id|BTFIXUPCALL_NOP
)paren
suffix:semicolon
id|BTFIXUPSET_CALL
c_func
(paren
id|set_irq_udt
comma
id|sun4d_set_udt
comma
id|BTFIXUPCALL_NOP
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Cannot enable interrupts until OBP ticker is disabled. */
)brace
eof
