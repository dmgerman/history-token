multiline_comment|/*&n; *  linux/arch/alpha/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
multiline_comment|/*&n; * No need to acquire the kernel lock, we&squot;re entirely local..&n; */
id|asmlinkage
r_int
DECL|function|sys_sethae
id|sys_sethae
c_func
(paren
r_int
r_int
id|hae
comma
r_int
r_int
id|a1
comma
r_int
r_int
id|a2
comma
r_int
r_int
id|a3
comma
r_int
r_int
id|a4
comma
r_int
r_int
id|a5
comma
r_struct
id|pt_regs
id|regs
)paren
(brace
(paren
op_amp
id|regs
)paren
op_member_access_from_pointer
id|hae
op_assign
id|hae
suffix:semicolon
r_return
l_int|0
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
r_void
DECL|function|cpu_idle
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_void
(paren
op_star
id|idle
)paren
(paren
r_void
)paren
op_assign
id|default_idle
suffix:semicolon
multiline_comment|/* FIXME -- EV6 and LCA45 know how to power down&n;&t;&t;   the CPU.  */
r_while
c_loop
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|idle
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|struct|halt_info
r_struct
id|halt_info
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|restart_cmd
r_char
op_star
id|restart_cmd
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
DECL|function|common_shutdown_1
id|common_shutdown_1
c_func
(paren
r_void
op_star
id|generic_ptr
)paren
(brace
r_struct
id|halt_info
op_star
id|how
op_assign
(paren
r_struct
id|halt_info
op_star
)paren
id|generic_ptr
suffix:semicolon
r_struct
id|percpu_struct
op_star
id|cpup
suffix:semicolon
r_int
r_int
op_star
id|pflags
comma
id|flags
suffix:semicolon
r_int
id|cpuid
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* No point in taking interrupts anymore. */
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|cpup
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
op_plus
id|hwrpb-&gt;processor_size
op_star
id|cpuid
)paren
suffix:semicolon
id|pflags
op_assign
op_amp
id|cpup-&gt;flags
suffix:semicolon
id|flags
op_assign
op_star
id|pflags
suffix:semicolon
multiline_comment|/* Clear reason to &quot;default&quot;; clear &quot;bootstrap in progress&quot;. */
id|flags
op_and_assign
op_complement
l_int|0x00ff0001UL
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Secondaries halt here. */
r_if
c_cond
(paren
id|cpuid
op_ne
id|boot_cpuid
)paren
(brace
id|flags
op_or_assign
l_int|0x00040000UL
suffix:semicolon
multiline_comment|/* &quot;remain halted&quot; */
op_star
id|pflags
op_assign
id|flags
suffix:semicolon
id|clear_bit
c_func
(paren
id|cpuid
comma
op_amp
id|cpu_present_mask
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|how-&gt;mode
op_eq
id|LINUX_REBOOT_CMD_RESTART
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|how-&gt;restart_cmd
)paren
(brace
id|flags
op_or_assign
l_int|0x00020000UL
suffix:semicolon
multiline_comment|/* &quot;cold bootstrap&quot; */
)brace
r_else
(brace
multiline_comment|/* For SRM, we could probably set environment&n;&t;&t;&t;   variables to get this to work.  We&squot;d have to&n;&t;&t;&t;   delay this until after srm_paging_stop unless&n;&t;&t;&t;   we ever got srm_fixup working.&n;&n;&t;&t;&t;   At the moment, SRM will use the last boot device,&n;&t;&t;&t;   but the file and flags will be the defaults, when&n;&t;&t;&t;   doing a &quot;warm&quot; bootstrap.  */
id|flags
op_or_assign
l_int|0x00030000UL
suffix:semicolon
multiline_comment|/* &quot;warm bootstrap&quot; */
)brace
)brace
r_else
(brace
id|flags
op_or_assign
l_int|0x00040000UL
suffix:semicolon
multiline_comment|/* &quot;remain halted&quot; */
)brace
op_star
id|pflags
op_assign
id|flags
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Wait for the secondaries to halt. */
id|clear_bit
c_func
(paren
id|boot_cpuid
comma
op_amp
id|cpu_present_mask
)paren
suffix:semicolon
r_while
c_loop
(paren
id|cpu_present_mask
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* If booted from SRM, reset some of the original environment. */
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
multiline_comment|/* This has the effect of resetting the VGA video origin.  */
id|take_over_console
c_func
(paren
op_amp
id|dummy_con
comma
l_int|0
comma
id|MAX_NR_CONSOLES
op_minus
l_int|1
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* reset_for_srm(); */
id|set_hae
c_func
(paren
id|srm_hae
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alpha_mv.kill_arch
)paren
id|alpha_mv
dot
id|kill_arch
c_func
(paren
id|how-&gt;mode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|alpha_using_srm
op_logical_and
id|how-&gt;mode
op_ne
id|LINUX_REBOOT_CMD_RESTART
)paren
(brace
multiline_comment|/* Unfortunately, since MILO doesn&squot;t currently understand&n;&t;&t;   the hwrpb bits above, we can&squot;t reliably halt the &n;&t;&t;   processor and keep it halted.  So just loop.  */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|srm_paging_stop
c_func
(paren
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|common_shutdown
id|common_shutdown
c_func
(paren
r_int
id|mode
comma
r_char
op_star
id|restart_cmd
)paren
(brace
r_struct
id|halt_info
id|args
suffix:semicolon
id|args.mode
op_assign
id|mode
suffix:semicolon
id|args.restart_cmd
op_assign
id|restart_cmd
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_call_function
c_func
(paren
id|common_shutdown_1
comma
op_amp
id|args
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|common_shutdown_1
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_restart
id|machine_restart
c_func
(paren
r_char
op_star
id|restart_cmd
)paren
(brace
id|common_shutdown
c_func
(paren
id|LINUX_REBOOT_CMD_RESTART
comma
id|restart_cmd
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_halt
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|common_shutdown
c_func
(paren
id|LINUX_REBOOT_CMD_HALT
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_void
DECL|function|machine_power_off
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
id|common_shutdown
c_func
(paren
id|LINUX_REBOOT_CMD_POWER_OFF
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_void
DECL|function|show_regs
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Pid: %d, comm: %20s&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ps: %04lx pc: [&lt;%016lx&gt;] CPU %d    %s&bslash;n&quot;
comma
id|regs-&gt;ps
comma
id|regs-&gt;pc
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;rp: [&lt;%016lx&gt;] sp: %p&bslash;n&quot;
comma
id|regs-&gt;r26
comma
id|regs
op_plus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; r0: %016lx  r1: %016lx  r2: %016lx  r3: %016lx&bslash;n&quot;
comma
id|regs-&gt;r0
comma
id|regs-&gt;r1
comma
id|regs-&gt;r2
comma
id|regs-&gt;r3
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; r4: %016lx  r5: %016lx  r6: %016lx  r7: %016lx&bslash;n&quot;
comma
id|regs-&gt;r4
comma
id|regs-&gt;r5
comma
id|regs-&gt;r6
comma
id|regs-&gt;r7
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; r8: %016lx r16: %016lx r17: %016lx r18: %016lx&bslash;n&quot;
comma
id|regs-&gt;r8
comma
id|regs-&gt;r16
comma
id|regs-&gt;r17
comma
id|regs-&gt;r18
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r19: %016lx r20: %016lx r21: %016lx r22: %016lx&bslash;n&quot;
comma
id|regs-&gt;r19
comma
id|regs-&gt;r20
comma
id|regs-&gt;r21
comma
id|regs-&gt;r22
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r23: %016lx r24: %016lx r25: %016lx r26: %016lx&bslash;n&quot;
comma
id|regs-&gt;r23
comma
id|regs-&gt;r24
comma
id|regs-&gt;r25
comma
id|regs-&gt;r26
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;r27: %016lx r28: %016lx r29: %016lx hae: %016lx&bslash;n&quot;
comma
id|regs-&gt;r27
comma
id|regs-&gt;r28
comma
id|regs-&gt;gp
comma
id|regs-&gt;hae
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Re-start a thread when doing execve()&n; */
r_void
DECL|function|start_thread
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|pc
comma
r_int
r_int
id|sp
)paren
(brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|regs-&gt;pc
op_assign
id|pc
suffix:semicolon
id|regs-&gt;ps
op_assign
l_int|8
suffix:semicolon
id|wrusp
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
r_void
DECL|function|exit_thread
id|exit_thread
c_func
(paren
r_void
)paren
(brace
)brace
r_void
DECL|function|flush_thread
id|flush_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Arrange for each exec&squot;ed process to start off with a clean slate&n;&t;   with respect to the FPU.  This is all exceptions disabled.  */
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|ieee_state
op_assign
l_int|0
suffix:semicolon
id|wrfpcr
c_func
(paren
id|FPCR_DYN_NORMAL
op_or
id|ieee_swcr_to_fpcr
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|release_thread
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
multiline_comment|/*&n; * &quot;alpha_clone()&quot;.. By the time we get here, the&n; * non-volatile registers have also been saved on the&n; * stack. We do some ugly pointer stuff here.. (see&n; * also copy_thread)&n; *&n; * Notice that &quot;fork()&quot; is implemented in terms of clone,&n; * with parameters (SIGCHLD, 0).&n; */
r_int
DECL|function|alpha_clone
id|alpha_clone
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
id|switch_stack
op_star
id|swstack
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usp
)paren
id|usp
op_assign
id|rdusp
c_func
(paren
)paren
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
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|swstack
op_plus
l_int|1
)paren
comma
l_int|0
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
DECL|function|alpha_vfork
id|alpha_vfork
c_func
(paren
r_struct
id|switch_stack
op_star
id|swstack
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
id|rdusp
c_func
(paren
)paren
comma
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|swstack
op_plus
l_int|1
)paren
comma
l_int|0
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
multiline_comment|/*&n; * Copy an alpha thread..&n; *&n; * Note the &quot;stack_offset&quot; stuff: when returning to kernel mode, we need&n; * to have some extra stack-space for the kernel stack that still exists&n; * after the &quot;ret_from_fork&quot;.  When returning to user mode, we only want&n; * the space needed by the syscall stack frame (ie &quot;struct pt_regs&quot;).&n; * Use the passed &quot;regs&quot; pointer to determine how much space we need&n; * for a kernel fork().&n; */
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
r_extern
r_void
id|ret_from_sys_call
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|thread_info
op_star
id|childti
op_assign
id|p-&gt;thread_info
suffix:semicolon
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_struct
id|switch_stack
op_star
id|childstack
comma
op_star
id|stack
suffix:semicolon
r_int
r_int
id|stack_offset
suffix:semicolon
id|stack_offset
op_assign
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|regs-&gt;ps
op_amp
l_int|8
)paren
)paren
id|stack_offset
op_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
(paren
r_int
r_int
)paren
id|regs
suffix:semicolon
id|childregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|stack_offset
op_plus
id|PAGE_SIZE
op_plus
(paren
r_int
)paren
id|childti
)paren
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;r0
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;r19
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;r20
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* OSF/1 has some strange fork() semantics.  */
id|regs-&gt;r20
op_assign
l_int|0
suffix:semicolon
id|stack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|regs
)paren
op_minus
l_int|1
suffix:semicolon
id|childstack
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|childregs
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|childstack
op_assign
op_star
id|stack
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|childstack-&gt;r26
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
macro_line|#else
id|childstack-&gt;r26
op_assign
(paren
r_int
r_int
)paren
id|ret_from_sys_call
suffix:semicolon
macro_line|#endif
id|childti-&gt;pcb.usp
op_assign
id|usp
suffix:semicolon
id|childti-&gt;pcb.ksp
op_assign
(paren
r_int
r_int
)paren
id|childstack
suffix:semicolon
id|childti-&gt;pcb.flags
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* set FEN, clear everything else */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the user structure for a core dump..&n; */
r_void
DECL|function|dump_thread
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|pt
comma
r_struct
id|user
op_star
id|dump
)paren
(brace
multiline_comment|/* switch stack follows right below pt_regs: */
r_struct
id|switch_stack
op_star
id|sw
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|pt
)paren
op_minus
l_int|1
suffix:semicolon
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
id|current-&gt;mm-&gt;start_code
suffix:semicolon
id|dump-&gt;start_data
op_assign
id|current-&gt;mm-&gt;start_data
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|rdusp
c_func
(paren
)paren
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump-&gt;u_tsize
op_assign
(paren
(paren
id|current-&gt;mm-&gt;end_code
op_minus
id|dump-&gt;start_code
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
(paren
id|current-&gt;mm-&gt;brk
op_plus
id|PAGE_SIZE
op_minus
l_int|1
op_minus
id|dump-&gt;start_data
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
(paren
id|current-&gt;mm-&gt;start_stack
op_minus
id|dump-&gt;start_stack
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * We store the registers in an order/format that is&n;&t; * compatible with DEC Unix/OSF/1 as this makes life easier&n;&t; * for gdb.&n;&t; */
id|dump-&gt;regs
(braket
id|EF_V0
)braket
op_assign
id|pt-&gt;r0
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T0
)braket
op_assign
id|pt-&gt;r1
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T1
)braket
op_assign
id|pt-&gt;r2
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T2
)braket
op_assign
id|pt-&gt;r3
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T3
)braket
op_assign
id|pt-&gt;r4
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T4
)braket
op_assign
id|pt-&gt;r5
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T5
)braket
op_assign
id|pt-&gt;r6
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T6
)braket
op_assign
id|pt-&gt;r7
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T7
)braket
op_assign
id|pt-&gt;r8
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S0
)braket
op_assign
id|sw-&gt;r9
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S1
)braket
op_assign
id|sw-&gt;r10
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S2
)braket
op_assign
id|sw-&gt;r11
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S3
)braket
op_assign
id|sw-&gt;r12
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S4
)braket
op_assign
id|sw-&gt;r13
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S5
)braket
op_assign
id|sw-&gt;r14
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_S6
)braket
op_assign
id|sw-&gt;r15
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A3
)braket
op_assign
id|pt-&gt;r19
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A4
)braket
op_assign
id|pt-&gt;r20
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A5
)braket
op_assign
id|pt-&gt;r21
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T8
)braket
op_assign
id|pt-&gt;r22
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T9
)braket
op_assign
id|pt-&gt;r23
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T10
)braket
op_assign
id|pt-&gt;r24
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T11
)braket
op_assign
id|pt-&gt;r25
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_RA
)braket
op_assign
id|pt-&gt;r26
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_T12
)braket
op_assign
id|pt-&gt;r27
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_AT
)braket
op_assign
id|pt-&gt;r28
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_SP
)braket
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_PS
)braket
op_assign
id|pt-&gt;ps
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_PC
)braket
op_assign
id|pt-&gt;pc
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_GP
)braket
op_assign
id|pt-&gt;gp
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A0
)braket
op_assign
id|pt-&gt;r16
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A1
)braket
op_assign
id|pt-&gt;r17
suffix:semicolon
id|dump-&gt;regs
(braket
id|EF_A2
)braket
op_assign
id|pt-&gt;r18
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|dump-&gt;regs
op_plus
id|EF_SIZE
comma
id|sw-&gt;fp
comma
l_int|32
op_star
l_int|8
)paren
suffix:semicolon
)brace
r_int
DECL|function|dump_fpu
id|dump_fpu
c_func
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
multiline_comment|/* switch stack follows right below pt_regs: */
r_struct
id|switch_stack
op_star
id|sw
op_assign
(paren
(paren
r_struct
id|switch_stack
op_star
)paren
id|regs
)paren
op_minus
l_int|1
suffix:semicolon
id|memcpy
c_func
(paren
id|r
comma
id|sw-&gt;fp
comma
l_int|32
op_star
l_int|8
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; *&n; * This works due to the alpha calling sequence: the first 6 args&n; * are gotten from registers, while the rest is on the stack, so&n; * we get a0-a5 for free, and then magically find &quot;struct pt_regs&quot;&n; * on the stack for us..&n; *&n; * Don&squot;t do this at home.&n; */
id|asmlinkage
r_int
DECL|function|sys_execve
id|sys_execve
c_func
(paren
r_char
op_star
id|ufilename
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
r_int
id|a3
comma
r_int
r_int
id|a4
comma
r_int
r_int
id|a5
comma
r_struct
id|pt_regs
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
id|ufilename
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
id|argv
comma
id|envp
comma
op_amp
id|regs
)paren
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
multiline_comment|/*&n; * Return saved PC of a blocked thread.  This assumes the frame&n; * pointer is the 6th saved long on the kernel stack and that the&n; * saved return address is the first long in the frame.  This all&n; * holds provided the thread blocked through a call to schedule() ($15&n; * is the frame pointer in schedule() and $15 is saved at offset 48 by&n; * entry.S:do_switch_stack).&n; *&n; * Under heavy swap load I&squot;ve seen this lose in an ugly way.  So do&n; * some extra sanity checking on the ranges we expect these pointers&n; * to be in so that we can fail gracefully.  This is just for ps after&n; * all.  -- r~&n; */
r_int
r_int
DECL|function|thread_saved_pc
id|thread_saved_pc
c_func
(paren
id|task_t
op_star
id|t
)paren
(brace
r_int
r_int
id|base
op_assign
(paren
r_int
r_int
)paren
id|t-&gt;thread_info
suffix:semicolon
r_int
r_int
id|fp
comma
id|sp
op_assign
id|t-&gt;thread_info-&gt;pcb.ksp
suffix:semicolon
r_if
c_cond
(paren
id|sp
OG
id|base
op_logical_and
id|sp
op_plus
l_int|6
op_star
l_int|8
OL
id|base
op_plus
l_int|16
op_star
l_int|1024
)paren
(brace
id|fp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|sp
)paren
(braket
l_int|6
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fp
OG
id|sp
op_logical_and
id|fp
OL
id|base
op_plus
l_int|16
op_star
l_int|1024
)paren
r_return
op_star
(paren
r_int
r_int
op_star
)paren
id|fp
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
mdefine_line|#define first_sched&t;((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched&t;((unsigned long) scheduling_functions_end_here)
r_int
r_int
DECL|function|get_wchan
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|schedule_frame
suffix:semicolon
r_int
r_int
id|pc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * This one depends on the frame size of schedule().  Do a&n;&t; * &quot;disass schedule&quot; in gdb to find the frame size.  Also, the&n;&t; * code assumes that sleep_on() follows immediately after&n;&t; * interruptible_sleep_on() and that add_timer() follows&n;&t; * immediately after interruptible_sleep().  Ugly, isn&squot;t it?&n;&t; * Maybe adding a wchan field to task_struct would be better,&n;&t; * after all...&n;&t; */
id|pc
op_assign
id|thread_saved_pc
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pc
op_ge
id|first_sched
op_logical_and
id|pc
OL
id|last_sched
)paren
(brace
id|schedule_frame
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|p-&gt;thread_info-&gt;pcb.ksp
)paren
(braket
l_int|6
)braket
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|schedule_frame
)paren
(braket
l_int|12
)braket
suffix:semicolon
)brace
r_return
id|pc
suffix:semicolon
)brace
eof
