multiline_comment|/*&n; *  linux/kernel/exit.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#ifdef CONFIG_BSD_PROCESS_ACCT
macro_line|#include &lt;linux/acct.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
r_extern
r_void
id|sem_exit
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|child_reaper
suffix:semicolon
r_int
id|getrusage
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
suffix:semicolon
DECL|function|release_task
r_static
r_void
id|release_task
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_if
c_cond
(paren
id|p
op_ne
id|current
)paren
(brace
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t;&t; * Wait to make sure the process isn&squot;t on the&n;&t;&t; * runqueue (active on some other CPU still)&n;&t;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|task_lock
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;has_cpu
)paren
r_break
suffix:semicolon
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
r_do
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p-&gt;has_cpu
)paren
suffix:semicolon
)brace
id|task_unlock
c_func
(paren
id|p
)paren
suffix:semicolon
macro_line|#endif
id|atomic_dec
c_func
(paren
op_amp
id|p-&gt;user-&gt;processes
)paren
suffix:semicolon
id|free_uid
c_func
(paren
id|p-&gt;user
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|p
)paren
suffix:semicolon
id|release_thread
c_func
(paren
id|p
)paren
suffix:semicolon
id|current-&gt;cmin_flt
op_add_assign
id|p-&gt;min_flt
op_plus
id|p-&gt;cmin_flt
suffix:semicolon
id|current-&gt;cmaj_flt
op_add_assign
id|p-&gt;maj_flt
op_plus
id|p-&gt;cmaj_flt
suffix:semicolon
id|current-&gt;cnswap
op_add_assign
id|p-&gt;nswap
op_plus
id|p-&gt;cnswap
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Potentially available timeslices are retrieved&n;&t;&t; * here - this way the parent does not get penalized&n;&t;&t; * for creating too many processes.&n;&t;&t; *&n;&t;&t; * (this cannot be used to artificially &squot;generate&squot;&n;&t;&t; * timeslices, because any timeslice recovered here&n;&t;&t; * was given away by the parent in the first place.)&n;&t;&t; */
id|current-&gt;counter
op_add_assign
id|p-&gt;counter
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;counter
op_ge
id|MAX_COUNTER
)paren
id|current-&gt;counter
op_assign
id|MAX_COUNTER
suffix:semicolon
id|p-&gt;pid
op_assign
l_int|0
suffix:semicolon
id|free_task_struct
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;task releasing itself&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This checks not only the pgrp, but falls back on the pid if no&n; * satisfactory pgrp is found. I dunno - gdb doesn&squot;t work correctly&n; * without this...&n; */
DECL|function|session_of_pgrp
r_int
id|session_of_pgrp
c_func
(paren
r_int
id|pgrp
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
id|fallback
suffix:semicolon
id|fallback
op_assign
op_minus
l_int|1
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;session
op_le
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pgrp
op_eq
id|pgrp
)paren
(brace
id|fallback
op_assign
id|p-&gt;session
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;pid
op_eq
id|pgrp
)paren
id|fallback
op_assign
id|p-&gt;session
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
id|fallback
suffix:semicolon
)brace
multiline_comment|/*&n; * Determine if a process group is &quot;orphaned&quot;, according to the POSIX&n; * definition in 2.2.2.52.  Orphaned process groups are not to be affected&n; * by terminal-generated stop signals.  Newly orphaned process groups are&n; * to receive a SIGHUP and a SIGCONT.&n; *&n; * &quot;I ask you, have you ever known what it is to be an orphan?&quot;&n; */
DECL|function|will_become_orphaned_pgrp
r_static
r_int
id|will_become_orphaned_pgrp
c_func
(paren
r_int
id|pgrp
comma
r_struct
id|task_struct
op_star
id|ignored_task
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
(paren
id|p
op_eq
id|ignored_task
)paren
op_logical_or
(paren
id|p-&gt;pgrp
op_ne
id|pgrp
)paren
op_logical_or
(paren
id|p-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
op_logical_or
(paren
id|p-&gt;p_pptr-&gt;pid
op_eq
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;p_pptr-&gt;pgrp
op_ne
id|pgrp
)paren
op_logical_and
(paren
id|p-&gt;p_pptr-&gt;session
op_eq
id|p-&gt;session
)paren
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
l_int|0
suffix:semicolon
)brace
)brace
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
multiline_comment|/* (sighing) &quot;Often!&quot; */
)brace
DECL|function|is_orphaned_pgrp
r_int
id|is_orphaned_pgrp
c_func
(paren
r_int
id|pgrp
)paren
(brace
r_return
id|will_become_orphaned_pgrp
c_func
(paren
id|pgrp
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|has_stopped_jobs
r_static
r_inline
r_int
id|has_stopped_jobs
c_func
(paren
r_int
id|pgrp
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pgrp
op_ne
id|pgrp
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;state
op_ne
id|TASK_STOPPED
)paren
r_continue
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * When we die, we re-parent all our children.&n; * Try to give them to another thread in our process&n; * group, and if no such member exists, give it to&n; * the global child reaper process (ie &quot;init&quot;)&n; */
DECL|function|forget_original_parent
r_static
r_inline
r_void
id|forget_original_parent
c_func
(paren
r_struct
id|task_struct
op_star
id|father
)paren
(brace
r_struct
id|task_struct
op_star
id|p
comma
op_star
id|reaper
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
multiline_comment|/* Next in our thread group */
id|reaper
op_assign
id|next_thread
c_func
(paren
id|father
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reaper
op_eq
id|father
)paren
id|reaper
op_assign
id|child_reaper
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;p_opptr
op_eq
id|father
)paren
(brace
multiline_comment|/* We dont want people slaying init */
id|p-&gt;exit_signal
op_assign
id|SIGCHLD
suffix:semicolon
id|p-&gt;self_exec_id
op_increment
suffix:semicolon
id|p-&gt;p_opptr
op_assign
id|reaper
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;pdeath_signal
)paren
id|send_sig
c_func
(paren
id|p-&gt;pdeath_signal
comma
id|p
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
)brace
DECL|function|close_files
r_static
r_inline
r_void
id|close_files
c_func
(paren
r_struct
id|files_struct
op_star
id|files
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|set
suffix:semicolon
id|i
op_assign
id|j
op_star
id|__NFDBITS
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|files-&gt;max_fdset
op_logical_or
id|i
op_ge
id|files-&gt;max_fds
)paren
r_break
suffix:semicolon
id|set
op_assign
id|files-&gt;open_fds-&gt;fds_bits
(braket
id|j
op_increment
)braket
suffix:semicolon
r_while
c_loop
(paren
id|set
)paren
(brace
r_if
c_cond
(paren
id|set
op_amp
l_int|1
)paren
(brace
r_struct
id|file
op_star
id|file
op_assign
id|xchg
c_func
(paren
op_amp
id|files-&gt;fd
(braket
id|i
)braket
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|filp_close
c_func
(paren
id|file
comma
id|files
)paren
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
id|set
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|function|put_files_struct
r_void
id|put_files_struct
c_func
(paren
r_struct
id|files_struct
op_star
id|files
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|files-&gt;count
)paren
)paren
(brace
id|close_files
c_func
(paren
id|files
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Free the fd and fdset arrays if we expanded them.&n;&t;&t; */
r_if
c_cond
(paren
id|files-&gt;fd
op_ne
op_amp
id|files-&gt;fd_array
(braket
l_int|0
)braket
)paren
id|free_fd_array
c_func
(paren
id|files-&gt;fd
comma
id|files-&gt;max_fds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|files-&gt;max_fdset
OG
id|__FD_SETSIZE
)paren
(brace
id|free_fdset
c_func
(paren
id|files-&gt;open_fds
comma
id|files-&gt;max_fdset
)paren
suffix:semicolon
id|free_fdset
c_func
(paren
id|files-&gt;close_on_exec
comma
id|files-&gt;max_fdset
)paren
suffix:semicolon
)brace
id|kmem_cache_free
c_func
(paren
id|files_cachep
comma
id|files
)paren
suffix:semicolon
)brace
)brace
DECL|function|__exit_files
r_static
r_inline
r_void
id|__exit_files
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|files_struct
op_star
id|files
op_assign
id|tsk-&gt;files
suffix:semicolon
r_if
c_cond
(paren
id|files
)paren
(brace
id|task_lock
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;files
op_assign
l_int|NULL
suffix:semicolon
id|task_unlock
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|put_files_struct
c_func
(paren
id|files
)paren
suffix:semicolon
)brace
)brace
DECL|function|exit_files
r_void
id|exit_files
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|__exit_files
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
DECL|function|__put_fs_struct
r_static
r_inline
r_void
id|__put_fs_struct
c_func
(paren
r_struct
id|fs_struct
op_star
id|fs
)paren
(brace
multiline_comment|/* No need to hold fs-&gt;lock if we are killing it */
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|fs-&gt;count
)paren
)paren
(brace
id|dput
c_func
(paren
id|fs-&gt;root
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|fs-&gt;rootmnt
)paren
suffix:semicolon
id|dput
c_func
(paren
id|fs-&gt;pwd
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|fs-&gt;pwdmnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fs-&gt;altroot
)paren
(brace
id|dput
c_func
(paren
id|fs-&gt;altroot
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|fs-&gt;altrootmnt
)paren
suffix:semicolon
)brace
id|kmem_cache_free
c_func
(paren
id|fs_cachep
comma
id|fs
)paren
suffix:semicolon
)brace
)brace
DECL|function|put_fs_struct
r_void
id|put_fs_struct
c_func
(paren
r_struct
id|fs_struct
op_star
id|fs
)paren
(brace
id|__put_fs_struct
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
DECL|function|__exit_fs
r_static
r_inline
r_void
id|__exit_fs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|fs_struct
op_star
id|fs
op_assign
id|tsk-&gt;fs
suffix:semicolon
r_if
c_cond
(paren
id|fs
)paren
(brace
id|task_lock
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;fs
op_assign
l_int|NULL
suffix:semicolon
id|task_unlock
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|__put_fs_struct
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
)brace
DECL|function|exit_fs
r_void
id|exit_fs
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|__exit_fs
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We can use these to temporarily drop into&n; * &quot;lazy TLB&quot; mode and back.&n; */
DECL|function|start_lazy_tlb
r_struct
id|mm_struct
op_star
id|start_lazy_tlb
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|current-&gt;mm
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* active_mm is still &squot;mm&squot; */
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_count
)paren
suffix:semicolon
id|enter_lazy_tlb
c_func
(paren
id|mm
comma
id|current
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|mm
suffix:semicolon
)brace
DECL|function|end_lazy_tlb
r_void
id|end_lazy_tlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_struct
id|mm_struct
op_star
id|active_mm
op_assign
id|current-&gt;active_mm
suffix:semicolon
id|current-&gt;mm
op_assign
id|mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|active_mm
)paren
(brace
id|current-&gt;active_mm
op_assign
id|mm
suffix:semicolon
id|activate_mm
c_func
(paren
id|active_mm
comma
id|mm
)paren
suffix:semicolon
)brace
id|mmdrop
c_func
(paren
id|active_mm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Turn us into a lazy TLB process if we&n; * aren&squot;t already..&n; */
DECL|function|__exit_mm
r_static
r_inline
r_void
id|__exit_mm
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
id|mm_release
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_ne
id|tsk-&gt;active_mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* more a memory barrier than a real lock */
id|task_lock
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;mm
op_assign
l_int|NULL
suffix:semicolon
id|task_unlock
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|enter_lazy_tlb
c_func
(paren
id|mm
comma
id|current
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
DECL|function|exit_mm
r_void
id|exit_mm
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|__exit_mm
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Send signals to all our closest relatives so that they know&n; * to properly mourn us..&n; */
DECL|function|exit_notify
r_static
r_void
id|exit_notify
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|p
comma
op_star
id|t
suffix:semicolon
id|forget_original_parent
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check to see if any process groups have become orphaned&n;&t; * as a result of our exiting, and if they have any stopped&n;&t; * jobs, send them a SIGHUP and then a SIGCONT.  (POSIX 3.2.2.2)&n;&t; *&n;&t; * Case i: Our father is in a different pgrp than we are&n;&t; * and we were the only connection outside, so our pgrp&n;&t; * is about to become orphaned.&n;&t; */
id|t
op_assign
id|current-&gt;p_pptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|t-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
op_logical_and
(paren
id|t-&gt;session
op_eq
id|current-&gt;session
)paren
op_logical_and
id|will_become_orphaned_pgrp
c_func
(paren
id|current-&gt;pgrp
comma
id|current
)paren
op_logical_and
id|has_stopped_jobs
c_func
(paren
id|current-&gt;pgrp
)paren
)paren
(brace
id|kill_pg
c_func
(paren
id|current-&gt;pgrp
comma
id|SIGHUP
comma
l_int|1
)paren
suffix:semicolon
id|kill_pg
c_func
(paren
id|current-&gt;pgrp
comma
id|SIGCONT
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Let father know we died &n;&t; *&n;&t; * Thread signals are configurable, but you aren&squot;t going to use&n;&t; * that to send signals to arbitary processes. &n;&t; * That stops right now.&n;&t; *&n;&t; * If the parent exec id doesn&squot;t match the exec id we saved&n;&t; * when we started then we know the parent has changed security&n;&t; * domain.&n;&t; *&n;&t; * If our self_exec id doesn&squot;t match our parent_exec_id then&n;&t; * we have changed execution domain as these two values started&n;&t; * the same after a fork.&n;&t; *&t;&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_signal
op_ne
id|SIGCHLD
op_logical_and
(paren
id|current-&gt;parent_exec_id
op_ne
id|t-&gt;self_exec_id
op_logical_or
id|current-&gt;self_exec_id
op_ne
id|current-&gt;parent_exec_id
)paren
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_KILL
)paren
)paren
(brace
id|current-&gt;exit_signal
op_assign
id|SIGCHLD
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This loop does two things:&n;&t; *&n;  &t; * A.  Make init inherit all the child processes&n;&t; * B.  Check to see if any process groups have become orphaned&n;&t; *&t;as a result of our exiting, and if they have any stopped&n;&t; *&t;jobs, send them a SIGHUP and then a SIGCONT.  (POSIX 3.2.2.2)&n;&t; */
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_ZOMBIE
suffix:semicolon
id|do_notify_parent
c_func
(paren
id|current
comma
id|current-&gt;exit_signal
)paren
suffix:semicolon
r_while
c_loop
(paren
id|current-&gt;p_cptr
op_ne
l_int|NULL
)paren
(brace
id|p
op_assign
id|current-&gt;p_cptr
suffix:semicolon
id|current-&gt;p_cptr
op_assign
id|p-&gt;p_osptr
suffix:semicolon
id|p-&gt;p_ysptr
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;ptrace
op_assign
l_int|0
suffix:semicolon
id|p-&gt;p_pptr
op_assign
id|p-&gt;p_opptr
suffix:semicolon
id|p-&gt;p_osptr
op_assign
id|p-&gt;p_pptr-&gt;p_cptr
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;p_osptr
)paren
id|p-&gt;p_osptr-&gt;p_ysptr
op_assign
id|p
suffix:semicolon
id|p-&gt;p_pptr-&gt;p_cptr
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
id|do_notify_parent
c_func
(paren
id|p
comma
id|p-&gt;exit_signal
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * process group orphan check&n;&t;&t; * Case ii: Our child is in a different pgrp&n;&t;&t; * than we are, and it was the only connection&n;&t;&t; * outside, so the child pgrp is now orphaned.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|p-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
op_logical_and
(paren
id|p-&gt;session
op_eq
id|current-&gt;session
)paren
)paren
(brace
r_int
id|pgrp
op_assign
id|p-&gt;pgrp
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_orphaned_pgrp
c_func
(paren
id|pgrp
)paren
op_logical_and
id|has_stopped_jobs
c_func
(paren
id|pgrp
)paren
)paren
(brace
id|kill_pg
c_func
(paren
id|pgrp
comma
id|SIGHUP
comma
l_int|1
)paren
suffix:semicolon
id|kill_pg
c_func
(paren
id|pgrp
comma
id|SIGCONT
comma
l_int|1
)paren
suffix:semicolon
)brace
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
)brace
)brace
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
)brace
DECL|function|do_exit
id|NORET_TYPE
r_void
id|do_exit
c_func
(paren
r_int
id|code
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Aiee, killing interrupt handler!&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk-&gt;pid
)paren
id|panic
c_func
(paren
l_string|&quot;Attempted to kill the idle task!&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;pid
op_eq
l_int|1
)paren
id|panic
c_func
(paren
l_string|&quot;Attempted to kill init!&quot;
)paren
suffix:semicolon
id|tsk-&gt;flags
op_or_assign
id|PF_EXITING
suffix:semicolon
id|del_timer_sync
c_func
(paren
op_amp
id|tsk-&gt;real_timer
)paren
suffix:semicolon
id|fake_volatile
suffix:colon
macro_line|#ifdef CONFIG_BSD_PROCESS_ACCT
id|acct_process
c_func
(paren
id|code
)paren
suffix:semicolon
macro_line|#endif
id|__exit_mm
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sem_exit
c_func
(paren
)paren
suffix:semicolon
id|__exit_files
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|__exit_fs
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|exit_sighand
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|exit_thread
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;leader
)paren
id|disassociate_ctty
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|put_exec_domain
c_func
(paren
id|tsk-&gt;exec_domain
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;binfmt
op_logical_and
id|tsk-&gt;binfmt-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|tsk-&gt;binfmt-&gt;module
)paren
suffix:semicolon
id|tsk-&gt;exit_code
op_assign
id|code
suffix:semicolon
id|exit_notify
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * In order to get rid of the &quot;volatile function does return&quot; message&n; * I did this little loop that confuses gcc to think do_exit really&n; * is volatile. In fact it&squot;s schedule() that is volatile in some&n; * circumstances: when current-&gt;state = ZOMBIE, schedule() never&n; * returns.&n; *&n; * In fact the natural way to do all this is to have the label and the&n; * goto right after each other, but I put the fake_volatile label at&n; * the start of the function just in case something /really/ bad&n; * happens, and the schedule returns. This way we can try again. I&squot;m&n; * not paranoid: it&squot;s just that everybody is out to get me.&n; */
r_goto
id|fake_volatile
suffix:semicolon
)brace
DECL|function|complete_and_exit
id|NORET_TYPE
r_void
id|complete_and_exit
c_func
(paren
r_struct
id|completion
op_star
id|comp
comma
r_int
id|code
)paren
(brace
r_if
c_cond
(paren
id|comp
)paren
id|complete
c_func
(paren
id|comp
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|code
)paren
suffix:semicolon
)brace
DECL|function|sys_exit
id|asmlinkage
r_int
id|sys_exit
c_func
(paren
r_int
id|error_code
)paren
(brace
id|do_exit
c_func
(paren
(paren
id|error_code
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|sys_wait4
id|asmlinkage
r_int
id|sys_wait4
c_func
(paren
id|pid_t
id|pid
comma
r_int
r_int
op_star
id|stat_addr
comma
r_int
id|options
comma
r_struct
id|rusage
op_star
id|ru
)paren
(brace
r_int
id|flag
comma
id|retval
suffix:semicolon
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_if
c_cond
(paren
id|options
op_amp
op_complement
(paren
id|WNOHANG
op_or
id|WUNTRACED
op_or
id|__WNOTHREAD
op_or
id|__WCLONE
op_or
id|__WALL
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|current-&gt;wait_chldexit
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|flag
op_assign
l_int|0
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|tsk
op_assign
id|current
suffix:semicolon
r_do
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|tsk-&gt;p_cptr
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;p_osptr
)paren
(brace
r_if
c_cond
(paren
id|pid
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pid
op_ne
id|pid
)paren
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pgrp
op_ne
id|current-&gt;pgrp
)paren
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pid
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pgrp
op_ne
op_minus
id|pid
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/* Wait for all children (clone and not) if __WALL is set;&n;&t;&t;&t; * otherwise, wait for clone children *only* if __WCLONE is&n;&t;&t;&t; * set; otherwise, wait for non-clone children *only*.  (Note:&n;&t;&t;&t; * A &quot;clone&quot; child here is one that reports to its parent&n;&t;&t;&t; * using a signal other than SIGCHLD.) */
r_if
c_cond
(paren
(paren
(paren
id|p-&gt;exit_signal
op_ne
id|SIGCHLD
)paren
op_xor
(paren
(paren
id|options
op_amp
id|__WCLONE
)paren
op_ne
l_int|0
)paren
)paren
op_logical_and
op_logical_neg
(paren
id|options
op_amp
id|__WALL
)paren
)paren
r_continue
suffix:semicolon
id|flag
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|p-&gt;state
)paren
(brace
r_case
id|TASK_STOPPED
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;exit_code
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|options
op_amp
id|WUNTRACED
)paren
op_logical_and
op_logical_neg
(paren
id|p-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_continue
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|retval
op_assign
id|ru
ques
c_cond
id|getrusage
c_func
(paren
id|p
comma
id|RUSAGE_BOTH
comma
id|ru
)paren
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|stat_addr
)paren
id|retval
op_assign
id|put_user
c_func
(paren
(paren
id|p-&gt;exit_code
op_lshift
l_int|8
)paren
op_or
l_int|0x7f
comma
id|stat_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
id|p-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
id|p-&gt;pid
suffix:semicolon
)brace
r_goto
id|end_wait4
suffix:semicolon
r_case
id|TASK_ZOMBIE
suffix:colon
id|current-&gt;times.tms_cutime
op_add_assign
id|p-&gt;times.tms_utime
op_plus
id|p-&gt;times.tms_cutime
suffix:semicolon
id|current-&gt;times.tms_cstime
op_add_assign
id|p-&gt;times.tms_stime
op_plus
id|p-&gt;times.tms_cstime
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|retval
op_assign
id|ru
ques
c_cond
id|getrusage
c_func
(paren
id|p
comma
id|RUSAGE_BOTH
comma
id|ru
)paren
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|stat_addr
)paren
id|retval
op_assign
id|put_user
c_func
(paren
id|p-&gt;exit_code
comma
id|stat_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|end_wait4
suffix:semicolon
id|retval
op_assign
id|p-&gt;pid
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;p_opptr
op_ne
id|p-&gt;p_pptr
)paren
(brace
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|REMOVE_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|p-&gt;p_pptr
op_assign
id|p-&gt;p_opptr
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|do_notify_parent
c_func
(paren
id|p
comma
id|SIGCHLD
)paren
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
)brace
r_else
id|release_task
c_func
(paren
id|p
)paren
suffix:semicolon
r_goto
id|end_wait4
suffix:semicolon
r_default
suffix:colon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|options
op_amp
id|__WNOTHREAD
)paren
r_break
suffix:semicolon
id|tsk
op_assign
id|next_thread
c_func
(paren
id|tsk
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tsk
op_ne
id|current
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
id|flag
)paren
(brace
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|options
op_amp
id|WNOHANG
)paren
r_goto
id|end_wait4
suffix:semicolon
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|end_wait4
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|ECHILD
suffix:semicolon
id|end_wait4
suffix:colon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|current-&gt;wait_chldexit
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#if !defined(__alpha__) &amp;&amp; !defined(__ia64__)
multiline_comment|/*&n; * sys_waitpid() remains for compatibility. waitpid() should be&n; * implemented by calling sys_wait4() from libc.a.&n; */
DECL|function|sys_waitpid
id|asmlinkage
r_int
id|sys_waitpid
c_func
(paren
id|pid_t
id|pid
comma
r_int
r_int
op_star
id|stat_addr
comma
r_int
id|options
)paren
(brace
r_return
id|sys_wait4
c_func
(paren
id|pid
comma
id|stat_addr
comma
id|options
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
