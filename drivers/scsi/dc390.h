multiline_comment|/***********************************************************************&n; *&t;FILE NAME : DC390.H&t;&t;&t;&t;&t;       *&n; *&t;     BY   : C.L. Huang&t;&t;&t;&t;&t;       *&n; *&t;Description: Device Driver for Tekram DC-390(T) PCI SCSI       *&n; *&t;&t;     Bus Master Host Adapter&t;&t;&t;       *&n; ***********************************************************************/
multiline_comment|/* $Id: dc390.h,v 2.43.2.22 2000/12/20 00:39:36 garloff Exp $ */
multiline_comment|/*&n; * DC390/AMD 53C974 driver, header file&n; */
macro_line|#ifndef DC390_H
DECL|macro|DC390_H
mdefine_line|#define DC390_H
macro_line|#include &lt;linux/version.h&gt;
DECL|macro|DC390_BANNER
mdefine_line|#define DC390_BANNER &quot;Tekram DC390/AM53C974&quot;
DECL|macro|DC390_VERSION
mdefine_line|#define DC390_VERSION &quot;2.1d 2004-05-27&quot;
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
macro_line|#endif /* DC390_H */
eof
