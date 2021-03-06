multiline_comment|/*&n; * i386 semaphore implementation.&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; *&n; * Portions Copyright 1999 Red Hat, Inc.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; * rw semaphores implemented November 1999 by Benjamin LaHaise &lt;bcrl@kvack.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/err.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
multiline_comment|/*&n; * Semaphores are implemented using a two-way counter:&n; * The &quot;count&quot; variable is decremented for each process&n; * that tries to acquire the semaphore, while the &quot;sleeping&quot;&n; * variable is a count of such acquires.&n; *&n; * Notably, the inline &quot;up()&quot; and &quot;down()&quot; functions can&n; * efficiently test if they need to do any extra work (up&n; * needs to do something only if count was negative before&n; * the increment operation.&n; *&n; * &quot;sleeping&quot; and the contention routine ordering is protected&n; * by the spinlock in the semaphore&squot;s waitqueue head.&n; *&n; * Note that these functions are only called when there is&n; * contention on the lock, and as such all this is the&n; * &quot;non-critical&quot; part of the whole semaphore business. The&n; * critical part is the inline stuff in &lt;asm/semaphore.h&gt;&n; * where we want to avoid any extra jumps and calls.&n; */
multiline_comment|/*&n; * Logic:&n; *  - only on a boundary condition do we need to care. When we go&n; *    from a negative count to a non-negative, we wake people up.&n; *  - when we go from a non-negative count to a negative do we&n; *    (a) synchronize with the &quot;sleeper&quot; count and (b) make sure&n; *    that we&squot;re on the wakeup list before we synchronize so that&n; *    we cannot lose wakeup events.&n; */
DECL|function|__up
r_static
id|fastcall
r_void
id|__attribute_used__
id|__up
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|wake_up
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|__down
r_static
id|fastcall
r_void
id|__attribute_used__
id|__sched
id|__down
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|add_wait_queue_exclusive_locked
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|sleepers
op_assign
id|sem-&gt;sleepers
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Add &quot;everybody else&quot; into it. They aren&squot;t&n;&t;&t; * playing, because we own the spinlock in&n;&t;&t; * the wait_queue_head.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
op_minus
l_int|1
comma
op_amp
id|sem-&gt;count
)paren
)paren
(brace
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sem-&gt;sleepers
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* us - see -1 above */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
)brace
id|remove_wait_queue_locked
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|wake_up_locked
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
)brace
DECL|function|__down_interruptible
r_static
id|fastcall
r_int
id|__attribute_used__
id|__sched
id|__down_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|tsk
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|add_wait_queue_exclusive_locked
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|sem-&gt;sleepers
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|sleepers
op_assign
id|sem-&gt;sleepers
suffix:semicolon
multiline_comment|/*&n;&t;&t; * With signals pending, this turns into&n;&t;&t; * the trylock failure case - we won&squot;t be&n;&t;&t; * sleeping, and we* can&squot;t get the lock as&n;&t;&t; * it has contention. Just correct the count&n;&t;&t; * and exit.&n;&t;&t; */
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|EINTR
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
id|atomic_add
c_func
(paren
id|sleepers
comma
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Add &quot;everybody else&quot; into it. They aren&squot;t&n;&t;&t; * playing, because we own the spinlock in&n;&t;&t; * wait_queue_head. The &quot;-1&quot; is because we&squot;re&n;&t;&t; * still hoping to get the semaphore.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
op_minus
l_int|1
comma
op_amp
id|sem-&gt;count
)paren
)paren
(brace
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|sem-&gt;sleepers
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* us - see -1 above */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
)brace
id|remove_wait_queue_locked
c_func
(paren
op_amp
id|sem-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|wake_up_locked
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|tsk-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Trylock failed - make sure we correct for&n; * having decremented the count.&n; *&n; * We could have done the trylock with a&n; * single &quot;cmpxchg&quot; without failure cases,&n; * but then it wouldn&squot;t work on a 386.&n; */
DECL|function|__down_trylock
r_static
id|fastcall
r_int
id|__attribute_used__
id|__down_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|sleepers
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
id|sleepers
op_assign
id|sem-&gt;sleepers
op_plus
l_int|1
suffix:semicolon
id|sem-&gt;sleepers
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Add &quot;everybody else&quot; and us into it. They aren&squot;t&n;&t; * playing, because we own the spinlock in the&n;&t; * wait_queue_head.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|atomic_add_negative
c_func
(paren
id|sleepers
comma
op_amp
id|sem-&gt;count
)paren
)paren
(brace
id|wake_up_locked
c_func
(paren
op_amp
id|sem-&gt;wait
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|sem-&gt;wait.lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The semaphore operations have a special calling sequence that&n; * allow us to do a simpler in-line version of them. These routines&n; * need to convert that sequence back into the C sequence when&n; * there is contention on the semaphore.&n; *&n; * %eax contains the semaphore pointer on entry. Save the C-clobbered&n; * registers (%eax, %edx and %ecx) except %eax whish is either a return&n; * value or just clobbered..&n; */
id|asm
c_func
(paren
l_string|&quot;.section .sched.text&bslash;n&quot;
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __down_failed&bslash;n&quot;
l_string|&quot;__down_failed:&bslash;n&bslash;t&quot;
macro_line|#if defined(CONFIG_FRAME_POINTER)
l_string|&quot;pushl %ebp&bslash;n&bslash;t&quot;
l_string|&quot;movl  %esp,%ebp&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __down&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
macro_line|#if defined(CONFIG_FRAME_POINTER)
l_string|&quot;movl %ebp,%esp&bslash;n&bslash;t&quot;
l_string|&quot;popl %ebp&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.section .sched.text&bslash;n&quot;
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __down_failed_interruptible&bslash;n&quot;
l_string|&quot;__down_failed_interruptible:&bslash;n&bslash;t&quot;
macro_line|#if defined(CONFIG_FRAME_POINTER)
l_string|&quot;pushl %ebp&bslash;n&bslash;t&quot;
l_string|&quot;movl  %esp,%ebp&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __down_interruptible&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
macro_line|#if defined(CONFIG_FRAME_POINTER)
l_string|&quot;movl %ebp,%esp&bslash;n&bslash;t&quot;
l_string|&quot;popl %ebp&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.section .sched.text&bslash;n&quot;
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __down_failed_trylock&bslash;n&quot;
l_string|&quot;__down_failed_trylock:&bslash;n&bslash;t&quot;
macro_line|#if defined(CONFIG_FRAME_POINTER)
l_string|&quot;pushl %ebp&bslash;n&bslash;t&quot;
l_string|&quot;movl  %esp,%ebp&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __down_trylock&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
macro_line|#if defined(CONFIG_FRAME_POINTER)
l_string|&quot;movl %ebp,%esp&bslash;n&bslash;t&quot;
l_string|&quot;popl %ebp&bslash;n&bslash;t&quot;
macro_line|#endif
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.section .sched.text&bslash;n&quot;
l_string|&quot;.align 4&bslash;n&quot;
l_string|&quot;.globl __up_wakeup&bslash;n&quot;
l_string|&quot;__up_wakeup:&bslash;n&bslash;t&quot;
l_string|&quot;pushl %edx&bslash;n&bslash;t&quot;
l_string|&quot;pushl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;call __up&bslash;n&bslash;t&quot;
l_string|&quot;popl %ecx&bslash;n&bslash;t&quot;
l_string|&quot;popl %edx&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * rw spinlock fallbacks&n; */
macro_line|#if defined(CONFIG_SMP)
id|asm
c_func
(paren
l_string|&quot;.section .sched.text&bslash;n&quot;
l_string|&quot;.align&t;4&bslash;n&quot;
l_string|&quot;.globl&t;__write_lock_failed&bslash;n&quot;
l_string|&quot;__write_lock_failed:&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;addl&t;$&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;,(%eax)&bslash;n&quot;
l_string|&quot;1:&t;rep; nop&bslash;n&bslash;t&quot;
l_string|&quot;cmpl&t;$&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;,(%eax)&bslash;n&bslash;t&quot;
l_string|&quot;jne&t;1b&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;subl&t;$&quot;
id|RW_LOCK_BIAS_STR
l_string|&quot;,(%eax)&bslash;n&bslash;t&quot;
l_string|&quot;jnz&t;__write_lock_failed&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;.section .sched.text&bslash;n&quot;
l_string|&quot;.align&t;4&bslash;n&quot;
l_string|&quot;.globl&t;__read_lock_failed&bslash;n&quot;
l_string|&quot;__read_lock_failed:&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;incl&t;(%eax)&bslash;n&quot;
l_string|&quot;1:&t;rep; nop&bslash;n&bslash;t&quot;
l_string|&quot;cmpl&t;$1,(%eax)&bslash;n&bslash;t&quot;
l_string|&quot;js&t;1b&bslash;n&bslash;t&quot;
id|LOCK
l_string|&quot;decl&t;(%eax)&bslash;n&bslash;t&quot;
l_string|&quot;js&t;__read_lock_failed&bslash;n&bslash;t&quot;
l_string|&quot;ret&quot;
)paren
suffix:semicolon
macro_line|#endif
eof
