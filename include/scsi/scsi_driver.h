macro_line|#ifndef _SCSI_SCSI_DRIVER_H
DECL|macro|_SCSI_SCSI_DRIVER_H
mdefine_line|#define _SCSI_SCSI_DRIVER_H
macro_line|#include &lt;linux/device.h&gt;
r_struct
id|module
suffix:semicolon
DECL|struct|scsi_driver
r_struct
id|scsi_driver
(brace
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|gendrv
r_struct
id|device_driver
id|gendrv
suffix:semicolon
DECL|member|init_command
r_int
(paren
op_star
id|init_command
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
DECL|member|rescan
r_void
(paren
op_star
id|rescan
)paren
(paren
r_struct
id|device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_scsi_driver
mdefine_line|#define to_scsi_driver(drv) &bslash;&n;&t;container_of((drv), struct scsi_driver, gendrv)
r_extern
r_int
id|scsi_register_driver
c_func
(paren
r_struct
id|device_driver
op_star
)paren
suffix:semicolon
DECL|macro|scsi_unregister_driver
mdefine_line|#define scsi_unregister_driver(drv) &bslash;&n;&t;driver_unregister(drv);
r_extern
r_int
id|scsi_register_interface
c_func
(paren
r_struct
id|class_interface
op_star
)paren
suffix:semicolon
DECL|macro|scsi_unregister_interface
mdefine_line|#define scsi_unregister_interface(intf) &bslash;&n;&t;class_interface_unregister(intf)
macro_line|#endif /* _SCSI_SCSI_DRIVER_H */
eof
