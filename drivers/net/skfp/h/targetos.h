multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *&t;Operating system specific definitions for driver and&n; *&t;hardware module.&n; */
macro_line|#ifndef&t;TARGETOS_H
DECL|macro|TARGETOS_H
mdefine_line|#define TARGETOS_H
singleline_comment|//-------- those should go into include/linux/pci.h
DECL|macro|PCI_VENDOR_ID_SK
mdefine_line|#define PCI_VENDOR_ID_SK&t;&t;0x1148
DECL|macro|PCI_DEVICE_ID_SK_FP
mdefine_line|#define PCI_DEVICE_ID_SK_FP&t;&t;0x4000
singleline_comment|//--------
singleline_comment|//-------- those should go into include/linux/if_fddi.h
DECL|macro|FDDI_MAC_HDR_LEN
mdefine_line|#define FDDI_MAC_HDR_LEN 13
DECL|macro|FDDI_RII
mdefine_line|#define FDDI_RII&t;0x01 /* routing information bit */
DECL|macro|FDDI_RCF_DIR_BIT
mdefine_line|#define FDDI_RCF_DIR_BIT 0x80
DECL|macro|FDDI_RCF_LEN_MASK
mdefine_line|#define FDDI_RCF_LEN_MASK 0x1f
DECL|macro|FDDI_RCF_BROADCAST
mdefine_line|#define FDDI_RCF_BROADCAST 0x8000
DECL|macro|FDDI_RCF_LIMITED_BROADCAST
mdefine_line|#define FDDI_RCF_LIMITED_BROADCAST 0xA000
DECL|macro|FDDI_RCF_FRAME2K
mdefine_line|#define FDDI_RCF_FRAME2K 0x20
DECL|macro|FDDI_RCF_FRAME4K
mdefine_line|#define FDDI_RCF_FRAME4K 0x30
singleline_comment|//--------
DECL|macro|ADDR
macro_line|#undef ADDR
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/fddidevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
singleline_comment|// is redefined by linux, but we need our definition
DECL|macro|ADDR
macro_line|#undef ADDR
macro_line|#ifdef MEM_MAPPED_IO
DECL|macro|ADDR
mdefine_line|#define&t;ADDR(a) (char far *) smc-&gt;hw.iop+(a)
macro_line|#else
DECL|macro|ADDR
mdefine_line|#define&t;ADDR(a) (((a)&gt;&gt;7) ? (outp(smc-&gt;hw.iop+B0_RAP,(a)&gt;&gt;7), (smc-&gt;hw.iop+( ((a)&amp;0x7F) | ((a)&gt;&gt;7 ? 0x80:0)) )) : (smc-&gt;hw.iop+(((a)&amp;0x7F)|((a)&gt;&gt;7 ? 0x80:0))))
macro_line|#endif
macro_line|#include &quot;h/hwmtm.h&quot;
DECL|macro|TRUE
mdefine_line|#define TRUE  1
DECL|macro|FALSE
mdefine_line|#define FALSE 0
singleline_comment|// HWM Definitions
singleline_comment|// -----------------------
DECL|macro|FDDI_TRACE
mdefine_line|#define FDDI_TRACE(string, arg1, arg2, arg3)&t;
singleline_comment|// Performance analysis.
macro_line|#ifdef PCI
DECL|macro|NDD_TRACE
mdefine_line|#define NDD_TRACE(string, arg1, arg2, arg3)&t;
singleline_comment|// Performance analysis.
macro_line|#endif&t;
singleline_comment|// PCI
DECL|macro|SMT_PAGESIZE
mdefine_line|#define SMT_PAGESIZE&t;PAGE_SIZE&t;
singleline_comment|// Size of a memory page (power of 2).
singleline_comment|// -----------------------
singleline_comment|// SMT Definitions
singleline_comment|// -----------------------
DECL|macro|TICKS_PER_SECOND
mdefine_line|#define&t;TICKS_PER_SECOND&t;HZ
DECL|macro|SMC_VERSION
mdefine_line|#define SMC_VERSION    &t;&t;1
singleline_comment|// -----------------------
singleline_comment|// OS-Driver Definitions
singleline_comment|// -----------------------
DECL|macro|NO_ADDRESS
mdefine_line|#define NO_ADDRESS 0xffe0&t;/* No Device (I/O) Address */
DECL|macro|SKFP_MAX_NUM_BOARDS
mdefine_line|#define SKFP_MAX_NUM_BOARDS 8&t;/* maximum number of PCI boards */
DECL|macro|SK_BUS_TYPE_PCI
mdefine_line|#define SK_BUS_TYPE_PCI&t;&t;0
DECL|macro|SK_BUS_TYPE_EISA
mdefine_line|#define SK_BUS_TYPE_EISA&t;1
DECL|macro|FP_IO_LEN
mdefine_line|#define FP_IO_LEN&t;&t;256&t;/* length of IO area used */
DECL|macro|u8
mdefine_line|#define u8&t;unsigned char
DECL|macro|u16
mdefine_line|#define u16&t;unsigned short
DECL|macro|u32
mdefine_line|#define u32&t;unsigned int
DECL|macro|MAX_TX_QUEUE_LEN
mdefine_line|#define MAX_TX_QUEUE_LEN&t;20 
singleline_comment|// number of packets queued by driver
DECL|macro|MAX_FRAME_SIZE
mdefine_line|#define MAX_FRAME_SIZE&t;&t;4550
DECL|macro|RX_LOW_WATERMARK
mdefine_line|#define&t;RX_LOW_WATERMARK&t;NUM_RECEIVE_BUFFERS  / 2
DECL|macro|TX_LOW_WATERMARK
mdefine_line|#define TX_LOW_WATERMARK&t;NUM_TRANSMIT_BUFFERS - 2
multiline_comment|/*&n;** Include the IOCTL stuff&n;*/
macro_line|#include &lt;linux/sockios.h&gt;
DECL|macro|SKFPIOCTL
mdefine_line|#define&t;SKFPIOCTL&t;SIOCDEVPRIVATE
DECL|struct|s_skfp_ioctl
r_struct
id|s_skfp_ioctl
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
multiline_comment|/* Command to run */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Length of the data buffer */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to the data buffer */
)brace
suffix:semicolon
multiline_comment|/* &n;** Recognised ioctl commands for the driver &n;*/
DECL|macro|SKFP_GET_STATS
mdefine_line|#define SKFP_GET_STATS&t;&t;0x05 /* Get the driver statistics */
DECL|macro|SKFP_CLR_STATS
mdefine_line|#define SKFP_CLR_STATS&t;&t;0x06 /* Zero out the driver statistics */
singleline_comment|// The per-adapter driver structure
DECL|struct|s_smt_os
r_struct
id|s_smt_os
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|next_module
r_struct
id|net_device
op_star
id|next_module
suffix:semicolon
DECL|member|bus_type
id|u32
id|bus_type
suffix:semicolon
multiline_comment|/* bus type (0 == PCI, 1 == EISA) */
DECL|member|pdev
r_struct
id|pci_dev
id|pdev
suffix:semicolon
multiline_comment|/* PCI device structure */
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|factory_mac_addr
r_int
r_char
id|factory_mac_addr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|SharedMemSize
id|ulong
id|SharedMemSize
suffix:semicolon
DECL|member|SharedMemHeap
id|ulong
id|SharedMemHeap
suffix:semicolon
DECL|member|SharedMemAddr
r_void
op_star
id|SharedMemAddr
suffix:semicolon
DECL|member|SharedMemDMA
id|dma_addr_t
id|SharedMemDMA
suffix:semicolon
DECL|member|QueueSkb
id|ulong
id|QueueSkb
suffix:semicolon
DECL|member|SendSkbQueue
r_struct
id|sk_buff_head
id|SendSkbQueue
suffix:semicolon
DECL|member|MaxFrameSize
id|ulong
id|MaxFrameSize
suffix:semicolon
DECL|member|ResetRequested
id|u8
id|ResetRequested
suffix:semicolon
singleline_comment|// MAC statistics structure
DECL|member|MacStat
r_struct
id|fddi_statistics
id|MacStat
suffix:semicolon
singleline_comment|// receive into this local buffer if no skb available
singleline_comment|// data will be not valid, because multiple RxDs can
singleline_comment|// point here at the same time, it must be at least
singleline_comment|// MAX_FRAME_SIZE bytes in size
DECL|member|LocalRxBuffer
r_int
r_char
op_star
id|LocalRxBuffer
suffix:semicolon
DECL|member|LocalRxBufferDMA
id|dma_addr_t
id|LocalRxBufferDMA
suffix:semicolon
singleline_comment|// Version (required by SMT module).
DECL|member|smc_version
id|u_long
id|smc_version
suffix:semicolon
singleline_comment|// Required by Hardware Module (HWM).
DECL|member|hwm
r_struct
id|hw_modul
id|hwm
suffix:semicolon
singleline_comment|// For SMP-savety
DECL|member|DriverLock
id|spinlock_t
id|DriverLock
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|skfddi_priv
r_typedef
r_struct
id|s_smt_os
id|skfddi_priv
suffix:semicolon
macro_line|#endif&t; 
singleline_comment|// _TARGETOS_
eof
