multiline_comment|/*&n;    card-es968.c - driver for ESS AudioDrive ES968 based soundcards.&n;    Copyright (C) 1999 by Massimo Piccioni &lt;dafastidio@libero.it&gt;&n;&n;    Thanks to Pierfrancesco &squot;qM2&squot; Passerini.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;*/
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#ifndef LINUX_ISAPNP_H
macro_line|#include &lt;linux/isapnp.h&gt;
DECL|macro|isapnp_card
mdefine_line|#define isapnp_card pci_bus
DECL|macro|isapnp_dev
mdefine_line|#define isapnp_dev pci_dev
macro_line|#endif
macro_line|#include &lt;sound/core.h&gt;
DECL|macro|SNDRV_GET_ID
mdefine_line|#define SNDRV_GET_ID
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;sound/sb.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t sb_t
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Massimo Piccioni &lt;dafastidio@libero.it&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ESS AudioDrive ES968&quot;
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
l_string|&quot;{{ESS,AudioDrive ES968}}&quot;
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
id|SNDRV_DEFAULT_ENABLE_ISAPNP
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
multiline_comment|/* Pnp setup */
DECL|variable|snd_dma8
r_static
r_int
id|snd_dma8
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_DMA
suffix:semicolon
multiline_comment|/* PnP setup */
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
l_string|&quot;Index value for es968 based soundcard.&quot;
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
l_string|&quot;ID string for es968 based soundcard.&quot;
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
l_string|&quot;Enable es968 based soundcard.&quot;
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
l_string|&quot;Port # for es968 driver.&quot;
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
l_string|&quot;IRQ # for es968 driver.&quot;
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
id|snd_dma8
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
id|snd_dma8
comma
l_string|&quot;8-bit DMA # for es968 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_dma8
comma
id|SNDRV_DMA8_DESC
)paren
suffix:semicolon
DECL|struct|snd_card_es968
r_struct
id|snd_card_es968
(brace
macro_line|#ifdef __ISAPNP__
DECL|member|dev
r_struct
id|isapnp_dev
op_star
id|dev
suffix:semicolon
macro_line|#endif&t;/* __ISAPNP__ */
)brace
suffix:semicolon
DECL|variable|snd_es968_cards
r_static
id|snd_card_t
op_star
id|snd_es968_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
macro_line|#ifdef __ISAPNP__
DECL|variable|__devinitdata
r_static
r_struct
id|isapnp_card
op_star
id|snd_es968_isapnp_cards
(braket
id|SNDRV_CARDS
)braket
id|__devinitdata
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_const
r_struct
id|isapnp_card_id
op_star
id|snd_es968_isapnp_id
(braket
id|SNDRV_CARDS
)braket
id|__devinitdata
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|isapnp_card_id
id|snd_es968_pnpids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
id|ISAPNP_CARD_ID
c_func
(paren
l_char|&squot;E&squot;
comma
l_char|&squot;S&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x0968
)paren
comma
dot
id|devs
op_assign
(brace
id|ISAPNP_DEVICE_ID
c_func
(paren
l_char|&squot;E&squot;
comma
l_char|&squot;S&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x0968
)paren
comma
)brace
)brace
comma
(brace
id|ISAPNP_CARD_END
comma
)brace
)brace
suffix:semicolon
DECL|variable|snd_es968_pnpids
id|ISAPNP_CARD_TABLE
c_func
(paren
id|snd_es968_pnpids
)paren
suffix:semicolon
macro_line|#endif&t;/* __ISAPNP__ */
DECL|macro|DRIVER_NAME
mdefine_line|#define&t;DRIVER_NAME&t;&quot;snd-card-es968&quot;
DECL|function|snd_card_es968_interrupt
r_static
r_void
id|snd_card_es968_interrupt
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
)brace
macro_line|#ifdef __ISAPNP__
DECL|function|snd_card_es968_isapnp
r_static
r_int
id|__init
id|snd_card_es968_isapnp
c_func
(paren
r_int
id|dev
comma
r_struct
id|snd_card_es968
op_star
id|acard
)paren
(brace
r_const
r_struct
id|isapnp_card_id
op_star
id|id
op_assign
id|snd_es968_isapnp_id
(braket
id|dev
)braket
suffix:semicolon
r_struct
id|isapnp_card
op_star
id|card
op_assign
id|snd_es968_isapnp_cards
(braket
id|dev
)braket
suffix:semicolon
r_struct
id|isapnp_dev
op_star
id|pdev
suffix:semicolon
id|acard-&gt;dev
op_assign
id|isapnp_find_dev
c_func
(paren
id|card
comma
id|id-&gt;devs
(braket
l_int|0
)braket
dot
id|vendor
comma
id|id-&gt;devs
(braket
l_int|0
)braket
dot
id|function
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acard-&gt;dev-&gt;active
)paren
(brace
id|acard-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|pdev
op_assign
id|acard-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_member_access_from_pointer
id|prepare
c_func
(paren
id|pdev
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|snd_port
(braket
id|dev
)braket
op_ne
id|SNDRV_AUTO_PORT
)paren
id|isapnp_resource_change
c_func
(paren
op_amp
id|pdev-&gt;resource
(braket
l_int|0
)braket
comma
id|snd_port
(braket
id|dev
)braket
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_dma8
(braket
id|dev
)braket
op_ne
id|SNDRV_AUTO_DMA
)paren
id|isapnp_resource_change
c_func
(paren
op_amp
id|pdev-&gt;dma_resource
(braket
l_int|0
)braket
comma
id|snd_dma8
(braket
id|dev
)braket
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_irq
(braket
id|dev
)braket
op_ne
id|SNDRV_AUTO_IRQ
)paren
id|isapnp_resource_change
c_func
(paren
op_amp
id|pdev-&gt;irq_resource
(braket
l_int|0
)braket
comma
id|snd_irq
(braket
id|dev
)braket
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_member_access_from_pointer
id|activate
c_func
(paren
id|pdev
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;AUDIO isapnp configure failure&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|snd_port
(braket
id|dev
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|snd_dma8
(braket
id|dev
)braket
op_assign
id|pdev-&gt;dma_resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|snd_irq
(braket
id|dev
)braket
op_assign
id|pdev-&gt;irq_resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_es968_deactivate
r_static
r_void
id|snd_card_es968_deactivate
c_func
(paren
r_struct
id|snd_card_es968
op_star
id|acard
)paren
(brace
r_if
c_cond
(paren
id|acard-&gt;dev
)paren
(brace
id|acard-&gt;dev
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|acard-&gt;dev
)paren
suffix:semicolon
id|acard-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* __ISAPNP__ */
DECL|function|snd_card_es968_free
r_static
r_void
id|snd_card_es968_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_struct
id|snd_card_es968
op_star
id|acard
op_assign
(paren
r_struct
id|snd_card_es968
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|acard
)paren
(brace
macro_line|#ifdef __ISAPNP__
id|snd_card_es968_deactivate
c_func
(paren
id|acard
)paren
suffix:semicolon
macro_line|#endif&t;/* __ISAPNP__ */
)brace
)brace
DECL|function|snd_card_es968_probe
r_static
r_int
id|__init
id|snd_card_es968_probe
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
id|error
suffix:semicolon
id|sb_t
op_star
id|chip
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_card_es968
op_star
id|acard
suffix:semicolon
r_if
c_cond
(paren
(paren
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
r_sizeof
(paren
r_struct
id|snd_card_es968
)paren
)paren
)paren
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
id|snd_card_es968
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|card-&gt;private_free
op_assign
id|snd_card_es968_free
suffix:semicolon
macro_line|#ifdef __ISAPNP__
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_card_es968_isapnp
c_func
(paren
id|dev
comma
id|acard
)paren
)paren
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
macro_line|#else
id|snd_printk
c_func
(paren
l_string|&quot;you have to enable PnP support ...&bslash;n&quot;
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
id|ENOSYS
suffix:semicolon
macro_line|#endif&t;/* __ISAPNP__ */
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_sbdsp_create
c_func
(paren
id|card
comma
id|snd_port
(braket
id|dev
)braket
comma
id|snd_irq
(braket
id|dev
)braket
comma
id|snd_card_es968_interrupt
comma
id|snd_dma8
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
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
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
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
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
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
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
id|error
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;ES968&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;ESS ES968&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s soundcard, %s at 0x%lx, irq %d, dma %d&quot;
comma
id|card-&gt;shortname
comma
id|chip-&gt;name
comma
id|chip-&gt;port
comma
id|snd_irq
(braket
id|dev
)braket
comma
id|snd_dma8
(braket
id|dev
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
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
id|error
suffix:semicolon
)brace
id|snd_es968_cards
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
macro_line|#ifdef __ISAPNP__
DECL|function|snd_es968_isapnp_detect
r_static
r_int
id|__init
id|snd_es968_isapnp_detect
c_func
(paren
r_struct
id|isapnp_card
op_star
id|card
comma
r_const
r_struct
id|isapnp_card_id
op_star
id|id
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
id|snd_enable
(braket
id|dev
)braket
)paren
r_continue
suffix:semicolon
id|snd_es968_isapnp_cards
(braket
id|dev
)braket
op_assign
id|card
suffix:semicolon
id|snd_es968_isapnp_id
(braket
id|dev
)braket
op_assign
id|id
suffix:semicolon
id|res
op_assign
id|snd_card_es968_probe
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
r_return
id|res
suffix:semicolon
id|dev
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#endif /* __ISAPNP__ */
DECL|function|alsa_card_es968_init
r_static
r_int
id|__init
id|alsa_card_es968_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cards
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __ISAPNP__
id|cards
op_add_assign
id|isapnp_probe_cards
c_func
(paren
id|snd_es968_pnpids
comma
id|snd_es968_isapnp_detect
)paren
suffix:semicolon
macro_line|#else
id|snd_printk
c_func
(paren
l_string|&quot;you have to enable ISA PnP support.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MODULE
r_if
c_cond
(paren
op_logical_neg
id|cards
)paren
id|snd_printk
c_func
(paren
l_string|&quot;no ES968 based soundcards found&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|cards
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|alsa_card_es968_exit
r_static
r_void
id|__exit
id|alsa_card_es968_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|dev
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
l_int|0
suffix:semicolon
id|dev
OL
id|SNDRV_CARDS
suffix:semicolon
id|dev
op_increment
)paren
id|snd_card_free
c_func
(paren
id|snd_es968_cards
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_es968_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_es968_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-es968=snd_enable,snd_index,snd_id,&n;&t;&t;&t;snd_port,snd_irq,snd_dma1 */
DECL|function|alsa_card_es968_setup
r_static
r_int
id|__init
id|alsa_card_es968_setup
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
id|snd_dma8
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
l_string|&quot;snd-es968=&quot;
comma
id|alsa_card_es968_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
