multiline_comment|/*&n; *   32bit -&gt; 64bit ioctl wrapper for control API&n; *   Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/driver.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;sound/core.h&gt;
macro_line|#include &lt;sound/control.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ioctl32.h&quot;
multiline_comment|/*&n; * register/unregister mappers&n; * exported for other modules&n; */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;ioctl32 wrapper for ALSA&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_int
id|register_ioctl32_conversion
c_func
(paren
r_int
r_int
id|cmd
comma
r_int
(paren
op_star
id|handler
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|file
op_star
)paren
)paren
suffix:semicolon
r_int
id|unregister_ioctl32_conversion
c_func
(paren
r_int
r_int
id|cmd
)paren
suffix:semicolon
DECL|function|snd_ioctl32_register
r_int
id|snd_ioctl32_register
c_func
(paren
r_struct
id|ioctl32_mapper
op_star
id|mappers
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|ioctl32_mapper
op_star
id|m
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
id|mappers
suffix:semicolon
id|m-&gt;cmd
suffix:semicolon
id|m
op_increment
)paren
(brace
id|err
op_assign
id|register_ioctl32_conversion
c_func
(paren
id|m-&gt;cmd
comma
id|m-&gt;handler
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
id|m-&gt;registered
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_ioctl32_unregister
r_void
id|snd_ioctl32_unregister
c_func
(paren
r_struct
id|ioctl32_mapper
op_star
id|mappers
)paren
(brace
r_struct
id|ioctl32_mapper
op_star
id|m
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
id|mappers
suffix:semicolon
id|m-&gt;cmd
suffix:semicolon
id|m
op_increment
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;registered
)paren
(brace
id|unregister_ioctl32_conversion
c_func
(paren
id|m-&gt;cmd
)paren
suffix:semicolon
id|m-&gt;registered
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * compatible wrapper&n; */
DECL|function|snd_ioctl32_compat
r_int
id|snd_ioctl32_compat
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_op
op_logical_or
op_logical_neg
id|filp-&gt;f_op-&gt;ioctl
)paren
r_return
op_minus
id|ENOTTY
suffix:semicolon
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|filp-&gt;f_dentry-&gt;d_inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Controls&n; */
DECL|struct|sndrv_ctl_elem_list32
r_struct
id|sndrv_ctl_elem_list32
(brace
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|space
id|u32
id|space
suffix:semicolon
DECL|member|used
id|u32
id|used
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|pids
id|u32
id|pids
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|50
)braket
suffix:semicolon
)brace
multiline_comment|/* don&squot;t set packed attribute here */
suffix:semicolon
DECL|macro|CVT_sndrv_ctl_elem_list
mdefine_line|#define CVT_sndrv_ctl_elem_list()&bslash;&n;{&bslash;&n;&t;COPY(offset);&bslash;&n;&t;COPY(space);&bslash;&n;&t;COPY(used);&bslash;&n;&t;COPY(count);&bslash;&n;&t;CPTR(pids);&bslash;&n;}
DECL|function|_snd_ioctl32_ctl_elem_list
r_static
r_int
id|_snd_ioctl32_ctl_elem_list
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|native_ctl
)paren
(brace
r_struct
id|sndrv_ctl_elem_list32
id|data32
suffix:semicolon
r_struct
id|sndrv_ctl_elem_list
id|data
suffix:semicolon
id|mm_segment_t
id|oldseg
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data32
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|data32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
id|data.offset
op_assign
id|data32.offset
suffix:semicolon
id|data.space
op_assign
id|data32.space
suffix:semicolon
id|data.used
op_assign
id|data32.used
suffix:semicolon
id|data.count
op_assign
id|data32.count
suffix:semicolon
id|data.pids
op_assign
id|A
c_func
(paren
id|data32.pids
)paren
suffix:semicolon
id|oldseg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
comma
id|file
comma
id|native_ctl
comma
(paren
r_int
r_int
)paren
op_amp
id|data
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldseg
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
multiline_comment|/* copy the result */
id|data32.offset
op_assign
id|data.offset
suffix:semicolon
id|data32.space
op_assign
id|data.space
suffix:semicolon
id|data32.used
op_assign
id|data.used
suffix:semicolon
id|data32.count
op_assign
id|data.count
suffix:semicolon
singleline_comment|//data.pids = data.pids;
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|data32
comma
r_sizeof
(paren
id|data32
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
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|ctl_elem_list
comma
id|ctl_elem_list
comma
id|SNDRV_CTL_IOCTL_ELEM_LIST
)paren
suffix:semicolon
multiline_comment|/*&n; * control element info&n; * it uses union, so the things are not easy..&n; */
DECL|struct|sndrv_ctl_elem_info32
r_struct
id|sndrv_ctl_elem_info32
(brace
DECL|member|id
r_struct
id|sndrv_ctl_elem_id
id|id
suffix:semicolon
singleline_comment|// the size of struct is same
DECL|member|type
id|s32
id|type
suffix:semicolon
DECL|member|access
id|u32
id|access
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|owner
id|s32
id|owner
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|min
id|s32
id|min
suffix:semicolon
DECL|member|max
id|s32
id|max
suffix:semicolon
DECL|member|step
id|s32
id|step
suffix:semicolon
DECL|member|integer
)brace
id|integer
suffix:semicolon
r_struct
(brace
DECL|member|min
id|u64
id|min
suffix:semicolon
DECL|member|max
id|u64
id|max
suffix:semicolon
DECL|member|step
id|u64
id|step
suffix:semicolon
DECL|member|integer64
)brace
id|integer64
suffix:semicolon
r_struct
(brace
DECL|member|items
id|u32
id|items
suffix:semicolon
DECL|member|item
id|u32
id|item
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|enumerated
)brace
id|enumerated
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|value
)brace
id|value
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|64
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|function|_snd_ioctl32_ctl_elem_info
r_static
r_int
id|_snd_ioctl32_ctl_elem_info
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|native_ctl
)paren
(brace
r_struct
id|sndrv_ctl_elem_info
id|data
suffix:semicolon
r_struct
id|sndrv_ctl_elem_info32
id|data32
suffix:semicolon
r_int
id|err
suffix:semicolon
id|mm_segment_t
id|oldseg
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data32
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|data32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|data
comma
l_int|0
comma
r_sizeof
(paren
id|data
)paren
)paren
suffix:semicolon
id|data.id
op_assign
id|data32.id
suffix:semicolon
multiline_comment|/* we need to copy the item index.&n;&t; * hope this doesn&squot;t break anything..&n;&t; */
id|data.value.enumerated.item
op_assign
id|data32.value.enumerated.item
suffix:semicolon
id|oldseg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
comma
id|file
comma
id|native_ctl
comma
(paren
r_int
r_int
)paren
op_amp
id|data
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldseg
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
multiline_comment|/* restore info to 32bit */
id|data32.id
op_assign
id|data.id
suffix:semicolon
id|data32.type
op_assign
id|data.type
suffix:semicolon
id|data32.access
op_assign
id|data.access
suffix:semicolon
id|data32.count
op_assign
id|data.count
suffix:semicolon
id|data32.owner
op_assign
id|data.owner
suffix:semicolon
r_switch
c_cond
(paren
id|data.type
)paren
(brace
r_case
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
suffix:colon
r_case
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:colon
id|data32.value.integer.min
op_assign
id|data.value.integer.min
suffix:semicolon
id|data32.value.integer.max
op_assign
id|data.value.integer.max
suffix:semicolon
id|data32.value.integer.step
op_assign
id|data.value.integer.step
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_INTEGER64
suffix:colon
id|data32.value.integer64.min
op_assign
id|data.value.integer64.min
suffix:semicolon
id|data32.value.integer64.max
op_assign
id|data.value.integer64.max
suffix:semicolon
id|data32.value.integer64.step
op_assign
id|data.value.integer64.step
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_ENUMERATED
suffix:colon
id|data32.value.enumerated.items
op_assign
id|data.value.enumerated.items
suffix:semicolon
id|data32.value.enumerated.item
op_assign
id|data.value.enumerated.item
suffix:semicolon
id|memcpy
c_func
(paren
id|data32.value.enumerated.name
comma
id|data.value.enumerated.name
comma
r_sizeof
(paren
id|data.value.enumerated.name
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|data32
comma
r_sizeof
(paren
id|data32
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
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|ctl_elem_info
comma
id|ctl_elem_info
comma
id|SNDRV_CTL_IOCTL_ELEM_INFO
)paren
suffix:semicolon
DECL|struct|sndrv_ctl_elem_value32
r_struct
id|sndrv_ctl_elem_value32
(brace
DECL|member|id
r_struct
id|sndrv_ctl_elem_id
id|id
suffix:semicolon
DECL|member|indirect
r_int
r_int
id|indirect
suffix:semicolon
multiline_comment|/* bit-field causes misalignment */
r_union
(brace
r_union
(brace
DECL|member|value
id|s32
id|value
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|value_ptr
id|u32
id|value_ptr
suffix:semicolon
DECL|member|integer
)brace
id|integer
suffix:semicolon
r_union
(brace
DECL|member|value
id|s64
id|value
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|value_ptr
id|u32
id|value_ptr
suffix:semicolon
DECL|member|integer64
)brace
id|integer64
suffix:semicolon
r_union
(brace
DECL|member|item
id|u32
id|item
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|item_ptr
id|u32
id|item_ptr
suffix:semicolon
DECL|member|enumerated
)brace
id|enumerated
suffix:semicolon
r_union
(brace
DECL|member|data
r_int
r_char
id|data
(braket
l_int|512
)braket
suffix:semicolon
DECL|member|data_ptr
id|u32
id|data_ptr
suffix:semicolon
DECL|member|bytes
)brace
id|bytes
suffix:semicolon
DECL|member|iec958
r_struct
id|sndrv_aes_iec958
id|iec958
suffix:semicolon
DECL|member|value
)brace
id|value
suffix:semicolon
DECL|member|reserved
r_int
r_char
id|reserved
(braket
l_int|128
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* hmm, it&squot;s so hard to retrieve the value type from the control id.. */
DECL|function|get_ctl_type
r_static
r_int
id|get_ctl_type
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|snd_ctl_elem_id_t
op_star
id|id
)paren
(brace
id|snd_ctl_file_t
op_star
id|ctl
suffix:semicolon
id|snd_kcontrol_t
op_star
id|kctl
suffix:semicolon
id|snd_ctl_elem_info_t
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ctl
op_assign
id|file-&gt;private_data
suffix:semicolon
id|down_read
c_func
(paren
op_amp
id|ctl-&gt;card-&gt;controls_rwsem
)paren
suffix:semicolon
id|kctl
op_assign
id|snd_ctl_find_id
c_func
(paren
id|ctl-&gt;card
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kctl
)paren
(brace
id|up_read
c_func
(paren
op_amp
id|ctl-&gt;card-&gt;controls_rwsem
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|info.id
op_assign
op_star
id|id
suffix:semicolon
id|err
op_assign
id|kctl
op_member_access_from_pointer
id|info
c_func
(paren
id|kctl
comma
op_amp
id|info
)paren
suffix:semicolon
id|up_read
c_func
(paren
op_amp
id|ctl-&gt;card-&gt;controls_rwsem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
)paren
id|err
op_assign
id|info.type
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|_snd_ioctl32_ctl_elem_value
r_static
r_int
id|_snd_ioctl32_ctl_elem_value
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|native_ctl
)paren
(brace
r_struct
id|sndrv_ctl_elem_value
op_star
id|data
suffix:semicolon
r_struct
id|sndrv_ctl_elem_value32
op_star
id|data32
suffix:semicolon
r_int
id|err
comma
id|i
suffix:semicolon
r_int
id|type
suffix:semicolon
id|mm_segment_t
id|oldseg
suffix:semicolon
multiline_comment|/* FIXME: check the sane ioctl.. */
id|data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|data32
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data32
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|NULL
op_logical_or
id|data32
op_eq
l_int|NULL
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|__end
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|data32
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
op_star
id|data32
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|__end
suffix:semicolon
)brace
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|data
)paren
)paren
suffix:semicolon
id|data-&gt;id
op_assign
id|data32-&gt;id
suffix:semicolon
id|data-&gt;indirect
op_assign
id|data32-&gt;indirect
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;indirect
)paren
multiline_comment|/* FIXME: this is not correct for long arrays */
id|data-&gt;value.integer.value_ptr
op_assign
(paren
r_void
op_star
)paren
id|TO_PTR
c_func
(paren
id|data32-&gt;value.integer.value_ptr
)paren
suffix:semicolon
id|type
op_assign
id|get_ctl_type
c_func
(paren
id|file
comma
op_amp
id|data-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
(brace
id|err
op_assign
id|type
suffix:semicolon
r_goto
id|__end
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;indirect
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
suffix:colon
r_case
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
id|i
op_increment
)paren
id|data-&gt;value.integer.value
(braket
id|i
)braket
op_assign
id|data32-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_INTEGER64
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|64
suffix:semicolon
id|i
op_increment
)paren
id|data-&gt;value.integer64.value
(braket
id|i
)braket
op_assign
id|data32-&gt;value.integer64.value
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_ENUMERATED
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
id|i
op_increment
)paren
id|data-&gt;value.enumerated.item
(braket
id|i
)braket
op_assign
id|data32-&gt;value.enumerated.item
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_BYTES
suffix:colon
id|memcpy
c_func
(paren
id|data-&gt;value.bytes.data
comma
id|data32-&gt;value.bytes.data
comma
r_sizeof
(paren
id|data-&gt;value.bytes.data
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_IEC958
suffix:colon
id|data-&gt;value.iec958
op_assign
id|data32-&gt;value.iec958
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;unknown type %d&bslash;n&quot;
comma
id|type
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|oldseg
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|file-&gt;f_op
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode
comma
id|file
comma
id|native_ctl
comma
(paren
r_int
r_int
)paren
id|data
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldseg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|__end
suffix:semicolon
multiline_comment|/* restore info to 32bit */
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;indirect
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|SNDRV_CTL_ELEM_TYPE_BOOLEAN
suffix:colon
r_case
id|SNDRV_CTL_ELEM_TYPE_INTEGER
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
id|i
op_increment
)paren
id|data32-&gt;value.integer.value
(braket
id|i
)braket
op_assign
id|data-&gt;value.integer.value
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_INTEGER64
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|64
suffix:semicolon
id|i
op_increment
)paren
id|data32-&gt;value.integer64.value
(braket
id|i
)braket
op_assign
id|data-&gt;value.integer64.value
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_ENUMERATED
suffix:colon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|128
suffix:semicolon
id|i
op_increment
)paren
id|data32-&gt;value.enumerated.item
(braket
id|i
)braket
op_assign
id|data-&gt;value.enumerated.item
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_BYTES
suffix:colon
id|memcpy
c_func
(paren
id|data32-&gt;value.bytes.data
comma
id|data-&gt;value.bytes.data
comma
r_sizeof
(paren
id|data-&gt;value.bytes.data
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDRV_CTL_ELEM_TYPE_IEC958
suffix:colon
id|data32-&gt;value.iec958
op_assign
id|data-&gt;value.iec958
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
id|err
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
id|data32
comma
r_sizeof
(paren
op_star
id|data32
)paren
)paren
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
id|__end
suffix:colon
r_if
c_cond
(paren
id|data32
)paren
id|kfree
c_func
(paren
id|data32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|ctl_elem_read
comma
id|ctl_elem_value
comma
id|SNDRV_CTL_IOCTL_ELEM_READ
)paren
suffix:semicolon
id|DEFINE_ALSA_IOCTL_ENTRY
c_func
(paren
id|ctl_elem_write
comma
id|ctl_elem_value
comma
id|SNDRV_CTL_IOCTL_ELEM_WRITE
)paren
suffix:semicolon
multiline_comment|/*&n; */
DECL|macro|AP
mdefine_line|#define AP(x) snd_ioctl32_##x
r_enum
(brace
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_LIST32
id|SNDRV_CTL_IOCTL_ELEM_LIST32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x10
comma
r_struct
id|sndrv_ctl_elem_list32
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_INFO32
id|SNDRV_CTL_IOCTL_ELEM_INFO32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x11
comma
r_struct
id|sndrv_ctl_elem_info32
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_READ32
id|SNDRV_CTL_IOCTL_ELEM_READ32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x12
comma
r_struct
id|sndrv_ctl_elem_value32
)paren
comma
DECL|enumerator|SNDRV_CTL_IOCTL_ELEM_WRITE32
id|SNDRV_CTL_IOCTL_ELEM_WRITE32
op_assign
id|_IOWR
c_func
(paren
l_char|&squot;U&squot;
comma
l_int|0x13
comma
r_struct
id|sndrv_ctl_elem_value32
)paren
comma
)brace
suffix:semicolon
DECL|variable|control_mappers
r_static
r_struct
id|ioctl32_mapper
id|control_mappers
(braket
)braket
op_assign
(brace
multiline_comment|/* controls (without rawmidi, hwdep, timer releated ones) */
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_PVERSION
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_CARD_INFO
)paren
comma
(brace
id|SNDRV_CTL_IOCTL_ELEM_LIST32
comma
id|AP
c_func
(paren
id|ctl_elem_list
)paren
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_ELEM_INFO32
comma
id|AP
c_func
(paren
id|ctl_elem_info
)paren
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_ELEM_READ32
comma
id|AP
c_func
(paren
id|ctl_elem_read
)paren
)brace
comma
(brace
id|SNDRV_CTL_IOCTL_ELEM_WRITE32
comma
id|AP
c_func
(paren
id|ctl_elem_write
)paren
)brace
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_ELEM_LOCK
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_ELEM_UNLOCK
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_SUBSCRIBE_EVENTS
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_HWDEP_INFO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_PCM_INFO
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_PCM_PREFER_SUBDEVICE
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_POWER
)paren
comma
id|MAP_COMPAT
c_func
(paren
id|SNDRV_CTL_IOCTL_POWER_STATE
)paren
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; */
r_extern
r_struct
id|ioctl32_mapper
id|pcm_mappers
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|ioctl32_mapper
id|rawmidi_mappers
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|ioctl32_mapper
id|timer_mappers
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|ioctl32_mapper
id|hwdep_mappers
(braket
)braket
suffix:semicolon
macro_line|#if defined(CONFIG_SND_SEQUENCER) || (defined(MODULE) &amp;&amp; defined(CONFIG_SND_SEQUENCER_MODULE))
r_extern
r_struct
id|ioctl32_mapper
id|seq_mappers
(braket
)braket
suffix:semicolon
macro_line|#endif
DECL|function|snd_ioctl32_done
r_static
r_void
id|snd_ioctl32_done
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SND_SEQUENCER) || (defined(MODULE) &amp;&amp; defined(CONFIG_SND_SEQUENCER_MODULE))
id|snd_ioctl32_unregister
c_func
(paren
id|seq_mappers
)paren
suffix:semicolon
macro_line|#endif
id|snd_ioctl32_unregister
c_func
(paren
id|hwdep_mappers
)paren
suffix:semicolon
id|snd_ioctl32_unregister
c_func
(paren
id|timer_mappers
)paren
suffix:semicolon
id|snd_ioctl32_unregister
c_func
(paren
id|rawmidi_mappers
)paren
suffix:semicolon
id|snd_ioctl32_unregister
c_func
(paren
id|pcm_mappers
)paren
suffix:semicolon
id|snd_ioctl32_unregister
c_func
(paren
id|control_mappers
)paren
suffix:semicolon
)brace
DECL|function|snd_ioctl32_init
r_static
r_int
id|__init
id|snd_ioctl32_init
c_func
(paren
r_void
)paren
(brace
id|snd_ioctl32_register
c_func
(paren
id|control_mappers
)paren
suffix:semicolon
id|snd_ioctl32_register
c_func
(paren
id|pcm_mappers
)paren
suffix:semicolon
id|snd_ioctl32_register
c_func
(paren
id|rawmidi_mappers
)paren
suffix:semicolon
id|snd_ioctl32_register
c_func
(paren
id|timer_mappers
)paren
suffix:semicolon
id|snd_ioctl32_register
c_func
(paren
id|hwdep_mappers
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SND_SEQUENCER) || (defined(MODULE) &amp;&amp; defined(CONFIG_SND_SEQUENCER_MODULE))
id|snd_ioctl32_register
c_func
(paren
id|seq_mappers
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|snd_ioctl32_init
)paren
id|module_exit
c_func
(paren
id|snd_ioctl32_done
)paren
eof
