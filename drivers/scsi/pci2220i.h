multiline_comment|/****************************************************************************&n; * Perceptive Solutions, Inc. PCI-2220I device driver for Linux.&n; *&n; * pci2220i.h - Linux Host Driver for PCI-2220i EIDE Adapters&n; *&n; * Copyright (c) 1997-1999 Perceptive Solutions, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * Technical updates and product information at:&n; *  http://www.psidisk.com&n; *&n; * Please send questions, comments, bug reports to:&n; *  tech@psidisk.com Technical Support&n; *&n; ****************************************************************************/
macro_line|#ifndef _PCI2220I_H
DECL|macro|_PCI2220I_H
mdefine_line|#define _PCI2220I_H
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif 
DECL|macro|LINUXVERSION
mdefine_line|#define&t;LINUXVERSION(v,p,s)    (((v)&lt;&lt;16) + ((p)&lt;&lt;8) + (s))
singleline_comment|// function prototypes
r_int
id|Pci2220i_Detect
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_int
id|Pci2220i_Command
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Pci2220i_QueueCommand
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
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
id|Pci2220i_Abort
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|Pci2220i_Reset
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_int
id|Pci2220i_Release
(paren
r_struct
id|Scsi_Host
op_star
id|pshost
)paren
suffix:semicolon
r_int
id|Pci2220i_BiosParam
(paren
id|Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
id|geom
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
DECL|macro|PCI2220I
mdefine_line|#define PCI2220I {&t;&t;&t;&t;&t;&bslash;&n;&t;proc_name:&t;&t;&quot;pci2220i&quot;,&t;&t;&bslash;&n;&t;name:&t;&t;&t;&quot;PCI-2220I/PCI-2240I&quot;,&t;&bslash;&n;&t;detect:&t;&t;&t;Pci2220i_Detect,&t;&bslash;&n;&t;release:&t;&t;Pci2220i_Release,&t;&bslash;&n;&t;command:&t;&t;Pci2220i_Command,&t;&bslash;&n;&t;queuecommand:&t;&t;Pci2220i_QueueCommand,&t;&bslash;&n;&t;abort:&t;&t;&t;Pci2220i_Abort,&t;&t;&bslash;&n;&t;reset:&t;&t;&t;Pci2220i_Reset,&t;&t;&bslash;&n;&t;bios_param:&t;&t;Pci2220i_BiosParam,&t;&bslash;&n;&t;can_queue:&t;&t;1,&t;&t;&t;&bslash;&n;&t;this_id:&t;&t;-1,&t;&t;&t;&bslash;&n;&t;sg_tablesize:&t;&t;SG_ALL,&t;&t;&t;&bslash;&n;&t;cmd_per_lun:&t;&t;1,&t;&t;&t;&bslash;&n;&t;present:&t;&t;0,&t;&t;&t;&bslash;&n;&t;unchecked_isa_dma:&t;0,&t;&t;&t;&bslash;&n;&t;use_clustering:&t;&t;DISABLE_CLUSTERING,&t;&bslash;&n;}
macro_line|#endif
eof
