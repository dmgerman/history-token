multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __USER_UTIL_H__
DECL|macro|__USER_UTIL_H__
mdefine_line|#define __USER_UTIL_H__
macro_line|#include &quot;sysdep/ptrace.h&quot;
DECL|macro|CATCH_EINTR
mdefine_line|#define CATCH_EINTR(expr) while (((expr) &lt; 0) &amp;&amp; (errno == EINTR))
r_extern
r_int
id|mode_tt
suffix:semicolon
r_extern
r_int
id|grantpt
c_func
(paren
r_int
id|__fd
)paren
suffix:semicolon
r_extern
r_int
id|unlockpt
c_func
(paren
r_int
id|__fd
)paren
suffix:semicolon
r_extern
r_char
op_star
id|ptsname
c_func
(paren
r_int
id|__fd
)paren
suffix:semicolon
DECL|struct|cpu_task
r_struct
id|cpu_task
(brace
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|task
r_void
op_star
id|task
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|cpu_task
id|cpu_tasks
(braket
)braket
suffix:semicolon
DECL|struct|signal_info
r_struct
id|signal_info
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_union
id|uml_pt_regs
op_star
)paren
suffix:semicolon
DECL|member|is_irq
r_int
id|is_irq
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|signal_info
id|sig_info
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|low_physmem
suffix:semicolon
r_extern
r_int
r_int
id|high_physmem
suffix:semicolon
r_extern
r_int
r_int
id|uml_physmem
suffix:semicolon
r_extern
r_int
r_int
id|uml_reserved
suffix:semicolon
r_extern
r_int
r_int
id|end_vm
suffix:semicolon
r_extern
r_int
r_int
id|start_vm
suffix:semicolon
r_extern
r_int
r_int
id|highmem
suffix:semicolon
r_extern
r_char
id|host_info
(braket
)braket
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
r_extern
r_char
id|command_line
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|tempdir
suffix:semicolon
r_extern
r_int
r_int
id|_stext
comma
id|_etext
comma
id|_sdata
comma
id|_edata
comma
id|__bss_start
comma
id|_end
suffix:semicolon
r_extern
r_int
r_int
id|_unprotected_end
suffix:semicolon
r_extern
r_int
r_int
id|brk_start
suffix:semicolon
r_extern
r_int
id|pty_output_sigio
suffix:semicolon
r_extern
r_int
id|pty_close_sigio
suffix:semicolon
r_extern
r_void
id|stop
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|stack_protections
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
id|task_protections
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_int
id|wait_for_stop
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
comma
r_int
id|cont_type
comma
r_void
op_star
id|relay
)paren
suffix:semicolon
r_extern
r_void
op_star
id|add_signal_handler
c_func
(paren
r_int
id|sig
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
)paren
)paren
suffix:semicolon
r_extern
r_int
id|start_fork_tramp
c_func
(paren
r_void
op_star
id|arg
comma
r_int
r_int
id|temp_stack
comma
r_int
id|clone_flags
comma
r_int
(paren
op_star
id|tramp
)paren
(paren
r_void
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|linux_main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
suffix:semicolon
r_extern
r_void
id|set_cmdline
c_func
(paren
r_char
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_void
id|input_cb
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
id|arg_len
)paren
suffix:semicolon
r_extern
r_int
id|get_pty
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|um_kmalloc
c_func
(paren
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|switcheroo
c_func
(paren
r_int
id|fd
comma
r_int
id|prot
comma
r_void
op_star
id|from
comma
r_void
op_star
id|to
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|setup_machinename
c_func
(paren
r_char
op_star
id|machine_out
)paren
suffix:semicolon
r_extern
r_void
id|setup_hostinfo
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|add_arg
c_func
(paren
r_char
op_star
id|cmd_line
comma
r_char
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|init_new_thread_stack
c_func
(paren
r_void
op_star
id|sig_stack
comma
r_void
(paren
op_star
id|usr1_handler
)paren
(paren
r_int
)paren
)paren
suffix:semicolon
r_extern
r_void
id|init_new_thread_signals
c_func
(paren
r_int
id|altstack
)paren
suffix:semicolon
r_extern
r_void
id|do_exec
c_func
(paren
r_int
id|old_pid
comma
r_int
id|new_pid
)paren
suffix:semicolon
r_extern
r_void
id|tracer_panic
c_func
(paren
r_char
op_star
id|msg
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_char
op_star
id|get_umid
c_func
(paren
r_int
id|only_if_set
)paren
suffix:semicolon
r_extern
r_void
id|do_longjmp
c_func
(paren
r_void
op_star
id|p
comma
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|suspend_new_thread
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_int
id|detach
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_int
id|attach
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|kill_child_dead
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_int
id|cont
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|check_ptrace
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|check_sigio
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|run_kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_void
op_star
op_star
id|jmp_ptr
)paren
suffix:semicolon
r_extern
r_void
id|write_sigio_workaround
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|arch_check_bugs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpu_feature
c_func
(paren
r_char
op_star
id|what
comma
r_char
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|arch_handle_signal
c_func
(paren
r_int
id|sig
comma
r_union
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|arch_fixup
c_func
(paren
r_int
r_int
id|address
comma
r_void
op_star
id|sc_ptr
)paren
suffix:semicolon
r_extern
r_void
id|forward_pending_sigio
c_func
(paren
r_int
id|target
)paren
suffix:semicolon
r_extern
r_int
id|can_do_skas
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|arch_init_thread
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|setjmp_wrapper
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
comma
r_void
op_star
)paren
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|raw
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
