multiline_comment|/*&n; *  linux/arch/arm/kernel/init_task.c&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
multiline_comment|/*&n; * Initial task structure.&n; *&n; * We need to make sure that this is 8192-byte aligned due to the&n; * way process stacks are handled. This is done by making sure&n; * the linker maps this in the .text segment right after head.S,&n; * and making head.S ensure the proper alignment.&n; *&n; * The things we do for performance..&n; */
DECL|variable|init_task_union
r_union
id|task_union
id|init_task_union
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.init.task&quot;
)paren
)paren
)paren
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
