macro_line|#ifndef __SOUND_TEA575X_TUNER_H
DECL|macro|__SOUND_TEA575X_TUNER_H
mdefine_line|#define __SOUND_TEA575X_TUNER_H
multiline_comment|/*&n; *   ALSA driver for TEA5757/5759 Philips AM/FM tuner chips&n; *&n; *&t;Copyright (c) 2004 Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#include &lt;linux/videodev.h&gt;
DECL|typedef|tea575x_t
r_typedef
r_struct
id|snd_tea575x
id|tea575x_t
suffix:semicolon
DECL|struct|snd_tea575x_ops
r_struct
id|snd_tea575x_ops
(brace
DECL|member|write
r_void
(paren
op_star
id|write
)paren
(paren
id|tea575x_t
op_star
id|tea
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|member|read
r_int
r_int
(paren
op_star
id|read
)paren
(paren
id|tea575x_t
op_star
id|tea
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|snd_tea575x
r_struct
id|snd_tea575x
(brace
DECL|member|card
id|snd_card_t
op_star
id|card
suffix:semicolon
DECL|member|vd
r_struct
id|video_device
id|vd
suffix:semicolon
multiline_comment|/* video device */
DECL|member|dev_nr
r_int
id|dev_nr
suffix:semicolon
multiline_comment|/* requested device number + 1 */
DECL|member|vd_registered
r_int
id|vd_registered
suffix:semicolon
multiline_comment|/* video device is registered */
DECL|member|tea5759
r_int
id|tea5759
suffix:semicolon
multiline_comment|/* 5759 chip is present */
DECL|member|freq_fixup
r_int
r_int
id|freq_fixup
suffix:semicolon
multiline_comment|/* crystal onboard */
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/* hw value */
DECL|member|freq
r_int
r_int
id|freq
suffix:semicolon
multiline_comment|/* frequency */
DECL|member|ops
r_struct
id|snd_tea575x_ops
op_star
id|ops
suffix:semicolon
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
)brace
suffix:semicolon
r_void
id|snd_tea575x_init
c_func
(paren
id|tea575x_t
op_star
id|tea
)paren
suffix:semicolon
r_void
id|snd_tea575x_exit
c_func
(paren
id|tea575x_t
op_star
id|tea
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_TEA575X_TUNER_H */
eof
