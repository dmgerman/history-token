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
DECL|macro|FTP_PORT
mdefine_line|#define FTP_PORT&t;21
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
multiline_comment|/* This structure is per expected connection */
DECL|struct|ip_ct_ftp_expect
r_struct
id|ip_ct_ftp_expect
(brace
multiline_comment|/* We record seq number and length of ftp ip/port text here: all in&n;&t; * host order. */
multiline_comment|/* sequence number of IP address in packet is in ip_conntrack_expect */
DECL|member|len
id|u_int32_t
id|len
suffix:semicolon
multiline_comment|/* length of IP address */
DECL|member|ftptype
r_enum
id|ip_ct_ftp_type
id|ftptype
suffix:semicolon
multiline_comment|/* PORT or PASV ? */
DECL|member|port
id|u_int16_t
id|port
suffix:semicolon
multiline_comment|/* TCP port that was to be used */
)brace
suffix:semicolon
multiline_comment|/* This structure exists only once per master */
DECL|struct|ip_ct_ftp_master
r_struct
id|ip_ct_ftp_master
(brace
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
