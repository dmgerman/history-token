multiline_comment|/*&n;    SMBus driver for nVidia nForce2 MCP&n;&n;&t;Ported to 2.5 Patrick Dreker &lt;patrick@dreker.de&gt;,&n;    Copyright (c) 2003  Hans-Frieder Vogt &lt;hfvogt@arcor.de&gt;,&n;    Based on&n;    SMBus 2.0 driver for AMD-8111 IO-Hub&n;    Copyright (c) 2002 Vojtech Pavlik&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    SUPPORTED DEVICES&t;PCI ID&n;    nForce2 MCP&t;&t;0064&n;&n;    This driver supports the 2 SMBuses that are included in the MCP2 of the&n;    nForce2 chipset.&n;*/
multiline_comment|/* Note: we assume there can only be one nForce2, with two SMBus interfaces */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
(paren
l_string|&quot;Hans-Frieder Vogt &lt;hfvogt@arcor.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;nForce2 SMBus driver&quot;
)paren
suffix:semicolon
macro_line|#ifndef PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS
DECL|macro|PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS
mdefine_line|#define PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS   0x0064
macro_line|#endif
DECL|struct|nforce2_smbus
r_struct
id|nforce2_smbus
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
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
DECL|member|size
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * nVidia nForce2 SMBus control register definitions&n; */
DECL|macro|NFORCE_PCI_SMB1
mdefine_line|#define NFORCE_PCI_SMB1&t;0x50
DECL|macro|NFORCE_PCI_SMB2
mdefine_line|#define NFORCE_PCI_SMB2&t;0x54
multiline_comment|/*&n; * ACPI 2.0 chapter 13 SMBus 2.0 EC register model&n; */
DECL|macro|NVIDIA_SMB_PRTCL
mdefine_line|#define NVIDIA_SMB_PRTCL&t;(smbus-&gt;base + 0x00)&t;/* protocol, PEC */
DECL|macro|NVIDIA_SMB_STS
mdefine_line|#define NVIDIA_SMB_STS&t;&t;(smbus-&gt;base + 0x01)&t;/* status */
DECL|macro|NVIDIA_SMB_ADDR
mdefine_line|#define NVIDIA_SMB_ADDR&t;&t;(smbus-&gt;base + 0x02)&t;/* address */
DECL|macro|NVIDIA_SMB_CMD
mdefine_line|#define NVIDIA_SMB_CMD&t;&t;(smbus-&gt;base + 0x03)&t;/* command */
DECL|macro|NVIDIA_SMB_DATA
mdefine_line|#define NVIDIA_SMB_DATA&t;&t;(smbus-&gt;base + 0x04)&t;/* 32 data registers */
DECL|macro|NVIDIA_SMB_BCNT
mdefine_line|#define NVIDIA_SMB_BCNT&t;&t;(smbus-&gt;base + 0x24)&t;/* number of data bytes */
DECL|macro|NVIDIA_SMB_ALRM_A
mdefine_line|#define NVIDIA_SMB_ALRM_A&t;(smbus-&gt;base + 0x25)&t;/* alarm address */
DECL|macro|NVIDIA_SMB_ALRM_D
mdefine_line|#define NVIDIA_SMB_ALRM_D&t;(smbus-&gt;base + 0x26)&t;/* 2 bytes alarm data */
DECL|macro|NVIDIA_SMB_STS_DONE
mdefine_line|#define NVIDIA_SMB_STS_DONE&t;0x80
DECL|macro|NVIDIA_SMB_STS_ALRM
mdefine_line|#define NVIDIA_SMB_STS_ALRM&t;0x40
DECL|macro|NVIDIA_SMB_STS_RES
mdefine_line|#define NVIDIA_SMB_STS_RES&t;0x20
DECL|macro|NVIDIA_SMB_STS_STATUS
mdefine_line|#define NVIDIA_SMB_STS_STATUS&t;0x1f
DECL|macro|NVIDIA_SMB_PRTCL_WRITE
mdefine_line|#define NVIDIA_SMB_PRTCL_WRITE&t;&t;&t;0x00
DECL|macro|NVIDIA_SMB_PRTCL_READ
mdefine_line|#define NVIDIA_SMB_PRTCL_READ&t;&t;&t;0x01
DECL|macro|NVIDIA_SMB_PRTCL_QUICK
mdefine_line|#define NVIDIA_SMB_PRTCL_QUICK&t;&t;&t;0x02
DECL|macro|NVIDIA_SMB_PRTCL_BYTE
mdefine_line|#define NVIDIA_SMB_PRTCL_BYTE&t;&t;&t;0x04
DECL|macro|NVIDIA_SMB_PRTCL_BYTE_DATA
mdefine_line|#define NVIDIA_SMB_PRTCL_BYTE_DATA&t;&t;0x06
DECL|macro|NVIDIA_SMB_PRTCL_WORD_DATA
mdefine_line|#define NVIDIA_SMB_PRTCL_WORD_DATA&t;&t;0x08
DECL|macro|NVIDIA_SMB_PRTCL_BLOCK_DATA
mdefine_line|#define NVIDIA_SMB_PRTCL_BLOCK_DATA&t;&t;0x0a
DECL|macro|NVIDIA_SMB_PRTCL_PROC_CALL
mdefine_line|#define NVIDIA_SMB_PRTCL_PROC_CALL&t;&t;0x0c
DECL|macro|NVIDIA_SMB_PRTCL_BLOCK_PROC_CALL
mdefine_line|#define NVIDIA_SMB_PRTCL_BLOCK_PROC_CALL&t;0x0d
DECL|macro|NVIDIA_SMB_PRTCL_I2C_BLOCK_DATA
mdefine_line|#define NVIDIA_SMB_PRTCL_I2C_BLOCK_DATA&t;&t;0x4a
DECL|macro|NVIDIA_SMB_PRTCL_PEC
mdefine_line|#define NVIDIA_SMB_PRTCL_PEC&t;&t;&t;0x80
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT 256
r_static
id|s32
id|nforce2_access
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
suffix:semicolon
r_static
id|u32
id|nforce2_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
suffix:semicolon
DECL|variable|smbus_algorithm
r_static
r_struct
id|i2c_algorithm
id|smbus_algorithm
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Non-I2C SMBus adapter&quot;
comma
dot
id|id
op_assign
id|I2C_ALGO_SMBUS
comma
dot
id|smbus_xfer
op_assign
id|nforce2_access
comma
dot
id|functionality
op_assign
id|nforce2_func
comma
)brace
suffix:semicolon
DECL|variable|nforce2_adapter
r_static
r_struct
id|i2c_adapter
id|nforce2_adapter
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
r_class
op_assign
id|I2C_CLASS_HWMON
comma
dot
id|algo
op_assign
op_amp
id|smbus_algorithm
comma
dot
id|name
op_assign
l_string|&quot;unset&quot;
comma
)brace
suffix:semicolon
multiline_comment|/* Return -1 on error. See smbus.h for more information */
DECL|function|nforce2_access
r_static
id|s32
id|nforce2_access
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
id|nforce2_smbus
op_star
id|smbus
op_assign
id|adap-&gt;algo_data
suffix:semicolon
r_int
r_char
id|protocol
comma
id|pec
comma
id|temp
suffix:semicolon
r_int
r_char
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to keep the compiler quiet */
r_int
id|timeout
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|protocol
op_assign
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
ques
c_cond
id|NVIDIA_SMB_PRTCL_READ
suffix:colon
id|NVIDIA_SMB_PRTCL_WRITE
suffix:semicolon
id|pec
op_assign
(paren
id|flags
op_amp
id|I2C_CLIENT_PEC
)paren
ques
c_cond
id|NVIDIA_SMB_PRTCL_PEC
suffix:colon
l_int|0
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
id|protocol
op_or_assign
id|NVIDIA_SMB_PRTCL_QUICK
suffix:semicolon
id|read_write
op_assign
id|I2C_SMBUS_WRITE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outb_p
c_func
(paren
id|command
comma
id|NVIDIA_SMB_CMD
)paren
suffix:semicolon
id|protocol
op_or_assign
id|NVIDIA_SMB_PRTCL_BYTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|outb_p
c_func
(paren
id|command
comma
id|NVIDIA_SMB_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outb_p
c_func
(paren
id|data-&gt;byte
comma
id|NVIDIA_SMB_DATA
)paren
suffix:semicolon
id|protocol
op_or_assign
id|NVIDIA_SMB_PRTCL_BYTE_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|outb_p
c_func
(paren
id|command
comma
id|NVIDIA_SMB_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|outb_p
c_func
(paren
id|data-&gt;word
comma
id|NVIDIA_SMB_DATA
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data-&gt;word
op_rshift
l_int|8
comma
id|NVIDIA_SMB_DATA
op_plus
l_int|1
)paren
suffix:semicolon
)brace
id|protocol
op_or_assign
id|NVIDIA_SMB_PRTCL_WORD_DATA
op_or
id|pec
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
id|outb_p
c_func
(paren
id|command
comma
id|NVIDIA_SMB_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
id|len
op_assign
id|min_t
c_func
(paren
id|u8
comma
id|data-&gt;block
(braket
l_int|0
)braket
comma
l_int|32
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|len
comma
id|NVIDIA_SMB_BCNT
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
id|i
op_increment
)paren
id|outb_p
c_func
(paren
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
comma
id|NVIDIA_SMB_DATA
op_plus
id|i
)paren
suffix:semicolon
)brace
id|protocol
op_or_assign
id|NVIDIA_SMB_PRTCL_BLOCK_DATA
op_or
id|pec
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_I2C_BLOCK_DATA
suffix:colon
id|len
op_assign
id|min_t
c_func
(paren
id|u8
comma
id|data-&gt;block
(braket
l_int|0
)braket
comma
l_int|32
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|NVIDIA_SMB_CMD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|len
comma
id|NVIDIA_SMB_BCNT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
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
id|outb_p
c_func
(paren
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
comma
id|NVIDIA_SMB_DATA
op_plus
id|i
)paren
suffix:semicolon
id|protocol
op_or_assign
id|NVIDIA_SMB_PRTCL_I2C_BLOCK_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;I2C_SMBUS_PROC_CALL not supported!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;outb_p(command, NVIDIA_SMB_CMD);&n;&t;&t;&t;outb_p(data-&gt;word, NVIDIA_SMB_DATA);&n;&t;&t;&t;outb_p(data-&gt;word &gt;&gt; 8, NVIDIA_SMB_DATA + 1);&n;&t;&t;&t;protocol = NVIDIA_SMB_PRTCL_PROC_CALL | pec;&n;&t;&t;&t;read_write = I2C_SMBUS_READ;&n;&t;&t;&t;break;&n;&t;&t;&t; */
r_case
id|I2C_SMBUS_BLOCK_PROC_CALL
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;I2C_SMBUS_BLOCK_PROC_CALL not supported!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;protocol |= pec;&n;&t;&t;&t;len = min_t(u8, data-&gt;block[0], 31);&n;&t;&t;&t;outb_p(command, NVIDIA_SMB_CMD);&n;&t;&t;&t;outb_p(len, NVIDIA_SMB_BCNT);&n;&t;&t;&t;for (i = 0; i &lt; len; i++)&n;&t;&t;&t;&t;outb_p(data-&gt;block[i + 1], NVIDIA_SMB_DATA + i);&n;&t;&t;&t;protocol = NVIDIA_SMB_PRTCL_BLOCK_PROC_CALL | pec;&n;&t;&t;&t;read_write = I2C_SMBUS_READ;&n;&t;&t;&t;break;&n;&t;&t;&t;*/
r_case
id|I2C_SMBUS_WORD_DATA_PEC
suffix:colon
r_case
id|I2C_SMBUS_BLOCK_DATA_PEC
suffix:colon
r_case
id|I2C_SMBUS_PROC_CALL_PEC
suffix:colon
r_case
id|I2C_SMBUS_BLOCK_PROC_CALL_PEC
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Unexpected software PEC transaction %d&bslash;n.&quot;
comma
id|size
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
r_default
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Unsupported transaction %d&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
(paren
id|addr
op_amp
l_int|0x7f
)paren
op_lshift
l_int|1
comma
id|NVIDIA_SMB_ADDR
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|protocol
comma
id|NVIDIA_SMB_PRTCL
)paren
suffix:semicolon
id|temp
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_STS
)paren
suffix:semicolon
macro_line|#if 0
r_do
(brace
id|i2c_do_pause
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|temp
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_STS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|temp
op_amp
id|NVIDIA_SMB_STS_DONE
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|timeout
op_increment
OL
id|MAX_TIMEOUT
)paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_complement
id|temp
op_amp
id|NVIDIA_SMB_STS_DONE
)paren
(brace
id|udelay
c_func
(paren
l_int|500
)paren
suffix:semicolon
id|temp
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_STS
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_complement
id|temp
op_amp
id|NVIDIA_SMB_STS_DONE
)paren
(brace
id|msleep
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|temp
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_STS
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|timeout
op_ge
id|MAX_TIMEOUT
)paren
op_logical_or
(paren
op_complement
id|temp
op_amp
id|NVIDIA_SMB_STS_DONE
)paren
op_logical_or
(paren
id|temp
op_amp
id|NVIDIA_SMB_STS_STATUS
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_BYTE
suffix:colon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|data-&gt;byte
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
multiline_comment|/* case I2C_SMBUS_PROC_CALL: not supported */
id|data-&gt;word
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_DATA
)paren
op_or
(paren
id|inb_p
c_func
(paren
id|NVIDIA_SMB_DATA
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
multiline_comment|/* case I2C_SMBUS_BLOCK_PROC_CALL: not supported */
id|len
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_BCNT
)paren
suffix:semicolon
id|len
op_assign
id|min_t
c_func
(paren
id|u8
comma
id|len
comma
l_int|32
)paren
suffix:semicolon
r_case
id|I2C_SMBUS_I2C_BLOCK_DATA
suffix:colon
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
id|data-&gt;block
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|inb_p
c_func
(paren
id|NVIDIA_SMB_DATA
op_plus
id|i
)paren
suffix:semicolon
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|len
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nforce2_func
r_static
id|u32
id|nforce2_func
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adapter
)paren
(brace
multiline_comment|/* other functionality might be possible, but is not tested */
r_return
id|I2C_FUNC_SMBUS_QUICK
op_or
id|I2C_FUNC_SMBUS_BYTE
op_or
id|I2C_FUNC_SMBUS_BYTE_DATA
op_or
id|I2C_FUNC_SMBUS_WORD_DATA
multiline_comment|/* |&n;&t;    I2C_FUNC_SMBUS_BLOCK_DATA */
suffix:semicolon
)brace
DECL|variable|nforce2_ids
r_static
r_struct
id|pci_device_id
id|nforce2_ids
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
id|PCI_DEVICE_ID_NVIDIA_NFORCE2_SMBUS
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|nforce2_ids
)paren
suffix:semicolon
DECL|function|nforce2_probe_smb
r_static
r_int
id|__devinit
id|nforce2_probe_smb
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|reg
comma
r_struct
id|nforce2_smbus
op_star
id|smbus
comma
r_char
op_star
id|name
)paren
(brace
id|u16
id|iobase
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|iobase
)paren
op_ne
id|PCIBIOS_SUCCESSFUL
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|smbus-&gt;adapter.dev
comma
l_string|&quot;Error reading PCI config for %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|smbus-&gt;dev
op_assign
id|dev
suffix:semicolon
id|smbus-&gt;base
op_assign
id|iobase
op_amp
l_int|0xfffc
suffix:semicolon
id|smbus-&gt;size
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|smbus-&gt;base
comma
id|smbus-&gt;size
comma
l_string|&quot;nForce2 SMBus&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|smbus-&gt;adapter.dev
comma
l_string|&quot;Error requesting region %02x .. %02X for %s&bslash;n&quot;
comma
id|smbus-&gt;base
comma
id|smbus-&gt;base
op_plus
id|smbus-&gt;size
op_minus
l_int|1
comma
id|name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|smbus-&gt;adapter
op_assign
id|nforce2_adapter
suffix:semicolon
id|smbus-&gt;adapter.algo_data
op_assign
id|smbus
suffix:semicolon
id|smbus-&gt;adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|smbus-&gt;adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus nForce2 adapter at %04x&quot;
comma
id|smbus-&gt;base
)paren
suffix:semicolon
id|error
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|smbus-&gt;adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|smbus-&gt;adapter.dev
comma
l_string|&quot;Failed to register adapter.&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|smbus-&gt;base
comma
id|smbus-&gt;size
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dev_info
c_func
(paren
op_amp
id|smbus-&gt;adapter.dev
comma
l_string|&quot;nForce2 SMBus adapter at %#x&bslash;n&quot;
comma
id|smbus-&gt;base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nforce2_probe
r_static
r_int
id|__devinit
id|nforce2_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_struct
id|nforce2_smbus
op_star
id|smbuses
suffix:semicolon
r_int
id|res1
comma
id|res2
suffix:semicolon
multiline_comment|/* we support 2 SMBus adapters */
r_if
c_cond
(paren
op_logical_neg
(paren
id|smbuses
op_assign
(paren
r_void
op_star
)paren
id|kmalloc
c_func
(paren
l_int|2
op_star
r_sizeof
(paren
r_struct
id|nforce2_smbus
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
(paren
id|smbuses
comma
l_int|0
comma
l_int|2
op_star
r_sizeof
(paren
r_struct
id|nforce2_smbus
)paren
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
id|smbuses
)paren
suffix:semicolon
multiline_comment|/* SMBus adapter 1 */
id|res1
op_assign
id|nforce2_probe_smb
(paren
id|dev
comma
id|NFORCE_PCI_SMB1
comma
op_amp
id|smbuses
(braket
l_int|0
)braket
comma
l_string|&quot;SMB1&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res1
OL
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Error probing SMB1.&bslash;n&quot;
)paren
suffix:semicolon
id|smbuses
(braket
l_int|0
)braket
dot
id|base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to have a check value */
)brace
id|res2
op_assign
id|nforce2_probe_smb
(paren
id|dev
comma
id|NFORCE_PCI_SMB2
comma
op_amp
id|smbuses
(braket
l_int|1
)braket
comma
l_string|&quot;SMB2&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res2
OL
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Error probing SMB2.&bslash;n&quot;
)paren
suffix:semicolon
id|smbuses
(braket
l_int|1
)braket
dot
id|base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to have a check value */
)brace
r_if
c_cond
(paren
(paren
id|res1
OL
l_int|0
)paren
op_logical_and
(paren
id|res2
OL
l_int|0
)paren
)paren
(brace
multiline_comment|/* we did not find even one of the SMBuses, so we give up */
id|kfree
c_func
(paren
id|smbuses
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nforce2_remove
r_static
r_void
id|__devexit
id|nforce2_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|nforce2_smbus
op_star
id|smbuses
op_assign
(paren
r_void
op_star
)paren
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smbuses
(braket
l_int|0
)braket
dot
id|base
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|smbuses
(braket
l_int|0
)braket
dot
id|adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|smbuses
(braket
l_int|0
)braket
dot
id|base
comma
id|smbuses
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|smbuses
(braket
l_int|1
)braket
dot
id|base
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|smbuses
(braket
l_int|1
)braket
dot
id|adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|smbuses
(braket
l_int|1
)braket
dot
id|base
comma
id|smbuses
(braket
l_int|1
)braket
dot
id|size
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|smbuses
)paren
suffix:semicolon
)brace
DECL|variable|nforce2_driver
r_static
r_struct
id|pci_driver
id|nforce2_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;nForce2_smbus&quot;
comma
dot
id|id_table
op_assign
id|nforce2_ids
comma
dot
id|probe
op_assign
id|nforce2_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|nforce2_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|nforce2_init
r_static
r_int
id|__init
id|nforce2_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|nforce2_driver
)paren
suffix:semicolon
)brace
DECL|function|nforce2_exit
r_static
r_void
id|__exit
id|nforce2_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|nforce2_driver
)paren
suffix:semicolon
)brace
DECL|variable|nforce2_init
id|module_init
c_func
(paren
id|nforce2_init
)paren
suffix:semicolon
DECL|variable|nforce2_exit
id|module_exit
c_func
(paren
id|nforce2_exit
)paren
suffix:semicolon
eof
