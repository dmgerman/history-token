macro_line|#ifndef __LINUX_SPINLOCK_H
DECL|macro|__LINUX_SPINLOCK_H
mdefine_line|#define __LINUX_SPINLOCK_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
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
mdefine_line|#define spin_unlock_irqrestore(lock, flags)&t;do { _raw_spin_unlock(lock);  local_irq_restore(flags); preempt_enable(); } while (0)
DECL|macro|_raw_spin_unlock_irqrestore
mdefine_line|#define _raw_spin_unlock_irqrestore(lock, flags) do { _raw_spin_unlock(lock);  local_irq_restore(flags); } while (0)
DECL|macro|spin_unlock_irq
mdefine_line|#define spin_unlock_irq(lock)&t;&t;&t;do { _raw_spin_unlock(lock);  local_irq_enable(); preempt_enable();       } while (0)
DECL|macro|spin_unlock_bh
mdefine_line|#define spin_unlock_bh(lock)&t;&t;&t;do { spin_unlock(lock); local_bh_enable(); } while (0)
DECL|macro|read_unlock_irqrestore
mdefine_line|#define read_unlock_irqrestore(lock, flags)&t;do { _raw_read_unlock(lock);  local_irq_restore(flags); preempt_enable(); } while (0)
DECL|macro|read_unlock_irq
mdefine_line|#define read_unlock_irq(lock)&t;&t;&t;do { _raw_read_unlock(lock);  local_irq_enable(); preempt_enable(); } while (0)
DECL|macro|read_unlock_bh
mdefine_line|#define read_unlock_bh(lock)&t;&t;&t;do { read_unlock(lock);  local_bh_enable();        } while (0)
DECL|macro|write_unlock_irqrestore
mdefine_line|#define write_unlock_irqrestore(lock, flags)&t;do { _raw_write_unlock(lock); local_irq_restore(flags); preempt_enable(); } while (0)
DECL|macro|write_unlock_irq
mdefine_line|#define write_unlock_irq(lock)&t;&t;&t;do { _raw_write_unlock(lock); local_irq_enable(); preempt_enable();       } while (0)
DECL|macro|write_unlock_bh
mdefine_line|#define write_unlock_bh(lock)&t;&t;&t;do { write_unlock(lock); local_bh_enable();        } while (0)
DECL|macro|spin_trylock_bh
mdefine_line|#define spin_trylock_bh(lock)&t;&t;&t;({ int __r; local_bh_disable();&bslash;&n;&t;&t;&t;&t;&t;&t;__r = spin_trylock(lock);      &bslash;&n;&t;&t;&t;&t;&t;&t;if (!__r) local_bh_enable();   &bslash;&n;&t;&t;&t;&t;&t;&t;__r; })
multiline_comment|/* Must define these before including other files, inline functions need them */
macro_line|#include &lt;linux/stringify.h&gt;
DECL|macro|LOCK_SECTION_NAME
mdefine_line|#define LOCK_SECTION_NAME&t;&t;&t;&bslash;&n;&t;&quot;.text.lock.&quot; __stringify(KBUILD_BASENAME)
DECL|macro|LOCK_SECTION_START
mdefine_line|#define LOCK_SECTION_START(extra)&t;&t;&bslash;&n;&t;&quot;.subsection 1&bslash;n&bslash;t&quot;&t;&t;&t;&bslash;&n;&t;extra&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;.ifndef &quot; LOCK_SECTION_NAME &quot;&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;LOCK_SECTION_NAME &quot;:&bslash;n&bslash;t&quot;&t;&t;&bslash;&n;&t;&quot;.endif&bslash;n&bslash;t&quot;
DECL|macro|LOCK_SECTION_END
mdefine_line|#define LOCK_SECTION_END&t;&t;&t;&bslash;&n;&t;&quot;.previous&bslash;n&bslash;t&quot;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#elif !defined(spin_lock_init) /* !SMP and spin_lock_init not previously&n;                                  defined (e.g. by including asm/spinlock.h */
macro_line|#ifndef CONFIG_PREEMPT
DECL|macro|atomic_dec_and_lock
macro_line|# define atomic_dec_and_lock(atomic,lock) atomic_dec_and_test(atomic)
DECL|macro|ATOMIC_DEC_AND_LOCK
macro_line|# define ATOMIC_DEC_AND_LOCK
macro_line|#endif
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
macro_line|# define SPIN_LOCK_UNLOCKED (spinlock_t) { }
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
macro_line|# define SPIN_LOCK_UNLOCKED (spinlock_t) { 0 }
macro_line|#endif
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_spin_lock
mdefine_line|#define _raw_spin_lock(lock)&t;(void)(lock) /* Not &quot;unused variable&quot;. */
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(lock)&t;((void)(lock), 0)
DECL|macro|_raw_spin_trylock
mdefine_line|#define _raw_spin_trylock(lock)&t;((void)(lock), 1)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lock)&t;do { (void)(lock); } while(0)
DECL|macro|_raw_spin_unlock
mdefine_line|#define _raw_spin_unlock(lock)&t;do { (void)(lock); } while(0)
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
DECL|macro|_raw_read_lock
mdefine_line|#define _raw_read_lock(lock)&t;(void)(lock) /* Not &quot;unused variable&quot;. */
DECL|macro|_raw_read_unlock
mdefine_line|#define _raw_read_unlock(lock)&t;do { } while(0)
DECL|macro|_raw_write_lock
mdefine_line|#define _raw_write_lock(lock)&t;(void)(lock) /* Not &quot;unused variable&quot;. */
DECL|macro|_raw_write_unlock
mdefine_line|#define _raw_write_unlock(lock)&t;do { } while(0)
macro_line|#endif /* !SMP */
macro_line|#ifdef CONFIG_PREEMPT
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&bslash;&n;do { &bslash;&n;&t;preempt_disable(); &bslash;&n;&t;_raw_spin_lock(lock); &bslash;&n;} while(0)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;({preempt_disable(); _raw_spin_trylock(lock) ? &bslash;&n;&t;&t;&t;&t;1 : ({preempt_enable(); 0;});})
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock) &bslash;&n;do { &bslash;&n;&t;_raw_spin_unlock(lock); &bslash;&n;&t;preempt_enable(); &bslash;&n;} while (0)
DECL|macro|read_lock
mdefine_line|#define read_lock(lock)&t;&t;({preempt_disable(); _raw_read_lock(lock);})
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock)&t;({_raw_read_unlock(lock); preempt_enable();})
DECL|macro|write_lock
mdefine_line|#define write_lock(lock)&t;({preempt_disable(); _raw_write_lock(lock);})
DECL|macro|write_unlock
mdefine_line|#define write_unlock(lock)&t;({_raw_write_unlock(lock); preempt_enable();})
DECL|macro|write_trylock
mdefine_line|#define write_trylock(lock)&t;({preempt_disable();_raw_write_trylock(lock) ? &bslash;&n;&t;&t;&t;&t;1 : ({preempt_enable(); 0;});})
macro_line|#else
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lock)&t;&t;&t;_raw_spin_lock(lock)
DECL|macro|spin_trylock
mdefine_line|#define spin_trylock(lock)&t;&t;_raw_spin_trylock(lock)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lock)&t;&t;_raw_spin_unlock(lock)
DECL|macro|read_lock
mdefine_line|#define read_lock(lock)&t;&t;&t;_raw_read_lock(lock)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(lock)&t;&t;_raw_read_unlock(lock)
DECL|macro|write_lock
mdefine_line|#define write_lock(lock)&t;&t;_raw_write_lock(lock)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(lock)&t;&t;_raw_write_unlock(lock)
DECL|macro|write_trylock
mdefine_line|#define write_trylock(lock)&t;&t;_raw_write_trylock(lock)
macro_line|#endif
multiline_comment|/* &quot;lock on reference count zero&quot; */
macro_line|#ifndef ATOMIC_DEC_AND_LOCK
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
