multiline_comment|/*&n; * linux/arch/i386/kernel/sysenter.c&n; *&n; * (C) Copyright 2002 Linus Torvalds&n; *&n; * This file contains the needed initializations to support sysenter.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/cpufeature.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
r_extern
id|asmlinkage
r_void
id|sysenter_entry
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Create a per-cpu fake &quot;SEP thread&quot; stack, so that we can&n; * enter the kernel without having to worry about things like&n; * &quot;current&quot; etc not working (debug traps and NMI&squot;s can happen&n; * before we can switch over to the &quot;real&quot; thread).&n; *&n; * Return the resulting fake stack pointer.&n; */
DECL|struct|fake_sep_struct
r_struct
id|fake_sep_struct
(brace
DECL|member|thread
r_struct
id|thread_info
id|thread
suffix:semicolon
DECL|member|task
r_struct
id|task_struct
id|task
suffix:semicolon
DECL|member|trampoline
r_int
r_char
id|trampoline
(braket
l_int|32
)braket
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|1024
)paren
)paren
)paren
suffix:semicolon
DECL|member|stack
r_int
r_char
id|stack
(braket
l_int|0
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|aligned
c_func
(paren
l_int|8192
)paren
)paren
)paren
suffix:semicolon
DECL|function|enable_sep_cpu
r_void
id|enable_sep_cpu
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_int
id|cpu
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
r_struct
id|tss_struct
op_star
id|tss
op_assign
id|init_tss
op_plus
id|cpu
suffix:semicolon
id|tss-&gt;ss1
op_assign
id|__KERNEL_CS
suffix:semicolon
id|tss-&gt;esp1
op_assign
r_sizeof
(paren
r_struct
id|tss_struct
)paren
op_plus
(paren
r_int
r_int
)paren
id|tss
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_SYSENTER_CS
comma
id|__KERNEL_CS
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_SYSENTER_ESP
comma
id|tss-&gt;esp1
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_SYSENTER_EIP
comma
(paren
r_int
r_int
)paren
id|sysenter_entry
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Enabling SEP on CPU %d&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sysenter_setup
r_static
r_int
id|__init
id|sysenter_setup
c_func
(paren
r_void
)paren
(brace
r_static
r_const
r_char
id|int80
(braket
)braket
op_assign
(brace
l_int|0xcd
comma
l_int|0x80
comma
multiline_comment|/* int $0x80 */
l_int|0xc3
multiline_comment|/* ret */
)brace
suffix:semicolon
r_static
r_const
r_char
id|sysent
(braket
)braket
op_assign
(brace
l_int|0x51
comma
multiline_comment|/* push %ecx */
l_int|0x52
comma
multiline_comment|/* push %edx */
l_int|0x55
comma
multiline_comment|/* push %ebp */
multiline_comment|/* 3: backjump target */
l_int|0x89
comma
l_int|0xe5
comma
multiline_comment|/* movl %esp,%ebp */
l_int|0x0f
comma
l_int|0x34
comma
multiline_comment|/* sysenter */
multiline_comment|/* 7: align return point with nop&squot;s to make disassembly easier */
l_int|0x90
comma
l_int|0x90
comma
l_int|0x90
comma
l_int|0x90
comma
l_int|0x90
comma
l_int|0x90
comma
l_int|0x90
comma
multiline_comment|/* 14: System call restart point is here! (SYSENTER_RETURN - 2) */
l_int|0xeb
comma
l_int|0xf3
comma
multiline_comment|/* jmp to &quot;movl %esp,%ebp&quot; */
multiline_comment|/* 16: System call normal return point is here! (SYSENTER_RETURN in entry.S) */
l_int|0x5d
comma
multiline_comment|/* pop %ebp */
l_int|0x5a
comma
multiline_comment|/* pop %edx */
l_int|0x59
comma
multiline_comment|/* pop %ecx */
l_int|0xc3
multiline_comment|/* ret */
)brace
suffix:semicolon
r_static
r_const
r_char
id|sigreturn
(braket
)braket
op_assign
(brace
multiline_comment|/* 32: sigreturn point */
l_int|0x58
comma
multiline_comment|/* popl %eax */
l_int|0xb8
comma
id|__NR_sigreturn
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* movl $__NR_sigreturn, %eax */
l_int|0xcd
comma
l_int|0x80
comma
multiline_comment|/* int $0x80 */
)brace
suffix:semicolon
r_static
r_const
r_char
id|rt_sigreturn
(braket
)braket
op_assign
(brace
multiline_comment|/* 64: rt_sigreturn point */
l_int|0xb8
comma
id|__NR_rt_sigreturn
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* movl $__NR_rt_sigreturn, %eax */
l_int|0xcd
comma
l_int|0x80
comma
multiline_comment|/* int $0x80 */
)brace
suffix:semicolon
r_int
r_int
id|page
op_assign
id|get_zeroed_page
c_func
(paren
id|GFP_ATOMIC
)paren
suffix:semicolon
id|__set_fixmap
c_func
(paren
id|FIX_VSYSCALL
comma
id|__pa
c_func
(paren
id|page
)paren
comma
id|PAGE_READONLY
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
id|int80
comma
r_sizeof
(paren
id|int80
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|page
op_plus
l_int|32
)paren
comma
id|sigreturn
comma
r_sizeof
(paren
id|sigreturn
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|page
op_plus
l_int|64
)paren
comma
id|rt_sigreturn
comma
r_sizeof
(paren
id|rt_sigreturn
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|boot_cpu_has
c_func
(paren
id|X86_FEATURE_SEP
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
id|sysent
comma
r_sizeof
(paren
id|sysent
)paren
)paren
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|enable_sep_cpu
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sysenter_setup
id|__initcall
c_func
(paren
id|sysenter_setup
)paren
suffix:semicolon
eof
