macro_line|#ifndef _ASM_IA64_SPINLOCK_H
DECL|macro|_ASM_IA64_SPINLOCK_H
mdefine_line|#define _ASM_IA64_SPINLOCK_H
multiline_comment|/*&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * This file is used for SMP configurations only.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;&t;&t;(spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;&t;&t;((x)-&gt;lock = 0)
DECL|macro|DEBUG_SPIN_LOCK
mdefine_line|#define DEBUG_SPIN_LOCK&t;0
macro_line|#if DEBUG_SPIN_LOCK
macro_line|#include &lt;ia64intrin.h&gt;
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(x)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _timeout = 1000000000;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;volatile unsigned int _old = 0, _new = 1, *_ptr = &amp;((x)-&gt;lock);&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (_timeout-- == 0) {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;extern void dump_stack (void);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(&quot;kernel DEADLOCK at %s:%d?&bslash;n&quot;, __FILE__, __LINE__);&t;&bslash;&n;&t;&t;&t;dump_stack();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (__sync_val_compare_and_swap(_ptr, _old, _new) != _old);&t;&t;&bslash;&n;} while (0)
macro_line|#else
multiline_comment|/*&n; * Streamlined test_and_set_bit(0, (x)).  We use test-and-test-and-set&n; * rather than a simple xchg to avoid writing the cache-line when&n; * there is contention.&n; */
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(x) __asm__ __volatile__ (&t;&t;&bslash;&n;&t;&quot;mov ar.ccv = r0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov r29 = 1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld4.bias r2 = [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmp4.eq p0,p7 = r0,r2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;(p7) br.cond.spnt.few 1b &bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmpxchg4.acq r2 = [%0], r29, ar.ccv&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmp4.eq p0,p7 = r0, r2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;(p7) br.cond.spnt.few 1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:: &quot;r&quot;(&amp;(x)-&gt;lock) : &quot;ar.ccv&quot;, &quot;p7&quot;, &quot;r2&quot;, &quot;r29&quot;, &quot;memory&quot;)
macro_line|#endif /* !DEBUG_SPIN_LOCK */
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
id|read_counter
suffix:colon
l_int|31
suffix:semicolon
DECL|member|write_lock
r_volatile
r_int
id|write_lock
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(x)&t;&t;do { *(x) = RW_LOCK_UNLOCKED; } while(0)
DECL|macro|rwlock_is_locked
mdefine_line|#define rwlock_is_locked(x)&t;(*(volatile int *) (x) != 0)
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(rw)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rwlock_t *__read_lock_ptr = (rw);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;while (unlikely(ia64_fetchadd(1, (int *) __read_lock_ptr, &quot;acq&quot;) &lt; 0)) {&t;&bslash;&n;&t;&t;ia64_fetchadd(-1, (int *) __read_lock_ptr, &quot;rel&quot;);&t;&t;&t;&bslash;&n;&t;&t;while (*(volatile int *)__read_lock_ptr &lt; 0)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;barrier();&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(rw)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rwlock_t *__read_lock_ptr = (rw);&t;&t;&t;&bslash;&n;&t;ia64_fetchadd(-1, (int *) __read_lock_ptr, &quot;rel&quot;);&t;&bslash;&n;} while (0)
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(rw)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov ar.ccv = r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;dep r29 = -1, r0, 31, 1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ld4 r2 = [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmp4.eq p0,p7 = r0,r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;(p7) br.cond.spnt.few 1b &bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmpxchg4.acq r2 = [%0], r29, ar.ccv&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmp4.eq p0,p7 = r0, r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;(p7) br.cond.spnt.few 1b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:: &quot;r&quot;(rw) : &quot;ar.ccv&quot;, &quot;p7&quot;, &quot;r2&quot;, &quot;r29&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;} while(0)
DECL|macro|_raw_write_trylock
mdefine_line|#define _raw_write_trylock(rw)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov ar.ccv = r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;dep r29 = -1, r0, 31, 1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmpxchg4.acq %0 = [%1], r29, ar.ccv&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(result) : &quot;r&quot;(rw) : &quot;ar.ccv&quot;, &quot;r29&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;(result == 0);&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(x)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;smp_mb__before_clear_bit();&t;/* need barrier before releasing lock... */&t;&bslash;&n;&t;clear_bit(31, (x));&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /*  _ASM_IA64_SPINLOCK_H */
eof
