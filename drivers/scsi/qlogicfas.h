macro_line|#ifndef _QLOGICFAS_H
DECL|macro|_QLOGICFAS_H
mdefine_line|#define _QLOGICFAS_H
r_int
id|qlogicfas_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|qlogicfas_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|qlogicfas_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|qlogicfas_queuecommand
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
id|qlogicfas_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|qlogicfas_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|qlogicfas_biosparam
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
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL (0)
macro_line|#endif
macro_line|#ifdef PCMCIA
DECL|macro|__QLINIT
mdefine_line|#define __QLINIT __devinit
macro_line|#else
DECL|macro|__QLINIT
mdefine_line|#define __QLINIT __init
macro_line|#endif
DECL|macro|QLOGICFAS
mdefine_line|#define QLOGICFAS {&t;&t;&bslash;&n;&t;detect:         qlogicfas_detect,&t;&bslash;&n;&t;info:           qlogicfas_info,&t;&t;&bslash;&n;&t;command:        qlogicfas_command, &t;&bslash;&n;&t;queuecommand:   qlogicfas_queuecommand,&t;&bslash;&n;&t;abort:          qlogicfas_abort,&t;&bslash;&n;&t;reset:          qlogicfas_reset,&t;&bslash;&n;&t;bios_param:     qlogicfas_biosparam,&t;&bslash;&n;&t;can_queue:      0,&t;&t;&t;&bslash;&n;&t;this_id:        -1,&t;&t;&t;&bslash;&n;&t;sg_tablesize:   SG_ALL,&t;&t;&t;&bslash;&n;&t;cmd_per_lun:    1,&t;&t;&t;&bslash;&n;&t;use_clustering: DISABLE_CLUSTERING&t;&bslash;&n;}
macro_line|#endif /* _QLOGICFAS_H */
eof
