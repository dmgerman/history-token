multiline_comment|/*&n; * Copyright(c) 1999 - 2003 Intel Corporation. All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY&n; * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n; * for more details.&n; *&n; * You should have received a copy of the GNU General Public License along&n; * with this program; if not, write to the Free Software Foundation, Inc.,&n; * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; * The full GNU General Public License is included in this distribution in the&n; * file called LICENSE.&n; */
macro_line|#ifndef __BOND_ALB_H__
DECL|macro|__BOND_ALB_H__
mdefine_line|#define __BOND_ALB_H__
macro_line|#include &lt;linux/if_ether.h&gt;
r_struct
id|bonding
suffix:semicolon
r_struct
id|slave
suffix:semicolon
DECL|macro|BOND_ALB_INFO
mdefine_line|#define BOND_ALB_INFO(bond)   ((bond)-&gt;alb_info)
DECL|macro|SLAVE_TLB_INFO
mdefine_line|#define SLAVE_TLB_INFO(slave) ((slave)-&gt;tlb_info)
DECL|struct|tlb_client_info
r_struct
id|tlb_client_info
(brace
DECL|member|tx_slave
r_struct
id|slave
op_star
id|tx_slave
suffix:semicolon
multiline_comment|/* A pointer to slave used for transmiting&n;&t;&t;&t;&t; * packets to a Client that the Hash function&n;&t;&t;&t;&t; * gave this entry index.&n;&t;&t;&t;&t; */
DECL|member|tx_bytes
id|u32
id|tx_bytes
suffix:semicolon
multiline_comment|/* Each Client acumulates the BytesTx that&n;&t;&t;&t;&t; * were tranmitted to it, and after each&n;&t;&t;&t;&t; * CallBack the LoadHistory is devided&n;&t;&t;&t;&t; * by the balance interval&n;&t;&t;&t;&t; */
DECL|member|load_history
id|u32
id|load_history
suffix:semicolon
multiline_comment|/* This field contains the amount of Bytes&n;&t;&t;&t;&t; * that were transmitted to this client by&n;&t;&t;&t;&t; * the server on the previous balance&n;&t;&t;&t;&t; * interval in Bps.&n;&t;&t;&t;&t; */
DECL|member|next
id|u32
id|next
suffix:semicolon
multiline_comment|/* The next Hash table entry index, assigned&n;&t;&t;&t;&t; * to use the same adapter for transmit.&n;&t;&t;&t;&t; */
DECL|member|prev
id|u32
id|prev
suffix:semicolon
multiline_comment|/* The previous Hash table entry index,&n;&t;&t;&t;&t; * assigned to use the same&n;&t;&t;&t;&t; */
)brace
suffix:semicolon
multiline_comment|/* -------------------------------------------------------------------------&n; * struct rlb_client_info contains all info related to a specific rx client&n; * connection. This is the Clients Hash Table entry struct&n; * -------------------------------------------------------------------------&n; */
DECL|struct|rlb_client_info
r_struct
id|rlb_client_info
(brace
DECL|member|ip_src
id|u32
id|ip_src
suffix:semicolon
multiline_comment|/* the server IP address */
DECL|member|ip_dst
id|u32
id|ip_dst
suffix:semicolon
multiline_comment|/* the client IP address */
DECL|member|mac_dst
id|u8
id|mac_dst
(braket
id|ETH_ALEN
)braket
suffix:semicolon
multiline_comment|/* the client MAC address */
DECL|member|next
id|u32
id|next
suffix:semicolon
multiline_comment|/* The next Hash table entry index */
DECL|member|prev
id|u32
id|prev
suffix:semicolon
multiline_comment|/* The previous Hash table entry index */
DECL|member|assigned
id|u8
id|assigned
suffix:semicolon
multiline_comment|/* checking whether this entry is assigned */
DECL|member|ntt
id|u8
id|ntt
suffix:semicolon
multiline_comment|/* flag - need to transmit client info */
DECL|member|slave
r_struct
id|slave
op_star
id|slave
suffix:semicolon
multiline_comment|/* the slave assigned to this client */
)brace
suffix:semicolon
DECL|struct|tlb_slave_info
r_struct
id|tlb_slave_info
(brace
DECL|member|head
id|u32
id|head
suffix:semicolon
multiline_comment|/* Index to the head of the bi-directional clients&n;&t;&t;&t; * hash table entries list. The entries in the list&n;&t;&t;&t; * are the entries that were assigned to use this&n;&t;&t;&t; * slave for transmit.&n;&t;&t;&t; */
DECL|member|load
id|u32
id|load
suffix:semicolon
multiline_comment|/* Each slave sums the loadHistory of all clients&n;&t;&t;&t; * assigned to it&n;&t;&t;&t; */
)brace
suffix:semicolon
DECL|struct|alb_bond_info
r_struct
id|alb_bond_info
(brace
DECL|member|alb_timer
r_struct
id|timer_list
id|alb_timer
suffix:semicolon
DECL|member|tx_hashtbl
r_struct
id|tlb_client_info
op_star
id|tx_hashtbl
suffix:semicolon
multiline_comment|/* Dynamically allocated */
DECL|member|tx_hashtbl_lock
id|spinlock_t
id|tx_hashtbl_lock
suffix:semicolon
DECL|member|unbalanced_load
id|u32
id|unbalanced_load
suffix:semicolon
DECL|member|tx_rebalance_counter
r_int
id|tx_rebalance_counter
suffix:semicolon
DECL|member|lp_counter
r_int
id|lp_counter
suffix:semicolon
multiline_comment|/* -------- rlb parameters -------- */
DECL|member|rlb_enabled
r_int
id|rlb_enabled
suffix:semicolon
DECL|member|rlb_pkt_type
r_struct
id|packet_type
id|rlb_pkt_type
suffix:semicolon
DECL|member|rx_hashtbl
r_struct
id|rlb_client_info
op_star
id|rx_hashtbl
suffix:semicolon
multiline_comment|/* Receive hash table */
DECL|member|rx_hashtbl_lock
id|spinlock_t
id|rx_hashtbl_lock
suffix:semicolon
DECL|member|rx_hashtbl_head
id|u32
id|rx_hashtbl_head
suffix:semicolon
DECL|member|rx_ntt
id|u8
id|rx_ntt
suffix:semicolon
multiline_comment|/* flag - need to transmit&n;&t;&t;&t;&t;&t; * to all rx clients&n;&t;&t;&t;&t;&t; */
DECL|member|next_rx_slave
r_struct
id|slave
op_star
id|next_rx_slave
suffix:semicolon
multiline_comment|/* next slave to be assigned&n;&t;&t;&t;&t;&t;&t;* to a new rx client for&n;&t;&t;&t;&t;&t;&t;*/
DECL|member|rlb_interval_counter
id|u32
id|rlb_interval_counter
suffix:semicolon
DECL|member|primary_is_promisc
id|u8
id|primary_is_promisc
suffix:semicolon
multiline_comment|/* boolean */
DECL|member|rlb_promisc_timeout_counter
id|u32
id|rlb_promisc_timeout_counter
suffix:semicolon
multiline_comment|/* counts primary&n;&t;&t;&t;&t;&t;&t;&t;     * promiscuity time&n;&t;&t;&t;&t;&t;&t;&t;     */
DECL|member|rlb_update_delay_counter
id|u32
id|rlb_update_delay_counter
suffix:semicolon
DECL|member|rlb_update_retry_counter
id|u32
id|rlb_update_retry_counter
suffix:semicolon
multiline_comment|/* counter of retries&n;&t;&t;&t;&t;&t;&t;&t;  * of client update&n;&t;&t;&t;&t;&t;&t;&t;  */
DECL|member|rlb_rebalance
id|u8
id|rlb_rebalance
suffix:semicolon
multiline_comment|/* flag - indicates that the&n;&t;&t;&t;&t;&t;&t; * rx traffic should be&n;&t;&t;&t;&t;&t;&t; * rebalanced&n;&t;&t;&t;&t;&t;&t; */
)brace
suffix:semicolon
r_int
id|bond_alb_initialize
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_int
id|rlb_enabled
)paren
suffix:semicolon
r_void
id|bond_alb_deinitialize
c_func
(paren
r_struct
id|bonding
op_star
id|bond
)paren
suffix:semicolon
r_int
id|bond_alb_init_slave
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_struct
id|slave
op_star
id|slave
)paren
suffix:semicolon
r_void
id|bond_alb_deinit_slave
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_struct
id|slave
op_star
id|slave
)paren
suffix:semicolon
r_void
id|bond_alb_handle_link_change
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_struct
id|slave
op_star
id|slave
comma
r_char
id|link
)paren
suffix:semicolon
r_void
id|bond_alb_assign_current_slave
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_struct
id|slave
op_star
id|new_slave
)paren
suffix:semicolon
r_int
id|bond_alb_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_void
id|bond_alb_monitor
c_func
(paren
r_struct
id|bonding
op_star
id|bond
)paren
suffix:semicolon
macro_line|#endif /* __BOND_ALB_H__ */
eof
