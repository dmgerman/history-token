multiline_comment|/*&n; * Copyright (C) 2004 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * Based on alpha version.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pmc.h&gt;
macro_line|#include &quot;op_impl.h&quot;
r_extern
r_struct
id|op_ppc64_model
id|op_model_rs64
suffix:semicolon
r_extern
r_struct
id|op_ppc64_model
id|op_model_power4
suffix:semicolon
DECL|variable|model
r_static
r_struct
id|op_ppc64_model
op_star
id|model
suffix:semicolon
DECL|variable|ctr
r_static
r_struct
id|op_counter_config
id|ctr
(braket
id|OP_MAX_COUNTER
)braket
suffix:semicolon
DECL|variable|sys
r_static
r_struct
id|op_system_config
id|sys
suffix:semicolon
DECL|function|op_handle_interrupt
r_static
r_void
id|op_handle_interrupt
c_func
(paren
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
id|regs
comma
id|ctr
)paren
suffix:semicolon
)brace
DECL|function|op_ppc64_setup
r_static
r_int
id|op_ppc64_setup
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* Grab the hardware */
id|err
op_assign
id|reserve_pmc_hardware
c_func
(paren
id|op_handle_interrupt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* Pre-compute the values to stuff in the hardware registers.  */
id|model
op_member_access_from_pointer
id|reg_setup
c_func
(paren
id|ctr
comma
op_amp
id|sys
comma
id|model-&gt;num_counters
)paren
suffix:semicolon
multiline_comment|/* Configure the registers on all cpus.  */
id|on_each_cpu
c_func
(paren
id|model-&gt;cpu_setup
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
DECL|function|op_ppc64_shutdown
r_static
r_void
id|op_ppc64_shutdown
c_func
(paren
r_void
)paren
(brace
id|release_pmc_hardware
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|op_ppc64_cpu_start
r_static
r_void
id|op_ppc64_cpu_start
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
id|model
op_member_access_from_pointer
id|start
c_func
(paren
id|ctr
)paren
suffix:semicolon
)brace
DECL|function|op_ppc64_start
r_static
r_int
id|op_ppc64_start
c_func
(paren
r_void
)paren
(brace
id|on_each_cpu
c_func
(paren
id|op_ppc64_cpu_start
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
DECL|function|op_ppc64_cpu_stop
r_static
r_inline
r_void
id|op_ppc64_cpu_stop
c_func
(paren
r_void
op_star
id|dummy
)paren
(brace
id|model
op_member_access_from_pointer
id|stop
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|op_ppc64_stop
r_static
r_void
id|op_ppc64_stop
c_func
(paren
r_void
)paren
(brace
id|on_each_cpu
c_func
(paren
id|op_ppc64_cpu_stop
comma
l_int|NULL
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|op_ppc64_create_files
r_static
r_int
id|op_ppc64_create_files
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
multiline_comment|/*&n;&t; * There is one mmcr0, mmcr1 and mmcra for setting the events for&n;&t; * all of the counters.&n;&t; */
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;mmcr0&quot;
comma
op_amp
id|sys.mmcr0
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;mmcr1&quot;
comma
op_amp
id|sys.mmcr1
)paren
suffix:semicolon
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;mmcra&quot;
comma
op_amp
id|sys.mmcra
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
multiline_comment|/*&n;&t;&t; * We dont support per counter user/kernel selection, but&n;&t;&t; * we leave the entries because userspace expects them&n;&t;&t; */
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
id|oprofilefs_create_ulong
c_func
(paren
id|sb
comma
id|root
comma
l_string|&quot;backtrace_spinlocks&quot;
comma
op_amp
id|sys.backtrace_spinlocks
)paren
suffix:semicolon
multiline_comment|/* Default to tracing both kernel and user */
id|sys.enable_kernel
op_assign
l_int|1
suffix:semicolon
id|sys.enable_user
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Turn on backtracing through spinlocks by default */
id|sys.backtrace_spinlocks
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|oprofile_arch_init
r_int
id|__init
id|oprofile_arch_init
c_func
(paren
r_struct
id|oprofile_operations
op_star
id|ops
)paren
(brace
r_int
r_int
id|pvr
suffix:semicolon
id|pvr
op_assign
id|mfspr
c_func
(paren
id|SPRN_PVR
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|PVR_VER
c_func
(paren
id|pvr
)paren
)paren
(brace
r_case
id|PV_630
suffix:colon
r_case
id|PV_630p
suffix:colon
id|model
op_assign
op_amp
id|op_model_rs64
suffix:semicolon
id|model-&gt;num_counters
op_assign
l_int|8
suffix:semicolon
id|ops-&gt;cpu_type
op_assign
l_string|&quot;ppc64/power3&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_NORTHSTAR
suffix:colon
r_case
id|PV_PULSAR
suffix:colon
r_case
id|PV_ICESTAR
suffix:colon
r_case
id|PV_SSTAR
suffix:colon
id|model
op_assign
op_amp
id|op_model_rs64
suffix:semicolon
id|model-&gt;num_counters
op_assign
l_int|8
suffix:semicolon
id|ops-&gt;cpu_type
op_assign
l_string|&quot;ppc64/rs64&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_POWER4
suffix:colon
r_case
id|PV_POWER4p
suffix:colon
id|model
op_assign
op_amp
id|op_model_power4
suffix:semicolon
id|model-&gt;num_counters
op_assign
l_int|8
suffix:semicolon
id|ops-&gt;cpu_type
op_assign
l_string|&quot;ppc64/power4&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_970
suffix:colon
r_case
id|PV_970FX
suffix:colon
id|model
op_assign
op_amp
id|op_model_power4
suffix:semicolon
id|model-&gt;num_counters
op_assign
l_int|8
suffix:semicolon
id|ops-&gt;cpu_type
op_assign
l_string|&quot;ppc64/970&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PV_POWER5
suffix:colon
r_case
id|PV_POWER5p
suffix:colon
id|model
op_assign
op_amp
id|op_model_power4
suffix:semicolon
id|model-&gt;num_counters
op_assign
l_int|6
suffix:semicolon
id|ops-&gt;cpu_type
op_assign
l_string|&quot;ppc64/power5&quot;
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
id|ops-&gt;create_files
op_assign
id|op_ppc64_create_files
suffix:semicolon
id|ops-&gt;setup
op_assign
id|op_ppc64_setup
suffix:semicolon
id|ops-&gt;shutdown
op_assign
id|op_ppc64_shutdown
suffix:semicolon
id|ops-&gt;start
op_assign
id|op_ppc64_start
suffix:semicolon
id|ops-&gt;stop
op_assign
id|op_ppc64_stop
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;oprofile: using %s performance monitoring.&bslash;n&quot;
comma
id|ops-&gt;cpu_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|oprofile_arch_exit
r_void
id|oprofile_arch_exit
c_func
(paren
r_void
)paren
(brace
)brace
eof
