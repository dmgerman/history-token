multiline_comment|/*&n; * Copyright (C) 2000, 2001 Broadcom Corporation&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version 2&n; * of the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; */
macro_line|#ifndef __ASM_SIBYTE_SWARM_H
DECL|macro|__ASM_SIBYTE_SWARM_H
mdefine_line|#define __ASM_SIBYTE_SWARM_H
macro_line|#include &lt;asm/sibyte/sb1250.h&gt;
macro_line|#include &lt;asm/sibyte/sb1250_int.h&gt;
macro_line|#ifdef CONFIG_SIBYTE_SWARM
DECL|macro|SIBYTE_BOARD_NAME
mdefine_line|#define SIBYTE_BOARD_NAME &quot;BCM91250A (SWARM)&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SIBYTE_PTSWARM
DECL|macro|SIBYTE_BOARD_NAME
mdefine_line|#define SIBYTE_BOARD_NAME &quot;PTSWARM&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SIBYTE_CRHONE
DECL|macro|SIBYTE_BOARD_NAME
mdefine_line|#define SIBYTE_BOARD_NAME &quot;BCM91125C (CRhone)&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SIBYTE_CRHINE
DECL|macro|SIBYTE_BOARD_NAME
mdefine_line|#define SIBYTE_BOARD_NAME &quot;BCM91120C (CRhine)&quot;
macro_line|#endif
multiline_comment|/* Generic bus chip selects */
DECL|macro|LEDS_CS
mdefine_line|#define LEDS_CS         3
DECL|macro|LEDS_PHYS
mdefine_line|#define LEDS_PHYS       0x100a0000
macro_line|#if defined(CONFIG_SIBYTE_SWARM) || defined(CONFIG_SIBYTE_PTSWARM)
DECL|macro|IDE_CS
mdefine_line|#define IDE_CS          4
DECL|macro|IDE_PHYS
mdefine_line|#define IDE_PHYS        0x100b0000
DECL|macro|PCMCIA_CS
mdefine_line|#define PCMCIA_CS       6
DECL|macro|PCMCIA_PHYS
mdefine_line|#define PCMCIA_PHYS     0x11000000
macro_line|#endif
multiline_comment|/* GPIOs */
macro_line|#if defined(CONFIG_SIBYTE_SWARM) || defined(CONFIG_SIBYTE_PTSWARM)
DECL|macro|K_GPIO_GB_IDE
mdefine_line|#define K_GPIO_GB_IDE   4
DECL|macro|K_INT_GB_IDE
mdefine_line|#define K_INT_GB_IDE    (K_INT_GPIO_0 + K_GPIO_GB_IDE)
DECL|macro|K_GPIO_PC_READY
mdefine_line|#define K_GPIO_PC_READY 9
DECL|macro|K_INT_PC_READY
mdefine_line|#define K_INT_PC_READY  (K_INT_GPIO_0 + K_GPIO_PC_READY)
macro_line|#endif
macro_line|#endif /* __ASM_SIBYTE_SWARM_H */
eof
