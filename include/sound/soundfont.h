macro_line|#ifndef __SOUND_SOUNDFONT_H
DECL|macro|__SOUND_SOUNDFONT_H
mdefine_line|#define __SOUND_SOUNDFONT_H
multiline_comment|/*&n; *  Soundfont defines and definitions.&n; *&n; *  Copyright (C) 1999 Steve Ratcliffe&n; *  Copyright (c) 1999-2000 Takashi iwai &lt;tiwai@suse.de&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &quot;sfnt_info.h&quot;
macro_line|#include &quot;util_mem.h&quot;
DECL|macro|SF_MAX_INSTRUMENTS
mdefine_line|#define SF_MAX_INSTRUMENTS&t;128&t;/* maximum instrument number */
DECL|macro|SF_MAX_PRESETS
mdefine_line|#define SF_MAX_PRESETS  256&t;/* drums are mapped from 128 to 256 */
DECL|macro|SF_IS_DRUM_BANK
mdefine_line|#define SF_IS_DRUM_BANK(z) ((z) == 128)
DECL|struct|snd_sf_zone
r_typedef
r_struct
id|snd_sf_zone
(brace
DECL|member|next
r_struct
id|snd_sf_zone
op_star
id|next
suffix:semicolon
multiline_comment|/* Link to next */
DECL|member|bank
r_int
r_char
id|bank
suffix:semicolon
multiline_comment|/* Midi bank for this zone */
DECL|member|instr
r_int
r_char
id|instr
suffix:semicolon
multiline_comment|/* Midi program for this zone */
DECL|member|mapped
r_int
r_char
id|mapped
suffix:semicolon
multiline_comment|/* True if mapped to something else */
DECL|member|v
id|soundfont_voice_info_t
id|v
suffix:semicolon
multiline_comment|/* All the soundfont parameters */
DECL|member|counter
r_int
id|counter
suffix:semicolon
DECL|member|sample
r_struct
id|snd_sf_sample
op_star
id|sample
suffix:semicolon
multiline_comment|/* Link to sample */
multiline_comment|/* The following deals with preset numbers (programs) */
DECL|member|next_instr
r_struct
id|snd_sf_zone
op_star
id|next_instr
suffix:semicolon
multiline_comment|/* Next zone of this instrument */
DECL|member|next_zone
r_struct
id|snd_sf_zone
op_star
id|next_zone
suffix:semicolon
multiline_comment|/* Next zone in play list */
DECL|typedef|snd_sf_zone_t
)brace
id|snd_sf_zone_t
suffix:semicolon
DECL|struct|snd_sf_sample
r_typedef
r_struct
id|snd_sf_sample
(brace
DECL|member|v
id|soundfont_sample_info_t
id|v
suffix:semicolon
DECL|member|counter
r_int
id|counter
suffix:semicolon
DECL|member|block
id|snd_util_memblk_t
op_star
id|block
suffix:semicolon
multiline_comment|/* allocated data block */
DECL|member|next
r_struct
id|snd_sf_sample
op_star
id|next
suffix:semicolon
DECL|typedef|snd_sf_sample_t
)brace
id|snd_sf_sample_t
suffix:semicolon
multiline_comment|/*&n; * This represents all the information relating to a soundfont.&n; */
DECL|struct|snd_soundfont
r_typedef
r_struct
id|snd_soundfont
(brace
DECL|member|next
r_struct
id|snd_soundfont
op_star
id|next
suffix:semicolon
multiline_comment|/* Link to next */
multiline_comment|/*struct snd_soundfont *prev;*/
multiline_comment|/* Link to previous */
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* file id */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* font type */
DECL|member|name
r_int
r_char
id|name
(braket
id|SNDRV_SFNT_PATCH_NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* identifier */
DECL|member|zones
id|snd_sf_zone_t
op_star
id|zones
suffix:semicolon
multiline_comment|/* Font information */
DECL|member|samples
id|snd_sf_sample_t
op_star
id|samples
suffix:semicolon
multiline_comment|/* The sample headers */
DECL|typedef|snd_soundfont_t
)brace
id|snd_soundfont_t
suffix:semicolon
multiline_comment|/*&n; * Type of the sample access callback&n; */
DECL|typedef|snd_sf_sample_new_t
r_typedef
r_int
(paren
op_star
id|snd_sf_sample_new_t
)paren
(paren
r_void
op_star
id|private_data
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
comma
r_const
r_void
id|__user
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|typedef|snd_sf_sample_free_t
r_typedef
r_int
(paren
op_star
id|snd_sf_sample_free_t
)paren
(paren
r_void
op_star
id|private_data
comma
id|snd_sf_sample_t
op_star
id|sp
comma
id|snd_util_memhdr_t
op_star
id|hdr
)paren
suffix:semicolon
DECL|typedef|snd_sf_sample_reset_t
r_typedef
r_void
(paren
op_star
id|snd_sf_sample_reset_t
)paren
(paren
r_void
op_star
r_private
)paren
suffix:semicolon
DECL|struct|snd_sf_callback
r_typedef
r_struct
id|snd_sf_callback
(brace
DECL|member|private_data
r_void
op_star
id|private_data
suffix:semicolon
DECL|member|sample_new
id|snd_sf_sample_new_t
id|sample_new
suffix:semicolon
DECL|member|sample_free
id|snd_sf_sample_free_t
id|sample_free
suffix:semicolon
DECL|member|sample_reset
id|snd_sf_sample_reset_t
id|sample_reset
suffix:semicolon
DECL|typedef|snd_sf_callback_t
)brace
id|snd_sf_callback_t
suffix:semicolon
multiline_comment|/*&n; * List of soundfonts.&n; */
DECL|struct|snd_sf_list
r_typedef
r_struct
id|snd_sf_list
(brace
DECL|member|currsf
id|snd_soundfont_t
op_star
id|currsf
suffix:semicolon
multiline_comment|/* The currently open soundfont */
DECL|member|open_client
r_int
id|open_client
suffix:semicolon
multiline_comment|/* client pointer for lock */
DECL|member|mem_used
r_int
id|mem_used
suffix:semicolon
multiline_comment|/* used memory size */
DECL|member|presets
id|snd_sf_zone_t
op_star
id|presets
(braket
id|SF_MAX_PRESETS
)braket
suffix:semicolon
DECL|member|fonts
id|snd_soundfont_t
op_star
id|fonts
suffix:semicolon
multiline_comment|/* The list of soundfonts */
DECL|member|fonts_size
r_int
id|fonts_size
suffix:semicolon
multiline_comment|/* number of fonts allocated */
DECL|member|zone_counter
r_int
id|zone_counter
suffix:semicolon
multiline_comment|/* last allocated time for zone */
DECL|member|sample_counter
r_int
id|sample_counter
suffix:semicolon
multiline_comment|/* last allocated time for sample */
DECL|member|zone_locked
r_int
id|zone_locked
suffix:semicolon
multiline_comment|/* locked time for zone */
DECL|member|sample_locked
r_int
id|sample_locked
suffix:semicolon
multiline_comment|/* locked time for sample */
DECL|member|callback
id|snd_sf_callback_t
id|callback
suffix:semicolon
multiline_comment|/* callback functions */
DECL|member|presets_mutex
r_struct
id|semaphore
id|presets_mutex
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|memhdr
id|snd_util_memhdr_t
op_star
id|memhdr
suffix:semicolon
DECL|typedef|snd_sf_list_t
)brace
id|snd_sf_list_t
suffix:semicolon
multiline_comment|/* Prototypes for soundfont.c */
r_int
id|snd_soundfont_load
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
comma
r_const
r_void
id|__user
op_star
id|data
comma
r_int
id|count
comma
r_int
id|client
)paren
suffix:semicolon
r_int
id|snd_soundfont_load_guspatch
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
comma
r_const
r_char
id|__user
op_star
id|data
comma
r_int
id|count
comma
r_int
id|client
)paren
suffix:semicolon
r_int
id|snd_soundfont_close_check
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
comma
r_int
id|client
)paren
suffix:semicolon
id|snd_sf_list_t
op_star
id|snd_sf_new
c_func
(paren
id|snd_sf_callback_t
op_star
id|callback
comma
id|snd_util_memhdr_t
op_star
id|hdr
)paren
suffix:semicolon
r_void
id|snd_sf_free
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
)paren
suffix:semicolon
r_int
id|snd_soundfont_remove_samples
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
)paren
suffix:semicolon
r_int
id|snd_soundfont_remove_unlocked
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
)paren
suffix:semicolon
r_int
id|snd_soundfont_mem_used
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
)paren
suffix:semicolon
r_int
id|snd_soundfont_search_zone
c_func
(paren
id|snd_sf_list_t
op_star
id|sflist
comma
r_int
op_star
id|notep
comma
r_int
id|vel
comma
r_int
id|preset
comma
r_int
id|bank
comma
r_int
id|def_preset
comma
r_int
id|def_bank
comma
id|snd_sf_zone_t
op_star
op_star
id|table
comma
r_int
id|max_layers
)paren
suffix:semicolon
multiline_comment|/* Parameter conversions */
r_int
id|snd_sf_calc_parm_hold
c_func
(paren
r_int
id|msec
)paren
suffix:semicolon
r_int
id|snd_sf_calc_parm_attack
c_func
(paren
r_int
id|msec
)paren
suffix:semicolon
r_int
id|snd_sf_calc_parm_decay
c_func
(paren
r_int
id|msec
)paren
suffix:semicolon
DECL|macro|snd_sf_calc_parm_delay
mdefine_line|#define snd_sf_calc_parm_delay(msec) (0x8000 - (msec) * 1000 / 725);
r_extern
r_int
id|snd_sf_vol_table
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|snd_sf_linear_to_log
c_func
(paren
r_int
r_int
id|amount
comma
r_int
id|offset
comma
r_int
id|ratio
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_SOUNDFONT_H */
eof
