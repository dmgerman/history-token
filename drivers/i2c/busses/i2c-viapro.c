multiline_comment|/*&n;    i2c-viapro.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;    Copyright (c) 1998 - 2002  Frodo Looijaard &lt;frodol@dds.nl&gt;, &n;    Philip Edelbrock &lt;phil@netroedge.com&gt;, Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt;,&n;    Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;   Supports Via devices:&n;&t;82C596A/B (0x3050)&n;&t;82C596B (0x3051)&n;&t;82C686A/B&n;&t;8231&n;&t;8233&n;&t;8233A (0x3147 and 0x3177)&n;&t;8235&n;&t;8237&n;   Note: we assume there can only be one device, with one SMBus interface.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|vt596_pdev
r_static
r_struct
id|pci_dev
op_star
id|vt596_pdev
suffix:semicolon
DECL|macro|SMBBA1
mdefine_line|#define SMBBA1&t;   &t; 0x90
DECL|macro|SMBBA2
mdefine_line|#define SMBBA2     &t; 0x80
DECL|macro|SMBBA3
mdefine_line|#define SMBBA3     &t; 0xD0
multiline_comment|/* SMBus address offsets */
DECL|variable|vt596_smba
r_static
r_int
r_int
id|vt596_smba
suffix:semicolon
DECL|macro|SMBHSTSTS
mdefine_line|#define SMBHSTSTS&t;(vt596_smba + 0)
DECL|macro|SMBHSLVSTS
mdefine_line|#define SMBHSLVSTS&t;(vt596_smba + 1)
DECL|macro|SMBHSTCNT
mdefine_line|#define SMBHSTCNT&t;(vt596_smba + 2)
DECL|macro|SMBHSTCMD
mdefine_line|#define SMBHSTCMD&t;(vt596_smba + 3)
DECL|macro|SMBHSTADD
mdefine_line|#define SMBHSTADD&t;(vt596_smba + 4)
DECL|macro|SMBHSTDAT0
mdefine_line|#define SMBHSTDAT0&t;(vt596_smba + 5)
DECL|macro|SMBHSTDAT1
mdefine_line|#define SMBHSTDAT1&t;(vt596_smba + 6)
DECL|macro|SMBBLKDAT
mdefine_line|#define SMBBLKDAT&t;(vt596_smba + 7)
DECL|macro|SMBSLVCNT
mdefine_line|#define SMBSLVCNT&t;(vt596_smba + 8)
DECL|macro|SMBSHDWCMD
mdefine_line|#define SMBSHDWCMD&t;(vt596_smba + 9)
DECL|macro|SMBSLVEVT
mdefine_line|#define SMBSLVEVT&t;(vt596_smba + 0xA)
DECL|macro|SMBSLVDAT
mdefine_line|#define SMBSLVDAT&t;(vt596_smba + 0xC)
multiline_comment|/* PCI Address Constants */
multiline_comment|/* SMBus data in configuration space can be found in two places,&n;   We try to select the better one*/
DECL|variable|smb_cf_hstcfg
r_static
r_int
r_int
id|smb_cf_hstcfg
op_assign
l_int|0xD2
suffix:semicolon
DECL|macro|SMBHSTCFG
mdefine_line|#define SMBHSTCFG   (smb_cf_hstcfg)
DECL|macro|SMBSLVC
mdefine_line|#define SMBSLVC     (smb_cf_hstcfg + 1)
DECL|macro|SMBSHDW1
mdefine_line|#define SMBSHDW1    (smb_cf_hstcfg + 2)
DECL|macro|SMBSHDW2
mdefine_line|#define SMBSHDW2    (smb_cf_hstcfg + 3)
DECL|macro|SMBREV
mdefine_line|#define SMBREV      (smb_cf_hstcfg + 4)
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT&t;500
DECL|macro|ENABLE_INT9
mdefine_line|#define ENABLE_INT9&t;0
multiline_comment|/* VT82C596 constants */
DECL|macro|VT596_QUICK
mdefine_line|#define VT596_QUICK      0x00
DECL|macro|VT596_BYTE
mdefine_line|#define VT596_BYTE       0x04
DECL|macro|VT596_BYTE_DATA
mdefine_line|#define VT596_BYTE_DATA  0x08
DECL|macro|VT596_WORD_DATA
mdefine_line|#define VT596_WORD_DATA  0x0C
DECL|macro|VT596_BLOCK_DATA
mdefine_line|#define VT596_BLOCK_DATA 0x14
multiline_comment|/* If force is set to anything different from 0, we forcibly enable the&n;   VT596. DANGEROUS! */
DECL|variable|force
r_static
r_int
id|force
suffix:semicolon
id|module_param
c_func
(paren
id|force
comma
r_bool
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|force
comma
l_string|&quot;Forcibly enable the SMBus. DANGEROUS!&quot;
)paren
suffix:semicolon
multiline_comment|/* If force_addr is set to anything different from 0, we forcibly enable&n;   the VT596 at the given address. VERY DANGEROUS! */
DECL|variable|force_addr
r_static
id|u16
id|force_addr
suffix:semicolon
id|module_param
c_func
(paren
id|force_addr
comma
id|ushort
comma
l_int|0
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|force_addr
comma
l_string|&quot;Forcibly enable the SMBus at the given address. &quot;
l_string|&quot;EXTREMELY DANGEROUS!&quot;
)paren
suffix:semicolon
DECL|variable|vt596_adapter
r_static
r_struct
id|i2c_adapter
id|vt596_adapter
suffix:semicolon
multiline_comment|/* Another internally used function */
DECL|function|vt596_transaction
r_static
r_int
id|vt596_transaction
c_func
(paren
r_void
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
id|vt596_adapter.dev
comma
l_string|&quot;Transaction (pre): CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMBHSTCNT
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTCMD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTADD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT1
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
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
)paren
op_ne
l_int|0x00
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;SMBus busy (0x%02x). &quot;
l_string|&quot;Resetting...&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|temp
comma
id|SMBHSTSTS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
)paren
op_ne
l_int|0x00
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;Failed! (0x%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|dev_dbg
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;Successfull!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* start the transaction by setting bit 6 */
id|outb_p
c_func
(paren
id|inb
c_func
(paren
id|SMBHSTCNT
)paren
op_or
l_int|0x040
comma
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* We will always wait for a fraction of a second! &n;&t;   I don&squot;t know if VIA needs this, Intel did  */
r_do
(brace
id|msleep
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
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|temp
op_amp
l_int|0x01
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
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;SMBus Timeout!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x10
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
id|vt596_adapter.dev
comma
l_string|&quot;Error: Failed bus transaction&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x08
)paren
(brace
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;Bus collision! SMBus may be &quot;
l_string|&quot;locked until next hard&bslash;nreset. (sorry!)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Clock stops and slave is stuck in mid-transmission */
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x04
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
id|vt596_adapter.dev
comma
l_string|&quot;Error: no response!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
op_ne
l_int|0x00
)paren
id|outb_p
c_func
(paren
id|inb
c_func
(paren
id|SMBHSTSTS
)paren
comma
id|SMBHSTSTS
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
)paren
op_ne
l_int|0x00
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;Failed reset at end of &quot;
l_string|&quot;transaction (%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
id|dev_dbg
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;Transaction (post): CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, DAT1=%02x&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|SMBHSTCNT
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTCMD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTADD
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
comma
id|inb_p
c_func
(paren
id|SMBHSTDAT1
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Return -1 on error. */
DECL|function|vt596_access
r_static
id|s32
id|vt596_access
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
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
id|dev_info
c_func
(paren
op_amp
id|vt596_adapter.dev
comma
l_string|&quot;I2C_SMBUS_PROC_CALL not supported!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|outb_p
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
id|SMBHSTADD
)paren
suffix:semicolon
id|size
op_assign
id|VT596_QUICK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
id|outb_p
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
id|SMBHSTADD
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
id|SMBHSTCMD
)paren
suffix:semicolon
id|size
op_assign
id|VT596_BYTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|outb_p
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
id|SMBHSTADD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|SMBHSTCMD
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
id|SMBHSTDAT0
)paren
suffix:semicolon
id|size
op_assign
id|VT596_BYTE_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|outb_p
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
id|SMBHSTADD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|SMBHSTCMD
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
op_amp
l_int|0xff
comma
id|SMBHSTDAT0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
(paren
id|data-&gt;word
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
comma
id|SMBHSTDAT1
)paren
suffix:semicolon
)brace
id|size
op_assign
id|VT596_WORD_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
id|outb_p
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
id|SMBHSTADD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|command
comma
id|SMBHSTCMD
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
id|I2C_SMBUS_BLOCK_MAX
)paren
id|len
op_assign
id|I2C_SMBUS_BLOCK_MAX
suffix:semicolon
id|outb_p
c_func
(paren
id|len
comma
id|SMBHSTDAT0
)paren
suffix:semicolon
id|i
op_assign
id|inb_p
c_func
(paren
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* Reset SMBBLKDAT */
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
id|SMBBLKDAT
)paren
suffix:semicolon
)brace
id|size
op_assign
id|VT596_BLOCK_DATA
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb_p
c_func
(paren
(paren
id|size
op_amp
l_int|0x1C
)paren
op_plus
(paren
id|ENABLE_INT9
op_amp
l_int|1
)paren
comma
id|SMBHSTCNT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vt596_transaction
c_func
(paren
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
id|VT596_QUICK
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
id|VT596_BYTE
suffix:colon
multiline_comment|/* Where is the result put? I assume here it is in&n;&t;&t; * SMBHSTDAT0 but it might just as well be in the&n;&t;&t; * SMBHSTCMD. No clue in the docs &n;&t;&t; */
id|data-&gt;byte
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VT596_BYTE_DATA
suffix:colon
id|data-&gt;byte
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VT596_WORD_DATA
suffix:colon
id|data-&gt;word
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
op_plus
(paren
id|inb_p
c_func
(paren
id|SMBHSTDAT1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VT596_BLOCK_DATA
suffix:colon
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|inb_p
c_func
(paren
id|SMBHSTDAT0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;block
(braket
l_int|0
)braket
OG
id|I2C_SMBUS_BLOCK_MAX
)paren
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|I2C_SMBUS_BLOCK_MAX
suffix:semicolon
id|i
op_assign
id|inb_p
c_func
(paren
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* Reset SMBBLKDAT */
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
id|SMBBLKDAT
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vt596_func
r_static
id|u32
id|vt596_func
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
id|vt596_access
comma
dot
id|functionality
op_assign
id|vt596_func
comma
)brace
suffix:semicolon
DECL|variable|vt596_adapter
r_static
r_struct
id|i2c_adapter
id|vt596_adapter
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
DECL|function|vt596_probe
r_static
r_int
id|__devinit
id|vt596_probe
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
r_char
id|temp
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Determine the address of the SMBus areas */
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|vt596_smba
op_assign
id|force_addr
op_amp
l_int|0xfff0
suffix:semicolon
id|force
op_assign
l_int|0
suffix:semicolon
r_goto
id|found
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|id-&gt;driver_data
comma
op_amp
id|vt596_smba
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|vt596_smba
op_amp
l_int|0x1
)paren
)paren
(brace
multiline_comment|/* try 2nd address and config reg. for 596 */
r_if
c_cond
(paren
id|id-&gt;device
op_eq
id|PCI_DEVICE_ID_VIA_82C596_3
op_logical_and
op_logical_neg
id|pci_read_config_word
c_func
(paren
id|pdev
comma
id|SMBBA2
comma
op_amp
id|vt596_smba
)paren
op_logical_and
(paren
id|vt596_smba
op_amp
l_int|0x1
)paren
)paren
(brace
id|smb_cf_hstcfg
op_assign
l_int|0x84
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* no matches at all */
id|dev_err
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;Cannot configure &quot;
l_string|&quot;SMBus I/O Base address&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
id|vt596_smba
op_and_assign
l_int|0xfff0
suffix:semicolon
r_if
c_cond
(paren
id|vt596_smba
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
l_string|&quot;SMBus base address &quot;
l_string|&quot;uninitialized - upgrade BIOS or use &quot;
l_string|&quot;force_addr=0xaddr&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|found
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|vt596_smba
comma
l_int|8
comma
l_string|&quot;viapro-smbus&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;SMBus region 0x%x already in use!&bslash;n&quot;
comma
id|vt596_smba
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
id|SMBHSTCFG
comma
op_amp
id|temp
)paren
suffix:semicolon
multiline_comment|/* If force_addr is set, we program the new address here. Just to make&n;&t;   sure, we disable the VT596 first. */
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
id|SMBHSTCFG
comma
id|temp
op_amp
l_int|0xfe
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|pdev
comma
id|id-&gt;driver_data
comma
id|vt596_smba
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
id|SMBHSTCFG
comma
id|temp
op_or
l_int|0x01
)paren
suffix:semicolon
id|dev_warn
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;WARNING: SMBus interface set to new &quot;
l_string|&quot;address 0x%04x!&bslash;n&quot;
comma
id|vt596_smba
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|force
)paren
(brace
multiline_comment|/* NOTE: This assumes I/O space and other allocations &n;&t;&t;&t; * WERE done by the Bios!  Don&squot;t complain if your &n;&t;&t;&t; * hardware does weird things after enabling this. &n;&t;&t;&t; * :&squot;) Check for Bios updates before resorting to &n;&t;&t;&t; * this.&n;&t;&t;&t; */
id|pci_write_config_byte
c_func
(paren
id|pdev
comma
id|SMBHSTCFG
comma
id|temp
op_or
l_int|1
)paren
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;Enabling SMBus device&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev_err
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;SMBUS: Error: Host SMBus &quot;
l_string|&quot;controller not enabled! - upgrade BIOS or &quot;
l_string|&quot;use force=1&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|release_region
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|0x0E
)paren
op_eq
l_int|8
)paren
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;using Interrupt 9 for SMBus.&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|0x0E
)paren
op_eq
l_int|0
)paren
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;using Interrupt SMI# for SMBus.&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|dev_dbg
c_func
(paren
op_amp
id|pdev-&gt;dev
comma
l_string|&quot;Illegal Interrupt configuration &quot;
l_string|&quot;(or code out of date)!&bslash;n&quot;
)paren
suffix:semicolon
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
l_string|&quot;SMBREV = 0x%X&bslash;n&quot;
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
l_string|&quot;VT596_smba = 0x%X&bslash;n&quot;
comma
id|vt596_smba
)paren
suffix:semicolon
id|vt596_adapter.dev.parent
op_assign
op_amp
id|pdev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|vt596_adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus Via Pro adapter at %04x&quot;
comma
id|vt596_smba
)paren
suffix:semicolon
id|vt596_pdev
op_assign
id|pci_dev_get
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_add_adapter
c_func
(paren
op_amp
id|vt596_adapter
)paren
)paren
(brace
id|pci_dev_put
c_func
(paren
id|vt596_pdev
)paren
suffix:semicolon
id|vt596_pdev
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Always return failure here.  This is to allow other drivers to bind&n;&t; * to this pci device.  We don&squot;t really want to have control over the&n;&t; * pci device, we only wanted to read as few register values from it.&n;&t; */
r_return
op_minus
id|ENODEV
suffix:semicolon
id|release_region
suffix:colon
id|release_region
c_func
(paren
id|vt596_smba
comma
l_int|8
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|variable|vt596_ids
r_static
r_struct
id|pci_device_id
id|vt596_ids
(braket
)braket
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C596_3
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA1
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C596B_3
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA1
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C686_4
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA1
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8233_0
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA3
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8233A
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA3
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8235
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA3
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8237
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA3
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8231_4
)paren
comma
dot
id|driver_data
op_assign
id|SMBBA1
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|pci
comma
id|vt596_ids
)paren
suffix:semicolon
DECL|variable|vt596_driver
r_static
r_struct
id|pci_driver
id|vt596_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vt596_smbus&quot;
comma
dot
id|id_table
op_assign
id|vt596_ids
comma
dot
id|probe
op_assign
id|vt596_probe
comma
)brace
suffix:semicolon
DECL|function|i2c_vt596_init
r_static
r_int
id|__init
id|i2c_vt596_init
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
id|vt596_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_vt596_exit
r_static
r_void
id|__exit
id|i2c_vt596_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|vt596_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vt596_pdev
op_ne
l_int|NULL
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|vt596_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|vt596_smba
comma
l_int|8
)paren
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|vt596_pdev
)paren
suffix:semicolon
id|vt596_pdev
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt; and &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;vt82c596 SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_vt596_init
id|module_init
c_func
(paren
id|i2c_vt596_init
)paren
suffix:semicolon
DECL|variable|i2c_vt596_exit
id|module_exit
c_func
(paren
id|i2c_vt596_exit
)paren
suffix:semicolon
eof
