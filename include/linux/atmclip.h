multiline_comment|/* atmclip.h - Classical IP over ATM */
multiline_comment|/* Written 1995-1998 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef LINUX_ATMCLIP_H
DECL|macro|LINUX_ATMCLIP_H
mdefine_line|#define LINUX_ATMCLIP_H
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|RFC1483LLC_LEN
mdefine_line|#define RFC1483LLC_LEN&t;8&t;&t;/* LLC+OUI+PID = 8 */
DECL|macro|RFC1626_MTU
mdefine_line|#define RFC1626_MTU&t;9180&t;&t;/* RFC1626 default MTU */
DECL|macro|CLIP_DEFAULT_IDLETIMER
mdefine_line|#define CLIP_DEFAULT_IDLETIMER 1200&t;/* 20 minutes, see RFC1755 */
DECL|macro|CLIP_CHECK_INTERVAL
mdefine_line|#define CLIP_CHECK_INTERVAL&t; 10&t;/* check every ten seconds */
DECL|macro|SIOCMKCLIP
mdefine_line|#define&t;SIOCMKCLIP&t;_IO(&squot;a&squot;,ATMIOC_CLIP)&t;/* create IP interface */
macro_line|#ifdef __KERNEL__
r_extern
r_const
r_int
r_char
id|llc_oui
(braket
l_int|6
)braket
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
