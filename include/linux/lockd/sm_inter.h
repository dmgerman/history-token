multiline_comment|/*&n; * linux/include/linux/lockd/sm_inter.h&n; *&n; * Declarations for the kernel statd client.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_LOCKD_SM_INTER_H
DECL|macro|LINUX_LOCKD_SM_INTER_H
mdefine_line|#define LINUX_LOCKD_SM_INTER_H
DECL|macro|SM_PROGRAM
mdefine_line|#define SM_PROGRAM&t;100024
DECL|macro|SM_VERSION
mdefine_line|#define SM_VERSION&t;1
DECL|macro|SM_STAT
mdefine_line|#define SM_STAT&t;&t;1
DECL|macro|SM_MON
mdefine_line|#define SM_MON&t;&t;2
DECL|macro|SM_UNMON
mdefine_line|#define SM_UNMON&t;3
DECL|macro|SM_UNMON_ALL
mdefine_line|#define SM_UNMON_ALL&t;4
DECL|macro|SM_SIMU_CRASH
mdefine_line|#define SM_SIMU_CRASH&t;5
DECL|macro|SM_NOTIFY
mdefine_line|#define SM_NOTIFY&t;6
DECL|macro|SM_MAXSTRLEN
mdefine_line|#define SM_MAXSTRLEN&t;1024
multiline_comment|/*&n; * Arguments for all calls to statd&n; */
DECL|struct|nsm_args
r_struct
id|nsm_args
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
multiline_comment|/* remote address */
DECL|member|prog
id|u32
id|prog
suffix:semicolon
multiline_comment|/* RPC callback info */
DECL|member|vers
id|u32
id|vers
suffix:semicolon
DECL|member|proc
id|u32
id|proc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Result returned by statd&n; */
DECL|struct|nsm_res
r_struct
id|nsm_res
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
)brace
suffix:semicolon
r_int
id|nsm_monitor
c_func
(paren
r_struct
id|nlm_host
op_star
)paren
suffix:semicolon
r_int
id|nsm_unmonitor
c_func
(paren
r_struct
id|nlm_host
op_star
)paren
suffix:semicolon
r_extern
id|u32
id|nsm_local_state
suffix:semicolon
macro_line|#endif /* LINUX_LOCKD_SM_INTER_H */
eof
