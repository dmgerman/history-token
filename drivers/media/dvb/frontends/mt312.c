multiline_comment|/* &n;    Driver for Zarlink MT312 Satellite Channel Decoder&n;&n;    Copyright (C) 2003 Andreas Oberritter &lt;obi@saftware.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    References:&n;    http://products.zarlink.com/product_profiles/MT312.htm&n;    http://products.zarlink.com/product_profiles/SL1935.htm&n;*/
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;dvb_frontend.h&quot;
macro_line|#include &quot;mt312.h&quot;
DECL|macro|I2C_ADDR_MT312
mdefine_line|#define I2C_ADDR_MT312&t;&t;0x0e
DECL|macro|I2C_ADDR_SL1935
mdefine_line|#define I2C_ADDR_SL1935&t;&t;0x61
DECL|macro|MT312_DEBUG
mdefine_line|#define MT312_DEBUG&t;&t;0
DECL|macro|MT312_SYS_CLK
mdefine_line|#define MT312_SYS_CLK&t;&t;90000000UL&t;/* 90 MHz */
DECL|macro|MT312_PLL_CLK
mdefine_line|#define MT312_PLL_CLK&t;&t;10000000UL&t;/* 10 MHz */
DECL|variable|mt312_info
r_static
r_struct
id|dvb_frontend_info
id|mt312_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Zarlink MT312&quot;
comma
dot
id|type
op_assign
id|FE_QPSK
comma
dot
id|frequency_min
op_assign
l_int|950000
comma
dot
id|frequency_max
op_assign
l_int|2150000
comma
dot
id|frequency_stepsize
op_assign
(paren
id|MT312_PLL_CLK
op_div
l_int|1000
)paren
op_div
l_int|128
comma
multiline_comment|/*.frequency_tolerance = 29500,         FIXME: binary compatibility waste? */
dot
id|symbol_rate_min
op_assign
id|MT312_SYS_CLK
op_div
l_int|128
comma
dot
id|symbol_rate_max
op_assign
id|MT312_SYS_CLK
op_div
l_int|2
comma
multiline_comment|/*.symbol_rate_tolerance = 500,         FIXME: binary compatibility waste? 2% */
dot
id|notifier_delay
op_assign
l_int|0
comma
dot
id|caps
op_assign
id|FE_CAN_INVERSION_AUTO
op_or
id|FE_CAN_FEC_1_2
op_or
id|FE_CAN_FEC_2_3
op_or
id|FE_CAN_FEC_3_4
op_or
id|FE_CAN_FEC_5_6
op_or
id|FE_CAN_FEC_7_8
op_or
id|FE_CAN_FEC_AUTO
op_or
id|FE_CAN_QPSK
op_or
id|FE_CAN_RECOVER
op_or
id|FE_CAN_CLEAN_SETUP
op_or
id|FE_CAN_MUTE_TS
)brace
suffix:semicolon
DECL|function|mt312_read
r_static
r_int
id|mt312_read
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
r_enum
id|mt312_reg_addr
id|reg
comma
r_void
op_star
id|buf
comma
r_const
r_int
id|count
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|i2c_msg
id|msg
(braket
l_int|2
)braket
suffix:semicolon
id|u8
id|regbuf
(braket
l_int|1
)braket
op_assign
(brace
id|reg
)brace
suffix:semicolon
id|msg
(braket
l_int|0
)braket
dot
id|addr
op_assign
id|I2C_ADDR_MT312
suffix:semicolon
id|msg
(braket
l_int|0
)braket
dot
id|flags
op_assign
l_int|0
suffix:semicolon
id|msg
(braket
l_int|0
)braket
dot
id|buf
op_assign
id|regbuf
suffix:semicolon
id|msg
(braket
l_int|0
)braket
dot
id|len
op_assign
l_int|1
suffix:semicolon
id|msg
(braket
l_int|1
)braket
dot
id|addr
op_assign
id|I2C_ADDR_MT312
suffix:semicolon
id|msg
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|I2C_M_RD
suffix:semicolon
id|msg
(braket
l_int|1
)braket
dot
id|buf
op_assign
id|buf
suffix:semicolon
id|msg
(braket
l_int|1
)braket
dot
id|len
op_assign
id|count
suffix:semicolon
id|ret
op_assign
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
id|msg
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|2
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ret == %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
macro_line|#ifdef MT312_DEBUG
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;R(%d):&quot;
comma
id|reg
op_amp
l_int|0x7f
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
id|count
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
(paren
(paren
r_const
id|u8
op_star
)paren
id|buf
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_write
r_static
r_int
id|mt312_write
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
r_enum
id|mt312_reg_addr
id|reg
comma
r_const
r_void
op_star
id|src
comma
r_const
r_int
id|count
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
id|count
op_plus
l_int|1
)braket
suffix:semicolon
r_struct
id|i2c_msg
id|msg
suffix:semicolon
macro_line|#ifdef MT312_DEBUG
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;W(%d):&quot;
comma
id|reg
op_amp
l_int|0x7f
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
id|count
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
(paren
(paren
r_const
id|u8
op_star
)paren
id|src
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|buf
(braket
l_int|0
)braket
op_assign
id|reg
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|buf
(braket
l_int|1
)braket
comma
id|src
comma
id|count
)paren
suffix:semicolon
id|msg.addr
op_assign
id|I2C_ADDR_MT312
suffix:semicolon
id|msg.flags
op_assign
l_int|0
suffix:semicolon
id|msg.buf
op_assign
id|buf
suffix:semicolon
id|msg.len
op_assign
id|count
op_plus
l_int|1
suffix:semicolon
id|ret
op_assign
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: ret == %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_return
op_minus
id|EREMOTEIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_readreg
r_static
r_inline
r_int
id|mt312_readreg
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
r_enum
id|mt312_reg_addr
id|reg
comma
id|u8
op_star
id|val
)paren
(brace
r_return
id|mt312_read
c_func
(paren
id|i2c
comma
id|reg
comma
id|val
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|mt312_writereg
r_static
r_inline
r_int
id|mt312_writereg
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
r_enum
id|mt312_reg_addr
id|reg
comma
r_const
id|u8
id|val
)paren
(brace
r_return
id|mt312_write
c_func
(paren
id|i2c
comma
id|reg
comma
op_amp
id|val
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|mt312_pll_write
r_static
r_int
id|mt312_pll_write
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
id|u8
id|addr
comma
id|u8
op_star
id|buf
comma
r_const
id|u8
id|len
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|i2c_msg
id|msg
suffix:semicolon
id|msg.addr
op_assign
id|addr
suffix:semicolon
id|msg.flags
op_assign
l_int|0
suffix:semicolon
id|msg.buf
op_assign
id|buf
suffix:semicolon
id|msg.len
op_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|GPP_CTRL
comma
l_int|0x40
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|i2c
op_member_access_from_pointer
id|xfer
c_func
(paren
id|i2c
comma
op_amp
id|msg
comma
l_int|1
)paren
)paren
op_ne
l_int|1
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: i/o error (ret == %d)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|ret
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|GPP_CTRL
comma
l_int|0x00
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_div
r_static
r_inline
id|u32
id|mt312_div
c_func
(paren
id|u32
id|a
comma
id|u32
id|b
)paren
(brace
r_return
(paren
id|a
op_plus
(paren
id|b
op_div
l_int|2
)paren
)paren
op_div
id|b
suffix:semicolon
)brace
DECL|function|sl1935_set_tv_freq
r_static
r_int
id|sl1935_set_tv_freq
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
id|freq
comma
id|u32
id|sr
)paren
(brace
multiline_comment|/* 155 uA, Baseband Path B */
id|u8
id|buf
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x80
comma
l_int|0x00
)brace
suffix:semicolon
id|u8
id|exp
suffix:semicolon
id|u32
id|ref
suffix:semicolon
id|u32
id|div
suffix:semicolon
r_if
c_cond
(paren
id|sr
OL
l_int|10000000
)paren
(brace
multiline_comment|/* 1-10 MSym/s: ratio 2 ^ 3 */
id|exp
op_assign
l_int|3
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_or_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* 690 uA */
)brace
r_else
r_if
c_cond
(paren
id|sr
OL
l_int|15000000
)paren
(brace
multiline_comment|/* 10-15 MSym/s: ratio 2 ^ 4 */
id|exp
op_assign
l_int|4
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_or_assign
l_int|0x20
suffix:semicolon
multiline_comment|/* 330 uA */
)brace
r_else
(brace
multiline_comment|/* 15-45 MSym/s: ratio 2 ^ 7 */
id|exp
op_assign
l_int|7
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_or_assign
l_int|0x08
suffix:semicolon
multiline_comment|/* Baseband Path A */
)brace
id|div
op_assign
id|mt312_div
c_func
(paren
id|MT312_PLL_CLK
comma
l_int|1
op_lshift
id|exp
)paren
suffix:semicolon
id|ref
op_assign
id|mt312_div
c_func
(paren
id|freq
op_star
l_int|1000
comma
id|div
)paren
suffix:semicolon
id|mt312_info.frequency_stepsize
op_assign
id|mt312_div
c_func
(paren
id|div
comma
l_int|1000
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|ref
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|ref
op_rshift
l_int|0
)paren
op_amp
l_int|0xff
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_or_assign
(paren
id|exp
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|freq
OL
l_int|1550000
)paren
id|buf
(braket
l_int|3
)braket
op_or_assign
l_int|0x10
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;synth dword = %02x%02x%02x%02x&bslash;n&quot;
comma
id|buf
(braket
l_int|0
)braket
comma
id|buf
(braket
l_int|1
)braket
comma
id|buf
(braket
l_int|2
)braket
comma
id|buf
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_return
id|mt312_pll_write
c_func
(paren
id|i2c
comma
id|I2C_ADDR_SL1935
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
)brace
DECL|function|mt312_reset
r_static
r_int
id|mt312_reset
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
id|u8
id|full
)paren
(brace
r_return
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|RESET
comma
id|full
ques
c_cond
l_int|0x80
suffix:colon
l_int|0x40
)paren
suffix:semicolon
)brace
DECL|function|mt312_init
r_static
r_int
id|mt312_init
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* wake up */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|CONFIG
comma
l_int|0x8c
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* wait at least 150 usec */
id|udelay
c_func
(paren
l_int|150
)paren
suffix:semicolon
multiline_comment|/* full reset */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_reset
c_func
(paren
id|i2c
comma
l_int|1
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* SYS_CLK */
id|buf
(braket
l_int|0
)braket
op_assign
id|mt312_div
c_func
(paren
id|MT312_SYS_CLK
op_star
l_int|2
comma
l_int|1000000
)paren
suffix:semicolon
multiline_comment|/* DISEQC_RATIO */
id|buf
(braket
l_int|1
)braket
op_assign
id|mt312_div
c_func
(paren
id|MT312_PLL_CLK
comma
l_int|15000
op_star
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_write
c_func
(paren
id|i2c
comma
id|SYS_CLK
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|SNR_THS_HIGH
comma
l_int|0x32
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* TS_SW_LIM */
id|buf
(braket
l_int|0
)braket
op_assign
l_int|0x8c
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
l_int|0x98
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_write
c_func
(paren
id|i2c
comma
id|TS_SW_LIM_L
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|CS_SW_LIM
comma
l_int|0x69
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_send_master_cmd
r_static
r_int
id|mt312_send_master_cmd
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
r_struct
id|dvb_diseqc_master_cmd
op_star
id|c
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|diseqc_mode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;msg_len
op_eq
l_int|0
)paren
op_logical_or
(paren
id|c-&gt;msg_len
OG
r_sizeof
(paren
id|c-&gt;msg
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
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
op_amp
id|diseqc_mode
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_write
c_func
(paren
id|i2c
comma
(paren
l_int|0x80
op_or
id|DISEQC_INSTR
)paren
comma
id|c-&gt;msg
comma
id|c-&gt;msg_len
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
(paren
id|diseqc_mode
op_amp
l_int|0x40
)paren
op_or
(paren
(paren
id|c-&gt;msg_len
op_minus
l_int|1
)paren
op_lshift
l_int|3
)paren
op_or
l_int|0x04
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* set DISEQC_MODE[2:0] to zero if a return message is expected */
r_if
c_cond
(paren
id|c-&gt;msg
(braket
l_int|0
)braket
op_amp
l_int|0x02
)paren
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
(paren
id|diseqc_mode
op_amp
l_int|0x40
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_recv_slave_reply
r_static
r_int
id|mt312_recv_slave_reply
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_struct
id|dvb_diseqc_slave_reply
op_star
id|r
)paren
(brace
multiline_comment|/* TODO */
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
)brace
DECL|function|mt312_send_burst
r_static
r_int
id|mt312_send_burst
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
id|fe_sec_mini_cmd_t
id|c
)paren
(brace
r_const
id|u8
id|mini_tab
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x02
comma
l_int|0x03
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|u8
id|diseqc_mode
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
id|SEC_MINI_B
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
op_amp
id|diseqc_mode
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
(paren
id|diseqc_mode
op_amp
l_int|0x40
)paren
op_or
id|mini_tab
(braket
id|c
)braket
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_set_tone
r_static
r_int
id|mt312_set_tone
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
id|fe_sec_tone_mode_t
id|t
)paren
(brace
r_const
id|u8
id|tone_tab
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0x00
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|u8
id|diseqc_mode
suffix:semicolon
r_if
c_cond
(paren
id|t
OG
id|SEC_TONE_OFF
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
op_amp
id|diseqc_mode
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
(paren
id|diseqc_mode
op_amp
l_int|0x40
)paren
op_or
id|tone_tab
(braket
id|t
)braket
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_set_voltage
r_static
r_int
id|mt312_set_voltage
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
id|fe_sec_voltage_t
id|v
)paren
(brace
r_const
id|u8
id|volt_tab
(braket
l_int|3
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x40
comma
l_int|0x00
)brace
suffix:semicolon
r_if
c_cond
(paren
id|v
OG
id|SEC_VOLTAGE_OFF
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|DISEQC_MODE
comma
id|volt_tab
(braket
id|v
)braket
)paren
suffix:semicolon
)brace
DECL|function|mt312_read_status
r_static
r_int
id|mt312_read_status
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_status_t
op_star
id|s
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|status
(braket
l_int|3
)braket
suffix:semicolon
op_star
id|s
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|QPSK_STAT_H
comma
id|status
comma
r_sizeof
(paren
id|status
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|status
(braket
l_int|0
)braket
op_amp
l_int|0xc0
)paren
op_star
id|s
op_or_assign
id|FE_HAS_SIGNAL
suffix:semicolon
multiline_comment|/* signal noise ratio */
r_if
c_cond
(paren
id|status
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
op_star
id|s
op_or_assign
id|FE_HAS_CARRIER
suffix:semicolon
multiline_comment|/* qpsk carrier lock */
r_if
c_cond
(paren
id|status
(braket
l_int|2
)braket
op_amp
l_int|0x02
)paren
op_star
id|s
op_or_assign
id|FE_HAS_VITERBI
suffix:semicolon
multiline_comment|/* viterbi lock */
r_if
c_cond
(paren
id|status
(braket
l_int|2
)braket
op_amp
l_int|0x04
)paren
op_star
id|s
op_or_assign
id|FE_HAS_SYNC
suffix:semicolon
multiline_comment|/* byte align lock */
r_if
c_cond
(paren
id|status
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
op_star
id|s
op_or_assign
id|FE_HAS_LOCK
suffix:semicolon
multiline_comment|/* qpsk lock */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_read_bercnt
r_static
r_int
id|mt312_read_bercnt
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
op_star
id|ber
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|RS_BERCNT_H
comma
id|buf
comma
l_int|3
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
op_star
id|ber
op_assign
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|buf
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
id|buf
(braket
l_int|2
)braket
)paren
op_star
l_int|64
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_read_agc
r_static
r_int
id|mt312_read_agc
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u16
op_star
id|signal_strength
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
l_int|3
)braket
suffix:semicolon
id|u16
id|agc
suffix:semicolon
id|s16
id|err_db
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|AGC_H
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|agc
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|buf
(braket
l_int|1
)braket
op_rshift
l_int|2
)paren
suffix:semicolon
id|err_db
op_assign
(paren
id|s16
)paren
(paren
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_amp
l_int|0x03
)paren
op_lshift
l_int|14
)paren
op_or
id|buf
(braket
l_int|2
)braket
op_lshift
l_int|6
)paren
op_rshift
l_int|6
suffix:semicolon
op_star
id|signal_strength
op_assign
id|agc
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;agc=%08x err_db=%hd&bslash;n&quot;
comma
id|agc
comma
id|err_db
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_read_snr
r_static
r_int
id|mt312_read_snr
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u16
op_star
id|snr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|M_SNR_H
comma
op_amp
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
op_star
id|snr
op_assign
l_int|0xFFFF
op_minus
(paren
(paren
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0x7f
)paren
op_lshift
l_int|8
)paren
op_or
id|buf
(braket
l_int|1
)braket
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_read_ubc
r_static
r_int
id|mt312_read_ubc
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
op_star
id|ubc
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|RS_UBC_H
comma
op_amp
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
op_star
id|ubc
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|buf
(braket
l_int|1
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_set_frontend
r_static
r_int
id|mt312_set_frontend
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_const
r_struct
id|dvb_frontend_parameters
op_star
id|p
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|buf
(braket
l_int|5
)braket
suffix:semicolon
id|u16
id|sr
suffix:semicolon
r_const
id|u8
id|fec_tab
(braket
l_int|10
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x3f
comma
l_int|0x08
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0x3f
comma
l_int|0x3f
)brace
suffix:semicolon
r_const
id|u8
id|inv_tab
(braket
l_int|3
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x40
comma
l_int|0x80
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;frequency
OL
id|mt312_info.frequency_min
)paren
op_logical_or
(paren
id|p-&gt;frequency
OG
id|mt312_info.frequency_max
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
id|p-&gt;inversion
OL
id|INVERSION_OFF
)paren
op_logical_or
(paren
id|p-&gt;inversion
OG
id|INVERSION_AUTO
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
id|p-&gt;u.qpsk.symbol_rate
OL
id|mt312_info.symbol_rate_min
)paren
op_logical_or
(paren
id|p-&gt;u.qpsk.symbol_rate
OG
id|mt312_info.symbol_rate_max
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
id|p-&gt;u.qpsk.fec_inner
OL
id|FEC_NONE
)paren
op_logical_or
(paren
id|p-&gt;u.qpsk.fec_inner
OG
id|FEC_AUTO
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
id|p-&gt;u.qpsk.fec_inner
op_eq
id|FEC_4_5
)paren
op_logical_or
(paren
id|p-&gt;u.qpsk.fec_inner
op_eq
id|FEC_8_9
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
id|ret
op_assign
id|sl1935_set_tv_freq
c_func
(paren
id|i2c
comma
id|p-&gt;frequency
comma
id|p-&gt;u.qpsk.symbol_rate
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* sr = (u16)(sr * 256.0 / 1000000.0) */
id|sr
op_assign
id|mt312_div
c_func
(paren
id|p-&gt;u.qpsk.symbol_rate
op_star
l_int|4
comma
l_int|15625
)paren
suffix:semicolon
multiline_comment|/* SYM_RATE */
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|sr
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|sr
op_rshift
l_int|0
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* VIT_MODE */
id|buf
(braket
l_int|2
)braket
op_assign
id|inv_tab
(braket
id|p-&gt;inversion
)braket
op_or
id|fec_tab
(braket
id|p-&gt;u.qpsk.fec_inner
)braket
suffix:semicolon
multiline_comment|/* QPSK_CTRL */
id|buf
(braket
l_int|3
)braket
op_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* swap I and Q before QPSK demodulation */
r_if
c_cond
(paren
id|p-&gt;u.qpsk.symbol_rate
OL
l_int|10000000
)paren
id|buf
(braket
l_int|3
)braket
op_or_assign
l_int|0x04
suffix:semicolon
multiline_comment|/* use afc mode */
multiline_comment|/* GO */
id|buf
(braket
l_int|4
)braket
op_assign
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_write
c_func
(paren
id|i2c
comma
id|SYM_RATE_H
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_get_inversion
r_static
r_int
id|mt312_get_inversion
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_spectral_inversion_t
op_star
id|i
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|vit_mode
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|VIT_MODE
comma
op_amp
id|vit_mode
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|vit_mode
op_amp
l_int|0x80
)paren
multiline_comment|/* auto inversion was used */
op_star
id|i
op_assign
(paren
id|vit_mode
op_amp
l_int|0x40
)paren
ques
c_cond
id|INVERSION_ON
suffix:colon
id|INVERSION_OFF
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_get_symbol_rate
r_static
r_int
id|mt312_get_symbol_rate
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|u32
op_star
id|sr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|sym_rate_h
suffix:semicolon
id|u8
id|dec_ratio
suffix:semicolon
id|u16
id|sym_rat_op
suffix:semicolon
id|u16
id|monitor
suffix:semicolon
id|u8
id|buf
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|SYM_RATE_H
comma
op_amp
id|sym_rate_h
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|sym_rate_h
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* symbol rate search was used */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|MON_CTRL
comma
l_int|0x03
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|MONITOR_H
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|monitor
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|buf
(braket
l_int|1
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sr(auto) = %u&bslash;n&quot;
comma
id|mt312_div
c_func
(paren
id|monitor
op_star
l_int|15625
comma
l_int|4
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|MON_CTRL
comma
l_int|0x05
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|MONITOR_H
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|dec_ratio
op_assign
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|0x07
)paren
op_star
l_int|32
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_read
c_func
(paren
id|i2c
comma
id|SYM_RAT_OP_H
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|sym_rat_op
op_assign
(paren
id|buf
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|buf
(braket
l_int|1
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;sym_rat_op=%d dec_ratio=%d&bslash;n&quot;
comma
id|sym_rat_op
comma
id|dec_ratio
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;*sr(manual) = %lu&bslash;n&quot;
comma
(paren
(paren
(paren
id|MT312_PLL_CLK
op_star
l_int|8192
)paren
op_div
(paren
id|sym_rat_op
op_plus
l_int|8192
)paren
)paren
op_star
l_int|2
)paren
op_minus
id|dec_ratio
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_get_code_rate
r_static
r_int
id|mt312_get_code_rate
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
id|fe_code_rate_t
op_star
id|cr
)paren
(brace
r_const
id|fe_code_rate_t
id|fec_tab
(braket
l_int|8
)braket
op_assign
(brace
id|FEC_1_2
comma
id|FEC_2_3
comma
id|FEC_3_4
comma
id|FEC_5_6
comma
id|FEC_6_7
comma
id|FEC_7_8
comma
id|FEC_AUTO
comma
id|FEC_AUTO
)brace
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|u8
id|fec_status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|FEC_STATUS
comma
op_amp
id|fec_status
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
op_star
id|cr
op_assign
id|fec_tab
(braket
(paren
id|fec_status
op_rshift
l_int|4
)paren
op_amp
l_int|0x07
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_get_frontend
r_static
r_int
id|mt312_get_frontend
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
comma
r_struct
id|dvb_frontend_parameters
op_star
id|p
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_get_inversion
c_func
(paren
id|i2c
comma
op_amp
id|p-&gt;inversion
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_get_symbol_rate
c_func
(paren
id|i2c
comma
op_amp
id|p-&gt;u.qpsk.symbol_rate
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_get_code_rate
c_func
(paren
id|i2c
comma
op_amp
id|p-&gt;u.qpsk.fec_inner
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_sleep
r_static
r_int
id|mt312_sleep
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|config
suffix:semicolon
multiline_comment|/* reset all registers to defaults */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_reset
c_func
(paren
id|i2c
comma
l_int|1
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|CONFIG
comma
op_amp
id|config
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/* enter standby */
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_writereg
c_func
(paren
id|i2c
comma
id|CONFIG
comma
id|config
op_amp
l_int|0x7f
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_ioctl
r_static
r_int
id|mt312_ioctl
c_func
(paren
r_struct
id|dvb_frontend
op_star
id|fe
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|dvb_i2c_bus
op_star
id|i2c
op_assign
id|fe-&gt;i2c
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FE_GET_INFO
suffix:colon
id|memcpy
c_func
(paren
id|arg
comma
op_amp
id|mt312_info
comma
r_sizeof
(paren
r_struct
id|dvb_frontend_info
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FE_DISEQC_RESET_OVERLOAD
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|FE_DISEQC_SEND_MASTER_CMD
suffix:colon
r_return
id|mt312_send_master_cmd
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_DISEQC_RECV_SLAVE_REPLY
suffix:colon
r_if
c_cond
(paren
(paren
r_int
)paren
id|fe-&gt;data
op_eq
id|ID_MT312
)paren
r_return
id|mt312_recv_slave_reply
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|FE_DISEQC_SEND_BURST
suffix:colon
r_return
id|mt312_send_burst
c_func
(paren
id|i2c
comma
(paren
id|fe_sec_mini_cmd_t
)paren
id|arg
)paren
suffix:semicolon
r_case
id|FE_SET_TONE
suffix:colon
r_return
id|mt312_set_tone
c_func
(paren
id|i2c
comma
(paren
id|fe_sec_tone_mode_t
)paren
id|arg
)paren
suffix:semicolon
r_case
id|FE_SET_VOLTAGE
suffix:colon
r_return
id|mt312_set_voltage
c_func
(paren
id|i2c
comma
(paren
id|fe_sec_voltage_t
)paren
id|arg
)paren
suffix:semicolon
r_case
id|FE_ENABLE_HIGH_LNB_VOLTAGE
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|FE_READ_STATUS
suffix:colon
r_return
id|mt312_read_status
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_READ_BER
suffix:colon
r_return
id|mt312_read_bercnt
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_READ_SIGNAL_STRENGTH
suffix:colon
r_return
id|mt312_read_agc
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_READ_SNR
suffix:colon
r_return
id|mt312_read_snr
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_READ_UNCORRECTED_BLOCKS
suffix:colon
r_return
id|mt312_read_ubc
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_SET_FRONTEND
suffix:colon
r_return
id|mt312_set_frontend
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_GET_FRONTEND
suffix:colon
r_return
id|mt312_get_frontend
c_func
(paren
id|i2c
comma
id|arg
)paren
suffix:semicolon
r_case
id|FE_GET_EVENT
suffix:colon
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_case
id|FE_SLEEP
suffix:colon
r_return
id|mt312_sleep
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_case
id|FE_INIT
suffix:colon
r_return
id|mt312_init
c_func
(paren
id|i2c
)paren
suffix:semicolon
r_case
id|FE_RESET
suffix:colon
r_return
id|mt312_reset
c_func
(paren
id|i2c
comma
l_int|0
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mt312_attach
r_static
r_int
id|mt312_attach
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
r_int
id|ret
suffix:semicolon
id|u8
id|id
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|mt312_readreg
c_func
(paren
id|i2c
comma
id|ID
comma
op_amp
id|id
)paren
)paren
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id
op_ne
id|ID_VP310
)paren
op_logical_and
(paren
id|id
op_ne
id|ID_MT312
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_return
id|dvb_register_frontend
c_func
(paren
id|mt312_ioctl
comma
id|i2c
comma
(paren
r_void
op_star
)paren
(paren
r_int
)paren
id|id
comma
op_amp
id|mt312_info
)paren
suffix:semicolon
)brace
DECL|function|mt312_detach
r_static
r_void
id|mt312_detach
c_func
(paren
r_struct
id|dvb_i2c_bus
op_star
id|i2c
)paren
(brace
id|dvb_unregister_frontend
c_func
(paren
id|mt312_ioctl
comma
id|i2c
)paren
suffix:semicolon
)brace
DECL|function|mt312_module_init
r_static
r_int
id|__init
id|mt312_module_init
c_func
(paren
r_void
)paren
(brace
r_return
id|dvb_register_i2c_device
c_func
(paren
id|THIS_MODULE
comma
id|mt312_attach
comma
id|mt312_detach
)paren
suffix:semicolon
)brace
DECL|function|mt312_module_exit
r_static
r_void
id|__exit
id|mt312_module_exit
c_func
(paren
r_void
)paren
(brace
id|dvb_unregister_i2c_device
c_func
(paren
id|mt312_attach
)paren
suffix:semicolon
)brace
DECL|variable|mt312_module_init
id|module_init
c_func
(paren
id|mt312_module_init
)paren
suffix:semicolon
DECL|variable|mt312_module_exit
id|module_exit
c_func
(paren
id|mt312_module_exit
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;MT312 Satellite Channel Decoder Driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Andreas Oberritter &lt;obi@saftware.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
