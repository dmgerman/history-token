multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: port.h&n;**&t;SID&t;&t;: 1.3&n;**&t;Last Modified&t;: 11/6/98 11:34:12&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)port.h&t;1.3&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef&t;__rio_port_h__
DECL|macro|__rio_port_h__
mdefine_line|#define&t;__rio_port_h__
macro_line|#ifdef SCCS_LABELS
DECL|variable|_port_h_sccs_
r_static
r_char
op_star
id|_port_h_sccs_
op_assign
l_string|&quot;@(#)port.h&t;1.3&quot;
suffix:semicolon
macro_line|#endif
DECL|macro|VPIX
macro_line|#undef VPIX
multiline_comment|/*&n;** the port data structure - one per port in the system&n;*/
macro_line|#ifdef STATS
DECL|struct|RIOStats
r_struct
id|RIOStats
(brace
multiline_comment|/*&n;&t;** interrupt statistics&n;&t;*/
DECL|member|BreakIntCnt
id|uint
id|BreakIntCnt
suffix:semicolon
DECL|member|ModemOffCnt
id|uint
id|ModemOffCnt
suffix:semicolon
DECL|member|ModemOnCnt
id|uint
id|ModemOnCnt
suffix:semicolon
DECL|member|RxIntCnt
id|uint
id|RxIntCnt
suffix:semicolon
DECL|member|TxIntCnt
id|uint
id|TxIntCnt
suffix:semicolon
multiline_comment|/*&n;&t;** throughput statistics&n;&t;*/
DECL|member|RxCharCnt
id|uint
id|RxCharCnt
suffix:semicolon
DECL|member|RxPktCnt
id|uint
id|RxPktCnt
suffix:semicolon
DECL|member|RxSaveCnt
id|uint
id|RxSaveCnt
suffix:semicolon
DECL|member|TxCharCnt
id|uint
id|TxCharCnt
suffix:semicolon
DECL|member|TxPktCnt
id|uint
id|TxPktCnt
suffix:semicolon
multiline_comment|/*&n;&t;** driver entry statistics&n;&t;*/
DECL|member|CloseCnt
id|uint
id|CloseCnt
suffix:semicolon
DECL|member|IoctlCnt
id|uint
id|IoctlCnt
suffix:semicolon
DECL|member|OpenCnt
id|uint
id|OpenCnt
suffix:semicolon
DECL|member|ReadCnt
id|uint
id|ReadCnt
suffix:semicolon
DECL|member|WriteCnt
id|uint
id|WriteCnt
suffix:semicolon
multiline_comment|/*&n;&t;** proc statistics&n;&t;*/
DECL|member|BlockCnt
id|uint
id|BlockCnt
suffix:semicolon
DECL|member|OutputCnt
id|uint
id|OutputCnt
suffix:semicolon
DECL|member|ResumeCnt
id|uint
id|ResumeCnt
suffix:semicolon
DECL|member|RflushCnt
id|uint
id|RflushCnt
suffix:semicolon
DECL|member|SuspendCnt
id|uint
id|SuspendCnt
suffix:semicolon
DECL|member|TbreakCnt
id|uint
id|TbreakCnt
suffix:semicolon
DECL|member|TimeoutCnt
id|uint
id|TimeoutCnt
suffix:semicolon
DECL|member|UnblockCnt
id|uint
id|UnblockCnt
suffix:semicolon
DECL|member|WflushCnt
id|uint
id|WflushCnt
suffix:semicolon
DECL|member|WFBodgeCnt
id|uint
id|WFBodgeCnt
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;**&t;Port data structure&n;*/
DECL|struct|Port
r_struct
id|Port
(brace
DECL|member|gs
r_struct
id|gs_port
id|gs
suffix:semicolon
DECL|member|PortNum
r_int
id|PortNum
suffix:semicolon
multiline_comment|/* RIO port no., 0-511 */
DECL|member|HostP
r_struct
id|Host
op_star
id|HostP
suffix:semicolon
DECL|member|Caddr
r_volatile
id|caddr_t
id|Caddr
suffix:semicolon
DECL|member|HostPort
id|ushort
id|HostPort
suffix:semicolon
multiline_comment|/* Port number on host card */
DECL|member|RupNum
id|uchar
id|RupNum
suffix:semicolon
multiline_comment|/* Number of RUP for port */
DECL|member|ID2
id|uchar
id|ID2
suffix:semicolon
multiline_comment|/* Second ID of RTA for port */
DECL|member|State
id|ulong
id|State
suffix:semicolon
multiline_comment|/* FLAGS for open &amp; xopen */
DECL|macro|RIO_LOPEN
mdefine_line|#define&t;RIO_LOPEN&t;0x00001&t;&t;/* Local open */
DECL|macro|RIO_MOPEN
mdefine_line|#define&t;RIO_MOPEN&t;0x00002&t;&t;/* Modem open */
DECL|macro|RIO_WOPEN
mdefine_line|#define&t;RIO_WOPEN&t;0x00004&t;&t;/* Waiting for open */
DECL|macro|RIO_CLOSING
mdefine_line|#define&t;RIO_CLOSING&t;0x00008&t;&t;/* The port is being close */
DECL|macro|RIO_XPBUSY
mdefine_line|#define&t;RIO_XPBUSY&t;0x00010&t;&t;/* Transparent printer busy */
DECL|macro|RIO_BREAKING
mdefine_line|#define&t;RIO_BREAKING&t;0x00020&t;&t;/* Break in progress */
DECL|macro|RIO_DIRECT
mdefine_line|#define&t;RIO_DIRECT&t;0x00040&t;&t;/* Doing Direct output */
DECL|macro|RIO_EXCLUSIVE
mdefine_line|#define&t;RIO_EXCLUSIVE&t;0x00080&t;&t;/* Stream open for exclusive use */
DECL|macro|RIO_NDELAY
mdefine_line|#define&t;RIO_NDELAY&t;0x00100&t;&t;/* Stream is open FNDELAY */
DECL|macro|RIO_CARR_ON
mdefine_line|#define&t;RIO_CARR_ON&t;0x00200&t;&t;/* Stream has carrier present */
DECL|macro|RIO_XPWANTR
mdefine_line|#define&t;RIO_XPWANTR&t;0x00400&t;&t;/* Stream wanted by Xprint */
DECL|macro|RIO_RBLK
mdefine_line|#define&t;RIO_RBLK&t;0x00800&t;&t;/* Stream is read-blocked */
DECL|macro|RIO_BUSY
mdefine_line|#define&t;RIO_BUSY&t;0x01000&t;&t;/* Stream is BUSY for write */
DECL|macro|RIO_TIMEOUT
mdefine_line|#define&t;RIO_TIMEOUT&t;0x02000&t;&t;/* Stream timeout in progress */
DECL|macro|RIO_TXSTOP
mdefine_line|#define&t;RIO_TXSTOP&t;0x04000&t;&t;/* Stream output is stopped */
DECL|macro|RIO_WAITFLUSH
mdefine_line|#define&t;RIO_WAITFLUSH&t;0x08000&t;&t;/* Stream waiting for flush */
DECL|macro|RIO_DYNOROD
mdefine_line|#define&t;RIO_DYNOROD&t;0x10000&t;&t;/* Drain failed */
DECL|macro|RIO_DELETED
mdefine_line|#define&t;RIO_DELETED&t;0x20000&t;&t;/* RTA has been deleted */
DECL|macro|RIO_ISSCANCODE
mdefine_line|#define RIO_ISSCANCODE&t;0x40000&t;&t;/* This line is in scancode mode */
DECL|macro|RIO_USING_EUC
mdefine_line|#define&t;RIO_USING_EUC&t;0x100000&t;/* Using extended Unix chars */
DECL|macro|RIO_CAN_COOK
mdefine_line|#define&t;RIO_CAN_COOK&t;0x200000&t;/* This line can do cooking */
DECL|macro|RIO_TRIAD_MODE
mdefine_line|#define RIO_TRIAD_MODE  0x400000        /* Enable TRIAD special ops. */
DECL|macro|RIO_TRIAD_BLOCK
mdefine_line|#define RIO_TRIAD_BLOCK 0x800000        /* Next read will block */
DECL|macro|RIO_TRIAD_FUNC
mdefine_line|#define RIO_TRIAD_FUNC  0x1000000       /* Seen a function key coming in */
DECL|macro|RIO_THROTTLE_RX
mdefine_line|#define RIO_THROTTLE_RX 0x2000000       /* RX needs to be throttled. */
DECL|member|Config
id|ulong
id|Config
suffix:semicolon
multiline_comment|/* FLAGS for NOREAD.... */
DECL|macro|RIO_NOREAD
mdefine_line|#define&t;RIO_NOREAD&t;0x0001&t;&t;/* Are not allowed to read port */
DECL|macro|RIO_NOWRITE
mdefine_line|#define&t;RIO_NOWRITE&t;0x0002&t;&t;/* Are not allowed to write port */
DECL|macro|RIO_NOXPRINT
mdefine_line|#define&t;RIO_NOXPRINT&t;0x0004&t;&t;/* Are not allowed to xprint port */
DECL|macro|RIO_NOMASK
mdefine_line|#define&t;RIO_NOMASK&t;0x0007&t;&t;/* All not allowed things */
DECL|macro|RIO_IXANY
mdefine_line|#define RIO_IXANY&t;0x0008          /* Port is allowed ixany */
DECL|macro|RIO_MODEM
mdefine_line|#define&t;RIO_MODEM&t;0x0010&t;&t;/* Stream is a modem device */
DECL|macro|RIO_IXON
mdefine_line|#define&t;RIO_IXON&t;0x0020&t;&t;/* Port is allowed ixon */
DECL|macro|RIO_WAITDRAIN
mdefine_line|#define RIO_WAITDRAIN&t;0x0040&t;&t;/* Wait for port to completely drain */
DECL|macro|RIO_MAP_50_TO_50
mdefine_line|#define RIO_MAP_50_TO_50&t;0x0080&t;/* Map 50 baud to 50 baud */
DECL|macro|RIO_MAP_110_TO_110
mdefine_line|#define RIO_MAP_110_TO_110&t;0x0100&t;/* Map 110 baud to 110 baud */
multiline_comment|/*&n;** 15.10.1998 ARG - ESIL 0761 prt fix&n;** As LynxOS does not appear to support Hardware Flow Control .....&n;** Define our own flow control flags in &squot;Config&squot;.&n;*/
DECL|macro|RIO_CTSFLOW
mdefine_line|#define RIO_CTSFLOW&t;0x0200&t;&t;/* RIO&squot;s own CTSFLOW flag */
DECL|macro|RIO_RTSFLOW
mdefine_line|#define RIO_RTSFLOW&t;0x0400&t;&t;/* RIO&squot;s own RTSFLOW flag */
DECL|member|PhbP
r_struct
id|PHB
op_star
id|PhbP
suffix:semicolon
multiline_comment|/* pointer to PHB for port */
DECL|member|TxAdd
id|WORD
op_star
id|TxAdd
suffix:semicolon
multiline_comment|/* Add packets here */
DECL|member|TxStart
id|WORD
op_star
id|TxStart
suffix:semicolon
multiline_comment|/* Start of add array */
DECL|member|TxEnd
id|WORD
op_star
id|TxEnd
suffix:semicolon
multiline_comment|/* End of add array */
DECL|member|RxRemove
id|WORD
op_star
id|RxRemove
suffix:semicolon
multiline_comment|/* Remove packets here */
DECL|member|RxStart
id|WORD
op_star
id|RxStart
suffix:semicolon
multiline_comment|/* Start of remove array */
DECL|member|RxEnd
id|WORD
op_star
id|RxEnd
suffix:semicolon
multiline_comment|/* End of remove array */
DECL|member|RtaUniqueNum
id|uint
id|RtaUniqueNum
suffix:semicolon
multiline_comment|/* Unique number of RTA */
DECL|member|PortState
id|ushort
id|PortState
suffix:semicolon
multiline_comment|/* status of port */
DECL|member|ModemState
id|ushort
id|ModemState
suffix:semicolon
multiline_comment|/* status of modem lines */
DECL|member|ModemLines
id|ulong
id|ModemLines
suffix:semicolon
multiline_comment|/* Modem bits sent to RTA */
DECL|member|CookMode
id|uchar
id|CookMode
suffix:semicolon
multiline_comment|/* who expands CR/LF? */
DECL|member|ParamSem
id|uchar
id|ParamSem
suffix:semicolon
multiline_comment|/* Prevent write during param */
DECL|member|Mapped
id|uchar
id|Mapped
suffix:semicolon
multiline_comment|/* if port mapped onto host */
DECL|member|SecondBlock
id|uchar
id|SecondBlock
suffix:semicolon
multiline_comment|/* if port belongs to 2nd block&n;&t;&t;&t;&t;&t;&t;   of 16 port RTA */
DECL|member|InUse
id|uchar
id|InUse
suffix:semicolon
multiline_comment|/* how many pre-emptive cmds */
DECL|member|Lock
id|uchar
id|Lock
suffix:semicolon
multiline_comment|/* if params locked */
DECL|member|Store
id|uchar
id|Store
suffix:semicolon
multiline_comment|/* if params stored across closes */
DECL|member|FirstOpen
id|uchar
id|FirstOpen
suffix:semicolon
multiline_comment|/* TRUE if first time port opened */
DECL|member|FlushCmdBodge
id|uchar
id|FlushCmdBodge
suffix:semicolon
multiline_comment|/* if doing a (non)flush */
DECL|member|MagicFlags
id|uchar
id|MagicFlags
suffix:semicolon
multiline_comment|/* require intr processing */
DECL|macro|MAGIC_FLUSH
mdefine_line|#define&t;MAGIC_FLUSH&t;0x01&t;/* mirror of WflushFlag */
DECL|macro|MAGIC_REBOOT
mdefine_line|#define&t;MAGIC_REBOOT&t;0x02&t;/* RTA re-booted, re-open ports */
DECL|macro|MORE_OUTPUT_EYGOR
mdefine_line|#define&t;MORE_OUTPUT_EYGOR 0x04&t;/* riotproc failed to empty clists */
DECL|member|WflushFlag
id|uchar
id|WflushFlag
suffix:semicolon
multiline_comment|/* 1 How many WFLUSHs active */
multiline_comment|/*&n;** Transparent print stuff&n;*/
DECL|struct|Xprint
r_struct
id|Xprint
(brace
macro_line|#ifndef MAX_XP_CTRL_LEN
DECL|macro|MAX_XP_CTRL_LEN
mdefine_line|#define MAX_XP_CTRL_LEN&t;&t;16&t;&t;/* ALSO IN DAEMON.H */
macro_line|#endif
DECL|member|XpCps
id|uint
id|XpCps
suffix:semicolon
DECL|member|XpOn
r_char
id|XpOn
(braket
id|MAX_XP_CTRL_LEN
)braket
suffix:semicolon
DECL|member|XpOff
r_char
id|XpOff
(braket
id|MAX_XP_CTRL_LEN
)braket
suffix:semicolon
DECL|member|XpLen
id|ushort
id|XpLen
suffix:semicolon
multiline_comment|/* strlen(XpOn)+strlen(XpOff) */
DECL|member|XpActive
id|uchar
id|XpActive
suffix:semicolon
DECL|member|XpLastTickOk
id|uchar
id|XpLastTickOk
suffix:semicolon
multiline_comment|/* TRUE if we can process */
DECL|macro|XP_OPEN
mdefine_line|#define&t;XP_OPEN&t;&t;00001
DECL|macro|XP_RUNABLE
mdefine_line|#define&t;XP_RUNABLE&t;00002
DECL|member|XttyP
r_struct
id|ttystatics
op_star
id|XttyP
suffix:semicolon
DECL|member|Xprint
)brace
id|Xprint
suffix:semicolon
macro_line|#ifdef VPIX
DECL|member|StashP
id|v86_t
op_star
id|StashP
suffix:semicolon
DECL|member|IntMask
id|uint
id|IntMask
suffix:semicolon
DECL|member|VpixSs
r_struct
id|termss
id|VpixSs
suffix:semicolon
DECL|member|ModemStatusReg
id|uchar
id|ModemStatusReg
suffix:semicolon
multiline_comment|/* Modem status register */
macro_line|#endif
DECL|member|RxDataStart
id|uchar
id|RxDataStart
suffix:semicolon
DECL|member|Cor2Copy
id|uchar
id|Cor2Copy
suffix:semicolon
multiline_comment|/* copy of COR2 */
DECL|member|Name
r_char
op_star
id|Name
suffix:semicolon
multiline_comment|/* points to the Rta&squot;s name */
macro_line|#ifdef STATS
DECL|member|Stat
r_struct
id|RIOStats
id|Stat
suffix:semicolon
multiline_comment|/* ports statistics */
macro_line|#endif
DECL|member|TxRingBuffer
r_char
op_star
id|TxRingBuffer
suffix:semicolon
DECL|member|TxBufferIn
id|ushort
id|TxBufferIn
suffix:semicolon
multiline_comment|/* New data arrives here */
DECL|member|TxBufferOut
id|ushort
id|TxBufferOut
suffix:semicolon
multiline_comment|/* Intr removes data here */
DECL|member|OldTxBufferOut
id|ushort
id|OldTxBufferOut
suffix:semicolon
multiline_comment|/* Indicates if draining */
DECL|member|TimeoutId
r_int
id|TimeoutId
suffix:semicolon
multiline_comment|/* Timeout ID */
DECL|member|Debug
id|uint
id|Debug
suffix:semicolon
DECL|member|WaitUntilBooted
id|uchar
id|WaitUntilBooted
suffix:semicolon
multiline_comment|/* True if open should block */
DECL|member|statsGather
id|uint
id|statsGather
suffix:semicolon
multiline_comment|/* True if gathering stats */
DECL|member|txchars
id|ulong
id|txchars
suffix:semicolon
multiline_comment|/* Chars transmitted */
DECL|member|rxchars
id|ulong
id|rxchars
suffix:semicolon
multiline_comment|/* Chars received */
DECL|member|opens
id|ulong
id|opens
suffix:semicolon
multiline_comment|/* port open count */
DECL|member|closes
id|ulong
id|closes
suffix:semicolon
multiline_comment|/* port close count */
DECL|member|ioctls
id|ulong
id|ioctls
suffix:semicolon
multiline_comment|/* ioctl count */
DECL|member|LastRxTgl
id|uchar
id|LastRxTgl
suffix:semicolon
multiline_comment|/* Last state of rx toggle bit */
DECL|member|portSem
id|spinlock_t
id|portSem
suffix:semicolon
multiline_comment|/* Lock using this sem */
DECL|member|MonitorTstate
r_int
id|MonitorTstate
suffix:semicolon
multiline_comment|/* Monitoring ? */
DECL|member|timeout_id
r_int
id|timeout_id
suffix:semicolon
multiline_comment|/* For calling 100 ms delays */
DECL|member|timeout_sem
r_int
id|timeout_sem
suffix:semicolon
multiline_comment|/* For calling 100 ms delays */
DECL|member|firstOpen
r_int
id|firstOpen
suffix:semicolon
multiline_comment|/* First time open ? */
DECL|member|p
r_char
op_star
id|p
suffix:semicolon
multiline_comment|/* save the global struc here .. */
)brace
suffix:semicolon
DECL|struct|ModuleInfo
r_struct
id|ModuleInfo
(brace
DECL|member|Name
r_char
op_star
id|Name
suffix:semicolon
DECL|member|Flags
id|uint
id|Flags
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* one per port on a module */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;** This struct is required because trying to grab an entire Port structure&n;** runs into problems with differing struct sizes between driver and config.&n;*/
DECL|struct|PortParams
r_struct
id|PortParams
(brace
DECL|member|Port
id|uint
id|Port
suffix:semicolon
DECL|member|Config
id|ulong
id|Config
suffix:semicolon
DECL|member|State
id|ulong
id|State
suffix:semicolon
DECL|member|TtyP
r_struct
id|ttystatics
op_star
id|TtyP
suffix:semicolon
)brace
suffix:semicolon
eof
