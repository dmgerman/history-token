macro_line|#ifndef _REISER_FS_I
DECL|macro|_REISER_FS_I
mdefine_line|#define _REISER_FS_I
macro_line|#include &lt;linux/list.h&gt;
DECL|struct|reiserfs_inode_info
r_struct
id|reiserfs_inode_info
(brace
DECL|member|i_key
id|__u32
id|i_key
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* key is still 4 32 bit integers */
multiline_comment|/* this comment will be totally&n;                                   cryptic to readers not familiar&n;                                   with 3.5/3.6 format conversion, and&n;                                   it does not consider that that 3.6&n;                                   might not be the last version */
DECL|member|i_version
r_int
id|i_version
suffix:semicolon
singleline_comment|// this says whether file is old or new
DECL|member|i_pack_on_close
r_int
id|i_pack_on_close
suffix:semicolon
singleline_comment|// file might need tail packing on close 
DECL|member|i_first_direct_byte
id|__u32
id|i_first_direct_byte
suffix:semicolon
singleline_comment|// offset of first byte stored in direct item.
multiline_comment|/* My guess is this contains the first&n;                                   unused block of a sequence of&n;                                   blocks plus the length of the&n;                                   sequence, which I think is always&n;                                   at least two at the time of the&n;                                   preallocation.  I really prefer&n;                                   allocate on flush conceptually.....&n;&n;&t;&t;&t;&t;   You know, it really annoys me when&n;&t;&t;&t;&t;   code is this badly commented that I&n;&t;&t;&t;&t;   have to guess what it does.&n;&t;&t;&t;&t;   Neither I nor anyone else has time&n;&t;&t;&t;&t;   for guessing what your&n;&t;&t;&t;&t;   datastructures mean.  -Hans */
singleline_comment|//For preallocation
DECL|member|i_prealloc_block
r_int
id|i_prealloc_block
suffix:semicolon
DECL|member|i_prealloc_count
r_int
id|i_prealloc_count
suffix:semicolon
DECL|member|i_prealloc_list
r_struct
id|list_head
id|i_prealloc_list
suffix:semicolon
multiline_comment|/* per-transaction list of inodes which&n;&t;&t;&t;&t; * have preallocated blocks */
multiline_comment|/* I regret that you think the below&n;                                   is a comment you should make.... -Hans */
singleline_comment|//nopack-attribute
DECL|member|nopack
r_int
id|nopack
suffix:semicolon
multiline_comment|/* we use these for fsync or O_SYNC to decide which transaction needs&n;  ** to be committed in order for this inode to be properly flushed&n;  */
DECL|member|i_trans_id
r_int
r_int
id|i_trans_id
suffix:semicolon
DECL|member|i_trans_index
r_int
r_int
id|i_trans_index
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
