macro_line|#ifndef __SOUND_HWDEP_H
DECL|macro|__SOUND_HWDEP_H
mdefine_line|#define __SOUND_HWDEP_H
multiline_comment|/*&n; *  Hardware dependent layer &n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;sound/asound.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
DECL|typedef|snd_hwdep_iface_t
r_typedef
r_enum
id|sndrv_hwdep_iface
id|snd_hwdep_iface_t
suffix:semicolon
DECL|typedef|snd_hwdep_info_t
r_typedef
r_struct
id|sndrv_hwdep_info
id|snd_hwdep_info_t
suffix:semicolon
DECL|typedef|snd_hwdep_dsp_status_t
r_typedef
r_struct
id|sndrv_hwdep_dsp_status
id|snd_hwdep_dsp_status_t
suffix:semicolon
DECL|typedef|snd_hwdep_dsp_image_t
r_typedef
r_struct
id|sndrv_hwdep_dsp_image
id|snd_hwdep_dsp_image_t
suffix:semicolon
DECL|struct|_snd_hwdep_ops
r_typedef
r_struct
id|_snd_hwdep_ops
(brace
DECL|member|llseek
r_int
r_int
(paren
op_star
id|llseek
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
id|orig
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
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
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
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
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|member|poll
r_int
r_int
(paren
op_star
id|poll
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
comma
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
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
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
DECL|member|ioctl_compat
r_int
(paren
op_star
id|ioctl_compat
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
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
DECL|member|mmap
r_int
(paren
op_star
id|mmap
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
comma
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
suffix:semicolon
DECL|member|dsp_status
r_int
(paren
op_star
id|dsp_status
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_status_t
op_star
id|status
)paren
suffix:semicolon
DECL|member|dsp_load
r_int
(paren
op_star
id|dsp_load
)paren
(paren
id|snd_hwdep_t
op_star
id|hw
comma
id|snd_hwdep_dsp_image_t
op_star
id|image
)paren
suffix:semicolon
DECL|typedef|snd_hwdep_ops_t
)brace
id|snd_hwdep_ops_t
suffix:semicolon
DECL|struct|_snd_hwdep
r_struct
id|_snd_hwdep
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|device
r_int
id|device
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|iface
r_int
id|iface
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
DECL|member|oss_dev
r_char
id|oss_dev
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|oss_type
r_int
id|oss_type
suffix:semicolon
DECL|member|ossreg
r_int
id|ossreg
suffix:semicolon
macro_line|#endif
DECL|member|ops
id|snd_hwdep_ops_t
id|ops
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
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
id|snd_hwdep_t
op_star
id|hwdep
)paren
suffix:semicolon
DECL|member|open_mutex
r_struct
id|semaphore
id|open_mutex
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|dsp_loaded
r_int
r_int
id|dsp_loaded
suffix:semicolon
DECL|member|exclusive
r_int
r_int
id|exclusive
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
r_extern
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
suffix:semicolon
macro_line|#endif /* __SOUND_HWDEP_H */
eof
