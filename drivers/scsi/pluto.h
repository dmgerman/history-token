multiline_comment|/* pluto.h: SparcSTORAGE Array SCSI host adapter driver definitions.&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef _PLUTO_H
DECL|macro|_PLUTO_H
mdefine_line|#define _PLUTO_H
macro_line|#include &quot;../fc4/fcp_impl.h&quot;
DECL|struct|pluto
r_struct
id|pluto
(brace
multiline_comment|/* This must be first */
DECL|member|fc
id|fc_channel
op_star
id|fc
suffix:semicolon
DECL|member|rev_str
r_char
id|rev_str
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|fw_rev_str
r_char
id|fw_rev_str
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|serial_str
r_char
id|serial_str
(braket
l_int|13
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pluto_inquiry
r_struct
id|pluto_inquiry
(brace
DECL|member|dtype
id|u8
id|dtype
suffix:semicolon
DECL|member|removable
DECL|member|qualifier
id|u8
id|removable
suffix:colon
l_int|1
comma
id|qualifier
suffix:colon
l_int|7
suffix:semicolon
DECL|member|iso
DECL|member|ecma
DECL|member|ansi
id|u8
id|iso
suffix:colon
l_int|2
comma
id|ecma
suffix:colon
l_int|3
comma
id|ansi
suffix:colon
l_int|3
suffix:semicolon
DECL|member|aenc
DECL|member|trmiop
DECL|member|rdf
id|u8
id|aenc
suffix:colon
l_int|1
comma
id|trmiop
suffix:colon
l_int|1
comma
suffix:colon
l_int|2
comma
id|rdf
suffix:colon
l_int|4
suffix:semicolon
DECL|member|len
id|u8
id|len
suffix:semicolon
DECL|member|xxx1
id|u8
id|xxx1
suffix:semicolon
DECL|member|xxx2
id|u8
id|xxx2
suffix:semicolon
DECL|member|reladdr
DECL|member|wbus32
DECL|member|wbus16
DECL|member|sync
DECL|member|linked
DECL|member|cmdque
DECL|member|softreset
id|u8
id|reladdr
suffix:colon
l_int|1
comma
id|wbus32
suffix:colon
l_int|1
comma
id|wbus16
suffix:colon
l_int|1
comma
id|sync
suffix:colon
l_int|1
comma
id|linked
suffix:colon
l_int|1
comma
suffix:colon
l_int|1
comma
id|cmdque
suffix:colon
l_int|1
comma
id|softreset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|vendor_id
id|u8
id|vendor_id
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|product_id
id|u8
id|product_id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|revision
id|u8
id|revision
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|fw_revision
id|u8
id|fw_revision
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|serial
id|u8
id|serial
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|xxx3
id|u8
id|xxx3
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|channels
id|u8
id|channels
suffix:semicolon
DECL|member|targets
id|u8
id|targets
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* This is the max number of outstanding SCSI commands per pluto */
DECL|macro|PLUTO_CAN_QUEUE
mdefine_line|#define PLUTO_CAN_QUEUE&t;&t;254
r_int
id|pluto_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|pluto_release
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
id|pluto_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|pluto_slave_configure
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
DECL|macro|PLUTO
mdefine_line|#define PLUTO {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;.name&t;&t;&t;= &quot;Sparc Storage Array 100/200&quot;,&t;&bslash;&n;&t;.detect&t;&t;&t;= pluto_detect,&t;&t;&t;&bslash;&n;&t;.release&t;&t;= pluto_release,&t;&t;&t;&bslash;&n;&t;.info&t;&t;&t;= pluto_info,&t;&t;&t;&bslash;&n;&t;.queuecommand&t;&t;= fcp_scsi_queuecommand,&t;&t;&bslash;&n;&t;.slave_configure&t;= pluto_slave_configure,&t;&t;&bslash;&n;&t;.can_queue&t;&t;= PLUTO_CAN_QUEUE,&t;&t;&bslash;&n;&t;.this_id&t;&t;= -1,&t;&t;&t;&t;&bslash;&n;&t;.sg_tablesize&t;&t;= 1,&t;&t;&t;&t;&bslash;&n;&t;.cmd_per_lun&t;&t;= 1,&t;&t;&t;&t;&bslash;&n;&t;.use_clustering&t;&t;= ENABLE_CLUSTERING,&t;&t;&bslash;&n;&t;.eh_abort_handler&t;= fcp_scsi_abort,&t;&t;&t;&bslash;&n;&t;.eh_device_reset_handler = fcp_scsi_dev_reset,&t;&t;&bslash;&n;&t;.eh_bus_reset_handler&t;= fcp_scsi_bus_reset,&t;&t;&bslash;&n;&t;.eh_host_reset_handler&t;= fcp_scsi_host_reset,&t;&t;&bslash;&n;}&t;
macro_line|#endif /* !(_PLUTO_H) */
eof
