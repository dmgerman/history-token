macro_line|#ifndef __SOUND_INFO_H
DECL|macro|__SOUND_INFO_H
mdefine_line|#define __SOUND_INFO_H
multiline_comment|/*&n; *  Header file for info interface&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/poll.h&gt;
multiline_comment|/* buffer for information */
DECL|struct|snd_info_buffer
r_struct
id|snd_info_buffer
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* pointer to begin of buffer */
DECL|member|curr
r_char
op_star
id|curr
suffix:semicolon
multiline_comment|/* current position in buffer */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* current size */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* total length of buffer */
DECL|member|stop
r_int
id|stop
suffix:semicolon
multiline_comment|/* stop flag */
DECL|member|error
r_int
id|error
suffix:semicolon
multiline_comment|/* error code */
)brace
suffix:semicolon
DECL|typedef|snd_info_buffer_t
r_typedef
r_struct
id|snd_info_buffer
id|snd_info_buffer_t
suffix:semicolon
DECL|macro|SNDRV_INFO_CONTENT_TEXT
mdefine_line|#define SNDRV_INFO_CONTENT_TEXT&t;&t;0
DECL|macro|SNDRV_INFO_CONTENT_DATA
mdefine_line|#define SNDRV_INFO_CONTENT_DATA&t;&t;1
r_struct
id|snd_info_entry
suffix:semicolon
DECL|struct|snd_info_entry_text
r_struct
id|snd_info_entry_text
(brace
DECL|member|read_size
r_int
r_int
id|read_size
suffix:semicolon
DECL|member|write_size
r_int
r_int
id|write_size
suffix:semicolon
DECL|member|read
r_void
(paren
op_star
id|read
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
suffix:semicolon
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
id|snd_info_buffer_t
op_star
id|buffer
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_info_entry_ops
r_struct
id|snd_info_entry_ops
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_int
r_int
id|mode
comma
r_void
op_star
op_star
id|file_private_data
)paren
suffix:semicolon
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_int
r_int
id|mode
comma
r_void
op_star
id|file_private_data
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
comma
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
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
comma
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
)paren
suffix:semicolon
DECL|member|llseek
r_int
r_int
(paren
op_star
id|llseek
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
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
DECL|member|poll
r_int
r_int
(paren
op_star
id|poll
)paren
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
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
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
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
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|file_private_data
comma
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
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_info_entry
r_struct
id|snd_info_entry
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|content
r_int
r_int
id|content
suffix:semicolon
DECL|member|disconnected
r_int
r_int
id|disconnected
suffix:colon
l_int|1
suffix:semicolon
r_union
(brace
DECL|member|text
r_struct
id|snd_info_entry_text
id|text
suffix:semicolon
DECL|member|ops
r_struct
id|snd_info_entry_ops
op_star
id|ops
suffix:semicolon
DECL|member|c
)brace
id|c
suffix:semicolon
DECL|member|parent
id|snd_info_entry_t
op_star
id|parent
suffix:semicolon
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
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
id|snd_info_entry_t
op_star
id|entry
)paren
suffix:semicolon
DECL|member|p
r_struct
id|proc_dir_entry
op_star
id|p
suffix:semicolon
DECL|member|access
r_struct
id|semaphore
id|access
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|snd_info_check_reserved_words
c_func
(paren
r_const
r_char
op_star
id|str
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_extern
r_int
id|snd_info_minor_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|snd_info_minor_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
r_extern
id|snd_info_entry_t
op_star
id|snd_seq_root
suffix:semicolon
macro_line|#ifdef CONFIG_SND_OSSEMUL
r_extern
id|snd_info_entry_t
op_star
id|snd_oss_root
suffix:semicolon
macro_line|#else
DECL|macro|snd_oss_root
mdefine_line|#define snd_oss_root NULL
macro_line|#endif
r_int
id|snd_iprintf
c_func
(paren
id|snd_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|2
comma
l_int|3
)paren
)paren
)paren
suffix:semicolon
r_int
id|snd_info_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_info_done
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_info_get_line
c_func
(paren
id|snd_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|line
comma
r_int
id|len
)paren
suffix:semicolon
r_char
op_star
id|snd_info_get_str
c_func
(paren
r_char
op_star
id|dest
comma
r_char
op_star
id|src
comma
r_int
id|len
)paren
suffix:semicolon
id|snd_info_entry_t
op_star
id|snd_info_create_module_entry
c_func
(paren
r_struct
id|module
op_star
id|module
comma
r_const
r_char
op_star
id|name
comma
id|snd_info_entry_t
op_star
id|parent
)paren
suffix:semicolon
id|snd_info_entry_t
op_star
id|snd_info_create_card_entry
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|name
comma
id|snd_info_entry_t
op_star
id|parent
)paren
suffix:semicolon
r_void
id|snd_info_free_entry
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
suffix:semicolon
r_int
id|snd_info_store_text
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
suffix:semicolon
r_int
id|snd_info_restore_text
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
suffix:semicolon
r_int
id|snd_info_card_create
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_info_card_register
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_info_card_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
suffix:semicolon
r_int
id|snd_info_register
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
suffix:semicolon
r_int
id|snd_info_unregister
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|snd_create_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
suffix:semicolon
r_void
id|snd_remove_proc_entry
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|parent
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
suffix:semicolon
multiline_comment|/* for card drivers */
r_int
id|snd_card_proc_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|name
comma
id|snd_info_entry_t
op_star
op_star
id|entryp
)paren
suffix:semicolon
DECL|function|snd_info_set_text_ops
r_static
r_inline
r_void
id|snd_info_set_text_ops
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
comma
r_void
op_star
id|private_data
comma
r_int
id|read_size
comma
r_void
(paren
op_star
id|read
)paren
(paren
id|snd_info_entry_t
op_star
comma
id|snd_info_buffer_t
op_star
)paren
)paren
(brace
id|entry-&gt;private_data
op_assign
id|private_data
suffix:semicolon
id|entry-&gt;c.text.read_size
op_assign
id|read_size
suffix:semicolon
id|entry-&gt;c.text.read
op_assign
id|read
suffix:semicolon
)brace
macro_line|#else
DECL|macro|snd_seq_root
mdefine_line|#define snd_seq_root NULL
DECL|macro|snd_oss_root
mdefine_line|#define snd_oss_root NULL
DECL|function|snd_iprintf
r_static
r_inline
r_int
id|snd_iprintf
c_func
(paren
id|snd_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_init
r_static
r_inline
r_int
id|snd_info_init
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_done
r_static
r_inline
r_int
id|snd_info_done
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_get_line
r_static
r_inline
r_int
id|snd_info_get_line
c_func
(paren
id|snd_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|line
comma
r_int
id|len
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_get_str
r_static
r_inline
r_char
op_star
id|snd_info_get_str
c_func
(paren
r_char
op_star
id|dest
comma
r_char
op_star
id|src
comma
r_int
id|len
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_info_create_module_entry
r_static
r_inline
id|snd_info_entry_t
op_star
id|snd_info_create_module_entry
c_func
(paren
r_struct
id|module
op_star
id|module
comma
r_const
r_char
op_star
id|name
comma
id|snd_info_entry_t
op_star
id|parent
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_info_create_card_entry
r_static
r_inline
id|snd_info_entry_t
op_star
id|snd_info_create_card_entry
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_const
r_char
op_star
id|name
comma
id|snd_info_entry_t
op_star
id|parent
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_info_free_entry
r_static
r_inline
r_void
id|snd_info_free_entry
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
(brace
suffix:semicolon
)brace
DECL|function|snd_info_card_create
r_static
r_inline
r_int
id|snd_info_card_create
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_card_register
r_static
r_inline
r_int
id|snd_info_card_register
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_card_free
r_static
r_inline
r_int
id|snd_info_card_free
c_func
(paren
id|snd_card_t
op_star
id|card
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_register
r_static
r_inline
r_int
id|snd_info_register
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_info_unregister
r_static
r_inline
r_int
id|snd_info_unregister
c_func
(paren
id|snd_info_entry_t
op_star
id|entry
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snd_create_proc_entry
r_static
r_inline
r_struct
id|proc_dir_entry
op_star
id|snd_create_proc_entry
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|mode_t
id|mode
comma
r_struct
id|proc_dir_entry
op_star
id|parent
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|snd_remove_proc_entry
r_static
r_inline
r_void
id|snd_remove_proc_entry
c_func
(paren
r_struct
id|proc_dir_entry
op_star
id|parent
comma
r_struct
id|proc_dir_entry
op_star
id|de
)paren
(brace
suffix:semicolon
)brace
DECL|macro|snd_card_proc_new
mdefine_line|#define snd_card_proc_new(card,name,entryp)  0 /* always success */
DECL|macro|snd_info_set_text_ops
mdefine_line|#define snd_info_set_text_ops(entry,private_data,read) /*NOP*/
macro_line|#endif
multiline_comment|/*&n; * OSS info part&n; */
macro_line|#if defined(CONFIG_SND_OSSEMUL) &amp;&amp; defined(CONFIG_PROC_FS)
DECL|macro|SNDRV_OSS_INFO_DEV_AUDIO
mdefine_line|#define SNDRV_OSS_INFO_DEV_AUDIO&t;0
DECL|macro|SNDRV_OSS_INFO_DEV_SYNTH
mdefine_line|#define SNDRV_OSS_INFO_DEV_SYNTH&t;1
DECL|macro|SNDRV_OSS_INFO_DEV_MIDI
mdefine_line|#define SNDRV_OSS_INFO_DEV_MIDI&t;&t;2
DECL|macro|SNDRV_OSS_INFO_DEV_TIMERS
mdefine_line|#define SNDRV_OSS_INFO_DEV_TIMERS&t;4
DECL|macro|SNDRV_OSS_INFO_DEV_MIXERS
mdefine_line|#define SNDRV_OSS_INFO_DEV_MIXERS&t;5
DECL|macro|SNDRV_OSS_INFO_DEV_COUNT
mdefine_line|#define SNDRV_OSS_INFO_DEV_COUNT&t;6
r_extern
r_int
id|snd_oss_info_register
c_func
(paren
r_int
id|dev
comma
r_int
id|num
comma
r_char
op_star
id|string
)paren
suffix:semicolon
DECL|macro|snd_oss_info_unregister
mdefine_line|#define snd_oss_info_unregister(dev, num) snd_oss_info_register(dev, num, NULL)
macro_line|#endif /* CONFIG_SND_OSSEMUL &amp;&amp; CONFIG_PROC_FS */
macro_line|#endif /* __SOUND_INFO_H */
eof
