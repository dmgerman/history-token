multiline_comment|/*&n; *  drivers/s390/s390mach.c&n; *   S/390 machine check handler&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/s390io.h&gt;
macro_line|#include &lt;asm/s390dyn.h&gt;
macro_line|#include &lt;asm/s390mach.h&gt;
macro_line|#ifdef CONFIG_MACHCHK_WARNING
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#endif
DECL|macro|S390_MACHCHK_DEBUG
mdefine_line|#define S390_MACHCHK_DEBUG
macro_line|#ifdef S390_MACHCHK_DEBUG
DECL|macro|DBG
mdefine_line|#define DBG printk
macro_line|#else&t;&t;&t;&t;/* S390_MACHCHK_DEBUG */
DECL|macro|DBG
mdefine_line|#define DBG(args,...) do {} while (0);
macro_line|#endif&t;&t;&t;&t;/* S390_MACHCHK_DEBUG */
r_static
r_int
id|s390_machine_check_handler
c_func
(paren
r_void
op_star
id|parm
)paren
suffix:semicolon
r_static
r_void
id|s390_enqueue_mchchk
c_func
(paren
id|mache_t
op_star
id|mchchk
)paren
suffix:semicolon
r_static
id|mache_t
op_star
id|s390_dequeue_mchchk
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|s390_enqueue_free_mchchk
c_func
(paren
id|mache_t
op_star
id|mchchk
)paren
suffix:semicolon
r_static
id|mache_t
op_star
id|s390_dequeue_free_mchchk
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|s390_collect_crw_info
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MACHCHK_WARNING
r_static
r_int
id|s390_post_warning
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|mchchk_queue_head
r_static
id|mache_t
op_star
id|mchchk_queue_head
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mchchk_queue_tail
r_static
id|mache_t
op_star
id|mchchk_queue_tail
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mchchk_queue_free
r_static
id|mache_t
op_star
id|mchchk_queue_free
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|crw_buffer_anchor
r_static
id|crwe_t
op_star
id|crw_buffer_anchor
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mchchk_queue_lock
r_static
id|spinlock_t
id|mchchk_queue_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|crw_queue_lock
r_static
id|spinlock_t
id|crw_queue_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|s_sem
r_static
r_struct
id|semaphore
id|s_sem
suffix:semicolon
macro_line|#ifdef CONFIG_MACHCHK_WARNING
DECL|variable|mchchk_wng_posted
r_static
r_int
id|mchchk_wng_posted
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * s390_init_machine_check&n; *&n; * initialize machine check handling&n; */
r_void
DECL|function|s390_init_machine_check
id|s390_init_machine_check
c_func
(paren
r_void
)paren
(brace
id|crwe_t
op_star
id|pcrwe
suffix:semicolon
multiline_comment|/* CRW buffer element pointer */
id|mache_t
op_star
id|pmache
suffix:semicolon
multiline_comment|/* machine check element pointer */
r_int
id|i
suffix:semicolon
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|s_sem
)paren
suffix:semicolon
id|pcrwe
op_assign
id|kmalloc
c_func
(paren
id|MAX_CRW_PENDING
op_star
r_sizeof
(paren
id|crwe_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pcrwe
)paren
id|panic
c_func
(paren
l_string|&quot;s390_init_machine_check: unable to obtain memory&bslash;n&quot;
)paren
suffix:semicolon
id|crw_buffer_anchor
op_assign
id|pcrwe
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
id|MAX_CRW_PENDING
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pcrwe-&gt;crwe_next
op_assign
(paren
id|crwe_t
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|pcrwe
op_plus
r_sizeof
(paren
id|crwe_t
)paren
)paren
suffix:semicolon
id|pcrwe
op_assign
id|pcrwe-&gt;crwe_next
suffix:semicolon
)brace
id|pcrwe-&gt;crwe_next
op_assign
l_int|NULL
suffix:semicolon
id|pmache
op_assign
id|kmalloc
c_func
(paren
id|MAX_MACH_PENDING
op_star
r_sizeof
(paren
id|mache_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmache
)paren
id|panic
c_func
(paren
l_string|&quot;s390_init_machine_check: unable to obtain memory&bslash;n&quot;
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
id|MAX_MACH_PENDING
suffix:semicolon
id|i
op_increment
)paren
(brace
id|s390_enqueue_free_mchchk
c_func
(paren
id|pmache
)paren
suffix:semicolon
id|pmache
op_assign
(paren
id|mache_t
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|pmache
op_plus
r_sizeof
(paren
id|mache_t
)paren
)paren
suffix:semicolon
)brace
id|DBG
c_func
(paren
id|KERN_NOTICE
l_string|&quot;init_mach : starting machine check handler&bslash;n&quot;
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|s390_machine_check_handler
comma
op_amp
id|s_sem
comma
id|CLONE_FS
op_or
id|CLONE_FILES
)paren
suffix:semicolon
id|ctl_clear_bit
c_func
(paren
l_int|14
comma
l_int|25
)paren
suffix:semicolon
multiline_comment|/* disable damage MCH */
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|26
)paren
suffix:semicolon
multiline_comment|/* enable degradation MCH */
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|27
)paren
suffix:semicolon
multiline_comment|/* enable system recovery MCH */
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|28
)paren
suffix:semicolon
multiline_comment|/* enable channel report MCH */
macro_line|#ifdef CONFIG_MACHCK_WARNING
id|ctl_set_bit
c_func
(paren
l_int|14
comma
l_int|24
)paren
suffix:semicolon
multiline_comment|/* enable warning MCH */
macro_line|#endif
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;init_mach : machine check buffer : head = %08X&bslash;n&quot;
comma
(paren
r_int
)paren
op_amp
id|mchchk_queue_head
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;init_mach : machine check buffer : tail = %08X&bslash;n&quot;
comma
(paren
r_int
)paren
op_amp
id|mchchk_queue_tail
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;init_mach : machine check buffer : free = %08X&bslash;n&quot;
comma
(paren
r_int
)paren
op_amp
id|mchchk_queue_free
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;init_mach : CRW entry buffer anchor = %08X&bslash;n&quot;
comma
(paren
r_int
)paren
op_amp
id|crw_buffer_anchor
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;init_mach : machine check handler ready&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|s390_handle_damage
id|s390_handle_damage
c_func
(paren
r_char
op_star
id|msg
)paren
(brace
r_int
r_int
id|caller
op_assign
(paren
r_int
r_int
)paren
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;%s&bslash;n&quot;
comma
id|msg
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|disabled_wait
c_func
(paren
id|caller
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * s390_do_machine_check&n; *&n; * mchine check pre-processor, collecting the machine check info,&n; *  queueing it and posting the machine check handler for processing.&n; */
r_void
DECL|function|s390_do_machine_check
id|s390_do_machine_check
c_func
(paren
r_void
)paren
(brace
r_int
id|crw_count
suffix:semicolon
id|mcic_t
id|mcic
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;s390_do_machine_check : starting ...&bslash;n&quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|mcic
comma
op_amp
id|S390_lowcore.mcck_interruption_code
comma
r_sizeof
(paren
id|__u64
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcic.mcc.mcd.sd
)paren
multiline_comment|/* system damage */
id|s390_handle_damage
c_func
(paren
l_string|&quot;received system damage machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcic.mcc.mcd.pd
)paren
multiline_comment|/* instruction processing damage */
id|s390_handle_damage
(paren
l_string|&quot;received instruction processing damage machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcic.mcc.mcd.se
)paren
multiline_comment|/* storage error uncorrected */
id|s390_handle_damage
(paren
l_string|&quot;received storage error uncorrected machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcic.mcc.mcd.sc
)paren
multiline_comment|/* storage error corrected */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;received storage error corrected machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcic.mcc.mcd.ke
)paren
multiline_comment|/* storage key-error uncorrected */
id|s390_handle_damage
(paren
l_string|&quot;received storage key-error uncorrected machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcic.mcc.mcd.ds
op_logical_and
id|mcic.mcc.mcd.fa
)paren
multiline_comment|/* storage degradation */
id|s390_handle_damage
(paren
l_string|&quot;received storage degradation machine check&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcic.mcc.mcd.cp
)paren
(brace
multiline_comment|/* CRW pending ? */
id|crw_count
op_assign
id|s390_collect_crw_info
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|crw_count
)paren
id|up
c_func
(paren
op_amp
id|s_sem
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MACHCHK_WARNING
multiline_comment|/*&n; * The warning may remain for a prolonged period on the bare iron.&n; * (actually till the machine is powered off, or until the problem is gone)&n; * So we just stop listening for the WARNING MCH and prevent continuously&n; * being interrupted.  One caveat is however, that we must do this per &n; * processor and cannot use the smp version of ctl_clear_bit().&n; * On VM we only get one interrupt per virtally presented machinecheck.&n; * Though one suffices, we may get one interrupt per (virtual) processor. &n; */
r_if
c_cond
(paren
id|mcic.mcc.mcd.w
)paren
(brace
multiline_comment|/* WARNING pending ? */
multiline_comment|/* &n;&t;&t; * Use single machine clear, as we cannot handle smp right now &n;&t;&t; */
id|__ctl_clear_bit
c_func
(paren
l_int|14
comma
l_int|24
)paren
suffix:semicolon
multiline_comment|/* Disable WARNING MCH */
r_if
c_cond
(paren
op_logical_neg
id|mchchk_wng_posted
)paren
(brace
id|mchchk_wng_posted
op_assign
id|s390_post_warning
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mchchk_wng_posted
)paren
id|up
c_func
(paren
op_amp
id|s_sem
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;s390_do_machine_check : done &bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * s390_machine_check_handler&n; *&n; * machine check handler, dequeueing machine check entries&n; *  and processing them&n; */
r_static
r_int
DECL|function|s390_machine_check_handler
id|s390_machine_check_handler
c_func
(paren
r_void
op_star
id|parm
)paren
(brace
r_struct
id|semaphore
op_star
id|sem
op_assign
id|parm
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|mache_t
op_star
id|pmache
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set name to something sensible */
id|strcpy
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;kmcheck&quot;
)paren
suffix:semicolon
multiline_comment|/* block all signals */
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_NOTICE
l_string|&quot;mach_handler : ready&bslash;n&quot;
)paren
suffix:semicolon
r_do
(brace
id|DBG
c_func
(paren
id|KERN_NOTICE
l_string|&quot;mach_handler : waiting for wakeup&bslash;n&quot;
)paren
suffix:semicolon
id|down_interruptible
c_func
(paren
id|sem
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_NOTICE
l_string|&quot;&bslash;nmach_handler : wakeup ... &bslash;n&quot;
)paren
suffix:semicolon
id|found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* init ... */
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|pmache
op_assign
id|s390_dequeue_mchchk
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmache
)paren
(brace
multiline_comment|/* unconditional surrender ... */
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mach_handler : nothing to do, sleeping&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|found
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pmache-&gt;mcic.mcc.mcd.cp
)paren
(brace
id|crwe_t
op_star
id|pcrwe_n
suffix:semicolon
id|crwe_t
op_star
id|pcrwe_h
suffix:semicolon
id|s390_do_crw_pending
c_func
(paren
id|pmache-&gt;mc.crwe
)paren
suffix:semicolon
id|pcrwe_h
op_assign
id|pmache-&gt;mc.crwe
suffix:semicolon
id|pcrwe_n
op_assign
id|pmache-&gt;mc.crwe-&gt;crwe_next
suffix:semicolon
id|pmache-&gt;mcic.mcc.mcd.cp
op_assign
l_int|0
suffix:semicolon
id|pmache-&gt;mc.crwe
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|crw_queue_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|pcrwe_h
)paren
(brace
id|pcrwe_h-&gt;crwe_next
op_assign
id|crw_buffer_anchor
suffix:semicolon
id|crw_buffer_anchor
op_assign
id|pcrwe_h
suffix:semicolon
id|pcrwe_h
op_assign
id|pcrwe_n
suffix:semicolon
r_if
c_cond
(paren
id|pcrwe_h
op_ne
l_int|NULL
)paren
id|pcrwe_n
op_assign
id|pcrwe_h-&gt;crwe_next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|crw_queue_lock
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MACHCHK_WARNING
r_if
c_cond
(paren
id|pmache-&gt;mcic.mcc.mcd.w
)paren
(brace
id|kill_proc
c_func
(paren
l_int|1
comma
id|SIGPWR
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Send INIT the signal */
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;mach_handler : kill -SIGPWR init&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|s390_enqueue_free_mchchk
c_func
(paren
id|pmache
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|pmache
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * s390_dequeue_mchchk&n; *&n; * Dequeue an entry from the machine check queue&n; *&n; * Note : The queue elements provide for a double linked list.&n; *  We dequeue entries from the tail, and enqueue entries to&n; *  the head.&n; *&n; */
r_static
id|mache_t
op_star
DECL|function|s390_dequeue_mchchk
id|s390_dequeue_mchchk
c_func
(paren
r_void
)paren
(brace
id|mache_t
op_star
id|qe
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
id|qe
op_assign
id|mchchk_queue_tail
suffix:semicolon
r_if
c_cond
(paren
id|qe
op_ne
l_int|NULL
)paren
(brace
id|mchchk_queue_tail
op_assign
id|qe-&gt;prev
suffix:semicolon
r_if
c_cond
(paren
id|mchchk_queue_tail
op_ne
l_int|NULL
)paren
(brace
id|mchchk_queue_tail-&gt;next
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|mchchk_queue_head
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
r_return
id|qe
suffix:semicolon
)brace
multiline_comment|/*&n; * s390_enqueue_mchchk&n; *&n; * Enqueue an entry to the machine check queue.&n; *&n; * Note : The queue elements provide for a double linked list.&n; *  We enqueue entries to the head, and dequeue entries from&n; *  the tail.&n; *&n; */
r_static
r_void
DECL|function|s390_enqueue_mchchk
id|s390_enqueue_mchchk
c_func
(paren
id|mache_t
op_star
id|pmache
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmache
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|mchchk_queue_head
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* first element */
id|pmache-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|pmache-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|mchchk_queue_head
op_assign
id|pmache
suffix:semicolon
id|mchchk_queue_tail
op_assign
id|pmache
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* new head */
id|pmache-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|pmache-&gt;next
op_assign
id|mchchk_queue_head
suffix:semicolon
id|mchchk_queue_head-&gt;prev
op_assign
id|pmache
suffix:semicolon
id|mchchk_queue_head
op_assign
id|pmache
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * s390_enqueue_free_mchchk&n; *&n; * Enqueue a free entry to the free queue.&n; *&n; * Note : While the queue elements provide for a double linked list,&n; *  the free queue entries are only concatenated by means of a&n; *  single linked list (forward concatenation).&n; *&n; */
r_static
r_void
DECL|function|s390_enqueue_free_mchchk
id|s390_enqueue_free_mchchk
c_func
(paren
id|mache_t
op_star
id|pmache
)paren
(brace
r_if
c_cond
(paren
id|pmache
op_ne
l_int|NULL
)paren
(brace
id|memset
c_func
(paren
id|pmache
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
(paren
id|mache_t
)paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
id|pmache-&gt;next
op_assign
id|mchchk_queue_free
suffix:semicolon
id|mchchk_queue_free
op_assign
id|pmache
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * s390_dequeue_free_mchchk&n; *&n; * Dequeue an entry from the free queue.&n; *&n; * Note : While the queue elements provide for a double linked list,&n; *  the free queue entries are only concatenated by means of a&n; *  single linked list (forward concatenation).&n; *&n; */
r_static
id|mache_t
op_star
DECL|function|s390_dequeue_free_mchchk
id|s390_dequeue_free_mchchk
c_func
(paren
r_void
)paren
(brace
id|mache_t
op_star
id|qe
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
id|qe
op_assign
id|mchchk_queue_free
suffix:semicolon
r_if
c_cond
(paren
id|qe
op_ne
l_int|NULL
)paren
(brace
id|mchchk_queue_free
op_assign
id|qe-&gt;next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|mchchk_queue_lock
)paren
suffix:semicolon
r_return
id|qe
suffix:semicolon
)brace
multiline_comment|/*&n; * s390_collect_crw_info&n; *&n; * Retrieve CRWs. If a CRW was found a machine check element&n; *  is dequeued from the free chain, filled and enqueued to&n; *  be processed.&n; *&n; * The function returns the number of CRWs found.&n; *&n; * Note : We must always be called disabled ...&n; */
r_static
r_int
DECL|function|s390_collect_crw_info
id|s390_collect_crw_info
c_func
(paren
r_void
)paren
(brace
id|crw_t
id|tcrw
suffix:semicolon
multiline_comment|/* temporarily holds a CRW */
r_int
id|ccode
suffix:semicolon
multiline_comment|/* condition code from stcrw() */
id|crwe_t
op_star
id|pcrwe
suffix:semicolon
multiline_comment|/* pointer to CRW buffer entry */
id|mache_t
op_star
id|pmache
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ptr to mchchk entry */
r_int
id|chain
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* indicate chaining */
id|crwe_t
op_star
id|pccrw
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ptr to current CRW buffer entry */
r_int
id|count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* CRW count */
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;crw_info : looking for CRWs ...&bslash;n&quot;
)paren
suffix:semicolon
r_do
(brace
id|ccode
op_assign
id|stcrw
c_func
(paren
(paren
id|__u32
op_star
)paren
op_amp
id|tcrw
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccode
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;crw_info : CRW reports &quot;
l_string|&quot;slct=%d, oflw=%d, chn=%d, &quot;
l_string|&quot;rsc=%X, anc=%d, erc=%X, &quot;
l_string|&quot;rsid=%X&bslash;n&quot;
comma
id|tcrw.slct
comma
id|tcrw.oflw
comma
id|tcrw.chn
comma
id|tcrw.rsc
comma
id|tcrw.anc
comma
id|tcrw.erc
comma
id|tcrw.rsid
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Dequeue a CRW entry from the free chain&n;&t;&t; *  and process it ...&n;&t;&t; */
id|spin_lock
c_func
(paren
op_amp
id|crw_queue_lock
)paren
suffix:semicolon
id|pcrwe
op_assign
id|crw_buffer_anchor
suffix:semicolon
r_if
c_cond
(paren
id|pcrwe
op_eq
l_int|NULL
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|crw_queue_lock
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;crw_info : &quot;
l_string|&quot;no CRW buffer entries available&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|crw_buffer_anchor
op_assign
id|pcrwe-&gt;crwe_next
suffix:semicolon
id|pcrwe-&gt;crwe_next
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|crw_queue_lock
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
(paren
id|pcrwe-&gt;crw
)paren
comma
op_amp
id|tcrw
comma
r_sizeof
(paren
id|crw_t
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If it is the first CRW, chain it to the mchchk&n;&t;&t; *  buffer entry, otherwise to the last CRW entry.&n;&t;&t; */
r_if
c_cond
(paren
id|chain
op_eq
l_int|0
)paren
(brace
id|pmache
op_assign
id|s390_dequeue_free_mchchk
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmache
)paren
id|panic
c_func
(paren
l_string|&quot;crw_info: unable to dequeue &quot;
l_string|&quot;free mchchk buffer&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pmache
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
(paren
id|mache_t
)paren
)paren
suffix:semicolon
id|pmache-&gt;mcic.mcc.mcd.cp
op_assign
l_int|1
suffix:semicolon
id|pmache-&gt;mc.crwe
op_assign
id|pcrwe
suffix:semicolon
id|pccrw
op_assign
id|pcrwe
suffix:semicolon
)brace
r_else
(brace
id|pccrw-&gt;crwe_next
op_assign
id|pcrwe
suffix:semicolon
id|pccrw
op_assign
id|pcrwe
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pccrw-&gt;crw.chn
)paren
(brace
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;crw_info: &quot;
l_string|&quot;chained CRWs pending ...&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|chain
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|chain
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We can enqueue the mchchk buffer if&n;&t;&t;&t; *  there aren&squot;t more CRWs chained.&n;&t;&t;&t; */
id|s390_enqueue_mchchk
c_func
(paren
id|pmache
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|ccode
op_eq
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|count
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MACHCHK_WARNING
multiline_comment|/*&n; * s390_post_warning&n; *&n; * Post a warning type machine check&n; *&n; * The function returns 1 when succesfull (panics otherwise)&n; */
r_static
r_int
DECL|function|s390_post_warning
id|s390_post_warning
c_func
(paren
r_void
)paren
(brace
id|mache_t
op_star
id|pmache
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* ptr to mchchk entry */
id|pmache
op_assign
id|s390_dequeue_free_mchchk
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmache
)paren
id|panic
c_func
(paren
l_string|&quot;post_warning : &quot;
l_string|&quot;unable to dequeue free mchchk buffer&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pmache
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
(paren
id|mache_t
)paren
)paren
suffix:semicolon
id|pmache-&gt;mcic.mcc.mcd.w
op_assign
l_int|1
suffix:semicolon
id|s390_enqueue_mchchk
c_func
(paren
id|pmache
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;post_warning : 1 warning machine check posted&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
