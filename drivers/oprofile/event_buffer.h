multiline_comment|/**&n; * @file event_buffer.h&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#ifndef EVENT_BUFFER_H
DECL|macro|EVENT_BUFFER_H
mdefine_line|#define EVENT_BUFFER_H
macro_line|#include &lt;linux/types.h&gt; 
macro_line|#include &lt;asm/semaphore.h&gt;
r_int
id|alloc_event_buffer
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|free_event_buffer
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* wake up the process sleeping on the event file */
r_void
id|wake_up_buffer_waiter
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Each escaped entry is prefixed by ESCAPE_CODE&n; * then one of the following codes, then the&n; * relevant data.&n; */
DECL|macro|ESCAPE_CODE
mdefine_line|#define ESCAPE_CODE&t;&t;&t;~0UL
DECL|macro|CTX_SWITCH_CODE
mdefine_line|#define CTX_SWITCH_CODE &t;&t;1
DECL|macro|CPU_SWITCH_CODE
mdefine_line|#define CPU_SWITCH_CODE &t;&t;2
DECL|macro|COOKIE_SWITCH_CODE
mdefine_line|#define COOKIE_SWITCH_CODE &t;&t;3
DECL|macro|KERNEL_ENTER_SWITCH_CODE
mdefine_line|#define KERNEL_ENTER_SWITCH_CODE&t;4
DECL|macro|KERNEL_EXIT_SWITCH_CODE
mdefine_line|#define KERNEL_EXIT_SWITCH_CODE&t;&t;5
DECL|macro|MODULE_LOADED_CODE
mdefine_line|#define MODULE_LOADED_CODE&t;&t;6
DECL|macro|CTX_TGID_CODE
mdefine_line|#define CTX_TGID_CODE&t;&t;&t;7
DECL|macro|TRACE_BEGIN_CODE
mdefine_line|#define TRACE_BEGIN_CODE&t;&t;8
DECL|macro|TRACE_END_CODE
mdefine_line|#define TRACE_END_CODE&t;&t;&t;9
multiline_comment|/* add data to the event buffer */
r_void
id|add_event_entry
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
id|event_buffer_fops
suffix:semicolon
multiline_comment|/* mutex between sync_cpu_buffers() and the&n; * file reading code.&n; */
r_extern
r_struct
id|semaphore
id|buffer_sem
suffix:semicolon
macro_line|#endif /* EVENT_BUFFER_H */
eof
