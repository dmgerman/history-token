macro_line|#ifndef _SYSV_FS_I
DECL|macro|_SYSV_FS_I
mdefine_line|#define _SYSV_FS_I
multiline_comment|/*&n; * SystemV/V7/Coherent FS inode data in memory&n; */
DECL|struct|sysv_inode_info
r_struct
id|sysv_inode_info
(brace
DECL|member|i_data
id|u32
id|i_data
(braket
l_int|10
op_plus
l_int|1
op_plus
l_int|1
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* zone numbers: max. 10 data blocks,&n;&t;&t;&t;&t; * then 1 indirection block,&n;&t;&t;&t;&t; * then 1 double indirection block,&n;&t;&t;&t;&t; * then 1 triple indirection block.&n;&t;&t;&t;&t; */
DECL|member|i_dir_start_lookup
id|u32
id|i_dir_start_lookup
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
