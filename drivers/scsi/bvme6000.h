macro_line|#ifndef BVME6000_SCSI_H
DECL|macro|BVME6000_SCSI_H
mdefine_line|#define BVME6000_SCSI_H
macro_line|#include &lt;linux/types.h&gt;
r_int
id|bvme6000_scsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|NCR53c7x0_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|NCR53c7xx_queue_command
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
id|NCR53c7xx_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|NCR53c7x0_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|NCR53c7xx_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|NCR53c7x0_intr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN 3
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE 24
macro_line|#endif
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#endif /* BVME6000_SCSI_H */
eof
