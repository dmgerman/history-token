multiline_comment|/*&n; *  Hardware dependent layer&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;sound/minors.h&gt;
macro_line|#include &lt;sound/hwdep.h&gt;
macro_line|#include &lt;sound/info.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Jaroslav Kysela &lt;perex@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Hardware dependent layer&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|snd_hwdep_devices
id|snd_hwdep_t
op_star
id|snd_hwdep_devices
(braket
id|SNDRV_CARDS
op_star
id|SNDRV_MINOR_HWDEPS
)braket
suffix:semicolon
r_static
id|DECLARE_MUTEX
c_func
(paren
id|register_mutex
)paren
suffix:semicolon
r_static
r_int
id|snd_hwdep_free
c_func
(paren
id|snd_hwdep_t
op_star
id|hwdep
)paren
suffix:semicolon
r_static
r_int
id|snd_hwdep_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|snd_hwdep_dev_register
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
r_static
r_int
id|snd_hwdep_dev_unregister
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
suffix:semicolon
multiline_comment|/*&n;&n; */
DECL|function|snd_hwdep_llseek
r_static
id|loff_t
id|snd_hwdep_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
id|snd_hwdep_t
op_star
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|file-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;ops.llseek
)paren
r_return
id|hw-&gt;ops
dot
id|llseek
c_func
(paren
id|hw
comma
id|file
comma
id|offset
comma
id|orig
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_hwdep_read
r_static
id|ssize_t
id|snd_hwdep_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
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
id|snd_hwdep_t
op_star
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|file-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;ops.read
)paren
r_return
id|hw-&gt;ops
dot
id|read
c_func
(paren
id|hw
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_hwdep_write
r_static
id|ssize_t
id|snd_hwdep_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
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
id|snd_hwdep_t
op_star
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|file-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;ops.write
)paren
r_return
id|hw-&gt;ops
dot
id|write
c_func
(paren
id|hw
comma
id|buf
comma
id|count
comma
id|offset
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_hwdep_open
r_static
r_int
id|snd_hwdep_open
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
id|major
op_assign
id|major
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|cardnum
suffix:semicolon
r_int
id|device
suffix:semicolon
id|snd_hwdep_t
op_star
id|hw
suffix:semicolon
r_int
id|err
suffix:semicolon
id|wait_queue_t
id|wait
suffix:semicolon
r_switch
c_cond
(paren
id|major
)paren
(brace
r_case
id|CONFIG_SND_MAJOR
suffix:colon
id|cardnum
op_assign
id|SNDRV_MINOR_CARD
c_func
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
id|device
op_assign
id|SNDRV_MINOR_DEVICE
c_func
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
op_minus
id|SNDRV_MINOR_HWDEP
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_case
id|SOUND_MAJOR
suffix:colon
id|cardnum
op_assign
id|SNDRV_MINOR_OSS_CARD
c_func
(paren
id|minor
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
suffix:semicolon
id|device
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|cardnum
op_mod_assign
id|SNDRV_CARDS
suffix:semicolon
id|device
op_mod_assign
id|SNDRV_MINOR_HWDEPS
suffix:semicolon
id|hw
op_assign
id|snd_hwdep_devices
(braket
(paren
id|cardnum
op_star
id|SNDRV_MINOR_HWDEPS
)paren
op_plus
id|device
)braket
suffix:semicolon
id|snd_assert
c_func
(paren
id|hw
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hw-&gt;ops.open
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_if
c_cond
(paren
id|major
op_eq
id|SOUND_MAJOR
op_logical_and
id|hw-&gt;oss_type
OL
l_int|0
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
macro_line|#endif
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
id|hw-&gt;open_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hw-&gt;open_mutex
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
id|hw-&gt;exclusive
op_logical_and
id|hw-&gt;used
OG
l_int|0
)paren
(brace
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_break
suffix:semicolon
)brace
id|err
op_assign
id|hw-&gt;ops
dot
id|open
c_func
(paren
id|hw
comma
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
r_break
suffix:semicolon
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|err
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|set_current_state
c_func
(paren
id|TASK_RUNNING
)paren
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|hw-&gt;open_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
(brace
id|file-&gt;private_data
op_assign
id|hw
suffix:semicolon
id|hw-&gt;used
op_increment
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|hw-&gt;open_mutex
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|snd_hwdep_release
r_static
r_int
id|snd_hwdep_release
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
id|err
op_assign
op_minus
id|ENXIO
suffix:semicolon
id|snd_hwdep_t
op_star
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|file-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|hw-&gt;open_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;ops.release
)paren
(brace
id|err
op_assign
id|hw-&gt;ops
dot
id|release
c_func
(paren
id|hw
comma
id|file
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|hw-&gt;open_wait
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw-&gt;used
OG
l_int|0
)paren
id|hw-&gt;used
op_decrement
suffix:semicolon
id|up
c_func
(paren
op_amp
id|hw-&gt;open_mutex
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_hwdep_poll
r_static
r_int
r_int
id|snd_hwdep_poll
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
id|snd_hwdep_t
op_star
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|file-&gt;private_data
comma
r_return
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;ops.poll
)paren
r_return
id|hw-&gt;ops
dot
id|poll
c_func
(paren
id|hw
comma
id|file
comma
id|wait
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_hwdep_info
r_static
r_int
id|snd_hwdep_info
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_info_t
op_star
id|_info
)paren
(brace
id|snd_hwdep_info_t
id|info
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.card
op_assign
id|hw-&gt;card-&gt;number
suffix:semicolon
id|strncpy
c_func
(paren
id|info.id
comma
id|hw-&gt;id
comma
r_sizeof
(paren
id|info.id
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|info.name
comma
id|hw-&gt;name
comma
r_sizeof
(paren
id|info.name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|info.iface
op_assign
id|hw-&gt;iface
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|_info
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_hwdep_dsp_status
r_static
r_int
id|snd_hwdep_dsp_status
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_status_t
op_star
id|_info
)paren
(brace
id|snd_hwdep_dsp_status_t
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hw-&gt;ops.dsp_status
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
id|info.dsp_loaded
op_assign
id|hw-&gt;dsp_loaded
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|hw-&gt;ops
dot
id|dsp_status
c_func
(paren
id|hw
comma
op_amp
id|info
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
id|copy_to_user
c_func
(paren
id|_info
comma
op_amp
id|info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_hwdep_dsp_load
r_static
r_int
id|snd_hwdep_dsp_load
c_func
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_image_t
op_star
id|_info
)paren
(brace
id|snd_hwdep_dsp_image_t
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hw-&gt;ops.dsp_load
op_logical_or
op_logical_neg
id|hw-&gt;ops.dsp_status
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|info
comma
l_int|0
comma
r_sizeof
(paren
id|info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|info
comma
id|_info
comma
r_sizeof
(paren
id|info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* check whether the dsp was already loaded */
r_if
c_cond
(paren
id|hw-&gt;dsp_loaded
op_amp
(paren
l_int|1
op_lshift
id|info.index
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|info.image
comma
id|info.length
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|hw-&gt;ops
dot
id|dsp_load
c_func
(paren
id|hw
comma
op_amp
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|hw-&gt;dsp_loaded
op_or_assign
(paren
l_int|1
op_lshift
id|info.index
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_hwdep_ioctl
r_static
r_int
id|snd_hwdep_ioctl
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
id|snd_hwdep_t
op_star
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|file-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDRV_HWDEP_IOCTL_PVERSION
suffix:colon
r_return
id|put_user
c_func
(paren
id|SNDRV_HWDEP_VERSION
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDRV_HWDEP_IOCTL_INFO
suffix:colon
r_return
id|snd_hwdep_info
c_func
(paren
id|hw
comma
(paren
id|snd_hwdep_info_t
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDRV_HWDEP_IOCTL_DSP_STATUS
suffix:colon
r_return
id|snd_hwdep_dsp_status
c_func
(paren
id|hw
comma
(paren
id|snd_hwdep_dsp_status_t
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDRV_HWDEP_IOCTL_DSP_LOAD
suffix:colon
r_return
id|snd_hwdep_dsp_load
c_func
(paren
id|hw
comma
(paren
id|snd_hwdep_dsp_image_t
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw-&gt;ops.ioctl
)paren
r_return
id|hw-&gt;ops
dot
id|ioctl
c_func
(paren
id|hw
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|ENOTTY
suffix:semicolon
)brace
DECL|function|snd_hwdep_mmap
r_static
r_int
id|snd_hwdep_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
id|snd_hwdep_t
op_star
id|hw
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|file-&gt;private_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw-&gt;ops.mmap
)paren
r_return
id|hw-&gt;ops
dot
id|mmap
c_func
(paren
id|hw
comma
id|file
comma
id|vma
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
DECL|function|snd_hwdep_control_ioctl
r_static
r_int
id|snd_hwdep_control_ioctl
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_ctl_file_t
op_star
id|control
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
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
id|card-&gt;number
op_star
id|SNDRV_MINOR_HWDEPS
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE
suffix:colon
(brace
r_int
id|device
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|device
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|device
op_assign
id|device
OL
l_int|0
ques
c_cond
l_int|0
suffix:colon
id|device
op_plus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|device
OL
id|SNDRV_MINOR_HWDEPS
)paren
(brace
r_if
c_cond
(paren
id|snd_hwdep_devices
(braket
id|tmp
op_plus
id|device
)braket
)paren
r_break
suffix:semicolon
id|device
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|device
op_ge
id|SNDRV_MINOR_HWDEPS
)paren
id|device
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|device
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|SNDRV_CTL_IOCTL_HWDEP_INFO
suffix:colon
(brace
id|snd_hwdep_info_t
op_star
id|info
op_assign
(paren
id|snd_hwdep_info_t
op_star
)paren
id|arg
suffix:semicolon
r_int
id|device
suffix:semicolon
id|snd_hwdep_t
op_star
id|hwdep
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|device
comma
op_amp
id|info-&gt;device
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|device
OL
l_int|0
op_logical_or
id|device
op_ge
id|SNDRV_MINOR_HWDEPS
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|hwdep
op_assign
id|snd_hwdep_devices
(braket
id|tmp
op_plus
id|device
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hwdep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
id|snd_hwdep_info
c_func
(paren
id|hwdep
comma
id|info
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
multiline_comment|/*&n;&n; */
DECL|variable|snd_hwdep_f_ops
r_static
r_struct
id|file_operations
id|snd_hwdep_f_ops
op_assign
(brace
macro_line|#ifndef LINUX_2_2
dot
id|owner
op_assign
id|THIS_MODULE
comma
macro_line|#endif
dot
id|llseek
op_assign
id|snd_hwdep_llseek
comma
dot
id|read
op_assign
id|snd_hwdep_read
comma
dot
id|write
op_assign
id|snd_hwdep_write
comma
dot
id|open
op_assign
id|snd_hwdep_open
comma
dot
id|release
op_assign
id|snd_hwdep_release
comma
dot
id|poll
op_assign
id|snd_hwdep_poll
comma
dot
id|ioctl
op_assign
id|snd_hwdep_ioctl
comma
dot
id|mmap
op_assign
id|snd_hwdep_mmap
comma
)brace
suffix:semicolon
DECL|variable|snd_hwdep_reg
r_static
id|snd_minor_t
id|snd_hwdep_reg
op_assign
(brace
dot
id|comment
op_assign
l_string|&quot;hardware dependent&quot;
comma
dot
id|f_ops
op_assign
op_amp
id|snd_hwdep_f_ops
comma
)brace
suffix:semicolon
multiline_comment|/**&n; * snd_hwdep_new - create a new hwdep instance&n; * @card: the card instance&n; * @id: the id string&n; * @device: the device index (zero-based)&n; * @rhwdep: the pointer to store the new hwdep instance&n; *&n; * Creates a new hwdep instance with the given index on the card.&n; * The callbacks (hwdep-&gt;ops) must be set on the returned instance&n; * after this call manually by the caller.&n; *&n; * Returns zero if successful, or a negative error code on failure.&n; */
DECL|function|snd_hwdep_new
r_int
id|snd_hwdep_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_char
op_star
id|id
comma
r_int
id|device
comma
id|snd_hwdep_t
op_star
op_star
id|rhwdep
)paren
(brace
id|snd_hwdep_t
op_star
id|hwdep
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
id|snd_hwdep_dev_free
comma
dot
id|dev_register
op_assign
id|snd_hwdep_dev_register
comma
dot
id|dev_unregister
op_assign
id|snd_hwdep_dev_unregister
)brace
suffix:semicolon
id|snd_assert
c_func
(paren
id|rhwdep
op_ne
l_int|NULL
comma
r_return
op_minus
id|EINVAL
)paren
suffix:semicolon
op_star
id|rhwdep
op_assign
l_int|NULL
suffix:semicolon
id|snd_assert
c_func
(paren
id|card
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|hwdep
op_assign
id|snd_magic_kcalloc
c_func
(paren
id|snd_hwdep_t
comma
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwdep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|hwdep-&gt;card
op_assign
id|card
suffix:semicolon
id|hwdep-&gt;device
op_assign
id|device
suffix:semicolon
r_if
c_cond
(paren
id|id
)paren
(brace
id|strncpy
c_func
(paren
id|hwdep-&gt;id
comma
id|id
comma
r_sizeof
(paren
id|hwdep-&gt;id
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SND_OSSEMUL
id|hwdep-&gt;oss_type
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#endif
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
id|SNDRV_DEV_HWDEP
comma
id|hwdep
comma
op_amp
id|ops
)paren
)paren
OL
l_int|0
)paren
(brace
id|snd_hwdep_free
c_func
(paren
id|hwdep
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|hwdep-&gt;open_wait
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|hwdep-&gt;open_mutex
)paren
suffix:semicolon
op_star
id|rhwdep
op_assign
id|hwdep
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_hwdep_free
r_static
r_int
id|snd_hwdep_free
c_func
(paren
id|snd_hwdep_t
op_star
id|hwdep
)paren
(brace
id|snd_assert
c_func
(paren
id|hwdep
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwdep-&gt;private_free
)paren
id|hwdep
op_member_access_from_pointer
id|private_free
c_func
(paren
id|hwdep
)paren
suffix:semicolon
id|snd_magic_kfree
c_func
(paren
id|hwdep
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_hwdep_dev_free
r_static
r_int
id|snd_hwdep_dev_free
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|snd_hwdep_t
op_star
id|hwdep
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|device-&gt;device_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_return
id|snd_hwdep_free
c_func
(paren
id|hwdep
)paren
suffix:semicolon
)brace
DECL|function|snd_hwdep_dev_register
r_static
r_int
id|snd_hwdep_dev_register
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|snd_hwdep_t
op_star
id|hwdep
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|device-&gt;device_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
id|idx
comma
id|err
suffix:semicolon
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|idx
op_assign
(paren
id|hwdep-&gt;card-&gt;number
op_star
id|SNDRV_MINOR_HWDEPS
)paren
op_plus
id|hwdep-&gt;device
suffix:semicolon
r_if
c_cond
(paren
id|snd_hwdep_devices
(braket
id|idx
)braket
)paren
(brace
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|snd_hwdep_devices
(braket
id|idx
)braket
op_assign
id|hwdep
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;hwC%iD%i&quot;
comma
id|hwdep-&gt;card-&gt;number
comma
id|hwdep-&gt;device
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|snd_register_device
c_func
(paren
id|SNDRV_DEVICE_TYPE_HWDEP
comma
id|hwdep-&gt;card
comma
id|hwdep-&gt;device
comma
op_amp
id|snd_hwdep_reg
comma
id|name
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
l_string|&quot;unable to register hardware dependent device %i:%i&bslash;n&quot;
comma
id|hwdep-&gt;card-&gt;number
comma
id|hwdep-&gt;device
)paren
suffix:semicolon
id|snd_hwdep_devices
(braket
id|idx
)braket
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SND_OSSEMUL
id|hwdep-&gt;ossreg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hwdep-&gt;oss_type
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|hwdep-&gt;oss_type
op_eq
id|SNDRV_OSS_DEVICE_TYPE_DMFM
)paren
op_logical_and
(paren
id|hwdep-&gt;device
op_ne
l_int|0
)paren
)paren
(brace
id|snd_printk
(paren
id|KERN_WARNING
l_string|&quot;only hwdep device 0 can be registered as OSS direct FM device!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|snd_register_oss_device
c_func
(paren
id|hwdep-&gt;oss_type
comma
id|hwdep-&gt;card
comma
id|hwdep-&gt;device
comma
op_amp
id|snd_hwdep_reg
comma
id|hwdep-&gt;oss_dev
)paren
OL
l_int|0
)paren
(brace
id|snd_printk
c_func
(paren
id|KERN_ERR
l_string|&quot;unable to register OSS compatibility device %i:%i&bslash;n&quot;
comma
id|hwdep-&gt;card-&gt;number
comma
id|hwdep-&gt;device
)paren
suffix:semicolon
)brace
r_else
id|hwdep-&gt;ossreg
op_assign
l_int|1
suffix:semicolon
)brace
)brace
macro_line|#endif
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
DECL|function|snd_hwdep_dev_unregister
r_static
r_int
id|snd_hwdep_dev_unregister
c_func
(paren
id|snd_device_t
op_star
id|device
)paren
(brace
id|snd_hwdep_t
op_star
id|hwdep
op_assign
id|snd_magic_cast
c_func
(paren
id|snd_hwdep_t
comma
id|device-&gt;device_data
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|snd_assert
c_func
(paren
id|hwdep
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENXIO
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
id|idx
op_assign
(paren
id|hwdep-&gt;card-&gt;number
op_star
id|SNDRV_MINOR_HWDEPS
)paren
op_plus
id|hwdep-&gt;device
suffix:semicolon
r_if
c_cond
(paren
id|snd_hwdep_devices
(braket
id|idx
)braket
op_ne
id|hwdep
)paren
(brace
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_if
c_cond
(paren
id|hwdep-&gt;ossreg
)paren
id|snd_unregister_oss_device
c_func
(paren
id|hwdep-&gt;oss_type
comma
id|hwdep-&gt;card
comma
id|hwdep-&gt;device
)paren
suffix:semicolon
macro_line|#endif
id|snd_unregister_device
c_func
(paren
id|SNDRV_DEVICE_TYPE_HWDEP
comma
id|hwdep-&gt;card
comma
id|hwdep-&gt;device
)paren
suffix:semicolon
id|snd_hwdep_devices
(braket
id|idx
)braket
op_assign
l_int|NULL
suffix:semicolon
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
r_return
id|snd_hwdep_free
c_func
(paren
id|hwdep
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Info interface&n; */
DECL|function|snd_hwdep_proc_read
r_static
r_void
id|snd_hwdep_proc_read
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
id|snd_hwdep_t
op_star
id|hwdep
suffix:semicolon
id|down
c_func
(paren
op_amp
id|register_mutex
)paren
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
op_star
id|SNDRV_MINOR_HWDEPS
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|hwdep
op_assign
id|snd_hwdep_devices
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hwdep
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
id|snd_iprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%02i-%02i: %s&bslash;n&quot;
comma
id|idx
op_div
id|SNDRV_MINOR_HWDEPS
comma
id|idx
op_mod
id|SNDRV_MINOR_HWDEPS
comma
id|hwdep-&gt;name
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|register_mutex
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  ENTRY functions&n; */
DECL|variable|snd_hwdep_proc_entry
r_static
id|snd_info_entry_t
op_star
id|snd_hwdep_proc_entry
op_assign
l_int|NULL
suffix:semicolon
DECL|function|alsa_hwdep_init
r_static
r_int
id|__init
id|alsa_hwdep_init
c_func
(paren
r_void
)paren
(brace
id|snd_info_entry_t
op_star
id|entry
suffix:semicolon
id|memset
c_func
(paren
id|snd_hwdep_devices
comma
l_int|0
comma
r_sizeof
(paren
id|snd_hwdep_devices
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|entry
op_assign
id|snd_info_create_module_entry
c_func
(paren
id|THIS_MODULE
comma
l_string|&quot;hwdep&quot;
comma
l_int|NULL
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|entry-&gt;content
op_assign
id|SNDRV_INFO_CONTENT_TEXT
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
l_int|512
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|snd_hwdep_proc_read
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
id|snd_hwdep_proc_entry
op_assign
id|entry
suffix:semicolon
id|snd_ctl_register_ioctl
c_func
(paren
id|snd_hwdep_control_ioctl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alsa_hwdep_exit
r_static
r_void
id|__exit
id|alsa_hwdep_exit
c_func
(paren
r_void
)paren
(brace
id|snd_ctl_unregister_ioctl
c_func
(paren
id|snd_hwdep_control_ioctl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|snd_hwdep_proc_entry
)paren
(brace
id|snd_info_unregister
c_func
(paren
id|snd_hwdep_proc_entry
)paren
suffix:semicolon
id|snd_hwdep_proc_entry
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|module_init
c_func
(paren
id|alsa_hwdep_init
)paren
id|module_exit
c_func
(paren
id|alsa_hwdep_exit
)paren
id|EXPORT_SYMBOL
c_func
(paren
id|snd_hwdep_new
)paren
suffix:semicolon
eof
