multiline_comment|/*&n; * Access vector cache interface for object managers.&n; *&n; * Author : Stephen Smalley, &lt;sds@epoch.ncsc.mil&gt;&n; */
macro_line|#ifndef _SELINUX_AVC_H_
DECL|macro|_SELINUX_AVC_H_
mdefine_line|#define _SELINUX_AVC_H_
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;flask.h&quot;
macro_line|#include &quot;av_permissions.h&quot;
macro_line|#include &quot;security.h&quot;
macro_line|#ifdef CONFIG_SECURITY_SELINUX_DEVELOP
r_extern
r_int
id|selinux_enforcing
suffix:semicolon
macro_line|#else
DECL|macro|selinux_enforcing
mdefine_line|#define selinux_enforcing 1
macro_line|#endif
multiline_comment|/*&n; * An entry in the AVC.&n; */
r_struct
id|avc_entry
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_struct
id|vfsmount
suffix:semicolon
r_struct
id|dentry
suffix:semicolon
r_struct
id|inode
suffix:semicolon
r_struct
id|sock
suffix:semicolon
r_struct
id|sk_buff
suffix:semicolon
multiline_comment|/* Auxiliary data to use in generating the audit record. */
DECL|struct|avc_audit_data
r_struct
id|avc_audit_data
(brace
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|macro|AVC_AUDIT_DATA_FS
mdefine_line|#define AVC_AUDIT_DATA_FS   1
DECL|macro|AVC_AUDIT_DATA_NET
mdefine_line|#define AVC_AUDIT_DATA_NET  2
DECL|macro|AVC_AUDIT_DATA_CAP
mdefine_line|#define AVC_AUDIT_DATA_CAP  3
DECL|macro|AVC_AUDIT_DATA_IPC
mdefine_line|#define AVC_AUDIT_DATA_IPC  4
DECL|member|tsk
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|mnt
r_struct
id|vfsmount
op_star
id|mnt
suffix:semicolon
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|fs
)brace
id|fs
suffix:semicolon
r_struct
(brace
DECL|member|netif
r_char
op_star
id|netif
suffix:semicolon
DECL|member|sk
r_struct
id|sock
op_star
id|sk
suffix:semicolon
DECL|member|family
id|u16
id|family
suffix:semicolon
DECL|member|dport
id|u16
id|dport
suffix:semicolon
DECL|member|sport
id|u16
id|sport
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|daddr
id|u32
id|daddr
suffix:semicolon
DECL|member|saddr
id|u32
id|saddr
suffix:semicolon
DECL|member|v4
)brace
id|v4
suffix:semicolon
r_struct
(brace
DECL|member|daddr
r_struct
id|in6_addr
id|daddr
suffix:semicolon
DECL|member|saddr
r_struct
id|in6_addr
id|saddr
suffix:semicolon
DECL|member|v6
)brace
id|v6
suffix:semicolon
DECL|member|fam
)brace
id|fam
suffix:semicolon
DECL|member|net
)brace
id|net
suffix:semicolon
DECL|member|cap
r_int
id|cap
suffix:semicolon
DECL|member|ipc_id
r_int
id|ipc_id
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|v4info
mdefine_line|#define v4info fam.v4
DECL|macro|v6info
mdefine_line|#define v6info fam.v6
multiline_comment|/* Initialize an AVC audit data structure. */
DECL|macro|AVC_AUDIT_DATA_INIT
mdefine_line|#define AVC_AUDIT_DATA_INIT(_d,_t) &bslash;&n;        { memset((_d), 0, sizeof(struct avc_audit_data)); (_d)-&gt;type = AVC_AUDIT_DATA_##_t; }
multiline_comment|/*&n; * AVC statistics&n; */
DECL|macro|AVC_ENTRY_LOOKUPS
mdefine_line|#define AVC_ENTRY_LOOKUPS        0
DECL|macro|AVC_ENTRY_HITS
mdefine_line|#define AVC_ENTRY_HITS&t;         1
DECL|macro|AVC_ENTRY_MISSES
mdefine_line|#define AVC_ENTRY_MISSES         2
DECL|macro|AVC_ENTRY_DISCARDS
mdefine_line|#define AVC_ENTRY_DISCARDS       3
DECL|macro|AVC_CAV_LOOKUPS
mdefine_line|#define AVC_CAV_LOOKUPS          4
DECL|macro|AVC_CAV_HITS
mdefine_line|#define AVC_CAV_HITS             5
DECL|macro|AVC_CAV_PROBES
mdefine_line|#define AVC_CAV_PROBES           6
DECL|macro|AVC_CAV_MISSES
mdefine_line|#define AVC_CAV_MISSES           7
DECL|macro|AVC_NSTATS
mdefine_line|#define AVC_NSTATS               8
multiline_comment|/*&n; * AVC display support&n; */
r_struct
id|audit_buffer
suffix:semicolon
r_void
id|avc_dump_av
c_func
(paren
r_struct
id|audit_buffer
op_star
id|ab
comma
id|u16
id|tclass
comma
id|u32
id|av
)paren
suffix:semicolon
r_void
id|avc_dump_query
c_func
(paren
r_struct
id|audit_buffer
op_star
id|ab
comma
id|u32
id|ssid
comma
id|u32
id|tsid
comma
id|u16
id|tclass
)paren
suffix:semicolon
multiline_comment|/*&n; * AVC operations&n; */
r_void
id|__init
id|avc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|avc_audit
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
comma
r_int
id|result
comma
r_struct
id|avc_audit_data
op_star
id|auditdata
)paren
suffix:semicolon
r_int
id|avc_has_perm_noaudit
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
id|avc_has_perm
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
id|avc_audit_data
op_star
id|auditdata
)paren
suffix:semicolon
DECL|macro|AVC_CALLBACK_GRANT
mdefine_line|#define AVC_CALLBACK_GRANT&t;&t;1
DECL|macro|AVC_CALLBACK_TRY_REVOKE
mdefine_line|#define AVC_CALLBACK_TRY_REVOKE&t;&t;2
DECL|macro|AVC_CALLBACK_REVOKE
mdefine_line|#define AVC_CALLBACK_REVOKE&t;&t;4
DECL|macro|AVC_CALLBACK_RESET
mdefine_line|#define AVC_CALLBACK_RESET&t;&t;8
DECL|macro|AVC_CALLBACK_AUDITALLOW_ENABLE
mdefine_line|#define AVC_CALLBACK_AUDITALLOW_ENABLE&t;16
DECL|macro|AVC_CALLBACK_AUDITALLOW_DISABLE
mdefine_line|#define AVC_CALLBACK_AUDITALLOW_DISABLE&t;32
DECL|macro|AVC_CALLBACK_AUDITDENY_ENABLE
mdefine_line|#define AVC_CALLBACK_AUDITDENY_ENABLE&t;64
DECL|macro|AVC_CALLBACK_AUDITDENY_DISABLE
mdefine_line|#define AVC_CALLBACK_AUDITDENY_DISABLE&t;128
r_int
id|avc_add_callback
c_func
(paren
r_int
(paren
op_star
id|callback
)paren
(paren
id|u32
id|event
comma
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
id|perms
comma
id|u32
op_star
id|out_retained
)paren
comma
id|u32
id|events
comma
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
id|perms
)paren
suffix:semicolon
macro_line|#endif /* _SELINUX_AVC_H_ */
eof
