multiline_comment|/*&n; **********************************************************************&n; *     recmgr.c -- Recording manager for emu10k1 driver&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#include &quot;8010.h&quot;
macro_line|#include &quot;recmgr.h&quot;
DECL|function|emu10k1_start_record
r_void
id|emu10k1_start_record
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|wavein_buffer
op_star
id|buffer
)paren
(brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_start_record()&bslash;n&quot;
)paren
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|buffer-&gt;sizereg
comma
l_int|0
comma
id|buffer-&gt;sizeregval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;adcctl
)paren
id|sblive_writeptr
c_func
(paren
id|card
comma
id|ADCCR
comma
l_int|0
comma
id|buffer-&gt;adcctl
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_stop_record
r_void
id|emu10k1_stop_record
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|wavein_buffer
op_star
id|buffer
)paren
(brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_stop_record()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Disable record transfer */
r_if
c_cond
(paren
id|buffer-&gt;adcctl
)paren
id|sblive_writeptr
c_func
(paren
id|card
comma
id|ADCCR
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|buffer-&gt;sizereg
comma
l_int|0
comma
id|ADCBS_BUFSIZE_NONE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_set_record_src
r_void
id|emu10k1_set_record_src
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|wiinst
op_star
id|wiinst
)paren
(brace
r_struct
id|wavein_buffer
op_star
id|buffer
op_assign
op_amp
id|wiinst-&gt;buffer
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_set_record_src()&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|wiinst-&gt;recsrc
)paren
(brace
r_case
id|WAVERECORD_AC97
suffix:colon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;recording source: AC97&bslash;n&quot;
)paren
suffix:semicolon
id|buffer-&gt;sizereg
op_assign
id|ADCBS
suffix:semicolon
id|buffer-&gt;addrreg
op_assign
id|ADCBA
suffix:semicolon
id|buffer-&gt;idxreg
op_assign
id|ADCIDX_IDX
suffix:semicolon
r_switch
c_cond
(paren
id|wiinst-&gt;format.samplingrate
)paren
(brace
r_case
l_int|0xBB80
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_48
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xAC44
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_44
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x7D00
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x5DC0
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_24
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x5622
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_22
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3E80
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2B11
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_11
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1F40
suffix:colon
id|buffer-&gt;adcctl
op_assign
id|ADCCR_SAMPLERATE_8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|buffer-&gt;adcctl
op_or_assign
id|ADCCR_LCHANENABLE
suffix:semicolon
r_if
c_cond
(paren
id|wiinst-&gt;format.channels
op_eq
l_int|2
)paren
id|buffer-&gt;adcctl
op_or_assign
id|ADCCR_RCHANENABLE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAVERECORD_MIC
suffix:colon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;recording source: MIC&bslash;n&quot;
)paren
suffix:semicolon
id|buffer-&gt;sizereg
op_assign
id|MICBS
suffix:semicolon
id|buffer-&gt;addrreg
op_assign
id|MICBA
suffix:semicolon
id|buffer-&gt;idxreg
op_assign
id|MICIDX_IDX
suffix:semicolon
id|buffer-&gt;adcctl
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAVERECORD_FX
suffix:colon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;recording source: FX&bslash;n&quot;
)paren
suffix:semicolon
id|buffer-&gt;sizereg
op_assign
id|FXBS
suffix:semicolon
id|buffer-&gt;addrreg
op_assign
id|FXBA
suffix:semicolon
id|buffer-&gt;idxreg
op_assign
id|FXIDX_IDX
suffix:semicolon
id|buffer-&gt;adcctl
op_assign
l_int|0
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|FXWC
comma
l_int|0
comma
id|wiinst-&gt;fxwc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;bus addx: %#x&bslash;n&quot;
comma
id|buffer-&gt;dma_handle
)paren
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|buffer-&gt;addrreg
comma
l_int|0
comma
id|buffer-&gt;dma_handle
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof