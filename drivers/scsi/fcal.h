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
id|fcal_slave_configure
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
macro_line|#endif /* !(_FCAL_H) */
eof
