multiline_comment|/*&n; * advansys.h - Linux Host Driver for AdvanSys SCSI Adapters&n; * &n; * Copyright (c) 1995-2000 Advanced System Products, Inc.&n; * Copyright (c) 2000-2001 ConnectCom Solutions, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * As of March 8, 2000 Advanced System Products, Inc. (AdvanSys)&n; * changed its name to ConnectCom Solutions, Inc.&n; *&n; * There is an AdvanSys Linux WWW page at:&n; *  http://www.connectcom.net/downloads/software/os/linux.html&n; *  http://www.advansys.com/linux.html&n; *&n; * The latest released version of the AdvanSys driver is available at:&n; *  ftp://ftp.advansys.com/pub/linux/linux.tgz&n; *  ftp://ftp.connectcom.net/pub/linux/linux.tgz&n; *&n; * Please send questions, comments, bug reports to:&n; *  linux@connectcom.net or bfrey@turbolinux.com.cn&n; */
macro_line|#ifndef _ADVANSYS_H
DECL|macro|_ADVANSYS_H
mdefine_line|#define _ADVANSYS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif /* LINUX_VERSION_CODE */
multiline_comment|/* Convert Linux Version, Patch-level, Sub-level to LINUX_VERSION_CODE. */
DECL|macro|ASC_LINUX_VERSION
mdefine_line|#define ASC_LINUX_VERSION(V, P, S)    (((V) * 65536) + ((P) * 256) + (S))
multiline_comment|/* Driver supported only in version 2.2 and version &gt;= 2.4. */
macro_line|#if LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(2,2,0) || &bslash;&n;    (LINUX_VERSION_CODE &gt; ASC_LINUX_VERSION(2,3,0) &amp;&amp; &bslash;&n;     LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(2,4,0))
macro_line|#error &quot;AdvanSys driver supported only in 2.2 and 2.4 or greater kernels.&quot;
macro_line|#endif
DECL|macro|ASC_LINUX_KERNEL22
mdefine_line|#define ASC_LINUX_KERNEL22 (LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(2,4,0))
DECL|macro|ASC_LINUX_KERNEL24
mdefine_line|#define ASC_LINUX_KERNEL24 (LINUX_VERSION_CODE &gt;= ASC_LINUX_VERSION(2,4,0))
multiline_comment|/*&n; * Scsi_Host_Template function prototypes.&n; */
r_int
id|advansys_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|advansys_release
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
id|advansys_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|advansys_queuecommand
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
id|advansys_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|advansys_biosparam
c_func
(paren
r_struct
id|scsi_device
op_star
comma
r_struct
id|block_device
op_star
comma
id|sector_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
r_static
r_int
id|advansys_slave_configure
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
multiline_comment|/* init/main.c setup function */
r_void
id|advansys_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
macro_line|#endif /* _ADVANSYS_H */
eof
