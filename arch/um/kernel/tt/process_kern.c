multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/signal.h&quot;
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/ptrace.h&quot;
macro_line|#include &quot;asm/system.h&quot;
macro_line|#include &quot;asm/pgalloc.h&quot;
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/tlbflush.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;tlb.h&quot;
macro_line|#include &quot;mode.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;tt.h&quot;
DECL|function|switch_to_tt
r_void
op_star
id|switch_to_tt
c_func
(paren
r_void
op_star
id|prev
comma
r_void
op_star
id|next
comma
r_void
op_star
id|last
)paren
(brace
r_struct
id|task_struct
op_star
id|from
comma
op_star
id|to
comma
op_star
id|prev_sched
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
comma
id|vtalrm
comma
id|alrm
comma
id|prof
comma
id|cpu
suffix:semicolon
r_char
id|c
suffix:semicolon
multiline_comment|/* jailing and SMP are incompatible, so this doesn&squot;t need to be &n;&t; * made per-cpu &n;&t; */
r_static
r_int
id|reading
suffix:semicolon
id|from
op_assign
id|prev
suffix:semicolon
id|to
op_assign
id|next
suffix:semicolon
id|to-&gt;thread.prev_sched
op_assign
id|from
suffix:semicolon
id|cpu
op_assign
id|from-&gt;thread_info-&gt;cpu
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
l_int|0
)paren
(brace
id|forward_interrupts
c_func
(paren
id|to-&gt;thread.mode.tt.extern_pid
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
id|forward_ipi
c_func
(paren
id|cpu_data
(braket
id|cpu
)braket
dot
id|ipi_pipe
(braket
l_int|0
)braket
comma
id|to-&gt;thread.mode.tt.extern_pid
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|vtalrm
op_assign
id|change_sig
c_func
(paren
id|SIGVTALRM
comma
l_int|0
)paren
suffix:semicolon
id|alrm
op_assign
id|change_sig
c_func
(paren
id|SIGALRM
comma
l_int|0
)paren
suffix:semicolon
id|prof
op_assign
id|change_sig
c_func
(paren
id|SIGPROF
comma
l_int|0
)paren
suffix:semicolon
id|forward_pending_sigio
c_func
(paren
id|to-&gt;thread.mode.tt.extern_pid
)paren
suffix:semicolon
id|c
op_assign
l_int|0
suffix:semicolon
id|set_current
c_func
(paren
id|to
)paren
suffix:semicolon
id|reading
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
id|os_write_file
c_func
(paren
id|to-&gt;thread.mode.tt.switch_pipe
(braket
l_int|1
)braket
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;write of switch_pipe failed, err = %d&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
id|reading
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|from-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
op_logical_or
(paren
id|from-&gt;state
op_eq
id|TASK_DEAD
)paren
)paren
(brace
id|os_kill_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
id|err
op_assign
id|os_read_file
c_func
(paren
id|from-&gt;thread.mode.tt.switch_pipe
(braket
l_int|0
)braket
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;read of switch_pipe failed, errno = %d&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/* If the process that we have just scheduled away from has exited,&n;&t; * then it needs to be killed here.  The reason is that, even though&n;&t; * it will kill itself when it next runs, that may be too late.  Its&n;&t; * stack will be freed, possibly before then, and if that happens,&n;&t; * we have a use-after-free situation.  So, it gets killed here&n;&t; * in case it has not already killed itself.&n;&t; */
id|prev_sched
op_assign
id|current-&gt;thread.prev_sched
suffix:semicolon
r_if
c_cond
(paren
(paren
id|prev_sched-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
op_logical_or
(paren
id|prev_sched-&gt;state
op_eq
id|TASK_DEAD
)paren
)paren
(brace
id|os_kill_process
c_func
(paren
id|prev_sched-&gt;thread.mode.tt.extern_pid
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* This works around a nasty race with &squot;jail&squot;.  If we are switching&n;&t; * between two threads of a threaded app and the incoming process &n;&t; * runs before the outgoing process reaches the read, and it makes&n;&t; * it all the way out to userspace, then it will have write-protected &n;&t; * the outgoing process stack.  Then, when the outgoing process &n;&t; * returns from the write, it will segfault because it can no longer&n;&t; * write its own stack.  So, in order to avoid that, the incoming &n;&t; * thread sits in a loop yielding until &squot;reading&squot; is set.  This &n;&t; * isn&squot;t entirely safe, since there may be a reschedule from a timer&n;&t; * happening between setting &squot;reading&squot; and sleeping in read.  But,&n;&t; * it should get a whole quantum in which to reach the read and sleep,&n;&t; * which should be enough.&n;&t; */
r_if
c_cond
(paren
id|jail
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|reading
)paren
(brace
id|sched_yield
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
id|change_sig
c_func
(paren
id|SIGVTALRM
comma
id|vtalrm
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGALRM
comma
id|alrm
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGPROF
comma
id|prof
)paren
suffix:semicolon
id|arch_switch
c_func
(paren
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|current-&gt;thread.prev_sched
suffix:semicolon
)brace
DECL|function|release_thread_tt
r_void
id|release_thread_tt
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_int
id|pid
op_assign
id|task-&gt;thread.mode.tt.extern_pid
suffix:semicolon
r_if
c_cond
(paren
id|os_getpid
c_func
(paren
)paren
op_ne
id|pid
)paren
(brace
id|os_kill_process
c_func
(paren
id|pid
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|exit_thread_tt
r_void
id|exit_thread_tt
c_func
(paren
r_void
)paren
(brace
id|os_close_file
c_func
(paren
id|current-&gt;thread.mode.tt.switch_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|os_close_file
c_func
(paren
id|current-&gt;thread.mode.tt.switch_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
r_void
id|schedule_tail
c_func
(paren
id|task_t
op_star
id|prev
)paren
suffix:semicolon
DECL|function|new_thread_handler
r_static
r_void
id|new_thread_handler
c_func
(paren
r_int
id|sig
)paren
(brace
r_int
r_int
id|disable
suffix:semicolon
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
op_star
id|arg
suffix:semicolon
id|fn
op_assign
id|current-&gt;thread.request.u.thread.proc
suffix:semicolon
id|arg
op_assign
id|current-&gt;thread.request.u.thread.arg
suffix:semicolon
id|UPT_SC
c_func
(paren
op_amp
id|current-&gt;thread.regs.regs
)paren
op_assign
(paren
r_void
op_star
)paren
(paren
op_amp
id|sig
op_plus
l_int|1
)paren
suffix:semicolon
id|disable
op_assign
(paren
l_int|1
op_lshift
(paren
id|SIGVTALRM
op_minus
l_int|1
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
id|SIGALRM
op_minus
l_int|1
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
id|SIGIO
op_minus
l_int|1
)paren
)paren
op_or
(paren
l_int|1
op_lshift
(paren
id|SIGPROF
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|SC_SIGMASK
c_func
(paren
id|UPT_SC
c_func
(paren
op_amp
id|current-&gt;thread.regs.regs
)paren
)paren
op_and_assign
op_complement
id|disable
suffix:semicolon
id|suspend_new_thread
c_func
(paren
id|current-&gt;thread.mode.tt.switch_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|force_flush_all
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;thread.prev_sched
op_ne
l_int|NULL
)paren
(brace
id|schedule_tail
c_func
(paren
id|current-&gt;thread.prev_sched
)paren
suffix:semicolon
)brace
id|current-&gt;thread.prev_sched
op_assign
l_int|NULL
suffix:semicolon
id|init_new_thread_signals
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|enable_timer
c_func
(paren
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|current-&gt;thread.temp_stack
)paren
suffix:semicolon
id|set_cmdline
c_func
(paren
l_string|&quot;(kernel thread)&quot;
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGUSR1
comma
l_int|1
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGVTALRM
comma
l_int|1
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGPROF
comma
l_int|1
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|run_kernel_thread
c_func
(paren
id|fn
comma
id|arg
comma
op_amp
id|current-&gt;thread.exec_buf
)paren
)paren
(brace
id|do_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|new_thread_proc
r_static
r_int
id|new_thread_proc
c_func
(paren
r_void
op_star
id|stack
)paren
(brace
multiline_comment|/* local_irq_disable is needed to block out signals until this thread is&n;&t; * properly scheduled.  Otherwise, the tracing thread will get mighty&n;&t; * upset about any signals that arrive before that.&n;&t; * This has the complication that it sets the saved signal mask in&n;&t; * the sigcontext to block signals.  This gets restored when this&n;&t; * thread (or a descendant, since they get a copy of this sigcontext)&n;&t; * returns to userspace.&n;&t; * So, this is compensated for elsewhere.&n;&t; * XXX There is still a small window until local_irq_disable() actually&n;&t; * finishes where signals are possible - shouldn&squot;t be a problem in&n;&t; * practice since SIGIO hasn&squot;t been forwarded here yet, and the&n;&t; * local_irq_disable should finish before a SIGVTALRM has time to be&n;&t; * delivered.&n;&t; */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|init_new_thread_stack
c_func
(paren
id|stack
comma
id|new_thread_handler
)paren
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Signal masking - signals are blocked at the start of fork_tramp.  They&n; * are re-enabled when finish_fork_handler is entered by fork_tramp hitting&n; * itself with a SIGUSR1.  set_user_mode has to be run with SIGUSR1 off,&n; * so it is blocked before it&squot;s called.  They are re-enabled on sigreturn&n; * despite the fact that they were blocked when the SIGUSR1 was issued because&n; * copy_thread copies the parent&squot;s sigcontext, including the signal mask&n; * onto the signal frame.&n; */
DECL|function|finish_fork_handler
r_void
id|finish_fork_handler
c_func
(paren
r_int
id|sig
)paren
(brace
id|UPT_SC
c_func
(paren
op_amp
id|current-&gt;thread.regs.regs
)paren
op_assign
(paren
r_void
op_star
)paren
(paren
op_amp
id|sig
op_plus
l_int|1
)paren
suffix:semicolon
id|suspend_new_thread
c_func
(paren
id|current-&gt;thread.mode.tt.switch_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|force_flush_all
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;thread.prev_sched
op_ne
l_int|NULL
)paren
(brace
id|schedule_tail
c_func
(paren
id|current-&gt;thread.prev_sched
)paren
suffix:semicolon
)brace
id|current-&gt;thread.prev_sched
op_assign
l_int|NULL
suffix:semicolon
id|enable_timer
c_func
(paren
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGVTALRM
comma
l_int|1
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm
op_ne
id|current-&gt;parent-&gt;mm
)paren
(brace
id|protect_memory
c_func
(paren
id|uml_reserved
comma
id|high_physmem
op_minus
id|uml_reserved
comma
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
id|task_protections
c_func
(paren
(paren
r_int
r_int
)paren
id|current_thread
)paren
suffix:semicolon
id|free_page
c_func
(paren
id|current-&gt;thread.temp_stack
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGUSR1
comma
l_int|0
)paren
suffix:semicolon
id|set_user_mode
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
DECL|function|fork_tramp
r_int
id|fork_tramp
c_func
(paren
r_void
op_star
id|stack
)paren
(brace
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|arch_init_thread
c_func
(paren
)paren
suffix:semicolon
id|init_new_thread_stack
c_func
(paren
id|stack
comma
id|finish_fork_handler
)paren
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_thread_tt
r_int
id|copy_thread_tt
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|sp
comma
r_int
r_int
id|stack_top
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
(paren
op_star
id|tramp
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
r_int
id|new_pid
comma
id|err
suffix:semicolon
r_int
r_int
id|stack
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;thread.forking
)paren
(brace
id|tramp
op_assign
id|fork_tramp
suffix:semicolon
)brace
r_else
(brace
id|tramp
op_assign
id|new_thread_proc
suffix:semicolon
id|p-&gt;thread.request.u.thread
op_assign
id|current-&gt;thread.request.u.thread
suffix:semicolon
)brace
id|err
op_assign
id|os_pipe
c_func
(paren
id|p-&gt;thread.mode.tt.switch_pipe
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
l_string|&quot;copy_thread : pipe failed, err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|stack
op_assign
id|alloc_stack
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stack
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;copy_thread : failed to allocate &quot;
l_string|&quot;temporary stack&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|clone_flags
op_and_assign
id|CLONE_VM
suffix:semicolon
id|p-&gt;thread.temp_stack
op_assign
id|stack
suffix:semicolon
id|new_pid
op_assign
id|start_fork_tramp
c_func
(paren
id|p-&gt;thread_info
comma
id|stack
comma
id|clone_flags
comma
id|tramp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;copy_thread : clone failed - errno = %d&bslash;n&quot;
comma
op_minus
id|new_pid
)paren
suffix:semicolon
r_return
id|new_pid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|current-&gt;thread.forking
)paren
(brace
id|sc_to_sc
c_func
(paren
id|UPT_SC
c_func
(paren
op_amp
id|p-&gt;thread.regs.regs
)paren
comma
id|UPT_SC
c_func
(paren
op_amp
id|current-&gt;thread.regs.regs
)paren
)paren
suffix:semicolon
id|SC_SET_SYSCALL_RETURN
c_func
(paren
id|UPT_SC
c_func
(paren
op_amp
id|p-&gt;thread.regs.regs
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_ne
l_int|0
)paren
(brace
id|SC_SP
c_func
(paren
id|UPT_SC
c_func
(paren
op_amp
id|p-&gt;thread.regs.regs
)paren
)paren
op_assign
id|sp
suffix:semicolon
)brace
)brace
id|p-&gt;thread.mode.tt.extern_pid
op_assign
id|new_pid
suffix:semicolon
id|current-&gt;thread.request.op
op_assign
id|OP_FORK
suffix:semicolon
id|current-&gt;thread.request.u.fork.pid
op_assign
id|new_pid
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|reboot_tt
r_void
id|reboot_tt
c_func
(paren
r_void
)paren
(brace
id|current-&gt;thread.request.op
op_assign
id|OP_REBOOT
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|halt_tt
r_void
id|halt_tt
c_func
(paren
r_void
)paren
(brace
id|current-&gt;thread.request.op
op_assign
id|OP_HALT
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|kill_off_processes_tt
r_void
id|kill_off_processes_tt
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
id|p-&gt;thread.mode.tt.extern_pid
op_ne
id|me
)paren
(brace
id|os_kill_process
c_func
(paren
id|p-&gt;thread.mode.tt.extern_pid
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)def_block
r_if
c_cond
(paren
id|init_task.thread.mode.tt.extern_pid
op_ne
id|me
)paren
(brace
id|os_kill_process
c_func
(paren
id|init_task.thread.mode.tt.extern_pid
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|initial_thread_cb_tt
r_void
id|initial_thread_cb_tt
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
)paren
(brace
r_if
c_cond
(paren
id|os_getpid
c_func
(paren
)paren
op_eq
id|tracing_pid
)paren
(brace
(paren
op_star
id|proc
)paren
(paren
id|arg
)paren
suffix:semicolon
)brace
r_else
(brace
id|current-&gt;thread.request.op
op_assign
id|OP_CB
suffix:semicolon
id|current-&gt;thread.request.u.cb.proc
op_assign
id|proc
suffix:semicolon
id|current-&gt;thread.request.u.cb.arg
op_assign
id|arg
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|do_proc_op
r_int
id|do_proc_op
c_func
(paren
r_void
op_star
id|t
comma
r_int
id|proc_id
)paren
(brace
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
r_struct
id|thread_struct
op_star
id|thread
suffix:semicolon
r_int
id|op
comma
id|pid
suffix:semicolon
id|task
op_assign
id|t
suffix:semicolon
id|thread
op_assign
op_amp
id|task-&gt;thread
suffix:semicolon
id|op
op_assign
id|thread-&gt;request.op
suffix:semicolon
r_switch
c_cond
(paren
id|op
)paren
(brace
r_case
id|OP_NONE
suffix:colon
r_case
id|OP_TRACE_ON
suffix:colon
r_break
suffix:semicolon
r_case
id|OP_EXEC
suffix:colon
id|pid
op_assign
id|thread-&gt;request.u.exec.pid
suffix:semicolon
id|do_exec
c_func
(paren
id|thread-&gt;mode.tt.extern_pid
comma
id|pid
)paren
suffix:semicolon
id|thread-&gt;mode.tt.extern_pid
op_assign
id|pid
suffix:semicolon
id|cpu_tasks
(braket
id|task-&gt;thread_info-&gt;cpu
)braket
dot
id|pid
op_assign
id|pid
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_FORK
suffix:colon
id|attach_process
c_func
(paren
id|thread-&gt;request.u.fork.pid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_CB
suffix:colon
(paren
op_star
id|thread-&gt;request.u.cb.proc
)paren
(paren
id|thread-&gt;request.u.cb.arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_REBOOT
suffix:colon
r_case
id|OP_HALT
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|tracer_panic
c_func
(paren
l_string|&quot;Bad op in do_proc_op&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|thread-&gt;request.op
op_assign
id|OP_NONE
suffix:semicolon
r_return
id|op
suffix:semicolon
)brace
DECL|function|init_idle_tt
r_void
id|init_idle_tt
c_func
(paren
r_void
)paren
(brace
id|default_idle
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Changed by jail_setup, which is a setup */
DECL|variable|jail
r_int
id|jail
op_assign
l_int|0
suffix:semicolon
DECL|function|jail_setup
r_int
id|__init
id|jail_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
r_int
id|ok
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|jail
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
id|printf
c_func
(paren
l_string|&quot;&squot;jail&squot; may not used used in a kernel with CONFIG_SMP &quot;
l_string|&quot;enabled&bslash;n&quot;
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HOSTFS
id|printf
c_func
(paren
l_string|&quot;&squot;jail&squot; may not used used in a kernel with CONFIG_HOSTFS &quot;
l_string|&quot;enabled&bslash;n&quot;
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MODULES
id|printf
c_func
(paren
l_string|&quot;&squot;jail&squot; may not used used in a kernel with CONFIG_MODULES &quot;
l_string|&quot;enabled&bslash;n&quot;
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
macro_line|#endif&t;
r_if
c_cond
(paren
op_logical_neg
id|ok
)paren
(brace
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* CAP_SYS_RAWIO controls the ability to open /dev/mem and /dev/kmem.&n;&t; * Removing it from the bounding set eliminates the ability of anything&n;&t; * to acquire it, and thus read or write kernel memory.&n;&t; */
id|cap_lower
c_func
(paren
id|cap_bset
comma
id|CAP_SYS_RAWIO
)paren
suffix:semicolon
id|jail
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;jail&quot;
comma
id|jail_setup
comma
l_string|&quot;jail&bslash;n&quot;
l_string|&quot;    Enables the protection of kernel memory from processes.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|mprotect_kernel_mem
r_static
r_void
id|mprotect_kernel_mem
c_func
(paren
r_int
id|w
)paren
(brace
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_int
id|pages
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|jail
op_logical_or
(paren
id|current
op_eq
op_amp
id|init_task
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|pages
op_assign
(paren
l_int|1
op_lshift
id|CONFIG_KERNEL_STACK_ORDER
)paren
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
id|current_thread
op_plus
id|PAGE_SIZE
suffix:semicolon
id|end
op_assign
(paren
r_int
r_int
)paren
id|current_thread
op_plus
id|PAGE_SIZE
op_star
id|pages
suffix:semicolon
id|protect_memory
c_func
(paren
id|uml_reserved
comma
id|start
op_minus
id|uml_reserved
comma
l_int|1
comma
id|w
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|protect_memory
c_func
(paren
id|end
comma
id|high_physmem
op_minus
id|end
comma
l_int|1
comma
id|w
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
id|UML_ROUND_DOWN
c_func
(paren
op_amp
id|_stext
)paren
suffix:semicolon
id|end
op_assign
(paren
r_int
r_int
)paren
id|UML_ROUND_UP
c_func
(paren
op_amp
id|_etext
)paren
suffix:semicolon
id|protect_memory
c_func
(paren
id|start
comma
id|end
op_minus
id|start
comma
l_int|1
comma
id|w
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
id|UML_ROUND_DOWN
c_func
(paren
op_amp
id|_unprotected_end
)paren
suffix:semicolon
id|end
op_assign
(paren
r_int
r_int
)paren
id|UML_ROUND_UP
c_func
(paren
op_amp
id|_edata
)paren
suffix:semicolon
id|protect_memory
c_func
(paren
id|start
comma
id|end
op_minus
id|start
comma
l_int|1
comma
id|w
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|start
op_assign
(paren
r_int
r_int
)paren
id|UML_ROUND_DOWN
c_func
(paren
op_amp
id|__bss_start
)paren
suffix:semicolon
id|end
op_assign
(paren
r_int
r_int
)paren
id|UML_ROUND_UP
c_func
(paren
id|brk_start
)paren
suffix:semicolon
id|protect_memory
c_func
(paren
id|start
comma
id|end
op_minus
id|start
comma
l_int|1
comma
id|w
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|mprotect_kernel_vm
c_func
(paren
id|w
)paren
suffix:semicolon
)brace
DECL|function|unprotect_kernel_mem
r_void
id|unprotect_kernel_mem
c_func
(paren
r_void
)paren
(brace
id|mprotect_kernel_mem
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|protect_kernel_mem
r_void
id|protect_kernel_mem
c_func
(paren
r_void
)paren
(brace
id|mprotect_kernel_mem
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_void
id|start_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|start_kernel_proc
r_static
r_int
id|start_kernel_proc
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|pid
suffix:semicolon
id|block_signals
c_func
(paren
)paren
suffix:semicolon
id|pid
op_assign
id|os_getpid
c_func
(paren
)paren
suffix:semicolon
id|cpu_tasks
(braket
l_int|0
)braket
dot
id|pid
op_assign
id|pid
suffix:semicolon
id|cpu_tasks
(braket
l_int|0
)braket
dot
id|task
op_assign
id|current
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|cpu_online_map
op_assign
id|cpumask_of_cpu
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|debug
)paren
(brace
id|os_stop_process
c_func
(paren
id|pid
)paren
suffix:semicolon
)brace
id|start_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_tracing
r_void
id|set_tracing
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|tracing
)paren
(brace
(paren
(paren
r_struct
id|task_struct
op_star
)paren
id|task
)paren
op_member_access_from_pointer
id|thread.mode.tt.tracing
op_assign
id|tracing
suffix:semicolon
)brace
DECL|function|is_tracing
r_int
id|is_tracing
c_func
(paren
r_void
op_star
id|t
)paren
(brace
r_return
(paren
(paren
(paren
r_struct
id|task_struct
op_star
)paren
id|t
)paren
op_member_access_from_pointer
id|thread.mode.tt.tracing
)paren
suffix:semicolon
)brace
DECL|function|set_user_mode
r_int
id|set_user_mode
c_func
(paren
r_void
op_star
id|t
)paren
(brace
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
id|task
op_assign
id|t
ques
c_cond
id|t
suffix:colon
id|current
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;thread.mode.tt.tracing
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|task-&gt;thread.request.op
op_assign
id|OP_TRACE_ON
suffix:semicolon
id|os_usr1_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_init_pid
r_void
id|set_init_pid
c_func
(paren
r_int
id|pid
)paren
(brace
r_int
id|err
suffix:semicolon
id|init_task.thread.mode.tt.extern_pid
op_assign
id|pid
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|init_task.thread.mode.tt.switch_pipe
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
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Can&squot;t create switch pipe for init_task, errno = %d&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
)brace
DECL|function|singlestepping_tt
r_int
id|singlestepping_tt
c_func
(paren
r_void
op_star
id|t
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|t
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;thread.mode.tt.singlestep_syscall
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|task-&gt;ptrace
op_amp
id|PT_DTRACE
suffix:semicolon
)brace
DECL|function|clear_singlestep
r_void
id|clear_singlestep
c_func
(paren
r_void
op_star
id|t
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|t
suffix:semicolon
id|task-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
)brace
DECL|function|start_uml_tt
r_int
id|start_uml_tt
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|sp
suffix:semicolon
r_int
id|pages
suffix:semicolon
id|pages
op_assign
(paren
l_int|1
op_lshift
id|CONFIG_KERNEL_STACK_ORDER
)paren
suffix:semicolon
id|sp
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|init_task.thread_info
)paren
op_plus
id|pages
op_star
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_return
id|tracer
c_func
(paren
id|start_kernel_proc
comma
id|sp
)paren
suffix:semicolon
)brace
DECL|function|external_pid_tt
r_int
id|external_pid_tt
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_return
id|task-&gt;thread.mode.tt.extern_pid
suffix:semicolon
)brace
DECL|function|thread_pid_tt
r_int
id|thread_pid_tt
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_return
id|task-&gt;thread.mode.tt.extern_pid
suffix:semicolon
)brace
DECL|function|is_valid_pid
r_int
id|is_valid_pid
c_func
(paren
r_int
id|pid
)paren
(brace
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
(def_block
id|for_each_process
c_func
(paren
id|task
)paren
(brace
r_if
c_cond
(paren
id|task-&gt;thread.mode.tt.extern_pid
op_eq
id|pid
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
)def_block
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
