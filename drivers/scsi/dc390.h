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
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|block_device
op_star
id|dev
comma
id|sector_t
id|capacity
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
macro_line|#endif /* DC390_H */
eof
