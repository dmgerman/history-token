multiline_comment|/*&n; * OSS compatible sequencer driver&n; *&n; * registration of device and proc&n; *&n; * Copyright (C) 1998,99 Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/minors.h&gt;
macro_line|#include &lt;sound/initval.h&gt;
macro_line|#include &quot;seq_oss_device.h&quot;
macro_line|#include &quot;seq_oss_synth.h&quot;
multiline_comment|/*&n; * module option&n; */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;OSS-compatible sequencer module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Takashi says this is really only for sound-service-0-, but this is OK. */
DECL|variable|SNDRV_MINOR_OSS_SEQUENCER
id|MODULE_ALIAS_SNDRV_MINOR
c_func
(paren
id|SNDRV_MINOR_OSS_SEQUENCER
)paren
suffix:semicolon
DECL|variable|SNDRV_MINOR_OSS_MUSIC
id|MODULE_ALIAS_SNDRV_MINOR
c_func
(paren
id|SNDRV_MINOR_OSS_MUSIC
)paren
suffix:semicolon
macro_line|#ifdef SNDRV_SEQ_OSS_DEBUG
id|module_param
c_func
(paren
id|seq_oss_debug
comma
r_int
comma
l_int|0644
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|seq_oss_debug
comma
l_string|&quot;debug option&quot;
)paren
suffix:semicolon
DECL|variable|seq_oss_debug
r_int
id|seq_oss_debug
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * prototypes&n; */
r_static
r_int
id|register_device
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|unregister_device
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|register_proc
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|unregister_proc
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|odev_open
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
suffix:semicolon
r_static
r_int
id|odev_release
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
suffix:semicolon
r_static
id|ssize_t
id|odev_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
suffix:semicolon
r_static
id|ssize_t
id|odev_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
suffix:semicolon
r_static
r_int
id|odev_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
r_int
id|odev_poll
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
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
r_static
r_void
id|info_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buf
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * module interface&n; */
DECL|function|alsa_seq_oss_init
r_static
r_int
id|__init
id|alsa_seq_oss_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_static
id|snd_seq_dev_ops_t
id|ops
op_assign
(brace
id|snd_seq_oss_synth_register
comma
id|snd_seq_oss_synth_unregister
comma
)brace
suffix:semicolon
id|snd_seq_autoload_lock
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|register_device
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|register_proc
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|unregister_device
c_func
(paren
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|snd_seq_oss_create_client
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|unregister_proc
c_func
(paren
)paren
suffix:semicolon
id|unregister_device
c_func
(paren
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|snd_seq_device_register_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_OSS
comma
op_amp
id|ops
comma
r_sizeof
(paren
id|snd_seq_oss_reg_t
)paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_seq_oss_delete_client
c_func
(paren
)paren
suffix:semicolon
id|unregister_proc
c_func
(paren
)paren
suffix:semicolon
id|unregister_device
c_func
(paren
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
multiline_comment|/* success */
id|snd_seq_oss_synth_init
c_func
(paren
)paren
suffix:semicolon
id|error
suffix:colon
id|snd_seq_autoload_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|alsa_seq_oss_exit
r_static
r_void
id|__exit
id|alsa_seq_oss_exit
c_func
(paren
r_void
)paren
(brace
id|snd_seq_device_unregister_driver
c_func
(paren
id|SNDRV_SEQ_DEV_ID_OSS
)paren
suffix:semicolon
id|snd_seq_oss_delete_client
c_func
(paren
)paren
suffix:semicolon
id|unregister_proc
c_func
(paren
)paren
suffix:semicolon
id|unregister_device
c_func
(paren
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|alsa_seq_oss_init
)paren
id|module_exit
c_func
(paren
id|alsa_seq_oss_exit
)paren
multiline_comment|/*&n; * ALSA minor device interface&n; */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|register_mutex
)paren
suffix:semicolon
r_static
r_int
DECL|function|odev_open
id|odev_open
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
id|level
comma
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|iminor
c_func
(paren
id|inode
)paren
op_eq
id|SNDRV_MINOR_OSS_MUSIC
)paren
id|level
op_assign
id|SNDRV_SEQ_OSS_MODE_MUSIC
suffix:semicolon
r_else
id|level
op_assign
id|SNDRV_SEQ_OSS_MODE_SYNTH
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|rc
op_assign
id|snd_seq_oss_open
c_func
(paren
id|file
comma
id|level
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_static
r_int
DECL|function|odev_release
id|odev_release
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
id|seq_oss_devinfo_t
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dp
op_assign
id|file-&gt;private_data
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|snd_seq_oss_drain_write
c_func
(paren
id|dp
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|snd_seq_oss_release
c_func
(paren
id|dp
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|odev_read
id|odev_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
id|seq_oss_devinfo_t
op_star
id|dp
suffix:semicolon
id|dp
op_assign
id|file-&gt;private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|dp
op_ne
l_int|NULL
comma
r_return
op_minus
id|EIO
)paren
suffix:semicolon
r_return
id|snd_seq_oss_read
c_func
(paren
id|dp
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|odev_write
id|odev_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
id|__user
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|offset
)paren
(brace
id|seq_oss_devinfo_t
op_star
id|dp
suffix:semicolon
id|dp
op_assign
id|file-&gt;private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|dp
op_ne
l_int|NULL
comma
r_return
op_minus
id|EIO
)paren
suffix:semicolon
r_return
id|snd_seq_oss_write
c_func
(paren
id|dp
comma
id|buf
comma
id|count
comma
id|file
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|odev_ioctl
id|odev_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|seq_oss_devinfo_t
op_star
id|dp
suffix:semicolon
r_int
id|err
suffix:semicolon
id|dp
op_assign
id|file-&gt;private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|dp
op_ne
l_int|NULL
comma
r_return
op_minus
id|EIO
)paren
suffix:semicolon
multiline_comment|/* FIXME: need to unlock BKL to allow preemption */
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|snd_seq_oss_ioctl
c_func
(paren
id|dp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|odev_poll
id|odev_poll
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
id|seq_oss_devinfo_t
op_star
id|dp
suffix:semicolon
id|dp
op_assign
id|file-&gt;private_data
suffix:semicolon
id|snd_assert
c_func
(paren
id|dp
op_ne
l_int|NULL
comma
r_return
l_int|0
)paren
suffix:semicolon
r_return
id|snd_seq_oss_poll
c_func
(paren
id|dp
comma
id|file
comma
id|wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * registration of sequencer minor device&n; */
DECL|variable|seq_oss_f_ops
r_static
r_struct
id|file_operations
id|seq_oss_f_ops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|read
op_assign
id|odev_read
comma
dot
id|write
op_assign
id|odev_write
comma
dot
id|open
op_assign
id|odev_open
comma
dot
id|release
op_assign
id|odev_release
comma
dot
id|poll
op_assign
id|odev_poll
comma
dot
id|ioctl
op_assign
id|odev_ioctl
comma
)brace
suffix:semicolon
DECL|variable|seq_oss_reg
r_static
id|snd_minor_t
id|seq_oss_reg
op_assign
(brace
dot
id|comment
op_assign
l_string|&quot;sequencer&quot;
comma
dot
id|f_ops
op_assign
op_amp
id|seq_oss_f_ops
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|register_device
id|register_device
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|snd_register_oss_device
c_func
(paren
id|SNDRV_OSS_DEVICE_TYPE_SEQUENCER
comma
l_int|NULL
comma
l_int|0
comma
op_amp
id|seq_oss_reg
comma
id|SNDRV_SEQ_OSS_DEVNAME
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t register device seq&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|snd_register_oss_device
c_func
(paren
id|SNDRV_OSS_DEVICE_TYPE_MUSIC
comma
l_int|NULL
comma
l_int|0
comma
op_amp
id|seq_oss_reg
comma
id|SNDRV_SEQ_OSS_DEVNAME
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;can&squot;t register device music&bslash;n&quot;
)paren
suffix:semicolon
id|snd_unregister_oss_device
c_func
(paren
id|SNDRV_OSS_DEVICE_TYPE_SEQUENCER
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|debug_printk
c_func
(paren
(paren
l_string|&quot;device registered&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|unregister_device
id|unregister_device
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|debug_printk
c_func
(paren
(paren
l_string|&quot;device unregistered&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_unregister_oss_device
c_func
(paren
id|SNDRV_OSS_DEVICE_TYPE_MUSIC
comma
l_int|NULL
comma
l_int|0
)paren
OL
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error unregister device music&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_unregister_oss_device
c_func
(paren
id|SNDRV_OSS_DEVICE_TYPE_SEQUENCER
comma
l_int|NULL
comma
l_int|0
)paren
OL
l_int|0
)paren
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;error unregister device seq&bslash;n&quot;
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * /proc interface&n; */
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|info_entry
r_static
id|snd_info_entry_t
op_star
id|info_entry
suffix:semicolon
r_static
r_void
DECL|function|info_read
id|info_read
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buf
)paren
(brace
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buf
comma
l_string|&quot;OSS sequencer emulation version %s&bslash;n&quot;
comma
id|SNDRV_SEQ_OSS_VERSION_STR
)paren
suffix:semicolon
id|snd_seq_oss_system_info_read
c_func
(paren
id|buf
)paren
suffix:semicolon
id|snd_seq_oss_synth_info_read
c_func
(paren
id|buf
)paren
suffix:semicolon
id|snd_seq_oss_midi_info_read
c_func
(paren
id|buf
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PROC_FS */
r_static
r_int
id|__init
DECL|function|register_proc
id|register_proc
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
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
id|SNDRV_SEQ_OSS_PROCNAME
comma
id|snd_seq_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|entry-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
l_int|1024
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|info_read
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
id|info_entry
op_assign
id|entry
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|unregister_proc
id|unregister_proc
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
r_if
c_cond
(paren
id|info_entry
)paren
id|snd_info_unregister
c_func
(paren
id|info_entry
)paren
suffix:semicolon
id|info_entry
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
)brace
eof
