multiline_comment|/*&n; * Copyright (C) 2000, 2001 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;initrd.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|load_initrd
r_int
id|load_initrd
c_func
(paren
r_char
op_star
id|filename
comma
r_void
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_int
id|fd
comma
id|n
suffix:semicolon
id|fd
op_assign
id|os_open_file
c_func
(paren
id|filename
comma
id|of_read
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
l_string|&quot;Opening &squot;%s&squot; failed - err = %d&bslash;n&quot;
comma
id|filename
comma
op_minus
id|fd
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|n
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
id|buf
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Read of %d bytes from &squot;%s&squot; failed, err = %d&bslash;n&quot;
comma
id|size
comma
id|filename
comma
op_minus
id|n
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
