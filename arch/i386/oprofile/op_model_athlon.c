multiline_comment|/**&n; * @file op_model_athlon.h&n; * athlon / K7 model-specific MSR operations&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon&n; * @author Philippe Elie&n; * @author Graydon Hoare&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &quot;op_x86_model.h&quot;
macro_line|#include &quot;op_counter.h&quot;
DECL|macro|NUM_COUNTERS
mdefine_line|#define NUM_COUNTERS 4
DECL|macro|NUM_CONTROLS
mdefine_line|#define NUM_CONTROLS 4
DECL|macro|CTR_READ
mdefine_line|#define CTR_READ(l,h,msrs,c) do {rdmsr(msrs-&gt;counters[(c)].addr, (l), (h));} while (0)
DECL|macro|CTR_WRITE
mdefine_line|#define CTR_WRITE(l,msrs,c) do {wrmsr(msrs-&gt;counters[(c)].addr, -(unsigned int)(l), -1);} while (0)
DECL|macro|CTR_OVERFLOWED
mdefine_line|#define CTR_OVERFLOWED(n) (!((n) &amp; (1U&lt;&lt;31)))
DECL|macro|CTRL_READ
mdefine_line|#define CTRL_READ(l,h,msrs,c) do {rdmsr(msrs-&gt;controls[(c)].addr, (l), (h));} while (0)
DECL|macro|CTRL_WRITE
mdefine_line|#define CTRL_WRITE(l,h,msrs,c) do {wrmsr(msrs-&gt;controls[(c)].addr, (l), (h));} while (0)
DECL|macro|CTRL_SET_ACTIVE
mdefine_line|#define CTRL_SET_ACTIVE(n) (n |= (1&lt;&lt;22))
DECL|macro|CTRL_SET_INACTIVE
mdefine_line|#define CTRL_SET_INACTIVE(n) (n &amp;= ~(1&lt;&lt;22))
DECL|macro|CTRL_CLEAR
mdefine_line|#define CTRL_CLEAR(x) (x &amp;= (1&lt;&lt;21))
DECL|macro|CTRL_SET_ENABLE
mdefine_line|#define CTRL_SET_ENABLE(val) (val |= 1&lt;&lt;20)
DECL|macro|CTRL_SET_USR
mdefine_line|#define CTRL_SET_USR(val,u) (val |= ((u &amp; 1) &lt;&lt; 16))
DECL|macro|CTRL_SET_KERN
mdefine_line|#define CTRL_SET_KERN(val,k) (val |= ((k &amp; 1) &lt;&lt; 17))
DECL|macro|CTRL_SET_UM
mdefine_line|#define CTRL_SET_UM(val, m) (val |= (m &lt;&lt; 8))
DECL|macro|CTRL_SET_EVENT
mdefine_line|#define CTRL_SET_EVENT(val, e) (val |= e)
DECL|variable|reset_value
r_static
r_int
r_int
id|reset_value
(braket
id|NUM_COUNTERS
)braket
suffix:semicolon
DECL|function|athlon_fill_in_addresses
r_static
r_void
id|athlon_fill_in_addresses
c_func
(paren
r_struct
id|op_msrs
op_star
r_const
id|msrs
)paren
(brace
id|msrs-&gt;counters
(braket
l_int|0
)braket
dot
id|addr
op_assign
id|MSR_K7_PERFCTR0
suffix:semicolon
id|msrs-&gt;counters
(braket
l_int|1
)braket
dot
id|addr
op_assign
id|MSR_K7_PERFCTR1
suffix:semicolon
id|msrs-&gt;counters
(braket
l_int|2
)braket
dot
id|addr
op_assign
id|MSR_K7_PERFCTR2
suffix:semicolon
id|msrs-&gt;counters
(braket
l_int|3
)braket
dot
id|addr
op_assign
id|MSR_K7_PERFCTR3
suffix:semicolon
id|msrs-&gt;controls
(braket
l_int|0
)braket
dot
id|addr
op_assign
id|MSR_K7_EVNTSEL0
suffix:semicolon
id|msrs-&gt;controls
(braket
l_int|1
)braket
dot
id|addr
op_assign
id|MSR_K7_EVNTSEL1
suffix:semicolon
id|msrs-&gt;controls
(braket
l_int|2
)braket
dot
id|addr
op_assign
id|MSR_K7_EVNTSEL2
suffix:semicolon
id|msrs-&gt;controls
(braket
l_int|3
)braket
dot
id|addr
op_assign
id|MSR_K7_EVNTSEL3
suffix:semicolon
)brace
DECL|function|athlon_setup_ctrs
r_static
r_void
id|athlon_setup_ctrs
c_func
(paren
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* clear all counters */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_CONTROLS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|CTRL_READ
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
id|CTRL_CLEAR
c_func
(paren
id|low
)paren
suffix:semicolon
id|CTRL_WRITE
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* avoid a false detection of ctr overflows in NMI handler */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_COUNTERS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|CTR_WRITE
c_func
(paren
l_int|1
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* enable active counters */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_COUNTERS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|counter_config
(braket
id|i
)braket
dot
id|enabled
)paren
(brace
id|reset_value
(braket
id|i
)braket
op_assign
id|counter_config
(braket
id|i
)braket
dot
id|count
suffix:semicolon
id|CTR_WRITE
c_func
(paren
id|counter_config
(braket
id|i
)braket
dot
id|count
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
id|CTRL_READ
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
id|CTRL_CLEAR
c_func
(paren
id|low
)paren
suffix:semicolon
id|CTRL_SET_ENABLE
c_func
(paren
id|low
)paren
suffix:semicolon
id|CTRL_SET_USR
c_func
(paren
id|low
comma
id|counter_config
(braket
id|i
)braket
dot
id|user
)paren
suffix:semicolon
id|CTRL_SET_KERN
c_func
(paren
id|low
comma
id|counter_config
(braket
id|i
)braket
dot
id|kernel
)paren
suffix:semicolon
id|CTRL_SET_UM
c_func
(paren
id|low
comma
id|counter_config
(braket
id|i
)braket
dot
id|unit_mask
)paren
suffix:semicolon
id|CTRL_SET_EVENT
c_func
(paren
id|low
comma
id|counter_config
(braket
id|i
)braket
dot
id|event
)paren
suffix:semicolon
id|CTRL_WRITE
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
)brace
r_else
(brace
id|reset_value
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|function|athlon_check_ctrs
r_static
r_int
id|athlon_check_ctrs
c_func
(paren
r_struct
id|pt_regs
op_star
r_const
id|regs
comma
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|low
comma
id|high
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
id|NUM_COUNTERS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|CTR_READ
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CTR_OVERFLOWED
c_func
(paren
id|low
)paren
)paren
(brace
id|oprofile_add_sample
c_func
(paren
id|regs
comma
id|i
)paren
suffix:semicolon
id|CTR_WRITE
c_func
(paren
id|reset_value
(braket
id|i
)braket
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* See op_model_ppro.c */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|athlon_start
r_static
r_void
id|athlon_start
c_func
(paren
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|low
comma
id|high
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
id|NUM_COUNTERS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|reset_value
(braket
id|i
)braket
)paren
(brace
id|CTRL_READ
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
id|CTRL_SET_ACTIVE
c_func
(paren
id|low
)paren
suffix:semicolon
id|CTRL_WRITE
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|athlon_stop
r_static
r_void
id|athlon_stop
c_func
(paren
r_struct
id|op_msrs
r_const
op_star
r_const
id|msrs
)paren
(brace
r_int
r_int
id|low
comma
id|high
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Subtle: stop on all counters to avoid race with&n;&t; * setting our pm callback */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_COUNTERS
suffix:semicolon
op_increment
id|i
)paren
(brace
id|CTRL_READ
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
id|CTRL_SET_INACTIVE
c_func
(paren
id|low
)paren
suffix:semicolon
id|CTRL_WRITE
c_func
(paren
id|low
comma
id|high
comma
id|msrs
comma
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|variable|op_athlon_spec
r_struct
id|op_x86_model_spec
r_const
id|op_athlon_spec
op_assign
(brace
dot
id|num_counters
op_assign
id|NUM_COUNTERS
comma
dot
id|num_controls
op_assign
id|NUM_CONTROLS
comma
dot
id|fill_in_addresses
op_assign
op_amp
id|athlon_fill_in_addresses
comma
dot
id|setup_ctrs
op_assign
op_amp
id|athlon_setup_ctrs
comma
dot
id|check_ctrs
op_assign
op_amp
id|athlon_check_ctrs
comma
dot
id|start
op_assign
op_amp
id|athlon_start
comma
dot
id|stop
op_assign
op_amp
id|athlon_stop
)brace
suffix:semicolon
eof
