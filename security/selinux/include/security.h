multiline_comment|/*&n; * Security server interface.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SELINUX_SECURITY_H_
DECL|macro|_SELINUX_SECURITY_H_
mdefine_line|#define _SELINUX_SECURITY_H_
macro_line|#include &quot;flask.h&quot;
DECL|macro|SECSID_NULL
mdefine_line|#define SECSID_NULL&t;&t;&t;0x00000000 /* unspecified SID */
DECL|macro|SECSID_WILD
mdefine_line|#define SECSID_WILD&t;&t;&t;0xffffffff /* wildcard SID */
DECL|macro|SECCLASS_NULL
mdefine_line|#define SECCLASS_NULL&t;&t;&t;0x0000 /* no class */
DECL|macro|SELINUX_MAGIC
mdefine_line|#define SELINUX_MAGIC 0xf97cff8c
DECL|macro|POLICYDB_VERSION
mdefine_line|#define POLICYDB_VERSION 15
macro_line|#ifdef CONFIG_SECURITY_SELINUX_BOOTPARAM
r_extern
r_int
id|selinux_enabled
suffix:semicolon
macro_line|#else
DECL|macro|selinux_enabled
mdefine_line|#define selinux_enabled 1
macro_line|#endif
r_int
id|security_load_policy
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|len
)paren
suffix:semicolon
DECL|struct|av_decision
r_struct
id|av_decision
(brace
DECL|member|allowed
id|u32
id|allowed
suffix:semicolon
DECL|member|decided
id|u32
id|decided
suffix:semicolon
DECL|member|auditallow
id|u32
id|auditallow
suffix:semicolon
DECL|member|auditdeny
id|u32
id|auditdeny
suffix:semicolon
DECL|member|seqno
id|u32
id|seqno
suffix:semicolon
)brace
suffix:semicolon
r_int
id|security_compute_av
c_func
(paren
id|u32
id|ssid
comma
id|u32
id|tsid
comma
id|u16
id|tclass
comma
id|u32
id|requested
comma
r_struct
id|av_decision
op_star
id|avd
)paren
suffix:semicolon
r_int
id|security_transition_sid
c_func
(paren
id|u32
id|ssid
comma
id|u32
id|tsid
comma
id|u16
id|tclass
comma
id|u32
op_star
id|out_sid
)paren
suffix:semicolon
r_int
id|security_member_sid
c_func
(paren
id|u32
id|ssid
comma
id|u32
id|tsid
comma
id|u16
id|tclass
comma
id|u32
op_star
id|out_sid
)paren
suffix:semicolon
r_int
id|security_change_sid
c_func
(paren
id|u32
id|ssid
comma
id|u32
id|tsid
comma
id|u16
id|tclass
comma
id|u32
op_star
id|out_sid
)paren
suffix:semicolon
r_int
id|security_sid_to_context
c_func
(paren
id|u32
id|sid
comma
r_char
op_star
op_star
id|scontext
comma
id|u32
op_star
id|scontext_len
)paren
suffix:semicolon
r_int
id|security_context_to_sid
c_func
(paren
r_char
op_star
id|scontext
comma
id|u32
id|scontext_len
comma
id|u32
op_star
id|out_sid
)paren
suffix:semicolon
r_int
id|security_get_user_sids
c_func
(paren
id|u32
id|callsid
comma
r_char
op_star
id|username
comma
id|u32
op_star
op_star
id|sids
comma
id|u32
op_star
id|nel
)paren
suffix:semicolon
r_int
id|security_port_sid
c_func
(paren
id|u16
id|domain
comma
id|u16
id|type
comma
id|u8
id|protocol
comma
id|u16
id|port
comma
id|u32
op_star
id|out_sid
)paren
suffix:semicolon
r_int
id|security_netif_sid
c_func
(paren
r_char
op_star
id|name
comma
id|u32
op_star
id|if_sid
comma
id|u32
op_star
id|msg_sid
)paren
suffix:semicolon
r_int
id|security_node_sid
c_func
(paren
id|u16
id|domain
comma
r_void
op_star
id|addr
comma
id|u32
id|addrlen
comma
id|u32
op_star
id|out_sid
)paren
suffix:semicolon
DECL|macro|SECURITY_FS_USE_XATTR
mdefine_line|#define SECURITY_FS_USE_XATTR&t;&t;1 /* use xattr */
DECL|macro|SECURITY_FS_USE_TRANS
mdefine_line|#define SECURITY_FS_USE_TRANS&t;&t;2 /* use transition SIDs, e.g. devpts/tmpfs */
DECL|macro|SECURITY_FS_USE_TASK
mdefine_line|#define SECURITY_FS_USE_TASK&t;&t;3 /* use task SIDs, e.g. pipefs/sockfs */
DECL|macro|SECURITY_FS_USE_GENFS
mdefine_line|#define SECURITY_FS_USE_GENFS&t;&t;4 /* use the genfs support */
DECL|macro|SECURITY_FS_USE_NONE
mdefine_line|#define SECURITY_FS_USE_NONE&t;&t;5 /* no labeling support */
DECL|macro|SECURITY_FS_USE_MNTPOINT
mdefine_line|#define SECURITY_FS_USE_MNTPOINT&t;6 /* use mountpoint labeling */
r_int
id|security_fs_use
c_func
(paren
r_const
r_char
op_star
id|fstype
comma
r_int
r_int
op_star
id|behavior
comma
id|u32
op_star
id|sid
)paren
suffix:semicolon
r_int
id|security_genfs_sid
c_func
(paren
r_const
r_char
op_star
id|fstype
comma
r_char
op_star
id|name
comma
id|u16
id|sclass
comma
id|u32
op_star
id|sid
)paren
suffix:semicolon
macro_line|#endif /* _SELINUX_SECURITY_H_ */
eof
