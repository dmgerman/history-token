multiline_comment|/*&n; * include/asm-v850/v850e_timer_d.h -- `Timer D&squot; component often used&n; *&t;with the V850E cpu core&n; *&n; *  Copyright (C) 2001,02,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,02,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
macro_line|#ifndef __V850_V850E_TIMER_D_H__
DECL|macro|__V850_V850E_TIMER_D_H__
mdefine_line|#define __V850_V850E_TIMER_D_H__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;&t;/* Pick up chip-specific defs.  */
multiline_comment|/* Timer D (16-bit interval timers).  */
multiline_comment|/* Count registers for timer D.  */
DECL|macro|V850E_TIMER_D_TMD_ADDR
mdefine_line|#define V850E_TIMER_D_TMD_ADDR(n) (V850E_TIMER_D_TMD_BASE_ADDR + 0x10 * (n))
DECL|macro|V850E_TIMER_D_TMD
mdefine_line|#define V850E_TIMER_D_TMD(n)&t;  (*(volatile u16 *)V850E_TIMER_D_TMD_ADDR(n))
multiline_comment|/* Count compare registers for timer D.  */
DECL|macro|V850E_TIMER_D_CMD_ADDR
mdefine_line|#define V850E_TIMER_D_CMD_ADDR(n) (V850E_TIMER_D_CMD_BASE_ADDR + 0x10 * (n))
DECL|macro|V850E_TIMER_D_CMD
mdefine_line|#define V850E_TIMER_D_CMD(n)&t;  (*(volatile u16 *)V850E_TIMER_D_CMD_ADDR(n))
multiline_comment|/* Control registers for timer D.  */
DECL|macro|V850E_TIMER_D_TMCD_ADDR
mdefine_line|#define V850E_TIMER_D_TMCD_ADDR(n) (V850E_TIMER_D_TMCD_BASE_ADDR + 0x10 * (n))
DECL|macro|V850E_TIMER_D_TMCD
mdefine_line|#define V850E_TIMER_D_TMCD(n)&t;   (*(volatile u8 *)V850E_TIMER_D_TMCD_ADDR(n))
multiline_comment|/* Control bits for timer D.  */
DECL|macro|V850E_TIMER_D_TMCD_CE
mdefine_line|#define V850E_TIMER_D_TMCD_CE  &t;   0x2 /* count enable */
DECL|macro|V850E_TIMER_D_TMCD_CAE
mdefine_line|#define V850E_TIMER_D_TMCD_CAE&t;   0x1 /* clock action enable */
multiline_comment|/* Clock divider setting (log2).  */
DECL|macro|V850E_TIMER_D_TMCD_CS
mdefine_line|#define V850E_TIMER_D_TMCD_CS(divlog2) (((divlog2) - V850E_TIMER_D_TMCD_CS_MIN) &lt;&lt; 4)
multiline_comment|/* Minimum clock divider setting (log2).  */
macro_line|#ifndef V850E_TIMER_D_TMCD_CS_MIN /* Can be overridden by mach-specific hdrs */
DECL|macro|V850E_TIMER_D_TMCD_CS_MIN
mdefine_line|#define V850E_TIMER_D_TMCD_CS_MIN  2 /* Default is correct for the v850e/ma1 */
macro_line|#endif
multiline_comment|/* Maximum clock divider setting (log2).  */
DECL|macro|V850E_TIMER_D_TMCD_CS_MAX
mdefine_line|#define V850E_TIMER_D_TMCD_CS_MAX  (V850E_TIMER_D_TMCD_CS_MIN + 7)
multiline_comment|/* Return the clock-divider (log2) of timer D unit N.  */
DECL|macro|V850E_TIMER_D_DIVLOG2
mdefine_line|#define V850E_TIMER_D_DIVLOG2(n) &bslash;&n;  (((V850E_TIMER_D_TMCD(n) &gt;&gt; 4) &amp; 0x7) + V850E_TIMER_D_TMCD_CS_MIN)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Start interval timer TIMER (0-3).  The timer will issue the&n;   corresponding INTCMD interrupt RATE times per second.  This function&n;   does not enable the interrupt.  */
r_extern
r_void
id|v850e_timer_d_configure
(paren
r_int
id|timer
comma
r_int
id|rate
)paren
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __V850_V850E_TIMER_D_H__  */
eof
