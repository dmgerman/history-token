macro_line|#ifndef _IP_CONNTRACK_AMANDA_H
DECL|macro|_IP_CONNTRACK_AMANDA_H
mdefine_line|#define _IP_CONNTRACK_AMANDA_H
multiline_comment|/* AMANDA tracking. */
DECL|struct|ip_ct_amanda_expect
r_struct
id|ip_ct_amanda_expect
(brace
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
multiline_comment|/* port number of this expectation */
DECL|member|offset
id|u_int16_t
id|offset
suffix:semicolon
multiline_comment|/* offset of port in ctrl packet */
DECL|member|len
id|u_int16_t
id|len
suffix:semicolon
multiline_comment|/* length of the port number string */
)brace
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_AMANDA_H */
eof
