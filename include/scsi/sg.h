macro_line|#ifndef _SCSI_GENERIC_H
DECL|macro|_SCSI_GENERIC_H
mdefine_line|#define _SCSI_GENERIC_H
multiline_comment|/*&n;   History:&n;    Started: Aug 9 by Lawrence Foard (entropy@world.std.com), to allow user&n;     process control of SCSI devices.&n;    Development Sponsored by Killy Corp. NY NY&n;Original driver (sg.h):&n;*       Copyright (C) 1992 Lawrence Foard&n;Version 2 and 3 extensions to driver:&n;*       Copyright (C) 1998 - 2000 Douglas Gilbert&n;&n;    Version: 3.1.17 (20000921)&n;    This version is for 2.4 series kernels.&n;&n;    Changes since 3.1.16 (20000716)&n;    &t;- changes for new scsi subsystem initialization&n;    &t;- change Scsi_Cmnd usage to Scsi_Request&n;    &t;- cleanup for no procfs&n;    Changes since 3.1.15 (20000528)&n;    &t;- further (scatter gather) buffer length changes&n;    Changes since 3.1.14 (20000503)&n;        - fix aha1542 odd length buffer problem&n;        - make multiple readers on same fd safe&n;    Changes since 3.1.13 (20000324)&n;        - revert change so sg_header interface doesn&squot;t send _UNKNOWN&n;        - &quot;discon&quot; and &quot;tq&quot; in /proc/scsi/sg/devices replaced with&n;          &quot;bopens&quot; and &quot;busy&quot;; correct duration output in procfs&n;        - provision for SG_RESET&n;        - lock file descriptor and request lists&n;    Changes since 3.1.12 (20000222)&n;    &t;- make sg_header interface use SCSI_DATA_UNKNOWN&n;    &t;- add SG_DXFER_UNKNOWN define to sg interface&n;    &t;- stop allocating data buffers to non data transfer commands&n;    Changes since 3.1.10 (20000123)&n;    &t;- make device allocation dynamic (get rid of SG_EXTRA_DEVS)&n;&t;- move to sg0,sg1,sg2 rather than sga,sgb,sgc&n;&t;- make sg_io_hdr_t safer across architectures&n;    Changes since 2.1.34 (990603) and 2.3.35 (990708)&n;&t;- add new interface structure: sg_io_hdr_t&n;&t;  - supports larger sense buffer, DMA residual count + direct IO&n;&t;- add SG_IO ioctl (combines function of write() + read() )&n;&t;- remove SG_SET_MERGE_FD, UNDERRUN_FLAG + _GET_ ioctls + logic&n;&t;- add proc_fs support in /proc/scsi/sg/ directory&n;        - add queuing info into struct sg_scsi_id&n;&t;- def_reserved_size can be given at driver or module load time&n;    Changes since 2.1.33 (990521)&n;        - implement SG_SET_RESERVED_SIZE and associated memory re-org.&n;        - add SG_NEXT_CMD_LEN to override SCSI command lengths&n;        - add SG_GET_VERSION_NUM to get version expressed as an integer&n;    Changes since 2.1.32 (990501)&n;        - fix race condition in sg_read() and sg_open()&n;    Changes since 2.1.31 (990327)&n;        - add ioctls SG_GET_UNDERRUN_FLAG and _SET_. Change the default&n;          to _not_ flag underruns (affects aic7xxx driver)&n;        - clean up logging of pointers to use %p (for 64 bit architectures)&n;        - rework usage of get_user/copy_to_user family of kernel calls&n;        - &quot;disown&quot; scsi_command blocks before releasing them&n;&n;Map of SG verions to the Linux kernels in which they appear:&n;       ----------        ----------------------------------&n;       original          all kernels &lt; 2.2.6&n;       2.1.31            2.2.6 and 2.2.7&n;       2.1.32            2.2.8 and 2.2.9&n;       2.1.34            2.2.10 to 2.2.13&n;       2.1.36            2.2.14 and 2.2.15&n;       3.0.x             optional version 3 sg driver for 2.2 series&n;       3.1.x             first appeared in lk 2.3.43&n;&n;Major new features in SG 3.x driver (cf SG 2.x drivers)&n;&t;- SG_IO ioctl() combines function if write() and read()&n;&t;- new interface (sg_io_hdr_t) but still supports old interface&n;&t;- scatter/gather in user space and direct IO supported&n;&n;Major features in SG 2.x driver (cf original SG driver)&n;&t;- per file descriptor (fd) write-read sequencing&n;&t;- command queuing supported&n;&t;- scatter-gather supported at kernel level allowing potentially&n;&t;  large transfers&n;&t;- more SCSI status information returned&n;&t;- asynchronous notification support added (SIGPOLL, SIGIO)&n;&t;- read() can fetch by given pack_id&n;&t;- uses kernel memory as appropriate for SCSI adapter being used&n;&t;- single SG_BIG_BUFF replaced by per file descriptor &quot;reserve&n;&t;  buffer&quot; whose size can be manipulated by ioctls()&n;&n; The term &quot;indirect IO&quot; refers a method by which data is DMAed into kernel&n; buffers from the hardware and afterwards is transferred into the user&n; space (or vice versa if you are writing). Transfer speeds of up to 20 to&n; 30MBytes/sec have been measured using indirect IO. For faster throughputs&n; &quot;direct IO&quot; which cuts out the double handling of data is required.&n; Direct IO is supported by the SG 3.x drivers on 2.3 series Linux kernels&n; (or later) and requires the use of the new interface.&n;&n; Requests for direct IO with the new interface will automatically fall back&n; to indirect IO mode if they cannot be fulfilled. An example of such a case&n; is an ISA SCSI adapter which is only capable of DMAing to the lower 16MB of&n; memory due to the architecture of ISA. The &squot;info&squot; field in the new&n; interface indicates whether a direct or indirect data transfer took place.&n;&n; Obtaining memory for the kernel buffers used in indirect IO is done by&n; first checking if the &quot;reserved buffer&quot; for the current file descriptor&n; is available and large enough. If these conditions are _not_ met then&n; kernel memory is obtained on a per SCSI command basis. This corresponds&n; to a write(), read() sequence or a SG_IO ioctl() call. Further, the&n; kernel memory that is suitable for DMA may be constrained by the&n; architecture of the SCSI adapter (e.g. ISA adapters).&n;&n; Documentation&n; =============&n; A web site for SG device drivers can be found at:&n;&t;http://www.torque.net/sg  [alternatively check the MAINTAINERS file]&n; The main documents are still based on 2.x versions:&n;&t;http://www.torque.net/sg/p/scsi-generic.txt&n;&t;http://www.torque.net/sg/p/scsi-generic_long.txt&n; Documentation on the changes and additions in 3.x version of the sg driver&n; can be found at: http://www.torque.net/sg/p/scsi-generic_v3.txt&n; This document can also be found in the kernel source tree, probably at:&n;        /usr/src/linux/Documentation/scsi-generic.txt .&n; Utility and test programs are also available at that web site.&n;*/
multiline_comment|/* New interface introduced in the 3.x SG drivers follows */
DECL|struct|sg_iovec
r_typedef
r_struct
id|sg_iovec
multiline_comment|/* same structure as used by readv() Linux system */
(brace
multiline_comment|/* call. It defines one scatter-gather element. */
DECL|member|iov_base
r_void
op_star
id|iov_base
suffix:semicolon
multiline_comment|/* Starting address  */
DECL|member|iov_len
r_int
id|iov_len
suffix:semicolon
multiline_comment|/* Length in bytes  */
DECL|typedef|sg_iovec_t
)brace
id|sg_iovec_t
suffix:semicolon
DECL|struct|sg_io_hdr
r_typedef
r_struct
id|sg_io_hdr
(brace
DECL|member|interface_id
r_int
id|interface_id
suffix:semicolon
multiline_comment|/* [i] &squot;S&squot; for SCSI generic (required) */
DECL|member|dxfer_direction
r_int
id|dxfer_direction
suffix:semicolon
multiline_comment|/* [i] data transfer direction  */
DECL|member|cmd_len
r_int
r_char
id|cmd_len
suffix:semicolon
multiline_comment|/* [i] SCSI command length ( &lt;= 16 bytes) */
DECL|member|mx_sb_len
r_int
r_char
id|mx_sb_len
suffix:semicolon
multiline_comment|/* [i] max length to write to sbp */
DECL|member|iovec_count
r_int
r_int
id|iovec_count
suffix:semicolon
multiline_comment|/* [i] 0 implies no scatter gather */
DECL|member|dxfer_len
r_int
r_int
id|dxfer_len
suffix:semicolon
multiline_comment|/* [i] byte count of data transfer */
DECL|member|dxferp
r_void
op_star
id|dxferp
suffix:semicolon
multiline_comment|/* [i], [*io] points to data transfer memory&n;&t;&t;&t;&t;&t;      or scatter gather list */
DECL|member|cmdp
r_int
r_char
op_star
id|cmdp
suffix:semicolon
multiline_comment|/* [i], [*i] points to command to perform */
DECL|member|sbp
r_int
r_char
op_star
id|sbp
suffix:semicolon
multiline_comment|/* [i], [*o] points to sense_buffer memory */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* [i] MAX_UINT-&gt;no timeout (unit: millisec) */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* [i] 0 -&gt; default, see SG_FLAG... */
DECL|member|pack_id
r_int
id|pack_id
suffix:semicolon
multiline_comment|/* [i-&gt;o] unused internally (normally) */
DECL|member|usr_ptr
r_void
op_star
id|usr_ptr
suffix:semicolon
multiline_comment|/* [i-&gt;o] unused internally */
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* [o] scsi status */
DECL|member|masked_status
r_int
r_char
id|masked_status
suffix:semicolon
multiline_comment|/* [o] shifted, masked scsi status */
DECL|member|msg_status
r_int
r_char
id|msg_status
suffix:semicolon
multiline_comment|/* [o] messaging level data (optional) */
DECL|member|sb_len_wr
r_int
r_char
id|sb_len_wr
suffix:semicolon
multiline_comment|/* [o] byte count actually written to sbp */
DECL|member|host_status
r_int
r_int
id|host_status
suffix:semicolon
multiline_comment|/* [o] errors from host adapter */
DECL|member|driver_status
r_int
r_int
id|driver_status
suffix:semicolon
multiline_comment|/* [o] errors from software driver */
DECL|member|resid
r_int
id|resid
suffix:semicolon
multiline_comment|/* [o] dxfer_len - actual_transferred */
DECL|member|duration
r_int
r_int
id|duration
suffix:semicolon
multiline_comment|/* [o] time taken by cmd (unit: millisec) */
DECL|member|info
r_int
r_int
id|info
suffix:semicolon
multiline_comment|/* [o] auxiliary information */
DECL|typedef|sg_io_hdr_t
)brace
id|sg_io_hdr_t
suffix:semicolon
multiline_comment|/* 64 bytes long (on i386) */
multiline_comment|/* Use negative values to flag difference from original sg_header structure */
DECL|macro|SG_DXFER_NONE
mdefine_line|#define SG_DXFER_NONE -1        /* e.g. a SCSI Test Unit Ready command */
DECL|macro|SG_DXFER_TO_DEV
mdefine_line|#define SG_DXFER_TO_DEV -2      /* e.g. a SCSI WRITE command */
DECL|macro|SG_DXFER_FROM_DEV
mdefine_line|#define SG_DXFER_FROM_DEV -3    /* e.g. a SCSI READ command */
DECL|macro|SG_DXFER_TO_FROM_DEV
mdefine_line|#define SG_DXFER_TO_FROM_DEV -4 /* treated like SG_DXFER_FROM_DEV with the&n;&t;&t;&t;&t;   additional property than during indirect&n;&t;&t;&t;&t;   IO the user buffer is copied into the&n;&t;&t;&t;&t;   kernel buffers before the transfer */
DECL|macro|SG_DXFER_UNKNOWN
mdefine_line|#define SG_DXFER_UNKNOWN -5     /* Unknown data direction */
multiline_comment|/* following flag values can be &quot;or&quot;-ed together */
DECL|macro|SG_FLAG_DIRECT_IO
mdefine_line|#define SG_FLAG_DIRECT_IO 1     /* default is indirect IO */
DECL|macro|SG_FLAG_LUN_INHIBIT
mdefine_line|#define SG_FLAG_LUN_INHIBIT 2   /* default is to put device&squot;s lun into */
multiline_comment|/* the 2nd byte of SCSI command */
DECL|macro|SG_FLAG_NO_DXFER
mdefine_line|#define SG_FLAG_NO_DXFER 0x10000 /* no transfer of kernel buffers to/from */
multiline_comment|/* user space (debug indirect IO) */
multiline_comment|/* following &squot;info&squot; values are &quot;or&quot;-ed together */
DECL|macro|SG_INFO_OK_MASK
mdefine_line|#define SG_INFO_OK_MASK 0x1
DECL|macro|SG_INFO_OK
mdefine_line|#define SG_INFO_OK 0x0          /* no sense, host nor driver &quot;noise&quot; */
DECL|macro|SG_INFO_CHECK
mdefine_line|#define SG_INFO_CHECK 0x1       /* something abnormal happened */
DECL|macro|SG_INFO_DIRECT_IO_MASK
mdefine_line|#define SG_INFO_DIRECT_IO_MASK 0x6
DECL|macro|SG_INFO_INDIRECT_IO
mdefine_line|#define SG_INFO_INDIRECT_IO 0x0 /* data xfer via kernel buffers (or no xfer) */
DECL|macro|SG_INFO_DIRECT_IO
mdefine_line|#define SG_INFO_DIRECT_IO 0x2   /* direct IO requested and performed */
DECL|macro|SG_INFO_MIXED_IO
mdefine_line|#define SG_INFO_MIXED_IO 0x4    /* part direct, part indirect IO */
DECL|struct|sg_scsi_id
r_typedef
r_struct
id|sg_scsi_id
(brace
multiline_comment|/* used by SG_GET_SCSI_ID ioctl() */
DECL|member|host_no
r_int
id|host_no
suffix:semicolon
multiline_comment|/* as in &quot;scsi&lt;n&gt;&quot; where &squot;n&squot; is one of 0, 1, 2 etc */
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|scsi_id
r_int
id|scsi_id
suffix:semicolon
multiline_comment|/* scsi id of target device */
DECL|member|lun
r_int
id|lun
suffix:semicolon
DECL|member|scsi_type
r_int
id|scsi_type
suffix:semicolon
multiline_comment|/* TYPE_... defined in scsi/scsi.h */
DECL|member|h_cmd_per_lun
r_int
id|h_cmd_per_lun
suffix:semicolon
multiline_comment|/* host (adapter) maximum commands per lun */
DECL|member|d_queue_depth
r_int
id|d_queue_depth
suffix:semicolon
multiline_comment|/* device (or adapter) maximum queue length */
DECL|member|unused
r_int
id|unused
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* probably find a good use, set 0 for now */
DECL|typedef|sg_scsi_id_t
)brace
id|sg_scsi_id_t
suffix:semicolon
multiline_comment|/* 32 bytes long on i386 */
DECL|struct|sg_req_info
r_typedef
r_struct
id|sg_req_info
(brace
multiline_comment|/* used by SG_GET_REQUEST_TABLE ioctl() */
DECL|member|req_state
r_char
id|req_state
suffix:semicolon
multiline_comment|/* 0 -&gt; not used, 1 -&gt; written, 2 -&gt; ready to read */
DECL|member|orphan
r_char
id|orphan
suffix:semicolon
multiline_comment|/* 0 -&gt; normal request, 1 -&gt; from interruped SG_IO */
DECL|member|sg_io_owned
r_char
id|sg_io_owned
suffix:semicolon
multiline_comment|/* 0 -&gt; complete with read(), 1 -&gt; owned by SG_IO */
DECL|member|problem
r_char
id|problem
suffix:semicolon
multiline_comment|/* 0 -&gt; no problem detected, 1 -&gt; error to report */
DECL|member|pack_id
r_int
id|pack_id
suffix:semicolon
multiline_comment|/* pack_id associated with request */
DECL|member|usr_ptr
r_void
op_star
id|usr_ptr
suffix:semicolon
multiline_comment|/* user provided pointer (in new interface) */
DECL|member|duration
r_int
r_int
id|duration
suffix:semicolon
multiline_comment|/* millisecs elapsed since written (req_state==1)&n;&t;&t;&t;      or request duration (req_state==2) */
DECL|member|unused
r_int
id|unused
suffix:semicolon
DECL|typedef|sg_req_info_t
)brace
id|sg_req_info_t
suffix:semicolon
multiline_comment|/* 20 bytes long on i386 */
multiline_comment|/* IOCTLs: Those ioctls that are relevant to the SG 3.x drivers follow.&n; [Those that only apply to the SG 2.x drivers are at the end of the file.]&n; (_GET_s yield result via &squot;int *&squot; 3rd argument unless otherwise indicated) */
DECL|macro|SG_EMULATED_HOST
mdefine_line|#define SG_EMULATED_HOST 0x2203 /* true for emulated host adapter (ATAPI) */
multiline_comment|/* Used to configure SCSI command transformation layer for ATAPI devices */
multiline_comment|/* Only supported by the ide-scsi driver */
DECL|macro|SG_SET_TRANSFORM
mdefine_line|#define SG_SET_TRANSFORM 0x2204 /* N.B. 3rd arg is not pointer but value: */
multiline_comment|/* 3rd arg = 0 to disable transform, 1 to enable it */
DECL|macro|SG_GET_TRANSFORM
mdefine_line|#define SG_GET_TRANSFORM 0x2205
DECL|macro|SG_SET_RESERVED_SIZE
mdefine_line|#define SG_SET_RESERVED_SIZE 0x2275  /* request a new reserved buffer size */
DECL|macro|SG_GET_RESERVED_SIZE
mdefine_line|#define SG_GET_RESERVED_SIZE 0x2272  /* actual size of reserved buffer */
multiline_comment|/* The following ioctl has a &squot;sg_scsi_id_t *&squot; object as its 3rd argument. */
DECL|macro|SG_GET_SCSI_ID
mdefine_line|#define SG_GET_SCSI_ID 0x2276   /* Yields fd&squot;s bus, chan, dev, lun + type */
multiline_comment|/* SCSI id information can also be obtained from SCSI_IOCTL_GET_IDLUN */
multiline_comment|/* Override host setting and always DMA using low memory ( &lt;16MB on i386) */
DECL|macro|SG_SET_FORCE_LOW_DMA
mdefine_line|#define SG_SET_FORCE_LOW_DMA 0x2279  /* 0-&gt; use adapter setting, 1-&gt; force */
DECL|macro|SG_GET_LOW_DMA
mdefine_line|#define SG_GET_LOW_DMA 0x227a   /* 0-&gt; use all ram for dma; 1-&gt; low dma ram */
multiline_comment|/* When SG_SET_FORCE_PACK_ID set to 1, pack_id is input to read() which&n;   tries to fetch a packet with a matching pack_id, waits, or returns EAGAIN.&n;   If pack_id is -1 then read oldest waiting. When ...FORCE_PACK_ID set to 0&n;   then pack_id ignored by read() and oldest readable fetched. */
DECL|macro|SG_SET_FORCE_PACK_ID
mdefine_line|#define SG_SET_FORCE_PACK_ID 0x227b
DECL|macro|SG_GET_PACK_ID
mdefine_line|#define SG_GET_PACK_ID 0x227c /* Yields oldest readable pack_id (or -1) */
DECL|macro|SG_GET_NUM_WAITING
mdefine_line|#define SG_GET_NUM_WAITING 0x227d /* Number of commands awaiting read() */
multiline_comment|/* Yields max scatter gather tablesize allowed by current host adapter */
DECL|macro|SG_GET_SG_TABLESIZE
mdefine_line|#define SG_GET_SG_TABLESIZE 0x227F  /* 0 implies can&squot;t do scatter gather */
DECL|macro|SG_GET_VERSION_NUM
mdefine_line|#define SG_GET_VERSION_NUM 0x2282 /* Example: version 2.1.34 yields 20134 */
multiline_comment|/* Returns -EBUSY if occupied. 3rd argument pointer to int (see next) */
DECL|macro|SG_SCSI_RESET
mdefine_line|#define SG_SCSI_RESET 0x2284
multiline_comment|/* Associated values that can be given to SG_SCSI_RESET follow */
DECL|macro|SG_SCSI_RESET_NOTHING
mdefine_line|#define&t;&t;SG_SCSI_RESET_NOTHING&t;0
DECL|macro|SG_SCSI_RESET_DEVICE
mdefine_line|#define&t;&t;SG_SCSI_RESET_DEVICE&t;1
DECL|macro|SG_SCSI_RESET_BUS
mdefine_line|#define&t;&t;SG_SCSI_RESET_BUS&t;2
DECL|macro|SG_SCSI_RESET_HOST
mdefine_line|#define&t;&t;SG_SCSI_RESET_HOST&t;3
multiline_comment|/* synchronous SCSI command ioctl, (only in version 3 interface) */
DECL|macro|SG_IO
mdefine_line|#define SG_IO 0x2285   /* similar effect as write() followed by read() */
DECL|macro|SG_GET_REQUEST_TABLE
mdefine_line|#define SG_GET_REQUEST_TABLE 0x2286   /* yields table of active requests */
multiline_comment|/* How to treat EINTR during SG_IO ioctl(), only in SG 3.x series */
DECL|macro|SG_SET_KEEP_ORPHAN
mdefine_line|#define SG_SET_KEEP_ORPHAN 0x2287 /* 1 -&gt; hold for read(), 0 -&gt; drop (def) */
DECL|macro|SG_GET_KEEP_ORPHAN
mdefine_line|#define SG_GET_KEEP_ORPHAN 0x2288
DECL|macro|SG_SCATTER_SZ
mdefine_line|#define SG_SCATTER_SZ (8 * 4096)  /* PAGE_SIZE not available to user */
multiline_comment|/* Largest size (in bytes) a single scatter-gather list element can have.&n;   The value must be a power of 2 and &lt;= (PAGE_SIZE * 32) [131072 bytes on&n;   i386]. The minimum value is PAGE_SIZE. If scatter-gather not supported&n;   by adapter then this value is the largest data block that can be&n;   read/written by a single scsi command. The user can find the value of&n;   PAGE_SIZE by calling getpagesize() defined in unistd.h . */
DECL|macro|SG_DEFAULT_RETRIES
mdefine_line|#define SG_DEFAULT_RETRIES 1
multiline_comment|/* Defaults, commented if they differ from original sg driver */
DECL|macro|SG_DEF_FORCE_LOW_DMA
mdefine_line|#define SG_DEF_FORCE_LOW_DMA 0  /* was 1 -&gt; memory below 16MB on i386 */
DECL|macro|SG_DEF_FORCE_PACK_ID
mdefine_line|#define SG_DEF_FORCE_PACK_ID 0
DECL|macro|SG_DEF_KEEP_ORPHAN
mdefine_line|#define SG_DEF_KEEP_ORPHAN 0
DECL|macro|SG_DEF_RESERVED_SIZE
mdefine_line|#define SG_DEF_RESERVED_SIZE SG_SCATTER_SZ /* load time option */
multiline_comment|/* maximum outstanding requests, write() yields EDOM if exceeded */
DECL|macro|SG_MAX_QUEUE
mdefine_line|#define SG_MAX_QUEUE 16
DECL|macro|SG_BIG_BUFF
mdefine_line|#define SG_BIG_BUFF SG_DEF_RESERVED_SIZE    /* for backward compatibility */
multiline_comment|/* Alternate style type names, &quot;..._t&quot; variants preferred */
DECL|typedef|Sg_io_hdr
r_typedef
r_struct
id|sg_io_hdr
id|Sg_io_hdr
suffix:semicolon
DECL|typedef|Sg_io_vec
r_typedef
r_struct
id|sg_io_vec
id|Sg_io_vec
suffix:semicolon
DECL|typedef|Sg_scsi_id
r_typedef
r_struct
id|sg_scsi_id
id|Sg_scsi_id
suffix:semicolon
DECL|typedef|Sg_req_info
r_typedef
r_struct
id|sg_req_info
id|Sg_req_info
suffix:semicolon
multiline_comment|/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
multiline_comment|/*   The older SG interface based on the &squot;sg_header&squot; structure follows.   */
multiline_comment|/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
DECL|macro|SG_MAX_SENSE
mdefine_line|#define SG_MAX_SENSE 16   /* this only applies to the sg_header interface */
DECL|struct|sg_header
r_struct
id|sg_header
(brace
DECL|member|pack_len
r_int
id|pack_len
suffix:semicolon
multiline_comment|/* [o] reply_len (ie useless), ignored as input */
DECL|member|reply_len
r_int
id|reply_len
suffix:semicolon
multiline_comment|/* [i] max length of expected reply (inc. sg_header) */
DECL|member|pack_id
r_int
id|pack_id
suffix:semicolon
multiline_comment|/* [io] id number of packet (use ints &gt;= 0) */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* [o] 0==ok, else (+ve) Unix errno (best ignored) */
DECL|member|twelve_byte
r_int
r_int
id|twelve_byte
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [i] Force 12 byte command length for group 6 &amp; 7 commands  */
DECL|member|target_status
r_int
r_int
id|target_status
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* [o] scsi status from target */
DECL|member|host_status
r_int
r_int
id|host_status
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* [o] host status (see &quot;DID&quot; codes) */
DECL|member|driver_status
r_int
r_int
id|driver_status
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* [o] driver status+suggestion */
DECL|member|other_flags
r_int
r_int
id|other_flags
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* unused */
DECL|member|sense_buffer
r_int
r_char
id|sense_buffer
(braket
id|SG_MAX_SENSE
)braket
suffix:semicolon
multiline_comment|/* [o] Output in 3 cases:&n;&t;   when target_status is CHECK_CONDITION or&n;&t;   when target_status is COMMAND_TERMINATED or&n;&t;   when (driver_status &amp; DRIVER_SENSE) is true. */
)brace
suffix:semicolon
multiline_comment|/* This structure is 36 bytes long on i386 */
multiline_comment|/* IOCTLs: The following are not required (or ignored) when the sg_io_hdr_t&n;&t;   interface is used. They are kept for backward compatibility with&n;&t;   the original and version 2 drivers. */
DECL|macro|SG_SET_TIMEOUT
mdefine_line|#define SG_SET_TIMEOUT 0x2201  /* unit: jiffies (10ms on i386) */
DECL|macro|SG_GET_TIMEOUT
mdefine_line|#define SG_GET_TIMEOUT 0x2202  /* yield timeout as _return_ value */
multiline_comment|/* Get/set command queuing state per fd (default is SG_DEF_COMMAND_Q.&n;   Each time a sg_io_hdr_t object is seen on this file descriptor, this&n;   command queuing flag is set on (overriding the previous setting). */
DECL|macro|SG_GET_COMMAND_Q
mdefine_line|#define SG_GET_COMMAND_Q 0x2270   /* Yields 0 (queuing off) or 1 (on) */
DECL|macro|SG_SET_COMMAND_Q
mdefine_line|#define SG_SET_COMMAND_Q 0x2271   /* Change queuing state with 0 or 1 */
multiline_comment|/* Turn on/off error sense trace (1 and 0 respectively, default is off).&n;   Try using: &quot;# cat /proc/scsi/sg/debug&quot; instead in the v3 driver */
DECL|macro|SG_SET_DEBUG
mdefine_line|#define SG_SET_DEBUG 0x227e    /* 0 -&gt; turn off debug */
DECL|macro|SG_NEXT_CMD_LEN
mdefine_line|#define SG_NEXT_CMD_LEN 0x2283  /* override SCSI command length with given&n;&t;&t;   number on the next write() on this file descriptor */
multiline_comment|/* Defaults, commented if they differ from original sg driver */
DECL|macro|SG_DEFAULT_TIMEOUT
mdefine_line|#define SG_DEFAULT_TIMEOUT (60*HZ) /* HZ == &squot;jiffies in 1 second&squot; */
DECL|macro|SG_DEF_COMMAND_Q
mdefine_line|#define SG_DEF_COMMAND_Q 0     /* command queuing is always on when&n;&t;&t;&t;&t;  the new interface is used */
DECL|macro|SG_DEF_UNDERRUN_FLAG
mdefine_line|#define SG_DEF_UNDERRUN_FLAG 0
macro_line|#endif
eof
