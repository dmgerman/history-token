multiline_comment|/*****************************************************************************&n;* sdla_x25.h&t;Sangoma X.25 firmware API definitions.&n;*&n;* Author:&t;Nenad Corbic&t;&lt;ncorbic@sangoma.com&gt;&n;*&n;* Copyright:&t;(c) 1995-2000 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Feb 28, 2000  Nenad Corbic    Updated for socket based x25api&n;* Dec 13, 1996&t;Gene Kozin&t;Initial version&n;*****************************************************************************/
macro_line|#ifndef&t;_SDLA_X25_H
DECL|macro|_SDLA_X25_H
mdefine_line|#define&t;_SDLA_X25_H
multiline_comment|/*----------------------------------------------------------------------------&n; * Notes:&n; * ------&n; * 1. All structures defined in this file are byte-alined.  &n; *&t;Compiler&t;Platform&t;&n; *&t;--------&t;--------&n; *&t;GNU C&t;&t;Linux&n; *&n; */
macro_line|#ifndef&t;PACKED
DECL|macro|PACKED
macro_line|#&t;define&t;PACKED&t;__attribute__((packed))
macro_line|#endif&t;/* PACKED */
multiline_comment|/******&t;CONSTANTS DEFINITIONS ***********************************************/
DECL|macro|X25_MAX_CHAN
mdefine_line|#define&t;X25_MAX_CHAN&t;255&t;/* max number of open X.25 circuits */
DECL|macro|X25_MAX_DATA
mdefine_line|#define&t;X25_MAX_DATA&t;1024&t;/* max length of X.25 data buffer */
multiline_comment|/*&n; * X.25 shared memory layout.&n; */
DECL|macro|X25_MBOX_OFFS
mdefine_line|#define&t;X25_MBOX_OFFS&t;0x16B0&t;/* general mailbox block */
DECL|macro|X25_RXMBOX_OFFS
mdefine_line|#define&t;X25_RXMBOX_OFFS&t;0x1AD0&t;/* receive mailbox */
DECL|macro|X25_STATUS_OFFS
mdefine_line|#define&t;X25_STATUS_OFFS&t;0x1EF0&t;/* X.25 status structure */
DECL|macro|X25_MB_VECTOR
mdefine_line|#define X25_MB_VECTOR&t;0xE000&t;/* S514 mailbox window vecotr */
DECL|macro|X25_MISC_HDLC_BITS
mdefine_line|#define X25_MISC_HDLC_BITS 0x1F00 /*X.25 miscallaneous HDLC bits */
multiline_comment|/* code levels */
DECL|macro|HDLC_LEVEL
mdefine_line|#define HDLC_LEVEL 0x01
DECL|macro|X25_LEVEL
mdefine_line|#define X25_LEVEL  0x02
DECL|macro|X25_AND_HDLC_LEVEL
mdefine_line|#define X25_AND_HDLC_LEVEL 0x03
DECL|macro|DO_HDLC_LEVEL_ERROR_CHECKING
mdefine_line|#define DO_HDLC_LEVEL_ERROR_CHECKING 0x04
multiline_comment|/****** DATA STRUCTURES *****************************************************/
multiline_comment|/*----------------------------------------------------------------------------&n; * X.25 Command Block.&n; */
DECL|struct|X25Cmd
r_typedef
r_struct
id|X25Cmd
(brace
DECL|member|PACKED
r_int
r_char
id|command
id|PACKED
suffix:semicolon
multiline_comment|/* command code */
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
multiline_comment|/* transfer data length */
DECL|member|PACKED
r_int
r_char
id|result
id|PACKED
suffix:semicolon
multiline_comment|/* return code */
DECL|member|PACKED
r_int
r_char
id|pf
id|PACKED
suffix:semicolon
multiline_comment|/* P/F bit */
DECL|member|PACKED
r_int
r_int
id|lcn
id|PACKED
suffix:semicolon
multiline_comment|/* logical channel */
DECL|member|PACKED
r_int
r_char
id|qdm
id|PACKED
suffix:semicolon
multiline_comment|/* Q/D/M bits */
DECL|member|PACKED
r_int
r_char
id|cause
id|PACKED
suffix:semicolon
multiline_comment|/* cause field */
DECL|member|PACKED
r_int
r_char
id|diagn
id|PACKED
suffix:semicolon
multiline_comment|/* diagnostics */
DECL|member|PACKED
r_int
r_char
id|pktType
id|PACKED
suffix:semicolon
multiline_comment|/* packet type */
DECL|member|PACKED
r_int
r_char
id|resrv
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|TX25Cmd
)brace
id|TX25Cmd
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;command&squot; field.&n; */
multiline_comment|/*----- General commands --------------*/
DECL|macro|X25_SET_GLOBAL_VARS
mdefine_line|#define X25_SET_GLOBAL_VARS&t;0x0B   &t;/* set global variables */ 
DECL|macro|X25_READ_MODEM_STATUS
mdefine_line|#define X25_READ_MODEM_STATUS&t;0x0C &t;/* read modem status */
DECL|macro|X25_READ_CODE_VERSION
mdefine_line|#define X25_READ_CODE_VERSION&t;0x15&t;/* read firmware version number */
DECL|macro|X25_TRACE_CONFIGURE
mdefine_line|#define X25_TRACE_CONFIGURE&t;0x14&t;/* configure trace facility */
DECL|macro|X25_READ_TRACE_DATA
mdefine_line|#define X25_READ_TRACE_DATA&t;0x16&t;/* read trace data */
DECL|macro|X25_SET_INTERRUPT_MODE
mdefine_line|#define&t;X25_SET_INTERRUPT_MODE&t;0x17&t;/* set interrupt generation mode */
DECL|macro|X25_READ_INTERRUPT_MODE
mdefine_line|#define&t;X25_READ_INTERRUPT_MODE&t;0x18&t;/* read interrupt generation mode */
multiline_comment|/*----- HDLC-level commands -----------*/
DECL|macro|X25_HDLC_LINK_CONFIGURE
mdefine_line|#define X25_HDLC_LINK_CONFIGURE&t;0x01&t;/* configure HDLC link level */   
DECL|macro|X25_HDLC_LINK_OPEN
mdefine_line|#define X25_HDLC_LINK_OPEN&t;0x02&t;/* open HDLC link */         &t;
DECL|macro|X25_HDLC_LINK_CLOSE
mdefine_line|#define X25_HDLC_LINK_CLOSE&t;0x03&t;/* close HDLC link */
DECL|macro|X25_HDLC_LINK_SETUP
mdefine_line|#define X25_HDLC_LINK_SETUP&t;0x04&t;/* set up HDLC link */ 
DECL|macro|X25_HDLC_LINK_DISC
mdefine_line|#define X25_HDLC_LINK_DISC&t;0x05&t;/* disconnect DHLC link */
DECL|macro|X25_HDLC_LINK_STATUS
mdefine_line|#define X25_HDLC_LINK_STATUS&t;0x06&t;/* read DHLC link status */
DECL|macro|X25_HDLC_READ_STATS
mdefine_line|#define X25_HDLC_READ_STATS&t;0x07&t;/* read operational statistics */
DECL|macro|X25_HDLC_FLUSH_STATS
mdefine_line|#define X25_HDLC_FLUSH_STATS&t;0x08 &t;/* flush operational statistics */
DECL|macro|X25_HDLC_READ_COMM_ERR
mdefine_line|#define X25_HDLC_READ_COMM_ERR&t;0x09 &t;/* read error statistics */
DECL|macro|X25_HDLC_FLUSH_COMM_ERR
mdefine_line|#define X25_HDLC_FLUSH_COMM_ERR&t;0x0A&t;/* flush error statistics */
DECL|macro|X25_HDLC_FLUSH_BUFFERS
mdefine_line|#define X25_HDLC_FLUSH_BUFFERS&t;0x0D&t;/* flush HDLC-level data buffers */
DECL|macro|X25_HDLC_SPRVS_CNT_STAT
mdefine_line|#define X25_HDLC_SPRVS_CNT_STAT 0x0F&t;/* read surervisory count status */
DECL|macro|X25_HDLC_SEND_UI_FRAME
mdefine_line|#define X25_HDLC_SEND_UI_FRAME&t;0x10&t;/* send unnumbered information frame */
DECL|macro|X25_HDLC_WRITE
mdefine_line|#define X25_HDLC_WRITE&t;&t;0x11&t;/* send HDLC information frame */
DECL|macro|X25_HDLC_READ
mdefine_line|#define X25_HDLC_READ&t;&t;0x21&t;/* read HDLC information frame */
DECL|macro|X25_HDLC_READ_CONFIG
mdefine_line|#define X25_HDLC_READ_CONFIG&t;0x12&t;/* read HDLC configuration */
DECL|macro|X25_HDLC_SET_CONFIG
mdefine_line|#define X25_HDLC_SET_CONFIG&t;0x13&t;/* set HDLC configuration */
DECL|macro|SET_PROTOCOL_LEVEL
mdefine_line|#define SET_PROTOCOL_LEVEL&t;0x1F&t;/* set protocol level */
multiline_comment|/*----- X.25-level commands -----------*/
DECL|macro|X25_READ
mdefine_line|#define X25_READ&t;&t;0x22&t;/* read X.25 packet */
DECL|macro|X25_WRITE
mdefine_line|#define X25_WRITE&t;&t;0x23&t;/* send X.25 packet */
DECL|macro|X25_PLACE_CALL
mdefine_line|#define X25_PLACE_CALL&t;&t;0x30&t;/* place a call on SVC */
DECL|macro|X25_ACCEPT_CALL
mdefine_line|#define X25_ACCEPT_CALL&t;&t;0x31&t;/* accept incomming call */
DECL|macro|X25_CLEAR_CALL
mdefine_line|#define X25_CLEAR_CALL&t;&t;0x32&t;/* clear call */
DECL|macro|X25_CLEAR_CONFRM
mdefine_line|#define X25_CLEAR_CONFRM&t;0x33&t;/* send clear confirmation packet */
DECL|macro|X25_RESET
mdefine_line|#define X25_RESET&t;&t;0x34&t;/* send reset request packet */
DECL|macro|X25_RESET_CONFRM
mdefine_line|#define X25_RESET_CONFRM&t;0x35&t;/* send reset confirmation packet */
DECL|macro|X25_RESTART
mdefine_line|#define X25_RESTART&t;&t;0x36&t;/* send restart request packet */
DECL|macro|X25_RESTART_CONFRM
mdefine_line|#define X25_RESTART_CONFRM&t;0x37&t;/* send restart confirmation packet */
DECL|macro|X25_INTERRUPT
mdefine_line|#define X25_INTERRUPT&t;&t;0x38&t;/* send interrupt request packet */
DECL|macro|X25_INTERRUPT_CONFRM
mdefine_line|#define X25_INTERRUPT_CONFRM&t;0x39&t;/* send interrupt confirmation pkt */
DECL|macro|X25_REGISTRATION_RQST
mdefine_line|#define X25_REGISTRATION_RQST&t;0x3A&t;/* send registration request packet */
DECL|macro|X25_REGISTRATION_CONFRM
mdefine_line|#define X25_REGISTRATION_CONFRM&t;0x3B&t;/* send registration confirmation */
DECL|macro|X25_IS_DATA_AVAILABLE
mdefine_line|#define X25_IS_DATA_AVAILABLE&t;0x40&t;/* querry receive queue */
DECL|macro|X25_INCOMMING_CALL_CTL
mdefine_line|#define X25_INCOMMING_CALL_CTL&t;0x41&t;/* select incomming call options */
DECL|macro|X25_CONFIGURE_PVC
mdefine_line|#define X25_CONFIGURE_PVC&t;0x42&t;/* configure PVC */
DECL|macro|X25_GET_ACTIVE_CHANNELS
mdefine_line|#define X25_GET_ACTIVE_CHANNELS&t;0x43&t;/* get a list of active circuits */
DECL|macro|X25_READ_CHANNEL_CONFIG
mdefine_line|#define X25_READ_CHANNEL_CONFIG&t;0x44&t;/* read virt. circuit configuration */
DECL|macro|X25_FLUSH_DATA_BUFFERS
mdefine_line|#define X25_FLUSH_DATA_BUFFERS&t;0x45&t;/* flush X.25-level data buffers */
DECL|macro|X25_READ_HISTORY_TABLE
mdefine_line|#define X25_READ_HISTORY_TABLE&t;0x46&t;/* read asynchronous event log */
DECL|macro|X25_HISTORY_TABLE_CTL
mdefine_line|#define X25_HISTORY_TABLE_CTL&t;0x47&t;/* control asynchronous event log */
DECL|macro|X25_GET_TX_D_BIT_STATUS
mdefine_line|#define&t;X25_GET_TX_D_BIT_STATUS&t;0x48&t;/* is packet with D-bit acknowleged */
DECL|macro|X25_READ_STATISTICS
mdefine_line|#define&t;X25_READ_STATISTICS&t;0x49&t;/* read X.25-level statistics */
DECL|macro|X25_FLUSH_STATISTICS
mdefine_line|#define&t;X25_FLUSH_STATISTICS&t;0x4A&t;/* flush X.25-level statistics */
DECL|macro|X25_READ_CONFIGURATION
mdefine_line|#define&t;X25_READ_CONFIGURATION&t;0x50&t;/* read HDLC &amp; X.25 configuration */
DECL|macro|X25_SET_CONFIGURATION
mdefine_line|#define&t;X25_SET_CONFIGURATION&t;0x51&t;/* set HDLC &amp; X.25 configuration */
multiline_comment|/*&n; * Defines for the &squot;result&squot; field.&n; */
multiline_comment|/*----- General results ---------------*/
DECL|macro|X25RES_OK
mdefine_line|#define X25RES_OK&t;&t;0x00
DECL|macro|X25RES_ERROR
mdefine_line|#define X25RES_ERROR&t;&t;0x01
DECL|macro|X25RES_LINK_NOT_IN_ABM
mdefine_line|#define X25RES_LINK_NOT_IN_ABM&t;0x02&t;/* link is not in ABM mode */
DECL|macro|X25RES_LINK_CLOSED
mdefine_line|#define X25RES_LINK_CLOSED&t;0x03
DECL|macro|X25RES_INVAL_LENGTH
mdefine_line|#define X25RES_INVAL_LENGTH&t;0x04
DECL|macro|X25RES_INVAL_CMD
mdefine_line|#define X25RES_INVAL_CMD&t;0x05
DECL|macro|X25RES_UNNUMBERED_FRAME
mdefine_line|#define X25RES_UNNUMBERED_FRAME&t;0x06&t;/* unnunbered frame received */
DECL|macro|X25RES_FRM_REJECT_MODE
mdefine_line|#define X25RES_FRM_REJECT_MODE&t;0x07&t;/* link is in Frame Reject mode */
DECL|macro|X25RES_MODEM_FAILURE
mdefine_line|#define X25RES_MODEM_FAILURE&t;0x08&t;/* DCD and/or CTS dropped */
DECL|macro|X25RES_N2_RETRY_LIMIT
mdefine_line|#define X25RES_N2_RETRY_LIMIT&t;0x09&t;/* N2 retry limit has been exceeded */
DECL|macro|X25RES_INVAL_LCN
mdefine_line|#define X25RES_INVAL_LCN&t;0x30&t;/* invalid logical channel number */
DECL|macro|X25RES_INVAL_STATE
mdefine_line|#define X25RES_INVAL_STATE&t;0x31&t;/* channel is not in data xfer mode */
DECL|macro|X25RES_INVAL_DATA_LEN
mdefine_line|#define X25RES_INVAL_DATA_LEN&t;0x32&t;/* invalid data length */
DECL|macro|X25RES_NOT_READY
mdefine_line|#define X25RES_NOT_READY&t;0x33&t;/* no data available / buffers full */
DECL|macro|X25RES_NETWORK_DOWN
mdefine_line|#define X25RES_NETWORK_DOWN&t;0x34
DECL|macro|X25RES_CHANNEL_IN_USE
mdefine_line|#define X25RES_CHANNEL_IN_USE&t;0x35&t;/* there is data queued on this LCN */
DECL|macro|X25RES_REGST_NOT_SUPPRT
mdefine_line|#define X25RES_REGST_NOT_SUPPRT&t;0x36&t;/* registration not supported */
DECL|macro|X25RES_INVAL_FORMAT
mdefine_line|#define X25RES_INVAL_FORMAT&t;0x37&t;/* invalid packet format */
DECL|macro|X25RES_D_BIT_NOT_SUPPRT
mdefine_line|#define X25RES_D_BIT_NOT_SUPPRT&t;0x38&t;/* D-bit pragmatics not supported */
DECL|macro|X25RES_FACIL_NOT_SUPPRT
mdefine_line|#define X25RES_FACIL_NOT_SUPPRT&t;0x39&t;/* Call facility not supported */
DECL|macro|X25RES_INVAL_CALL_ARG
mdefine_line|#define X25RES_INVAL_CALL_ARG&t;0x3A&t;/* errorneous call arguments */
DECL|macro|X25RES_INVAL_CALL_DATA
mdefine_line|#define X25RES_INVAL_CALL_DATA&t;0x3B&t;/* errorneous call user data */
DECL|macro|X25RES_ASYNC_PACKET
mdefine_line|#define X25RES_ASYNC_PACKET&t;0x40&t;/* asynchronous packet received */
DECL|macro|X25RES_PROTO_VIOLATION
mdefine_line|#define X25RES_PROTO_VIOLATION&t;0x41&t;/* protocol violation occured */
DECL|macro|X25RES_PKT_TIMEOUT
mdefine_line|#define X25RES_PKT_TIMEOUT&t;0x42&t;/* X.25 packet time out */
DECL|macro|X25RES_PKT_RETRY_LIMIT
mdefine_line|#define X25RES_PKT_RETRY_LIMIT&t;0x43&t;/* X.25 packet retry limit exceeded */
multiline_comment|/*----- Command-dependant results -----*/
DECL|macro|X25RES_LINK_DISC
mdefine_line|#define X25RES_LINK_DISC&t;0x00&t;/* HDLC_LINK_STATUS */
DECL|macro|X25RES_LINK_IN_ABM
mdefine_line|#define X25RES_LINK_IN_ABM&t;0x01&t;/* HDLC_LINK_STATUS */
DECL|macro|X25RES_NO_DATA
mdefine_line|#define X25RES_NO_DATA&t;&t;0x01&t;/* HDLC_READ/READ_TRACE_DATA*/
DECL|macro|X25RES_TRACE_INACTIVE
mdefine_line|#define X25RES_TRACE_INACTIVE&t;0x02&t;/* READ_TRACE_DATA */
DECL|macro|X25RES_LINK_IS_OPEN
mdefine_line|#define X25RES_LINK_IS_OPEN&t;0x01&t;/* HDLC_LINK_OPEN */
DECL|macro|X25RES_LINK_IS_DISC
mdefine_line|#define X25RES_LINK_IS_DISC&t;0x02&t;/* HDLC_LINK_DISC */
DECL|macro|X25RES_LINK_IS_CLOSED
mdefine_line|#define X25RES_LINK_IS_CLOSED&t;0x03&t;/* HDLC_LINK_CLOSE */
DECL|macro|X25RES_INVAL_PARAM
mdefine_line|#define X25RES_INVAL_PARAM&t;0x31&t;/* INCOMMING_CALL_CTL */
DECL|macro|X25RES_INVAL_CONFIG
mdefine_line|#define X25RES_INVAL_CONFIG&t;0x35&t;/* REGISTR_RQST/CONFRM */
multiline_comment|/*&n; * Defines for the &squot;qdm_bits&squot; field.&n; */
DECL|macro|X25CMD_Q_BIT_MASK
mdefine_line|#define X25CMD_Q_BIT_MASK&t;0x04
DECL|macro|X25CMD_D_BIT_MASK
mdefine_line|#define X25CMD_D_BIT_MASK&t;0x02
DECL|macro|X25CMD_M_BIT_MASK
mdefine_line|#define X25CMD_M_BIT_MASK&t;0x01
multiline_comment|/*&n; * Defines for the &squot;pkt_type&squot; field.&n; */
multiline_comment|/*----- Asynchronous events ------*/
DECL|macro|ASE_CLEAR_RQST
mdefine_line|#define ASE_CLEAR_RQST&t;&t;0x02
DECL|macro|ASE_RESET_RQST
mdefine_line|#define ASE_RESET_RQST&t;&t;0x04
DECL|macro|ASE_RESTART_RQST
mdefine_line|#define ASE_RESTART_RQST&t;0x08
DECL|macro|ASE_INTERRUPT
mdefine_line|#define ASE_INTERRUPT&t;&t;0x10
DECL|macro|ASE_DTE_REGISTR_RQST
mdefine_line|#define ASE_DTE_REGISTR_RQST&t;0x20
DECL|macro|ASE_CALL_RQST
mdefine_line|#define ASE_CALL_RQST&t;&t;0x30
DECL|macro|ASE_CALL_ACCEPTED
mdefine_line|#define ASE_CALL_ACCEPTED&t;0x31
DECL|macro|ASE_CLEAR_CONFRM
mdefine_line|#define ASE_CLEAR_CONFRM&t;0x32
DECL|macro|ASE_RESET_CONFRM
mdefine_line|#define ASE_RESET_CONFRM&t;0x33
DECL|macro|ASE_RESTART_CONFRM
mdefine_line|#define ASE_RESTART_CONFRM&t;0x34
DECL|macro|ASE_INTERRUPT_CONFRM
mdefine_line|#define ASE_INTERRUPT_CONFRM&t;0x35
DECL|macro|ASE_DCE_REGISTR_CONFRM
mdefine_line|#define ASE_DCE_REGISTR_CONFRM&t;0x36
DECL|macro|ASE_DIAGNOSTIC
mdefine_line|#define ASE_DIAGNOSTIC&t;&t;0x37
DECL|macro|ASE_CALL_AUTO_CLEAR
mdefine_line|#define ASE_CALL_AUTO_CLEAR&t;0x38
DECL|macro|AUTO_RESPONSE_FLAG
mdefine_line|#define AUTO_RESPONSE_FLAG&t;0x80
multiline_comment|/*----- Time-Out events ----------*/
DECL|macro|TOE_RESTART_RQST
mdefine_line|#define TOE_RESTART_RQST&t;0x03
DECL|macro|TOE_CALL_RQST
mdefine_line|#define TOE_CALL_RQST&t;&t;0x05
DECL|macro|TOE_CLEAR_RQST
mdefine_line|#define TOE_CLEAR_RQST&t;&t;0x08
DECL|macro|TOE_RESET_RQST
mdefine_line|#define TOE_RESET_RQST&t;&t;0x0A
multiline_comment|/*----- Protocol Violation events */
DECL|macro|PVE_CLEAR_RQST
mdefine_line|#define PVE_CLEAR_RQST&t;&t;0x32
DECL|macro|PVE_RESET_RQST
mdefine_line|#define PVE_RESET_RQST&t;&t;0x33
DECL|macro|PVE_RESTART_RQST
mdefine_line|#define PVE_RESTART_RQST&t;0x34
DECL|macro|PVE_DIAGNOSTIC
mdefine_line|#define PVE_DIAGNOSTIC&t;&t;0x37
DECL|macro|INTR_ON_RX_FRAME
mdefine_line|#define INTR_ON_RX_FRAME            0x01
DECL|macro|INTR_ON_TX_FRAME
mdefine_line|#define INTR_ON_TX_FRAME            0x02
DECL|macro|INTR_ON_MODEM_STATUS_CHANGE
mdefine_line|#define INTR_ON_MODEM_STATUS_CHANGE 0x04
DECL|macro|INTR_ON_COMMAND_COMPLETE
mdefine_line|#define INTR_ON_COMMAND_COMPLETE    0x08
DECL|macro|INTR_ON_X25_ASY_TRANSACTION
mdefine_line|#define INTR_ON_X25_ASY_TRANSACTION 0x10
DECL|macro|INTR_ON_TIMER
mdefine_line|#define INTR_ON_TIMER&t;&t;    0x40
DECL|macro|DIRECT_RX_INTR_USAGE
mdefine_line|#define DIRECT_RX_INTR_USAGE        0x80
DECL|macro|NO_INTR_PENDING
mdefine_line|#define NO_INTR_PENDING  &t;        0x00
DECL|macro|RX_INTR_PENDING
mdefine_line|#define RX_INTR_PENDING&t;&t;&t;0x01&t;
DECL|macro|TX_INTR_PENDING
mdefine_line|#define TX_INTR_PENDING&t;&t;&t;0x02
DECL|macro|MODEM_INTR_PENDING
mdefine_line|#define MODEM_INTR_PENDING&t;&t;0x04
DECL|macro|COMMAND_COMPLETE_INTR_PENDING
mdefine_line|#define COMMAND_COMPLETE_INTR_PENDING &t;0x08
DECL|macro|X25_ASY_TRANS_INTR_PENDING
mdefine_line|#define X25_ASY_TRANS_INTR_PENDING&t;0x10
DECL|macro|TIMER_INTR_PENDING
mdefine_line|#define TIMER_INTR_PENDING&t;&t;0x40
multiline_comment|/*----------------------------------------------------------------------------&n; * X.25 Mailbox.&n; *&t;This structure is located at offsets X25_MBOX_OFFS and X25_RXMBOX_OFFS&n; *&t;into shared memory window.&n; */
DECL|struct|X25Mbox
r_typedef
r_struct
id|X25Mbox
(brace
DECL|member|PACKED
r_int
r_char
id|opflag
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: execution flag */
DECL|member|PACKED
id|TX25Cmd
id|cmd
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: command block */
DECL|member|PACKED
r_int
r_char
id|data
(braket
l_int|1
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 10h: data buffer */
DECL|typedef|TX25Mbox
)brace
id|TX25Mbox
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * X.25 Time Stamp Structure.&n; */
DECL|struct|X25TimeStamp
r_typedef
r_struct
id|X25TimeStamp
(brace
DECL|member|PACKED
r_int
r_char
id|month
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|date
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|sec
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|min
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|hour
id|PACKED
suffix:semicolon
DECL|typedef|TX25TimeStamp
)brace
id|TX25TimeStamp
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * X.25 Status Block.&n; *&t;This structure is located at offset X25_STATUS_OFF into shared memory&n; *&t;window.&n; */
DECL|struct|X25Status
r_typedef
r_struct
id|X25Status
(brace
DECL|member|PACKED
r_int
r_int
id|pvc_map
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: PVC map */
DECL|member|PACKED
r_int
r_int
id|icc_map
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: Incomming Chan. map */
DECL|member|PACKED
r_int
r_int
id|twc_map
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: Two-way Cnan. map */
DECL|member|PACKED
r_int
r_int
id|ogc_map
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: Outgoing Chan. map */
DECL|member|PACKED
id|TX25TimeStamp
id|tstamp
id|PACKED
suffix:semicolon
multiline_comment|/* 08h: timestamp (BCD) */
DECL|member|PACKED
r_int
r_char
id|iflags
id|PACKED
suffix:semicolon
multiline_comment|/* 0Dh: interrupt flags */
DECL|member|PACKED
r_int
r_char
id|imask
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh: interrupt mask  */
DECL|member|PACKED
r_int
r_char
id|resrv
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh: */
DECL|member|PACKED
r_int
r_char
id|gflags
id|PACKED
suffix:semicolon
multiline_comment|/* 10h: misc. HDLC/X25 flags */
DECL|member|PACKED
r_int
r_char
id|cflags
(braket
id|X25_MAX_CHAN
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* channel status bytes */
DECL|typedef|TX25Status
)brace
id|TX25Status
suffix:semicolon
multiline_comment|/*&n; * Bitmasks for the &squot;iflags&squot; field.&n; */
DECL|macro|X25_RX_INTR
mdefine_line|#define X25_RX_INTR&t;0x01&t;/* receive interrupt */
DECL|macro|X25_TX_INTR
mdefine_line|#define X25_TX_INTR&t;0x02&t;/* transmit interrupt */
DECL|macro|X25_MODEM_INTR
mdefine_line|#define X25_MODEM_INTR&t;0x04&t;/* modem status interrupt (CTS/DCD) */
DECL|macro|X25_EVENT_INTR
mdefine_line|#define X25_EVENT_INTR&t;0x10&t;/* asyncronous event encountered */
DECL|macro|X25_CMD_INTR
mdefine_line|#define X25_CMD_INTR&t;0x08&t;/* interface command complete */
multiline_comment|/*&n; * Bitmasks for the &squot;gflags&squot; field.&n; */
DECL|macro|X25_HDLC_ABM
mdefine_line|#define X25_HDLC_ABM&t;0x01&t;/* HDLC is in ABM mode */
DECL|macro|X25_RX_READY
mdefine_line|#define X25_RX_READY&t;0x02&t;/* X.25 data available */
DECL|macro|X25_TRACE_READY
mdefine_line|#define X25_TRACE_READY&t;0x08&t;/* trace data available */
DECL|macro|X25_EVENT_IND
mdefine_line|#define X25_EVENT_IND&t;0x20&t;/* asynchronous event indicator */
DECL|macro|X25_TX_READY
mdefine_line|#define X25_TX_READY&t;0x40&t;/* space is available in Tx buf.*/
multiline_comment|/*&n; * Bitmasks for the &squot;cflags&squot; field.&n; */
DECL|macro|X25_XFER_MODE
mdefine_line|#define X25_XFER_MODE&t;0x80&t;/* channel is in data transfer mode */
DECL|macro|X25_TXWIN_OPEN
mdefine_line|#define X25_TXWIN_OPEN&t;0x40&t;/* transmit window open */
DECL|macro|X25_RXBUF_MASK
mdefine_line|#define X25_RXBUF_MASK&t;0x3F&t;/* number of data buffers available */
multiline_comment|/*****************************************************************************&n; * Following definitions structurize contents of the TX25Mbox.data field for&n; * different X.25 interface commands.&n; ****************************************************************************/
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_SET_GLOBAL_VARS Command.&n; */
DECL|struct|X25GlobalVars
r_typedef
r_struct
id|X25GlobalVars
(brace
DECL|member|PACKED
r_int
r_char
id|resrv
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: reserved */
DECL|member|PACKED
r_int
r_char
id|dtrCtl
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: DTR control code */
DECL|member|PACKED
r_int
r_char
id|resErr
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: &squot;1&squot; - reset modem error */
DECL|typedef|TX25GlobalVars
)brace
id|TX25GlobalVars
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;dtrCtl&squot; field.&n; */
DECL|macro|X25_RAISE_DTR
mdefine_line|#define X25_RAISE_DTR&t;0x01
DECL|macro|X25_DROP_DTR
mdefine_line|#define X25_DROP_DTR&t;0x02
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_READ_MODEM_STATUS Command.&n; */
DECL|struct|X25ModemStatus
r_typedef
r_struct
id|X25ModemStatus
(brace
DECL|member|PACKED
r_int
r_char
id|status
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: modem status */
DECL|typedef|TX25ModemStatus
)brace
id|TX25ModemStatus
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;status&squot; field.&n; */
DECL|macro|X25_CTS_MASK
mdefine_line|#define X25_CTS_MASK&t;0x20
DECL|macro|X25_DCD_MASK
mdefine_line|#define X25_DCD_MASK&t;0x08
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_HDLC_LINK_STATUS Command.&n; */
DECL|struct|X25LinkStatus
r_typedef
r_struct
id|X25LinkStatus
(brace
DECL|member|PACKED
r_int
r_char
id|txQueued
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: queued Tx I-frames*/
DECL|member|PACKED
r_int
r_char
id|rxQueued
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: queued Rx I-frames*/
DECL|member|PACKED
r_int
r_char
id|station
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: DTE/DCE config. */
DECL|member|PACKED
r_int
r_char
id|reserved
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: reserved */
DECL|member|PACKED
r_int
r_char
id|sfTally
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: supervisory frame tally */
DECL|typedef|TX25LinkStatus
)brace
id|TX25LinkStatus
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;station&squot; field.&n; */
DECL|macro|X25_STATION_DTE
mdefine_line|#define&t;X25_STATION_DTE&t;0x01&t;/* station configured as DTE */
DECL|macro|X25_STATION_DCE
mdefine_line|#define X25_STATION_DCE&t;0x02&t;/* station configured as DCE */
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_HDLC_READ_STATS Command.&n; */
DECL|struct|HdlcStats
r_typedef
r_struct
id|HdlcStats
(brace
multiline_comment|/*&t;a number of ... */
DECL|member|PACKED
r_int
r_int
id|rxIFrames
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: ready Rx I-frames */
DECL|member|PACKED
r_int
r_int
id|rxNoseq
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: frms out-of-sequence */
DECL|member|PACKED
r_int
r_int
id|rxNodata
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: I-frms without data */
DECL|member|PACKED
r_int
r_int
id|rxDiscarded
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: discarded frames */
DECL|member|PACKED
r_int
r_int
id|rxTooLong
id|PACKED
suffix:semicolon
multiline_comment|/* 08h: frames too long */
DECL|member|PACKED
r_int
r_int
id|rxBadAddr
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah: frms with inval.addr*/
DECL|member|PACKED
r_int
r_int
id|txAcked
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch: acknowledged I-frms */
DECL|member|PACKED
r_int
r_int
id|txRetransm
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh: re-transmit. I-frms */
DECL|member|PACKED
r_int
r_int
id|t1Timeout
id|PACKED
suffix:semicolon
multiline_comment|/* 10h: T1 timeouts */
DECL|member|PACKED
r_int
r_int
id|rxSABM
id|PACKED
suffix:semicolon
multiline_comment|/* 12h: received SABM frames */
DECL|member|PACKED
r_int
r_int
id|rxDISC
id|PACKED
suffix:semicolon
multiline_comment|/* 14h: received DISC frames */
DECL|member|PACKED
r_int
r_int
id|rxDM
id|PACKED
suffix:semicolon
multiline_comment|/* 16h: received DM frames */
DECL|member|PACKED
r_int
r_int
id|rxFRMR
id|PACKED
suffix:semicolon
multiline_comment|/* 18h: FRMR frames received */
DECL|member|PACKED
r_int
r_int
id|txSABM
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ah: transm. SABM frames*/
DECL|member|PACKED
r_int
r_int
id|txDISC
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ch: transm. DISC frames*/
DECL|member|PACKED
r_int
r_int
id|txDM
id|PACKED
suffix:semicolon
multiline_comment|/* 1Eh: transm. DM frames */
DECL|member|PACKED
r_int
r_int
id|txFRMR
id|PACKED
suffix:semicolon
multiline_comment|/* 20h: transm. FRMR frames*/
DECL|typedef|THdlcStats
)brace
id|THdlcStats
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_HDLC_READ_COMM_ERR Command.&n; */
DECL|struct|HdlcCommErr
r_typedef
r_struct
id|HdlcCommErr
(brace
multiline_comment|/*&t;a number of ... */
DECL|member|PACKED
r_int
r_char
id|rxOverrun
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: Rx overrun errors */
DECL|member|PACKED
r_int
r_char
id|rxBadCrc
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: Rx CRC errors */
DECL|member|PACKED
r_int
r_char
id|rxAborted
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: Rx aborted frames */
DECL|member|PACKED
r_int
r_char
id|rxDropped
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: frames lost */
DECL|member|PACKED
r_int
r_char
id|txAborted
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: Tx aborted frames */
DECL|member|PACKED
r_int
r_char
id|txUnderrun
id|PACKED
suffix:semicolon
multiline_comment|/* 05h: Tx underrun errors */
DECL|member|PACKED
r_int
r_char
id|txMissIntr
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: missed underrun ints */
DECL|member|PACKED
r_int
r_char
id|reserved
id|PACKED
suffix:semicolon
multiline_comment|/* 07h: reserved */
DECL|member|PACKED
r_int
r_char
id|droppedDCD
id|PACKED
suffix:semicolon
multiline_comment|/* 08h: times DCD dropped */
DECL|member|PACKED
r_int
r_char
id|droppedCTS
id|PACKED
suffix:semicolon
multiline_comment|/* 09h: times CTS dropped */
DECL|typedef|THdlcCommErr
)brace
id|THdlcCommErr
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_SET_CONFIGURATION &amp; X25_READ_CONFIGURATION Commands.&n; */
DECL|struct|X25Config
r_typedef
r_struct
id|X25Config
(brace
DECL|member|PACKED
r_int
r_char
id|baudRate
id|PACKED
suffix:semicolon
multiline_comment|/* 00h:  */
DECL|member|PACKED
r_int
r_char
id|t1
id|PACKED
suffix:semicolon
multiline_comment|/* 01h:  */
DECL|member|PACKED
r_int
r_char
id|t2
id|PACKED
suffix:semicolon
multiline_comment|/* 02h:  */
DECL|member|PACKED
r_int
r_char
id|n2
id|PACKED
suffix:semicolon
multiline_comment|/* 03h:  */
DECL|member|PACKED
r_int
r_int
id|hdlcMTU
id|PACKED
suffix:semicolon
multiline_comment|/* 04h:  */
DECL|member|PACKED
r_int
r_char
id|hdlcWindow
id|PACKED
suffix:semicolon
multiline_comment|/* 06h:  */
DECL|member|PACKED
r_int
r_char
id|t4
id|PACKED
suffix:semicolon
multiline_comment|/* 07h:  */
DECL|member|PACKED
r_int
r_char
id|autoModem
id|PACKED
suffix:semicolon
multiline_comment|/* 08h:  */
DECL|member|PACKED
r_int
r_char
id|autoHdlc
id|PACKED
suffix:semicolon
multiline_comment|/* 09h:  */
DECL|member|PACKED
r_int
r_char
id|hdlcOptions
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah:  */
DECL|member|PACKED
r_int
r_char
id|station
id|PACKED
suffix:semicolon
multiline_comment|/* 0Bh:  */
DECL|member|PACKED
r_int
r_char
id|pktWindow
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch:  */
DECL|member|PACKED
r_int
r_int
id|defPktSize
id|PACKED
suffix:semicolon
multiline_comment|/* 0Dh:  */
DECL|member|PACKED
r_int
r_int
id|pktMTU
id|PACKED
suffix:semicolon
multiline_comment|/* 0Fh:  */
DECL|member|PACKED
r_int
r_int
id|loPVC
id|PACKED
suffix:semicolon
multiline_comment|/* 11h:  */
DECL|member|PACKED
r_int
r_int
id|hiPVC
id|PACKED
suffix:semicolon
multiline_comment|/* 13h:  */
DECL|member|PACKED
r_int
r_int
id|loIncommingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 15h:  */
DECL|member|PACKED
r_int
r_int
id|hiIncommingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 17h:  */
DECL|member|PACKED
r_int
r_int
id|loTwoWaySVC
id|PACKED
suffix:semicolon
multiline_comment|/* 19h:  */
DECL|member|PACKED
r_int
r_int
id|hiTwoWaySVC
id|PACKED
suffix:semicolon
multiline_comment|/* 1Bh:  */
DECL|member|PACKED
r_int
r_int
id|loOutgoingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 1Dh:  */
DECL|member|PACKED
r_int
r_int
id|hiOutgoingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 1Fh:  */
DECL|member|PACKED
r_int
r_int
id|options
id|PACKED
suffix:semicolon
multiline_comment|/* 21h:  */
DECL|member|PACKED
r_int
r_char
id|responseOpt
id|PACKED
suffix:semicolon
multiline_comment|/* 23h:  */
DECL|member|PACKED
r_int
r_int
id|facil1
id|PACKED
suffix:semicolon
multiline_comment|/* 24h:  */
DECL|member|PACKED
r_int
r_int
id|facil2
id|PACKED
suffix:semicolon
multiline_comment|/* 26h:  */
DECL|member|PACKED
r_int
r_int
id|ccittFacil
id|PACKED
suffix:semicolon
multiline_comment|/* 28h:  */
DECL|member|PACKED
r_int
r_int
id|otherFacil
id|PACKED
suffix:semicolon
multiline_comment|/* 2Ah:  */
DECL|member|PACKED
r_int
r_int
id|ccittCompat
id|PACKED
suffix:semicolon
multiline_comment|/* 2Ch:  */
DECL|member|PACKED
r_int
r_char
id|t10t20
id|PACKED
suffix:semicolon
multiline_comment|/* 2Eh:  */
DECL|member|PACKED
r_int
r_char
id|t11t21
id|PACKED
suffix:semicolon
multiline_comment|/* 2Fh:  */
DECL|member|PACKED
r_int
r_char
id|t12t22
id|PACKED
suffix:semicolon
multiline_comment|/* 30h:  */
DECL|member|PACKED
r_int
r_char
id|t13t23
id|PACKED
suffix:semicolon
multiline_comment|/* 31h:  */
DECL|member|PACKED
r_int
r_char
id|t16t26
id|PACKED
suffix:semicolon
multiline_comment|/* 32H:  */
DECL|member|PACKED
r_int
r_char
id|t28
id|PACKED
suffix:semicolon
multiline_comment|/* 33h:  */
DECL|member|PACKED
r_int
r_char
id|r10r20
id|PACKED
suffix:semicolon
multiline_comment|/* 34h:  */
DECL|member|PACKED
r_int
r_char
id|r12r22
id|PACKED
suffix:semicolon
multiline_comment|/* 35h:  */
DECL|member|PACKED
r_int
r_char
id|r13r23
id|PACKED
suffix:semicolon
multiline_comment|/* 36h:  */
DECL|typedef|TX25Config
)brace
id|TX25Config
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_READ_CHANNEL_CONFIG Command.&n; */
DECL|struct|X25ChanAlloc
r_typedef
r_struct
id|X25ChanAlloc
multiline_comment|/*----- Channel allocation -*/
(brace
DECL|member|PACKED
r_int
r_int
id|loPVC
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: lowest PVC number */
DECL|member|PACKED
r_int
r_int
id|hiPVC
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: highest PVC number */
DECL|member|PACKED
r_int
r_int
id|loIncommingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: lowest incoming SVC */
DECL|member|PACKED
r_int
r_int
id|hiIncommingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: highest incoming SVC */
DECL|member|PACKED
r_int
r_int
id|loTwoWaySVC
id|PACKED
suffix:semicolon
multiline_comment|/* 08h: lowest two-way SVC */
DECL|member|PACKED
r_int
r_int
id|hiTwoWaySVC
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah: highest two-way SVC */
DECL|member|PACKED
r_int
r_int
id|loOutgoingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch: lowest outgoing SVC */
DECL|member|PACKED
r_int
r_int
id|hiOutgoingSVC
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh: highest outgoing SVC */
DECL|typedef|TX25ChanAlloc
)brace
id|TX25ChanAlloc
suffix:semicolon
DECL|struct|X25ChanCfg
r_typedef
r_struct
id|X25ChanCfg
multiline_comment|/*------ Channel configuration -----*/
(brace
DECL|member|PACKED
r_int
r_char
id|type
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: channel type */
DECL|member|PACKED
r_int
r_char
id|txConf
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: Tx packet and window sizes */
DECL|member|PACKED
r_int
r_char
id|rxConf
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: Rx packet and window sizes */
DECL|typedef|TX25ChanCfg
)brace
id|TX25ChanCfg
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;type&squot; field.&n; */
DECL|macro|X25_PVC
mdefine_line|#define&t;X25_PVC  &t;0x01&t;/* PVC */
DECL|macro|X25_SVC_IN
mdefine_line|#define&t;X25_SVC_IN&t;0x03&t;/* Incoming SVC */
DECL|macro|X25_SVC_TWOWAY
mdefine_line|#define&t;X25_SVC_TWOWAY&t;0x07&t;/* Two-way SVC */
DECL|macro|X25_SVC_OUT
mdefine_line|#define&t;X25_SVC_OUT&t;0x0B&t;/* Outgoing SVC */
multiline_comment|/*----------------------------------------------------------------------------&n; * X25_READ_STATISTICS Command.&n; */
DECL|struct|X25Stats
r_typedef
r_struct
id|X25Stats
(brace
multiline_comment|/* number of packets Tx/Rx&squot;ed */
DECL|member|PACKED
r_int
r_int
id|txRestartRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: Restart Request */
DECL|member|PACKED
r_int
r_int
id|rxRestartRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: Restart Request */
DECL|member|PACKED
r_int
r_int
id|txRestartConf
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: Restart Confirmation */
DECL|member|PACKED
r_int
r_int
id|rxRestartConf
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: Restart Confirmation */
DECL|member|PACKED
r_int
r_int
id|txResetRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 08h: Reset Request */
DECL|member|PACKED
r_int
r_int
id|rxResetRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ah: Reset Request */
DECL|member|PACKED
r_int
r_int
id|txResetConf
id|PACKED
suffix:semicolon
multiline_comment|/* 0Ch: Reset Confirmation */
DECL|member|PACKED
r_int
r_int
id|rxResetConf
id|PACKED
suffix:semicolon
multiline_comment|/* 0Eh: Reset Confirmation */
DECL|member|PACKED
r_int
r_int
id|txCallRequest
id|PACKED
suffix:semicolon
multiline_comment|/* 10h: Call Request */
DECL|member|PACKED
r_int
r_int
id|rxCallRequest
id|PACKED
suffix:semicolon
multiline_comment|/* 12h: Call Request */
DECL|member|PACKED
r_int
r_int
id|txCallAccept
id|PACKED
suffix:semicolon
multiline_comment|/* 14h: Call Accept */
DECL|member|PACKED
r_int
r_int
id|rxCallAccept
id|PACKED
suffix:semicolon
multiline_comment|/* 16h: Call Accept */
DECL|member|PACKED
r_int
r_int
id|txClearRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 18h: Clear Request */
DECL|member|PACKED
r_int
r_int
id|rxClearRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ah: Clear Request */
DECL|member|PACKED
r_int
r_int
id|txClearConf
id|PACKED
suffix:semicolon
multiline_comment|/* 1Ch: Clear Confirmation */
DECL|member|PACKED
r_int
r_int
id|rxClearConf
id|PACKED
suffix:semicolon
multiline_comment|/* 1Eh: Clear Confirmation */
DECL|member|PACKED
r_int
r_int
id|txDiagnostic
id|PACKED
suffix:semicolon
multiline_comment|/* 20h: Diagnostic */
DECL|member|PACKED
r_int
r_int
id|rxDiagnostic
id|PACKED
suffix:semicolon
multiline_comment|/* 22h: Diagnostic */
DECL|member|PACKED
r_int
r_int
id|txRegRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 24h: Registration Request */
DECL|member|PACKED
r_int
r_int
id|rxRegRqst
id|PACKED
suffix:semicolon
multiline_comment|/* 26h: Registration Request */
DECL|member|PACKED
r_int
r_int
id|txRegConf
id|PACKED
suffix:semicolon
multiline_comment|/* 28h: Registration Confirm.*/
DECL|member|PACKED
r_int
r_int
id|rxRegConf
id|PACKED
suffix:semicolon
multiline_comment|/* 2Ah: Registration Confirm.*/
DECL|member|PACKED
r_int
r_int
id|txInterrupt
id|PACKED
suffix:semicolon
multiline_comment|/* 2Ch: Interrupt */
DECL|member|PACKED
r_int
r_int
id|rxInterrupt
id|PACKED
suffix:semicolon
multiline_comment|/* 2Eh: Interrupt */
DECL|member|PACKED
r_int
r_int
id|txIntrConf
id|PACKED
suffix:semicolon
multiline_comment|/* 30h: Interrupt Confirm. */
DECL|member|PACKED
r_int
r_int
id|rxIntrConf
id|PACKED
suffix:semicolon
multiline_comment|/* 32h: Interrupt Confirm. */
DECL|member|PACKED
r_int
r_int
id|txData
id|PACKED
suffix:semicolon
multiline_comment|/* 34h: Data */
DECL|member|PACKED
r_int
r_int
id|rxData
id|PACKED
suffix:semicolon
multiline_comment|/* 36h: Data */
DECL|member|PACKED
r_int
r_int
id|txRR
id|PACKED
suffix:semicolon
multiline_comment|/* 38h: RR */
DECL|member|PACKED
r_int
r_int
id|rxRR
id|PACKED
suffix:semicolon
multiline_comment|/* 3Ah: RR */
DECL|member|PACKED
r_int
r_int
id|txRNR
id|PACKED
suffix:semicolon
multiline_comment|/* 3Ch: RNR */
DECL|member|PACKED
r_int
r_int
id|rxRNR
id|PACKED
suffix:semicolon
multiline_comment|/* 3Eh: RNR */
DECL|typedef|TX25Stats
)brace
id|TX25Stats
suffix:semicolon
multiline_comment|/*----------------------------------------------------------------------------&n; * X25_READ_HISTORY_TABLE Command.&n; */
DECL|struct|X25EventLog
r_typedef
r_struct
id|X25EventLog
(brace
DECL|member|PACKED
r_int
r_char
id|type
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: transaction type */
DECL|member|PACKED
r_int
r_int
id|lcn
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: logical channel num */
DECL|member|PACKED
r_int
r_char
id|packet
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: async packet type */
DECL|member|PACKED
r_int
r_char
id|cause
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: X.25 cause field */
DECL|member|PACKED
r_int
r_char
id|diag
id|PACKED
suffix:semicolon
multiline_comment|/* 05h: X.25 diag field */
DECL|member|PACKED
id|TX25TimeStamp
id|ts
id|PACKED
suffix:semicolon
multiline_comment|/* 06h: time stamp */
DECL|typedef|TX25EventLog
)brace
id|TX25EventLog
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;type&squot; field.&n; */
DECL|macro|X25LOG_INCOMMING
mdefine_line|#define X25LOG_INCOMMING&t;0x00
DECL|macro|X25LOG_APPLICATION
mdefine_line|#define X25LOG_APPLICATION &t;0x01
DECL|macro|X25LOG_AUTOMATIC
mdefine_line|#define X25LOG_AUTOMATIC&t;0x02
DECL|macro|X25LOG_ERROR
mdefine_line|#define X25LOG_ERROR&t;&t;0x04
DECL|macro|X25LOG_TIMEOUT
mdefine_line|#define X25LOG_TIMEOUT&t;&t;0x08
DECL|macro|X25LOG_RECOVERY
mdefine_line|#define X25LOG_RECOVERY&t;&t;0x10
multiline_comment|/*&n; * Defines for the &squot;packet&squot; field.&n; */
DECL|macro|X25LOG_CALL_RQST
mdefine_line|#define X25LOG_CALL_RQST&t;0x0B
DECL|macro|X25LOG_CALL_ACCEPTED
mdefine_line|#define X25LOG_CALL_ACCEPTED&t;0x0F
DECL|macro|X25LOG_CLEAR_RQST
mdefine_line|#define X25LOG_CLEAR_RQST&t;0x13
DECL|macro|X25LOG_CLEAR_CONFRM
mdefine_line|#define X25LOG_CLEAR_CONFRM&t;0x17
DECL|macro|X25LOG_RESET_RQST
mdefine_line|#define X25LOG_RESET_RQST&t;0x1B
DECL|macro|X25LOG_RESET_CONFRM
mdefine_line|#define X25LOG_RESET_CONFRM&t;0x1F
DECL|macro|X25LOG_RESTART_RQST
mdefine_line|#define X25LOG_RESTART_RQST&t;0xFB
DECL|macro|X25LOG_RESTART_COMFRM
mdefine_line|#define X25LOG_RESTART_COMFRM&t;0xFF
DECL|macro|X25LOG_DIAGNOSTIC
mdefine_line|#define X25LOG_DIAGNOSTIC&t;0xF1
DECL|macro|X25LOG_DTE_REG_RQST
mdefine_line|#define X25LOG_DTE_REG_RQST&t;0xF3
DECL|macro|X25LOG_DTE_REG_COMFRM
mdefine_line|#define X25LOG_DTE_REG_COMFRM&t;0xF7
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_TRACE_CONFIGURE Command.&n; */
DECL|struct|X25TraceCfg
r_typedef
r_struct
id|X25TraceCfg
(brace
DECL|member|PACKED
r_int
r_char
id|flags
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: trace configuration flags */
DECL|member|PACKED
r_int
r_char
id|timeout
id|PACKED
suffix:semicolon
multiline_comment|/* 01h: timeout for trace delay mode*/
DECL|typedef|TX25TraceCfg
)brace
id|TX25TraceCfg
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;flags&squot; field.&n; */
DECL|macro|X25_TRC_ENABLE
mdefine_line|#define X25_TRC_ENABLE&t;&t;0x01&t;/* bit0: &squot;1&squot; - trace enabled */
DECL|macro|X25_TRC_TIMESTAMP
mdefine_line|#define X25_TRC_TIMESTAMP&t;0x02&t;/* bit1: &squot;1&squot; - time stamping enabled*/
DECL|macro|X25_TRC_DELAY
mdefine_line|#define X25_TRC_DELAY&t;&t;0x04&t;/* bit2: &squot;1&squot; - trace delay enabled */
DECL|macro|X25_TRC_DATA
mdefine_line|#define X25_TRC_DATA&t;&t;0x08&t;/* bit3: &squot;1&squot; - trace data packets */
DECL|macro|X25_TRC_SUPERVISORY
mdefine_line|#define X25_TRC_SUPERVISORY&t;0x10    /* bit4: &squot;1&squot; - trace suprvisory pkts*/
DECL|macro|X25_TRC_ASYNCHRONOUS
mdefine_line|#define X25_TRC_ASYNCHRONOUS&t;0x20&t;/* bit5: &squot;1&squot; - trace asynch. packets*/
DECL|macro|X25_TRC_HDLC
mdefine_line|#define X25_TRC_HDLC&t;&t;0x40&t;/* bit6: &squot;1&squot; - trace all packets */
DECL|macro|X25_TRC_READ
mdefine_line|#define X25_TRC_READ&t;&t;0x80&t;/* bit7: &squot;1&squot; - get current config. */
multiline_comment|/* ---------------------------------------------------------------------------&n; * X25_READ_TRACE_DATA Command.&n; */
DECL|struct|X25Trace
r_typedef
r_struct
id|X25Trace
multiline_comment|/*----- Trace data structure -------*/
(brace
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
multiline_comment|/* 00h: trace data length */
DECL|member|PACKED
r_int
r_char
id|type
id|PACKED
suffix:semicolon
multiline_comment|/* 02h: trace type */
DECL|member|PACKED
r_int
r_char
id|lost_cnt
id|PACKED
suffix:semicolon
multiline_comment|/* 03h: N of traces lost */
DECL|member|PACKED
id|TX25TimeStamp
id|tstamp
id|PACKED
suffix:semicolon
multiline_comment|/* 04h: mon/date/sec/min/hour */
DECL|member|PACKED
r_int
r_int
id|millisec
id|PACKED
suffix:semicolon
multiline_comment|/* 09h: ms time stamp */
DECL|member|PACKED
r_int
r_char
id|data
(braket
l_int|0
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* 0Bh: traced frame */
DECL|typedef|TX25Trace
)brace
id|TX25Trace
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;type&squot; field.&n; */
DECL|macro|X25_TRC_TYPE_MASK
mdefine_line|#define X25_TRC_TYPE_MASK&t;0x0F&t;/* bits 0..3: trace type */
DECL|macro|X25_TRC_TYPE_RX_FRAME
mdefine_line|#define X25_TRC_TYPE_RX_FRAME&t;0x00&t;/* received frame trace */
DECL|macro|X25_TRC_TYPE_TX_FRAME
mdefine_line|#define X25_TRC_TYPE_TX_FRAME&t;0x01&t;/* transmitted frame */
DECL|macro|X25_TRC_TYPE_ERR_FRAME
mdefine_line|#define X25_TRC_TYPE_ERR_FRAME&t;0x02&t;/* error frame */
DECL|macro|X25_TRC_ERROR_MASK
mdefine_line|#define X25_TRC_ERROR_MASK&t;0xF0&t;/* bits 4..7: error code */
DECL|macro|X25_TRCERR_RX_ABORT
mdefine_line|#define X25_TRCERR_RX_ABORT&t;0x10&t;/* receive abort error */
DECL|macro|X25_TRCERR_RX_BADCRC
mdefine_line|#define X25_TRCERR_RX_BADCRC&t;0x20&t;/* receive CRC error */
DECL|macro|X25_TRCERR_RX_OVERRUN
mdefine_line|#define X25_TRCERR_RX_OVERRUN&t;0x30&t;/* receiver overrun error */
DECL|macro|X25_TRCERR_RX_TOO_LONG
mdefine_line|#define X25_TRCERR_RX_TOO_LONG&t;0x40&t;/* excessive frame length error */
DECL|macro|X25_TRCERR_TX_ABORT
mdefine_line|#define X25_TRCERR_TX_ABORT&t;0x70&t;/* aborted frame transmittion error */
DECL|macro|X25_TRCERR_TX_UNDERRUN
mdefine_line|#define X25_TRCERR_TX_UNDERRUN&t;0x80&t;/* transmit underrun error */
multiline_comment|/*****************************************************************************&n; * Following definitions describe HDLC frame and X.25 packet formats.&n; ****************************************************************************/
DECL|struct|HDLCFrame
r_typedef
r_struct
id|HDLCFrame
multiline_comment|/*----- DHLC Frame Format ----------*/
(brace
DECL|member|PACKED
r_int
r_char
id|addr
id|PACKED
suffix:semicolon
multiline_comment|/* address field */
DECL|member|PACKED
r_int
r_char
id|cntl
id|PACKED
suffix:semicolon
multiline_comment|/* control field */
DECL|member|PACKED
r_int
r_char
id|data
(braket
l_int|0
)braket
id|PACKED
suffix:semicolon
DECL|typedef|THDLCFrame
)brace
id|THDLCFrame
suffix:semicolon
DECL|struct|X25Pkt
r_typedef
r_struct
id|X25Pkt
multiline_comment|/*----- X.25 Paket Format ----------*/
(brace
DECL|member|PACKED
r_int
r_char
id|lcn_hi
id|PACKED
suffix:semicolon
multiline_comment|/* 4 MSB of Logical Channel Number */
DECL|member|PACKED
r_int
r_char
id|lcn_lo
id|PACKED
suffix:semicolon
multiline_comment|/* 8 LSB of Logical Channel Number */
DECL|member|PACKED
r_int
r_char
id|type
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|data
(braket
l_int|0
)braket
id|PACKED
suffix:semicolon
DECL|typedef|TX25Pkt
)brace
id|TX25Pkt
suffix:semicolon
multiline_comment|/*&n; * Defines for the &squot;lcn_hi&squot; field.&n; */
DECL|macro|X25_Q_BIT_MASK
mdefine_line|#define&t;X25_Q_BIT_MASK&t;&t;0x80&t;/* Data Qualifier Bit mask */
DECL|macro|X25_D_BIT_MASK
mdefine_line|#define&t;X25_D_BIT_MASK&t;&t;0x40&t;/* Delivery Confirmation Bit mask */
DECL|macro|X25_M_BITS_MASK
mdefine_line|#define&t;X25_M_BITS_MASK&t;&t;0x30&t;/* Modulo Bits mask */
DECL|macro|X25_LCN_MSB_MASK
mdefine_line|#define&t;X25_LCN_MSB_MASK&t;0x0F&t;/* LCN most significant bits mask */
multiline_comment|/*&n; * Defines for the &squot;type&squot; field.&n; */
DECL|macro|X25PKT_DATA
mdefine_line|#define&t;X25PKT_DATA&t;&t;0x01&t;/* Data packet mask */
DECL|macro|X25PKT_SUPERVISORY
mdefine_line|#define&t;X25PKT_SUPERVISORY&t;0x02&t;/* Supervisory packet mask */
DECL|macro|X25PKT_CALL_RQST
mdefine_line|#define&t;X25PKT_CALL_RQST&t;0x0B&t;/* Call Request/Incoming */
DECL|macro|X25PKT_CALL_ACCEPTED
mdefine_line|#define&t;X25PKT_CALL_ACCEPTED&t;0x0F&t;/* Call Accepted/Connected */
DECL|macro|X25PKT_CLEAR_RQST
mdefine_line|#define&t;X25PKT_CLEAR_RQST&t;0x13&t;/* Clear Request/Indication */
DECL|macro|X25PKT_CLEAR_CONFRM
mdefine_line|#define&t;X25PKT_CLEAR_CONFRM&t;0x17&t;/* Clear Confirmation */
DECL|macro|X25PKT_RESET_RQST
mdefine_line|#define&t;X25PKT_RESET_RQST&t;0x1B&t;/* Reset Request/Indication */
DECL|macro|X25PKT_RESET_CONFRM
mdefine_line|#define&t;X25PKT_RESET_CONFRM&t;0x1F&t;/* Reset Confirmation */
DECL|macro|X25PKT_RESTART_RQST
mdefine_line|#define&t;X25PKT_RESTART_RQST&t;0xFB&t;/* Restart Request/Indication */
DECL|macro|X25PKT_RESTART_CONFRM
mdefine_line|#define&t;X25PKT_RESTART_CONFRM&t;0xFF&t;/* Restart Confirmation */
DECL|macro|X25PKT_INTERRUPT
mdefine_line|#define&t;X25PKT_INTERRUPT&t;0x23&t;/* Interrupt */
DECL|macro|X25PKT_INTERRUPT_CONFRM
mdefine_line|#define&t;X25PKT_INTERRUPT_CONFRM&t;0x27&t;/* Interrupt Confirmation */
DECL|macro|X25PKT_DIAGNOSTIC
mdefine_line|#define&t;X25PKT_DIAGNOSTIC&t;0xF1&t;/* Diagnostic */
DECL|macro|X25PKT_REGISTR_RQST
mdefine_line|#define&t;X25PKT_REGISTR_RQST&t;0xF3&t;/* Registration Request */
DECL|macro|X25PKT_REGISTR_CONFRM
mdefine_line|#define&t;X25PKT_REGISTR_CONFRM&t;0xF7&t;/* Registration Confirmation */
DECL|macro|X25PKT_RR_MASKED
mdefine_line|#define&t;X25PKT_RR_MASKED&t;0x01&t;/* Receive Ready packet after masking */
DECL|macro|X25PKT_RNR_MASKED
mdefine_line|#define&t;X25PKT_RNR_MASKED&t;0x05&t;/* Receive Not Ready after masking  */
r_typedef
r_struct
(brace
DECL|member|PACKED
id|TX25Cmd
id|cmd
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_char
id|data
(braket
id|X25_MAX_DATA
)braket
id|PACKED
suffix:semicolon
DECL|typedef|mbox_cmd_t
)brace
id|mbox_cmd_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|qdm
id|PACKED
suffix:semicolon
multiline_comment|/* Q/D/M bits */
DECL|member|PACKED
r_int
r_char
id|cause
id|PACKED
suffix:semicolon
multiline_comment|/* cause field */
DECL|member|PACKED
r_int
r_char
id|diagn
id|PACKED
suffix:semicolon
multiline_comment|/* diagnostics */
DECL|member|PACKED
r_int
r_char
id|pktType
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|result
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|lcn
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_char
id|reserved
(braket
l_int|7
)braket
id|PACKED
suffix:semicolon
DECL|typedef|x25api_hdr_t
)brace
id|x25api_hdr_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
id|x25api_hdr_t
id|hdr
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_char
id|data
(braket
id|X25_MAX_DATA
)braket
id|PACKED
suffix:semicolon
DECL|typedef|x25api_t
)brace
id|x25api_t
suffix:semicolon
multiline_comment|/* &n; * XPIPEMON Definitions&n; */
multiline_comment|/* valid ip_protocol for UDP management */
DECL|macro|UDPMGMT_UDP_PROTOCOL
mdefine_line|#define UDPMGMT_UDP_PROTOCOL 0x11
DECL|macro|UDPMGMT_XPIPE_SIGNATURE
mdefine_line|#define UDPMGMT_XPIPE_SIGNATURE         &quot;XLINK8ND&quot;
DECL|macro|UDPMGMT_DRVRSTATS_SIGNATURE
mdefine_line|#define UDPMGMT_DRVRSTATS_SIGNATURE     &quot;DRVSTATS&quot;
multiline_comment|/* values for request/reply byte */
DECL|macro|UDPMGMT_REQUEST
mdefine_line|#define UDPMGMT_REQUEST&t;0x01
DECL|macro|UDPMGMT_REPLY
mdefine_line|#define UDPMGMT_REPLY&t;0x02
DECL|macro|UDP_OFFSET
mdefine_line|#define UDP_OFFSET&t;12
r_typedef
r_struct
(brace
DECL|member|PACKED
r_int
r_char
id|opp_flag
id|PACKED
suffix:semicolon
multiline_comment|/* the opp flag */
DECL|member|PACKED
r_int
r_char
id|command
id|PACKED
suffix:semicolon
multiline_comment|/* command code */
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
multiline_comment|/* transfer data length */
DECL|member|PACKED
r_int
r_char
id|result
id|PACKED
suffix:semicolon
multiline_comment|/* return code */
DECL|member|PACKED
r_int
r_char
id|pf
id|PACKED
suffix:semicolon
multiline_comment|/* P/F bit */
DECL|member|PACKED
r_int
r_int
id|lcn
id|PACKED
suffix:semicolon
multiline_comment|/* logical channel */
DECL|member|PACKED
r_int
r_char
id|qdm
id|PACKED
suffix:semicolon
multiline_comment|/* Q/D/M bits */
DECL|member|PACKED
r_int
r_char
id|cause
id|PACKED
suffix:semicolon
multiline_comment|/* cause field */
DECL|member|PACKED
r_int
r_char
id|diagn
id|PACKED
suffix:semicolon
multiline_comment|/* diagnostics */
DECL|member|PACKED
r_int
r_char
id|pktType
id|PACKED
suffix:semicolon
multiline_comment|/* packet type */
DECL|member|PACKED
r_int
r_char
id|resrv
(braket
l_int|4
)braket
id|PACKED
suffix:semicolon
multiline_comment|/* reserved */
DECL|typedef|cblock_t
)brace
id|cblock_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|PACKED
id|ip_pkt_t
id|ip_pkt
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|udp_pkt_t
id|udp_pkt
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|wp_mgmt_t
id|wp_mgmt
id|PACKED
suffix:semicolon
DECL|member|PACKED
id|cblock_t
id|cblock
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|data
(braket
l_int|4080
)braket
id|PACKED
suffix:semicolon
DECL|typedef|x25_udp_pkt_t
)brace
id|x25_udp_pkt_t
suffix:semicolon
DECL|struct|read_hdlc_stat
r_typedef
r_struct
id|read_hdlc_stat
(brace
DECL|member|PACKED
r_int
r_int
id|inf_frames_rx_ok
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|inf_frames_rx_out_of_seq
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|inf_frames_rx_no_data
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|inf_frames_rx_dropped
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|inf_frames_rx_data_too_long
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|inf_frames_rx_invalid_addr
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|inf_frames_tx_ok
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|inf_frames_tx_retransmit
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|T1_timeouts
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|SABM_frames_rx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|DISC_frames_rx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|DM_frames_rx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|FRMR_frames_rx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|SABM_frames_tx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|DISC_frames_tx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|DM_frames_tx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|FRMR_frames_tx
id|PACKED
suffix:semicolon
DECL|typedef|read_hdlc_stat_t
)brace
id|read_hdlc_stat_t
suffix:semicolon
DECL|struct|read_comms_err_stats
r_typedef
r_struct
id|read_comms_err_stats
(brace
DECL|member|PACKED
r_int
r_char
id|overrun_err_rx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|CRC_err
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|abort_frames_rx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|frames_dropped_buf_full
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|abort_frames_tx
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|transmit_underruns
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|missed_tx_underruns_intr
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|reserved
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|DCD_drop
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|CTS_drop
id|PACKED
suffix:semicolon
DECL|typedef|read_comms_err_stats_t
)brace
id|read_comms_err_stats_t
suffix:semicolon
DECL|struct|trace_data
r_typedef
r_struct
id|trace_data
(brace
DECL|member|PACKED
r_int
r_int
id|length
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|type
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|trace_dropped
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|reserved
(braket
l_int|5
)braket
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_int
id|timestamp
id|PACKED
suffix:semicolon
DECL|member|PACKED
r_int
r_char
id|data
id|PACKED
suffix:semicolon
DECL|typedef|trace_data_t
)brace
id|trace_data_t
suffix:semicolon
DECL|enumerator|UDP_XPIPE_TYPE
r_enum
(brace
id|UDP_XPIPE_TYPE
)brace
suffix:semicolon
DECL|macro|XPIPE_ENABLE_TRACING
mdefine_line|#define XPIPE_ENABLE_TRACING                    0x14
DECL|macro|XPIPE_DISABLE_TRACING
mdefine_line|#define XPIPE_DISABLE_TRACING                   0x14
DECL|macro|XPIPE_GET_TRACE_INFO
mdefine_line|#define XPIPE_GET_TRACE_INFO                    0x16
DECL|macro|XPIPE_FT1_READ_STATUS
mdefine_line|#define XPIPE_FT1_READ_STATUS                   0x74
DECL|macro|XPIPE_DRIVER_STAT_IFSEND
mdefine_line|#define XPIPE_DRIVER_STAT_IFSEND                0x75
DECL|macro|XPIPE_DRIVER_STAT_INTR
mdefine_line|#define XPIPE_DRIVER_STAT_INTR                  0x76
DECL|macro|XPIPE_DRIVER_STAT_GEN
mdefine_line|#define XPIPE_DRIVER_STAT_GEN                   0x77
DECL|macro|XPIPE_FLUSH_DRIVER_STATS
mdefine_line|#define XPIPE_FLUSH_DRIVER_STATS                0x78
DECL|macro|XPIPE_ROUTER_UP_TIME
mdefine_line|#define XPIPE_ROUTER_UP_TIME                    0x79        
DECL|macro|XPIPE_SET_FT1_MODE
mdefine_line|#define XPIPE_SET_FT1_MODE&t;&t;&t;0x81
DECL|macro|XPIPE_FT1_STATUS_CTRL
mdefine_line|#define XPIPE_FT1_STATUS_CTRL&t;&t;&t;0x80
multiline_comment|/* error messages */
DECL|macro|NO_BUFFS_OR_CLOSED_WIN
mdefine_line|#define NO_BUFFS_OR_CLOSED_WIN  0x33
DECL|macro|DATA_LENGTH_TOO_BIG
mdefine_line|#define DATA_LENGTH_TOO_BIG     0x32
DECL|macro|NO_DATA_AVAILABLE
mdefine_line|#define NO_DATA_AVAILABLE       0x33
DECL|macro|Z80_TIMEOUT_ERROR
mdefine_line|#define Z80_TIMEOUT_ERROR       0x0a   
DECL|macro|NO_BUFFS
mdefine_line|#define&t;NO_BUFFS&t;&t;0x08
multiline_comment|/* Trace options */
DECL|macro|TRACE_DEFAULT
mdefine_line|#define TRACE_DEFAULT&t;&t;0x03
DECL|macro|TRACE_SUPERVISOR_FRMS
mdefine_line|#define TRACE_SUPERVISOR_FRMS&t;0x10
DECL|macro|TRACE_ASYNC_FRMS
mdefine_line|#define TRACE_ASYNC_FRMS&t;0x20
DECL|macro|TRACE_ALL_HDLC_FRMS
mdefine_line|#define TRACE_ALL_HDLC_FRMS&t;0x40
DECL|macro|TRACE_DATA_FRMS
mdefine_line|#define TRACE_DATA_FRMS&t;&t;0x08
macro_line|#endif&t;/* _SDLA_X25_H */
eof
