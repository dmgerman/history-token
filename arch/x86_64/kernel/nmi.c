multiline_comment|/*&n; *  linux/arch/x86_64/nmi.c&n; *&n; *  NMI watchdog support on APIC systems&n; *&n; *  Started by Ingo Molnar &lt;mingo@redhat.com&gt;&n; *&n; *  Fixes:&n; *  Mikael Pettersson&t;: AMD K7 support for local APIC NMI watchdog.&n; *  Mikael Pettersson&t;: Power Management for local APIC NMI watchdog.&n; *  Pavel Machek and&n; *  Mikael Pettersson&t;: PM converted to driver model. Disable/enable API.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/nmi.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/nmi.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/proto.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
multiline_comment|/*&n; * lapic_nmi_owner tracks the ownership of the lapic NMI hardware:&n; * - it may be reserved by some other driver, or not&n; * - when not reserved by some other driver, it may be used for&n; *   the NMI watchdog, or not&n; *&n; * This is maintained separately from nmi_active because the NMI&n; * watchdog may also be driven from the I/O APIC timer.&n; */
DECL|variable|lapic_nmi_owner_lock
r_static
id|spinlock_t
id|lapic_nmi_owner_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|lapic_nmi_owner
r_static
r_int
r_int
id|lapic_nmi_owner
suffix:semicolon
DECL|macro|LAPIC_NMI_WATCHDOG
mdefine_line|#define LAPIC_NMI_WATCHDOG&t;(1&lt;&lt;0)
DECL|macro|LAPIC_NMI_RESERVED
mdefine_line|#define LAPIC_NMI_RESERVED&t;(1&lt;&lt;1)
multiline_comment|/* nmi_active:&n; * +1: the lapic NMI watchdog is active, but can be disabled&n; *  0: the lapic NMI watchdog has not been set up, and cannot&n; *     be enabled&n; * -1: the lapic NMI watchdog is disabled, but can be enabled&n; */
DECL|variable|nmi_active
r_int
id|nmi_active
suffix:semicolon
multiline_comment|/* oprofile uses this */
DECL|variable|panic_on_timeout
r_static
r_int
id|panic_on_timeout
suffix:semicolon
DECL|variable|nmi_watchdog
r_int
r_int
id|nmi_watchdog
op_assign
id|NMI_DEFAULT
suffix:semicolon
DECL|variable|nmi_hz
r_static
r_int
r_int
id|nmi_hz
op_assign
id|HZ
suffix:semicolon
DECL|variable|nmi_perfctr_msr
r_int
r_int
id|nmi_perfctr_msr
suffix:semicolon
multiline_comment|/* the MSR to reset in NMI handler */
multiline_comment|/* Note that these events don&squot;t tick when the CPU idles. This means&n;   the frequency varies with CPU load. */
DECL|macro|K7_EVNTSEL_ENABLE
mdefine_line|#define K7_EVNTSEL_ENABLE&t;(1 &lt;&lt; 22)
DECL|macro|K7_EVNTSEL_INT
mdefine_line|#define K7_EVNTSEL_INT&t;&t;(1 &lt;&lt; 20)
DECL|macro|K7_EVNTSEL_OS
mdefine_line|#define K7_EVNTSEL_OS&t;&t;(1 &lt;&lt; 17)
DECL|macro|K7_EVNTSEL_USR
mdefine_line|#define K7_EVNTSEL_USR&t;&t;(1 &lt;&lt; 16)
DECL|macro|K7_EVENT_CYCLES_PROCESSOR_IS_RUNNING
mdefine_line|#define K7_EVENT_CYCLES_PROCESSOR_IS_RUNNING&t;0x76
DECL|macro|K7_NMI_EVENT
mdefine_line|#define K7_NMI_EVENT&t;&t;K7_EVENT_CYCLES_PROCESSOR_IS_RUNNING
DECL|macro|P6_EVNTSEL0_ENABLE
mdefine_line|#define P6_EVNTSEL0_ENABLE&t;(1 &lt;&lt; 22)
DECL|macro|P6_EVNTSEL_INT
mdefine_line|#define P6_EVNTSEL_INT&t;&t;(1 &lt;&lt; 20)
DECL|macro|P6_EVNTSEL_OS
mdefine_line|#define P6_EVNTSEL_OS&t;&t;(1 &lt;&lt; 17)
DECL|macro|P6_EVNTSEL_USR
mdefine_line|#define P6_EVNTSEL_USR&t;&t;(1 &lt;&lt; 16)
DECL|macro|P6_EVENT_CPU_CLOCKS_NOT_HALTED
mdefine_line|#define P6_EVENT_CPU_CLOCKS_NOT_HALTED&t;0x79
DECL|macro|P6_NMI_EVENT
mdefine_line|#define P6_NMI_EVENT&t;&t;P6_EVENT_CPU_CLOCKS_NOT_HALTED
multiline_comment|/* Run after command line and cpu_init init, but before all other checks */
DECL|function|nmi_watchdog_default
r_void
id|__init
id|nmi_watchdog_default
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|nmi_watchdog
op_ne
id|NMI_DEFAULT
)paren
r_return
suffix:semicolon
multiline_comment|/* For some reason the IO APIC watchdog doesn&squot;t work on the AMD&n;&t;   8111 chipset. For now switch to local APIC mode using&n;&t;   perfctr0 there.  On Intel CPUs we don&squot;t have code to handle&n;&t;   the perfctr and the IO-APIC seems to work, so use that.  */
r_if
c_cond
(paren
id|boot_cpu_data.x86_vendor
op_eq
id|X86_VENDOR_AMD
)paren
(brace
id|nmi_watchdog
op_assign
id|NMI_LOCAL_APIC
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using local APIC NMI watchdog using perfctr0&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Using IO APIC NMI watchdog&bslash;n&quot;
)paren
suffix:semicolon
id|nmi_watchdog
op_assign
id|NMI_IO_APIC
suffix:semicolon
)brace
)brace
multiline_comment|/* Why is there no CPUID flag for this? */
DECL|function|cpu_has_lapic
r_static
id|__init
r_int
id|cpu_has_lapic
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|boot_cpu_data.x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_INTEL
suffix:colon
r_case
id|X86_VENDOR_AMD
suffix:colon
r_return
id|boot_cpu_data.x86
op_ge
l_int|6
suffix:semicolon
multiline_comment|/* .... add more cpus here or find a different way to figure this out. */
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|check_nmi_watchdog
r_int
id|__init
id|check_nmi_watchdog
(paren
r_void
)paren
(brace
r_int
id|counts
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_if
c_cond
(paren
id|nmi_watchdog
op_eq
id|NMI_LOCAL_APIC
op_logical_and
op_logical_neg
id|cpu_has_lapic
c_func
(paren
)paren
)paren
(brace
id|nmi_watchdog
op_assign
id|NMI_NONE
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;testing NMI watchdog ... &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
id|counts
(braket
id|cpu
)braket
op_assign
id|cpu_pda
(braket
id|cpu
)braket
dot
id|__nmi_count
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|mdelay
c_func
(paren
(paren
l_int|10
op_star
l_int|1000
)paren
op_div
id|nmi_hz
)paren
suffix:semicolon
singleline_comment|// wait 10 ticks
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|cpu_pda
(braket
id|cpu
)braket
dot
id|__nmi_count
op_minus
id|counts
(braket
id|cpu
)braket
op_le
l_int|5
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU#%d: NMI appears to be stuck (%d)!&bslash;n&quot;
comma
id|cpu
comma
id|cpu_pda
(braket
id|cpu
)braket
dot
id|__nmi_count
)paren
suffix:semicolon
id|nmi_active
op_assign
l_int|0
suffix:semicolon
id|lapic_nmi_owner
op_and_assign
op_complement
id|LAPIC_NMI_WATCHDOG
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;OK.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* now that we know it works we can reduce NMI frequency to&n;&t;   something more reasonable; makes a difference in some configs */
r_if
c_cond
(paren
id|nmi_watchdog
op_eq
id|NMI_LOCAL_APIC
)paren
id|nmi_hz
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|setup_nmi_watchdog
r_int
id|__init
id|setup_nmi_watchdog
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|nmi
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;panic&quot;
comma
l_int|5
)paren
)paren
(brace
id|panic_on_timeout
op_assign
l_int|1
suffix:semicolon
id|str
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
)paren
r_return
l_int|1
suffix:semicolon
op_increment
id|str
suffix:semicolon
)brace
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|nmi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nmi
op_ge
id|NMI_INVALID
)paren
r_return
l_int|0
suffix:semicolon
id|nmi_watchdog
op_assign
id|nmi
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nmi_watchdog=&quot;
comma
id|setup_nmi_watchdog
)paren
suffix:semicolon
DECL|function|disable_lapic_nmi_watchdog
r_static
r_void
id|disable_lapic_nmi_watchdog
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|nmi_active
op_le
l_int|0
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|boot_cpu_data.x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
id|wrmsr
c_func
(paren
id|MSR_K7_EVNTSEL0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|X86_VENDOR_INTEL
suffix:colon
id|wrmsr
c_func
(paren
id|MSR_IA32_EVNTSEL0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|nmi_active
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* tell do_nmi() and others that we&squot;re not active any more */
id|nmi_watchdog
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|enable_lapic_nmi_watchdog
r_static
r_void
id|enable_lapic_nmi_watchdog
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|nmi_active
OL
l_int|0
)paren
(brace
id|nmi_watchdog
op_assign
id|NMI_LOCAL_APIC
suffix:semicolon
id|setup_apic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|reserve_lapic_nmi
r_int
id|reserve_lapic_nmi
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|old_owner
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lapic_nmi_owner_lock
)paren
suffix:semicolon
id|old_owner
op_assign
id|lapic_nmi_owner
suffix:semicolon
id|lapic_nmi_owner
op_or_assign
id|LAPIC_NMI_RESERVED
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lapic_nmi_owner_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old_owner
op_amp
id|LAPIC_NMI_RESERVED
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|old_owner
op_amp
id|LAPIC_NMI_WATCHDOG
)paren
id|disable_lapic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|release_lapic_nmi
r_void
id|release_lapic_nmi
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|new_owner
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lapic_nmi_owner_lock
)paren
suffix:semicolon
id|new_owner
op_assign
id|lapic_nmi_owner
op_amp
op_complement
id|LAPIC_NMI_RESERVED
suffix:semicolon
id|lapic_nmi_owner
op_assign
id|new_owner
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lapic_nmi_owner_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_owner
op_amp
id|LAPIC_NMI_WATCHDOG
)paren
id|enable_lapic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|disable_timer_nmi_watchdog
r_void
id|disable_timer_nmi_watchdog
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
(paren
id|nmi_watchdog
op_ne
id|NMI_IO_APIC
)paren
op_logical_or
(paren
id|nmi_active
op_le
l_int|0
)paren
)paren
r_return
suffix:semicolon
id|disable_irq
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|unset_nmi_callback
c_func
(paren
)paren
suffix:semicolon
id|nmi_active
op_assign
op_minus
l_int|1
suffix:semicolon
id|nmi_watchdog
op_assign
id|NMI_NONE
suffix:semicolon
)brace
DECL|function|enable_timer_nmi_watchdog
r_void
id|enable_timer_nmi_watchdog
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|nmi_active
OL
l_int|0
)paren
(brace
id|nmi_watchdog
op_assign
id|NMI_IO_APIC
suffix:semicolon
id|touch_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
id|nmi_active
op_assign
l_int|1
suffix:semicolon
id|enable_irq
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_PM
DECL|variable|nmi_pm_active
r_static
r_int
id|nmi_pm_active
suffix:semicolon
multiline_comment|/* nmi_active before suspend */
DECL|function|lapic_nmi_suspend
r_static
r_int
id|lapic_nmi_suspend
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
comma
id|u32
id|state
)paren
(brace
id|nmi_pm_active
op_assign
id|nmi_active
suffix:semicolon
id|disable_lapic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lapic_nmi_resume
r_static
r_int
id|lapic_nmi_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|nmi_pm_active
OG
l_int|0
)paren
id|enable_lapic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nmi_sysclass
r_static
r_struct
id|sysdev_class
id|nmi_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;lapic_nmi&quot;
)paren
comma
dot
id|resume
op_assign
id|lapic_nmi_resume
comma
dot
id|suspend
op_assign
id|lapic_nmi_suspend
comma
)brace
suffix:semicolon
DECL|variable|device_lapic_nmi
r_static
r_struct
id|sys_device
id|device_lapic_nmi
op_assign
(brace
dot
id|id
op_assign
l_int|0
comma
dot
id|cls
op_assign
op_amp
id|nmi_sysclass
comma
)brace
suffix:semicolon
DECL|function|init_lapic_nmi_sysfs
r_static
r_int
id|__init
id|init_lapic_nmi_sysfs
c_func
(paren
r_void
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|nmi_active
op_eq
l_int|0
op_logical_or
id|nmi_watchdog
op_ne
id|NMI_LOCAL_APIC
)paren
r_return
l_int|0
suffix:semicolon
id|error
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|nmi_sysclass
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|sysdev_register
c_func
(paren
op_amp
id|device_lapic_nmi
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* must come after the local APIC&squot;s device_initcall() */
DECL|variable|init_lapic_nmi_sysfs
id|late_initcall
c_func
(paren
id|init_lapic_nmi_sysfs
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_PM */
multiline_comment|/*&n; * Activate the NMI watchdog via the local APIC.&n; * Original code written by Keith Owens.&n; */
DECL|function|setup_k7_watchdog
r_static
r_void
id|setup_k7_watchdog
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|evntsel
suffix:semicolon
multiline_comment|/* No check, so can start with slow frequency */
id|nmi_hz
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* XXX should check these in EFER */
id|nmi_perfctr_msr
op_assign
id|MSR_K7_PERFCTR0
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
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
multiline_comment|/* Simulator may not support it */
r_if
c_cond
(paren
id|checking_wrmsrl
c_func
(paren
id|MSR_K7_EVNTSEL0
op_plus
id|i
comma
l_int|0UL
)paren
)paren
r_return
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_K7_PERFCTR0
op_plus
id|i
comma
l_int|0UL
)paren
suffix:semicolon
)brace
id|evntsel
op_assign
id|K7_EVNTSEL_INT
op_or
id|K7_EVNTSEL_OS
op_or
id|K7_EVNTSEL_USR
op_or
id|K7_NMI_EVENT
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K7_EVNTSEL0
comma
id|evntsel
comma
l_int|0
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_K7_PERFCTR0
comma
op_minus
(paren
(paren
id|u64
)paren
id|cpu_khz
op_star
l_int|1000
)paren
op_div
id|nmi_hz
)paren
suffix:semicolon
id|apic_write
c_func
(paren
id|APIC_LVTPC
comma
id|APIC_DM_NMI
)paren
suffix:semicolon
id|evntsel
op_or_assign
id|K7_EVNTSEL_ENABLE
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K7_EVNTSEL0
comma
id|evntsel
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|setup_apic_nmi_watchdog
r_void
id|setup_apic_nmi_watchdog
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|boot_cpu_data.x86_vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
r_if
c_cond
(paren
id|boot_cpu_data.x86
OL
l_int|6
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|boot_cpu_data.x86_model_id
comma
l_string|&quot;Screwdriver&quot;
)paren
)paren
r_return
suffix:semicolon
id|setup_k7_watchdog
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|lapic_nmi_owner
op_assign
id|LAPIC_NMI_WATCHDOG
suffix:semicolon
id|nmi_active
op_assign
l_int|1
suffix:semicolon
)brace
DECL|variable|nmi_print_lock
r_static
id|spinlock_t
id|nmi_print_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * the best way to detect whether a CPU has a &squot;hard lockup&squot; problem&n; * is to check it&squot;s local APIC timer IRQ counts. If they are not&n; * changing then that CPU has some problem.&n; *&n; * as these watchdog NMI IRQs are generated on every CPU, we only&n; * have to check the current processor.&n; *&n; * since NMIs don&squot;t listen to _any_ locks, we have to be extremely&n; * careful not to rely on unsafe variables. The printk might lock&n; * up though, so we have to break up any console locks first ...&n; * [when there will be more tty-related locks, break them up&n; *  here too!]&n; */
r_static
r_int
r_int
DECL|variable|last_irq_sums
id|last_irq_sums
(braket
id|NR_CPUS
)braket
comma
DECL|variable|alert_counter
id|alert_counter
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|touch_nmi_watchdog
r_void
id|touch_nmi_watchdog
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * Just reset the alert counters, (other CPUs might be&n;&t; * spinning on locks we hold):&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
id|alert_counter
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|nmi_watchdog_tick
r_void
id|nmi_watchdog_tick
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|reason
)paren
(brace
r_int
id|sum
comma
id|cpu
suffix:semicolon
id|cpu
op_assign
id|safe_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|sum
op_assign
id|read_pda
c_func
(paren
id|apic_timer_irqs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|last_irq_sums
(braket
id|cpu
)braket
op_eq
id|sum
)paren
(brace
multiline_comment|/*&n;&t;&t; * Ayiee, looks like this CPU is stuck ...&n;&t;&t; * wait a few IRQs (5 seconds) before doing the oops ...&n;&t;&t; */
id|alert_counter
(braket
id|cpu
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|alert_counter
(braket
id|cpu
)braket
op_eq
l_int|5
op_star
id|nmi_hz
)paren
(brace
r_if
c_cond
(paren
id|notify_die
c_func
(paren
id|DIE_NMI
comma
l_string|&quot;nmi&quot;
comma
id|regs
comma
id|reason
comma
l_int|2
comma
id|SIGINT
)paren
op_eq
id|NOTIFY_BAD
)paren
(brace
id|alert_counter
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|nmi_print_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * We are in trouble anyway, lets at least try&n;&t;&t;&t; * to get a message out.&n;&t;&t;&t; */
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;NMI Watchdog detected LOCKUP on CPU%d, registers:&bslash;n&quot;
comma
id|cpu
)paren
suffix:semicolon
id|show_registers
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|panic_on_timeout
op_logical_or
id|panic_on_oops
)paren
id|panic
c_func
(paren
l_string|&quot;nmi watchdog&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;console shuts up ...&bslash;n&quot;
)paren
suffix:semicolon
id|console_silent
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|nmi_print_lock
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|last_irq_sums
(braket
id|cpu
)braket
op_assign
id|sum
suffix:semicolon
id|alert_counter
(braket
id|cpu
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nmi_perfctr_msr
)paren
id|wrmsr
c_func
(paren
id|nmi_perfctr_msr
comma
op_minus
(paren
id|cpu_khz
op_div
id|nmi_hz
op_star
l_int|1000
)paren
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|dummy_nmi_callback
r_static
r_int
id|dummy_nmi_callback
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|cpu
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nmi_callback
r_static
id|nmi_callback_t
id|nmi_callback
op_assign
id|dummy_nmi_callback
suffix:semicolon
DECL|function|do_nmi
id|asmlinkage
r_void
id|do_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|error_code
)paren
(brace
r_int
id|cpu
op_assign
id|safe_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|nmi_enter
c_func
(paren
)paren
suffix:semicolon
id|add_pda
c_func
(paren
id|__nmi_count
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nmi_callback
c_func
(paren
id|regs
comma
id|cpu
)paren
)paren
id|default_do_nmi
c_func
(paren
id|regs
)paren
suffix:semicolon
id|nmi_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|set_nmi_callback
r_void
id|set_nmi_callback
c_func
(paren
id|nmi_callback_t
id|callback
)paren
(brace
id|nmi_callback
op_assign
id|callback
suffix:semicolon
)brace
DECL|function|unset_nmi_callback
r_void
id|unset_nmi_callback
c_func
(paren
r_void
)paren
(brace
id|nmi_callback
op_assign
id|dummy_nmi_callback
suffix:semicolon
)brace
DECL|variable|nmi_active
id|EXPORT_SYMBOL
c_func
(paren
id|nmi_active
)paren
suffix:semicolon
DECL|variable|nmi_watchdog
id|EXPORT_SYMBOL
c_func
(paren
id|nmi_watchdog
)paren
suffix:semicolon
DECL|variable|reserve_lapic_nmi
id|EXPORT_SYMBOL
c_func
(paren
id|reserve_lapic_nmi
)paren
suffix:semicolon
DECL|variable|release_lapic_nmi
id|EXPORT_SYMBOL
c_func
(paren
id|release_lapic_nmi
)paren
suffix:semicolon
DECL|variable|disable_timer_nmi_watchdog
id|EXPORT_SYMBOL
c_func
(paren
id|disable_timer_nmi_watchdog
)paren
suffix:semicolon
DECL|variable|enable_timer_nmi_watchdog
id|EXPORT_SYMBOL
c_func
(paren
id|enable_timer_nmi_watchdog
)paren
suffix:semicolon
DECL|variable|touch_nmi_watchdog
id|EXPORT_SYMBOL
c_func
(paren
id|touch_nmi_watchdog
)paren
suffix:semicolon
eof
