multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef _SIBYTE_BOARD_H
DECL|macro|_SIBYTE_BOARD_H
mdefine_line|#define _SIBYTE_BOARD_H
macro_line|#ifdef CONFIG_SIBYTE_BOARD
macro_line|#if defined(CONFIG_SIBYTE_SWARM) || defined(CONFIG_SIBYTE_PTSWARM) || &bslash;&n;    defined(CONFIG_SIBYTE_CRHONE) || defined(CONFIG_SIBYTE_CRHINE)
macro_line|#include &lt;asm/sibyte/swarm.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_SIBYTE_SENTOSA) || defined(CONFIG_SIBYTE_RHONE)
macro_line|#include &lt;asm/sibyte/sentosa.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_SIBYTE_CARMEL
macro_line|#include &lt;asm/sibyte/carmel.h&gt;
macro_line|#endif
macro_line|#ifdef __ASSEMBLY__
macro_line|#ifdef LEDS_PHYS
DECL|macro|setleds
mdefine_line|#define setleds(t0,t1,c0,c1,c2,c3) &bslash;&n;&t;li&t;t0, (LEDS_PHYS|0xa0000000); &bslash;&n;&t;li&t;t1, c0; &bslash;&n;&t;sb&t;t1, 0x18(t0); &bslash;&n;&t;li&t;t1, c1; &bslash;&n;&t;sb&t;t1, 0x10(t0); &bslash;&n;&t;li&t;t1, c2; &bslash;&n;&t;sb&t;t1, 0x08(t0); &bslash;&n;&t;li&t;t1, c3; &bslash;&n;&t;sb&t;t1, 0x00(t0)
macro_line|#else
DECL|macro|setleds
mdefine_line|#define setleds(t0,t1,c0,c1,c2,c3)
macro_line|#endif /* LEDS_PHYS */
macro_line|#else
r_void
id|swarm_setup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef LEDS_PHYS
r_extern
r_void
id|setleds
c_func
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
macro_line|#else
DECL|macro|setleds
mdefine_line|#define setleds(s) do { } while (0)
macro_line|#endif /* LEDS_PHYS */
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* CONFIG_SIBYTE_BOARD */
macro_line|#endif /* _SIBYTE_BOARD_H */
eof
