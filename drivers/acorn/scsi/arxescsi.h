multiline_comment|/*&n; * ARXE SCSI card driver&n; *&n; * Copyright (C) 1997-2000 Russell King&n; *&n; * Changes to support ARXE 16-bit SCSI card by Stefan Hanske&n; */
macro_line|#ifndef ARXE_SCSI_H
DECL|macro|ARXE_SCSI_H
mdefine_line|#define ARXE_SCSI_H
DECL|macro|MANU_ARXE
mdefine_line|#define MANU_ARXE &t;0x0041
DECL|macro|PROD_ARXE_SCSI
mdefine_line|#define PROD_ARXE_SCSI&t;0x00be
r_extern
r_int
id|arxescsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|arxescsi_release
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|arxescsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|arxescsi_proc_info
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *)0)
macro_line|#endif
macro_line|#ifndef CAN_QUEUE
multiline_comment|/*&n; * Default queue size&n; */
DECL|macro|CAN_QUEUE
mdefine_line|#define CAN_QUEUE&t;1
macro_line|#endif
macro_line|#ifndef CMD_PER_LUN
DECL|macro|CMD_PER_LUN
mdefine_line|#define CMD_PER_LUN&t;1
macro_line|#endif
macro_line|#ifndef SCSI_ID
multiline_comment|/*&n; * Default SCSI host ID&n; */
DECL|macro|SCSI_ID
mdefine_line|#define SCSI_ID&t;&t;7
macro_line|#endif
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#include &quot;fas216.h&quot;
DECL|macro|ARXEScsi
mdefine_line|#define ARXEScsi {&t;&t;&t;&t;&t;&bslash;&n;proc_info:&t;&t;&t;arxescsi_proc_info,&t;&bslash;&n;name:&t;&t;&t;&t;&quot;ARXE SCSI card&quot;,&t;&bslash;&n;detect:&t;&t;&t;&t;arxescsi_detect,&t;&bslash;&n;release:&t;&t;&t;arxescsi_release,&t;&bslash;&n;info:&t;&t;&t;&t;arxescsi_info,&t;&t;&bslash;&n;bios_param:&t;&t;&t;scsicam_bios_param,&t;&bslash;&n;can_queue:&t;&t;&t;CAN_QUEUE,&t;&t;&bslash;&n;this_id:&t;&t;&t;SCSI_ID,&t;&t;&bslash;&n;sg_tablesize:&t;&t;&t;SG_ALL,&t;&t;&t;&bslash;&n;cmd_per_lun:&t;&t;&t;CMD_PER_LUN,&t;&t;&bslash;&n;use_clustering:&t;&t;&t;DISABLE_CLUSTERING,&t;&bslash;&n;command:&t;&t;&t;fas216_command,&t;&t;&bslash;&n;queuecommand:&t;&t;&t;fas216_queue_command,&t;&bslash;&n;eh_host_reset_handler:&t;&t;fas216_eh_host_reset,&t;&bslash;&n;eh_bus_reset_handler:&t;&t;fas216_eh_bus_reset,&t;&bslash;&n;eh_device_reset_handler:&t;fas216_eh_device_reset,&t;&bslash;&n;eh_abort_handler:&t;&t;fas216_eh_abort,&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
r_typedef
r_struct
(brace
DECL|member|info
id|FAS216_Info
id|info
suffix:semicolon
multiline_comment|/* other info... */
DECL|member|cstatus
r_int
r_int
id|cstatus
suffix:semicolon
multiline_comment|/* card status register&t;*/
DECL|member|dmaarea
r_int
r_int
id|dmaarea
suffix:semicolon
multiline_comment|/* Pseudo DMA area&t;*/
DECL|typedef|ARXEScsi_Info
)brace
id|ARXEScsi_Info
suffix:semicolon
DECL|macro|CSTATUS_IRQ
mdefine_line|#define CSTATUS_IRQ&t;(1 &lt;&lt; 0)
DECL|macro|CSTATUS_DRQ
mdefine_line|#define CSTATUS_DRQ&t;(1 &lt;&lt; 0)
macro_line|#endif /* HOSTS_C */
macro_line|#endif /* ARXE_SCSI_H */
eof
