macro_line|#ifndef _IP_NAT_FTP_H
DECL|macro|_IP_NAT_FTP_H
mdefine_line|#define _IP_NAT_FTP_H
multiline_comment|/* FTP extension for TCP NAT alteration. */
macro_line|#ifndef __KERNEL__
macro_line|#error Only in kernel.
macro_line|#endif
multiline_comment|/* Protects ftp part of conntracks */
DECL|variable|ip_ftp_lock
id|DECLARE_LOCK_EXTERN
c_func
(paren
id|ip_ftp_lock
)paren
suffix:semicolon
multiline_comment|/* We keep track of where the last SYN correction was, and the SYN&n;   offsets before and after that correction.  Two of these (indexed by&n;   direction). */
DECL|struct|ip_nat_ftp_info
r_struct
id|ip_nat_ftp_info
(brace
DECL|member|syn_correction_pos
id|u_int32_t
id|syn_correction_pos
suffix:semicolon
DECL|member|syn_offset_before
DECL|member|syn_offset_after
r_int32
id|syn_offset_before
comma
id|syn_offset_after
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IP_NAT_FTP_H */
eof
