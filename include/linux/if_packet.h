macro_line|#ifndef __LINUX_IF_PACKET_H
DECL|macro|__LINUX_IF_PACKET_H
mdefine_line|#define __LINUX_IF_PACKET_H
DECL|struct|sockaddr_pkt
r_struct
id|sockaddr_pkt
(brace
DECL|member|spkt_family
r_int
r_int
id|spkt_family
suffix:semicolon
DECL|member|spkt_device
r_int
r_char
id|spkt_device
(braket
l_int|14
)braket
suffix:semicolon
DECL|member|spkt_protocol
r_int
r_int
id|spkt_protocol
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sockaddr_ll
r_struct
id|sockaddr_ll
(brace
DECL|member|sll_family
r_int
r_int
id|sll_family
suffix:semicolon
DECL|member|sll_protocol
r_int
r_int
id|sll_protocol
suffix:semicolon
DECL|member|sll_ifindex
r_int
id|sll_ifindex
suffix:semicolon
DECL|member|sll_hatype
r_int
r_int
id|sll_hatype
suffix:semicolon
DECL|member|sll_pkttype
r_int
r_char
id|sll_pkttype
suffix:semicolon
DECL|member|sll_halen
r_int
r_char
id|sll_halen
suffix:semicolon
DECL|member|sll_addr
r_int
r_char
id|sll_addr
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Packet types */
DECL|macro|PACKET_HOST
mdefine_line|#define PACKET_HOST&t;&t;0&t;&t;/* To us&t;&t;*/
DECL|macro|PACKET_BROADCAST
mdefine_line|#define PACKET_BROADCAST&t;1&t;&t;/* To all&t;&t;*/
DECL|macro|PACKET_MULTICAST
mdefine_line|#define PACKET_MULTICAST&t;2&t;&t;/* To group&t;&t;*/
DECL|macro|PACKET_OTHERHOST
mdefine_line|#define PACKET_OTHERHOST&t;3&t;&t;/* To someone else &t;*/
DECL|macro|PACKET_OUTGOING
mdefine_line|#define PACKET_OUTGOING&t;&t;4&t;&t;/* Outgoing of any type */
multiline_comment|/* These ones are invisible by user level */
DECL|macro|PACKET_LOOPBACK
mdefine_line|#define PACKET_LOOPBACK&t;&t;5&t;&t;/* MC/BRD frame looped back */
DECL|macro|PACKET_FASTROUTE
mdefine_line|#define PACKET_FASTROUTE&t;6&t;&t;/* Fastrouted frame&t;*/
multiline_comment|/* Packet socket options */
DECL|macro|PACKET_ADD_MEMBERSHIP
mdefine_line|#define PACKET_ADD_MEMBERSHIP&t;&t;1
DECL|macro|PACKET_DROP_MEMBERSHIP
mdefine_line|#define PACKET_DROP_MEMBERSHIP&t;&t;2
DECL|macro|PACKET_RECV_OUTPUT
mdefine_line|#define PACKET_RECV_OUTPUT&t;&t;3
multiline_comment|/* Value 4 is still used by obsolete turbo-packet. */
DECL|macro|PACKET_RX_RING
mdefine_line|#define PACKET_RX_RING&t;&t;&t;5
DECL|macro|PACKET_STATISTICS
mdefine_line|#define PACKET_STATISTICS&t;&t;6
DECL|macro|PACKET_COPY_THRESH
mdefine_line|#define PACKET_COPY_THRESH&t;&t;7
DECL|struct|tpacket_stats
r_struct
id|tpacket_stats
(brace
DECL|member|tp_packets
r_int
r_int
id|tp_packets
suffix:semicolon
DECL|member|tp_drops
r_int
r_int
id|tp_drops
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tpacket_hdr
r_struct
id|tpacket_hdr
(brace
DECL|member|tp_status
r_int
r_int
id|tp_status
suffix:semicolon
DECL|macro|TP_STATUS_KERNEL
mdefine_line|#define TP_STATUS_KERNEL&t;0
DECL|macro|TP_STATUS_USER
mdefine_line|#define TP_STATUS_USER&t;&t;1
DECL|macro|TP_STATUS_COPY
mdefine_line|#define TP_STATUS_COPY&t;&t;2
DECL|macro|TP_STATUS_LOSING
mdefine_line|#define TP_STATUS_LOSING&t;4
DECL|macro|TP_STATUS_CSUMNOTREADY
mdefine_line|#define TP_STATUS_CSUMNOTREADY&t;8
DECL|member|tp_len
r_int
r_int
id|tp_len
suffix:semicolon
DECL|member|tp_snaplen
r_int
r_int
id|tp_snaplen
suffix:semicolon
DECL|member|tp_mac
r_int
r_int
id|tp_mac
suffix:semicolon
DECL|member|tp_net
r_int
r_int
id|tp_net
suffix:semicolon
DECL|member|tp_sec
r_int
r_int
id|tp_sec
suffix:semicolon
DECL|member|tp_usec
r_int
r_int
id|tp_usec
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|TPACKET_ALIGNMENT
mdefine_line|#define TPACKET_ALIGNMENT&t;16
DECL|macro|TPACKET_ALIGN
mdefine_line|#define TPACKET_ALIGN(x)&t;(((x)+TPACKET_ALIGNMENT-1)&amp;~(TPACKET_ALIGNMENT-1))
DECL|macro|TPACKET_HDRLEN
mdefine_line|#define TPACKET_HDRLEN&t;&t;(TPACKET_ALIGN(sizeof(struct tpacket_hdr)) + sizeof(struct sockaddr_ll))
multiline_comment|/*&n;   Frame structure:&n;&n;   - Start. Frame must be aligned to TPACKET_ALIGNMENT=16&n;   - struct tpacket_hdr&n;   - pad to TPACKET_ALIGNMENT=16&n;   - struct sockaddr_ll&n;   - Gap, chosen so that packet data (Start+tp_net) alignes to TPACKET_ALIGNMENT=16&n;   - Start+tp_mac: [ Optional MAC header ]&n;   - Start+tp_net: Packet data, aligned to TPACKET_ALIGNMENT=16.&n;   - Pad to align to TPACKET_ALIGNMENT=16&n; */
DECL|struct|tpacket_req
r_struct
id|tpacket_req
(brace
DECL|member|tp_block_size
r_int
r_int
id|tp_block_size
suffix:semicolon
multiline_comment|/* Minimal size of contiguous block */
DECL|member|tp_block_nr
r_int
r_int
id|tp_block_nr
suffix:semicolon
multiline_comment|/* Number of blocks */
DECL|member|tp_frame_size
r_int
r_int
id|tp_frame_size
suffix:semicolon
multiline_comment|/* Size of frame */
DECL|member|tp_frame_nr
r_int
r_int
id|tp_frame_nr
suffix:semicolon
multiline_comment|/* Total number of frames */
)brace
suffix:semicolon
DECL|struct|packet_mreq
r_struct
id|packet_mreq
(brace
DECL|member|mr_ifindex
r_int
id|mr_ifindex
suffix:semicolon
DECL|member|mr_type
r_int
r_int
id|mr_type
suffix:semicolon
DECL|member|mr_alen
r_int
r_int
id|mr_alen
suffix:semicolon
DECL|member|mr_address
r_int
r_char
id|mr_address
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PACKET_MR_MULTICAST
mdefine_line|#define PACKET_MR_MULTICAST&t;0
DECL|macro|PACKET_MR_PROMISC
mdefine_line|#define PACKET_MR_PROMISC&t;1
DECL|macro|PACKET_MR_ALLMULTI
mdefine_line|#define PACKET_MR_ALLMULTI&t;2
macro_line|#endif
eof
