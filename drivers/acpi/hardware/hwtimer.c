multiline_comment|/******************************************************************************&n; *&n; * Name: hwtimer.c - ACPI Power Management Timer Interface&n; *              $Revision: 10 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;achware.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_HARDWARE
id|MODULE_NAME
(paren
l_string|&quot;hwtimer&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_timer_resolution&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      Number of bits of resolution in the PM Timer (24 or 32).&n; *&n; * DESCRIPTION: Obtains resolution of the ACPI PM Timer.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_get_timer_resolution
id|acpi_get_timer_resolution
(paren
id|u32
op_star
id|resolution
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
multiline_comment|/* Ensure that ACPI has been initialized */
id|ACPI_IS_INITIALIZATION_COMPLETE
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|resolution
)paren
(brace
r_return
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
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_timer&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      Current value of the ACPI PM Timer (in ticks).&n; *&n; * DESCRIPTION: Obtains current value of ACPI PM Timer.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_get_timer
id|acpi_get_timer
(paren
id|u32
op_star
id|ticks
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
multiline_comment|/* Ensure that ACPI has been initialized */
id|ACPI_IS_INITIALIZATION_COMPLETE
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ticks
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
op_star
id|ticks
op_assign
id|acpi_os_in32
(paren
(paren
id|ACPI_IO_ADDRESS
)paren
id|ACPI_GET_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xpm_tmr_blk.address
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_timer_duration&n; *&n; * PARAMETERS:  Start_ticks&n; *              End_ticks&n; *              Time_elapsed&n; *&n; * RETURN:      Time_elapsed&n; *&n; * DESCRIPTION: Computes the time elapsed (in microseconds) between two&n; *              PM Timer time stamps, taking into account the possibility of&n; *              rollovers, the timer resolution, and timer frequency.&n; *&n; *              The PM Timer&squot;s clock ticks at roughly 3.6 times per&n; *              _microsecond_, and its clock continues through Cx state&n; *              transitions (unlike many CPU timestamp counters) -- making it&n; *              a versatile and accurate timer.&n; *&n; *              Note that this function accomodates only a single timer&n; *              rollover.  Thus for 24-bit timers, this function should only&n; *              be used for calculating durations less than ~4.6 seconds&n; *              (~20 hours for 32-bit timers).&n; *&n; ******************************************************************************/
id|ACPI_STATUS
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
id|u32
id|seconds
op_assign
l_int|0
suffix:semicolon
id|u32
id|milliseconds
op_assign
l_int|0
suffix:semicolon
id|u32
id|microseconds
op_assign
l_int|0
suffix:semicolon
id|u32
id|remainder
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|time_elapsed
)paren
(brace
r_return
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
multiline_comment|/* 24-bit Timer */
r_if
c_cond
(paren
l_int|0
op_eq
id|acpi_gbl_FADT-&gt;tmr_val_ext
)paren
(brace
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
multiline_comment|/* 32-bit Timer */
r_else
(brace
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
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Compute Duration:&n;&t; * -----------------&n;&t; * Since certain compilers (gcc/Linux, argh!) don&squot;t support 64-bit&n;&t; * divides in kernel-space we have to do some trickery to preserve&n;&t; * accuracy while using 32-bit math.&n;&t; *&n;&t; * TBD: Change to use 64-bit math when supported.&n;&t; *&n;&t; * The process is as follows:&n;&t; *  1. Compute the number of seconds by dividing Delta Ticks by&n;&t; *     the timer frequency.&n;&t; *  2. Compute the number of milliseconds in the remainder from step #1&n;&t; *     by multiplying by 1000 and then dividing by the timer frequency.&n;&t; *  3. Compute the number of microseconds in the remainder from step #2&n;&t; *     by multiplying by 1000 and then dividing by the timer frequency.&n;&t; *  4. Add the results from steps 1, 2, and 3 to get the total duration.&n;&t; *&n;&t; * Example: The time elapsed for Delta_ticks = 0xFFFFFFFF should be&n;&t; *          1199864031 microseconds.  This is computed as follows:&n;&t; *          Step #1: Seconds = 1199; Remainder = 3092840&n;&t; *          Step #2: Milliseconds = 864; Remainder = 113120&n;&t; *          Step #3: Microseconds = 31; Remainder = &lt;don&squot;t care!&gt;&n;&t; */
multiline_comment|/* Step #1 */
id|seconds
op_assign
id|delta_ticks
op_div
id|PM_TIMER_FREQUENCY
suffix:semicolon
id|remainder
op_assign
id|delta_ticks
op_mod
id|PM_TIMER_FREQUENCY
suffix:semicolon
multiline_comment|/* Step #2 */
id|milliseconds
op_assign
(paren
id|remainder
op_star
l_int|1000
)paren
op_div
id|PM_TIMER_FREQUENCY
suffix:semicolon
id|remainder
op_assign
(paren
id|remainder
op_star
l_int|1000
)paren
op_mod
id|PM_TIMER_FREQUENCY
suffix:semicolon
multiline_comment|/* Step #3 */
id|microseconds
op_assign
(paren
id|remainder
op_star
l_int|1000
)paren
op_div
id|PM_TIMER_FREQUENCY
suffix:semicolon
multiline_comment|/* Step #4 */
op_star
id|time_elapsed
op_assign
id|seconds
op_star
l_int|1000000
suffix:semicolon
op_star
id|time_elapsed
op_add_assign
id|milliseconds
op_star
l_int|1000
suffix:semicolon
op_star
id|time_elapsed
op_add_assign
id|microseconds
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
