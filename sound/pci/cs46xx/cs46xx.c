multiline_comment|/*&n; *  The driver for the Cirrus Logic&squot;s Sound Fusion CS46XX based soundcards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/*&n;  NOTES:&n;  - sometimes the sound is metallic and sibilant, unloading and &n;    reloading the module may solve this.&n;*/
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/cs46xx.h&gt;
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
l_string|&quot;Cirrus Logic Sound Fusion CS46XX&quot;
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
l_string|&quot;{{Cirrus Logic,Sound Fusion (CS4280)},&quot;
l_string|&quot;{Cirrus Logic,Sound Fusion (CS4610)},&quot;
l_string|&quot;{Cirrus Logic,Sound Fusion (CS4612)},&quot;
l_string|&quot;{Cirrus Logic,Sound Fusion (CS4615)},&quot;
l_string|&quot;{Cirrus Logic,Sound Fusion (CS4622)},&quot;
l_string|&quot;{Cirrus Logic,Sound Fusion (CS4624)},&quot;
l_string|&quot;{Cirrus Logic,Sound Fusion (CS4630)}}&quot;
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
id|SNDRV_DEFAULT_ENABLE_PNP
suffix:semicolon
multiline_comment|/* Enable this card */
DECL|variable|snd_external_amp
r_static
r_int
id|snd_external_amp
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
l_int|0
)brace
suffix:semicolon
DECL|variable|snd_thinkpad
r_static
r_int
id|snd_thinkpad
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
l_int|0
)brace
suffix:semicolon
macro_line|#ifndef CONFIG_SND_CS46XX_ACCEPT_VALID
DECL|variable|snd_mmap_valid
r_static
r_int
id|snd_mmap_valid
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
l_int|0
)brace
suffix:semicolon
macro_line|#endif
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
l_string|&quot;Index value for the CS46xx soundcard.&quot;
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
l_string|&quot;ID string for the CS46xx soundcard.&quot;
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
l_string|&quot;Enable CS46xx soundcard.&quot;
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
id|snd_external_amp
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
id|snd_external_amp
comma
l_string|&quot;Force to enable external amplifer.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_external_amp
comma
id|SNDRV_ENABLED
l_string|&quot;,&quot;
id|SNDRV_BOOLEAN_FALSE_DESC
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|snd_thinkpad
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
id|snd_thinkpad
comma
l_string|&quot;Force to enable Thinkpad&squot;s CLKRUN control.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_thinkpad
comma
id|SNDRV_ENABLED
l_string|&quot;,&quot;
id|SNDRV_BOOLEAN_FALSE_DESC
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SND_CS46XX_ACCEPT_VALID
id|MODULE_PARM
c_func
(paren
id|snd_mmap_valid
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
id|snd_mmap_valid
comma
l_string|&quot;Support OSS mmap.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_mmap_valid
comma
id|SNDRV_ENABLED
l_string|&quot;,&quot;
id|SNDRV_BOOLEAN_FALSE_DESC
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|snd_cs46xx_ids
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
l_int|0x1013
comma
l_int|0x6001
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* CS4280 */
(brace
l_int|0x1013
comma
l_int|0x6003
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* CS4612 */
(brace
l_int|0x1013
comma
l_int|0x6004
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* CS4615 */
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
id|snd_cs46xx_ids
)paren
suffix:semicolon
DECL|function|snd_card_cs46xx_probe
r_static
r_int
id|__devinit
id|snd_card_cs46xx_probe
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
id|id
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
id|cs46xx_t
op_star
id|chip
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
id|snd_enable
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs46xx_create
c_func
(paren
id|card
comma
id|pci
comma
id|snd_external_amp
(braket
id|dev
)braket
comma
id|snd_thinkpad
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
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SND_CS46XX_ACCEPT_VALID
id|chip-&gt;accept_valid
op_assign
l_int|1
suffix:semicolon
macro_line|#else
id|chip-&gt;accept_valid
op_assign
id|snd_mmap_valid
(braket
id|dev
)braket
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_cs46xx_pcm
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
id|snd_cs46xx_mixer
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
id|snd_cs46xx_midi
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
id|snd_cs46xx_gameport
c_func
(paren
id|chip
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;CS46xx&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Sound Fusion CS46xx&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s at 0x%lx/0x%lx, irq %i&quot;
comma
id|card-&gt;shortname
comma
id|chip-&gt;ba0_addr
comma
id|chip-&gt;ba1_addr
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
id|chip
)paren
suffix:semicolon
id|dev
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
macro_line|#ifndef PCI_OLD_SUSPEND
DECL|function|snd_card_cs46xx_suspend
r_static
r_int
id|snd_card_cs46xx_suspend
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
id|u32
id|state
)paren
(brace
id|cs46xx_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs46xx_t
comma
id|pci_get_drvdata
c_func
(paren
id|pci
)paren
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_cs46xx_suspend
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_cs46xx_resume
r_static
r_int
id|snd_card_cs46xx_resume
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
id|cs46xx_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs46xx_t
comma
id|pci_get_drvdata
c_func
(paren
id|pci
)paren
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|snd_cs46xx_resume
c_func
(paren
id|chip
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else
DECL|function|snd_card_cs46xx_suspend
r_static
r_void
id|snd_card_cs46xx_suspend
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
id|cs46xx_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs46xx_t
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
id|snd_cs46xx_suspend
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
DECL|function|snd_card_cs46xx_resume
r_static
r_void
id|snd_card_cs46xx_resume
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
id|cs46xx_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs46xx_t
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
id|snd_cs46xx_resume
c_func
(paren
id|chip
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
DECL|function|snd_card_cs46xx_remove
r_static
r_void
id|__devexit
id|snd_card_cs46xx_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
id|cs46xx_t
op_star
id|chip
op_assign
id|snd_magic_cast
c_func
(paren
id|cs46xx_t
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
id|chip
)paren
id|snd_card_free
c_func
(paren
id|chip-&gt;card
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
id|name
suffix:colon
l_string|&quot;Sound Fusion CS46xx&quot;
comma
id|id_table
suffix:colon
id|snd_cs46xx_ids
comma
id|probe
suffix:colon
id|snd_card_cs46xx_probe
comma
id|remove
suffix:colon
id|__devexit_p
c_func
(paren
id|snd_card_cs46xx_remove
)paren
comma
macro_line|#ifdef CONFIG_PM
id|suspend
suffix:colon
id|snd_card_cs46xx_suspend
comma
id|resume
suffix:colon
id|snd_card_cs46xx_resume
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|function|alsa_card_cs46xx_init
r_static
r_int
id|__init
id|alsa_card_cs46xx_init
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
l_string|&quot;Sound Fusion CS46xx soundcard not found or device busy&bslash;n&quot;
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
DECL|function|alsa_card_cs46xx_exit
r_static
r_void
id|__exit
id|alsa_card_cs46xx_exit
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
id|alsa_card_cs46xx_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_cs46xx_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-cs46xx=snd_enable,snd_index,snd_id */
DECL|function|alsa_card_cs46xx_setup
r_static
r_int
id|__init
id|alsa_card_cs46xx_setup
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
l_string|&quot;snd-cs46xx=&quot;
comma
id|alsa_card_cs46xx_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
