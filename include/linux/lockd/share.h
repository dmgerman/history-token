multiline_comment|/*&n; * linux/include/linux/lockd/share.h&n; *&n; * DOS share management for lockd.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_LOCKD_SHARE_H
DECL|macro|LINUX_LOCKD_SHARE_H
mdefine_line|#define LINUX_LOCKD_SHARE_H
multiline_comment|/*&n; * DOS share for a specific file&n; */
DECL|struct|nlm_share
r_struct
id|nlm_share
(brace
DECL|member|s_next
r_struct
id|nlm_share
op_star
id|s_next
suffix:semicolon
multiline_comment|/* linked list */
DECL|member|s_host
r_struct
id|nlm_host
op_star
id|s_host
suffix:semicolon
multiline_comment|/* client host */
DECL|member|s_file
r_struct
id|nlm_file
op_star
id|s_file
suffix:semicolon
multiline_comment|/* shared file */
DECL|member|s_owner
r_struct
id|xdr_netobj
id|s_owner
suffix:semicolon
multiline_comment|/* owner handle */
DECL|member|s_access
id|u32
id|s_access
suffix:semicolon
multiline_comment|/* access mode */
DECL|member|s_mode
id|u32
id|s_mode
suffix:semicolon
multiline_comment|/* deny mode */
)brace
suffix:semicolon
id|u32
id|nlmsvc_share_file
c_func
(paren
r_struct
id|nlm_host
op_star
comma
r_struct
id|nlm_file
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
id|u32
id|nlmsvc_unshare_file
c_func
(paren
r_struct
id|nlm_host
op_star
comma
r_struct
id|nlm_file
op_star
comma
r_struct
id|nlm_args
op_star
)paren
suffix:semicolon
r_int
id|nlmsvc_traverse_shares
c_func
(paren
r_struct
id|nlm_host
op_star
comma
r_struct
id|nlm_file
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* LINUX_LOCKD_SHARE_H */
eof
