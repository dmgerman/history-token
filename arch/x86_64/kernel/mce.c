multiline_comment|/*&n; * Machine check handler.&n; * K8 parts Copyright 2002,2003 Andi Kleen, SuSE Labs.&n; * Rest from unknown author(s). &n; * 2004 Andi Kleen. Rewrote most of it. &n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/rcupdate.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/processor.h&gt; 
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/mce.h&gt;
macro_line|#include &lt;asm/kdebug.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|MISC_MCELOG_MINOR
mdefine_line|#define MISC_MCELOG_MINOR 227
DECL|macro|NR_BANKS
mdefine_line|#define NR_BANKS 5
DECL|variable|__initdata
r_static
r_int
id|mce_disabled
id|__initdata
suffix:semicolon
multiline_comment|/* 0: always panic, 1: panic if deadlock possible, 2: try to avoid panic */
DECL|variable|tolerant
r_static
r_int
id|tolerant
op_assign
l_int|2
suffix:semicolon
DECL|variable|banks
r_static
r_int
id|banks
suffix:semicolon
DECL|variable|bank
r_static
r_int
r_int
id|bank
(braket
id|NR_BANKS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|NR_BANKS
op_minus
l_int|1
)braket
op_assign
op_complement
l_int|0UL
)brace
suffix:semicolon
multiline_comment|/*&n; * Lockless MCE logging infrastructure.&n; * This avoids deadlocks on printk locks without having to break locks. Also&n; * separate MCEs from kernel messages to avoid bogus bug reports.&n; */
DECL|variable|mcelog
r_struct
id|mce_log
id|mcelog
op_assign
(brace
id|MCE_LOG_SIGNATURE
comma
id|MCE_LOG_LEN
comma
)brace
suffix:semicolon
DECL|function|mce_log
r_static
r_void
id|mce_log
c_func
(paren
r_struct
id|mce
op_star
id|mce
)paren
(brace
r_int
id|next
comma
id|entry
suffix:semicolon
id|mce-&gt;finished
op_assign
l_int|0
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|entry
op_assign
id|mcelog.next
suffix:semicolon
id|read_barrier_depends
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* When the buffer fills up discard new entries. Assume &n;&t;&t;   that the earlier errors are the more interesting. */
r_if
c_cond
(paren
id|entry
op_ge
id|MCE_LOG_LEN
)paren
(brace
id|set_bit
c_func
(paren
id|MCE_OVERFLOW
comma
op_amp
id|mcelog.flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Old left over entry. Skip. */
r_if
c_cond
(paren
id|mcelog.entry
(braket
id|entry
)braket
dot
id|finished
)paren
r_continue
suffix:semicolon
id|smp_rmb
c_func
(paren
)paren
suffix:semicolon
id|next
op_assign
id|entry
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cmpxchg
c_func
(paren
op_amp
id|mcelog.next
comma
id|entry
comma
id|next
)paren
op_eq
id|entry
)paren
r_break
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|mcelog.entry
op_plus
id|entry
comma
id|mce
comma
r_sizeof
(paren
r_struct
id|mce
)paren
)paren
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
id|mcelog.entry
(braket
id|entry
)braket
dot
id|finished
op_assign
l_int|1
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|print_mce
r_static
r_void
id|print_mce
c_func
(paren
r_struct
id|mce
op_star
id|m
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU %d: Machine Check Exception: %16Lx Bank %d: %016Lx&bslash;n&quot;
comma
id|m-&gt;cpu
comma
id|m-&gt;mcgstatus
comma
id|m-&gt;bank
comma
id|m-&gt;status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;rip
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RIP%s %02x:&lt;%016Lx&gt; &quot;
comma
op_logical_neg
(paren
id|m-&gt;mcgstatus
op_amp
id|MCG_STATUS_EIPV
)paren
ques
c_cond
l_string|&quot; !INEXACT!&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|m-&gt;cs
comma
id|m-&gt;rip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;cs
op_eq
id|__KERNEL_CS
)paren
id|print_symbol
c_func
(paren
l_string|&quot;{%s}&quot;
comma
id|m-&gt;rip
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;TSC %Lx &quot;
comma
id|m-&gt;tsc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;addr
)paren
id|printk
c_func
(paren
l_string|&quot;ADDR %Lx &quot;
comma
id|m-&gt;addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m-&gt;misc
)paren
id|printk
c_func
(paren
l_string|&quot;MISC %Lx &quot;
comma
id|m-&gt;misc
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|mce_panic
r_static
r_void
id|mce_panic
c_func
(paren
r_char
op_star
id|msg
comma
r_struct
id|mce
op_star
id|backup
comma
r_int
r_int
id|start
)paren
(brace
r_int
id|i
suffix:semicolon
id|oops_begin
c_func
(paren
)paren
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
id|MCE_LOG_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mcelog.entry
(braket
id|i
)braket
dot
id|tsc
OL
id|start
)paren
r_continue
suffix:semicolon
id|print_mce
c_func
(paren
op_amp
id|mcelog.entry
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mcelog.entry
(braket
id|i
)braket
dot
id|tsc
op_eq
id|backup-&gt;tsc
)paren
id|backup
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|backup
)paren
id|print_mce
c_func
(paren
id|backup
)paren
suffix:semicolon
id|panic
c_func
(paren
id|msg
)paren
suffix:semicolon
)brace
DECL|function|mce_available
r_static
r_int
id|mce_available
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_return
op_logical_neg
id|mce_disabled
op_logical_and
id|test_bit
c_func
(paren
id|X86_FEATURE_MCE
comma
op_amp
id|c-&gt;x86_capability
)paren
op_logical_and
id|test_bit
c_func
(paren
id|X86_FEATURE_MCA
comma
op_amp
id|c-&gt;x86_capability
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * The actual machine check handler&n; */
DECL|function|do_machine_check
r_void
id|do_machine_check
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
r_struct
id|mce
id|m
suffix:semicolon
r_int
id|nowayout
op_assign
l_int|0
suffix:semicolon
r_int
id|kill_it
op_assign
l_int|0
suffix:semicolon
id|u64
id|mcestart
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|regs
)paren
id|notify_die
c_func
(paren
id|DIE_NMI
comma
l_string|&quot;machine check&quot;
comma
id|regs
comma
id|error_code
comma
l_int|255
comma
id|SIGKILL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|banks
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|m
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mce
)paren
)paren
suffix:semicolon
id|m.cpu
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
id|m.mcgstatus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|regs
op_logical_and
(paren
id|m.mcgstatus
op_amp
id|MCG_STATUS_MCIP
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|m.mcgstatus
op_amp
id|MCG_STATUS_RIPV
)paren
)paren
id|kill_it
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|regs
)paren
(brace
id|m.rip
op_assign
id|regs-&gt;rip
suffix:semicolon
id|m.cs
op_assign
id|regs-&gt;cs
suffix:semicolon
)brace
id|rdtscll
c_func
(paren
id|mcestart
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bank
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
id|m.status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|m.status
op_amp
id|MCI_STATUS_VAL
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|nowayout
op_or_assign
(paren
id|tolerant
OL
l_int|1
)paren
suffix:semicolon
id|nowayout
op_or_assign
op_logical_neg
op_logical_neg
(paren
id|m.status
op_amp
(paren
id|MCI_STATUS_OVER
op_or
id|MCI_STATUS_PCC
)paren
)paren
suffix:semicolon
id|kill_it
op_or_assign
op_logical_neg
op_logical_neg
(paren
id|m.status
op_amp
id|MCI_STATUS_UC
)paren
suffix:semicolon
id|m.bank
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|m.status
op_amp
id|MCI_STATUS_MISCV
)paren
id|rdmsrl
c_func
(paren
id|MSR_IA32_MC0_MISC
op_plus
id|i
op_star
l_int|4
comma
id|m.misc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|m.status
op_amp
id|MCI_STATUS_ADDRV
)paren
id|rdmsrl
c_func
(paren
id|MSR_IA32_MC0_ADDR
op_plus
id|i
op_star
l_int|4
comma
id|m.addr
)paren
suffix:semicolon
id|rdtscll
c_func
(paren
id|m.tsc
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|mce_log
c_func
(paren
op_amp
id|m
)paren
suffix:semicolon
)brace
id|wrmsrl
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Never do anything final in the polling timer */
r_if
c_cond
(paren
op_logical_neg
id|regs
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|nowayout
)paren
id|mce_panic
c_func
(paren
l_string|&quot;Machine check&quot;
comma
op_amp
id|m
comma
id|mcestart
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kill_it
)paren
(brace
r_int
id|user_space
op_assign
(paren
id|m.rip
op_logical_and
(paren
id|m.cs
op_amp
l_int|3
)paren
)paren
suffix:semicolon
multiline_comment|/* When the machine was in user space and the CPU didn&squot;t get&n;&t;&t;   confused it&squot;s normally not necessary to panic, unless you are &n;&t;&t;   paranoid (tolerant == 0) */
r_if
c_cond
(paren
op_logical_neg
id|user_space
op_logical_and
(paren
id|panic_on_oops
op_logical_or
id|tolerant
OL
l_int|2
)paren
)paren
id|mce_panic
c_func
(paren
l_string|&quot;Uncorrected machine check&quot;
comma
op_amp
id|m
comma
id|mcestart
)paren
suffix:semicolon
multiline_comment|/* do_exit takes an awful lot of locks and has as slight risk &n;&t;&t;   of deadlocking. If you don&squot;t want that don&squot;t set tolerant &gt;= 2 */
id|do_exit
c_func
(paren
id|SIGBUS
)paren
suffix:semicolon
)brace
)brace
DECL|function|mce_clear_all
r_static
r_void
id|mce_clear_all
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
id|wrmsrl
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
id|i
op_star
l_int|4
comma
l_int|0
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_IA32_MCG_STATUS
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Periodic polling timer for &quot;silent&quot; machine check errors.&n; */
DECL|variable|check_interval
r_static
r_int
id|check_interval
op_assign
l_int|3600
suffix:semicolon
multiline_comment|/* one hour */
r_static
r_void
id|mcheck_timer
c_func
(paren
r_void
op_star
id|data
)paren
suffix:semicolon
r_static
id|DECLARE_WORK
c_func
(paren
id|mcheck_work
comma
id|mcheck_timer
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|mcheck_check_cpu
r_static
r_void
id|mcheck_check_cpu
c_func
(paren
r_void
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|mce_available
c_func
(paren
op_amp
id|current_cpu_data
)paren
)paren
id|do_machine_check
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|mcheck_timer
r_static
r_void
id|mcheck_timer
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|on_each_cpu
c_func
(paren
id|mcheck_check_cpu
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|schedule_delayed_work
c_func
(paren
op_amp
id|mcheck_work
comma
id|check_interval
op_star
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|periodic_mcheck_init
r_static
id|__init
r_int
id|periodic_mcheck_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|check_interval
)paren
id|schedule_delayed_work
c_func
(paren
op_amp
id|mcheck_work
comma
id|check_interval
op_star
id|HZ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|periodic_mcheck_init
id|__initcall
c_func
(paren
id|periodic_mcheck_init
)paren
suffix:semicolon
multiline_comment|/* &n; * Initialize Machine Checks for a CPU.&n; */
DECL|function|mce_init
r_static
r_void
id|mce_init
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
id|u64
id|cap
suffix:semicolon
r_int
id|i
suffix:semicolon
id|rdmsrl
c_func
(paren
id|MSR_IA32_MCG_CAP
comma
id|cap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cap
op_amp
id|MCG_CTL_P
)paren
id|wrmsr
c_func
(paren
id|MSR_IA32_MCG_CTL
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
suffix:semicolon
id|banks
op_assign
id|cap
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|banks
OG
id|NR_BANKS
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;MCE: warning: using only %d banks&bslash;n&quot;
comma
id|banks
)paren
suffix:semicolon
id|banks
op_assign
id|NR_BANKS
suffix:semicolon
)brace
id|mce_clear_all
c_func
(paren
)paren
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
id|banks
suffix:semicolon
id|i
op_increment
)paren
(brace
id|wrmsrl
c_func
(paren
id|MSR_IA32_MC0_CTL
op_plus
l_int|4
op_star
id|i
comma
id|bank
(braket
id|i
)braket
)paren
suffix:semicolon
id|wrmsrl
c_func
(paren
id|MSR_IA32_MC0_STATUS
op_plus
l_int|4
op_star
id|i
comma
l_int|0
)paren
suffix:semicolon
)brace
id|set_in_cr4
c_func
(paren
id|X86_CR4_MCE
)paren
suffix:semicolon
)brace
multiline_comment|/* Add per CPU specific workarounds here */
DECL|function|mce_cpu_quirks
r_static
r_void
id|__init
id|mce_cpu_quirks
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
multiline_comment|/* This should be disabled by the BIOS, but isn&squot;t always */
r_if
c_cond
(paren
id|c-&gt;x86_vendor
op_eq
id|X86_VENDOR_AMD
op_logical_and
id|c-&gt;x86
op_eq
l_int|15
)paren
(brace
multiline_comment|/* disable GART TBL walk error reporting, which trips off &n;&t;&t;   incorrectly with the IOMMU &amp; 3ware &amp; Cerberus. */
id|clear_bit
c_func
(paren
l_int|10
comma
op_amp
id|bank
(braket
l_int|4
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* &n; * Called for each booted CPU to set up machine checks.&n; * Must be called with preempt off. &n; */
DECL|function|mcheck_init
r_void
id|__init
id|mcheck_init
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
id|c
)paren
(brace
r_static
r_int
r_int
id|mce_cpus
id|__initdata
op_assign
l_int|0
suffix:semicolon
id|mce_cpu_quirks
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
op_amp
id|mce_cpus
)paren
op_logical_or
op_logical_neg
id|mce_available
c_func
(paren
id|c
)paren
)paren
r_return
suffix:semicolon
id|mce_init
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Character device to read and clear the MCE log.&n; */
DECL|function|collect_tscs
r_static
r_void
id|collect_tscs
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_int
r_int
op_star
id|cpu_tsc
op_assign
(paren
r_int
r_int
op_star
)paren
id|data
suffix:semicolon
id|rdtscll
c_func
(paren
id|cpu_tsc
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
)paren
suffix:semicolon
)brace
DECL|function|mce_read
r_static
id|ssize_t
id|mce_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|ubuf
comma
r_int
id|usize
comma
id|loff_t
op_star
id|off
)paren
(brace
r_int
r_int
id|cpu_tsc
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|mce_read_sem
)paren
suffix:semicolon
r_int
id|next
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|ubuf
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mce_read_sem
)paren
suffix:semicolon
id|next
op_assign
id|mcelog.next
suffix:semicolon
id|read_barrier_depends
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Only supports full reads right now */
r_if
c_cond
(paren
op_star
id|off
op_ne
l_int|0
op_logical_or
id|usize
OL
id|MCE_LOG_LEN
op_star
r_sizeof
(paren
r_struct
id|mce
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|mce_read_sem
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|err
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
id|next
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mcelog.entry
(braket
id|i
)braket
dot
id|finished
)paren
r_continue
suffix:semicolon
id|smp_rmb
c_func
(paren
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|mcelog.entry
op_plus
id|i
comma
r_sizeof
(paren
r_struct
id|mce
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
r_sizeof
(paren
r_struct
id|mce
)paren
suffix:semicolon
)brace
id|memset
c_func
(paren
id|mcelog.entry
comma
l_int|0
comma
id|next
op_star
r_sizeof
(paren
r_struct
id|mce
)paren
)paren
suffix:semicolon
id|mcelog.next
op_assign
l_int|0
suffix:semicolon
id|smp_wmb
c_func
(paren
)paren
suffix:semicolon
id|synchronize_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Collect entries that were still getting written before the synchronize. */
id|on_each_cpu
c_func
(paren
id|collect_tscs
comma
id|cpu_tsc
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|next
suffix:semicolon
id|i
OL
id|MCE_LOG_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mcelog.entry
(braket
id|i
)braket
dot
id|finished
op_logical_and
id|mcelog.entry
(braket
id|i
)braket
dot
id|tsc
OL
id|cpu_tsc
(braket
id|mcelog.entry
(braket
id|i
)braket
dot
id|cpu
)braket
)paren
(brace
id|err
op_or_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|mcelog.entry
op_plus
id|i
comma
r_sizeof
(paren
r_struct
id|mce
)paren
)paren
suffix:semicolon
id|smp_rmb
c_func
(paren
)paren
suffix:semicolon
id|buf
op_add_assign
r_sizeof
(paren
r_struct
id|mce
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mcelog.entry
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mce
)paren
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|mce_read_sem
)paren
suffix:semicolon
r_return
id|err
ques
c_cond
op_minus
id|EFAULT
suffix:colon
id|buf
op_minus
id|ubuf
suffix:semicolon
)brace
DECL|function|mce_ioctl
r_static
r_int
id|mce_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_struct
id|file
op_star
id|f
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|MCE_GET_RECORD_LEN
suffix:colon
r_return
id|put_user
c_func
(paren
r_sizeof
(paren
r_struct
id|mce
)paren
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|MCE_GET_LOG_LEN
suffix:colon
r_return
id|put_user
c_func
(paren
id|MCE_LOG_LEN
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|MCE_GETCLEAR_FLAGS
suffix:colon
(brace
r_int
id|flags
suffix:semicolon
r_do
(brace
id|flags
op_assign
id|mcelog.flags
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cmpxchg
c_func
(paren
op_amp
id|mcelog.flags
comma
id|flags
comma
l_int|0
)paren
op_ne
id|flags
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|flags
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
)brace
DECL|variable|mce_chrdev_ops
r_static
r_struct
id|file_operations
id|mce_chrdev_ops
op_assign
(brace
dot
id|read
op_assign
id|mce_read
comma
dot
id|ioctl
op_assign
id|mce_ioctl
comma
)brace
suffix:semicolon
DECL|variable|mce_log_device
r_static
r_struct
id|miscdevice
id|mce_log_device
op_assign
(brace
id|MISC_MCELOG_MINOR
comma
l_string|&quot;mcelog&quot;
comma
op_amp
id|mce_chrdev_ops
comma
)brace
suffix:semicolon
multiline_comment|/* &n; * Old style boot options parsing. Only for compatibility. &n; */
DECL|function|mcheck_disable
r_static
r_int
id|__init
id|mcheck_disable
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|mce_disabled
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* mce=off disable machine check */
DECL|function|mcheck_enable
r_static
r_int
id|__init
id|mcheck_enable
c_func
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
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
)paren
)paren
id|mce_disabled
op_assign
l_int|1
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;mce= argument %s ignored. Please use /sys&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;nomce&quot;
comma
id|mcheck_disable
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;mce&quot;
comma
id|mcheck_enable
)paren
suffix:semicolon
multiline_comment|/* &n; * Sysfs support&n; */
multiline_comment|/* On resume clear all MCE state. Don&squot;t want to see leftovers from the BIOS. */
DECL|function|mce_resume
r_static
r_int
id|mce_resume
c_func
(paren
r_struct
id|sys_device
op_star
id|dev
)paren
(brace
id|mce_clear_all
c_func
(paren
)paren
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|mce_init
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
multiline_comment|/* Reinit MCEs after user configuration changes */
DECL|function|mce_restart
r_static
r_void
id|mce_restart
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|check_interval
)paren
id|cancel_delayed_work
c_func
(paren
op_amp
id|mcheck_work
)paren
suffix:semicolon
multiline_comment|/* Timer race is harmless here */
id|on_each_cpu
c_func
(paren
id|mce_init
comma
l_int|NULL
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check_interval
)paren
id|schedule_delayed_work
c_func
(paren
op_amp
id|mcheck_work
comma
id|check_interval
op_star
id|HZ
)paren
suffix:semicolon
)brace
DECL|variable|mce_sysclass
r_static
r_struct
id|sysdev_class
id|mce_sysclass
op_assign
(brace
dot
id|resume
op_assign
id|mce_resume
comma
id|set_kset_name
c_func
(paren
l_string|&quot;machinecheck&quot;
)paren
comma
)brace
suffix:semicolon
DECL|variable|device_mce
r_static
r_struct
id|sys_device
id|device_mce
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
id|mce_sysclass
comma
)brace
suffix:semicolon
multiline_comment|/* Why are there no generic functions for this? */
DECL|macro|ACCESSOR
mdefine_line|#define ACCESSOR(name, var, start) &bslash;&n;&t;static ssize_t show_ ## name(struct sys_device *s, char *buf) { &t;   &t;   &bslash;&n;&t;&t;return sprintf(buf, &quot;%lu&bslash;n&quot;, (unsigned long)var);&t;&t;   &bslash;&n;&t;} &t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;static ssize_t set_ ## name(struct sys_device *s,const char *buf,size_t siz) { &bslash;&n;&t;&t;char *end; &t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;unsigned long new = simple_strtoul(buf, &amp;end, 0); &t;&t;   &bslash;&n;&t;&t;if (end == buf) return -EINVAL;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;var = new;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;start; &t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;return end-buf;&t;&t;     &t;&t;&t;&t;&t;   &bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;static SYSDEV_ATTR(name, 0644, show_ ## name, set_ ## name);
id|ACCESSOR
c_func
(paren
id|bank0ctl
comma
id|bank
(braket
l_int|0
)braket
comma
id|mce_restart
c_func
(paren
)paren
)paren
id|ACCESSOR
c_func
(paren
id|bank1ctl
comma
id|bank
(braket
l_int|1
)braket
comma
id|mce_restart
c_func
(paren
)paren
)paren
id|ACCESSOR
c_func
(paren
id|bank2ctl
comma
id|bank
(braket
l_int|2
)braket
comma
id|mce_restart
c_func
(paren
)paren
)paren
id|ACCESSOR
c_func
(paren
id|bank3ctl
comma
id|bank
(braket
l_int|3
)braket
comma
id|mce_restart
c_func
(paren
)paren
)paren
id|ACCESSOR
c_func
(paren
id|bank4ctl
comma
id|bank
(braket
l_int|4
)braket
comma
id|mce_restart
c_func
(paren
)paren
)paren
id|ACCESSOR
c_func
(paren
id|tolerant
comma
id|tolerant
comma
)paren
id|ACCESSOR
c_func
(paren
id|check_interval
comma
id|check_interval
comma
id|mce_restart
c_func
(paren
)paren
)paren
DECL|function|mce_init_device
r_static
id|__init
r_int
id|mce_init_device
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mce_available
c_func
(paren
op_amp
id|boot_cpu_data
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|err
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|mce_sysclass
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|err
op_assign
id|sysdev_register
c_func
(paren
op_amp
id|device_mce
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
multiline_comment|/* could create per CPU objects, but is not worth it. */
id|sysdev_create_file
c_func
(paren
op_amp
id|device_mce
comma
op_amp
id|attr_bank0ctl
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|device_mce
comma
op_amp
id|attr_bank1ctl
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|device_mce
comma
op_amp
id|attr_bank2ctl
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|device_mce
comma
op_amp
id|attr_bank3ctl
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|device_mce
comma
op_amp
id|attr_bank4ctl
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|device_mce
comma
op_amp
id|attr_tolerant
)paren
suffix:semicolon
id|sysdev_create_file
c_func
(paren
op_amp
id|device_mce
comma
op_amp
id|attr_check_interval
)paren
suffix:semicolon
)brace
id|misc_register
c_func
(paren
op_amp
id|mce_log_device
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|mce_init_device
id|device_initcall
c_func
(paren
id|mce_init_device
)paren
suffix:semicolon
eof
