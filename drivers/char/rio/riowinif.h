multiline_comment|/************************************************************************/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Title&t;&t;:&t;RIO Shared Memory Window Inteface&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Author&t;&t;:&t;N.P.Vassallo&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Creation&t;:&t;7th June 1999&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Version&t;&t;:&t;1.0.0&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Copyright&t;:&t;(c) Specialix International Ltd. 1999&t;*&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;Description&t;:&t;Prototypes, structures and definitions&t;*/
multiline_comment|/*&t;&t;&t;&t;describing RIO host card shared&t;memory&t;*/
multiline_comment|/*&t;&t;&t;&t;window interface structures:&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;PARMMAP&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;RUP&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;PHB&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;LPB&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;PKT&t;&t;&t;&t;*/
multiline_comment|/*&t;&t;&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************************************/
multiline_comment|/* History...&n;&n;1.0.0&t;07/06/99 NPV&t;Creation. (based on PARMMAP.H)&n;&n;*/
macro_line|#ifndef&t;_riowinif_h&t;&t;&t;&t;/* If RIOWINDIF.H not already defined */
DECL|macro|_riowinif_h
mdefine_line|#define&t;_riowinif_h    1
multiline_comment|/*****************************************************************************&n;********************************             *********************************&n;********************************   General   *********************************&n;********************************             *********************************&n;*****************************************************************************/
DECL|macro|TPNULL
mdefine_line|#define&t;TPNULL&t;&t;((_u16)(0x8000))
multiline_comment|/*****************************************************************************&n;********************************              ********************************&n;********************************   PARM_MAP   ********************************&n;********************************              ********************************&n;*****************************************************************************/
multiline_comment|/* The PARM_MAP structure defines global values relating to the Host Card / RTA&n;   and is the main structure from which all other structures are referenced. */
DECL|struct|_PARM_MAP
r_typedef
r_struct
id|_PARM_MAP
(brace
DECL|member|phb_ptr
id|_u16
id|phb_ptr
suffix:semicolon
multiline_comment|/* 0x00 Pointer to the PHB array */
DECL|member|phb_num_ptr
id|_u16
id|phb_num_ptr
suffix:semicolon
multiline_comment|/* 0x02 Ptr to Number of PHB&squot;s */
DECL|member|free_list
id|_u16
id|free_list
suffix:semicolon
multiline_comment|/* 0x04 Free List pointer */
DECL|member|free_list_end
id|_u16
id|free_list_end
suffix:semicolon
multiline_comment|/* 0x06 Free List End pointer */
DECL|member|q_free_list_ptr
id|_u16
id|q_free_list_ptr
suffix:semicolon
multiline_comment|/* 0x08 Ptr to Q_BUF variable */
DECL|member|unit_id_ptr
id|_u16
id|unit_id_ptr
suffix:semicolon
multiline_comment|/* 0x0A Unit Id */
DECL|member|link_str_ptr
id|_u16
id|link_str_ptr
suffix:semicolon
multiline_comment|/* 0x0C Link Structure Array */
DECL|member|bootloader_1
id|_u16
id|bootloader_1
suffix:semicolon
multiline_comment|/* 0x0E 1st Stage Boot Loader */
DECL|member|bootloader_2
id|_u16
id|bootloader_2
suffix:semicolon
multiline_comment|/* 0x10 2nd Stage Boot Loader */
DECL|member|port_route_map_ptr
id|_u16
id|port_route_map_ptr
suffix:semicolon
multiline_comment|/* 0x12 Port Route Map */
DECL|member|route_ptr
id|_u16
id|route_ptr
suffix:semicolon
multiline_comment|/* 0x14 Route Map */
DECL|member|map_present
id|_u16
id|map_present
suffix:semicolon
multiline_comment|/* 0x16 Route Map present */
DECL|member|pkt_num
id|_u16
id|pkt_num
suffix:semicolon
multiline_comment|/* 0x18 Total number of packets */
DECL|member|q_num
id|_u16
id|q_num
suffix:semicolon
multiline_comment|/* 0x1A Total number of Q packets */
DECL|member|buffers_per_port
id|_u16
id|buffers_per_port
suffix:semicolon
multiline_comment|/* 0x1C Number of buffers per port */
DECL|member|heap_size
id|_u16
id|heap_size
suffix:semicolon
multiline_comment|/* 0x1E Initial size of heap */
DECL|member|heap_left
id|_u16
id|heap_left
suffix:semicolon
multiline_comment|/* 0x20 Current Heap left */
DECL|member|error
id|_u16
id|error
suffix:semicolon
multiline_comment|/* 0x22 Error code */
DECL|member|tx_max
id|_u16
id|tx_max
suffix:semicolon
multiline_comment|/* 0x24 Max number of tx pkts per phb */
DECL|member|rx_max
id|_u16
id|rx_max
suffix:semicolon
multiline_comment|/* 0x26 Max number of rx pkts per phb */
DECL|member|rx_limit
id|_u16
id|rx_limit
suffix:semicolon
multiline_comment|/* 0x28 For high / low watermarks */
DECL|member|links
id|_u16
id|links
suffix:semicolon
multiline_comment|/* 0x2A Links to use */
DECL|member|timer
id|_u16
id|timer
suffix:semicolon
multiline_comment|/* 0x2C Interrupts per second */
DECL|member|rups
id|_u16
id|rups
suffix:semicolon
multiline_comment|/* 0x2E Pointer to the RUPs */
DECL|member|max_phb
id|_u16
id|max_phb
suffix:semicolon
multiline_comment|/* 0x30 Mostly for debugging */
DECL|member|living
id|_u16
id|living
suffix:semicolon
multiline_comment|/* 0x32 Just increments!! */
DECL|member|init_done
id|_u16
id|init_done
suffix:semicolon
multiline_comment|/* 0x34 Initialisation over */
DECL|member|booting_link
id|_u16
id|booting_link
suffix:semicolon
multiline_comment|/* 0x36 */
DECL|member|idle_count
id|_u16
id|idle_count
suffix:semicolon
multiline_comment|/* 0x38 Idle time counter */
DECL|member|busy_count
id|_u16
id|busy_count
suffix:semicolon
multiline_comment|/* 0x3A Busy counter */
DECL|member|idle_control
id|_u16
id|idle_control
suffix:semicolon
multiline_comment|/* 0x3C Control Idle Process */
DECL|member|tx_intr
id|_u16
id|tx_intr
suffix:semicolon
multiline_comment|/* 0x3E TX interrupt pending */
DECL|member|rx_intr
id|_u16
id|rx_intr
suffix:semicolon
multiline_comment|/* 0x40 RX interrupt pending */
DECL|member|rup_intr
id|_u16
id|rup_intr
suffix:semicolon
multiline_comment|/* 0x42 RUP interrupt pending */
DECL|typedef|PARM_MAP
)brace
id|PARM_MAP
suffix:semicolon
multiline_comment|/* Same thing again, but defined as offsets... */
DECL|macro|PM_phb_ptr
mdefine_line|#define&t;PM_phb_ptr&t;&t;0x00&t;/* 0x00 Pointer to the PHB array */
DECL|macro|PM_phb_num_ptr
mdefine_line|#define&t;PM_phb_num_ptr&t;&t;0x02&t;/* 0x02 Ptr to Number of PHB&squot;s */
DECL|macro|PM_free_list
mdefine_line|#define&t;PM_free_list&t;&t;0x04&t;/* 0x04 Free List pointer */
DECL|macro|PM_free_list_end
mdefine_line|#define&t;PM_free_list_end&t;0x06&t;/* 0x06 Free List End pointer */
DECL|macro|PM_q_free_list_ptr
mdefine_line|#define&t;PM_q_free_list_ptr&t;0x08&t;/* 0x08 Ptr to Q_BUF variable */
DECL|macro|PM_unit_id_ptr
mdefine_line|#define&t;PM_unit_id_ptr&t;&t;0x0A&t;/* 0x0A Unit Id */
DECL|macro|PM_link_str_ptr
mdefine_line|#define&t;PM_link_str_ptr&t;&t;0x0C&t;/* 0x0C Link Structure Array */
DECL|macro|PM_bootloader_1
mdefine_line|#define&t;PM_bootloader_1&t;&t;0x0E&t;/* 0x0E 1st Stage Boot Loader */
DECL|macro|PM_bootloader_2
mdefine_line|#define&t;PM_bootloader_2&t;&t;0x10&t;/* 0x10 2nd Stage Boot Loader */
DECL|macro|PM_port_route_map_ptr
mdefine_line|#define&t;PM_port_route_map_ptr&t;0x12&t;/* 0x12 Port Route Map */
DECL|macro|PM_route_ptr
mdefine_line|#define&t;PM_route_ptr&t;&t;0x14&t;/* 0x14 Route Map */
DECL|macro|PM_map_present
mdefine_line|#define&t;PM_map_present&t;&t;0x16&t;/* 0x16 Route Map present */
DECL|macro|PM_pkt_num
mdefine_line|#define&t;PM_pkt_num&t;&t;0x18&t;/* 0x18 Total number of packets */
DECL|macro|PM_q_num
mdefine_line|#define&t;PM_q_num&t;&t;0x1A&t;/* 0x1A Total number of Q packets */
DECL|macro|PM_buffers_per_port
mdefine_line|#define&t;PM_buffers_per_port&t;0x1C&t;/* 0x1C Number of buffers per port */
DECL|macro|PM_heap_size
mdefine_line|#define&t;PM_heap_size&t;&t;0x1E&t;/* 0x1E Initial size of heap */
DECL|macro|PM_heap_left
mdefine_line|#define&t;PM_heap_left&t;&t;0x20&t;/* 0x20 Current Heap left */
DECL|macro|PM_error
mdefine_line|#define&t;PM_error&t;&t;0x22&t;/* 0x22 Error code */
DECL|macro|PM_tx_max
mdefine_line|#define&t;PM_tx_max&t;&t;0x24&t;/* 0x24 Max number of tx pkts per phb */
DECL|macro|PM_rx_max
mdefine_line|#define&t;PM_rx_max&t;&t;0x26&t;/* 0x26 Max number of rx pkts per phb */
DECL|macro|PM_rx_limit
mdefine_line|#define&t;PM_rx_limit&t;&t;0x28&t;/* 0x28 For high / low watermarks */
DECL|macro|PM_links
mdefine_line|#define&t;PM_links&t;&t;0x2A&t;/* 0x2A Links to use */
DECL|macro|PM_timer
mdefine_line|#define&t;PM_timer&t;&t;0x2C&t;/* 0x2C Interrupts per second */
DECL|macro|PM_rups
mdefine_line|#define&t;PM_rups&t;&t;&t;0x2E&t;/* 0x2E Pointer to the RUPs */
DECL|macro|PM_max_phb
mdefine_line|#define&t;PM_max_phb&t;&t;0x30&t;/* 0x30 Mostly for debugging */
DECL|macro|PM_living
mdefine_line|#define&t;PM_living&t;&t;0x32&t;/* 0x32 Just increments!! */
DECL|macro|PM_init_done
mdefine_line|#define&t;PM_init_done&t;&t;0x34&t;/* 0x34 Initialisation over */
DECL|macro|PM_booting_link
mdefine_line|#define&t;PM_booting_link&t;&t;0x36&t;/* 0x36 */
DECL|macro|PM_idle_count
mdefine_line|#define&t;PM_idle_count&t;&t;0x38&t;/* 0x38 Idle time counter */
DECL|macro|PM_busy_count
mdefine_line|#define&t;PM_busy_count&t;&t;0x3A&t;/* 0x3A Busy counter */
DECL|macro|PM_idle_control
mdefine_line|#define&t;PM_idle_control&t;&t;0x3C&t;/* 0x3C Control Idle Process */
DECL|macro|PM_tx_intr
mdefine_line|#define&t;PM_tx_intr&t;&t;0x3E&t;/* 0x4E TX interrupt pending */
DECL|macro|PM_rx_intr
mdefine_line|#define&t;PM_rx_intr&t;&t;0x40&t;/* 0x40 RX interrupt pending */
DECL|macro|PM_rup_intr
mdefine_line|#define&t;PM_rup_intr&t;&t;0x42&t;/* 0x42 RUP interrupt pending */
DECL|macro|sizeof_PARM_MAP
mdefine_line|#define&t;sizeof_PARM_MAP&t;&t;0x44&t;/* structure size = 0x44 */
multiline_comment|/* PARM_MAP.error definitions... */
DECL|macro|E_NO_ERROR
mdefine_line|#define&t;E_NO_ERROR&t;&t;0x00
DECL|macro|E_PROCESS_NOT_INIT
mdefine_line|#define&t;E_PROCESS_NOT_INIT&t;0x01
DECL|macro|E_LINK_TIMEOUT
mdefine_line|#define&t;E_LINK_TIMEOUT&t;&t;0x02
DECL|macro|E_NO_ROUTE
mdefine_line|#define&t;E_NO_ROUTE&t;&t;0x03
DECL|macro|E_CONFUSED
mdefine_line|#define&t;E_CONFUSED&t;&t;0x04
DECL|macro|E_HOME
mdefine_line|#define&t;E_HOME&t;&t;&t;0x05
DECL|macro|E_CSUM_FAIL
mdefine_line|#define&t;E_CSUM_FAIL&t;&t;0x06
DECL|macro|E_DISCONNECTED
mdefine_line|#define&t;E_DISCONNECTED&t;&t;0x07
DECL|macro|E_BAD_RUP
mdefine_line|#define&t;E_BAD_RUP&t;&t;0x08
DECL|macro|E_NO_VIRGIN
mdefine_line|#define&t;E_NO_VIRGIN&t;&t;0x09
DECL|macro|E_BOOT_RUP_BUSY
mdefine_line|#define&t;E_BOOT_RUP_BUSY&t;&t;0x10
DECL|macro|E_CHANALLOC
mdefine_line|#define&t;E_CHANALLOC&t;&t;0x80
DECL|macro|E_POLL_ALLOC
mdefine_line|#define&t;E_POLL_ALLOC&t;&t;0x81
DECL|macro|E_LTTWAKE
mdefine_line|#define&t;E_LTTWAKE&t;&t;0x82
DECL|macro|E_LTT_ALLOC
mdefine_line|#define&t;E_LTT_ALLOC&t;&t;0x83
DECL|macro|E_LRT_ALLOC
mdefine_line|#define&t;E_LRT_ALLOC&t;&t;0x84
DECL|macro|E_CIRRUS
mdefine_line|#define&t;E_CIRRUS&t;&t;0x85
DECL|macro|E_MONITOR
mdefine_line|#define&t;E_MONITOR&t;&t;0x86
DECL|macro|E_PHB_ALLOC
mdefine_line|#define&t;E_PHB_ALLOC&t;&t;0x87
DECL|macro|E_ARRAY_ALLOC
mdefine_line|#define&t;E_ARRAY_ALLOC&t;&t;0x88
DECL|macro|E_QBUF_ALLOC
mdefine_line|#define&t;E_QBUF_ALLOC&t;&t;0x89
DECL|macro|E_PKT_ALLOC
mdefine_line|#define&t;E_PKT_ALLOC&t;&t;0x8a
DECL|macro|E_GET_TX_Q_BUF
mdefine_line|#define&t;E_GET_TX_Q_BUF&t;&t;0x8b
DECL|macro|E_GET_RX_Q_BUF
mdefine_line|#define&t;E_GET_RX_Q_BUF&t;&t;0x8c
DECL|macro|E_MEM_OUT
mdefine_line|#define&t;E_MEM_OUT&t;&t;0x8d
DECL|macro|E_MMU_INIT
mdefine_line|#define&t;E_MMU_INIT&t;&t;0x8e
DECL|macro|E_LTT_INIT
mdefine_line|#define&t;E_LTT_INIT&t;&t;0x8f
DECL|macro|E_LRT_INIT
mdefine_line|#define&t;E_LRT_INIT&t;&t;0x90
DECL|macro|E_LINK_RUN
mdefine_line|#define&t;E_LINK_RUN&t;&t;0x91
DECL|macro|E_MONITOR_ALLOC
mdefine_line|#define&t;E_MONITOR_ALLOC&t;&t;0x92
DECL|macro|E_MONITOR_INIT
mdefine_line|#define&t;E_MONITOR_INIT&t;&t;0x93
DECL|macro|E_POLL_INIT
mdefine_line|#define&t;E_POLL_INIT&t;&t;0x94
multiline_comment|/* PARM_MAP.links definitions... */
DECL|macro|RIO_LINK_ENABLE
mdefine_line|#define&t;RIO_LINK_ENABLE&t;0x80FF
multiline_comment|/*****************************************************************************&n;**********************************         ***********************************&n;**********************************   RUP   ***********************************&n;**********************************         ***********************************&n;*****************************************************************************/
multiline_comment|/* The RUP (Remote Unit Port) structure relates to the Remote Terminal Adapters&n;   attached to the system and there is normally an array of MAX_RUPS (=16) structures&n;   in a host card, defined by PARM_MAP-&gt;rup. */
DECL|struct|_RUP
r_typedef
r_struct
id|_RUP
(brace
DECL|member|txpkt
id|_u16
id|txpkt
suffix:semicolon
multiline_comment|/* 0x00 Outgoing packet */
DECL|member|rxpkt
id|_u16
id|rxpkt
suffix:semicolon
multiline_comment|/* 0x02 ncoming packet */
DECL|member|link
id|_u16
id|link
suffix:semicolon
multiline_comment|/* 0x04 Which link to send packet down ? */
DECL|member|rup_dest_unit
id|_u8
id|rup_dest_unit
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x06 Destination Unit */
DECL|member|handshake
id|_u16
id|handshake
suffix:semicolon
multiline_comment|/* 0x08 Handshaking */
DECL|member|timeout
id|_u16
id|timeout
suffix:semicolon
multiline_comment|/* 0x0A Timeout */
DECL|member|status
id|_u16
id|status
suffix:semicolon
multiline_comment|/* 0x0C Status */
DECL|member|txcontrol
id|_u16
id|txcontrol
suffix:semicolon
multiline_comment|/* 0x0E Transmit control */
DECL|member|rxcontrol
id|_u16
id|rxcontrol
suffix:semicolon
multiline_comment|/* 0x10 Receive control */
DECL|typedef|RUP
)brace
id|RUP
suffix:semicolon
multiline_comment|/* Same thing again, but defined as offsets... */
DECL|macro|RUP_txpkt
mdefine_line|#define&t;RUP_txpkt&t;&t;0x00&t;&t;/* 0x00 Outgoing packet */
DECL|macro|RUP_rxpkt
mdefine_line|#define&t;RUP_rxpkt&t;&t;0x02&t;&t;/* 0x02 Incoming packet */
DECL|macro|RUP_link
mdefine_line|#define&t;RUP_link&t;&t;0x04&t;&t;/* 0x04 Which link to send packet down ? */
DECL|macro|RUP_rup_dest_unit
mdefine_line|#define&t;RUP_rup_dest_unit&t;0x06&t;&t;/* 0x06 Destination Unit */
DECL|macro|RUP_handshake
mdefine_line|#define&t;RUP_handshake&t;&t;0x08&t;&t;/* 0x08 Handshaking */
DECL|macro|RUP_timeout
mdefine_line|#define&t;RUP_timeout&t;&t;0x0A&t;&t;/* 0x0A Timeout */
DECL|macro|RUP_status
mdefine_line|#define&t;RUP_status&t;&t;0x0C&t;&t;/* 0x0C Status */
DECL|macro|RUP_txcontrol
mdefine_line|#define&t;RUP_txcontrol&t;&t;0x0E&t;&t;/* 0x0E Transmit control */
DECL|macro|RUP_rxcontrol
mdefine_line|#define&t;RUP_rxcontrol&t;&t;0x10&t;&t;/* 0x10 Receive control */
DECL|macro|sizeof_RUP
mdefine_line|#define&t;sizeof_RUP&t;&t;0x12&t;&t;/* structure size = 0x12 */
DECL|macro|MAX_RUP
mdefine_line|#define MAX_RUP&t;&t;&t;16
multiline_comment|/* RUP.txcontrol definitions... */
DECL|macro|TX_RUP_INACTIVE
mdefine_line|#define&t;TX_RUP_INACTIVE&t;&t;0&t;&t;/* Nothing to transmit */
DECL|macro|TX_PACKET_READY
mdefine_line|#define&t;TX_PACKET_READY&t;&t;1&t;&t;/* Transmit packet ready */
DECL|macro|TX_LOCK_RUP
mdefine_line|#define&t;TX_LOCK_RUP&t;&t;2&t;&t;/* Transmit side locked */
multiline_comment|/* RUP.txcontrol definitions... */
DECL|macro|RX_RUP_INACTIVE
mdefine_line|#define&t;RX_RUP_INACTIVE&t;&t;0&t;&t;/* Nothing received */
DECL|macro|RX_PACKET_READY
mdefine_line|#define&t;RX_PACKET_READY&t;&t;1&t;&t;/* Packet received */
DECL|macro|RUP_NO_OWNER
mdefine_line|#define&t;RUP_NO_OWNER&t;&t;0xFF&t;&t;/* RUP not owned by any process */
multiline_comment|/*****************************************************************************&n;**********************************         ***********************************&n;**********************************   PHB   ***********************************&n;**********************************         ***********************************&n;*****************************************************************************/
multiline_comment|/* The PHB (Port Header Block) structure relates to the serial ports attached&n;   to the system and there is normally an array of MAX_PHBS (=128) structures&n;   in a host card, defined by PARM_MAP-&gt;phb_ptr and PARM_MAP-&gt;phb_num_ptr. */
DECL|struct|_PHB
r_typedef
r_struct
id|_PHB
(brace
DECL|member|source
id|_u16
id|source
suffix:semicolon
multiline_comment|/* 0x00 Location of the PHB in the host card */
DECL|member|handshake
id|_u16
id|handshake
suffix:semicolon
multiline_comment|/* 0x02 Used to manage receive packet flow control */
DECL|member|status
id|_u16
id|status
suffix:semicolon
multiline_comment|/* 0x04 Internal port transmit/receive status */
DECL|member|timeout
id|_u16
id|timeout
suffix:semicolon
multiline_comment|/* 0x06 Time period to wait for an ACK */
DECL|member|link
id|_u16
id|link
suffix:semicolon
multiline_comment|/* 0x08 The host link associated with the PHB */
DECL|member|destination
id|_u16
id|destination
suffix:semicolon
multiline_comment|/* 0x0A Location of the remote port on the network */
DECL|member|tx_start
id|_u16
id|tx_start
suffix:semicolon
multiline_comment|/* 0x0C first entry in the packet array for transmit packets */
DECL|member|tx_end
id|_u16
id|tx_end
suffix:semicolon
multiline_comment|/* 0x0E last entry in the packet array for transmit packets */
DECL|member|tx_add
id|_u16
id|tx_add
suffix:semicolon
multiline_comment|/* 0x10 position in the packet array for new transmit packets */
DECL|member|tx_remove
id|_u16
id|tx_remove
suffix:semicolon
multiline_comment|/* 0x12 current position in the packet pointer array */
DECL|member|rx_start
id|_u16
id|rx_start
suffix:semicolon
multiline_comment|/* 0x14 first entry in the packet array for receive packets */
DECL|member|rx_end
id|_u16
id|rx_end
suffix:semicolon
multiline_comment|/* 0x16 last entry in the packet array for receive packets */
DECL|member|rx_add
id|_u16
id|rx_add
suffix:semicolon
multiline_comment|/* 0x18 position in the packet array for new receive packets */
DECL|member|rx_remove
id|_u16
id|rx_remove
suffix:semicolon
multiline_comment|/* 0x1A current position in the packet pointer array */
DECL|typedef|PHB
)brace
id|PHB
suffix:semicolon
multiline_comment|/* Same thing again, but defined as offsets... */
DECL|macro|PHB_source
mdefine_line|#define&t;PHB_source&t;&t;0x00&t;&t;/* 0x00 Location of the PHB in the host card */
DECL|macro|PHB_handshake
mdefine_line|#define&t;PHB_handshake&t;&t;0x02&t;&t;/* 0x02 Used to manage receive packet flow control */
DECL|macro|PHB_status
mdefine_line|#define&t;PHB_status&t;&t;0x04&t;&t;/* 0x04 Internal port transmit/receive status */
DECL|macro|PHB_timeout
mdefine_line|#define&t;PHB_timeout&t;&t;0x06&t;&t;/* 0x06 Time period to wait for an ACK */
DECL|macro|PHB_link
mdefine_line|#define&t;PHB_link&t;&t;0x08&t;&t;/* 0x08 The host link associated with the PHB */
DECL|macro|PHB_destination
mdefine_line|#define&t;PHB_destination&t;&t;0x0A&t;&t;/* 0x0A Location of the remote port on the network */
DECL|macro|PHB_tx_start
mdefine_line|#define&t;PHB_tx_start&t;&t;0x0C&t;&t;/* 0x0C first entry in the packet array for transmit packets */
DECL|macro|PHB_tx_end
mdefine_line|#define&t;PHB_tx_end&t;&t;0x0E&t;&t;/* 0x0E last entry in the packet array for transmit packets */
DECL|macro|PHB_tx_add
mdefine_line|#define&t;PHB_tx_add&t;&t;0x10&t;&t;/* 0x10 position in the packet array for new transmit packets */
DECL|macro|PHB_tx_remove
mdefine_line|#define&t;PHB_tx_remove&t;&t;0x12&t;&t;/* 0x12 current position in the packet pointer array */
DECL|macro|PHB_rx_start
mdefine_line|#define&t;PHB_rx_start&t;&t;0x14&t;&t;/* 0x14 first entry in the packet array for receive packets */
DECL|macro|PHB_rx_end
mdefine_line|#define&t;PHB_rx_end&t;&t;0x16&t;&t;/* 0x16 last entry in the packet array for receive packets */
DECL|macro|PHB_rx_add
mdefine_line|#define&t;PHB_rx_add&t;&t;0x18&t;&t;/* 0x18 position in the packet array for new receive packets */
DECL|macro|PHB_rx_remove
mdefine_line|#define&t;PHB_rx_remove&t;&t;0x1A&t;&t;/* 0x1A current position in the packet pointer array */
DECL|macro|sizeof_PHB
mdefine_line|#define&t;sizeof_PHB&t;&t;0x1C&t;&t;/* structure size = 0x1C */
multiline_comment|/* PHB.handshake definitions... */
DECL|macro|PHB_HANDSHAKE_SET
mdefine_line|#define&t;PHB_HANDSHAKE_SET&t;0x0001&t;&t;/* Set by LRT */
DECL|macro|PHB_HANDSHAKE_RESET
mdefine_line|#define&t;PHB_HANDSHAKE_RESET&t;0x0002&t;&t;/* Set by ISR / driver */
DECL|macro|PHB_HANDSHAKE_FLAGS
mdefine_line|#define&t;PHB_HANDSHAKE_FLAGS&t;(PHB_HANDSHAKE_RESET|PHB_HANDSHAKE_SET)
multiline_comment|/* Reset by ltt */
DECL|macro|MAX_PHB
mdefine_line|#define&t;MAX_PHB&t;&t;&t;128&t;&t;/* range 0-127 */
multiline_comment|/*****************************************************************************&n;**********************************         ***********************************&n;**********************************   LPB   ***********************************&n;**********************************         ***********************************&n;*****************************************************************************/
multiline_comment|/* The LPB (Link Parameter Block) structure relates to a RIO Network Link&n;   and there is normally an array of MAX_LINKS (=4) structures in a host card,&n;   defined by PARM_MAP-&gt;link_str_ptr. */
DECL|struct|_LPB
r_typedef
r_struct
id|_LPB
(brace
DECL|member|link_number
id|_u16
id|link_number
suffix:semicolon
multiline_comment|/* 0x00 Link Number */
DECL|member|in_ch
id|_u16
id|in_ch
suffix:semicolon
multiline_comment|/* 0x02 Link In Channel */
DECL|member|out_ch
id|_u16
id|out_ch
suffix:semicolon
multiline_comment|/* 0x04 Link Out Channel */
DECL|member|attached_serial
id|_u8
id|attached_serial
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x06 Attached serial number */
DECL|member|attached_host_serial
id|_u8
id|attached_host_serial
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0A Serial number of Host who booted other end */
DECL|member|descheduled
id|_u16
id|descheduled
suffix:semicolon
multiline_comment|/* 0x0E Currently Descheduled */
DECL|member|state
id|_u16
id|state
suffix:semicolon
multiline_comment|/* 0x10 Current state */
DECL|member|send_poll
id|_u16
id|send_poll
suffix:semicolon
multiline_comment|/* 0x12 Send a Poll Packet */
DECL|member|ltt_p
id|_u16
id|ltt_p
suffix:semicolon
multiline_comment|/* 0x14 Process Descriptor */
DECL|member|lrt_p
id|_u16
id|lrt_p
suffix:semicolon
multiline_comment|/* 0x16 Process Descriptor */
DECL|member|lrt_status
id|_u16
id|lrt_status
suffix:semicolon
multiline_comment|/* 0x18 Current lrt status */
DECL|member|ltt_status
id|_u16
id|ltt_status
suffix:semicolon
multiline_comment|/* 0x1A Current ltt status */
DECL|member|timeout
id|_u16
id|timeout
suffix:semicolon
multiline_comment|/* 0x1C Timeout value */
DECL|member|topology
id|_u16
id|topology
suffix:semicolon
multiline_comment|/* 0x1E Topology bits */
DECL|member|mon_ltt
id|_u16
id|mon_ltt
suffix:semicolon
multiline_comment|/* 0x20 */
DECL|member|mon_lrt
id|_u16
id|mon_lrt
suffix:semicolon
multiline_comment|/* 0x22 */
DECL|member|num_pkts
id|_u16
id|num_pkts
suffix:semicolon
multiline_comment|/* 0x24 */
DECL|member|add_packet_list
id|_u16
id|add_packet_list
suffix:semicolon
multiline_comment|/* 0x26 Add packets to here */
DECL|member|remove_packet_list
id|_u16
id|remove_packet_list
suffix:semicolon
multiline_comment|/* 0x28 Send packets from here */
DECL|member|lrt_fail_chan
id|_u16
id|lrt_fail_chan
suffix:semicolon
multiline_comment|/* 0x2A Lrt&squot;s failure channel */
DECL|member|ltt_fail_chan
id|_u16
id|ltt_fail_chan
suffix:semicolon
multiline_comment|/* 0x2C Ltt&squot;s failure channel */
DECL|member|rup
id|RUP
id|rup
suffix:semicolon
multiline_comment|/* 0x2E RUP structure for HOST to driver comms */
DECL|member|link_rup
id|RUP
id|link_rup
suffix:semicolon
multiline_comment|/* 0x40 RUP for the link (POLL, topology etc.) */
DECL|member|attached_link
id|_u16
id|attached_link
suffix:semicolon
multiline_comment|/* 0x52 Number of attached link */
DECL|member|csum_errors
id|_u16
id|csum_errors
suffix:semicolon
multiline_comment|/* 0x54 csum errors */
DECL|member|num_disconnects
id|_u16
id|num_disconnects
suffix:semicolon
multiline_comment|/* 0x56 number of disconnects */
DECL|member|num_sync_rcvd
id|_u16
id|num_sync_rcvd
suffix:semicolon
multiline_comment|/* 0x58 # sync&squot;s received */
DECL|member|num_sync_rqst
id|_u16
id|num_sync_rqst
suffix:semicolon
multiline_comment|/* 0x5A # sync requests */
DECL|member|num_tx
id|_u16
id|num_tx
suffix:semicolon
multiline_comment|/* 0x5C Num pkts sent */
DECL|member|num_rx
id|_u16
id|num_rx
suffix:semicolon
multiline_comment|/* 0x5E Num pkts received */
DECL|member|module_attached
id|_u16
id|module_attached
suffix:semicolon
multiline_comment|/* 0x60 Module tpyes of attached */
DECL|member|led_timeout
id|_u16
id|led_timeout
suffix:semicolon
multiline_comment|/* 0x62 LED timeout */
DECL|member|first_port
id|_u16
id|first_port
suffix:semicolon
multiline_comment|/* 0x64 First port to service */
DECL|member|last_port
id|_u16
id|last_port
suffix:semicolon
multiline_comment|/* 0x66 Last port to service */
DECL|typedef|LPB
)brace
id|LPB
suffix:semicolon
multiline_comment|/* Same thing again, but defined as offsets... */
DECL|macro|LPB_link_number
mdefine_line|#define&t;LPB_link_number&t;&t;0x00&t;&t;/* 0x00 Link Number */
DECL|macro|LPB_in_ch
mdefine_line|#define&t;LPB_in_ch&t;&t;0x02&t;&t;/* 0x02 Link In Channel */
DECL|macro|LPB_out_ch
mdefine_line|#define&t;LPB_out_ch&t;&t;0x04&t;&t;/* 0x04 Link Out Channel */
DECL|macro|LPB_attached_serial
mdefine_line|#define&t;LPB_attached_serial&t;0x06&t;&t;/* 0x06 Attached serial number */
DECL|macro|LPB_attached_host_serial
mdefine_line|#define&t;LPB_attached_host_serial 0x0A&t;&t;/* 0x0A Serial number of Host who booted other end */
DECL|macro|LPB_descheduled
mdefine_line|#define&t;LPB_descheduled&t;&t;0x0E&t;&t;/* 0x0E Currently Descheduled */
DECL|macro|LPB_state
mdefine_line|#define&t;LPB_state&t;&t;0x10&t;&t;/* 0x10 Current state */
DECL|macro|LPB_send_poll
mdefine_line|#define&t;LPB_send_poll&t;&t;0x12&t;&t;/* 0x12 Send a Poll Packet */
DECL|macro|LPB_ltt_p
mdefine_line|#define&t;LPB_ltt_p&t;&t;0x14&t;&t;/* 0x14 Process Descriptor */
DECL|macro|LPB_lrt_p
mdefine_line|#define&t;LPB_lrt_p&t;&t;0x16&t;&t;/* 0x16 Process Descriptor */
DECL|macro|LPB_lrt_status
mdefine_line|#define&t;LPB_lrt_status&t;&t;0x18&t;&t;/* 0x18 Current lrt status */
DECL|macro|LPB_ltt_status
mdefine_line|#define&t;LPB_ltt_status&t;&t;0x1A&t;&t;/* 0x1A Current ltt status */
DECL|macro|LPB_timeout
mdefine_line|#define&t;LPB_timeout&t;&t;0x1C&t;&t;/* 0x1C Timeout value */
DECL|macro|LPB_topology
mdefine_line|#define&t;LPB_topology&t;&t;0x1E&t;&t;/* 0x1E Topology bits */
DECL|macro|LPB_mon_ltt
mdefine_line|#define&t;LPB_mon_ltt&t;&t;0x20&t;&t;/* 0x20 */
DECL|macro|LPB_mon_lrt
mdefine_line|#define&t;LPB_mon_lrt&t;&t;0x22&t;&t;/* 0x22 */
DECL|macro|LPB_num_pkts
mdefine_line|#define&t;LPB_num_pkts&t;&t;0x24&t;&t;/* 0x24 */
DECL|macro|LPB_add_packet_list
mdefine_line|#define&t;LPB_add_packet_list&t;0x26&t;&t;/* 0x26 Add packets to here */
DECL|macro|LPB_remove_packet_list
mdefine_line|#define&t;LPB_remove_packet_list&t;0x28&t;&t;/* 0x28 Send packets from here */
DECL|macro|LPB_lrt_fail_chan
mdefine_line|#define&t;LPB_lrt_fail_chan&t;0x2A&t;&t;/* 0x2A Lrt&squot;s failure channel */
DECL|macro|LPB_ltt_fail_chan
mdefine_line|#define&t;LPB_ltt_fail_chan&t;0x2C&t;&t;/* 0x2C Ltt&squot;s failure channel */
DECL|macro|LPB_rup
mdefine_line|#define&t;LPB_rup&t;&t;&t;0x2E&t;&t;/* 0x2E RUP structure for HOST to driver comms */
DECL|macro|LPB_link_rup
mdefine_line|#define&t;LPB_link_rup&t;&t;0x40&t;&t;/* 0x40 RUP for the link (POLL, topology etc.) */
DECL|macro|LPB_attached_link
mdefine_line|#define&t;LPB_attached_link&t;0x52&t;&t;/* 0x52 Number of attached link */
DECL|macro|LPB_csum_errors
mdefine_line|#define&t;LPB_csum_errors&t;&t;0x54&t;&t;/* 0x54 csum errors */
DECL|macro|LPB_num_disconnects
mdefine_line|#define&t;LPB_num_disconnects&t;0x56&t;&t;/* 0x56 number of disconnects */
DECL|macro|LPB_num_sync_rcvd
mdefine_line|#define&t;LPB_num_sync_rcvd&t;0x58&t;&t;/* 0x58 # sync&squot;s received */
DECL|macro|LPB_num_sync_rqst
mdefine_line|#define&t;LPB_num_sync_rqst&t;0x5A&t;&t;/* 0x5A # sync requests */
DECL|macro|LPB_num_tx
mdefine_line|#define&t;LPB_num_tx&t;&t;0x5C&t;&t;/* 0x5C Num pkts sent */
DECL|macro|LPB_num_rx
mdefine_line|#define&t;LPB_num_rx&t;&t;0x5E&t;&t;/* 0x5E Num pkts received */
DECL|macro|LPB_module_attached
mdefine_line|#define&t;LPB_module_attached&t;0x60&t;&t;/* 0x60 Module tpyes of attached */
DECL|macro|LPB_led_timeout
mdefine_line|#define&t;LPB_led_timeout&t;&t;0x62&t;&t;/* 0x62 LED timeout */
DECL|macro|LPB_first_port
mdefine_line|#define&t;LPB_first_port&t;&t;0x64&t;&t;/* 0x64 First port to service */
DECL|macro|LPB_last_port
mdefine_line|#define&t;LPB_last_port&t;&t;0x66&t;&t;/* 0x66 Last port to service */
DECL|macro|sizeof_LPB
mdefine_line|#define&t;sizeof_LPB&t;&t;0x68&t;&t;/* structure size = 0x68 */
DECL|macro|LINKS_PER_UNIT
mdefine_line|#define&t;LINKS_PER_UNIT&t;&t;4&t;&t;/* number of links from a host */
multiline_comment|/*****************************************************************************&n;********************************               *******************************&n;********************************   FREE_LIST   *******************************&n;********************************               *******************************&n;*****************************************************************************/
multiline_comment|/* Used to overlay packet headers when allocating/freeing packets from the free list */
DECL|struct|_FREE_LIST
r_typedef
r_struct
id|_FREE_LIST
(brace
DECL|member|next
id|_u16
id|next
suffix:semicolon
multiline_comment|/* 0x00 offset of next list item */
DECL|member|prev
id|_u16
id|prev
suffix:semicolon
multiline_comment|/* 0x02 offset of previous list item */
DECL|typedef|FREE_LIST
)brace
id|FREE_LIST
suffix:semicolon
multiline_comment|/* Same thing again, but defined as offsets... */
DECL|macro|FL_next
mdefine_line|#define&t;FL_next&t;&t;&t;0x00&t;&t;/* 0x00 offset of next list item */
DECL|macro|FL_prev
mdefine_line|#define&t;FL_prev&t;&t;&t;0x02&t;&t;/* 0x02 offset of previous list item */
multiline_comment|/*****************************************************************************&n;**********************************         ***********************************&n;**********************************   PKT   ***********************************&n;**********************************         ***********************************&n;*****************************************************************************/
multiline_comment|/* The PKT is the main unit of communication between Host Cards and RTAs across&n;   the RIO network.  */
DECL|macro|PKT_MAX_DATA_LEN
mdefine_line|#define PKT_MAX_DATA_LEN   72&t;&t;&t;/* Size of packet data */
DECL|struct|_PKT
r_typedef
r_struct
id|_PKT
(brace
DECL|member|dest_unit
id|_u8
id|dest_unit
suffix:semicolon
multiline_comment|/* 0x00 Destination Unit Id */
DECL|member|dest_port
id|_u8
id|dest_port
suffix:semicolon
multiline_comment|/* 0x01 Destination Port */
DECL|member|src_unit
id|_u8
id|src_unit
suffix:semicolon
multiline_comment|/* 0x02 Source Unit Id */
DECL|member|src_port
id|_u8
id|src_port
suffix:semicolon
multiline_comment|/* 0x03 Source Port */
DECL|member|len
id|_u8
id|len
suffix:semicolon
multiline_comment|/* 0x04 Length (in bytes) of data field */
DECL|member|control
id|_u8
id|control
suffix:semicolon
multiline_comment|/* 0x05 */
DECL|member|data
id|_u8
id|data
(braket
id|PKT_MAX_DATA_LEN
)braket
suffix:semicolon
multiline_comment|/* 0x06 Actual data */
DECL|member|csum
id|_u16
id|csum
suffix:semicolon
multiline_comment|/* 0x4E C-SUM */
DECL|typedef|PKT
)brace
id|PKT
suffix:semicolon
multiline_comment|/* Same thing again, but defined as offsets... */
DECL|macro|PKT_dest_unit
mdefine_line|#define&t;PKT_dest_unit&t;&t;0x00&t;&t;/* 0x00 Destination Unit Id */
DECL|macro|PKT_dest_port
mdefine_line|#define&t;PKT_dest_port&t;&t;0x01&t;&t;/* 0x01 Destination Port */
DECL|macro|PKT_src_unit
mdefine_line|#define&t;PKT_src_unit&t;&t;0x02&t;&t;/* 0x02 Source Unit Id */
DECL|macro|PKT_src_port
mdefine_line|#define&t;PKT_src_port&t;&t;0x03&t;&t;/* 0x03 Source Port */
DECL|macro|PKT_len
mdefine_line|#define&t;PKT_len&t;&t;&t;0x04&t;&t;/* 0x04 Length (in bytes) of data field */
DECL|macro|PKT_control
mdefine_line|#define&t;PKT_control&t;&t;0x05&t;&t;/* 0x05 */
DECL|macro|PKT_data
mdefine_line|#define&t;PKT_data&t;&t;0x06&t;&t;/* 0x06 Actual data */
DECL|macro|PKT_csum
mdefine_line|#define&t;PKT_csum&t;&t;0x4E&t;&t;/* 0x4E C-SUM */
DECL|macro|sizeof_PKT
mdefine_line|#define&t;sizeof_PKT&t;&t;0x50&t;&t;/* structure size = 0x50 */
multiline_comment|/* PKT.len definitions... */
DECL|macro|PKT_CMD_BIT
mdefine_line|#define&t;PKT_CMD_BIT&t;&t;0x80
DECL|macro|PKT_CMD_DATA
mdefine_line|#define&t;PKT_CMD_DATA&t;&t;0x80
DECL|macro|PKT_LEN_MASK
mdefine_line|#define&t;PKT_LEN_MASK&t;&t;0x7F
multiline_comment|/* PKT.control definitions... */
DECL|macro|PKT_ACK
mdefine_line|#define&t;PKT_ACK&t;&t;&t;0x40
DECL|macro|PKT_TGL
mdefine_line|#define&t;PKT_TGL&t;&t;&t;0x20
DECL|macro|DATA_WNDW
mdefine_line|#define&t;DATA_WNDW&t;&t;0x10
DECL|macro|PKT_TTL_MASK
mdefine_line|#define&t;PKT_TTL_MASK&t;&t;0x0F
DECL|macro|MAX_TTL
mdefine_line|#define&t;MAX_TTL&t;&t;&t;0x0F
multiline_comment|/*****************************************************************************&n;*****************************                     ****************************&n;*****************************   Control Packets   ****************************&n;*****************************                     ****************************&n;*****************************************************************************/
multiline_comment|/* The following definitions and structures define the control packets sent&n;   between the driver and RIO Ports, RTAs and Host Cards. */
DECL|macro|PRE_EMPTIVE
mdefine_line|#define&t;PRE_EMPTIVE&t;&t;0x80&t;&t;&t;/* Pre-emptive command (sent via port&squot;s RUP) */
multiline_comment|/* &quot;in-band&quot; and &quot;pre-emptive&quot; port commands... */
DECL|macro|OPEN
mdefine_line|#define&t;OPEN&t;&t;&t;0x00&t;&t;&t;/* Driver-&gt;RIO Open a port */
DECL|macro|CONFIG
mdefine_line|#define&t;CONFIG&t;&t;&t;0x01&t;&t;&t;/* Driver-&gt;RIO Configure a port */
DECL|macro|MOPEN
mdefine_line|#define&t;MOPEN&t;&t;&t;0x02&t;&t;&t;/* Driver-&gt;RIO Modem open (wait for DCD) */
DECL|macro|CLOSE
mdefine_line|#define&t;CLOSE&t;&t;&t;0x03&t;&t;&t;/* Driver-&gt;RIO Close a port */
DECL|macro|WFLUSH
mdefine_line|#define&t;WFLUSH&t;&t;&t;(0x04|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Write flush */
DECL|macro|RFLUSH
mdefine_line|#define&t;RFLUSH&t;&t;&t;(0x05|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Read flush */
DECL|macro|RESUME
mdefine_line|#define&t;RESUME&t;&t;&t;(0x06|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Behave as if XON received */
DECL|macro|SBREAK
mdefine_line|#define&t;SBREAK&t;&t;&t;0x07&t;&t;&t;/* Driver-&gt;RIO Start break */
DECL|macro|EBREAK
mdefine_line|#define&t;EBREAK&t;&t;&t;0x08&t;&t;&t;/* Driver-&gt;RIO End break */
DECL|macro|SUSPEND
mdefine_line|#define&t;SUSPEND&t;&t;&t;(0x09|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Behave as if XOFF received */
DECL|macro|FCLOSE
mdefine_line|#define&t;FCLOSE&t;&t;&t;(0x0A|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Force close */
DECL|macro|XPRINT
mdefine_line|#define&t;XPRINT&t;&t;&t;0x0B&t;&t;&t;/* Driver-&gt;RIO Xprint packet */
DECL|macro|MBIS
mdefine_line|#define&t;MBIS&t;&t;&t;(0x0C|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Set modem lines */
DECL|macro|MBIC
mdefine_line|#define&t;MBIC&t;&t;&t;(0x0D|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Clear modem lines */
DECL|macro|MSET
mdefine_line|#define&t;MSET&t;&t;&t;(0x0E|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Set modem lines */
DECL|macro|PCLOSE
mdefine_line|#define&t;PCLOSE&t;&t;&t;0x0F&t;&t;&t;/* Driver-&gt;RIO Pseudo close */
DECL|macro|MGET
mdefine_line|#define&t;MGET&t;&t;&t;(0x10|PRE_EMPTIVE)&t;/* Driver-&gt;RIO Force update of modem status */
DECL|macro|MEMDUMP
mdefine_line|#define&t;MEMDUMP&t;&t;&t;(0x11|PRE_EMPTIVE)&t;/* Driver-&gt;RIO DEBUG request for RTA memory */
DECL|macro|READ_REGISTER
mdefine_line|#define&t;READ_REGISTER&t;&t;(0x12|PRE_EMPTIVE)&t;/* Driver-&gt;RIO DEBUG read CD1400 register */
multiline_comment|/* Remote Unit Port (RUP) packet definitions... (specified in PKT.dest_unit and PKT.src_unit) */
DECL|macro|SYNC_RUP
mdefine_line|#define&t;SYNC_RUP&t;&t;0xFF&t;&t;&t;/* Download internal */
DECL|macro|COMMAND_RUP
mdefine_line|#define&t;COMMAND_RUP&t;&t;0xFE&t;&t;&t;/* Command ack/status */
DECL|macro|ERROR_RUP
mdefine_line|#define&t;ERROR_RUP&t;&t;0xFD&t;&t;&t;/* Download internal */
DECL|macro|POLL_RUP
mdefine_line|#define&t;POLL_RUP&t;&t;0xFC&t;&t;&t;/* Download internal */
DECL|macro|BOOT_RUP
mdefine_line|#define&t;BOOT_RUP&t;&t;0xFB&t;&t;&t;/* Used to boot RTAs */
DECL|macro|ROUTE_RUP
mdefine_line|#define&t;ROUTE_RUP&t;&t;0xFA&t;&t;&t;/* Used to specify routing/topology */
DECL|macro|STATUS_RUP
mdefine_line|#define&t;STATUS_RUP&t;&t;0xF9&t;&t;&t;/* Not used */
DECL|macro|POWER_RUP
mdefine_line|#define&t;POWER_RUP&t;&t;0xF8&t;&t;&t;/* Download internal */
multiline_comment|/* COMMAND_RUP definitions... */
DECL|macro|COMPLETE
mdefine_line|#define&t;COMPLETE&t;&t;(0x20|PRE_EMPTIVE)&t;/* RIO-&gt;Driver Command complete */
DECL|macro|BREAK_RECEIVED
mdefine_line|#define&t;BREAK_RECEIVED&t;&t;(0x21|PRE_EMPTIVE)&t;/* RIO-&gt;Driver Break received */
DECL|macro|MODEM_STATUS
mdefine_line|#define&t;MODEM_STATUS&t;&t;(0x22|PRE_EMPTIVE)&t;/* RIO-&gt;Driver Modem status change */
multiline_comment|/* BOOT_RUP definitions... */
DECL|macro|BOOT_REQUEST
mdefine_line|#define&t;BOOT_REQUEST&t;&t;0x00&t;&t;&t;/* RIO-&gt;Driver Request for boot */
DECL|macro|BOOT_ABORT
mdefine_line|#define&t;BOOT_ABORT&t;&t;0x01&t;&t;&t;/* Driver-&gt;RIO Abort a boot */
DECL|macro|BOOT_SEQUENCE
mdefine_line|#define&t;BOOT_SEQUENCE&t;&t;0x02&t;&t;&t;/* Driver-&gt;RIO Packet with firmware details */
DECL|macro|BOOT_COMPLETED
mdefine_line|#define&t;BOOT_COMPLETED&t;&t;0x03&t;&t;&t;/* RIO-&gt;Driver Boot completed */
DECL|macro|IFOAD
mdefine_line|#define IFOAD&t;&t;&t;0x2F&t;&t;&t;/* Driver-&gt;RIO Shutdown/Reboot RTA (Fall Over And Die) */
DECL|macro|IDENTIFY
mdefine_line|#define&t;IDENTIFY&t;&t;0x30&t;&t;&t;/* Driver-&gt;RIO Identify RTA */
DECL|macro|ZOMBIE
mdefine_line|#define&t;ZOMBIE&t;&t;&t;0x31&t;&t;&t;/* Driver-&gt;RIO Shutdown/Flash LEDs */
DECL|macro|UFOAD
mdefine_line|#define&t;UFOAD&t;&t;&t;0x32&t;&t;&t;/* Driver-&gt;RIO Shutdown/Reboot neighbouring RTA */
DECL|macro|IWAIT
mdefine_line|#define IWAIT&t;&t;&t;0x33&t;&t;&t;/* Driver-&gt;RIO Pause booting process */
multiline_comment|/* ROUTE_RUP definitions... */
DECL|macro|ROUTE_REQUEST
mdefine_line|#define&t;ROUTE_REQUEST&t;&t;0x00&t;&t;&t;/* RIO-&gt;Driver Request an ID */
DECL|macro|ROUTE_FOAD
mdefine_line|#define&t;ROUTE_FOAD&t;&t;0x01&t;&t;&t;/* Driver-&gt;RIO Shutdown/reboot RTA */
DECL|macro|ROUTE_ALREADY
mdefine_line|#define&t;ROUTE_ALREADY&t;&t;0x02&t;&t;&t;/* Driver-&gt;RIO Not used */
DECL|macro|ROUTE_USED
mdefine_line|#define&t;ROUTE_USED&t;&t;0x03&t;&t;&t;/* Driver-&gt;RIO Not used */
DECL|macro|ROUTE_ALLOCATE
mdefine_line|#define&t;ROUTE_ALLOCATE&t;&t;0x04&t;&t;&t;/* Driver-&gt;RIO Allocate RTA RUP numbers */
DECL|macro|ROUTE_REQ_TOP
mdefine_line|#define&t;ROUTE_REQ_TOP&t;&t;0x05&t;&t;&t;/* Driver-&gt;RIO Not used */
DECL|macro|ROUTE_TOPOLOGY
mdefine_line|#define ROUTE_TOPOLOGY&t;&t;0x06&t;&t;&t;/* RIO-&gt;Driver Route/Topology status */
multiline_comment|/*****************************************************************************&n;**********************************          **********************************&n;**********************************   OPEN   **********************************&n;**********************************          **********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   Sent to open a port. &n;   Structure of configuration info used with OPEN, CONFIG and MOPEN packets... */
DECL|macro|PKT_Cmd
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
DECL|macro|PKT_Cor1
mdefine_line|#define&t;PKT_Cor1&t;&t;(PKT_Data+1)&t;&t;/* Channel Option Register 1 */
DECL|macro|PKT_Cor2
mdefine_line|#define&t;PKT_Cor2&t;&t;(PKT_Data+2)&t;&t;/* Channel Option Register 2 */
DECL|macro|PKT_Cor4
mdefine_line|#define&t;PKT_Cor4&t;&t;(PKT_Data+3)&t;&t;/* Channel Option Register 4 */
DECL|macro|PKT_Cor5
mdefine_line|#define&t;PKT_Cor5&t;&t;(PKT_Data+4)&t;&t;/* Channel Option Register 5 */
DECL|macro|PKT_TxXon
mdefine_line|#define&t;PKT_TxXon&t;&t;(PKT_Data+5)&t;&t;/* Transmit XON character */
DECL|macro|PKT_TxXoff
mdefine_line|#define&t;PKT_TxXoff&t;&t;(PKT_Data+6)&t;&t;/* Transmit XOFF character */
DECL|macro|PKT_RxXon
mdefine_line|#define&t;PKT_RxXon&t;&t;(PKT_Data+7)&t;&t;/* Receive XON character */
DECL|macro|PKT_RxXoff
mdefine_line|#define&t;PKT_RxXoff&t;&t;(PKT_Data+8)&t;&t;/* Receive XOFF character */
DECL|macro|PKT_Lnext
mdefine_line|#define&t;PKT_Lnext&t;&t;(PKT_Data+9)&t;&t;/* Lnext character */
DECL|macro|PKT_TxBaud
mdefine_line|#define&t;PKT_TxBaud&t;&t;(PKT_Data+10)&t;&t;/* Transmit baud rate */
DECL|macro|PKT_RxBaud
mdefine_line|#define&t;PKT_RxBaud&t;&t;(PKT_Data+11)&t;&t;/* Receive baud rate */
multiline_comment|/* COR1 definitions... */
DECL|macro|COR1_PARITY
mdefine_line|#define&t;COR1_PARITY&t;&t;0xE0&t;&t;&t;/* Parity mask */
DECL|macro|COR1_NONE
mdefine_line|#define&t;COR1_NONE&t;&t;0x00&t;&t;&t;/* No parity */
DECL|macro|COR1_SPACE
mdefine_line|#define&t;COR1_SPACE&t;&t;0x20&t;&t;&t;/* Space parity */
DECL|macro|COR1_EVEN
mdefine_line|#define&t;COR1_EVEN&t;&t;0x40&t;&t;&t;/* Even parity */
DECL|macro|COR1_MARK
mdefine_line|#define&t;COR1_MARK&t;&t;0xA0&t;&t;&t;/* Mark parity */
DECL|macro|COR1_ODD
mdefine_line|#define&t;COR1_ODD&t;&t;0xC0&t;&t;&t;/* Odd parity */
DECL|macro|COR1_STOPBITS
mdefine_line|#define&t;COR1_STOPBITS&t;&t;0x0C&t;&t;&t;/* Stop bits mask */
DECL|macro|COR1_STOP1
mdefine_line|#define&t;COR1_STOP1&t;&t;0x00&t;&t;&t;/* 1 stop bit */
DECL|macro|COR1_STOP1_5
mdefine_line|#define&t;COR1_STOP1_5&t;&t;0x04&t;&t;&t;/* 1.5 stop bits */
DECL|macro|COR1_STOP2
mdefine_line|#define&t;COR1_STOP2&t;&t;0x08&t;&t;&t;/* 2 stop bits */
DECL|macro|COR1_DATABITS
mdefine_line|#define&t;COR1_DATABITS&t;&t;0x03&t;&t;&t;/* Data bits mask */
DECL|macro|COR1_DATA5
mdefine_line|#define&t;COR1_DATA5&t;&t;0x00&t;&t;&t;/* 5 data bits */
DECL|macro|COR1_DATA6
mdefine_line|#define&t;COR1_DATA6&t;&t;0x01&t;&t;&t;/* 6 data bits */
DECL|macro|COR1_DATA7
mdefine_line|#define&t;COR1_DATA7&t;&t;0x02&t;&t;&t;/* 7 data bits */
DECL|macro|COR1_DATA8
mdefine_line|#define&t;COR1_DATA8&t;&t;0x03&t;&t;&t;/* 8 data bits */
multiline_comment|/* COR2 definitions... */
DECL|macro|COR2_XON_TXFLOW
mdefine_line|#define&t;COR2_XON_TXFLOW&t;&t;0x40&t;&t;&t;/* XON/XOFF Transmit Flow */
DECL|macro|COR2_XANY_TXFLOW
mdefine_line|#define&t;COR2_XANY_TXFLOW&t;0xC0&t;&t;&t;/* XON/XANY Transmit Flow */
DECL|macro|COR2_HUPCL
mdefine_line|#define&t;COR2_HUPCL&t;&t;0x20&t;&t;&t;/* Hang Up On Close */
DECL|macro|COR2_DSR_TXFLOW
mdefine_line|#define&t;COR2_DSR_TXFLOW&t;&t;0x08&t;&t;&t;/* DSR Transmit Flow Control */
DECL|macro|COR2_RTS_RXFLOW
mdefine_line|#define&t;COR2_RTS_RXFLOW&t;&t;0x04&t;&t;&t;/* RTS Receive Flow Control */
DECL|macro|COR2_CTS_TXFLOW
mdefine_line|#define&t;COR2_CTS_TXFLOW&t;&t;0x02&t;&t;&t;/* CTS Transmit Flow Control */
DECL|macro|COR2_XON_RXFLOW
mdefine_line|#define&t;COR2_XON_RXFLOW&t;&t;0x01&t;&t;&t;/* XON/XOFF Receive Flow */
multiline_comment|/* COR4 definition... */
DECL|macro|COR4_IGNCR
mdefine_line|#define&t;COR4_IGNCR&t;&t;0x80&t;&t;&t;/* Discard received CR */
DECL|macro|COR4_ICRNL
mdefine_line|#define&t;COR4_ICRNL&t;&t;0x40&t;&t;&t;/* Map received CR -&gt; NL */
DECL|macro|COR4_INLCR
mdefine_line|#define&t;COR4_INLCR&t;&t;0x20&t;&t;&t;/* Map received NL -&gt; CR */
DECL|macro|COR4_IGNBRK
mdefine_line|#define&t;COR4_IGNBRK&t;&t;0x10&t;&t;&t;/* Ignore Received Break */
DECL|macro|COR4_NBRKINT
mdefine_line|#define&t;COR4_NBRKINT&t;&t;0x08&t;&t;&t;/* No interrupt on rx Break */
DECL|macro|COR4_IGNPAR
mdefine_line|#define&t;COR4_IGNPAR&t;&t;0x04&t;&t;&t;/* ignore rx parity error chars */
DECL|macro|COR4_PARMRK
mdefine_line|#define&t;COR4_PARMRK&t;&t;0x02&t;&t;&t;/* Mark rx parity error chars */
DECL|macro|COR4_RAISEMOD
mdefine_line|#define&t;COR4_RAISEMOD&t;&t;0x01&t;&t;&t;/* Raise modem lines on !0 baud */
multiline_comment|/* COR5 definitions... */
DECL|macro|COR5_ISTRIP
mdefine_line|#define&t;COR5_ISTRIP&t;&t;0x80&t;&t;&t;/* Strip input chars to 7 bits */
DECL|macro|COR5_LNE
mdefine_line|#define&t;COR5_LNE&t;&t;0x40&t;&t;&t;/* Enable LNEXT processing */
DECL|macro|COR5_CMOE
mdefine_line|#define&t;COR5_CMOE&t;&t;0x20&t;&t;&t;/* Match good &amp; error characters */
DECL|macro|COR5_TAB3
mdefine_line|#define&t;COR5_TAB3&t;&t;0x10&t;&t;&t;/* TAB3 mode */
DECL|macro|COR5_TSTATE_ON
mdefine_line|#define&t;COR5_TSTATE_ON&t;&t;0x08&t;&t;&t;/* Enable tbusy/tstop monitoring */
DECL|macro|COR5_TSTATE_OFF
mdefine_line|#define&t;COR5_TSTATE_OFF&t;&t;0x04&t;&t;&t;/* Disable tbusy/tstop monitoring */
DECL|macro|COR5_ONLCR
mdefine_line|#define&t;COR5_ONLCR&t;&t;0x02&t;&t;&t;/* NL -&gt; CR NL on output */
DECL|macro|COR5_OCRNL
mdefine_line|#define&t;COR5_OCRNL&t;&t;0x01&t;&t;&t;/* CR -&gt; NL on output */
multiline_comment|/* RxBaud and TxBaud definitions... */
DECL|macro|RIO_B0
mdefine_line|#define&t;RIO_B0&t;&t;&t;0x00&t;&t;&t;/* RTS / DTR signals dropped */
DECL|macro|RIO_B50
mdefine_line|#define&t;RIO_B50&t;&t;&t;0x01&t;&t;&t;/* 50 baud */
DECL|macro|RIO_B75
mdefine_line|#define&t;RIO_B75&t;&t;&t;0x02&t;&t;&t;/* 75 baud */
DECL|macro|RIO_B110
mdefine_line|#define&t;RIO_B110&t;&t;0x03&t;&t;&t;/* 110 baud */
DECL|macro|RIO_B134
mdefine_line|#define&t;RIO_B134&t;&t;0x04&t;&t;&t;/* 134.5 baud */
DECL|macro|RIO_B150
mdefine_line|#define&t;RIO_B150&t;&t;0x05&t;&t;&t;/* 150 baud */
DECL|macro|RIO_B200
mdefine_line|#define&t;RIO_B200&t;&t;0x06&t;&t;&t;/* 200 baud */
DECL|macro|RIO_B300
mdefine_line|#define&t;RIO_B300&t;&t;0x07&t;&t;&t;/* 300 baud */
DECL|macro|RIO_B600
mdefine_line|#define&t;RIO_B600&t;&t;0x08&t;&t;&t;/* 600 baud */
DECL|macro|RIO_B1200
mdefine_line|#define&t;RIO_B1200&t;&t;0x09&t;&t;&t;/* 1200 baud */
DECL|macro|RIO_B1800
mdefine_line|#define&t;RIO_B1800&t;&t;0x0A&t;&t;&t;/* 1800 baud */
DECL|macro|RIO_B2400
mdefine_line|#define&t;RIO_B2400&t;&t;0x0B&t;&t;&t;/* 2400 baud */
DECL|macro|RIO_B4800
mdefine_line|#define&t;RIO_B4800&t;&t;0x0C&t;&t;&t;/* 4800 baud */
DECL|macro|RIO_B9600
mdefine_line|#define&t;RIO_B9600&t;&t;0x0D&t;&t;&t;/* 9600 baud */
DECL|macro|RIO_B19200
mdefine_line|#define&t;RIO_B19200&t;&t;0x0E&t;&t;&t;/* 19200 baud */
DECL|macro|RIO_B38400
mdefine_line|#define&t;RIO_B38400&t;&t;0x0F&t;&t;&t;/* 38400 baud */
DECL|macro|RIO_B56000
mdefine_line|#define&t;RIO_B56000&t;&t;0x10&t;&t;&t;/* 56000 baud */
DECL|macro|RIO_B57600
mdefine_line|#define&t;RIO_B57600&t;&t;0x11&t;&t;&t;/* 57600 baud */
DECL|macro|RIO_B64000
mdefine_line|#define&t;RIO_B64000&t;&t;0x12&t;&t;&t;/* 64000 baud */
DECL|macro|RIO_B115200
mdefine_line|#define&t;RIO_B115200&t;&t;0x13&t;&t;&t;/* 115200 baud */
DECL|macro|RIO_B2000
mdefine_line|#define&t;RIO_B2000&t;&t;0x14&t;&t;&t;/* 2000 baud */
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   CONFIG   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   CONFIG is sent from the driver to configure an already opened port.&n;   Packet structure is same as OPEN.  */
multiline_comment|/*****************************************************************************&n;*********************************           **********************************&n;*********************************   MOPEN   **********************************&n;*********************************           **********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   MOPEN is sent from the driver to open a port attached to a modem. (in-band)&n;   Packet structure is same as OPEN.  */
multiline_comment|/*****************************************************************************&n;*********************************           **********************************&n;*********************************   CLOSE   **********************************&n;*********************************           **********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   CLOSE is sent from the driver to close a previously opened port.&n;   No parameters.&n; */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   WFLUSH   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   WFLUSH is sent pre-emptively from the driver to flush the write buffers and&n;   packets of a port.  (pre-emptive)&n;   &n;   WFLUSH is also sent in-band from the driver to a port as a marker to end&n;   write flushing previously started by a pre-emptive WFLUSH packet. (in-band)&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_PhbNum
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   RFLUSH   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   RFLUSH is sent pre-emptively from the driver to flush the read buffers and&n;   packets of a port.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   RESUME   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   RESUME is sent pre-emptively from the driver to cause a port to resume &n;   transmission of data if blocked by XOFF.  (as if XON had been received)&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   SBREAK   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   SBREAK is sent in-band from the driver to a port to suspend data and start&n;   break signal transmission.&n;&n;   If the break delay is 0, the break signal will be acknowledged with a&n;   RUP_COMMAND, COMPLETE packet and continue until an EBREAK packet is received.&n;&n;   Otherwise, there is no acknowledgement and the break signal will last for the&n;   specified number of mS.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_BreakDelay
mdefine_line|#define&t;PKT_BreakDelay&t;&t;(PKT_Data+1)&t;&t;/* Break delay in mS */
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   EBREAK   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   EBREAK is sent in-band from the driver to a port to stop transmission of a&n;   break signal.&n;&n;   No parameters.  */
multiline_comment|/*****************************************************************************&n;*********************************             ********************************&n;*********************************   SUSPEND   ********************************&n;*********************************             ********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   SUSPEND is sent pre-emptively from the driver to cause a port to suspend&n;   transmission of data.  (as if XOFF had been received)&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   FCLOSE   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   FCLOSE is sent pre-emptively from the driver to force close a port.&n;   A force close flushes receive and transmit queues, and also lowers all output&n;   modem signals if the COR5_HUPCL (Hang Up On Close) flag is set.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   XPRINT   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   XPRINT is sent as a normal I/O data packet except that the PKT_CMD_BIT of&n;   the &quot;len&quot; field is set, and the first &quot;data&quot; byte is XPRINT.&n;&n;   The I/O data in the XPRINT packet will contain the following:&n;   -&t;Transparent Print Start Sequence&n;   -&t;Transparent Print Data&n;   -&t;Transparent Print Stop Sequence.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;**********************************          **********************************&n;**********************************   MBIS   **********************************&n;**********************************          **********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   MBIS is sent pre-emptively from the driver to set a port&squot;s modem signals.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
DECL|macro|PKT_ModemSet
mdefine_line|#define&t;PKT_ModemSet&t;&t;(PKT_Data+4)&t;&t;/* Modem set signals mask */
multiline_comment|/* ModemSet definitions... */
DECL|macro|MBIS_RTS
mdefine_line|#define&t;MBIS_RTS&t;&t;0x01&t;&t;&t;/* RTS modem signal */
DECL|macro|MBIS_DTR
mdefine_line|#define&t;MBIS_DTR&t;&t;0x02&t;&t;&t;/* DTR modem signal */
multiline_comment|/*****************************************************************************&n;**********************************          **********************************&n;**********************************   MBIC   **********************************&n;**********************************          **********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   MBIC is sent pre-emptively from the driver to clear a port&squot;s modem signals.&n;   */
macro_line|#if 0   
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
DECL|macro|PKT_ModemClear
mdefine_line|#define&t;PKT_ModemClear&t;&t;(PKT_Data+4)&t;&t;/* Modem clear signals mask */
multiline_comment|/* ModemClear definitions... */
DECL|macro|MBIC_RTS
mdefine_line|#define&t;MBIC_RTS&t;&t;0x01&t;&t;&t;/* RTS modem signal */
DECL|macro|MBIC_DTR
mdefine_line|#define&t;MBIC_DTR&t;&t;0x02&t;&t;&t;/* DTR modem signal */
multiline_comment|/*****************************************************************************&n;**********************************          **********************************&n;**********************************   MSET   **********************************&n;**********************************          **********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   MSET is sent pre-emptively from the driver to set/clear a port&squot;s modem signals. */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
macro_line|#endif
DECL|macro|PKT_ModemSet
mdefine_line|#define&t;PKT_ModemSet&t;&t;(PKT_Data+4)&t;&t;/* Modem set signals mask */
multiline_comment|/* ModemSet definitions... */
DECL|macro|MSET_RTS
mdefine_line|#define&t;MSET_RTS&t;&t;0x01&t;&t;&t;/* RTS modem signal */
DECL|macro|MSET_DTR
mdefine_line|#define&t;MSET_DTR&t;&t;0x02&t;&t;&t;/* DTR modem signal */
multiline_comment|/*****************************************************************************&n;*********************************            *********************************&n;*********************************   PCLOSE   *********************************&n;*********************************            *********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,in-band)&n;&n;   PCLOSE is sent from the driver to pseudo close a previously opened port.&n;   &n;   The port will close when all data has been sent/received, however, the&n;   port&squot;s transmit / receive and modem signals will be left enabled and the&n;   port marked internally as Pseudo Closed. */
DECL|macro|PKT_Cmd
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
multiline_comment|/*****************************************************************************&n;**********************************          **********************************&n;**********************************   MGET   **********************************&n;**********************************          **********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   MGET is sent pre-emptively from the driver to request the port&squot;s current modem signals. */
DECL|macro|PKT_Cmd
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
DECL|macro|PKT_PhbNum
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
multiline_comment|/*****************************************************************************&n;*********************************             ********************************&n;*********************************   MEMDUMP   ********************************&n;*********************************             ********************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   MEMDUMP is sent pre-emptively from the driver to request a dump of 32 bytes&n;   of the specified port&squot;s RTA address space.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_PhbNum
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
DECL|macro|PKT_SubCmd
mdefine_line|#define&t;PKT_SubCmd&t;&t;(PKT_Data+5)&t;&t;/* Sub Command */
DECL|macro|PKT_Address
mdefine_line|#define&t;PKT_Address&t;&t;(PKT_Data+6)&t;&t;/* Requested address */
multiline_comment|/*****************************************************************************&n;******************************                   *****************************&n;******************************   READ_REGISTER   *****************************&n;******************************                   *****************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   READ_REGISTER is sent pre-emptively from the driver to request the contents&n;   of the CD1400 register specified in address.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_PhbNum
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
DECL|macro|PKT_SubCmd
mdefine_line|#define&t;PKT_SubCmd&t;&t;(PKT_Data+5)&t;&t;/* Sub Command */
DECL|macro|PKT_Address
mdefine_line|#define&t;PKT_Address&t;&t;(PKT_Data+6)&t;&t;/* Requested address */
multiline_comment|/*****************************************************************************&n;************************                            **************************&n;************************   COMMAND_RUP - COMPLETE   **************************&n;************************                            **************************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   COMMAND_RUP - COMPLETE is sent in response to all port I/O control command&n;   packets, except MEMDUMP and READ_REGISTER.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_PhbNum
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
DECL|macro|PKT_Cmd2
mdefine_line|#define&t;PKT_Cmd2&t;&t;(PKT_Data+2)&t;&t;/* Command code copy */
DECL|macro|PKT_ModemStatus
mdefine_line|#define&t;PKT_ModemStatus&t;&t;(PKT_Data+3)&t;&t;/* Modem signal status */
DECL|macro|PKT_PortStatus
mdefine_line|#define&t;PKT_PortStatus&t;&t;(PKT_Data+4)&t;&t;/* Port signal status */
DECL|macro|PKT_SubCmd
mdefine_line|#define&t;PKT_SubCmd&t;&t;(PKT_Data+5)&t;&t;/* Sub Command */
multiline_comment|/* ModemStatus definitions... */
DECL|macro|MODEM_DSR
mdefine_line|#define&t;MODEM_DSR&t;&t;0x80&t;&t;&t;/* Data Set Ready modem state */
DECL|macro|MODEM_CTS
mdefine_line|#define&t;MODEM_CTS&t;&t;0x40&t;&t;&t;/* Clear To Send modem state */
DECL|macro|MODEM_RI
mdefine_line|#define&t;MODEM_RI&t;&t;0x20&t;&t;&t;/* Ring Indicate modem state */
DECL|macro|MODEM_CD
mdefine_line|#define&t;MODEM_CD&t;&t;0x10&t;&t;&t;/* Carrier Detect modem state */
DECL|macro|MODEM_TSTOP
mdefine_line|#define&t;MODEM_TSTOP&t;&t;0x08&t;&t;&t;/* Transmit Stopped state */
DECL|macro|MODEM_TEMPTY
mdefine_line|#define&t;MODEM_TEMPTY&t;&t;0x04&t;&t;&t;/* Transmit Empty state */
DECL|macro|MODEM_DTR
mdefine_line|#define&t;MODEM_DTR&t;&t;0x02&t;&t;&t;/* DTR modem output state */
DECL|macro|MODEM_RTS
mdefine_line|#define&t;MODEM_RTS&t;&t;0x01&t;&t;&t;/* RTS modem output state */
multiline_comment|/* PortStatus definitions... */
DECL|macro|PORT_ISOPEN
mdefine_line|#define&t;PORT_ISOPEN&t;&t;0x01&t;&t;&t;/* Port open ? */
DECL|macro|PORT_HUPCL
mdefine_line|#define&t;PORT_HUPCL&t;&t;0x02&t;&t;&t;/* Hangup on close? */
DECL|macro|PORT_MOPENPEND
mdefine_line|#define&t;PORT_MOPENPEND&t;&t;0x04&t;&t;&t;/* Modem open pending */
DECL|macro|PORT_ISPARALLEL
mdefine_line|#define&t;PORT_ISPARALLEL&t;&t;0x08&t;&t;&t;/* Parallel port */
DECL|macro|PORT_BREAK
mdefine_line|#define&t;PORT_BREAK&t;&t;0x10&t;&t;&t;/* Port on break */
DECL|macro|PORT_STATUSPEND
mdefine_line|#define&t;PORT_STATUSPEND&t;&t;0020&t;&t;&t;/* Status packet pending */
DECL|macro|PORT_BREAKPEND
mdefine_line|#define&t;PORT_BREAKPEND&t;&t;0x40&t;&t;&t;/* Break packet pending */
DECL|macro|PORT_MODEMPEND
mdefine_line|#define&t;PORT_MODEMPEND&t;&t;0x80&t;&t;&t;/* Modem status packet pending */
multiline_comment|/*****************************************************************************&n;************************                            **************************&n;************************   COMMAND_RUP - COMPLETE   **************************&n;************************                            **************************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   COMMAND_RUP - COMPLETE is sent in response to all port I/O control command&n;   packets, except MEMDUMP and READ_REGISTER.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
mdefine_line|#define&t;PKT_Cmd2&t;&t;(PKT_Data+2)&t;&t;/* Command code copy */
macro_line|#endif
DECL|macro|PKT_ModemStatus
mdefine_line|#define&t;PKT_ModemStatus&t;&t;(PKT_Data+3)&t;&t;/* Modem signal status */
DECL|macro|PKT_PortStatus
mdefine_line|#define&t;PKT_PortStatus&t;&t;(PKT_Data+4)&t;&t;/* Port signal status */
macro_line|#if 0
mdefine_line|#define&t;PKT_SubCmd&t;&t;(PKT_Data+5)&t;&t;/* Sub Command */
macro_line|#endif
multiline_comment|/* ModemStatus definitions... */
DECL|macro|MODEM_DSR
mdefine_line|#define&t;MODEM_DSR&t;&t;0x80&t;&t;&t;/* Data Set Ready modem state */
DECL|macro|MODEM_CTS
mdefine_line|#define&t;MODEM_CTS&t;&t;0x40&t;&t;&t;/* Clear To Send modem state */
DECL|macro|MODEM_RI
mdefine_line|#define&t;MODEM_RI&t;&t;0x20&t;&t;&t;/* Ring Indicate modem state */
DECL|macro|MODEM_CD
mdefine_line|#define&t;MODEM_CD&t;&t;0x10&t;&t;&t;/* Carrier Detect modem state */
DECL|macro|MODEM_TSTOP
mdefine_line|#define&t;MODEM_TSTOP&t;&t;0x08&t;&t;&t;/* Transmit Stopped state */
DECL|macro|MODEM_TEMPTY
mdefine_line|#define&t;MODEM_TEMPTY&t;&t;0x04&t;&t;&t;/* Transmit Empty state */
DECL|macro|MODEM_DTR
mdefine_line|#define&t;MODEM_DTR&t;&t;0x02&t;&t;&t;/* DTR modem output state */
DECL|macro|MODEM_RTS
mdefine_line|#define&t;MODEM_RTS&t;&t;0x01&t;&t;&t;/* RTS modem output state */
multiline_comment|/* PortStatus definitions... */
DECL|macro|PORT_ISOPEN
mdefine_line|#define&t;PORT_ISOPEN&t;&t;0x01&t;&t;&t;/* Port open ? */
DECL|macro|PORT_HUPCL
mdefine_line|#define&t;PORT_HUPCL&t;&t;0x02&t;&t;&t;/* Hangup on close? */
DECL|macro|PORT_MOPENPEND
mdefine_line|#define&t;PORT_MOPENPEND&t;&t;0x04&t;&t;&t;/* Modem open pending */
DECL|macro|PORT_ISPARALLEL
mdefine_line|#define&t;PORT_ISPARALLEL&t;&t;0x08&t;&t;&t;/* Parallel port */
DECL|macro|PORT_BREAK
mdefine_line|#define&t;PORT_BREAK&t;&t;0x10&t;&t;&t;/* Port on break */
DECL|macro|PORT_STATUSPEND
mdefine_line|#define&t;PORT_STATUSPEND&t;&t;0020&t;&t;&t;/* Status packet pending */
DECL|macro|PORT_BREAKPEND
mdefine_line|#define&t;PORT_BREAKPEND&t;&t;0x40&t;&t;&t;/* Break packet pending */
DECL|macro|PORT_MODEMPEND
mdefine_line|#define&t;PORT_MODEMPEND&t;&t;0x80&t;&t;&t;/* Modem status packet pending */
multiline_comment|/*****************************************************************************&n;********************                                      ********************&n;********************   COMMAND_RUP - COMPLETE - MEMDUMP   ********************&n;********************                                      ********************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   COMMAND_RUP - COMPLETE - MEMDUMP is sent as an acknowledgement for a MEMDUMP&n;   port I/O control command packet.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
mdefine_line|#define&t;PKT_Cmd2&t;&t;(PKT_Data+2)&t;&t;/* Command code copy */
mdefine_line|#define&t;PKT_ModemStatus&t;&t;(PKT_Data+3)&t;&t;/* Modem signal status */
mdefine_line|#define&t;PKT_PortStatus&t;&t;(PKT_Data+4)&t;&t;/* Port signal status */
mdefine_line|#define&t;PKT_SubCmd&t;&t;(PKT_Data+5)&t;&t;/* Sub Command */
mdefine_line|#define&t;PKT_Address&t;&t;(PKT_Data+6)&t;&t;/* Requested address */
macro_line|#endif
DECL|macro|PKT_Dump
mdefine_line|#define&t;PKT_Dump&t;&t;(PKT_Data+8)&t;&t;/* 32bytes of requested dump data */
multiline_comment|/*****************************************************************************&n;*****************                                            *****************&n;*****************   COMMAND_RUP - COMPLETE - READ_REGISTER   *****************&n;*****************                                            *****************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   COMMAND_RUP - COMPLETE - READ_REGISTER is sent as an acknowledgement for a&n;   READ_REGISTER port I/O control command packet.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/*Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/*Port number wrt RTA */
mdefine_line|#define&t;PKT_Cmd2&t;&t;(PKT_Data+2)&t;&t;/* Command code copy */
macro_line|#endif
DECL|macro|PKT_RegisterValue
mdefine_line|#define&t;PKT_RegisterValue&t;(PKT_Data+3)&t;&t;/* Modem signal status */
macro_line|#if 0
mdefine_line|#define&t;PKT_PortStatus&t;&t;(PKT_Data+4)&t;&t;/* Port signal status */
mdefine_line|#define&t;PKT_SubCmd&t;&t;(PKT_Data+5)&t;&t;/* Sub Command */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*********************                                  ***********************&n;*********************   COMMAND_RUP - BREAK_RECEIVED   ***********************&n;*********************                                  ***********************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   COMMAND_RUP - BREAK_RECEIVED packets are sent when the port detects a receive BREAK signal.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
mdefine_line|#define&t;PKT_Cmd2&t;&t;(PKT_Data+2)&t;&t;/* Command code copy */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;*********************                                *************************&n;*********************   COMMAND_RUP - MODEM_STATUS   *************************&n;*********************                                *************************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   COMMAND_RUP - MODEM_STATUS packets are sent whenever the port detects a&n;   change in the input modem signal states.&n;&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_PhbNum&t;&t;(PKT_Data+1)&t;&t;/* Port number wrt RTA */
mdefine_line|#define&t;PKT_Cmd2&t;&t;(PKT_Data+2)&t;&t;/* Command code copy */
mdefine_line|#define&t;PKT_ModemStatus&t;&t;(PKT_Data+3)&t;&t;/* Modem signal status */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;************************                             *************************&n;************************   BOOT_RUP - BOOT_REQUEST   *************************&n;************************                             *************************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   BOOT_RUP - BOOT_REQUEST packets are sent to the Driver from RIO to request&n;   firmware code to load onto attached RTAs.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
multiline_comment|/*****************************************************************************&n;************************                              ************************&n;************************   BOOT_RUP - BOOT_SEQUENCE   ************************&n;************************                              ************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   BOOT_RUP - BOOT_SEQUENCE packets are sent from the Driver to RIO in response&n;   to a BOOT_RUP - BOOT_REQUEST packet.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_NumPackets
mdefine_line|#define&t;PKT_NumPackets&t;&t;(PKT_Data+2)&t;&t;/* Packets required to load firmware */
DECL|macro|PKT_LoadBase
mdefine_line|#define&t;PKT_LoadBase&t;&t;(PKT_Data+4)&t;&t;/* RTA firmware load address */
DECL|macro|PKT_CodeSize
mdefine_line|#define&t;PKT_CodeSize&t;&t;(PKT_Data+6)&t;&t;/* Size of firmware in bytes */
DECL|macro|PKT_CmdString
mdefine_line|#define&t;PKT_CmdString&t;&t;(PKT_Data+8)&t;&t;/* Command string */
multiline_comment|/*****************************************************************************&n;************************                               ***********************&n;************************   BOOT_RUP - BOOT_COMPLETED   ***********************&n;************************                               ***********************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   BOOT_RUP - BOOT_COMPLETE is sent to the Driver from RIO when downloading of&n;   RTA firmware has completed.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_LinkNumber
mdefine_line|#define&t;PKT_LinkNumber&t;&t;(PKT_Data+1)&t;&t;/* Link number RTA booted on */
DECL|macro|PKT_SerialNumber
mdefine_line|#define&t;PKT_SerialNumber&t;(PKT_Data+2)&t;&t;/* 4 byte serial number */
multiline_comment|/*****************************************************************************&n;************************                               ***********************&n;************************   BOOT_RUP - Packet Request   ***********************&n;************************                               ***********************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   BOOT_RUP packet without the PKT_CMD_BIT set in the PKT-&gt;len field is sent&n;   from RIO to the Driver as a request for a firmware boot packet. */
DECL|macro|PKT_SequenceNumber
mdefine_line|#define&t;PKT_SequenceNumber&t;(PKT_Data+0)&t;&t;/* Packet sequence number */
multiline_comment|/*****************************************************************************&n;***********************                                ***********************&n;***********************   BOOT_RUP - Packet Response   ***********************&n;***********************                                ***********************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   In response to a BOOT_RUP boot packet request, the driver fills out the response&n;   packet with the 70 bytes of the requested sequence.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_SequenceNumber&t;(PKT_Data+0)&t;&t;/* Packet sequence number */
macro_line|#endif
DECL|macro|PKT_FirmwarePacket
mdefine_line|#define&t;PKT_FirmwarePacket&t;(PKT_Data+2)&t;&t;/* Firmware packet */
multiline_comment|/*****************************************************************************&n;****************************                      ****************************&n;****************************   BOOT_RUP - IFOAD   ****************************&n;****************************                      ****************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   BOOT_RUP - IFOAD packets are sent from the Driver to an RTA to cause the&n;   RTA to shut down and reboot.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_IfoadId1
mdefine_line|#define&t;PKT_IfoadId1&t;&t;(PKT_Data+2)&t;&t;/* IFOAD Id 1 */
DECL|macro|PKT_IfoadId2
mdefine_line|#define&t;PKT_IfoadId2&t;&t;(PKT_Data+3)&t;&t;/* IFOAD Id 2 */
DECL|macro|IFOADID1
mdefine_line|#define&t;IFOADID1&t;&t;0xAD
DECL|macro|IFOADID2
mdefine_line|#define&t;IFOADID2&t;&t;0xF0
multiline_comment|/*****************************************************************************&n;**************************                         ***************************&n;**************************   BOOT_RUP - IDENTIFY   ***************************&n;**************************                         ***************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   BOOT_RUP - IDENTIFY packets are sent from the Driver to an RTA to cause the&n;   RTA to flash its LEDs for a period of time.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_IdentifyId
mdefine_line|#define&t;PKT_IdentifyId&t;&t;(PKT_Data+2)&t;&t;/* defines pattern to flash */
multiline_comment|/*****************************************************************************&n;****************************                       ***************************&n;****************************   BOOT_RUP - ZOMBIE   ***************************&n;****************************                       ***************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   BOOT_RUP - ZOMBIE packets are sent from the Driver to an RTA to cause the&n;   RTA to shut down and flash it&squot;s LEDs.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_ZombieId1
mdefine_line|#define&t;PKT_ZombieId1&t;&t;(PKT_Data+2)&t;&t;/* ZOMBIE Id 1 */
DECL|macro|PKT_ZombieId2
mdefine_line|#define&t;PKT_ZombieId2&t;&t;(PKT_Data+3)&t;&t;/* ZOMBIE Id 2 */
DECL|macro|ZOMBIEID1
mdefine_line|#define&t;ZOMBIEID1&t;&t;0x52
DECL|macro|ZOMBIEID2
mdefine_line|#define&t;ZOMBIEID2&t;&t;0x21
multiline_comment|/*****************************************************************************&n;****************************                      ****************************&n;****************************   BOOT_RUP - UFOAD   ****************************&n;****************************                      ****************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   BOOT_RUP - UFOAD packets are sent from the Driver to an RTA to cause the RTA&n;   to ask it&squot;s neighbouring RTA to shut down and reboot.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_LinkNumber&t;&t;(PKT_Data+1)&t;&t;/* Link number of RTA to UFOAD */
macro_line|#endif
DECL|macro|PKT_UfoadId1
mdefine_line|#define&t;PKT_UfoadId1&t;&t;(PKT_Data+2)&t;&t;/* UFOAD Id 1 */
DECL|macro|PKT_UfoadId2
mdefine_line|#define&t;PKT_UfoadId2&t;&t;(PKT_Data+3)&t;&t;/* UFOAD Id 2 */
DECL|macro|UFOADID1
mdefine_line|#define&t;UFOADID1&t;&t;0x1E
DECL|macro|UFOADID2
mdefine_line|#define&t;UFOADID2&t;&t;0x0D
multiline_comment|/*****************************************************************************&n;****************************                      ****************************&n;****************************   BOOT_RUP - IWAIT   ****************************&n;****************************                      ****************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   BOOT_RUP - IWAIT packets are sent from the Driver to an RTA to cause the RTA&n;   to pause booting on the specified link for 30 seconds.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
mdefine_line|#define&t;PKT_LinkNumber&t;&t;(PKT_Data+1)&t;&t;/* Link number of RTA to UFOAD */
macro_line|#endif
DECL|macro|PKT_IwaitId1
mdefine_line|#define&t;PKT_IwaitId1&t;&t;(PKT_Data+2)&t;&t;/* IWAIT Id 1 */
DECL|macro|PKT_IwaitId2
mdefine_line|#define&t;PKT_IwaitId2&t;&t;(PKT_Data+3)&t;&t;/* IWAIT Id 2 */
DECL|macro|IWAITID1
mdefine_line|#define&t;IWAITID1&t;&t;0xDE
DECL|macro|IWAITID2
mdefine_line|#define&t;IWAITID2&t;&t;0xB1
multiline_comment|/*****************************************************************************&n;************************                               ***********************&n;************************   ROUTE_RUP - ROUTE_REQUEST   ***********************&n;************************                               ***********************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   ROUTE_RUP - ROUTE_REQUEST packets are sent from a newly booted or connected&n;   RTA to a Driver to request an ID (RUP or unit number).&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_SerialNumber
mdefine_line|#define&t;PKT_SerialNumber&t;(PKT_Data+2)&t;&t;/* 4 byte serial number */
DECL|macro|PKT_ModuleTypes
mdefine_line|#define&t;PKT_ModuleTypes&t;&t;(PKT_Data+6)&t;&t;/* RTA Module types */
multiline_comment|/* ModuleTypes definitions... */
DECL|macro|MOD_BLANK
mdefine_line|#define&t;MOD_BLANK&t;&t;0x0F&t;&t;&t;/* Blank plate attached */
DECL|macro|MOD_RS232DB25
mdefine_line|#define&t;MOD_RS232DB25&t;&t;0x00&t;&t;&t;/* RS232 DB25 connector */
DECL|macro|MOD_RS232RJ45
mdefine_line|#define&t;MOD_RS232RJ45&t;&t;0x01&t;&t;&t;/* RS232 RJ45 connector */
DECL|macro|MOD_RS422DB25
mdefine_line|#define&t;MOD_RS422DB25&t;&t;0x02&t;&t;&t;/* RS422 DB25 connector */
DECL|macro|MOD_RS485DB25
mdefine_line|#define&t;MOD_RS485DB25&t;&t;0x03&t;&t;&t;/* RS485 DB25 connector */
DECL|macro|MOD_PARALLEL
mdefine_line|#define&t;MOD_PARALLEL&t;&t;0x04&t;&t;&t;/* Centronics parallel */
DECL|macro|MOD2
mdefine_line|#define&t;MOD2&t;&t;&t;0x08&t;&t;&t;/* Set to indicate Rev2 module */
multiline_comment|/*****************************************************************************&n;*************************                            *************************&n;*************************   ROUTE_RUP - ROUTE_FOAD   *************************&n;*************************                            *************************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   ROUTE_RUP - ROUTE_FOAD packet is sent as a response to a ROUTE_RUP - ROUTE_REQUEST&n;   packet to cause the RTA to &quot;Fall Over And Die&quot;., i.e. shutdown and reboot.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_RouteCmdString
mdefine_line|#define&t;PKT_RouteCmdString&t;(PKT_Data+2)&t;&t;/* Command string */
multiline_comment|/*****************************************************************************&n;***********************                                ***********************&n;***********************   ROUTE_RUP - ROUTE_ALLOCATE   ***********************&n;***********************                                ***********************&n;*****************************************************************************/
multiline_comment|/* (Driver-&gt;RIO,pre-emptive)&n;&n;   ROUTE_RUP - ROUTE_ALLOCATE packet is sent as a response to a ROUTE_RUP - ROUTE_REQUEST&n;   packet to allocate the RTA&squot;s Id number (RUP number 1..16)&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_IdNum
mdefine_line|#define&t;PKT_IdNum&t;&t;(PKT_Data+1)&t;&t;/* RUP number for ports 1..8 */
macro_line|#if 0
mdefine_line|#define&t;PKT_RouteCmdString&t;(PKT_Data+2)&t;&t;/* Command string */
macro_line|#endif
DECL|macro|PKT_IdNum2
mdefine_line|#define&t;PKT_IdNum2&t;&t;(PKT_Data+0x17)&t;&t;/* RUP number for ports 9..16 */
multiline_comment|/*****************************************************************************&n;***********************                                ***********************&n;***********************   ROUTE_RUP - ROUTE_TOPOLOGY   ***********************&n;***********************                                ***********************&n;*****************************************************************************/
multiline_comment|/* (RIO-&gt;Driver,pre-emptive)&n;&n;   ROUTE_RUP - ROUTE_TOPOLOGY packet is sent to inform the driver of an RTA&squot;s&n;   current link status.&n;   */
macro_line|#if 0
mdefine_line|#define&t;PKT_Cmd&t;&t;&t;(PKT_Data+0)&t;&t;/* Command code */
macro_line|#endif
DECL|macro|PKT_Link1Rup
mdefine_line|#define&t;PKT_Link1Rup&t;&t;(PKT_Data+2)&t;&t;/* Link 1 RUP number */
DECL|macro|PKT_Link1Link
mdefine_line|#define&t;PKT_Link1Link&t;&t;(PKT_Data+3)&t;&t;/* Link 1 link number */
DECL|macro|PKT_Link2Rup
mdefine_line|#define&t;PKT_Link2Rup&t;&t;(PKT_Data+4)&t;&t;/* Link 2 RUP number */
DECL|macro|PKT_Link2Link
mdefine_line|#define&t;PKT_Link2Link&t;&t;(PKT_Data+5)&t;&t;/* Link 2 link number */
DECL|macro|PKT_Link3Rup
mdefine_line|#define&t;PKT_Link3Rup&t;&t;(PKT_Data+6)&t;&t;/* Link 3 RUP number */
DECL|macro|PKT_Link3Link
mdefine_line|#define&t;PKT_Link3Link&t;&t;(PKT_Data+7)&t;&t;/* Link 3 link number */
DECL|macro|PKT_Link4Rup
mdefine_line|#define&t;PKT_Link4Rup&t;&t;(PKT_Data+8)&t;&t;/* Link 4 RUP number */
DECL|macro|PKT_Link4Link
mdefine_line|#define&t;PKT_Link4Link&t;&t;(PKT_Data+9)&t;&t;/* Link 4 link number */
DECL|macro|PKT_RtaVpdProm
mdefine_line|#define&t;PKT_RtaVpdProm&t;&t;(PKT_Data+10)&t;&t;/* 32 bytes of RTA VPD PROM Contents */
macro_line|#endif&t;&t;&t;&t;&t;&t;/* _sxwinif_h */
multiline_comment|/* End of RIOWINIF.H */
eof
