multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@addtoit.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;user_util.h&quot;
DECL|macro|ARBITRARY_ADDR
mdefine_line|#define ARBITRARY_ADDR -1
DECL|macro|FAILURE_PID
mdefine_line|#define FAILURE_PID    -1
DECL|macro|STAT_PATH_LEN
mdefine_line|#define STAT_PATH_LEN sizeof(&quot;/proc/#######/stat&bslash;0&quot;)
DECL|macro|COMM_SCANF
mdefine_line|#define COMM_SCANF &quot;%*[^)])&quot;
DECL|function|os_process_pc
r_int
r_int
id|os_process_pc
c_func
(paren
r_int
id|pid
)paren
(brace
r_char
id|proc_stat
(braket
id|STAT_PATH_LEN
)braket
comma
id|buf
(braket
l_int|256
)braket
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
r_int
id|fd
comma
id|err
suffix:semicolon
id|sprintf
c_func
(paren
id|proc_stat
comma
l_string|&quot;/proc/%d/stat&quot;
comma
id|pid
)paren
suffix:semicolon
id|fd
op_assign
id|os_open_file
c_func
(paren
id|proc_stat
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
l_string|&quot;os_process_pc - couldn&squot;t open &squot;%s&squot;, err = %d&bslash;n&quot;
comma
id|proc_stat
comma
op_minus
id|fd
)paren
suffix:semicolon
r_return
id|ARBITRARY_ADDR
suffix:semicolon
)brace
id|err
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
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
l_string|&quot;os_process_pc - couldn&squot;t read &squot;%s&squot;, err = %d&bslash;n&quot;
comma
id|proc_stat
comma
op_minus
id|err
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
id|ARBITRARY_ADDR
suffix:semicolon
)brace
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
id|pc
op_assign
id|ARBITRARY_ADDR
suffix:semicolon
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|buf
comma
l_string|&quot;%*d &quot;
id|COMM_SCANF
l_string|&quot; %*c %*d %*d %*d %*d %*d %*d %*d &quot;
l_string|&quot;%*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d &quot;
l_string|&quot;%*d %*d %*d %*d %*d %lu&quot;
comma
op_amp
id|pc
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;os_process_pc - couldn&squot;t find pc in &squot;%s&squot;&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
)brace
r_return
id|pc
suffix:semicolon
)brace
DECL|function|os_process_parent
r_int
id|os_process_parent
c_func
(paren
r_int
id|pid
)paren
(brace
r_char
id|stat
(braket
id|STAT_PATH_LEN
)braket
suffix:semicolon
r_char
id|data
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|parent
comma
id|n
comma
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
op_minus
l_int|1
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|snprintf
c_func
(paren
id|stat
comma
r_sizeof
(paren
id|stat
)paren
comma
l_string|&quot;/proc/%d/stat&quot;
comma
id|pid
)paren
suffix:semicolon
id|fd
op_assign
id|os_open_file
c_func
(paren
id|stat
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
l_string|&quot;Couldn&squot;t open &squot;%s&squot;, err = %d&bslash;n&quot;
comma
id|stat
comma
op_minus
id|fd
)paren
suffix:semicolon
r_return
id|FAILURE_PID
suffix:semicolon
)brace
id|n
op_assign
id|os_read_file
c_func
(paren
id|fd
comma
id|data
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Couldn&squot;t read &squot;%s&squot;, err = %d&bslash;n&quot;
comma
id|stat
comma
op_minus
id|n
)paren
suffix:semicolon
r_return
id|FAILURE_PID
suffix:semicolon
)brace
id|parent
op_assign
id|FAILURE_PID
suffix:semicolon
id|n
op_assign
id|sscanf
c_func
(paren
id|data
comma
l_string|&quot;%*d &quot;
id|COMM_SCANF
l_string|&quot; %*c %d&quot;
comma
op_amp
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to scan &squot;%s&squot;&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
)brace
r_return
id|parent
suffix:semicolon
)brace
DECL|function|os_stop_process
r_void
id|os_stop_process
c_func
(paren
r_int
id|pid
)paren
(brace
id|kill
c_func
(paren
id|pid
comma
id|SIGSTOP
)paren
suffix:semicolon
)brace
DECL|function|os_kill_process
r_void
id|os_kill_process
c_func
(paren
r_int
id|pid
comma
r_int
id|reap_child
)paren
(brace
id|kill
c_func
(paren
id|pid
comma
id|SIGKILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reap_child
)paren
(brace
id|CATCH_EINTR
c_func
(paren
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|os_kill_ptraced_process
r_void
id|os_kill_ptraced_process
c_func
(paren
r_int
id|pid
comma
r_int
id|reap_child
)paren
(brace
id|ptrace
c_func
(paren
id|PTRACE_KILL
comma
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reap_child
)paren
(brace
id|CATCH_EINTR
c_func
(paren
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|os_usr1_process
r_void
id|os_usr1_process
c_func
(paren
r_int
id|pid
)paren
(brace
id|kill
c_func
(paren
id|pid
comma
id|SIGUSR1
)paren
suffix:semicolon
)brace
multiline_comment|/*Don&squot;t use the glibc version, which caches the result in TLS. It misses some&n; * syscalls, and also breaks with clone(), which does not unshare the TLS.*/
DECL|function|_syscall0
r_inline
id|_syscall0
c_func
(paren
id|pid_t
comma
id|getpid
)paren
r_int
id|os_getpid
c_func
(paren
r_void
)paren
(brace
r_return
id|getpid
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|os_map_memory
r_int
id|os_map_memory
c_func
(paren
r_void
op_star
id|virt
comma
r_int
id|fd
comma
r_int
r_int
r_int
id|off
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
)paren
(brace
r_void
op_star
id|loc
suffix:semicolon
r_int
id|prot
suffix:semicolon
id|prot
op_assign
(paren
id|r
ques
c_cond
id|PROT_READ
suffix:colon
l_int|0
)paren
op_or
(paren
id|w
ques
c_cond
id|PROT_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|x
ques
c_cond
id|PROT_EXEC
suffix:colon
l_int|0
)paren
suffix:semicolon
id|loc
op_assign
id|mmap64
c_func
(paren
(paren
r_void
op_star
)paren
id|virt
comma
id|len
comma
id|prot
comma
id|MAP_SHARED
op_or
id|MAP_FIXED
comma
id|fd
comma
id|off
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loc
op_eq
id|MAP_FAILED
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_protect_memory
r_int
id|os_protect_memory
c_func
(paren
r_void
op_star
id|addr
comma
r_int
r_int
id|len
comma
r_int
id|r
comma
r_int
id|w
comma
r_int
id|x
)paren
(brace
r_int
id|prot
op_assign
(paren
(paren
id|r
ques
c_cond
id|PROT_READ
suffix:colon
l_int|0
)paren
op_or
(paren
id|w
ques
c_cond
id|PROT_WRITE
suffix:colon
l_int|0
)paren
op_or
(paren
id|x
ques
c_cond
id|PROT_EXEC
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mprotect
c_func
(paren
id|addr
comma
id|len
comma
id|prot
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|os_unmap_memory
r_int
id|os_unmap_memory
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|len
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|munmap
c_func
(paren
id|addr
comma
id|len
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
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
