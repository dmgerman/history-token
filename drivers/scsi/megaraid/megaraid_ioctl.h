multiline_comment|/*&n; *&n; *&t;&t;&t;Linux MegaRAID device driver&n; *&n; * Copyright (c) 2003-2004  LSI Logic Corporation.&n; *&n; *&t;   This program is free software; you can redistribute it and/or&n; *&t;   modify it under the terms of the GNU General Public License&n; *&t;   as published by the Free Software Foundation; either version&n; *&t;   2 of the License, or (at your option) any later version.&n; *&n; * FILE&t;&t;: megaraid_ioctl.h&n; *&n; * Definitions to interface with user level applications&n; */
macro_line|#ifndef _MEGARAID_IOCTL_H_
DECL|macro|_MEGARAID_IOCTL_H_
mdefine_line|#define _MEGARAID_IOCTL_H_
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;mbox_defs.h&quot;
multiline_comment|/**&n; * con_log() - console log routine&n; * @param level&t;&t;: indicates the severity of the message.&n; * @fparam mt&t;&t;: format string&n; *&n; * con_log displays the error messages on the console based on the current&n; * debug level. Also it attaches the appropriate kernel severity level with&n; * the message.&n; *&n; *&n; * consolge messages debug levels&n; */
DECL|macro|CL_ANN
mdefine_line|#define&t;CL_ANN&t;&t;0&t;/* print unconditionally, announcements */
DECL|macro|CL_DLEVEL1
mdefine_line|#define CL_DLEVEL1&t;1&t;/* debug level 1, informative */
DECL|macro|CL_DLEVEL2
mdefine_line|#define CL_DLEVEL2&t;2&t;/* debug level 2, verbose */
DECL|macro|CL_DLEVEL3
mdefine_line|#define CL_DLEVEL3&t;3&t;/* debug level 3, very verbose */
DECL|macro|con_log
mdefine_line|#define&t;con_log(level, fmt) if (LSI_DBGLVL &gt;= level) printk fmt;
multiline_comment|/*&n; * Definitions &amp; Declarations needed to use common management module&n; */
DECL|macro|MEGAIOC_MAGIC
mdefine_line|#define MEGAIOC_MAGIC&t;&t;&squot;m&squot;
DECL|macro|MEGAIOCCMD
mdefine_line|#define MEGAIOCCMD&t;&t;_IOWR(MEGAIOC_MAGIC, 0, mimd_t)
DECL|macro|MEGAIOC_QNADAP
mdefine_line|#define MEGAIOC_QNADAP&t;&t;&squot;m&squot;&t;/* Query # of adapters&t;&t;*/
DECL|macro|MEGAIOC_QDRVRVER
mdefine_line|#define MEGAIOC_QDRVRVER&t;&squot;e&squot;&t;/* Query driver version&t;&t;*/
DECL|macro|MEGAIOC_QADAPINFO
mdefine_line|#define MEGAIOC_QADAPINFO   &t;&squot;g&squot;&t;/* Query adapter information&t;*/
DECL|macro|USCSICMD
mdefine_line|#define USCSICMD&t;&t;0x80
DECL|macro|UIOC_RD
mdefine_line|#define UIOC_RD&t;&t;&t;0x00001
DECL|macro|UIOC_WR
mdefine_line|#define UIOC_WR&t;&t;&t;0x00002
DECL|macro|MBOX_CMD
mdefine_line|#define MBOX_CMD&t;&t;0x00000
DECL|macro|GET_DRIVER_VER
mdefine_line|#define GET_DRIVER_VER&t;&t;0x10000
DECL|macro|GET_N_ADAP
mdefine_line|#define GET_N_ADAP&t;&t;0x20000
DECL|macro|GET_ADAP_INFO
mdefine_line|#define GET_ADAP_INFO&t;&t;0x30000
DECL|macro|GET_CAP
mdefine_line|#define GET_CAP&t;&t;&t;0x40000
DECL|macro|GET_STATS
mdefine_line|#define GET_STATS&t;&t;0x50000
DECL|macro|GET_IOCTL_VERSION
mdefine_line|#define GET_IOCTL_VERSION&t;0x01
DECL|macro|EXT_IOCTL_SIGN_SZ
mdefine_line|#define EXT_IOCTL_SIGN_SZ&t;16
DECL|macro|EXT_IOCTL_SIGN
mdefine_line|#define EXT_IOCTL_SIGN&t;&t;&quot;$$_EXTD_IOCTL_$$&quot;
DECL|macro|MBOX_LEGACY
mdefine_line|#define&t;MBOX_LEGACY&t;&t;0x00&t;&t;/* ioctl has legacy mbox*/
DECL|macro|MBOX_HPE
mdefine_line|#define MBOX_HPE&t;&t;0x01&t;&t;/* ioctl has hpe mbox&t;*/
DECL|macro|APPTYPE_MIMD
mdefine_line|#define&t;APPTYPE_MIMD&t;&t;0x00&t;&t;/* old existing apps&t;*/
DECL|macro|APPTYPE_UIOC
mdefine_line|#define APPTYPE_UIOC&t;&t;0x01&t;&t;/* new apps using uioc&t;*/
DECL|macro|IOCTL_ISSUE
mdefine_line|#define IOCTL_ISSUE&t;&t;0x00000001&t;/* Issue ioctl&t;&t;*/
DECL|macro|IOCTL_ABORT
mdefine_line|#define IOCTL_ABORT&t;&t;0x00000002&t;/* Abort previous ioctl&t;*/
DECL|macro|DRVRTYPE_MBOX
mdefine_line|#define DRVRTYPE_MBOX&t;&t;0x00000001&t;/* regular mbox driver&t;*/
DECL|macro|DRVRTYPE_HPE
mdefine_line|#define DRVRTYPE_HPE&t;&t;0x00000002&t;/* new hpe driver&t;*/
DECL|macro|MKADAP
mdefine_line|#define MKADAP(adapno)&t;(MEGAIOC_MAGIC &lt;&lt; 8 | (adapno) )
DECL|macro|GETADAP
mdefine_line|#define GETADAP(mkadap)&t;((mkadap) ^ MEGAIOC_MAGIC &lt;&lt; 8)
DECL|macro|MAX_DMA_POOLS
mdefine_line|#define MAX_DMA_POOLS&t;&t;5&t;&t;/* 4k, 8k, 16k, 32k, 64k*/
multiline_comment|/**&n; * struct uioc_t - the common ioctl packet structure&n; *&n; * @signature&t;: Must be &quot;$$_EXTD_IOCTL_$$&quot;&n; * @mb_type&t;: Type of the mail box (MB_LEGACY or MB_HPE)&n; * @app_type&t;: Type of the issuing application (existing or new)&n; * @opcode&t;: Opcode of the command&n; * @adapno&t;: Adapter number&n; * @cmdbuf&t;: Pointer to buffer - can point to mbox or plain data buffer&n; * @xferlen&t;: xferlen for DCMD and non mailbox commands&n; * @data_dir&t;: Direction of the data transfer&n; * @status&t;: Status from the driver&n; * @reserved&t;: reserved bytes for future expansion&n; *&n; * @user_data&t;: user data transfer address is saved in this&n; * @user_data_len: length of the data buffer sent by user app&n; * @user_pthru&t;: user passthru address is saves in this (null if DCMD)&n; * @pthru32&t;: kernel address passthru (allocated per kioc)&n; * @pthru32_h&t;: physicall address of @pthru32&n; * @list&t;: for kioc free pool list maintenance&n; * @done&t;: call back routine for llds to call when kioc is completed&n; * @buf_vaddr&t;: dma pool buffer attached to kioc for data transfer&n; * @buf_paddr&t;: physical address of the dma pool buffer&n; * @pool_index&t;: index of the dma pool that @buf_vaddr is taken from&n; * @free_buf&t;: indicates if buffer needs to be freed after kioc completes&n; *&n; * Note&t;&t;: All LSI drivers understand only this packet. Any other&n; *&t;&t;: format sent by applications would be converted to this.&n; */
DECL|struct|uioc
r_typedef
r_struct
id|uioc
(brace
multiline_comment|/* User Apps: */
DECL|member|signature
r_uint8
id|signature
(braket
id|EXT_IOCTL_SIGN_SZ
)braket
suffix:semicolon
DECL|member|mb_type
r_uint16
id|mb_type
suffix:semicolon
DECL|member|app_type
r_uint16
id|app_type
suffix:semicolon
DECL|member|opcode
r_uint32
id|opcode
suffix:semicolon
DECL|member|adapno
r_uint32
id|adapno
suffix:semicolon
DECL|member|cmdbuf
r_uint64
id|cmdbuf
suffix:semicolon
DECL|member|xferlen
r_uint32
id|xferlen
suffix:semicolon
DECL|member|data_dir
r_uint32
id|data_dir
suffix:semicolon
DECL|member|status
r_int32
id|status
suffix:semicolon
DECL|member|reserved
r_uint8
id|reserved
(braket
l_int|128
)braket
suffix:semicolon
multiline_comment|/* Driver Data: */
DECL|member|user_data
r_void
id|__user
op_star
id|user_data
suffix:semicolon
DECL|member|user_data_len
r_uint32
id|user_data_len
suffix:semicolon
DECL|member|user_pthru
id|mraid_passthru_t
id|__user
op_star
id|user_pthru
suffix:semicolon
DECL|member|pthru32
id|mraid_passthru_t
op_star
id|pthru32
suffix:semicolon
DECL|member|pthru32_h
id|dma_addr_t
id|pthru32_h
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|done
r_void
(paren
op_star
id|done
)paren
(paren
r_struct
id|uioc
op_star
)paren
suffix:semicolon
DECL|member|buf_vaddr
id|caddr_t
id|buf_vaddr
suffix:semicolon
DECL|member|buf_paddr
id|dma_addr_t
id|buf_paddr
suffix:semicolon
DECL|member|pool_index
r_uint8
id|pool_index
suffix:semicolon
DECL|member|free_buf
r_uint8
id|free_buf
suffix:semicolon
DECL|member|timedout
r_uint8
id|timedout
suffix:semicolon
DECL|typedef|uioc_t
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|1024
)paren
comma
id|packed
)paren
)paren
id|uioc_t
suffix:semicolon
multiline_comment|/**&n; * struct mraid_hba_info - information about the controller&n; *&n; * @param pci_vendor_id&t;&t;: PCI vendor id&n; * @param pci_device_id&t;&t;: PCI device id&n; * @param subsystem_vendor_id&t;: PCI subsystem vendor id&n; * @param subsystem_device_id&t;: PCI subsystem device id&n; * @param baseport&t;&t;: base port of hba memory&n; * @param pci_bus&t;&t;: PCI bus&n; * @param pci_dev_fn&t;&t;: PCI device/function values&n; * @param irq&t;&t;&t;: interrupt vector for the device&n; *&n; * Extended information of 256 bytes about the controller. Align on the single&n; * byte boundary so that 32-bit applications can be run on 64-bit platform&n; * drivers withoug re-compilation.&n; * NOTE: reduce the number of reserved bytes whenever new field are added, so&n; * that total size of the structure remains 256 bytes.&n; */
DECL|struct|mraid_hba_info
r_typedef
r_struct
id|mraid_hba_info
(brace
DECL|member|pci_vendor_id
r_uint16
id|pci_vendor_id
suffix:semicolon
DECL|member|pci_device_id
r_uint16
id|pci_device_id
suffix:semicolon
DECL|member|subsys_vendor_id
r_uint16
id|subsys_vendor_id
suffix:semicolon
DECL|member|subsys_device_id
r_uint16
id|subsys_device_id
suffix:semicolon
DECL|member|baseport
r_uint64
id|baseport
suffix:semicolon
DECL|member|pci_bus
r_uint8
id|pci_bus
suffix:semicolon
DECL|member|pci_dev_fn
r_uint8
id|pci_dev_fn
suffix:semicolon
DECL|member|pci_slot
r_uint8
id|pci_slot
suffix:semicolon
DECL|member|irq
r_uint8
id|irq
suffix:semicolon
DECL|member|unique_id
r_uint32
id|unique_id
suffix:semicolon
DECL|member|host_no
r_uint32
id|host_no
suffix:semicolon
DECL|member|num_ldrv
r_uint8
id|num_ldrv
suffix:semicolon
DECL|typedef|mraid_hba_info_t
)brace
id|__attribute__
(paren
(paren
id|aligned
c_func
(paren
l_int|256
)paren
comma
id|packed
)paren
)paren
id|mraid_hba_info_t
suffix:semicolon
multiline_comment|/**&n; * mcontroller&t;: adapter info structure for old mimd_t apps&n; *&n; * @base&t;: base address&n; * @irq&t;&t;: irq number&n; * @numldrv&t;: number of logical drives&n; * @pcibus&t;: pci bus&n; * @pcidev&t;: pci device&n; * @pcifun&t;: pci function&n; * @pciid&t;: pci id&n; * @pcivendor&t;: vendor id&n; * @pcislot&t;: slot number&n; * @uid&t;&t;: unique id&n; */
DECL|struct|mcontroller
r_typedef
r_struct
id|mcontroller
(brace
DECL|member|base
r_uint64
id|base
suffix:semicolon
DECL|member|irq
r_uint8
id|irq
suffix:semicolon
DECL|member|numldrv
r_uint8
id|numldrv
suffix:semicolon
DECL|member|pcibus
r_uint8
id|pcibus
suffix:semicolon
DECL|member|pcidev
r_uint16
id|pcidev
suffix:semicolon
DECL|member|pcifun
r_uint8
id|pcifun
suffix:semicolon
DECL|member|pciid
r_uint16
id|pciid
suffix:semicolon
DECL|member|pcivendor
r_uint16
id|pcivendor
suffix:semicolon
DECL|member|pcislot
r_uint8
id|pcislot
suffix:semicolon
DECL|member|uid
r_uint32
id|uid
suffix:semicolon
DECL|typedef|mcontroller_t
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
id|mcontroller_t
suffix:semicolon
multiline_comment|/**&n; * mm_dmapool_t&t;: Represents one dma pool with just one buffer&n; *&n; * @vaddr&t;: Virtual address&n; * @paddr&t;: DMA physicall address&n; * @bufsize&t;: In KB - 4 = 4k, 8 = 8k etc.&n; * @handle&t;: Handle to the dma pool&n; * @lock&t;: lock to synchronize access to the pool&n; * @in_use&t;: If pool already in use, attach new block&n; */
DECL|struct|mm_dmapool
r_typedef
r_struct
id|mm_dmapool
(brace
DECL|member|vaddr
id|caddr_t
id|vaddr
suffix:semicolon
DECL|member|paddr
id|dma_addr_t
id|paddr
suffix:semicolon
DECL|member|buf_size
r_uint32
id|buf_size
suffix:semicolon
DECL|member|handle
r_struct
id|dma_pool
op_star
id|handle
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|in_use
r_uint8
id|in_use
suffix:semicolon
DECL|typedef|mm_dmapool_t
)brace
id|mm_dmapool_t
suffix:semicolon
multiline_comment|/**&n; * mraid_mmadp_t: Structure that drivers pass during (un)registration&n; *&n; * @unique_id&t;&t;: Any unique id (usually PCI bus+dev+fn)&n; * @drvr_type&t;&t;: megaraid or hpe (DRVRTYPE_MBOX or DRVRTYPE_HPE)&n; * @drv_data&t;&t;: Driver specific; not touched by the common module&n; * @timeout&t;&t;: timeout for issued kiocs&n; * @max_kioc&t;&t;: Maximum ioctl packets acceptable by the lld&n; * @pdev&t;&t;: pci dev; used for allocating dma&squot;ble memory&n; * @issue_uioc&t;&t;: Driver supplied routine to issue uioc_t commands&n; *&t;&t;&t;: issue_uioc(drvr_data, kioc, ISSUE/ABORT, uioc_done)&n; * @quiescent&t;&t;: flag to indicate if ioctl can be issued to this adp&n; * @list&t;&t;: attach with the global list of adapters&n; * @kioc_list&t;&t;: block of mem for @max_kioc number of kiocs&n; * @kioc_pool&t;&t;: pool of free kiocs&n; * @kioc_pool_lock&t;: protection for free pool&n; * @kioc_semaphore&t;: so as not to exceed @max_kioc parallel ioctls&n; * @mbox_list&t;&t;: block of mem for @max_kioc number of mboxes&n; * @pthru_dma_pool&t;: DMA pool to allocate passthru packets&n; * @dma_pool_list&t;: array of dma pools&n; */
DECL|struct|mraid_mmadp
r_typedef
r_struct
id|mraid_mmadp
(brace
multiline_comment|/* Filled by driver */
DECL|member|unique_id
r_uint32
id|unique_id
suffix:semicolon
DECL|member|drvr_type
r_uint32
id|drvr_type
suffix:semicolon
DECL|member|drvr_data
r_int
r_int
id|drvr_data
suffix:semicolon
DECL|member|timeout
r_uint16
id|timeout
suffix:semicolon
DECL|member|max_kioc
r_uint8
id|max_kioc
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
DECL|member|issue_uioc
r_int
(paren
op_star
id|issue_uioc
)paren
(paren
r_int
r_int
comma
id|uioc_t
op_star
comma
r_uint32
)paren
suffix:semicolon
multiline_comment|/* Maintained by common module */
DECL|member|quiescent
r_uint32
id|quiescent
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|kioc_list
id|uioc_t
op_star
id|kioc_list
suffix:semicolon
DECL|member|kioc_pool
r_struct
id|list_head
id|kioc_pool
suffix:semicolon
DECL|member|kioc_pool_lock
id|spinlock_t
id|kioc_pool_lock
suffix:semicolon
DECL|member|kioc_semaphore
r_struct
id|semaphore
id|kioc_semaphore
suffix:semicolon
DECL|member|mbox_list
id|mbox64_t
op_star
id|mbox_list
suffix:semicolon
DECL|member|pthru_dma_pool
r_struct
id|dma_pool
op_star
id|pthru_dma_pool
suffix:semicolon
DECL|member|dma_pool_list
id|mm_dmapool_t
id|dma_pool_list
(braket
id|MAX_DMA_POOLS
)braket
suffix:semicolon
DECL|typedef|mraid_mmadp_t
)brace
id|mraid_mmadp_t
suffix:semicolon
r_int
id|mraid_mm_register_adp
c_func
(paren
id|mraid_mmadp_t
op_star
)paren
suffix:semicolon
r_int
id|mraid_mm_unregister_adp
c_func
(paren
r_uint32
)paren
suffix:semicolon
macro_line|#endif /* _MEGARAID_IOCTL_H_ */
eof
