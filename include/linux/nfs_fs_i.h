macro_line|#ifndef _NFS_FS_I
DECL|macro|_NFS_FS_I
mdefine_line|#define _NFS_FS_I
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
multiline_comment|/*&n; * nfs fs inode data in memory&n; */
DECL|struct|nfs_inode_info
r_struct
id|nfs_inode_info
(brace
multiline_comment|/*&n;&t; * The 64bit &squot;inode number&squot;&n;&t; */
DECL|member|fsid
id|__u64
id|fsid
suffix:semicolon
DECL|member|fileid
id|__u64
id|fileid
suffix:semicolon
multiline_comment|/*&n;&t; * NFS file handle&n;&t; */
DECL|member|fh
r_struct
id|nfs_fh
id|fh
suffix:semicolon
multiline_comment|/*&n;&t; * Various flags&n;&t; */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * read_cache_jiffies is when we started read-caching this inode,&n;&t; * and read_cache_mtime is the mtime of the inode at that time.&n;&t; * attrtimeo is for how long the cached information is assumed&n;&t; * to be valid. A successful attribute revalidation doubles&n;&t; * attrtimeo (up to acregmax/acdirmax), a failure resets it to&n;&t; * acregmin/acdirmin.&n;&t; *&n;&t; * We need to revalidate the cached attrs for this inode if&n;&t; *&n;&t; *&t;jiffies - read_cache_jiffies &gt; attrtimeo&n;&t; *&n;&t; * and invalidate any cached data/flush out any dirty pages if&n;&t; * we find that&n;&t; *&n;&t; *&t;mtime != read_cache_mtime&n;&t; */
DECL|member|read_cache_jiffies
r_int
r_int
id|read_cache_jiffies
suffix:semicolon
DECL|member|read_cache_ctime
id|__u64
id|read_cache_ctime
suffix:semicolon
DECL|member|read_cache_mtime
id|__u64
id|read_cache_mtime
suffix:semicolon
DECL|member|read_cache_atime
id|__u64
id|read_cache_atime
suffix:semicolon
DECL|member|read_cache_isize
id|__u64
id|read_cache_isize
suffix:semicolon
DECL|member|attrtimeo
r_int
r_int
id|attrtimeo
suffix:semicolon
DECL|member|attrtimeo_timestamp
r_int
r_int
id|attrtimeo_timestamp
suffix:semicolon
multiline_comment|/*&n;&t; * This is the cookie verifier used for NFSv3 readdir&n;&t; * operations&n;&t; */
DECL|member|cookieverf
id|__u32
id|cookieverf
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * This is the list of dirty unwritten pages.&n;&t; */
DECL|member|read
r_struct
id|list_head
id|read
suffix:semicolon
DECL|member|dirty
r_struct
id|list_head
id|dirty
suffix:semicolon
DECL|member|commit
r_struct
id|list_head
id|commit
suffix:semicolon
DECL|member|writeback
r_struct
id|list_head
id|writeback
suffix:semicolon
DECL|member|nread
r_int
r_int
id|nread
comma
DECL|member|ndirty
id|ndirty
comma
DECL|member|ncommit
id|ncommit
comma
DECL|member|npages
id|npages
suffix:semicolon
multiline_comment|/* Flush daemon info */
DECL|member|hash_next
r_struct
id|inode
op_star
id|hash_next
comma
DECL|member|hash_prev
op_star
id|hash_prev
suffix:semicolon
DECL|member|nextscan
r_int
r_int
id|nextscan
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Legal inode flag values&n; */
DECL|macro|NFS_INO_STALE
mdefine_line|#define NFS_INO_STALE&t;&t;0x0001&t;&t;/* possible stale inode */
DECL|macro|NFS_INO_ADVISE_RDPLUS
mdefine_line|#define NFS_INO_ADVISE_RDPLUS   0x0002          /* advise readdirplus */
DECL|macro|NFS_INO_REVALIDATING
mdefine_line|#define NFS_INO_REVALIDATING&t;0x0004&t;&t;/* revalidating attrs */
DECL|macro|NFS_IS_SNAPSHOT
mdefine_line|#define NFS_IS_SNAPSHOT&t;&t;0x0010&t;&t;/* a snapshot file */
DECL|macro|NFS_INO_FLUSH
mdefine_line|#define NFS_INO_FLUSH&t;&t;0x0020&t;&t;/* inode is due for flushing */
multiline_comment|/*&n; * NFS lock info&n; */
DECL|struct|nfs_lock_info
r_struct
id|nfs_lock_info
(brace
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|host
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Lock flag values&n; */
DECL|macro|NFS_LCK_GRANTED
mdefine_line|#define NFS_LCK_GRANTED&t;&t;0x0001&t;&t;/* lock has been granted */
macro_line|#endif
eof
