macro_line|#ifndef __SOUND_OPL4_H
DECL|macro|__SOUND_OPL4_H
mdefine_line|#define __SOUND_OPL4_H
multiline_comment|/*&n; * Global definitions for the OPL4 driver&n; * Copyright (c) 2003 by Clemens Ladisch &lt;clemens@ladisch.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;sound/opl3.h&gt;
DECL|typedef|opl4_t
r_typedef
r_struct
id|opl4
id|opl4_t
suffix:semicolon
r_extern
r_int
id|snd_opl4_create
c_func
(paren
id|snd_card_t
op_star
id|card
comma
r_int
r_int
id|fm_port
comma
r_int
r_int
id|pcm_port
comma
r_int
id|seq_device
comma
id|opl3_t
op_star
op_star
id|opl3
comma
id|opl4_t
op_star
op_star
id|opl4
)paren
suffix:semicolon
macro_line|#endif /* __SOUND_OPL4_H */
eof
