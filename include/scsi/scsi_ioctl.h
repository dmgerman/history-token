macro_line|#ifndef _SCSI_IOCTL_H
DECL|macro|_SCSI_IOCTL_H
mdefine_line|#define _SCSI_IOCTL_H 
DECL|macro|SCSI_IOCTL_SEND_COMMAND
mdefine_line|#define SCSI_IOCTL_SEND_COMMAND 1
DECL|macro|SCSI_IOCTL_TEST_UNIT_READY
mdefine_line|#define SCSI_IOCTL_TEST_UNIT_READY 2
DECL|macro|SCSI_IOCTL_BENCHMARK_COMMAND
mdefine_line|#define SCSI_IOCTL_BENCHMARK_COMMAND 3
DECL|macro|SCSI_IOCTL_SYNC
mdefine_line|#define SCSI_IOCTL_SYNC 4&t;&t;&t;/* Request synchronous parameters */
DECL|macro|SCSI_IOCTL_START_UNIT
mdefine_line|#define SCSI_IOCTL_START_UNIT 5
DECL|macro|SCSI_IOCTL_STOP_UNIT
mdefine_line|#define SCSI_IOCTL_STOP_UNIT 6
multiline_comment|/* The door lock/unlock constants are compatible with Sun constants for&n;   the cdrom */
DECL|macro|SCSI_IOCTL_DOORLOCK
mdefine_line|#define SCSI_IOCTL_DOORLOCK 0x5380&t;&t;/* lock the eject mechanism */
DECL|macro|SCSI_IOCTL_DOORUNLOCK
mdefine_line|#define SCSI_IOCTL_DOORUNLOCK 0x5381&t;&t;/* unlock the mechanism&t;  */
DECL|macro|SCSI_REMOVAL_PREVENT
mdefine_line|#define&t;SCSI_REMOVAL_PREVENT&t;1
DECL|macro|SCSI_REMOVAL_ALLOW
mdefine_line|#define&t;SCSI_REMOVAL_ALLOW&t;0
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Structures used for scsi_ioctl et al.&n; */
DECL|struct|scsi_ioctl_command
r_typedef
r_struct
id|scsi_ioctl_command
(brace
DECL|member|inlen
r_int
r_int
id|inlen
suffix:semicolon
DECL|member|outlen
r_int
r_int
id|outlen
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
DECL|typedef|Scsi_Ioctl_Command
)brace
id|Scsi_Ioctl_Command
suffix:semicolon
DECL|struct|scsi_idlun
r_typedef
r_struct
id|scsi_idlun
(brace
DECL|member|dev_id
id|__u32
id|dev_id
suffix:semicolon
DECL|member|host_unique_id
id|__u32
id|host_unique_id
suffix:semicolon
DECL|typedef|Scsi_Idlun
)brace
id|Scsi_Idlun
suffix:semicolon
multiline_comment|/* Fibre Channel WWN, port_id struct */
DECL|struct|scsi_fctargaddress
r_typedef
r_struct
id|scsi_fctargaddress
(brace
DECL|member|host_port_id
id|__u32
id|host_port_id
suffix:semicolon
DECL|member|host_wwn
r_int
r_char
id|host_wwn
(braket
l_int|8
)braket
suffix:semicolon
singleline_comment|// include NULL term.
DECL|typedef|Scsi_FCTargAddress
)brace
id|Scsi_FCTargAddress
suffix:semicolon
r_extern
r_int
id|scsi_ioctl
(paren
id|Scsi_Device
op_star
id|dev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|kernel_scsi_ioctl
(paren
id|Scsi_Device
op_star
id|dev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|scsi_ioctl_send_command
c_func
(paren
id|Scsi_Device
op_star
id|dev
comma
id|Scsi_Ioctl_Command
op_star
id|arg
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
