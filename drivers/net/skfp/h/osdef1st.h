multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998,1999 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/* &n; * Operating system-dependant definitions that have to be defined&n; * before any other header files are included.&n; */
singleline_comment|// HWM (HardWare Module) Definitions
singleline_comment|// -----------------------
macro_line|#ifdef __LITTLE_ENDIAN
DECL|macro|LITTLE_ENDIAN
mdefine_line|#define LITTLE_ENDIAN
macro_line|#else
DECL|macro|BIG_ENDIAN
mdefine_line|#define BIG_ENDIAN
macro_line|#endif
singleline_comment|// this is set in the makefile
singleline_comment|// #define PCI&t;&t;&t;/* only PCI adapters supported by this driver */
singleline_comment|// #define MEM_MAPPED_IO&t;/* use memory mapped I/O */
DECL|macro|USE_CAN_ADDR
mdefine_line|#define USE_CAN_ADDR&t;&t;/* DA and SA in MAC header are canonical. */
DECL|macro|MB_OUTSIDE_SMC
mdefine_line|#define MB_OUTSIDE_SMC&t;&t;/* SMT Mbufs outside of smc struct. */
singleline_comment|// -----------------------
singleline_comment|// SMT Definitions 
singleline_comment|// -----------------------
DECL|macro|SYNC
mdefine_line|#define SYNC&t;       &t;&t;/* allow synchronous frames */
singleline_comment|// #define SBA&t;&t;&t;/* Synchronous Bandwidth Allocator support */
multiline_comment|/* not available as free source */
DECL|macro|ESS
mdefine_line|#define ESS&t;&t;&t;/* SBA End Station Support */
DECL|macro|SMT_PANIC
mdefine_line|#define&t;SMT_PANIC(smc, nr, msg)&t;printk(KERN_INFO &quot;SMT PANIC: code: %d, msg: %s&bslash;n&quot;,nr,msg)
macro_line|#ifdef DEBUG
DECL|macro|printf
mdefine_line|#define printf(s,args...) printk(KERN_INFO s, ## args)
macro_line|#endif
singleline_comment|// #define HW_PTR&t;u_long
singleline_comment|// -----------------------
singleline_comment|// HWM and OS-specific buffer definitions
singleline_comment|// -----------------------
singleline_comment|// default number of receive buffers.
DECL|macro|NUM_RECEIVE_BUFFERS
mdefine_line|#define NUM_RECEIVE_BUFFERS&t;&t;10
singleline_comment|// default number of transmit buffers.
DECL|macro|NUM_TRANSMIT_BUFFERS
mdefine_line|#define NUM_TRANSMIT_BUFFERS&t;&t;10
singleline_comment|// Number of SMT buffers (Mbufs).
DECL|macro|NUM_SMT_BUF
mdefine_line|#define NUM_SMT_BUF&t;4
singleline_comment|// Number of TXDs for asynchronous transmit queue.
DECL|macro|HWM_ASYNC_TXD_COUNT
mdefine_line|#define HWM_ASYNC_TXD_COUNT&t;(NUM_TRANSMIT_BUFFERS + NUM_SMT_BUF)
singleline_comment|// Number of TXDs for synchronous transmit queue.
DECL|macro|HWM_SYNC_TXD_COUNT
mdefine_line|#define HWM_SYNC_TXD_COUNT&t;HWM_ASYNC_TXD_COUNT
singleline_comment|// Number of RXDs for receive queue #1.
singleline_comment|// Note: Workaround for ASIC Errata #7: One extra RXD is required.
macro_line|#if (NUM_RECEIVE_BUFFERS &gt; 100)
DECL|macro|SMT_R1_RXD_COUNT
mdefine_line|#define SMT_R1_RXD_COUNT&t;(1 + 100)
macro_line|#else
DECL|macro|SMT_R1_RXD_COUNT
mdefine_line|#define SMT_R1_RXD_COUNT&t;(1 + NUM_RECEIVE_BUFFERS)
macro_line|#endif
singleline_comment|// Number of RXDs for receive queue #2.
DECL|macro|SMT_R2_RXD_COUNT
mdefine_line|#define SMT_R2_RXD_COUNT&t;0&t;
singleline_comment|// Not used.
singleline_comment|// -----------------------
multiline_comment|/*&n; * OS-specific part of the transmit/receive descriptor structure (TXD/RXD).&n; *&n; * Note: The size of these structures must follow this rule:&n; *&n; *&t;sizeof(struct) + 2*sizeof(void*) == n * 16, n &gt;= 1&n; *&n; * We use the dma_addr fields under Linux to keep track of the&n; * DMA address of the packet data, for later pci_unmap_single. -DaveM&n; */
DECL|struct|s_txd_os
r_struct
id|s_txd_os
(brace
singleline_comment|// os-specific part of transmit descriptor
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|s_rxd_os
r_struct
id|s_rxd_os
(brace
singleline_comment|// os-specific part of receive descriptor
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|dma_addr
id|dma_addr_t
id|dma_addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * So we do not need to make too many modifications to the generic driver&n; * parts, we take advantage of the AIX byte swapping macro interface.&n; */
DECL|macro|AIX_REVERSE
mdefine_line|#define AIX_REVERSE(x)&t;&t;((u32)le32_to_cpu((u32)(x)))
DECL|macro|MDR_REVERSE
mdefine_line|#define MDR_REVERSE(x)&t;&t;((u32)le32_to_cpu((u32)(x)))
eof
