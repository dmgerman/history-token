multiline_comment|/*&n;    card-ad1816a.c - driver for ADI SoundPort AD1816A based soundcards.&n;    Copyright (C) 2000 by Massimo Piccioni &lt;dafastidio@libero.it&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;*/
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
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
macro_line|#include &lt;sound/ad1816a.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/opl3.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t ad1816a_t
DECL|macro|PFX
mdefine_line|#define PFX &quot;ad1816a: &quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Massimo Piccioni &lt;dafastidio@libero.it&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AD1816A, AD1815&quot;
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
l_string|&quot;{{Highscreen,Sound-Boostar 16 3D},&quot;
l_string|&quot;{Analog Devices,AD1815},&quot;
l_string|&quot;{Analog Devices,AD1816A},&quot;
l_string|&quot;{TerraTec,Base 64},&quot;
l_string|&quot;{TerraTec,AudioSystem EWS64S},&quot;
l_string|&quot;{Aztech/Newcom SC-16 3D},&quot;
l_string|&quot;{Shark Predator ISA}}&quot;
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
multiline_comment|/* Index 1-MAX */
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
id|SNDRV_DEFAULT_ENABLE_ISAPNP
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
multiline_comment|/* PnP setup */
DECL|variable|mpu_port
r_static
r_int
id|mpu_port
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PORT
suffix:semicolon
multiline_comment|/* PnP setup */
DECL|variable|fm_port
r_static
r_int
id|fm_port
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PORT
suffix:semicolon
multiline_comment|/* PnP setup */
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
multiline_comment|/* Pnp setup */
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
multiline_comment|/* Pnp setup */
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
multiline_comment|/* PnP setup */
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
multiline_comment|/* PnP setup */
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
l_string|&quot;Index value for ad1816a based soundcard.&quot;
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
l_string|&quot;ID string for ad1816a based soundcard.&quot;
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
l_string|&quot;Enable ad1816a based soundcard.&quot;
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
l_string|&quot;Port # for ad1816a driver.&quot;
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
l_string|&quot;MPU-401 port # for ad1816a driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|mpu_port
comma
id|SNDRV_PORT12_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|fm_port
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
id|fm_port
comma
l_string|&quot;FM port # for ad1816a driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|fm_port
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
l_string|&quot;IRQ # for ad1816a driver.&quot;
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
l_string|&quot;MPU-401 IRQ # for ad1816a driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|mpu_irq
comma
id|SNDRV_IRQ_DESC
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
l_string|&quot;1st DMA # for ad1816a driver.&quot;
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
l_string|&quot;2nd DMA # for ad1816a driver.&quot;
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
DECL|struct|snd_card_ad1816a
r_struct
id|snd_card_ad1816a
(brace
macro_line|#ifdef __ISAPNP__
DECL|member|dev
r_struct
id|isapnp_dev
op_star
id|dev
suffix:semicolon
DECL|member|devmpu
r_struct
id|isapnp_dev
op_star
id|devmpu
suffix:semicolon
macro_line|#endif&t;/* __ISAPNP__ */
)brace
suffix:semicolon
DECL|variable|snd_ad1816a_cards
r_static
id|snd_card_t
op_star
id|snd_ad1816a_cards
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
id|snd_ad1816a_isapnp_cards
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
id|snd_ad1816a_isapnp_id
(braket
id|SNDRV_CARDS
)braket
id|__devinitdata
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|macro|ISAPNP_AD1816A
mdefine_line|#define ISAPNP_AD1816A(_va, _vb, _vc, _device, _fa, _fb, _fc, _audio, _mpu401) &bslash;&n;&t;{ &bslash;&n;&t;&t;ISAPNP_CARD_ID(_va, _vb, _vc, _device), &bslash;&n;&t;&t;.devs = { ISAPNP_DEVICE_ID(_fa, _fb, _fc, _audio), &bslash;&n;&t;&t;&t;  ISAPNP_DEVICE_ID(_fa, _fb, _fc, _mpu401), } &bslash;&n;&t;}
DECL|variable|__devinitdata
r_static
r_struct
id|isapnp_card_id
id|snd_ad1816a_pnpids
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/* Highscreen Sound-Boostar 16 3D */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;M&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;K&squot;
comma
l_int|0x1605
comma
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7180
comma
l_int|0x7181
)paren
comma
multiline_comment|/* Highscreen Sound-Boostar 16 3D - added by Stefan Behnel */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;L&squot;
comma
l_char|&squot;W&squot;
comma
l_char|&squot;C&squot;
comma
l_int|0x1061
comma
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7180
comma
l_int|0x7181
)paren
comma
multiline_comment|/* Analog Devices AD1815 */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7150
comma
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7150
comma
l_int|0x7151
)paren
comma
multiline_comment|/* Analog Devices AD1816A - added by Kenneth Platz &lt;kxp@atl.hp.com&gt; */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7181
comma
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7180
comma
l_int|0x7181
)paren
comma
multiline_comment|/* Analog Devices AD1816A - Terratec Base 64 */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;E&squot;
comma
l_char|&squot;R&squot;
comma
l_int|0x1411
comma
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7180
comma
l_int|0x7181
)paren
comma
multiline_comment|/* Analog Devices AD1816A - Terratec AudioSystem EWS64S */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;E&squot;
comma
l_char|&squot;R&squot;
comma
l_int|0x1112
comma
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7180
comma
l_int|0x7181
)paren
comma
multiline_comment|/* Analog Devices AD1816A - Aztech/Newcom SC-16 3D */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;A&squot;
comma
l_char|&squot;Z&squot;
comma
l_char|&squot;T&squot;
comma
l_int|0x1022
comma
l_char|&squot;A&squot;
comma
l_char|&squot;Z&squot;
comma
l_char|&squot;T&squot;
comma
l_int|0x1018
comma
l_int|0x2002
)paren
comma
multiline_comment|/* Shark Predator ISA - added by Ken Arromdee */
id|ISAPNP_AD1816A
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;M&squot;
comma
l_char|&squot;M&squot;
comma
l_int|0x7180
comma
l_char|&squot;A&squot;
comma
l_char|&squot;D&squot;
comma
l_char|&squot;S&squot;
comma
l_int|0x7180
comma
l_int|0x7181
)paren
comma
(brace
id|ISAPNP_CARD_END
comma
)brace
)brace
suffix:semicolon
DECL|variable|snd_ad1816a_pnpids
id|ISAPNP_CARD_TABLE
c_func
(paren
id|snd_ad1816a_pnpids
)paren
suffix:semicolon
macro_line|#endif&t;/* __ISAPNP__ */
DECL|macro|DRIVER_NAME
mdefine_line|#define&t;DRIVER_NAME&t;&quot;snd-card-ad1816a&quot;
macro_line|#ifdef __ISAPNP__
DECL|function|snd_card_ad1816a_isapnp
r_static
r_int
id|__init
id|snd_card_ad1816a_isapnp
c_func
(paren
r_int
id|dev
comma
r_struct
id|snd_card_ad1816a
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
id|snd_ad1816a_isapnp_id
(braket
id|dev
)braket
suffix:semicolon
r_struct
id|isapnp_card
op_star
id|card
op_assign
id|snd_ad1816a_isapnp_cards
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
id|acard-&gt;devmpu
op_assign
id|isapnp_find_dev
c_func
(paren
id|card
comma
id|id-&gt;devs
(braket
l_int|1
)braket
dot
id|vendor
comma
id|id-&gt;devs
(braket
l_int|1
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
id|acard-&gt;devmpu-&gt;active
)paren
(brace
id|acard-&gt;dev
op_assign
id|acard-&gt;devmpu
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
id|port
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
l_int|2
)braket
comma
id|port
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
id|fm_port
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
l_int|1
)braket
comma
id|fm_port
(braket
id|dev
)braket
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma1
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
id|dma1
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
id|dma2
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
l_int|1
)braket
comma
id|dma2
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
id|irq
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
id|irq
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
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;AUDIO isapnp configure failure&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|port
(braket
id|dev
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
suffix:semicolon
id|fm_port
(braket
id|dev
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|dma1
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
id|dma2
(braket
id|dev
)braket
op_assign
id|pdev-&gt;dma_resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|irq
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
id|pdev
op_assign
id|acard-&gt;devmpu
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_eq
l_int|NULL
op_logical_or
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
(brace
id|mpu_port
(braket
id|dev
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|acard-&gt;devmpu
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mpu_port
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
id|mpu_port
(braket
id|dev
)braket
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu_irq
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
id|mpu_irq
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
multiline_comment|/* not fatal error */
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;MPU-401 isapnp configure failure&bslash;n&quot;
)paren
suffix:semicolon
id|mpu_port
(braket
id|dev
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|acard-&gt;devmpu
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|mpu_port
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
id|mpu_irq
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_ad1816a_deactivate
r_static
r_void
id|snd_card_ad1816a_deactivate
c_func
(paren
r_struct
id|snd_card_ad1816a
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
r_if
c_cond
(paren
id|acard-&gt;devmpu
)paren
(brace
id|acard-&gt;devmpu
op_member_access_from_pointer
id|deactivate
c_func
(paren
id|acard-&gt;devmpu
)paren
suffix:semicolon
id|acard-&gt;devmpu
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* __ISAPNP__ */
DECL|function|snd_card_ad1816a_free
r_static
r_void
id|snd_card_ad1816a_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_struct
id|snd_card_ad1816a
op_star
id|acard
op_assign
(paren
r_struct
id|snd_card_ad1816a
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
id|snd_card_ad1816a_deactivate
c_func
(paren
id|acard
)paren
suffix:semicolon
macro_line|#endif&t;/* __ISAPNP__ */
)brace
)brace
DECL|function|snd_card_ad1816a_probe
r_static
r_int
id|__init
id|snd_card_ad1816a_probe
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
id|error
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_card_ad1816a
op_star
id|acard
suffix:semicolon
id|ad1816a_t
op_star
id|chip
suffix:semicolon
id|opl3_t
op_star
id|opl3
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
id|snd_card_ad1816a
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
id|snd_card_ad1816a
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|card-&gt;private_free
op_assign
id|snd_card_ad1816a_free
suffix:semicolon
macro_line|#ifdef __ISAPNP__
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_card_ad1816a_isapnp
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
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;you have to enable ISA PnP support.&bslash;n&quot;
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
id|snd_ad1816a_create
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
id|dma1
(braket
id|dev
)braket
comma
id|dma2
(braket
id|dev
)braket
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
id|snd_ad1816a_pcm
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
id|snd_ad1816a_mixer
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
id|mpu_port
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
id|snd_mpu401_uart_new
c_func
(paren
id|card
comma
l_int|0
comma
id|MPU401_HW_MPU401
comma
id|mpu_port
(braket
id|dev
)braket
comma
l_int|0
comma
id|mpu_irq
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
id|PFX
l_string|&quot;no MPU-401 device at 0x%lx.&bslash;n&quot;
comma
id|mpu_port
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fm_port
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
id|snd_opl3_create
c_func
(paren
id|card
comma
id|fm_port
(braket
id|dev
)braket
comma
id|fm_port
(braket
id|dev
)braket
op_plus
l_int|2
comma
id|OPL3_HW_AUTO
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
id|PFX
l_string|&quot;no OPL device at 0x%lx-0x%lx.&bslash;n&quot;
comma
id|fm_port
(braket
id|dev
)braket
comma
id|fm_port
(braket
id|dev
)braket
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_opl3_timer_new
c_func
(paren
id|opl3
comma
l_int|1
comma
l_int|2
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
id|error
suffix:semicolon
)brace
)brace
)brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;AD1816A&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;ADI SoundPort AD1816A&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s soundcard, SS at 0x%lx, irq %d, dma %d&amp;%d&quot;
comma
id|card-&gt;shortname
comma
id|chip-&gt;port
comma
id|irq
(braket
id|dev
)braket
comma
id|dma1
(braket
id|dev
)braket
comma
id|dma2
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
id|snd_ad1816a_cards
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
DECL|function|snd_ad1816a_isapnp_detect
r_static
r_int
id|__init
id|snd_ad1816a_isapnp_detect
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
id|enable
(braket
id|dev
)braket
)paren
r_continue
suffix:semicolon
id|snd_ad1816a_isapnp_cards
(braket
id|dev
)braket
op_assign
id|card
suffix:semicolon
id|snd_ad1816a_isapnp_id
(braket
id|dev
)braket
op_assign
id|id
suffix:semicolon
id|res
op_assign
id|snd_card_ad1816a_probe
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
macro_line|#endif
DECL|function|alsa_card_ad1816a_init
r_static
r_int
id|__init
id|alsa_card_ad1816a_init
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
id|snd_ad1816a_pnpids
comma
id|snd_ad1816a_isapnp_detect
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
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
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;no AD1816A based soundcards found.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;/* MODULE */
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
DECL|function|alsa_card_ad1816a_exit
r_static
r_void
id|__exit
id|alsa_card_ad1816a_exit
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
id|snd_ad1816a_cards
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_ad1816a_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_ad1816a_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-ad1816a=enable,index,id,port,&n;&t;&t;&t;  mpu_port,fm_port,irq,mpu_irq,&n;&t;&t;&t;  dma1,dma2 */
DECL|function|alsa_card_ad1816a_setup
r_static
r_int
id|__init
id|alsa_card_ad1816a_setup
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
(paren
r_int
op_star
)paren
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
(paren
r_int
op_star
)paren
op_amp
id|fm_port
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
l_string|&quot;snd-ad1816a=&quot;
comma
id|alsa_card_ad1816a_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
