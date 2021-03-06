multiline_comment|/**&n; * @file buffer_sync.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; *&n; * This is the core of the buffer management. Each&n; * CPU buffer is processed and entered into the&n; * global event buffer. Such processing is necessary&n; * in several circumstances, mentioned below.&n; *&n; * The processing does the job of converting the&n; * transitory EIP value into a persistent dentry/offset&n; * value that the profiler can record at its leisure.&n; *&n; * See fs/dcookies.c for a description of the dentry/offset&n; * objects.&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/dcookies.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;oprofile_stats.h&quot;
macro_line|#include &quot;event_buffer.h&quot;
macro_line|#include &quot;cpu_buffer.h&quot;
macro_line|#include &quot;buffer_sync.h&quot;
r_static
id|LIST_HEAD
c_func
(paren
id|dying_tasks
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|dead_tasks
)paren
suffix:semicolon
DECL|variable|marked_cpus
r_static
id|cpumask_t
id|marked_cpus
op_assign
id|CPU_MASK_NONE
suffix:semicolon
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|task_mortuary
)paren
suffix:semicolon
r_static
r_void
id|process_task_mortuary
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Take ownership of the task struct and place it on the&n; * list for processing. Only after two full buffer syncs&n; * does the task eventually get freed, because by then&n; * we are sure we will not reference it again.&n; */
DECL|function|task_free_notify
r_static
r_int
id|task_free_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|task
op_assign
id|data
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|task_mortuary
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|task-&gt;tasks
comma
op_amp
id|dying_tasks
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|task_mortuary
)paren
suffix:semicolon
r_return
id|NOTIFY_OK
suffix:semicolon
)brace
multiline_comment|/* The task is on its way out. A sync of the buffer means we can catch&n; * any remaining samples for this task.&n; */
DECL|function|task_exit_notify
r_static
r_int
id|task_exit_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
multiline_comment|/* To avoid latency problems, we only process the current CPU,&n;&t; * hoping that most samples for the task are on this CPU&n;&t; */
id|sync_buffer
c_func
(paren
id|_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The task is about to try a do_munmap(). We peek at what it&squot;s going to&n; * do, and if it&squot;s an executable region, process the samples first, so&n; * we don&squot;t lose any. This does not have to be exact, it&squot;s a QoI issue&n; * only.&n; */
DECL|function|munmap_notify
r_static
r_int
id|munmap_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|data
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|mpnt
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mpnt
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpnt
op_logical_and
id|mpnt-&gt;vm_file
op_logical_and
(paren
id|mpnt-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* To avoid latency problems, we only process the current CPU,&n;&t;&t; * hoping that most samples for the task are on this CPU&n;&t;&t; */
id|sync_buffer
c_func
(paren
id|_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* We need to be told about new modules so we don&squot;t attribute to a previously&n; * loaded module, or drop the samples on the floor.&n; */
DECL|function|module_load_notify
r_static
r_int
id|module_load_notify
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|val
comma
r_void
op_star
id|data
)paren
(brace
macro_line|#ifdef CONFIG_MODULES
r_if
c_cond
(paren
id|val
op_ne
id|MODULE_STATE_COMING
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: should we process all CPU buffers ? */
id|down
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|ESCAPE_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|MODULE_LOADED_CODE
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|task_free_nb
r_static
r_struct
id|notifier_block
id|task_free_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|task_free_notify
comma
)brace
suffix:semicolon
DECL|variable|task_exit_nb
r_static
r_struct
id|notifier_block
id|task_exit_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|task_exit_notify
comma
)brace
suffix:semicolon
DECL|variable|munmap_nb
r_static
r_struct
id|notifier_block
id|munmap_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|munmap_notify
comma
)brace
suffix:semicolon
DECL|variable|module_load_nb
r_static
r_struct
id|notifier_block
id|module_load_nb
op_assign
(brace
dot
id|notifier_call
op_assign
id|module_load_notify
comma
)brace
suffix:semicolon
DECL|function|end_sync
r_static
r_void
id|end_sync
c_func
(paren
r_void
)paren
(brace
id|end_cpu_work
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* make sure we don&squot;t leak task structs */
id|process_task_mortuary
c_func
(paren
)paren
suffix:semicolon
id|process_task_mortuary
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sync_start
r_int
id|sync_start
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|start_cpu_work
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|task_handoff_register
c_func
(paren
op_amp
id|task_free_nb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out1
suffix:semicolon
id|err
op_assign
id|profile_event_register
c_func
(paren
id|PROFILE_TASK_EXIT
comma
op_amp
id|task_exit_nb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out2
suffix:semicolon
id|err
op_assign
id|profile_event_register
c_func
(paren
id|PROFILE_MUNMAP
comma
op_amp
id|munmap_nb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out3
suffix:semicolon
id|err
op_assign
id|register_module_notifier
c_func
(paren
op_amp
id|module_load_nb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out4
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out4
suffix:colon
id|profile_event_unregister
c_func
(paren
id|PROFILE_MUNMAP
comma
op_amp
id|munmap_nb
)paren
suffix:semicolon
id|out3
suffix:colon
id|profile_event_unregister
c_func
(paren
id|PROFILE_TASK_EXIT
comma
op_amp
id|task_exit_nb
)paren
suffix:semicolon
id|out2
suffix:colon
id|task_handoff_unregister
c_func
(paren
op_amp
id|task_free_nb
)paren
suffix:semicolon
id|out1
suffix:colon
id|end_sync
c_func
(paren
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|sync_stop
r_void
id|sync_stop
c_func
(paren
r_void
)paren
(brace
id|unregister_module_notifier
c_func
(paren
op_amp
id|module_load_nb
)paren
suffix:semicolon
id|profile_event_unregister
c_func
(paren
id|PROFILE_MUNMAP
comma
op_amp
id|munmap_nb
)paren
suffix:semicolon
id|profile_event_unregister
c_func
(paren
id|PROFILE_TASK_EXIT
comma
op_amp
id|task_exit_nb
)paren
suffix:semicolon
id|task_handoff_unregister
c_func
(paren
op_amp
id|task_free_nb
)paren
suffix:semicolon
id|end_sync
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Optimisation. We can manage without taking the dcookie sem&n; * because we cannot reach this code without at least one&n; * dcookie user still being registered (namely, the reader&n; * of the event buffer). */
DECL|function|fast_get_dcookie
r_static
r_inline
r_int
r_int
id|fast_get_dcookie
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|vfsmount
op_star
id|vfsmnt
)paren
(brace
r_int
r_int
id|cookie
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_cookie
)paren
r_return
(paren
r_int
r_int
)paren
id|dentry
suffix:semicolon
id|get_dcookie
c_func
(paren
id|dentry
comma
id|vfsmnt
comma
op_amp
id|cookie
)paren
suffix:semicolon
r_return
id|cookie
suffix:semicolon
)brace
multiline_comment|/* Look up the dcookie for the task&squot;s first VM_EXECUTABLE mapping,&n; * which corresponds loosely to &quot;application name&quot;. This is&n; * not strictly necessary but allows oprofile to associate&n; * shared-library samples with particular applications&n; */
DECL|function|get_exec_dcookie
r_static
r_int
r_int
id|get_exec_dcookie
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_int
r_int
id|cookie
op_assign
l_int|0
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_goto
id|out
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_file
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_EXECUTABLE
)paren
)paren
r_continue
suffix:semicolon
id|cookie
op_assign
id|fast_get_dcookie
c_func
(paren
id|vma-&gt;vm_file-&gt;f_dentry
comma
id|vma-&gt;vm_file-&gt;f_vfsmnt
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|cookie
suffix:semicolon
)brace
multiline_comment|/* Convert the EIP value of a sample into a persistent dentry/offset&n; * pair that can then be added to the global event buffer. We make&n; * sure to do this lookup before a mm-&gt;mmap modification happens so&n; * we don&squot;t lose track.&n; */
DECL|function|lookup_dcookie
r_static
r_int
r_int
id|lookup_dcookie
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
comma
id|off_t
op_star
id|offset
)paren
(brace
r_int
r_int
id|cookie
op_assign
l_int|0
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_file
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|vma-&gt;vm_start
op_logical_or
id|addr
op_ge
id|vma-&gt;vm_end
)paren
r_continue
suffix:semicolon
id|cookie
op_assign
id|fast_get_dcookie
c_func
(paren
id|vma-&gt;vm_file-&gt;f_dentry
comma
id|vma-&gt;vm_file-&gt;f_vfsmnt
)paren
suffix:semicolon
op_star
id|offset
op_assign
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
op_plus
id|addr
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|cookie
suffix:semicolon
)brace
DECL|variable|last_cookie
r_static
r_int
r_int
id|last_cookie
op_assign
op_complement
l_int|0UL
suffix:semicolon
DECL|function|add_cpu_switch
r_static
r_void
id|add_cpu_switch
c_func
(paren
r_int
id|i
)paren
(brace
id|add_event_entry
c_func
(paren
id|ESCAPE_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|CPU_SWITCH_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|i
)paren
suffix:semicolon
id|last_cookie
op_assign
op_complement
l_int|0UL
suffix:semicolon
)brace
DECL|function|add_kernel_ctx_switch
r_static
r_void
id|add_kernel_ctx_switch
c_func
(paren
r_int
r_int
id|in_kernel
)paren
(brace
id|add_event_entry
c_func
(paren
id|ESCAPE_CODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in_kernel
)paren
id|add_event_entry
c_func
(paren
id|KERNEL_ENTER_SWITCH_CODE
)paren
suffix:semicolon
r_else
id|add_event_entry
c_func
(paren
id|KERNEL_EXIT_SWITCH_CODE
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|add_user_ctx_switch
id|add_user_ctx_switch
c_func
(paren
r_struct
id|task_struct
r_const
op_star
id|task
comma
r_int
r_int
id|cookie
)paren
(brace
id|add_event_entry
c_func
(paren
id|ESCAPE_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|CTX_SWITCH_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|task-&gt;pid
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|cookie
)paren
suffix:semicolon
multiline_comment|/* Another code for daemon back-compat */
id|add_event_entry
c_func
(paren
id|ESCAPE_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|CTX_TGID_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|task-&gt;tgid
)paren
suffix:semicolon
)brace
DECL|function|add_cookie_switch
r_static
r_void
id|add_cookie_switch
c_func
(paren
r_int
r_int
id|cookie
)paren
(brace
id|add_event_entry
c_func
(paren
id|ESCAPE_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|COOKIE_SWITCH_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|cookie
)paren
suffix:semicolon
)brace
DECL|function|add_trace_begin
r_static
r_void
id|add_trace_begin
c_func
(paren
r_void
)paren
(brace
id|add_event_entry
c_func
(paren
id|ESCAPE_CODE
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|TRACE_BEGIN_CODE
)paren
suffix:semicolon
)brace
DECL|function|add_sample_entry
r_static
r_void
id|add_sample_entry
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|event
)paren
(brace
id|add_event_entry
c_func
(paren
id|offset
)paren
suffix:semicolon
id|add_event_entry
c_func
(paren
id|event
)paren
suffix:semicolon
)brace
DECL|function|add_us_sample
r_static
r_int
id|add_us_sample
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|op_sample
op_star
id|s
)paren
(brace
r_int
r_int
id|cookie
suffix:semicolon
id|off_t
id|offset
suffix:semicolon
id|cookie
op_assign
id|lookup_dcookie
c_func
(paren
id|mm
comma
id|s-&gt;eip
comma
op_amp
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cookie
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|oprofile_stats.sample_lost_no_mapping
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cookie
op_ne
id|last_cookie
)paren
(brace
id|add_cookie_switch
c_func
(paren
id|cookie
)paren
suffix:semicolon
id|last_cookie
op_assign
id|cookie
suffix:semicolon
)brace
id|add_sample_entry
c_func
(paren
id|offset
comma
id|s-&gt;event
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Add a sample to the global event buffer. If possible the&n; * sample is converted into a persistent dentry/offset pair&n; * for later lookup from userspace.&n; */
r_static
r_int
DECL|function|add_sample
id|add_sample
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|op_sample
op_star
id|s
comma
r_int
id|in_kernel
)paren
(brace
r_if
c_cond
(paren
id|in_kernel
)paren
(brace
id|add_sample_entry
c_func
(paren
id|s-&gt;eip
comma
id|s-&gt;event
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|mm
)paren
(brace
r_return
id|add_us_sample
c_func
(paren
id|mm
comma
id|s
)paren
suffix:semicolon
)brace
r_else
(brace
id|atomic_inc
c_func
(paren
op_amp
id|oprofile_stats.sample_lost_no_mm
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_mm
r_static
r_void
id|release_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_return
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
DECL|function|take_tasks_mm
r_static
r_struct
id|mm_struct
op_star
id|take_tasks_mm
c_func
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|get_task_mm
c_func
(paren
id|task
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
id|down_read
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|mm
suffix:semicolon
)brace
DECL|function|is_code
r_static
r_inline
r_int
id|is_code
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_return
id|val
op_eq
id|ESCAPE_CODE
suffix:semicolon
)brace
multiline_comment|/* &quot;acquire&quot; as many cpu buffer slots as we can */
DECL|function|get_slots
r_static
r_int
r_int
id|get_slots
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|b
)paren
(brace
r_int
r_int
id|head
op_assign
id|b-&gt;head_pos
suffix:semicolon
r_int
r_int
id|tail
op_assign
id|b-&gt;tail_pos
suffix:semicolon
multiline_comment|/*&n;&t; * Subtle. This resets the persistent last_task&n;&t; * and in_kernel values used for switching notes.&n;&t; * BUT, there is a small window between reading&n;&t; * head_pos, and this call, that means samples&n;&t; * can appear at the new head position, but not&n;&t; * be prefixed with the notes for switching&n;&t; * kernel mode or a task switch. This small hole&n;&t; * can lead to mis-attribution or samples where&n;&t; * we don&squot;t know if it&squot;s in the kernel or not,&n;&t; * at the start of an event buffer.&n;&t; */
id|cpu_buffer_reset
c_func
(paren
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|head
op_ge
id|tail
)paren
r_return
id|head
op_minus
id|tail
suffix:semicolon
r_return
id|head
op_plus
(paren
id|b-&gt;buffer_size
op_minus
id|tail
)paren
suffix:semicolon
)brace
DECL|function|increment_tail
r_static
r_void
id|increment_tail
c_func
(paren
r_struct
id|oprofile_cpu_buffer
op_star
id|b
)paren
(brace
r_int
r_int
id|new_tail
op_assign
id|b-&gt;tail_pos
op_plus
l_int|1
suffix:semicolon
id|rmb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_tail
OL
id|b-&gt;buffer_size
)paren
id|b-&gt;tail_pos
op_assign
id|new_tail
suffix:semicolon
r_else
id|b-&gt;tail_pos
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Move tasks along towards death. Any tasks on dead_tasks&n; * will definitely have no remaining references in any&n; * CPU buffers at this point, because we use two lists,&n; * and to have reached the list, it must have gone through&n; * one full sync already.&n; */
DECL|function|process_task_mortuary
r_static
r_void
id|process_task_mortuary
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|pos
suffix:semicolon
r_struct
id|list_head
op_star
id|pos2
suffix:semicolon
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|task_mortuary
)paren
suffix:semicolon
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|pos2
comma
op_amp
id|dead_tasks
)paren
(brace
id|task
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|task_struct
comma
id|tasks
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|task-&gt;tasks
)paren
suffix:semicolon
id|free_task
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
id|list_for_each_safe
c_func
(paren
id|pos
comma
id|pos2
comma
op_amp
id|dying_tasks
)paren
(brace
id|task
op_assign
id|list_entry
c_func
(paren
id|pos
comma
r_struct
id|task_struct
comma
id|tasks
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|task-&gt;tasks
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|task-&gt;tasks
comma
op_amp
id|dead_tasks
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|task_mortuary
)paren
suffix:semicolon
)brace
DECL|function|mark_done
r_static
r_void
id|mark_done
c_func
(paren
r_int
id|cpu
)paren
(brace
r_int
id|i
suffix:semicolon
id|cpu_set
c_func
(paren
id|cpu
comma
id|marked_cpus
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_isset
c_func
(paren
id|i
comma
id|marked_cpus
)paren
)paren
r_return
suffix:semicolon
)brace
multiline_comment|/* All CPUs have been processed at least once,&n;&t; * we can process the mortuary once&n;&t; */
id|process_task_mortuary
c_func
(paren
)paren
suffix:semicolon
id|cpus_clear
c_func
(paren
id|marked_cpus
)paren
suffix:semicolon
)brace
multiline_comment|/* FIXME: this is not sufficient if we implement syscall barrier backtrace&n; * traversal, the code switch to sb_sample_start at first kernel enter/exit&n; * switch so we need a fifth state and some special handling in sync_buffer()&n; */
r_typedef
r_enum
(brace
DECL|enumerator|sb_bt_ignore
id|sb_bt_ignore
op_assign
op_minus
l_int|2
comma
DECL|enumerator|sb_buffer_start
id|sb_buffer_start
comma
DECL|enumerator|sb_bt_start
id|sb_bt_start
comma
DECL|enumerator|sb_sample_start
id|sb_sample_start
comma
DECL|typedef|sync_buffer_state
)brace
id|sync_buffer_state
suffix:semicolon
multiline_comment|/* Sync one of the CPU&squot;s buffers into the global event buffer.&n; * Here we need to go through each batch of samples punctuated&n; * by context switch notes, taking the task&squot;s mmap_sem and doing&n; * lookup in task-&gt;mm-&gt;mmap to convert EIP into dcookie/offset&n; * value.&n; */
DECL|function|sync_buffer
r_void
id|sync_buffer
c_func
(paren
r_int
id|cpu
)paren
(brace
r_struct
id|oprofile_cpu_buffer
op_star
id|cpu_buf
op_assign
op_amp
id|cpu_buffer
(braket
id|cpu
)braket
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|task_struct
op_star
r_new
suffix:semicolon
r_int
r_int
id|cookie
op_assign
l_int|0
suffix:semicolon
r_int
id|in_kernel
op_assign
l_int|1
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|sync_buffer_state
id|state
op_assign
id|sb_buffer_start
suffix:semicolon
r_int
r_int
id|available
suffix:semicolon
id|down
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
id|add_cpu_switch
c_func
(paren
id|cpu
)paren
suffix:semicolon
multiline_comment|/* Remember, only we can modify tail_pos */
id|available
op_assign
id|get_slots
c_func
(paren
id|cpu_buf
)paren
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
id|available
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|op_sample
op_star
id|s
op_assign
op_amp
id|cpu_buf-&gt;buffer
(braket
id|cpu_buf-&gt;tail_pos
)braket
suffix:semicolon
r_if
c_cond
(paren
id|is_code
c_func
(paren
id|s-&gt;eip
)paren
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;event
op_le
id|CPU_IS_KERNEL
)paren
(brace
multiline_comment|/* kernel/userspace switch */
id|in_kernel
op_assign
id|s-&gt;event
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
id|sb_buffer_start
)paren
id|state
op_assign
id|sb_sample_start
suffix:semicolon
id|add_kernel_ctx_switch
c_func
(paren
id|s-&gt;event
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;event
op_eq
id|CPU_TRACE_BEGIN
)paren
(brace
id|state
op_assign
id|sb_bt_start
suffix:semicolon
id|add_trace_begin
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|mm_struct
op_star
id|oldmm
op_assign
id|mm
suffix:semicolon
multiline_comment|/* userspace context switch */
r_new
op_assign
(paren
r_struct
id|task_struct
op_star
)paren
id|s-&gt;event
suffix:semicolon
id|release_mm
c_func
(paren
id|oldmm
)paren
suffix:semicolon
id|mm
op_assign
id|take_tasks_mm
c_func
(paren
r_new
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|oldmm
)paren
id|cookie
op_assign
id|get_exec_dcookie
c_func
(paren
id|mm
)paren
suffix:semicolon
id|add_user_ctx_switch
c_func
(paren
r_new
comma
id|cookie
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|state
op_ge
id|sb_bt_start
op_logical_and
op_logical_neg
id|add_sample
c_func
(paren
id|mm
comma
id|s
comma
id|in_kernel
)paren
)paren
(brace
r_if
c_cond
(paren
id|state
op_eq
id|sb_bt_start
)paren
(brace
id|state
op_assign
id|sb_bt_ignore
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|oprofile_stats.bt_lost_no_mapping
)paren
suffix:semicolon
)brace
)brace
)brace
id|increment_tail
c_func
(paren
id|cpu_buf
)paren
suffix:semicolon
)brace
id|release_mm
c_func
(paren
id|mm
)paren
suffix:semicolon
id|mark_done
c_func
(paren
id|cpu
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|buffer_sem
)paren
suffix:semicolon
)brace
eof
