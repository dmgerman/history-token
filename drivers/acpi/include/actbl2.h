multiline_comment|/******************************************************************************&n; *&n; * Name: actbl2.h - ACPI Specification Revision 2.0 Tables&n; *       $Revision: 24 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACTBL2_H__
DECL|macro|__ACTBL2_H__
mdefine_line|#define __ACTBL2_H__
multiline_comment|/*&n; * Prefered Power Management Profiles&n; */
DECL|macro|PM_UNSPECIFIED
mdefine_line|#define PM_UNSPECIFIED                  0
DECL|macro|PM_DESKTOP
mdefine_line|#define PM_DESKTOP                      1
DECL|macro|PM_MOBILE
mdefine_line|#define PM_MOBILE                       2
DECL|macro|PM_WORKSTATION
mdefine_line|#define PM_WORKSTATION                  3
DECL|macro|PM_ENTERPRISE_SERVER
mdefine_line|#define PM_ENTERPRISE_SERVER            4
DECL|macro|PM_SOHO_SERVER
mdefine_line|#define PM_SOHO_SERVER                  5
DECL|macro|PM_APPLIANCE_PC
mdefine_line|#define PM_APPLIANCE_PC                 6
multiline_comment|/*&n; * ACPI Boot Arch Flags&n; */
DECL|macro|BAF_LEGACY_DEVICES
mdefine_line|#define BAF_LEGACY_DEVICES              0x0001
DECL|macro|BAF_8042_KEYBOARD_CONTROLLER
mdefine_line|#define BAF_8042_KEYBOARD_CONTROLLER    0x0002
DECL|macro|FADT2_REVISION_ID
mdefine_line|#define FADT2_REVISION_ID               3
macro_line|#pragma pack(1)
multiline_comment|/*&n; * ACPI Specification Rev 2.0 for the Root System Description Table&n; */
r_typedef
r_struct
(brace
DECL|member|header
id|acpi_table_header
id|header
suffix:semicolon
multiline_comment|/* Table header */
DECL|member|table_offset_entry
id|u32
id|table_offset_entry
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Array of pointers to  */
multiline_comment|/* other tables&squot; headers */
DECL|typedef|RSDT_DESCRIPTOR_REV2
)brace
id|RSDT_DESCRIPTOR_REV2
suffix:semicolon
multiline_comment|/*&n; * ACPI Specification Rev 2.0 for the Extended System Description Table (XSDT)&n; */
r_typedef
r_struct
(brace
DECL|member|header
id|acpi_table_header
id|header
suffix:semicolon
multiline_comment|/* Table header */
DECL|member|table_offset_entry
id|u64
id|table_offset_entry
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Array of pointers to  */
multiline_comment|/* other tables&squot; headers */
DECL|typedef|XSDT_DESCRIPTOR_REV2
)brace
id|XSDT_DESCRIPTOR_REV2
suffix:semicolon
multiline_comment|/*&n; * ACPI Specification Rev 2.0 for the Firmware ACPI Control Structure&n; */
r_typedef
r_struct
(brace
DECL|member|signature
id|NATIVE_CHAR
id|signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* signature &quot;FACS&quot; */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* length of structure, in bytes */
DECL|member|hardware_signature
id|u32
id|hardware_signature
suffix:semicolon
multiline_comment|/* hardware configuration signature */
DECL|member|firmware_waking_vector
id|u32
id|firmware_waking_vector
suffix:semicolon
multiline_comment|/* 32bit physical address of the Firmware Waking Vector. */
DECL|member|global_lock
id|u32
id|global_lock
suffix:semicolon
multiline_comment|/* Global Lock used to synchronize access to shared hardware resources */
DECL|member|S4bios_f
id|u32
id|S4bios_f
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates if S4BIOS support is present */
DECL|member|reserved1
id|u32
id|reserved1
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* must be 0 */
DECL|member|Xfirmware_waking_vector
id|u64
id|Xfirmware_waking_vector
suffix:semicolon
multiline_comment|/* 64bit physical address of the Firmware Waking Vector. */
DECL|member|version
id|u8
id|version
suffix:semicolon
multiline_comment|/* Version of this table */
DECL|member|reserved3
id|u8
id|reserved3
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* reserved - must be zero */
DECL|typedef|facs_descriptor_rev2
)brace
id|facs_descriptor_rev2
suffix:semicolon
multiline_comment|/*&n; * ACPI Specification Rev 2.0 for the Generic Address Structure (GAS)&n; */
r_typedef
r_struct
(brace
DECL|member|address_space_id
id|u8
id|address_space_id
suffix:semicolon
multiline_comment|/* Address space where struct or register exists. */
DECL|member|register_bit_width
id|u8
id|register_bit_width
suffix:semicolon
multiline_comment|/* Size in bits of given register */
DECL|member|register_bit_offset
id|u8
id|register_bit_offset
suffix:semicolon
multiline_comment|/* Bit offset within the register */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* Must be 0 */
DECL|member|address
id|u64
id|address
suffix:semicolon
multiline_comment|/* 64-bit address of struct or register */
DECL|typedef|acpi_generic_address
)brace
id|acpi_generic_address
suffix:semicolon
multiline_comment|/*&n; * ACPI Specification Rev 2.0 for the Fixed ACPI Description Table&n; */
r_typedef
r_struct
(brace
DECL|member|header
id|acpi_table_header
id|header
suffix:semicolon
multiline_comment|/* table header */
DECL|member|V1_firmware_ctrl
id|u32
id|V1_firmware_ctrl
suffix:semicolon
multiline_comment|/* 32-bit physical address of FACS */
DECL|member|V1_dsdt
id|u32
id|V1_dsdt
suffix:semicolon
multiline_comment|/* 32-bit physical address of DSDT */
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
multiline_comment|/* System Interrupt Model isn&squot;t used in ACPI 2.0*/
DECL|member|prefer_PM_profile
id|u8
id|prefer_PM_profile
suffix:semicolon
multiline_comment|/* Conveys preferred power management profile to OSPM. */
DECL|member|sci_int
id|u16
id|sci_int
suffix:semicolon
multiline_comment|/* System vector of SCI interrupt */
DECL|member|smi_cmd
id|u32
id|smi_cmd
suffix:semicolon
multiline_comment|/* Port address of SMI command port */
DECL|member|acpi_enable
id|u8
id|acpi_enable
suffix:semicolon
multiline_comment|/* value to write to smi_cmd to enable ACPI */
DECL|member|acpi_disable
id|u8
id|acpi_disable
suffix:semicolon
multiline_comment|/* value to write to smi_cmd to disable ACPI */
DECL|member|S4bios_req
id|u8
id|S4bios_req
suffix:semicolon
multiline_comment|/* Value to write to SMI CMD to enter S4BIOS state */
DECL|member|pstate_cnt
id|u8
id|pstate_cnt
suffix:semicolon
multiline_comment|/* processor performance state control*/
DECL|member|V1_pm1a_evt_blk
id|u32
id|V1_pm1a_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1a Acpi_event Reg Blk */
DECL|member|V1_pm1b_evt_blk
id|u32
id|V1_pm1b_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1b Acpi_event Reg Blk */
DECL|member|V1_pm1a_cnt_blk
id|u32
id|V1_pm1a_cnt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1a Control Reg Blk */
DECL|member|V1_pm1b_cnt_blk
id|u32
id|V1_pm1b_cnt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1b Control Reg Blk */
DECL|member|V1_pm2_cnt_blk
id|u32
id|V1_pm2_cnt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 2 Control Reg Blk */
DECL|member|V1_pm_tmr_blk
id|u32
id|V1_pm_tmr_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt Timer Ctrl Reg Blk */
DECL|member|V1_gpe0blk
id|u32
id|V1_gpe0blk
suffix:semicolon
multiline_comment|/* Port addr of General Purpose Acpi_event 0 Reg Blk */
DECL|member|V1_gpe1_blk
id|u32
id|V1_gpe1_blk
suffix:semicolon
multiline_comment|/* Port addr of General Purpose Acpi_event 1 Reg Blk */
DECL|member|pm1_evt_len
id|u8
id|pm1_evt_len
suffix:semicolon
multiline_comment|/* Byte Length of ports at pm1_x_evt_blk */
DECL|member|pm1_cnt_len
id|u8
id|pm1_cnt_len
suffix:semicolon
multiline_comment|/* Byte Length of ports at pm1_x_cnt_blk */
DECL|member|pm2_cnt_len
id|u8
id|pm2_cnt_len
suffix:semicolon
multiline_comment|/* Byte Length of ports at pm2_cnt_blk */
DECL|member|pm_tm_len
id|u8
id|pm_tm_len
suffix:semicolon
multiline_comment|/* Byte Length of ports at pm_tm_blk */
DECL|member|gpe0blk_len
id|u8
id|gpe0blk_len
suffix:semicolon
multiline_comment|/* Byte Length of ports at gpe0_blk */
DECL|member|gpe1_blk_len
id|u8
id|gpe1_blk_len
suffix:semicolon
multiline_comment|/* Byte Length of ports at gpe1_blk */
DECL|member|gpe1_base
id|u8
id|gpe1_base
suffix:semicolon
multiline_comment|/* offset in gpe model where gpe1 events start */
DECL|member|cst_cnt
id|u8
id|cst_cnt
suffix:semicolon
multiline_comment|/* Support for the _CST object and C States change notification.*/
DECL|member|plvl2_lat
id|u16
id|plvl2_lat
suffix:semicolon
multiline_comment|/* worst case HW latency to enter/exit C2 state */
DECL|member|plvl3_lat
id|u16
id|plvl3_lat
suffix:semicolon
multiline_comment|/* worst case HW latency to enter/exit C3 state */
DECL|member|flush_size
id|u16
id|flush_size
suffix:semicolon
multiline_comment|/* number of flush strides that need to be read */
DECL|member|flush_stride
id|u16
id|flush_stride
suffix:semicolon
multiline_comment|/* Processor&squot;s memory cache line width, in bytes */
DECL|member|duty_offset
id|u8
id|duty_offset
suffix:semicolon
multiline_comment|/* Processor_&#xfffd;s duty cycle index in processor&squot;s P_CNT reg*/
DECL|member|duty_width
id|u8
id|duty_width
suffix:semicolon
multiline_comment|/* Processor_&#xfffd;s duty cycle value bit width in P_CNT register.*/
DECL|member|day_alrm
id|u8
id|day_alrm
suffix:semicolon
multiline_comment|/* index to day-of-month alarm in RTC CMOS RAM */
DECL|member|mon_alrm
id|u8
id|mon_alrm
suffix:semicolon
multiline_comment|/* index to month-of-year alarm in RTC CMOS RAM */
DECL|member|century
id|u8
id|century
suffix:semicolon
multiline_comment|/* index to century in RTC CMOS RAM */
DECL|member|iapc_boot_arch
id|u16
id|iapc_boot_arch
suffix:semicolon
multiline_comment|/* IA-PC Boot Architecture Flags. See Table 5-10 for description*/
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|wb_invd
id|u32
id|wb_invd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* wbinvd instruction works properly */
DECL|member|wb_invd_flush
id|u32
id|wb_invd_flush
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* wbinvd flushes but does not invalidate */
DECL|member|proc_c1
id|u32
id|proc_c1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* all processors support C1 state */
DECL|member|plvl2_up
id|u32
id|plvl2_up
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* C2 state works on MP system */
DECL|member|pwr_button
id|u32
id|pwr_button
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Power button is handled as a generic feature */
DECL|member|sleep_button
id|u32
id|sleep_button
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Sleep button is handled as a generic feature, or not present */
DECL|member|fixed_rTC
id|u32
id|fixed_rTC
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* RTC wakeup stat not in fixed register space */
DECL|member|rtcs4
id|u32
id|rtcs4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* RTC wakeup stat not possible from S4 */
DECL|member|tmr_val_ext
id|u32
id|tmr_val_ext
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* tmr_val is 32 bits */
DECL|member|dock_cap
id|u32
id|dock_cap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supports Docking */
DECL|member|reset_reg_sup
id|u32
id|reset_reg_sup
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates system supports system reset via the FADT RESET_REG*/
DECL|member|sealed_case
id|u32
id|sealed_case
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates system has no internal expansion capabilities and case is sealed. */
DECL|member|headless
id|u32
id|headless
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates system does not have local video capabilities or local input devices.*/
DECL|member|cpu_sw_sleep
id|u32
id|cpu_sw_sleep
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates to OSPM that a processor native instruction */
multiline_comment|/* must be executed after writing the SLP_TYPx register. */
DECL|member|reserved6
id|u32
id|reserved6
suffix:colon
l_int|18
suffix:semicolon
multiline_comment|/* reserved - must be zero */
DECL|member|reset_register
id|acpi_generic_address
id|reset_register
suffix:semicolon
multiline_comment|/* Reset register address in GAS format */
DECL|member|reset_value
id|u8
id|reset_value
suffix:semicolon
multiline_comment|/* Value to write to the Reset_register port to reset the system. */
DECL|member|reserved7
id|u8
id|reserved7
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* These three bytes must be zero */
DECL|member|Xfirmware_ctrl
id|u64
id|Xfirmware_ctrl
suffix:semicolon
multiline_comment|/* 64-bit physical address of FACS */
DECL|member|Xdsdt
id|u64
id|Xdsdt
suffix:semicolon
multiline_comment|/* 64-bit physical address of DSDT */
DECL|member|Xpm1a_evt_blk
id|acpi_generic_address
id|Xpm1a_evt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1a Acpi_event Reg Blk address */
DECL|member|Xpm1b_evt_blk
id|acpi_generic_address
id|Xpm1b_evt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1b Acpi_event Reg Blk address */
DECL|member|Xpm1a_cnt_blk
id|acpi_generic_address
id|Xpm1a_cnt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1a Control Reg Blk address */
DECL|member|Xpm1b_cnt_blk
id|acpi_generic_address
id|Xpm1b_cnt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1b Control Reg Blk address */
DECL|member|Xpm2_cnt_blk
id|acpi_generic_address
id|Xpm2_cnt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 2 Control Reg Blk address */
DECL|member|Xpm_tmr_blk
id|acpi_generic_address
id|Xpm_tmr_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt Timer Ctrl Reg Blk address */
DECL|member|Xgpe0blk
id|acpi_generic_address
id|Xgpe0blk
suffix:semicolon
multiline_comment|/* Extended General Purpose Acpi_event 0 Reg Blk address */
DECL|member|Xgpe1_blk
id|acpi_generic_address
id|Xgpe1_blk
suffix:semicolon
multiline_comment|/* Extended General Purpose Acpi_event 1 Reg Blk address */
DECL|typedef|fadt_descriptor_rev2
)brace
id|fadt_descriptor_rev2
suffix:semicolon
macro_line|#pragma pack()
macro_line|#endif /* __ACTBL2_H__ */
eof
