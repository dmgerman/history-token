multiline_comment|/*&n;    amd756.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;&n;    Copyright (c) 1999-2002 Merlin Hughes &lt;merlin@merlin.org&gt;&n;&n;    Shamelessly ripped from i2c-piix4.c:&n;&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt; and&n;    Philip Edelbrock &lt;phil@netroedge.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    2002-04-08: Added nForce support. (Csaba Halasz)&n;    2002-10-03: Fixed nForce PnP I/O port. (Michael Steil)&n;    2002-12-28: Rewritten into something that resembles a Linux driver (hch)&n;    2003-11-29: Added back AMD8111 removed by the previous rewrite.&n;                (Philip Pokorny)&n;*/
multiline_comment|/*&n;   Supports AMD756, AMD766, AMD768, AMD8111 and nVidia nForce&n;   Note: we assume there can only be one device, with one SMBus interface.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* AMD756 SMBus address offsets */
DECL|macro|SMB_ADDR_OFFSET
mdefine_line|#define SMB_ADDR_OFFSET&t;&t;0xE0
DECL|macro|SMB_IOSIZE
mdefine_line|#define SMB_IOSIZE&t;&t;16
DECL|macro|SMB_GLOBAL_STATUS
mdefine_line|#define SMB_GLOBAL_STATUS&t;(0x0 + amd756_ioport)
DECL|macro|SMB_GLOBAL_ENABLE
mdefine_line|#define SMB_GLOBAL_ENABLE&t;(0x2 + amd756_ioport)
DECL|macro|SMB_HOST_ADDRESS
mdefine_line|#define SMB_HOST_ADDRESS&t;(0x4 + amd756_ioport)
DECL|macro|SMB_HOST_DATA
mdefine_line|#define SMB_HOST_DATA&t;&t;(0x6 + amd756_ioport)
DECL|macro|SMB_HOST_COMMAND
mdefine_line|#define SMB_HOST_COMMAND&t;(0x8 + amd756_ioport)
DECL|macro|SMB_HOST_BLOCK_DATA
mdefine_line|#define SMB_HOST_BLOCK_DATA&t;(0x9 + amd756_ioport)
DECL|macro|SMB_HAS_DATA
mdefine_line|#define SMB_HAS_DATA&t;&t;(0xA + amd756_ioport)
DECL|macro|SMB_HAS_DEVICE_ADDRESS
mdefine_line|#define SMB_HAS_DEVICE_ADDRESS&t;(0xC + amd756_ioport)
DECL|macro|SMB_HAS_HOST_ADDRESS
mdefine_line|#define SMB_HAS_HOST_ADDRESS&t;(0xE + amd756_ioport)
DECL|macro|SMB_SNOOP_ADDRESS
mdefine_line|#define SMB_SNOOP_ADDRESS&t;(0xF + amd756_ioport)
multiline_comment|/* PCI Address Constants */
multiline_comment|/* address of I/O space */
DECL|macro|SMBBA
mdefine_line|#define SMBBA&t;&t;0x058&t;&t;/* mh */
DECL|macro|SMBBANFORCE
mdefine_line|#define SMBBANFORCE&t;0x014
multiline_comment|/* general configuration */
DECL|macro|SMBGCFG
mdefine_line|#define SMBGCFG&t;&t;0x041&t;&t;/* mh */
multiline_comment|/* silicon revision code */
DECL|macro|SMBREV
mdefine_line|#define SMBREV&t;&t;0x008
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT&t;500
multiline_comment|/* AMD756 constants */
DECL|macro|AMD756_QUICK
mdefine_line|#define AMD756_QUICK&t;&t;0x00
DECL|macro|AMD756_BYTE
mdefine_line|#define AMD756_BYTE&t;&t;0x01
DECL|macro|AMD756_BYTE_DATA
mdefine_line|#define AMD756_BYTE_DATA&t;0x02
DECL|macro|AMD756_WORD_DATA
mdefine_line|#define AMD756_WORD_DATA&t;0x03
DECL|macro|AMD756_PROCESS_CALL
mdefine_line|#define AMD756_PROCESS_CALL&t;0x04
DECL|macro|AMD756_BLOCK_DATA
mdefine_line|#define AMD756_BLOCK_DATA&t;0x05
DECL|variable|amd756_ioport
r_static
r_int
r_int
id|amd756_ioport
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;  SMBUS event = I/O 28-29 bit 11&n;     see E0 for the status bits and enabled in E2&n;     &n;*/
DECL|macro|GS_ABRT_STS
mdefine_line|#define GS_ABRT_STS&t;(1 &lt;&lt; 0)
DECL|macro|GS_COL_STS
mdefine_line|#define GS_COL_STS&t;(1 &lt;&lt; 1)
DECL|macro|GS_PRERR_STS
mdefine_line|#define GS_PRERR_STS&t;(1 &lt;&lt; 2)
DECL|macro|GS_HST_STS
mdefine_line|#define GS_HST_STS&t;(1 &lt;&lt; 3)
DECL|macro|GS_HCYC_STS
mdefine_line|#define GS_HCYC_STS&t;(1 &lt;&lt; 4)
DECL|macro|GS_TO_STS
mdefine_line|#define GS_TO_STS&t;(1 &lt;&lt; 5)
DECL|macro|GS_SMB_STS
mdefine_line|#define GS_SMB_STS&t;(1 &lt;&lt; 11)
DECL|macro|GS_CLEAR_STS
mdefine_line|#define GS_CLEAR_STS&t;(GS_ABRT_STS | GS_COL_STS | GS_PRERR_STS | &bslash;&n;&t;&t;&t; GS_HCYC_STS | GS_TO_STS )
DECL|macro|GE_CYC_TYPE_MASK
mdefine_line|#define GE_CYC_TYPE_MASK&t;(7)
DECL|macro|GE_HOST_STC
mdefine_line|#define GE_HOST_STC&t;&t;(1 &lt;&lt; 3)
DECL|macro|GE_ABORT
mdefine_line|#define GE_ABORT&t;&t;(1 &lt;&lt; 5)
DECL|function|amd756_transaction
r_static
r_int
id|amd756_transaction
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_int
id|temp
suffix:semicolon
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
id|timeout
op_assign
l_int|0
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: Transaction (pre): GS=%04x, GE=%04x, ADD=%04x, &quot;
l_string|&quot;DAT=%04x&bslash;n&quot;
comma
id|inw_p
c_func
(paren
id|SMB_GLOBAL_STATUS
)paren
comma
id|inw_p
c_func
(paren
id|SMB_GLOBAL_ENABLE
)paren
comma
id|inw_p
c_func
(paren
id|SMB_HOST_ADDRESS
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HOST_DATA
)paren
)paren
suffix:semicolon
multiline_comment|/* Make sure the SMBus host is ready to start transmitting */
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|inw_p
c_func
(paren
id|SMB_GLOBAL_STATUS
)paren
)paren
op_amp
(paren
id|GS_HST_STS
op_or
id|GS_SMB_STS
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: SMBus busy (%04x). Waiting... &bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
r_do
(brace
id|i2c_delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|temp
op_assign
id|inw_p
c_func
(paren
id|SMB_GLOBAL_STATUS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|temp
op_amp
(paren
id|GS_HST_STS
op_or
id|GS_SMB_STS
)paren
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
multiline_comment|/* If the SMBus is still busy, we give up */
r_if
c_cond
(paren
id|timeout
op_ge
id|MAX_TIMEOUT
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: Busy wait timeout (%04x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
id|timeout
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* start the transaction by setting the start bit */
id|outw_p
c_func
(paren
id|inw
c_func
(paren
id|SMB_GLOBAL_ENABLE
)paren
op_or
id|GE_HOST_STC
comma
id|SMB_GLOBAL_ENABLE
)paren
suffix:semicolon
multiline_comment|/* We will always wait for a fraction of a second! */
r_do
(brace
id|i2c_delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|temp
op_assign
id|inw_p
c_func
(paren
id|SMB_GLOBAL_STATUS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|temp
op_amp
id|GS_HST_STS
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
multiline_comment|/* If the SMBus is still busy, we give up */
r_if
c_cond
(paren
id|timeout
op_ge
id|MAX_TIMEOUT
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: Completion timeout!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_abort
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
id|GS_PRERR_STS
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: SMBus Protocol error (no response)!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
id|GS_COL_STS
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_warn
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot; SMBus collision!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
id|GS_TO_STS
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: SMBus protocol timeout!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
id|GS_HCYC_STS
)paren
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot; SMBus protocol success!&bslash;n&quot;
)paren
suffix:semicolon
id|outw_p
c_func
(paren
id|GS_CLEAR_STS
comma
id|SMB_GLOBAL_STATUS
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
(paren
(paren
id|temp
op_assign
id|inw_p
c_func
(paren
id|SMB_GLOBAL_STATUS
)paren
)paren
op_amp
id|GS_CLEAR_STS
)paren
op_ne
l_int|0x00
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: Failed reset at end of transaction (%04x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
macro_line|#endif
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: Transaction (post): GS=%04x, GE=%04x, ADD=%04x, DAT=%04x&bslash;n&quot;
comma
id|inw_p
c_func
(paren
id|SMB_GLOBAL_STATUS
)paren
comma
id|inw_p
c_func
(paren
id|SMB_GLOBAL_ENABLE
)paren
comma
id|inw_p
c_func
(paren
id|SMB_HOST_ADDRESS
)paren
comma
id|inb_p
c_func
(paren
id|SMB_HOST_DATA
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
m_abort
suffix:colon
id|dev_warn
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: Sending abort.&bslash;n&quot;
)paren
suffix:semicolon
id|outw_p
c_func
(paren
id|inw
c_func
(paren
id|SMB_GLOBAL_ENABLE
)paren
op_or
id|GE_ABORT
comma
id|SMB_GLOBAL_ENABLE
)paren
suffix:semicolon
id|i2c_delay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|outw_p
c_func
(paren
id|GS_CLEAR_STS
comma
id|SMB_GLOBAL_STATUS
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Return -1 on error. */
DECL|function|amd756_access
r_static
id|s32
id|amd756_access
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
r_int
id|i
comma
id|len
suffix:semicolon
multiline_comment|/** TODO: Should I supporte the 10-bit transfers? */
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;: I2C_SMBUS_PROC_CALL not supported!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* TODO: Well... It is supported, I&squot;m just not sure what to do here... */
r_return
op_minus
l_int|1
suffix:semicolon
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|outw_p
c_func
(paren
(paren
(paren
id|addr
op_amp
l_int|0x7f
)paren
op_lshift
l_int|1
)paren
op_or
(paren
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMB_HOST_ADDRESS
)paren
suffix:semicolon
id|size
op_assign
id|AMD756_QUICK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
id|outw_p
c_func
(paren
(paren
(paren
id|addr
op_amp
l_int|0x7f
)paren
op_lshift
l_int|1
)paren
op_or
(paren
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMB_HOST_ADDRESS
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
id|command
comma
id|SMB_HOST_DATA
)paren
suffix:semicolon
id|size
op_assign
id|AMD756_BYTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|outw_p
c_func
(paren
(paren
(paren
id|addr
op_amp
l_int|0x7f
)paren
op_lshift
l_int|1
)paren
op_or
(paren
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMB_HOST_ADDRESS
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|SMB_HOST_COMMAND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outw_p
c_func
(paren
id|data-&gt;byte
comma
id|SMB_HOST_DATA
)paren
suffix:semicolon
id|size
op_assign
id|AMD756_BYTE_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|outw_p
c_func
(paren
(paren
(paren
id|addr
op_amp
l_int|0x7f
)paren
op_lshift
l_int|1
)paren
op_or
(paren
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMB_HOST_ADDRESS
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|SMB_HOST_COMMAND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|outw_p
c_func
(paren
id|data-&gt;word
comma
id|SMB_HOST_DATA
)paren
suffix:semicolon
multiline_comment|/* TODO: endian???? */
id|size
op_assign
id|AMD756_WORD_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
id|outw_p
c_func
(paren
(paren
(paren
id|addr
op_amp
l_int|0x7f
)paren
op_lshift
l_int|1
)paren
op_or
(paren
id|read_write
op_amp
l_int|0x01
)paren
comma
id|SMB_HOST_ADDRESS
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|SMB_HOST_COMMAND
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
id|data-&gt;block
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
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
id|outw_p
c_func
(paren
id|len
comma
id|SMB_HOST_DATA
)paren
suffix:semicolon
multiline_comment|/* i = inw_p(SMBHSTCNT); Reset SMBBLKDAT */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
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
)braket
comma
id|SMB_HOST_BLOCK_DATA
)paren
suffix:semicolon
)brace
id|size
op_assign
id|AMD756_BLOCK_DATA
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* How about enabling interrupts... */
id|outw_p
c_func
(paren
id|size
op_amp
id|GE_CYC_TYPE_MASK
comma
id|SMB_GLOBAL_ENABLE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amd756_transaction
c_func
(paren
id|adap
)paren
)paren
multiline_comment|/* Error in transaction */
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
op_logical_or
(paren
id|size
op_eq
id|AMD756_QUICK
)paren
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
id|AMD756_BYTE
suffix:colon
id|data-&gt;byte
op_assign
id|inw_p
c_func
(paren
id|SMB_HOST_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AMD756_BYTE_DATA
suffix:colon
id|data-&gt;byte
op_assign
id|inw_p
c_func
(paren
id|SMB_HOST_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AMD756_WORD_DATA
suffix:colon
id|data-&gt;word
op_assign
id|inw_p
c_func
(paren
id|SMB_HOST_DATA
)paren
suffix:semicolon
multiline_comment|/* TODO: endian???? */
r_break
suffix:semicolon
r_case
id|AMD756_BLOCK_DATA
suffix:colon
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|inw_p
c_func
(paren
id|SMB_HOST_DATA
)paren
op_amp
l_int|0x3f
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;block
(braket
l_int|0
)braket
OG
l_int|32
)paren
(brace
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
l_int|32
suffix:semicolon
)brace
multiline_comment|/* i = inw_p(SMBHSTCNT); Reset SMBBLKDAT */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
id|data-&gt;block
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
)paren
id|data-&gt;block
(braket
id|i
)braket
op_assign
id|inb_p
c_func
(paren
id|SMB_HOST_BLOCK_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd756_func
r_static
id|u32
id|amd756_func
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
op_or
id|I2C_FUNC_SMBUS_PROC_CALL
suffix:semicolon
)brace
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
id|amd756_access
comma
dot
id|functionality
op_assign
id|amd756_func
comma
)brace
suffix:semicolon
DECL|variable|amd756_adapter
r_static
r_struct
id|i2c_adapter
id|amd756_adapter
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
id|I2C_CLASS_SMBUS
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
DECL|enum|chiptype
DECL|enumerator|AMD756
DECL|enumerator|AMD766
DECL|enumerator|AMD768
DECL|enumerator|NFORCE
DECL|enumerator|AMD8111
r_enum
id|chiptype
(brace
id|AMD756
comma
id|AMD766
comma
id|AMD768
comma
id|NFORCE
comma
id|AMD8111
)brace
suffix:semicolon
DECL|variable|amd756_ids
r_static
r_struct
id|pci_device_id
id|amd756_ids
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_AMD
comma
l_int|0x740B
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|AMD756
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
l_int|0x7413
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|AMD766
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
l_int|0x7443
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|AMD768
)brace
comma
(brace
id|PCI_VENDOR_ID_AMD
comma
l_int|0x746B
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|AMD8111
)brace
comma
(brace
id|PCI_VENDOR_ID_NVIDIA
comma
l_int|0x01B4
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|NFORCE
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|amd756_probe
r_static
r_int
id|__devinit
id|amd756_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_int
id|nforce
op_assign
(paren
id|id-&gt;driver_data
op_eq
id|NFORCE
)paren
suffix:semicolon
r_int
id|error
suffix:semicolon
id|u8
id|temp
suffix:semicolon
r_if
c_cond
(paren
id|amd756_ioport
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;: Only one device supported. &quot;
l_string|&quot;(you have a strange motherboard, btw..)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nforce
)paren
(brace
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|pdev-&gt;devfn
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|SMBBANFORCE
comma
op_amp
id|amd756_ioport
)paren
suffix:semicolon
id|amd756_ioport
op_and_assign
l_int|0xfffc
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* amd */
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|pdev-&gt;devfn
)paren
op_ne
l_int|3
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|SMBGCFG
comma
op_amp
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|128
)paren
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;: Error: SMBus controller I/O not enabled!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Determine the address of the SMBus areas */
multiline_comment|/* Technically it is a dword but... */
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|SMBBA
comma
op_amp
id|amd756_ioport
)paren
suffix:semicolon
id|amd756_ioport
op_and_assign
l_int|0xff00
suffix:semicolon
id|amd756_ioport
op_add_assign
id|SMB_ADDR_OFFSET
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|amd756_ioport
comma
id|SMB_IOSIZE
comma
l_string|&quot;amd756-smbus&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;: SMB region 0x%x already in use!&bslash;n&quot;
comma
id|amd756_ioport
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|pdev
comma
id|SMBREV
comma
op_amp
id|temp
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;: SMBREV = 0x%X&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;: AMD756_smba = 0x%X&bslash;n&quot;
comma
id|amd756_ioport
)paren
suffix:semicolon
multiline_comment|/* set up the driverfs linkage to our parent device */
id|amd756_adapter.dev.parent
op_assign
op_amp
id|pdev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|amd756_adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus AMD756 adapter at %04x&quot;
comma
id|amd756_ioport
)paren
suffix:semicolon
id|error
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|amd756_adapter
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
id|pdev-&gt;dev
comma
l_string|&quot;: Adapter registration failed, module not inserted.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|out_err
suffix:colon
id|release_region
c_func
(paren
id|amd756_ioport
comma
id|SMB_IOSIZE
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|amd756_remove
r_static
r_void
id|__devexit
id|amd756_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|amd756_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|amd756_ioport
comma
id|SMB_IOSIZE
)paren
suffix:semicolon
)brace
DECL|variable|amd756_driver
r_static
r_struct
id|pci_driver
id|amd756_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;amd756 smbus&quot;
comma
dot
id|id_table
op_assign
id|amd756_ids
comma
dot
id|probe
op_assign
id|amd756_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|amd756_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|amd756_init
r_static
r_int
id|__init
id|amd756_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|amd756_driver
)paren
suffix:semicolon
)brace
DECL|function|amd756_exit
r_static
r_void
id|__exit
id|amd756_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|amd756_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Merlin Hughes &lt;merlin@merlin.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AMD756/766/768/8111 and nVidia nForce SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_init
c_func
(paren
id|amd756_init
)paren
id|module_exit
c_func
(paren
id|amd756_exit
)paren
eof
