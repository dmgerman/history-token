macro_line|#ifndef MVME147_H
multiline_comment|/* $Id: mvme147.h,v 1.4 1997/01/19 23:07:10 davem Exp $&n; *&n; * Header file for the MVME147 built-in SCSI controller for Linux&n; *&n; * Written and (C) 1993, Hamish Macdonald, see mvme147.c for more info&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
r_int
id|mvme147_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|mvme147_release
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
id|wd33c93_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|wd33c93_queuecommand
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
id|wd33c93_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|wd33c93_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 2
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 16
macro_line|#endif
macro_line|#endif /* MVME147_H */
eof
