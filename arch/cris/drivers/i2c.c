multiline_comment|/*!***************************************************************************&n;*!&n;*! FILE NAME  : i2c.c&n;*!&n;*! DESCRIPTION: implements an interface for IIC/I2C, both directly from other&n;*!              kernel modules (i2c_writereg/readreg) and from userspace using&n;*!              ioctl()&squot;s&n;*!&n;*! Nov 30 1998  Torbjorn Eliasson  Initial version.&n;*!              Bjorn Wesen        Elinux kernel version.&n;*! Jan 14 2000  Johan Adolfsson    Fixed PB shadow register stuff - &n;*!                                 don&squot;t use PB_I2C if DS1302 uses same bits,&n;*!                                 use PB.&n;*! $Log: i2c.c,v $&n;*! Revision 1.1.1.1  2001/12/17 13:59:27  bjornw&n;*! Import of Linux 2.5.1&n;*!&n;*! Revision 1.7  2001/04/04 13:11:36  markusl&n;*! Updated according to review remarks&n;*!&n;*! Revision 1.6  2001/03/19 12:43:00  markusl&n;*! Made some symbols unstatic (used by the eeprom driver)&n;*!&n;*! Revision 1.5  2001/02/27 13:52:48  bjornw&n;*! malloc.h -&gt; slab.h&n;*!&n;*! Revision 1.4  2001/02/15 07:17:40  starvik&n;*! Corrected usage if port_pb_i2c_shadow&n;*!&n;*! Revision 1.3  2001/01/26 17:55:13  bjornw&n;*! * Made I2C_USES_PB_NOT_PB_I2C a CONFIG option instead of assigning it&n;*!   magically. Config.in needs to set it for the options that need it, like&n;*!   Dallas 1302 support. Actually, it should be default since it screws up&n;*!   the PB bits even if you don&squot;t use I2C..&n;*! * Include linux/config.h to get the above&n;*!&n;*! Revision 1.2  2001/01/18 15:49:30  bjornw&n;*! 2.4 port of I2C including some cleanups (untested of course)&n;*!&n;*! Revision 1.1  2001/01/18 15:35:25  bjornw&n;*! Verbatim copy of the Etrax i2c driver, 2.0 elinux version&n;*!&n;*!&n;*! ---------------------------------------------------------------------------&n;*!&n;*! (C) Copyright 1999, 2000, 2001 Axis Communications AB, LUND, SWEDEN&n;*!&n;*!***************************************************************************/
multiline_comment|/* $Id: i2c.c,v 1.1.1.1 2001/12/17 13:59:27 bjornw Exp $ */
multiline_comment|/****************** INCLUDE FILES SECTION ***********************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/etraxi2c.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/svinto.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &quot;i2c.h&quot;
multiline_comment|/****************** I2C DEFINITION SECTION *************************/
DECL|macro|D
mdefine_line|#define D(x)
DECL|macro|I2C_MAJOR
mdefine_line|#define I2C_MAJOR 123  /* LOCAL/EXPERIMENTAL */
DECL|variable|i2c_name
r_static
r_const
r_char
id|i2c_name
(braket
)braket
op_assign
l_string|&quot;i2c&quot;
suffix:semicolon
DECL|macro|CLOCK_LOW_TIME
mdefine_line|#define CLOCK_LOW_TIME            8
DECL|macro|CLOCK_HIGH_TIME
mdefine_line|#define CLOCK_HIGH_TIME           8
DECL|macro|START_CONDITION_HOLD_TIME
mdefine_line|#define START_CONDITION_HOLD_TIME 8
DECL|macro|STOP_CONDITION_HOLD_TIME
mdefine_line|#define STOP_CONDITION_HOLD_TIME  8
DECL|macro|ENABLE_OUTPUT
mdefine_line|#define ENABLE_OUTPUT 0x01
DECL|macro|ENABLE_INPUT
mdefine_line|#define ENABLE_INPUT 0x00
DECL|macro|I2C_CLOCK_HIGH
mdefine_line|#define I2C_CLOCK_HIGH 1
DECL|macro|I2C_CLOCK_LOW
mdefine_line|#define I2C_CLOCK_LOW 0
DECL|macro|I2C_DATA_HIGH
mdefine_line|#define I2C_DATA_HIGH 1
DECL|macro|I2C_DATA_LOW
mdefine_line|#define I2C_DATA_LOW 0
macro_line|#if 0
multiline_comment|/* TODO: fix this so the CONFIG_ETRAX_I2C_USES... is set in Config.in instead */
macro_line|#if defined(CONFIG_DS1302) &amp;&amp; (CONFIG_DS1302_SDABIT==0) &amp;&amp; &bslash;&n;           (CONFIG_DS1302_SCLBIT == 1)
mdefine_line|#define CONFIG_ETRAX_I2C_USES_PB_NOT_PB_I2C
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_I2C_USES_PB_NOT_PB_I2C
multiline_comment|/* Use PB and not PB_I2C */
DECL|macro|SDABIT
mdefine_line|#define SDABIT 0
DECL|macro|SCLBIT
mdefine_line|#define SCLBIT 1
DECL|macro|i2c_enable
mdefine_line|#define i2c_enable() 
DECL|macro|i2c_disable
mdefine_line|#define i2c_disable() 
multiline_comment|/* enable or disable output-enable, to select output or input on the i2c bus */
DECL|macro|i2c_dir_out
mdefine_line|#define i2c_dir_out() &bslash;&n;  REG_SHADOW_SET(R_PORT_PB_DIR, port_pb_dir_shadow, SDABIT, 1)
DECL|macro|i2c_dir_in
mdefine_line|#define i2c_dir_in()  &bslash;&n;  REG_SHADOW_SET(R_PORT_PB_DIR, port_pb_dir_shadow, SDABIT, 0)
multiline_comment|/* control the i2c clock and data signals */
DECL|macro|i2c_clk
mdefine_line|#define i2c_clk(x) &bslash;&n;  REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, SCLBIT, x)
DECL|macro|i2c_data
mdefine_line|#define i2c_data(x) &bslash;&n;  REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, SDABIT, x)
multiline_comment|/* read a bit from the i2c interface */
DECL|macro|i2c_getbit
mdefine_line|#define i2c_getbit() (*R_PORT_PB_READ &amp; (1 &lt;&lt; SDABIT))
macro_line|#else
multiline_comment|/* enable or disable the i2c interface */
DECL|macro|i2c_enable
mdefine_line|#define i2c_enable() *R_PORT_PB_I2C = (port_pb_i2c_shadow |= IO_MASK(R_PORT_PB_I2C, i2c_en))
DECL|macro|i2c_disable
mdefine_line|#define i2c_disable() *R_PORT_PB_I2C = (port_pb_i2c_shadow &amp;= ~IO_MASK(R_PORT_PB_I2C, i2c_en))
multiline_comment|/* enable or disable output-enable, to select output or input on the i2c bus */
DECL|macro|i2c_dir_out
mdefine_line|#define i2c_dir_out() *R_PORT_PB_I2C = (port_pb_i2c_shadow &amp;= ~IO_MASK(R_PORT_PB_I2C, i2c_oe_))
DECL|macro|i2c_dir_in
mdefine_line|#define i2c_dir_in() *R_PORT_PB_I2C = (port_pb_i2c_shadow |= IO_MASK(R_PORT_PB_I2C, i2c_oe_))
multiline_comment|/* control the i2c clock and data signals */
DECL|macro|i2c_clk
mdefine_line|#define i2c_clk(x) *R_PORT_PB_I2C = (port_pb_i2c_shadow = (port_pb_i2c_shadow &amp; &bslash;&n;       ~IO_MASK(R_PORT_PB_I2C, i2c_clk)) | IO_FIELD(R_PORT_PB_I2C, i2c_clk, (x)))
DECL|macro|i2c_data
mdefine_line|#define i2c_data(x) *R_PORT_PB_I2C = (port_pb_i2c_shadow = (port_pb_i2c_shadow &amp; &bslash;&n;       ~IO_MASK(R_PORT_PB_I2C, i2c_d)) | IO_FIELD(R_PORT_PB_I2C, i2c_d, (x)))
multiline_comment|/* read a bit from the i2c interface */
DECL|macro|i2c_getbit
mdefine_line|#define i2c_getbit() (*R_PORT_PB_READ &amp; 0x1)
macro_line|#endif
multiline_comment|/* use the kernels delay routine */
DECL|macro|i2c_delay
mdefine_line|#define i2c_delay(usecs) udelay(usecs)
multiline_comment|/****************** FUNCTION DEFINITION SECTION *************************/
multiline_comment|/* generate i2c start condition */
r_void
DECL|function|i2c_start
id|i2c_start
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * SCL=1 SDA=1&n;&t; */
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|6
)paren
suffix:semicolon
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SCL=1 SDA=0&n;&t; */
id|i2c_data
c_func
(paren
id|I2C_DATA_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|START_CONDITION_HOLD_TIME
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SCL=0 SDA=0&n;&t; */
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
)brace
multiline_comment|/* generate i2c stop condition */
r_void
DECL|function|i2c_stop
id|i2c_stop
c_func
(paren
r_void
)paren
(brace
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SCL=0 SDA=0&n;&t; */
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_data
c_func
(paren
id|I2C_DATA_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_star
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SCL=1 SDA=0&n;&t; */
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_star
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * SCL=1 SDA=1&n;&t; */
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|STOP_CONDITION_HOLD_TIME
)paren
suffix:semicolon
id|i2c_dir_in
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* write a byte to the i2c interface */
r_void
DECL|function|i2c_outbyte
id|i2c_outbyte
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
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|x
op_amp
l_int|0x80
)paren
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
r_else
id|i2c_data
c_func
(paren
id|I2C_DATA_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_div
l_int|2
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_div
l_int|2
)paren
suffix:semicolon
id|x
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|i2c_data
c_func
(paren
id|I2C_DATA_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * enable input&n;&t; */
id|i2c_dir_in
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* read a byte from the i2c interface */
r_int
r_char
DECL|function|i2c_inbyte
id|i2c_inbyte
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|aBitByte
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|iaa
suffix:semicolon
multiline_comment|/*&n;&t; * enable output&n;&t; */
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Release data bus by setting&n;&t; * data high&n;&t; */
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * enable input&n;&t; */
id|i2c_dir_in
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Use PORT PB instead of I2C&n;&t; * for input. (I2C not working)&n;&t; */
id|i2c_clk
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i2c_data
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * get bits&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * low clock period&n;&t;&t; */
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * switch off I2C&n;&t;&t; */
id|i2c_data
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i2c_disable
c_func
(paren
)paren
suffix:semicolon
id|i2c_dir_in
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * wait before getting bit&n;&t;&t; */
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|2
)paren
suffix:semicolon
id|aBitByte
op_assign
(paren
id|aBitByte
op_lshift
l_int|1
)paren
suffix:semicolon
id|iaa
op_assign
id|i2c_getbit
c_func
(paren
)paren
suffix:semicolon
id|aBitByte
op_assign
id|aBitByte
op_or
id|iaa
suffix:semicolon
multiline_comment|/*&n;&t;&t; * wait&n;&t;&t; */
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * end clock puls&n;&t;&t; */
id|i2c_enable
c_func
(paren
)paren
suffix:semicolon
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * low clock period&n;&t;&t; */
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_div
l_int|2
)paren
suffix:semicolon
)brace
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
r_return
id|aBitByte
suffix:semicolon
)brace
multiline_comment|/*#---------------------------------------------------------------------------&n;*#&n;*# FUNCTION NAME: i2c_getack&n;*#&n;*# DESCRIPTION  : checks if ack was received from ic2&n;*#&n;*#--------------------------------------------------------------------------*/
r_int
DECL|function|i2c_getack
id|i2c_getack
c_func
(paren
r_void
)paren
(brace
r_int
id|ack
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * enable output&n;&t; */
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Release data bus by setting&n;&t; * data high&n;&t; */
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * enable input&n;&t; */
id|i2c_dir_in
c_func
(paren
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * generate ACK clock pulse&n;&t; */
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Use PORT PB instead of I2C&n;&t; * for input. (I2C not working)&n;&t; */
id|i2c_clk
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i2c_data
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * switch off I2C&n;&t; */
id|i2c_data
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|i2c_disable
c_func
(paren
)paren
suffix:semicolon
id|i2c_dir_in
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * now wait for ack&n;&t; */
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check for ack&n;&t; */
r_if
c_cond
(paren
id|i2c_getbit
c_func
(paren
)paren
)paren
(brace
id|ack
op_assign
l_int|0
suffix:semicolon
)brace
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ack
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i2c_getbit
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* receiver pulld SDA low */
id|ack
op_assign
l_int|1
suffix:semicolon
)brace
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * end clock pulse&n;&t; */
id|i2c_enable
c_func
(paren
)paren
suffix:semicolon
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * enable output&n;&t; */
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * remove ACK clock pulse&n;&t; */
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_div
l_int|2
)paren
suffix:semicolon
r_return
id|ack
suffix:semicolon
)brace
multiline_comment|/*#---------------------------------------------------------------------------&n;*#&n;*# FUNCTION NAME: I2C::sendAck&n;*#&n;*# DESCRIPTION  : Send ACK on received data&n;*#&n;*#--------------------------------------------------------------------------*/
r_void
DECL|function|i2c_sendack
id|i2c_sendack
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * enable output&n;&t; */
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set ack pulse high&n;&t; */
id|i2c_data
c_func
(paren
id|I2C_DATA_LOW
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * generate clock pulse&n;&t; */
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
op_div
l_int|6
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
op_div
l_int|6
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * reset data out&n;&t; */
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
id|i2c_dir_in
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*#---------------------------------------------------------------------------&n;*#&n;*# FUNCTION NAME: i2c_writereg&n;*#&n;*# DESCRIPTION  : Writes a value to an I2C device&n;*#&n;*#--------------------------------------------------------------------------*/
r_int
DECL|function|i2c_writereg
id|i2c_writereg
c_func
(paren
r_int
r_char
id|theSlave
comma
r_int
r_char
id|theReg
comma
r_int
r_char
id|theValue
)paren
(brace
r_int
id|error
comma
id|cntr
op_assign
l_int|3
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_do
(brace
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we don&squot;t like to be interrupted&n;&t;&t; */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * generate start condition&n;&t;&t; */
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * dummy preamble&n;&t;&t; */
id|i2c_outbyte
c_func
(paren
l_int|0x01
)paren
suffix:semicolon
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
)paren
suffix:semicolon
multiline_comment|/* Dummy Acknowledge */
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
multiline_comment|/* Repeated Start Condition */
id|i2c_data
c_func
(paren
id|I2C_DATA_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * send slave address&n;&t;&t; */
id|i2c_outbyte
c_func
(paren
id|theSlave
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * wait for ack&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|error
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * now select register&n;&t;&t; */
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
id|theReg
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * now it&squot;s time to wait for ack&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|error
op_or_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * send register register data&n;&t;&t; */
id|i2c_outbyte
c_func
(paren
id|theValue
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * now it&squot;s time to wait for ack&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|error
op_or_assign
l_int|4
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * end byte stream&n;&t;&t; */
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * enable interrupt again&n;&t;&t; */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|error
op_logical_and
id|cntr
op_decrement
)paren
(brace
suffix:semicolon
)brace
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
r_return
op_minus
id|error
suffix:semicolon
)brace
multiline_comment|/*#---------------------------------------------------------------------------&n;*#&n;*# FUNCTION NAME: i2c_readreg&n;*#&n;*# DESCRIPTION  : Reads a value from the decoder registers.&n;*#&n;*#--------------------------------------------------------------------------*/
r_int
r_char
DECL|function|i2c_readreg
id|i2c_readreg
c_func
(paren
r_int
r_char
id|theSlave
comma
r_int
r_char
id|theReg
)paren
(brace
r_int
r_char
id|b
op_assign
l_int|0
suffix:semicolon
r_int
id|error
comma
id|cntr
op_assign
l_int|3
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_do
(brace
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we don&squot;t like to be interrupted&n;&t;&t; */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * generate start condition&n;&t;&t; */
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * dummy preamble&n;&t;&t; */
id|i2c_outbyte
c_func
(paren
l_int|0x01
)paren
suffix:semicolon
id|i2c_data
c_func
(paren
id|I2C_DATA_HIGH
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
)paren
suffix:semicolon
multiline_comment|/* Dummy Acknowledge */
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_HIGH
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
multiline_comment|/* Repeated Start Condition */
id|i2c_data
c_func
(paren
id|I2C_DATA_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_HIGH_TIME
)paren
suffix:semicolon
id|i2c_clk
c_func
(paren
id|I2C_CLOCK_LOW
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * send slave address&n;&t;&t; */
id|i2c_outbyte
c_func
(paren
id|theSlave
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * wait for ack&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|error
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * now select register&n;&t;&t; */
id|i2c_dir_out
c_func
(paren
)paren
suffix:semicolon
id|i2c_outbyte
c_func
(paren
id|theReg
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * now it&squot;s time to wait for ack&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|error
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * repeat start condition&n;&t;&t; */
id|i2c_delay
c_func
(paren
id|CLOCK_LOW_TIME
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * send slave address&n;&t;&t; */
id|i2c_outbyte
c_func
(paren
id|theSlave
op_or
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * wait for ack&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|i2c_getack
c_func
(paren
)paren
)paren
(brace
id|error
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * fetch register&n;&t;&t; */
id|b
op_assign
id|i2c_inbyte
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * send Ack&n;&t;&t; */
id|i2c_sendack
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * end sequence&n;&t;&t; */
id|i2c_stop
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * enable interrupt again&n;&t;&t; */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|error
op_logical_and
id|cntr
op_decrement
)paren
(brace
suffix:semicolon
)brace
r_return
id|b
suffix:semicolon
)brace
r_static
r_int
DECL|function|i2c_open
id|i2c_open
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
id|filp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|i2c_release
id|i2c_release
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
id|filp
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Main device API. ioctl&squot;s to write or read to/from i2c registers.&n; */
r_static
r_int
DECL|function|i2c_ioctl
id|i2c_ioctl
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
r_if
c_cond
(paren
id|_IOC_TYPE
c_func
(paren
id|cmd
)paren
op_ne
id|ETRAXI2C_IOCTYPE
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|_IOC_NR
c_func
(paren
id|cmd
)paren
)paren
(brace
r_case
id|I2C_WRITEREG
suffix:colon
multiline_comment|/* write to an i2c slave */
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2cw %d %d %d&bslash;n&quot;
comma
id|I2C_ARGSLAVE
c_func
(paren
id|arg
)paren
comma
id|I2C_ARGREG
c_func
(paren
id|arg
)paren
comma
id|I2C_ARGVALUE
c_func
(paren
id|arg
)paren
)paren
)paren
suffix:semicolon
r_return
id|i2c_writereg
c_func
(paren
id|I2C_ARGSLAVE
c_func
(paren
id|arg
)paren
comma
id|I2C_ARGREG
c_func
(paren
id|arg
)paren
comma
id|I2C_ARGVALUE
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
r_case
id|I2C_READREG
suffix:colon
(brace
r_int
r_char
id|val
suffix:semicolon
multiline_comment|/* read from an i2c slave */
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2cr %d %d &quot;
comma
id|I2C_ARGSLAVE
c_func
(paren
id|arg
)paren
comma
id|I2C_ARGREG
c_func
(paren
id|arg
)paren
)paren
)paren
suffix:semicolon
id|val
op_assign
id|i2c_readreg
c_func
(paren
id|I2C_ARGSLAVE
c_func
(paren
id|arg
)paren
comma
id|I2C_ARGREG
c_func
(paren
id|arg
)paren
)paren
suffix:semicolon
id|D
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;= %d&bslash;n&quot;
comma
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|i2c_fops
r_static
r_struct
id|file_operations
id|i2c_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|ioctl
suffix:colon
id|i2c_ioctl
comma
id|open
suffix:colon
id|i2c_open
comma
id|release
suffix:colon
id|i2c_release
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|i2c_init
id|i2c_init
c_func
(paren
r_void
)paren
(brace
r_int
id|res
suffix:semicolon
multiline_comment|/* Setup and enable the Port B I2C interface */
macro_line|#ifndef CONFIG_ETRAX_I2C_USES_PB_NOT_PB_I2C
op_star
id|R_PORT_PB_I2C
op_assign
id|port_pb_i2c_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_PORT_PB_I2C
comma
id|i2c_en
comma
id|on
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_PORT_PB_I2C
comma
id|i2c_d
comma
l_int|1
)paren
op_or
id|IO_FIELD
c_func
(paren
id|R_PORT_PB_I2C
comma
id|i2c_clk
comma
l_int|1
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PORT_PB_I2C
comma
id|i2c_oe_
comma
id|enable
)paren
suffix:semicolon
macro_line|#endif
id|port_pb_dir_shadow
op_and_assign
op_complement
id|IO_MASK
c_func
(paren
id|R_PORT_PB_DIR
comma
id|dir0
)paren
suffix:semicolon
id|port_pb_dir_shadow
op_and_assign
op_complement
id|IO_MASK
c_func
(paren
id|R_PORT_PB_DIR
comma
id|dir1
)paren
suffix:semicolon
op_star
id|R_PORT_PB_DIR
op_assign
(paren
id|port_pb_dir_shadow
op_or_assign
id|IO_STATE
c_func
(paren
id|R_PORT_PB_DIR
comma
id|dir0
comma
id|input
)paren
op_or
id|IO_STATE
c_func
(paren
id|R_PORT_PB_DIR
comma
id|dir1
comma
id|output
)paren
)paren
suffix:semicolon
multiline_comment|/* register char device */
id|res
op_assign
id|register_chrdev
c_func
(paren
id|I2C_MAJOR
comma
id|i2c_name
comma
op_amp
id|i2c_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c: couldn&squot;t get a major number.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;I2C driver v2.2, (c) 1999-2001 Axis Communications AB&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this makes sure that i2c_init is called during boot */
DECL|variable|i2c_init
id|module_init
c_func
(paren
id|i2c_init
)paren
suffix:semicolon
multiline_comment|/****************** END OF FILE i2c.c ********************************/
eof
