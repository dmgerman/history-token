multiline_comment|/*&n; * Cumana Generic NCR5380 driver defines&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * ALPHA RELEASE 1.&n; *&n; * For more information, please consult&n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: cumana_NCR5380.h,v $&n; */
macro_line|#ifndef MAC_NCR5380_H
DECL|macro|MAC_NCR5380_H
mdefine_line|#define MAC_NCR5380_H
DECL|macro|MACSCSI_PUBLIC_RELEASE
mdefine_line|#define MACSCSI_PUBLIC_RELEASE 2
macro_line|#ifndef ASM
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
macro_line|#ifndef SG_TABLESIZE
DECL|macro|SG_TABLESIZE
mdefine_line|#define SG_TABLESIZE SG_NONE
macro_line|#endif
macro_line|#ifndef USE_TAGGED_QUEUING
DECL|macro|USE_TAGGED_QUEUING
mdefine_line|#define&t;USE_TAGGED_QUEUING 0
macro_line|#endif
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#ifndef HOSTS_C
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    int port, ctrl
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;        struct Scsi_Host *_instance
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;        _instance = instance
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) macscsi_read(_instance, reg)
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) macscsi_write(_instance, reg, value)
DECL|macro|NCR5380_pread
mdefine_line|#define NCR5380_pread &t;macscsi_pread
DECL|macro|NCR5380_pwrite
mdefine_line|#define NCR5380_pwrite &t;macscsi_pwrite
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr macscsi_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command macscsi_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort macscsi_abort
DECL|macro|NCR5380_bus_reset
mdefine_line|#define NCR5380_bus_reset macscsi_bus_reset
DECL|macro|NCR5380_device_reset
mdefine_line|#define NCR5380_device_reset macscsi_device_reset
DECL|macro|NCR5380_host_reset
mdefine_line|#define NCR5380_host_reset macscsi_host_reset
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info macscsi_proc_info
DECL|macro|BOARD_NORMAL
mdefine_line|#define BOARD_NORMAL&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
macro_line|#endif /* ndef HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* MAC_NCR5380_H */
eof
