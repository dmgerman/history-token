multiline_comment|/**&n; * @file cpu_buffer.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; *&n; * Each CPU has a local buffer that stores PC value/event&n; * pairs. We also log context switches when we notice them.&n; * Eventually each CPU&squot;s buffer is processed into the global&n; * event buffer by sync_buffer().&n; *&n; * We use a local buffer for two reasons: an NMI or similar&n; * interrupt cannot synchronise, and high sampling rates&n; * would lead to catastrophic global synchronisation if&n; * a global buffer was used.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;event_buffer.h&quot;
macro_line|#include &quot;cpu_buffer.h&quot;
macro_line|#include &quot;buffer_sync.h&quot;
macro_line|#include &quot;oprof.h&quot;
DECL|variable|__cacheline_aligned
r_struct
id|oprofile_cpu_buffer
id|cpu_buffer
(braket
id|NR_CPUS
)braket
id|__cacheline_aligned
suffix:semicolon
r_static
r_void
id|wq_sync_buffer
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|macro|DEFAULT_TIMER_EXPIRE
mdefine_line|#define DEFAULT_TIMER_EXPIRE (HZ / 10)
DECL|variable|work_enabled
r_int
id|work_enabled
suffix:semicolon
DECL|function|free_cpu_buffers
r_void
id|free_cpu_buffers
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
id|vfree
c_func
(paren
id|cpu_buffer
(braket
id|i
)braket
dot
id|buffer
)paren
suffix:semicolon
)brace
)brace
DECL|function|alloc_cpu_buffers
r_int
id|alloc_cpu_buffers
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|buffer_size
op_assign
id|fs_cpu_buffer_size
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|b
op_assign
op_amp
id|cpu_buffer
(braket
id|i
)braket
suffix:semicolon
id|b-&gt;buffer
op_assign
id|vmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|op_sample
)paren
op_star
id|buffer_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b-&gt;buffer
)paren
r_goto
id|fail
suffix:semicolon
id|b-&gt;last_task
op_assign
l_int|NULL
suffix:semicolon
id|b-&gt;last_is_kernel
op_assign
op_minus
l_int|1
suffix:semicolon
id|b-&gt;tracing
op_assign
l_int|0
suffix:semicolon
id|b-&gt;buffer_size
op_assign
id|buffer_size
suffix:semicolon
id|b-&gt;tail_pos
op_assign
l_int|0
suffix:semicolon
id|b-&gt;head_pos
op_assign
l_int|0
suffix:semicolon
id|b-&gt;sample_received
op_assign
l_int|0
suffix:semicolon
id|b-&gt;sample_lost_overflow
op_assign
l_int|0
suffix:semicolon
id|b-&gt;cpu
op_assign
id|i
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|b-&gt;work
comma
id|wq_sync_buffer
comma
id|b
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|free_cpu_buffers
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|start_cpu_work
r_void
id|start_cpu_work
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|work_enabled
op_assign
l_int|1
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|b
op_assign
op_amp
id|cpu_buffer
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Spread the work by 1 jiffy per cpu so they dont all&n;&t;&t; * fire at once.&n;&t;&t; */
id|schedule_delayed_work_on
c_func
(paren
id|i
comma
op_amp
id|b-&gt;work
comma
id|DEFAULT_TIMER_EXPIRE
op_plus
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|end_cpu_work
r_void
id|end_cpu_work
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|work_enabled
op_assign
l_int|0
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|b
op_assign
op_amp
id|cpu_buffer
(braket
id|i
)braket
suffix:semicolon
id|cancel_delayed_work
c_func
(paren
op_amp
id|b-&gt;work
)paren
suffix:semicolon
)brace
id|flush_scheduled_work
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Resets the cpu buffer to a sane state. */
DECL|function|cpu_buffer_reset
r_void
id|cpu_buffer_reset
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
)paren
(brace
multiline_comment|/* reset these to invalid values; the next sample&n;&t; * collected will populate the buffer with proper&n;&t; * values to initialize the buffer&n;&t; */
id|cpu_buf-&gt;last_is_kernel
op_assign
op_minus
l_int|1
suffix:semicolon
id|cpu_buf-&gt;last_task
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* compute number of available slots in cpu_buffer queue */
DECL|function|nr_available_slots
r_static
r_int
r_int
id|nr_available_slots
c_func
(paren
r_struct
id|oprofile_cpu_buffer
r_const
op_star
id|b
)paren
(brace
r_int
r_int
id|head
op_assign
id|b-&gt;head_pos
suffix:semicolon
r_int
r_int
id|tail
op_assign
id|b-&gt;tail_pos
suffix:semicolon
r_if
c_cond
(paren
id|tail
OG
id|head
)paren
r_return
(paren
id|tail
op_minus
id|head
)paren
op_minus
l_int|1
suffix:semicolon
r_return
id|tail
op_plus
(paren
id|b-&gt;buffer_size
op_minus
id|head
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|increment_head
r_static
r_void
id|increment_head
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|b
)paren
(brace
r_int
r_int
id|new_head
op_assign
id|b-&gt;head_pos
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* Ensure anything written to the slot before we&n;&t; * increment is visible */
id|wmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_head
OL
id|b-&gt;buffer_size
)paren
id|b-&gt;head_pos
op_assign
id|new_head
suffix:semicolon
r_else
id|b-&gt;head_pos
op_assign
l_int|0
suffix:semicolon
)brace
r_inline
r_static
r_void
DECL|function|add_sample
id|add_sample
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|event
)paren
(brace
r_struct
id|op_sample
op_star
id|entry
op_assign
op_amp
id|cpu_buf-&gt;buffer
(braket
id|cpu_buf-&gt;head_pos
)braket
suffix:semicolon
id|entry-&gt;eip
op_assign
id|pc
suffix:semicolon
id|entry-&gt;event
op_assign
id|event
suffix:semicolon
id|increment_head
c_func
(paren
id|cpu_buf
)paren
suffix:semicolon
)brace
r_inline
r_static
r_void
DECL|function|add_code
id|add_code
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|buffer
comma
r_int
r_int
id|value
)paren
(brace
id|add_sample
c_func
(paren
id|buffer
comma
id|ESCAPE_CODE
comma
id|value
)paren
suffix:semicolon
)brace
multiline_comment|/* This must be safe from any context. It&squot;s safe writing here&n; * because of the head/tail separation of the writer and reader&n; * of the CPU buffer.&n; *&n; * is_kernel is needed because on some architectures you cannot&n; * tell if you are in kernel or user space simply by looking at&n; * pc. We tag this in the buffer by generating kernel enter/exit&n; * events whenever is_kernel changes&n; */
DECL|function|log_sample
r_static
r_int
id|log_sample
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
comma
r_int
r_int
id|pc
comma
r_int
id|is_kernel
comma
r_int
r_int
id|event
)paren
(brace
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
id|cpu_buf-&gt;sample_received
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|nr_available_slots
c_func
(paren
id|cpu_buf
)paren
OL
l_int|3
)paren
(brace
id|cpu_buf-&gt;sample_lost_overflow
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|is_kernel
op_assign
op_logical_neg
op_logical_neg
id|is_kernel
suffix:semicolon
id|task
op_assign
id|current
suffix:semicolon
multiline_comment|/* notice a switch from user-&gt;kernel or vice versa */
r_if
c_cond
(paren
id|cpu_buf-&gt;last_is_kernel
op_ne
id|is_kernel
)paren
(brace
id|cpu_buf-&gt;last_is_kernel
op_assign
id|is_kernel
suffix:semicolon
id|add_code
c_func
(paren
id|cpu_buf
comma
id|is_kernel
)paren
suffix:semicolon
)brace
multiline_comment|/* notice a task switch */
r_if
c_cond
(paren
id|cpu_buf-&gt;last_task
op_ne
id|task
)paren
(brace
id|cpu_buf-&gt;last_task
op_assign
id|task
suffix:semicolon
id|add_code
c_func
(paren
id|cpu_buf
comma
(paren
r_int
r_int
)paren
id|task
)paren
suffix:semicolon
)brace
id|add_sample
c_func
(paren
id|cpu_buf
comma
id|pc
comma
id|event
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|oprofile_begin_trace
r_static
r_int
id|oprofile_begin_trace
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
)paren
(brace
r_if
c_cond
(paren
id|nr_available_slots
c_func
(paren
id|cpu_buf
)paren
OL
l_int|4
)paren
(brace
id|cpu_buf-&gt;sample_lost_overflow
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|add_code
c_func
(paren
id|cpu_buf
comma
id|CPU_TRACE_BEGIN
)paren
suffix:semicolon
id|cpu_buf-&gt;tracing
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|oprofile_end_trace
r_static
r_void
id|oprofile_end_trace
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
)paren
(brace
id|cpu_buf-&gt;tracing
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|oprofile_add_sample
r_void
id|oprofile_add_sample
c_func
(paren
r_struct
id|pt_regs
op_star
r_const
id|regs
comma
r_int
r_int
id|event
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
op_assign
op_amp
id|cpu_buffer
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
r_int
r_int
id|pc
op_assign
id|profile_pc
c_func
(paren
id|regs
)paren
suffix:semicolon
r_int
id|is_kernel
op_assign
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|backtrace_depth
)paren
(brace
id|log_sample
c_func
(paren
id|cpu_buf
comma
id|pc
comma
id|is_kernel
comma
id|event
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|oprofile_begin_trace
c_func
(paren
id|cpu_buf
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* if log_sample() fail we can&squot;t backtrace since we lost the source&n;&t; * of this event */
r_if
c_cond
(paren
id|log_sample
c_func
(paren
id|cpu_buf
comma
id|pc
comma
id|is_kernel
comma
id|event
)paren
)paren
id|oprofile_ops
dot
id|backtrace
c_func
(paren
id|regs
comma
id|backtrace_depth
)paren
suffix:semicolon
id|oprofile_end_trace
c_func
(paren
id|cpu_buf
)paren
suffix:semicolon
)brace
DECL|function|oprofile_add_pc
r_void
id|oprofile_add_pc
c_func
(paren
r_int
r_int
id|pc
comma
r_int
id|is_kernel
comma
r_int
r_int
id|event
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
op_assign
op_amp
id|cpu_buffer
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
id|log_sample
c_func
(paren
id|cpu_buf
comma
id|pc
comma
id|is_kernel
comma
id|event
)paren
suffix:semicolon
)brace
DECL|function|oprofile_add_trace
r_void
id|oprofile_add_trace
c_func
(paren
r_int
r_int
id|pc
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
op_assign
op_amp
id|cpu_buffer
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_buf-&gt;tracing
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|nr_available_slots
c_func
(paren
id|cpu_buf
)paren
OL
l_int|1
)paren
(brace
id|cpu_buf-&gt;tracing
op_assign
l_int|0
suffix:semicolon
id|cpu_buf-&gt;sample_lost_overflow
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* broken frame can give an eip with the same value as an escape code,&n;&t; * abort the trace if we get it */
r_if
c_cond
(paren
id|pc
op_eq
id|ESCAPE_CODE
)paren
(brace
id|cpu_buf-&gt;tracing
op_assign
l_int|0
suffix:semicolon
id|cpu_buf-&gt;backtrace_aborted
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
id|add_sample
c_func
(paren
id|cpu_buf
comma
id|pc
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This serves to avoid cpu buffer overflow, and makes sure&n; * the task mortuary progresses&n; *&n; * By using schedule_delayed_work_on and then schedule_delayed_work&n; * we guarantee this will stay on the correct cpu&n; */
DECL|function|wq_sync_buffer
r_static
r_void
id|wq_sync_buffer
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|b
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|b-&gt;cpu
op_ne
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WQ on CPU%d, prefer CPU%d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|b-&gt;cpu
)paren
suffix:semicolon
)brace
id|sync_buffer
c_func
(paren
id|b-&gt;cpu
)paren
suffix:semicolon
multiline_comment|/* don&squot;t re-add the work if we&squot;re shutting down */
r_if
c_cond
(paren
id|work_enabled
)paren
id|schedule_delayed_work
c_func
(paren
op_amp
id|b-&gt;work
comma
id|DEFAULT_TIMER_EXPIRE
)paren
suffix:semicolon
)brace
eof
