multiline_comment|/*&n; *  Name                         : qnx4_fs_sb.h&n; *  Author                       : Richard Frowijn&n; *  Function                     : qnx4 superblock definitions&n; *  Version                      : 1.0.2&n; *  Last modified                : 2000-01-06&n; * &n; *  History                      : 23-03-1998 created&n; * &n; */
macro_line|#ifndef _QNX4_FS_SB
DECL|macro|_QNX4_FS_SB
mdefine_line|#define _QNX4_FS_SB
macro_line|#include &lt;linux/qnx4_fs.h&gt;
multiline_comment|/*&n; * qnx4 super-block data in memory&n; */
DECL|struct|qnx4_sb_info
r_struct
id|qnx4_sb_info
(brace
DECL|member|sb_buf
r_struct
id|buffer_head
op_star
id|sb_buf
suffix:semicolon
multiline_comment|/* superblock buffer */
DECL|member|sb
r_struct
id|qnx4_super_block
op_star
id|sb
suffix:semicolon
multiline_comment|/* our superblock */
DECL|member|Version
r_int
r_int
id|Version
suffix:semicolon
multiline_comment|/* may be useful */
DECL|member|BitMap
r_struct
id|qnx4_inode_entry
op_star
id|BitMap
suffix:semicolon
multiline_comment|/* useful */
)brace
suffix:semicolon
macro_line|#endif
eof
