multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Copyright (C) 2001 Ridgerun,Inc (glonnon@ridgerun.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stddef.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/socket.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;sys/param.h&gt;
macro_line|#include &quot;asm/types.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;ubd_user.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;cow.h&quot;
macro_line|#include &lt;endian.h&gt;
macro_line|#include &lt;byteswap.h&gt;
DECL|function|ignore_sigwinch_sig
r_void
id|ignore_sigwinch_sig
c_func
(paren
r_void
)paren
(brace
id|signal
c_func
(paren
id|SIGWINCH
comma
id|SIG_IGN
)paren
suffix:semicolon
)brace
DECL|function|start_io_thread
r_int
id|start_io_thread
c_func
(paren
r_int
r_int
id|sp
comma
r_int
op_star
id|fd_out
)paren
(brace
r_int
id|pid
comma
id|fds
(braket
l_int|2
)braket
comma
id|err
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|fds
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_io_thread - os_pipe failed, err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|kernel_fd
op_assign
id|fds
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|fd_out
op_assign
id|fds
(braket
l_int|1
)braket
suffix:semicolon
id|pid
op_assign
id|clone
c_func
(paren
id|io_thread
comma
(paren
r_void
op_star
)paren
id|sp
comma
id|CLONE_FILES
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_io_thread - clone failed : errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|errno
suffix:semicolon
r_goto
id|out_close
suffix:semicolon
)brace
r_return
id|pid
suffix:semicolon
id|out_close
suffix:colon
id|os_close_file
c_func
(paren
id|fds
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|fds
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|kernel_fd
op_assign
op_minus
l_int|1
suffix:semicolon
op_star
id|fd_out
op_assign
op_minus
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
