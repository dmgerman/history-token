multiline_comment|/*&n; *  Generic driver for CS4231 chips&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *  Originally the CS4232/CS4232A driver, modified for use on CS4231 by&n; *  Tugrul Galatali &lt;galatalt@stuy.edu&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/cs4231.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
DECL|macro|SNDRV_GET_ID
mdefine_line|#define SNDRV_GET_ID
macro_line|#include &lt;sound/initval.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t cs4231_t
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Generic CS4231&quot;
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
l_string|&quot;{{Crystal Semiconductors,CS4231}}&quot;
)paren
suffix:semicolon
DECL|variable|snd_index
r_static
r_int
id|snd_index
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IDX
suffix:semicolon
multiline_comment|/* Index 0-MAX */
DECL|variable|snd_id
r_static
r_char
op_star
id|snd_id
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_STR
suffix:semicolon
multiline_comment|/* ID for this card */
DECL|variable|snd_enable
r_static
r_int
id|snd_enable
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_ENABLE
suffix:semicolon
multiline_comment|/* Enable this card */
DECL|variable|snd_port
r_static
r_int
id|snd_port
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PORT
suffix:semicolon
multiline_comment|/* PnP setup */
DECL|variable|snd_mpu_port
r_static
r_int
id|snd_mpu_port
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PORT
suffix:semicolon
multiline_comment|/* PnP setup */
DECL|variable|snd_irq
r_static
r_int
id|snd_irq
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IRQ
suffix:semicolon
multiline_comment|/* 5,7,9,11,12,15 */
DECL|variable|snd_mpu_irq
r_static
r_int
id|snd_mpu_irq
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_IRQ
suffix:semicolon
multiline_comment|/* 9,11,12,15 */
DECL|variable|snd_dma1
r_static
r_int
id|snd_dma1
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_DMA
suffix:semicolon
multiline_comment|/* 0,1,3,5,6,7 */
DECL|variable|snd_dma2
r_static
r_int
id|snd_dma2
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_DMA
suffix:semicolon
multiline_comment|/* 0,1,3,5,6,7 */
id|MODULE_PARM
c_func
(paren
id|snd_index
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
id|snd_index
comma
l_string|&quot;Index value for CS4231 soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_index
comma
id|SNDRV_INDEX_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_id
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
id|snd_id
comma
l_string|&quot;ID string for CS4231 soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_id
comma
id|SNDRV_ID_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_enable
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
id|snd_enable
comma
l_string|&quot;Enable CS4231 soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_enable
comma
id|SNDRV_ENABLE_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_port
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
id|snd_port
comma
l_string|&quot;Port # for CS4231 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_port
comma
id|SNDRV_PORT12_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_mpu_port
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
id|snd_mpu_port
comma
l_string|&quot;MPU-401 port # for CS4231 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_mpu_port
comma
id|SNDRV_PORT12_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_irq
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
id|snd_irq
comma
l_string|&quot;IRQ # for CS4231 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_irq
comma
id|SNDRV_IRQ_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_mpu_irq
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
id|snd_mpu_irq
comma
l_string|&quot;MPU-401 IRQ # for CS4231 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_mpu_irq
comma
id|SNDRV_IRQ_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_dma1
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
id|snd_dma1
comma
l_string|&quot;DMA1 # for CS4231 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_dma1
comma
id|SNDRV_DMA_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_dma2
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
id|snd_dma2
comma
l_string|&quot;DMA2 # for CS4231 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_dma2
comma
id|SNDRV_DMA_DESC
)paren
suffix:semicolon
DECL|variable|snd_cs4231_cards
r_static
id|snd_card_t
op_star
id|snd_cs4231_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|function|snd_card_cs4231_probe
r_static
r_int
id|__init
id|snd_card_cs4231_probe
c_func
(paren
r_int
id|dev
)paren
(brace
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_card_cs4231
op_star
id|acard
suffix:semicolon
id|snd_pcm_t
op_star
id|pcm
op_assign
l_int|NULL
suffix:semicolon
id|cs4231_t
op_star
id|chip
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|snd_port
(braket
id|dev
)braket
op_eq
id|SNDRV_AUTO_PORT
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;specify snd_port&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|snd_irq
(braket
id|dev
)braket
op_eq
id|SNDRV_AUTO_IRQ
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;specify snd_irq&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|snd_dma1
(braket
id|dev
)braket
op_eq
id|SNDRV_AUTO_DMA
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;specify snd_dma1&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|card
op_assign
id|snd_card_new
c_func
(paren
id|snd_index
(braket
id|dev
)braket
comma
id|snd_id
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
id|snd_card_cs4231
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|snd_mpu_port
(braket
id|dev
)braket
OL
l_int|0
)paren
id|snd_mpu_port
(braket
id|dev
)braket
op_assign
id|SNDRV_AUTO_PORT
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
id|snd_port
(braket
id|dev
)braket
comma
op_minus
l_int|1
comma
id|snd_irq
(braket
id|dev
)braket
comma
id|snd_dma1
(braket
id|dev
)braket
comma
id|snd_dma2
(braket
id|dev
)braket
comma
id|CS4231_HW_DETECT
comma
l_int|0
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
(paren
id|err
op_assign
id|snd_cs4231_pcm
c_func
(paren
id|chip
comma
l_int|0
comma
op_amp
id|pcm
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
(paren
id|err
op_assign
id|snd_cs4231_timer
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
id|snd_mpu_irq
(braket
id|dev
)braket
op_ge
l_int|0
op_logical_and
id|snd_mpu_irq
(braket
id|dev
)braket
op_ne
id|SNDRV_AUTO_IRQ
)paren
(brace
r_if
c_cond
(paren
id|snd_mpu401_uart_new
c_func
(paren
id|card
comma
l_int|0
comma
id|MPU401_HW_CS4232
comma
id|snd_mpu_port
(braket
id|dev
)braket
comma
l_int|0
comma
id|snd_mpu_irq
(braket
id|dev
)braket
comma
id|SA_INTERRUPT
comma
l_int|NULL
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs4231: MPU401 not detected&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;CS4231&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
id|pcm-&gt;name
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%lx, irq %d, dma %d&quot;
comma
id|pcm-&gt;name
comma
id|chip-&gt;port
comma
id|snd_irq
(braket
id|dev
)braket
comma
id|snd_dma1
(braket
id|dev
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_dma2
(braket
id|dev
)braket
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
l_string|&quot;&amp;%d&quot;
comma
id|snd_dma2
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
id|snd_cs4231_cards
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
DECL|function|alsa_card_cs4231_init
r_static
r_int
id|__init
id|alsa_card_cs4231_init
c_func
(paren
r_void
)paren
(brace
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
id|snd_enable
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
id|snd_card_cs4231_probe
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
l_string|&quot;CS4231 soundcard not found or device busy&bslash;n&quot;
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
DECL|function|alsa_card_cs4231_exit
r_static
r_void
id|__exit
id|alsa_card_cs4231_exit
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
id|snd_cs4231_cards
(braket
id|idx
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_cs4231_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_cs4231_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-cs4231=snd_enable,snd_index,snd_id,&n;&t;&t;&t; snd_port,snd_mpu_port,snd_irq,snd_mpu_irq,&n;&t;&t;&t; snd_dma1,snd_dma2 */
DECL|function|alsa_card_cs4231_setup
r_static
r_int
id|__init
id|alsa_card_cs4231_setup
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
r_int
id|__attribute__
(paren
(paren
id|__unused__
)paren
)paren
id|pnp
op_assign
id|INT_MAX
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
id|snd_enable
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
id|snd_index
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
id|snd_id
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
id|pnp
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
id|snd_port
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
id|snd_mpu_port
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
id|snd_irq
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
id|snd_mpu_irq
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
id|snd_dma1
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
id|snd_dma2
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
l_string|&quot;snd-cs4231=&quot;
comma
id|alsa_card_cs4231_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
