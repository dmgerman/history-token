multiline_comment|/*&n; *  Patch routines for the emu8000 (AWE32/64)&n; *&n; *  Copyright (C) 1999 Steve Ratcliffe&n; *  Copyright (C) 1999-2000 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;emu8000_local.h&quot;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
DECL|variable|emu8000_reset_addr
r_static
r_int
id|emu8000_reset_addr
op_assign
l_int|0
suffix:semicolon
id|module_param
c_func
(paren
id|emu8000_reset_addr
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|emu8000_reset_addr
comma
l_string|&quot;reset write address at each time (makes slowdown)&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Open up channels.&n; */
r_static
r_int
DECL|function|snd_emu8000_open_dma
id|snd_emu8000_open_dma
c_func
(paren
id|emu8000_t
op_star
id|emu
comma
r_int
id|write
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* reserve all 30 voices for loading */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EMU8000_DRAM_VOICES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snd_emux_lock_voice
c_func
(paren
id|emu-&gt;emu
comma
id|i
)paren
suffix:semicolon
id|snd_emu8000_dma_chan
c_func
(paren
id|emu
comma
id|i
comma
id|write
)paren
suffix:semicolon
)brace
multiline_comment|/* assign voice 31 and 32 to ROM */
id|EMU8000_VTFT_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0
)paren
suffix:semicolon
id|EMU8000_PSST_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0x1d8
)paren
suffix:semicolon
id|EMU8000_CSL_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0x1e0
)paren
suffix:semicolon
id|EMU8000_CCCA_WRITE
c_func
(paren
id|emu
comma
l_int|30
comma
l_int|0x1d8
)paren
suffix:semicolon
id|EMU8000_VTFT_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0
)paren
suffix:semicolon
id|EMU8000_PSST_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0x1d8
)paren
suffix:semicolon
id|EMU8000_CSL_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0x1e0
)paren
suffix:semicolon
id|EMU8000_CCCA_WRITE
c_func
(paren
id|emu
comma
l_int|31
comma
l_int|0x1d8
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Close all dram channels.&n; */
r_static
r_void
DECL|function|snd_emu8000_close_dma
id|snd_emu8000_close_dma
c_func
(paren
id|emu8000_t
op_star
id|emu
)paren
(brace
r_int
id|i
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
id|EMU8000_DRAM_VOICES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|snd_emu8000_dma_chan
c_func
(paren
id|emu
comma
id|i
comma
id|EMU8000_RAM_CLOSE
)paren
suffix:semicolon
id|snd_emux_unlock_voice
c_func
(paren
id|emu-&gt;emu
comma
id|i
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; */
DECL|macro|BLANK_LOOP_START
mdefine_line|#define BLANK_LOOP_START&t;4
DECL|macro|BLANK_LOOP_END
mdefine_line|#define BLANK_LOOP_END&t;&t;8
DECL|macro|BLANK_LOOP_SIZE
mdefine_line|#define BLANK_LOOP_SIZE&t;&t;12
DECL|macro|BLANK_HEAD_SIZE
mdefine_line|#define BLANK_HEAD_SIZE&t;&t;48
multiline_comment|/*&n; * Read a word from userland, taking care of conversions from&n; * 8bit samples etc.&n; */
r_static
r_int
r_int
DECL|function|read_word
id|read_word
c_func
(paren
r_const
r_void
id|__user
op_star
id|buf
comma
r_int
id|offset
comma
r_int
id|mode
)paren
(brace
r_int
r_int
id|c
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
(brace
r_int
r_char
id|cc
suffix:semicolon
id|get_user
c_func
(paren
id|cc
comma
(paren
r_int
r_char
id|__user
op_star
)paren
id|buf
op_plus
id|offset
)paren
suffix:semicolon
id|c
op_assign
id|cc
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* convert 8bit -&gt; 16bit */
)brace
r_else
(brace
macro_line|#ifdef SNDRV_LITTLE_ENDIAN
id|get_user
c_func
(paren
id|c
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
op_plus
id|offset
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|cc
suffix:semicolon
id|get_user
c_func
(paren
id|cc
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|buf
op_plus
id|offset
)paren
suffix:semicolon
id|c
op_assign
id|swab16
c_func
(paren
id|cc
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|mode
op_amp
id|SNDRV_SFNT_SAMPLE_UNSIGNED
)paren
id|c
op_xor_assign
l_int|0x8000
suffix:semicolon
multiline_comment|/* unsigned -&gt; signed */
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/*&n; */
r_static
r_void
DECL|function|snd_emu8000_write_wait
id|snd_emu8000_write_wait
c_func
(paren
id|emu8000_t
op_star
id|emu
)paren
(brace
r_while
c_loop
(paren
(paren
id|EMU8000_SMALW_READ
c_func
(paren
id|emu
)paren
op_amp
l_int|0x80000000
)paren
op_ne
l_int|0
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * write sample word data&n; *&n; * You should not have to keep resetting the address each time&n; * as the chip is supposed to step on the next address automatically.&n; * It mostly does, but during writes of some samples at random it&n; * completely loses words (every one in 16 roughly but with no&n; * obvious pattern).&n; *&n; * This is therefore much slower than need be, but is at least&n; * working.&n; */
r_inline
r_static
r_void
DECL|function|write_word
id|write_word
c_func
(paren
id|emu8000_t
op_star
id|emu
comma
r_int
op_star
id|offset
comma
r_int
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
id|emu8000_reset_addr
)paren
(brace
r_if
c_cond
(paren
id|emu8000_reset_addr
OG
l_int|1
)paren
id|snd_emu8000_write_wait
c_func
(paren
id|emu
)paren
suffix:semicolon
id|EMU8000_SMALW_WRITE
c_func
(paren
id|emu
comma
op_star
id|offset
)paren
suffix:semicolon
)brace
id|EMU8000_SMLD_WRITE
c_func
(paren
id|emu
comma
id|data
)paren
suffix:semicolon
op_star
id|offset
op_add_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Write the sample to EMU800 memory.  This routine is invoked out of&n; * the generic soundfont routines as a callback.&n; */
r_int
DECL|function|snd_emu8000_sample_new
id|snd_emu8000_sample_new
c_func
(paren
id|snd_emux_t
op_star
id|rec
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
comma
r_const
r_void
id|__user
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|rc
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_int
id|truesize
suffix:semicolon
r_int
id|dram_offset
comma
id|dram_start
suffix:semicolon
id|emu8000_t
op_star
id|emu
suffix:semicolon
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|emu8000_t
comma
id|rec-&gt;hw
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_assert
c_func
(paren
id|sp
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
id|sp-&gt;v.size
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* be sure loop points start &lt; end */
r_if
c_cond
(paren
id|sp-&gt;v.loopstart
OG
id|sp-&gt;v.loopend
)paren
(brace
r_int
id|tmp
op_assign
id|sp-&gt;v.loopstart
suffix:semicolon
id|sp-&gt;v.loopstart
op_assign
id|sp-&gt;v.loopend
suffix:semicolon
id|sp-&gt;v.loopend
op_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* compute true data size to be loaded */
id|truesize
op_assign
id|sp-&gt;v.size
suffix:semicolon
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
(paren
id|SNDRV_SFNT_SAMPLE_BIDIR_LOOP
op_or
id|SNDRV_SFNT_SAMPLE_REVERSE_LOOP
)paren
)paren
id|truesize
op_add_assign
id|sp-&gt;v.loopend
op_minus
id|sp-&gt;v.loopstart
suffix:semicolon
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_NO_BLANK
)paren
id|truesize
op_add_assign
id|BLANK_LOOP_SIZE
suffix:semicolon
id|sp-&gt;block
op_assign
id|snd_util_mem_alloc
c_func
(paren
id|hdr
comma
id|truesize
op_star
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sp-&gt;block
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/*snd_printd(&quot;EMU8000: out of memory&bslash;n&quot;);*/
multiline_comment|/* not ENOMEM (for compatibility) */
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|data
comma
id|sp-&gt;v.size
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|data
comma
id|sp-&gt;v.size
op_star
l_int|2
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/* recalculate address offset */
id|sp-&gt;v.end
op_sub_assign
id|sp-&gt;v.start
suffix:semicolon
id|sp-&gt;v.loopstart
op_sub_assign
id|sp-&gt;v.start
suffix:semicolon
id|sp-&gt;v.loopend
op_sub_assign
id|sp-&gt;v.start
suffix:semicolon
id|sp-&gt;v.start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* dram position (in word) -- mem_offset is byte */
id|dram_offset
op_assign
id|EMU8000_DRAM_OFFSET
op_plus
(paren
id|sp-&gt;block-&gt;offset
op_rshift
l_int|1
)paren
suffix:semicolon
id|dram_start
op_assign
id|dram_offset
suffix:semicolon
multiline_comment|/* set the total size (store onto obsolete checksum value) */
id|sp-&gt;v.truesize
op_assign
id|truesize
op_star
l_int|2
suffix:semicolon
multiline_comment|/* in bytes */
id|snd_emux_terminate_all
c_func
(paren
id|emu-&gt;emu
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|snd_emu8000_open_dma
c_func
(paren
id|emu
comma
id|EMU8000_RAM_WRITE
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|rc
suffix:semicolon
multiline_comment|/* Set the address to start writing at */
id|snd_emu8000_write_wait
c_func
(paren
id|emu
)paren
suffix:semicolon
id|EMU8000_SMALW_WRITE
c_func
(paren
id|emu
comma
id|dram_offset
)paren
suffix:semicolon
multiline_comment|/*snd_emu8000_init_fm(emu);*/
macro_line|#if 0
multiline_comment|/* first block - write 48 samples for silence */
r_if
c_cond
(paren
op_logical_neg
id|sp-&gt;block-&gt;offset
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BLANK_HEAD_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|write_word
c_func
(paren
id|emu
comma
op_amp
id|dram_offset
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|offset
op_assign
l_int|0
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
id|sp-&gt;v.size
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|s
suffix:semicolon
id|s
op_assign
id|read_word
c_func
(paren
id|data
comma
id|offset
comma
id|sp-&gt;v.mode_flags
)paren
suffix:semicolon
id|offset
op_increment
suffix:semicolon
id|write_word
c_func
(paren
id|emu
comma
op_amp
id|dram_offset
comma
id|s
)paren
suffix:semicolon
multiline_comment|/* we may take too long time in this loop.&n;&t;&t; * so give controls back to kernel if needed.&n;&t;&t; */
id|cond_resched
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|sp-&gt;v.loopend
op_logical_and
(paren
id|sp-&gt;v.mode_flags
op_amp
(paren
id|SNDRV_SFNT_SAMPLE_BIDIR_LOOP
op_or
id|SNDRV_SFNT_SAMPLE_REVERSE_LOOP
)paren
)paren
)paren
(brace
r_int
id|looplen
op_assign
id|sp-&gt;v.loopend
op_minus
id|sp-&gt;v.loopstart
suffix:semicolon
r_int
id|k
suffix:semicolon
multiline_comment|/* copy reverse loop */
r_for
c_loop
(paren
id|k
op_assign
l_int|1
suffix:semicolon
id|k
op_le
id|looplen
suffix:semicolon
id|k
op_increment
)paren
(brace
id|s
op_assign
id|read_word
c_func
(paren
id|data
comma
id|offset
op_minus
id|k
comma
id|sp-&gt;v.mode_flags
)paren
suffix:semicolon
id|write_word
c_func
(paren
id|emu
comma
op_amp
id|dram_offset
comma
id|s
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_BIDIR_LOOP
)paren
(brace
id|sp-&gt;v.loopend
op_add_assign
id|looplen
suffix:semicolon
)brace
r_else
(brace
id|sp-&gt;v.loopstart
op_add_assign
id|looplen
suffix:semicolon
id|sp-&gt;v.loopend
op_add_assign
id|looplen
suffix:semicolon
)brace
id|sp-&gt;v.end
op_add_assign
id|looplen
suffix:semicolon
)brace
)brace
multiline_comment|/* if no blank loop is attached in the sample, add it */
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_NO_BLANK
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|BLANK_LOOP_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|write_word
c_func
(paren
id|emu
comma
op_amp
id|dram_offset
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_SINGLESHOT
)paren
(brace
id|sp-&gt;v.loopstart
op_assign
id|sp-&gt;v.end
op_plus
id|BLANK_LOOP_START
suffix:semicolon
id|sp-&gt;v.loopend
op_assign
id|sp-&gt;v.end
op_plus
id|BLANK_LOOP_END
suffix:semicolon
)brace
)brace
multiline_comment|/* add dram offset */
id|sp-&gt;v.start
op_add_assign
id|dram_start
suffix:semicolon
id|sp-&gt;v.end
op_add_assign
id|dram_start
suffix:semicolon
id|sp-&gt;v.loopstart
op_add_assign
id|dram_start
suffix:semicolon
id|sp-&gt;v.loopend
op_add_assign
id|dram_start
suffix:semicolon
id|snd_emu8000_close_dma
c_func
(paren
id|emu
)paren
suffix:semicolon
id|snd_emu8000_init_fm
c_func
(paren
id|emu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * free a sample block&n; */
r_int
DECL|function|snd_emu8000_sample_free
id|snd_emu8000_sample_free
c_func
(paren
id|snd_emux_t
op_star
id|rec
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
)paren
(brace
r_if
c_cond
(paren
id|sp-&gt;block
)paren
(brace
id|snd_util_mem_free
c_func
(paren
id|hdr
comma
id|sp-&gt;block
)paren
suffix:semicolon
id|sp-&gt;block
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sample_reset callback - terminate voices&n; */
r_void
DECL|function|snd_emu8000_sample_reset
id|snd_emu8000_sample_reset
c_func
(paren
id|snd_emux_t
op_star
id|rec
)paren
(brace
id|snd_emux_terminate_all
c_func
(paren
id|rec
)paren
suffix:semicolon
)brace
eof
