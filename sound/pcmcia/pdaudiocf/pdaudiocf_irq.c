multiline_comment|/*&n; * Driver for Sound Core PDAudioCF soundcard&n; *&n; * Copyright (c) 2003 by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;pdaudiocf.h&quot;
macro_line|#include &lt;sound/initval.h&gt;
multiline_comment|/*&n; *&n; */
DECL|function|pdacf_interrupt
id|irqreturn_t
id|pdacf_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|pdacf_t
comma
id|dev
comma
r_return
id|IRQ_NONE
)paren
suffix:semicolon
r_int
r_int
id|stat
suffix:semicolon
r_if
c_cond
(paren
(paren
id|chip-&gt;chip_status
op_amp
(paren
id|PDAUDIOCF_STAT_IS_STALE
op_or
id|PDAUDIOCF_STAT_IS_CONFIGURED
op_or
id|PDAUDIOCF_STAT_IS_SUSPENDED
)paren
)paren
op_ne
id|PDAUDIOCF_STAT_IS_CONFIGURED
)paren
r_return
id|IRQ_HANDLED
suffix:semicolon
multiline_comment|/* IRQ_NONE here? */
id|stat
op_assign
id|inw
c_func
(paren
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_ISR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
(paren
id|PDAUDIOCF_IRQLVL
op_or
id|PDAUDIOCF_IRQOVR
)paren
)paren
(brace
r_if
c_cond
(paren
id|stat
op_amp
id|PDAUDIOCF_IRQOVR
)paren
multiline_comment|/* should never happen */
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PDAUDIOCF SRAM buffer overrun detected!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;pcm_substream
)paren
id|tasklet_hi_schedule
c_func
(paren
op_amp
id|chip-&gt;tq
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|stat
op_amp
id|PDAUDIOCF_IRQAKM
)paren
)paren
id|stat
op_or_assign
id|PDAUDIOCF_IRQAKM
suffix:semicolon
multiline_comment|/* check rate */
)brace
r_if
c_cond
(paren
id|regs
op_ne
l_int|NULL
)paren
id|snd_ak4117_check_rate_and_errors
c_func
(paren
id|chip-&gt;ak4117
comma
l_int|0
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|pdacf_transfer_mono16
r_static
r_inline
r_void
id|pdacf_transfer_mono16
c_func
(paren
id|u16
op_star
id|dst
comma
id|u16
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
op_xor
op_xor
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_mono32
r_static
r_inline
r_void
id|pdacf_transfer_mono32
c_func
(paren
id|u32
op_star
id|dst
comma
id|u32
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
(paren
(paren
(paren
id|u32
)paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
id|val1
op_lshift
l_int|8
)paren
)paren
op_xor
op_xor
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_stereo16
r_static
r_inline
r_void
id|pdacf_transfer_stereo16
c_func
(paren
id|u16
op_star
id|dst
comma
id|u16
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
op_xor
op_xor
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
op_xor
op_xor
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_stereo32
r_static
r_inline
r_void
id|pdacf_transfer_stereo32
c_func
(paren
id|u32
op_star
id|dst
comma
id|u32
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
comma
id|val3
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val3
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
(paren
(paren
(paren
id|u32
)paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
id|val1
op_lshift
l_int|8
)paren
)paren
op_xor
op_xor
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
(paren
(paren
id|u32
)paren
id|val3
op_lshift
l_int|16
)paren
op_or
(paren
id|val2
op_amp
l_int|0xff00
)paren
)paren
op_xor
op_xor
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_mono16sw
r_static
r_inline
r_void
id|pdacf_transfer_mono16sw
c_func
(paren
id|u16
op_star
id|dst
comma
id|u16
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|swab16
c_func
(paren
id|inw
c_func
(paren
id|rdp_port
)paren
op_xor
op_xor
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_mono32sw
r_static
r_inline
r_void
id|pdacf_transfer_mono32sw
c_func
(paren
id|u32
op_star
id|dst
comma
id|u32
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|swab32
c_func
(paren
(paren
(paren
(paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
id|val1
op_lshift
l_int|8
)paren
)paren
op_xor
op_xor
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_stereo16sw
r_static
r_inline
r_void
id|pdacf_transfer_stereo16sw
c_func
(paren
id|u16
op_star
id|dst
comma
id|u16
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
op_star
id|dst
op_increment
op_assign
id|swab16
c_func
(paren
id|inw
c_func
(paren
id|rdp_port
)paren
op_xor
op_xor
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|swab16
c_func
(paren
id|inw
c_func
(paren
id|rdp_port
)paren
op_xor
op_xor
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_stereo32sw
r_static
r_inline
r_void
id|pdacf_transfer_stereo32sw
c_func
(paren
id|u32
op_star
id|dst
comma
id|u32
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
comma
id|val3
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val3
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|swab32
c_func
(paren
(paren
(paren
(paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
id|val1
op_lshift
l_int|8
)paren
)paren
op_xor
op_xor
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
id|swab32
c_func
(paren
(paren
(paren
(paren
id|u32
)paren
id|val3
op_lshift
l_int|16
)paren
op_or
(paren
id|val2
op_amp
l_int|0xff00
)paren
)paren
op_xor
op_xor
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_mono24le
r_static
r_inline
r_void
id|pdacf_transfer_mono24le
c_func
(paren
id|u8
op_star
id|dst
comma
id|u16
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
suffix:semicolon
r_register
id|u32
id|xval1
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|xval1
op_assign
(paren
(paren
(paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|val1
op_lshift
l_int|16
)paren
)paren
op_xor
op_xor
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|24
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_mono24be
r_static
r_inline
r_void
id|pdacf_transfer_mono24be
c_func
(paren
id|u8
op_star
id|dst
comma
id|u16
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
suffix:semicolon
r_register
id|u32
id|xval1
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|xval1
op_assign
(paren
(paren
(paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|val1
op_lshift
l_int|16
)paren
)paren
op_xor
op_xor
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|24
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_stereo24le
r_static
r_inline
r_void
id|pdacf_transfer_stereo24le
c_func
(paren
id|u8
op_star
id|dst
comma
id|u32
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
comma
id|val3
suffix:semicolon
r_register
id|u32
id|xval1
comma
id|xval2
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val3
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|xval1
op_assign
(paren
(paren
(paren
(paren
id|u32
)paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
id|val1
op_lshift
l_int|8
)paren
)paren
op_xor
op_xor
suffix:semicolon
id|xval2
op_assign
(paren
(paren
(paren
id|u32
)paren
id|val3
op_lshift
l_int|16
)paren
op_or
(paren
id|val2
op_amp
l_int|0xff00
)paren
)paren
op_xor
op_xor
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|24
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval2
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval2
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval2
op_rshift
l_int|24
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer_stereo24be
r_static
r_inline
r_void
id|pdacf_transfer_stereo24be
c_func
(paren
id|u8
op_star
id|dst
comma
id|u32
op_xor
comma
r_int
r_int
id|size
comma
r_int
r_int
id|rdp_port
)paren
(brace
r_register
id|u16
id|val1
comma
id|val2
comma
id|val3
suffix:semicolon
r_register
id|u32
id|xval1
comma
id|xval2
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|val1
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val2
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|val3
op_assign
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|xval1
op_assign
(paren
(paren
(paren
(paren
id|u32
)paren
id|val2
op_amp
l_int|0xff
)paren
op_lshift
l_int|24
)paren
op_or
(paren
(paren
id|u32
)paren
id|val1
op_lshift
l_int|8
)paren
)paren
op_xor
op_xor
suffix:semicolon
id|xval2
op_assign
(paren
(paren
(paren
id|u32
)paren
id|val3
op_lshift
l_int|16
)paren
op_or
(paren
id|val2
op_amp
l_int|0xff00
)paren
)paren
op_xor
op_xor
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|24
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval1
op_rshift
l_int|8
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval2
op_rshift
l_int|24
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval2
op_rshift
l_int|16
)paren
suffix:semicolon
op_star
id|dst
op_increment
op_assign
(paren
id|u8
)paren
(paren
id|xval2
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
)brace
DECL|function|pdacf_transfer
r_static
r_void
id|pdacf_transfer
c_func
(paren
id|pdacf_t
op_star
id|chip
comma
r_int
r_int
id|size
comma
r_int
r_int
id|off
)paren
(brace
r_int
r_int
id|rdp_port
op_assign
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_MD
suffix:semicolon
r_int
r_int
op_xor
op_assign
id|chip-&gt;pcm_xor
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;pcm_sample
op_eq
l_int|3
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_little
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_channels
op_eq
l_int|1
)paren
(brace
id|pdacf_transfer_mono24le
c_func
(paren
(paren
r_char
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|3
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
r_else
(brace
id|pdacf_transfer_stereo24le
c_func
(paren
(paren
r_char
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|6
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_channels
op_eq
l_int|1
)paren
(brace
id|pdacf_transfer_mono24be
c_func
(paren
(paren
r_char
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|3
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
r_else
(brace
id|pdacf_transfer_stereo24be
c_func
(paren
(paren
r_char
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|6
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip-&gt;pcm_swab
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_channels
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_frame
op_eq
l_int|2
)paren
(brace
id|pdacf_transfer_mono16
c_func
(paren
(paren
id|u16
op_star
)paren
id|chip-&gt;pcm_area
op_plus
id|off
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
r_else
(brace
id|pdacf_transfer_mono32
c_func
(paren
(paren
id|u32
op_star
)paren
id|chip-&gt;pcm_area
op_plus
id|off
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_frame
op_eq
l_int|2
)paren
(brace
id|pdacf_transfer_stereo16
c_func
(paren
(paren
id|u16
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|2
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
r_else
(brace
id|pdacf_transfer_stereo32
c_func
(paren
(paren
id|u32
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|2
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_channels
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_frame
op_eq
l_int|2
)paren
(brace
id|pdacf_transfer_mono16sw
c_func
(paren
(paren
id|u16
op_star
)paren
id|chip-&gt;pcm_area
op_plus
id|off
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
r_else
(brace
id|pdacf_transfer_mono32sw
c_func
(paren
(paren
id|u32
op_star
)paren
id|chip-&gt;pcm_area
op_plus
id|off
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|chip-&gt;pcm_frame
op_eq
l_int|2
)paren
(brace
id|pdacf_transfer_stereo16sw
c_func
(paren
(paren
id|u16
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|2
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
r_else
(brace
id|pdacf_transfer_stereo32sw
c_func
(paren
(paren
id|u32
op_star
)paren
id|chip-&gt;pcm_area
op_plus
(paren
id|off
op_star
l_int|2
)paren
comma
op_xor
comma
id|size
comma
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pdacf_tasklet
r_void
id|pdacf_tasklet
c_func
(paren
r_int
r_int
id|private_data
)paren
(brace
id|pdacf_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|pdacf_t
comma
(paren
r_void
op_star
)paren
id|private_data
comma
r_return
)paren
suffix:semicolon
r_int
id|size
comma
id|off
comma
id|cont
comma
id|rdp
comma
id|wdp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|chip-&gt;chip_status
op_amp
(paren
id|PDAUDIOCF_STAT_IS_STALE
op_or
id|PDAUDIOCF_STAT_IS_CONFIGURED
)paren
)paren
op_ne
id|PDAUDIOCF_STAT_IS_CONFIGURED
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;pcm_substream
op_eq
l_int|NULL
op_logical_or
id|chip-&gt;pcm_substream-&gt;runtime
op_eq
l_int|NULL
op_logical_or
op_logical_neg
id|snd_pcm_running
c_func
(paren
id|chip-&gt;pcm_substream
)paren
)paren
r_return
suffix:semicolon
id|rdp
op_assign
id|inw
c_func
(paren
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_RDP
)paren
suffix:semicolon
id|wdp
op_assign
id|inw
c_func
(paren
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_WDP
)paren
suffix:semicolon
singleline_comment|// printk(&quot;TASKLET: rdp = %x, wdp = %x&bslash;n&quot;, rdp, wdp);
id|size
op_assign
id|wdp
op_minus
id|rdp
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
l_int|0
)paren
id|size
op_add_assign
l_int|0x10000
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
id|size
op_assign
l_int|0x10000
suffix:semicolon
id|size
op_div_assign
id|chip-&gt;pcm_frame
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
l_int|64
)paren
id|size
op_sub_assign
l_int|32
suffix:semicolon
macro_line|#if 0
id|chip-&gt;pcm_hwptr
op_add_assign
id|size
suffix:semicolon
id|chip-&gt;pcm_hwptr
op_mod_assign
id|chip-&gt;pcm_size
suffix:semicolon
id|chip-&gt;pcm_tdone
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;pcm_frame
op_eq
l_int|2
)paren
(brace
r_int
r_int
id|rdp_port
op_assign
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_MD
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
r_int
id|rdp_port
op_assign
id|chip-&gt;port
op_plus
id|PDAUDIOCF_REG_MD
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
OG
l_int|0
)paren
(brace
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
id|inw
c_func
(paren
id|rdp_port
)paren
suffix:semicolon
)brace
)brace
macro_line|#else
id|off
op_assign
id|chip-&gt;pcm_hwptr
op_plus
id|chip-&gt;pcm_tdone
suffix:semicolon
id|off
op_mod_assign
id|chip-&gt;pcm_size
suffix:semicolon
id|chip-&gt;pcm_tdone
op_add_assign
id|size
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|cont
op_assign
id|chip-&gt;pcm_size
op_minus
id|off
suffix:semicolon
r_if
c_cond
(paren
id|cont
OG
id|size
)paren
id|cont
op_assign
id|size
suffix:semicolon
id|pdacf_transfer
c_func
(paren
id|chip
comma
id|cont
comma
id|off
)paren
suffix:semicolon
id|off
op_add_assign
id|cont
suffix:semicolon
id|off
op_mod_assign
id|chip-&gt;pcm_size
suffix:semicolon
id|size
op_sub_assign
id|cont
suffix:semicolon
)brace
macro_line|#endif
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;reg_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|chip-&gt;pcm_tdone
op_ge
id|chip-&gt;pcm_period
)paren
(brace
id|chip-&gt;pcm_hwptr
op_add_assign
id|chip-&gt;pcm_period
suffix:semicolon
id|chip-&gt;pcm_hwptr
op_mod_assign
id|chip-&gt;pcm_size
suffix:semicolon
id|chip-&gt;pcm_tdone
op_sub_assign
id|chip-&gt;pcm_period
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;reg_lock
)paren
suffix:semicolon
id|snd_pcm_period_elapsed
c_func
(paren
id|chip-&gt;pcm_substream
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|chip-&gt;reg_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|chip-&gt;reg_lock
)paren
suffix:semicolon
singleline_comment|// printk(&quot;TASKLET: end&bslash;n&quot;);
)brace
eof
