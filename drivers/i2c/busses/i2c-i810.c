multiline_comment|/*&n;    i2c-i810.c - Part of lm_sensors, Linux kernel modules for hardware&n;              monitoring&n;    Copyright (c) 1998, 1999, 2000  Frodo Looijaard &lt;frodol@dds.nl&gt;,&n;    Philip Edelbrock &lt;phil@netroedge.com&gt;,&n;    Ralph Metzler &lt;rjkm@thp.uni-koeln.de&gt;, and&n;    Mark D. Studebaker &lt;mdsxyz123@yahoo.com&gt;&n;    &n;    Based on code written by Ralph Metzler &lt;rjkm@thp.uni-koeln.de&gt; and&n;    Simon Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
multiline_comment|/*&n;   This interfaces to the I810/I815 to provide access to&n;   the DDC Bus and the I2C Bus.&n;&n;   SUPPORTED DEVICES&t;PCI ID&n;   i810AA&t;&t;7121           &n;   i810AB&t;&t;7123           &n;   i810E&t;&t;7125           &n;   i815&t;&t;&t;1132           &n;*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* GPIO register locations */
DECL|macro|I810_IOCONTROL_OFFSET
mdefine_line|#define I810_IOCONTROL_OFFSET&t;0x5000
DECL|macro|I810_HVSYNC
mdefine_line|#define I810_HVSYNC&t;&t;0x00&t;/* not used */
DECL|macro|I810_GPIOA
mdefine_line|#define I810_GPIOA&t;&t;0x10
DECL|macro|I810_GPIOB
mdefine_line|#define I810_GPIOB&t;&t;0x14
multiline_comment|/* bit locations in the registers */
DECL|macro|SCL_DIR_MASK
mdefine_line|#define SCL_DIR_MASK&t;&t;0x0001
DECL|macro|SCL_DIR
mdefine_line|#define SCL_DIR&t;&t;&t;0x0002
DECL|macro|SCL_VAL_MASK
mdefine_line|#define SCL_VAL_MASK&t;&t;0x0004
DECL|macro|SCL_VAL_OUT
mdefine_line|#define SCL_VAL_OUT&t;&t;0x0008
DECL|macro|SCL_VAL_IN
mdefine_line|#define SCL_VAL_IN&t;&t;0x0010
DECL|macro|SDA_DIR_MASK
mdefine_line|#define SDA_DIR_MASK&t;&t;0x0100
DECL|macro|SDA_DIR
mdefine_line|#define SDA_DIR&t;&t;&t;0x0200
DECL|macro|SDA_VAL_MASK
mdefine_line|#define SDA_VAL_MASK&t;&t;0x0400
DECL|macro|SDA_VAL_OUT
mdefine_line|#define SDA_VAL_OUT&t;&t;0x0800
DECL|macro|SDA_VAL_IN
mdefine_line|#define SDA_VAL_IN&t;&t;0x1000
multiline_comment|/* initialization states */
DECL|macro|INIT1
mdefine_line|#define INIT1&t;&t;&t;0x1
DECL|macro|INIT2
mdefine_line|#define INIT2&t;&t;&t;0x2
DECL|macro|INIT3
mdefine_line|#define INIT3&t;&t;&t;0x4
multiline_comment|/* delays */
DECL|macro|CYCLE_DELAY
mdefine_line|#define CYCLE_DELAY&t;&t;10
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT&t;&t;&t;(HZ / 2)
DECL|variable|ioaddr
r_static
r_void
op_star
id|ioaddr
suffix:semicolon
multiline_comment|/* The i810 GPIO registers have individual masks for each bit&n;   so we never have to read before writing. Nice. */
DECL|function|bit_i810i2c_setscl
r_static
r_void
id|bit_i810i2c_setscl
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
id|writel
c_func
(paren
(paren
id|val
ques
c_cond
id|SCL_VAL_OUT
suffix:colon
l_int|0
)paren
op_or
id|SCL_DIR
op_or
id|SCL_DIR_MASK
op_or
id|SCL_VAL_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|bit_i810i2c_setsda
r_static
r_void
id|bit_i810i2c_setsda
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
id|writel
c_func
(paren
(paren
id|val
ques
c_cond
id|SDA_VAL_OUT
suffix:colon
l_int|0
)paren
op_or
id|SDA_DIR
op_or
id|SDA_DIR_MASK
op_or
id|SDA_VAL_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
multiline_comment|/* The GPIO pins are open drain, so the pins could always remain outputs.&n;   However, some chip versions don&squot;t latch the inputs unless they&n;   are set as inputs.&n;   We rely on the i2c-algo-bit routines to set the pins high before&n;   reading the input from other chips. Following guidance in the 815&n;   prog. ref. guide, we do a &quot;dummy write&quot; of 0 to the register before&n;   reading which forces the input value to be latched. We presume this&n;   applies to the 810 as well; shouldn&squot;t hurt anyway. This is necessary to get&n;   i2c_algo_bit bit_test=1 to pass. */
DECL|function|bit_i810i2c_getscl
r_static
r_int
id|bit_i810i2c_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|writel
c_func
(paren
id|SCL_DIR_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
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
id|I810_GPIOB
)paren
op_amp
id|SCL_VAL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_i810i2c_getsda
r_static
r_int
id|bit_i810i2c_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|writel
c_func
(paren
id|SDA_DIR_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|I810_GPIOB
)paren
suffix:semicolon
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
id|I810_GPIOB
)paren
op_amp
id|SDA_VAL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_i810ddc_setscl
r_static
r_void
id|bit_i810ddc_setscl
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
id|writel
c_func
(paren
(paren
id|val
ques
c_cond
id|SCL_VAL_OUT
suffix:colon
l_int|0
)paren
op_or
id|SCL_DIR
op_or
id|SCL_DIR_MASK
op_or
id|SCL_VAL_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|bit_i810ddc_setsda
r_static
r_void
id|bit_i810ddc_setsda
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
id|writel
c_func
(paren
(paren
id|val
ques
c_cond
id|SDA_VAL_OUT
suffix:colon
l_int|0
)paren
op_or
id|SDA_DIR
op_or
id|SDA_DIR_MASK
op_or
id|SDA_VAL_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
id|readl
c_func
(paren
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|bit_i810ddc_getscl
r_static
r_int
id|bit_i810ddc_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|writel
c_func
(paren
id|SCL_DIR_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
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
id|I810_GPIOA
)paren
op_amp
id|SCL_VAL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_i810ddc_getsda
r_static
r_int
id|bit_i810ddc_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
id|writel
c_func
(paren
id|SDA_DIR_MASK
comma
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
id|writel
c_func
(paren
l_int|0
comma
id|ioaddr
op_plus
id|I810_GPIOA
)paren
suffix:semicolon
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
id|I810_GPIOA
)paren
op_amp
id|SDA_VAL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|config_i810
r_static
r_int
id|config_i810
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
multiline_comment|/* map I810 memory */
id|cadr
op_assign
id|dev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|cadr
op_add_assign
id|I810_IOCONTROL_OFFSET
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
id|bit_i810i2c_setscl
c_func
(paren
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
id|bit_i810i2c_setsda
c_func
(paren
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
id|bit_i810ddc_setscl
c_func
(paren
l_int|NULL
comma
l_int|1
)paren
suffix:semicolon
id|bit_i810ddc_setsda
c_func
(paren
l_int|NULL
comma
l_int|1
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
DECL|variable|i810_i2c_bit_data
r_static
r_struct
id|i2c_algo_bit_data
id|i810_i2c_bit_data
op_assign
(brace
dot
id|setsda
op_assign
id|bit_i810i2c_setsda
comma
dot
id|setscl
op_assign
id|bit_i810i2c_setscl
comma
dot
id|getsda
op_assign
id|bit_i810i2c_getsda
comma
dot
id|getscl
op_assign
id|bit_i810i2c_getscl
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
comma
)brace
suffix:semicolon
DECL|variable|i810_i2c_adapter
r_static
r_struct
id|i2c_adapter
id|i810_i2c_adapter
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
l_string|&quot;I810/I815 I2C Adapter&quot;
comma
dot
id|algo_data
op_assign
op_amp
id|i810_i2c_bit_data
comma
)brace
suffix:semicolon
DECL|variable|i810_ddc_bit_data
r_static
r_struct
id|i2c_algo_bit_data
id|i810_ddc_bit_data
op_assign
(brace
dot
id|setsda
op_assign
id|bit_i810ddc_setsda
comma
dot
id|setscl
op_assign
id|bit_i810ddc_setscl
comma
dot
id|getsda
op_assign
id|bit_i810ddc_getsda
comma
dot
id|getscl
op_assign
id|bit_i810ddc_getscl
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
comma
)brace
suffix:semicolon
DECL|variable|i810_ddc_adapter
r_static
r_struct
id|i2c_adapter
id|i810_ddc_adapter
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
l_string|&quot;I810/I815 DDC Adapter&quot;
comma
dot
id|algo_data
op_assign
op_amp
id|i810_ddc_bit_data
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|i810_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82810_IG1
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82810_IG3
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82810E_IG
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82815_CGC
)paren
)brace
comma
(brace
id|PCI_DEVICE
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82845G_IG
)paren
)brace
comma
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|function|i810_probe
r_static
r_int
id|__devinit
id|i810_probe
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
id|config_i810
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
id|dev_info
c_func
(paren
op_amp
id|dev-&gt;dev
comma
l_string|&quot;i810/i815 i2c device found.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* set up the sysfs linkage to our parent device */
id|i810_i2c_adapter.dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|i810_ddc_adapter.dev.parent
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
id|i810_i2c_adapter
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
id|i810_ddc_adapter
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
id|i810_i2c_adapter
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|i810_remove
r_static
r_void
id|__devexit
id|i810_remove
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
id|i810_ddc_adapter
)paren
suffix:semicolon
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|i810_i2c_adapter
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
)brace
DECL|variable|i810_driver
r_static
r_struct
id|pci_driver
id|i810_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;i810 smbus&quot;
comma
dot
id|id_table
op_assign
id|i810_ids
comma
dot
id|probe
op_assign
id|i810_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|i810_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|i2c_i810_init
r_static
r_int
id|__init
id|i2c_i810_init
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
id|i810_driver
)paren
suffix:semicolon
)brace
DECL|function|i2c_i810_exit
r_static
r_void
id|__exit
id|i2c_i810_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|i810_driver
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
l_string|&quot;I810/I815 I2C/DDC driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|i2c_i810_init
id|module_init
c_func
(paren
id|i2c_i810_init
)paren
suffix:semicolon
DECL|variable|i2c_i810_exit
id|module_exit
c_func
(paren
id|i2c_i810_exit
)paren
suffix:semicolon
eof
