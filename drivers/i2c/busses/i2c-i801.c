multiline_comment|/*&n;    i801.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;    Copyright (c) 1998 - 2002  Frodo Looijaard &lt;frodol@dds.nl&gt;,&n;    Philip Edelbrock &lt;phil@netroedge.com&gt;, and Mark D. Studebaker&n;    &lt;mdsxyz123@yahoo.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    SUPPORTED DEVICES&t;PCI ID&n;    82801AA&t;&t;2413           &n;    82801AB&t;&t;2423           &n;    82801BA&t;&t;2443           &n;    82801CA/CAM&t;&t;2483           &n;    82801DB&t;&t;24C3   (HW PEC supported, 32 byte buffer not supported)&n;    82801EB&t;&t;24D3   (HW PEC supported, 32 byte buffer not supported)&n;    6300ESB&t;&t;25A4&n;    ICH6&t;&t;266A&n;    This driver supports several versions of Intel&squot;s I/O Controller Hubs (ICH).&n;    For SMBus support, they are similar to the PIIX4 and are part&n;    of Intel&squot;s &squot;810&squot; and other chipsets.&n;    See the doc/busses/i2c-i801 file for details.&n;    I2C Block Read and Process Call are not supported.&n;*/
multiline_comment|/* Note: we assume there can only be one I801, with one SMBus interface */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef I2C_FUNC_SMBUS_BLOCK_DATA_PEC
DECL|macro|HAVE_PEC
mdefine_line|#define HAVE_PEC
macro_line|#endif
multiline_comment|/* I801 SMBus address offsets */
DECL|macro|SMBHSTSTS
mdefine_line|#define SMBHSTSTS&t;(0 + i801_smba)
DECL|macro|SMBHSTCNT
mdefine_line|#define SMBHSTCNT&t;(2 + i801_smba)
DECL|macro|SMBHSTCMD
mdefine_line|#define SMBHSTCMD&t;(3 + i801_smba)
DECL|macro|SMBHSTADD
mdefine_line|#define SMBHSTADD&t;(4 + i801_smba)
DECL|macro|SMBHSTDAT0
mdefine_line|#define SMBHSTDAT0&t;(5 + i801_smba)
DECL|macro|SMBHSTDAT1
mdefine_line|#define SMBHSTDAT1&t;(6 + i801_smba)
DECL|macro|SMBBLKDAT
mdefine_line|#define SMBBLKDAT&t;(7 + i801_smba)
DECL|macro|SMBPEC
mdefine_line|#define SMBPEC&t;&t;(8 + i801_smba)&t;/* ICH4 only */
DECL|macro|SMBAUXSTS
mdefine_line|#define SMBAUXSTS&t;(12 + i801_smba)&t;/* ICH4 only */
DECL|macro|SMBAUXCTL
mdefine_line|#define SMBAUXCTL&t;(13 + i801_smba)&t;/* ICH4 only */
multiline_comment|/* PCI Address Constants */
DECL|macro|SMBBA
mdefine_line|#define SMBBA&t;&t;0x020
DECL|macro|SMBHSTCFG
mdefine_line|#define SMBHSTCFG&t;0x040
DECL|macro|SMBREV
mdefine_line|#define SMBREV&t;&t;0x008
multiline_comment|/* Host configuration bits for SMBHSTCFG */
DECL|macro|SMBHSTCFG_HST_EN
mdefine_line|#define SMBHSTCFG_HST_EN&t;1
DECL|macro|SMBHSTCFG_SMB_SMI_EN
mdefine_line|#define SMBHSTCFG_SMB_SMI_EN&t;2
DECL|macro|SMBHSTCFG_I2C_EN
mdefine_line|#define SMBHSTCFG_I2C_EN&t;4
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT&t;&t;100
DECL|macro|ENABLE_INT9
mdefine_line|#define ENABLE_INT9&t;&t;0&t;/* set to 0x01 to enable - untested */
multiline_comment|/* I801 command constants */
DECL|macro|I801_QUICK
mdefine_line|#define I801_QUICK&t;&t;0x00
DECL|macro|I801_BYTE
mdefine_line|#define I801_BYTE&t;&t;0x04
DECL|macro|I801_BYTE_DATA
mdefine_line|#define I801_BYTE_DATA&t;&t;0x08
DECL|macro|I801_WORD_DATA
mdefine_line|#define I801_WORD_DATA&t;&t;0x0C
DECL|macro|I801_PROC_CALL
mdefine_line|#define I801_PROC_CALL&t;&t;0x10&t;/* later chips only, unimplemented */
DECL|macro|I801_BLOCK_DATA
mdefine_line|#define I801_BLOCK_DATA&t;&t;0x14
DECL|macro|I801_I2C_BLOCK_DATA
mdefine_line|#define I801_I2C_BLOCK_DATA&t;0x18&t;/* unimplemented */
DECL|macro|I801_BLOCK_LAST
mdefine_line|#define I801_BLOCK_LAST&t;&t;0x34
DECL|macro|I801_I2C_BLOCK_LAST
mdefine_line|#define I801_I2C_BLOCK_LAST&t;0x38&t;/* unimplemented */
DECL|macro|I801_START
mdefine_line|#define I801_START&t;&t;0x40
DECL|macro|I801_PEC_EN
mdefine_line|#define I801_PEC_EN&t;&t;0x80&t;/* ICH4 only */
multiline_comment|/* insmod parameters */
multiline_comment|/* If force_addr is set to anything different from 0, we forcibly enable&n;   the I801 at the given address. VERY DANGEROUS! */
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
l_string|&quot;Forcibly enable the I801 at the given address. &quot;
l_string|&quot;EXTREMELY DANGEROUS!&quot;
)paren
suffix:semicolon
r_static
r_int
id|i801_transaction
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|i801_block_transaction
c_func
(paren
r_union
id|i2c_smbus_data
op_star
id|data
comma
r_char
id|read_write
comma
r_int
id|command
)paren
suffix:semicolon
DECL|variable|i801_smba
r_static
r_int
r_int
id|i801_smba
suffix:semicolon
DECL|variable|I801_dev
r_static
r_struct
id|pci_dev
op_star
id|I801_dev
suffix:semicolon
DECL|variable|isich4
r_static
r_int
id|isich4
suffix:semicolon
DECL|function|i801_setup
r_static
r_int
id|i801_setup
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|error_return
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|temp
suffix:semicolon
multiline_comment|/* Note: we keep on searching until we have found &squot;function 3&squot; */
r_if
c_cond
(paren
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
op_ne
l_int|3
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|I801_dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82801DB_3
)paren
op_logical_or
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_82801EB_3
)paren
op_logical_or
(paren
id|dev-&gt;device
op_eq
id|PCI_DEVICE_ID_INTEL_ESB_4
)paren
)paren
id|isich4
op_assign
l_int|1
suffix:semicolon
r_else
id|isich4
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Determine the address of the SMBus areas */
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|i801_smba
op_assign
id|force_addr
op_amp
l_int|0xfff0
suffix:semicolon
)brace
r_else
(brace
id|pci_read_config_word
c_func
(paren
id|I801_dev
comma
id|SMBBA
comma
op_amp
id|i801_smba
)paren
suffix:semicolon
id|i801_smba
op_and_assign
l_int|0xfff0
suffix:semicolon
r_if
c_cond
(paren
id|i801_smba
op_eq
l_int|0
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SMB base address uninitialized&quot;
l_string|&quot;- upgrade BIOS or use force_addr=0xaddr&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|i801_smba
comma
(paren
id|isich4
ques
c_cond
l_int|16
suffix:colon
l_int|8
)paren
comma
l_string|&quot;i801-smbus&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;I801_smb region 0x%x already in use!&bslash;n&quot;
comma
id|i801_smba
)paren
suffix:semicolon
id|error_return
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|END
suffix:semicolon
)brace
id|pci_read_config_byte
c_func
(paren
id|I801_dev
comma
id|SMBHSTCFG
comma
op_amp
id|temp
)paren
suffix:semicolon
id|temp
op_and_assign
op_complement
id|SMBHSTCFG_I2C_EN
suffix:semicolon
multiline_comment|/* SMBus timing */
id|pci_write_config_byte
c_func
(paren
id|I801_dev
comma
id|SMBHSTCFG
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* If force_addr is set, we program the new address here. Just to make&n;&t;   sure, we disable the device first. */
r_if
c_cond
(paren
id|force_addr
)paren
(brace
id|pci_write_config_byte
c_func
(paren
id|I801_dev
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
id|I801_dev
comma
id|SMBBA
comma
id|i801_smba
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|I801_dev
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
id|dev-&gt;dev
comma
l_string|&quot;WARNING: I801 SMBus interface set to &quot;
l_string|&quot;new address %04x!&bslash;n&quot;
comma
id|i801_smba
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
id|pci_write_config_byte
c_func
(paren
id|I801_dev
comma
id|SMBHSTCFG
comma
id|temp
op_or
l_int|1
)paren
suffix:semicolon
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;enabling SMBus device&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x02
)paren
id|dev_dbg
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;I801 using Interrupt SMI# for SMBus.&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|dev_dbg
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;I801 using PCI Interrupt for SMBus.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|I801_dev
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
id|dev-&gt;dev
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
id|dev-&gt;dev
comma
l_string|&quot;I801_smba = 0x%X&bslash;n&quot;
comma
id|i801_smba
)paren
suffix:semicolon
id|END
suffix:colon
r_return
id|error_return
suffix:semicolon
)brace
DECL|function|i801_transaction
r_static
r_int
id|i801_transaction
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
id|I801_dev-&gt;dev
comma
l_string|&quot;Transaction (pre): CNT=%02x, CMD=%02x,&quot;
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
multiline_comment|/* 0x1f = Failed, Bus_Err, Dev_Err, Intr, Host_Busy */
r_if
c_cond
(paren
(paren
id|temp
op_assign
(paren
l_int|0x1f
op_amp
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
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
id|I801_dev-&gt;dev
comma
l_string|&quot;SMBus busy (%02x). Resetting... &bslash;n&quot;
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
(paren
l_int|0x1f
op_amp
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
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
id|I801_dev-&gt;dev
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
id|I801_dev-&gt;dev
comma
l_string|&quot;Successfull!&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
id|outb_p
c_func
(paren
id|inb
c_func
(paren
id|SMBHSTCNT
)paren
op_or
id|I801_START
comma
id|SMBHSTCNT
)paren
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
id|dev_dbg
c_func
(paren
op_amp
id|I801_dev-&gt;dev
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
id|I801_dev-&gt;dev
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
id|dev_err
c_func
(paren
op_amp
id|I801_dev-&gt;dev
comma
l_string|&quot;Bus collision! SMBus may be locked &quot;
l_string|&quot;until next hard reset. (sorry!)&bslash;n&quot;
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
id|I801_dev-&gt;dev
comma
l_string|&quot;Error: no response!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
op_amp
l_int|0x1f
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
(paren
l_int|0x1f
op_amp
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
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
id|I801_dev-&gt;dev
comma
l_string|&quot;Failed reset at end of transaction&quot;
l_string|&quot;(%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
id|dev_dbg
c_func
(paren
op_amp
id|I801_dev-&gt;dev
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
multiline_comment|/* All-inclusive block transaction function */
DECL|function|i801_block_transaction
r_static
r_int
id|i801_block_transaction
c_func
(paren
r_union
id|i2c_smbus_data
op_star
id|data
comma
r_char
id|read_write
comma
r_int
id|command
)paren
(brace
r_int
id|i
comma
id|len
suffix:semicolon
r_int
id|smbcmd
suffix:semicolon
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
suffix:semicolon
r_int
r_char
id|hostc
comma
id|errmask
suffix:semicolon
r_if
c_cond
(paren
id|command
op_eq
id|I2C_SMBUS_I2C_BLOCK_DATA
)paren
(brace
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
)paren
(brace
multiline_comment|/* set I2C_EN bit in configuration register */
id|pci_read_config_byte
c_func
(paren
id|I801_dev
comma
id|SMBHSTCFG
comma
op_amp
id|hostc
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|I801_dev
comma
id|SMBHSTCFG
comma
id|hostc
op_or
id|SMBHSTCFG_I2C_EN
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev_err
c_func
(paren
op_amp
id|I801_dev-&gt;dev
comma
l_string|&quot;I2C_SMBUS_I2C_BLOCK_READ not DB!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
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
l_int|1
)paren
id|len
op_assign
l_int|1
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
id|outb_p
c_func
(paren
id|len
comma
id|SMBHSTDAT0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|data-&gt;block
(braket
l_int|1
)braket
comma
id|SMBBLKDAT
)paren
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* max for reads */
)brace
r_if
c_cond
(paren
id|isich4
op_logical_and
id|command
op_ne
id|I2C_SMBUS_I2C_BLOCK_DATA
)paren
(brace
multiline_comment|/* set 32 byte buffer */
)brace
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
r_if
c_cond
(paren
id|i
op_eq
id|len
op_logical_and
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
id|smbcmd
op_assign
id|I801_BLOCK_LAST
suffix:semicolon
r_else
id|smbcmd
op_assign
id|I801_BLOCK_DATA
suffix:semicolon
id|outb_p
c_func
(paren
id|smbcmd
op_or
id|ENABLE_INT9
comma
id|SMBHSTCNT
)paren
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|I801_dev-&gt;dev
comma
l_string|&quot;Block (pre %d): CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, BLKDAT=%02x&bslash;n&quot;
comma
id|i
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
id|SMBBLKDAT
)paren
)paren
suffix:semicolon
multiline_comment|/* Make sure the SMBus host is ready to start transmitting */
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
(brace
multiline_comment|/* Erronenous conditions before transaction: &n;&t;&t;&t; * Byte_Done, Failed, Bus_Err, Dev_Err, Intr, Host_Busy */
id|errmask
op_assign
l_int|0x9f
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Erronenous conditions during transaction: &n;&t;&t;&t; * Failed, Bus_Err, Dev_Err, Intr */
id|errmask
op_assign
l_int|0x1e
suffix:semicolon
)brace
r_if
c_cond
(paren
id|temp
op_amp
id|errmask
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|I801_dev-&gt;dev
comma
l_string|&quot;SMBus busy (%02x). &quot;
l_string|&quot;Resetting... &bslash;n&quot;
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
(paren
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
)paren
op_amp
id|errmask
)paren
op_ne
l_int|0x00
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|I801_dev-&gt;dev
comma
l_string|&quot;Reset failed! (%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|END
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ne
l_int|1
)paren
(brace
multiline_comment|/* if die in middle of block transaction, fail */
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
r_goto
id|END
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
id|outb_p
c_func
(paren
id|inb
c_func
(paren
id|SMBHSTCNT
)paren
op_or
id|I801_START
comma
id|SMBHSTCNT
)paren
suffix:semicolon
multiline_comment|/* We will always wait for a fraction of a second! */
id|timeout
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
op_logical_neg
(paren
id|temp
op_amp
l_int|0x80
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
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|I801_dev-&gt;dev
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
id|I801_dev-&gt;dev
comma
l_string|&quot;Error: Failed bus transaction&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
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
id|dev_err
c_func
(paren
op_amp
id|I801_dev-&gt;dev
comma
l_string|&quot;Bus collision!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
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
id|I801_dev-&gt;dev
comma
l_string|&quot;Error: no response!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|1
op_logical_and
id|read_write
op_eq
id|I2C_SMBUS_READ
)paren
(brace
id|len
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
id|len
OL
l_int|1
)paren
id|len
op_assign
l_int|1
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
id|data-&gt;block
(braket
l_int|0
)braket
op_assign
id|len
suffix:semicolon
)brace
multiline_comment|/* Retrieve/store value in SMBBLKDAT */
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_READ
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
r_if
c_cond
(paren
id|read_write
op_eq
id|I2C_SMBUS_WRITE
op_logical_and
id|i
op_plus
l_int|1
op_le
id|len
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
id|SMBBLKDAT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_amp
l_int|0x9e
)paren
op_ne
l_int|0x00
)paren
id|outb_p
c_func
(paren
id|temp
comma
id|SMBHSTSTS
)paren
suffix:semicolon
multiline_comment|/* signals SMBBLKDAT ready */
r_if
c_cond
(paren
(paren
id|temp
op_assign
(paren
l_int|0x1e
op_amp
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
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
id|I801_dev-&gt;dev
comma
l_string|&quot;Bad status (%02x) at end of transaction&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
id|dev_dbg
c_func
(paren
op_amp
id|I801_dev-&gt;dev
comma
l_string|&quot;Block (post %d): CNT=%02x, CMD=%02x, &quot;
l_string|&quot;ADD=%02x, DAT0=%02x, BLKDAT=%02x&bslash;n&quot;
comma
id|i
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
id|SMBBLKDAT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_goto
id|END
suffix:semicolon
)brace
macro_line|#ifdef HAVE_PEC
r_if
c_cond
(paren
id|isich4
op_logical_and
id|command
op_eq
id|I2C_SMBUS_BLOCK_DATA_PEC
)paren
(brace
multiline_comment|/* wait for INTR bit as advised by Intel */
id|timeout
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|temp
op_assign
id|inb_p
c_func
(paren
id|SMBHSTSTS
)paren
suffix:semicolon
id|msleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
op_logical_neg
(paren
id|temp
op_amp
l_int|0x02
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
id|I801_dev-&gt;dev
comma
l_string|&quot;PEC Timeout!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|temp
comma
id|SMBHSTSTS
)paren
suffix:semicolon
)brace
macro_line|#endif
id|result
op_assign
l_int|0
suffix:semicolon
id|END
suffix:colon
r_if
c_cond
(paren
id|command
op_eq
id|I2C_SMBUS_I2C_BLOCK_DATA
)paren
(brace
multiline_comment|/* restore saved configuration register value */
id|pci_write_config_byte
c_func
(paren
id|I801_dev
comma
id|SMBHSTCFG
comma
id|hostc
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Return -1 on error. */
DECL|function|i801_access
r_static
id|s32
id|i801_access
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
id|hwpec
op_assign
l_int|0
suffix:semicolon
r_int
id|block
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
comma
id|xact
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef HAVE_PEC
r_if
c_cond
(paren
id|isich4
)paren
(brace
id|hwpec
op_assign
(paren
id|flags
op_amp
id|I2C_CLIENT_PEC
)paren
op_ne
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_switch
c_cond
(paren
id|size
)paren
(brace
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
id|xact
op_assign
id|I801_QUICK
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
id|xact
op_assign
id|I801_BYTE
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
id|xact
op_assign
id|I801_BYTE_DATA
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
id|xact
op_assign
id|I801_WORD_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
r_case
id|I2C_SMBUS_I2C_BLOCK_DATA
suffix:colon
macro_line|#ifdef HAVE_PEC
r_case
id|I2C_SMBUS_BLOCK_DATA_PEC
suffix:colon
r_if
c_cond
(paren
id|hwpec
op_logical_and
id|size
op_eq
id|I2C_SMBUS_BLOCK_DATA
)paren
(brace
id|size
op_assign
id|I2C_SMBUS_BLOCK_DATA_PEC
suffix:semicolon
)brace
macro_line|#endif
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
id|block
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
r_default
suffix:colon
id|dev_err
c_func
(paren
op_amp
id|I801_dev-&gt;dev
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
macro_line|#ifdef HAVE_PEC
r_if
c_cond
(paren
id|isich4
op_logical_and
id|hwpec
)paren
(brace
r_if
c_cond
(paren
id|size
op_ne
id|I2C_SMBUS_QUICK
op_logical_and
id|size
op_ne
id|I2C_SMBUS_I2C_BLOCK_DATA
)paren
(brace
id|outb_p
c_func
(paren
l_int|1
comma
id|SMBAUXCTL
)paren
suffix:semicolon
)brace
multiline_comment|/* enable HW PEC */
)brace
macro_line|#endif
r_if
c_cond
(paren
id|block
)paren
(brace
id|ret
op_assign
id|i801_block_transaction
c_func
(paren
id|data
comma
id|read_write
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb_p
c_func
(paren
id|xact
op_or
id|ENABLE_INT9
comma
id|SMBHSTCNT
)paren
suffix:semicolon
id|ret
op_assign
id|i801_transaction
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef HAVE_PEC
r_if
c_cond
(paren
id|isich4
op_logical_and
id|hwpec
)paren
(brace
r_if
c_cond
(paren
id|size
op_ne
id|I2C_SMBUS_QUICK
op_logical_and
id|size
op_ne
id|I2C_SMBUS_I2C_BLOCK_DATA
)paren
(brace
id|outb_p
c_func
(paren
l_int|0
comma
id|SMBAUXCTL
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|block
)paren
(brace
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
id|xact
op_eq
id|I801_QUICK
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|xact
op_amp
l_int|0x7f
)paren
(brace
r_case
id|I801_BYTE
suffix:colon
multiline_comment|/* Result put in SMBHSTDAT0 */
r_case
id|I801_BYTE_DATA
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
id|I801_WORD_DATA
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|i801_func
r_static
id|u32
id|i801_func
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
id|I2C_FUNC_SMBUS_WRITE_I2C_BLOCK
macro_line|#ifdef HAVE_PEC
op_or
(paren
id|isich4
ques
c_cond
id|I2C_FUNC_SMBUS_BLOCK_DATA_PEC
op_or
id|I2C_FUNC_SMBUS_HWPEC_CALC
suffix:colon
l_int|0
)paren
macro_line|#endif
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
id|i801_access
comma
dot
id|functionality
op_assign
id|i801_func
comma
)brace
suffix:semicolon
DECL|variable|i801_adapter
r_static
r_struct
id|i2c_adapter
id|i801_adapter
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
DECL|variable|i801_ids
r_static
r_struct
id|pci_device_id
id|i801_ids
(braket
)braket
op_assign
(brace
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82801AA_3
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82801AB_3
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82801BA_2
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82801CA_3
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82801DB_3
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_82801EB_3
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_ESB_4
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_INTEL
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_INTEL_ICH6_16
comma
dot
id|subvendor
op_assign
id|PCI_ANY_ID
comma
dot
id|subdevice
op_assign
id|PCI_ANY_ID
comma
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
id|i801_ids
)paren
suffix:semicolon
DECL|function|i801_probe
r_static
r_int
id|__devinit
id|i801_probe
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
id|i801_setup
c_func
(paren
id|dev
)paren
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;I801 not detected, module not inserted.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* set up the driverfs linkage to our parent device */
id|i801_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|i801_adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SMBus I801 adapter at %04x&quot;
comma
id|i801_smba
)paren
suffix:semicolon
r_return
id|i2c_add_adapter
c_func
(paren
op_amp
id|i801_adapter
)paren
suffix:semicolon
)brace
DECL|function|i801_remove
r_static
r_void
id|__devexit
id|i801_remove
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
id|i801_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|i801_smba
comma
(paren
id|isich4
ques
c_cond
l_int|16
suffix:colon
l_int|8
)paren
)paren
suffix:semicolon
)brace
DECL|variable|i801_driver
r_static
r_struct
id|pci_driver
id|i801_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i801_smbus&quot;
comma
dot
id|id_table
op_assign
id|i801_ids
comma
dot
id|probe
op_assign
id|i801_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|i801_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_i801_init
r_static
r_int
id|__init
id|i2c_i801_init
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
id|i801_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_i801_exit
r_static
r_void
id|__exit
id|i2c_i801_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|i801_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt;, &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt;, &quot;
l_string|&quot;and Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I801 SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_i801_init
id|module_init
c_func
(paren
id|i2c_i801_init
)paren
suffix:semicolon
DECL|variable|i2c_i801_exit
id|module_exit
c_func
(paren
id|i2c_i801_exit
)paren
suffix:semicolon
eof
