macro_line|#ifndef __LINUX_SEQLOCK_H
DECL|macro|__LINUX_SEQLOCK_H
mdefine_line|#define __LINUX_SEQLOCK_H
multiline_comment|/*&n; * Reader/writer consistent mechanism without starving writers. This type of&n; * lock for data where the reader wants a consitent set of information&n; * and is willing to retry if the information changes.  Readers never&n; * block but they may have to retry if a writer is in&n; * progress. Writers do not wait for readers. &n; *&n; * This is not as cache friendly as brlock. Also, this will not work&n; * for data that contains pointers, because any writer could&n; * invalidate a pointer that a reader was following.&n; *&n; * Expected reader usage:&n; * &t;do {&n; *&t;    seq = read_seqbegin(&amp;foo);&n; * &t;...&n; *      } while (read_seqretry(&amp;foo, seq));&n; *&n; *&n; * On non-SMP the spin locks disappear but the writer still needs&n; * to increment the sequence variables because an interrupt routine could&n; * change the state of the data.&n; *&n; * Based on x86_64 vsyscall gettimeofday &n; * by Keith Owens and Andrea Arcangeli&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/preempt.h&gt;
r_typedef
r_struct
(brace
DECL|member|sequence
r_int
id|sequence
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|typedef|seqlock_t
)brace
id|seqlock_t
suffix:semicolon
multiline_comment|/*&n; * These macros triggered gcc-3.x compile-time problems.  We think these are&n; * OK now.  Be cautious.&n; */
DECL|macro|SEQLOCK_UNLOCKED
mdefine_line|#define SEQLOCK_UNLOCKED { 0, SPIN_LOCK_UNLOCKED }
DECL|macro|seqlock_init
mdefine_line|#define seqlock_init(x)&t;do { *(x) = (seqlock_t) SEQLOCK_UNLOCKED; } while (0)
multiline_comment|/* Lock out other writers and update the count.&n; * Acts like a normal spin_lock/unlock.&n; * Don&squot;t need preempt_disable() because that is in the spin_lock already.&n; */
DECL|function|write_seqlock
r_static
r_inline
r_void
id|write_seqlock
c_func
(paren
id|seqlock_t
op_star
id|sl
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|sl-&gt;lock
)paren
suffix:semicolon
op_increment
id|sl-&gt;sequence
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|write_sequnlock
r_static
r_inline
r_void
id|write_sequnlock
c_func
(paren
id|seqlock_t
op_star
id|sl
)paren
(brace
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
id|sl-&gt;sequence
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|sl-&gt;lock
)paren
suffix:semicolon
)brace
DECL|function|write_tryseqlock
r_static
r_inline
r_int
id|write_tryseqlock
c_func
(paren
id|seqlock_t
op_star
id|sl
)paren
(brace
r_int
id|ret
op_assign
id|spin_trylock
c_func
(paren
op_amp
id|sl-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
op_increment
id|sl-&gt;sequence
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Start of read calculation -- fetch last complete writer token */
DECL|function|read_seqbegin
r_static
r_inline
r_int
id|read_seqbegin
c_func
(paren
r_const
id|seqlock_t
op_star
id|sl
)paren
(brace
r_int
id|ret
op_assign
id|sl-&gt;sequence
suffix:semicolon
id|smp_rmb
c_func
(paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Test if reader processed invalid data.&n; * If initial values is odd, &n; *&t;then writer had already started when section was entered&n; * If sequence value changed&n; *&t;then writer changed data while in section&n; *    &n; * Using xor saves one conditional branch.&n; */
DECL|function|read_seqretry
r_static
r_inline
r_int
id|read_seqretry
c_func
(paren
r_const
id|seqlock_t
op_star
id|sl
comma
r_int
id|iv
)paren
(brace
id|smp_rmb
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|iv
op_amp
l_int|1
)paren
op_or
(paren
id|sl-&gt;sequence
op_xor
id|iv
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Possible sw/hw IRQ protected versions of the interfaces.&n; */
DECL|macro|write_seqlock_irqsave
mdefine_line|#define write_seqlock_irqsave(lock, flags)&t;&t;&t;&t;&bslash;&n;&t;do { local_irq_save(flags); write_seqlock(lock); } while (0)
DECL|macro|write_seqlock_irq
mdefine_line|#define write_seqlock_irq(lock)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do { local_irq_disable();   write_seqlock(lock); } while (0)
DECL|macro|write_seqlock_bh
mdefine_line|#define write_seqlock_bh(lock)&t;&t;&t;&t;&t;&t;&bslash;&n;        do { local_bh_disable();    write_seqlock(lock); } while (0)
DECL|macro|write_sequnlock_irqrestore
mdefine_line|#define write_sequnlock_irqrestore(lock, flags)&t;&t;&t;&t;&bslash;&n;&t;do { write_sequnlock(lock); local_irq_restore(flags); } while(0)
DECL|macro|write_sequnlock_irq
mdefine_line|#define write_sequnlock_irq(lock)&t;&t;&t;&t;&t;&bslash;&n;&t;do { write_sequnlock(lock); local_irq_enable(); } while(0)
DECL|macro|write_sequnlock_bh
mdefine_line|#define write_sequnlock_bh(lock)&t;&t;&t;&t;&t;&bslash;&n;&t;do { write_sequnlock(lock); local_bh_enable(); } while(0)
DECL|macro|read_seqbegin_irqsave
mdefine_line|#define read_seqbegin_irqsave(lock, flags)&t;&t;&t;&t;&bslash;&n;&t;({ local_irq_save(flags);   read_seqbegin(lock); })
DECL|macro|read_seqretry_irqrestore
mdefine_line|#define read_seqretry_irqrestore(lock, iv, flags)&t;&t;&t;&bslash;&n;&t;({int ret = read_seqretry(&amp;(lock)-&gt;seq, iv);&t;&t;&t;&bslash;&n;&t;&t;local_irq_restore(flags);&t;&t;&t;&t;&bslash;&n;&t;&t;ret;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;})
macro_line|#endif /* __LINUX_SEQLOCK_H */
eof
