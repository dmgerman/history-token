multiline_comment|/******************************************************************************&n; *&n; * Module Name: tbconvrt - ACPI Table conversion utilities&n; *              $Revision: 18 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;actables.h&quot;
macro_line|#include &quot;actbl.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          TABLE_MANAGER
id|MODULE_NAME
(paren
l_string|&quot;tbconvrt&quot;
)paren
multiline_comment|/*&n; * Build a GAS structure from earlier ACPI table entries (V1.0 and 0.71 extensions)&n; *&n; * 1) Address space&n; * 2) Length in bytes -- convert to length in bits&n; * 3) Bit offset is zero&n; * 4) Reserved field is zero&n; * 5) Expand address to 64 bits&n; */
DECL|macro|ASL_BUILD_GAS_FROM_ENTRY
mdefine_line|#define ASL_BUILD_GAS_FROM_ENTRY(a,b,c,d)   {a.address_space_id = (u8) d;&bslash;&n;&t;&t;&t;   a.register_bit_width = (u8) MUL_8 (b);&bslash;&n;&t;&t;&t;   a.register_bit_offset = 0;&bslash;&n;&t;&t;&t;   a.reserved = 0;&bslash;&n;&t;&t;&t;   ACPI_STORE_ADDRESS (a.address,c);}
multiline_comment|/* ACPI V1.0 entries -- address space is always I/O */
DECL|macro|ASL_BUILD_GAS_FROM_V1_ENTRY
mdefine_line|#define ASL_BUILD_GAS_FROM_V1_ENTRY(a,b,c)  ASL_BUILD_GAS_FROM_ENTRY(a,b,c,ADDRESS_SPACE_SYSTEM_IO)
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_convert_to_xsdt&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_tb_convert_to_xsdt
id|acpi_tb_convert_to_xsdt
(paren
id|ACPI_TABLE_DESC
op_star
id|table_info
comma
id|u32
op_star
id|number_of_tables
)paren
(brace
id|u32
id|table_size
suffix:semicolon
id|u32
id|pointer_size
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|XSDT_DESCRIPTOR
op_star
id|new_table
suffix:semicolon
macro_line|#ifndef _IA64
r_if
c_cond
(paren
id|acpi_gbl_RSDP-&gt;revision
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
id|UINT64
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Determine the number of tables pointed to by the RSDT/XSDT.&n;&t; * This is defined by the ACPI Specification to be the number of&n;&t; * pointers contained within the RSDT/XSDT.  The size of the pointers&n;&t; * is architecture-dependent.&n;&t; */
id|table_size
op_assign
id|table_info-&gt;pointer-&gt;length
suffix:semicolon
op_star
id|number_of_tables
op_assign
(paren
id|table_size
op_minus
r_sizeof
(paren
id|ACPI_TABLE_HEADER
)paren
)paren
op_div
id|pointer_size
suffix:semicolon
multiline_comment|/* Compute size of the converted XSDT */
id|table_size
op_assign
(paren
op_star
id|number_of_tables
op_star
r_sizeof
(paren
id|UINT64
)paren
)paren
op_plus
r_sizeof
(paren
id|ACPI_TABLE_HEADER
)paren
suffix:semicolon
multiline_comment|/* Allocate an XSDT */
id|new_table
op_assign
id|acpi_cm_callocate
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
id|MEMCPY
(paren
id|new_table
comma
id|table_info-&gt;pointer
comma
r_sizeof
(paren
id|ACPI_TABLE_HEADER
)paren
)paren
suffix:semicolon
id|new_table-&gt;header.length
op_assign
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
op_star
id|number_of_tables
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
macro_line|#ifdef _IA64
id|new_table-&gt;table_offset_entry
(braket
id|i
)braket
op_assign
(paren
(paren
id|RSDT_DESCRIPTOR_REV071
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
macro_line|#else
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
macro_line|#endif
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
id|XSDT_DESCRIPTOR
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
id|ACPI_TABLE_HEADER
op_star
)paren
id|new_table
suffix:semicolon
id|table_info-&gt;base_pointer
op_assign
(paren
id|ACPI_TABLE_HEADER
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_convert_table_fadt&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *    Converts BIOS supplied 1.0 and 0.71 ACPI FADT to an intermediate&n; *    ACPI 2.0 FADT. If the BIOS supplied a 2.0 FADT then it is simply&n; *    copied to the intermediate FADT.  The ACPI CA software uses this&n; *    intermediate FADT. Thus a significant amount of special #ifdef&n; *    type codeing is saved. This intermediate FADT will need to be&n; *    freed at some point.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_tb_convert_table_fadt
id|acpi_tb_convert_table_fadt
(paren
r_void
)paren
(brace
macro_line|#ifdef _IA64
id|FADT_DESCRIPTOR_REV071
op_star
id|FADT71
suffix:semicolon
id|u8
id|pm1_address_space
suffix:semicolon
id|u8
id|pm2_address_space
suffix:semicolon
id|u8
id|pm_timer_address_space
suffix:semicolon
id|u8
id|gpe0address_space
suffix:semicolon
id|u8
id|gpe1_address_space
suffix:semicolon
macro_line|#else
id|FADT_DESCRIPTOR_REV1
op_star
id|FADT1
suffix:semicolon
macro_line|#endif
id|FADT_DESCRIPTOR_REV2
op_star
id|FADT2
suffix:semicolon
id|ACPI_TABLE_DESC
op_star
id|table_desc
suffix:semicolon
multiline_comment|/* Acpi_gbl_FADT is valid */
multiline_comment|/* Allocate and zero the 2.0 buffer */
id|FADT2
op_assign
id|acpi_cm_callocate
(paren
r_sizeof
(paren
id|FADT_DESCRIPTOR_REV2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|FADT2
op_eq
l_int|NULL
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* The ACPI FADT revision number is FADT2_REVISION_ID=3 */
multiline_comment|/* So, if the current table revision is less than 3 it is type 1.0 or 0.71 */
r_if
c_cond
(paren
id|acpi_gbl_FADT-&gt;header.revision
op_ge
id|FADT2_REVISION_ID
)paren
(brace
multiline_comment|/* We have an ACPI 2.0 FADT but we must copy it to our local buffer */
op_star
id|FADT2
op_assign
op_star
(paren
(paren
id|FADT_DESCRIPTOR_REV2
op_star
)paren
id|acpi_gbl_FADT
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef _IA64
multiline_comment|/*&n;&t;&t; * For the 64-bit case only, a revision ID less than V2.0 means the&n;&t;&t; * tables are the 0.71 extensions&n;&t;&t; */
multiline_comment|/* The BIOS stored FADT should agree with Revision 0.71 */
id|FADT71
op_assign
(paren
id|FADT_DESCRIPTOR_REV071
op_star
)paren
id|acpi_gbl_FADT
suffix:semicolon
multiline_comment|/* Copy the table header*/
id|FADT2-&gt;header
op_assign
id|FADT71-&gt;header
suffix:semicolon
multiline_comment|/* Copy the common fields */
id|FADT2-&gt;sci_int
op_assign
id|FADT71-&gt;sci_int
suffix:semicolon
id|FADT2-&gt;acpi_enable
op_assign
id|FADT71-&gt;acpi_enable
suffix:semicolon
id|FADT2-&gt;acpi_disable
op_assign
id|FADT71-&gt;acpi_disable
suffix:semicolon
id|FADT2-&gt;S4_bios_req
op_assign
id|FADT71-&gt;S4_bios_req
suffix:semicolon
id|FADT2-&gt;plvl2_lat
op_assign
id|FADT71-&gt;plvl2_lat
suffix:semicolon
id|FADT2-&gt;plvl3_lat
op_assign
id|FADT71-&gt;plvl3_lat
suffix:semicolon
id|FADT2-&gt;day_alrm
op_assign
id|FADT71-&gt;day_alrm
suffix:semicolon
id|FADT2-&gt;mon_alrm
op_assign
id|FADT71-&gt;mon_alrm
suffix:semicolon
id|FADT2-&gt;century
op_assign
id|FADT71-&gt;century
suffix:semicolon
id|FADT2-&gt;gpe1_base
op_assign
id|FADT71-&gt;gpe1_base
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We still use the block length registers even though&n;&t;&t; * the GAS structure should obsolete them.  This is because&n;&t;&t; * these registers are byte lengths versus the GAS which&n;&t;&t; * contains a bit width&n;&t;&t; */
id|FADT2-&gt;pm1_evt_len
op_assign
id|FADT71-&gt;pm1_evt_len
suffix:semicolon
id|FADT2-&gt;pm1_cnt_len
op_assign
id|FADT71-&gt;pm1_cnt_len
suffix:semicolon
id|FADT2-&gt;pm2_cnt_len
op_assign
id|FADT71-&gt;pm2_cnt_len
suffix:semicolon
id|FADT2-&gt;pm_tm_len
op_assign
id|FADT71-&gt;pm_tm_len
suffix:semicolon
id|FADT2-&gt;gpe0blk_len
op_assign
id|FADT71-&gt;gpe0blk_len
suffix:semicolon
id|FADT2-&gt;gpe1_blk_len
op_assign
id|FADT71-&gt;gpe1_blk_len
suffix:semicolon
id|FADT2-&gt;gpe1_base
op_assign
id|FADT71-&gt;gpe1_base
suffix:semicolon
multiline_comment|/* Copy the existing 0.71 flags to 2.0. The other bits are zero.*/
id|FADT2-&gt;wb_invd
op_assign
id|FADT71-&gt;flush_cash
suffix:semicolon
id|FADT2-&gt;proc_c1
op_assign
id|FADT71-&gt;proc_c1
suffix:semicolon
id|FADT2-&gt;plvl2_up
op_assign
id|FADT71-&gt;plvl2_up
suffix:semicolon
id|FADT2-&gt;pwr_button
op_assign
id|FADT71-&gt;pwr_button
suffix:semicolon
id|FADT2-&gt;sleep_button
op_assign
id|FADT71-&gt;sleep_button
suffix:semicolon
id|FADT2-&gt;fixed_rTC
op_assign
id|FADT71-&gt;fixed_rTC
suffix:semicolon
id|FADT2-&gt;rtcs4
op_assign
id|FADT71-&gt;rtcs4
suffix:semicolon
id|FADT2-&gt;tmr_val_ext
op_assign
id|FADT71-&gt;tmr_val_ext
suffix:semicolon
id|FADT2-&gt;dock_cap
op_assign
id|FADT71-&gt;dock_cap
suffix:semicolon
multiline_comment|/* We should not use these next two addresses */
multiline_comment|/* Since our buffer is pre-zeroed nothing to do for */
multiline_comment|/* the next three data items in the structure */
multiline_comment|/* FADT2-&gt;Firmware_ctrl = 0; */
multiline_comment|/* FADT2-&gt;Dsdt = 0; */
multiline_comment|/* System Interrupt Model isn&squot;t used in ACPI 2.0*/
multiline_comment|/* FADT2-&gt;Reserved1 = 0; */
multiline_comment|/* This field is set by the OEM to convey the preferred */
multiline_comment|/* power management profile to OSPM. It doesn&squot;t have any*/
multiline_comment|/* 0.71 equivalence.  Since we don&squot;t know what kind of  */
multiline_comment|/* 64-bit system this is, we will pick unspecified.     */
id|FADT2-&gt;prefer_PM_profile
op_assign
id|PM_UNSPECIFIED
suffix:semicolon
multiline_comment|/* Port address of SMI command port */
multiline_comment|/* We shouldn&squot;t use this port because IA64 doesn&squot;t */
multiline_comment|/* have or use SMI.  It has PMI. */
id|FADT2-&gt;smi_cmd
op_assign
(paren
id|u32
)paren
(paren
id|FADT71-&gt;smi_cmd
op_amp
l_int|0xFFFFFFFF
)paren
suffix:semicolon
multiline_comment|/* processor performance state control*/
multiline_comment|/* The value OSPM writes to the SMI_CMD register to assume */
multiline_comment|/* processor performance state control responsibility. */
multiline_comment|/* There isn&squot;t any equivalence in 0.71 */
multiline_comment|/* Again this should be meaningless for IA64 */
multiline_comment|/* FADT2-&gt;Pstate_cnt = 0; */
multiline_comment|/* The 32-bit Power management and GPE registers are */
multiline_comment|/* not valid in IA-64 and we are not going to use them */
multiline_comment|/* so leaving them pre-zeroed. */
multiline_comment|/* Support for the _CST object and C States change notification.*/
multiline_comment|/* This data item hasn&squot;t any 0.71 equivalence so leaving it zero.*/
multiline_comment|/* FADT2-&gt;Cst_cnt = 0; */
multiline_comment|/* number of flush strides that need to be read */
multiline_comment|/* No 0.71 equivalence. Leave pre-zeroed. */
multiline_comment|/* FADT2-&gt;Flush_size = 0; */
multiline_comment|/* Processor&squot;s memory cache line width, in bytes */
multiline_comment|/* No 0.71 equivalence. Leave pre-zeroed. */
multiline_comment|/* FADT2-&gt;Flush_stride = 0; */
multiline_comment|/* Processor&squot;s duty cycle index in processor&squot;s P_CNT reg*/
multiline_comment|/* No 0.71 equivalence. Leave pre-zeroed. */
multiline_comment|/* FADT2-&gt;Duty_offset = 0; */
multiline_comment|/* Processor&squot;s duty cycle value bit width in P_CNT register.*/
multiline_comment|/* No 0.71 equivalence. Leave pre-zeroed. */
multiline_comment|/* FADT2-&gt;Duty_width = 0; */
multiline_comment|/* Since there isn&squot;t any equivalence in 0.71 */
multiline_comment|/* and since Big_sur had to support legacy */
id|FADT2-&gt;iapc_boot_arch
op_assign
id|BAF_LEGACY_DEVICES
suffix:semicolon
multiline_comment|/* Copy to ACPI 2.0 64-BIT Extended Addresses */
id|FADT2-&gt;Xfirmware_ctrl
op_assign
id|FADT71-&gt;firmware_ctrl
suffix:semicolon
id|FADT2-&gt;Xdsdt
op_assign
id|FADT71-&gt;dsdt
suffix:semicolon
multiline_comment|/* Extract the address space IDs */
id|pm1_address_space
op_assign
(paren
id|u8
)paren
(paren
(paren
id|FADT71-&gt;address_space
op_amp
id|PM1_BLK_ADDRESS_SPACE
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|pm2_address_space
op_assign
(paren
id|u8
)paren
(paren
(paren
id|FADT71-&gt;address_space
op_amp
id|PM2_CNT_BLK_ADDRESS_SPACE
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
id|pm_timer_address_space
op_assign
(paren
id|u8
)paren
(paren
(paren
id|FADT71-&gt;address_space
op_amp
id|PM_TMR_BLK_ADDRESS_SPACE
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|gpe0address_space
op_assign
(paren
id|u8
)paren
(paren
(paren
id|FADT71-&gt;address_space
op_amp
id|GPE0_BLK_ADDRESS_SPACE
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
id|gpe1_address_space
op_assign
(paren
id|u8
)paren
(paren
(paren
id|FADT71-&gt;address_space
op_amp
id|GPE1_BLK_ADDRESS_SPACE
)paren
op_rshift
l_int|5
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Convert the 0.71 (non-GAS style) Block addresses to V2.0 GAS structures,&n;&t;&t; * in this order:&n;&t;&t; *&n;&t;&t; * PM 1_a Events&n;&t;&t; * PM 1_b Events&n;&t;&t; * PM 1_a Control&n;&t;&t; * PM 1_b Control&n;&t;&t; * PM 2 Control&n;&t;&t; * PM Timer Control&n;&t;&t; * GPE Block 0&n;&t;&t; * GPE Block 1&n;&t;&t; */
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xpm1a_evt_blk
comma
id|FADT71-&gt;pm1_evt_len
comma
id|FADT71-&gt;pm1a_evt_blk
comma
id|pm1_address_space
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xpm1b_evt_blk
comma
id|FADT71-&gt;pm1_evt_len
comma
id|FADT71-&gt;pm1b_evt_blk
comma
id|pm1_address_space
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xpm1a_cnt_blk
comma
id|FADT71-&gt;pm1_cnt_len
comma
id|FADT71-&gt;pm1a_cnt_blk
comma
id|pm1_address_space
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xpm1b_cnt_blk
comma
id|FADT71-&gt;pm1_cnt_len
comma
id|FADT71-&gt;pm1b_cnt_blk
comma
id|pm1_address_space
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xpm2_cnt_blk
comma
id|FADT71-&gt;pm2_cnt_len
comma
id|FADT71-&gt;pm2_cnt_blk
comma
id|pm2_address_space
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xpm_tmr_blk
comma
id|FADT71-&gt;pm_tm_len
comma
id|FADT71-&gt;pm_tmr_blk
comma
id|pm_timer_address_space
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xgpe0blk
comma
id|FADT71-&gt;gpe0blk_len
comma
id|FADT71-&gt;gpe0blk
comma
id|gpe0address_space
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_ENTRY
(paren
id|FADT2-&gt;Xgpe1_blk
comma
id|FADT71-&gt;gpe1_blk_len
comma
id|FADT71-&gt;gpe1_blk
comma
id|gpe1_address_space
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* ACPI 1.0 FACS */
multiline_comment|/* The BIOS stored FADT should agree with Revision 1.0 */
id|FADT1
op_assign
(paren
id|FADT_DESCRIPTOR_REV1
op_star
)paren
id|acpi_gbl_FADT
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Copy the table header and the common part of the tables&n;&t;&t; * The 2.0 table is an extension of the 1.0 table, so the&n;&t;&t; * entire 1.0 table can be copied first, then expand some&n;&t;&t; * fields to 64 bits.&n;&t;&t; */
id|MEMCPY
(paren
id|FADT2
comma
id|FADT1
comma
r_sizeof
(paren
id|FADT_DESCRIPTOR_REV1
)paren
)paren
suffix:semicolon
multiline_comment|/* Convert table pointers to 64-bit fields */
id|ACPI_STORE_ADDRESS
(paren
id|FADT2-&gt;Xfirmware_ctrl
comma
id|FADT1-&gt;firmware_ctrl
)paren
suffix:semicolon
id|ACPI_STORE_ADDRESS
(paren
id|FADT2-&gt;Xdsdt
comma
id|FADT1-&gt;dsdt
)paren
suffix:semicolon
multiline_comment|/* System Interrupt Model isn&squot;t used in ACPI 2.0*/
multiline_comment|/* FADT2-&gt;Reserved1 = 0; */
multiline_comment|/* This field is set by the OEM to convey the preferred */
multiline_comment|/* power management profile to OSPM. It doesn&squot;t have any*/
multiline_comment|/* 1.0 equivalence.  Since we don&squot;t know what kind of   */
multiline_comment|/* 32-bit system this is, we will pick unspecified.     */
id|FADT2-&gt;prefer_PM_profile
op_assign
id|PM_UNSPECIFIED
suffix:semicolon
multiline_comment|/* Processor Performance State Control. This is the value  */
multiline_comment|/* OSPM writes to the SMI_CMD register to assume processor */
multiline_comment|/* performance state control responsibility. There isn&squot;t   */
multiline_comment|/* any equivalence in 1.0.  So leave it zeroed.            */
id|FADT2-&gt;pstate_cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Support for the _CST object and C States change notification.*/
multiline_comment|/* This data item hasn&squot;t any 1.0 equivalence so leaving it zero.*/
id|FADT2-&gt;cst_cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Since there isn&squot;t any equivalence in 1.0 and since it   */
multiline_comment|/* is highly likely that a 1.0 system has legacy  support. */
id|FADT2-&gt;iapc_boot_arch
op_assign
id|BAF_LEGACY_DEVICES
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Convert the V1.0 Block addresses to V2.0 GAS structures&n;&t;&t; * in this order:&n;&t;&t; *&n;&t;&t; * PM 1_a Events&n;&t;&t; * PM 1_b Events&n;&t;&t; * PM 1_a Control&n;&t;&t; * PM 1_b Control&n;&t;&t; * PM 2 Control&n;&t;&t; * PM Timer Control&n;&t;&t; * GPE Block 0&n;&t;&t; * GPE Block 1&n;&t;&t; */
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xpm1a_evt_blk
comma
id|FADT1-&gt;pm1_evt_len
comma
id|FADT1-&gt;pm1a_evt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xpm1b_evt_blk
comma
id|FADT1-&gt;pm1_evt_len
comma
id|FADT1-&gt;pm1b_evt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xpm1a_cnt_blk
comma
id|FADT1-&gt;pm1_cnt_len
comma
id|FADT1-&gt;pm1a_cnt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xpm1b_cnt_blk
comma
id|FADT1-&gt;pm1_cnt_len
comma
id|FADT1-&gt;pm1b_cnt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xpm2_cnt_blk
comma
id|FADT1-&gt;pm2_cnt_len
comma
id|FADT1-&gt;pm2_cnt_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xpm_tmr_blk
comma
id|FADT1-&gt;pm_tm_len
comma
id|FADT1-&gt;pm_tmr_blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xgpe0blk
comma
id|FADT1-&gt;gpe0blk_len
comma
id|FADT1-&gt;gpe0blk
)paren
suffix:semicolon
id|ASL_BUILD_GAS_FROM_V1_ENTRY
(paren
id|FADT2-&gt;Xgpe1_blk
comma
id|FADT1-&gt;gpe1_blk_len
comma
id|FADT1-&gt;gpe1_blk
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;&t; * Global FADT pointer will point to the common V2.0 FADT&n;&t; */
id|acpi_gbl_FADT
op_assign
id|FADT2
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
id|ACPI_TABLE_HEADER
op_star
)paren
id|acpi_gbl_FADT
suffix:semicolon
id|table_desc-&gt;base_pointer
op_assign
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
id|FADT_DESCRIPTOR_REV2
)paren
suffix:semicolon
multiline_comment|/* Dump the entire FADT */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_tb_convert_table_facs&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_tb_build_common_facs
id|acpi_tb_build_common_facs
(paren
id|ACPI_TABLE_DESC
op_star
id|table_info
)paren
(brace
id|ACPI_COMMON_FACS
op_star
id|common_facs
suffix:semicolon
macro_line|#ifdef _IA64
id|FACS_DESCRIPTOR_REV071
op_star
id|FACS71
suffix:semicolon
macro_line|#else
id|FACS_DESCRIPTOR_REV1
op_star
id|FACS1
suffix:semicolon
macro_line|#endif
id|FACS_DESCRIPTOR_REV2
op_star
id|FACS2
suffix:semicolon
multiline_comment|/* Allocate a common FACS */
id|common_facs
op_assign
id|acpi_cm_callocate
(paren
r_sizeof
(paren
id|ACPI_COMMON_FACS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|common_facs
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy fields to the new FACS */
r_if
c_cond
(paren
id|acpi_gbl_RSDP-&gt;revision
OL
l_int|2
)paren
(brace
macro_line|#ifdef _IA64
multiline_comment|/* 0.71 FACS */
id|FACS71
op_assign
(paren
id|FACS_DESCRIPTOR_REV071
op_star
)paren
id|acpi_gbl_FACS
suffix:semicolon
id|common_facs-&gt;global_lock
op_assign
(paren
id|u32
op_star
)paren
op_amp
(paren
id|FACS71-&gt;global_lock
)paren
suffix:semicolon
id|common_facs-&gt;firmware_waking_vector
op_assign
op_amp
id|FACS71-&gt;firmware_waking_vector
suffix:semicolon
id|common_facs-&gt;vector_width
op_assign
l_int|64
suffix:semicolon
macro_line|#else
multiline_comment|/* ACPI 1.0 FACS */
id|FACS1
op_assign
(paren
id|FACS_DESCRIPTOR_REV1
op_star
)paren
id|acpi_gbl_FACS
suffix:semicolon
id|common_facs-&gt;global_lock
op_assign
op_amp
(paren
id|FACS1-&gt;global_lock
)paren
suffix:semicolon
id|common_facs-&gt;firmware_waking_vector
op_assign
(paren
id|UINT64
op_star
)paren
op_amp
id|FACS1-&gt;firmware_waking_vector
suffix:semicolon
id|common_facs-&gt;vector_width
op_assign
l_int|32
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
multiline_comment|/* ACPI 2.0 FACS */
id|FACS2
op_assign
(paren
id|FACS_DESCRIPTOR_REV2
op_star
)paren
id|acpi_gbl_FACS
suffix:semicolon
id|common_facs-&gt;global_lock
op_assign
op_amp
(paren
id|FACS2-&gt;global_lock
)paren
suffix:semicolon
id|common_facs-&gt;firmware_waking_vector
op_assign
op_amp
id|FACS2-&gt;Xfirmware_waking_vector
suffix:semicolon
id|common_facs-&gt;vector_width
op_assign
l_int|64
suffix:semicolon
)brace
multiline_comment|/* Set the global FACS pointer to point to the common FACS */
id|acpi_gbl_FACS
op_assign
id|common_facs
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
