multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;This file implements the various access functions for the&n; *&t;&t;PROC file system.  It is mainly used for debugging and&n; *&t;&t;statistics.&n; *&n; * Version:&t;$Id: proc.c,v 1.45 2001/05/16 16:45:35 davem Exp $&n; *&n; * Authors:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Gerald J. Heim, &lt;heim@peanuts.informatik.uni-tuebingen.de&gt;&n; *&t;&t;Fred Baumgarten, &lt;dc6iq@insu1.etec.uni-karlsruhe.de&gt;&n; *&t;&t;Erik Schoenfelder, &lt;schoenfr@ibr.cs.tu-bs.de&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;UDP sockets show the rxqueue/txqueue&n; *&t;&t;&t;&t;&t;using hint flag for the netinfo.&n; *&t;Pauline Middelink&t;:&t;identd support&n; *&t;&t;Alan Cox&t;:&t;Make /proc safer.&n; *&t;Erik Schoenfelder&t;:&t;/proc/net/snmp&n; *&t;&t;Alan Cox&t;:&t;Handle dead sockets properly.&n; *&t;Gerhard Koerting&t;:&t;Show both timers&n; *&t;&t;Alan Cox&t;:&t;Allow inode to be NULL (kernel socket)&n; *&t;Andi Kleen&t;&t;:&t;Add support for open_requests and &n; *&t;&t;&t;&t;&t;split functions for more readibility.&n; *&t;Andi Kleen&t;&t;:&t;Add support for /proc/net/netstat&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/un.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/raw.h&gt;
DECL|function|fold_prot_inuse
r_static
r_int
id|fold_prot_inuse
c_func
(paren
r_struct
id|proto
op_star
id|proto
)paren
(brace
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_int
id|cpu
suffix:semicolon
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|NR_CPUS
suffix:semicolon
id|cpu
op_increment
)paren
id|res
op_add_assign
id|proto-&gt;stats
(braket
id|cpu
)braket
dot
id|inuse
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Report socket allocation statistics [mea@utu.fi]&n; */
DECL|function|afinet_get_info
r_int
id|afinet_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
multiline_comment|/* From  net/socket.c  */
r_extern
r_int
id|socket_get_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_int
id|len
op_assign
id|socket_get_info
c_func
(paren
id|buffer
comma
id|start
comma
id|offset
comma
id|length
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;TCP: inuse %d orphan %d tw %d alloc %d mem %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|tcp_prot
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|tcp_orphan_count
)paren
comma
id|tcp_tw_count
comma
id|atomic_read
c_func
(paren
op_amp
id|tcp_sockets_allocated
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|tcp_memory_allocated
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;UDP: inuse %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|udp_prot
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;RAW: inuse %d&bslash;n&quot;
comma
id|fold_prot_inuse
c_func
(paren
op_amp
id|raw_prot
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;FRAG: inuse %d memory %d&bslash;n&quot;
comma
id|ip_frag_nqueues
comma
id|atomic_read
c_func
(paren
op_amp
id|ip_frag_mem
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|fold_field
r_static
r_int
r_int
id|fold_field
c_func
(paren
r_int
r_int
op_star
id|begin
comma
r_int
id|sz
comma
r_int
id|nr
)paren
(brace
r_int
r_int
id|res
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sz
op_div_assign
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|res
op_add_assign
id|begin
(braket
l_int|2
op_star
id|i
op_star
id|sz
op_plus
id|nr
)braket
suffix:semicolon
id|res
op_add_assign
id|begin
(braket
(paren
l_int|2
op_star
id|i
op_plus
l_int|1
)paren
op_star
id|sz
op_plus
id|nr
)braket
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Called from the PROCfs module. This outputs /proc/net/snmp.&n; */
DECL|function|snmp_get_info
r_int
id|snmp_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_extern
r_int
id|sysctl_ip_default_ttl
suffix:semicolon
r_int
id|len
comma
id|i
suffix:semicolon
id|len
op_assign
id|sprintf
(paren
id|buffer
comma
l_string|&quot;Ip: Forwarding DefaultTTL InReceives InHdrErrors InAddrErrors ForwDatagrams InUnknownProtos InDiscards InDelivers OutRequests OutDiscards OutNoRoutes ReasmTimeout ReasmReqds ReasmOKs ReasmFails FragOKs FragFails FragCreates&bslash;n&quot;
l_string|&quot;Ip: %d %d&quot;
comma
id|ipv4_devconf.forwarding
ques
c_cond
l_int|1
suffix:colon
l_int|2
comma
id|sysctl_ip_default_ttl
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
m_offsetof
(paren
r_struct
id|ip_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|ip_statistics
comma
r_sizeof
(paren
r_struct
id|ip_mib
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nIcmp: InMsgs InErrors InDestUnreachs InTimeExcds InParmProbs InSrcQuenchs InRedirects InEchos InEchoReps InTimestamps InTimestampReps InAddrMasks InAddrMaskReps OutMsgs OutErrors OutDestUnreachs OutTimeExcds OutParmProbs OutSrcQuenchs OutRedirects OutEchos OutEchoReps OutTimestamps OutTimestampReps OutAddrMasks OutAddrMaskReps&bslash;n&quot;
l_string|&quot;Icmp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
m_offsetof
(paren
r_struct
id|icmp_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|icmp_statistics
comma
r_sizeof
(paren
r_struct
id|icmp_mib
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nTcp: RtoAlgorithm RtoMin RtoMax MaxConn ActiveOpens PassiveOpens AttemptFails EstabResets CurrEstab InSegs OutSegs RetransSegs InErrs OutRsts&bslash;n&quot;
l_string|&quot;Tcp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
m_offsetof
(paren
r_struct
id|tcp_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|tcp_statistics
comma
r_sizeof
(paren
r_struct
id|tcp_mib
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nUdp: InDatagrams NoPorts InErrors OutDatagrams&bslash;n&quot;
l_string|&quot;Udp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
m_offsetof
(paren
r_struct
id|udp_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|udp_statistics
comma
r_sizeof
(paren
r_struct
id|udp_mib
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Output /proc/net/netstat&n; */
DECL|function|netstat_get_info
r_int
id|netstat_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
(brace
r_int
id|len
comma
id|i
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;TcpExt: SyncookiesSent SyncookiesRecv SyncookiesFailed&quot;
l_string|&quot; EmbryonicRsts PruneCalled RcvPruned OfoPruned&quot;
l_string|&quot; OutOfWindowIcmps LockDroppedIcmps ArpFilter&quot;
l_string|&quot; TW TWRecycled TWKilled&quot;
l_string|&quot; PAWSPassive PAWSActive PAWSEstab&quot;
l_string|&quot; DelayedACKs DelayedACKLocked DelayedACKLost&quot;
l_string|&quot; ListenOverflows ListenDrops&quot;
l_string|&quot; TCPPrequeued TCPDirectCopyFromBacklog&quot;
l_string|&quot; TCPDirectCopyFromPrequeue TCPPrequeueDropped&quot;
l_string|&quot; TCPHPHits TCPHPHitsToUser&quot;
l_string|&quot; TCPPureAcks TCPHPAcks&quot;
l_string|&quot; TCPRenoRecovery TCPSackRecovery&quot;
l_string|&quot; TCPSACKReneging&quot;
l_string|&quot; TCPFACKReorder TCPSACKReorder TCPRenoReorder TCPTSReorder&quot;
l_string|&quot; TCPFullUndo TCPPartialUndo TCPDSACKUndo TCPLossUndo&quot;
l_string|&quot; TCPLoss TCPLostRetransmit&quot;
l_string|&quot; TCPRenoFailures TCPSackFailures TCPLossFailures&quot;
l_string|&quot; TCPFastRetrans TCPForwardRetrans TCPSlowStartRetrans&quot;
l_string|&quot; TCPTimeouts&quot;
l_string|&quot; TCPRenoRecoveryFail TCPSackRecoveryFail&quot;
l_string|&quot; TCPSchedulerFailed TCPRcvCollapsed&quot;
l_string|&quot; TCPDSACKOldSent TCPDSACKOfoSent TCPDSACKRecv TCPDSACKOfoRecv&quot;
l_string|&quot; TCPAbortOnSyn TCPAbortOnData TCPAbortOnClose&quot;
l_string|&quot; TCPAbortOnMemory TCPAbortOnTimeout TCPAbortOnLinger&quot;
l_string|&quot; TCPAbortFailed TCPMemoryPressures&bslash;n&quot;
l_string|&quot;TcpExt:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
m_offsetof
(paren
r_struct
id|linux_mib
comma
id|__pad
)paren
op_div
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|net_statistics
comma
r_sizeof
(paren
r_struct
id|linux_mib
)paren
comma
id|i
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
id|len
op_sub_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
