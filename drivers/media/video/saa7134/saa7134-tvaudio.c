multiline_comment|/*&n; * device driver for philips saa7134 based TV cards&n; * tv audio decoder (fm stereo, nicam, ...)&n; *&n; * (c) 2001,02 Gerd Knorr &lt;kraxel@bytesex.org&gt; [SuSE Labs]&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__ 1
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/div64.h&gt;
macro_line|#include &quot;saa7134-reg.h&quot;
macro_line|#include &quot;saa7134.h&quot;
multiline_comment|/* ------------------------------------------------------------------ */
DECL|variable|audio_debug
r_static
r_int
r_int
id|audio_debug
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|audio_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|audio_debug
comma
l_string|&quot;enable debug messages [tv audio]&quot;
)paren
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk(fmt, arg...)&t;if (audio_debug) &bslash;&n;&t;printk(KERN_DEBUG &quot;%s/audio: &quot; fmt, dev-&gt;name, ## arg)
DECL|macro|print_regb
mdefine_line|#define print_regb(reg) printk(&quot;%s:   reg 0x%03x [%-16s]: 0x%02x&bslash;n&quot;, &bslash;&n;&t;&t;dev-&gt;name,(SAA7134_##reg),(#reg),saa_readb((SAA7134_##reg)))
multiline_comment|/* ------------------------------------------------------------------ */
DECL|variable|tvaudio
r_static
r_struct
id|saa7134_tvaudio
id|tvaudio
(braket
)braket
op_assign
(brace
(brace
dot
id|name
op_assign
l_string|&quot;PAL-B/G FM-stereo&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_PAL
comma
dot
id|mode
op_assign
id|TVAUDIO_FM_BG_STEREO
comma
dot
id|carr1
op_assign
l_int|5500
comma
dot
id|carr2
op_assign
l_int|5742
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;PAL-D/K1 FM-stereo&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_PAL
comma
dot
id|carr1
op_assign
l_int|6500
comma
dot
id|carr2
op_assign
l_int|6258
comma
dot
id|mode
op_assign
id|TVAUDIO_FM_BG_STEREO
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;PAL-D/K2 FM-stereo&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_PAL
comma
dot
id|carr1
op_assign
l_int|6500
comma
dot
id|carr2
op_assign
l_int|6742
comma
dot
id|mode
op_assign
id|TVAUDIO_FM_BG_STEREO
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;PAL-D/K3 FM-stereo&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_PAL
comma
dot
id|carr1
op_assign
l_int|6500
comma
dot
id|carr2
op_assign
l_int|5742
comma
dot
id|mode
op_assign
id|TVAUDIO_FM_BG_STEREO
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;PAL-B/G NICAM&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_PAL
comma
dot
id|carr1
op_assign
l_int|5500
comma
dot
id|carr2
op_assign
l_int|5850
comma
dot
id|mode
op_assign
id|TVAUDIO_NICAM_FM
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;PAL-I NICAM&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_PAL
comma
dot
id|carr1
op_assign
l_int|6000
comma
dot
id|carr2
op_assign
l_int|6552
comma
dot
id|mode
op_assign
id|TVAUDIO_NICAM_FM
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;PAL-D/K NICAM&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_PAL
comma
dot
id|carr1
op_assign
l_int|6500
comma
dot
id|carr2
op_assign
l_int|5850
comma
dot
id|mode
op_assign
id|TVAUDIO_NICAM_FM
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;SECAM-L NICAM&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_SECAM
comma
dot
id|carr1
op_assign
l_int|6500
comma
dot
id|carr2
op_assign
l_int|5850
comma
dot
id|mode
op_assign
id|TVAUDIO_NICAM_AM
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;NTSC-M&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_NTSC
comma
dot
id|carr1
op_assign
l_int|4500
comma
dot
id|carr2
op_assign
op_minus
l_int|1
comma
dot
id|mode
op_assign
id|TVAUDIO_FM_MONO
comma
)brace
comma
(brace
dot
id|name
op_assign
l_string|&quot;NTSC-A2 FM-stereo&quot;
comma
dot
id|std
op_assign
id|V4L2_STD_NTSC
comma
dot
id|carr1
op_assign
l_int|4500
comma
dot
id|carr2
op_assign
l_int|4724
comma
dot
id|mode
op_assign
id|TVAUDIO_FM_K_STEREO
comma
)brace
)brace
suffix:semicolon
DECL|macro|TVAUDIO
mdefine_line|#define TVAUDIO (sizeof(tvaudio)/sizeof(struct saa7134_tvaudio))
multiline_comment|/* ------------------------------------------------------------------ */
DECL|function|tvaudio_init
r_static
r_void
id|tvaudio_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_int
id|clock
op_assign
id|saa7134_boards
(braket
id|dev-&gt;board
)braket
dot
id|audio_clock
suffix:semicolon
multiline_comment|/* init all audio registers */
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_PLL_CTRL
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCK0
comma
id|clock
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCK1
comma
(paren
id|clock
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCK2
comma
(paren
id|clock
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_PLL_CTRL
comma
l_int|0x01
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_NICAM_ERROR_LOW
comma
l_int|0x14
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_NICAM_ERROR_HIGH
comma
l_int|0x50
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_MONITOR_SELECT
comma
l_int|0xa0
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_FM_DEMATRIX
comma
l_int|0x80
)paren
suffix:semicolon
)brace
DECL|function|tvaudio_carr2reg
r_static
id|__u32
id|tvaudio_carr2reg
c_func
(paren
id|__u32
id|carrier
)paren
(brace
id|__u64
id|a
op_assign
id|carrier
suffix:semicolon
id|a
op_lshift_assign
l_int|24
suffix:semicolon
id|do_div
c_func
(paren
id|a
comma
l_int|12288
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
DECL|function|tvaudio_setcarrier
r_static
r_void
id|tvaudio_setcarrier
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
id|primary
comma
r_int
id|secondary
)paren
(brace
r_if
c_cond
(paren
op_minus
l_int|1
op_eq
id|secondary
)paren
id|secondary
op_assign
id|primary
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_CARRIER1_FREQ0
op_rshift
l_int|2
comma
id|tvaudio_carr2reg
c_func
(paren
id|primary
)paren
)paren
suffix:semicolon
id|saa_writel
c_func
(paren
id|SAA7134_CARRIER2_FREQ0
op_rshift
l_int|2
comma
id|tvaudio_carr2reg
c_func
(paren
id|secondary
)paren
)paren
suffix:semicolon
)brace
DECL|function|saa7134_tvaudio_do_mute_input
r_static
r_void
id|saa7134_tvaudio_do_mute_input
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
r_int
id|mute
suffix:semicolon
r_struct
id|saa7134_input
op_star
id|in
suffix:semicolon
r_int
id|reg
op_assign
l_int|0
suffix:semicolon
r_int
id|mask
suffix:semicolon
multiline_comment|/* look what is to do ... */
id|in
op_assign
id|dev-&gt;input
suffix:semicolon
id|mute
op_assign
(paren
id|dev-&gt;ctl_mute
op_logical_or
id|dev-&gt;automute
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card_has_audio
c_func
(paren
id|dev
)paren
op_logical_and
id|card
c_func
(paren
id|dev
)paren
dot
id|mute.name
)paren
(brace
multiline_comment|/* 7130 - we&squot;ll mute using some unconnected audio input */
r_if
c_cond
(paren
id|mute
)paren
id|in
op_assign
op_amp
id|card
c_func
(paren
id|dev
)paren
dot
id|mute
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;hw_mute
op_eq
id|mute
op_logical_and
id|dev-&gt;hw_input
op_eq
id|in
)paren
r_return
suffix:semicolon
macro_line|#if 1
id|dprintk
c_func
(paren
l_string|&quot;ctl_mute=%d automute=%d input=%s  =&gt;  mute=%d input=%s&bslash;n&quot;
comma
id|dev-&gt;ctl_mute
comma
id|dev-&gt;automute
comma
id|dev-&gt;input-&gt;name
comma
id|mute
comma
id|in-&gt;name
)paren
suffix:semicolon
macro_line|#endif
id|dev-&gt;hw_mute
op_assign
id|mute
suffix:semicolon
id|dev-&gt;hw_input
op_assign
id|in
suffix:semicolon
r_if
c_cond
(paren
id|card_has_audio
c_func
(paren
id|dev
)paren
)paren
multiline_comment|/* 7134 mute */
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_MUTE_CTRL
comma
id|mute
ques
c_cond
l_int|0xff
suffix:colon
l_int|0xbb
)paren
suffix:semicolon
multiline_comment|/* switch internal audio mux */
r_switch
c_cond
(paren
id|in-&gt;amux
)paren
(brace
r_case
id|TV
suffix:colon
id|reg
op_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LINE1
suffix:colon
id|reg
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LINE2
suffix:colon
id|reg
op_assign
l_int|0x01
suffix:semicolon
r_break
suffix:semicolon
)brace
id|saa_andorb
c_func
(paren
id|SAA7134_ANALOG_IO_SELECT
comma
l_int|0x07
comma
id|reg
)paren
suffix:semicolon
multiline_comment|/* switch gpio-connected external audio mux */
r_if
c_cond
(paren
l_int|0
op_eq
id|card
c_func
(paren
id|dev
)paren
dot
id|gpiomask
)paren
r_return
suffix:semicolon
id|mask
op_assign
id|card
c_func
(paren
id|dev
)paren
dot
id|gpiomask
suffix:semicolon
id|saa_andorl
c_func
(paren
id|SAA7134_GPIO_GPMODE0
op_rshift
l_int|2
comma
id|mask
comma
id|mask
)paren
suffix:semicolon
id|saa_andorl
c_func
(paren
id|SAA7134_GPIO_GPSTATUS0
op_rshift
l_int|2
comma
id|mask
comma
id|in-&gt;gpio
)paren
suffix:semicolon
id|saa7134_track_gpio
c_func
(paren
id|dev
comma
id|in-&gt;name
)paren
suffix:semicolon
)brace
DECL|function|saa7134_tvaudio_setmute
r_void
id|saa7134_tvaudio_setmute
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|saa7134_tvaudio_do_mute_input
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|saa7134_tvaudio_setinput
r_void
id|saa7134_tvaudio_setinput
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_input
op_star
id|in
)paren
(brace
id|dev-&gt;input
op_assign
id|in
suffix:semicolon
id|saa7134_tvaudio_do_mute_input
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|saa7134_tvaudio_setvolume
r_void
id|saa7134_tvaudio_setvolume
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
id|level
)paren
(brace
id|saa_writeb
c_func
(paren
id|SAA7134_CHANNEL1_LEVEL
comma
id|level
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_CHANNEL2_LEVEL
comma
id|level
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_NICAM_LEVEL_ADJUST
comma
id|level
op_amp
l_int|0x1f
)paren
suffix:semicolon
)brace
DECL|function|tvaudio_setmode
r_static
r_void
id|tvaudio_setmode
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_tvaudio
op_star
id|audio
comma
r_char
op_star
id|note
)paren
(brace
r_if
c_cond
(paren
id|note
)paren
id|dprintk
c_func
(paren
l_string|&quot;tvaudio_setmode: %s %s [%d.%03d/%d.%03d MHz]&bslash;n&quot;
comma
id|note
comma
id|audio-&gt;name
comma
id|audio-&gt;carr1
op_div
l_int|1000
comma
id|audio-&gt;carr1
op_mod
l_int|1000
comma
id|audio-&gt;carr2
op_div
l_int|1000
comma
id|audio-&gt;carr2
op_mod
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tvnorm-&gt;id
op_eq
id|V4L2_STD_NTSC
)paren
(brace
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCKS_PER_FIELD0
comma
l_int|0xde
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCKS_PER_FIELD1
comma
l_int|0x15
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCKS_PER_FIELD2
comma
l_int|0x02
)paren
suffix:semicolon
)brace
r_else
(brace
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCKS_PER_FIELD0
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCKS_PER_FIELD1
comma
l_int|0x80
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_AUDIO_CLOCKS_PER_FIELD2
comma
l_int|0x02
)paren
suffix:semicolon
)brace
id|tvaudio_setcarrier
c_func
(paren
id|dev
comma
id|audio-&gt;carr1
comma
id|audio-&gt;carr2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|audio-&gt;mode
)paren
(brace
r_case
id|TVAUDIO_FM_MONO
suffix:colon
r_case
id|TVAUDIO_FM_BG_STEREO
suffix:colon
id|saa_writeb
c_func
(paren
id|SAA7134_DEMODULATOR
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_DCXO_IDENT_CTRL
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_FM_DEEMPHASIS
comma
l_int|0x22
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_FM_DEMATRIX
comma
l_int|0x80
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_STEREO_DAC_OUTPUT_SELECT
comma
l_int|0xa0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TVAUDIO_FM_K_STEREO
suffix:colon
id|saa_writeb
c_func
(paren
id|SAA7134_DEMODULATOR
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_DCXO_IDENT_CTRL
comma
l_int|0x01
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_FM_DEEMPHASIS
comma
l_int|0x22
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_FM_DEMATRIX
comma
l_int|0x80
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_STEREO_DAC_OUTPUT_SELECT
comma
l_int|0xa0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TVAUDIO_NICAM_FM
suffix:colon
id|saa_writeb
c_func
(paren
id|SAA7134_DEMODULATOR
comma
l_int|0x10
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_DCXO_IDENT_CTRL
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_FM_DEEMPHASIS
comma
l_int|0x44
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_STEREO_DAC_OUTPUT_SELECT
comma
l_int|0xa1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TVAUDIO_NICAM_AM
suffix:colon
id|saa_writeb
c_func
(paren
id|SAA7134_DEMODULATOR
comma
l_int|0x12
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_DCXO_IDENT_CTRL
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_FM_DEEMPHASIS
comma
l_int|0x44
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_STEREO_DAC_OUTPUT_SELECT
comma
l_int|0xa1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TVAUDIO_FM_SAT_STEREO
suffix:colon
multiline_comment|/* not implemented (yet) */
r_break
suffix:semicolon
)brace
id|saa_writel
c_func
(paren
l_int|0x174
op_rshift
l_int|2
comma
l_int|0x0001e000
)paren
suffix:semicolon
multiline_comment|/* FIXME */
)brace
DECL|function|saa7134_tvaudio_getstereo
r_int
id|saa7134_tvaudio_getstereo
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_struct
id|saa7134_tvaudio
op_star
id|audio
)paren
(brace
id|__u32
id|idp
comma
id|nicam
suffix:semicolon
r_int
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|audio-&gt;mode
)paren
(brace
r_case
id|TVAUDIO_FM_MONO
suffix:colon
r_return
id|V4L2_TUNER_SUB_MONO
suffix:semicolon
r_case
id|TVAUDIO_FM_K_STEREO
suffix:colon
r_case
id|TVAUDIO_FM_BG_STEREO
suffix:colon
id|idp
op_assign
(paren
id|saa_readb
c_func
(paren
id|SAA7134_IDENT_SIF
)paren
op_amp
l_int|0xe0
)paren
op_rshift
l_int|5
suffix:semicolon
r_if
c_cond
(paren
l_int|0x03
op_eq
(paren
id|idp
op_amp
l_int|0x03
)paren
)paren
id|retval
op_assign
id|V4L2_TUNER_SUB_LANG1
op_or
id|V4L2_TUNER_SUB_LANG2
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|0x05
op_eq
(paren
id|idp
op_amp
l_int|0x05
)paren
)paren
id|retval
op_assign
id|V4L2_TUNER_SUB_MONO
op_or
id|V4L2_TUNER_SUB_STEREO
suffix:semicolon
r_else
r_if
c_cond
(paren
l_int|0x01
op_eq
(paren
id|idp
op_amp
l_int|0x01
)paren
)paren
id|retval
op_assign
id|V4L2_TUNER_SUB_MONO
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TVAUDIO_FM_SAT_STEREO
suffix:colon
multiline_comment|/* not implemented (yet) */
r_break
suffix:semicolon
r_case
id|TVAUDIO_NICAM_FM
suffix:colon
r_case
id|TVAUDIO_NICAM_AM
suffix:colon
id|nicam
op_assign
id|saa_readb
c_func
(paren
id|SAA7134_NICAM_STATUS
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|nicam
op_amp
l_int|0x0b
)paren
(brace
r_case
l_int|0x08
suffix:colon
id|retval
op_assign
id|V4L2_TUNER_SUB_MONO
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x09
suffix:colon
id|retval
op_assign
id|V4L2_TUNER_SUB_LANG1
op_or
id|V4L2_TUNER_SUB_LANG2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0a
suffix:colon
id|retval
op_assign
id|V4L2_TUNER_SUB_MONO
op_or
id|V4L2_TUNER_SUB_STEREO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ne
op_minus
l_int|1
)paren
id|dprintk
c_func
(paren
l_string|&quot;found audio subchannels:%s%s%s%s&bslash;n&quot;
comma
(paren
id|retval
op_amp
id|V4L2_TUNER_SUB_MONO
)paren
ques
c_cond
l_string|&quot; mono&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|retval
op_amp
id|V4L2_TUNER_SUB_STEREO
)paren
ques
c_cond
l_string|&quot; stereo&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|retval
op_amp
id|V4L2_TUNER_SUB_LANG1
)paren
ques
c_cond
l_string|&quot; lang1&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|retval
op_amp
id|V4L2_TUNER_SUB_LANG2
)paren
ques
c_cond
l_string|&quot; lang2&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|tvaudio_sleep
r_static
r_int
id|tvaudio_sleep
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
id|timeout
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|dev-&gt;thread.wq
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|timeout
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|dev-&gt;thread.wq
comma
op_amp
id|wait
)paren
suffix:semicolon
r_return
id|dev-&gt;thread.scan1
op_ne
id|dev-&gt;thread.scan2
suffix:semicolon
)brace
DECL|function|tvaudio_checkcarrier
r_static
r_int
id|tvaudio_checkcarrier
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
comma
r_int
id|carrier
)paren
(brace
id|__s32
id|left
comma
id|right
comma
id|value
suffix:semicolon
id|tvaudio_setcarrier
c_func
(paren
id|dev
comma
id|carrier
op_minus
l_int|100
comma
id|carrier
op_minus
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tvaudio_sleep
c_func
(paren
id|dev
comma
id|HZ
op_div
l_int|10
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|left
op_assign
id|saa_readl
c_func
(paren
id|SAA7134_LEVEL_READOUT1
op_rshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tvaudio_sleep
c_func
(paren
id|dev
comma
id|HZ
op_div
l_int|10
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|left
op_assign
id|saa_readl
c_func
(paren
id|SAA7134_LEVEL_READOUT1
op_rshift
l_int|2
)paren
suffix:semicolon
id|tvaudio_setcarrier
c_func
(paren
id|dev
comma
id|carrier
op_plus
l_int|100
comma
id|carrier
op_plus
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tvaudio_sleep
c_func
(paren
id|dev
comma
id|HZ
op_div
l_int|10
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|right
op_assign
id|saa_readl
c_func
(paren
id|SAA7134_LEVEL_READOUT1
op_rshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tvaudio_sleep
c_func
(paren
id|dev
comma
id|HZ
op_div
l_int|10
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|right
op_assign
id|saa_readl
c_func
(paren
id|SAA7134_LEVEL_READOUT1
op_rshift
l_int|2
)paren
suffix:semicolon
id|left
op_rshift_assign
l_int|16
suffix:semicolon
id|right
op_rshift_assign
l_int|16
suffix:semicolon
id|value
op_assign
id|left
OG
id|right
ques
c_cond
id|left
op_minus
id|right
suffix:colon
id|right
op_minus
id|left
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;scanning %d.%03d MHz =&gt;  dc is %5d [%d/%d]&bslash;n&quot;
comma
id|carrier
op_div
l_int|1000
comma
id|carrier
op_mod
l_int|1000
comma
id|value
comma
id|left
comma
id|right
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|function|sifdebug_dump_regs
r_static
r_void
id|sifdebug_dump_regs
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|print_regb
c_func
(paren
id|AUDIO_STATUS
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|IDENT_SIF
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|LEVEL_READOUT1
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|LEVEL_READOUT2
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|DCXO_IDENT_CTRL
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|DEMODULATOR
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|AGC_GAIN_SELECT
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|MONITOR_SELECT
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|FM_DEEMPHASIS
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|FM_DEMATRIX
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|SIF_SAMPLE_FREQ
)paren
suffix:semicolon
id|print_regb
c_func
(paren
id|ANALOG_IO_SELECT
)paren
suffix:semicolon
)brace
DECL|function|tvaudio_thread
r_static
r_int
id|tvaudio_thread
c_func
(paren
r_void
op_star
id|data
)paren
(brace
DECL|macro|MAX_SCAN
mdefine_line|#define MAX_SCAN 4
r_static
r_const
r_int
id|carr_pal
(braket
id|MAX_SCAN
)braket
op_assign
(brace
l_int|5500
comma
l_int|6000
comma
l_int|6500
)brace
suffix:semicolon
r_static
r_const
r_int
id|carr_ntsc
(braket
id|MAX_SCAN
)braket
op_assign
(brace
l_int|4500
)brace
suffix:semicolon
r_static
r_const
r_int
id|carr_secam
(braket
id|MAX_SCAN
)braket
op_assign
(brace
l_int|6500
)brace
suffix:semicolon
r_static
r_const
r_int
id|carr_default
(braket
id|MAX_SCAN
)braket
op_assign
(brace
l_int|4500
comma
l_int|5500
comma
l_int|6000
comma
l_int|6500
)brace
suffix:semicolon
r_struct
id|saa7134_dev
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_const
r_int
op_star
id|carr_scan
suffix:semicolon
r_int
id|carr_vals
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|i
comma
id|max
comma
id|carrier
comma
id|audio
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|daemonize
c_func
(paren
)paren
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;%s&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;thread.task
op_assign
id|current
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;thread.notify
op_ne
l_int|NULL
)paren
id|up
c_func
(paren
id|dev-&gt;thread.notify
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;thread
dot
m_exit
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|done
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|dev-&gt;thread.wq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;thread
dot
m_exit
op_logical_or
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_goto
id|done
suffix:semicolon
id|restart
suffix:colon
id|dev-&gt;thread.scan1
op_assign
id|dev-&gt;thread.scan2
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tvaudio thread scan start [%d]&bslash;n&quot;
comma
id|dev-&gt;thread.scan1
)paren
suffix:semicolon
id|dev-&gt;tvaudio
op_assign
l_int|NULL
suffix:semicolon
id|tvaudio_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;automute
op_assign
l_int|1
suffix:semicolon
id|saa7134_tvaudio_setmute
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* give the tuner some time */
r_if
c_cond
(paren
id|tvaudio_sleep
c_func
(paren
id|dev
comma
id|HZ
op_div
l_int|2
)paren
)paren
r_goto
id|restart
suffix:semicolon
multiline_comment|/* find the main carrier */
id|carr_scan
op_assign
id|carr_default
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tvnorm-&gt;id
op_amp
id|V4L2_STD_PAL
)paren
id|carr_scan
op_assign
id|carr_pal
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tvnorm-&gt;id
op_amp
id|V4L2_STD_NTSC
)paren
id|carr_scan
op_assign
id|carr_ntsc
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tvnorm-&gt;id
op_amp
id|V4L2_STD_SECAM
)paren
id|carr_scan
op_assign
id|carr_secam
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_MONITOR_SELECT
comma
l_int|0x00
)paren
suffix:semicolon
id|tvaudio_setmode
c_func
(paren
id|dev
comma
op_amp
id|tvaudio
(braket
l_int|0
)braket
comma
l_int|NULL
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
id|MAX_SCAN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|carr_scan
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
id|carr_vals
(braket
id|i
)braket
op_assign
id|tvaudio_checkcarrier
c_func
(paren
id|dev
comma
id|carr_scan
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;thread.scan1
op_ne
id|dev-&gt;thread.scan2
)paren
r_goto
id|restart
suffix:semicolon
)brace
r_for
c_loop
(paren
id|carrier
op_assign
l_int|0
comma
id|max
op_assign
l_int|0
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_SCAN
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|carr_scan
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|max
OL
id|carr_vals
(braket
id|i
)braket
)paren
(brace
id|max
op_assign
id|carr_vals
(braket
id|i
)braket
suffix:semicolon
id|carrier
op_assign
id|carr_scan
(braket
id|i
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|carrier
)paren
(brace
multiline_comment|/* Oops: autoscan didn&squot;t work for some reason :-/ */
id|printk
c_func
(paren
l_string|&quot;%s/audio: oops: audio carrier scan failed&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|sifdebug_dump_regs
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;found %s main sound carrier @ %d.%03d MHz&bslash;n&quot;
comma
id|dev-&gt;tvnorm-&gt;name
comma
id|carrier
op_div
l_int|1000
comma
id|carrier
op_mod
l_int|1000
)paren
suffix:semicolon
)brace
id|tvaudio_setcarrier
c_func
(paren
id|dev
comma
id|carrier
comma
id|carrier
)paren
suffix:semicolon
id|dev-&gt;automute
op_assign
l_int|0
suffix:semicolon
id|saa7134_tvaudio_setmute
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* find the exact tv audio norm */
r_for
c_loop
(paren
id|audio
op_assign
op_minus
l_int|1
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TVAUDIO
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;tvnorm-&gt;id
op_ne
op_minus
l_int|1
op_logical_and
id|dev-&gt;tvnorm-&gt;id
op_ne
id|tvaudio
(braket
id|i
)braket
dot
id|std
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|tvaudio
(braket
id|i
)braket
dot
id|carr1
op_ne
id|carrier
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_minus
l_int|1
op_eq
id|audio
)paren
id|audio
op_assign
id|i
suffix:semicolon
id|tvaudio_setmode
c_func
(paren
id|dev
comma
op_amp
id|tvaudio
(braket
id|i
)braket
comma
l_string|&quot;trying&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tvaudio_sleep
c_func
(paren
id|dev
comma
id|HZ
)paren
)paren
r_goto
id|restart
suffix:semicolon
r_if
c_cond
(paren
op_minus
l_int|1
op_ne
id|saa7134_tvaudio_getstereo
c_func
(paren
id|dev
comma
op_amp
id|tvaudio
(braket
id|i
)braket
)paren
)paren
(brace
id|audio
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_minus
l_int|1
op_eq
id|audio
)paren
r_continue
suffix:semicolon
id|tvaudio_setmode
c_func
(paren
id|dev
comma
op_amp
id|tvaudio
(braket
id|audio
)braket
comma
l_string|&quot;using&quot;
)paren
suffix:semicolon
id|dev-&gt;tvaudio
op_assign
op_amp
id|tvaudio
(braket
id|audio
)braket
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|tvaudio_sleep
c_func
(paren
id|dev
comma
l_int|3
op_star
id|HZ
)paren
)paren
r_goto
id|restart
suffix:semicolon
id|saa7134_tvaudio_getstereo
c_func
(paren
id|dev
comma
op_amp
id|tvaudio
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
id|done
suffix:colon
id|dev-&gt;thread.task
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;thread.notify
op_ne
l_int|NULL
)paren
(brace
id|up
c_func
(paren
id|dev-&gt;thread.notify
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------------ */
DECL|function|saa7134_tvaudio_init
r_int
id|saa7134_tvaudio_init
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|sem
)paren
suffix:semicolon
multiline_comment|/* enable I2S audio output */
r_if
c_cond
(paren
id|saa7134_boards
(braket
id|dev-&gt;board
)braket
dot
id|i2s_rate
)paren
(brace
r_int
id|rate
op_assign
(paren
l_int|32000
op_eq
id|saa7134_boards
(braket
id|dev-&gt;board
)braket
dot
id|i2s_rate
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0x03
suffix:semicolon
multiline_comment|/* set rate */
id|saa_andorb
c_func
(paren
id|SAA7134_SIF_SAMPLE_FREQ
comma
l_int|0x03
comma
id|rate
)paren
suffix:semicolon
multiline_comment|/* enable I2S output */
id|saa_writeb
c_func
(paren
id|SAA7134_DSP_OUTPUT_SELECT
comma
l_int|0x80
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_I2S_OUTPUT_SELECT
comma
l_int|0x80
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_I2S_OUTPUT_FORMAT
comma
l_int|0x01
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_I2S_OUTPUT_LEVEL
comma
l_int|0x00
)paren
suffix:semicolon
id|saa_writeb
c_func
(paren
id|SAA7134_I2S_AUDIO_OUTPUT
comma
l_int|0x01
)paren
suffix:semicolon
)brace
multiline_comment|/* start tvaudio thread */
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;thread.wq
)paren
suffix:semicolon
id|dev-&gt;thread.notify
op_assign
op_amp
id|sem
suffix:semicolon
id|kernel_thread
c_func
(paren
id|tvaudio_thread
comma
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|dev-&gt;thread.notify
op_assign
l_int|NULL
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;thread.wq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_tvaudio_fini
r_int
id|saa7134_tvaudio_fini
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|sem
)paren
suffix:semicolon
multiline_comment|/* shutdown tvaudio thread */
r_if
c_cond
(paren
id|dev-&gt;thread.task
)paren
(brace
id|dev-&gt;thread.notify
op_assign
op_amp
id|sem
suffix:semicolon
id|dev-&gt;thread
dot
m_exit
op_assign
l_int|1
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;thread.wq
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|dev-&gt;thread.notify
op_assign
l_int|NULL
suffix:semicolon
)brace
id|saa_andorb
c_func
(paren
id|SAA7134_ANALOG_IO_SELECT
comma
l_int|0x07
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* LINE1 */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7134_tvaudio_do_scan
r_int
id|saa7134_tvaudio_do_scan
c_func
(paren
r_struct
id|saa7134_dev
op_star
id|dev
)paren
(brace
id|dev-&gt;thread.scan2
op_increment
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;thread.wq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------- */
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
