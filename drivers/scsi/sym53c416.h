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
macro_line|#include &lt;linux/kdev_t.h&gt;
DECL|macro|SYM53C416_SCSI_ID
mdefine_line|#define SYM53C416_SCSI_ID 7
r_extern
r_int
id|sym53c416_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
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
r_extern
r_int
id|sym53c416_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
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
r_extern
r_int
id|sym53c416_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sym53c416_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sym53c416_bios_param
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
r_extern
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
mdefine_line|#define SYM53C416 {                                          &bslash;&n;                  proc_name:         &quot;sym53c416&quot;,   &bslash;&n;                  name:              &quot;Symbios Logic 53c416&quot;, &bslash;&n;                  detect:            sym53c416_detect,       &bslash;&n;                  info:              sym53c416_info,         &bslash;&n;                  command:           sym53c416_command,      &bslash;&n;                  queuecommand:      sym53c416_queuecommand, &bslash;&n;                  abort:             sym53c416_abort,        &bslash;&n;                  reset:             sym53c416_reset,        &bslash;&n;                  bios_param:        sym53c416_bios_param,   &bslash;&n;                  can_queue:         1,                      &bslash;&n;                  this_id:           SYM53C416_SCSI_ID,      &bslash;&n;                  sg_tablesize:      32,                     &bslash;&n;                  cmd_per_lun:       1,                      &bslash;&n;                  unchecked_isa_dma: 1,                      &bslash;&n;                  use_clustering:    ENABLE_CLUSTERING       &bslash;&n;                  }
macro_line|#endif
eof
