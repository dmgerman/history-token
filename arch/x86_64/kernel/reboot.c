multiline_comment|/* Various gunk just to reboot the machine. */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
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
l_int|3
)braket
suffix:semicolon
r_static
r_enum
(brace
DECL|enumerator|BOOT_BIOS
id|BOOT_BIOS
op_assign
l_char|&squot;b&squot;
comma
DECL|enumerator|BOOT_TRIPLE
id|BOOT_TRIPLE
op_assign
l_char|&squot;t&squot;
comma
DECL|enumerator|BOOT_KBD
id|BOOT_KBD
op_assign
l_char|&squot;k&squot;
DECL|variable|reboot_type
)brace
id|reboot_type
op_assign
id|BOOT_KBD
suffix:semicolon
DECL|variable|reboot_mode
r_static
r_int
id|reboot_mode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* reboot=b[ios] | t[riple] | k[bd] [, [w]arm | [c]old]&n;   bios&t;  Use the CPU reboot vector for warm reset&n;   warm   Don&squot;t set the cold reboot flag&n;   cold   Set the cold reboot flag&n;   triple Force a triple fault (init)&n;   kbd    Use the keyboard controller. cold reset (default)&n; */
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
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
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
id|reboot_mode
op_assign
l_int|0x1234
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
id|reboot_mode
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;t&squot;
suffix:colon
r_case
l_char|&squot;b&squot;
suffix:colon
r_case
l_char|&squot;k&squot;
suffix:colon
id|reboot_type
op_assign
op_star
id|str
suffix:semicolon
r_break
suffix:semicolon
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
multiline_comment|/* overwrites random kernel memory. Should not be kernel .text */
DECL|macro|WARMBOOT_TRAMP
mdefine_line|#define WARMBOOT_TRAMP 0x1000UL
DECL|function|reboot_warm
r_static
r_void
id|reboot_warm
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
r_char
id|warm_reboot
(braket
)braket
comma
id|warm_reboot_end
(braket
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;warm reboot&bslash;n&quot;
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* restore identity mapping */
id|init_level4_pgt
(braket
l_int|0
)braket
op_assign
id|__pgd
c_func
(paren
id|__pa
c_func
(paren
id|level3_ident_pgt
)paren
op_or
l_int|7
)paren
suffix:semicolon
id|__flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Move the trampoline to low memory */
id|memcpy
c_func
(paren
id|__va
c_func
(paren
id|WARMBOOT_TRAMP
)paren
comma
id|warm_reboot
comma
id|warm_reboot_end
op_minus
id|warm_reboot
)paren
suffix:semicolon
multiline_comment|/* Start it in compatibility mode. */
id|asm
r_volatile
(paren
l_string|&quot;   pushq $0&bslash;n&quot;
multiline_comment|/* ss */
l_string|&quot;   pushq $0x2000&bslash;n&quot;
multiline_comment|/* rsp */
l_string|&quot;   pushfq&bslash;n&quot;
multiline_comment|/* eflags */
l_string|&quot;   pushq %[cs]&bslash;n&quot;
l_string|&quot;   pushq %[target]&bslash;n&quot;
l_string|&quot;   iretq&quot;
op_scope_resolution
(braket
id|cs
)braket
l_string|&quot;i&quot;
(paren
id|__KERNEL_COMPAT32_CS
)paren
comma
(braket
id|target
)braket
l_string|&quot;b&quot;
(paren
id|WARMBOOT_TRAMP
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|smp_halt
r_static
r_void
id|smp_halt
c_func
(paren
r_void
)paren
(brace
r_int
id|cpuid
op_assign
id|safe_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_static
r_int
id|first_entry
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|first_entry
)paren
(brace
id|first_entry
op_assign
l_int|0
suffix:semicolon
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
id|smp_stop_cpu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* AP calling this. Just halt */
r_if
c_cond
(paren
id|cpuid
op_ne
id|boot_cpu_id
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
id|asm
c_func
(paren
l_string|&quot;hlt&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Wait for all other CPUs to have run smp_stop_cpu */
r_while
c_loop
(paren
op_logical_neg
id|cpus_empty
c_func
(paren
id|cpu_online_map
)paren
)paren
id|rep_nop
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
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
r_int
id|i
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_halt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|disable_local_APIC
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|disable_IO_APIC
c_func
(paren
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Tell the BIOS if we want cold or warm reboot */
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
multiline_comment|/* Could also try the reset bit in the Hammer NB */
r_switch
c_cond
(paren
id|reboot_type
)paren
(brace
r_case
id|BOOT_BIOS
suffix:colon
id|reboot_warm
c_func
(paren
)paren
suffix:semicolon
r_case
id|BOOT_KBD
suffix:colon
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
r_case
id|BOOT_TRIPLE
suffix:colon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lidt (%0)&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
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
id|reboot_type
op_assign
id|BOOT_KBD
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
)paren
suffix:semicolon
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
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
eof
