multiline_comment|/**************************************************************************/
multiline_comment|/*                                                                        */
multiline_comment|/* IBM eServer i/[Series Virtual Ethernet Device Driver                   */
multiline_comment|/* Copyright (C) 2003 IBM Corp.                                           */
multiline_comment|/*  Dave Larson (larson1@us.ibm.com)                                      */
multiline_comment|/*  Santiago Leon (santil@us.ibm.com)                                     */
multiline_comment|/*                                                                        */
multiline_comment|/*  This program is free software; you can redistribute it and/or modify  */
multiline_comment|/*  it under the terms of the GNU General Public License as published by  */
multiline_comment|/*  the Free Software Foundation; either version 2 of the License, or     */
multiline_comment|/*  (at your option) any later version.                                   */
multiline_comment|/*                                                                        */
multiline_comment|/*  This program is distributed in the hope that it will be useful,       */
multiline_comment|/*  but WITHOUT ANY WARRANTY; without even the implied warranty of        */
multiline_comment|/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
multiline_comment|/*  GNU General Public License for more details.                          */
multiline_comment|/*                                                                        */
multiline_comment|/*  You should have received a copy of the GNU General Public License     */
multiline_comment|/*  along with this program; if not, write to the Free Software           */
multiline_comment|/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  */
multiline_comment|/*                                                                   USA  */
multiline_comment|/*                                                                        */
multiline_comment|/**************************************************************************/
macro_line|#ifndef _IBMVETH_H
DECL|macro|_IBMVETH_H
mdefine_line|#define _IBMVETH_H
DECL|macro|IbmVethMaxSendFrags
mdefine_line|#define IbmVethMaxSendFrags 6
multiline_comment|/* constants for H_MULTICAST_CTRL */
DECL|macro|IbmVethMcastReceptionModifyBit
mdefine_line|#define IbmVethMcastReceptionModifyBit     0x80000UL
DECL|macro|IbmVethMcastReceptionEnableBit
mdefine_line|#define IbmVethMcastReceptionEnableBit     0x20000UL
DECL|macro|IbmVethMcastFilterModifyBit
mdefine_line|#define IbmVethMcastFilterModifyBit        0x40000UL
DECL|macro|IbmVethMcastFilterEnableBit
mdefine_line|#define IbmVethMcastFilterEnableBit        0x10000UL
DECL|macro|IbmVethMcastEnableRecv
mdefine_line|#define IbmVethMcastEnableRecv       (IbmVethMcastReceptionModifyBit | IbmVethMcastReceptionEnableBit)
DECL|macro|IbmVethMcastDisableRecv
mdefine_line|#define IbmVethMcastDisableRecv      (IbmVethMcastReceptionModifyBit)
DECL|macro|IbmVethMcastEnableFiltering
mdefine_line|#define IbmVethMcastEnableFiltering  (IbmVethMcastFilterModifyBit | IbmVethMcastFilterEnableBit)
DECL|macro|IbmVethMcastDisableFiltering
mdefine_line|#define IbmVethMcastDisableFiltering (IbmVethMcastFilterModifyBit)
DECL|macro|IbmVethMcastAddFilter
mdefine_line|#define IbmVethMcastAddFilter        0x1UL
DECL|macro|IbmVethMcastRemoveFilter
mdefine_line|#define IbmVethMcastRemoveFilter     0x2UL
DECL|macro|IbmVethMcastClearFilterTable
mdefine_line|#define IbmVethMcastClearFilterTable 0x3UL
multiline_comment|/* hcall numbers */
DECL|macro|H_VIO_SIGNAL
mdefine_line|#define H_VIO_SIGNAL             0x104
DECL|macro|H_REGISTER_LOGICAL_LAN
mdefine_line|#define H_REGISTER_LOGICAL_LAN   0x114
DECL|macro|H_FREE_LOGICAL_LAN
mdefine_line|#define H_FREE_LOGICAL_LAN       0x118
DECL|macro|H_ADD_LOGICAL_LAN_BUFFER
mdefine_line|#define H_ADD_LOGICAL_LAN_BUFFER 0x11C
DECL|macro|H_SEND_LOGICAL_LAN
mdefine_line|#define H_SEND_LOGICAL_LAN       0x120
DECL|macro|H_MULTICAST_CTRL
mdefine_line|#define H_MULTICAST_CTRL         0x130
DECL|macro|H_CHANGE_LOGICAL_LAN_MAC
mdefine_line|#define H_CHANGE_LOGICAL_LAN_MAC 0x14C
multiline_comment|/* hcall macros */
DECL|macro|h_register_logical_lan
mdefine_line|#define h_register_logical_lan(ua, buflst, rxq, fltlst, mac) &bslash;&n;  plpar_hcall_norets(H_REGISTER_LOGICAL_LAN, ua, buflst, rxq, fltlst, mac)
DECL|macro|h_free_logical_lan
mdefine_line|#define h_free_logical_lan(ua) &bslash;&n;  plpar_hcall_norets(H_FREE_LOGICAL_LAN, ua)
DECL|macro|h_add_logical_lan_buffer
mdefine_line|#define h_add_logical_lan_buffer(ua, buf) &bslash;&n;  plpar_hcall_norets(H_ADD_LOGICAL_LAN_BUFFER, ua, buf)
DECL|macro|h_send_logical_lan
mdefine_line|#define h_send_logical_lan(ua, buf1, buf2, buf3, buf4, buf5, buf6, correlator) &bslash;&n;  plpar_hcall_8arg_2ret(H_SEND_LOGICAL_LAN, ua, buf1, buf2, buf3, buf4, buf5, buf6, correlator, &amp;correlator)
DECL|macro|h_multicast_ctrl
mdefine_line|#define h_multicast_ctrl(ua, cmd, mac) &bslash;&n;  plpar_hcall_norets(H_MULTICAST_CTRL, ua, cmd, mac)
DECL|macro|h_change_logical_lan_mac
mdefine_line|#define h_change_logical_lan_mac(ua, mac) &bslash;&n;  plpar_hcall_norets(H_CHANGE_LOGICAL_LAN_MAC, ua, mac)
DECL|macro|IbmVethNumBufferPools
mdefine_line|#define IbmVethNumBufferPools 3
DECL|macro|IbmVethPool0DftSize
mdefine_line|#define IbmVethPool0DftSize (1024 * 2)
DECL|macro|IbmVethPool1DftSize
mdefine_line|#define IbmVethPool1DftSize (1024 * 4)
DECL|macro|IbmVethPool2DftSize
mdefine_line|#define IbmVethPool2DftSize (1024 * 10)
DECL|macro|IbmVethPool0DftCnt
mdefine_line|#define IbmVethPool0DftCnt  256
DECL|macro|IbmVethPool1DftCnt
mdefine_line|#define IbmVethPool1DftCnt  256
DECL|macro|IbmVethPool2DftCnt
mdefine_line|#define IbmVethPool2DftCnt  256
DECL|struct|ibmveth_buff_pool
r_struct
id|ibmveth_buff_pool
(brace
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|member|buff_size
id|u32
id|buff_size
suffix:semicolon
DECL|member|threshold
id|u32
id|threshold
suffix:semicolon
DECL|member|available
id|atomic_t
id|available
suffix:semicolon
DECL|member|consumer_index
id|u32
id|consumer_index
suffix:semicolon
DECL|member|producer_index
id|u32
id|producer_index
suffix:semicolon
DECL|member|free_map
id|u16
op_star
id|free_map
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
op_star
id|dma_addr
suffix:semicolon
DECL|member|skbuff
r_struct
id|sk_buff
op_star
op_star
id|skbuff
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ibmveth_rx_q
r_struct
id|ibmveth_rx_q
(brace
DECL|member|index
id|u64
id|index
suffix:semicolon
DECL|member|num_slots
id|u64
id|num_slots
suffix:semicolon
DECL|member|toggle
id|u64
id|toggle
suffix:semicolon
DECL|member|queue_dma
id|dma_addr_t
id|queue_dma
suffix:semicolon
DECL|member|queue_len
id|u32
id|queue_len
suffix:semicolon
DECL|member|queue_addr
r_struct
id|ibmveth_rx_q_entry
op_star
id|queue_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ibmveth_adapter
r_struct
id|ibmveth_adapter
(brace
DECL|member|vdev
r_struct
id|vio_dev
op_star
id|vdev
suffix:semicolon
DECL|member|netdev
r_struct
id|net_device
op_star
id|netdev
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|mcastFilterSize
r_int
r_int
id|mcastFilterSize
suffix:semicolon
DECL|member|mac_addr
r_int
r_int
id|mac_addr
suffix:semicolon
DECL|member|liobn
r_int
r_int
id|liobn
suffix:semicolon
DECL|member|buffer_list_addr
r_void
op_star
id|buffer_list_addr
suffix:semicolon
DECL|member|filter_list_addr
r_void
op_star
id|filter_list_addr
suffix:semicolon
DECL|member|buffer_list_dma
id|dma_addr_t
id|buffer_list_dma
suffix:semicolon
DECL|member|filter_list_dma
id|dma_addr_t
id|filter_list_dma
suffix:semicolon
DECL|member|rx_buff_pool
r_struct
id|ibmveth_buff_pool
id|rx_buff_pool
(braket
id|IbmVethNumBufferPools
)braket
suffix:semicolon
DECL|member|rx_queue
r_struct
id|ibmveth_rx_q
id|rx_queue
suffix:semicolon
DECL|member|not_replenishing
id|atomic_t
id|not_replenishing
suffix:semicolon
multiline_comment|/* helper tasks */
DECL|member|replenish_task
r_struct
id|work_struct
id|replenish_task
suffix:semicolon
multiline_comment|/* adapter specific stats */
DECL|member|replenish_task_cycles
id|u64
id|replenish_task_cycles
suffix:semicolon
DECL|member|replenish_no_mem
id|u64
id|replenish_no_mem
suffix:semicolon
DECL|member|replenish_add_buff_failure
id|u64
id|replenish_add_buff_failure
suffix:semicolon
DECL|member|replenish_add_buff_success
id|u64
id|replenish_add_buff_success
suffix:semicolon
DECL|member|rx_invalid_buffer
id|u64
id|rx_invalid_buffer
suffix:semicolon
DECL|member|rx_no_buffer
id|u64
id|rx_no_buffer
suffix:semicolon
DECL|member|tx_multidesc_send
id|u64
id|tx_multidesc_send
suffix:semicolon
DECL|member|tx_linearized
id|u64
id|tx_linearized
suffix:semicolon
DECL|member|tx_linearize_failed
id|u64
id|tx_linearize_failed
suffix:semicolon
DECL|member|tx_map_failed
id|u64
id|tx_map_failed
suffix:semicolon
DECL|member|tx_send_failed
id|u64
id|tx_send_failed
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ibmveth_buf_desc_fields
r_struct
id|ibmveth_buf_desc_fields
(brace
DECL|member|valid
id|u32
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|toggle
id|u32
id|toggle
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|6
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:colon
l_int|24
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
)brace
suffix:semicolon
DECL|union|ibmveth_buf_desc
r_union
id|ibmveth_buf_desc
(brace
DECL|member|desc
id|u64
id|desc
suffix:semicolon
DECL|member|fields
r_struct
id|ibmveth_buf_desc_fields
id|fields
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ibmveth_rx_q_entry
r_struct
id|ibmveth_rx_q_entry
(brace
DECL|member|toggle
id|u16
id|toggle
suffix:colon
l_int|1
suffix:semicolon
DECL|member|valid
id|u16
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:colon
l_int|14
suffix:semicolon
DECL|member|offset
id|u16
id|offset
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|correlator
id|u64
id|correlator
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _IBMVETH_H */
eof
