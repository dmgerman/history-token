multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
multiline_comment|/*&n; * Time routines for the swarm board.  We pass all the hard stuff&n; * through to the sb1250 handling code.  Only thing we really keep&n; * track of here is what time of day we think it is.  And we don&squot;t&n; * really even do a good job of that...&n; */
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/sibyte/64bit.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_regs.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_smbus.h&gt;
DECL|variable|sec_bias
r_static
r_int
r_int
r_int
id|sec_bias
op_assign
l_int|0
suffix:semicolon
DECL|variable|usec_bias
r_static
r_int
r_int
id|usec_bias
op_assign
l_int|0
suffix:semicolon
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
multiline_comment|/*&n; * In order to set the CMOS clock precisely, set_rtc_mmss has to be&n; * called 500 ms after the second nowtime has started, because when&n; * nowtime is written into the registers of the CMOS clock, it will&n; * jump to the next second precisely 500 ms later. Check the Motorola&n; * MC146818A or Dallas DS12887 data sheet for details.&n; *&n; * BUG: This routine does not handle hour overflow properly; it just&n; *      sets the minutes. Usually you&squot;ll only notice that after reboot!&n; */
DECL|function|set_rtc_mmss
r_int
id|set_rtc_mmss
c_func
(paren
r_int
r_int
id|nowtime
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|real_seconds
comma
id|real_minutes
comma
id|cmos_minutes
suffix:semicolon
id|cmos_minutes
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_MN
)paren
suffix:semicolon
id|cmos_minutes
op_assign
id|BCD2BIN
c_func
(paren
id|cmos_minutes
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * since we&squot;re only adjusting minutes and seconds,&n;&t; * don&squot;t interfere with hour overflow. This avoids&n;&t; * messing with unknown time zones but requires your&n;&t; * RTC not to be off by more than 15 minutes&n;&t; */
id|real_seconds
op_assign
id|nowtime
op_mod
l_int|60
suffix:semicolon
id|real_minutes
op_assign
id|nowtime
op_div
l_int|60
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
op_plus
l_int|15
)paren
op_div
l_int|30
)paren
op_amp
l_int|1
)paren
id|real_minutes
op_add_assign
l_int|30
suffix:semicolon
multiline_comment|/* correct for half hour time zone */
id|real_minutes
op_mod_assign
l_int|60
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
r_if
c_cond
(paren
id|abs
c_func
(paren
id|real_minutes
op_minus
id|cmos_minutes
)paren
OL
l_int|30
)paren
(brace
id|real_seconds
op_assign
id|BIN2BCD
c_func
(paren
id|real_seconds
)paren
suffix:semicolon
id|real_minutes
op_assign
id|BIN2BCD
c_func
(paren
id|real_minutes
)paren
suffix:semicolon
id|xicor_write
c_func
(paren
id|X1241REG_SC
comma
id|real_seconds
)paren
suffix:semicolon
id|xicor_write
c_func
(paren
id|X1241REG_MN
comma
id|real_minutes
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;set_rtc_mmss: can&squot;t update from %d to %d&bslash;n&quot;
comma
id|cmos_minutes
comma
id|real_minutes
)paren
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|xicor_write
c_func
(paren
id|X1241REG_SR
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;set_rtc_mmss: %02d:%02d&bslash;n&quot;
comma
id|real_minutes
comma
id|real_seconds
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|get_swarm_time
r_static
r_int
r_int
id|__init
id|get_swarm_time
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
multiline_comment|/*&n; *  Bring up the timer at 100 Hz.&n; */
DECL|function|swarm_time_init
r_void
id|__init
id|swarm_time_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* Set up the scd general purpose timer 0 to cpu 0 */
id|sb1250_time_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Establish communication with the Xicor 1241 RTC */
multiline_comment|/* XXXKW how do I share the SMBus with the I2C subsystem? */
id|out64
c_func
(paren
id|K_SMB_FREQ_400KHZ
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_FREQ
)paren
)paren
suffix:semicolon
id|out64
c_func
(paren
l_int|0
comma
id|SMB_CSR
c_func
(paren
id|R_SMB_CONTROL
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|xicor_read
c_func
(paren
id|X1241REG_SR_RTCF
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;x1241: couldn&squot;t detect on SWARM SMBus 1&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|status
op_amp
id|X1241REG_SR_RTCF
)paren
id|printk
c_func
(paren
l_string|&quot;x1241: battery failed -- time is probably wrong&bslash;n&quot;
)paren
suffix:semicolon
id|write_seqlock_irqsave
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
id|xtime.tv_sec
op_assign
id|get_swarm_time
c_func
(paren
)paren
suffix:semicolon
id|xtime.tv_nsec
op_assign
l_int|0
suffix:semicolon
id|write_sequnlock_irqrestore
c_func
(paren
op_amp
id|xtime_lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
eof
