multiline_comment|/*&n; *  linux/arch/i386/nmi.c&n; *&n; *  NMI watchdog support on APIC systems&n; *&n; *  Started by Ingo Molnar &lt;mingo@redhat.com&gt;&n; *&n; *  Fixes:&n; *  Mikael Pettersson&t;: AMD K7 support for local APIC NMI watchdog.&n; *  Mikael Pettersson&t;: Power Management for local APIC NMI watchdog.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;asm/mpspec.h&gt;
DECL|variable|nmi_watchdog
r_int
r_int
id|nmi_watchdog
op_assign
id|NMI_NONE
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
DECL|function|check_nmi_watchdog
r_int
id|__init
id|check_nmi_watchdog
(paren
r_void
)paren
(brace
id|irq_cpustat_t
id|tmp
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_int
id|j
comma
id|cpu
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;testing NMI watchdog ... &quot;
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|tmp
comma
id|irq_stat
comma
r_sizeof
(paren
id|tmp
)paren
)paren
suffix:semicolon
id|sti
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
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|smp_num_cpus
suffix:semicolon
id|j
op_increment
)paren
(brace
id|cpu
op_assign
id|cpu_logical_map
c_func
(paren
id|j
)paren
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
id|tmp
(braket
id|cpu
)braket
dot
id|__nmi_count
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
multiline_comment|/*&n;&t; * If any other x86 CPU has a local APIC, then&n;&t; * please test the NMI stuff there and send me the&n;&t; * missing bits. Right now Intel P6 and AMD K7 only.&n;&t; */
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
macro_line|#ifdef CONFIG_PM
macro_line|#include &lt;linux/pm.h&gt;
DECL|variable|nmi_pmdev
r_struct
id|pm_dev
op_star
id|nmi_pmdev
suffix:semicolon
DECL|function|disable_apic_nmi_watchdog
r_static
r_void
id|disable_apic_nmi_watchdog
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
)brace
DECL|function|nmi_pm_callback
r_static
r_int
id|nmi_pm_callback
c_func
(paren
r_struct
id|pm_dev
op_star
id|dev
comma
id|pm_request_t
id|rqst
comma
r_void
op_star
id|data
)paren
(brace
r_switch
c_cond
(paren
id|rqst
)paren
(brace
r_case
id|PM_SUSPEND
suffix:colon
id|disable_apic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_RESUME
suffix:colon
id|setup_apic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nmi_pm_init
r_static
r_void
id|nmi_pm_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|nmi_pmdev
)paren
id|nmi_pmdev
op_assign
id|apic_pm_register
c_func
(paren
id|PM_SYS_DEV
comma
l_int|0
comma
id|nmi_pm_callback
)paren
suffix:semicolon
)brace
DECL|macro|__pminit
mdefine_line|#define __pminit&t;/*empty*/
macro_line|#else&t;/* CONFIG_PM */
DECL|function|nmi_pm_init
r_static
r_inline
r_void
id|nmi_pm_init
c_func
(paren
r_void
)paren
(brace
)brace
DECL|macro|__pminit
mdefine_line|#define __pminit&t;__init
macro_line|#endif&t;/* CONFIG_PM */
multiline_comment|/*&n; * Activate the NMI watchdog via the local APIC.&n; * Original code written by Keith Owens.&n; */
DECL|function|setup_k7_watchdog
r_static
r_void
id|__pminit
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
id|wrmsr
c_func
(paren
id|MSR_K7_EVNTSEL0
op_plus
id|i
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_K7_PERFCTR0
op_plus
id|i
comma
l_int|0
comma
l_int|0
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
id|__pminit
id|setup_p6_watchdog
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
id|nmi_perfctr_msr
op_assign
id|MSR_IA32_PERFCTR0
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
l_int|2
suffix:semicolon
op_increment
id|i
)paren
(brace
id|wrmsr
c_func
(paren
id|MSR_IA32_EVNTSEL0
op_plus
id|i
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|wrmsr
c_func
(paren
id|MSR_IA32_PERFCTR0
op_plus
id|i
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
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
id|MSR_IA32_EVNTSEL0
comma
id|evntsel
comma
l_int|0
)paren
suffix:semicolon
id|Dprintk
c_func
(paren
l_string|&quot;setting IA32_PERFCTR0 to %08lx&bslash;n&quot;
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
id|MSR_IA32_PERFCTR0
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
id|MSR_IA32_EVNTSEL0
comma
id|evntsel
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|setup_apic_nmi_watchdog
r_void
id|__pminit
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
r_if
c_cond
(paren
id|boot_cpu_data.x86
op_ne
l_int|6
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
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|nmi_pm_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|nmi_print_lock
r_static
id|spinlock_t
id|nmi_print_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * the best way to detect whether a CPU has a &squot;hard lockup&squot; problem&n; * is to check it&squot;s local APIC timer IRQ counts. If they are not&n; * changing then that CPU has some problem.&n; *&n; * as these watchdog NMI IRQs are generated on every CPU, we only&n; * have to check the current processor.&n; *&n; * since NMIs dont listen to _any_ locks, we have to be extremely&n; * careful not to rely on unsafe variables. The printk might lock&n; * up though, so we have to break up any console locks first ...&n; * [when there will be more tty-related locks, break them up&n; *  here too!]&n; */
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
id|smp_num_cpus
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
)paren
(brace
multiline_comment|/*&n;&t; * Since current-&gt; is always on the stack, and we always switch&n;&t; * the stack NMI-atomically, it&squot;s safe to use smp_processor_id().&n;&t; */
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
id|apic_timer_irqs
(braket
id|cpu
)braket
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
l_string|&quot;NMI Watchdog detected LOCKUP on CPU%d, eip %08lx, registers:&bslash;n&quot;
comma
id|cpu
comma
id|regs-&gt;eip
)paren
suffix:semicolon
id|show_registers
c_func
(paren
id|regs
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
eof
