multiline_comment|/**&n; * @file cpu_buffer.h&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#ifndef OPROFILE_CPU_BUFFER_H
DECL|macro|OPROFILE_CPU_BUFFER_H
mdefine_line|#define OPROFILE_CPU_BUFFER_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/* allocate a sample buffer for each CPU */
r_int
id|alloc_cpu_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|free_cpu_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* CPU buffer is composed of such entries (which are&n; * also used for context switch notes)&n; */
DECL|struct|op_sample
r_struct
id|op_sample
(brace
DECL|member|eip
r_int
r_int
id|eip
suffix:semicolon
DECL|member|event
r_int
r_int
id|event
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|oprofile_cpu_buffer
r_struct
id|oprofile_cpu_buffer
(brace
DECL|member|int_lock
id|spinlock_t
id|int_lock
suffix:semicolon
multiline_comment|/* protected by int_lock */
DECL|member|pos
r_int
r_int
id|pos
suffix:semicolon
DECL|member|last_task
r_struct
id|task_struct
op_star
id|last_task
suffix:semicolon
DECL|member|buffer
r_struct
id|op_sample
op_star
id|buffer
suffix:semicolon
DECL|member|sample_received
r_int
r_int
id|sample_received
suffix:semicolon
DECL|member|sample_lost_locked
r_int
r_int
id|sample_lost_locked
suffix:semicolon
DECL|member|sample_lost_overflow
r_int
r_int
id|sample_lost_overflow
suffix:semicolon
DECL|member|sample_lost_task_exit
r_int
r_int
id|sample_lost_task_exit
suffix:semicolon
DECL|variable|____cacheline_aligned
)brace
id|____cacheline_aligned
suffix:semicolon
r_extern
r_struct
id|oprofile_cpu_buffer
id|cpu_buffer
(braket
)braket
suffix:semicolon
macro_line|#endif /* OPROFILE_CPU_BUFFER_H */
eof
