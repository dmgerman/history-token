multiline_comment|/*&n; *&n; *&t;&t;&t;Linux MegaRAID device driver&n; *&n; * Copyright (c) 2003-2004  LSI Logic Corporation.&n; *&n; *&t;   This program is free software; you can redistribute it and/or&n; *&t;   modify it under the terms of the GNU General Public License&n; *&t;   as published by the Free Software Foundation; either version&n; *&t;   2 of the License, or (at your option) any later version.&n; *&n; * FILE&t;&t;: mega_common.h&n; *&n; * Libaray of common routine used by all low-level megaraid drivers&n; */
macro_line|#ifndef _MEGA_COMMON_H_
DECL|macro|_MEGA_COMMON_H_
mdefine_line|#define _MEGA_COMMON_H_
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;scsi/scsi.h&gt;
macro_line|#include &lt;scsi/scsi_cmnd.h&gt;
macro_line|#include &lt;scsi/scsi_device.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
DECL|macro|LSI_MAX_CHANNELS
mdefine_line|#define LSI_MAX_CHANNELS&t;&t;16
DECL|macro|LSI_MAX_LOGICAL_DRIVES_64LD
mdefine_line|#define LSI_MAX_LOGICAL_DRIVES_64LD&t;(64+1)
multiline_comment|/**&n; * scb_t - scsi command control block&n; * @param ccb&t;&t;: command control block for individual driver&n; * @param list&t;&t;: list of control blocks&n; * @param gp&t;&t;: general purpose field for LLDs&n; * @param sno&t;&t;: all SCBs have a serial number&n; * @param scp&t;&t;: associated scsi command&n; * @param state&t;&t;: current state of scb&n; * @param dma_dir&t;: direction of data transfer&n; * @param dma_type&t;: transfer with sg list, buffer, or no data transfer&n; * @param dev_channel&t;: actual channel on the device&n; * @param dev_target&t;: actual target on the device&n; * @param status&t;: completion status&n; *&n; * This is our central data structure to issue commands the each driver.&n; * Driver specific data structures are maintained in the ccb field.&n; * scb provides a field &squot;gp&squot;, which can be used by LLD for its own purposes&n; *&n; * dev_channel and dev_target must be initialized with the actual channel and&n; * target on the controller.&n; */
r_typedef
r_struct
(brace
DECL|member|ccb
id|caddr_t
id|ccb
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|gp
r_int
r_int
id|gp
suffix:semicolon
DECL|member|sno
r_int
r_int
id|sno
suffix:semicolon
DECL|member|scp
r_struct
id|scsi_cmnd
op_star
id|scp
suffix:semicolon
DECL|member|state
r_uint32
id|state
suffix:semicolon
DECL|member|dma_direction
r_uint32
id|dma_direction
suffix:semicolon
DECL|member|dma_type
r_uint32
id|dma_type
suffix:semicolon
DECL|member|dev_channel
r_uint16
id|dev_channel
suffix:semicolon
DECL|member|dev_target
r_uint16
id|dev_target
suffix:semicolon
DECL|member|status
r_uint32
id|status
suffix:semicolon
DECL|typedef|scb_t
)brace
id|scb_t
suffix:semicolon
multiline_comment|/*&n; * SCB states as it transitions from one state to another&n; */
DECL|macro|SCB_FREE
mdefine_line|#define SCB_FREE&t;0x0000&t;/* on the free list */
DECL|macro|SCB_ACTIVE
mdefine_line|#define SCB_ACTIVE&t;0x0001&t;/* off the free list */
DECL|macro|SCB_PENDQ
mdefine_line|#define SCB_PENDQ&t;0x0002&t;/* on the pending queue */
DECL|macro|SCB_ISSUED
mdefine_line|#define SCB_ISSUED&t;0x0004&t;/* issued - owner f/w */
DECL|macro|SCB_ABORT
mdefine_line|#define SCB_ABORT&t;0x0008&t;/* Got an abort for this one */
DECL|macro|SCB_RESET
mdefine_line|#define SCB_RESET&t;0x0010&t;/* Got a reset for this one */
multiline_comment|/*&n; * DMA types for scb&n; */
DECL|macro|MRAID_DMA_NONE
mdefine_line|#define MRAID_DMA_NONE&t;0x0000&t;/* no data transfer for this command */
DECL|macro|MRAID_DMA_WSG
mdefine_line|#define MRAID_DMA_WSG&t;0x0001&t;/* data transfer using a sg list */
DECL|macro|MRAID_DMA_WBUF
mdefine_line|#define MRAID_DMA_WBUF&t;0x0002&t;/* data transfer using a contiguous buffer */
multiline_comment|/**&n; * struct adapter_t - driver&squot;s initialization structure&n; * @param dpc_h&t;&t;&t;: tasklet handle&n; * @param pdev&t;&t;&t;: pci configuration pointer for kernel&n; * @param host&t;&t;&t;: pointer to host structure of mid-layer&n; * @param host_lock&t;&t;: pointer to appropriate lock&n; * @param lock&t;&t;&t;: synchronization lock for mid-layer and driver&n; * @param quiescent&t;&t;: driver is quiescent for now.&n; * @param outstanding_cmds&t;: number of commands pending in the driver&n; * @param kscb_list&t;&t;: pointer to the bulk of SCBs pointers for IO&n; * @param kscb_pool&t;&t;: pool of free scbs for IO&n; * @param kscb_pool_lock&t;: lock for pool of free scbs&n; * @param pend_list&t;&t;: pending commands list&n; * @param pend_list_lock&t;: exlusion lock for pending commands list&n; * @param completed_list&t;: list of completed commands&n; * @param completed_list_lock&t;: exclusion lock for list of completed commands&n; * @param sglen&t;&t;&t;: max sg elements supported&n; * @param device_ids&t;&t;: to convert kernel device addr to our devices.&n; * @param raid_device&t;&t;: raid adapter specific pointer&n; * @param max_channel&t;&t;: maximum channel number supported - inclusive&n; * @param max_target&t;&t;: max target supported - inclusive&n; * @param max_lun&t;&t;: max lun supported - inclusive&n; * @param unique_id&t;&t;: unique identifier for each adapter&n; * @param irq&t;&t;&t;: IRQ for this adapter&n; * @param ito&t;&t;&t;: internal timeout value, (-1) means no timeout&n; * @param ibuf&t;&t;&t;: buffer to issue internal commands&n; * @param ibuf_dma_h&t;&t;: dma handle for the above buffer&n; * @param uscb_list&t;&t;: SCB pointers for user cmds, common mgmt module&n; * @param uscb_pool&t;&t;: pool of SCBs for user commands&n; * @param uscb_pool_lock&t;: exclusion lock for these SCBs&n; * @param max_cmds&t;&t;: max outstanding commands&n; * @param fw_version&t;&t;: firmware version&n; * @param bios_version&t;&t;: bios version&n; * @param max_cdb_sz&t;&t;: biggest CDB size supported.&n; * @param ha&t;&t;&t;: is high availability present - clustering&n; * @param init_id&t;&t;: initiator ID, the default value should be 7&n; * @param max_sectors&t;&t;: max sectors per request&n; * @param cmd_per_lun&t;&t;: max outstanding commands per LUN&n; * @param being_detached&t;: set when unloading, no more mgmt calls&n; *&n; *&n; * mraid_setup_device_map() can be called anytime after the device map is&n; * available and MRAID_GET_DEVICE_MAP() can be called whenever the mapping is&n; * required, usually from LLD&squot;s queue entry point. The formar API sets up the&n; * MRAID_IS_LOGICAL(adapter_t *, struct scsi_cmnd *) to find out if the&n; * device in question is a logical drive.&n; *&n; * quiescent flag should be set by the driver if it is not accepting more&n; * commands&n; *&n; * NOTE: The fields of this structures are placed to minimize cache misses&n; */
singleline_comment|// amount of space required to store the bios and firmware version strings
DECL|macro|VERSION_SIZE
mdefine_line|#define VERSION_SIZE&t;16
r_typedef
r_struct
(brace
DECL|member|dpc_h
r_struct
id|tasklet_struct
id|dpc_h
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
DECL|member|host_lock
id|spinlock_t
op_star
id|host_lock
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|quiescent
r_uint8
id|quiescent
suffix:semicolon
DECL|member|outstanding_cmds
r_int
id|outstanding_cmds
suffix:semicolon
DECL|member|kscb_list
id|scb_t
op_star
id|kscb_list
suffix:semicolon
DECL|member|kscb_pool
r_struct
id|list_head
id|kscb_pool
suffix:semicolon
DECL|member|kscb_pool_lock
id|spinlock_t
id|kscb_pool_lock
suffix:semicolon
DECL|member|pend_list
r_struct
id|list_head
id|pend_list
suffix:semicolon
DECL|member|pend_list_lock
id|spinlock_t
id|pend_list_lock
suffix:semicolon
DECL|member|completed_list
r_struct
id|list_head
id|completed_list
suffix:semicolon
DECL|member|completed_list_lock
id|spinlock_t
id|completed_list_lock
suffix:semicolon
DECL|member|sglen
r_uint16
id|sglen
suffix:semicolon
DECL|member|device_ids
r_int
id|device_ids
(braket
id|LSI_MAX_CHANNELS
)braket
(braket
id|LSI_MAX_LOGICAL_DRIVES_64LD
)braket
suffix:semicolon
DECL|member|raid_device
id|caddr_t
id|raid_device
suffix:semicolon
DECL|member|max_channel
r_uint8
id|max_channel
suffix:semicolon
DECL|member|max_target
r_uint16
id|max_target
suffix:semicolon
DECL|member|max_lun
r_uint8
id|max_lun
suffix:semicolon
DECL|member|unique_id
r_uint32
id|unique_id
suffix:semicolon
DECL|member|irq
r_uint8
id|irq
suffix:semicolon
DECL|member|ito
r_uint8
id|ito
suffix:semicolon
DECL|member|ibuf
id|caddr_t
id|ibuf
suffix:semicolon
DECL|member|ibuf_dma_h
id|dma_addr_t
id|ibuf_dma_h
suffix:semicolon
DECL|member|uscb_list
id|scb_t
op_star
id|uscb_list
suffix:semicolon
DECL|member|uscb_pool
r_struct
id|list_head
id|uscb_pool
suffix:semicolon
DECL|member|uscb_pool_lock
id|spinlock_t
id|uscb_pool_lock
suffix:semicolon
DECL|member|max_cmds
r_int
id|max_cmds
suffix:semicolon
DECL|member|fw_version
r_uint8
id|fw_version
(braket
id|VERSION_SIZE
)braket
suffix:semicolon
DECL|member|bios_version
r_uint8
id|bios_version
(braket
id|VERSION_SIZE
)braket
suffix:semicolon
DECL|member|max_cdb_sz
r_uint8
id|max_cdb_sz
suffix:semicolon
DECL|member|ha
r_uint8
id|ha
suffix:semicolon
DECL|member|init_id
r_uint16
id|init_id
suffix:semicolon
DECL|member|max_sectors
r_uint16
id|max_sectors
suffix:semicolon
DECL|member|cmd_per_lun
r_uint16
id|cmd_per_lun
suffix:semicolon
DECL|member|being_detached
id|atomic_t
id|being_detached
suffix:semicolon
DECL|typedef|adapter_t
)brace
id|adapter_t
suffix:semicolon
DECL|macro|SCSI_FREE_LIST_LOCK
mdefine_line|#define SCSI_FREE_LIST_LOCK(adapter)&t;(&amp;adapter-&gt;kscb_pool_lock)
DECL|macro|USER_FREE_LIST_LOCK
mdefine_line|#define USER_FREE_LIST_LOCK(adapter)&t;(&amp;adapter-&gt;uscb_pool_lock)
DECL|macro|PENDING_LIST_LOCK
mdefine_line|#define PENDING_LIST_LOCK(adapter)&t;(&amp;adapter-&gt;pend_list_lock)
DECL|macro|COMPLETED_LIST_LOCK
mdefine_line|#define COMPLETED_LIST_LOCK(adapter)&t;(&amp;adapter-&gt;completed_list_lock)
singleline_comment|// conversion from scsi command
DECL|macro|SCP2HOST
mdefine_line|#define SCP2HOST(scp)&t;&t;&t;(scp)-&gt;device-&gt;host&t;
singleline_comment|// to host
DECL|macro|SCP2HOSTDATA
mdefine_line|#define SCP2HOSTDATA(scp)&t;&t;SCP2HOST(scp)-&gt;hostdata&t;
singleline_comment|// to soft state
DECL|macro|SCP2CHANNEL
mdefine_line|#define SCP2CHANNEL(scp)&t;&t;(scp)-&gt;device-&gt;channel&t;
singleline_comment|// to channel
DECL|macro|SCP2TARGET
mdefine_line|#define SCP2TARGET(scp)&t;&t;&t;(scp)-&gt;device-&gt;id&t;
singleline_comment|// to target
DECL|macro|SCP2LUN
mdefine_line|#define SCP2LUN(scp)&t;&t;&t;(scp)-&gt;device-&gt;lun&t;
singleline_comment|// to LUN
singleline_comment|// generic macro to convert scsi command and host to controller&squot;s soft state
DECL|macro|SCSIHOST2ADAP
mdefine_line|#define SCSIHOST2ADAP(host)&t;(((caddr_t *)(host-&gt;hostdata))[0])
DECL|macro|SCP2ADAPTER
mdefine_line|#define SCP2ADAPTER(scp)&t;(adapter_t *)SCSIHOST2ADAP(SCP2HOST(scp))
multiline_comment|/**&n; * MRAID_GET_DEVICE_MAP - device ids&n; * @param adp&t;&t;- Adapter&squot;s soft state&n; * @param scp&t;&t;- mid-layer scsi command pointer&n; * @param p_chan&t;- physical channel on the controller&n; * @param target&t;- target id of the device or logical drive number&n; * @param islogical&t;- set if the command is for the logical drive&n; *&n; * Macro to retrieve information about device class, logical or physical and&n; * the corresponding physical channel and target or logical drive number&n; **/
DECL|macro|MRAID_IS_LOGICAL
mdefine_line|#define MRAID_IS_LOGICAL(adp, scp)&t;&bslash;&n;&t;(SCP2CHANNEL(scp) == (adp)-&gt;max_channel) ? 1 : 0
DECL|macro|MRAID_IS_LOGICAL_SDEV
mdefine_line|#define MRAID_IS_LOGICAL_SDEV(adp, sdev)&t;&bslash;&n;&t;(sdev-&gt;channel == (adp)-&gt;max_channel) ? 1 : 0
DECL|macro|MRAID_GET_DEVICE_MAP
mdefine_line|#define MRAID_GET_DEVICE_MAP(adp, scp, p_chan, target, islogical)&t;&bslash;&n;&t;/*&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * Is the request coming for the virtual channel&t;&t;&bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;islogical = MRAID_IS_LOGICAL(adp, scp);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/*&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; * Get an index into our table of drive ids mapping&t;&t;&bslash;&n;&t; */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (islogical) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;p_chan = 0xFF;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;target =&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;(adp)-&gt;device_ids[(adp)-&gt;max_channel][SCP2TARGET(scp)];&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;p_chan = ((adp)-&gt;device_ids[SCP2CHANNEL(scp)]&t;&t;&bslash;&n;&t;&t;&t;&t;&t;[SCP2TARGET(scp)] &gt;&gt; 8) &amp; 0xFF;&t;&bslash;&n;&t;&t;target = ((adp)-&gt;device_ids[SCP2CHANNEL(scp)]&t;&t;&bslash;&n;&t;&t;&t;&t;&t;[SCP2TARGET(scp)] &amp; 0xFF);&t;&bslash;&n;&t;}
multiline_comment|/*&n; * ### Helper routines ###&n; */
DECL|macro|LSI_DBGLVL
mdefine_line|#define LSI_DBGLVL mraid_debug_level&t;
singleline_comment|// each LLD must define a global
singleline_comment|// mraid_debug_level
macro_line|#ifdef DEBUG
macro_line|#if defined (_ASSERT_PANIC)
DECL|macro|ASSERT_ACTION
mdefine_line|#define ASSERT_ACTION&t;panic
macro_line|#else
DECL|macro|ASSERT_ACTION
mdefine_line|#define ASSERT_ACTION&t;printk
macro_line|#endif
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expression)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!(expression)) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ASSERT_ACTION(&quot;assertion failed:(%s), file: %s, line: %d:%s&bslash;n&quot;,&t;&bslash;&n;&t;&t;&t;#expression, __FILE__, __LINE__, __FUNCTION__);&t;&bslash;&n;&t;}
macro_line|#else
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expression)
macro_line|#endif
multiline_comment|/*&n; * struct mraid_pci_blk - structure holds DMA memory block info&n; * @param vaddr&t;&t;: virtual address to a memory block&n; * @param dma_addr&t;: DMA handle to a memory block&n; *&n; * This structure is filled up for the caller. It is the responsibilty of the&n; * caller to allocate this array big enough to store addresses for all&n; * requested elements&n; */
DECL|struct|mraid_pci_blk
r_struct
id|mraid_pci_blk
(brace
DECL|member|vaddr
id|caddr_t
id|vaddr
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif 
singleline_comment|// _MEGA_COMMON_H_
singleline_comment|// vim: set ts=8 sw=8 tw=78:
eof
