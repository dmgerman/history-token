multiline_comment|/*&n; * Platform dependent support for HP simulator.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; */
macro_line|#ifndef _IA64_PLATFORM_HPSIM_SSC_H
DECL|macro|_IA64_PLATFORM_HPSIM_SSC_H
mdefine_line|#define _IA64_PLATFORM_HPSIM_SSC_H
multiline_comment|/* Simulator system calls: */
DECL|macro|SSC_CONSOLE_INIT
mdefine_line|#define SSC_CONSOLE_INIT&t;&t;20
DECL|macro|SSC_GETCHAR
mdefine_line|#define SSC_GETCHAR&t;&t;&t;21
DECL|macro|SSC_PUTCHAR
mdefine_line|#define SSC_PUTCHAR&t;&t;&t;31
DECL|macro|SSC_CONNECT_INTERRUPT
mdefine_line|#define SSC_CONNECT_INTERRUPT&t;&t;58
DECL|macro|SSC_GENERATE_INTERRUPT
mdefine_line|#define SSC_GENERATE_INTERRUPT&t;&t;59
DECL|macro|SSC_SET_PERIODIC_INTERRUPT
mdefine_line|#define SSC_SET_PERIODIC_INTERRUPT&t;60
DECL|macro|SSC_GET_RTC
mdefine_line|#define SSC_GET_RTC&t;&t;&t;65
DECL|macro|SSC_EXIT
mdefine_line|#define SSC_EXIT&t;&t;&t;66
DECL|macro|SSC_LOAD_SYMBOLS
mdefine_line|#define SSC_LOAD_SYMBOLS&t;&t;69
DECL|macro|SSC_GET_TOD
mdefine_line|#define SSC_GET_TOD&t;&t;&t;74
DECL|macro|SSC_CTL_TRACE
mdefine_line|#define SSC_CTL_TRACE&t;&t;&t;76
DECL|macro|SSC_NETDEV_PROBE
mdefine_line|#define SSC_NETDEV_PROBE&t;&t;100
DECL|macro|SSC_NETDEV_SEND
mdefine_line|#define SSC_NETDEV_SEND&t;&t;&t;101
DECL|macro|SSC_NETDEV_RECV
mdefine_line|#define SSC_NETDEV_RECV&t;&t;&t;102
DECL|macro|SSC_NETDEV_ATTACH
mdefine_line|#define SSC_NETDEV_ATTACH&t;&t;103
DECL|macro|SSC_NETDEV_DETACH
mdefine_line|#define SSC_NETDEV_DETACH&t;&t;104
multiline_comment|/*&n; * Simulator system call.&n; */
r_extern
r_int
id|ia64_ssc
(paren
r_int
id|arg0
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|nr
)paren
suffix:semicolon
macro_line|#endif /* _IA64_PLATFORM_HPSIM_SSC_H */
eof
