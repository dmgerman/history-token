multiline_comment|/*&n; * $Id: au88x0_game.c,v 1.9 2003/09/22 03:51:28 mjander Exp $&n; *&n; *  Manuel Jander.&n; *&n; *  Based on the work of:&n; *  Vojtech Pavlik&n; *  Raymond Ingles&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; *&n; * Based 90% on Vojtech Pavlik pcigame driver.&n; * Merged and modified by Manuel Jander, for the OpenVortex&n; * driver. (email: mjander@embedded.cl).&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &quot;au88x0.h&quot;
macro_line|#include &lt;linux/gameport.h&gt;
DECL|macro|VORTEX_GAME_DWAIT
mdefine_line|#define VORTEX_GAME_DWAIT&t;20&t;/* 20 ms */
DECL|variable|gameport
r_static
r_struct
id|gameport
id|gameport
suffix:semicolon
DECL|function|vortex_game_read
r_static
r_int
r_char
id|vortex_game_read
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
id|vortex_t
op_star
id|vortex
op_assign
id|gameport-&gt;driver
suffix:semicolon
r_return
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_GAME_LEGACY
)paren
suffix:semicolon
)brace
DECL|function|vortex_game_trigger
r_static
r_void
id|vortex_game_trigger
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
id|vortex_t
op_star
id|vortex
op_assign
id|gameport-&gt;driver
suffix:semicolon
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_GAME_LEGACY
comma
l_int|0xff
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|vortex_game_cooked_read
id|vortex_game_cooked_read
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
op_star
id|axes
comma
r_int
op_star
id|buttons
)paren
(brace
id|vortex_t
op_star
id|vortex
op_assign
id|gameport-&gt;driver
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|buttons
op_assign
(paren
op_complement
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_GAME_LEGACY
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|axes
(braket
id|i
)braket
op_assign
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_GAME_AXIS
op_plus
(paren
id|i
op_star
id|AXIS_SIZE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|axes
(braket
id|i
)braket
op_eq
id|AXIS_RANGE
)paren
id|axes
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vortex_game_open
r_static
r_int
id|vortex_game_open
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
id|mode
)paren
(brace
id|vortex_t
op_star
id|vortex
op_assign
id|gameport-&gt;driver
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|GAMEPORT_MODE_COOKED
suffix:colon
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL2
comma
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL2
)paren
op_or
id|CTRL2_GAME_ADCMODE
)paren
suffix:semicolon
id|wait_ms
c_func
(paren
id|VORTEX_GAME_DWAIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|GAMEPORT_MODE_RAW
suffix:colon
id|hwwrite
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL2
comma
id|hwread
c_func
(paren
id|vortex-&gt;mmio
comma
id|VORTEX_CTRL2
)paren
op_amp
op_complement
id|CTRL2_GAME_ADCMODE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vortex_gameport_register
r_static
r_int
id|vortex_gameport_register
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
(brace
id|vortex-&gt;gameport
op_assign
op_amp
id|gameport
suffix:semicolon
id|vortex-&gt;gameport-&gt;driver
op_assign
id|vortex
suffix:semicolon
id|vortex-&gt;gameport-&gt;fuzz
op_assign
l_int|64
suffix:semicolon
id|vortex-&gt;gameport-&gt;read
op_assign
id|vortex_game_read
suffix:semicolon
id|vortex-&gt;gameport-&gt;trigger
op_assign
id|vortex_game_trigger
suffix:semicolon
id|vortex-&gt;gameport-&gt;cooked_read
op_assign
id|vortex_game_cooked_read
suffix:semicolon
id|vortex-&gt;gameport-&gt;open
op_assign
id|vortex_game_open
suffix:semicolon
id|gameport_register_port
c_func
(paren
(paren
r_struct
id|gameport
op_star
)paren
id|vortex-&gt;gameport
)paren
suffix:semicolon
multiline_comment|/*&t;printk(KERN_INFO &quot;gameport%d: %s at speed %d kHz&bslash;n&quot;,&n;&t;&t;vortex-&gt;gameport-&gt;number, vortex-&gt;pci_dev-&gt;name, vortex-&gt;gameport-&gt;speed);&n;*/
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vortex_gameport_unregister
r_static
r_int
id|vortex_gameport_unregister
c_func
(paren
id|vortex_t
op_star
id|vortex
)paren
(brace
r_if
c_cond
(paren
id|vortex-&gt;gameport
op_ne
l_int|NULL
)paren
id|gameport_unregister_port
c_func
(paren
id|vortex-&gt;gameport
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
