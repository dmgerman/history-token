multiline_comment|/*&n; * IA32 helper functions&n; *&n; * Copyright (C) 1999 Arun Sharma &lt;arun.sharma@intel.com&gt;&n; * Copyright (C) 2000 Asit K. Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 2001-2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * 06/16/00&t;A. Mallick&t;added csd/ssd/tssd for ia32 thread context&n; * 02/19/01&t;D. Mosberger&t;dropped tssd; it&squot;s not needed&n; * 09/14/01&t;D. Mosberger&t;fixed memory management for gdt/tss page&n; * 09/29/01&t;D. Mosberger&t;added ia32_load_segment_descriptors()&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &quot;ia32priv.h&quot;
r_extern
r_void
id|die_if_kernel
(paren
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
suffix:semicolon
DECL|variable|ia32_exec_domain
r_struct
id|exec_domain
id|ia32_exec_domain
suffix:semicolon
DECL|variable|ia32_shared_page
r_struct
id|page
op_star
id|ia32_shared_page
(braket
(paren
l_int|2
op_star
id|IA32_PAGE_SIZE
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_div
id|PAGE_SIZE
)braket
suffix:semicolon
DECL|variable|ia32_gdt
r_int
r_int
op_star
id|ia32_gdt
suffix:semicolon
r_static
r_int
r_int
DECL|function|load_desc
id|load_desc
(paren
id|u16
id|selector
)paren
(brace
r_int
r_int
op_star
id|table
comma
id|limit
comma
id|index
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|selector
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|selector
op_amp
id|IA32_SEGSEL_TI
)paren
(brace
id|table
op_assign
(paren
r_int
r_int
op_star
)paren
id|IA32_LDT_OFFSET
suffix:semicolon
id|limit
op_assign
id|IA32_LDT_ENTRIES
suffix:semicolon
)brace
r_else
(brace
id|table
op_assign
id|ia32_gdt
suffix:semicolon
id|limit
op_assign
id|IA32_PAGE_SIZE
op_div
r_sizeof
(paren
id|ia32_gdt
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
id|index
op_assign
id|selector
op_rshift
id|IA32_SEGSEL_INDEX_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|index
op_ge
id|limit
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|IA32_SEG_UNSCRAMBLE
c_func
(paren
id|table
(braket
id|index
)braket
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia32_load_segment_descriptors
id|ia32_load_segment_descriptors
(paren
r_struct
id|task_struct
op_star
id|task
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|ia64_task_regs
c_func
(paren
id|task
)paren
suffix:semicolon
multiline_comment|/* Setup the segment descriptors */
id|regs-&gt;r24
op_assign
id|load_desc
c_func
(paren
id|regs-&gt;r16
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* ESD */
id|regs-&gt;r27
op_assign
id|load_desc
c_func
(paren
id|regs-&gt;r16
op_rshift
l_int|0
)paren
suffix:semicolon
multiline_comment|/* DSD */
id|regs-&gt;r28
op_assign
id|load_desc
c_func
(paren
id|regs-&gt;r16
op_rshift
l_int|32
)paren
suffix:semicolon
multiline_comment|/* FSD */
id|regs-&gt;r29
op_assign
id|load_desc
c_func
(paren
id|regs-&gt;r16
op_rshift
l_int|48
)paren
suffix:semicolon
multiline_comment|/* GSD */
id|regs-&gt;ar_csd
op_assign
id|load_desc
c_func
(paren
id|regs-&gt;r17
op_rshift
l_int|0
)paren
suffix:semicolon
multiline_comment|/* CSD */
id|regs-&gt;ar_ssd
op_assign
id|load_desc
c_func
(paren
id|regs-&gt;r17
op_rshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* SSD */
)brace
r_void
DECL|function|ia32_save_state
id|ia32_save_state
(paren
r_struct
id|task_struct
op_star
id|t
)paren
(brace
r_int
r_int
id|eflag
comma
id|fsr
comma
id|fcr
comma
id|fir
comma
id|fdr
suffix:semicolon
id|asm
(paren
l_string|&quot;mov %0=ar.eflag;&quot;
l_string|&quot;mov %1=ar.fsr;&quot;
l_string|&quot;mov %2=ar.fcr;&quot;
l_string|&quot;mov %3=ar.fir;&quot;
l_string|&quot;mov %4=ar.fdr;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|eflag
)paren
comma
l_string|&quot;=r&quot;
(paren
id|fsr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|fcr
)paren
comma
l_string|&quot;=r&quot;
(paren
id|fir
)paren
comma
l_string|&quot;=r&quot;
(paren
id|fdr
)paren
)paren
suffix:semicolon
id|t-&gt;thread.eflag
op_assign
id|eflag
suffix:semicolon
id|t-&gt;thread.fsr
op_assign
id|fsr
suffix:semicolon
id|t-&gt;thread.fcr
op_assign
id|fcr
suffix:semicolon
id|t-&gt;thread.fir
op_assign
id|fir
suffix:semicolon
id|t-&gt;thread.fdr
op_assign
id|fdr
suffix:semicolon
id|ia64_set_kr
c_func
(paren
id|IA64_KR_IO_BASE
comma
id|t-&gt;thread.old_iob
)paren
suffix:semicolon
id|ia64_set_kr
c_func
(paren
id|IA64_KR_TSSD
comma
id|t-&gt;thread.old_k1
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia32_load_state
id|ia32_load_state
(paren
r_struct
id|task_struct
op_star
id|t
)paren
(brace
r_int
r_int
id|eflag
comma
id|fsr
comma
id|fcr
comma
id|fir
comma
id|fdr
comma
id|tssd
suffix:semicolon
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|ia64_task_regs
c_func
(paren
id|t
)paren
suffix:semicolon
r_int
id|nr
op_assign
id|get_cpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* LDT and TSS depend on CPU number: */
id|eflag
op_assign
id|t-&gt;thread.eflag
suffix:semicolon
id|fsr
op_assign
id|t-&gt;thread.fsr
suffix:semicolon
id|fcr
op_assign
id|t-&gt;thread.fcr
suffix:semicolon
id|fir
op_assign
id|t-&gt;thread.fir
suffix:semicolon
id|fdr
op_assign
id|t-&gt;thread.fdr
suffix:semicolon
id|tssd
op_assign
id|load_desc
c_func
(paren
id|_TSS
c_func
(paren
id|nr
)paren
)paren
suffix:semicolon
multiline_comment|/* TSSD */
id|asm
r_volatile
(paren
l_string|&quot;mov ar.eflag=%0;&quot;
l_string|&quot;mov ar.fsr=%1;&quot;
l_string|&quot;mov ar.fcr=%2;&quot;
l_string|&quot;mov ar.fir=%3;&quot;
l_string|&quot;mov ar.fdr=%4;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|eflag
)paren
comma
l_string|&quot;r&quot;
(paren
id|fsr
)paren
comma
l_string|&quot;r&quot;
(paren
id|fcr
)paren
comma
l_string|&quot;r&quot;
(paren
id|fir
)paren
comma
l_string|&quot;r&quot;
(paren
id|fdr
)paren
)paren
suffix:semicolon
id|current-&gt;thread.old_iob
op_assign
id|ia64_get_kr
c_func
(paren
id|IA64_KR_IO_BASE
)paren
suffix:semicolon
id|current-&gt;thread.old_k1
op_assign
id|ia64_get_kr
c_func
(paren
id|IA64_KR_TSSD
)paren
suffix:semicolon
id|ia64_set_kr
c_func
(paren
id|IA64_KR_IO_BASE
comma
id|IA32_IOBASE
)paren
suffix:semicolon
id|ia64_set_kr
c_func
(paren
id|IA64_KR_TSSD
comma
id|tssd
)paren
suffix:semicolon
id|regs-&gt;r17
op_assign
(paren
id|_TSS
c_func
(paren
id|nr
)paren
op_lshift
l_int|48
)paren
op_or
(paren
id|_LDT
c_func
(paren
id|nr
)paren
op_lshift
l_int|32
)paren
op_or
(paren
id|__u32
)paren
id|regs-&gt;r17
suffix:semicolon
id|regs-&gt;r30
op_assign
id|load_desc
c_func
(paren
id|_LDT
c_func
(paren
id|nr
)paren
)paren
suffix:semicolon
multiline_comment|/* LDTD */
id|put_cpu
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup IA32 GDT and TSS&n; */
r_void
DECL|function|ia32_gdt_init
id|ia32_gdt_init
(paren
r_void
)paren
(brace
r_int
r_int
op_star
id|tss
suffix:semicolon
r_int
r_int
id|ldt_size
suffix:semicolon
r_int
id|nr
suffix:semicolon
id|ia32_shared_page
(braket
l_int|0
)braket
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
id|ia32_gdt
op_assign
id|page_address
c_func
(paren
id|ia32_shared_page
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|tss
op_assign
id|ia32_gdt
op_plus
id|IA32_PAGE_SIZE
op_div
r_sizeof
(paren
id|ia32_gdt
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IA32_PAGE_SIZE
op_eq
id|PAGE_SIZE
)paren
(brace
id|ia32_shared_page
(braket
l_int|1
)braket
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
id|tss
op_assign
id|page_address
c_func
(paren
id|ia32_shared_page
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* CS descriptor in IA-32 (scrambled) format */
id|ia32_gdt
(braket
id|__USER_CS
op_rshift
l_int|3
)braket
op_assign
id|IA32_SEG_DESCRIPTOR
c_func
(paren
l_int|0
comma
(paren
id|IA32_PAGE_OFFSET
op_minus
l_int|1
)paren
op_rshift
id|IA32_PAGE_SHIFT
comma
l_int|0xb
comma
l_int|1
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* DS descriptor in IA-32 (scrambled) format */
id|ia32_gdt
(braket
id|__USER_DS
op_rshift
l_int|3
)braket
op_assign
id|IA32_SEG_DESCRIPTOR
c_func
(paren
l_int|0
comma
(paren
id|IA32_PAGE_OFFSET
op_minus
l_int|1
)paren
op_rshift
id|IA32_PAGE_SHIFT
comma
l_int|0x3
comma
l_int|1
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* We never change the TSS and LDT descriptors, so we can share them across all CPUs.  */
id|ldt_size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|IA32_LDT_ENTRIES
op_star
id|IA32_LDT_ENTRY_SIZE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
l_int|0
suffix:semicolon
id|nr
OL
id|NR_CPUS
suffix:semicolon
op_increment
id|nr
)paren
(brace
id|ia32_gdt
(braket
id|_TSS
c_func
(paren
id|nr
)paren
op_rshift
id|IA32_SEGSEL_INDEX_SHIFT
)braket
op_assign
id|IA32_SEG_DESCRIPTOR
c_func
(paren
id|IA32_TSS_OFFSET
comma
l_int|235
comma
l_int|0xb
comma
l_int|0
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|ia32_gdt
(braket
id|_LDT
c_func
(paren
id|nr
)paren
op_rshift
id|IA32_SEGSEL_INDEX_SHIFT
)braket
op_assign
id|IA32_SEG_DESCRIPTOR
c_func
(paren
id|IA32_LDT_OFFSET
comma
id|ldt_size
op_minus
l_int|1
comma
l_int|0x2
comma
l_int|0
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Handle bad IA32 interrupt via syscall&n; */
r_void
DECL|function|ia32_bad_interrupt
id|ia32_bad_interrupt
(paren
r_int
r_int
id|int_num
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|siginfo_t
id|siginfo
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Bad IA-32 interrupt&quot;
comma
id|regs
comma
id|int_num
)paren
suffix:semicolon
id|siginfo.si_signo
op_assign
id|SIGTRAP
suffix:semicolon
id|siginfo.si_errno
op_assign
id|int_num
suffix:semicolon
multiline_comment|/* XXX is it OK to abuse si_errno like this? */
id|siginfo.si_flags
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_isr
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_addr
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_imm
op_assign
l_int|0
suffix:semicolon
id|siginfo.si_code
op_assign
id|TRAP_BRKPT
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGTRAP
comma
op_amp
id|siginfo
comma
id|current
)paren
suffix:semicolon
)brace
r_void
DECL|function|ia32_cpu_init
id|ia32_cpu_init
(paren
r_void
)paren
(brace
multiline_comment|/* initialize global ia32 state - CR0 and CR4 */
id|asm
r_volatile
(paren
l_string|&quot;mov ar.cflg = %0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
(paren
id|ulong
)paren
id|IA32_CR4
op_lshift
l_int|32
)paren
op_or
id|IA32_CR0
)paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|ia32_init
id|ia32_init
(paren
r_void
)paren
(brace
id|ia32_exec_domain.name
op_assign
l_string|&quot;Linux/x86&quot;
suffix:semicolon
id|ia32_exec_domain.handler
op_assign
l_int|NULL
suffix:semicolon
id|ia32_exec_domain.pers_low
op_assign
id|PER_LINUX32
suffix:semicolon
id|ia32_exec_domain.pers_high
op_assign
id|PER_LINUX32
suffix:semicolon
id|ia32_exec_domain.signal_map
op_assign
id|default_exec_domain.signal_map
suffix:semicolon
id|ia32_exec_domain.signal_invmap
op_assign
id|default_exec_domain.signal_invmap
suffix:semicolon
id|register_exec_domain
c_func
(paren
op_amp
id|ia32_exec_domain
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ia32_init
id|__initcall
c_func
(paren
id|ia32_init
)paren
suffix:semicolon
eof
