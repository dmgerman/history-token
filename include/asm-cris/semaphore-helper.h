multiline_comment|/* $Id: semaphore-helper.h,v 1.3 2001/03/26 15:00:33 orjanf Exp $&n; *&n; * SMP- and interrupt-safe semaphores helper functions. Generic versions, no&n; * optimizations whatsoever... &n; *&n; */
macro_line|#ifndef _ASM_SEMAPHORE_HELPER_H
DECL|macro|_ASM_SEMAPHORE_HELPER_H
mdefine_line|#define _ASM_SEMAPHORE_HELPER_H
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
DECL|macro|read
mdefine_line|#define read(a) ((a)-&gt;counter)
DECL|macro|inc
mdefine_line|#define inc(a) (((a)-&gt;counter)++)
DECL|macro|dec
mdefine_line|#define dec(a) (((a)-&gt;counter)--)
DECL|macro|count_inc
mdefine_line|#define count_inc(a) ((*(a))++)
multiline_comment|/*&n; * These two _must_ execute atomically wrt each other.&n; */
DECL|function|wake_one_more
r_extern
r_inline
r_void
id|wake_one_more
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
)brace
DECL|function|waking_non_zero
r_extern
r_inline
r_int
id|waking_non_zero
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
OG
l_int|0
)paren
(brace
id|dec
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|waking_non_zero_interruptible
r_extern
r_inline
r_int
id|waking_non_zero_interruptible
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
OG
l_int|0
)paren
(brace
id|dec
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|tsk
)paren
)paren
(brace
id|count_inc
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|waking_non_zero_trylock
r_extern
r_inline
r_int
id|waking_non_zero_trylock
c_func
(paren
r_struct
id|semaphore
op_star
id|sem
)paren
(brace
r_int
id|ret
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
op_le
l_int|0
)paren
id|count_inc
c_func
(paren
op_amp
id|sem-&gt;count
)paren
suffix:semicolon
r_else
(brace
id|dec
c_func
(paren
op_amp
id|sem-&gt;waking
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* _ASM_SEMAPHORE_HELPER_H */
eof
