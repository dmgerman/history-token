multiline_comment|/*&n; *  linux/kernel/profile.c&n; *  Simple profiling. Manages a direct-mapped profile hit count buffer,&n; *  with configurable resolution, support for restricting the cpus on&n; *  which profiling is done, and switching between cpu time and&n; *  schedule() calls via kernel command line parameters passed at boot.&n; *&n; *  Scheduler profiling support, Arjan van de Ven and Ingo Molnar,&n; *&t;Red Hat, July 2004&n; *  Consolidation of architecture support code for profiling,&n; *&t;William Irwin, Oracle, July 2004&n; *  Amortized hit count accounting via per-cpu open-addressed hashtables&n; *&t;to resolve timer interrupt livelocks, William Irwin, Oracle, 2004&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
macro_line|#include &lt;linux/cpu.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|struct|profile_hit
r_struct
id|profile_hit
(brace
DECL|member|pc
DECL|member|hits
id|u32
id|pc
comma
id|hits
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PROFILE_GRPSHIFT
mdefine_line|#define PROFILE_GRPSHIFT&t;3
DECL|macro|PROFILE_GRPSZ
mdefine_line|#define PROFILE_GRPSZ&t;&t;(1 &lt;&lt; PROFILE_GRPSHIFT)
DECL|macro|NR_PROFILE_HIT
mdefine_line|#define NR_PROFILE_HIT&t;&t;(PAGE_SIZE/sizeof(struct profile_hit))
DECL|macro|NR_PROFILE_GRP
mdefine_line|#define NR_PROFILE_GRP&t;&t;(NR_PROFILE_HIT/PROFILE_GRPSZ)
multiline_comment|/* Oprofile timer tick hook */
DECL|variable|timer_hook
r_int
(paren
op_star
id|timer_hook
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|prof_buffer
r_static
id|atomic_t
op_star
id|prof_buffer
suffix:semicolon
DECL|variable|prof_len
DECL|variable|prof_shift
r_static
r_int
r_int
id|prof_len
comma
id|prof_shift
suffix:semicolon
DECL|variable|prof_on
r_static
r_int
id|prof_on
suffix:semicolon
DECL|variable|prof_cpu_mask
r_static
id|cpumask_t
id|prof_cpu_mask
op_assign
id|CPU_MASK_ALL
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|profile_hit
op_star
(braket
l_int|2
)braket
comma
id|cpu_profile_hits
)paren
suffix:semicolon
r_static
id|DEFINE_PER_CPU
c_func
(paren
r_int
comma
id|cpu_profile_flip
)paren
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|profile_flip_mutex
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
DECL|function|profile_setup
r_static
r_int
id|__init
id|profile_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|par
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;schedule&quot;
comma
l_int|8
)paren
)paren
(brace
id|prof_on
op_assign
id|SCHED_PROFILING
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;kernel schedule profiling enabled&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str
(braket
l_int|7
)braket
op_eq
l_char|&squot;,&squot;
)paren
id|str
op_add_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|par
)paren
)paren
(brace
id|prof_shift
op_assign
id|par
suffix:semicolon
id|prof_on
op_assign
id|CPU_PROFILING
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;kernel profiling enabled (shift: %ld)&bslash;n&quot;
comma
id|prof_shift
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;profile=&quot;
comma
id|profile_setup
)paren
suffix:semicolon
DECL|function|profile_init
r_void
id|__init
id|profile_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prof_on
)paren
r_return
suffix:semicolon
multiline_comment|/* only text is profiled */
id|prof_len
op_assign
(paren
id|_etext
op_minus
id|_stext
)paren
op_rshift
id|prof_shift
suffix:semicolon
id|prof_buffer
op_assign
id|alloc_bootmem
c_func
(paren
id|prof_len
op_star
r_sizeof
(paren
id|atomic_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Profile event notifications */
macro_line|#ifdef CONFIG_PROFILING
r_static
id|DECLARE_RWSEM
c_func
(paren
id|profile_rwsem
)paren
suffix:semicolon
r_static
id|DEFINE_RWLOCK
c_func
(paren
id|handoff_lock
)paren
suffix:semicolon
DECL|variable|task_exit_notifier
r_static
r_struct
id|notifier_block
op_star
id|task_exit_notifier
suffix:semicolon
DECL|variable|task_free_notifier
r_static
r_struct
id|notifier_block
op_star
id|task_free_notifier
suffix:semicolon
DECL|variable|munmap_notifier
r_static
r_struct
id|notifier_block
op_star
id|munmap_notifier
suffix:semicolon
DECL|function|profile_task_exit
r_void
id|profile_task_exit
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
id|down_read
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
id|notifier_call_chain
c_func
(paren
op_amp
id|task_exit_notifier
comma
l_int|0
comma
id|task
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
)brace
DECL|function|profile_handoff_task
r_int
id|profile_handoff_task
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_int
id|ret
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|handoff_lock
)paren
suffix:semicolon
id|ret
op_assign
id|notifier_call_chain
c_func
(paren
op_amp
id|task_free_notifier
comma
l_int|0
comma
id|task
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|handoff_lock
)paren
suffix:semicolon
r_return
(paren
id|ret
op_eq
id|NOTIFY_OK
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|profile_munmap
r_void
id|profile_munmap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|down_read
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
id|notifier_call_chain
c_func
(paren
op_amp
id|munmap_notifier
comma
l_int|0
comma
(paren
r_void
op_star
)paren
id|addr
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
)brace
DECL|function|task_handoff_register
r_int
id|task_handoff_register
c_func
(paren
r_struct
id|notifier_block
op_star
id|n
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|handoff_lock
)paren
suffix:semicolon
id|err
op_assign
id|notifier_chain_register
c_func
(paren
op_amp
id|task_free_notifier
comma
id|n
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|handoff_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|task_handoff_unregister
r_int
id|task_handoff_unregister
c_func
(paren
r_struct
id|notifier_block
op_star
id|n
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|handoff_lock
)paren
suffix:semicolon
id|err
op_assign
id|notifier_chain_unregister
c_func
(paren
op_amp
id|task_free_notifier
comma
id|n
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|handoff_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|profile_event_register
r_int
id|profile_event_register
c_func
(paren
r_enum
id|profile_type
id|type
comma
r_struct
id|notifier_block
op_star
id|n
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|PROFILE_TASK_EXIT
suffix:colon
id|err
op_assign
id|notifier_chain_register
c_func
(paren
op_amp
id|task_exit_notifier
comma
id|n
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROFILE_MUNMAP
suffix:colon
id|err
op_assign
id|notifier_chain_register
c_func
(paren
op_amp
id|munmap_notifier
comma
id|n
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|profile_event_unregister
r_int
id|profile_event_unregister
c_func
(paren
r_enum
id|profile_type
id|type
comma
r_struct
id|notifier_block
op_star
id|n
)paren
(brace
r_int
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|down_write
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|PROFILE_TASK_EXIT
suffix:colon
id|err
op_assign
id|notifier_chain_unregister
c_func
(paren
op_amp
id|task_exit_notifier
comma
id|n
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PROFILE_MUNMAP
suffix:colon
id|err
op_assign
id|notifier_chain_unregister
c_func
(paren
op_amp
id|munmap_notifier
comma
id|n
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|up_write
c_func
(paren
op_amp
id|profile_rwsem
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|register_timer_hook
r_int
id|register_timer_hook
c_func
(paren
r_int
(paren
op_star
id|hook
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
r_if
c_cond
(paren
id|timer_hook
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|timer_hook
op_assign
id|hook
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_timer_hook
r_void
id|unregister_timer_hook
c_func
(paren
r_int
(paren
op_star
id|hook
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
)paren
(brace
id|WARN_ON
c_func
(paren
id|hook
op_ne
id|timer_hook
)paren
suffix:semicolon
id|timer_hook
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* make sure all CPUs see the NULL hook */
id|synchronize_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|register_timer_hook
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|register_timer_hook
)paren
suffix:semicolon
DECL|variable|unregister_timer_hook
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|unregister_timer_hook
)paren
suffix:semicolon
DECL|variable|task_handoff_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|task_handoff_register
)paren
suffix:semicolon
DECL|variable|task_handoff_unregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|task_handoff_unregister
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROFILING */
DECL|variable|profile_event_register
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|profile_event_register
)paren
suffix:semicolon
DECL|variable|profile_event_unregister
id|EXPORT_SYMBOL_GPL
c_func
(paren
id|profile_event_unregister
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n; * Each cpu has a pair of open-addressed hashtables for pending&n; * profile hits. read_profile() IPI&squot;s all cpus to request them&n; * to flip buffers and flushes their contents to prof_buffer itself.&n; * Flip requests are serialized by the profile_flip_mutex. The sole&n; * use of having a second hashtable is for avoiding cacheline&n; * contention that would otherwise happen during flushes of pending&n; * profile hits required for the accuracy of reported profile hits&n; * and so resurrect the interrupt livelock issue.&n; *&n; * The open-addressed hashtables are indexed by profile buffer slot&n; * and hold the number of pending hits to that profile buffer slot on&n; * a cpu in an entry. When the hashtable overflows, all pending hits&n; * are accounted to their corresponding profile buffer slots with&n; * atomic_add() and the hashtable emptied. As numerous pending hits&n; * may be accounted to a profile buffer slot in a hashtable entry,&n; * this amortizes a number of atomic profile buffer increments likely&n; * to be far larger than the number of entries in the hashtable,&n; * particularly given that the number of distinct profile buffer&n; * positions to which hits are accounted during short intervals (e.g.&n; * several seconds) is usually very small. Exclusion from buffer&n; * flipping is provided by interrupt disablement (note that for&n; * SCHED_PROFILING profile_hit() may be called from process context).&n; * The hash function is meant to be lightweight as opposed to strong,&n; * and was vaguely inspired by ppc64 firmware-supported inverted&n; * pagetable hash functions, but uses a full hashtable full of finite&n; * collision chains, not just pairs of them.&n; *&n; * -- wli&n; */
DECL|function|__profile_flip_buffers
r_static
r_void
id|__profile_flip_buffers
c_func
(paren
r_void
op_star
id|unused
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
id|per_cpu
c_func
(paren
id|cpu_profile_flip
comma
id|cpu
)paren
op_assign
op_logical_neg
id|per_cpu
c_func
(paren
id|cpu_profile_flip
comma
id|cpu
)paren
suffix:semicolon
)brace
DECL|function|profile_flip_buffers
r_static
r_void
id|profile_flip_buffers
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
comma
id|cpu
suffix:semicolon
id|down
c_func
(paren
op_amp
id|profile_flip_mutex
)paren
suffix:semicolon
id|j
op_assign
id|per_cpu
c_func
(paren
id|cpu_profile_flip
comma
id|get_cpu
c_func
(paren
)paren
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|__profile_flip_buffers
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
(brace
r_struct
id|profile_hit
op_star
id|hits
op_assign
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
id|j
)braket
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
id|NR_PROFILE_HIT
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hits
(braket
id|i
)braket
dot
id|hits
)paren
(brace
r_if
c_cond
(paren
id|hits
(braket
id|i
)braket
dot
id|pc
)paren
id|hits
(braket
id|i
)braket
dot
id|pc
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|atomic_add
c_func
(paren
id|hits
(braket
id|i
)braket
dot
id|hits
comma
op_amp
id|prof_buffer
(braket
id|hits
(braket
id|i
)braket
dot
id|pc
)braket
)paren
suffix:semicolon
id|hits
(braket
id|i
)braket
dot
id|hits
op_assign
id|hits
(braket
id|i
)braket
dot
id|pc
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|profile_flip_mutex
)paren
suffix:semicolon
)brace
DECL|function|profile_discard_flip_buffers
r_static
r_void
id|profile_discard_flip_buffers
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|cpu
suffix:semicolon
id|down
c_func
(paren
op_amp
id|profile_flip_mutex
)paren
suffix:semicolon
id|i
op_assign
id|per_cpu
c_func
(paren
id|cpu_profile_flip
comma
id|get_cpu
c_func
(paren
)paren
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|__profile_flip_buffers
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
(brace
r_struct
id|profile_hit
op_star
id|hits
op_assign
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
id|i
)braket
suffix:semicolon
id|memset
c_func
(paren
id|hits
comma
l_int|0
comma
id|NR_PROFILE_HIT
op_star
r_sizeof
(paren
r_struct
id|profile_hit
)paren
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|profile_flip_mutex
)paren
suffix:semicolon
)brace
DECL|function|profile_hit
r_void
id|profile_hit
c_func
(paren
r_int
id|type
comma
r_void
op_star
id|__pc
)paren
(brace
r_int
r_int
id|primary
comma
id|secondary
comma
id|flags
comma
id|pc
op_assign
(paren
r_int
r_int
)paren
id|__pc
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|cpu
suffix:semicolon
r_struct
id|profile_hit
op_star
id|hits
suffix:semicolon
r_if
c_cond
(paren
id|prof_on
op_ne
id|type
op_logical_or
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
id|pc
op_assign
id|min
c_func
(paren
(paren
id|pc
op_minus
(paren
r_int
r_int
)paren
id|_stext
)paren
op_rshift
id|prof_shift
comma
id|prof_len
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_assign
id|primary
op_assign
(paren
id|pc
op_amp
(paren
id|NR_PROFILE_GRP
op_minus
l_int|1
)paren
)paren
op_lshift
id|PROFILE_GRPSHIFT
suffix:semicolon
id|secondary
op_assign
(paren
op_complement
(paren
id|pc
op_lshift
l_int|1
)paren
op_amp
(paren
id|NR_PROFILE_GRP
op_minus
l_int|1
)paren
)paren
op_lshift
id|PROFILE_GRPSHIFT
suffix:semicolon
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
id|hits
op_assign
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
id|per_cpu
c_func
(paren
id|cpu_profile_flip
comma
id|cpu
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hits
)paren
(brace
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_do
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
id|PROFILE_GRPSZ
suffix:semicolon
op_increment
id|j
)paren
(brace
r_if
c_cond
(paren
id|hits
(braket
id|i
op_plus
id|j
)braket
dot
id|pc
op_eq
id|pc
)paren
(brace
id|hits
(braket
id|i
op_plus
id|j
)braket
dot
id|hits
op_increment
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|hits
(braket
id|i
op_plus
id|j
)braket
dot
id|hits
)paren
(brace
id|hits
(braket
id|i
op_plus
id|j
)braket
dot
id|pc
op_assign
id|pc
suffix:semicolon
id|hits
(braket
id|i
op_plus
id|j
)braket
dot
id|hits
op_assign
l_int|1
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|i
op_assign
(paren
id|i
op_plus
id|secondary
)paren
op_amp
(paren
id|NR_PROFILE_HIT
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
op_ne
id|primary
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|prof_buffer
(braket
id|pc
)braket
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
id|NR_PROFILE_HIT
suffix:semicolon
op_increment
id|i
)paren
(brace
id|atomic_add
c_func
(paren
id|hits
(braket
id|i
)braket
dot
id|hits
comma
op_amp
id|prof_buffer
(braket
id|hits
(braket
id|i
)braket
dot
id|pc
)braket
)paren
suffix:semicolon
id|hits
(braket
id|i
)braket
dot
id|pc
op_assign
id|hits
(braket
id|i
)braket
dot
id|hits
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG_CPU
DECL|function|profile_cpu_callback
r_static
r_int
id|__devinit
id|profile_cpu_callback
c_func
(paren
r_struct
id|notifier_block
op_star
id|info
comma
r_int
r_int
id|action
comma
r_void
op_star
id|__cpu
)paren
(brace
r_int
id|node
comma
id|cpu
op_assign
(paren
r_int
r_int
)paren
id|__cpu
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|CPU_UP_PREPARE
suffix:colon
id|node
op_assign
id|cpu_to_node
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_flip
comma
id|cpu
)paren
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
)paren
(brace
id|page
op_assign
id|alloc_pages_node
c_func
(paren
id|node
comma
id|GFP_KERNEL
op_or
id|__GFP_ZERO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
id|NOTIFY_BAD
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
)paren
(brace
id|page
op_assign
id|alloc_pages_node
c_func
(paren
id|node
comma
id|GFP_KERNEL
op_or
id|__GFP_ZERO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|out_free
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
op_assign
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
id|out_free
suffix:colon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|NOTIFY_BAD
suffix:semicolon
r_case
id|CPU_ONLINE
suffix:colon
id|cpu_set
c_func
(paren
id|cpu
comma
id|prof_cpu_mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CPU_UP_CANCELED
suffix:colon
r_case
id|CPU_DEAD
suffix:colon
id|cpu_clear
c_func
(paren
id|cpu
comma
id|prof_cpu_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
)paren
(brace
id|page
op_assign
id|virt_to_page
c_func
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
)paren
(brace
id|page
op_assign
id|virt_to_page
c_func
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_HOTPLUG_CPU */
macro_line|#else /* !CONFIG_SMP */
DECL|macro|profile_flip_buffers
mdefine_line|#define profile_flip_buffers()&t;&t;do { } while (0)
DECL|macro|profile_discard_flip_buffers
mdefine_line|#define profile_discard_flip_buffers()&t;do { } while (0)
DECL|function|profile_hit
r_void
id|profile_hit
c_func
(paren
r_int
id|type
comma
r_void
op_star
id|__pc
)paren
(brace
r_int
r_int
id|pc
suffix:semicolon
r_if
c_cond
(paren
id|prof_on
op_ne
id|type
op_logical_or
op_logical_neg
id|prof_buffer
)paren
r_return
suffix:semicolon
id|pc
op_assign
(paren
(paren
r_int
r_int
)paren
id|__pc
op_minus
(paren
r_int
r_int
)paren
id|_stext
)paren
op_rshift
id|prof_shift
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|prof_buffer
(braket
id|min
c_func
(paren
id|pc
comma
id|prof_len
op_minus
l_int|1
)paren
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_SMP */
DECL|function|profile_tick
r_void
id|profile_tick
c_func
(paren
r_int
id|type
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|type
op_eq
id|CPU_PROFILING
op_logical_and
id|timer_hook
)paren
id|timer_hook
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
id|cpu_isset
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|prof_cpu_mask
)paren
)paren
id|profile_hit
c_func
(paren
id|type
comma
(paren
r_void
op_star
)paren
id|profile_pc
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
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
id|cpumask_t
op_star
id|mask
op_assign
(paren
id|cpumask_t
op_star
)paren
id|data
suffix:semicolon
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
DECL|function|create_prof_cpu_mask
r_void
id|create_prof_cpu_mask
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|root_irq_dir
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
multiline_comment|/* create /proc/irq/prof_cpu_mask */
r_if
c_cond
(paren
op_logical_neg
(paren
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
)paren
)paren
r_return
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
)brace
multiline_comment|/*&n; * This function accesses profiling information. The returned data is&n; * binary: the sampling step and the actual contents of the profile&n; * buffer. Use of the program readprofile is recommended in order to&n; * get meaningful info out of these data.&n; */
r_static
id|ssize_t
DECL|function|read_profile
id|read_profile
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
r_int
id|p
op_assign
op_star
id|ppos
suffix:semicolon
id|ssize_t
id|read
suffix:semicolon
r_char
op_star
id|pnt
suffix:semicolon
r_int
r_int
id|sample_step
op_assign
l_int|1
op_lshift
id|prof_shift
suffix:semicolon
id|profile_flip_buffers
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
(paren
id|prof_len
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
id|prof_len
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
op_minus
id|p
)paren
id|count
op_assign
(paren
id|prof_len
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
op_minus
id|p
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
template_param
l_int|0
)paren
(brace
id|put_user
c_func
(paren
op_star
(paren
(paren
r_char
op_star
)paren
(paren
op_amp
id|sample_step
)paren
op_plus
id|p
)paren
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|read
op_increment
suffix:semicolon
)brace
id|pnt
op_assign
(paren
r_char
op_star
)paren
id|prof_buffer
op_plus
id|p
op_minus
r_sizeof
(paren
id|atomic_t
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|pnt
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|read
op_add_assign
id|count
suffix:semicolon
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * Writing to /proc/profile resets the counters&n; *&n; * Writing a &squot;profiling multiplier&squot; value into it also re-sets the profiling&n; * interrupt frequency, on architectures that support this.&n; */
DECL|function|write_profile
r_static
id|ssize_t
id|write_profile
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
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
id|setup_profiling_timer
(paren
r_int
r_int
id|multiplier
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_int
r_int
id|multiplier
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|multiplier
comma
id|buf
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|setup_profiling_timer
c_func
(paren
id|multiplier
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
id|profile_discard_flip_buffers
c_func
(paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|prof_buffer
comma
l_int|0
comma
id|prof_len
op_star
r_sizeof
(paren
id|atomic_t
)paren
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|proc_profile_operations
r_static
r_struct
id|file_operations
id|proc_profile_operations
op_assign
(brace
dot
id|read
op_assign
id|read_profile
comma
dot
id|write
op_assign
id|write_profile
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|function|profile_nop
r_static
r_void
id|__init
id|profile_nop
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
)brace
DECL|function|create_hash_tables
r_static
r_int
id|__init
id|create_hash_tables
c_func
(paren
r_void
)paren
(brace
r_int
id|cpu
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
(brace
r_int
id|node
op_assign
id|cpu_to_node
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|page
op_assign
id|alloc_pages_node
c_func
(paren
id|node
comma
id|GFP_KERNEL
op_or
id|__GFP_ZERO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|out_cleanup
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
op_assign
(paren
r_struct
id|profile_hit
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|page
op_assign
id|alloc_pages_node
c_func
(paren
id|node
comma
id|GFP_KERNEL
op_or
id|__GFP_ZERO
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|out_cleanup
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
op_assign
(paren
r_struct
id|profile_hit
op_star
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_cleanup
suffix:colon
id|prof_on
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|profile_nop
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|cpu
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
r_if
c_cond
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
)paren
(brace
id|page
op_assign
id|virt_to_page
c_func
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|0
)braket
op_assign
l_int|NULL
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
)paren
(brace
id|page
op_assign
id|virt_to_page
c_func
(paren
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|per_cpu
c_func
(paren
id|cpu_profile_hits
comma
id|cpu
)paren
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|macro|create_hash_tables
mdefine_line|#define create_hash_tables()&t;&t;&t;({ 0; })
macro_line|#endif
DECL|function|create_proc_profile
r_static
r_int
id|__init
id|create_proc_profile
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prof_on
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|create_hash_tables
c_func
(paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;profile&quot;
comma
id|S_IWUSR
op_or
id|S_IRUGO
comma
l_int|NULL
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|entry-&gt;proc_fops
op_assign
op_amp
id|proc_profile_operations
suffix:semicolon
id|entry-&gt;size
op_assign
(paren
l_int|1
op_plus
id|prof_len
)paren
op_star
r_sizeof
(paren
id|atomic_t
)paren
suffix:semicolon
id|hotcpu_notifier
c_func
(paren
id|profile_cpu_callback
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|create_proc_profile
id|module_init
c_func
(paren
id|create_proc_profile
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PROC_FS */
eof
