macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;linux/mqueue.h&gt;
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
DECL|variable|init_mm
id|EXPORT_SYMBOL
c_func
(paren
id|init_mm
)paren
suffix:semicolon
DECL|variable|init_task
id|EXPORT_SYMBOL
c_func
(paren
id|init_task
)paren
suffix:semicolon
multiline_comment|/* .text section in head.S is aligned at 8k boundary and this gets linked&n; * right after that so that the init_thread_union is aligned properly as well.&n; * If this is not aligned on a 8k boundry, then you should change code&n; * in etrap.S which assumes it.&n; */
DECL|variable|init_thread_union
r_union
id|thread_union
id|init_thread_union
id|__attribute__
c_func
(paren
(paren
id|section
(paren
l_string|&quot;.text&bslash;&quot;&bslash;n&bslash;t#&quot;
)paren
)paren
)paren
id|__attribute__
c_func
(paren
(paren
id|aligned
(paren
id|THREAD_SIZE
)paren
)paren
)paren
op_assign
(brace
id|INIT_THREAD_INFO
c_func
(paren
id|init_task
)paren
)brace
suffix:semicolon
eof
