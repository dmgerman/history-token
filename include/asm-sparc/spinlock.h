multiline_comment|/* spinlock.h: 32-bit Sparc spinlock support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC_SPINLOCK_H
DECL|macro|__SPARC_SPINLOCK_H
mdefine_line|#define __SPARC_SPINLOCK_H
macro_line|#include &lt;linux/threads.h&gt;&t;/* For NR_CPUS */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
DECL|struct|_spinlock_debug
r_struct
id|_spinlock_debug
(brace
DECL|member|lock
r_int
r_char
id|lock
suffix:semicolon
DECL|member|owner_pc
r_int
r_int
id|owner_pc
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|typedef|spinlock_t
r_typedef
r_struct
id|_spinlock_debug
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;(spinlock_t) { 0, 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lp)&t;do { *(lp)= SPIN_LOCK_UNLOCKED; } while(0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lp)  (*((volatile unsigned char *)(&amp;((lp)-&gt;lock))) != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lp)&t;do { barrier(); } while(*(volatile unsigned char *)(&amp;(lp)-&gt;lock))
r_extern
r_void
id|_do_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_int
id|_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_do_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
DECL|macro|_raw_spin_trylock
mdefine_line|#define _raw_spin_trylock(lp)&t;_spin_trylock(lp)
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(lock)&t;_do_spin_lock(lock, &quot;spin_lock&quot;)
DECL|macro|_raw_spin_unlock
mdefine_line|#define _raw_spin_unlock(lock)&t;_do_spin_unlock(lock)
DECL|struct|_rwlock_debug
r_struct
id|_rwlock_debug
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|owner_pc
r_int
r_int
id|owner_pc
suffix:semicolon
DECL|member|reader_pc
r_int
r_int
id|reader_pc
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
DECL|member|break_lock
r_int
r_int
id|break_lock
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|typedef|rwlock_t
r_typedef
r_struct
id|_rwlock_debug
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0, {0} }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lp)&t;do { *(lp)= RW_LOCK_UNLOCKED; } while(0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(lp) ((lp)-&gt;lock != 0)
r_extern
r_void
id|_do_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|_do_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|_do_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
comma
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_void
id|_do_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(lock)&t;&bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_read_lock(lock, &quot;read_lock&quot;); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_read_unlock(lock, &quot;read_unlock&quot;); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_write_lock(lock, &quot;write_lock&quot;); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_write_unlock(lock); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
macro_line|#else /* !CONFIG_DEBUG_SPINLOCK */
r_typedef
r_struct
(brace
DECL|member|lock
r_int
r_char
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
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;{ 0, }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)   (*((unsigned char *)(lock)) = 0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)    (*((volatile unsigned char *)(lock)) != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock) &bslash;&n;do { &bslash;&n;&t;barrier(); &bslash;&n;} while(*((volatile unsigned char *)lock))
DECL|function|_raw_spin_lock
r_extern
id|__inline__
r_void
id|_raw_spin_lock
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
l_string|&quot;&bslash;n1:&bslash;n&bslash;t&quot;
l_string|&quot;ldstub&t;[%0], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;orcc&t;%%g2, 0x0, %%g0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a&t;2f&bslash;n&bslash;t&quot;
l_string|&quot; ldub&t;[%0], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;.subsection&t;2&bslash;n&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;orcc&t;%%g2, 0x0, %%g0&bslash;n&bslash;t&quot;
l_string|&quot;bne,a&t;2b&bslash;n&bslash;t&quot;
l_string|&quot; ldub&t;[%0], %%g2&bslash;n&bslash;t&quot;
l_string|&quot;b,a&t;1b&bslash;n&bslash;t&quot;
l_string|&quot;.previous&bslash;n&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|lock
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|function|_raw_spin_trylock
r_extern
id|__inline__
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
id|result
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldstub [%1], %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
(paren
id|result
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|_raw_spin_unlock
r_extern
id|__inline__
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
l_string|&quot;stb %%g0, [%0]&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|lock
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; *&n; * XXX This might create some problems with my dual spinlock&n; * XXX scheme, deadlocks etc. -DaveM&n; */
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
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lp)&t;do { *(lp)= RW_LOCK_UNLOCKED; } while(0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(lp) ((lp)-&gt;lock != 0)
multiline_comment|/* Sort of like atomic_t&squot;s on Sparc, but even more clever.&n; *&n; *&t;------------------------------------&n; *&t;| 24-bit counter           | wlock |  rwlock_t&n; *&t;------------------------------------&n; *&t; 31                       8 7     0&n; *&n; * wlock signifies the one writer is in or somebody is updating&n; * counter. For a writer, if he successfully acquires the wlock,&n; * but counter is non-zero, he has to release the lock and wait,&n; * till both counter and wlock are zero.&n; *&n; * Unfortunately this scheme limits us to ~16,000,000 cpus.&n; */
DECL|function|_read_lock
r_extern
id|__inline__
r_void
id|_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_register
id|rwlock_t
op_star
id|lp
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|lp
op_assign
id|rw
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___rw_read_enter&bslash;n&bslash;t&quot;
l_string|&quot; ldstub&t;[%%g1 + 3], %%g2&bslash;n&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|lp
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_read_lock(lock); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|function|_read_unlock
r_extern
id|__inline__
r_void
id|_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
(brace
r_register
id|rwlock_t
op_star
id|lp
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|lp
op_assign
id|rw
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___rw_read_exit&bslash;n&bslash;t&quot;
l_string|&quot; ldstub&t;[%%g1 + 3], %%g2&bslash;n&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|lp
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_read_unlock(lock); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|function|_raw_write_lock
r_extern
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
r_register
id|rwlock_t
op_star
id|lp
id|asm
c_func
(paren
l_string|&quot;g1&quot;
)paren
suffix:semicolon
id|lp
op_assign
id|rw
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov&t;%%o7, %%g4&bslash;n&bslash;t&quot;
l_string|&quot;call&t;___rw_write_enter&bslash;n&bslash;t&quot;
l_string|&quot; ldstub&t;[%%g1 + 3], %%g2&bslash;n&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|lp
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g4&quot;
comma
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(rw)&t;do { (rw)-&gt;lock = 0; } while(0)
macro_line|#endif /* CONFIG_DEBUG_SPINLOCK */
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* __SPARC_SPINLOCK_H */
eof
