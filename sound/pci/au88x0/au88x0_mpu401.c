multiline_comment|/*&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Routines for control of MPU-401 in UART mode&n; *&n; *   Modified for the Aureal Vortex based Soundcards&n; *   by Manuel Jander (mjande@embedded.cl).&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &quot;au88x0.h&quot;
multiline_comment|/* Check for mpu401 mmio support. */
multiline_comment|/* MPU401 legacy support is only provided as a emergency fallback *&n; * for older versions of ALSA. Its usage is strongly discouraged. */
macro_line|#ifndef MPU401_HW_AUREAL
DECL|macro|VORTEX_MPU401_LEGACY
mdefine_line|#define VORTEX_MPU401_LEGACY
macro_line|#endif
multiline_comment|/* Vortex MPU401 defines. */
DECL|macro|MIDI_CLOCK_DIV
mdefine_line|#define MIDI_CLOCK_DIV      0x61
multiline_comment|/* Standart MPU401 defines. */
DECL|macro|MPU401_RESET
mdefine_line|#define MPU401_RESET&t;&t;0xff
DECL|macro|MPU401_ENTER_UART
mdefine_line|#define MPU401_ENTER_UART&t;0x3f
DECL|macro|MPU401_ACK
mdefine_line|#define MPU401_ACK&t;&t;    0xfe
DECL|function|snd_vortex_midi
r_static
r_int
id|__devinit
id|snd_vortex_midi
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
(brace
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
r_int
id|temp
comma
id|mode
suffix:semicolon
id|mpu401_t
op_star
id|mpu
suffix:semicolon
r_int
id|port
suffix:semicolon
macro_line|#ifdef VORTEX_MPU401_LEGACY
multiline_comment|/* EnableHardCodedMPU401Port() */
multiline_comment|/* Enable Legacy MIDI Interface port. */
id|port
op_assign
(paren
l_int|0x03
op_lshift
l_int|5
)paren
suffix:semicolon
multiline_comment|/* FIXME: static address. 0x330 */
id|temp
op_assign
(paren
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
)paren
op_amp
op_complement
id|CTRL_MIDI_PORT
)paren
op_or
id|CTRL_MIDI_EN
op_or
id|port
suffix:semicolon
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
comma
id|temp
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* Disable Legacy MIDI Interface port. */
id|temp
op_assign
(paren
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
)paren
op_amp
op_complement
id|CTRL_MIDI_PORT
)paren
op_amp
op_complement
id|CTRL_MIDI_EN
suffix:semicolon
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
comma
id|temp
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Mpu401UartInit() */
id|mode
op_assign
l_int|1
suffix:semicolon
id|temp
op_assign
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL2
)paren
op_amp
l_int|0xffff00cf
suffix:semicolon
id|temp
op_or_assign
(paren
id|MIDI_CLOCK_DIV
op_lshift
l_int|8
)paren
op_or
(paren
(paren
id|mode
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
)paren
op_lshift
l_int|4
suffix:semicolon
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL2
comma
id|temp
)paren
suffix:semicolon
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_MIDI_CMD
comma
id|MPU401_RESET
)paren
suffix:semicolon
multiline_comment|/* Set some kind of mode */
r_if
c_cond
(paren
id|mode
)paren
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_MIDI_CMD
comma
id|MPU401_ENTER_UART
)paren
suffix:semicolon
multiline_comment|/* Check if anything is OK. */
id|temp
op_assign
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_MIDI_DATA
)paren
suffix:semicolon
r_if
c_cond
(paren
id|temp
op_ne
id|MPU401_ACK
multiline_comment|/*0xfe */
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;midi port doesn&squot;t acknowledge!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Enable MPU401 interrupts. */
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_IRQ_CTRL
comma
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_IRQ_CTRL
)paren
op_or
id|IRQ_MIDI
)paren
suffix:semicolon
multiline_comment|/* Create MPU401 instance. */
macro_line|#ifdef VORTEX_MPU401_LEGACY
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|snd_mpu401_uart_new
c_func
(paren
id|vortex-&gt;card
comma
l_int|0
comma
id|MPU401_HW_MPU401
comma
l_int|0x330
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|rmidi
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
comma
(paren
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
)paren
op_amp
op_complement
id|CTRL_MIDI_PORT
)paren
op_amp
op_complement
id|CTRL_MIDI_EN
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
macro_line|#else
id|port
op_assign
(paren
r_int
r_int
)paren
(paren
id|vortex-&gt;mmio
op_plus
(paren
id|VORTEX_MIDI_DATA
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|snd_mpu401_uart_new
c_func
(paren
id|vortex-&gt;card
comma
l_int|0
comma
id|MPU401_HW_AUREAL
comma
id|port
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
op_amp
id|rmidi
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
comma
(paren
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL
)paren
op_amp
op_complement
id|CTRL_MIDI_PORT
)paren
op_amp
op_complement
id|CTRL_MIDI_EN
)paren
suffix:semicolon
r_return
id|temp
suffix:semicolon
)brace
id|mpu
op_assign
id|rmidi-&gt;private_data
suffix:semicolon
id|mpu-&gt;cport
op_assign
(paren
r_int
r_int
)paren
(paren
id|vortex-&gt;mmio
op_plus
(paren
id|VORTEX_MIDI_CMD
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
macro_line|#endif
id|vortex-&gt;rmidi
op_assign
id|rmidi
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
