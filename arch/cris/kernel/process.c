multiline_comment|/* $Id: process.c,v 1.17 2004/04/05 13:53:48 starvik Exp $&n; * &n; *  linux/arch/cris/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Copyright (C) 2000-2002  Axis Communications AB&n; *&n; *  Authors:   Bjorn Wesen (bjornw@axis.com)&n; *&n; *  $Log: process.c,v $&n; *  Revision 1.17  2004/04/05 13:53:48  starvik&n; *  Merge of Linux 2.6.5&n; *&n; *  Revision 1.16  2003/10/27 08:04:33  starvik&n; *  Merge of Linux 2.6.0-test9&n; *&n; *  Revision 1.15  2003/09/11 07:29:52  starvik&n; *  Merge of Linux 2.6.0-test5&n; *&n; *  Revision 1.14  2003/06/10 10:21:12  johana&n; *  Moved thread_saved_pc() from arch/cris/kernel/process.c to&n; *  subarch specific process.c. arch-v32 has an erp, no irp.&n; *&n; *  Revision 1.13  2003/04/09 05:20:47  starvik&n; *  Merge of Linux 2.5.67&n; *&n; *  Revision 1.12  2002/12/11 15:41:11  starvik&n; *  Extracted v10 (ETRAX 100LX) specific stuff to arch/cris/arch-v10/kernel&n; *&n; *  Revision 1.11  2002/12/10 09:00:10  starvik&n; *  Merge of Linux 2.5.51&n; *&n; *  Revision 1.10  2002/11/27 08:42:34  starvik&n; *  Argument to user_regs() is thread_info*&n; *&n; *  Revision 1.9  2002/11/26 09:44:21  starvik&n; *  New threads exits through ret_from_fork (necessary for preemptive scheduling)&n; *&n; *  Revision 1.8  2002/11/19 14:35:24  starvik&n; *  Changes from linux 2.4&n; *  Changed struct initializer syntax to the currently prefered notation&n; *&n; *  Revision 1.7  2002/11/18 07:39:42  starvik&n; *  thread_saved_pc moved here from processor.h&n; *&n; *  Revision 1.6  2002/11/14 06:51:27  starvik&n; *  Made cpu_idle more similar with other archs&n; *  init_task_union -&gt; init_thread_union&n; *  Updated for new interrupt macros&n; *  sys_clone and do_fork have a new argument, user_tid&n; *&n; *  Revision 1.5  2002/11/05 06:45:11  starvik&n; *  Merge of Linux 2.5.45&n; *&n; *  Revision 1.4  2002/02/05 15:37:44  bjornw&n; *  Need init_task.h&n; *&n; *  Revision 1.3  2002/01/21 15:22:49  bjornw&n; *  current-&gt;counter is gone&n; *&n; *  Revision 1.22  2001/11/13 09:40:43  orjanf&n; *  Added dump_fpu (needed for core dumps).&n; *&n; *  Revision 1.21  2001/11/12 18:26:21  pkj&n; *  Fixed compiler warnings.&n; *&n; *  Revision 1.20  2001/10/03 08:21:39  jonashg&n; *  cause_of_death does not exist if CONFIG_SVINTO_SIM is defined.&n; *&n; *  Revision 1.19  2001/09/26 11:52:54  bjornw&n; *  INIT_MMAP is gone in 2.4.10&n; *&n; *  Revision 1.18  2001/08/21 21:43:51  hp&n; *  Move last watchdog fix inside #ifdef CONFIG_ETRAX_WATCHDOG&n; *&n; *  Revision 1.17  2001/08/21 13:48:01  jonashg&n; *  Added fix by HP to avoid oops when doing a hard_reset_now.&n; *&n; *  Revision 1.16  2001/06/21 02:00:40  hp&n; *  &t;* entry.S: Include asm/unistd.h.&n; *  &t;(_sys_call_table): Use section .rodata, not .data.&n; *  &t;(_kernel_thread): Move from...&n; *  &t;* process.c: ... here.&n; *  &t;* entryoffsets.c (VAL): Break out from...&n; *  &t;(OF): Use VAL.&n; *  &t;(LCLONE_VM): New asmified value from CLONE_VM.&n; *&n; *  Revision 1.15  2001/06/20 16:31:57  hp&n; *  Add comments to describe empty functions according to review.&n; *&n; *  Revision 1.14  2001/05/29 11:27:59  markusl&n; *  Fixed so that hard_reset_now will do reset even if watchdog wasn&squot;t enabled&n; *&n; *  Revision 1.13  2001/03/20 19:44:06  bjornw&n; *  Use the 7th syscall argument for regs instead of current_regs&n; *&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/fs_struct.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
singleline_comment|//#define DEBUG
multiline_comment|/*&n; * Initial task structure. Make this a per-architecture thing,&n; * because different architectures tend to have different&n; * alignment requirements and potentially different initial&n; * setup.&n; */
DECL|variable|init_fs
r_static
r_struct
id|fs_struct
id|init_fs
op_assign
id|INIT_FS
suffix:semicolon
DECL|variable|init_files
r_static
r_struct
id|files_struct
id|init_files
op_assign
id|INIT_FILES
suffix:semicolon
DECL|variable|init_signals
r_static
r_struct
id|signal_struct
id|init_signals
op_assign
id|INIT_SIGNALS
c_func
(paren
id|init_signals
)paren
suffix:semicolon
DECL|variable|init_sighand
r_static
r_struct
id|sighand_struct
id|init_sighand
op_assign
id|INIT_SIGHAND
c_func
(paren
id|init_sighand
)paren
suffix:semicolon
DECL|variable|init_mm
r_struct
id|mm_struct
id|init_mm
op_assign
id|INIT_MM
c_func
(paren
id|init_mm
)paren
suffix:semicolon
DECL|variable|init_mm
id|EXPORT_SYMBOL
c_func
(paren
id|init_mm
)paren
suffix:semicolon
multiline_comment|/*&n; * Initial thread structure.&n; *&n; * We need to make sure that this is 8192-byte aligned due to the&n; * way process stacks are handled. This is done by having a special&n; * &quot;init_task&quot; linker map entry..&n; */
DECL|variable|init_thread_union
r_union
id|thread_union
id|init_thread_union
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data.init_task&quot;
)paren
)paren
)paren
op_assign
(brace
id|INIT_THREAD_INFO
c_func
(paren
id|init_task
)paren
)brace
suffix:semicolon
multiline_comment|/*&n; * Initial task structure.&n; *&n; * All other task structs will be allocated on slabs in fork.c&n; */
DECL|variable|init_task
r_struct
id|task_struct
id|init_task
op_assign
id|INIT_TASK
c_func
(paren
id|init_task
)paren
suffix:semicolon
DECL|variable|init_task
id|EXPORT_SYMBOL
c_func
(paren
id|init_task
)paren
suffix:semicolon
multiline_comment|/*&n; * The hlt_counter, disable_hlt and enable_hlt is just here as a hook if&n; * there would ever be a halt sequence (for power save when idle) with&n; * some largish delay when halting or resuming *and* a driver that can&squot;t&n; * afford that delay.  The hlt_counter would then be checked before&n; * executing the halt sequence, and the driver marks the unhaltable&n; * region by enable_hlt/disable_hlt.&n; */
DECL|variable|hlt_counter
r_static
r_int
id|hlt_counter
op_assign
l_int|0
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
DECL|variable|disable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|disable_hlt
)paren
suffix:semicolon
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
DECL|variable|enable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|enable_hlt
)paren
suffix:semicolon
multiline_comment|/*&n; * The following aren&squot;t currently used.&n; */
DECL|variable|pm_idle
r_void
(paren
op_star
id|pm_idle
)paren
(paren
r_void
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
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
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
id|pm_idle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idle
)paren
id|idle
op_assign
id|default_idle
suffix:semicolon
id|idle
c_func
(paren
)paren
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_void
id|hard_reset_now
(paren
r_void
)paren
suffix:semicolon
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_void
)paren
(brace
id|hard_reset_now
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
)paren
suffix:semicolon
multiline_comment|/*&n; * Similar to machine_power_off, but don&squot;t shut off power.  Add code&n; * here to freeze the system for e.g. post-mortem debug purpose when&n; * possible.  This halt has nothing to do with the idle halt.&n; */
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|machine_halt
id|EXPORT_SYMBOL
c_func
(paren
id|machine_halt
)paren
suffix:semicolon
multiline_comment|/* If or when software power-off is implemented, add code here.  */
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
)brace
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
multiline_comment|/*&n; * When a process does an &quot;exec&quot;, machine state like FPU and debug&n; * registers need to be reset.  This is a hook function for that.&n; * Currently we don&squot;t have any such state to reset, so this is empty.&n; */
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * fill in the user structure for a core dump..&n; */
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
id|dump
)paren
(brace
macro_line|#if 0
r_int
id|i
suffix:semicolon
multiline_comment|/* changed the size calculations - should hopefully work better. lbt */
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
l_int|0
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|regs-&gt;esp
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
r_int
r_int
)paren
id|current-&gt;mm-&gt;end_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_sub_assign
id|dump-&gt;u_tsize
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
l_int|0
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|dump-&gt;u_debugreg
(braket
id|i
)braket
op_assign
id|current-&gt;debugreg
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dump-&gt;start_stack
OL
id|TASK_SIZE
)paren
id|dump-&gt;u_ssize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|TASK_SIZE
op_minus
id|dump-&gt;start_stack
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;regs
op_assign
op_star
id|regs
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;i387
)paren
suffix:semicolon
macro_line|#endif 
)brace
multiline_comment|/* Fill in the fpu structure for a core dump. */
DECL|function|dump_fpu
r_int
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
id|fpu
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
