multiline_comment|/*&n; *&n; *&t;&t;&t;Linux MegaRAID device driver&n; *&n; * Copyright (c) 2003-2004  LSI Logic Corporation.&n; *&n; *&t;   This program is free software; you can redistribute it and/or&n; *&t;   modify it under the terms of the GNU General Public License&n; *&t;   as published by the Free Software Foundation; either version&n; *&t;   2 of the License, or (at your option) any later version.&n; *&n; * FILE&t;&t;: megaraid_mbox.h&n; */
macro_line|#ifndef _MEGARAID_H_
DECL|macro|_MEGARAID_H_
mdefine_line|#define _MEGARAID_H_
macro_line|#include &quot;mega_common.h&quot;
macro_line|#include &quot;mbox_defs.h&quot;
macro_line|#include &quot;megaraid_ioctl.h&quot;
DECL|macro|MEGARAID_VERSION
mdefine_line|#define MEGARAID_VERSION&t;&quot;2.20.4.5&quot;
DECL|macro|MEGARAID_EXT_VERSION
mdefine_line|#define MEGARAID_EXT_VERSION&t;&quot;(Release Date: Thu Feb 03 12:27:22 EST 2005)&quot;
multiline_comment|/*&n; * Define some PCI values here until they are put in the kernel&n; */
DECL|macro|PCI_DEVICE_ID_PERC4_DI_DISCOVERY
mdefine_line|#define PCI_DEVICE_ID_PERC4_DI_DISCOVERY&t;&t;0x000E
DECL|macro|PCI_SUBSYS_ID_PERC4_DI_DISCOVERY
mdefine_line|#define PCI_SUBSYS_ID_PERC4_DI_DISCOVERY&t;&t;0x0123
DECL|macro|PCI_DEVICE_ID_PERC4_SC
mdefine_line|#define PCI_DEVICE_ID_PERC4_SC&t;&t;&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_PERC4_SC
mdefine_line|#define PCI_SUBSYS_ID_PERC4_SC&t;&t;&t;&t;0x0520
DECL|macro|PCI_DEVICE_ID_PERC4_DC
mdefine_line|#define PCI_DEVICE_ID_PERC4_DC&t;&t;&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_PERC4_DC
mdefine_line|#define PCI_SUBSYS_ID_PERC4_DC&t;&t;&t;&t;0x0518
DECL|macro|PCI_DEVICE_ID_PERC4_QC
mdefine_line|#define PCI_DEVICE_ID_PERC4_QC&t;&t;&t;&t;0x0407
DECL|macro|PCI_SUBSYS_ID_PERC4_QC
mdefine_line|#define PCI_SUBSYS_ID_PERC4_QC&t;&t;&t;&t;0x0531
DECL|macro|PCI_DEVICE_ID_PERC4_DI_EVERGLADES
mdefine_line|#define PCI_DEVICE_ID_PERC4_DI_EVERGLADES&t;&t;0x000F
DECL|macro|PCI_SUBSYS_ID_PERC4_DI_EVERGLADES
mdefine_line|#define PCI_SUBSYS_ID_PERC4_DI_EVERGLADES&t;&t;0x014A
DECL|macro|PCI_DEVICE_ID_PERC4E_SI_BIGBEND
mdefine_line|#define PCI_DEVICE_ID_PERC4E_SI_BIGBEND&t;&t;&t;0x0013
DECL|macro|PCI_SUBSYS_ID_PERC4E_SI_BIGBEND
mdefine_line|#define PCI_SUBSYS_ID_PERC4E_SI_BIGBEND&t;&t;&t;0x016c
DECL|macro|PCI_DEVICE_ID_PERC4E_DI_KOBUK
mdefine_line|#define PCI_DEVICE_ID_PERC4E_DI_KOBUK&t;&t;&t;0x0013
DECL|macro|PCI_SUBSYS_ID_PERC4E_DI_KOBUK
mdefine_line|#define PCI_SUBSYS_ID_PERC4E_DI_KOBUK&t;&t;&t;0x016d
DECL|macro|PCI_DEVICE_ID_PERC4E_DI_CORVETTE
mdefine_line|#define PCI_DEVICE_ID_PERC4E_DI_CORVETTE&t;&t;0x0013
DECL|macro|PCI_SUBSYS_ID_PERC4E_DI_CORVETTE
mdefine_line|#define PCI_SUBSYS_ID_PERC4E_DI_CORVETTE&t;&t;0x016e
DECL|macro|PCI_DEVICE_ID_PERC4E_DI_EXPEDITION
mdefine_line|#define PCI_DEVICE_ID_PERC4E_DI_EXPEDITION&t;&t;0x0013
DECL|macro|PCI_SUBSYS_ID_PERC4E_DI_EXPEDITION
mdefine_line|#define PCI_SUBSYS_ID_PERC4E_DI_EXPEDITION&t;&t;0x016f
DECL|macro|PCI_DEVICE_ID_PERC4E_DI_GUADALUPE
mdefine_line|#define PCI_DEVICE_ID_PERC4E_DI_GUADALUPE&t;&t;0x0013
DECL|macro|PCI_SUBSYS_ID_PERC4E_DI_GUADALUPE
mdefine_line|#define PCI_SUBSYS_ID_PERC4E_DI_GUADALUPE&t;&t;0x0170
DECL|macro|PCI_DEVICE_ID_PERC4E_DC_320_2E
mdefine_line|#define PCI_DEVICE_ID_PERC4E_DC_320_2E&t;&t;&t;0x0408
DECL|macro|PCI_SUBSYS_ID_PERC4E_DC_320_2E
mdefine_line|#define PCI_SUBSYS_ID_PERC4E_DC_320_2E&t;&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_PERC4E_SC_320_1E
mdefine_line|#define PCI_DEVICE_ID_PERC4E_SC_320_1E&t;&t;&t;0x0408
DECL|macro|PCI_SUBSYS_ID_PERC4E_SC_320_1E
mdefine_line|#define PCI_SUBSYS_ID_PERC4E_SC_320_1E&t;&t;&t;0x0001
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_0
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_0&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_0
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_0&t;&t;0xA520
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_1
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_1&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_1
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_1&t;&t;0x0520
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_2
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_2&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_2
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_2&t;&t;0x0518
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_0x
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_0x&t;&t;0x0407
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_0x
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_0x&t;&t;0x0530
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_2x
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_2x&t;&t;0x0407
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_2x
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_2x&t;&t;0x0532
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_4x
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_4x&t;&t;0x0407
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_4x
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_4x&t;&t;0x0531
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_1E
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_1E&t;&t;0x0408
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_1E
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_1E&t;&t;0x0001
DECL|macro|PCI_DEVICE_ID_MEGARAID_SCSI_320_2E
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SCSI_320_2E&t;&t;0x0408
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SCSI_320_2E
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SCSI_320_2E&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_MEGARAID_I4_133_RAID
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_I4_133_RAID&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_MEGARAID_I4_133_RAID
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_I4_133_RAID&t;&t;0x0522
DECL|macro|PCI_DEVICE_ID_MEGARAID_SATA_150_4
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SATA_150_4&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SATA_150_4
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SATA_150_4&t;&t;0x4523
DECL|macro|PCI_DEVICE_ID_MEGARAID_SATA_150_6
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SATA_150_6&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SATA_150_6
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SATA_150_6&t;&t;0x0523
DECL|macro|PCI_DEVICE_ID_MEGARAID_SATA_300_4x
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SATA_300_4x&t;&t;0x0409
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SATA_300_4x
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SATA_300_4x&t;&t;0x3004
DECL|macro|PCI_DEVICE_ID_MEGARAID_SATA_300_8x
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_SATA_300_8x&t;&t;0x0409
DECL|macro|PCI_SUBSYS_ID_MEGARAID_SATA_300_8x
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_SATA_300_8x&t;&t;0x3008
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SRCU42X
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SRCU42X&t;&t;0x0407
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SRCU42X
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SRCU42X&t;&t;0x0532
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SRCS16
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SRCS16&t;&t;&t;0x1960
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SRCS16
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SRCS16&t;&t;&t;0x0523
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SRCU42E
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SRCU42E&t;&t;0x0408
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SRCU42E
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SRCU42E&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SRCZCRX
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SRCZCRX&t;&t;0x0407
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SRCZCRX
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SRCZCRX&t;&t;0x0530
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SRCS28X
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SRCS28X&t;&t;0x0409
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SRCS28X
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SRCS28X&t;&t;0x3008
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SROMBU42E_ALIEF
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SROMBU42E_ALIEF&t;0x0408
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SROMBU42E_ALIEF
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SROMBU42E_ALIEF&t;0x3431
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SROMBU42E_HARWICH
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SROMBU42E_HARWICH&t;0x0408
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SROMBU42E_HARWICH
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SROMBU42E_HARWICH&t;0x3499
DECL|macro|PCI_DEVICE_ID_INTEL_RAID_SRCU41L_LAKE_SHETEK
mdefine_line|#define PCI_DEVICE_ID_INTEL_RAID_SRCU41L_LAKE_SHETEK&t;0x1960
DECL|macro|PCI_SUBSYS_ID_INTEL_RAID_SRCU41L_LAKE_SHETEK
mdefine_line|#define PCI_SUBSYS_ID_INTEL_RAID_SRCU41L_LAKE_SHETEK&t;0x0520
DECL|macro|PCI_DEVICE_ID_FSC_MEGARAID_PCI_EXPRESS_ROMB
mdefine_line|#define PCI_DEVICE_ID_FSC_MEGARAID_PCI_EXPRESS_ROMB&t;0x0408
DECL|macro|PCI_SUBSYS_ID_FSC_MEGARAID_PCI_EXPRESS_ROMB
mdefine_line|#define PCI_SUBSYS_ID_FSC_MEGARAID_PCI_EXPRESS_ROMB&t;0x1065
DECL|macro|PCI_DEVICE_ID_MEGARAID_ACER_ROMB_2E
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_ACER_ROMB_2E&t;&t;0x0408
DECL|macro|PCI_SUBSYS_ID_MEGARAID_ACER_ROMB_2E
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_ACER_ROMB_2E&t;&t;0x004D
DECL|macro|PCI_SUBSYS_ID_PERC3_QC
mdefine_line|#define PCI_SUBSYS_ID_PERC3_QC&t;&t;&t;&t;0x0471
DECL|macro|PCI_SUBSYS_ID_PERC3_DC
mdefine_line|#define PCI_SUBSYS_ID_PERC3_DC&t;&t;&t;&t;0x0493
DECL|macro|PCI_SUBSYS_ID_PERC3_SC
mdefine_line|#define PCI_SUBSYS_ID_PERC3_SC&t;&t;&t;&t;0x0475
DECL|macro|PCI_DEVICE_ID_MEGARAID_NEC_ROMB_2E
mdefine_line|#define PCI_DEVICE_ID_MEGARAID_NEC_ROMB_2E&t;&t;0x0408
DECL|macro|PCI_SUBSYS_ID_MEGARAID_NEC_ROMB_2E
mdefine_line|#define PCI_SUBSYS_ID_MEGARAID_NEC_ROMB_2E&t;&t;0x8287
macro_line|#ifndef PCI_SUBSYS_ID_FSC
DECL|macro|PCI_SUBSYS_ID_FSC
mdefine_line|#define PCI_SUBSYS_ID_FSC&t;&t;&t;&t;0x1734
macro_line|#endif
DECL|macro|MBOX_MAX_SCSI_CMDS
mdefine_line|#define MBOX_MAX_SCSI_CMDS&t;128&t;
singleline_comment|// number of cmds reserved for kernel
DECL|macro|MBOX_MAX_USER_CMDS
mdefine_line|#define MBOX_MAX_USER_CMDS&t;32&t;
singleline_comment|// number of cmds for applications
DECL|macro|MBOX_DEF_CMD_PER_LUN
mdefine_line|#define MBOX_DEF_CMD_PER_LUN&t;64&t;
singleline_comment|// default commands per lun
DECL|macro|MBOX_DEFAULT_SG_SIZE
mdefine_line|#define MBOX_DEFAULT_SG_SIZE&t;26&t;
singleline_comment|// default sg size supported by all fw
DECL|macro|MBOX_MAX_SG_SIZE
mdefine_line|#define MBOX_MAX_SG_SIZE&t;32&t;
singleline_comment|// maximum scatter-gather list size
DECL|macro|MBOX_MAX_SECTORS
mdefine_line|#define MBOX_MAX_SECTORS&t;128&t;
singleline_comment|// maximum sectors per IO
DECL|macro|MBOX_TIMEOUT
mdefine_line|#define MBOX_TIMEOUT&t;&t;30&t;
singleline_comment|// timeout value for internal cmds
DECL|macro|MBOX_BUSY_WAIT
mdefine_line|#define MBOX_BUSY_WAIT&t;&t;10&t;
singleline_comment|// max usec to wait for busy mailbox
DECL|macro|MBOX_RESET_WAIT
mdefine_line|#define MBOX_RESET_WAIT&t;&t;180&t;
singleline_comment|// wait these many seconds in reset
DECL|macro|MBOX_RESET_EXT_WAIT
mdefine_line|#define MBOX_RESET_EXT_WAIT&t;120&t;
singleline_comment|// extended wait reset
multiline_comment|/*&n; * maximum transfer that can happen through the firmware commands issued&n; * internnaly from the driver.&n; */
DECL|macro|MBOX_IBUF_SIZE
mdefine_line|#define MBOX_IBUF_SIZE&t;&t;4096
multiline_comment|/**&n; * mbox_ccb_t - command control block specific to mailbox based controllers&n; * @raw_mbox&t;&t;: raw mailbox pointer&n; * @mbox&t;&t;: mailbox&n; * @mbox64&t;&t;: extended mailbox&n; * @mbox_dma_h&t;&t;: maibox dma address&n; * @sgl64&t;&t;: 64-bit scatter-gather list&n; * @sgl32&t;&t;: 32-bit scatter-gather list&n; * @sgl_dma_h&t;&t;: dma handle for the scatter-gather list&n; * @pthru&t;&t;: passthru structure&n; * @pthru_dma_h&t;&t;: dma handle for the passthru structure&n; * @epthru&t;&t;: extended passthru structure&n; * @epthru_dma_h&t;: dma handle for extended passthru structure&n; * @buf_dma_h&t;&t;: dma handle for buffers w/o sg list&n; *&n; * command control block specific to the mailbox based controllers&n; */
r_typedef
r_struct
(brace
DECL|member|raw_mbox
r_uint8
op_star
id|raw_mbox
suffix:semicolon
DECL|member|mbox
id|mbox_t
op_star
id|mbox
suffix:semicolon
DECL|member|mbox64
id|mbox64_t
op_star
id|mbox64
suffix:semicolon
DECL|member|mbox_dma_h
id|dma_addr_t
id|mbox_dma_h
suffix:semicolon
DECL|member|sgl64
id|mbox_sgl64
op_star
id|sgl64
suffix:semicolon
DECL|member|sgl32
id|mbox_sgl32
op_star
id|sgl32
suffix:semicolon
DECL|member|sgl_dma_h
id|dma_addr_t
id|sgl_dma_h
suffix:semicolon
DECL|member|pthru
id|mraid_passthru_t
op_star
id|pthru
suffix:semicolon
DECL|member|pthru_dma_h
id|dma_addr_t
id|pthru_dma_h
suffix:semicolon
DECL|member|epthru
id|mraid_epassthru_t
op_star
id|epthru
suffix:semicolon
DECL|member|epthru_dma_h
id|dma_addr_t
id|epthru_dma_h
suffix:semicolon
DECL|member|buf_dma_h
id|dma_addr_t
id|buf_dma_h
suffix:semicolon
DECL|typedef|mbox_ccb_t
)brace
id|mbox_ccb_t
suffix:semicolon
multiline_comment|/**&n; * mraid_device_t - adapter soft state structure for mailbox controllers&n; * @param una_mbox64&t;&t;: 64-bit mbox - unaligned&n; * @param una_mbox64_dma&t;: mbox dma addr - unaligned&n; * @param mbox&t;&t;&t;: 32-bit mbox - aligned&n; * @param mbox64&t;&t;: 64-bit mbox - aligned&n; * @param mbox_dma&t;&t;: mbox dma addr - aligned&n; * @param mailbox_lock&t;&t;: exclusion lock for the mailbox&n; * @param baseport&t;&t;: base port of hba memory&n; * @param baseaddr&t;&t;: mapped addr of hba memory&n; * @param mbox_pool&t;&t;: pool of mailboxes&n; * @param mbox_pool_handle&t;: handle for the mailbox pool memory&n; * @param epthru_pool&t;&t;: a pool for extended passthru commands&n; * @param epthru_pool_handle&t;: handle to the pool above&n; * @param sg_pool&t;&t;: pool of scatter-gather lists for this driver&n; * @param sg_pool_handle&t;: handle to the pool above&n; * @param ccb_list&t;&t;: list of our command control blocks&n; * @param uccb_list&t;&t;: list of cmd control blocks for mgmt module&n; * @param umbox64&t;&t;: array of mailbox for user commands (cmm)&n; * @param pdrv_state&t;&t;: array for state of each physical drive.&n; * @param last_disp&t;&t;: flag used to show device scanning&n; * @param hw_error&t;&t;: set if FW not responding&n; * @param fast_load&t;&t;: If set, skip physical device scanning&n; * @channel_class&t;&t;: channel class, RAID or SCSI&n; * @sysfs_sem&t;&t;&t;: semaphore to serialize access to sysfs res.&n; * @sysfs_uioc&t;&t;&t;: management packet to issue FW calls from sysfs&n; * @sysfs_mbox64&t;&t;: mailbox packet to issue FW calls from sysfs&n; * @sysfs_buffer&t;&t;: data buffer for FW commands issued from sysfs&n; * @sysfs_buffer_dma&t;&t;: DMA buffer for FW commands issued from sysfs&n; * @sysfs_wait_q&t;&t;: wait queue for sysfs operations&n; * @random_del_supported&t;: set if the random deletion is supported&n; * @curr_ldmap&t;&t;&t;: current LDID map&n; *&n; * Initialization structure for mailbox controllers: memory based and IO based&n; * All the fields in this structure are LLD specific and may be discovered at&n; * init() or start() time.&n; *&n; * NOTE: The fields of this structures are placed to minimize cache misses&n; */
DECL|macro|MAX_LD_EXTENDED64
mdefine_line|#define MAX_LD_EXTENDED64&t;64
r_typedef
r_struct
(brace
DECL|member|una_mbox64
id|mbox64_t
op_star
id|una_mbox64
suffix:semicolon
DECL|member|una_mbox64_dma
id|dma_addr_t
id|una_mbox64_dma
suffix:semicolon
DECL|member|mbox
id|mbox_t
op_star
id|mbox
suffix:semicolon
DECL|member|mbox64
id|mbox64_t
op_star
id|mbox64
suffix:semicolon
DECL|member|mbox_dma
id|dma_addr_t
id|mbox_dma
suffix:semicolon
DECL|member|mailbox_lock
id|spinlock_t
id|mailbox_lock
suffix:semicolon
DECL|member|baseport
r_int
r_int
id|baseport
suffix:semicolon
DECL|member|baseaddr
r_void
id|__iomem
op_star
id|baseaddr
suffix:semicolon
DECL|member|mbox_pool
r_struct
id|mraid_pci_blk
id|mbox_pool
(braket
id|MBOX_MAX_SCSI_CMDS
)braket
suffix:semicolon
DECL|member|mbox_pool_handle
r_struct
id|dma_pool
op_star
id|mbox_pool_handle
suffix:semicolon
DECL|member|epthru_pool
r_struct
id|mraid_pci_blk
id|epthru_pool
(braket
id|MBOX_MAX_SCSI_CMDS
)braket
suffix:semicolon
DECL|member|epthru_pool_handle
r_struct
id|dma_pool
op_star
id|epthru_pool_handle
suffix:semicolon
DECL|member|sg_pool
r_struct
id|mraid_pci_blk
id|sg_pool
(braket
id|MBOX_MAX_SCSI_CMDS
)braket
suffix:semicolon
DECL|member|sg_pool_handle
r_struct
id|dma_pool
op_star
id|sg_pool_handle
suffix:semicolon
DECL|member|ccb_list
id|mbox_ccb_t
id|ccb_list
(braket
id|MBOX_MAX_SCSI_CMDS
)braket
suffix:semicolon
DECL|member|uccb_list
id|mbox_ccb_t
id|uccb_list
(braket
id|MBOX_MAX_USER_CMDS
)braket
suffix:semicolon
DECL|member|umbox64
id|mbox64_t
id|umbox64
(braket
id|MBOX_MAX_USER_CMDS
)braket
suffix:semicolon
DECL|member|pdrv_state
r_uint8
id|pdrv_state
(braket
id|MBOX_MAX_PHYSICAL_DRIVES
)braket
suffix:semicolon
DECL|member|last_disp
r_uint32
id|last_disp
suffix:semicolon
DECL|member|hw_error
r_int
id|hw_error
suffix:semicolon
DECL|member|fast_load
r_int
id|fast_load
suffix:semicolon
DECL|member|channel_class
r_uint8
id|channel_class
suffix:semicolon
DECL|member|sysfs_sem
r_struct
id|semaphore
id|sysfs_sem
suffix:semicolon
DECL|member|sysfs_uioc
id|uioc_t
op_star
id|sysfs_uioc
suffix:semicolon
DECL|member|sysfs_mbox64
id|mbox64_t
op_star
id|sysfs_mbox64
suffix:semicolon
DECL|member|sysfs_buffer
id|caddr_t
id|sysfs_buffer
suffix:semicolon
DECL|member|sysfs_buffer_dma
id|dma_addr_t
id|sysfs_buffer_dma
suffix:semicolon
DECL|member|sysfs_wait_q
id|wait_queue_head_t
id|sysfs_wait_q
suffix:semicolon
DECL|member|random_del_supported
r_int
id|random_del_supported
suffix:semicolon
DECL|member|curr_ldmap
r_uint16
id|curr_ldmap
(braket
id|MAX_LD_EXTENDED64
)braket
suffix:semicolon
DECL|typedef|mraid_device_t
)brace
id|mraid_device_t
suffix:semicolon
singleline_comment|// route to raid device from adapter
DECL|macro|ADAP2RAIDDEV
mdefine_line|#define ADAP2RAIDDEV(adp)&t;((mraid_device_t *)((adp)-&gt;raid_device))
DECL|macro|MAILBOX_LOCK
mdefine_line|#define MAILBOX_LOCK(rdev)&t;(&amp;(rdev)-&gt;mailbox_lock)
singleline_comment|// Find out if this channel is a RAID or SCSI
DECL|macro|IS_RAID_CH
mdefine_line|#define IS_RAID_CH(rdev, ch)&t;(((rdev)-&gt;channel_class &gt;&gt; (ch)) &amp; 0x01)
DECL|macro|RDINDOOR
mdefine_line|#define RDINDOOR(rdev)&t;&t;readl((rdev)-&gt;baseaddr + 0x20)
DECL|macro|RDOUTDOOR
mdefine_line|#define RDOUTDOOR(rdev)&t;&t;readl((rdev)-&gt;baseaddr + 0x2C)
DECL|macro|WRINDOOR
mdefine_line|#define WRINDOOR(rdev, value)&t;writel(value, (rdev)-&gt;baseaddr + 0x20)
DECL|macro|WROUTDOOR
mdefine_line|#define WROUTDOOR(rdev, value)&t;writel(value, (rdev)-&gt;baseaddr + 0x2C)
macro_line|#endif 
singleline_comment|// _MEGARAID_H_
singleline_comment|// vim: set ts=8 sw=8 tw=78:
eof
