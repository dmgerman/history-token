macro_line|#ifndef _ASM_M68K_FD_H
DECL|macro|_ASM_M68K_FD_H
mdefine_line|#define _ASM_M68K_FD_H
multiline_comment|/* Definitions for the Atari Floppy driver */
DECL|struct|atari_format_descr
r_struct
id|atari_format_descr
(brace
DECL|member|track
r_int
id|track
suffix:semicolon
multiline_comment|/* to be formatted */
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/*   &quot;&quot;     &quot;&quot;     */
DECL|member|sect_offset
r_int
id|sect_offset
suffix:semicolon
multiline_comment|/* offset of first sector */
)brace
suffix:semicolon
macro_line|#endif
eof
