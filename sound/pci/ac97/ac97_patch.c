multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.2&n; *  by Intel Corporation (http://developer.intel.com).&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/pcm.h&gt;
macro_line|#include &lt;sound/ac97_codec.h&gt;
macro_line|#include &lt;sound/asoundef.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &quot;ac97_patch.h&quot;
multiline_comment|/*&n; *  Chip specific initialization&n; */
DECL|function|patch_yamaha_ymf753
r_int
id|patch_yamaha_ymf753
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
multiline_comment|/* Patch for Yamaha YMF753, Copyright (c) by David Shust, dshust@shustring.com.&n;&t;   This chip has nonstandard and extended behaviour with regard to its S/PDIF output.&n;&t;   The AC&squot;97 spec states that the S/PDIF signal is to be output at pin 48.&n;&t;   The YMF753 will ouput the S/PDIF signal to pin 43, 47 (EAPD), or 48.&n;&t;   By default, no output pin is selected, and the S/PDIF signal is not output.&n;&t;   There is also a bit to mute S/PDIF output in a vendor-specific register.&n;&t;*/
id|ac97-&gt;caps
op_or_assign
id|AC97_BC_BASS_TREBLE
suffix:semicolon
id|ac97-&gt;caps
op_or_assign
l_int|0x04
op_lshift
l_int|10
suffix:semicolon
multiline_comment|/* Yamaha 3D enhancement */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_wolfson00
r_int
id|patch_wolfson00
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
multiline_comment|/* This sequence is suspect because it was designed for&n;&t;   the WM9704, and is known to fail when applied to the&n;&t;   WM9707.  If you&squot;re having trouble initializing a&n;&t;   WM9700, this is the place to start looking.&n;&t;   Randolph Bentson &lt;bentson@holmsjoen.com&gt; */
singleline_comment|// WM9701A
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x72
comma
l_int|0x0808
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x74
comma
l_int|0x0808
)paren
suffix:semicolon
singleline_comment|// patch for DVD noise
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x5a
comma
l_int|0x0200
)paren
suffix:semicolon
singleline_comment|// init vol
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x70
comma
l_int|0x0808
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SURROUND_MASTER
comma
l_int|0x0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_wolfson03
r_int
id|patch_wolfson03
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
multiline_comment|/* This is known to work for the ViewSonic ViewPad 1000&n;&t;   Randolph Bentson &lt;bentson@holmsjoen.com&gt; */
singleline_comment|// WM9703/9707
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x72
comma
l_int|0x0808
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x20
comma
l_int|0x8000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_wolfson04
r_int
id|patch_wolfson04
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
singleline_comment|// WM9704
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x72
comma
l_int|0x0808
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x74
comma
l_int|0x0808
)paren
suffix:semicolon
singleline_comment|// patch for DVD noise
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x5a
comma
l_int|0x0200
)paren
suffix:semicolon
singleline_comment|// init vol
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x70
comma
l_int|0x0808
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SURROUND_MASTER
comma
l_int|0x0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_tritech_tr28028
r_int
id|patch_tritech_tr28028
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x26
comma
l_int|0x0300
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
l_int|0x26
comma
l_int|0x0000
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SURROUND_MASTER
comma
l_int|0x0000
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SPDIF
comma
l_int|0x0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_sigmatel_stac9708
r_int
id|patch_sigmatel_stac9708
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_int
r_int
id|codec72
comma
id|codec6c
suffix:semicolon
id|codec72
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS2
)paren
op_amp
l_int|0x8000
suffix:semicolon
id|codec6c
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_ANALOG
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|codec72
op_eq
l_int|0
)paren
op_logical_and
(paren
id|codec6c
op_eq
l_int|0
)paren
)paren
(brace
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC2
comma
l_int|0x1000
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS2
comma
l_int|0x0007
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|codec72
op_eq
l_int|0x8000
)paren
op_logical_and
(paren
id|codec6c
op_eq
l_int|0
)paren
)paren
(brace
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC2
comma
l_int|0x1001
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_DAC2INVERT
comma
l_int|0x0008
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|codec72
op_eq
l_int|0x8000
)paren
op_logical_and
(paren
id|codec6c
op_eq
l_int|0x0080
)paren
)paren
(brace
multiline_comment|/* nothing */
)brace
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_MULTICHN
comma
l_int|0x0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_sigmatel_stac9721
r_int
id|patch_sigmatel_stac9721
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_if
c_cond
(paren
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_ANALOG
)paren
op_eq
l_int|0
)paren
(brace
singleline_comment|// patch for SigmaTel
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC2
comma
l_int|0x4000
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS2
comma
l_int|0x0002
)paren
suffix:semicolon
)brace
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_MULTICHN
comma
l_int|0x0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_sigmatel_stac9744
r_int
id|patch_sigmatel_stac9744
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
singleline_comment|// patch for SigmaTel
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC2
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* is this correct? --jk */
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS2
comma
l_int|0x0002
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_MULTICHN
comma
l_int|0x0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_sigmatel_stac9756
r_int
id|patch_sigmatel_stac9756
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
singleline_comment|// patch for SigmaTel
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_CIC2
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* is this correct? --jk */
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS1
comma
l_int|0xabba
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_BIAS2
comma
l_int|0x0002
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_SIGMATEL_MULTICHN
comma
l_int|0x0000
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_cirrus_spdif
r_int
id|patch_cirrus_spdif
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
multiline_comment|/* Basically, the cs4201/cs4205/cs4297a has non-standard sp/dif registers.&n;&t;   WHY CAN&squot;T ANYONE FOLLOW THE BLOODY SPEC?  *sigh*&n;&t;   - sp/dif EA ID is not set, but sp/dif is always present.&n;&t;   - enable/disable is spdif register bit 15.&n;&t;   - sp/dif control register is 0x68.  differs from AC97:&n;&t;   - valid is bit 14 (vs 15)&n;&t;   - no DRS&n;&t;   - only 44.1/48k [00 = 48, 01=44,1] (AC97 is 00=44.1, 10=48)&n;&t;   - sp/dif ssource select is in 0x5e bits 0,1.&n;&t;*/
id|ac97-&gt;flags
op_or_assign
id|AC97_CS_SPDIF
suffix:semicolon
id|ac97-&gt;rates
(braket
id|AC97_RATES_SPDIF
)braket
op_and_assign
op_complement
id|SNDRV_PCM_RATE_32000
suffix:semicolon
id|ac97-&gt;ext_id
op_or_assign
id|AC97_EI_SPDIF
suffix:semicolon
multiline_comment|/* force the detection of spdif */
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_CSR_ACMODE
comma
l_int|0x0080
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_cirrus_cs4299
r_int
id|patch_cirrus_cs4299
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
multiline_comment|/* force the detection of PC Beep */
id|ac97-&gt;flags
op_or_assign
id|AC97_HAS_PC_BEEP
suffix:semicolon
r_return
id|patch_cirrus_spdif
c_func
(paren
id|ac97
)paren
suffix:semicolon
)brace
DECL|function|patch_conexant
r_int
id|patch_conexant
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
id|ac97-&gt;flags
op_or_assign
id|AC97_CX_SPDIF
suffix:semicolon
id|ac97-&gt;ext_id
op_or_assign
id|AC97_EI_SPDIF
suffix:semicolon
multiline_comment|/* force the detection of spdif */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_ad1819
r_int
id|patch_ad1819
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
singleline_comment|// patch for Analog Devices
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
l_int|0x7000
)paren
suffix:semicolon
multiline_comment|/* select all codecs */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_ad1881_unchained
r_static
r_int
r_int
id|patch_ad1881_unchained
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
id|idx
comma
r_int
r_int
id|mask
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
singleline_comment|// test for unchained codec
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
id|mask
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_CODEC_CFG
comma
l_int|0x0000
)paren
suffix:semicolon
multiline_comment|/* ID0C, ID1C, SDIE = off */
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_VENDOR_ID2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
l_int|0xff40
)paren
op_ne
l_int|0x5340
)paren
r_return
l_int|0
suffix:semicolon
id|ac97-&gt;spec.ad18xx.unchained
(braket
id|idx
)braket
op_assign
id|mask
suffix:semicolon
id|ac97-&gt;spec.ad18xx.id
(braket
id|idx
)braket
op_assign
id|val
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|patch_ad1881_chained1
r_static
r_int
id|patch_ad1881_chained1
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
id|idx
comma
r_int
r_int
id|codec_bits
)paren
(brace
r_static
r_int
id|cfg_bits
(braket
l_int|3
)braket
op_assign
(brace
l_int|1
op_lshift
l_int|12
comma
l_int|1
op_lshift
l_int|14
comma
l_int|1
op_lshift
l_int|13
)brace
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
id|cfg_bits
(braket
id|idx
)braket
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_CODEC_CFG
comma
l_int|0x0004
)paren
suffix:semicolon
singleline_comment|// SDIE
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_VENDOR_ID2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|val
op_amp
l_int|0xff40
)paren
op_ne
l_int|0x5340
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|codec_bits
)paren
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_CODEC_CFG
comma
id|codec_bits
)paren
suffix:semicolon
id|ac97-&gt;spec.ad18xx.chained
(braket
id|idx
)braket
op_assign
id|cfg_bits
(braket
id|idx
)braket
suffix:semicolon
id|ac97-&gt;spec.ad18xx.id
(braket
id|idx
)braket
op_assign
id|val
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|patch_ad1881_chained
r_static
r_void
id|patch_ad1881_chained
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
r_int
id|unchained_idx
comma
r_int
id|cidx1
comma
r_int
id|cidx2
)paren
(brace
singleline_comment|// already detected?
r_if
c_cond
(paren
id|ac97-&gt;spec.ad18xx.unchained
(braket
id|cidx1
)braket
op_logical_or
id|ac97-&gt;spec.ad18xx.chained
(braket
id|cidx1
)braket
)paren
id|cidx1
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;spec.ad18xx.unchained
(braket
id|cidx2
)braket
op_logical_or
id|ac97-&gt;spec.ad18xx.chained
(braket
id|cidx2
)braket
)paren
id|cidx2
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cidx1
OL
l_int|0
op_logical_and
id|cidx2
OL
l_int|0
)paren
r_return
suffix:semicolon
singleline_comment|// test for chained codecs
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
id|ac97-&gt;spec.ad18xx.unchained
(braket
id|unchained_idx
)braket
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_CODEC_CFG
comma
l_int|0x0002
)paren
suffix:semicolon
singleline_comment|// ID1C
r_if
c_cond
(paren
id|cidx1
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|patch_ad1881_chained1
c_func
(paren
id|ac97
comma
id|cidx1
comma
l_int|0x0006
)paren
)paren
singleline_comment|// SDIE | ID1C
id|patch_ad1881_chained1
c_func
(paren
id|ac97
comma
id|cidx2
comma
l_int|0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|patch_ad1881_chained1
c_func
(paren
id|ac97
comma
id|cidx2
comma
l_int|0x0006
)paren
)paren
singleline_comment|// SDIE | ID1C
id|patch_ad1881_chained1
c_func
(paren
id|ac97
comma
id|cidx1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cidx2
op_ge
l_int|0
)paren
(brace
id|patch_ad1881_chained1
c_func
(paren
id|ac97
comma
id|cidx2
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|patch_ad1881
r_int
id|patch_ad1881
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_static
r_const
r_char
id|cfg_idxs
(braket
l_int|3
)braket
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|2
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|2
)brace
comma
(brace
l_int|0
comma
l_int|1
)brace
)brace
suffix:semicolon
singleline_comment|// patch for Analog Devices
r_int
r_int
id|codecs
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|idx
comma
id|num
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|ac97-&gt;spec.ad18xx.mutex
)paren
suffix:semicolon
id|codecs
(braket
l_int|0
)braket
op_assign
id|patch_ad1881_unchained
c_func
(paren
id|ac97
comma
l_int|0
comma
(paren
l_int|1
op_lshift
l_int|12
)paren
)paren
suffix:semicolon
id|codecs
(braket
l_int|1
)braket
op_assign
id|patch_ad1881_unchained
c_func
(paren
id|ac97
comma
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|14
)paren
)paren
suffix:semicolon
id|codecs
(braket
l_int|2
)braket
op_assign
id|patch_ad1881_unchained
c_func
(paren
id|ac97
comma
l_int|2
comma
(paren
l_int|1
op_lshift
l_int|13
)paren
)paren
suffix:semicolon
id|snd_runtime_check
c_func
(paren
id|codecs
(braket
l_int|0
)braket
op_or
id|codecs
(braket
l_int|1
)braket
op_or
id|codecs
(braket
l_int|2
)braket
comma
r_goto
id|__end
)paren
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
l_int|3
suffix:semicolon
id|idx
op_increment
)paren
r_if
c_cond
(paren
id|ac97-&gt;spec.ad18xx.unchained
(braket
id|idx
)braket
)paren
id|patch_ad1881_chained
c_func
(paren
id|ac97
comma
id|idx
comma
id|cfg_idxs
(braket
id|idx
)braket
(braket
l_int|0
)braket
comma
id|cfg_idxs
(braket
id|idx
)braket
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;spec.ad18xx.id
(braket
l_int|1
)braket
)paren
(brace
id|ac97-&gt;flags
op_or_assign
id|AC97_AD_MULTI
suffix:semicolon
id|ac97-&gt;scaps
op_or_assign
id|AC97_SCAP_SURROUND_DAC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ac97-&gt;spec.ad18xx.id
(braket
l_int|2
)braket
)paren
(brace
id|ac97-&gt;flags
op_or_assign
id|AC97_AD_MULTI
suffix:semicolon
id|ac97-&gt;scaps
op_or_assign
id|AC97_SCAP_CENTER_LFE_DAC
suffix:semicolon
)brace
id|__end
suffix:colon
multiline_comment|/* select all codecs */
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
l_int|0x7000
)paren
suffix:semicolon
multiline_comment|/* check if only one codec is present */
r_for
c_loop
(paren
id|idx
op_assign
id|num
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|3
suffix:semicolon
id|idx
op_increment
)paren
r_if
c_cond
(paren
id|ac97-&gt;spec.ad18xx.id
(braket
id|idx
)braket
)paren
id|num
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|num
op_eq
l_int|1
)paren
(brace
multiline_comment|/* ok, deselect all ID bits */
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_CODEC_CFG
comma
l_int|0x0000
)paren
suffix:semicolon
)brace
multiline_comment|/* required for AD1886/AD1885 combination */
id|ac97-&gt;ext_id
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_ID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;spec.ad18xx.id
(braket
l_int|0
)braket
)paren
(brace
id|ac97-&gt;id
op_and_assign
l_int|0xffff0000
suffix:semicolon
id|ac97-&gt;id
op_or_assign
id|ac97-&gt;spec.ad18xx.id
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_ad1885
r_int
id|patch_ad1885
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_int
r_int
id|jack
suffix:semicolon
id|patch_ad1881
c_func
(paren
id|ac97
)paren
suffix:semicolon
multiline_comment|/* This is required to deal with the Intel D815EEAL2 */
multiline_comment|/* i.e. Line out is actually headphone out from codec */
multiline_comment|/* turn off jack sense bits D8 &amp; D9 */
id|jack
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_AD_JACK_SPDIF
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_JACK_SPDIF
comma
id|jack
op_or
l_int|0x0300
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_ad1886
r_int
id|patch_ad1886
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
id|patch_ad1881
c_func
(paren
id|ac97
)paren
suffix:semicolon
multiline_comment|/* Presario700 workaround */
multiline_comment|/* for Jack Sense/SPDIF Register misetting causing */
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_JACK_SPDIF
comma
l_int|0x0010
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_ad1980
r_int
id|patch_ad1980
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
r_int
r_int
id|misc
suffix:semicolon
id|patch_ad1881
c_func
(paren
id|ac97
)paren
suffix:semicolon
multiline_comment|/* Switch FRONT/SURROUND LINE-OUT/HP-OUT default connection */
multiline_comment|/* it seems that most vendors connect line-out connector to headphone out of AC&squot;97 */
id|misc
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_AD_MISC
)paren
suffix:semicolon
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_AD_MISC
comma
id|misc
op_or
l_int|0x0420
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|patch_alc650
r_int
id|patch_alc650
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
multiline_comment|/* enable spdif in */
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|AC97_ALC650_CLOCK
comma
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_ALC650_CLOCK
)paren
op_or
l_int|0x03
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
