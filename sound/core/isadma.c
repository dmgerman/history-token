multiline_comment|/*&n; *  ISA DMA support functions&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/*&n; * Defining following add some delay. Maybe this helps for some broken&n; * ISA DMA controllers.&n; */
DECL|macro|HAVE_REALLY_SLOW_DMA_CONTROLLER
macro_line|#undef HAVE_REALLY_SLOW_DMA_CONTROLLER
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#ifdef CONFIG_ISA
multiline_comment|/*&n; *&n; */
DECL|function|snd_dma_program
r_void
id|snd_dma_program
c_func
(paren
r_int
r_int
id|dma
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|mode
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|claim_dma_lock
c_func
(paren
)paren
suffix:semicolon
id|disable_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|clear_dma_ff
c_func
(paren
id|dma
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|dma
comma
id|mode
)paren
suffix:semicolon
id|set_dma_addr
c_func
(paren
id|dma
comma
id|addr
)paren
suffix:semicolon
id|set_dma_count
c_func
(paren
id|dma
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
id|DMA_MODE_NO_ENABLE
)paren
)paren
id|enable_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|release_dma_lock
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_dma_disable
r_void
id|snd_dma_disable
c_func
(paren
r_int
r_int
id|dma
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|flags
op_assign
id|claim_dma_lock
c_func
(paren
)paren
suffix:semicolon
id|clear_dma_ff
c_func
(paren
id|dma
)paren
suffix:semicolon
id|disable_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|release_dma_lock
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_dma_residue
r_int
r_int
id|snd_dma_residue
c_func
(paren
r_int
r_int
id|dma
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|result
suffix:semicolon
id|flags
op_assign
id|claim_dma_lock
c_func
(paren
)paren
suffix:semicolon
id|clear_dma_ff
c_func
(paren
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isa_dma_bridge_buggy
)paren
id|disable_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|result
op_assign
id|get_dma_residue
c_func
(paren
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isa_dma_bridge_buggy
)paren
id|enable_dma
c_func
(paren
id|dma
)paren
suffix:semicolon
id|release_dma_lock
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ISA */
eof
