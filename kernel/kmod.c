multiline_comment|/*&n;&t;kmod, the new module loader (replaces kerneld)&n;&t;Kirk Petersen&n;&n;&t;Reorganized not to be a daemon by Adam Richter, with guidance&n;&t;from Greg Zornetzer.&n;&n;&t;Modified to avoid chroot and file sharing problems.&n;&t;Mikael Pettersson&n;&n;&t;Limit the concurrent number of kmod modprobes to catch loops from&n;&t;&quot;modprobe needs a service that is in a module&quot;.&n;&t;Keith Owens &lt;kaos@ocs.com.au&gt; December 1999&n;&n;&t;Unblock all signals when we exec a usermode process.&n;&t;Shuu Yamaguchi &lt;shuu@wondernetworkresources.com&gt; December 2000&n;&n;&t;call_usermodehelper wait flag, and remove exec_usermodehelper.&n;&t;Rusty Russell &lt;rusty@rustcorp.com.au&gt;  Jan 2003&n;*/
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/namespace.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/workqueue.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
r_extern
r_int
id|max_threads
comma
id|system_running
suffix:semicolon
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
multiline_comment|/**&n; * request_module - try to load a kernel module&n; * @module_name: Name of module&n; *&n; * Load a module using the user mode module loader. The function returns&n; * zero on success or a negative errno code on failure. Note that a&n; * successful module load does not mean the module did not then unload&n; * and exit on an error of its own. Callers must check that the service&n; * they requested is now available not blindly invoke it.&n; *&n; * If module auto-loading support is disabled then this function&n; * becomes a no-operation.&n; */
DECL|macro|MODULENAME_SIZE
mdefine_line|#define MODULENAME_SIZE 32
DECL|function|request_module
r_int
id|request_module
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
id|module_name
(braket
id|MODULENAME_SIZE
)braket
suffix:semicolon
r_int
r_int
id|max_modprobes
suffix:semicolon
r_int
id|ret
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
l_string|&quot;--&quot;
comma
id|module_name
comma
l_int|NULL
)brace
suffix:semicolon
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
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|ret
op_assign
id|vsnprintf
c_func
(paren
id|module_name
comma
id|MODULENAME_SIZE
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
id|MODULENAME_SIZE
)paren
r_return
op_minus
id|ENAMETOOLONG
suffix:semicolon
multiline_comment|/* If modprobe needs a service that is in a module, we get a recursive&n;&t; * loop.  Limit the number of running kmod threads to max_threads/2 or&n;&t; * MAX_KMOD_CONCURRENT, whichever is the smaller.  A cleaner method&n;&t; * would be to run the parents of this process, counting how many times&n;&t; * kmod was invoked.  That would mean accessing the internals of the&n;&t; * process tables to get the command line, proc_pid_cmdline is static&n;&t; * and it is not worth changing the proc code just to handle this case. &n;&t; * KAO.&n;&t; *&n;&t; * &quot;trace the ppid&quot; is simple, but will fail if someone&squot;s&n;&t; * parent exits.  I think this is as good as it gets. --RR&n;&t; */
id|max_modprobes
op_assign
id|min
c_func
(paren
id|max_threads
op_div
l_int|2
comma
id|MAX_KMOD_CONCURRENT
)paren
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
id|max_modprobes
)paren
(brace
multiline_comment|/* We may be blaming an innocent here, but unlikely */
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
l_string|&quot;request_module: runaway loop modprobe %s&bslash;n&quot;
comma
id|module_name
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
id|ret
op_assign
id|call_usermodehelper
c_func
(paren
id|modprobe_path
comma
id|argv
comma
id|envp
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
r_static
r_int
r_int
id|last
suffix:semicolon
r_int
r_int
id|now
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|now
op_minus
id|last
OG
id|HZ
)paren
(brace
id|last
op_assign
id|now
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;request_module: failed %s -- %s. error = %d&bslash;n&quot;
comma
id|modprobe_path
comma
id|module_name
comma
id|ret
)paren
suffix:semicolon
)brace
)brace
id|atomic_dec
c_func
(paren
op_amp
id|kmod_concurrent
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_KMOD */
macro_line|#ifdef CONFIG_HOTPLUG
multiline_comment|/*&n;&t;hotplug path is set via /proc/sys&n;&t;invoked by hotplug-aware bus drivers,&n;&t;with call_usermodehelper&n;&n;&t;argv [0] = hotplug_path;&n;&t;argv [1] = &quot;usb&quot;, &quot;scsi&quot;, &quot;pci&quot;, &quot;network&quot;, etc;&n;&t;... plus optional type-specific parameters&n;&t;argv [n] = 0;&n;&n;&t;envp [*] = HOME, PATH; optional type-specific parameters&n;&n;&t;a hotplug bus should invoke this for device add/remove&n;&t;events.  the command is expected to load drivers when&n;&t;necessary, and may perform additional system setup.&n;*/
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
DECL|member|wait
r_int
id|wait
suffix:semicolon
DECL|member|retval
r_int
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
multiline_comment|/* Unblock all signals. */
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|flush_signal_handlers
c_func
(paren
id|current
comma
l_int|1
)paren
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
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
id|execve
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
id|retval
suffix:semicolon
id|do_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Keventd can&squot;t block, but this (a child) can. */
DECL|function|wait_for_helper
r_static
r_int
id|wait_for_helper
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
r_else
id|sys_wait4
c_func
(paren
id|pid
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|sub_info-&gt;retval
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|complete
c_func
(paren
id|sub_info-&gt;complete
)paren
suffix:semicolon
r_return
l_int|0
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
multiline_comment|/* CLONE_VFORK: wait until the usermode helper has execve&squot;d&n;&t; * successfully We need the data structures to stay around&n;&t; * until that is done.  */
r_if
c_cond
(paren
id|sub_info-&gt;wait
)paren
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|wait_for_helper
comma
id|sub_info
comma
id|CLONE_KERNEL
op_or
id|SIGCHLD
)paren
suffix:semicolon
r_else
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
(brace
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
r_else
r_if
c_cond
(paren
op_logical_neg
id|sub_info-&gt;wait
)paren
id|complete
c_func
(paren
id|sub_info-&gt;complete
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * call_usermodehelper - start a usermode application&n; * @path: pathname for the application&n; * @argv: null-terminated argument list&n; * @envp: null-terminated environment list&n; * @wait: wait for the application to finish and return status.&n; *&n; * Runs a user-space application.  The application is started&n; * asynchronously if wait is not set, and runs as a child of keventd.&n; * (ie. it runs with full root capabilities).&n; *&n; * Must be called from process context.  Returns a negative error code&n; * if program was not execed successfully, or (exitcode &lt;&lt; 8 + signal)&n; * of the application (0 if wait is not set).&n; */
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
comma
r_int
id|wait
)paren
(brace
id|DECLARE_COMPLETION
c_func
(paren
id|done
)paren
suffix:semicolon
r_struct
id|subprocess_info
id|sub_info
op_assign
(brace
dot
id|complete
op_assign
op_amp
id|done
comma
dot
id|path
op_assign
id|path
comma
dot
id|argv
op_assign
id|argv
comma
dot
id|envp
op_assign
id|envp
comma
dot
id|wait
op_assign
id|wait
comma
dot
id|retval
op_assign
l_int|0
comma
)brace
suffix:semicolon
id|DECLARE_WORK
c_func
(paren
id|work
comma
id|__call_usermodehelper
comma
op_amp
id|sub_info
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|system_running
)paren
r_return
op_minus
id|EBUSY
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
id|schedule_work
c_func
(paren
op_amp
id|work
)paren
suffix:semicolon
id|wait_for_completion
c_func
(paren
op_amp
id|done
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
