macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
multiline_comment|/* .text section in head.S is aligned at 8k boundry and this gets linked&n; * right after that so that the init_task_union is aligned properly as well.&n; * If this is not aligned on a 8k boundry, then you should change code&n; * in etrap.S which assumes it.&n; */
id|__asm__
c_func
(paren
l_string|&quot;.section &bslash;&quot;.text&bslash;&quot;,#alloc&bslash;n&quot;
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
eof
