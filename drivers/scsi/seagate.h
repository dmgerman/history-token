multiline_comment|/*&n; *&t;seagate.h Copyright (C) 1992 Drew Eckhardt &n; *&t;low level scsi driver header for ST01/ST02 by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#ifndef _SEAGATE_H
DECL|macro|SEAGATE_H
mdefine_line|#define SEAGATE_H
multiline_comment|/*&n;&t;$Header&n;*/
macro_line|#ifndef ASM
r_int
id|seagate_st0x_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|seagate_st0x_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|seagate_st0x_queue_command
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
r_int
id|seagate_st0x_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|seagate_st0x_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|seagate_st0x_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|SEAGATE_ST0X
mdefine_line|#define SEAGATE_ST0X  {  detect:         seagate_st0x_detect,&t;&t;&bslash;&n;&t;&t;&t; info:           seagate_st0x_info,&t;&t;&bslash;&n;&t;&t;&t; command:        seagate_st0x_command,&t;&t;&bslash;&n;&t;&t;&t; queuecommand:   seagate_st0x_queue_command,&t;&bslash;&n;&t;&t;&t; abort:          seagate_st0x_abort,&t;&t;&bslash;&n;&t;&t;&t; reset:          seagate_st0x_reset,&t;&t;&bslash;&n;&t;&t;&t; can_queue:      1,&t;&t;&t;&t;&bslash;&n;&t;&t;&t; this_id:        7,&t;&t;&t;&t;&bslash;&n;&t;&t;&t; sg_tablesize:   SG_ALL,&t;&t;&t;&bslash;&n;&t;&t;&t; cmd_per_lun:    1,&t;&t;&t;&t;&bslash;&n;&t;&t;&t; use_clustering: DISABLE_CLUSTERING}
macro_line|#endif /* ASM */
macro_line|#endif /* _SEAGATE_H */
eof
