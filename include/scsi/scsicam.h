multiline_comment|/*&n; * scsicam.h - SCSI CAM support functions, use for HDIO_GETGEO, etc.&n; *&n; * Copyright 1993, 1994 Drew Eckhardt&n; *      Visionary Computing &n; *      (Unix and Linux consulting and custom programming)&n; *      drew@Colorado.EDU&n; *&t;+1 (303) 786-7975&n; *&n; * For more information, please consult the SCSI-CAM draft.&n; */
macro_line|#ifndef SCSICAM_H
DECL|macro|SCSICAM_H
mdefine_line|#define SCSICAM_H
macro_line|#include &lt;linux/kdev_t.h&gt;
r_extern
r_int
id|scsicam_bios_param
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_int
id|scsi_partsize
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
r_int
id|capacity
comma
r_int
r_int
op_star
id|cyls
comma
r_int
r_int
op_star
id|hds
comma
r_int
r_int
op_star
id|secs
)paren
suffix:semicolon
macro_line|#endif /* def SCSICAM_H */
eof
