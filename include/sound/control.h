macro_line|#ifndef __SOUND_CONTROL_H
DECL|macro|__SOUND_CONTROL_H
mdefine_line|#define __SOUND_CONTROL_H
multiline_comment|/*&n; *  Header file for control interface&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/asound.h&gt;
DECL|typedef|snd_aes_iec958_t
r_typedef
r_struct
id|sndrv_aes_iec958
id|snd_aes_iec958_t
suffix:semicolon
DECL|typedef|snd_ctl_card_info_t
r_typedef
r_struct
id|sndrv_ctl_card_info
id|snd_ctl_card_info_t
suffix:semicolon
DECL|typedef|snd_ctl_elem_type_t
r_typedef
r_enum
id|sndrv_ctl_elem_type
id|snd_ctl_elem_type_t
suffix:semicolon
DECL|typedef|snd_ctl_elem_iface_t
r_typedef
r_enum
id|sndrv_ctl_elem_iface
id|snd_ctl_elem_iface_t
suffix:semicolon
DECL|typedef|snd_ctl_elem_id_t
r_typedef
r_struct
id|sndrv_ctl_elem_id
id|snd_ctl_elem_id_t
suffix:semicolon
DECL|typedef|snd_ctl_elem_list_t
r_typedef
r_struct
id|sndrv_ctl_elem_list
id|snd_ctl_elem_list_t
suffix:semicolon
DECL|typedef|snd_ctl_elem_info_t
r_typedef
r_struct
id|sndrv_ctl_elem_info
id|snd_ctl_elem_info_t
suffix:semicolon
DECL|typedef|snd_ctl_elem_value_t
r_typedef
r_struct
id|sndrv_ctl_elem_value
id|snd_ctl_elem_value_t
suffix:semicolon
DECL|typedef|snd_ctl_event_type_t
r_typedef
r_enum
id|sndrv_ctl_event_type
id|snd_ctl_event_type_t
suffix:semicolon
DECL|typedef|snd_ctl_event_t
r_typedef
r_struct
id|sndrv_ctl_event
id|snd_ctl_event_t
suffix:semicolon
DECL|macro|snd_kcontrol_chip
mdefine_line|#define snd_kcontrol_chip(kcontrol) ((kcontrol)-&gt;private_data)
DECL|typedef|snd_kcontrol_info_t
r_typedef
r_int
(paren
id|snd_kcontrol_info_t
)paren
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_info_t
op_star
id|uinfo
)paren
suffix:semicolon
DECL|typedef|snd_kcontrol_get_t
r_typedef
r_int
(paren
id|snd_kcontrol_get_t
)paren
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
DECL|typedef|snd_kcontrol_put_t
r_typedef
r_int
(paren
id|snd_kcontrol_put_t
)paren
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
id|snd_ctl_elem_value_t
op_star
id|ucontrol
)paren
suffix:semicolon
DECL|struct|_snd_kcontrol_new
r_typedef
r_struct
id|_snd_kcontrol_new
(brace
DECL|member|iface
id|snd_ctl_elem_iface_t
id|iface
suffix:semicolon
multiline_comment|/* interface identifier */
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* device/client number */
DECL|member|subdevice
r_int
r_int
id|subdevice
suffix:semicolon
multiline_comment|/* subdevice (substream) number */
DECL|member|name
r_int
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* ASCII name of item */
DECL|member|index
r_int
r_int
id|index
suffix:semicolon
multiline_comment|/* index of item */
DECL|member|access
r_int
r_int
id|access
suffix:semicolon
multiline_comment|/* access rights */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* count of same elements */
DECL|member|info
id|snd_kcontrol_info_t
op_star
id|info
suffix:semicolon
DECL|member|get
id|snd_kcontrol_get_t
op_star
id|get
suffix:semicolon
DECL|member|put
id|snd_kcontrol_put_t
op_star
id|put
suffix:semicolon
DECL|member|private_value
r_int
r_int
id|private_value
suffix:semicolon
DECL|typedef|snd_kcontrol_new_t
)brace
id|snd_kcontrol_new_t
suffix:semicolon
DECL|struct|_snd_kcontrol_volatile
r_typedef
r_struct
id|_snd_kcontrol_volatile
(brace
DECL|member|owner
id|snd_ctl_file_t
op_star
id|owner
suffix:semicolon
multiline_comment|/* locked */
DECL|member|owner_pid
id|pid_t
id|owner_pid
suffix:semicolon
DECL|member|access
r_int
r_int
id|access
suffix:semicolon
multiline_comment|/* access rights */
DECL|typedef|snd_kcontrol_volatile_t
)brace
id|snd_kcontrol_volatile_t
suffix:semicolon
DECL|struct|_snd_kcontrol
r_struct
id|_snd_kcontrol
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of controls */
DECL|member|id
id|snd_ctl_elem_id_t
id|id
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* count of same elements */
DECL|member|info
id|snd_kcontrol_info_t
op_star
id|info
suffix:semicolon
DECL|member|get
id|snd_kcontrol_get_t
op_star
id|get
suffix:semicolon
DECL|member|put
id|snd_kcontrol_put_t
op_star
id|put
suffix:semicolon
DECL|member|private_value
r_int
r_int
id|private_value
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
)paren
suffix:semicolon
DECL|member|vd
id|snd_kcontrol_volatile_t
id|vd
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* volatile data */
)brace
suffix:semicolon
DECL|macro|snd_kcontrol
mdefine_line|#define snd_kcontrol(n) list_entry(n, snd_kcontrol_t, list)
DECL|struct|_snd_kctl_event
r_typedef
r_struct
id|_snd_kctl_event
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of events */
DECL|member|id
id|snd_ctl_elem_id_t
id|id
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|typedef|snd_kctl_event_t
)brace
id|snd_kctl_event_t
suffix:semicolon
DECL|macro|snd_kctl_event
mdefine_line|#define snd_kctl_event(n) list_entry(n, snd_kctl_event_t, list)
DECL|struct|_snd_ctl_file
r_struct
id|_snd_ctl_file
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* list of all control files */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|prefer_pcm_subdevice
r_int
id|prefer_pcm_subdevice
suffix:semicolon
DECL|member|prefer_rawmidi_subdevice
r_int
id|prefer_rawmidi_subdevice
suffix:semicolon
DECL|member|change_sleep
id|wait_queue_head_t
id|change_sleep
suffix:semicolon
DECL|member|read_lock
id|spinlock_t
id|read_lock
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|subscribed
r_int
id|subscribed
suffix:semicolon
multiline_comment|/* read interface is activated */
DECL|member|events
r_struct
id|list_head
id|events
suffix:semicolon
multiline_comment|/* waiting events for read */
)brace
suffix:semicolon
DECL|macro|snd_ctl_file
mdefine_line|#define snd_ctl_file(n) list_entry(n, snd_ctl_file_t, list)
DECL|typedef|snd_kctl_ioctl_func_t
r_typedef
r_int
(paren
op_star
id|snd_kctl_ioctl_func_t
)paren
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
suffix:semicolon
r_void
id|snd_ctl_notify
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|mask
comma
id|snd_ctl_elem_id_t
op_star
id|id
)paren
suffix:semicolon
id|snd_kcontrol_t
op_star
id|snd_ctl_new
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
comma
r_int
r_int
id|access
)paren
suffix:semicolon
id|snd_kcontrol_t
op_star
id|snd_ctl_new1
c_func
(paren
id|snd_kcontrol_new_t
op_star
id|kcontrolnew
comma
r_void
op_star
id|private_data
)paren
suffix:semicolon
r_void
id|snd_ctl_free_one
c_func
(paren
id|snd_kcontrol_t
op_star
id|kcontrol
)paren
suffix:semicolon
r_int
id|snd_ctl_add
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_kcontrol_t
op_star
id|kcontrol
)paren
suffix:semicolon
r_int
id|snd_ctl_remove
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_kcontrol_t
op_star
id|kcontrol
)paren
suffix:semicolon
r_int
id|snd_ctl_remove_id
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_ctl_elem_id_t
op_star
id|id
)paren
suffix:semicolon
r_int
id|snd_ctl_rename_id
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_ctl_elem_id_t
op_star
id|src_id
comma
id|snd_ctl_elem_id_t
op_star
id|dst_id
)paren
suffix:semicolon
id|snd_kcontrol_t
op_star
id|snd_ctl_find_numid
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|numid
)paren
suffix:semicolon
id|snd_kcontrol_t
op_star
id|snd_ctl_find_id
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_ctl_elem_id_t
op_star
id|id
)paren
suffix:semicolon
r_int
id|snd_ctl_register
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_ctl_disconnect
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_ctl_can_unregister
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_ctl_unregister
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_ctl_register_ioctl
c_func
(paren
id|snd_kctl_ioctl_func_t
id|fcn
)paren
suffix:semicolon
r_int
id|snd_ctl_unregister_ioctl
c_func
(paren
id|snd_kctl_ioctl_func_t
id|fcn
)paren
suffix:semicolon
multiline_comment|/* for ioctl32 */
r_int
id|snd_ctl_elem_read
c_func
(paren
id|snd_card_t
op_star
id|card
comma
id|snd_ctl_elem_value_t
op_star
id|control
)paren
suffix:semicolon
r_int
id|snd_ctl_elem_write
c_func
(paren
id|snd_ctl_file_t
op_star
id|file
comma
id|snd_ctl_elem_value_t
op_star
id|control
)paren
suffix:semicolon
DECL|function|snd_ctl_get_ioffnum
r_static
r_inline
r_int
r_int
id|snd_ctl_get_ioffnum
c_func
(paren
id|snd_kcontrol_t
op_star
id|kctl
comma
id|snd_ctl_elem_id_t
op_star
id|id
)paren
(brace
r_return
id|id-&gt;numid
op_minus
id|kctl-&gt;id.numid
suffix:semicolon
)brace
DECL|function|snd_ctl_get_ioffidx
r_static
r_inline
r_int
r_int
id|snd_ctl_get_ioffidx
c_func
(paren
id|snd_kcontrol_t
op_star
id|kctl
comma
id|snd_ctl_elem_id_t
op_star
id|id
)paren
(brace
r_return
id|id-&gt;index
op_minus
id|kctl-&gt;id.index
suffix:semicolon
)brace
DECL|function|snd_ctl_get_ioff
r_static
r_inline
r_int
r_int
id|snd_ctl_get_ioff
c_func
(paren
id|snd_kcontrol_t
op_star
id|kctl
comma
id|snd_ctl_elem_id_t
op_star
id|id
)paren
(brace
r_if
c_cond
(paren
id|id-&gt;numid
)paren
(brace
r_return
id|snd_ctl_get_ioffnum
c_func
(paren
id|kctl
comma
id|id
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|snd_ctl_get_ioffidx
c_func
(paren
id|kctl
comma
id|id
)paren
suffix:semicolon
)brace
)brace
DECL|function|snd_ctl_build_ioff
r_static
r_inline
id|snd_ctl_elem_id_t
op_star
id|snd_ctl_build_ioff
c_func
(paren
id|snd_ctl_elem_id_t
op_star
id|dst_id
comma
id|snd_kcontrol_t
op_star
id|src_kctl
comma
r_int
r_int
id|offset
)paren
(brace
op_star
id|dst_id
op_assign
id|src_kctl-&gt;id
suffix:semicolon
id|dst_id-&gt;index
op_add_assign
id|offset
suffix:semicolon
id|dst_id-&gt;numid
op_add_assign
id|offset
suffix:semicolon
r_return
id|dst_id
suffix:semicolon
)brace
macro_line|#endif&t;/* __SOUND_CONTROL_H */
eof
