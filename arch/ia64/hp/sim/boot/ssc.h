multiline_comment|/*&n; * Copyright (C) 1998-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&t;Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; */
macro_line|#ifndef ssc_h
DECL|macro|ssc_h
mdefine_line|#define ssc_h
multiline_comment|/* Simulator system calls: */
DECL|macro|SSC_CONSOLE_INIT
mdefine_line|#define SSC_CONSOLE_INIT&t;&t;20
DECL|macro|SSC_GETCHAR
mdefine_line|#define SSC_GETCHAR&t;&t;&t;21
DECL|macro|SSC_PUTCHAR
mdefine_line|#define SSC_PUTCHAR&t;&t;&t;31
DECL|macro|SSC_OPEN
mdefine_line|#define SSC_OPEN&t;&t;&t;50
DECL|macro|SSC_CLOSE
mdefine_line|#define SSC_CLOSE&t;&t;&t;51
DECL|macro|SSC_READ
mdefine_line|#define SSC_READ&t;&t;&t;52
DECL|macro|SSC_WRITE
mdefine_line|#define SSC_WRITE&t;&t;&t;53
DECL|macro|SSC_GET_COMPLETION
mdefine_line|#define SSC_GET_COMPLETION&t;&t;54
DECL|macro|SSC_WAIT_COMPLETION
mdefine_line|#define SSC_WAIT_COMPLETION&t;&t;55
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
DECL|macro|SSC_GET_ARGS
mdefine_line|#define SSC_GET_ARGS&t;&t;&t;75
multiline_comment|/*&n; * Simulator system call.&n; */
r_extern
r_int
id|ssc
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
macro_line|#endif /* ssc_h */
eof
