multiline_comment|/*&n;    i2c-savage4.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;    Copyright (C) 1998-2003  The LM Sensors Team&n;    Alexander Wold &lt;awold@bigfoot.com&gt;&n;    Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;    &n;    Based on i2c-voodoo3.c.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/* This interfaces to the I2C bus of the Savage4 to gain access to&n;   the BT869 and possibly other I2C devices. The DDC bus is not&n;   yet supported because its register is not memory-mapped.&n;   However we leave the DDC code here, commented out, to make&n;   it easier to add later.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* 3DFX defines */
DECL|macro|PCI_CHIP_SAVAGE3D
mdefine_line|#define PCI_CHIP_SAVAGE3D&t;0x8A20
DECL|macro|PCI_CHIP_SAVAGE3D_MV
mdefine_line|#define PCI_CHIP_SAVAGE3D_MV&t;0x8A21
DECL|macro|PCI_CHIP_SAVAGE4
mdefine_line|#define PCI_CHIP_SAVAGE4&t;0x8A22
DECL|macro|PCI_CHIP_SAVAGE2000
mdefine_line|#define PCI_CHIP_SAVAGE2000&t;0x9102
DECL|macro|PCI_CHIP_PROSAVAGE_PM
mdefine_line|#define PCI_CHIP_PROSAVAGE_PM&t;0x8A25
DECL|macro|PCI_CHIP_PROSAVAGE_KM
mdefine_line|#define PCI_CHIP_PROSAVAGE_KM&t;0x8A26
DECL|macro|PCI_CHIP_SAVAGE_MX_MV
mdefine_line|#define PCI_CHIP_SAVAGE_MX_MV&t;0x8c10
DECL|macro|PCI_CHIP_SAVAGE_MX
mdefine_line|#define PCI_CHIP_SAVAGE_MX&t;0x8c11
DECL|macro|PCI_CHIP_SAVAGE_IX_MV
mdefine_line|#define PCI_CHIP_SAVAGE_IX_MV&t;0x8c12
DECL|macro|PCI_CHIP_SAVAGE_IX
mdefine_line|#define PCI_CHIP_SAVAGE_IX&t;0x8c13
DECL|macro|REG
mdefine_line|#define REG&t;&t;&t;0xff20&t;/* Serial Port 1 Register */
multiline_comment|/* bit locations in the register */
DECL|macro|DDC_ENAB
mdefine_line|#define DDC_ENAB&t;&t;0x00040000
DECL|macro|DDC_SCL_OUT
mdefine_line|#define DDC_SCL_OUT&t;&t;0x00080000
DECL|macro|DDC_SDA_OUT
mdefine_line|#define DDC_SDA_OUT&t;&t;0x00100000
DECL|macro|DDC_SCL_IN
mdefine_line|#define DDC_SCL_IN&t;&t;0x00200000
DECL|macro|DDC_SDA_IN
mdefine_line|#define DDC_SDA_IN&t;&t;0x00400000
DECL|macro|I2C_ENAB
mdefine_line|#define I2C_ENAB&t;&t;0x00000020
DECL|macro|I2C_SCL_OUT
mdefine_line|#define I2C_SCL_OUT&t;&t;0x00000001
DECL|macro|I2C_SDA_OUT
mdefine_line|#define I2C_SDA_OUT&t;&t;0x00000002
DECL|macro|I2C_SCL_IN
mdefine_line|#define I2C_SCL_IN&t;&t;0x00000008
DECL|macro|I2C_SDA_IN
mdefine_line|#define I2C_SDA_IN&t;&t;0x00000010
multiline_comment|/* initialization states */
DECL|macro|INIT2
mdefine_line|#define INIT2&t;&t;&t;0x20
DECL|macro|INIT3
mdefine_line|#define INIT3&t;&t;&t;0x04
multiline_comment|/* delays */
DECL|macro|CYCLE_DELAY
mdefine_line|#define CYCLE_DELAY&t;&t;10
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;&t;&t;(HZ / 2)
DECL|variable|ioaddr
r_static
r_void
id|__iomem
op_star
id|ioaddr
suffix:semicolon
multiline_comment|/* The sav GPIO registers don&squot;t have individual masks for each bit&n;   so we always have to read before writing. */
DECL|function|bit_savi2c_setscl
r_static
r_void
id|bit_savi2c_setscl
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
(brace
id|r
op_or_assign
id|I2C_SCL_OUT
suffix:semicolon
)brace
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
DECL|function|bit_savi2c_setsda
r_static
r_void
id|bit_savi2c_setsda
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
(brace
id|r
op_or_assign
id|I2C_SDA_OUT
suffix:semicolon
)brace
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
DECL|function|bit_savi2c_getscl
r_static
r_int
id|bit_savi2c_getscl
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
DECL|function|bit_savi2c_getsda
r_static
r_int
id|bit_savi2c_getsda
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
multiline_comment|/* Configures the chip */
DECL|function|config_s4
r_static
r_int
id|config_s4
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
multiline_comment|/* map memory */
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
l_int|0x0080000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ioaddr
)paren
(brace
multiline_comment|/* writel(0x8160, ioaddr + REG2); */
id|writel
c_func
(paren
l_int|0x00000020
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
l_string|&quot;Using Savage4 at %p&bslash;n&quot;
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
DECL|variable|sav_i2c_bit_data
r_static
r_struct
id|i2c_algo_bit_data
id|sav_i2c_bit_data
op_assign
(brace
dot
id|setsda
op_assign
id|bit_savi2c_setsda
comma
dot
id|setscl
op_assign
id|bit_savi2c_setscl
comma
dot
id|getsda
op_assign
id|bit_savi2c_getsda
comma
dot
id|getscl
op_assign
id|bit_savi2c_getscl
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
DECL|variable|savage4_i2c_adapter
r_static
r_struct
id|i2c_adapter
id|savage4_i2c_adapter
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
l_string|&quot;I2C Savage4 adapter&quot;
comma
dot
id|algo_data
op_assign
op_amp
id|sav_i2c_bit_data
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|savage4_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_S3
comma
id|PCI_CHIP_SAVAGE4
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_S3
comma
id|PCI_CHIP_SAVAGE2000
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
id|savage4_ids
)paren
suffix:semicolon
DECL|function|savage4_probe
r_static
r_int
id|__devinit
id|savage4_probe
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
id|config_s4
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
id|savage4_i2c_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
r_return
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|savage4_i2c_adapter
)paren
suffix:semicolon
)brace
DECL|function|savage4_remove
r_static
r_void
id|__devexit
id|savage4_remove
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
id|savage4_i2c_adapter
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
)brace
DECL|variable|savage4_driver
r_static
r_struct
id|pci_driver
id|savage4_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;savage4_smbus&quot;
comma
dot
id|id_table
op_assign
id|savage4_ids
comma
dot
id|probe
op_assign
id|savage4_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|savage4_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_savage4_init
r_static
r_int
id|__init
id|i2c_savage4_init
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
id|savage4_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_savage4_exit
r_static
r_void
id|__exit
id|i2c_savage4_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|savage4_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Alexander Wold &lt;awold@bigfoot.com&gt; &quot;
l_string|&quot;and Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Savage4 I2C/SMBus driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_savage4_init
id|module_init
c_func
(paren
id|i2c_savage4_init
)paren
suffix:semicolon
DECL|variable|i2c_savage4_exit
id|module_exit
c_func
(paren
id|i2c_savage4_exit
)paren
suffix:semicolon
eof
