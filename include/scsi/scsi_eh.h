macro_line|#ifndef _SCSI_SCSI_EH_H
DECL|macro|_SCSI_SCSI_EH_H
mdefine_line|#define _SCSI_SCSI_EH_H
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
r_void
id|scsi_sleep
c_func
(paren
r_int
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
