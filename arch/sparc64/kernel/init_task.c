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
multiline_comment|/* .text section in head.S is aligned at 2 page boundry and this gets linked&n; * right after that so that the init_task_union is aligned properly as well.&n; * We really don&squot;t need this special alignment like the Intel does, but&n; * I do it anyways for completeness.&n; */
id|__asm__
(paren
l_string|&quot;.text&quot;
)paren
suffix:semicolon
DECL|variable|init_task_union
r_union
id|task_union
id|init_task_union
op_assign
(brace
id|INIT_TASK
c_func
(paren
id|init_task_union.task
)paren
)brace
suffix:semicolon
multiline_comment|/*&n; * This is to make the init_task+stack of the right size for &gt;8k pagesize.&n; * The definition of task_union in sched.h makes it 16k wide.&n; */
macro_line|#if PAGE_SHIFT != 13
DECL|variable|init_task_stack
r_char
id|init_task_stack
(braket
id|THREAD_SIZE
op_minus
id|INIT_TASK_SIZE
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
macro_line|#endif
eof
