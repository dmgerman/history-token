multiline_comment|/*&n; * ALSA driver for the Aureal Vortex family of soundprocessors.&n; * Author: Manuel Jander (mjander@embedded.cl)&n; *&n; *   This driver is the result of the OpenVortex Project from Savannah&n; * (savannah.nongnu.org/projects/openvortex). I would like to thank&n; * the developers of OpenVortex, Jeff Muizelar and Kester Maddock, from&n; * whom i got plenty of help, and their codebase was invaluable.&n; *   Thanks to the ALSA developers, they helped a lot working out&n; * the ALSA part.&n; *   Thanks also to Sourceforge for maintaining the old binary drivers,&n; * and the forum, where developers could comunicate.&n; *&n; * Now at least i can play Legacy DOOM with MIDI music :-)&n; */
macro_line|#include &quot;au88x0.h&quot;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
singleline_comment|// module parameters (see &quot;Module Parameters&quot;)
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
DECL|variable|pcifix
r_static
r_int
id|pcifix
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
l_int|255
)brace
suffix:semicolon
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
l_string|&quot;Index value for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
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
l_string|&quot;ID string for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
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
l_string|&quot;Enable &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
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
id|module_param_array
c_func
(paren
id|pcifix
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
id|pcifix
comma
l_string|&quot;Enable VIA-workaround for &quot;
id|CARD_NAME
l_string|&quot; soundcard.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|pcifix
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{0,Disabled},{1,Latency},{2,Bridge},{3,Both},{255,Auto}},default:4,dialog:check&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Aureal vortex&quot;
)paren
suffix:semicolon
id|MODULE_CLASSES
c_func
(paren
l_string|&quot;{sound}&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_DEVICES
c_func
(paren
l_string|&quot;{{Aureal Semiconductor Inc., Aureal Vortex Sound Processor}}&quot;
)paren
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|snd_vortex_ids
)paren
suffix:semicolon
DECL|function|snd_vortex_workaround
r_static
r_void
id|__devinit
id|snd_vortex_workaround
c_func
(paren
r_struct
id|pci_dev
op_star
id|vortex
comma
r_int
id|fix
)paren
(brace
r_struct
id|pci_dev
op_star
id|via
op_assign
l_int|NULL
suffix:semicolon
r_int
id|rc
suffix:semicolon
multiline_comment|/* autodetect if workarounds are required */
r_while
c_loop
(paren
(paren
id|via
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_VIA
comma
id|PCI_DEVICE_ID_VIA_8365_1
comma
id|via
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|fix
op_eq
l_int|255
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|CARD_NAME
l_string|&quot;: detected VIA KT133/KM133. activating workaround...&bslash;n&quot;
)paren
suffix:semicolon
id|fix
op_assign
l_int|3
suffix:semicolon
singleline_comment|// do latency and via bridge workaround
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/* do not do anything if autodetection was enabled and found no VIA */
r_if
c_cond
(paren
id|fix
op_eq
l_int|255
)paren
r_return
suffix:semicolon
multiline_comment|/* fix vortex latency */
r_if
c_cond
(paren
id|fix
op_amp
l_int|0x01
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|rc
op_assign
id|pci_write_config_byte
c_func
(paren
id|vortex
comma
l_int|0x40
comma
l_int|0xff
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|CARD_NAME
l_string|&quot;: vortex latency is 0xff&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|CARD_NAME
l_string|&quot;: could not set vortex latency: pci error 0x%x&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* fix via agp bridge */
r_if
c_cond
(paren
id|via
op_logical_and
(paren
id|fix
op_amp
l_int|0x02
)paren
)paren
(brace
id|u8
id|value
suffix:semicolon
multiline_comment|/*&n;&t;&t; * only set the bit (Extend PCI#2 Internal Master for&n;&t;&t; * Efficient Handling of Dummy Requests) if the can&n;&t;&t; * read the config and it is not already set&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|rc
op_assign
id|pci_read_config_byte
c_func
(paren
id|via
comma
l_int|0x42
comma
op_amp
id|value
)paren
)paren
op_logical_and
(paren
(paren
id|value
op_amp
l_int|0x10
)paren
op_logical_or
op_logical_neg
(paren
id|rc
op_assign
id|pci_write_config_byte
c_func
(paren
id|via
comma
l_int|0x42
comma
id|value
op_or
l_int|0x10
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
id|CARD_NAME
l_string|&quot;: bridge config is 0x%x&bslash;n&quot;
comma
id|value
op_or
l_int|0x10
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
id|CARD_NAME
l_string|&quot;: could not set vortex latency: pci error 0x%x&bslash;n&quot;
comma
id|rc
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|// component-destructor
singleline_comment|// (see &quot;Management of Cards and Components&quot;)
DECL|function|snd_vortex_dev_free
r_static
r_int
id|snd_vortex_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|vortex_t
op_star
id|vortex
op_assign
id|snd_magic_cast
c_func
(paren
id|vortex_t
comma
id|device-&gt;device_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|vortex_gameport_unregister
c_func
(paren
id|vortex
)paren
suffix:semicolon
id|vortex_core_shutdown
c_func
(paren
id|vortex
)paren
suffix:semicolon
singleline_comment|// Take down PCI interface.
id|synchronize_irq
c_func
(paren
id|vortex-&gt;irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|vortex-&gt;irq
comma
id|vortex
)paren
suffix:semicolon
id|pci_release_regions
c_func
(paren
id|vortex-&gt;pci_dev
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|vortex-&gt;pci_dev
)paren
suffix:semicolon
id|snd_magic_kfree
c_func
(paren
id|vortex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// chip-specific constructor
singleline_comment|// (see &quot;Management of Cards and Components&quot;)
r_static
r_int
id|__devinit
DECL|function|snd_vortex_create
id|snd_vortex_create
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
id|vortex_t
op_star
op_star
id|rchip
)paren
(brace
id|vortex_t
op_star
id|chip
suffix:semicolon
r_int
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
id|snd_vortex_dev_free
comma
)brace
suffix:semicolon
op_star
id|rchip
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// check PCI availability (DMA).
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
r_if
c_cond
(paren
op_logical_neg
id|pci_dma_supported
c_func
(paren
id|pci
comma
id|VORTEX_DMA_MASK
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error to set DMA mask&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|pci_set_dma_mask
c_func
(paren
id|pci
comma
id|VORTEX_DMA_MASK
)paren
suffix:semicolon
id|chip
op_assign
id|snd_magic_kcalloc
c_func
(paren
id|vortex_t
comma
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chip
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|chip-&gt;card
op_assign
id|card
suffix:semicolon
singleline_comment|// initialize the stuff
id|chip-&gt;pci_dev
op_assign
id|pci
suffix:semicolon
id|chip-&gt;io
op_assign
id|pci_resource_start
c_func
(paren
id|pci
comma
l_int|0
)paren
suffix:semicolon
id|chip-&gt;vendor
op_assign
id|pci-&gt;vendor
suffix:semicolon
id|chip-&gt;device
op_assign
id|pci-&gt;device
suffix:semicolon
id|chip-&gt;card
op_assign
id|card
suffix:semicolon
id|chip-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// (1) PCI resource allocation
singleline_comment|// Get MMIO area
singleline_comment|//
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
id|CARD_NAME_SHORT
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|regions_out
suffix:semicolon
id|chip-&gt;mmio
op_assign
id|ioremap_nocache
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pci
comma
l_int|0
)paren
comma
id|pci_resource_len
c_func
(paren
id|pci
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|chip-&gt;mmio
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;MMIO area remap failed.&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|ioremap_out
suffix:semicolon
)brace
multiline_comment|/* Init audio core.&n;&t; * This must be done before we do request_irq otherwise we can get spurious&n;&t; * interupts that we do not handle properly and make a mess of things */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|vortex_core_init
c_func
(paren
id|chip
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hw core init failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|core_out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|request_irq
c_func
(paren
id|pci-&gt;irq
comma
id|vortex_interrupt
comma
id|SA_INTERRUPT
op_or
id|SA_SHIRQ
comma
id|CARD_NAME_SHORT
comma
(paren
r_void
op_star
)paren
id|chip
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cannot grab irq&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|irq_out
suffix:semicolon
)brace
id|chip-&gt;irq
op_assign
id|pci-&gt;irq
suffix:semicolon
id|pci_set_master
c_func
(paren
id|pci
)paren
suffix:semicolon
singleline_comment|// End of PCI setup.
singleline_comment|// Register alsa root device.
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
r_goto
id|alloc_out
suffix:semicolon
)brace
op_star
id|rchip
op_assign
id|chip
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|alloc_out
suffix:colon
id|synchronize_irq
c_func
(paren
id|chip-&gt;irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|chip-&gt;irq
comma
id|chip
)paren
suffix:semicolon
id|irq_out
suffix:colon
id|vortex_core_shutdown
c_func
(paren
id|chip
)paren
suffix:semicolon
id|core_out
suffix:colon
singleline_comment|//FIXME: the type of chip-&gt;mmio might need to be changed??
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|chip-&gt;mmio
)paren
suffix:semicolon
id|ioremap_out
suffix:colon
id|pci_release_regions
c_func
(paren
id|chip-&gt;pci_dev
)paren
suffix:semicolon
id|regions_out
suffix:colon
id|pci_disable_device
c_func
(paren
id|chip-&gt;pci_dev
)paren
suffix:semicolon
singleline_comment|//FIXME: this not the right place to unregister the gameport
id|vortex_gameport_unregister
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
singleline_comment|// constructor -- see &quot;Constructor&quot; sub-section
r_static
r_int
id|__devinit
DECL|function|snd_vortex_probe
id|snd_vortex_probe
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
id|vortex_t
op_star
id|chip
suffix:semicolon
r_int
id|err
suffix:semicolon
singleline_comment|// (1)
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
singleline_comment|// (2)
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
singleline_comment|// (3)
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vortex_create
c_func
(paren
id|card
comma
id|pci
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
id|snd_vortex_workaround
c_func
(paren
id|pci
comma
id|pcifix
(braket
id|dev
)braket
)paren
suffix:semicolon
singleline_comment|// (4) Alloc components.
singleline_comment|// ADB pcm.
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vortex_new_pcm
c_func
(paren
id|chip
comma
id|VORTEX_PCM_ADB
comma
id|NR_ADB
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
macro_line|#ifndef CHIP_AU8820
singleline_comment|// ADB SPDIF
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vortex_new_pcm
c_func
(paren
id|chip
comma
id|VORTEX_PCM_SPDIF
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
id|err
suffix:semicolon
)brace
singleline_comment|// A3D
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vortex_new_pcm
c_func
(paren
id|chip
comma
id|VORTEX_PCM_A3D
comma
id|NR_A3D
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
macro_line|#endif
multiline_comment|/*&n;&t;   // ADB I2S&n;&t;   if ((err = snd_vortex_new_pcm(chip, VORTEX_PCM_I2S, 1)) &lt; 0) {&n;&t;   snd_card_free(card);&n;&t;   return err;&n;&t;   }&n;&t; */
macro_line|#ifndef CHIP_AU8810
singleline_comment|// WT pcm.
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vortex_new_pcm
c_func
(paren
id|chip
comma
id|VORTEX_PCM_WT
comma
id|NR_WT
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
macro_line|#endif
singleline_comment|// snd_ac97_mixer and Vortex mixer.
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_vortex_mixer
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
id|snd_vortex_midi
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
id|vortex_gameport_register
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
macro_line|#if 0
r_if
c_cond
(paren
id|snd_seq_device_new
c_func
(paren
id|card
comma
l_int|1
comma
id|SNDRV_SEQ_DEV_ID_VORTEX_SYNTH
comma
r_sizeof
(paren
id|snd_vortex_synth_arg_t
)paren
comma
op_amp
id|wave
)paren
OL
l_int|0
op_logical_or
id|wave
op_eq
l_int|NULL
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;Can&squot;t initialize Aureal wavetable synth&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_vortex_synth_arg_t
op_star
id|arg
suffix:semicolon
id|arg
op_assign
id|SNDRV_SEQ_DEVICE_ARGPTR
c_func
(paren
id|wave
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|wave-&gt;name
comma
l_string|&quot;Aureal Synth&quot;
)paren
suffix:semicolon
id|arg-&gt;hwptr
op_assign
id|vortex
suffix:semicolon
id|arg-&gt;index
op_assign
l_int|1
suffix:semicolon
id|arg-&gt;seq_ports
op_assign
id|seq_ports
(braket
id|dev
)braket
suffix:semicolon
id|arg-&gt;max_voices
op_assign
id|max_synth_voices
(braket
id|dev
)braket
suffix:semicolon
)brace
macro_line|#endif
singleline_comment|// (5)
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;Aureal Vortex&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
id|CARD_NAME_SHORT
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%lx irq %i&quot;
comma
id|card-&gt;shortname
comma
id|chip-&gt;io
comma
id|chip-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_read_config_word
c_func
(paren
id|pci
comma
id|PCI_DEVICE_ID
comma
op_amp
(paren
id|chip-&gt;device
)paren
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
id|pci_read_config_word
c_func
(paren
id|pci
comma
id|PCI_VENDOR_ID
comma
op_amp
(paren
id|chip-&gt;vendor
)paren
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
id|pci_read_config_byte
c_func
(paren
id|pci
comma
id|PCI_REVISION_ID
comma
op_amp
(paren
id|chip-&gt;rev
)paren
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
macro_line|#ifdef CHIP_AU8830
r_if
c_cond
(paren
(paren
id|chip-&gt;rev
)paren
op_ne
l_int|0xfe
op_logical_and
(paren
id|chip-&gt;rev
)paren
op_ne
l_int|0xfa
)paren
(brace
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;vortex: The revision (%x) of your card has not been seen before.&bslash;n&quot;
comma
id|chip-&gt;rev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ALERT
l_string|&quot;vortex: Please email the results of &squot;lspci -vv&squot; to openvortex-dev@nongnu.org.&bslash;n&quot;
)paren
suffix:semicolon
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
singleline_comment|// (6)
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
singleline_comment|// (7)
id|pci_set_drvdata
c_func
(paren
id|pci
comma
id|chip
)paren
suffix:semicolon
id|dev
op_increment
suffix:semicolon
id|vortex_connect_default
c_func
(paren
id|chip
comma
l_int|1
)paren
suffix:semicolon
id|vortex_enable_int
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// destructor -- see &quot;Destructor&quot; sub-section
DECL|function|snd_vortex_remove
r_static
r_void
id|__devexit
id|snd_vortex_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
id|vortex_t
op_star
id|vortex
op_assign
id|snd_magic_cast
c_func
(paren
id|vortex_t
comma
id|pci_get_drvdata
c_func
(paren
id|pci
)paren
comma
r_return
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vortex
)paren
(brace
singleline_comment|// Release ALSA stuff.
id|snd_card_free
c_func
(paren
id|vortex-&gt;card
)paren
suffix:semicolon
singleline_comment|// Free Vortex struct.
id|pci_set_drvdata
c_func
(paren
id|pci
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;snd_vortex_remove called more than one time!&bslash;n&quot;
)paren
suffix:semicolon
)brace
singleline_comment|// pci_driver definition
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
id|CARD_NAME_SHORT
comma
dot
id|id_table
op_assign
id|snd_vortex_ids
comma
dot
id|probe
op_assign
id|snd_vortex_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_vortex_remove
)paren
comma
)brace
suffix:semicolon
singleline_comment|// initialization of the module
DECL|function|alsa_card_vortex_init
r_static
r_int
id|__init
id|alsa_card_vortex_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pci_module_init
c_func
(paren
op_amp
id|driver
)paren
)paren
OL
l_int|0
)paren
(brace
macro_line|#ifdef MODULE
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Aureal soundcard not found &quot;
l_string|&quot;or device busy&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// clean up the module
DECL|function|alsa_card_vortex_exit
r_static
r_void
id|__exit
id|alsa_card_vortex_exit
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
id|alsa_card_vortex_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_vortex_exit
)paren
eof
