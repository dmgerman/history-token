macro_line|#ifndef __LINUX_BRLOCK_H
DECL|macro|__LINUX_BRLOCK_H
mdefine_line|#define __LINUX_BRLOCK_H
multiline_comment|/*&n; * &squot;Big Reader&squot; read-write spinlocks.&n; *&n; * super-fast read/write locks, with write-side penalty. The point&n; * is to have a per-CPU read/write lock. Readers lock their CPU-local&n; * readlock, writers must lock all locks to get write access. These&n; * CPU-read-write locks are semantically identical to normal rwlocks.&n; * Memory usage is higher as well. (NR_CPUS*L1_CACHE_BYTES bytes)&n; *&n; * The most important feature is that these spinlocks do not cause&n; * cacheline ping-pong in the &squot;most readonly data&squot; case.&n; *&n; * Copyright 2000, Ingo Molnar &lt;mingo@redhat.com&gt;&n; *&n; * Registry idea and naming [ crutial! :-) ] by:&n; *&n; *                 David S. Miller &lt;davem@redhat.com&gt;&n; *&n; * David has an implementation that doesn&squot;t use atomic operations in&n; * the read branch via memory ordering tricks - i guess we need to&n; * split this up into a per-arch thing? The atomicity issue is a&n; * secondary item in profiles, at least on x86 platforms.&n; *&n; * The atomic op version overhead is indeed a big deal on&n; * load-locked/store-conditional cpus (ALPHA/MIPS/PPC) and&n; * compare-and-swap cpus (Sparc64).  So we control which&n; * implementation to use with a __BRLOCK_USE_ATOMICS define. -DaveM&n; *&n; */
multiline_comment|/* Register bigreader lock indices here. */
DECL|enum|brlock_indices
r_enum
id|brlock_indices
(brace
DECL|enumerator|BR_NETPROTO_LOCK
id|BR_NETPROTO_LOCK
comma
DECL|enumerator|__BR_END
id|__BR_END
)brace
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SMP
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#if defined(__i386__) || defined(__ia64__) || defined(__x86_64__)
DECL|macro|__BRLOCK_USE_ATOMICS
mdefine_line|#define __BRLOCK_USE_ATOMICS
macro_line|#else
DECL|macro|__BRLOCK_USE_ATOMICS
macro_line|#undef __BRLOCK_USE_ATOMICS
macro_line|#endif
macro_line|#ifdef __BRLOCK_USE_ATOMICS
DECL|typedef|brlock_read_lock_t
r_typedef
id|rwlock_t
id|brlock_read_lock_t
suffix:semicolon
macro_line|#else
DECL|typedef|brlock_read_lock_t
r_typedef
r_int
r_int
id|brlock_read_lock_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * align last allocated index to the next cacheline:&n; */
DECL|macro|__BR_IDX_MAX
mdefine_line|#define __BR_IDX_MAX &bslash;&n;&t;(((sizeof(brlock_read_lock_t)*__BR_END + SMP_CACHE_BYTES-1) &amp; ~(SMP_CACHE_BYTES-1)) / sizeof(brlock_read_lock_t))
r_extern
id|brlock_read_lock_t
id|__brlock_array
(braket
id|NR_CPUS
)braket
(braket
id|__BR_IDX_MAX
)braket
suffix:semicolon
macro_line|#ifndef __BRLOCK_USE_ATOMICS
DECL|struct|br_wrlock
r_struct
id|br_wrlock
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|__aligned__
c_func
(paren
id|SMP_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|br_wrlock
id|__br_write_locks
(braket
id|__BR_IDX_MAX
)braket
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|__br_lock_usage_bug
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef __BRLOCK_USE_ATOMICS
DECL|function|br_read_lock
r_static
r_inline
r_void
id|br_read_lock
(paren
r_enum
id|brlock_indices
id|idx
)paren
(brace
multiline_comment|/*&n;&t; * This causes a link-time bug message if an&n;&t; * invalid index is used:&n;&t; */
r_if
c_cond
(paren
id|idx
op_ge
id|__BR_END
)paren
id|__br_lock_usage_bug
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|_raw_read_lock
c_func
(paren
op_amp
id|__brlock_array
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
DECL|function|br_read_unlock
r_static
r_inline
r_void
id|br_read_unlock
(paren
r_enum
id|brlock_indices
id|idx
)paren
(brace
r_if
c_cond
(paren
id|idx
op_ge
id|__BR_END
)paren
id|__br_lock_usage_bug
c_func
(paren
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|__brlock_array
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
macro_line|#else /* ! __BRLOCK_USE_ATOMICS */
DECL|function|br_read_lock
r_static
r_inline
r_void
id|br_read_lock
(paren
r_enum
id|brlock_indices
id|idx
)paren
(brace
r_int
r_int
op_star
id|ctr
suffix:semicolon
id|spinlock_t
op_star
id|lock
suffix:semicolon
multiline_comment|/*&n;&t; * This causes a link-time bug message if an&n;&t; * invalid index is used:&n;&t; */
r_if
c_cond
(paren
id|idx
op_ge
id|__BR_END
)paren
id|__br_lock_usage_bug
c_func
(paren
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
id|ctr
op_assign
op_amp
id|__brlock_array
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
id|idx
)braket
suffix:semicolon
id|lock
op_assign
op_amp
id|__br_write_locks
(braket
id|idx
)braket
dot
id|lock
suffix:semicolon
id|again
suffix:colon
(paren
op_star
id|ctr
)paren
op_increment
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spin_is_locked
c_func
(paren
id|lock
)paren
)paren
(brace
(paren
op_star
id|ctr
)paren
op_decrement
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;* The release of the ctr must become visible&n;&t;&t;&t;* to the other cpus eventually thus wmb(),&n;&t;&t;&t;* we don&squot;t care if spin_is_locked is reordered&n;&t;&t;&t;* before the releasing of the ctr.&n;&t;&t;&t;* However IMHO this wmb() is superflous even in theory.&n;&t;&t;&t;* It would not be superflous only if on the&n;&t;&t;&t;* other CPUs doing a ldl_l instead of an ldl&n;&t;&t;&t;* would make a difference and I don&squot;t think this is&n;&t;&t;&t;* the case.&n;&t;&t;&t;* I&squot;d like to clarify this issue further&n;&t;&t;&t;* but for now this is a slow path so adding the&n;&t;&t;&t;* wmb() will keep us on the safe side.&n;&t;&t;&t;*/
r_while
c_loop
(paren
id|spin_is_locked
c_func
(paren
id|lock
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
)brace
DECL|function|br_read_unlock
r_static
r_inline
r_void
id|br_read_unlock
(paren
r_enum
id|brlock_indices
id|idx
)paren
(brace
r_int
r_int
op_star
id|ctr
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|__BR_END
)paren
id|__br_lock_usage_bug
c_func
(paren
)paren
suffix:semicolon
id|ctr
op_assign
op_amp
id|__brlock_array
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
(braket
id|idx
)braket
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
(paren
op_star
id|ctr
)paren
op_decrement
suffix:semicolon
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __BRLOCK_USE_ATOMICS */
multiline_comment|/* write path not inlined - it&squot;s rare and larger */
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__br_write_lock
(paren
r_enum
id|brlock_indices
id|idx
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__br_write_unlock
(paren
r_enum
id|brlock_indices
id|idx
)paren
)paren
suffix:semicolon
DECL|function|br_write_lock
r_static
r_inline
r_void
id|br_write_lock
(paren
r_enum
id|brlock_indices
id|idx
)paren
(brace
r_if
c_cond
(paren
id|idx
op_ge
id|__BR_END
)paren
id|__br_lock_usage_bug
c_func
(paren
)paren
suffix:semicolon
id|__br_write_lock
c_func
(paren
id|idx
)paren
suffix:semicolon
)brace
DECL|function|br_write_unlock
r_static
r_inline
r_void
id|br_write_unlock
(paren
r_enum
id|brlock_indices
id|idx
)paren
(brace
r_if
c_cond
(paren
id|idx
op_ge
id|__BR_END
)paren
id|__br_lock_usage_bug
c_func
(paren
)paren
suffix:semicolon
id|__br_write_unlock
c_func
(paren
id|idx
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|br_read_lock
macro_line|# define br_read_lock(idx)&t;({ (void)(idx); preempt_disable(); })
DECL|macro|br_read_unlock
macro_line|# define br_read_unlock(idx)&t;({ (void)(idx); preempt_enable(); })
DECL|macro|br_write_lock
macro_line|# define br_write_lock(idx)&t;({ (void)(idx); preempt_disable(); })
DECL|macro|br_write_unlock
macro_line|# define br_write_unlock(idx)&t;({ (void)(idx); preempt_enable(); })
macro_line|#endif&t;/* CONFIG_SMP */
multiline_comment|/*&n; * Now enumerate all of the possible sw/hw IRQ protected&n; * versions of the interfaces.&n; */
DECL|macro|br_read_lock_irqsave
mdefine_line|#define br_read_lock_irqsave(idx, flags) &bslash;&n;&t;do { local_irq_save(flags); br_read_lock(idx); } while (0)
DECL|macro|br_read_lock_irq
mdefine_line|#define br_read_lock_irq(idx) &bslash;&n;&t;do { local_irq_disable(); br_read_lock(idx); } while (0)
DECL|macro|br_read_lock_bh
mdefine_line|#define br_read_lock_bh(idx) &bslash;&n;&t;do { local_bh_disable(); br_read_lock(idx); } while (0)
DECL|macro|br_write_lock_irqsave
mdefine_line|#define br_write_lock_irqsave(idx, flags) &bslash;&n;&t;do { local_irq_save(flags); br_write_lock(idx); } while (0)
DECL|macro|br_write_lock_irq
mdefine_line|#define br_write_lock_irq(idx) &bslash;&n;&t;do { local_irq_disable(); br_write_lock(idx); } while (0)
DECL|macro|br_write_lock_bh
mdefine_line|#define br_write_lock_bh(idx) &bslash;&n;&t;do { local_bh_disable(); br_write_lock(idx); } while (0)
DECL|macro|br_read_unlock_irqrestore
mdefine_line|#define br_read_unlock_irqrestore(idx, flags) &bslash;&n;&t;do { br_read_unlock(irx); local_irq_restore(flags); } while (0)
DECL|macro|br_read_unlock_irq
mdefine_line|#define br_read_unlock_irq(idx) &bslash;&n;&t;do { br_read_unlock(idx); local_irq_enable(); } while (0)
DECL|macro|br_read_unlock_bh
mdefine_line|#define br_read_unlock_bh(idx) &bslash;&n;&t;do { br_read_unlock(idx); local_bh_enable(); } while (0)
DECL|macro|br_write_unlock_irqrestore
mdefine_line|#define br_write_unlock_irqrestore(idx, flags) &bslash;&n;&t;do { br_write_unlock(irx); local_irq_restore(flags); } while (0)
DECL|macro|br_write_unlock_irq
mdefine_line|#define br_write_unlock_irq(idx) &bslash;&n;&t;do { br_write_unlock(idx); local_irq_enable(); } while (0)
DECL|macro|br_write_unlock_bh
mdefine_line|#define br_write_unlock_bh(idx) &bslash;&n;&t;do { br_write_unlock(idx); local_bh_enable(); } while (0)
macro_line|#endif /* __LINUX_BRLOCK_H */
eof
