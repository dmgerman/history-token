multiline_comment|/*&n; *  arch/s390/kernel/s390mach.c&n; *   S/390 machine check handler,&n; *            currently only channel-reports are supported&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ingo Adlung (adlung@de.ibm.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/s390io.h&gt;
macro_line|#include &lt;asm/s390dyn.h&gt;
macro_line|#include &lt;asm/s390mach.h&gt;
DECL|macro|S390_MACHCHK_DEBUG
mdefine_line|#define S390_MACHCHK_DEBUG
DECL|variable|mchchk_queue_head
r_static
id|mchchk_queue_element_t
op_star
id|mchchk_queue_head
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mchchk_queue_tail
r_static
id|mchchk_queue_element_t
op_star
id|mchchk_queue_tail
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mchchk_queue_free
r_static
id|mchchk_queue_element_t
op_star
id|mchchk_queue_free
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mchchk_queue_lock
r_static
id|spinlock_t
id|mchchk_queue_lock
suffix:semicolon
DECL|variable|s_sem
r_static
r_struct
id|semaphore
id|s_sem
(braket
l_int|2
)braket
suffix:semicolon
singleline_comment|//
singleline_comment|// initialize machine check handling
singleline_comment|//
DECL|function|s390_init_machine_check
r_void
id|s390_init_machine_check
c_func
(paren
r_void
)paren
(brace
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|s_sem
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|init_MUTEX_LOCKED
c_func
(paren
op_amp
id|s_sem
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#if 0
singleline_comment|//
singleline_comment|// fix me ! initialize a machine check queue with 100 elements
singleline_comment|//
macro_line|#ifdef S390_MACHCHK_DEBUG
id|printk
c_func
(paren
l_string|&quot;init_mach : starting kernel thread&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
id|kernel_thread
c_func
(paren
id|s390_machine_check_handler
comma
id|s_sem
comma
l_int|0
)paren
suffix:semicolon
singleline_comment|//
singleline_comment|// wait for the machine check handler to be ready
singleline_comment|//
macro_line|#ifdef S390_MACHCHK_DEBUG
id|printk
c_func
(paren
l_string|&quot;init_mach : waiting for kernel thread&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
id|down
c_func
(paren
op_amp
id|sem
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#ifdef S390_MACHCHK_DEBUG
id|printk
c_func
(paren
l_string|&quot;init_mach : kernel thread ready&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
singleline_comment|//
singleline_comment|// fix me ! we have to initialize CR14 to allow for CRW pending
singleline_comment|//           conditions
singleline_comment|//
singleline_comment|// fix me ! enable machine checks in the PSW
singleline_comment|//
macro_line|#endif
r_return
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// machine check pre-processor
singleline_comment|//
DECL|function|s390_do_machine_check
r_void
id|__init
id|s390_do_machine_check
c_func
(paren
r_void
)paren
(brace
singleline_comment|// fix me ! we have to check for machine check and
singleline_comment|//          post the handler eventually
r_return
suffix:semicolon
)brace
singleline_comment|//
singleline_comment|// machine check handler
singleline_comment|//
DECL|function|s390_machine_check_handler
r_static
r_void
id|__init
id|s390_machine_check_handler
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
macro_line|#ifdef S390_MACHCHK_DEBUG
id|printk
c_func
(paren
l_string|&quot;mach_handler : kernel thread up&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
id|up
c_func
(paren
op_amp
id|sem
(braket
l_int|0
)braket
)paren
suffix:semicolon
macro_line|#ifdef S390_MACHCHK_DEBUG
id|printk
c_func
(paren
l_string|&quot;mach_handler : kernel thread ready&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
r_do
(brace
macro_line|#ifdef S390_MACHCHK_DEBUG
id|printk
c_func
(paren
l_string|&quot;mach_handler : waiting for wakeup&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
id|down_interruptible
c_func
(paren
op_amp
id|sem
(braket
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#ifdef S390_MACHCHK_DEBUG
id|printk
c_func
(paren
l_string|&quot;mach_handler : wakeup&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;
r_break
suffix:semicolon
singleline_comment|// fix me ! unconditional surrender ...
singleline_comment|// fix me ! check for machine checks and
singleline_comment|//          call do_crw_pending() eventually
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|s390_get_mchchk
id|mchchk_queue_element_t
op_star
id|s390_get_mchchk
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|mchchk_queue_element_t
op_star
id|qe
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mchchk_queue_lock
comma
id|flags
)paren
suffix:semicolon
singleline_comment|// fix me ! dequeue first element if available
id|qe
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mchchk_queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|qe
suffix:semicolon
)brace
DECL|function|s390_free_mchchk
r_void
id|s390_free_mchchk
c_func
(paren
id|mchchk_queue_element_t
op_star
id|mchchk
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|mchchk
op_ne
l_int|NULL
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|mchchk_queue_lock
comma
id|flags
)paren
suffix:semicolon
id|mchchk-&gt;next
op_assign
id|mchchk_queue_free
suffix:semicolon
r_if
c_cond
(paren
id|mchchk_queue_free
op_ne
l_int|NULL
)paren
(brace
id|mchchk_queue_free-&gt;prev
op_assign
id|mchchk
suffix:semicolon
)brace
multiline_comment|/* endif */
id|mchchk-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|mchchk_queue_free
op_assign
id|mchchk
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|mchchk_queue_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* endif */
r_return
suffix:semicolon
)brace
eof
