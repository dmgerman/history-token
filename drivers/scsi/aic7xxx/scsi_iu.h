multiline_comment|/*&n; * This file is in the public domain.&n; */
macro_line|#ifndef&t;_SCSI_SCSI_IU_H
DECL|macro|_SCSI_SCSI_IU_H
mdefine_line|#define _SCSI_SCSI_IU_H 1
DECL|struct|scsi_status_iu_header
r_struct
id|scsi_status_iu_header
(brace
DECL|member|reserved
id|u_int8_t
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|flags
id|u_int8_t
id|flags
suffix:semicolon
DECL|macro|SIU_SNSVALID
mdefine_line|#define&t;SIU_SNSVALID 0x2
DECL|macro|SIU_RSPVALID
mdefine_line|#define&t;SIU_RSPVALID 0x1
DECL|member|status
id|u_int8_t
id|status
suffix:semicolon
DECL|member|sense_length
id|u_int8_t
id|sense_length
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pkt_failures_length
id|u_int8_t
id|pkt_failures_length
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|pkt_failures
id|u_int8_t
id|pkt_failures
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SIU_PKTFAIL_OFFSET
mdefine_line|#define SIU_PKTFAIL_OFFSET(siu) 12
DECL|macro|SIU_PKTFAIL_CODE
mdefine_line|#define SIU_PKTFAIL_CODE(siu) (scsi_4btoul((siu)-&gt;pkt_failures) &amp; 0xFF)
DECL|macro|SIU_PFC_NONE
mdefine_line|#define&t;&t;SIU_PFC_NONE&t;&t;&t;0
DECL|macro|SIU_PFC_CIU_FIELDS_INVALID
mdefine_line|#define&t;&t;SIU_PFC_CIU_FIELDS_INVALID&t;2
DECL|macro|SIU_PFC_TMF_NOT_SUPPORTED
mdefine_line|#define&t;&t;SIU_PFC_TMF_NOT_SUPPORTED&t;4
DECL|macro|SIU_PFC_TMF_FAILED
mdefine_line|#define&t;&t;SIU_PFC_TMF_FAILED&t;&t;5
DECL|macro|SIU_PFC_INVALID_TYPE_CODE
mdefine_line|#define&t;&t;SIU_PFC_INVALID_TYPE_CODE&t;6
DECL|macro|SIU_PFC_ILLEGAL_REQUEST
mdefine_line|#define&t;&t;SIU_PFC_ILLEGAL_REQUEST&t;&t;7
DECL|macro|SIU_SENSE_OFFSET
mdefine_line|#define SIU_SENSE_OFFSET(siu)&t;&t;&t;&t;&bslash;&n;    (12 + (((siu)-&gt;flags &amp; SIU_RSPVALID)&t;&t;&bslash;&n;&t;? scsi_4btoul((siu)-&gt;pkt_failures_length)&t;&bslash;&n;&t;: 0))
DECL|macro|SIU_TASKMGMT_NONE
mdefine_line|#define&t;SIU_TASKMGMT_NONE&t;&t;0x00
DECL|macro|SIU_TASKMGMT_ABORT_TASK
mdefine_line|#define&t;SIU_TASKMGMT_ABORT_TASK&t;&t;0x01
DECL|macro|SIU_TASKMGMT_ABORT_TASK_SET
mdefine_line|#define&t;SIU_TASKMGMT_ABORT_TASK_SET&t;0x02
DECL|macro|SIU_TASKMGMT_CLEAR_TASK_SET
mdefine_line|#define&t;SIU_TASKMGMT_CLEAR_TASK_SET&t;0x04
DECL|macro|SIU_TASKMGMT_LUN_RESET
mdefine_line|#define&t;SIU_TASKMGMT_LUN_RESET&t;&t;0x08
DECL|macro|SIU_TASKMGMT_TARGET_RESET
mdefine_line|#define&t;SIU_TASKMGMT_TARGET_RESET&t;0x20
DECL|macro|SIU_TASKMGMT_CLEAR_ACA
mdefine_line|#define&t;SIU_TASKMGMT_CLEAR_ACA&t;&t;0x40
macro_line|#endif /*_SCSI_SCSI_IU_H*/
eof
