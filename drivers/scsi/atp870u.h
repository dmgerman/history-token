macro_line|#ifndef _ATP870U_H
multiline_comment|/* $Id: atp870u.h,v 1.0 1997/05/07 15:09:00 root Exp root $&n;&n; * Header file for the ACARD 870U/W driver for Linux&n; *&n; * $Log: atp870u.h,v $&n; * Revision 1.0  1997/05/07  15:09:00  root&n; * Initial revision&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* I/O Port */
DECL|macro|MAX_CDB
mdefine_line|#define MAX_CDB 12
DECL|macro|MAX_SENSE
mdefine_line|#define MAX_SENSE 14
r_static
r_int
id|atp870u_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_static
r_int
id|atp870u_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|atp870u_queuecommand
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
id|atp870u_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_static
r_int
id|atp870u_biosparam
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
r_int
id|atp870u_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
DECL|macro|qcnt
mdefine_line|#define qcnt&t;&t;32
DECL|macro|ATP870U_SCATTER
mdefine_line|#define ATP870U_SCATTER 128
DECL|macro|ATP870U_CMDLUN
mdefine_line|#define ATP870U_CMDLUN 1
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
r_extern
r_const
r_char
op_star
id|atp870u_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|atp870u_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|ATP870U
mdefine_line|#define ATP870U {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;proc_info: atp870u_proc_info,&t;&t;&t;&t;&bslash;&n;&t;detect: atp870u_detect, &t;&t;&t;&t;&bslash;&n;&t;release: atp870u_release,&t;&t;&t;&t;&bslash;&n;&t;info: atp870u_info,&t;&t;&t;&t;&t;&bslash;&n;&t;command: atp870u_command,&t;&t;&t;&t;&bslash;&n;&t;queuecommand: atp870u_queuecommand,&t;&t;&t;&bslash;&n;&t;eh_abort_handler: atp870u_abort, &t;&t;&t;&bslash;&n;&t;bios_param: atp870u_biosparam,&t;&t;&t;&t;&bslash;&n;&t;can_queue: qcnt,&t; /* max simultaneous cmds      */&bslash;&n;&t;this_id: 7,&t;       /* scsi id of host adapter    */&bslash;&n;&t;sg_tablesize: ATP870U_SCATTER,&t;/* max scatter-gather cmds    */&bslash;&n;&t;cmd_per_lun: ATP870U_CMDLUN,&t;/* cmds per lun (linked cmds) */&bslash;&n;&t;present: 0,&t;&t;/* number of 7xxx&squot;s present   */&bslash;&n;&t;unchecked_isa_dma: 0,&t;/* no memory DMA restrictions */&bslash;&n;&t;use_clustering: ENABLE_CLUSTERING,&t;&t;&t;&bslash;&n;}
macro_line|#endif
eof
