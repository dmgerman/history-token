multiline_comment|/* fc.h: Definitions for Fibre Channel Physical and Signaling Interface.&n; *&n; * Copyright (C) 1996-1997,1999 Jakub Jelinek (jj@ultra.linux.cz)&n; *&n; * Sources:&n; *&t;Fibre Channel Physical &amp; Signaling Interface (FC-PH), dpANS, 1994&n; *&t;dpANS Fibre Channel Protocol for SCSI (X3.269-199X), Rev. 012, 1995&n; */
macro_line|#ifndef __FC_H
DECL|macro|__FC_H
mdefine_line|#define __FC_H
multiline_comment|/* World Wide Name */
DECL|macro|NAAID_IEEE
mdefine_line|#define NAAID_IEEE&t;&t;1
DECL|macro|NAAID_IEEE_EXT
mdefine_line|#define NAAID_IEEE_EXT&t;&t;2
DECL|macro|NAAID_LOCAL
mdefine_line|#define NAAID_LOCAL&t;&t;3
DECL|macro|NAAID_IP
mdefine_line|#define NAAID_IP&t;&t;4
DECL|macro|NAAID_IEEE_REG
mdefine_line|#define NAAID_IEEE_REG&t;&t;5
DECL|macro|NAAID_IEEE_REG_EXT
mdefine_line|#define NAAID_IEEE_REG_EXT&t;6
DECL|macro|NAAID_CCITT
mdefine_line|#define NAAID_CCITT&t;&t;12
DECL|macro|NAAID_CCITT_GRP
mdefine_line|#define NAAID_CCITT_GRP&t;&t;14
multiline_comment|/* This is NAAID_IEEE_EXT scheme */
r_typedef
r_struct
(brace
DECL|member|naaid
id|u32
id|naaid
suffix:colon
l_int|4
suffix:semicolon
DECL|member|nportid
id|u32
id|nportid
suffix:colon
l_int|12
suffix:semicolon
DECL|member|hi
id|u32
id|hi
suffix:colon
l_int|16
suffix:semicolon
DECL|member|lo
id|u32
id|lo
suffix:semicolon
DECL|typedef|fc_wwn
)brace
id|fc_wwn
suffix:semicolon
multiline_comment|/* Frame header for FC-PH frames */
multiline_comment|/* r_ctl field */
DECL|macro|R_CTL_DEVICE_DATA
mdefine_line|#define R_CTL_DEVICE_DATA&t;0x00&t;/* FC4 Device_Data frame */
DECL|macro|R_CTL_EXTENDED_SVC
mdefine_line|#define R_CTL_EXTENDED_SVC&t;0x20&t;/* Extended Link_Data frame */
DECL|macro|R_CTL_FC4_SVC
mdefine_line|#define R_CTL_FC4_SVC&t;&t;0x30&t;/* FC4 Link_Data frame */
DECL|macro|R_CTL_VIDEO
mdefine_line|#define R_CTL_VIDEO&t;&t;0x40&t;/* Video_Data frame */
DECL|macro|R_CTL_BASIC_SVC
mdefine_line|#define R_CTL_BASIC_SVC&t;&t;0x80&t;/* Basic Link_Data frame */
DECL|macro|R_CTL_LINK_CTL
mdefine_line|#define R_CTL_LINK_CTL&t;&t;0xc0&t;/* Link_Control frame */
multiline_comment|/* FC4 Device_Data frames */
DECL|macro|R_CTL_UNCATEGORIZED
mdefine_line|#define R_CTL_UNCATEGORIZED&t;0x00
DECL|macro|R_CTL_SOLICITED_DATA
mdefine_line|#define R_CTL_SOLICITED_DATA&t;0x01
DECL|macro|R_CTL_UNSOL_CONTROL
mdefine_line|#define R_CTL_UNSOL_CONTROL&t;0x02
DECL|macro|R_CTL_SOLICITED_CONTROL
mdefine_line|#define R_CTL_SOLICITED_CONTROL&t;0x03
DECL|macro|R_CTL_UNSOL_DATA
mdefine_line|#define R_CTL_UNSOL_DATA&t;0x04
DECL|macro|R_CTL_XFER_RDY
mdefine_line|#define R_CTL_XFER_RDY&t;&t;0x05
DECL|macro|R_CTL_COMMAND
mdefine_line|#define R_CTL_COMMAND&t;&t;0x06
DECL|macro|R_CTL_STATUS
mdefine_line|#define R_CTL_STATUS&t;&t;0x07
multiline_comment|/* Basic Link_Data frames */
DECL|macro|R_CTL_LS_NOP
mdefine_line|#define R_CTL_LS_NOP&t;&t;0x80
DECL|macro|R_CTL_LS_ABTS
mdefine_line|#define R_CTL_LS_ABTS&t;&t;0x81
DECL|macro|R_CTL_LS_RMC
mdefine_line|#define R_CTL_LS_RMC&t;&t;0x82
DECL|macro|R_CTL_LS_BA_ACC
mdefine_line|#define R_CTL_LS_BA_ACC&t;&t;0x84
DECL|macro|R_CTL_LS_BA_RJT
mdefine_line|#define R_CTL_LS_BA_RJT&t;&t;0x85
multiline_comment|/* Extended Link_Data frames */
DECL|macro|R_CTL_ELS_REQ
mdefine_line|#define R_CTL_ELS_REQ&t;&t;0x22
DECL|macro|R_CTL_ELS_RSP
mdefine_line|#define R_CTL_ELS_RSP&t;&t;0x23
multiline_comment|/* Link_Control frames */
DECL|macro|R_CTL_ACK_1
mdefine_line|#define R_CTL_ACK_1&t;&t;0xc0
DECL|macro|R_CTL_ACK_N
mdefine_line|#define R_CTL_ACK_N&t;&t;0xc1
DECL|macro|R_CTL_P_RJT
mdefine_line|#define R_CTL_P_RJT&t;&t;0xc2
DECL|macro|R_CTL_F_RJT
mdefine_line|#define R_CTL_F_RJT&t;&t;0xc3
DECL|macro|R_CTL_P_BSY
mdefine_line|#define R_CTL_P_BSY&t;&t;0xc4
DECL|macro|R_CTL_F_BSY_DF
mdefine_line|#define R_CTL_F_BSY_DF&t;&t;0xc5
DECL|macro|R_CTL_F_BSY_LC
mdefine_line|#define R_CTL_F_BSY_LC&t;&t;0xc6
DECL|macro|R_CTL_LCR
mdefine_line|#define R_CTL_LCR&t;&t;0xc7
multiline_comment|/* type field */
DECL|macro|TYPE_BASIC_LS
mdefine_line|#define TYPE_BASIC_LS&t;&t;0x00
DECL|macro|TYPE_EXTENDED_LS
mdefine_line|#define TYPE_EXTENDED_LS&t;0x01
DECL|macro|TYPE_IS8802
mdefine_line|#define TYPE_IS8802&t;&t;0x04
DECL|macro|TYPE_IS8802_SNAP
mdefine_line|#define TYPE_IS8802_SNAP&t;0x05
DECL|macro|TYPE_SCSI_FCP
mdefine_line|#define TYPE_SCSI_FCP&t;&t;0x08
DECL|macro|TYPE_SCSI_GPP
mdefine_line|#define TYPE_SCSI_GPP&t;&t;0x09
DECL|macro|TYPE_HIPP_FP
mdefine_line|#define TYPE_HIPP_FP&t;&t;0x0a
DECL|macro|TYPE_IPI3_MASTER
mdefine_line|#define TYPE_IPI3_MASTER&t;0x11
DECL|macro|TYPE_IPI3_SLAVE
mdefine_line|#define TYPE_IPI3_SLAVE&t;&t;0x12
DECL|macro|TYPE_IPI3_PEER
mdefine_line|#define TYPE_IPI3_PEER&t;&t;0x13
multiline_comment|/* f_ctl field */
DECL|macro|F_CTL_FILL_BYTES
mdefine_line|#define F_CTL_FILL_BYTES&t;0x000003
DECL|macro|F_CTL_XCHG_REASSEMBLE
mdefine_line|#define F_CTL_XCHG_REASSEMBLE&t;0x000004
DECL|macro|F_CTL_RO_PRESENT
mdefine_line|#define F_CTL_RO_PRESENT&t;0x000008
DECL|macro|F_CTL_ABORT_SEQ
mdefine_line|#define F_CTL_ABORT_SEQ&t;&t;0x000030
DECL|macro|F_CTL_CONTINUE_SEQ
mdefine_line|#define F_CTL_CONTINUE_SEQ&t;0x0000c0
DECL|macro|F_CTL_INVALIDATE_XID
mdefine_line|#define F_CTL_INVALIDATE_XID&t;0x004000
DECL|macro|F_CTL_XID_REASSIGNED
mdefine_line|#define F_CTL_XID_REASSIGNED&t;0x008000
DECL|macro|F_CTL_SEQ_INITIATIVE
mdefine_line|#define F_CTL_SEQ_INITIATIVE&t;0x010000
DECL|macro|F_CTL_CHAINED_SEQ
mdefine_line|#define F_CTL_CHAINED_SEQ&t;0x020000
DECL|macro|F_CTL_END_CONNECT
mdefine_line|#define F_CTL_END_CONNECT&t;0x040000
DECL|macro|F_CTL_END_SEQ
mdefine_line|#define F_CTL_END_SEQ&t;&t;0x080000
DECL|macro|F_CTL_LAST_SEQ
mdefine_line|#define F_CTL_LAST_SEQ&t;&t;0x100000
DECL|macro|F_CTL_FIRST_SEQ
mdefine_line|#define F_CTL_FIRST_SEQ&t;&t;0x200000
DECL|macro|F_CTL_SEQ_CONTEXT
mdefine_line|#define F_CTL_SEQ_CONTEXT&t;0x400000
DECL|macro|F_CTL_XCHG_CONTEXT
mdefine_line|#define F_CTL_XCHG_CONTEXT&t;0x800000
r_typedef
r_struct
(brace
DECL|member|r_ctl
DECL|member|did
id|u32
id|r_ctl
suffix:colon
l_int|8
comma
id|did
suffix:colon
l_int|24
suffix:semicolon
DECL|member|xxx1
DECL|member|sid
id|u32
id|xxx1
suffix:colon
l_int|8
comma
id|sid
suffix:colon
l_int|24
suffix:semicolon
DECL|member|type
DECL|member|f_ctl
id|u32
id|type
suffix:colon
l_int|8
comma
id|f_ctl
suffix:colon
l_int|24
suffix:semicolon
DECL|member|seq_id
DECL|member|df_ctl
DECL|member|seq_cnt
id|u32
id|seq_id
suffix:colon
l_int|8
comma
id|df_ctl
suffix:colon
l_int|8
comma
id|seq_cnt
suffix:colon
l_int|16
suffix:semicolon
DECL|member|ox_id
DECL|member|rx_id
id|u16
id|ox_id
comma
id|rx_id
suffix:semicolon
DECL|member|param
id|u32
id|param
suffix:semicolon
DECL|typedef|fc_hdr
)brace
id|fc_hdr
suffix:semicolon
multiline_comment|/* The following are ugly macros to make setup of this structure faster */
DECL|macro|FILL_FCHDR_RCTL_DID
mdefine_line|#define FILL_FCHDR_RCTL_DID(fch, r_ctl, did) *(u32 *)(fch) = ((r_ctl) &lt;&lt; 24) | (did);
DECL|macro|FILL_FCHDR_SID
mdefine_line|#define FILL_FCHDR_SID(fch, sid) *((u32 *)(fch)+1) = (sid);
DECL|macro|FILL_FCHDR_TYPE_FCTL
mdefine_line|#define FILL_FCHDR_TYPE_FCTL(fch, type, f_ctl) *((u32 *)(fch)+2) = ((type) &lt;&lt; 24) | (f_ctl);
DECL|macro|FILL_FCHDR_SEQ_DF_SEQ
mdefine_line|#define FILL_FCHDR_SEQ_DF_SEQ(fch, seq_id, df_ctl, seq_cnt) *((u32 *)(fch)+3) = ((seq_id) &lt;&lt; 24) | ((df_ctl) &lt;&lt; 16) | (seq_cnt);
DECL|macro|FILL_FCHDR_OXRX
mdefine_line|#define FILL_FCHDR_OXRX(fch, ox_id, rx_id) *((u32 *)(fch)+4) = ((ox_id) &lt;&lt; 16) | (rx_id);
multiline_comment|/* Well known addresses */
DECL|macro|FS_GENERAL_MULTICAST
mdefine_line|#define FS_GENERAL_MULTICAST&t;0xfffff7
DECL|macro|FS_WELL_KNOWN_MULTICAST
mdefine_line|#define FS_WELL_KNOWN_MULTICAST&t;0xfffff8
DECL|macro|FS_HUNT_GROUP
mdefine_line|#define FS_HUNT_GROUP&t;&t;0xfffff9
DECL|macro|FS_MANAGEMENT_SERVER
mdefine_line|#define FS_MANAGEMENT_SERVER&t;0xfffffa
DECL|macro|FS_TIME_SERVER
mdefine_line|#define FS_TIME_SERVER&t;&t;0xfffffb
DECL|macro|FS_NAME_SERVER
mdefine_line|#define FS_NAME_SERVER&t;&t;0xfffffc
DECL|macro|FS_FABRIC_CONTROLLER
mdefine_line|#define FS_FABRIC_CONTROLLER&t;0xfffffd
DECL|macro|FS_FABRIC_F_PORT
mdefine_line|#define FS_FABRIC_F_PORT&t;0xfffffe
DECL|macro|FS_BROADCAST
mdefine_line|#define FS_BROADCAST&t;&t;0xffffff
multiline_comment|/* Reject frames */
multiline_comment|/* The param field should be cast to this structure */
r_typedef
r_struct
(brace
DECL|member|action
id|u8
id|action
suffix:semicolon
DECL|member|reason
id|u8
id|reason
suffix:semicolon
DECL|member|xxx
id|u8
id|xxx
suffix:semicolon
DECL|member|vendor_unique
id|u8
id|vendor_unique
suffix:semicolon
DECL|typedef|rjt_param
)brace
id|rjt_param
suffix:semicolon
multiline_comment|/* Reject action codes */
DECL|macro|RJT_RETRY
mdefine_line|#define RJT_RETRY&t;&t;&t;0x01
DECL|macro|RJT_NONRETRY
mdefine_line|#define RJT_NONRETRY&t;&t;&t;0x02
multiline_comment|/* Reject reason codes */
DECL|macro|RJT_INVALID_DID
mdefine_line|#define RJT_INVALID_DID&t;&t;&t;0x01
DECL|macro|RJT_INVALID_SID
mdefine_line|#define RJT_INVALID_SID&t;&t;&t;0x02
DECL|macro|RJT_NPORT_NOT_AVAIL_TEMP
mdefine_line|#define RJT_NPORT_NOT_AVAIL_TEMP&t;0x03
DECL|macro|RJT_NPORT_NOT_AVAIL_PERM
mdefine_line|#define RJT_NPORT_NOT_AVAIL_PERM&t;0x04
DECL|macro|RJT_CLASS_NOT_SUPPORTED
mdefine_line|#define RJT_CLASS_NOT_SUPPORTED&t;&t;0x05
DECL|macro|RJT_DELIMITER_ERROR
mdefine_line|#define RJT_DELIMITER_ERROR&t;&t;0x06
DECL|macro|RJT_TYPE_NOT_SUPPORTED
mdefine_line|#define RJT_TYPE_NOT_SUPPORTED&t;&t;0x07
DECL|macro|RJT_INVALID_LINK_CONTROL
mdefine_line|#define RJT_INVALID_LINK_CONTROL&t;0x08
DECL|macro|RJT_INVALID_R_CTL
mdefine_line|#define RJT_INVALID_R_CTL&t;&t;0x09
DECL|macro|RJT_INVALID_F_CTL
mdefine_line|#define RJT_INVALID_F_CTL&t;&t;0x0a
DECL|macro|RJT_INVALID_OX_ID
mdefine_line|#define RJT_INVALID_OX_ID&t;&t;0x0b
DECL|macro|RJT_INVALID_RX_ID
mdefine_line|#define RJT_INVALID_RX_ID&t;&t;0x0c
DECL|macro|RJT_INVALID_SEQ_ID
mdefine_line|#define RJT_INVALID_SEQ_ID&t;&t;0x0d
DECL|macro|RJT_INVALID_DF_CTL
mdefine_line|#define RJT_INVALID_DF_CTL&t;&t;0x0e
DECL|macro|RJT_INVALID_SEQ_CNT
mdefine_line|#define RJT_INVALID_SEQ_CNT&t;&t;0x0f
DECL|macro|RJT_INVALID_PARAMETER
mdefine_line|#define RJT_INVALID_PARAMETER&t;&t;0x10
DECL|macro|RJT_EXCHANGE_ERROR
mdefine_line|#define RJT_EXCHANGE_ERROR&t;&t;0x11
DECL|macro|RJT_PROTOCOL_ERROR
mdefine_line|#define RJT_PROTOCOL_ERROR&t;&t;0x12
DECL|macro|RJT_INCORRECT_LENGTH
mdefine_line|#define RJT_INCORRECT_LENGTH&t;&t;0x13
DECL|macro|RJT_UNEXPECTED_ACK
mdefine_line|#define RJT_UNEXPECTED_ACK&t;&t;0x14
DECL|macro|RJT_UNEXPECTED_LINK_RESP
mdefine_line|#define RJT_UNEXPECTED_LINK_RESP&t;0x15
DECL|macro|RJT_LOGIN_REQUIRED
mdefine_line|#define RJT_LOGIN_REQUIRED&t;&t;0x16
DECL|macro|RJT_EXCESSIVE_SEQUENCES
mdefine_line|#define RJT_EXCESSIVE_SEQUENCES&t;&t;0x17
DECL|macro|RJT_CANT_ESTABLISH_EXCHANGE
mdefine_line|#define RJT_CANT_ESTABLISH_EXCHANGE&t;0x18
DECL|macro|RJT_SECURITY_NOT_SUPPORTED
mdefine_line|#define RJT_SECURITY_NOT_SUPPORTED&t;0x19
DECL|macro|RJT_FABRIC_NA
mdefine_line|#define RJT_FABRIC_NA&t;&t;&t;0x1a
DECL|macro|RJT_VENDOR_UNIQUE
mdefine_line|#define RJT_VENDOR_UNIQUE&t;&t;0xff
DECL|macro|SP_F_PORT_LOGIN
mdefine_line|#define SP_F_PORT_LOGIN&t;&t;&t;0x10
multiline_comment|/* Extended SVC commands */
DECL|macro|LS_RJT
mdefine_line|#define LS_RJT&t;&t;&t;0x01000000
DECL|macro|LS_ACC
mdefine_line|#define LS_ACC&t;&t;&t;0x02000000
DECL|macro|LS_PRLI_ACC
mdefine_line|#define LS_PRLI_ACC&t;&t;0x02100014
DECL|macro|LS_PLOGI
mdefine_line|#define LS_PLOGI&t;&t;0x03000000
DECL|macro|LS_FLOGI
mdefine_line|#define LS_FLOGI&t;&t;0x04000000
DECL|macro|LS_LOGO
mdefine_line|#define LS_LOGO&t;&t;&t;0x05000000
DECL|macro|LS_ABTX
mdefine_line|#define LS_ABTX&t;&t;&t;0x06000000
DECL|macro|LS_RCS
mdefine_line|#define LS_RCS&t;&t;&t;0x07000000
DECL|macro|LS_RES
mdefine_line|#define LS_RES&t;&t;&t;0x08000000
DECL|macro|LS_RSS
mdefine_line|#define LS_RSS&t;&t;&t;0x09000000
DECL|macro|LS_RSI
mdefine_line|#define LS_RSI&t;&t;&t;0x0a000000
DECL|macro|LS_ESTS
mdefine_line|#define LS_ESTS&t;&t;&t;0x0b000000
DECL|macro|LS_ESTC
mdefine_line|#define LS_ESTC&t;&t;&t;0x0c000000
DECL|macro|LS_ADVC
mdefine_line|#define LS_ADVC&t;&t;&t;0x0d000000
DECL|macro|LS_RTV
mdefine_line|#define LS_RTV&t;&t;&t;0x0e000000
DECL|macro|LS_RLS
mdefine_line|#define LS_RLS&t;&t;&t;0x0f000000
DECL|macro|LS_ECHO
mdefine_line|#define LS_ECHO&t;&t;&t;0x10000000
DECL|macro|LS_TEST
mdefine_line|#define LS_TEST&t;&t;&t;0x11000000
DECL|macro|LS_RRQ
mdefine_line|#define LS_RRQ&t;&t;&t;0x12000000
DECL|macro|LS_IDENT
mdefine_line|#define LS_IDENT&t;&t;0x20000000
DECL|macro|LS_PRLI
mdefine_line|#define LS_PRLI&t;&t;&t;0x20100014
DECL|macro|LS_DISPLAY
mdefine_line|#define LS_DISPLAY&t;&t;0x21000000
DECL|macro|LS_PRLO
mdefine_line|#define LS_PRLO&t;&t;&t;0x21100014
DECL|macro|LS_PDISC
mdefine_line|#define LS_PDISC&t;&t;0x50000000
DECL|macro|LS_ADISC
mdefine_line|#define LS_ADISC&t;&t;0x52000000
r_typedef
r_struct
(brace
DECL|member|fcph_hi
DECL|member|fcph_lo
id|u8
id|fcph_hi
comma
id|fcph_lo
suffix:semicolon
DECL|member|buf2buf_credit
id|u16
id|buf2buf_credit
suffix:semicolon
DECL|member|common_features
id|u8
id|common_features
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
suffix:semicolon
DECL|member|buf2buf_size
id|u16
id|buf2buf_size
suffix:semicolon
DECL|member|xxx2
id|u8
id|xxx2
suffix:semicolon
DECL|member|total_concurrent
id|u8
id|total_concurrent
suffix:semicolon
DECL|member|off_by_info
id|u16
id|off_by_info
suffix:semicolon
DECL|member|e_d_tov
id|u32
id|e_d_tov
suffix:semicolon
DECL|typedef|common_svc_parm
)brace
id|common_svc_parm
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|serv_opts
id|u16
id|serv_opts
suffix:semicolon
DECL|member|initiator_ctl
id|u16
id|initiator_ctl
suffix:semicolon
DECL|member|rcpt_ctl
id|u16
id|rcpt_ctl
suffix:semicolon
DECL|member|recv_size
id|u16
id|recv_size
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
suffix:semicolon
DECL|member|concurrent_seqs
id|u8
id|concurrent_seqs
suffix:semicolon
DECL|member|end2end_credit
id|u16
id|end2end_credit
suffix:semicolon
DECL|member|open_seqs_per_xchg
id|u16
id|open_seqs_per_xchg
suffix:semicolon
DECL|member|xxx2
id|u16
id|xxx2
suffix:semicolon
DECL|typedef|svc_parm
)brace
id|svc_parm
suffix:semicolon
multiline_comment|/* Login */
r_typedef
r_struct
(brace
DECL|member|code
id|u32
id|code
suffix:semicolon
DECL|member|common
id|common_svc_parm
id|common
suffix:semicolon
DECL|member|nport_wwn
id|fc_wwn
id|nport_wwn
suffix:semicolon
DECL|member|node_wwn
id|fc_wwn
id|node_wwn
suffix:semicolon
DECL|member|class1
id|svc_parm
id|class1
suffix:semicolon
DECL|member|class2
id|svc_parm
id|class2
suffix:semicolon
DECL|member|class3
id|svc_parm
id|class3
suffix:semicolon
DECL|typedef|logi
)brace
id|logi
suffix:semicolon
macro_line|#endif /* !(__FC_H) */
eof
