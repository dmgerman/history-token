macro_line|#ifndef _SCSI_DEBUG_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
r_static
r_int
id|scsi_debug_detect
c_func
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_slave_attach
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_static
r_void
id|scsi_debug_slave_detach
c_func
(paren
r_struct
id|scsi_device
op_star
)paren
suffix:semicolon
r_static
r_int
id|scsi_debug_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/* static int scsi_debug_command(struct scsi_cmnd *); */
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
mdefine_line|#define SCSI_DEBUG_CANQUEUE  255 &t;/* needs to be &gt;= 1 */
DECL|macro|SCSI_DEBUG_MAX_CMD_LEN
mdefine_line|#define SCSI_DEBUG_MAX_CMD_LEN 16
DECL|variable|driver_template
r_static
id|Scsi_Host_Template
id|driver_template
op_assign
(brace
dot
id|proc_info
op_assign
id|scsi_debug_proc_info
comma
dot
id|name
op_assign
l_string|&quot;SCSI DEBUG&quot;
comma
dot
id|info
op_assign
id|scsi_debug_info
comma
dot
id|detect
op_assign
id|scsi_debug_detect
comma
dot
id|slave_attach
op_assign
id|scsi_debug_slave_attach
comma
dot
id|slave_detach
op_assign
id|scsi_debug_slave_detach
comma
dot
id|release
op_assign
id|scsi_debug_release
comma
dot
id|ioctl
op_assign
id|scsi_debug_ioctl
comma
dot
id|queuecommand
op_assign
id|scsi_debug_queuecommand
comma
dot
id|eh_abort_handler
op_assign
id|scsi_debug_abort
comma
dot
id|eh_bus_reset_handler
op_assign
id|scsi_debug_bus_reset
comma
dot
id|eh_device_reset_handler
op_assign
id|scsi_debug_device_reset
comma
dot
id|eh_host_reset_handler
op_assign
id|scsi_debug_host_reset
comma
dot
id|bios_param
op_assign
id|scsi_debug_biosparam
comma
dot
id|can_queue
op_assign
id|SCSI_DEBUG_CANQUEUE
comma
dot
id|this_id
op_assign
l_int|7
comma
dot
id|sg_tablesize
op_assign
l_int|64
comma
dot
id|cmd_per_lun
op_assign
l_int|3
comma
dot
id|unchecked_isa_dma
op_assign
l_int|0
comma
dot
id|use_clustering
op_assign
id|ENABLE_CLUSTERING
comma
)brace
suffix:semicolon
multiline_comment|/* the name &squot;driver_template&squot; is used by scsi_module.c */
macro_line|#endif
eof
