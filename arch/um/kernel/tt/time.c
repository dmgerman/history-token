multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;time_user.h&gt;
macro_line|#include &quot;process.h&quot;
macro_line|#include &quot;user.h&quot;
DECL|function|user_time_init_tt
r_void
id|user_time_init_tt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|signal
c_func
(paren
id|SIGVTALRM
comma
(paren
id|__sighandler_t
)paren
id|alarm_handler
)paren
op_eq
id|SIG_ERR
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Couldn&squot;t set SIGVTALRM handler&quot;
)paren
suffix:semicolon
)brace
id|set_interval
c_func
(paren
id|ITIMER_VIRTUAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
