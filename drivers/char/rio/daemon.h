multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: daemon.h&n;**&t;SID&t;&t;: 1.3&n;**&t;Last Modified&t;: 11/6/98 11:34:09&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)daemon.h&t;1.3&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef&t;__rio_daemon_h__
DECL|macro|__rio_daemon_h__
mdefine_line|#define&t;__rio_daemon_h__
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
DECL|variable|_daemon_h_sccs_
r_static
r_char
op_star
id|_daemon_h_sccs_
op_assign
l_string|&quot;@(#)daemon.h&t;1.3&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;** structures used on /dev/rio&n;*/
DECL|struct|Error
r_struct
id|Error
(brace
DECL|member|Error
id|uint
id|Error
suffix:semicolon
DECL|member|Entry
id|uint
id|Entry
suffix:semicolon
DECL|member|Other
id|uint
id|Other
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|DownLoad
r_struct
id|DownLoad
(brace
DECL|member|DataP
r_char
op_star
id|DataP
suffix:semicolon
DECL|member|Count
id|uint
id|Count
suffix:semicolon
DECL|member|ProductCode
id|uint
id|ProductCode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;** A few constants....&n;*/
macro_line|#ifndef MAX_VERSION_LEN
DECL|macro|MAX_VERSION_LEN
mdefine_line|#define&t;MAX_VERSION_LEN&t;256
macro_line|#endif
macro_line|#ifndef MAX_XP_CTRL_LEN
DECL|macro|MAX_XP_CTRL_LEN
mdefine_line|#define&t;MAX_XP_CTRL_LEN 16&t;&t;/* ALSO IN PORT.H */
macro_line|#endif
DECL|struct|PortSetup
r_struct
id|PortSetup
(brace
DECL|member|From
id|uint
id|From
suffix:semicolon
multiline_comment|/* Set/Clear XP &amp; IXANY Control from this port.... */
DECL|member|To
id|uint
id|To
suffix:semicolon
multiline_comment|/* .... to this port */
DECL|member|XpCps
id|uint
id|XpCps
suffix:semicolon
multiline_comment|/* at this speed */
DECL|member|XpOn
r_char
id|XpOn
(braket
id|MAX_XP_CTRL_LEN
)braket
suffix:semicolon
multiline_comment|/* this is the start string */
DECL|member|XpOff
r_char
id|XpOff
(braket
id|MAX_XP_CTRL_LEN
)braket
suffix:semicolon
multiline_comment|/* this is the stop string */
DECL|member|IxAny
id|uchar
id|IxAny
suffix:semicolon
multiline_comment|/* enable/disable IXANY */
DECL|member|IxOn
id|uchar
id|IxOn
suffix:semicolon
multiline_comment|/* enable/disable IXON */
DECL|member|Lock
id|uchar
id|Lock
suffix:semicolon
multiline_comment|/* lock port params */
DECL|member|Store
id|uchar
id|Store
suffix:semicolon
multiline_comment|/* store params across closes */
DECL|member|Drain
id|uchar
id|Drain
suffix:semicolon
multiline_comment|/* close only when drained */
)brace
suffix:semicolon
DECL|struct|LpbReq
r_struct
id|LpbReq
(brace
DECL|member|Host
id|uint
id|Host
suffix:semicolon
DECL|member|Link
id|uint
id|Link
suffix:semicolon
DECL|member|LpbP
r_struct
id|LPB
op_star
id|LpbP
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RupReq
r_struct
id|RupReq
(brace
DECL|member|HostNum
id|uint
id|HostNum
suffix:semicolon
DECL|member|RupNum
id|uint
id|RupNum
suffix:semicolon
DECL|member|RupP
r_struct
id|RUP
op_star
id|RupP
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|PortReq
r_struct
id|PortReq
(brace
DECL|member|SysPort
id|uint
id|SysPort
suffix:semicolon
DECL|member|PortP
r_struct
id|Port
op_star
id|PortP
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|StreamInfo
r_struct
id|StreamInfo
(brace
DECL|member|SysPort
id|uint
id|SysPort
suffix:semicolon
macro_line|#if 0
id|queue_t
id|RQueue
suffix:semicolon
id|queue_t
id|WQueue
suffix:semicolon
macro_line|#else
DECL|member|RQueue
r_int
id|RQueue
suffix:semicolon
DECL|member|WQueue
r_int
id|WQueue
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|HostReq
r_struct
id|HostReq
(brace
DECL|member|HostNum
id|uint
id|HostNum
suffix:semicolon
DECL|member|HostP
r_struct
id|Host
op_star
id|HostP
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|HostDpRam
r_struct
id|HostDpRam
(brace
DECL|member|HostNum
id|uint
id|HostNum
suffix:semicolon
DECL|member|DpRamP
r_struct
id|DpRam
op_star
id|DpRamP
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|DebugCtrl
r_struct
id|DebugCtrl
(brace
DECL|member|SysPort
id|uint
id|SysPort
suffix:semicolon
DECL|member|Debug
id|uint
id|Debug
suffix:semicolon
DECL|member|Wait
id|uint
id|Wait
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|MapInfo
r_struct
id|MapInfo
(brace
DECL|member|FirstPort
id|uint
id|FirstPort
suffix:semicolon
multiline_comment|/* 8 ports, starting from this (tty) number */
DECL|member|RtaUnique
id|uint
id|RtaUnique
suffix:semicolon
multiline_comment|/* reside on this RTA (unique number) */
)brace
suffix:semicolon
DECL|struct|MapIn
r_struct
id|MapIn
(brace
DECL|member|NumEntries
id|uint
id|NumEntries
suffix:semicolon
multiline_comment|/* How many port sets are we mapping? */
DECL|member|MapInfoP
r_struct
id|MapInfo
op_star
id|MapInfoP
suffix:semicolon
multiline_comment|/* Pointer to (user space) info */
)brace
suffix:semicolon
DECL|struct|SendPack
r_struct
id|SendPack
(brace
DECL|member|PortNum
r_int
r_int
id|PortNum
suffix:semicolon
DECL|member|Len
r_int
r_char
id|Len
suffix:semicolon
DECL|member|Data
r_int
r_char
id|Data
(braket
id|PKT_MAX_DATA_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|SpecialRupCmd
r_struct
id|SpecialRupCmd
(brace
DECL|member|Packet
r_struct
id|PKT
id|Packet
suffix:semicolon
DECL|member|Host
r_int
r_int
id|Host
suffix:semicolon
DECL|member|RupNum
r_int
r_int
id|RupNum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|IdentifyRta
r_struct
id|IdentifyRta
(brace
DECL|member|RtaUnique
id|ulong
id|RtaUnique
suffix:semicolon
DECL|member|ID
id|uchar
id|ID
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|KillNeighbour
r_struct
id|KillNeighbour
(brace
DECL|member|UniqueNum
id|ulong
id|UniqueNum
suffix:semicolon
DECL|member|Link
id|uchar
id|Link
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rioVersion
r_struct
id|rioVersion
(brace
DECL|member|version
r_char
id|version
(braket
id|MAX_VERSION_LEN
)braket
suffix:semicolon
DECL|member|relid
r_char
id|relid
(braket
id|MAX_VERSION_LEN
)braket
suffix:semicolon
DECL|member|buildLevel
r_int
id|buildLevel
suffix:semicolon
DECL|member|buildDate
r_char
id|buildDate
(braket
id|MAX_VERSION_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;**&t;RIOC commands are for the daemon type operations&n;**&n;** 09.12.1998 ARG - ESIL 0776 part fix&n;** Definition for &squot;RIOC&squot; also appears in rioioctl.h, so we&squot;d better do a&n;** #ifndef here first.&n;** rioioctl.h also now has #define &squot;RIO_QUICK_CHECK&squot; as this ioctl is now&n;** allowed to be used by customers.&n;*/
macro_line|#ifndef RIOC
DECL|macro|RIOC
mdefine_line|#define&t;RIOC&t;(&squot;R&squot;&lt;&lt;8)|(&squot;i&squot;&lt;&lt;16)|(&squot;o&squot;&lt;&lt;24)
macro_line|#endif
multiline_comment|/*&n;** Boot stuff&n;*/
DECL|macro|RIO_GET_TABLE
mdefine_line|#define&t;RIO_GET_TABLE     (RIOC | 100)
DECL|macro|RIO_PUT_TABLE
mdefine_line|#define RIO_PUT_TABLE     (RIOC | 101)
DECL|macro|RIO_ASSIGN_RTA
mdefine_line|#define RIO_ASSIGN_RTA    (RIOC | 102)
DECL|macro|RIO_DELETE_RTA
mdefine_line|#define RIO_DELETE_RTA    (RIOC | 103)
DECL|macro|RIO_HOST_FOAD
mdefine_line|#define&t;RIO_HOST_FOAD&t;  (RIOC | 104)
DECL|macro|RIO_QUICK_CHECK
mdefine_line|#define&t;RIO_QUICK_CHECK&t;  (RIOC | 105)
DECL|macro|RIO_SIGNALS_ON
mdefine_line|#define RIO_SIGNALS_ON    (RIOC | 106)
DECL|macro|RIO_SIGNALS_OFF
mdefine_line|#define RIO_SIGNALS_OFF   (RIOC | 107)
DECL|macro|RIO_CHANGE_NAME
mdefine_line|#define&t;RIO_CHANGE_NAME   (RIOC | 108)
DECL|macro|RIO_DOWNLOAD
mdefine_line|#define RIO_DOWNLOAD      (RIOC | 109)
DECL|macro|RIO_GET_LOG
mdefine_line|#define&t;RIO_GET_LOG&t;  (RIOC | 110)
DECL|macro|RIO_SETUP_PORTS
mdefine_line|#define&t;RIO_SETUP_PORTS   (RIOC | 111)
DECL|macro|RIO_ALL_MODEM
mdefine_line|#define RIO_ALL_MODEM     (RIOC | 112)
multiline_comment|/*&n;** card state, debug stuff&n;*/
DECL|macro|RIO_NUM_HOSTS
mdefine_line|#define&t;RIO_NUM_HOSTS&t;  (RIOC | 120)
DECL|macro|RIO_HOST_LPB
mdefine_line|#define&t;RIO_HOST_LPB&t;  (RIOC | 121)
DECL|macro|RIO_HOST_RUP
mdefine_line|#define&t;RIO_HOST_RUP&t;  (RIOC | 122)
DECL|macro|RIO_HOST_PORT
mdefine_line|#define&t;RIO_HOST_PORT&t;  (RIOC | 123)
DECL|macro|RIO_PARMS
mdefine_line|#define&t;RIO_PARMS &t;  (RIOC | 124)
DECL|macro|RIO_HOST_REQ
mdefine_line|#define RIO_HOST_REQ&t;  (RIOC | 125)
DECL|macro|RIO_READ_CONFIG
mdefine_line|#define&t;RIO_READ_CONFIG&t;  (RIOC | 126)
DECL|macro|RIO_SET_CONFIG
mdefine_line|#define&t;RIO_SET_CONFIG&t;  (RIOC | 127)
DECL|macro|RIO_VERSID
mdefine_line|#define&t;RIO_VERSID&t;  (RIOC | 128)
DECL|macro|RIO_FLAGS
mdefine_line|#define&t;RIO_FLAGS&t;  (RIOC | 129)
DECL|macro|RIO_SETDEBUG
mdefine_line|#define&t;RIO_SETDEBUG&t;  (RIOC | 130)
DECL|macro|RIO_GETDEBUG
mdefine_line|#define&t;RIO_GETDEBUG&t;  (RIOC | 131)
DECL|macro|RIO_READ_LEVELS
mdefine_line|#define&t;RIO_READ_LEVELS   (RIOC | 132)
DECL|macro|RIO_SET_FAST_BUS
mdefine_line|#define&t;RIO_SET_FAST_BUS  (RIOC | 133)
DECL|macro|RIO_SET_SLOW_BUS
mdefine_line|#define&t;RIO_SET_SLOW_BUS  (RIOC | 134)
DECL|macro|RIO_SET_BYTE_MODE
mdefine_line|#define&t;RIO_SET_BYTE_MODE (RIOC | 135)
DECL|macro|RIO_SET_WORD_MODE
mdefine_line|#define&t;RIO_SET_WORD_MODE (RIOC | 136)
DECL|macro|RIO_STREAM_INFO
mdefine_line|#define RIO_STREAM_INFO   (RIOC | 137)
DECL|macro|RIO_START_POLLER
mdefine_line|#define&t;RIO_START_POLLER  (RIOC | 138)
DECL|macro|RIO_STOP_POLLER
mdefine_line|#define&t;RIO_STOP_POLLER   (RIOC | 139)
DECL|macro|RIO_LAST_ERROR
mdefine_line|#define&t;RIO_LAST_ERROR    (RIOC | 140)
DECL|macro|RIO_TICK
mdefine_line|#define&t;RIO_TICK&t;  (RIOC | 141)
DECL|macro|RIO_TOCK
mdefine_line|#define&t;RIO_TOCK&t;  (RIOC | 241)&t;/* I did this on purpose, you know. */
DECL|macro|RIO_SEND_PACKET
mdefine_line|#define&t;RIO_SEND_PACKET   (RIOC | 142)
DECL|macro|RIO_SET_BUSY
mdefine_line|#define&t;RIO_SET_BUSY&t;  (RIOC | 143)
DECL|macro|SPECIAL_RUP_CMD
mdefine_line|#define&t;SPECIAL_RUP_CMD   (RIOC | 144)
DECL|macro|RIO_FOAD_RTA
mdefine_line|#define&t;RIO_FOAD_RTA      (RIOC | 145)
DECL|macro|RIO_ZOMBIE_RTA
mdefine_line|#define&t;RIO_ZOMBIE_RTA    (RIOC | 146)
DECL|macro|RIO_IDENTIFY_RTA
mdefine_line|#define RIO_IDENTIFY_RTA  (RIOC | 147)
DECL|macro|RIO_KILL_NEIGHBOUR
mdefine_line|#define RIO_KILL_NEIGHBOUR (RIOC | 148)
DECL|macro|RIO_DEBUG_MEM
mdefine_line|#define RIO_DEBUG_MEM     (RIOC | 149)
multiline_comment|/*&n;** 150 - 167 used.....   See below&n;*/
DECL|macro|RIO_GET_PORT_SETUP
mdefine_line|#define RIO_GET_PORT_SETUP (RIOC | 168)
DECL|macro|RIO_RESUME
mdefine_line|#define RIO_RESUME        (RIOC | 169)
DECL|macro|RIO_MESG
mdefine_line|#define&t;RIO_MESG&t;(RIOC | 170)
DECL|macro|RIO_NO_MESG
mdefine_line|#define&t;RIO_NO_MESG&t;(RIOC | 171)
DECL|macro|RIO_WHAT_MESG
mdefine_line|#define&t;RIO_WHAT_MESG&t;(RIOC | 172)
DECL|macro|RIO_HOST_DPRAM
mdefine_line|#define RIO_HOST_DPRAM&t;(RIOC | 173)
DECL|macro|RIO_MAP_B50_TO_50
mdefine_line|#define RIO_MAP_B50_TO_50&t;(RIOC | 174)
DECL|macro|RIO_MAP_B50_TO_57600
mdefine_line|#define RIO_MAP_B50_TO_57600&t;(RIOC | 175)
DECL|macro|RIO_MAP_B110_TO_110
mdefine_line|#define RIO_MAP_B110_TO_110&t;(RIOC | 176)
DECL|macro|RIO_MAP_B110_TO_115200
mdefine_line|#define RIO_MAP_B110_TO_115200&t;(RIOC | 177)
DECL|macro|RIO_GET_PORT_PARAMS
mdefine_line|#define RIO_GET_PORT_PARAMS&t;(RIOC | 178)
DECL|macro|RIO_SET_PORT_PARAMS
mdefine_line|#define RIO_SET_PORT_PARAMS&t;(RIOC | 179)
DECL|macro|RIO_GET_PORT_TTY
mdefine_line|#define RIO_GET_PORT_TTY&t;(RIOC | 180)
DECL|macro|RIO_SET_PORT_TTY
mdefine_line|#define RIO_SET_PORT_TTY&t;(RIOC | 181)
DECL|macro|RIO_SYSLOG_ONLY
mdefine_line|#define RIO_SYSLOG_ONLY&t;(RIOC | 182)
DECL|macro|RIO_SYSLOG_CONS
mdefine_line|#define RIO_SYSLOG_CONS&t;(RIOC | 183)
DECL|macro|RIO_CONS_ONLY
mdefine_line|#define RIO_CONS_ONLY&t;(RIOC | 184)
DECL|macro|RIO_BLOCK_OPENS
mdefine_line|#define RIO_BLOCK_OPENS&t;(RIOC | 185)
multiline_comment|/*&n;** 02.03.1999 ARG - ESIL 0820 fix :&n;** RIOBootMode is no longer use by the driver, so these ioctls&n;** are now obsolete :&n;**&n;#define RIO_GET_BOOT_MODE&t;(RIOC | 186)&n;#define RIO_SET_BOOT_MODE&t;(RIOC | 187)&n;**&n;*/
DECL|macro|RIO_MEM_DUMP
mdefine_line|#define RIO_MEM_DUMP&t;(RIOC | 189)
DECL|macro|RIO_READ_REGISTER
mdefine_line|#define RIO_READ_REGISTER&t;(RIOC | 190)
DECL|macro|RIO_GET_MODTYPE
mdefine_line|#define RIO_GET_MODTYPE&t;(RIOC | 191)
DECL|macro|RIO_SET_TIMER
mdefine_line|#define RIO_SET_TIMER&t;(RIOC | 192)
DECL|macro|RIO_READ_CHECK
mdefine_line|#define RIO_READ_CHECK&t;(RIOC | 196)
DECL|macro|RIO_WAITING_FOR_RESTART
mdefine_line|#define RIO_WAITING_FOR_RESTART&t;(RIOC | 197)
DECL|macro|RIO_BIND_RTA
mdefine_line|#define RIO_BIND_RTA&t;(RIOC | 198)
DECL|macro|RIO_GET_BINDINGS
mdefine_line|#define RIO_GET_BINDINGS&t;(RIOC | 199)
DECL|macro|RIO_PUT_BINDINGS
mdefine_line|#define RIO_PUT_BINDINGS&t;(RIOC | 200)
DECL|macro|RIO_MAKE_DEV
mdefine_line|#define&t;RIO_MAKE_DEV&t;&t;(RIOC | 201)
DECL|macro|RIO_MINOR
mdefine_line|#define&t;RIO_MINOR&t;&t;(RIOC | 202)
DECL|macro|RIO_IDENTIFY_DRIVER
mdefine_line|#define&t;RIO_IDENTIFY_DRIVER&t;(RIOC | 203)
DECL|macro|RIO_DISPLAY_HOST_CFG
mdefine_line|#define&t;RIO_DISPLAY_HOST_CFG&t;(RIOC | 204)
multiline_comment|/*&n;** MAKE_DEV / MINOR stuff&n;*/
DECL|macro|RIO_DEV_DIRECT
mdefine_line|#define&t;RIO_DEV_DIRECT&t;&t;0x0000
DECL|macro|RIO_DEV_MODEM
mdefine_line|#define&t;RIO_DEV_MODEM&t;&t;0x0200
DECL|macro|RIO_DEV_XPRINT
mdefine_line|#define&t;RIO_DEV_XPRINT&t;&t;0x0400
DECL|macro|RIO_DEV_MASK
mdefine_line|#define&t;RIO_DEV_MASK&t;&t;0x0600
multiline_comment|/*&n;** port management, xprint stuff&n;*/
DECL|macro|rIOCN
mdefine_line|#define&t;rIOCN(N)&t;(RIOC|(N))
DECL|macro|rIOCR
mdefine_line|#define&t;rIOCR(N,T)&t;(RIOC|(N))
DECL|macro|rIOCW
mdefine_line|#define&t;rIOCW(N,T)&t;(RIOC|(N))
DECL|macro|RIO_GET_XP_ON
mdefine_line|#define&t;RIO_GET_XP_ON     rIOCR(150,char[16])&t;/* start xprint string */
DECL|macro|RIO_SET_XP_ON
mdefine_line|#define&t;RIO_SET_XP_ON     rIOCW(151,char[16])
DECL|macro|RIO_GET_XP_OFF
mdefine_line|#define&t;RIO_GET_XP_OFF    rIOCR(152,char[16])&t;/* finish xprint string */
DECL|macro|RIO_SET_XP_OFF
mdefine_line|#define&t;RIO_SET_XP_OFF    rIOCW(153,char[16])
DECL|macro|RIO_GET_XP_CPS
mdefine_line|#define&t;RIO_GET_XP_CPS    rIOCR(154,int)&t;/* xprint CPS */
DECL|macro|RIO_SET_XP_CPS
mdefine_line|#define&t;RIO_SET_XP_CPS    rIOCW(155,int)
DECL|macro|RIO_GET_IXANY
mdefine_line|#define RIO_GET_IXANY     rIOCR(156,int)&t;/* ixany allowed? */
DECL|macro|RIO_SET_IXANY
mdefine_line|#define RIO_SET_IXANY     rIOCW(157,int)
DECL|macro|RIO_SET_IXANY_ON
mdefine_line|#define RIO_SET_IXANY_ON  rIOCN(158)&t;&t;/* allow ixany */
DECL|macro|RIO_SET_IXANY_OFF
mdefine_line|#define RIO_SET_IXANY_OFF rIOCN(159)&t;&t;/* disallow ixany */
DECL|macro|RIO_GET_MODEM
mdefine_line|#define RIO_GET_MODEM     rIOCR(160,int)&t;/* port is modem/direct line? */
DECL|macro|RIO_SET_MODEM
mdefine_line|#define RIO_SET_MODEM     rIOCW(161,int)
DECL|macro|RIO_SET_MODEM_ON
mdefine_line|#define RIO_SET_MODEM_ON  rIOCN(162)&t;&t;/* port is a modem */
DECL|macro|RIO_SET_MODEM_OFF
mdefine_line|#define RIO_SET_MODEM_OFF rIOCN(163)&t;&t;/* port is direct */
DECL|macro|RIO_GET_IXON
mdefine_line|#define RIO_GET_IXON      rIOCR(164,int)&t;/* ixon allowed? */
DECL|macro|RIO_SET_IXON
mdefine_line|#define RIO_SET_IXON      rIOCW(165,int)
DECL|macro|RIO_SET_IXON_ON
mdefine_line|#define RIO_SET_IXON_ON   rIOCN(166)&t;&t;/* allow ixon */
DECL|macro|RIO_SET_IXON_OFF
mdefine_line|#define RIO_SET_IXON_OFF  rIOCN(167)&t;&t;/* disallow ixon */
DECL|macro|RIO_GET_SIVIEW
mdefine_line|#define RIO_GET_SIVIEW&t;  (((&squot;s&squot;)&lt;&lt;8) | 106)&t;/* backwards compatible with SI */
DECL|macro|RIO_IOCTL_UNKNOWN
mdefine_line|#define&t;RIO_IOCTL_UNKNOWN&t;-2
macro_line|#endif
eof
