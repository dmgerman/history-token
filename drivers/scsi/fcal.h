multiline_comment|/* fcal.h: Generic Fibre Channel Arbitrated Loop SCSI host adapter driver definitions.&n; *&n; * Copyright (C) 1998,1999 Jakub Jelinek (jj@ultra.linux.cz)&n; */
macro_line|#ifndef _FCAL_H
DECL|macro|_FCAL_H
mdefine_line|#define _FCAL_H
macro_line|#include &quot;../fc4/fcp_impl.h&quot;
DECL|struct|fcal
r_struct
id|fcal
(brace
multiline_comment|/* fc must be first */
DECL|member|fc
id|fc_channel
op_star
id|fc
suffix:semicolon
DECL|member|map
r_int
r_char
id|map
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|nport_wwn
id|fc_wwn
id|nport_wwn
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|node_wwn
id|fc_wwn
id|node_wwn
(braket
l_int|128
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Arbitrary constant. Cannot be too large, as fc4 layer has limitations&n;   for a particular channel */
DECL|macro|FCAL_CAN_QUEUE
mdefine_line|#define FCAL_CAN_QUEUE&t;&t;512
r_int
id|fcal_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|fcal_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|fcal_proc_info
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
DECL|macro|FCAL
mdefine_line|#define FCAL {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;name:&t;&t;&t;&quot;Fibre Channel Arbitrated Loop&quot;,&bslash;&n;&t;detect:&t;&t;&t;fcal_detect,&t;&t;&t;&bslash;&n;&t;release:&t;&t;fcal_release,&t;&t;&t;&bslash;&n;&t;proc_info:&t;&t;fcal_proc_info,&t;&t;&t;&bslash;&n;&t;queuecommand:&t;&t;fcp_scsi_queuecommand,&t;&t;&bslash;&n;&t;can_queue:&t;&t;FCAL_CAN_QUEUE,&t;&t;&t;&bslash;&n;&t;this_id:&t;&t;-1,&t;&t;&t;&t;&bslash;&n;&t;sg_tablesize:&t;&t;1,&t;&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;&t;1,&t;&t;&t;&t;&bslash;&n;&t;use_clustering:&t;&t;ENABLE_CLUSTERING,&t;&t;&bslash;&n;&t;use_new_eh_code:&t;FCP_SCSI_USE_NEW_EH_CODE,&t;&bslash;&n;&t;abort:&t;&t;&t;fcp_old_abort,&t;&t;&t;&bslash;&n;&t;eh_abort_handler:&t;fcp_scsi_abort,&t;&t;&t;&bslash;&n;&t;eh_device_reset_handler:fcp_scsi_dev_reset,&t;&t;&bslash;&n;&t;eh_bus_reset_handler:&t;fcp_scsi_bus_reset,&t;&t;&bslash;&n;&t;eh_host_reset_handler:&t;fcp_scsi_host_reset,&t;&t;&bslash;&n;}&t;
macro_line|#endif /* !(_FCAL_H) */
eof
