multiline_comment|/*&n; *  linux/arch/x86-64/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; * &n; *  X86-64 port&n; *&t;Andi Kleen.&n; * &n; *  $Id: process.c,v 1.38 2002/01/15 10:08:03 ak Exp $&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/prctl.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/err.h&gt;
id|asmlinkage
r_extern
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|hlt_counter
r_int
id|hlt_counter
suffix:semicolon
multiline_comment|/*&n; * Powermanagement idle function, if any..&n; */
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
multiline_comment|/*&n; * We use this if we don&squot;t have any better&n; * idle routine..&n; */
DECL|function|default_idle
r_static
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|hlt_counter
)paren
(brace
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|need_resched
c_func
(paren
)paren
)paren
id|safe_halt
c_func
(paren
)paren
suffix:semicolon
r_else
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * On SMP it&squot;s slightly faster (but much more power-consuming!)&n; * to poll the -&gt;need_resched flag instead of waiting for the&n; * cross-CPU IPI to arrive. Use this option with caution.&n; */
DECL|function|poll_idle
r_static
r_void
id|poll_idle
(paren
r_void
)paren
(brace
r_int
id|oldval
suffix:semicolon
id|__sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Deal with another CPU just having chosen a thread to&n;&t; * run here:&n;&t; */
id|oldval
op_assign
id|test_and_clear_thread_flag
c_func
(paren
id|TIF_NEED_RESCHED
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldval
)paren
(brace
id|set_thread_flag
c_func
(paren
id|TIF_POLLING_NRFLAG
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;2:&quot;
l_string|&quot;testl %0,%1;&quot;
l_string|&quot;rep; nop;&quot;
l_string|&quot;je 2b;&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|_TIF_NEED_RESCHED
)paren
comma
l_string|&quot;m&quot;
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|set_need_resched
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
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
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|idle_setup
r_static
r_int
id|__init
id|idle_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;poll&quot;
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;using polling idle threads.&bslash;n&quot;
)paren
suffix:semicolon
id|pm_idle
op_assign
id|poll_idle
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;idle=&quot;
comma
id|idle_setup
)paren
suffix:semicolon
DECL|variable|no_idt
r_static
r_int
id|no_idt
(braket
l_int|3
)braket
suffix:semicolon
DECL|variable|reboot_mode
r_static
r_int
id|reboot_mode
suffix:semicolon
DECL|variable|reboot_thru_bios
r_int
id|reboot_thru_bios
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|reboot_smp
r_int
id|reboot_smp
op_assign
l_int|0
suffix:semicolon
DECL|variable|reboot_cpu
r_static
r_int
id|reboot_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* shamelessly grabbed from lib/vsprintf.c for readability */
DECL|macro|is_digit
mdefine_line|#define is_digit(c)&t;((c) &gt;= &squot;0&squot; &amp;&amp; (c) &lt;= &squot;9&squot;)
macro_line|#endif
DECL|function|reboot_setup
r_static
r_int
id|__init
id|reboot_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_switch
c_cond
(paren
op_star
id|str
)paren
(brace
r_case
l_char|&squot;w&squot;
suffix:colon
multiline_comment|/* &quot;warm&quot; reboot (no memory testing etc) */
id|reboot_mode
op_assign
l_int|0x1234
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
multiline_comment|/* &quot;cold&quot; reboot (with memory testing etc) */
id|reboot_mode
op_assign
l_int|0x0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
multiline_comment|/* &quot;bios&quot; reboot by jumping through the BIOS */
id|reboot_thru_bios
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
multiline_comment|/* &quot;hard&quot; reboot by toggling RESET and/or crashing the CPU */
id|reboot_thru_bios
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_case
l_char|&squot;s&squot;
suffix:colon
multiline_comment|/* &quot;smp&quot; reboot by executing reset on BSP or other CPU*/
id|reboot_smp
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|is_digit
c_func
(paren
op_star
(paren
id|str
op_plus
l_int|1
)paren
)paren
)paren
(brace
id|reboot_cpu
op_assign
(paren
r_int
)paren
(paren
op_star
(paren
id|str
op_plus
l_int|1
)paren
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_digit
c_func
(paren
op_star
(paren
id|str
op_plus
l_int|2
)paren
)paren
)paren
id|reboot_cpu
op_assign
id|reboot_cpu
op_star
l_int|10
op_plus
(paren
r_int
)paren
(paren
op_star
(paren
id|str
op_plus
l_int|2
)paren
op_minus
l_char|&squot;0&squot;
)paren
suffix:semicolon
)brace
multiline_comment|/* we will leave sorting out the final value &n;&t;&t;&t;&t;when we are ready to reboot, since we might not&n; &t;&t;&t;&t;have set up boot_cpu_id or smp_num_cpu */
r_break
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
(paren
id|str
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|str
op_increment
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;reboot=&quot;
comma
id|reboot_setup
)paren
suffix:semicolon
DECL|function|kb_wait
r_static
r_inline
r_void
id|kb_wait
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
l_int|0x10000
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
l_int|0x64
)paren
op_amp
l_int|0x02
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * Switch to real mode and then execute the code&n; * specified by the code and length parameters.&n; * We assume that length will aways be less that 100!&n; */
DECL|function|machine_real_restart
r_void
id|machine_real_restart
c_func
(paren
r_int
r_char
op_star
id|code
comma
r_int
id|length
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* This will have to be rewritten for sledgehammer. It would&n;&t;   help if sledgehammer have simple option to reset itself.&n;&t;*/
id|panic
c_func
(paren
l_string|&quot;real_restart is hard to do.&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
macro_line|#if CONFIG_SMP
r_int
id|cpuid
suffix:semicolon
id|cpuid
op_assign
id|GET_APIC_ID
c_func
(paren
id|apic_read
c_func
(paren
id|APIC_ID
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reboot_smp
)paren
(brace
multiline_comment|/* check to see if reboot_cpu is valid &n;&t;&t;   if its not, default to the BSP */
r_if
c_cond
(paren
(paren
id|reboot_cpu
op_eq
op_minus
l_int|1
)paren
op_logical_or
(paren
id|reboot_cpu
OG
(paren
id|NR_CPUS
op_minus
l_int|1
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|phys_cpu_present_map
op_amp
(paren
l_int|1
op_lshift
id|cpuid
)paren
)paren
)paren
id|reboot_cpu
op_assign
id|boot_cpu_id
suffix:semicolon
id|reboot_smp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* use this as a flag to only go through this once*/
multiline_comment|/* re-run this function on the other CPUs&n;&t;&t;   it will fall though this section since we have &n;&t;&t;   cleared reboot_smp, and do the reboot if it is the&n;&t;&t;   correct CPU, otherwise it halts. */
r_if
c_cond
(paren
id|reboot_cpu
op_ne
id|cpuid
)paren
id|smp_call_function
c_func
(paren
(paren
r_void
op_star
)paren
id|machine_restart
comma
l_int|NULL
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* if reboot_cpu is still -1, then we want a tradional reboot, &n;&t;   and if we are not running on the reboot_cpu,, halt */
r_if
c_cond
(paren
(paren
id|reboot_cpu
op_ne
op_minus
l_int|1
)paren
op_logical_and
(paren
id|cpuid
op_ne
id|reboot_cpu
)paren
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;hlt&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Stop all CPUs and turn off local APICs and the IO-APIC, so&n;&t; * other OSs see a clean IRQ state.&n;&t; */
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
id|disable_IO_APIC
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|reboot_thru_bios
)paren
(brace
multiline_comment|/* rebooting needs to touch the page at absolute addr 0 */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|__va
c_func
(paren
l_int|0x472
)paren
)paren
op_assign
id|reboot_mode
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
id|i
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
l_int|100
suffix:semicolon
id|i
op_increment
)paren
(brace
id|kb_wait
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xfe
comma
l_int|0x64
)paren
suffix:semicolon
multiline_comment|/* pulse reset low */
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
)brace
multiline_comment|/* That didn&squot;t work - force a triple fault.. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lidt %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|no_idt
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;int3&quot;
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;no bios restart currently&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
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
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pm_power_off
)paren
id|pm_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Prints also some state that isn&squot;t saved in the pt_regs */
DECL|function|show_regs
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|cr0
op_assign
l_int|0L
comma
id|cr2
op_assign
l_int|0L
comma
id|cr3
op_assign
l_int|0L
comma
id|cr4
op_assign
l_int|0L
comma
id|fs
comma
id|gs
suffix:semicolon
r_int
r_int
id|fsindex
comma
id|gsindex
suffix:semicolon
r_int
r_int
id|ds
comma
id|cs
comma
id|es
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Pid: %d, comm: %.20s %s&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
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
l_string|&quot;RIP: %04lx:[&lt;%016lx&gt;]&bslash;n&quot;
comma
id|regs-&gt;cs
op_amp
l_int|0xffff
comma
id|regs-&gt;rip
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RSP: %016lx  EFLAGS: %08lx&bslash;n&quot;
comma
id|regs-&gt;rsp
comma
id|regs-&gt;eflags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RAX: %016lx RBX: %016lx RCX: %016lx&bslash;n&quot;
comma
id|regs-&gt;rax
comma
id|regs-&gt;rbx
comma
id|regs-&gt;rcx
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RDX: %016lx RSI: %016lx RDI: %016lx&bslash;n&quot;
comma
id|regs-&gt;rdx
comma
id|regs-&gt;rsi
comma
id|regs-&gt;rdi
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RBP: %016lx R08: %016lx R09: %08lx&bslash;n&quot;
comma
id|regs-&gt;rbp
comma
id|regs-&gt;r8
comma
id|regs-&gt;r9
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R10: %016lx R11: %016lx R12: %016lx&bslash;n&quot;
comma
id|regs-&gt;r10
comma
id|regs-&gt;r11
comma
id|regs-&gt;r12
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R13: %016lx R14: %016lx R15: %016lx&bslash;n&quot;
comma
id|regs-&gt;r13
comma
id|regs-&gt;r14
comma
id|regs-&gt;r15
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%ds,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ds
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%es,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|es
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%cs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cs
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fsindex
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|gsindex
)paren
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
l_int|0xc0000100
comma
id|fs
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
l_int|0xc0000101
comma
id|gs
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr0
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr2
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr3, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr3
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movq %%cr4, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr4
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;FS: %016lx(%04x) GS:%016lx(%04x)&bslash;n&quot;
comma
id|fs
comma
id|fsindex
comma
id|gs
comma
id|gsindex
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CS: %04x DS:%04x ES:%04x CR0: %016lx&bslash;n&quot;
comma
id|cs
comma
id|ds
comma
id|es
comma
id|cr0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CR2: %016lx CR3: %016lx CR4: %016lx&bslash;n&quot;
comma
id|cr2
comma
id|cr3
comma
id|cr4
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * No need to lock the MM as we are the last user&n; */
DECL|function|release_segments
r_void
id|release_segments
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_void
op_star
id|ldt
op_assign
id|mm-&gt;context.segments
suffix:semicolon
multiline_comment|/*&n;&t; * free the LDT&n;&t; */
r_if
c_cond
(paren
id|ldt
)paren
(brace
id|mm-&gt;context.segments
op_assign
l_int|NULL
suffix:semicolon
id|clear_LDT
c_func
(paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|ldt
)paren
suffix:semicolon
)brace
)brace
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|__STR2
mdefine_line|#define __STR2(x) __STR(x)
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* nothing to do ... */
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|memset
c_func
(paren
id|tsk-&gt;thread.debugreg
comma
l_int|0
comma
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Forget coprocessor state..&n;&t; */
id|clear_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;used_math
op_assign
l_int|0
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
r_if
c_cond
(paren
id|dead_task-&gt;mm
)paren
(brace
r_void
op_star
id|ldt
op_assign
id|dead_task-&gt;mm-&gt;context.segments
suffix:semicolon
singleline_comment|// temporary debugging check
r_if
c_cond
(paren
id|ldt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: dead process %8s still has LDT? &lt;%p&gt;&bslash;n&quot;
comma
id|dead_task-&gt;comm
comma
id|ldt
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * we do not have to muck with descriptors here, that is&n; * done in switch_mm() as needed.&n; */
DECL|function|copy_segments
r_void
id|copy_segments
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|mm_struct
op_star
id|new_mm
)paren
(brace
r_struct
id|mm_struct
op_star
id|old_mm
suffix:semicolon
r_void
op_star
id|old_ldt
comma
op_star
id|ldt
suffix:semicolon
id|ldt
op_assign
l_int|NULL
suffix:semicolon
id|old_mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|old_mm
op_logical_and
(paren
id|old_ldt
op_assign
id|old_mm-&gt;context.segments
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n;&t;&t; * Completely new LDT, we initialize it from the parent:&n;&t;&t; */
id|ldt
op_assign
id|vmalloc
c_func
(paren
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ldt
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ldt allocation failed&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|ldt
comma
id|old_ldt
comma
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
)brace
id|new_mm-&gt;context.segments
op_assign
id|ldt
suffix:semicolon
id|new_mm-&gt;context.cpuvalid
op_assign
l_int|0UL
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|copy_thread
r_int
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
id|rsp
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
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
r_struct
id|task_struct
op_star
id|me
op_assign
id|current
suffix:semicolon
id|childregs
op_assign
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|THREAD_SIZE
op_plus
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
)paren
)paren
op_minus
l_int|1
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
id|childregs-&gt;rax
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;rsp
op_assign
id|rsp
suffix:semicolon
r_if
c_cond
(paren
id|rsp
op_eq
op_complement
l_int|0
)paren
(brace
id|childregs-&gt;rsp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
)brace
id|p-&gt;thread.rsp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.rsp0
op_assign
(paren
r_int
r_int
)paren
(paren
id|childregs
op_plus
l_int|1
)paren
suffix:semicolon
id|p-&gt;thread.userrsp
op_assign
id|current-&gt;thread.userrsp
suffix:semicolon
id|p-&gt;thread.rip
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|p-&gt;thread.fs
op_assign
id|me-&gt;thread.fs
suffix:semicolon
id|p-&gt;thread.gs
op_assign
id|me-&gt;thread.gs
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.gsindex
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.fsindex
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%es,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.es
)paren
)paren
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;movl %%ds,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|p-&gt;thread.ds
)paren
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
id|p-&gt;thread.i387
op_assign
id|current-&gt;thread.i387
suffix:semicolon
r_return
l_int|0
suffix:semicolon
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
id|regs-&gt;rsp
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
id|current-&gt;thread.debugreg
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
DECL|macro|SAVE
mdefine_line|#define SAVE(reg) dump-&gt;regs.reg = regs-&gt;reg
id|SAVE
c_func
(paren
id|rax
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|rbx
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|rcx
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|rdx
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|rsi
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|rdi
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|rbp
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r8
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r9
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r10
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r11
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r12
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r13
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r14
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|r15
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|orig_rax
)paren
suffix:semicolon
id|SAVE
c_func
(paren
id|rip
)paren
suffix:semicolon
DECL|macro|SAVE
macro_line|#undef SAVE
multiline_comment|/* FIXME: Should use symbolic names for msr-s! */
id|rdmsrl
c_func
(paren
l_int|0xc0000100
comma
id|dump-&gt;regs.fs_base
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
l_int|0xc0000101
comma
id|dump-&gt;regs.kernel_gs_base
)paren
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
)brace
multiline_comment|/*&n; * This special macro can be used to load a debugging register&n; */
DECL|macro|loaddebug
mdefine_line|#define loaddebug(thread,register) &bslash;&n;&t;&t;set_debug(thread-&gt;debugreg[register], register)
multiline_comment|/*&n; *&t;switch_to(x,y) should switch tasks from x to y.&n; *&n; * We fsave/fwait so that an exception goes off at the right time&n; * (as a call from the fsave or fwait in effect) rather than to&n; * the wrong process. &n; * &n; * This could still be optimized: &n; * - fold all the options into a flag word and test it with a single test.&n; * - could test fs/gs bitsliced&n; */
DECL|function|__switch_to
r_void
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev_p
comma
r_struct
id|task_struct
op_star
id|next_p
)paren
(brace
r_struct
id|thread_struct
op_star
id|prev
op_assign
op_amp
id|prev_p-&gt;thread
comma
op_star
id|next
op_assign
op_amp
id|next_p-&gt;thread
suffix:semicolon
r_struct
id|tss_struct
op_star
id|tss
op_assign
id|init_tss
op_plus
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|prev_p
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reload esp0, LDT and the page table pointer:&n;&t; */
id|tss-&gt;rsp0
op_assign
id|next-&gt;rsp0
suffix:semicolon
multiline_comment|/* &n;&t; * Switch DS and ES.&n;&t; * XXX: check if this is safe on SMP&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %%es,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|prev-&gt;es
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;es
op_ne
id|prev-&gt;es
)paren
)paren
id|loadsegment
c_func
(paren
id|es
comma
id|next-&gt;es
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%ds,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|prev-&gt;ds
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;ds
op_ne
id|prev-&gt;ds
)paren
)paren
id|loadsegment
c_func
(paren
id|ds
comma
id|next-&gt;ds
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Switch FS and GS.&n;&t; */
(brace
r_int
r_int
id|fsindex
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=g&quot;
(paren
id|fsindex
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|fsindex
op_ne
id|prev-&gt;fsindex
)paren
)paren
id|prev-&gt;fs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|fsindex
op_or
id|next-&gt;fsindex
)paren
op_logical_or
id|prev-&gt;fs
)paren
)paren
id|loadsegment
c_func
(paren
id|fs
comma
id|next-&gt;fsindex
)paren
suffix:semicolon
multiline_comment|/* Should use a shortcut via a GDT entry if next-&gt;fs is 32bit */
r_if
c_cond
(paren
id|fsindex
op_ne
id|prev-&gt;fsindex
op_logical_or
id|next-&gt;fs
op_ne
id|prev-&gt;fs
)paren
id|wrmsrl
c_func
(paren
id|MSR_FS_BASE
comma
id|next-&gt;fs
)paren
suffix:semicolon
id|prev-&gt;fsindex
op_assign
id|fsindex
suffix:semicolon
)brace
(brace
r_int
r_int
id|gsindex
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=g&quot;
(paren
id|gsindex
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|gsindex
op_ne
id|prev-&gt;gsindex
)paren
)paren
id|prev-&gt;gs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
(paren
id|gsindex
op_or
id|next-&gt;gsindex
)paren
op_logical_or
id|prev-&gt;gs
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* could load gs in syscall exit after swapgs instead */
r_int
id|nr
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|loadsegment
c_func
(paren
id|gs
comma
id|next-&gt;gsindex
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_GS_BASE
comma
id|cpu_pda
op_plus
id|nr
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|gsindex
op_ne
id|prev-&gt;gsindex
op_logical_or
(paren
id|prev-&gt;gs
op_or
id|next-&gt;gs
)paren
)paren
id|wrmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
id|next-&gt;gs
)paren
suffix:semicolon
id|prev-&gt;gsindex
op_assign
id|gsindex
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Switch the PDA context.&n;&t; */
id|prev-&gt;userrsp
op_assign
id|read_pda
c_func
(paren
id|oldrsp
)paren
suffix:semicolon
id|write_pda
c_func
(paren
id|oldrsp
comma
id|next-&gt;userrsp
)paren
suffix:semicolon
id|write_pda
c_func
(paren
id|pcurrent
comma
id|next_p
)paren
suffix:semicolon
id|write_pda
c_func
(paren
id|kernelstack
comma
(paren
r_int
r_int
)paren
id|next_p-&gt;thread_info
op_plus
id|THREAD_SIZE
op_minus
id|PDA_STACKOFFSET
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now maybe reload the debug registers&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;debugreg
(braket
l_int|7
)braket
)paren
)paren
(brace
id|loaddebug
c_func
(paren
id|next
comma
l_int|0
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|1
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|2
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* no 4 and 5 */
id|loaddebug
c_func
(paren
id|next
comma
l_int|6
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|7
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Handle the IO bitmap &n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|prev-&gt;ioperm
op_or
id|next-&gt;ioperm
)paren
)paren
(brace
r_if
c_cond
(paren
id|next-&gt;ioperm
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 4 cachelines copy ... not good, but not that&n;&t;&t;&t; * bad either. Anyone got something better?&n;&t;&t;&t; * This only affects processes which use ioperm().&n;&t;&t;&t; * [Putting the TSSs into 4k-tlb mapped regions&n;&t;&t;&t; * and playing VM tricks to switch the IO bitmap&n;&t;&t;&t; * is not really acceptable.]&n;&t;&t;&t; * On x86-64 we could put multiple bitmaps into &n;&t;&t;&t; * the GDT and just switch offsets&n;&t;&t;&t; * This would require ugly special cases on overflow&n;&t;&t;&t; * though -AK &n;&t;&t;&t; */
id|memcpy
c_func
(paren
id|tss-&gt;io_bitmap
comma
id|next-&gt;io_bitmap
comma
id|IO_BITMAP_SIZE
op_star
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
id|tss-&gt;io_map_base
op_assign
id|IO_BITMAP_OFFSET
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * a bitmap offset pointing outside of the TSS limit&n;&t;&t;&t; * causes a nicely controllable SIGSEGV if a process&n;&t;&t;&t; * tries to use a port IO instruction. The first&n;&t;&t;&t; * sys_ioperm() call sets up the bitmap properly.&n;&t;&t;&t; */
id|tss-&gt;io_map_base
op_assign
id|INVALID_IO_BITMAP_OFFSET
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
id|asmlinkage
DECL|function|sys_execve
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|name
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
id|name
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
r_return
id|error
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
r_return
id|error
suffix:semicolon
)brace
DECL|function|set_personality_64bit
r_void
id|set_personality_64bit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* inherit personality from parent */
multiline_comment|/* Make sure to be in 64bit mode */
id|clear_thread_flag
c_func
(paren
id|TIF_IA32
)paren
suffix:semicolon
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.rsp
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sys_clone
id|asmlinkage
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
r_struct
id|pt_regs
id|regs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.rsp
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is trivial, and on the face of it looks like it&n; * could equally well be done in user mode.&n; *&n; * Not so, for quite unobvious reasons - register pressure.&n; * In user mode vfork() cannot have a stack frame, and if&n; * done by calling the &quot;clone()&quot; system call directly, you&n; * do not have enough call-clobbered registers to hold all&n; * the information you need.&n; */
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|regs.rsp
comma
op_amp
id|regs
comma
l_int|0
)paren
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
multiline_comment|/* &n; * Do a traceback through the scheduler to find where a process sleeps.&n; * &n; * Currently sched.c is compiled with -fno-omit-frame-pointer, so we&n; * just go through the stack frames. &n; */
DECL|function|get_wchan
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|macro|last_sched
macro_line|#undef last_sched
DECL|macro|first_sched
macro_line|#undef first_sched
DECL|function|sys_arch_prctl
id|asmlinkage
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
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tmp
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
id|asm
r_volatile
(paren
l_string|&quot;movw %%gs,%0&quot;
suffix:colon
l_string|&quot;=g&quot;
(paren
id|current-&gt;thread.gsindex
)paren
)paren
suffix:semicolon
id|current-&gt;thread.gs
op_assign
id|addr
suffix:semicolon
id|ret
op_assign
id|checking_wrmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_SET_FS
suffix:colon
id|asm
r_volatile
(paren
l_string|&quot;movw %%fs,%0&quot;
suffix:colon
l_string|&quot;=g&quot;
(paren
id|current-&gt;thread.fsindex
)paren
)paren
suffix:semicolon
id|current-&gt;thread.fs
op_assign
id|addr
suffix:semicolon
id|ret
op_assign
id|checking_wrmsrl
c_func
(paren
id|MSR_FS_BASE
comma
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Returned value may not be correct when the user changed fs/gs */
r_case
id|ARCH_GET_FS
suffix:colon
id|rdmsrl
c_func
(paren
id|MSR_FS_BASE
comma
id|tmp
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
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARCH_GET_GS
suffix:colon
id|rdmsrl
c_func
(paren
id|MSR_KERNEL_GS_BASE
comma
id|tmp
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
eof