multiline_comment|/*&n;    sis96x.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;&n;    Copyright (c) 2003 Mark M. Hoffman &lt;mhoffman@lightlink.com&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;    This module must be considered BETA unless and until&n;    the chipset manufacturer releases a datasheet.&n;    The register definitions are based on the SiS630.&n;&n;    This module relies on quirk_sis_96x_smbus (drivers/pci/quirks.c)&n;    for just about every machine for which users have reported.&n;    If this module isn&squot;t detecting your 96x south bridge, have a &n;    look there.&n;&n;    We assume there can only be one SiS96x with one SMBus interface.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n;&t;HISTORY:&n;&t;2003-05-11&t;1.0.0 &t;Updated from lm_sensors project for kernel 2.5&n;&t;&t;&t;&t;(was i2c-sis645.c from lm_sensors 2.7.0)&n;*/
DECL|macro|SIS96x_VERSION
mdefine_line|#define SIS96x_VERSION &quot;1.0.0&quot;
multiline_comment|/* base address register in PCI config space */
DECL|macro|SIS96x_BAR
mdefine_line|#define SIS96x_BAR 0x04
multiline_comment|/* SiS96x SMBus registers */
DECL|macro|SMB_STS
mdefine_line|#define SMB_STS      0x00
DECL|macro|SMB_EN
mdefine_line|#define SMB_EN       0x01
DECL|macro|SMB_CNT
mdefine_line|#define SMB_CNT      0x02
DECL|macro|SMB_HOST_CNT
mdefine_line|#define SMB_HOST_CNT 0x03
DECL|macro|SMB_ADDR
mdefine_line|#define SMB_ADDR     0x04
DECL|macro|SMB_CMD
mdefine_line|#define SMB_CMD      0x05
DECL|macro|SMB_PCOUNT
mdefine_line|#define SMB_PCOUNT   0x06
DECL|macro|SMB_COUNT
mdefine_line|#define SMB_COUNT    0x07
DECL|macro|SMB_BYTE
mdefine_line|#define SMB_BYTE     0x08
DECL|macro|SMB_DEV_ADDR
mdefine_line|#define SMB_DEV_ADDR 0x10
DECL|macro|SMB_DB0
mdefine_line|#define SMB_DB0      0x11
DECL|macro|SMB_DB1
mdefine_line|#define SMB_DB1      0x12
DECL|macro|SMB_SAA
mdefine_line|#define SMB_SAA      0x13
multiline_comment|/* register count for request_region */
DECL|macro|SMB_IOSIZE
mdefine_line|#define SMB_IOSIZE 0x20
multiline_comment|/* Other settings */
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT 500
multiline_comment|/* SiS96x SMBus constants */
DECL|macro|SIS96x_QUICK
mdefine_line|#define SIS96x_QUICK      0x00
DECL|macro|SIS96x_BYTE
mdefine_line|#define SIS96x_BYTE       0x01
DECL|macro|SIS96x_BYTE_DATA
mdefine_line|#define SIS96x_BYTE_DATA  0x02
DECL|macro|SIS96x_WORD_DATA
mdefine_line|#define SIS96x_WORD_DATA  0x03
DECL|macro|SIS96x_PROC_CALL
mdefine_line|#define SIS96x_PROC_CALL  0x04
DECL|macro|SIS96x_BLOCK_DATA
mdefine_line|#define SIS96x_BLOCK_DATA 0x05
DECL|variable|sis96x_adapter
r_static
r_struct
id|i2c_adapter
id|sis96x_adapter
suffix:semicolon
DECL|variable|sis96x_smbus_base
r_static
id|u16
id|sis96x_smbus_base
op_assign
l_int|0
suffix:semicolon
DECL|function|sis96x_read
r_static
r_inline
id|u8
id|sis96x_read
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
id|sis96x_smbus_base
op_plus
id|reg
)paren
suffix:semicolon
)brace
DECL|function|sis96x_write
r_static
r_inline
r_void
id|sis96x_write
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
id|sis96x_smbus_base
op_plus
id|reg
)paren
suffix:semicolon
)brace
multiline_comment|/* Execute a SMBus transaction.&n;   int size is from SIS96x_QUICK to SIS96x_BLOCK_DATA&n; */
DECL|function|sis96x_transaction
r_static
r_int
id|sis96x_transaction
c_func
(paren
r_int
id|size
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
id|sis96x_adapter.dev
comma
l_string|&quot;SMBus transaction %d&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
multiline_comment|/* Make sure the SMBus host is ready to start transmitting */
r_if
c_cond
(paren
(paren
(paren
id|temp
op_assign
id|sis96x_read
c_func
(paren
id|SMB_CNT
)paren
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
id|sis96x_adapter.dev
comma
l_string|&quot;SMBus busy (0x%02x). &quot;
l_string|&quot;Resetting...&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
multiline_comment|/* kill the transaction */
id|sis96x_write
c_func
(paren
id|SMB_HOST_CNT
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* check it again */
r_if
c_cond
(paren
(paren
(paren
id|temp
op_assign
id|sis96x_read
c_func
(paren
id|SMB_CNT
)paren
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
id|sis96x_adapter.dev
comma
l_string|&quot;Failed (0x%02x)&bslash;n&quot;
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
id|sis96x_adapter.dev
comma
l_string|&quot;Successful&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Turn off timeout interrupts, set fast host clock */
id|sis96x_write
c_func
(paren
id|SMB_CNT
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* clear all (sticky) status flags */
id|temp
op_assign
id|sis96x_read
c_func
(paren
id|SMB_STS
)paren
suffix:semicolon
id|sis96x_write
c_func
(paren
id|SMB_STS
comma
id|temp
op_amp
l_int|0x1e
)paren
suffix:semicolon
multiline_comment|/* start the transaction by setting bit 4 and size bits */
id|sis96x_write
c_func
(paren
id|SMB_HOST_CNT
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
id|sis96x_read
c_func
(paren
id|SMB_STS
)paren
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
id|sis96x_adapter.dev
comma
l_string|&quot;SMBus Timeout! (0x%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* device error - probably missing ACK */
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
id|sis96x_adapter.dev
comma
l_string|&quot;Failed bus transaction!&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* bus collision */
r_if
c_cond
(paren
id|temp
op_amp
l_int|0x04
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|sis96x_adapter.dev
comma
l_string|&quot;Bus collision!&bslash;n&quot;
)paren
suffix:semicolon
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Finish up by resetting the bus */
id|sis96x_write
c_func
(paren
id|SMB_STS
comma
id|temp
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|sis96x_read
c_func
(paren
id|SMB_STS
)paren
)paren
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|sis96x_adapter.dev
comma
l_string|&quot;Failed reset at &quot;
l_string|&quot;end of transaction! (0x%02x)&bslash;n&quot;
comma
id|temp
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Return -1 on error. */
DECL|function|sis96x_access
r_static
id|s32
id|sis96x_access
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
id|sis96x_write
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
id|SIS96x_QUICK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE
suffix:colon
id|sis96x_write
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
id|sis96x_write
c_func
(paren
id|SMB_CMD
comma
id|command
)paren
suffix:semicolon
id|size
op_assign
id|SIS96x_BYTE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BYTE_DATA
suffix:colon
id|sis96x_write
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
id|sis96x_write
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
id|sis96x_write
c_func
(paren
id|SMB_BYTE
comma
id|data-&gt;byte
)paren
suffix:semicolon
id|size
op_assign
id|SIS96x_BYTE_DATA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_PROC_CALL
suffix:colon
r_case
id|I2C_SMBUS_WORD_DATA
suffix:colon
id|sis96x_write
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
id|sis96x_write
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
id|sis96x_write
c_func
(paren
id|SMB_BYTE
comma
id|data-&gt;word
op_amp
l_int|0xff
)paren
suffix:semicolon
id|sis96x_write
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
id|SIS96x_PROC_CALL
suffix:colon
id|SIS96x_WORD_DATA
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|I2C_SMBUS_BLOCK_DATA
suffix:colon
multiline_comment|/* TO DO: */
id|dev_info
c_func
(paren
op_amp
id|adap-&gt;dev
comma
l_string|&quot;SMBus block not implemented!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|dev_info
c_func
(paren
op_amp
id|adap-&gt;dev
comma
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
id|sis96x_transaction
c_func
(paren
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
id|SIS96x_PROC_CALL
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
id|SIS96x_QUICK
)paren
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
id|SIS96x_BYTE
suffix:colon
r_case
id|SIS96x_BYTE_DATA
suffix:colon
id|data-&gt;byte
op_assign
id|sis96x_read
c_func
(paren
id|SMB_BYTE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIS96x_WORD_DATA
suffix:colon
r_case
id|SIS96x_PROC_CALL
suffix:colon
id|data-&gt;word
op_assign
id|sis96x_read
c_func
(paren
id|SMB_BYTE
)paren
op_plus
(paren
id|sis96x_read
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sis96x_func
r_static
id|u32
id|sis96x_func
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
id|sis96x_access
comma
dot
id|functionality
op_assign
id|sis96x_func
comma
)brace
suffix:semicolon
DECL|variable|sis96x_adapter
r_static
r_struct
id|i2c_adapter
id|sis96x_adapter
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
DECL|variable|sis96x_ids
r_static
r_struct
id|pci_device_id
id|sis96x_ids
(braket
)braket
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_SI
comma
id|PCI_DEVICE_ID_SI_SMBUS
)paren
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
id|sis96x_ids
)paren
suffix:semicolon
DECL|function|sis96x_probe
r_static
r_int
id|__devinit
id|sis96x_probe
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
id|u16
id|ww
op_assign
l_int|0
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|sis96x_smbus_base
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Only one device supported.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_CLASS_DEVICE
comma
op_amp
id|ww
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PCI_CLASS_SERIAL_SMBUS
op_ne
id|ww
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Unsupported device class 0x%04x!&bslash;n&quot;
comma
id|ww
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|sis96x_smbus_base
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
id|SIS96x_BAR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sis96x_smbus_base
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SiS96x SMBus base address &quot;
l_string|&quot;not initialized!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|dev_info
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SiS96x SMBus base address: 0x%04x&bslash;n&quot;
comma
id|sis96x_smbus_base
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
id|sis96x_smbus_base
comma
id|SMB_IOSIZE
comma
l_string|&quot;sis96x-smbus&quot;
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;SMBus registers 0x%04x-0x%04x &quot;
l_string|&quot;already in use!&bslash;n&quot;
comma
id|sis96x_smbus_base
comma
id|sis96x_smbus_base
op_plus
id|SMB_IOSIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|sis96x_smbus_base
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* set up the driverfs linkage to our parent device */
id|sis96x_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|snprintf
c_func
(paren
id|sis96x_adapter.name
comma
id|I2C_NAME_SIZE
comma
l_string|&quot;SiS96x SMBus adapter at 0x%04x&quot;
comma
id|sis96x_smbus_base
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|i2c_add_adapter
c_func
(paren
op_amp
id|sis96x_adapter
)paren
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Couldn&squot;t register adapter!&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|sis96x_smbus_base
comma
id|SMB_IOSIZE
)paren
suffix:semicolon
id|sis96x_smbus_base
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|sis96x_remove
r_static
r_void
id|__devexit
id|sis96x_remove
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
id|sis96x_smbus_base
)paren
(brace
id|i2c_del_adapter
c_func
(paren
op_amp
id|sis96x_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|sis96x_smbus_base
comma
id|SMB_IOSIZE
)paren
suffix:semicolon
id|sis96x_smbus_base
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|sis96x_driver
r_static
r_struct
id|pci_driver
id|sis96x_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;sis96x_smbus&quot;
comma
dot
id|id_table
op_assign
id|sis96x_ids
comma
dot
id|probe
op_assign
id|sis96x_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|sis96x_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_sis96x_init
r_static
r_int
id|__init
id|i2c_sis96x_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;i2c-sis96x version %s&bslash;n&quot;
comma
id|SIS96x_VERSION
)paren
suffix:semicolon
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|sis96x_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_sis96x_exit
r_static
r_void
id|__exit
id|i2c_sis96x_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|sis96x_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Mark M. Hoffman &lt;mhoffman@lightlink.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;SiS96x SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Register initialization functions using helper macros */
DECL|variable|i2c_sis96x_init
id|module_init
c_func
(paren
id|i2c_sis96x_init
)paren
suffix:semicolon
DECL|variable|i2c_sis96x_exit
id|module_exit
c_func
(paren
id|i2c_sis96x_exit
)paren
suffix:semicolon
eof
