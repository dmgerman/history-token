multiline_comment|/*&n; * This is where we statically allocate and initialize the initial&n; * task.&n; *&n; * Copyright (C) 1999 Hewlett-Packard Co&n; * Copyright (C) 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|init_mmap
r_static
r_struct
id|vm_area_struct
id|init_mmap
op_assign
id|INIT_MMAP
suffix:semicolon
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
multiline_comment|/*&n; * Initial task structure.&n; *&n; * We need to make sure that this is page aligned due to the way&n; * process stacks are handled. This is done by having a special&n; * &quot;init_task&quot; linker map entry..&n; */
DECL|variable|init_task_union
r_union
id|task_union
id|init_task_union
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;init_task&quot;
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
