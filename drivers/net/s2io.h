multiline_comment|/************************************************************************&n; * s2io.h: A Linux PCI-X Ethernet driver for S2IO 10GbE Server NIC&n; * Copyright 2002 Raghavendra Koushik (raghavendra.koushik@s2io.com)&n;&n; * This software may be used and distributed according to the terms of&n; * the GNU General Public License (GPL), incorporated herein by reference.&n; * Drivers based on or derived from this code fall under the GPL and must&n; * retain the authorship, copyright and license notice.  This file is not&n; * a complete program and may only be used when the entire operating&n; * system is licensed under the GPL.&n; * See the file COPYING in this distribution for more information.&n; ************************************************************************/
macro_line|#ifndef _S2IO_H
DECL|macro|_S2IO_H
mdefine_line|#define _S2IO_H
DECL|macro|TBD
mdefine_line|#define TBD 0
DECL|macro|BIT
mdefine_line|#define BIT(loc)&t;&t;(0x8000000000000000ULL &gt;&gt; (loc))
DECL|macro|vBIT
mdefine_line|#define vBIT(val, loc, sz)&t;(((u64)val) &lt;&lt; (64-loc-sz))
macro_line|#ifndef BOOL
DECL|macro|BOOL
mdefine_line|#define BOOL    int
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE    1
DECL|macro|FALSE
mdefine_line|#define FALSE   0
macro_line|#endif
DECL|macro|SUCCESS
macro_line|#undef SUCCESS
DECL|macro|SUCCESS
mdefine_line|#define SUCCESS 0
DECL|macro|FAILURE
mdefine_line|#define FAILURE -1
multiline_comment|/* Maximum outstanding splits to be configured into xena. */
DECL|enum|xena_max_outstanding_splits
r_typedef
r_enum
id|xena_max_outstanding_splits
(brace
DECL|enumerator|XENA_ONE_SPLIT_TRANSACTION
id|XENA_ONE_SPLIT_TRANSACTION
op_assign
l_int|0
comma
DECL|enumerator|XENA_TWO_SPLIT_TRANSACTION
id|XENA_TWO_SPLIT_TRANSACTION
op_assign
l_int|1
comma
DECL|enumerator|XENA_THREE_SPLIT_TRANSACTION
id|XENA_THREE_SPLIT_TRANSACTION
op_assign
l_int|2
comma
DECL|enumerator|XENA_FOUR_SPLIT_TRANSACTION
id|XENA_FOUR_SPLIT_TRANSACTION
op_assign
l_int|3
comma
DECL|enumerator|XENA_EIGHT_SPLIT_TRANSACTION
id|XENA_EIGHT_SPLIT_TRANSACTION
op_assign
l_int|4
comma
DECL|enumerator|XENA_TWELVE_SPLIT_TRANSACTION
id|XENA_TWELVE_SPLIT_TRANSACTION
op_assign
l_int|5
comma
DECL|enumerator|XENA_SIXTEEN_SPLIT_TRANSACTION
id|XENA_SIXTEEN_SPLIT_TRANSACTION
op_assign
l_int|6
comma
DECL|enumerator|XENA_THIRTYTWO_SPLIT_TRANSACTION
id|XENA_THIRTYTWO_SPLIT_TRANSACTION
op_assign
l_int|7
DECL|typedef|xena_max_outstanding_splits
)brace
id|xena_max_outstanding_splits
suffix:semicolon
DECL|macro|XENA_MAX_OUTSTANDING_SPLITS
mdefine_line|#define XENA_MAX_OUTSTANDING_SPLITS(n) (n &lt;&lt; 4)
multiline_comment|/*  OS concerned variables and constants */
DECL|macro|WATCH_DOG_TIMEOUT
mdefine_line|#define WATCH_DOG_TIMEOUT   &t;5*HZ
DECL|macro|EFILL
mdefine_line|#define EFILL       &t;&t;&t;0x1234
DECL|macro|ALIGN_SIZE
mdefine_line|#define ALIGN_SIZE  &t;&t;&t;127
DECL|macro|PCIX_COMMAND_REGISTER
mdefine_line|#define&t;PCIX_COMMAND_REGISTER&t;0x62
multiline_comment|/*&n; * Debug related variables.&n; */
DECL|macro|DEBUG_ON
mdefine_line|#define DEBUG_ON TRUE
multiline_comment|/* different debug levels. */
DECL|macro|ERR_DBG
mdefine_line|#define&t;ERR_DBG&t;&t;0
DECL|macro|INIT_DBG
mdefine_line|#define&t;INIT_DBG&t;1
DECL|macro|INFO_DBG
mdefine_line|#define&t;INFO_DBG&t;2
DECL|macro|TX_DBG
mdefine_line|#define&t;TX_DBG&t;&t;3
DECL|macro|INTR_DBG
mdefine_line|#define&t;INTR_DBG&t;4
multiline_comment|/* Global variable that defines the present debug level of the driver. */
DECL|variable|debug_level
r_int
id|debug_level
op_assign
id|ERR_DBG
suffix:semicolon
multiline_comment|/* Default level. */
multiline_comment|/* DEBUG message print. */
DECL|macro|DBG_PRINT
mdefine_line|#define DBG_PRINT(dbg_level, args...)  if(!(debug_level&lt;dbg_level)) printk(args)
multiline_comment|/* Protocol assist features of the NIC */
DECL|macro|L3_CKSUM_OK
mdefine_line|#define L3_CKSUM_OK 0xFFFF
DECL|macro|L4_CKSUM_OK
mdefine_line|#define L4_CKSUM_OK 0xFFFF
DECL|macro|S2IO_JUMBO_SIZE
mdefine_line|#define S2IO_JUMBO_SIZE 9600
multiline_comment|/* The statistics block of Xena */
DECL|struct|stat_block
r_typedef
r_struct
id|stat_block
(brace
macro_line|#ifdef  __BIG_ENDIAN
multiline_comment|/* Tx MAC statistics counters. */
DECL|member|tmac_frms
id|u32
id|tmac_frms
suffix:semicolon
DECL|member|tmac_data_octets
id|u32
id|tmac_data_octets
suffix:semicolon
DECL|member|tmac_drop_frms
id|u64
id|tmac_drop_frms
suffix:semicolon
DECL|member|tmac_mcst_frms
id|u32
id|tmac_mcst_frms
suffix:semicolon
DECL|member|tmac_bcst_frms
id|u32
id|tmac_bcst_frms
suffix:semicolon
DECL|member|tmac_pause_ctrl_frms
id|u64
id|tmac_pause_ctrl_frms
suffix:semicolon
DECL|member|tmac_ttl_octets
id|u32
id|tmac_ttl_octets
suffix:semicolon
DECL|member|tmac_ucst_frms
id|u32
id|tmac_ucst_frms
suffix:semicolon
DECL|member|tmac_nucst_frms
id|u32
id|tmac_nucst_frms
suffix:semicolon
DECL|member|tmac_any_err_frms
id|u32
id|tmac_any_err_frms
suffix:semicolon
DECL|member|tmac_ttl_less_fb_octets
id|u64
id|tmac_ttl_less_fb_octets
suffix:semicolon
DECL|member|tmac_vld_ip_octets
id|u64
id|tmac_vld_ip_octets
suffix:semicolon
DECL|member|tmac_vld_ip
id|u32
id|tmac_vld_ip
suffix:semicolon
DECL|member|tmac_drop_ip
id|u32
id|tmac_drop_ip
suffix:semicolon
DECL|member|tmac_icmp
id|u32
id|tmac_icmp
suffix:semicolon
DECL|member|tmac_rst_tcp
id|u32
id|tmac_rst_tcp
suffix:semicolon
DECL|member|tmac_tcp
id|u64
id|tmac_tcp
suffix:semicolon
DECL|member|tmac_udp
id|u32
id|tmac_udp
suffix:semicolon
DECL|member|reserved_0
id|u32
id|reserved_0
suffix:semicolon
multiline_comment|/* Rx MAC Statistics counters. */
DECL|member|rmac_vld_frms
id|u32
id|rmac_vld_frms
suffix:semicolon
DECL|member|rmac_data_octets
id|u32
id|rmac_data_octets
suffix:semicolon
DECL|member|rmac_fcs_err_frms
id|u64
id|rmac_fcs_err_frms
suffix:semicolon
DECL|member|rmac_drop_frms
id|u64
id|rmac_drop_frms
suffix:semicolon
DECL|member|rmac_vld_mcst_frms
id|u32
id|rmac_vld_mcst_frms
suffix:semicolon
DECL|member|rmac_vld_bcst_frms
id|u32
id|rmac_vld_bcst_frms
suffix:semicolon
DECL|member|rmac_in_rng_len_err_frms
id|u32
id|rmac_in_rng_len_err_frms
suffix:semicolon
DECL|member|rmac_out_rng_len_err_frms
id|u32
id|rmac_out_rng_len_err_frms
suffix:semicolon
DECL|member|rmac_long_frms
id|u64
id|rmac_long_frms
suffix:semicolon
DECL|member|rmac_pause_ctrl_frms
id|u64
id|rmac_pause_ctrl_frms
suffix:semicolon
DECL|member|rmac_unsup_ctrl_frms
id|u64
id|rmac_unsup_ctrl_frms
suffix:semicolon
DECL|member|rmac_ttl_octets
id|u32
id|rmac_ttl_octets
suffix:semicolon
DECL|member|rmac_accepted_ucst_frms
id|u32
id|rmac_accepted_ucst_frms
suffix:semicolon
DECL|member|rmac_accepted_nucst_frms
id|u32
id|rmac_accepted_nucst_frms
suffix:semicolon
DECL|member|rmac_discarded_frms
id|u32
id|rmac_discarded_frms
suffix:semicolon
DECL|member|rmac_drop_events
id|u32
id|rmac_drop_events
suffix:semicolon
DECL|member|reserved_1
id|u32
id|reserved_1
suffix:semicolon
DECL|member|rmac_ttl_less_fb_octets
id|u64
id|rmac_ttl_less_fb_octets
suffix:semicolon
DECL|member|rmac_ttl_frms
id|u64
id|rmac_ttl_frms
suffix:semicolon
DECL|member|reserved_2
id|u64
id|reserved_2
suffix:semicolon
DECL|member|reserved_3
id|u32
id|reserved_3
suffix:semicolon
DECL|member|rmac_usized_frms
id|u32
id|rmac_usized_frms
suffix:semicolon
DECL|member|rmac_osized_frms
id|u32
id|rmac_osized_frms
suffix:semicolon
DECL|member|rmac_frag_frms
id|u32
id|rmac_frag_frms
suffix:semicolon
DECL|member|rmac_jabber_frms
id|u32
id|rmac_jabber_frms
suffix:semicolon
DECL|member|reserved_4
id|u32
id|reserved_4
suffix:semicolon
DECL|member|rmac_ttl_64_frms
id|u64
id|rmac_ttl_64_frms
suffix:semicolon
DECL|member|rmac_ttl_65_127_frms
id|u64
id|rmac_ttl_65_127_frms
suffix:semicolon
DECL|member|reserved_5
id|u64
id|reserved_5
suffix:semicolon
DECL|member|rmac_ttl_128_255_frms
id|u64
id|rmac_ttl_128_255_frms
suffix:semicolon
DECL|member|rmac_ttl_256_511_frms
id|u64
id|rmac_ttl_256_511_frms
suffix:semicolon
DECL|member|reserved_6
id|u64
id|reserved_6
suffix:semicolon
DECL|member|rmac_ttl_512_1023_frms
id|u64
id|rmac_ttl_512_1023_frms
suffix:semicolon
DECL|member|rmac_ttl_1024_1518_frms
id|u64
id|rmac_ttl_1024_1518_frms
suffix:semicolon
DECL|member|reserved_7
id|u32
id|reserved_7
suffix:semicolon
DECL|member|rmac_ip
id|u32
id|rmac_ip
suffix:semicolon
DECL|member|rmac_ip_octets
id|u64
id|rmac_ip_octets
suffix:semicolon
DECL|member|rmac_hdr_err_ip
id|u32
id|rmac_hdr_err_ip
suffix:semicolon
DECL|member|rmac_drop_ip
id|u32
id|rmac_drop_ip
suffix:semicolon
DECL|member|rmac_icmp
id|u32
id|rmac_icmp
suffix:semicolon
DECL|member|reserved_8
id|u32
id|reserved_8
suffix:semicolon
DECL|member|rmac_tcp
id|u64
id|rmac_tcp
suffix:semicolon
DECL|member|rmac_udp
id|u32
id|rmac_udp
suffix:semicolon
DECL|member|rmac_err_drp_udp
id|u32
id|rmac_err_drp_udp
suffix:semicolon
DECL|member|rmac_xgmii_err_sym
id|u64
id|rmac_xgmii_err_sym
suffix:semicolon
DECL|member|rmac_frms_q0
id|u64
id|rmac_frms_q0
suffix:semicolon
DECL|member|rmac_frms_q1
id|u64
id|rmac_frms_q1
suffix:semicolon
DECL|member|rmac_frms_q2
id|u64
id|rmac_frms_q2
suffix:semicolon
DECL|member|rmac_frms_q3
id|u64
id|rmac_frms_q3
suffix:semicolon
DECL|member|rmac_frms_q4
id|u64
id|rmac_frms_q4
suffix:semicolon
DECL|member|rmac_frms_q5
id|u64
id|rmac_frms_q5
suffix:semicolon
DECL|member|rmac_frms_q6
id|u64
id|rmac_frms_q6
suffix:semicolon
DECL|member|rmac_frms_q7
id|u64
id|rmac_frms_q7
suffix:semicolon
DECL|member|rmac_full_q0
id|u16
id|rmac_full_q0
suffix:semicolon
DECL|member|rmac_full_q1
id|u16
id|rmac_full_q1
suffix:semicolon
DECL|member|rmac_full_q2
id|u16
id|rmac_full_q2
suffix:semicolon
DECL|member|rmac_full_q3
id|u16
id|rmac_full_q3
suffix:semicolon
DECL|member|rmac_full_q4
id|u16
id|rmac_full_q4
suffix:semicolon
DECL|member|rmac_full_q5
id|u16
id|rmac_full_q5
suffix:semicolon
DECL|member|rmac_full_q6
id|u16
id|rmac_full_q6
suffix:semicolon
DECL|member|rmac_full_q7
id|u16
id|rmac_full_q7
suffix:semicolon
DECL|member|rmac_pause_cnt
id|u32
id|rmac_pause_cnt
suffix:semicolon
DECL|member|reserved_9
id|u32
id|reserved_9
suffix:semicolon
DECL|member|rmac_xgmii_data_err_cnt
id|u64
id|rmac_xgmii_data_err_cnt
suffix:semicolon
DECL|member|rmac_xgmii_ctrl_err_cnt
id|u64
id|rmac_xgmii_ctrl_err_cnt
suffix:semicolon
DECL|member|rmac_accepted_ip
id|u32
id|rmac_accepted_ip
suffix:semicolon
DECL|member|rmac_err_tcp
id|u32
id|rmac_err_tcp
suffix:semicolon
multiline_comment|/* PCI/PCI-X Read transaction statistics. */
DECL|member|rd_req_cnt
id|u32
id|rd_req_cnt
suffix:semicolon
DECL|member|new_rd_req_cnt
id|u32
id|new_rd_req_cnt
suffix:semicolon
DECL|member|new_rd_req_rtry_cnt
id|u32
id|new_rd_req_rtry_cnt
suffix:semicolon
DECL|member|rd_rtry_cnt
id|u32
id|rd_rtry_cnt
suffix:semicolon
DECL|member|wr_rtry_rd_ack_cnt
id|u32
id|wr_rtry_rd_ack_cnt
suffix:semicolon
multiline_comment|/* PCI/PCI-X write transaction statistics. */
DECL|member|wr_req_cnt
id|u32
id|wr_req_cnt
suffix:semicolon
DECL|member|new_wr_req_cnt
id|u32
id|new_wr_req_cnt
suffix:semicolon
DECL|member|new_wr_req_rtry_cnt
id|u32
id|new_wr_req_rtry_cnt
suffix:semicolon
DECL|member|wr_rtry_cnt
id|u32
id|wr_rtry_cnt
suffix:semicolon
DECL|member|wr_disc_cnt
id|u32
id|wr_disc_cnt
suffix:semicolon
DECL|member|rd_rtry_wr_ack_cnt
id|u32
id|rd_rtry_wr_ack_cnt
suffix:semicolon
multiline_comment|/*&t;DMA Transaction statistics. */
DECL|member|txp_wr_cnt
id|u32
id|txp_wr_cnt
suffix:semicolon
DECL|member|txd_rd_cnt
id|u32
id|txd_rd_cnt
suffix:semicolon
DECL|member|txd_wr_cnt
id|u32
id|txd_wr_cnt
suffix:semicolon
DECL|member|rxd_rd_cnt
id|u32
id|rxd_rd_cnt
suffix:semicolon
DECL|member|rxd_wr_cnt
id|u32
id|rxd_wr_cnt
suffix:semicolon
DECL|member|txf_rd_cnt
id|u32
id|txf_rd_cnt
suffix:semicolon
DECL|member|rxf_wr_cnt
id|u32
id|rxf_wr_cnt
suffix:semicolon
macro_line|#else
multiline_comment|/* Tx MAC statistics counters. */
id|u32
id|tmac_data_octets
suffix:semicolon
id|u32
id|tmac_frms
suffix:semicolon
id|u64
id|tmac_drop_frms
suffix:semicolon
id|u32
id|tmac_bcst_frms
suffix:semicolon
id|u32
id|tmac_mcst_frms
suffix:semicolon
id|u64
id|tmac_pause_ctrl_frms
suffix:semicolon
id|u32
id|tmac_ucst_frms
suffix:semicolon
id|u32
id|tmac_ttl_octets
suffix:semicolon
id|u32
id|tmac_any_err_frms
suffix:semicolon
id|u32
id|tmac_nucst_frms
suffix:semicolon
id|u64
id|tmac_ttl_less_fb_octets
suffix:semicolon
id|u64
id|tmac_vld_ip_octets
suffix:semicolon
id|u32
id|tmac_drop_ip
suffix:semicolon
id|u32
id|tmac_vld_ip
suffix:semicolon
id|u32
id|tmac_rst_tcp
suffix:semicolon
id|u32
id|tmac_icmp
suffix:semicolon
id|u64
id|tmac_tcp
suffix:semicolon
id|u32
id|reserved_0
suffix:semicolon
id|u32
id|tmac_udp
suffix:semicolon
multiline_comment|/* Rx MAC Statistics counters. */
id|u32
id|rmac_data_octets
suffix:semicolon
id|u32
id|rmac_vld_frms
suffix:semicolon
id|u64
id|rmac_fcs_err_frms
suffix:semicolon
id|u64
id|rmac_drop_frms
suffix:semicolon
id|u32
id|rmac_vld_bcst_frms
suffix:semicolon
id|u32
id|rmac_vld_mcst_frms
suffix:semicolon
id|u32
id|rmac_out_rng_len_err_frms
suffix:semicolon
id|u32
id|rmac_in_rng_len_err_frms
suffix:semicolon
id|u64
id|rmac_long_frms
suffix:semicolon
id|u64
id|rmac_pause_ctrl_frms
suffix:semicolon
id|u64
id|rmac_unsup_ctrl_frms
suffix:semicolon
id|u32
id|rmac_accepted_ucst_frms
suffix:semicolon
id|u32
id|rmac_ttl_octets
suffix:semicolon
id|u32
id|rmac_discarded_frms
suffix:semicolon
id|u32
id|rmac_accepted_nucst_frms
suffix:semicolon
id|u32
id|reserved_1
suffix:semicolon
id|u32
id|rmac_drop_events
suffix:semicolon
id|u64
id|rmac_ttl_less_fb_octets
suffix:semicolon
id|u64
id|rmac_ttl_frms
suffix:semicolon
id|u64
id|reserved_2
suffix:semicolon
id|u32
id|rmac_usized_frms
suffix:semicolon
id|u32
id|reserved_3
suffix:semicolon
id|u32
id|rmac_frag_frms
suffix:semicolon
id|u32
id|rmac_osized_frms
suffix:semicolon
id|u32
id|reserved_4
suffix:semicolon
id|u32
id|rmac_jabber_frms
suffix:semicolon
id|u64
id|rmac_ttl_64_frms
suffix:semicolon
id|u64
id|rmac_ttl_65_127_frms
suffix:semicolon
id|u64
id|reserved_5
suffix:semicolon
id|u64
id|rmac_ttl_128_255_frms
suffix:semicolon
id|u64
id|rmac_ttl_256_511_frms
suffix:semicolon
id|u64
id|reserved_6
suffix:semicolon
id|u64
id|rmac_ttl_512_1023_frms
suffix:semicolon
id|u64
id|rmac_ttl_1024_1518_frms
suffix:semicolon
id|u32
id|rmac_ip
suffix:semicolon
id|u32
id|reserved_7
suffix:semicolon
id|u64
id|rmac_ip_octets
suffix:semicolon
id|u32
id|rmac_drop_ip
suffix:semicolon
id|u32
id|rmac_hdr_err_ip
suffix:semicolon
id|u32
id|reserved_8
suffix:semicolon
id|u32
id|rmac_icmp
suffix:semicolon
id|u64
id|rmac_tcp
suffix:semicolon
id|u32
id|rmac_err_drp_udp
suffix:semicolon
id|u32
id|rmac_udp
suffix:semicolon
id|u64
id|rmac_xgmii_err_sym
suffix:semicolon
id|u64
id|rmac_frms_q0
suffix:semicolon
id|u64
id|rmac_frms_q1
suffix:semicolon
id|u64
id|rmac_frms_q2
suffix:semicolon
id|u64
id|rmac_frms_q3
suffix:semicolon
id|u64
id|rmac_frms_q4
suffix:semicolon
id|u64
id|rmac_frms_q5
suffix:semicolon
id|u64
id|rmac_frms_q6
suffix:semicolon
id|u64
id|rmac_frms_q7
suffix:semicolon
id|u16
id|rmac_full_q3
suffix:semicolon
id|u16
id|rmac_full_q2
suffix:semicolon
id|u16
id|rmac_full_q1
suffix:semicolon
id|u16
id|rmac_full_q0
suffix:semicolon
id|u16
id|rmac_full_q7
suffix:semicolon
id|u16
id|rmac_full_q6
suffix:semicolon
id|u16
id|rmac_full_q5
suffix:semicolon
id|u16
id|rmac_full_q4
suffix:semicolon
id|u32
id|reserved_9
suffix:semicolon
id|u32
id|rmac_pause_cnt
suffix:semicolon
id|u64
id|rmac_xgmii_data_err_cnt
suffix:semicolon
id|u64
id|rmac_xgmii_ctrl_err_cnt
suffix:semicolon
id|u32
id|rmac_err_tcp
suffix:semicolon
id|u32
id|rmac_accepted_ip
suffix:semicolon
multiline_comment|/* PCI/PCI-X Read transaction statistics. */
id|u32
id|new_rd_req_cnt
suffix:semicolon
id|u32
id|rd_req_cnt
suffix:semicolon
id|u32
id|rd_rtry_cnt
suffix:semicolon
id|u32
id|new_rd_req_rtry_cnt
suffix:semicolon
multiline_comment|/* PCI/PCI-X Write/Read transaction statistics. */
id|u32
id|wr_req_cnt
suffix:semicolon
id|u32
id|wr_rtry_rd_ack_cnt
suffix:semicolon
id|u32
id|new_wr_req_rtry_cnt
suffix:semicolon
id|u32
id|new_wr_req_cnt
suffix:semicolon
id|u32
id|wr_disc_cnt
suffix:semicolon
id|u32
id|wr_rtry_cnt
suffix:semicolon
multiline_comment|/*&t;PCI/PCI-X Write / DMA Transaction statistics. */
id|u32
id|txp_wr_cnt
suffix:semicolon
id|u32
id|rd_rtry_wr_ack_cnt
suffix:semicolon
id|u32
id|txd_wr_cnt
suffix:semicolon
id|u32
id|txd_rd_cnt
suffix:semicolon
id|u32
id|rxd_wr_cnt
suffix:semicolon
id|u32
id|rxd_rd_cnt
suffix:semicolon
id|u32
id|rxf_wr_cnt
suffix:semicolon
id|u32
id|txf_rd_cnt
suffix:semicolon
macro_line|#endif
DECL|typedef|StatInfo_t
)brace
id|StatInfo_t
suffix:semicolon
multiline_comment|/* Structures representing different init time configuration&n; * parameters of the NIC.&n; */
multiline_comment|/* Maintains Per FIFO related information. */
DECL|struct|tx_fifo_config
r_typedef
r_struct
id|tx_fifo_config
(brace
DECL|macro|MAX_AVAILABLE_TXDS
mdefine_line|#define&t;MAX_AVAILABLE_TXDS&t;8192
DECL|member|FifoLen
id|u32
id|FifoLen
suffix:semicolon
multiline_comment|/* specifies len of FIFO upto 8192, ie no of TxDLs */
multiline_comment|/* Priority definition */
DECL|macro|TX_FIFO_PRI_0
mdefine_line|#define TX_FIFO_PRI_0               0&t;/*Highest */
DECL|macro|TX_FIFO_PRI_1
mdefine_line|#define TX_FIFO_PRI_1               1
DECL|macro|TX_FIFO_PRI_2
mdefine_line|#define TX_FIFO_PRI_2               2
DECL|macro|TX_FIFO_PRI_3
mdefine_line|#define TX_FIFO_PRI_3               3
DECL|macro|TX_FIFO_PRI_4
mdefine_line|#define TX_FIFO_PRI_4               4
DECL|macro|TX_FIFO_PRI_5
mdefine_line|#define TX_FIFO_PRI_5               5
DECL|macro|TX_FIFO_PRI_6
mdefine_line|#define TX_FIFO_PRI_6               6
DECL|macro|TX_FIFO_PRI_7
mdefine_line|#define TX_FIFO_PRI_7               7&t;/*lowest */
DECL|member|FifoPriority
id|u8
id|FifoPriority
suffix:semicolon
multiline_comment|/* specifies pointer level for FIFO */
multiline_comment|/* user should not set twos fifos with same pri */
DECL|member|fNoSnoop
id|u8
id|fNoSnoop
suffix:semicolon
DECL|macro|NO_SNOOP_TXD
mdefine_line|#define NO_SNOOP_TXD                0x01
DECL|macro|NO_SNOOP_TXD_BUFFER
mdefine_line|#define NO_SNOOP_TXD_BUFFER          0x02
DECL|typedef|tx_fifo_config_t
)brace
id|tx_fifo_config_t
suffix:semicolon
multiline_comment|/* Maintains per Ring related information */
DECL|struct|rx_ring_config
r_typedef
r_struct
id|rx_ring_config
(brace
DECL|member|NumRxd
id|u32
id|NumRxd
suffix:semicolon
multiline_comment|/*No of RxDs per Rx Ring */
DECL|macro|RX_RING_PRI_0
mdefine_line|#define RX_RING_PRI_0               0&t;/* highest */
DECL|macro|RX_RING_PRI_1
mdefine_line|#define RX_RING_PRI_1               1
DECL|macro|RX_RING_PRI_2
mdefine_line|#define RX_RING_PRI_2               2
DECL|macro|RX_RING_PRI_3
mdefine_line|#define RX_RING_PRI_3               3
DECL|macro|RX_RING_PRI_4
mdefine_line|#define RX_RING_PRI_4               4
DECL|macro|RX_RING_PRI_5
mdefine_line|#define RX_RING_PRI_5               5
DECL|macro|RX_RING_PRI_6
mdefine_line|#define RX_RING_PRI_6               6
DECL|macro|RX_RING_PRI_7
mdefine_line|#define RX_RING_PRI_7               7&t;/* lowest */
DECL|member|RingPriority
id|u8
id|RingPriority
suffix:semicolon
multiline_comment|/*Specifies service priority of ring */
multiline_comment|/* OSM should not set any two rings with same priority */
DECL|member|RingOrg
id|u8
id|RingOrg
suffix:semicolon
multiline_comment|/*Organization of ring */
DECL|macro|RING_ORG_BUFF1
mdefine_line|#define RING_ORG_BUFF1           0x01
DECL|macro|RX_RING_ORG_BUFF3
mdefine_line|#define RX_RING_ORG_BUFF3           0x03
DECL|macro|RX_RING_ORG_BUFF5
mdefine_line|#define RX_RING_ORG_BUFF5           0x05
multiline_comment|/* In case of 3 buffer recv. mode, size of three buffers is expected as.. */
DECL|macro|BUFF_SZ_1
mdefine_line|#define BUFF_SZ_1                   22&t;/* ethernet header */
DECL|macro|BUFF_SZ_2
mdefine_line|#define BUFF_SZ_2                   (64+64)&t;/* max. IP+TCP header size */
DECL|macro|BUFF_SZ_3
mdefine_line|#define BUFF_SZ_3                   (1500-20-20)&t;/* TCP payload */
DECL|macro|BUFF_SZ_3_JUMBO
mdefine_line|#define BUFF_SZ_3_JUMBO             (9600-20-20)&t;/* Jumbo TCP payload */
DECL|member|RxdThresh
id|u32
id|RxdThresh
suffix:semicolon
multiline_comment|/*No of used Rxds NIC can store before transfer to host */
DECL|macro|DEFAULT_RXD_THRESHOLD
mdefine_line|#define DEFAULT_RXD_THRESHOLD       0x1&t;/* TODO */
DECL|member|fNoSnoop
id|u8
id|fNoSnoop
suffix:semicolon
DECL|macro|NO_SNOOP_RXD
mdefine_line|#define NO_SNOOP_RXD                0x01
DECL|macro|NO_SNOOP_RXD_BUFFER
mdefine_line|#define NO_SNOOP_RXD_BUFFER         0x02
DECL|member|RxD_BackOff_Interval
id|u32
id|RxD_BackOff_Interval
suffix:semicolon
DECL|macro|RXD_BACKOFF_INTERVAL_DEF
mdefine_line|#define RXD_BACKOFF_INTERVAL_DEF        0x0
DECL|macro|RXD_BACKOFF_INTERVAL_MIN
mdefine_line|#define RXD_BACKOFF_INTERVAL_MIN        0x0
DECL|macro|RXD_BACKOFF_INTERVAL_MAX
mdefine_line|#define RXD_BACKOFF_INTERVAL_MAX        0x0
DECL|typedef|rx_ring_config_t
)brace
id|rx_ring_config_t
suffix:semicolon
multiline_comment|/* This structure provides contains values of the tunable parameters &n; * of the H/W &n; */
DECL|struct|config_param
r_struct
id|config_param
(brace
multiline_comment|/* Tx Side */
DECL|member|TxFIFONum
id|u32
id|TxFIFONum
suffix:semicolon
multiline_comment|/*Number of Tx FIFOs */
DECL|macro|MAX_TX_FIFOS
mdefine_line|#define MAX_TX_FIFOS 8
DECL|member|TxCfg
id|tx_fifo_config_t
id|TxCfg
(braket
id|MAX_TX_FIFOS
)braket
suffix:semicolon
multiline_comment|/*Per-Tx FIFO config */
DECL|member|MaxTxDs
id|u32
id|MaxTxDs
suffix:semicolon
multiline_comment|/*Max no. of Tx buffer descriptor per TxDL */
DECL|member|TxVLANEnable
id|BOOL
id|TxVLANEnable
suffix:semicolon
multiline_comment|/*TRUE: Insert VLAN ID, FALSE: Don&squot;t insert */
DECL|macro|TX_REQ_TIMEOUT_DEFAULT
mdefine_line|#define TX_REQ_TIMEOUT_DEFAULT          0x0
DECL|macro|TX_REQ_TIMEOUT_MIN
mdefine_line|#define TX_REQ_TIMEOUT_MIN              0x0
DECL|macro|TX_REQ_TIMEOUT_MAX
mdefine_line|#define TX_REQ_TIMEOUT_MAX              0x0
DECL|member|TxReqTimeOut
id|u32
id|TxReqTimeOut
suffix:semicolon
DECL|member|TxFlow
id|BOOL
id|TxFlow
suffix:semicolon
multiline_comment|/*Tx flow control enable */
DECL|member|RxFlow
id|BOOL
id|RxFlow
suffix:semicolon
DECL|member|OverrideTxServiceState
id|BOOL
id|OverrideTxServiceState
suffix:semicolon
multiline_comment|/* TRUE: Overide, FALSE: Do not override &n;&t;&t;&t;&t;&t;   Use the new priority information&n;&t;&t;&t;&t;&t;   of service state. It is not recommended&n;&t;&t;&t;&t;&t;   to change but OSM can opt to do so */
DECL|macro|MAX_SERVICE_STATES
mdefine_line|#define MAX_SERVICE_STATES  36
DECL|member|TxServiceState
id|u8
id|TxServiceState
(braket
id|MAX_SERVICE_STATES
)braket
suffix:semicolon
multiline_comment|/* Array element represent &squot;priority&squot; &n;&t; * and array index represents&n;&t; *  &squot;Service state&squot; e.g. &n;&t; *  TxServiceState[3]=7; it means &n;&t; *  Service state 3 is associated &n;&t; *  with priority 7 of a Tx FIFO */
DECL|member|TxIntrType
id|u64
id|TxIntrType
suffix:semicolon
multiline_comment|/* Specifies if Tx Intr is UTILZ or PER_LIST type. */
multiline_comment|/* Rx Side */
DECL|member|RxRingNum
id|u32
id|RxRingNum
suffix:semicolon
multiline_comment|/*Number of receive rings */
DECL|macro|MAX_RX_RINGS
mdefine_line|#define MAX_RX_RINGS 8
DECL|macro|MAX_RX_BLOCKS_PER_RING
mdefine_line|#define MAX_RX_BLOCKS_PER_RING  150
DECL|member|RxCfg
id|rx_ring_config_t
id|RxCfg
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
multiline_comment|/*Per-Rx Ring config */
DECL|member|RxVLANEnable
id|BOOL
id|RxVLANEnable
suffix:semicolon
multiline_comment|/*TRUE: Strip off VLAN tag from the frame,&n;&t;&t;&t;&t;   FALSE: Don&squot;t strip off VLAN tag */
DECL|macro|HEADER_ETHERNET_II_802_3_SIZE
mdefine_line|#define HEADER_ETHERNET_II_802_3_SIZE 14
DECL|macro|HEADER_802_2_SIZE
mdefine_line|#define HEADER_802_2_SIZE              3
DECL|macro|HEADER_SNAP_SIZE
mdefine_line|#define HEADER_SNAP_SIZE               5
DECL|macro|HEADER_VLAN_SIZE
mdefine_line|#define HEADER_VLAN_SIZE               4
DECL|macro|MIN_MTU
mdefine_line|#define MIN_MTU                       46
DECL|macro|MAX_PYLD
mdefine_line|#define MAX_PYLD                    1500
DECL|macro|MAX_MTU
mdefine_line|#define MAX_MTU                     (MAX_PYLD+18)
DECL|macro|MAX_MTU_VLAN
mdefine_line|#define MAX_MTU_VLAN                (MAX_PYLD+22)
DECL|macro|MAX_PYLD_JUMBO
mdefine_line|#define MAX_PYLD_JUMBO              9600
DECL|macro|MAX_MTU_JUMBO
mdefine_line|#define MAX_MTU_JUMBO               (MAX_PYLD_JUMBO+18)
DECL|macro|MAX_MTU_JUMBO_VLAN
mdefine_line|#define MAX_MTU_JUMBO_VLAN          (MAX_PYLD_JUMBO+22)
DECL|member|MTU
id|u32
id|MTU
suffix:semicolon
multiline_comment|/*Maximum Payload */
DECL|member|JumboEnable
id|BOOL
id|JumboEnable
suffix:semicolon
multiline_comment|/*Enable Jumbo frames recv/send */
DECL|member|OverrideRxServiceState
id|BOOL
id|OverrideRxServiceState
suffix:semicolon
multiline_comment|/* TRUE: Overide, FALSE: Do not override &n;&t;&t;&t;&t;&t;   Use the new priority information&n;&t;&t;&t;&t;&t;   of service state. It is not recommended&n;&t;&t;&t;&t;&t;   to change but OSM can opt to do so */
DECL|macro|MAX_SERVICE_STATES
mdefine_line|#define MAX_SERVICE_STATES  36
DECL|member|RxServiceState
id|u8
id|RxServiceState
(braket
id|MAX_SERVICE_STATES
)braket
suffix:semicolon
multiline_comment|/* Array element represent &squot;priority&squot; &n;&t; * and array index represents &n;&t; * &squot;Service state&squot;e.g. &n;&t; * RxServiceState[3]=7; it means &n;&t; * Service state 3 is associated &n;&t; * with priority 7 of a Rx FIFO */
DECL|member|StatAutoRefresh
id|BOOL
id|StatAutoRefresh
suffix:semicolon
multiline_comment|/* When true, StatRefreshTime have valid value */
DECL|member|StatRefreshTime
id|u32
id|StatRefreshTime
suffix:semicolon
multiline_comment|/*Time for refreshing statistics */
DECL|macro|STAT_TRSF_PER_1_SECOND
mdefine_line|#define     STAT_TRSF_PER_1_SECOND      0x208D5
)brace
suffix:semicolon
multiline_comment|/* Structure representing MAC Addrs */
DECL|struct|mac_addr
r_typedef
r_struct
id|mac_addr
(brace
DECL|member|mac_addr
id|u8
id|mac_addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|typedef|macaddr_t
)brace
id|macaddr_t
suffix:semicolon
multiline_comment|/* Structure that represent every FIFO element in the BAR1&n; * Address location. &n; */
DECL|struct|_TxFIFO_element
r_typedef
r_struct
id|_TxFIFO_element
(brace
DECL|member|TxDL_Pointer
id|u64
id|TxDL_Pointer
suffix:semicolon
DECL|member|List_Control
id|u64
id|List_Control
suffix:semicolon
DECL|macro|TX_FIFO_LAST_TXD_NUM
mdefine_line|#define TX_FIFO_LAST_TXD_NUM( val)     vBIT(val,0,8)
DECL|macro|TX_FIFO_FIRST_LIST
mdefine_line|#define TX_FIFO_FIRST_LIST             BIT(14)
DECL|macro|TX_FIFO_LAST_LIST
mdefine_line|#define TX_FIFO_LAST_LIST              BIT(15)
DECL|macro|TX_FIFO_FIRSTNLAST_LIST
mdefine_line|#define TX_FIFO_FIRSTNLAST_LIST        vBIT(3,14,2)
DECL|macro|TX_FIFO_SPECIAL_FUNC
mdefine_line|#define TX_FIFO_SPECIAL_FUNC           BIT(23)
DECL|macro|TX_FIFO_DS_NO_SNOOP
mdefine_line|#define TX_FIFO_DS_NO_SNOOP            BIT(31)
DECL|macro|TX_FIFO_BUFF_NO_SNOOP
mdefine_line|#define TX_FIFO_BUFF_NO_SNOOP          BIT(30)
DECL|typedef|TxFIFO_element_t
)brace
id|TxFIFO_element_t
suffix:semicolon
multiline_comment|/* Tx descriptor structure */
DECL|struct|_TxD
r_typedef
r_struct
id|_TxD
(brace
DECL|member|Control_1
id|u64
id|Control_1
suffix:semicolon
multiline_comment|/* bit mask */
DECL|macro|TXD_LIST_OWN_XENA
mdefine_line|#define TXD_LIST_OWN_XENA       BIT(7)
DECL|macro|TXD_T_CODE
mdefine_line|#define TXD_T_CODE              (BIT(12)|BIT(13)|BIT(14)|BIT(15))
DECL|macro|TXD_T_CODE_OK
mdefine_line|#define TXD_T_CODE_OK(val)      (|(val &amp; TXD_T_CODE))
DECL|macro|GET_TXD_T_CODE
mdefine_line|#define GET_TXD_T_CODE(val)     ((val &amp; TXD_T_CODE)&lt;&lt;12)
DECL|macro|TXD_GATHER_CODE
mdefine_line|#define TXD_GATHER_CODE         (BIT(22) | BIT(23))
DECL|macro|TXD_GATHER_CODE_FIRST
mdefine_line|#define TXD_GATHER_CODE_FIRST   BIT(22)
DECL|macro|TXD_GATHER_CODE_LAST
mdefine_line|#define TXD_GATHER_CODE_LAST    BIT(23)
DECL|macro|TXD_TCP_LSO_EN
mdefine_line|#define TXD_TCP_LSO_EN          BIT(30)
DECL|macro|TXD_UDP_COF_EN
mdefine_line|#define TXD_UDP_COF_EN          BIT(31)
DECL|macro|TXD_TCP_LSO_MSS
mdefine_line|#define TXD_TCP_LSO_MSS(val)    vBIT(val,34,14)
DECL|macro|TXD_BUFFER0_SIZE
mdefine_line|#define TXD_BUFFER0_SIZE(val)   vBIT(val,48,16)
DECL|member|Control_2
id|u64
id|Control_2
suffix:semicolon
DECL|macro|TXD_TX_CKO_CONTROL
mdefine_line|#define TXD_TX_CKO_CONTROL      (BIT(5)|BIT(6)|BIT(7))
DECL|macro|TXD_TX_CKO_IPV4_EN
mdefine_line|#define TXD_TX_CKO_IPV4_EN      BIT(5)
DECL|macro|TXD_TX_CKO_TCP_EN
mdefine_line|#define TXD_TX_CKO_TCP_EN       BIT(6)
DECL|macro|TXD_TX_CKO_UDP_EN
mdefine_line|#define TXD_TX_CKO_UDP_EN       BIT(7)
DECL|macro|TXD_VLAN_ENABLE
mdefine_line|#define TXD_VLAN_ENABLE         BIT(15)
DECL|macro|TXD_VLAN_TAG
mdefine_line|#define TXD_VLAN_TAG(val)       vBIT(val,16,16)
DECL|macro|TXD_INT_NUMBER
mdefine_line|#define TXD_INT_NUMBER(val)     vBIT(val,34,6)
DECL|macro|TXD_INT_TYPE_PER_LIST
mdefine_line|#define TXD_INT_TYPE_PER_LIST   BIT(47)
DECL|macro|TXD_INT_TYPE_UTILZ
mdefine_line|#define TXD_INT_TYPE_UTILZ      BIT(46)
DECL|macro|TXD_SET_MARKER
mdefine_line|#define TXD_SET_MARKER         vBIT(0x6,0,4)
DECL|member|Buffer_Pointer
id|u64
id|Buffer_Pointer
suffix:semicolon
DECL|member|Host_Control
id|u64
id|Host_Control
suffix:semicolon
multiline_comment|/* reserved for host */
DECL|typedef|TxD_t
)brace
id|TxD_t
suffix:semicolon
multiline_comment|/* Rx descriptor structure */
DECL|struct|_RxD_t
r_typedef
r_struct
id|_RxD_t
(brace
DECL|member|Host_Control
id|u64
id|Host_Control
suffix:semicolon
multiline_comment|/* reserved for host */
DECL|member|Control_1
id|u64
id|Control_1
suffix:semicolon
DECL|macro|RXD_OWN_XENA
mdefine_line|#define RXD_OWN_XENA            BIT(7)
DECL|macro|RXD_T_CODE
mdefine_line|#define RXD_T_CODE              (BIT(12)|BIT(13)|BIT(14)|BIT(15))
DECL|macro|RXD_FRAME_PROTO
mdefine_line|#define RXD_FRAME_PROTO         vBIT(0xFFFF,24,8)
DECL|macro|RXD_FRAME_PROTO_IPV4
mdefine_line|#define RXD_FRAME_PROTO_IPV4    BIT(27)
DECL|macro|RXD_FRAME_PROTO_IPV6
mdefine_line|#define RXD_FRAME_PROTO_IPV6    BIT(28)
DECL|macro|RXD_FRAME_PROTO_TCP
mdefine_line|#define RXD_FRAME_PROTO_TCP     BIT(30)
DECL|macro|RXD_FRAME_PROTO_UDP
mdefine_line|#define RXD_FRAME_PROTO_UDP     BIT(31)
DECL|macro|TCP_OR_UDP_FRAME
mdefine_line|#define TCP_OR_UDP_FRAME        (RXD_FRAME_PROTO_TCP | RXD_FRAME_PROTO_UDP)
DECL|macro|RXD_GET_L3_CKSUM
mdefine_line|#define RXD_GET_L3_CKSUM(val)   ((u16)(val&gt;&gt; 16) &amp; 0xFFFF)
DECL|macro|RXD_GET_L4_CKSUM
mdefine_line|#define RXD_GET_L4_CKSUM(val)   ((u16)(val) &amp; 0xFFFF)
DECL|member|Control_2
id|u64
id|Control_2
suffix:semicolon
DECL|macro|MASK_BUFFER0_SIZE
mdefine_line|#define MASK_BUFFER0_SIZE       vBIT(0xFFFF,0,16)
DECL|macro|SET_BUFFER0_SIZE
mdefine_line|#define SET_BUFFER0_SIZE(val)   vBIT(val,0,16)
DECL|macro|MASK_VLAN_TAG
mdefine_line|#define MASK_VLAN_TAG           vBIT(0xFFFF,48,16)
DECL|macro|SET_VLAN_TAG
mdefine_line|#define SET_VLAN_TAG(val)       vBIT(val,48,16)
DECL|macro|SET_NUM_TAG
mdefine_line|#define SET_NUM_TAG(val)       vBIT(val,16,32)
DECL|macro|RXD_GET_BUFFER0_SIZE
mdefine_line|#define RXD_GET_BUFFER0_SIZE(Control_2) (u64)((Control_2 &amp; vBIT(0xFFFF,0,16)))
multiline_comment|/*    &n;#define TXD_GET_BUFFER1_SIZE(Control_2) (u16)((Control_2 &amp; MASK_BUFFER1_SIZE) &gt;&gt; (63-31))  &n;#define TXD_GET_BUFFER2_SIZE(Control_2) (u16)((Control_2 &amp; MASK_BUFFER2_SIZE) &gt;&gt; (63-47))  &n;*/
DECL|member|Buffer0_ptr
id|u64
id|Buffer0_ptr
suffix:semicolon
DECL|typedef|RxD_t
)brace
id|RxD_t
suffix:semicolon
multiline_comment|/* Structure that represents the Rx descriptor block which contains &n; * 128 Rx descriptors.&n; */
DECL|struct|_RxD_block
r_typedef
r_struct
id|_RxD_block
(brace
DECL|macro|MAX_RXDS_PER_BLOCK
mdefine_line|#define MAX_RXDS_PER_BLOCK             127
DECL|member|rxd
id|RxD_t
id|rxd
(braket
id|MAX_RXDS_PER_BLOCK
)braket
suffix:semicolon
DECL|member|reserved_0
id|u64
id|reserved_0
suffix:semicolon
DECL|macro|END_OF_BLOCK
mdefine_line|#define END_OF_BLOCK    0xFEFFFFFFFFFFFFFFULL
DECL|member|reserved_1
id|u64
id|reserved_1
suffix:semicolon
multiline_comment|/* 0xFEFFFFFFFFFFFFFF to mark last Rxd in this blk */
DECL|member|reserved_2_pNext_RxD_block
id|u64
id|reserved_2_pNext_RxD_block
suffix:semicolon
multiline_comment|/*@ Logical ptr to next */
DECL|member|pNext_RxD_Blk_physical
id|u64
id|pNext_RxD_Blk_physical
suffix:semicolon
multiline_comment|/* Buff0_ptr.&n;&t;&t;&t;&t;&t;   In a 32 bit arch the upper 32 bits &n;&t;&t;&t;&t;&t;   should be 0 */
DECL|typedef|RxD_block_t
)brace
id|RxD_block_t
suffix:semicolon
multiline_comment|/* Structure which stores all the MAC control parameters */
multiline_comment|/* This structure stores the offset of the RxD in the ring &n; * from which the Rx Interrupt processor can start picking &n; * up the RxDs for processing.&n; */
DECL|struct|_rx_curr_get_info_t
r_typedef
r_struct
id|_rx_curr_get_info_t
(brace
DECL|member|block_index
id|u32
id|block_index
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|ring_len
id|u32
id|ring_len
suffix:semicolon
DECL|typedef|rx_curr_get_info_t
)brace
id|rx_curr_get_info_t
suffix:semicolon
DECL|typedef|rx_curr_put_info_t
r_typedef
id|rx_curr_get_info_t
id|rx_curr_put_info_t
suffix:semicolon
multiline_comment|/* This structure stores the offset of the TxDl in the FIFO&n; * from which the Tx Interrupt processor can start picking &n; * up the TxDLs for send complete interrupt processing.&n; */
r_typedef
r_struct
(brace
DECL|member|offset
id|u32
id|offset
suffix:semicolon
DECL|member|fifo_len
id|u32
id|fifo_len
suffix:semicolon
DECL|typedef|tx_curr_get_info_t
)brace
id|tx_curr_get_info_t
suffix:semicolon
DECL|typedef|tx_curr_put_info_t
r_typedef
id|tx_curr_get_info_t
id|tx_curr_put_info_t
suffix:semicolon
multiline_comment|/* Infomation related to the Tx and Rx FIFOs and Rings of Xena&n; * is maintained in this structure.&n; */
DECL|struct|mac_info
r_typedef
r_struct
id|mac_info
(brace
multiline_comment|/* rx side stuff */
DECL|member|rxd_ring_mem_sz
id|u32
id|rxd_ring_mem_sz
suffix:semicolon
DECL|member|RxRing
id|RxD_t
op_star
id|RxRing
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
multiline_comment|/* Logical Rx ring pointers */
DECL|member|RxRing_Phy
id|dma_addr_t
id|RxRing_Phy
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
multiline_comment|/* Put pointer info which indictes which RxD has to be replenished &n;&t; * with a new buffer.&n;&t; */
DECL|member|rx_curr_put_info
id|rx_curr_put_info_t
id|rx_curr_put_info
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
multiline_comment|/* Get pointer info which indictes which is the last RxD that was &n;&t; * processed by the driver.&n;&t; */
DECL|member|rx_curr_get_info
id|rx_curr_get_info_t
id|rx_curr_get_info
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
DECL|member|rmac_pause_time
id|u16
id|rmac_pause_time
suffix:semicolon
multiline_comment|/* this will be used in receive function, this decides which ring would&n;&t;   be processed first. eg: ring with priority value 0 (highest) should&n;&t;   be processed first. &n;&t;   first 3 LSB bits represent ring number which should be processed &n;&t;   first, similarly next 3 bits represent next ring to be processed.&n;&t;   eg: value of _rx_ring_pri_map = 0x0000 003A means &n;&t;   ring #2 would be processed first and #7 would be processed next&n;&t; */
DECL|member|_rx_ring_pri_map
id|u32
id|_rx_ring_pri_map
suffix:semicolon
multiline_comment|/* tx side stuff */
DECL|member|txd_list_mem
r_void
op_star
id|txd_list_mem
suffix:semicolon
multiline_comment|/* orignal pointer to allocated mem */
DECL|member|txd_list_mem_phy
id|dma_addr_t
id|txd_list_mem_phy
suffix:semicolon
DECL|member|txd_list_mem_sz
id|u32
id|txd_list_mem_sz
suffix:semicolon
multiline_comment|/* logical pointer of start of each Tx FIFO */
DECL|member|tx_FIFO_start
id|TxFIFO_element_t
op_star
id|tx_FIFO_start
(braket
id|MAX_TX_FIFOS
)braket
suffix:semicolon
multiline_comment|/* logical pointer of start of TxDL which corresponds to each Tx FIFO */
DECL|member|txdl_start
id|TxD_t
op_star
id|txdl_start
(braket
id|MAX_TX_FIFOS
)braket
suffix:semicolon
multiline_comment|/* Same as txdl_start but phy addr */
DECL|member|txdl_start_phy
id|dma_addr_t
id|txdl_start_phy
(braket
id|MAX_TX_FIFOS
)braket
suffix:semicolon
multiline_comment|/* Current offset within tx_FIFO_start, where driver would write new Tx frame*/
DECL|member|tx_curr_put_info
id|tx_curr_put_info_t
id|tx_curr_put_info
(braket
id|MAX_TX_FIFOS
)braket
suffix:semicolon
DECL|member|tx_curr_get_info
id|tx_curr_get_info_t
id|tx_curr_get_info
(braket
id|MAX_TX_FIFOS
)braket
suffix:semicolon
DECL|member|txdl_len
id|u16
id|txdl_len
suffix:semicolon
multiline_comment|/* length of a TxDL, same for all */
DECL|member|stats_mem
r_void
op_star
id|stats_mem
suffix:semicolon
multiline_comment|/* orignal pointer to allocated mem */
DECL|member|stats_mem_phy
id|dma_addr_t
id|stats_mem_phy
suffix:semicolon
multiline_comment|/* Physical address of the stat block */
DECL|member|stats_mem_sz
id|u32
id|stats_mem_sz
suffix:semicolon
DECL|member|StatsInfo
id|StatInfo_t
op_star
id|StatsInfo
suffix:semicolon
multiline_comment|/* Logical address of the stat block */
DECL|typedef|mac_info_t
)brace
id|mac_info_t
suffix:semicolon
multiline_comment|/* structure representing the user defined MAC addresses */
r_typedef
r_struct
(brace
DECL|member|addr
r_char
id|addr
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|usage_cnt
r_int
id|usage_cnt
suffix:semicolon
DECL|typedef|usr_addr_t
)brace
id|usr_addr_t
suffix:semicolon
multiline_comment|/* Structure that holds the Phy and virt addresses of the Blocks */
DECL|struct|rx_block_info
r_typedef
r_struct
id|rx_block_info
(brace
DECL|member|block_virt_addr
id|RxD_t
op_star
id|block_virt_addr
suffix:semicolon
DECL|member|block_dma_addr
id|dma_addr_t
id|block_dma_addr
suffix:semicolon
DECL|typedef|rx_block_info_t
)brace
id|rx_block_info_t
suffix:semicolon
multiline_comment|/* Structure representing one instance of the NIC */
DECL|struct|s2io_nic
r_typedef
r_struct
id|s2io_nic
(brace
DECL|macro|MAX_MAC_SUPPORTED
mdefine_line|#define MAX_MAC_SUPPORTED   16
DECL|macro|MAX_SUPPORTED_MULTICASTS
mdefine_line|#define MAX_SUPPORTED_MULTICASTS MAX_MAC_SUPPORTED
DECL|member|defMacAddr
id|macaddr_t
id|defMacAddr
(braket
id|MAX_MAC_SUPPORTED
)braket
suffix:semicolon
DECL|member|preMacAddr
id|macaddr_t
id|preMacAddr
(braket
id|MAX_MAC_SUPPORTED
)braket
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|bar0
id|caddr_t
id|bar0
suffix:semicolon
DECL|member|bar1
id|caddr_t
id|bar1
suffix:semicolon
DECL|member|config
r_struct
id|config_param
id|config
suffix:semicolon
DECL|member|mac_control
id|mac_info_t
id|mac_control
suffix:semicolon
DECL|member|high_dma_flag
r_int
id|high_dma_flag
suffix:semicolon
DECL|member|device_close_flag
r_int
id|device_close_flag
suffix:semicolon
DECL|member|device_enabled_once
r_int
id|device_enabled_once
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|task
r_struct
id|tasklet_struct
id|task
suffix:semicolon
DECL|member|tasklet_status
id|atomic_t
id|tasklet_status
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|vendor_id
id|u16
id|vendor_id
suffix:semicolon
DECL|member|device_id
id|u16
id|device_id
suffix:semicolon
DECL|member|ccmd
id|u16
id|ccmd
suffix:semicolon
DECL|member|cbar0_1
id|u32
id|cbar0_1
suffix:semicolon
DECL|member|cbar0_2
id|u32
id|cbar0_2
suffix:semicolon
DECL|member|cbar1_1
id|u32
id|cbar1_1
suffix:semicolon
DECL|member|cbar1_2
id|u32
id|cbar1_2
suffix:semicolon
DECL|member|cirq
id|u32
id|cirq
suffix:semicolon
DECL|member|cache_line
id|u8
id|cache_line
suffix:semicolon
DECL|member|rom_expansion
id|u32
id|rom_expansion
suffix:semicolon
DECL|member|pcix_cmd
id|u16
id|pcix_cmd
suffix:semicolon
DECL|member|irq
id|u32
id|irq
suffix:semicolon
DECL|member|rx_bufs_left
id|atomic_t
id|rx_bufs_left
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
DECL|member|isr_lock
id|spinlock_t
id|isr_lock
suffix:semicolon
DECL|member|tx_lock
id|spinlock_t
id|tx_lock
suffix:semicolon
DECL|macro|PROMISC
mdefine_line|#define PROMISC     1
DECL|macro|ALL_MULTI
mdefine_line|#define ALL_MULTI   2
DECL|macro|MAX_ADDRS_SUPPORTED
mdefine_line|#define MAX_ADDRS_SUPPORTED 64
DECL|member|usr_addr_count
id|u16
id|usr_addr_count
suffix:semicolon
DECL|member|mc_addr_count
id|u16
id|mc_addr_count
suffix:semicolon
DECL|member|usr_addrs
id|usr_addr_t
id|usr_addrs
(braket
id|MAX_ADDRS_SUPPORTED
)braket
suffix:semicolon
DECL|member|m_cast_flg
id|u16
id|m_cast_flg
suffix:semicolon
DECL|member|all_multi_pos
id|u16
id|all_multi_pos
suffix:semicolon
DECL|member|promisc_flg
id|u16
id|promisc_flg
suffix:semicolon
DECL|member|tx_pkt_count
id|u16
id|tx_pkt_count
suffix:semicolon
DECL|member|rx_pkt_count
id|u16
id|rx_pkt_count
suffix:semicolon
DECL|member|tx_err_count
id|u16
id|tx_err_count
suffix:semicolon
DECL|member|rx_err_count
id|u16
id|rx_err_count
suffix:semicolon
macro_line|#if DEBUG_ON
DECL|member|rxpkt_bytes
id|u64
id|rxpkt_bytes
suffix:semicolon
DECL|member|txpkt_bytes
id|u64
id|txpkt_bytes
suffix:semicolon
DECL|member|int_cnt
r_int
id|int_cnt
suffix:semicolon
DECL|member|rxint_cnt
r_int
id|rxint_cnt
suffix:semicolon
DECL|member|txint_cnt
r_int
id|txint_cnt
suffix:semicolon
DECL|member|rxpkt_cnt
id|u64
id|rxpkt_cnt
suffix:semicolon
macro_line|#endif
multiline_comment|/*  Place holders for the virtual and physical addresses of &n;&t; *  all the Rx Blocks&n;&t; */
r_struct
id|rx_block_info
DECL|member|rx_blocks
id|rx_blocks
(braket
id|MAX_RX_RINGS
)braket
(braket
id|MAX_RX_BLOCKS_PER_RING
)braket
suffix:semicolon
DECL|member|block_count
r_int
id|block_count
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
DECL|member|pkt_cnt
r_int
id|pkt_cnt
(braket
id|MAX_RX_RINGS
)braket
suffix:semicolon
multiline_comment|/*  Id timer, used to blink NIC to physically identify NIC. */
DECL|member|id_timer
r_struct
id|timer_list
id|id_timer
suffix:semicolon
multiline_comment|/*  Restart timer, used to restart NIC if the device is stuck and&n;&t; *  a schedule task that will set the correct Link state once the &n;&t; *  NIC&squot;s PHY has stabilized after a state change.&n;&t; */
macro_line|#ifdef INIT_TQUEUE
DECL|member|rst_timer_task
r_struct
id|tq_struct
id|rst_timer_task
suffix:semicolon
DECL|member|set_link_task
r_struct
id|tq_struct
id|set_link_task
suffix:semicolon
macro_line|#else
DECL|member|rst_timer_task
r_struct
id|work_struct
id|rst_timer_task
suffix:semicolon
DECL|member|set_link_task
r_struct
id|work_struct
id|set_link_task
suffix:semicolon
macro_line|#endif
multiline_comment|/* Flag that can be used to turn on or turn off the Rx checksum &n;&t; * offload feature.&n;&t; */
DECL|member|rx_csum
r_int
id|rx_csum
suffix:semicolon
multiline_comment|/*  after blink, the adapter must be restored with original &n;&t; *  values.&n;&t; */
DECL|member|adapt_ctrl_org
id|u64
id|adapt_ctrl_org
suffix:semicolon
multiline_comment|/* Last known link state. */
DECL|member|last_link_state
id|u16
id|last_link_state
suffix:semicolon
DECL|macro|LINK_DOWN
mdefine_line|#define&t;LINK_DOWN&t;1
DECL|macro|LINK_UP
mdefine_line|#define&t;LINK_UP&t;&t;2
DECL|typedef|nic_t
)brace
id|nic_t
suffix:semicolon
DECL|macro|RESET_ERROR
mdefine_line|#define RESET_ERROR 1;
DECL|macro|CMD_ERROR
mdefine_line|#define CMD_ERROR   2;
multiline_comment|/* Default Tunable parameters of the NIC. */
DECL|macro|DEFAULT_FIFO_LEN
mdefine_line|#define DEFAULT_FIFO_LEN 4096
DECL|macro|SMALL_RXD_CNT
mdefine_line|#define SMALL_RXD_CNT&t;40 * (MAX_RXDS_PER_BLOCK+1)
DECL|macro|LARGE_RXD_CNT
mdefine_line|#define LARGE_RXD_CNT&t;100 * (MAX_RXDS_PER_BLOCK+1)
multiline_comment|/*  OS related system calls */
macro_line|#ifndef readq
DECL|function|readq
r_static
r_inline
id|u64
id|readq
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
id|u64
id|ret
op_assign
l_int|0
suffix:semicolon
id|ret
op_assign
id|readl
c_func
(paren
id|addr
op_plus
l_int|4
)paren
suffix:semicolon
id|ret
op_lshift_assign
l_int|32
suffix:semicolon
id|ret
op_or_assign
id|readl
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef writeq
DECL|function|writeq
r_static
r_inline
r_void
id|writeq
c_func
(paren
id|u64
id|val
comma
r_void
op_star
id|addr
)paren
(brace
id|writel
c_func
(paren
(paren
id|u32
)paren
(paren
id|val
)paren
comma
id|addr
)paren
suffix:semicolon
id|writel
c_func
(paren
(paren
id|u32
)paren
(paren
id|val
op_rshift
l_int|32
)paren
comma
(paren
id|addr
op_plus
l_int|4
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*  Interrupt related values of Xena */
DECL|macro|ENABLE_INTRS
mdefine_line|#define ENABLE_INTRS    1
DECL|macro|DISABLE_INTRS
mdefine_line|#define DISABLE_INTRS   2
multiline_comment|/*  Highest level interrupt blocks */
DECL|macro|TX_PIC_INTR
mdefine_line|#define TX_PIC_INTR     (0x0001&lt;&lt;0)
DECL|macro|TX_DMA_INTR
mdefine_line|#define TX_DMA_INTR     (0x0001&lt;&lt;1)
DECL|macro|TX_MAC_INTR
mdefine_line|#define TX_MAC_INTR     (0x0001&lt;&lt;2)
DECL|macro|TX_XGXS_INTR
mdefine_line|#define TX_XGXS_INTR    (0x0001&lt;&lt;3)
DECL|macro|TX_TRAFFIC_INTR
mdefine_line|#define TX_TRAFFIC_INTR (0x0001&lt;&lt;4)
DECL|macro|RX_PIC_INTR
mdefine_line|#define RX_PIC_INTR     (0x0001&lt;&lt;5)
DECL|macro|RX_DMA_INTR
mdefine_line|#define RX_DMA_INTR     (0x0001&lt;&lt;6)
DECL|macro|RX_MAC_INTR
mdefine_line|#define RX_MAC_INTR     (0x0001&lt;&lt;7)
DECL|macro|RX_XGXS_INTR
mdefine_line|#define RX_XGXS_INTR    (0x0001&lt;&lt;8)
DECL|macro|RX_TRAFFIC_INTR
mdefine_line|#define RX_TRAFFIC_INTR (0x0001&lt;&lt;9)
DECL|macro|MC_INTR
mdefine_line|#define MC_INTR         (0x0001&lt;&lt;10)
DECL|macro|ENA_ALL_INTRS
mdefine_line|#define ENA_ALL_INTRS    (   TX_PIC_INTR     | &bslash;&n;                            TX_DMA_INTR     | &bslash;&n;                            TX_MAC_INTR     | &bslash;&n;                            TX_XGXS_INTR    | &bslash;&n;                            TX_TRAFFIC_INTR | &bslash;&n;                            RX_PIC_INTR     | &bslash;&n;                            RX_DMA_INTR     | &bslash;&n;                            RX_MAC_INTR     | &bslash;&n;                            RX_XGXS_INTR    | &bslash;&n;                            RX_TRAFFIC_INTR | &bslash;&n;                            MC_INTR )
multiline_comment|/*  Interrupt masks for the general interrupt mask register */
DECL|macro|DISABLE_ALL_INTRS
mdefine_line|#define DISABLE_ALL_INTRS   0xFFFFFFFFFFFFFFFFULL
DECL|macro|TXPIC_INT_M
mdefine_line|#define TXPIC_INT_M         BIT(0)
DECL|macro|TXDMA_INT_M
mdefine_line|#define TXDMA_INT_M         BIT(1)
DECL|macro|TXMAC_INT_M
mdefine_line|#define TXMAC_INT_M         BIT(2)
DECL|macro|TXXGXS_INT_M
mdefine_line|#define TXXGXS_INT_M        BIT(3)
DECL|macro|TXTRAFFIC_INT_M
mdefine_line|#define TXTRAFFIC_INT_M     BIT(8)
DECL|macro|PIC_RX_INT_M
mdefine_line|#define PIC_RX_INT_M        BIT(32)
DECL|macro|RXDMA_INT_M
mdefine_line|#define RXDMA_INT_M         BIT(33)
DECL|macro|RXMAC_INT_M
mdefine_line|#define RXMAC_INT_M         BIT(34)
DECL|macro|MC_INT_M
mdefine_line|#define MC_INT_M            BIT(35)
DECL|macro|RXXGXS_INT_M
mdefine_line|#define RXXGXS_INT_M        BIT(36)
DECL|macro|RXTRAFFIC_INT_M
mdefine_line|#define RXTRAFFIC_INT_M     BIT(40)
multiline_comment|/*  PIC level Interrupts TODO*/
multiline_comment|/*  DMA level Inressupts */
DECL|macro|TXDMA_PFC_INT_M
mdefine_line|#define TXDMA_PFC_INT_M     BIT(0)
multiline_comment|/*  PFC block interrupts */
DECL|macro|PFC_MISC_ERR_1
mdefine_line|#define PFC_MISC_ERR_1      BIT(0)&t;/* Interrupt to indicate FIFO full */
multiline_comment|/*&n; * Prototype declaration.&n; */
r_static
r_int
id|__devinit
id|s2io_init_nic
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|pre
)paren
suffix:semicolon
r_static
r_void
id|__devexit
id|s2io_rem_nic
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
suffix:semicolon
r_static
r_int
id|initSharedMem
c_func
(paren
r_struct
id|s2io_nic
op_star
id|sp
)paren
suffix:semicolon
r_static
r_void
id|freeSharedMem
c_func
(paren
r_struct
id|s2io_nic
op_star
id|sp
)paren
suffix:semicolon
r_static
r_int
id|initNic
c_func
(paren
r_struct
id|s2io_nic
op_star
id|nic
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_S2IO_NAPI
r_static
r_void
id|rxIntrHandler
c_func
(paren
r_struct
id|s2io_nic
op_star
id|sp
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|txIntrHandler
c_func
(paren
r_struct
id|s2io_nic
op_star
id|sp
)paren
suffix:semicolon
r_static
r_void
id|alarmIntrHandler
c_func
(paren
r_struct
id|s2io_nic
op_star
id|sp
)paren
suffix:semicolon
r_static
r_int
id|s2io_starter
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|s2io_closer
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|s2io_tx_watchdog
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|s2io_tasklet
c_func
(paren
r_int
r_int
id|dev_addr
)paren
suffix:semicolon
r_static
r_void
id|s2io_set_multicast
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|rxOsmHandler
c_func
(paren
id|nic_t
op_star
id|sp
comma
id|u16
id|len
comma
id|RxD_t
op_star
id|rxdp
comma
r_int
id|ring_no
)paren
suffix:semicolon
r_void
id|s2io_link
c_func
(paren
id|nic_t
op_star
id|sp
comma
r_int
id|link
)paren
suffix:semicolon
r_void
id|s2io_reset
c_func
(paren
id|nic_t
op_star
id|sp
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_S2IO_NAPI
r_static
r_int
id|s2io_poll
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
op_star
id|budget
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|s2io_init_pci
c_func
(paren
id|nic_t
op_star
id|sp
)paren
suffix:semicolon
r_int
id|s2io_set_mac_addr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u8
op_star
id|addr
)paren
suffix:semicolon
r_static
id|irqreturn_t
id|s2io_isr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|verify_xena_quiescence
c_func
(paren
id|u64
id|val64
comma
r_int
id|flag
)paren
suffix:semicolon
DECL|variable|netdev_ethtool_ops
r_static
r_struct
id|ethtool_ops
id|netdev_ethtool_ops
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _S2IO_H */
eof
