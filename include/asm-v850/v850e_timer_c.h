multiline_comment|/*&n; * include/asm-v850/v850e_timer_c.h -- `Timer C&squot; component often used&n; *&t;with the V850E cpu core&n; *&n; *  Copyright (C) 2001,03  NEC Electronics Corporation&n; *  Copyright (C) 2001,03  Miles Bader &lt;miles@gnu.org&gt;&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * Written by Miles Bader &lt;miles@gnu.org&gt;&n; */
multiline_comment|/* NOTE: this include file currently contains only enough to allow us to&n;   use timer C as an interrupt pass-through.  */
macro_line|#ifndef __V850_V850E_TIMER_C_H__
DECL|macro|__V850_V850E_TIMER_C_H__
mdefine_line|#define __V850_V850E_TIMER_C_H__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;&t;/* Pick up chip-specific defs.  */
multiline_comment|/* Timer C (16-bit interval timers).  */
multiline_comment|/* Control register 0 for timer C.  */
DECL|macro|V850E_TIMER_C_TMCC0_ADDR
mdefine_line|#define V850E_TIMER_C_TMCC0_ADDR(n) (V850E_TIMER_C_BASE_ADDR + 0x6 + 0x10 *(n))
DECL|macro|V850E_TIMER_C_TMCC0
mdefine_line|#define V850E_TIMER_C_TMCC0(n)&t;  (*(volatile u8 *)V850E_TIMER_C_TMCC0_ADDR(n))
DECL|macro|V850E_TIMER_C_TMCC0_CAE
mdefine_line|#define V850E_TIMER_C_TMCC0_CAE&t;  0x01 /* clock action enable */
DECL|macro|V850E_TIMER_C_TMCC0_CE
mdefine_line|#define V850E_TIMER_C_TMCC0_CE&t;  0x02 /* count enable */
multiline_comment|/* ... */
multiline_comment|/* Control register 1 for timer C.  */
DECL|macro|V850E_TIMER_C_TMCC1_ADDR
mdefine_line|#define V850E_TIMER_C_TMCC1_ADDR(n) (V850E_TIMER_C_BASE_ADDR + 0x8 + 0x10 *(n))
DECL|macro|V850E_TIMER_C_TMCC1
mdefine_line|#define V850E_TIMER_C_TMCC1(n)&t;  (*(volatile u8 *)V850E_TIMER_C_TMCC1_ADDR(n))
DECL|macro|V850E_TIMER_C_TMCC1_CMS0
mdefine_line|#define V850E_TIMER_C_TMCC1_CMS0  0x01 /* capture/compare mode select (ccc0) */
DECL|macro|V850E_TIMER_C_TMCC1_CMS1
mdefine_line|#define V850E_TIMER_C_TMCC1_CMS1  0x02 /* capture/compare mode select (ccc1) */
multiline_comment|/* ... */
multiline_comment|/* Interrupt edge-sensitivity control for timer C.  */
DECL|macro|V850E_TIMER_C_SESC_ADDR
mdefine_line|#define V850E_TIMER_C_SESC_ADDR(n) (V850E_TIMER_C_BASE_ADDR + 0x9 + 0x10 *(n))
DECL|macro|V850E_TIMER_C_SESC
mdefine_line|#define V850E_TIMER_C_SESC(n)&t;  (*(volatile u8 *)V850E_TIMER_C_SESC_ADDR(n))
multiline_comment|/* ...etc... */
macro_line|#endif /* __V850_V850E_TIMER_C_H__  */
eof
