multiline_comment|/*&n;&t;kmod, the new module loader (replaces kerneld)&n;&t;Kirk Petersen&n;&n;&t;Reorganized not to be a daemon by Adam Richter, with guidance&n;&t;from Greg Zornetzer.&n;&n;&t;Modified to avoid chroot and file sharing problems.&n;&t;Mikael Pettersson&n;&n;&t;Limit the concurrent number of kmod modprobes to catch loops from&n;&t;&quot;modprobe needs a service that is in a module&quot;.&n;&t;Keith Owens &lt;kaos@ocs.com.au&gt; December 1999&n;&n;&t;Unblock all signals when we exec a usermode process.&n;&t;Shuu Yamaguchi &lt;shuu@wondernetworkresources.com&gt; December 2000&n;*/
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_int
id|max_threads
suffix:semicolon
r_static
r_inline
r_void
DECL|function|use_init_fs_context
id|use_init_fs_context
c_func
(paren
r_void
)paren
(brace
r_struct
id|fs_struct
op_star
id|our_fs
comma
op_star
id|init_fs
suffix:semicolon
r_struct
id|dentry
op_star
id|root
comma
op_star
id|pwd
suffix:semicolon
r_struct
id|vfsmount
op_star
id|rootmnt
comma
op_star
id|pwdmnt
suffix:semicolon
multiline_comment|/*&n;&t; * Make modprobe&squot;s fs context be a copy of init&squot;s.&n;&t; *&n;&t; * We cannot use the user&squot;s fs context, because it&n;&t; * may have a different root than init.&n;&t; * Since init was created with CLONE_FS, we can grab&n;&t; * its fs context from &quot;init_task&quot;.&n;&t; *&n;&t; * The fs context has to be a copy. If it is shared&n;&t; * with init, then any chdir() call in modprobe will&n;&t; * also affect init and the other threads sharing&n;&t; * init_task&squot;s fs context.&n;&t; *&n;&t; * We created the exec_modprobe thread without CLONE_FS,&n;&t; * so we can update the fields in our fs context freely.&n;&t; */
id|init_fs
op_assign
id|init_task.fs
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|init_fs-&gt;lock
)paren
suffix:semicolon
id|rootmnt
op_assign
id|mntget
c_func
(paren
id|init_fs-&gt;rootmnt
)paren
suffix:semicolon
id|root
op_assign
id|dget
c_func
(paren
id|init_fs-&gt;root
)paren
suffix:semicolon
id|pwdmnt
op_assign
id|mntget
c_func
(paren
id|init_fs-&gt;pwdmnt
)paren
suffix:semicolon
id|pwd
op_assign
id|dget
c_func
(paren
id|init_fs-&gt;pwd
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|init_fs-&gt;lock
)paren
suffix:semicolon
multiline_comment|/* FIXME - unsafe -&gt;fs access */
id|our_fs
op_assign
id|current-&gt;fs
suffix:semicolon
id|our_fs-&gt;umask
op_assign
id|init_fs-&gt;umask
suffix:semicolon
id|set_fs_root
c_func
(paren
id|our_fs
comma
id|rootmnt
comma
id|root
)paren
suffix:semicolon
id|set_fs_pwd
c_func
(paren
id|our_fs
comma
id|pwdmnt
comma
id|pwd
)paren
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|our_fs-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|our_fs-&gt;altroot
)paren
(brace
r_struct
id|vfsmount
op_star
id|mnt
op_assign
id|our_fs-&gt;altrootmnt
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
id|our_fs-&gt;altroot
suffix:semicolon
id|our_fs-&gt;altrootmnt
op_assign
l_int|NULL
suffix:semicolon
id|our_fs-&gt;altroot
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|our_fs-&gt;lock
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|mnt
)paren
suffix:semicolon
)brace
r_else
id|write_unlock
c_func
(paren
op_amp
id|our_fs-&gt;lock
)paren
suffix:semicolon
id|dput
c_func
(paren
id|root
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|rootmnt
)paren
suffix:semicolon
id|dput
c_func
(paren
id|pwd
)paren
suffix:semicolon
id|mntput
c_func
(paren
id|pwdmnt
)paren
suffix:semicolon
)brace
DECL|function|exec_usermodehelper
r_int
id|exec_usermodehelper
c_func
(paren
r_char
op_star
id|program_path
comma
r_char
op_star
id|argv
(braket
)braket
comma
r_char
op_star
id|envp
(braket
)braket
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|task_struct
op_star
id|curtask
op_assign
id|current
suffix:semicolon
id|curtask-&gt;session
op_assign
l_int|1
suffix:semicolon
id|curtask-&gt;pgrp
op_assign
l_int|1
suffix:semicolon
id|use_init_fs_context
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Prevent parent user process from sending signals to child.&n;&t;   Otherwise, if the modprobe program does not exist, it might&n;&t;   be possible to get a user defined signal handler to execute&n;&t;   as the super user right after the execve fails if you time&n;&t;   the signal just right.&n;&t;*/
id|spin_lock_irq
c_func
(paren
op_amp
id|curtask-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|curtask-&gt;blocked
)paren
suffix:semicolon
id|flush_signals
c_func
(paren
id|curtask
)paren
suffix:semicolon
id|flush_signal_handlers
c_func
(paren
id|curtask
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|curtask
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|curtask-&gt;sigmask_lock
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
id|curtask-&gt;files-&gt;max_fds
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|curtask-&gt;files-&gt;fd
(braket
id|i
)braket
)paren
id|close
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* Drop the &quot;current user&quot; thing */
(brace
r_struct
id|user_struct
op_star
id|user
op_assign
id|curtask-&gt;user
suffix:semicolon
id|curtask-&gt;user
op_assign
id|INIT_USER
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|INIT_USER-&gt;__count
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|INIT_USER-&gt;processes
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|user-&gt;processes
)paren
suffix:semicolon
id|free_uid
c_func
(paren
id|user
)paren
suffix:semicolon
)brace
multiline_comment|/* Give kmod all effective privileges.. */
id|curtask-&gt;euid
op_assign
id|curtask-&gt;fsuid
op_assign
l_int|0
suffix:semicolon
id|curtask-&gt;egid
op_assign
id|curtask-&gt;fsgid
op_assign
l_int|0
suffix:semicolon
id|cap_set_full
c_func
(paren
id|curtask-&gt;cap_effective
)paren
suffix:semicolon
multiline_comment|/* Allow execve args to be in kernel space. */
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
multiline_comment|/* Go, go, go... */
r_if
c_cond
(paren
id|execve
c_func
(paren
id|program_path
comma
id|argv
comma
id|envp
)paren
OL
l_int|0
)paren
r_return
op_minus
id|errno
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_KMOD
multiline_comment|/*&n;&t;modprobe_path is set via /proc/sys.&n;*/
DECL|variable|modprobe_path
r_char
id|modprobe_path
(braket
l_int|256
)braket
op_assign
l_string|&quot;/sbin/modprobe&quot;
suffix:semicolon
DECL|function|exec_modprobe
r_static
r_int
id|exec_modprobe
c_func
(paren
r_void
op_star
id|module_name
)paren
(brace
r_static
r_char
op_star
id|envp
(braket
)braket
op_assign
(brace
l_string|&quot;HOME=/&quot;
comma
l_string|&quot;TERM=linux&quot;
comma
l_string|&quot;PATH=/sbin:/usr/sbin:/bin:/usr/bin&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
id|modprobe_path
comma
l_string|&quot;-s&quot;
comma
l_string|&quot;-k&quot;
comma
l_string|&quot;--&quot;
comma
(paren
r_char
op_star
)paren
id|module_name
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|exec_usermodehelper
c_func
(paren
id|modprobe_path
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kmod: failed to exec %s -s -k %s, errno = %d&bslash;n&quot;
comma
id|modprobe_path
comma
(paren
r_char
op_star
)paren
id|module_name
comma
id|errno
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**&n; * request_module - try to load a kernel module&n; * @module_name: Name of module&n; *&n; * Load a module using the user mode module loader. The function returns&n; * zero on success or a negative errno code on failure. Note that a&n; * successful module load does not mean the module did not then unload&n; * and exit on an error of its own. Callers must check that the service&n; * they requested is now available not blindly invoke it.&n; *&n; * If module auto-loading support is disabled then this function&n; * becomes a no-operation.&n; */
DECL|function|request_module
r_int
id|request_module
c_func
(paren
r_const
r_char
op_star
id|module_name
)paren
(brace
id|pid_t
id|pid
suffix:semicolon
r_int
id|waitpid_result
suffix:semicolon
id|sigset_t
id|tmpsig
suffix:semicolon
r_int
id|i
suffix:semicolon
r_static
id|atomic_t
id|kmod_concurrent
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|macro|MAX_KMOD_CONCURRENT
mdefine_line|#define MAX_KMOD_CONCURRENT 50&t;/* Completely arbitrary value - KAO */
r_static
r_int
id|kmod_loop_msg
suffix:semicolon
multiline_comment|/* Don&squot;t allow request_module() before the root fs is mounted!  */
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;fs-&gt;root
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_module[%s]: Root fs not mounted&bslash;n&quot;
comma
id|module_name
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
multiline_comment|/* If modprobe needs a service that is in a module, we get a recursive&n;&t; * loop.  Limit the number of running kmod threads to max_threads/2 or&n;&t; * MAX_KMOD_CONCURRENT, whichever is the smaller.  A cleaner method&n;&t; * would be to run the parents of this process, counting how many times&n;&t; * kmod was invoked.  That would mean accessing the internals of the&n;&t; * process tables to get the command line, proc_pid_cmdline is static&n;&t; * and it is not worth changing the proc code just to handle this case. &n;&t; * KAO.&n;&t; */
id|i
op_assign
id|max_threads
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|MAX_KMOD_CONCURRENT
)paren
id|i
op_assign
id|MAX_KMOD_CONCURRENT
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|kmod_concurrent
)paren
OG
id|i
)paren
(brace
r_if
c_cond
(paren
id|kmod_loop_msg
op_increment
OL
l_int|5
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;kmod: runaway modprobe loop assumed and stopped&bslash;n&quot;
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|exec_modprobe
comma
(paren
r_void
op_star
)paren
id|module_name
comma
l_int|0
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_module[%s]: fork failed, errno %d&bslash;n&quot;
comma
id|module_name
comma
op_minus
id|pid
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
multiline_comment|/* Block everything but SIGKILL/SIGSTOP */
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|tmpsig
op_assign
id|current-&gt;blocked
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|sigmask
c_func
(paren
id|SIGKILL
)paren
op_or
id|sigmask
c_func
(paren
id|SIGSTOP
)paren
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|waitpid_result
op_assign
id|waitpid
c_func
(paren
id|pid
comma
l_int|NULL
comma
id|__WCLONE
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
multiline_comment|/* Allow signals again.. */
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|tmpsig
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitpid_result
op_ne
id|pid
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;request_module[%s]: waitpid(%d,...) failed, errno %d&bslash;n&quot;
comma
id|module_name
comma
id|pid
comma
op_minus
id|waitpid_result
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_KMOD */
macro_line|#ifdef CONFIG_HOTPLUG
multiline_comment|/*&n;&t;hotplug path is set via /proc/sys&n;&t;invoked by hotplug-aware bus drivers,&n;&t;with exec_usermodehelper and some thread-spawner&n;&n;&t;argv [0] = hotplug_path;&n;&t;argv [1] = &quot;usb&quot;, &quot;scsi&quot;, &quot;pci&quot;, &quot;network&quot;, etc;&n;&t;... plus optional type-specific parameters&n;&t;argv [n] = 0;&n;&n;&t;envp [*] = HOME, PATH; optional type-specific parameters&n;&n;&t;a hotplug bus should invoke this for device add/remove&n;&t;events.  the command is expected to load drivers when&n;&t;necessary, and may perform additional system setup.&n;*/
DECL|variable|hotplug_path
r_char
id|hotplug_path
(braket
l_int|256
)braket
op_assign
l_string|&quot;/sbin/hotplug&quot;
suffix:semicolon
DECL|variable|hotplug_path
id|EXPORT_SYMBOL
c_func
(paren
id|hotplug_path
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_HOTPLUG */
DECL|struct|subprocess_info
r_struct
id|subprocess_info
(brace
DECL|member|complete
r_struct
id|completion
op_star
id|complete
suffix:semicolon
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
DECL|member|argv
r_char
op_star
op_star
id|argv
suffix:semicolon
DECL|member|envp
r_char
op_star
op_star
id|envp
suffix:semicolon
DECL|member|retval
id|pid_t
id|retval
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This is the task which runs the usermode application&n; */
DECL|function|____call_usermodehelper
r_static
r_int
id|____call_usermodehelper
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|subprocess_info
op_star
id|sub_info
op_assign
id|data
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|retval
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;fs-&gt;root
)paren
id|retval
op_assign
id|exec_usermodehelper
c_func
(paren
id|sub_info-&gt;path
comma
id|sub_info-&gt;argv
comma
id|sub_info-&gt;envp
)paren
suffix:semicolon
multiline_comment|/* Exec failed? */
id|sub_info-&gt;retval
op_assign
(paren
id|pid_t
)paren
id|retval
suffix:semicolon
id|do_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is run by keventd.&n; */
DECL|function|__call_usermodehelper
r_static
r_void
id|__call_usermodehelper
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|subprocess_info
op_star
id|sub_info
op_assign
id|data
suffix:semicolon
id|pid_t
id|pid
suffix:semicolon
multiline_comment|/*&n;&t; * CLONE_VFORK: wait until the usermode helper has execve&squot;d successfully&n;&t; * We need the data structures to stay around until that is done.&n;&t; */
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|____call_usermodehelper
comma
id|sub_info
comma
id|CLONE_VFORK
op_or
id|SIGCHLD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
id|sub_info-&gt;retval
op_assign
id|pid
suffix:semicolon
id|complete
c_func
(paren
id|sub_info-&gt;complete
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * call_usermodehelper - start a usermode application&n; * @path: pathname for the application&n; * @argv: null-terminated argument list&n; * @envp: null-terminated environment list&n; *&n; * Runs a user-space application.  The application is started asynchronously.  It&n; * runs as a child of keventd.  It runs with full root capabilities.  keventd silently&n; * reaps the child when it exits.&n; *&n; * Must be called from process context.  Returns zero on success, else a negative&n; * error code.&n; */
DECL|function|call_usermodehelper
r_int
id|call_usermodehelper
c_func
(paren
r_char
op_star
id|path
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
id|DECLARE_COMPLETION
c_func
(paren
id|work
)paren
suffix:semicolon
r_struct
id|subprocess_info
id|sub_info
op_assign
(brace
id|complete
suffix:colon
op_amp
id|work
comma
id|path
suffix:colon
id|path
comma
id|argv
suffix:colon
id|argv
comma
id|envp
suffix:colon
id|envp
comma
id|retval
suffix:colon
l_int|0
comma
)brace
suffix:semicolon
r_struct
id|tq_struct
id|tqs
op_assign
(brace
id|routine
suffix:colon
id|__call_usermodehelper
comma
id|data
suffix:colon
op_amp
id|sub_info
comma
)brace
suffix:semicolon
r_if
c_cond
(paren
id|path
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|current_is_keventd
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* We can&squot;t wait on keventd! */
id|__call_usermodehelper
c_func
(paren
op_amp
id|sub_info
)paren
suffix:semicolon
)brace
r_else
(brace
id|schedule_task
c_func
(paren
op_amp
id|tqs
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|work
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|sub_info.retval
suffix:semicolon
)brace
multiline_comment|/*&n; * This is for the serialisation of device probe() functions&n; * against device open() functions&n; */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|dev_probe_sem
)paren
suffix:semicolon
DECL|function|dev_probe_lock
r_void
id|dev_probe_lock
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|dev_probe_sem
)paren
suffix:semicolon
)brace
DECL|function|dev_probe_unlock
r_void
id|dev_probe_unlock
c_func
(paren
r_void
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev_probe_sem
)paren
suffix:semicolon
)brace
DECL|variable|exec_usermodehelper
id|EXPORT_SYMBOL
c_func
(paren
id|exec_usermodehelper
)paren
suffix:semicolon
DECL|variable|call_usermodehelper
id|EXPORT_SYMBOL
c_func
(paren
id|call_usermodehelper
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
DECL|variable|request_module
id|EXPORT_SYMBOL
c_func
(paren
id|request_module
)paren
suffix:semicolon
macro_line|#endif
eof
