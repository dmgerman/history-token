macro_line|#ifndef&t;__BPQETHER_H
DECL|macro|__BPQETHER_H
mdefine_line|#define&t;__BPQETHER_H
multiline_comment|/*&n; * &t;Defines for the BPQETHER pseudo device driver&n; */
macro_line|#ifndef __LINUX_IF_ETHER_H
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#endif
DECL|macro|SIOCSBPQETHOPT
mdefine_line|#define SIOCSBPQETHOPT&t;&t;(SIOCDEVPRIVATE+0)&t;/* reserved */
DECL|macro|SIOCSBPQETHADDR
mdefine_line|#define SIOCSBPQETHADDR&t;&t;(SIOCDEVPRIVATE+1)
DECL|struct|bpq_ethaddr
r_struct
id|bpq_ethaddr
(brace
DECL|member|destination
r_int
r_char
id|destination
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|accept
r_int
r_char
id|accept
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * For SIOCSBPQETHOPT - this is compatible with PI2/PacketTwin card drivers,&n; * currently not implemented, though. If someone wants to hook a radio&n; * to his Ethernet card he may find this useful. ;-)&n; */
DECL|macro|SIOCGBPQETHPARAM
mdefine_line|#define SIOCGBPQETHPARAM&t;0x5000  /* get Level 1 parameters */
DECL|macro|SIOCSBPQETHPARAM
mdefine_line|#define SIOCSBPQETHPARAM&t;0x5001  /* set */
DECL|struct|bpq_req
r_struct
id|bpq_req
(brace
DECL|member|cmd
r_int
id|cmd
suffix:semicolon
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* unused */
DECL|member|clockmode
r_int
id|clockmode
suffix:semicolon
multiline_comment|/* unused */
DECL|member|txdelay
r_int
id|txdelay
suffix:semicolon
DECL|member|persist
r_int
r_char
id|persist
suffix:semicolon
multiline_comment|/* unused */
DECL|member|slotime
r_int
id|slotime
suffix:semicolon
multiline_comment|/* unused */
DECL|member|squeldelay
r_int
id|squeldelay
suffix:semicolon
DECL|member|dmachan
r_int
id|dmachan
suffix:semicolon
multiline_comment|/* unused */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* unused */
)brace
suffix:semicolon
macro_line|#endif
eof
