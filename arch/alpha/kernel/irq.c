multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/irq.c&n; *&n; *&t;Copyright (C) 1995 Linus Torvalds&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Controller mappings for all interrupt sources:&n; */
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
dot
id|handler
op_assign
op_amp
id|no_irq_type
comma
dot
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
)brace
)brace
suffix:semicolon
r_static
r_void
id|register_irq_proc
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|variable|irq_err_count
r_volatile
r_int
r_int
id|irq_err_count
suffix:semicolon
multiline_comment|/*&n; * Special irq handlers.&n; */
DECL|function|no_action
id|irqreturn_t
id|no_action
c_func
(paren
r_int
id|cpl
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
(brace
r_return
id|IRQ_NONE
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic no controller code&n; */
DECL|function|no_irq_enable_disable
r_static
r_void
id|no_irq_enable_disable
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|no_irq_startup
r_static
r_int
r_int
id|no_irq_startup
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|no_irq_ack
id|no_irq_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_err_count
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Unexpected IRQ trap at vector %u&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|no_irq_type
r_struct
id|hw_interrupt_type
id|no_irq_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;none&quot;
comma
dot
id|startup
op_assign
id|no_irq_startup
comma
dot
id|shutdown
op_assign
id|no_irq_enable_disable
comma
dot
id|enable
op_assign
id|no_irq_enable_disable
comma
dot
id|disable
op_assign
id|no_irq_enable_disable
comma
dot
id|ack
op_assign
id|no_irq_ack
comma
dot
id|end
op_assign
id|no_irq_enable_disable
comma
)brace
suffix:semicolon
r_int
DECL|function|handle_IRQ_event
id|handle_IRQ_event
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
l_int|1
suffix:semicolon
multiline_comment|/* Force the &quot;do bottom halves&quot; bit */
r_do
(brace
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
r_else
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
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
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic enable/disable code: this just calls&n; * down into the PIC-specific version for the actual&n; * hardware disable after having gotten the irq&n; * controller lock. &n; */
r_void
r_inline
DECL|function|disable_irq_nosync
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
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|disable
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
multiline_comment|/*&n; * Synchronous version of the above, making sure the IRQ is&n; * no longer running on any other IRQ..&n; */
r_void
DECL|function|disable_irq
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
r_void
DECL|function|enable_irq
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
id|desc-&gt;handler
op_member_access_from_pointer
id|enable
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
id|KERN_ERR
l_string|&quot;enable_irq() unbalanced from %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
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
r_struct
id|irqaction
op_star
id|old
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;handler
op_eq
op_amp
id|no_irq_type
)paren
r_return
op_minus
id|ENOSYS
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
op_or
id|IRQ_INPROGRESS
)paren
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|startup
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
r_return
l_int|0
suffix:semicolon
)brace
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
macro_line|#ifdef CONFIG_SMP 
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
DECL|variable|irq_user_affinity
r_static
r_char
id|irq_user_affinity
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|variable|irq_affinity
r_static
id|cpumask_t
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
id|CPU_MASK_ALL
)brace
suffix:semicolon
r_static
r_void
DECL|function|select_smp_affinity
id|select_smp_affinity
c_func
(paren
r_int
id|irq
)paren
(brace
r_static
r_int
id|last_cpu
suffix:semicolon
r_int
id|cpu
op_assign
id|last_cpu
op_plus
l_int|1
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
op_logical_or
id|irq_user_affinity
(braket
id|irq
)braket
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|cpu
)paren
)paren
id|cpu
op_assign
(paren
id|cpu
OL
(paren
id|NR_CPUS
op_minus
l_int|1
)paren
ques
c_cond
id|cpu
op_plus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|last_cpu
op_assign
id|cpu
suffix:semicolon
id|irq_affinity
(braket
id|irq
)braket
op_assign
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
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
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|irq_affinity_read_proc
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
r_int
id|len
op_assign
id|cpumask_scnprintf
c_func
(paren
id|page
comma
id|count
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
r_if
c_cond
(paren
id|count
op_minus
id|len
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|irq_affinity_write_proc
id|irq_affinity_write_proc
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
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
id|cpumask_t
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
id|cpumask_parse
c_func
(paren
id|buffer
comma
id|count
comma
id|new_value
)paren
suffix:semicolon
multiline_comment|/* The special value 0 means release control of the&n;&t;   affinity to kernel.  */
id|cpus_and
c_func
(paren
id|new_value
comma
id|new_value
comma
id|cpu_online_map
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|new_value
)paren
)paren
(brace
id|irq_user_affinity
(braket
id|irq
)braket
op_assign
l_int|0
suffix:semicolon
id|select_smp_affinity
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/* Do not allow disabling IRQs completely - it&squot;s a too easy&n;&t;   way to make the system unusable accidentally :-) At least&n;&t;   one online CPU still has to be targeted.  */
r_else
(brace
id|irq_affinity
(braket
id|irq
)braket
op_assign
id|new_value
suffix:semicolon
id|irq_user_affinity
(braket
id|irq
)braket
op_assign
l_int|1
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
)brace
r_return
id|full_count
suffix:semicolon
)brace
r_static
r_int
DECL|function|prof_cpu_mask_read_proc
id|prof_cpu_mask_read_proc
c_func
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
id|len
op_assign
id|cpumask_scnprintf
c_func
(paren
id|page
comma
id|count
comma
op_star
(paren
id|cpumask_t
op_star
)paren
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_minus
id|len
OL
l_int|2
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
r_static
r_int
DECL|function|prof_cpu_mask_write_proc
id|prof_cpu_mask_write_proc
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
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
id|full_count
op_assign
id|count
comma
id|err
suffix:semicolon
id|cpumask_t
id|new_value
comma
op_star
id|mask
op_assign
(paren
id|cpumask_t
op_star
)paren
id|data
suffix:semicolon
id|err
op_assign
id|cpumask_parse
c_func
(paren
id|buffer
comma
id|count
comma
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
macro_line|#endif /* CONFIG_SMP */
DECL|macro|MAX_NAMELEN
mdefine_line|#define MAX_NAMELEN 10
r_static
r_void
DECL|function|register_irq_proc
id|register_irq_proc
(paren
r_int
r_int
id|irq
)paren
(brace
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
op_amp
id|no_irq_type
)paren
op_logical_or
id|irq_dir
(braket
id|irq
)braket
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
macro_line|#ifdef CONFIG_SMP 
r_if
c_cond
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler-&gt;set_affinity
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
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
r_if
c_cond
(paren
id|entry
)paren
(brace
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
(paren
r_int
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
)brace
id|smp_affinity_entry
(braket
id|irq
)braket
op_assign
id|entry
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|variable|prof_cpu_mask
r_int
r_int
id|prof_cpu_mask
op_assign
op_complement
l_int|0UL
suffix:semicolon
r_void
DECL|function|init_irq_proc
id|init_irq_proc
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
macro_line|#endif
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
macro_line|#ifdef CONFIG_SMP 
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
macro_line|#endif
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
id|ACTUAL_NR_IRQS
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
op_amp
id|no_irq_type
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
r_int
DECL|function|request_irq
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
id|irqreturn_t
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
r_int
id|retval
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|ACTUAL_NR_IRQS
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
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#if 1
multiline_comment|/*&n;&t; * Sanity-check: shared interrupts should REALLY pass in&n;&t; * a real dev-ID, otherwise we&squot;ll have trouble later trying&n;&t; * to figure out which interrupt is which (messes up the&n;&t; * interrupt freeing logic etc).&n;&t; */
r_if
c_cond
(paren
(paren
id|irqflags
op_amp
id|SA_SHIRQ
)paren
op_logical_and
op_logical_neg
id|dev_id
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Bad boy: %s (at %p) called us without a dev_id!&bslash;n&quot;
comma
id|devname
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|action-&gt;handler
op_assign
id|handler
suffix:semicolon
id|action-&gt;flags
op_assign
id|irqflags
suffix:semicolon
id|cpus_clear
c_func
(paren
id|action-&gt;mask
)paren
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
macro_line|#ifdef CONFIG_SMP
id|select_smp_affinity
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#endif
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
DECL|variable|request_irq
id|EXPORT_SYMBOL
c_func
(paren
id|request_irq
)paren
suffix:semicolon
r_void
DECL|function|free_irq
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
r_if
c_cond
(paren
id|irq
op_ge
id|ACTUAL_NR_IRQS
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Trying to free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
multiline_comment|/* Found - now remove it from the list of entries.  */
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
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
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
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Wait to make sure it&squot;s not being used on&n;&t;&t;&t;   another CPU.  */
r_while
c_loop
(paren
id|desc-&gt;status
op_amp
id|IRQ_INPROGRESS
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|kfree
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
id|KERN_ERR
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
r_return
suffix:semicolon
)brace
)brace
DECL|variable|free_irq
id|EXPORT_SYMBOL
c_func
(paren
id|free_irq
)paren
suffix:semicolon
r_int
DECL|function|show_interrupts
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
macro_line|#ifdef CONFIG_SMP
r_int
id|j
suffix:semicolon
macro_line|#endif
r_int
id|i
op_assign
op_star
(paren
id|loff_t
op_star
)paren
id|v
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
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
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;CPU%d       &quot;
comma
id|i
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
macro_line|#endif
r_if
c_cond
(paren
id|i
OL
id|ACTUAL_NR_IRQS
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_desc
(braket
id|i
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
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
)paren
r_goto
id|unlock
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
id|kstat_cpu
c_func
(paren
id|j
)paren
dot
id|irqs
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %14s&quot;
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
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;  %c%s&quot;
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
(brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;, %c%s&quot;
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
)brace
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|unlock
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_desc
(braket
id|i
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|ACTUAL_NR_IRQS
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;IPI: &quot;
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
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|i
)paren
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10lu &quot;
comma
id|cpu_data
(braket
id|i
)braket
dot
id|ipi_count
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
macro_line|#endif
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;ERR: %10lu&bslash;n&quot;
comma
id|irq_err_count
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * handle_irq handles all normal device IRQ&squot;s (the special&n; * SMP cross-CPU interrupts have their own specific&n; * handlers).&n; */
DECL|macro|MAX_ILLEGAL_IRQS
mdefine_line|#define MAX_ILLEGAL_IRQS 16
r_void
DECL|function|handle_irq
id|handle_irq
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
multiline_comment|/* &n;&t; * We ack quickly, we don&squot;t want the irq controller&n;&t; * thinking we&squot;re snobs just because some other CPU has&n;&t; * disabled global interrupts (we have already done the&n;&t; * INT_ACK cycles, it&squot;s too late to try to pretend to the&n;&t; * controller that we aren&squot;t taking the interrupt).&n;&t; *&n;&t; * 0 return value means that this irq is already being&n;&t; * handled by some other CPU. (or is disabled)&n;&t; */
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
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_static
r_int
r_int
id|illegal_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|irq
OG
id|ACTUAL_NR_IRQS
op_logical_and
id|illegal_count
OL
id|MAX_ILLEGAL_IRQS
)paren
(brace
id|irq_err_count
op_increment
suffix:semicolon
id|illegal_count
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;device_interrupt: invalid interrupt %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* mask also the higher prio events */
id|desc-&gt;handler
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * REPLAY is when Linux resends an IRQ that was dropped earlier.&n;&t; * WAITING is used by probe to mark irqs that are being tested.&n;&t; */
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
(brace
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
id|status
op_and_assign
op_complement
id|IRQ_PENDING
suffix:semicolon
multiline_comment|/* we commit to handling */
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
multiline_comment|/*&n;&t; * If there is no IRQ handler or it was disabled, exit early.&n;&t; * Since we set PENDING, if another processor is handling&n;&t; * a different instance of this same irq, the other processor&n;&t; * will take care of it.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Edge triggered interrupts need to remember pending events.&n;&t; * This applies to any hw interrupts that allow a second&n;&t; * instance of the same irq to arrive while we are in handle_irq&n;&t; * or in the handler. But the code here only handles the _second_&n;&t; * instance of the irq, not the third or fourth. So it is mostly&n;&t; * useful for irq hardware that does not mask cleanly in an&n;&t; * SMP environment.&n;&t; */
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
id|handle_IRQ_event
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
op_logical_neg
(paren
id|desc-&gt;status
op_amp
id|IRQ_PENDING
)paren
op_logical_or
(paren
id|desc-&gt;status
op_amp
id|IRQ_LEVEL
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
id|desc-&gt;status
op_and_assign
op_complement
id|IRQ_INPROGRESS
suffix:semicolon
id|out
suffix:colon
multiline_comment|/*&n;&t; * The -&gt;end() handler has to deal with interrupts which got&n;&t; * disabled while the handler was running.&n;&t; */
id|desc-&gt;handler
op_member_access_from_pointer
id|end
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IRQ autodetection code..&n; *&n; * This depends on the fact that any interrupt that&n; * comes in on to an unassigned handler will get stuck&n; * with &quot;IRQ_WAITING&quot; cleared and the interrupt&n; * disabled.&n; */
r_int
r_int
DECL|function|probe_irq_on
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|irq_desc_t
op_star
id|desc
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/* Something may have generated an irq long ago and we want to&n;&t;   flush such a longstanding irq before considering it as spurious. */
r_for
c_loop
(paren
id|i
op_assign
id|NR_IRQS
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_desc
(braket
id|i
)braket
dot
id|action
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|i
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait for longstanding interrupts to trigger. */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|50
suffix:semicolon
id|time_after
c_func
(paren
id|delay
comma
id|jiffies
)paren
suffix:semicolon
)paren
multiline_comment|/* about 20ms delay */
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* enable any unassigned irqs (we must startup again here because&n;&t;   if a longstanding irq happened in the previous stage, it may have&n;&t;   masked itself) first, enable any unassigned irqs. */
r_for
c_loop
(paren
id|i
op_assign
id|NR_IRQS
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
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
id|IRQ_AUTODETECT
op_or
id|IRQ_WAITING
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|i
)paren
)paren
id|desc-&gt;status
op_or_assign
id|IRQ_PENDING
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Wait for spurious interrupts to trigger&n;&t; */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|time_after
c_func
(paren
id|delay
comma
id|jiffies
)paren
suffix:semicolon
)paren
multiline_comment|/* about 100ms delay */
id|barrier
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now filter out any obviously spurious interrupts&n;&t; */
id|val
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
multiline_comment|/* It triggered already - consider it spurious. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
(brace
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
OL
l_int|32
)paren
id|val
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|variable|probe_irq_on
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_on
)paren
suffix:semicolon
multiline_comment|/*&n; * Return a mask of triggered interrupts (this&n; * can handle only legacy ISA interrupts).&n; */
r_int
r_int
DECL|function|probe_irq_mask
id|probe_irq_mask
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
id|mask
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
multiline_comment|/* We only react to ISA interrupts */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|16
)paren
id|mask
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
)brace
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
r_return
id|mask
op_amp
id|val
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the result of the IRQ probe.. A negative result means that&n; * we have several candidates (but we return the lowest-numbered&n; * one).&n; */
r_int
DECL|function|probe_irq_off
id|probe_irq_off
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
id|i
comma
id|irq_found
comma
id|nr_irqs
suffix:semicolon
id|nr_irqs
op_assign
l_int|0
suffix:semicolon
id|irq_found
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc_t
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|i
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|status
op_assign
id|desc-&gt;status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|IRQ_AUTODETECT
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|IRQ_WAITING
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nr_irqs
)paren
id|irq_found
op_assign
id|i
suffix:semicolon
id|nr_irqs
op_increment
suffix:semicolon
)brace
id|desc-&gt;status
op_assign
id|status
op_amp
op_complement
id|IRQ_AUTODETECT
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|shutdown
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr_irqs
OG
l_int|1
)paren
id|irq_found
op_assign
op_minus
id|irq_found
suffix:semicolon
r_return
id|irq_found
suffix:semicolon
)brace
DECL|variable|probe_irq_off
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_off
)paren
suffix:semicolon
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
multiline_comment|/* is there anything to synchronize with? */
r_if
c_cond
(paren
op_logical_neg
id|irq_desc
(braket
id|irq
)braket
dot
id|action
)paren
r_return
suffix:semicolon
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
macro_line|#endif
eof
