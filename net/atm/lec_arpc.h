multiline_comment|/*&n; * Lec arp cache&n; * Marko Kiiskila mkiiskila@yahoo.com&n; *&n; */
macro_line|#ifndef _LEC_ARP_H
DECL|macro|_LEC_ARP_H
mdefine_line|#define _LEC_ARP_H
macro_line|#include &lt;linux/atm.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/atmlec.h&gt;
DECL|struct|lec_arp_table
r_struct
id|lec_arp_table
(brace
DECL|member|next
r_struct
id|lec_arp_table
op_star
id|next
suffix:semicolon
multiline_comment|/* Linked entry list */
DECL|member|atm_addr
r_int
r_char
id|atm_addr
(braket
id|ATM_ESA_LEN
)braket
suffix:semicolon
multiline_comment|/* Atm address */
DECL|member|mac_addr
r_int
r_char
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* Mac address */
DECL|member|is_rdesc
r_int
id|is_rdesc
suffix:semicolon
multiline_comment|/* Mac address is a route descriptor */
DECL|member|vcc
r_struct
id|atm_vcc
op_star
id|vcc
suffix:semicolon
multiline_comment|/* Vcc this entry is attached */
DECL|member|recv_vcc
r_struct
id|atm_vcc
op_star
id|recv_vcc
suffix:semicolon
multiline_comment|/* Vcc we receive data from */
DECL|member|old_push
r_void
(paren
op_star
id|old_push
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* Push that leads to daemon */
DECL|member|old_recv_push
r_void
(paren
op_star
id|old_recv_push
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* Push that leads to daemon */
DECL|member|old_close
r_void
(paren
op_star
id|old_close
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
multiline_comment|/* We want to see when this&n;                                              * vcc gets closed */
DECL|member|last_used
r_int
r_int
id|last_used
suffix:semicolon
multiline_comment|/* For expiry */
DECL|member|timestamp
r_int
r_int
id|timestamp
suffix:semicolon
multiline_comment|/* Used for various timestamping&n;                                              * things:&n;                                              * 1. FLUSH started &n;                                              *    (status=ESI_FLUSH_PENDING)&n;                                              * 2. Counting to &n;                                              *    max_unknown_frame_time&n;                                              *    (status=ESI_ARP_PENDING||&n;                                              *     status=ESI_VC_PENDING)&n;                                              */
DECL|member|no_tries
r_int
r_char
id|no_tries
suffix:semicolon
multiline_comment|/* No of times arp retry has been &n;                                                tried */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* Status of this entry */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flags for this entry */
DECL|member|packets_flooded
r_int
r_int
id|packets_flooded
suffix:semicolon
multiline_comment|/* Data packets flooded */
DECL|member|flush_tran_id
r_int
r_int
id|flush_tran_id
suffix:semicolon
multiline_comment|/* Transaction id in flush protocol */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* Arping timer */
DECL|member|priv
r_struct
id|lec_priv
op_star
id|priv
suffix:semicolon
multiline_comment|/* Pointer back */
DECL|member|tlvs
id|u8
op_star
id|tlvs
suffix:semicolon
multiline_comment|/* LANE2: Each MAC address can have TLVs    */
DECL|member|sizeoftlvs
id|u32
id|sizeoftlvs
suffix:semicolon
multiline_comment|/* associated with it. sizeoftlvs tells the */
multiline_comment|/* the length of the tlvs array             */
DECL|member|tx_wait
r_struct
id|sk_buff_head
id|tx_wait
suffix:semicolon
multiline_comment|/* wait queue for outgoing packets    */
)brace
suffix:semicolon
DECL|struct|tlv
r_struct
id|tlv
(brace
multiline_comment|/* LANE2: Template tlv struct for accessing */
multiline_comment|/* the tlvs in the lec_arp_table-&gt;tlvs array*/
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|value
id|u8
id|value
(braket
l_int|255
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Status fields */
DECL|macro|ESI_UNKNOWN
mdefine_line|#define ESI_UNKNOWN 0       /*&n;                             * Next packet sent to this mac address&n;                             * causes ARP-request to be sent &n;                             */
DECL|macro|ESI_ARP_PENDING
mdefine_line|#define ESI_ARP_PENDING 1   /*&n;                             * There is no ATM address associated with this&n;                             * 48-bit address.  The LE-ARP protocol is in&n;                             * progress.&n;                             */
DECL|macro|ESI_VC_PENDING
mdefine_line|#define ESI_VC_PENDING 2    /*&n;                             * There is a valid ATM address associated with &n;                             * this 48-bit address but there is no VC set &n;                             * up to that ATM address.  The signaling &n;                             * protocol is in process.&n;                             */
DECL|macro|ESI_FLUSH_PENDING
mdefine_line|#define ESI_FLUSH_PENDING 4 /*&n;                             * The LEC has been notified of the FLUSH_START&n;                             * status and it is assumed that the flush &n;                             * protocol is in process.&n;                             */
DECL|macro|ESI_FORWARD_DIRECT
mdefine_line|#define ESI_FORWARD_DIRECT 5 /*&n;                              * Either the Path Switching Delay (C22) has &n;                              * elapsed or the LEC has notified the Mapping &n;                              * that the flush protocol has completed.  In &n;                              * either case, it is safe to forward packets &n;                              * to this address via the data direct VC.&n;                              */
multiline_comment|/* Flag values */
DECL|macro|LEC_REMOTE_FLAG
mdefine_line|#define LEC_REMOTE_FLAG      0x0001
DECL|macro|LEC_PERMANENT_FLAG
mdefine_line|#define LEC_PERMANENT_FLAG   0x0002
macro_line|#endif
eof
