macro_line|#ifndef _SCSI_SCSI_EH_H
DECL|macro|_SCSI_SCSI_EH_H
mdefine_line|#define _SCSI_SCSI_EH_H
r_struct
id|scsi_cmnd
suffix:semicolon
r_struct
id|scsi_device
suffix:semicolon
r_struct
id|scsi_request
suffix:semicolon
r_struct
id|Scsi_Host
suffix:semicolon
multiline_comment|/*&n; * This is a slightly modified SCSI sense &quot;descriptor&quot; format header.&n; * The addition is to allow the 0x70 and 0x71 response codes. The idea&n; * is to place the salient data from either &quot;fixed&quot; or &quot;descriptor&quot; sense&n; * format into one structure to ease application processing.&n; *&n; * The original sense buffer should be kept around for those cases&n; * in which more information is required (e.g. the LBA of a MEDIUM ERROR).&n; */
DECL|struct|scsi_sense_hdr
r_struct
id|scsi_sense_hdr
(brace
multiline_comment|/* See SPC-3 section 4.5 */
DECL|member|response_code
id|u8
id|response_code
suffix:semicolon
multiline_comment|/* permit: 0x0, 0x70, 0x71, 0x72, 0x73 */
DECL|member|sense_key
id|u8
id|sense_key
suffix:semicolon
DECL|member|asc
id|u8
id|asc
suffix:semicolon
DECL|member|ascq
id|u8
id|ascq
suffix:semicolon
DECL|member|byte4
id|u8
id|byte4
suffix:semicolon
DECL|member|byte5
id|u8
id|byte5
suffix:semicolon
DECL|member|byte6
id|u8
id|byte6
suffix:semicolon
DECL|member|additional_length
id|u8
id|additional_length
suffix:semicolon
multiline_comment|/* always 0 for fixed sense format */
)brace
suffix:semicolon
r_extern
r_void
id|scsi_add_timer
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_int
comma
r_void
(paren
op_star
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|scsi_delete_timer
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_extern
r_void
id|scsi_report_bus_reset
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|scsi_report_device_reset
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|scsi_block_when_processing_errors
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|scsi_normalize_sense
c_func
(paren
r_const
id|u8
op_star
id|sense_buffer
comma
r_int
id|sb_len
comma
r_struct
id|scsi_sense_hdr
op_star
id|sshdr
)paren
suffix:semicolon
r_extern
r_int
id|scsi_request_normalize_sense
c_func
(paren
r_struct
id|scsi_request
op_star
id|sreq
comma
r_struct
id|scsi_sense_hdr
op_star
id|sshdr
)paren
suffix:semicolon
r_extern
r_int
id|scsi_command_normalize_sense
c_func
(paren
r_struct
id|scsi_cmnd
op_star
id|cmd
comma
r_struct
id|scsi_sense_hdr
op_star
id|sshdr
)paren
suffix:semicolon
DECL|function|scsi_sense_is_deferred
r_static
r_inline
r_int
id|scsi_sense_is_deferred
c_func
(paren
r_struct
id|scsi_sense_hdr
op_star
id|sshdr
)paren
(brace
r_return
(paren
(paren
id|sshdr-&gt;response_code
op_ge
l_int|0x70
)paren
op_logical_and
(paren
id|sshdr-&gt;response_code
op_amp
l_int|1
)paren
)paren
suffix:semicolon
)brace
r_extern
r_const
id|u8
op_star
id|scsi_sense_desc_find
c_func
(paren
r_const
id|u8
op_star
id|sense_buffer
comma
r_int
id|sb_len
comma
r_int
id|desc_type
)paren
suffix:semicolon
r_extern
r_int
id|scsi_get_sense_info_fld
c_func
(paren
r_const
id|u8
op_star
id|sense_buffer
comma
r_int
id|sb_len
comma
id|u64
op_star
id|info_out
)paren
suffix:semicolon
multiline_comment|/*&n; * Reset request from external source&n; */
DECL|macro|SCSI_TRY_RESET_DEVICE
mdefine_line|#define SCSI_TRY_RESET_DEVICE&t;1
DECL|macro|SCSI_TRY_RESET_BUS
mdefine_line|#define SCSI_TRY_RESET_BUS&t;2
DECL|macro|SCSI_TRY_RESET_HOST
mdefine_line|#define SCSI_TRY_RESET_HOST&t;3
r_extern
r_int
id|scsi_reset_provider
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif /* _SCSI_SCSI_EH_H */
eof
