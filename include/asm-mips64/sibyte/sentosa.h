multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_SIBYTE_SENTOSA_H
DECL|macro|__ASM_SIBYTE_SENTOSA_H
mdefine_line|#define __ASM_SIBYTE_SENTOSA_H
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_int.h&gt;
macro_line|#ifdef CONFIG_SIBYTE_SENTOSA
DECL|macro|SIBYTE_BOARD_NAME
mdefine_line|#define SIBYTE_BOARD_NAME &quot;BCM91250E (Sentosa)&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SIBYTE_RHONE
DECL|macro|SIBYTE_BOARD_NAME
mdefine_line|#define SIBYTE_BOARD_NAME &quot;BCM91125E (Rhone)&quot;
macro_line|#endif
multiline_comment|/* Generic bus chip selects */
macro_line|#ifdef CONFIG_SIBYTE_RHONE
DECL|macro|LEDS_CS
mdefine_line|#define LEDS_CS         6
DECL|macro|LEDS_PHYS
mdefine_line|#define LEDS_PHYS       0x1d0a0000
macro_line|#endif
multiline_comment|/* GPIOs */
DECL|macro|K_GPIO_DBG_LED
mdefine_line|#define K_GPIO_DBG_LED  0
macro_line|#endif /* __ASM_SIBYTE_SENTOSA_H */
eof
