multiline_comment|/*&n; *  Dummy soundcard for virtual rawmidi devices&n; *&n; *  Copyright (c) 2000 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
multiline_comment|/*&n; * VIRTUAL RAW MIDI DEVICE CARDS&n; *&n; * This dummy card contains up to 4 virtual rawmidi devices.&n; * They are not real rawmidi devices but just associated with sequencer&n; * clients, so that any input/output sources can be connected as a raw&n; * MIDI device arbitrary.&n; * Also, multiple access is allowed to a single rawmidi device.&n; *&n; * Typical usage is like following:&n; * - Load snd-virmidi module.&n; *&t;# modprobe snd-virmidi snd_index=2&n; *   Then, sequencer clients 72:0 to 75:0 will be created, which are&n; *   mapped from /dev/snd/midiC1D0 to /dev/snd/midiC1D3, respectively.&n; *&n; * - Connect input/output via aconnect.&n; *&t;% aconnect 64:0 72:0&t;# keyboard input redirection 64:0 -&gt; 72:0&n; *&t;% aconnect 72:0 65:0&t;# output device redirection 72:0 -&gt; 65:0&n; *&n; * - Run application using a midi device (eg. /dev/snd/midiC1D0)&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/seq_kernel.h&gt;
macro_line|#include &lt;sound/seq_virmidi.h&gt;
DECL|macro|SNDRV_GET_ID
mdefine_line|#define SNDRV_GET_ID
macro_line|#include &lt;sound/initval.h&gt;
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Dummy soundcard for virtual rawmidi devices&quot;
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
l_string|&quot;{{ALSA,Virtual rawmidi device}}&quot;
)paren
suffix:semicolon
DECL|macro|MAX_MIDI_DEVICES
mdefine_line|#define MAX_MIDI_DEVICES&t;8
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
(brace
l_int|1
comma
(braket
l_int|1
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
DECL|variable|snd_midi_devs
r_static
r_int
id|snd_midi_devs
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
l_string|&quot;Index value for virmidi soundcard.&quot;
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
l_string|&quot;ID string for virmidi soundcard.&quot;
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
l_string|&quot;Enable this soundcard.&quot;
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
id|snd_midi_devs
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
id|snd_midi_devs
comma
l_string|&quot;MIDI devices # (1-8)&quot;
)paren
suffix:semicolon
id|MODULE_PARM_SYNTAX
c_func
(paren
id|snd_midi_devs
comma
id|SNDRV_ENABLED
l_string|&quot;,allows:{{1,8}}&quot;
)paren
suffix:semicolon
DECL|struct|snd_card_virmidi
r_typedef
r_struct
id|snd_card_virmidi
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|midi
id|snd_rawmidi_t
op_star
id|midi
(braket
id|MAX_MIDI_DEVICES
)braket
suffix:semicolon
DECL|typedef|snd_card_virmidi_t
)brace
id|snd_card_virmidi_t
suffix:semicolon
DECL|variable|snd_virmidi_cards
r_static
id|snd_card_t
op_star
id|snd_virmidi_cards
(braket
id|SNDRV_CARDS
)braket
op_assign
id|SNDRV_DEFAULT_PTR
suffix:semicolon
DECL|function|snd_card_virmidi_probe
r_static
r_int
id|__init
id|snd_card_virmidi_probe
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
id|snd_card_virmidi
op_star
id|vmidi
suffix:semicolon
r_int
id|idx
comma
id|err
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
r_return
op_minus
id|ENODEV
suffix:semicolon
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
id|snd_card_virmidi
)paren
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
id|vmidi
op_assign
(paren
r_struct
id|snd_card_virmidi
op_star
)paren
id|card-&gt;private_data
suffix:semicolon
id|vmidi-&gt;card
op_assign
id|card
suffix:semicolon
r_if
c_cond
(paren
id|snd_midi_devs
(braket
id|dev
)braket
OG
id|MAX_MIDI_DEVICES
)paren
(brace
id|snd_printk
c_func
(paren
l_string|&quot;too much midi devices for virmidi %d: force to use %d&bslash;n&quot;
comma
id|dev
comma
id|MAX_MIDI_DEVICES
)paren
suffix:semicolon
id|snd_midi_devs
(braket
id|dev
)braket
op_assign
id|MAX_MIDI_DEVICES
suffix:semicolon
)brace
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|snd_midi_devs
(braket
id|dev
)braket
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|snd_rawmidi_t
op_star
id|rmidi
suffix:semicolon
id|snd_virmidi_dev_t
op_star
id|rdev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_virmidi_new
c_func
(paren
id|card
comma
id|idx
comma
op_amp
id|rmidi
)paren
)paren
OL
l_int|0
)paren
r_goto
id|__nodev
suffix:semicolon
id|rdev
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_virmidi_dev_t
comma
id|rmidi-&gt;private_data
comma
r_continue
)paren
suffix:semicolon
id|vmidi-&gt;midi
(braket
id|idx
)braket
op_assign
id|rmidi
suffix:semicolon
id|strcpy
c_func
(paren
id|rmidi-&gt;name
comma
l_string|&quot;Virtual Raw MIDI&quot;
)paren
suffix:semicolon
id|rdev-&gt;seq_mode
op_assign
id|SNDRV_VIRMIDI_SEQ_DISPATCH
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|card-&gt;driver
comma
l_string|&quot;VirMIDI&quot;
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;shortname
comma
l_string|&quot;VirMIDI&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;longname
comma
l_string|&quot;Virtual MIDI Card %i&quot;
comma
id|dev
op_plus
l_int|1
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
op_eq
l_int|0
)paren
(brace
id|snd_virmidi_cards
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
id|__nodev
suffix:colon
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
DECL|function|alsa_card_virmidi_init
r_static
r_int
id|__init
id|alsa_card_virmidi_init
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
id|snd_card_virmidi_probe
c_func
(paren
id|dev
)paren
OL
l_int|0
)paren
(brace
macro_line|#ifdef MODULE
id|snd_printk
c_func
(paren
l_string|&quot;Card-VirMIDI #%i not found or device busy&bslash;n&quot;
comma
id|dev
op_plus
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
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
id|snd_printk
c_func
(paren
l_string|&quot;Card-VirMIDI soundcard not found or device busy&bslash;n&quot;
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
DECL|function|alsa_card_virmidi_exit
r_static
r_void
id|__exit
id|alsa_card_virmidi_exit
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
id|snd_virmidi_cards
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_card_virmidi_init
)paren
id|module_exit
c_func
(paren
id|alsa_card_virmidi_exit
)paren
macro_line|#ifndef MODULE
multiline_comment|/* format is: snd-virmidi=snd_enable,snd_index,snd_id,snd_midi_devs */
DECL|function|alsa_card_virmidi_setup
r_static
r_int
id|__init
id|alsa_card_virmidi_setup
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
op_amp
id|snd_midi_devs
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
l_string|&quot;snd-virmidi=&quot;
comma
id|alsa_card_virmidi_setup
)paren
suffix:semicolon
macro_line|#endif /* ifndef MODULE */
eof
