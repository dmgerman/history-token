multiline_comment|/******************************************************************************&n; *&n; * Module Name: utinit - Common ACPI subsystem initialization&n; *              $Revision: 102 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acdispat.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|MODULE_NAME
(paren
l_string|&quot;utinit&quot;
)paren
DECL|macro|ACPI_OFFSET
mdefine_line|#define ACPI_OFFSET(d,o)    ((u32) &amp;(((d *)0)-&gt;o))
DECL|macro|ACPI_FADT_OFFSET
mdefine_line|#define ACPI_FADT_OFFSET(o) ACPI_OFFSET (FADT_DESCRIPTOR, o)
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_fadt_register_error&n; *&n; * PARAMETERS:  *Register_name          - Pointer to string identifying register&n; *              Value                   - Actual register contents value&n; *              Acpi_test_spec_section  - TDS section containing assertion&n; *              Acpi_assertion          - Assertion number being tested&n; *&n; * RETURN:      AE_BAD_VALUE&n; *&n; * DESCRIPTION: Display failure message and link failure to TDS assertion&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ut_fadt_register_error
id|acpi_ut_fadt_register_error
(paren
id|NATIVE_CHAR
op_star
id|register_name
comma
id|u32
id|value
comma
id|u32
id|offset
)paren
(brace
id|REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid FADT value %s=%lX at offset %lX FADT=%p&bslash;n&quot;
comma
id|register_name
comma
id|value
comma
id|offset
comma
id|acpi_gbl_FADT
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_validate_fadt&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Validate various ACPI registers in the FADT&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_validate_fadt
id|acpi_ut_validate_fadt
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
multiline_comment|/*&n;&t; * Verify Fixed ACPI Description Table fields,&n;&t; * but don&squot;t abort on any problems, just display error&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;pm1_evt_len
OL
l_int|4
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;PM1_EVT_LEN&quot;
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;pm1_evt_len
comma
id|ACPI_FADT_OFFSET
(paren
id|pm1_evt_len
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_FADT-&gt;pm1_cnt_len
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;PM1_CNT_LEN&quot;
comma
l_int|0
comma
id|ACPI_FADT_OFFSET
(paren
id|pm1_cnt_len
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ACPI_VALID_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xpm1a_evt_blk.address
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;X_PM1a_EVT_BLK&quot;
comma
l_int|0
comma
id|ACPI_FADT_OFFSET
(paren
id|Xpm1a_evt_blk.address
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ACPI_VALID_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xpm1a_cnt_blk.address
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;X_PM1a_CNT_BLK&quot;
comma
l_int|0
comma
id|ACPI_FADT_OFFSET
(paren
id|Xpm1a_cnt_blk.address
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ACPI_VALID_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xpm_tmr_blk.address
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;X_PM_TMR_BLK&quot;
comma
l_int|0
comma
id|ACPI_FADT_OFFSET
(paren
id|Xpm_tmr_blk.address
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ACPI_VALID_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xpm2_cnt_blk.address
)paren
op_logical_and
op_logical_neg
id|acpi_gbl_FADT-&gt;pm2_cnt_len
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;PM2_CNT_LEN&quot;
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;pm2_cnt_len
comma
id|ACPI_FADT_OFFSET
(paren
id|pm2_cnt_len
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;pm_tm_len
OL
l_int|4
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;PM_TM_LEN&quot;
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;pm_tm_len
comma
id|ACPI_FADT_OFFSET
(paren
id|pm_tm_len
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* length of GPE blocks must be a multiple of 2 */
r_if
c_cond
(paren
id|ACPI_VALID_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xgpe0blk.address
)paren
op_logical_and
(paren
id|acpi_gbl_FADT-&gt;gpe0blk_len
op_amp
l_int|1
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;(x)GPE0_BLK_LEN&quot;
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;gpe0blk_len
comma
id|ACPI_FADT_OFFSET
(paren
id|gpe0blk_len
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_VALID_ADDRESS
(paren
id|acpi_gbl_FADT-&gt;Xgpe1_blk.address
)paren
op_logical_and
(paren
id|acpi_gbl_FADT-&gt;gpe1_blk_len
op_amp
l_int|1
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_fadt_register_error
(paren
l_string|&quot;(x)GPE1_BLK_LEN&quot;
comma
(paren
id|u32
)paren
id|acpi_gbl_FADT-&gt;gpe1_blk_len
comma
id|ACPI_FADT_OFFSET
(paren
id|gpe1_blk_len
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_terminate&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      none&n; *&n; * DESCRIPTION: free memory allocated for table storage.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_terminate
id|acpi_ut_terminate
(paren
r_void
)paren
(brace
id|FUNCTION_TRACE
(paren
l_string|&quot;Ut_terminate&quot;
)paren
suffix:semicolon
multiline_comment|/* Free global tables, etc. */
r_if
c_cond
(paren
id|acpi_gbl_gpe0enable_register_save
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|acpi_gbl_gpe0enable_register_save
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_gpe1_enable_register_save
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|acpi_gbl_gpe1_enable_register_save
)paren
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ut_subsystem_shutdown&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      none&n; *&n; * DESCRIPTION: Shutdown the various subsystems.  Don&squot;t delete the mutex&n; *              objects here -- because the AML debugger may be still running.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_subsystem_shutdown
id|acpi_ut_subsystem_shutdown
(paren
r_void
)paren
(brace
id|FUNCTION_TRACE
(paren
l_string|&quot;Ut_subsystem_shutdown&quot;
)paren
suffix:semicolon
multiline_comment|/* Just exit if subsystem is already shutdown */
r_if
c_cond
(paren
id|acpi_gbl_shutdown
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;ACPI Subsystem is already terminated&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Subsystem appears active, go ahead and shut it down */
id|acpi_gbl_shutdown
op_assign
id|TRUE
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Shutting down ACPI Subsystem...&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Close the Namespace */
id|acpi_ns_terminate
(paren
)paren
suffix:semicolon
multiline_comment|/* Close the Acpi_event Handling */
id|acpi_ev_terminate
(paren
)paren
suffix:semicolon
multiline_comment|/* Close the globals */
id|acpi_ut_terminate
(paren
)paren
suffix:semicolon
multiline_comment|/* Flush the local cache(s) */
id|acpi_ut_delete_generic_state_cache
(paren
)paren
suffix:semicolon
id|acpi_ut_delete_object_cache
(paren
)paren
suffix:semicolon
id|acpi_ds_delete_walk_state_cache
(paren
)paren
suffix:semicolon
multiline_comment|/* Close the Parser */
multiline_comment|/* TBD: [Restructure] Acpi_ps_terminate () */
id|acpi_ps_delete_parse_cache
(paren
)paren
suffix:semicolon
multiline_comment|/* Debug only - display leftover memory allocation, if any */
macro_line|#ifdef ACPI_DBG_TRACK_ALLOCATIONS
id|acpi_ut_dump_allocations
(paren
id|ACPI_UINT32_MAX
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
