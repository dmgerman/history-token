multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Universal interface for Audio Codec &squot;97&n; *&n; *  For more details look to AC &squot;97 component specification revision 2.2&n; *  by Intel Corporation (http://developer.intel.com).&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/ac97_codec.h&gt;
macro_line|#include &lt;sound/asoundef.h&gt;
macro_line|#include &quot;ac97_local.h&quot;
macro_line|#include &quot;ac97_id.h&quot;
multiline_comment|/*&n; * proc interface&n; */
DECL|function|snd_ac97_proc_read_functions
r_static
r_void
id|snd_ac97_proc_read_functions
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
r_int
id|header
op_assign
l_int|0
comma
id|function
suffix:semicolon
r_int
r_int
id|info
comma
id|sense_info
suffix:semicolon
r_static
r_const
r_char
op_star
id|function_names
(braket
l_int|12
)braket
op_assign
(brace
l_string|&quot;Master Out&quot;
comma
l_string|&quot;AUX Out&quot;
comma
l_string|&quot;Center/LFE Out&quot;
comma
l_string|&quot;SPDIF Out&quot;
comma
l_string|&quot;Phone In&quot;
comma
l_string|&quot;Mic 1&quot;
comma
l_string|&quot;Mic 2&quot;
comma
l_string|&quot;Line In&quot;
comma
l_string|&quot;CD In&quot;
comma
l_string|&quot;Video In&quot;
comma
l_string|&quot;Aux In&quot;
comma
l_string|&quot;Mono Out&quot;
)brace
suffix:semicolon
r_static
r_const
r_char
op_star
id|locations
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;Rear I/O Panel&quot;
comma
l_string|&quot;Front Panel&quot;
comma
l_string|&quot;Motherboard&quot;
comma
l_string|&quot;Dock/External&quot;
comma
l_string|&quot;reserved&quot;
comma
l_string|&quot;reserved&quot;
comma
l_string|&quot;reserved&quot;
comma
l_string|&quot;NC/unused&quot;
)brace
suffix:semicolon
r_for
c_loop
(paren
id|function
op_assign
l_int|0
suffix:semicolon
id|function
OL
l_int|12
suffix:semicolon
op_increment
id|function
)paren
(brace
id|snd_ac97_write
c_func
(paren
id|ac97
comma
id|AC97_FUNC_SELECT
comma
id|function
op_lshift
l_int|1
)paren
suffix:semicolon
id|info
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_FUNC_INFO
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|info
op_amp
l_int|0x0001
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|header
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;n                    Gain     Inverted  Buffer delay  Location&bslash;n&quot;
)paren
suffix:semicolon
id|header
op_assign
l_int|1
suffix:semicolon
)brace
id|sense_info
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_SENSE_INFO
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%-17s: %3d.%d dBV    %c      %2d/fs         %s&bslash;n&quot;
comma
id|function_names
(braket
id|function
)braket
comma
(paren
id|info
op_amp
l_int|0x8000
ques
c_cond
op_minus
l_int|1
suffix:colon
l_int|1
)paren
op_star
(paren
(paren
id|info
op_amp
l_int|0x7000
)paren
op_rshift
l_int|12
)paren
op_star
l_int|3
op_div
l_int|2
comma
(paren
(paren
id|info
op_amp
l_int|0x0800
)paren
op_rshift
l_int|11
)paren
op_star
l_int|5
comma
id|info
op_amp
l_int|0x0400
ques
c_cond
l_char|&squot;X&squot;
suffix:colon
l_char|&squot;-&squot;
comma
(paren
id|info
op_amp
l_int|0x03e0
)paren
op_rshift
l_int|5
comma
id|locations
(braket
id|sense_info
op_rshift
l_int|13
)braket
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_ac97_proc_read_main
r_static
r_void
id|snd_ac97_proc_read_main
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
id|snd_info_buffer_t
op_star
id|buffer
comma
r_int
id|subidx
)paren
(brace
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
r_int
r_int
id|val
comma
id|tmp
comma
id|ext
comma
id|mext
suffix:semicolon
r_static
r_const
r_char
op_star
id|spdif_slots
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot; SPDIF=3/4&quot;
comma
l_string|&quot; SPDIF=7/8&quot;
comma
l_string|&quot; SPDIF=6/9&quot;
comma
l_string|&quot; SPDIF=res&quot;
)brace
suffix:semicolon
r_static
r_const
r_char
op_star
id|spdif_rates
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot; Rate=44.1kHz&quot;
comma
l_string|&quot; Rate=res&quot;
comma
l_string|&quot; Rate=48kHz&quot;
comma
l_string|&quot; Rate=32kHz&quot;
)brace
suffix:semicolon
r_static
r_const
r_char
op_star
id|spdif_rates_cs4205
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot; Rate=48kHz&quot;
comma
l_string|&quot; Rate=44.1kHz&quot;
comma
l_string|&quot; Rate=res&quot;
comma
l_string|&quot; Rate=res&quot;
)brace
suffix:semicolon
id|snd_ac97_get_name
c_func
(paren
l_int|NULL
comma
id|ac97-&gt;id
comma
id|name
comma
l_int|0
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d-%d/%d: %s&bslash;n&bslash;n&quot;
comma
id|ac97-&gt;addr
comma
id|ac97-&gt;num
comma
id|subidx
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ac97-&gt;scaps
op_amp
id|AC97_SCAP_AUDIO
)paren
op_eq
l_int|0
)paren
r_goto
id|__modem
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_REV_MASK
)paren
op_ge
id|AC97_EI_REV_23
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_INT_PAGING
)paren
suffix:semicolon
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_INT_PAGING
comma
id|AC97_PAGE_MASK
comma
id|AC97_PAGE_1
)paren
suffix:semicolon
id|tmp
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_CODEC_CLASS_REV
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Revision         : 0x%02x&bslash;n&quot;
comma
id|tmp
op_amp
l_int|0xff
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Compat. Class    : 0x%02x&bslash;n&quot;
comma
(paren
id|tmp
op_rshift
l_int|8
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Subsys. Vendor ID: 0x%04x&bslash;n&quot;
comma
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_PCI_SVID
)paren
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Subsys. ID       : 0x%04x&bslash;n&bslash;n&quot;
comma
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_PCI_SID
)paren
)paren
suffix:semicolon
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_INT_PAGING
comma
id|AC97_PAGE_MASK
comma
id|val
op_amp
id|AC97_PAGE_MASK
)paren
suffix:semicolon
)brace
singleline_comment|// val = snd_ac97_read(ac97, AC97_RESET);
id|val
op_assign
id|ac97-&gt;caps
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Capabilities     :%s%s%s%s%s%s&bslash;n&quot;
comma
id|val
op_amp
id|AC97_BC_DEDICATED_MIC
ques
c_cond
l_string|&quot; -dedicated MIC PCM IN channel-&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_BC_RESERVED1
ques
c_cond
l_string|&quot; -reserved1-&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_BC_BASS_TREBLE
ques
c_cond
l_string|&quot; -bass &amp; treble-&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_BC_SIM_STEREO
ques
c_cond
l_string|&quot; -simulated stereo-&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_BC_HEADPHONE
ques
c_cond
l_string|&quot; -headphone out-&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_BC_LOUDNESS
ques
c_cond
l_string|&quot; -loudness-&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|tmp
op_assign
id|ac97-&gt;caps
op_amp
id|AC97_BC_DAC_MASK
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;DAC resolution   : %s%s%s%s&bslash;n&quot;
comma
id|tmp
op_eq
id|AC97_BC_16BIT_DAC
ques
c_cond
l_string|&quot;16-bit&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tmp
op_eq
id|AC97_BC_18BIT_DAC
ques
c_cond
l_string|&quot;18-bit&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tmp
op_eq
id|AC97_BC_20BIT_DAC
ques
c_cond
l_string|&quot;20-bit&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tmp
op_eq
id|AC97_BC_DAC_MASK
ques
c_cond
l_string|&quot;???&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|tmp
op_assign
id|ac97-&gt;caps
op_amp
id|AC97_BC_ADC_MASK
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;ADC resolution   : %s%s%s%s&bslash;n&quot;
comma
id|tmp
op_eq
id|AC97_BC_16BIT_ADC
ques
c_cond
l_string|&quot;16-bit&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tmp
op_eq
id|AC97_BC_18BIT_ADC
ques
c_cond
l_string|&quot;18-bit&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tmp
op_eq
id|AC97_BC_20BIT_ADC
ques
c_cond
l_string|&quot;20-bit&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|tmp
op_eq
id|AC97_BC_ADC_MASK
ques
c_cond
l_string|&quot;???&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;3D enhancement   : %s&bslash;n&quot;
comma
id|snd_ac97_stereo_enhancements
(braket
(paren
id|val
op_rshift
l_int|10
)paren
op_amp
l_int|0x1f
)braket
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;nCurrent setup&bslash;n&quot;
)paren
suffix:semicolon
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_MIC
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Mic gain         : %s [%s]&bslash;n&quot;
comma
id|val
op_amp
l_int|0x0040
ques
c_cond
l_string|&quot;+20dB&quot;
suffix:colon
l_string|&quot;+0dB&quot;
comma
id|ac97-&gt;regs
(braket
id|AC97_MIC
)braket
op_amp
l_int|0x0040
ques
c_cond
l_string|&quot;+20dB&quot;
suffix:colon
l_string|&quot;+0dB&quot;
)paren
suffix:semicolon
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_GENERAL_PURPOSE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;POP path         : %s 3D&bslash;n&quot;
l_string|&quot;Sim. stereo      : %s&bslash;n&quot;
l_string|&quot;3D enhancement   : %s&bslash;n&quot;
l_string|&quot;Loudness         : %s&bslash;n&quot;
l_string|&quot;Mono output      : %s&bslash;n&quot;
l_string|&quot;Mic select       : %s&bslash;n&quot;
l_string|&quot;ADC/DAC loopback : %s&bslash;n&quot;
comma
id|val
op_amp
l_int|0x8000
ques
c_cond
l_string|&quot;post&quot;
suffix:colon
l_string|&quot;pre&quot;
comma
id|val
op_amp
l_int|0x4000
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
comma
id|val
op_amp
l_int|0x2000
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
comma
id|val
op_amp
l_int|0x1000
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
comma
id|val
op_amp
l_int|0x0200
ques
c_cond
l_string|&quot;Mic&quot;
suffix:colon
l_string|&quot;MIX&quot;
comma
id|val
op_amp
l_int|0x0100
ques
c_cond
l_string|&quot;Mic2&quot;
suffix:colon
l_string|&quot;Mic1&quot;
comma
id|val
op_amp
l_int|0x0080
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|ext
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
id|ext
op_eq
l_int|0
)paren
r_goto
id|__modem
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Extended ID      : codec=%i rev=%i%s%s%s%s DSA=%i%s%s%s%s&bslash;n&quot;
comma
(paren
id|ext
op_amp
id|AC97_EI_ADDR_MASK
)paren
op_rshift
id|AC97_EI_ADDR_SHIFT
comma
(paren
id|ext
op_amp
id|AC97_EI_REV_MASK
)paren
op_rshift
id|AC97_EI_REV_SHIFT
comma
id|ext
op_amp
id|AC97_EI_AMAP
ques
c_cond
l_string|&quot; AMAP&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ext
op_amp
id|AC97_EI_LDAC
ques
c_cond
l_string|&quot; LDAC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ext
op_amp
id|AC97_EI_SDAC
ques
c_cond
l_string|&quot; SDAC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ext
op_amp
id|AC97_EI_CDAC
ques
c_cond
l_string|&quot; CDAC&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|ext
op_amp
id|AC97_EI_DACS_SLOT_MASK
)paren
op_rshift
id|AC97_EI_DACS_SLOT_SHIFT
comma
id|ext
op_amp
id|AC97_EI_VRM
ques
c_cond
l_string|&quot; VRM&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ext
op_amp
id|AC97_EI_SPDIF
ques
c_cond
l_string|&quot; SPDIF&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ext
op_amp
id|AC97_EI_DRA
ques
c_cond
l_string|&quot; DRA&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ext
op_amp
id|AC97_EI_VRA
ques
c_cond
l_string|&quot; VRA&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_STATUS
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Extended status  :%s%s%s%s%s%s%s%s%s%s%s%s%s%s&bslash;n&quot;
comma
id|val
op_amp
id|AC97_EA_PRL
ques
c_cond
l_string|&quot; PRL&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_PRK
ques
c_cond
l_string|&quot; PRK&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_PRJ
ques
c_cond
l_string|&quot; PRJ&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_PRI
ques
c_cond
l_string|&quot; PRI&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_SPCV
ques
c_cond
l_string|&quot; SPCV&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_MDAC
ques
c_cond
l_string|&quot; MADC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_LDAC
ques
c_cond
l_string|&quot; LDAC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_SDAC
ques
c_cond
l_string|&quot; SDAC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_CDAC
ques
c_cond
l_string|&quot; CDAC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|ext
op_amp
id|AC97_EI_SPDIF
ques
c_cond
id|spdif_slots
(braket
(paren
id|val
op_amp
id|AC97_EA_SPSA_SLOT_MASK
)paren
op_rshift
id|AC97_EA_SPSA_SLOT_SHIFT
)braket
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_VRM
ques
c_cond
l_string|&quot; VRM&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_SPDIF
ques
c_cond
l_string|&quot; SPDIF&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_DRA
ques
c_cond
l_string|&quot; DRA&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_EA_VRA
ques
c_cond
l_string|&quot; VRA&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ext
op_amp
id|AC97_EI_VRA
)paren
(brace
multiline_comment|/* VRA */
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_PCM_FRONT_DAC_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;PCM front DAC    : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ext
op_amp
id|AC97_EI_SDAC
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_PCM_SURR_DAC_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;PCM Surr DAC     : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ext
op_amp
id|AC97_EI_LDAC
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_PCM_LFE_DAC_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;PCM LFE DAC      : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_PCM_LR_ADC_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;PCM ADC          : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ext
op_amp
id|AC97_EI_VRM
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_PCM_MIC_ADC_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;PCM MIC ADC      : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ext
op_amp
id|AC97_EI_SPDIF
)paren
op_logical_or
(paren
id|ac97-&gt;flags
op_amp
id|AC97_CS_SPDIF
)paren
)paren
(brace
r_if
c_cond
(paren
id|ac97-&gt;flags
op_amp
id|AC97_CS_SPDIF
)paren
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_CSR_SPDIF
)paren
suffix:semicolon
r_else
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_SPDIF
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;SPDIF Control    :%s%s%s%s Category=0x%x Generation=%i%s%s%s&bslash;n&quot;
comma
id|val
op_amp
id|AC97_SC_PRO
ques
c_cond
l_string|&quot; PRO&quot;
suffix:colon
l_string|&quot; Consumer&quot;
comma
id|val
op_amp
id|AC97_SC_NAUDIO
ques
c_cond
l_string|&quot; Non-audio&quot;
suffix:colon
l_string|&quot; PCM&quot;
comma
id|val
op_amp
id|AC97_SC_COPY
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; Copyright&quot;
comma
id|val
op_amp
id|AC97_SC_PRE
ques
c_cond
l_string|&quot; Preemph50/15&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|val
op_amp
id|AC97_SC_CC_MASK
)paren
op_rshift
id|AC97_SC_CC_SHIFT
comma
(paren
id|val
op_amp
id|AC97_SC_L
)paren
op_rshift
l_int|11
comma
(paren
id|ac97-&gt;flags
op_amp
id|AC97_CS_SPDIF
)paren
ques
c_cond
id|spdif_rates_cs4205
(braket
(paren
id|val
op_amp
id|AC97_SC_SPSR_MASK
)paren
op_rshift
id|AC97_SC_SPSR_SHIFT
)braket
suffix:colon
id|spdif_rates
(braket
(paren
id|val
op_amp
id|AC97_SC_SPSR_MASK
)paren
op_rshift
id|AC97_SC_SPSR_SHIFT
)braket
comma
(paren
id|ac97-&gt;flags
op_amp
id|AC97_CS_SPDIF
)paren
ques
c_cond
(paren
id|val
op_amp
id|AC97_SC_DRS
ques
c_cond
l_string|&quot; Validity&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:colon
(paren
id|val
op_amp
id|AC97_SC_DRS
ques
c_cond
l_string|&quot; DRS&quot;
suffix:colon
l_string|&quot;&quot;
)paren
comma
(paren
id|ac97-&gt;flags
op_amp
id|AC97_CS_SPDIF
)paren
ques
c_cond
(paren
id|val
op_amp
id|AC97_SC_V
ques
c_cond
l_string|&quot; Enabled&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:colon
(paren
id|val
op_amp
id|AC97_SC_V
ques
c_cond
l_string|&quot; Validity&quot;
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* ALC650 specific*/
r_if
c_cond
(paren
(paren
id|ac97-&gt;id
op_amp
l_int|0xfffffff0
)paren
op_eq
l_int|0x414c4720
op_logical_and
(paren
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_ALC650_CLOCK
)paren
op_amp
l_int|0x01
)paren
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_ALC650_SPDIF_INPUT_STATUS2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|AC97_ALC650_CLOCK_LOCK
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_ALC650_SPDIF_INPUT_STATUS1
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;SPDIF In Status  :%s%s%s%s Category=0x%x Generation=%i&quot;
comma
id|val
op_amp
id|AC97_ALC650_PRO
ques
c_cond
l_string|&quot; PRO&quot;
suffix:colon
l_string|&quot; Consumer&quot;
comma
id|val
op_amp
id|AC97_ALC650_NAUDIO
ques
c_cond
l_string|&quot; Non-audio&quot;
suffix:colon
l_string|&quot; PCM&quot;
comma
id|val
op_amp
id|AC97_ALC650_COPY
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot; Copyright&quot;
comma
id|val
op_amp
id|AC97_ALC650_PRE
ques
c_cond
l_string|&quot; Preemph50/15&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|val
op_amp
id|AC97_ALC650_CC_MASK
)paren
op_rshift
id|AC97_ALC650_CC_SHIFT
comma
(paren
id|val
op_amp
id|AC97_ALC650_L
)paren
op_rshift
l_int|15
)paren
suffix:semicolon
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_ALC650_SPDIF_INPUT_STATUS2
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s Accuracy=%i%s%s&bslash;n&quot;
comma
id|spdif_rates
(braket
(paren
id|val
op_amp
id|AC97_ALC650_SPSR_MASK
)paren
op_rshift
id|AC97_ALC650_SPSR_SHIFT
)braket
comma
(paren
id|val
op_amp
id|AC97_ALC650_CLOCK_ACCURACY
)paren
op_rshift
id|AC97_ALC650_CLOCK_SHIFT
comma
(paren
id|val
op_amp
id|AC97_ALC650_CLOCK_LOCK
ques
c_cond
l_string|&quot; Locked&quot;
suffix:colon
l_string|&quot; Unlocked&quot;
)paren
comma
(paren
id|val
op_amp
id|AC97_ALC650_V
ques
c_cond
l_string|&quot; Validity?&quot;
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;SPDIF In Status  : Not Locked&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
(paren
id|ac97-&gt;ext_id
op_amp
id|AC97_EI_REV_MASK
)paren
op_ge
id|AC97_EI_REV_23
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_INT_PAGING
)paren
suffix:semicolon
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_INT_PAGING
comma
id|AC97_PAGE_MASK
comma
id|AC97_PAGE_1
)paren
suffix:semicolon
id|snd_ac97_proc_read_functions
c_func
(paren
id|ac97
comma
id|buffer
)paren
suffix:semicolon
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_INT_PAGING
comma
id|AC97_PAGE_MASK
comma
id|val
op_amp
id|AC97_PAGE_MASK
)paren
suffix:semicolon
)brace
id|__modem
suffix:colon
id|mext
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_MID
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mext
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Extended modem ID: codec=%i%s%s%s%s%s&bslash;n&quot;
comma
(paren
id|mext
op_amp
id|AC97_MEI_ADDR_MASK
)paren
op_rshift
id|AC97_MEI_ADDR_SHIFT
comma
id|mext
op_amp
id|AC97_MEI_CID2
ques
c_cond
l_string|&quot; CID2&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|mext
op_amp
id|AC97_MEI_CID1
ques
c_cond
l_string|&quot; CID1&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|mext
op_amp
id|AC97_MEI_HANDSET
ques
c_cond
l_string|&quot; HSET&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|mext
op_amp
id|AC97_MEI_LINE2
ques
c_cond
l_string|&quot; LIN2&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|mext
op_amp
id|AC97_MEI_LINE1
ques
c_cond
l_string|&quot; LIN1&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_EXTENDED_MSTATUS
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Modem status     :%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s&bslash;n&quot;
comma
id|val
op_amp
id|AC97_MEA_GPIO
ques
c_cond
l_string|&quot; GPIO&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_MREF
ques
c_cond
l_string|&quot; MREF&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_ADC1
ques
c_cond
l_string|&quot; ADC1&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_DAC1
ques
c_cond
l_string|&quot; DAC1&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_ADC2
ques
c_cond
l_string|&quot; ADC2&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_DAC2
ques
c_cond
l_string|&quot; DAC2&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_HADC
ques
c_cond
l_string|&quot; HADC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_HDAC
ques
c_cond
l_string|&quot; HDAC&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRA
ques
c_cond
l_string|&quot; PRA(GPIO)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRB
ques
c_cond
l_string|&quot; PRB(res)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRC
ques
c_cond
l_string|&quot; PRC(ADC1)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRD
ques
c_cond
l_string|&quot; PRD(DAC1)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRE
ques
c_cond
l_string|&quot; PRE(ADC2)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRF
ques
c_cond
l_string|&quot; PRF(DAC2)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRG
ques
c_cond
l_string|&quot; PRG(HADC)&quot;
suffix:colon
l_string|&quot;&quot;
comma
id|val
op_amp
id|AC97_MEA_PRH
ques
c_cond
l_string|&quot; PRH(HDAC)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mext
op_amp
id|AC97_MEI_LINE1
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_LINE1_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Line1 rate       : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mext
op_amp
id|AC97_MEI_LINE2
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_LINE2_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Line2 rate       : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mext
op_amp
id|AC97_MEI_HANDSET
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|AC97_HANDSET_RATE
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Headset rate     : %iHz&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_ac97_proc_read
r_static
r_void
id|snd_ac97_proc_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
id|ac97_t
op_star
id|ac97
op_assign
id|snd_magic_cast
c_func
(paren
id|ac97_t
comma
id|entry-&gt;private_data
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ac97-&gt;id
op_amp
l_int|0xffffff40
)paren
op_eq
id|AC97_ID_AD1881
)paren
(brace
singleline_comment|// Analog Devices AD1881/85/86
r_int
id|idx
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ac97-&gt;spec.ad18xx.mutex
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
id|ac97-&gt;spec.ad18xx.id
(braket
id|idx
)braket
)paren
(brace
multiline_comment|/* select single codec */
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
l_int|0x7000
comma
id|ac97-&gt;spec.ad18xx.unchained
(braket
id|idx
)braket
op_or
id|ac97-&gt;spec.ad18xx.chained
(braket
id|idx
)braket
)paren
suffix:semicolon
id|snd_ac97_proc_read_main
c_func
(paren
id|ac97
comma
id|buffer
comma
id|idx
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* select all codecs */
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
l_int|0x7000
comma
l_int|0x7000
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ac97-&gt;spec.ad18xx.mutex
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;nAD18XX configuration&bslash;n&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Unchained        : 0x%04x,0x%04x,0x%04x&bslash;n&quot;
comma
id|ac97-&gt;spec.ad18xx.unchained
(braket
l_int|0
)braket
comma
id|ac97-&gt;spec.ad18xx.unchained
(braket
l_int|1
)braket
comma
id|ac97-&gt;spec.ad18xx.unchained
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Chained          : 0x%04x,0x%04x,0x%04x&bslash;n&quot;
comma
id|ac97-&gt;spec.ad18xx.chained
(braket
l_int|0
)braket
comma
id|ac97-&gt;spec.ad18xx.chained
(braket
l_int|1
)braket
comma
id|ac97-&gt;spec.ad18xx.chained
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_ac97_proc_read_main
c_func
(paren
id|ac97
comma
id|buffer
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SND_DEBUG
multiline_comment|/* direct register write for debugging */
DECL|function|snd_ac97_proc_regs_write
r_static
r_void
id|snd_ac97_proc_regs_write
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
id|ac97_t
op_star
id|ac97
op_assign
id|snd_magic_cast
c_func
(paren
id|ac97_t
comma
id|entry-&gt;private_data
comma
r_return
)paren
suffix:semicolon
r_char
id|line
(braket
l_int|64
)braket
suffix:semicolon
r_int
r_int
id|reg
comma
id|val
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|snd_info_get_line
c_func
(paren
id|buffer
comma
id|line
comma
r_sizeof
(paren
id|line
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|sscanf
c_func
(paren
id|line
comma
l_string|&quot;%x %x&quot;
comma
op_amp
id|reg
comma
op_amp
id|val
)paren
op_ne
l_int|2
)paren
r_continue
suffix:semicolon
multiline_comment|/* register must be odd */
r_if
c_cond
(paren
id|reg
OL
l_int|0x80
op_logical_and
(paren
id|reg
op_amp
l_int|1
)paren
op_eq
l_int|0
op_logical_and
id|val
op_le
l_int|0xffff
)paren
id|snd_ac97_write_cache
c_func
(paren
id|ac97
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|snd_ac97_proc_regs_read_main
r_static
r_void
id|snd_ac97_proc_regs_read_main
c_func
(paren
id|ac97_t
op_star
id|ac97
comma
id|snd_info_buffer_t
op_star
id|buffer
comma
r_int
id|subidx
)paren
(brace
r_int
id|reg
comma
id|val
suffix:semicolon
r_for
c_loop
(paren
id|reg
op_assign
l_int|0
suffix:semicolon
id|reg
OL
l_int|0x80
suffix:semicolon
id|reg
op_add_assign
l_int|2
)paren
(brace
id|val
op_assign
id|snd_ac97_read
c_func
(paren
id|ac97
comma
id|reg
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%i:%02x = %04x&bslash;n&quot;
comma
id|subidx
comma
id|reg
comma
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_ac97_proc_regs_read
r_static
r_void
id|snd_ac97_proc_regs_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
id|ac97_t
op_star
id|ac97
op_assign
id|snd_magic_cast
c_func
(paren
id|ac97_t
comma
id|entry-&gt;private_data
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ac97-&gt;id
op_amp
l_int|0xffffff40
)paren
op_eq
id|AC97_ID_AD1881
)paren
(brace
singleline_comment|// Analog Devices AD1881/85/86
r_int
id|idx
suffix:semicolon
id|down
c_func
(paren
op_amp
id|ac97-&gt;spec.ad18xx.mutex
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
id|ac97-&gt;spec.ad18xx.id
(braket
id|idx
)braket
)paren
(brace
multiline_comment|/* select single codec */
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
l_int|0x7000
comma
id|ac97-&gt;spec.ad18xx.unchained
(braket
id|idx
)braket
op_or
id|ac97-&gt;spec.ad18xx.chained
(braket
id|idx
)braket
)paren
suffix:semicolon
id|snd_ac97_proc_regs_read_main
c_func
(paren
id|ac97
comma
id|buffer
comma
id|idx
)paren
suffix:semicolon
)brace
multiline_comment|/* select all codecs */
id|snd_ac97_update_bits
c_func
(paren
id|ac97
comma
id|AC97_AD_SERIAL_CFG
comma
l_int|0x7000
comma
l_int|0x7000
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|ac97-&gt;spec.ad18xx.mutex
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_ac97_proc_regs_read_main
c_func
(paren
id|ac97
comma
id|buffer
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_ac97_proc_init
r_void
id|snd_ac97_proc_init
c_func
(paren
id|ac97_t
op_star
id|ac97
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
r_const
r_char
op_star
id|prefix
suffix:semicolon
r_if
c_cond
(paren
id|ac97-&gt;bus-&gt;proc
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|prefix
op_assign
id|ac97_is_audio
c_func
(paren
id|ac97
)paren
ques
c_cond
l_string|&quot;ac97&quot;
suffix:colon
l_string|&quot;mc97&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s#%d-%d&quot;
comma
id|prefix
comma
id|ac97-&gt;addr
comma
id|ac97-&gt;num
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|snd_info_create_card_entry
c_func
(paren
id|ac97-&gt;bus-&gt;card
comma
id|name
comma
id|ac97-&gt;bus-&gt;proc
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|snd_info_set_text_ops
c_func
(paren
id|entry
comma
id|ac97
comma
l_int|1024
comma
id|snd_ac97_proc_read
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|ac97-&gt;proc
op_assign
id|entry
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%s#%d-%d+regs&quot;
comma
id|prefix
comma
id|ac97-&gt;addr
comma
id|ac97-&gt;num
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|snd_info_create_card_entry
c_func
(paren
id|ac97-&gt;bus-&gt;card
comma
id|name
comma
id|ac97-&gt;bus-&gt;proc
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|snd_info_set_text_ops
c_func
(paren
id|entry
comma
id|ac97
comma
l_int|1024
comma
id|snd_ac97_proc_regs_read
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG
id|entry-&gt;mode
op_or_assign
id|S_IWUSR
suffix:semicolon
id|entry-&gt;c.text.write_size
op_assign
l_int|1024
suffix:semicolon
id|entry-&gt;c.text.write
op_assign
id|snd_ac97_proc_regs_write
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|ac97-&gt;proc_regs
op_assign
id|entry
suffix:semicolon
)brace
DECL|function|snd_ac97_proc_done
r_void
id|snd_ac97_proc_done
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
id|ac97-&gt;proc_regs
)paren
(brace
id|snd_info_unregister
c_func
(paren
id|ac97-&gt;proc_regs
)paren
suffix:semicolon
id|ac97-&gt;proc_regs
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ac97-&gt;proc
)paren
(brace
id|snd_info_unregister
c_func
(paren
id|ac97-&gt;proc
)paren
suffix:semicolon
id|ac97-&gt;proc
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
DECL|function|snd_ac97_bus_proc_init
r_void
id|snd_ac97_bus_proc_init
c_func
(paren
id|ac97_bus_t
op_star
id|bus
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;codec97#%d&quot;
comma
id|bus-&gt;num
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|snd_info_create_card_entry
c_func
(paren
id|bus-&gt;card
comma
id|name
comma
id|bus-&gt;card-&gt;proc_root
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|entry-&gt;mode
op_assign
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|bus-&gt;proc
op_assign
id|entry
suffix:semicolon
)brace
DECL|function|snd_ac97_bus_proc_done
r_void
id|snd_ac97_bus_proc_done
c_func
(paren
id|ac97_bus_t
op_star
id|bus
)paren
(brace
r_if
c_cond
(paren
id|bus-&gt;proc
)paren
(brace
id|snd_info_unregister
c_func
(paren
id|bus-&gt;proc
)paren
suffix:semicolon
id|bus-&gt;proc
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
