macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* we seem to be the only architecture that uses 0 to mean locked - but we&n; * have to.  prumpf */
DECL|macro|SPIN_LOCK_UNLOCKED
macro_line|#undef SPIN_LOCK_UNLOCKED
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 1 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { (x)-&gt;lock = 1; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while(((volatile spinlock_t *)(x))-&gt;lock == 1)
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x) &bslash;&n;&t;do { while(__ldcw(&amp;(x)-&gt;lock) == 0); } while(0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(x) &bslash;&n;&t;do { (x)-&gt;lock = 1; } while(0)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(x) (__ldcw(&amp;(x)-&gt;lock) == 1)
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
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { SPIN_LOCK_UNLOCKED, 0 }
multiline_comment|/* read_lock, read_unlock are pretty straightforward.  Of course it somehow&n; * sucks we end up saving/restoring flags twice for read_lock_irqsave aso. */
DECL|function|read_lock
r_static
r_inline
r_void
id|read_lock
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rw-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|rw-&gt;counter
op_increment
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rw-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|read_unlock
r_static
r_inline
r_void
id|read_unlock
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rw-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|rw-&gt;counter
op_decrement
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rw-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* write_lock is less trivial.  We optimistically grab the lock and check&n; * if we surprised any readers.  If so we release the lock and wait till&n; * they&squot;re all gone before trying again&n; *&n; * Also note that we don&squot;t use the _irqsave / _irqrestore suffixes here.&n; * If we&squot;re called with interrupts enabled and we&squot;ve got readers (or other&n; * writers) in interrupt handlers someone fucked up and we&squot;d dead-lock&n; * sooner or later anyway.   prumpf */
DECL|function|write_lock
r_static
r_inline
r_void
id|write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|retry
suffix:colon
id|spin_lock
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
id|spin_unlock
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
)brace
multiline_comment|/* write_unlock is absolutely trivial - we don&squot;t have to wait for anything */
DECL|function|write_unlock
r_static
r_inline
r_void
id|write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|rw-&gt;lock
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SPINLOCK_H */
eof
