multiline_comment|/*&n; *  $Id: ipconfig.h,v 1.4 2001/04/30 04:51:46 davem Exp $&n; *&n; *  Copyright (C) 1997 Martin Mares&n; *&n; *  Automatic IP Layer Configuration&n; */
multiline_comment|/* The following are initdata: */
r_extern
r_int
id|ic_proto_enabled
suffix:semicolon
multiline_comment|/* Protocols enabled (see IC_xxx) */
r_extern
r_int
id|ic_set_manually
suffix:semicolon
multiline_comment|/* IPconfig parameters set manually */
r_extern
id|u32
id|ic_myaddr
suffix:semicolon
multiline_comment|/* My IP address */
r_extern
id|u32
id|ic_gateway
suffix:semicolon
multiline_comment|/* Gateway IP address */
r_extern
id|u32
id|ic_servaddr
suffix:semicolon
multiline_comment|/* Boot server IP address */
r_extern
id|u32
id|root_server_addr
suffix:semicolon
multiline_comment|/* Address of NFS server */
r_extern
id|u8
id|root_server_path
(braket
)braket
suffix:semicolon
multiline_comment|/* Path to mount as root */
multiline_comment|/* bits in ic_proto_{enabled,used} */
DECL|macro|IC_PROTO
mdefine_line|#define IC_PROTO&t;0xFF&t;/* Protocols mask: */
DECL|macro|IC_BOOTP
mdefine_line|#define IC_BOOTP&t;0x01&t;/*   BOOTP (or DHCP, see below) */
DECL|macro|IC_RARP
mdefine_line|#define IC_RARP&t;&t;0x02&t;/*   RARP */
DECL|macro|IC_USE_DHCP
mdefine_line|#define IC_USE_DHCP    0x100&t;/* If on, use DHCP instead of BOOTP */
eof
