multiline_comment|/*&n;    $Id: bttv-i2c.c,v 1.11 2004/10/13 10:39:00 kraxel Exp $&n;&n;    bttv-i2c.c  --  all the i2c code is here&n;&n;    bttv - Bt848 frame grabber driver&n;&n;    Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)&n;                           &amp; Marcus Metzler (mocm@thp.uni-koeln.de)&n;    (c) 1999-2003 Gerd Knorr &lt;kraxel@bytesex.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;bttvp.h&quot;
DECL|variable|bttv_i2c_algo_bit_template
r_static
r_struct
id|i2c_algo_bit_data
id|bttv_i2c_algo_bit_template
suffix:semicolon
DECL|variable|bttv_i2c_adap_sw_template
r_static
r_struct
id|i2c_adapter
id|bttv_i2c_adap_sw_template
suffix:semicolon
DECL|variable|bttv_i2c_adap_hw_template
r_static
r_struct
id|i2c_adapter
id|bttv_i2c_adap_hw_template
suffix:semicolon
DECL|variable|bttv_i2c_client_template
r_static
r_struct
id|i2c_client
id|bttv_i2c_client_template
suffix:semicolon
macro_line|#ifndef I2C_PEC
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
suffix:semicolon
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
suffix:semicolon
macro_line|#endif
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
suffix:semicolon
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
suffix:semicolon
DECL|variable|i2c_debug
r_static
r_int
id|i2c_debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|i2c_hw
r_static
r_int
id|i2c_hw
op_assign
l_int|0
suffix:semicolon
DECL|variable|i2c_scan
r_static
r_int
id|i2c_scan
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i2c_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i2c_hw
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|i2c_scan
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|i2c_scan
comma
l_string|&quot;scan i2c bus at insmod time&quot;
)paren
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* I2C functions - bitbanging adapter (software i2c)                       */
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
DECL|variable|bttv_i2c_algo_bit_template
r_static
r_struct
id|i2c_algo_bit_data
id|bttv_i2c_algo_bit_template
op_assign
(brace
dot
id|setsda
op_assign
id|bttv_bit_setsda
comma
dot
id|setscl
op_assign
id|bttv_bit_setscl
comma
dot
id|getsda
op_assign
id|bttv_bit_getsda
comma
dot
id|getscl
op_assign
id|bttv_bit_getscl
comma
dot
id|udelay
op_assign
l_int|16
comma
dot
id|mdelay
op_assign
l_int|10
comma
dot
id|timeout
op_assign
l_int|200
comma
)brace
suffix:semicolon
DECL|variable|bttv_i2c_adap_sw_template
r_static
r_struct
id|i2c_adapter
id|bttv_i2c_adap_sw_template
op_assign
(brace
macro_line|#ifdef I2C_PEC
dot
id|owner
op_assign
id|THIS_MODULE
comma
macro_line|#else
dot
id|inc_use
op_assign
id|bttv_inc_use
comma
dot
id|dec_use
op_assign
id|bttv_dec_use
comma
macro_line|#endif
macro_line|#ifdef I2C_CLASS_TV_ANALOG
dot
r_class
op_assign
id|I2C_CLASS_TV_ANALOG
comma
macro_line|#endif
id|I2C_DEVNAME
c_func
(paren
l_string|&quot;bt848&quot;
)paren
comma
dot
id|id
op_assign
id|I2C_HW_B_BT848
comma
dot
id|client_register
op_assign
id|attach_inform
comma
dot
id|client_unregister
op_assign
id|detach_inform
comma
)brace
suffix:semicolon
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* I2C functions - hardware i2c                                            */
DECL|function|algo_control
r_static
r_int
id|algo_control
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|functionality
r_static
id|u32
id|functionality
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_return
id|I2C_FUNC_SMBUS_EMUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|bttv_i2c_wait_done
id|bttv_i2c_wait_done
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|btv-&gt;i2c_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|btv-&gt;i2c_done
)paren
id|msleep_interruptible
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|btv-&gt;i2c_queue
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|btv-&gt;i2c_done
)paren
multiline_comment|/* timeout */
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
id|btv-&gt;i2c_done
op_amp
id|BT848_INT_RACK
)paren
id|rc
op_assign
l_int|1
suffix:semicolon
id|btv-&gt;i2c_done
op_assign
l_int|0
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|macro|I2C_HW
mdefine_line|#define I2C_HW (BT878_I2C_MODE  | BT848_I2C_SYNC |&bslash;&n;&t;&t;BT848_I2C_SCL | BT848_I2C_SDA)
r_static
r_int
DECL|function|bttv_i2c_sendbytes
id|bttv_i2c_sendbytes
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_const
r_struct
id|i2c_msg
op_star
id|msg
comma
r_int
id|last
)paren
(brace
id|u32
id|xmit
suffix:semicolon
r_int
id|retval
comma
id|cnt
suffix:semicolon
multiline_comment|/* sanity checks */
r_if
c_cond
(paren
l_int|0
op_eq
id|msg-&gt;len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* start, address + first byte */
id|xmit
op_assign
(paren
id|msg-&gt;addr
op_lshift
l_int|25
)paren
op_or
(paren
id|msg-&gt;buf
(braket
l_int|0
)braket
op_lshift
l_int|16
)paren
op_or
id|I2C_HW
suffix:semicolon
r_if
c_cond
(paren
id|msg-&gt;len
OG
l_int|1
op_logical_or
op_logical_neg
id|last
)paren
id|xmit
op_or_assign
id|BT878_I2C_NOSTOP
suffix:semicolon
id|btwrite
c_func
(paren
id|xmit
comma
id|BT848_I2C
)paren
suffix:semicolon
id|retval
op_assign
id|bttv_i2c_wait_done
c_func
(paren
id|btv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
r_goto
id|eio
suffix:semicolon
r_if
c_cond
(paren
id|i2c_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; &lt;W %02x %02x&quot;
comma
id|msg-&gt;addr
op_lshift
l_int|1
comma
id|msg-&gt;buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xmit
op_amp
id|BT878_I2C_NOSTOP
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cnt
op_assign
l_int|1
suffix:semicolon
id|cnt
OL
id|msg-&gt;len
suffix:semicolon
id|cnt
op_increment
)paren
(brace
multiline_comment|/* following bytes */
id|xmit
op_assign
(paren
id|msg-&gt;buf
(braket
id|cnt
)braket
op_lshift
l_int|24
)paren
op_or
id|I2C_HW
op_or
id|BT878_I2C_NOSTART
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
id|msg-&gt;len
op_minus
l_int|1
op_logical_or
op_logical_neg
id|last
)paren
id|xmit
op_or_assign
id|BT878_I2C_NOSTOP
suffix:semicolon
id|btwrite
c_func
(paren
id|xmit
comma
id|BT848_I2C
)paren
suffix:semicolon
id|retval
op_assign
id|bttv_i2c_wait_done
c_func
(paren
id|btv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
r_goto
id|eio
suffix:semicolon
r_if
c_cond
(paren
id|i2c_debug
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|msg-&gt;buf
(braket
id|cnt
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xmit
op_amp
id|BT878_I2C_NOSTOP
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|msg-&gt;len
suffix:semicolon
id|eio
suffix:colon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
id|err
suffix:colon
r_if
c_cond
(paren
id|i2c_debug
)paren
id|printk
c_func
(paren
l_string|&quot; ERR: %d&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_int
DECL|function|bttv_i2c_readbytes
id|bttv_i2c_readbytes
c_func
(paren
r_struct
id|bttv
op_star
id|btv
comma
r_const
r_struct
id|i2c_msg
op_star
id|msg
comma
r_int
id|last
)paren
(brace
id|u32
id|xmit
suffix:semicolon
id|u32
id|cnt
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_for
c_loop
(paren
id|cnt
op_assign
l_int|0
suffix:semicolon
id|cnt
OL
id|msg-&gt;len
suffix:semicolon
id|cnt
op_increment
)paren
(brace
id|xmit
op_assign
(paren
id|msg-&gt;addr
op_lshift
l_int|25
)paren
op_or
(paren
l_int|1
op_lshift
l_int|24
)paren
op_or
id|I2C_HW
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
id|msg-&gt;len
op_minus
l_int|1
)paren
id|xmit
op_or_assign
id|BT848_I2C_W3B
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OL
id|msg-&gt;len
op_minus
l_int|1
op_logical_or
op_logical_neg
id|last
)paren
id|xmit
op_or_assign
id|BT878_I2C_NOSTOP
suffix:semicolon
r_if
c_cond
(paren
id|cnt
)paren
id|xmit
op_or_assign
id|BT878_I2C_NOSTART
suffix:semicolon
id|btwrite
c_func
(paren
id|xmit
comma
id|BT848_I2C
)paren
suffix:semicolon
id|retval
op_assign
id|bttv_i2c_wait_done
c_func
(paren
id|btv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
r_goto
id|eio
suffix:semicolon
id|msg-&gt;buf
(braket
id|cnt
)braket
op_assign
(paren
(paren
id|u32
)paren
id|btread
c_func
(paren
id|BT848_I2C
)paren
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|i2c_debug
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|xmit
op_amp
id|BT878_I2C_NOSTART
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; &lt;R %02x&quot;
comma
(paren
id|msg-&gt;addr
op_lshift
l_int|1
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; =%02x&quot;
comma
id|msg-&gt;buf
(braket
id|cnt
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xmit
op_amp
id|BT878_I2C_NOSTOP
)paren
)paren
id|printk
c_func
(paren
l_string|&quot; &gt;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_return
id|msg-&gt;len
suffix:semicolon
id|eio
suffix:colon
id|retval
op_assign
op_minus
id|EIO
suffix:semicolon
id|err
suffix:colon
r_if
c_cond
(paren
id|i2c_debug
)paren
id|printk
c_func
(paren
l_string|&quot; ERR: %d&bslash;n&quot;
comma
id|retval
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|bttv_i2c_xfer
r_int
id|bttv_i2c_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|i2c_adap
comma
r_struct
id|i2c_msg
id|msgs
(braket
)braket
comma
r_int
id|num
)paren
(brace
r_struct
id|bttv
op_star
id|btv
op_assign
id|i2c_get_adapdata
c_func
(paren
id|i2c_adap
)paren
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i2c_debug
)paren
id|printk
c_func
(paren
l_string|&quot;bt-i2c:&quot;
)paren
suffix:semicolon
id|btwrite
c_func
(paren
id|BT848_INT_I2CDONE
op_or
id|BT848_INT_RACK
comma
id|BT848_INT_STAT
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
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|msgs
(braket
id|i
)braket
dot
id|flags
op_amp
id|I2C_M_RD
)paren
(brace
multiline_comment|/* read */
id|retval
op_assign
id|bttv_i2c_readbytes
c_func
(paren
id|btv
comma
op_amp
id|msgs
(braket
id|i
)braket
comma
id|i
op_plus
l_int|1
op_eq
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* write */
id|retval
op_assign
id|bttv_i2c_sendbytes
c_func
(paren
id|btv
comma
op_amp
id|msgs
(braket
id|i
)braket
comma
id|i
op_plus
l_int|1
op_eq
id|num
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
)brace
)brace
r_return
id|num
suffix:semicolon
id|err
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|variable|bttv_algo
r_static
r_struct
id|i2c_algorithm
id|bttv_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;bt878&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
multiline_comment|/* FIXME */
comma
dot
id|master_xfer
op_assign
id|bttv_i2c_xfer
comma
dot
id|algo_control
op_assign
id|algo_control
comma
dot
id|functionality
op_assign
id|functionality
comma
)brace
suffix:semicolon
DECL|variable|bttv_i2c_adap_hw_template
r_static
r_struct
id|i2c_adapter
id|bttv_i2c_adap_hw_template
op_assign
(brace
macro_line|#ifdef I2C_PEC
dot
id|owner
op_assign
id|THIS_MODULE
comma
macro_line|#else
dot
id|inc_use
op_assign
id|bttv_inc_use
comma
dot
id|dec_use
op_assign
id|bttv_dec_use
comma
macro_line|#endif
macro_line|#ifdef I2C_CLASS_TV_ANALOG
dot
r_class
op_assign
id|I2C_CLASS_TV_ANALOG
comma
macro_line|#endif
id|I2C_DEVNAME
c_func
(paren
l_string|&quot;bt878&quot;
)paren
comma
dot
id|id
op_assign
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
multiline_comment|/* FIXME */
comma
dot
id|algo
op_assign
op_amp
id|bttv_algo
comma
dot
id|client_register
op_assign
id|attach_inform
comma
dot
id|client_unregister
op_assign
id|detach_inform
comma
)brace
suffix:semicolon
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
id|i2c_get_adapdata
c_func
(paren
id|client-&gt;adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|btv-&gt;tuner_type
op_ne
id|UNSET
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
id|btv-&gt;pinnacle_id
op_ne
id|UNSET
)paren
id|bttv_call_i2c_clients
c_func
(paren
id|btv
comma
id|AUDC_CONFIG_PINNACLE
comma
op_amp
id|btv-&gt;pinnacle_id
)paren
suffix:semicolon
id|bttv_i2c_info
c_func
(paren
op_amp
id|btv-&gt;c
comma
id|client
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bttv_debug
)paren
id|printk
c_func
(paren
l_string|&quot;bttv%d: i2c attach [client=%s]&bslash;n&quot;
comma
id|btv-&gt;c.nr
comma
id|i2c_clientname
c_func
(paren
id|client
)paren
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
id|i2c_get_adapdata
c_func
(paren
id|client-&gt;adapter
)paren
suffix:semicolon
id|bttv_i2c_info
c_func
(paren
op_amp
id|btv-&gt;c
comma
id|client
comma
l_int|0
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
r_if
c_cond
(paren
l_int|0
op_ne
id|btv-&gt;i2c_rc
)paren
r_return
suffix:semicolon
id|i2c_clients_command
c_func
(paren
op_amp
id|btv-&gt;c.i2c_adap
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|bttv_i2c_call
r_void
id|bttv_i2c_call
c_func
(paren
r_int
r_int
id|card
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
r_if
c_cond
(paren
id|card
op_ge
id|bttv_num
)paren
r_return
suffix:semicolon
id|bttv_call_i2c_clients
c_func
(paren
op_amp
id|bttvs
(braket
id|card
)braket
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|variable|bttv_i2c_client_template
r_static
r_struct
id|i2c_client
id|bttv_i2c_client_template
op_assign
(brace
id|I2C_DEVNAME
c_func
(paren
l_string|&quot;bttv internal&quot;
)paren
comma
dot
id|id
op_assign
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
id|btv-&gt;c.nr
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
id|btv-&gt;c.nr
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
DECL|variable|i2c_devs
r_static
r_char
op_star
id|i2c_devs
(braket
l_int|128
)braket
op_assign
(brace
(braket
l_int|0x30
op_rshift
l_int|1
)braket
op_assign
l_string|&quot;IR (hauppauge)&quot;
comma
(braket
l_int|0x80
op_rshift
l_int|1
)braket
op_assign
l_string|&quot;msp34xx&quot;
comma
(braket
l_int|0x86
op_rshift
l_int|1
)braket
op_assign
l_string|&quot;tda9887&quot;
comma
(braket
l_int|0xa0
op_rshift
l_int|1
)braket
op_assign
l_string|&quot;eeprom&quot;
comma
(braket
l_int|0xc0
op_rshift
l_int|1
)braket
op_assign
l_string|&quot;tuner (analog)&quot;
comma
(braket
l_int|0xc2
op_rshift
l_int|1
)braket
op_assign
l_string|&quot;tuner (analog)&quot;
comma
)brace
suffix:semicolon
DECL|function|do_i2c_scan
r_static
r_void
id|do_i2c_scan
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|i2c_client
op_star
id|c
)paren
(brace
r_int
r_char
id|buf
suffix:semicolon
r_int
id|i
comma
id|rc
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
l_int|128
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c-&gt;addr
op_assign
id|i
suffix:semicolon
id|rc
op_assign
id|i2c_master_recv
c_func
(paren
id|c
comma
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: i2c scan: found device @ 0x%x  [%s]&bslash;n&quot;
comma
id|name
comma
id|i
op_lshift
l_int|1
comma
id|i2c_devs
(braket
id|i
)braket
ques
c_cond
id|i2c_devs
(braket
id|i
)braket
suffix:colon
l_string|&quot;???&quot;
)paren
suffix:semicolon
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
id|btv-&gt;i2c_client
comma
op_amp
id|bttv_i2c_client_template
comma
r_sizeof
(paren
id|bttv_i2c_client_template
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_hw
)paren
id|btv-&gt;use_i2c_hw
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|btv-&gt;use_i2c_hw
)paren
(brace
multiline_comment|/* bt878 */
id|memcpy
c_func
(paren
op_amp
id|btv-&gt;c.i2c_adap
comma
op_amp
id|bttv_i2c_adap_hw_template
comma
r_sizeof
(paren
id|bttv_i2c_adap_hw_template
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* bt848 */
id|memcpy
c_func
(paren
op_amp
id|btv-&gt;c.i2c_adap
comma
op_amp
id|bttv_i2c_adap_sw_template
comma
r_sizeof
(paren
id|bttv_i2c_adap_sw_template
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
id|bttv_i2c_algo_bit_template
comma
r_sizeof
(paren
id|bttv_i2c_algo_bit_template
)paren
)paren
suffix:semicolon
id|btv-&gt;i2c_algo.data
op_assign
id|btv
suffix:semicolon
id|btv-&gt;c.i2c_adap.algo_data
op_assign
op_amp
id|btv-&gt;i2c_algo
suffix:semicolon
)brace
id|btv-&gt;c.i2c_adap.dev.parent
op_assign
op_amp
id|btv-&gt;c.pci-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|btv-&gt;c.i2c_adap.name
comma
r_sizeof
(paren
id|btv-&gt;c.i2c_adap.name
)paren
comma
l_string|&quot;bt%d #%d [%s]&quot;
comma
id|btv-&gt;id
comma
id|btv-&gt;c.nr
comma
id|btv-&gt;use_i2c_hw
ques
c_cond
l_string|&quot;hw&quot;
suffix:colon
l_string|&quot;sw&quot;
)paren
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
op_amp
id|btv-&gt;c.i2c_adap
comma
id|btv
)paren
suffix:semicolon
id|btv-&gt;i2c_client.adapter
op_assign
op_amp
id|btv-&gt;c.i2c_adap
suffix:semicolon
macro_line|#ifdef I2C_CLASS_TV_ANALOG
r_if
c_cond
(paren
id|bttv_tvcards
(braket
id|btv-&gt;c.type
)braket
dot
id|no_video
)paren
id|btv-&gt;c.i2c_adap
dot
r_class
op_and_assign
op_complement
id|I2C_CLASS_TV_ANALOG
suffix:semicolon
r_if
c_cond
(paren
id|bttv_tvcards
(braket
id|btv-&gt;c.type
)braket
dot
id|has_dvb
)paren
id|btv-&gt;c.i2c_adap
dot
r_class
op_or_assign
id|I2C_CLASS_TV_DIGITAL
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|btv-&gt;use_i2c_hw
)paren
(brace
id|btv-&gt;i2c_rc
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|btv-&gt;c.i2c_adap
)paren
suffix:semicolon
)brace
r_else
(brace
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
id|btv-&gt;c.i2c_adap
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|btv-&gt;i2c_rc
op_logical_and
id|i2c_scan
)paren
id|do_i2c_scan
c_func
(paren
id|btv-&gt;c.name
comma
op_amp
id|btv-&gt;i2c_client
)paren
suffix:semicolon
r_return
id|btv-&gt;i2c_rc
suffix:semicolon
)brace
DECL|function|fini_bttv_i2c
r_int
id|__devexit
id|fini_bttv_i2c
c_func
(paren
r_struct
id|bttv
op_star
id|btv
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
id|btv-&gt;i2c_rc
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|btv-&gt;use_i2c_hw
)paren
(brace
r_return
id|i2c_del_adapter
c_func
(paren
op_amp
id|btv-&gt;c.i2c_adap
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|btv-&gt;c.i2c_adap
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
