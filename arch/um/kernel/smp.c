multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
multiline_comment|/* CPU online map */
DECL|variable|cpu_online_map
r_int
r_int
id|cpu_online_map
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/threads.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;asm/smp.h&quot;
macro_line|#include &quot;asm/processor.h&quot;
macro_line|#include &quot;asm/spinlock.h&quot;
macro_line|#include &quot;asm/softirq.h&quot;
macro_line|#include &quot;asm/hardirq.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;os.h&quot;
multiline_comment|/* The &squot;big kernel lock&squot; */
DECL|variable|__cacheline_aligned_in_smp
id|spinlock_t
id|kernel_flag
id|__cacheline_aligned_in_smp
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* Per CPU bogomips and other parameters */
DECL|variable|cpu_data
r_struct
id|cpuinfo_um
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|um_bh_lock
id|spinlock_t
id|um_bh_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|global_bh_count
id|atomic_t
id|global_bh_count
suffix:semicolon
DECL|variable|global_irq_holder
r_int
r_char
id|global_irq_holder
op_assign
id|NO_PROC_ID
suffix:semicolon
DECL|variable|global_irq_lock
r_int
r_volatile
r_int
id|global_irq_lock
suffix:semicolon
multiline_comment|/* Set when the idlers are all forked */
DECL|variable|smp_threads_ready
r_int
id|smp_threads_ready
op_assign
l_int|0
suffix:semicolon
DECL|variable|num_reschedules_sent
r_int
id|num_reschedules_sent
op_assign
l_int|0
suffix:semicolon
DECL|function|smp_send_reschedule
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
(brace
id|write
c_func
(paren
id|cpu_data
(braket
id|cpu
)braket
dot
id|ipi_pipe
(braket
l_int|1
)braket
comma
l_string|&quot;R&quot;
comma
l_int|1
)paren
suffix:semicolon
id|num_reschedules_sent
op_increment
suffix:semicolon
)brace
DECL|function|show
r_static
r_void
id|show
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;n%s, CPU %d:&bslash;n&quot;
comma
id|str
comma
id|cpu
)paren
suffix:semicolon
)brace
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 100000000
DECL|function|wait_on_bh
r_static
r_inline
r_void
id|wait_on_bh
c_func
(paren
r_void
)paren
(brace
r_int
id|count
op_assign
id|MAXCOUNT
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|count
)paren
(brace
id|show
c_func
(paren
l_string|&quot;wait_on_bh&quot;
)paren
suffix:semicolon
id|count
op_assign
op_complement
l_int|0
suffix:semicolon
)brace
multiline_comment|/* nothing .. wait for the other bh&squot;s to go away */
)brace
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|global_bh_count
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called when we want to synchronize with&n; * bottom half handlers. We need to wait until&n; * no other CPU is executing any bottom half handler.&n; *&n; * Don&squot;t wait if we&squot;re already running in an interrupt&n; * context or are inside a bh handler. &n; */
DECL|function|synchronize_bh
r_void
id|synchronize_bh
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|global_bh_count
)paren
op_logical_and
op_logical_neg
id|in_interrupt
c_func
(paren
)paren
)paren
id|wait_on_bh
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|smp_send_stop
r_void
id|smp_send_stop
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Stopping all CPUs&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|smp_commenced
r_static
id|atomic_t
id|smp_commenced
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|smp_callin_map
r_static
r_volatile
r_int
r_int
id|smp_callin_map
op_assign
l_int|0
suffix:semicolon
DECL|function|smp_commence
r_void
id|smp_commence
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;All CPUs are go!&bslash;n&quot;
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|smp_commenced
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|idle_proc
r_static
r_int
id|idle_proc
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|cpu
comma
id|err
suffix:semicolon
id|set_current
c_func
(paren
id|current
)paren
suffix:semicolon
id|del_from_runqueue
c_func
(paren
id|current
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|current
)paren
suffix:semicolon
id|cpu
op_assign
id|current-&gt;processor
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|cpu_data
(braket
id|cpu
)braket
dot
id|ipi_pipe
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;CPU#%d failed to create IPI pipe, errno = %d&quot;
comma
id|cpu
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|activate_ipi
c_func
(paren
id|cpu_data
(braket
id|cpu
)braket
dot
id|ipi_pipe
(braket
l_int|0
)braket
comma
id|current-&gt;thread.extern_pid
)paren
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|current-&gt;processor
comma
op_amp
id|smp_callin_map
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;huh, CPU#%d already present??&bslash;n&quot;
comma
id|current-&gt;processor
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|smp_commenced
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|init_idle
c_func
(paren
)paren
suffix:semicolon
id|default_idle
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|inited_cpus
r_int
id|inited_cpus
op_assign
l_int|1
suffix:semicolon
DECL|function|idle_thread
r_static
r_int
id|idle_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_int
id|cpu
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|pid
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
id|current-&gt;thread.request.u.thread.proc
op_assign
id|fn
suffix:semicolon
id|current-&gt;thread.request.u.thread.arg
op_assign
l_int|NULL
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_PID
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;do_fork failed in idle_thread&quot;
)paren
suffix:semicolon
)brace
id|cpu_tasks
(braket
id|cpu
)braket
dot
id|pid
op_assign
id|p-&gt;thread.extern_pid
suffix:semicolon
id|cpu_tasks
(braket
id|cpu
)braket
dot
id|task
op_assign
id|p
suffix:semicolon
id|inited_cpus
op_increment
suffix:semicolon
id|init_tasks
(braket
id|cpu
)braket
op_assign
id|p
suffix:semicolon
id|p-&gt;processor
op_assign
id|cpu
suffix:semicolon
id|p-&gt;cpus_allowed
op_assign
l_int|1
op_lshift
id|cpu
suffix:semicolon
id|p-&gt;cpus_runnable
op_assign
id|p-&gt;cpus_allowed
suffix:semicolon
id|write
c_func
(paren
id|p-&gt;thread.switch_pipe
(braket
l_int|1
)braket
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
suffix:semicolon
r_return
id|p-&gt;thread.extern_pid
suffix:semicolon
)brace
DECL|function|smp_boot_cpus
r_void
id|smp_boot_cpus
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
id|set_bit
c_func
(paren
l_int|0
comma
op_amp
id|smp_callin_map
)paren
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|cpu_data
(braket
l_int|0
)braket
dot
id|ipi_pipe
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;CPU#0 failed to create IPI pipe, errno = %d&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|activate_ipi
c_func
(paren
id|cpu_data
(braket
l_int|0
)braket
dot
id|ipi_pipe
(braket
l_int|0
)braket
comma
id|current-&gt;thread.extern_pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ncpus
OL
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ncpus set to 1&bslash;n&quot;
)paren
suffix:semicolon
id|ncpus
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ncpus
OG
id|NR_CPUS
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ncpus can&squot;t be greater than NR_CPUS, set to %d&bslash;n&quot;
comma
id|NR_CPUS
)paren
suffix:semicolon
id|ncpus
op_assign
id|NR_CPUS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ncpus
OG
l_int|1
)paren
(brace
r_int
id|i
comma
id|pid
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Starting up other processors:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|ncpus
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|waittime
suffix:semicolon
multiline_comment|/* Do this early, for hard_smp_processor_id()  */
id|cpu_tasks
(braket
id|i
)braket
dot
id|pid
op_assign
op_minus
l_int|1
suffix:semicolon
id|set_bit
c_func
(paren
id|i
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
id|pid
op_assign
id|idle_thread
c_func
(paren
id|idle_proc
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;&bslash;t#%d - idle thread pid = %d.. &quot;
comma
id|i
comma
id|pid
)paren
suffix:semicolon
id|waittime
op_assign
l_int|200000000
suffix:semicolon
r_while
c_loop
(paren
id|waittime
op_decrement
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|i
comma
op_amp
id|smp_callin_map
)paren
)paren
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
op_amp
id|smp_callin_map
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;online&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;failed&bslash;n&quot;
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|i
comma
op_amp
id|cpu_online_map
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|setup_profiling_timer
r_int
id|setup_profiling_timer
c_func
(paren
r_int
r_int
id|multiplier
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;setup_profiling_timer&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|smp_call_function_slave
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
DECL|function|IPI_handler
r_void
id|IPI_handler
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|cpu_data
(braket
id|cpu
)braket
dot
id|ipi_pipe
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|read
c_func
(paren
id|fd
comma
op_amp
id|c
comma
l_int|1
)paren
op_eq
l_int|1
)paren
(brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;C&squot;
suffix:colon
id|smp_call_function_slave
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;R&squot;
suffix:colon
id|current-&gt;need_resched
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;CPU#%d received unknown IPI [%c]!&bslash;n&quot;
comma
id|cpu
comma
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|hard_smp_processor_id
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
r_return
id|pid_to_processor_id
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|variable|call_lock
r_static
id|spinlock_t
id|call_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|scf_started
r_static
id|atomic_t
id|scf_started
suffix:semicolon
DECL|variable|scf_finished
r_static
id|atomic_t
id|scf_finished
suffix:semicolon
DECL|variable|func
r_static
r_void
(paren
op_star
id|func
)paren
(paren
r_void
op_star
id|info
)paren
suffix:semicolon
DECL|variable|info
r_static
r_void
op_star
id|info
suffix:semicolon
DECL|function|smp_call_function_slave
r_void
id|smp_call_function_slave
c_func
(paren
r_int
id|cpu
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|scf_started
)paren
suffix:semicolon
(paren
op_star
id|func
)paren
(paren
id|info
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|scf_finished
)paren
suffix:semicolon
)brace
DECL|function|smp_call_function
r_int
id|smp_call_function
c_func
(paren
r_void
(paren
op_star
id|_func
)paren
(paren
r_void
op_star
id|info
)paren
comma
r_void
op_star
id|_info
comma
r_int
id|nonatomic
comma
r_int
id|wait
)paren
(brace
r_int
id|cpus
op_assign
id|num_online_cpus
c_func
(paren
)paren
op_minus
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpus
)paren
r_return
l_int|0
suffix:semicolon
id|spin_lock_bh
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|scf_started
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|scf_finished
comma
l_int|0
)paren
suffix:semicolon
id|func
op_assign
id|_func
suffix:semicolon
id|info
op_assign
id|_info
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
id|i
op_ne
id|current-&gt;processor
op_logical_and
id|test_bit
c_func
(paren
id|i
comma
op_amp
id|cpu_online_map
)paren
)paren
id|write
c_func
(paren
id|cpu_data
(braket
id|i
)braket
dot
id|ipi_pipe
(braket
l_int|1
)braket
comma
l_string|&quot;C&quot;
comma
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|scf_started
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait
)paren
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|scf_finished
)paren
op_ne
id|cpus
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_bh
c_func
(paren
op_amp
id|call_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof