multiline_comment|/*&n; * linux/drivers/video/riva/fbdev-i2c.c - nVidia i2c&n; *&n; * Maintained by Ani Joshi &lt;ajoshi@shell.unixbox.com&gt;&n; *&n; * Copyright 2004 Antonino A. Daplas &lt;adaplas @pol.net&gt;&n; *&n; * Based on radeonfb-i2c.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;rivafb.h&quot;
macro_line|#include &quot;../edid.h&quot;
DECL|macro|RIVA_DDC
mdefine_line|#define RIVA_DDC &t;0x50
DECL|function|riva_gpio_setscl
r_static
r_void
id|riva_gpio_setscl
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
r_struct
id|riva_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|riva_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_struct
id|riva_par
op_star
id|par
op_assign
id|chan-&gt;par
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d4
comma
id|chan-&gt;ddc_base
op_plus
l_int|1
)paren
suffix:semicolon
id|val
op_assign
id|VGA_RD08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d5
)paren
op_amp
l_int|0xf0
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
id|val
op_or_assign
l_int|0x20
suffix:semicolon
r_else
id|val
op_and_assign
op_complement
l_int|0x20
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d4
comma
id|chan-&gt;ddc_base
op_plus
l_int|1
)paren
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d5
comma
id|val
op_or
l_int|0x1
)paren
suffix:semicolon
)brace
DECL|function|riva_gpio_setsda
r_static
r_void
id|riva_gpio_setsda
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
r_struct
id|riva_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|riva_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_struct
id|riva_par
op_star
id|par
op_assign
id|chan-&gt;par
suffix:semicolon
id|u32
id|val
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d4
comma
id|chan-&gt;ddc_base
op_plus
l_int|1
)paren
suffix:semicolon
id|val
op_assign
id|VGA_RD08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d5
)paren
op_amp
l_int|0xf0
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
id|val
op_or_assign
l_int|0x10
suffix:semicolon
r_else
id|val
op_and_assign
op_complement
l_int|0x10
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d4
comma
id|chan-&gt;ddc_base
op_plus
l_int|1
)paren
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d5
comma
id|val
op_or
l_int|0x1
)paren
suffix:semicolon
)brace
DECL|function|riva_gpio_getscl
r_static
r_int
id|riva_gpio_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|riva_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|riva_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_struct
id|riva_par
op_star
id|par
op_assign
id|chan-&gt;par
suffix:semicolon
id|u32
id|val
op_assign
l_int|0
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d4
comma
id|chan-&gt;ddc_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VGA_RD08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d5
)paren
op_amp
l_int|0x04
)paren
id|val
op_assign
l_int|1
suffix:semicolon
id|val
op_assign
id|VGA_RD08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d5
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|riva_gpio_getsda
r_static
r_int
id|riva_gpio_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|riva_i2c_chan
op_star
id|chan
op_assign
(paren
r_struct
id|riva_i2c_chan
op_star
)paren
id|data
suffix:semicolon
r_struct
id|riva_par
op_star
id|par
op_assign
id|chan-&gt;par
suffix:semicolon
id|u32
id|val
op_assign
l_int|0
suffix:semicolon
id|VGA_WR08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d4
comma
id|chan-&gt;ddc_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|VGA_RD08
c_func
(paren
id|par-&gt;riva.PCIO
comma
l_int|0x3d5
)paren
op_amp
l_int|0x08
)paren
id|val
op_assign
l_int|1
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|macro|I2C_ALGO_RIVA
mdefine_line|#define I2C_ALGO_RIVA   0x0e0000
DECL|function|riva_setup_i2c_bus
r_static
r_int
id|riva_setup_i2c_bus
c_func
(paren
r_struct
id|riva_i2c_chan
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
id|rc
suffix:semicolon
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
id|I2C_ALGO_RIVA
suffix:semicolon
id|chan-&gt;adapter.algo_data
op_assign
op_amp
id|chan-&gt;algo
suffix:semicolon
id|chan-&gt;adapter.dev.parent
op_assign
op_amp
id|chan-&gt;par-&gt;pdev-&gt;dev
suffix:semicolon
id|chan-&gt;algo.setsda
op_assign
id|riva_gpio_setsda
suffix:semicolon
id|chan-&gt;algo.setscl
op_assign
id|riva_gpio_setscl
suffix:semicolon
id|chan-&gt;algo.getsda
op_assign
id|riva_gpio_getsda
suffix:semicolon
id|chan-&gt;algo.getscl
op_assign
id|riva_gpio_getscl
suffix:semicolon
id|chan-&gt;algo.udelay
op_assign
l_int|5
suffix:semicolon
id|chan-&gt;algo.mdelay
op_assign
l_int|5
suffix:semicolon
id|chan-&gt;algo.timeout
op_assign
l_int|10
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
id|riva_gpio_setsda
c_func
(paren
id|chan
comma
l_int|1
)paren
suffix:semicolon
id|riva_gpio_setscl
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
id|i2c_bit_add_bus
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
id|chan-&gt;par-&gt;pdev-&gt;dev
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
id|chan-&gt;par-&gt;pdev-&gt;dev
comma
l_string|&quot;Failed to register I2C bus %s.&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|riva_create_i2c_busses
r_void
id|riva_create_i2c_busses
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
id|par-&gt;chan
(braket
l_int|0
)braket
dot
id|par
op_assign
id|par
suffix:semicolon
id|par-&gt;chan
(braket
l_int|1
)braket
dot
id|par
op_assign
id|par
suffix:semicolon
id|par-&gt;chan
(braket
l_int|2
)braket
dot
id|par
op_assign
id|par
suffix:semicolon
r_switch
c_cond
(paren
id|par-&gt;riva.Architecture
)paren
(brace
macro_line|#if 0&t;&t;/* no support yet for other nVidia chipsets */
id|par-&gt;chan
(braket
l_int|2
)braket
dot
id|ddc_base
op_assign
l_int|0x50
suffix:semicolon
id|riva_setup_i2c_bus
c_func
(paren
op_amp
id|par-&gt;chan
(braket
l_int|2
)braket
comma
l_string|&quot;BUS2&quot;
)paren
suffix:semicolon
macro_line|#endif
r_case
id|NV_ARCH_10
suffix:colon
r_case
id|NV_ARCH_20
suffix:colon
r_case
id|NV_ARCH_04
suffix:colon
id|par-&gt;chan
(braket
l_int|1
)braket
dot
id|ddc_base
op_assign
l_int|0x36
suffix:semicolon
id|riva_setup_i2c_bus
c_func
(paren
op_amp
id|par-&gt;chan
(braket
l_int|1
)braket
comma
l_string|&quot;BUS1&quot;
)paren
suffix:semicolon
r_case
id|NV_ARCH_03
suffix:colon
id|par-&gt;chan
(braket
l_int|0
)braket
dot
id|ddc_base
op_assign
l_int|0x3e
suffix:semicolon
id|riva_setup_i2c_bus
c_func
(paren
op_amp
id|par-&gt;chan
(braket
l_int|0
)braket
comma
l_string|&quot;BUS0&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|riva_delete_i2c_busses
r_void
id|riva_delete_i2c_busses
c_func
(paren
r_struct
id|riva_par
op_star
id|par
)paren
(brace
r_if
c_cond
(paren
id|par-&gt;chan
(braket
l_int|0
)braket
dot
id|par
)paren
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|par-&gt;chan
(braket
l_int|0
)braket
dot
id|adapter
)paren
suffix:semicolon
id|par-&gt;chan
(braket
l_int|0
)braket
dot
id|par
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|par-&gt;chan
(braket
l_int|1
)braket
dot
id|par
)paren
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|par-&gt;chan
(braket
l_int|1
)braket
dot
id|adapter
)paren
suffix:semicolon
id|par-&gt;chan
(braket
l_int|1
)braket
dot
id|par
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|riva_do_probe_i2c_edid
r_static
id|u8
op_star
id|riva_do_probe_i2c_edid
c_func
(paren
r_struct
id|riva_i2c_chan
op_star
id|chan
)paren
(brace
id|u8
id|start
op_assign
l_int|0x0
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
id|RIVA_DDC
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
id|RIVA_DDC
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
suffix:semicolon
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
op_logical_neg
id|buf
)paren
(brace
id|dev_warn
c_func
(paren
op_amp
id|chan-&gt;par-&gt;pdev-&gt;dev
comma
l_string|&quot;Out of memory!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
id|i2c_transfer
c_func
(paren
op_amp
id|chan-&gt;adapter
comma
id|msgs
comma
l_int|2
)paren
op_eq
l_int|2
)paren
r_return
id|buf
suffix:semicolon
id|dev_dbg
c_func
(paren
op_amp
id|chan-&gt;par-&gt;pdev-&gt;dev
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
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|riva_probe_i2c_connector
r_int
id|riva_probe_i2c_connector
c_func
(paren
r_struct
id|riva_par
op_star
id|par
comma
r_int
id|conn
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
id|riva_do_probe_i2c_edid
c_func
(paren
op_amp
id|par-&gt;chan
(braket
id|conn
op_minus
l_int|1
)braket
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
eof
