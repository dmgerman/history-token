multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbconvrt - ACPI Table conversion utilities&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;actables.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_TABLES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;tbconvrt&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_get_table_count&n; *&n; * PARAMETERS:  RSDP            - Pointer to the RSDP&n; *              RSDT            - Pointer to the RSDT/XSDT&n; *&n; * RETURN:      The number of tables pointed to by the RSDT or XSDT.&n; *&n; * DESCRIPTION: Calculate the number of tables.  Automatically handles either&n; *              an RSDT or XSDT.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_tb_get_table_count
id|acpi_tb_get_table_count
(paren
id|rsdp_descriptor
op_star
id|RSDP
comma
id|acpi_table_header
op_star
id|RSDT
)paren
(brace
id|u32
id|pointer_size
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
macro_line|#if ACPI_MACHINE_WIDTH != 64
r_if
c_cond
(paren
id|RSDP-&gt;revision
OL
l_int|2
)paren
(brace
id|pointer_size
op_assign
r_sizeof
(paren
id|u32
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
id|pointer_size
op_assign
r_sizeof
(paren
id|u64
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Determine the number of tables pointed to by the RSDT/XSDT.&n;&t; * This is defined by the ACPI Specification to be the number of&n;&t; * pointers contained within the RSDT/XSDT.  The size of the pointers&n;&t; * is architecture-dependent.&n;&t; */
r_return
(paren
(paren
id|RSDT-&gt;length
op_minus
r_sizeof
(paren
id|acpi_table_header
)paren
)paren
op_div
id|pointer_size
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_convert_to_xsdt&n; *&n; * PARAMETERS:  table_info      - Info about the RSDT&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert an RSDT to an XSDT (internal common format)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_convert_to_xsdt
id|acpi_tb_convert_to_xsdt
(paren
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
id|acpi_size
id|table_size
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|xsdt_descriptor
op_star
id|new_table
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Compute size of the converted XSDT */
id|table_size
op_assign
(paren
(paren
id|acpi_size
)paren
id|acpi_gbl_rsdt_table_count
op_star
r_sizeof
(paren
id|u64
)paren
)paren
op_plus
r_sizeof
(paren
id|acpi_table_header
)paren
suffix:semicolon
multiline_comment|/* Allocate an XSDT */
id|new_table
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|table_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_table
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the header and set the length */
id|ACPI_MEMCPY
(paren
id|new_table
comma
id|table_info-&gt;pointer
comma
r_sizeof
(paren
id|acpi_table_header
)paren
)paren
suffix:semicolon
id|new_table-&gt;header.length
op_assign
(paren
id|u32
)paren
id|table_size
suffix:semicolon
multiline_comment|/* Copy the table pointers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_rsdt_table_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|acpi_gbl_RSDP-&gt;revision
OL
l_int|2
)paren
(brace
id|ACPI_STORE_ADDRESS
(paren
id|new_table-&gt;table_offset_entry
(braket
id|i
)braket
comma
(paren
(paren
id|RSDT_DESCRIPTOR_REV1
op_star
)paren
id|table_info-&gt;pointer
)paren
op_member_access_from_pointer
id|table_offset_entry
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|new_table-&gt;table_offset_entry
(braket
id|i
)braket
op_assign
(paren
(paren
id|xsdt_descriptor
op_star
)paren
id|table_info-&gt;pointer
)paren
op_member_access_from_pointer
id|table_offset_entry
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/* Delete the original table (either mapped or in a buffer) */
id|acpi_tb_delete_single_table
(paren
id|table_info
)paren
suffix:semicolon
multiline_comment|/* Point the table descriptor to the new table */
id|table_info-&gt;pointer
op_assign
(paren
id|acpi_table_header
op_star
)paren
id|new_table
suffix:semicolon
id|table_info-&gt;length
op_assign
id|table_size
suffix:semicolon
id|table_info-&gt;allocation
op_assign
id|ACPI_MEM_ALLOCATED
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_convert_fadt1&n; *&n; * PARAMETERS:  local_fadt      - Pointer to new FADT&n; *              original_fadt   - Pointer to old FADT&n; *&n; * RETURN:      Populates local_fadt&n; *&n; * DESCRIPTION: Convert an ACPI 1.0 FADT to common internal format&n; *&n; ******************************************************************************/
r_static
r_void
DECL|function|acpi_tb_convert_fadt1
id|acpi_tb_convert_fadt1
(paren
id|fadt_descriptor_rev2
op_star
id|local_fadt
comma
id|fadt_descriptor_rev1
op_star
id|original_fadt
)paren
(brace
multiline_comment|/* ACPI 1.0 FACS */
multiline_comment|/* The BIOS stored FADT should agree with Revision 1.0 */
multiline_comment|/*&n;&t; * Copy the table header and the common part of the tables.&n;&t; *&n;&t; * The 2.0 table is an extension of the 1.0 table, so the entire 1.0&n;&t; * table can be copied first, then expand some fields to 64 bits.&n;&t; */
id|ACPI_MEMCPY
(paren
id|local_fadt
comma
id|original_fadt
comma
r_sizeof
(paren
id|fadt_descriptor_rev1
)paren
)paren
suffix:semicolon
multiline_comment|/* Convert table pointers to 64-bit fields */
id|ACPI_STORE_ADDRESS
(paren
id|local_fadt-&gt;xfirmware_ctrl
comma
id|local_fadt-&gt;V1_firmware_ctrl
)paren
suffix:semicolon
id|ACPI_STORE_ADDRESS
(paren
id|local_fadt-&gt;Xdsdt
comma
id|local_fadt-&gt;V1_dsdt
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * System Interrupt Model isn&squot;t used in ACPI 2.0 (local_fadt-&gt;Reserved1 = 0;)&n;&t; */
multiline_comment|/*&n;&t; * This field is set by the OEM to convey the preferred power management&n;&t; * profile to OSPM. It doesn&squot;t have any 1.0 equivalence.  Since we don&squot;t&n;&t; * know what kind of 32-bit system this is, we will use &quot;unspecified&quot;.&n;&t; */
id|local_fadt-&gt;prefer_PM_profile
op_assign
id|PM_UNSPECIFIED
suffix:semicolon
multiline_comment|/*&n;&t; * Processor Performance State Control. This is the value OSPM writes to&n;&t; * the SMI_CMD register to assume processor performance state control&n;&t; * responsibility. There isn&squot;t any equivalence in 1.0, leave it zeroed.&n;&t; */
id|local_fadt-&gt;pstate_cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Support for the _CST object and C States change notification.&n;&t; * This data item hasn&squot;t any 1.0 equivalence so leave it zero.&n;&t; */
id|local_fadt-&gt;cst_cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Since there isn&squot;t any equivalence in 1.0 and since it highly likely&n;&t; * that a 1.0 system has legacy support.&n;&t; */
id|local_fadt-&gt;iapc_boot_arch
op_assign
id|BAF_LEGACY_DEVICES
suffix:semicolon
multiline_comment|/*&n;&t; * Convert the V1.0 block addresses to V2.0 GAS structures&n;&t; */
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1a_evt_blk
comma
id|local_fadt-&gt;pm1_evt_len
comma
id|local_fadt-&gt;V1_pm1a_evt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1b_evt_blk
comma
id|local_fadt-&gt;pm1_evt_len
comma
id|local_fadt-&gt;V1_pm1b_evt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1a_cnt_blk
comma
id|local_fadt-&gt;pm1_cnt_len
comma
id|local_fadt-&gt;V1_pm1a_cnt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1b_cnt_blk
comma
id|local_fadt-&gt;pm1_cnt_len
comma
id|local_fadt-&gt;V1_pm1b_cnt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm2_cnt_blk
comma
id|local_fadt-&gt;pm2_cnt_len
comma
id|local_fadt-&gt;V1_pm2_cnt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm_tmr_blk
comma
id|local_fadt-&gt;pm_tm_len
comma
id|local_fadt-&gt;V1_pm_tmr_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xgpe0_blk
comma
id|local_fadt-&gt;gpe0_blk_len
comma
id|local_fadt-&gt;V1_gpe0_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xgpe1_blk
comma
id|local_fadt-&gt;gpe1_blk_len
comma
id|local_fadt-&gt;V1_gpe1_blk
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_convert_fadt2&n; *&n; * PARAMETERS:  local_fadt      - Pointer to new FADT&n; *              original_fadt   - Pointer to old FADT&n; *&n; * RETURN:      Populates local_fadt&n; *&n; * DESCRIPTION: Convert an ACPI 2.0 FADT to common internal format.&n; *              Handles optional &quot;X&quot; fields.&n; *&n; ******************************************************************************/
r_static
r_void
DECL|function|acpi_tb_convert_fadt2
id|acpi_tb_convert_fadt2
(paren
id|fadt_descriptor_rev2
op_star
id|local_fadt
comma
id|fadt_descriptor_rev2
op_star
id|original_fadt
)paren
(brace
multiline_comment|/* We have an ACPI 2.0 FADT but we must copy it to our local buffer */
id|ACPI_MEMCPY
(paren
id|local_fadt
comma
id|original_fadt
comma
r_sizeof
(paren
id|fadt_descriptor_rev2
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;X&quot; fields are optional extensions to the original V1.0 fields, so&n;&t; * we must selectively expand V1.0 fields if the corresponding X field&n;&t; * is zero.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xfirmware_ctrl
)paren
)paren
(brace
id|ACPI_STORE_ADDRESS
(paren
id|local_fadt-&gt;xfirmware_ctrl
comma
id|local_fadt-&gt;V1_firmware_ctrl
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;Xdsdt
)paren
)paren
(brace
id|ACPI_STORE_ADDRESS
(paren
id|local_fadt-&gt;Xdsdt
comma
id|local_fadt-&gt;V1_dsdt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xpm1a_evt_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1a_evt_blk
comma
id|local_fadt-&gt;pm1_evt_len
comma
id|local_fadt-&gt;V1_pm1a_evt_blk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xpm1b_evt_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1b_evt_blk
comma
id|local_fadt-&gt;pm1_evt_len
comma
id|local_fadt-&gt;V1_pm1b_evt_blk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xpm1a_cnt_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1a_cnt_blk
comma
id|local_fadt-&gt;pm1_cnt_len
comma
id|local_fadt-&gt;V1_pm1a_cnt_blk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xpm1b_cnt_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm1b_cnt_blk
comma
id|local_fadt-&gt;pm1_cnt_len
comma
id|local_fadt-&gt;V1_pm1b_cnt_blk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xpm2_cnt_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm2_cnt_blk
comma
id|local_fadt-&gt;pm2_cnt_len
comma
id|local_fadt-&gt;V1_pm2_cnt_blk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xpm_tmr_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xpm_tmr_blk
comma
id|local_fadt-&gt;pm_tm_len
comma
id|local_fadt-&gt;V1_pm_tmr_blk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xgpe0_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xgpe0_blk
comma
id|local_fadt-&gt;gpe0_blk_len
comma
id|local_fadt-&gt;V1_gpe0_blk
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|local_fadt-&gt;xgpe1_blk.address
)paren
)paren
(brace
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|local_fadt-&gt;xgpe1_blk
comma
id|local_fadt-&gt;gpe1_blk_len
comma
id|local_fadt-&gt;V1_gpe1_blk
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_convert_table_fadt&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Converts a BIOS supplied ACPI 1.0 FADT to a local&n; *              ACPI 2.0 FADT. If the BIOS supplied a 2.0 FADT then it is simply&n; *              copied to the local FADT.  The ACPI CA software uses this&n; *              local FADT. Thus a significant amount of special #ifdef&n; *              type codeing is saved.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_convert_table_fadt
id|acpi_tb_convert_table_fadt
(paren
r_void
)paren
(brace
id|fadt_descriptor_rev2
op_star
id|local_fadt
suffix:semicolon
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_convert_table_fadt&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * acpi_gbl_FADT is valid&n;&t; * Allocate and zero the 2.0 FADT buffer&n;&t; */
id|local_fadt
op_assign
id|ACPI_MEM_CALLOCATE
(paren
r_sizeof
(paren
id|fadt_descriptor_rev2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_fadt
op_eq
l_int|NULL
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * FADT length and version validation.  The table must be at least as&n;&t; * long as the version 1.0 FADT&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;header.length
OL
r_sizeof
(paren
id|fadt_descriptor_rev1
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid FADT table length: 0x%X&bslash;n&quot;
comma
id|acpi_gbl_FADT-&gt;header.length
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_INVALID_TABLE_LENGTH
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;header.revision
op_ge
id|FADT2_REVISION_ID
)paren
(brace
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;header.length
OL
r_sizeof
(paren
id|fadt_descriptor_rev2
)paren
)paren
(brace
multiline_comment|/* Length is too short to be a V2.0 table */
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;Inconsistent FADT length (0x%X) and revision (0x%X), using FADT V1.0 portion of table&bslash;n&quot;
comma
id|acpi_gbl_FADT-&gt;header.length
comma
id|acpi_gbl_FADT-&gt;header.revision
)paren
)paren
suffix:semicolon
id|acpi_tb_convert_fadt1
(paren
id|local_fadt
comma
(paren
r_void
op_star
)paren
id|acpi_gbl_FADT
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Valid V2.0 table */
id|acpi_tb_convert_fadt2
(paren
id|local_fadt
comma
id|acpi_gbl_FADT
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Valid V1.0 table */
id|acpi_tb_convert_fadt1
(paren
id|local_fadt
comma
(paren
r_void
op_star
)paren
id|acpi_gbl_FADT
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Global FADT pointer will point to the new common V2.0 FADT&n;&t; */
id|acpi_gbl_FADT
op_assign
id|local_fadt
suffix:semicolon
id|acpi_gbl_FADT-&gt;header.length
op_assign
r_sizeof
(paren
id|FADT_DESCRIPTOR
)paren
suffix:semicolon
multiline_comment|/* Free the original table */
id|table_desc
op_assign
op_amp
id|acpi_gbl_acpi_tables
(braket
id|ACPI_TABLE_FADT
)braket
suffix:semicolon
id|acpi_tb_delete_single_table
(paren
id|table_desc
)paren
suffix:semicolon
multiline_comment|/* Install the new table */
id|table_desc-&gt;pointer
op_assign
(paren
id|acpi_table_header
op_star
)paren
id|acpi_gbl_FADT
suffix:semicolon
id|table_desc-&gt;allocation
op_assign
id|ACPI_MEM_ALLOCATED
suffix:semicolon
id|table_desc-&gt;length
op_assign
r_sizeof
(paren
id|fadt_descriptor_rev2
)paren
suffix:semicolon
multiline_comment|/* Dump the entire FADT */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_TABLES
comma
l_string|&quot;Hex dump of common internal FADT, size %d (%X)&bslash;n&quot;
comma
id|acpi_gbl_FADT-&gt;header.length
comma
id|acpi_gbl_FADT-&gt;header.length
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
(paren
id|u8
op_star
)paren
(paren
id|acpi_gbl_FADT
)paren
comma
id|acpi_gbl_FADT-&gt;header.length
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_tb_convert_table_facs&n; *&n; * PARAMETERS:  table_info      - Info for currently installad FACS&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert ACPI 1.0 and ACPI 2.0 FACS to a common internal&n; *              table format.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_tb_build_common_facs
id|acpi_tb_build_common_facs
(paren
id|acpi_table_desc
op_star
id|table_info
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;tb_build_common_facs&quot;
)paren
suffix:semicolon
multiline_comment|/* Absolute minimum length is 24, but the ACPI spec says 64 */
r_if
c_cond
(paren
id|acpi_gbl_FACS-&gt;length
OL
l_int|24
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid FACS table length: 0x%X&bslash;n&quot;
comma
id|acpi_gbl_FACS-&gt;length
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_INVALID_TABLE_LENGTH
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_FACS-&gt;length
OL
l_int|64
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;FACS is shorter than the ACPI specification allows: 0x%X, using anyway&bslash;n&quot;
comma
id|acpi_gbl_FACS-&gt;length
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy fields to the new FACS */
id|acpi_gbl_common_fACS.global_lock
op_assign
op_amp
(paren
id|acpi_gbl_FACS-&gt;global_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|acpi_gbl_RSDP-&gt;revision
OL
l_int|2
)paren
op_logical_or
(paren
id|acpi_gbl_FACS-&gt;length
OL
l_int|32
)paren
op_logical_or
(paren
op_logical_neg
(paren
id|acpi_gbl_FACS-&gt;xfirmware_waking_vector
)paren
)paren
)paren
(brace
multiline_comment|/* ACPI 1.0 FACS or short table or optional X_ field is zero */
id|acpi_gbl_common_fACS.firmware_waking_vector
op_assign
id|ACPI_CAST_PTR
(paren
id|u64
comma
op_amp
(paren
id|acpi_gbl_FACS-&gt;firmware_waking_vector
)paren
)paren
suffix:semicolon
id|acpi_gbl_common_fACS.vector_width
op_assign
l_int|32
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ACPI 2.0 FACS with valid X_ field */
id|acpi_gbl_common_fACS.firmware_waking_vector
op_assign
op_amp
id|acpi_gbl_FACS-&gt;xfirmware_waking_vector
suffix:semicolon
id|acpi_gbl_common_fACS.vector_width
op_assign
l_int|64
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
