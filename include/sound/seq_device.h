macro_line|#ifndef __SOUND_SEQ_DEVICE_H
DECL|macro|__SOUND_SEQ_DEVICE_H
mdefine_line|#define __SOUND_SEQ_DEVICE_H
multiline_comment|/*&n; *  ALSA sequencer device management&n; *  Copyright (c) 1999 by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
DECL|typedef|snd_seq_device_t
r_typedef
r_struct
id|snd_seq_device
id|snd_seq_device_t
suffix:semicolon
DECL|typedef|snd_seq_dev_ops_t
r_typedef
r_struct
id|snd_seq_dev_ops
id|snd_seq_dev_ops_t
suffix:semicolon
multiline_comment|/*&n; * registered device information&n; */
DECL|macro|ID_LEN
mdefine_line|#define ID_LEN&t;32
multiline_comment|/* status flag */
DECL|macro|SNDRV_SEQ_DEVICE_FREE
mdefine_line|#define SNDRV_SEQ_DEVICE_FREE&t;&t;0
DECL|macro|SNDRV_SEQ_DEVICE_REGISTERED
mdefine_line|#define SNDRV_SEQ_DEVICE_REGISTERED&t;1
DECL|struct|snd_seq_device
r_struct
id|snd_seq_device
(brace
multiline_comment|/* device info */
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
multiline_comment|/* sound card */
DECL|member|device
r_int
id|device
suffix:semicolon
multiline_comment|/* device number */
DECL|member|id
r_char
id|id
(braket
id|ID_LEN
)braket
suffix:semicolon
multiline_comment|/* driver id */
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* device name */
DECL|member|argsize
r_int
id|argsize
suffix:semicolon
multiline_comment|/* size of the argument */
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
multiline_comment|/* private data for driver */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* flag - read only */
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
multiline_comment|/* private data for the caller */
DECL|member|private_free
r_void
(paren
op_star
id|private_free
)paren
(paren
id|snd_seq_device_t
op_star
id|device
)paren
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
multiline_comment|/* link to next device */
)brace
suffix:semicolon
multiline_comment|/* driver operators&n; * init_device:&n; *&t;Initialize the device with given parameters.&n; *&t;Typically,&n; *&t;&t;1. call snd_hwdep_new&n; *&t;&t;2. allocate private data and initialize it&n; *&t;&t;3. call snd_hwdep_register&n; *&t;&t;4. store the instance to dev-&gt;driver_data pointer.&n; *&t;&t;&n; * free_device:&n; *&t;Release the private data.&n; *&t;Typically, call snd_device_free(dev-&gt;card, dev-&gt;driver_data)&n; */
DECL|struct|snd_seq_dev_ops
r_struct
id|snd_seq_dev_ops
(brace
DECL|member|init_device
r_int
(paren
op_star
id|init_device
)paren
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
suffix:semicolon
DECL|member|free_device
r_int
(paren
op_star
id|free_device
)paren
(paren
id|snd_seq_device_t
op_star
id|dev
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * prototypes&n; */
r_void
id|snd_seq_device_load_drivers
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|snd_seq_device_new
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
id|device
comma
r_char
op_star
id|id
comma
r_int
id|argsize
comma
id|snd_seq_device_t
op_star
op_star
id|result
)paren
suffix:semicolon
r_int
id|snd_seq_device_register_driver
c_func
(paren
r_char
op_star
id|id
comma
id|snd_seq_dev_ops_t
op_star
id|entry
comma
r_int
id|argsize
)paren
suffix:semicolon
r_int
id|snd_seq_device_unregister_driver
c_func
(paren
r_char
op_star
id|id
)paren
suffix:semicolon
DECL|macro|SNDRV_SEQ_DEVICE_ARGPTR
mdefine_line|#define SNDRV_SEQ_DEVICE_ARGPTR(dev) (void *)((char *)(dev) + sizeof(snd_seq_device_t))
multiline_comment|/*&n; * id strings for generic devices&n; */
DECL|macro|SNDRV_SEQ_DEV_ID_MIDISYNTH
mdefine_line|#define SNDRV_SEQ_DEV_ID_MIDISYNTH&t;&quot;seq-midi&quot;
DECL|macro|SNDRV_SEQ_DEV_ID_OPL3
mdefine_line|#define SNDRV_SEQ_DEV_ID_OPL3&t;&t;&quot;opl3-synth&quot;
macro_line|#endif /* __SOUND_SEQ_DEVICE_H */
eof
