multiline_comment|/*&n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sys/param.h&gt;
macro_line|#include &quot;init.h&quot;
DECL|variable|tempdir
r_char
op_star
id|tempdir
op_assign
l_int|NULL
suffix:semicolon
DECL|function|find_tempdir
r_static
r_void
id|__init
id|find_tempdir
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|dirs
(braket
)braket
op_assign
(brace
l_string|&quot;TMP&quot;
comma
l_string|&quot;TEMP&quot;
comma
l_string|&quot;TMPDIR&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|dir
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tempdir
op_ne
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* We&squot;ve already been called */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|dirs
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dir
op_assign
id|getenv
c_func
(paren
id|dirs
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
op_ne
l_int|NULL
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dir
op_eq
l_int|NULL
)paren
(brace
id|dir
op_assign
l_string|&quot;/tmp&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|dir
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|dir
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dir
op_ne
l_int|NULL
)paren
(brace
id|tempdir
op_assign
id|malloc
c_func
(paren
id|strlen
c_func
(paren
id|dir
)paren
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tempdir
op_eq
l_int|NULL
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Failed to malloc tempdir, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|tempdir
comma
id|dir
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|tempdir
comma
l_string|&quot;/&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|make_tempfile
r_int
id|make_tempfile
c_func
(paren
r_const
r_char
op_star
r_template
comma
r_char
op_star
op_star
id|out_tempname
comma
r_int
id|do_unlink
)paren
(brace
r_char
id|tempname
(braket
id|MAXPATHLEN
)braket
suffix:semicolon
r_int
id|fd
suffix:semicolon
id|find_tempdir
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
r_template
op_ne
l_char|&squot;/&squot;
)paren
id|strcpy
c_func
(paren
id|tempname
comma
id|tempdir
)paren
suffix:semicolon
r_else
op_star
id|tempname
op_assign
l_int|0
suffix:semicolon
id|strcat
c_func
(paren
id|tempname
comma
r_template
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|mkstemp
c_func
(paren
id|tempname
)paren
)paren
OL
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;open - cannot create %s: %s&bslash;n&quot;
comma
id|tempname
comma
id|strerror
c_func
(paren
id|errno
)paren
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
id|do_unlink
op_logical_and
(paren
id|unlink
c_func
(paren
id|tempname
)paren
OL
l_int|0
)paren
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;unlink&quot;
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
id|out_tempname
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|out_tempname
op_assign
id|strdup
c_func
(paren
id|tempname
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;strdup&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|fd
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
