macro_line|#ifndef NFS_CLUSTER_H
DECL|macro|NFS_CLUSTER_H
mdefine_line|#define NFS_CLUSTER_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;linux/nfs_fs_sb.h&gt;
multiline_comment|/*&n; * Counters of total number and pending number of requests.&n; * When the total number of requests exceeds the hard limit, we stall&n; * until it drops again.&n; */
DECL|macro|MAX_REQUEST_HARD
mdefine_line|#define MAX_REQUEST_HARD        256
multiline_comment|/*&n; * Maximum number of requests per write cluster.&n; * 32 requests per cluster account for 128K of data on an intel box.&n; * Note: it&squot;s a good idea to make this number smaller than MAX_REQUEST_SOFT.&n; *&n; * For 100Mbps Ethernet, 128 pages (i.e. 256K) per cluster gives much&n; * better performance.&n; */
DECL|macro|REQUEST_HASH_SIZE
mdefine_line|#define REQUEST_HASH_SIZE&t;16
DECL|macro|REQUEST_NR
mdefine_line|#define REQUEST_NR(off)&t;&t;((off) &gt;&gt; PAGE_CACHE_SHIFT)
DECL|macro|REQUEST_HASH
mdefine_line|#define REQUEST_HASH(ino, off)&t;(((ino) ^ REQUEST_NR(off)) &amp; (REQUEST_HASH_SIZE - 1))
multiline_comment|/*&n; * Functions&n; */
r_extern
r_int
id|nfs_reqlist_alloc
c_func
(paren
r_struct
id|nfs_server
op_star
)paren
suffix:semicolon
r_extern
r_void
id|nfs_reqlist_free
c_func
(paren
r_struct
id|nfs_server
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_reqlist_init
c_func
(paren
r_struct
id|nfs_server
op_star
)paren
suffix:semicolon
r_extern
r_void
id|nfs_reqlist_exit
c_func
(paren
r_struct
id|nfs_server
op_star
)paren
suffix:semicolon
r_extern
r_void
id|nfs_wake_flushd
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * This is the per-mount writeback cache.&n; */
DECL|struct|nfs_reqlist
r_struct
id|nfs_reqlist
(brace
DECL|member|nr_requests
id|atomic_t
id|nr_requests
suffix:semicolon
DECL|member|runat
r_int
r_int
id|runat
suffix:semicolon
DECL|member|request_wait
id|wait_queue_head_t
id|request_wait
suffix:semicolon
multiline_comment|/* The async RPC task that is responsible for scanning the&n;&t; * requests.&n;&t; */
DECL|member|task
r_struct
id|rpc_task
op_star
id|task
suffix:semicolon
multiline_comment|/* request flush task */
multiline_comment|/* Authentication flavor handle for this NFS client */
DECL|member|auth
r_struct
id|rpc_auth
op_star
id|auth
suffix:semicolon
multiline_comment|/* The list of all inodes with pending writebacks.  */
DECL|member|inodes
r_struct
id|inode
op_star
id|inodes
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
