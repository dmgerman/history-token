multiline_comment|/*&n; * Copyright (2004) Linus Torvalds&n; *&n; * Author: Zwane Mwaikambo &lt;zwane@fsmlabs.com&gt;&n; *&n; * Copyright (2004) Ingo Molnar&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; * Generic declaration of the raw read_trylock() function,&n; * architectures are supposed to optimize this:&n; */
DECL|function|generic_raw_read_trylock
r_int
id|__lockfunc
id|generic_raw_read_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|_raw_read_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|generic_raw_read_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|generic_raw_read_trylock
)paren
suffix:semicolon
DECL|function|_spin_trylock
r_int
id|__lockfunc
id|_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_raw_spin_trylock
c_func
(paren
id|lock
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|_spin_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_trylock
)paren
suffix:semicolon
DECL|function|_read_trylock
r_int
id|__lockfunc
id|_read_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_raw_read_trylock
c_func
(paren
id|lock
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|_read_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|_read_trylock
)paren
suffix:semicolon
DECL|function|_write_trylock
r_int
id|__lockfunc
id|_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_raw_write_trylock
c_func
(paren
id|lock
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|_write_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|_write_trylock
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_PREEMPT
DECL|function|_read_lock
r_void
id|__lockfunc
id|_read_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_read_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_read_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_read_lock
)paren
suffix:semicolon
DECL|function|_spin_lock_irqsave
r_int
r_int
id|__lockfunc
id|_spin_lock_irqsave
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_spin_lock_flags
c_func
(paren
id|lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|variable|_spin_lock_irqsave
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_lock_irqsave
)paren
suffix:semicolon
DECL|function|_spin_lock_irq
r_void
id|__lockfunc
id|_spin_lock_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_spin_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_spin_lock_irq
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_lock_irq
)paren
suffix:semicolon
DECL|function|_spin_lock_bh
r_void
id|__lockfunc
id|_spin_lock_bh
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_spin_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_spin_lock_bh
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_lock_bh
)paren
suffix:semicolon
DECL|function|_read_lock_irqsave
r_int
r_int
id|__lockfunc
id|_read_lock_irqsave
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_read_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|variable|_read_lock_irqsave
id|EXPORT_SYMBOL
c_func
(paren
id|_read_lock_irqsave
)paren
suffix:semicolon
DECL|function|_read_lock_irq
r_void
id|__lockfunc
id|_read_lock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_read_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_read_lock_irq
id|EXPORT_SYMBOL
c_func
(paren
id|_read_lock_irq
)paren
suffix:semicolon
DECL|function|_read_lock_bh
r_void
id|__lockfunc
id|_read_lock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_read_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_read_lock_bh
id|EXPORT_SYMBOL
c_func
(paren
id|_read_lock_bh
)paren
suffix:semicolon
DECL|function|_write_lock_irqsave
r_int
r_int
id|__lockfunc
id|_write_lock_irqsave
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_write_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
r_return
id|flags
suffix:semicolon
)brace
DECL|variable|_write_lock_irqsave
id|EXPORT_SYMBOL
c_func
(paren
id|_write_lock_irqsave
)paren
suffix:semicolon
DECL|function|_write_lock_irq
r_void
id|__lockfunc
id|_write_lock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_write_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_write_lock_irq
id|EXPORT_SYMBOL
c_func
(paren
id|_write_lock_irq
)paren
suffix:semicolon
DECL|function|_write_lock_bh
r_void
id|__lockfunc
id|_write_lock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_write_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_write_lock_bh
id|EXPORT_SYMBOL
c_func
(paren
id|_write_lock_bh
)paren
suffix:semicolon
DECL|function|_spin_lock
r_void
id|__lockfunc
id|_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_spin_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_spin_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_lock
)paren
suffix:semicolon
DECL|function|_write_lock
r_void
id|__lockfunc
id|_write_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_write_lock
c_func
(paren
id|lock
)paren
suffix:semicolon
)brace
DECL|variable|_write_lock
id|EXPORT_SYMBOL
c_func
(paren
id|_write_lock
)paren
suffix:semicolon
macro_line|#else /* CONFIG_PREEMPT: */
multiline_comment|/*&n; * This could be a long-held lock. We both prepare to spin for a long&n; * time (making _this_ CPU preemptable if possible), and we also signal&n; * towards that other CPU that it should break the lock ASAP.&n; *&n; * (We do this in a function because inlining it would be excessive.)&n; */
DECL|macro|BUILD_LOCK_OPS
mdefine_line|#define BUILD_LOCK_OPS(op, locktype)&t;&t;&t;&t;&t;&bslash;&n;void __lockfunc _##op##_lock(locktype##_t *lock)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_disable();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (likely(_raw_##op##_trylock(lock)))&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_enable();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!(lock)-&gt;break_lock)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;(lock)-&gt;break_lock = 1;&t;&t;&t;&t;&bslash;&n;&t;&t;while (!op##_can_lock(lock) &amp;&amp; (lock)-&gt;break_lock)&t;&bslash;&n;&t;&t;&t;cpu_relax();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_disable();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(lock)-&gt;break_lock = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;EXPORT_SYMBOL(_##op##_lock);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;unsigned long __lockfunc _##op##_lock_irqsave(locktype##_t *lock)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;preempt_disable();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (;;) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_save(flags);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (likely(_raw_##op##_trylock(lock)))&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;local_irq_restore(flags);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_enable();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (!(lock)-&gt;break_lock)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;(lock)-&gt;break_lock = 1;&t;&t;&t;&t;&bslash;&n;&t;&t;while (!op##_can_lock(lock) &amp;&amp; (lock)-&gt;break_lock)&t;&bslash;&n;&t;&t;&t;cpu_relax();&t;&t;&t;&t;&t;&bslash;&n;&t;&t;preempt_disable();&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(lock)-&gt;break_lock = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return flags;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;EXPORT_SYMBOL(_##op##_lock_irqsave);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;void __lockfunc _##op##_lock_irq(locktype##_t *lock)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_##op##_lock_irqsave(lock);&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;EXPORT_SYMBOL(_##op##_lock_irq);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;void __lockfunc _##op##_lock_bh(locktype##_t *lock)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long flags;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/*&t;&t;&t;&t;&t;&t;&t;*/&t;&bslash;&n;&t;/* Careful: we must exclude softirqs too, hence the&t;*/&t;&bslash;&n;&t;/* irq-disabling. We use the generic preemption-aware&t;*/&t;&bslash;&n;&t;/* function:&t;&t;&t;&t;&t;&t;*/&t;&bslash;&n;&t;/**/&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flags = _##op##_lock_irqsave(lock);&t;&t;&t;&t;&bslash;&n;&t;local_bh_disable();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;local_irq_restore(flags);&t;&t;&t;&t;&t;&bslash;&n;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;EXPORT_SYMBOL(_##op##_lock_bh)
multiline_comment|/*&n; * Build preemption-friendly versions of the following&n; * lock-spinning functions:&n; *&n; *         _[spin|read|write]_lock()&n; *         _[spin|read|write]_lock_irq()&n; *         _[spin|read|write]_lock_irqsave()&n; *         _[spin|read|write]_lock_bh()&n; */
id|BUILD_LOCK_OPS
c_func
(paren
id|spin
comma
id|spinlock
)paren
suffix:semicolon
id|BUILD_LOCK_OPS
c_func
(paren
id|read
comma
id|rwlock
)paren
suffix:semicolon
id|BUILD_LOCK_OPS
c_func
(paren
id|write
comma
id|rwlock
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PREEMPT */
DECL|function|_spin_unlock
r_void
id|__lockfunc
id|_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|_raw_spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_spin_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_unlock
)paren
suffix:semicolon
DECL|function|_write_unlock
r_void
id|__lockfunc
id|_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|_raw_write_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_write_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_write_unlock
)paren
suffix:semicolon
DECL|function|_read_unlock
r_void
id|__lockfunc
id|_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|_raw_read_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_read_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|_read_unlock
)paren
suffix:semicolon
DECL|function|_spin_unlock_irqrestore
r_void
id|__lockfunc
id|_spin_unlock_irqrestore
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_int
r_int
id|flags
)paren
(brace
id|_raw_spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_spin_unlock_irqrestore
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_unlock_irqrestore
)paren
suffix:semicolon
DECL|function|_spin_unlock_irq
r_void
id|__lockfunc
id|_spin_unlock_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|_raw_spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_spin_unlock_irq
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_unlock_irq
)paren
suffix:semicolon
DECL|function|_spin_unlock_bh
r_void
id|__lockfunc
id|_spin_unlock_bh
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|_raw_spin_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_spin_unlock_bh
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_unlock_bh
)paren
suffix:semicolon
DECL|function|_read_unlock_irqrestore
r_void
id|__lockfunc
id|_read_unlock_irqrestore
c_func
(paren
id|rwlock_t
op_star
id|lock
comma
r_int
r_int
id|flags
)paren
(brace
id|_raw_read_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_read_unlock_irqrestore
id|EXPORT_SYMBOL
c_func
(paren
id|_read_unlock_irqrestore
)paren
suffix:semicolon
DECL|function|_read_unlock_irq
r_void
id|__lockfunc
id|_read_unlock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|_raw_read_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_read_unlock_irq
id|EXPORT_SYMBOL
c_func
(paren
id|_read_unlock_irq
)paren
suffix:semicolon
DECL|function|_read_unlock_bh
r_void
id|__lockfunc
id|_read_unlock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|_raw_read_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_read_unlock_bh
id|EXPORT_SYMBOL
c_func
(paren
id|_read_unlock_bh
)paren
suffix:semicolon
DECL|function|_write_unlock_irqrestore
r_void
id|__lockfunc
id|_write_unlock_irqrestore
c_func
(paren
id|rwlock_t
op_star
id|lock
comma
r_int
r_int
id|flags
)paren
(brace
id|_raw_write_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_write_unlock_irqrestore
id|EXPORT_SYMBOL
c_func
(paren
id|_write_unlock_irqrestore
)paren
suffix:semicolon
DECL|function|_write_unlock_irq
r_void
id|__lockfunc
id|_write_unlock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|_raw_write_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_write_unlock_irq
id|EXPORT_SYMBOL
c_func
(paren
id|_write_unlock_irq
)paren
suffix:semicolon
DECL|function|_write_unlock_bh
r_void
id|__lockfunc
id|_write_unlock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
(brace
id|_raw_write_unlock
c_func
(paren
id|lock
)paren
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|_write_unlock_bh
id|EXPORT_SYMBOL
c_func
(paren
id|_write_unlock_bh
)paren
suffix:semicolon
DECL|function|_spin_trylock_bh
r_int
id|__lockfunc
id|_spin_trylock_bh
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|local_bh_disable
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_raw_spin_trylock
c_func
(paren
id|lock
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|local_bh_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|_spin_trylock_bh
id|EXPORT_SYMBOL
c_func
(paren
id|_spin_trylock_bh
)paren
suffix:semicolon
DECL|function|in_lock_functions
r_int
id|in_lock_functions
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* Linker adds these: start and end of __lockfunc functions */
r_extern
r_char
id|__lock_text_start
(braket
)braket
comma
id|__lock_text_end
(braket
)braket
suffix:semicolon
r_return
id|addr
op_ge
(paren
r_int
r_int
)paren
id|__lock_text_start
op_logical_and
id|addr
OL
(paren
r_int
r_int
)paren
id|__lock_text_end
suffix:semicolon
)brace
DECL|variable|in_lock_functions
id|EXPORT_SYMBOL
c_func
(paren
id|in_lock_functions
)paren
suffix:semicolon
eof
