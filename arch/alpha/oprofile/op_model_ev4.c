multiline_comment|/**&n; * @file arch/alpha/oprofile/op_model_ev4.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author Richard Henderson &lt;rth@twiddle.net&gt;&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;op_impl.h&quot;
multiline_comment|/* Compute all of the registers in preparation for enabling profiling.  */
r_static
r_void
DECL|function|ev4_reg_setup
id|ev4_reg_setup
c_func
(paren
r_struct
id|op_register_config
op_star
id|reg
comma
r_struct
id|op_counter_config
op_star
id|ctr
comma
r_struct
id|op_system_config
op_star
id|sys
)paren
(brace
r_int
r_int
id|ctl
op_assign
l_int|0
comma
id|count
comma
id|hilo
suffix:semicolon
multiline_comment|/* Select desired events.  We&squot;ve mapped the event numbers&n;&t;   such that they fit directly into the event selection fields.&n;&n;&t;   Note that there is no &quot;off&quot; setting.  In both cases we select&n;&t;   the EXTERNAL event source, hoping that it&squot;ll be the lowest&n;&t;   frequency, and set the frequency counter to LOW.  The interrupts&n;&t;   for these &quot;disabled&quot; counter overflows are ignored by the&n;&t;   interrupt handler.&n;&n;&t;   This is most irritating, because the hardware *can* enable and&n;&t;   disable the interrupts for these counters independently, but the&n;&t;   wrperfmon interface doesn&squot;t allow it.  */
id|ctl
op_or_assign
(paren
id|ctr
(braket
l_int|0
)braket
dot
id|enabled
ques
c_cond
id|ctr
(braket
l_int|0
)braket
dot
id|event
op_lshift
l_int|8
suffix:colon
l_int|14
op_lshift
l_int|8
)paren
suffix:semicolon
id|ctl
op_or_assign
(paren
id|ctr
(braket
l_int|1
)braket
dot
id|enabled
ques
c_cond
(paren
id|ctr
(braket
l_int|1
)braket
dot
id|event
op_minus
l_int|16
)paren
op_lshift
l_int|32
suffix:colon
l_int|7ul
op_lshift
l_int|32
)paren
suffix:semicolon
multiline_comment|/* EV4 can not read or write its counter registers.  The only&n;&t;   thing one can do at all is see if you overflow and get an&n;&t;   interrupt.  We can set the width of the counters, to some&n;&t;   extent.  Take the interrupt count selected by the user,&n;&t;   map it onto one of the possible values, and write it back.  */
id|count
op_assign
id|ctr
(braket
l_int|0
)braket
dot
id|count
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|4096
)paren
id|count
op_assign
l_int|4096
comma
id|hilo
op_assign
l_int|1
suffix:semicolon
r_else
id|count
op_assign
l_int|65536
comma
id|hilo
op_assign
l_int|0
suffix:semicolon
id|ctr
(braket
l_int|0
)braket
dot
id|count
op_assign
id|count
suffix:semicolon
id|ctl
op_or_assign
(paren
id|ctr
(braket
l_int|0
)braket
dot
id|enabled
op_logical_and
id|hilo
)paren
op_lshift
l_int|3
suffix:semicolon
id|count
op_assign
id|ctr
(braket
l_int|1
)braket
dot
id|count
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|256
)paren
id|count
op_assign
l_int|256
comma
id|hilo
op_assign
l_int|1
suffix:semicolon
r_else
id|count
op_assign
l_int|4096
comma
id|hilo
op_assign
l_int|0
suffix:semicolon
id|ctr
(braket
l_int|1
)braket
dot
id|count
op_assign
id|count
suffix:semicolon
id|ctl
op_or_assign
(paren
id|ctr
(braket
l_int|1
)braket
dot
id|enabled
op_logical_and
id|hilo
)paren
suffix:semicolon
id|reg-&gt;mux_select
op_assign
id|ctl
suffix:semicolon
multiline_comment|/* Select performance monitoring options.  */
multiline_comment|/* ??? Need to come up with some mechanism to trace only&n;&t;   selected processes.  EV4 does not have a mechanism to&n;&t;   select kernel or user mode only.  For now, enable always.  */
id|reg-&gt;proc_mode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Frequency is folded into mux_select for EV4.  */
id|reg-&gt;freq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* See above regarding no writes.  */
id|reg-&gt;reset_values
op_assign
l_int|0
suffix:semicolon
id|reg-&gt;need_reset
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Program all of the registers in preparation for enabling profiling.  */
r_static
r_void
DECL|function|ev4_cpu_setup
id|ev4_cpu_setup
c_func
(paren
r_void
op_star
id|x
)paren
(brace
r_struct
id|op_register_config
op_star
id|reg
op_assign
id|x
suffix:semicolon
id|wrperfmon
c_func
(paren
l_int|2
comma
id|reg-&gt;mux_select
)paren
suffix:semicolon
id|wrperfmon
c_func
(paren
l_int|3
comma
id|reg-&gt;proc_mode
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ev4_handle_interrupt
id|ev4_handle_interrupt
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
comma
r_struct
id|op_counter_config
op_star
id|ctr
)paren
(brace
multiline_comment|/* EV4 can&squot;t properly disable counters individually.&n;&t;   Discard &quot;disabled&quot; events now.  */
r_if
c_cond
(paren
op_logical_neg
id|ctr
(braket
id|which
)braket
dot
id|enabled
)paren
r_return
suffix:semicolon
multiline_comment|/* Record the sample.  */
id|oprofile_add_sample
c_func
(paren
id|regs
comma
id|which
)paren
suffix:semicolon
)brace
DECL|variable|op_model_ev4
r_struct
id|op_axp_model
id|op_model_ev4
op_assign
(brace
dot
id|reg_setup
op_assign
id|ev4_reg_setup
comma
dot
id|cpu_setup
op_assign
id|ev4_cpu_setup
comma
dot
id|reset_ctr
op_assign
l_int|NULL
comma
dot
id|handle_interrupt
op_assign
id|ev4_handle_interrupt
comma
dot
id|cpu_type
op_assign
l_string|&quot;alpha/ev4&quot;
comma
dot
id|num_counters
op_assign
l_int|2
comma
dot
id|can_set_proc_mode
op_assign
l_int|0
comma
)brace
suffix:semicolon
eof
