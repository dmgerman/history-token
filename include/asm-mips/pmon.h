multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2004 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_PMON_H
DECL|macro|_ASM_PMON_H
mdefine_line|#define _ASM_PMON_H
DECL|struct|callvectors
r_struct
id|callvectors
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&t; 0 */
DECL|member|close
r_int
(paren
op_star
id|close
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&t; 4 */
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&t; 8 */
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_int
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&t;12 */
DECL|member|lseek
id|off_t
(paren
op_star
id|lseek
)paren
(paren
r_int
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&t;16 */
DECL|member|printf
r_int
(paren
op_star
id|printf
)paren
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/*&t;20 */
DECL|member|cacheflush
r_void
(paren
op_star
id|cacheflush
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&t;24 */
DECL|member|gets
r_char
op_star
(paren
op_star
id|gets
)paren
(paren
r_char
op_star
)paren
suffix:semicolon
multiline_comment|/*&t;28 */
)brace
suffix:semicolon
macro_line|#endif /* _ASM_PMON_H */
eof
