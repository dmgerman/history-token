multiline_comment|/*&n; *  linux/arch/parisc/kernel/process.c&n; *&t;based on the work for i386&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/offsets.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/pdc_chassis.h&gt;
DECL|variable|hlt_counter
r_int
id|hlt_counter
suffix:semicolon
multiline_comment|/*&n; * Power off function, if any&n; */
DECL|variable|pm_power_off
r_void
(paren
op_star
id|pm_power_off
)paren
(paren
r_void
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
id|hlt_counter
op_increment
suffix:semicolon
)brace
DECL|function|enable_hlt
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_decrement
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
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef __LP64__
DECL|macro|COMMAND_GLOBAL
mdefine_line|#define COMMAND_GLOBAL  0xfffffffffffe0030UL
macro_line|#else
DECL|macro|COMMAND_GLOBAL
mdefine_line|#define COMMAND_GLOBAL  0xfffe0030
macro_line|#endif
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET       5       /* reset any module */
multiline_comment|/*&n;** The Wright Brothers and Gecko systems have a H/W problem&n;** (Lasi...&squot;nuf said) may cause a broadcast reset to lockup&n;** the system. An HVERSION dependent PDC call was developed&n;** to perform a &quot;safe&quot;, platform specific broadcast reset instead&n;** of kludging up all the code.&n;**&n;** Older machines which do not implement PDC_BROADCAST_RESET will&n;** return (with an error) and the regular broadcast reset can be&n;** issued. Obviously, if the PDC does implement PDC_BROADCAST_RESET&n;** the PDC call will not return (the system will be reset).&n;*/
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
macro_line|#ifdef FASTBOOT_SELFTEST_SUPPORT
multiline_comment|/*&n;&t; ** If user has modified the Firmware Selftest Bitmap,&n;&t; ** run the tests specified in the bitmap after the&n;&t; ** system is rebooted w/PDC_DO_RESET.&n;&t; **&n;&t; ** ftc_bitmap = 0x1AUL &quot;Skip destructive memory tests&quot;&n;&t; **&n;&t; ** Using &quot;directed resets&quot; at each processor with the MEM_TOC&n;&t; ** vector cleared will also avoid running destructive&n;&t; ** memory self tests. (Not implemented yet)&n;&t; */
r_if
c_cond
(paren
id|ftc_bitmap
)paren
(brace
id|pdc_do_firm_test_reset
c_func
(paren
id|ftc_bitmap
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* set up a new led state on systems shipped with a LED State panel */
id|pdc_chassis_send_status
c_func
(paren
id|PDC_CHASSIS_DIRECT_SHUTDOWN
)paren
suffix:semicolon
multiline_comment|/* &quot;Normal&quot; system reset */
id|pdc_do_reset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Nope...box should reset with just CMD_RESET now */
id|gsc_writel
c_func
(paren
id|CMD_RESET
comma
id|COMMAND_GLOBAL
)paren
suffix:semicolon
multiline_comment|/* Wait for RESET to lay us to rest. */
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t;** The LED/ChassisCodes are updated by the led_halt()&n;&t;** function, called by the reboot notifier chain.&n;&t;*/
)brace
multiline_comment|/*&n; * This routine is called from sys_reboot to actually turn off the&n; * machine &n; */
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* If there is a registered power off handler, call it. */
r_if
c_cond
(paren
id|pm_power_off
)paren
(brace
id|pm_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Put the soft power button back under hardware control.&n;&t; * If the user had already pressed the power button, the&n;&t; * following call will immediately power off. */
id|pdc_soft_power_button
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|pdc_chassis_send_status
c_func
(paren
id|PDC_CHASSIS_DIRECT_SHUTDOWN
)paren
suffix:semicolon
multiline_comment|/* It seems we have no way to power the system off via&n;&t; * software. The user has to press the button himself. */
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;System shut down completed.&bslash;n&quot;
id|KERN_EMERG
l_string|&quot;Please power this system off now.&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a kernel thread&n; */
r_extern
id|pid_t
id|__kernel_thread
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
suffix:semicolon
DECL|function|kernel_thread
id|pid_t
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
multiline_comment|/*&n;&t; * FIXME: Once we are sure we don&squot;t need any debug here,&n;&t; *&t;  kernel_thread can become a #define.&n;&t; */
r_return
id|__kernel_thread
c_func
(paren
id|fn
comma
id|arg
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Only needs to handle fpu stuff or perf monitors.&n;&t;** REVISIT: several arches implement a &quot;lazy fpu state&quot;.&n;&t;*/
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
)brace
DECL|function|release_thread
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
)brace
multiline_comment|/*&n; * Fill in the FPU structure for a core dump.&n; */
DECL|function|dump_fpu
r_int
id|dump_fpu
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|r
)paren
(brace
id|memcpy
c_func
(paren
id|r
comma
id|regs-&gt;fr
comma
r_sizeof
op_star
id|r
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Note that &quot;fork()&quot; is implemented in terms of clone, with&n;   parameters (SIGCHLD, regs-&gt;gr[30], regs). */
r_int
DECL|function|sys_clone
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
op_star
id|user_tid
op_assign
(paren
r_int
op_star
)paren
id|regs-&gt;gr
(braket
l_int|26
)braket
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|clone_flags
op_amp
op_complement
id|CLONE_IDLETASK
comma
id|usp
comma
id|regs
comma
l_int|0
comma
id|user_tid
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
r_int
DECL|function|sys_vfork
id|sys_vfork
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|regs-&gt;gr
(braket
l_int|30
)braket
comma
id|regs
comma
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
r_int
DECL|function|copy_thread
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
id|usp
comma
r_int
r_int
id|unused
comma
multiline_comment|/* in ia64 this is &quot;user_stack_size&quot; */
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|pregs
)paren
(brace
r_struct
id|pt_regs
op_star
id|cregs
op_assign
op_amp
(paren
id|p-&gt;thread.regs
)paren
suffix:semicolon
r_struct
id|thread_info
op_star
id|ti
op_assign
id|p-&gt;thread_info
suffix:semicolon
multiline_comment|/* We have to use void * instead of a function pointer, because&n;&t; * function pointers aren&squot;t a pointer to the function on 64-bit.&n;&t; * Make them const so the compiler knows they live in .text */
r_extern
r_void
op_star
r_const
id|ret_from_kernel_thread
suffix:semicolon
r_extern
r_void
op_star
r_const
id|child_return
suffix:semicolon
r_extern
r_void
op_star
r_const
id|hpux_child_return
suffix:semicolon
op_star
id|cregs
op_assign
op_star
id|pregs
suffix:semicolon
multiline_comment|/* Set the return value for the child.  Note that this is not&n;           actually restored by the syscall exit path, but we put it&n;           here for consistency in case of signals. */
id|cregs-&gt;gr
(braket
l_int|28
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* child */
multiline_comment|/*&n;&t; * We need to differentiate between a user fork and a&n;&t; * kernel fork. We can&squot;t use user_mode, because the&n;&t; * the syscall path doesn&squot;t save iaoq. Right now&n;&t; * We rely on the fact that kernel_thread passes&n;&t; * in zero for usp.&n;&t; */
r_if
c_cond
(paren
id|usp
op_eq
l_int|0
)paren
(brace
multiline_comment|/* kernel thread */
id|cregs-&gt;ksp
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|ti
)paren
)paren
op_plus
id|THREAD_SZ_ALGN
)paren
suffix:semicolon
multiline_comment|/* Must exit via ret_from_kernel_thread in order&n;&t;&t; * to call schedule_tail()&n;&t;&t; */
id|cregs-&gt;kpc
op_assign
(paren
r_int
r_int
)paren
op_amp
id|ret_from_kernel_thread
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Copy function and argument to be called from&n;&t;&t; * ret_from_kernel_thread.&n;&t;&t; */
macro_line|#ifdef __LP64__
id|cregs-&gt;gr
(braket
l_int|27
)braket
op_assign
id|pregs-&gt;gr
(braket
l_int|27
)braket
suffix:semicolon
macro_line|#endif
id|cregs-&gt;gr
(braket
l_int|26
)braket
op_assign
id|pregs-&gt;gr
(braket
l_int|26
)braket
suffix:semicolon
id|cregs-&gt;gr
(braket
l_int|25
)braket
op_assign
id|pregs-&gt;gr
(braket
l_int|25
)braket
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* user thread */
multiline_comment|/*&n;&t;&t; * Note that the fork wrappers are responsible&n;&t;&t; * for setting gr[21].&n;&t;&t; */
multiline_comment|/* Use same stack depth as parent */
id|cregs-&gt;ksp
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|ti
)paren
)paren
op_plus
(paren
id|pregs-&gt;gr
(braket
l_int|21
)braket
op_amp
(paren
id|INIT_THREAD_SIZE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|cregs-&gt;gr
(braket
l_int|30
)braket
op_assign
id|usp
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;personality
op_eq
id|PER_HPUX
)paren
(brace
id|cregs-&gt;kpc
op_assign
(paren
r_int
r_int
)paren
op_amp
id|hpux_child_return
suffix:semicolon
)brace
r_else
(brace
id|cregs-&gt;kpc
op_assign
(paren
r_int
r_int
)paren
op_amp
id|child_return
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
op_star
)paren
id|regs-&gt;gr
(braket
l_int|26
)braket
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
op_star
op_star
)paren
id|regs-&gt;gr
(braket
l_int|25
)braket
comma
(paren
r_char
op_star
op_star
)paren
id|regs-&gt;gr
(braket
l_int|24
)braket
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
eof
