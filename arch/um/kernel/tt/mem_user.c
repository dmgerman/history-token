multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &quot;tt.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;user_util.h&quot;
DECL|function|remap_data
r_void
id|remap_data
c_func
(paren
r_void
op_star
id|segment_start
comma
r_void
op_star
id|segment_end
comma
r_int
id|w
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
id|data
comma
id|prot
suffix:semicolon
r_if
c_cond
(paren
id|w
)paren
(brace
id|prot
op_assign
id|PROT_WRITE
suffix:semicolon
)brace
r_else
id|prot
op_assign
l_int|0
suffix:semicolon
id|prot
op_or_assign
id|PROT_READ
op_or
id|PROT_EXEC
suffix:semicolon
id|size
op_assign
(paren
r_int
r_int
)paren
id|segment_end
op_minus
(paren
r_int
r_int
)paren
id|segment_start
suffix:semicolon
id|data
op_assign
id|create_mem_file
c_func
(paren
id|size
)paren
suffix:semicolon
id|addr
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|size
comma
id|PROT_WRITE
op_or
id|PROT_READ
comma
id|MAP_SHARED
comma
id|data
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_eq
id|MAP_FAILED
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;mapping new data segment&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|addr
comma
id|segment_start
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|switcheroo
c_func
(paren
id|data
comma
id|prot
comma
id|addr
comma
id|segment_start
comma
id|size
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;switcheroo failed&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
