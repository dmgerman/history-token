multiline_comment|/*&n; * Driver for Digigram VX222 V2/Mic PCI soundcards&n; *&n; * Copyright (c) 2002 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &quot;vx222.h&quot;
DECL|macro|CARD_NAME
mdefine_line|#define CARD_NAME &quot;VX222&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Digigram VX222 V2/Mic&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;{{Digigram,&quot;
id|CARD_NAME
l_string|&quot;}}&quot;
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
id|SNDRV_DEFAULT_ENABLE_PNP
suffix:semicolon
multiline_comment|/* Enable this card */
DECL|variable|mic
r_static
r_int
id|mic
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
multiline_comment|/* microphone */
DECL|variable|ibl
r_static
r_int
id|ibl
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
multiline_comment|/* microphone */
DECL|variable|boot_devs
r_static
r_int
id|boot_devs
suffix:semicolon
id|module_param_array
c_func
(paren
id|index
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|index
comma
l_string|&quot;Index value for Digigram &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|id
comma
id|charp
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|id
comma
l_string|&quot;ID string for Digigram &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|enable
comma
r_bool
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|enable
comma
l_string|&quot;Enable Digigram &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|mic
comma
r_bool
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mic
comma
l_string|&quot;Enable Microphone.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|ibl
comma
r_int
comma
id|boot_devs
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|ibl
comma
l_string|&quot;Capture IBL size.&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; */
r_enum
(brace
DECL|enumerator|VX_PCI_VX222_OLD
id|VX_PCI_VX222_OLD
comma
DECL|enumerator|VX_PCI_VX222_NEW
id|VX_PCI_VX222_NEW
)brace
suffix:semicolon
DECL|variable|snd_vx222_ids
r_static
r_struct
id|pci_device_id
id|snd_vx222_ids
(braket
)braket
op_assign
(brace
(brace
l_int|0x10b5
comma
l_int|0x9050
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|VX_PCI_VX222_OLD
comma
)brace
comma
multiline_comment|/* PLX */
(brace
l_int|0x10b5
comma
l_int|0x9030
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|VX_PCI_VX222_NEW
comma
)brace
comma
multiline_comment|/* PLX */
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|snd_vx222_ids
)paren
suffix:semicolon
multiline_comment|/*&n; */
DECL|variable|vx222_old_hw
r_static
r_struct
id|snd_vx_hardware
id|vx222_old_hw
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VX222/Old&quot;
comma
dot
id|type
op_assign
id|VX_TYPE_BOARD
comma
multiline_comment|/* hw specs */
dot
id|num_codecs
op_assign
l_int|1
comma
dot
id|num_ins
op_assign
l_int|1
comma
dot
id|num_outs
op_assign
l_int|1
comma
dot
id|output_level_max
op_assign
id|VX_ANALOG_OUT_LEVEL_MAX
comma
)brace
suffix:semicolon
DECL|variable|vx222_v2_hw
r_static
r_struct
id|snd_vx_hardware
id|vx222_v2_hw
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VX222/v2&quot;
comma
dot
id|type
op_assign
id|VX_TYPE_V2
comma
multiline_comment|/* hw specs */
dot
id|num_codecs
op_assign
l_int|1
comma
dot
id|num_ins
op_assign
l_int|1
comma
dot
id|num_outs
op_assign
l_int|1
comma
dot
id|output_level_max
op_assign
id|VX2_AKM_LEVEL_MAX
comma
)brace
suffix:semicolon
DECL|variable|vx222_mic_hw
r_static
r_struct
id|snd_vx_hardware
id|vx222_mic_hw
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;VX222/Mic&quot;
comma
dot
id|type
op_assign
id|VX_TYPE_MIC
comma
multiline_comment|/* hw specs */
dot
id|num_codecs
op_assign
l_int|1
comma
dot
id|num_ins
op_assign
l_int|1
comma
dot
id|num_outs
op_assign
l_int|1
comma
dot
id|output_level_max
op_assign
id|VX2_AKM_LEVEL_MAX
comma
)brace
suffix:semicolon
multiline_comment|/*&n; */
DECL|function|snd_vx222_free
r_static
r_int
id|snd_vx222_free
c_func
(paren
id|vx_core_t
op_star
id|chip
)paren
(brace
r_struct
id|snd_vx222
op_star
id|vx
op_assign
(paren
r_struct
id|snd_vx222
op_star
)paren
id|chip
suffix:semicolon
r_if
c_cond
(paren
id|chip-&gt;irq
op_ge
l_int|0
)paren
id|free_irq
c_func
(paren
id|chip-&gt;irq
comma
(paren
r_void
op_star
)paren
id|chip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vx-&gt;port
(braket
l_int|0
)braket
)paren
id|pci_release_regions
c_func
(paren
id|vx-&gt;pci
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_vx222_dev_free
r_static
r_int
id|snd_vx222_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|vx_core_t
op_star
id|chip
op_assign
id|device-&gt;device_data
suffix:semicolon
r_return
id|snd_vx222_free
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
DECL|function|snd_vx222_create
r_static
r_int
id|__devinit
id|snd_vx222_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|pci_dev
op_star
id|pci
comma
r_struct
id|snd_vx_hardware
op_star
id|hw
comma
r_struct
id|snd_vx222
op_star
op_star
id|rchip
)paren
(brace
id|vx_core_t
op_star
id|chip
suffix:semicolon
r_struct
id|snd_vx222
op_star
id|vx
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
r_static
id|snd_device_ops_t
id|ops
op_assign
(brace
dot
id|dev_free
op_assign
id|snd_vx222_dev_free
comma
)brace
suffix:semicolon
r_struct
id|snd_vx_ops
op_star
id|vx_ops
suffix:semicolon
multiline_comment|/* enable PCI device */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_enable_device
c_func
(paren
id|pci
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|pci_set_master
c_func
(paren
id|pci
)paren
suffix:semicolon
id|vx_ops
op_assign
id|hw-&gt;type
op_eq
id|VX_TYPE_BOARD
ques
c_cond
op_amp
id|vx222_old_ops
suffix:colon
op_amp
id|vx222_ops
suffix:semicolon
id|chip
op_assign
id|snd_vx_create
c_func
(paren
id|card
comma
id|hw
comma
id|vx_ops
comma
r_sizeof
(paren
r_struct
id|snd_vx222
)paren
op_minus
r_sizeof
(paren
id|vx_core_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chip
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|vx
op_assign
(paren
r_struct
id|snd_vx222
op_star
)paren
id|chip
suffix:semicolon
id|vx-&gt;pci
op_assign
id|pci
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_request_regions
c_func
(paren
id|pci
comma
id|CARD_NAME
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_vx222_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|vx-&gt;port
(braket
id|i
)braket
op_assign
id|pci_resource_start
c_func
(paren
id|pci
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|pci-&gt;irq
comma
id|snd_vx_irq_handler
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
comma
id|CARD_NAME
comma
(paren
r_void
op_star
)paren
id|chip
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to grab IRQ %d&bslash;n&quot;
comma
id|pci-&gt;irq
)paren
suffix:semicolon
id|snd_vx222_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|chip-&gt;irq
op_assign
id|pci-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_device_new
c_func
(paren
id|card
comma
id|SNDRV_DEV_LOWLEVEL
comma
id|chip
comma
op_amp
id|ops
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_vx222_free
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|snd_card_set_dev
c_func
(paren
id|card
comma
op_amp
id|pci-&gt;dev
)paren
suffix:semicolon
op_star
id|rchip
op_assign
id|vx
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_vx222_probe
r_static
r_int
id|__devinit
id|snd_vx222_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_const
r_struct
id|pci_device_id
op_star
id|pci_id
)paren
(brace
r_static
r_int
id|dev
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_struct
id|snd_vx_hardware
op_star
id|hw
suffix:semicolon
r_struct
id|snd_vx222
op_star
id|vx
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|SNDRV_CARDS
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|enable
(braket
id|dev
)braket
)paren
(brace
id|dev
op_increment
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
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
r_switch
c_cond
(paren
(paren
r_int
)paren
id|pci_id-&gt;driver_data
)paren
(brace
r_case
id|VX_PCI_VX222_OLD
suffix:colon
id|hw
op_assign
op_amp
id|vx222_old_hw
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VX_PCI_VX222_NEW
suffix:colon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|mic
(braket
id|dev
)braket
)paren
id|hw
op_assign
op_amp
id|vx222_mic_hw
suffix:semicolon
r_else
id|hw
op_assign
op_amp
id|vx222_v2_hw
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vx222_create
c_func
(paren
id|card
comma
id|pci
comma
id|hw
comma
op_amp
id|vx
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
id|vx-&gt;core.ibl.size
op_assign
id|ibl
(braket
id|dev
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%lx &amp; 0x%lx, irq %i&quot;
comma
id|card-&gt;shortname
comma
id|vx-&gt;port
(braket
l_int|0
)braket
comma
id|vx-&gt;port
(braket
l_int|1
)braket
comma
id|vx-&gt;core.irq
)paren
suffix:semicolon
id|snd_printdd
c_func
(paren
l_string|&quot;%s at 0x%lx &amp; 0x%lx, irq %i&bslash;n&quot;
comma
id|card-&gt;shortname
comma
id|vx-&gt;port
(braket
l_int|0
)braket
comma
id|vx-&gt;port
(braket
l_int|1
)braket
comma
id|vx-&gt;core.irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vx_hwdep_new
c_func
(paren
op_amp
id|vx-&gt;core
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
id|pci_set_drvdata
c_func
(paren
id|pci
comma
id|card
)paren
suffix:semicolon
id|dev
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_vx222_remove
r_static
r_void
id|__devexit
id|snd_vx222_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
id|snd_card_free
c_func
(paren
id|pci_get_drvdata
c_func
(paren
id|pci
)paren
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pci
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|driver
r_static
r_struct
id|pci_driver
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Digigram VX222&quot;
comma
dot
id|id_table
op_assign
id|snd_vx222_ids
comma
dot
id|probe
op_assign
id|snd_vx222_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_vx222_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|alsa_card_vx222_init
r_static
r_int
id|__init
id|alsa_card_vx222_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
DECL|function|alsa_card_vx222_exit
r_static
r_void
id|__exit
id|alsa_card_vx222_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_vx222_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_vx222_exit
)paren
eof
