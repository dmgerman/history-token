multiline_comment|/*&n; *  Advanced Linux Sound Architecture&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/minors.h&gt;
macro_line|#include &lt;sound/info.h&gt;
macro_line|#include &lt;sound/version.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
DECL|macro|SNDRV_OS_MINORS
mdefine_line|#define SNDRV_OS_MINORS 256
DECL|variable|major
r_static
r_int
id|major
op_assign
id|CONFIG_SND_MAJOR
suffix:semicolon
DECL|variable|snd_major
r_int
id|snd_major
suffix:semicolon
DECL|variable|cards_limit
r_static
r_int
id|cards_limit
op_assign
l_int|1
suffix:semicolon
DECL|variable|device_mode
r_static
r_int
id|device_mode
op_assign
id|S_IFCHR
op_or
id|S_IRUGO
op_or
id|S_IWUGO
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Advanced Linux Sound Architecture driver for soundcards.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|major
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|major
comma
l_string|&quot;Major # for sound driver.&quot;
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|cards_limit
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|cards_limit
comma
l_string|&quot;Count of auto-loadable soundcards.&quot;
)paren
suffix:semicolon
DECL|variable|CONFIG_SND_MAJOR
id|MODULE_ALIAS_CHARDEV_MAJOR
c_func
(paren
id|CONFIG_SND_MAJOR
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEVFS_FS
id|module_param
c_func
(paren
id|device_mode
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|device_mode
comma
l_string|&quot;Device file permission mask for devfs.&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|CONFIG_SND_MAJOR
id|MODULE_ALIAS_CHARDEV_MAJOR
c_func
(paren
id|CONFIG_SND_MAJOR
)paren
suffix:semicolon
multiline_comment|/* this one holds the actual max. card number currently available.&n; * as default, it&squot;s identical with cards_limit option.  when more&n; * modules are loaded manually, this limit number increases, too.&n; */
DECL|variable|snd_ecards_limit
r_int
id|snd_ecards_limit
suffix:semicolon
DECL|variable|snd_minors_hash
r_static
r_struct
id|list_head
id|snd_minors_hash
(braket
id|SNDRV_CARDS
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|sound_mutex
)paren
suffix:semicolon
r_extern
r_struct
id|class_simple
op_star
id|sound_class
suffix:semicolon
macro_line|#ifdef CONFIG_KMOD
multiline_comment|/**&n; * snd_request_card - try to load the card module&n; * @card: the card number&n; *&n; * Tries to load the module &quot;snd-card-X&quot; for the given card number&n; * via KMOD.  Returns immediately if already loaded.&n; */
DECL|function|snd_request_card
r_void
id|snd_request_card
c_func
(paren
r_int
id|card
)paren
(brace
r_int
id|locked
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;fs-&gt;root
)paren
r_return
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
id|locked
op_assign
id|snd_cards_lock
op_amp
(paren
l_int|1
op_lshift
id|card
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|locked
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|card
OL
l_int|0
op_logical_or
id|card
op_ge
id|cards_limit
)paren
r_return
suffix:semicolon
id|request_module
c_func
(paren
l_string|&quot;snd-card-%i&quot;
comma
id|card
)paren
suffix:semicolon
)brace
DECL|function|snd_request_other
r_static
r_void
id|snd_request_other
c_func
(paren
r_int
id|minor
)paren
(brace
r_char
op_star
id|str
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;fs-&gt;root
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|minor
)paren
(brace
r_case
id|SNDRV_MINOR_SEQUENCER
suffix:colon
id|str
op_assign
l_string|&quot;snd-seq&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_MINOR_TIMER
suffix:colon
id|str
op_assign
l_string|&quot;snd-timer&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|request_module
c_func
(paren
id|str
)paren
suffix:semicolon
)brace
macro_line|#endif&t;&t;&t;&t;/* request_module support */
DECL|function|snd_minor_search
r_static
id|snd_minor_t
op_star
id|snd_minor_search
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
id|snd_minors_hash
(braket
id|SNDRV_MINOR_CARD
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
DECL|function|snd_open
r_static
r_int
id|snd_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|minor
op_assign
id|iminor
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
id|card
op_assign
id|SNDRV_MINOR_CARD
c_func
(paren
id|minor
)paren
suffix:semicolon
r_int
id|dev
op_assign
id|SNDRV_MINOR_DEVICE
c_func
(paren
id|minor
)paren
suffix:semicolon
id|snd_minor_t
op_star
id|mptr
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|file_operations
op_star
id|old_fops
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ne
id|SNDRV_MINOR_SEQUENCER
op_logical_and
id|dev
op_ne
id|SNDRV_MINOR_TIMER
)paren
(brace
r_if
c_cond
(paren
id|snd_cards
(braket
id|card
)braket
op_eq
l_int|NULL
)paren
(brace
macro_line|#ifdef CONFIG_KMOD
id|snd_request_card
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_cards
(braket
id|card
)braket
op_eq
l_int|NULL
)paren
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_else
(brace
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
(paren
id|mptr
op_assign
id|snd_minor_search
c_func
(paren
id|minor
)paren
)paren
op_eq
l_int|NULL
)paren
id|snd_request_other
c_func
(paren
id|minor
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|mptr
op_eq
l_int|NULL
op_logical_and
(paren
id|mptr
op_assign
id|snd_minor_search
c_func
(paren
id|minor
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|old_fops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|mptr-&gt;f_ops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op-&gt;open
)paren
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|fops_put
c_func
(paren
id|file-&gt;f_op
)paren
suffix:semicolon
id|file-&gt;f_op
op_assign
id|fops_get
c_func
(paren
id|old_fops
)paren
suffix:semicolon
)brace
id|fops_put
c_func
(paren
id|old_fops
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|snd_fops
r_static
r_struct
id|file_operations
id|snd_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|snd_open
)brace
suffix:semicolon
DECL|function|snd_kernel_minor
r_static
r_int
id|snd_kernel_minor
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
id|SNDRV_DEVICE_TYPE_SEQUENCER
suffix:colon
r_case
id|SNDRV_DEVICE_TYPE_TIMER
suffix:colon
id|minor
op_assign
id|type
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_DEVICE_TYPE_CONTROL
suffix:colon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|minor
op_assign
id|SNDRV_MINOR
c_func
(paren
id|card-&gt;number
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_DEVICE_TYPE_HWDEP
suffix:colon
r_case
id|SNDRV_DEVICE_TYPE_RAWMIDI
suffix:colon
r_case
id|SNDRV_DEVICE_TYPE_PCM_PLAYBACK
suffix:colon
r_case
id|SNDRV_DEVICE_TYPE_PCM_CAPTURE
suffix:colon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
id|minor
op_assign
id|SNDRV_MINOR
c_func
(paren
id|card-&gt;number
comma
id|type
op_plus
id|dev
)paren
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
multiline_comment|/**&n; * snd_register_device - Register the ALSA device file for the card&n; * @type: the device type, SNDRV_DEVICE_TYPE_XXX&n; * @card: the card instance&n; * @dev: the device index&n; * @reg: the snd_minor_t record&n; * @name: the device file name&n; *&n; * Registers an ALSA device file for the given card.&n; * The operators have to be set in reg parameter.&n; *&n; * Retrurns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_register_device
r_int
id|snd_register_device
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
id|snd_kernel_minor
c_func
(paren
id|type
comma
id|card
comma
id|dev
)paren
suffix:semicolon
id|snd_minor_t
op_star
id|preg
suffix:semicolon
r_struct
id|device
op_star
id|device
op_assign
l_int|NULL
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
id|snd_assert
c_func
(paren
id|name
comma
r_return
op_minus
id|EINVAL
)paren
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
op_plus
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
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
id|strcpy
c_func
(paren
id|preg-&gt;name
comma
id|name
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|sound_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_minor_search
c_func
(paren
id|minor
)paren
)paren
(brace
id|up
c_func
(paren
op_amp
id|sound_mutex
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
id|list_add_tail
c_func
(paren
op_amp
id|preg-&gt;list
comma
op_amp
id|snd_minors_hash
(braket
id|SNDRV_MINOR_CARD
c_func
(paren
id|minor
)paren
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|name
comma
l_string|&quot;controlC&quot;
comma
l_int|8
)paren
op_logical_or
id|card-&gt;number
op_ge
id|cards_limit
)paren
(brace
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
comma
id|S_IFCHR
op_or
id|device_mode
comma
l_string|&quot;snd/%s&quot;
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card
)paren
id|device
op_assign
id|card-&gt;dev
suffix:semicolon
id|class_simple_device_add
c_func
(paren
id|sound_class
comma
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
comma
id|device
comma
id|name
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|sound_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * snd_unregister_device - unregister the device on the given card&n; * @type: the device type, SNDRV_DEVICE_TYPE_XXX&n; * @card: the card instance&n; * @dev: the device index&n; *&n; * Unregisters the device file already registered via&n; * snd_register_device().&n; *&n; * Returns zero if sucecessful, or a negative error code on failure&n; */
DECL|function|snd_unregister_device
r_int
id|snd_unregister_device
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
id|snd_kernel_minor
c_func
(paren
id|type
comma
id|card
comma
id|dev
)paren
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
id|sound_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mptr
op_assign
id|snd_minor_search
c_func
(paren
id|minor
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|up
c_func
(paren
op_amp
id|sound_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|mptr-&gt;name
comma
l_string|&quot;controlC&quot;
comma
l_int|8
)paren
op_logical_or
id|card-&gt;number
op_ge
id|cards_limit
)paren
(brace
multiline_comment|/* created in sound.c */
id|devfs_remove
c_func
(paren
l_string|&quot;snd/%s&quot;
comma
id|mptr-&gt;name
)paren
suffix:semicolon
id|class_simple_device_remove
c_func
(paren
id|MKDEV
c_func
(paren
id|major
comma
id|minor
)paren
)paren
suffix:semicolon
)brace
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
id|sound_mutex
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
DECL|variable|snd_minor_info_entry
r_static
id|snd_info_entry_t
op_star
id|snd_minor_info_entry
op_assign
l_int|NULL
suffix:semicolon
DECL|function|snd_minor_info_read
r_static
r_void
id|snd_minor_info_read
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
id|device
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
id|sound_mutex
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
id|snd_minors_hash
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
r_if
c_cond
(paren
id|SNDRV_MINOR_DEVICE
c_func
(paren
id|mptr-&gt;number
)paren
op_ne
id|SNDRV_MINOR_SEQUENCER
)paren
(brace
r_if
c_cond
(paren
(paren
id|device
op_assign
id|mptr-&gt;device
)paren
op_ge
l_int|0
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
id|device
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
l_string|&quot;%3i: [%i]   : %s&bslash;n&quot;
comma
id|mptr-&gt;number
comma
id|card
comma
id|mptr-&gt;comment
)paren
suffix:semicolon
)brace
r_else
(brace
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
)brace
id|up
c_func
(paren
op_amp
id|sound_mutex
)paren
suffix:semicolon
)brace
DECL|function|snd_minor_info_init
r_int
id|__init
id|snd_minor_info_init
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
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
id|entry-&gt;c.text.read_size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|snd_minor_info_read
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
id|snd_minor_info_entry
op_assign
id|entry
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_minor_info_done
r_int
id|__exit
id|snd_minor_info_done
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|snd_minor_info_entry
)paren
id|snd_info_unregister
c_func
(paren
id|snd_minor_info_entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  INIT PART&n; */
DECL|function|alsa_sound_init
r_static
r_int
id|__init
id|alsa_sound_init
c_func
(paren
r_void
)paren
(brace
r_int
id|controlnum
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|card
suffix:semicolon
id|snd_major
op_assign
id|major
suffix:semicolon
id|snd_ecards_limit
op_assign
id|cards_limit
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
id|snd_minors_hash
(braket
id|card
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_oss_init_module
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|devfs_mk_dir
c_func
(paren
l_string|&quot;snd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|major
comma
l_string|&quot;alsa&quot;
comma
op_amp
id|snd_fops
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to register native major device number %d&bslash;n&quot;
comma
id|major
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;snd&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|snd_memory_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_init
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|snd_memory_done
c_func
(paren
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|major
comma
l_string|&quot;alsa&quot;
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;snd&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|snd_info_minor_register
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|controlnum
op_assign
l_int|0
suffix:semicolon
id|controlnum
OL
id|cards_limit
suffix:semicolon
id|controlnum
op_increment
)paren
(brace
id|devfs_mk_cdev
c_func
(paren
id|MKDEV
c_func
(paren
id|major
comma
id|controlnum
op_lshift
l_int|5
)paren
comma
id|S_IFCHR
op_or
id|device_mode
comma
l_string|&quot;snd/controlC%d&quot;
comma
id|controlnum
)paren
suffix:semicolon
id|class_simple_device_add
c_func
(paren
id|sound_class
comma
id|MKDEV
c_func
(paren
id|major
comma
id|controlnum
op_lshift
l_int|5
)paren
comma
l_int|NULL
comma
l_string|&quot;controlC%d&quot;
comma
id|controlnum
)paren
suffix:semicolon
)brace
macro_line|#ifndef MODULE
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Advanced Linux Sound Architecture Driver Version &quot;
id|CONFIG_SND_VERSION
id|CONFIG_SND_DATE
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_sound_exit
r_static
r_void
id|__exit
id|alsa_sound_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|controlnum
suffix:semicolon
r_for
c_loop
(paren
id|controlnum
op_assign
l_int|0
suffix:semicolon
id|controlnum
OL
id|cards_limit
suffix:semicolon
id|controlnum
op_increment
)paren
(brace
id|devfs_remove
c_func
(paren
l_string|&quot;snd/controlC%d&quot;
comma
id|controlnum
)paren
suffix:semicolon
id|class_simple_device_remove
c_func
(paren
id|MKDEV
c_func
(paren
id|major
comma
id|controlnum
op_lshift
l_int|5
)paren
)paren
suffix:semicolon
)brace
id|snd_info_minor_unregister
c_func
(paren
)paren
suffix:semicolon
id|snd_info_done
c_func
(paren
)paren
suffix:semicolon
id|snd_memory_done
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unregister_chrdev
c_func
(paren
id|major
comma
l_string|&quot;alsa&quot;
)paren
op_ne
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to unregister major device number %d&bslash;n&quot;
comma
id|major
)paren
suffix:semicolon
id|devfs_remove
c_func
(paren
l_string|&quot;snd&quot;
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_sound_init
)paren
id|module_exit
c_func
(paren
id|alsa_sound_exit
)paren
multiline_comment|/* sound.c */
id|EXPORT_SYMBOL
c_func
(paren
id|snd_major
)paren
suffix:semicolon
DECL|variable|EXPORT_SYMBOL
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ecards_limit
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_KMOD)
DECL|variable|snd_request_card
id|EXPORT_SYMBOL
c_func
(paren
id|snd_request_card
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|snd_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|snd_register_device
)paren
suffix:semicolon
DECL|variable|snd_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|snd_unregister_device
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SND_OSSEMUL)
DECL|variable|snd_register_oss_device
id|EXPORT_SYMBOL
c_func
(paren
id|snd_register_oss_device
)paren
suffix:semicolon
DECL|variable|snd_unregister_oss_device
id|EXPORT_SYMBOL
c_func
(paren
id|snd_unregister_oss_device
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* memory.c */
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
DECL|variable|snd_hidden_kmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hidden_kmalloc
)paren
suffix:semicolon
DECL|variable|snd_hidden_kcalloc
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hidden_kcalloc
)paren
suffix:semicolon
DECL|variable|snd_hidden_kfree
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hidden_kfree
)paren
suffix:semicolon
DECL|variable|snd_hidden_vmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hidden_vmalloc
)paren
suffix:semicolon
DECL|variable|snd_hidden_vfree
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hidden_vfree
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|snd_kmalloc_strdup
id|EXPORT_SYMBOL
c_func
(paren
id|snd_kmalloc_strdup
)paren
suffix:semicolon
DECL|variable|copy_to_user_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|copy_to_user_fromio
)paren
suffix:semicolon
DECL|variable|copy_from_user_toio
id|EXPORT_SYMBOL
c_func
(paren
id|copy_from_user_toio
)paren
suffix:semicolon
multiline_comment|/* init.c */
DECL|variable|snd_cards
id|EXPORT_SYMBOL
c_func
(paren
id|snd_cards
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SND_MIXER_OSS) || defined(CONFIG_SND_MIXER_OSS_MODULE)
DECL|variable|snd_mixer_oss_notify_callback
id|EXPORT_SYMBOL
c_func
(paren
id|snd_mixer_oss_notify_callback
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|snd_card_new
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_new
)paren
suffix:semicolon
DECL|variable|snd_card_disconnect
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_disconnect
)paren
suffix:semicolon
DECL|variable|snd_card_free
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_free
)paren
suffix:semicolon
DECL|variable|snd_card_free_in_thread
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_free_in_thread
)paren
suffix:semicolon
DECL|variable|snd_card_register
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_register
)paren
suffix:semicolon
DECL|variable|snd_component_add
id|EXPORT_SYMBOL
c_func
(paren
id|snd_component_add
)paren
suffix:semicolon
DECL|variable|snd_card_file_add
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_file_add
)paren
suffix:semicolon
DECL|variable|snd_card_file_remove
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_file_remove
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
DECL|variable|snd_power_wait
id|EXPORT_SYMBOL
c_func
(paren
id|snd_power_wait
)paren
suffix:semicolon
DECL|variable|snd_card_set_pm_callback
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_set_pm_callback
)paren
suffix:semicolon
DECL|variable|snd_card_set_dev_pm_callback
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_set_dev_pm_callback
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
DECL|variable|snd_card_pci_suspend
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_pci_suspend
)paren
suffix:semicolon
DECL|variable|snd_card_pci_resume
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_pci_resume
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* device.c */
DECL|variable|snd_device_new
id|EXPORT_SYMBOL
c_func
(paren
id|snd_device_new
)paren
suffix:semicolon
DECL|variable|snd_device_register
id|EXPORT_SYMBOL
c_func
(paren
id|snd_device_register
)paren
suffix:semicolon
DECL|variable|snd_device_free
id|EXPORT_SYMBOL
c_func
(paren
id|snd_device_free
)paren
suffix:semicolon
DECL|variable|snd_device_free_all
id|EXPORT_SYMBOL
c_func
(paren
id|snd_device_free_all
)paren
suffix:semicolon
multiline_comment|/* isadma.c */
macro_line|#ifdef CONFIG_ISA
DECL|variable|snd_dma_program
id|EXPORT_SYMBOL
c_func
(paren
id|snd_dma_program
)paren
suffix:semicolon
DECL|variable|snd_dma_disable
id|EXPORT_SYMBOL
c_func
(paren
id|snd_dma_disable
)paren
suffix:semicolon
DECL|variable|snd_dma_pointer
id|EXPORT_SYMBOL
c_func
(paren
id|snd_dma_pointer
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* info.c */
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|snd_seq_root
id|EXPORT_SYMBOL
c_func
(paren
id|snd_seq_root
)paren
suffix:semicolon
DECL|variable|snd_iprintf
id|EXPORT_SYMBOL
c_func
(paren
id|snd_iprintf
)paren
suffix:semicolon
DECL|variable|snd_info_get_line
id|EXPORT_SYMBOL
c_func
(paren
id|snd_info_get_line
)paren
suffix:semicolon
DECL|variable|snd_info_get_str
id|EXPORT_SYMBOL
c_func
(paren
id|snd_info_get_str
)paren
suffix:semicolon
DECL|variable|snd_info_create_module_entry
id|EXPORT_SYMBOL
c_func
(paren
id|snd_info_create_module_entry
)paren
suffix:semicolon
DECL|variable|snd_info_create_card_entry
id|EXPORT_SYMBOL
c_func
(paren
id|snd_info_create_card_entry
)paren
suffix:semicolon
DECL|variable|snd_info_free_entry
id|EXPORT_SYMBOL
c_func
(paren
id|snd_info_free_entry
)paren
suffix:semicolon
DECL|variable|snd_info_register
id|EXPORT_SYMBOL
c_func
(paren
id|snd_info_register
)paren
suffix:semicolon
DECL|variable|snd_info_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|snd_info_unregister
)paren
suffix:semicolon
DECL|variable|snd_card_proc_new
id|EXPORT_SYMBOL
c_func
(paren
id|snd_card_proc_new
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* info_oss.c */
macro_line|#if defined(CONFIG_SND_OSSEMUL) &amp;&amp; defined(CONFIG_PROC_FS)
DECL|variable|snd_oss_info_register
id|EXPORT_SYMBOL
c_func
(paren
id|snd_oss_info_register
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* control.c */
DECL|variable|snd_ctl_new
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_new
)paren
suffix:semicolon
DECL|variable|snd_ctl_new1
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_new1
)paren
suffix:semicolon
DECL|variable|snd_ctl_free_one
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_free_one
)paren
suffix:semicolon
DECL|variable|snd_ctl_add
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_add
)paren
suffix:semicolon
DECL|variable|snd_ctl_remove
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_remove
)paren
suffix:semicolon
DECL|variable|snd_ctl_remove_id
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_remove_id
)paren
suffix:semicolon
DECL|variable|snd_ctl_rename_id
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_rename_id
)paren
suffix:semicolon
DECL|variable|snd_ctl_find_numid
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_find_numid
)paren
suffix:semicolon
DECL|variable|snd_ctl_find_id
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_find_id
)paren
suffix:semicolon
DECL|variable|snd_ctl_notify
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_notify
)paren
suffix:semicolon
DECL|variable|snd_ctl_register_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_register_ioctl
)paren
suffix:semicolon
DECL|variable|snd_ctl_unregister_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_unregister_ioctl
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_COMPAT
DECL|variable|snd_ctl_elem_read
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_elem_read
)paren
suffix:semicolon
DECL|variable|snd_ctl_elem_write
id|EXPORT_SYMBOL
c_func
(paren
id|snd_ctl_elem_write
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* misc.c */
DECL|variable|snd_task_name
id|EXPORT_SYMBOL
c_func
(paren
id|snd_task_name
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_VERBOSE_PRINTK
DECL|variable|snd_verbose_printk
id|EXPORT_SYMBOL
c_func
(paren
id|snd_verbose_printk
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_SND_DEBUG) &amp;&amp; defined(CONFIG_SND_VERBOSE_PRINTK)
DECL|variable|snd_verbose_printd
id|EXPORT_SYMBOL
c_func
(paren
id|snd_verbose_printd
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* wrappers */
macro_line|#ifdef CONFIG_SND_DEBUG_MEMORY
DECL|variable|snd_wrapper_kmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|snd_wrapper_kmalloc
)paren
suffix:semicolon
DECL|variable|snd_wrapper_kfree
id|EXPORT_SYMBOL
c_func
(paren
id|snd_wrapper_kfree
)paren
suffix:semicolon
DECL|variable|snd_wrapper_vmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|snd_wrapper_vmalloc
)paren
suffix:semicolon
DECL|variable|snd_wrapper_vfree
id|EXPORT_SYMBOL
c_func
(paren
id|snd_wrapper_vfree
)paren
suffix:semicolon
macro_line|#endif
eof
