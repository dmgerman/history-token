multiline_comment|/******************************************************************************&n; *&n; * Name:&t;skdrv2nd.h&n; * Project:&t;GEnesis, PCI Gigabit Ethernet Adapter&n; * Version:&t;$Revision: 1.12.2.1 $&n; * Date:&t;$Date: 2001/03/12 16:50:59 $&n; * Purpose:&t;Second header file for driver and all other modules&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; *&t;(C)Copyright 1998-2001 SysKonnect,&n; *&t;a business unit of Schneider &amp; Koch &amp; Co. Datensysteme GmbH.&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;The information in this file is provided &quot;AS IS&quot; without warranty.&n; *&n; ******************************************************************************/
multiline_comment|/******************************************************************************&n; *&n; * History:&n; *&n; *&t;$Log: skdrv2nd.h,v $&n; *&t;Revision 1.12.2.1  2001/03/12 16:50:59  mlindner&n; *&t;chg: kernel 2.4 adaption&n; *&t;&n; *&t;Revision 1.12  2001/03/01 12:52:15  mlindner&n; *&t;Fixed ring size&n; *&n; *&t;Revision 1.11  2001/02/19 13:28:02  mlindner&n; *&t;Changed PNMI parameter values&n; *&n; *&t;Revision 1.10  2001/01/22 14:16:04  mlindner&n; *&t;added ProcFs functionality&n; *&t;Dual Net functionality integrated&n; *&t;Rlmt networks added&n; *&n; *&t;Revision 1.1  2000/10/05 19:46:50  phargrov&n; *&t;Add directory src/vipk_devs_nonlbl/vipk_sk98lin/&n; *&t;This is the SysKonnect SK-98xx Gigabit Ethernet driver,&n; *&t;contributed by SysKonnect.&n; *&n; *&t;Revision 1.9  2000/02/21 10:39:55  cgoos&n; *&t;Added flag for jumbo support usage.&n; *&n; *&t;Revision 1.8  1999/11/22 13:50:44  cgoos&n; *&t;Changed license header to GPL.&n; *&t;Fixed two comments.&n; *&n; *&t;Revision 1.7  1999/09/28 12:38:21  cgoos&n; *&t;Added CheckQueue to SK_AC.&n; *&t;&n; *&t;Revision 1.6  1999/07/27 08:04:05  cgoos&n; *&t;Added checksumming variables to SK_AC.&n; *&t;&n; *&t;Revision 1.5  1999/03/29 12:33:26  cgoos&n; *&t;Rreversed to fine lock granularity.&n; *&t;&n; *&t;Revision 1.4  1999/03/15 12:14:02  cgoos&n; *&t;Added DriverLock to SK_AC.&n; *&t;Removed other locks.&n; *&t;&n; *&t;Revision 1.3  1999/03/01 08:52:27  cgoos&n; *&t;Changed pAC-&gt;PciDev declaration.&n; *&t;&n; *&t;Revision 1.2  1999/02/18 10:57:14  cgoos&n; *&t;Removed SkDrvTimeStamp prototype.&n; *&t;Fixed SkGeOsGetTime prototype.&n; *&t;&n; *&t;Revision 1.1  1999/02/16 07:41:01  cgoos&n; *&t;First version.&n; *&t;&n; *&t;&n; *&n; ******************************************************************************/
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
multiline_comment|/* global function prototypes ******************************************/
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
multiline_comment|/*&n; * ioctl definitions&n; */
DECL|macro|SK_IOCTL_BASE
mdefine_line|#define&t;&t;SK_IOCTL_BASE&t;&t;(SIOCDEVPRIVATE)
DECL|macro|SK_IOCTL_GETMIB
mdefine_line|#define&t;&t;SK_IOCTL_GETMIB&t;&t;(SK_IOCTL_BASE + 0)
DECL|macro|SK_IOCTL_SETMIB
mdefine_line|#define&t;&t;SK_IOCTL_SETMIB&t;&t;(SK_IOCTL_BASE + 1)
DECL|macro|SK_IOCTL_PRESETMIB
mdefine_line|#define&t;&t;SK_IOCTL_PRESETMIB&t;(SK_IOCTL_BASE + 2)
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
mdefine_line|#define DESCR_ALIGN&t;8
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
multiline_comment|/* Time stamp from XMAX */
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
DECL|member|TcpSumStWr
id|SK_U32
id|TcpSumStWr
suffix:semicolon
multiline_comment|/* TCP Sum Start / TCP Sum Write */
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
multiline_comment|/* definition of flags in descriptor control field */
DECL|macro|RX_CTRL_OWN_BMU
mdefine_line|#define&t;RX_CTRL_OWN_BMU &t;UINT32_C(0x80000000)
DECL|macro|RX_CTRL_STF
mdefine_line|#define&t;RX_CTRL_STF&t;&t;UINT32_C(0x40000000)
DECL|macro|RX_CTRL_EOF
mdefine_line|#define&t;RX_CTRL_EOF&t;&t;UINT32_C(0x20000000)
DECL|macro|RX_CTRL_EOB_IRQ
mdefine_line|#define&t;RX_CTRL_EOB_IRQ&t;&t;UINT32_C(0x10000000)
DECL|macro|RX_CTRL_EOF_IRQ
mdefine_line|#define&t;RX_CTRL_EOF_IRQ&t;&t;UINT32_C(0x08000000)
DECL|macro|RX_CTRL_DEV_NULL
mdefine_line|#define RX_CTRL_DEV_NULL&t;UINT32_C(0x04000000)
DECL|macro|RX_CTRL_STAT_VALID
mdefine_line|#define RX_CTRL_STAT_VALID&t;UINT32_C(0x02000000)
DECL|macro|RX_CTRL_TIME_VALID
mdefine_line|#define RX_CTRL_TIME_VALID&t;UINT32_C(0x01000000)
DECL|macro|RX_CTRL_CHECK_DEFAULT
mdefine_line|#define RX_CTRL_CHECK_DEFAULT&t;UINT32_C(0x00550000)
DECL|macro|RX_CTRL_CHECK_CSUM
mdefine_line|#define RX_CTRL_CHECK_CSUM&t;UINT32_C(0x00560000)
DECL|macro|RX_CTRL_LEN_MASK
mdefine_line|#define&t;RX_CTRL_LEN_MASK&t;UINT32_C(0x0000FFFF)
DECL|macro|TX_CTRL_OWN_BMU
mdefine_line|#define&t;TX_CTRL_OWN_BMU &t;UINT32_C(0x80000000)
DECL|macro|TX_CTRL_STF
mdefine_line|#define&t;TX_CTRL_STF&t;&t;UINT32_C(0x40000000)
DECL|macro|TX_CTRL_EOF
mdefine_line|#define&t;TX_CTRL_EOF&t;&t;UINT32_C(0x20000000)
DECL|macro|TX_CTRL_EOB_IRQ
mdefine_line|#define&t;TX_CTRL_EOB_IRQ&t;&t;UINT32_C(0x10000000)
DECL|macro|TX_CTRL_EOF_IRQ
mdefine_line|#define&t;TX_CTRL_EOF_IRQ&t;&t;UINT32_C(0x08000000)
DECL|macro|TX_CTRL_ST_FWD
mdefine_line|#define TX_CTRL_ST_FWD&t;&t;UINT32_C(0x04000000)
DECL|macro|TX_CTRL_DISAB_CRC
mdefine_line|#define TX_CTRL_DISAB_CRC&t;UINT32_C(0x02000000)
DECL|macro|TX_CTRL_SOFTWARE
mdefine_line|#define TX_CTRL_SOFTWARE&t;UINT32_C(0x01000000)
DECL|macro|TX_CTRL_CHECK_DEFAULT
mdefine_line|#define TX_CTRL_CHECK_DEFAULT&t;UINT32_C(0x00550000)
DECL|macro|TX_CTRL_CHECK_CSUM
mdefine_line|#define TX_CTRL_CHECK_CSUM&t;UINT32_C(0x00560000)
DECL|macro|TX_CTRL_LEN_MASK
mdefine_line|#define&t;TX_CTRL_LEN_MASK&t;UINT32_C(0x0000FFFF)
multiline_comment|/* The offsets of registers in the TX and RX queue control io area ***********/
DECL|macro|RX_Q_BUF_CTRL_CNT
mdefine_line|#define RX_Q_BUF_CTRL_CNT&t;0x00
DECL|macro|RX_Q_NEXT_DESCR_LOW
mdefine_line|#define RX_Q_NEXT_DESCR_LOW&t;0x04
DECL|macro|RX_Q_BUF_ADDR_LOW
mdefine_line|#define RX_Q_BUF_ADDR_LOW&t;0x08
DECL|macro|RX_Q_BUF_ADDR_HIGH
mdefine_line|#define RX_Q_BUF_ADDR_HIGH&t;0x0c
DECL|macro|RX_Q_FRAME_STAT
mdefine_line|#define RX_Q_FRAME_STAT&t;&t;0x10
DECL|macro|RX_Q_TIME_STAMP
mdefine_line|#define RX_Q_TIME_STAMP&t;&t;0x14
DECL|macro|RX_Q_CSUM_1_2
mdefine_line|#define RX_Q_CSUM_1_2&t;&t;0x18
DECL|macro|RX_Q_CSUM_START_1_2
mdefine_line|#define RX_Q_CSUM_START_1_2&t;0x1c
DECL|macro|RX_Q_CUR_DESCR_LOW
mdefine_line|#define RX_Q_CUR_DESCR_LOW&t;0x20
DECL|macro|RX_Q_DESCR_HIGH
mdefine_line|#define RX_Q_DESCR_HIGH&t;&t;0x24
DECL|macro|RX_Q_CUR_ADDR_LOW
mdefine_line|#define RX_Q_CUR_ADDR_LOW&t;0x28
DECL|macro|RX_Q_CUR_ADDR_HIGH
mdefine_line|#define RX_Q_CUR_ADDR_HIGH&t;0x2c
DECL|macro|RX_Q_CUR_BYTE_CNT
mdefine_line|#define RX_Q_CUR_BYTE_CNT&t;0x30
DECL|macro|RX_Q_CTRL
mdefine_line|#define RX_Q_CTRL&t;&t;0x34
DECL|macro|RX_Q_FLAG
mdefine_line|#define RX_Q_FLAG&t;&t;0x38
DECL|macro|RX_Q_TEST1
mdefine_line|#define RX_Q_TEST1&t;&t;0x3c
DECL|macro|RX_Q_TEST2
mdefine_line|#define RX_Q_TEST2&t;&t;0x40
DECL|macro|RX_Q_TEST3
mdefine_line|#define RX_Q_TEST3&t;&t;0x44
DECL|macro|TX_Q_BUF_CTRL_CNT
mdefine_line|#define TX_Q_BUF_CTRL_CNT&t;0x00
DECL|macro|TX_Q_NEXT_DESCR_LOW
mdefine_line|#define TX_Q_NEXT_DESCR_LOW&t;0x04
DECL|macro|TX_Q_BUF_ADDR_LOW
mdefine_line|#define TX_Q_BUF_ADDR_LOW&t;0x08
DECL|macro|TX_Q_BUF_ADDR_HIGH
mdefine_line|#define TX_Q_BUF_ADDR_HIGH&t;0x0c
DECL|macro|TX_Q_FRAME_STAT
mdefine_line|#define TX_Q_FRAME_STAT&t;&t;0x10
DECL|macro|TX_Q_CSUM_START
mdefine_line|#define TX_Q_CSUM_START&t;&t;0x14
DECL|macro|TX_Q_CSUM_START_POS
mdefine_line|#define TX_Q_CSUM_START_POS&t;0x18
DECL|macro|TX_Q_RESERVED
mdefine_line|#define TX_Q_RESERVED&t;&t;0x1c
DECL|macro|TX_Q_CUR_DESCR_LOW
mdefine_line|#define TX_Q_CUR_DESCR_LOW&t;0x20
DECL|macro|TX_Q_DESCR_HIGH
mdefine_line|#define TX_Q_DESCR_HIGH&t;&t;0x24
DECL|macro|TX_Q_CUR_ADDR_LOW
mdefine_line|#define TX_Q_CUR_ADDR_LOW&t;0x28
DECL|macro|TX_Q_CUR_ADDR_HIGH
mdefine_line|#define TX_Q_CUR_ADDR_HIGH&t;0x2c
DECL|macro|TX_Q_CUR_BYTE_CNT
mdefine_line|#define TX_Q_CUR_BYTE_CNT&t;0x30
DECL|macro|TX_Q_CTRL
mdefine_line|#define TX_Q_CTRL&t;&t;0x34
DECL|macro|TX_Q_FLAG
mdefine_line|#define TX_Q_FLAG&t;&t;0x38
DECL|macro|TX_Q_TEST1
mdefine_line|#define TX_Q_TEST1&t;&t;0x3c
DECL|macro|TX_Q_TEST2
mdefine_line|#define TX_Q_TEST2&t;&t;0x40
DECL|macro|TX_Q_TEST3
mdefine_line|#define TX_Q_TEST3&t;&t;0x44
multiline_comment|/* definition of flags in the queue control field */
DECL|macro|RX_Q_CTRL_POLL_ON
mdefine_line|#define RX_Q_CTRL_POLL_ON&t;0x00000080
DECL|macro|RX_Q_CTRL_POLL_OFF
mdefine_line|#define RX_Q_CTRL_POLL_OFF&t;0x00000040
DECL|macro|RX_Q_CTRL_STOP
mdefine_line|#define RX_Q_CTRL_STOP&t;&t;0x00000020
DECL|macro|RX_Q_CTRL_START
mdefine_line|#define RX_Q_CTRL_START&t;&t;0x00000010
DECL|macro|RX_Q_CTRL_CLR_I_PAR
mdefine_line|#define RX_Q_CTRL_CLR_I_PAR&t;0x00000008
DECL|macro|RX_Q_CTRL_CLR_I_EOB
mdefine_line|#define RX_Q_CTRL_CLR_I_EOB&t;0x00000004
DECL|macro|RX_Q_CTRL_CLR_I_EOF
mdefine_line|#define RX_Q_CTRL_CLR_I_EOF&t;0x00000002
DECL|macro|RX_Q_CTRL_CLR_I_ERR
mdefine_line|#define RX_Q_CTRL_CLR_I_ERR&t;0x00000001
DECL|macro|TX_Q_CTRL_POLL_ON
mdefine_line|#define TX_Q_CTRL_POLL_ON&t;0x00000080
DECL|macro|TX_Q_CTRL_POLL_OFF
mdefine_line|#define TX_Q_CTRL_POLL_OFF&t;0x00000040
DECL|macro|TX_Q_CTRL_STOP
mdefine_line|#define TX_Q_CTRL_STOP&t;&t;0x00000020
DECL|macro|TX_Q_CTRL_START
mdefine_line|#define TX_Q_CTRL_START&t;&t;0x00000010
DECL|macro|TX_Q_CTRL_CLR_I_EOB
mdefine_line|#define TX_Q_CTRL_CLR_I_EOB&t;0x00000004
DECL|macro|TX_Q_CTRL_CLR_I_EOF
mdefine_line|#define TX_Q_CTRL_CLR_I_EOF&t;0x00000002
DECL|macro|TX_Q_CTRL_CLR_I_ERR
mdefine_line|#define TX_Q_CTRL_CLR_I_ERR&t;0x00000001
multiline_comment|/* Interrupt bits in the interrupts source register **************************/
DECL|macro|IRQ_HW_ERROR
mdefine_line|#define IRQ_HW_ERROR&t;&t;0x80000000
DECL|macro|IRQ_RESERVED
mdefine_line|#define IRQ_RESERVED&t;&t;0x40000000
DECL|macro|IRQ_PKT_TOUT_RX1
mdefine_line|#define IRQ_PKT_TOUT_RX1&t;0x20000000
DECL|macro|IRQ_PKT_TOUT_RX2
mdefine_line|#define IRQ_PKT_TOUT_RX2&t;0x10000000
DECL|macro|IRQ_PKT_TOUT_TX1
mdefine_line|#define IRQ_PKT_TOUT_TX1&t;0x08000000
DECL|macro|IRQ_PKT_TOUT_TX2
mdefine_line|#define IRQ_PKT_TOUT_TX2&t;0x04000000
DECL|macro|IRQ_I2C_READY
mdefine_line|#define IRQ_I2C_READY&t;&t;0x02000000
DECL|macro|IRQ_SW
mdefine_line|#define IRQ_SW&t;&t;&t;0x01000000
DECL|macro|IRQ_EXTERNAL_REG
mdefine_line|#define IRQ_EXTERNAL_REG&t;0x00800000
DECL|macro|IRQ_TIMER
mdefine_line|#define IRQ_TIMER&t;&t;0x00400000
DECL|macro|IRQ_MAC1
mdefine_line|#define IRQ_MAC1&t;&t;0x00200000
DECL|macro|IRQ_LINK_SYNC_C_M1
mdefine_line|#define IRQ_LINK_SYNC_C_M1&t;0x00100000
DECL|macro|IRQ_MAC2
mdefine_line|#define IRQ_MAC2&t;&t;0x00080000
DECL|macro|IRQ_LINK_SYNC_C_M2
mdefine_line|#define IRQ_LINK_SYNC_C_M2&t;0x00040000
DECL|macro|IRQ_EOB_RX1
mdefine_line|#define IRQ_EOB_RX1&t;&t;0x00020000
DECL|macro|IRQ_EOF_RX1
mdefine_line|#define IRQ_EOF_RX1&t;&t;0x00010000
DECL|macro|IRQ_CHK_RX1
mdefine_line|#define IRQ_CHK_RX1&t;&t;0x00008000
DECL|macro|IRQ_EOB_RX2
mdefine_line|#define IRQ_EOB_RX2&t;&t;0x00004000
DECL|macro|IRQ_EOF_RX2
mdefine_line|#define IRQ_EOF_RX2&t;&t;0x00002000
DECL|macro|IRQ_CHK_RX2
mdefine_line|#define IRQ_CHK_RX2&t;&t;0x00001000
DECL|macro|IRQ_EOB_SY_TX1
mdefine_line|#define IRQ_EOB_SY_TX1&t;&t;0x00000800
DECL|macro|IRQ_EOF_SY_TX1
mdefine_line|#define IRQ_EOF_SY_TX1&t;&t;0x00000400
DECL|macro|IRQ_CHK_SY_TX1
mdefine_line|#define IRQ_CHK_SY_TX1&t;&t;0x00000200
DECL|macro|IRQ_EOB_AS_TX1
mdefine_line|#define IRQ_EOB_AS_TX1&t;&t;0x00000100
DECL|macro|IRQ_EOF_AS_TX1
mdefine_line|#define IRQ_EOF_AS_TX1&t;&t;0x00000080
DECL|macro|IRQ_CHK_AS_TX1
mdefine_line|#define IRQ_CHK_AS_TX1&t;&t;0x00000040
DECL|macro|IRQ_EOB_SY_TX2
mdefine_line|#define IRQ_EOB_SY_TX2&t;&t;0x00000020
DECL|macro|IRQ_EOF_SY_TX2
mdefine_line|#define IRQ_EOF_SY_TX2&t;&t;0x00000010
DECL|macro|IRQ_CHK_SY_TX2
mdefine_line|#define IRQ_CHK_SY_TX2&t;&t;0x00000008
DECL|macro|IRQ_EOB_AS_TX2
mdefine_line|#define IRQ_EOB_AS_TX2&t;&t;0x00000004
DECL|macro|IRQ_EOF_AS_TX2
mdefine_line|#define IRQ_EOF_AS_TX2&t;&t;0x00000002
DECL|macro|IRQ_CHK_AS_TX2
mdefine_line|#define IRQ_CHK_AS_TX2&t;&t;0x00000001
DECL|macro|DRIVER_IRQS
mdefine_line|#define DRIVER_IRQS&t;(IRQ_SW | IRQ_EOF_RX1 | IRQ_EOF_RX2 | &bslash;&n;&t;&t;&t;IRQ_EOF_SY_TX1 | IRQ_EOF_AS_TX1 | &bslash;&n;&t;&t;&t;IRQ_EOF_SY_TX2 | IRQ_EOF_AS_TX2)
DECL|macro|SPECIAL_IRQS
mdefine_line|#define SPECIAL_IRQS&t;(IRQ_HW_ERROR | IRQ_PKT_TOUT_RX1 | IRQ_PKT_TOUT_RX2 | &bslash;&n;&t;&t;&t;IRQ_PKT_TOUT_TX1 | IRQ_PKT_TOUT_TX2 | &bslash;&n;&t;&t;&t;IRQ_I2C_READY | IRQ_EXTERNAL_REG | IRQ_TIMER | &bslash;&n;&t;&t;&t;IRQ_MAC1 | IRQ_LINK_SYNC_C_M1 | &bslash;&n;&t;&t;&t;IRQ_MAC2 | IRQ_LINK_SYNC_C_M2 | &bslash;&n;&t;&t;&t;IRQ_CHK_RX1 | IRQ_CHK_RX2 | &bslash;&n;&t;&t;&t;IRQ_CHK_SY_TX1 | IRQ_CHK_AS_TX1 | &bslash;&n;&t;&t;&t;IRQ_CHK_SY_TX2 | IRQ_CHK_AS_TX2)
DECL|macro|IRQ_MASK
mdefine_line|#define IRQ_MASK&t;(IRQ_SW | IRQ_EOB_RX1 | IRQ_EOF_RX1 | &bslash;&n;&t;&t;&t;IRQ_EOB_RX2 | IRQ_EOF_RX2 | &bslash;&n;&t;&t;&t;IRQ_EOB_SY_TX1 | IRQ_EOF_SY_TX1 | &bslash;&n;&t;&t;&t;IRQ_EOB_AS_TX1 | IRQ_EOF_AS_TX1 | &bslash;&n;&t;&t;&t;IRQ_EOB_SY_TX2 | IRQ_EOF_SY_TX2 | &bslash;&n;&t;&t;&t;IRQ_EOB_AS_TX2 | IRQ_EOF_AS_TX2 | &bslash;&n;&t;&t;&t;IRQ_HW_ERROR | IRQ_PKT_TOUT_RX1 | IRQ_PKT_TOUT_RX2 | &bslash;&n;&t;&t;&t;IRQ_PKT_TOUT_TX1 | IRQ_PKT_TOUT_TX2 | &bslash;&n;&t;&t;&t;IRQ_I2C_READY | IRQ_EXTERNAL_REG | IRQ_TIMER | &bslash;&n;&t;&t;&t;IRQ_MAC1 | &bslash;&n;&t;&t;&t;IRQ_MAC2 | &bslash;&n;&t;&t;&t;IRQ_CHK_RX1 | IRQ_CHK_RX2 | &bslash;&n;&t;&t;&t;IRQ_CHK_SY_TX1 | IRQ_CHK_AS_TX1 | &bslash;&n;&t;&t;&t;IRQ_CHK_SY_TX2 | IRQ_CHK_AS_TX2)
DECL|macro|IRQ_HWE_MASK
mdefine_line|#define IRQ_HWE_MASK&t;0x00000FFF /* enable all HW irqs */
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
id|caddr_t
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
id|caddr_t
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
DECL|typedef|PER_STRM
r_typedef
r_struct
id|s_PerStrm
id|PER_STRM
suffix:semicolon
DECL|macro|SK_ALLOC_IRQ
mdefine_line|#define SK_ALLOC_IRQ&t;0x00000001
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
id|net_device
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
DECL|member|Next
r_struct
id|net_device
op_star
id|Next
suffix:semicolon
multiline_comment|/* link all devices (for clearing) */
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
)brace
suffix:semicolon
macro_line|#endif /* __INC_SKDRV2ND_H */
eof
