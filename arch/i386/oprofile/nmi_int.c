multiline_comment|/**&n; * @file nmi_int.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;asm/nmi.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/apic.h&gt;
macro_line|#include &quot;op_counter.h&quot;
macro_line|#include &quot;op_x86_model.h&quot;
DECL|variable|model
r_static
r_struct
id|op_x86_model_spec
r_const
op_star
id|model
suffix:semicolon
DECL|variable|cpu_msrs
r_static
r_struct
id|op_msrs
id|cpu_msrs
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|saved_lvtpc
r_static
r_int
r_int
id|saved_lvtpc
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_static
r_int
id|nmi_start
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|nmi_stop
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|oprofile_pmdev
r_static
r_struct
id|pm_dev
op_star
id|oprofile_pmdev
suffix:semicolon
multiline_comment|/* We&squot;re at risk of causing big trouble unless we&n; * make sure to not cause any NMI interrupts when&n; * suspended.&n; */
DECL|function|oprofile_pm_callback
r_static
r_int
id|oprofile_pm_callback
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
id|nmi_stop
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PM_RESUME
suffix:colon
id|nmi_start
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
DECL|function|nmi_callback
r_static
r_int
id|nmi_callback
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
id|model
op_member_access_from_pointer
id|check_ctrs
c_func
(paren
id|cpu
comma
op_amp
id|cpu_msrs
(braket
id|cpu
)braket
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|nmi_save_registers
r_static
r_void
id|nmi_save_registers
c_func
(paren
r_struct
id|op_msrs
op_star
id|msrs
)paren
(brace
r_int
r_int
r_const
id|nr_ctrs
op_assign
id|model-&gt;num_counters
suffix:semicolon
r_int
r_int
r_const
id|nr_ctrls
op_assign
id|model-&gt;num_controls
suffix:semicolon
r_struct
id|op_msr_group
op_star
id|counters
op_assign
op_amp
id|msrs-&gt;counters
suffix:semicolon
r_struct
id|op_msr_group
op_star
id|controls
op_assign
op_amp
id|msrs-&gt;controls
suffix:semicolon
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
id|nr_ctrs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|rdmsr
c_func
(paren
id|counters-&gt;addrs
(braket
id|i
)braket
comma
id|counters-&gt;saved
(braket
id|i
)braket
dot
id|low
comma
id|counters-&gt;saved
(braket
id|i
)braket
dot
id|high
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_ctrls
suffix:semicolon
op_increment
id|i
)paren
(brace
id|rdmsr
c_func
(paren
id|controls-&gt;addrs
(braket
id|i
)braket
comma
id|controls-&gt;saved
(braket
id|i
)braket
dot
id|low
comma
id|controls-&gt;saved
(braket
id|i
)braket
dot
id|high
)paren
suffix:semicolon
)brace
)brace
DECL|function|nmi_cpu_setup
r_static
r_void
id|nmi_cpu_setup
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|op_msrs
op_star
id|msrs
op_assign
op_amp
id|cpu_msrs
(braket
id|cpu
)braket
suffix:semicolon
id|model
op_member_access_from_pointer
id|fill_in_addresses
c_func
(paren
id|msrs
)paren
suffix:semicolon
id|nmi_save_registers
c_func
(paren
id|msrs
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
id|model
op_member_access_from_pointer
id|setup_ctrs
c_func
(paren
id|msrs
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|oprofilefs_lock
)paren
suffix:semicolon
id|saved_lvtpc
(braket
id|cpu
)braket
op_assign
id|apic_read
c_func
(paren
id|APIC_LVTPC
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
DECL|function|nmi_setup
r_static
r_int
id|nmi_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We walk a thin line between law and rape here.&n;&t; * We need to be careful to install our NMI handler&n;&t; * without actually triggering any NMIs as this will&n;&t; * break the core code horrifically.&n;&t; */
id|smp_call_function
c_func
(paren
id|nmi_cpu_setup
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|nmi_cpu_setup
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|set_nmi_callback
c_func
(paren
id|nmi_callback
)paren
suffix:semicolon
id|oprofile_pmdev
op_assign
id|set_nmi_pm_callback
c_func
(paren
id|oprofile_pm_callback
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nmi_restore_registers
r_static
r_void
id|nmi_restore_registers
c_func
(paren
r_struct
id|op_msrs
op_star
id|msrs
)paren
(brace
r_int
r_int
r_const
id|nr_ctrs
op_assign
id|model-&gt;num_counters
suffix:semicolon
r_int
r_int
r_const
id|nr_ctrls
op_assign
id|model-&gt;num_controls
suffix:semicolon
r_struct
id|op_msr_group
op_star
id|counters
op_assign
op_amp
id|msrs-&gt;counters
suffix:semicolon
r_struct
id|op_msr_group
op_star
id|controls
op_assign
op_amp
id|msrs-&gt;controls
suffix:semicolon
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
id|nr_ctrls
suffix:semicolon
op_increment
id|i
)paren
(brace
id|wrmsr
c_func
(paren
id|controls-&gt;addrs
(braket
id|i
)braket
comma
id|controls-&gt;saved
(braket
id|i
)braket
dot
id|low
comma
id|controls-&gt;saved
(braket
id|i
)braket
dot
id|high
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nr_ctrs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|wrmsr
c_func
(paren
id|counters-&gt;addrs
(braket
id|i
)braket
comma
id|counters-&gt;saved
(braket
id|i
)braket
dot
id|low
comma
id|counters-&gt;saved
(braket
id|i
)braket
dot
id|high
)paren
suffix:semicolon
)brace
)brace
DECL|function|nmi_cpu_shutdown
r_static
r_void
id|nmi_cpu_shutdown
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_int
r_int
id|v
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_struct
id|op_msrs
op_star
id|msrs
op_assign
op_amp
id|cpu_msrs
(braket
id|cpu
)braket
suffix:semicolon
multiline_comment|/* restoring APIC_LVTPC can trigger an apic error because the delivery&n;&t; * mode and vector nr combination can be illegal. That&squot;s by design: on&n;&t; * power on apic lvt contain a zero vector nr which are legal only for&n;&t; * NMI delivery mode. So inhibit apic err before restoring lvtpc&n;&t; */
id|v
op_assign
id|apic_read
c_func
(paren
id|APIC_LVTERR
)paren
suffix:semicolon
id|apic_write
c_func
(paren
id|APIC_LVTERR
comma
id|v
op_or
id|APIC_LVT_MASKED
)paren
suffix:semicolon
id|apic_write
c_func
(paren
id|APIC_LVTPC
comma
id|saved_lvtpc
(braket
id|cpu
)braket
)paren
suffix:semicolon
id|apic_write
c_func
(paren
id|APIC_LVTERR
comma
id|v
)paren
suffix:semicolon
id|nmi_restore_registers
c_func
(paren
id|msrs
)paren
suffix:semicolon
)brace
DECL|function|nmi_shutdown
r_static
r_void
id|nmi_shutdown
c_func
(paren
r_void
)paren
(brace
id|unset_nmi_pm_callback
c_func
(paren
id|oprofile_pmdev
)paren
suffix:semicolon
id|unset_nmi_callback
c_func
(paren
)paren
suffix:semicolon
id|smp_call_function
c_func
(paren
id|nmi_cpu_shutdown
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|nmi_cpu_shutdown
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|nmi_cpu_start
r_static
r_void
id|nmi_cpu_start
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_struct
id|op_msrs
r_const
op_star
id|msrs
op_assign
op_amp
id|cpu_msrs
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
id|model
op_member_access_from_pointer
id|start
c_func
(paren
id|msrs
)paren
suffix:semicolon
)brace
DECL|function|nmi_start
r_static
r_int
id|nmi_start
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|nmi_cpu_start
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|nmi_cpu_start
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nmi_cpu_stop
r_static
r_void
id|nmi_cpu_stop
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
r_struct
id|op_msrs
r_const
op_star
id|msrs
op_assign
op_amp
id|cpu_msrs
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
id|model
op_member_access_from_pointer
id|stop
c_func
(paren
id|msrs
)paren
suffix:semicolon
)brace
DECL|function|nmi_stop
r_static
r_void
id|nmi_stop
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|nmi_cpu_stop
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|nmi_cpu_stop
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|counter_config
r_struct
id|op_counter_config
id|counter_config
(braket
id|OP_MAX_COUNTER
)braket
suffix:semicolon
DECL|function|nmi_create_files
r_static
r_int
id|nmi_create_files
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|dentry
op_star
id|root
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
id|model-&gt;num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
r_struct
id|dentry
op_star
id|dir
suffix:semicolon
r_char
id|buf
(braket
l_int|2
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
l_int|2
comma
l_string|&quot;%d&quot;
comma
id|i
)paren
suffix:semicolon
id|dir
op_assign
id|oprofilefs_mkdir
c_func
(paren
id|sb
comma
id|root
comma
id|buf
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;enabled&quot;
comma
op_amp
id|counter_config
(braket
id|i
)braket
dot
id|enabled
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;event&quot;
comma
op_amp
id|counter_config
(braket
id|i
)braket
dot
id|event
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;count&quot;
comma
op_amp
id|counter_config
(braket
id|i
)braket
dot
id|count
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;unit_mask&quot;
comma
op_amp
id|counter_config
(braket
id|i
)braket
dot
id|unit_mask
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;kernel&quot;
comma
op_amp
id|counter_config
(braket
id|i
)braket
dot
id|kernel
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|dir
comma
l_string|&quot;user&quot;
comma
op_amp
id|counter_config
(braket
id|i
)braket
dot
id|user
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|nmi_ops
r_struct
id|oprofile_operations
id|nmi_ops
op_assign
(brace
dot
id|create_files
op_assign
id|nmi_create_files
comma
dot
id|setup
op_assign
id|nmi_setup
comma
dot
id|shutdown
op_assign
id|nmi_shutdown
comma
dot
id|start
op_assign
id|nmi_start
comma
dot
id|stop
op_assign
id|nmi_stop
)brace
suffix:semicolon
macro_line|#if !defined(CONFIG_X86_64)
DECL|function|p4_init
r_static
r_int
id|__init
id|p4_init
c_func
(paren
r_enum
id|oprofile_cpu
op_star
id|cpu
)paren
(brace
id|__u8
id|cpu_model
op_assign
id|current_cpu_data.x86_model
suffix:semicolon
r_if
c_cond
(paren
id|cpu_model
OG
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
op_star
id|cpu
op_assign
id|OPROFILE_CPU_P4
suffix:semicolon
id|model
op_assign
op_amp
id|op_p4_spec
suffix:semicolon
r_return
l_int|1
suffix:semicolon
macro_line|#else
r_switch
c_cond
(paren
id|smp_num_siblings
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|cpu
op_assign
id|OPROFILE_CPU_P4
suffix:semicolon
id|model
op_assign
op_amp
id|op_p4_spec
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|cpu
op_assign
id|OPROFILE_CPU_P4_HT2
suffix:semicolon
id|model
op_assign
op_amp
id|op_p4_ht2_spec
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: P4 HyperThreading detected with &gt; 2 threads&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: Reverting to timer mode.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ppro_init
r_static
r_int
id|__init
id|ppro_init
c_func
(paren
r_enum
id|oprofile_cpu
op_star
id|cpu
)paren
(brace
id|__u8
id|cpu_model
op_assign
id|current_cpu_data.x86_model
suffix:semicolon
r_if
c_cond
(paren
id|cpu_model
OG
l_int|5
)paren
(brace
op_star
id|cpu
op_assign
id|OPROFILE_CPU_PIII
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpu_model
OG
l_int|2
)paren
(brace
op_star
id|cpu
op_assign
id|OPROFILE_CPU_PII
suffix:semicolon
)brace
r_else
(brace
op_star
id|cpu
op_assign
id|OPROFILE_CPU_PPRO
suffix:semicolon
)brace
id|model
op_assign
op_amp
id|op_ppro_spec
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_X86_64 */
DECL|function|nmi_init
r_int
id|__init
id|nmi_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
comma
r_enum
id|oprofile_cpu
op_star
id|cpu
)paren
(brace
id|__u8
id|vendor
op_assign
id|current_cpu_data.x86_vendor
suffix:semicolon
id|__u8
id|family
op_assign
id|current_cpu_data.x86
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_apic
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|vendor
)paren
(brace
r_case
id|X86_VENDOR_AMD
suffix:colon
multiline_comment|/* Needs to be at least an Athlon (or hammer in 32bit mode) */
r_if
c_cond
(paren
id|family
OL
l_int|6
)paren
r_return
l_int|0
suffix:semicolon
id|model
op_assign
op_amp
id|op_athlon_spec
suffix:semicolon
op_star
id|cpu
op_assign
id|OPROFILE_CPU_ATHLON
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if !defined(CONFIG_X86_64)
r_case
id|X86_VENDOR_INTEL
suffix:colon
r_switch
c_cond
(paren
id|family
)paren
(brace
multiline_comment|/* Pentium IV */
r_case
l_int|0xf
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|p4_init
c_func
(paren
id|cpu
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* A P6-class processor */
r_case
l_int|6
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|ppro_init
c_func
(paren
id|cpu
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif /* !CONFIG_X86_64 */
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|ops
op_assign
op_amp
id|nmi_ops
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: using NMI interrupt.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
