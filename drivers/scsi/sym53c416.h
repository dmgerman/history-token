multiline_comment|/*&n; *  sym53c416.h&n; * &n; *  Copyright (C) 1998 Lieven Willems (lw_linux@hotmail.com)&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2, or (at your option) any&n; *  later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; */
macro_line|#ifndef _SYM53C416_H
DECL|macro|_SYM53C416_H
mdefine_line|#define _SYM53C416_H
macro_line|#if !defined(LINUX_VERSION_CODE)
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#ifndef LinuxVersionCode
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#endif
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|SYM53C416_SCSI_ID
mdefine_line|#define SYM53C416_SCSI_ID 7
r_static
r_int
id|sym53c416_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_const
r_char
op_star
id|sym53c416_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_static
r_int
id|sym53c416_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_static
r_int
id|sym53c416_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|sym53c416_queuecommand
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
r_static
r_int
id|sym53c416_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|sym53c416_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|sym53c416_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|sym53c416_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|sym53c416_bios_param
c_func
(paren
id|Disk
op_star
comma
r_struct
id|block_device
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_static
r_void
id|sym53c416_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
DECL|macro|SYM53C416
mdefine_line|#define SYM53C416 {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.proc_name =&t;&t;&quot;sym53c416&quot;,&t;&t;&bslash;&n;&t;&t;.name =&t;&t;&t;&quot;Symbios Logic 53c416&quot;,&t;&bslash;&n;&t;&t;.detect =&t;&t;sym53c416_detect,&t;&bslash;&n;&t;&t;.info =&t;&t;&t;sym53c416_info,&t;&t;&bslash;&n;&t;&t;.command =&t;&t;sym53c416_command,&t;&bslash;&n;&t;&t;.queuecommand =&t;&t;sym53c416_queuecommand,&t;&bslash;&n;&t;&t;.eh_abort_handler =&t;sym53c416_abort,&t;&bslash;&n;&t;&t;.eh_host_reset_handler =sym53c416_host_reset,&t;&bslash;&n;&t;&t;.eh_bus_reset_handler = sym53c416_bus_reset,&t;&bslash;&n;&t;&t;.eh_device_reset_handler =sym53c416_device_reset,&bslash;&n;&t;&t;.release = &t;&t;sym53c416_release,&t;&bslash;&n;&t;&t;.bios_param =&t;&t;sym53c416_bios_param,&t;&bslash;&n;&t;&t;.can_queue =&t;&t;1,&t;&t;&t;&bslash;&n;&t;&t;.this_id =&t;&t;SYM53C416_SCSI_ID,&t;&bslash;&n;&t;&t;.sg_tablesize =&t;&t;32,&t;&t;&t;&bslash;&n;&t;&t;.cmd_per_lun =&t;&t;1,&t;&t;&t;&bslash;&n;&t;&t;.unchecked_isa_dma =&t;1,&t;&t;&t;&bslash;&n;&t;&t;.use_clustering =&t;ENABLE_CLUSTERING&t;&bslash;&n;&t;&t;}
macro_line|#endif
eof
