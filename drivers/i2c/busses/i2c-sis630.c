multiline_comment|/*&n;    i2c-sis630.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;&n;    Copyright (c) 2002,2003 Alexander Malysh &lt;amalysh@web.de&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;   Changes:&n;   24.08.2002&n;   &t;Fixed the typo in sis630_access (Thanks to Mark M. Hoffman)&n;&t;Changed sis630_transaction.(Thanks to Mark M. Hoffman)&n;   18.09.2002&n;&t;Added SIS730 as supported.&n;   21.09.2002&n;&t;Added high_clock module option.If this option is set&n;&t;used Host Master Clock 56KHz (default 14KHz).For now we save old Host&n;&t;Master Clock and after transaction completed restore (otherwise&n;&t;it&squot;s confuse BIOS and hung Machine).&n;   24.09.2002&n;&t;Fixed typo in sis630_access&n;&t;Fixed logical error by restoring of Host Master Clock&n;   31.07.2003&n;   &t;Added block data read/write support.&n;*/
multiline_comment|/*&n;   Status: beta&n;&n;   Supports:&n;&t;SIS 630&n;&t;SIS 730&n;&n;   Note: we assume there can only be one device, with one SMBus interface.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* SIS630 SMBus registers */
DECL|macro|SMB_STS
mdefine_line|#define SMB_STS&t;&t;&t;0x80&t;/* status */
DECL|macro|SMB_EN
mdefine_line|#define SMB_EN&t;&t;&t;0x81&t;/* status enable */
DECL|macro|SMB_CNT
mdefine_line|#define SMB_CNT&t;&t;&t;0x82
DECL|macro|SMBHOST_CNT
mdefine_line|#define SMBHOST_CNT&t;&t;0x83
DECL|macro|SMB_ADDR
mdefine_line|#define SMB_ADDR&t;&t;0x84
DECL|macro|SMB_CMD
mdefine_line|#define SMB_CMD&t;&t;&t;0x85
DECL|macro|SMB_PCOUNT
mdefine_line|#define SMB_PCOUNT&t;&t;0x86&t;/* processed count */
DECL|macro|SMB_COUNT
mdefine_line|#define SMB_COUNT&t;&t;0x87
DECL|macro|SMB_BYTE
mdefine_line|#define SMB_BYTE&t;&t;0x88&t;/* ~0x8F data byte field */
DECL|macro|SMBDEV_ADDR
mdefine_line|#define SMBDEV_ADDR&t;&t;0x90
DECL|macro|SMB_DB0
mdefine_line|#define SMB_DB0&t;&t;&t;0x91
DECL|macro|SMB_DB1
mdefine_line|#define SMB_DB1&t;&t;&t;0x92
DECL|macro|SMB_SAA
mdefine_line|#define SMB_SAA&t;&t;&t;0x93
multiline_comment|/* register count for request_region */
DECL|macro|SIS630_SMB_IOREGION
mdefine_line|#define SIS630_SMB_IOREGION&t;20
multiline_comment|/* PCI address constants */
multiline_comment|/* acpi base address register  */
DECL|macro|SIS630_ACPI_BASE_REG
mdefine_line|#define SIS630_ACPI_BASE_REG&t;0x74
multiline_comment|/* bios control register */
DECL|macro|SIS630_BIOS_CTL_REG
mdefine_line|#define SIS630_BIOS_CTL_REG&t;0x40
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT&t;&t;500
multiline_comment|/* SIS630 constants */
DECL|macro|SIS630_QUICK
mdefine_line|#define SIS630_QUICK&t;&t;0x00
DECL|macro|SIS630_BYTE
mdefine_line|#define SIS630_BYTE&t;&t;0x01
DECL|macro|SIS630_BYTE_DATA
mdefine_line|#define SIS630_BYTE_DATA&t;0x02
DECL|macro|SIS630_WORD_DATA
mdefine_line|#define SIS630_WORD_DATA&t;0x03
DECL|macro|SIS630_PCALL
mdefine_line|#define SIS630_PCALL&t;&t;0x04
DECL|macro|SIS630_BLOCK_DATA
mdefine_line|#define SIS630_BLOCK_DATA&t;0x05
multiline_comment|/* insmod parameters */
DECL|variable|high_clock
r_static
r_int
id|high_clock
op_assign
l_int|0
suffix:semicolon
DECL|variable|force
r_static
r_int
id|force
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|high_clock
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|high_clock
comma
l_string|&quot;Set Host Master Clock to 56KHz (default 14KHz).&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|force
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|force
comma
l_string|&quot;Forcibly enable the SIS630. DANGEROUS!&quot;
)paren
suffix:semicolon
multiline_comment|/* acpi base address */
DECL|variable|acpi_base
r_static
r_int
r_int
id|acpi_base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* supported chips */
DECL|variable|supported
r_static
r_int
id|supported
(braket
)braket
op_assign
(brace
id|PCI_DEVICE_ID_SI_630
comma
id|PCI_DEVICE_ID_SI_730
comma
l_int|0
multiline_comment|/* terminates the list */
)brace
suffix:semicolon
DECL|function|sis630_read
r_static
r_inline
id|u8
id|sis630_read
c_func
(paren
id|u8
id|reg
)paren
(brace
r_return
id|inb
c_func
(paren
id|acpi_base
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|sis630_write
r_static
r_inline
r_void
id|sis630_write
c_func
(paren
id|u8
id|reg
comma
id|u8
id|data
)paren
(brace
id|outb
c_func
(paren
id|data
comma
id|acpi_base
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|sis630_transaction_start
r_static
r_int
id|sis630_transaction_start
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|size
comma
id|u8
op_star
id|oldclock
)paren
(brace
r_int
id|temp
suffix:semicolon
multiline_comment|/* Make sure the SMBus host is ready to start transmitting. */
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|sis630_read
c_func
(paren
id|SMB_CNT
)paren
op_amp
l_int|0x03
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
l_string|&quot;SMBus busy (%02x).Resetting...&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* kill smbus transaction */
id|sis630_write
c_func
(paren
id|SMBHOST_CNT
comma
l_int|0x20
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|sis630_read
c_func
(paren
id|SMB_CNT
)paren
op_amp
l_int|0x03
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
l_string|&quot;Failed! (%02x)&bslash;n&quot;
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
id|adap-&gt;dev
comma
l_string|&quot;Successfull!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* save old clock, so we can prevent machine for hung */
op_star
id|oldclock
op_assign
id|sis630_read
c_func
(paren
id|SMB_CNT
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;saved clock 0x%02x&bslash;n&quot;
comma
op_star
id|oldclock
)paren
suffix:semicolon
multiline_comment|/* disable timeout interrupt , set Host Master Clock to 56KHz if requested */
r_if
c_cond
(paren
id|high_clock
OG
l_int|0
)paren
id|sis630_write
c_func
(paren
id|SMB_CNT
comma
l_int|0x20
)paren
suffix:semicolon
r_else
id|sis630_write
c_func
(paren
id|SMB_CNT
comma
(paren
op_star
id|oldclock
op_amp
op_complement
l_int|0x40
)paren
)paren
suffix:semicolon
multiline_comment|/* clear all sticky bits */
id|temp
op_assign
id|sis630_read
c_func
(paren
id|SMB_STS
)paren
suffix:semicolon
id|sis630_write
c_func
(paren
id|SMB_STS
comma
id|temp
op_amp
l_int|0x1e
)paren
suffix:semicolon
multiline_comment|/* start the transaction by setting bit 4 and size */
id|sis630_write
c_func
(paren
id|SMBHOST_CNT
comma
l_int|0x10
op_or
(paren
id|size
op_amp
l_int|0x07
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis630_transaction_wait
r_static
r_int
id|sis630_transaction_wait
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|size
)paren
(brace
r_int
id|temp
comma
id|result
op_assign
l_int|0
comma
id|timeout
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We will always wait for a fraction of a second! */
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
id|sis630_read
c_func
(paren
id|SMB_STS
)paren
suffix:semicolon
multiline_comment|/* check if block transmitted */
r_if
c_cond
(paren
id|size
op_eq
id|SIS630_BLOCK_DATA
op_logical_and
(paren
id|temp
op_amp
l_int|0x10
)paren
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|temp
op_amp
l_int|0x0e
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
l_string|&quot;SMBus Timeout!&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x02
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Error: Failed bus transaction&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x04
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;Bus collision!&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;  TBD: Datasheet say:&n;&t;&t;  the software should clear this bit and restart SMBUS operation.&n;&t;&t;  Should we do it or user start request again?&n;&t;&t;*/
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|sis630_transaction_end
r_static
r_void
id|sis630_transaction_end
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
id|u8
id|oldclock
)paren
(brace
r_int
id|temp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* clear all status &quot;sticky&quot; bits */
id|sis630_write
c_func
(paren
id|SMB_STS
comma
id|temp
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;SMB_CNT before clock restore 0x%02x&bslash;n&quot;
comma
id|sis630_read
c_func
(paren
id|SMB_CNT
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * restore old Host Master Clock if high_clock is set&n;&t; * and oldclock was not 56KHz&n;&t; */
r_if
c_cond
(paren
id|high_clock
OG
l_int|0
op_logical_and
op_logical_neg
(paren
id|oldclock
op_amp
l_int|0x20
)paren
)paren
id|sis630_write
c_func
(paren
id|SMB_CNT
comma
(paren
id|sis630_read
c_func
(paren
id|SMB_CNT
)paren
op_amp
op_complement
l_int|0x20
)paren
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;SMB_CNT after clock restore 0x%02x&bslash;n&quot;
comma
id|sis630_read
c_func
(paren
id|SMB_CNT
)paren
)paren
suffix:semicolon
)brace
DECL|function|sis630_transaction
r_static
r_int
id|sis630_transaction
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|size
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|u8
id|oldclock
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
id|sis630_transaction_start
c_func
(paren
id|adap
comma
id|size
comma
op_amp
id|oldclock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
id|result
op_assign
id|sis630_transaction_wait
c_func
(paren
id|adap
comma
id|size
)paren
suffix:semicolon
id|sis630_transaction_end
c_func
(paren
id|adap
comma
id|oldclock
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
DECL|function|sis630_block_data
r_static
r_int
id|sis630_block_data
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_union
id|i2c_smbus_data
op_star
id|data
comma
r_int
id|read_write
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
comma
id|rc
op_assign
l_int|0
suffix:semicolon
id|u8
id|oldclock
op_assign
l_int|0
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
r_else
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
id|sis630_write
c_func
(paren
id|SMB_COUNT
comma
id|len
)paren
suffix:semicolon
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
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;set data 0x%02x&bslash;n&quot;
comma
id|data-&gt;block
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* set data */
id|sis630_write
c_func
(paren
id|SMB_BYTE
op_plus
(paren
id|i
op_minus
l_int|1
)paren
op_mod
l_int|8
comma
id|data-&gt;block
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|8
op_logical_or
(paren
id|len
OL
l_int|8
op_logical_and
id|i
op_eq
id|len
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;start trans len=%d i=%d&bslash;n&quot;
comma
id|len
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* first transaction */
r_if
c_cond
(paren
id|sis630_transaction_start
c_func
(paren
id|adap
comma
id|SIS630_BLOCK_DATA
comma
op_amp
id|oldclock
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|i
op_minus
l_int|1
)paren
op_mod
l_int|8
op_eq
l_int|7
op_logical_or
id|i
op_eq
id|len
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;trans_wait len=%d i=%d&bslash;n&quot;
comma
id|len
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|8
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;clear smbary_sts len=%d i=%d&bslash;n&quot;
comma
id|len
comma
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;   If this is not first transaction,&n;&t;&t;&t;&t;&t;   we must clear sticky bit.&n;&t;&t;&t;&t;&t;   clear SMBARY_STS&n;&t;&t;&t;&t;&t;*/
id|sis630_write
c_func
(paren
id|SMB_STS
comma
l_int|0x10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sis630_transaction_wait
c_func
(paren
id|adap
comma
id|SIS630_BLOCK_DATA
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;trans_wait failed&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
r_else
(brace
multiline_comment|/* read request */
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|len
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sis630_transaction_start
c_func
(paren
id|adap
comma
id|SIS630_BLOCK_DATA
comma
op_amp
id|oldclock
)paren
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
id|sis630_transaction_wait
c_func
(paren
id|adap
comma
id|SIS630_BLOCK_DATA
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;trans_wait failed&bslash;n&quot;
)paren
suffix:semicolon
id|rc
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* if this first transaction then read byte count */
r_if
c_cond
(paren
id|len
op_eq
l_int|0
)paren
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|sis630_read
c_func
(paren
id|SMB_COUNT
)paren
suffix:semicolon
multiline_comment|/* just to be sure */
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
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
l_int|32
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;block data read len=0x%x&bslash;n&quot;
comma
id|data-&gt;block
(braket
l_int|0
)braket
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
op_logical_and
id|len
OL
id|data-&gt;block
(braket
l_int|0
)braket
suffix:semicolon
id|i
op_increment
comma
id|len
op_increment
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;read i=%d len=%d&bslash;n&quot;
comma
id|i
comma
id|len
)paren
suffix:semicolon
id|data-&gt;block
(braket
id|len
op_plus
l_int|1
)braket
op_assign
id|sis630_read
c_func
(paren
id|SMB_BYTE
op_plus
id|i
)paren
suffix:semicolon
)brace
id|dev_dbg
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;clear smbary_sts len=%d i=%d&bslash;n&quot;
comma
id|len
comma
id|i
)paren
suffix:semicolon
multiline_comment|/* clear SMBARY_STS */
id|sis630_write
c_func
(paren
id|SMB_STS
comma
l_int|0x10
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OL
id|data-&gt;block
(braket
l_int|0
)braket
)paren
(brace
suffix:semicolon
)brace
)brace
id|sis630_transaction_end
c_func
(paren
id|adap
comma
id|oldclock
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* Return -1 on error. */
DECL|function|sis630_access
r_static
id|s32
id|sis630_access
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
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|I2C_SMBUS_QUICK
suffix:colon
id|sis630_write
c_func
(paren
id|SMB_ADDR
comma
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
)paren
suffix:semicolon
id|size
op_assign
id|SIS630_QUICK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
id|sis630_write
c_func
(paren
id|SMB_ADDR
comma
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
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|sis630_write
c_func
(paren
id|SMB_CMD
comma
id|command
)paren
suffix:semicolon
id|size
op_assign
id|SIS630_BYTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|sis630_write
c_func
(paren
id|SMB_ADDR
comma
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
)paren
suffix:semicolon
id|sis630_write
c_func
(paren
id|SMB_CMD
comma
id|command
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
id|sis630_write
c_func
(paren
id|SMB_BYTE
comma
id|data-&gt;byte
)paren
suffix:semicolon
id|size
op_assign
id|SIS630_BYTE_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|sis630_write
c_func
(paren
id|SMB_ADDR
comma
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
)paren
suffix:semicolon
id|sis630_write
c_func
(paren
id|SMB_CMD
comma
id|command
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
id|sis630_write
c_func
(paren
id|SMB_BYTE
comma
id|data-&gt;word
op_amp
l_int|0xff
)paren
suffix:semicolon
id|sis630_write
c_func
(paren
id|SMB_BYTE
op_plus
l_int|1
comma
(paren
id|data-&gt;word
op_amp
l_int|0xff00
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
id|size
op_assign
(paren
id|size
op_eq
id|I2C_SMBUS_PROC_CALL
ques
c_cond
id|SIS630_PCALL
suffix:colon
id|SIS630_WORD_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
id|sis630_write
c_func
(paren
id|SMB_ADDR
comma
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
)paren
suffix:semicolon
id|sis630_write
c_func
(paren
id|SMB_CMD
comma
id|command
)paren
suffix:semicolon
id|size
op_assign
id|SIS630_BLOCK_DATA
suffix:semicolon
r_return
id|sis630_block_data
c_func
(paren
id|adap
comma
id|data
comma
id|read_write
)paren
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unsupported I2C size&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sis630_transaction
c_func
(paren
id|adap
comma
id|size
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_ne
id|SIS630_PCALL
)paren
op_logical_and
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
id|SIS630_QUICK
)paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
id|SIS630_BYTE
suffix:colon
r_case
id|SIS630_BYTE_DATA
suffix:colon
id|data-&gt;byte
op_assign
id|sis630_read
c_func
(paren
id|SMB_BYTE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIS630_PCALL
suffix:colon
r_case
id|SIS630_WORD_DATA
suffix:colon
id|data-&gt;word
op_assign
id|sis630_read
c_func
(paren
id|SMB_BYTE
)paren
op_plus
(paren
id|sis630_read
c_func
(paren
id|SMB_BYTE
op_plus
l_int|1
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis630_func
r_static
id|u32
id|sis630_func
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
id|I2C_FUNC_SMBUS_PROC_CALL
op_or
id|I2C_FUNC_SMBUS_BLOCK_DATA
suffix:semicolon
)brace
DECL|function|sis630_setup
r_static
r_int
id|sis630_setup
c_func
(paren
r_struct
id|pci_dev
op_star
id|sis630_dev
)paren
(brace
r_int
r_char
id|b
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dummy
op_assign
l_int|NULL
suffix:semicolon
r_int
id|retval
op_assign
op_minus
id|ENODEV
comma
id|i
suffix:semicolon
multiline_comment|/* check for supported SiS devices */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|supported
(braket
id|i
)braket
OG
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|dummy
op_assign
id|pci_get_device
c_func
(paren
id|PCI_VENDOR_ID_SI
comma
id|supported
(braket
id|i
)braket
comma
id|dummy
)paren
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* found */
)brace
r_if
c_cond
(paren
id|dummy
)paren
(brace
id|pci_dev_put
c_func
(paren
id|dummy
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|force
OG
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|sis630_dev-&gt;dev
comma
l_string|&quot;WARNING: Can&squot;t detect SIS630 compatible device, but &quot;
l_string|&quot;loading because of force option enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   Enable ACPI first , so we can accsess reg 74-75&n;&t;   in acpi io space and read acpi base addr&n;&t;*/
r_if
c_cond
(paren
id|pci_read_config_byte
c_func
(paren
id|sis630_dev
comma
id|SIS630_BIOS_CTL_REG
comma
op_amp
id|b
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|sis630_dev-&gt;dev
comma
l_string|&quot;Error: Can&squot;t read bios ctl reg&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* if ACPI already enabled , do nothing */
r_if
c_cond
(paren
op_logical_neg
(paren
id|b
op_amp
l_int|0x80
)paren
op_logical_and
id|pci_write_config_byte
c_func
(paren
id|sis630_dev
comma
id|SIS630_BIOS_CTL_REG
comma
id|b
op_or
l_int|0x80
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|sis630_dev-&gt;dev
comma
l_string|&quot;Error: Can&squot;t enable ACPI&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* Determine the ACPI base address */
r_if
c_cond
(paren
id|pci_read_config_word
c_func
(paren
id|sis630_dev
comma
id|SIS630_ACPI_BASE_REG
comma
op_amp
id|acpi_base
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|sis630_dev-&gt;dev
comma
l_string|&quot;Error: Can&squot;t determine ACPI base address&bslash;n&quot;
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|dev_dbg
c_func
(paren
op_amp
id|sis630_dev-&gt;dev
comma
l_string|&quot;ACPI base at 0x%04x&bslash;n&quot;
comma
id|acpi_base
)paren
suffix:semicolon
multiline_comment|/* Everything is happy, let&squot;s grab the memory and set things up. */
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|acpi_base
op_plus
id|SMB_STS
comma
id|SIS630_SMB_IOREGION
comma
l_string|&quot;sis630-smbus&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|sis630_dev-&gt;dev
comma
l_string|&quot;SMBus registers 0x%04x-0x%04x already &quot;
l_string|&quot;in use!&bslash;n&quot;
comma
id|acpi_base
op_plus
id|SMB_STS
comma
id|acpi_base
op_plus
id|SMB_SAA
)paren
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
m_exit
suffix:colon
r_if
c_cond
(paren
id|retval
)paren
id|acpi_base
op_assign
l_int|0
suffix:semicolon
r_return
id|retval
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
id|sis630_access
comma
dot
id|functionality
op_assign
id|sis630_func
comma
)brace
suffix:semicolon
DECL|variable|sis630_adapter
r_static
r_struct
id|i2c_adapter
id|sis630_adapter
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
id|name
op_assign
l_string|&quot;unset&quot;
comma
dot
id|algo
op_assign
op_amp
id|smbus_algorithm
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|sis630_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_503
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_LPC
)paren
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|sis630_probe
r_static
r_int
id|__devinit
id|sis630_probe
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
r_if
c_cond
(paren
id|sis630_setup
c_func
(paren
id|dev
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SIS630 comp. bus not detected, module not inserted.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* set up the driverfs linkage to our parent device */
id|sis630_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|sprintf
c_func
(paren
id|sis630_adapter.name
comma
l_string|&quot;SMBus SIS630 adapter at %04x&quot;
comma
id|acpi_base
op_plus
id|SMB_STS
)paren
suffix:semicolon
r_return
id|i2c_add_adapter
c_func
(paren
op_amp
id|sis630_adapter
)paren
suffix:semicolon
)brace
DECL|function|sis630_remove
r_static
r_void
id|__devexit
id|sis630_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|acpi_base
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|sis630_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|acpi_base
op_plus
id|SMB_STS
comma
id|SIS630_SMB_IOREGION
)paren
suffix:semicolon
id|acpi_base
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|sis630_driver
r_static
r_struct
id|pci_driver
id|sis630_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sis630 smbus&quot;
comma
dot
id|id_table
op_assign
id|sis630_ids
comma
dot
id|probe
op_assign
id|sis630_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|sis630_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_sis630_init
r_static
r_int
id|__init
id|i2c_sis630_init
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
id|sis630_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_sis630_exit
r_static
r_void
id|__exit
id|i2c_sis630_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|sis630_driver
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alexander Malysh &lt;amalysh@web.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SIS630 SMBus driver&quot;
)paren
suffix:semicolon
DECL|variable|i2c_sis630_init
id|module_init
c_func
(paren
id|i2c_sis630_init
)paren
suffix:semicolon
DECL|variable|i2c_sis630_exit
id|module_exit
c_func
(paren
id|i2c_sis630_exit
)paren
suffix:semicolon
eof
