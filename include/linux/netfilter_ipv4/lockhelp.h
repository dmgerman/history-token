macro_line|#ifndef _LOCKHELP_H
DECL|macro|_LOCKHELP_H
mdefine_line|#define _LOCKHELP_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
multiline_comment|/* Header to do help in lock debugging. */
macro_line|#ifdef CONFIG_NETFILTER_DEBUG
DECL|struct|spinlock_debug
r_struct
id|spinlock_debug
(brace
DECL|member|l
id|spinlock_t
id|l
suffix:semicolon
DECL|member|locked_by
id|atomic_t
id|locked_by
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rwlock_debug
r_struct
id|rwlock_debug
(brace
DECL|member|l
id|rwlock_t
id|l
suffix:semicolon
DECL|member|read_locked_map
r_int
id|read_locked_map
suffix:semicolon
DECL|member|write_locked_map
r_int
id|write_locked_map
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DECLARE_LOCK
mdefine_line|#define DECLARE_LOCK(l) &t;&t;&t;&t;&t;&t;&bslash;&n;struct spinlock_debug l = { SPIN_LOCK_UNLOCKED, ATOMIC_INIT(-1) }
DECL|macro|DECLARE_LOCK_EXTERN
mdefine_line|#define DECLARE_LOCK_EXTERN(l) &t;&t;&t;&bslash;&n;extern struct spinlock_debug l
DECL|macro|DECLARE_RWLOCK
mdefine_line|#define DECLARE_RWLOCK(l)&t;&t;&t;&t;&bslash;&n;struct rwlock_debug l = { RW_LOCK_UNLOCKED, 0, 0 }
DECL|macro|DECLARE_RWLOCK_EXTERN
mdefine_line|#define DECLARE_RWLOCK_EXTERN(l)&t;&t;&bslash;&n;extern struct rwlock_debug l
DECL|macro|MUST_BE_LOCKED
mdefine_line|#define MUST_BE_LOCKED(l)&t;&t;&t;&t;&t;&t;&bslash;&n;do { if (atomic_read(&amp;(l)-&gt;locked_by) != smp_processor_id())&t;&t;&bslash;&n;&t;printk(&quot;ASSERT %s:%u %s unlocked&bslash;n&quot;, __FILE__, __LINE__, #l);&t;&bslash;&n;} while(0)
DECL|macro|MUST_BE_UNLOCKED
mdefine_line|#define MUST_BE_UNLOCKED(l)&t;&t;&t;&t;&t;&t;&bslash;&n;do { if (atomic_read(&amp;(l)-&gt;locked_by) == smp_processor_id())&t;&t;&bslash;&n;&t;printk(&quot;ASSERT %s:%u %s locked&bslash;n&quot;, __FILE__, __LINE__, #l);&t;&bslash;&n;} while(0)
multiline_comment|/* Write locked OK as well. */
"&bslash;"
DECL|macro|MUST_BE_READ_LOCKED
mdefine_line|#define MUST_BE_READ_LOCKED(l)&t;&t;&t;&t;&t;&t;    &bslash;&n;do { if (!((l)-&gt;read_locked_map &amp; (1 &lt;&lt; smp_processor_id()))&t;&t;    &bslash;&n;&t; &amp;&amp; !((l)-&gt;write_locked_map &amp; (1 &lt;&lt; smp_processor_id())))&t;    &bslash;&n;&t;printk(&quot;ASSERT %s:%u %s not readlocked&bslash;n&quot;, __FILE__, __LINE__, #l); &bslash;&n;} while(0)
DECL|macro|MUST_BE_WRITE_LOCKED
mdefine_line|#define MUST_BE_WRITE_LOCKED(l)&t;&t;&t;&t;&t;&t;     &bslash;&n;do { if (!((l)-&gt;write_locked_map &amp; (1 &lt;&lt; smp_processor_id())))&t;&t;     &bslash;&n;&t;printk(&quot;ASSERT %s:%u %s not writelocked&bslash;n&quot;, __FILE__, __LINE__, #l); &bslash;&n;} while(0)
DECL|macro|MUST_BE_READ_WRITE_UNLOCKED
mdefine_line|#define MUST_BE_READ_WRITE_UNLOCKED(l)&t;&t;&t;&t;&t;  &bslash;&n;do { if ((l)-&gt;read_locked_map &amp; (1 &lt;&lt; smp_processor_id()))&t;&t;  &bslash;&n;&t;printk(&quot;ASSERT %s:%u %s readlocked&bslash;n&quot;, __FILE__, __LINE__, #l);&t;  &bslash;&n; else if ((l)-&gt;write_locked_map &amp; (1 &lt;&lt; smp_processor_id()))&t;&t;  &bslash;&n;&t; printk(&quot;ASSERT %s:%u %s writelocked&bslash;n&quot;, __FILE__, __LINE__, #l); &bslash;&n;} while(0)
DECL|macro|LOCK_BH
mdefine_line|#define LOCK_BH(lk)&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MUST_BE_UNLOCKED(lk);&t;&t;&t;&t;&t;&bslash;&n;&t;spin_lock_bh(&amp;(lk)-&gt;l);&t;&t;&t;&t;&t;&bslash;&n;&t;atomic_set(&amp;(lk)-&gt;locked_by, smp_processor_id());&t;&bslash;&n;} while(0)
DECL|macro|UNLOCK_BH
mdefine_line|#define UNLOCK_BH(lk)&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MUST_BE_LOCKED(lk);&t;&t;&t;&bslash;&n;&t;atomic_set(&amp;(lk)-&gt;locked_by, -1);&t;&bslash;&n;&t;spin_unlock_bh(&amp;(lk)-&gt;l);&t;&t;&bslash;&n;} while(0)
DECL|macro|READ_LOCK
mdefine_line|#define READ_LOCK(lk) &t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MUST_BE_READ_WRITE_UNLOCKED(lk);&t;&t;&t;&bslash;&n;&t;read_lock_bh(&amp;(lk)-&gt;l);&t;&t;&t;&t;&t;&bslash;&n;&t;set_bit(smp_processor_id(), &amp;(lk)-&gt;read_locked_map);&t;&bslash;&n;} while(0)
DECL|macro|WRITE_LOCK
mdefine_line|#define WRITE_LOCK(lk)&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;MUST_BE_READ_WRITE_UNLOCKED(lk);&t;&t;&t;&t;  &bslash;&n;&t;write_lock_bh(&amp;(lk)-&gt;l);&t;&t;&t;&t;&t;  &bslash;&n;&t;set_bit(smp_processor_id(), &amp;(lk)-&gt;write_locked_map);&t;&t;  &bslash;&n;} while(0)
DECL|macro|READ_UNLOCK
mdefine_line|#define READ_UNLOCK(lk)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!((lk)-&gt;read_locked_map &amp; (1 &lt;&lt; smp_processor_id())))&t;&bslash;&n;&t;&t;printk(&quot;ASSERT: %s:%u %s not readlocked&bslash;n&quot;, &t;&t;&bslash;&n;&t;&t;       __FILE__, __LINE__, #lk);&t;&t;&t;&bslash;&n;&t;clear_bit(smp_processor_id(), &amp;(lk)-&gt;read_locked_map);&t;&t;&bslash;&n;&t;read_unlock_bh(&amp;(lk)-&gt;l);&t;&t;&t;&t;&t;&bslash;&n;} while(0)
DECL|macro|WRITE_UNLOCK
mdefine_line|#define WRITE_UNLOCK(lk)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;MUST_BE_WRITE_LOCKED(lk);&t;&t;&t;&t;&bslash;&n;&t;clear_bit(smp_processor_id(), &amp;(lk)-&gt;write_locked_map);&t;&bslash;&n;&t;write_unlock_bh(&amp;(lk)-&gt;l);&t;&t;&t;&t;&bslash;&n;} while(0)
macro_line|#else
DECL|macro|DECLARE_LOCK
mdefine_line|#define DECLARE_LOCK(l) spinlock_t l = SPIN_LOCK_UNLOCKED
DECL|macro|DECLARE_LOCK_EXTERN
mdefine_line|#define DECLARE_LOCK_EXTERN(l) extern spinlock_t l
DECL|macro|DECLARE_RWLOCK
mdefine_line|#define DECLARE_RWLOCK(l) rwlock_t l = RW_LOCK_UNLOCKED
DECL|macro|DECLARE_RWLOCK_EXTERN
mdefine_line|#define DECLARE_RWLOCK_EXTERN(l) extern rwlock_t l
DECL|macro|MUST_BE_LOCKED
mdefine_line|#define MUST_BE_LOCKED(l)
DECL|macro|MUST_BE_UNLOCKED
mdefine_line|#define MUST_BE_UNLOCKED(l)
DECL|macro|MUST_BE_READ_LOCKED
mdefine_line|#define MUST_BE_READ_LOCKED(l)
DECL|macro|MUST_BE_WRITE_LOCKED
mdefine_line|#define MUST_BE_WRITE_LOCKED(l)
DECL|macro|MUST_BE_READ_WRITE_UNLOCKED
mdefine_line|#define MUST_BE_READ_WRITE_UNLOCKED(l)
DECL|macro|LOCK_BH
mdefine_line|#define LOCK_BH(l) spin_lock_bh(l)
DECL|macro|UNLOCK_BH
mdefine_line|#define UNLOCK_BH(l) spin_unlock_bh(l)
DECL|macro|READ_LOCK
mdefine_line|#define READ_LOCK(l) read_lock_bh(l)
DECL|macro|WRITE_LOCK
mdefine_line|#define WRITE_LOCK(l) write_lock_bh(l)
DECL|macro|READ_UNLOCK
mdefine_line|#define READ_UNLOCK(l) read_unlock_bh(l)
DECL|macro|WRITE_UNLOCK
mdefine_line|#define WRITE_UNLOCK(l) write_unlock_bh(l)
macro_line|#endif /*CONFIG_NETFILTER_DEBUG*/
macro_line|#endif /* _LOCKHELP_H */
eof
