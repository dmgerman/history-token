multiline_comment|/*&n; * Cumana Generic NCR5380 driver defines&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: cumana_1.h,v $&n; * Revision 1.1  1998/02/23 02:45:22  davem&n; * Merge to 2.1.88&n; *&n; */
macro_line|#ifndef CUMANA_NCR5380_H
DECL|macro|CUMANA_NCR5380_H
mdefine_line|#define CUMANA_NCR5380_H
DECL|macro|CUMANASCSI_PUBLIC_RELEASE
mdefine_line|#define CUMANASCSI_PUBLIC_RELEASE 1
macro_line|#ifndef ASM
r_int
id|cumanascsi_abort
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|cumanascsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|cumanascsi_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|cumanascsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|cumanascsi_reset
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
id|cumanascsi_queue_command
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
id|cumanascsi_proc_info
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
macro_line|#include &lt;scsi/scsicam.h&gt;
DECL|macro|CUMANA_NCR5380
mdefine_line|#define CUMANA_NCR5380 {&t;&t;&t;&t;&t;&t;&bslash;&n;name:&t;&t;&t;&quot;Cumana 16-bit SCSI&quot;,&t;&t;&t;&t;&bslash;&n;detect:&t;&t;&t;cumanascsi_detect,&t;&t;&t;&t;&bslash;&n;release:&t;&t;cumanascsi_release,&t;/* Release */&t;&t;&bslash;&n;info:&t;&t;&t;cumanascsi_info,&t;&t;&t;&t;&bslash;&n;queuecommand:&t;&t;cumanascsi_queue_command,&t;&t;&t;&bslash;&n;abort:&t;&t;&t;cumanascsi_abort,&t;&t;&t; &t;&bslash;&n;reset:&t;&t;&t;cumanascsi_reset,&t;&t;&t;&t;&bslash;&n;bios_param:&t;&t;scsicam_bios_param,&t;/* biosparam */&t;&t;&bslash;&n;can_queue:&t;&t;CAN_QUEUE,&t;&t;/* can queue */&t;&t;&bslash;&n;this_id:&t;&t;7,&t;&t;&t;/* id */&t;&t;&bslash;&n;sg_tablesize:&t;&t;SG_ALL,&t;&t;&t;/* sg_tablesize */&t;&bslash;&n;cmd_per_lun:&t;&t;CMD_PER_LUN,&t;&t;/* cmd per lun */&t;&bslash;&n;unchecked_isa_dma:&t;0,&t;&t;&t;/* unchecked_isa_dma */&t;&bslash;&n;use_clustering:&t;&t;DISABLE_CLUSTERING&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    int port, ctrl
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;        struct Scsi_Host *_instance
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;        _instance = instance
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) cumanascsi_read(_instance, reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) cumanascsi_write(_instance, reg, value)
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr do_cumanascsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command cumanascsi_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort cumanascsi_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset cumanascsi_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info cumanascsi_proc_info
DECL|macro|BOARD_NORMAL
mdefine_line|#define BOARD_NORMAL&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
macro_line|#endif /* ndef HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* CUMANA_NCR5380_H */
eof
