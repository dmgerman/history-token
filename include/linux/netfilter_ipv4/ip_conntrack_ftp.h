macro_line|#ifndef _IP_CONNTRACK_FTP_H
DECL|macro|_IP_CONNTRACK_FTP_H
mdefine_line|#define _IP_CONNTRACK_FTP_H
multiline_comment|/* FTP tracking. */
macro_line|#ifdef __KERNEL__
DECL|macro|FTP_PORT
mdefine_line|#define FTP_PORT&t;21
macro_line|#endif /* __KERNEL__ */
DECL|enum|ip_ct_ftp_type
r_enum
id|ip_ct_ftp_type
(brace
multiline_comment|/* PORT command from client */
DECL|enumerator|IP_CT_FTP_PORT
id|IP_CT_FTP_PORT
comma
multiline_comment|/* PASV response from server */
DECL|enumerator|IP_CT_FTP_PASV
id|IP_CT_FTP_PASV
comma
multiline_comment|/* EPRT command from client */
DECL|enumerator|IP_CT_FTP_EPRT
id|IP_CT_FTP_EPRT
comma
multiline_comment|/* EPSV response from server */
DECL|enumerator|IP_CT_FTP_EPSV
id|IP_CT_FTP_EPSV
comma
)brace
suffix:semicolon
DECL|macro|NUM_SEQ_TO_REMEMBER
mdefine_line|#define NUM_SEQ_TO_REMEMBER 2
multiline_comment|/* This structure exists only once per master */
DECL|struct|ip_ct_ftp_master
r_struct
id|ip_ct_ftp_master
(brace
multiline_comment|/* Valid seq positions for cmd matching after newline */
DECL|member|seq_aft_nl
id|u_int32_t
id|seq_aft_nl
(braket
id|IP_CT_DIR_MAX
)braket
(braket
id|NUM_SEQ_TO_REMEMBER
)braket
suffix:semicolon
multiline_comment|/* 0 means seq_match_aft_nl not set */
DECL|member|seq_aft_nl_num
r_int
id|seq_aft_nl_num
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|ip_conntrack_expect
suffix:semicolon
multiline_comment|/* For NAT to hook in when we find a packet which describes what other&n; * connection we should expect. */
r_extern
r_int
r_int
(paren
op_star
id|ip_nat_ftp_hook
)paren
(paren
r_struct
id|sk_buff
op_star
op_star
id|pskb
comma
r_enum
id|ip_conntrack_info
id|ctinfo
comma
r_enum
id|ip_ct_ftp_type
id|type
comma
r_int
r_int
id|matchoff
comma
r_int
r_int
id|matchlen
comma
r_struct
id|ip_conntrack_expect
op_star
id|exp
comma
id|u32
op_star
id|seq
)paren
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_FTP_H */
eof
