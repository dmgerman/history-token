multiline_comment|/*&n; * QLogic ISP1020 Intelligent SCSI Processor Driver (PCI)&n; * Written by Erik H. Moe, ehm@cris.com&n; * Copyright 1995, Erik H. Moe&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2, or (at your option) any&n; * later version.&n; *&n; * This program is distributed in the hope that it will be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; * General Public License for more details.&n; */
multiline_comment|/* Renamed and updated to 1.3.x by Michael Griffith &lt;grif@cs.ucr.edu&gt; */
multiline_comment|/*&n; * $Date: 1995/09/22 02:32:56 $&n; * $Revision: 0.5 $&n; *&n; * $Log: isp1020.h,v $&n; * Revision 0.5  1995/09/22  02:32:56  root&n; * do auto request sense&n; *&n; * Revision 0.4  1995/08/07  04:48:28  root&n; * supply firmware with driver.&n; * numerous bug fixes/general cleanup of code.&n; *&n; * Revision 0.3  1995/07/16  16:17:16  root&n; * added reset/abort code.&n; *&n; * Revision 0.2  1995/06/29  03:19:43  root&n; * fixed biosparam.&n; * added queue protocol.&n; *&n; * Revision 0.1  1995/06/25  01:56:13  root&n; * Initial release.&n; *&n; */
macro_line|#ifndef _QLOGICISP_H
DECL|macro|_QLOGICISP_H
mdefine_line|#define _QLOGICISP_H
multiline_comment|/*&n; * With the qlogic interface, every queue slot can hold a SCSI&n; * command with up to 4 scatter/gather entries.  If we need more&n; * than 4 entries, continuation entries can be used that hold&n; * another 7 entries each.  Unlike for other drivers, this means&n; * that the maximum number of scatter/gather entries we can&n; * support at any given time is a function of the number of queue&n; * slots available.  That is, host-&gt;can_queue and host-&gt;sg_tablesize&n; * are dynamic and _not_ independent.  This all works fine because&n; * requests are queued serially and the scatter/gather limit is&n; * determined for each queue request anew.&n; */
DECL|macro|QLOGICISP_REQ_QUEUE_LEN
mdefine_line|#define QLOGICISP_REQ_QUEUE_LEN&t;63&t;/* must be power of two - 1 */
DECL|macro|QLOGICISP_MAX_SG
mdefine_line|#define QLOGICISP_MAX_SG(ql)&t;(4 + ((ql) &gt; 0) ? 7*((ql) - 1) : 0)
r_int
id|isp1020_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|isp1020_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|isp1020_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|isp1020_queuecommand
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
id|isp1020_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|isp1020_reset
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
id|isp1020_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL (0)
macro_line|#endif
DECL|macro|QLOGICISP
mdefine_line|#define QLOGICISP {&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;detect:&t;&t;&t;isp1020_detect,&t;&t;&t;&t;   &bslash;&n;&t;release:&t;&t;isp1020_release,&t;&t;&t;   &bslash;&n;&t;info:&t;&t;&t;isp1020_info,&t;&t;&t;&t;   &bslash;&n;&t;queuecommand:&t;&t;isp1020_queuecommand,&t;&t;&t;   &bslash;&n;&t;abort:&t;&t;&t;isp1020_abort,&t;&t;&t;&t;   &bslash;&n;&t;reset:&t;&t;&t;isp1020_reset,&t;&t;&t;&t;   &bslash;&n;&t;bios_param:&t;&t;isp1020_biosparam,&t;&t;&t;   &bslash;&n;&t;can_queue:&t;&t;QLOGICISP_REQ_QUEUE_LEN,&t;&t;   &bslash;&n;&t;this_id:&t;&t;-1,&t;&t;&t;&t;&t;   &bslash;&n;&t;sg_tablesize:&t;&t;QLOGICISP_MAX_SG(QLOGICISP_REQ_QUEUE_LEN), &bslash;&n;&t;cmd_per_lun:&t;&t;1,&t;&t;&t;&t;&t;   &bslash;&n;&t;present:&t;&t;0,&t;&t;&t;&t;&t;   &bslash;&n;&t;unchecked_isa_dma:&t;0,&t;&t;&t;&t;&t;   &bslash;&n;&t;use_clustering:&t;&t;DISABLE_CLUSTERING&t;&t;&t;   &bslash;&n;}
macro_line|#endif /* _QLOGICISP_H */
eof
