multiline_comment|/*&n; * Universal Interface for Intel High Definition Audio Codec&n; *&n; * HD audio interface patch for C-Media CMI9880&n; *&n; * Copyright (c) 2004 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *&n; *  This driver is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This driver is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;hda_codec.h&quot;
macro_line|#include &quot;hda_local.h&quot;
multiline_comment|/* board config type */
r_enum
(brace
DECL|enumerator|CMI_MINIMAL
id|CMI_MINIMAL
comma
multiline_comment|/* back 3-jack */
DECL|enumerator|CMI_MIN_FP
id|CMI_MIN_FP
comma
multiline_comment|/* back 3-jack + front-panel 2-jack */
DECL|enumerator|CMI_FULL
id|CMI_FULL
comma
multiline_comment|/* back 6-jack + front-panel 2-jack */
DECL|enumerator|CMI_FULL_DIG
id|CMI_FULL_DIG
comma
multiline_comment|/* back 6-jack + front-panel 2-jack + digital I/O */
DECL|enumerator|CMI_ALLOUT
id|CMI_ALLOUT
comma
multiline_comment|/* back 5-jack + front-panel 2-jack + digital out */
)brace
suffix:semicolon
DECL|struct|cmi_spec
r_struct
id|cmi_spec
(brace
DECL|member|board_config
r_int
id|board_config
suffix:semicolon
DECL|member|surr_switch
r_int
r_int
id|surr_switch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* switchable line,mic */
DECL|member|no_line_in
r_int
r_int
id|no_line_in
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* no line-in (5-jack) */
DECL|member|front_panel
r_int
r_int
id|front_panel
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* has front-panel 2-jack */
multiline_comment|/* playback */
DECL|member|multiout
r_struct
id|hda_multi_out
id|multiout
suffix:semicolon
multiline_comment|/* capture */
DECL|member|adc_nids
id|hda_nid_t
op_star
id|adc_nids
suffix:semicolon
DECL|member|dig_in_nid
id|hda_nid_t
id|dig_in_nid
suffix:semicolon
multiline_comment|/* capture source */
DECL|member|input_mux
r_const
r_struct
id|hda_input_mux
op_star
id|input_mux
suffix:semicolon
DECL|member|cur_mux
r_int
r_int
id|cur_mux
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* channel mode */
DECL|member|num_ch_modes
r_int
r_int
id|num_ch_modes
suffix:semicolon
DECL|member|cur_ch_mode
r_int
r_int
id|cur_ch_mode
suffix:semicolon
DECL|member|channel_modes
r_const
r_struct
id|cmi_channel_mode
op_star
id|channel_modes
suffix:semicolon
DECL|member|pcm_rec
r_struct
id|hda_pcm
id|pcm_rec
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* PCM information */
)brace
suffix:semicolon
multiline_comment|/*&n; * input MUX&n; */
DECL|function|cmi_mux_enum_info
r_static
r_int
id|cmi_mux_enum_info
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
r_struct
id|hda_codec
op_star
id|codec
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_return
id|snd_hda_input_mux_info
c_func
(paren
id|spec-&gt;input_mux
comma
id|uinfo
)paren
suffix:semicolon
)brace
DECL|function|cmi_mux_enum_get
r_static
r_int
id|cmi_mux_enum_get
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
r_struct
id|hda_codec
op_star
id|codec
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_int
r_int
id|adc_idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_assign
id|spec-&gt;cur_mux
(braket
id|adc_idx
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmi_mux_enum_put
r_static
r_int
id|cmi_mux_enum_put
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
r_struct
id|hda_codec
op_star
id|codec
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_int
r_int
id|adc_idx
op_assign
id|snd_ctl_get_ioffidx
c_func
(paren
id|kcontrol
comma
op_amp
id|ucontrol-&gt;id
)paren
suffix:semicolon
r_return
id|snd_hda_input_mux_put
c_func
(paren
id|codec
comma
id|spec-&gt;input_mux
comma
id|ucontrol
comma
id|spec-&gt;adc_nids
(braket
id|adc_idx
)braket
comma
op_amp
id|spec-&gt;cur_mux
(braket
id|adc_idx
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * shared line-in, mic for surrounds&n; */
multiline_comment|/* 3-stack / 2 channel */
DECL|variable|cmi9880_ch2_init
r_static
r_struct
id|hda_verb
id|cmi9880_ch2_init
(braket
)braket
op_assign
(brace
multiline_comment|/* set line-in PIN for input */
(brace
l_int|0x0c
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x20
)brace
comma
multiline_comment|/* set mic PIN for input, also enable vref */
(brace
l_int|0x0d
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x24
)brace
comma
multiline_comment|/* route front PCM (DAC1) to HP */
(brace
l_int|0x0f
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x00
)brace
comma
(brace
)brace
)brace
suffix:semicolon
multiline_comment|/* 3-stack / 6 channel */
DECL|variable|cmi9880_ch6_init
r_static
r_struct
id|hda_verb
id|cmi9880_ch6_init
(braket
)braket
op_assign
(brace
multiline_comment|/* set line-in PIN for input */
(brace
l_int|0x0c
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x40
)brace
comma
multiline_comment|/* set mic PIN for input, also enable vref */
(brace
l_int|0x0d
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x40
)brace
comma
multiline_comment|/* route front PCM (DAC1) to HP */
(brace
l_int|0x0f
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x00
)brace
comma
(brace
)brace
)brace
suffix:semicolon
multiline_comment|/* 3-stack+front / 8 channel */
DECL|variable|cmi9880_ch8_init
r_static
r_struct
id|hda_verb
id|cmi9880_ch8_init
(braket
)braket
op_assign
(brace
multiline_comment|/* set line-in PIN for input */
(brace
l_int|0x0c
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x40
)brace
comma
multiline_comment|/* set mic PIN for input, also enable vref */
(brace
l_int|0x0d
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x40
)brace
comma
multiline_comment|/* route rear-surround PCM (DAC4) to HP */
(brace
l_int|0x0f
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x03
)brace
comma
(brace
)brace
)brace
suffix:semicolon
DECL|struct|cmi_channel_mode
r_struct
id|cmi_channel_mode
(brace
DECL|member|channels
r_int
r_int
id|channels
suffix:semicolon
DECL|member|sequence
r_const
r_struct
id|hda_verb
op_star
id|sequence
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|cmi9880_channel_modes
r_static
r_struct
id|cmi_channel_mode
id|cmi9880_channel_modes
(braket
l_int|3
)braket
op_assign
(brace
(brace
l_int|2
comma
id|cmi9880_ch2_init
)brace
comma
(brace
l_int|6
comma
id|cmi9880_ch6_init
)brace
comma
(brace
l_int|8
comma
id|cmi9880_ch8_init
)brace
comma
)brace
suffix:semicolon
DECL|function|cmi_ch_mode_info
r_static
r_int
id|cmi_ch_mode_info
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
r_struct
id|hda_codec
op_star
id|codec
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
id|snd_assert
c_func
(paren
id|spec-&gt;channel_modes
comma
r_return
op_minus
id|EINVAL
)paren
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
id|spec-&gt;num_ch_modes
suffix:semicolon
r_if
c_cond
(paren
id|uinfo-&gt;value.enumerated.item
op_ge
id|uinfo-&gt;value.enumerated.items
)paren
id|uinfo-&gt;value.enumerated.item
op_assign
id|uinfo-&gt;value.enumerated.items
op_minus
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|uinfo-&gt;value.enumerated.name
comma
l_string|&quot;%dch&quot;
comma
id|spec-&gt;channel_modes
(braket
id|uinfo-&gt;value.enumerated.item
)braket
dot
id|channels
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmi_ch_mode_get
r_static
r_int
id|cmi_ch_mode_get
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
r_struct
id|hda_codec
op_star
id|codec
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_assign
id|spec-&gt;cur_ch_mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmi_ch_mode_put
r_static
r_int
id|cmi_ch_mode_put
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
r_struct
id|hda_codec
op_star
id|codec
op_assign
id|snd_kcontrol_chip
c_func
(paren
id|kcontrol
)paren
suffix:semicolon
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
id|snd_assert
c_func
(paren
id|spec-&gt;channel_modes
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_ge
id|spec-&gt;num_ch_modes
)paren
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_assign
id|spec-&gt;num_ch_modes
suffix:semicolon
r_if
c_cond
(paren
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
op_eq
id|spec-&gt;cur_ch_mode
op_logical_and
op_logical_neg
id|codec-&gt;in_resume
)paren
r_return
l_int|0
suffix:semicolon
id|spec-&gt;cur_ch_mode
op_assign
id|ucontrol-&gt;value.enumerated.item
(braket
l_int|0
)braket
suffix:semicolon
id|snd_hda_sequence_write
c_func
(paren
id|codec
comma
id|spec-&gt;channel_modes
(braket
id|spec-&gt;cur_ch_mode
)braket
dot
id|sequence
)paren
suffix:semicolon
id|spec-&gt;multiout.max_channels
op_assign
id|spec-&gt;channel_modes
(braket
id|spec-&gt;cur_ch_mode
)braket
dot
id|channels
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|variable|cmi9880_basic_mixer
r_static
id|snd_kcontrol_new_t
id|cmi9880_basic_mixer
(braket
)braket
op_assign
(brace
multiline_comment|/* CMI9880 has no playback volumes! */
id|HDA_CODEC_MUTE
c_func
(paren
l_string|&quot;PCM Playback Switch&quot;
comma
l_int|0x03
comma
l_int|0x0
comma
id|HDA_OUTPUT
)paren
comma
multiline_comment|/* front */
id|HDA_CODEC_MUTE
c_func
(paren
l_string|&quot;Surround Playback Switch&quot;
comma
l_int|0x04
comma
l_int|0x0
comma
id|HDA_OUTPUT
)paren
comma
id|HDA_CODEC_MUTE_MONO
c_func
(paren
l_string|&quot;Center Playback Switch&quot;
comma
l_int|0x05
comma
l_int|1
comma
l_int|0x0
comma
id|HDA_OUTPUT
)paren
comma
id|HDA_CODEC_MUTE_MONO
c_func
(paren
l_string|&quot;LFE Playback Switch&quot;
comma
l_int|0x05
comma
l_int|2
comma
l_int|0x0
comma
id|HDA_OUTPUT
)paren
comma
id|HDA_CODEC_MUTE
c_func
(paren
l_string|&quot;Side Playback Switch&quot;
comma
l_int|0x06
comma
l_int|0x0
comma
id|HDA_OUTPUT
)paren
comma
(brace
dot
id|iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
comma
multiline_comment|/* The multiple &quot;Capture Source&quot; controls confuse alsamixer&n;&t;&t; * So call somewhat different..&n;&t;&t; * FIXME: the controls appear in the &quot;playback&quot; view!&n;&t;&t; */
multiline_comment|/* .name = &quot;Capture Source&quot;, */
dot
id|name
op_assign
l_string|&quot;Input Source&quot;
comma
dot
id|count
op_assign
l_int|2
comma
dot
id|info
op_assign
id|cmi_mux_enum_info
comma
dot
id|get
op_assign
id|cmi_mux_enum_get
comma
dot
id|put
op_assign
id|cmi_mux_enum_put
comma
)brace
comma
id|HDA_CODEC_VOLUME
c_func
(paren
l_string|&quot;Capture Volume&quot;
comma
l_int|0x08
comma
l_int|0
comma
id|HDA_INPUT
)paren
comma
id|HDA_CODEC_VOLUME_IDX
c_func
(paren
l_string|&quot;Capture Volume&quot;
comma
l_int|1
comma
l_int|0x09
comma
l_int|0
comma
id|HDA_INPUT
)paren
comma
id|HDA_CODEC_MUTE
c_func
(paren
l_string|&quot;Capture Switch&quot;
comma
l_int|0x08
comma
l_int|0
comma
id|HDA_INPUT
)paren
comma
id|HDA_CODEC_MUTE_IDX
c_func
(paren
l_string|&quot;Capture Switch&quot;
comma
l_int|1
comma
l_int|0x09
comma
l_int|0
comma
id|HDA_INPUT
)paren
comma
id|HDA_CODEC_VOLUME
c_func
(paren
l_string|&quot;PC Speaker Playback Volume&quot;
comma
l_int|0x23
comma
l_int|0
comma
id|HDA_OUTPUT
)paren
comma
id|HDA_CODEC_MUTE
c_func
(paren
l_string|&quot;PC Speaker Playback Switch&quot;
comma
l_int|0x23
comma
l_int|0
comma
id|HDA_OUTPUT
)paren
comma
(brace
)brace
multiline_comment|/* end */
)brace
suffix:semicolon
multiline_comment|/*&n; * shared I/O pins&n; */
DECL|variable|cmi9880_ch_mode_mixer
r_static
id|snd_kcontrol_new_t
id|cmi9880_ch_mode_mixer
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
l_string|&quot;Channel Mode&quot;
comma
dot
id|info
op_assign
id|cmi_ch_mode_info
comma
dot
id|get
op_assign
id|cmi_ch_mode_get
comma
dot
id|put
op_assign
id|cmi_ch_mode_put
comma
)brace
comma
(brace
)brace
multiline_comment|/* end */
)brace
suffix:semicolon
multiline_comment|/* AUD-in selections:&n; * 0x0b 0x0c 0x0d 0x0e 0x0f 0x10 0x11 0x1f 0x20&n; */
DECL|variable|cmi9880_basic_mux
r_static
r_struct
id|hda_input_mux
id|cmi9880_basic_mux
op_assign
(brace
dot
id|num_items
op_assign
l_int|4
comma
dot
id|items
op_assign
(brace
(brace
l_string|&quot;Front Mic&quot;
comma
l_int|0x5
)brace
comma
(brace
l_string|&quot;Rear Mic&quot;
comma
l_int|0x2
)brace
comma
(brace
l_string|&quot;Line&quot;
comma
l_int|0x1
)brace
comma
(brace
l_string|&quot;CD&quot;
comma
l_int|0x7
)brace
comma
)brace
)brace
suffix:semicolon
DECL|variable|cmi9880_no_line_mux
r_static
r_struct
id|hda_input_mux
id|cmi9880_no_line_mux
op_assign
(brace
dot
id|num_items
op_assign
l_int|3
comma
dot
id|items
op_assign
(brace
(brace
l_string|&quot;Front Mic&quot;
comma
l_int|0x5
)brace
comma
(brace
l_string|&quot;Rear Mic&quot;
comma
l_int|0x2
)brace
comma
(brace
l_string|&quot;CD&quot;
comma
l_int|0x7
)brace
comma
)brace
)brace
suffix:semicolon
multiline_comment|/* front, rear, clfe, rear_surr */
DECL|variable|cmi9880_dac_nids
r_static
id|hda_nid_t
id|cmi9880_dac_nids
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x03
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0x06
)brace
suffix:semicolon
multiline_comment|/* ADC0, ADC1 */
DECL|variable|cmi9880_adc_nids
r_static
id|hda_nid_t
id|cmi9880_adc_nids
(braket
l_int|2
)braket
op_assign
(brace
l_int|0x08
comma
l_int|0x09
)brace
suffix:semicolon
DECL|macro|CMI_DIG_OUT_NID
mdefine_line|#define CMI_DIG_OUT_NID&t;0x07
DECL|macro|CMI_DIG_IN_NID
mdefine_line|#define CMI_DIG_IN_NID&t;0x0a
multiline_comment|/*&n; */
DECL|variable|cmi9880_basic_init
r_static
r_struct
id|hda_verb
id|cmi9880_basic_init
(braket
)braket
op_assign
(brace
multiline_comment|/* port-D for line out (rear panel) */
(brace
l_int|0x0b
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-E for HP out (front panel) */
(brace
l_int|0x0f
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* route front PCM to HP */
(brace
l_int|0x0f
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x00
)brace
comma
multiline_comment|/* port-A for surround (rear panel) */
(brace
l_int|0x0e
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-G for CLFE (rear panel) */
(brace
l_int|0x1f
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-H for side (rear panel) */
(brace
l_int|0x20
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-C for line-in (rear panel) */
(brace
l_int|0x0c
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x20
)brace
comma
multiline_comment|/* port-B for mic-in (rear panel) with vref */
(brace
l_int|0x0d
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x24
)brace
comma
multiline_comment|/* port-F for mic-in (front panel) with vref */
(brace
l_int|0x10
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x24
)brace
comma
multiline_comment|/* CD-in */
(brace
l_int|0x11
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x20
)brace
comma
multiline_comment|/* route front mic to ADC1/2 */
(brace
l_int|0x08
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x05
)brace
comma
(brace
l_int|0x09
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x05
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
DECL|variable|cmi9880_allout_init
r_static
r_struct
id|hda_verb
id|cmi9880_allout_init
(braket
)braket
op_assign
(brace
multiline_comment|/* port-D for line out (rear panel) */
(brace
l_int|0x0b
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-E for HP out (front panel) */
(brace
l_int|0x0f
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* route front PCM to HP */
(brace
l_int|0x0f
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x00
)brace
comma
multiline_comment|/* port-A for side (rear panel) */
(brace
l_int|0x0e
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-G for CLFE (rear panel) */
(brace
l_int|0x1f
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-C for surround (rear panel) */
(brace
l_int|0x0c
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0xc0
)brace
comma
multiline_comment|/* port-B for mic-in (rear panel) with vref */
(brace
l_int|0x0d
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x24
)brace
comma
multiline_comment|/* port-F for mic-in (front panel) with vref */
(brace
l_int|0x10
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x24
)brace
comma
multiline_comment|/* CD-in */
(brace
l_int|0x11
comma
id|AC_VERB_SET_PIN_WIDGET_CONTROL
comma
l_int|0x20
)brace
comma
multiline_comment|/* route front mic to ADC1/2 */
(brace
l_int|0x08
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x05
)brace
comma
(brace
l_int|0x09
comma
id|AC_VERB_SET_CONNECT_SEL
comma
l_int|0x05
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
multiline_comment|/*&n; */
DECL|function|cmi9880_build_controls
r_static
r_int
id|cmi9880_build_controls
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
op_assign
id|snd_hda_add_new_ctls
c_func
(paren
id|codec
comma
id|cmi9880_basic_mixer
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
r_if
c_cond
(paren
id|spec-&gt;surr_switch
)paren
(brace
id|err
op_assign
id|snd_hda_add_new_ctls
c_func
(paren
id|codec
comma
id|cmi9880_ch_mode_mixer
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
r_if
c_cond
(paren
id|spec-&gt;multiout.dig_out_nid
)paren
(brace
id|err
op_assign
id|snd_hda_create_spdif_out_ctls
c_func
(paren
id|codec
comma
id|CMI_DIG_OUT_NID
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
multiline_comment|/* TODO: digital-in */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmi9880_init
r_static
r_int
id|cmi9880_init
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;board_config
op_eq
id|CMI_ALLOUT
)paren
id|snd_hda_sequence_write
c_func
(paren
id|codec
comma
id|cmi9880_allout_init
)paren
suffix:semicolon
r_else
id|snd_hda_sequence_write
c_func
(paren
id|codec
comma
id|cmi9880_basic_init
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
multiline_comment|/*&n; * resume&n; */
DECL|function|cmi9880_resume
r_static
r_int
id|cmi9880_resume
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
comma
r_int
r_int
id|state
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
id|cmi9880_init
c_func
(paren
id|codec
)paren
suffix:semicolon
id|snd_hda_resume_ctls
c_func
(paren
id|codec
comma
id|cmi9880_basic_mixer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;surr_switch
)paren
id|snd_hda_resume_ctls
c_func
(paren
id|codec
comma
id|cmi9880_ch_mode_mixer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;multiout.dig_out_nid
)paren
id|snd_hda_resume_spdif_out
c_func
(paren
id|codec
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Analog playback callbacks&n; */
DECL|function|cmi9880_playback_pcm_open
r_static
r_int
id|cmi9880_playback_pcm_open
c_func
(paren
r_struct
id|hda_pcm_stream
op_star
id|hinfo
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_return
id|snd_hda_multi_out_analog_open
c_func
(paren
id|codec
comma
op_amp
id|spec-&gt;multiout
comma
id|substream
)paren
suffix:semicolon
)brace
DECL|function|cmi9880_playback_pcm_prepare
r_static
r_int
id|cmi9880_playback_pcm_prepare
c_func
(paren
r_struct
id|hda_pcm_stream
op_star
id|hinfo
comma
r_struct
id|hda_codec
op_star
id|codec
comma
r_int
r_int
id|stream_tag
comma
r_int
r_int
id|format
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_return
id|snd_hda_multi_out_analog_prepare
c_func
(paren
id|codec
comma
op_amp
id|spec-&gt;multiout
comma
id|stream_tag
comma
id|format
comma
id|substream
)paren
suffix:semicolon
)brace
DECL|function|cmi9880_playback_pcm_cleanup
r_static
r_int
id|cmi9880_playback_pcm_cleanup
c_func
(paren
r_struct
id|hda_pcm_stream
op_star
id|hinfo
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_return
id|snd_hda_multi_out_analog_cleanup
c_func
(paren
id|codec
comma
op_amp
id|spec-&gt;multiout
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Digital out&n; */
DECL|function|cmi9880_dig_playback_pcm_open
r_static
r_int
id|cmi9880_dig_playback_pcm_open
c_func
(paren
r_struct
id|hda_pcm_stream
op_star
id|hinfo
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_return
id|snd_hda_multi_out_dig_open
c_func
(paren
id|codec
comma
op_amp
id|spec-&gt;multiout
)paren
suffix:semicolon
)brace
DECL|function|cmi9880_dig_playback_pcm_close
r_static
r_int
id|cmi9880_dig_playback_pcm_close
c_func
(paren
r_struct
id|hda_pcm_stream
op_star
id|hinfo
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_return
id|snd_hda_multi_out_dig_close
c_func
(paren
id|codec
comma
op_amp
id|spec-&gt;multiout
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Analog capture&n; */
DECL|function|cmi9880_capture_pcm_prepare
r_static
r_int
id|cmi9880_capture_pcm_prepare
c_func
(paren
r_struct
id|hda_pcm_stream
op_star
id|hinfo
comma
r_struct
id|hda_codec
op_star
id|codec
comma
r_int
r_int
id|stream_tag
comma
r_int
r_int
id|format
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
id|snd_hda_codec_setup_stream
c_func
(paren
id|codec
comma
id|spec-&gt;adc_nids
(braket
id|substream-&gt;number
)braket
comma
id|stream_tag
comma
l_int|0
comma
id|format
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmi9880_capture_pcm_cleanup
r_static
r_int
id|cmi9880_capture_pcm_cleanup
c_func
(paren
r_struct
id|hda_pcm_stream
op_star
id|hinfo
comma
r_struct
id|hda_codec
op_star
id|codec
comma
id|snd_pcm_substream_t
op_star
id|substream
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
id|snd_hda_codec_setup_stream
c_func
(paren
id|codec
comma
id|spec-&gt;adc_nids
(braket
id|substream-&gt;number
)braket
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|variable|cmi9880_pcm_analog_playback
r_static
r_struct
id|hda_pcm_stream
id|cmi9880_pcm_analog_playback
op_assign
(brace
dot
id|substreams
op_assign
l_int|1
comma
dot
id|channels_min
op_assign
l_int|2
comma
dot
id|channels_max
op_assign
l_int|8
comma
dot
id|nid
op_assign
l_int|0x03
comma
multiline_comment|/* NID to query formats and rates */
dot
id|ops
op_assign
(brace
dot
id|open
op_assign
id|cmi9880_playback_pcm_open
comma
dot
id|prepare
op_assign
id|cmi9880_playback_pcm_prepare
comma
dot
id|cleanup
op_assign
id|cmi9880_playback_pcm_cleanup
)brace
comma
)brace
suffix:semicolon
DECL|variable|cmi9880_pcm_analog_capture
r_static
r_struct
id|hda_pcm_stream
id|cmi9880_pcm_analog_capture
op_assign
(brace
dot
id|substreams
op_assign
l_int|2
comma
dot
id|channels_min
op_assign
l_int|2
comma
dot
id|channels_max
op_assign
l_int|2
comma
dot
id|nid
op_assign
l_int|0x08
comma
multiline_comment|/* NID to query formats and rates */
dot
id|ops
op_assign
(brace
dot
id|prepare
op_assign
id|cmi9880_capture_pcm_prepare
comma
dot
id|cleanup
op_assign
id|cmi9880_capture_pcm_cleanup
)brace
comma
)brace
suffix:semicolon
DECL|variable|cmi9880_pcm_digital_playback
r_static
r_struct
id|hda_pcm_stream
id|cmi9880_pcm_digital_playback
op_assign
(brace
dot
id|substreams
op_assign
l_int|1
comma
dot
id|channels_min
op_assign
l_int|2
comma
dot
id|channels_max
op_assign
l_int|2
comma
multiline_comment|/* NID is set in cmi9880_build_pcms */
dot
id|ops
op_assign
(brace
dot
id|open
op_assign
id|cmi9880_dig_playback_pcm_open
comma
dot
id|close
op_assign
id|cmi9880_dig_playback_pcm_close
)brace
comma
)brace
suffix:semicolon
DECL|variable|cmi9880_pcm_digital_capture
r_static
r_struct
id|hda_pcm_stream
id|cmi9880_pcm_digital_capture
op_assign
(brace
dot
id|substreams
op_assign
l_int|1
comma
dot
id|channels_min
op_assign
l_int|2
comma
dot
id|channels_max
op_assign
l_int|2
comma
multiline_comment|/* NID is set in cmi9880_build_pcms */
)brace
suffix:semicolon
DECL|function|cmi9880_build_pcms
r_static
r_int
id|cmi9880_build_pcms
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
op_assign
id|codec-&gt;spec
suffix:semicolon
r_struct
id|hda_pcm
op_star
id|info
op_assign
id|spec-&gt;pcm_rec
suffix:semicolon
id|codec-&gt;num_pcms
op_assign
l_int|1
suffix:semicolon
id|codec-&gt;pcm_info
op_assign
id|info
suffix:semicolon
id|info-&gt;name
op_assign
l_string|&quot;CMI9880&quot;
suffix:semicolon
id|info-&gt;stream
(braket
id|SNDRV_PCM_STREAM_PLAYBACK
)braket
op_assign
id|cmi9880_pcm_analog_playback
suffix:semicolon
id|info-&gt;stream
(braket
id|SNDRV_PCM_STREAM_CAPTURE
)braket
op_assign
id|cmi9880_pcm_analog_capture
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;multiout.dig_out_nid
op_logical_or
id|spec-&gt;dig_in_nid
)paren
(brace
id|codec-&gt;num_pcms
op_increment
suffix:semicolon
id|info
op_increment
suffix:semicolon
id|info-&gt;name
op_assign
l_string|&quot;CMI9880 Digital&quot;
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;multiout.dig_out_nid
)paren
(brace
id|info-&gt;stream
(braket
id|SNDRV_PCM_STREAM_PLAYBACK
)braket
op_assign
id|cmi9880_pcm_digital_playback
suffix:semicolon
id|info-&gt;stream
(braket
id|SNDRV_PCM_STREAM_PLAYBACK
)braket
dot
id|nid
op_assign
id|spec-&gt;multiout.dig_out_nid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spec-&gt;dig_in_nid
)paren
(brace
id|info-&gt;stream
(braket
id|SNDRV_PCM_STREAM_CAPTURE
)braket
op_assign
id|cmi9880_pcm_digital_capture
suffix:semicolon
id|info-&gt;stream
(braket
id|SNDRV_PCM_STREAM_CAPTURE
)braket
dot
id|nid
op_assign
id|spec-&gt;dig_in_nid
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cmi9880_free
r_static
r_void
id|cmi9880_free
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
(brace
id|kfree
c_func
(paren
id|codec-&gt;spec
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; */
DECL|variable|cmi9880_cfg_tbl
r_static
r_struct
id|hda_board_config
id|cmi9880_cfg_tbl
(braket
)braket
op_assign
(brace
(brace
dot
id|modelname
op_assign
l_string|&quot;minimal&quot;
comma
dot
id|config
op_assign
id|CMI_MINIMAL
)brace
comma
(brace
dot
id|modelname
op_assign
l_string|&quot;min_fp&quot;
comma
dot
id|config
op_assign
id|CMI_MIN_FP
)brace
comma
(brace
dot
id|modelname
op_assign
l_string|&quot;full&quot;
comma
dot
id|config
op_assign
id|CMI_FULL
)brace
comma
(brace
dot
id|modelname
op_assign
l_string|&quot;full_dig&quot;
comma
dot
id|config
op_assign
id|CMI_FULL_DIG
)brace
comma
(brace
dot
id|modelname
op_assign
l_string|&quot;allout&quot;
comma
dot
id|config
op_assign
id|CMI_ALLOUT
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
DECL|variable|cmi9880_patch_ops
r_static
r_struct
id|hda_codec_ops
id|cmi9880_patch_ops
op_assign
(brace
dot
id|build_controls
op_assign
id|cmi9880_build_controls
comma
dot
id|build_pcms
op_assign
id|cmi9880_build_pcms
comma
dot
id|init
op_assign
id|cmi9880_init
comma
dot
id|free
op_assign
id|cmi9880_free
comma
macro_line|#ifdef CONFIG_PM
dot
id|resume
op_assign
id|cmi9880_resume
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|patch_cmi9880
r_static
r_int
id|patch_cmi9880
c_func
(paren
r_struct
id|hda_codec
op_star
id|codec
)paren
(brace
r_struct
id|cmi_spec
op_star
id|spec
suffix:semicolon
id|spec
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
op_star
id|spec
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spec
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|codec-&gt;spec
op_assign
id|spec
suffix:semicolon
id|spec-&gt;board_config
op_assign
id|snd_hda_check_board_config
c_func
(paren
id|codec
comma
id|cmi9880_cfg_tbl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;board_config
OL
l_int|0
)paren
(brace
id|snd_printd
c_func
(paren
id|KERN_INFO
l_string|&quot;hda_codec: Unknown model for CMI9880&bslash;n&quot;
)paren
suffix:semicolon
id|spec-&gt;board_config
op_assign
id|CMI_MINIMAL
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|spec-&gt;board_config
)paren
(brace
r_case
id|CMI_MINIMAL
suffix:colon
r_case
id|CMI_MIN_FP
suffix:colon
id|spec-&gt;surr_switch
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;board_config
op_eq
id|CMI_MINIMAL
)paren
id|spec-&gt;num_ch_modes
op_assign
l_int|2
suffix:semicolon
r_else
(brace
id|spec-&gt;front_panel
op_assign
l_int|1
suffix:semicolon
id|spec-&gt;num_ch_modes
op_assign
l_int|3
suffix:semicolon
)brace
id|spec-&gt;channel_modes
op_assign
id|cmi9880_channel_modes
suffix:semicolon
id|spec-&gt;multiout.max_channels
op_assign
id|cmi9880_channel_modes
(braket
l_int|0
)braket
dot
id|channels
suffix:semicolon
id|spec-&gt;input_mux
op_assign
op_amp
id|cmi9880_basic_mux
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CMI_FULL
suffix:colon
r_case
id|CMI_FULL_DIG
suffix:colon
id|spec-&gt;front_panel
op_assign
l_int|1
suffix:semicolon
id|spec-&gt;multiout.max_channels
op_assign
l_int|8
suffix:semicolon
id|spec-&gt;input_mux
op_assign
op_amp
id|cmi9880_basic_mux
suffix:semicolon
r_if
c_cond
(paren
id|spec-&gt;board_config
op_eq
id|CMI_FULL_DIG
)paren
(brace
id|spec-&gt;multiout.dig_out_nid
op_assign
id|CMI_DIG_OUT_NID
suffix:semicolon
id|spec-&gt;dig_in_nid
op_assign
id|CMI_DIG_IN_NID
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CMI_ALLOUT
suffix:colon
id|spec-&gt;front_panel
op_assign
l_int|1
suffix:semicolon
id|spec-&gt;multiout.max_channels
op_assign
l_int|8
suffix:semicolon
id|spec-&gt;no_line_in
op_assign
l_int|1
suffix:semicolon
id|spec-&gt;input_mux
op_assign
op_amp
id|cmi9880_no_line_mux
suffix:semicolon
id|spec-&gt;multiout.dig_out_nid
op_assign
id|CMI_DIG_OUT_NID
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spec-&gt;multiout.num_dacs
op_assign
l_int|4
suffix:semicolon
id|spec-&gt;multiout.dac_nids
op_assign
id|cmi9880_dac_nids
suffix:semicolon
id|spec-&gt;adc_nids
op_assign
id|cmi9880_adc_nids
suffix:semicolon
id|codec-&gt;patch_ops
op_assign
id|cmi9880_patch_ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * patch entries&n; */
DECL|variable|snd_hda_preset_cmedia
r_struct
id|hda_codec_preset
id|snd_hda_preset_cmedia
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
l_int|0x434d4980
comma
dot
id|name
op_assign
l_string|&quot;CMI9880&quot;
comma
dot
id|patch
op_assign
id|patch_cmi9880
)brace
comma
(brace
)brace
multiline_comment|/* terminator */
)brace
suffix:semicolon
eof
