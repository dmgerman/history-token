multiline_comment|/*&n; **********************************************************************&n; *     passthrough.c -- Emu10k1 digital passthrough&n; *     Copyright (C) 2001  Juha Yrj&#xfffd;l&#xfffd; &lt;jyrjola@cc.hut.fi&gt;&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     May 15, 2001&t;    Juha Yrj&#xfffd;l&#xfffd;&t;    base code release&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/wrapper.h&gt;
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;cardwo.h&quot;
macro_line|#include &quot;cardwi.h&quot;
macro_line|#include &quot;recmgr.h&quot;
macro_line|#include &quot;irqmgr.h&quot;
macro_line|#include &quot;audio.h&quot;
macro_line|#include &quot;8010.h&quot;
DECL|function|pt_putsamples
r_static
r_void
id|pt_putsamples
c_func
(paren
r_struct
id|pt_data
op_star
id|pt
comma
id|u16
op_star
id|ptr
comma
id|u16
id|left
comma
id|u16
id|right
)paren
(brace
r_int
r_int
id|idx
suffix:semicolon
id|ptr
(braket
id|pt-&gt;copyptr
)braket
op_assign
id|left
suffix:semicolon
id|idx
op_assign
id|pt-&gt;copyptr
op_plus
id|PT_SAMPLES
op_div
l_int|2
suffix:semicolon
id|idx
op_mod_assign
id|PT_SAMPLES
suffix:semicolon
id|ptr
(braket
id|idx
)braket
op_assign
id|right
suffix:semicolon
)brace
DECL|function|pt_can_write
r_static
r_inline
r_int
id|pt_can_write
c_func
(paren
r_struct
id|pt_data
op_star
id|pt
)paren
(brace
r_return
id|pt-&gt;blocks_copied
OL
id|pt-&gt;blocks_played
op_plus
l_int|8
suffix:semicolon
)brace
DECL|function|pt_wait_for_write
r_static
r_int
id|pt_wait_for_write
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wavedev
comma
r_int
id|nonblock
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wavedev-&gt;card
suffix:semicolon
r_struct
id|pt_data
op_star
id|pt
op_assign
op_amp
id|card-&gt;pt
suffix:semicolon
r_if
c_cond
(paren
id|nonblock
op_logical_and
op_logical_neg
id|pt_can_write
c_func
(paren
id|pt
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|pt_can_write
c_func
(paren
id|pt
)paren
op_logical_and
id|pt-&gt;state
op_ne
id|PT_STATE_INACTIVE
)paren
(brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|pt-&gt;wait
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
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pt-&gt;state
op_eq
id|PT_STATE_INACTIVE
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pt_putblock
r_static
r_int
id|pt_putblock
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
comma
id|u16
op_star
id|block
comma
r_int
id|nonblock
)paren
(brace
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|pt_data
op_star
id|pt
op_assign
op_amp
id|card-&gt;pt
suffix:semicolon
id|u16
op_star
id|ptr
op_assign
(paren
id|u16
op_star
)paren
id|card-&gt;tankmem.addr
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|r
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|r
op_assign
id|pt_wait_for_write
c_func
(paren
id|wave_dev
comma
id|nonblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
OL
l_int|0
)paren
r_return
id|r
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;pt.lock
comma
id|flags
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|PT_BLOCKSAMPLES
)paren
(brace
id|pt_putsamples
c_func
(paren
id|pt
comma
id|ptr
comma
id|block
(braket
l_int|2
op_star
id|i
)braket
comma
id|block
(braket
l_int|2
op_star
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;copyptr
op_eq
l_int|0
)paren
id|pt-&gt;copyptr
op_assign
id|PT_SAMPLES
suffix:semicolon
id|pt-&gt;copyptr
op_decrement
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|woinst-&gt;total_copied
op_add_assign
id|PT_BLOCKSIZE
suffix:semicolon
id|pt-&gt;blocks_copied
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;blocks_copied
op_ge
l_int|4
op_logical_and
id|pt-&gt;state
op_ne
id|PT_STATE_PLAYING
)paren
(brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;activating digital pass-through playback&bslash;n&quot;
)paren
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|GPR_BASE
op_plus
id|pt-&gt;enable_gpr
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|pt-&gt;state
op_assign
id|PT_STATE_PLAYING
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;pt.lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pt_setup
r_static
r_int
id|pt_setup
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
id|u32
id|bits
suffix:semicolon
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|pt_data
op_star
id|pt
op_assign
op_amp
id|card-&gt;pt
suffix:semicolon
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|pt-&gt;old_spcs
(braket
id|i
)braket
op_assign
id|sblive_readptr
c_func
(paren
id|card
comma
id|SPCS0
op_plus
id|i
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;spcs_to_use
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;using S/PDIF port %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|bits
op_assign
id|SPCS_CLKACCY_1000PPM
op_or
id|SPCS_SAMPLERATE_48
op_or
id|SPCS_CHANNELNUM_LEFT
op_or
id|SPCS_SOURCENUM_UNSPEC
op_or
id|SPCS_GENERATIONSTATUS
op_or
l_int|0x00001200
op_or
id|SPCS_EMPHASIS_NONE
op_or
id|SPCS_COPYRIGHT
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;ac3data
)paren
id|bits
op_or_assign
id|SPCS_NOTAUDIODATA
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|SPCS0
op_plus
id|i
comma
l_int|0
comma
id|bits
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_pt_write
id|ssize_t
id|emu10k1_pt_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
id|count
)paren
(brace
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
op_assign
(paren
r_struct
id|emu10k1_wavedevice
op_star
)paren
id|file-&gt;private_data
suffix:semicolon
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|wave_dev-&gt;card
suffix:semicolon
r_struct
id|pt_data
op_star
id|pt
op_assign
op_amp
id|card-&gt;pt
suffix:semicolon
r_int
id|nonblock
comma
id|i
comma
id|r
comma
id|blocks
comma
id|blocks_copied
comma
id|bytes_copied
op_assign
l_int|0
suffix:semicolon
id|DPD
c_func
(paren
l_int|3
comma
l_string|&quot;emu10k1_pt_write(): %d bytes&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
id|nonblock
op_assign
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;tankmem.size
OL
id|PT_SAMPLES
op_star
l_int|2
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;state
op_eq
id|PT_STATE_INACTIVE
)paren
(brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;bufptr init&bslash;n&quot;
)paren
suffix:semicolon
id|pt-&gt;playptr
op_assign
id|PT_SAMPLES
op_minus
l_int|1
suffix:semicolon
id|pt-&gt;copyptr
op_assign
id|PT_INITPTR
suffix:semicolon
id|pt-&gt;blocks_played
op_assign
id|pt-&gt;blocks_copied
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|card-&gt;tankmem.addr
comma
l_int|0
comma
id|card-&gt;tankmem.size
)paren
suffix:semicolon
id|pt-&gt;state
op_assign
id|PT_STATE_ACTIVATED
suffix:semicolon
id|pt-&gt;buf
op_assign
id|kmalloc
c_func
(paren
id|PT_BLOCKSIZE
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|pt-&gt;prepend_size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;buf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pt_setup
c_func
(paren
id|wave_dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pt-&gt;prepend_size
)paren
(brace
r_int
id|needed
op_assign
id|PT_BLOCKSIZE
op_minus
id|pt-&gt;prepend_size
suffix:semicolon
id|DPD
c_func
(paren
l_int|3
comma
l_string|&quot;prepend size %d, prepending %d bytes&bslash;n&quot;
comma
id|pt-&gt;prepend_size
comma
id|needed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|needed
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|pt-&gt;buf
op_plus
id|pt-&gt;prepend_size
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|pt-&gt;prepend_size
op_add_assign
id|count
suffix:semicolon
id|DPD
c_func
(paren
l_int|3
comma
l_string|&quot;prepend size now %d&bslash;n&quot;
comma
id|pt-&gt;prepend_size
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|pt-&gt;buf
op_plus
id|pt-&gt;prepend_size
comma
id|buffer
comma
id|needed
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|r
op_assign
id|pt_putblock
c_func
(paren
id|wave_dev
comma
(paren
id|u16
op_star
)paren
id|pt-&gt;buf
comma
id|nonblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
id|r
suffix:semicolon
id|bytes_copied
op_add_assign
id|needed
suffix:semicolon
id|pt-&gt;prepend_size
op_assign
l_int|0
suffix:semicolon
)brace
id|blocks
op_assign
(paren
id|count
op_minus
id|bytes_copied
)paren
op_div
id|PT_BLOCKSIZE
suffix:semicolon
id|blocks_copied
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|blocks
OG
l_int|0
)paren
(brace
id|u16
op_star
id|bufptr
op_assign
(paren
id|u16
op_star
)paren
id|buffer
op_plus
(paren
id|bytes_copied
op_div
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|pt-&gt;buf
comma
id|bufptr
comma
id|PT_BLOCKSIZE
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|bufptr
op_assign
(paren
id|u16
op_star
)paren
id|pt-&gt;buf
suffix:semicolon
id|r
op_assign
id|pt_putblock
c_func
(paren
id|wave_dev
comma
id|bufptr
comma
id|nonblock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
r_if
c_cond
(paren
id|bytes_copied
)paren
r_return
id|bytes_copied
suffix:semicolon
r_else
r_return
id|r
suffix:semicolon
)brace
id|bytes_copied
op_add_assign
id|PT_BLOCKSIZE
suffix:semicolon
id|blocks
op_decrement
suffix:semicolon
id|blocks_copied
op_increment
suffix:semicolon
)brace
id|i
op_assign
id|count
op_minus
id|bytes_copied
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
(brace
id|pt-&gt;prepend_size
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|pt-&gt;buf
comma
id|buffer
op_plus
id|bytes_copied
comma
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|bytes_copied
op_add_assign
id|i
suffix:semicolon
id|DPD
c_func
(paren
l_int|3
comma
l_string|&quot;filling prepend buffer with %d bytes&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_return
id|bytes_copied
suffix:semicolon
)brace
DECL|function|emu10k1_pt_stop
r_void
id|emu10k1_pt_stop
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
r_struct
id|pt_data
op_star
id|pt
op_assign
op_amp
id|card-&gt;pt
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;state
op_ne
id|PT_STATE_INACTIVE
)paren
(brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;digital pass-through stopped&bslash;n&quot;
)paren
suffix:semicolon
id|sblive_writeptr
c_func
(paren
id|card
comma
id|GPR_BASE
op_plus
id|pt-&gt;enable_gpr
comma
l_int|0
comma
l_int|0
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pt-&gt;spcs_to_use
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|sblive_writeptr
c_func
(paren
id|card
comma
id|SPCS0
op_plus
id|i
comma
l_int|0
comma
id|pt-&gt;old_spcs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|pt-&gt;state
op_assign
id|PT_STATE_INACTIVE
suffix:semicolon
id|kfree
c_func
(paren
id|pt-&gt;buf
)paren
suffix:semicolon
)brace
)brace
DECL|function|emu10k1_pt_waveout_update
r_void
id|emu10k1_pt_waveout_update
c_func
(paren
r_struct
id|emu10k1_wavedevice
op_star
id|wave_dev
)paren
(brace
r_struct
id|woinst
op_star
id|woinst
op_assign
id|wave_dev-&gt;woinst
suffix:semicolon
r_struct
id|pt_data
op_star
id|pt
op_assign
op_amp
id|wave_dev-&gt;card-&gt;pt
suffix:semicolon
id|u32
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|pt-&gt;state
op_eq
id|PT_STATE_PLAYING
op_logical_and
id|pt-&gt;pos_gpr
op_ge
l_int|0
)paren
(brace
id|pos
op_assign
id|sblive_readptr
c_func
(paren
id|wave_dev-&gt;card
comma
id|GPR_BASE
op_plus
id|pt-&gt;pos_gpr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OG
id|PT_BLOCKSAMPLES
)paren
id|pos
op_assign
id|PT_BLOCKSAMPLES
suffix:semicolon
id|pos
op_assign
l_int|4
op_star
(paren
id|PT_BLOCKSAMPLES
op_minus
id|pos
)paren
suffix:semicolon
)brace
r_else
id|pos
op_assign
l_int|0
suffix:semicolon
id|woinst-&gt;total_played
op_assign
id|pt-&gt;blocks_played
op_star
id|woinst-&gt;buffer.fragment_size
op_plus
id|pos
suffix:semicolon
id|woinst-&gt;buffer.hw_pos
op_assign
id|pos
suffix:semicolon
)brace
eof
