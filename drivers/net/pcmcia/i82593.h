multiline_comment|/*&n; * Definitions for Intel 82593 CSMA/CD Core LAN Controller&n; * The definitions are taken from the 1992 users manual with Intel&n; * order number 297125-001.&n; *&n; * /usr/src/pc/RCS/i82593.h,v 1.1 1996/07/17 15:23:12 root Exp&n; *&n; * Copyright 1994, Anders Klemets &lt;klemets@it.kth.se&gt;&n; *&n; * This software may be freely distributed for noncommercial purposes&n; * as long as this notice is retained.&n; * &n; * HISTORY&n; * i82593.h,v&n; * Revision 1.1  1996/07/17 15:23:12  root&n; * Initial revision&n; *&n; * Revision 1.3  1995/04/05  15:13:58  adj&n; * Initial alpha release&n; *&n; * Revision 1.2  1994/06/16  23:57:31  klemets&n; * Mirrored all the fields in the configuration block.&n; *&n; * Revision 1.1  1994/06/02  20:25:34  klemets&n; * Initial revision&n; *&n; *&n; */
macro_line|#ifndef&t;_I82593_H
DECL|macro|_I82593_H
mdefine_line|#define&t;_I82593_H
multiline_comment|/* Intel 82593 CSMA/CD Core LAN Controller */
multiline_comment|/* Port 0 Command Register definitions */
multiline_comment|/* Execution operations */
DECL|macro|OP0_NOP
mdefine_line|#define OP0_NOP&t;&t;&t;0&t;/* CHNL = 0 */
DECL|macro|OP0_SWIT_TO_PORT_1
mdefine_line|#define OP0_SWIT_TO_PORT_1&t;0&t;/* CHNL = 1 */
DECL|macro|OP0_IA_SETUP
mdefine_line|#define OP0_IA_SETUP&t;&t;1
DECL|macro|OP0_CONFIGURE
mdefine_line|#define OP0_CONFIGURE&t;&t;2
DECL|macro|OP0_MC_SETUP
mdefine_line|#define OP0_MC_SETUP&t;&t;3
DECL|macro|OP0_TRANSMIT
mdefine_line|#define OP0_TRANSMIT&t;&t;4
DECL|macro|OP0_TDR
mdefine_line|#define OP0_TDR&t;&t;&t;5
DECL|macro|OP0_DUMP
mdefine_line|#define OP0_DUMP&t;&t;6
DECL|macro|OP0_DIAGNOSE
mdefine_line|#define OP0_DIAGNOSE&t;&t;7
DECL|macro|OP0_TRANSMIT_NO_CRC
mdefine_line|#define OP0_TRANSMIT_NO_CRC&t;9
DECL|macro|OP0_RETRANSMIT
mdefine_line|#define OP0_RETRANSMIT&t;&t;12
DECL|macro|OP0_ABORT
mdefine_line|#define OP0_ABORT&t;&t;13
multiline_comment|/* Reception operations */
DECL|macro|OP0_RCV_ENABLE
mdefine_line|#define OP0_RCV_ENABLE&t;&t;8
DECL|macro|OP0_RCV_DISABLE
mdefine_line|#define OP0_RCV_DISABLE&t;&t;10
DECL|macro|OP0_STOP_RCV
mdefine_line|#define OP0_STOP_RCV&t;&t;11
multiline_comment|/* Status pointer control operations */
DECL|macro|OP0_FIX_PTR
mdefine_line|#define OP0_FIX_PTR&t;&t;15&t;/* CHNL = 1 */
DECL|macro|OP0_RLS_PTR
mdefine_line|#define OP0_RLS_PTR&t;&t;15&t;/* CHNL = 0 */
DECL|macro|OP0_RESET
mdefine_line|#define OP0_RESET&t;&t;14
DECL|macro|CR0_CHNL
mdefine_line|#define CR0_CHNL&t;&t;(1 &lt;&lt; 4)&t;/* 0=Channel 0, 1=Channel 1 */
DECL|macro|CR0_STATUS_0
mdefine_line|#define CR0_STATUS_0&t;&t;0x00
DECL|macro|CR0_STATUS_1
mdefine_line|#define CR0_STATUS_1&t;&t;0x20
DECL|macro|CR0_STATUS_2
mdefine_line|#define CR0_STATUS_2&t;&t;0x40
DECL|macro|CR0_STATUS_3
mdefine_line|#define CR0_STATUS_3&t;&t;0x60
DECL|macro|CR0_INT_ACK
mdefine_line|#define CR0_INT_ACK&t;&t;(1 &lt;&lt; 7)&t;/* 0=No ack, 1=acknowledge */
multiline_comment|/* Port 0 Status Register definitions */
DECL|macro|SR0_NO_RESULT
mdefine_line|#define SR0_NO_RESULT&t;&t;0&t;&t;/* dummy */
DECL|macro|SR0_EVENT_MASK
mdefine_line|#define SR0_EVENT_MASK&t;&t;0x0f
DECL|macro|SR0_IA_SETUP_DONE
mdefine_line|#define SR0_IA_SETUP_DONE&t;1
DECL|macro|SR0_CONFIGURE_DONE
mdefine_line|#define SR0_CONFIGURE_DONE&t;2
DECL|macro|SR0_MC_SETUP_DONE
mdefine_line|#define SR0_MC_SETUP_DONE&t;3
DECL|macro|SR0_TRANSMIT_DONE
mdefine_line|#define SR0_TRANSMIT_DONE&t;4
DECL|macro|SR0_TDR_DONE
mdefine_line|#define SR0_TDR_DONE&t;&t;5
DECL|macro|SR0_DUMP_DONE
mdefine_line|#define SR0_DUMP_DONE&t;&t;6
DECL|macro|SR0_DIAGNOSE_PASSED
mdefine_line|#define SR0_DIAGNOSE_PASSED&t;7
DECL|macro|SR0_TRANSMIT_NO_CRC_DONE
mdefine_line|#define SR0_TRANSMIT_NO_CRC_DONE 9
DECL|macro|SR0_RETRANSMIT_DONE
mdefine_line|#define SR0_RETRANSMIT_DONE&t;12
DECL|macro|SR0_EXECUTION_ABORTED
mdefine_line|#define SR0_EXECUTION_ABORTED&t;13
DECL|macro|SR0_END_OF_FRAME
mdefine_line|#define SR0_END_OF_FRAME&t;8
DECL|macro|SR0_RECEPTION_ABORTED
mdefine_line|#define SR0_RECEPTION_ABORTED&t;10
DECL|macro|SR0_DIAGNOSE_FAILED
mdefine_line|#define SR0_DIAGNOSE_FAILED&t;15
DECL|macro|SR0_STOP_REG_HIT
mdefine_line|#define SR0_STOP_REG_HIT&t;11
DECL|macro|SR0_CHNL
mdefine_line|#define SR0_CHNL&t;&t;(1 &lt;&lt; 4)
DECL|macro|SR0_EXECUTION
mdefine_line|#define SR0_EXECUTION&t;&t;(1 &lt;&lt; 5)
DECL|macro|SR0_RECEPTION
mdefine_line|#define SR0_RECEPTION&t;&t;(1 &lt;&lt; 6)
DECL|macro|SR0_INTERRUPT
mdefine_line|#define SR0_INTERRUPT&t;&t;(1 &lt;&lt; 7)
DECL|macro|SR0_BOTH_RX_TX
mdefine_line|#define SR0_BOTH_RX_TX&t;&t;(SR0_EXECUTION | SR0_RECEPTION)
DECL|macro|SR3_EXEC_STATE_MASK
mdefine_line|#define SR3_EXEC_STATE_MASK&t;0x03
DECL|macro|SR3_EXEC_IDLE
mdefine_line|#define SR3_EXEC_IDLE&t;&t;0
DECL|macro|SR3_TX_ABORT_IN_PROGRESS
mdefine_line|#define SR3_TX_ABORT_IN_PROGRESS 1
DECL|macro|SR3_EXEC_ACTIVE
mdefine_line|#define SR3_EXEC_ACTIVE&t;&t;2
DECL|macro|SR3_ABORT_IN_PROGRESS
mdefine_line|#define SR3_ABORT_IN_PROGRESS&t;3
DECL|macro|SR3_EXEC_CHNL
mdefine_line|#define SR3_EXEC_CHNL&t;&t;(1 &lt;&lt; 2)
DECL|macro|SR3_STP_ON_NO_RSRC
mdefine_line|#define SR3_STP_ON_NO_RSRC&t;(1 &lt;&lt; 3)
DECL|macro|SR3_RCVING_NO_RSRC
mdefine_line|#define SR3_RCVING_NO_RSRC&t;(1 &lt;&lt; 4)
DECL|macro|SR3_RCV_STATE_MASK
mdefine_line|#define SR3_RCV_STATE_MASK&t;0x60
DECL|macro|SR3_RCV_IDLE
mdefine_line|#define SR3_RCV_IDLE&t;&t;0x00
DECL|macro|SR3_RCV_READY
mdefine_line|#define SR3_RCV_READY&t;&t;0x20
DECL|macro|SR3_RCV_ACTIVE
mdefine_line|#define SR3_RCV_ACTIVE&t;&t;0x40
DECL|macro|SR3_RCV_STOP_IN_PROG
mdefine_line|#define SR3_RCV_STOP_IN_PROG&t;0x60
DECL|macro|SR3_RCV_CHNL
mdefine_line|#define SR3_RCV_CHNL&t;&t;(1 &lt;&lt; 7)
multiline_comment|/* Port 1 Command Register definitions */
DECL|macro|OP1_NOP
mdefine_line|#define OP1_NOP&t;&t;&t;0
DECL|macro|OP1_SWIT_TO_PORT_0
mdefine_line|#define OP1_SWIT_TO_PORT_0&t;1
DECL|macro|OP1_INT_DISABLE
mdefine_line|#define OP1_INT_DISABLE&t;&t;2
DECL|macro|OP1_INT_ENABLE
mdefine_line|#define OP1_INT_ENABLE&t;&t;3
DECL|macro|OP1_SET_TS
mdefine_line|#define OP1_SET_TS&t;&t;5
DECL|macro|OP1_RST_TS
mdefine_line|#define OP1_RST_TS&t;&t;7
DECL|macro|OP1_POWER_DOWN
mdefine_line|#define OP1_POWER_DOWN&t;&t;8
DECL|macro|OP1_RESET_RING_MNGMT
mdefine_line|#define OP1_RESET_RING_MNGMT&t;11
DECL|macro|OP1_RESET
mdefine_line|#define OP1_RESET&t;&t;14
DECL|macro|OP1_SEL_RST
mdefine_line|#define OP1_SEL_RST&t;&t;15
DECL|macro|CR1_STATUS_4
mdefine_line|#define CR1_STATUS_4&t;&t;0x00
DECL|macro|CR1_STATUS_5
mdefine_line|#define CR1_STATUS_5&t;&t;0x20
DECL|macro|CR1_STATUS_6
mdefine_line|#define CR1_STATUS_6&t;&t;0x40
DECL|macro|CR1_STOP_REG_UPDATE
mdefine_line|#define CR1_STOP_REG_UPDATE&t;(1 &lt;&lt; 7)
multiline_comment|/* Receive frame status bits */
DECL|macro|RX_RCLD
mdefine_line|#define&t;RX_RCLD&t;&t;&t;(1 &lt;&lt; 0)
DECL|macro|RX_IA_MATCH
mdefine_line|#define RX_IA_MATCH&t;&t;(1 &lt;&lt; 1)
DECL|macro|RX_NO_AD_MATCH
mdefine_line|#define&t;RX_NO_AD_MATCH&t;&t;(1 &lt;&lt; 2)
DECL|macro|RX_NO_SFD
mdefine_line|#define RX_NO_SFD&t;&t;(1 &lt;&lt; 3)
DECL|macro|RX_SRT_FRM
mdefine_line|#define RX_SRT_FRM&t;&t;(1 &lt;&lt; 7)
DECL|macro|RX_OVRRUN
mdefine_line|#define RX_OVRRUN&t;&t;(1 &lt;&lt; 8)
DECL|macro|RX_ALG_ERR
mdefine_line|#define RX_ALG_ERR&t;&t;(1 &lt;&lt; 10)
DECL|macro|RX_CRC_ERR
mdefine_line|#define RX_CRC_ERR&t;&t;(1 &lt;&lt; 11)
DECL|macro|RX_LEN_ERR
mdefine_line|#define RX_LEN_ERR&t;&t;(1 &lt;&lt; 12)
DECL|macro|RX_RCV_OK
mdefine_line|#define RX_RCV_OK&t;&t;(1 &lt;&lt; 13)
DECL|macro|RX_TYP_LEN
mdefine_line|#define RX_TYP_LEN&t;&t;(1 &lt;&lt; 15)
multiline_comment|/* Transmit status bits */
DECL|macro|TX_NCOL_MASK
mdefine_line|#define TX_NCOL_MASK&t;&t;0x0f
DECL|macro|TX_FRTL
mdefine_line|#define TX_FRTL&t;&t;&t;(1 &lt;&lt; 4)
DECL|macro|TX_MAX_COL
mdefine_line|#define TX_MAX_COL&t;&t;(1 &lt;&lt; 5)
DECL|macro|TX_HRT_BEAT
mdefine_line|#define TX_HRT_BEAT&t;&t;(1 &lt;&lt; 6)
DECL|macro|TX_DEFER
mdefine_line|#define TX_DEFER&t;&t;(1 &lt;&lt; 7)
DECL|macro|TX_UND_RUN
mdefine_line|#define TX_UND_RUN&t;&t;(1 &lt;&lt; 8)
DECL|macro|TX_LOST_CTS
mdefine_line|#define TX_LOST_CTS&t;&t;(1 &lt;&lt; 9)
DECL|macro|TX_LOST_CRS
mdefine_line|#define TX_LOST_CRS&t;&t;(1 &lt;&lt; 10)
DECL|macro|TX_LTCOL
mdefine_line|#define TX_LTCOL&t;&t;(1 &lt;&lt; 11)
DECL|macro|TX_OK
mdefine_line|#define TX_OK&t;&t;&t;(1 &lt;&lt; 13)
DECL|macro|TX_COLL
mdefine_line|#define TX_COLL&t;&t;&t;(1 &lt;&lt; 15)
DECL|struct|i82593_conf_block
r_struct
id|i82593_conf_block
(brace
DECL|member|fifo_limit
id|u_char
id|fifo_limit
suffix:colon
l_int|4
comma
DECL|member|forgnesi
id|forgnesi
suffix:colon
l_int|1
comma
DECL|member|fifo_32
id|fifo_32
suffix:colon
l_int|1
comma
DECL|member|d6mod
id|d6mod
suffix:colon
l_int|1
comma
DECL|member|throttle_enb
id|throttle_enb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|throttle
id|u_char
id|throttle
suffix:colon
l_int|6
comma
DECL|member|cntrxint
id|cntrxint
suffix:colon
l_int|1
comma
DECL|member|contin
id|contin
suffix:colon
l_int|1
suffix:semicolon
DECL|member|addr_len
id|u_char
id|addr_len
suffix:colon
l_int|3
comma
DECL|member|acloc
id|acloc
suffix:colon
l_int|1
comma
DECL|member|preamb_len
id|preamb_len
suffix:colon
l_int|2
comma
DECL|member|loopback
id|loopback
suffix:colon
l_int|2
suffix:semicolon
DECL|member|lin_prio
id|u_char
id|lin_prio
suffix:colon
l_int|3
comma
DECL|member|tbofstop
id|tbofstop
suffix:colon
l_int|1
comma
DECL|member|exp_prio
id|exp_prio
suffix:colon
l_int|3
comma
DECL|member|bof_met
id|bof_met
suffix:colon
l_int|1
suffix:semicolon
DECL|member|u_char
id|u_char
suffix:colon
l_int|4
comma
DECL|member|ifrm_spc
id|ifrm_spc
suffix:colon
l_int|4
suffix:semicolon
DECL|member|u_char
id|u_char
suffix:colon
l_int|5
comma
DECL|member|slottim_low
id|slottim_low
suffix:colon
l_int|3
suffix:semicolon
DECL|member|slottim_hi
id|u_char
id|slottim_hi
suffix:colon
l_int|3
comma
suffix:colon
l_int|1
comma
DECL|member|max_retr
id|max_retr
suffix:colon
l_int|4
suffix:semicolon
DECL|member|prmisc
id|u_char
id|prmisc
suffix:colon
l_int|1
comma
DECL|member|bc_dis
id|bc_dis
suffix:colon
l_int|1
comma
suffix:colon
l_int|1
comma
DECL|member|crs_1
id|crs_1
suffix:colon
l_int|1
comma
DECL|member|nocrc_ins
id|nocrc_ins
suffix:colon
l_int|1
comma
DECL|member|crc_1632
id|crc_1632
suffix:colon
l_int|1
comma
suffix:colon
l_int|1
comma
DECL|member|crs_cdt
id|crs_cdt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cs_filter
id|u_char
id|cs_filter
suffix:colon
l_int|3
comma
DECL|member|crs_src
id|crs_src
suffix:colon
l_int|1
comma
DECL|member|cd_filter
id|cd_filter
suffix:colon
l_int|3
comma
suffix:colon
l_int|1
suffix:semicolon
DECL|member|u_char
id|u_char
suffix:colon
l_int|2
comma
DECL|member|min_fr_len
id|min_fr_len
suffix:colon
l_int|6
suffix:semicolon
DECL|member|lng_typ
id|u_char
id|lng_typ
suffix:colon
l_int|1
comma
DECL|member|lng_fld
id|lng_fld
suffix:colon
l_int|1
comma
DECL|member|rxcrc_xf
id|rxcrc_xf
suffix:colon
l_int|1
comma
DECL|member|artx
id|artx
suffix:colon
l_int|1
comma
DECL|member|sarec
id|sarec
suffix:colon
l_int|1
comma
DECL|member|tx_jabber
id|tx_jabber
suffix:colon
l_int|1
comma
multiline_comment|/* why is this called max_len in the manual? */
DECL|member|hash_1
id|hash_1
suffix:colon
l_int|1
comma
DECL|member|lbpkpol
id|lbpkpol
suffix:colon
l_int|1
suffix:semicolon
DECL|member|u_char
id|u_char
suffix:colon
l_int|6
comma
DECL|member|fdx
id|fdx
suffix:colon
l_int|1
comma
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dummy_6
id|u_char
id|dummy_6
suffix:colon
l_int|6
comma
multiline_comment|/* supposed to be ones */
DECL|member|mult_ia
id|mult_ia
suffix:colon
l_int|1
comma
DECL|member|dis_bof
id|dis_bof
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dummy_1
id|u_char
id|dummy_1
suffix:colon
l_int|1
comma
multiline_comment|/* supposed to be one */
DECL|member|tx_ifs_retrig
id|tx_ifs_retrig
suffix:colon
l_int|2
comma
DECL|member|mc_all
id|mc_all
suffix:colon
l_int|1
comma
DECL|member|rcv_mon
id|rcv_mon
suffix:colon
l_int|2
comma
DECL|member|frag_acpt
id|frag_acpt
suffix:colon
l_int|1
comma
DECL|member|tstrttrs
id|tstrttrs
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fretx
id|u_char
id|fretx
suffix:colon
l_int|1
comma
DECL|member|runt_eop
id|runt_eop
suffix:colon
l_int|1
comma
DECL|member|hw_sw_pin
id|hw_sw_pin
suffix:colon
l_int|1
comma
DECL|member|big_endn
id|big_endn
suffix:colon
l_int|1
comma
DECL|member|syncrqs
id|syncrqs
suffix:colon
l_int|1
comma
DECL|member|sttlen
id|sttlen
suffix:colon
l_int|1
comma
DECL|member|tx_eop
id|tx_eop
suffix:colon
l_int|1
comma
DECL|member|rx_eop
id|rx_eop
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rbuf_size
id|u_char
id|rbuf_size
suffix:colon
l_int|5
comma
DECL|member|rcvstop
id|rcvstop
suffix:colon
l_int|1
comma
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|I82593_MAX_MULTICAST_ADDRESSES
mdefine_line|#define I82593_MAX_MULTICAST_ADDRESSES&t;128&t;/* Hardware hashed filter */
macro_line|#endif _I82593_H
eof
