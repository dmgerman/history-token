macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
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
multiline_comment|/* .text section in head.S is aligned at 2 page boundry and this gets linked&n; * right after that so that the init_thread_union is aligned properly as well.&n; * We really don&squot;t need this special alignment like the Intel does, but&n; * I do it anyways for completeness.&n; */
id|__asm__
(paren
l_string|&quot;.text&quot;
)paren
suffix:semicolon
DECL|variable|init_thread_union
r_union
id|thread_union
id|init_thread_union
op_assign
(brace
id|INIT_THREAD_INFO
c_func
(paren
id|init_task
)paren
)brace
suffix:semicolon
multiline_comment|/*&n; * This is to make the init_thread+stack be the right size for &gt;8k pagesize.&n; * The definition of thread_union in sched.h makes it 16k wide.&n; */
macro_line|#if PAGE_SHIFT != 13
DECL|variable|init_task_stack
r_char
id|init_task_stack
(braket
id|THREAD_SIZE
op_minus
id|INIT_THREAD_SIZE
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Initial task structure.&n; *&n; * All other task structs will be allocated on slabs in fork.c&n; */
id|__asm__
c_func
(paren
l_string|&quot;.data&quot;
)paren
suffix:semicolon
DECL|variable|init_task
r_struct
id|task_struct
id|init_task
op_assign
id|INIT_TASK
c_func
(paren
id|init_task
)paren
suffix:semicolon
eof
