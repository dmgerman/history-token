multiline_comment|/*&n; *  Routines for GF1 DMA control&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/gus.h&gt;
DECL|function|snd_gf1_dma_ack
r_void
id|snd_gf1_dma_ack
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_DRAM_DMA_CONTROL
comma
l_int|0x00
)paren
suffix:semicolon
id|snd_gf1_look8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_DRAM_DMA_CONTROL
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_dma_program
r_void
id|snd_gf1_dma_program
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|buf_addr
comma
r_int
r_int
id|count
comma
r_int
r_int
id|cmd
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_int
r_char
id|dma_cmd
suffix:semicolon
r_int
r_int
id|address_high
suffix:semicolon
singleline_comment|// snd_printk(&quot;dma_transfer: addr=0x%x, buf=0x%lx, count=0x%x&bslash;n&quot;, addr, (long) buf, count);
r_if
c_cond
(paren
id|gus-&gt;gf1.dma1
OG
l_int|3
)paren
(brace
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
(brace
id|address
op_assign
id|addr
op_rshift
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|addr
op_amp
l_int|0x1f
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;snd_gf1_dma_transfer: unaligned address (0x%x)?&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|address
op_assign
(paren
id|addr
op_amp
l_int|0x000c0000
)paren
op_or
(paren
(paren
id|addr
op_amp
l_int|0x0003ffff
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|address
op_assign
id|addr
suffix:semicolon
)brace
id|dma_cmd
op_assign
id|SNDRV_GF1_DMA_ENABLE
op_or
(paren
r_int
r_int
)paren
id|cmd
suffix:semicolon
macro_line|#if 0
id|dma_cmd
op_or_assign
l_int|0x08
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|dma_cmd
op_amp
id|SNDRV_GF1_DMA_16BIT
)paren
(brace
id|count
op_increment
suffix:semicolon
id|count
op_and_assign
op_complement
l_int|1
suffix:semicolon
multiline_comment|/* align */
)brace
r_if
c_cond
(paren
id|gus-&gt;gf1.dma1
OG
l_int|3
)paren
(brace
id|dma_cmd
op_or_assign
id|SNDRV_GF1_DMA_WIDTH16
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|count
op_and_assign
op_complement
l_int|1
suffix:semicolon
multiline_comment|/* align */
)brace
id|snd_gf1_dma_ack
c_func
(paren
id|gus
)paren
suffix:semicolon
id|snd_dma_program
c_func
(paren
id|gus-&gt;gf1.dma1
comma
id|buf_addr
comma
id|count
comma
id|dma_cmd
op_amp
id|SNDRV_GF1_DMA_READ
ques
c_cond
id|DMA_MODE_READ
suffix:colon
id|DMA_MODE_WRITE
)paren
suffix:semicolon
macro_line|#if 0
id|snd_printk
c_func
(paren
l_string|&quot;address = 0x%x, count = 0x%x, dma_cmd = 0x%x&bslash;n&quot;
comma
id|address
op_lshift
l_int|1
comma
id|count
comma
id|dma_cmd
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.enh_mode
)paren
(brace
id|address_high
op_assign
(paren
(paren
id|address
op_rshift
l_int|16
)paren
op_amp
l_int|0x000000f0
)paren
op_or
(paren
id|address
op_amp
l_int|0x0000000f
)paren
suffix:semicolon
id|snd_gf1_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GW_DRAM_DMA_LOW
comma
(paren
r_int
r_int
)paren
(paren
id|address
op_rshift
l_int|4
)paren
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_DRAM_DMA_HIGH
comma
(paren
r_int
r_char
)paren
id|address_high
)paren
suffix:semicolon
)brace
r_else
id|snd_gf1_write16
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GW_DRAM_DMA_LOW
comma
(paren
r_int
r_int
)paren
(paren
id|address
op_rshift
l_int|4
)paren
)paren
suffix:semicolon
id|snd_gf1_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_DRAM_DMA_CONTROL
comma
id|dma_cmd
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|snd_gf1_dma_next_block
r_static
id|snd_gf1_dma_block_t
op_star
id|snd_gf1_dma_next_block
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_dma_block_t
op_star
id|block
suffix:semicolon
multiline_comment|/* PCM block have bigger priority than synthesizer one */
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_data_pcm
)paren
(brace
id|block
op_assign
id|gus-&gt;gf1.dma_data_pcm
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_data_pcm_last
op_eq
id|block
)paren
(brace
id|gus-&gt;gf1.dma_data_pcm
op_assign
id|gus-&gt;gf1.dma_data_pcm_last
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|gus-&gt;gf1.dma_data_pcm
op_assign
id|block-&gt;next
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_data_synth
)paren
(brace
id|block
op_assign
id|gus-&gt;gf1.dma_data_synth
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_data_synth_last
op_eq
id|block
)paren
(brace
id|gus-&gt;gf1.dma_data_synth
op_assign
id|gus-&gt;gf1.dma_data_synth_last
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|gus-&gt;gf1.dma_data_synth
op_assign
id|block-&gt;next
suffix:semicolon
)brace
)brace
r_else
(brace
id|block
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|block
)paren
(brace
id|gus-&gt;gf1.dma_ack
op_assign
id|block-&gt;ack
suffix:semicolon
id|gus-&gt;gf1.dma_private_data
op_assign
id|block-&gt;private_data
suffix:semicolon
)brace
r_return
id|block
suffix:semicolon
)brace
DECL|function|snd_gf1_dma_interrupt
r_static
r_void
id|snd_gf1_dma_interrupt
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_dma_block_t
op_star
id|block
suffix:semicolon
id|snd_gf1_dma_ack
c_func
(paren
id|gus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_ack
)paren
id|gus-&gt;gf1
dot
id|dma_ack
c_func
(paren
id|gus
comma
id|gus-&gt;gf1.dma_private_data
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|gus-&gt;dma_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_data_pcm
op_eq
l_int|NULL
op_logical_and
id|gus-&gt;gf1.dma_data_synth
op_eq
l_int|NULL
)paren
(brace
id|gus-&gt;gf1.dma_ack
op_assign
l_int|NULL
suffix:semicolon
id|gus-&gt;gf1.dma_flags
op_and_assign
op_complement
id|SNDRV_GF1_DMA_TRIGGER
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|gus-&gt;dma_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|block
op_assign
id|snd_gf1_dma_next_block
c_func
(paren
id|gus
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|gus-&gt;dma_lock
)paren
suffix:semicolon
id|snd_gf1_dma_program
c_func
(paren
id|gus
comma
id|block-&gt;addr
comma
id|block-&gt;buf_addr
comma
id|block-&gt;count
comma
(paren
r_int
r_int
)paren
id|block-&gt;cmd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;program dma (IRQ) - addr = 0x%x, buffer = 0x%lx, count = 0x%x, cmd = 0x%x&bslash;n&quot;
comma
id|addr
comma
(paren
r_int
)paren
id|buffer
comma
id|count
comma
id|cmd
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|snd_gf1_dma_init
r_int
id|snd_gf1_dma_init
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|down
c_func
(paren
op_amp
id|gus-&gt;dma_mutex
)paren
suffix:semicolon
id|gus-&gt;gf1.dma_shared
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_shared
OG
l_int|1
)paren
(brace
id|up
c_func
(paren
op_amp
id|gus-&gt;dma_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|gus-&gt;gf1.interrupt_handler_dma_write
op_assign
id|snd_gf1_dma_interrupt
suffix:semicolon
id|gus-&gt;gf1.dma_data_pcm
op_assign
id|gus-&gt;gf1.dma_data_pcm_last
op_assign
id|gus-&gt;gf1.dma_data_synth
op_assign
id|gus-&gt;gf1.dma_data_synth_last
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|gus-&gt;dma_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gf1_dma_done
r_int
id|snd_gf1_dma_done
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_dma_block_t
op_star
id|block
suffix:semicolon
id|down
c_func
(paren
op_amp
id|gus-&gt;dma_mutex
)paren
suffix:semicolon
id|gus-&gt;gf1.dma_shared
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gus-&gt;gf1.dma_shared
)paren
(brace
id|snd_dma_disable
c_func
(paren
id|gus-&gt;gf1.dma1
)paren
suffix:semicolon
id|snd_gf1_set_default_handlers
c_func
(paren
id|gus
comma
id|SNDRV_GF1_HANDLER_DMA_WRITE
)paren
suffix:semicolon
id|snd_gf1_dma_ack
c_func
(paren
id|gus
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|block
op_assign
id|gus-&gt;gf1.dma_data_pcm
)paren
)paren
(brace
id|gus-&gt;gf1.dma_data_pcm
op_assign
id|block-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|block
op_assign
id|gus-&gt;gf1.dma_data_synth
)paren
)paren
(brace
id|gus-&gt;gf1.dma_data_synth
op_assign
id|block-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
)brace
id|gus-&gt;gf1.dma_data_pcm_last
op_assign
id|gus-&gt;gf1.dma_data_synth_last
op_assign
l_int|NULL
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|gus-&gt;dma_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gf1_dma_transfer_block
r_int
id|snd_gf1_dma_transfer_block
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
comma
id|snd_gf1_dma_block_t
op_star
id|__block
comma
r_int
id|atomic
comma
r_int
id|synth
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|snd_gf1_dma_block_t
op_star
id|block
suffix:semicolon
id|block
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|block
)paren
comma
id|atomic
ques
c_cond
id|GFP_ATOMIC
suffix:colon
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;gf1: DMA transfer failure; not enough memory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
op_star
id|block
op_assign
op_star
id|__block
suffix:semicolon
id|block-&gt;next
op_assign
l_int|NULL
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;addr = 0x%x, buffer = 0x%lx, count = 0x%x, cmd = 0x%x&bslash;n&quot;
comma
id|block-&gt;addr
comma
(paren
r_int
)paren
id|block-&gt;buffer
comma
id|block-&gt;count
comma
id|block-&gt;cmd
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;gus-&gt;gf1.dma_data_pcm_last = 0x%lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|gus-&gt;gf1.dma_data_pcm_last
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;gus-&gt;gf1.dma_data_pcm = 0x%lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|gus-&gt;gf1.dma_data_pcm
)paren
suffix:semicolon
macro_line|#endif
id|spin_lock_irqsave
c_func
(paren
op_amp
id|gus-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|synth
)paren
(brace
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_data_synth_last
)paren
(brace
id|gus-&gt;gf1.dma_data_synth_last-&gt;next
op_assign
id|block
suffix:semicolon
id|gus-&gt;gf1.dma_data_synth_last
op_assign
id|block
suffix:semicolon
)brace
r_else
(brace
id|gus-&gt;gf1.dma_data_synth
op_assign
id|gus-&gt;gf1.dma_data_synth_last
op_assign
id|block
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|gus-&gt;gf1.dma_data_pcm_last
)paren
(brace
id|gus-&gt;gf1.dma_data_pcm_last-&gt;next
op_assign
id|block
suffix:semicolon
id|gus-&gt;gf1.dma_data_pcm_last
op_assign
id|block
suffix:semicolon
)brace
r_else
(brace
id|gus-&gt;gf1.dma_data_pcm
op_assign
id|gus-&gt;gf1.dma_data_pcm_last
op_assign
id|block
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|gus-&gt;gf1.dma_flags
op_amp
id|SNDRV_GF1_DMA_TRIGGER
)paren
)paren
(brace
id|gus-&gt;gf1.dma_flags
op_or_assign
id|SNDRV_GF1_DMA_TRIGGER
suffix:semicolon
id|block
op_assign
id|snd_gf1_dma_next_block
c_func
(paren
id|gus
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|snd_gf1_dma_program
c_func
(paren
id|gus
comma
id|block-&gt;addr
comma
id|block-&gt;buf_addr
comma
id|block-&gt;count
comma
(paren
r_int
r_int
)paren
id|block-&gt;cmd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|gus-&gt;dma_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
