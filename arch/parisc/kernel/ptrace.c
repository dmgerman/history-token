multiline_comment|/*&n; * Kernel support for the ptrace() and syscall tracing interfaces.&n; *&n; * Copyright (C) 2000 Hewlett-Packard Co, Linuxcare Inc.&n; * Copyright (C) 2000 Matthew Wilcox &lt;matthew@wil.cx&gt;&n; * Copyright (C) 2000 David Huggins-Daines &lt;dhd@debian.org&gt;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/security.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/offsets.h&gt;
multiline_comment|/* These are used in entry.S, syscall_restore_rfi.  We need to record the&n; * current stepping mode somewhere other than in PSW, because there is no&n; * concept of saving and restoring the users PSW over a syscall.  We choose&n; * to use these two bits in task-&gt;ptrace.  These bits must not clash with&n; * any PT_* defined in include/linux/sched.h, and must match with the bit&n; * tests in entry.S&n; */
DECL|macro|PT_SINGLESTEP
mdefine_line|#define PT_SINGLESTEP&t;0x10000
DECL|macro|PT_BLOCKSTEP
mdefine_line|#define PT_BLOCKSTEP&t;0x20000
multiline_comment|/* PSW bits we allow the debugger to modify */
DECL|macro|USER_PSW_BITS
mdefine_line|#define USER_PSW_BITS&t;(PSW_N | PSW_V | PSW_CB)
DECL|macro|DEBUG_PTRACE
macro_line|#undef DEBUG_PTRACE
macro_line|#ifdef DEBUG_PTRACE
DECL|macro|DBG
mdefine_line|#define DBG(x)&t;printk x
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x)
macro_line|#endif
macro_line|#ifdef __LP64__
DECL|macro|CHILD_IS_32BIT
mdefine_line|#define CHILD_IS_32BIT&t;(child-&gt;personality == PER_LINUX_32BIT)
multiline_comment|/* This function is needed to translate 32 bit pt_regs offsets in to&n; * 64 bit pt_regs offsets.  For example, a 32 bit gdb under a 64 bit kernel&n; * will request offset 12 if it wants gr3, but the lower 32 bits of&n; * the 64 bit kernels view of gr3 will be at offset 28 (3*8 + 4).&n; * This code relies on a 32 bit pt_regs being comprised of 32 bit values&n; * except for the fp registers which (a) are 64 bits, and (b) follow&n; * the gr registers at the start of pt_regs.  The 32 bit pt_regs should&n; * be half the size of the 64 bit pt_regs, plus 32*4 to allow for fr[]&n; * being 64 bit in both cases.&n; */
DECL|function|translate_usr_offset
r_static
r_int
id|translate_usr_offset
c_func
(paren
r_int
id|offset
)paren
(brace
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|offset
op_le
l_int|32
op_star
l_int|4
)paren
multiline_comment|/* gr[0..31] */
r_return
id|offset
op_star
l_int|2
op_plus
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|offset
op_le
l_int|32
op_star
l_int|4
op_plus
l_int|32
op_star
l_int|8
)paren
multiline_comment|/* gr[0..31] + fr[0..31] */
r_return
id|offset
op_plus
l_int|32
op_star
l_int|4
suffix:semicolon
r_else
r_if
c_cond
(paren
id|offset
OL
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_div
l_int|2
op_plus
l_int|32
op_star
l_int|4
)paren
r_return
id|offset
op_star
l_int|2
op_plus
l_int|4
op_minus
l_int|32
op_star
l_int|8
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Called by kernel/ptrace.c when detaching..&n; *&n; * Make sure single step bits etc are not set.&n; */
DECL|function|ptrace_disable
r_void
id|ptrace_disable
c_func
(paren
r_struct
id|task_struct
op_star
id|child
)paren
(brace
multiline_comment|/* make sure the trap bits are not set */
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|r
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|t
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|h
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|l
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|sys_ptrace
r_int
id|sys_ptrace
c_func
(paren
r_int
id|request
comma
id|pid_t
id|pid
comma
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_struct
id|task_struct
op_star
id|child
suffix:semicolon
r_int
id|ret
suffix:semicolon
macro_line|#ifdef DEBUG_PTRACE
r_int
id|oaddr
op_assign
id|addr
comma
id|odata
op_assign
id|data
suffix:semicolon
macro_line|#endif
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_TRACEME
)paren
(brace
multiline_comment|/* are we already being traced? */
r_if
c_cond
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
id|security_ptrace
c_func
(paren
id|current-&gt;parent
comma
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* set the ptrace bit in the process flags. */
id|current-&gt;ptrace
op_or_assign
id|PT_PTRACED
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|ESRCH
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|child
op_assign
id|find_task_by_pid
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child
)paren
id|get_task_struct
c_func
(paren
id|child
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
op_logical_neg
id|child
)paren
r_goto
id|out
suffix:semicolon
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_eq
l_int|1
)paren
multiline_comment|/* no messing around with init! */
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_ATTACH
)paren
(brace
id|ret
op_assign
id|ptrace_attach
c_func
(paren
id|child
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|ret
op_assign
id|ptrace_check_attach
c_func
(paren
id|child
comma
id|request
op_eq
id|PTRACE_KILL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_goto
id|out_tsk
suffix:semicolon
r_switch
c_cond
(paren
id|request
)paren
(brace
r_case
id|PTRACE_PEEKTEXT
suffix:colon
multiline_comment|/* read word at location addr. */
r_case
id|PTRACE_PEEKDATA
suffix:colon
(brace
r_int
id|copied
suffix:semicolon
macro_line|#ifdef __LP64__
r_if
c_cond
(paren
id|CHILD_IS_32BIT
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffffffL
suffix:semicolon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_ne
r_sizeof
(paren
id|tmp
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(PEEK%s, %d, %lx, %lx) returning %ld, data %x&bslash;n&quot;
comma
id|request
op_eq
id|PTRACE_PEEKTEXT
ques
c_cond
l_string|&quot;TEXT&quot;
suffix:colon
l_string|&quot;DATA&quot;
comma
id|pid
comma
id|oaddr
comma
id|odata
comma
id|ret
comma
id|tmp
)paren
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|copied
op_assign
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|0
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|copied
op_ne
r_sizeof
(paren
id|tmp
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
)brace
r_goto
id|out_tsk
suffix:semicolon
)brace
multiline_comment|/* when I and D space are separate, this will have to be fixed. */
r_case
id|PTRACE_POKETEXT
suffix:colon
multiline_comment|/* write the word at location addr. */
r_case
id|PTRACE_POKEDATA
suffix:colon
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __LP64__
r_if
c_cond
(paren
id|CHILD_IS_32BIT
)paren
(brace
r_int
r_int
id|tmp
op_assign
(paren
r_int
r_int
)paren
id|data
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(POKE%s, %d, %lx, %lx)&bslash;n&quot;
comma
id|request
op_eq
id|PTRACE_POKETEXT
ques
c_cond
l_string|&quot;TEXT&quot;
suffix:colon
l_string|&quot;DATA&quot;
comma
id|pid
comma
id|oaddr
comma
id|odata
)paren
)paren
suffix:semicolon
id|addr
op_and_assign
l_int|0xffffffffL
suffix:semicolon
r_if
c_cond
(paren
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|tmp
comma
r_sizeof
(paren
id|tmp
)paren
comma
l_int|1
)paren
op_eq
r_sizeof
(paren
id|tmp
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
r_if
c_cond
(paren
id|access_process_vm
c_func
(paren
id|child
comma
id|addr
comma
op_amp
id|data
comma
r_sizeof
(paren
id|data
)paren
comma
l_int|1
)paren
op_eq
r_sizeof
(paren
id|data
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
)brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
multiline_comment|/* Read the word at location addr in the USER area.  For ptraced&n;&t;   processes, the kernel saves all regs on a syscall. */
r_case
id|PTRACE_PEEKUSR
suffix:colon
(brace
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
macro_line|#ifdef __LP64__
r_if
c_cond
(paren
id|CHILD_IS_32BIT
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_assign
id|translate_usr_offset
c_func
(paren
id|addr
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out_tsk
suffix:semicolon
id|tmp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|task_regs
c_func
(paren
id|child
)paren
op_plus
id|addr
)paren
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(PEEKUSR, %d, %lx, %lx) returning %ld, addr %lx, data %x&bslash;n&quot;
comma
id|pid
comma
id|oaddr
comma
id|odata
comma
id|ret
comma
id|addr
comma
id|tmp
)paren
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
r_int
r_int
)paren
id|addr
op_ge
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
id|tmp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|task_regs
c_func
(paren
id|child
)paren
op_plus
id|addr
)paren
suffix:semicolon
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
(paren
r_int
r_int
op_star
)paren
id|data
)paren
suffix:semicolon
)brace
r_goto
id|out_tsk
suffix:semicolon
)brace
multiline_comment|/* Write the word at location addr in the USER area.  This will need&n;&t;   to change when the kernel no longer saves all regs on a syscall.&n;&t;   FIXME.  There is a problem at the moment in that r3-r18 are only&n;&t;   saved if the process is ptraced on syscall entry, and even then&n;&t;   those values are overwritten by actual register values on syscall&n;&t;   exit. */
r_case
id|PTRACE_POKEUSR
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* Some register values written here may be ignored in&n;&t;&t; * entry.S:syscall_restore_rfi; e.g. iaoq is written with&n;&t;&t; * r31/r31+4, and not with the values in pt_regs.&n;&t;&t; */
multiline_comment|/* PT_PSW=0, so this is valid for 32 bit processes under 64&n;&t;&t; * bit kernels.&n;&t;&t; */
r_if
c_cond
(paren
id|addr
op_eq
id|PT_PSW
)paren
(brace
multiline_comment|/* PT_PSW=0, so this is valid for 32 bit processes&n;&t;&t;&t; * under 64 bit kernels.&n;&t;&t;&t; *&n;&t;&t;&t; * Allow writing to Nullify, Divide-step-correction,&n;&t;&t;&t; * and carry/borrow bits.&n;&t;&t;&t; * BEWARE, if you set N, and then single step, it wont&n;&t;&t;&t; * stop on the nullified instruction.&n;&t;&t;&t; */
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(POKEUSR, %d, %lx, %lx)&bslash;n&quot;
comma
id|pid
comma
id|oaddr
comma
id|odata
)paren
)paren
suffix:semicolon
id|data
op_and_assign
id|USER_PSW_BITS
suffix:semicolon
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|gr
(braket
l_int|0
)braket
op_and_assign
op_complement
id|USER_PSW_BITS
suffix:semicolon
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|gr
(braket
l_int|0
)braket
op_or_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
macro_line|#ifdef __LP64__
r_if
c_cond
(paren
id|CHILD_IS_32BIT
)paren
(brace
r_if
c_cond
(paren
id|addr
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_assign
id|translate_usr_offset
c_func
(paren
id|addr
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out_tsk
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(POKEUSR, %d, %lx, %lx) addr %lx&bslash;n&quot;
comma
id|pid
comma
id|oaddr
comma
id|odata
comma
id|addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
id|PT_FR0
op_logical_and
id|addr
op_le
id|PT_FR31
)paren
(brace
multiline_comment|/* Special case, fp regs are 64 bits anyway */
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|task_regs
c_func
(paren
id|child
)paren
op_plus
id|addr
)paren
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|PT_GR1
op_plus
l_int|4
op_logical_and
id|addr
op_le
id|PT_GR31
op_plus
l_int|4
)paren
op_logical_or
id|addr
op_eq
id|PT_IAOQ0
op_plus
l_int|4
op_logical_or
id|addr
op_eq
id|PT_IAOQ1
op_plus
l_int|4
op_logical_or
id|addr
op_eq
id|PT_SAR
op_plus
l_int|4
)paren
(brace
multiline_comment|/* Zero the top 32 bits */
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|task_regs
c_func
(paren
id|child
)paren
op_plus
id|addr
op_minus
l_int|4
)paren
op_assign
l_int|0
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|task_regs
c_func
(paren
id|child
)paren
op_plus
id|addr
)paren
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_goto
id|out_tsk
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
r_if
c_cond
(paren
(paren
id|addr
op_amp
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
)paren
op_logical_or
(paren
r_int
r_int
)paren
id|addr
op_ge
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
r_goto
id|out_tsk
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_ge
id|PT_GR1
op_logical_and
id|addr
op_le
id|PT_GR31
)paren
op_logical_or
id|addr
op_eq
id|PT_IAOQ0
op_logical_or
id|addr
op_eq
id|PT_IAOQ1
op_logical_or
(paren
id|addr
op_ge
id|PT_FR0
op_logical_and
id|addr
op_le
id|PT_FR31
)paren
op_logical_or
id|addr
op_eq
id|PT_SAR
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|task_regs
c_func
(paren
id|child
)paren
op_plus
id|addr
)paren
op_assign
id|data
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_goto
id|out_tsk
suffix:semicolon
)brace
r_case
id|PTRACE_SYSCALL
suffix:colon
multiline_comment|/* continue and stop at next (return from) syscall */
r_case
id|PTRACE_CONT
suffix:colon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(%s)&bslash;n&quot;
comma
id|request
op_eq
id|PTRACE_SYSCALL
ques
c_cond
l_string|&quot;SYSCALL&quot;
suffix:colon
l_string|&quot;CONT&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_goto
id|out_tsk
suffix:semicolon
id|child-&gt;ptrace
op_and_assign
op_complement
(paren
id|PT_SINGLESTEP
op_or
id|PT_BLOCKSTEP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request
op_eq
id|PTRACE_SYSCALL
)paren
(brace
id|set_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
)brace
r_else
(brace
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
)brace
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
r_goto
id|out_wake_notrap
suffix:semicolon
r_case
id|PTRACE_KILL
suffix:colon
multiline_comment|/*&n;&t;&t; * make the child exit.  Best I can do is send it a&n;&t;&t; * sigkill.  perhaps it should be put in the status&n;&t;&t; * that it wants to exit.&n;&t;&t; */
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(KILL)&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child-&gt;state
op_eq
id|TASK_ZOMBIE
)paren
multiline_comment|/* already dead */
r_goto
id|out_tsk
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|SIGKILL
suffix:semicolon
r_goto
id|out_wake_notrap
suffix:semicolon
r_case
id|PTRACE_SINGLEBLOCK
suffix:colon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(SINGLEBLOCK)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_goto
id|out_tsk
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_SINGLESTEP
suffix:semicolon
id|child-&gt;ptrace
op_or_assign
id|PT_BLOCKSTEP
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
multiline_comment|/* Enable taken branch trap. */
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|r
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|t
op_assign
l_int|1
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|h
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|l
op_assign
l_int|0
suffix:semicolon
r_goto
id|out_wake
suffix:semicolon
r_case
id|PTRACE_SINGLESTEP
suffix:colon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(SINGLESTEP)&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ret
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|data
OG
id|_NSIG
)paren
r_goto
id|out_tsk
suffix:semicolon
id|clear_tsk_thread_flag
c_func
(paren
id|child
comma
id|TIF_SYSCALL_TRACE
)paren
suffix:semicolon
id|child-&gt;ptrace
op_and_assign
op_complement
id|PT_BLOCKSTEP
suffix:semicolon
id|child-&gt;ptrace
op_or_assign
id|PT_SINGLESTEP
suffix:semicolon
id|child-&gt;exit_code
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|n
)paren
(brace
r_struct
id|siginfo
id|si
suffix:semicolon
multiline_comment|/* Nullified, just crank over the queue. */
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|iaoq
(braket
l_int|0
)braket
op_assign
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|iaoq
(braket
l_int|1
)braket
suffix:semicolon
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|iasq
(braket
l_int|0
)braket
op_assign
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|iasq
(braket
l_int|1
)braket
suffix:semicolon
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|iaoq
(braket
l_int|1
)braket
op_assign
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|iaoq
(braket
l_int|0
)braket
op_plus
l_int|4
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|n
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|x
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|y
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|z
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|b
op_assign
l_int|0
suffix:semicolon
id|ptrace_disable
c_func
(paren
id|child
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t wake up the child, but let the&n;&t;&t;&t;   parent know something happened. */
id|si.si_code
op_assign
id|TRAP_TRACE
suffix:semicolon
id|si.si_addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|task_regs
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|iaoq
(braket
l_int|0
)braket
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
id|si.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|si
comma
id|child
)paren
suffix:semicolon
singleline_comment|//notify_parent(child, SIGCHLD);
singleline_comment|//ret = 0;
r_goto
id|out_wake
suffix:semicolon
)brace
multiline_comment|/* Enable recovery counter traps.  The recovery counter&n;&t;&t; * itself will be set to zero on a task switch.  If the&n;&t;&t; * task is suspended on a syscall then the syscall return&n;&t;&t; * path will overwrite the recovery counter with a suitable&n;&t;&t; * value such that it traps once back in user space.  We&n;&t;&t; * disable interrupts in the childs PSW here also, to avoid&n;&t;&t; * interrupts while the recovery counter is decrementing.&n;&t;&t; */
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|r
op_assign
l_int|1
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|t
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|h
op_assign
l_int|0
suffix:semicolon
id|pa_psw
c_func
(paren
id|child
)paren
op_member_access_from_pointer
id|l
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* give it a chance to run. */
r_goto
id|out_wake
suffix:semicolon
r_case
id|PTRACE_DETACH
suffix:colon
id|ret
op_assign
id|ptrace_detach
c_func
(paren
id|child
comma
id|data
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
id|ptrace_request
c_func
(paren
id|child
comma
id|request
comma
id|addr
comma
id|data
)paren
suffix:semicolon
r_goto
id|out_tsk
suffix:semicolon
)brace
id|out_wake_notrap
suffix:colon
id|ptrace_disable
c_func
(paren
id|child
)paren
suffix:semicolon
id|out_wake
suffix:colon
id|wake_up_process
c_func
(paren
id|child
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|out_tsk
suffix:colon
id|put_task_struct
c_func
(paren
id|child
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
(paren
l_string|&quot;sys_ptrace(%ld, %d, %lx, %lx) returning %ld&bslash;n&quot;
comma
id|request
comma
id|pid
comma
id|oaddr
comma
id|odata
comma
id|ret
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|syscall_trace
r_void
id|syscall_trace
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_thread_flag
c_func
(paren
id|TIF_SYSCALL_TRACE
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
)paren
r_return
suffix:semicolon
id|current-&gt;exit_code
op_assign
id|SIGTRAP
op_or
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_TRACESYSGOOD
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|notify_parent
c_func
(paren
id|current
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * this isn&squot;t the same as continuing with a signal, but it will do&n;&t; * for normal use.  strace only continues with a signal if the&n;&t; * stopping signal is not SIGTRAP.  -brl&n;&t; */
r_if
c_cond
(paren
id|current-&gt;exit_code
)paren
(brace
id|send_sig
c_func
(paren
id|current-&gt;exit_code
comma
id|current
comma
l_int|1
)paren
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
)brace
)brace
eof
