multiline_comment|/******************************************************************************&n; *&n; * Name: actbl1.h - ACPI 1.0 tables&n; *       $Revision: 15 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACTBL1_H__
DECL|macro|__ACTBL1_H__
mdefine_line|#define __ACTBL1_H__
macro_line|#pragma pack(1)
multiline_comment|/*************************************/
multiline_comment|/* ACPI Specification Rev 1.0 for    */
multiline_comment|/* the Root System Description Table */
multiline_comment|/*************************************/
r_typedef
r_struct
(brace
DECL|member|header
id|ACPI_TABLE_HEADER
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
multiline_comment|/* Array of pointers to other */
multiline_comment|/* ACPI tables */
DECL|typedef|RSDT_DESCRIPTOR_REV1
)brace
id|RSDT_DESCRIPTOR_REV1
suffix:semicolon
multiline_comment|/***************************************/
multiline_comment|/* ACPI Specification Rev 1.0 for      */
multiline_comment|/* the Firmware ACPI Control Structure */
multiline_comment|/***************************************/
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
multiline_comment|/* ACPI OS waking vector */
DECL|member|global_lock
id|u32
id|global_lock
suffix:semicolon
multiline_comment|/* Global Lock */
DECL|member|S4_bios_f
id|u32
id|S4_bios_f
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Indicates if S4_bIOS support is present */
DECL|member|reserved1
id|u32
id|reserved1
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* must be 0 */
DECL|member|resverved3
id|u8
id|resverved3
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* reserved - must be zero */
DECL|typedef|FACS_DESCRIPTOR_REV1
)brace
id|FACS_DESCRIPTOR_REV1
suffix:semicolon
multiline_comment|/************************************/
multiline_comment|/* ACPI Specification Rev 1.0 for   */
multiline_comment|/* the Fixed ACPI Description Table */
multiline_comment|/************************************/
r_typedef
r_struct
(brace
DECL|member|header
id|ACPI_TABLE_HEADER
id|header
suffix:semicolon
multiline_comment|/* table header */
DECL|member|firmware_ctrl
id|u32
id|firmware_ctrl
suffix:semicolon
multiline_comment|/* Physical address of FACS */
DECL|member|dsdt
id|u32
id|dsdt
suffix:semicolon
multiline_comment|/* Physical address of DSDT */
DECL|member|model
id|u8
id|model
suffix:semicolon
multiline_comment|/* System Interrupt Model */
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
multiline_comment|/* reserved */
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
DECL|member|S4_bios_req
id|u8
id|S4_bios_req
suffix:semicolon
multiline_comment|/* Value to write to SMI CMD to enter S4_bIOS state */
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
multiline_comment|/* reserved - must be zero */
DECL|member|pm1a_evt_blk
id|u32
id|pm1a_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1a Acpi_event Reg Blk */
DECL|member|pm1b_evt_blk
id|u32
id|pm1b_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1b Acpi_event Reg Blk */
DECL|member|pm1a_cnt_blk
id|u32
id|pm1a_cnt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1a Control Reg Blk */
DECL|member|pm1b_cnt_blk
id|u32
id|pm1b_cnt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1b Control Reg Blk */
DECL|member|pm2_cnt_blk
id|u32
id|pm2_cnt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 2 Control Reg Blk */
DECL|member|pm_tmr_blk
id|u32
id|pm_tmr_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt Timer Ctrl Reg Blk */
DECL|member|gpe0blk
id|u32
id|gpe0blk
suffix:semicolon
multiline_comment|/* Port addr of General Purpose Acpi_event 0 Reg Blk */
DECL|member|gpe1_blk
id|u32
id|gpe1_blk
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
DECL|member|reserved3
id|u8
id|reserved3
suffix:semicolon
multiline_comment|/* reserved */
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
multiline_comment|/* Size of area read to flush caches */
DECL|member|flush_stride
id|u16
id|flush_stride
suffix:semicolon
multiline_comment|/* Stride used in flushing caches */
DECL|member|duty_offset
id|u8
id|duty_offset
suffix:semicolon
multiline_comment|/* bit location of duty cycle field in p_cnt reg */
DECL|member|duty_width
id|u8
id|duty_width
suffix:semicolon
multiline_comment|/* bit width of duty cycle field in p_cnt reg */
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
DECL|member|reserved4
id|u8
id|reserved4
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|reserved4a
id|u8
id|reserved4a
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|reserved4b
id|u8
id|reserved4b
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
DECL|member|reserved5
id|u32
id|reserved5
suffix:colon
l_int|23
suffix:semicolon
multiline_comment|/* reserved - must be zero */
DECL|typedef|FADT_DESCRIPTOR_REV1
)brace
id|FADT_DESCRIPTOR_REV1
suffix:semicolon
macro_line|#pragma pack()
macro_line|#endif /* __ACTBL1_H__ */
eof
