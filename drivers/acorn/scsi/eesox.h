multiline_comment|/*&n; *  linux/drivers/acorn/scsi/eesox.h&n; *&n; *  Copyright (C) 1997-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  EESOX SCSI driver&n; */
macro_line|#ifndef EESOXSCSI_H
DECL|macro|EESOXSCSI_H
mdefine_line|#define EESOXSCSI_H
r_extern
r_int
id|eesoxscsi_detect
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eesoxscsi_release
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
id|eesoxscsi_info
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|eesoxscsi_proc_info
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
DECL|macro|EESOXSCSI
mdefine_line|#define EESOXSCSI {&t;&t;&t;&t;&t;&bslash;&n;proc_info:&t;&t;&t;eesoxscsi_proc_info,&t;&bslash;&n;name:&t;&t;&t;&t;&quot;EESOX SCSI&quot;,&t;&t;&bslash;&n;detect:&t;&t;&t;&t;eesoxscsi_detect,&t;&bslash;&n;release:&t;&t;&t;eesoxscsi_release,&t;&bslash;&n;info:&t;&t;&t;&t;eesoxscsi_info,&t;&t;&bslash;&n;bios_param:&t;&t;&t;scsicam_bios_param,&t;&bslash;&n;can_queue:&t;&t;&t;CAN_QUEUE,&t;&t;&bslash;&n;this_id:&t;&t;&t;SCSI_ID,&t;&t;&bslash;&n;sg_tablesize:&t;&t;&t;SG_ALL,&t;&t;&t;&bslash;&n;cmd_per_lun:&t;&t;&t;CAN_QUEUE,&t;&t;&bslash;&n;use_clustering:&t;&t;&t;DISABLE_CLUSTERING,&t;&bslash;&n;command:&t;&t;&t;fas216_command,&t;&t;&bslash;&n;queuecommand:&t;&t;&t;fas216_queue_command,&t;&bslash;&n;eh_host_reset_handler:&t;&t;fas216_eh_host_reset,&t;&bslash;&n;eh_bus_reset_handler:&t;&t;fas216_eh_bus_reset,&t;&bslash;&n;eh_device_reset_handler:&t;fas216_eh_device_reset,&t;&bslash;&n;eh_abort_handler:&t;&t;fas216_eh_abort,&t;&bslash;&n;use_new_eh_code:&t;&t;1&t;&t;&t;&bslash;&n;&t;}
macro_line|#ifndef HOSTS_C
macro_line|#include &lt;asm/dma.h&gt;
DECL|macro|NR_SG
mdefine_line|#define NR_SG&t;256
DECL|struct|control
r_struct
id|control
(brace
DECL|member|io_port
r_int
r_int
id|io_port
suffix:semicolon
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|info
id|FAS216_Info
id|info
suffix:semicolon
DECL|member|control
r_struct
id|control
id|control
suffix:semicolon
DECL|member|dmaarea
r_int
r_int
id|dmaarea
suffix:semicolon
multiline_comment|/* Pseudo DMA area&t;*/
DECL|member|sg
r_struct
id|scatterlist
id|sg
(braket
id|NR_SG
)braket
suffix:semicolon
multiline_comment|/* Scatter DMA list&t;*/
DECL|typedef|EESOXScsi_Info
)brace
id|EESOXScsi_Info
suffix:semicolon
macro_line|#endif /* HOSTS_C */
macro_line|#endif /* EESOXSCSI_H */
eof
