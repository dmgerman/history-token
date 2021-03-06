macro_line|#ifndef _SCSI_DEBUG_H
macro_line|#include &lt;linux/types.h&gt;
r_static
r_int
id|scsi_debug_slave_alloc
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_slave_configure
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_static
r_void
id|scsi_debug_slave_destroy
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_queuecommand
c_func
(paren
r_struct
id|scsi_cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|scsi_cmnd
op_star
)paren
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_ioctl
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_int
comma
r_void
id|__user
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_biosparam
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
r_static
r_int
id|scsi_debug_abort
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_bus_reset
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_device_reset
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_host_reset
c_func
(paren
r_struct
id|scsi_cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_proc_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
comma
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
DECL|macro|SCSI_DEBUG_CANQUEUE
mdefine_line|#define SCSI_DEBUG_CANQUEUE  255 &t;/* needs to be &gt;= 1 */
DECL|macro|SCSI_DEBUG_MAX_CMD_LEN
mdefine_line|#define SCSI_DEBUG_MAX_CMD_LEN 16
macro_line|#endif
eof
