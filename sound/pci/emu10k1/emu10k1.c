multiline_comment|/*&n; *  The driver for the EMU10K1 (SB Live!) based soundcards&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/emu10k1.h&gt;
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
l_string|&quot;EMU10K1&quot;
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
l_string|&quot;{{Creative Labs,SB Live!/PCI512/E-mu APS},&quot;
l_string|&quot;{Creative Labs,SB Audigy}}&quot;
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SND_SEQUENCER) || (defined(MODULE) &amp;&amp; defined(CONFIG_SND_SEQUENCER_MODULE))
DECL|macro|ENABLE_SYNTH
mdefine_line|#define ENABLE_SYNTH
macro_line|#include &lt;sound/emu10k1_synth.h&gt;
macro_line|#endif
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
DECL|variable|extin
r_static
r_int
id|extin
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
DECL|variable|extout
r_static
r_int
id|extout
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
DECL|variable|seq_ports
r_static
r_int
id|seq_ports
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
l_int|4
)brace
suffix:semicolon
DECL|variable|max_synth_voices
r_static
r_int
id|max_synth_voices
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
l_int|64
)brace
suffix:semicolon
DECL|variable|max_buffer_size
r_static
r_int
id|max_buffer_size
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
l_int|128
)brace
suffix:semicolon
DECL|variable|enable_ir
r_static
r_int
id|enable_ir
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
l_string|&quot;Index value for the EMU10K1 soundcard.&quot;
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
l_string|&quot;ID string for the EMU10K1 soundcard.&quot;
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
l_string|&quot;Enable the EMU10K1 soundcard.&quot;
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
id|extin
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
id|extin
comma
l_string|&quot;Available external inputs for FX8010. Zero=default.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|extin
comma
id|SNDRV_ENABLED
l_string|&quot;allows:{{0,0x0ffff}},base:16&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|extout
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
id|extout
comma
l_string|&quot;Available external outputs for FX8010. Zero=default.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|extout
comma
id|SNDRV_ENABLED
l_string|&quot;allows:{{0,0x0ffff}},base:16&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|seq_ports
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
id|seq_ports
comma
l_string|&quot;Allocated sequencer ports for internal synthesizer.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|seq_ports
comma
id|SNDRV_ENABLED
l_string|&quot;allows:{{0,32}}&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|max_synth_voices
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
id|max_synth_voices
comma
l_string|&quot;Maximum number of voices for WaveTable.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|max_synth_voices
comma
id|SNDRV_ENABLED
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|max_buffer_size
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
id|max_buffer_size
comma
l_string|&quot;Maximum sample buffer size in MB.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|max_buffer_size
comma
id|SNDRV_ENABLED
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|enable_ir
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
id|enable_ir
comma
l_string|&quot;Enable IR.&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|enable_ir
comma
id|SNDRV_ENABLE_DESC
)paren
suffix:semicolon
DECL|variable|snd_emu10k1_ids
r_static
r_struct
id|pci_device_id
id|snd_emu10k1_ids
(braket
)braket
op_assign
(brace
(brace
l_int|0x1102
comma
l_int|0x0002
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
)brace
comma
multiline_comment|/* EMU10K1 */
(brace
l_int|0x1102
comma
l_int|0x0006
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
)brace
comma
multiline_comment|/* Dell OEM version (EMU10K1) */
(brace
l_int|0x1102
comma
l_int|0x0004
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* Audigy */
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
id|snd_emu10k1_ids
)paren
suffix:semicolon
DECL|function|snd_card_emu10k1_probe
r_static
r_int
id|__devinit
id|snd_card_emu10k1_probe
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
id|emu10k1_t
op_star
id|emu
suffix:semicolon
macro_line|#ifdef ENABLE_SYNTH
id|snd_seq_device_t
op_star
id|wave
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|max_buffer_size
(braket
id|dev
)braket
OL
l_int|32
)paren
id|max_buffer_size
(braket
id|dev
)braket
op_assign
l_int|32
suffix:semicolon
r_else
r_if
c_cond
(paren
id|max_buffer_size
(braket
id|dev
)braket
OG
l_int|1024
)paren
id|max_buffer_size
(braket
id|dev
)braket
op_assign
l_int|1024
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_emu10k1_create
c_func
(paren
id|card
comma
id|pci
comma
id|extin
(braket
id|dev
)braket
comma
id|extout
(braket
id|dev
)braket
comma
(paren
r_int
)paren
id|max_buffer_size
(braket
id|dev
)braket
op_star
l_int|1024
op_star
l_int|1024
comma
id|enable_ir
(braket
id|dev
)braket
comma
op_amp
id|emu
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
id|snd_emu10k1_pcm
c_func
(paren
id|emu
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
id|snd_emu10k1_pcm_mic
c_func
(paren
id|emu
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_emu10k1_pcm_efx
c_func
(paren
id|emu
comma
l_int|2
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
id|snd_emu10k1_fx8010_pcm
c_func
(paren
id|emu
comma
l_int|3
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
id|snd_emu10k1_mixer
c_func
(paren
id|emu
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
id|emu-&gt;audigy
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_emu10k1_audigy_midi
c_func
(paren
id|emu
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
r_else
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_emu10k1_midi
c_func
(paren
id|emu
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
id|snd_emu10k1_fx8010_new
c_func
(paren
id|emu
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
macro_line|#ifdef ENABLE_SYNTH
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
id|SNDRV_SEQ_DEV_ID_EMU10K1_SYNTH
comma
r_sizeof
(paren
id|snd_emu10k1_synth_arg_t
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
l_string|&quot;can&squot;t initialize Emu10k1 wavetable synth&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_emu10k1_synth_arg_t
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
l_string|&quot;Emu-10k1 Synth&quot;
)paren
suffix:semicolon
id|arg-&gt;hwptr
op_assign
id|emu
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
r_if
c_cond
(paren
id|emu-&gt;audigy
op_logical_and
(paren
id|emu-&gt;revision
op_eq
l_int|4
)paren
)paren
(brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;Audigy2&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Sound Blaster Audigy2&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|emu-&gt;audigy
)paren
(brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;Audigy&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Sound Blaster Audigy&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|emu-&gt;APS
)paren
(brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;E-mu APS&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;E-mu APS&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;EMU10K1&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;Sound Blaster Live!&quot;
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;%s (rev.%d) at 0x%lx, irq %i&quot;
comma
id|card-&gt;shortname
comma
id|emu-&gt;revision
comma
id|emu-&gt;port
comma
id|emu-&gt;irq
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
DECL|function|snd_card_emu10k1_remove
r_static
r_void
id|__devexit
id|snd_card_emu10k1_remove
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
l_string|&quot;EMU10K1_Audigy&quot;
comma
dot
id|id_table
op_assign
id|snd_emu10k1_ids
comma
dot
id|probe
op_assign
id|snd_card_emu10k1_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|snd_card_emu10k1_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|alsa_card_emu10k1_init
r_static
r_int
id|__init
id|alsa_card_emu10k1_init
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
l_string|&quot;EMU10K1/Audigy soundcard not found or device busy&bslash;n&quot;
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
DECL|function|alsa_card_emu10k1_exit
r_static
r_void
id|__exit
id|alsa_card_emu10k1_exit
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
id|alsa_card_emu10k1_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_emu10k1_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-emu10k1=enable,index,id,&n;&t;&t;&t;  seq_ports,max_synth_voices */
DECL|function|alsa_card_emu10k1_setup
r_static
r_int
id|__init
id|alsa_card_emu10k1_setup
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
op_amp
id|seq_ports
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
id|max_synth_voices
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
l_string|&quot;snd-emu10k1=&quot;
comma
id|alsa_card_emu10k1_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
