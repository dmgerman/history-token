multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2005 Silicon Graphics, Inc.  All Rights Reserved.&n; */
macro_line|#ifndef _LINUX_IOC4_COMMON_H
DECL|macro|_LINUX_IOC4_COMMON_H
mdefine_line|#define _LINUX_IOC4_COMMON_H
multiline_comment|/* prototypes */
r_int
id|ioc4_serial_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ioc4_serial_attach_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|pci_id
)paren
suffix:semicolon
r_int
id|ioc4_ide_attach_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|pci_id
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_IOC4_COMMON_H */
eof
