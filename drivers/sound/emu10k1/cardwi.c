multiline_comment|/*&n; **********************************************************************&n; *     cardwi.c - PCM input HAL for emu10k1 driver&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;timer.h&quot;
macro_line|#include &quot;recmgr.h&quot;
macro_line|#include &quot;audio.h&quot;
macro_line|#include &quot;cardwi.h&quot;
multiline_comment|/**&n; * query_format - returns a valid sound format&n; *&n; * This function will return a valid sound format as close&n; * to the requested one as possible. &n; */
DECL|function|query_format
r_void
id|query_format
c_func
(paren
r_int
id|recsrc
comma
r_struct
id|wave_format
op_star
id|wave_fmt
)paren
(brace
r_switch
c_cond
(paren
id|recsrc
)paren
(brace
r_case
id|WAVERECORD_AC97
suffix:colon
r_if
c_cond
(paren
(paren
id|wave_fmt-&gt;channels
op_ne
l_int|1
)paren
op_logical_and
(paren
id|wave_fmt-&gt;channels
op_ne
l_int|2
)paren
)paren
id|wave_fmt-&gt;channels
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
(paren
l_int|0xBB80
op_plus
l_int|0xAC44
)paren
op_div
l_int|2
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0xBB80
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
(paren
l_int|0xAC44
op_plus
l_int|0x7D00
)paren
op_div
l_int|2
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0xAC44
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
(paren
l_int|0x7D00
op_plus
l_int|0x5DC0
)paren
op_div
l_int|2
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0x7D00
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
(paren
l_int|0x5DC0
op_plus
l_int|0x5622
)paren
op_div
l_int|2
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0x5DC0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
(paren
l_int|0x5622
op_plus
l_int|0x3E80
)paren
op_div
l_int|2
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0x5622
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
(paren
l_int|0x3E80
op_plus
l_int|0x2B11
)paren
op_div
l_int|2
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0x3E80
suffix:semicolon
r_else
r_if
c_cond
(paren
id|wave_fmt-&gt;samplingrate
op_ge
(paren
l_int|0x2B11
op_plus
l_int|0x1F40
)paren
op_div
l_int|2
)paren
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0x2B11
suffix:semicolon
r_else
id|wave_fmt-&gt;samplingrate
op_assign
l_int|0x1F40
suffix:semicolon
r_switch
c_cond
(paren
id|wave_fmt-&gt;id
)paren
(brace
r_case
id|AFMT_S16_LE
suffix:colon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AFMT_U8
suffix:colon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|wave_fmt-&gt;id
op_assign
id|AFMT_S16_LE
suffix:semicolon
id|wave_fmt-&gt;bitsperchannel
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* these can&squot;t be changed from the original values */
r_case
id|WAVERECORD_MIC
suffix:colon
r_case
id|WAVERECORD_FX
suffix:colon
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
id|wave_fmt-&gt;bytesperchannel
op_assign
id|wave_fmt-&gt;bitsperchannel
op_rshift
l_int|3
suffix:semicolon
id|wave_fmt-&gt;bytespersample
op_assign
id|wave_fmt-&gt;channels
op_star
id|wave_fmt-&gt;bytesperchannel
suffix:semicolon
id|wave_fmt-&gt;bytespersec
op_assign
id|wave_fmt-&gt;bytespersample
op_star
id|wave_fmt-&gt;samplingrate
suffix:semicolon
)brace
DECL|function|alloc_buffer
r_static
r_int
id|alloc_buffer
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
id|buffer-&gt;addr
op_assign
id|pci_alloc_consistent
c_func
(paren
id|card-&gt;pci_dev
comma
id|buffer-&gt;size
op_star
id|buffer-&gt;cov
comma
op_amp
id|buffer-&gt;dma_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;addr
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|free_buffer
r_static
r_void
id|free_buffer
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
r_if
c_cond
(paren
id|buffer-&gt;addr
op_ne
l_int|NULL
)paren
id|pci_free_consistent
c_func
(paren
id|card-&gt;pci_dev
comma
id|buffer-&gt;size
op_star
id|buffer-&gt;cov
comma
id|buffer-&gt;addr
comma
id|buffer-&gt;dma_handle
)paren
suffix:semicolon
)brace
DECL|function|emu10k1_wavein_open
r_int
id|emu10k1_wavein_open
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|wiinst
op_star
id|wiinst
op_assign
id|wave_dev-&gt;wiinst
suffix:semicolon
r_struct
id|wiinst
op_star
op_star
id|wiinst_tmp
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|delay
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_wavein_open()&bslash;n&quot;
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
id|wiinst_tmp
op_assign
op_amp
id|card-&gt;wavein.ac97
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAVERECORD_MIC
suffix:colon
id|wiinst_tmp
op_assign
op_amp
id|card-&gt;wavein.mic
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAVERECORD_FX
suffix:colon
id|wiinst_tmp
op_assign
op_amp
id|card-&gt;wavein.fx
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|wiinst_tmp
op_ne
l_int|NULL
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|wiinst_tmp
op_assign
id|wiinst
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* handle 8 bit recording */
r_if
c_cond
(paren
id|wiinst-&gt;format.bytesperchannel
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|wiinst-&gt;buffer.size
OG
l_int|0x8000
)paren
(brace
id|wiinst-&gt;buffer.size
op_assign
l_int|0x8000
suffix:semicolon
id|wiinst-&gt;buffer.sizeregval
op_assign
l_int|0x1f
suffix:semicolon
)brace
r_else
id|wiinst-&gt;buffer.sizeregval
op_add_assign
l_int|4
suffix:semicolon
id|wiinst-&gt;buffer.cov
op_assign
l_int|2
suffix:semicolon
)brace
r_else
id|wiinst-&gt;buffer.cov
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|alloc_buffer
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;buffer
)paren
OL
l_int|0
)paren
(brace
id|ERROR
c_func
(paren
)paren
suffix:semicolon
id|emu10k1_wavein_close
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|emu10k1_set_record_src
c_func
(paren
id|card
comma
id|wiinst
)paren
suffix:semicolon
id|delay
op_assign
(paren
l_int|48000
op_star
id|wiinst-&gt;buffer.fragment_size
)paren
op_div
id|wiinst-&gt;format.bytespersec
suffix:semicolon
id|emu10k1_timer_install
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;timer
comma
id|delay
op_div
l_int|2
)paren
suffix:semicolon
id|wiinst-&gt;state
op_assign
id|WAVE_STATE_OPEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_wavein_close
r_void
id|emu10k1_wavein_close
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|wiinst
op_star
id|wiinst
op_assign
id|wave_dev-&gt;wiinst
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_wavein_close()&bslash;n&quot;
)paren
suffix:semicolon
id|emu10k1_wavein_stop
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
id|emu10k1_timer_uninstall
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;timer
)paren
suffix:semicolon
id|free_buffer
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;buffer
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|wave_dev-&gt;wiinst-&gt;recsrc
)paren
(brace
r_case
id|WAVERECORD_AC97
suffix:colon
id|card-&gt;wavein.ac97
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAVERECORD_MIC
suffix:colon
id|card-&gt;wavein.mic
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAVERECORD_FX
suffix:colon
id|card-&gt;wavein.fx
op_assign
l_int|NULL
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|wiinst-&gt;state
op_assign
id|WAVE_STATE_CLOSED
suffix:semicolon
)brace
DECL|function|emu10k1_wavein_start
r_void
id|emu10k1_wavein_start
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|wiinst
op_star
id|wiinst
op_assign
id|wave_dev-&gt;wiinst
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_wavein_start()&bslash;n&quot;
)paren
suffix:semicolon
id|emu10k1_start_record
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;buffer
)paren
suffix:semicolon
id|emu10k1_timer_enable
c_func
(paren
id|wave_dev-&gt;card
comma
op_amp
id|wiinst-&gt;timer
)paren
suffix:semicolon
id|wiinst-&gt;buffer.hw_pos
op_assign
l_int|0
suffix:semicolon
id|wiinst-&gt;buffer.pos
op_assign
l_int|0
suffix:semicolon
id|wiinst-&gt;buffer.bytestocopy
op_assign
l_int|0
suffix:semicolon
id|wiinst-&gt;state
op_or_assign
id|WAVE_STATE_STARTED
suffix:semicolon
)brace
DECL|function|emu10k1_wavein_stop
r_void
id|emu10k1_wavein_stop
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|wiinst
op_star
id|wiinst
op_assign
id|wave_dev-&gt;wiinst
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_wavein_stop()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|wiinst-&gt;state
op_amp
id|WAVE_STATE_STARTED
)paren
)paren
r_return
suffix:semicolon
id|emu10k1_timer_disable
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;timer
)paren
suffix:semicolon
id|emu10k1_stop_record
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;buffer
)paren
suffix:semicolon
id|wiinst-&gt;state
op_and_assign
op_complement
id|WAVE_STATE_STARTED
suffix:semicolon
)brace
DECL|function|emu10k1_wavein_setformat
r_int
id|emu10k1_wavein_setformat
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
comma
r_struct
id|wave_format
op_star
id|format
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|wiinst
op_star
id|wiinst
op_assign
id|wave_dev-&gt;wiinst
suffix:semicolon
id|u32
id|delay
suffix:semicolon
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;emu10k1_wavein_setformat()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wiinst-&gt;state
op_amp
id|WAVE_STATE_STARTED
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|query_format
c_func
(paren
id|wiinst-&gt;recsrc
comma
id|format
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wiinst-&gt;format.samplingrate
op_ne
id|format-&gt;samplingrate
)paren
op_logical_or
(paren
id|wiinst-&gt;format.bitsperchannel
op_ne
id|format-&gt;bitsperchannel
)paren
op_logical_or
(paren
id|wiinst-&gt;format.channels
op_ne
id|format-&gt;channels
)paren
)paren
(brace
id|wiinst-&gt;format
op_assign
op_star
id|format
suffix:semicolon
r_if
c_cond
(paren
id|wiinst-&gt;state
op_eq
id|WAVE_STATE_CLOSED
)paren
r_return
l_int|0
suffix:semicolon
id|wiinst-&gt;buffer.size
op_mul_assign
id|wiinst-&gt;buffer.cov
suffix:semicolon
r_if
c_cond
(paren
id|wiinst-&gt;format.bytesperchannel
op_eq
l_int|1
)paren
(brace
id|wiinst-&gt;buffer.cov
op_assign
l_int|2
suffix:semicolon
id|wiinst-&gt;buffer.size
op_div_assign
id|wiinst-&gt;buffer.cov
suffix:semicolon
)brace
r_else
id|wiinst-&gt;buffer.cov
op_assign
l_int|1
suffix:semicolon
id|emu10k1_timer_uninstall
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;timer
)paren
suffix:semicolon
id|delay
op_assign
(paren
l_int|48000
op_star
id|wiinst-&gt;buffer.fragment_size
)paren
op_div
id|wiinst-&gt;format.bytespersec
suffix:semicolon
id|emu10k1_timer_install
c_func
(paren
id|card
comma
op_amp
id|wiinst-&gt;timer
comma
id|delay
op_div
l_int|2
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_wavein_getxfersize
r_void
id|emu10k1_wavein_getxfersize
c_func
(paren
r_struct
id|wiinst
op_star
id|wiinst
comma
id|u32
op_star
id|size
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
op_star
id|size
op_assign
id|buffer-&gt;bytestocopy
suffix:semicolon
r_if
c_cond
(paren
id|wiinst-&gt;mmapped
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_star
id|size
OG
id|buffer-&gt;size
)paren
(brace
op_star
id|size
op_assign
id|buffer-&gt;size
suffix:semicolon
id|buffer-&gt;pos
op_assign
id|buffer-&gt;hw_pos
suffix:semicolon
id|buffer-&gt;bytestocopy
op_assign
id|buffer-&gt;size
suffix:semicolon
id|DPF
c_func
(paren
l_int|1
comma
l_string|&quot;buffer overrun&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|copy_block
r_static
r_void
id|copy_block
c_func
(paren
id|u8
op_star
id|dst
comma
id|u8
op_star
id|src
comma
id|u32
id|str
comma
id|u32
id|len
comma
id|u8
id|cov
)paren
(brace
r_if
c_cond
(paren
id|cov
op_eq
l_int|1
)paren
id|__copy_to_user
c_func
(paren
id|dst
comma
id|src
op_plus
id|str
comma
id|len
)paren
suffix:semicolon
r_else
(brace
id|u8
id|byte
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|src
op_add_assign
l_int|1
op_plus
l_int|2
op_star
id|str
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
id|byte
op_assign
id|src
(braket
l_int|2
op_star
id|i
)braket
op_xor
l_int|0x80
suffix:semicolon
id|__copy_to_user
c_func
(paren
id|dst
op_plus
id|i
comma
op_amp
id|byte
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|emu10k1_wavein_xferdata
r_void
id|emu10k1_wavein_xferdata
c_func
(paren
r_struct
id|wiinst
op_star
id|wiinst
comma
id|u8
op_star
id|data
comma
id|u32
op_star
id|size
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
id|u32
id|sizetocopy
comma
id|sizetocopy_now
comma
id|start
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|sizetocopy
op_assign
id|min
c_func
(paren
id|u32
comma
id|buffer-&gt;size
comma
op_star
id|size
)paren
suffix:semicolon
op_star
id|size
op_assign
id|sizetocopy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sizetocopy
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|wiinst-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|start
op_assign
id|buffer-&gt;pos
suffix:semicolon
id|buffer-&gt;pos
op_add_assign
id|sizetocopy
suffix:semicolon
id|buffer-&gt;pos
op_mod_assign
id|buffer-&gt;size
suffix:semicolon
id|buffer-&gt;bytestocopy
op_sub_assign
id|sizetocopy
suffix:semicolon
id|sizetocopy_now
op_assign
id|buffer-&gt;size
op_minus
id|start
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|wiinst-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sizetocopy
OG
id|sizetocopy_now
)paren
(brace
id|sizetocopy
op_sub_assign
id|sizetocopy_now
suffix:semicolon
id|copy_block
c_func
(paren
id|data
comma
id|buffer-&gt;addr
comma
id|start
comma
id|sizetocopy_now
comma
id|buffer-&gt;cov
)paren
suffix:semicolon
id|copy_block
c_func
(paren
id|data
op_plus
id|sizetocopy_now
comma
id|buffer-&gt;addr
comma
l_int|0
comma
id|sizetocopy
comma
id|buffer-&gt;cov
)paren
suffix:semicolon
)brace
r_else
(brace
id|copy_block
c_func
(paren
id|data
comma
id|buffer-&gt;addr
comma
id|start
comma
id|sizetocopy
comma
id|buffer-&gt;cov
)paren
suffix:semicolon
)brace
)brace
DECL|function|emu10k1_wavein_update
r_void
id|emu10k1_wavein_update
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
id|u32
id|hw_pos
suffix:semicolon
id|u32
id|diff
suffix:semicolon
multiline_comment|/* There is no actual start yet */
r_if
c_cond
(paren
op_logical_neg
(paren
id|wiinst-&gt;state
op_amp
id|WAVE_STATE_STARTED
)paren
)paren
(brace
id|hw_pos
op_assign
id|wiinst-&gt;buffer.hw_pos
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* hw_pos in byte units */
id|hw_pos
op_assign
id|sblive_readptr
c_func
(paren
id|card
comma
id|wiinst-&gt;buffer.idxreg
comma
l_int|0
)paren
op_div
id|wiinst-&gt;buffer.cov
suffix:semicolon
)brace
id|diff
op_assign
(paren
id|wiinst-&gt;buffer.size
op_plus
id|hw_pos
op_minus
id|wiinst-&gt;buffer.hw_pos
)paren
op_mod
id|wiinst-&gt;buffer.size
suffix:semicolon
id|wiinst-&gt;total_recorded
op_add_assign
id|diff
suffix:semicolon
id|wiinst-&gt;buffer.bytestocopy
op_add_assign
id|diff
suffix:semicolon
id|wiinst-&gt;buffer.hw_pos
op_assign
id|hw_pos
suffix:semicolon
)brace
eof
