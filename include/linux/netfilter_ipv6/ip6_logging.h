multiline_comment|/* IPv6 macros for the nternal logging interface. */
macro_line|#ifndef __IP6_LOGGING_H
DECL|macro|__IP6_LOGGING_H
mdefine_line|#define __IP6_LOGGING_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/netfilter_logging.h&gt;
DECL|macro|nf_log_ip6_packet
mdefine_line|#define nf_log_ip6_packet(pskb,hooknum,in,out,fmt,args...) &bslash;&n;&t;nf_log_packet(AF_INET6,pskb,hooknum,in,out,fmt,##args)
DECL|macro|nf_log_ip6
mdefine_line|#define nf_log_ip6(pfh,len,fmt,args...) &bslash;&n;&t;nf_log(AF_INET6,pfh,len,fmt,##args)
DECL|macro|nf_ip6_log_register
mdefine_line|#define nf_ip6_log_register(logging) nf_log_register(AF_INET6,logging)
DECL|macro|nf_ip6_log_unregister
mdefine_line|#define nf_ip6_log_unregister(logging) nf_log_unregister(AF_INET6,logging)
macro_line|#endif /*__KERNEL__*/
macro_line|#endif /*__IP6_LOGGING_H*/
eof
