multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *&t;AMD Fplus in tag mode data structs&n; *&t;defs for fplustm.c&n; */
macro_line|#ifndef&t;_FPLUS_
DECL|macro|_FPLUS_
mdefine_line|#define _FPLUS_
macro_line|#ifndef&t;HW_PTR
macro_line|#ifdef&t;MEM_MAPPED_IO
DECL|macro|HW_PTR
mdefine_line|#define&t;HW_PTR&t;u_long
macro_line|#else
DECL|macro|HW_PTR
mdefine_line|#define&t;HW_PTR&t;u_short
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * fplus error statistic structure&n; */
DECL|struct|err_st
r_struct
id|err_st
(brace
DECL|member|err_valid
id|u_long
id|err_valid
suffix:semicolon
multiline_comment|/* memory status valid */
DECL|member|err_abort
id|u_long
id|err_abort
suffix:semicolon
multiline_comment|/* memory status receive abort */
DECL|member|err_e_indicator
id|u_long
id|err_e_indicator
suffix:semicolon
multiline_comment|/* error indicator */
DECL|member|err_crc
id|u_long
id|err_crc
suffix:semicolon
multiline_comment|/* error detected (CRC or length) */
DECL|member|err_llc_frame
id|u_long
id|err_llc_frame
suffix:semicolon
multiline_comment|/* LLC frame */
DECL|member|err_mac_frame
id|u_long
id|err_mac_frame
suffix:semicolon
multiline_comment|/* MAC frame */
DECL|member|err_smt_frame
id|u_long
id|err_smt_frame
suffix:semicolon
multiline_comment|/* SMT frame */
DECL|member|err_imp_frame
id|u_long
id|err_imp_frame
suffix:semicolon
multiline_comment|/* implementer frame */
DECL|member|err_no_buf
id|u_long
id|err_no_buf
suffix:semicolon
multiline_comment|/* no buffer available */
DECL|member|err_too_long
id|u_long
id|err_too_long
suffix:semicolon
multiline_comment|/* longer than max. buffer */
DECL|member|err_bec_stat
id|u_long
id|err_bec_stat
suffix:semicolon
multiline_comment|/* beacon state entered */
DECL|member|err_clm_stat
id|u_long
id|err_clm_stat
suffix:semicolon
multiline_comment|/* claim state entered */
DECL|member|err_sifg_det
id|u_long
id|err_sifg_det
suffix:semicolon
multiline_comment|/* short interframe gap detect */
DECL|member|err_phinv
id|u_long
id|err_phinv
suffix:semicolon
multiline_comment|/* PHY invalid */
DECL|member|err_tkiss
id|u_long
id|err_tkiss
suffix:semicolon
multiline_comment|/* token issued */
DECL|member|err_tkerr
id|u_long
id|err_tkerr
suffix:semicolon
multiline_comment|/* token error */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Transmit Descriptor struct&n; */
DECL|struct|s_smt_fp_txd
r_struct
id|s_smt_fp_txd
(brace
DECL|member|txd_tbctrl
id|u_int
id|txd_tbctrl
suffix:semicolon
multiline_comment|/* transmit buffer control */
DECL|member|txd_txdscr
id|u_int
id|txd_txdscr
suffix:semicolon
multiline_comment|/* transmit frame status word */
DECL|member|txd_tbadr
id|u_int
id|txd_tbadr
suffix:semicolon
multiline_comment|/* physical tx buffer address */
DECL|member|txd_ntdadr
id|u_int
id|txd_ntdadr
suffix:semicolon
multiline_comment|/* physical pointer to the next TxD */
macro_line|#ifdef&t;ENA_64BIT_SUP
DECL|member|txd_tbadr_hi
id|u_int
id|txd_tbadr_hi
suffix:semicolon
multiline_comment|/* physical tx buffer addr (high dword)*/
macro_line|#endif
DECL|member|txd_virt
r_char
id|far
op_star
id|txd_virt
suffix:semicolon
multiline_comment|/* virtual pointer to the data frag */
multiline_comment|/* virt pointer to the next TxD */
DECL|member|txd_next
r_struct
id|s_smt_fp_txd
r_volatile
id|far
op_star
id|txd_next
suffix:semicolon
DECL|member|txd_os
r_struct
id|s_txd_os
id|txd_os
suffix:semicolon
multiline_comment|/* OS - specific struct */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Receive Descriptor struct&n; */
DECL|struct|s_smt_fp_rxd
r_struct
id|s_smt_fp_rxd
(brace
DECL|member|rxd_rbctrl
id|u_int
id|rxd_rbctrl
suffix:semicolon
multiline_comment|/* receive buffer control */
DECL|member|rxd_rfsw
id|u_int
id|rxd_rfsw
suffix:semicolon
multiline_comment|/* receive frame status word */
DECL|member|rxd_rbadr
id|u_int
id|rxd_rbadr
suffix:semicolon
multiline_comment|/* physical rx buffer address */
DECL|member|rxd_nrdadr
id|u_int
id|rxd_nrdadr
suffix:semicolon
multiline_comment|/* physical pointer to the next RxD */
macro_line|#ifdef&t;ENA_64BIT_SUP
DECL|member|rxd_rbadr_hi
id|u_int
id|rxd_rbadr_hi
suffix:semicolon
multiline_comment|/* physical tx buffer addr (high dword)*/
macro_line|#endif
DECL|member|rxd_virt
r_char
id|far
op_star
id|rxd_virt
suffix:semicolon
multiline_comment|/* virtual pointer to the data frag */
multiline_comment|/* virt pointer to the next RxD */
DECL|member|rxd_next
r_struct
id|s_smt_fp_rxd
r_volatile
id|far
op_star
id|rxd_next
suffix:semicolon
DECL|member|rxd_os
r_struct
id|s_rxd_os
id|rxd_os
suffix:semicolon
multiline_comment|/* OS - specific struct */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Descriptor Union Definition&n; */
DECL|union|s_fp_descr
r_union
id|s_fp_descr
(brace
DECL|member|t
r_struct
id|s_smt_fp_txd
id|t
suffix:semicolon
multiline_comment|/* pointer to the TxD */
DECL|member|r
r_struct
id|s_smt_fp_rxd
id|r
suffix:semicolon
multiline_comment|/* pointer to the RxD */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;TxD Ring Control struct&n; */
DECL|struct|s_smt_tx_queue
r_struct
id|s_smt_tx_queue
(brace
DECL|member|tx_curr_put
r_struct
id|s_smt_fp_txd
r_volatile
op_star
id|tx_curr_put
suffix:semicolon
multiline_comment|/* next free TxD */
DECL|member|tx_prev_put
r_struct
id|s_smt_fp_txd
r_volatile
op_star
id|tx_prev_put
suffix:semicolon
multiline_comment|/* shadow put pointer */
DECL|member|tx_curr_get
r_struct
id|s_smt_fp_txd
r_volatile
op_star
id|tx_curr_get
suffix:semicolon
multiline_comment|/* next TxD to release*/
DECL|member|tx_free
id|u_short
id|tx_free
suffix:semicolon
multiline_comment|/* count of free TxD&squot;s */
DECL|member|tx_used
id|u_short
id|tx_used
suffix:semicolon
multiline_comment|/* count of used TxD&squot;s */
DECL|member|tx_bmu_ctl
id|HW_PTR
id|tx_bmu_ctl
suffix:semicolon
multiline_comment|/* BMU addr for tx start */
DECL|member|tx_bmu_dsc
id|HW_PTR
id|tx_bmu_dsc
suffix:semicolon
multiline_comment|/* BMU addr for curr dsc. */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;RxD Ring Control struct&n; */
DECL|struct|s_smt_rx_queue
r_struct
id|s_smt_rx_queue
(brace
DECL|member|rx_curr_put
r_struct
id|s_smt_fp_rxd
r_volatile
op_star
id|rx_curr_put
suffix:semicolon
multiline_comment|/* next RxD to queue into */
DECL|member|rx_prev_put
r_struct
id|s_smt_fp_rxd
r_volatile
op_star
id|rx_prev_put
suffix:semicolon
multiline_comment|/* shadow put pointer */
DECL|member|rx_curr_get
r_struct
id|s_smt_fp_rxd
r_volatile
op_star
id|rx_curr_get
suffix:semicolon
multiline_comment|/* next RxD to fill */
DECL|member|rx_free
id|u_short
id|rx_free
suffix:semicolon
multiline_comment|/* count of free RxD&squot;s */
DECL|member|rx_used
id|u_short
id|rx_used
suffix:semicolon
multiline_comment|/* count of used RxD&squot;s */
DECL|member|rx_bmu_ctl
id|HW_PTR
id|rx_bmu_ctl
suffix:semicolon
multiline_comment|/* BMU addr for rx start */
DECL|member|rx_bmu_dsc
id|HW_PTR
id|rx_bmu_dsc
suffix:semicolon
multiline_comment|/* BMU addr for curr dsc. */
)brace
suffix:semicolon
DECL|macro|VOID_FRAME_OFF
mdefine_line|#define VOID_FRAME_OFF&t;&t;0x00
DECL|macro|CLAIM_FRAME_OFF
mdefine_line|#define CLAIM_FRAME_OFF&t;&t;0x08
DECL|macro|BEACON_FRAME_OFF
mdefine_line|#define BEACON_FRAME_OFF&t;0x10
DECL|macro|DBEACON_FRAME_OFF
mdefine_line|#define DBEACON_FRAME_OFF&t;0x18
DECL|macro|RX_FIFO_OFF
mdefine_line|#define RX_FIFO_OFF&t;&t;0x21&t;&t;/* to get a prime number for */
multiline_comment|/* the RX_FIFO_SPACE */
DECL|macro|RBC_MEM_SIZE
mdefine_line|#define RBC_MEM_SIZE&t;&t;0x8000
DECL|macro|SEND_ASYNC_AS_SYNC
mdefine_line|#define SEND_ASYNC_AS_SYNC&t;0x1
DECL|macro|SYNC_TRAFFIC_ON
mdefine_line|#define&t;SYNC_TRAFFIC_ON&t;&t;0x2
multiline_comment|/* big FIFO memory */
DECL|macro|RX_FIFO_SPACE
mdefine_line|#define&t;RX_FIFO_SPACE&t;&t;0x4000 - RX_FIFO_OFF
DECL|macro|TX_FIFO_SPACE
mdefine_line|#define&t;TX_FIFO_SPACE&t;&t;0x4000
DECL|macro|TX_SMALL_FIFO
mdefine_line|#define&t;TX_SMALL_FIFO&t;&t;0x0900
DECL|macro|TX_MEDIUM_FIFO
mdefine_line|#define&t;TX_MEDIUM_FIFO&t;&t;TX_FIFO_SPACE / 2&t;
DECL|macro|TX_LARGE_FIFO
mdefine_line|#define&t;TX_LARGE_FIFO&t;&t;TX_FIFO_SPACE - TX_SMALL_FIFO&t;
DECL|macro|RX_SMALL_FIFO
mdefine_line|#define&t;RX_SMALL_FIFO&t;&t;0x0900
DECL|macro|RX_LARGE_FIFO
mdefine_line|#define&t;RX_LARGE_FIFO&t;&t;RX_FIFO_SPACE - RX_SMALL_FIFO&t;
DECL|struct|s_smt_fifo_conf
r_struct
id|s_smt_fifo_conf
(brace
DECL|member|rbc_ram_start
id|u_short
id|rbc_ram_start
suffix:semicolon
multiline_comment|/* FIFO start address */
DECL|member|rbc_ram_end
id|u_short
id|rbc_ram_end
suffix:semicolon
multiline_comment|/* FIFO size */
DECL|member|rx1_fifo_start
id|u_short
id|rx1_fifo_start
suffix:semicolon
multiline_comment|/* rx queue start address */
DECL|member|rx1_fifo_size
id|u_short
id|rx1_fifo_size
suffix:semicolon
multiline_comment|/* rx queue size */
DECL|member|rx2_fifo_start
id|u_short
id|rx2_fifo_start
suffix:semicolon
multiline_comment|/* rx queue start address */
DECL|member|rx2_fifo_size
id|u_short
id|rx2_fifo_size
suffix:semicolon
multiline_comment|/* rx queue size */
DECL|member|tx_s_start
id|u_short
id|tx_s_start
suffix:semicolon
multiline_comment|/* sync queue start address */
DECL|member|tx_s_size
id|u_short
id|tx_s_size
suffix:semicolon
multiline_comment|/* sync queue size */
DECL|member|tx_a0_start
id|u_short
id|tx_a0_start
suffix:semicolon
multiline_comment|/* async queue A0 start address */
DECL|member|tx_a0_size
id|u_short
id|tx_a0_size
suffix:semicolon
multiline_comment|/* async queue A0 size */
DECL|member|fifo_config_mode
id|u_short
id|fifo_config_mode
suffix:semicolon
multiline_comment|/* FIFO configuration mode */
)brace
suffix:semicolon
DECL|macro|FM_ADDRX
mdefine_line|#define FM_ADDRX&t;(FM_ADDET|FM_EXGPA0|FM_EXGPA1)
DECL|struct|s_smt_fp
r_struct
id|s_smt_fp
(brace
DECL|member|mdr2init
id|u_short
id|mdr2init
suffix:semicolon
multiline_comment|/* mode register 2 init value */
DECL|member|mdr3init
id|u_short
id|mdr3init
suffix:semicolon
multiline_comment|/* mode register 3 init value */
DECL|member|frselreg_init
id|u_short
id|frselreg_init
suffix:semicolon
multiline_comment|/* frame selection register init val */
DECL|member|rx_mode
id|u_short
id|rx_mode
suffix:semicolon
multiline_comment|/* address mode broad/multi/promisc */
DECL|member|nsa_mode
id|u_short
id|nsa_mode
suffix:semicolon
DECL|member|rx_prom
id|u_short
id|rx_prom
suffix:semicolon
DECL|member|exgpa
id|u_short
id|exgpa
suffix:semicolon
DECL|member|err_stats
r_struct
id|err_st
id|err_stats
suffix:semicolon
multiline_comment|/* error statistics */
multiline_comment|/*&n;&t; * MAC buffers&n;&t; */
DECL|struct|fddi_mac_sf
r_struct
id|fddi_mac_sf
(brace
multiline_comment|/* special frame build buffer */
DECL|member|mac_fc
id|u_char
id|mac_fc
suffix:semicolon
DECL|member|mac_dest
r_struct
id|fddi_addr
id|mac_dest
suffix:semicolon
DECL|member|mac_source
r_struct
id|fddi_addr
id|mac_source
suffix:semicolon
DECL|member|mac_info
id|u_char
id|mac_info
(braket
l_int|0x20
)braket
suffix:semicolon
DECL|member|mac_sfb
)brace
id|mac_sfb
suffix:semicolon
multiline_comment|/*&n;&t; * queues&n;&t; */
DECL|macro|QUEUE_S
mdefine_line|#define QUEUE_S&t;&t;&t;0
DECL|macro|QUEUE_A0
mdefine_line|#define QUEUE_A0&t;&t;1
DECL|macro|QUEUE_R1
mdefine_line|#define QUEUE_R1&t;&t;0
DECL|macro|QUEUE_R2
mdefine_line|#define QUEUE_R2&t;&t;1
DECL|macro|USED_QUEUES
mdefine_line|#define USED_QUEUES&t;&t;2
multiline_comment|/*&n;&t; * queue pointers; points to the queue dependent variables&n;&t; */
DECL|member|tx
r_struct
id|s_smt_tx_queue
op_star
id|tx
(braket
id|USED_QUEUES
)braket
suffix:semicolon
DECL|member|rx
r_struct
id|s_smt_rx_queue
op_star
id|rx
(braket
id|USED_QUEUES
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * queue dependent variables&n;&t; */
DECL|member|tx_q
r_struct
id|s_smt_tx_queue
id|tx_q
(braket
id|USED_QUEUES
)braket
suffix:semicolon
DECL|member|rx_q
r_struct
id|s_smt_rx_queue
id|rx_q
(braket
id|USED_QUEUES
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * FIFO configuration struct&n;&t; */
DECL|member|fifo
r_struct
id|s_smt_fifo_conf
id|fifo
suffix:semicolon
multiline_comment|/* last formac status */
DECL|member|s2u
id|u_short
id|s2u
suffix:semicolon
DECL|member|s2l
id|u_short
id|s2l
suffix:semicolon
multiline_comment|/* calculated FORMAC+ reg.addr. */
DECL|member|fm_st1u
id|HW_PTR
id|fm_st1u
suffix:semicolon
DECL|member|fm_st1l
id|HW_PTR
id|fm_st1l
suffix:semicolon
DECL|member|fm_st2u
id|HW_PTR
id|fm_st2u
suffix:semicolon
DECL|member|fm_st2l
id|HW_PTR
id|fm_st2l
suffix:semicolon
DECL|member|fm_st3u
id|HW_PTR
id|fm_st3u
suffix:semicolon
DECL|member|fm_st3l
id|HW_PTR
id|fm_st3l
suffix:semicolon
multiline_comment|/*&n;&t; * multicast table&n;&t; */
DECL|macro|FPMAX_MULTICAST
mdefine_line|#define FPMAX_MULTICAST 32 
DECL|macro|SMT_MAX_MULTI
mdefine_line|#define&t;SMT_MAX_MULTI&t;4
r_struct
(brace
DECL|struct|s_fpmc
r_struct
id|s_fpmc
(brace
DECL|member|a
r_struct
id|fddi_addr
id|a
suffix:semicolon
multiline_comment|/* mc address */
DECL|member|n
id|u_char
id|n
suffix:semicolon
multiline_comment|/* usage counter */
DECL|member|perm
id|u_char
id|perm
suffix:semicolon
multiline_comment|/* flag: permanent */
DECL|member|table
)brace
id|table
(braket
id|FPMAX_MULTICAST
)braket
suffix:semicolon
DECL|member|mc
)brace
id|mc
suffix:semicolon
DECL|member|group_addr
r_struct
id|fddi_addr
id|group_addr
suffix:semicolon
DECL|member|func_addr
id|u_long
id|func_addr
suffix:semicolon
multiline_comment|/* functional address */
DECL|member|smt_slots_used
r_int
id|smt_slots_used
suffix:semicolon
multiline_comment|/* count of table entries for the SMT */
DECL|member|os_slots_used
r_int
id|os_slots_used
suffix:semicolon
multiline_comment|/* count of table entries */
multiline_comment|/* used by the os-specific module */
)brace
suffix:semicolon
multiline_comment|/*&n; * modes for mac_set_rx_mode()&n; */
DECL|macro|RX_ENABLE_ALLMULTI
mdefine_line|#define RX_ENABLE_ALLMULTI&t;1&t;/* enable all multicasts */
DECL|macro|RX_DISABLE_ALLMULTI
mdefine_line|#define RX_DISABLE_ALLMULTI&t;2&t;/* disable &quot;enable all multicasts&quot; */
DECL|macro|RX_ENABLE_PROMISC
mdefine_line|#define RX_ENABLE_PROMISC&t;3&t;/* enable promiscous */
DECL|macro|RX_DISABLE_PROMISC
mdefine_line|#define RX_DISABLE_PROMISC&t;4&t;/* disable promiscous */
DECL|macro|RX_ENABLE_NSA
mdefine_line|#define RX_ENABLE_NSA&t;&t;5&t;/* enable reception of NSA frames */
DECL|macro|RX_DISABLE_NSA
mdefine_line|#define RX_DISABLE_NSA&t;&t;6&t;/* disable reception of NSA frames */
multiline_comment|/*&n; * support for byte reversal in AIX&n; * (descriptors and pointers must be byte reversed in memory&n; *  CPU is big endian; M-Channel is little endian)&n; */
macro_line|#ifdef&t;AIX
DECL|macro|MDR_REV
mdefine_line|#define MDR_REV
DECL|macro|AIX_REVERSE
mdefine_line|#define&t;AIX_REVERSE(x)&t;&t;((((x)&lt;&lt;24L)&amp;0xff000000L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&lt;&lt; 8L)&amp;0x00ff0000L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&gt;&gt; 8L)&amp;0x0000ff00L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&gt;&gt;24L)&amp;0x000000ffL))
macro_line|#else
macro_line|#ifndef AIX_REVERSE
DECL|macro|AIX_REVERSE
mdefine_line|#define&t;AIX_REVERSE(x)&t;(x)
macro_line|#endif
macro_line|#endif
macro_line|#ifdef&t;MDR_REV&t;
DECL|macro|MDR_REVERSE
mdefine_line|#define&t;MDR_REVERSE(x)&t;&t;((((x)&lt;&lt;24L)&amp;0xff000000L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&lt;&lt; 8L)&amp;0x00ff0000L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&gt;&gt; 8L)&amp;0x0000ff00L)&t;+&t;&bslash;&n;&t;&t;&t;&t; (((x)&gt;&gt;24L)&amp;0x000000ffL))
macro_line|#else
macro_line|#ifndef MDR_REVERSE
DECL|macro|MDR_REVERSE
mdefine_line|#define&t;MDR_REVERSE(x)&t;(x)
macro_line|#endif
macro_line|#endif
macro_line|#endif
eof
