multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
DECL|struct|grantpt_info
r_struct
id|grantpt_info
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|res
r_int
id|res
suffix:semicolon
DECL|member|err
r_int
id|err
suffix:semicolon
)brace
suffix:semicolon
DECL|function|grantpt_cb
r_static
r_void
id|grantpt_cb
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|grantpt_info
op_star
id|info
op_assign
id|arg
suffix:semicolon
id|info-&gt;res
op_assign
id|grantpt
c_func
(paren
id|info-&gt;fd
)paren
suffix:semicolon
id|info-&gt;err
op_assign
id|errno
suffix:semicolon
)brace
DECL|function|get_pty
r_int
id|get_pty
c_func
(paren
r_void
)paren
(brace
r_struct
id|grantpt_info
id|info
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|os_open_file
c_func
(paren
l_string|&quot;/dev/ptmx&quot;
comma
id|of_rdwr
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;get_pty : Couldn&squot;t open /dev/ptmx - err = %d&bslash;n&quot;
comma
op_minus
id|fd
)paren
suffix:semicolon
r_return
id|fd
suffix:semicolon
)brace
id|info.fd
op_assign
id|fd
suffix:semicolon
id|initial_thread_cb
c_func
(paren
id|grantpt_cb
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info.res
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;get_pty : Couldn&squot;t grant pty - errno = %d&bslash;n&quot;
comma
op_minus
id|info.err
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|unlockpt
c_func
(paren
id|fd
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;get_pty : Couldn&squot;t unlock pty - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
