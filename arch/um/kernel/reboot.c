multiline_comment|/* &n; * Copyright (C) 2000 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|kill_off_processes
r_static
r_void
id|kill_off_processes
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|me
suffix:semicolon
id|me
op_assign
id|os_getpid
c_func
(paren
)paren
suffix:semicolon
(def_block
id|for_each_process
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;thread.extern_pid
op_ne
id|me
)paren
(brace
id|os_kill_process
c_func
(paren
id|p-&gt;thread.extern_pid
)paren
suffix:semicolon
)brace
)brace
)def_block
r_if
c_cond
(paren
id|init_task.thread.extern_pid
op_ne
id|me
)paren
(brace
id|os_kill_process
c_func
(paren
id|init_task.thread.extern_pid
)paren
suffix:semicolon
)brace
)brace
DECL|function|uml_cleanup
r_void
id|uml_cleanup
c_func
(paren
r_void
)paren
(brace
id|kill_off_processes
c_func
(paren
)paren
suffix:semicolon
id|do_uml_exitcalls
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
id|do_uml_exitcalls
c_func
(paren
)paren
suffix:semicolon
id|kill_off_processes
c_func
(paren
)paren
suffix:semicolon
id|tracing_reboot
c_func
(paren
)paren
suffix:semicolon
id|os_kill_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
id|do_uml_exitcalls
c_func
(paren
)paren
suffix:semicolon
id|kill_off_processes
c_func
(paren
)paren
suffix:semicolon
id|tracing_halt
c_func
(paren
)paren
suffix:semicolon
id|os_kill_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|machine_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
