macro_line|#ifndef _IPT_SCTP_H_
DECL|macro|_IPT_SCTP_H_
mdefine_line|#define _IPT_SCTP_H_
DECL|macro|IPT_SCTP_SRC_PORTS
mdefine_line|#define IPT_SCTP_SRC_PORTS&t;        0x01
DECL|macro|IPT_SCTP_DEST_PORTS
mdefine_line|#define IPT_SCTP_DEST_PORTS&t;        0x02
DECL|macro|IPT_SCTP_CHUNK_TYPES
mdefine_line|#define IPT_SCTP_CHUNK_TYPES&t;&t;0x04
DECL|macro|IPT_SCTP_VALID_FLAGS
mdefine_line|#define IPT_SCTP_VALID_FLAGS&t;&t;0x07
DECL|macro|ELEMCOUNT
mdefine_line|#define ELEMCOUNT(x) (sizeof(x)/sizeof(x[0]))
DECL|struct|ipt_sctp_flag_info
r_struct
id|ipt_sctp_flag_info
(brace
DECL|member|chunktype
id|u_int8_t
id|chunktype
suffix:semicolon
DECL|member|flag
id|u_int8_t
id|flag
suffix:semicolon
DECL|member|flag_mask
id|u_int8_t
id|flag_mask
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IPT_NUM_SCTP_FLAGS
mdefine_line|#define IPT_NUM_SCTP_FLAGS&t;4
DECL|struct|ipt_sctp_info
r_struct
id|ipt_sctp_info
(brace
DECL|member|dpts
id|u_int16_t
id|dpts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Min, Max */
DECL|member|spts
id|u_int16_t
id|spts
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Min, Max */
DECL|member|chunkmap
id|u_int32_t
id|chunkmap
(braket
l_int|256
op_div
r_sizeof
(paren
id|u_int32_t
)paren
)braket
suffix:semicolon
multiline_comment|/* Bit mask of chunks to be matched according to RFC 2960 */
DECL|macro|SCTP_CHUNK_MATCH_ANY
mdefine_line|#define SCTP_CHUNK_MATCH_ANY   0x01  /* Match if any of the chunk types are present */
DECL|macro|SCTP_CHUNK_MATCH_ALL
mdefine_line|#define SCTP_CHUNK_MATCH_ALL   0x02  /* Match if all of the chunk types are present */
DECL|macro|SCTP_CHUNK_MATCH_ONLY
mdefine_line|#define SCTP_CHUNK_MATCH_ONLY  0x04  /* Match if these are the only chunk types present */
DECL|member|chunk_match_type
id|u_int32_t
id|chunk_match_type
suffix:semicolon
DECL|member|flag_info
r_struct
id|ipt_sctp_flag_info
id|flag_info
(braket
id|IPT_NUM_SCTP_FLAGS
)braket
suffix:semicolon
DECL|member|flag_count
r_int
id|flag_count
suffix:semicolon
DECL|member|flags
id|u_int32_t
id|flags
suffix:semicolon
DECL|member|invflags
id|u_int32_t
id|invflags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|bytes
mdefine_line|#define bytes(type) (sizeof(type) * 8)
DECL|macro|SCTP_CHUNKMAP_SET
mdefine_line|#define SCTP_CHUNKMAP_SET(chunkmap, type) &t;&t;&bslash;&n;&t;do { &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;chunkmap[type / bytes(u_int32_t)] |= &t;&bslash;&n;&t;&t;&t;1 &lt;&lt; (type % bytes(u_int32_t));&t;&bslash;&n;&t;} while (0)
DECL|macro|SCTP_CHUNKMAP_CLEAR
mdefine_line|#define SCTP_CHUNKMAP_CLEAR(chunkmap, type)&t;&t; &t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;chunkmap[type / bytes(u_int32_t)] &amp;= &t;&t;&bslash;&n;&t;&t;&t;~(1 &lt;&lt; (type % bytes(u_int32_t)));&t;&bslash;&n;&t;} while (0)
DECL|macro|SCTP_CHUNKMAP_IS_SET
mdefine_line|#define SCTP_CHUNKMAP_IS_SET(chunkmap, type) &t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(chunkmap[type / bytes (u_int32_t)] &amp; &t;&t;&t;&bslash;&n;&t;&t;(1 &lt;&lt; (type % bytes (u_int32_t)))) ? 1: 0;&t;&bslash;&n;})
DECL|macro|SCTP_CHUNKMAP_RESET
mdefine_line|#define SCTP_CHUNKMAP_RESET(chunkmap) &t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int i; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;for (i = 0; i &lt; ELEMCOUNT(chunkmap); i++)&t;&bslash;&n;&t;&t;&t;chunkmap[i] = 0;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|SCTP_CHUNKMAP_SET_ALL
mdefine_line|#define SCTP_CHUNKMAP_SET_ALL(chunkmap) &t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int i; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;for (i = 0; i &lt; ELEMCOUNT(chunkmap); i++) &t;&bslash;&n;&t;&t;&t;chunkmap[i] = ~0;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|SCTP_CHUNKMAP_COPY
mdefine_line|#define SCTP_CHUNKMAP_COPY(destmap, srcmap) &t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;int i; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;for (i = 0; i &lt; ELEMCOUNT(chunkmap); i++) &t;&bslash;&n;&t;&t;&t;destmap[i] = srcmap[i];&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|SCTP_CHUNKMAP_IS_CLEAR
mdefine_line|#define SCTP_CHUNKMAP_IS_CLEAR(chunkmap) &t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int i; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;int flag = 1;&t;&t;&t;&t;&t;&bslash;&n;&t;for (i = 0; i &lt; ELEMCOUNT(chunkmap); i++) {&t;&bslash;&n;&t;&t;if (chunkmap[i]) {&t;&t;&t;&bslash;&n;&t;&t;&t;flag = 0;&t;&t;&t;&bslash;&n;&t;&t;&t;break;&t;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;        flag;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|SCTP_CHUNKMAP_IS_ALL_SET
mdefine_line|#define SCTP_CHUNKMAP_IS_ALL_SET(chunkmap) &t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int i; &t;&t;&t;&t;&t;&t;&bslash;&n;&t;int flag = 1;&t;&t;&t;&t;&t;&bslash;&n;&t;for (i = 0; i &lt; ELEMCOUNT(chunkmap); i++) {&t;&bslash;&n;&t;&t;if (chunkmap[i] != ~0) {&t;&t;&bslash;&n;&t;&t;&t;flag = 0;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;break;&t;&t;&t;&bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&bslash;&n;        flag;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* _IPT_SCTP_H_ */
eof
