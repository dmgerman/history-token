multiline_comment|/*&n; *  linux/arch/i386/nmi.c&n; *&n; *  NMI watchdog support on APIC systems&n; *&n; *  Started by Ingo Molnar &lt;mingo@redhat.com&gt;&n; *&n; *  Fixes:&n; *  Mikael Pettersson&t;: AMD K7 support for local APIC NMI watchdog.&n; *  Mikael Pettersson&t;: Power Management for local APIC NMI watchdog.&n; *  Mikael Pettersson&t;: Pentium 4 support for local APIC NMI watchdog.&n; *  Pavel Machek and&n; *  Mikael Pettersson&t;: PM converted to driver model. Disable/enable API.&n; */
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
macro_line|#include &lt;linux/nmi.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
macro_line|#include &lt;asm/nmi.h&gt;
macro_line|#include &quot;mach_traps.h&quot;
DECL|variable|nmi_watchdog
r_int
r_int
id|nmi_watchdog
op_assign
id|NMI_NONE
suffix:semicolon
r_extern
r_int
id|unknown_nmi_panic
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
r_static
r_int
r_int
id|nmi_perfctr_msr
suffix:semicolon
multiline_comment|/* the MSR to reset in NMI handler */
DECL|variable|nmi_p4_cccr_val
r_static
r_int
r_int
id|nmi_p4_cccr_val
suffix:semicolon
r_extern
r_void
id|show_registers
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
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
DECL|macro|MSR_P4_MISC_ENABLE
mdefine_line|#define MSR_P4_MISC_ENABLE&t;0x1A0
DECL|macro|MSR_P4_MISC_ENABLE_PERF_AVAIL
mdefine_line|#define MSR_P4_MISC_ENABLE_PERF_AVAIL&t;(1&lt;&lt;7)
DECL|macro|MSR_P4_MISC_ENABLE_PEBS_UNAVAIL
mdefine_line|#define MSR_P4_MISC_ENABLE_PEBS_UNAVAIL&t;(1&lt;&lt;12)
DECL|macro|MSR_P4_PERFCTR0
mdefine_line|#define MSR_P4_PERFCTR0&t;&t;0x300
DECL|macro|MSR_P4_CCCR0
mdefine_line|#define MSR_P4_CCCR0&t;&t;0x360
DECL|macro|P4_ESCR_EVENT_SELECT
mdefine_line|#define P4_ESCR_EVENT_SELECT(N)&t;((N)&lt;&lt;25)
DECL|macro|P4_ESCR_OS
mdefine_line|#define P4_ESCR_OS&t;&t;(1&lt;&lt;3)
DECL|macro|P4_ESCR_USR
mdefine_line|#define P4_ESCR_USR&t;&t;(1&lt;&lt;2)
DECL|macro|P4_CCCR_OVF_PMI0
mdefine_line|#define P4_CCCR_OVF_PMI0&t;(1&lt;&lt;26)
DECL|macro|P4_CCCR_OVF_PMI1
mdefine_line|#define P4_CCCR_OVF_PMI1&t;(1&lt;&lt;27)
DECL|macro|P4_CCCR_THRESHOLD
mdefine_line|#define P4_CCCR_THRESHOLD(N)&t;((N)&lt;&lt;20)
DECL|macro|P4_CCCR_COMPLEMENT
mdefine_line|#define P4_CCCR_COMPLEMENT&t;(1&lt;&lt;19)
DECL|macro|P4_CCCR_COMPARE
mdefine_line|#define P4_CCCR_COMPARE&t;&t;(1&lt;&lt;18)
DECL|macro|P4_CCCR_REQUIRED
mdefine_line|#define P4_CCCR_REQUIRED&t;(3&lt;&lt;16)
DECL|macro|P4_CCCR_ESCR_SELECT
mdefine_line|#define P4_CCCR_ESCR_SELECT(N)&t;((N)&lt;&lt;13)
DECL|macro|P4_CCCR_ENABLE
mdefine_line|#define P4_CCCR_ENABLE&t;&t;(1&lt;&lt;12)
multiline_comment|/* Set up IQ_COUNTER0 to behave like a clock, by having IQ_CCCR0 filter&n;   CRU_ESCR0 (with any non-null event selector) through a complemented&n;   max threshold. [IA32-Vol3, Section 14.9.9] */
DECL|macro|MSR_P4_IQ_COUNTER0
mdefine_line|#define MSR_P4_IQ_COUNTER0&t;0x30C
DECL|macro|P4_NMI_CRU_ESCR0
mdefine_line|#define P4_NMI_CRU_ESCR0&t;(P4_ESCR_EVENT_SELECT(0x3F)|P4_ESCR_OS|P4_ESCR_USR)
DECL|macro|P4_NMI_IQ_CCCR0
mdefine_line|#define P4_NMI_IQ_CCCR0&t;&bslash;&n;&t;(P4_CCCR_OVF_PMI0|P4_CCCR_THRESHOLD(15)|P4_CCCR_COMPLEMENT|&t;&bslash;&n;&t; P4_CCCR_COMPARE|P4_CCCR_REQUIRED|P4_CCCR_ESCR_SELECT(4)|P4_CCCR_ENABLE)
DECL|function|check_nmi_watchdog
r_int
id|__init
id|check_nmi_watchdog
(paren
r_void
)paren
(brace
r_int
r_int
id|prev_nmi_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_int
id|cpu
suffix:semicolon
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
id|prev_nmi_count
(braket
id|cpu
)braket
op_assign
id|irq_stat
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
multiline_comment|/* FIXME: Only boot CPU is online at this stage.  Check CPUs&n;           as they come up. */
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
id|nmi_count
c_func
(paren
id|cpu
)paren
op_minus
id|prev_nmi_count
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
l_string|&quot;CPU#%d: NMI appears to be stuck!&bslash;n&quot;
comma
id|cpu
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
r_static
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
r_if
c_cond
(paren
id|nmi
op_eq
id|NMI_NONE
)paren
id|nmi_watchdog
op_assign
id|nmi
suffix:semicolon
multiline_comment|/*&n;&t; * If any other x86 CPU has a local APIC, then&n;&t; * please test the NMI stuff there and send me the&n;&t; * missing bits. Right now Intel P6/P4 and AMD K7 only.&n;&t; */
r_if
c_cond
(paren
(paren
id|nmi
op_eq
id|NMI_LOCAL_APIC
)paren
op_logical_and
(paren
id|boot_cpu_data.x86_vendor
op_eq
id|X86_VENDOR_INTEL
)paren
op_logical_and
(paren
id|boot_cpu_data.x86
op_eq
l_int|6
op_logical_or
id|boot_cpu_data.x86
op_eq
l_int|15
)paren
)paren
id|nmi_watchdog
op_assign
id|nmi
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nmi
op_eq
id|NMI_LOCAL_APIC
)paren
op_logical_and
(paren
id|boot_cpu_data.x86_vendor
op_eq
id|X86_VENDOR_AMD
)paren
op_logical_and
(paren
id|boot_cpu_data.x86
op_eq
l_int|6
op_logical_or
id|boot_cpu_data.x86
op_eq
l_int|15
)paren
)paren
id|nmi_watchdog
op_assign
id|nmi
suffix:semicolon
multiline_comment|/*&n;&t; * We can enable the IO-APIC watchdog&n;&t; * unconditionally.&n;&t; */
r_if
c_cond
(paren
id|nmi
op_eq
id|NMI_IO_APIC
)paren
(brace
id|nmi_active
op_assign
l_int|1
suffix:semicolon
id|nmi_watchdog
op_assign
id|nmi
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
id|boot_cpu_data.x86
)paren
(brace
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|boot_cpu_data.x86_model
OG
l_int|0xd
)paren
r_break
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P6_EVNTSEL0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
r_if
c_cond
(paren
id|boot_cpu_data.x86_model
OG
l_int|0x3
)paren
r_break
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_IQ_CCCR0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_CRU_ESCR0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
DECL|function|clear_msr_range
r_static
r_void
id|clear_msr_range
c_func
(paren
r_int
r_int
id|base
comma
r_int
r_int
id|n
)paren
(brace
r_int
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
id|n
suffix:semicolon
op_increment
id|i
)paren
(brace
id|wrmsr
c_func
(paren
id|base
op_plus
id|i
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
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
r_int
id|evntsel
suffix:semicolon
id|nmi_perfctr_msr
op_assign
id|MSR_K7_PERFCTR0
suffix:semicolon
id|clear_msr_range
c_func
(paren
id|MSR_K7_EVNTSEL0
comma
l_int|4
)paren
suffix:semicolon
id|clear_msr_range
c_func
(paren
id|MSR_K7_PERFCTR0
comma
l_int|4
)paren
suffix:semicolon
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
id|Dprintk
c_func
(paren
l_string|&quot;setting K7_PERFCTR0 to %08lx&bslash;n&quot;
comma
op_minus
(paren
id|cpu_khz
op_div
id|nmi_hz
op_star
l_int|1000
)paren
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K7_PERFCTR0
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
DECL|function|setup_p6_watchdog
r_static
r_void
id|setup_p6_watchdog
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|evntsel
suffix:semicolon
id|nmi_perfctr_msr
op_assign
id|MSR_P6_PERFCTR0
suffix:semicolon
id|clear_msr_range
c_func
(paren
id|MSR_P6_EVNTSEL0
comma
l_int|2
)paren
suffix:semicolon
id|clear_msr_range
c_func
(paren
id|MSR_P6_PERFCTR0
comma
l_int|2
)paren
suffix:semicolon
id|evntsel
op_assign
id|P6_EVNTSEL_INT
op_or
id|P6_EVNTSEL_OS
op_or
id|P6_EVNTSEL_USR
op_or
id|P6_NMI_EVENT
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P6_EVNTSEL0
comma
id|evntsel
comma
l_int|0
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;setting P6_PERFCTR0 to %08lx&bslash;n&quot;
comma
op_minus
(paren
id|cpu_khz
op_div
id|nmi_hz
op_star
l_int|1000
)paren
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P6_PERFCTR0
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
l_int|0
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
id|P6_EVNTSEL0_ENABLE
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P6_EVNTSEL0
comma
id|evntsel
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|setup_p4_watchdog
r_static
r_int
id|setup_p4_watchdog
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|misc_enable
comma
id|dummy
suffix:semicolon
id|rdmsr
c_func
(paren
id|MSR_P4_MISC_ENABLE
comma
id|misc_enable
comma
id|dummy
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|misc_enable
op_amp
id|MSR_P4_MISC_ENABLE_PERF_AVAIL
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|nmi_perfctr_msr
op_assign
id|MSR_P4_IQ_COUNTER0
suffix:semicolon
id|nmi_p4_cccr_val
op_assign
id|P4_NMI_IQ_CCCR0
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|smp_num_siblings
op_eq
l_int|2
)paren
id|nmi_p4_cccr_val
op_or_assign
id|P4_CCCR_OVF_PMI1
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|misc_enable
op_amp
id|MSR_P4_MISC_ENABLE_PEBS_UNAVAIL
)paren
)paren
id|clear_msr_range
c_func
(paren
l_int|0x3F1
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* MSR 0x3F0 seems to have a default value of 0xFC00, but current&n;&t;   docs doesn&squot;t fully define it, so leave it alone for now. */
id|clear_msr_range
c_func
(paren
l_int|0x3A0
comma
l_int|31
)paren
suffix:semicolon
id|clear_msr_range
c_func
(paren
l_int|0x3C0
comma
l_int|6
)paren
suffix:semicolon
id|clear_msr_range
c_func
(paren
l_int|0x3C8
comma
l_int|6
)paren
suffix:semicolon
id|clear_msr_range
c_func
(paren
l_int|0x3E0
comma
l_int|2
)paren
suffix:semicolon
id|clear_msr_range
c_func
(paren
id|MSR_P4_CCCR0
comma
l_int|18
)paren
suffix:semicolon
id|clear_msr_range
c_func
(paren
id|MSR_P4_PERFCTR0
comma
l_int|18
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_CRU_ESCR0
comma
id|P4_NMI_CRU_ESCR0
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_IQ_CCCR0
comma
id|P4_NMI_IQ_CCCR0
op_amp
op_complement
id|P4_CCCR_ENABLE
comma
l_int|0
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;setting P4_IQ_COUNTER0 to 0x%08lx&bslash;n&quot;
comma
op_minus
(paren
id|cpu_khz
op_div
id|nmi_hz
op_star
l_int|1000
)paren
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_IQ_COUNTER0
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
id|apic_write
c_func
(paren
id|APIC_LVTPC
comma
id|APIC_DM_NMI
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_P4_IQ_CCCR0
comma
id|nmi_p4_cccr_val
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|setup_apic_nmi_watchdog
r_void
id|setup_apic_nmi_watchdog
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
op_ne
l_int|6
op_logical_and
id|boot_cpu_data.x86
op_ne
l_int|15
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
r_case
id|X86_VENDOR_INTEL
suffix:colon
r_switch
c_cond
(paren
id|boot_cpu_data.x86
)paren
(brace
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
id|boot_cpu_data.x86_model
OG
l_int|0xd
)paren
r_return
suffix:semicolon
id|setup_p6_watchdog
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|15
suffix:colon
r_if
c_cond
(paren
id|boot_cpu_data.x86_model
OG
l_int|0x3
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|setup_p4_watchdog
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
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
r_extern
r_void
id|die_nmi
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_const
r_char
op_star
id|msg
)paren
suffix:semicolon
DECL|function|nmi_watchdog_tick
r_void
id|nmi_watchdog_tick
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/*&n;&t; * Since current_thread_info()-&gt; is always on the stack, and we&n;&t; * always switch the stack NMI-atomically, it&squot;s safe to use&n;&t; * smp_processor_id().&n;&t; */
r_int
id|sum
comma
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|sum
op_assign
id|irq_stat
(braket
id|cpu
)braket
dot
id|apic_timer_irqs
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
id|die_nmi
c_func
(paren
id|regs
comma
l_string|&quot;NMI Watchdog detected LOCKUP&quot;
)paren
suffix:semicolon
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
(brace
r_if
c_cond
(paren
id|nmi_perfctr_msr
op_eq
id|MSR_P4_IQ_COUNTER0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * P4 quirks:&n;&t;&t;&t; * - An overflown perfctr will assert its interrupt&n;&t;&t;&t; *   until the OVF flag in its CCCR is cleared.&n;&t;&t;&t; * - LVTPC is masked on interrupt and must be&n;&t;&t;&t; *   unmasked by the LVTPC handler.&n;&t;&t;&t; */
id|wrmsr
c_func
(paren
id|MSR_P4_IQ_CCCR0
comma
id|nmi_p4_cccr_val
comma
l_int|0
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
)brace
r_else
r_if
c_cond
(paren
id|nmi_perfctr_msr
op_eq
id|MSR_P6_PERFCTR0
)paren
(brace
multiline_comment|/* Only P6 based Pentium M need to re-unmask&n;&t;&t;&t; * the apic vector but it doesn&squot;t hurt&n;&t;&t;&t; * other P6 variant */
id|apic_write
c_func
(paren
id|APIC_LVTPC
comma
id|APIC_DM_NMI
)paren
suffix:semicolon
)brace
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
)brace
macro_line|#ifdef CONFIG_SYSCTL
DECL|function|unknown_nmi_panic_callback
r_static
r_int
id|unknown_nmi_panic_callback
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
r_int
r_char
id|reason
op_assign
id|get_nmi_reason
c_func
(paren
)paren
suffix:semicolon
r_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|reason
op_amp
l_int|0xc0
)paren
)paren
(brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;NMI received for unknown reason %02x&bslash;n&quot;
comma
id|reason
)paren
suffix:semicolon
id|die_nmi
c_func
(paren
id|regs
comma
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * proc handler for /proc/sys/kernel/unknown_nmi_panic&n; */
DECL|function|proc_unknown_nmi_panic
r_int
id|proc_unknown_nmi_panic
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|file
comma
r_void
id|__user
op_star
id|buffer
comma
r_int
op_star
id|length
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
id|old_state
suffix:semicolon
id|old_state
op_assign
id|unknown_nmi_panic
suffix:semicolon
id|proc_dointvec
c_func
(paren
id|table
comma
id|write
comma
id|file
comma
id|buffer
comma
id|length
comma
id|ppos
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_logical_neg
id|old_state
op_eq
op_logical_neg
op_logical_neg
id|unknown_nmi_panic
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|unknown_nmi_panic
)paren
(brace
r_if
c_cond
(paren
id|reserve_lapic_nmi
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|unknown_nmi_panic
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
(brace
id|set_nmi_callback
c_func
(paren
id|unknown_nmi_panic_callback
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|release_lapic_nmi
c_func
(paren
)paren
suffix:semicolon
id|unset_nmi_callback
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
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
eof
