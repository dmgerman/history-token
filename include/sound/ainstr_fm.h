multiline_comment|/*&n; *  Advanced Linux Sound Architecture&n; *&n; *  FM (OPL2/3) Instrument Format&n; *  Copyright (c) 2000 Uros Bizjak &lt;uros@kss-loka.si&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef __SOUND_AINSTR_FM_H
DECL|macro|__SOUND_AINSTR_FM_H
mdefine_line|#define __SOUND_AINSTR_FM_H
macro_line|#ifndef __KERNEL__
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#endif
multiline_comment|/*&n; *  share types (share ID 1)&n; */
DECL|macro|FM_SHARE_FILE
mdefine_line|#define FM_SHARE_FILE&t;&t;0
multiline_comment|/*&n; * FM operator&n; */
DECL|struct|fm_operator
r_typedef
r_struct
id|fm_operator
(brace
DECL|member|am_vib
r_int
r_char
id|am_vib
suffix:semicolon
DECL|member|ksl_level
r_int
r_char
id|ksl_level
suffix:semicolon
DECL|member|attack_decay
r_int
r_char
id|attack_decay
suffix:semicolon
DECL|member|sustain_release
r_int
r_char
id|sustain_release
suffix:semicolon
DECL|member|wave_select
r_int
r_char
id|wave_select
suffix:semicolon
DECL|typedef|fm_operator_t
)brace
id|fm_operator_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument&n; */
DECL|macro|FM_PATCH_OPL2
mdefine_line|#define FM_PATCH_OPL2&t;0x01&t;&t;/* OPL2 2 operators FM instrument */
DECL|macro|FM_PATCH_OPL3
mdefine_line|#define FM_PATCH_OPL3&t;0x02&t;&t;/* OPL3 4 operators FM instrument */
r_typedef
r_struct
(brace
DECL|member|share_id
r_int
r_int
id|share_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* share id - zero = no sharing */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* instrument type */
DECL|member|op
id|fm_operator_t
id|op
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|feedback_connection
r_int
r_char
id|feedback_connection
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|echo_delay
r_int
r_char
id|echo_delay
suffix:semicolon
DECL|member|echo_atten
r_int
r_char
id|echo_atten
suffix:semicolon
DECL|member|chorus_spread
r_int
r_char
id|chorus_spread
suffix:semicolon
DECL|member|trnsps
r_int
r_char
id|trnsps
suffix:semicolon
DECL|member|fix_dur
r_int
r_char
id|fix_dur
suffix:semicolon
DECL|member|modes
r_int
r_char
id|modes
suffix:semicolon
DECL|member|fix_key
r_int
r_char
id|fix_key
suffix:semicolon
DECL|typedef|fm_instrument_t
)brace
id|fm_instrument_t
suffix:semicolon
multiline_comment|/*&n; *&n; *    Kernel &lt;-&gt; user space&n; *    Hardware (CPU) independent section&n; *&n; *    * = zero or more&n; *    + = one or more&n; *&n; *    fm_xinstrument&t;FM_STRU_INSTR&n; *&n; */
DECL|macro|FM_STRU_INSTR
mdefine_line|#define FM_STRU_INSTR&t;__cpu_to_be32((&squot;I&squot;&lt;&lt;24)|(&squot;N&squot;&lt;&lt;16)|(&squot;S&squot;&lt;&lt;8)|&squot;T&squot;)
multiline_comment|/*&n; * FM operator&n; */
DECL|struct|fm_xoperator
r_typedef
r_struct
id|fm_xoperator
(brace
DECL|member|am_vib
id|__u8
id|am_vib
suffix:semicolon
DECL|member|ksl_level
id|__u8
id|ksl_level
suffix:semicolon
DECL|member|attack_decay
id|__u8
id|attack_decay
suffix:semicolon
DECL|member|sustain_release
id|__u8
id|sustain_release
suffix:semicolon
DECL|member|wave_select
id|__u8
id|wave_select
suffix:semicolon
DECL|typedef|fm_xoperator_t
)brace
id|fm_xoperator_t
suffix:semicolon
multiline_comment|/*&n; *  Instrument&n; */
DECL|struct|fm_xinstrument
r_typedef
r_struct
id|fm_xinstrument
(brace
DECL|member|stype
id|__u32
id|stype
suffix:semicolon
multiline_comment|/* structure type */
DECL|member|share_id
id|__u32
id|share_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* share id - zero = no sharing */
DECL|member|type
id|__u8
id|type
suffix:semicolon
multiline_comment|/* instrument type */
DECL|member|op
id|fm_xoperator_t
id|op
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* fm operators */
DECL|member|feedback_connection
id|__u8
id|feedback_connection
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|echo_delay
id|__u8
id|echo_delay
suffix:semicolon
DECL|member|echo_atten
id|__u8
id|echo_atten
suffix:semicolon
DECL|member|chorus_spread
id|__u8
id|chorus_spread
suffix:semicolon
DECL|member|trnsps
id|__u8
id|trnsps
suffix:semicolon
DECL|member|fix_dur
id|__u8
id|fix_dur
suffix:semicolon
DECL|member|modes
id|__u8
id|modes
suffix:semicolon
DECL|member|fix_key
id|__u8
id|fix_key
suffix:semicolon
DECL|typedef|fm_xinstrument_t
)brace
id|fm_xinstrument_t
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &quot;seq_instr.h&quot;
r_extern
r_char
op_star
id|snd_seq_fm_id
suffix:semicolon
r_int
id|snd_seq_fm_init
c_func
(paren
id|snd_seq_kinstr_ops_t
op_star
id|ops
comma
id|snd_seq_kinstr_ops_t
op_star
id|next
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;/* __SOUND_AINSTR_FM_H */
eof
