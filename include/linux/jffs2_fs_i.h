multiline_comment|/* $Id: jffs2_fs_i.h,v 1.8 2001/04/18 13:05:28 dwmw2 Exp $ */
macro_line|#ifndef _JFFS2_FS_I
DECL|macro|_JFFS2_FS_I
mdefine_line|#define _JFFS2_FS_I
multiline_comment|/* Include the pipe_inode_info at the beginning so that we can still&n;   use the storage space in the inode when we have a pipe inode.&n;   This sucks.&n;*/
DECL|macro|THISSUCKS
macro_line|#undef THISSUCKS /* Only for 2.2 */
macro_line|#ifdef THISSUCKS
macro_line|#include &lt;linux/pipe_fs_i.h&gt;
macro_line|#endif
DECL|struct|jffs2_inode_info
r_struct
id|jffs2_inode_info
(brace
macro_line|#ifdef THISSUCKS
DECL|member|pipecrap
r_struct
id|pipe_inode_info
id|pipecrap
suffix:semicolon
macro_line|#endif
multiline_comment|/* We need an internal semaphore similar to inode-&gt;i_sem.&n;&t;   Unfortunately, we can&squot;t used the existing one, because&n;&t;   either the GC would deadlock, or we&squot;d have to release it&n;&t;   before letting GC proceed. Or we&squot;d have to put ugliness&n;&t;   into the GC code so it didn&squot;t attempt to obtain the i_sem&n;&t;   for the inode(s) which are already locked */
DECL|member|sem
r_struct
id|semaphore
id|sem
suffix:semicolon
multiline_comment|/* The highest (datanode) version number used for this ino */
DECL|member|highest_version
id|__u32
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
multiline_comment|/* Keep a pointer to the last physical node in the list. We don&squot;t &n;&t;   use the doubly-linked lists because we don&squot;t want to increase&n;&t;   the memory usage that much. This is simpler */
singleline_comment|//&t;struct jffs2_raw_node_ref *lastnode;
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
DECL|member|usercompr
id|__u8
id|usercompr
suffix:semicolon
DECL|member|vfs_inode
r_struct
id|inode
id|vfs_inode
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef JFFS2_OUT_OF_KERNEL
DECL|macro|JFFS2_INODE_INFO
mdefine_line|#define JFFS2_INODE_INFO(i) ((struct jffs2_inode_info *) &amp;(i)-&gt;u)
macro_line|#else
DECL|function|JFFS2_INODE_INFO
r_static
r_inline
r_struct
id|jffs2_inode_info
op_star
id|JFFS2_INODE_INFO
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|list_entry
c_func
(paren
id|inode
comma
r_struct
id|jffs2_inode_info
comma
id|vfs_inode
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _JFFS2_FS_I */
eof
