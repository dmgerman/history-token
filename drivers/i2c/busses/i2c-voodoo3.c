multiline_comment|/*&n;    voodoo3.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;    Copyright (c) 1998, 1999  Frodo Looijaard &lt;frodol@dds.nl&gt;,&n;    Philip Edelbrock &lt;phil@netroedge.com&gt;,&n;    Ralph Metzler &lt;rjkm@thp.uni-koeln.de&gt;, and&n;    Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;    &n;    Based on code written by Ralph Metzler &lt;rjkm@thp.uni-koeln.de&gt; and&n;    Simon Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* This interfaces to the I2C bus of the Voodoo3 to gain access to&n;    the BT869 and possibly other I2C devices. */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* the only registers we use */
DECL|macro|REG
mdefine_line|#define REG&t;&t;0x78
DECL|macro|REG2
mdefine_line|#define REG2 &t;&t;0x70
multiline_comment|/* bit locations in the register */
DECL|macro|DDC_ENAB
mdefine_line|#define DDC_ENAB&t;0x00040000
DECL|macro|DDC_SCL_OUT
mdefine_line|#define DDC_SCL_OUT&t;0x00080000
DECL|macro|DDC_SDA_OUT
mdefine_line|#define DDC_SDA_OUT&t;0x00100000
DECL|macro|DDC_SCL_IN
mdefine_line|#define DDC_SCL_IN&t;0x00200000
DECL|macro|DDC_SDA_IN
mdefine_line|#define DDC_SDA_IN&t;0x00400000
DECL|macro|I2C_ENAB
mdefine_line|#define I2C_ENAB&t;0x00800000
DECL|macro|I2C_SCL_OUT
mdefine_line|#define I2C_SCL_OUT&t;0x01000000
DECL|macro|I2C_SDA_OUT
mdefine_line|#define I2C_SDA_OUT&t;0x02000000
DECL|macro|I2C_SCL_IN
mdefine_line|#define I2C_SCL_IN&t;0x04000000
DECL|macro|I2C_SDA_IN
mdefine_line|#define I2C_SDA_IN&t;0x08000000
multiline_comment|/* initialization states */
DECL|macro|INIT2
mdefine_line|#define INIT2&t;&t;0x2
DECL|macro|INIT3
mdefine_line|#define INIT3&t;&t;0x4
multiline_comment|/* delays */
DECL|macro|CYCLE_DELAY
mdefine_line|#define CYCLE_DELAY&t;10
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;&t;(HZ / 2)
DECL|variable|ioaddr
r_static
r_void
id|__iomem
op_star
id|ioaddr
suffix:semicolon
multiline_comment|/* The voo GPIO registers don&squot;t have individual masks for each bit&n;   so we always have to read before writing. */
DECL|function|bit_vooi2c_setscl
r_static
r_void
id|bit_vooi2c_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|r
suffix:semicolon
id|r
op_assign
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|r
op_or_assign
id|I2C_SCL_OUT
suffix:semicolon
r_else
id|r
op_and_assign
op_complement
id|I2C_SCL_OUT
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|bit_vooi2c_setsda
r_static
r_void
id|bit_vooi2c_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|r
suffix:semicolon
id|r
op_assign
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|r
op_or_assign
id|I2C_SDA_OUT
suffix:semicolon
r_else
id|r
op_and_assign
op_complement
id|I2C_SDA_OUT
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
multiline_comment|/* The GPIO pins are open drain, so the pins always remain outputs.&n;   We rely on the i2c-algo-bit routines to set the pins high before&n;   reading the input from other chips. */
DECL|function|bit_vooi2c_getscl
r_static
r_int
id|bit_vooi2c_getscl
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
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
op_amp
id|I2C_SCL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_vooi2c_getsda
r_static
r_int
id|bit_vooi2c_getsda
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
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
op_amp
id|I2C_SDA_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_vooddc_setscl
r_static
r_void
id|bit_vooddc_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|r
suffix:semicolon
id|r
op_assign
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|r
op_or_assign
id|DDC_SCL_OUT
suffix:semicolon
r_else
id|r
op_and_assign
op_complement
id|DDC_SCL_OUT
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|bit_vooddc_setsda
r_static
r_void
id|bit_vooddc_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|val
)paren
(brace
r_int
r_int
id|r
suffix:semicolon
id|r
op_assign
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
id|r
op_or_assign
id|DDC_SDA_OUT
suffix:semicolon
r_else
id|r
op_and_assign
op_complement
id|DDC_SDA_OUT
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|bit_vooddc_getscl
r_static
r_int
id|bit_vooddc_getscl
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
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
op_amp
id|DDC_SCL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_vooddc_getsda
r_static
r_int
id|bit_vooddc_getsda
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
id|readl
c_func
(paren
id|ioaddr
op_plus
id|REG
)paren
op_amp
id|DDC_SDA_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|config_v3
r_static
r_int
id|config_v3
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|cadr
suffix:semicolon
multiline_comment|/* map Voodoo3 memory */
id|cadr
op_assign
id|dev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|cadr
op_and_assign
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
id|ioaddr
op_assign
id|ioremap_nocache
c_func
(paren
id|cadr
comma
l_int|0x1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioaddr
)paren
(brace
id|writel
c_func
(paren
l_int|0x8160
comma
id|ioaddr
op_plus
id|REG2
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0xcffc0020
comma
id|ioaddr
op_plus
id|REG
)paren
suffix:semicolon
id|dev_info
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;Using Banshee/Voodoo3 I2C device at %p&bslash;n&quot;
comma
id|ioaddr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|voo_i2c_bit_data
r_static
r_struct
id|i2c_algo_bit_data
id|voo_i2c_bit_data
op_assign
(brace
dot
id|setsda
op_assign
id|bit_vooi2c_setsda
comma
dot
id|setscl
op_assign
id|bit_vooi2c_setscl
comma
dot
id|getsda
op_assign
id|bit_vooi2c_getsda
comma
dot
id|getscl
op_assign
id|bit_vooi2c_getscl
comma
dot
id|udelay
op_assign
id|CYCLE_DELAY
comma
dot
id|mdelay
op_assign
id|CYCLE_DELAY
comma
dot
id|timeout
op_assign
id|TIMEOUT
)brace
suffix:semicolon
DECL|variable|voodoo3_i2c_adapter
r_static
r_struct
id|i2c_adapter
id|voodoo3_i2c_adapter
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
id|I2C_CLASS_TV_ANALOG
comma
dot
id|name
op_assign
l_string|&quot;I2C Voodoo3/Banshee adapter&quot;
comma
dot
id|algo_data
op_assign
op_amp
id|voo_i2c_bit_data
comma
)brace
suffix:semicolon
DECL|variable|voo_ddc_bit_data
r_static
r_struct
id|i2c_algo_bit_data
id|voo_ddc_bit_data
op_assign
(brace
dot
id|setsda
op_assign
id|bit_vooddc_setsda
comma
dot
id|setscl
op_assign
id|bit_vooddc_setscl
comma
dot
id|getsda
op_assign
id|bit_vooddc_getsda
comma
dot
id|getscl
op_assign
id|bit_vooddc_getscl
comma
dot
id|udelay
op_assign
id|CYCLE_DELAY
comma
dot
id|mdelay
op_assign
id|CYCLE_DELAY
comma
dot
id|timeout
op_assign
id|TIMEOUT
)brace
suffix:semicolon
DECL|variable|voodoo3_ddc_adapter
r_static
r_struct
id|i2c_adapter
id|voodoo3_ddc_adapter
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
id|I2C_CLASS_DDC
comma
dot
id|name
op_assign
l_string|&quot;DDC Voodoo3/Banshee adapter&quot;
comma
dot
id|algo_data
op_assign
op_amp
id|voo_ddc_bit_data
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|voodoo3_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_3DFX
comma
id|PCI_DEVICE_ID_3DFX_VOODOO3
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_3DFX
comma
id|PCI_DEVICE_ID_3DFX_BANSHEE
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
id|voodoo3_ids
)paren
suffix:semicolon
DECL|function|voodoo3_probe
r_static
r_int
id|__devinit
id|voodoo3_probe
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
r_int
id|retval
suffix:semicolon
id|retval
op_assign
id|config_v3
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* set up the sysfs linkage to our parent device */
id|voodoo3_i2c_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|voodoo3_ddc_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|retval
op_assign
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|voodoo3_i2c_adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
id|retval
op_assign
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|voodoo3_ddc_adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|voodoo3_i2c_adapter
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|voodoo3_remove
r_static
r_void
id|__devexit
id|voodoo3_remove
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
id|voodoo3_i2c_adapter
)paren
suffix:semicolon
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|voodoo3_ddc_adapter
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
)brace
DECL|variable|voodoo3_driver
r_static
r_struct
id|pci_driver
id|voodoo3_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;voodoo3_smbus&quot;
comma
dot
id|id_table
op_assign
id|voodoo3_ids
comma
dot
id|probe
op_assign
id|voodoo3_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|voodoo3_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_voodoo3_init
r_static
r_int
id|__init
id|i2c_voodoo3_init
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
id|voodoo3_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_voodoo3_exit
r_static
r_void
id|__exit
id|i2c_voodoo3_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|voodoo3_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Frodo Looijaard &lt;frodol@dds.nl&gt;, &quot;
l_string|&quot;Philip Edelbrock &lt;phil@netroedge.com&gt;, &quot;
l_string|&quot;Ralph Metzler &lt;rjkm@thp.uni-koeln.de&gt;, &quot;
l_string|&quot;and Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Voodoo3 I2C/SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_voodoo3_init
id|module_init
c_func
(paren
id|i2c_voodoo3_init
)paren
suffix:semicolon
DECL|variable|i2c_voodoo3_exit
id|module_exit
c_func
(paren
id|i2c_voodoo3_exit
)paren
suffix:semicolon
eof
