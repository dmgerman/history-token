multiline_comment|/******************************************************************************&n; *&n; * Name: hwsleep.c - ACPI Hardware Sleep/Wake Interface&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_HARDWARE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;hwsleep&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_set_firmware_waking_vector&n; *&n; * PARAMETERS:  physical_address    - Physical address of ACPI real mode&n; *                                    entry point.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: access function for d_firmware_waking_vector field in FACS&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_set_firmware_waking_vector
id|acpi_set_firmware_waking_vector
(paren
id|acpi_physical_address
id|physical_address
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_set_firmware_waking_vector&quot;
)paren
suffix:semicolon
multiline_comment|/* Set the vector */
r_if
c_cond
(paren
id|acpi_gbl_common_fACS.vector_width
op_eq
l_int|32
)paren
(brace
op_star
(paren
id|ACPI_CAST_PTR
(paren
id|u32
comma
id|acpi_gbl_common_fACS.firmware_waking_vector
)paren
)paren
op_assign
(paren
id|u32
)paren
id|physical_address
suffix:semicolon
)brace
r_else
(brace
op_star
id|acpi_gbl_common_fACS.firmware_waking_vector
op_assign
id|physical_address
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_get_firmware_waking_vector&n; *&n; * PARAMETERS:  *physical_address   - Output buffer where contents of&n; *                                    the firmware_waking_vector field of&n; *                                    the FACS will be stored.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Access function for firmware_waking_vector field in FACS&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_firmware_waking_vector
id|acpi_get_firmware_waking_vector
(paren
id|acpi_physical_address
op_star
id|physical_address
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_firmware_waking_vector&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|physical_address
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the vector */
r_if
c_cond
(paren
id|acpi_gbl_common_fACS.vector_width
op_eq
l_int|32
)paren
(brace
op_star
id|physical_address
op_assign
(paren
id|acpi_physical_address
)paren
op_star
(paren
id|ACPI_CAST_PTR
(paren
id|u32
comma
id|acpi_gbl_common_fACS.firmware_waking_vector
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|physical_address
op_assign
op_star
id|acpi_gbl_common_fACS.firmware_waking_vector
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_enter_sleep_state_prep&n; *&n; * PARAMETERS:  sleep_state         - Which sleep state to enter&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Prepare to enter a system sleep state (see ACPI 2.0 spec p 231)&n; *              This function must execute with interrupts enabled.&n; *              We break sleeping into 2 stages so that OSPM can handle&n; *              various OS-specific tasks between the two steps.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_enter_sleep_state_prep
id|acpi_enter_sleep_state_prep
(paren
id|u8
id|sleep_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_object_list
id|arg_list
suffix:semicolon
r_union
id|acpi_object
id|arg
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_enter_sleep_state_prep&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * _PSW methods could be run here to enable wake-on keyboard, LAN, etc.&n;&t; */
id|status
op_assign
id|acpi_get_sleep_type_data
(paren
id|sleep_state
comma
op_amp
id|acpi_gbl_sleep_type_a
comma
op_amp
id|acpi_gbl_sleep_type_b
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Setup parameter object */
id|arg_list.count
op_assign
l_int|1
suffix:semicolon
id|arg_list.pointer
op_assign
op_amp
id|arg
suffix:semicolon
id|arg.type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
id|arg.integer.value
op_assign
id|sleep_state
suffix:semicolon
multiline_comment|/* Run the _PTS and _GTS methods */
id|status
op_assign
id|acpi_evaluate_object
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_PTS&quot;
comma
op_amp
id|arg_list
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_and
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_evaluate_object
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_GTS&quot;
comma
op_amp
id|arg_list
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_and
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the system indicators to show the desired sleep state. */
id|status
op_assign
id|acpi_evaluate_object
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_SI._SST&quot;
comma
op_amp
id|arg_list
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_and
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Method _SST failed, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_enter_sleep_state&n; *&n; * PARAMETERS:  sleep_state         - Which sleep state to enter&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Enter a system sleep state (see ACPI 2.0 spec p 231)&n; *              THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_enter_sleep_state
id|acpi_enter_sleep_state
(paren
id|u8
id|sleep_state
)paren
(brace
id|u32
id|PM1Acontrol
suffix:semicolon
id|u32
id|PM1Bcontrol
suffix:semicolon
r_struct
id|acpi_bit_register_info
op_star
id|sleep_type_reg_info
suffix:semicolon
r_struct
id|acpi_bit_register_info
op_star
id|sleep_enable_reg_info
suffix:semicolon
id|u32
id|in_value
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_enter_sleep_state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|acpi_gbl_sleep_type_a
OG
id|ACPI_SLEEP_TYPE_MAX
)paren
op_logical_or
(paren
id|acpi_gbl_sleep_type_b
OG
id|ACPI_SLEEP_TYPE_MAX
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Sleep values out of range: A=%X B=%X&bslash;n&quot;
comma
id|acpi_gbl_sleep_type_a
comma
id|acpi_gbl_sleep_type_b
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_VALUE
)paren
suffix:semicolon
)brace
id|sleep_type_reg_info
op_assign
id|acpi_hw_get_bit_register_info
(paren
id|ACPI_BITREG_SLEEP_TYPE_A
)paren
suffix:semicolon
id|sleep_enable_reg_info
op_assign
id|acpi_hw_get_bit_register_info
(paren
id|ACPI_BITREG_SLEEP_ENABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sleep_state
op_ne
id|ACPI_STATE_S5
)paren
(brace
multiline_comment|/* Clear wake status */
id|status
op_assign
id|acpi_set_register
(paren
id|ACPI_BITREG_WAKE_STATUS
comma
l_int|1
comma
id|ACPI_MTX_DO_NOT_LOCK
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_clear_acpi_status
(paren
id|ACPI_MTX_DO_NOT_LOCK
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable BM arbitration */
id|status
op_assign
id|acpi_set_register
(paren
id|ACPI_BITREG_ARB_DISABLE
comma
l_int|1
comma
id|ACPI_MTX_DO_NOT_LOCK
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
id|status
op_assign
id|acpi_hw_disable_non_wakeup_gpes
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Get current value of PM1A control */
id|status
op_assign
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_CONTROL
comma
op_amp
id|PM1Acontrol
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INIT
comma
l_string|&quot;Entering sleep state [S%d]&bslash;n&quot;
comma
id|sleep_state
)paren
)paren
suffix:semicolon
multiline_comment|/* Clear SLP_EN and SLP_TYP fields */
id|PM1Acontrol
op_and_assign
op_complement
(paren
id|sleep_type_reg_info-&gt;access_bit_mask
op_or
id|sleep_enable_reg_info-&gt;access_bit_mask
)paren
suffix:semicolon
id|PM1Bcontrol
op_assign
id|PM1Acontrol
suffix:semicolon
multiline_comment|/* Insert SLP_TYP bits */
id|PM1Acontrol
op_or_assign
(paren
id|acpi_gbl_sleep_type_a
op_lshift
id|sleep_type_reg_info-&gt;bit_position
)paren
suffix:semicolon
id|PM1Bcontrol
op_or_assign
(paren
id|acpi_gbl_sleep_type_b
op_lshift
id|sleep_type_reg_info-&gt;bit_position
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We split the writes of SLP_TYP and SLP_EN to workaround&n;&t; * poorly implemented hardware.&n;&t; */
multiline_comment|/* Write #1: fill in SLP_TYP data */
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1A_CONTROL
comma
id|PM1Acontrol
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1B_CONTROL
comma
id|PM1Bcontrol
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Insert SLP_ENABLE bit */
id|PM1Acontrol
op_or_assign
id|sleep_enable_reg_info-&gt;access_bit_mask
suffix:semicolon
id|PM1Bcontrol
op_or_assign
id|sleep_enable_reg_info-&gt;access_bit_mask
suffix:semicolon
multiline_comment|/* Write #2: SLP_TYP + SLP_EN */
id|ACPI_FLUSH_CPU_CACHE
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1A_CONTROL
comma
id|PM1Acontrol
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1B_CONTROL
comma
id|PM1Bcontrol
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sleep_state
OG
id|ACPI_STATE_S3
)paren
(brace
multiline_comment|/*&n;&t;&t; * We wanted to sleep &gt; S3, but it didn&squot;t happen (by virtue of the fact that&n;&t;&t; * we are still executing!)&n;&t;&t; *&n;&t;&t; * Wait ten seconds, then try again. This is to get S4/S5 to work on all machines.&n;&t;&t; *&n;&t;&t; * We wait so long to allow chipsets that poll this reg very slowly to&n;&t;&t; * still read the right value. Ideally, this block would go&n;&t;&t; * away entirely.&n;&t;&t; */
id|acpi_os_stall
(paren
l_int|10000000
)paren
suffix:semicolon
id|status
op_assign
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_CONTROL
comma
id|sleep_enable_reg_info-&gt;access_bit_mask
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Wait until we enter sleep state */
r_do
(brace
id|status
op_assign
id|acpi_get_register
(paren
id|ACPI_BITREG_WAKE_STATUS
comma
op_amp
id|in_value
comma
id|ACPI_MTX_DO_NOT_LOCK
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Spin until we wake */
)brace
r_while
c_loop
(paren
op_logical_neg
id|in_value
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_enter_sleep_state_s4bios&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Perform a S4 bios request.&n; *              THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_enter_sleep_state_s4bios
id|acpi_enter_sleep_state_s4bios
(paren
r_void
)paren
(brace
id|u32
id|in_value
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_enter_sleep_state_s4bios&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_set_register
(paren
id|ACPI_BITREG_WAKE_STATUS
comma
l_int|1
comma
id|ACPI_MTX_DO_NOT_LOCK
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_clear_acpi_status
(paren
id|ACPI_MTX_DO_NOT_LOCK
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_hw_disable_non_wakeup_gpes
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|ACPI_FLUSH_CPU_CACHE
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_os_write_port
(paren
id|acpi_gbl_FADT-&gt;smi_cmd
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;S4bios_req
comma
l_int|8
)paren
suffix:semicolon
r_do
(brace
id|acpi_os_stall
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|status
op_assign
id|acpi_get_register
(paren
id|ACPI_BITREG_WAKE_STATUS
comma
op_amp
id|in_value
comma
id|ACPI_MTX_DO_NOT_LOCK
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|in_value
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_leave_sleep_state&n; *&n; * PARAMETERS:  sleep_state         - Which sleep state we just exited&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Perform OS-independent ACPI cleanup after a sleep&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_leave_sleep_state
id|acpi_leave_sleep_state
(paren
id|u8
id|sleep_state
)paren
(brace
r_struct
id|acpi_object_list
id|arg_list
suffix:semicolon
r_union
id|acpi_object
id|arg
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_bit_register_info
op_star
id|sleep_type_reg_info
suffix:semicolon
r_struct
id|acpi_bit_register_info
op_star
id|sleep_enable_reg_info
suffix:semicolon
id|u32
id|PM1Acontrol
suffix:semicolon
id|u32
id|PM1Bcontrol
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_leave_sleep_state&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set SLP_TYPE and SLP_EN to state S0.&n;&t; * This is unclear from the ACPI Spec, but it is required&n;&t; * by some machines.&n;&t; */
id|status
op_assign
id|acpi_get_sleep_type_data
(paren
id|ACPI_STATE_S0
comma
op_amp
id|acpi_gbl_sleep_type_a
comma
op_amp
id|acpi_gbl_sleep_type_b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
id|sleep_type_reg_info
op_assign
id|acpi_hw_get_bit_register_info
(paren
id|ACPI_BITREG_SLEEP_TYPE_A
)paren
suffix:semicolon
id|sleep_enable_reg_info
op_assign
id|acpi_hw_get_bit_register_info
(paren
id|ACPI_BITREG_SLEEP_ENABLE
)paren
suffix:semicolon
multiline_comment|/* Get current value of PM1A control */
id|status
op_assign
id|acpi_hw_register_read
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1_CONTROL
comma
op_amp
id|PM1Acontrol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Clear SLP_EN and SLP_TYP fields */
id|PM1Acontrol
op_and_assign
op_complement
(paren
id|sleep_type_reg_info-&gt;access_bit_mask
op_or
id|sleep_enable_reg_info-&gt;access_bit_mask
)paren
suffix:semicolon
id|PM1Bcontrol
op_assign
id|PM1Acontrol
suffix:semicolon
multiline_comment|/* Insert SLP_TYP bits */
id|PM1Acontrol
op_or_assign
(paren
id|acpi_gbl_sleep_type_a
op_lshift
id|sleep_type_reg_info-&gt;bit_position
)paren
suffix:semicolon
id|PM1Bcontrol
op_or_assign
(paren
id|acpi_gbl_sleep_type_b
op_lshift
id|sleep_type_reg_info-&gt;bit_position
)paren
suffix:semicolon
multiline_comment|/* Just ignore any errors */
(paren
r_void
)paren
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1A_CONTROL
comma
id|PM1Acontrol
)paren
suffix:semicolon
(paren
r_void
)paren
id|acpi_hw_register_write
(paren
id|ACPI_MTX_DO_NOT_LOCK
comma
id|ACPI_REGISTER_PM1B_CONTROL
comma
id|PM1Bcontrol
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Ensure enter_sleep_state_prep -&gt; enter_sleep_state ordering */
id|acpi_gbl_sleep_type_a
op_assign
id|ACPI_SLEEP_TYPE_INVALID
suffix:semicolon
multiline_comment|/* Setup parameter object */
id|arg_list.count
op_assign
l_int|1
suffix:semicolon
id|arg_list.pointer
op_assign
op_amp
id|arg
suffix:semicolon
id|arg.type
op_assign
id|ACPI_TYPE_INTEGER
suffix:semicolon
multiline_comment|/* Ignore any errors from these methods */
id|arg.integer.value
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_SI._SST&quot;
comma
op_amp
id|arg_list
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_and
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Method _SST failed, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|arg.integer.value
op_assign
id|sleep_state
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_object
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_BFS&quot;
comma
op_amp
id|arg_list
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_and
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Method _BFS failed, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_evaluate_object
(paren
l_int|NULL
comma
l_string|&quot;&bslash;&bslash;_WAK&quot;
comma
op_amp
id|arg_list
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
op_logical_and
id|status
op_ne
id|AE_NOT_FOUND
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Method _WAK failed, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* _WAK returns stuff - do we want to look at it? */
id|status
op_assign
id|acpi_hw_enable_non_wakeup_gpes
(paren
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable BM arbitration */
id|status
op_assign
id|acpi_set_register
(paren
id|ACPI_BITREG_ARB_DISABLE
comma
l_int|0
comma
id|ACPI_MTX_LOCK
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
