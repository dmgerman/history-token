multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skdrv2nd.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.10 $&n; * Date:&t;$Date: 2003/12/11 16:04:45 $&n; * Purpose:&t;Second header file for driver and all other modules&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2002 SysKonnect GmbH.&n; *&t;(C)Copyright 2002-2003 Marvell.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * Description:&n; *&n; * This is the second include file of the driver, which includes all other&n; * neccessary files and defines all structures and constants used by the&n; * driver and the common modules.&n; *&n; * Include File Hierarchy:&n; *&n; *&t;see skge.c&n; *&n; ******************************************************************************/
macro_line|#ifndef __INC_SKDRV2ND_H
DECL|macro|__INC_SKDRV2ND_H
mdefine_line|#define __INC_SKDRV2ND_H
macro_line|#include &quot;h/skqueue.h&quot;
macro_line|#include &quot;h/skgehwt.h&quot;
macro_line|#include &quot;h/sktimer.h&quot;
macro_line|#include &quot;h/ski2c.h&quot;
macro_line|#include &quot;h/skgepnmi.h&quot;
macro_line|#include &quot;h/skvpd.h&quot;
macro_line|#include &quot;h/skgehw.h&quot;
macro_line|#include &quot;h/skgeinit.h&quot;
macro_line|#include &quot;h/skaddr.h&quot;
macro_line|#include &quot;h/skgesirq.h&quot;
macro_line|#include &quot;h/skcsum.h&quot;
macro_line|#include &quot;h/skrlmt.h&quot;
macro_line|#include &quot;h/skgedrv.h&quot;
r_extern
id|SK_MBUF
op_star
id|SkDrvAllocRlmtMbuf
c_func
(paren
id|SK_AC
op_star
comma
id|SK_IOC
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|SkDrvFreeRlmtMbuf
c_func
(paren
id|SK_AC
op_star
comma
id|SK_IOC
comma
id|SK_MBUF
op_star
)paren
suffix:semicolon
r_extern
id|SK_U64
id|SkOsGetTime
c_func
(paren
id|SK_AC
op_star
)paren
suffix:semicolon
r_extern
r_int
id|SkPciReadCfgDWord
c_func
(paren
id|SK_AC
op_star
comma
r_int
comma
id|SK_U32
op_star
)paren
suffix:semicolon
r_extern
r_int
id|SkPciReadCfgWord
c_func
(paren
id|SK_AC
op_star
comma
r_int
comma
id|SK_U16
op_star
)paren
suffix:semicolon
r_extern
r_int
id|SkPciReadCfgByte
c_func
(paren
id|SK_AC
op_star
comma
r_int
comma
id|SK_U8
op_star
)paren
suffix:semicolon
r_extern
r_int
id|SkPciWriteCfgDWord
c_func
(paren
id|SK_AC
op_star
comma
r_int
comma
id|SK_U32
)paren
suffix:semicolon
r_extern
r_int
id|SkPciWriteCfgWord
c_func
(paren
id|SK_AC
op_star
comma
r_int
comma
id|SK_U16
)paren
suffix:semicolon
r_extern
r_int
id|SkPciWriteCfgByte
c_func
(paren
id|SK_AC
op_star
comma
r_int
comma
id|SK_U8
)paren
suffix:semicolon
r_extern
r_int
id|SkDrvEvent
c_func
(paren
id|SK_AC
op_star
comma
id|SK_IOC
id|IoC
comma
id|SK_U32
comma
id|SK_EVPARA
)paren
suffix:semicolon
macro_line|#ifdef SK_DIAG_SUPPORT
r_extern
r_int
id|SkDrvEnterDiagMode
c_func
(paren
id|SK_AC
op_star
id|pAc
)paren
suffix:semicolon
r_extern
r_int
id|SkDrvLeaveDiagMode
c_func
(paren
id|SK_AC
op_star
id|pAc
)paren
suffix:semicolon
macro_line|#endif
DECL|struct|s_DrvRlmtMbuf
r_struct
id|s_DrvRlmtMbuf
(brace
DECL|member|pNext
id|SK_MBUF
op_star
id|pNext
suffix:semicolon
multiline_comment|/* Pointer to next RLMT Mbuf. */
DECL|member|pData
id|SK_U8
op_star
id|pData
suffix:semicolon
multiline_comment|/* Data buffer (virtually contig.). */
DECL|member|Size
r_int
id|Size
suffix:semicolon
multiline_comment|/* Data buffer size. */
DECL|member|Length
r_int
id|Length
suffix:semicolon
multiline_comment|/* Length of packet (&lt;= Size). */
DECL|member|PortIdx
id|SK_U32
id|PortIdx
suffix:semicolon
multiline_comment|/* Receiving/transmitting port. */
macro_line|#ifdef SK_RLMT_MBUF_PRIVATE
DECL|member|Rlmt
id|SK_RLMT_MBUF
id|Rlmt
suffix:semicolon
multiline_comment|/* Private part for RLMT. */
macro_line|#endif  /* SK_RLMT_MBUF_PRIVATE */
DECL|member|pOs
r_struct
id|sk_buff
op_star
id|pOs
suffix:semicolon
multiline_comment|/* Pointer to message block */
)brace
suffix:semicolon
multiline_comment|/*&n; * Time macros&n; */
macro_line|#if SK_TICKS_PER_SEC == 100
DECL|macro|SK_PNMI_HUNDREDS_SEC
mdefine_line|#define SK_PNMI_HUNDREDS_SEC(t)&t;(t)
macro_line|#else
DECL|macro|SK_PNMI_HUNDREDS_SEC
mdefine_line|#define SK_PNMI_HUNDREDS_SEC(t)&t;((((unsigned long)t) * 100) / &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;(SK_TICKS_PER_SEC))
macro_line|#endif
multiline_comment|/*&n; * New SkOsGetTime&n; */
DECL|macro|SkOsGetTimeCurrent
mdefine_line|#define SkOsGetTimeCurrent(pAC, pUsec) {&bslash;&n;&t;struct timeval t;&bslash;&n;&t;do_gettimeofday(&amp;t);&bslash;&n;&t;*pUsec = ((((t.tv_sec) * 1000000L)+t.tv_usec)/10000);&bslash;&n;}
multiline_comment|/*&n; * ioctl definitions&n; */
DECL|macro|SK_IOCTL_BASE
mdefine_line|#define&t;&t;SK_IOCTL_BASE&t;&t;(SIOCDEVPRIVATE)
DECL|macro|SK_IOCTL_GETMIB
mdefine_line|#define&t;&t;SK_IOCTL_GETMIB&t;&t;(SK_IOCTL_BASE + 0)
DECL|macro|SK_IOCTL_SETMIB
mdefine_line|#define&t;&t;SK_IOCTL_SETMIB&t;&t;(SK_IOCTL_BASE + 1)
DECL|macro|SK_IOCTL_PRESETMIB
mdefine_line|#define&t;&t;SK_IOCTL_PRESETMIB&t;(SK_IOCTL_BASE + 2)
DECL|macro|SK_IOCTL_GEN
mdefine_line|#define&t;&t;SK_IOCTL_GEN&t;&t;(SK_IOCTL_BASE + 3)
DECL|macro|SK_IOCTL_DIAG
mdefine_line|#define&t;&t;SK_IOCTL_DIAG&t;&t;(SK_IOCTL_BASE + 4)
DECL|typedef|SK_GE_IOCTL
r_typedef
r_struct
id|s_IOCTL
id|SK_GE_IOCTL
suffix:semicolon
DECL|struct|s_IOCTL
r_struct
id|s_IOCTL
(brace
DECL|member|pData
r_char
id|__user
op_star
id|pData
suffix:semicolon
DECL|member|Len
r_int
r_int
id|Len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * define sizes of descriptor rings in bytes&n; */
DECL|macro|TX_RING_SIZE
mdefine_line|#define&t;&t;TX_RING_SIZE&t;(8*1024)
DECL|macro|RX_RING_SIZE
mdefine_line|#define&t;&t;RX_RING_SIZE&t;(24*1024)
multiline_comment|/*&n; * Buffer size for ethernet packets&n; */
DECL|macro|ETH_BUF_SIZE
mdefine_line|#define&t;ETH_BUF_SIZE&t;1540
DECL|macro|ETH_MAX_MTU
mdefine_line|#define&t;ETH_MAX_MTU&t;1514
DECL|macro|ETH_MIN_MTU
mdefine_line|#define ETH_MIN_MTU&t;60
DECL|macro|ETH_MULTICAST_BIT
mdefine_line|#define ETH_MULTICAST_BIT&t;0x01
DECL|macro|SK_JUMBO_MTU
mdefine_line|#define SK_JUMBO_MTU&t;9000
multiline_comment|/*&n; * transmit priority selects the queue: LOW=asynchron, HIGH=synchron&n; */
DECL|macro|TX_PRIO_LOW
mdefine_line|#define TX_PRIO_LOW&t;0
DECL|macro|TX_PRIO_HIGH
mdefine_line|#define TX_PRIO_HIGH&t;1
multiline_comment|/*&n; * alignment of rx/tx descriptors&n; */
DECL|macro|DESCR_ALIGN
mdefine_line|#define DESCR_ALIGN&t;64
multiline_comment|/*&n; * definitions for pnmi. TODO&n; */
DECL|macro|SK_DRIVER_RESET
mdefine_line|#define SK_DRIVER_RESET(pAC, IoC)&t;0
DECL|macro|SK_DRIVER_SENDEVENT
mdefine_line|#define SK_DRIVER_SENDEVENT(pAC, IoC)&t;0
DECL|macro|SK_DRIVER_SELFTEST
mdefine_line|#define SK_DRIVER_SELFTEST(pAC, IoC)&t;0
multiline_comment|/* For get mtu you must add an own function */
DECL|macro|SK_DRIVER_GET_MTU
mdefine_line|#define SK_DRIVER_GET_MTU(pAc,IoC,i)&t;0
DECL|macro|SK_DRIVER_SET_MTU
mdefine_line|#define SK_DRIVER_SET_MTU(pAc,IoC,i,v)&t;0
DECL|macro|SK_DRIVER_PRESET_MTU
mdefine_line|#define SK_DRIVER_PRESET_MTU(pAc,IoC,i,v)&t;0
multiline_comment|/*&n;** Interim definition of SK_DRV_TIMER placed in this file until &n;** common modules have boon finallized&n;*/
DECL|macro|SK_DRV_TIMER
mdefine_line|#define SK_DRV_TIMER&t;&t;&t;11 
DECL|macro|SK_DRV_MODERATION_TIMER
mdefine_line|#define&t;SK_DRV_MODERATION_TIMER&t;&t;1
DECL|macro|SK_DRV_MODERATION_TIMER_LENGTH
mdefine_line|#define SK_DRV_MODERATION_TIMER_LENGTH  1000000  /* 1 second */
DECL|macro|SK_DRV_RX_CLEANUP_TIMER
mdefine_line|#define SK_DRV_RX_CLEANUP_TIMER&t;&t;2
DECL|macro|SK_DRV_RX_CLEANUP_TIMER_LENGTH
mdefine_line|#define SK_DRV_RX_CLEANUP_TIMER_LENGTH&t;1000000&t; /* 100 millisecs */
multiline_comment|/*&n;** Definitions regarding transmitting frames &n;** any calculating any checksum.&n;*/
DECL|macro|C_LEN_ETHERMAC_HEADER_DEST_ADDR
mdefine_line|#define C_LEN_ETHERMAC_HEADER_DEST_ADDR 6
DECL|macro|C_LEN_ETHERMAC_HEADER_SRC_ADDR
mdefine_line|#define C_LEN_ETHERMAC_HEADER_SRC_ADDR  6
DECL|macro|C_LEN_ETHERMAC_HEADER_LENTYPE
mdefine_line|#define C_LEN_ETHERMAC_HEADER_LENTYPE   2
DECL|macro|C_LEN_ETHERMAC_HEADER
mdefine_line|#define C_LEN_ETHERMAC_HEADER           ( (C_LEN_ETHERMAC_HEADER_DEST_ADDR) + &bslash;&n;                                          (C_LEN_ETHERMAC_HEADER_SRC_ADDR)  + &bslash;&n;                                          (C_LEN_ETHERMAC_HEADER_LENTYPE) )
DECL|macro|C_LEN_ETHERMTU_MINSIZE
mdefine_line|#define C_LEN_ETHERMTU_MINSIZE          46
DECL|macro|C_LEN_ETHERMTU_MAXSIZE_STD
mdefine_line|#define C_LEN_ETHERMTU_MAXSIZE_STD      1500
DECL|macro|C_LEN_ETHERMTU_MAXSIZE_JUMBO
mdefine_line|#define C_LEN_ETHERMTU_MAXSIZE_JUMBO    9000
DECL|macro|C_LEN_ETHERNET_MINSIZE
mdefine_line|#define C_LEN_ETHERNET_MINSIZE          ( (C_LEN_ETHERMAC_HEADER) + &bslash;&n;                                          (C_LEN_ETHERMTU_MINSIZE) )
DECL|macro|C_OFFSET_IPHEADER
mdefine_line|#define C_OFFSET_IPHEADER               C_LEN_ETHERMAC_HEADER
DECL|macro|C_OFFSET_IPHEADER_IPPROTO
mdefine_line|#define C_OFFSET_IPHEADER_IPPROTO       9
DECL|macro|C_OFFSET_TCPHEADER_TCPCS
mdefine_line|#define C_OFFSET_TCPHEADER_TCPCS        16
DECL|macro|C_OFFSET_UDPHEADER_UDPCS
mdefine_line|#define C_OFFSET_UDPHEADER_UDPCS        6
DECL|macro|C_OFFSET_IPPROTO
mdefine_line|#define C_OFFSET_IPPROTO                ( (C_LEN_ETHERMAC_HEADER) + &bslash;&n;                                          (C_OFFSET_IPHEADER_IPPROTO) )
DECL|macro|C_PROTO_ID_UDP
mdefine_line|#define C_PROTO_ID_UDP                  17       /* refer to RFC 790 or Stevens&squot;   */
DECL|macro|C_PROTO_ID_TCP
mdefine_line|#define C_PROTO_ID_TCP                  6        /* TCP/IP illustrated for details */
multiline_comment|/* TX and RX descriptors *****************************************************/
DECL|typedef|RXD
r_typedef
r_struct
id|s_RxD
id|RXD
suffix:semicolon
multiline_comment|/* the receive descriptor */
DECL|struct|s_RxD
r_struct
id|s_RxD
(brace
DECL|member|RBControl
r_volatile
id|SK_U32
id|RBControl
suffix:semicolon
multiline_comment|/* Receive Buffer Control */
DECL|member|VNextRxd
id|SK_U32
id|VNextRxd
suffix:semicolon
multiline_comment|/* Next receive descriptor,low dword */
DECL|member|VDataLow
id|SK_U32
id|VDataLow
suffix:semicolon
multiline_comment|/* Receive buffer Addr, low dword */
DECL|member|VDataHigh
id|SK_U32
id|VDataHigh
suffix:semicolon
multiline_comment|/* Receive buffer Addr, high dword */
DECL|member|FrameStat
id|SK_U32
id|FrameStat
suffix:semicolon
multiline_comment|/* Receive Frame Status word */
DECL|member|TimeStamp
id|SK_U32
id|TimeStamp
suffix:semicolon
multiline_comment|/* Time stamp from XMAC */
DECL|member|TcpSums
id|SK_U32
id|TcpSums
suffix:semicolon
multiline_comment|/* TCP Sum 2 / TCP Sum 1 */
DECL|member|TcpSumStarts
id|SK_U32
id|TcpSumStarts
suffix:semicolon
multiline_comment|/* TCP Sum Start 2 / TCP Sum Start 1 */
DECL|member|pNextRxd
id|RXD
op_star
id|pNextRxd
suffix:semicolon
multiline_comment|/* Pointer to next Rxd */
DECL|member|pMBuf
r_struct
id|sk_buff
op_star
id|pMBuf
suffix:semicolon
multiline_comment|/* Pointer to Linux&squot; socket buffer */
)brace
suffix:semicolon
DECL|typedef|TXD
r_typedef
r_struct
id|s_TxD
id|TXD
suffix:semicolon
multiline_comment|/* the transmit descriptor */
DECL|struct|s_TxD
r_struct
id|s_TxD
(brace
DECL|member|TBControl
r_volatile
id|SK_U32
id|TBControl
suffix:semicolon
multiline_comment|/* Transmit Buffer Control */
DECL|member|VNextTxd
id|SK_U32
id|VNextTxd
suffix:semicolon
multiline_comment|/* Next transmit descriptor,low dword */
DECL|member|VDataLow
id|SK_U32
id|VDataLow
suffix:semicolon
multiline_comment|/* Transmit Buffer Addr, low dword */
DECL|member|VDataHigh
id|SK_U32
id|VDataHigh
suffix:semicolon
multiline_comment|/* Transmit Buffer Addr, high dword */
DECL|member|FrameStat
id|SK_U32
id|FrameStat
suffix:semicolon
multiline_comment|/* Transmit Frame Status Word */
DECL|member|TcpSumOfs
id|SK_U32
id|TcpSumOfs
suffix:semicolon
multiline_comment|/* Reserved / TCP Sum Offset */
DECL|member|TcpSumSt
id|SK_U16
id|TcpSumSt
suffix:semicolon
multiline_comment|/* TCP Sum Start */
DECL|member|TcpSumWr
id|SK_U16
id|TcpSumWr
suffix:semicolon
multiline_comment|/* TCP Sum Write */
DECL|member|TcpReserved
id|SK_U32
id|TcpReserved
suffix:semicolon
multiline_comment|/* not used */
DECL|member|pNextTxd
id|TXD
op_star
id|pNextTxd
suffix:semicolon
multiline_comment|/* Pointer to next Txd */
DECL|member|pMBuf
r_struct
id|sk_buff
op_star
id|pMBuf
suffix:semicolon
multiline_comment|/* Pointer to Linux&squot; socket buffer */
)brace
suffix:semicolon
multiline_comment|/* Used interrupt bits in the interrupts source register *********************/
DECL|macro|DRIVER_IRQS
mdefine_line|#define DRIVER_IRQS&t;((IS_IRQ_SW)   | &bslash;&n;&t;&t;&t;(IS_R1_F)      |(IS_R2_F)  | &bslash;&n;&t;&t;&t;(IS_XS1_F)     |(IS_XA1_F) | &bslash;&n;&t;&t;&t;(IS_XS2_F)     |(IS_XA2_F))
DECL|macro|SPECIAL_IRQS
mdefine_line|#define SPECIAL_IRQS&t;((IS_HW_ERR)   |(IS_I2C_READY)  | &bslash;&n;&t;&t;&t;(IS_EXT_REG)   |(IS_TIMINT)     | &bslash;&n;&t;&t;&t;(IS_PA_TO_RX1) |(IS_PA_TO_RX2)  | &bslash;&n;&t;&t;&t;(IS_PA_TO_TX1) |(IS_PA_TO_TX2)  | &bslash;&n;&t;&t;&t;(IS_MAC1)      |(IS_LNK_SYNC_M1)| &bslash;&n;&t;&t;&t;(IS_MAC2)      |(IS_LNK_SYNC_M2)| &bslash;&n;&t;&t;&t;(IS_R1_C)      |(IS_R2_C)       | &bslash;&n;&t;&t;&t;(IS_XS1_C)     |(IS_XA1_C)      | &bslash;&n;&t;&t;&t;(IS_XS2_C)     |(IS_XA2_C))
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;((IS_IRQ_SW)   | &bslash;&n;&t;&t;&t;(IS_R1_B)      |(IS_R1_F)     |(IS_R2_B) |(IS_R2_F) | &bslash;&n;&t;&t;&t;(IS_XS1_B)     |(IS_XS1_F)    |(IS_XA1_B)|(IS_XA1_F)| &bslash;&n;&t;&t;&t;(IS_XS2_B)     |(IS_XS2_F)    |(IS_XA2_B)|(IS_XA2_F)| &bslash;&n;&t;&t;&t;(IS_HW_ERR)    |(IS_I2C_READY)| &bslash;&n;&t;&t;&t;(IS_EXT_REG)   |(IS_TIMINT)   | &bslash;&n;&t;&t;&t;(IS_PA_TO_RX1) |(IS_PA_TO_RX2)| &bslash;&n;&t;&t;&t;(IS_PA_TO_TX1) |(IS_PA_TO_TX2)| &bslash;&n;&t;&t;&t;(IS_MAC1)      |(IS_MAC2)     | &bslash;&n;&t;&t;&t;(IS_R1_C)      |(IS_R2_C)     | &bslash;&n;&t;&t;&t;(IS_XS1_C)     |(IS_XA1_C)    | &bslash;&n;&t;&t;&t;(IS_XS2_C)     |(IS_XA2_C))
DECL|macro|IRQ_HWE_MASK
mdefine_line|#define IRQ_HWE_MASK&t;(IS_ERR_MSK) /* enable all HW irqs */
DECL|typedef|DEV_NET
r_typedef
r_struct
id|s_DevNet
id|DEV_NET
suffix:semicolon
DECL|struct|s_DevNet
r_struct
id|s_DevNet
(brace
DECL|member|PortNr
r_int
id|PortNr
suffix:semicolon
DECL|member|NetNr
r_int
id|NetNr
suffix:semicolon
DECL|member|Mtu
r_int
id|Mtu
suffix:semicolon
DECL|member|Up
r_int
id|Up
suffix:semicolon
DECL|member|pAC
id|SK_AC
op_star
id|pAC
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|TX_PORT
r_typedef
r_struct
id|s_TxPort
id|TX_PORT
suffix:semicolon
DECL|struct|s_TxPort
r_struct
id|s_TxPort
(brace
multiline_comment|/* the transmit descriptor rings */
DECL|member|pTxDescrRing
id|caddr_t
id|pTxDescrRing
suffix:semicolon
multiline_comment|/* descriptor area memory */
DECL|member|VTxDescrRing
id|SK_U64
id|VTxDescrRing
suffix:semicolon
multiline_comment|/* descr. area bus virt. addr. */
DECL|member|pTxdRingHead
id|TXD
op_star
id|pTxdRingHead
suffix:semicolon
multiline_comment|/* Head of Tx rings */
DECL|member|pTxdRingTail
id|TXD
op_star
id|pTxdRingTail
suffix:semicolon
multiline_comment|/* Tail of Tx rings */
DECL|member|pTxdRingPrev
id|TXD
op_star
id|pTxdRingPrev
suffix:semicolon
multiline_comment|/* descriptor sent previously */
DECL|member|TxdRingFree
r_int
id|TxdRingFree
suffix:semicolon
multiline_comment|/* # of free entrys */
DECL|member|TxDesRingLock
id|spinlock_t
id|TxDesRingLock
suffix:semicolon
multiline_comment|/* serialize descriptor accesses */
DECL|member|HwAddr
id|SK_IOC
id|HwAddr
suffix:semicolon
multiline_comment|/* bmu registers address */
DECL|member|PortIndex
r_int
id|PortIndex
suffix:semicolon
multiline_comment|/* index number of port (0 or 1) */
)brace
suffix:semicolon
DECL|typedef|RX_PORT
r_typedef
r_struct
id|s_RxPort
id|RX_PORT
suffix:semicolon
DECL|struct|s_RxPort
r_struct
id|s_RxPort
(brace
multiline_comment|/* the receive descriptor rings */
DECL|member|pRxDescrRing
id|caddr_t
id|pRxDescrRing
suffix:semicolon
multiline_comment|/* descriptor area memory */
DECL|member|VRxDescrRing
id|SK_U64
id|VRxDescrRing
suffix:semicolon
multiline_comment|/* descr. area bus virt. addr. */
DECL|member|pRxdRingHead
id|RXD
op_star
id|pRxdRingHead
suffix:semicolon
multiline_comment|/* Head of Rx rings */
DECL|member|pRxdRingTail
id|RXD
op_star
id|pRxdRingTail
suffix:semicolon
multiline_comment|/* Tail of Rx rings */
DECL|member|pRxdRingPrev
id|RXD
op_star
id|pRxdRingPrev
suffix:semicolon
multiline_comment|/* descriptor given to BMU previously */
DECL|member|RxdRingFree
r_int
id|RxdRingFree
suffix:semicolon
multiline_comment|/* # of free entrys */
DECL|member|RxDesRingLock
id|spinlock_t
id|RxDesRingLock
suffix:semicolon
multiline_comment|/* serialize descriptor accesses */
DECL|member|RxFillLimit
r_int
id|RxFillLimit
suffix:semicolon
multiline_comment|/* limit for buffers in ring */
DECL|member|HwAddr
id|SK_IOC
id|HwAddr
suffix:semicolon
multiline_comment|/* bmu registers address */
DECL|member|PortIndex
r_int
id|PortIndex
suffix:semicolon
multiline_comment|/* index number of port (0 or 1) */
)brace
suffix:semicolon
multiline_comment|/* Definitions needed for interrupt moderation *******************************/
DECL|macro|IRQ_EOF_AS_TX
mdefine_line|#define IRQ_EOF_AS_TX     ((IS_XA1_F)     | (IS_XA2_F))
DECL|macro|IRQ_EOF_SY_TX
mdefine_line|#define IRQ_EOF_SY_TX     ((IS_XS1_F)     | (IS_XS2_F))
DECL|macro|IRQ_MASK_TX_ONLY
mdefine_line|#define IRQ_MASK_TX_ONLY  ((IRQ_EOF_AS_TX)| (IRQ_EOF_SY_TX))
DECL|macro|IRQ_MASK_RX_ONLY
mdefine_line|#define IRQ_MASK_RX_ONLY  ((IS_R1_F)      | (IS_R2_F))
DECL|macro|IRQ_MASK_SP_ONLY
mdefine_line|#define IRQ_MASK_SP_ONLY  (SPECIAL_IRQS)
DECL|macro|IRQ_MASK_TX_RX
mdefine_line|#define IRQ_MASK_TX_RX    ((IRQ_MASK_TX_ONLY)| (IRQ_MASK_RX_ONLY))
DECL|macro|IRQ_MASK_SP_RX
mdefine_line|#define IRQ_MASK_SP_RX    ((SPECIAL_IRQS)    | (IRQ_MASK_RX_ONLY))
DECL|macro|IRQ_MASK_SP_TX
mdefine_line|#define IRQ_MASK_SP_TX    ((SPECIAL_IRQS)    | (IRQ_MASK_TX_ONLY))
DECL|macro|IRQ_MASK_RX_TX_SP
mdefine_line|#define IRQ_MASK_RX_TX_SP ((SPECIAL_IRQS)    | (IRQ_MASK_TX_RX))
DECL|macro|C_INT_MOD_NONE
mdefine_line|#define C_INT_MOD_NONE                 1
DECL|macro|C_INT_MOD_STATIC
mdefine_line|#define C_INT_MOD_STATIC               2
DECL|macro|C_INT_MOD_DYNAMIC
mdefine_line|#define C_INT_MOD_DYNAMIC              4
DECL|macro|C_CLK_FREQ_GENESIS
mdefine_line|#define C_CLK_FREQ_GENESIS      53215000 /* shorter: 53.125 MHz  */
DECL|macro|C_CLK_FREQ_YUKON
mdefine_line|#define C_CLK_FREQ_YUKON        78215000 /* shorter: 78.125 MHz  */
DECL|macro|C_INTS_PER_SEC_DEFAULT
mdefine_line|#define C_INTS_PER_SEC_DEFAULT      2000 
DECL|macro|C_INT_MOD_ENABLE_PERCENTAGE
mdefine_line|#define C_INT_MOD_ENABLE_PERCENTAGE   50 /* if higher 50% enable */
DECL|macro|C_INT_MOD_DISABLE_PERCENTAGE
mdefine_line|#define C_INT_MOD_DISABLE_PERCENTAGE  50 /* if lower 50% disable */
DECL|macro|C_INT_MOD_IPS_LOWER_RANGE
mdefine_line|#define C_INT_MOD_IPS_LOWER_RANGE     30
DECL|macro|C_INT_MOD_IPS_UPPER_RANGE
mdefine_line|#define C_INT_MOD_IPS_UPPER_RANGE     40000
DECL|typedef|DIM_INFO
r_typedef
r_struct
id|s_DynIrqModInfo
id|DIM_INFO
suffix:semicolon
DECL|struct|s_DynIrqModInfo
r_struct
id|s_DynIrqModInfo
(brace
DECL|member|PrevTimeVal
r_int
r_int
id|PrevTimeVal
suffix:semicolon
DECL|member|PrevSysLoad
r_int
r_int
id|PrevSysLoad
suffix:semicolon
DECL|member|PrevUsedTime
r_int
r_int
id|PrevUsedTime
suffix:semicolon
DECL|member|PrevTotalTime
r_int
r_int
id|PrevTotalTime
suffix:semicolon
DECL|member|PrevUsedDescrRatio
r_int
id|PrevUsedDescrRatio
suffix:semicolon
DECL|member|NbrProcessedDescr
r_int
id|NbrProcessedDescr
suffix:semicolon
DECL|member|PrevPort0RxIntrCts
id|SK_U64
id|PrevPort0RxIntrCts
suffix:semicolon
DECL|member|PrevPort1RxIntrCts
id|SK_U64
id|PrevPort1RxIntrCts
suffix:semicolon
DECL|member|PrevPort0TxIntrCts
id|SK_U64
id|PrevPort0TxIntrCts
suffix:semicolon
DECL|member|PrevPort1TxIntrCts
id|SK_U64
id|PrevPort1TxIntrCts
suffix:semicolon
DECL|member|ModJustEnabled
id|SK_BOOL
id|ModJustEnabled
suffix:semicolon
multiline_comment|/* Moderation just enabled yes/no */
DECL|member|MaxModIntsPerSec
r_int
id|MaxModIntsPerSec
suffix:semicolon
multiline_comment|/* Moderation Threshold */
DECL|member|MaxModIntsPerSecUpperLimit
r_int
id|MaxModIntsPerSecUpperLimit
suffix:semicolon
multiline_comment|/* Upper limit for DIM  */
DECL|member|MaxModIntsPerSecLowerLimit
r_int
id|MaxModIntsPerSecLowerLimit
suffix:semicolon
multiline_comment|/* Lower limit for DIM  */
DECL|member|MaskIrqModeration
r_int
id|MaskIrqModeration
suffix:semicolon
multiline_comment|/* ModIrqType (eg. &squot;TxRx&squot;)      */
DECL|member|DisplayStats
id|SK_BOOL
id|DisplayStats
suffix:semicolon
multiline_comment|/* Stats yes/no                 */
DECL|member|AutoSizing
id|SK_BOOL
id|AutoSizing
suffix:semicolon
multiline_comment|/* Resize DIM-timer on/off      */
DECL|member|IntModTypeSelect
r_int
id|IntModTypeSelect
suffix:semicolon
multiline_comment|/* EnableIntMod (eg. &squot;dynamic&squot;) */
DECL|member|ModTimer
id|SK_TIMER
id|ModTimer
suffix:semicolon
multiline_comment|/* just some timer */
)brace
suffix:semicolon
DECL|typedef|PER_STRM
r_typedef
r_struct
id|s_PerStrm
id|PER_STRM
suffix:semicolon
DECL|macro|SK_ALLOC_IRQ
mdefine_line|#define SK_ALLOC_IRQ&t;0x00000001
macro_line|#ifdef SK_DIAG_SUPPORT
DECL|macro|DIAG_ACTIVE
mdefine_line|#define&t;DIAG_ACTIVE&t;&t;1
DECL|macro|DIAG_NOTACTIVE
mdefine_line|#define&t;DIAG_NOTACTIVE&t;&t;0
macro_line|#endif
multiline_comment|/****************************************************************************&n; * Per board structure / Adapter Context structure:&n; *&t;Allocated within attach(9e) and freed within detach(9e).&n; *&t;Contains all &squot;per device&squot; necessary handles, flags, locks etc.:&n; */
DECL|struct|s_AC
r_struct
id|s_AC
(brace
DECL|member|GIni
id|SK_GEINIT
id|GIni
suffix:semicolon
multiline_comment|/* GE init struct */
DECL|member|Pnmi
id|SK_PNMI
id|Pnmi
suffix:semicolon
multiline_comment|/* PNMI data struct */
DECL|member|vpd
id|SK_VPD
id|vpd
suffix:semicolon
multiline_comment|/* vpd data struct */
DECL|member|Event
id|SK_QUEUE
id|Event
suffix:semicolon
multiline_comment|/* Event queue */
DECL|member|Hwt
id|SK_HWT
id|Hwt
suffix:semicolon
multiline_comment|/* Hardware Timer control struct */
DECL|member|Tim
id|SK_TIMCTRL
id|Tim
suffix:semicolon
multiline_comment|/* Software Timer control struct */
DECL|member|I2c
id|SK_I2C
id|I2c
suffix:semicolon
multiline_comment|/* I2C relevant data structure */
DECL|member|Addr
id|SK_ADDR
id|Addr
suffix:semicolon
multiline_comment|/* for Address module */
DECL|member|Csum
id|SK_CSUM
id|Csum
suffix:semicolon
multiline_comment|/* for checksum module */
DECL|member|Rlmt
id|SK_RLMT
id|Rlmt
suffix:semicolon
multiline_comment|/* for rlmt module */
DECL|member|SlowPathLock
id|spinlock_t
id|SlowPathLock
suffix:semicolon
multiline_comment|/* Normal IRQ lock */
DECL|member|PnmiStruct
id|SK_PNMI_STRUCT_DATA
id|PnmiStruct
suffix:semicolon
multiline_comment|/* structure to get all Pnmi-Data */
DECL|member|RlmtMode
r_int
id|RlmtMode
suffix:semicolon
multiline_comment|/* link check mode to set */
DECL|member|RlmtNets
r_int
id|RlmtNets
suffix:semicolon
multiline_comment|/* Number of nets */
DECL|member|IoBase
id|SK_IOC
id|IoBase
suffix:semicolon
multiline_comment|/* register set of adapter */
DECL|member|BoardLevel
r_int
id|BoardLevel
suffix:semicolon
multiline_comment|/* level of active hw init (0-2) */
DECL|member|DeviceStr
r_char
id|DeviceStr
(braket
l_int|80
)braket
suffix:semicolon
multiline_comment|/* adapter string from vpd */
DECL|member|AllocFlag
id|SK_U32
id|AllocFlag
suffix:semicolon
multiline_comment|/* flag allocation of resources */
DECL|member|PciDev
r_struct
id|pci_dev
op_star
id|PciDev
suffix:semicolon
multiline_comment|/* for access to pci config space */
DECL|member|PciDevId
id|SK_U32
id|PciDevId
suffix:semicolon
multiline_comment|/* pci device id */
DECL|member|dev
r_struct
id|SK_NET_DEVICE
op_star
id|dev
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* pointer to device struct */
DECL|member|Name
r_char
id|Name
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* driver name */
DECL|member|RxBufSize
r_int
id|RxBufSize
suffix:semicolon
multiline_comment|/* length of receive buffers */
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
multiline_comment|/* linux &squot;netstat -i&squot; statistics */
DECL|member|Index
r_int
id|Index
suffix:semicolon
multiline_comment|/* internal board index number */
multiline_comment|/* adapter RAM sizes for queues of active port */
DECL|member|RxQueueSize
r_int
id|RxQueueSize
suffix:semicolon
multiline_comment|/* memory used for receive queue */
DECL|member|TxSQueueSize
r_int
id|TxSQueueSize
suffix:semicolon
multiline_comment|/* memory used for sync. tx queue */
DECL|member|TxAQueueSize
r_int
id|TxAQueueSize
suffix:semicolon
multiline_comment|/* memory used for async. tx queue */
DECL|member|PromiscCount
r_int
id|PromiscCount
suffix:semicolon
multiline_comment|/* promiscuous mode counter  */
DECL|member|AllMultiCount
r_int
id|AllMultiCount
suffix:semicolon
multiline_comment|/* allmulticast mode counter */
DECL|member|MulticCount
r_int
id|MulticCount
suffix:semicolon
multiline_comment|/* number of different MC    */
multiline_comment|/*  addresses for this board */
multiline_comment|/*  (may be more than HW can)*/
DECL|member|HWRevision
r_int
id|HWRevision
suffix:semicolon
multiline_comment|/* Hardware revision */
DECL|member|ActivePort
r_int
id|ActivePort
suffix:semicolon
multiline_comment|/* the active XMAC port */
DECL|member|MaxPorts
r_int
id|MaxPorts
suffix:semicolon
multiline_comment|/* number of activated ports */
DECL|member|TxDescrPerRing
r_int
id|TxDescrPerRing
suffix:semicolon
multiline_comment|/* # of descriptors per tx ring */
DECL|member|RxDescrPerRing
r_int
id|RxDescrPerRing
suffix:semicolon
multiline_comment|/* # of descriptors per rx ring */
DECL|member|pDescrMem
id|caddr_t
id|pDescrMem
suffix:semicolon
multiline_comment|/* Pointer to the descriptor area */
DECL|member|pDescrMemDMA
id|dma_addr_t
id|pDescrMemDMA
suffix:semicolon
multiline_comment|/* PCI DMA address of area */
multiline_comment|/* the port structures with descriptor rings */
DECL|member|TxPort
id|TX_PORT
id|TxPort
(braket
id|SK_MAX_MACS
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|RxPort
id|RX_PORT
id|RxPort
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
DECL|member|CsOfs1
r_int
r_int
id|CsOfs1
suffix:semicolon
multiline_comment|/* for checksum calculation */
DECL|member|CsOfs2
r_int
r_int
id|CsOfs2
suffix:semicolon
multiline_comment|/* for checksum calculation */
DECL|member|CsOfs
id|SK_U32
id|CsOfs
suffix:semicolon
multiline_comment|/* for checksum calculation */
DECL|member|CheckQueue
id|SK_BOOL
id|CheckQueue
suffix:semicolon
multiline_comment|/* check event queue soon */
DECL|member|DrvCleanupTimer
id|SK_TIMER
id|DrvCleanupTimer
suffix:semicolon
multiline_comment|/* to check for pending descriptors */
DECL|member|DynIrqModInfo
id|DIM_INFO
id|DynIrqModInfo
suffix:semicolon
multiline_comment|/* all data related to DIM */
multiline_comment|/* Only for tests */
DECL|member|PortUp
r_int
id|PortUp
suffix:semicolon
DECL|member|PortDown
r_int
id|PortDown
suffix:semicolon
DECL|member|ChipsetType
r_int
id|ChipsetType
suffix:semicolon
multiline_comment|/*  Chipset family type &n;&t;&t;&t;&t;&t; *  0 == Genesis family support&n;&t;&t;&t;&t;&t; *  1 == Yukon family support&n;&t;&t;&t;&t;&t; */
macro_line|#ifdef SK_DIAG_SUPPORT
DECL|member|DiagModeActive
id|SK_U32
id|DiagModeActive
suffix:semicolon
multiline_comment|/* is diag active?&t;*/
DECL|member|DiagFlowCtrl
id|SK_BOOL
id|DiagFlowCtrl
suffix:semicolon
multiline_comment|/* for control purposes&t;*/
DECL|member|PnmiBackup
id|SK_PNMI_STRUCT_DATA
id|PnmiBackup
suffix:semicolon
multiline_comment|/* backup structure for all Pnmi-Data */
DECL|member|WasIfUp
id|SK_BOOL
id|WasIfUp
(braket
id|SK_MAX_MACS
)braket
suffix:semicolon
multiline_comment|/* for OpenClose while &n;&t;&t;&t;&t;&t;&t; * DIAG is busy with NIC &n;&t;&t;&t;&t;&t;&t; */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif /* __INC_SKDRV2ND_H */
eof
