multiline_comment|/*&n; *  Initialization routines&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/info.h&gt;
DECL|struct|snd_shutdown_f_ops
r_struct
id|snd_shutdown_f_ops
(brace
DECL|member|f_ops
r_struct
id|file_operations
id|f_ops
suffix:semicolon
DECL|member|next
r_struct
id|snd_shutdown_f_ops
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|snd_cards_count
r_int
id|snd_cards_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|snd_cards_lock
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
r_static
r_void
id|snd_card_free_thread
c_func
(paren
r_void
op_star
id|__card
)paren
suffix:semicolon
multiline_comment|/**&n; *  snd_card_new - create and initialize a soundcard structure&n; *  @idx: card index (address) [0 ... (SNDRV_CARDS-1)]&n; *  @xid: card identification (ASCII string)&n; *  @module: top level module for locking&n; *  @extra_size: allocate this extra size after the main soundcard structure&n; *&n; *  Creates and initializes a soundcard structure.&n; *&n; *  Returns kmallocated snd_card_t structure. Creates the ALSA control interface&n; *  (which is blocked until snd_card_register function is called).&n; */
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
id|strlcpy
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
r_if
c_cond
(paren
id|idx
OL
l_int|0
op_logical_and
id|snd_ecards_limit
OL
id|SNDRV_CARDS
)paren
multiline_comment|/* for dynamically additional devices like hotplug:&n;&t;&t;&t; * increment the limit if still free slot exists.&n;&t;&t;&t; */
id|idx
op_assign
id|snd_ecards_limit
op_increment
suffix:semicolon
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
r_else
r_if
c_cond
(paren
id|idx
OL
id|SNDRV_CARDS
)paren
id|snd_ecards_limit
op_assign
id|idx
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* increase the limit */
r_else
id|idx
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
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
id|init_rwsem
c_func
(paren
op_amp
id|card-&gt;controls_rwsem
)paren
suffix:semicolon
id|rwlock_init
c_func
(paren
op_amp
id|card-&gt;ctl_files_rwlock
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
id|spin_lock_init
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|card-&gt;shutdown_sleep
)paren
suffix:semicolon
id|INIT_WORK
c_func
(paren
op_amp
id|card-&gt;free_workq
comma
id|snd_card_free_thread
comma
id|card
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
id|snd_info_card_create
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
l_string|&quot;unable to create card info&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|__error_ctl
suffix:semicolon
)brace
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
DECL|function|snd_disconnect_poll
r_static
r_int
r_int
id|snd_disconnect_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_return
id|POLLERR
op_or
id|POLLNVAL
suffix:semicolon
)brace
multiline_comment|/**&n; *  snd_card_disconnect - disconnect all APIs from the file-operations (user space)&n; *  @card: soundcard structure&n; *&n; *  Disconnects all APIs from the file-operations (user space).&n; *&n; *  Returns zero, otherwise a negative error code.&n; *&n; *  Note: The current implementation replaces all active file-&gt;f_op with special&n; *        dummy file operations (they do nothing except release).&n; */
DECL|function|snd_card_disconnect
r_int
id|snd_card_disconnect
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_struct
id|snd_monitor_file
op_star
id|mfile
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|snd_shutdown_f_ops
op_star
id|s_f_ops
suffix:semicolon
r_struct
id|file_operations
op_star
id|f_ops
comma
op_star
id|old_f_ops
suffix:semicolon
r_int
id|err
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;shutdown
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|card-&gt;shutdown
op_assign
l_int|1
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
multiline_comment|/* phase 1: disable fops (user space) operations for ALSA API */
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
id|write_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
)paren
suffix:semicolon
multiline_comment|/* phase 2: replace file-&gt;f_op with special dummy operations */
id|spin_lock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
id|mfile
op_assign
id|card-&gt;files
suffix:semicolon
r_while
c_loop
(paren
id|mfile
)paren
(brace
id|file
op_assign
id|mfile-&gt;file
suffix:semicolon
multiline_comment|/* it&squot;s critical part, use endless loop */
multiline_comment|/* we have no room to fail */
id|s_f_ops
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|snd_shutdown_f_ops
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s_f_ops
op_eq
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;Atomic allocation failed for snd_shutdown_f_ops!&quot;
)paren
suffix:semicolon
id|f_ops
op_assign
op_amp
id|s_f_ops-&gt;f_ops
suffix:semicolon
id|memset
c_func
(paren
id|f_ops
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|f_ops
)paren
)paren
suffix:semicolon
id|f_ops-&gt;owner
op_assign
id|file-&gt;f_op-&gt;owner
suffix:semicolon
id|f_ops-&gt;release
op_assign
id|file-&gt;f_op-&gt;release
suffix:semicolon
id|f_ops-&gt;poll
op_assign
id|snd_disconnect_poll
suffix:semicolon
id|s_f_ops-&gt;next
op_assign
id|card-&gt;s_f_ops
suffix:semicolon
id|card-&gt;s_f_ops
op_assign
id|s_f_ops
suffix:semicolon
id|f_ops
op_assign
id|fops_get
c_func
(paren
id|f_ops
)paren
suffix:semicolon
id|old_f_ops
op_assign
id|file-&gt;f_op
suffix:semicolon
id|file-&gt;f_op
op_assign
id|f_ops
suffix:semicolon
multiline_comment|/* must be atomic */
id|fops_put
c_func
(paren
id|old_f_ops
)paren
suffix:semicolon
id|mfile
op_assign
id|mfile-&gt;next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
multiline_comment|/* phase 3: notify all connected devices about disconnection */
multiline_comment|/* at this point, they cannot respond to any calls except release() */
id|snd_ctl_disconnect
c_func
(paren
id|card
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
id|SND_MIXER_OSS_NOTIFY_DISCONNECT
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* notify all devices that we are disconnected */
id|err
op_assign
id|snd_device_disconnect_all
c_func
(paren
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;not all devices for card %i can be disconnected&bslash;n&quot;
comma
id|card-&gt;number
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *  snd_card_free - frees given soundcard structure&n; *  @card: soundcard structure&n; *&n; *  This function releases the soundcard structure and the all assigned&n; *  devices automatically.  That is, you don&squot;t have to release the devices&n; *  by yourself.&n; *&n; *  Returns zero. Frees all associated devices and frees the control&n; *  interface associated to given soundcard.&n; */
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
r_struct
id|snd_shutdown_f_ops
op_star
id|s_f_ops
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
macro_line|#ifdef CONFIG_PM
id|wake_up
c_func
(paren
op_amp
id|card-&gt;power_sleep
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* wait, until all devices are ready for the free operation */
id|wait_event
c_func
(paren
id|card-&gt;shutdown_sleep
comma
id|card-&gt;files
op_eq
l_int|NULL
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
id|SND_MIXER_OSS_NOTIFY_FREE
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
id|snd_info_card_free
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
l_string|&quot;unable to free card info&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Not fatal error */
)brace
r_while
c_loop
(paren
id|card-&gt;s_f_ops
)paren
(brace
id|s_f_ops
op_assign
id|card-&gt;s_f_ops
suffix:semicolon
id|card-&gt;s_f_ops
op_assign
id|s_f_ops-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|s_f_ops
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
DECL|function|snd_card_free_thread
r_static
r_void
id|snd_card_free_thread
c_func
(paren
r_void
op_star
id|__card
)paren
(brace
id|snd_card_t
op_star
id|card
op_assign
id|__card
suffix:semicolon
r_struct
id|module
op_star
id|module
op_assign
id|card-&gt;module
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|try_module_get
c_func
(paren
id|module
)paren
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to lock toplevel module for card %i in free thread&bslash;n&quot;
comma
id|card-&gt;number
)paren
suffix:semicolon
id|module
op_assign
l_int|NULL
suffix:semicolon
)brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
id|module_put
c_func
(paren
id|module
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *  snd_card_free_in_thread - call snd_card_free() in thread&n; *  @card: soundcard structure&n; *&n; *  This function schedules the call of snd_card_free() function in a&n; *  work queue.  When all devices are released (non-busy), the work&n; *  is woken up and calls snd_card_free().&n; *&n; *  When a card can be disconnected at any time by hotplug service,&n; *  this function should be used in disconnect (or detach) callback&n; *  instead of calling snd_card_free() directly.&n; *  &n; *  Returns - zero otherwise a negative error code if the start of thread failed.&n; */
DECL|function|snd_card_free_in_thread
r_int
id|snd_card_free_in_thread
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
id|card-&gt;files
op_eq
l_int|NULL
)paren
(brace
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|schedule_work
c_func
(paren
op_amp
id|card-&gt;free_workq
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;schedule_work() failed in snd_card_free_in_thread for card %i&bslash;n&quot;
comma
id|card-&gt;number
)paren
suffix:semicolon
multiline_comment|/* try to free the structure immediately */
id|snd_card_free
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
DECL|function|choose_default_id
r_static
r_void
id|choose_default_id
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_int
id|i
comma
id|len
comma
id|idx_flag
op_assign
l_int|0
comma
id|loops
op_assign
l_int|8
suffix:semicolon
r_char
op_star
id|id
comma
op_star
id|spos
suffix:semicolon
id|id
op_assign
id|spos
op_assign
id|card-&gt;shortname
suffix:semicolon
r_while
c_loop
(paren
op_star
id|id
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
id|id
op_eq
l_char|&squot; &squot;
)paren
id|spos
op_assign
id|id
op_plus
l_int|1
suffix:semicolon
id|id
op_increment
suffix:semicolon
)brace
id|id
op_assign
id|card-&gt;id
suffix:semicolon
r_while
c_loop
(paren
op_star
id|spos
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
op_logical_neg
id|isalnum
c_func
(paren
op_star
id|spos
)paren
)paren
id|spos
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|isdigit
c_func
(paren
op_star
id|spos
)paren
)paren
op_star
id|id
op_increment
op_assign
id|isalpha
c_func
(paren
id|card-&gt;shortname
(braket
l_int|0
)braket
)paren
ques
c_cond
id|card-&gt;shortname
(braket
l_int|0
)braket
suffix:colon
l_char|&squot;D&squot;
suffix:semicolon
r_while
c_loop
(paren
op_star
id|spos
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
(paren
r_int
)paren
(paren
id|id
op_minus
id|card-&gt;id
)paren
OL
r_sizeof
(paren
id|card-&gt;id
)paren
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|isalnum
c_func
(paren
op_star
id|spos
)paren
)paren
op_star
id|id
op_increment
op_assign
op_star
id|spos
suffix:semicolon
id|spos
op_increment
suffix:semicolon
)brace
op_star
id|id
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|id
op_assign
id|card-&gt;id
suffix:semicolon
r_if
c_cond
(paren
op_star
id|id
op_eq
l_char|&squot;&bslash;0&squot;
)paren
id|strcpy
c_func
(paren
id|id
comma
l_string|&quot;default&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|loops
op_decrement
op_eq
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to choose default card id (%s)&quot;
comma
id|id
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|card-&gt;id
comma
id|card-&gt;proc_root-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|snd_info_check_reserved_words
c_func
(paren
id|id
)paren
)paren
r_goto
id|__change
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|snd_ecards_limit
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|snd_cards
(braket
id|i
)braket
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|snd_cards
(braket
id|i
)braket
op_member_access_from_pointer
id|id
comma
id|id
)paren
)paren
r_goto
id|__change
suffix:semicolon
)brace
r_break
suffix:semicolon
id|__change
suffix:colon
id|len
op_assign
id|strlen
c_func
(paren
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idx_flag
)paren
id|id
(braket
id|len
op_minus
l_int|1
)braket
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
r_int
)paren
id|len
op_le
r_sizeof
(paren
id|card-&gt;id
)paren
op_minus
l_int|3
)paren
(brace
id|strcat
c_func
(paren
id|id
comma
l_string|&quot;_1&quot;
)paren
suffix:semicolon
id|idx_flag
op_increment
suffix:semicolon
)brace
r_else
(brace
id|spos
op_assign
id|id
op_plus
id|len
op_minus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|len
op_le
r_sizeof
(paren
id|card-&gt;id
)paren
op_minus
l_int|2
)paren
id|spos
op_increment
suffix:semicolon
op_star
id|spos
op_increment
op_assign
l_char|&squot;_&squot;
suffix:semicolon
op_star
id|spos
op_increment
op_assign
l_char|&squot;1&squot;
suffix:semicolon
op_star
id|spos
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|idx_flag
op_increment
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; *  snd_card_register - register the soundcard&n; *  @card: soundcard structure&n; *&n; *  This function registers all the devices assigned to the soundcard.&n; *  Until calling this, the ALSA control interface is blocked from the&n; *  external accesses.  Thus, you should call this function at the end&n; *  of the initialization of the card.&n; *&n; *  Returns zero otherwise a negative error code if the registrain failed.&n; */
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
id|snd_info_entry_t
op_star
id|entry
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
r_if
c_cond
(paren
id|card-&gt;id
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
id|choose_default_id
c_func
(paren
id|card
)paren
suffix:semicolon
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
l_string|&quot;unable to create card info&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|__skip_info
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
id|__skip_info
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
id|entry
op_assign
l_int|NULL
suffix:semicolon
)brace
id|card-&gt;proc_id
op_assign
id|entry
suffix:semicolon
id|__skip_info
suffix:colon
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
id|SND_MIXER_OSS_NOTIFY_REGISTER
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
macro_line|#ifdef MODULE
DECL|variable|snd_card_module_info_entry
r_static
id|snd_info_entry_t
op_star
id|snd_card_module_info_entry
suffix:semicolon
DECL|function|snd_card_module_info_read
r_static
r_void
id|snd_card_module_info_read
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
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%i %s&bslash;n&quot;
comma
id|idx
comma
id|card-&gt;module-&gt;name
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|snd_card_rwlock
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
macro_line|#ifdef MODULE
id|entry
op_assign
id|snd_info_create_module_entry
c_func
(paren
id|THIS_MODULE
comma
l_string|&quot;modules&quot;
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
id|snd_card_module_info_read
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
id|snd_info_free_entry
c_func
(paren
id|entry
)paren
suffix:semicolon
r_else
id|snd_card_module_info_entry
op_assign
id|entry
suffix:semicolon
)brace
macro_line|#endif
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
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|snd_card_module_info_entry
)paren
id|snd_info_unregister
c_func
(paren
id|snd_card_module_info_entry
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *  snd_component_add - add a component string&n; *  @card: soundcard structure&n; *  @component: the component id string&n; *&n; *  This function adds the component id string to the supported list.&n; *  The component can be referred from the alsa-lib.&n; *&n; *  Returns zero otherwise a negative error code.&n; */
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
multiline_comment|/**&n; *  snd_card_file_add - add the file to the file list of the card&n; *  @card: soundcard structure&n; *  @file: file pointer&n; *&n; *  This function adds the file to the file linked-list of the card.&n; *  This linked-list is used to keep tracking the connection state,&n; *  and to avoid the release of busy resources by hotplug.&n; *&n; *  Returns zero or a negative error code.&n; */
DECL|function|snd_card_file_add
r_int
id|snd_card_file_add
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|snd_monitor_file
op_star
id|mfile
suffix:semicolon
id|mfile
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mfile
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mfile
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|mfile-&gt;file
op_assign
id|file
suffix:semicolon
id|mfile-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;shutdown
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mfile
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|mfile-&gt;next
op_assign
id|card-&gt;files
suffix:semicolon
id|card-&gt;files
op_assign
id|mfile
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *  snd_card_file_remove - remove the file from the file list&n; *  @card: soundcard structure&n; *  @file: file pointer&n; *&n; *  This function removes the file formerly added to the card via&n; *  snd_card_file_add() function.&n; *  If all files are removed and the release of the card is&n; *  scheduled, it will wake up the the thread to call snd_card_free()&n; *  (see snd_card_free_in_thread() function).&n; *&n; *  Returns zero or a negative error code.&n; */
DECL|function|snd_card_file_remove
r_int
id|snd_card_file_remove
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_struct
id|snd_monitor_file
op_star
id|mfile
comma
op_star
id|pfile
op_assign
l_int|NULL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
id|mfile
op_assign
id|card-&gt;files
suffix:semicolon
r_while
c_loop
(paren
id|mfile
)paren
(brace
r_if
c_cond
(paren
id|mfile-&gt;file
op_eq
id|file
)paren
(brace
r_if
c_cond
(paren
id|pfile
)paren
id|pfile-&gt;next
op_assign
id|mfile-&gt;next
suffix:semicolon
r_else
id|card-&gt;files
op_assign
id|mfile-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pfile
op_assign
id|mfile
suffix:semicolon
id|mfile
op_assign
id|mfile-&gt;next
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|card-&gt;files_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;files
op_eq
l_int|NULL
)paren
id|wake_up
c_func
(paren
op_amp
id|card-&gt;shutdown_sleep
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mfile
)paren
(brace
id|kfree
c_func
(paren
id|mfile
)paren
suffix:semicolon
)brace
r_else
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ALSA card file remove problem (%p)&bslash;n&quot;
comma
id|file
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PM
multiline_comment|/**&n; *  snd_power_wait - wait until the power-state is changed.&n; *  @card: soundcard structure&n; *  @power_state: expected power state&n; *  @file: file structure for the O_NONBLOCK check (optional)&n; *&n; *  Waits until the power-state is changed.&n; *&n; *  Note: the power lock must be active before call.&n; */
DECL|function|snd_power_wait
r_int
id|snd_power_wait
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|power_state
comma
r_struct
id|file
op_star
id|file
)paren
(brace
id|wait_queue_t
id|wait
suffix:semicolon
multiline_comment|/* fastpath */
r_if
c_cond
(paren
id|snd_power_get_state
c_func
(paren
id|card
)paren
op_eq
id|power_state
)paren
r_return
l_int|0
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
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|card-&gt;shutdown
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|snd_power_get_state
c_func
(paren
id|card
)paren
op_eq
id|power_state
)paren
(brace
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
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file
op_logical_and
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|snd_power_unlock
c_func
(paren
id|card
)paren
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
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
id|snd_power_lock
c_func
(paren
id|card
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_PM */
eof
