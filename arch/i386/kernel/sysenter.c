multiline_comment|/*&n; * linux/arch/i386/kernel/sysenter.c&n; *&n; * (C) Copyright 2002 Linus Torvalds&n; *&n; * This file contains the needed initializations to support sysenter.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/thread_info.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/gfp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
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
op_amp
id|per_cpu
c_func
(paren
id|init_tss
comma
id|cpu
)paren
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
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * These symbols are defined by vsyscall.o to mark the bounds&n; * of the ELF DSO images included therein.&n; */
r_extern
r_const
r_char
id|vsyscall_int80_start
comma
id|vsyscall_int80_end
suffix:semicolon
r_extern
r_const
r_char
id|vsyscall_sysenter_start
comma
id|vsyscall_sysenter_end
suffix:semicolon
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
r_void
op_star
id|page
op_assign
(paren
r_void
op_star
)paren
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
id|PAGE_READONLY_EXEC
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
(brace
id|memcpy
c_func
(paren
id|page
comma
op_amp
id|vsyscall_int80_start
comma
op_amp
id|vsyscall_int80_end
op_minus
op_amp
id|vsyscall_int80_start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|page
comma
op_amp
id|vsyscall_sysenter_start
comma
op_amp
id|vsyscall_sysenter_end
op_minus
op_amp
id|vsyscall_sysenter_start
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
