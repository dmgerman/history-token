macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_SPINLOCK_H
DECL|macro|__ASM_SPINLOCK_H
mdefine_line|#define __ASM_SPINLOCK_H
multiline_comment|/*&n; * Simple spin lock operations.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|owner_pc
r_volatile
r_int
r_int
id|owner_pc
suffix:semicolon
DECL|member|owner_cpu
r_volatile
r_int
r_int
id|owner_cpu
suffix:semicolon
DECL|typedef|spinlock_t
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED&t;(spinlock_t) { 0, 0, 0 }
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(lp) &t;do { (lp)-&gt;lock = 0; } while(0)
DECL|macro|spin_unlock_wait
mdefine_line|#define spin_unlock_wait(lp)&t;do { barrier(); } while((lp)-&gt;lock)
DECL|macro|spin_is_locked
mdefine_line|#define spin_is_locked(x)&t;((x)-&gt;lock != 0)
r_extern
r_void
id|_spin_lock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_void
id|_spin_unlock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
r_extern
r_int
id|spin_trylock
c_func
(paren
id|spinlock_t
op_star
id|lock
)paren
suffix:semicolon
DECL|macro|spin_lock
mdefine_line|#define spin_lock(lp)&t;&t;&t;_spin_lock(lp)
DECL|macro|spin_unlock
mdefine_line|#define spin_unlock(lp)&t;&t;&t;_spin_unlock(lp)
r_extern
r_int
r_int
id|__spin_trylock
c_func
(paren
r_volatile
r_int
r_int
op_star
id|lock
)paren
suffix:semicolon
multiline_comment|/*&n; * Read-write spinlocks, allowing multiple readers&n; * but only one writer.&n; *&n; * NOTE! it is quite common to have readers in interrupts&n; * but no interrupt writers. For those circumstances we&n; * can &quot;mix&quot; irq-safe locks - any writer needs to get a&n; * irq-safe write-lock, but readers can get non-irqsafe&n; * read-locks.&n; */
r_typedef
r_struct
(brace
DECL|member|lock
r_volatile
r_int
r_int
id|lock
suffix:semicolon
DECL|member|owner_pc
r_volatile
r_int
r_int
id|owner_pc
suffix:semicolon
DECL|typedef|rwlock_t
)brace
id|rwlock_t
suffix:semicolon
DECL|macro|RW_LOCK_UNLOCKED
mdefine_line|#define RW_LOCK_UNLOCKED (rwlock_t) { 0, 0 }
DECL|macro|rwlock_init
mdefine_line|#define rwlock_init(lp) do { *(lp) = RW_LOCK_UNLOCKED; } while(0)
r_extern
r_void
id|_read_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_read_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_lock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
r_extern
r_void
id|_write_unlock
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
suffix:semicolon
DECL|macro|read_lock
mdefine_line|#define read_lock(rw)&t;&t;_read_lock(rw)
DECL|macro|write_lock
mdefine_line|#define write_lock(rw)&t;&t;_write_lock(rw)
DECL|macro|write_unlock
mdefine_line|#define write_unlock(rw)&t;_write_unlock(rw)
DECL|macro|read_unlock
mdefine_line|#define read_unlock(rw)&t;&t;_read_unlock(rw)
macro_line|#endif /* __ASM_SPINLOCK_H */
macro_line|#endif /* __KERNEL__ */
eof
