multiline_comment|/* $Id: advansys.h,v 1.18 1999/11/29 21:47:16 bobf Exp bobf $ */
multiline_comment|/*&n; * advansys.h - Linux Host Driver for AdvanSys SCSI Adapters&n; * &n; * Copyright (c) 1995-1998 Advanced System Products, Inc.&n; * All Rights Reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that redistributions of source&n; * code retain the above copyright notice and this comment without&n; * modification.&n; *&n; * There is an AdvanSys Linux WWW page at:&n; *  http://www.advansys.com/linux.html&n; *&n; * The latest version of the AdvanSys driver is available at:&n; *  ftp://ftp.advansys.com/pub/linux&n; *&n; * Please send questions, comments, bug reports to:&n; *  bobf@advansys.com (Bob Frey)&n; */
macro_line|#ifndef _ADVANSYS_H
DECL|macro|_ADVANSYS_H
mdefine_line|#define _ADVANSYS_H
multiline_comment|/* Convert Linux Version, Patch-level, Sub-level to LINUX_VERSION_CODE. */
DECL|macro|ASC_LINUX_VERSION
mdefine_line|#define ASC_LINUX_VERSION(V, P, S)    (((V) * 65536) + ((P) * 256) + (S))
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif /* LINUX_VERSION_CODE */
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
id|advansys_command
c_func
(paren
id|Scsi_Cmnd
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
id|advansys_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(1,3,89)
r_int
id|advansys_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#else /* version &gt;= v1.3.89 */
r_int
id|advansys_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* version &gt;= v1.3.89 */
macro_line|#if LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(1,3,0)
r_int
id|advansys_biosparam
c_func
(paren
id|Disk
op_star
comma
r_int
comma
r_int
(braket
)braket
)paren
suffix:semicolon
macro_line|#else /* version &gt;= v1.3.0 */
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
macro_line|#endif /* version &gt;= v1.3.0 */
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
macro_line|#if LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(1,3,0)
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;    NULL,                     /* struct SHT *next */ &bslash;&n;    NULL,                     /* int *usage_count */ &bslash;&n;    &quot;advansys&quot;,               /* char *name */ &bslash;&n;    advansys_detect,          /* int (*detect)(struct SHT *) */ &bslash;&n;    advansys_release,         /* int (*release)(struct Scsi_Host *) */ &bslash;&n;    advansys_info,            /* const char *(*info)(struct Scsi_Host *) */ &bslash;&n;    advansys_command,         /* int (*command)(Scsi_Cmnd *) */ &bslash;&n;    advansys_queuecommand, &bslash;&n;            /* int (*queuecommand)(Scsi_Cmnd *, void (*done)(Scsi_Cmnd *)) */ &bslash;&n;    advansys_abort,           /* int (*abort)(Scsi_Cmnd *) */ &bslash;&n;    advansys_reset,           /* int (*reset)(Scsi_Cmnd *) */ &bslash;&n;    NULL,                     /* int (*slave_attach)(int, int) */ &bslash;&n;    advansys_biosparam,       /* int (* bios_param)(Disk *, int, int []) */ &bslash;&n;    /* &bslash;&n;     * The following fields are set per adapter in advansys_detect(). &bslash;&n;     */ &bslash;&n;    0,                        /* int can_queue */ &bslash;&n;    0,                        /* int this_id */ &bslash;&n;    0,                        /* short unsigned int sg_tablesize */ &bslash;&n;    0,                        /* short cmd_per_lun */ &bslash;&n;    0,                        /* unsigned char present */    &bslash;&n;    /* &bslash;&n;     * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;     * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;     * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;     */ &bslash;&n;    1,                        /* unsigned unchecked_isa_dma:1 */ &bslash;&n;    /* &bslash;&n;     * All adapters controlled by this driver are capable of large &bslash;&n;     * scatter-gather lists. According to the mid-level SCSI documentation &bslash;&n;     * this obviates any performance gain provided by setting &bslash;&n;     * &squot;use_clustering&squot;. But empirically while CPU utilization is increased &bslash;&n;     * by enabling clustering, I/O throughput increases as well. &bslash;&n;     */ &bslash;&n;    ENABLE_CLUSTERING,        /* unsigned use_clustering:1 */ &bslash;&n;}
macro_line|#elif LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(2,1,75)
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;    NULL,                    /* struct SHT *next */ &bslash;&n;    NULL, &bslash;&n;        /* version &lt; v2.1.23 long *usage_count */ &bslash;&n;        /* version &gt;= v2.1.23 struct module * */ &bslash;&n;    &amp;proc_scsi_advansys,     /* struct proc_dir_entry *proc_dir */ &bslash;&n;    advansys_proc_info,    &bslash;&n;        /* int (*proc_info)(char *, char **, off_t, int, int, int) */ &bslash;&n;    &quot;advansys&quot;,              /* const char *name */ &bslash;&n;    advansys_detect,         /* int (*detect)(struct SHT *) */ &bslash;&n;    advansys_release,        /* int (*release)(struct Scsi_Host *) */ &bslash;&n;    advansys_info,           /* const char *(*info)(struct Scsi_Host *) */ &bslash;&n;    advansys_command,        /* int (*command)(Scsi_Cmnd *) */ &bslash;&n;    advansys_queuecommand, &bslash;&n;        /* int (*queuecommand)(Scsi_Cmnd *, void (*done)(Scsi_Cmnd *)) */ &bslash;&n;    advansys_abort,          /* int (*abort)(Scsi_Cmnd *) */ &bslash;&n;    advansys_reset, &bslash;&n;        /* version &lt; v1.3.89 int (*reset)(Scsi_Cmnd *) */ &bslash;&n;        /* version &gt;= v1.3.89 int (*reset)(Scsi_Cmnd *, unsigned int) */ &bslash;&n;    NULL,                    /* int (*slave_attach)(int, int) */ &bslash;&n;    advansys_biosparam,      /* int (* bios_param)(Disk *, kdev_t, int []) */ &bslash;&n;    /* &bslash;&n;     * The following fields are set per adapter in advansys_detect(). &bslash;&n;     */ &bslash;&n;    0,                        /* int can_queue */ &bslash;&n;    0,                        /* int this_id */ &bslash;&n;    0,                        /* short unsigned int sg_tablesize */ &bslash;&n;    0,                        /* short cmd_per_lun */ &bslash;&n;    0,                        /* unsigned char present */    &bslash;&n;    /* &bslash;&n;     * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;     * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;     * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;     */ &bslash;&n;    1,                        /* unsigned unchecked_isa_dma:1 */ &bslash;&n;    /* &bslash;&n;     * All adapters controlled by this driver are capable of large &bslash;&n;     * scatter-gather lists. According to the mid-level SCSI documentation &bslash;&n;     * this obviates any performance gain provided by setting &bslash;&n;     * &squot;use_clustering&squot;. But empirically while CPU utilization is increased &bslash;&n;     * by enabling clustering, I/O throughput increases as well. &bslash;&n;     */ &bslash;&n;    ENABLE_CLUSTERING,        /* unsigned use_clustering:1 */ &bslash;&n;}
macro_line|#elif LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(2,3,28)
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;    proc_dir:     &amp;proc_scsi_advansys, &bslash;&n;    proc_info:    advansys_proc_info, &bslash;&n;    name:         &quot;advansys&quot;, &bslash;&n;    detect:       advansys_detect, &bslash;&n;    release:      advansys_release, &bslash;&n;    info:         advansys_info, &bslash;&n;    command:      advansys_command, &bslash;&n;    queuecommand: advansys_queuecommand, &bslash;&n;    abort:        advansys_abort, &bslash;&n;    reset:        advansys_reset, &bslash;&n;    bios_param:   advansys_biosparam, &bslash;&n;    /* &bslash;&n;     * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;     * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;     * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;     */ &bslash;&n;    unchecked_isa_dma: 1, &bslash;&n;    /* &bslash;&n;     * All adapters controlled by this driver are capable of large &bslash;&n;     * scatter-gather lists. According to the mid-level SCSI documentation &bslash;&n;     * this obviates any performance gain provided by setting &bslash;&n;     * &squot;use_clustering&squot;. But empirically while CPU utilization is increased &bslash;&n;     * by enabling clustering, I/O throughput increases as well. &bslash;&n;     */ &bslash;&n;    use_clustering: ENABLE_CLUSTERING, &bslash;&n;}
macro_line|#else /* version &gt;= v2.3.28 */
DECL|macro|ADVANSYS
mdefine_line|#define ADVANSYS { &bslash;&n;    proc_name:    &quot;advansys&quot;, &bslash;&n;    proc_info:    advansys_proc_info, &bslash;&n;    name:         &quot;advansys&quot;, &bslash;&n;    detect:       advansys_detect, &bslash;&n;    release:      advansys_release, &bslash;&n;    info:         advansys_info, &bslash;&n;    command:      advansys_command, &bslash;&n;    queuecommand: advansys_queuecommand, &bslash;&n;    abort:        advansys_abort, &bslash;&n;    reset:        advansys_reset, &bslash;&n;    bios_param:   advansys_biosparam, &bslash;&n;    /* &bslash;&n;     * Because the driver may control an ISA adapter &squot;unchecked_isa_dma&squot; &bslash;&n;     * must be set. The flag will be cleared in advansys_detect for non-ISA &bslash;&n;     * adapters. Refer to the comment in scsi_module.c for more information. &bslash;&n;     */ &bslash;&n;    unchecked_isa_dma: 1, &bslash;&n;    /* &bslash;&n;     * All adapters controlled by this driver are capable of large &bslash;&n;     * scatter-gather lists. According to the mid-level SCSI documentation &bslash;&n;     * this obviates any performance gain provided by setting &bslash;&n;     * &squot;use_clustering&squot;. But empirically while CPU utilization is increased &bslash;&n;     * by enabling clustering, I/O throughput increases as well. &bslash;&n;     */ &bslash;&n;    use_clustering: ENABLE_CLUSTERING, &bslash;&n;}
macro_line|#endif /* version &gt;= v2.3.28 */
macro_line|#endif /* _ADVANSYS_H */
eof
