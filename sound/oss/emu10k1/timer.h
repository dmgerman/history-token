multiline_comment|/*&n; **********************************************************************&n; *     timer.h&n; *     Copyright (C) 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _TIMER_H
DECL|macro|_TIMER_H
mdefine_line|#define _TIMER_H
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &quot;hwaccess.h&quot;
DECL|struct|emu_timer
r_struct
id|emu_timer
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* current number of interrupts */
DECL|member|count_max
id|u32
id|count_max
suffix:semicolon
multiline_comment|/* number of interrupts needed to schedule the bh */
DECL|member|delay
id|u32
id|delay
suffix:semicolon
multiline_comment|/* timer delay */
)brace
suffix:semicolon
r_void
id|emu10k1_timer_install
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|emu_timer
op_star
comma
id|u32
)paren
suffix:semicolon
r_void
id|emu10k1_timer_uninstall
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|emu_timer
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_timer_enable
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|emu_timer
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_timer_disable
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|emu_timer
op_star
)paren
suffix:semicolon
DECL|macro|TIMER_STOPPED
mdefine_line|#define TIMER_STOPPED &t;&t;&t;0xffffffff 
DECL|macro|TIMER_STATE_INSTALLED
mdefine_line|#define TIMER_STATE_INSTALLED &t;&t;0x01
DECL|macro|TIMER_STATE_ACTIVE
mdefine_line|#define TIMER_STATE_ACTIVE&t;&t;0x02
DECL|macro|TIMER_STATE_UNINSTALLED
mdefine_line|#define TIMER_STATE_UNINSTALLED &t;0x04
macro_line|#endif /* _TIMER_H */
eof
