multiline_comment|/*&n; * Copyright 2003 PathScale, Inc.&n; *&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/linkage.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/shm.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
DECL|macro|__FRAME_OFFSETS
mdefine_line|#define __FRAME_OFFSETS
macro_line|#include &quot;asm/ptrace.h&quot;
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;asm/prctl.h&quot; /* XXX This should get the constants from libc */
macro_line|#include &quot;choose-mode.h&quot;
DECL|function|wrap_sys_shmat
id|asmlinkage
r_int
id|wrap_sys_shmat
c_func
(paren
r_int
id|shmid
comma
r_char
id|__user
op_star
id|shmaddr
comma
r_int
id|shmflg
)paren
(brace
r_int
r_int
id|raddr
suffix:semicolon
r_return
id|do_shmat
c_func
(paren
id|shmid
comma
id|shmaddr
comma
id|shmflg
comma
op_amp
id|raddr
)paren
ques
c_cond
suffix:colon
(paren
r_int
)paren
id|raddr
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODE_TT
r_extern
r_int
id|modify_ldt
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
suffix:semicolon
DECL|function|sys_modify_ldt_tt
r_int
id|sys_modify_ldt_tt
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
multiline_comment|/* XXX This should check VERIFY_WRITE depending on func, check this&n;&t; * in i386 as well.&n;&t; */
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|ptr
comma
id|bytecount
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|modify_ldt
c_func
(paren
id|func
comma
id|ptr
comma
id|bytecount
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_SKAS
r_extern
r_int
id|userspace_pid
(braket
)braket
suffix:semicolon
DECL|function|sys_modify_ldt_skas
r_int
id|sys_modify_ldt_skas
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
r_struct
id|ptrace_ldt
id|ldt
suffix:semicolon
r_void
op_star
id|buf
suffix:semicolon
r_int
id|res
comma
id|n
suffix:semicolon
id|buf
op_assign
id|kmalloc
c_func
(paren
id|bytecount
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|res
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
l_int|1
suffix:colon
r_case
l_int|0x11
suffix:colon
id|res
op_assign
id|copy_from_user
c_func
(paren
id|buf
comma
id|ptr
comma
id|bytecount
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res
op_ne
l_int|0
)paren
(brace
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|ldt
op_assign
(paren
(paren
r_struct
id|ptrace_ldt
)paren
(brace
dot
id|func
op_assign
id|func
comma
dot
id|ptr
op_assign
id|buf
comma
dot
id|bytecount
op_assign
id|bytecount
)brace
)paren
suffix:semicolon
macro_line|#warning Need to look up userspace_pid by cpu
id|res
op_assign
id|ptrace
c_func
(paren
id|PTRACE_LDT
comma
id|userspace_pid
(braket
l_int|0
)braket
comma
l_int|0
comma
(paren
r_int
r_int
)paren
op_amp
id|ldt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|func
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|2
suffix:colon
id|n
op_assign
id|res
suffix:semicolon
id|res
op_assign
id|copy_to_user
c_func
(paren
id|ptr
comma
id|buf
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_ne
l_int|0
)paren
(brace
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
id|res
op_assign
id|n
suffix:semicolon
r_break
suffix:semicolon
)brace
id|out
suffix:colon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_modify_ldt
r_int
id|sys_modify_ldt
c_func
(paren
r_int
id|func
comma
r_void
op_star
id|ptr
comma
r_int
r_int
id|bytecount
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|sys_modify_ldt_tt
comma
id|sys_modify_ldt_skas
comma
id|func
comma
id|ptr
comma
id|bytecount
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODE_TT
r_extern
r_int
id|arch_prctl
c_func
(paren
r_int
id|code
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|function|arch_prctl_tt
r_static
r_int
id|arch_prctl_tt
c_func
(paren
r_int
id|code
comma
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ARCH_SET_GS
suffix:colon
r_case
id|ARCH_SET_FS
suffix:colon
id|ret
op_assign
id|arch_prctl
c_func
(paren
id|code
comma
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_GET_FS
suffix:colon
r_case
id|ARCH_GET_GS
suffix:colon
id|ret
op_assign
id|arch_prctl
c_func
(paren
id|code
comma
(paren
r_int
r_int
)paren
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|ret
op_assign
id|put_user
c_func
(paren
id|tmp
comma
op_amp
id|addr
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MODE_SKAS
DECL|function|arch_prctl_skas
r_static
r_int
id|arch_prctl_skas
c_func
(paren
r_int
id|code
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ARCH_SET_GS
suffix:colon
id|current-&gt;thread.regs.regs.skas.regs
(braket
id|GS_BASE
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
op_assign
id|addr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_SET_FS
suffix:colon
id|current-&gt;thread.regs.regs.skas.regs
(braket
id|FS_BASE
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
op_assign
id|addr
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_GET_FS
suffix:colon
id|ret
op_assign
id|put_user
c_func
(paren
id|current-&gt;thread.regs.regs.skas.regs
(braket
id|GS
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
comma
op_amp
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_GET_GS
suffix:colon
id|ret
op_assign
id|put_user
c_func
(paren
id|current-&gt;thread.regs.regs.skas.regs
(braket
id|FS
op_div
r_sizeof
(paren
r_int
"&bslash;"
r_int
)paren
)braket
comma
op_amp
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_arch_prctl
r_int
id|sys_arch_prctl
c_func
(paren
r_int
id|code
comma
r_int
r_int
id|addr
)paren
(brace
r_return
id|CHOOSE_MODE_PROC
c_func
(paren
id|arch_prctl_tt
comma
id|arch_prctl_skas
comma
id|code
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|sys_clone
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|newsp
comma
r_void
id|__user
op_star
id|parent_tid
comma
r_void
id|__user
op_star
id|child_tid
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* XXX: normal arch do here this pass, and also pass the regs to&n;&t; * do_fork, instead of NULL. Currently the arch-independent code&n;&t; * ignores these values, while the UML code (actually it&squot;s&n;&t; * copy_thread) does the right thing. But this should change,&n;&t; probably. */
multiline_comment|/*if (!newsp)&n;&t;&t;newsp = UPT_SP(current-&gt;thread.regs);*/
id|current-&gt;thread.forking
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
l_int|NULL
comma
l_int|0
comma
id|parent_tid
comma
id|child_tid
)paren
suffix:semicolon
id|current-&gt;thread.forking
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
