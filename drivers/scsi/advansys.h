multiline_comment|/*&n; * advansys.h - Linux Host Driver for AdvanSys SCSI Adapters&n; * &n; * Copyright (c) 1995-2000 Advanced System Products, Inc.&n; * Copyright (c) 2000-2001 ConnectCom Solutions, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * As of March 8, 2000 Advanced System Products, Inc. (AdvanSys)&n; * changed its name to ConnectCom Solutions, Inc.&n; *&n; * There is an AdvanSys Linux WWW page at:&n; *  http://www.connectcom.net/downloads/software/os/linux.html&n; *  http://www.advansys.com/linux.html&n; *&n; * The latest released version of the AdvanSys driver is available at:&n; *  ftp://ftp.advansys.com/pub/linux/linux.tgz&n; *  ftp://ftp.connectcom.net/pub/linux/linux.tgz&n; *&n; * Please send questions, comments, bug reports to:&n; *  linux@connectcom.net or bfrey@turbolinux.com.cn&n; */
macro_line|#ifndef _ADVANSYS_H
DECL|macro|_ADVANSYS_H
mdefine_line|#define _ADVANSYS_H
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
id|Disk
op_star
comma
id|kdev_t
comma
r_int
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#if LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(2,3,28)
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_advansys
suffix:semicolon
macro_line|#endif /* version &lt; v2.3.28 */
r_int
id|advansys_proc_info
c_func
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
macro_line|#else /* !defined(CONFIG_PROC_FS) */
DECL|macro|advansys_proc_info
mdefine_line|#define advansys_proc_info      NULL
macro_line|#endif /* !defined(CONFIG_PROC_FS) */
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
multiline_comment|/*&n; * AdvanSys Host Driver Scsi_Host_Template (struct SHT) from hosts.h.&n; */
macro_line|#if ASC_LINUX_KERNEL24
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;    proc_name:                  &quot;advansys&quot;, &bslash;&n;    proc_info:                  advansys_proc_info, &bslash;&n;    name:                       &quot;advansys&quot;, &bslash;&n;    detect:                     advansys_detect, &bslash;&n;    release:                    advansys_release, &bslash;&n;    info:                       advansys_info, &bslash;&n;    queuecommand:               advansys_queuecommand, &bslash;&n;    use_new_eh_code:&t;&t;1, &bslash;&n;    eh_bus_reset_handler:&t;advansys_reset, &bslash;&n;    bios_param:                 advansys_biosparam, &bslash;&n;    /* &bslash;&n;     * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;     * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;     * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;     */ &bslash;&n;    unchecked_isa_dma:          1, &bslash;&n;    /* &bslash;&n;     * All adapters controlled by this driver are capable of large &bslash;&n;     * scatter-gather lists. According to the mid-level SCSI documentation &bslash;&n;     * this obviates any performance gain provided by setting &bslash;&n;     * &squot;use_clustering&squot;. But empirically while CPU utilization is increased &bslash;&n;     * by enabling clustering, I/O throughput increases as well. &bslash;&n;     */ &bslash;&n;    use_clustering:             ENABLE_CLUSTERING, &bslash;&n;}
macro_line|#elif ASC_LINUX_KERNEL22
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;    proc_info:                  advansys_proc_info, &bslash;&n;    name:                       &quot;advansys&quot;, &bslash;&n;    detect:                     advansys_detect, &bslash;&n;    release:                    advansys_release, &bslash;&n;    info:                       advansys_info, &bslash;&n;    queuecommand:               advansys_queuecommand, &bslash;&n;    use_new_eh_code:&t;&t;1, &bslash;&n;    eh_bus_reset_handler:&t;advansys_reset, &bslash;&n;    bios_param:                 advansys_biosparam, &bslash;&n;    /* &bslash;&n;     * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;     * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;     * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;     */ &bslash;&n;    unchecked_isa_dma:          1, &bslash;&n;    /* &bslash;&n;     * All adapters controlled by this driver are capable of large &bslash;&n;     * scatter-gather lists. According to the mid-level SCSI documentation &bslash;&n;     * this obviates any performance gain provided by setting &bslash;&n;     * &squot;use_clustering&squot;. But empirically while CPU utilization is increased &bslash;&n;     * by enabling clustering, I/O throughput increases as well. &bslash;&n;     */ &bslash;&n;    use_clustering:             ENABLE_CLUSTERING, &bslash;&n;}
macro_line|#endif
macro_line|#endif /* _ADVANSYS_H */
eof
