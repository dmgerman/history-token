macro_line|#ifndef __SOUND_INITVAL_H
DECL|macro|__SOUND_INITVAL_H
mdefine_line|#define __SOUND_INITVAL_H
multiline_comment|/*&n; *  Init values for soundcard modules&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|macro|SNDRV_AUTO_PORT
mdefine_line|#define SNDRV_AUTO_PORT&t;&t;1
DECL|macro|SNDRV_AUTO_IRQ
mdefine_line|#define SNDRV_AUTO_IRQ&t;&t;0xffff
DECL|macro|SNDRV_AUTO_DMA
mdefine_line|#define SNDRV_AUTO_DMA&t;&t;0xffff
DECL|macro|SNDRV_AUTO_DMA_SIZE
mdefine_line|#define SNDRV_AUTO_DMA_SIZE&t;(0x7fffffff)
DECL|macro|SNDRV_DEFAULT_IDX1
mdefine_line|#define SNDRV_DEFAULT_IDX1&t;(-1)
DECL|macro|SNDRV_DEFAULT_STR1
mdefine_line|#define SNDRV_DEFAULT_STR1&t;NULL
DECL|macro|SNDRV_DEFAULT_ENABLE1
mdefine_line|#define SNDRV_DEFAULT_ENABLE1&t;1
DECL|macro|SNDRV_DEFAULT_PORT1
mdefine_line|#define SNDRV_DEFAULT_PORT1&t;SNDRV_AUTO_PORT
DECL|macro|SNDRV_DEFAULT_IRQ1
mdefine_line|#define SNDRV_DEFAULT_IRQ1&t;SNDRV_AUTO_IRQ
DECL|macro|SNDRV_DEFAULT_DMA1
mdefine_line|#define SNDRV_DEFAULT_DMA1&t;SNDRV_AUTO_DMA
DECL|macro|SNDRV_DEFAULT_DMA_SIZE1
mdefine_line|#define SNDRV_DEFAULT_DMA_SIZE1&t;SNDRV_AUTO_DMA_SIZE
DECL|macro|SNDRV_DEFAULT_PTR1
mdefine_line|#define SNDRV_DEFAULT_PTR1&t;SNDRV_DEFAULT_STR1
DECL|macro|SNDRV_DEFAULT_IDX
mdefine_line|#define SNDRV_DEFAULT_IDX&t;{ [0 ... (SNDRV_CARDS-1)] = -1 }
DECL|macro|SNDRV_DEFAULT_STR
mdefine_line|#define SNDRV_DEFAULT_STR&t;{ [0 ... (SNDRV_CARDS-1)] = NULL }
DECL|macro|SNDRV_DEFAULT_ENABLE
mdefine_line|#define SNDRV_DEFAULT_ENABLE&t;{ 1, [1 ... (SNDRV_CARDS-1)] = 0 }
DECL|macro|SNDRV_DEFAULT_ENABLE_PNP
mdefine_line|#define SNDRV_DEFAULT_ENABLE_PNP { [0 ... (SNDRV_CARDS-1)] = 1 }
macro_line|#ifdef CONFIG_PNP
DECL|macro|SNDRV_DEFAULT_ENABLE_ISAPNP
mdefine_line|#define SNDRV_DEFAULT_ENABLE_ISAPNP SNDRV_DEFAULT_ENABLE_PNP
macro_line|#else
DECL|macro|SNDRV_DEFAULT_ENABLE_ISAPNP
mdefine_line|#define SNDRV_DEFAULT_ENABLE_ISAPNP SNDRV_DEFAULT_ENABLE
macro_line|#endif
DECL|macro|SNDRV_DEFAULT_PORT
mdefine_line|#define SNDRV_DEFAULT_PORT&t;{ [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_PORT }
DECL|macro|SNDRV_DEFAULT_IRQ
mdefine_line|#define SNDRV_DEFAULT_IRQ&t;{ [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_IRQ }
DECL|macro|SNDRV_DEFAULT_DMA
mdefine_line|#define SNDRV_DEFAULT_DMA&t;{ [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_DMA }
DECL|macro|SNDRV_DEFAULT_DMA_SIZE
mdefine_line|#define SNDRV_DEFAULT_DMA_SIZE&t;{ [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_DMA_SIZE }
DECL|macro|SNDRV_DEFAULT_PTR
mdefine_line|#define SNDRV_DEFAULT_PTR&t;SNDRV_DEFAULT_STR
macro_line|#ifdef SNDRV_LEGACY_AUTO_PROBE
DECL|function|snd_legacy_auto_probe
r_static
r_int
id|snd_legacy_auto_probe
c_func
(paren
r_int
r_int
op_star
id|ports
comma
r_int
(paren
op_star
id|probe
)paren
(paren
r_int
r_int
id|port
)paren
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* number of detected cards */
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
op_star
id|ports
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|probe
c_func
(paren
op_star
id|ports
)paren
op_ge
l_int|0
)paren
id|result
op_increment
suffix:semicolon
id|ports
op_increment
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SNDRV_LEGACY_FIND_FREE_IRQ
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|function|snd_legacy_empty_irq_handler
r_static
id|irqreturn_t
id|snd_legacy_empty_irq_handler
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
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|snd_legacy_find_free_irq
r_static
r_int
id|snd_legacy_find_free_irq
c_func
(paren
r_int
op_star
id|irq_table
)paren
(brace
r_while
c_loop
(paren
op_star
id|irq_table
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_irq
c_func
(paren
op_star
id|irq_table
comma
id|snd_legacy_empty_irq_handler
comma
id|SA_INTERRUPT
comma
l_string|&quot;ALSA Test IRQ&quot;
comma
(paren
r_void
op_star
)paren
id|irq_table
)paren
)paren
(brace
id|free_irq
c_func
(paren
op_star
id|irq_table
comma
(paren
r_void
op_star
)paren
id|irq_table
)paren
suffix:semicolon
r_return
op_star
id|irq_table
suffix:semicolon
)brace
id|irq_table
op_increment
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SNDRV_LEGACY_FIND_FREE_DMA
DECL|function|snd_legacy_find_free_dma
r_static
r_int
id|snd_legacy_find_free_dma
c_func
(paren
r_int
op_star
id|dma_table
)paren
(brace
r_while
c_loop
(paren
op_star
id|dma_table
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_dma
c_func
(paren
op_star
id|dma_table
comma
l_string|&quot;ALSA Test DMA&quot;
)paren
)paren
(brace
id|free_dma
c_func
(paren
op_star
id|dma_table
)paren
suffix:semicolon
r_return
op_star
id|dma_table
suffix:semicolon
)brace
id|dma_table
op_increment
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __SOUND_INITVAL_H */
eof
