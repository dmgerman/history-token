multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/init_task.h&quot;
macro_line|#include &quot;linux/mqueue.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
DECL|variable|init_fs
r_static
r_struct
id|fs_struct
id|init_fs
op_assign
id|INIT_FS
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
id|EXPORT_SYMBOL
c_func
(paren
id|init_mm
)paren
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
multiline_comment|/*&n; * Initial thread structure.&n; *&n; * We need to make sure that this is 16384-byte aligned due to the&n; * way process stacks are handled. This is done by having a special&n; * &quot;init_task&quot; linker map entry..&n; */
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
DECL|function|unprotect_stack
r_void
id|unprotect_stack
c_func
(paren
r_int
r_int
id|stack
)paren
(brace
id|protect_memory
c_func
(paren
id|stack
comma
(paren
l_int|1
op_lshift
id|CONFIG_KERNEL_STACK_ORDER
)paren
op_star
id|PAGE_SIZE
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
