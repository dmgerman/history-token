multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef __KERN_UTIL_H__
DECL|macro|__KERN_UTIL_H__
mdefine_line|#define __KERN_UTIL_H__
macro_line|#include &quot;sysdep/ptrace.h&quot;
r_extern
r_int
id|ncpus
suffix:semicolon
r_extern
r_char
op_star
id|linux_prog
suffix:semicolon
r_extern
r_char
op_star
id|gdb_init
suffix:semicolon
r_extern
r_int
id|kmalloc_ok
suffix:semicolon
r_extern
r_int
id|timer_irq_inited
suffix:semicolon
r_extern
r_int
id|jail
suffix:semicolon
DECL|macro|ROUND_DOWN
mdefine_line|#define ROUND_DOWN(addr) ((void *)(((unsigned long) addr) &amp; PAGE_MASK))
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(addr) ROUND_DOWN(((unsigned long) addr) + PAGE_SIZE - 1)
r_extern
r_int
id|kernel_fork
c_func
(paren
r_int
r_int
id|flags
comma
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
)paren
suffix:semicolon
r_extern
r_int
r_int
id|stack_sp
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_int
id|kernel_thread_proc
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_void
id|syscall_segv
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_int
id|current_pid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_init_pid
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|do_signal
c_func
(paren
r_int
id|error
)paren
suffix:semicolon
r_extern
r_int
id|is_stack_fault
c_func
(paren
r_int
r_int
id|sp
)paren
suffix:semicolon
r_extern
r_int
r_int
id|segv
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|ip
comma
r_int
id|is_write
comma
r_int
id|is_user
comma
r_void
op_star
id|sc_ptr
)paren
suffix:semicolon
r_extern
r_int
id|set_user_mode
c_func
(paren
r_void
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|syscall_ready
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_tracing
c_func
(paren
r_void
op_star
id|t
comma
r_int
id|tracing
)paren
suffix:semicolon
r_extern
r_int
id|is_tracing
c_func
(paren
r_void
op_star
id|task
)paren
suffix:semicolon
r_extern
r_int
id|segv_syscall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kern_finish_exec
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|new_pid
comma
r_int
r_int
id|stack
)paren
suffix:semicolon
r_extern
r_int
id|page_size
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|page_mask
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|need_finish_fork
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|add_input_request
c_func
(paren
r_int
id|op
comma
r_void
(paren
op_star
id|proc
)paren
(paren
r_int
)paren
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|env
)paren
suffix:semicolon
r_extern
r_char
op_star
id|current_cmd
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|timer_handler
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
r_int
id|set_signals
c_func
(paren
r_int
id|enable
)paren
suffix:semicolon
r_extern
r_void
id|force_sigbus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pid_to_processor_id
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|block_signals
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|unblock_signals
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|deliver_signals
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
r_extern
r_int
id|next_syscall_index
c_func
(paren
r_int
id|max
)paren
suffix:semicolon
r_extern
r_int
id|next_trap_index
c_func
(paren
r_int
id|max
)paren
suffix:semicolon
r_extern
r_void
id|default_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|finish_fork
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|init_flush_vm
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|syscall_sp
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|hz
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|idle_timer
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|do_IRQ
c_func
(paren
r_int
id|irq
comma
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|external_pid
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
r_extern
r_int
id|pid_to_processor_id
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|boot_timer_handler
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
r_extern
r_void
id|interrupt_end
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tracing_reboot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|tracing_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_int
id|debugger_signal
c_func
(paren
r_int
id|status
comma
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|debugger_parent_signal
c_func
(paren
r_int
id|status
comma
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|child_signal
c_func
(paren
r_int
id|pid
comma
r_int
id|status
)paren
suffix:semicolon
r_extern
r_int
id|init_ptrace_proxy
c_func
(paren
r_int
id|idle_pid
comma
r_int
id|startup
comma
r_int
id|stop
)paren
suffix:semicolon
r_extern
r_int
id|init_parent_proxy
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|check_stack_overflow
c_func
(paren
r_void
op_star
id|ptr
)paren
suffix:semicolon
r_extern
r_void
id|relay_signal
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
r_int
id|singlestepping
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|clear_singlestep
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|not_implemented
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|user_context
c_func
(paren
r_int
r_int
id|sp
)paren
suffix:semicolon
r_extern
r_void
id|timer_irq
c_func
(paren
r_struct
id|uml_pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|unprotect_stack
c_func
(paren
r_int
r_int
id|stack
)paren
suffix:semicolon
r_extern
r_void
id|do_uml_exitcalls
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|attach_debugger
c_func
(paren
r_int
id|idle_pid
comma
r_int
id|pid
comma
r_int
id|stop
)paren
suffix:semicolon
r_extern
r_void
op_star
id|round_up
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
op_star
id|round_down
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|bad_segv
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|ip
comma
r_int
id|is_write
)paren
suffix:semicolon
r_extern
r_int
id|config_gdb
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_int
id|remove_gdb
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|uml_strdup
c_func
(paren
r_char
op_star
id|string
)paren
suffix:semicolon
r_extern
r_void
id|unprotect_kernel_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|protect_kernel_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_kmem_end
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_kmem_end
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|set_task_sizes
c_func
(paren
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|uml_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pid_to_processor_id
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|set_current
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|lock_signalled_task
c_func
(paren
r_void
op_star
id|t
)paren
suffix:semicolon
r_extern
r_void
id|IPI_handler
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_void
op_star
id|get_init_task
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|set_thread_sc
c_func
(paren
r_void
op_star
id|sc
)paren
suffix:semicolon
r_extern
r_void
id|bus_handler
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
r_int
id|execute_syscall
c_func
(paren
r_void
op_star
id|r
)paren
suffix:semicolon
r_extern
r_int
id|smp_sigio_handler
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
op_star
id|get_current
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
r_extern
r_void
id|machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|is_syscall
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|arch_switch
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|is_valid_pid
c_func
(paren
r_int
id|pid
)paren
suffix:semicolon
r_extern
r_void
id|free_irq
c_func
(paren
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|um_in_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpu
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
