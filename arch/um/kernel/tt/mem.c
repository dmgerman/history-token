multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;tt.h&quot;
DECL|function|before_mem_tt
r_void
id|before_mem_tt
c_func
(paren
r_int
r_int
id|brk_start
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|jail
op_logical_or
id|debug
)paren
(brace
id|remap_data
c_func
(paren
id|UML_ROUND_DOWN
c_func
(paren
op_amp
id|_stext
)paren
comma
id|UML_ROUND_UP
c_func
(paren
op_amp
id|_etext
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
id|remap_data
c_func
(paren
id|UML_ROUND_DOWN
c_func
(paren
op_amp
id|_sdata
)paren
comma
id|UML_ROUND_UP
c_func
(paren
op_amp
id|_edata
)paren
comma
l_int|1
)paren
suffix:semicolon
id|remap_data
c_func
(paren
id|UML_ROUND_DOWN
c_func
(paren
op_amp
id|__bss_start
)paren
comma
id|UML_ROUND_UP
c_func
(paren
id|brk_start
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOST_2G_2G
DECL|macro|TOP
mdefine_line|#define TOP 0x80000000
macro_line|#else
DECL|macro|TOP
mdefine_line|#define TOP 0xc0000000
macro_line|#endif
DECL|macro|SIZE
mdefine_line|#define SIZE ((CONFIG_NEST_LEVEL + CONFIG_KERNEL_HALF_GIGS) * 0x20000000)
DECL|macro|START
mdefine_line|#define START (TOP - SIZE)
DECL|function|set_task_sizes_tt
r_int
r_int
id|set_task_sizes_tt
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
op_star
id|host_size_out
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
op_star
id|task_size_out
op_assign
id|START
suffix:semicolon
r_return
id|START
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
