multiline_comment|/*&n;** asm/blinken.h -- m68k blinkenlights support (currently hp300 only)&n;**&n;** (c) 1998 Phil Blundell &lt;philb@gnu.org&gt;&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;*/
macro_line|#ifndef _M68K_BLINKEN_H
DECL|macro|_M68K_BLINKEN_H
mdefine_line|#define _M68K_BLINKEN_H
macro_line|#include &lt;asm/setup.h&gt;
DECL|macro|HP300_LEDS
mdefine_line|#define HP300_LEDS&t;&t;0xf001ffff
DECL|function|blinken_leds
r_static
id|__inline__
r_void
id|blinken_leds
c_func
(paren
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
id|MACH_IS_HP300
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_char
op_star
)paren
id|HP300_LEDS
)paren
op_assign
(paren
id|x
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
