multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/interrupt.h&quot;
macro_line|#include &quot;linux/mm.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/utsname.h&quot;
macro_line|#include &quot;linux/fs.h&quot;
macro_line|#include &quot;linux/utime.h&quot;
macro_line|#include &quot;linux/smp_lock.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;linux/init.h&quot;
macro_line|#include &quot;linux/capability.h&quot;
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;asm/mman.h&quot;
macro_line|#include &quot;asm/segment.h&quot;
macro_line|#include &quot;asm/stat.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;asm/processor.h&quot;
macro_line|#include &quot;asm/tlbflush.h&quot;
macro_line|#include &quot;asm/spinlock.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;signal_kern.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;tlb.h&quot;
macro_line|#include &quot;frame_kern.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
macro_line|#include &quot;2_5compat.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|variable|cpu_tasks
r_struct
id|cpu_task
id|cpu_tasks
(braket
id|NR_CPUS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NR_CPUS
op_minus
l_int|1
)braket
op_assign
(brace
op_minus
l_int|1
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|get_task
r_struct
id|task_struct
op_star
id|get_task
c_func
(paren
r_int
id|pid
comma
r_int
id|require
)paren
(brace
r_struct
id|task_struct
op_star
id|task
comma
op_star
id|ret
suffix:semicolon
id|ret
op_assign
l_int|NULL
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
id|task-&gt;pid
op_eq
id|pid
)paren
(brace
id|ret
op_assign
id|task
suffix:semicolon
r_break
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
r_if
c_cond
(paren
id|require
op_logical_and
(paren
id|ret
op_eq
l_int|NULL
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;get_task couldn&squot;t find a task&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
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
id|task-&gt;thread.extern_pid
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
DECL|function|external_pid
r_int
id|external_pid
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
ques
c_cond
id|t
suffix:colon
id|current
suffix:semicolon
r_return
id|task-&gt;thread.extern_pid
suffix:semicolon
)brace
DECL|function|pid_to_processor_id
r_int
id|pid_to_processor_id
c_func
(paren
r_int
id|pid
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_online_cpus
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_tasks
(braket
id|i
)braket
dot
id|pid
op_eq
id|pid
)paren
(brace
r_return
id|i
suffix:semicolon
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|free_stack
r_void
id|free_stack
c_func
(paren
r_int
r_int
id|stack
comma
r_int
id|order
)paren
(brace
id|free_pages
c_func
(paren
id|stack
comma
id|order
)paren
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
id|init_task.thread.extern_pid
op_assign
id|pid
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|init_task.thread.switch_pipe
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
id|err
)paren
suffix:semicolon
)brace
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
id|task-&gt;thread.tracing
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
id|thread.tracing
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
id|thread.tracing
)paren
suffix:semicolon
)brace
DECL|function|alloc_stack
r_int
r_int
id|alloc_stack
c_func
(paren
r_int
id|order
comma
r_int
id|atomic
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
r_int
id|flags
op_assign
id|GFP_KERNEL
suffix:semicolon
r_if
c_cond
(paren
id|atomic
)paren
(brace
id|flags
op_or_assign
id|GFP_ATOMIC
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|page
op_assign
id|__get_free_pages
c_func
(paren
id|flags
comma
id|order
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|stack_protections
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
r_extern
r_void
id|schedule_tail
c_func
(paren
r_struct
id|task_struct
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
id|current-&gt;thread.regs.regs.sc
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
id|current-&gt;thread.switch_pipe
(braket
l_int|0
)braket
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
id|force_flush_all
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;thread.prev_sched
op_assign
l_int|NULL
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGUSR1
comma
l_int|1
)paren
suffix:semicolon
id|unblock_signals
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
id|current-&gt;thread.jmp
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
id|block_signals
c_func
(paren
)paren
suffix:semicolon
id|init_new_thread
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
DECL|function|kernel_thread
r_int
id|kernel_thread
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
r_int
r_int
id|flags
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|current-&gt;thread.request.u.thread.proc
op_assign
id|fn
suffix:semicolon
id|current-&gt;thread.request.u.thread.arg
op_assign
id|arg
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|CLONE_VM
op_or
id|flags
comma
l_int|0
comma
l_int|NULL
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|p
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;do_fork failed in kernel_thread&quot;
)paren
suffix:semicolon
)brace
r_return
id|p-&gt;pid
suffix:semicolon
)brace
DECL|function|switch_mm
r_void
id|switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|prev
op_ne
id|next
)paren
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|prev-&gt;cpu_vm_mask
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|cpu
comma
op_amp
id|next-&gt;cpu_vm_mask
)paren
suffix:semicolon
)brace
DECL|function|set_current
r_void
id|set_current
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
id|cpu_tasks
(braket
id|task-&gt;thread_info-&gt;cpu
)braket
op_assign
(paren
(paren
r_struct
id|cpu_task
)paren
(brace
id|task-&gt;thread.extern_pid
comma
id|task
)brace
)paren
suffix:semicolon
)brace
DECL|function|switch_to
r_void
op_star
id|switch_to
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
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|vtalrm
comma
id|alrm
comma
id|prof
comma
id|err
comma
id|cpu
suffix:semicolon
r_char
id|c
suffix:semicolon
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
id|to-&gt;thread.extern_pid
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
id|to-&gt;thread.extern_pid
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
id|to-&gt;thread.extern_pid
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
id|user_write
c_func
(paren
id|to-&gt;thread.switch_pipe
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
l_string|&quot;write of switch_pipe failed, errno = %d&quot;
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
id|from-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
(brace
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
id|err
op_assign
id|user_read
c_func
(paren
id|from-&gt;thread.switch_pipe
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
DECL|function|interrupt_end
r_void
id|interrupt_end
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_tsk_thread_flag
c_func
(paren
id|current
comma
id|TIF_SIGPENDING
)paren
)paren
(brace
id|do_signal
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|release_thread
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
id|os_kill_process
c_func
(paren
id|task-&gt;thread.extern_pid
)paren
suffix:semicolon
)brace
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
id|close
c_func
(paren
id|current-&gt;thread.switch_pipe
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|close
c_func
(paren
id|current-&gt;thread.switch_pipe
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|unprotect_stack
c_func
(paren
(paren
r_int
r_int
)paren
id|current-&gt;thread_info
)paren
suffix:semicolon
)brace
multiline_comment|/* Signal masking - signals are blocked at the start of fork_tramp.  They&n; * are re-enabled when finish_fork_handler is entered by fork_tramp hitting&n; * itself with a SIGUSR1.  set_user_mode has to be run with SIGUSR1 off,&n; * so it is blocked before it&squot;s called.  They are re-enabled on sigreturn&n; * despite the fact that they were blocked when the SIGUSR1 was issued because&n; * copy_thread copies the parent&squot;s signcontext, including the signal mask&n; * onto the signal frame.&n; */
r_extern
r_int
id|hit_me
suffix:semicolon
DECL|function|finish_fork_handler
r_void
id|finish_fork_handler
c_func
(paren
r_int
id|sig
)paren
(brace
id|current-&gt;thread.regs.regs.sc
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
id|current-&gt;thread.switch_pipe
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
id|current-&gt;mm
op_ne
id|current-&gt;parent-&gt;mm
)paren
(brace
id|protect
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
id|current-&gt;thread_info
)paren
suffix:semicolon
id|current-&gt;thread.prev_sched
op_assign
l_int|NULL
suffix:semicolon
id|free_page
c_func
(paren
id|current-&gt;thread.temp_stack
)paren
suffix:semicolon
id|block_signals
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
DECL|function|get_current
r_void
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_return
id|current
suffix:semicolon
)brace
multiline_comment|/* This sigusr1 business works around a bug in gcc&squot;s -pg support.  &n; * Normally a procedure&squot;s mcount call comes after esp has been copied to &n; * ebp and the new frame is constructed.  With procedures with no locals,&n; * the mcount comes before, as the first thing that the procedure does.&n; * When that procedure is main for a thread, ebp comes in as NULL.  So,&n; * when mcount dereferences it, it segfaults.  So, UML works around this&n; * by adding a non-optimizable local to the various trampolines, fork_tramp&n; * and outer_tramp below, and exec_tramp.&n; */
DECL|variable|sigusr1
r_static
r_int
id|sigusr1
op_assign
id|SIGUSR1
suffix:semicolon
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
r_int
id|sig
op_assign
id|sigusr1
suffix:semicolon
id|block_signals
c_func
(paren
)paren
suffix:semicolon
id|init_new_thread
c_func
(paren
id|stack
comma
id|finish_fork_handler
)paren
suffix:semicolon
id|kill
c_func
(paren
id|os_getpid
c_func
(paren
)paren
comma
id|sig
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_thread
r_int
id|copy_thread
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
id|new_pid
comma
id|err
suffix:semicolon
r_int
r_int
id|stack
suffix:semicolon
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
id|p-&gt;thread
op_assign
(paren
r_struct
id|thread_struct
)paren
id|INIT_THREAD
suffix:semicolon
id|p-&gt;thread.kernel_stack
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
op_plus
l_int|2
op_star
id|PAGE_SIZE
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
id|p-&gt;thread.switch_pipe
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
id|printk
c_func
(paren
l_string|&quot;copy_thread : pipe failed, errno = %d&bslash;n&quot;
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
(paren
r_void
op_star
)paren
id|p-&gt;thread.kernel_stack
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
id|p-&gt;thread.regs.regs.sc
comma
id|current-&gt;thread.regs.regs.sc
)paren
suffix:semicolon
id|PT_REGS_SET_SYSCALL_RETURN
c_func
(paren
op_amp
id|p-&gt;thread.regs
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
id|PT_REGS_SP
c_func
(paren
op_amp
id|p-&gt;thread.regs
)paren
op_assign
id|sp
suffix:semicolon
)brace
)brace
id|p-&gt;thread.extern_pid
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
DECL|function|tracing_reboot
r_void
id|tracing_reboot
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
DECL|function|tracing_halt
r_void
id|tracing_halt
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
DECL|function|tracing_cb
r_void
id|tracing_cb
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
id|thread-&gt;extern_pid
comma
id|pid
)paren
suffix:semicolon
id|thread-&gt;extern_pid
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
DECL|function|stack_sp
r_int
r_int
id|stack_sp
c_func
(paren
r_int
r_int
id|page
)paren
(brace
r_return
id|page
op_plus
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
)brace
DECL|function|current_pid
r_int
id|current_pid
c_func
(paren
r_void
)paren
(brace
r_return
id|current-&gt;pid
suffix:semicolon
)brace
DECL|function|default_idle
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;thread_info-&gt;cpu
op_eq
l_int|0
)paren
(brace
id|idle_timer
c_func
(paren
)paren
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
id|SET_PRI
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * although we are an idle CPU, we do not want to&n;&t;&t; * get into the scheduler unnecessarily.&n;&t;&t; */
id|irq_stat
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
dot
id|idle_timestamp
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
c_func
(paren
)paren
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|idle_sleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
)brace
DECL|function|cpu_idle
r_void
id|cpu_idle
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
DECL|function|page_size
r_int
id|page_size
c_func
(paren
r_void
)paren
(brace
r_return
id|PAGE_SIZE
suffix:semicolon
)brace
DECL|function|page_mask
r_int
id|page_mask
c_func
(paren
r_void
)paren
(brace
r_return
id|PAGE_MASK
suffix:semicolon
)brace
DECL|function|um_virt_to_phys
r_int
r_int
id|um_virt_to_phys
c_func
(paren
r_void
op_star
id|t
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|task
op_assign
id|t
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;mm
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|task-&gt;mm
comma
id|addr
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|pgd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmd
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
r_return
(paren
id|pte_val
c_func
(paren
op_star
id|pte
)paren
op_amp
id|PAGE_MASK
)paren
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
)brace
DECL|function|current_cmd
r_char
op_star
id|current_cmd
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SMP) || defined(CONFIG_HIGHMEM)
r_return
l_string|&quot;(Unknown)&quot;
suffix:semicolon
macro_line|#else
r_int
r_int
id|addr
op_assign
id|um_virt_to_phys
c_func
(paren
id|current
comma
id|current-&gt;mm-&gt;arg_start
)paren
suffix:semicolon
r_return
id|addr
op_eq
l_int|0xffffffff
ques
c_cond
l_string|&quot;(Unknown)&quot;
suffix:colon
id|__va
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|force_sigbus
r_void
id|force_sigbus
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Killing pid %d because of a lack of memory&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|current-&gt;pending.signal
comma
id|SIGBUS
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_SIGNALED
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGBUS
op_or
l_int|0x80
)paren
suffix:semicolon
)brace
DECL|function|dump_thread
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user
op_star
id|u
)paren
(brace
)brace
DECL|function|enable_hlt
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;enable_hlt&quot;
)paren
suffix:semicolon
)brace
DECL|function|disable_hlt
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;disable_hlt&quot;
)paren
suffix:semicolon
)brace
r_extern
r_int
id|signal_frame_size
suffix:semicolon
DECL|function|um_kmalloc
r_void
op_star
id|um_kmalloc
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
)brace
DECL|function|um_kmalloc_atomic
r_void
op_star
id|um_kmalloc_atomic
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
)brace
DECL|function|get_fault_addr
r_int
r_int
id|get_fault_addr
c_func
(paren
r_void
)paren
(brace
r_return
(paren
r_int
r_int
)paren
id|current-&gt;thread.fault_addr
suffix:semicolon
)brace
DECL|variable|get_fault_addr
id|EXPORT_SYMBOL
c_func
(paren
id|get_fault_addr
)paren
suffix:semicolon
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
(paren
r_struct
id|task_struct
op_star
)paren
id|t
suffix:semicolon
id|task-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
)brace
DECL|function|singlestepping
r_int
id|singlestepping
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
(paren
r_struct
id|task_struct
op_star
)paren
id|t
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;thread.singlestep_syscall
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
DECL|function|not_implemented
r_void
id|not_implemented
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Something isn&squot;t implemented in here&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|not_implemented
id|EXPORT_SYMBOL
c_func
(paren
id|not_implemented
)paren
suffix:semicolon
DECL|function|user_context
r_int
id|user_context
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_return
(paren
id|sp
op_amp
(paren
id|PAGE_MASK
op_lshift
l_int|1
)paren
)paren
op_ne
id|current-&gt;thread.kernel_stack
suffix:semicolon
)brace
r_extern
r_void
id|remove_umid_dir
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|remove_umid_dir
id|__uml_exitcall
c_func
(paren
id|remove_umid_dir
)paren
suffix:semicolon
r_extern
id|exitcall_t
id|__uml_exitcall_begin
comma
id|__uml_exitcall_end
suffix:semicolon
DECL|function|do_uml_exitcalls
r_void
id|do_uml_exitcalls
c_func
(paren
r_void
)paren
(brace
id|exitcall_t
op_star
id|call
suffix:semicolon
id|call
op_assign
op_amp
id|__uml_exitcall_end
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|call
op_ge
op_amp
id|__uml_exitcall_begin
)paren
(paren
op_star
id|call
)paren
(paren
)paren
suffix:semicolon
)brace
DECL|function|round_up
r_void
op_star
id|round_up
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|ROUND_UP
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|round_down
r_void
op_star
id|round_down
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|ROUND_DOWN
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|uml_strdup
r_char
op_star
id|uml_strdup
c_func
(paren
r_char
op_star
id|string
)paren
(brace
r_char
op_star
r_new
suffix:semicolon
r_new
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|string
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|strcpy
c_func
(paren
r_new
comma
id|string
)paren
suffix:semicolon
r_return
r_new
suffix:semicolon
)brace
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
id|start
op_assign
(paren
r_int
r_int
)paren
id|current-&gt;thread_info
op_plus
id|PAGE_SIZE
suffix:semicolon
id|end
op_assign
(paren
r_int
r_int
)paren
id|current-&gt;thread_info
op_plus
id|PAGE_SIZE
op_star
l_int|4
suffix:semicolon
id|protect
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
id|protect
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
id|ROUND_DOWN
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
id|ROUND_UP
c_func
(paren
op_amp
id|_etext
)paren
suffix:semicolon
id|protect
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
id|ROUND_DOWN
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
id|ROUND_UP
c_func
(paren
op_amp
id|_edata
)paren
suffix:semicolon
id|protect
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
id|ROUND_DOWN
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
id|ROUND_UP
c_func
(paren
id|brk_start
)paren
suffix:semicolon
id|protect
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
DECL|variable|jail_timer_off
r_int
id|jail_timer_off
op_assign
l_int|0
suffix:semicolon
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
id|jail_timer_off
op_assign
l_int|0
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
id|jail_timer_off
op_assign
l_int|1
suffix:semicolon
id|mprotect_kernel_mem
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|get_init_task
r_void
op_star
id|get_init_task
c_func
(paren
r_void
)paren
(brace
r_return
op_amp
id|init_thread_union.thread_info.task
suffix:semicolon
)brace
DECL|function|copy_to_user_proc
r_int
id|copy_to_user_proc
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
id|size
)paren
(brace
r_return
id|copy_to_user
c_func
(paren
id|to
comma
id|from
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|copy_from_user_proc
r_int
id|copy_from_user_proc
c_func
(paren
r_void
op_star
id|to
comma
r_void
op_star
id|from
comma
r_int
id|size
)paren
(brace
r_return
id|copy_from_user
c_func
(paren
id|to
comma
id|from
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|clear_user_proc
r_int
id|clear_user_proc
c_func
(paren
r_void
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_return
id|clear_user
c_func
(paren
id|buf
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|set_thread_sc
r_void
id|set_thread_sc
c_func
(paren
r_void
op_star
id|sc
)paren
(brace
id|current-&gt;thread.regs.regs.sc
op_assign
id|sc
suffix:semicolon
)brace
DECL|function|smp_sigio_handler
r_int
id|smp_sigio_handler
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|IPI_handler
c_func
(paren
id|hard_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hard_smp_processor_id
c_func
(paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|um_in_interrupt
r_int
id|um_in_interrupt
c_func
(paren
r_void
)paren
(brace
r_return
id|in_interrupt
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
