multiline_comment|/*&n; * PMac DACA lowlevel functions&n; *&n; * Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-dev.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;pmac.h&quot;
multiline_comment|/* i2c address */
DECL|macro|DACA_I2C_ADDR
mdefine_line|#define DACA_I2C_ADDR&t;0x4d
multiline_comment|/* registers */
DECL|macro|DACA_REG_SR
mdefine_line|#define DACA_REG_SR&t;0x01
DECL|macro|DACA_REG_AVOL
mdefine_line|#define DACA_REG_AVOL&t;0x02
DECL|macro|DACA_REG_GCFG
mdefine_line|#define DACA_REG_GCFG&t;0x03
multiline_comment|/* maximum volume value */
DECL|macro|DACA_VOL_MAX
mdefine_line|#define DACA_VOL_MAX&t;0x38
DECL|struct|pmac_daca_t
r_typedef
r_struct
id|pmac_daca_t
(brace
DECL|member|i2c
id|pmac_keywest_t
id|i2c
suffix:semicolon
DECL|member|left_vol
DECL|member|right_vol
r_int
id|left_vol
comma
id|right_vol
suffix:semicolon
DECL|member|deemphasis
r_int
r_int
id|deemphasis
suffix:colon
l_int|1
suffix:semicolon
DECL|member|amp_on
r_int
r_int
id|amp_on
suffix:colon
l_int|1
suffix:semicolon
DECL|typedef|pmac_daca_t
)brace
id|pmac_daca_t
suffix:semicolon
multiline_comment|/*&n; * initialize / detect DACA&n; */
DECL|function|daca_init_client
r_static
r_int
id|daca_init_client
c_func
(paren
id|pmac_keywest_t
op_star
id|i2c
)paren
(brace
r_int
r_int
id|wdata
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* SR: no swap, 1bit delay, 32-48kHz */
multiline_comment|/* GCFG: power amp inverted, DAC on */
r_if
c_cond
(paren
id|i2c_smbus_write_byte_data
c_func
(paren
id|i2c-&gt;client
comma
id|DACA_REG_SR
comma
l_int|0x08
)paren
OL
l_int|0
op_logical_or
id|i2c_smbus_write_byte_data
c_func
(paren
id|i2c-&gt;client
comma
id|DACA_REG_GCFG
comma
l_int|0x05
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|i2c_smbus_write_block_data
c_func
(paren
id|i2c-&gt;client
comma
id|DACA_REG_AVOL
comma
l_int|2
comma
(paren
r_int
r_char
op_star
)paren
op_amp
id|wdata
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * update volume&n; */
DECL|function|daca_set_volume
r_static
r_int
id|daca_set_volume
c_func
(paren
id|pmac_daca_t
op_star
id|mix
)paren
(brace
r_int
r_char
id|data
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mix-&gt;i2c.client
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|mix-&gt;left_vol
OG
id|DACA_VOL_MAX
)paren
id|data
(braket
l_int|0
)braket
op_assign
id|DACA_VOL_MAX
suffix:semicolon
r_else
id|data
(braket
l_int|0
)braket
op_assign
id|mix-&gt;left_vol
suffix:semicolon
r_if
c_cond
(paren
id|mix-&gt;right_vol
OG
id|DACA_VOL_MAX
)paren
id|data
(braket
l_int|1
)braket
op_assign
id|DACA_VOL_MAX
suffix:semicolon
r_else
id|data
(braket
l_int|1
)braket
op_assign
id|mix-&gt;right_vol
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_or_assign
id|mix-&gt;deemphasis
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|i2c_smbus_write_block_data
c_func
(paren
id|mix-&gt;i2c.client
comma
id|DACA_REG_AVOL
comma
l_int|2
comma
id|data
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;failed to set volume &bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* deemphasis switch */
DECL|function|daca_info_deemphasis
r_static
r_int
id|daca_info_deemphasis
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_get_deemphasis
r_static
r_int
id|daca_get_deemphasis
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|pmac_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|pmac_daca_t
op_star
id|mix
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mix
op_assign
id|chip-&gt;mixer_data
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|mix-&gt;deemphasis
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_put_deemphasis
r_static
r_int
id|daca_put_deemphasis
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|pmac_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|pmac_daca_t
op_star
id|mix
suffix:semicolon
r_int
id|change
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mix
op_assign
id|chip-&gt;mixer_data
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|change
op_assign
id|mix-&gt;deemphasis
op_ne
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
(brace
id|mix-&gt;deemphasis
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
suffix:semicolon
id|daca_set_volume
c_func
(paren
id|mix
)paren
suffix:semicolon
)brace
r_return
id|change
suffix:semicolon
)brace
multiline_comment|/* output volume */
DECL|function|daca_info_volume
r_static
r_int
id|daca_info_volume
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
(brace
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|2
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
id|DACA_VOL_MAX
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_get_volume
r_static
r_int
id|daca_get_volume
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|pmac_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|pmac_daca_t
op_star
id|mix
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mix
op_assign
id|chip-&gt;mixer_data
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|mix-&gt;left_vol
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|mix-&gt;right_vol
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_put_volume
r_static
r_int
id|daca_put_volume
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|pmac_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|pmac_daca_t
op_star
id|mix
suffix:semicolon
r_int
id|change
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mix
op_assign
id|chip-&gt;mixer_data
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|change
op_assign
id|mix-&gt;left_vol
op_ne
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_logical_or
id|mix-&gt;right_vol
op_ne
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
(brace
id|mix-&gt;left_vol
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
suffix:semicolon
id|mix-&gt;right_vol
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
suffix:semicolon
id|daca_set_volume
c_func
(paren
id|mix
)paren
suffix:semicolon
)brace
r_return
id|change
suffix:semicolon
)brace
multiline_comment|/* amplifier switch */
DECL|macro|daca_info_amp
mdefine_line|#define daca_info_amp&t;daca_info_deemphasis
DECL|function|daca_get_amp
r_static
r_int
id|daca_get_amp
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|pmac_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|pmac_daca_t
op_star
id|mix
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mix
op_assign
id|chip-&gt;mixer_data
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|mix-&gt;amp_on
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|daca_put_amp
r_static
r_int
id|daca_put_amp
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
(brace
id|pmac_t
op_star
id|chip
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
id|pmac_daca_t
op_star
id|mix
suffix:semicolon
r_int
id|change
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mix
op_assign
id|chip-&gt;mixer_data
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|change
op_assign
id|mix-&gt;amp_on
op_ne
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
(brace
id|mix-&gt;amp_on
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|mix-&gt;i2c.client
comma
id|DACA_REG_GCFG
comma
id|mix-&gt;amp_on
ques
c_cond
l_int|0x05
suffix:colon
l_int|0x04
)paren
suffix:semicolon
)brace
r_return
id|change
suffix:semicolon
)brace
DECL|variable|daca_mixers
r_static
id|snd_kcontrol_new_t
id|daca_mixers
(braket
)braket
op_assign
(brace
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;Deemphasis Switch&quot;
comma
dot
id|info
op_assign
id|daca_info_deemphasis
comma
dot
id|get
op_assign
id|daca_get_deemphasis
comma
dot
id|put
op_assign
id|daca_put_deemphasis
)brace
comma
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;Master Playback Volume&quot;
comma
dot
id|info
op_assign
id|daca_info_volume
comma
dot
id|get
op_assign
id|daca_get_volume
comma
dot
id|put
op_assign
id|daca_put_volume
)brace
comma
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
dot
id|name
op_assign
l_string|&quot;Power Amplifier Switch&quot;
comma
dot
id|info
op_assign
id|daca_info_amp
comma
dot
id|get
op_assign
id|daca_get_amp
comma
dot
id|put
op_assign
id|daca_put_amp
)brace
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PMAC_PBOOK
DECL|function|daca_resume
r_static
r_void
id|daca_resume
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
(brace
id|pmac_daca_t
op_star
id|mix
op_assign
id|chip-&gt;mixer_data
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|mix-&gt;i2c.client
comma
id|DACA_REG_SR
comma
l_int|0x08
)paren
suffix:semicolon
id|i2c_smbus_write_byte_data
c_func
(paren
id|mix-&gt;i2c.client
comma
id|DACA_REG_GCFG
comma
id|mix-&gt;amp_on
ques
c_cond
l_int|0x05
suffix:colon
l_int|0x04
)paren
suffix:semicolon
id|daca_set_volume
c_func
(paren
id|mix
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PMAC_PBOOK */
DECL|function|daca_cleanup
r_static
r_void
id|daca_cleanup
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
(brace
id|pmac_daca_t
op_star
id|mix
op_assign
id|chip-&gt;mixer_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mix
)paren
r_return
suffix:semicolon
id|snd_pmac_keywest_cleanup
c_func
(paren
op_amp
id|mix-&gt;i2c
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mix
)paren
suffix:semicolon
id|chip-&gt;mixer_data
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* exported */
DECL|function|snd_pmac_daca_init
r_int
id|__init
id|snd_pmac_daca_init
c_func
(paren
id|pmac_t
op_star
id|chip
)paren
(brace
r_int
id|i
comma
id|err
suffix:semicolon
id|pmac_daca_t
op_star
id|mix
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|current-&gt;fs-&gt;root
)paren
id|request_module
c_func
(paren
l_string|&quot;i2c-keywest&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_KMOD */&t;
id|mix
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mix
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mix
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|mix
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mix
)paren
)paren
suffix:semicolon
id|chip-&gt;mixer_data
op_assign
id|mix
suffix:semicolon
id|chip-&gt;mixer_free
op_assign
id|daca_cleanup
suffix:semicolon
id|mix-&gt;amp_on
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* default on */
id|mix-&gt;i2c.addr
op_assign
id|DACA_I2C_ADDR
suffix:semicolon
id|mix-&gt;i2c.init_client
op_assign
id|daca_init_client
suffix:semicolon
id|mix-&gt;i2c.name
op_assign
l_string|&quot;DACA&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_pmac_keywest_init
c_func
(paren
op_amp
id|mix-&gt;i2c
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * build mixers&n;&t; */
id|strcpy
c_func
(paren
id|chip-&gt;card-&gt;mixername
comma
l_string|&quot;PowerMac DACA&quot;
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
id|ARRAY_SIZE
c_func
(paren
id|daca_mixers
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|chip-&gt;card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|daca_mixers
(braket
id|i
)braket
comma
id|chip
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PMAC_PBOOK
id|chip-&gt;resume
op_assign
id|daca_resume
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
