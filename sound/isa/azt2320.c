multiline_comment|/*&n;    card-azt2320.c - driver for Aztech Systems AZT2320 based soundcards.&n;    Copyright (C) 1999-2000 by Massimo Piccioni &lt;dafastidio@libero.it&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;*/
multiline_comment|/*&n;    This driver should provide support for most Aztech AZT2320 based cards.&n;    Several AZT2316 chips are also supported/tested, but autoprobe doesn&squot;t&n;    work: all module option have to be set.&n;&n;    No docs available for us at Aztech headquarters !!!   Unbelievable ...&n;    No other help obtained.&n;&n;    Thanks to Rainer Wiesner &lt;rainer.wiesner@01019freenet.de&gt; for the WSS&n;    activation method (full-duplex audio!).&n;*/
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;sound/core.h&gt;
DECL|macro|SNDRV_GET_ID
mdefine_line|#define SNDRV_GET_ID
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;sound/cs4231.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/opl3.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t cs4231_t
DECL|macro|PFX
mdefine_line|#define PFX &quot;azt2320: &quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Massimo Piccioni &lt;dafastidio@libero.it&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Aztech Systems AZT2320&quot;
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
l_string|&quot;{{Aztech Systems,PRO16V},&quot;
l_string|&quot;{Aztech Systems,AZT2320},&quot;
l_string|&quot;{Aztech Systems,AZT3300},&quot;
l_string|&quot;{Aztech Systems,AZT2320},&quot;
l_string|&quot;{Aztech Systems,AZT3000}}&quot;
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
DECL|variable|wss_port
r_static
r_int
id|wss_port
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
l_string|&quot;Index value for azt2320 based soundcard.&quot;
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
l_string|&quot;ID string for azt2320 based soundcard.&quot;
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
l_string|&quot;Enable azt2320 based soundcard.&quot;
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
l_string|&quot;Port # for azt2320 driver.&quot;
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
id|wss_port
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
id|wss_port
comma
l_string|&quot;WSS Port # for azt2320 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|wss_port
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
l_string|&quot;MPU-401 port # for azt2320 driver.&quot;
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
l_string|&quot;FM port # for azt2320 driver.&quot;
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
l_string|&quot;IRQ # for azt2320 driver.&quot;
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
l_string|&quot;MPU-401 IRQ # for azt2320 driver.&quot;
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
l_string|&quot;1st DMA # for azt2320 driver.&quot;
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
l_string|&quot;2nd DMA # for azt2320 driver.&quot;
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
DECL|struct|snd_card_azt2320
r_struct
id|snd_card_azt2320
(brace
macro_line|#ifdef CONFIG_PNP
DECL|member|dev_no
r_int
id|dev_no
suffix:semicolon
DECL|member|dev
r_struct
id|pnp_dev
op_star
id|dev
suffix:semicolon
DECL|member|devmpu
r_struct
id|pnp_dev
op_star
id|devmpu
suffix:semicolon
macro_line|#endif&t;/* CONFIG_PNP */
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pnp_card_device_id
id|snd_azt2320_pnpids
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/* PRO16V */
(brace
dot
id|id
op_assign
l_string|&quot;AZT1008&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;AZT1008&quot;
)brace
comma
(brace
l_string|&quot;AZT2001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Aztech Sound Galaxy 16 */
(brace
dot
id|id
op_assign
l_string|&quot;AZT2320&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;AZT0001&quot;
)brace
comma
(brace
l_string|&quot;AZT0002&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* Packard Bell Sound III 336 AM/SP */
(brace
dot
id|id
op_assign
l_string|&quot;AZT3000&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;AZT1003&quot;
)brace
comma
(brace
l_string|&quot;AZT2001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* AT3300 */
(brace
dot
id|id
op_assign
l_string|&quot;AZT3002&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;AZT1004&quot;
)brace
comma
(brace
l_string|&quot;AZT2001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* --- */
(brace
dot
id|id
op_assign
l_string|&quot;AZT3005&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;AZT1003&quot;
)brace
comma
(brace
l_string|&quot;AZT2001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* --- */
(brace
dot
id|id
op_assign
l_string|&quot;AZT3011&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;AZT1003&quot;
)brace
comma
(brace
l_string|&quot;AZT2001&quot;
)brace
comma
)brace
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;&quot;
)brace
multiline_comment|/* end */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pnp_card
comma
id|snd_azt2320_pnpids
)paren
suffix:semicolon
DECL|macro|DRIVER_NAME
mdefine_line|#define&t;DRIVER_NAME&t;&quot;snd-card-azt2320&quot;
DECL|function|snd_card_azt2320_isapnp
r_static
r_int
id|__init
id|snd_card_azt2320_isapnp
c_func
(paren
r_int
id|dev
comma
r_struct
id|snd_card_azt2320
op_star
id|acard
comma
r_struct
id|pnp_card_link
op_star
id|card
comma
r_const
r_struct
id|pnp_card_device_id
op_star
id|id
)paren
(brace
r_struct
id|pnp_dev
op_star
id|pdev
suffix:semicolon
r_struct
id|pnp_resource_table
op_star
id|cfg
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pnp_resource_table
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cfg
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|acard-&gt;dev
op_assign
id|pnp_request_card_device
c_func
(paren
id|card
comma
id|id-&gt;devs
(braket
l_int|0
)braket
dot
id|id
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acard-&gt;dev
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|cfg
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|acard-&gt;devmpu
op_assign
id|pnp_request_card_device
c_func
(paren
id|card
comma
id|id-&gt;devs
(braket
l_int|1
)braket
dot
id|id
comma
l_int|NULL
)paren
suffix:semicolon
id|pdev
op_assign
id|acard-&gt;dev
suffix:semicolon
id|pnp_init_resource_table
c_func
(paren
id|cfg
)paren
suffix:semicolon
multiline_comment|/* override resources */
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
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;port_resource
(braket
l_int|0
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
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;port_resource
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
id|wss_port
(braket
id|dev
)braket
op_ne
id|SNDRV_AUTO_PORT
)paren
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;port_resource
(braket
l_int|2
)braket
comma
id|wss_port
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
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;dma_resource
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
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;dma_resource
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
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;irq_resource
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
(paren
id|pnp_manual_config_dev
c_func
(paren
id|pdev
comma
id|cfg
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;AUDIO the requested resources are invalid, using auto config&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|pnp_activate_dev
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;AUDIO pnp configure failure&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cfg
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|port
(braket
id|dev
)braket
op_assign
id|pnp_port_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|fm_port
(braket
id|dev
)braket
op_assign
id|pnp_port_start
c_func
(paren
id|pdev
comma
l_int|1
)paren
suffix:semicolon
id|wss_port
(braket
id|dev
)braket
op_assign
id|pnp_port_start
c_func
(paren
id|pdev
comma
l_int|2
)paren
suffix:semicolon
id|dma1
(braket
id|dev
)braket
op_assign
id|pnp_dma
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|dma2
(braket
id|dev
)braket
op_assign
id|pnp_dma
c_func
(paren
id|pdev
comma
l_int|1
)paren
suffix:semicolon
id|irq
(braket
id|dev
)braket
op_assign
id|pnp_irq
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|pdev
op_assign
id|acard-&gt;devmpu
suffix:semicolon
r_if
c_cond
(paren
id|pdev
op_ne
l_int|NULL
)paren
(brace
id|pnp_init_resource_table
c_func
(paren
id|cfg
)paren
suffix:semicolon
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
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;port_resource
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
id|pnp_resource_change
c_func
(paren
op_amp
id|cfg-&gt;irq_resource
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
(paren
id|pnp_manual_config_dev
c_func
(paren
id|pdev
comma
id|cfg
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;MPU401 the requested resources are invalid, using auto config&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|pnp_activate_dev
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|__mpu_error
suffix:semicolon
id|mpu_port
(braket
id|dev
)braket
op_assign
id|pnp_port_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|mpu_irq
(braket
id|dev
)braket
op_assign
id|pnp_irq
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|__mpu_error
suffix:colon
r_if
c_cond
(paren
id|pdev
)paren
(brace
id|pnp_release_card_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
id|PFX
l_string|&quot;MPU401 pnp configure failure, skipping&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|acard-&gt;devmpu
op_assign
l_int|NULL
suffix:semicolon
id|mpu_port
(braket
id|dev
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|kfree
(paren
id|cfg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* same of snd_sbdsp_command by Jaroslav Kysela */
DECL|function|snd_card_azt2320_command
r_static
r_int
id|__init
id|snd_card_azt2320_command
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_char
id|val
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|limit
suffix:semicolon
id|limit
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|50000
suffix:semicolon
id|i
op_logical_and
(paren
id|limit
op_minus
id|jiffies
)paren
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|port
op_plus
l_int|0x0c
)paren
op_amp
l_int|0x80
)paren
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|port
op_plus
l_int|0x0c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|snd_card_azt2320_enable_wss
r_static
r_int
id|__init
id|snd_card_azt2320_enable_wss
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_card_azt2320_command
c_func
(paren
id|port
comma
l_int|0x09
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_card_azt2320_command
c_func
(paren
id|port
comma
l_int|0x00
)paren
)paren
)paren
r_return
id|error
suffix:semicolon
id|mdelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_azt2320_probe
r_static
r_int
id|__init
id|snd_card_azt2320_probe
c_func
(paren
r_int
id|dev
comma
r_struct
id|pnp_card_link
op_star
id|pcard
comma
r_const
r_struct
id|pnp_card_device_id
op_star
id|pid
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
id|snd_card_azt2320
op_star
id|acard
suffix:semicolon
id|cs4231_t
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
id|snd_card_azt2320
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
id|snd_card_azt2320
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_card_azt2320_isapnp
c_func
(paren
id|dev
comma
id|acard
comma
id|pcard
comma
id|pid
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
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_card_azt2320_enable_wss
c_func
(paren
id|port
(braket
id|dev
)braket
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
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_cs4231_create
c_func
(paren
id|card
comma
id|wss_port
(braket
id|dev
)braket
comma
op_minus
l_int|1
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
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|snd_cs4231_pcm
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
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
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
id|MPU401_HW_AZT2320
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
l_string|&quot;no MPU-401 device at 0x%lx&bslash;n&quot;
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
l_string|&quot;no OPL device at 0x%lx-0x%lx&bslash;n&quot;
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
l_string|&quot;AZT2320&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Aztech AZT2320&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s soundcard, WSS at 0x%lx, irq %i, dma %i&amp;%i&quot;
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
id|pnp_set_card_drvdata
c_func
(paren
id|pcard
comma
id|card
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_azt2320_pnp_detect
r_static
r_int
id|__init
id|snd_azt2320_pnp_detect
c_func
(paren
r_struct
id|pnp_card_link
op_star
id|card
comma
r_const
r_struct
id|pnp_card_device_id
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
id|res
op_assign
id|snd_card_azt2320_probe
c_func
(paren
id|dev
comma
id|card
comma
id|id
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
DECL|function|snd_azt2320_pnp_remove
r_static
r_void
id|__devexit
id|snd_azt2320_pnp_remove
c_func
(paren
r_struct
id|pnp_card_link
op_star
id|pcard
)paren
(brace
id|snd_card_t
op_star
id|card
op_assign
(paren
id|snd_card_t
op_star
)paren
id|pnp_get_card_drvdata
c_func
(paren
id|pcard
)paren
suffix:semicolon
id|snd_card_disconnect
c_func
(paren
id|card
)paren
suffix:semicolon
id|snd_card_free_in_thread
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
DECL|variable|azt2320_pnpc_driver
r_static
r_struct
id|pnp_card_driver
id|azt2320_pnpc_driver
op_assign
(brace
dot
id|flags
op_assign
id|PNP_DRIVER_RES_DISABLE
comma
dot
id|name
op_assign
l_string|&quot;azt2320&quot;
comma
dot
id|id_table
op_assign
id|snd_azt2320_pnpids
comma
dot
id|probe
op_assign
id|snd_azt2320_pnp_detect
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_azt2320_pnp_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|alsa_card_azt2320_init
r_static
r_int
id|__init
id|alsa_card_azt2320_init
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
id|snd_azt2320_pnpids
comma
id|snd_azt2320_isapnp_detect
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
id|cards
op_add_assign
id|pnp_register_card_driver
c_func
(paren
op_amp
id|azt2320_pnpc_driver
)paren
suffix:semicolon
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
l_string|&quot;no AZT2320 based soundcards found&bslash;n&quot;
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
DECL|function|alsa_card_azt2320_exit
r_static
r_void
id|__exit
id|alsa_card_azt2320_exit
c_func
(paren
r_void
)paren
(brace
id|pnp_unregister_card_driver
c_func
(paren
op_amp
id|azt2320_pnpc_driver
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_azt2320_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_azt2320_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-azt2320=enable,index,id,port,&n;&t;&t;&t;  wss_port,mpu_port,fm_port,&n;&t;&t;&t;  irq,mpu_irq,dma1,dma2 */
DECL|function|alsa_card_azt2320_setup
r_static
r_int
id|__init
id|alsa_card_azt2320_setup
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
id|wss_port
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
l_string|&quot;snd-azt2320=&quot;
comma
id|alsa_card_azt2320_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
