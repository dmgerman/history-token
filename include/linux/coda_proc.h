multiline_comment|/*&n; * coda_statis.h&n; * &n; * CODA operation statistics&n; *&n; * (c) March, 1998&n; * by Michihiro Kuramochi, Zhenyu Xia and Zhanyong Wan&n; * zhanyong.wan@yale.edu&n; *&n; */
macro_line|#ifndef _CODA_PROC_H
DECL|macro|_CODA_PROC_H
mdefine_line|#define _CODA_PROC_H
r_void
id|coda_sysctl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coda_sysctl_clean
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
multiline_comment|/* these four files are presented to show the result of the statistics:&n; *&n; *&t;/proc/fs/coda/vfs_stats&n; *&t;&t;      cache_inv_stats&n; *&n; * these four files are presented to reset the statistics to 0:&n; *&n; *&t;/proc/sys/coda/vfs_stats&n; *&t;&t;       cache_inv_stats&n; */
multiline_comment|/* VFS operation statistics */
DECL|struct|coda_vfs_stats
r_struct
id|coda_vfs_stats
(brace
multiline_comment|/* file operations */
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|flush
r_int
id|flush
suffix:semicolon
DECL|member|release
r_int
id|release
suffix:semicolon
DECL|member|fsync
r_int
id|fsync
suffix:semicolon
multiline_comment|/* dir operations */
DECL|member|readdir
r_int
id|readdir
suffix:semicolon
multiline_comment|/* inode operations */
DECL|member|create
r_int
id|create
suffix:semicolon
DECL|member|lookup
r_int
id|lookup
suffix:semicolon
DECL|member|link
r_int
id|link
suffix:semicolon
DECL|member|unlink
r_int
id|unlink
suffix:semicolon
DECL|member|symlink
r_int
id|symlink
suffix:semicolon
DECL|member|mkdir
r_int
id|mkdir
suffix:semicolon
DECL|member|rmdir
r_int
id|rmdir
suffix:semicolon
DECL|member|rename
r_int
id|rename
suffix:semicolon
DECL|member|permission
r_int
id|permission
suffix:semicolon
multiline_comment|/* symlink operatoins*/
DECL|member|follow_link
r_int
id|follow_link
suffix:semicolon
DECL|member|readlink
r_int
id|readlink
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* cache invalidation statistics */
DECL|struct|coda_cache_inv_stats
r_struct
id|coda_cache_inv_stats
(brace
DECL|member|flush
r_int
id|flush
suffix:semicolon
DECL|member|purge_user
r_int
id|purge_user
suffix:semicolon
DECL|member|zap_dir
r_int
id|zap_dir
suffix:semicolon
DECL|member|zap_file
r_int
id|zap_file
suffix:semicolon
DECL|member|zap_vnode
r_int
id|zap_vnode
suffix:semicolon
DECL|member|purge_fid
r_int
id|purge_fid
suffix:semicolon
DECL|member|replace
r_int
id|replace
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* these global variables hold the actual statistics data */
r_extern
r_struct
id|coda_vfs_stats
id|coda_vfs_stat
suffix:semicolon
macro_line|#endif /* _CODA_PROC_H */
eof
