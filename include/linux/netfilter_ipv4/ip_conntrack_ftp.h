macro_line|#ifndef _IP_CONNTRACK_FTP_H
DECL|macro|_IP_CONNTRACK_FTP_H
mdefine_line|#define _IP_CONNTRACK_FTP_H
multiline_comment|/* FTP tracking. */
macro_line|#ifndef __KERNEL__
macro_line|#error Only in kernel.
macro_line|#endif
macro_line|#include &lt;linux/netfilter_ipv4/lockhelp.h&gt;
multiline_comment|/* Protects ftp part of conntracks */
DECL|variable|ip_ftp_lock
id|DECLARE_LOCK_EXTERN
c_func
(paren
id|ip_ftp_lock
)paren
suffix:semicolon
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
multiline_comment|/* We record seq number and length of ftp ip/port text here: all in&n;   host order. */
DECL|struct|ip_ct_ftp
r_struct
id|ip_ct_ftp
(brace
multiline_comment|/* This tells NAT that this is an ftp connection */
DECL|member|is_ftp
r_int
id|is_ftp
suffix:semicolon
DECL|member|seq
id|u_int32_t
id|seq
suffix:semicolon
multiline_comment|/* 0 means not found yet */
DECL|member|len
id|u_int32_t
id|len
suffix:semicolon
DECL|member|ftptype
r_enum
id|ip_ct_ftp_type
id|ftptype
suffix:semicolon
multiline_comment|/* Port that was to be used */
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
multiline_comment|/* Next valid seq position for cmd matching after newline */
DECL|member|seq_aft_nl
id|u_int32_t
id|seq_aft_nl
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
multiline_comment|/* 0 means seq_match_aft_nl not set */
DECL|member|seq_aft_nl_set
r_int
id|seq_aft_nl_set
(braket
id|IP_CT_DIR_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IP_CONNTRACK_FTP_H */
eof
