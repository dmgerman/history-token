multiline_comment|/* $Id: jffs2_fs_i.h,v 1.12 2002/03/06 13:59:21 dwmw2 Exp $ */
macro_line|#ifndef _JFFS2_FS_I
DECL|macro|_JFFS2_FS_I
mdefine_line|#define _JFFS2_FS_I
macro_line|#include &lt;linux/version.h&gt;
DECL|struct|jffs2_inode_info
r_struct
id|jffs2_inode_info
(brace
multiline_comment|/* We need an internal semaphore similar to inode-&gt;i_sem.&n;&t;   Unfortunately, we can&squot;t used the existing one, because&n;&t;   either the GC would deadlock, or we&squot;d have to release it&n;&t;   before letting GC proceed. Or we&squot;d have to put ugliness&n;&t;   into the GC code so it didn&squot;t attempt to obtain the i_sem&n;&t;   for the inode(s) which are already locked */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* The highest (datanode) version number used for this ino */
DECL|member|highest_version
r_uint32
id|highest_version
suffix:semicolon
multiline_comment|/* List of data fragments which make up the file */
DECL|member|fraglist
r_struct
id|jffs2_node_frag
op_star
id|fraglist
suffix:semicolon
multiline_comment|/* There may be one datanode which isn&squot;t referenced by any of the&n;&t;   above fragments, if it contains a metadata update but no actual&n;&t;   data - or if this is a directory inode */
multiline_comment|/* This also holds the _only_ dnode for symlinks/device nodes, &n;&t;   etc. */
DECL|member|metadata
r_struct
id|jffs2_full_dnode
op_star
id|metadata
suffix:semicolon
multiline_comment|/* Directory entries */
DECL|member|dents
r_struct
id|jffs2_full_dirent
op_star
id|dents
suffix:semicolon
multiline_comment|/* Some stuff we just have to keep in-core at all times, for each inode. */
DECL|member|inocache
r_struct
id|jffs2_inode_cache
op_star
id|inocache
suffix:semicolon
DECL|member|flags
r_uint16
id|flags
suffix:semicolon
DECL|member|usercompr
r_uint8
id|usercompr
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,5,2)
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* _JFFS2_FS_I */
eof
