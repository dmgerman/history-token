multiline_comment|/*&n; **********************************************************************&n; *     timer.c&n; *     Copyright (C) 1999, 2000 Creative Labs, inc.&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
multiline_comment|/* 3/6/2000&t;Improved support for different timer delays  Rui Sousa */
multiline_comment|/* 4/3/2000&t;Implemented timer list using list.h &t;     Rui Sousa */
macro_line|#include &quot;hwaccess.h&quot;
macro_line|#include &quot;8010.h&quot;
macro_line|#include &quot;irqmgr.h&quot;
macro_line|#include &quot;timer.h&quot;
multiline_comment|/* Try to schedule only once per fragment */
DECL|function|emu10k1_timer_irqhandler
r_void
id|emu10k1_timer_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
)paren
(brace
r_struct
id|emu_timer
op_star
id|t
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|card-&gt;timer_lock
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|card-&gt;timers
)paren
(brace
id|t
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|emu_timer
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;state
op_amp
id|TIMER_STATE_ACTIVE
)paren
(brace
id|t-&gt;count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;count
op_eq
id|t-&gt;count_max
)paren
(brace
id|t-&gt;count
op_assign
l_int|0
suffix:semicolon
id|tasklet_hi_schedule
c_func
(paren
op_amp
id|t-&gt;tasklet
)paren
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|card-&gt;timer_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_timer_install
r_void
id|emu10k1_timer_install
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|emu_timer
op_star
id|timer
comma
id|u16
id|delay
)paren
(brace
r_struct
id|emu_timer
op_star
id|t
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|delay
OL
l_int|5
)paren
id|delay
op_assign
l_int|5
suffix:semicolon
id|timer-&gt;delay
op_assign
id|delay
suffix:semicolon
id|timer-&gt;state
op_assign
id|TIMER_STATE_INSTALLED
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
id|timer-&gt;count_max
op_assign
id|timer-&gt;delay
op_div
(paren
id|card-&gt;timer_delay
OL
l_int|1024
ques
c_cond
id|card-&gt;timer_delay
suffix:colon
l_int|1024
)paren
suffix:semicolon
id|timer-&gt;count
op_assign
id|timer-&gt;count_max
op_minus
l_int|1
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|timer-&gt;list
comma
op_amp
id|card-&gt;timers
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;timer_delay
OG
id|delay
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;timer_delay
op_eq
id|TIMER_STOPPED
)paren
id|emu10k1_irq_enable
c_func
(paren
id|card
comma
id|INTE_INTERVALTIMERENB
)paren
suffix:semicolon
id|card-&gt;timer_delay
op_assign
id|delay
suffix:semicolon
id|delay
op_assign
(paren
id|delay
OL
l_int|1024
ques
c_cond
id|delay
suffix:colon
l_int|1024
)paren
suffix:semicolon
id|emu10k1_timer_set
c_func
(paren
id|card
comma
id|delay
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|card-&gt;timers
)paren
(brace
id|t
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|emu_timer
comma
id|list
)paren
suffix:semicolon
id|t-&gt;count_max
op_assign
id|t-&gt;delay
op_div
id|delay
suffix:semicolon
multiline_comment|/* don&squot;t want to think much, just force scheduling &n;&t;&t;&t;   on the next interrupt */
id|t-&gt;count
op_assign
id|t-&gt;count_max
op_minus
l_int|1
suffix:semicolon
)brace
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;timer rate --&gt; %u&bslash;n&quot;
comma
id|delay
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_timer_uninstall
r_void
id|emu10k1_timer_uninstall
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|emu_timer
op_star
id|timer
)paren
(brace
r_struct
id|emu_timer
op_star
id|t
suffix:semicolon
r_struct
id|list_head
op_star
id|entry
suffix:semicolon
id|u16
id|delay
op_assign
id|TIMER_STOPPED
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|timer-&gt;state
op_eq
id|TIMER_STATE_UNINSTALLED
)paren
r_return
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|timer-&gt;list
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|card-&gt;timers
)paren
(brace
id|t
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|emu_timer
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;delay
OL
id|delay
)paren
id|delay
op_assign
id|t-&gt;delay
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;timer_delay
op_ne
id|delay
)paren
(brace
id|card-&gt;timer_delay
op_assign
id|delay
suffix:semicolon
r_if
c_cond
(paren
id|delay
op_eq
id|TIMER_STOPPED
)paren
id|emu10k1_irq_disable
c_func
(paren
id|card
comma
id|INTE_INTERVALTIMERENB
)paren
suffix:semicolon
r_else
(brace
id|delay
op_assign
(paren
id|delay
OL
l_int|1024
ques
c_cond
id|delay
suffix:colon
l_int|1024
)paren
suffix:semicolon
id|emu10k1_timer_set
c_func
(paren
id|card
comma
id|delay
)paren
suffix:semicolon
id|list_for_each
c_func
(paren
id|entry
comma
op_amp
id|card-&gt;timers
)paren
(brace
id|t
op_assign
id|list_entry
c_func
(paren
id|entry
comma
r_struct
id|emu_timer
comma
id|list
)paren
suffix:semicolon
id|t-&gt;count_max
op_assign
id|t-&gt;delay
op_div
id|delay
suffix:semicolon
id|t-&gt;count
op_assign
id|t-&gt;count_max
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|DPD
c_func
(paren
l_int|2
comma
l_string|&quot;timer rate --&gt; %u&bslash;n&quot;
comma
id|delay
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
id|timer-&gt;state
op_assign
id|TIMER_STATE_UNINSTALLED
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_timer_enable
r_void
id|emu10k1_timer_enable
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|emu_timer
op_star
id|timer
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
id|timer-&gt;state
op_or_assign
id|TIMER_STATE_ACTIVE
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|emu10k1_timer_disable
r_void
id|emu10k1_timer_disable
c_func
(paren
r_struct
id|emu10k1_card
op_star
id|card
comma
r_struct
id|emu_timer
op_star
id|timer
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
id|timer-&gt;state
op_and_assign
op_complement
id|TIMER_STATE_ACTIVE
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|card-&gt;timer_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
