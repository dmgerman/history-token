macro_line|#ifndef _NFS_FS_I
DECL|macro|_NFS_FS_I
mdefine_line|#define _NFS_FS_I
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
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
DECL|macro|NFS_LCK_RECLAIM
mdefine_line|#define NFS_LCK_RECLAIM&t;&t;0x0002&t;&t;/* lock marked for reclaiming */
macro_line|#endif
eof
