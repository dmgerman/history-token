multiline_comment|/* atmarp.h - ATM ARP protocol and kernel-demon interface definitions */
multiline_comment|/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef _LINUX_ATMARP_H
DECL|macro|_LINUX_ATMARP_H
mdefine_line|#define _LINUX_ATMARP_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/atmapi.h&gt;
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|ATMARP_RETRY_DELAY
mdefine_line|#define ATMARP_RETRY_DELAY 30&t;&t;/* request next resolution or forget&n;&t;&t;&t;&t;&t;   NAK after 30 sec - should go into&n;&t;&t;&t;&t;&t;   atmclip.h */
DECL|macro|ATMARP_MAX_UNRES_PACKETS
mdefine_line|#define ATMARP_MAX_UNRES_PACKETS 5&t;/* queue that many packets while&n;&t;&t;&t;&t;&t;   waiting for the resolver */
DECL|macro|ATMARPD_CTRL
mdefine_line|#define ATMARPD_CTRL&t;_IO(&squot;a&squot;,ATMIOC_CLIP+1)&t;/* become atmarpd ctrl sock */
DECL|macro|ATMARP_MKIP
mdefine_line|#define ATMARP_MKIP&t;_IO(&squot;a&squot;,ATMIOC_CLIP+2)&t;/* attach socket to IP */
DECL|macro|ATMARP_SETENTRY
mdefine_line|#define ATMARP_SETENTRY&t;_IO(&squot;a&squot;,ATMIOC_CLIP+3)&t;/* fill or hide ARP entry */
DECL|macro|ATMARP_ENCAP
mdefine_line|#define ATMARP_ENCAP&t;_IO(&squot;a&squot;,ATMIOC_CLIP+5)&t;/* change encapsulation */
DECL|enum|atmarp_ctrl_type
r_enum
id|atmarp_ctrl_type
(brace
DECL|enumerator|act_invalid
id|act_invalid
comma
multiline_comment|/* catch uninitialized structures */
DECL|enumerator|act_need
id|act_need
comma
multiline_comment|/* need address resolution */
DECL|enumerator|act_up
id|act_up
comma
multiline_comment|/* interface is coming up */
DECL|enumerator|act_down
id|act_down
comma
multiline_comment|/* interface is going down */
DECL|enumerator|act_change
id|act_change
multiline_comment|/* interface configuration has changed */
)brace
suffix:semicolon
DECL|struct|atmarp_ctrl
r_struct
id|atmarp_ctrl
(brace
DECL|member|type
r_enum
id|atmarp_ctrl_type
id|type
suffix:semicolon
multiline_comment|/* message type */
DECL|member|itf_num
r_int
id|itf_num
suffix:semicolon
multiline_comment|/* interface number (if present) */
DECL|member|ip
r_uint32
id|ip
suffix:semicolon
multiline_comment|/* IP address (act_need only) */
)brace
suffix:semicolon
macro_line|#endif
eof
