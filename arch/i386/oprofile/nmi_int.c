multiline_comment|/**&n; * @file nmi_int.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon &lt;levon@movementarian.org&gt;&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/sysdev.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
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
multiline_comment|/* 0 == registered but off, 1 == registered and on */
DECL|variable|nmi_enabled
r_static
r_int
id|nmi_enabled
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|function|nmi_suspend
r_static
r_int
id|nmi_suspend
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
r_if
c_cond
(paren
id|nmi_enabled
op_eq
l_int|1
)paren
id|nmi_stop
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nmi_resume
r_static
r_int
id|nmi_resume
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
id|nmi_enabled
op_eq
l_int|1
)paren
id|nmi_start
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|oprofile_sysclass
r_static
r_struct
id|sysdev_class
id|oprofile_sysclass
op_assign
(brace
id|set_kset_name
c_func
(paren
l_string|&quot;oprofile&quot;
)paren
comma
dot
id|resume
op_assign
id|nmi_resume
comma
dot
id|suspend
op_assign
id|nmi_suspend
comma
)brace
suffix:semicolon
DECL|variable|device_oprofile
r_static
r_struct
id|sys_device
id|device_oprofile
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
id|oprofile_sysclass
comma
)brace
suffix:semicolon
DECL|function|init_driverfs
r_static
r_int
id|__init
id|init_driverfs
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
op_logical_neg
(paren
id|error
op_assign
id|sysdev_class_register
c_func
(paren
op_amp
id|oprofile_sysclass
)paren
)paren
)paren
id|error
op_assign
id|sys_device_register
c_func
(paren
op_amp
id|device_oprofile
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|exit_driverfs
r_static
r_void
id|__exit
id|exit_driverfs
c_func
(paren
r_void
)paren
(brace
id|sys_device_unregister
c_func
(paren
op_amp
id|device_oprofile
)paren
suffix:semicolon
id|sysdev_class_unregister
c_func
(paren
op_amp
id|oprofile_sysclass
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|init_driverfs
mdefine_line|#define init_driverfs() do { } while (0)
DECL|macro|exit_driverfs
mdefine_line|#define exit_driverfs() do { } while (0)
macro_line|#endif /* CONFIG_PM */
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
DECL|function|nmi_cpu_save_registers
r_static
r_void
id|nmi_cpu_save_registers
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
id|op_msr
op_star
id|counters
op_assign
id|msrs-&gt;counters
suffix:semicolon
r_struct
id|op_msr
op_star
id|controls
op_assign
id|msrs-&gt;controls
suffix:semicolon
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
id|nr_ctrs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|rdmsr
c_func
(paren
id|counters
(braket
id|i
)braket
dot
id|addr
comma
id|counters
(braket
id|i
)braket
dot
id|saved.low
comma
id|counters
(braket
id|i
)braket
dot
id|saved.high
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
id|controls
(braket
id|i
)braket
dot
id|addr
comma
id|controls
(braket
id|i
)braket
dot
id|saved.low
comma
id|controls
(braket
id|i
)braket
dot
id|saved.high
)paren
suffix:semicolon
)brace
)brace
DECL|function|nmi_save_registers
r_static
r_void
id|nmi_save_registers
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
id|nmi_cpu_save_registers
c_func
(paren
id|msrs
)paren
suffix:semicolon
)brace
DECL|function|free_msrs
r_static
r_void
id|free_msrs
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
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|kfree
c_func
(paren
id|cpu_msrs
(braket
id|i
)braket
dot
id|counters
)paren
suffix:semicolon
id|cpu_msrs
(braket
id|i
)braket
dot
id|counters
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|cpu_msrs
(braket
id|i
)braket
dot
id|controls
)paren
suffix:semicolon
id|cpu_msrs
(braket
id|i
)braket
dot
id|controls
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|allocate_msrs
r_static
r_int
id|allocate_msrs
c_func
(paren
r_void
)paren
(brace
r_int
id|success
op_assign
l_int|1
suffix:semicolon
r_int
id|controls_size
op_assign
r_sizeof
(paren
r_struct
id|op_msr
)paren
op_star
id|model-&gt;num_controls
suffix:semicolon
r_int
id|counters_size
op_assign
r_sizeof
(paren
r_struct
id|op_msr
)paren
op_star
id|model-&gt;num_counters
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
id|NR_CPUS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|cpu_msrs
(braket
id|i
)braket
dot
id|counters
op_assign
id|kmalloc
c_func
(paren
id|counters_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_msrs
(braket
id|i
)braket
dot
id|counters
)paren
(brace
id|success
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|cpu_msrs
(braket
id|i
)braket
dot
id|controls
op_assign
id|kmalloc
c_func
(paren
id|controls_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cpu_msrs
(braket
id|i
)braket
dot
id|controls
)paren
(brace
id|success
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|success
)paren
id|free_msrs
c_func
(paren
)paren
suffix:semicolon
r_return
id|success
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|allocate_msrs
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* We walk a thin line between law and rape here.&n;&t; * We need to be careful to install our NMI handler&n;&t; * without actually triggering any NMIs as this will&n;&t; * break the core code horrifically.&n;&t; */
id|disable_lapic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We need to serialize save and setup for HT because the subset&n;&t; * of msrs are distinct for save and setup operations&n;&t; */
id|on_each_cpu
c_func
(paren
id|nmi_save_registers
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|on_each_cpu
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
id|set_nmi_callback
c_func
(paren
id|nmi_callback
)paren
suffix:semicolon
id|nmi_enabled
op_assign
l_int|1
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
id|op_msr
op_star
id|counters
op_assign
id|msrs-&gt;counters
suffix:semicolon
r_struct
id|op_msr
op_star
id|controls
op_assign
id|msrs-&gt;controls
suffix:semicolon
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
id|nr_ctrls
suffix:semicolon
op_increment
id|i
)paren
(brace
id|wrmsr
c_func
(paren
id|controls
(braket
id|i
)braket
dot
id|addr
comma
id|controls
(braket
id|i
)braket
dot
id|saved.low
comma
id|controls
(braket
id|i
)braket
dot
id|saved.high
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
id|counters
(braket
id|i
)braket
dot
id|addr
comma
id|counters
(braket
id|i
)braket
dot
id|saved.low
comma
id|counters
(braket
id|i
)braket
dot
id|saved.high
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
id|nmi_enabled
op_assign
l_int|0
suffix:semicolon
id|on_each_cpu
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
id|unset_nmi_callback
c_func
(paren
)paren
suffix:semicolon
id|enable_lapic_nmi_watchdog
c_func
(paren
)paren
suffix:semicolon
id|free_msrs
c_func
(paren
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
id|on_each_cpu
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
id|on_each_cpu
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
DECL|function|p4_init
r_static
r_int
id|__init
id|p4_init
c_func
(paren
r_void
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
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/p4&quot;
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
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/p4&quot;
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
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/p4-ht&quot;
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
r_void
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
l_int|0xd
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cpu_model
op_eq
l_int|9
)paren
(brace
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/p6_mobile&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cpu_model
OG
l_int|5
)paren
(brace
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/piii&quot;
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
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/pii&quot;
suffix:semicolon
)brace
r_else
(brace
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/ppro&quot;
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
multiline_comment|/* in order to get driverfs right */
DECL|variable|using_nmi
r_static
r_int
id|using_nmi
suffix:semicolon
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
op_minus
id|ENODEV
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
r_switch
c_cond
(paren
id|family
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
r_case
l_int|6
suffix:colon
id|model
op_assign
op_amp
id|op_athlon_spec
suffix:semicolon
id|nmi_ops.cpu_type
op_assign
l_string|&quot;i386/athlon&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf
suffix:colon
id|model
op_assign
op_amp
id|op_athlon_spec
suffix:semicolon
multiline_comment|/* Actually it could be i386/hammer too, but give&n;&t;&t;&t;&t;   user space an consistent name. */
id|nmi_ops.cpu_type
op_assign
l_string|&quot;x86-64/hammer&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
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
)paren
)paren
r_return
op_minus
id|ENODEV
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
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|init_driverfs
c_func
(paren
)paren
suffix:semicolon
id|using_nmi
op_assign
l_int|1
suffix:semicolon
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
l_int|0
suffix:semicolon
)brace
DECL|function|nmi_exit
r_void
id|__exit
id|nmi_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|using_nmi
)paren
id|exit_driverfs
c_func
(paren
)paren
suffix:semicolon
)brace
eof
