multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/list.h&quot;
macro_line|#include &quot;linux/spinlock.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;asm/current.h&quot;
macro_line|#include &quot;asm/segment.h&quot;
macro_line|#include &quot;asm/mmu.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;skas.h&quot;
DECL|function|init_new_context_skas
r_int
id|init_new_context_skas
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
id|from
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;mm
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|current-&gt;mm
op_ne
op_amp
id|init_mm
)paren
)paren
(brace
id|from
op_assign
id|current-&gt;mm-&gt;context.skas.mm_fd
suffix:semicolon
)brace
r_else
id|from
op_assign
op_minus
l_int|1
suffix:semicolon
id|mm-&gt;context.skas.mm_fd
op_assign
id|new_mm
c_func
(paren
id|from
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;context.skas.mm_fd
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;init_new_context_skas - new_mm failed, errno = %d&bslash;n&quot;
comma
id|mm-&gt;context.skas.mm_fd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|destroy_context_skas
r_void
id|destroy_context_skas
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|os_close_file
c_func
(paren
id|mm-&gt;context.skas.mm_fd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
