multiline_comment|/*&n; *  linux/arch/i386/kernel/reboot.c&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;mach_reboot.h&quot;
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
DECL|variable|no_idt
r_static
r_int
id|no_idt
(braket
l_int|2
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
multiline_comment|/* The following code and data reboots the machine by switching to real&n;   mode and jumping to the BIOS reset entry point, as if the CPU has&n;   really been reset.  The previous version asked the keyboard&n;   controller to pulse the CPU reset line, which is more thorough, but&n;   doesn&squot;t work with at least one type of 486 motherboard.  It is easy&n;   to stop this code working; hence the copious comments. */
r_static
r_int
r_int
r_int
DECL|variable|real_mode_gdt_entries
id|real_mode_gdt_entries
(braket
l_int|3
)braket
op_assign
(brace
l_int|0x0000000000000000ULL
comma
multiline_comment|/* Null descriptor */
l_int|0x00009a000000ffffULL
comma
multiline_comment|/* 16-bit real-mode 64k code at 0x00000000 */
l_int|0x000092000100ffffULL
multiline_comment|/* 16-bit real-mode 64k data at 0x00000100 */
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|size
r_int
r_int
id|size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|base
r_int
r_int
r_int
op_star
id|base
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
DECL|variable|real_mode_gdt
id|real_mode_gdt
op_assign
(brace
r_sizeof
(paren
id|real_mode_gdt_entries
)paren
op_minus
l_int|1
comma
id|real_mode_gdt_entries
)brace
comma
DECL|variable|real_mode_idt
id|real_mode_idt
op_assign
(brace
l_int|0x3ff
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* This is 16-bit protected mode code to disable paging and the cache,&n;   switch to real mode and jump to the BIOS reset code.&n;&n;   The instruction that switches to real mode by writing to CR0 must be&n;   followed immediately by a far jump instruction, which set CS to a&n;   valid value for real mode, and flushes the prefetch queue to avoid&n;   running instructions that have already been decoded in protected&n;   mode.&n;&n;   Clears all the flags except ET, especially PG (paging), PE&n;   (protected-mode enable) and TS (task switch for coprocessor state&n;   save).  Flushes the TLB after paging has been disabled.  Sets CD and&n;   NW, to disable the cache on a 486, and invalidates the cache.  This&n;   is more like the state of a 486 after reset.  I don&squot;t know if&n;   something else should be done for other chips.&n;&n;   More could be done here to set up the registers as if a CPU reset had&n;   occurred; hopefully real BIOSs don&squot;t assume much. */
DECL|variable|real_mode_switch
r_static
r_int
r_char
id|real_mode_switch
(braket
)braket
op_assign
(brace
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x20
comma
l_int|0xc0
comma
multiline_comment|/*    movl  %cr0,%eax        */
l_int|0x66
comma
l_int|0x83
comma
l_int|0xe0
comma
l_int|0x11
comma
multiline_comment|/*    andl  $0x00000011,%eax */
l_int|0x66
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x60
comma
multiline_comment|/*    orl   $0x60000000,%eax */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x22
comma
l_int|0xc0
comma
multiline_comment|/*    movl  %eax,%cr0        */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x22
comma
l_int|0xd8
comma
multiline_comment|/*    movl  %eax,%cr3        */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x20
comma
l_int|0xc3
comma
multiline_comment|/*    movl  %cr0,%ebx        */
l_int|0x66
comma
l_int|0x81
comma
l_int|0xe3
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x60
comma
multiline_comment|/*    andl  $0x60000000,%ebx */
l_int|0x74
comma
l_int|0x02
comma
multiline_comment|/*    jz    f                */
l_int|0x0f
comma
l_int|0x09
comma
multiline_comment|/*    wbinvd                 */
l_int|0x24
comma
l_int|0x10
comma
multiline_comment|/* f: andb  $0x10,al         */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x22
comma
l_int|0xc0
multiline_comment|/*    movl  %eax,%cr0        */
)brace
suffix:semicolon
DECL|variable|jump_to_bios
r_static
r_int
r_char
id|jump_to_bios
(braket
)braket
op_assign
(brace
l_int|0xea
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xff
comma
l_int|0xff
multiline_comment|/*    ljmp  $0xffff,$0x0000  */
)brace
suffix:semicolon
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
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Write zero to CMOS register number 0x0f, which the BIOS POST&n;&t;   routine will recognize as telling it to do a proper reboot.  (Well&n;&t;   that&squot;s what this book in front of me says -- it may only apply to&n;&t;   the Phoenix BIOS though, it&squot;s not clear).  At the same time,&n;&t;   disable NMIs by setting the top bit in the CMOS address register,&n;&t;   as we&squot;re about to do peculiar things to the CPU.  I&squot;m not sure if&n;&t;   `outb_p&squot; is needed instead of just `outb&squot;.  Use it to be on the&n;&t;   safe side.  (Yes, CMOS_WRITE does outb_p&squot;s. -  Paul G.)&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
l_int|0x00
comma
l_int|0x8f
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|rtc_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Remap the kernel at virtual address zero, as well as offset zero&n;&t;   from the kernel segment.  This assumes the kernel segment starts at&n;&t;   virtual address PAGE_OFFSET. */
id|memcpy
(paren
id|swapper_pg_dir
comma
id|swapper_pg_dir
op_plus
id|USER_PGD_PTRS
comma
r_sizeof
(paren
id|swapper_pg_dir
(braket
l_int|0
)braket
)paren
op_star
id|KERNEL_PGD_PTRS
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Use `swapper_pg_dir&squot; as our page directory.&n;&t; */
id|load_cr3
c_func
(paren
id|swapper_pg_dir
)paren
suffix:semicolon
multiline_comment|/* Write 0x1234 to absolute memory location 0x472.  The BIOS reads&n;&t;   this on booting to tell it to &quot;Bypass memory test (also warm&n;&t;   boot)&quot;.  This seems like a fairly standard thing that gets set by&n;&t;   REBOOT.COM programs, and the previous reset routine did this&n;&t;   too. */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0x472
)paren
op_assign
id|reboot_mode
suffix:semicolon
multiline_comment|/* For the switch to real mode, copy some code to low memory.  It has&n;&t;   to be in the first 64k because it is running in 16-bit mode, and it&n;&t;   has to have the same physical and virtual address, because it turns&n;&t;   off paging.  Copy it near the end of the first page, out of the way&n;&t;   of BIOS variables. */
id|memcpy
(paren
(paren
r_void
op_star
)paren
(paren
l_int|0x1000
op_minus
r_sizeof
(paren
id|real_mode_switch
)paren
op_minus
l_int|100
)paren
comma
id|real_mode_switch
comma
r_sizeof
(paren
id|real_mode_switch
)paren
)paren
suffix:semicolon
id|memcpy
(paren
(paren
r_void
op_star
)paren
(paren
l_int|0x1000
op_minus
l_int|100
)paren
comma
id|code
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* Set up the IDT for real mode. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;lidt %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|real_mode_idt
)paren
)paren
suffix:semicolon
multiline_comment|/* Set up a GDT from which we can load segment descriptors for real&n;&t;   mode.  The GDT is not used in real mode; it is just needed here to&n;&t;   prepare the descriptors. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;lgdt %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|real_mode_gdt
)paren
)paren
suffix:semicolon
multiline_comment|/* Load the data segment registers, and thus the descriptors ready for&n;&t;   real mode.  The base address of each segment is 0x100, 16 times the&n;&t;   selector value being loaded here.  This is so that the segment&n;&t;   registers don&squot;t have to be reloaded after switching to real mode:&n;&t;   the values are consistent for real mode operation already. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;movl $0x0010,%%eax&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%ds&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%es&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%fs&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%gs&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%ss&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;eax&quot;
)paren
suffix:semicolon
multiline_comment|/* Jump to the 16-bit code that we copied earlier.  It disables paging&n;&t;   and the cache, switches to real mode, and jumps to the BIOS reset&n;&t;   entry point. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;ljmp $0x0008,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
(paren
r_void
op_star
)paren
(paren
l_int|0x1000
op_minus
r_sizeof
(paren
id|real_mode_switch
)paren
op_minus
l_int|100
)paren
)paren
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_SMP
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
id|boot_cpu_physical_apicid
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
id|mach_reboot
c_func
(paren
)paren
suffix:semicolon
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
id|machine_real_restart
c_func
(paren
id|jump_to_bios
comma
r_sizeof
(paren
id|jump_to_bios
)paren
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
eof
