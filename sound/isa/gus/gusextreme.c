multiline_comment|/*&n; *  Driver for Gravis UltraSound Extreme soundcards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/gus.h&gt;
macro_line|#include &lt;sound/es1688.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/opl3.h&gt;
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
l_string|&quot;Gravis UltraSound Extreme&quot;
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
l_string|&quot;{{Gravis,UltraSound Extreme}}&quot;
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
multiline_comment|/* 0x220,0x240,0x260 */
DECL|variable|gf1_port
r_static
r_int
id|gf1_port
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
)paren
op_minus
l_int|1
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* 0x210,0x220,0x230,0x240,0x250,0x260,0x270 */
DECL|variable|mpu_port
r_static
r_int
id|mpu_port
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
)paren
op_minus
l_int|1
)braket
op_assign
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* 0x300,0x310,0x320 */
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
multiline_comment|/* 5,7,9,10 */
DECL|variable|mpu_irq
r_static
r_int
id|mpu_irq
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IRQ
suffix:semicolon
multiline_comment|/* 5,7,9,10 */
DECL|variable|gf1_irq
r_static
r_int
id|gf1_irq
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IRQ
suffix:semicolon
multiline_comment|/* 2,3,5,9,11,12,15 */
DECL|variable|dma8
r_static
r_int
id|dma8
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_DMA
suffix:semicolon
multiline_comment|/* 0,1,3 */
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
l_string|&quot;Index value for GUS Extreme soundcard.&quot;
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
l_string|&quot;ID string for GUS Extreme soundcard.&quot;
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
l_string|&quot;Enable GUS Extreme soundcard.&quot;
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
l_string|&quot;Port # for GUS Extreme driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|port
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{0x220,0x260,0x20}},dialog:list&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|gf1_port
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
id|gf1_port
comma
l_string|&quot;GF1 port # for GUS Extreme driver (optional).&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|gf1_port
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{0x210,0x270,0x10}},dialog:list&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mpu_port
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
id|mpu_port
comma
l_string|&quot;MPU-401 port # for GUS Extreme driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|mpu_port
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{0x300,0x320,0x10}},dialog:list&quot;
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
l_string|&quot;IRQ # for GUS Extreme driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|irq
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{5},{7},{9},{10}},dialog:list&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mpu_irq
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
id|mpu_irq
comma
l_string|&quot;MPU-401 IRQ # for GUS Extreme driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|mpu_irq
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{5},{7},{9},{10}},dialog:list&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|gf1_irq
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
id|gf1_irq
comma
l_string|&quot;GF1 IRQ # for GUS Extreme driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|gf1_irq
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{2},{3},{5},{9},{11},{12},{15}},dialog:list&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma8
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
id|dma8
comma
l_string|&quot;8-bit DMA # for GUS Extreme driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|dma8
comma
id|SNDRV_DMA8_DESC
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
l_string|&quot;GF1 DMA # for GUS Extreme driver.&quot;
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
l_string|&quot;Joystick DAC level 0.59V-4.52V or 0.389V-2.98V for GUS Extreme driver.&quot;
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
l_string|&quot;GF1 channels for GUS Extreme driver.&quot;
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
l_string|&quot;Reserved PCM channels for GUS Extreme driver.&quot;
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
DECL|variable|snd_gusextreme_cards
r_static
id|snd_card_t
op_star
id|snd_gusextreme_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|function|snd_gusextreme_detect
r_static
r_int
id|__init
id|snd_gusextreme_detect
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
comma
id|es1688_t
op_star
id|es1688
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * This is main stuff - enable access to GF1 chip...&n;&t; * I&squot;m not sure, if this will work for card which have&n;&t; * ES1688 chip in another place than 0x220.&n;         *&n;         * I used reverse-engineering in DOSEMU. [--jk]&n;&t; *&n;&t; * ULTRINIT.EXE:&n;&t; * 0x230 = 0,2,3&n;&t; * 0x240 = 2,0,1&n;&t; * 0x250 = 2,0,3&n;&t; * 0x260 = 2,2,1&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|es1688-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
id|snd_es1688_mixer_write
c_func
(paren
id|es1688
comma
l_int|0x40
comma
l_int|0x0b
)paren
suffix:semicolon
multiline_comment|/* don&squot;t change!!! */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|es1688-&gt;mixer_lock
comma
id|flags
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|es1688-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
id|gf1_port
(braket
id|dev
)braket
op_amp
l_int|0x040
ques
c_cond
l_int|2
suffix:colon
l_int|0
comma
id|ES1688P
c_func
(paren
id|es1688
comma
id|INIT1
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
l_int|0x201
)paren
suffix:semicolon
id|outb
c_func
(paren
id|gf1_port
(braket
id|dev
)braket
op_amp
l_int|0x020
ques
c_cond
l_int|2
suffix:colon
l_int|0
comma
id|ES1688P
c_func
(paren
id|es1688
comma
id|INIT1
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
l_int|0x201
)paren
suffix:semicolon
id|outb
c_func
(paren
id|gf1_port
(braket
id|dev
)braket
op_amp
l_int|0x010
ques
c_cond
l_int|3
suffix:colon
l_int|1
comma
id|ES1688P
c_func
(paren
id|es1688
comma
id|INIT1
)paren
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|es1688-&gt;reg_lock
comma
id|flags
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
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
id|EIO
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
id|EIO
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
id|EIO
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
id|EIO
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gusextreme_init
r_static
r_void
id|__init
id|snd_gusextreme_init
c_func
(paren
r_int
id|dev
comma
id|snd_gus_card_t
op_star
id|gus
)paren
(brace
id|gus-&gt;joystick_dac
op_assign
id|joystick_dac
(braket
id|dev
)braket
suffix:semicolon
)brace
DECL|function|snd_gusextreme_mixer
r_static
r_int
id|__init
id|snd_gusextreme_mixer
c_func
(paren
id|es1688_t
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
multiline_comment|/* reassign AUX to SYNTHESIZER */
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
multiline_comment|/* reassign Master Playback Switch to Synth Playback Switch */
id|strcpy
c_func
(paren
id|id1.name
comma
l_string|&quot;Master Playback Switch&quot;
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_gusextreme_probe
r_static
r_int
id|__init
id|snd_gusextreme_probe
c_func
(paren
r_int
id|dev
)paren
(brace
r_static
r_int
id|possible_ess_irqs
(braket
)braket
op_assign
(brace
l_int|5
comma
l_int|9
comma
l_int|10
comma
l_int|7
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_int
id|possible_ess_dmas
(braket
)braket
op_assign
(brace
l_int|1
comma
l_int|3
comma
l_int|0
comma
op_minus
l_int|1
)brace
suffix:semicolon
r_static
r_int
id|possible_gf1_irqs
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
id|possible_gf1_dmas
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
id|xgf1_irq
comma
id|xgf1_dma
comma
id|xess_irq
comma
id|xmpu_irq
comma
id|xess_dma
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_gusextreme
op_star
id|acard
suffix:semicolon
id|snd_gus_card_t
op_star
id|gus
suffix:semicolon
id|es1688_t
op_star
id|es1688
suffix:semicolon
id|opl3_t
op_star
id|opl3
suffix:semicolon
r_int
id|err
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
l_int|0
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
id|acard
op_assign
(paren
r_struct
id|snd_gusextreme
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|xgf1_irq
op_assign
id|gf1_irq
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xgf1_irq
op_eq
id|SNDRV_AUTO_IRQ
)paren
(brace
r_if
c_cond
(paren
(paren
id|xgf1_irq
op_assign
id|snd_legacy_find_free_irq
c_func
(paren
id|possible_gf1_irqs
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;unable to find a free IRQ for GF1&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|xess_irq
op_assign
id|irq
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xess_irq
op_eq
id|SNDRV_AUTO_IRQ
)paren
(brace
r_if
c_cond
(paren
(paren
id|xess_irq
op_assign
id|snd_legacy_find_free_irq
c_func
(paren
id|possible_ess_irqs
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;unable to find a free IRQ for ES1688&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|mpu_port
(braket
id|dev
)braket
op_eq
id|SNDRV_AUTO_PORT
)paren
id|mpu_port
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
id|xmpu_irq
op_assign
id|mpu_irq
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xmpu_irq
OG
l_int|15
)paren
id|xmpu_irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|xgf1_dma
op_assign
id|dma1
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xgf1_dma
op_eq
id|SNDRV_AUTO_DMA
)paren
(brace
r_if
c_cond
(paren
(paren
id|xgf1_dma
op_assign
id|snd_legacy_find_free_dma
c_func
(paren
id|possible_gf1_dmas
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;unable to find a free DMA for GF1&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|xess_dma
op_assign
id|dma8
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|xess_dma
op_eq
id|SNDRV_AUTO_DMA
)paren
(brace
r_if
c_cond
(paren
(paren
id|xess_dma
op_assign
id|snd_legacy_find_free_dma
c_func
(paren
id|possible_ess_dmas
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;unable to find a free DMA for ES1688&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_es1688_create
c_func
(paren
id|card
comma
id|port
(braket
id|dev
)braket
comma
id|mpu_port
(braket
id|dev
)braket
comma
id|xess_irq
comma
id|xmpu_irq
comma
id|xess_dma
comma
id|ES1688_HW_1688
comma
op_amp
id|es1688
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|gf1_port
(braket
id|dev
)braket
OL
l_int|0
)paren
id|gf1_port
(braket
id|dev
)braket
op_assign
id|port
(braket
id|dev
)braket
op_plus
l_int|0x20
suffix:semicolon
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
id|gf1_port
(braket
id|dev
)braket
comma
id|xgf1_irq
comma
id|xgf1_dma
comma
op_minus
l_int|1
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
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gusextreme_detect
c_func
(paren
id|dev
comma
id|card
comma
id|gus
comma
id|es1688
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|snd_gusextreme_init
c_func
(paren
id|dev
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
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gus-&gt;ess_flag
)paren
(brace
id|snd_printdd
c_func
(paren
l_string|&quot;GUS Extreme soundcard was not detected at 0x%lx&bslash;n&quot;
comma
id|gus-&gt;gf1.port
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_es1688_pcm
c_func
(paren
id|es1688
comma
l_int|0
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_es1688_mixer
c_func
(paren
id|es1688
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|snd_component_add
c_func
(paren
id|card
comma
l_string|&quot;ES1688&quot;
)paren
suffix:semicolon
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
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gf1_new_mixer
c_func
(paren
id|gus
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_gusextreme_mixer
c_func
(paren
id|es1688
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|snd_opl3_create
c_func
(paren
id|card
comma
id|es1688-&gt;port
comma
id|es1688-&gt;port
op_plus
l_int|2
comma
id|OPL3_HW_OPL3
comma
l_int|0
comma
op_amp
id|opl3
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;gusextreme: opl3 not detected at 0x%lx&bslash;n&quot;
comma
id|es1688-&gt;port
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_opl3_hwdep_new
c_func
(paren
id|opl3
comma
l_int|0
comma
l_int|2
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|es1688-&gt;mpu_port
op_ge
l_int|0x300
op_logical_and
(paren
id|err
op_assign
id|snd_mpu401_uart_new
c_func
(paren
id|card
comma
l_int|0
comma
id|MPU401_HW_ES1688
comma
id|es1688-&gt;mpu_port
comma
l_int|0
comma
id|xmpu_irq
comma
id|SA_INTERRUPT
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;Gravis UltraSound Extreme at 0x%lx, irq %i&amp;%i, dma %i&amp;%i&quot;
comma
id|es1688-&gt;port
comma
id|xgf1_irq
comma
id|xess_irq
comma
id|xgf1_dma
comma
id|xess_dma
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
r_goto
id|out
suffix:semicolon
id|snd_gusextreme_cards
(braket
id|dev
)braket
op_assign
id|card
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
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
DECL|function|snd_gusextreme_legacy_auto_probe
r_static
r_int
id|__init
id|snd_gusextreme_legacy_auto_probe
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
id|snd_gusextreme_probe
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
DECL|function|alsa_card_gusextreme_init
r_static
r_int
id|__init
id|alsa_card_gusextreme_init
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
l_int|0x240
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
id|snd_gusextreme_probe
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
id|snd_gusextreme_legacy_auto_probe
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
l_string|&quot;GUS Extreme soundcard not found or device busy&bslash;n&quot;
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
DECL|function|alsa_card_gusextreme_exit
r_static
r_void
id|__exit
id|alsa_card_gusextreme_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|idx
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_gusextreme
op_star
id|acard
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
(brace
id|card
op_assign
id|snd_gusextreme_cards
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|acard
op_assign
(paren
r_struct
id|snd_gusextreme
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|snd_card_free
c_func
(paren
id|snd_gusextreme_cards
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
)brace
id|module_init
c_func
(paren
id|alsa_card_gusextreme_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_gusextreme_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-gusextreme=enable,index,id,&n;&t;&t;&t;     port,gf1_port,mpu_port,&n;&t;&t;&t;     irq,gf1_irq,mpu_irq,&n;&t;&t;&t;     dma8,dma1,&n;&t;&t;&t;     joystick_dac,&n;&t;&t;&t;     channels,pcm_channels */
DECL|function|alsa_card_gusextreme_setup
r_static
r_int
id|__init
id|alsa_card_gusextreme_setup
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
id|get_option_long
c_func
(paren
op_amp
id|str
comma
op_amp
id|gf1_port
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
id|mpu_port
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
id|gf1_irq
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
id|mpu_irq
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
id|dma8
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
l_string|&quot;snd-gusextreme=&quot;
comma
id|alsa_card_gusextreme_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
