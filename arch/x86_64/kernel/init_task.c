macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
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
multiline_comment|/*&n; * Initial task structure.&n; *&n; * We need to make sure that this is 8192-byte aligned due to the&n; * way process stacks are handled. This is done by having a special&n; * &quot;init_task&quot; linker map entry..&n; */
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
multiline_comment|/*&n; * per-CPU TSS segments. Threads are completely &squot;soft&squot; on Linux,&n; * no more per-task TSS&squot;s. The TSS size is kept cacheline-aligned&n; * so they are allowed to end up in the .data.cacheline_aligned&n; * section. Since TSS&squot;s are completely CPU-local, we want them&n; * on exact cacheline boundaries, to eliminate cacheline ping-pong.&n; */
DECL|variable|__cacheline_aligned
r_struct
id|tss_struct
id|init_tss
(braket
id|NR_CPUS
)braket
id|__cacheline_aligned
suffix:semicolon
DECL|macro|ALIGN_TO_4K
mdefine_line|#define ALIGN_TO_4K __attribute__((section(&quot;.data.init_task&quot;)))
DECL|variable|ALIGN_TO_4K
id|pgd_t
id|boot_vmalloc_pgt
(braket
l_int|512
)braket
id|ALIGN_TO_4K
suffix:semicolon
eof
