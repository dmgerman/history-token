multiline_comment|/*&n; *  Driver for SoundBlaster 1.0/2.0/Pro soundcards and compatible&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/sb.h&gt;
macro_line|#include &lt;sound/opl3.h&gt;
DECL|macro|SNDRV_LEGACY_AUTO_PROBE
mdefine_line|#define SNDRV_LEGACY_AUTO_PROBE
DECL|macro|SNDRV_GET_ID
mdefine_line|#define SNDRV_GET_ID
macro_line|#include &lt;sound/initval.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t sb_t
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Sound Blaster 1.0/2.0/Pro&quot;
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
l_string|&quot;{{Creative Labs,SB 1.0/SB 2.0/SB Pro}}&quot;
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
multiline_comment|/* 1,3 */
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
l_string|&quot;Index value for Sound Blaster soundcard.&quot;
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
l_string|&quot;ID string for Sound Blaster soundcard.&quot;
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
l_string|&quot;Enable Sound Blaster soundcard.&quot;
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
l_string|&quot;Port # for SB8 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|port
comma
id|SNDRV_PORT12_DESC
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
l_string|&quot;IRQ # for SB8 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|irq
comma
id|SNDRV_IRQ_DESC
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
l_string|&quot;8-bit DMA # for SB8 driver.&quot;
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
DECL|struct|snd_sb8
r_struct
id|snd_sb8
(brace
DECL|member|fm_res
r_struct
id|resource
op_star
id|fm_res
suffix:semicolon
multiline_comment|/* used to block FM i/o region for legacy cards */
)brace
suffix:semicolon
DECL|variable|snd_sb8_cards
r_static
id|snd_card_t
op_star
id|snd_sb8_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|function|snd_sb8_interrupt
r_static
id|irqreturn_t
id|snd_sb8_interrupt
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
id|sb_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|sb_t
comma
id|dev_id
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;open
op_amp
id|SB_OPEN_PCM
)paren
(brace
id|snd_sb8dsp_interrupt
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_sb8dsp_midi_interrupt
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|snd_sb8_free
r_static
r_void
id|snd_sb8_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_struct
id|snd_sb8
op_star
id|acard
op_assign
(paren
r_struct
id|snd_sb8
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|acard
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|acard-&gt;fm_res
)paren
(brace
id|release_resource
c_func
(paren
id|acard-&gt;fm_res
)paren
suffix:semicolon
id|kfree_nocheck
c_func
(paren
id|acard-&gt;fm_res
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_sb8_probe
r_static
r_int
id|__init
id|snd_sb8_probe
c_func
(paren
r_int
id|dev
)paren
(brace
id|sb_t
op_star
id|chip
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_sb8
op_star
id|acard
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
r_sizeof
(paren
r_struct
id|snd_sb8
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
id|acard
op_assign
(paren
r_struct
id|snd_sb8
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|card-&gt;private_free
op_assign
id|snd_sb8_free
suffix:semicolon
multiline_comment|/* block the 0x388 port to avoid PnP conflicts */
id|acard-&gt;fm_res
op_assign
id|request_region
c_func
(paren
l_int|0x388
comma
l_int|4
comma
l_string|&quot;SoundBlaster FM&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_sbdsp_create
c_func
(paren
id|card
comma
id|port
(braket
id|dev
)braket
comma
id|irq
(braket
id|dev
)braket
comma
id|snd_sb8_interrupt
comma
id|dma8
(braket
id|dev
)braket
comma
op_minus
l_int|1
comma
id|SB_HW_AUTO
comma
op_amp
id|chip
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
id|chip-&gt;hardware
op_ge
id|SB_HW_16
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;hardware
op_eq
id|SB_HW_ALS100
)paren
id|snd_printdd
c_func
(paren
l_string|&quot;ALS100 chip detected at 0x%lx, try snd-als100 module&bslash;n&quot;
comma
id|port
(braket
id|dev
)braket
)paren
suffix:semicolon
r_else
id|snd_printdd
c_func
(paren
l_string|&quot;SB 16 chip detected at 0x%lx, try snd-sb16 module&bslash;n&quot;
comma
id|port
(braket
id|dev
)braket
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
(paren
id|err
op_assign
id|snd_sb8dsp_pcm
c_func
(paren
id|chip
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
id|snd_sbmixer_new
c_func
(paren
id|chip
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
id|chip-&gt;hardware
op_eq
id|SB_HW_10
op_logical_or
id|chip-&gt;hardware
op_eq
id|SB_HW_20
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_opl3_create
c_func
(paren
id|card
comma
id|chip-&gt;port
op_plus
l_int|8
comma
l_int|0
comma
id|OPL3_HW_AUTO
comma
l_int|1
comma
op_amp
id|opl3
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sb8: no OPL device at 0x%lx&bslash;n&quot;
comma
id|chip-&gt;port
op_plus
l_int|8
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_opl3_create
c_func
(paren
id|card
comma
id|chip-&gt;port
comma
id|chip-&gt;port
op_plus
l_int|2
comma
id|OPL3_HW_AUTO
comma
l_int|1
comma
op_amp
id|opl3
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sb8: no OPL device at 0x%lx-0x%lx&bslash;n&quot;
comma
id|chip-&gt;port
comma
id|chip-&gt;port
op_plus
l_int|2
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
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
id|snd_sb8dsp_midi
c_func
(paren
id|chip
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
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
id|chip-&gt;hardware
op_eq
id|SB_HW_PRO
ques
c_cond
l_string|&quot;SB Pro&quot;
suffix:colon
l_string|&quot;SB8&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
id|chip-&gt;name
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%lx, irq %d, dma %d&quot;
comma
id|chip-&gt;name
comma
id|chip-&gt;port
comma
id|irq
(braket
id|dev
)braket
comma
id|dma8
(braket
id|dev
)braket
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
id|snd_sb8_cards
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
DECL|function|snd_card_sb8_legacy_auto_probe
r_static
r_int
id|__init
id|snd_card_sb8_legacy_auto_probe
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
id|snd_sb8_probe
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
DECL|function|alsa_card_sb8_init
r_static
r_int
id|__init
id|alsa_card_sb8_init
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
OL
id|SNDRV_CARDS
op_logical_and
id|enable
(braket
id|dev
)braket
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
id|snd_sb8_probe
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
id|cards
op_add_assign
id|snd_legacy_auto_probe
c_func
(paren
id|possible_ports
comma
id|snd_card_sb8_legacy_auto_probe
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cards
)paren
(brace
macro_line|#ifdef MODULE
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Sound Blaster soundcard not found or device busy&bslash;n&quot;
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
DECL|function|alsa_card_sb8_exit
r_static
r_void
id|__exit
id|alsa_card_sb8_exit
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
id|snd_sb8_cards
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_sb8_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_sb8_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-sb8=enable,index,id,&n;&t;&t;      port,irq,dma8 */
DECL|function|alsa_card_sb8_setup
r_static
r_int
id|__init
id|alsa_card_sb8_setup
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
id|get_option
c_func
(paren
op_amp
id|str
comma
(paren
r_int
op_star
)paren
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
id|dma8
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
l_string|&quot;snd-sb8=&quot;
comma
id|alsa_card_sb8_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
