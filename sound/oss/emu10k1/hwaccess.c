multiline_comment|/*&n; **********************************************************************&n; *     hwaccess.c -- Hardware access layer&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *     December 9, 1999     Jon Taylor      rewrote the I/O subsystem&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;8010.h&quot;
macro_line|#include &quot;icardmid.h&quot;
multiline_comment|/*************************************************************************&n;* Function : srToPitch                                                   *&n;* Input    : sampleRate - sampling rate                                  *&n;* Return   : pitch value                                                 *&n;* About    : convert sampling rate to pitch                              *&n;* Note     : for 8010, sampling rate is at 48kHz, this function should   *&n;*            be changed.                                                 *&n;*************************************************************************/
DECL|function|srToPitch
id|u32
id|srToPitch
c_func
(paren
id|u32
id|sampleRate
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* FIXME: These tables should be defined in a headerfile */
r_static
id|u32
id|logMagTable
(braket
l_int|128
)braket
op_assign
(brace
l_int|0x00000
comma
l_int|0x02dfc
comma
l_int|0x05b9e
comma
l_int|0x088e6
comma
l_int|0x0b5d6
comma
l_int|0x0e26f
comma
l_int|0x10eb3
comma
l_int|0x13aa2
comma
l_int|0x1663f
comma
l_int|0x1918a
comma
l_int|0x1bc84
comma
l_int|0x1e72e
comma
l_int|0x2118b
comma
l_int|0x23b9a
comma
l_int|0x2655d
comma
l_int|0x28ed5
comma
l_int|0x2b803
comma
l_int|0x2e0e8
comma
l_int|0x30985
comma
l_int|0x331db
comma
l_int|0x359eb
comma
l_int|0x381b6
comma
l_int|0x3a93d
comma
l_int|0x3d081
comma
l_int|0x3f782
comma
l_int|0x41e42
comma
l_int|0x444c1
comma
l_int|0x46b01
comma
l_int|0x49101
comma
l_int|0x4b6c4
comma
l_int|0x4dc49
comma
l_int|0x50191
comma
l_int|0x5269e
comma
l_int|0x54b6f
comma
l_int|0x57006
comma
l_int|0x59463
comma
l_int|0x5b888
comma
l_int|0x5dc74
comma
l_int|0x60029
comma
l_int|0x623a7
comma
l_int|0x646ee
comma
l_int|0x66a00
comma
l_int|0x68cdd
comma
l_int|0x6af86
comma
l_int|0x6d1fa
comma
l_int|0x6f43c
comma
l_int|0x7164b
comma
l_int|0x73829
comma
l_int|0x759d4
comma
l_int|0x77b4f
comma
l_int|0x79c9a
comma
l_int|0x7bdb5
comma
l_int|0x7dea1
comma
l_int|0x7ff5e
comma
l_int|0x81fed
comma
l_int|0x8404e
comma
l_int|0x86082
comma
l_int|0x88089
comma
l_int|0x8a064
comma
l_int|0x8c014
comma
l_int|0x8df98
comma
l_int|0x8fef1
comma
l_int|0x91e20
comma
l_int|0x93d26
comma
l_int|0x95c01
comma
l_int|0x97ab4
comma
l_int|0x9993e
comma
l_int|0x9b79f
comma
l_int|0x9d5d9
comma
l_int|0x9f3ec
comma
l_int|0xa11d8
comma
l_int|0xa2f9d
comma
l_int|0xa4d3c
comma
l_int|0xa6ab5
comma
l_int|0xa8808
comma
l_int|0xaa537
comma
l_int|0xac241
comma
l_int|0xadf26
comma
l_int|0xafbe7
comma
l_int|0xb1885
comma
l_int|0xb3500
comma
l_int|0xb5157
comma
l_int|0xb6d8c
comma
l_int|0xb899f
comma
l_int|0xba58f
comma
l_int|0xbc15e
comma
l_int|0xbdd0c
comma
l_int|0xbf899
comma
l_int|0xc1404
comma
l_int|0xc2f50
comma
l_int|0xc4a7b
comma
l_int|0xc6587
comma
l_int|0xc8073
comma
l_int|0xc9b3f
comma
l_int|0xcb5ed
comma
l_int|0xcd07c
comma
l_int|0xceaec
comma
l_int|0xd053f
comma
l_int|0xd1f73
comma
l_int|0xd398a
comma
l_int|0xd5384
comma
l_int|0xd6d60
comma
l_int|0xd8720
comma
l_int|0xda0c3
comma
l_int|0xdba4a
comma
l_int|0xdd3b4
comma
l_int|0xded03
comma
l_int|0xe0636
comma
l_int|0xe1f4e
comma
l_int|0xe384a
comma
l_int|0xe512c
comma
l_int|0xe69f3
comma
l_int|0xe829f
comma
l_int|0xe9b31
comma
l_int|0xeb3a9
comma
l_int|0xecc08
comma
l_int|0xee44c
comma
l_int|0xefc78
comma
l_int|0xf148a
comma
l_int|0xf2c83
comma
l_int|0xf4463
comma
l_int|0xf5c2a
comma
l_int|0xf73da
comma
l_int|0xf8b71
comma
l_int|0xfa2f0
comma
l_int|0xfba57
comma
l_int|0xfd1a7
comma
l_int|0xfe8df
)brace
suffix:semicolon
r_static
r_char
id|logSlopeTable
(braket
l_int|128
)braket
op_assign
(brace
l_int|0x5c
comma
l_int|0x5c
comma
l_int|0x5b
comma
l_int|0x5a
comma
l_int|0x5a
comma
l_int|0x59
comma
l_int|0x58
comma
l_int|0x58
comma
l_int|0x57
comma
l_int|0x56
comma
l_int|0x56
comma
l_int|0x55
comma
l_int|0x55
comma
l_int|0x54
comma
l_int|0x53
comma
l_int|0x53
comma
l_int|0x52
comma
l_int|0x52
comma
l_int|0x51
comma
l_int|0x51
comma
l_int|0x50
comma
l_int|0x50
comma
l_int|0x4f
comma
l_int|0x4f
comma
l_int|0x4e
comma
l_int|0x4d
comma
l_int|0x4d
comma
l_int|0x4d
comma
l_int|0x4c
comma
l_int|0x4c
comma
l_int|0x4b
comma
l_int|0x4b
comma
l_int|0x4a
comma
l_int|0x4a
comma
l_int|0x49
comma
l_int|0x49
comma
l_int|0x48
comma
l_int|0x48
comma
l_int|0x47
comma
l_int|0x47
comma
l_int|0x47
comma
l_int|0x46
comma
l_int|0x46
comma
l_int|0x45
comma
l_int|0x45
comma
l_int|0x45
comma
l_int|0x44
comma
l_int|0x44
comma
l_int|0x43
comma
l_int|0x43
comma
l_int|0x43
comma
l_int|0x42
comma
l_int|0x42
comma
l_int|0x42
comma
l_int|0x41
comma
l_int|0x41
comma
l_int|0x41
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x3f
comma
l_int|0x3f
comma
l_int|0x3f
comma
l_int|0x3e
comma
l_int|0x3e
comma
l_int|0x3e
comma
l_int|0x3d
comma
l_int|0x3d
comma
l_int|0x3d
comma
l_int|0x3c
comma
l_int|0x3c
comma
l_int|0x3c
comma
l_int|0x3b
comma
l_int|0x3b
comma
l_int|0x3b
comma
l_int|0x3b
comma
l_int|0x3a
comma
l_int|0x3a
comma
l_int|0x3a
comma
l_int|0x39
comma
l_int|0x39
comma
l_int|0x39
comma
l_int|0x39
comma
l_int|0x38
comma
l_int|0x38
comma
l_int|0x38
comma
l_int|0x38
comma
l_int|0x37
comma
l_int|0x37
comma
l_int|0x37
comma
l_int|0x37
comma
l_int|0x36
comma
l_int|0x36
comma
l_int|0x36
comma
l_int|0x36
comma
l_int|0x35
comma
l_int|0x35
comma
l_int|0x35
comma
l_int|0x35
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x34
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x33
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x32
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x31
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x30
comma
l_int|0x2f
comma
l_int|0x2f
comma
l_int|0x2f
comma
l_int|0x2f
comma
l_int|0x2f
)brace
suffix:semicolon
r_if
c_cond
(paren
id|sampleRate
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Bail out if no leading &quot;1&quot; */
id|sampleRate
op_mul_assign
l_int|11185
suffix:semicolon
multiline_comment|/* Scale 48000 to 0x20002380 */
r_for
c_loop
(paren
id|i
op_assign
l_int|31
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|sampleRate
op_amp
l_int|0x80000000
)paren
(brace
multiline_comment|/* Detect leading &quot;1&quot; */
r_return
(paren
id|u32
)paren
(paren
(paren
(paren
id|s32
)paren
(paren
id|i
op_minus
l_int|15
)paren
op_lshift
l_int|20
)paren
op_plus
id|logMagTable
(braket
l_int|0x7f
op_amp
(paren
id|sampleRate
op_rshift
l_int|24
)paren
)braket
op_plus
(paren
l_int|0x7f
op_amp
(paren
id|sampleRate
op_rshift
l_int|17
)paren
)paren
op_star
id|logSlopeTable
(braket
l_int|0x7f
op_amp
(paren
id|sampleRate
op_rshift
l_int|24
)paren
)braket
)paren
suffix:semicolon
)brace
id|sampleRate
op_assign
id|sampleRate
op_lshift
l_int|1
suffix:semicolon
)brace
id|DPF
c_func
(paren
l_int|2
comma
l_string|&quot;srToPitch: BUG!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Should never reach this point */
)brace
multiline_comment|/* Returns an attenuation based upon a cumulative volume value */
multiline_comment|/* Algorithm calculates 0x200 - 0x10 log2 (input) */
DECL|function|sumVolumeToAttenuation
id|u8
id|sumVolumeToAttenuation
c_func
(paren
id|u32
id|value
)paren
(brace
id|u16
id|count
op_assign
l_int|16
suffix:semicolon
id|s16
id|ans
suffix:semicolon
r_if
c_cond
(paren
id|value
op_eq
l_int|0
)paren
r_return
l_int|0xFF
suffix:semicolon
multiline_comment|/* Find first SET bit. This is the integer part of the value */
r_while
c_loop
(paren
(paren
id|value
op_amp
l_int|0x10000
)paren
op_eq
l_int|0
)paren
(brace
id|value
op_lshift_assign
l_int|1
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
multiline_comment|/* The REST of the data is the fractional part. */
id|ans
op_assign
(paren
id|s16
)paren
(paren
l_int|0x110
op_minus
(paren
(paren
id|count
op_lshift
l_int|4
)paren
op_plus
(paren
(paren
id|value
op_amp
l_int|0x0FFFFL
)paren
op_rshift
l_int|12
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ans
OG
l_int|0xFF
)paren
id|ans
op_assign
l_int|0xFF
suffix:semicolon
r_return
(paren
id|u8
)paren
id|ans
suffix:semicolon
)brace
multiline_comment|/*******************************************&n;* write/read PCI function 0 registers      *&n;********************************************/
DECL|function|emu10k1_writefn0
r_void
id|emu10k1_writefn0
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|reg
comma
id|u32
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xff000000
)paren
(brace
id|u32
id|mask
suffix:semicolon
id|u8
id|size
comma
id|offset
suffix:semicolon
id|size
op_assign
(paren
id|reg
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|offset
op_assign
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
id|size
)paren
op_minus
l_int|1
)paren
op_lshift
id|offset
suffix:semicolon
id|data
op_assign
(paren
id|data
op_lshift
id|offset
)paren
op_amp
id|mask
suffix:semicolon
id|reg
op_and_assign
l_int|0x7f
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
id|data
op_or_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|reg
)paren
op_amp
op_complement
id|mask
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|card-&gt;iobase
op_plus
id|reg
)paren
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
)brace
r_else
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|card-&gt;iobase
op_plus
id|reg
)paren
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
)brace
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_readfn0
id|u32
id|emu10k1_readfn0
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|reg
)paren
(brace
id|u32
id|val
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xff000000
)paren
(brace
id|u32
id|mask
suffix:semicolon
id|u8
id|size
comma
id|offset
suffix:semicolon
id|size
op_assign
(paren
id|reg
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|offset
op_assign
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
id|size
)paren
op_minus
l_int|1
)paren
op_lshift
id|offset
suffix:semicolon
id|reg
op_and_assign
l_int|0x7f
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
id|val
op_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|reg
)paren
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
r_return
(paren
id|val
op_amp
id|mask
)paren
op_rshift
id|offset
suffix:semicolon
)brace
r_else
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|reg
)paren
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
r_return
id|val
suffix:semicolon
)brace
)brace
multiline_comment|/************************************************************************&n;* write/read Emu10k1 pointer-offset register set, accessed through      *&n;*  the PTR and DATA registers                                           *&n;*************************************************************************/
DECL|function|sblive_writeptr
r_void
id|sblive_writeptr
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|reg
comma
id|u32
id|channel
comma
id|u32
id|data
)paren
(brace
id|u32
id|regptr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|regptr
op_assign
(paren
(paren
id|reg
op_lshift
l_int|16
)paren
op_amp
id|PTR_ADDRESS_MASK
)paren
op_or
(paren
id|channel
op_amp
id|PTR_CHANNELNUM_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xff000000
)paren
(brace
id|u32
id|mask
suffix:semicolon
id|u8
id|size
comma
id|offset
suffix:semicolon
id|size
op_assign
(paren
id|reg
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|offset
op_assign
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
id|size
)paren
op_minus
l_int|1
)paren
op_lshift
id|offset
suffix:semicolon
id|data
op_assign
(paren
id|data
op_lshift
id|offset
)paren
op_amp
id|mask
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
id|outl
c_func
(paren
id|regptr
comma
id|card-&gt;iobase
op_plus
id|PTR
)paren
suffix:semicolon
id|data
op_or_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|DATA
)paren
op_amp
op_complement
id|mask
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|card-&gt;iobase
op_plus
id|DATA
)paren
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
)brace
r_else
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|regptr
comma
id|card-&gt;iobase
op_plus
id|PTR
)paren
suffix:semicolon
id|outl
c_func
(paren
id|data
comma
id|card-&gt;iobase
op_plus
id|DATA
)paren
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
)brace
)brace
multiline_comment|/* ... :  data, reg, ... , TAGLIST_END */
DECL|function|sblive_writeptr_tag
r_void
id|sblive_writeptr_tag
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|channel
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|reg
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|channel
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
r_while
c_loop
(paren
(paren
id|reg
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|u32
)paren
)paren
op_ne
id|TAGLIST_END
)paren
(brace
id|u32
id|data
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|u32
)paren
suffix:semicolon
id|u32
id|regptr
op_assign
(paren
(paren
(paren
id|reg
op_lshift
l_int|16
)paren
op_amp
id|PTR_ADDRESS_MASK
)paren
op_or
(paren
id|channel
op_amp
id|PTR_CHANNELNUM_MASK
)paren
)paren
suffix:semicolon
id|outl
c_func
(paren
id|regptr
comma
id|card-&gt;iobase
op_plus
id|PTR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xff000000
)paren
(brace
r_int
id|size
op_assign
(paren
id|reg
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
suffix:semicolon
r_int
id|offset
op_assign
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|u32
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
id|size
)paren
op_minus
l_int|1
)paren
op_lshift
id|offset
suffix:semicolon
id|data
op_assign
(paren
id|data
op_lshift
id|offset
)paren
op_amp
id|mask
suffix:semicolon
id|data
op_or_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|DATA
)paren
op_amp
op_complement
id|mask
suffix:semicolon
)brace
id|outl
c_func
(paren
id|data
comma
id|card-&gt;iobase
op_plus
id|DATA
)paren
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
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sblive_readptr
id|u32
id|sblive_readptr
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|reg
comma
id|u32
id|channel
)paren
(brace
id|u32
id|regptr
comma
id|val
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|regptr
op_assign
(paren
(paren
id|reg
op_lshift
l_int|16
)paren
op_amp
id|PTR_ADDRESS_MASK
)paren
op_or
(paren
id|channel
op_amp
id|PTR_CHANNELNUM_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_amp
l_int|0xff000000
)paren
(brace
id|u32
id|mask
suffix:semicolon
id|u8
id|size
comma
id|offset
suffix:semicolon
id|size
op_assign
(paren
id|reg
op_rshift
l_int|24
)paren
op_amp
l_int|0x3f
suffix:semicolon
id|offset
op_assign
(paren
id|reg
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
suffix:semicolon
id|mask
op_assign
(paren
(paren
l_int|1
op_lshift
id|size
)paren
op_minus
l_int|1
)paren
op_lshift
id|offset
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
id|outl
c_func
(paren
id|regptr
comma
id|card-&gt;iobase
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|DATA
)paren
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
r_return
(paren
id|val
op_amp
id|mask
)paren
op_rshift
id|offset
suffix:semicolon
)brace
r_else
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|outl
c_func
(paren
id|regptr
comma
id|card-&gt;iobase
op_plus
id|PTR
)paren
suffix:semicolon
id|val
op_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|DATA
)paren
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
r_return
id|val
suffix:semicolon
)brace
)brace
DECL|function|emu10k1_irq_enable
r_void
id|emu10k1_irq_enable
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|irq_mask
)paren
(brace
id|u32
id|val
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
l_string|&quot;emu10k1_irq_enable()&bslash;n&quot;
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
id|val
op_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|INTE
)paren
op_or
id|irq_mask
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
id|card-&gt;iobase
op_plus
id|INTE
)paren
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
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_irq_disable
r_void
id|emu10k1_irq_disable
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|irq_mask
)paren
(brace
id|u32
id|val
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
l_string|&quot;emu10k1_irq_disable()&bslash;n&quot;
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
id|val
op_assign
id|inl
c_func
(paren
id|card-&gt;iobase
op_plus
id|INTE
)paren
op_amp
op_complement
id|irq_mask
suffix:semicolon
id|outl
c_func
(paren
id|val
comma
id|card-&gt;iobase
op_plus
id|INTE
)paren
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
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_set_stop_on_loop
r_void
id|emu10k1_set_stop_on_loop
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|voicenum
)paren
(brace
multiline_comment|/* Voice interrupt */
r_if
c_cond
(paren
id|voicenum
op_ge
l_int|32
)paren
id|sblive_writeptr
c_func
(paren
id|card
comma
id|SOLEH
op_or
(paren
(paren
l_int|0x0100
op_or
(paren
id|voicenum
op_minus
l_int|32
)paren
)paren
op_lshift
l_int|16
)paren
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_else
id|sblive_writeptr
c_func
(paren
id|card
comma
id|SOLEL
op_or
(paren
(paren
l_int|0x0100
op_or
id|voicenum
)paren
op_lshift
l_int|16
)paren
comma
l_int|0
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_clear_stop_on_loop
r_void
id|emu10k1_clear_stop_on_loop
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|voicenum
)paren
(brace
multiline_comment|/* Voice interrupt */
r_if
c_cond
(paren
id|voicenum
op_ge
l_int|32
)paren
id|sblive_writeptr
c_func
(paren
id|card
comma
id|SOLEH
op_or
(paren
(paren
l_int|0x0100
op_or
(paren
id|voicenum
op_minus
l_int|32
)paren
)paren
op_lshift
l_int|16
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_else
id|sblive_writeptr
c_func
(paren
id|card
comma
id|SOLEL
op_or
(paren
(paren
l_int|0x0100
op_or
id|voicenum
)paren
op_lshift
l_int|16
)paren
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|sblive_wcwait
r_static
r_void
id|sblive_wcwait
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u32
id|wait
)paren
(brace
r_volatile
r_int
id|uCount
suffix:semicolon
id|u32
id|newtime
op_assign
l_int|0
comma
id|curtime
suffix:semicolon
id|curtime
op_assign
id|emu10k1_readfn0
c_func
(paren
id|card
comma
id|WC_SAMPLECOUNTER
)paren
suffix:semicolon
r_while
c_loop
(paren
id|wait
op_decrement
)paren
(brace
id|uCount
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|uCount
op_increment
OL
id|TIMEOUT
)paren
(brace
id|newtime
op_assign
id|emu10k1_readfn0
c_func
(paren
id|card
comma
id|WC_SAMPLECOUNTER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newtime
op_ne
id|curtime
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|uCount
op_ge
id|TIMEOUT
)paren
r_break
suffix:semicolon
id|curtime
op_assign
id|newtime
suffix:semicolon
)brace
)brace
DECL|function|emu10k1_ac97_read
id|u16
id|emu10k1_ac97_read
c_func
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
id|u8
id|reg
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|codec-&gt;private_data
suffix:semicolon
id|u16
id|data
suffix:semicolon
r_int
r_int
id|flags
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
id|outb
c_func
(paren
id|reg
comma
id|card-&gt;iobase
op_plus
id|AC97ADDRESS
)paren
suffix:semicolon
id|data
op_assign
id|inw
c_func
(paren
id|card-&gt;iobase
op_plus
id|AC97DATA
)paren
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
r_return
id|data
suffix:semicolon
)brace
DECL|function|emu10k1_ac97_write
r_void
id|emu10k1_ac97_write
c_func
(paren
r_struct
id|ac97_codec
op_star
id|codec
comma
id|u8
id|reg
comma
id|u16
id|value
)paren
(brace
r_struct
id|emu10k1_card
op_star
id|card
op_assign
id|codec-&gt;private_data
suffix:semicolon
r_int
r_int
id|flags
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
id|outb
c_func
(paren
id|reg
comma
id|card-&gt;iobase
op_plus
id|AC97ADDRESS
)paren
suffix:semicolon
id|outw
c_func
(paren
id|value
comma
id|card-&gt;iobase
op_plus
id|AC97DATA
)paren
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
)brace
multiline_comment|/*********************************************************&n;*            MPU access functions                        *&n;**********************************************************/
DECL|function|emu10k1_mpu_write_data
r_int
id|emu10k1_mpu_write_data
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u8
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
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
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|card-&gt;iobase
op_plus
id|MUSTAT
)paren
op_amp
id|MUSTAT_ORDYN
)paren
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|data
comma
id|card-&gt;iobase
op_plus
id|MUDATA
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|ret
op_assign
op_minus
l_int|1
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
r_return
id|ret
suffix:semicolon
)brace
DECL|function|emu10k1_mpu_read_data
r_int
id|emu10k1_mpu_read_data
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
id|u8
op_star
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
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
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|card-&gt;iobase
op_plus
id|MUSTAT
)paren
op_amp
id|MUSTAT_IRDYN
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|data
op_assign
id|inb
c_func
(paren
id|card-&gt;iobase
op_plus
id|MUDATA
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|ret
op_assign
op_minus
l_int|1
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
r_return
id|ret
suffix:semicolon
)brace
DECL|function|emu10k1_mpu_reset
r_int
id|emu10k1_mpu_reset
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
id|u8
id|status
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
l_string|&quot;emu10k1_mpu_reset()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;mpuacqcount
op_eq
l_int|0
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|MUCMD_RESET
comma
id|card-&gt;iobase
op_plus
id|MUCMD
)paren
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
id|sblive_wcwait
c_func
(paren
id|card
comma
l_int|8
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
id|outb
c_func
(paren
id|MUCMD_RESET
comma
id|card-&gt;iobase
op_plus
id|MUCMD
)paren
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
id|sblive_wcwait
c_func
(paren
id|card
comma
l_int|8
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
id|outb
c_func
(paren
id|MUCMD_ENTERUARTMODE
comma
id|card-&gt;iobase
op_plus
id|MUCMD
)paren
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
id|sblive_wcwait
c_func
(paren
id|card
comma
l_int|8
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
id|status
op_assign
id|inb
c_func
(paren
id|card-&gt;iobase
op_plus
id|MUDATA
)paren
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
r_if
c_cond
(paren
id|status
op_eq
l_int|0xfe
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_mpu_acquire
r_int
id|emu10k1_mpu_acquire
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
multiline_comment|/* FIXME: This should be a macro */
op_increment
id|card-&gt;mpuacqcount
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu10k1_mpu_release
r_int
id|emu10k1_mpu_release
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
multiline_comment|/* FIXME: this should be a macro */
op_decrement
id|card-&gt;mpuacqcount
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof