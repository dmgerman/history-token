macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* Note that PA-RISC has to use `1&squot; to mean unlocked and `0&squot; to mean locked&n; * since it only has load-and-zero.&n; */
DECL|macro|SPIN_LOCK_UNLOCKED
macro_line|#undef SPIN_LOCK_UNLOCKED
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 1 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { (x)-&gt;lock = 1; } while(0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x) ((x)-&gt;lock == 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while(((volatile spinlock_t *)(x))-&gt;lock == 0)
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
macro_line|#if 1
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(x) do { &bslash;&n;&t;while (__ldcw (&amp;(x)-&gt;lock) == 0) &bslash;&n;&t;&t;while (((x)-&gt;lock) == 0) ; } while (0)
macro_line|#else
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(x) &bslash;&n;&t;do { while(__ldcw(&amp;(x)-&gt;lock) == 0); } while(0)
macro_line|#endif
DECL|macro|_raw_spin_unlock
mdefine_line|#define _raw_spin_unlock(x) &bslash;&n;&t;do { (x)-&gt;lock = 1; } while(0)
DECL|macro|_raw_spin_trylock
mdefine_line|#define _raw_spin_trylock(x) (__ldcw(&amp;(x)-&gt;lock) != 0)
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|counter
r_volatile
r_int
id|counter
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { {1}, 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lp)&t;do { *(lp) = RW_LOCK_UNLOCKED; } while (0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(lp) ((lp)-&gt;counter != 0)
multiline_comment|/* read_lock, read_unlock are pretty straightforward.  Of course it somehow&n; * sucks we end up saving/restoring flags twice for read_lock_irqsave aso. */
DECL|function|_raw_read_lock
r_static
id|__inline__
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
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|_raw_spin_lock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
id|rw-&gt;counter
op_increment
suffix:semicolon
id|_raw_spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|_raw_read_unlock
r_static
id|__inline__
r_void
id|_raw_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
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
id|_raw_spin_lock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
id|rw-&gt;counter
op_decrement
suffix:semicolon
id|_raw_spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* write_lock is less trivial.  We optimistically grab the lock and check&n; * if we surprised any readers.  If so we release the lock and wait till&n; * they&squot;re all gone before trying again&n; *&n; * Also note that we don&squot;t use the _irqsave / _irqrestore suffixes here.&n; * If we&squot;re called with interrupts enabled and we&squot;ve got readers (or other&n; * writers) in interrupt handlers someone fucked up and we&squot;d dead-lock&n; * sooner or later anyway.   prumpf */
DECL|function|_raw_write_lock
r_static
id|__inline__
r_void
id|_raw_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|retry
suffix:colon
id|_raw_spin_lock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rw-&gt;counter
op_ne
l_int|0
)paren
(brace
multiline_comment|/* this basically never happens */
id|_raw_spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|rw-&gt;counter
op_ne
l_int|0
)paren
(brace
suffix:semicolon
)brace
r_goto
id|retry
suffix:semicolon
)brace
multiline_comment|/* got it.  now leave without unlocking */
id|rw-&gt;counter
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* remember we are locked */
)brace
multiline_comment|/* write_unlock is absolutely trivial - we don&squot;t have to wait for anything */
DECL|function|_raw_write_unlock
r_static
id|__inline__
r_void
id|_raw_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|rw-&gt;counter
op_assign
l_int|0
suffix:semicolon
id|_raw_spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|is_read_locked
r_static
id|__inline__
r_int
id|is_read_locked
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_return
id|rw-&gt;counter
OG
l_int|0
suffix:semicolon
)brace
DECL|function|is_write_locked
r_static
id|__inline__
r_int
id|is_write_locked
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_return
id|rw-&gt;counter
OL
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
