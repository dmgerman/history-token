multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Copyright 2003 PathScale, Inc.&n; * Licensed under the GPL&n; */
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
macro_line|#include &quot;linux/vmalloc.h&quot;
macro_line|#include &quot;linux/spinlock.h&quot;
macro_line|#include &quot;linux/proc_fs.h&quot;
macro_line|#include &quot;linux/ptrace.h&quot;
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;asm/mman.h&quot;
macro_line|#include &quot;asm/segment.h&quot;
macro_line|#include &quot;asm/stat.h&quot;
macro_line|#include &quot;asm/pgtable.h&quot;
macro_line|#include &quot;asm/processor.h&quot;
macro_line|#include &quot;asm/tlbflush.h&quot;
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
macro_line|#include &quot;mode.h&quot;
macro_line|#include &quot;mode_kern.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
multiline_comment|/* This is a per-cpu array.  A processor only modifies its entry and it only&n; * cares about its entry, so it&squot;s OK if another processor is modifying its&n; * entry.&n; */
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
id|ret
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|ret
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
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
id|CHOOSE_MODE_PROC
c_func
(paren
id|external_pid_tt
comma
id|external_pid_skas
comma
id|task
)paren
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
id|ncpus
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
id|page
op_assign
id|__get_free_pages
c_func
(paren
id|flags
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
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
r_int
id|pid
suffix:semicolon
id|current-&gt;thread.request.u.thread.proc
op_assign
id|fn
suffix:semicolon
id|current-&gt;thread.request.u.thread.arg
op_assign
id|arg
suffix:semicolon
id|pid
op_assign
id|do_fork
c_func
(paren
id|CLONE_VM
op_or
id|CLONE_UNTRACED
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
id|panic
c_func
(paren
l_string|&quot;do_fork failed in kernel_thread, errno = %d&quot;
comma
id|pid
)paren
suffix:semicolon
)brace
r_return
id|pid
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
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prev
op_ne
id|next
)paren
id|cpu_clear
c_func
(paren
id|cpu
comma
id|prev-&gt;cpu_vm_mask
)paren
suffix:semicolon
id|cpu_set
c_func
(paren
id|cpu
comma
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
id|external_pid
c_func
(paren
id|task
)paren
comma
id|task
)brace
)paren
suffix:semicolon
)brace
DECL|function|_switch_to
r_void
op_star
id|_switch_to
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
r_return
id|CHOOSE_MODE
c_func
(paren
id|switch_to_tt
c_func
(paren
id|prev
comma
id|next
)paren
comma
id|switch_to_skas
c_func
(paren
id|prev
comma
id|next
)paren
)paren
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
id|CHOOSE_MODE
c_func
(paren
id|release_thread_tt
c_func
(paren
id|task
)paren
comma
id|release_thread_skas
c_func
(paren
id|task
)paren
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
id|CHOOSE_MODE
c_func
(paren
id|exit_thread_tt
c_func
(paren
)paren
comma
id|exit_thread_skas
c_func
(paren
)paren
)paren
suffix:semicolon
id|unprotect_stack
c_func
(paren
(paren
r_int
r_int
)paren
id|current_thread
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
DECL|function|prepare_to_copy
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
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
id|p-&gt;thread
op_assign
(paren
r_struct
id|thread_struct
)paren
id|INIT_THREAD
suffix:semicolon
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|copy_thread_tt
comma
id|copy_thread_skas
comma
id|nr
comma
id|clone_flags
comma
id|sp
comma
id|stack_top
comma
id|p
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|initial_thread_cb
r_void
id|initial_thread_cb
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
r_int
id|save_kmalloc_ok
op_assign
id|kmalloc_ok
suffix:semicolon
id|kmalloc_ok
op_assign
l_int|0
suffix:semicolon
id|CHOOSE_MODE_PROC
c_func
(paren
id|initial_thread_cb_tt
comma
id|initial_thread_cb_skas
comma
id|proc
comma
id|arg
)paren
suffix:semicolon
id|kmalloc_ok
op_assign
id|save_kmalloc_ok
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
id|uml_idle_timer
c_func
(paren
)paren
suffix:semicolon
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
id|CHOOSE_MODE
c_func
(paren
id|init_idle_tt
c_func
(paren
)paren
comma
id|init_idle_skas
c_func
(paren
)paren
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
r_void
op_star
id|um_virt_to_phys
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
comma
id|pte_t
op_star
id|pte_out
)paren
(brace
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
r_if
c_cond
(paren
id|task-&gt;mm
op_eq
l_int|NULL
)paren
(brace
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
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
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
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
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pte_out
op_ne
l_int|NULL
)paren
(brace
op_star
id|pte_out
op_assign
op_star
id|pte
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
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
r_void
op_star
id|addr
op_assign
id|um_virt_to_phys
c_func
(paren
id|current
comma
id|current-&gt;mm-&gt;arg_start
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|addr
)paren
ques
c_cond
l_string|&quot;(Unknown)&quot;
suffix:colon
id|__va
c_func
(paren
(paren
r_int
r_int
)paren
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
DECL|variable|enable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|enable_hlt
)paren
suffix:semicolon
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
DECL|variable|disable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|disable_hlt
)paren
suffix:semicolon
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
DECL|function|um_vmalloc
r_void
op_star
id|um_vmalloc
c_func
(paren
r_int
id|size
)paren
(brace
r_return
id|vmalloc
c_func
(paren
id|size
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
r_int
r_int
id|stack
suffix:semicolon
id|stack
op_assign
id|sp
op_amp
(paren
id|PAGE_MASK
op_lshift
id|CONFIG_KERNEL_STACK_ORDER
)paren
suffix:semicolon
r_return
id|stack
op_ne
(paren
r_int
r_int
)paren
id|current_thread
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
DECL|function|strlen_user_proc
r_int
id|strlen_user_proc
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|strlen_user
c_func
(paren
id|str
)paren
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
r_int
id|cpu
op_assign
id|current_thread-&gt;cpu
suffix:semicolon
id|IPI_handler
c_func
(paren
id|cpu
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_ne
l_int|0
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
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
DECL|function|cpu
r_int
id|cpu
c_func
(paren
r_void
)paren
(brace
r_return
id|current_thread-&gt;cpu
suffix:semicolon
)brace
DECL|variable|using_sysemu
r_static
id|atomic_t
id|using_sysemu
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|variable|sysemu_supported
r_int
id|sysemu_supported
suffix:semicolon
DECL|function|set_using_sysemu
r_void
id|set_using_sysemu
c_func
(paren
r_int
id|value
)paren
(brace
id|atomic_set
c_func
(paren
op_amp
id|using_sysemu
comma
id|sysemu_supported
op_logical_and
id|value
)paren
suffix:semicolon
)brace
DECL|function|get_using_sysemu
r_int
id|get_using_sysemu
c_func
(paren
r_void
)paren
(brace
r_return
id|atomic_read
c_func
(paren
op_amp
id|using_sysemu
)paren
suffix:semicolon
)brace
DECL|function|proc_read_sysemu
r_static
r_int
id|proc_read_sysemu
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|size
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|snprintf
c_func
(paren
id|buf
comma
id|size
comma
l_string|&quot;%d&bslash;n&quot;
comma
id|get_using_sysemu
c_func
(paren
)paren
)paren
OL
id|size
)paren
multiline_comment|/*No overflow*/
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
DECL|function|proc_write_sysemu
r_static
r_int
id|proc_write_sysemu
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_char
id|tmp
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|tmp
comma
id|buf
comma
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
(braket
l_int|0
)braket
op_eq
l_char|&squot;0&squot;
op_logical_or
id|tmp
(braket
l_int|0
)braket
op_eq
l_char|&squot;1&squot;
)paren
id|set_using_sysemu
c_func
(paren
id|tmp
(braket
l_int|0
)braket
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
multiline_comment|/*We use the first char, but pretend to write everything*/
)brace
DECL|function|make_proc_sysemu
r_int
id|__init
id|make_proc_sysemu
c_func
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysemu_supported
)paren
r_return
l_int|0
suffix:semicolon
id|ent
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;sysemu&quot;
comma
l_int|0600
comma
op_amp
id|proc_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failed to register /proc/sysemu&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ent-&gt;read_proc
op_assign
id|proc_read_sysemu
suffix:semicolon
id|ent-&gt;write_proc
op_assign
id|proc_write_sysemu
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|make_proc_sysemu
id|late_initcall
c_func
(paren
id|make_proc_sysemu
)paren
suffix:semicolon
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
op_logical_neg
(paren
id|task-&gt;ptrace
op_amp
id|PT_DTRACE
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;thread.singlestep_syscall
)paren
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
