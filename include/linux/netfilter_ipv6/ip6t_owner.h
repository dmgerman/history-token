macro_line|#ifndef _IP6T_OWNER_H
DECL|macro|_IP6T_OWNER_H
mdefine_line|#define _IP6T_OWNER_H
multiline_comment|/* match and invert flags */
DECL|macro|IP6T_OWNER_UID
mdefine_line|#define IP6T_OWNER_UID&t;0x01
DECL|macro|IP6T_OWNER_GID
mdefine_line|#define IP6T_OWNER_GID&t;0x02
DECL|macro|IP6T_OWNER_PID
mdefine_line|#define IP6T_OWNER_PID&t;0x04
DECL|macro|IP6T_OWNER_SID
mdefine_line|#define IP6T_OWNER_SID&t;0x08
DECL|struct|ip6t_owner_info
r_struct
id|ip6t_owner_info
(brace
DECL|member|uid
id|uid_t
id|uid
suffix:semicolon
DECL|member|gid
id|gid_t
id|gid
suffix:semicolon
DECL|member|pid
id|pid_t
id|pid
suffix:semicolon
DECL|member|sid
id|pid_t
id|sid
suffix:semicolon
DECL|member|match
DECL|member|invert
id|u_int8_t
id|match
comma
id|invert
suffix:semicolon
multiline_comment|/* flags */
)brace
suffix:semicolon
macro_line|#endif /*_IPT_OWNER_H*/
eof
