macro_line|#ifndef _GDTH_H
DECL|macro|_GDTH_H
mdefine_line|#define _GDTH_H
multiline_comment|/*&n; * Header file for the GDT ISA/EISA/PCI Disk Array Controller driver for Linux&n; * &n; * gdth.h Copyright (C) 1995-01 ICP vortex Computersysteme GmbH, Achim Leubner&n; * See gdth.c for further informations and &n; * below for supported controller types&n; *&n; * &lt;achim@vortex.de&gt;&n; *&n; * $Id: gdth.h,v 1.44 2001/08/21 11:19:05 achim Exp $&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
multiline_comment|/* defines, macros */
multiline_comment|/* driver version */
DECL|macro|GDTH_VERSION_STR
mdefine_line|#define GDTH_VERSION_STR        &quot;2.03&quot;
DECL|macro|GDTH_VERSION
mdefine_line|#define GDTH_VERSION            2
DECL|macro|GDTH_SUBVERSION
mdefine_line|#define GDTH_SUBVERSION         3
multiline_comment|/* protocol version */
DECL|macro|PROTOCOL_VERSION
mdefine_line|#define PROTOCOL_VERSION        1
multiline_comment|/* OEM IDs */
DECL|macro|OEM_ID_ICP
mdefine_line|#define OEM_ID_ICP&t;0x941c
DECL|macro|OEM_ID_INTEL
mdefine_line|#define OEM_ID_INTEL&t;0x8000
multiline_comment|/* controller classes */
DECL|macro|GDT_ISA
mdefine_line|#define GDT_ISA         0x01                    /* ISA controller */
DECL|macro|GDT_EISA
mdefine_line|#define GDT_EISA        0x02                    /* EISA controller */
DECL|macro|GDT_PCI
mdefine_line|#define GDT_PCI         0x03                    /* PCI controller */
DECL|macro|GDT_PCINEW
mdefine_line|#define GDT_PCINEW      0x04                    /* new PCI controller */
DECL|macro|GDT_PCIMPR
mdefine_line|#define GDT_PCIMPR      0x05                    /* PCI MPR controller */
multiline_comment|/* GDT_EISA, controller subtypes EISA */
DECL|macro|GDT3_ID
mdefine_line|#define GDT3_ID         0x0130941c              /* GDT3000/3020 */
DECL|macro|GDT3A_ID
mdefine_line|#define GDT3A_ID        0x0230941c              /* GDT3000A/3020A/3050A */
DECL|macro|GDT3B_ID
mdefine_line|#define GDT3B_ID        0x0330941c              /* GDT3000B/3010A */
multiline_comment|/* GDT_ISA */
DECL|macro|GDT2_ID
mdefine_line|#define GDT2_ID         0x0120941c              /* GDT2000/2020 */
multiline_comment|/* vendor ID, device IDs (PCI) */
multiline_comment|/* these defines should already exist in &lt;linux/pci.h&gt; */
macro_line|#ifndef PCI_VENDOR_ID_VORTEX
DECL|macro|PCI_VENDOR_ID_VORTEX
mdefine_line|#define PCI_VENDOR_ID_VORTEX            0x1119  /* PCI controller vendor ID */
macro_line|#endif
macro_line|#ifndef PCI_VENDOR_ID_INTEL
DECL|macro|PCI_VENDOR_ID_INTEL
mdefine_line|#define PCI_VENDOR_ID_INTEL             0x8086  
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDT60x0
multiline_comment|/* GDT_PCI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT60x0
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT60x0    0       /* GDT6000/6020/6050 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6000B
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6000B   1       /* GDT6000B/6010 */
multiline_comment|/* GDT_PCINEW */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x10
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x10    2       /* GDT6110/6510 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x20
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x20    3       /* GDT6120/6520 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6530
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6530    4       /* GDT6530 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6550
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6550    5       /* GDT6550 */
multiline_comment|/* GDT_PCINEW, wide/ultra SCSI controllers */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17    6       /* GDT6117/6517 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27    7       /* GDT6127/6527 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537    8       /* GDT6537 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557    9       /* GDT6557/6557-ECC */
multiline_comment|/* GDT_PCINEW, wide SCSI controllers */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x15
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x15    10      /* GDT6115/6515 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x25
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x25    11      /* GDT6125/6525 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6535
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6535    12      /* GDT6535 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6555
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6555    13      /* GDT6555/6555-ECC */
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDT6x17RP
multiline_comment|/* GDT_MPR, RP series, wide/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RP  0x100   /* GDT6117RP/GDT6517RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RP  0x101   /* GDT6127RP/GDT6527RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RP  0x102   /* GDT6537RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RP  0x103   /* GDT6557RP */
multiline_comment|/* GDT_MPR, RP series, narrow/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RP  0x104   /* GDT6111RP/GDT6511RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RP  0x105   /* GDT6121RP/GDT6521RP */
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDT6x17RD
multiline_comment|/* GDT_MPR, RD series, wide/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RD  0x110   /* GDT6117RD/GDT6517RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RD  0x111   /* GDT6127RD/GDT6527RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RD  0x112   /* GDT6537RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RD  0x113   /* GDT6557RD */
multiline_comment|/* GDT_MPR, RD series, narrow/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RD  0x114   /* GDT6111RD/GDT6511RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RD  0x115   /* GDT6121RD/GDT6521RD */
multiline_comment|/* GDT_MPR, RD series, wide/ultra2 SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x18RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x18RD  0x118   /* GDT6118RD/GDT6518RD/&n;                                                   GDT6618RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x28RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x28RD  0x119   /* GDT6128RD/GDT6528RD/&n;                                                   GDT6628RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x38RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x38RD  0x11A   /* GDT6538RD/GDT6638RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x58RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x58RD  0x11B   /* GDT6558RD/GDT6658RD */
multiline_comment|/* GDT_MPR, RN series (64-bit PCI), wide/ultra2 SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT7x18RN
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT7x18RN  0x168   /* GDT7118RN/GDT7518RN/&n;                                                   GDT7618RN */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT7x28RN
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT7x28RN  0x169   /* GDT7128RN/GDT7528RN/&n;                                                   GDT7628RN */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT7x38RN
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT7x38RN  0x16A   /* GDT7538RN/GDT7638RN */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT7x58RN
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT7x58RN  0x16B   /* GDT7558RN/GDT7658RN */
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDT6x19RD
multiline_comment|/* GDT_MPR, RD series, Fibre Channel */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x19RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x19RD  0x210   /* GDT6519RD/GDT6619RD */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x29RD
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x29RD  0x211   /* GDT6529RD/GDT6629RD */
multiline_comment|/* GDT_MPR, RN series (64-bit PCI), Fibre Channel */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT7x19RN
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT7x19RN  0x260   /* GDT7519RN/GDT7619RN */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT7x29RN
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT7x29RN  0x261   /* GDT7529RN/GDT7629RN */
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDTMAXRP
multiline_comment|/* GDT_MPR, last device ID */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDTMAXRP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDTMAXRP   0x2ff   
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDTNEWRX
multiline_comment|/* new GDT Rx Controller */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDTNEWRX
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDTNEWRX&t;0x300
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_INTEL_SRC
multiline_comment|/* Intel Storage RAID Controller */
DECL|macro|PCI_DEVICE_ID_INTEL_SRC
mdefine_line|#define PCI_DEVICE_ID_INTEL_SRC&t;&t;0x600
macro_line|#endif
multiline_comment|/* limits */
DECL|macro|GDTH_SCRATCH
mdefine_line|#define GDTH_SCRATCH    PAGE_SIZE               /* 4KB scratch buffer */
DECL|macro|GDTH_SCRATCH_ORD
mdefine_line|#define GDTH_SCRATCH_ORD 0                      /* order 0 means 1 page */
DECL|macro|GDTH_MAXCMDS
mdefine_line|#define GDTH_MAXCMDS    124
DECL|macro|GDTH_MAXC_P_L
mdefine_line|#define GDTH_MAXC_P_L   16                      /* max. cmds per lun */
DECL|macro|GDTH_MAX_RAW
mdefine_line|#define GDTH_MAX_RAW    2                       /* max. cmds per raw device */
DECL|macro|MAXOFFSETS
mdefine_line|#define MAXOFFSETS      128
DECL|macro|MAXHA
mdefine_line|#define MAXHA           16
DECL|macro|MAXID
mdefine_line|#define MAXID           127
DECL|macro|MAXLUN
mdefine_line|#define MAXLUN          8
DECL|macro|MAXBUS
mdefine_line|#define MAXBUS          6
DECL|macro|MAX_HDRIVES
mdefine_line|#define MAX_HDRIVES     100                     /* max. host drive count */
DECL|macro|MAX_LDRIVES
mdefine_line|#define MAX_LDRIVES     255                     /* max. log. drive count */
DECL|macro|MAX_EVENTS
mdefine_line|#define MAX_EVENTS      100                     /* event buffer count */
DECL|macro|MAX_RES_ARGS
mdefine_line|#define MAX_RES_ARGS    40                      /* device reservation, &n;                                                   must be a multiple of 4 */
DECL|macro|MAXCYLS
mdefine_line|#define MAXCYLS         1024
DECL|macro|HEADS
mdefine_line|#define HEADS           64
DECL|macro|SECS
mdefine_line|#define SECS            32                      /* mapping 64*32 */
DECL|macro|MEDHEADS
mdefine_line|#define MEDHEADS        127
DECL|macro|MEDSECS
mdefine_line|#define MEDSECS         63                      /* mapping 127*63 */
DECL|macro|BIGHEADS
mdefine_line|#define BIGHEADS        255
DECL|macro|BIGSECS
mdefine_line|#define BIGSECS         63                      /* mapping 255*63 */
multiline_comment|/* special command ptr. */
DECL|macro|UNUSED_CMND
mdefine_line|#define UNUSED_CMND     ((Scsi_Cmnd *)-1)
DECL|macro|INTERNAL_CMND
mdefine_line|#define INTERNAL_CMND   ((Scsi_Cmnd *)-2)
DECL|macro|SCREEN_CMND
mdefine_line|#define SCREEN_CMND     ((Scsi_Cmnd *)-3)
DECL|macro|SPECIAL_SCP
mdefine_line|#define SPECIAL_SCP(p)  (p==UNUSED_CMND || p==INTERNAL_CMND || p==SCREEN_CMND)
multiline_comment|/* controller services */
DECL|macro|SCSIRAWSERVICE
mdefine_line|#define SCSIRAWSERVICE  3
DECL|macro|CACHESERVICE
mdefine_line|#define CACHESERVICE    9
DECL|macro|SCREENSERVICE
mdefine_line|#define SCREENSERVICE   11
multiline_comment|/* screenservice defines */
DECL|macro|MSG_INV_HANDLE
mdefine_line|#define MSG_INV_HANDLE  -1                      /* special message handle */
DECL|macro|MSGLEN
mdefine_line|#define MSGLEN          16                      /* size of message text */
DECL|macro|MSG_SIZE
mdefine_line|#define MSG_SIZE        34                      /* size of message structure */
DECL|macro|MSG_REQUEST
mdefine_line|#define MSG_REQUEST     0                       /* async. event: message */
multiline_comment|/* cacheservice defines */
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE     0x200                   /* always 512 bytes per sec. */
multiline_comment|/* DPMEM constants */
DECL|macro|DPMEM_MAGIC
mdefine_line|#define DPMEM_MAGIC     0xC0FFEE11
DECL|macro|IC_HEADER_BYTES
mdefine_line|#define IC_HEADER_BYTES 48
DECL|macro|IC_QUEUE_BYTES
mdefine_line|#define IC_QUEUE_BYTES  4
DECL|macro|DPMEM_COMMAND_OFFSET
mdefine_line|#define DPMEM_COMMAND_OFFSET    IC_HEADER_BYTES+IC_QUEUE_BYTES*MAXOFFSETS
multiline_comment|/* cluster_type constants */
DECL|macro|CLUSTER_DRIVE
mdefine_line|#define CLUSTER_DRIVE         1
DECL|macro|CLUSTER_MOUNTED
mdefine_line|#define CLUSTER_MOUNTED       2
DECL|macro|CLUSTER_RESERVED
mdefine_line|#define CLUSTER_RESERVED      4
DECL|macro|CLUSTER_RESERVE_STATE
mdefine_line|#define CLUSTER_RESERVE_STATE (CLUSTER_DRIVE|CLUSTER_MOUNTED|CLUSTER_RESERVED)
multiline_comment|/* commands for all services, cache service */
DECL|macro|GDT_INIT
mdefine_line|#define GDT_INIT        0                       /* service initialization */
DECL|macro|GDT_READ
mdefine_line|#define GDT_READ        1                       /* read command */
DECL|macro|GDT_WRITE
mdefine_line|#define GDT_WRITE       2                       /* write command */
DECL|macro|GDT_INFO
mdefine_line|#define GDT_INFO        3                       /* information about devices */
DECL|macro|GDT_FLUSH
mdefine_line|#define GDT_FLUSH       4                       /* flush dirty cache buffers */
DECL|macro|GDT_IOCTL
mdefine_line|#define GDT_IOCTL       5                       /* ioctl command */
DECL|macro|GDT_DEVTYPE
mdefine_line|#define GDT_DEVTYPE     9                       /* additional information */
DECL|macro|GDT_MOUNT
mdefine_line|#define GDT_MOUNT       10                      /* mount cache device */
DECL|macro|GDT_UNMOUNT
mdefine_line|#define GDT_UNMOUNT     11                      /* unmount cache device */
DECL|macro|GDT_SET_FEAT
mdefine_line|#define GDT_SET_FEAT    12                      /* set feat. (scatter/gather) */
DECL|macro|GDT_GET_FEAT
mdefine_line|#define GDT_GET_FEAT    13                      /* get features */
DECL|macro|GDT_WRITE_THR
mdefine_line|#define GDT_WRITE_THR   16                      /* write through */
DECL|macro|GDT_READ_THR
mdefine_line|#define GDT_READ_THR    17                      /* read through */
DECL|macro|GDT_EXT_INFO
mdefine_line|#define GDT_EXT_INFO    18                      /* extended info */
DECL|macro|GDT_RESET
mdefine_line|#define GDT_RESET       19                      /* controller reset */
DECL|macro|GDT_RESERVE_DRV
mdefine_line|#define GDT_RESERVE_DRV 20                      /* reserve host drive */
DECL|macro|GDT_RELEASE_DRV
mdefine_line|#define GDT_RELEASE_DRV 21                      /* release host drive */
DECL|macro|GDT_CLUST_INFO
mdefine_line|#define GDT_CLUST_INFO  22                      /* cluster info */
DECL|macro|GDT_RW_ATTRIBS
mdefine_line|#define GDT_RW_ATTRIBS  23                      /* R/W attribs (write thru,..)*/
DECL|macro|GDT_CLUST_RESET
mdefine_line|#define GDT_CLUST_RESET 24                      /* releases the cluster drives*/
DECL|macro|GDT_FREEZE_IO
mdefine_line|#define GDT_FREEZE_IO   25                      /* freezes all IOs */
DECL|macro|GDT_UNFREEZE_IO
mdefine_line|#define GDT_UNFREEZE_IO 26                      /* unfreezes all IOs */
multiline_comment|/* raw service commands */
DECL|macro|GDT_RESERVE
mdefine_line|#define GDT_RESERVE     14                      /* reserve dev. to raw serv. */
DECL|macro|GDT_RELEASE
mdefine_line|#define GDT_RELEASE     15                      /* release device */
DECL|macro|GDT_RESERVE_ALL
mdefine_line|#define GDT_RESERVE_ALL 16                      /* reserve all devices */
DECL|macro|GDT_RELEASE_ALL
mdefine_line|#define GDT_RELEASE_ALL 17                      /* release all devices */
DECL|macro|GDT_RESET_BUS
mdefine_line|#define GDT_RESET_BUS   18                      /* reset bus */
DECL|macro|GDT_SCAN_START
mdefine_line|#define GDT_SCAN_START  19                      /* start device scan */
DECL|macro|GDT_SCAN_END
mdefine_line|#define GDT_SCAN_END    20                      /* stop device scan */  
multiline_comment|/* screen service commands */
DECL|macro|GDT_REALTIME
mdefine_line|#define GDT_REALTIME    3                       /* realtime clock to screens. */
multiline_comment|/* IOCTL command defines */
DECL|macro|SCSI_DR_INFO
mdefine_line|#define SCSI_DR_INFO    0x00                    /* SCSI drive info */                   
DECL|macro|SCSI_CHAN_CNT
mdefine_line|#define SCSI_CHAN_CNT   0x05                    /* SCSI channel count */   
DECL|macro|SCSI_DR_LIST
mdefine_line|#define SCSI_DR_LIST    0x06                    /* SCSI drive list */
DECL|macro|SCSI_DEF_CNT
mdefine_line|#define SCSI_DEF_CNT    0x15                    /* grown/primary defects */
DECL|macro|DSK_STATISTICS
mdefine_line|#define DSK_STATISTICS  0x4b                    /* SCSI disk statistics */
DECL|macro|IOCHAN_DESC
mdefine_line|#define IOCHAN_DESC     0x5d                    /* description of IO channel */
DECL|macro|IOCHAN_RAW_DESC
mdefine_line|#define IOCHAN_RAW_DESC 0x5e                    /* description of raw IO chn. */
DECL|macro|L_CTRL_PATTERN
mdefine_line|#define L_CTRL_PATTERN  0x20000000L             /* SCSI IOCTL mask */
DECL|macro|ARRAY_INFO
mdefine_line|#define ARRAY_INFO      0x12                    /* array drive info */
DECL|macro|ARRAY_DRV_LIST
mdefine_line|#define ARRAY_DRV_LIST  0x0f                    /* array drive list */
DECL|macro|ARRAY_DRV_LIST2
mdefine_line|#define ARRAY_DRV_LIST2 0x34                    /* array drive list (new) */
DECL|macro|LA_CTRL_PATTERN
mdefine_line|#define LA_CTRL_PATTERN 0x10000000L             /* array IOCTL mask */
DECL|macro|CACHE_DRV_CNT
mdefine_line|#define CACHE_DRV_CNT   0x01                    /* cache drive count */
DECL|macro|CACHE_DRV_LIST
mdefine_line|#define CACHE_DRV_LIST  0x02                    /* cache drive list */
DECL|macro|CACHE_INFO
mdefine_line|#define CACHE_INFO      0x04                    /* cache info */
DECL|macro|CACHE_CONFIG
mdefine_line|#define CACHE_CONFIG    0x05                    /* cache configuration */
DECL|macro|CACHE_DRV_INFO
mdefine_line|#define CACHE_DRV_INFO  0x07                    /* cache drive info */
DECL|macro|BOARD_FEATURES
mdefine_line|#define BOARD_FEATURES  0x15                    /* controller features */
DECL|macro|BOARD_INFO
mdefine_line|#define BOARD_INFO      0x28                    /* controller info */
DECL|macro|HOST_GET
mdefine_line|#define HOST_GET        0x10001L                /* get host drive list */
DECL|macro|IO_CHANNEL
mdefine_line|#define IO_CHANNEL      0x00020000L             /* default IO channel */
DECL|macro|INVALID_CHANNEL
mdefine_line|#define INVALID_CHANNEL 0x0000ffffL             /* invalid channel */
multiline_comment|/* service errors */
DECL|macro|S_OK
mdefine_line|#define S_OK            1                       /* no error */
DECL|macro|S_GENERR
mdefine_line|#define S_GENERR        6                       /* general error */
DECL|macro|S_BSY
mdefine_line|#define S_BSY           7                       /* controller busy */
DECL|macro|S_CACHE_UNKNOWN
mdefine_line|#define S_CACHE_UNKNOWN 12                      /* cache serv.: drive unknown */
DECL|macro|S_RAW_SCSI
mdefine_line|#define S_RAW_SCSI      12                      /* raw serv.: target error */
DECL|macro|S_RAW_ILL
mdefine_line|#define S_RAW_ILL       0xff                    /* raw serv.: illegal */
multiline_comment|/* timeout values */
DECL|macro|INIT_RETRIES
mdefine_line|#define INIT_RETRIES    100000                  /* 100000 * 1ms = 100s */
DECL|macro|INIT_TIMEOUT
mdefine_line|#define INIT_TIMEOUT    100000                  /* 100000 * 1ms = 100s */
DECL|macro|POLL_TIMEOUT
mdefine_line|#define POLL_TIMEOUT    10000                   /* 10000 * 1ms = 10s */
multiline_comment|/* priorities */
DECL|macro|DEFAULT_PRI
mdefine_line|#define DEFAULT_PRI     0x20
DECL|macro|IOCTL_PRI
mdefine_line|#define IOCTL_PRI       0x10
DECL|macro|HIGH_PRI
mdefine_line|#define HIGH_PRI        0x08
multiline_comment|/* data directions */
DECL|macro|GDTH_DATA_IN
mdefine_line|#define GDTH_DATA_IN    0x01000000L             /* data from target */
DECL|macro|GDTH_DATA_OUT
mdefine_line|#define GDTH_DATA_OUT   0x00000000L             /* data to target */
multiline_comment|/* BMIC registers (EISA controllers) */
DECL|macro|ID0REG
mdefine_line|#define ID0REG          0x0c80                  /* board ID */
DECL|macro|EINTENABREG
mdefine_line|#define EINTENABREG     0x0c89                  /* interrupt enable */
DECL|macro|SEMA0REG
mdefine_line|#define SEMA0REG        0x0c8a                  /* command semaphore */
DECL|macro|SEMA1REG
mdefine_line|#define SEMA1REG        0x0c8b                  /* status semaphore */
DECL|macro|LDOORREG
mdefine_line|#define LDOORREG        0x0c8d                  /* local doorbell */
DECL|macro|EDENABREG
mdefine_line|#define EDENABREG       0x0c8e                  /* EISA system doorbell enab. */
DECL|macro|EDOORREG
mdefine_line|#define EDOORREG        0x0c8f                  /* EISA system doorbell */
DECL|macro|MAILBOXREG
mdefine_line|#define MAILBOXREG      0x0c90                  /* mailbox reg. (16 bytes) */
DECL|macro|EISAREG
mdefine_line|#define EISAREG         0x0cc0                  /* EISA configuration */
multiline_comment|/* other defines */
DECL|macro|LINUX_OS
mdefine_line|#define LINUX_OS        8                       /* used for cache optim. */
DECL|macro|SCATTER_GATHER
mdefine_line|#define SCATTER_GATHER  1                       /* s/g feature */
DECL|macro|GDTH_MAXSG
mdefine_line|#define GDTH_MAXSG      32                      /* max. s/g elements */
DECL|macro|SECS32
mdefine_line|#define SECS32          0x1f                    /* round capacity */
DECL|macro|BIOS_ID_OFFS
mdefine_line|#define BIOS_ID_OFFS    0x10                    /* offset contr-ID in ISABIOS */
DECL|macro|LOCALBOARD
mdefine_line|#define LOCALBOARD      0                       /* board node always 0 */
DECL|macro|ASYNCINDEX
mdefine_line|#define ASYNCINDEX      0                       /* cmd index async. event */
DECL|macro|SPEZINDEX
mdefine_line|#define SPEZINDEX       1                       /* cmd index unknown service */
DECL|macro|GDT_WR_THROUGH
mdefine_line|#define GDT_WR_THROUGH  0x100                   /* WRITE_THROUGH supported */
multiline_comment|/* typedefs */
DECL|typedef|ulong32
r_typedef
id|u32
id|ulong32
suffix:semicolon
DECL|macro|PACKED
mdefine_line|#define PACKED  __attribute__((packed))
multiline_comment|/* screenservice message */
r_typedef
r_struct
(brace
DECL|member|msg_handle
id|ulong32
id|msg_handle
suffix:semicolon
multiline_comment|/* message handle */
DECL|member|msg_len
id|ulong32
id|msg_len
suffix:semicolon
multiline_comment|/* size of message */
DECL|member|msg_alen
id|ulong32
id|msg_alen
suffix:semicolon
multiline_comment|/* answer length */
DECL|member|msg_answer
id|unchar
id|msg_answer
suffix:semicolon
multiline_comment|/* answer flag */
DECL|member|msg_ext
id|unchar
id|msg_ext
suffix:semicolon
multiline_comment|/* more messages */
DECL|member|msg_reserved
id|unchar
id|msg_reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|msg_text
r_char
id|msg_text
(braket
id|MSGLEN
op_plus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* the message text */
DECL|typedef|gdth_msg_str
)brace
id|PACKED
id|gdth_msg_str
suffix:semicolon
multiline_comment|/* IOCTL data structures */
multiline_comment|/* SCSI drive info */
r_typedef
r_struct
(brace
DECL|member|vendor
id|unchar
id|vendor
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* vendor string */
DECL|member|product
id|unchar
id|product
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* product string */
DECL|member|revision
id|unchar
id|revision
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* revision */
DECL|member|sy_rate
id|ulong32
id|sy_rate
suffix:semicolon
multiline_comment|/* current rate for sync. tr. */
DECL|member|sy_max_rate
id|ulong32
id|sy_max_rate
suffix:semicolon
multiline_comment|/* max. rate for sync. tr. */
DECL|member|no_ldrive
id|ulong32
id|no_ldrive
suffix:semicolon
multiline_comment|/* belongs to this log. drv.*/
DECL|member|blkcnt
id|ulong32
id|blkcnt
suffix:semicolon
multiline_comment|/* number of blocks */
DECL|member|blksize
id|ushort
id|blksize
suffix:semicolon
multiline_comment|/* size of block in bytes */
DECL|member|available
id|unchar
id|available
suffix:semicolon
multiline_comment|/* flag: access is available */
DECL|member|init
id|unchar
id|init
suffix:semicolon
multiline_comment|/* medium is initialized */
DECL|member|devtype
id|unchar
id|devtype
suffix:semicolon
multiline_comment|/* SCSI devicetype */
DECL|member|rm_medium
id|unchar
id|rm_medium
suffix:semicolon
multiline_comment|/* medium is removable */
DECL|member|wp_medium
id|unchar
id|wp_medium
suffix:semicolon
multiline_comment|/* medium is write protected */
DECL|member|ansi
id|unchar
id|ansi
suffix:semicolon
multiline_comment|/* SCSI I/II or III? */
DECL|member|protocol
id|unchar
id|protocol
suffix:semicolon
multiline_comment|/* same as ansi */
DECL|member|sync
id|unchar
id|sync
suffix:semicolon
multiline_comment|/* flag: sync. transfer enab. */
DECL|member|disc
id|unchar
id|disc
suffix:semicolon
multiline_comment|/* flag: disconnect enabled */
DECL|member|queueing
id|unchar
id|queueing
suffix:semicolon
multiline_comment|/* flag: command queing enab. */
DECL|member|cached
id|unchar
id|cached
suffix:semicolon
multiline_comment|/* flag: caching enabled */
DECL|member|target_id
id|unchar
id|target_id
suffix:semicolon
multiline_comment|/* target ID of device */
DECL|member|lun
id|unchar
id|lun
suffix:semicolon
multiline_comment|/* LUN id of device */
DECL|member|orphan
id|unchar
id|orphan
suffix:semicolon
multiline_comment|/* flag: drive fragment */
DECL|member|last_error
id|ulong32
id|last_error
suffix:semicolon
multiline_comment|/* sense key or drive state */
DECL|member|last_result
id|ulong32
id|last_result
suffix:semicolon
multiline_comment|/* result of last command */
DECL|member|check_errors
id|ulong32
id|check_errors
suffix:semicolon
multiline_comment|/* err. in last surface check */
DECL|member|percent
id|unchar
id|percent
suffix:semicolon
multiline_comment|/* progress for surface check */
DECL|member|last_check
id|unchar
id|last_check
suffix:semicolon
multiline_comment|/* IOCTRL operation */
DECL|member|res
id|unchar
id|res
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|flags
id|ulong32
id|flags
suffix:semicolon
multiline_comment|/* from 1.19/2.19: raw reserv.*/
DECL|member|multi_bus
id|unchar
id|multi_bus
suffix:semicolon
multiline_comment|/* multi bus dev? (fibre ch.) */
DECL|member|mb_status
id|unchar
id|mb_status
suffix:semicolon
multiline_comment|/* status: available? */
DECL|member|res2
id|unchar
id|res2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mb_alt_status
id|unchar
id|mb_alt_status
suffix:semicolon
multiline_comment|/* status on second bus */
DECL|member|mb_alt_bid
id|unchar
id|mb_alt_bid
suffix:semicolon
multiline_comment|/* number of second bus */
DECL|member|mb_alt_tid
id|unchar
id|mb_alt_tid
suffix:semicolon
multiline_comment|/* target id on second bus */
DECL|member|res3
id|unchar
id|res3
suffix:semicolon
DECL|member|fc_flag
id|unchar
id|fc_flag
suffix:semicolon
multiline_comment|/* from 1.22/2.22: info valid?*/
DECL|member|res4
id|unchar
id|res4
suffix:semicolon
DECL|member|fc_frame_size
id|ushort
id|fc_frame_size
suffix:semicolon
multiline_comment|/* frame size (bytes) */
DECL|member|wwn
r_char
id|wwn
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* world wide name */
DECL|typedef|gdth_diskinfo_str
)brace
id|PACKED
id|gdth_diskinfo_str
suffix:semicolon
multiline_comment|/* get SCSI channel count  */
r_typedef
r_struct
(brace
DECL|member|channel_no
id|ulong32
id|channel_no
suffix:semicolon
multiline_comment|/* number of channel */
DECL|member|drive_cnt
id|ulong32
id|drive_cnt
suffix:semicolon
multiline_comment|/* drive count */
DECL|member|siop_id
id|unchar
id|siop_id
suffix:semicolon
multiline_comment|/* SCSI processor ID */
DECL|member|siop_state
id|unchar
id|siop_state
suffix:semicolon
multiline_comment|/* SCSI processor state */
DECL|typedef|gdth_getch_str
)brace
id|PACKED
id|gdth_getch_str
suffix:semicolon
multiline_comment|/* get SCSI drive numbers */
r_typedef
r_struct
(brace
DECL|member|sc_no
id|ulong32
id|sc_no
suffix:semicolon
multiline_comment|/* SCSI channel */
DECL|member|sc_cnt
id|ulong32
id|sc_cnt
suffix:semicolon
multiline_comment|/* sc_list[] elements */
DECL|member|sc_list
id|ulong32
id|sc_list
(braket
id|MAXID
)braket
suffix:semicolon
multiline_comment|/* minor device numbers */
DECL|typedef|gdth_drlist_str
)brace
id|PACKED
id|gdth_drlist_str
suffix:semicolon
multiline_comment|/* get grown/primary defect count */
r_typedef
r_struct
(brace
DECL|member|sddc_type
id|unchar
id|sddc_type
suffix:semicolon
multiline_comment|/* 0x08: grown, 0x10: prim. */
DECL|member|sddc_format
id|unchar
id|sddc_format
suffix:semicolon
multiline_comment|/* list entry format */
DECL|member|sddc_len
id|unchar
id|sddc_len
suffix:semicolon
multiline_comment|/* list entry length */
DECL|member|sddc_res
id|unchar
id|sddc_res
suffix:semicolon
DECL|member|sddc_cnt
id|ulong32
id|sddc_cnt
suffix:semicolon
multiline_comment|/* entry count */
DECL|typedef|gdth_defcnt_str
)brace
id|PACKED
id|gdth_defcnt_str
suffix:semicolon
multiline_comment|/* disk statistics */
r_typedef
r_struct
(brace
DECL|member|bid
id|ulong32
id|bid
suffix:semicolon
multiline_comment|/* SCSI channel */
DECL|member|first
id|ulong32
id|first
suffix:semicolon
multiline_comment|/* first SCSI disk */
DECL|member|entries
id|ulong32
id|entries
suffix:semicolon
multiline_comment|/* number of elements */
DECL|member|count
id|ulong32
id|count
suffix:semicolon
multiline_comment|/* (R) number of init. el. */
DECL|member|mon_time
id|ulong32
id|mon_time
suffix:semicolon
multiline_comment|/* time stamp */
r_struct
(brace
DECL|member|tid
id|unchar
id|tid
suffix:semicolon
multiline_comment|/* target ID */
DECL|member|lun
id|unchar
id|lun
suffix:semicolon
multiline_comment|/* LUN */
DECL|member|res
id|unchar
id|res
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|blk_size
id|ulong32
id|blk_size
suffix:semicolon
multiline_comment|/* block size in bytes */
DECL|member|rd_count
id|ulong32
id|rd_count
suffix:semicolon
multiline_comment|/* bytes read */
DECL|member|wr_count
id|ulong32
id|wr_count
suffix:semicolon
multiline_comment|/* bytes written */
DECL|member|rd_blk_count
id|ulong32
id|rd_blk_count
suffix:semicolon
multiline_comment|/* blocks read */
DECL|member|wr_blk_count
id|ulong32
id|wr_blk_count
suffix:semicolon
multiline_comment|/* blocks written */
DECL|member|retries
id|ulong32
id|retries
suffix:semicolon
multiline_comment|/* retries */
DECL|member|reassigns
id|ulong32
id|reassigns
suffix:semicolon
multiline_comment|/* reassigns */
DECL|member|list
)brace
id|PACKED
id|list
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|gdth_dskstat_str
)brace
id|PACKED
id|gdth_dskstat_str
suffix:semicolon
multiline_comment|/* IO channel header */
r_typedef
r_struct
(brace
DECL|member|version
id|ulong32
id|version
suffix:semicolon
multiline_comment|/* version (-1UL: newest) */
DECL|member|list_entries
id|unchar
id|list_entries
suffix:semicolon
multiline_comment|/* list entry count */
DECL|member|first_chan
id|unchar
id|first_chan
suffix:semicolon
multiline_comment|/* first channel number */
DECL|member|last_chan
id|unchar
id|last_chan
suffix:semicolon
multiline_comment|/* last channel number */
DECL|member|chan_count
id|unchar
id|chan_count
suffix:semicolon
multiline_comment|/* (R) channel count */
DECL|member|list_offset
id|ulong32
id|list_offset
suffix:semicolon
multiline_comment|/* offset of list[0] */
DECL|typedef|gdth_iochan_header
)brace
id|PACKED
id|gdth_iochan_header
suffix:semicolon
multiline_comment|/* get IO channel description */
r_typedef
r_struct
(brace
DECL|member|hdr
id|gdth_iochan_header
id|hdr
suffix:semicolon
r_struct
(brace
DECL|member|address
id|ulong32
id|address
suffix:semicolon
multiline_comment|/* channel address */
DECL|member|type
id|unchar
id|type
suffix:semicolon
multiline_comment|/* type (SCSI, FCAL) */
DECL|member|local_no
id|unchar
id|local_no
suffix:semicolon
multiline_comment|/* local number */
DECL|member|features
id|ushort
id|features
suffix:semicolon
multiline_comment|/* channel features */
DECL|member|list
)brace
id|PACKED
id|list
(braket
id|MAXBUS
)braket
suffix:semicolon
DECL|typedef|gdth_iochan_str
)brace
id|PACKED
id|gdth_iochan_str
suffix:semicolon
multiline_comment|/* get raw IO channel description */
r_typedef
r_struct
(brace
DECL|member|hdr
id|gdth_iochan_header
id|hdr
suffix:semicolon
r_struct
(brace
DECL|member|proc_id
id|unchar
id|proc_id
suffix:semicolon
multiline_comment|/* processor id */
DECL|member|proc_defect
id|unchar
id|proc_defect
suffix:semicolon
multiline_comment|/* defect ? */
DECL|member|reserved
id|unchar
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|list
)brace
id|PACKED
id|list
(braket
id|MAXBUS
)braket
suffix:semicolon
DECL|typedef|gdth_raw_iochan_str
)brace
id|PACKED
id|gdth_raw_iochan_str
suffix:semicolon
multiline_comment|/* array drive component */
r_typedef
r_struct
(brace
DECL|member|al_controller
id|ulong32
id|al_controller
suffix:semicolon
multiline_comment|/* controller ID */
DECL|member|al_cache_drive
id|unchar
id|al_cache_drive
suffix:semicolon
multiline_comment|/* cache drive number */
DECL|member|al_status
id|unchar
id|al_status
suffix:semicolon
multiline_comment|/* cache drive state */
DECL|member|al_res
id|unchar
id|al_res
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|gdth_arraycomp_str
)brace
id|PACKED
id|gdth_arraycomp_str
suffix:semicolon
multiline_comment|/* array drive information */
r_typedef
r_struct
(brace
DECL|member|ai_type
id|unchar
id|ai_type
suffix:semicolon
multiline_comment|/* array type (RAID0,4,5) */
DECL|member|ai_cache_drive_cnt
id|unchar
id|ai_cache_drive_cnt
suffix:semicolon
multiline_comment|/* active cachedrives */
DECL|member|ai_state
id|unchar
id|ai_state
suffix:semicolon
multiline_comment|/* array drive state */
DECL|member|ai_master_cd
id|unchar
id|ai_master_cd
suffix:semicolon
multiline_comment|/* master cachedrive */
DECL|member|ai_master_controller
id|ulong32
id|ai_master_controller
suffix:semicolon
multiline_comment|/* ID of master controller */
DECL|member|ai_size
id|ulong32
id|ai_size
suffix:semicolon
multiline_comment|/* user capacity [sectors] */
DECL|member|ai_striping_size
id|ulong32
id|ai_striping_size
suffix:semicolon
multiline_comment|/* striping size [sectors] */
DECL|member|ai_secsize
id|ulong32
id|ai_secsize
suffix:semicolon
multiline_comment|/* sector size [bytes] */
DECL|member|ai_err_info
id|ulong32
id|ai_err_info
suffix:semicolon
multiline_comment|/* failed cache drive */
DECL|member|ai_name
id|unchar
id|ai_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* name of the array drive */
DECL|member|ai_controller_cnt
id|unchar
id|ai_controller_cnt
suffix:semicolon
multiline_comment|/* number of controllers */
DECL|member|ai_removable
id|unchar
id|ai_removable
suffix:semicolon
multiline_comment|/* flag: removable */
DECL|member|ai_write_protected
id|unchar
id|ai_write_protected
suffix:semicolon
multiline_comment|/* flag: write protected */
DECL|member|ai_devtype
id|unchar
id|ai_devtype
suffix:semicolon
multiline_comment|/* type: always direct access */
DECL|member|ai_drives
id|gdth_arraycomp_str
id|ai_drives
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* drive components: */
DECL|member|ai_drive_entries
id|unchar
id|ai_drive_entries
suffix:semicolon
multiline_comment|/* number of drive components */
DECL|member|ai_protected
id|unchar
id|ai_protected
suffix:semicolon
multiline_comment|/* protection flag */
DECL|member|ai_verify_state
id|unchar
id|ai_verify_state
suffix:semicolon
multiline_comment|/* state of a parity verify */
DECL|member|ai_ext_state
id|unchar
id|ai_ext_state
suffix:semicolon
multiline_comment|/* extended array drive state */
DECL|member|ai_expand_state
id|unchar
id|ai_expand_state
suffix:semicolon
multiline_comment|/* array expand state (&gt;=2.18)*/
DECL|member|ai_reserved
id|unchar
id|ai_reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|gdth_arrayinf_str
)brace
id|PACKED
id|gdth_arrayinf_str
suffix:semicolon
multiline_comment|/* get array drive list */
r_typedef
r_struct
(brace
DECL|member|controller_no
id|ulong32
id|controller_no
suffix:semicolon
multiline_comment|/* controller no. */
DECL|member|cd_handle
id|unchar
id|cd_handle
suffix:semicolon
multiline_comment|/* master cachedrive */
DECL|member|is_arrayd
id|unchar
id|is_arrayd
suffix:semicolon
multiline_comment|/* Flag: is array drive? */
DECL|member|is_master
id|unchar
id|is_master
suffix:semicolon
multiline_comment|/* Flag: is array master? */
DECL|member|is_parity
id|unchar
id|is_parity
suffix:semicolon
multiline_comment|/* Flag: is parity drive? */
DECL|member|is_hotfix
id|unchar
id|is_hotfix
suffix:semicolon
multiline_comment|/* Flag: is hotfix drive? */
DECL|member|res
id|unchar
id|res
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|gdth_alist_str
)brace
id|PACKED
id|gdth_alist_str
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|entries_avail
id|ulong32
id|entries_avail
suffix:semicolon
multiline_comment|/* allocated entries */
DECL|member|entries_init
id|ulong32
id|entries_init
suffix:semicolon
multiline_comment|/* returned entries */
DECL|member|first_entry
id|ulong32
id|first_entry
suffix:semicolon
multiline_comment|/* first entry number */
DECL|member|list_offset
id|ulong32
id|list_offset
suffix:semicolon
multiline_comment|/* offset of following list */
DECL|member|list
id|gdth_alist_str
id|list
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* list */
DECL|typedef|gdth_arcdl_str
)brace
id|PACKED
id|gdth_arcdl_str
suffix:semicolon
multiline_comment|/* cache info/config IOCTL */
r_typedef
r_struct
(brace
DECL|member|version
id|ulong32
id|version
suffix:semicolon
multiline_comment|/* firmware version */
DECL|member|state
id|ushort
id|state
suffix:semicolon
multiline_comment|/* cache state (on/off) */
DECL|member|strategy
id|ushort
id|strategy
suffix:semicolon
multiline_comment|/* cache strategy */
DECL|member|write_back
id|ushort
id|write_back
suffix:semicolon
multiline_comment|/* write back state (on/off) */
DECL|member|block_size
id|ushort
id|block_size
suffix:semicolon
multiline_comment|/* cache block size */
DECL|typedef|gdth_cpar_str
)brace
id|PACKED
id|gdth_cpar_str
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|csize
id|ulong32
id|csize
suffix:semicolon
multiline_comment|/* cache size */
DECL|member|read_cnt
id|ulong32
id|read_cnt
suffix:semicolon
multiline_comment|/* read/write counter */
DECL|member|write_cnt
id|ulong32
id|write_cnt
suffix:semicolon
DECL|member|tr_hits
id|ulong32
id|tr_hits
suffix:semicolon
multiline_comment|/* hits */
DECL|member|sec_hits
id|ulong32
id|sec_hits
suffix:semicolon
DECL|member|sec_miss
id|ulong32
id|sec_miss
suffix:semicolon
multiline_comment|/* misses */
DECL|typedef|gdth_cstat_str
)brace
id|PACKED
id|gdth_cstat_str
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cpar
id|gdth_cpar_str
id|cpar
suffix:semicolon
DECL|member|cstat
id|gdth_cstat_str
id|cstat
suffix:semicolon
DECL|typedef|gdth_cinfo_str
)brace
id|PACKED
id|gdth_cinfo_str
suffix:semicolon
multiline_comment|/* cache drive info */
r_typedef
r_struct
(brace
DECL|member|cd_name
id|unchar
id|cd_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* cache drive name */
DECL|member|cd_devtype
id|ulong32
id|cd_devtype
suffix:semicolon
multiline_comment|/* SCSI devicetype */
DECL|member|cd_ldcnt
id|ulong32
id|cd_ldcnt
suffix:semicolon
multiline_comment|/* number of log. drives */
DECL|member|cd_last_error
id|ulong32
id|cd_last_error
suffix:semicolon
multiline_comment|/* last error */
DECL|member|cd_initialized
id|unchar
id|cd_initialized
suffix:semicolon
multiline_comment|/* drive is initialized */
DECL|member|cd_removable
id|unchar
id|cd_removable
suffix:semicolon
multiline_comment|/* media is removable */
DECL|member|cd_write_protected
id|unchar
id|cd_write_protected
suffix:semicolon
multiline_comment|/* write protected */
DECL|member|cd_flags
id|unchar
id|cd_flags
suffix:semicolon
multiline_comment|/* Pool Hot Fix? */
DECL|member|ld_blkcnt
id|ulong32
id|ld_blkcnt
suffix:semicolon
multiline_comment|/* number of blocks */
DECL|member|ld_blksize
id|ulong32
id|ld_blksize
suffix:semicolon
multiline_comment|/* blocksize */
DECL|member|ld_dcnt
id|ulong32
id|ld_dcnt
suffix:semicolon
multiline_comment|/* number of disks */
DECL|member|ld_slave
id|ulong32
id|ld_slave
suffix:semicolon
multiline_comment|/* log. drive index */
DECL|member|ld_dtype
id|ulong32
id|ld_dtype
suffix:semicolon
multiline_comment|/* type of logical drive */
DECL|member|ld_last_error
id|ulong32
id|ld_last_error
suffix:semicolon
multiline_comment|/* last error */
DECL|member|ld_name
id|unchar
id|ld_name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* log. drive name */
DECL|member|ld_error
id|unchar
id|ld_error
suffix:semicolon
multiline_comment|/* error */
DECL|typedef|gdth_cdrinfo_str
)brace
id|PACKED
id|gdth_cdrinfo_str
suffix:semicolon
multiline_comment|/* board features */
r_typedef
r_struct
(brace
DECL|member|chaining
id|unchar
id|chaining
suffix:semicolon
multiline_comment|/* Chaining supported */
DECL|member|striping
id|unchar
id|striping
suffix:semicolon
multiline_comment|/* Striping (RAID-0) supp. */
DECL|member|mirroring
id|unchar
id|mirroring
suffix:semicolon
multiline_comment|/* Mirroring (RAID-1) supp. */
DECL|member|raid
id|unchar
id|raid
suffix:semicolon
multiline_comment|/* RAID-4/5/10 supported */
DECL|typedef|gdth_bfeat_str
)brace
id|PACKED
id|gdth_bfeat_str
suffix:semicolon
multiline_comment|/* board info IOCTL */
r_typedef
r_struct
(brace
DECL|member|ser_no
id|ulong32
id|ser_no
suffix:semicolon
multiline_comment|/* serial no. */
DECL|member|oem_id
id|unchar
id|oem_id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* OEM ID */
DECL|member|ep_flags
id|ushort
id|ep_flags
suffix:semicolon
multiline_comment|/* eprom flags */
DECL|member|proc_id
id|ulong32
id|proc_id
suffix:semicolon
multiline_comment|/* processor ID */
DECL|member|memsize
id|ulong32
id|memsize
suffix:semicolon
multiline_comment|/* memory size (bytes) */
DECL|member|mem_banks
id|unchar
id|mem_banks
suffix:semicolon
multiline_comment|/* memory banks */
DECL|member|chan_type
id|unchar
id|chan_type
suffix:semicolon
multiline_comment|/* channel type */
DECL|member|chan_count
id|unchar
id|chan_count
suffix:semicolon
multiline_comment|/* channel count */
DECL|member|rdongle_pres
id|unchar
id|rdongle_pres
suffix:semicolon
multiline_comment|/* dongle present? */
DECL|member|epr_fw_ver
id|ulong32
id|epr_fw_ver
suffix:semicolon
multiline_comment|/* (eprom) firmware version */
DECL|member|upd_fw_ver
id|ulong32
id|upd_fw_ver
suffix:semicolon
multiline_comment|/* (update) firmware version */
DECL|member|upd_revision
id|ulong32
id|upd_revision
suffix:semicolon
multiline_comment|/* update revision */
DECL|member|type_string
r_char
id|type_string
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* controller name */
DECL|member|raid_string
r_char
id|raid_string
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* RAID firmware name */
DECL|member|update_pres
id|unchar
id|update_pres
suffix:semicolon
multiline_comment|/* update present? */
DECL|member|xor_pres
id|unchar
id|xor_pres
suffix:semicolon
multiline_comment|/* XOR engine present? */
DECL|member|prom_type
id|unchar
id|prom_type
suffix:semicolon
multiline_comment|/* ROM type (eprom/flash) */
DECL|member|prom_count
id|unchar
id|prom_count
suffix:semicolon
multiline_comment|/* number of ROM devices */
DECL|member|dup_pres
id|ulong32
id|dup_pres
suffix:semicolon
multiline_comment|/* duplexing module present? */
DECL|member|chan_pres
id|ulong32
id|chan_pres
suffix:semicolon
multiline_comment|/* number of expansion chn. */
DECL|member|mem_pres
id|ulong32
id|mem_pres
suffix:semicolon
multiline_comment|/* memory expansion inst. ? */
DECL|member|ft_bus_system
id|unchar
id|ft_bus_system
suffix:semicolon
multiline_comment|/* fault bus supported? */
DECL|member|subtype_valid
id|unchar
id|subtype_valid
suffix:semicolon
multiline_comment|/* board_subtype valid? */
DECL|member|board_subtype
id|unchar
id|board_subtype
suffix:semicolon
multiline_comment|/* subtype/hardware level */
DECL|member|ramparity_pres
id|unchar
id|ramparity_pres
suffix:semicolon
multiline_comment|/* RAM parity check hardware? */
DECL|typedef|gdth_binfo_str
)brace
id|PACKED
id|gdth_binfo_str
suffix:semicolon
multiline_comment|/* get host drive info */
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* host drive name */
DECL|member|size
id|ulong32
id|size
suffix:semicolon
multiline_comment|/* size (sectors) */
DECL|member|host_drive
id|unchar
id|host_drive
suffix:semicolon
multiline_comment|/* host drive number */
DECL|member|log_drive
id|unchar
id|log_drive
suffix:semicolon
multiline_comment|/* log. drive (master) */
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|rw_attribs
id|unchar
id|rw_attribs
suffix:semicolon
multiline_comment|/* r/w attribs */
DECL|member|start_sec
id|ulong32
id|start_sec
suffix:semicolon
multiline_comment|/* start sector */
DECL|typedef|gdth_hentry_str
)brace
id|PACKED
id|gdth_hentry_str
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|entries
id|ulong32
id|entries
suffix:semicolon
multiline_comment|/* entry count */
DECL|member|offset
id|ulong32
id|offset
suffix:semicolon
multiline_comment|/* offset of entries */
DECL|member|secs_p_head
id|unchar
id|secs_p_head
suffix:semicolon
multiline_comment|/* sectors/head */
DECL|member|heads_p_cyl
id|unchar
id|heads_p_cyl
suffix:semicolon
multiline_comment|/* heads/cylinder */
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|clust_drvtype
id|unchar
id|clust_drvtype
suffix:semicolon
multiline_comment|/* cluster drive type */
DECL|member|location
id|ulong32
id|location
suffix:semicolon
multiline_comment|/* controller number */
DECL|member|entry
id|gdth_hentry_str
id|entry
(braket
id|MAX_HDRIVES
)braket
suffix:semicolon
multiline_comment|/* entries */
DECL|typedef|gdth_hget_str
)brace
id|PACKED
id|gdth_hget_str
suffix:semicolon
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
id|Scsi_Cmnd
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
multiline_comment|/* DPRAM structures */
multiline_comment|/* interface area ISA/PCI */
r_typedef
r_struct
(brace
DECL|member|S_Cmd_Indx
id|unchar
id|S_Cmd_Indx
suffix:semicolon
multiline_comment|/* special command */
DECL|member|S_Status
id|unchar
r_volatile
id|S_Status
suffix:semicolon
multiline_comment|/* status special command */
DECL|member|reserved1
id|ushort
id|reserved1
suffix:semicolon
DECL|member|S_Info
id|ulong32
id|S_Info
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* add. info special command */
DECL|member|Sema0
id|unchar
r_volatile
id|Sema0
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|reserved2
id|unchar
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Cmd_Index
id|unchar
id|Cmd_Index
suffix:semicolon
multiline_comment|/* command number */
DECL|member|reserved3
id|unchar
id|reserved3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Status
id|ushort
r_volatile
id|Status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|Service
id|ushort
id|Service
suffix:semicolon
multiline_comment|/* service(for async.events) */
DECL|member|Info
id|ulong32
id|Info
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* additional info */
r_struct
(brace
DECL|member|offset
id|ushort
id|offset
suffix:semicolon
multiline_comment|/* command offs. in the DPRAM*/
DECL|member|serv_id
id|ushort
id|serv_id
suffix:semicolon
multiline_comment|/* service */
DECL|member|comm_queue
)brace
id|PACKED
id|comm_queue
(braket
id|MAXOFFSETS
)braket
suffix:semicolon
multiline_comment|/* command queue */
DECL|member|bios_reserved
id|ulong32
id|bios_reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|gdt_dpr_cmd
id|unchar
id|gdt_dpr_cmd
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* commands */
DECL|typedef|gdt_dpr_if
)brace
id|PACKED
id|gdt_dpr_if
suffix:semicolon
multiline_comment|/* SRAM structure PCI controllers */
r_typedef
r_struct
(brace
DECL|member|magic
id|ulong32
id|magic
suffix:semicolon
multiline_comment|/* controller ID from BIOS */
DECL|member|need_deinit
id|ushort
id|need_deinit
suffix:semicolon
multiline_comment|/* switch betw. BIOS/driver */
DECL|member|switch_support
id|unchar
id|switch_support
suffix:semicolon
multiline_comment|/* see need_deinit */
DECL|member|padding
id|unchar
id|padding
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|os_used
id|unchar
id|os_used
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OS code per service */
DECL|member|unused
id|unchar
id|unused
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|fw_magic
id|unchar
id|fw_magic
suffix:semicolon
multiline_comment|/* contr. ID from firmware */
DECL|typedef|gdt_pci_sram
)brace
id|PACKED
id|gdt_pci_sram
suffix:semicolon
multiline_comment|/* SRAM structure EISA controllers (but NOT GDT3000/3020) */
r_typedef
r_struct
(brace
DECL|member|os_used
id|unchar
id|os_used
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OS code per service */
DECL|member|need_deinit
id|ushort
id|need_deinit
suffix:semicolon
multiline_comment|/* switch betw. BIOS/driver */
DECL|member|switch_support
id|unchar
id|switch_support
suffix:semicolon
multiline_comment|/* see need_deinit */
DECL|member|padding
id|unchar
id|padding
suffix:semicolon
DECL|typedef|gdt_eisa_sram
)brace
id|PACKED
id|gdt_eisa_sram
suffix:semicolon
multiline_comment|/* DPRAM ISA controllers */
r_typedef
r_struct
(brace
r_union
(brace
r_struct
(brace
DECL|member|bios_used
id|unchar
id|bios_used
(braket
l_int|0x3c00
op_minus
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 15KB - 32Bytes BIOS */
DECL|member|magic
id|ulong32
id|magic
suffix:semicolon
multiline_comment|/* controller (EISA) ID */
DECL|member|need_deinit
id|ushort
id|need_deinit
suffix:semicolon
multiline_comment|/* switch betw. BIOS/driver */
DECL|member|switch_support
id|unchar
id|switch_support
suffix:semicolon
multiline_comment|/* see need_deinit */
DECL|member|padding
id|unchar
id|padding
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|os_used
id|unchar
id|os_used
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OS code per service */
DECL|member|dp_sram
)brace
id|PACKED
id|dp_sram
suffix:semicolon
DECL|member|bios_area
id|unchar
id|bios_area
(braket
l_int|0x4000
)braket
suffix:semicolon
multiline_comment|/* 16KB reserved for BIOS */
DECL|member|bu
)brace
id|bu
suffix:semicolon
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0x3000
)braket
suffix:semicolon
multiline_comment|/* 12KB for interface */
DECL|member|u
)brace
id|u
suffix:semicolon
r_struct
(brace
DECL|member|memlock
id|unchar
id|memlock
suffix:semicolon
multiline_comment|/* write protection DPRAM */
DECL|member|event
id|unchar
id|event
suffix:semicolon
multiline_comment|/* release event */
DECL|member|irqen
id|unchar
id|irqen
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|irqdel
id|unchar
id|irqdel
suffix:semicolon
multiline_comment|/* acknowledge board int. */
DECL|member|Sema1
id|unchar
r_volatile
id|Sema1
suffix:semicolon
multiline_comment|/* status semaphore */
DECL|member|rq
id|unchar
id|rq
suffix:semicolon
multiline_comment|/* IRQ/DRQ configuration */
DECL|member|io
)brace
id|PACKED
id|io
suffix:semicolon
DECL|typedef|gdt2_dpram_str
)brace
id|PACKED
id|gdt2_dpram_str
suffix:semicolon
multiline_comment|/* DPRAM PCI controllers */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0xff0
op_minus
r_sizeof
(paren
id|gdt_pci_sram
)paren
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|gdt6sr
id|gdt_pci_sram
id|gdt6sr
suffix:semicolon
multiline_comment|/* SRAM structure */
r_struct
(brace
DECL|member|unused0
id|unchar
id|unused0
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|Sema1
id|unchar
r_volatile
id|Sema1
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|unused1
id|unchar
id|unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irqen
id|unchar
id|irqen
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|unused2
id|unchar
id|unused2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|event
id|unchar
id|event
suffix:semicolon
multiline_comment|/* release event */
DECL|member|unused3
id|unchar
id|unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irqdel
id|unchar
id|irqdel
suffix:semicolon
multiline_comment|/* acknowledge board int. */
DECL|member|unused4
id|unchar
id|unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|io
)brace
id|PACKED
id|io
suffix:semicolon
DECL|typedef|gdt6_dpram_str
)brace
id|PACKED
id|gdt6_dpram_str
suffix:semicolon
multiline_comment|/* PLX register structure (new PCI controllers) */
r_typedef
r_struct
(brace
DECL|member|cfg_reg
id|unchar
id|cfg_reg
suffix:semicolon
multiline_comment|/* DPRAM cfg.(2:below 1MB,0:anywhere)*/
DECL|member|unused1
id|unchar
id|unused1
(braket
l_int|0x3f
)braket
suffix:semicolon
DECL|member|sema0_reg
id|unchar
r_volatile
id|sema0_reg
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|sema1_reg
id|unchar
r_volatile
id|sema1_reg
suffix:semicolon
multiline_comment|/* status semaphore */
DECL|member|unused2
id|unchar
id|unused2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|status
id|ushort
r_volatile
id|status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|service
id|ushort
id|service
suffix:semicolon
multiline_comment|/* service */
DECL|member|info
id|ulong32
id|info
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* additional info */
DECL|member|unused3
id|unchar
id|unused3
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|ldoor_reg
id|unchar
id|ldoor_reg
suffix:semicolon
multiline_comment|/* PCI to local doorbell */
DECL|member|unused4
id|unchar
id|unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|edoor_reg
id|unchar
r_volatile
id|edoor_reg
suffix:semicolon
multiline_comment|/* local to PCI doorbell */
DECL|member|unused5
id|unchar
id|unused5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|control0
id|unchar
id|control0
suffix:semicolon
multiline_comment|/* control0 register(unused) */
DECL|member|control1
id|unchar
id|control1
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|unused6
id|unchar
id|unused6
(braket
l_int|0x16
)braket
suffix:semicolon
DECL|typedef|gdt6c_plx_regs
)brace
id|PACKED
id|gdt6c_plx_regs
suffix:semicolon
multiline_comment|/* DPRAM new PCI controllers */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0x4000
op_minus
r_sizeof
(paren
id|gdt_pci_sram
)paren
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|gdt6sr
id|gdt_pci_sram
id|gdt6sr
suffix:semicolon
multiline_comment|/* SRAM structure */
DECL|typedef|gdt6c_dpram_str
)brace
id|PACKED
id|gdt6c_dpram_str
suffix:semicolon
multiline_comment|/* i960 register structure (PCI MPR controllers) */
r_typedef
r_struct
(brace
DECL|member|unused1
id|unchar
id|unused1
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sema0_reg
id|unchar
r_volatile
id|sema0_reg
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|unused2
id|unchar
id|unused2
suffix:semicolon
DECL|member|sema1_reg
id|unchar
r_volatile
id|sema1_reg
suffix:semicolon
multiline_comment|/* status semaphore */
DECL|member|unused3
id|unchar
id|unused3
suffix:semicolon
DECL|member|status
id|ushort
r_volatile
id|status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|service
id|ushort
id|service
suffix:semicolon
multiline_comment|/* service */
DECL|member|info
id|ulong32
id|info
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* additional info */
DECL|member|ldoor_reg
id|unchar
id|ldoor_reg
suffix:semicolon
multiline_comment|/* PCI to local doorbell */
DECL|member|unused4
id|unchar
id|unused4
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|edoor_reg
id|unchar
r_volatile
id|edoor_reg
suffix:semicolon
multiline_comment|/* local to PCI doorbell */
DECL|member|unused5
id|unchar
id|unused5
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|edoor_en_reg
id|unchar
id|edoor_en_reg
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|unused6
id|unchar
id|unused6
(braket
l_int|27
)braket
suffix:semicolon
DECL|member|unused7
id|ulong32
id|unused7
(braket
l_int|939
)braket
suffix:semicolon
DECL|member|severity
id|ulong32
id|severity
suffix:semicolon
DECL|member|evt_str
r_char
id|evt_str
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* event string */
DECL|typedef|gdt6m_i960_regs
)brace
id|PACKED
id|gdt6m_i960_regs
suffix:semicolon
multiline_comment|/* DPRAM PCI MPR controllers */
r_typedef
r_struct
(brace
DECL|member|i960r
id|gdt6m_i960_regs
id|i960r
suffix:semicolon
multiline_comment|/* 4KB i960 registers */
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0x3000
op_minus
r_sizeof
(paren
id|gdt_pci_sram
)paren
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|gdt6sr
id|gdt_pci_sram
id|gdt6sr
suffix:semicolon
multiline_comment|/* SRAM structure */
DECL|typedef|gdt6m_dpram_str
)brace
id|PACKED
id|gdt6m_dpram_str
suffix:semicolon
multiline_comment|/* PCI resources */
r_typedef
r_struct
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= 0x02015C
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
macro_line|#endif
DECL|member|vendor_id
id|ushort
id|vendor_id
suffix:semicolon
multiline_comment|/* vendor (ICP, Intel, ..) */
DECL|member|device_id
id|ushort
id|device_id
suffix:semicolon
multiline_comment|/* device ID (0,..,9) */
DECL|member|subdevice_id
id|ushort
id|subdevice_id
suffix:semicolon
multiline_comment|/* sub device ID */
DECL|member|bus
id|unchar
id|bus
suffix:semicolon
multiline_comment|/* PCI bus */
DECL|member|device_fn
id|unchar
id|device_fn
suffix:semicolon
multiline_comment|/* PCI device/function no. */
DECL|member|dpmem
id|ulong
id|dpmem
suffix:semicolon
multiline_comment|/* DPRAM address */
DECL|member|io
id|ulong
id|io
suffix:semicolon
multiline_comment|/* IO address */
DECL|member|io_mm
id|ulong
id|io_mm
suffix:semicolon
multiline_comment|/* IO address mem. mapped */
DECL|member|irq
id|unchar
id|irq
suffix:semicolon
multiline_comment|/* IRQ */
DECL|typedef|gdth_pci_str
)brace
id|gdth_pci_str
suffix:semicolon
multiline_comment|/* controller information structure */
r_typedef
r_struct
(brace
DECL|member|oem_id
id|ushort
id|oem_id
suffix:semicolon
multiline_comment|/* OEM */
DECL|member|type
id|ushort
id|type
suffix:semicolon
multiline_comment|/* controller class */
DECL|member|raw_feat
id|ushort
id|raw_feat
suffix:semicolon
multiline_comment|/* feat. raw service (s/g,..) */
DECL|member|stype
id|ulong32
id|stype
suffix:semicolon
multiline_comment|/* subtype (PCI: device ID) */
DECL|member|subdevice_id
id|ushort
id|subdevice_id
suffix:semicolon
multiline_comment|/* sub device ID (PCI) */
DECL|member|fw_vers
id|ushort
id|fw_vers
suffix:semicolon
multiline_comment|/* firmware version */
DECL|member|cache_feat
id|ushort
id|cache_feat
suffix:semicolon
multiline_comment|/* feat. cache serv. (s/g,..) */
DECL|member|bmic
id|ushort
id|bmic
suffix:semicolon
multiline_comment|/* BMIC address (EISA) */
DECL|member|brd
r_void
op_star
id|brd
suffix:semicolon
multiline_comment|/* DPRAM address */
DECL|member|brd_phys
id|ulong32
id|brd_phys
suffix:semicolon
multiline_comment|/* slot number/BIOS address */
DECL|member|plx
id|gdt6c_plx_regs
op_star
id|plx
suffix:semicolon
multiline_comment|/* PLX regs (new PCI contr.) */
DECL|member|pccb
id|gdth_cmd_str
op_star
id|pccb
suffix:semicolon
multiline_comment|/* address command structure */
DECL|member|pscratch
r_char
op_star
id|pscratch
suffix:semicolon
multiline_comment|/* scratch (DMA) buffer */
DECL|member|scratch_busy
id|unchar
id|scratch_busy
suffix:semicolon
multiline_comment|/* in use? */
DECL|member|scan_mode
id|unchar
id|scan_mode
suffix:semicolon
multiline_comment|/* current scan mode */
DECL|member|irq
id|unchar
id|irq
suffix:semicolon
multiline_comment|/* IRQ */
DECL|member|drq
id|unchar
id|drq
suffix:semicolon
multiline_comment|/* DRQ (ISA controllers) */
DECL|member|status
id|ushort
id|status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|service
id|ushort
id|service
suffix:semicolon
multiline_comment|/* service/firmware ver./.. */
DECL|member|info
id|ulong32
id|info
suffix:semicolon
DECL|member|info2
id|ulong32
id|info2
suffix:semicolon
multiline_comment|/* additional info */
DECL|member|req_first
id|Scsi_Cmnd
op_star
id|req_first
suffix:semicolon
multiline_comment|/* top of request queue */
r_struct
(brace
DECL|member|present
id|unchar
id|present
suffix:semicolon
multiline_comment|/* Flag: host drive present? */
DECL|member|is_logdrv
id|unchar
id|is_logdrv
suffix:semicolon
multiline_comment|/* Flag: log. drive (master)? */
DECL|member|is_arraydrv
id|unchar
id|is_arraydrv
suffix:semicolon
multiline_comment|/* Flag: array drive? */
DECL|member|is_master
id|unchar
id|is_master
suffix:semicolon
multiline_comment|/* Flag: array drive master? */
DECL|member|is_parity
id|unchar
id|is_parity
suffix:semicolon
multiline_comment|/* Flag: parity drive? */
DECL|member|is_hotfix
id|unchar
id|is_hotfix
suffix:semicolon
multiline_comment|/* Flag: hotfix drive? */
DECL|member|master_no
id|unchar
id|master_no
suffix:semicolon
multiline_comment|/* number of master drive */
DECL|member|lock
id|unchar
id|lock
suffix:semicolon
multiline_comment|/* drive locked? (hot plug) */
DECL|member|heads
id|unchar
id|heads
suffix:semicolon
multiline_comment|/* mapping */
DECL|member|secs
id|unchar
id|secs
suffix:semicolon
DECL|member|devtype
id|ushort
id|devtype
suffix:semicolon
multiline_comment|/* further information */
DECL|member|size
id|ulong32
id|size
suffix:semicolon
multiline_comment|/* capacity */
DECL|member|ldr_no
id|unchar
id|ldr_no
suffix:semicolon
multiline_comment|/* log. drive no. */
DECL|member|rw_attribs
id|unchar
id|rw_attribs
suffix:semicolon
multiline_comment|/* r/w attributes */
DECL|member|cluster_type
id|unchar
id|cluster_type
suffix:semicolon
multiline_comment|/* cluster properties */
DECL|member|media_changed
id|unchar
id|media_changed
suffix:semicolon
multiline_comment|/* Flag:MOUNT/UNMOUNT occured */
DECL|member|start_sec
id|ulong32
id|start_sec
suffix:semicolon
multiline_comment|/* start sector */
DECL|member|hdr
)brace
id|hdr
(braket
id|MAX_LDRIVES
)braket
suffix:semicolon
multiline_comment|/* host drives */
r_struct
(brace
DECL|member|lock
id|unchar
id|lock
suffix:semicolon
multiline_comment|/* channel locked? (hot plug) */
DECL|member|pdev_cnt
id|unchar
id|pdev_cnt
suffix:semicolon
multiline_comment|/* physical device count */
DECL|member|local_no
id|unchar
id|local_no
suffix:semicolon
multiline_comment|/* local channel number */
DECL|member|io_cnt
id|unchar
id|io_cnt
(braket
id|MAXID
)braket
suffix:semicolon
multiline_comment|/* current IO count */
DECL|member|address
id|ulong32
id|address
suffix:semicolon
multiline_comment|/* channel address */
DECL|member|id_list
id|ulong32
id|id_list
(braket
id|MAXID
)braket
suffix:semicolon
multiline_comment|/* IDs of the phys. devices */
DECL|member|raw
)brace
id|raw
(braket
id|MAXBUS
)braket
suffix:semicolon
multiline_comment|/* SCSI channels */
r_struct
(brace
DECL|member|cmnd
id|Scsi_Cmnd
op_star
id|cmnd
suffix:semicolon
multiline_comment|/* pending request */
DECL|member|service
id|ushort
id|service
suffix:semicolon
multiline_comment|/* service */
DECL|member|cmd_tab
)brace
id|cmd_tab
(braket
id|GDTH_MAXCMDS
)braket
suffix:semicolon
multiline_comment|/* table of pend. requests */
DECL|member|bus_cnt
id|unchar
id|bus_cnt
suffix:semicolon
multiline_comment|/* SCSI bus count */
DECL|member|tid_cnt
id|unchar
id|tid_cnt
suffix:semicolon
multiline_comment|/* Target ID count */
DECL|member|bus_id
id|unchar
id|bus_id
(braket
id|MAXBUS
)braket
suffix:semicolon
multiline_comment|/* IOP IDs */
DECL|member|virt_bus
id|unchar
id|virt_bus
suffix:semicolon
multiline_comment|/* number of virtual bus */
DECL|member|more_proc
id|unchar
id|more_proc
suffix:semicolon
multiline_comment|/* more /proc info supported */
DECL|member|cmd_cnt
id|ushort
id|cmd_cnt
suffix:semicolon
multiline_comment|/* command count in DPRAM */
DECL|member|cmd_len
id|ushort
id|cmd_len
suffix:semicolon
multiline_comment|/* length of actual command */
DECL|member|cmd_offs_dpmem
id|ushort
id|cmd_offs_dpmem
suffix:semicolon
multiline_comment|/* actual offset in DPRAM */
DECL|member|ic_all_size
id|ushort
id|ic_all_size
suffix:semicolon
multiline_comment|/* sizeof DPRAM interf. area */
DECL|member|cpar
id|gdth_cpar_str
id|cpar
suffix:semicolon
multiline_comment|/* controller cache par. */
DECL|member|bfeat
id|gdth_bfeat_str
id|bfeat
suffix:semicolon
multiline_comment|/* controller features */
DECL|member|binfo
id|gdth_binfo_str
id|binfo
suffix:semicolon
multiline_comment|/* controller info */
DECL|member|dvr
id|gdth_evt_data
id|dvr
suffix:semicolon
multiline_comment|/* event structure */
macro_line|#if LINUX_VERSION_CODE &gt;= 0x02015F
DECL|member|smp_lock
id|spinlock_t
id|smp_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|gdth_ha_str
)brace
id|gdth_ha_str
suffix:semicolon
multiline_comment|/* structure for scsi_register(), SCSI bus != 0 */
r_typedef
r_struct
(brace
DECL|member|hanum
id|ushort
id|hanum
suffix:semicolon
DECL|member|busnum
id|ushort
id|busnum
suffix:semicolon
DECL|typedef|gdth_num_str
)brace
id|gdth_num_str
suffix:semicolon
multiline_comment|/* structure for scsi_register() */
r_typedef
r_struct
(brace
DECL|member|numext
id|gdth_num_str
id|numext
suffix:semicolon
multiline_comment|/* must be the first element */
DECL|member|haext
id|gdth_ha_str
id|haext
suffix:semicolon
DECL|member|cmdext
id|gdth_cmd_str
id|cmdext
suffix:semicolon
DECL|typedef|gdth_ext_str
)brace
id|gdth_ext_str
suffix:semicolon
multiline_comment|/* INQUIRY data format */
r_typedef
r_struct
(brace
DECL|member|type_qual
id|unchar
id|type_qual
suffix:semicolon
DECL|member|modif_rmb
id|unchar
id|modif_rmb
suffix:semicolon
DECL|member|version
id|unchar
id|version
suffix:semicolon
DECL|member|resp_aenc
id|unchar
id|resp_aenc
suffix:semicolon
DECL|member|add_length
id|unchar
id|add_length
suffix:semicolon
DECL|member|reserved1
id|unchar
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|unchar
id|reserved2
suffix:semicolon
DECL|member|misc
id|unchar
id|misc
suffix:semicolon
DECL|member|vendor
id|unchar
id|vendor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|product
id|unchar
id|product
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|revision
id|unchar
id|revision
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|gdth_inq_data
)brace
id|PACKED
id|gdth_inq_data
suffix:semicolon
multiline_comment|/* READ_CAPACITY data format */
r_typedef
r_struct
(brace
DECL|member|last_block_no
id|ulong32
id|last_block_no
suffix:semicolon
DECL|member|block_length
id|ulong32
id|block_length
suffix:semicolon
DECL|typedef|gdth_rdcap_data
)brace
id|PACKED
id|gdth_rdcap_data
suffix:semicolon
multiline_comment|/* REQUEST_SENSE data format */
r_typedef
r_struct
(brace
DECL|member|errorcode
id|unchar
id|errorcode
suffix:semicolon
DECL|member|segno
id|unchar
id|segno
suffix:semicolon
DECL|member|key
id|unchar
id|key
suffix:semicolon
DECL|member|info
id|ulong32
id|info
suffix:semicolon
DECL|member|add_length
id|unchar
id|add_length
suffix:semicolon
DECL|member|cmd_info
id|ulong32
id|cmd_info
suffix:semicolon
DECL|member|adsc
id|unchar
id|adsc
suffix:semicolon
DECL|member|adsq
id|unchar
id|adsq
suffix:semicolon
DECL|member|fruc
id|unchar
id|fruc
suffix:semicolon
DECL|member|key_spec
id|unchar
id|key_spec
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|gdth_sense_data
)brace
id|PACKED
id|gdth_sense_data
suffix:semicolon
multiline_comment|/* MODE_SENSE data format */
r_typedef
r_struct
(brace
r_struct
(brace
DECL|member|data_length
id|unchar
id|data_length
suffix:semicolon
DECL|member|med_type
id|unchar
id|med_type
suffix:semicolon
DECL|member|dev_par
id|unchar
id|dev_par
suffix:semicolon
DECL|member|bd_length
id|unchar
id|bd_length
suffix:semicolon
DECL|member|hd
)brace
id|PACKED
id|hd
suffix:semicolon
r_struct
(brace
DECL|member|dens_code
id|unchar
id|dens_code
suffix:semicolon
DECL|member|block_count
id|unchar
id|block_count
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|block_length
id|unchar
id|block_length
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|bd
)brace
id|PACKED
id|bd
suffix:semicolon
DECL|typedef|gdth_modep_data
)brace
id|PACKED
id|gdth_modep_data
suffix:semicolon
multiline_comment|/* stack frame */
r_typedef
r_struct
(brace
DECL|member|b
id|ulong
id|b
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* 32/64 bit compiler ! */
DECL|typedef|gdth_stackframe
)brace
id|PACKED
id|gdth_stackframe
suffix:semicolon
multiline_comment|/* function prototyping */
r_int
id|gdth_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|gdth_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|gdth_queuecommand
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
id|gdth_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x010346
r_int
id|gdth_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
id|reset_flags
)paren
suffix:semicolon
macro_line|#else
r_int
id|gdth_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#endif
r_const
r_char
op_star
id|gdth_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020322
r_int
id|gdth_bios_param
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|gdth_proc_info
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
r_int
id|gdth_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_int
id|gdth_eh_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_int
id|gdth_eh_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_int
id|gdth_eh_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
DECL|macro|GDTH
mdefine_line|#define GDTH { proc_name:       &quot;gdth&quot;,                          &bslash;&n;               proc_info:       gdth_proc_info,                  &bslash;&n;               name:            &quot;GDT SCSI Disk Array Controller&quot;,&bslash;&n;               detect:          gdth_detect,                     &bslash;&n;               release:         gdth_release,                    &bslash;&n;               info:            gdth_info,                       &bslash;&n;               command:         NULL,                            &bslash;&n;               queuecommand:    gdth_queuecommand,               &bslash;&n;               eh_abort_handler: gdth_eh_abort,                  &bslash;&n;               eh_device_reset_handler: gdth_eh_device_reset,    &bslash;&n;               eh_bus_reset_handler: gdth_eh_bus_reset,          &bslash;&n;               eh_host_reset_handler: gdth_eh_host_reset,        &bslash;&n;               abort:           gdth_abort,                      &bslash;&n;               reset:           gdth_reset,                      &bslash;&n;               bios_param:      gdth_bios_param,                 &bslash;&n;               can_queue:       GDTH_MAXCMDS,                    &bslash;&n;               this_id:         -1,                              &bslash;&n;               sg_tablesize:    GDTH_MAXSG,                      &bslash;&n;               cmd_per_lun:     GDTH_MAXC_P_L,                   &bslash;&n;               present:         0,                               &bslash;&n;               unchecked_isa_dma: 1,                             &bslash;&n;               use_clustering:  ENABLE_CLUSTERING,               &bslash;&n;               use_new_eh_code: 1       /* use new error code */ }    
macro_line|#elif LINUX_VERSION_CODE &gt;= 0x02015F
r_int
id|gdth_bios_param
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_gdth
suffix:semicolon
r_int
id|gdth_proc_info
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
r_int
id|gdth_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_int
id|gdth_eh_device_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_int
id|gdth_eh_bus_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
r_int
id|gdth_eh_host_reset
c_func
(paren
id|Scsi_Cmnd
op_star
id|scp
)paren
suffix:semicolon
DECL|macro|GDTH
mdefine_line|#define GDTH { proc_dir:        &amp;proc_scsi_gdth,                 &bslash;&n;               proc_info:       gdth_proc_info,                  &bslash;&n;               name:            &quot;GDT SCSI Disk Array Controller&quot;,&bslash;&n;               detect:          gdth_detect,                     &bslash;&n;               release:         gdth_release,                    &bslash;&n;               info:            gdth_info,                       &bslash;&n;               command:         NULL,                            &bslash;&n;               queuecommand:    gdth_queuecommand,               &bslash;&n;               eh_abort_handler: gdth_eh_abort,                  &bslash;&n;               eh_device_reset_handler: gdth_eh_device_reset,    &bslash;&n;               eh_bus_reset_handler: gdth_eh_bus_reset,          &bslash;&n;               eh_host_reset_handler: gdth_eh_host_reset,        &bslash;&n;               abort:           gdth_abort,                      &bslash;&n;               reset:           gdth_reset,                      &bslash;&n;               bios_param:      gdth_bios_param,                 &bslash;&n;               can_queue:       GDTH_MAXCMDS,                    &bslash;&n;               this_id:         -1,                              &bslash;&n;               sg_tablesize:    GDTH_MAXSG,                      &bslash;&n;               cmd_per_lun:     GDTH_MAXC_P_L,                   &bslash;&n;               present:         0,                               &bslash;&n;               unchecked_isa_dma: 1,                             &bslash;&n;               use_clustering:  ENABLE_CLUSTERING,               &bslash;&n;               use_new_eh_code: 1       /* use new error code */ }    
macro_line|#elif LINUX_VERSION_CODE &gt;= 0x010300
r_int
id|gdth_bios_param
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_gdth
suffix:semicolon
r_int
id|gdth_proc_info
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
DECL|macro|GDTH
mdefine_line|#define GDTH { NULL, NULL,                              &bslash;&n;                   &amp;proc_scsi_gdth,                     &bslash;&n;                   gdth_proc_info,                      &bslash;&n;                   &quot;GDT SCSI Disk Array Controller&quot;,    &bslash;&n;                   gdth_detect,                         &bslash;&n;                   gdth_release,                        &bslash;&n;                   gdth_info,                           &bslash;&n;                   NULL,                                &bslash;&n;                   gdth_queuecommand,                   &bslash;&n;                   gdth_abort,                          &bslash;&n;                   gdth_reset,                          &bslash;&n;                   NULL,                                &bslash;&n;                   gdth_bios_param,                     &bslash;&n;                   GDTH_MAXCMDS,                        &bslash;&n;                   -1,                                  &bslash;&n;                   GDTH_MAXSG,                          &bslash;&n;                   GDTH_MAXC_P_L,                       &bslash;&n;                   0,                                   &bslash;&n;                   1,                                   &bslash;&n;                   ENABLE_CLUSTERING}
macro_line|#else
r_int
id|gdth_bios_param
c_func
(paren
id|Disk
op_star
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
DECL|macro|GDTH
mdefine_line|#define GDTH { NULL, NULL,                              &bslash;&n;                   &quot;GDT SCSI Disk Array Controller&quot;,    &bslash;&n;                   gdth_detect,                         &bslash;&n;                   gdth_release,                        &bslash;&n;                   gdth_info,                           &bslash;&n;                   NULL,                                &bslash;&n;                   gdth_queuecommand,                   &bslash;&n;                   gdth_abort,                          &bslash;&n;                   gdth_reset,                          &bslash;&n;                   NULL,                                &bslash;&n;                   gdth_bios_param,                     &bslash;&n;                   GDTH_MAXCMDS,                        &bslash;&n;                   -1,                                  &bslash;&n;                   GDTH_MAXSG,                          &bslash;&n;                   GDTH_MAXC_P_L,                       &bslash;&n;                   0,                                   &bslash;&n;                   1,                                   &bslash;&n;                   ENABLE_CLUSTERING}
macro_line|#endif
macro_line|#endif
eof
