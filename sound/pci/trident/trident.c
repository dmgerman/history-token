multiline_comment|/*&n; *  Driver for Trident 4DWave DX/NX &amp; SiS SI7018 Audio PCI soundcard&n; *&n; *  Driver was originated by Trident &lt;audio@tridentmicro.com&gt;&n; *  &t;&t;&t;     Fri Feb 19 15:55:28 MST 1999&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/trident.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;, &lt;audio@tridentmicro.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Trident 4D-WaveDX/NX &amp; SiS SI7018&quot;
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
l_string|&quot;{{Trident,4DWave DX},&quot;
l_string|&quot;{Trident,4DWave NX},&quot;
l_string|&quot;{SiS,SI7018 PCI Audio},&quot;
l_string|&quot;{Best Union,Miss Melody 4DWave PCI},&quot;
l_string|&quot;{HIS,4DWave PCI},&quot;
l_string|&quot;{Warpspeed,ONSpeed 4DWave PCI},&quot;
l_string|&quot;{Aztech Systems,PCI 64-Q3D},&quot;
l_string|&quot;{Addonics,SV 750},&quot;
l_string|&quot;{CHIC,True Sound 4Dwave},&quot;
l_string|&quot;{Shark,Predator4D-PCI},&quot;
l_string|&quot;{Jaton,SonicWave 4D},&quot;
l_string|&quot;{Hoontech,SoundTrack Digital 4DWave NX}}&quot;
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
l_int|32
)brace
suffix:semicolon
DECL|variable|wavetable_size
r_static
r_int
id|wavetable_size
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
l_int|8192
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
l_string|&quot;Index value for Trident 4DWave PCI soundcard.&quot;
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
l_string|&quot;ID string for Trident 4DWave PCI soundcard.&quot;
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
l_string|&quot;Enable Trident 4DWave PCI soundcard.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|pcm_channels
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
id|pcm_channels
comma
l_string|&quot;Number of hardware channels assigned for PCM.&quot;
)paren
suffix:semicolon
id|module_param_array
c_func
(paren
id|wavetable_size
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
id|wavetable_size
comma
l_string|&quot;Maximum memory size in kB for wavetable synth.&quot;
)paren
suffix:semicolon
DECL|variable|snd_trident_ids
r_static
r_struct
id|pci_device_id
id|snd_trident_ids
(braket
)braket
op_assign
(brace
(brace
l_int|0x1023
comma
l_int|0x2000
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
multiline_comment|/* Trident 4DWave DX PCI Audio */
(brace
l_int|0x1023
comma
l_int|0x2001
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
multiline_comment|/* Trident 4DWave NX PCI Audio */
(brace
l_int|0x1039
comma
l_int|0x7018
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
multiline_comment|/* SiS SI7018 PCI Audio */
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
id|snd_trident_ids
)paren
suffix:semicolon
DECL|function|snd_trident_probe
r_static
r_int
id|__devinit
id|snd_trident_probe
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
id|trident_t
op_star
id|trident
suffix:semicolon
r_const
r_char
op_star
id|str
suffix:semicolon
r_int
id|err
comma
id|pcm_dev
op_assign
l_int|0
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_trident_create
c_func
(paren
id|card
comma
id|pci
comma
id|pcm_channels
(braket
id|dev
)braket
comma
(paren
(paren
id|pci-&gt;vendor
op_lshift
l_int|16
)paren
op_or
id|pci-&gt;device
)paren
op_eq
id|TRIDENT_DEVICE_ID_SI7018
ques
c_cond
l_int|1
suffix:colon
l_int|2
comma
id|wavetable_size
(braket
id|dev
)braket
comma
op_amp
id|trident
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
r_switch
c_cond
(paren
id|trident-&gt;device
)paren
(brace
r_case
id|TRIDENT_DEVICE_ID_DX
suffix:colon
id|str
op_assign
l_string|&quot;TRID4DWAVEDX&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRIDENT_DEVICE_ID_NX
suffix:colon
id|str
op_assign
l_string|&quot;TRID4DWAVENX&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TRIDENT_DEVICE_ID_SI7018
suffix:colon
id|str
op_assign
l_string|&quot;SI7018&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|str
op_assign
l_string|&quot;Unknown&quot;
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trident-&gt;device
op_eq
id|TRIDENT_DEVICE_ID_SI7018
)paren
(brace
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;SiS &quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Trident &quot;
)paren
suffix:semicolon
)brace
id|strcat
c_func
(paren
id|card-&gt;shortname
comma
id|card-&gt;driver
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s PCI Audio at 0x%lx, irq %d&quot;
comma
id|card-&gt;shortname
comma
id|trident-&gt;port
comma
id|trident-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_trident_pcm
c_func
(paren
id|trident
comma
id|pcm_dev
op_increment
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
r_switch
c_cond
(paren
id|trident-&gt;device
)paren
(brace
r_case
id|TRIDENT_DEVICE_ID_DX
suffix:colon
r_case
id|TRIDENT_DEVICE_ID_NX
suffix:colon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_trident_foldback_pcm
c_func
(paren
id|trident
comma
id|pcm_dev
op_increment
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
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|trident-&gt;device
op_eq
id|TRIDENT_DEVICE_ID_NX
op_logical_or
id|trident-&gt;device
op_eq
id|TRIDENT_DEVICE_ID_SI7018
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_trident_spdif_pcm
c_func
(paren
id|trident
comma
id|pcm_dev
op_increment
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
id|snd_mpu401_uart_new
c_func
(paren
id|card
comma
l_int|0
comma
id|MPU401_HW_TRID4DWAVE
comma
id|trident-&gt;midi_port
comma
l_int|1
comma
id|trident-&gt;irq
comma
l_int|0
comma
op_amp
id|trident-&gt;rmidi
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
macro_line|#if defined(CONFIG_SND_SEQUENCER) || (defined(MODULE) &amp;&amp; defined(CONFIG_SND_SEQUENCER_MODULE))
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_trident_attach_synthesizer
c_func
(paren
id|trident
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
id|snd_trident_gameport
c_func
(paren
id|trident
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
DECL|function|snd_trident_remove
r_static
r_void
id|__devexit
id|snd_trident_remove
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
l_string|&quot;Trident4DWaveAudio&quot;
comma
dot
id|id_table
op_assign
id|snd_trident_ids
comma
dot
id|probe
op_assign
id|snd_trident_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_trident_remove
)paren
comma
id|SND_PCI_PM_CALLBACKS
)brace
suffix:semicolon
DECL|function|alsa_card_trident_init
r_static
r_int
id|__init
id|alsa_card_trident_init
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
DECL|function|alsa_card_trident_exit
r_static
r_void
id|__exit
id|alsa_card_trident_exit
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
id|alsa_card_trident_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_trident_exit
)paren
eof
