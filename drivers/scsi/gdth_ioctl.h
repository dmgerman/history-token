macro_line|#ifndef _GDTH_IOCTL_H
DECL|macro|_GDTH_IOCTL_H
mdefine_line|#define _GDTH_IOCTL_H
multiline_comment|/* gdth_ioctl.h&n; * $Id: gdth_ioctl.h,v 1.11 2003/02/27 14:59:03 achim Exp $&n; */
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
DECL|macro|GDTH_MAXSG
mdefine_line|#define GDTH_MAXSG      32                      /* max. s/g elements */
DECL|macro|MAX_LDRIVES
mdefine_line|#define MAX_LDRIVES     255                     /* max. log. drive count */
macro_line|#ifdef GDTH_IOCTL_PROC
DECL|macro|MAX_HDRIVES
mdefine_line|#define MAX_HDRIVES     100                     /* max. host drive count */
macro_line|#else
DECL|macro|MAX_HDRIVES
mdefine_line|#define MAX_HDRIVES     MAX_LDRIVES             /* max. host drive count */
macro_line|#endif
multiline_comment|/* typedefs */
macro_line|#ifdef __KERNEL__
DECL|typedef|ulong32
r_typedef
id|u32
id|ulong32
suffix:semicolon
macro_line|#endif
DECL|macro|PACKED
mdefine_line|#define PACKED  __attribute__((packed))
multiline_comment|/* scatter/gather element */
r_typedef
r_struct
(brace
DECL|member|sg_ptr
id|ulong32
id|sg_ptr
suffix:semicolon
multiline_comment|/* address */
DECL|member|sg_len
id|ulong32
id|sg_len
suffix:semicolon
multiline_comment|/* length */
DECL|typedef|gdth_sg_str
)brace
id|PACKED
id|gdth_sg_str
suffix:semicolon
multiline_comment|/* command structure */
r_typedef
r_struct
(brace
DECL|member|BoardNode
id|ulong32
id|BoardNode
suffix:semicolon
multiline_comment|/* board node (always 0) */
DECL|member|CommandIndex
id|ulong32
id|CommandIndex
suffix:semicolon
multiline_comment|/* command number */
DECL|member|OpCode
id|ushort
id|OpCode
suffix:semicolon
multiline_comment|/* the command (READ,..) */
r_union
(brace
r_struct
(brace
DECL|member|DeviceNo
id|ushort
id|DeviceNo
suffix:semicolon
multiline_comment|/* number of cache drive */
DECL|member|BlockNo
id|ulong32
id|BlockNo
suffix:semicolon
multiline_comment|/* block number */
DECL|member|BlockCnt
id|ulong32
id|BlockCnt
suffix:semicolon
multiline_comment|/* block count */
DECL|member|DestAddr
id|ulong32
id|DestAddr
suffix:semicolon
multiline_comment|/* dest. addr. (if s/g: -1) */
DECL|member|sg_canz
id|ulong32
id|sg_canz
suffix:semicolon
multiline_comment|/* s/g element count */
DECL|member|sg_lst
id|gdth_sg_str
id|sg_lst
(braket
id|GDTH_MAXSG
)braket
suffix:semicolon
multiline_comment|/* s/g list */
DECL|member|cache
)brace
id|PACKED
id|cache
suffix:semicolon
multiline_comment|/* cache service cmd. str. */
r_struct
(brace
DECL|member|param_size
id|ushort
id|param_size
suffix:semicolon
multiline_comment|/* size of p_param buffer */
DECL|member|subfunc
id|ulong32
id|subfunc
suffix:semicolon
multiline_comment|/* IOCTL function */
DECL|member|channel
id|ulong32
id|channel
suffix:semicolon
multiline_comment|/* device */
DECL|member|p_param
id|ulong32
id|p_param
suffix:semicolon
multiline_comment|/* buffer */
DECL|member|ioctl
)brace
id|PACKED
id|ioctl
suffix:semicolon
multiline_comment|/* IOCTL command structure */
r_struct
(brace
DECL|member|reserved
id|ushort
id|reserved
suffix:semicolon
r_union
(brace
r_struct
(brace
DECL|member|msg_handle
id|ulong32
id|msg_handle
suffix:semicolon
multiline_comment|/* message handle */
DECL|member|msg_addr
id|ulong32
id|msg_addr
suffix:semicolon
multiline_comment|/* message buffer address */
DECL|member|msg
)brace
id|PACKED
id|msg
suffix:semicolon
DECL|member|data
id|unchar
id|data
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* buffer for rtc data, ... */
DECL|member|su
)brace
id|su
suffix:semicolon
DECL|member|screen
)brace
id|PACKED
id|screen
suffix:semicolon
multiline_comment|/* screen service cmd. str. */
r_struct
(brace
DECL|member|reserved
id|ushort
id|reserved
suffix:semicolon
DECL|member|direction
id|ulong32
id|direction
suffix:semicolon
multiline_comment|/* data direction */
DECL|member|mdisc_time
id|ulong32
id|mdisc_time
suffix:semicolon
multiline_comment|/* disc. time (0: no timeout)*/
DECL|member|mcon_time
id|ulong32
id|mcon_time
suffix:semicolon
multiline_comment|/* connect time(0: no to.) */
DECL|member|sdata
id|ulong32
id|sdata
suffix:semicolon
multiline_comment|/* dest. addr. (if s/g: -1) */
DECL|member|sdlen
id|ulong32
id|sdlen
suffix:semicolon
multiline_comment|/* data length (bytes) */
DECL|member|clen
id|ulong32
id|clen
suffix:semicolon
multiline_comment|/* SCSI cmd. length(6,10,12) */
DECL|member|cmd
id|unchar
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* SCSI command */
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
DECL|member|bus
id|unchar
id|bus
suffix:semicolon
multiline_comment|/* SCSI bus number */
DECL|member|priority
id|unchar
id|priority
suffix:semicolon
multiline_comment|/* only 0 used */
DECL|member|sense_len
id|ulong32
id|sense_len
suffix:semicolon
multiline_comment|/* sense data length */
DECL|member|sense_data
id|ulong32
id|sense_data
suffix:semicolon
multiline_comment|/* sense data addr. */
DECL|member|link_p
id|ulong32
id|link_p
suffix:semicolon
multiline_comment|/* linked cmds (not supp.) */
DECL|member|sg_ranz
id|ulong32
id|sg_ranz
suffix:semicolon
multiline_comment|/* s/g element count */
DECL|member|sg_lst
id|gdth_sg_str
id|sg_lst
(braket
id|GDTH_MAXSG
)braket
suffix:semicolon
multiline_comment|/* s/g list */
DECL|member|raw
)brace
id|PACKED
id|raw
suffix:semicolon
multiline_comment|/* raw service cmd. struct. */
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* additional variables */
DECL|member|Service
id|unchar
id|Service
suffix:semicolon
multiline_comment|/* controller service */
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|Status
id|ushort
id|Status
suffix:semicolon
multiline_comment|/* command result */
DECL|member|Info
id|ulong32
id|Info
suffix:semicolon
multiline_comment|/* additional information */
DECL|member|RequestBuffer
r_void
op_star
id|RequestBuffer
suffix:semicolon
multiline_comment|/* request buffer */
DECL|typedef|gdth_cmd_str
)brace
id|PACKED
id|gdth_cmd_str
suffix:semicolon
multiline_comment|/* controller event structure */
DECL|macro|ES_ASYNC
mdefine_line|#define ES_ASYNC    1
DECL|macro|ES_DRIVER
mdefine_line|#define ES_DRIVER   2
DECL|macro|ES_TEST
mdefine_line|#define ES_TEST     3
DECL|macro|ES_SYNC
mdefine_line|#define ES_SYNC     4
r_typedef
r_struct
(brace
DECL|member|size
id|ushort
id|size
suffix:semicolon
multiline_comment|/* size of structure */
r_union
(brace
DECL|member|stream
r_char
id|stream
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
DECL|member|service
id|ushort
id|service
suffix:semicolon
DECL|member|index
id|ulong32
id|index
suffix:semicolon
DECL|member|driver
)brace
id|PACKED
id|driver
suffix:semicolon
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
DECL|member|service
id|ushort
id|service
suffix:semicolon
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|info
id|ulong32
id|info
suffix:semicolon
DECL|member|scsi_coord
id|unchar
id|scsi_coord
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|async
)brace
id|PACKED
id|async
suffix:semicolon
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
DECL|member|service
id|ushort
id|service
suffix:semicolon
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|info
id|ulong32
id|info
suffix:semicolon
DECL|member|hostdrive
id|ushort
id|hostdrive
suffix:semicolon
DECL|member|scsi_coord
id|unchar
id|scsi_coord
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|sense_key
id|unchar
id|sense_key
suffix:semicolon
DECL|member|sync
)brace
id|PACKED
id|sync
suffix:semicolon
r_struct
(brace
DECL|member|l1
DECL|member|l2
DECL|member|l3
DECL|member|l4
id|ulong32
id|l1
comma
id|l2
comma
id|l3
comma
id|l4
suffix:semicolon
DECL|member|test
)brace
id|PACKED
id|test
suffix:semicolon
DECL|member|eu
)brace
id|eu
suffix:semicolon
DECL|member|severity
id|ulong32
id|severity
suffix:semicolon
DECL|member|event_string
id|unchar
id|event_string
(braket
l_int|256
)braket
suffix:semicolon
DECL|typedef|gdth_evt_data
)brace
id|PACKED
id|gdth_evt_data
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|first_stamp
id|ulong32
id|first_stamp
suffix:semicolon
DECL|member|last_stamp
id|ulong32
id|last_stamp
suffix:semicolon
DECL|member|same_count
id|ushort
id|same_count
suffix:semicolon
DECL|member|event_source
id|ushort
id|event_source
suffix:semicolon
DECL|member|event_idx
id|ushort
id|event_idx
suffix:semicolon
DECL|member|application
id|unchar
id|application
suffix:semicolon
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|event_data
id|gdth_evt_data
id|event_data
suffix:semicolon
DECL|typedef|gdth_evt_str
)brace
id|PACKED
id|gdth_evt_str
suffix:semicolon
macro_line|#ifdef GDTH_IOCTL_PROC
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
DECL|member|device_id
id|ushort
id|device_id
suffix:semicolon
multiline_comment|/* device ID */
DECL|member|sub_device_id
id|ushort
id|sub_device_id
suffix:semicolon
multiline_comment|/* sub device ID */
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
macro_line|#ifdef GDTH_IOCTL_CHRDEV
multiline_comment|/* GDTIOCTL_GENERAL */
r_typedef
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
multiline_comment|/* controller number */
DECL|member|timeout
id|ushort
id|timeout
suffix:semicolon
multiline_comment|/* timeout */
DECL|member|info
id|ulong32
id|info
suffix:semicolon
multiline_comment|/* error info */
DECL|member|status
id|ushort
id|status
suffix:semicolon
multiline_comment|/* status */
DECL|member|data_len
id|ulong
id|data_len
suffix:semicolon
multiline_comment|/* data buffer size */
DECL|member|sense_len
id|ulong
id|sense_len
suffix:semicolon
multiline_comment|/* sense buffer size */
DECL|member|command
id|gdth_cmd_str
id|command
suffix:semicolon
multiline_comment|/* command */
DECL|typedef|gdth_ioctl_general
)brace
id|gdth_ioctl_general
suffix:semicolon
multiline_comment|/* GDTIOCTL_LOCKDRV */
r_typedef
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
multiline_comment|/* controller number */
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
DECL|typedef|gdth_ioctl_lockdrv
)brace
id|gdth_ioctl_lockdrv
suffix:semicolon
multiline_comment|/* GDTIOCTL_LOCKCHN */
r_typedef
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
multiline_comment|/* controller number */
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
DECL|typedef|gdth_ioctl_lockchn
)brace
id|gdth_ioctl_lockchn
suffix:semicolon
multiline_comment|/* GDTIOCTL_OSVERS */
r_typedef
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
DECL|typedef|gdth_ioctl_osvers
)brace
id|gdth_ioctl_osvers
suffix:semicolon
multiline_comment|/* GDTIOCTL_CTRTYPE */
r_typedef
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
multiline_comment|/* controller number */
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
DECL|member|device_id
id|ushort
id|device_id
suffix:semicolon
multiline_comment|/* device ID */
DECL|member|sub_device_id
id|ushort
id|sub_device_id
suffix:semicolon
multiline_comment|/* sub device ID */
DECL|typedef|gdth_ioctl_ctrtype
)brace
id|gdth_ioctl_ctrtype
suffix:semicolon
multiline_comment|/* GDTIOCTL_EVENT */
r_typedef
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
DECL|member|erase
r_int
id|erase
suffix:semicolon
multiline_comment|/* erase event? */
DECL|member|handle
r_int
id|handle
suffix:semicolon
multiline_comment|/* event handle */
DECL|member|event
id|gdth_evt_str
id|event
suffix:semicolon
DECL|typedef|gdth_ioctl_event
)brace
id|gdth_ioctl_event
suffix:semicolon
multiline_comment|/* GDTIOCTL_RESCAN/GDTIOCTL_HDRLIST */
r_typedef
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
multiline_comment|/* controller number */
DECL|member|flag
id|unchar
id|flag
suffix:semicolon
multiline_comment|/* add/remove */
DECL|member|hdr_no
id|ushort
id|hdr_no
suffix:semicolon
multiline_comment|/* drive no. */
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
DECL|typedef|gdth_ioctl_rescan
)brace
id|gdth_ioctl_rescan
suffix:semicolon
multiline_comment|/* GDTIOCTL_RESET_BUS/GDTIOCTL_RESET_DRV */
r_typedef
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
multiline_comment|/* controller number */
DECL|member|number
id|ushort
id|number
suffix:semicolon
multiline_comment|/* bus/host drive number */
DECL|member|status
id|ushort
id|status
suffix:semicolon
multiline_comment|/* status */
DECL|typedef|gdth_ioctl_reset
)brace
id|gdth_ioctl_reset
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
