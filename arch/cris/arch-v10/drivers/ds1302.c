multiline_comment|/*!***************************************************************************&n;*!&n;*! FILE NAME  : ds1302.c&n;*!&n;*! DESCRIPTION: Implements an interface for the DS1302 RTC through Etrax I/O&n;*!&n;*! Functions exported: ds1302_readreg, ds1302_writereg, ds1302_init&n;*!&n;*! $Log: ds1302.c,v $&n;*! Revision 1.13  2004/05/28 09:26:59  starvik&n;*! Modified I2C initialization to work in 2.6.&n;*!&n;*! Revision 1.12  2004/05/14 07:58:03  starvik&n;*! Merge of changes from 2.4&n;*!&n;*! Revision 1.10  2004/02/04 09:25:12  starvik&n;*! Merge of Linux 2.6.2&n;*!&n;*! Revision 1.9  2003/07/04 08:27:37  starvik&n;*! Merge of Linux 2.5.74&n;*!&n;*! Revision 1.8  2003/04/09 05:20:47  starvik&n;*! Merge of Linux 2.5.67&n;*!&n;*! Revision 1.6  2003/01/09 14:42:51  starvik&n;*! Merge of Linux 2.5.55&n;*!&n;*! Revision 1.4  2002/12/11 13:13:57  starvik&n;*! Added arch/ to v10 specific includes&n;*! Added fix from Linux 2.4 in serial.c (flush_to_flip_buffer)&n;*!&n;*! Revision 1.3  2002/11/20 11:56:10  starvik&n;*! Merge of Linux 2.5.48&n;*!&n;*! Revision 1.2  2002/11/18 13:16:06  starvik&n;*! Linux 2.5 port of latest 2.4 drivers&n;*!&n;*! Revision 1.15  2002/10/11 16:14:33  johana&n;*! Added CONFIG_ETRAX_DS1302_TRICKLE_CHARGE and initial setting of the&n;*! trcklecharge register.&n;*!&n;*! Revision 1.14  2002/10/10 12:15:38  magnusmn&n;*! Added support for having the RST signal on bit g0&n;*!&n;*! Revision 1.13  2002/05/29 15:16:08  johana&n;*! Removed unused variables.&n;*!&n;*! Revision 1.12  2002/04/10 15:35:25  johana&n;*! Moved probe function closer to init function and marked it __init.&n;*!&n;*! Revision 1.11  2001/06/14 12:35:52  jonashg&n;*! The ATA hack is back. It is unfortunately the only way to set g27 to output.&n;*!&n;*! Revision 1.9  2001/06/14 10:00:14  jonashg&n;*! No need for tempudelay to be inline anymore (had to adjust the usec to&n;*! loops conversion because of this to make it slow enough to be a udelay).&n;*!&n;*! Revision 1.8  2001/06/14 08:06:32  jonashg&n;*! Made tempudelay delay usecs (well, just a tad more).&n;*!&n;*! Revision 1.7  2001/06/13 14:18:11  jonashg&n;*! Only allow processes with SYS_TIME capability to set time and charge.&n;*!&n;*! Revision 1.6  2001/06/12 15:22:07  jonashg&n;*! * Made init function __init.&n;*! * Parameter to out_byte() is unsigned char.&n;*! * The magic number 42 has got a name.&n;*! * Removed comment about /proc (nothing is exported there).&n;*!&n;*! Revision 1.5  2001/06/12 14:35:13  jonashg&n;*! Gave the module a name and added it to printk&squot;s.&n;*!&n;*! Revision 1.4  2001/05/31 14:53:40  jonashg&n;*! Made tempudelay() inline so that the watchdog doesn&squot;t reset (see&n;*! function comment).&n;*!&n;*! Revision 1.3  2001/03/26 16:03:06  bjornw&n;*! Needs linux/config.h&n;*!&n;*! Revision 1.2  2001/03/20 19:42:00  bjornw&n;*! Use the ETRAX prefix on the DS1302 options&n;*!&n;*! Revision 1.1  2001/03/20 09:13:50  magnusmn&n;*! Linux 2.4 port&n;*!&n;*! Revision 1.10  2000/07/05 15:38:23  bjornw&n;*! Dont update kernel time when a RTC_SET_TIME is done&n;*!&n;*! Revision 1.9  2000/03/02 15:42:59  macce&n;*! * Hack to make RTC work on all 2100/2400&n;*!&n;*! Revision 1.8  2000/02/23 16:59:18  torbjore&n;*! added setup of R_GEN_CONFIG when RTC is connected to the generic port.&n;*!&n;*! Revision 1.7  2000/01/17 15:51:43  johana&n;*! Added RTC_SET_CHARGE ioctl to enable trickle charger.&n;*!&n;*! Revision 1.6  1999/10/27 13:19:47  bjornw&n;*! Added update_xtime_from_cmos which reads back the updated RTC into the kernel.&n;*! /dev/rtc calls it now.&n;*!&n;*! Revision 1.5  1999/10/27 12:39:37  bjornw&n;*! Disabled superuser check. Anyone can now set the time.&n;*!&n;*! Revision 1.4  1999/09/02 13:27:46  pkj&n;*! Added shadow for R_PORT_PB_CONFIG.&n;*! Renamed port_g_shadow to port_g_data_shadow.&n;*!&n;*! Revision 1.3  1999/09/02 08:28:06  pkj&n;*! Made it possible to select either port PB or the generic port for the RST&n;*! signal line to the DS1302 RTC.&n;*! Also make sure the RST bit is configured as output on Port PB (if used).&n;*!&n;*! Revision 1.2  1999/09/01 14:47:20  bjornw&n;*! Added support for /dev/rtc operations with ioctl RD_TIME and SET_TIME to read&n;*! and set the date. Register as major 121.&n;*!&n;*! Revision 1.1  1999/09/01 09:45:29  bjornw&n;*! Implemented a DS1302 RTC driver.&n;*!&n;*!&n;*! ---------------------------------------------------------------------------&n;*!&n;*! (C) Copyright 1999, 2000, 2001  Axis Communications AB, LUND, SWEDEN&n;*!&n;*! $Id: ds1302.c,v 1.13 2004/05/28 09:26:59 starvik Exp $&n;*!&n;*!***************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/bcd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/arch/svinto.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
DECL|macro|RTC_MAJOR_NR
mdefine_line|#define RTC_MAJOR_NR 121 /* local major, change later */
DECL|variable|ds1302_name
r_static
r_const
r_char
id|ds1302_name
(braket
)braket
op_assign
l_string|&quot;ds1302&quot;
suffix:semicolon
multiline_comment|/* The DS1302 might be connected to different bits on different products. &n; * It has three signals - SDA, SCL and RST. RST and SCL are always outputs,&n; * but SDA can have a selected direction.&n; * For now, only PORT_PB is hardcoded.&n; */
multiline_comment|/* The RST bit may be on either the Generic Port or Port PB. */
macro_line|#ifdef CONFIG_ETRAX_DS1302_RST_ON_GENERIC_PORT
DECL|macro|TK_RST_OUT
mdefine_line|#define TK_RST_OUT(x) REG_SHADOW_SET(R_PORT_G_DATA,  port_g_data_shadow,  CONFIG_ETRAX_DS1302_RSTBIT, x)
DECL|macro|TK_RST_DIR
mdefine_line|#define TK_RST_DIR(x)
macro_line|#else
DECL|macro|TK_RST_OUT
mdefine_line|#define TK_RST_OUT(x) REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_DS1302_RSTBIT, x)
DECL|macro|TK_RST_DIR
mdefine_line|#define TK_RST_DIR(x) REG_SHADOW_SET(R_PORT_PB_DIR,  port_pb_dir_shadow,  CONFIG_ETRAX_DS1302_RSTBIT, x)
macro_line|#endif
DECL|macro|TK_SDA_OUT
mdefine_line|#define TK_SDA_OUT(x) REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_DS1302_SDABIT, x)
DECL|macro|TK_SCL_OUT
mdefine_line|#define TK_SCL_OUT(x) REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_DS1302_SCLBIT, x)
DECL|macro|TK_SDA_IN
mdefine_line|#define TK_SDA_IN()   ((*R_PORT_PB_READ &gt;&gt; CONFIG_ETRAX_DS1302_SDABIT) &amp; 1)
multiline_comment|/* 1 is out, 0 is in */
DECL|macro|TK_SDA_DIR
mdefine_line|#define TK_SDA_DIR(x) REG_SHADOW_SET(R_PORT_PB_DIR,  port_pb_dir_shadow,  CONFIG_ETRAX_DS1302_SDABIT, x)
DECL|macro|TK_SCL_DIR
mdefine_line|#define TK_SCL_DIR(x) REG_SHADOW_SET(R_PORT_PB_DIR,  port_pb_dir_shadow,  CONFIG_ETRAX_DS1302_SCLBIT, x)
multiline_comment|/*&n; * The reason for tempudelay and not udelay is that loops_per_usec&n; * (used in udelay) is not set when functions here are called from time.c &n; */
DECL|function|tempudelay
r_static
r_void
id|tempudelay
c_func
(paren
r_int
id|usecs
)paren
(brace
r_volatile
r_int
id|loops
suffix:semicolon
r_for
c_loop
(paren
id|loops
op_assign
id|usecs
op_star
l_int|12
suffix:semicolon
id|loops
OG
l_int|0
suffix:semicolon
id|loops
op_decrement
)paren
(brace
multiline_comment|/* nothing */
suffix:semicolon
)brace
)brace
multiline_comment|/* Send 8 bits. */
r_static
r_void
DECL|function|out_byte
id|out_byte
c_func
(paren
r_int
r_char
id|x
)paren
(brace
r_int
id|i
suffix:semicolon
id|TK_SDA_DIR
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|8
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)paren
(brace
multiline_comment|/* The chip latches incoming bits on the rising edge of SCL. */
id|TK_SCL_OUT
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|TK_SDA_OUT
c_func
(paren
id|x
op_amp
l_int|1
)paren
suffix:semicolon
id|tempudelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|TK_SCL_OUT
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|tempudelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|x
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|TK_SDA_DIR
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|in_byte
id|in_byte
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|x
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Read byte. Bits come LSB first, on the falling edge of SCL.&n;&t; * Assume SDA is in input direction already.&n;&t; */
id|TK_SDA_DIR
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|8
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)paren
(brace
id|TK_SCL_OUT
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|tempudelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|x
op_rshift_assign
l_int|1
suffix:semicolon
id|x
op_or_assign
(paren
id|TK_SDA_IN
c_func
(paren
)paren
op_lshift
l_int|7
)paren
suffix:semicolon
id|TK_SCL_OUT
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|tempudelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/* Prepares for a transaction by de-activating RST (active-low). */
r_static
r_void
DECL|function|start
id|start
c_func
(paren
r_void
)paren
(brace
id|TK_SCL_OUT
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|tempudelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|TK_RST_OUT
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|tempudelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|TK_RST_OUT
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Ends a transaction by taking RST active again. */
r_static
r_void
DECL|function|stop
id|stop
c_func
(paren
r_void
)paren
(brace
id|tempudelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|TK_RST_OUT
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Enable writing. */
r_static
r_void
DECL|function|ds1302_wenable
id|ds1302_wenable
c_func
(paren
r_void
)paren
(brace
id|start
c_func
(paren
)paren
suffix:semicolon
id|out_byte
c_func
(paren
l_int|0x8e
)paren
suffix:semicolon
multiline_comment|/* Write control register  */
id|out_byte
c_func
(paren
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable write protect bit 7 = 0 */
id|stop
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable writing. */
r_static
r_void
DECL|function|ds1302_wdisable
id|ds1302_wdisable
c_func
(paren
r_void
)paren
(brace
id|start
c_func
(paren
)paren
suffix:semicolon
id|out_byte
c_func
(paren
l_int|0x8e
)paren
suffix:semicolon
multiline_comment|/* Write control register  */
id|out_byte
c_func
(paren
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Disable write protect bit 7 = 0 */
id|stop
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Read a byte from the selected register in the DS1302. */
r_int
r_char
DECL|function|ds1302_readreg
id|ds1302_readreg
c_func
(paren
r_int
id|reg
)paren
(brace
r_int
r_char
id|x
suffix:semicolon
id|start
c_func
(paren
)paren
suffix:semicolon
id|out_byte
c_func
(paren
l_int|0x81
op_or
(paren
id|reg
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* read register */
id|x
op_assign
id|in_byte
c_func
(paren
)paren
suffix:semicolon
id|stop
c_func
(paren
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
multiline_comment|/* Write a byte to the selected register. */
r_void
DECL|function|ds1302_writereg
id|ds1302_writereg
c_func
(paren
r_int
id|reg
comma
r_int
r_char
id|val
)paren
(brace
macro_line|#ifndef CONFIG_ETRAX_RTC_READONLY
r_int
id|do_writereg
op_assign
l_int|1
suffix:semicolon
macro_line|#else
r_int
id|do_writereg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_eq
id|RTC_TRICKLECHARGER
)paren
id|do_writereg
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|do_writereg
)paren
(brace
id|ds1302_wenable
c_func
(paren
)paren
suffix:semicolon
id|start
c_func
(paren
)paren
suffix:semicolon
id|out_byte
c_func
(paren
l_int|0x80
op_or
(paren
id|reg
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/* write register */
id|out_byte
c_func
(paren
id|val
)paren
suffix:semicolon
id|stop
c_func
(paren
)paren
suffix:semicolon
id|ds1302_wdisable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|get_rtc_time
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|rtc_tm
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_sec
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_SECONDS
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_min
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MINUTES
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_hour
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_HOURS
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_mday
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_mon
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_MONTH
)paren
suffix:semicolon
id|rtc_tm-&gt;tm_year
op_assign
id|CMOS_READ
c_func
(paren
id|RTC_YEAR
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_mday
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|rtc_tm-&gt;tm_year
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Account for differences between how the RTC uses the values&n;&t; * and how they are defined in a struct rtc_time;&n;&t; */
r_if
c_cond
(paren
id|rtc_tm-&gt;tm_year
op_le
l_int|69
)paren
id|rtc_tm-&gt;tm_year
op_add_assign
l_int|100
suffix:semicolon
id|rtc_tm-&gt;tm_mon
op_decrement
suffix:semicolon
)brace
DECL|variable|days_in_mo
r_static
r_int
r_char
id|days_in_mo
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|28
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
multiline_comment|/* ioctl that supports RTC_RD_TIME and RTC_SET_TIME (read and set time/date). */
r_static
r_int
DECL|function|rtc_ioctl
id|rtc_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_RD_TIME
suffix:colon
multiline_comment|/* read the time/date from RTC&t;*/
(brace
r_struct
id|rtc_time
id|rtc_tm
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|rtc_tm
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
suffix:semicolon
id|get_rtc_time
c_func
(paren
op_amp
id|rtc_tm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
op_amp
id|rtc_tm
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|RTC_SET_TIME
suffix:colon
multiline_comment|/* set the RTC */
(brace
r_struct
id|rtc_time
id|rtc_tm
suffix:semicolon
r_int
r_char
id|mon
comma
id|day
comma
id|hrs
comma
id|min
comma
id|sec
comma
id|leap_yr
suffix:semicolon
r_int
r_int
id|yrs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rtc_tm
comma
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|yrs
op_assign
id|rtc_tm.tm_year
op_plus
l_int|1900
suffix:semicolon
id|mon
op_assign
id|rtc_tm.tm_mon
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* tm_mon starts at zero */
id|day
op_assign
id|rtc_tm.tm_mday
suffix:semicolon
id|hrs
op_assign
id|rtc_tm.tm_hour
suffix:semicolon
id|min
op_assign
id|rtc_tm.tm_min
suffix:semicolon
id|sec
op_assign
id|rtc_tm.tm_sec
suffix:semicolon
r_if
c_cond
(paren
(paren
id|yrs
OL
l_int|1970
)paren
op_logical_or
(paren
id|yrs
OG
l_int|2069
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|leap_yr
op_assign
(paren
(paren
op_logical_neg
(paren
id|yrs
op_mod
l_int|4
)paren
op_logical_and
(paren
id|yrs
op_mod
l_int|100
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|yrs
op_mod
l_int|400
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mon
OG
l_int|12
)paren
op_logical_or
(paren
id|day
op_eq
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|day
OG
(paren
id|days_in_mo
(braket
id|mon
)braket
op_plus
(paren
(paren
id|mon
op_eq
l_int|2
)paren
op_logical_and
id|leap_yr
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hrs
op_ge
l_int|24
)paren
op_logical_or
(paren
id|min
op_ge
l_int|60
)paren
op_logical_or
(paren
id|sec
op_ge
l_int|60
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|yrs
op_ge
l_int|2000
)paren
id|yrs
op_sub_assign
l_int|2000
suffix:semicolon
multiline_comment|/* RTC (0, 1, ... 69) */
r_else
id|yrs
op_sub_assign
l_int|1900
suffix:semicolon
multiline_comment|/* RTC (70, 71, ... 99) */
id|BIN_TO_BCD
c_func
(paren
id|sec
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|min
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|hrs
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|day
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|mon
)paren
suffix:semicolon
id|BIN_TO_BCD
c_func
(paren
id|yrs
)paren
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|yrs
comma
id|RTC_YEAR
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|mon
comma
id|RTC_MONTH
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|day
comma
id|RTC_DAY_OF_MONTH
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|hrs
comma
id|RTC_HOURS
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|min
comma
id|RTC_MINUTES
)paren
suffix:semicolon
id|CMOS_WRITE
c_func
(paren
id|sec
comma
id|RTC_SECONDS
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Notice that at this point, the RTC is updated but&n;&t;&t;&t; * the kernel is still running with the old time.&n;&t;&t;&t; * You need to set that separately with settimeofday&n;&t;&t;&t; * or adjtimex.&n;&t;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|RTC_SET_CHARGE
suffix:colon
multiline_comment|/* set the RTC TRICKLE CHARGE register */
(brace
r_int
id|tcs_val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|tcs_val
comma
(paren
r_int
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|tcs_val
op_assign
id|RTC_TCR_PATTERN
op_or
(paren
id|tcs_val
op_amp
l_int|0x0F
)paren
suffix:semicolon
id|ds1302_writereg
c_func
(paren
id|RTC_TRICKLECHARGER
comma
id|tcs_val
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|RTC_VLOW_RD
suffix:colon
(brace
multiline_comment|/* TODO:&n;&t;&t;&t; * Implement voltage low detection support&n;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DS1302: RTC Voltage Low detection&quot;
l_string|&quot; is not supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|RTC_VLOW_SET
suffix:colon
(brace
multiline_comment|/* TODO:&n;&t;&t;&t; * Nothing to do since Voltage Low detection is not supported&n;&t;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|print_rtc_status
id|print_rtc_status
c_func
(paren
r_void
)paren
(brace
r_struct
id|rtc_time
id|tm
suffix:semicolon
id|get_rtc_time
c_func
(paren
op_amp
id|tm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * There is no way to tell if the luser has the RTC set for local&n;&t; * time or for Universal Standard Time (GMT). Probably local though.&n;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;rtc_time&bslash;t: %02d:%02d:%02d&bslash;n&quot;
comma
id|tm.tm_hour
comma
id|tm.tm_min
comma
id|tm.tm_sec
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;rtc_date&bslash;t: %04d-%02d-%02d&bslash;n&quot;
comma
id|tm.tm_year
op_plus
l_int|1900
comma
id|tm.tm_mon
op_plus
l_int|1
comma
id|tm.tm_mday
)paren
suffix:semicolon
)brace
multiline_comment|/* The various file operations we support. */
DECL|variable|rtc_fops
r_static
r_struct
id|file_operations
id|rtc_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|rtc_ioctl
comma
)brace
suffix:semicolon
multiline_comment|/* Probe for the chip by writing something to its RAM and try reading it back. */
DECL|macro|MAGIC_PATTERN
mdefine_line|#define MAGIC_PATTERN 0x42
r_static
r_int
id|__init
DECL|function|ds1302_probe
id|ds1302_probe
c_func
(paren
r_void
)paren
(brace
r_int
id|retval
comma
id|res
suffix:semicolon
id|TK_RST_DIR
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|TK_SCL_DIR
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|TK_SDA_DIR
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Try to talk to timekeeper. */
id|ds1302_wenable
c_func
(paren
)paren
suffix:semicolon
id|start
c_func
(paren
)paren
suffix:semicolon
id|out_byte
c_func
(paren
l_int|0xc0
)paren
suffix:semicolon
multiline_comment|/* write RAM byte 0 */
id|out_byte
c_func
(paren
id|MAGIC_PATTERN
)paren
suffix:semicolon
multiline_comment|/* write something magic */
id|start
c_func
(paren
)paren
suffix:semicolon
id|out_byte
c_func
(paren
l_int|0xc1
)paren
suffix:semicolon
multiline_comment|/* read RAM byte 0 */
r_if
c_cond
(paren
(paren
id|res
op_assign
id|in_byte
c_func
(paren
)paren
)paren
op_eq
id|MAGIC_PATTERN
)paren
(brace
id|stop
c_func
(paren
)paren
suffix:semicolon
id|ds1302_wdisable
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: RTC found.&bslash;n&quot;
comma
id|ds1302_name
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: SDA, SCL, RST on PB%i, PB%i, %s%i&bslash;n&quot;
comma
id|ds1302_name
comma
id|CONFIG_ETRAX_DS1302_SDABIT
comma
id|CONFIG_ETRAX_DS1302_SCLBIT
comma
macro_line|#ifdef CONFIG_ETRAX_DS1302_RST_ON_GENERIC_PORT
l_string|&quot;GENIO&quot;
comma
macro_line|#else
l_string|&quot;PB&quot;
comma
macro_line|#endif
id|CONFIG_ETRAX_DS1302_RSTBIT
)paren
suffix:semicolon
id|print_rtc_status
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|stop
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Just probe for the RTC and register the device to handle the ioctl needed. */
r_int
id|__init
DECL|function|ds1302_init
id|ds1302_init
c_func
(paren
r_void
)paren
(brace
id|i2c_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ds1302_probe
c_func
(paren
)paren
)paren
(brace
macro_line|#ifdef CONFIG_ETRAX_DS1302_RST_ON_GENERIC_PORT
macro_line|#if CONFIG_ETRAX_DS1302_RSTBIT == 27
multiline_comment|/*&n;&t;&t; * The only way to set g27 to output is to enable ATA.&n;&t;&t; *&n;&t;&t; * Make sure that R_GEN_CONFIG is setup correct.&n;&t;&t; */
id|genconfig_shadow
op_assign
(paren
(paren
id|genconfig_shadow
op_amp
op_complement
id|IO_MASK
c_func
(paren
id|R_GEN_CONFIG
comma
id|ata
)paren
)paren
op_or
(paren
id|IO_STATE
c_func
(paren
id|R_GEN_CONFIG
comma
id|ata
comma
id|select
)paren
)paren
)paren
suffix:semicolon
op_star
id|R_GEN_CONFIG
op_assign
id|genconfig_shadow
suffix:semicolon
macro_line|#elif CONFIG_ETRAX_DS1302_RSTBIT == 0
multiline_comment|/* Set the direction of this bit to out. */
id|genconfig_shadow
op_assign
(paren
(paren
id|genconfig_shadow
op_amp
op_complement
id|IO_MASK
c_func
(paren
id|R_GEN_CONFIG
comma
id|g0dir
)paren
)paren
op_or
(paren
id|IO_STATE
c_func
(paren
id|R_GEN_CONFIG
comma
id|g0dir
comma
id|out
)paren
)paren
)paren
suffix:semicolon
op_star
id|R_GEN_CONFIG
op_assign
id|genconfig_shadow
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|ds1302_probe
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: RTC not found.&bslash;n&quot;
comma
id|ds1302_name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: RTC not found.&bslash;n&quot;
comma
id|ds1302_name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Initialise trickle charger */
id|ds1302_writereg
c_func
(paren
id|RTC_TRICKLECHARGER
comma
id|RTC_TCR_PATTERN
op_or
(paren
id|CONFIG_ETRAX_DS1302_TRICKLE_CHARGE
op_amp
l_int|0x0F
)paren
)paren
suffix:semicolon
multiline_comment|/* Start clock by resetting CLOCK_HALT */
id|ds1302_writereg
c_func
(paren
id|RTC_SECONDS
comma
(paren
id|ds1302_readreg
c_func
(paren
id|RTC_SECONDS
)paren
op_amp
l_int|0x7F
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ds1302_register
r_static
r_int
id|__init
id|ds1302_register
c_func
(paren
r_void
)paren
(brace
id|ds1302_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|RTC_MAJOR_NR
comma
id|ds1302_name
comma
op_amp
id|rtc_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unable to get major %d for rtc&bslash;n&quot;
comma
id|ds1302_name
comma
id|RTC_MAJOR_NR
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ds1302_register
id|module_init
c_func
(paren
id|ds1302_register
)paren
suffix:semicolon
eof
