multiline_comment|/**&n; * @file arch/alpha/oprofile/common.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author Richard Henderson &lt;rth@twiddle.net&gt;&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;op_impl.h&quot;
r_extern
r_struct
id|op_axp_model
id|op_model_ev4
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|op_axp_model
id|op_model_ev5
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|op_axp_model
id|op_model_pca56
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|op_axp_model
id|op_model_ev6
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|op_axp_model
id|op_model_ev67
id|__attribute__
c_func
(paren
(paren
id|weak
)paren
)paren
suffix:semicolon
DECL|variable|model
r_static
r_struct
id|op_axp_model
op_star
id|model
suffix:semicolon
r_extern
r_void
(paren
op_star
id|perf_irq
)paren
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|save_perf_irq
r_static
r_void
(paren
op_star
id|save_perf_irq
)paren
(paren
r_int
r_int
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|variable|ctr
r_static
r_struct
id|op_counter_config
id|ctr
(braket
l_int|20
)braket
suffix:semicolon
DECL|variable|sys
r_static
r_struct
id|op_system_config
id|sys
suffix:semicolon
DECL|variable|reg
r_static
r_struct
id|op_register_config
id|reg
suffix:semicolon
multiline_comment|/* Called from do_entInt to handle the performance monitor interrupt.  */
r_static
r_void
DECL|function|op_handle_interrupt
id|op_handle_interrupt
c_func
(paren
r_int
r_int
id|which
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|model
op_member_access_from_pointer
id|handle_interrupt
c_func
(paren
id|which
comma
id|regs
comma
id|ctr
)paren
suffix:semicolon
multiline_comment|/* If the user has selected an interrupt frequency that is&n;&t;   not exactly the width of the counter, write a new value&n;&t;   into the counter such that it&squot;ll overflow after N more&n;&t;   events.  */
r_if
c_cond
(paren
(paren
id|reg.need_reset
op_rshift
id|which
)paren
op_amp
l_int|1
)paren
id|model
op_member_access_from_pointer
id|reset_ctr
c_func
(paren
op_amp
id|reg
comma
id|which
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|op_axp_setup
id|op_axp_setup
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|e
suffix:semicolon
multiline_comment|/* Install our interrupt handler into the existing hook.  */
id|save_perf_irq
op_assign
id|perf_irq
suffix:semicolon
id|perf_irq
op_assign
id|op_handle_interrupt
suffix:semicolon
multiline_comment|/* Compute the mask of enabled counters.  */
r_for
c_loop
(paren
id|i
op_assign
id|e
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
r_if
c_cond
(paren
id|ctr
(braket
l_int|0
)braket
dot
id|enabled
)paren
id|e
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
id|reg.enable
op_assign
id|e
suffix:semicolon
multiline_comment|/* Pre-compute the values to stuff in the hardware registers.  */
id|model
op_member_access_from_pointer
id|reg_setup
c_func
(paren
op_amp
id|reg
comma
id|ctr
comma
op_amp
id|sys
)paren
suffix:semicolon
multiline_comment|/* Configure the registers on all cpus.  */
id|smp_call_function
c_func
(paren
id|model-&gt;cpu_setup
comma
op_amp
id|reg
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|model
op_member_access_from_pointer
id|cpu_setup
c_func
(paren
op_amp
id|reg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|op_axp_shutdown
id|op_axp_shutdown
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Remove our interrupt handler.  We may be removing this module.  */
id|perf_irq
op_assign
id|save_perf_irq
suffix:semicolon
)brace
r_static
r_void
DECL|function|op_axp_cpu_start
id|op_axp_cpu_start
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
id|wrperfmon
c_func
(paren
l_int|1
comma
id|reg.enable
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|op_axp_start
id|op_axp_start
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|op_axp_cpu_start
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|op_axp_cpu_start
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|op_axp_cpu_stop
id|op_axp_cpu_stop
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
multiline_comment|/* Disable performance monitoring for all counters.  */
id|wrperfmon
c_func
(paren
l_int|0
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|op_axp_stop
id|op_axp_stop
c_func
(paren
r_void
)paren
(brace
id|smp_call_function
c_func
(paren
id|op_axp_cpu_stop
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|op_axp_cpu_stop
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|op_axp_create_files
id|op_axp_create_files
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
l_int|3
)braket
suffix:semicolon
id|snprintf
c_func
(paren
id|buf
comma
r_sizeof
id|buf
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
id|ctr
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
id|ctr
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
id|ctr
(braket
id|i
)braket
dot
id|count
)paren
suffix:semicolon
multiline_comment|/* Dummies.  */
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
id|ctr
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
id|ctr
(braket
id|i
)braket
dot
id|user
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
id|ctr
(braket
id|i
)braket
dot
id|unit_mask
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|model-&gt;can_set_proc_mode
)paren
(brace
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;enable_pal&quot;
comma
op_amp
id|sys.enable_pal
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;enable_kernel&quot;
comma
op_amp
id|sys.enable_kernel
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;enable_user&quot;
comma
op_amp
id|sys.enable_user
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|oprof_axp_ops
r_static
r_struct
id|oprofile_operations
id|oprof_axp_ops
op_assign
(brace
dot
id|create_files
op_assign
id|op_axp_create_files
comma
dot
id|setup
op_assign
id|op_axp_setup
comma
dot
id|shutdown
op_assign
id|op_axp_shutdown
comma
dot
id|start
op_assign
id|op_axp_start
comma
dot
id|stop
op_assign
id|op_axp_stop
comma
dot
id|cpu_type
op_assign
l_int|NULL
multiline_comment|/* To be filled in below.  */
)brace
suffix:semicolon
r_int
id|__init
DECL|function|oprofile_arch_init
id|oprofile_arch_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
op_star
id|ops
)paren
(brace
r_struct
id|op_axp_model
op_star
id|lmodel
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|implver
c_func
(paren
)paren
)paren
(brace
r_case
id|IMPLVER_EV4
suffix:colon
id|lmodel
op_assign
op_amp
id|op_model_ev4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IMPLVER_EV5
suffix:colon
multiline_comment|/* 21164PC has a slightly different set of events.&n;&t;&t;   Recognize the chip by the presence of the MAX insns.  */
r_if
c_cond
(paren
op_logical_neg
id|amask
c_func
(paren
id|AMASK_MAX
)paren
)paren
id|lmodel
op_assign
op_amp
id|op_model_pca56
suffix:semicolon
r_else
id|lmodel
op_assign
op_amp
id|op_model_ev5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IMPLVER_EV6
suffix:colon
multiline_comment|/* 21264A supports ProfileMe.&n;&t;&t;   Recognize the chip by the presence of the CIX insns.  */
r_if
c_cond
(paren
op_logical_neg
id|amask
c_func
(paren
id|AMASK_CIX
)paren
)paren
id|lmodel
op_assign
op_amp
id|op_model_ev67
suffix:semicolon
r_else
id|lmodel
op_assign
op_amp
id|op_model_ev6
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|lmodel
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|model
op_assign
id|lmodel
suffix:semicolon
id|oprof_axp_ops.cpu_type
op_assign
id|lmodel-&gt;cpu_type
suffix:semicolon
op_star
id|ops
op_assign
op_amp
id|oprof_axp_ops
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: using %s performance monitoring.&bslash;n&quot;
comma
id|lmodel-&gt;cpu_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|oprofile_arch_exit
id|oprofile_arch_exit
c_func
(paren
r_void
)paren
(brace
)brace
eof
