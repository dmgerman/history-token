multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;This file implements the various access functions for the&n; *&t;&t;PROC file system.  It is mainly used for debugging and&n; *&t;&t;statistics.&n; *&n; * Version:&t;$Id: proc.c,v 1.45 2001/05/16 16:45:35 davem Exp $&n; *&n; * Authors:&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&t;&t;Gerald J. Heim, &lt;heim@peanuts.informatik.uni-tuebingen.de&gt;&n; *&t;&t;Fred Baumgarten, &lt;dc6iq@insu1.etec.uni-karlsruhe.de&gt;&n; *&t;&t;Erik Schoenfelder, &lt;schoenfr@ibr.cs.tu-bs.de&gt;&n; *&n; * Fixes:&n; *&t;&t;Alan Cox&t;:&t;UDP sockets show the rxqueue/txqueue&n; *&t;&t;&t;&t;&t;using hint flag for the netinfo.&n; *&t;Pauline Middelink&t;:&t;identd support&n; *&t;&t;Alan Cox&t;:&t;Make /proc safer.&n; *&t;Erik Schoenfelder&t;:&t;/proc/net/snmp&n; *&t;&t;Alan Cox&t;:&t;Handle dead sockets properly.&n; *&t;Gerhard Koerting&t;:&t;Show both timers&n; *&t;&t;Alan Cox&t;:&t;Allow inode to be NULL (kernel socket)&n; *&t;Andi Kleen&t;&t;:&t;Add support for open_requests and&n; *&t;&t;&t;&t;&t;split functions for more readibility.&n; *&t;Andi Kleen&t;&t;:&t;Add support for /proc/net/netstat&n; *&t;Arnaldo C. Melo&t;&t;:&t;Convert to seq_file&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/icmp.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
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
DECL|function|sockstat_seq_show
r_static
r_int
id|sockstat_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
multiline_comment|/* From net/socket.c */
r_extern
r_void
id|socket_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
)paren
suffix:semicolon
id|socket_seq_show
c_func
(paren
id|seq
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
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
id|seq_printf
c_func
(paren
id|seq
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
id|seq_printf
c_func
(paren
id|seq
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
id|seq_printf
c_func
(paren
id|seq
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sockstat_seq_open
r_static
r_int
id|sockstat_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|single_open
c_func
(paren
id|file
comma
id|sockstat_seq_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|sockstat_seq_fops
r_static
r_struct
id|file_operations
id|sockstat_seq_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|sockstat_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
r_static
r_int
r_int
DECL|function|fold_field
id|fold_field
c_func
(paren
r_void
op_star
id|mib
(braket
)braket
comma
r_int
id|offt
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
r_if
c_cond
(paren
op_logical_neg
id|cpu_possible
c_func
(paren
id|i
)paren
)paren
r_continue
suffix:semicolon
id|res
op_add_assign
op_star
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|per_cpu_ptr
c_func
(paren
id|mib
(braket
l_int|0
)braket
comma
id|i
)paren
)paren
op_plus
id|offt
)paren
suffix:semicolon
id|res
op_add_assign
op_star
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|per_cpu_ptr
c_func
(paren
id|mib
(braket
l_int|1
)braket
comma
id|i
)paren
)paren
op_plus
id|offt
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/* snmp items */
DECL|variable|snmp4_ipstats_list
r_static
r_struct
id|snmp_mib
id|snmp4_ipstats_list
(braket
)braket
op_assign
(brace
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InReceives&quot;
comma
id|IPSTATS_MIB_INRECEIVES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InHdrErrors&quot;
comma
id|IPSTATS_MIB_INHDRERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InAddrErrors&quot;
comma
id|IPSTATS_MIB_INADDRERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ForwDatagrams&quot;
comma
id|IPSTATS_MIB_OUTFORWDATAGRAMS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InUnknownProtos&quot;
comma
id|IPSTATS_MIB_INUNKNOWNPROTOS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InDiscards&quot;
comma
id|IPSTATS_MIB_INDISCARDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InDelivers&quot;
comma
id|IPSTATS_MIB_INDELIVERS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutRequests&quot;
comma
id|IPSTATS_MIB_OUTREQUESTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutDiscards&quot;
comma
id|IPSTATS_MIB_OUTDISCARDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutNoRoutes&quot;
comma
id|IPSTATS_MIB_OUTNOROUTES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ReasmTimeout&quot;
comma
id|IPSTATS_MIB_REASMTIMEOUT
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ReasmReqds&quot;
comma
id|IPSTATS_MIB_REASMREQDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ReasmOKs&quot;
comma
id|IPSTATS_MIB_REASMOKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ReasmFails&quot;
comma
id|IPSTATS_MIB_REASMFAILS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;FragOKs&quot;
comma
id|IPSTATS_MIB_FRAGOKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;FragFails&quot;
comma
id|IPSTATS_MIB_FRAGFAILS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;FragCreates&quot;
comma
id|IPSTATS_MIB_FRAGCREATES
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp4_icmp_list
r_static
r_struct
id|snmp_mib
id|snmp4_icmp_list
(braket
)braket
op_assign
(brace
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InMsgs&quot;
comma
id|ICMP_MIB_INMSGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InErrors&quot;
comma
id|ICMP_MIB_INERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InDestUnreachs&quot;
comma
id|ICMP_MIB_INDESTUNREACHS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InTimeExcds&quot;
comma
id|ICMP_MIB_INTIMEEXCDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InParmProbs&quot;
comma
id|ICMP_MIB_INPARMPROBS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InSrcQuenchs&quot;
comma
id|ICMP_MIB_INSRCQUENCHS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InRedirects&quot;
comma
id|ICMP_MIB_INREDIRECTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InEchos&quot;
comma
id|ICMP_MIB_INECHOS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InEchoReps&quot;
comma
id|ICMP_MIB_INECHOREPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InTimestamps&quot;
comma
id|ICMP_MIB_INTIMESTAMPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InTimestampReps&quot;
comma
id|ICMP_MIB_INTIMESTAMPREPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InAddrMasks&quot;
comma
id|ICMP_MIB_INADDRMASKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InAddrMaskReps&quot;
comma
id|ICMP_MIB_INADDRMASKREPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutMsgs&quot;
comma
id|ICMP_MIB_OUTMSGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutErrors&quot;
comma
id|ICMP_MIB_OUTERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutDestUnreachs&quot;
comma
id|ICMP_MIB_OUTDESTUNREACHS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutTimeExcds&quot;
comma
id|ICMP_MIB_OUTTIMEEXCDS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutParmProbs&quot;
comma
id|ICMP_MIB_OUTPARMPROBS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutSrcQuenchs&quot;
comma
id|ICMP_MIB_OUTSRCQUENCHS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutRedirects&quot;
comma
id|ICMP_MIB_OUTREDIRECTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutEchos&quot;
comma
id|ICMP_MIB_OUTECHOS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutEchoReps&quot;
comma
id|ICMP_MIB_OUTECHOREPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutTimestamps&quot;
comma
id|ICMP_MIB_OUTTIMESTAMPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutTimestampReps&quot;
comma
id|ICMP_MIB_OUTTIMESTAMPREPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutAddrMasks&quot;
comma
id|ICMP_MIB_OUTADDRMASKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutAddrMaskReps&quot;
comma
id|ICMP_MIB_OUTADDRMASKREPS
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp4_tcp_list
r_static
r_struct
id|snmp_mib
id|snmp4_tcp_list
(braket
)braket
op_assign
(brace
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;RtoAlgorithm&quot;
comma
id|TCP_MIB_RTOALGORITHM
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;RtoMin&quot;
comma
id|TCP_MIB_RTOMIN
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;RtoMax&quot;
comma
id|TCP_MIB_RTOMAX
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;MaxConn&quot;
comma
id|TCP_MIB_MAXCONN
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ActiveOpens&quot;
comma
id|TCP_MIB_ACTIVEOPENS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;PassiveOpens&quot;
comma
id|TCP_MIB_PASSIVEOPENS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;AttemptFails&quot;
comma
id|TCP_MIB_ATTEMPTFAILS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;EstabResets&quot;
comma
id|TCP_MIB_ESTABRESETS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;CurrEstab&quot;
comma
id|TCP_MIB_CURRESTAB
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InSegs&quot;
comma
id|TCP_MIB_INSEGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutSegs&quot;
comma
id|TCP_MIB_OUTSEGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;RetransSegs&quot;
comma
id|TCP_MIB_RETRANSSEGS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InErrs&quot;
comma
id|TCP_MIB_INERRS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutRsts&quot;
comma
id|TCP_MIB_OUTRSTS
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp4_udp_list
r_static
r_struct
id|snmp_mib
id|snmp4_udp_list
(braket
)braket
op_assign
(brace
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InDatagrams&quot;
comma
id|UDP_MIB_INDATAGRAMS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;NoPorts&quot;
comma
id|UDP_MIB_NOPORTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;InErrors&quot;
comma
id|UDP_MIB_INERRORS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutDatagrams&quot;
comma
id|UDP_MIB_OUTDATAGRAMS
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
DECL|variable|snmp4_net_list
r_static
r_struct
id|snmp_mib
id|snmp4_net_list
(braket
)braket
op_assign
(brace
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;SyncookiesSent&quot;
comma
id|LINUX_MIB_SYNCOOKIESSENT
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;SyncookiesRecv&quot;
comma
id|LINUX_MIB_SYNCOOKIESRECV
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;SyncookiesFailed&quot;
comma
id|LINUX_MIB_SYNCOOKIESFAILED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;EmbryonicRsts&quot;
comma
id|LINUX_MIB_EMBRYONICRSTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;PruneCalled&quot;
comma
id|LINUX_MIB_PRUNECALLED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;RcvPruned&quot;
comma
id|LINUX_MIB_RCVPRUNED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OfoPruned&quot;
comma
id|LINUX_MIB_OFOPRUNED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;OutOfWindowIcmps&quot;
comma
id|LINUX_MIB_OUTOFWINDOWICMPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;LockDroppedIcmps&quot;
comma
id|LINUX_MIB_LOCKDROPPEDICMPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ArpFilter&quot;
comma
id|LINUX_MIB_ARPFILTER
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TW&quot;
comma
id|LINUX_MIB_TIMEWAITED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TWRecycled&quot;
comma
id|LINUX_MIB_TIMEWAITRECYCLED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TWKilled&quot;
comma
id|LINUX_MIB_TIMEWAITKILLED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;PAWSPassive&quot;
comma
id|LINUX_MIB_PAWSPASSIVEREJECTED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;PAWSActive&quot;
comma
id|LINUX_MIB_PAWSACTIVEREJECTED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;PAWSEstab&quot;
comma
id|LINUX_MIB_PAWSESTABREJECTED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;DelayedACKs&quot;
comma
id|LINUX_MIB_DELAYEDACKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;DelayedACKLocked&quot;
comma
id|LINUX_MIB_DELAYEDACKLOCKED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;DelayedACKLost&quot;
comma
id|LINUX_MIB_DELAYEDACKLOST
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ListenOverflows&quot;
comma
id|LINUX_MIB_LISTENOVERFLOWS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;ListenDrops&quot;
comma
id|LINUX_MIB_LISTENDROPS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPPrequeued&quot;
comma
id|LINUX_MIB_TCPPREQUEUED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPDirectCopyFromBacklog&quot;
comma
id|LINUX_MIB_TCPDIRECTCOPYFROMBACKLOG
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPDirectCopyFromPrequeue&quot;
comma
id|LINUX_MIB_TCPDIRECTCOPYFROMPREQUEUE
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPPrequeueDropped&quot;
comma
id|LINUX_MIB_TCPPREQUEUEDROPPED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPHPHits&quot;
comma
id|LINUX_MIB_TCPHPHITS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPHPHitsToUser&quot;
comma
id|LINUX_MIB_TCPHPHITSTOUSER
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPPureAcks&quot;
comma
id|LINUX_MIB_TCPPUREACKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPHPAcks&quot;
comma
id|LINUX_MIB_TCPHPACKS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPRenoRecovery&quot;
comma
id|LINUX_MIB_TCPRENORECOVERY
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPSackRecovery&quot;
comma
id|LINUX_MIB_TCPSACKRECOVERY
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPSACKReneging&quot;
comma
id|LINUX_MIB_TCPSACKRENEGING
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPFACKReorder&quot;
comma
id|LINUX_MIB_TCPFACKREORDER
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPSACKReorder&quot;
comma
id|LINUX_MIB_TCPSACKREORDER
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPRenoReorder&quot;
comma
id|LINUX_MIB_TCPRENOREORDER
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPTSReorder&quot;
comma
id|LINUX_MIB_TCPTSREORDER
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPFullUndo&quot;
comma
id|LINUX_MIB_TCPFULLUNDO
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPPartialUndo&quot;
comma
id|LINUX_MIB_TCPPARTIALUNDO
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPDSACKUndo&quot;
comma
id|LINUX_MIB_TCPDSACKUNDO
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPLossUndo&quot;
comma
id|LINUX_MIB_TCPLOSSUNDO
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPLoss&quot;
comma
id|LINUX_MIB_TCPLOSS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPLostRetransmit&quot;
comma
id|LINUX_MIB_TCPLOSTRETRANSMIT
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPRenoFailures&quot;
comma
id|LINUX_MIB_TCPRENOFAILURES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPSackFailures&quot;
comma
id|LINUX_MIB_TCPSACKFAILURES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPLossFailures&quot;
comma
id|LINUX_MIB_TCPLOSSFAILURES
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPFastRetrans&quot;
comma
id|LINUX_MIB_TCPFASTRETRANS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPForwardRetrans&quot;
comma
id|LINUX_MIB_TCPFORWARDRETRANS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPSlowStartRetrans&quot;
comma
id|LINUX_MIB_TCPSLOWSTARTRETRANS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPTimeouts&quot;
comma
id|LINUX_MIB_TCPTIMEOUTS
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPRenoRecoveryFail&quot;
comma
id|LINUX_MIB_TCPRENORECOVERYFAIL
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPSackRecoveryFail&quot;
comma
id|LINUX_MIB_TCPSACKRECOVERYFAIL
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPSchedulerFailed&quot;
comma
id|LINUX_MIB_TCPSCHEDULERFAILED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPRcvCollapsed&quot;
comma
id|LINUX_MIB_TCPRCVCOLLAPSED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPDSACKOldSent&quot;
comma
id|LINUX_MIB_TCPDSACKOLDSENT
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPDSACKOfoSent&quot;
comma
id|LINUX_MIB_TCPDSACKOFOSENT
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPDSACKRecv&quot;
comma
id|LINUX_MIB_TCPDSACKRECV
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPDSACKOfoRecv&quot;
comma
id|LINUX_MIB_TCPDSACKOFORECV
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPAbortOnSyn&quot;
comma
id|LINUX_MIB_TCPABORTONSYN
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPAbortOnData&quot;
comma
id|LINUX_MIB_TCPABORTONDATA
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPAbortOnClose&quot;
comma
id|LINUX_MIB_TCPABORTONCLOSE
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPAbortOnMemory&quot;
comma
id|LINUX_MIB_TCPABORTONMEMORY
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPAbortOnTimeout&quot;
comma
id|LINUX_MIB_TCPABORTONTIMEOUT
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPAbortOnLinger&quot;
comma
id|LINUX_MIB_TCPABORTONLINGER
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPAbortFailed&quot;
comma
id|LINUX_MIB_TCPABORTFAILED
)paren
comma
id|SNMP_MIB_ITEM
c_func
(paren
l_string|&quot;TCPMemoryPressures&quot;
comma
id|LINUX_MIB_TCPMEMORYPRESSURES
)paren
comma
id|SNMP_MIB_SENTINEL
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Called from the PROCfs module. This outputs /proc/net/snmp.&n; */
DECL|function|snmp_seq_show
r_static
r_int
id|snmp_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;Ip: Forwarding DefaultTTL&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_ipstats_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %s&quot;
comma
id|snmp4_ipstats_list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nIp: %d %d&quot;
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
id|snmp4_ipstats_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|ip_statistics
comma
id|snmp4_ipstats_list
(braket
id|i
)braket
dot
id|entry
)paren
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nIcmp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_icmp_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %s&quot;
comma
id|snmp4_icmp_list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nIcmp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_icmp_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|icmp_statistics
comma
id|snmp4_icmp_list
(braket
id|i
)braket
dot
id|entry
)paren
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nTcp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_tcp_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %s&quot;
comma
id|snmp4_tcp_list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nTcp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_tcp_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* MaxConn field is signed, RFC 2012 */
r_if
c_cond
(paren
id|snmp4_tcp_list
(braket
id|i
)braket
dot
id|entry
op_eq
id|TCP_MIB_MAXCONN
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %ld&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|tcp_statistics
comma
id|snmp4_tcp_list
(braket
id|i
)braket
dot
id|entry
)paren
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|tcp_statistics
comma
id|snmp4_tcp_list
(braket
id|i
)braket
dot
id|entry
)paren
)paren
suffix:semicolon
)brace
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nUdp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_udp_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %s&quot;
comma
id|snmp4_udp_list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nUdp:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_udp_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|udp_statistics
comma
id|snmp4_udp_list
(braket
id|i
)braket
dot
id|entry
)paren
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|snmp_seq_open
r_static
r_int
id|snmp_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|single_open
c_func
(paren
id|file
comma
id|snmp_seq_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|snmp_seq_fops
r_static
r_struct
id|file_operations
id|snmp_seq_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|snmp_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Output /proc/net/netstat&n; */
DECL|function|netstat_seq_show
r_static
r_int
id|netstat_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
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
id|snmp4_net_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %s&quot;
comma
id|snmp4_net_list
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;&bslash;nTcpExt:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|snmp4_net_list
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
suffix:semicolon
id|i
op_increment
)paren
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot; %lu&quot;
comma
id|fold_field
c_func
(paren
(paren
r_void
op_star
op_star
)paren
id|net_statistics
comma
id|snmp4_net_list
(braket
id|i
)braket
dot
id|entry
)paren
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|seq
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|netstat_seq_open
r_static
r_int
id|netstat_seq_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|single_open
c_func
(paren
id|file
comma
id|netstat_seq_show
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|variable|netstat_seq_fops
r_static
r_struct
id|file_operations
id|netstat_seq_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|open
op_assign
id|netstat_seq_open
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
DECL|function|ip_misc_proc_init
r_int
id|__init
id|ip_misc_proc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_fops_create
c_func
(paren
l_string|&quot;netstat&quot;
comma
id|S_IRUGO
comma
op_amp
id|netstat_seq_fops
)paren
)paren
r_goto
id|out_netstat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_fops_create
c_func
(paren
l_string|&quot;snmp&quot;
comma
id|S_IRUGO
comma
op_amp
id|snmp_seq_fops
)paren
)paren
r_goto
id|out_snmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_fops_create
c_func
(paren
l_string|&quot;sockstat&quot;
comma
id|S_IRUGO
comma
op_amp
id|sockstat_seq_fops
)paren
)paren
r_goto
id|out_sockstat
suffix:semicolon
id|out
suffix:colon
r_return
id|rc
suffix:semicolon
id|out_sockstat
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;snmp&quot;
)paren
suffix:semicolon
id|out_snmp
suffix:colon
id|proc_net_remove
c_func
(paren
l_string|&quot;netstat&quot;
)paren
suffix:semicolon
id|out_netstat
suffix:colon
id|rc
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
eof
