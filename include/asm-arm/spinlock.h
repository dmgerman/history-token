macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
macro_line|#if __LINUX_ARM_ARCH__ &lt; 6
macro_line|#error SMP not supported on pre-ARMv6 CPUs
macro_line|#endif
multiline_comment|/*&n; * ARMv6 Spin-locking.&n; *&n; * We (exclusively) read the old value, and decrement it.  If it&n; * hits zero, we may have won the lock, so we try (exclusively)&n; * storing it.&n; *&n; * Unlocked value: 0&n; * Locked value: 1&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;(spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { *(x) = SPIN_LOCK_UNLOCKED; } while (0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while (spin_is_locked(x))
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
DECL|function|_raw_spin_lock
r_static
r_inline
r_void
id|_raw_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldrex&t;%0, [%1]&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;strexeq&t;%0, %2, [%1]&bslash;n&quot;
l_string|&quot;&t;teqeq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|lock-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|1
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_spin_trylock
r_static
r_inline
r_int
id|_raw_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;ldrex&t;%0, [%1]&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;strexeq&t;%0, %2, [%1]&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|lock-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|1
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|tmp
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|_raw_spin_unlock
r_static
r_inline
r_void
id|_raw_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&t;str&t;%1, [%0]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|lock-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * RWLOCKS&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED&t;(rwlock_t) { 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)&t;&t;do { *(x) + RW_LOCK_UNLOCKED; } while (0)
multiline_comment|/*&n; * Write locks are easy - we just set bit 31.  When unlocking, we can&n; * just write zero since the lock is exclusively held.&n; */
DECL|function|_raw_write_lock
r_static
r_inline
r_void
id|_raw_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldrex&t;%0, [%1]&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;strexeq&t;%0, %2, [%1]&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x80000000
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_write_unlock
r_static
r_inline
r_void
id|_raw_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;str&t;%1, [%0]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read locks are a bit more hairy:&n; *  - Exclusively load the lock value.&n; *  - Increment it.&n; *  - Store new lock value if positive, and we still own this location.&n; *    If the value is negative, we&squot;ve already failed.&n; *  - If we failed to store the value, we want a negative result.&n; *  - If we failed, try again.&n; * Unlocking is similarly hairy.  We may have multiple read locks&n; * currently active.  However, we know we won&squot;t have any write&n; * locks.&n; */
DECL|function|_raw_read_lock
r_static
r_inline
r_void
id|_raw_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
comma
id|tmp2
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldrex&t;%0, [%2]&bslash;n&quot;
l_string|&quot;&t;adds&t;%0, %0, #1&bslash;n&quot;
l_string|&quot;&t;strexpl&t;%1, %0, [%2]&bslash;n&quot;
l_string|&quot;&t;rsbpls&t;%0, %1, #0&bslash;n&quot;
l_string|&quot;&t;bmi&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_read_unlock
r_static
r_inline
r_void
id|_raw_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldrex&t;%0, [%2]&bslash;n&quot;
l_string|&quot;&t;sub&t;%0, %0, #1&bslash;n&quot;
l_string|&quot;&t;strex&t;%1, %0, [%2]&bslash;n&quot;
l_string|&quot;&t;teq&t;%1, #0&bslash;n&quot;
l_string|&quot;&t;bne&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|_raw_read_trylock
mdefine_line|#define _raw_read_trylock(lock) generic_raw_read_trylock(lock)
DECL|function|_raw_write_trylock
r_static
r_inline
r_int
id|_raw_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldrex&t;%0, [%1]&bslash;n&quot;
l_string|&quot;&t;teq&t;%0, #0&bslash;n&quot;
l_string|&quot;&t;strexeq&t;%0, %2, [%1]&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|rw-&gt;lock
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0x80000000
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|tmp
op_eq
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
