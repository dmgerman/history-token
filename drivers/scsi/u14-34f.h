multiline_comment|/*&n; *   u14-34f.h - used by the low-level driver for UltraStor 14F/34F&n; */
macro_line|#ifndef _U14_34F_H
DECL|macro|_U14_34F_H
mdefine_line|#define _U14_34F_H
macro_line|#include &lt;scsi/scsicam.h&gt;
r_int
id|u14_34f_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|u14_34f_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|u14_34f_queuecommand
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
id|u14_34f_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|u14_34f_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|u14_34f_biosparam
c_func
(paren
id|Disk
op_star
comma
r_struct
id|block_device
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|U14_34F_VERSION
mdefine_line|#define U14_34F_VERSION &quot;7.22.00&quot;
DECL|macro|ULTRASTOR_14_34F
mdefine_line|#define ULTRASTOR_14_34F {                                                   &bslash;&n;                name:         &quot;UltraStor 14F/34F rev. &quot; U14_34F_VERSION &quot; &quot;, &bslash;&n;                detect:                  u14_34f_detect,                     &bslash;&n;                release:                 u14_34f_release,                    &bslash;&n;                queuecommand:            u14_34f_queuecommand,               &bslash;&n;                abort:                   NULL,                               &bslash;&n;                reset:                   NULL,                               &bslash;&n;                eh_abort_handler:        u14_34f_abort,                      &bslash;&n;                eh_device_reset_handler: NULL,                               &bslash;&n;                eh_bus_reset_handler:    NULL,                               &bslash;&n;                eh_host_reset_handler:   u14_34f_reset,                      &bslash;&n;                bios_param:              u14_34f_biosparam,                  &bslash;&n;                this_id:                 7,                                  &bslash;&n;                unchecked_isa_dma:       1,                                  &bslash;&n;                use_clustering:          ENABLE_CLUSTERING,                  &bslash;&n;                }
macro_line|#endif
eof
