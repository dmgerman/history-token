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
r_struct
id|scsi_device
op_star
id|sdev
comma
r_struct
id|block_device
op_star
id|dev
comma
id|sector_t
id|capacity
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
macro_line|#endif
eof
