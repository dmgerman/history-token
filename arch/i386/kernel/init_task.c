macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mqueue.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
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
multiline_comment|/*&n; * Initial thread structure.&n; *&n; * We need to make sure that this is THREAD_SIZE aligned due to the&n; * way process stacks are handled. This is done by having a special&n; * &quot;init_task&quot; linker map entry..&n; */
DECL|variable|init_thread_union
r_union
id|thread_union
id|init_thread_union
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data.init_task&quot;
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
multiline_comment|/*&n; * Initial task structure.&n; *&n; * All other task structs will be allocated on slabs in fork.c&n; */
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
DECL|variable|init_task
id|EXPORT_SYMBOL
c_func
(paren
id|init_task
)paren
suffix:semicolon
multiline_comment|/*&n; * per-CPU TSS segments. Threads are completely &squot;soft&squot; on Linux,&n; * no more per-task TSS&squot;s.&n; */
id|DEFINE_PER_CPU
c_func
(paren
r_struct
id|tss_struct
comma
id|init_tss
)paren
id|____cacheline_maxaligned_in_smp
op_assign
id|INIT_TSS
suffix:semicolon
eof
