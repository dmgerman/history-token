multiline_comment|/*&n;    i2c-via.c - Part of lm_sensors,  Linux kernel modules&n;                for hardware monitoring&n;&n;    i2c Support for Via Technologies 82C586B South Bridge&n;&n;    Copyright (c) 1998, 1999 Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* #define DEBUG */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Power management registers */
DECL|macro|PM_CFG_REVID
mdefine_line|#define PM_CFG_REVID&t;0x08&t;/* silicon revision code */
DECL|macro|PM_CFG_IOBASE0
mdefine_line|#define PM_CFG_IOBASE0&t;0x20
DECL|macro|PM_CFG_IOBASE1
mdefine_line|#define PM_CFG_IOBASE1&t;0x48
DECL|macro|I2C_DIR
mdefine_line|#define I2C_DIR&t;&t;(pm_io_base+0x40)
DECL|macro|I2C_OUT
mdefine_line|#define I2C_OUT&t;&t;(pm_io_base+0x42)
DECL|macro|I2C_IN
mdefine_line|#define I2C_IN&t;&t;(pm_io_base+0x44)
DECL|macro|I2C_SCL
mdefine_line|#define I2C_SCL&t;&t;0x02&t;/* clock bit in DIR/OUT/IN register */
DECL|macro|I2C_SDA
mdefine_line|#define I2C_SDA&t;&t;0x04
multiline_comment|/* io-region reservation */
DECL|macro|IOSPACE
mdefine_line|#define IOSPACE&t;&t;0x06
DECL|macro|IOTEXT
mdefine_line|#define IOTEXT&t;&t;&quot;via-i2c&quot;
DECL|variable|pm_io_base
r_static
id|u16
id|pm_io_base
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;   It does not appear from the datasheet that the GPIO pins are&n;   open drain. So a we set a low value by setting the direction to&n;   output and a high value by setting the direction to input and&n;   relying on the required I2C pullup. The data value is initialized&n;   to 0 in via_init() and never changed.&n;*/
DECL|function|bit_via_setscl
r_static
r_void
id|bit_via_setscl
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
id|outb
c_func
(paren
id|state
ques
c_cond
id|inb
c_func
(paren
id|I2C_DIR
)paren
op_amp
op_complement
id|I2C_SCL
suffix:colon
id|inb
c_func
(paren
id|I2C_DIR
)paren
op_or
id|I2C_SCL
comma
id|I2C_DIR
)paren
suffix:semicolon
)brace
DECL|function|bit_via_setsda
r_static
r_void
id|bit_via_setsda
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
id|outb
c_func
(paren
id|state
ques
c_cond
id|inb
c_func
(paren
id|I2C_DIR
)paren
op_amp
op_complement
id|I2C_SDA
suffix:colon
id|inb
c_func
(paren
id|I2C_DIR
)paren
op_or
id|I2C_SDA
comma
id|I2C_DIR
)paren
suffix:semicolon
)brace
DECL|function|bit_via_getscl
r_static
r_int
id|bit_via_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
l_int|0
op_ne
(paren
id|inb
c_func
(paren
id|I2C_IN
)paren
op_amp
id|I2C_SCL
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_via_getsda
r_static
r_int
id|bit_via_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
l_int|0
op_ne
(paren
id|inb
c_func
(paren
id|I2C_IN
)paren
op_amp
id|I2C_SDA
)paren
)paren
suffix:semicolon
)brace
DECL|variable|bit_data
r_static
r_struct
id|i2c_algo_bit_data
id|bit_data
op_assign
(brace
dot
id|setsda
op_assign
id|bit_via_setsda
comma
dot
id|setscl
op_assign
id|bit_via_setscl
comma
dot
id|getsda
op_assign
id|bit_via_getsda
comma
dot
id|getscl
op_assign
id|bit_via_getscl
comma
dot
id|udelay
op_assign
l_int|5
comma
dot
id|mdelay
op_assign
l_int|5
comma
dot
id|timeout
op_assign
id|HZ
)brace
suffix:semicolon
DECL|variable|vt586b_adapter
r_static
r_struct
id|i2c_adapter
id|vt586b_adapter
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;VIA i2c&quot;
comma
dot
id|algo_data
op_assign
op_amp
id|bit_data
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|vt586b_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_82C586_3
)paren
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|function|vt586b_probe
r_static
r_int
id|__devinit
id|vt586b_probe
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
id|base
suffix:semicolon
id|u8
id|rev
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|pm_io_base
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;i2c-via: Will only support one host&bslash;n&quot;
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
id|dev
comma
id|PM_CFG_REVID
comma
op_amp
id|rev
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|rev
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|base
op_assign
id|PM_CFG_IOBASE0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x01
suffix:colon
r_case
l_int|0x10
suffix:colon
id|base
op_assign
id|PM_CFG_IOBASE1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|base
op_assign
id|PM_CFG_IOBASE1
suffix:semicolon
multiline_comment|/* later revision */
)brace
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|base
comma
op_amp
id|pm_io_base
)paren
suffix:semicolon
id|pm_io_base
op_and_assign
(paren
l_int|0xff
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|I2C_DIR
comma
id|IOSPACE
comma
id|IOTEXT
)paren
)paren
(brace
id|dev_err
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;IO 0x%x-0x%x already in use&bslash;n&quot;
comma
id|I2C_DIR
comma
id|I2C_DIR
op_plus
id|IOSPACE
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|outb
c_func
(paren
id|inb
c_func
(paren
id|I2C_DIR
)paren
op_amp
op_complement
(paren
id|I2C_SDA
op_or
id|I2C_SCL
)paren
comma
id|I2C_DIR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|I2C_OUT
)paren
op_amp
op_complement
(paren
id|I2C_SDA
op_or
id|I2C_SCL
)paren
comma
id|I2C_OUT
)paren
suffix:semicolon
multiline_comment|/* set up the driverfs linkage to our parent device */
id|vt586b_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|res
op_assign
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|vt586b_adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
(brace
id|release_region
c_func
(paren
id|I2C_DIR
comma
id|IOSPACE
)paren
suffix:semicolon
id|pm_io_base
op_assign
l_int|0
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vt586b_remove
r_static
r_void
id|__devexit
id|vt586b_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|vt586b_adapter
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|I2C_DIR
comma
id|IOSPACE
)paren
suffix:semicolon
id|pm_io_base
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|vt586b_driver
r_static
r_struct
id|pci_driver
id|vt586b_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vt586b smbus&quot;
comma
dot
id|id_table
op_assign
id|vt586b_ids
comma
dot
id|probe
op_assign
id|vt586b_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|vt586b_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_vt586b_init
r_static
r_int
id|__init
id|i2c_vt586b_init
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
id|vt586b_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_vt586b_exit
r_static
r_void
id|__exit
id|i2c_vt586b_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|vt586b_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;i2c for Via vt82c586b southbridge&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_vt586b_init
id|module_init
c_func
(paren
id|i2c_vt586b_init
)paren
suffix:semicolon
DECL|variable|i2c_vt586b_exit
id|module_exit
c_func
(paren
id|i2c_vt586b_exit
)paren
suffix:semicolon
eof
