multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * Copyright (C) 2002 MontaVista Software Inc.&n; * Author: jsun@mvista.com or jsun@junsun.net&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/sibyte/64bit.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_smbus.h&gt;
multiline_comment|/* Xicor 1241 definitions */
multiline_comment|/*&n; * Register bits&n; */
DECL|macro|X1241REG_SR_BAT
mdefine_line|#define X1241REG_SR_BAT&t;0x80&t;&t;/* currently on battery power */
DECL|macro|X1241REG_SR_RWEL
mdefine_line|#define X1241REG_SR_RWEL 0x04&t;&t;/* r/w latch is enabled, can write RTC */
DECL|macro|X1241REG_SR_WEL
mdefine_line|#define X1241REG_SR_WEL 0x02&t;&t;/* r/w latch is unlocked, can enable r/w now */
DECL|macro|X1241REG_SR_RTCF
mdefine_line|#define X1241REG_SR_RTCF 0x01&t;&t;/* clock failed */
DECL|macro|X1241REG_BL_BP2
mdefine_line|#define X1241REG_BL_BP2 0x80&t;&t;/* block protect 2 */
DECL|macro|X1241REG_BL_BP1
mdefine_line|#define X1241REG_BL_BP1 0x40&t;&t;/* block protect 1 */
DECL|macro|X1241REG_BL_BP0
mdefine_line|#define X1241REG_BL_BP0 0x20&t;&t;/* block protect 0 */
DECL|macro|X1241REG_BL_WD1
mdefine_line|#define X1241REG_BL_WD1&t;0x10
DECL|macro|X1241REG_BL_WD0
mdefine_line|#define X1241REG_BL_WD0&t;0x08
DECL|macro|X1241REG_HR_MIL
mdefine_line|#define X1241REG_HR_MIL 0x80&t;&t;/* military time format */
multiline_comment|/*&n; * Register numbers&n; */
DECL|macro|X1241REG_BL
mdefine_line|#define X1241REG_BL&t;0x10&t;&t;/* block protect bits */
DECL|macro|X1241REG_INT
mdefine_line|#define X1241REG_INT&t;0x11&t;&t;/*  */
DECL|macro|X1241REG_SC
mdefine_line|#define X1241REG_SC&t;0x30&t;&t;/* Seconds */
DECL|macro|X1241REG_MN
mdefine_line|#define X1241REG_MN&t;0x31&t;&t;/* Minutes */
DECL|macro|X1241REG_HR
mdefine_line|#define X1241REG_HR&t;0x32&t;&t;/* Hours */
DECL|macro|X1241REG_DT
mdefine_line|#define X1241REG_DT&t;0x33&t;&t;/* Day of month */
DECL|macro|X1241REG_MO
mdefine_line|#define X1241REG_MO&t;0x34&t;&t;/* Month */
DECL|macro|X1241REG_YR
mdefine_line|#define X1241REG_YR&t;0x35&t;&t;/* Year */
DECL|macro|X1241REG_DW
mdefine_line|#define X1241REG_DW&t;0x36&t;&t;/* Day of Week */
DECL|macro|X1241REG_Y2K
mdefine_line|#define X1241REG_Y2K&t;0x37&t;&t;/* Year 2K */
DECL|macro|X1241REG_SR
mdefine_line|#define X1241REG_SR&t;0x3F&t;&t;/* Status register */
DECL|macro|X1241_CCR_ADDRESS
mdefine_line|#define X1241_CCR_ADDRESS&t;0x6F
DECL|macro|SMB_CSR
mdefine_line|#define SMB_CSR(reg) (KSEG1 | A_SMB_REGISTER(1, reg))
DECL|function|xicor_read
r_static
r_int
id|xicor_read
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
(paren
id|addr
op_rshift
l_int|8
)paren
op_amp
l_int|0x7
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
id|addr
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
(paren
id|V_SMB_ADDR
c_func
(paren
id|X1241_CCR_ADDRESS
)paren
op_or
id|V_SMB_TT_WR2BYTE
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
id|X1241_CCR_ADDRESS
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
DECL|function|xicor_write
r_static
r_int
id|xicor_write
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
id|addr
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
id|addr
op_amp
l_int|0xff
)paren
op_or
(paren
(paren
id|b
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
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
id|X1241_CCR_ADDRESS
)paren
op_or
id|V_SMB_TT_WR3BYTE
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
r_else
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|xicor_set_time
r_int
id|xicor_set_time
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
r_int
id|tmp
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
multiline_comment|/* unlock writes to the CCR */
id|xicor_write
c_func
(paren
id|X1241REG_SR
comma
id|X1241REG_SR_WEL
)paren
suffix:semicolon
id|xicor_write
c_func
(paren
id|X1241REG_SR
comma
id|X1241REG_SR_WEL
op_or
id|X1241REG_SR_RWEL
)paren
suffix:semicolon
multiline_comment|/* trivial ones */
id|tm.tm_sec
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_sec
)paren
suffix:semicolon
id|xicor_write
c_func
(paren
id|X1241REG_SC
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
id|xicor_write
c_func
(paren
id|X1241REG_MN
comma
id|tm.tm_min
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
id|xicor_write
c_func
(paren
id|X1241REG_DT
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
id|xicor_write
c_func
(paren
id|X1241REG_MO
comma
id|tm.tm_mon
)paren
suffix:semicolon
multiline_comment|/* year is split */
id|tmp
op_assign
id|tm.tm_year
op_div
l_int|100
suffix:semicolon
id|tm.tm_year
op_mod_assign
l_int|100
suffix:semicolon
id|xicor_write
c_func
(paren
id|X1241REG_YR
comma
id|tm.tm_year
)paren
suffix:semicolon
id|xicor_write
c_func
(paren
id|X1241REG_Y2K
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* hour is the most tricky one */
id|tmp
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_HR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|X1241REG_HR_MIL
)paren
(brace
multiline_comment|/* 24 hour format */
id|tm.tm_hour
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|tmp
op_assign
(paren
id|tmp
op_amp
op_complement
l_int|0x3f
)paren
op_or
(paren
id|tm.tm_hour
op_amp
l_int|0x3f
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 12 hour format, with 0x2 for pm */
id|tmp
op_assign
id|tmp
op_amp
op_complement
l_int|0x3f
suffix:semicolon
r_if
c_cond
(paren
id|tm.tm_hour
op_ge
l_int|12
)paren
(brace
id|tmp
op_or_assign
l_int|0x20
suffix:semicolon
id|tm.tm_hour
op_sub_assign
l_int|12
suffix:semicolon
)brace
id|tm.tm_hour
op_assign
id|BIN2BCD
c_func
(paren
id|tm.tm_hour
)paren
suffix:semicolon
id|tmp
op_or_assign
id|tm.tm_hour
suffix:semicolon
)brace
id|xicor_write
c_func
(paren
id|X1241REG_HR
comma
id|tmp
)paren
suffix:semicolon
id|xicor_write
c_func
(paren
id|X1241REG_SR
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xicor_get_time
r_int
r_int
id|xicor_get_time
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
comma
id|y2k
suffix:semicolon
id|sec
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_SC
)paren
suffix:semicolon
id|min
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_MN
)paren
suffix:semicolon
id|hour
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_HR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hour
op_amp
id|X1241REG_HR_MIL
)paren
(brace
id|hour
op_and_assign
l_int|0x3f
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|hour
op_amp
l_int|0x20
)paren
id|hour
op_assign
(paren
id|hour
op_amp
l_int|0xf
)paren
op_plus
l_int|0x12
suffix:semicolon
)brace
id|day
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_DT
)paren
suffix:semicolon
id|mon
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_MO
)paren
suffix:semicolon
id|year
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_YR
)paren
suffix:semicolon
id|y2k
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_Y2K
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
id|y2k
op_assign
id|BCD2BIN
c_func
(paren
id|y2k
)paren
suffix:semicolon
id|year
op_add_assign
(paren
id|y2k
op_star
l_int|100
)paren
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
DECL|function|xicor_probe
r_int
id|xicor_probe
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|xicor_read
c_func
(paren
id|X1241REG_SC
)paren
op_ne
op_minus
l_int|1
)paren
suffix:semicolon
)brace
eof
