multiline_comment|/******************************************************************************&n; *&n; * Name: hwtimer.c - ACPI Power Management Timer Interface&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_HARDWARE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;hwtimer&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_get_timer_resolution&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      Number of bits of resolution in the PM Timer (24 or 32).&n; *&n; * DESCRIPTION: Obtains resolution of the ACPI PM Timer.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_timer_resolution
id|acpi_get_timer_resolution
(paren
id|u32
op_star
id|resolution
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_timer_resolution&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resolution
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|acpi_gbl_FADT-&gt;tmr_val_ext
)paren
(brace
op_star
id|resolution
op_assign
l_int|24
suffix:semicolon
)brace
r_else
(brace
op_star
id|resolution
op_assign
l_int|32
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_get_timer&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      Current value of the ACPI PM Timer (in ticks).&n; *&n; * DESCRIPTION: Obtains current value of ACPI PM Timer.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_timer
id|acpi_get_timer
(paren
id|u32
op_star
id|ticks
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_timer&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ticks
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_low_level_read
(paren
l_int|32
comma
id|ticks
comma
op_amp
id|acpi_gbl_FADT-&gt;xpm_tmr_blk
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_get_timer_duration&n; *&n; * PARAMETERS:  start_ticks&n; *              end_ticks&n; *              time_elapsed&n; *&n; * RETURN:      time_elapsed&n; *&n; * DESCRIPTION: Computes the time elapsed (in microseconds) between two&n; *              PM Timer time stamps, taking into account the possibility of&n; *              rollovers, the timer resolution, and timer frequency.&n; *&n; *              The PM Timer&squot;s clock ticks at roughly 3.6 times per&n; *              _microsecond_, and its clock continues through Cx state&n; *              transitions (unlike many CPU timestamp counters) -- making it&n; *              a versatile and accurate timer.&n; *&n; *              Note that this function accommodates only a single timer&n; *              rollover.  Thus for 24-bit timers, this function should only&n; *              be used for calculating durations less than ~4.6 seconds&n; *              (~20 minutes for 32-bit timers) -- calculations below&n; *&n; *              2**24 Ticks / 3,600,000 Ticks/Sec = 4.66 sec&n; *              2**32 Ticks / 3,600,000 Ticks/Sec = 1193 sec or 19.88 minutes&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_timer_duration
id|acpi_get_timer_duration
(paren
id|u32
id|start_ticks
comma
id|u32
id|end_ticks
comma
id|u32
op_star
id|time_elapsed
)paren
(brace
id|u32
id|delta_ticks
op_assign
l_int|0
suffix:semicolon
r_union
id|uint64_overlay
id|normalized_ticks
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_integer
id|out_quotient
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_timer_duration&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|time_elapsed
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Compute Tick Delta:&n;&t; * -------------------&n;&t; * Handle (max one) timer rollovers on 24- versus 32-bit timers.&n;&t; */
r_if
c_cond
(paren
id|start_ticks
OL
id|end_ticks
)paren
(brace
id|delta_ticks
op_assign
id|end_ticks
op_minus
id|start_ticks
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|start_ticks
OG
id|end_ticks
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
id|acpi_gbl_FADT-&gt;tmr_val_ext
)paren
(brace
multiline_comment|/* 24-bit Timer */
id|delta_ticks
op_assign
(paren
(paren
(paren
l_int|0x00FFFFFF
op_minus
id|start_ticks
)paren
op_plus
id|end_ticks
)paren
op_amp
l_int|0x00FFFFFF
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 32-bit Timer */
id|delta_ticks
op_assign
(paren
l_int|0xFFFFFFFF
op_minus
id|start_ticks
)paren
op_plus
id|end_ticks
suffix:semicolon
)brace
)brace
r_else
(brace
op_star
id|time_elapsed
op_assign
l_int|0
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Compute Duration:&n;&t; * -----------------&n;&t; *&n;&t; * Requires a 64-bit divide:&n;&t; *&n;&t; * time_elapsed = (delta_ticks * 1000000) / PM_TIMER_FREQUENCY;&n;&t; */
id|normalized_ticks.full
op_assign
(paren
(paren
id|u64
)paren
id|delta_ticks
)paren
op_star
l_int|1000000
suffix:semicolon
id|status
op_assign
id|acpi_ut_short_divide
(paren
op_amp
id|normalized_ticks.full
comma
id|PM_TIMER_FREQUENCY
comma
op_amp
id|out_quotient
comma
l_int|NULL
)paren
suffix:semicolon
op_star
id|time_elapsed
op_assign
(paren
id|u32
)paren
id|out_quotient
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
