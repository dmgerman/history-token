macro_line|#ifndef _MINIX_FS_I
DECL|macro|_MINIX_FS_I
mdefine_line|#define _MINIX_FS_I
multiline_comment|/*&n; * minix fs inode data in memory&n; */
DECL|struct|minix_inode_info
r_struct
id|minix_inode_info
(brace
r_union
(brace
DECL|member|i1_data
id|__u16
id|i1_data
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|i2_data
id|__u32
id|i2_data
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
