multiline_comment|/*&n; * linux/include/linux/lockd/bind.h&n; *&n; * This is the part of lockd visible to nfsd and the nfs client.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_LOCKD_BIND_H
DECL|macro|LINUX_LOCKD_BIND_H
mdefine_line|#define LINUX_LOCKD_BIND_H
macro_line|#include &lt;linux/lockd/nlm.h&gt;
multiline_comment|/* Dummy declarations */
r_struct
id|svc_rqst
suffix:semicolon
r_struct
id|svc_client
suffix:semicolon
multiline_comment|/* opaque type */
multiline_comment|/*&n; * This is the set of functions for lockd-&gt;nfsd communication&n; */
DECL|struct|nlmsvc_binding
r_struct
id|nlmsvc_binding
(brace
DECL|member|fopen
id|u32
(paren
op_star
id|fopen
)paren
(paren
r_struct
id|svc_rqst
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
DECL|member|fclose
r_void
(paren
op_star
id|fclose
)paren
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|nlmsvc_binding
op_star
id|nlmsvc_ops
suffix:semicolon
multiline_comment|/*&n; * Functions exported by the lockd module&n; */
r_extern
r_int
id|nlmclnt_proc
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
r_extern
r_int
id|lockd_up
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|lockd_down
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* LINUX_LOCKD_BIND_H */
eof
