multiline_comment|/*&n; * $Id: saa7134-i2c.c,v 1.5 2004/10/06 17:30:51 kraxel Exp $&n; *&n; * device driver for philips saa7134 based TV cards&n; * i2c interface support&n; *&n; * (c) 2001,02 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &quot;saa7134-reg.h&quot;
macro_line|#include &quot;saa7134.h&quot;
multiline_comment|/* ----------------------------------------------------------- */
DECL|variable|i2c_debug
r_static
r_int
r_int
id|i2c_debug
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
id|MODULE_PARM_DESC
c_func
(paren
id|i2c_debug
comma
l_string|&quot;enable debug messages [i2c]&quot;
)paren
suffix:semicolon
DECL|variable|i2c_scan
r_static
r_int
r_int
id|i2c_scan
op_assign
l_int|0
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
DECL|macro|d1printk
mdefine_line|#define d1printk if (1 == i2c_debug) printk
DECL|macro|d2printk
mdefine_line|#define d2printk if (2 == i2c_debug) printk
DECL|macro|I2C_WAIT_DELAY
mdefine_line|#define I2C_WAIT_DELAY  32
DECL|macro|I2C_WAIT_RETRY
mdefine_line|#define I2C_WAIT_RETRY  16
multiline_comment|/* ----------------------------------------------------------- */
DECL|variable|str_i2c_status
r_static
r_char
op_star
id|str_i2c_status
(braket
)braket
op_assign
(brace
l_string|&quot;IDLE&quot;
comma
l_string|&quot;DONE_STOP&quot;
comma
l_string|&quot;BUSY&quot;
comma
l_string|&quot;TO_SCL&quot;
comma
l_string|&quot;TO_ARB&quot;
comma
l_string|&quot;DONE_WRITE&quot;
comma
l_string|&quot;DONE_READ&quot;
comma
l_string|&quot;DONE_WRITE_TO&quot;
comma
l_string|&quot;DONE_READ_TO&quot;
comma
l_string|&quot;NO_DEVICE&quot;
comma
l_string|&quot;NO_ACKN&quot;
comma
l_string|&quot;BUS_ERR&quot;
comma
l_string|&quot;ARB_LOST&quot;
comma
l_string|&quot;SEQ_ERR&quot;
comma
l_string|&quot;ST_ERR&quot;
comma
l_string|&quot;SW_ERR&quot;
)brace
suffix:semicolon
DECL|enum|i2c_status
r_enum
id|i2c_status
(brace
DECL|enumerator|IDLE
id|IDLE
op_assign
l_int|0
comma
singleline_comment|// no I2C command pending
DECL|enumerator|DONE_STOP
id|DONE_STOP
op_assign
l_int|1
comma
singleline_comment|// I2C command done and STOP executed
DECL|enumerator|BUSY
id|BUSY
op_assign
l_int|2
comma
singleline_comment|// executing I2C command
DECL|enumerator|TO_SCL
id|TO_SCL
op_assign
l_int|3
comma
singleline_comment|// executing I2C command, time out on clock stretching
DECL|enumerator|TO_ARB
id|TO_ARB
op_assign
l_int|4
comma
singleline_comment|// time out on arbitration trial, still trying
DECL|enumerator|DONE_WRITE
id|DONE_WRITE
op_assign
l_int|5
comma
singleline_comment|// I2C command done and awaiting next write command
DECL|enumerator|DONE_READ
id|DONE_READ
op_assign
l_int|6
comma
singleline_comment|// I2C command done and awaiting next read command
DECL|enumerator|DONE_WRITE_TO
id|DONE_WRITE_TO
op_assign
l_int|7
comma
singleline_comment|// see 5, and time out on status echo
DECL|enumerator|DONE_READ_TO
id|DONE_READ_TO
op_assign
l_int|8
comma
singleline_comment|// see 6, and time out on status echo
DECL|enumerator|NO_DEVICE
id|NO_DEVICE
op_assign
l_int|9
comma
singleline_comment|// no acknowledge on device slave address
DECL|enumerator|NO_ACKN
id|NO_ACKN
op_assign
l_int|10
comma
singleline_comment|// no acknowledge after data byte transfer
DECL|enumerator|BUS_ERR
id|BUS_ERR
op_assign
l_int|11
comma
singleline_comment|// bus error
DECL|enumerator|ARB_LOST
id|ARB_LOST
op_assign
l_int|12
comma
singleline_comment|// arbitration lost during transfer
DECL|enumerator|SEQ_ERR
id|SEQ_ERR
op_assign
l_int|13
comma
singleline_comment|// erroneous programming sequence
DECL|enumerator|ST_ERR
id|ST_ERR
op_assign
l_int|14
comma
singleline_comment|// wrong status echoing
DECL|enumerator|SW_ERR
id|SW_ERR
op_assign
l_int|15
singleline_comment|// software error
)brace
suffix:semicolon
DECL|variable|str_i2c_attr
r_static
r_char
op_star
id|str_i2c_attr
(braket
)braket
op_assign
(brace
l_string|&quot;NOP&quot;
comma
l_string|&quot;STOP&quot;
comma
l_string|&quot;CONTINUE&quot;
comma
l_string|&quot;START&quot;
)brace
suffix:semicolon
DECL|enum|i2c_attr
r_enum
id|i2c_attr
(brace
DECL|enumerator|NOP
id|NOP
op_assign
l_int|0
comma
singleline_comment|// no operation on I2C bus
DECL|enumerator|STOP
id|STOP
op_assign
l_int|1
comma
singleline_comment|// stop condition, no associated byte transfer
DECL|enumerator|CONTINUE
id|CONTINUE
op_assign
l_int|2
comma
singleline_comment|// continue with byte transfer
DECL|enumerator|START
id|START
op_assign
l_int|3
singleline_comment|// start condition with byte transfer
)brace
suffix:semicolon
DECL|function|i2c_get_status
r_static
r_inline
r_enum
id|i2c_status
id|i2c_get_status
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_enum
id|i2c_status
id|status
suffix:semicolon
id|status
op_assign
id|saa_readb
c_func
(paren
id|SAA7134_I2C_ATTR_STATUS
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|d2printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: i2c stat &lt;= %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|str_i2c_status
(braket
id|status
)braket
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|i2c_set_status
r_static
r_inline
r_void
id|i2c_set_status
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_enum
id|i2c_status
id|status
)paren
(brace
id|d2printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: i2c stat =&gt; %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|str_i2c_status
(braket
id|status
)braket
)paren
suffix:semicolon
id|saa_andorb
c_func
(paren
id|SAA7134_I2C_ATTR_STATUS
comma
l_int|0x0f
comma
id|status
)paren
suffix:semicolon
)brace
DECL|function|i2c_set_attr
r_static
r_inline
r_void
id|i2c_set_attr
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_enum
id|i2c_attr
id|attr
)paren
(brace
id|d2printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: i2c attr =&gt; %s&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|str_i2c_attr
(braket
id|attr
)braket
)paren
suffix:semicolon
id|saa_andorb
c_func
(paren
id|SAA7134_I2C_ATTR_STATUS
comma
l_int|0xc0
comma
id|attr
op_lshift
l_int|6
)paren
suffix:semicolon
)brace
DECL|function|i2c_is_error
r_static
r_inline
r_int
id|i2c_is_error
c_func
(paren
r_enum
id|i2c_status
id|status
)paren
(brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|NO_DEVICE
suffix:colon
r_case
id|NO_ACKN
suffix:colon
r_case
id|BUS_ERR
suffix:colon
r_case
id|ARB_LOST
suffix:colon
r_case
id|SEQ_ERR
suffix:colon
r_case
id|ST_ERR
suffix:colon
r_return
id|TRUE
suffix:semicolon
r_default
suffix:colon
r_return
id|FALSE
suffix:semicolon
)brace
)brace
DECL|function|i2c_is_idle
r_static
r_inline
r_int
id|i2c_is_idle
c_func
(paren
r_enum
id|i2c_status
id|status
)paren
(brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|IDLE
suffix:colon
r_case
id|DONE_STOP
suffix:colon
r_return
id|TRUE
suffix:semicolon
r_default
suffix:colon
r_return
id|FALSE
suffix:semicolon
)brace
)brace
DECL|function|i2c_is_busy
r_static
r_inline
r_int
id|i2c_is_busy
c_func
(paren
r_enum
id|i2c_status
id|status
)paren
(brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|BUSY
suffix:colon
r_return
id|TRUE
suffix:semicolon
r_default
suffix:colon
r_return
id|FALSE
suffix:semicolon
)brace
)brace
DECL|function|i2c_is_busy_wait
r_static
r_int
id|i2c_is_busy_wait
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_enum
id|i2c_status
id|status
suffix:semicolon
r_int
id|count
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|I2C_WAIT_RETRY
suffix:semicolon
id|count
op_increment
)paren
(brace
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_busy
c_func
(paren
id|status
)paren
)paren
r_break
suffix:semicolon
id|saa_wait
c_func
(paren
id|I2C_WAIT_DELAY
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|I2C_WAIT_RETRY
op_eq
id|count
)paren
r_return
id|FALSE
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
DECL|function|i2c_reset
r_static
r_int
id|i2c_reset
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_enum
id|i2c_status
id|status
suffix:semicolon
r_int
id|count
suffix:semicolon
id|d2printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: i2c reset&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_error
c_func
(paren
id|status
)paren
)paren
r_return
id|TRUE
suffix:semicolon
id|i2c_set_status
c_func
(paren
id|dev
comma
id|status
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|I2C_WAIT_RETRY
suffix:semicolon
id|count
op_increment
)paren
(brace
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_error
c_func
(paren
id|status
)paren
)paren
r_break
suffix:semicolon
id|udelay
c_func
(paren
id|I2C_WAIT_DELAY
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|I2C_WAIT_RETRY
op_eq
id|count
)paren
r_return
id|FALSE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_idle
c_func
(paren
id|status
)paren
)paren
r_return
id|FALSE
suffix:semicolon
id|i2c_set_attr
c_func
(paren
id|dev
comma
id|NOP
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
DECL|function|i2c_send_byte
r_static
r_inline
r_int
id|i2c_send_byte
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_enum
id|i2c_attr
id|attr
comma
r_int
r_char
id|data
)paren
(brace
r_enum
id|i2c_status
id|status
suffix:semicolon
id|__u32
id|dword
suffix:semicolon
macro_line|#if 0
id|i2c_set_attr
c_func
(paren
id|dev
comma
id|attr
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_I2C_DATA
comma
id|data
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* have to write both attr + data in one 32bit word */
id|dword
op_assign
id|saa_readl
c_func
(paren
id|SAA7134_I2C_ATTR_STATUS
op_rshift
l_int|2
)paren
suffix:semicolon
id|dword
op_and_assign
l_int|0x0f
suffix:semicolon
id|dword
op_or_assign
(paren
id|attr
op_lshift
l_int|6
)paren
suffix:semicolon
id|dword
op_or_assign
(paren
(paren
id|__u32
)paren
id|data
op_lshift
l_int|8
)paren
suffix:semicolon
id|dword
op_or_assign
l_int|0x00
op_lshift
l_int|16
suffix:semicolon
id|dword
op_or_assign
l_int|0xf0
op_lshift
l_int|24
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_I2C_ATTR_STATUS
op_rshift
l_int|2
comma
id|dword
)paren
suffix:semicolon
macro_line|#endif
id|d2printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: i2c data =&gt; 0x%x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_busy_wait
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_is_error
c_func
(paren
id|status
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i2c_recv_byte
r_static
r_inline
r_int
id|i2c_recv_byte
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_enum
id|i2c_status
id|status
suffix:semicolon
r_int
r_char
id|data
suffix:semicolon
id|i2c_set_attr
c_func
(paren
id|dev
comma
id|CONTINUE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_busy_wait
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_is_error
c_func
(paren
id|status
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|data
op_assign
id|saa_readb
c_func
(paren
id|SAA7134_I2C_DATA
)paren
suffix:semicolon
id|d2printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: i2c data &lt;= 0x%x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|data
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|saa7134_i2c_xfer
r_static
r_int
id|saa7134_i2c_xfer
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
id|saa7134_dev
op_star
id|dev
op_assign
id|i2c_adap-&gt;algo_data
suffix:semicolon
r_enum
id|i2c_status
id|status
suffix:semicolon
r_int
r_char
id|data
suffix:semicolon
r_int
id|addr
comma
id|rc
comma
id|i
comma
id|byte
suffix:semicolon
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_idle
c_func
(paren
id|status
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|i2c_reset
c_func
(paren
id|dev
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|d1printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: i2c xfer:&quot;
comma
id|dev-&gt;name
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
op_logical_neg
(paren
id|msgs
(braket
id|i
)braket
dot
id|flags
op_amp
id|I2C_M_NOSTART
)paren
op_logical_or
l_int|0
op_eq
id|i
)paren
(brace
multiline_comment|/* send address */
id|addr
op_assign
id|msgs
(braket
id|i
)braket
dot
id|addr
op_lshift
l_int|1
suffix:semicolon
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
id|addr
op_or_assign
l_int|1
suffix:semicolon
id|d1printk
c_func
(paren
l_string|&quot; &lt; %02x&quot;
comma
id|addr
)paren
suffix:semicolon
id|rc
op_assign
id|i2c_send_byte
c_func
(paren
id|dev
comma
id|START
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
)brace
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
multiline_comment|/* read bytes */
r_for
c_loop
(paren
id|byte
op_assign
l_int|0
suffix:semicolon
id|byte
OL
id|msgs
(braket
id|i
)braket
dot
id|len
suffix:semicolon
id|byte
op_increment
)paren
(brace
id|d1printk
c_func
(paren
l_string|&quot; =&quot;
)paren
suffix:semicolon
id|rc
op_assign
id|i2c_recv_byte
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
id|d1printk
c_func
(paren
l_string|&quot;%02x&quot;
comma
id|rc
)paren
suffix:semicolon
id|msgs
(braket
id|i
)braket
dot
id|buf
(braket
id|byte
)braket
op_assign
id|rc
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* write bytes */
r_for
c_loop
(paren
id|byte
op_assign
l_int|0
suffix:semicolon
id|byte
OL
id|msgs
(braket
id|i
)braket
dot
id|len
suffix:semicolon
id|byte
op_increment
)paren
(brace
id|data
op_assign
id|msgs
(braket
id|i
)braket
dot
id|buf
(braket
id|byte
)braket
suffix:semicolon
id|d1printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|data
)paren
suffix:semicolon
id|rc
op_assign
id|i2c_send_byte
c_func
(paren
id|dev
comma
id|CONTINUE
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
OL
l_int|0
)paren
r_goto
id|err
suffix:semicolon
)brace
)brace
)brace
id|d1printk
c_func
(paren
l_string|&quot; &gt;&quot;
)paren
suffix:semicolon
id|i2c_set_attr
c_func
(paren
id|dev
comma
id|STOP
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i2c_is_busy_wait
c_func
(paren
id|dev
)paren
)paren
r_goto
id|err
suffix:semicolon
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_is_error
c_func
(paren
id|status
)paren
)paren
r_goto
id|err
suffix:semicolon
id|d1printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|num
suffix:semicolon
id|err
suffix:colon
r_if
c_cond
(paren
l_int|1
op_eq
id|i2c_debug
)paren
(brace
id|status
op_assign
id|i2c_get_status
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; ERROR: %s&bslash;n&quot;
comma
id|str_i2c_status
(braket
id|status
)braket
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------- */
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
id|saa7134_dev
op_star
id|dev
op_assign
id|client-&gt;adapter-&gt;algo_data
suffix:semicolon
r_int
id|tuner
op_assign
id|dev-&gt;tuner_type
suffix:semicolon
r_int
id|conf
op_assign
id|dev-&gt;tda9887_conf
suffix:semicolon
id|saa7134_i2c_call_clients
c_func
(paren
id|dev
comma
id|TUNER_SET_TYPE
comma
op_amp
id|tuner
)paren
suffix:semicolon
id|saa7134_i2c_call_clients
c_func
(paren
id|dev
comma
id|TDA9887_SET_CONFIG
comma
op_amp
id|conf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|saa7134_algo
r_static
r_struct
id|i2c_algorithm
id|saa7134_algo
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;saa7134&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SAA7134
comma
dot
id|master_xfer
op_assign
id|saa7134_i2c_xfer
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
DECL|variable|saa7134_adap_template
r_static
r_struct
id|i2c_adapter
id|saa7134_adap_template
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
id|inc_use
comma
dot
id|dec_use
op_assign
id|dec_use
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
l_string|&quot;saa7134&quot;
)paren
comma
dot
id|id
op_assign
id|I2C_ALGO_SAA7134
comma
dot
id|algo
op_assign
op_amp
id|saa7134_algo
comma
dot
id|client_register
op_assign
id|attach_inform
comma
)brace
suffix:semicolon
DECL|variable|saa7134_client_template
r_static
r_struct
id|i2c_client
id|saa7134_client_template
op_assign
(brace
id|I2C_DEVNAME
c_func
(paren
l_string|&quot;saa7134 internal&quot;
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
multiline_comment|/* ----------------------------------------------------------- */
r_static
r_int
DECL|function|saa7134_i2c_eeprom
id|saa7134_i2c_eeprom
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
r_char
op_star
id|eedata
comma
r_int
id|len
)paren
(brace
r_int
r_char
id|buf
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
id|dev-&gt;i2c_client.addr
op_assign
l_int|0xa0
op_rshift
l_int|1
suffix:semicolon
id|buf
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_ne
(paren
id|err
op_assign
id|i2c_master_send
c_func
(paren
op_amp
id|dev-&gt;i2c_client
comma
op_amp
id|buf
comma
l_int|1
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Huh, no eeprom present (err=%d)?&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
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
id|len
op_ne
(paren
id|err
op_assign
id|i2c_master_recv
c_func
(paren
op_amp
id|dev-&gt;i2c_client
comma
id|eedata
comma
id|len
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: i2c eeprom read error (err=%d)&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|err
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_eq
(paren
id|i
op_mod
l_int|16
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: i2c eeprom %02x:&quot;
comma
id|dev-&gt;name
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|eedata
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|15
op_eq
(paren
id|i
op_mod
l_int|16
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
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
l_int|0x20
)braket
op_assign
l_string|&quot;mpeg encoder (saa6752hs)&quot;
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
l_int|0x86
op_rshift
l_int|1
)braket
op_assign
l_string|&quot;tda9887&quot;
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
DECL|function|saa7134_i2c_call_clients
r_void
id|saa7134_i2c_call_clients
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
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
id|BUG_ON
c_func
(paren
l_int|NULL
op_eq
id|dev-&gt;i2c_adap.algo_data
)paren
suffix:semicolon
id|i2c_clients_command
c_func
(paren
op_amp
id|dev-&gt;i2c_adap
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|saa7134_i2c_register
r_int
id|saa7134_i2c_register
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;i2c_adap
op_assign
id|saa7134_adap_template
suffix:semicolon
id|dev-&gt;i2c_adap.dev.parent
op_assign
op_amp
id|dev-&gt;pci-&gt;dev
suffix:semicolon
id|strcpy
c_func
(paren
id|dev-&gt;i2c_adap.name
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;i2c_adap.algo_data
op_assign
id|dev
suffix:semicolon
id|i2c_add_adapter
c_func
(paren
op_amp
id|dev-&gt;i2c_adap
)paren
suffix:semicolon
id|dev-&gt;i2c_client
op_assign
id|saa7134_client_template
suffix:semicolon
id|dev-&gt;i2c_client.adapter
op_assign
op_amp
id|dev-&gt;i2c_adap
suffix:semicolon
id|saa7134_i2c_eeprom
c_func
(paren
id|dev
comma
id|dev-&gt;eedata
comma
r_sizeof
(paren
id|dev-&gt;eedata
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_scan
)paren
id|do_i2c_scan
c_func
(paren
id|dev-&gt;name
comma
op_amp
id|dev-&gt;i2c_client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_i2c_unregister
r_int
id|saa7134_i2c_unregister
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|dev-&gt;i2c_adap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
