macro_line|#ifndef _SCSI_DEBUG_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
r_static
r_int
id|scsi_debug_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
multiline_comment|/* static int scsi_debug_command(Scsi_Cmnd *); */
r_static
r_int
id|scsi_debug_queuecommand
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
id|scsi_debug_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_biosparam
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
r_static
r_int
id|scsi_debug_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_proc_info
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
r_static
r_const
r_char
op_star
id|scsi_debug_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
multiline_comment|/*&n; * This driver is written for the lk 2.5 series&n; */
DECL|macro|SCSI_DEBUG_CANQUEUE
mdefine_line|#define SCSI_DEBUG_CANQUEUE  255
DECL|macro|SCSI_DEBUG_MAX_CMD_LEN
mdefine_line|#define SCSI_DEBUG_MAX_CMD_LEN 16
DECL|macro|SCSI_DEBUG_TEMPLATE
mdefine_line|#define SCSI_DEBUG_TEMPLATE &bslash;&n;&t;&t;   {proc_info:         scsi_debug_proc_info,&t;&bslash;&n;&t;&t;    name:              &quot;SCSI DEBUG&quot;,&t;&t;&bslash;&n;&t;&t;    info:              scsi_debug_info,&t;&t;&bslash;&n;&t;&t;    detect:            scsi_debug_detect,&t;&bslash;&n;&t;&t;    release:           scsi_debug_release,&t;&bslash;&n;&t;&t;    ioctl:             scsi_debug_ioctl,&t;&bslash;&n;&t;&t;    queuecommand:      scsi_debug_queuecommand, &bslash;&n;&t;&t;    eh_abort_handler:  scsi_debug_abort,&t;&bslash;&n;&t;&t;    eh_bus_reset_handler: scsi_debug_bus_reset,&t;&bslash;&n;&t;&t;    eh_device_reset_handler: scsi_debug_device_reset,&t;&bslash;&n;&t;&t;    eh_host_reset_handler: scsi_debug_host_reset,&t;&bslash;&n;&t;&t;    bios_param:        scsi_debug_biosparam,&t;&bslash;&n;&t;&t;    can_queue:         SCSI_DEBUG_CANQUEUE,&t;&bslash;&n;&t;&t;    this_id:           7,&t;&t;&t;&bslash;&n;&t;&t;    sg_tablesize:      64,&t;&t;&t;&bslash;&n;&t;&t;    cmd_per_lun:       3,&t;&t;&t;&bslash;&n;&t;&t;    unchecked_isa_dma: 0,&t;&t;&t;&bslash;&n;&t;&t;    use_clustering:    ENABLE_CLUSTERING,&t;&bslash;&n;}
macro_line|#endif
eof
