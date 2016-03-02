multiline_comment|/* spinlock.h: 64-bit Sparc spinlock support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SPINLOCK_H
DECL|macro|__SPARC64_SPINLOCK_H
mdefine_line|#define __SPARC64_SPINLOCK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;&t;/* For NR_CPUS */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* To get debugging spinlocks which detect and catch&n; * deadlock situations, set CONFIG_DEBUG_SPINLOCK&n; * and rebuild your kernel.&n; */
multiline_comment|/* All of these locking primitives are expected to work properly&n; * even in an RMO memory model, which currently is what the kernel&n; * runs in.&n; *&n; * There is another issue.  Because we play games to save cycles&n; * in the non-contention case, we need to be extra careful about&n; * branch targets into the &quot;spinning&quot; code.  They live in their&n; * own section, but the newer V9 branches have a shorter range&n; * than the traditional 32-bit sparc branch variants.  The rule&n; * is that the branches that go into and out of the spinner sections&n; * must be pre-V9 branches.&n; */
macro_line|#ifndef CONFIG_DEBUG_SPINLOCK
DECL|typedef|spinlock_t
r_typedef
r_int
r_char
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;0
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;(*((unsigned char *)(lock)) = 0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)&t;(*((volatile unsigned char *)(lock)) != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;&bslash;&n;do {&t;membar(&quot;#LoadLoad&quot;);&t;&bslash;&n;} while(*((volatile unsigned char *)lock))
multiline_comment|/* arch/sparc64/lib/spinlock.S */
r_extern
r_void
id|_raw_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
DECL|function|_raw_spin_trylock
r_static
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
l_string|&quot;ldstub [%1], %0&bslash;n&bslash;t&quot;
l_string|&quot;membar #StoreLoad | #StoreStore&quot;
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
r_static
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
l_string|&quot;membar&t;#StoreStore | #LoadStore&bslash;n&bslash;t&quot;
l_string|&quot;stb&t;%%g0, [%0]&quot;
suffix:colon
multiline_comment|/* No outputs */
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
r_extern
r_void
id|_raw_spin_lock_flags
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
suffix:semicolon
macro_line|#else /* !(CONFIG_DEBUG_SPINLOCK) */
r_typedef
r_struct
(brace
DECL|member|lock
r_int
r_char
id|lock
suffix:semicolon
DECL|member|owner_pc
DECL|member|owner_cpu
r_int
r_int
id|owner_pc
comma
id|owner_cpu
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0, 0, 0xff }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(__lock)&t;&bslash;&n;do {&t;(__lock)-&gt;lock = 0; &bslash;&n;&t;(__lock)-&gt;owner_pc = 0; &bslash;&n;&t;(__lock)-&gt;owner_cpu = 0xff; &bslash;&n;} while(0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(__lock)&t;(*((volatile unsigned char *)(&amp;((__lock)-&gt;lock))) != 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(__lock)&t;&bslash;&n;do { &bslash;&n;&t;membar(&quot;#LoadLoad&quot;); &bslash;&n;} while(*((volatile unsigned char *)(&amp;((__lock)-&gt;lock))))
r_extern
r_void
id|_do_spin_lock
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
r_void
id|_do_spin_unlock
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_int
id|_spin_trylock
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
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
macro_line|#endif /* CONFIG_DEBUG_SPINLOCK */
multiline_comment|/* Multi-reader locks, these are much saner than the 32-bit Sparc ones... */
macro_line|#ifndef CONFIG_DEBUG_SPINLOCK
DECL|typedef|rwlock_t
r_typedef
r_int
r_int
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED&t;0
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lp) do { *(lp) = RW_LOCK_UNLOCKED; } while(0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(x) (*(x) != RW_LOCK_UNLOCKED)
r_extern
r_void
id|__read_lock
c_func
(paren
id|rwlock_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__read_unlock
c_func
(paren
id|rwlock_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__write_lock
c_func
(paren
id|rwlock_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__write_unlock
c_func
(paren
id|rwlock_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__write_trylock
c_func
(paren
id|rwlock_t
op_star
)paren
suffix:semicolon
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(p)&t;__read_lock(p)
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(p)&t;__read_unlock(p)
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(p)&t;__write_lock(p)
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(p)&t;__write_unlock(p)
DECL|macro|_raw_write_trylock
mdefine_line|#define _raw_write_trylock(p)&t;__write_trylock(p)
macro_line|#else /* !(CONFIG_DEBUG_SPINLOCK) */
r_typedef
r_struct
(brace
DECL|member|lock
r_int
r_int
id|lock
suffix:semicolon
DECL|member|writer_pc
DECL|member|writer_cpu
r_int
r_int
id|writer_pc
comma
id|writer_cpu
suffix:semicolon
DECL|member|reader_pc
r_int
r_int
id|reader_pc
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED&t;(rwlock_t) { 0, 0, 0xff, { } }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lp) do { *(lp) = RW_LOCK_UNLOCKED; } while(0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(x) ((x)-&gt;lock != 0)
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
r_extern
r_int
id|_do_write_trylock
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
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_read_lock(lock, &quot;read_lock&quot;); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_read_unlock(lock, &quot;read_unlock&quot;); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_write_lock(lock, &quot;write_lock&quot;); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_do_write_unlock(lock); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;} while(0)
DECL|macro|_raw_write_trylock
mdefine_line|#define _raw_write_trylock(lock) &bslash;&n;({&t;unsigned long flags; &bslash;&n;&t;int val; &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;val = _do_write_trylock(lock, &quot;write_trylock&quot;); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;&t;val; &bslash;&n;})
macro_line|#endif /* CONFIG_DEBUG_SPINLOCK */
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_SPINLOCK_H) */
eof
