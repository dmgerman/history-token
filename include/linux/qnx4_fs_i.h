multiline_comment|/*&n; *  Name                         : qnx4_fs_i.h&n; *  Author                       : Richard Frowijn&n; *  Function                     : qnx4 inode definitions&n; *  Version                      : 1.0.2&n; *  Last modified                : 2000-01-06&n; *&n; *  History                      : 23-03-1998 created&n; *&n; */
macro_line|#ifndef _QNX4_FS_I
DECL|macro|_QNX4_FS_I
mdefine_line|#define _QNX4_FS_I
macro_line|#include &lt;linux/qnxtypes.h&gt;
multiline_comment|/*&n; * qnx4 fs inode entry&n; */
DECL|struct|qnx4_inode_info
r_struct
id|qnx4_inode_info
(brace
DECL|member|i_reserved
r_char
id|i_reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|i_size
id|qnx4_off_t
id|i_size
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_first_xtnt
id|qnx4_xtnt_t
id|i_first_xtnt
suffix:semicolon
multiline_comment|/*  8 */
DECL|member|i_xblk
id|__u32
id|i_xblk
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_ftime
id|__s32
id|i_ftime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_mtime
id|__s32
id|i_mtime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_atime
id|__s32
id|i_atime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_ctime
id|__s32
id|i_ctime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_num_xtnts
id|qnx4_nxtnt_t
id|i_num_xtnts
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_mode
id|qnx4_mode_t
id|i_mode
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_uid
id|qnx4_muid_t
id|i_uid
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_gid
id|qnx4_mgid_t
id|i_gid
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_nlink
id|qnx4_nlink_t
id|i_nlink
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_zero
id|__u8
id|i_zero
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_type
id|qnx4_ftype_t
id|i_type
suffix:semicolon
multiline_comment|/*  1 */
DECL|member|i_status
id|__u8
id|i_status
suffix:semicolon
multiline_comment|/*  1 */
DECL|member|mmu_private
r_int
r_int
id|mmu_private
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
