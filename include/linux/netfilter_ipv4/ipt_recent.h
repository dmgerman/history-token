macro_line|#ifndef _IPT_RECENT_H
DECL|macro|_IPT_RECENT_H
mdefine_line|#define _IPT_RECENT_H
DECL|macro|RECENT_NAME
mdefine_line|#define RECENT_NAME&t;&quot;ipt_recent&quot;
DECL|macro|RECENT_VER
mdefine_line|#define RECENT_VER&t;&quot;v0.3.1&quot;
DECL|macro|IPT_RECENT_CHECK
mdefine_line|#define IPT_RECENT_CHECK  1
DECL|macro|IPT_RECENT_SET
mdefine_line|#define IPT_RECENT_SET    2
DECL|macro|IPT_RECENT_UPDATE
mdefine_line|#define IPT_RECENT_UPDATE 4
DECL|macro|IPT_RECENT_REMOVE
mdefine_line|#define IPT_RECENT_REMOVE 8
DECL|macro|IPT_RECENT_TTL
mdefine_line|#define IPT_RECENT_TTL   16
DECL|macro|IPT_RECENT_SOURCE
mdefine_line|#define IPT_RECENT_SOURCE 0
DECL|macro|IPT_RECENT_DEST
mdefine_line|#define IPT_RECENT_DEST   1
DECL|macro|IPT_RECENT_NAME_LEN
mdefine_line|#define IPT_RECENT_NAME_LEN 200
DECL|struct|ipt_recent_info
r_struct
id|ipt_recent_info
(brace
DECL|member|seconds
id|u_int32_t
id|seconds
suffix:semicolon
DECL|member|hit_count
id|u_int32_t
id|hit_count
suffix:semicolon
DECL|member|check_set
id|u_int8_t
id|check_set
suffix:semicolon
DECL|member|invert
id|u_int8_t
id|invert
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|IPT_RECENT_NAME_LEN
)braket
suffix:semicolon
DECL|member|side
id|u_int8_t
id|side
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_RECENT_H*/
eof
