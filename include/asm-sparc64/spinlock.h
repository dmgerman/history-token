multiline_comment|/* spinlock.h: 64-bit Sparc spinlock support.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC64_SPINLOCK_H
DECL|macro|__SPARC64_SPINLOCK_H
mdefine_line|#define __SPARC64_SPINLOCK_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* To get debugging spinlocks which detect and catch&n; * deadlock situations, set DEBUG_SPINLOCKS in the sparc64&n; * specific makefile and rebuild your kernel.&n; */
multiline_comment|/* All of these locking primitives are expected to work properly&n; * even in an RMO memory model, which currently is what the kernel&n; * runs in.&n; *&n; * There is another issue.  Because we play games to save cycles&n; * in the non-contention case, we need to be extra careful about&n; * branch targets into the &quot;spinning&quot; code.  They live in their&n; * own section, but the newer V9 branches have a shorter range&n; * than the traditional 32-bit sparc branch variants.  The rule&n; * is that the branches that go into and out of the spinner sections&n; * must be pre-V9 branches.&n; */
macro_line|#ifndef SPIN_LOCK_DEBUG
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
DECL|function|spin_lock
r_extern
id|__inline__
r_void
id|spin_lock
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
"&quot;"
l_int|1
suffix:colon
id|ldstub
(braket
op_mod
l_int|0
)braket
comma
op_mod
op_mod
id|g7
id|brnz
comma
id|pn
op_mod
op_mod
id|g7
comma
l_float|2f
id|membar
macro_line|#StoreLoad | #StoreStore
dot
id|subsection
l_int|2
l_int|2
suffix:colon
id|ldub
(braket
op_mod
l_int|0
)braket
comma
op_mod
op_mod
id|g7
id|brnz
comma
id|pt
op_mod
op_mod
id|g7
comma
l_int|2
id|b
id|membar
macro_line|#LoadLoad
id|b
comma
id|a
comma
id|pt
op_mod
op_mod
id|xcc
comma
l_int|1
id|b
dot
id|previous
"&quot;"
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|lock
)paren
suffix:colon
l_string|&quot;g7&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|function|spin_trylock
r_extern
id|__inline__
r_int
id|spin_trylock
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
DECL|function|spin_unlock
r_extern
id|__inline__
r_void
id|spin_unlock
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
macro_line|#else /* !(SPIN_LOCK_DEBUG) */
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
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lp)&t;_spin_trylock(lp)
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;_do_spin_lock(lock, &quot;spin_lock&quot;)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;_do_spin_unlock(lock)
macro_line|#endif /* SPIN_LOCK_DEBUG */
multiline_comment|/* Multi-reader locks, these are much saner than the 32-bit Sparc ones... */
macro_line|#ifndef SPIN_LOCK_DEBUG
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
DECL|macro|read_lock
mdefine_line|#define read_lock(p)&t;__read_lock(p)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(p)&t;__read_unlock(p)
DECL|macro|write_lock
mdefine_line|#define write_lock(p)&t;__write_lock(p)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(p)&t;__write_unlock(p)
macro_line|#else /* !(SPIN_LOCK_DEBUG) */
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
l_int|4
)braket
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED&t;(rwlock_t) { 0, 0, 0xff, { 0, 0, 0, 0 } }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lp) do { *(lp) = RW_LOCK_UNLOCKED; } while(0)
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
DECL|macro|read_lock
mdefine_line|#define read_lock(lock)&t;&bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;__save_and_cli(flags); &bslash;&n;&t;_do_read_lock(lock, &quot;read_lock&quot;); &bslash;&n;&t;__restore_flags(flags); &bslash;&n;} while(0)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;__save_and_cli(flags); &bslash;&n;&t;_do_read_unlock(lock, &quot;read_unlock&quot;); &bslash;&n;&t;__restore_flags(flags); &bslash;&n;} while(0)
DECL|macro|write_lock
mdefine_line|#define write_lock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;__save_and_cli(flags); &bslash;&n;&t;_do_write_lock(lock, &quot;write_lock&quot;); &bslash;&n;&t;__restore_flags(flags); &bslash;&n;} while(0)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(lock) &bslash;&n;do {&t;unsigned long flags; &bslash;&n;&t;__save_and_cli(flags); &bslash;&n;&t;_do_write_unlock(lock); &bslash;&n;&t;__restore_flags(flags); &bslash;&n;} while(0)
macro_line|#endif /* SPIN_LOCK_DEBUG */
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_SPINLOCK_H) */
eof
