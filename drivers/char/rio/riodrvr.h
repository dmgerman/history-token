multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: riodrvr.h&n;**&t;SID&t;&t;: 1.3&n;**&t;Last Modified&t;: 11/6/98 09:22:46&n;**&t;Retrieved&t;: 11/6/98 09:22:46&n;**&n;**  ident @(#)riodrvr.h&t;1.3&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __riodrvr_h
DECL|macro|__riodrvr_h
mdefine_line|#define __riodrvr_h
macro_line|#ifdef SCCS_LABELS
DECL|variable|_riodrvr_h_sccs_
r_static
r_char
op_star
id|_riodrvr_h_sccs_
op_assign
l_string|&quot;@(#)riodrvr.h&t;1.3&quot;
suffix:semicolon
macro_line|#endif
DECL|macro|MEMDUMP_SIZE
mdefine_line|#define MEMDUMP_SIZE&t;32
DECL|macro|HZ
mdefine_line|#define HZ&t;&t;&t;&t;100
DECL|macro|MOD_DISABLE
mdefine_line|#define&t;MOD_DISABLE&t;(RIO_NOREAD|RIO_NOWRITE|RIO_NOXPRINT)
DECL|struct|rio_info
r_struct
id|rio_info
(brace
DECL|member|mode
r_int
id|mode
suffix:semicolon
multiline_comment|/* Intr or polled, word/byte */
DECL|member|RIOIntrSem
id|spinlock_t
id|RIOIntrSem
suffix:semicolon
multiline_comment|/* Interrupt thread sem */
DECL|member|current_chan
r_int
id|current_chan
suffix:semicolon
multiline_comment|/* current channel */
DECL|member|RIOFailed
r_int
id|RIOFailed
suffix:semicolon
multiline_comment|/* Not initialised ? */
DECL|member|RIOInstallAttempts
r_int
id|RIOInstallAttempts
suffix:semicolon
multiline_comment|/* no. of rio-install() calls */
DECL|member|RIOLastPCISearch
r_int
id|RIOLastPCISearch
suffix:semicolon
multiline_comment|/* status of last search */
DECL|member|RIONumHosts
r_int
id|RIONumHosts
suffix:semicolon
multiline_comment|/* Number of RIO Hosts */
DECL|member|RIOHosts
r_struct
id|Host
op_star
id|RIOHosts
suffix:semicolon
multiline_comment|/* RIO Host values */
DECL|member|RIOPortp
r_struct
id|Port
op_star
op_star
id|RIOPortp
suffix:semicolon
multiline_comment|/* RIO port values */
multiline_comment|/*&n;** 02.03.1999 ARG - ESIL 0820 fix&n;** We no longer use RIOBootMode&n;**&n;&t;int&t;&t;&t;RIOBootMode;&t;&t;* RIO boot mode *&n;**&n;*/
DECL|member|RIOPrintDisabled
r_int
id|RIOPrintDisabled
suffix:semicolon
multiline_comment|/* RIO printing disabled ? */
DECL|member|RIOPrintLogState
r_int
id|RIOPrintLogState
suffix:semicolon
multiline_comment|/* RIO printing state ? */
DECL|member|RIOPolling
r_int
id|RIOPolling
suffix:semicolon
multiline_comment|/* Polling ? */
multiline_comment|/*&n;** 09.12.1998 ARG - ESIL 0776 part fix&n;** The &squot;RIO_QUICK_CHECK&squot; ioctl was using RIOHalted.&n;** The fix for this ESIL introduces another member (RIORtaDisCons) here to be&n;** updated in RIOConCon() - to keep track of RTA connections/disconnections.&n;** &squot;RIO_QUICK_CHECK&squot; now returns the value of RIORtaDisCons.&n;*/
DECL|member|RIOHalted
r_int
id|RIOHalted
suffix:semicolon
multiline_comment|/* halted ? */
DECL|member|RIORtaDisCons
r_int
id|RIORtaDisCons
suffix:semicolon
multiline_comment|/* RTA connections/disconnections */
DECL|member|RIOReadCheck
id|uint
id|RIOReadCheck
suffix:semicolon
multiline_comment|/* Rio read check */
DECL|member|RIONoMessage
id|uint
id|RIONoMessage
suffix:semicolon
multiline_comment|/* To display message or not */
DECL|member|RIONumBootPkts
id|uint
id|RIONumBootPkts
suffix:semicolon
multiline_comment|/* how many packets for an RTA */
DECL|member|RIOBootCount
id|uint
id|RIOBootCount
suffix:semicolon
multiline_comment|/* size of RTA code */
DECL|member|RIOBooting
id|uint
id|RIOBooting
suffix:semicolon
multiline_comment|/* count of outstanding boots */
DECL|member|RIOSystemUp
id|uint
id|RIOSystemUp
suffix:semicolon
multiline_comment|/* Booted ?? */
DECL|member|RIOCounting
id|uint
id|RIOCounting
suffix:semicolon
multiline_comment|/* for counting interrupts */
DECL|member|RIOIntCount
id|uint
id|RIOIntCount
suffix:semicolon
multiline_comment|/* # of intr since last check */
DECL|member|RIOTxCount
id|uint
id|RIOTxCount
suffix:semicolon
multiline_comment|/* number of xmit intrs  */
DECL|member|RIORxCount
id|uint
id|RIORxCount
suffix:semicolon
multiline_comment|/* number of rx intrs */
DECL|member|RIORupCount
id|uint
id|RIORupCount
suffix:semicolon
multiline_comment|/* number of rup intrs */
DECL|member|RIXTimer
r_int
id|RIXTimer
suffix:semicolon
DECL|member|RIOBufferSize
r_int
id|RIOBufferSize
suffix:semicolon
multiline_comment|/* Buffersize */
DECL|member|RIOBufferMask
r_int
id|RIOBufferMask
suffix:semicolon
multiline_comment|/* Buffersize */
DECL|member|RIOFirstMajor
r_int
id|RIOFirstMajor
suffix:semicolon
multiline_comment|/* First host card&squot;s major no */
DECL|member|RIOLastPortsMapped
id|uint
id|RIOLastPortsMapped
suffix:semicolon
multiline_comment|/* highest port number known */
DECL|member|RIOFirstPortsMapped
id|uint
id|RIOFirstPortsMapped
suffix:semicolon
multiline_comment|/* lowest port number known */
DECL|member|RIOLastPortsBooted
id|uint
id|RIOLastPortsBooted
suffix:semicolon
multiline_comment|/* highest port number running */
DECL|member|RIOFirstPortsBooted
id|uint
id|RIOFirstPortsBooted
suffix:semicolon
multiline_comment|/* lowest port number running */
DECL|member|RIOLastPortsOpened
id|uint
id|RIOLastPortsOpened
suffix:semicolon
multiline_comment|/* highest port number running */
DECL|member|RIOFirstPortsOpened
id|uint
id|RIOFirstPortsOpened
suffix:semicolon
multiline_comment|/* lowest port number running */
multiline_comment|/* Flag to say that the topology information has been changed. */
DECL|member|RIOQuickCheck
id|uint
id|RIOQuickCheck
suffix:semicolon
DECL|member|CdRegister
id|uint
id|CdRegister
suffix:semicolon
multiline_comment|/* ??? */
DECL|member|RIOSignalProcess
r_int
id|RIOSignalProcess
suffix:semicolon
multiline_comment|/* Signalling process */
DECL|member|rio_debug
r_int
id|rio_debug
suffix:semicolon
multiline_comment|/* To debug ... */
DECL|member|RIODebugWait
r_int
id|RIODebugWait
suffix:semicolon
multiline_comment|/* For what ??? */
DECL|member|tpri
r_int
id|tpri
suffix:semicolon
multiline_comment|/* Thread prio */
DECL|member|tid
r_int
id|tid
suffix:semicolon
multiline_comment|/* Thread id */
DECL|member|_RIO_Polled
id|uint
id|_RIO_Polled
suffix:semicolon
multiline_comment|/* Counter for polling */
DECL|member|_RIO_Interrupted
id|uint
id|_RIO_Interrupted
suffix:semicolon
multiline_comment|/* Counter for interrupt */
DECL|member|intr_tid
r_int
id|intr_tid
suffix:semicolon
multiline_comment|/* iointset return value */
DECL|member|TxEnSem
r_int
id|TxEnSem
suffix:semicolon
multiline_comment|/* TxEnable Semaphore */
DECL|member|RIOError
r_struct
id|Error
id|RIOError
suffix:semicolon
multiline_comment|/* to Identify what went wrong */
DECL|member|RIOConf
r_struct
id|Conf
id|RIOConf
suffix:semicolon
multiline_comment|/* Configuration ??? */
DECL|member|channel
r_struct
id|ttystatics
id|channel
(braket
id|RIO_PORTS
)braket
suffix:semicolon
multiline_comment|/* channel information */
DECL|member|RIOBootPackets
r_char
id|RIOBootPackets
(braket
l_int|1
op_plus
(paren
id|SIXTY_FOUR_K
op_div
id|RTA_BOOT_DATA_SIZE
)paren
)braket
(braket
id|RTA_BOOT_DATA_SIZE
)braket
suffix:semicolon
DECL|member|RIOConnectTable
r_struct
id|Map
id|RIOConnectTable
(braket
id|TOTAL_MAP_ENTRIES
)braket
suffix:semicolon
DECL|member|RIOSavedTable
r_struct
id|Map
id|RIOSavedTable
(braket
id|TOTAL_MAP_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* RTA to host binding table for master/slave operation */
DECL|member|RIOBindTab
id|ulong
id|RIOBindTab
(braket
id|MAX_RTA_BINDINGS
)braket
suffix:semicolon
multiline_comment|/* RTA memory dump variable */
DECL|member|RIOMemDump
id|uchar
id|RIOMemDump
(braket
id|MEMDUMP_SIZE
)braket
suffix:semicolon
DECL|member|RIOModuleTypes
r_struct
id|ModuleInfo
id|RIOModuleTypes
(braket
id|MAX_MODULE_TYPES
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef linux
DECL|macro|debug
mdefine_line|#define debug(x)        printk x
macro_line|#else
DECL|macro|debug
mdefine_line|#define debug(x)&t;kkprintf x
macro_line|#endif
DECL|macro|RIO_RESET_INT
mdefine_line|#define RIO_RESET_INT&t;0x7d80
DECL|macro|WRBYTE
mdefine_line|#define WRBYTE(x,y)&t;&t;*(volatile unsigned char *)((x)) = &bslash;&n;&t;&t;&t;&t;&t;(unsigned char)(y)
macro_line|#endif&t;/* __riodrvr.h */
eof
