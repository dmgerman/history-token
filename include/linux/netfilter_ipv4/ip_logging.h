multiline_comment|/* IPv4 macros for the internal logging interface. */
macro_line|#ifndef __IP_LOGGING_H
DECL|macro|__IP_LOGGING_H
mdefine_line|#define __IP_LOGGING_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/netfilter_logging.h&gt;
DECL|macro|nf_log_ip_packet
mdefine_line|#define nf_log_ip_packet(pskb,hooknum,in,out,fmt,args...) &bslash;&n;&t;nf_log_packet(AF_INET,pskb,hooknum,in,out,fmt,##args)
DECL|macro|nf_log_ip
mdefine_line|#define nf_log_ip(pfh,len,fmt,args...) &bslash;&n;&t;nf_log(AF_INET,pfh,len,fmt,##args)
DECL|macro|nf_ip_log_register
mdefine_line|#define nf_ip_log_register(logging) nf_log_register(AF_INET,logging)
DECL|macro|nf_ip_log_unregister
mdefine_line|#define nf_ip_log_unregister(logging) nf_log_unregister(AF_INET,logging)
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*__IP_LOGGING_H*/
eof
