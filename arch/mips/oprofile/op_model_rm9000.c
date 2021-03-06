multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 by Ralf Baechle&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &quot;op_impl.h&quot;
DECL|macro|RM9K_COUNTER1_EVENT
mdefine_line|#define RM9K_COUNTER1_EVENT(event)&t;((event) &lt;&lt; 0)
DECL|macro|RM9K_COUNTER1_SUPERVISOR
mdefine_line|#define RM9K_COUNTER1_SUPERVISOR&t;(1ULL    &lt;&lt;  7)
DECL|macro|RM9K_COUNTER1_KERNEL
mdefine_line|#define RM9K_COUNTER1_KERNEL&t;&t;(1ULL    &lt;&lt;  8)
DECL|macro|RM9K_COUNTER1_USER
mdefine_line|#define RM9K_COUNTER1_USER&t;&t;(1ULL    &lt;&lt;  9)
DECL|macro|RM9K_COUNTER1_ENABLE
mdefine_line|#define RM9K_COUNTER1_ENABLE&t;&t;(1ULL    &lt;&lt; 10)
DECL|macro|RM9K_COUNTER1_OVERFLOW
mdefine_line|#define RM9K_COUNTER1_OVERFLOW&t;&t;(1ULL    &lt;&lt; 15)
DECL|macro|RM9K_COUNTER2_EVENT
mdefine_line|#define RM9K_COUNTER2_EVENT(event)&t;((event) &lt;&lt; 16)
DECL|macro|RM9K_COUNTER2_SUPERVISOR
mdefine_line|#define RM9K_COUNTER2_SUPERVISOR&t;(1ULL    &lt;&lt; 23)
DECL|macro|RM9K_COUNTER2_KERNEL
mdefine_line|#define RM9K_COUNTER2_KERNEL&t;&t;(1ULL    &lt;&lt; 24)
DECL|macro|RM9K_COUNTER2_USER
mdefine_line|#define RM9K_COUNTER2_USER&t;&t;(1ULL    &lt;&lt; 25)
DECL|macro|RM9K_COUNTER2_ENABLE
mdefine_line|#define RM9K_COUNTER2_ENABLE&t;&t;(1ULL    &lt;&lt; 26)
DECL|macro|RM9K_COUNTER2_OVERFLOW
mdefine_line|#define RM9K_COUNTER2_OVERFLOW&t;&t;(1ULL    &lt;&lt; 31)
r_extern
r_int
r_int
id|rm9000_perfcount_irq
suffix:semicolon
DECL|struct|rm9k_register_config
r_static
r_struct
id|rm9k_register_config
(brace
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
DECL|member|reset_counter1
r_int
r_int
id|reset_counter1
suffix:semicolon
DECL|member|reset_counter2
r_int
r_int
id|reset_counter2
suffix:semicolon
DECL|variable|reg
)brace
id|reg
suffix:semicolon
multiline_comment|/* Compute all of the registers in preparation for enabling profiling.  */
DECL|function|rm9000_reg_setup
r_static
r_void
id|rm9000_reg_setup
c_func
(paren
r_struct
id|op_counter_config
op_star
id|ctr
)paren
(brace
r_int
r_int
id|control
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Compute the performance counter control word.  */
multiline_comment|/* For now count kernel and user mode */
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
id|control
op_or_assign
id|RM9K_COUNTER1_EVENT
c_func
(paren
id|ctr
(braket
l_int|0
)braket
dot
id|event
)paren
op_or
id|RM9K_COUNTER1_KERNEL
op_or
id|RM9K_COUNTER1_USER
op_or
id|RM9K_COUNTER1_ENABLE
suffix:semicolon
r_if
c_cond
(paren
id|ctr
(braket
l_int|1
)braket
dot
id|enabled
)paren
id|control
op_or_assign
id|RM9K_COUNTER2_EVENT
c_func
(paren
id|ctr
(braket
l_int|1
)braket
dot
id|event
)paren
op_or
id|RM9K_COUNTER2_KERNEL
op_or
id|RM9K_COUNTER2_USER
op_or
id|RM9K_COUNTER2_ENABLE
suffix:semicolon
id|reg.control
op_assign
id|control
suffix:semicolon
id|reg.reset_counter1
op_assign
l_int|0x80000000
op_minus
id|ctr
(braket
l_int|0
)braket
dot
id|count
suffix:semicolon
id|reg.reset_counter2
op_assign
l_int|0x80000000
op_minus
id|ctr
(braket
l_int|1
)braket
dot
id|count
suffix:semicolon
)brace
multiline_comment|/* Program all of the registers in preparation for enabling profiling.  */
DECL|function|rm9000_cpu_setup
r_static
r_void
id|rm9000_cpu_setup
(paren
r_void
op_star
id|args
)paren
(brace
r_uint64
id|perfcount
suffix:semicolon
id|perfcount
op_assign
(paren
(paren
r_uint64
)paren
id|reg.reset_counter2
op_lshift
l_int|32
)paren
op_or
id|reg.reset_counter1
suffix:semicolon
id|write_c0_perfcount
c_func
(paren
id|perfcount
)paren
suffix:semicolon
)brace
DECL|function|rm9000_cpu_start
r_static
r_void
id|rm9000_cpu_start
c_func
(paren
r_void
op_star
id|args
)paren
(brace
multiline_comment|/* Start all counters on current CPU */
id|write_c0_perfcontrol
c_func
(paren
id|reg.control
)paren
suffix:semicolon
)brace
DECL|function|rm9000_cpu_stop
r_static
r_void
id|rm9000_cpu_stop
c_func
(paren
r_void
op_star
id|args
)paren
(brace
multiline_comment|/* Stop all counters on current CPU */
id|write_c0_perfcontrol
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|rm9000_perfcount_handler
r_static
id|irqreturn_t
id|rm9000_perfcount_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|control
op_assign
id|read_c0_perfcontrol
c_func
(paren
)paren
suffix:semicolon
r_uint32
id|counter1
comma
id|counter2
suffix:semicolon
r_uint64
id|counters
suffix:semicolon
multiline_comment|/*&n;&t; * RM9000 combines two 32-bit performance counters into a single&n;&t; * 64-bit coprocessor zero register.  To avoid a race updating the&n;&t; * registers we need to stop the counters while we&squot;re messing with&n;&t; * them ...&n;&t; */
id|write_c0_perfcontrol
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|counters
op_assign
id|read_c0_perfcount
c_func
(paren
)paren
suffix:semicolon
id|counter1
op_assign
id|counters
suffix:semicolon
id|counter2
op_assign
id|counters
op_rshift
l_int|32
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|RM9K_COUNTER1_OVERFLOW
)paren
(brace
id|oprofile_add_sample
c_func
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|counter1
op_assign
id|reg.reset_counter1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|control
op_amp
id|RM9K_COUNTER2_OVERFLOW
)paren
(brace
id|oprofile_add_sample
c_func
(paren
id|regs
comma
l_int|1
)paren
suffix:semicolon
id|counter2
op_assign
id|reg.reset_counter2
suffix:semicolon
)brace
id|counters
op_assign
(paren
(paren
r_uint64
)paren
id|counter2
op_lshift
l_int|32
)paren
op_or
id|counter1
suffix:semicolon
id|write_c0_perfcount
c_func
(paren
id|counters
)paren
suffix:semicolon
id|write_c0_perfcontrol
c_func
(paren
id|reg.control
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|rm9000_init
r_static
r_int
id|rm9000_init
c_func
(paren
r_void
)paren
(brace
r_return
id|request_irq
c_func
(paren
id|rm9000_perfcount_irq
comma
id|rm9000_perfcount_handler
comma
l_int|0
comma
l_string|&quot;Perfcounter&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|rm9000_exit
r_static
r_void
id|rm9000_exit
c_func
(paren
r_void
)paren
(brace
id|free_irq
c_func
(paren
id|rm9000_perfcount_irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|op_model_rm9000
r_struct
id|op_mips_model
id|op_model_rm9000
op_assign
(brace
dot
id|reg_setup
op_assign
id|rm9000_reg_setup
comma
dot
id|cpu_setup
op_assign
id|rm9000_cpu_setup
comma
dot
id|init
op_assign
id|rm9000_init
comma
dot
m_exit
op_assign
id|rm9000_exit
comma
dot
id|cpu_start
op_assign
id|rm9000_cpu_start
comma
dot
id|cpu_stop
op_assign
id|rm9000_cpu_stop
comma
dot
id|cpu_type
op_assign
l_string|&quot;mips/rm9000&quot;
comma
dot
id|num_counters
op_assign
l_int|2
)brace
suffix:semicolon
eof
