multiline_comment|/******************************************************************************&n; *&n; * Name: actbl2.h - ACPI Specification Revision 2.0 Tables&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
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
multiline_comment|/*&n; * ACPI 2.0 Root System Description Table (RSDT)&n; */
DECL|struct|rsdt_descriptor_rev2
r_struct
id|rsdt_descriptor_rev2
(brace
id|ACPI_TABLE_HEADER_DEF
multiline_comment|/* ACPI common table header */
DECL|member|table_offset_entry
id|u32
id|table_offset_entry
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Array of pointers to  */
multiline_comment|/* ACPI table headers */
)brace
suffix:semicolon
multiline_comment|/*&n; * ACPI 2.0 Extended System Description Table (XSDT)&n; */
DECL|struct|xsdt_descriptor_rev2
r_struct
id|xsdt_descriptor_rev2
(brace
id|ACPI_TABLE_HEADER_DEF
multiline_comment|/* ACPI common table header */
DECL|member|table_offset_entry
id|u64
id|table_offset_entry
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Array of pointers to  */
multiline_comment|/* ACPI table headers */
)brace
suffix:semicolon
multiline_comment|/*&n; * ACPI 2.0 Firmware ACPI Control Structure (FACS)&n; */
DECL|struct|facs_descriptor_rev2
r_struct
id|facs_descriptor_rev2
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ACPI signature */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* Length of structure, in bytes */
DECL|member|hardware_signature
id|u32
id|hardware_signature
suffix:semicolon
multiline_comment|/* Hardware configuration signature */
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
multiline_comment|/* S4Bios_f - Indicates if S4BIOS support is present */
DECL|member|reserved1
id|u32
id|reserved1
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* Must be 0 */
DECL|member|xfirmware_waking_vector
id|u64
id|xfirmware_waking_vector
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
multiline_comment|/* Reserved - must be zero */
)brace
suffix:semicolon
multiline_comment|/*&n; * ACPI 2.0 Generic Address Structure (GAS)&n; */
DECL|struct|acpi_generic_address
r_struct
id|acpi_generic_address
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
)brace
suffix:semicolon
multiline_comment|/*&n; * ACPI 2.0 Fixed ACPI Description Table (FADT)&n; */
DECL|struct|fadt_descriptor_rev2
r_struct
id|fadt_descriptor_rev2
(brace
id|ACPI_TABLE_HEADER_DEF
multiline_comment|/* ACPI common table header */
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
multiline_comment|/* Value to write to smi_cmd to enable ACPI */
DECL|member|acpi_disable
id|u8
id|acpi_disable
suffix:semicolon
multiline_comment|/* Value to write to smi_cmd to disable ACPI */
DECL|member|S4bios_req
id|u8
id|S4bios_req
suffix:semicolon
multiline_comment|/* Value to write to SMI CMD to enter S4BIOS state */
DECL|member|pstate_cnt
id|u8
id|pstate_cnt
suffix:semicolon
multiline_comment|/* Processor performance state control*/
DECL|member|V1_pm1a_evt_blk
id|u32
id|V1_pm1a_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1a acpi_event Reg Blk */
DECL|member|V1_pm1b_evt_blk
id|u32
id|V1_pm1b_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1b acpi_event Reg Blk */
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
DECL|member|V1_gpe0_blk
id|u32
id|V1_gpe0_blk
suffix:semicolon
multiline_comment|/* Port addr of General Purpose acpi_event 0 Reg Blk */
DECL|member|V1_gpe1_blk
id|u32
id|V1_gpe1_blk
suffix:semicolon
multiline_comment|/* Port addr of General Purpose acpi_event 1 Reg Blk */
DECL|member|pm1_evt_len
id|u8
id|pm1_evt_len
suffix:semicolon
multiline_comment|/* Byte length of ports at pm1_x_evt_blk */
DECL|member|pm1_cnt_len
id|u8
id|pm1_cnt_len
suffix:semicolon
multiline_comment|/* Byte length of ports at pm1_x_cnt_blk */
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
DECL|member|gpe0_blk_len
id|u8
id|gpe0_blk_len
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
multiline_comment|/* Offset in gpe model where gpe1 events start */
DECL|member|cst_cnt
id|u8
id|cst_cnt
suffix:semicolon
multiline_comment|/* Support for the _CST object and C States change notification.*/
DECL|member|plvl2_lat
id|u16
id|plvl2_lat
suffix:semicolon
multiline_comment|/* Worst case HW latency to enter/exit C2 state */
DECL|member|plvl3_lat
id|u16
id|plvl3_lat
suffix:semicolon
multiline_comment|/* Worst case HW latency to enter/exit C3 state */
DECL|member|flush_size
id|u16
id|flush_size
suffix:semicolon
multiline_comment|/* Number of flush strides that need to be read */
DECL|member|flush_stride
id|u16
id|flush_stride
suffix:semicolon
multiline_comment|/* Processor&squot;s memory cache line width, in bytes */
DECL|member|duty_offset
id|u8
id|duty_offset
suffix:semicolon
multiline_comment|/* Processor&squot;s duty cycle index in processor&squot;s P_CNT reg*/
DECL|member|duty_width
id|u8
id|duty_width
suffix:semicolon
multiline_comment|/* Processor&squot;s duty cycle value bit width in P_CNT register.*/
DECL|member|day_alrm
id|u8
id|day_alrm
suffix:semicolon
multiline_comment|/* Index to day-of-month alarm in RTC CMOS RAM */
DECL|member|mon_alrm
id|u8
id|mon_alrm
suffix:semicolon
multiline_comment|/* Index to month-of-year alarm in RTC CMOS RAM */
DECL|member|century
id|u8
id|century
suffix:semicolon
multiline_comment|/* Index to century in RTC CMOS RAM */
DECL|member|iapc_boot_arch
id|u16
id|iapc_boot_arch
suffix:semicolon
multiline_comment|/* IA-PC Boot Architecture Flags. See Table 5-10 for description*/
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|wb_invd
id|u32
id|wb_invd
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The wbinvd instruction works properly */
DECL|member|wb_invd_flush
id|u32
id|wb_invd_flush
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The wbinvd flushes but does not invalidate */
DECL|member|proc_c1
id|u32
id|proc_c1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* All processors support C1 state */
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
multiline_comment|/* Indicates tmr_val is 32 bits 0=24-bits*/
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
multiline_comment|/* Must be executed after writing the SLP_TYPx register. */
DECL|member|reserved6
id|u32
id|reserved6
suffix:colon
l_int|18
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
DECL|member|reset_register
r_struct
id|acpi_generic_address
id|reset_register
suffix:semicolon
multiline_comment|/* Reset register address in GAS format */
DECL|member|reset_value
id|u8
id|reset_value
suffix:semicolon
multiline_comment|/* Value to write to the reset_register port to reset the system. */
DECL|member|reserved7
id|u8
id|reserved7
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* These three bytes must be zero */
DECL|member|xfirmware_ctrl
id|u64
id|xfirmware_ctrl
suffix:semicolon
multiline_comment|/* 64-bit physical address of FACS */
DECL|member|Xdsdt
id|u64
id|Xdsdt
suffix:semicolon
multiline_comment|/* 64-bit physical address of DSDT */
DECL|member|xpm1a_evt_blk
r_struct
id|acpi_generic_address
id|xpm1a_evt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1a acpi_event Reg Blk address */
DECL|member|xpm1b_evt_blk
r_struct
id|acpi_generic_address
id|xpm1b_evt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1b acpi_event Reg Blk address */
DECL|member|xpm1a_cnt_blk
r_struct
id|acpi_generic_address
id|xpm1a_cnt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1a Control Reg Blk address */
DECL|member|xpm1b_cnt_blk
r_struct
id|acpi_generic_address
id|xpm1b_cnt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 1b Control Reg Blk address */
DECL|member|xpm2_cnt_blk
r_struct
id|acpi_generic_address
id|xpm2_cnt_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt 2 Control Reg Blk address */
DECL|member|xpm_tmr_blk
r_struct
id|acpi_generic_address
id|xpm_tmr_blk
suffix:semicolon
multiline_comment|/* Extended Power Mgt Timer Ctrl Reg Blk address */
DECL|member|xgpe0_blk
r_struct
id|acpi_generic_address
id|xgpe0_blk
suffix:semicolon
multiline_comment|/* Extended General Purpose acpi_event 0 Reg Blk address */
DECL|member|xgpe1_blk
r_struct
id|acpi_generic_address
id|xgpe1_blk
suffix:semicolon
multiline_comment|/* Extended General Purpose acpi_event 1 Reg Blk address */
)brace
suffix:semicolon
multiline_comment|/* Embedded Controller */
DECL|struct|ec_boot_resources
r_struct
id|ec_boot_resources
(brace
id|ACPI_TABLE_HEADER_DEF
DECL|member|ec_control
r_struct
id|acpi_generic_address
id|ec_control
suffix:semicolon
multiline_comment|/* Address of EC command/status register */
DECL|member|ec_data
r_struct
id|acpi_generic_address
id|ec_data
suffix:semicolon
multiline_comment|/* Address of EC data register */
DECL|member|uid
id|u32
id|uid
suffix:semicolon
multiline_comment|/* Unique ID - must be same as the EC _UID method */
DECL|member|gpe_bit
id|u8
id|gpe_bit
suffix:semicolon
multiline_comment|/* The GPE for the EC */
DECL|member|ec_id
id|u8
id|ec_id
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Full namepath of the EC in the ACPI namespace */
)brace
suffix:semicolon
macro_line|#pragma pack()
macro_line|#endif /* __ACTBL2_H__ */
eof
