multiline_comment|/* fcp.h: Definitions for Fibre Channel Protocol.&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; *&n; */
macro_line|#ifndef __FCP_H
DECL|macro|__FCP_H
mdefine_line|#define __FCP_H
multiline_comment|/* FCP addressing is hierarchical with up to 4 layers, MS first.&n;   Exact meaning of the addresses is up to the vendor */
multiline_comment|/* fcp_cntl field */
DECL|macro|FCP_CNTL_WRITE
mdefine_line|#define FCP_CNTL_WRITE&t;&t;0x00000001&t;/* Initiator write */
DECL|macro|FCP_CNTL_READ
mdefine_line|#define FCP_CNTL_READ&t;&t;0x00000002&t;/* Initiator read */
DECL|macro|FCP_CNTL_ABORT_TSK
mdefine_line|#define FCP_CNTL_ABORT_TSK&t;0x00000200&t;/* Abort task set */
DECL|macro|FCP_CNTL_CLR_TASK
mdefine_line|#define FCP_CNTL_CLR_TASK&t;0x00000400&t;/* Clear task set */
DECL|macro|FCP_CNTL_RESET
mdefine_line|#define FCP_CNTL_RESET&t;&t;0x00002000&t;/* Reset */
DECL|macro|FCP_CNTL_CLR_ACA
mdefine_line|#define FCP_CNTL_CLR_ACA&t;0x00004000&t;/* Clear ACA */
DECL|macro|FCP_CNTL_KILL_TASK
mdefine_line|#define FCP_CNTL_KILL_TASK&t;0x00008000&t;/* Terminate task */
DECL|macro|FCP_CNTL_QTYPE_MASK
mdefine_line|#define FCP_CNTL_QTYPE_MASK&t;0x00070000&t;/* Tagged queueing type */
DECL|macro|FCP_CNTL_QTYPE_SIMPLE
mdefine_line|#define &t;FCP_CNTL_QTYPE_SIMPLE&t;&t;0x00000000
DECL|macro|FCP_CNTL_QTYPE_HEAD_OF_Q
mdefine_line|#define &t;FCP_CNTL_QTYPE_HEAD_OF_Q&t;0x00010000
DECL|macro|FCP_CNTL_QTYPE_ORDERED
mdefine_line|#define&t;&t;FCP_CNTL_QTYPE_ORDERED&t;&t;0x00020000
DECL|macro|FCP_CNTL_QTYPE_ACA_Q_TAG
mdefine_line|#define &t;FCP_CNTL_QTYPE_ACA_Q_TAG&t;0x00040000
DECL|macro|FCP_CNTL_QTYPE_UNTAGGED
mdefine_line|#define &t;FCP_CNTL_QTYPE_UNTAGGED&t;&t;0x00050000
r_typedef
r_struct
(brace
DECL|member|fcp_addr
id|u16
id|fcp_addr
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|fcp_cntl
id|u32
id|fcp_cntl
suffix:semicolon
DECL|member|fcp_cdb
id|u8
id|fcp_cdb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fcp_data_len
id|u32
id|fcp_data_len
suffix:semicolon
DECL|typedef|fcp_cmd
)brace
id|fcp_cmd
suffix:semicolon
multiline_comment|/* fcp_status field */
DECL|macro|FCP_STATUS_MASK
mdefine_line|#define&t;FCP_STATUS_MASK&t;&t;0x000000ff&t;/* scsi status of command */
DECL|macro|FCP_STATUS_RSP_LEN
mdefine_line|#define FCP_STATUS_RSP_LEN&t;0x00000100&t;/* response_len != 0 */
DECL|macro|FCP_STATUS_SENSE_LEN
mdefine_line|#define FCP_STATUS_SENSE_LEN&t;0x00000200&t;/* sense_len != 0 */
DECL|macro|FCP_STATUS_RESID
mdefine_line|#define FCP_STATUS_RESID&t;0x00000400&t;/* resid != 0 */
r_typedef
r_struct
(brace
DECL|member|xxx
id|u32
id|xxx
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|fcp_status
id|u32
id|fcp_status
suffix:semicolon
DECL|member|fcp_resid
id|u32
id|fcp_resid
suffix:semicolon
DECL|member|fcp_sense_len
id|u32
id|fcp_sense_len
suffix:semicolon
DECL|member|fcp_response_len
id|u32
id|fcp_response_len
suffix:semicolon
multiline_comment|/* u8&t;fcp_sense[fcp_sense_len]; */
multiline_comment|/* u8&t;fcp_response[fcp_response_len]; */
DECL|typedef|fcp_rsp
)brace
id|fcp_rsp
suffix:semicolon
multiline_comment|/* fcp errors */
multiline_comment|/* rsp_info_type field */
DECL|macro|FCP_RSP_SCSI_BUS_ERR
mdefine_line|#define FCP_RSP_SCSI_BUS_ERR&t;0x01
DECL|macro|FCP_RSP_SCSI_PORT_ERR
mdefine_line|#define FCP_RSP_SCSI_PORT_ERR&t;0x02
DECL|macro|FCP_RSP_CARD_ERR
mdefine_line|#define FCP_RSP_CARD_ERR&t;0x03
multiline_comment|/* isp_status field */
DECL|macro|FCP_RSP_CMD_COMPLETE
mdefine_line|#define FCP_RSP_CMD_COMPLETE&t;0x0000
DECL|macro|FCP_RSP_CMD_INCOMPLETE
mdefine_line|#define FCP_RSP_CMD_INCOMPLETE&t;0x0001
DECL|macro|FCP_RSP_CMD_DMA_ERR
mdefine_line|#define FCP_RSP_CMD_DMA_ERR&t;0x0002
DECL|macro|FCP_RSP_CMD_TRAN_ERR
mdefine_line|#define FCP_RSP_CMD_TRAN_ERR&t;0x0003
DECL|macro|FCP_RSP_CMD_RESET
mdefine_line|#define FCP_RSP_CMD_RESET&t;0x0004
DECL|macro|FCP_RSP_CMD_ABORTED
mdefine_line|#define FCP_RSP_CMD_ABORTED&t;0x0005
DECL|macro|FCP_RSP_CMD_TIMEOUT
mdefine_line|#define FCP_RSP_CMD_TIMEOUT&t;0x0006
DECL|macro|FCP_RSP_CMD_OVERRUN
mdefine_line|#define FCP_RSP_CMD_OVERRUN&t;0x0007
multiline_comment|/* isp_state_flags field */
DECL|macro|FCP_RSP_ST_GOT_BUS
mdefine_line|#define FCP_RSP_ST_GOT_BUS&t;0x0100
DECL|macro|FCP_RSP_ST_GOT_TARGET
mdefine_line|#define FCP_RSP_ST_GOT_TARGET&t;0x0200
DECL|macro|FCP_RSP_ST_SENT_CMD
mdefine_line|#define FCP_RSP_ST_SENT_CMD&t;0x0400
DECL|macro|FCP_RSP_ST_XFRD_DATA
mdefine_line|#define FCP_RSP_ST_XFRD_DATA&t;0x0800
DECL|macro|FCP_RSP_ST_GOT_STATUS
mdefine_line|#define FCP_RSP_ST_GOT_STATUS&t;0x1000
DECL|macro|FCP_RSP_ST_GOT_SENSE
mdefine_line|#define FCP_RSP_ST_GOT_SENSE&t;0x2000
multiline_comment|/* isp_stat_flags field */
DECL|macro|FCP_RSP_STAT_DISC
mdefine_line|#define FCP_RSP_STAT_DISC&t;0x0001
DECL|macro|FCP_RSP_STAT_SYNC
mdefine_line|#define FCP_RSP_STAT_SYNC&t;0x0002
DECL|macro|FCP_RSP_STAT_PERR
mdefine_line|#define FCP_RSP_STAT_PERR&t;0x0004
DECL|macro|FCP_RSP_STAT_BUS_RESET
mdefine_line|#define FCP_RSP_STAT_BUS_RESET&t;0x0008
DECL|macro|FCP_RSP_STAT_DEV_RESET
mdefine_line|#define FCP_RSP_STAT_DEV_RESET&t;0x0010
DECL|macro|FCP_RSP_STAT_ABORTED
mdefine_line|#define FCP_RSP_STAT_ABORTED&t;0x0020
DECL|macro|FCP_RSP_STAT_TIMEOUT
mdefine_line|#define FCP_RSP_STAT_TIMEOUT&t;0x0040
DECL|macro|FCP_RSP_STAT_NEGOTIATE
mdefine_line|#define FCP_RSP_STAT_NEGOTIATE&t;0x0080
r_typedef
r_struct
(brace
DECL|member|rsp_info_type
id|u8
id|rsp_info_type
suffix:semicolon
DECL|member|xxx
id|u8
id|xxx
suffix:semicolon
DECL|member|isp_status
id|u16
id|isp_status
suffix:semicolon
DECL|member|isp_state_flags
id|u16
id|isp_state_flags
suffix:semicolon
DECL|member|isp_stat_flags
id|u16
id|isp_stat_flags
suffix:semicolon
DECL|typedef|fcp_scsi_err
)brace
id|fcp_scsi_err
suffix:semicolon
macro_line|#endif /* !(__FCP_H) */
eof
