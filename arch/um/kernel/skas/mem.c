multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;mem_user.h&quot;
DECL|function|set_task_sizes_skas
r_int
r_int
id|set_task_sizes_skas
c_func
(paren
r_int
id|arg
comma
r_int
r_int
op_star
id|host_size_out
comma
r_int
r_int
op_star
id|task_size_out
)paren
(brace
multiline_comment|/* Round up to the nearest 4M */
r_int
r_int
id|top
op_assign
id|ROUND_4M
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|arg
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HOST_TASK_SIZE
op_star
id|host_size_out
op_assign
id|CONFIG_HOST_TASK_SIZE
suffix:semicolon
op_star
id|task_size_out
op_assign
id|CONFIG_HOST_TASK_SIZE
suffix:semicolon
macro_line|#else
op_star
id|host_size_out
op_assign
id|top
suffix:semicolon
op_star
id|task_size_out
op_assign
id|top
suffix:semicolon
macro_line|#endif
r_return
(paren
(paren
r_int
r_int
)paren
id|set_task_sizes_skas
)paren
op_amp
op_complement
l_int|0xffffff
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
