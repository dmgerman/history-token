multiline_comment|/*&n; * Cumana Generic NCR5380 driver defines&n; *&n; * Copyright 1995, Russell King&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: ecoscsi.h,v $&n; * Revision 1.1  1998/02/23 02:45:24  davem&n; * Merge to 2.1.88&n; *&n; */
macro_line|#ifndef ECOSCSI_NCR5380_H
DECL|macro|ECOSCSI_NCR5380_H
mdefine_line|#define ECOSCSI_NCR5380_H
DECL|macro|ECOSCSI_PUBLIC_RELEASE
mdefine_line|#define ECOSCSI_PUBLIC_RELEASE 1
macro_line|#ifndef ASM
r_int
id|ecoscsi_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ecoscsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|ecoscsi_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|ecoscsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|ecoscsi_reset
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
id|ecoscsi_queue_command
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
id|ecoscsi_proc_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 2
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 16
macro_line|#endif
DECL|macro|ECOSCSI_NCR5380
mdefine_line|#define ECOSCSI_NCR5380 {&t;&t;&t;&t;&t;&bslash;&n;name:&t;&t;&quot;Serial Port EcoSCSI NCR5380&quot;,&t;&t;&t;&bslash;&n;detect:&t;&t;ecoscsi_detect,&t;&t;&t;&t;&t;&bslash;&n;release:&t;ecoscsi_release,&t;&t;&t;&t;&bslash;&n;info:&t;&t;ecoscsi_info,&t;&t;&t;&t;&t;&bslash;&n;queuecommand:&t;ecoscsi_queue_command,&t;&t;&t;&t;&bslash;&n;abort:&t;&t;ecoscsi_abort, &t;&t;&t;&t;&t;&bslash;&n;reset:&t;&t;ecoscsi_reset,&t;&t;&t;&t;&t;&bslash;&n;can_queue:&t;CAN_QUEUE,&t;&t;/* can queue */&t;&t;&bslash;&n;this_id:&t;7,&t;&t;&t;/* id */&t;&t;&bslash;&n;sg_tablesize:&t;SG_ALL,&t;&t;&t;&t;&t;&t;&bslash;&n;cmd_per_lun:&t;CMD_PER_LUN,&t;&t;/* cmd per lun */&t;&bslash;&n;use_clustering:&t;DISABLE_CLUSTERING&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    int port, ctrl
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;        struct Scsi_Host *_instance
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;        _instance = instance
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) ecoscsi_read(_instance, reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) ecoscsi_write(_instance, reg, value)
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr do_ecoscsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command ecoscsi_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort ecoscsi_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset ecoscsi_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info ecoscsi_proc_info
DECL|macro|BOARD_NORMAL
mdefine_line|#define BOARD_NORMAL&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
macro_line|#endif /* ndef HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* ECOSCSI_NCR5380_H */
eof
