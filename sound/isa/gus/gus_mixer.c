multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Routines for control of ICS 2101 chip and &quot;mixer&quot; in GF1 chip&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/gus.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t snd_gus_card_t
multiline_comment|/*&n; *&n; */
DECL|macro|GF1_SINGLE
mdefine_line|#define GF1_SINGLE(xname, xindex, shift, invert) &bslash;&n;{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, name: xname, index: xindex, &bslash;&n;  .info = snd_gf1_info_single, &bslash;&n;  .get = snd_gf1_get_single, put: snd_gf1_put_single, &bslash;&n;  private_value: shift | (invert &lt;&lt; 8) }
DECL|function|snd_gf1_info_single
r_static
r_int
id|snd_gf1_info_single
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
DECL|function|snd_gf1_get_single
r_static
r_int
id|snd_gf1_get_single
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
id|snd_gus_card_t
op_star
id|gus
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
id|shift
op_assign
id|kcontrol-&gt;private_value
op_amp
l_int|0xff
suffix:semicolon
r_int
id|invert
op_assign
(paren
id|kcontrol-&gt;private_value
op_rshift
l_int|8
)paren
op_amp
l_int|1
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
(paren
id|gus-&gt;mix_cntrl_reg
op_rshift
id|shift
)paren
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|invert
)paren
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_xor_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gf1_put_single
r_static
r_int
id|snd_gf1_put_single
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
id|snd_gus_card_t
op_star
id|gus
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|shift
op_assign
id|kcontrol-&gt;private_value
op_amp
l_int|0xff
suffix:semicolon
r_int
id|invert
op_assign
(paren
id|kcontrol-&gt;private_value
op_rshift
l_int|8
)paren
op_amp
l_int|1
suffix:semicolon
r_int
id|change
suffix:semicolon
r_int
r_char
id|oval
comma
id|nval
suffix:semicolon
id|nval
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_amp
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|invert
)paren
id|nval
op_xor_assign
l_int|1
suffix:semicolon
id|nval
op_lshift_assign
id|shift
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|oval
op_assign
id|gus-&gt;mix_cntrl_reg
suffix:semicolon
id|nval
op_assign
(paren
id|oval
op_amp
op_complement
(paren
l_int|1
op_lshift
id|shift
)paren
)paren
op_or
id|nval
suffix:semicolon
id|change
op_assign
id|nval
op_ne
id|oval
suffix:semicolon
id|outb
c_func
(paren
id|gus-&gt;mix_cntrl_reg
op_assign
id|nval
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXCNTRLREG
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|gus-&gt;gf1.active_voice
op_assign
l_int|0
comma
id|GUSP
c_func
(paren
id|gus
comma
id|GF1PAGE
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|macro|ICS_DOUBLE
mdefine_line|#define ICS_DOUBLE(xname, xindex, addr) &bslash;&n;{ .iface = SNDRV_CTL_ELEM_IFACE_MIXER, name: xname, index: xindex, &bslash;&n;  .info = snd_ics_info_double, &bslash;&n;  .get = snd_ics_get_double, put: snd_ics_put_double, &bslash;&n;  private_value: addr }
DECL|function|snd_ics_info_double
r_static
r_int
id|snd_ics_info_double
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
l_int|127
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_ics_get_double
r_static
r_int
id|snd_ics_get_double
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
id|snd_gus_card_t
op_star
id|gus
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|addr
op_assign
id|kcontrol-&gt;private_value
op_amp
l_int|0xff
suffix:semicolon
r_int
r_char
id|left
comma
id|right
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|left
op_assign
id|gus-&gt;gf1.ics_regs
(braket
id|addr
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|right
op_assign
id|gus-&gt;gf1.ics_regs
(braket
id|addr
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_assign
id|left
op_amp
l_int|127
suffix:semicolon
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_assign
id|right
op_amp
l_int|127
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_ics_put_double
r_static
r_int
id|snd_ics_put_double
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
id|snd_gus_card_t
op_star
id|gus
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|addr
op_assign
id|kcontrol-&gt;private_value
op_amp
l_int|0xff
suffix:semicolon
r_int
id|change
suffix:semicolon
r_int
r_char
id|val1
comma
id|val2
comma
id|oval1
comma
id|oval2
comma
id|tmp
suffix:semicolon
id|val1
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|0
)braket
op_amp
l_int|127
suffix:semicolon
id|val2
op_assign
id|ucontrol-&gt;value.integer.value
(braket
l_int|1
)braket
op_amp
l_int|127
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|oval1
op_assign
id|gus-&gt;gf1.ics_regs
(braket
id|addr
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|oval2
op_assign
id|gus-&gt;gf1.ics_regs
(braket
id|addr
)braket
(braket
l_int|1
)braket
suffix:semicolon
id|change
op_assign
id|val1
op_ne
id|oval1
op_logical_or
id|val2
op_ne
id|oval2
suffix:semicolon
id|gus-&gt;gf1.ics_regs
(braket
id|addr
)braket
(braket
l_int|0
)braket
op_assign
id|val1
suffix:semicolon
id|gus-&gt;gf1.ics_regs
(braket
id|addr
)braket
(braket
l_int|1
)braket
op_assign
id|val2
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;ics_flag
op_logical_and
id|gus-&gt;ics_flipped
op_logical_and
(paren
id|addr
op_eq
id|SNDRV_ICS_GF1_DEV
op_logical_or
id|addr
op_eq
id|SNDRV_ICS_MASTER_DEV
)paren
)paren
(brace
id|tmp
op_assign
id|val1
suffix:semicolon
id|val1
op_assign
id|val2
suffix:semicolon
id|val2
op_assign
id|tmp
suffix:semicolon
)brace
id|addr
op_lshift_assign
l_int|3
suffix:semicolon
id|outb
c_func
(paren
id|addr
op_or
l_int|0
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXCNTRLPORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|1
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXDATAPORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|addr
op_or
l_int|2
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXCNTRLPORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
r_int
r_char
)paren
id|val1
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXDATAPORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|addr
op_or
l_int|1
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXCNTRLPORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|2
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXDATAPORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|addr
op_or
l_int|3
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXCNTRLPORT
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
r_int
r_char
)paren
id|val2
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MIXDATAPORT
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|change
suffix:semicolon
)brace
DECL|macro|GF1_CONTROLS
mdefine_line|#define GF1_CONTROLS (sizeof(snd_gf1_controls)/sizeof(snd_kcontrol_new_t))
DECL|variable|snd_gf1_controls
r_static
id|snd_kcontrol_new_t
id|snd_gf1_controls
(braket
)braket
op_assign
(brace
id|GF1_SINGLE
c_func
(paren
l_string|&quot;Master Playback Switch&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|1
)paren
comma
id|GF1_SINGLE
c_func
(paren
l_string|&quot;Line Switch&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
comma
id|GF1_SINGLE
c_func
(paren
l_string|&quot;Mic Switch&quot;
comma
l_int|0
comma
l_int|2
comma
l_int|0
)paren
)brace
suffix:semicolon
DECL|macro|ICS_CONTROLS
mdefine_line|#define ICS_CONTROLS (sizeof(snd_ics_controls)/sizeof(snd_kcontrol_new_t))
DECL|variable|snd_ics_controls
r_static
id|snd_kcontrol_new_t
id|snd_ics_controls
(braket
)braket
op_assign
(brace
id|GF1_SINGLE
c_func
(paren
l_string|&quot;Master Playback Switch&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|1
)paren
comma
id|ICS_DOUBLE
c_func
(paren
l_string|&quot;Master Playback Volume&quot;
comma
l_int|0
comma
id|SNDRV_ICS_MASTER_DEV
)paren
comma
id|ICS_DOUBLE
c_func
(paren
l_string|&quot;Synth Playback Volume&quot;
comma
l_int|0
comma
id|SNDRV_ICS_GF1_DEV
)paren
comma
id|GF1_SINGLE
c_func
(paren
l_string|&quot;Line Switch&quot;
comma
l_int|0
comma
l_int|0
comma
l_int|1
)paren
comma
id|ICS_DOUBLE
c_func
(paren
l_string|&quot;Line Playback Volume&quot;
comma
l_int|0
comma
id|SNDRV_ICS_LINE_DEV
)paren
comma
id|GF1_SINGLE
c_func
(paren
l_string|&quot;Mic Switch&quot;
comma
l_int|0
comma
l_int|2
comma
l_int|0
)paren
comma
id|ICS_DOUBLE
c_func
(paren
l_string|&quot;Mic Playback Volume&quot;
comma
l_int|0
comma
id|SNDRV_ICS_MIC_DEV
)paren
comma
id|ICS_DOUBLE
c_func
(paren
l_string|&quot;CD Playback Volume&quot;
comma
l_int|0
comma
id|SNDRV_ICS_CD_DEV
)paren
)brace
suffix:semicolon
DECL|function|snd_gf1_new_mixer
r_int
id|snd_gf1_new_mixer
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_card_t
op_star
id|card
suffix:semicolon
r_int
id|idx
comma
id|err
comma
id|max
suffix:semicolon
id|snd_assert
c_func
(paren
id|gus
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|card
op_assign
id|gus-&gt;card
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;ics_flag
)paren
id|snd_component_add
c_func
(paren
id|card
comma
l_string|&quot;ICS2101&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;mixername
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|strcpy
c_func
(paren
id|card-&gt;mixername
comma
id|gus-&gt;ics_flag
ques
c_cond
l_string|&quot;GF1,ICS2101&quot;
suffix:colon
l_string|&quot;GF1&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|gus-&gt;ics_flag
)paren
id|strcat
c_func
(paren
id|card-&gt;mixername
comma
l_string|&quot;,ICS2101&quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|card-&gt;mixername
comma
l_string|&quot;,GF1&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|gus-&gt;ics_flag
)paren
(brace
id|max
op_assign
id|gus-&gt;ess_flag
ques
c_cond
l_int|1
suffix:colon
id|GF1_CONTROLS
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
id|max
suffix:semicolon
id|idx
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
id|card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_gf1_controls
(braket
id|idx
)braket
comma
id|gus
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
)brace
r_else
(brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|ICS_CONTROLS
suffix:semicolon
id|idx
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
id|card
comma
id|snd_ctl_new1
c_func
(paren
op_amp
id|snd_ics_controls
(braket
id|idx
)braket
comma
id|gus
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
