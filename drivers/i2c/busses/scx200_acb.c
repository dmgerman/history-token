multiline_comment|/*  linux/drivers/i2c/scx200_acb.c &n;&n;    Copyright (c) 2001,2002 Christer Weinigel &lt;wingel@nano-system.com&gt;&n;&n;    National Semiconductor SCx200 ACCESS.bus support&n;    &n;    Based on i2c-keywest.c which is:&n;        Copyright (c) 2001 Benjamin Herrenschmidt &lt;benh@kernel.crashing.org&gt;&n;        Copyright (c) 2000 Philip Edelbrock &lt;phil@stimpy.netroedge.com&gt;&n;    &n;    This program is free software; you can redistribute it and/or&n;    modify it under the terms of the GNU General Public License as&n;    published by the Free Software Foundation; either version 2 of the&n;    License, or (at your option) any later version.&n;   &n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;    General Public License for more details.&n;   &n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/scx200.h&gt;
DECL|macro|NAME
mdefine_line|#define NAME &quot;scx200_acb&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Christer Weinigel &lt;wingel@nano-system.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NatSemi SCx200 ACCESS.bus Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES 4
DECL|variable|base
r_static
r_int
id|base
(braket
id|MAX_DEVICES
)braket
op_assign
(brace
l_int|0x820
comma
l_int|0x840
)brace
suffix:semicolon
id|module_param_array
c_func
(paren
id|base
comma
r_int
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|base
comma
l_string|&quot;Base addresses for the ACCESS.bus controllers&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(KERN_DEBUG NAME &quot;: &quot; x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
multiline_comment|/* The hardware supports interrupt driven mode too, but I haven&squot;t&n;   implemented that. */
DECL|macro|POLLED_MODE
mdefine_line|#define POLLED_MODE 1
DECL|macro|POLL_TIMEOUT
mdefine_line|#define POLL_TIMEOUT (HZ)
DECL|enum|scx200_acb_state
r_enum
id|scx200_acb_state
(brace
DECL|enumerator|state_idle
id|state_idle
comma
DECL|enumerator|state_address
id|state_address
comma
DECL|enumerator|state_command
id|state_command
comma
DECL|enumerator|state_repeat_start
id|state_repeat_start
comma
DECL|enumerator|state_quick
id|state_quick
comma
DECL|enumerator|state_read
id|state_read
comma
DECL|enumerator|state_write
id|state_write
comma
)brace
suffix:semicolon
DECL|variable|scx200_acb_state_name
r_static
r_const
r_char
op_star
id|scx200_acb_state_name
(braket
)braket
op_assign
(brace
l_string|&quot;idle&quot;
comma
l_string|&quot;address&quot;
comma
l_string|&quot;command&quot;
comma
l_string|&quot;repeat_start&quot;
comma
l_string|&quot;quick&quot;
comma
l_string|&quot;read&quot;
comma
l_string|&quot;write&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* Physical interface */
DECL|struct|scx200_acb_iface
r_struct
id|scx200_acb_iface
(brace
DECL|member|next
r_struct
id|scx200_acb_iface
op_star
id|next
suffix:semicolon
DECL|member|adapter
r_struct
id|i2c_adapter
id|adapter
suffix:semicolon
DECL|member|base
r_int
id|base
suffix:semicolon
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* State machine data */
DECL|member|state
r_enum
id|scx200_acb_state
id|state
suffix:semicolon
DECL|member|result
r_int
id|result
suffix:semicolon
DECL|member|address_byte
id|u8
id|address_byte
suffix:semicolon
DECL|member|command
id|u8
id|command
suffix:semicolon
DECL|member|ptr
id|u8
op_star
id|ptr
suffix:semicolon
DECL|member|needs_reset
r_char
id|needs_reset
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Register Definitions */
DECL|macro|ACBSDA
mdefine_line|#define ACBSDA&t;&t;(iface-&gt;base + 0)
DECL|macro|ACBST
mdefine_line|#define ACBST&t;&t;(iface-&gt;base + 1)
DECL|macro|ACBST_SDAST
mdefine_line|#define    ACBST_SDAST&t;&t;0x40 /* SDA Status */
DECL|macro|ACBST_BER
mdefine_line|#define    ACBST_BER&t;&t;0x20 
DECL|macro|ACBST_NEGACK
mdefine_line|#define    ACBST_NEGACK&t;&t;0x10 /* Negative Acknowledge */
DECL|macro|ACBST_STASTR
mdefine_line|#define    ACBST_STASTR&t;&t;0x08 /* Stall After Start */
DECL|macro|ACBST_MASTER
mdefine_line|#define    ACBST_MASTER&t;&t;0x02
DECL|macro|ACBCST
mdefine_line|#define ACBCST&t;&t;(iface-&gt;base + 2)
DECL|macro|ACBCST_BB
mdefine_line|#define    ACBCST_BB&t;&t;0x02
DECL|macro|ACBCTL1
mdefine_line|#define ACBCTL1&t;&t;(iface-&gt;base + 3)
DECL|macro|ACBCTL1_STASTRE
mdefine_line|#define    ACBCTL1_STASTRE&t;0x80
DECL|macro|ACBCTL1_NMINTE
mdefine_line|#define    ACBCTL1_NMINTE&t;0x40
DECL|macro|ACBCTL1_ACK
mdefine_line|#define&t;   ACBCTL1_ACK&t;&t;0x10
DECL|macro|ACBCTL1_STOP
mdefine_line|#define&t;   ACBCTL1_STOP&t;&t;0x02
DECL|macro|ACBCTL1_START
mdefine_line|#define&t;   ACBCTL1_START&t;0x01
DECL|macro|ACBADDR
mdefine_line|#define ACBADDR&t;&t;(iface-&gt;base + 4)
DECL|macro|ACBCTL2
mdefine_line|#define ACBCTL2&t;&t;(iface-&gt;base + 5)
DECL|macro|ACBCTL2_ENABLE
mdefine_line|#define    ACBCTL2_ENABLE&t;0x01
multiline_comment|/************************************************************************/
DECL|function|scx200_acb_machine
r_static
r_void
id|scx200_acb_machine
c_func
(paren
r_struct
id|scx200_acb_iface
op_star
id|iface
comma
id|u8
id|status
)paren
(brace
r_const
r_char
op_star
id|errmsg
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;state %s, status = 0x%02x&bslash;n&quot;
comma
id|scx200_acb_state_name
(braket
id|iface-&gt;state
)braket
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|ACBST_BER
)paren
(brace
id|errmsg
op_assign
l_string|&quot;bus error&quot;
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|ACBST_MASTER
)paren
)paren
(brace
id|errmsg
op_assign
l_string|&quot;not master&quot;
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|ACBST_NEGACK
)paren
r_goto
id|negack
suffix:semicolon
r_switch
c_cond
(paren
id|iface-&gt;state
)paren
(brace
r_case
id|state_idle
suffix:colon
id|dev_warn
c_func
(paren
op_amp
id|iface-&gt;adapter.dev
comma
l_string|&quot;interrupt in idle state&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|state_address
suffix:colon
multiline_comment|/* Do a pointer write first */
id|outb
c_func
(paren
id|iface-&gt;address_byte
op_amp
op_complement
l_int|1
comma
id|ACBSDA
)paren
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_command
suffix:semicolon
r_break
suffix:semicolon
r_case
id|state_command
suffix:colon
id|outb
c_func
(paren
id|iface-&gt;command
comma
id|ACBSDA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iface-&gt;address_byte
op_amp
l_int|1
)paren
id|iface-&gt;state
op_assign
id|state_repeat_start
suffix:semicolon
r_else
id|iface-&gt;state
op_assign
id|state_write
suffix:semicolon
r_break
suffix:semicolon
r_case
id|state_repeat_start
suffix:colon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_START
comma
id|ACBCTL1
)paren
suffix:semicolon
multiline_comment|/* fallthrough */
r_case
id|state_quick
suffix:colon
r_if
c_cond
(paren
id|iface-&gt;address_byte
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|iface-&gt;len
op_eq
l_int|1
)paren
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_ACK
comma
id|ACBCTL1
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_amp
op_complement
id|ACBCTL1_ACK
comma
id|ACBCTL1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|iface-&gt;address_byte
comma
id|ACBSDA
)paren
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_read
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|iface-&gt;address_byte
comma
id|ACBSDA
)paren
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_write
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|state_read
suffix:colon
multiline_comment|/* Set ACK if receiving the last byte */
r_if
c_cond
(paren
id|iface-&gt;len
op_eq
l_int|1
)paren
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_ACK
comma
id|ACBCTL1
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_amp
op_complement
id|ACBCTL1_ACK
comma
id|ACBCTL1
)paren
suffix:semicolon
op_star
id|iface-&gt;ptr
op_increment
op_assign
id|inb
c_func
(paren
id|ACBSDA
)paren
suffix:semicolon
op_decrement
id|iface-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|iface-&gt;len
op_eq
l_int|0
)paren
(brace
id|iface-&gt;result
op_assign
l_int|0
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_idle
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_STOP
comma
id|ACBCTL1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|state_write
suffix:colon
r_if
c_cond
(paren
id|iface-&gt;len
op_eq
l_int|0
)paren
(brace
id|iface-&gt;result
op_assign
l_int|0
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_idle
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_STOP
comma
id|ACBCTL1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
c_func
(paren
op_star
id|iface-&gt;ptr
op_increment
comma
id|ACBSDA
)paren
suffix:semicolon
op_decrement
id|iface-&gt;len
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
suffix:semicolon
id|negack
suffix:colon
id|DBG
c_func
(paren
l_string|&quot;negative acknowledge in state %s&bslash;n&quot;
comma
id|scx200_acb_state_name
(braket
id|iface-&gt;state
)braket
)paren
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_idle
suffix:semicolon
id|iface-&gt;result
op_assign
op_minus
id|ENXIO
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_STOP
comma
id|ACBCTL1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ACBST_STASTR
op_or
id|ACBST_NEGACK
comma
id|ACBST
)paren
suffix:semicolon
r_return
suffix:semicolon
id|error
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|iface-&gt;adapter.dev
comma
l_string|&quot;%s in state %s&bslash;n&quot;
comma
id|errmsg
comma
id|scx200_acb_state_name
(braket
id|iface-&gt;state
)braket
)paren
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_idle
suffix:semicolon
id|iface-&gt;result
op_assign
op_minus
id|EIO
suffix:semicolon
id|iface-&gt;needs_reset
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|scx200_acb_timeout
r_static
r_void
id|scx200_acb_timeout
c_func
(paren
r_struct
id|scx200_acb_iface
op_star
id|iface
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|iface-&gt;adapter.dev
comma
l_string|&quot;timeout in state %s&bslash;n&quot;
comma
id|scx200_acb_state_name
(braket
id|iface-&gt;state
)braket
)paren
suffix:semicolon
id|iface-&gt;state
op_assign
id|state_idle
suffix:semicolon
id|iface-&gt;result
op_assign
op_minus
id|EIO
suffix:semicolon
id|iface-&gt;needs_reset
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef POLLED_MODE
DECL|function|scx200_acb_poll
r_static
r_void
id|scx200_acb_poll
c_func
(paren
r_struct
id|scx200_acb_iface
op_star
id|iface
)paren
(brace
id|u8
id|status
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|timeout
op_assign
id|jiffies
op_plus
id|POLL_TIMEOUT
suffix:semicolon
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
(brace
id|status
op_assign
id|inb
c_func
(paren
id|ACBST
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
id|ACBST_SDAST
op_or
id|ACBST_BER
op_or
id|ACBST_NEGACK
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|scx200_acb_machine
c_func
(paren
id|iface
comma
id|status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
id|scx200_acb_timeout
c_func
(paren
id|iface
)paren
suffix:semicolon
)brace
macro_line|#endif /* POLLED_MODE */
DECL|function|scx200_acb_reset
r_static
r_void
id|scx200_acb_reset
c_func
(paren
r_struct
id|scx200_acb_iface
op_star
id|iface
)paren
(brace
multiline_comment|/* Disable the ACCESS.bus device and Configure the SCL&n;           frequency: 16 clock cycles */
id|outb
c_func
(paren
l_int|0x70
comma
id|ACBCTL2
)paren
suffix:semicolon
multiline_comment|/* Polling mode */
id|outb
c_func
(paren
l_int|0
comma
id|ACBCTL1
)paren
suffix:semicolon
multiline_comment|/* Disable slave address */
id|outb
c_func
(paren
l_int|0
comma
id|ACBADDR
)paren
suffix:semicolon
multiline_comment|/* Enable the ACCESS.bus device */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL2
)paren
op_or
id|ACBCTL2_ENABLE
comma
id|ACBCTL2
)paren
suffix:semicolon
multiline_comment|/* Free STALL after START */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_amp
op_complement
(paren
id|ACBCTL1_STASTRE
op_or
id|ACBCTL1_NMINTE
)paren
comma
id|ACBCTL1
)paren
suffix:semicolon
multiline_comment|/* Send a STOP */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_STOP
comma
id|ACBCTL1
)paren
suffix:semicolon
multiline_comment|/* Clear BER, NEGACK and STASTR bits */
id|outb
c_func
(paren
id|ACBST_BER
op_or
id|ACBST_NEGACK
op_or
id|ACBST_STASTR
comma
id|ACBST
)paren
suffix:semicolon
multiline_comment|/* Clear BB bit */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCST
)paren
op_or
id|ACBCST_BB
comma
id|ACBCST
)paren
suffix:semicolon
)brace
DECL|function|scx200_acb_smbus_xfer
r_static
id|s32
id|scx200_acb_smbus_xfer
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
comma
id|u16
id|address
comma
r_int
r_int
id|flags
comma
r_char
id|rw
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
id|scx200_acb_iface
op_star
id|iface
op_assign
id|i2c_get_adapdata
c_func
(paren
id|adapter
)paren
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
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
r_if
c_cond
(paren
id|rw
op_eq
id|I2C_SMBUS_READ
)paren
(brace
id|len
op_assign
l_int|1
suffix:semicolon
id|buffer
op_assign
op_amp
id|data-&gt;byte
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
l_int|1
suffix:semicolon
id|buffer
op_assign
op_amp
id|command
suffix:semicolon
)brace
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
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|DBG
c_func
(paren
l_string|&quot;size=%d, address=0x%x, command=0x%x, len=%d, read=%d&bslash;n&quot;
comma
id|size
comma
id|address
comma
id|command
comma
id|len
comma
id|rw
op_eq
id|I2C_SMBUS_READ
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
op_logical_and
id|rw
op_eq
id|I2C_SMBUS_READ
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;zero length read&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_logical_and
op_logical_neg
id|buffer
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;nonzero length but no buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
id|iface-&gt;address_byte
op_assign
id|address
op_lshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|rw
op_eq
id|I2C_SMBUS_READ
)paren
id|iface-&gt;address_byte
op_or_assign
l_int|1
suffix:semicolon
id|iface-&gt;command
op_assign
id|command
suffix:semicolon
id|iface-&gt;ptr
op_assign
id|buffer
suffix:semicolon
id|iface-&gt;len
op_assign
id|len
suffix:semicolon
id|iface-&gt;result
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|iface-&gt;needs_reset
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_START
comma
id|ACBCTL1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
id|I2C_SMBUS_QUICK
op_logical_or
id|size
op_eq
id|I2C_SMBUS_BYTE
)paren
id|iface-&gt;state
op_assign
id|state_quick
suffix:semicolon
r_else
id|iface-&gt;state
op_assign
id|state_address
suffix:semicolon
macro_line|#ifdef POLLED_MODE
r_while
c_loop
(paren
id|iface-&gt;state
op_ne
id|state_idle
)paren
id|scx200_acb_poll
c_func
(paren
id|iface
)paren
suffix:semicolon
macro_line|#else /* POLLED_MODE */
macro_line|#error Interrupt driven mode not implemented
macro_line|#endif /* POLLED_MODE */&t;
r_if
c_cond
(paren
id|iface-&gt;needs_reset
)paren
id|scx200_acb_reset
c_func
(paren
id|iface
)paren
suffix:semicolon
id|rc
op_assign
id|iface-&gt;result
suffix:semicolon
id|up
c_func
(paren
op_amp
id|iface-&gt;sem
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
id|rw
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
macro_line|#ifdef DEBUG
id|DBG
c_func
(paren
l_string|&quot;: transfer done, result: %d&quot;
comma
id|rc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; data:&quot;
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
id|len
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|buffer
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|rc
suffix:semicolon
)brace
DECL|function|scx200_acb_func
r_static
id|u32
id|scx200_acb_func
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
DECL|variable|scx200_acb_algorithm
r_static
r_struct
id|i2c_algorithm
id|scx200_acb_algorithm
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;NatSemi SCx200 ACCESS.bus&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SMBUS
comma
dot
id|smbus_xfer
op_assign
id|scx200_acb_smbus_xfer
comma
dot
id|functionality
op_assign
id|scx200_acb_func
comma
)brace
suffix:semicolon
DECL|variable|scx200_acb_list
r_struct
id|scx200_acb_iface
op_star
id|scx200_acb_list
suffix:semicolon
DECL|function|scx200_acb_probe
r_int
id|scx200_acb_probe
c_func
(paren
r_struct
id|scx200_acb_iface
op_star
id|iface
)paren
(brace
id|u8
id|val
suffix:semicolon
multiline_comment|/* Disable the ACCESS.bus device and Configure the SCL&n;           frequency: 16 clock cycles */
id|outb
c_func
(paren
l_int|0x70
comma
id|ACBCTL2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ACBCTL2
)paren
op_ne
l_int|0x70
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;ACBCTL2 readback failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_NMINTE
comma
id|ACBCTL1
)paren
suffix:semicolon
id|val
op_assign
id|inb
c_func
(paren
id|ACBCTL1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;disabled, but ACBCTL1=0x%02x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL2
)paren
op_or
id|ACBCTL2_ENABLE
comma
id|ACBCTL2
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ACBCTL1
)paren
op_or
id|ACBCTL1_NMINTE
comma
id|ACBCTL1
)paren
suffix:semicolon
id|val
op_assign
id|inb
c_func
(paren
id|ACBCTL1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
id|ACBCTL1_NMINTE
)paren
op_ne
id|ACBCTL1_NMINTE
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;enabled, but NMINTE won&squot;t be set, ACBCTL1=0x%02x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scx200_acb_create
r_static
r_int
id|__init
id|scx200_acb_create
c_func
(paren
r_int
id|base
comma
r_int
id|index
)paren
(brace
r_struct
id|scx200_acb_iface
op_star
id|iface
suffix:semicolon
r_struct
id|i2c_adapter
op_star
id|adapter
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_char
id|description
(braket
l_int|64
)braket
suffix:semicolon
id|iface
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|iface
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|iface
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|NAME
l_string|&quot;: can&squot;t allocate memory&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|memset
c_func
(paren
id|iface
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|iface
)paren
)paren
suffix:semicolon
id|adapter
op_assign
op_amp
id|iface-&gt;adapter
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
id|adapter
comma
id|iface
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|adapter-&gt;name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SCx200 ACB%d&quot;
comma
id|index
)paren
suffix:semicolon
id|adapter-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|adapter-&gt;id
op_assign
id|I2C_ALGO_SMBUS
suffix:semicolon
id|adapter-&gt;algo
op_assign
op_amp
id|scx200_acb_algorithm
suffix:semicolon
id|adapter
op_member_access_from_pointer
r_class
op_assign
id|I2C_CLASS_HWMON
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|iface-&gt;sem
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|description
comma
r_sizeof
(paren
id|description
)paren
comma
l_string|&quot;NatSemi SCx200 ACCESS.bus [%s]&quot;
comma
id|adapter-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_region
c_func
(paren
id|base
comma
l_int|8
comma
id|description
)paren
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;can&squot;t allocate io 0x%x-0x%x&bslash;n&quot;
comma
id|base
comma
id|base
op_plus
l_int|8
op_minus
l_int|1
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|iface-&gt;base
op_assign
id|base
suffix:semicolon
id|rc
op_assign
id|scx200_acb_probe
c_func
(paren
id|iface
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;probe failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|scx200_acb_reset
c_func
(paren
id|iface
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_add_adapter
c_func
(paren
id|adapter
)paren
OL
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|adapter-&gt;dev
comma
l_string|&quot;failed to register&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|iface-&gt;next
op_assign
id|scx200_acb_list
suffix:semicolon
id|scx200_acb_list
op_assign
id|iface
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|errout
suffix:colon
r_if
c_cond
(paren
id|iface
)paren
(brace
r_if
c_cond
(paren
id|iface-&gt;base
)paren
id|release_region
c_func
(paren
id|iface-&gt;base
comma
l_int|8
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iface
)paren
suffix:semicolon
)brace
r_return
id|rc
suffix:semicolon
)brace
DECL|variable|scx200
r_static
r_struct
id|pci_device_id
id|scx200
(braket
)braket
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_SCx200_BRIDGE
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_NS
comma
id|PCI_DEVICE_ID_NS_SC1100_BRIDGE
)paren
)brace
comma
(brace
)brace
comma
)brace
suffix:semicolon
DECL|function|scx200_acb_init
r_static
r_int
id|__init
id|scx200_acb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|pr_debug
c_func
(paren
id|NAME
l_string|&quot;: NatSemi SCx200 ACCESS.bus Driver&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Verify that this really is a SCx200 processor */
r_if
c_cond
(paren
id|pci_dev_present
c_func
(paren
id|scx200
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|rc
op_assign
op_minus
id|ENXIO
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
id|MAX_DEVICES
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|base
(braket
id|i
)braket
OG
l_int|0
)paren
id|rc
op_assign
id|scx200_acb_create
c_func
(paren
id|base
(braket
id|i
)braket
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scx200_acb_list
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|scx200_acb_cleanup
r_static
r_void
id|__exit
id|scx200_acb_cleanup
c_func
(paren
r_void
)paren
(brace
r_struct
id|scx200_acb_iface
op_star
id|iface
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|iface
op_assign
id|scx200_acb_list
)paren
op_ne
l_int|NULL
)paren
(brace
id|scx200_acb_list
op_assign
id|iface-&gt;next
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|i2c_del_adapter
c_func
(paren
op_amp
id|iface-&gt;adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|iface-&gt;base
comma
l_int|8
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iface
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|scx200_acb_init
id|module_init
c_func
(paren
id|scx200_acb_init
)paren
suffix:semicolon
DECL|variable|scx200_acb_cleanup
id|module_exit
c_func
(paren
id|scx200_acb_cleanup
)paren
suffix:semicolon
multiline_comment|/*&n;    Local variables:&n;        compile-command: &quot;make -k -C ../.. SUBDIRS=drivers/i2c modules&quot;&n;        c-basic-offset: 8&n;    End:&n;*/
eof
