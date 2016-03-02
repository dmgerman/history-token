multiline_comment|/******************************************************************************&n; *&n; * Name: actbl1.h - ACPI 1.0 tables&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACTBL1_H__
DECL|macro|__ACTBL1_H__
mdefine_line|#define __ACTBL1_H__
macro_line|#pragma pack(1)
multiline_comment|/*&n; * ACPI 1.0 Root System Description Table (RSDT)&n; */
DECL|struct|rsdt_descriptor_rev1
r_struct
id|rsdt_descriptor_rev1
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
multiline_comment|/* ACPI Table header */
DECL|member|table_offset_entry
id|u32
id|table_offset_entry
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Array of pointers to other */
multiline_comment|/* ACPI tables */
)brace
suffix:semicolon
multiline_comment|/*&n; * ACPI 1.0 Firmware ACPI Control Structure (FACS)&n; */
DECL|struct|facs_descriptor_rev1
r_struct
id|facs_descriptor_rev1
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* ACPI Signature */
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
multiline_comment|/* ACPI OS waking vector */
DECL|member|global_lock
id|u32
id|global_lock
suffix:semicolon
multiline_comment|/* Global Lock */
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
multiline_comment|/* Must be 0 */
DECL|member|resverved3
id|u8
id|resverved3
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
)brace
suffix:semicolon
multiline_comment|/*&n; * ACPI 1.0 Fixed ACPI Description Table (FADT)&n; */
DECL|struct|fadt_descriptor_rev1
r_struct
id|fadt_descriptor_rev1
(brace
DECL|member|header
r_struct
id|acpi_table_header
id|header
suffix:semicolon
multiline_comment|/* ACPI Table header */
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
multiline_comment|/* Reserved */
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
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
DECL|member|pm1a_evt_blk
id|u32
id|pm1a_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1a acpi_event Reg Blk */
DECL|member|pm1b_evt_blk
id|u32
id|pm1b_evt_blk
suffix:semicolon
multiline_comment|/* Port address of Power Mgt 1b acpi_event Reg Blk */
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
DECL|member|gpe0_blk
id|u32
id|gpe0_blk
suffix:semicolon
multiline_comment|/* Port addr of General Purpose acpi_event 0 Reg Blk */
DECL|member|gpe1_blk
id|u32
id|gpe1_blk
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
DECL|member|reserved3
id|u8
id|reserved3
suffix:semicolon
multiline_comment|/* Reserved */
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
multiline_comment|/* Bit location of duty cycle field in p_cnt reg */
DECL|member|duty_width
id|u8
id|duty_width
suffix:semicolon
multiline_comment|/* Bit width of duty cycle field in p_cnt reg */
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
DECL|member|reserved4
id|u8
id|reserved4
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|reserved4a
id|u8
id|reserved4a
suffix:semicolon
multiline_comment|/* Reserved */
DECL|member|reserved4b
id|u8
id|reserved4b
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
multiline_comment|/* The tmr_val width is 32 bits (0 = 24 bits) */
DECL|member|reserved5
id|u32
id|reserved5
suffix:colon
l_int|23
suffix:semicolon
multiline_comment|/* Reserved - must be zero */
)brace
suffix:semicolon
macro_line|#pragma pack()
macro_line|#endif /* __ACTBL1_H__ */
eof
