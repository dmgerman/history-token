multiline_comment|/* &n;   BlueCore Serial Protocol (BCSP) for Linux Bluetooth stack (BlueZ).&n;   Copyright 2002 by Fabrizio Gennari &lt;fabrizio.gennari@philips.com&gt;&n;&n;   Based on&n;       hci_h4.c  by Maxim Krasnyansky &lt;maxk@qualcomm.com&gt;&n;       ABCSP     by Carl Orsborn &lt;cjo@csr.com&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License version 2 as&n;   published by the Free Software Foundation;&n;&n;   THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS&n;   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n;   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.&n;   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY&n;   CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES &n;   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN &n;   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF &n;   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.&n;&n;   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS, &n;   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS &n;   SOFTWARE IS DISCLAIMED.&n;*/
multiline_comment|/* &n; * $Id: hci_bcsp.h,v 1.2 2002/09/26 05:05:14 maxk Exp $&n; */
macro_line|#ifndef __HCI_BCSP_H__
DECL|macro|__HCI_BCSP_H__
mdefine_line|#define __HCI_BCSP_H__
DECL|macro|BCSP_TXWINSIZE
mdefine_line|#define BCSP_TXWINSIZE  4
DECL|macro|BCSP_ACK_PKT
mdefine_line|#define BCSP_ACK_PKT    0x05
DECL|macro|BCSP_LE_PKT
mdefine_line|#define BCSP_LE_PKT     0x06
DECL|struct|bcsp_struct
r_struct
id|bcsp_struct
(brace
DECL|member|unack
r_struct
id|sk_buff_head
id|unack
suffix:semicolon
multiline_comment|/* Unack&squot;ed packets queue */
DECL|member|rel
r_struct
id|sk_buff_head
id|rel
suffix:semicolon
multiline_comment|/* Reliable packets queue */
DECL|member|unrel
r_struct
id|sk_buff_head
id|unrel
suffix:semicolon
multiline_comment|/* Unreliable packets queue */
DECL|member|rx_count
r_int
r_int
id|rx_count
suffix:semicolon
DECL|member|rx_skb
r_struct
id|sk_buff
op_star
id|rx_skb
suffix:semicolon
DECL|member|rxseq_txack
id|u8
id|rxseq_txack
suffix:semicolon
multiline_comment|/* rxseq == txack. */
DECL|member|rxack
id|u8
id|rxack
suffix:semicolon
multiline_comment|/* Last packet sent by us that the peer ack&squot;ed */
DECL|member|tbcsp
r_struct
id|timer_list
id|tbcsp
suffix:semicolon
r_enum
(brace
DECL|enumerator|BCSP_W4_PKT_DELIMITER
id|BCSP_W4_PKT_DELIMITER
comma
DECL|enumerator|BCSP_W4_PKT_START
id|BCSP_W4_PKT_START
comma
DECL|enumerator|BCSP_W4_BCSP_HDR
id|BCSP_W4_BCSP_HDR
comma
DECL|enumerator|BCSP_W4_DATA
id|BCSP_W4_DATA
comma
DECL|enumerator|BCSP_W4_CRC
id|BCSP_W4_CRC
DECL|member|rx_state
)brace
id|rx_state
suffix:semicolon
r_enum
(brace
DECL|enumerator|BCSP_ESCSTATE_NOESC
id|BCSP_ESCSTATE_NOESC
comma
DECL|enumerator|BCSP_ESCSTATE_ESC
id|BCSP_ESCSTATE_ESC
DECL|member|rx_esc_state
)brace
id|rx_esc_state
suffix:semicolon
DECL|member|message_crc
id|u16
id|message_crc
suffix:semicolon
DECL|member|txack_req
id|u8
id|txack_req
suffix:semicolon
multiline_comment|/* Do we need to send ack&squot;s to the peer? */
multiline_comment|/* Reliable packet sequence number - used to assign seq to each rel pkt. */
DECL|member|msgq_txseq
id|u8
id|msgq_txseq
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif&t;/* __HCI_BCSP_H__ */
eof
