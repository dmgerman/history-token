multiline_comment|/*&n; * linux/include/asm-arm/arch-omap/gpio.h&n; *&n; * OMAP GPIO handling defines and functions&n; *&n; * Copyright (C) 2003 Nokia Corporation&n; *&n; * Written by Juha Yrj&#xfffd;l&#xfffd; &lt;juha.yrjola@nokia.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; */
macro_line|#ifndef __ASM_ARCH_OMAP_GPIO_H
DECL|macro|__ASM_ARCH_OMAP_GPIO_H
mdefine_line|#define __ASM_ARCH_OMAP_GPIO_H
macro_line|#include &lt;asm/arch/hardware.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|OMAP_MPUIO_BASE
mdefine_line|#define OMAP_MPUIO_BASE&t;&t;&t;0xfffb5000
DECL|macro|OMAP_MPUIO_INPUT_LATCH
mdefine_line|#define OMAP_MPUIO_INPUT_LATCH&t;&t;0x00
DECL|macro|OMAP_MPUIO_OUTPUT
mdefine_line|#define OMAP_MPUIO_OUTPUT&t;&t;0x04
DECL|macro|OMAP_MPUIO_IO_CNTL
mdefine_line|#define OMAP_MPUIO_IO_CNTL&t;&t;0x08
DECL|macro|OMAP_MPUIO_KBR_LATCH
mdefine_line|#define OMAP_MPUIO_KBR_LATCH&t;&t;0x10
DECL|macro|OMAP_MPUIO_KBC
mdefine_line|#define OMAP_MPUIO_KBC&t;&t;&t;0x14
DECL|macro|OMAP_MPUIO_GPIO_EVENT_MODE
mdefine_line|#define OMAP_MPUIO_GPIO_EVENT_MODE&t;0x18
DECL|macro|OMAP_MPUIO_GPIO_INT_EDGE
mdefine_line|#define OMAP_MPUIO_GPIO_INT_EDGE&t;0x1c
DECL|macro|OMAP_MPUIO_KBD_INT
mdefine_line|#define OMAP_MPUIO_KBD_INT&t;&t;0x20
DECL|macro|OMAP_MPUIO_GPIO_INT
mdefine_line|#define OMAP_MPUIO_GPIO_INT&t;&t;0x24
DECL|macro|OMAP_MPUIO_KBD_MASKIT
mdefine_line|#define OMAP_MPUIO_KBD_MASKIT&t;&t;0x28
DECL|macro|OMAP_MPUIO_GPIO_MASKIT
mdefine_line|#define OMAP_MPUIO_GPIO_MASKIT&t;&t;0x2c
DECL|macro|OMAP_MPUIO_GPIO_DEBOUNCING
mdefine_line|#define OMAP_MPUIO_GPIO_DEBOUNCING&t;0x30
DECL|macro|OMAP_MPUIO_LATCH
mdefine_line|#define OMAP_MPUIO_LATCH&t;&t;0x34
DECL|macro|OMAP_MPUIO
mdefine_line|#define OMAP_MPUIO(nr)&t;&t;(OMAP_MAX_GPIO_LINES + (nr))
DECL|macro|OMAP_GPIO_IS_MPUIO
mdefine_line|#define OMAP_GPIO_IS_MPUIO(nr)&t;((nr) &gt;= OMAP_MAX_GPIO_LINES)
DECL|macro|OMAP_GPIO_IRQ
mdefine_line|#define OMAP_GPIO_IRQ(nr)&t;(OMAP_GPIO_IS_MPUIO(nr) ? &bslash;&n;&t;&t;&t;&t; IH_MPUIO_BASE + ((nr) &amp; 0x0f) : &bslash;&n;&t;&t;&t;&t; IH_GPIO_BASE + ((nr) &amp; 0x3f))
multiline_comment|/* For EDGECTRL */
DECL|macro|OMAP_GPIO_NO_EDGE
mdefine_line|#define OMAP_GPIO_NO_EDGE&t;  0x00
DECL|macro|OMAP_GPIO_FALLING_EDGE
mdefine_line|#define OMAP_GPIO_FALLING_EDGE&t;  0x01
DECL|macro|OMAP_GPIO_RISING_EDGE
mdefine_line|#define OMAP_GPIO_RISING_EDGE&t;  0x02
DECL|macro|OMAP_GPIO_BOTH_EDGES
mdefine_line|#define OMAP_GPIO_BOTH_EDGES&t;  0x03
r_extern
r_int
id|omap_gpio_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Call from board init only */
r_extern
r_int
id|omap_request_gpio
c_func
(paren
r_int
id|gpio
)paren
suffix:semicolon
r_extern
r_void
id|omap_free_gpio
c_func
(paren
r_int
id|gpio
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_gpio_direction
c_func
(paren
r_int
id|gpio
comma
r_int
id|is_input
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_gpio_dataout
c_func
(paren
r_int
id|gpio
comma
r_int
id|enable
)paren
suffix:semicolon
r_extern
r_int
id|omap_get_gpio_datain
c_func
(paren
r_int
id|gpio
)paren
suffix:semicolon
r_extern
r_void
id|omap_set_gpio_edge_ctrl
c_func
(paren
r_int
id|gpio
comma
r_int
id|edge
)paren
suffix:semicolon
macro_line|#endif
eof
