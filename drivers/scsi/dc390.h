multiline_comment|/***********************************************************************&n; *&t;FILE NAME : DC390.H&t;&t;&t;&t;&t;       *&n; *&t;     BY   : C.L. Huang&t;&t;&t;&t;&t;       *&n; *&t;Description: Device Driver for Tekram DC-390(T) PCI SCSI       *&n; *&t;&t;     Bus Master Host Adapter&t;&t;&t;       *&n; ***********************************************************************/
multiline_comment|/* $Id: dc390.h,v 2.43.2.22 2000/12/20 00:39:36 garloff Exp $ */
multiline_comment|/*&n; * DC390/AMD 53C974 driver, header file&n; */
macro_line|#ifndef DC390_H
DECL|macro|DC390_H
mdefine_line|#define DC390_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
macro_line|# define KERNEL_VERSION(a,b,c) (((a) &lt;&lt; 16) + ((b) &lt;&lt; 8) + (c))
macro_line|#endif
DECL|macro|DC390_BANNER
mdefine_line|#define DC390_BANNER &quot;Tekram DC390/AM53C974&quot;
DECL|macro|DC390_VERSION
mdefine_line|#define DC390_VERSION &quot;2.0f 2000-12-20&quot;
multiline_comment|/* We don&squot;t have eh_abort_handler, eh_device_reset_handler, &n; * eh_bus_reset_handler, eh_host_reset_handler yet! &n; * So long: Use old exception handling :-( */
DECL|macro|OLD_EH
mdefine_line|#define OLD_EH
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION (2,1,70) || defined (OLD_EH)
DECL|macro|NEW_EH
macro_line|# define NEW_EH
macro_line|#else
DECL|macro|NEW_EH
macro_line|# define NEW_EH use_new_eh_code: 1,
DECL|macro|USE_NEW_EH
macro_line|# define USE_NEW_EH
macro_line|#endif
macro_line|#if defined(HOSTS_C) || defined(MODULE) || LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,99)
r_extern
r_int
id|DC390_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|psht
)paren
suffix:semicolon
r_extern
r_int
id|DC390_queue_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
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
r_extern
r_int
id|DC390_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_extern
r_int
id|DC390_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
r_int
id|resetFlags
)paren
suffix:semicolon
r_extern
r_int
id|DC390_bios_param
c_func
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|devno
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_static
r_int
id|DC390_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|DC390_release
macro_line|# define DC390_release NULL
macro_line|#endif
r_extern
r_int
id|DC390_proc_info
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
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,30)
DECL|macro|DC390_T
mdefine_line|#define DC390_T    {&t;&t;&t;&t;&t;&bslash;&n;   proc_name:      &quot;tmscsim&quot;,                           &bslash;&n;   proc_info:      DC390_proc_info,&t;&t;&t;&bslash;&n;   name:           DC390_BANNER &quot; V&quot; DC390_VERSION,&t;&bslash;&n;   detect:         DC390_detect,&t;&t;&t;&bslash;&n;   release:        DC390_release,&t;&t;&t;&bslash;&n;   queuecommand:   DC390_queue_command,&t;&t;&t;&bslash;&n;   abort:          DC390_abort,&t;&t;&t;&t;&bslash;&n;   reset:          DC390_reset,&t;&t;&t;&t;&bslash;&n;   bios_param:     DC390_bios_param,&t;&t;&t;&bslash;&n;   can_queue:      42,&t;&t;&t;&t;&t;&bslash;&n;   this_id:        7,&t;&t;&t;&t;&t;&bslash;&n;   sg_tablesize:   SG_ALL,&t;&t;&t;&t;&bslash;&n;   cmd_per_lun:    16,&t;&t;&t;&t;&t;&bslash;&n;   unchecked_isa_dma: 0,&t;&t;&t;&t;&bslash;&n;   use_clustering: DISABLE_CLUSTERING&t;&t;&t;&bslash;&n;   }
macro_line|#else
r_extern
r_struct
id|proc_dir_entry
id|DC390_proc_scsi_tmscsim
suffix:semicolon
DECL|macro|DC390_T
mdefine_line|#define DC390_T    {&t;&t;&t;&t;&t;&bslash;&n;   proc_dir:       &amp;DC390_proc_scsi_tmscsim,&t;&t;&bslash;&n;   proc_info:      DC390_proc_info,&t;&t;&t;&bslash;&n;   name:           DC390_BANNER &quot; V&quot; DC390_VERSION,&t;&bslash;&n;   detect:         DC390_detect,&t;&t;&t;&bslash;&n;   release:        DC390_release,&t;&t;&t;&bslash;&n;   queuecommand:   DC390_queue_command,&t;&t;&t;&bslash;&n;   abort:          DC390_abort,&t;&t;&t;&t;&bslash;&n;   reset:          DC390_reset,&t;&t;&t;&t;&bslash;&n;   bios_param:     DC390_bios_param,&t;&t;&t;&bslash;&n;   can_queue:      42,&t;&t;&t;&t;&t;&bslash;&n;   this_id:        7,&t;&t;&t;&t;&t;&bslash;&n;   sg_tablesize:   SG_ALL,&t;&t;&t;&t;&bslash;&n;   cmd_per_lun:    16,&t;&t;&t;&t;&t;&bslash;&n;   NEW_EH&t;&t;&t;&t;&t;&t;&bslash;&n;   unchecked_isa_dma: 0,&t;&t;&t;&t;&bslash;&n;   use_clustering: DISABLE_CLUSTERING&t;&t;&t;&bslash;&n;   }
macro_line|#endif
macro_line|#endif /* defined(HOSTS_C) || defined(MODULE) */
macro_line|#endif /* DC390_H */
eof
