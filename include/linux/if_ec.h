multiline_comment|/* Definitions for Econet sockets. */
macro_line|#ifndef __LINUX_IF_EC
DECL|macro|__LINUX_IF_EC
mdefine_line|#define __LINUX_IF_EC
multiline_comment|/* User visible stuff. Glibc provides its own but libc5 folk will use these */
DECL|struct|ec_addr
r_struct
id|ec_addr
(brace
DECL|member|station
r_int
r_char
id|station
suffix:semicolon
multiline_comment|/* Station number.  */
DECL|member|net
r_int
r_char
id|net
suffix:semicolon
multiline_comment|/* Network number.  */
)brace
suffix:semicolon
DECL|struct|sockaddr_ec
r_struct
id|sockaddr_ec
(brace
DECL|member|sec_family
r_int
r_int
id|sec_family
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
multiline_comment|/* Port number.  */
DECL|member|cb
r_int
r_char
id|cb
suffix:semicolon
multiline_comment|/* Control/flag byte.  */
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
multiline_comment|/* Type of message.  */
DECL|member|addr
r_struct
id|ec_addr
id|addr
suffix:semicolon
DECL|member|cookie
r_int
r_int
id|cookie
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ECTYPE_PACKET_RECEIVED
mdefine_line|#define ECTYPE_PACKET_RECEIVED&t;&t;0&t;/* Packet received */
DECL|macro|ECTYPE_TRANSMIT_STATUS
mdefine_line|#define ECTYPE_TRANSMIT_STATUS&t;&t;0x10&t;/* Transmit completed, &n;&t;&t;&t;&t;&t;&t;   low nibble holds status */
DECL|macro|ECTYPE_TRANSMIT_OK
mdefine_line|#define ECTYPE_TRANSMIT_OK&t;&t;1
DECL|macro|ECTYPE_TRANSMIT_NOT_LISTENING
mdefine_line|#define ECTYPE_TRANSMIT_NOT_LISTENING&t;2
DECL|macro|ECTYPE_TRANSMIT_NET_ERROR
mdefine_line|#define ECTYPE_TRANSMIT_NET_ERROR&t;3
DECL|macro|ECTYPE_TRANSMIT_NO_CLOCK
mdefine_line|#define ECTYPE_TRANSMIT_NO_CLOCK&t;4
DECL|macro|ECTYPE_TRANSMIT_LINE_JAMMED
mdefine_line|#define ECTYPE_TRANSMIT_LINE_JAMMED&t;5
DECL|macro|ECTYPE_TRANSMIT_NOT_PRESENT
mdefine_line|#define ECTYPE_TRANSMIT_NOT_PRESENT&t;6
macro_line|#ifdef __KERNEL__
DECL|macro|EC_HLEN
mdefine_line|#define EC_HLEN&t;&t;&t;&t;6
multiline_comment|/* This is what an Econet frame looks like on the wire. */
DECL|struct|ec_framehdr
r_struct
id|ec_framehdr
(brace
DECL|member|dst_stn
r_int
r_char
id|dst_stn
suffix:semicolon
DECL|member|dst_net
r_int
r_char
id|dst_net
suffix:semicolon
DECL|member|src_stn
r_int
r_char
id|src_stn
suffix:semicolon
DECL|member|src_net
r_int
r_char
id|src_net
suffix:semicolon
DECL|member|cb
r_int
r_char
id|cb
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|econet_opt
r_struct
id|econet_opt
(brace
DECL|member|cb
r_int
r_char
id|cb
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
DECL|member|station
r_int
r_char
id|station
suffix:semicolon
DECL|member|net
r_int
r_char
id|net
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ec_sk
mdefine_line|#define ec_sk(__sk) ((struct econet_opt *)(__sk)-&gt;protinfo)
DECL|struct|ec_device
r_struct
id|ec_device
(brace
DECL|member|station
DECL|member|net
r_int
r_char
id|station
comma
id|net
suffix:semicolon
multiline_comment|/* Econet protocol address */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
