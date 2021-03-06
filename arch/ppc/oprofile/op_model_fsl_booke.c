multiline_comment|/*&n; * oprofile/op_model_e500.c&n; *&n; * Freescale Book-E oprofile support, based on ppc64 oprofile support&n; * Copyright (C) 2004 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * Copyright (c) 2004 Freescale Semiconductor, Inc&n; *&n; * Author: Andy Fleming&n; * Maintainer: Kumar Gala &lt;Kumar.Gala@freescale.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/reg_booke.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/perfmon.h&gt;
macro_line|#include &quot;op_impl.h&quot;
DECL|variable|reset_value
r_static
r_int
r_int
id|reset_value
(braket
id|OP_MAX_COUNTER
)braket
suffix:semicolon
DECL|variable|num_counters
r_static
r_int
id|num_counters
suffix:semicolon
DECL|variable|oprofile_running
r_static
r_int
id|oprofile_running
suffix:semicolon
DECL|function|ctr_read
r_static
r_inline
r_int
r_int
id|ctr_read
c_func
(paren
r_int
r_int
id|i
)paren
(brace
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
id|mfpmr
c_func
(paren
id|PMRN_PMC0
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
r_return
id|mfpmr
c_func
(paren
id|PMRN_PMC1
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
id|mfpmr
c_func
(paren
id|PMRN_PMC2
)paren
suffix:semicolon
r_case
l_int|3
suffix:colon
r_return
id|mfpmr
c_func
(paren
id|PMRN_PMC3
)paren
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|ctr_write
r_static
r_inline
r_void
id|ctr_write
c_func
(paren
r_int
r_int
id|i
comma
r_int
r_int
id|val
)paren
(brace
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
id|mtpmr
c_func
(paren
id|PMRN_PMC0
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|mtpmr
c_func
(paren
id|PMRN_PMC1
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|mtpmr
c_func
(paren
id|PMRN_PMC2
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|mtpmr
c_func
(paren
id|PMRN_PMC3
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
DECL|function|fsl_booke_reg_setup
r_static
r_void
id|fsl_booke_reg_setup
c_func
(paren
r_struct
id|op_counter_config
op_star
id|ctr
comma
r_struct
id|op_system_config
op_star
id|sys
comma
r_int
id|num_ctrs
)paren
(brace
r_int
id|i
suffix:semicolon
id|num_counters
op_assign
id|num_ctrs
suffix:semicolon
multiline_comment|/* freeze all counters */
id|pmc_stop_ctrs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Our counters count up, and &quot;count&quot; refers to&n;&t; * how much before the next interrupt, and we interrupt&n;&t; * on overflow.  So we calculate the starting value&n;&t; * which will give us &quot;count&quot; until overflow.&n;&t; * Then we set the events on the enabled counters */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
id|reset_value
(braket
id|i
)braket
op_assign
l_int|0x80000000UL
op_minus
id|ctr
(braket
id|i
)braket
dot
id|count
suffix:semicolon
id|init_pmc_stop
c_func
(paren
id|i
)paren
suffix:semicolon
id|set_pmc_event
c_func
(paren
id|i
comma
id|ctr
(braket
id|i
)braket
dot
id|event
)paren
suffix:semicolon
id|set_pmc_user_kernel
c_func
(paren
id|i
comma
id|ctr
(braket
id|i
)braket
dot
id|user
comma
id|ctr
(braket
id|i
)braket
dot
id|kernel
)paren
suffix:semicolon
)brace
)brace
DECL|function|fsl_booke_start
r_static
r_void
id|fsl_booke_start
c_func
(paren
r_struct
id|op_counter_config
op_star
id|ctr
)paren
(brace
r_int
id|i
suffix:semicolon
id|mtmsr
c_func
(paren
id|mfmsr
c_func
(paren
)paren
op_or
id|MSR_PMM
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|ctr
(braket
id|i
)braket
dot
id|enabled
)paren
(brace
id|ctr_write
c_func
(paren
id|i
comma
id|reset_value
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* Set Each enabled counterd to only&n;&t;&t;&t; * count when the Mark bit is not set */
id|set_pmc_marked
c_func
(paren
id|i
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
id|pmc_start_ctr
c_func
(paren
id|i
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|ctr_write
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set the ctr to be stopped */
id|pmc_start_ctr
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Clear the freeze bit, and enable the interrupt.&n;&t; * The counters won&squot;t actually start until the rfi clears&n;&t; * the PMM bit */
id|pmc_start_ctrs
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|oprofile_running
op_assign
l_int|1
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;start on cpu %d, pmgc0 %x&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mfpmr
c_func
(paren
id|PMRN_PMGC0
)paren
)paren
suffix:semicolon
)brace
DECL|function|fsl_booke_stop
r_static
r_void
id|fsl_booke_stop
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* freeze counters */
id|pmc_stop_ctrs
c_func
(paren
)paren
suffix:semicolon
id|oprofile_running
op_assign
l_int|0
suffix:semicolon
id|pr_debug
c_func
(paren
l_string|&quot;stop on cpu %d, pmgc0 %x&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|mfpmr
c_func
(paren
id|PMRN_PMGC0
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|fsl_booke_handle_interrupt
r_static
r_void
id|fsl_booke_handle_interrupt
c_func
(paren
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
r_int
r_int
id|pc
suffix:semicolon
r_int
id|is_kernel
suffix:semicolon
r_int
id|val
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* set the PMM bit (see comment below) */
id|mtmsr
c_func
(paren
id|mfmsr
c_func
(paren
)paren
op_or
id|MSR_PMM
)paren
suffix:semicolon
id|pc
op_assign
id|regs-&gt;nip
suffix:semicolon
id|is_kernel
op_assign
(paren
id|pc
op_ge
id|KERNELBASE
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
id|num_counters
suffix:semicolon
op_increment
id|i
)paren
(brace
id|val
op_assign
id|ctr_read
c_func
(paren
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|oprofile_running
op_logical_and
id|ctr
(braket
id|i
)braket
dot
id|enabled
)paren
(brace
id|oprofile_add_pc
c_func
(paren
id|pc
comma
id|is_kernel
comma
id|i
)paren
suffix:semicolon
id|ctr_write
c_func
(paren
id|i
comma
id|reset_value
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|ctr_write
c_func
(paren
id|i
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* The freeze bit was set by the interrupt. */
multiline_comment|/* Clear the freeze bit, and reenable the interrupt.&n;&t; * The counters won&squot;t actually start until the rfi clears&n;&t; * the PMM bit */
id|pmc_start_ctrs
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|op_model_fsl_booke
r_struct
id|op_ppc32_model
id|op_model_fsl_booke
op_assign
(brace
dot
id|reg_setup
op_assign
id|fsl_booke_reg_setup
comma
dot
id|start
op_assign
id|fsl_booke_start
comma
dot
id|stop
op_assign
id|fsl_booke_stop
comma
dot
id|handle_interrupt
op_assign
id|fsl_booke_handle_interrupt
comma
)brace
suffix:semicolon
eof
