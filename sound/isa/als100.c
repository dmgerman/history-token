multiline_comment|/*&n;    card-als100.c - driver for Avance Logic ALS100 based soundcards.&n;    Copyright (C) 1999-2000 by Massimo Piccioni &lt;dafastidio@libero.it&gt;&n;&n;    Thanks to Pierfrancesco &squot;qM2&squot; Passerini.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n;*/
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;sound/core.h&gt;
DECL|macro|SNDRV_GET_ID
mdefine_line|#define SNDRV_GET_ID
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;sound/mpu401.h&gt;
macro_line|#include &lt;sound/opl3.h&gt;
macro_line|#include &lt;sound/sb.h&gt;
DECL|macro|chip_t
mdefine_line|#define chip_t sb_t
DECL|macro|PFX
mdefine_line|#define PFX &quot;als100: &quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Massimo Piccioni &lt;dafastidio@libero.it&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Avance Logic ALS1X0&quot;
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
l_string|&quot;{{Avance Logic,ALS100 - PRO16PNP},&quot;
l_string|&quot;{Avance Logic,ALS110},&quot;
l_string|&quot;{Avance Logic,ALS120},&quot;
l_string|&quot;{Avance Logic,ALS200},&quot;
l_string|&quot;{3D Melody,MF1000},&quot;
l_string|&quot;{Digimate,3D Sound},&quot;
l_string|&quot;{Avance Logic,ALS120},&quot;
l_string|&quot;{RTL,RTL3000}}&quot;
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
multiline_comment|/* PnP setup */
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
multiline_comment|/* PnP setup */
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
multiline_comment|/* PnP setup */
DECL|variable|dma16
r_static
r_int
id|dma16
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
l_string|&quot;Index value for als100 based soundcard.&quot;
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
l_string|&quot;ID string for als100 based soundcard.&quot;
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
l_string|&quot;Enable als100 based soundcard.&quot;
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
l_string|&quot;Port # for als100 driver.&quot;
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
l_string|&quot;MPU-401 port # for als100 driver.&quot;
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
l_string|&quot;FM port # for als100 driver.&quot;
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
l_string|&quot;IRQ # for als100 driver.&quot;
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
l_string|&quot;MPU-401 IRQ # for als100 driver.&quot;
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
l_string|&quot;8-bit DMA # for als100 driver.&quot;
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
id|dma16
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
id|dma16
comma
l_string|&quot;16-bit DMA # for als100 driver.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|dma16
comma
id|SNDRV_DMA16_DESC
)paren
suffix:semicolon
DECL|struct|snd_card_als100
r_struct
id|snd_card_als100
(brace
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
DECL|member|devopl
r_struct
id|pnp_dev
op_star
id|devopl
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pnp_card_id
id|snd_als100_pnpids
(braket
)braket
id|__devinitdata
op_assign
(brace
multiline_comment|/* ALS100 - PRO16PNP */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0001&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;@@@0001&quot;
)brace
comma
(brace
l_string|&quot;@X@0001&quot;
)brace
comma
(brace
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS110 - MF1000 - Digimate 3D Sound */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0110&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;@@@1001&quot;
)brace
comma
(brace
l_string|&quot;@X@1001&quot;
)brace
comma
(brace
l_string|&quot;@H@1001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS120 */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0120&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;@@@2001&quot;
)brace
comma
(brace
l_string|&quot;@X@2001&quot;
)brace
comma
(brace
l_string|&quot;@H@2001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* ALS200 */
(brace
dot
id|id
op_assign
l_string|&quot;ALS0200&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;@@@0020&quot;
)brace
comma
(brace
l_string|&quot;@X@0020&quot;
)brace
comma
(brace
l_string|&quot;@H@0001&quot;
)brace
comma
)brace
)brace
comma
multiline_comment|/* RTL3000 */
(brace
dot
id|id
op_assign
l_string|&quot;RTL3000&quot;
comma
dot
id|devs
op_assign
(brace
(brace
l_string|&quot;@@@2001&quot;
)brace
comma
(brace
l_string|&quot;@X@2001&quot;
)brace
comma
(brace
l_string|&quot;@H@2001&quot;
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
comma
)brace
multiline_comment|/* end */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pnp_card
comma
id|snd_als100_pnpids
)paren
suffix:semicolon
DECL|macro|DRIVER_NAME
mdefine_line|#define DRIVER_NAME&t;&quot;snd-card-als100&quot;
DECL|variable|als100_pnpc_driver
r_static
r_struct
id|pnp_card_driver
id|als100_pnpc_driver
suffix:semicolon
DECL|function|snd_card_als100_isapnp
r_static
r_int
id|__devinit
id|snd_card_als100_isapnp
c_func
(paren
r_int
id|dev
comma
r_struct
id|snd_card_als100
op_star
id|acard
comma
r_struct
id|pnp_card
op_star
id|card
comma
r_const
r_struct
id|pnp_card_id
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
id|GFP_ATOMIC
comma
r_sizeof
(paren
r_struct
id|pnp_resource_table
)paren
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
op_amp
id|als100_pnpc_driver
comma
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
op_amp
id|als100_pnpc_driver
comma
id|card
comma
id|id-&gt;devs
(braket
l_int|1
)braket
dot
id|id
comma
id|acard-&gt;dev
)paren
suffix:semicolon
id|acard-&gt;devopl
op_assign
id|pnp_request_card_device
c_func
(paren
op_amp
id|als100_pnpc_driver
comma
id|card
comma
id|id-&gt;devs
(braket
l_int|2
)braket
dot
id|id
comma
id|acard-&gt;devmpu
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
id|dma8
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
id|dma8
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
id|dma16
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
id|dma16
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
id|dma8
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
id|dma16
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
id|pdev
op_assign
id|acard-&gt;devopl
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
l_int|0
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
l_string|&quot;OPL3 the requested resources are invalid, using auto config&bslash;n&quot;
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
id|__fm_error
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
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|__fm_error
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
l_string|&quot;OPL3 pnp configure failure, skipping&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|acard-&gt;devopl
op_assign
l_int|NULL
suffix:semicolon
id|fm_port
(braket
id|dev
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|cfg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_als100_probe
r_static
r_int
id|__init
id|snd_card_als100_probe
c_func
(paren
r_int
id|dev
comma
r_struct
id|pnp_card
op_star
id|pcard
comma
r_const
r_struct
id|pnp_card_id
op_star
id|pid
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
id|snd_card_als100
op_star
id|acard
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
id|snd_card_als100
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
id|snd_card_als100
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
id|snd_card_als100_isapnp
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
id|snd_sb16dsp_interrupt
comma
id|dma8
(braket
id|dev
)braket
comma
id|dma16
(braket
id|dev
)braket
comma
id|SB_HW_ALS100
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
id|snd_sb16dsp_pcm
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
id|MPU401_HW_ALS100
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
l_int|0
comma
l_int|1
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
l_string|&quot;ALS100&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Avance Logic ALS100&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s soundcard, %s at 0x%lx, irq %d, dma %d&amp;%d&quot;
comma
id|card-&gt;shortname
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
comma
id|dma16
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
DECL|function|snd_als100_pnp_detect
r_static
r_int
id|__devinit
id|snd_als100_pnp_detect
c_func
(paren
r_struct
id|pnp_card
op_star
id|card
comma
r_const
r_struct
id|pnp_card_id
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
id|snd_card_als100_probe
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
DECL|function|snd_als100_pnp_remove
r_static
r_void
id|__devexit
id|snd_als100_pnp_remove
c_func
(paren
r_struct
id|pnp_card
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
DECL|variable|als100_pnpc_driver
r_static
r_struct
id|pnp_card_driver
id|als100_pnpc_driver
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
l_string|&quot;als100&quot;
comma
dot
id|id_table
op_assign
id|snd_als100_pnpids
comma
dot
id|probe
op_assign
id|snd_als100_pnp_detect
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_als100_pnp_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|alsa_card_als100_init
r_static
r_int
id|__init
id|alsa_card_als100_init
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
id|cards
op_add_assign
id|pnp_register_card_driver
c_func
(paren
op_amp
id|als100_pnpc_driver
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
l_string|&quot;no ALS100 based soundcards found&bslash;n&quot;
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
DECL|function|alsa_card_als100_exit
r_static
r_void
id|__exit
id|alsa_card_als100_exit
c_func
(paren
r_void
)paren
(brace
id|pnp_unregister_card_driver
c_func
(paren
op_amp
id|als100_pnpc_driver
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_als100_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_als100_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-als100=enable,index,id,port,&n;&t;&t;&t; mpu_port,fm_port,irq,mpu_irq,&n;&t;&t;&t; dma8,dma16 */
DECL|function|alsa_card_als100_setup
r_static
r_int
id|__init
id|alsa_card_als100_setup
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
id|dma16
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
l_string|&quot;snd-als100=&quot;
comma
id|alsa_card_als100_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
