macro_line|#ifndef __LINUX_SPINLOCK_H
DECL|macro|__LINUX_SPINLOCK_H
mdefine_line|#define __LINUX_SPINLOCK_H
multiline_comment|/*&n; * include/linux/spinlock.h - generic locking declarations&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stringify.h&gt;
macro_line|#include &lt;asm/processor.h&gt;&t;/* for cpu relax */
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * Must define these before including other files, inline functions need them&n; */
DECL|macro|LOCK_SECTION_NAME
mdefine_line|#define LOCK_SECTION_NAME                       &bslash;&n;        &quot;.text.lock.&quot; __stringify(KBUILD_BASENAME)
DECL|macro|LOCK_SECTION_START
mdefine_line|#define LOCK_SECTION_START(extra)               &bslash;&n;        &quot;.subsection 1&bslash;n&bslash;t&quot;                     &bslash;&n;        extra                                   &bslash;&n;        &quot;.ifndef &quot; LOCK_SECTION_NAME &quot;&bslash;n&bslash;t&quot;     &bslash;&n;        LOCK_SECTION_NAME &quot;:&bslash;n&bslash;t&quot;               &bslash;&n;        &quot;.endif&bslash;n&quot;
DECL|macro|LOCK_SECTION_END
mdefine_line|#define LOCK_SECTION_END                        &bslash;&n;        &quot;.previous&bslash;n&bslash;t&quot;
DECL|macro|__lockfunc
mdefine_line|#define __lockfunc fastcall __attribute__((section(&quot;.spinlock.text&quot;)))
multiline_comment|/*&n; * If CONFIG_SMP is set, pull in the _raw_* definitions&n; */
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/spinlock.h&gt;
r_int
id|__lockfunc
id|_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_int
id|__lockfunc
id|_read_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_int
id|__lockfunc
id|_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_void
id|__lockfunc
id|_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_read_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_write_lock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_void
id|__lockfunc
id|_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_int
r_int
id|__lockfunc
id|_spin_lock_irqsave
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_int
r_int
id|__lockfunc
id|_read_lock_irqsave
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_int
r_int
id|__lockfunc
id|_write_lock_irqsave
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_void
id|__lockfunc
id|_spin_lock_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_void
id|__lockfunc
id|_spin_lock_bh
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_read_lock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_read_lock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_write_lock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_write_lock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__acquires
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_void
id|__lockfunc
id|_spin_unlock_irqrestore
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
id|__releases
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_void
id|__lockfunc
id|_spin_unlock_irq
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|spinlock_t
r_void
id|__lockfunc
id|_spin_unlock_bh
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|spinlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_read_unlock_irqrestore
c_func
(paren
id|rwlock_t
op_star
id|lock
comma
r_int
r_int
id|flags
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_read_unlock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_read_unlock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_write_unlock_irqrestore
c_func
(paren
id|rwlock_t
op_star
id|lock
comma
r_int
r_int
id|flags
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_write_unlock_irq
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
DECL|variable|rwlock_t
r_void
id|__lockfunc
id|_write_unlock_bh
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
id|__releases
c_func
(paren
id|rwlock_t
)paren
suffix:semicolon
r_int
id|__lockfunc
id|_spin_trylock_bh
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_int
id|__lockfunc
id|generic_raw_read_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_int
id|in_lock_functions
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#else
DECL|macro|in_lock_functions
mdefine_line|#define in_lock_functions(ADDR) 0
macro_line|#if !defined(CONFIG_PREEMPT) &amp;&amp; !defined(CONFIG_DEBUG_SPINLOCK)
DECL|macro|_atomic_dec_and_lock
macro_line|# define _atomic_dec_and_lock(atomic,lock) atomic_dec_and_test(atomic)
DECL|macro|ATOMIC_DEC_AND_LOCK
macro_line|# define ATOMIC_DEC_AND_LOCK
macro_line|#endif
macro_line|#ifdef CONFIG_DEBUG_SPINLOCK
DECL|macro|SPINLOCK_MAGIC
mdefine_line|#define SPINLOCK_MAGIC&t;0x1D244B3C
r_typedef
r_struct
(brace
DECL|member|magic
r_int
r_int
id|magic
suffix:semicolon
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|babble
r_volatile
r_int
r_int
id|babble
suffix:semicolon
DECL|member|module
r_const
r_char
op_star
id|module
suffix:semicolon
DECL|member|owner
r_char
op_star
id|owner
suffix:semicolon
DECL|member|oline
r_int
id|oline
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { SPINLOCK_MAGIC, 0, 10, __FILE__ , NULL, 0}
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x) &bslash;&n;&t;do { &bslash;&n;&t;&t;(x)-&gt;magic = SPINLOCK_MAGIC; &bslash;&n;&t;&t;(x)-&gt;lock = 0; &bslash;&n;&t;&t;(x)-&gt;babble = 5; &bslash;&n;&t;&t;(x)-&gt;module = __FILE__; &bslash;&n;&t;&t;(x)-&gt;owner = NULL; &bslash;&n;&t;&t;(x)-&gt;oline = 0; &bslash;&n;&t;} while (0)
DECL|macro|CHECK_LOCK
mdefine_line|#define CHECK_LOCK(x) &bslash;&n;&t;do { &bslash;&n;&t; &t;if ((x)-&gt;magic != SPINLOCK_MAGIC) { &bslash;&n;&t;&t;&t;printk(KERN_ERR &quot;%s:%d: spin_is_locked on uninitialized spinlock %p.&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;__FILE__, __LINE__, (x)); &bslash;&n;&t;&t;} &bslash;&n;&t;} while(0)
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(x)&t;&t;&bslash;&n;&t;do { &bslash;&n;&t; &t;CHECK_LOCK(x); &bslash;&n;&t;&t;if ((x)-&gt;lock&amp;&amp;(x)-&gt;babble) { &bslash;&n;&t;&t;&t;(x)-&gt;babble--; &bslash;&n;&t;&t;&t;printk(&quot;%s:%d: spin_lock(%s:%p) already locked by %s/%d&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;__FILE__,__LINE__, (x)-&gt;module, &bslash;&n;&t;&t;&t;&t;&t;(x), (x)-&gt;owner, (x)-&gt;oline); &bslash;&n;&t;&t;} &bslash;&n;&t;&t;(x)-&gt;lock = 1; &bslash;&n;&t;&t;(x)-&gt;owner = __FILE__; &bslash;&n;&t;&t;(x)-&gt;oline = __LINE__; &bslash;&n;&t;} while (0)
multiline_comment|/* without debugging, spin_is_locked on UP always says&n; * FALSE. --&gt; printk if already locked. */
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x) &bslash;&n;&t;({ &bslash;&n;&t; &t;CHECK_LOCK(x); &bslash;&n;&t;&t;if ((x)-&gt;lock&amp;&amp;(x)-&gt;babble) { &bslash;&n;&t;&t;&t;(x)-&gt;babble--; &bslash;&n;&t;&t;&t;printk(&quot;%s:%d: spin_is_locked(%s:%p) already locked by %s/%d&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;__FILE__,__LINE__, (x)-&gt;module, &bslash;&n;&t;&t;&t;&t;&t;(x), (x)-&gt;owner, (x)-&gt;oline); &bslash;&n;&t;&t;} &bslash;&n;&t;&t;0; &bslash;&n;&t;})
multiline_comment|/* without debugging, spin_trylock on UP always says&n; * TRUE. --&gt; printk if already locked. */
DECL|macro|_raw_spin_trylock
mdefine_line|#define _raw_spin_trylock(x) &bslash;&n;&t;({ &bslash;&n;&t; &t;CHECK_LOCK(x); &bslash;&n;&t;&t;if ((x)-&gt;lock&amp;&amp;(x)-&gt;babble) { &bslash;&n;&t;&t;&t;(x)-&gt;babble--; &bslash;&n;&t;&t;&t;printk(&quot;%s:%d: spin_trylock(%s:%p) already locked by %s/%d&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;__FILE__,__LINE__, (x)-&gt;module, &bslash;&n;&t;&t;&t;&t;&t;(x), (x)-&gt;owner, (x)-&gt;oline); &bslash;&n;&t;&t;} &bslash;&n;&t;&t;(x)-&gt;lock = 1; &bslash;&n;&t;&t;(x)-&gt;owner = __FILE__; &bslash;&n;&t;&t;(x)-&gt;oline = __LINE__; &bslash;&n;&t;&t;1; &bslash;&n;&t;})
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;&bslash;&n;&t;do { &bslash;&n;&t; &t;CHECK_LOCK(x); &bslash;&n;&t;&t;if ((x)-&gt;lock&amp;&amp;(x)-&gt;babble) { &bslash;&n;&t;&t;&t;(x)-&gt;babble--; &bslash;&n;&t;&t;&t;printk(&quot;%s:%d: spin_unlock_wait(%s:%p) owned by %s/%d&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;__FILE__,__LINE__, (x)-&gt;module, (x), &bslash;&n;&t;&t;&t;&t;&t;(x)-&gt;owner, (x)-&gt;oline); &bslash;&n;&t;&t;}&bslash;&n;&t;} while (0)
DECL|macro|_raw_spin_unlock
mdefine_line|#define _raw_spin_unlock(x) &bslash;&n;&t;do { &bslash;&n;&t; &t;CHECK_LOCK(x); &bslash;&n;&t;&t;if (!(x)-&gt;lock&amp;&amp;(x)-&gt;babble) { &bslash;&n;&t;&t;&t;(x)-&gt;babble--; &bslash;&n;&t;&t;&t;printk(&quot;%s:%d: spin_unlock(%s:%p) not locked&bslash;n&quot;, &bslash;&n;&t;&t;&t;&t;&t;__FILE__,__LINE__, (x)-&gt;module, (x));&bslash;&n;&t;&t;} &bslash;&n;&t;&t;(x)-&gt;lock = 0; &bslash;&n;&t;} while (0)
macro_line|#else
multiline_comment|/*&n; * gcc versions before ~2.95 have a nasty bug with empty initializers.&n; */
macro_line|#if (__GNUC__ &gt; 2)
DECL|typedef|spinlock_t
r_typedef
r_struct
(brace
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { }
macro_line|#else
DECL|member|gcc_is_buggy
DECL|typedef|spinlock_t
r_typedef
r_struct
(brace
r_int
id|gcc_is_buggy
suffix:semicolon
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 }
macro_line|#endif
multiline_comment|/*&n; * If CONFIG_SMP is unset, declare the _raw_* definitions as nops&n; */
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(lock)&t;do { (void)(lock); } while(0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)&t;((void)(lock), 0)
DECL|macro|_raw_spin_trylock
mdefine_line|#define _raw_spin_trylock(lock)&t;(((void)(lock), 1))
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;(void)(lock)
DECL|macro|_raw_spin_unlock
mdefine_line|#define _raw_spin_unlock(lock) do { (void)(lock); } while(0)
macro_line|#endif /* CONFIG_DEBUG_SPINLOCK */
multiline_comment|/* RW spinlocks: No debug version */
macro_line|#if (__GNUC__ &gt; 2)
DECL|typedef|rwlock_t
r_typedef
r_struct
(brace
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { }
macro_line|#else
DECL|member|gcc_is_buggy
DECL|typedef|rwlock_t
r_typedef
r_struct
(brace
r_int
id|gcc_is_buggy
suffix:semicolon
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0 }
macro_line|#endif
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_read_trylock
mdefine_line|#define _raw_read_trylock(lock) ({ (void)(lock); (1); })
DECL|macro|_raw_write_trylock
mdefine_line|#define _raw_write_trylock(lock) ({ (void)(lock); (1); })
DECL|macro|_spin_trylock
mdefine_line|#define _spin_trylock(lock)&t;({preempt_disable(); _raw_spin_trylock(lock) ? &bslash;&n;&t;&t;&t;&t;1 : ({preempt_enable(); 0;});})
DECL|macro|_read_trylock
mdefine_line|#define _read_trylock(lock)&t;({preempt_disable();_raw_read_trylock(lock) ? &bslash;&n;&t;&t;&t;&t;1 : ({preempt_enable(); 0;});})
DECL|macro|_write_trylock
mdefine_line|#define _write_trylock(lock)&t;({preempt_disable(); _raw_write_trylock(lock) ? &bslash;&n;&t;&t;&t;&t;1 : ({preempt_enable(); 0;});})
DECL|macro|_spin_trylock_bh
mdefine_line|#define _spin_trylock_bh(lock)&t;({preempt_disable(); local_bh_disable(); &bslash;&n;&t;&t;&t;&t;_raw_spin_trylock(lock) ? &bslash;&n;&t;&t;&t;&t;1 : ({preempt_enable(); local_bh_enable(); 0;});})
DECL|macro|_spin_lock
mdefine_line|#define _spin_lock(lock)&t;&bslash;&n;do { &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_spin_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while(0)
DECL|macro|_write_lock
mdefine_line|#define _write_lock(lock) &bslash;&n;do { &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_write_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while(0)
DECL|macro|_read_lock
mdefine_line|#define _read_lock(lock)&t;&bslash;&n;do { &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_read_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while(0)
DECL|macro|_spin_unlock
mdefine_line|#define _spin_unlock(lock) &bslash;&n;do { &bslash;&n;&t;_raw_spin_unlock(lock); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_write_unlock
mdefine_line|#define _write_unlock(lock) &bslash;&n;do { &bslash;&n;&t;_raw_write_unlock(lock); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while(0)
DECL|macro|_read_unlock
mdefine_line|#define _read_unlock(lock) &bslash;&n;do { &bslash;&n;&t;_raw_read_unlock(lock); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while(0)
DECL|macro|_spin_lock_irqsave
mdefine_line|#define _spin_lock_irqsave(lock, flags) &bslash;&n;do {&t;&bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_spin_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_spin_lock_irq
mdefine_line|#define _spin_lock_irq(lock) &bslash;&n;do { &bslash;&n;&t;local_irq_disable(); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_spin_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_spin_lock_bh
mdefine_line|#define _spin_lock_bh(lock) &bslash;&n;do { &bslash;&n;&t;local_bh_disable(); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_spin_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_read_lock_irqsave
mdefine_line|#define _read_lock_irqsave(lock, flags) &bslash;&n;do {&t;&bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_read_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_read_lock_irq
mdefine_line|#define _read_lock_irq(lock) &bslash;&n;do { &bslash;&n;&t;local_irq_disable(); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_read_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_read_lock_bh
mdefine_line|#define _read_lock_bh(lock) &bslash;&n;do { &bslash;&n;&t;local_bh_disable(); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_read_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_write_lock_irqsave
mdefine_line|#define _write_lock_irqsave(lock, flags) &bslash;&n;do {&t;&bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_write_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_write_lock_irq
mdefine_line|#define _write_lock_irq(lock) &bslash;&n;do { &bslash;&n;&t;local_irq_disable(); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_write_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_write_lock_bh
mdefine_line|#define _write_lock_bh(lock) &bslash;&n;do { &bslash;&n;&t;local_bh_disable(); &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_write_lock(lock); &bslash;&n;&t;__acquire(lock); &bslash;&n;} while (0)
DECL|macro|_spin_unlock_irqrestore
mdefine_line|#define _spin_unlock_irqrestore(lock, flags) &bslash;&n;do { &bslash;&n;&t;_raw_spin_unlock(lock); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_spin_unlock_irq
mdefine_line|#define _spin_unlock_irq(lock) &bslash;&n;do { &bslash;&n;&t;_raw_spin_unlock(lock); &bslash;&n;&t;local_irq_enable(); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_spin_unlock_bh
mdefine_line|#define _spin_unlock_bh(lock) &bslash;&n;do { &bslash;&n;&t;_raw_spin_unlock(lock); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;local_bh_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_write_unlock_bh
mdefine_line|#define _write_unlock_bh(lock) &bslash;&n;do { &bslash;&n;&t;_raw_write_unlock(lock); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;local_bh_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_read_unlock_irqrestore
mdefine_line|#define _read_unlock_irqrestore(lock, flags) &bslash;&n;do { &bslash;&n;&t;_raw_read_unlock(lock); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_write_unlock_irqrestore
mdefine_line|#define _write_unlock_irqrestore(lock, flags) &bslash;&n;do { &bslash;&n;&t;_raw_write_unlock(lock); &bslash;&n;&t;local_irq_restore(flags); &bslash;&n;&t;preempt_enable(); &bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_read_unlock_irq
mdefine_line|#define _read_unlock_irq(lock)&t;&bslash;&n;do { &bslash;&n;&t;_raw_read_unlock(lock);&t;&bslash;&n;&t;local_irq_enable();&t;&bslash;&n;&t;preempt_enable();&t;&bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_read_unlock_bh
mdefine_line|#define _read_unlock_bh(lock)&t;&bslash;&n;do { &bslash;&n;&t;_raw_read_unlock(lock);&t;&bslash;&n;&t;local_bh_enable();&t;&bslash;&n;&t;preempt_enable();&t;&bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
DECL|macro|_write_unlock_irq
mdefine_line|#define _write_unlock_irq(lock)&t;&bslash;&n;do { &bslash;&n;&t;_raw_write_unlock(lock);&t;&bslash;&n;&t;local_irq_enable();&t;&bslash;&n;&t;preempt_enable();&t;&bslash;&n;&t;__release(lock); &bslash;&n;} while (0)
macro_line|#endif /* !SMP */
multiline_comment|/*&n; * Define the various spin_lock and rw_lock methods.  Note we define these&n; * regardless of whether CONFIG_SMP or CONFIG_PREEMPT are set. The various&n; * methods are defined as nops in the case they are not required.&n; */
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;__cond_lock(_spin_trylock(lock))
DECL|macro|read_trylock
mdefine_line|#define read_trylock(lock)&t;__cond_lock(_read_trylock(lock))
DECL|macro|write_trylock
mdefine_line|#define write_trylock(lock)&t;__cond_lock(_write_trylock(lock))
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;_spin_lock(lock)
DECL|macro|write_lock
mdefine_line|#define write_lock(lock)&t;_write_lock(lock)
DECL|macro|read_lock
mdefine_line|#define read_lock(lock)&t;&t;_read_lock(lock)
macro_line|#ifdef CONFIG_SMP
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags)&t;flags = _spin_lock_irqsave(lock)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(lock, flags)&t;flags = _read_lock_irqsave(lock)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;flags = _write_lock_irqsave(lock)
macro_line|#else
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags)&t;_spin_lock_irqsave(lock, flags)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(lock, flags)&t;_read_lock_irqsave(lock, flags)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;_write_lock_irqsave(lock, flags)
macro_line|#endif
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock)&t;&t;_spin_lock_irq(lock)
DECL|macro|spin_lock_bh
mdefine_line|#define spin_lock_bh(lock)&t;&t;_spin_lock_bh(lock)
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(lock)&t;&t;_read_lock_irq(lock)
DECL|macro|read_lock_bh
mdefine_line|#define read_lock_bh(lock)&t;&t;_read_lock_bh(lock)
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(lock)&t;&t;_write_lock_irq(lock)
DECL|macro|write_lock_bh
mdefine_line|#define write_lock_bh(lock)&t;&t;_write_lock_bh(lock)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;_spin_unlock(lock)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(lock)&t;_write_unlock(lock)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock)&t;_read_unlock(lock)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags)&t;_spin_unlock_irqrestore(lock, flags)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock)&t;&t;_spin_unlock_irq(lock)
DECL|macro|spin_unlock_bh
mdefine_line|#define spin_unlock_bh(lock)&t;&t;_spin_unlock_bh(lock)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags)&t;_read_unlock_irqrestore(lock, flags)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock)&t;&t;&t;_read_unlock_irq(lock)
DECL|macro|read_unlock_bh
mdefine_line|#define read_unlock_bh(lock)&t;&t;&t;_read_unlock_bh(lock)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags)&t;_write_unlock_irqrestore(lock, flags)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock)&t;&t;&t;_write_unlock_irq(lock)
DECL|macro|write_unlock_bh
mdefine_line|#define write_unlock_bh(lock)&t;&t;&t;_write_unlock_bh(lock)
DECL|macro|spin_trylock_bh
mdefine_line|#define spin_trylock_bh(lock)&t;&t;&t;__cond_lock(_spin_trylock_bh(lock))
DECL|macro|spin_trylock_irq
mdefine_line|#define spin_trylock_irq(lock) &bslash;&n;({ &bslash;&n;&t;local_irq_disable(); &bslash;&n;&t;_spin_trylock(lock) ? &bslash;&n;&t;1 : ({local_irq_enable(); 0; }); &bslash;&n;})
DECL|macro|spin_trylock_irqsave
mdefine_line|#define spin_trylock_irqsave(lock, flags) &bslash;&n;({ &bslash;&n;&t;local_irq_save(flags); &bslash;&n;&t;_spin_trylock(lock) ? &bslash;&n;&t;1 : ({local_irq_restore(flags); 0;}); &bslash;&n;})
macro_line|#ifdef CONFIG_LOCKMETER
r_extern
r_void
id|_metered_spin_lock
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_metered_spin_unlock
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_int
id|_metered_spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_metered_read_lock
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_metered_read_unlock
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_metered_write_lock
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_metered_write_unlock
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_int
id|_metered_read_trylock
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_int
id|_metered_write_trylock
c_func
(paren
id|rwlock_t
op_star
id|lock
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* &quot;lock on reference count zero&quot; */
macro_line|#ifndef ATOMIC_DEC_AND_LOCK
macro_line|#include &lt;asm/atomic.h&gt;
r_extern
r_int
id|_atomic_dec_and_lock
c_func
(paren
id|atomic_t
op_star
id|atomic
comma
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|atomic_dec_and_lock
mdefine_line|#define atomic_dec_and_lock(atomic,lock) __cond_lock(_atomic_dec_and_lock(atomic,lock))
multiline_comment|/*&n; *  bit-based spin_lock()&n; *&n; * Don&squot;t use this unless you really need to: spin_lock() and spin_unlock()&n; * are significantly faster.&n; */
DECL|function|bit_spin_lock
r_static
r_inline
r_void
id|bit_spin_lock
c_func
(paren
r_int
id|bitnum
comma
r_int
r_int
op_star
id|addr
)paren
(brace
multiline_comment|/*&n;&t; * Assuming the lock is uncontended, this never enters&n;&t; * the body of the outer loop. If it is contended, then&n;&t; * within the inner loop a non-atomic test is used to&n;&t; * busywait with less bus contention for a good time to&n;&t; * attempt to acquire the lock bit.&n;&t; */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
r_while
c_loop
(paren
id|test_and_set_bit
c_func
(paren
id|bitnum
comma
id|addr
)paren
)paren
(brace
r_while
c_loop
(paren
id|test_bit
c_func
(paren
id|bitnum
comma
id|addr
)paren
)paren
(brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|cpu_relax
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|__acquire
c_func
(paren
id|bitlock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return true if it was acquired&n; */
DECL|function|bit_spin_trylock
r_static
r_inline
r_int
id|bit_spin_trylock
c_func
(paren
r_int
id|bitnum
comma
r_int
r_int
op_star
id|addr
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|bitnum
comma
id|addr
)paren
)paren
(brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|__acquire
c_func
(paren
id|bitlock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *  bit-based spin_unlock()&n; */
DECL|function|bit_spin_unlock
r_static
r_inline
r_void
id|bit_spin_unlock
c_func
(paren
r_int
id|bitnum
comma
r_int
r_int
op_star
id|addr
)paren
(brace
macro_line|#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
id|BUG_ON
c_func
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|bitnum
comma
id|addr
)paren
)paren
suffix:semicolon
id|smp_mb__before_clear_bit
c_func
(paren
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|bitnum
comma
id|addr
)paren
suffix:semicolon
macro_line|#endif
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
id|__release
c_func
(paren
id|bitlock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return true if the lock is held.&n; */
DECL|function|bit_spin_is_locked
r_static
r_inline
r_int
id|bit_spin_is_locked
c_func
(paren
r_int
id|bitnum
comma
r_int
r_int
op_star
id|addr
)paren
(brace
macro_line|#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
r_return
id|test_bit
c_func
(paren
id|bitnum
comma
id|addr
)paren
suffix:semicolon
macro_line|#elif defined CONFIG_PREEMPT
r_return
id|preempt_count
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|1
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|DEFINE_SPINLOCK
mdefine_line|#define DEFINE_SPINLOCK(x) spinlock_t x = SPIN_LOCK_UNLOCKED
DECL|macro|DEFINE_RWLOCK
mdefine_line|#define DEFINE_RWLOCK(x) rwlock_t x = RW_LOCK_UNLOCKED
multiline_comment|/**&n; * spin_can_lock - would spin_trylock() succeed?&n; * @lock: the spinlock in question.&n; */
DECL|macro|spin_can_lock
mdefine_line|#define spin_can_lock(lock)&t;&t;(!spin_is_locked(lock))
macro_line|#endif /* __LINUX_SPINLOCK_H */
eof
