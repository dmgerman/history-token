multiline_comment|/*&n; * Generic Generic NCR5380 driver defines&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix and Linux consulting and custom programming)&n; *&t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * NCR53C400 extensions (c) 1994,1995,1996, Kevin Lentin&n; *    K.Lentin@cs.monash.edu.au&n; *&n; * ALPHA RELEASE 1. &n; *&n; * For more information, please consult &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; *&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: generic_NCR5380.h,v $&n; */
macro_line|#ifndef GENERIC_NCR5380_H
DECL|macro|GENERIC_NCR5380_H
mdefine_line|#define GENERIC_NCR5380_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|GENERIC_NCR5380_PUBLIC_RELEASE
mdefine_line|#define GENERIC_NCR5380_PUBLIC_RELEASE 1
macro_line|#ifdef NCR53C400
DECL|macro|BIOSPARAM
mdefine_line|#define BIOSPARAM
DECL|macro|NCR5380_BIOSPARAM
mdefine_line|#define NCR5380_BIOSPARAM generic_NCR5380_biosparam
macro_line|#else
DECL|macro|NCR5380_BIOSPARAM
mdefine_line|#define NCR5380_BIOSPARAM NULL
macro_line|#endif
macro_line|#ifndef ASM
r_int
id|generic_NCR5380_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|generic_NCR5380_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|generic_NCR5380_release_resources
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|generic_NCR5380_queue_command
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
id|generic_NCR5380_reset
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
id|notyet_generic_proc_info
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
r_const
r_char
op_star
id|generic_NCR5380_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#ifdef BIOSPARAM
r_int
id|generic_NCR5380_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#endif
r_int
id|generic_NCR5380_proc_info
c_func
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
DECL|macro|GENERIC_NCR5380
mdefine_line|#define GENERIC_NCR5380 {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_info:      generic_NCR5380_proc_info,&t;&t;&t;&bslash;&n;&t;name:           &quot;Generic NCR5380/NCR53C400 Scsi Driver&quot;,&t;&bslash;&n;&t;detect:         generic_NCR5380_detect,&t;&t;&t;&t;&bslash;&n;&t;release:        generic_NCR5380_release_resources,&t;&t;&bslash;&n;&t;info:           (void *)generic_NCR5380_info,&t;&t;&t;&bslash;&n;&t;queuecommand:   generic_NCR5380_queue_command,&t;&t;&t;&bslash;&n;&t;abort:          generic_NCR5380_abort,&t;&t;&t;&t;&bslash;&n;&t;reset:          generic_NCR5380_reset, &t;&t;&t;&t;&bslash;&n;&t;bios_param:     NCR5380_BIOSPARAM,&t;&t;&t;&t;&bslash;&n;&t;can_queue:      CAN_QUEUE,&t;&t;&t;&t;&t;&bslash;&n;        this_id:        7,&t;&t;&t;&t;&t;&t;&bslash;&n;        sg_tablesize:   SG_ALL,&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:    CMD_PER_LUN ,&t;&t;&t;&t;&t;&bslash;&n;        use_clustering: DISABLE_CLUSTERING}
macro_line|#ifndef HOSTS_C
DECL|macro|__STRVAL
mdefine_line|#define __STRVAL(x) #x
DECL|macro|STRVAL
mdefine_line|#define STRVAL(x) __STRVAL(x)
macro_line|#ifdef CONFIG_SCSI_G_NCR5380_PORT
DECL|macro|NCR5380_map_config
mdefine_line|#define NCR5380_map_config port
DECL|macro|NCR5380_map_type
mdefine_line|#define NCR5380_map_type int
DECL|macro|NCR5380_map_name
mdefine_line|#define NCR5380_map_name port
DECL|macro|NCR5380_instance_name
mdefine_line|#define NCR5380_instance_name io_port
DECL|macro|NCR53C400_register_offset
mdefine_line|#define NCR53C400_register_offset 0
DECL|macro|NCR53C400_address_adjust
mdefine_line|#define NCR53C400_address_adjust 8
macro_line|#ifdef NCR53C400
DECL|macro|NCR5380_region_size
mdefine_line|#define NCR5380_region_size 16
macro_line|#else
DECL|macro|NCR5380_region_size
mdefine_line|#define NCR5380_region_size 8
macro_line|#endif
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) (inb(NCR5380_map_name + (reg)))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) (outb((value), (NCR5380_map_name + (reg))))
macro_line|#else 
multiline_comment|/* therefore CONFIG_SCSI_G_NCR5380_MEM */
DECL|macro|NCR5380_map_config
mdefine_line|#define NCR5380_map_config memory
DECL|macro|NCR5380_map_type
mdefine_line|#define NCR5380_map_type unsigned long
DECL|macro|NCR5380_map_name
mdefine_line|#define NCR5380_map_name base
DECL|macro|NCR5380_instance_name
mdefine_line|#define NCR5380_instance_name base
DECL|macro|NCR53C400_register_offset
mdefine_line|#define NCR53C400_register_offset 0x108
DECL|macro|NCR53C400_address_adjust
mdefine_line|#define NCR53C400_address_adjust 0
DECL|macro|NCR53C400_mem_base
mdefine_line|#define NCR53C400_mem_base 0x3880
DECL|macro|NCR53C400_host_buffer
mdefine_line|#define NCR53C400_host_buffer 0x3900
DECL|macro|NCR5380_region_size
mdefine_line|#define NCR5380_region_size 0x3a00
DECL|macro|NCR5380_read
mdefine_line|#define NCR5380_read(reg) isa_readb(NCR5380_map_name + NCR53C400_mem_base + (reg))
DECL|macro|NCR5380_write
mdefine_line|#define NCR5380_write(reg, value) isa_writeb(NCR5380_map_name + NCR53C400_mem_base + (reg), value)
macro_line|#endif
DECL|macro|NCR5380_implementation_fields
mdefine_line|#define NCR5380_implementation_fields &bslash;&n;    NCR5380_map_type NCR5380_map_name
DECL|macro|NCR5380_local_declare
mdefine_line|#define NCR5380_local_declare() &bslash;&n;    register NCR5380_implementation_fields
DECL|macro|NCR5380_setup
mdefine_line|#define NCR5380_setup(instance) &bslash;&n;    NCR5380_map_name = (NCR5380_map_type)((instance)-&gt;NCR5380_instance_name)
DECL|macro|NCR5380_intr
mdefine_line|#define NCR5380_intr generic_NCR5380_intr
DECL|macro|do_NCR5380_intr
mdefine_line|#define do_NCR5380_intr do_generic_NCR5380_intr
DECL|macro|NCR5380_queue_command
mdefine_line|#define NCR5380_queue_command generic_NCR5380_queue_command
DECL|macro|NCR5380_abort
mdefine_line|#define NCR5380_abort generic_NCR5380_abort
DECL|macro|NCR5380_reset
mdefine_line|#define NCR5380_reset generic_NCR5380_reset
DECL|macro|NCR5380_pread
mdefine_line|#define NCR5380_pread generic_NCR5380_pread
DECL|macro|NCR5380_pwrite
mdefine_line|#define NCR5380_pwrite generic_NCR5380_pwrite
DECL|macro|NCR5380_proc_info
mdefine_line|#define NCR5380_proc_info notyet_generic_proc_info
DECL|macro|BOARD_NCR5380
mdefine_line|#define BOARD_NCR5380&t;0
DECL|macro|BOARD_NCR53C400
mdefine_line|#define BOARD_NCR53C400&t;1
DECL|macro|BOARD_NCR53C400A
mdefine_line|#define BOARD_NCR53C400A 2
DECL|macro|BOARD_DTC3181E
mdefine_line|#define BOARD_DTC3181E&t;3
macro_line|#endif /* else def HOSTS_C */
macro_line|#endif /* ndef ASM */
macro_line|#endif /* GENERIC_NCR5380_H */
eof
