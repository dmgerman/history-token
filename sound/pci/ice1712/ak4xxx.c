multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *   AK4524 / AK4528 / AK4529 / AK4355 / AK4381 interface&n; *&n; *&t;Copyright (c) 2000 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &quot;ice1712.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ICEnsemble ICE17xx &lt;-&gt; AK4xxx AD/DA chip interface&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|snd_ice1712_akm4xxx_lock
r_static
r_void
id|snd_ice1712_akm4xxx_lock
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
id|chip
)paren
(brace
id|ice1712_t
op_star
id|ice
op_assign
id|ak-&gt;private_data
(braket
l_int|0
)braket
suffix:semicolon
id|snd_ice1712_save_gpio_status
c_func
(paren
id|ice
)paren
suffix:semicolon
)brace
DECL|function|snd_ice1712_akm4xxx_unlock
r_static
r_void
id|snd_ice1712_akm4xxx_unlock
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
id|chip
)paren
(brace
id|ice1712_t
op_star
id|ice
op_assign
id|ak-&gt;private_data
(braket
l_int|0
)braket
suffix:semicolon
id|snd_ice1712_restore_gpio_status
c_func
(paren
id|ice
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * write AK4xxx register&n; */
DECL|function|snd_ice1712_akm4xxx_write
r_static
r_void
id|snd_ice1712_akm4xxx_write
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
id|chip
comma
r_int
r_char
id|addr
comma
r_int
r_char
id|data
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_int
r_int
id|addrdata
suffix:semicolon
r_struct
id|snd_ak4xxx_private
op_star
id|priv
op_assign
(paren
r_void
op_star
)paren
id|ak-&gt;private_value
(braket
l_int|0
)braket
suffix:semicolon
id|ice1712_t
op_star
id|ice
op_assign
id|ak-&gt;private_data
(braket
l_int|0
)braket
suffix:semicolon
id|snd_assert
c_func
(paren
id|chip
op_ge
l_int|0
op_logical_and
id|chip
OL
l_int|4
comma
r_return
)paren
suffix:semicolon
id|tmp
op_assign
id|snd_ice1712_gpio_read
c_func
(paren
id|ice
)paren
suffix:semicolon
id|tmp
op_or_assign
id|priv-&gt;add_flags
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|priv-&gt;mask_flags
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;cs_mask
op_eq
id|priv-&gt;cs_addr
)paren
(brace
r_if
c_cond
(paren
id|priv-&gt;cif
)paren
(brace
id|tmp
op_or_assign
id|priv-&gt;cs_mask
suffix:semicolon
multiline_comment|/* start without chip select */
)brace
r_else
(brace
id|tmp
op_and_assign
op_complement
id|priv-&gt;cs_mask
suffix:semicolon
multiline_comment|/* chip select low */
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|tmp
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* doesn&squot;t handle cf=1 yet */
id|tmp
op_and_assign
op_complement
id|priv-&gt;cs_mask
suffix:semicolon
id|tmp
op_or_assign
id|priv-&gt;cs_addr
suffix:semicolon
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|tmp
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* build I2C address + data byte */
id|addrdata
op_assign
(paren
id|priv-&gt;caddr
op_lshift
l_int|6
)paren
op_or
l_int|0x20
op_or
(paren
id|addr
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|addrdata
op_assign
(paren
id|addrdata
op_lshift
l_int|8
)paren
op_or
id|data
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|15
suffix:semicolon
id|idx
op_ge
l_int|0
suffix:semicolon
id|idx
op_decrement
)paren
(brace
multiline_comment|/* drop clock */
id|tmp
op_and_assign
op_complement
id|priv-&gt;clk_mask
suffix:semicolon
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|tmp
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* set data */
r_if
c_cond
(paren
id|addrdata
op_amp
(paren
l_int|1
op_lshift
id|idx
)paren
)paren
id|tmp
op_or_assign
id|priv-&gt;data_mask
suffix:semicolon
r_else
id|tmp
op_and_assign
op_complement
id|priv-&gt;data_mask
suffix:semicolon
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|tmp
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* raise clock */
id|tmp
op_or_assign
id|priv-&gt;clk_mask
suffix:semicolon
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|tmp
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;cs_mask
op_eq
id|priv-&gt;cs_addr
)paren
(brace
r_if
c_cond
(paren
id|priv-&gt;cif
)paren
(brace
multiline_comment|/* assert a cs pulse to trigger */
id|tmp
op_and_assign
op_complement
id|priv-&gt;cs_mask
suffix:semicolon
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|tmp
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|tmp
op_or_assign
id|priv-&gt;cs_mask
suffix:semicolon
multiline_comment|/* chip select high to trigger */
)brace
r_else
(brace
id|tmp
op_and_assign
op_complement
id|priv-&gt;cs_mask
suffix:semicolon
id|tmp
op_or_assign
id|priv-&gt;cs_none
suffix:semicolon
multiline_comment|/* deselect address */
)brace
id|snd_ice1712_gpio_write
c_func
(paren
id|ice
comma
id|tmp
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * initialize the akm4xxx_t record with the template&n; */
DECL|function|snd_ice1712_akm4xxx_init
r_int
id|snd_ice1712_akm4xxx_init
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_const
id|akm4xxx_t
op_star
id|temp
comma
r_const
r_struct
id|snd_ak4xxx_private
op_star
id|_priv
comma
id|ice1712_t
op_star
id|ice
)paren
(brace
r_struct
id|snd_ak4xxx_private
op_star
id|priv
suffix:semicolon
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|ak
op_assign
op_star
id|temp
suffix:semicolon
id|ak-&gt;card
op_assign
id|ice-&gt;card
suffix:semicolon
op_star
id|priv
op_assign
op_star
id|_priv
suffix:semicolon
id|ak-&gt;private_value
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|priv
suffix:semicolon
id|ak-&gt;private_data
(braket
l_int|0
)braket
op_assign
id|ice
suffix:semicolon
r_if
c_cond
(paren
id|ak-&gt;ops.lock
op_eq
l_int|NULL
)paren
id|ak-&gt;ops.lock
op_assign
id|snd_ice1712_akm4xxx_lock
suffix:semicolon
r_if
c_cond
(paren
id|ak-&gt;ops.unlock
op_eq
l_int|NULL
)paren
id|ak-&gt;ops.unlock
op_assign
id|snd_ice1712_akm4xxx_unlock
suffix:semicolon
r_if
c_cond
(paren
id|ak-&gt;ops.write
op_eq
l_int|NULL
)paren
id|ak-&gt;ops.write
op_assign
id|snd_ice1712_akm4xxx_write
suffix:semicolon
id|snd_akm4xxx_init
c_func
(paren
id|ak
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_ice1712_akm4xxx_free
r_void
id|snd_ice1712_akm4xxx_free
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
r_int
r_int
id|akidx
suffix:semicolon
r_if
c_cond
(paren
id|ice-&gt;akm
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|akidx
op_assign
l_int|0
suffix:semicolon
id|akidx
OL
id|ice-&gt;akm_codecs
suffix:semicolon
id|akidx
op_increment
)paren
(brace
id|akm4xxx_t
op_star
id|ak
op_assign
op_amp
id|ice-&gt;akm
(braket
id|akidx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ak-&gt;private_value
(braket
l_int|0
)braket
)paren
id|kfree
c_func
(paren
(paren
r_void
op_star
)paren
id|ak-&gt;private_value
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|ice-&gt;akm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * build AK4xxx controls&n; */
DECL|function|snd_ice1712_akm4xxx_build_controls
r_int
id|snd_ice1712_akm4xxx_build_controls
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
r_int
r_int
id|akidx
suffix:semicolon
r_int
id|err
suffix:semicolon
r_for
c_loop
(paren
id|akidx
op_assign
l_int|0
suffix:semicolon
id|akidx
OL
id|ice-&gt;akm_codecs
suffix:semicolon
id|akidx
op_increment
)paren
(brace
id|akm4xxx_t
op_star
id|ak
op_assign
op_amp
id|ice-&gt;akm
(braket
id|akidx
)braket
suffix:semicolon
id|err
op_assign
id|snd_akm4xxx_build_controls
c_func
(paren
id|ak
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_ice1712_akm4xxx_module_init
r_static
r_int
id|__init
id|alsa_ice1712_akm4xxx_module_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_ice1712_akm4xxx_module_exit
r_static
r_void
id|__exit
id|alsa_ice1712_akm4xxx_module_exit
c_func
(paren
r_void
)paren
(brace
)brace
id|module_init
c_func
(paren
id|alsa_ice1712_akm4xxx_module_init
)paren
id|module_exit
c_func
(paren
id|alsa_ice1712_akm4xxx_module_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ice1712_akm4xxx_init
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ice1712_akm4xxx_free
)paren
suffix:semicolon
DECL|variable|snd_ice1712_akm4xxx_build_controls
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ice1712_akm4xxx_build_controls
)paren
suffix:semicolon
eof
