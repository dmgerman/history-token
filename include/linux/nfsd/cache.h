multiline_comment|/*&n; * include/linux/nfsd/cache.h&n; *&n; * Request reply cache. This was heavily inspired by the&n; * implementation in 4.3BSD/4.4BSD.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef NFSCACHE_H
DECL|macro|NFSCACHE_H
mdefine_line|#define NFSCACHE_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/sched.h&gt;
multiline_comment|/*&n; * Representation of a reply cache entry. The first two members *must*&n; * be hash_next and hash_prev.&n; */
DECL|struct|svc_cacherep
r_struct
id|svc_cacherep
(brace
DECL|member|c_hash_next
r_struct
id|svc_cacherep
op_star
id|c_hash_next
suffix:semicolon
DECL|member|c_hash_prev
r_struct
id|svc_cacherep
op_star
id|c_hash_prev
suffix:semicolon
DECL|member|c_lru_next
r_struct
id|svc_cacherep
op_star
id|c_lru_next
suffix:semicolon
DECL|member|c_lru_prev
r_struct
id|svc_cacherep
op_star
id|c_lru_prev
suffix:semicolon
DECL|member|c_state
r_int
r_char
id|c_state
comma
multiline_comment|/* unused, inprog, done */
DECL|member|c_type
id|c_type
comma
multiline_comment|/* status, buffer */
DECL|member|c_secure
id|c_secure
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* req came from port &lt; 1024 */
DECL|member|c_addr
r_struct
id|sockaddr_in
id|c_addr
suffix:semicolon
DECL|member|c_xid
id|u32
id|c_xid
suffix:semicolon
DECL|member|c_prot
id|u32
id|c_prot
suffix:semicolon
DECL|member|c_proc
id|u32
id|c_proc
suffix:semicolon
DECL|member|c_vers
id|u32
id|c_vers
suffix:semicolon
DECL|member|c_timestamp
r_int
r_int
id|c_timestamp
suffix:semicolon
r_union
(brace
DECL|member|u_buffer
r_struct
id|svc_buf
id|u_buffer
suffix:semicolon
DECL|member|u_status
id|u32
id|u_status
suffix:semicolon
DECL|member|c_u
)brace
id|c_u
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|c_replbuf
mdefine_line|#define c_replbuf&t;&t;c_u.u_buffer
DECL|macro|c_replstat
mdefine_line|#define c_replstat&t;&t;c_u.u_status
multiline_comment|/* cache entry states */
r_enum
(brace
DECL|enumerator|RC_UNUSED
id|RC_UNUSED
comma
DECL|enumerator|RC_INPROG
id|RC_INPROG
comma
DECL|enumerator|RC_DONE
id|RC_DONE
)brace
suffix:semicolon
multiline_comment|/* return values */
r_enum
(brace
DECL|enumerator|RC_DROPIT
id|RC_DROPIT
comma
DECL|enumerator|RC_REPLY
id|RC_REPLY
comma
DECL|enumerator|RC_DOIT
id|RC_DOIT
comma
DECL|enumerator|RC_INTR
id|RC_INTR
)brace
suffix:semicolon
multiline_comment|/*&n; * Cache types.&n; * We may want to add more types one day, e.g. for diropres and&n; * attrstat replies. Using cache entries with fixed length instead&n; * of buffer pointers may be more efficient.&n; */
r_enum
(brace
DECL|enumerator|RC_NOCACHE
id|RC_NOCACHE
comma
DECL|enumerator|RC_REPLSTAT
id|RC_REPLSTAT
comma
DECL|enumerator|RC_REPLBUFF
id|RC_REPLBUFF
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * If requests are retransmitted within this interval, they&squot;re dropped.&n; */
DECL|macro|RC_DELAY
mdefine_line|#define RC_DELAY&t;&t;(HZ/5)
r_void
id|nfsd_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_cache_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|nfsd_cache_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|nfsd_cache_update
c_func
(paren
r_struct
id|svc_rqst
op_star
comma
r_int
comma
id|u32
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* NFSCACHE_H */
eof
