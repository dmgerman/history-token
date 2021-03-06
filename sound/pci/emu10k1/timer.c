multiline_comment|/*&n; *  Copyright (c) by Lee Revell &lt;rlrevell@joe-job.com&gt;&n; *                   Clemens Ladisch &lt;clemens@ladisch.de&gt;&n; *  Routines for control of EMU10K1 chips&n; *&n; *  BUGS:&n; *    --&n; *&n; *  TODO:&n; *    --&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
DECL|function|snd_emu10k1_timer_start
r_static
r_int
id|snd_emu10k1_timer_start
c_func
(paren
id|snd_timer_t
op_star
id|timer
)paren
(brace
id|emu10k1_t
op_star
id|emu
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
id|emu
op_assign
id|snd_timer_chip
c_func
(paren
id|timer
)paren
suffix:semicolon
id|delay
op_assign
id|timer-&gt;sticks
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|delay
OL
l_int|5
)paren
multiline_comment|/* minimum time is 5 ticks */
id|delay
op_assign
l_int|5
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_intr_enable
c_func
(paren
id|emu
comma
id|INTE_INTERVALTIMERENB
)paren
suffix:semicolon
id|outw
c_func
(paren
id|delay
op_amp
id|TIMER_RATE_MASK
comma
id|emu-&gt;port
op_plus
id|TIMER
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_timer_stop
r_static
r_int
id|snd_emu10k1_timer_stop
c_func
(paren
id|snd_timer_t
op_star
id|timer
)paren
(brace
id|emu10k1_t
op_star
id|emu
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|emu
op_assign
id|snd_timer_chip
c_func
(paren
id|timer
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_emu10k1_intr_disable
c_func
(paren
id|emu
comma
id|INTE_INTERVALTIMERENB
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|emu-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_emu10k1_timer_precise_resolution
r_static
r_int
id|snd_emu10k1_timer_precise_resolution
c_func
(paren
id|snd_timer_t
op_star
id|timer
comma
r_int
r_int
op_star
id|num
comma
r_int
r_int
op_star
id|den
)paren
(brace
op_star
id|num
op_assign
l_int|1
suffix:semicolon
op_star
id|den
op_assign
l_int|48000
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_emu10k1_timer_hw
r_static
r_struct
id|_snd_timer_hardware
id|snd_emu10k1_timer_hw
op_assign
(brace
dot
id|flags
op_assign
id|SNDRV_TIMER_HW_AUTO
comma
dot
id|resolution
op_assign
l_int|20833
comma
multiline_comment|/* 1 sample @ 48KHZ = 20.833...us */
dot
id|ticks
op_assign
l_int|1024
comma
dot
id|start
op_assign
id|snd_emu10k1_timer_start
comma
dot
id|stop
op_assign
id|snd_emu10k1_timer_stop
comma
dot
id|precise_resolution
op_assign
id|snd_emu10k1_timer_precise_resolution
comma
)brace
suffix:semicolon
DECL|function|snd_emu10k1_timer
r_int
id|__devinit
id|snd_emu10k1_timer
c_func
(paren
id|emu10k1_t
op_star
id|emu
comma
r_int
id|device
)paren
(brace
id|snd_timer_t
op_star
id|timer
op_assign
l_int|NULL
suffix:semicolon
id|snd_timer_id_t
id|tid
suffix:semicolon
r_int
id|err
suffix:semicolon
id|tid.dev_class
op_assign
id|SNDRV_TIMER_CLASS_CARD
suffix:semicolon
id|tid.dev_sclass
op_assign
id|SNDRV_TIMER_SCLASS_NONE
suffix:semicolon
id|tid.card
op_assign
id|emu-&gt;card-&gt;number
suffix:semicolon
id|tid.device
op_assign
id|device
suffix:semicolon
id|tid.subdevice
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_timer_new
c_func
(paren
id|emu-&gt;card
comma
l_string|&quot;EMU10K1&quot;
comma
op_amp
id|tid
comma
op_amp
id|timer
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|strcpy
c_func
(paren
id|timer-&gt;name
comma
l_string|&quot;EMU10K1 timer&quot;
)paren
suffix:semicolon
id|timer-&gt;private_data
op_assign
id|emu
suffix:semicolon
id|timer-&gt;hw
op_assign
id|snd_emu10k1_timer_hw
suffix:semicolon
)brace
id|emu-&gt;timer
op_assign
id|timer
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
eof
