multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *                   Creative Labs, Inc.&n; *  Routines for control of EMU10K1 chips / proc interface routines&n; *&n; *  BUGS:&n; *    --&n; *&n; *  TODO:&n; *    --&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
DECL|function|snd_emu10k1_proc_spdif_status
r_static
r_void
id|snd_emu10k1_proc_spdif_status
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
id|snd_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|title
comma
r_int
id|status_reg
comma
r_int
id|rate_reg
)paren
(brace
r_static
r_char
op_star
id|clkaccy
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;1000ppm&quot;
comma
l_string|&quot;50ppm&quot;
comma
l_string|&quot;variable&quot;
comma
l_string|&quot;unknown&quot;
)brace
suffix:semicolon
r_static
r_int
id|samplerate
(braket
l_int|16
)braket
op_assign
(brace
l_int|44100
comma
l_int|1
comma
l_int|48000
comma
l_int|32000
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
)brace
suffix:semicolon
r_static
r_char
op_star
id|channel
(braket
l_int|16
)braket
op_assign
(brace
l_string|&quot;unspec&quot;
comma
l_string|&quot;left&quot;
comma
l_string|&quot;right&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
comma
l_string|&quot;5&quot;
comma
l_string|&quot;6&quot;
comma
l_string|&quot;7&quot;
comma
l_string|&quot;8&quot;
comma
l_string|&quot;9&quot;
comma
l_string|&quot;10&quot;
comma
l_string|&quot;11&quot;
comma
l_string|&quot;12&quot;
comma
l_string|&quot;13&quot;
comma
l_string|&quot;14&quot;
comma
l_string|&quot;15&quot;
)brace
suffix:semicolon
r_static
r_char
op_star
id|emphasis
(braket
l_int|8
)braket
op_assign
(brace
l_string|&quot;none&quot;
comma
l_string|&quot;50/15 usec 2 channel&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
comma
l_string|&quot;4&quot;
comma
l_string|&quot;5&quot;
comma
l_string|&quot;6&quot;
comma
l_string|&quot;7&quot;
)brace
suffix:semicolon
r_int
r_int
id|status
comma
id|rate
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|status_reg
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rate_reg
OG
l_int|0
)paren
id|rate
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|rate_reg
comma
l_int|0
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;n%s&bslash;n&quot;
comma
id|title
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Professional Mode     : %s&bslash;n&quot;
comma
(paren
id|status
op_amp
id|SPCS_PROFESSIONAL
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Not Audio Data        : %s&bslash;n&quot;
comma
(paren
id|status
op_amp
id|SPCS_NOTAUDIODATA
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Copyright             : %s&bslash;n&quot;
comma
(paren
id|status
op_amp
id|SPCS_COPYRIGHT
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Emphasis              : %s&bslash;n&quot;
comma
id|emphasis
(braket
(paren
id|status
op_amp
id|SPCS_EMPHASISMASK
)paren
op_rshift
l_int|3
)braket
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Mode                  : %i&bslash;n&quot;
comma
(paren
id|status
op_amp
id|SPCS_MODEMASK
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Category Code         : 0x%x&bslash;n&quot;
comma
(paren
id|status
op_amp
id|SPCS_CATEGORYCODEMASK
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Generation Status     : %s&bslash;n&quot;
comma
id|status
op_amp
id|SPCS_GENERATIONSTATUS
ques
c_cond
l_string|&quot;original&quot;
suffix:colon
l_string|&quot;copy&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Source Mask           : %i&bslash;n&quot;
comma
(paren
id|status
op_amp
id|SPCS_SOURCENUMMASK
)paren
op_rshift
l_int|16
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Channel Number        : %s&bslash;n&quot;
comma
id|channel
(braket
(paren
id|status
op_amp
id|SPCS_CHANNELNUMMASK
)paren
op_rshift
l_int|20
)braket
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Sample Rate           : %iHz&bslash;n&quot;
comma
id|samplerate
(braket
(paren
id|status
op_amp
id|SPCS_SAMPLERATEMASK
)paren
op_rshift
l_int|24
)braket
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Clock Accuracy        : %s&bslash;n&quot;
comma
id|clkaccy
(braket
(paren
id|status
op_amp
id|SPCS_CLKACCYMASK
)paren
op_rshift
l_int|28
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rate_reg
OG
l_int|0
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;S/PDIF Locked         : %s&bslash;n&quot;
comma
id|rate
op_amp
id|SRCS_SPDIFLOCKED
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Rate Locked           : %s&bslash;n&quot;
comma
id|rate
op_amp
id|SRCS_RATELOCKED
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Estimated Sample Rate : 0x%x&bslash;n&quot;
comma
id|rate
op_amp
id|SRCS_ESTSAMPLERATE
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_emu10k1_proc_read
r_static
r_void
id|snd_emu10k1_proc_read
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
r_static
r_char
op_star
id|outputs
(braket
l_int|32
)braket
op_assign
(brace
multiline_comment|/* 00 */
l_string|&quot;PCM Left&quot;
comma
multiline_comment|/* 01 */
l_string|&quot;PCM Right&quot;
comma
multiline_comment|/* 02 */
l_string|&quot;PCM Surround Left&quot;
comma
multiline_comment|/* 03 */
l_string|&quot;PCM Surround Right&quot;
comma
multiline_comment|/* 04 */
l_string|&quot;MIDI Left&quot;
comma
multiline_comment|/* 05 */
l_string|&quot;MIDI Right&quot;
comma
multiline_comment|/* 06 */
l_string|&quot;PCM Center&quot;
comma
multiline_comment|/* 07 */
l_string|&quot;PCM LFE&quot;
comma
multiline_comment|/* 08 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 09 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 10 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 11 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 12 */
l_string|&quot;MIDI Reverb&quot;
comma
multiline_comment|/* 13 */
l_string|&quot;MIDI Chorus&quot;
comma
multiline_comment|/* 14 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 15 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 16 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 17 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 18 */
l_string|&quot;ADC Left / CDROM S/PDIF Left&quot;
comma
multiline_comment|/* 19 */
l_string|&quot;ADC Right / CDROM S/PDIF Right&quot;
comma
multiline_comment|/* 20 */
l_string|&quot;MIC / Zoom Video Left&quot;
comma
multiline_comment|/* 21 */
l_string|&quot;Zoom Video Right&quot;
comma
multiline_comment|/* 22 */
l_string|&quot;S/PDIF Left&quot;
comma
multiline_comment|/* 23 */
l_string|&quot;S/PDIF Right&quot;
comma
multiline_comment|/* 24 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 25 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 26 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 27 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 28 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 29 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 30 */
l_string|&quot;???&quot;
comma
multiline_comment|/* 31 */
l_string|&quot;???&quot;
)brace
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|entry-&gt;private_data
comma
r_return
)paren
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_int
id|nefx
op_assign
id|emu-&gt;audigy
ques
c_cond
l_int|64
suffix:colon
l_int|32
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;EMU10K1&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
id|val
op_assign
id|emu-&gt;audigy
ques
c_cond
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|A_FXRT1
comma
l_int|0
)paren
suffix:colon
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|FXRT
comma
l_int|0
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Card                  : %s&bslash;n&quot;
comma
id|emu-&gt;audigy
ques
c_cond
l_string|&quot;Audigy&quot;
suffix:colon
(paren
id|emu-&gt;APS
ques
c_cond
l_string|&quot;EMU APS&quot;
suffix:colon
l_string|&quot;Creative&quot;
)paren
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Internal TRAM (words) : 0x%x&bslash;n&quot;
comma
id|emu-&gt;fx8010.itram_size
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;External TRAM (words) : 0x%x&bslash;n&quot;
comma
id|emu-&gt;fx8010.etram_size
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Effect Send Routing   : A=%i, B=%i, C=%i, D=%i&bslash;n&quot;
comma
id|val
op_amp
l_int|0x3f
comma
(paren
id|val
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
comma
(paren
id|val
op_rshift
l_int|16
)paren
op_amp
l_int|0x3f
comma
(paren
id|val
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
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
l_string|&quot;Effect Send Routing   : A=%i, B=%i, C=%i, D=%i&bslash;n&quot;
comma
(paren
id|val
op_rshift
l_int|16
)paren
op_amp
l_int|0x0f
comma
(paren
id|val
op_rshift
l_int|20
)paren
op_amp
l_int|0x0f
comma
(paren
id|val
op_rshift
l_int|24
)paren
op_amp
l_int|0x0f
comma
(paren
id|val
op_rshift
l_int|28
)paren
op_amp
l_int|0x0f
)paren
suffix:semicolon
)brace
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;nCaptured FX Outputs   :&bslash;n&quot;
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
id|nefx
suffix:semicolon
id|idx
op_increment
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;efx_voices_mask
(braket
id|idx
op_div
l_int|32
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|idx
op_mod
l_int|32
)paren
)paren
)paren
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;  Output %02i [%s]&bslash;n&quot;
comma
id|idx
comma
id|outputs
(braket
id|idx
op_mod
l_int|32
)braket
)paren
suffix:semicolon
)brace
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;nAll FX Outputs        :&bslash;n&quot;
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
l_int|32
suffix:semicolon
id|idx
op_increment
)paren
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;  Output %02i [%s]&bslash;n&quot;
comma
id|idx
comma
id|outputs
(braket
id|idx
)braket
)paren
suffix:semicolon
id|snd_emu10k1_proc_spdif_status
c_func
(paren
id|emu
comma
id|buffer
comma
l_string|&quot;S/PDIF Output 0&quot;
comma
id|SPCS0
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|snd_emu10k1_proc_spdif_status
c_func
(paren
id|emu
comma
id|buffer
comma
l_string|&quot;S/PDIF Output 1&quot;
comma
id|SPCS1
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|snd_emu10k1_proc_spdif_status
c_func
(paren
id|emu
comma
id|buffer
comma
l_string|&quot;S/PDIF Output 2/3&quot;
comma
id|SPCS2
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|snd_emu10k1_proc_spdif_status
c_func
(paren
id|emu
comma
id|buffer
comma
l_string|&quot;CD-ROM S/PDIF&quot;
comma
id|CDCS
comma
id|CDSRCS
)paren
suffix:semicolon
id|snd_emu10k1_proc_spdif_status
c_func
(paren
id|emu
comma
id|buffer
comma
l_string|&quot;General purpose S/PDIF&quot;
comma
id|GPSCS
comma
id|GPSRCS
)paren
suffix:semicolon
id|val
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|ZVSRCS
comma
l_int|0
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;nZoomed Video&bslash;n&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Rate Locked           : %s&bslash;n&quot;
comma
id|val
op_amp
id|SRCS_RATELOCKED
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Estimated Sample Rate : 0x%x&bslash;n&quot;
comma
id|val
op_amp
id|SRCS_ESTSAMPLERATE
)paren
suffix:semicolon
)brace
DECL|function|snd_emu10k1_proc_acode_read
r_static
r_void
id|snd_emu10k1_proc_acode_read
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
id|u32
id|pc
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|entry-&gt;private_data
comma
r_return
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;FX8010 Instruction List &squot;%s&squot;&bslash;n&quot;
comma
id|emu-&gt;fx8010.name
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;  Code dump      :&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pc
op_assign
l_int|0
suffix:semicolon
id|pc
OL
l_int|512
suffix:semicolon
id|pc
op_increment
)paren
(brace
id|u32
id|low
comma
id|high
suffix:semicolon
id|low
op_assign
id|snd_emu10k1_efx_read
c_func
(paren
id|emu
comma
id|pc
op_star
l_int|2
)paren
suffix:semicolon
id|high
op_assign
id|snd_emu10k1_efx_read
c_func
(paren
id|emu
comma
id|pc
op_star
l_int|2
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;    OP(0x%02x, 0x%03x, 0x%03x, 0x%03x, 0x%03x) /* 0x%04x: 0x%08x%08x */&bslash;n&quot;
comma
(paren
id|high
op_rshift
l_int|24
)paren
op_amp
l_int|0x0f
comma
(paren
id|high
op_rshift
l_int|12
)paren
op_amp
l_int|0x7ff
comma
(paren
id|high
op_rshift
l_int|0
)paren
op_amp
l_int|0x7ff
comma
(paren
id|low
op_rshift
l_int|12
)paren
op_amp
l_int|0x7ff
comma
(paren
id|low
op_rshift
l_int|0
)paren
op_amp
l_int|0x7ff
comma
id|pc
comma
id|high
comma
id|low
)paren
suffix:semicolon
r_else
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;    OP(0x%02x, 0x%03x, 0x%03x, 0x%03x, 0x%03x) /* 0x%04x: 0x%08x%08x */&bslash;n&quot;
comma
(paren
id|high
op_rshift
l_int|20
)paren
op_amp
l_int|0x0f
comma
(paren
id|high
op_rshift
l_int|10
)paren
op_amp
l_int|0x3ff
comma
(paren
id|high
op_rshift
l_int|0
)paren
op_amp
l_int|0x3ff
comma
(paren
id|low
op_rshift
l_int|10
)paren
op_amp
l_int|0x3ff
comma
(paren
id|low
op_rshift
l_int|0
)paren
op_amp
l_int|0x3ff
comma
id|pc
comma
id|high
comma
id|low
)paren
suffix:semicolon
)brace
)brace
DECL|macro|TOTAL_SIZE_GPR
mdefine_line|#define TOTAL_SIZE_GPR&t;&t;(0x100*4)
DECL|macro|TOTAL_SIZE_TANKMEM_DATA
mdefine_line|#define TOTAL_SIZE_TANKMEM_DATA&t;(0xa0*4)
DECL|macro|TOTAL_SIZE_TANKMEM_ADDR
mdefine_line|#define TOTAL_SIZE_TANKMEM_ADDR (0xa0*4)
DECL|macro|TOTAL_SIZE_CODE
mdefine_line|#define TOTAL_SIZE_CODE&t;&t;(0x200*8)
DECL|function|snd_emu10k1_fx8010_read
r_static
r_int
id|snd_emu10k1_fx8010_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|size
suffix:semicolon
id|emu10k1_t
op_star
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|entry-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
l_string|&quot;fx8010_tram_addr&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|offset
op_assign
id|TANKMEMADDRREGBASE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
l_string|&quot;fx8010_tram_data&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|offset
op_assign
id|TANKMEMDATAREGBASE
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|entry-&gt;name
comma
l_string|&quot;fx8010_code&quot;
)paren
)paren
(brace
id|offset
op_assign
id|emu-&gt;audigy
ques
c_cond
id|A_MICROCODEBASE
suffix:colon
id|MICROCODEBASE
suffix:semicolon
)brace
r_else
(brace
id|offset
op_assign
id|emu-&gt;audigy
ques
c_cond
id|A_FXGPREGBASE
suffix:colon
id|FXGPREGBASE
suffix:semicolon
)brace
id|size
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
op_plus
id|size
OG
id|entry-&gt;size
)paren
id|size
op_assign
(paren
r_int
)paren
id|entry-&gt;size
op_minus
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|0
)paren
(brace
r_int
r_int
op_star
id|tmp
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|kmalloc
c_func
(paren
id|size
op_plus
l_int|8
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
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
(paren
(paren
id|file-&gt;f_pos
op_amp
l_int|3
)paren
op_plus
id|size
op_plus
l_int|3
)paren
op_rshift
l_int|2
suffix:semicolon
id|idx
op_increment
)paren
id|tmp
(braket
id|idx
)braket
op_assign
id|snd_emu10k1_ptr_read
c_func
(paren
id|emu
comma
id|offset
op_plus
id|idx
op_plus
(paren
id|file-&gt;f_pos
op_rshift
l_int|2
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
(paren
r_char
op_star
)paren
id|tmp
)paren
op_plus
(paren
id|file-&gt;f_pos
op_amp
l_int|3
)paren
comma
id|size
)paren
)paren
id|res
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_else
(brace
id|res
op_assign
id|size
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|size
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_emu10k1_proc_ops_fx8010
r_static
r_struct
id|snd_info_entry_ops
id|snd_emu10k1_proc_ops_fx8010
op_assign
(brace
dot
id|read
op_assign
id|snd_emu10k1_fx8010_read
comma
)brace
suffix:semicolon
DECL|function|snd_emu10k1_proc_init
r_int
id|__devinit
id|snd_emu10k1_proc_init
c_func
(paren
id|emu10k1_t
op_star
id|emu
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_card_proc_new
c_func
(paren
id|emu-&gt;card
comma
l_string|&quot;emu10k1&quot;
comma
op_amp
id|entry
)paren
)paren
id|snd_info_set_text_ops
c_func
(paren
id|entry
comma
id|emu
comma
l_int|1024
comma
id|snd_emu10k1_proc_read
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_card_proc_new
c_func
(paren
id|emu-&gt;card
comma
l_string|&quot;fx8010_gpr&quot;
comma
op_amp
id|entry
)paren
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_DATA
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|entry-&gt;mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
multiline_comment|/*| S_IWUSR*/
suffix:semicolon
id|entry-&gt;size
op_assign
id|TOTAL_SIZE_GPR
suffix:semicolon
id|entry-&gt;c.ops
op_assign
op_amp
id|snd_emu10k1_proc_ops_fx8010
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|emu-&gt;audigy
op_logical_and
op_logical_neg
id|snd_card_proc_new
c_func
(paren
id|emu-&gt;card
comma
l_string|&quot;fx8010_tram_data&quot;
comma
op_amp
id|entry
)paren
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_DATA
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|entry-&gt;mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
multiline_comment|/*| S_IWUSR*/
suffix:semicolon
id|entry-&gt;size
op_assign
id|TOTAL_SIZE_TANKMEM_DATA
suffix:semicolon
id|entry-&gt;c.ops
op_assign
op_amp
id|snd_emu10k1_proc_ops_fx8010
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|emu-&gt;audigy
op_logical_and
op_logical_neg
id|snd_card_proc_new
c_func
(paren
id|emu-&gt;card
comma
l_string|&quot;fx8010_tram_addr&quot;
comma
op_amp
id|entry
)paren
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_DATA
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|entry-&gt;mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
multiline_comment|/*| S_IWUSR*/
suffix:semicolon
id|entry-&gt;size
op_assign
id|TOTAL_SIZE_TANKMEM_ADDR
suffix:semicolon
id|entry-&gt;c.ops
op_assign
op_amp
id|snd_emu10k1_proc_ops_fx8010
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|snd_card_proc_new
c_func
(paren
id|emu-&gt;card
comma
l_string|&quot;fx8010_code&quot;
comma
op_amp
id|entry
)paren
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_DATA
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|entry-&gt;mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
multiline_comment|/*| S_IWUSR*/
suffix:semicolon
id|entry-&gt;size
op_assign
id|TOTAL_SIZE_CODE
suffix:semicolon
id|entry-&gt;c.ops
op_assign
op_amp
id|snd_emu10k1_proc_ops_fx8010
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|snd_card_proc_new
c_func
(paren
id|emu-&gt;card
comma
l_string|&quot;fx8010_acode&quot;
comma
op_amp
id|entry
)paren
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|entry-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|entry-&gt;mode
op_assign
id|S_IFREG
op_or
id|S_IRUGO
multiline_comment|/*| S_IWUSR*/
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
l_int|64
op_star
l_int|1024
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|snd_emu10k1_proc_acode_read
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
