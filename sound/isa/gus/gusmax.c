multiline_comment|/*&n; *  Driver for Gravis UltraSound MAX soundcard&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/gus.h&gt;
macro_line|#include &lt;sound/cs4231.h&gt;
DECL|macro|SNDRV_LEGACY_AUTO_PROBE
mdefine_line|#define SNDRV_LEGACY_AUTO_PROBE
DECL|macro|SNDRV_LEGACY_FIND_FREE_IRQ
mdefine_line|#define SNDRV_LEGACY_FIND_FREE_IRQ
DECL|macro|SNDRV_LEGACY_FIND_FREE_DMA
mdefine_line|#define SNDRV_LEGACY_FIND_FREE_DMA
DECL|macro|SNDRV_GET_ID
mdefine_line|#define SNDRV_GET_ID
macro_line|#include &lt;sound/initval.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Gravis UltraSound MAX&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_DEVICES
c_func
(paren
l_string|&quot;{{Gravis,UltraSound MAX}}&quot;
)paren
suffix:semicolon
DECL|variable|index
r_static
r_int
id|index
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IDX
suffix:semicolon
multiline_comment|/* Index 0-MAX */
DECL|variable|id
r_static
r_char
op_star
id|id
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_STR
suffix:semicolon
multiline_comment|/* ID for this card */
DECL|variable|enable
r_static
r_int
id|enable
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_ENABLE
suffix:semicolon
multiline_comment|/* Enable this card */
DECL|variable|port
r_static
r_int
id|port
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PORT
suffix:semicolon
multiline_comment|/* 0x220,0x230,0x240,0x250,0x260 */
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IRQ
suffix:semicolon
multiline_comment|/* 2,3,5,9,11,12,15 */
DECL|variable|dma1
r_static
r_int
id|dma1
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_DMA
suffix:semicolon
multiline_comment|/* 1,3,5,6,7 */
DECL|variable|dma2
r_static
r_int
id|dma2
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_DMA
suffix:semicolon
multiline_comment|/* 1,3,5,6,7 */
DECL|variable|joystick_dac
r_static
r_int
id|joystick_dac
(braket
id|SNDRV_CARDS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|SNDRV_CARDS
op_minus
l_int|1
)paren
)braket
op_assign
l_int|29
)brace
suffix:semicolon
multiline_comment|/* 0 to 31, (0.59V-4.52V or 0.389V-2.98V) */
DECL|variable|channels
r_static
r_int
id|channels
(braket
id|SNDRV_CARDS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|SNDRV_CARDS
op_minus
l_int|1
)paren
)braket
op_assign
l_int|24
)brace
suffix:semicolon
DECL|variable|pcm_channels
r_static
r_int
id|pcm_channels
(braket
id|SNDRV_CARDS
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
(paren
id|SNDRV_CARDS
op_minus
l_int|1
)paren
)braket
op_assign
l_int|2
)brace
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|index
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|index
comma
l_string|&quot;Index value for GUS MAX soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|index
comma
id|SNDRV_INDEX_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|id
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID string for GUS MAX soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|id
comma
id|SNDRV_ID_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|enable
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable GUS MAX soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|enable
comma
id|SNDRV_ENABLE_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|port
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;l&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|port
comma
l_string|&quot;Port # for GUS MAX driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|port
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{0x220},{0x230},{0x240},{0x250},{0x260}},dialog:list&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;IRQ # for GUS MAX driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|irq
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{3},{5},{9},{11},{12},{15}},dialog:list&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma1
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dma1
comma
l_string|&quot;DMA1 # for GUS MAX driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|dma1
comma
id|SNDRV_DMA_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma2
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|dma2
comma
l_string|&quot;DMA2 # for GUS MAX driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|dma2
comma
id|SNDRV_DMA_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|joystick_dac
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|joystick_dac
comma
l_string|&quot;Joystick DAC level 0.59V-4.52V or 0.389V-2.98V for GUS MAX driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|joystick_dac
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{0,31}}&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|channels
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|channels
comma
l_string|&quot;Used GF1 channels for GUS MAX driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|channels
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{14,32}}&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|pcm_channels
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|SNDRV_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|pcm_channels
comma
l_string|&quot;Reserved PCM channels for GUS MAX driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|pcm_channels
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{2,16}}&quot;
)paren
suffix:semicolon
DECL|struct|snd_gusmax
r_struct
id|snd_gusmax
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|gus
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
DECL|member|cs4231
id|cs4231_t
op_star
id|cs4231
suffix:semicolon
DECL|member|gus_status_reg
r_int
r_int
id|gus_status_reg
suffix:semicolon
DECL|member|pcm_status_reg
r_int
r_int
id|pcm_status_reg
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|snd_gusmax_cards
r_static
id|snd_card_t
op_star
id|snd_gusmax_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|function|snd_gusmax_detect
r_static
r_int
id|__init
id|snd_gusmax_detect
c_func
(paren
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* reset GF1 */
macro_line|#ifdef CONFIG_SND_DEBUG_DETECT
(brace
r_int
r_char
id|d
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|d
op_assign
id|snd_gf1_i_look8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
)paren
)paren
op_amp
l_int|0x07
)paren
op_ne
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;[0x%lx] check 1 failed - 0x%x&bslash;n&quot;
comma
id|gus-&gt;gf1.port
comma
id|d
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
macro_line|#else
r_if
c_cond
(paren
(paren
id|snd_gf1_i_look8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
)paren
op_amp
l_int|0x07
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
id|udelay
c_func
(paren
l_int|160
)paren
suffix:semicolon
id|snd_gf1_i_write8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* release reset */
id|udelay
c_func
(paren
l_int|160
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_DEBUG_DETECT
(brace
r_int
r_char
id|d
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|d
op_assign
id|snd_gf1_i_look8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
)paren
)paren
op_amp
l_int|0x07
)paren
op_ne
l_int|1
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;[0x%lx] check 2 failed - 0x%x&bslash;n&quot;
comma
id|gus-&gt;gf1.port
comma
id|d
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
macro_line|#else
r_if
c_cond
(paren
(paren
id|snd_gf1_i_look8
c_func
(paren
id|gus
comma
id|SNDRV_GF1_GB_RESET
)paren
op_amp
l_int|0x07
)paren
op_ne
l_int|1
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gusmax_interrupt
r_static
id|irqreturn_t
id|snd_gusmax_interrupt
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
r_struct
id|snd_gusmax
op_star
id|maxcard
op_assign
(paren
r_struct
id|snd_gusmax
op_star
)paren
id|dev_id
suffix:semicolon
r_int
id|loop
comma
id|max
op_assign
l_int|5
suffix:semicolon
r_int
id|handled
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|loop
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|maxcard-&gt;gus_status_reg
)paren
)paren
(brace
id|handled
op_assign
l_int|1
suffix:semicolon
id|snd_gus_interrupt
c_func
(paren
id|irq
comma
id|maxcard-&gt;gus
comma
id|regs
)paren
suffix:semicolon
id|loop
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|maxcard-&gt;pcm_status_reg
)paren
op_amp
l_int|0x01
)paren
(brace
multiline_comment|/* IRQ bit is set? */
id|handled
op_assign
l_int|1
suffix:semicolon
id|snd_cs4231_interrupt
c_func
(paren
id|irq
comma
id|maxcard-&gt;cs4231
comma
id|regs
)paren
suffix:semicolon
id|loop
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|loop
op_logical_and
op_decrement
id|max
OG
l_int|0
)paren
suffix:semicolon
r_return
id|IRQ_RETVAL
c_func
(paren
id|handled
)paren
suffix:semicolon
)brace
DECL|function|snd_gusmax_init
r_static
r_void
id|__init
id|snd_gusmax_init
c_func
(paren
r_int
id|dev
comma
id|snd_card_t
op_star
id|card
comma
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|gus-&gt;equal_irq
op_assign
l_int|1
suffix:semicolon
id|gus-&gt;codec_flag
op_assign
l_int|1
suffix:semicolon
id|gus-&gt;joystick_dac
op_assign
id|joystick_dac
(braket
id|dev
)braket
suffix:semicolon
multiline_comment|/* init control register */
id|gus-&gt;max_cntrl_val
op_assign
(paren
id|gus-&gt;gf1.port
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.dma1
OG
l_int|3
)paren
id|gus-&gt;max_cntrl_val
op_or_assign
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
id|gus-&gt;gf1.dma2
OG
l_int|3
)paren
id|gus-&gt;max_cntrl_val
op_or_assign
l_int|0x20
suffix:semicolon
id|gus-&gt;max_cntrl_val
op_or_assign
l_int|0x40
suffix:semicolon
id|outb
c_func
(paren
id|gus-&gt;max_cntrl_val
comma
id|GUSP
c_func
(paren
id|gus
comma
id|MAXCNTRLPORT
)paren
)paren
suffix:semicolon
)brace
DECL|macro|CS4231_PRIVATE
mdefine_line|#define CS4231_PRIVATE( left, right, shift, mute ) &bslash;&n;&t;&t;&t;((left &lt;&lt; 24)|(right &lt;&lt; 16)|(shift&lt;&lt;8)|mute)
DECL|function|snd_gusmax_mixer
r_static
r_int
id|__init
id|snd_gusmax_mixer
c_func
(paren
id|cs4231_t
op_star
id|chip
)paren
(brace
id|snd_card_t
op_star
id|card
op_assign
id|chip-&gt;card
suffix:semicolon
id|snd_ctl_elem_id_t
id|id1
comma
id|id2
suffix:semicolon
r_int
id|err
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|id1
comma
l_int|0
comma
r_sizeof
(paren
id|id1
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|id2
comma
l_int|0
comma
r_sizeof
(paren
id|id2
)paren
)paren
suffix:semicolon
id|id1.iface
op_assign
id|id2.iface
op_assign
id|SNDRV_CTL_ELEM_IFACE_MIXER
suffix:semicolon
multiline_comment|/* reassign AUXA to SYNTHESIZER */
id|strcpy
c_func
(paren
id|id1.name
comma
l_string|&quot;Aux Playback Switch&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|id2.name
comma
l_string|&quot;Synth Playback Switch&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_rename_id
c_func
(paren
id|card
comma
op_amp
id|id1
comma
op_amp
id|id2
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|strcpy
c_func
(paren
id|id1.name
comma
l_string|&quot;Aux Playback Volume&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|id2.name
comma
l_string|&quot;Synth Playback Volume&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_rename_id
c_func
(paren
id|card
comma
op_amp
id|id1
comma
op_amp
id|id2
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* reassign AUXB to CD */
id|strcpy
c_func
(paren
id|id1.name
comma
l_string|&quot;Aux Playback Switch&quot;
)paren
suffix:semicolon
id|id1.index
op_assign
l_int|1
suffix:semicolon
id|strcpy
c_func
(paren
id|id2.name
comma
l_string|&quot;CD Playback Switch&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_rename_id
c_func
(paren
id|card
comma
op_amp
id|id1
comma
op_amp
id|id2
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|strcpy
c_func
(paren
id|id1.name
comma
l_string|&quot;Aux Playback Volume&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|id2.name
comma
l_string|&quot;CD Playback Volume&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_rename_id
c_func
(paren
id|card
comma
op_amp
id|id1
comma
op_amp
id|id2
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
macro_line|#if 0
multiline_comment|/* reassign Mono Input to MIC */
r_if
c_cond
(paren
id|snd_mixer_group_rename
c_func
(paren
id|mixer
comma
id|SNDRV_MIXER_IN_MONO
comma
l_int|0
comma
id|SNDRV_MIXER_IN_MIC
comma
l_int|0
)paren
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
r_if
c_cond
(paren
id|snd_mixer_elem_rename
c_func
(paren
id|mixer
comma
id|SNDRV_MIXER_IN_MONO
comma
l_int|0
comma
id|SNDRV_MIXER_ETYPE_INPUT
comma
id|SNDRV_MIXER_IN_MIC
comma
l_int|0
)paren
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
r_if
c_cond
(paren
id|snd_mixer_elem_rename
c_func
(paren
id|mixer
comma
l_string|&quot;Mono Capture Volume&quot;
comma
l_int|0
comma
id|SNDRV_MIXER_ETYPE_VOLUME1
comma
l_string|&quot;Mic Capture Volume&quot;
comma
l_int|0
)paren
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
r_if
c_cond
(paren
id|snd_mixer_elem_rename
c_func
(paren
id|mixer
comma
l_string|&quot;Mono Capture Switch&quot;
comma
l_int|0
comma
id|SNDRV_MIXER_ETYPE_SWITCH1
comma
l_string|&quot;Mic Capture Switch&quot;
comma
l_int|0
)paren
OL
l_int|0
)paren
r_goto
id|__error
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gusmax_free
r_static
r_void
id|snd_gusmax_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_struct
id|snd_gusmax
op_star
id|maxcard
op_assign
(paren
r_struct
id|snd_gusmax
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|maxcard
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|maxcard-&gt;irq
op_ge
l_int|0
)paren
id|free_irq
c_func
(paren
id|maxcard-&gt;irq
comma
(paren
r_void
op_star
)paren
id|maxcard
)paren
suffix:semicolon
)brace
DECL|function|snd_gusmax_probe
r_static
r_int
id|__init
id|snd_gusmax_probe
c_func
(paren
r_int
id|dev
)paren
(brace
r_static
r_int
id|possible_irqs
(braket
)braket
op_assign
(brace
l_int|5
comma
l_int|11
comma
l_int|12
comma
l_int|9
comma
l_int|7
comma
l_int|15
comma
l_int|3
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_int
id|possible_dmas
(braket
)braket
op_assign
(brace
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|1
comma
l_int|3
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_int
id|xirq
comma
id|xdma1
comma
id|xdma2
comma
id|err
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
op_assign
l_int|NULL
suffix:semicolon
id|cs4231_t
op_star
id|cs4231
suffix:semicolon
r_struct
id|snd_gusmax
op_star
id|maxcard
suffix:semicolon
id|card
op_assign
id|snd_card_new
c_func
(paren
id|index
(braket
id|dev
)braket
comma
id|id
(braket
id|dev
)braket
comma
id|THIS_MODULE
comma
r_sizeof
(paren
r_struct
id|snd_gusmax
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|card-&gt;private_free
op_assign
id|snd_gusmax_free
suffix:semicolon
id|maxcard
op_assign
(paren
r_struct
id|snd_gusmax
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|maxcard-&gt;card
op_assign
id|card
suffix:semicolon
id|maxcard-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|xirq
op_assign
id|irq
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xirq
op_eq
id|SNDRV_AUTO_IRQ
)paren
(brace
r_if
c_cond
(paren
(paren
id|xirq
op_assign
id|snd_legacy_find_free_irq
c_func
(paren
id|possible_irqs
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
l_string|&quot;unable to find a free IRQ&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|xdma1
op_assign
id|dma1
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xdma1
op_eq
id|SNDRV_AUTO_DMA
)paren
(brace
r_if
c_cond
(paren
(paren
id|xdma1
op_assign
id|snd_legacy_find_free_dma
c_func
(paren
id|possible_dmas
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
l_string|&quot;unable to find a free DMA1&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|xdma2
op_assign
id|dma2
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xdma2
op_eq
id|SNDRV_AUTO_DMA
)paren
(brace
r_if
c_cond
(paren
(paren
id|xdma2
op_assign
id|snd_legacy_find_free_dma
c_func
(paren
id|possible_dmas
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|snd_printk
c_func
(paren
l_string|&quot;unable to find a free DMA2&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gus_create
c_func
(paren
id|card
comma
id|port
(braket
id|dev
)braket
comma
op_minus
id|xirq
comma
id|xdma1
comma
id|xdma2
comma
l_int|0
comma
id|channels
(braket
id|dev
)braket
comma
id|pcm_channels
(braket
id|dev
)braket
comma
l_int|0
comma
op_amp
id|gus
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gusmax_detect
c_func
(paren
id|gus
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|maxcard-&gt;gus_status_reg
op_assign
id|gus-&gt;gf1.reg_irqstat
suffix:semicolon
id|maxcard-&gt;pcm_status_reg
op_assign
id|gus-&gt;gf1.port
op_plus
l_int|0x10c
op_plus
l_int|2
suffix:semicolon
id|snd_gusmax_init
c_func
(paren
id|dev
comma
id|card
comma
id|gus
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gus_initialize
c_func
(paren
id|gus
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|gus-&gt;max_flag
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;GUS MAX soundcard was not detected at 0x%lx&bslash;n&quot;
comma
id|gus-&gt;gf1.port
)paren
suffix:semicolon
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|xirq
comma
id|snd_gusmax_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;GUS MAX&quot;
comma
(paren
r_void
op_star
)paren
id|maxcard
)paren
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;gusmax: unable to grab IRQ %d&bslash;n&quot;
comma
id|xirq
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|maxcard-&gt;irq
op_assign
id|xirq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs4231_create
c_func
(paren
id|card
comma
id|gus-&gt;gf1.port
op_plus
l_int|0x10c
comma
op_minus
l_int|1
comma
id|xirq
comma
id|xdma2
OL
l_int|0
ques
c_cond
id|xdma1
suffix:colon
id|xdma2
comma
id|xdma1
comma
id|CS4231_HW_DETECT
comma
id|CS4231_HWSHARE_IRQ
op_or
id|CS4231_HWSHARE_DMA1
op_or
id|CS4231_HWSHARE_DMA2
comma
op_amp
id|cs4231
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs4231_pcm
c_func
(paren
id|cs4231
comma
l_int|0
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs4231_mixer
c_func
(paren
id|cs4231
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs4231_timer
c_func
(paren
id|cs4231
comma
l_int|2
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pcm_channels
(braket
id|dev
)braket
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gf1_pcm_new
c_func
(paren
id|gus
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gusmax_mixer
c_func
(paren
id|cs4231
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gf1_rawmidi_new
c_func
(paren
id|gus
comma
l_int|0
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|card-&gt;longname
op_plus
id|strlen
c_func
(paren
id|card-&gt;longname
)paren
comma
l_string|&quot; at 0x%lx, irq %i, dma %i&quot;
comma
id|gus-&gt;gf1.port
comma
id|xirq
comma
id|xdma1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xdma2
op_ge
l_int|0
)paren
id|sprintf
c_func
(paren
id|card-&gt;longname
op_plus
id|strlen
c_func
(paren
id|card-&gt;longname
)paren
comma
l_string|&quot;&amp;%i&quot;
comma
id|xdma2
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_card_register
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|maxcard-&gt;gus
op_assign
id|gus
suffix:semicolon
id|maxcard-&gt;cs4231
op_assign
id|cs4231
suffix:semicolon
id|snd_gusmax_cards
(braket
id|dev
)braket
op_assign
id|card
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gusmax_legacy_auto_probe
r_static
r_int
id|__init
id|snd_gusmax_legacy_auto_probe
c_func
(paren
r_int
r_int
id|xport
)paren
(brace
r_static
r_int
id|dev
suffix:semicolon
r_int
id|res
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|dev
OL
id|SNDRV_CARDS
suffix:semicolon
id|dev
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|enable
(braket
id|dev
)braket
op_logical_or
id|port
(braket
id|dev
)braket
op_ne
id|SNDRV_AUTO_PORT
)paren
r_continue
suffix:semicolon
id|port
(braket
id|dev
)braket
op_assign
id|xport
suffix:semicolon
id|res
op_assign
id|snd_gusmax_probe
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
OL
l_int|0
)paren
id|port
(braket
id|dev
)braket
op_assign
id|SNDRV_AUTO_PORT
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|alsa_card_gusmax_init
r_static
r_int
id|__init
id|alsa_card_gusmax_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
r_int
id|possible_ports
(braket
)braket
op_assign
(brace
l_int|0x220
comma
l_int|0x230
comma
l_int|0x240
comma
l_int|0x250
comma
l_int|0x260
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_int
id|dev
comma
id|cards
comma
id|i
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|cards
op_assign
l_int|0
suffix:semicolon
id|dev
template_param
l_int|0
suffix:semicolon
id|dev
op_increment
)paren
(brace
r_if
c_cond
(paren
id|port
(braket
id|dev
)braket
op_eq
id|SNDRV_AUTO_PORT
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|snd_gusmax_probe
c_func
(paren
id|dev
)paren
op_ge
l_int|0
)paren
id|cards
op_increment
suffix:semicolon
)brace
id|i
op_assign
id|snd_legacy_auto_probe
c_func
(paren
id|possible_ports
comma
id|snd_gusmax_legacy_auto_probe
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
id|cards
op_add_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cards
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;GUS MAX soundcard not found or device busy&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_card_gusmax_exit
r_static
r_void
id|__exit
id|alsa_card_gusmax_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|idx
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_CARDS
suffix:semicolon
id|idx
op_increment
)paren
id|snd_card_free
c_func
(paren
id|snd_gusmax_cards
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_gusmax_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_gusmax_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-gusmax=enable,index,id,&n;&t;&t;&t; port,irq,&n;&t;&t;&t; dma1,dma2,&n;&t;&t;&t; joystick_dac,&n;&t;&t;&t; channels,pcm_channels */
DECL|function|alsa_card_gusmax_setup
r_static
r_int
id|__init
id|alsa_card_gusmax_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_static
r_int
id|__initdata
id|nr_dev
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nr_dev
op_ge
id|SNDRV_CARDS
)paren
r_return
l_int|0
suffix:semicolon
(paren
r_void
)paren
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|enable
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|index
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_id
c_func
(paren
op_amp
id|str
comma
op_amp
id|id
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option_long
c_func
(paren
op_amp
id|str
comma
op_amp
id|port
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|irq
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|dma1
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|dma2
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|joystick_dac
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|channels
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
op_logical_and
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|pcm_channels
(braket
id|nr_dev
)braket
)paren
op_eq
l_int|2
)paren
suffix:semicolon
id|nr_dev
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;snd-gusmax=&quot;
comma
id|alsa_card_gusmax_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
