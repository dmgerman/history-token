multiline_comment|/* $Id: sgiwd93.h,v 1.5 1998/08/25 09:18:50 ralf Exp $&n; * sgiwd93.h: SGI WD93 scsi definitions.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#ifndef _SGIWD93_H
DECL|macro|_SGIWD93_H
mdefine_line|#define _SGIWD93_H
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL        0
macro_line|#endif
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 8
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE   16
macro_line|#endif
r_int
id|sgiwd93_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|sgiwd93_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
r_const
r_char
op_star
id|wd33c93_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|wd33c93_queuecommand
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
id|wd33c93_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|wd33c93_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|SGIWD93_SCSI
mdefine_line|#define SGIWD93_SCSI {proc_name:&t;   &quot;SGIWD93&quot;, &bslash;&n;&t;&t;      name:                &quot;SGI WD93&quot;, &bslash;&n;&t;&t;      detect:              sgiwd93_detect,    &bslash;&n;&t;&t;      release:             sgiwd93_release,   &bslash;&n;&t;&t;      queuecommand:        wd33c93_queuecommand, &bslash;&n;&t;&t;      abort:               wd33c93_abort,   &bslash;&n;&t;&t;      reset:               wd33c93_reset,   &bslash;&n;&t;&t;      can_queue:           CAN_QUEUE,       &bslash;&n;&t;&t;      this_id:             7,               &bslash;&n;&t;&t;      sg_tablesize:        SG_ALL,          &bslash;&n;&t;&t;      cmd_per_lun:&t;   CMD_PER_LUN,     &bslash;&n;&t;&t;      use_clustering:      DISABLE_CLUSTERING }
macro_line|#endif /* !(_SGIWD93_H) */
eof
