multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * Copyright (C) 2002 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute&t;it and/or modify it&n; * under  the terms of&t;the GNU General&t; Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; */
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/sibyte/64bit.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_smbus.h&gt;
multiline_comment|/* M41T81 definitions */
multiline_comment|/*&n; * Register bits&n; */
DECL|macro|M41T81REG_SC_ST
mdefine_line|#define M41T81REG_SC_ST&t;&t;0x80&t;&t;/* stop bit */
DECL|macro|M41T81REG_HR_CB
mdefine_line|#define M41T81REG_HR_CB&t;&t;0x40&t;&t;/* century bit */
DECL|macro|M41T81REG_HR_CEB
mdefine_line|#define M41T81REG_HR_CEB&t;0x80&t;&t;/* century enable bit */
DECL|macro|M41T81REG_CTL_S
mdefine_line|#define M41T81REG_CTL_S&t;&t;0x20&t;&t;/* sign bit */
DECL|macro|M41T81REG_CTL_FT
mdefine_line|#define M41T81REG_CTL_FT&t;0x40&t;&t;/* frequency test bit */
DECL|macro|M41T81REG_CTL_OUT
mdefine_line|#define M41T81REG_CTL_OUT&t;0x80&t;&t;/* output level */
DECL|macro|M41T81REG_WD_RB0
mdefine_line|#define M41T81REG_WD_RB0&t;0x01&t;&t;/* watchdog resolution bit 0 */
DECL|macro|M41T81REG_WD_RB1
mdefine_line|#define M41T81REG_WD_RB1&t;0x02&t;&t;/* watchdog resolution bit 1 */
DECL|macro|M41T81REG_WD_BMB0
mdefine_line|#define M41T81REG_WD_BMB0&t;0x04&t;&t;/* watchdog multiplier bit 0 */
DECL|macro|M41T81REG_WD_BMB1
mdefine_line|#define M41T81REG_WD_BMB1&t;0x08&t;&t;/* watchdog multiplier bit 1 */
DECL|macro|M41T81REG_WD_BMB2
mdefine_line|#define M41T81REG_WD_BMB2&t;0x10&t;&t;/* watchdog multiplier bit 2 */
DECL|macro|M41T81REG_WD_BMB3
mdefine_line|#define M41T81REG_WD_BMB3&t;0x20&t;&t;/* watchdog multiplier bit 3 */
DECL|macro|M41T81REG_WD_BMB4
mdefine_line|#define M41T81REG_WD_BMB4&t;0x40&t;&t;/* watchdog multiplier bit 4 */
DECL|macro|M41T81REG_AMO_ABE
mdefine_line|#define M41T81REG_AMO_ABE&t;0x20&t;&t;/* alarm in &quot;battery back-up mode&quot; enable bit */
DECL|macro|M41T81REG_AMO_SQWE
mdefine_line|#define M41T81REG_AMO_SQWE&t;0x40&t;&t;/* square wave enable */
DECL|macro|M41T81REG_AMO_AFE
mdefine_line|#define M41T81REG_AMO_AFE&t;0x80&t;&t;/* alarm flag enable flag */
DECL|macro|M41T81REG_ADT_RPT5
mdefine_line|#define M41T81REG_ADT_RPT5&t;0x40&t;&t;/* alarm repeat mode bit 5 */
DECL|macro|M41T81REG_ADT_RPT4
mdefine_line|#define M41T81REG_ADT_RPT4&t;0x80&t;&t;/* alarm repeat mode bit 4 */
DECL|macro|M41T81REG_AHR_RPT3
mdefine_line|#define M41T81REG_AHR_RPT3&t;0x80&t;&t;/* alarm repeat mode bit 3 */
DECL|macro|M41T81REG_AHR_HT
mdefine_line|#define M41T81REG_AHR_HT&t;0x40&t;&t;/* halt update bit */
DECL|macro|M41T81REG_AMN_RPT2
mdefine_line|#define M41T81REG_AMN_RPT2&t;0x80&t;&t;/* alarm repeat mode bit 2 */
DECL|macro|M41T81REG_ASC_RPT1
mdefine_line|#define M41T81REG_ASC_RPT1&t;0x80&t;&t;/* alarm repeat mode bit 1 */
DECL|macro|M41T81REG_FLG_AF
mdefine_line|#define M41T81REG_FLG_AF&t;0x40&t;&t;/* alarm flag (read only) */
DECL|macro|M41T81REG_FLG_WDF
mdefine_line|#define M41T81REG_FLG_WDF&t;0x80&t;&t;/* watchdog flag (read only) */
DECL|macro|M41T81REG_SQW_RS0
mdefine_line|#define M41T81REG_SQW_RS0&t;0x10&t;&t;/* sqw frequency bit 0 */
DECL|macro|M41T81REG_SQW_RS1
mdefine_line|#define M41T81REG_SQW_RS1&t;0x20&t;&t;/* sqw frequency bit 1 */
DECL|macro|M41T81REG_SQW_RS2
mdefine_line|#define M41T81REG_SQW_RS2&t;0x40&t;&t;/* sqw frequency bit 2 */
DECL|macro|M41T81REG_SQW_RS3
mdefine_line|#define M41T81REG_SQW_RS3&t;0x80&t;&t;/* sqw frequency bit 3 */
multiline_comment|/*&n; * Register numbers&n; */
DECL|macro|M41T81REG_TSC
mdefine_line|#define M41T81REG_TSC&t;0x00&t;&t;/* tenths/hundredths of second */
DECL|macro|M41T81REG_SC
mdefine_line|#define M41T81REG_SC&t;0x01&t;&t;/* seconds */
DECL|macro|M41T81REG_MN
mdefine_line|#define M41T81REG_MN&t;0x02&t;&t;/* minute */
DECL|macro|M41T81REG_HR
mdefine_line|#define M41T81REG_HR&t;0x03&t;&t;/* hour/century */
DECL|macro|M41T81REG_DY
mdefine_line|#define M41T81REG_DY&t;0x04&t;&t;/* day of week */
DECL|macro|M41T81REG_DT
mdefine_line|#define M41T81REG_DT&t;0x05&t;&t;/* date of month */
DECL|macro|M41T81REG_MO
mdefine_line|#define M41T81REG_MO&t;0x06&t;&t;/* month */
DECL|macro|M41T81REG_YR
mdefine_line|#define M41T81REG_YR&t;0x07&t;&t;/* year */
DECL|macro|M41T81REG_CTL
mdefine_line|#define M41T81REG_CTL&t;0x08&t;&t;/* control */
DECL|macro|M41T81REG_WD
mdefine_line|#define M41T81REG_WD&t;0x09&t;&t;/* watchdog */
DECL|macro|M41T81REG_AMO
mdefine_line|#define M41T81REG_AMO&t;0x0A&t;&t;/* alarm: month */
DECL|macro|M41T81REG_ADT
mdefine_line|#define M41T81REG_ADT&t;0x0B&t;&t;/* alarm: date */
DECL|macro|M41T81REG_AHR
mdefine_line|#define M41T81REG_AHR&t;0x0C&t;&t;/* alarm: hour */
DECL|macro|M41T81REG_AMN
mdefine_line|#define M41T81REG_AMN&t;0x0D&t;&t;/* alarm: minute */
DECL|macro|M41T81REG_ASC
mdefine_line|#define M41T81REG_ASC&t;0x0E&t;&t;/* alarm: second */
DECL|macro|M41T81REG_FLG
mdefine_line|#define M41T81REG_FLG&t;0x0F&t;&t;/* flags */
DECL|macro|M41T81REG_SQW
mdefine_line|#define M41T81REG_SQW&t;0x13&t;&t;/* square wave register */
DECL|macro|M41T81_CCR_ADDRESS
mdefine_line|#define M41T81_CCR_ADDRESS&t;0x68
DECL|macro|SMB_CSR
mdefine_line|#define SMB_CSR(reg) (KSEG1 | A_SMB_REGISTER(1, reg))
DECL|function|m41t81_read
r_static
r_int
id|m41t81_read
c_func
(paren
r_uint8
id|addr
)paren
(brace
r_while
c_loop
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
id|out64
c_func
(paren
id|addr
op_amp
l_int|0xff
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_CMD
)paren
)paren
suffix:semicolon
id|out64
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|M41T81_CCR_ADDRESS
)paren
op_or
id|V_SMB_TT_WR1BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_START
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
id|out64
c_func
(paren
(paren
id|V_SMB_ADDR
c_func
(paren
id|M41T81_CCR_ADDRESS
)paren
op_or
id|V_SMB_TT_RD1BYTE
)paren
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_START
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_ERROR
)paren
(brace
multiline_comment|/* Clear error bit by writing a 1 */
id|out64
c_func
(paren
id|M_SMB_ERROR
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_DATA
)paren
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
DECL|function|m41t81_write
r_static
r_int
id|m41t81_write
c_func
(paren
r_uint8
id|addr
comma
r_int
id|b
)paren
(brace
r_while
c_loop
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
id|out64
c_func
(paren
(paren
id|addr
op_amp
l_int|0xFF
)paren
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_CMD
)paren
)paren
suffix:semicolon
id|out64
c_func
(paren
(paren
id|b
op_amp
l_int|0xff
)paren
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_DATA
)paren
)paren
suffix:semicolon
id|out64
c_func
(paren
id|V_SMB_ADDR
c_func
(paren
id|M41T81_CCR_ADDRESS
)paren
op_or
id|V_SMB_TT_WR2BYTE
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_START
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_ERROR
)paren
(brace
multiline_comment|/* Clear error bit by writing a 1 */
id|out64
c_func
(paren
id|M_SMB_ERROR
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* read the same byte again to make sure it is written */
id|out64
c_func
(paren
id|V_SMB_ADDR
c_func
(paren
id|M41T81_CCR_ADDRESS
)paren
op_or
id|V_SMB_TT_RD1BYTE
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_START
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|in64
c_func
(paren
id|SMB_CSR
c_func
(paren
id|R_SMB_STATUS
)paren
)paren
op_amp
id|M_SMB_BUSY
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|m41t81_set_time
r_int
id|m41t81_set_time
c_func
(paren
r_int
r_int
id|t
)paren
(brace
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|to_tm
c_func
(paren
id|t
comma
op_amp
id|tm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note the write order matters as it ensures the correctness.&n;&t; * When we write sec, 10th sec is clear.  It is reasonable to &n;&t; * believe we should finish writing min within a second.&n;&t; */
id|tm.tm_sec
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_SC
comma
id|tm.tm_sec
)paren
suffix:semicolon
id|tm.tm_min
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_min
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_MN
comma
id|tm.tm_min
)paren
suffix:semicolon
id|tm.tm_hour
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|tm.tm_hour
op_assign
(paren
id|tm.tm_hour
op_amp
l_int|0x3f
)paren
op_or
(paren
id|m41t81_read
c_func
(paren
id|M41T81REG_HR
)paren
op_amp
l_int|0xc0
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_HR
comma
id|tm.tm_hour
)paren
suffix:semicolon
multiline_comment|/* tm_wday starts from 0 to 6 */
r_if
c_cond
(paren
id|tm.tm_wday
op_eq
l_int|0
)paren
id|tm.tm_wday
op_assign
l_int|7
suffix:semicolon
id|tm.tm_wday
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_wday
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_DY
comma
id|tm.tm_wday
)paren
suffix:semicolon
id|tm.tm_mday
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_mday
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_DT
comma
id|tm.tm_mday
)paren
suffix:semicolon
multiline_comment|/* tm_mon starts from 0, *ick* */
id|tm.tm_mon
op_increment
suffix:semicolon
id|tm.tm_mon
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_mon
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_MO
comma
id|tm.tm_mon
)paren
suffix:semicolon
multiline_comment|/* we don&squot;t do century, everything is beyond 2000 */
id|tm.tm_year
op_mod_assign
l_int|100
suffix:semicolon
id|tm.tm_year
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_year
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_YR
comma
id|tm.tm_year
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|m41t81_get_time
r_int
r_int
id|m41t81_get_time
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
suffix:semicolon
multiline_comment|/* &n;&t; * min is valid if two reads of sec are the same.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|sec
op_assign
id|m41t81_read
c_func
(paren
id|M41T81REG_SC
)paren
suffix:semicolon
id|min
op_assign
id|m41t81_read
c_func
(paren
id|M41T81REG_MN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sec
op_eq
id|m41t81_read
c_func
(paren
id|M41T81REG_SC
)paren
)paren
r_break
suffix:semicolon
)brace
id|hour
op_assign
id|m41t81_read
c_func
(paren
id|M41T81REG_HR
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|day
op_assign
id|m41t81_read
c_func
(paren
id|M41T81REG_DT
)paren
suffix:semicolon
id|mon
op_assign
id|m41t81_read
c_func
(paren
id|M41T81REG_MO
)paren
suffix:semicolon
id|year
op_assign
id|m41t81_read
c_func
(paren
id|M41T81REG_YR
)paren
suffix:semicolon
id|sec
op_assign
id|BCD2BIN
c_func
(paren
id|sec
)paren
suffix:semicolon
id|min
op_assign
id|BCD2BIN
c_func
(paren
id|min
)paren
suffix:semicolon
id|hour
op_assign
id|BCD2BIN
c_func
(paren
id|hour
)paren
suffix:semicolon
id|day
op_assign
id|BCD2BIN
c_func
(paren
id|day
)paren
suffix:semicolon
id|mon
op_assign
id|BCD2BIN
c_func
(paren
id|mon
)paren
suffix:semicolon
id|year
op_assign
id|BCD2BIN
c_func
(paren
id|year
)paren
suffix:semicolon
id|year
op_add_assign
l_int|2000
suffix:semicolon
r_return
id|mktime
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
)brace
DECL|function|m41t81_probe
r_int
id|m41t81_probe
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
multiline_comment|/* enable chip if it is not enabled yet */
id|tmp
op_assign
id|m41t81_read
c_func
(paren
id|M41T81REG_SC
)paren
suffix:semicolon
id|m41t81_write
c_func
(paren
id|M41T81REG_SC
comma
id|tmp
op_amp
l_int|0x7f
)paren
suffix:semicolon
r_return
(paren
id|m41t81_read
c_func
(paren
id|M41T81REG_SC
)paren
op_ne
op_minus
l_int|1
)paren
suffix:semicolon
)brace
eof
