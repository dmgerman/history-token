multiline_comment|/*&n;    i2c Support for Apple Keywest I2C Bus Controller&n;&n;    Copyright (c) 2001 Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt;&n;&n;    Original work by&n;    &n;    Copyright (c) 2000 Philip Edelbrock &lt;phil@stimpy.netroedge.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    Changes:&n;&n;    2001/12/13 BenH&t;New implementation&n;    2001/12/15 BenH&t;Add support for &quot;byte&quot; and &quot;quick&quot;&n;                        transfers. Add i2c_xfer routine.&n;&n;    My understanding of the various modes supported by keywest are:&n;&n;     - Dumb mode : not implemented, probably direct tweaking of lines&n;     - Standard mode : simple i2c transaction of type&n;         S Addr R/W A Data A Data ... T&n;     - Standard sub mode : combined 8 bit subaddr write with data read&n;         S Addr R/W A SubAddr A Data A Data ... T&n;     - Combined mode : Subaddress and Data sequences appended with no stop&n;         S Addr R/W A SubAddr S Addr R/W A Data A Data ... T&n;&n;    Currently, this driver uses only Standard mode for i2c xfer, and&n;    smbus byte &amp; quick transfers ; and uses StandardSub mode for&n;    other smbus transfers instead of combined as we need that for the&n;    sound driver to be happy&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pmac_feature.h&gt;
macro_line|#include &quot;i2c-keywest.h&quot;
DECL|macro|DBG
mdefine_line|#define DBG(x...) do {&bslash;&n;&t;if (debug &gt; 0) &bslash;&n;&t;&t;printk(KERN_DEBUG &quot;KW:&quot; x); &bslash;&n;&t;} while(0)
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C driver for Apple&squot;s Keywest&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|probe
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|probe
r_int
id|probe
op_assign
l_int|0
suffix:semicolon
DECL|variable|debug
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
r_static
r_void
DECL|function|do_stop
id|do_stop
c_func
(paren
r_struct
id|keywest_iface
op_star
id|iface
comma
r_int
id|result
)paren
(brace
id|write_reg
c_func
(paren
id|reg_control
comma
id|read_reg
c_func
(paren
id|reg_control
)paren
op_or
id|KW_I2C_CTL_STOP
)paren
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_stop
suffix:semicolon
id|iface-&gt;result
op_assign
id|result
suffix:semicolon
)brace
multiline_comment|/* Main state machine for standard &amp; standard sub mode */
r_static
r_int
DECL|function|handle_interrupt
id|handle_interrupt
c_func
(paren
r_struct
id|keywest_iface
op_star
id|iface
comma
id|u8
id|isr
)paren
(brace
r_int
id|ack
suffix:semicolon
r_int
id|rearm_timer
op_assign
l_int|1
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;handle_interrupt(), got: %x, status: %x, state: %d&bslash;n&quot;
comma
id|isr
comma
id|read_reg
c_func
(paren
id|reg_status
)paren
comma
id|iface-&gt;state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|isr
op_eq
l_int|0
op_logical_and
id|iface-&gt;state
op_ne
id|state_stop
)paren
(brace
id|do_stop
c_func
(paren
id|iface
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|rearm_timer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isr
op_amp
id|KW_I2C_IRQ_STOP
op_logical_and
id|iface-&gt;state
op_ne
id|state_stop
)paren
(brace
id|iface-&gt;result
op_assign
op_minus
l_int|1
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_stop
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|iface-&gt;state
)paren
(brace
r_case
id|state_addr
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|isr
op_amp
id|KW_I2C_IRQ_ADDR
)paren
)paren
(brace
id|do_stop
c_func
(paren
id|iface
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ack
op_assign
id|read_reg
c_func
(paren
id|reg_status
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;ack on set address: %x&bslash;n&quot;
comma
id|ack
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ack
op_amp
id|KW_I2C_STAT_LAST_AAK
)paren
op_eq
l_int|0
)paren
(brace
id|do_stop
c_func
(paren
id|iface
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Handle rw &quot;quick&quot; mode */
r_if
c_cond
(paren
id|iface-&gt;datalen
op_eq
l_int|0
)paren
id|do_stop
c_func
(paren
id|iface
comma
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|iface-&gt;read_write
op_eq
id|I2C_SMBUS_READ
)paren
(brace
id|iface-&gt;state
op_assign
id|state_read
suffix:semicolon
r_if
c_cond
(paren
id|iface-&gt;datalen
OG
l_int|1
)paren
id|write_reg
c_func
(paren
id|reg_control
comma
id|read_reg
c_func
(paren
id|reg_control
)paren
op_or
id|KW_I2C_CTL_AAK
)paren
suffix:semicolon
)brace
r_else
(brace
id|iface-&gt;state
op_assign
id|state_write
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;write byte: %x&bslash;n&quot;
comma
op_star
(paren
id|iface-&gt;data
)paren
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_data
comma
op_star
(paren
id|iface-&gt;data
op_increment
)paren
)paren
suffix:semicolon
id|iface-&gt;datalen
op_decrement
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|state_read
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|isr
op_amp
id|KW_I2C_IRQ_DATA
)paren
)paren
(brace
id|do_stop
c_func
(paren
id|iface
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
(paren
id|iface-&gt;data
op_increment
)paren
op_assign
id|read_reg
c_func
(paren
id|reg_data
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;read byte: %x&bslash;n&quot;
comma
op_star
(paren
id|iface-&gt;data
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|iface-&gt;datalen
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|iface-&gt;datalen
op_eq
l_int|0
)paren
id|iface-&gt;state
op_assign
id|state_stop
suffix:semicolon
r_else
id|write_reg
c_func
(paren
id|reg_control
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|state_write
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|isr
op_amp
id|KW_I2C_IRQ_DATA
)paren
)paren
(brace
id|do_stop
c_func
(paren
id|iface
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Check ack status */
id|ack
op_assign
id|read_reg
c_func
(paren
id|reg_status
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;ack on data write: %x&bslash;n&quot;
comma
id|ack
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ack
op_amp
id|KW_I2C_STAT_LAST_AAK
)paren
op_eq
l_int|0
)paren
(brace
id|do_stop
c_func
(paren
id|iface
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|iface-&gt;datalen
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;write byte: %x&bslash;n&quot;
comma
op_star
(paren
id|iface-&gt;data
)paren
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_data
comma
op_star
(paren
id|iface-&gt;data
op_increment
)paren
)paren
suffix:semicolon
id|iface-&gt;datalen
op_decrement
suffix:semicolon
)brace
r_else
id|do_stop
c_func
(paren
id|iface
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|state_stop
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|isr
op_amp
id|KW_I2C_IRQ_STOP
)paren
op_logical_and
(paren
op_increment
id|iface-&gt;stopretry
)paren
OL
l_int|10
)paren
id|do_stop
c_func
(paren
id|iface
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_else
(brace
id|rearm_timer
op_assign
l_int|0
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_idle
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_control
comma
l_int|0x00
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_ier
comma
l_int|0x00
)paren
suffix:semicolon
id|complete
c_func
(paren
op_amp
id|iface-&gt;complete
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|write_reg
c_func
(paren
id|reg_isr
comma
id|isr
)paren
suffix:semicolon
r_return
id|rearm_timer
suffix:semicolon
)brace
multiline_comment|/* Interrupt handler */
r_static
id|irqreturn_t
DECL|function|keywest_irq
id|keywest_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|keywest_iface
op_star
id|iface
op_assign
(paren
r_struct
id|keywest_iface
op_star
)paren
id|dev_id
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|iface-&gt;timeout_timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handle_interrupt
c_func
(paren
id|iface
comma
id|read_reg
c_func
(paren
id|reg_isr
)paren
)paren
)paren
id|mod_timer
c_func
(paren
op_amp
id|iface-&gt;timeout_timer
comma
id|jiffies
op_plus
id|POLL_TIMEOUT
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_void
DECL|function|keywest_timeout
id|keywest_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|keywest_iface
op_star
id|iface
op_assign
(paren
r_struct
id|keywest_iface
op_star
)paren
id|data
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;timeout !&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handle_interrupt
c_func
(paren
id|iface
comma
id|read_reg
c_func
(paren
id|reg_isr
)paren
)paren
)paren
id|mod_timer
c_func
(paren
op_amp
id|iface-&gt;timeout_timer
comma
id|jiffies
op_plus
id|POLL_TIMEOUT
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * SMBUS-type transfer entrypoint&n; */
r_static
id|s32
DECL|function|keywest_smbus_xfer
id|keywest_smbus_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
id|u16
id|addr
comma
r_int
r_int
id|flags
comma
r_char
id|read_write
comma
id|u8
id|command
comma
r_int
id|size
comma
r_union
id|i2c_smbus_data
op_star
id|data
)paren
(brace
r_struct
id|keywest_chan
op_star
id|chan
op_assign
id|i2c_get_adapdata
c_func
(paren
id|adap
)paren
suffix:semicolon
r_struct
id|keywest_iface
op_star
id|iface
op_assign
id|chan-&gt;iface
suffix:semicolon
r_int
id|len
suffix:semicolon
id|u8
op_star
id|buffer
suffix:semicolon
id|u16
id|cur_word
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|iface-&gt;state
op_eq
id|state_dead
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Prepare datas &amp; select mode */
id|iface-&gt;cur_mode
op_and_assign
op_complement
id|KW_I2C_MODE_MODE_MASK
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|len
op_assign
l_int|0
suffix:semicolon
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|iface-&gt;cur_mode
op_or_assign
id|KW_I2C_MODE_STANDARD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
id|len
op_assign
l_int|1
suffix:semicolon
id|buffer
op_assign
op_amp
id|data-&gt;byte
suffix:semicolon
id|iface-&gt;cur_mode
op_or_assign
id|KW_I2C_MODE_STANDARD
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|len
op_assign
l_int|1
suffix:semicolon
id|buffer
op_assign
op_amp
id|data-&gt;byte
suffix:semicolon
id|iface-&gt;cur_mode
op_or_assign
id|KW_I2C_MODE_STANDARDSUB
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|len
op_assign
l_int|2
suffix:semicolon
id|cur_word
op_assign
id|cpu_to_le16
c_func
(paren
id|data-&gt;word
)paren
suffix:semicolon
id|buffer
op_assign
(paren
id|u8
op_star
)paren
op_amp
id|cur_word
suffix:semicolon
id|iface-&gt;cur_mode
op_or_assign
id|KW_I2C_MODE_STANDARDSUB
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
id|len
op_assign
id|data-&gt;block
(braket
l_int|0
)braket
suffix:semicolon
id|buffer
op_assign
op_amp
id|data-&gt;block
(braket
l_int|1
)braket
suffix:semicolon
id|iface-&gt;cur_mode
op_or_assign
id|KW_I2C_MODE_STANDARDSUB
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Original driver had this limitation */
r_if
c_cond
(paren
id|len
OG
l_int|32
)paren
id|len
op_assign
l_int|32
suffix:semicolon
id|down
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;chan: %d, addr: 0x%x, transfer len: %d, read: %d&bslash;n&quot;
comma
id|chan-&gt;chan_no
comma
id|addr
comma
id|len
comma
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
suffix:semicolon
id|iface-&gt;data
op_assign
id|buffer
suffix:semicolon
id|iface-&gt;datalen
op_assign
id|len
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_addr
suffix:semicolon
id|iface-&gt;result
op_assign
l_int|0
suffix:semicolon
id|iface-&gt;stopretry
op_assign
l_int|0
suffix:semicolon
id|iface-&gt;read_write
op_assign
id|read_write
suffix:semicolon
multiline_comment|/* Setup channel &amp; clear pending irqs */
id|write_reg
c_func
(paren
id|reg_mode
comma
id|iface-&gt;cur_mode
op_or
(paren
id|chan-&gt;chan_no
op_lshift
l_int|4
)paren
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_isr
comma
id|read_reg
c_func
(paren
id|reg_isr
)paren
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_status
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set up address and r/w bit */
id|write_reg
c_func
(paren
id|reg_addr
comma
(paren
id|addr
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x00
)paren
)paren
suffix:semicolon
multiline_comment|/* Set up the sub address */
r_if
c_cond
(paren
(paren
id|iface-&gt;cur_mode
op_amp
id|KW_I2C_MODE_MODE_MASK
)paren
op_eq
id|KW_I2C_MODE_STANDARDSUB
op_logical_or
(paren
id|iface-&gt;cur_mode
op_amp
id|KW_I2C_MODE_MODE_MASK
)paren
op_eq
id|KW_I2C_MODE_COMBINED
)paren
id|write_reg
c_func
(paren
id|reg_subaddr
comma
id|command
)paren
suffix:semicolon
multiline_comment|/* Arm timeout */
id|mod_timer
c_func
(paren
op_amp
id|iface-&gt;timeout_timer
comma
id|jiffies
op_plus
id|POLL_TIMEOUT
)paren
suffix:semicolon
multiline_comment|/* Start sending address &amp; enable interrupt*/
id|write_reg
c_func
(paren
id|reg_control
comma
id|read_reg
c_func
(paren
id|reg_control
)paren
op_or
id|KW_I2C_CTL_XADDR
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_ier
comma
id|KW_I2C_IRQ_MASK
)paren
suffix:semicolon
multiline_comment|/* Wait interrupt operations completion */
id|wait_for_completion
c_func
(paren
op_amp
id|iface-&gt;complete
)paren
suffix:semicolon
id|rc
op_assign
id|iface-&gt;result
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;transfer done, result: %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
op_logical_and
id|size
op_eq
id|I2C_SMBUS_WORD_DATA
op_logical_and
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
id|data-&gt;word
op_assign
id|le16_to_cpu
c_func
(paren
id|cur_word
)paren
suffix:semicolon
multiline_comment|/* Release sem */
id|up
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic i2c master transfer entrypoint&n; */
r_static
r_int
DECL|function|keywest_xfer
id|keywest_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
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
id|keywest_chan
op_star
id|chan
op_assign
id|i2c_get_adapdata
c_func
(paren
id|adap
)paren
suffix:semicolon
r_struct
id|keywest_iface
op_star
id|iface
op_assign
id|chan-&gt;iface
suffix:semicolon
r_struct
id|i2c_msg
op_star
id|pmsg
suffix:semicolon
r_int
id|i
comma
id|completed
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* Set adapter to standard mode */
id|iface-&gt;cur_mode
op_and_assign
op_complement
id|KW_I2C_MODE_MODE_MASK
suffix:semicolon
id|iface-&gt;cur_mode
op_or_assign
id|KW_I2C_MODE_STANDARD
suffix:semicolon
id|completed
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|rc
op_ge
l_int|0
op_logical_and
id|i
OL
id|num
suffix:semicolon
)paren
(brace
id|u8
id|addr
suffix:semicolon
id|pmsg
op_assign
op_amp
id|msgs
(braket
id|i
op_increment
)braket
suffix:semicolon
id|addr
op_assign
id|pmsg-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|pmsg-&gt;flags
op_amp
id|I2C_M_TEN
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-keywest: 10 bits addr not supported !&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;xfer: chan: %d, doing %s %d bytes to 0x%02x - %d of %d messages&bslash;n&quot;
comma
id|chan-&gt;chan_no
comma
id|pmsg-&gt;flags
op_amp
id|I2C_M_RD
ques
c_cond
l_string|&quot;read&quot;
suffix:colon
l_string|&quot;write&quot;
comma
id|pmsg-&gt;len
comma
id|addr
comma
id|i
comma
id|num
)paren
suffix:semicolon
multiline_comment|/* Setup channel &amp; clear pending irqs */
id|write_reg
c_func
(paren
id|reg_mode
comma
id|iface-&gt;cur_mode
op_or
(paren
id|chan-&gt;chan_no
op_lshift
l_int|4
)paren
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_isr
comma
id|read_reg
c_func
(paren
id|reg_isr
)paren
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_status
comma
l_int|0
)paren
suffix:semicolon
id|iface-&gt;data
op_assign
id|pmsg-&gt;buf
suffix:semicolon
id|iface-&gt;datalen
op_assign
id|pmsg-&gt;len
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_addr
suffix:semicolon
id|iface-&gt;result
op_assign
l_int|0
suffix:semicolon
id|iface-&gt;stopretry
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pmsg-&gt;flags
op_amp
id|I2C_M_RD
)paren
id|iface-&gt;read_write
op_assign
id|I2C_SMBUS_READ
suffix:semicolon
r_else
id|iface-&gt;read_write
op_assign
id|I2C_SMBUS_WRITE
suffix:semicolon
multiline_comment|/* Set up address and r/w bit */
r_if
c_cond
(paren
id|pmsg-&gt;flags
op_amp
id|I2C_M_REV_DIR_ADDR
)paren
id|addr
op_xor_assign
l_int|1
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_addr
comma
(paren
id|addr
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|iface-&gt;read_write
op_eq
id|I2C_SMBUS_READ
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x00
)paren
)paren
suffix:semicolon
multiline_comment|/* Arm timeout */
id|mod_timer
c_func
(paren
op_amp
id|iface-&gt;timeout_timer
comma
id|jiffies
op_plus
id|POLL_TIMEOUT
)paren
suffix:semicolon
multiline_comment|/* Start sending address &amp; enable interrupt*/
id|write_reg
c_func
(paren
id|reg_control
comma
id|read_reg
c_func
(paren
id|reg_control
)paren
op_or
id|KW_I2C_CTL_XADDR
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_ier
comma
id|KW_I2C_IRQ_MASK
)paren
suffix:semicolon
multiline_comment|/* Wait interrupt operations completion */
id|wait_for_completion
c_func
(paren
op_amp
id|iface-&gt;complete
)paren
suffix:semicolon
id|rc
op_assign
id|iface-&gt;result
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
id|completed
op_increment
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;transfer done, result: %d&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
multiline_comment|/* Release sem */
id|up
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
r_return
id|completed
suffix:semicolon
)brace
r_static
id|u32
DECL|function|keywest_func
id|keywest_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
r_return
id|I2C_FUNC_SMBUS_QUICK
op_or
id|I2C_FUNC_SMBUS_BYTE
op_or
id|I2C_FUNC_SMBUS_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
op_or
id|I2C_FUNC_SMBUS_BLOCK_DATA
suffix:semicolon
)brace
multiline_comment|/* For now, we only handle combined mode (smbus) */
DECL|variable|keywest_algorithm
r_static
r_struct
id|i2c_algorithm
id|keywest_algorithm
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Keywest i2c&quot;
comma
id|id
suffix:colon
id|I2C_ALGO_SMBUS
comma
id|smbus_xfer
suffix:colon
id|keywest_smbus_xfer
comma
id|master_xfer
suffix:colon
id|keywest_xfer
comma
id|functionality
suffix:colon
id|keywest_func
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|create_iface
id|create_iface
c_func
(paren
r_struct
id|device_node
op_star
id|np
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
r_int
id|steps
comma
op_star
id|psteps
comma
op_star
id|prate
suffix:semicolon
r_int
id|bsteps
comma
id|tsize
comma
id|i
comma
id|nchan
comma
id|addroffset
suffix:semicolon
r_struct
id|keywest_iface
op_star
id|iface
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|psteps
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;AAPL,address-step&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|steps
op_assign
id|psteps
ques
c_cond
(paren
op_star
id|psteps
)paren
suffix:colon
l_int|0x10
suffix:semicolon
multiline_comment|/* Hrm... maybe we can be smarter here */
r_for
c_loop
(paren
id|bsteps
op_assign
l_int|0
suffix:semicolon
(paren
id|steps
op_amp
l_int|0x01
)paren
op_eq
l_int|0
suffix:semicolon
id|bsteps
op_increment
)paren
id|steps
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|np-&gt;parent-&gt;name
comma
l_string|&quot;uni-n&quot;
)paren
)paren
(brace
id|nchan
op_assign
l_int|2
suffix:semicolon
id|addroffset
op_assign
l_int|3
suffix:semicolon
)brace
r_else
(brace
id|addroffset
op_assign
l_int|0
suffix:semicolon
id|nchan
op_assign
l_int|1
suffix:semicolon
)brace
id|tsize
op_assign
r_sizeof
(paren
r_struct
id|keywest_iface
)paren
op_plus
(paren
r_sizeof
(paren
r_struct
id|keywest_chan
)paren
op_plus
l_int|4
)paren
op_star
id|nchan
suffix:semicolon
id|iface
op_assign
(paren
r_struct
id|keywest_iface
op_star
)paren
id|kmalloc
c_func
(paren
id|tsize
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iface
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-keywest: can&squot;t allocate inteface !&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|iface
comma
l_int|0
comma
id|tsize
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
id|init_completion
c_func
(paren
op_amp
id|iface-&gt;complete
)paren
suffix:semicolon
id|iface-&gt;bsteps
op_assign
id|bsteps
suffix:semicolon
id|iface-&gt;chan_count
op_assign
id|nchan
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_idle
suffix:semicolon
id|iface-&gt;irq
op_assign
id|np-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
suffix:semicolon
id|iface-&gt;channels
op_assign
(paren
r_struct
id|keywest_chan
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|iface
op_plus
l_int|1
)paren
op_plus
l_int|3UL
)paren
op_amp
op_complement
l_int|3UL
)paren
suffix:semicolon
id|iface-&gt;base
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
op_plus
id|addroffset
comma
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iface-&gt;base
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-keywest: can&squot;t map inteface !&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iface
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|iface-&gt;timeout_timer
)paren
suffix:semicolon
id|iface-&gt;timeout_timer.function
op_assign
id|keywest_timeout
suffix:semicolon
id|iface-&gt;timeout_timer.data
op_assign
(paren
r_int
r_int
)paren
id|iface
suffix:semicolon
multiline_comment|/* Select interface rate */
id|iface-&gt;cur_mode
op_assign
id|KW_I2C_MODE_100KHZ
suffix:semicolon
id|prate
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;AAPL,i2c-rate&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prate
)paren
r_switch
c_cond
(paren
op_star
id|prate
)paren
(brace
r_case
l_int|100
suffix:colon
id|iface-&gt;cur_mode
op_assign
id|KW_I2C_MODE_100KHZ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|50
suffix:colon
id|iface-&gt;cur_mode
op_assign
id|KW_I2C_MODE_50KHZ
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|25
suffix:colon
id|iface-&gt;cur_mode
op_assign
id|KW_I2C_MODE_25KHZ
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;i2c-keywest: unknown rate %ldKhz, using 100KHz&bslash;n&quot;
comma
op_star
id|prate
)paren
suffix:semicolon
)brace
multiline_comment|/* Select standard sub mode */
id|iface-&gt;cur_mode
op_or_assign
id|KW_I2C_MODE_STANDARDSUB
suffix:semicolon
multiline_comment|/* Write mode */
id|write_reg
c_func
(paren
id|reg_mode
comma
id|iface-&gt;cur_mode
)paren
suffix:semicolon
multiline_comment|/* Switch interrupts off &amp; clear them*/
id|write_reg
c_func
(paren
id|reg_ier
comma
l_int|0x00
)paren
suffix:semicolon
id|write_reg
c_func
(paren
id|reg_isr
comma
id|KW_I2C_IRQ_MASK
)paren
suffix:semicolon
multiline_comment|/* Request chip interrupt */
id|rc
op_assign
id|request_irq
c_func
(paren
id|iface-&gt;irq
comma
id|keywest_irq
comma
l_int|0
comma
l_string|&quot;keywest i2c&quot;
comma
id|iface
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;i2c-keywest: can&squot;t get IRQ %d !&bslash;n&quot;
comma
id|iface-&gt;irq
)paren
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|iface-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iface
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dev_set_drvdata
c_func
(paren
id|dev
comma
id|iface
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
id|nchan
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|keywest_chan
op_star
id|chan
op_assign
op_amp
id|iface-&gt;channels
(braket
id|i
)braket
suffix:semicolon
id|u8
id|addr
suffix:semicolon
id|sprintf
c_func
(paren
id|chan-&gt;adapter.name
comma
l_string|&quot;%s %d&quot;
comma
id|np-&gt;parent-&gt;name
comma
id|i
)paren
suffix:semicolon
id|chan-&gt;iface
op_assign
id|iface
suffix:semicolon
id|chan-&gt;chan_no
op_assign
id|i
suffix:semicolon
id|chan-&gt;adapter.id
op_assign
id|I2C_ALGO_SMBUS
suffix:semicolon
id|chan-&gt;adapter.algo
op_assign
op_amp
id|keywest_algorithm
suffix:semicolon
id|chan-&gt;adapter.algo_data
op_assign
l_int|NULL
suffix:semicolon
id|chan-&gt;adapter.client_register
op_assign
l_int|NULL
suffix:semicolon
id|chan-&gt;adapter.client_unregister
op_assign
l_int|NULL
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
op_amp
id|chan-&gt;adapter
comma
id|chan
)paren
suffix:semicolon
id|chan-&gt;adapter.dev.parent
op_assign
id|dev
suffix:semicolon
id|rc
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|chan-&gt;adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i2c-keywest.c: Adapter %s registration failed&bslash;n&quot;
comma
id|chan-&gt;adapter.name
)paren
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
op_amp
id|chan-&gt;adapter
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|probe
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Probe: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|addr
op_assign
l_int|0x00
suffix:semicolon
id|addr
op_le
l_int|0x7f
suffix:semicolon
id|addr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i2c_smbus_xfer
c_func
(paren
op_amp
id|chan-&gt;adapter
comma
id|addr
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|I2C_SMBUS_QUICK
comma
l_int|NULL
)paren
op_ge
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|addr
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Found KeyWest i2c on &bslash;&quot;%s&bslash;&quot;, %d channel%s, stepping: %d bits&bslash;n&quot;
comma
id|np-&gt;parent-&gt;name
comma
id|nchan
comma
id|nchan
OG
l_int|1
ques
c_cond
l_string|&quot;s&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|bsteps
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|dispose_iface
id|dispose_iface
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|keywest_iface
op_star
id|iface
op_assign
id|dev_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|i
comma
id|rc
suffix:semicolon
multiline_comment|/* Make sure we stop all activity */
id|down
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|iface-&gt;state
op_ne
id|state_idle
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
id|set_task_state
c_func
(paren
id|current
comma
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
)brace
id|iface-&gt;state
op_assign
id|state_dead
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|iface-&gt;lock
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|iface-&gt;irq
comma
id|iface
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
multiline_comment|/* Release all channels */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|iface-&gt;chan_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|keywest_chan
op_star
id|chan
op_assign
op_amp
id|iface-&gt;channels
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i2c_get_adapdata
c_func
(paren
op_amp
id|chan-&gt;adapter
)paren
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|rc
op_assign
id|i2c_del_adapter
c_func
(paren
op_amp
id|chan-&gt;adapter
)paren
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
op_amp
id|chan-&gt;adapter
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* We aren&squot;t that prepared to deal with this... */
r_if
c_cond
(paren
id|rc
)paren
id|printk
c_func
(paren
l_string|&quot;i2c-keywest.c: i2c_del_adapter failed, that&squot;s bad !&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|iface-&gt;base
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
id|dev
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iface
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|create_iface_macio
id|create_iface_macio
c_func
(paren
r_struct
id|macio_dev
op_star
id|dev
comma
r_const
r_struct
id|of_match
op_star
id|match
)paren
(brace
r_return
id|create_iface
c_func
(paren
id|dev-&gt;ofdev.node
comma
op_amp
id|dev-&gt;ofdev.dev
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|dispose_iface_macio
id|dispose_iface_macio
c_func
(paren
r_struct
id|macio_dev
op_star
id|dev
)paren
(brace
r_return
id|dispose_iface
c_func
(paren
op_amp
id|dev-&gt;ofdev.dev
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|create_iface_of_platform
id|create_iface_of_platform
c_func
(paren
r_struct
id|of_device
op_star
id|dev
comma
r_const
r_struct
id|of_match
op_star
id|match
)paren
(brace
r_return
id|create_iface
c_func
(paren
id|dev-&gt;node
comma
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|dispose_iface_of_platform
id|dispose_iface_of_platform
c_func
(paren
r_struct
id|of_device
op_star
id|dev
)paren
(brace
r_return
id|dispose_iface
c_func
(paren
op_amp
id|dev-&gt;dev
)paren
suffix:semicolon
)brace
DECL|variable|i2c_keywest_match
r_static
r_struct
id|of_match
id|i2c_keywest_match
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
id|OF_ANY_MATCH
comma
dot
id|type
op_assign
l_string|&quot;i2c&quot;
comma
dot
id|compatible
op_assign
l_string|&quot;keywest&quot;
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|variable|i2c_keywest_macio_driver
r_static
r_struct
id|macio_driver
id|i2c_keywest_macio_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i2c-keywest&quot;
comma
dot
id|match_table
op_assign
id|i2c_keywest_match
comma
dot
id|probe
op_assign
id|create_iface_macio
comma
dot
id|remove
op_assign
id|dispose_iface_macio
)brace
suffix:semicolon
DECL|variable|i2c_keywest_of_platform_driver
r_static
r_struct
id|of_platform_driver
id|i2c_keywest_of_platform_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i2c-keywest&quot;
comma
dot
id|match_table
op_assign
id|i2c_keywest_match
comma
dot
id|probe
op_assign
id|create_iface_of_platform
comma
dot
id|remove
op_assign
id|dispose_iface_of_platform
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|i2c_keywest_init
id|i2c_keywest_init
c_func
(paren
r_void
)paren
(brace
id|macio_register_driver
c_func
(paren
op_amp
id|i2c_keywest_macio_driver
)paren
suffix:semicolon
id|of_register_driver
c_func
(paren
op_amp
id|i2c_keywest_of_platform_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|i2c_keywest_cleanup
id|i2c_keywest_cleanup
c_func
(paren
r_void
)paren
(brace
id|macio_unregister_driver
c_func
(paren
op_amp
id|i2c_keywest_macio_driver
)paren
suffix:semicolon
id|of_unregister_driver
c_func
(paren
op_amp
id|i2c_keywest_of_platform_driver
)paren
suffix:semicolon
)brace
DECL|variable|i2c_keywest_init
id|module_init
c_func
(paren
id|i2c_keywest_init
)paren
suffix:semicolon
DECL|variable|i2c_keywest_cleanup
id|module_exit
c_func
(paren
id|i2c_keywest_cleanup
)paren
suffix:semicolon
eof
