multiline_comment|/*&n; *  font.h -- `Soft&squot; font definitions&n; *&n; *  Created 1995 by Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive&n; *  for more details.&n; */
macro_line|#ifndef _VIDEO_FONT_H
DECL|macro|_VIDEO_FONT_H
mdefine_line|#define _VIDEO_FONT_H
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|font_desc
r_struct
id|font_desc
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|width
DECL|member|height
r_int
id|width
comma
id|height
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|pref
r_int
id|pref
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _VIDEO_FONT_H */
eof
