macro_line|#ifndef _I2O_SCSI_H
DECL|macro|_I2O_SCSI_H
mdefine_line|#define _I2O_SCSI_H
macro_line|#if !defined(LINUX_VERSION_CODE)
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
DECL|macro|I2O_SCSI_ID
mdefine_line|#define I2O_SCSI_ID 15
DECL|macro|I2O_SCSI_CAN_QUEUE
mdefine_line|#define I2O_SCSI_CAN_QUEUE 4
DECL|macro|I2O_SCSI_CMD_PER_LUN
mdefine_line|#define I2O_SCSI_CMD_PER_LUN 6
r_static
r_int
id|i2o_scsi_detect
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
id|i2o_scsi_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_static
r_int
id|i2o_scsi_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|i2o_scsi_queuecommand
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
id|i2o_scsi_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|i2o_scsi_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|i2o_scsi_bios_param
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
r_static
r_int
id|i2o_scsi_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|host
)paren
suffix:semicolon
DECL|macro|I2OSCSI
mdefine_line|#define I2OSCSI {                                          &bslash;&n;&t;&t;  next: NULL,&t;&t;&t;&t;    &bslash;&n;                  proc_name:         &quot;i2o_scsi&quot;,   &bslash;&n;                  name:              &quot;I2O SCSI Layer&quot;, &t;    &bslash;&n;                  detect:            i2o_scsi_detect,       &bslash;&n;                  release:&t;     i2o_scsi_release,&t;    &bslash;&n;                  info:              i2o_scsi_info,         &bslash;&n;                  command:           i2o_scsi_command,      &bslash;&n;                  queuecommand:      i2o_scsi_queuecommand, &bslash;&n;                  abort:             i2o_scsi_abort,        &bslash;&n;                  reset:             i2o_scsi_reset,        &bslash;&n;                  bios_param:        i2o_scsi_bios_param,   &bslash;&n;                  can_queue:         I2O_SCSI_CAN_QUEUE,    &bslash;&n;                  this_id:           I2O_SCSI_ID,           &bslash;&n;                  sg_tablesize:      8,                     &bslash;&n;                  cmd_per_lun:       I2O_SCSI_CMD_PER_LUN,  &bslash;&n;                  unchecked_isa_dma: 0,                     &bslash;&n;                  use_clustering:    ENABLE_CLUSTERING     &bslash;&n;                  }
macro_line|#endif
eof
