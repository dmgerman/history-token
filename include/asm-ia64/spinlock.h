macro_line|#ifndef _ASM_IA64_SPINLOCK_H
DECL|macro|_ASM_IA64_SPINLOCK_H
mdefine_line|#define _ASM_IA64_SPINLOCK_H
multiline_comment|/*&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * This file is used for SMP configurations only.&n; */
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;&t;&t;(spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;&t;&t;((x)-&gt;lock = 0)
macro_line|#ifdef ASM_SUPPORTED
multiline_comment|/*&n; * Try to get the lock.  If we fail to get the lock, make a non-standard call to&n; * ia64_spinlock_contention().  We do not use a normal call because that would force all&n; * callers of spin_lock() to be non-leaf routines.  Instead, ia64_spinlock_contention() is&n; * carefully coded to touch only those registers that spin_lock() marks &quot;clobbered&quot;.&n; */
DECL|macro|IA64_SPINLOCK_CLOBBERS
mdefine_line|#define IA64_SPINLOCK_CLOBBERS &quot;ar.ccv&quot;, &quot;ar.pfs&quot;, &quot;p14&quot;, &quot;p15&quot;, &quot;r27&quot;, &quot;r28&quot;, &quot;r29&quot;, &quot;r30&quot;, &quot;b6&quot;, &quot;memory&quot;
r_static
r_inline
r_void
DECL|function|_raw_spin_lock_flags
id|_raw_spin_lock_flags
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
r_register
r_volatile
r_int
r_int
op_star
id|ptr
id|asm
(paren
l_string|&quot;r31&quot;
)paren
op_assign
op_amp
id|lock-&gt;lock
suffix:semicolon
macro_line|#if __GNUC__ &lt; 3 || (__GNUC__ == 3 &amp;&amp; __GNUC_MINOR__ &lt; 3)
macro_line|# ifdef CONFIG_ITANIUM
multiline_comment|/* don&squot;t use brl on Itanium... */
id|asm
r_volatile
(paren
l_string|&quot;{&bslash;n&bslash;t&quot;
l_string|&quot;  mov ar.ccv = r0&bslash;n&bslash;t&quot;
l_string|&quot;  mov r28 = ip&bslash;n&bslash;t&quot;
l_string|&quot;  mov r30 = 1;;&bslash;n&bslash;t&quot;
l_string|&quot;}&bslash;n&bslash;t&quot;
l_string|&quot;cmpxchg4.acq r30 = [%1], r30, ar.ccv&bslash;n&bslash;t&quot;
l_string|&quot;movl r29 = ia64_spinlock_contention_pre3_4;;&bslash;n&bslash;t&quot;
l_string|&quot;cmp4.ne p14, p0 = r30, r0&bslash;n&bslash;t&quot;
l_string|&quot;mov b6 = r29;;&bslash;n&bslash;t&quot;
l_string|&quot;mov r27=%2&bslash;n&bslash;t&quot;
l_string|&quot;(p14) br.cond.spnt.many b6&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
)paren
suffix:colon
id|IA64_SPINLOCK_CLOBBERS
)paren
suffix:semicolon
macro_line|# else
id|asm
r_volatile
(paren
l_string|&quot;{&bslash;n&bslash;t&quot;
l_string|&quot;  mov ar.ccv = r0&bslash;n&bslash;t&quot;
l_string|&quot;  mov r28 = ip&bslash;n&bslash;t&quot;
l_string|&quot;  mov r30 = 1;;&bslash;n&bslash;t&quot;
l_string|&quot;}&bslash;n&bslash;t&quot;
l_string|&quot;cmpxchg4.acq r30 = [%1], r30, ar.ccv;;&bslash;n&bslash;t&quot;
l_string|&quot;cmp4.ne p14, p0 = r30, r0&bslash;n&bslash;t&quot;
l_string|&quot;mov r27=%2&bslash;n&bslash;t&quot;
l_string|&quot;(p14) brl.cond.spnt.many ia64_spinlock_contention_pre3_4;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
)paren
suffix:colon
id|IA64_SPINLOCK_CLOBBERS
)paren
suffix:semicolon
macro_line|# endif /* CONFIG_MCKINLEY */
macro_line|#else
macro_line|# ifdef CONFIG_ITANIUM
multiline_comment|/* don&squot;t use brl on Itanium... */
multiline_comment|/* mis-declare, so we get the entry-point, not it&squot;s function descriptor: */
id|asm
r_volatile
(paren
l_string|&quot;mov r30 = 1&bslash;n&bslash;t&quot;
l_string|&quot;mov r27=%2&bslash;n&bslash;t&quot;
l_string|&quot;mov ar.ccv = r0;;&bslash;n&bslash;t&quot;
l_string|&quot;cmpxchg4.acq r30 = [%0], r30, ar.ccv&bslash;n&bslash;t&quot;
l_string|&quot;movl r29 = ia64_spinlock_contention;;&bslash;n&bslash;t&quot;
l_string|&quot;cmp4.ne p14, p0 = r30, r0&bslash;n&bslash;t&quot;
l_string|&quot;mov b6 = r29;;&bslash;n&bslash;t&quot;
l_string|&quot;(p14) br.call.spnt.many b6 = b6&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
)paren
suffix:colon
id|IA64_SPINLOCK_CLOBBERS
)paren
suffix:semicolon
macro_line|# else
id|asm
r_volatile
(paren
l_string|&quot;mov r30 = 1&bslash;n&bslash;t&quot;
l_string|&quot;mov r27=%2&bslash;n&bslash;t&quot;
l_string|&quot;mov ar.ccv = r0;;&bslash;n&bslash;t&quot;
l_string|&quot;cmpxchg4.acq r30 = [%0], r30, ar.ccv;;&bslash;n&bslash;t&quot;
l_string|&quot;cmp4.ne p14, p0 = r30, r0&bslash;n&bslash;t&quot;
l_string|&quot;(p14) brl.call.spnt.many b6=ia64_spinlock_contention;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|ptr
)paren
comma
l_string|&quot;r&quot;
(paren
id|flags
)paren
suffix:colon
id|IA64_SPINLOCK_CLOBBERS
)paren
suffix:semicolon
macro_line|# endif /* CONFIG_MCKINLEY */
macro_line|#endif
)brace
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(lock) _raw_spin_lock_flags(lock, 0)
macro_line|#else /* !ASM_SUPPORTED */
DECL|macro|_raw_spin_lock_flags
mdefine_line|#define _raw_spin_lock_flags(lock, flags) _raw_spin_lock(lock)
DECL|macro|_raw_spin_lock
macro_line|# define _raw_spin_lock(x)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u32 *ia64_spinlock_ptr = (__u32 *) (x);&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_spinlock_val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_spinlock_val = ia64_cmpxchg4_acq(ia64_spinlock_ptr, 1, 0);&t;&t;&t;&bslash;&n;&t;if (unlikely(ia64_spinlock_val)) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;while (*ia64_spinlock_ptr)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;ia64_barrier();&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ia64_spinlock_val = ia64_cmpxchg4_acq(ia64_spinlock_ptr, 1, 0);&t;&bslash;&n;&t;&t;} while (ia64_spinlock_val);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* !ASM_SUPPORTED */
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|_raw_spin_unlock
mdefine_line|#define _raw_spin_unlock(x)&t;do { barrier(); ((spinlock_t *) x)-&gt;lock = 0; } while (0)
DECL|macro|_raw_spin_trylock
mdefine_line|#define _raw_spin_trylock(x)&t;(cmpxchg_acq(&amp;(x)-&gt;lock, 0, 1) == 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while ((x)-&gt;lock)
r_typedef
r_struct
(brace
DECL|member|read_counter
r_volatile
r_int
r_int
id|read_counter
suffix:colon
l_int|31
suffix:semicolon
DECL|member|write_lock
r_volatile
r_int
r_int
id|write_lock
suffix:colon
l_int|1
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
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)&t;&t;do { *(x) = RW_LOCK_UNLOCKED; } while(0)
DECL|macro|read_can_lock
mdefine_line|#define read_can_lock(rw)&t;(*(volatile int *)(rw) &gt;= 0)
DECL|macro|write_can_lock
mdefine_line|#define write_can_lock(rw)&t;(*(volatile int *)(rw) == 0)
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(rw)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rwlock_t *__read_lock_ptr = (rw);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (unlikely(ia64_fetchadd(1, (int *) __read_lock_ptr, acq) &lt; 0)) {&t;&t;&bslash;&n;&t;&t;ia64_fetchadd(-1, (int *) __read_lock_ptr, rel);&t;&t;&t;&bslash;&n;&t;&t;while (*(volatile int *)__read_lock_ptr &lt; 0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_relax();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(rw)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rwlock_t *__read_lock_ptr = (rw);&t;&t;&t;&bslash;&n;&t;ia64_fetchadd(-1, (int *) __read_lock_ptr, rel);&t;&bslash;&n;} while (0)
macro_line|#ifdef ASM_SUPPORTED
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(rw)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov ar.ccv = r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;dep r29 = -1, r0, 31, 1;;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ld4 r2 = [%0];;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmp4.eq p0,p7 = r0,r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;(p7) br.cond.spnt.few 1b &bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmpxchg4.acq r2 = [%0], r29, ar.ccv;;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmp4.eq p0,p7 = r0, r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;(p7) br.cond.spnt.few 1b;;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:: &quot;r&quot;(rw) : &quot;ar.ccv&quot;, &quot;p7&quot;, &quot;r2&quot;, &quot;r29&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;} while(0)
DECL|macro|_raw_write_trylock
mdefine_line|#define _raw_write_trylock(rw)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov ar.ccv = r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;dep r29 = -1, r0, 31, 1;;&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmpxchg4.acq %0 = [%1], r29, ar.ccv&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(result) : &quot;r&quot;(rw) : &quot;ar.ccv&quot;, &quot;r29&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;(result == 0);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#else /* !ASM_SUPPORTED */
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(l)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_val, ia64_set_val = ia64_dep_mi(-1, 0, 31, 1);&t;&t;&t;&bslash;&n;&t;__u32 *ia64_write_lock_ptr = (__u32 *) (l);&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;while (*ia64_write_lock_ptr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;ia64_barrier();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;ia64_val = ia64_cmpxchg4_acq(ia64_write_lock_ptr, ia64_set_val, 0);&t;&bslash;&n;&t;} while (ia64_val);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|_raw_write_trylock
mdefine_line|#define _raw_write_trylock(rw)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_val;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 ia64_set_val = ia64_dep_mi(-1, 0, 31,1);&t;&t;&t;&bslash;&n;&t;ia64_val = ia64_cmpxchg4_acq((__u32 *)(rw), ia64_set_val, 0);&t;&bslash;&n;&t;(ia64_val == 0);&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* !ASM_SUPPORTED */
DECL|macro|_raw_read_trylock
mdefine_line|#define _raw_read_trylock(lock) generic_raw_read_trylock(lock)
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(x)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;smp_mb__before_clear_bit();&t;/* need barrier before releasing lock... */&t;&bslash;&n;&t;clear_bit(31, (x));&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /*  _ASM_IA64_SPINLOCK_H */
eof
