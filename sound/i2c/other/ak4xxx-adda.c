multiline_comment|/*&n; *   ALSA driver for AK4524 / AK4528 / AK4529 / AK4355 / AK4381&n; *   AD and DA converters&n; *&n; *&t;Copyright (c) 2000-2003 Jaroslav Kysela &lt;perex@suse.cz&gt;,&n; *&t;&t;&t;&t;Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/ak4xxx-adda.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;, Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Routines for control of AK452x / AK43xx  AD/DA converters&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|snd_akm4xxx_write
r_void
id|snd_akm4xxx_write
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
id|reg
comma
r_int
r_char
id|val
)paren
(brace
id|ak-&gt;ops
dot
id|lock
c_func
(paren
id|ak
comma
id|chip
)paren
suffix:semicolon
id|ak-&gt;ops
dot
id|write
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|val
)paren
suffix:semicolon
multiline_comment|/* save the data */
r_if
c_cond
(paren
id|ak-&gt;type
op_eq
id|SND_AK4524
op_logical_or
id|ak-&gt;type
op_eq
id|SND_AK4528
)paren
(brace
r_if
c_cond
(paren
(paren
id|reg
op_ne
l_int|0x04
op_logical_and
id|reg
op_ne
l_int|0x05
)paren
op_logical_or
(paren
id|reg
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
id|snd_akm4xxx_set
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|val
)paren
suffix:semicolon
r_else
id|snd_akm4xxx_set_ipga
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* AK4529, or else */
id|snd_akm4xxx_set
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
id|ak-&gt;ops
dot
id|unlock
c_func
(paren
id|ak
comma
id|chip
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * reset the AKM codecs&n; * @state: 1 = reset codec, 0 = restore the registers&n; *&n; * assert the reset operation and restores the register values to the chips.&n; */
DECL|function|snd_akm4xxx_reset
r_void
id|snd_akm4xxx_reset
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
id|state
)paren
(brace
r_int
r_int
id|chip
suffix:semicolon
r_int
r_char
id|reg
suffix:semicolon
r_switch
c_cond
(paren
id|ak-&gt;type
)paren
(brace
r_case
id|SND_AK4524
suffix:colon
r_case
id|SND_AK4528
suffix:colon
r_for
c_loop
(paren
id|chip
op_assign
l_int|0
suffix:semicolon
id|chip
OL
id|ak-&gt;num_dacs
op_div
l_int|2
suffix:semicolon
id|chip
op_increment
)paren
(brace
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
l_int|0x01
comma
id|state
ques
c_cond
l_int|0x00
suffix:colon
l_int|0x03
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
r_continue
suffix:semicolon
multiline_comment|/* DAC volumes */
r_for
c_loop
(paren
id|reg
op_assign
l_int|0x04
suffix:semicolon
id|reg
OL
(paren
id|ak-&gt;type
op_eq
id|SND_AK4528
ques
c_cond
l_int|0x06
suffix:colon
l_int|0x08
)paren
suffix:semicolon
id|reg
op_increment
)paren
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ak-&gt;type
op_eq
id|SND_AK4528
)paren
r_continue
suffix:semicolon
multiline_comment|/* IPGA */
r_for
c_loop
(paren
id|reg
op_assign
l_int|0x04
suffix:semicolon
id|reg
OL
l_int|0x06
suffix:semicolon
id|reg
op_increment
)paren
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|snd_akm4xxx_get_ipga
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SND_AK4529
suffix:colon
multiline_comment|/* FIXME: needed for ak4529? */
r_break
suffix:semicolon
r_case
id|SND_AK4355
suffix:colon
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
l_int|0
comma
l_int|0x01
comma
id|state
ques
c_cond
l_int|0x02
suffix:colon
l_int|0x01
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|reg
op_assign
l_int|0x00
suffix:semicolon
id|reg
OL
l_int|0x0a
suffix:semicolon
id|reg
op_increment
)paren
r_if
c_cond
(paren
id|reg
op_ne
l_int|0x01
)paren
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
l_int|0
comma
id|reg
comma
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
l_int|0
comma
id|reg
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_AK4381
suffix:colon
r_for
c_loop
(paren
id|chip
op_assign
l_int|0
suffix:semicolon
id|chip
OL
id|ak-&gt;num_dacs
op_div
l_int|2
suffix:semicolon
id|chip
op_increment
)paren
(brace
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
l_int|0x00
comma
id|state
ques
c_cond
l_int|0x0c
suffix:colon
l_int|0x0f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|reg
op_assign
l_int|0x01
suffix:semicolon
id|reg
OL
l_int|0x05
suffix:semicolon
id|reg
op_increment
)paren
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * initialize all the ak4xxx chips&n; */
DECL|function|snd_akm4xxx_init
r_void
id|snd_akm4xxx_init
c_func
(paren
id|akm4xxx_t
op_star
id|ak
)paren
(brace
r_static
r_int
r_char
id|inits_ak4524
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x07
comma
multiline_comment|/* 0: all power up */
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* 1: ADC/DAC reset */
l_int|0x02
comma
l_int|0x60
comma
multiline_comment|/* 2: 24bit I2S */
l_int|0x03
comma
l_int|0x19
comma
multiline_comment|/* 3: deemphasis off */
l_int|0x01
comma
l_int|0x03
comma
multiline_comment|/* 1: ADC/DAC enable */
l_int|0x04
comma
l_int|0x00
comma
multiline_comment|/* 4: ADC left muted */
l_int|0x05
comma
l_int|0x00
comma
multiline_comment|/* 5: ADC right muted */
l_int|0x04
comma
l_int|0x80
comma
multiline_comment|/* 4: ADC IPGA gain 0dB */
l_int|0x05
comma
l_int|0x80
comma
multiline_comment|/* 5: ADC IPGA gain 0dB */
l_int|0x06
comma
l_int|0x00
comma
multiline_comment|/* 6: DAC left muted */
l_int|0x07
comma
l_int|0x00
comma
multiline_comment|/* 7: DAC right muted */
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_static
r_int
r_char
id|inits_ak4528
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x07
comma
multiline_comment|/* 0: all power up */
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* 1: ADC/DAC reset */
l_int|0x02
comma
l_int|0x60
comma
multiline_comment|/* 2: 24bit I2S */
l_int|0x03
comma
l_int|0x0d
comma
multiline_comment|/* 3: deemphasis off, turn LR highpass filters on */
l_int|0x01
comma
l_int|0x03
comma
multiline_comment|/* 1: ADC/DAC enable */
l_int|0x04
comma
l_int|0x00
comma
multiline_comment|/* 4: ADC left muted */
l_int|0x05
comma
l_int|0x00
comma
multiline_comment|/* 5: ADC right muted */
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_static
r_int
r_char
id|inits_ak4529
(braket
)braket
op_assign
(brace
l_int|0x09
comma
l_int|0x01
comma
multiline_comment|/* 9: ATS=0, RSTN=1 */
l_int|0x0a
comma
l_int|0x3f
comma
multiline_comment|/* A: all power up, no zero/overflow detection */
l_int|0x00
comma
l_int|0x0c
comma
multiline_comment|/* 0: TDM=0, 24bit I2S, SMUTE=0 */
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* 1: ACKS=0, ADC, loop off */
l_int|0x02
comma
l_int|0xff
comma
multiline_comment|/* 2: LOUT1 muted */
l_int|0x03
comma
l_int|0xff
comma
multiline_comment|/* 3: ROUT1 muted */
l_int|0x04
comma
l_int|0xff
comma
multiline_comment|/* 4: LOUT2 muted */
l_int|0x05
comma
l_int|0xff
comma
multiline_comment|/* 5: ROUT2 muted */
l_int|0x06
comma
l_int|0xff
comma
multiline_comment|/* 6: LOUT3 muted */
l_int|0x07
comma
l_int|0xff
comma
multiline_comment|/* 7: ROUT3 muted */
l_int|0x0b
comma
l_int|0xff
comma
multiline_comment|/* B: LOUT4 muted */
l_int|0x0c
comma
l_int|0xff
comma
multiline_comment|/* C: ROUT4 muted */
l_int|0x08
comma
l_int|0x55
comma
multiline_comment|/* 8: deemphasis all off */
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_static
r_int
r_char
id|inits_ak4355
(braket
)braket
op_assign
(brace
l_int|0x01
comma
l_int|0x02
comma
multiline_comment|/* 1: reset and soft-mute */
l_int|0x00
comma
l_int|0x06
comma
multiline_comment|/* 0: mode3(i2s), disable auto-clock detect, disable DZF, sharp roll-off, RSTN#=0 */
singleline_comment|// 0x02, 0x0e, /* 2: DA&squot;s power up, normal speed, RSTN#=0 */
l_int|0x02
comma
l_int|0x2e
comma
l_int|0x03
comma
l_int|0x01
comma
multiline_comment|/* 3: de-emphasis off */
l_int|0x04
comma
l_int|0x00
comma
multiline_comment|/* 4: LOUT1 volume muted */
l_int|0x05
comma
l_int|0x00
comma
multiline_comment|/* 5: ROUT1 volume muted */
l_int|0x06
comma
l_int|0x00
comma
multiline_comment|/* 6: LOUT2 volume muted */
l_int|0x07
comma
l_int|0x00
comma
multiline_comment|/* 7: ROUT2 volume muted */
l_int|0x08
comma
l_int|0x00
comma
multiline_comment|/* 8: LOUT3 volume muted */
l_int|0x09
comma
l_int|0x00
comma
multiline_comment|/* 9: ROUT3 volume muted */
l_int|0x0a
comma
l_int|0x00
comma
multiline_comment|/* a: DATT speed=0, ignore DZF */
l_int|0x01
comma
l_int|0x01
comma
multiline_comment|/* 1: un-reset, unmute */
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_static
r_int
r_char
id|inits_ak4381
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x0c
comma
multiline_comment|/* 0: mode3(i2s), disable auto-clock detect */
singleline_comment|// 0x01, 0x02, /* 1: de-emphasis off, normal speed, sharp roll-off, DZF off */
l_int|0x01
comma
l_int|0x12
comma
l_int|0x02
comma
l_int|0x00
comma
multiline_comment|/* 2: DZF disabled */
l_int|0x03
comma
l_int|0x00
comma
multiline_comment|/* 3: LATT 0 */
l_int|0x04
comma
l_int|0x00
comma
multiline_comment|/* 4: RATT 0 */
l_int|0x00
comma
l_int|0x0f
comma
multiline_comment|/* 0: power-up, un-reset */
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
r_int
id|chip
comma
id|num_chips
suffix:semicolon
r_int
r_char
op_star
id|ptr
comma
id|reg
comma
id|data
comma
op_star
id|inits
suffix:semicolon
r_switch
c_cond
(paren
id|ak-&gt;type
)paren
(brace
r_case
id|SND_AK4524
suffix:colon
id|inits
op_assign
id|inits_ak4524
suffix:semicolon
id|num_chips
op_assign
id|ak-&gt;num_dacs
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_AK4528
suffix:colon
id|inits
op_assign
id|inits_ak4528
suffix:semicolon
id|num_chips
op_assign
id|ak-&gt;num_dacs
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_AK4529
suffix:colon
id|inits
op_assign
id|inits_ak4529
suffix:semicolon
id|num_chips
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_AK4355
suffix:colon
id|inits
op_assign
id|inits_ak4355
suffix:semicolon
id|num_chips
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_AK4381
suffix:colon
id|inits
op_assign
id|inits_ak4381
suffix:semicolon
id|num_chips
op_assign
id|ak-&gt;num_dacs
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|snd_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|chip
op_assign
l_int|0
suffix:semicolon
id|chip
OL
id|num_chips
suffix:semicolon
id|chip
op_increment
)paren
(brace
id|ptr
op_assign
id|inits
suffix:semicolon
r_while
c_loop
(paren
op_star
id|ptr
op_ne
l_int|0xff
)paren
(brace
id|reg
op_assign
op_star
id|ptr
op_increment
suffix:semicolon
id|data
op_assign
op_star
id|ptr
op_increment
suffix:semicolon
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
id|reg
comma
id|data
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|macro|AK_GET_CHIP
mdefine_line|#define AK_GET_CHIP(val)&t;&t;(((val) &gt;&gt; 8) &amp; 0xff)
DECL|macro|AK_GET_ADDR
mdefine_line|#define AK_GET_ADDR(val)&t;&t;((val) &amp; 0xff)
DECL|macro|AK_GET_SHIFT
mdefine_line|#define AK_GET_SHIFT(val)&t;&t;(((val) &gt;&gt; 16) &amp; 0x7f)
DECL|macro|AK_GET_INVERT
mdefine_line|#define AK_GET_INVERT(val)&t;&t;(((val) &gt;&gt; 23) &amp; 1)
DECL|macro|AK_GET_MASK
mdefine_line|#define AK_GET_MASK(val)&t;&t;(((val) &gt;&gt; 24) &amp; 0xff)
DECL|macro|AK_COMPOSE
mdefine_line|#define AK_COMPOSE(chip,addr,shift,mask) (((chip) &lt;&lt; 8) | (addr) | ((shift) &lt;&lt; 16) | ((mask) &lt;&lt; 24))
DECL|macro|AK_INVERT
mdefine_line|#define AK_INVERT &t;&t;&t;(1&lt;&lt;23)
DECL|function|snd_akm4xxx_volume_info
r_static
r_int
id|snd_akm4xxx_volume_info
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
r_int
r_int
id|mask
op_assign
id|AK_GET_MASK
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_INTEGER
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
id|mask
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_volume_get
r_static
r_int
id|snd_akm4xxx_volume_get
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
id|akm4xxx_t
op_star
id|ak
op_assign
id|_snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|chip
op_assign
id|AK_GET_CHIP
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|addr
op_assign
id|AK_GET_ADDR
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|invert
op_assign
id|AK_GET_INVERT
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|AK_GET_MASK
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
r_char
id|val
op_assign
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|invert
ques
c_cond
id|mask
op_minus
id|val
suffix:colon
id|val
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_volume_put
r_static
r_int
id|snd_akm4xxx_volume_put
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
id|akm4xxx_t
op_star
id|ak
op_assign
id|_snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|chip
op_assign
id|AK_GET_CHIP
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|addr
op_assign
id|AK_GET_ADDR
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|invert
op_assign
id|AK_GET_INVERT
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|AK_GET_MASK
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
r_char
id|nval
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_mod
(paren
id|mask
op_plus
l_int|1
)paren
suffix:semicolon
r_int
id|change
suffix:semicolon
r_if
c_cond
(paren
id|invert
)paren
id|nval
op_assign
id|mask
op_minus
id|nval
suffix:semicolon
id|change
op_assign
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
)paren
op_ne
id|nval
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
comma
id|nval
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_ipga_gain_info
r_static
r_int
id|snd_akm4xxx_ipga_gain_info
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
l_int|1
suffix:semicolon
id|uinfo-&gt;value.integer.min
op_assign
l_int|0
suffix:semicolon
id|uinfo-&gt;value.integer.max
op_assign
l_int|36
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_ipga_gain_get
r_static
r_int
id|snd_akm4xxx_ipga_gain_get
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
id|akm4xxx_t
op_star
id|ak
op_assign
id|_snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|chip
op_assign
id|AK_GET_CHIP
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|addr
op_assign
id|AK_GET_ADDR
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|snd_akm4xxx_get_ipga
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
)paren
op_amp
l_int|0x7f
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_ipga_gain_put
r_static
r_int
id|snd_akm4xxx_ipga_gain_put
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
id|akm4xxx_t
op_star
id|ak
op_assign
id|_snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|chip
op_assign
id|AK_GET_CHIP
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|addr
op_assign
id|AK_GET_ADDR
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
r_char
id|nval
op_assign
(paren
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_mod
l_int|37
)paren
op_or
l_int|0x80
suffix:semicolon
r_int
id|change
op_assign
id|snd_akm4xxx_get_ipga
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
)paren
op_ne
id|nval
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
comma
id|nval
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_deemphasis_info
r_static
r_int
id|snd_akm4xxx_deemphasis_info
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
r_static
r_char
op_star
id|texts
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;44.1kHz&quot;
comma
l_string|&quot;Off&quot;
comma
l_string|&quot;48kHz&quot;
comma
l_string|&quot;32kHz&quot;
comma
)brace
suffix:semicolon
id|uinfo-&gt;type
op_assign
id|SNDRV_CTL_ELEM_TYPE_ENUMERATED
suffix:semicolon
id|uinfo-&gt;count
op_assign
l_int|1
suffix:semicolon
id|uinfo-&gt;value.enumerated.items
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|uinfo-&gt;value.enumerated.item
op_ge
l_int|4
)paren
id|uinfo-&gt;value.enumerated.item
op_assign
l_int|3
suffix:semicolon
id|strcpy
c_func
(paren
id|uinfo-&gt;value.enumerated.name
comma
id|texts
(braket
id|uinfo-&gt;value.enumerated.item
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_deemphasis_get
r_static
r_int
id|snd_akm4xxx_deemphasis_get
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
id|akm4xxx_t
op_star
id|ak
op_assign
id|_snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|chip
op_assign
id|AK_GET_CHIP
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|addr
op_assign
id|AK_GET_ADDR
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|shift
op_assign
id|AK_GET_SHIFT
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_assign
(paren
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
)paren
op_rshift
id|shift
)paren
op_amp
l_int|3
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_akm4xxx_deemphasis_put
r_static
r_int
id|snd_akm4xxx_deemphasis_put
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
id|akm4xxx_t
op_star
id|ak
op_assign
id|_snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|chip
op_assign
id|AK_GET_CHIP
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|addr
op_assign
id|AK_GET_ADDR
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
id|shift
op_assign
id|AK_GET_SHIFT
c_func
(paren
id|kcontrol-&gt;private_value
)paren
suffix:semicolon
r_int
r_char
id|nval
op_assign
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_amp
l_int|3
suffix:semicolon
r_int
id|change
suffix:semicolon
id|nval
op_assign
(paren
id|nval
op_lshift
id|shift
)paren
op_or
(paren
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
)paren
op_amp
op_complement
(paren
l_int|3
op_lshift
id|shift
)paren
)paren
suffix:semicolon
id|change
op_assign
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
)paren
op_ne
id|nval
suffix:semicolon
r_if
c_cond
(paren
id|change
)paren
id|snd_akm4xxx_write
c_func
(paren
id|ak
comma
id|chip
comma
id|addr
comma
id|nval
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
multiline_comment|/*&n; * build AK4xxx controls&n; */
DECL|function|snd_akm4xxx_build_controls
r_int
id|snd_akm4xxx_build_controls
c_func
(paren
id|akm4xxx_t
op_star
id|ak
)paren
(brace
r_int
r_int
id|idx
suffix:semicolon
r_int
id|err
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|ak-&gt;num_dacs
suffix:semicolon
op_increment
id|idx
)paren
(brace
id|snd_kcontrol_t
id|ctl
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ctl
comma
l_int|0
comma
r_sizeof
(paren
id|ctl
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ctl.id.name
comma
l_string|&quot;DAC Volume&quot;
)paren
suffix:semicolon
id|ctl.id.index
op_assign
id|idx
op_plus
id|ak-&gt;idx_offset
op_star
l_int|2
suffix:semicolon
id|ctl.id.iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
suffix:semicolon
id|ctl.count
op_assign
l_int|1
suffix:semicolon
id|ctl.info
op_assign
id|snd_akm4xxx_volume_info
suffix:semicolon
id|ctl.get
op_assign
id|snd_akm4xxx_volume_get
suffix:semicolon
id|ctl.put
op_assign
id|snd_akm4xxx_volume_put
suffix:semicolon
r_switch
c_cond
(paren
id|ak-&gt;type
)paren
(brace
r_case
id|SND_AK4524
suffix:colon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
op_div
l_int|2
comma
(paren
id|idx
op_mod
l_int|2
)paren
op_plus
l_int|6
comma
l_int|0
comma
l_int|127
)paren
suffix:semicolon
multiline_comment|/* register 6 &amp; 7 */
r_break
suffix:semicolon
r_case
id|SND_AK4528
suffix:colon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
op_div
l_int|2
comma
(paren
id|idx
op_mod
l_int|2
)paren
op_plus
l_int|4
comma
l_int|0
comma
l_int|127
)paren
suffix:semicolon
multiline_comment|/* register 4 &amp; 5 */
r_break
suffix:semicolon
r_case
id|SND_AK4529
suffix:colon
(brace
r_int
id|val
op_assign
id|idx
OL
l_int|6
ques
c_cond
id|idx
op_plus
l_int|2
suffix:colon
(paren
id|idx
op_minus
l_int|6
)paren
op_plus
l_int|0xb
suffix:semicolon
multiline_comment|/* registers 2-7 and b,c */
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
l_int|0
comma
id|val
comma
l_int|0
comma
l_int|255
)paren
op_or
id|AK_INVERT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|SND_AK4355
suffix:colon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
l_int|0
comma
id|idx
op_plus
l_int|4
comma
l_int|0
comma
l_int|255
)paren
suffix:semicolon
multiline_comment|/* register 4-9, chip #0 only */
r_break
suffix:semicolon
r_case
id|SND_AK4381
suffix:colon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
op_div
l_int|2
comma
(paren
id|idx
op_mod
l_int|2
)paren
op_plus
l_int|3
comma
l_int|0
comma
l_int|255
)paren
suffix:semicolon
multiline_comment|/* register 3 &amp; 4 */
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|ctl.private_data
op_assign
id|ak
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|ak-&gt;card
comma
id|snd_ctl_new
c_func
(paren
op_amp
id|ctl
comma
id|SNDRV_CTL_ELEM_ACCESS_READ
op_or
id|SNDRV_CTL_ELEM_ACCESS_WRITE
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
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|ak-&gt;num_adcs
op_logical_and
id|ak-&gt;type
op_eq
id|SND_AK4524
suffix:semicolon
op_increment
id|idx
)paren
(brace
id|snd_kcontrol_t
id|ctl
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ctl
comma
l_int|0
comma
r_sizeof
(paren
id|ctl
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ctl.id.name
comma
l_string|&quot;ADC Volume&quot;
)paren
suffix:semicolon
id|ctl.id.index
op_assign
id|idx
suffix:semicolon
id|ctl.id.iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
suffix:semicolon
id|ctl.count
op_assign
l_int|1
suffix:semicolon
id|ctl.info
op_assign
id|snd_akm4xxx_volume_info
suffix:semicolon
id|ctl.get
op_assign
id|snd_akm4xxx_volume_get
suffix:semicolon
id|ctl.put
op_assign
id|snd_akm4xxx_volume_put
suffix:semicolon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
op_div
l_int|2
comma
(paren
id|idx
op_mod
l_int|2
)paren
op_plus
l_int|4
comma
l_int|0
comma
l_int|127
)paren
suffix:semicolon
multiline_comment|/* register 4 &amp; 5 */
id|ctl.private_data
op_assign
id|ak
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|ak-&gt;card
comma
id|snd_ctl_new
c_func
(paren
op_amp
id|ctl
comma
id|SNDRV_CTL_ELEM_ACCESS_READ
op_or
id|SNDRV_CTL_ELEM_ACCESS_WRITE
)paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ctl
comma
l_int|0
comma
r_sizeof
(paren
id|ctl
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ctl.id.name
comma
l_string|&quot;IPGA Analog Capture Volume&quot;
)paren
suffix:semicolon
id|ctl.id.index
op_assign
id|idx
suffix:semicolon
id|ctl.id.iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
suffix:semicolon
id|ctl.count
op_assign
l_int|1
suffix:semicolon
id|ctl.info
op_assign
id|snd_akm4xxx_ipga_gain_info
suffix:semicolon
id|ctl.get
op_assign
id|snd_akm4xxx_ipga_gain_get
suffix:semicolon
id|ctl.put
op_assign
id|snd_akm4xxx_ipga_gain_put
suffix:semicolon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
op_div
l_int|2
comma
(paren
id|idx
op_mod
l_int|2
)paren
op_plus
l_int|4
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* register 4 &amp; 5 */
id|ctl.private_data
op_assign
id|ak
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|ak-&gt;card
comma
id|snd_ctl_new
c_func
(paren
op_amp
id|ctl
comma
id|SNDRV_CTL_ELEM_ACCESS_READ
op_or
id|SNDRV_CTL_ELEM_ACCESS_WRITE
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
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|ak-&gt;num_dacs
op_div
l_int|2
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|snd_kcontrol_t
id|ctl
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ctl
comma
l_int|0
comma
r_sizeof
(paren
id|ctl
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|ctl.id.name
comma
l_string|&quot;Deemphasis&quot;
)paren
suffix:semicolon
id|ctl.id.index
op_assign
id|idx
op_plus
id|ak-&gt;idx_offset
suffix:semicolon
id|ctl.id.iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
suffix:semicolon
id|ctl.count
op_assign
l_int|1
suffix:semicolon
id|ctl.info
op_assign
id|snd_akm4xxx_deemphasis_info
suffix:semicolon
id|ctl.get
op_assign
id|snd_akm4xxx_deemphasis_get
suffix:semicolon
id|ctl.put
op_assign
id|snd_akm4xxx_deemphasis_put
suffix:semicolon
r_switch
c_cond
(paren
id|ak-&gt;type
)paren
(brace
r_case
id|SND_AK4524
suffix:colon
r_case
id|SND_AK4528
suffix:colon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
comma
l_int|3
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* register 3 */
r_break
suffix:semicolon
r_case
id|SND_AK4529
suffix:colon
(brace
r_int
id|shift
op_assign
id|idx
op_eq
l_int|3
ques
c_cond
l_int|6
suffix:colon
(paren
l_int|2
op_minus
id|idx
)paren
op_star
l_int|2
suffix:semicolon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
l_int|0
comma
l_int|8
comma
id|shift
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* register 8 with shift */
r_break
suffix:semicolon
)brace
r_case
id|SND_AK4355
suffix:colon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
comma
l_int|3
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_AK4381
suffix:colon
id|ctl.private_value
op_assign
id|AK_COMPOSE
c_func
(paren
id|idx
comma
l_int|1
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ctl.private_data
op_assign
id|ak
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_add
c_func
(paren
id|ak-&gt;card
comma
id|snd_ctl_new
c_func
(paren
op_amp
id|ctl
comma
id|SNDRV_CTL_ELEM_ACCESS_READ
op_or
id|SNDRV_CTL_ELEM_ACCESS_WRITE
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_akm4xxx_write
id|EXPORT_SYMBOL
c_func
(paren
id|snd_akm4xxx_write
)paren
suffix:semicolon
DECL|variable|snd_akm4xxx_reset
id|EXPORT_SYMBOL
c_func
(paren
id|snd_akm4xxx_reset
)paren
suffix:semicolon
DECL|variable|snd_akm4xxx_init
id|EXPORT_SYMBOL
c_func
(paren
id|snd_akm4xxx_init
)paren
suffix:semicolon
DECL|variable|snd_akm4xxx_build_controls
id|EXPORT_SYMBOL
c_func
(paren
id|snd_akm4xxx_build_controls
)paren
suffix:semicolon
eof
