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
id|Disk
op_star
comma
id|kdev_t
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
singleline_comment|// note: since Tachyon TS supports an extended scatter/gather
singleline_comment|// linked list of infinite length (with linked Ext S/G pages,
singleline_comment|// limited only by available physical memory) we use SG_ALL.
DECL|macro|CPQFCTS
mdefine_line|#define CPQFCTS {                                &bslash;&n; detect:                 cpqfcTS_detect,         &bslash;&n; release:                cpqfcTS_release,        &bslash;&n; info:                   cpqfcTS_info,           &bslash;&n; proc_info:              cpqfcTS_proc_info,      &bslash;&n; ioctl:                  cpqfcTS_ioctl,          &bslash;&n; queuecommand:           cpqfcTS_queuecommand,   &bslash;&n; eh_device_reset_handler:   cpqfcTS_eh_device_reset,   &bslash;&n; eh_abort_handler:       cpqfcTS_eh_abort,       &bslash;&n; reset:                  cpqfcTS_reset,          &bslash;&n; abort:                  cpqfcTS_abort,&t;&t; &bslash;&n; bios_param:             cpqfcTS_biosparam,      &bslash;&n; can_queue:              CPQFCTS_REQ_QUEUE_LEN,  &bslash;&n; this_id:                -1,                     &bslash;&n; sg_tablesize:           SG_ALL,                 &bslash;&n; cmd_per_lun:            CPQFCTS_CMD_PER_LUN,    &bslash;&n; present:                0,                      &bslash;&n; unchecked_isa_dma:      0,                      &bslash;&n; use_clustering:         ENABLE_CLUSTERING,      &bslash;&n;}
macro_line|#endif /* CPQFCTS_H */ 
eof
