multiline_comment|/*&n; *&n; *&n; * Copyright (c) 2003 Silicon Graphics, Inc.  All Rights Reserved.&n; * &n; * This program is free software; you can redistribute it and/or modify it &n; * under the terms of version 2 of the GNU General Public License &n; * as published by the Free Software Foundation.&n; * &n; * This program is distributed in the hope that it would be useful, but &n; * WITHOUT ANY WARRANTY; without even the implied warranty of &n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. &n; * &n; * Further, this software is distributed without any warranty that it is &n; * free of the rightful claim of any third person regarding infringement &n; * or the like.  Any license provided herein, whether implied or &n; * otherwise, applies only to this software file.  Patent licenses, if &n; * any, provided herein do not apply to combinations of this program with &n; * other software, or any other product whatsoever.&n; * &n; * You should have received a copy of the GNU General Public &n; * License along with this program; if not, write the Free Software &n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; * &n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy, &n; * Mountain View, CA  94043, or:&n; * &n; * http://www.sgi.com &n; * &n; * For further information regarding this notice, see: &n; * &n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/sn/pda.h&gt;
macro_line|#include &lt;asm/sn/leds.h&gt;
r_extern
r_void
id|sn_lb_int_war_check
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|irqreturn_t
id|timer_interrupt
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|macro|SN_LB_INT_WAR_INTERVAL
mdefine_line|#define SN_LB_INT_WAR_INTERVAL 100
r_void
DECL|function|sn_timer_interrupt
id|sn_timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* LED blinking */
r_if
c_cond
(paren
op_logical_neg
id|pda-&gt;hb_count
op_decrement
)paren
(brace
id|pda-&gt;hb_count
op_assign
id|HZ
op_div
l_int|2
suffix:semicolon
id|set_led_bits
c_func
(paren
id|pda-&gt;hb_state
op_xor_assign
id|LED_CPU_HEARTBEAT
comma
id|LED_CPU_HEARTBEAT
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Blink&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|enable_shub_wars_1_1
c_func
(paren
)paren
)paren
(brace
multiline_comment|/* Bugfix code for SHUB 1.1 */
r_if
c_cond
(paren
id|pda-&gt;pio_shub_war_cam_addr
)paren
op_star
id|pda-&gt;pio_shub_war_cam_addr
op_assign
l_int|0x8000000000000010UL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pda-&gt;sn_lb_int_war_ticks
op_eq
l_int|0
)paren
id|sn_lb_int_war_check
c_func
(paren
)paren
suffix:semicolon
id|pda-&gt;sn_lb_int_war_ticks
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pda-&gt;sn_lb_int_war_ticks
op_ge
id|SN_LB_INT_WAR_INTERVAL
)paren
id|pda-&gt;sn_lb_int_war_ticks
op_assign
l_int|0
suffix:semicolon
)brace
eof
