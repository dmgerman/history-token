macro_line|#ifndef _QLOGICFAS_H
DECL|macro|_QLOGICFAS_H
mdefine_line|#define _QLOGICFAS_H
r_static
r_int
id|qlogicfas_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
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
r_static
r_int
id|qlogicfas_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
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
r_static
r_int
id|qlogicfas_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|qlogicfas_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|qlogicfas_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|qlogicfas_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|qlogicfas_biosparam
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
DECL|macro|QLOGICFAS
mdefine_line|#define QLOGICFAS {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;detect:         &t;&t;qlogicfas_detect,&t;&bslash;&n;&t;info:           &t;&t;qlogicfas_info,&t;&t;&bslash;&n;&t;command:     &t;&t;&t;qlogicfas_command, &t;&bslash;&n;&t;queuecommand:&t;&t;&t;qlogicfas_queuecommand,&t;&bslash;&n;&t;eh_abort_handler:          &t;qlogicfas_abort,&t;&bslash;&n;&t;eh_bus_reset_handler:&t;&t;qlogicfas_bus_reset,&t;&bslash;&n;&t;eh_device_reset_handler:        qlogicfas_device_reset,&t;&bslash;&n;&t;eh_host_reset_handler:          qlogicfas_host_reset,&t;&bslash;&n;&t;bios_param:     qlogicfas_biosparam,&t;&t;&t;&bslash;&n;&t;can_queue:      0,&t;&t;&t;&t;&t;&bslash;&n;&t;this_id:        -1,&t;&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:   SG_ALL,&t;&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:    1,&t;&t;&t;&t;&t;&bslash;&n;&t;use_clustering: DISABLE_CLUSTERING&t;&t;&t;&bslash;&n;}
macro_line|#endif /* _QLOGICFAS_H */
eof
