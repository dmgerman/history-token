multiline_comment|/*&n; *  Initialization routines&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/info.h&gt;
DECL|variable|snd_cards_count
r_int
id|snd_cards_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|snd_cards_lock
r_static
r_int
r_int
id|snd_cards_lock
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* locked for registering/using */
DECL|variable|snd_cards
id|snd_card_t
op_star
id|snd_cards
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
l_int|NULL
)brace
suffix:semicolon
DECL|variable|snd_card_rwlock
id|rwlock_t
id|snd_card_rwlock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
macro_line|#if defined(CONFIG_SND_MIXER_OSS) || defined(CONFIG_SND_MIXER_OSS_MODULE)
DECL|variable|snd_mixer_oss_notify_callback
r_int
(paren
op_star
id|snd_mixer_oss_notify_callback
)paren
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|free_flag
)paren
suffix:semicolon
macro_line|#endif
DECL|function|snd_card_id_read
r_static
r_void
id|snd_card_id_read
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
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|entry-&gt;card-&gt;id
)paren
suffix:semicolon
)brace
DECL|function|snd_card_new
id|snd_card_t
op_star
id|snd_card_new
c_func
(paren
r_int
id|idx
comma
r_const
r_char
op_star
id|xid
comma
r_struct
id|module
op_star
id|module
comma
r_int
id|extra_size
)paren
(brace
id|snd_card_t
op_star
id|card
suffix:semicolon
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|extra_size
OL
l_int|0
)paren
id|extra_size
op_assign
l_int|0
suffix:semicolon
id|card
op_assign
(paren
id|snd_card_t
op_star
)paren
id|snd_kcalloc
c_func
(paren
r_sizeof
(paren
id|snd_card_t
)paren
op_plus
id|extra_size
comma
id|GFP_KERNEL
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
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|xid
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|snd_info_check_reserved_words
c_func
(paren
id|xid
)paren
)paren
r_goto
id|__error
suffix:semicolon
id|strncpy
c_func
(paren
id|card-&gt;id
comma
id|xid
comma
r_sizeof
(paren
id|card-&gt;id
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|write_lock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
)paren
(brace
r_int
id|idx2
suffix:semicolon
r_for
c_loop
(paren
id|idx2
op_assign
l_int|0
suffix:semicolon
id|idx2
OL
id|snd_ecards_limit
suffix:semicolon
id|idx2
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|snd_cards_lock
op_amp
(paren
l_int|1
op_lshift
id|idx2
)paren
)paren
)paren
(brace
id|idx
op_assign
id|idx2
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|idx
OL
id|snd_ecards_limit
)paren
(brace
r_if
c_cond
(paren
id|snd_cards_lock
op_amp
(paren
l_int|1
op_lshift
id|idx
)paren
)paren
id|idx
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* invalid */
)brace
r_if
c_cond
(paren
id|idx
OL
l_int|0
op_logical_or
id|idx
op_ge
id|snd_ecards_limit
)paren
(brace
id|write_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx
op_ge
id|snd_ecards_limit
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;card %i is out of range (0-%i)&bslash;n&quot;
comma
id|idx
comma
id|snd_ecards_limit
op_minus
l_int|1
)paren
suffix:semicolon
r_goto
id|__error
suffix:semicolon
)brace
id|snd_cards_lock
op_or_assign
l_int|1
op_lshift
id|idx
suffix:semicolon
multiline_comment|/* lock it */
id|write_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
id|card-&gt;number
op_assign
id|idx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;id
(braket
l_int|0
)braket
)paren
id|sprintf
c_func
(paren
id|card-&gt;id
comma
l_string|&quot;card%i&quot;
comma
id|card-&gt;number
)paren
suffix:semicolon
id|card-&gt;module
op_assign
id|module
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|card-&gt;devices
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|card-&gt;control_rwlock
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|card-&gt;control_owner_lock
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|card-&gt;controls
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|card-&gt;ctl_files
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
id|init_MUTEX
c_func
(paren
op_amp
id|card-&gt;power_lock
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|card-&gt;power_sleep
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* the control interface cannot be accessed from the user space until */
multiline_comment|/* snd_cards_bitmask and snd_cards are set with snd_card_register */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_ctl_register
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;unable to register control minors&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|__error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_info_card_register
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;unable to register card info&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|__error_ctl
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|snd_info_create_card_entry
c_func
(paren
id|card
comma
l_string|&quot;id&quot;
comma
id|card-&gt;proc_root
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|snd_printd
c_func
(paren
l_string|&quot;unable to create card entry&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|__error_info
suffix:semicolon
)brace
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
id|snd_card_id_read
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
r_goto
id|__error_info
suffix:semicolon
)brace
id|card-&gt;proc_id
op_assign
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|extra_size
OG
l_int|0
)paren
id|card-&gt;private_data
op_assign
(paren
r_char
op_star
)paren
id|card
op_plus
r_sizeof
(paren
id|snd_card_t
)paren
suffix:semicolon
r_return
id|card
suffix:semicolon
id|__error_info
suffix:colon
id|snd_info_card_unregister
c_func
(paren
id|card
)paren
suffix:semicolon
id|__error_ctl
suffix:colon
id|snd_ctl_unregister
c_func
(paren
id|card
)paren
suffix:semicolon
id|__error
suffix:colon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_card_free
r_int
id|snd_card_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_if
c_cond
(paren
id|card
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
id|snd_cards
(braket
id|card-&gt;number
)braket
op_assign
l_int|NULL
suffix:semicolon
id|snd_cards_count
op_decrement
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SND_MIXER_OSS) || defined(CONFIG_SND_MIXER_OSS_MODULE)
r_if
c_cond
(paren
id|snd_mixer_oss_notify_callback
)paren
id|snd_mixer_oss_notify_callback
c_func
(paren
id|card
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|snd_device_free_all
c_func
(paren
id|card
comma
id|SNDRV_DEV_CMD_PRE
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to free all devices (pre)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Fatal, but this situation should never occur */
)brace
r_if
c_cond
(paren
id|snd_device_free_all
c_func
(paren
id|card
comma
id|SNDRV_DEV_CMD_NORMAL
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to free all devices (normal)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Fatal, but this situation should never occur */
)brace
r_if
c_cond
(paren
id|snd_ctl_unregister
c_func
(paren
id|card
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to unregister control minors&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Not fatal error */
)brace
r_if
c_cond
(paren
id|snd_device_free_all
c_func
(paren
id|card
comma
id|SNDRV_DEV_CMD_POST
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to free all devices (post)&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Fatal, but this situation should never occur */
)brace
r_if
c_cond
(paren
id|card-&gt;private_free
)paren
id|card
op_member_access_from_pointer
id|private_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|snd_info_free_entry
c_func
(paren
id|card-&gt;proc_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_info_card_unregister
c_func
(paren
id|card
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;unable to unregister card info&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Not fatal error */
)brace
id|write_lock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
id|snd_cards_lock
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|card-&gt;number
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_register
r_int
id|snd_card_register
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_int
id|err
suffix:semicolon
id|snd_runtime_check
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
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_device_register_all
c_func
(paren
id|card
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_cards
(braket
id|card-&gt;number
)braket
)paren
(brace
multiline_comment|/* already registered */
id|write_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|snd_cards
(braket
id|card-&gt;number
)braket
op_assign
id|card
suffix:semicolon
id|snd_cards_count
op_increment
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SND_MIXER_OSS) || defined(CONFIG_SND_MIXER_OSS_MODULE)
r_if
c_cond
(paren
id|snd_mixer_oss_notify_callback
)paren
id|snd_mixer_oss_notify_callback
c_func
(paren
id|card
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|snd_card_info_entry
r_static
id|snd_info_entry_t
op_star
id|snd_card_info_entry
op_assign
l_int|NULL
suffix:semicolon
DECL|function|snd_card_info_read
r_static
r_void
id|snd_card_info_read
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
id|idx
comma
id|count
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
id|count
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_CARDS
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|card
op_assign
id|snd_cards
(braket
id|idx
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|count
op_increment
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%i [%-15s]: %s - %s&bslash;n&quot;
comma
id|idx
comma
id|card-&gt;id
comma
id|card-&gt;driver
comma
id|card-&gt;shortname
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;                     %s&bslash;n&quot;
comma
id|card-&gt;longname
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;--- no soundcards ---&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SND_OSSEMUL) &amp;&amp; defined(CONFIG_PROC_FS)
DECL|function|snd_card_info_read_oss
r_void
id|snd_card_info_read_oss
c_func
(paren
id|snd_info_buffer_t
op_star
id|buffer
)paren
(brace
r_int
id|idx
comma
id|count
suffix:semicolon
id|snd_card_t
op_star
id|card
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
id|count
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|SNDRV_CARDS
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|read_lock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|card
op_assign
id|snd_cards
(braket
id|idx
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|count
op_increment
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|card-&gt;longname
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
(brace
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;--- no soundcards ---&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|snd_card_info_init
r_int
id|__init
id|snd_card_info_init
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
l_string|&quot;cards&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|snd_runtime_check
c_func
(paren
id|entry
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENOMEM
)paren
suffix:semicolon
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
id|snd_card_info_read
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|snd_card_info_entry
op_assign
id|entry
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_card_info_done
r_int
id|__exit
id|snd_card_info_done
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|snd_card_info_entry
)paren
id|snd_info_unregister
c_func
(paren
id|snd_card_info_entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_component_add
r_int
id|snd_component_add
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|component
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|component
)paren
suffix:semicolon
id|ptr
op_assign
id|strstr
c_func
(paren
id|card-&gt;components
comma
id|component
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ptr
(braket
id|len
)braket
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
id|ptr
(braket
id|len
)braket
op_eq
l_char|&squot; &squot;
)paren
multiline_comment|/* already there */
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|card-&gt;components
)paren
op_plus
l_int|1
op_plus
id|len
op_plus
l_int|1
OG
r_sizeof
(paren
id|card-&gt;components
)paren
)paren
(brace
id|snd_BUG
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;components
(braket
l_int|0
)braket
op_ne
l_char|&squot;&bslash;0&squot;
)paren
id|strcat
c_func
(paren
id|card-&gt;components
comma
l_string|&quot; &quot;
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|card-&gt;components
comma
id|component
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
multiline_comment|/* the power lock must be active before call */
DECL|function|snd_power_wait
r_void
id|snd_power_wait
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
id|wait_queue_t
id|wait
suffix:semicolon
id|init_waitqueue_entry
c_func
(paren
op_amp
id|wait
comma
id|current
)paren
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|card-&gt;power_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|snd_power_unlock
c_func
(paren
id|card
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|30
op_star
id|HZ
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|card-&gt;power_sleep
comma
op_amp
id|wait
)paren
suffix:semicolon
id|snd_power_lock
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PM */
eof
