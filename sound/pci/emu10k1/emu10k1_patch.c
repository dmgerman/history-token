multiline_comment|/*&n; *  Patch transfer callback for Emu10k1&n; *&n; *  Copyright (C) 2000 Takashi iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
multiline_comment|/*&n; * All the code for loading in a patch.  There is very little that is&n; * chip specific here.  Just the actual writing to the board.&n; */
macro_line|#include &quot;emu10k1_synth_local.h&quot;
multiline_comment|/*&n; */
DECL|macro|BLANK_LOOP_START
mdefine_line|#define BLANK_LOOP_START&t;4
DECL|macro|BLANK_LOOP_END
mdefine_line|#define BLANK_LOOP_END&t;&t;8
DECL|macro|BLANK_LOOP_SIZE
mdefine_line|#define BLANK_LOOP_SIZE&t;&t;12
DECL|macro|BLANK_HEAD_SIZE
mdefine_line|#define BLANK_HEAD_SIZE&t;&t;32
multiline_comment|/*&n; * allocate a sample block and copy data from userspace&n; */
r_int
DECL|function|snd_emu10k1_sample_new
id|snd_emu10k1_sample_new
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
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_int
id|offset
suffix:semicolon
r_int
id|truesize
comma
id|size
comma
id|loopsize
comma
id|blocksize
suffix:semicolon
r_int
id|loopend
comma
id|sampleend
suffix:semicolon
r_int
r_int
id|start_addr
suffix:semicolon
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|rec-&gt;hw
comma
r_return
op_minus
id|ENXIO
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
id|snd_assert
c_func
(paren
id|hdr
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
(brace
id|snd_printd
c_func
(paren
l_string|&quot;emu: rom font for sample %d&bslash;n&quot;
comma
id|sp-&gt;v.sample
)paren
suffix:semicolon
r_return
l_int|0
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
multiline_comment|/* some samples have invalid data.  the addresses are corrected in voice info */
id|sampleend
op_assign
id|sp-&gt;v.end
suffix:semicolon
r_if
c_cond
(paren
id|sampleend
OG
id|sp-&gt;v.size
)paren
id|sampleend
op_assign
id|sp-&gt;v.size
suffix:semicolon
id|loopend
op_assign
id|sp-&gt;v.loopend
suffix:semicolon
r_if
c_cond
(paren
id|loopend
OG
id|sampleend
)paren
id|loopend
op_assign
id|sampleend
suffix:semicolon
multiline_comment|/* be sure loop points start &lt; end */
r_if
c_cond
(paren
id|sp-&gt;v.loopstart
op_ge
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
op_plus
id|BLANK_HEAD_SIZE
suffix:semicolon
id|loopsize
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0 /* not supported */
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
id|loopsize
op_assign
id|sp-&gt;v.loopend
op_minus
id|sp-&gt;v.loopstart
suffix:semicolon
id|truesize
op_add_assign
id|loopsize
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* try to allocate a memory block */
id|blocksize
op_assign
id|truesize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
)paren
id|blocksize
op_mul_assign
l_int|2
suffix:semicolon
id|sp-&gt;block
op_assign
id|snd_emu10k1_synth_alloc
c_func
(paren
id|emu
comma
id|blocksize
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
id|snd_printd
c_func
(paren
l_string|&quot;emu10k1: synth malloc failed (size=%d)&bslash;n&quot;
comma
id|blocksize
)paren
suffix:semicolon
multiline_comment|/* not ENOMEM (for compatibility with OSS) */
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/* set the total size */
id|sp-&gt;v.truesize
op_assign
id|blocksize
suffix:semicolon
multiline_comment|/* write blank samples at head */
id|offset
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
id|BLANK_HEAD_SIZE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
)paren
id|size
op_mul_assign
l_int|2
suffix:semicolon
id|snd_assert
c_func
(paren
id|offset
op_plus
id|size
op_le
id|blocksize
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|snd_emu10k1_synth_bzero
c_func
(paren
id|emu
comma
id|sp-&gt;block
comma
id|offset
comma
id|size
)paren
suffix:semicolon
id|offset
op_add_assign
id|size
suffix:semicolon
multiline_comment|/* copy start-&gt;loopend */
id|size
op_assign
id|loopend
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
)paren
id|size
op_mul_assign
l_int|2
suffix:semicolon
id|snd_assert
c_func
(paren
id|offset
op_plus
id|size
op_le
id|blocksize
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_emu10k1_synth_copy_from_user
c_func
(paren
id|emu
comma
id|sp-&gt;block
comma
id|offset
comma
id|data
comma
id|size
)paren
)paren
(brace
id|snd_emu10k1_synth_free
c_func
(paren
id|emu
comma
id|sp-&gt;block
)paren
suffix:semicolon
id|sp-&gt;block
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|offset
op_add_assign
id|size
suffix:semicolon
id|data
op_add_assign
id|size
suffix:semicolon
macro_line|#if 0 /* not suppported yet */
multiline_comment|/* handle reverse (or bidirectional) loop */
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
(brace
multiline_comment|/* copy loop in reverse */
r_if
c_cond
(paren
op_logical_neg
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
)paren
(brace
r_int
id|woffset
suffix:semicolon
r_int
r_int
op_star
id|wblock
op_assign
(paren
r_int
r_int
op_star
)paren
id|block
suffix:semicolon
id|woffset
op_assign
id|offset
op_div
l_int|2
suffix:semicolon
id|snd_assert
c_func
(paren
id|offset
op_plus
id|loopsize
op_star
l_int|2
op_le
id|blocksize
comma
r_return
op_minus
id|EINVAL
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
id|loopsize
suffix:semicolon
id|i
op_increment
)paren
id|wblock
(braket
id|woffset
op_plus
id|i
)braket
op_assign
id|wblock
(braket
id|woffset
op_minus
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|offset
op_add_assign
id|loopsize
op_star
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|snd_assert
c_func
(paren
id|offset
op_plus
id|loopsize
op_le
id|blocksize
comma
r_return
op_minus
id|EINVAL
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
id|loopsize
suffix:semicolon
id|i
op_increment
)paren
id|block
(braket
id|offset
op_plus
id|i
)braket
op_assign
id|block
(braket
id|offset
op_minus
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|offset
op_add_assign
id|loopsize
suffix:semicolon
)brace
multiline_comment|/* modify loop pointers */
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
id|loopsize
suffix:semicolon
)brace
r_else
(brace
id|sp-&gt;v.loopstart
op_add_assign
id|loopsize
suffix:semicolon
id|sp-&gt;v.loopend
op_add_assign
id|loopsize
suffix:semicolon
)brace
multiline_comment|/* add sample pointer */
id|sp-&gt;v.end
op_add_assign
id|loopsize
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* loopend -&gt; sample end */
id|size
op_assign
id|sp-&gt;v.size
op_minus
id|loopend
suffix:semicolon
id|snd_assert
c_func
(paren
id|size
op_ge
l_int|0
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
)paren
id|size
op_mul_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|snd_emu10k1_synth_copy_from_user
c_func
(paren
id|emu
comma
id|sp-&gt;block
comma
id|offset
comma
id|data
comma
id|size
)paren
)paren
(brace
id|snd_emu10k1_synth_free
c_func
(paren
id|emu
comma
id|sp-&gt;block
)paren
suffix:semicolon
id|sp-&gt;block
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|offset
op_add_assign
id|size
suffix:semicolon
multiline_comment|/* clear rest of samples (if any) */
r_if
c_cond
(paren
id|offset
OL
id|blocksize
)paren
id|snd_emu10k1_synth_bzero
c_func
(paren
id|emu
comma
id|sp-&gt;block
comma
id|offset
comma
id|blocksize
op_minus
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_NO_BLANK
)paren
(brace
multiline_comment|/* if no blank loop is attached in the sample, add it */
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
macro_line|#if 0 /* not supported yet */
r_if
c_cond
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_UNSIGNED
)paren
(brace
multiline_comment|/* unsigned -&gt; signed */
r_if
c_cond
(paren
op_logical_neg
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
)paren
(brace
r_int
r_int
op_star
id|wblock
op_assign
(paren
r_int
r_int
op_star
)paren
id|block
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
id|truesize
suffix:semicolon
id|i
op_increment
)paren
id|wblock
(braket
id|i
)braket
op_xor_assign
l_int|0x8000
suffix:semicolon
)brace
r_else
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
id|truesize
suffix:semicolon
id|i
op_increment
)paren
id|block
(braket
id|i
)braket
op_xor_assign
l_int|0x80
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* recalculate offset */
id|start_addr
op_assign
id|BLANK_HEAD_SIZE
op_star
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sp-&gt;v.mode_flags
op_amp
id|SNDRV_SFNT_SAMPLE_8BITS
)paren
)paren
id|start_addr
op_rshift_assign
l_int|1
suffix:semicolon
id|sp-&gt;v.start
op_add_assign
id|start_addr
suffix:semicolon
id|sp-&gt;v.end
op_add_assign
id|start_addr
suffix:semicolon
id|sp-&gt;v.loopstart
op_add_assign
id|start_addr
suffix:semicolon
id|sp-&gt;v.loopend
op_add_assign
id|start_addr
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * free a sample block&n; */
r_int
DECL|function|snd_emu10k1_sample_free
id|snd_emu10k1_sample_free
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
id|emu10k1_t
op_star
id|emu
suffix:semicolon
id|emu
op_assign
id|snd_magic_cast
c_func
(paren
id|emu10k1_t
comma
id|rec-&gt;hw
comma
r_return
op_minus
id|ENXIO
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
id|snd_assert
c_func
(paren
id|hdr
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
id|sp-&gt;block
)paren
(brace
id|snd_emu10k1_synth_free
c_func
(paren
id|emu
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
eof
