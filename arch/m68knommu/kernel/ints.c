multiline_comment|/*&n; * linux/arch/m68knommu/kernel/ints.c -- General interrupt handling code&n; *&n; * Copyright (C) 1999-2002  Greg Ungerer (gerg@snapgear.com)&n; * Copyright (C) 1998  D. Jeff Dionne &lt;jeff@lineo.ca&gt;,&n; *                     Kenneth Albanowski &lt;kjahds@kjahds.com&gt;,&n; * Copyright (C) 2000  Lineo Inc. (www.lineo.com) &n; *&n; * Based on:&n; *&n; * linux/arch/m68k/kernel/ints.c -- Linux/m68k general interrupt handling code&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/*&n; *&t;This table stores the address info for each vector handler.&n; */
DECL|variable|irq_list
id|irq_handler_t
id|irq_list
(braket
id|SYS_IRQS
)braket
suffix:semicolon
DECL|variable|mach_kstat_irqs
r_int
r_int
op_star
id|mach_kstat_irqs
suffix:semicolon
DECL|macro|NUM_IRQ_NODES
mdefine_line|#define NUM_IRQ_NODES 16
DECL|variable|nodes
r_static
id|irq_node_t
id|nodes
(braket
id|NUM_IRQ_NODES
)braket
suffix:semicolon
multiline_comment|/* The number of spurious interrupts */
DECL|variable|num_spurious
r_volatile
r_int
r_int
id|num_spurious
suffix:semicolon
DECL|variable|local_bh_count
r_int
r_int
id|local_bh_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|local_irq_count
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|default_irq_handler
r_static
r_void
id|default_irq_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|ptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;%s(%d): default irq handler vec=%d [0x%x]&bslash;n&quot;
comma
id|__FILE__
comma
id|__LINE__
comma
id|irq
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * void init_IRQ(void)&n; *&n; * Parameters:&t;None&n; *&n; * Returns:&t;Nothing&n; *&n; * This function should be called during kernel startup to initialize&n; * the IRQ handling routines.&n; */
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
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
id|SYS_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mach_default_handler
)paren
id|irq_list
(braket
id|i
)braket
dot
id|handler
op_assign
(paren
op_star
id|mach_default_handler
)paren
(braket
id|i
)braket
suffix:semicolon
r_else
id|irq_list
(braket
id|i
)braket
dot
id|handler
op_assign
id|default_irq_handler
suffix:semicolon
id|irq_list
(braket
id|i
)braket
dot
id|flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
id|irq_list
(braket
id|i
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_list
(braket
id|i
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_IRQ_NODES
suffix:semicolon
id|i
op_increment
)paren
id|nodes
(braket
id|i
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|mach_init_IRQ
)paren
id|mach_init_IRQ
c_func
(paren
)paren
suffix:semicolon
id|mach_kstat_irqs
op_assign
op_amp
id|kstat.irqs
(braket
l_int|0
)braket
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|new_irq_node
id|irq_node_t
op_star
id|new_irq_node
c_func
(paren
r_void
)paren
(brace
id|irq_node_t
op_star
id|node
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
id|nodes
comma
id|i
op_assign
id|NUM_IRQ_NODES
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|node
op_increment
comma
id|i
op_decrement
)paren
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;handler
)paren
r_return
id|node
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;new_irq_node: out of nodes&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
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
id|flags
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
r_if
c_cond
(paren
id|irq
OL
l_int|0
op_logical_or
id|irq
op_ge
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_amp
id|IRQ_FLG_STD
)paren
)paren
(brace
r_if
c_cond
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_amp
id|IRQ_FLG_LOCK
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: IRQ %d from %s is not replaceable&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|IRQ_FLG_REPLACE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: %s can&squot;t replace IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|devname
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_COLDFIRE
r_if
c_cond
(paren
id|flags
op_amp
id|IRQ_FLG_FAST
)paren
(brace
r_extern
id|asmlinkage
r_void
id|fasthandler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_evector
c_func
(paren
r_int
id|vecnum
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
id|set_evector
c_func
(paren
id|irq
comma
id|fasthandler
)paren
suffix:semicolon
)brace
macro_line|#endif
id|irq_list
(braket
id|irq
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_assign
id|flags
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|dev_id
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|devname
op_assign
id|devname
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
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d&bslash;n&quot;
comma
id|__FUNCTION__
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
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_ne
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Removing probably wrong IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_COLDFIRE
r_if
c_cond
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_amp
id|IRQ_FLG_FAST
)paren
(brace
r_extern
id|asmlinkage
r_void
id|inthandler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_evector
c_func
(paren
r_int
id|vecnum
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
id|set_evector
c_func
(paren
id|irq
comma
id|inthandler
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|mach_default_handler
)paren
id|irq_list
(braket
id|irq
)braket
dot
id|handler
op_assign
(paren
op_star
id|mach_default_handler
)paren
(braket
id|irq
)braket
suffix:semicolon
r_else
id|irq_list
(braket
id|irq
)braket
dot
id|handler
op_assign
id|default_irq_handler
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|sys_request_irq
r_int
id|sys_request_irq
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
id|flags
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
r_if
c_cond
(paren
id|irq
OG
id|IRQ7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_amp
id|IRQ_FLG_STD
)paren
)paren
(brace
r_if
c_cond
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_amp
id|IRQ_FLG_LOCK
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: IRQ %d from %s is not replaceable&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|IRQ_FLG_REPLACE
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: %s can&squot;t replace IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|devname
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
macro_line|#endif
id|irq_list
(braket
id|irq
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_assign
id|flags
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|dev_id
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|devname
op_assign
id|devname
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_free_irq
r_void
id|sys_free_irq
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
r_if
c_cond
(paren
id|irq
OG
id|IRQ7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d&bslash;n&quot;
comma
id|__FUNCTION__
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
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_ne
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Removing probably wrong IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|handler
op_assign
(paren
op_star
id|mach_default_handler
)paren
(braket
id|irq
)braket
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Do we need these probe functions on the m68k?&n; *&n; *  ... may be usefull with ISA devices&n; */
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
DECL|function|process_int
id|asmlinkage
r_void
id|process_int
c_func
(paren
r_int
r_int
id|vec
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_if
c_cond
(paren
id|vec
op_ge
id|VEC_INT1
op_logical_and
id|vec
op_le
id|VEC_INT7
)paren
(brace
id|vec
op_sub_assign
id|VEC_SPUR
suffix:semicolon
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|vec
)braket
op_increment
suffix:semicolon
id|irq_list
(braket
id|vec
)braket
dot
id|handler
c_func
(paren
id|vec
comma
id|irq_list
(braket
id|vec
)braket
dot
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mach_process_int
)paren
id|mach_process_int
c_func
(paren
id|vec
comma
id|fp
)paren
suffix:semicolon
r_else
id|panic
c_func
(paren
l_string|&quot;Can&squot;t process interrupt vector %ld&bslash;n&quot;
comma
id|vec
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|irq_list
(braket
id|i
)braket
dot
id|flags
op_amp
id|IRQ_FLG_STD
)paren
r_continue
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%3d: %10u &quot;
comma
id|i
comma
(paren
id|i
ques
c_cond
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|i
)braket
suffix:colon
id|num_spurious
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_list
(braket
id|i
)braket
dot
id|flags
op_amp
id|IRQ_FLG_LOCK
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;L &quot;
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|irq_list
(braket
id|i
)braket
dot
id|devname
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mach_get_irq_list
)paren
id|mach_get_irq_list
c_func
(paren
id|p
comma
id|v
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_irq_proc
r_void
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Insert /proc/irq driver here */
)brace
eof
