macro_line|#ifndef _ASM_IA64_SPINLOCK_H
DECL|macro|_ASM_IA64_SPINLOCK_H
mdefine_line|#define _ASM_IA64_SPINLOCK_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * This file is used for SMP configurations only.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
DECL|macro|NEW_LOCK
macro_line|#undef NEW_LOCK
macro_line|#ifdef NEW_LOCK
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
multiline_comment|/*&n; * Streamlined test_and_set_bit(0, (x)).  We use test-and-test-and-set&n; * rather than a simple xchg to avoid writing the cache-line when&n; * there is contention.&n; */
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register char *addr __asm__ (&quot;r31&quot;) = (char *) &amp;(x)-&gt;lock;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov r30=1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov ar.ccv=r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_SEMFIX&quot;cmpxchg4.acq r30=[%0],r30,ar.ccv&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmp.ne p15,p0=r30,r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;(p15) br.call.spnt.few b7=ia64_spinlock_contention&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;/* force a new bundle */&t;&t;&bslash;&n;&t;&t;:: &quot;r&quot;(addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;ar.ccv&quot;, &quot;ar.pfs&quot;, &quot;b7&quot;, &quot;p15&quot;, &quot;r28&quot;, &quot;r29&quot;, &quot;r30&quot;, &quot;memory&quot;);&t;&bslash;&n;}
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(x)&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;register long result;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov ar.ccv=r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_SEMFIX&quot;cmpxchg4.acq %0=[%2],%1,ar.ccv&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=r&quot;(result) : &quot;r&quot;(1), &quot;r&quot;(&amp;(x)-&gt;lock) : &quot;ar.ccv&quot;, &quot;memory&quot;);&t;&t;&bslash;&n;&t;(result == 0);&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(x)&t;&t;do {((spinlock_t *) x)-&gt;lock = 0;} while (0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do {} while ((x)-&gt;lock)
macro_line|#else /* !NEW_LOCK */
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
multiline_comment|/*&n; * Streamlined test_and_set_bit(0, (x)).  We use test-and-test-and-set&n; * rather than a simple xchg to avoid writing the cache-line when&n; * there is contention.&n; */
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x) __asm__ __volatile__ (&t;&t;&t;&bslash;&n;&t;&quot;mov ar.ccv = r0&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mov r29 = 1&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ld4 r2 = [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmp4.eq p0,p7 = r0,r2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;(p7) br.cond.spnt.few 1b &bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;IA64_SEMFIX&quot;cmpxchg4.acq r2 = [%0], r29, ar.ccv&bslash;n&quot;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;cmp4.eq p0,p7 = r0, r2&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;(p7) br.cond.spnt.few 1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;:: &quot;r&quot;(&amp;(x)-&gt;lock) : &quot;r2&quot;, &quot;r29&quot;, &quot;memory&quot;)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(x)&t;&t;do {((spinlock_t *) x)-&gt;lock = 0; barrier(); } while (0)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(x)&t;&t;(cmpxchg_acq(&amp;(x)-&gt;lock, 0, 1) == 0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { barrier(); } while ((x)-&gt;lock)
macro_line|#endif /* !NEW_LOCK */
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
DECL|macro|read_lock
mdefine_line|#define read_lock(rw)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int tmp = 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;1:&bslash;t&quot;IA64_SEMFIX&quot;fetchadd4.acq %0 = [%1], 1&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;tbit.nz p6,p0 = %0, 31&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;(p6) br.cond.sptk.few 2f&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;.section .text.lock,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;2:&bslash;t&quot;IA64_SEMFIX&quot;fetchadd4.rel %0 = [%1], -1&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;3:&bslash;tld4.acq %0 = [%1]&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;tbit.nz p6,p0 = %0, 31&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;(p6) br.cond.sptk.few 3b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;br.cond.sptk.few 1b&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      &quot;.previous&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      : &quot;=&amp;r&quot; (tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      : &quot;r&quot; (rw): &quot;memory&quot;);&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int tmp = 0;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (IA64_SEMFIX&quot;fetchadd4.rel %0 = [%1], -1&bslash;n&quot;&t;&bslash;&n;&t;&t;&t;      : &quot;=r&quot; (tmp)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      : &quot;r&quot; (rw)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;      : &quot;memory&quot;);&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|write_lock
mdefine_line|#define write_lock(rw)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; &t;__asm__ __volatile__ (&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;mov ar.ccv = r0&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;movl r29 = 0x80000000&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;ld4 r2 = [%0]&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmp4.eq p0,p7 = r0,r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;(p7) br.cond.spnt.few 1b &bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;IA64_SEMFIX&quot;cmpxchg4.acq r2 = [%0], r29, ar.ccv&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;cmp4.eq p0,p7 = r0, r2&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;(p7) br.cond.spnt.few 1b&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;;;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;:: &quot;r&quot;(rw) : &quot;r2&quot;, &quot;r29&quot;, &quot;memory&quot;);&t;&t;&t;&t;&bslash;&n;} while(0)
multiline_comment|/*&n; * clear_bit() has &quot;acq&quot; semantics; we&squot;re really need &quot;rel&quot; semantics,&n; * but for simplicity, we simply do a fence for now...&n; */
DECL|macro|write_unlock
mdefine_line|#define write_unlock(x)&t;&t;&t;&t;({clear_bit(31, (x)); mb();})
macro_line|#endif /*  _ASM_IA64_SPINLOCK_H */
eof
