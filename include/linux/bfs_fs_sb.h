multiline_comment|/*&n; *&t;include/linux/bfs_fs_sb.h&n; *&t;Copyright (C) 1999 Tigran Aivazian &lt;tigran@veritas.com&gt;&n; */
macro_line|#ifndef _LINUX_BFS_FS_SB
DECL|macro|_LINUX_BFS_FS_SB
mdefine_line|#define _LINUX_BFS_FS_SB
multiline_comment|/*&n; * BFS file system in-core superblock info&n; */
DECL|struct|bfs_sb_info
r_struct
id|bfs_sb_info
(brace
DECL|member|si_blocks
r_int
r_int
id|si_blocks
suffix:semicolon
DECL|member|si_freeb
r_int
r_int
id|si_freeb
suffix:semicolon
DECL|member|si_freei
r_int
r_int
id|si_freei
suffix:semicolon
DECL|member|si_lf_ioff
r_int
r_int
id|si_lf_ioff
suffix:semicolon
DECL|member|si_lf_sblk
r_int
r_int
id|si_lf_sblk
suffix:semicolon
DECL|member|si_lf_eblk
r_int
r_int
id|si_lf_eblk
suffix:semicolon
DECL|member|si_lasti
r_int
r_int
id|si_lasti
suffix:semicolon
DECL|member|si_imap
r_char
op_star
id|si_imap
suffix:semicolon
DECL|member|si_sbh
r_struct
id|buffer_head
op_star
id|si_sbh
suffix:semicolon
multiline_comment|/* buffer header w/superblock */
DECL|member|si_bfs_sb
r_struct
id|bfs_super_block
op_star
id|si_bfs_sb
suffix:semicolon
multiline_comment|/* superblock in si_sbh-&gt;b_data */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_BFS_FS_SB */
eof
