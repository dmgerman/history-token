multiline_comment|/*&n; *  Advanced Linux Sound Architecture&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#ifdef CONFIG_SND_OSSEMUL
macro_line|#if !defined(CONFIG_SOUND) &amp;&amp; !defined(CONFIG_SOUND_MODULE)
macro_line|#error &quot;Enable the OSS soundcore multiplexer (CONFIG_SOUND) in the kernel.&quot;
macro_line|#endif
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/minors.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#include &lt;linux/sound.h&gt;
DECL|macro|SNDRV_OS_MINORS
mdefine_line|#define SNDRV_OS_MINORS&t;&t;256
DECL|variable|snd_oss_minors_hash
r_static
r_struct
id|list_head
id|snd_oss_minors_hash
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|sound_oss_mutex
)paren
suffix:semicolon
DECL|function|snd_oss_minor_search
r_static
id|snd_minor_t
op_star
id|snd_oss_minor_search
c_func
(paren
r_int
id|minor
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|snd_minor_t
op_star
id|mptr
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|snd_oss_minors_hash
(braket
id|SNDRV_MINOR_OSS_CARD
c_func
(paren
id|minor
)paren
)braket
)paren
(brace
id|mptr
op_assign
id|list_entry
c_func
(paren
id|list
comma
id|snd_minor_t
comma
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mptr-&gt;number
op_eq
id|minor
)paren
r_return
id|mptr
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_oss_kernel_minor
r_static
r_int
id|snd_oss_kernel_minor
c_func
(paren
r_int
id|type
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|dev
)paren
(brace
r_int
id|minor
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|SNDRV_OSS_DEVICE_TYPE_MIXER
suffix:colon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
op_logical_and
id|dev
op_le
l_int|1
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|minor
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|card-&gt;number
comma
(paren
id|dev
ques
c_cond
id|SNDRV_MINOR_OSS_MIXER1
suffix:colon
id|SNDRV_MINOR_OSS_MIXER
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_OSS_DEVICE_TYPE_SEQUENCER
suffix:colon
id|minor
op_assign
id|SNDRV_MINOR_OSS_SEQUENCER
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_OSS_DEVICE_TYPE_MUSIC
suffix:colon
id|minor
op_assign
id|SNDRV_MINOR_OSS_MUSIC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_OSS_DEVICE_TYPE_PCM
suffix:colon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
op_logical_and
id|dev
op_le
l_int|1
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|minor
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|card-&gt;number
comma
(paren
id|dev
ques
c_cond
id|SNDRV_MINOR_OSS_PCM1
suffix:colon
id|SNDRV_MINOR_OSS_PCM
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_OSS_DEVICE_TYPE_MIDI
suffix:colon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
op_logical_and
id|dev
op_le
l_int|1
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|minor
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|card-&gt;number
comma
(paren
id|dev
ques
c_cond
id|SNDRV_MINOR_OSS_MIDI1
suffix:colon
id|SNDRV_MINOR_OSS_MIDI
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_OSS_DEVICE_TYPE_DMFM
suffix:colon
id|minor
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|card-&gt;number
comma
id|SNDRV_MINOR_OSS_DMFM
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_OSS_DEVICE_TYPE_SNDSTAT
suffix:colon
id|minor
op_assign
id|SNDRV_MINOR_OSS_SNDSTAT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|snd_assert
c_func
(paren
id|minor
op_ge
l_int|0
op_logical_and
id|minor
OL
id|SNDRV_OS_MINORS
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
r_return
id|minor
suffix:semicolon
)brace
DECL|function|snd_register_oss_device
r_int
id|snd_register_oss_device
c_func
(paren
r_int
id|type
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|dev
comma
id|snd_minor_t
op_star
id|reg
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_int
id|minor
op_assign
id|snd_oss_kernel_minor
c_func
(paren
id|type
comma
id|card
comma
id|dev
)paren
suffix:semicolon
r_int
id|minor_unit
suffix:semicolon
id|snd_minor_t
op_star
id|preg
suffix:semicolon
r_int
id|cidx
op_assign
id|SNDRV_MINOR_OSS_CARD
c_func
(paren
id|minor
)paren
suffix:semicolon
r_int
id|track2
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|register1
op_assign
op_minus
l_int|1
comma
id|register2
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
r_return
id|minor
suffix:semicolon
id|preg
op_assign
(paren
id|snd_minor_t
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|snd_minor_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|preg
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|preg
op_assign
op_star
id|reg
suffix:semicolon
id|preg-&gt;number
op_assign
id|minor
suffix:semicolon
id|preg-&gt;device
op_assign
id|dev
suffix:semicolon
id|preg-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|preg-&gt;list
comma
op_amp
id|snd_oss_minors_hash
(braket
id|cidx
)braket
)paren
suffix:semicolon
id|minor_unit
op_assign
id|SNDRV_MINOR_OSS_DEVICE
c_func
(paren
id|minor
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|minor_unit
)paren
(brace
r_case
id|SNDRV_MINOR_OSS_PCM
suffix:colon
id|track2
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|cidx
comma
id|SNDRV_MINOR_OSS_AUDIO
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_MINOR_OSS_MIDI
suffix:colon
id|track2
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|cidx
comma
id|SNDRV_MINOR_OSS_DMMIDI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_MINOR_OSS_MIDI1
suffix:colon
id|track2
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|cidx
comma
id|SNDRV_MINOR_OSS_DMMIDI1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|register1
op_assign
id|register_sound_special
c_func
(paren
id|reg-&gt;f_ops
comma
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register1
op_ne
id|minor
)paren
r_goto
id|__end
suffix:semicolon
r_if
c_cond
(paren
id|track2
op_ge
l_int|0
)paren
(brace
id|register2
op_assign
id|register_sound_special
c_func
(paren
id|reg-&gt;f_ops
comma
id|track2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register2
op_ne
id|track2
)paren
r_goto
id|__end
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|__end
suffix:colon
r_if
c_cond
(paren
id|register2
op_ge
l_int|0
)paren
id|unregister_sound_special
c_func
(paren
id|register2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register1
op_ge
l_int|0
)paren
id|unregister_sound_special
c_func
(paren
id|register1
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|preg-&gt;list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|preg
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
DECL|function|snd_unregister_oss_device
r_int
id|snd_unregister_oss_device
c_func
(paren
r_int
id|type
comma
id|snd_card_t
op_star
id|card
comma
r_int
id|dev
)paren
(brace
r_int
id|minor
op_assign
id|snd_oss_kernel_minor
c_func
(paren
id|type
comma
id|card
comma
id|dev
)paren
suffix:semicolon
r_int
id|cidx
op_assign
id|SNDRV_MINOR_OSS_CARD
c_func
(paren
id|minor
)paren
suffix:semicolon
r_int
id|track2
op_assign
op_minus
l_int|1
suffix:semicolon
id|snd_minor_t
op_star
id|mptr
suffix:semicolon
r_if
c_cond
(paren
id|minor
OL
l_int|0
)paren
r_return
id|minor
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
id|mptr
op_assign
id|snd_oss_minor_search
c_func
(paren
id|minor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mptr
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|unregister_sound_special
c_func
(paren
id|minor
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|SNDRV_MINOR_OSS_DEVICE
c_func
(paren
id|minor
)paren
)paren
(brace
r_case
id|SNDRV_MINOR_OSS_PCM
suffix:colon
id|track2
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|cidx
comma
id|SNDRV_MINOR_OSS_AUDIO
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_MINOR_OSS_MIDI
suffix:colon
id|track2
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|cidx
comma
id|SNDRV_MINOR_OSS_DMMIDI
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_MINOR_OSS_MIDI1
suffix:colon
id|track2
op_assign
id|SNDRV_MINOR_OSS
c_func
(paren
id|cidx
comma
id|SNDRV_MINOR_OSS_DMMIDI1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|track2
op_ge
l_int|0
)paren
id|unregister_sound_special
c_func
(paren
id|track2
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|mptr-&gt;list
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mptr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  INFO PART&n; */
DECL|variable|snd_minor_info_oss_entry
r_static
id|snd_info_entry_t
op_star
id|snd_minor_info_oss_entry
op_assign
l_int|NULL
suffix:semicolon
DECL|function|snd_minor_info_oss_read
r_static
r_void
id|snd_minor_info_oss_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
r_int
id|card
comma
id|dev
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
id|snd_minor_t
op_star
id|mptr
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
r_for
c_loop
(paren
id|card
op_assign
l_int|0
suffix:semicolon
id|card
OL
id|SNDRV_CARDS
suffix:semicolon
id|card
op_increment
)paren
(brace
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|snd_oss_minors_hash
(braket
id|card
)braket
)paren
(brace
id|mptr
op_assign
id|list_entry
c_func
(paren
id|list
comma
id|snd_minor_t
comma
id|list
)paren
suffix:semicolon
id|dev
op_assign
id|SNDRV_MINOR_OSS_DEVICE
c_func
(paren
id|mptr-&gt;number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ne
id|SNDRV_MINOR_OSS_SNDSTAT
op_logical_and
id|dev
op_ne
id|SNDRV_MINOR_OSS_SEQUENCER
op_logical_and
id|dev
op_ne
id|SNDRV_MINOR_OSS_MUSIC
)paren
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%3i: [%i-%2i]: %s&bslash;n&quot;
comma
id|mptr-&gt;number
comma
id|card
comma
id|dev
comma
id|mptr-&gt;comment
)paren
suffix:semicolon
r_else
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%3i:       : %s&bslash;n&quot;
comma
id|mptr-&gt;number
comma
id|mptr-&gt;comment
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|sound_oss_mutex
)paren
suffix:semicolon
)brace
DECL|function|snd_minor_info_oss_init
r_int
id|__init
id|snd_minor_info_oss_init
c_func
(paren
r_void
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
id|entry
op_assign
id|snd_info_create_module_entry
c_func
(paren
id|THIS_MODULE
comma
l_string|&quot;devices&quot;
comma
id|snd_oss_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|snd_minor_info_oss_read
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_register
c_func
(paren
id|entry
)paren
OL
l_int|0
)paren
(brace
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|snd_minor_info_oss_entry
op_assign
id|entry
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_minor_info_oss_done
r_int
id|__exit
id|snd_minor_info_oss_done
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|snd_minor_info_oss_entry
)paren
id|snd_info_unregister
c_func
(paren
id|snd_minor_info_oss_entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_oss_init_module
r_int
id|__init
id|snd_oss_init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|card
suffix:semicolon
r_for
c_loop
(paren
id|card
op_assign
l_int|0
suffix:semicolon
id|card
OL
id|SNDRV_CARDS
suffix:semicolon
id|card
op_increment
)paren
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|snd_oss_minors_hash
(braket
id|card
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_oss_cleanup_module
r_void
id|snd_oss_cleanup_module
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_SND_OSSEMUL */
eof
