multiline_comment|/*&n; * Copyright(c) 1999 - 2003 Intel Corporation. All rights reserved.&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the Free&n; * Software Foundation; either version 2 of the License, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; *&n; * You should have received a copy of the GNU General Public License along with&n; * this program; if not, write to the Free Software Foundation, Inc., 59&n; * Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n; *&n; * The full GNU General Public License is included in this distribution in the&n; * file called LICENSE.&n; *&n; *&n; * Changes:&n; *&n; * 2003/05/01 - Tsippy Mendelson &lt;tsippy.mendelson at intel dot com&gt; and&n; *&t;&t;Amir Noam &lt;amir.noam at intel dot com&gt;&n; *&t;- Added support for lacp_rate module param.&n; *&n; * 2003/05/01 - Shmulik Hen &lt;shmulik.hen at intel dot com&gt;&n; *&t;- Renamed bond_3ad_link_status_changed() to&n; *&t;  bond_3ad_handle_link_change() for compatibility with TLB.&n; */
macro_line|#ifndef __BOND_3AD_H__
DECL|macro|__BOND_3AD_H__
mdefine_line|#define __BOND_3AD_H__
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
singleline_comment|// General definitions
DECL|macro|BOND_ETH_P_LACPDU
mdefine_line|#define BOND_ETH_P_LACPDU       0x8809
DECL|macro|PKT_TYPE_LACPDU
mdefine_line|#define PKT_TYPE_LACPDU         __constant_htons(BOND_ETH_P_LACPDU)
DECL|macro|AD_TIMER_INTERVAL
mdefine_line|#define AD_TIMER_INTERVAL       100 /*msec*/
DECL|macro|MULTICAST_LACPDU_ADDR
mdefine_line|#define MULTICAST_LACPDU_ADDR    {0x01, 0x80, 0xC2, 0x00, 0x00, 0x02}
DECL|macro|AD_MULTICAST_LACPDU_ADDR
mdefine_line|#define AD_MULTICAST_LACPDU_ADDR    {MULTICAST_LACPDU_ADDR}
DECL|macro|AD_LACP_SLOW
mdefine_line|#define AD_LACP_SLOW 0
DECL|macro|AD_LACP_FAST
mdefine_line|#define AD_LACP_FAST 1
DECL|struct|mac_addr
r_typedef
r_struct
id|mac_addr
(brace
DECL|member|mac_addr_value
id|u8
id|mac_addr_value
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|typedef|mac_addr_t
)brace
id|mac_addr_t
suffix:semicolon
r_typedef
r_enum
(brace
DECL|enumerator|AD_BANDWIDTH
id|AD_BANDWIDTH
op_assign
l_int|0
comma
DECL|enumerator|AD_COUNT
id|AD_COUNT
DECL|typedef|agg_selection_t
)brace
id|agg_selection_t
suffix:semicolon
singleline_comment|// rx machine states(43.4.11 in the 802.3ad standard)
r_typedef
r_enum
(brace
DECL|enumerator|AD_RX_DUMMY
id|AD_RX_DUMMY
comma
DECL|enumerator|AD_RX_INITIALIZE
id|AD_RX_INITIALIZE
comma
singleline_comment|// rx Machine
DECL|enumerator|AD_RX_PORT_DISABLED
id|AD_RX_PORT_DISABLED
comma
singleline_comment|// rx Machine
DECL|enumerator|AD_RX_LACP_DISABLED
id|AD_RX_LACP_DISABLED
comma
singleline_comment|// rx Machine
DECL|enumerator|AD_RX_EXPIRED
id|AD_RX_EXPIRED
comma
singleline_comment|// rx Machine
DECL|enumerator|AD_RX_DEFAULTED
id|AD_RX_DEFAULTED
comma
singleline_comment|// rx Machine
DECL|enumerator|AD_RX_CURRENT
id|AD_RX_CURRENT
singleline_comment|// rx Machine
DECL|typedef|rx_states_t
)brace
id|rx_states_t
suffix:semicolon
singleline_comment|// periodic machine states(43.4.12 in the 802.3ad standard)
r_typedef
r_enum
(brace
DECL|enumerator|AD_PERIODIC_DUMMY
id|AD_PERIODIC_DUMMY
comma
DECL|enumerator|AD_NO_PERIODIC
id|AD_NO_PERIODIC
comma
singleline_comment|// periodic machine
DECL|enumerator|AD_FAST_PERIODIC
id|AD_FAST_PERIODIC
comma
singleline_comment|// periodic machine
DECL|enumerator|AD_SLOW_PERIODIC
id|AD_SLOW_PERIODIC
comma
singleline_comment|// periodic machine
DECL|enumerator|AD_PERIODIC_TX
id|AD_PERIODIC_TX
singleline_comment|// periodic machine
DECL|typedef|periodic_states_t
)brace
id|periodic_states_t
suffix:semicolon
singleline_comment|// mux machine states(43.4.13 in the 802.3ad standard)
r_typedef
r_enum
(brace
DECL|enumerator|AD_MUX_DUMMY
id|AD_MUX_DUMMY
comma
DECL|enumerator|AD_MUX_DETACHED
id|AD_MUX_DETACHED
comma
singleline_comment|// mux machine
DECL|enumerator|AD_MUX_WAITING
id|AD_MUX_WAITING
comma
singleline_comment|// mux machine
DECL|enumerator|AD_MUX_ATTACHED
id|AD_MUX_ATTACHED
comma
singleline_comment|// mux machine
DECL|enumerator|AD_MUX_COLLECTING_DISTRIBUTING
id|AD_MUX_COLLECTING_DISTRIBUTING
singleline_comment|// mux machine
DECL|typedef|mux_states_t
)brace
id|mux_states_t
suffix:semicolon
singleline_comment|// tx machine states(43.4.15 in the 802.3ad standard)
r_typedef
r_enum
(brace
DECL|enumerator|AD_TX_DUMMY
id|AD_TX_DUMMY
comma
DECL|enumerator|AD_TRANSMIT
id|AD_TRANSMIT
singleline_comment|// tx Machine
DECL|typedef|tx_states_t
)brace
id|tx_states_t
suffix:semicolon
singleline_comment|// rx indication types
r_typedef
r_enum
(brace
DECL|enumerator|AD_TYPE_LACPDU
id|AD_TYPE_LACPDU
op_assign
l_int|1
comma
singleline_comment|// type lacpdu
DECL|enumerator|AD_TYPE_MARKER
id|AD_TYPE_MARKER
singleline_comment|// type marker
DECL|typedef|pdu_type_t
)brace
id|pdu_type_t
suffix:semicolon
singleline_comment|// rx marker indication types
r_typedef
r_enum
(brace
DECL|enumerator|AD_MARKER_INFORMATION_SUBTYPE
id|AD_MARKER_INFORMATION_SUBTYPE
op_assign
l_int|1
comma
singleline_comment|// marker imformation subtype
DECL|enumerator|AD_MARKER_RESPONSE_SUBTYPE
id|AD_MARKER_RESPONSE_SUBTYPE
singleline_comment|// marker response subtype
DECL|typedef|marker_subtype_t
)brace
id|marker_subtype_t
suffix:semicolon
singleline_comment|// timers types(43.4.9 in the 802.3ad standard)
r_typedef
r_enum
(brace
DECL|enumerator|AD_CURRENT_WHILE_TIMER
id|AD_CURRENT_WHILE_TIMER
comma
DECL|enumerator|AD_ACTOR_CHURN_TIMER
id|AD_ACTOR_CHURN_TIMER
comma
DECL|enumerator|AD_PERIODIC_TIMER
id|AD_PERIODIC_TIMER
comma
DECL|enumerator|AD_PARTNER_CHURN_TIMER
id|AD_PARTNER_CHURN_TIMER
comma
DECL|enumerator|AD_WAIT_WHILE_TIMER
id|AD_WAIT_WHILE_TIMER
DECL|typedef|ad_timers_t
)brace
id|ad_timers_t
suffix:semicolon
macro_line|#pragma pack(1)
DECL|struct|ad_header
r_typedef
r_struct
id|ad_header
(brace
DECL|member|destination_address
r_struct
id|mac_addr
id|destination_address
suffix:semicolon
DECL|member|source_address
r_struct
id|mac_addr
id|source_address
suffix:semicolon
DECL|member|length_type
id|u16
id|length_type
suffix:semicolon
DECL|typedef|ad_header_t
)brace
id|ad_header_t
suffix:semicolon
singleline_comment|// Link Aggregation Control Protocol(LACP) data unit structure(43.4.2.2 in the 802.3ad standard)
DECL|struct|lacpdu
r_typedef
r_struct
id|lacpdu
(brace
DECL|member|subtype
id|u8
id|subtype
suffix:semicolon
singleline_comment|// = LACP(= 0x01)
DECL|member|version_number
id|u8
id|version_number
suffix:semicolon
DECL|member|tlv_type_actor_info
id|u8
id|tlv_type_actor_info
suffix:semicolon
singleline_comment|// = actor information(type/length/value)
DECL|member|actor_information_length
id|u8
id|actor_information_length
suffix:semicolon
singleline_comment|// = 20
DECL|member|actor_system_priority
id|u16
id|actor_system_priority
suffix:semicolon
DECL|member|actor_system
r_struct
id|mac_addr
id|actor_system
suffix:semicolon
DECL|member|actor_key
id|u16
id|actor_key
suffix:semicolon
DECL|member|actor_port_priority
id|u16
id|actor_port_priority
suffix:semicolon
DECL|member|actor_port
id|u16
id|actor_port
suffix:semicolon
DECL|member|actor_state
id|u8
id|actor_state
suffix:semicolon
DECL|member|reserved_3_1
id|u8
id|reserved_3_1
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// = 0
DECL|member|tlv_type_partner_info
id|u8
id|tlv_type_partner_info
suffix:semicolon
singleline_comment|// = partner information
DECL|member|partner_information_length
id|u8
id|partner_information_length
suffix:semicolon
singleline_comment|// = 20
DECL|member|partner_system_priority
id|u16
id|partner_system_priority
suffix:semicolon
DECL|member|partner_system
r_struct
id|mac_addr
id|partner_system
suffix:semicolon
DECL|member|partner_key
id|u16
id|partner_key
suffix:semicolon
DECL|member|partner_port_priority
id|u16
id|partner_port_priority
suffix:semicolon
DECL|member|partner_port
id|u16
id|partner_port
suffix:semicolon
DECL|member|partner_state
id|u8
id|partner_state
suffix:semicolon
DECL|member|reserved_3_2
id|u8
id|reserved_3_2
(braket
l_int|3
)braket
suffix:semicolon
singleline_comment|// = 0
DECL|member|tlv_type_collector_info
id|u8
id|tlv_type_collector_info
suffix:semicolon
singleline_comment|// = collector information
DECL|member|collector_information_length
id|u8
id|collector_information_length
suffix:semicolon
singleline_comment|// = 16
DECL|member|collector_max_delay
id|u16
id|collector_max_delay
suffix:semicolon
DECL|member|reserved_12
id|u8
id|reserved_12
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|tlv_type_terminator
id|u8
id|tlv_type_terminator
suffix:semicolon
singleline_comment|// = terminator
DECL|member|terminator_length
id|u8
id|terminator_length
suffix:semicolon
singleline_comment|// = 0
DECL|member|reserved_50
id|u8
id|reserved_50
(braket
l_int|50
)braket
suffix:semicolon
singleline_comment|// = 0
DECL|typedef|lacpdu_t
)brace
id|lacpdu_t
suffix:semicolon
DECL|struct|lacpdu_header
r_typedef
r_struct
id|lacpdu_header
(brace
DECL|member|ad_header
r_struct
id|ad_header
id|ad_header
suffix:semicolon
DECL|member|lacpdu
r_struct
id|lacpdu
id|lacpdu
suffix:semicolon
DECL|typedef|lacpdu_header_t
)brace
id|lacpdu_header_t
suffix:semicolon
singleline_comment|// Marker Protocol Data Unit(PDU) structure(43.5.3.2 in the 802.3ad standard)
DECL|struct|marker
r_typedef
r_struct
id|marker
(brace
DECL|member|subtype
id|u8
id|subtype
suffix:semicolon
singleline_comment|//  = 0x02  (marker PDU)
DECL|member|version_number
id|u8
id|version_number
suffix:semicolon
singleline_comment|//  = 0x01
DECL|member|tlv_type
id|u8
id|tlv_type
suffix:semicolon
singleline_comment|//  = 0x01  (marker information)
singleline_comment|//  = 0x02  (marker response information)
DECL|member|marker_length
id|u8
id|marker_length
suffix:semicolon
singleline_comment|//  = 0x16
DECL|member|requester_port
id|u16
id|requester_port
suffix:semicolon
singleline_comment|//   The number assigned to the port by the requester
DECL|member|requester_system
r_struct
id|mac_addr
id|requester_system
suffix:semicolon
singleline_comment|//   The requester&#xfffd;s system id
DECL|member|requester_transaction_id
id|u32
id|requester_transaction_id
suffix:semicolon
singleline_comment|//   The transaction id allocated by the requester,
DECL|member|pad
id|u16
id|pad
suffix:semicolon
singleline_comment|//  = 0
DECL|member|tlv_type_terminator
id|u8
id|tlv_type_terminator
suffix:semicolon
singleline_comment|//  = 0x00
DECL|member|terminator_length
id|u8
id|terminator_length
suffix:semicolon
singleline_comment|//  = 0x00
DECL|member|reserved_90
id|u8
id|reserved_90
(braket
l_int|90
)braket
suffix:semicolon
singleline_comment|//  = 0
DECL|typedef|marker_t
)brace
id|marker_t
suffix:semicolon
DECL|struct|marker_header
r_typedef
r_struct
id|marker_header
(brace
DECL|member|ad_header
r_struct
id|ad_header
id|ad_header
suffix:semicolon
DECL|member|marker
r_struct
id|marker
id|marker
suffix:semicolon
DECL|typedef|marker_header_t
)brace
id|marker_header_t
suffix:semicolon
macro_line|#pragma pack()
r_struct
id|slave
suffix:semicolon
r_struct
id|bonding
suffix:semicolon
r_struct
id|ad_info
suffix:semicolon
r_struct
id|port
suffix:semicolon
macro_line|#ifdef __ia64__
macro_line|#pragma pack(8)
macro_line|#endif
singleline_comment|// aggregator structure(43.4.5 in the 802.3ad standard)
DECL|struct|aggregator
r_typedef
r_struct
id|aggregator
(brace
DECL|member|aggregator_mac_address
r_struct
id|mac_addr
id|aggregator_mac_address
suffix:semicolon
DECL|member|aggregator_identifier
id|u16
id|aggregator_identifier
suffix:semicolon
DECL|member|is_individual
id|u16
id|is_individual
suffix:semicolon
singleline_comment|// BOOLEAN
DECL|member|actor_admin_aggregator_key
id|u16
id|actor_admin_aggregator_key
suffix:semicolon
DECL|member|actor_oper_aggregator_key
id|u16
id|actor_oper_aggregator_key
suffix:semicolon
DECL|member|partner_system
r_struct
id|mac_addr
id|partner_system
suffix:semicolon
DECL|member|partner_system_priority
id|u16
id|partner_system_priority
suffix:semicolon
DECL|member|partner_oper_aggregator_key
id|u16
id|partner_oper_aggregator_key
suffix:semicolon
DECL|member|receive_state
id|u16
id|receive_state
suffix:semicolon
singleline_comment|// BOOLEAN
DECL|member|transmit_state
id|u16
id|transmit_state
suffix:semicolon
singleline_comment|// BOOLEAN
DECL|member|lag_ports
r_struct
id|port
op_star
id|lag_ports
suffix:semicolon
singleline_comment|// ****** PRIVATE PARAMETERS ******
DECL|member|slave
r_struct
id|slave
op_star
id|slave
suffix:semicolon
singleline_comment|// pointer to the bond slave that this aggregator belongs to
DECL|member|is_active
id|u16
id|is_active
suffix:semicolon
singleline_comment|// BOOLEAN. Indicates if this aggregator is active
DECL|member|num_of_ports
id|u16
id|num_of_ports
suffix:semicolon
DECL|typedef|aggregator_t
)brace
id|aggregator_t
suffix:semicolon
singleline_comment|// port structure(43.4.6 in the 802.3ad standard)
DECL|struct|port
r_typedef
r_struct
id|port
(brace
DECL|member|actor_port_number
id|u16
id|actor_port_number
suffix:semicolon
DECL|member|actor_port_priority
id|u16
id|actor_port_priority
suffix:semicolon
DECL|member|actor_system
r_struct
id|mac_addr
id|actor_system
suffix:semicolon
singleline_comment|// This parameter is added here although it is not specified in the standard, just for simplification
DECL|member|actor_system_priority
id|u16
id|actor_system_priority
suffix:semicolon
singleline_comment|// This parameter is added here although it is not specified in the standard, just for simplification
DECL|member|actor_port_aggregator_identifier
id|u16
id|actor_port_aggregator_identifier
suffix:semicolon
DECL|member|ntt
id|u16
id|ntt
suffix:semicolon
singleline_comment|// BOOLEAN
DECL|member|actor_admin_port_key
id|u16
id|actor_admin_port_key
suffix:semicolon
DECL|member|actor_oper_port_key
id|u16
id|actor_oper_port_key
suffix:semicolon
DECL|member|actor_admin_port_state
id|u8
id|actor_admin_port_state
suffix:semicolon
DECL|member|actor_oper_port_state
id|u8
id|actor_oper_port_state
suffix:semicolon
DECL|member|partner_admin_system
r_struct
id|mac_addr
id|partner_admin_system
suffix:semicolon
DECL|member|partner_oper_system
r_struct
id|mac_addr
id|partner_oper_system
suffix:semicolon
DECL|member|partner_admin_system_priority
id|u16
id|partner_admin_system_priority
suffix:semicolon
DECL|member|partner_oper_system_priority
id|u16
id|partner_oper_system_priority
suffix:semicolon
DECL|member|partner_admin_key
id|u16
id|partner_admin_key
suffix:semicolon
DECL|member|partner_oper_key
id|u16
id|partner_oper_key
suffix:semicolon
DECL|member|partner_admin_port_number
id|u16
id|partner_admin_port_number
suffix:semicolon
DECL|member|partner_oper_port_number
id|u16
id|partner_oper_port_number
suffix:semicolon
DECL|member|partner_admin_port_priority
id|u16
id|partner_admin_port_priority
suffix:semicolon
DECL|member|partner_oper_port_priority
id|u16
id|partner_oper_port_priority
suffix:semicolon
DECL|member|partner_admin_port_state
id|u8
id|partner_admin_port_state
suffix:semicolon
DECL|member|partner_oper_port_state
id|u8
id|partner_oper_port_state
suffix:semicolon
DECL|member|is_enabled
id|u16
id|is_enabled
suffix:semicolon
singleline_comment|// BOOLEAN
singleline_comment|// ****** PRIVATE PARAMETERS ******
DECL|member|sm_vars
id|u16
id|sm_vars
suffix:semicolon
singleline_comment|// all state machines variables for this port
DECL|member|sm_rx_state
id|rx_states_t
id|sm_rx_state
suffix:semicolon
singleline_comment|// state machine rx state
DECL|member|sm_rx_timer_counter
id|u16
id|sm_rx_timer_counter
suffix:semicolon
singleline_comment|// state machine rx timer counter
DECL|member|sm_periodic_state
id|periodic_states_t
id|sm_periodic_state
suffix:semicolon
singleline_comment|// state machine periodic state
DECL|member|sm_periodic_timer_counter
id|u16
id|sm_periodic_timer_counter
suffix:semicolon
singleline_comment|// state machine periodic timer counter
DECL|member|sm_mux_state
id|mux_states_t
id|sm_mux_state
suffix:semicolon
singleline_comment|// state machine mux state
DECL|member|sm_mux_timer_counter
id|u16
id|sm_mux_timer_counter
suffix:semicolon
singleline_comment|// state machine mux timer counter
DECL|member|sm_tx_state
id|tx_states_t
id|sm_tx_state
suffix:semicolon
singleline_comment|// state machine tx state
DECL|member|sm_tx_timer_counter
id|u16
id|sm_tx_timer_counter
suffix:semicolon
singleline_comment|// state machine tx timer counter(allways on - enter to transmit state 3 time per second)
DECL|member|slave
r_struct
id|slave
op_star
id|slave
suffix:semicolon
singleline_comment|// pointer to the bond slave that this port belongs to
DECL|member|aggregator
r_struct
id|aggregator
op_star
id|aggregator
suffix:semicolon
singleline_comment|// pointer to an aggregator that this port related to
DECL|member|next_port_in_aggregator
r_struct
id|port
op_star
id|next_port_in_aggregator
suffix:semicolon
singleline_comment|// Next port on the linked list of the parent aggregator
DECL|member|transaction_id
id|u32
id|transaction_id
suffix:semicolon
singleline_comment|// continuous number for identification of Marker PDU&squot;s;
DECL|member|lacpdu
r_struct
id|lacpdu
id|lacpdu
suffix:semicolon
singleline_comment|// the lacpdu that will be sent for this port
DECL|typedef|port_t
)brace
id|port_t
suffix:semicolon
singleline_comment|// system structure
DECL|struct|ad_system
r_typedef
r_struct
id|ad_system
(brace
DECL|member|sys_priority
id|u16
id|sys_priority
suffix:semicolon
DECL|member|sys_mac_addr
r_struct
id|mac_addr
id|sys_mac_addr
suffix:semicolon
DECL|typedef|ad_system_t
)brace
id|ad_system_t
suffix:semicolon
macro_line|#ifdef __ia64__
macro_line|#pragma pack()
macro_line|#endif
singleline_comment|// ================= AD Exported structures to the main bonding code ==================
DECL|macro|BOND_AD_INFO
mdefine_line|#define BOND_AD_INFO(bond)   ((bond)-&gt;ad_info)
DECL|macro|SLAVE_AD_INFO
mdefine_line|#define SLAVE_AD_INFO(slave) ((slave)-&gt;ad_info)
DECL|struct|ad_bond_info
r_struct
id|ad_bond_info
(brace
DECL|member|system
id|ad_system_t
id|system
suffix:semicolon
singleline_comment|// 802.3ad system structure
DECL|member|agg_select_timer
id|u32
id|agg_select_timer
suffix:semicolon
singleline_comment|// Timer to select aggregator after all adapter&squot;s hand shakes
DECL|member|agg_select_mode
id|u32
id|agg_select_mode
suffix:semicolon
singleline_comment|// Mode of selection of active aggregator(bandwidth/count)
DECL|member|lacp_fast
r_int
id|lacp_fast
suffix:semicolon
multiline_comment|/* whether fast periodic tx should be&n;&t;&t;&t;&t; * requested&n;&t;&t;&t;&t; */
DECL|member|ad_timer
r_struct
id|timer_list
id|ad_timer
suffix:semicolon
DECL|member|ad_pkt_type
r_struct
id|packet_type
id|ad_pkt_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ad_slave_info
r_struct
id|ad_slave_info
(brace
DECL|member|aggregator
r_struct
id|aggregator
id|aggregator
suffix:semicolon
singleline_comment|// 802.3ad aggregator structure
DECL|member|port
r_struct
id|port
id|port
suffix:semicolon
singleline_comment|// 802.3ad port structure
DECL|member|rx_machine_lock
id|spinlock_t
id|rx_machine_lock
suffix:semicolon
singleline_comment|// To avoid race condition between callback and receive interrupt
DECL|member|id
id|u16
id|id
suffix:semicolon
)brace
suffix:semicolon
singleline_comment|// ================= AD Exported functions to the main bonding code ==================
r_void
id|bond_3ad_initialize
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
id|u16
id|tick_resolution
comma
r_int
id|lacp_fast
)paren
suffix:semicolon
r_int
id|bond_3ad_bind_slave
c_func
(paren
r_struct
id|slave
op_star
id|slave
)paren
suffix:semicolon
r_void
id|bond_3ad_unbind_slave
c_func
(paren
r_struct
id|slave
op_star
id|slave
)paren
suffix:semicolon
r_void
id|bond_3ad_state_machine_handler
c_func
(paren
r_struct
id|bonding
op_star
id|bond
)paren
suffix:semicolon
r_void
id|bond_3ad_rx_indication
c_func
(paren
r_struct
id|lacpdu
op_star
id|lacpdu
comma
r_struct
id|slave
op_star
id|slave
comma
id|u16
id|length
)paren
suffix:semicolon
r_void
id|bond_3ad_adapter_speed_changed
c_func
(paren
r_struct
id|slave
op_star
id|slave
)paren
suffix:semicolon
r_void
id|bond_3ad_adapter_duplex_changed
c_func
(paren
r_struct
id|slave
op_star
id|slave
)paren
suffix:semicolon
r_void
id|bond_3ad_handle_link_change
c_func
(paren
r_struct
id|slave
op_star
id|slave
comma
r_char
id|link
)paren
suffix:semicolon
r_int
id|bond_3ad_get_active_agg_info
c_func
(paren
r_struct
id|bonding
op_star
id|bond
comma
r_struct
id|ad_info
op_star
id|ad_info
)paren
suffix:semicolon
r_int
id|bond_3ad_xmit_xor
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
r_int
id|bond_3ad_lacpdu_recv
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
comma
r_struct
id|packet_type
op_star
id|ptype
)paren
suffix:semicolon
macro_line|#endif 
singleline_comment|//__BOND_3AD_H__
eof
