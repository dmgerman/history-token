multiline_comment|/*&n; * linux/drivers/video/savage/savagefb-i2c.c - S3 Savage DDC2&n; *&n; * Copyright 2004 Antonino A. Daplas &lt;adaplas @pol.net&gt;&n; *&n; * Based partly on rivafb-i2c.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;savagefb.h&quot;
DECL|macro|SAVAGE_DDC
mdefine_line|#define SAVAGE_DDC &t;0x50
DECL|macro|VGA_CR_IX
mdefine_line|#define VGA_CR_IX&t;0x3d4
DECL|macro|VGA_CR_DATA
mdefine_line|#define VGA_CR_DATA&t;0x3d5
DECL|macro|CR_SERIAL1
mdefine_line|#define CR_SERIAL1&t;0xa0&t;/* I2C serial communications interface */
DECL|macro|MM_SERIAL1
mdefine_line|#define MM_SERIAL1&t;0xff20
DECL|macro|CR_SERIAL2
mdefine_line|#define CR_SERIAL2&t;0xb1&t;/* DDC2 monitor communications interface */
multiline_comment|/* based on vt8365 documentation */
DECL|macro|PROSAVAGE_I2C_ENAB
mdefine_line|#define PROSAVAGE_I2C_ENAB&t;0x10
DECL|macro|PROSAVAGE_I2C_SCL_OUT
mdefine_line|#define PROSAVAGE_I2C_SCL_OUT&t;0x01
DECL|macro|PROSAVAGE_I2C_SDA_OUT
mdefine_line|#define PROSAVAGE_I2C_SDA_OUT&t;0x02
DECL|macro|PROSAVAGE_I2C_SCL_IN
mdefine_line|#define PROSAVAGE_I2C_SCL_IN&t;0x04
DECL|macro|PROSAVAGE_I2C_SDA_IN
mdefine_line|#define PROSAVAGE_I2C_SDA_IN&t;0x08
DECL|macro|SAVAGE4_I2C_ENAB
mdefine_line|#define SAVAGE4_I2C_ENAB&t;0x00000020
DECL|macro|SAVAGE4_I2C_SCL_OUT
mdefine_line|#define SAVAGE4_I2C_SCL_OUT&t;0x00000001
DECL|macro|SAVAGE4_I2C_SDA_OUT
mdefine_line|#define SAVAGE4_I2C_SDA_OUT&t;0x00000002
DECL|macro|SAVAGE4_I2C_SCL_IN
mdefine_line|#define SAVAGE4_I2C_SCL_IN&t;0x00000008
DECL|macro|SAVAGE4_I2C_SDA_IN
mdefine_line|#define SAVAGE4_I2C_SDA_IN&t;0x00000010
DECL|macro|SET_CR_IX
mdefine_line|#define SET_CR_IX(base, val)&t;writeb((val), base + 0x8000 + VGA_CR_IX)
DECL|macro|SET_CR_DATA
mdefine_line|#define SET_CR_DATA(base, val)&t;writeb((val), base + 0x8000 + VGA_CR_DATA)
DECL|macro|GET_CR_DATA
mdefine_line|#define GET_CR_DATA(base)&t;readb(base + 0x8000 + VGA_CR_DATA)
DECL|function|savage4_gpio_setscl
r_static
r_void
id|savage4_gpio_setscl
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
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|r
suffix:semicolon
id|r
op_assign
id|readl
c_func
(paren
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
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
id|SAVAGE4_I2C_SCL_OUT
suffix:semicolon
)brace
r_else
id|r
op_and_assign
op_complement
id|SAVAGE4_I2C_SCL_OUT
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
)paren
suffix:semicolon
id|readl
c_func
(paren
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|savage4_gpio_setsda
r_static
r_void
id|savage4_gpio_setsda
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
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|r
suffix:semicolon
id|r
op_assign
id|readl
c_func
(paren
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
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
id|SAVAGE4_I2C_SDA_OUT
suffix:semicolon
)brace
r_else
id|r
op_and_assign
op_complement
id|SAVAGE4_I2C_SDA_OUT
suffix:semicolon
id|writel
c_func
(paren
id|r
comma
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
)paren
suffix:semicolon
id|readl
c_func
(paren
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
)paren
suffix:semicolon
multiline_comment|/* flush posted write */
)brace
DECL|function|savage4_gpio_getscl
r_static
r_int
id|savage4_gpio_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_return
(paren
l_int|0
op_ne
(paren
id|readl
c_func
(paren
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
)paren
op_amp
id|SAVAGE4_I2C_SCL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|savage4_gpio_getsda
r_static
r_int
id|savage4_gpio_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_return
(paren
l_int|0
op_ne
(paren
id|readl
c_func
(paren
id|chan-&gt;ioaddr
op_plus
id|chan-&gt;reg
)paren
op_amp
id|SAVAGE4_I2C_SDA_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|prosavage_gpio_setscl
r_static
r_void
id|prosavage_gpio_setscl
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
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
id|u32
id|r
suffix:semicolon
id|SET_CR_IX
c_func
(paren
id|chan-&gt;ioaddr
comma
id|chan-&gt;reg
)paren
suffix:semicolon
id|r
op_assign
id|GET_CR_DATA
c_func
(paren
id|chan-&gt;ioaddr
)paren
suffix:semicolon
id|r
op_or_assign
id|PROSAVAGE_I2C_ENAB
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|r
op_or_assign
id|PROSAVAGE_I2C_SCL_OUT
suffix:semicolon
)brace
r_else
(brace
id|r
op_and_assign
op_complement
id|PROSAVAGE_I2C_SCL_OUT
suffix:semicolon
)brace
id|SET_CR_DATA
c_func
(paren
id|chan-&gt;ioaddr
comma
id|r
)paren
suffix:semicolon
)brace
DECL|function|prosavage_gpio_setsda
r_static
r_void
id|prosavage_gpio_setsda
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
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|r
suffix:semicolon
id|SET_CR_IX
c_func
(paren
id|chan-&gt;ioaddr
comma
id|chan-&gt;reg
)paren
suffix:semicolon
id|r
op_assign
id|GET_CR_DATA
c_func
(paren
id|chan-&gt;ioaddr
)paren
suffix:semicolon
id|r
op_or_assign
id|PROSAVAGE_I2C_ENAB
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
id|r
op_or_assign
id|PROSAVAGE_I2C_SDA_OUT
suffix:semicolon
)brace
r_else
(brace
id|r
op_and_assign
op_complement
id|PROSAVAGE_I2C_SDA_OUT
suffix:semicolon
)brace
id|SET_CR_DATA
c_func
(paren
id|chan-&gt;ioaddr
comma
id|r
)paren
suffix:semicolon
)brace
DECL|function|prosavage_gpio_getscl
r_static
r_int
id|prosavage_gpio_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
id|SET_CR_IX
c_func
(paren
id|chan-&gt;ioaddr
comma
id|chan-&gt;reg
)paren
suffix:semicolon
r_return
(paren
l_int|0
op_ne
(paren
id|GET_CR_DATA
c_func
(paren
id|chan-&gt;ioaddr
)paren
op_amp
id|PROSAVAGE_I2C_SCL_IN
)paren
)paren
suffix:semicolon
)brace
DECL|function|prosavage_gpio_getsda
r_static
r_int
id|prosavage_gpio_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|savagefb_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|savagefb_i2c_chan
op_star
)paren
id|data
suffix:semicolon
id|SET_CR_IX
c_func
(paren
id|chan-&gt;ioaddr
comma
id|chan-&gt;reg
)paren
suffix:semicolon
r_return
(paren
l_int|0
op_ne
(paren
id|GET_CR_DATA
c_func
(paren
id|chan-&gt;ioaddr
)paren
op_amp
id|PROSAVAGE_I2C_SDA_IN
)paren
)paren
suffix:semicolon
)brace
DECL|macro|I2C_ALGO_SAVAGE
mdefine_line|#define I2C_ALGO_SAVAGE   0x0f0000
DECL|function|savage_setup_i2c_bus
r_static
r_int
id|savage_setup_i2c_bus
c_func
(paren
r_struct
id|savagefb_i2c_chan
op_star
id|chan
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
(paren
op_star
id|add_bus
)paren
(paren
r_struct
id|i2c_adapter
op_star
)paren
op_assign
id|symbol_get
c_func
(paren
id|i2c_bit_add_bus
)paren
suffix:semicolon
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|add_bus
op_logical_and
id|chan-&gt;par
)paren
(brace
id|strcpy
c_func
(paren
id|chan-&gt;adapter.name
comma
id|name
)paren
suffix:semicolon
id|chan-&gt;adapter.owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|chan-&gt;adapter.id
op_assign
id|I2C_ALGO_SAVAGE
suffix:semicolon
id|chan-&gt;adapter.algo_data
op_assign
op_amp
id|chan-&gt;algo
suffix:semicolon
id|chan-&gt;adapter.dev.parent
op_assign
op_amp
id|chan-&gt;par-&gt;pcidev-&gt;dev
suffix:semicolon
id|chan-&gt;algo.udelay
op_assign
l_int|40
suffix:semicolon
id|chan-&gt;algo.mdelay
op_assign
l_int|5
suffix:semicolon
id|chan-&gt;algo.timeout
op_assign
l_int|20
suffix:semicolon
id|chan-&gt;algo.data
op_assign
id|chan
suffix:semicolon
id|i2c_set_adapdata
c_func
(paren
op_amp
id|chan-&gt;adapter
comma
id|chan
)paren
suffix:semicolon
multiline_comment|/* Raise SCL and SDA */
id|chan-&gt;algo
dot
id|setsda
c_func
(paren
id|chan
comma
l_int|1
)paren
suffix:semicolon
id|chan-&gt;algo
dot
id|setscl
c_func
(paren
id|chan
comma
l_int|1
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|rc
op_assign
id|add_bus
c_func
(paren
op_amp
id|chan-&gt;adapter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_eq
l_int|0
)paren
id|dev_dbg
c_func
(paren
op_amp
id|chan-&gt;par-&gt;pcidev-&gt;dev
comma
l_string|&quot;I2C bus %s registered.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_else
id|dev_warn
c_func
(paren
op_amp
id|chan-&gt;par-&gt;pcidev-&gt;dev
comma
l_string|&quot;Failed to register I2C bus %s.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|symbol_put
c_func
(paren
id|i2c_bit_add_bus
)paren
suffix:semicolon
)brace
r_else
id|chan-&gt;par
op_assign
l_int|NULL
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|savagefb_create_i2c_busses
r_void
id|savagefb_create_i2c_busses
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|savagefb_par
op_star
id|par
op_assign
(paren
r_struct
id|savagefb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
id|par-&gt;chan.par
op_assign
id|par
suffix:semicolon
r_switch
c_cond
(paren
id|info-&gt;fix.accel
)paren
(brace
r_case
id|FB_ACCEL_PROSAVAGE_DDRK
suffix:colon
r_case
id|FB_ACCEL_PROSAVAGE_PM
suffix:colon
id|par-&gt;chan.reg
op_assign
id|CR_SERIAL2
suffix:semicolon
id|par-&gt;chan.ioaddr
op_assign
id|par-&gt;mmio.vbase
suffix:semicolon
id|par-&gt;chan.algo.setsda
op_assign
id|prosavage_gpio_setsda
suffix:semicolon
id|par-&gt;chan.algo.setscl
op_assign
id|prosavage_gpio_setscl
suffix:semicolon
id|par-&gt;chan.algo.getsda
op_assign
id|prosavage_gpio_getsda
suffix:semicolon
id|par-&gt;chan.algo.getscl
op_assign
id|prosavage_gpio_getscl
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FB_ACCEL_SAVAGE4
suffix:colon
id|par-&gt;chan.reg
op_assign
l_int|0xff20
suffix:semicolon
id|par-&gt;chan.ioaddr
op_assign
id|par-&gt;mmio.vbase
suffix:semicolon
id|par-&gt;chan.algo.setsda
op_assign
id|savage4_gpio_setsda
suffix:semicolon
id|par-&gt;chan.algo.setscl
op_assign
id|savage4_gpio_setscl
suffix:semicolon
id|par-&gt;chan.algo.getsda
op_assign
id|savage4_gpio_getsda
suffix:semicolon
id|par-&gt;chan.algo.getscl
op_assign
id|savage4_gpio_getscl
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|par-&gt;chan.par
op_assign
l_int|NULL
suffix:semicolon
)brace
id|savage_setup_i2c_bus
c_func
(paren
op_amp
id|par-&gt;chan
comma
l_string|&quot;SAVAGE DDC2&quot;
)paren
suffix:semicolon
)brace
DECL|variable|savagefb_create_i2c_busses
id|EXPORT_SYMBOL
c_func
(paren
id|savagefb_create_i2c_busses
)paren
suffix:semicolon
DECL|function|savagefb_delete_i2c_busses
r_void
id|savagefb_delete_i2c_busses
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|savagefb_par
op_star
id|par
op_assign
(paren
r_struct
id|savagefb_par
op_star
)paren
id|info-&gt;par
suffix:semicolon
r_int
(paren
op_star
id|del_bus
)paren
(paren
r_struct
id|i2c_adapter
op_star
)paren
op_assign
id|symbol_get
c_func
(paren
id|i2c_bit_del_bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|del_bus
op_logical_and
id|par-&gt;chan.par
)paren
(brace
id|del_bus
c_func
(paren
op_amp
id|par-&gt;chan.adapter
)paren
suffix:semicolon
id|symbol_put
c_func
(paren
id|i2c_bit_del_bus
)paren
suffix:semicolon
)brace
id|par-&gt;chan.par
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|variable|savagefb_delete_i2c_busses
id|EXPORT_SYMBOL
c_func
(paren
id|savagefb_delete_i2c_busses
)paren
suffix:semicolon
DECL|function|savage_do_probe_i2c_edid
r_static
id|u8
op_star
id|savage_do_probe_i2c_edid
c_func
(paren
r_struct
id|savagefb_i2c_chan
op_star
id|chan
)paren
(brace
id|u8
id|start
op_assign
l_int|0x0
suffix:semicolon
r_int
(paren
op_star
id|transfer
)paren
(paren
r_struct
id|i2c_adapter
op_star
comma
r_struct
id|i2c_msg
op_star
comma
r_int
)paren
op_assign
id|symbol_get
c_func
(paren
id|i2c_transfer
)paren
suffix:semicolon
r_struct
id|i2c_msg
id|msgs
(braket
)braket
op_assign
(brace
(brace
dot
id|addr
op_assign
id|SAVAGE_DDC
comma
dot
id|len
op_assign
l_int|1
comma
dot
id|buf
op_assign
op_amp
id|start
comma
)brace
comma
(brace
dot
id|addr
op_assign
id|SAVAGE_DDC
comma
dot
id|flags
op_assign
id|I2C_M_RD
comma
dot
id|len
op_assign
id|EDID_LENGTH
comma
)brace
comma
)brace
suffix:semicolon
id|u8
op_star
id|buf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|transfer
op_logical_and
id|chan-&gt;par
)paren
(brace
id|buf
op_assign
id|kmalloc
c_func
(paren
id|EDID_LENGTH
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
(brace
id|msgs
(braket
l_int|1
)braket
dot
id|buf
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|transfer
c_func
(paren
op_amp
id|chan-&gt;adapter
comma
id|msgs
comma
l_int|2
)paren
op_ne
l_int|2
)paren
(brace
id|dev_dbg
c_func
(paren
op_amp
id|chan-&gt;par-&gt;pcidev-&gt;dev
comma
l_string|&quot;Unable to read EDID block.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|buf
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|symbol_put
c_func
(paren
id|i2c_transfer
)paren
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
DECL|function|savagefb_probe_i2c_connector
r_int
id|savagefb_probe_i2c_connector
c_func
(paren
r_struct
id|savagefb_par
op_star
id|par
comma
id|u8
op_star
op_star
id|out_edid
)paren
(brace
id|u8
op_star
id|edid
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Do the real work */
id|edid
op_assign
id|savage_do_probe_i2c_edid
c_func
(paren
op_amp
id|par-&gt;chan
)paren
suffix:semicolon
r_if
c_cond
(paren
id|edid
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out_edid
)paren
op_star
id|out_edid
op_assign
id|edid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|edid
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|savagefb_probe_i2c_connector
id|EXPORT_SYMBOL
c_func
(paren
id|savagefb_probe_i2c_connector
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
