macro_line|#ifndef __SOUND_TIMER_H
DECL|macro|__SOUND_TIMER_H
mdefine_line|#define __SOUND_TIMER_H
multiline_comment|/*&n; *  Timer abstract layer&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/asound.h&gt;
DECL|typedef|snd_timer_class_t
r_typedef
r_enum
id|sndrv_timer_class
id|snd_timer_class_t
suffix:semicolon
DECL|typedef|snd_timer_slave_class_t
r_typedef
r_enum
id|sndrv_timer_slave_class
id|snd_timer_slave_class_t
suffix:semicolon
DECL|typedef|snd_timer_global_t
r_typedef
r_enum
id|sndrv_timer_global
id|snd_timer_global_t
suffix:semicolon
DECL|typedef|snd_timer_id_t
r_typedef
r_struct
id|sndrv_timer_id
id|snd_timer_id_t
suffix:semicolon
DECL|typedef|snd_timer_select_t
r_typedef
r_struct
id|sndrv_timer_select
id|snd_timer_select_t
suffix:semicolon
DECL|typedef|snd_timer_info_t
r_typedef
r_struct
id|sndrv_timer_info
id|snd_timer_info_t
suffix:semicolon
DECL|typedef|snd_timer_params_t
r_typedef
r_struct
id|sndrv_timer_params
id|snd_timer_params_t
suffix:semicolon
DECL|typedef|snd_timer_status_t
r_typedef
r_struct
id|sndrv_timer_status
id|snd_timer_status_t
suffix:semicolon
DECL|typedef|snd_timer_read_t
r_typedef
r_struct
id|sndrv_timer_read
id|snd_timer_read_t
suffix:semicolon
DECL|macro|_snd_timer_chip
mdefine_line|#define _snd_timer_chip(timer) ((timer)-&gt;private_data)
DECL|macro|snd_timer_chip
mdefine_line|#define snd_timer_chip(timer) snd_magic_cast1(chip_t, _snd_timer_chip(timer), return -ENXIO)
DECL|macro|SNDRV_TIMER_DEVICES
mdefine_line|#define SNDRV_TIMER_DEVICES&t;16
DECL|macro|SNDRV_TIMER_DEV_FLG_PCM
mdefine_line|#define SNDRV_TIMER_DEV_FLG_PCM&t;0x10000000
DECL|macro|SNDRV_TIMER_HW_AUTO
mdefine_line|#define SNDRV_TIMER_HW_AUTO&t;0x00000001&t;/* auto trigger is supported */
DECL|macro|SNDRV_TIMER_HW_STOP
mdefine_line|#define SNDRV_TIMER_HW_STOP&t;0x00000002&t;/* call stop before start */
DECL|macro|SNDRV_TIMER_HW_SLAVE
mdefine_line|#define SNDRV_TIMER_HW_SLAVE&t;0x00000004&t;/* only slave timer (variable resolution) */
DECL|macro|SNDRV_TIMER_HW_FIRST
mdefine_line|#define SNDRV_TIMER_HW_FIRST&t;0x00000008&t;/* first tick can be incomplete */
DECL|macro|SNDRV_TIMER_IFLG_SLAVE
mdefine_line|#define SNDRV_TIMER_IFLG_SLAVE&t;0x00000001
DECL|macro|SNDRV_TIMER_IFLG_RUNNING
mdefine_line|#define SNDRV_TIMER_IFLG_RUNNING&t;0x00000002
DECL|macro|SNDRV_TIMER_IFLG_START
mdefine_line|#define SNDRV_TIMER_IFLG_START&t;0x00000004
DECL|macro|SNDRV_TIMER_IFLG_AUTO
mdefine_line|#define SNDRV_TIMER_IFLG_AUTO&t;0x00000008&t;/* auto restart */
DECL|macro|SNDRV_TIMER_FLG_SYSTEM
mdefine_line|#define SNDRV_TIMER_FLG_SYSTEM&t;0x00000001&t;/* system timer */
DECL|macro|SNDRV_TIMER_FLG_CHANGE
mdefine_line|#define SNDRV_TIMER_FLG_CHANGE&t;0x00000002
DECL|macro|SNDRV_TIMER_FLG_RESCHED
mdefine_line|#define SNDRV_TIMER_FLG_RESCHED&t;0x00000004&t;/* need reschedule */
DECL|typedef|snd_timer_callback_t
r_typedef
r_void
(paren
op_star
id|snd_timer_callback_t
)paren
(paren
id|snd_timer_instance_t
op_star
id|timeri
comma
r_int
r_int
id|ticks
comma
r_int
r_int
id|resolution
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|struct|_snd_timer_hardware
r_struct
id|_snd_timer_hardware
(brace
multiline_comment|/* -- must be filled with low-level driver */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|resolution
r_int
r_int
id|resolution
suffix:semicolon
multiline_comment|/* average timer resolution for one tick in nsec */
DECL|member|ticks
r_int
r_int
id|ticks
suffix:semicolon
multiline_comment|/* max timer ticks per interrupt */
multiline_comment|/* -- low-level functions -- */
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
DECL|member|c_resolution
r_int
r_int
(paren
op_star
id|c_resolution
)paren
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
DECL|member|start
r_int
(paren
op_star
id|start
)paren
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
DECL|member|stop
r_int
(paren
op_star
id|stop
)paren
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_timer
r_struct
id|_snd_timer
(brace
DECL|member|tmr_class
id|snd_timer_class_t
id|tmr_class
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|tmr_device
r_int
id|tmr_device
suffix:semicolon
DECL|member|tmr_subdevice
r_int
id|tmr_subdevice
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* running instances */
DECL|member|sticks
r_int
r_int
id|sticks
suffix:semicolon
multiline_comment|/* schedule ticks */
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
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
DECL|member|hw
r_struct
id|_snd_timer_hardware
id|hw
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|device_list
r_struct
id|list_head
id|device_list
suffix:semicolon
DECL|member|open_list_head
r_struct
id|list_head
id|open_list_head
suffix:semicolon
DECL|member|active_list_head
r_struct
id|list_head
id|active_list_head
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_snd_timer_instance
r_struct
id|_snd_timer_instance
(brace
DECL|member|timer
id|snd_timer_t
op_star
id|timer
suffix:semicolon
DECL|member|owner
r_char
op_star
id|owner
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
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
id|snd_timer_instance_t
op_star
id|ti
)paren
suffix:semicolon
DECL|member|callback
id|snd_timer_callback_t
id|callback
suffix:semicolon
DECL|member|callback_data
r_void
op_star
id|callback_data
suffix:semicolon
DECL|member|ticks
r_int
r_int
id|ticks
suffix:semicolon
DECL|member|cticks
r_int
r_int
id|cticks
suffix:semicolon
DECL|member|lost
r_int
r_int
id|lost
suffix:semicolon
multiline_comment|/* lost ticks */
DECL|member|slave_class
id|snd_timer_slave_class_t
id|slave_class
suffix:semicolon
DECL|member|slave_id
r_int
r_int
id|slave_id
suffix:semicolon
DECL|member|open_list
r_struct
id|list_head
id|open_list
suffix:semicolon
DECL|member|active_list
r_struct
id|list_head
id|active_list
suffix:semicolon
DECL|member|slave_list_head
r_struct
id|list_head
id|slave_list_head
suffix:semicolon
DECL|member|slave_active_head
r_struct
id|list_head
id|slave_active_head
suffix:semicolon
DECL|member|master
id|snd_timer_instance_t
op_star
id|master
suffix:semicolon
DECL|member|in_use
id|atomic_t
id|in_use
suffix:semicolon
multiline_comment|/* don&squot;t free */
)brace
suffix:semicolon
multiline_comment|/*&n; *  Registering&n; */
r_extern
r_int
id|snd_timer_new
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
id|snd_timer_id_t
op_star
id|tid
comma
id|snd_timer_t
op_star
op_star
id|rtimer
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_global_new
c_func
(paren
r_char
op_star
id|id
comma
r_int
id|device
comma
id|snd_timer_t
op_star
op_star
id|rtimer
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_global_free
c_func
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_global_register
c_func
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_global_unregister
c_func
(paren
id|snd_timer_t
op_star
id|timer
)paren
suffix:semicolon
r_extern
id|snd_timer_instance_t
op_star
id|snd_timer_open
c_func
(paren
r_char
op_star
id|owner
comma
id|snd_timer_id_t
op_star
id|tid
comma
r_int
r_int
id|slave_id
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_close
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_set_owner
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
comma
id|pid_t
id|pid
comma
id|gid_t
id|gid
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_reset_owner
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_set_resolution
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
comma
r_int
r_int
id|resolution
)paren
suffix:semicolon
r_extern
r_int
r_int
id|snd_timer_resolution
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_start
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
comma
r_int
r_int
id|ticks
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_stop
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
)paren
suffix:semicolon
r_extern
r_int
id|snd_timer_continue
c_func
(paren
id|snd_timer_instance_t
op_star
id|timeri
)paren
suffix:semicolon
r_extern
r_void
id|snd_timer_interrupt
c_func
(paren
id|snd_timer_t
op_star
id|timer
comma
r_int
r_int
id|ticks_left
)paren
suffix:semicolon
r_extern
r_int
r_int
id|snd_timer_system_resolution
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_TIMER_H */
eof