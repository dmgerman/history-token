macro_line|#ifndef CPQFCTS_H
DECL|macro|CPQFCTS_H
mdefine_line|#define CPQFCTS_H
macro_line|#include &quot;cpqfcTSstructs.h&quot;
singleline_comment|// These functions are required by the Linux SCSI layers
r_extern
r_int
id|cpqfcTS_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|cpqfcTS_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|Cmnd
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_eh_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_biosparam
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_struct
id|block_device
op_star
comma
id|sector_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
r_extern
r_int
id|cpqfcTS_ioctl
c_func
(paren
id|Scsi_Device
op_star
id|ScsiDev
comma
r_int
id|Cmnd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
macro_line|#endif /* CPQFCTS_H */ 
eof
