multiline_comment|/*&n; * ItSpCommArea.h&n; * Copyright (C) 2001  Mike Corrigan IBM Corporation&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#ifndef _ITSPCOMMAREA_H
DECL|macro|_ITSPCOMMAREA_H
mdefine_line|#define _ITSPCOMMAREA_H
DECL|struct|SpCommArea
r_struct
id|SpCommArea
(brace
DECL|member|xDesc
id|u32
id|xDesc
suffix:semicolon
singleline_comment|// Descriptor (only in new formats)&t;000-003
DECL|member|xFormat
id|u8
id|xFormat
suffix:semicolon
singleline_comment|// Format (only in new formats)&t;&t;004-004
DECL|member|xRsvd1
id|u8
id|xRsvd1
(braket
l_int|11
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;005-00F
DECL|member|xRawTbAtIplStart
id|u64
id|xRawTbAtIplStart
suffix:semicolon
singleline_comment|// Raw HW TB value when IPL is started&t;010-017
DECL|member|xRawTodAtIplStart
id|u64
id|xRawTodAtIplStart
suffix:semicolon
singleline_comment|// Raw HW TOD value when IPL is started&t;018-01F
DECL|member|xBcdTimeAtIplStart
id|u64
id|xBcdTimeAtIplStart
suffix:semicolon
singleline_comment|// BCD time when IPL is started&t;&t;020-027
DECL|member|xBcdTimeAtOsStart
id|u64
id|xBcdTimeAtOsStart
suffix:semicolon
singleline_comment|// BCD time when OS passed control&t;028-02F
DECL|member|xRsvd2
id|u8
id|xRsvd2
(braket
l_int|80
)braket
suffix:semicolon
singleline_comment|// Reserved&t;&t;&t;&t;030-07F
)brace
suffix:semicolon
r_extern
r_struct
id|SpCommArea
id|xSpCommArea
suffix:semicolon
macro_line|#endif /* _ITSPCOMMAREA_H */
eof
