multiline_comment|/* Header file for IP tables userspace logging, Version 1.8&n; *&n; * (C) 2000-2002 by Harald Welte &lt;laforge@gnumonks.org&gt;&n; * &n; * Distributed under the terms of GNU GPL */
macro_line|#ifndef _IPT_ULOG_H
DECL|macro|_IPT_ULOG_H
mdefine_line|#define _IPT_ULOG_H
macro_line|#ifndef NETLINK_NFLOG
DECL|macro|NETLINK_NFLOG
mdefine_line|#define NETLINK_NFLOG &t;5
macro_line|#endif
DECL|macro|ULOG_MAC_LEN
mdefine_line|#define ULOG_MAC_LEN&t;80
DECL|macro|ULOG_PREFIX_LEN
mdefine_line|#define ULOG_PREFIX_LEN&t;32
DECL|macro|ULOG_MAX_QLEN
mdefine_line|#define ULOG_MAX_QLEN&t;50
multiline_comment|/* Why 50? Well... there is a limit imposed by the slab cache 131000&n; * bytes. So the multipart netlink-message has to be &lt; 131000 bytes.&n; * Assuming a standard ethernet-mtu of 1500, we could define this up&n; * to 80... but even 50 seems to be big enough. */
multiline_comment|/* private data structure for each rule with a ULOG target */
DECL|struct|ipt_ulog_info
r_struct
id|ipt_ulog_info
(brace
DECL|member|nl_group
r_int
r_int
id|nl_group
suffix:semicolon
DECL|member|copy_range
r_int
id|copy_range
suffix:semicolon
DECL|member|qthreshold
r_int
id|qthreshold
suffix:semicolon
DECL|member|prefix
r_char
id|prefix
(braket
id|ULOG_PREFIX_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Format of the ULOG packets passed through netlink */
DECL|struct|ulog_packet_msg
r_typedef
r_struct
id|ulog_packet_msg
(brace
DECL|member|mark
r_int
r_int
id|mark
suffix:semicolon
DECL|member|timestamp_sec
r_int
id|timestamp_sec
suffix:semicolon
DECL|member|timestamp_usec
r_int
id|timestamp_usec
suffix:semicolon
DECL|member|hook
r_int
r_int
id|hook
suffix:semicolon
DECL|member|indev_name
r_char
id|indev_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|outdev_name
r_char
id|outdev_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|data_len
r_int
id|data_len
suffix:semicolon
DECL|member|prefix
r_char
id|prefix
(braket
id|ULOG_PREFIX_LEN
)braket
suffix:semicolon
DECL|member|mac_len
r_int
r_char
id|mac_len
suffix:semicolon
DECL|member|mac
r_int
r_char
id|mac
(braket
id|ULOG_MAC_LEN
)braket
suffix:semicolon
DECL|member|payload
r_int
r_char
id|payload
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|ulog_packet_msg_t
)brace
id|ulog_packet_msg_t
suffix:semicolon
macro_line|#endif /*_IPT_ULOG_H*/
eof
