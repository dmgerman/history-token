multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __USER_UTIL_H__
DECL|macro|__USER_UTIL_H__
mdefine_line|#define __USER_UTIL_H__
macro_line|#include &quot;sysdep/ptrace.h&quot;
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
DECL|enumerator|OP_NONE
DECL|enumerator|OP_EXEC
DECL|enumerator|OP_FORK
DECL|enumerator|OP_TRACE_ON
DECL|enumerator|OP_REBOOT
DECL|enumerator|OP_HALT
DECL|enumerator|OP_CB
r_enum
(brace
id|OP_NONE
comma
id|OP_EXEC
comma
id|OP_FORK
comma
id|OP_TRACE_ON
comma
id|OP_REBOOT
comma
id|OP_HALT
comma
id|OP_CB
)brace
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
r_int
id|tracing_pid
suffix:semicolon
r_extern
r_int
id|honeypot
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
r_int
id|gdb_pid
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
op_star
id|open_maps
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|close_maps
c_func
(paren
r_void
op_star
id|fd
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_brk
c_func
(paren
r_void
)paren
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
r_int
id|proc_start_thread
c_func
(paren
r_int
r_int
id|ip
comma
r_int
r_int
id|sp
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
r_void
id|abandon_proc_space
c_func
(paren
r_int
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
r_extern
r_int
id|signals
c_func
(paren
r_int
(paren
op_star
id|init_proc
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|sp
)paren
suffix:semicolon
r_extern
r_int
id|__personality
c_func
(paren
r_int
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
r_void
id|signal_init
c_func
(paren
r_void
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
r_void
id|trace_myself
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|get_profile_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_profile_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_timers
c_func
(paren
r_int
id|set_signal
)paren
suffix:semicolon
r_extern
r_int
id|clone_and_wait
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
id|sp
comma
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_int
id|input_loop
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|continue_execing_proc
c_func
(paren
r_int
id|pid
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
r_void
id|setup_input
c_func
(paren
r_void
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
id|save_signal_state
c_func
(paren
r_int
op_star
id|sig_ptr
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
id|raw
c_func
(paren
r_int
id|fd
comma
r_int
id|complain
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
id|idle_sleep
c_func
(paren
r_int
id|secs
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
id|init_new_thread
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
id|attach_process
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|calc_sigframe_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|fork_tramp
c_func
(paren
r_void
op_star
id|sig_stack
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
r_void
id|close_fd
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
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
id|tempname
comma
r_int
id|do_unlink
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
)paren
suffix:semicolon
r_extern
r_void
id|term_handler
c_func
(paren
r_int
id|sig
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
r_int
id|user_read
c_func
(paren
r_int
id|fd
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
id|user_write
c_func
(paren
r_int
id|fd
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
id|arch_handle_signal
c_func
(paren
r_int
id|sig
comma
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|user_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pid_pc
c_func
(paren
r_int
id|pid
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
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
