multiline_comment|/*&n;    bttv-if.c  --  interfaces to other kernel modules&n;&t;all the i2c code is here&n;&t;also the gpio interface exported by bttv (used by lirc)&n;&n;    bttv - Bt848 frame grabber driver&n;&n;    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)&n;                           &amp; Marcus Metzler (mocm@thp.uni-koeln.de)&n;    (c) 1999,2000 Gerd Knorr &lt;kraxel@goldbach.in-berlin.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;    &n;*/
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__ 1
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;bttvp.h&quot;
macro_line|#include &quot;tuner.h&quot;
DECL|variable|bttv_i2c_algo_template
r_static
r_struct
id|i2c_algo_bit_data
id|bttv_i2c_algo_template
suffix:semicolon
DECL|variable|bttv_i2c_adap_template
r_static
r_struct
id|i2c_adapter
id|bttv_i2c_adap_template
suffix:semicolon
DECL|variable|bttv_i2c_client_template
r_static
r_struct
id|i2c_client
id|bttv_i2c_client_template
suffix:semicolon
DECL|variable|bttv_get_cardinfo
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_get_cardinfo
)paren
suffix:semicolon
DECL|variable|bttv_get_id
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_get_id
)paren
suffix:semicolon
DECL|variable|bttv_gpio_enable
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_gpio_enable
)paren
suffix:semicolon
DECL|variable|bttv_read_gpio
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_read_gpio
)paren
suffix:semicolon
DECL|variable|bttv_write_gpio
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_write_gpio
)paren
suffix:semicolon
DECL|variable|bttv_get_gpio_queue
id|EXPORT_SYMBOL
c_func
(paren
id|bttv_get_gpio_queue
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* Exported functions - for other modules which want to access the         */
multiline_comment|/*                      gpio ports (IR for example)                        */
multiline_comment|/*                      see bttv.h for comments                            */
DECL|function|bttv_get_cardinfo
r_int
id|bttv_get_cardinfo
c_func
(paren
r_int
r_int
id|card
comma
r_int
op_star
id|type
comma
r_int
op_star
id|cardid
)paren
(brace
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|type
op_assign
id|bttvs
(braket
id|card
)braket
dot
id|type
suffix:semicolon
op_star
id|cardid
op_assign
id|bttvs
(braket
id|card
)braket
dot
id|cardid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_get_id
r_int
id|bttv_get_id
c_func
(paren
r_int
r_int
id|card
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bttv_get_id is obsolete, use bttv_get_cardinfo instead&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|bttvs
(braket
id|card
)braket
dot
id|type
suffix:semicolon
)brace
DECL|function|bttv_gpio_enable
r_int
id|bttv_gpio_enable
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
id|btaor
c_func
(paren
id|data
comma
op_complement
id|mask
comma
id|BT848_GPIO_OUT_EN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bttv_gpio
)paren
id|bttv_gpio_tracking
c_func
(paren
id|btv
comma
l_string|&quot;extern enable&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_read_gpio
r_int
id|bttv_read_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
op_star
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
r_if
c_cond
(paren
id|btv-&gt;shutdown
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* prior setting BT848_GPIO_REG_INP is (probably) not needed &n;   because we set direct input on init */
op_star
id|data
op_assign
id|btread
c_func
(paren
id|BT848_GPIO_DATA
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_write_gpio
r_int
id|bttv_write_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
multiline_comment|/* prior setting BT848_GPIO_REG_INP is (probably) not needed &n;   because direct input is set on init */
id|btaor
c_func
(paren
id|data
op_amp
id|mask
comma
op_complement
id|mask
comma
id|BT848_GPIO_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bttv_gpio
)paren
id|bttv_gpio_tracking
c_func
(paren
id|btv
comma
l_string|&quot;extern write&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_get_gpio_queue
id|wait_queue_head_t
op_star
id|bttv_get_gpio_queue
c_func
(paren
r_int
r_int
id|card
)paren
(brace
r_struct
id|bttv
op_star
id|btv
suffix:semicolon
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|btv
op_assign
op_amp
id|bttvs
(braket
id|card
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bttvs
(braket
id|card
)braket
dot
id|shutdown
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
op_amp
id|btv-&gt;gpioq
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* I2C functions                                                           */
DECL|function|bttv_bit_setscl
r_void
id|bttv_bit_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_struct
id|bttv
op_star
id|btv
op_assign
(paren
r_struct
id|bttv
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
id|btv-&gt;i2c_state
op_or_assign
l_int|0x02
suffix:semicolon
r_else
id|btv-&gt;i2c_state
op_and_assign
op_complement
l_int|0x02
suffix:semicolon
id|btwrite
c_func
(paren
id|btv-&gt;i2c_state
comma
id|BT848_I2C
)paren
suffix:semicolon
id|btread
c_func
(paren
id|BT848_I2C
)paren
suffix:semicolon
)brace
DECL|function|bttv_bit_setsda
r_void
id|bttv_bit_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_struct
id|bttv
op_star
id|btv
op_assign
(paren
r_struct
id|bttv
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
id|btv-&gt;i2c_state
op_or_assign
l_int|0x01
suffix:semicolon
r_else
id|btv-&gt;i2c_state
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
id|btwrite
c_func
(paren
id|btv-&gt;i2c_state
comma
id|BT848_I2C
)paren
suffix:semicolon
id|btread
c_func
(paren
id|BT848_I2C
)paren
suffix:semicolon
)brace
DECL|function|bttv_bit_getscl
r_static
r_int
id|bttv_bit_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
op_assign
(paren
r_struct
id|bttv
op_star
)paren
id|data
suffix:semicolon
r_int
id|state
suffix:semicolon
id|state
op_assign
id|btread
c_func
(paren
id|BT848_I2C
)paren
op_amp
l_int|0x02
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
id|state
suffix:semicolon
)brace
DECL|function|bttv_bit_getsda
r_static
r_int
id|bttv_bit_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|bttv
op_star
id|btv
op_assign
(paren
r_struct
id|bttv
op_star
)paren
id|data
suffix:semicolon
r_int
id|state
suffix:semicolon
id|state
op_assign
id|btread
c_func
(paren
id|BT848_I2C
)paren
op_amp
l_int|0x01
suffix:semicolon
r_return
id|state
suffix:semicolon
)brace
DECL|function|bttv_inc_use
r_static
r_void
id|bttv_inc_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|bttv_dec_use
r_static
r_void
id|bttv_dec_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|attach_inform
r_static
r_int
id|attach_inform
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|bttv
op_star
id|btv
op_assign
(paren
r_struct
id|bttv
op_star
)paren
id|client-&gt;adapter-&gt;data
suffix:semicolon
r_int
id|i
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
id|I2C_CLIENTS_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|btv-&gt;i2c_clients
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
id|btv-&gt;i2c_clients
(braket
id|i
)braket
op_assign
id|client
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|btv-&gt;tuner_type
op_ne
op_minus
l_int|1
)paren
id|bttv_call_i2c_clients
c_func
(paren
id|btv
comma
id|TUNER_SET_TYPE
comma
op_amp
id|btv-&gt;tuner_type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bttv_verbose
)paren
id|printk
c_func
(paren
l_string|&quot;bttv%d: i2c attach [client=%s,%s]&bslash;n&quot;
comma
id|btv-&gt;nr
comma
id|client-&gt;name
comma
(paren
id|i
OL
id|I2C_CLIENTS_MAX
)paren
ques
c_cond
l_string|&quot;ok&quot;
suffix:colon
l_string|&quot;failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|detach_inform
r_static
r_int
id|detach_inform
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|bttv
op_star
id|btv
op_assign
(paren
r_struct
id|bttv
op_star
)paren
id|client-&gt;adapter-&gt;data
suffix:semicolon
r_int
id|i
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
id|I2C_CLIENTS_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|btv-&gt;i2c_clients
(braket
id|i
)braket
op_eq
id|client
)paren
(brace
id|btv-&gt;i2c_clients
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|bttv_verbose
)paren
id|printk
c_func
(paren
l_string|&quot;bttv%d: i2c detach [client=%s,%s]&bslash;n&quot;
comma
id|btv-&gt;nr
comma
id|client-&gt;name
comma
(paren
id|i
OL
id|I2C_CLIENTS_MAX
)paren
ques
c_cond
l_string|&quot;ok&quot;
suffix:colon
l_string|&quot;failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bttv_call_i2c_clients
r_void
id|bttv_call_i2c_clients
c_func
(paren
r_struct
id|bttv
op_star
id|btv
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
r_int
id|i
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
id|I2C_CLIENTS_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
l_int|NULL
op_eq
id|btv-&gt;i2c_clients
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
id|btv-&gt;i2c_clients
(braket
id|i
)braket
op_member_access_from_pointer
id|driver-&gt;command
)paren
r_continue
suffix:semicolon
id|btv-&gt;i2c_clients
(braket
id|i
)braket
op_member_access_from_pointer
id|driver
op_member_access_from_pointer
id|command
c_func
(paren
id|btv-&gt;i2c_clients
(braket
id|i
)braket
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
)brace
DECL|variable|bttv_i2c_algo_template
r_static
r_struct
id|i2c_algo_bit_data
id|bttv_i2c_algo_template
op_assign
(brace
id|setsda
suffix:colon
id|bttv_bit_setsda
comma
id|setscl
suffix:colon
id|bttv_bit_setscl
comma
id|getsda
suffix:colon
id|bttv_bit_getsda
comma
id|getscl
suffix:colon
id|bttv_bit_getscl
comma
id|udelay
suffix:colon
l_int|16
comma
id|mdelay
suffix:colon
l_int|10
comma
id|timeout
suffix:colon
l_int|200
comma
)brace
suffix:semicolon
DECL|variable|bttv_i2c_adap_template
r_static
r_struct
id|i2c_adapter
id|bttv_i2c_adap_template
op_assign
(brace
id|name
suffix:colon
l_string|&quot;bt848&quot;
comma
id|id
suffix:colon
id|I2C_HW_B_BT848
comma
id|inc_use
suffix:colon
id|bttv_inc_use
comma
id|dec_use
suffix:colon
id|bttv_dec_use
comma
id|client_register
suffix:colon
id|attach_inform
comma
id|client_unregister
suffix:colon
id|detach_inform
comma
)brace
suffix:semicolon
DECL|variable|bttv_i2c_client_template
r_static
r_struct
id|i2c_client
id|bttv_i2c_client_template
op_assign
(brace
id|name
suffix:colon
l_string|&quot;bttv internal use only&quot;
comma
id|id
suffix:colon
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* read I2C */
DECL|function|bttv_I2CRead
r_int
id|bttv_I2CRead
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_char
id|addr
comma
r_char
op_star
id|probe_for
)paren
(brace
r_int
r_char
id|buffer
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|btv-&gt;i2c_rc
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bttv_verbose
op_logical_and
l_int|NULL
op_ne
id|probe_for
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;bttv%d: i2c: checking for %s @ 0x%02x... &quot;
comma
id|btv-&gt;nr
comma
id|probe_for
comma
id|addr
)paren
suffix:semicolon
id|btv-&gt;i2c_client.addr
op_assign
id|addr
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_ne
id|i2c_master_recv
c_func
(paren
op_amp
id|btv-&gt;i2c_client
comma
op_amp
id|buffer
comma
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
l_int|NULL
op_ne
id|probe_for
)paren
(brace
r_if
c_cond
(paren
id|bttv_verbose
)paren
id|printk
c_func
(paren
l_string|&quot;not found&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;bttv%d: i2c read 0x%x: error&bslash;n&quot;
comma
id|btv-&gt;nr
comma
id|addr
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bttv_verbose
op_logical_and
l_int|NULL
op_ne
id|probe_for
)paren
id|printk
c_func
(paren
l_string|&quot;found&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
multiline_comment|/* write I2C */
DECL|function|bttv_I2CWrite
r_int
id|bttv_I2CWrite
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_char
id|addr
comma
r_int
r_char
id|b1
comma
r_int
r_char
id|b2
comma
r_int
id|both
)paren
(brace
r_int
r_char
id|buffer
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|bytes
op_assign
id|both
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_ne
id|btv-&gt;i2c_rc
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|btv-&gt;i2c_client.addr
op_assign
id|addr
op_rshift
l_int|1
suffix:semicolon
id|buffer
(braket
l_int|0
)braket
op_assign
id|b1
suffix:semicolon
id|buffer
(braket
l_int|1
)braket
op_assign
id|b2
suffix:semicolon
r_if
c_cond
(paren
id|bytes
op_ne
id|i2c_master_send
c_func
(paren
op_amp
id|btv-&gt;i2c_client
comma
id|buffer
comma
id|bytes
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* read EEPROM content */
DECL|function|bttv_readee
r_void
id|__devinit
id|bttv_readee
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_int
r_char
op_star
id|eedata
comma
r_int
id|addr
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|bttv_I2CWrite
c_func
(paren
id|btv
comma
id|addr
comma
l_int|0
comma
op_minus
l_int|1
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;bttv: readee error&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|btv-&gt;i2c_client.addr
op_assign
id|addr
op_rshift
l_int|1
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
l_int|256
suffix:semicolon
id|i
op_add_assign
l_int|16
)paren
(brace
r_if
c_cond
(paren
l_int|16
op_ne
id|i2c_master_recv
c_func
(paren
op_amp
id|btv-&gt;i2c_client
comma
id|eedata
op_plus
id|i
comma
l_int|16
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;bttv: readee error&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* init + register i2c algo-bit adapter */
DECL|function|init_bttv_i2c
r_int
id|__devinit
id|init_bttv_i2c
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
(brace
id|memcpy
c_func
(paren
op_amp
id|btv-&gt;i2c_adap
comma
op_amp
id|bttv_i2c_adap_template
comma
r_sizeof
(paren
r_struct
id|i2c_adapter
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|btv-&gt;i2c_algo
comma
op_amp
id|bttv_i2c_algo_template
comma
r_sizeof
(paren
r_struct
id|i2c_algo_bit_data
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|btv-&gt;i2c_client
comma
op_amp
id|bttv_i2c_client_template
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|btv-&gt;i2c_adap.name
op_plus
id|strlen
c_func
(paren
id|btv-&gt;i2c_adap.name
)paren
comma
l_string|&quot; #%d&quot;
comma
id|btv-&gt;nr
)paren
suffix:semicolon
id|btv-&gt;i2c_algo.data
op_assign
id|btv
suffix:semicolon
id|btv-&gt;i2c_adap.data
op_assign
id|btv
suffix:semicolon
id|btv-&gt;i2c_adap.algo_data
op_assign
op_amp
id|btv-&gt;i2c_algo
suffix:semicolon
id|btv-&gt;i2c_client.adapter
op_assign
op_amp
id|btv-&gt;i2c_adap
suffix:semicolon
id|bttv_bit_setscl
c_func
(paren
id|btv
comma
l_int|1
)paren
suffix:semicolon
id|bttv_bit_setsda
c_func
(paren
id|btv
comma
l_int|1
)paren
suffix:semicolon
id|btv-&gt;i2c_rc
op_assign
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|btv-&gt;i2c_adap
)paren
suffix:semicolon
r_return
id|btv-&gt;i2c_rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
