macro_line|#ifndef _ISO_FS_I
DECL|macro|_ISO_FS_I
mdefine_line|#define _ISO_FS_I
multiline_comment|/*&n; * iso fs inode data in memory&n; */
DECL|struct|iso_inode_info
r_struct
id|iso_inode_info
(brace
DECL|member|i_first_extent
r_int
r_int
id|i_first_extent
suffix:semicolon
DECL|member|i_file_format
r_int
r_char
id|i_file_format
suffix:semicolon
DECL|member|i_next_section_ino
r_int
r_int
id|i_next_section_ino
suffix:semicolon
DECL|member|i_section_size
id|off_t
id|i_section_size
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
