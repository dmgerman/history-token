macro_line|#ifndef _IPT_HASHLIMIT_H
DECL|macro|_IPT_HASHLIMIT_H
mdefine_line|#define _IPT_HASHLIMIT_H
multiline_comment|/* timings are in milliseconds. */
DECL|macro|IPT_HASHLIMIT_SCALE
mdefine_line|#define IPT_HASHLIMIT_SCALE 10000
multiline_comment|/* 1/10,000 sec period =&gt; max of 10,000/sec.  Min rate is then 429490&n;   seconds, or one every 59 hours. */
multiline_comment|/* details of this structure hidden by the implementation */
r_struct
id|ipt_hashlimit_htable
suffix:semicolon
DECL|macro|IPT_HASHLIMIT_HASH_DIP
mdefine_line|#define IPT_HASHLIMIT_HASH_DIP&t;0x0001
DECL|macro|IPT_HASHLIMIT_HASH_DPT
mdefine_line|#define IPT_HASHLIMIT_HASH_DPT&t;0x0002
DECL|macro|IPT_HASHLIMIT_HASH_SIP
mdefine_line|#define IPT_HASHLIMIT_HASH_SIP&t;0x0004
DECL|macro|IPT_HASHLIMIT_HASH_SPT
mdefine_line|#define IPT_HASHLIMIT_HASH_SPT&t;0x0008
DECL|struct|hashlimit_cfg
r_struct
id|hashlimit_cfg
(brace
DECL|member|mode
id|u_int32_t
id|mode
suffix:semicolon
multiline_comment|/* bitmask of IPT_HASHLIMIT_HASH_* */
DECL|member|avg
id|u_int32_t
id|avg
suffix:semicolon
multiline_comment|/* Average secs between packets * scale */
DECL|member|burst
id|u_int32_t
id|burst
suffix:semicolon
multiline_comment|/* Period multiplier for upper limit. */
multiline_comment|/* user specified */
DECL|member|size
id|u_int32_t
id|size
suffix:semicolon
multiline_comment|/* how many buckets */
DECL|member|max
id|u_int32_t
id|max
suffix:semicolon
multiline_comment|/* max number of entries */
DECL|member|gc_interval
id|u_int32_t
id|gc_interval
suffix:semicolon
multiline_comment|/* gc interval */
DECL|member|expire
id|u_int32_t
id|expire
suffix:semicolon
multiline_comment|/* when do entries expire? */
)brace
suffix:semicolon
DECL|struct|ipt_hashlimit_info
r_struct
id|ipt_hashlimit_info
(brace
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* name */
DECL|member|cfg
r_struct
id|hashlimit_cfg
id|cfg
suffix:semicolon
DECL|member|hinfo
r_struct
id|ipt_hashlimit_htable
op_star
id|hinfo
suffix:semicolon
multiline_comment|/* Used internally by the kernel */
r_union
(brace
DECL|member|ptr
r_void
op_star
id|ptr
suffix:semicolon
DECL|member|master
r_struct
id|ipt_hashlimit_info
op_star
id|master
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_HASHLIMIT_H*/
eof
