macro_line|#ifndef _GDTH_IOCTL_H
DECL|macro|_GDTH_IOCTL_H
mdefine_line|#define _GDTH_IOCTL_H
multiline_comment|/* gdth_ioctl.h&n; * $Id: gdth_ioctl.h,v 1.9 2001/01/10 14:39:37 achim Exp $&n; */
multiline_comment|/* IOCTLs */
DECL|macro|GDTIOCTL_MASK
mdefine_line|#define GDTIOCTL_MASK       (&squot;J&squot;&lt;&lt;8)
DECL|macro|GDTIOCTL_GENERAL
mdefine_line|#define GDTIOCTL_GENERAL    (GDTIOCTL_MASK | 0) /* general IOCTL */
DECL|macro|GDTIOCTL_DRVERS
mdefine_line|#define GDTIOCTL_DRVERS     (GDTIOCTL_MASK | 1) /* get driver version */
DECL|macro|GDTIOCTL_CTRTYPE
mdefine_line|#define GDTIOCTL_CTRTYPE    (GDTIOCTL_MASK | 2) /* get controller type */
DECL|macro|GDTIOCTL_OSVERS
mdefine_line|#define GDTIOCTL_OSVERS     (GDTIOCTL_MASK | 3) /* get OS version */
DECL|macro|GDTIOCTL_HDRLIST
mdefine_line|#define GDTIOCTL_HDRLIST    (GDTIOCTL_MASK | 4) /* get host drive list */
DECL|macro|GDTIOCTL_CTRCNT
mdefine_line|#define GDTIOCTL_CTRCNT     (GDTIOCTL_MASK | 5) /* get controller count */
DECL|macro|GDTIOCTL_LOCKDRV
mdefine_line|#define GDTIOCTL_LOCKDRV    (GDTIOCTL_MASK | 6) /* lock host drive */
DECL|macro|GDTIOCTL_LOCKCHN
mdefine_line|#define GDTIOCTL_LOCKCHN    (GDTIOCTL_MASK | 7) /* lock channel */
DECL|macro|GDTIOCTL_EVENT
mdefine_line|#define GDTIOCTL_EVENT      (GDTIOCTL_MASK | 8) /* read controller events */
DECL|macro|GDTIOCTL_SCSI
mdefine_line|#define GDTIOCTL_SCSI       (GDTIOCTL_MASK | 9) /* SCSI command */
DECL|macro|GDTIOCTL_RESET_BUS
mdefine_line|#define GDTIOCTL_RESET_BUS  (GDTIOCTL_MASK |10) /* reset SCSI bus */
DECL|macro|GDTIOCTL_RESCAN
mdefine_line|#define GDTIOCTL_RESCAN     (GDTIOCTL_MASK |11) /* rescan host drives */
DECL|macro|GDTIOCTL_RESET_DRV
mdefine_line|#define GDTIOCTL_RESET_DRV  (GDTIOCTL_MASK |12) /* reset (remote) drv. res. */
DECL|macro|GDTIOCTL_MAGIC
mdefine_line|#define GDTIOCTL_MAGIC      0xaffe0004
DECL|macro|EVENT_SIZE
mdefine_line|#define EVENT_SIZE          294 
DECL|macro|MAX_HDRIVES
mdefine_line|#define MAX_HDRIVES         100                     
multiline_comment|/* IOCTL structure (write) */
r_typedef
r_struct
(brace
DECL|member|magic
id|ulong32
id|magic
suffix:semicolon
multiline_comment|/* IOCTL magic */
DECL|member|ioctl
id|ushort
id|ioctl
suffix:semicolon
multiline_comment|/* IOCTL */
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
multiline_comment|/* controller number */
DECL|member|service
id|ushort
id|service
suffix:semicolon
multiline_comment|/* controller service */
DECL|member|timeout
id|ushort
id|timeout
suffix:semicolon
multiline_comment|/* timeout */
r_union
(brace
r_struct
(brace
DECL|member|command
id|unchar
id|command
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* controller command */
DECL|member|data
id|unchar
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* add. data */
DECL|member|general
)brace
id|general
suffix:semicolon
r_struct
(brace
DECL|member|lock
id|unchar
id|lock
suffix:semicolon
multiline_comment|/* lock/unlock */
DECL|member|drive_cnt
id|unchar
id|drive_cnt
suffix:semicolon
multiline_comment|/* drive count */
DECL|member|drives
id|ushort
id|drives
(braket
id|MAX_HDRIVES
)braket
suffix:semicolon
multiline_comment|/* drives */
DECL|member|lockdrv
)brace
id|lockdrv
suffix:semicolon
r_struct
(brace
DECL|member|lock
id|unchar
id|lock
suffix:semicolon
multiline_comment|/* lock/unlock */
DECL|member|channel
id|unchar
id|channel
suffix:semicolon
multiline_comment|/* channel */
DECL|member|lockchn
)brace
id|lockchn
suffix:semicolon
r_struct
(brace
DECL|member|erase
r_int
id|erase
suffix:semicolon
multiline_comment|/* erase event ? */
DECL|member|handle
r_int
id|handle
suffix:semicolon
DECL|member|evt
id|unchar
id|evt
(braket
id|EVENT_SIZE
)braket
suffix:semicolon
multiline_comment|/* event structure */
DECL|member|event
)brace
id|event
suffix:semicolon
r_struct
(brace
DECL|member|bus
id|unchar
id|bus
suffix:semicolon
multiline_comment|/* SCSI bus */
DECL|member|target
id|unchar
id|target
suffix:semicolon
multiline_comment|/* target ID */
DECL|member|lun
id|unchar
id|lun
suffix:semicolon
multiline_comment|/* LUN */
DECL|member|cmd_len
id|unchar
id|cmd_len
suffix:semicolon
multiline_comment|/* command length */
DECL|member|cmd
id|unchar
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* SCSI command */
DECL|member|scsi
)brace
id|scsi
suffix:semicolon
r_struct
(brace
DECL|member|hdr_no
id|ushort
id|hdr_no
suffix:semicolon
multiline_comment|/* host drive number */
DECL|member|flag
id|unchar
id|flag
suffix:semicolon
multiline_comment|/* old meth./add/remove */
DECL|member|rescan
)brace
id|rescan
suffix:semicolon
DECL|member|iu
)brace
id|iu
suffix:semicolon
DECL|typedef|gdth_iowr_str
)brace
id|gdth_iowr_str
suffix:semicolon
multiline_comment|/* IOCTL structure (read) */
r_typedef
r_struct
(brace
DECL|member|size
id|ulong32
id|size
suffix:semicolon
multiline_comment|/* buffer size */
DECL|member|status
id|ulong32
id|status
suffix:semicolon
multiline_comment|/* IOCTL error code */
r_union
(brace
r_struct
(brace
DECL|member|data
id|unchar
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* data */
DECL|member|general
)brace
id|general
suffix:semicolon
r_struct
(brace
DECL|member|version
id|ushort
id|version
suffix:semicolon
multiline_comment|/* driver version */
DECL|member|drvers
)brace
id|drvers
suffix:semicolon
r_struct
(brace
DECL|member|type
id|unchar
id|type
suffix:semicolon
multiline_comment|/* controller type */
DECL|member|info
id|ushort
id|info
suffix:semicolon
multiline_comment|/* slot etc. */
DECL|member|oem_id
id|ushort
id|oem_id
suffix:semicolon
multiline_comment|/* OEM ID */
DECL|member|bios_ver
id|ushort
id|bios_ver
suffix:semicolon
multiline_comment|/* not used */
DECL|member|access
id|ushort
id|access
suffix:semicolon
multiline_comment|/* not used */
DECL|member|ext_type
id|ushort
id|ext_type
suffix:semicolon
multiline_comment|/* extended type */
DECL|member|ctrtype
)brace
id|ctrtype
suffix:semicolon
r_struct
(brace
DECL|member|version
id|unchar
id|version
suffix:semicolon
multiline_comment|/* OS version */
DECL|member|subversion
id|unchar
id|subversion
suffix:semicolon
multiline_comment|/* OS subversion */
DECL|member|revision
id|ushort
id|revision
suffix:semicolon
multiline_comment|/* revision */
DECL|member|osvers
)brace
id|osvers
suffix:semicolon
r_struct
(brace
DECL|member|count
id|ushort
id|count
suffix:semicolon
multiline_comment|/* controller count */
DECL|member|ctrcnt
)brace
id|ctrcnt
suffix:semicolon
r_struct
(brace
DECL|member|handle
r_int
id|handle
suffix:semicolon
DECL|member|evt
id|unchar
id|evt
(braket
id|EVENT_SIZE
)braket
suffix:semicolon
multiline_comment|/* event structure */
DECL|member|event
)brace
id|event
suffix:semicolon
r_struct
(brace
DECL|member|bus
id|unchar
id|bus
suffix:semicolon
multiline_comment|/* SCSI bus, 0xff: invalid */
DECL|member|target
id|unchar
id|target
suffix:semicolon
multiline_comment|/* target ID */
DECL|member|lun
id|unchar
id|lun
suffix:semicolon
multiline_comment|/* LUN */
DECL|member|cluster_type
id|unchar
id|cluster_type
suffix:semicolon
multiline_comment|/* cluster properties */
DECL|member|hdr_list
)brace
id|hdr_list
(braket
id|MAX_HDRIVES
)braket
suffix:semicolon
multiline_comment|/* index is host drive number */
DECL|member|iu
)brace
id|iu
suffix:semicolon
DECL|typedef|gdth_iord_str
)brace
id|gdth_iord_str
suffix:semicolon
macro_line|#endif
eof
