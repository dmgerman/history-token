multiline_comment|/*&n; *   ALSA driver for ICEnsemble ICE1712 (Envy24)&n; *&n; *   Lowlevel functions for M-Audio Revolution 7.1&n; *&n; *&t;Copyright (c) 2003 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;ice1712.h&quot;
macro_line|#include &quot;envy24ht.h&quot;
macro_line|#include &quot;revo.h&quot;
multiline_comment|/*&n; * change the rate of envy24HT, AK4355 and AK4381&n; */
DECL|function|revo_set_rate_val
r_static
r_void
id|revo_set_rate_val
c_func
(paren
id|akm4xxx_t
op_star
id|ak
comma
r_int
r_int
id|rate
)paren
(brace
r_int
r_char
id|old
comma
id|tmp
comma
id|dfs
suffix:semicolon
r_int
id|reg
comma
id|shift
suffix:semicolon
r_if
c_cond
(paren
id|rate
op_eq
l_int|0
)paren
multiline_comment|/* no hint - S/PDIF input is master, simply return */
r_return
suffix:semicolon
multiline_comment|/* adjust DFS on codecs */
r_if
c_cond
(paren
id|rate
OG
l_int|96000
)paren
id|dfs
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
id|rate
OG
l_int|48000
)paren
id|dfs
op_assign
l_int|1
suffix:semicolon
r_else
id|dfs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ak-&gt;type
op_eq
id|SND_AK4355
)paren
(brace
id|reg
op_assign
l_int|2
suffix:semicolon
id|shift
op_assign
l_int|4
suffix:semicolon
)brace
r_else
(brace
id|reg
op_assign
l_int|1
suffix:semicolon
id|shift
op_assign
l_int|3
suffix:semicolon
)brace
id|tmp
op_assign
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
l_int|0
comma
id|reg
)paren
suffix:semicolon
id|old
op_assign
(paren
id|tmp
op_rshift
id|shift
)paren
op_amp
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
id|old
op_eq
id|dfs
)paren
r_return
suffix:semicolon
multiline_comment|/* reset DFS */
id|snd_akm4xxx_reset
c_func
(paren
id|ak
comma
l_int|1
)paren
suffix:semicolon
id|tmp
op_assign
id|snd_akm4xxx_get
c_func
(paren
id|ak
comma
l_int|0
comma
id|reg
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
l_int|0x03
op_lshift
id|shift
)paren
suffix:semicolon
id|tmp
op_or_assign
id|dfs
op_lshift
id|shift
suffix:semicolon
singleline_comment|// snd_akm4xxx_write(ak, 0, reg, tmp);
id|snd_akm4xxx_set
c_func
(paren
id|ak
comma
l_int|0
comma
id|reg
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* the value is written in reset(0) */
id|snd_akm4xxx_reset
c_func
(paren
id|ak
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * initialize the chips on M-Audio Revolution cards&n; */
DECL|variable|__devinitdata
r_static
id|akm4xxx_t
id|akm_revo_front
id|__devinitdata
op_assign
(brace
dot
id|type
op_assign
id|SND_AK4381
comma
dot
id|num_dacs
op_assign
l_int|2
comma
dot
id|ops
op_assign
(brace
dot
id|set_rate_val
op_assign
id|revo_set_rate_val
)brace
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|snd_ak4xxx_private
id|akm_revo_front_priv
id|__devinitdata
op_assign
(brace
dot
id|caddr
op_assign
l_int|1
comma
dot
id|cif
op_assign
l_int|0
comma
dot
id|data_mask
op_assign
id|VT1724_REVO_CDOUT
comma
dot
id|clk_mask
op_assign
id|VT1724_REVO_CCLK
comma
dot
id|cs_mask
op_assign
id|VT1724_REVO_CS0
op_or
id|VT1724_REVO_CS1
op_or
id|VT1724_REVO_CS2
comma
dot
id|cs_addr
op_assign
id|VT1724_REVO_CS0
op_or
id|VT1724_REVO_CS2
comma
dot
id|cs_none
op_assign
id|VT1724_REVO_CS0
op_or
id|VT1724_REVO_CS1
op_or
id|VT1724_REVO_CS2
comma
dot
id|add_flags
op_assign
id|VT1724_REVO_CCLK
comma
multiline_comment|/* high at init */
dot
id|mask_flags
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|akm4xxx_t
id|akm_revo_surround
id|__devinitdata
op_assign
(brace
dot
id|type
op_assign
id|SND_AK4355
comma
dot
id|idx_offset
op_assign
l_int|1
comma
dot
id|num_dacs
op_assign
l_int|6
comma
dot
id|ops
op_assign
(brace
dot
id|set_rate_val
op_assign
id|revo_set_rate_val
)brace
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|snd_ak4xxx_private
id|akm_revo_surround_priv
id|__devinitdata
op_assign
(brace
dot
id|caddr
op_assign
l_int|3
comma
dot
id|cif
op_assign
l_int|0
comma
dot
id|data_mask
op_assign
id|VT1724_REVO_CDOUT
comma
dot
id|clk_mask
op_assign
id|VT1724_REVO_CCLK
comma
dot
id|cs_mask
op_assign
id|VT1724_REVO_CS0
op_or
id|VT1724_REVO_CS1
op_or
id|VT1724_REVO_CS2
comma
dot
id|cs_addr
op_assign
id|VT1724_REVO_CS0
op_or
id|VT1724_REVO_CS1
comma
dot
id|cs_none
op_assign
id|VT1724_REVO_CS0
op_or
id|VT1724_REVO_CS1
op_or
id|VT1724_REVO_CS2
comma
dot
id|add_flags
op_assign
id|VT1724_REVO_CCLK
comma
multiline_comment|/* high at init */
dot
id|mask_flags
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|function|revo_init
r_static
r_int
id|__devinit
id|revo_init
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
id|akm4xxx_t
op_star
id|ak
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* determine I2C, DACs and ADCs */
r_switch
c_cond
(paren
id|ice-&gt;eeprom.subvendor
)paren
(brace
r_case
id|VT1724_SUBDEVICE_REVOLUTION71
suffix:colon
id|ice-&gt;num_total_dacs
op_assign
l_int|8
suffix:semicolon
id|ice-&gt;num_total_adcs
op_assign
l_int|4
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
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* second stage of initialization, analog parts and others */
id|ak
op_assign
id|ice-&gt;akm
op_assign
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|akm4xxx_t
)paren
op_star
l_int|2
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ak
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|ice-&gt;akm_codecs
op_assign
l_int|2
suffix:semicolon
r_switch
c_cond
(paren
id|ice-&gt;eeprom.subvendor
)paren
(brace
r_case
id|VT1724_SUBDEVICE_REVOLUTION71
suffix:colon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ice1712_akm4xxx_init
c_func
(paren
id|ak
comma
op_amp
id|akm_revo_front
comma
op_amp
id|akm_revo_front_priv
comma
id|ice
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ice1712_akm4xxx_init
c_func
(paren
id|ak
op_plus
l_int|1
comma
op_amp
id|akm_revo_surround
comma
op_amp
id|akm_revo_surround_priv
comma
id|ice
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* unmute all codecs */
id|snd_ice1712_gpio_write_bits
c_func
(paren
id|ice
comma
id|VT1724_REVO_MUTE
comma
id|VT1724_REVO_MUTE
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|revo_add_controls
r_static
r_int
id|__devinit
id|revo_add_controls
c_func
(paren
id|ice1712_t
op_star
id|ice
)paren
(brace
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|ice-&gt;eeprom.subvendor
)paren
(brace
r_case
id|VT1724_SUBDEVICE_REVOLUTION71
suffix:colon
id|err
op_assign
id|snd_ice1712_akm4xxx_build_controls
c_func
(paren
id|ice
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
multiline_comment|/* entry point */
DECL|variable|__devinitdata
r_struct
id|snd_ice1712_card_info
id|snd_vt1724_revo_cards
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
dot
id|subvendor
op_assign
id|VT1724_SUBDEVICE_REVOLUTION71
comma
dot
id|name
op_assign
l_string|&quot;M Audio Revolution-7.1&quot;
comma
dot
id|model
op_assign
l_string|&quot;revo71&quot;
comma
dot
id|chip_init
op_assign
id|revo_init
comma
dot
id|build_controls
op_assign
id|revo_add_controls
comma
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
eof
