multiline_comment|/*&n; * This is where we statically allocate and initialize the initial&n; * task.&n; *&n; * Copyright (C) 1999, 2002-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;linux/mqueue.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|init_fs
r_static
r_struct
id|fs_struct
id|init_fs
op_assign
id|INIT_FS
suffix:semicolon
DECL|variable|init_files
r_static
r_struct
id|files_struct
id|init_files
op_assign
id|INIT_FILES
suffix:semicolon
DECL|variable|init_signals
r_static
r_struct
id|signal_struct
id|init_signals
op_assign
id|INIT_SIGNALS
c_func
(paren
id|init_signals
)paren
suffix:semicolon
DECL|variable|init_sighand
r_static
r_struct
id|sighand_struct
id|init_sighand
op_assign
id|INIT_SIGHAND
c_func
(paren
id|init_sighand
)paren
suffix:semicolon
DECL|variable|init_mm
r_struct
id|mm_struct
id|init_mm
op_assign
id|INIT_MM
c_func
(paren
id|init_mm
)paren
suffix:semicolon
DECL|variable|init_mm
id|EXPORT_SYMBOL
c_func
(paren
id|init_mm
)paren
suffix:semicolon
multiline_comment|/*&n; * Initial task structure.&n; *&n; * We need to make sure that this is properly aligned due to the way process stacks are&n; * handled. This is done by having a special &quot;.data.init_task&quot; section...&n; */
DECL|macro|init_thread_info
mdefine_line|#define init_thread_info&t;init_task_mem.s.thread_info
r_union
(brace
r_struct
(brace
DECL|member|task
r_struct
id|task_struct
id|task
suffix:semicolon
DECL|member|thread_info
r_struct
id|thread_info
id|thread_info
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|stack
r_int
r_int
id|stack
(braket
id|KERNEL_STACK_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
)brace
id|init_task_mem
id|asm
(paren
l_string|&quot;init_task&quot;
)paren
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;.data.init_task&quot;
)paren
)paren
)paren
op_assign
(brace
(brace
dot
id|task
op_assign
id|INIT_TASK
c_func
(paren
id|init_task_mem.s.task
)paren
comma
dot
id|thread_info
op_assign
id|INIT_THREAD_INFO
c_func
(paren
id|init_task_mem.s.task
)paren
)brace
)brace
suffix:semicolon
DECL|variable|init_task
id|EXPORT_SYMBOL
c_func
(paren
id|init_task
)paren
suffix:semicolon
eof
