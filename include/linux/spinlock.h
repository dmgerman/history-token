macro_line|#ifndef __LINUX_SPINLOCK_H
DECL|macro|__LINUX_SPINLOCK_H
mdefine_line|#define __LINUX_SPINLOCK_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * These are the generic versions of the spinlocks and read-write&n; * locks..&n; */
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(lock, flags)&t;&t;do { local_irq_save(flags);       spin_lock(lock); } while (0)
DECL|macro|spin_lock_irq
mdefine_line|#define spin_lock_irq(lock)&t;&t;&t;do { local_irq_disable();         spin_lock(lock); } while (0)
DECL|macro|spin_lock_bh
mdefine_line|#define spin_lock_bh(lock)&t;&t;&t;do { local_bh_disable();          spin_lock(lock); } while (0)
DECL|macro|read_lock_irqsave
mdefine_line|#define read_lock_irqsave(lock, flags)&t;&t;do { local_irq_save(flags);       read_lock(lock); } while (0)
DECL|macro|read_lock_irq
mdefine_line|#define read_lock_irq(lock)&t;&t;&t;do { local_irq_disable();         read_lock(lock); } while (0)
DECL|macro|read_lock_bh
mdefine_line|#define read_lock_bh(lock)&t;&t;&t;do { local_bh_disable();          read_lock(lock); } while (0)
DECL|macro|write_lock_irqsave
mdefine_line|#define write_lock_irqsave(lock, flags)&t;&t;do { local_irq_save(flags);      write_lock(lock); } while (0)
DECL|macro|write_lock_irq
mdefine_line|#define write_lock_irq(lock)&t;&t;&t;do { local_irq_disable();        write_lock(lock); } while (0)
DECL|macro|write_lock_bh
mdefine_line|#define write_lock_bh(lock)&t;&t;&t;do { local_bh_disable();         write_lock(lock); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(lock, flags)&t;do { spin_unlock(lock);  local_irq_restore(flags); } while (0)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock)&t;&t;&t;do { spin_unlock(lock);  local_irq_enable();       } while (0)
DECL|macro|spin_unlock_bh
mdefine_line|#define spin_unlock_bh(lock)&t;&t;&t;do { spin_unlock(lock);  local_bh_enable();        } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags)&t;do { read_unlock(lock);  local_irq_restore(flags); } while (0)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock)&t;&t;&t;do { read_unlock(lock);  local_irq_enable();       } while (0)
DECL|macro|read_unlock_bh
mdefine_line|#define read_unlock_bh(lock)&t;&t;&t;do { read_unlock(lock);  local_bh_enable();        } while (0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags)&t;do { write_unlock(lock); local_irq_restore(flags); } while (0)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock)&t;&t;&t;do { write_unlock(lock); local_irq_enable();       } while (0)
DECL|macro|write_unlock_bh
mdefine_line|#define write_unlock_bh(lock)&t;&t;&t;do { write_unlock(lock); local_bh_enable();        } while (0)
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#elif !defined(spin_lock_init) /* !SMP and spin_lock_init not previously&n;                                  defined (e.g. by including asm/spinlock.h */
DECL|macro|DEBUG_SPINLOCKS
mdefine_line|#define DEBUG_SPINLOCKS&t;0&t;/* 0 == no debugging, 1 == maintain lock state, 2 == full debug */
macro_line|#if (DEBUG_SPINLOCKS &lt; 1)
DECL|macro|atomic_dec_and_lock
mdefine_line|#define atomic_dec_and_lock(atomic,lock) atomic_dec_and_test(atomic)
multiline_comment|/*&n; * Your basic spinlocks, allowing only a single CPU anywhere&n; *&n; * Most gcc versions have a nasty bug with empty initializers.&n; */
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
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;do { } while(0)
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;(void)(lock) /* Not &quot;unused variable&quot;. */
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)&t;(0)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;({1; })
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;do { } while(0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;do { } while(0)
macro_line|#elif (DEBUG_SPINLOCKS &lt; 2)
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
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { (x)-&gt;lock = 0; } while (0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)&t;(test_bit(0,(lock)))
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;(!test_and_set_bit(0,(lock)))
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x)&t;&t;do { (x)-&gt;lock = 1; } while (0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do { } while (0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(x)&t;&t;do { (x)-&gt;lock = 0; } while (0)
macro_line|#else /* (DEBUG_SPINLOCKS &gt;= 2) */
r_typedef
r_struct
(brace
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
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED (spinlock_t) { 0, 25, __BASE_FILE__ }
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x)&t;do { (x)-&gt;lock = 0; } while (0)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)&t;(test_bit(0,(lock)))
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;(!test_and_set_bit(0,(lock)))
DECL|macro|spin_lock
mdefine_line|#define spin_lock(x)&t;&t;do {unsigned long __spinflags; save_flags(__spinflags); cli(); if ((x)-&gt;lock&amp;&amp;(x)-&gt;babble) {printk(&quot;%s:%d: spin_lock(%s:%p) already locked&bslash;n&quot;, __BASE_FILE__,__LINE__, (x)-&gt;module, (x));(x)-&gt;babble--;} (x)-&gt;lock = 1; restore_flags(__spinflags);} while (0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(x)&t;do {unsigned long __spinflags; save_flags(__spinflags); cli(); if ((x)-&gt;lock&amp;&amp;(x)-&gt;babble) {printk(&quot;%s:%d: spin_unlock_wait(%s:%p) deadlock&bslash;n&quot;, __BASE_FILE__,__LINE__, (x)-&gt;module, (x));(x)-&gt;babble--;} restore_flags(__spinflags);} while (0)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(x)&t;&t;do {unsigned long __spinflags; save_flags(__spinflags); cli(); if (!(x)-&gt;lock&amp;&amp;(x)-&gt;babble) {printk(&quot;%s:%d: spin_unlock(%s:%p) not locked&bslash;n&quot;, __BASE_FILE__,__LINE__, (x)-&gt;module, (x));(x)-&gt;babble--;} (x)-&gt;lock = 0; restore_flags(__spinflags);} while (0)
macro_line|#endif&t;/* DEBUG_SPINLOCKS */
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; *&n; * Most gcc versions have a nasty bug with empty initializers.&n; */
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
mdefine_line|#define rwlock_init(lock)&t;do { } while(0)
DECL|macro|read_lock
mdefine_line|#define read_lock(lock)&t;&t;(void)(lock) /* Not &quot;unused variable&quot;. */
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock)&t;do { } while(0)
DECL|macro|write_lock
mdefine_line|#define write_lock(lock)&t;(void)(lock) /* Not &quot;unused variable&quot;. */
DECL|macro|write_unlock
mdefine_line|#define write_unlock(lock)&t;do { } while(0)
macro_line|#endif /* !SMP */
multiline_comment|/* &quot;lock on reference count zero&quot; */
macro_line|#ifndef atomic_dec_and_lock
macro_line|#include &lt;asm/atomic.h&gt;
r_extern
r_int
id|atomic_dec_and_lock
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
macro_line|#endif /* __LINUX_SPINLOCK_H */
eof
