macro_line|#ifndef _LINUX__INIT_TASK_H
DECL|macro|_LINUX__INIT_TASK_H
mdefine_line|#define _LINUX__INIT_TASK_H
macro_line|#include &lt;linux/file.h&gt;
DECL|macro|INIT_FILES
mdefine_line|#define INIT_FILES &bslash;&n;{ &t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.count&t;&t;= ATOMIC_INIT(1), &t;&t;&bslash;&n;&t;.file_lock&t;= SPIN_LOCK_UNLOCKED, &t;&t;&bslash;&n;&t;.max_fds&t;= NR_OPEN_DEFAULT, &t;&t;&bslash;&n;&t;.max_fdset&t;= __FD_SETSIZE, &t;&t;&bslash;&n;&t;.next_fd&t;= 0, &t;&t;&t;&t;&bslash;&n;&t;.fd&t;&t;= &amp;init_files.fd_array[0], &t;&bslash;&n;&t;.close_on_exec&t;= &amp;init_files.close_on_exec_init, &bslash;&n;&t;.open_fds&t;= &amp;init_files.open_fds_init, &t;&bslash;&n;&t;.close_on_exec_init = { { 0, } }, &t;&t;&bslash;&n;&t;.open_fds_init&t;= { { 0, } }, &t;&t;&t;&bslash;&n;&t;.fd_array&t;= { NULL, } &t;&t;&t;&bslash;&n;}
DECL|macro|INIT_KIOCTX
mdefine_line|#define INIT_KIOCTX(name, which_mm) &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.users&t;&t;= ATOMIC_INIT(1),&t;&t;&bslash;&n;&t;.dead&t;&t;= 0,&t;&t;&t;&t;&bslash;&n;&t;.mm&t;&t;= &amp;which_mm,&t;&t;&t;&bslash;&n;&t;.user_id&t;= 0,&t;&t;&t;&t;&bslash;&n;&t;.next&t;&t;= NULL,&t;&t;&t;&t;&bslash;&n;&t;.wait&t;&t;= __WAIT_QUEUE_HEAD_INITIALIZER(name.wait), &bslash;&n;&t;.ctx_lock&t;= SPIN_LOCK_UNLOCKED,&t;&t;&bslash;&n;&t;.reqs_active&t;= 0U,&t;&t;&t;&t;&bslash;&n;&t;.max_reqs&t;= ~0U,&t;&t;&t;&t;&bslash;&n;}
DECL|macro|INIT_MM
mdefine_line|#define INIT_MM(name) &bslash;&n;{&t;&t;&t; &t;&t;&t;&t;&t;&bslash;&n;&t;.mm_rb&t;&t;= RB_ROOT,&t;&t;&t;&t;&bslash;&n;&t;.pgd&t;&t;= swapper_pg_dir, &t;&t;&t;&bslash;&n;&t;.mm_users&t;= ATOMIC_INIT(2), &t;&t;&t;&bslash;&n;&t;.mm_count&t;= ATOMIC_INIT(1), &t;&t;&t;&bslash;&n;&t;.mmap_sem&t;= __RWSEM_INITIALIZER(name.mmap_sem),&t;&bslash;&n;&t;.page_table_lock =  SPIN_LOCK_UNLOCKED, &t;&t;&bslash;&n;&t;.mmlist&t;&t;= LIST_HEAD_INIT(name.mmlist),&t;&t;&bslash;&n;&t;.cpu_vm_mask&t;= CPU_MASK_ALL,&t;&t;&t;&t;&bslash;&n;&t;.default_kioctx = INIT_KIOCTX(name.default_kioctx, name),&t;&bslash;&n;}
DECL|macro|INIT_SIGNALS
mdefine_line|#define INIT_SIGNALS(sig) {&t;&bslash;&n;&t;.count&t;&t;= ATOMIC_INIT(1), &t;&t;&bslash;&n;&t;.wait_chldexit&t;= __WAIT_QUEUE_HEAD_INITIALIZER(sig.wait_chldexit),&bslash;&n;&t;.shared_pending&t;= { &t;&t;&t;&t;&bslash;&n;&t;&t;.list = LIST_HEAD_INIT(sig.shared_pending.list),&t;&bslash;&n;&t;&t;.signal =  {{0}}}, &bslash;&n;&t;.posix_timers&t; = LIST_HEAD_INIT(sig.posix_timers),&t;&t;&bslash;&n;&t;.rlim&t;&t;= INIT_RLIMITS,&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|INIT_SIGHAND
mdefine_line|#define INIT_SIGHAND(sighand) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.count&t;&t;= ATOMIC_INIT(1), &t;&t;&t;&t;&bslash;&n;&t;.action&t;&t;= { { { .sa_handler = NULL, } }, },&t;&t;&bslash;&n;&t;.siglock&t;= SPIN_LOCK_UNLOCKED, &t;&t;&t;&t;&bslash;&n;}
r_extern
r_struct
id|group_info
id|init_groups
suffix:semicolon
multiline_comment|/*&n; *  INIT_TASK is used to set up the first task table, touch at&n; * your own risk!. Base=0, limit=0x1fffff (=2MB)&n; */
DECL|macro|INIT_TASK
mdefine_line|#define INIT_TASK(tsk)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.state&t;&t;= 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.thread_info&t;= &amp;init_thread_info,&t;&t;&t;&t;&bslash;&n;&t;.usage&t;&t;= ATOMIC_INIT(2),&t;&t;&t;&t;&bslash;&n;&t;.flags&t;&t;= 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.lock_depth&t;= -1,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.prio&t;&t;= MAX_PRIO-20,&t;&t;&t;&t;&t;&bslash;&n;&t;.static_prio&t;= MAX_PRIO-20,&t;&t;&t;&t;&t;&bslash;&n;&t;.policy&t;&t;= SCHED_NORMAL,&t;&t;&t;&t;&t;&bslash;&n;&t;.cpus_allowed&t;= CPU_MASK_ALL,&t;&t;&t;&t;&t;&bslash;&n;&t;.mm&t;&t;= NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.active_mm&t;= &amp;init_mm,&t;&t;&t;&t;&t;&bslash;&n;&t;.run_list&t;= LIST_HEAD_INIT(tsk.run_list),&t;&t;&t;&bslash;&n;&t;.time_slice&t;= HZ,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.tasks&t;&t;= LIST_HEAD_INIT(tsk.tasks),&t;&t;&t;&bslash;&n;&t;.ptrace_children= LIST_HEAD_INIT(tsk.ptrace_children),&t;&t;&bslash;&n;&t;.ptrace_list&t;= LIST_HEAD_INIT(tsk.ptrace_list),&t;&t;&bslash;&n;&t;.real_parent&t;= &amp;tsk,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.parent&t;&t;= &amp;tsk,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.children&t;= LIST_HEAD_INIT(tsk.children),&t;&t;&t;&bslash;&n;&t;.sibling&t;= LIST_HEAD_INIT(tsk.sibling),&t;&t;&t;&bslash;&n;&t;.group_leader&t;= &amp;tsk,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.real_timer&t;= {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.function&t;= it_real_fn&t;&t;&t;&t;&bslash;&n;&t;},&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.group_info&t;= &amp;init_groups,&t;&t;&t;&t;&t;&bslash;&n;&t;.cap_effective&t;= CAP_INIT_EFF_SET,&t;&t;&t;&t;&bslash;&n;&t;.cap_inheritable = CAP_INIT_INH_SET,&t;&t;&t;&t;&bslash;&n;&t;.cap_permitted&t;= CAP_FULL_SET,&t;&t;&t;&t;&t;&bslash;&n;&t;.keep_capabilities = 0,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.user&t;&t;= INIT_USER,&t;&t;&t;&t;&t;&bslash;&n;&t;.comm&t;&t;= &quot;swapper&quot;,&t;&t;&t;&t;&t;&bslash;&n;&t;.thread&t;&t;= INIT_THREAD,&t;&t;&t;&t;&t;&bslash;&n;&t;.fs&t;&t;= &amp;init_fs,&t;&t;&t;&t;&t;&bslash;&n;&t;.files&t;&t;= &amp;init_files,&t;&t;&t;&t;&t;&bslash;&n;&t;.signal&t;&t;= &amp;init_signals,&t;&t;&t;&t;&bslash;&n;&t;.sighand&t;= &amp;init_sighand,&t;&t;&t;&t;&bslash;&n;&t;.pending&t;= {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.list = LIST_HEAD_INIT(tsk.pending.list),&t;&t;&bslash;&n;&t;&t;.signal = {{0}}},&t;&t;&t;&t;&t;&bslash;&n;&t;.blocked&t;= {{0}},&t;&t;&t;&t;&t;&bslash;&n;&t;.alloc_lock&t;= SPIN_LOCK_UNLOCKED,&t;&t;&t;&t;&bslash;&n;&t;.proc_lock&t;= SPIN_LOCK_UNLOCKED,&t;&t;&t;&t;&bslash;&n;&t;.switch_lock&t;= SPIN_LOCK_UNLOCKED,&t;&t;&t;&t;&bslash;&n;&t;.journal_info&t;= NULL,&t;&t;&t;&t;&t;&t;&bslash;&n;}
macro_line|#endif
eof
