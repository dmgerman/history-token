multiline_comment|/*&n; * Definitions for MIBs&n; *&n; * Author: Hideaki YOSHIFUJI &lt;yoshfuji@linux-ipv6.org&gt;&n; */
macro_line|#ifndef _LINUX_SNMP_H
DECL|macro|_LINUX_SNMP_H
mdefine_line|#define _LINUX_SNMP_H
multiline_comment|/* ipstats mib definitions */
multiline_comment|/*&n; * RFC 1213:  MIB-II&n; * RFC 2011 (updates 1213):  SNMPv2-MIB-IP&n; * RFC 2863:  Interfaces Group MIB&n; * RFC 2465:  IPv6 MIB: General Group&n; * draft-ietf-ipv6-rfc2011-update-10.txt: MIB for IP: IP Statistics Tables&n; */
r_enum
(brace
DECL|enumerator|IPSTATS_MIB_NUM
id|IPSTATS_MIB_NUM
op_assign
l_int|0
comma
DECL|enumerator|IPSTATS_MIB_INRECEIVES
id|IPSTATS_MIB_INRECEIVES
comma
multiline_comment|/* InReceives */
DECL|enumerator|IPSTATS_MIB_INHDRERRORS
id|IPSTATS_MIB_INHDRERRORS
comma
multiline_comment|/* InHdrErrors */
DECL|enumerator|IPSTATS_MIB_INTOOBIGERRORS
id|IPSTATS_MIB_INTOOBIGERRORS
comma
multiline_comment|/* InTooBigErrors */
DECL|enumerator|IPSTATS_MIB_INNOROUTES
id|IPSTATS_MIB_INNOROUTES
comma
multiline_comment|/* InNoRoutes */
DECL|enumerator|IPSTATS_MIB_INADDRERRORS
id|IPSTATS_MIB_INADDRERRORS
comma
multiline_comment|/* InAddrErrors */
DECL|enumerator|IPSTATS_MIB_INUNKNOWNPROTOS
id|IPSTATS_MIB_INUNKNOWNPROTOS
comma
multiline_comment|/* InUnknownProtos */
DECL|enumerator|IPSTATS_MIB_INTRUNCATEDPKTS
id|IPSTATS_MIB_INTRUNCATEDPKTS
comma
multiline_comment|/* InTruncatedPkts */
DECL|enumerator|IPSTATS_MIB_INDISCARDS
id|IPSTATS_MIB_INDISCARDS
comma
multiline_comment|/* InDiscards */
DECL|enumerator|IPSTATS_MIB_INDELIVERS
id|IPSTATS_MIB_INDELIVERS
comma
multiline_comment|/* InDelivers */
DECL|enumerator|IPSTATS_MIB_OUTFORWDATAGRAMS
id|IPSTATS_MIB_OUTFORWDATAGRAMS
comma
multiline_comment|/* OutForwDatagrams */
DECL|enumerator|IPSTATS_MIB_OUTREQUESTS
id|IPSTATS_MIB_OUTREQUESTS
comma
multiline_comment|/* OutRequests */
DECL|enumerator|IPSTATS_MIB_OUTDISCARDS
id|IPSTATS_MIB_OUTDISCARDS
comma
multiline_comment|/* OutDiscards */
DECL|enumerator|IPSTATS_MIB_OUTNOROUTES
id|IPSTATS_MIB_OUTNOROUTES
comma
multiline_comment|/* OutNoRoutes */
DECL|enumerator|IPSTATS_MIB_REASMTIMEOUT
id|IPSTATS_MIB_REASMTIMEOUT
comma
multiline_comment|/* ReasmTimeout */
DECL|enumerator|IPSTATS_MIB_REASMREQDS
id|IPSTATS_MIB_REASMREQDS
comma
multiline_comment|/* ReasmReqds */
DECL|enumerator|IPSTATS_MIB_REASMOKS
id|IPSTATS_MIB_REASMOKS
comma
multiline_comment|/* ReasmOKs */
DECL|enumerator|IPSTATS_MIB_REASMFAILS
id|IPSTATS_MIB_REASMFAILS
comma
multiline_comment|/* ReasmFails */
DECL|enumerator|IPSTATS_MIB_FRAGOKS
id|IPSTATS_MIB_FRAGOKS
comma
multiline_comment|/* FragOKs */
DECL|enumerator|IPSTATS_MIB_FRAGFAILS
id|IPSTATS_MIB_FRAGFAILS
comma
multiline_comment|/* FragFails */
DECL|enumerator|IPSTATS_MIB_FRAGCREATES
id|IPSTATS_MIB_FRAGCREATES
comma
multiline_comment|/* FragCreates */
DECL|enumerator|IPSTATS_MIB_INMCASTPKTS
id|IPSTATS_MIB_INMCASTPKTS
comma
multiline_comment|/* InMcastPkts */
DECL|enumerator|IPSTATS_MIB_OUTMCASTPKTS
id|IPSTATS_MIB_OUTMCASTPKTS
comma
multiline_comment|/* OutMcastPkts */
DECL|enumerator|__IPSTATS_MIB_MAX
id|__IPSTATS_MIB_MAX
)brace
suffix:semicolon
multiline_comment|/* icmp mib definitions */
multiline_comment|/*&n; * RFC 1213:  MIB-II ICMP Group&n; * RFC 2011 (updates 1213):  SNMPv2 MIB for IP: ICMP group&n; */
r_enum
(brace
DECL|enumerator|ICMP_MIB_NUM
id|ICMP_MIB_NUM
op_assign
l_int|0
comma
DECL|enumerator|ICMP_MIB_INMSGS
id|ICMP_MIB_INMSGS
comma
multiline_comment|/* InMsgs */
DECL|enumerator|ICMP_MIB_INERRORS
id|ICMP_MIB_INERRORS
comma
multiline_comment|/* InErrors */
DECL|enumerator|ICMP_MIB_INDESTUNREACHS
id|ICMP_MIB_INDESTUNREACHS
comma
multiline_comment|/* InDestUnreachs */
DECL|enumerator|ICMP_MIB_INTIMEEXCDS
id|ICMP_MIB_INTIMEEXCDS
comma
multiline_comment|/* InTimeExcds */
DECL|enumerator|ICMP_MIB_INPARMPROBS
id|ICMP_MIB_INPARMPROBS
comma
multiline_comment|/* InParmProbs */
DECL|enumerator|ICMP_MIB_INSRCQUENCHS
id|ICMP_MIB_INSRCQUENCHS
comma
multiline_comment|/* InSrcQuenchs */
DECL|enumerator|ICMP_MIB_INREDIRECTS
id|ICMP_MIB_INREDIRECTS
comma
multiline_comment|/* InRedirects */
DECL|enumerator|ICMP_MIB_INECHOS
id|ICMP_MIB_INECHOS
comma
multiline_comment|/* InEchos */
DECL|enumerator|ICMP_MIB_INECHOREPS
id|ICMP_MIB_INECHOREPS
comma
multiline_comment|/* InEchoReps */
DECL|enumerator|ICMP_MIB_INTIMESTAMPS
id|ICMP_MIB_INTIMESTAMPS
comma
multiline_comment|/* InTimestamps */
DECL|enumerator|ICMP_MIB_INTIMESTAMPREPS
id|ICMP_MIB_INTIMESTAMPREPS
comma
multiline_comment|/* InTimestampReps */
DECL|enumerator|ICMP_MIB_INADDRMASKS
id|ICMP_MIB_INADDRMASKS
comma
multiline_comment|/* InAddrMasks */
DECL|enumerator|ICMP_MIB_INADDRMASKREPS
id|ICMP_MIB_INADDRMASKREPS
comma
multiline_comment|/* InAddrMaskReps */
DECL|enumerator|ICMP_MIB_OUTMSGS
id|ICMP_MIB_OUTMSGS
comma
multiline_comment|/* OutMsgs */
DECL|enumerator|ICMP_MIB_OUTERRORS
id|ICMP_MIB_OUTERRORS
comma
multiline_comment|/* OutErrors */
DECL|enumerator|ICMP_MIB_OUTDESTUNREACHS
id|ICMP_MIB_OUTDESTUNREACHS
comma
multiline_comment|/* OutDestUnreachs */
DECL|enumerator|ICMP_MIB_OUTTIMEEXCDS
id|ICMP_MIB_OUTTIMEEXCDS
comma
multiline_comment|/* OutTimeExcds */
DECL|enumerator|ICMP_MIB_OUTPARMPROBS
id|ICMP_MIB_OUTPARMPROBS
comma
multiline_comment|/* OutParmProbs */
DECL|enumerator|ICMP_MIB_OUTSRCQUENCHS
id|ICMP_MIB_OUTSRCQUENCHS
comma
multiline_comment|/* OutSrcQuenchs */
DECL|enumerator|ICMP_MIB_OUTREDIRECTS
id|ICMP_MIB_OUTREDIRECTS
comma
multiline_comment|/* OutRedirects */
DECL|enumerator|ICMP_MIB_OUTECHOS
id|ICMP_MIB_OUTECHOS
comma
multiline_comment|/* OutEchos */
DECL|enumerator|ICMP_MIB_OUTECHOREPS
id|ICMP_MIB_OUTECHOREPS
comma
multiline_comment|/* OutEchoReps */
DECL|enumerator|ICMP_MIB_OUTTIMESTAMPS
id|ICMP_MIB_OUTTIMESTAMPS
comma
multiline_comment|/* OutTimestamps */
DECL|enumerator|ICMP_MIB_OUTTIMESTAMPREPS
id|ICMP_MIB_OUTTIMESTAMPREPS
comma
multiline_comment|/* OutTimestampReps */
DECL|enumerator|ICMP_MIB_OUTADDRMASKS
id|ICMP_MIB_OUTADDRMASKS
comma
multiline_comment|/* OutAddrMasks */
DECL|enumerator|ICMP_MIB_OUTADDRMASKREPS
id|ICMP_MIB_OUTADDRMASKREPS
comma
multiline_comment|/* OutAddrMaskReps */
DECL|enumerator|__ICMP_MIB_MAX
id|__ICMP_MIB_MAX
)brace
suffix:semicolon
multiline_comment|/* icmp6 mib definitions */
multiline_comment|/*&n; * RFC 2466:  ICMPv6-MIB&n; */
r_enum
(brace
DECL|enumerator|ICMP6_MIB_NUM
id|ICMP6_MIB_NUM
op_assign
l_int|0
comma
DECL|enumerator|ICMP6_MIB_INMSGS
id|ICMP6_MIB_INMSGS
comma
multiline_comment|/* InMsgs */
DECL|enumerator|ICMP6_MIB_INERRORS
id|ICMP6_MIB_INERRORS
comma
multiline_comment|/* InErrors */
DECL|enumerator|ICMP6_MIB_INDESTUNREACHS
id|ICMP6_MIB_INDESTUNREACHS
comma
multiline_comment|/* InDestUnreachs */
DECL|enumerator|ICMP6_MIB_INPKTTOOBIGS
id|ICMP6_MIB_INPKTTOOBIGS
comma
multiline_comment|/* InPktTooBigs */
DECL|enumerator|ICMP6_MIB_INTIMEEXCDS
id|ICMP6_MIB_INTIMEEXCDS
comma
multiline_comment|/* InTimeExcds */
DECL|enumerator|ICMP6_MIB_INPARMPROBLEMS
id|ICMP6_MIB_INPARMPROBLEMS
comma
multiline_comment|/* InParmProblems */
DECL|enumerator|ICMP6_MIB_INECHOS
id|ICMP6_MIB_INECHOS
comma
multiline_comment|/* InEchos */
DECL|enumerator|ICMP6_MIB_INECHOREPLIES
id|ICMP6_MIB_INECHOREPLIES
comma
multiline_comment|/* InEchoReplies */
DECL|enumerator|ICMP6_MIB_INGROUPMEMBQUERIES
id|ICMP6_MIB_INGROUPMEMBQUERIES
comma
multiline_comment|/* InGroupMembQueries */
DECL|enumerator|ICMP6_MIB_INGROUPMEMBRESPONSES
id|ICMP6_MIB_INGROUPMEMBRESPONSES
comma
multiline_comment|/* InGroupMembResponses */
DECL|enumerator|ICMP6_MIB_INGROUPMEMBREDUCTIONS
id|ICMP6_MIB_INGROUPMEMBREDUCTIONS
comma
multiline_comment|/* InGroupMembReductions */
DECL|enumerator|ICMP6_MIB_INROUTERSOLICITS
id|ICMP6_MIB_INROUTERSOLICITS
comma
multiline_comment|/* InRouterSolicits */
DECL|enumerator|ICMP6_MIB_INROUTERADVERTISEMENTS
id|ICMP6_MIB_INROUTERADVERTISEMENTS
comma
multiline_comment|/* InRouterAdvertisements */
DECL|enumerator|ICMP6_MIB_INNEIGHBORSOLICITS
id|ICMP6_MIB_INNEIGHBORSOLICITS
comma
multiline_comment|/* InNeighborSolicits */
DECL|enumerator|ICMP6_MIB_INNEIGHBORADVERTISEMENTS
id|ICMP6_MIB_INNEIGHBORADVERTISEMENTS
comma
multiline_comment|/* InNeighborAdvertisements */
DECL|enumerator|ICMP6_MIB_INREDIRECTS
id|ICMP6_MIB_INREDIRECTS
comma
multiline_comment|/* InRedirects */
DECL|enumerator|ICMP6_MIB_OUTMSGS
id|ICMP6_MIB_OUTMSGS
comma
multiline_comment|/* OutMsgs */
DECL|enumerator|ICMP6_MIB_OUTDESTUNREACHS
id|ICMP6_MIB_OUTDESTUNREACHS
comma
multiline_comment|/* OutDestUnreachs */
DECL|enumerator|ICMP6_MIB_OUTPKTTOOBIGS
id|ICMP6_MIB_OUTPKTTOOBIGS
comma
multiline_comment|/* OutPktTooBigs */
DECL|enumerator|ICMP6_MIB_OUTTIMEEXCDS
id|ICMP6_MIB_OUTTIMEEXCDS
comma
multiline_comment|/* OutTimeExcds */
DECL|enumerator|ICMP6_MIB_OUTPARMPROBLEMS
id|ICMP6_MIB_OUTPARMPROBLEMS
comma
multiline_comment|/* OutParmProblems */
DECL|enumerator|ICMP6_MIB_OUTECHOREPLIES
id|ICMP6_MIB_OUTECHOREPLIES
comma
multiline_comment|/* OutEchoReplies */
DECL|enumerator|ICMP6_MIB_OUTROUTERSOLICITS
id|ICMP6_MIB_OUTROUTERSOLICITS
comma
multiline_comment|/* OutRouterSolicits */
DECL|enumerator|ICMP6_MIB_OUTNEIGHBORSOLICITS
id|ICMP6_MIB_OUTNEIGHBORSOLICITS
comma
multiline_comment|/* OutNeighborSolicits */
DECL|enumerator|ICMP6_MIB_OUTNEIGHBORADVERTISEMENTS
id|ICMP6_MIB_OUTNEIGHBORADVERTISEMENTS
comma
multiline_comment|/* OutNeighborAdvertisements */
DECL|enumerator|ICMP6_MIB_OUTREDIRECTS
id|ICMP6_MIB_OUTREDIRECTS
comma
multiline_comment|/* OutRedirects */
DECL|enumerator|ICMP6_MIB_OUTGROUPMEMBRESPONSES
id|ICMP6_MIB_OUTGROUPMEMBRESPONSES
comma
multiline_comment|/* OutGroupMembResponses */
DECL|enumerator|ICMP6_MIB_OUTGROUPMEMBREDUCTIONS
id|ICMP6_MIB_OUTGROUPMEMBREDUCTIONS
comma
multiline_comment|/* OutGroupMembReductions */
DECL|enumerator|__ICMP6_MIB_MAX
id|__ICMP6_MIB_MAX
)brace
suffix:semicolon
multiline_comment|/* tcp mib definitions */
multiline_comment|/*&n; * RFC 1213:  MIB-II TCP group&n; * RFC 2012 (updates 1213):  SNMPv2-MIB-TCP&n; */
r_enum
(brace
DECL|enumerator|TCP_MIB_NUM
id|TCP_MIB_NUM
op_assign
l_int|0
comma
DECL|enumerator|TCP_MIB_RTOALGORITHM
id|TCP_MIB_RTOALGORITHM
comma
multiline_comment|/* RtoAlgorithm */
DECL|enumerator|TCP_MIB_RTOMIN
id|TCP_MIB_RTOMIN
comma
multiline_comment|/* RtoMin */
DECL|enumerator|TCP_MIB_RTOMAX
id|TCP_MIB_RTOMAX
comma
multiline_comment|/* RtoMax */
DECL|enumerator|TCP_MIB_MAXCONN
id|TCP_MIB_MAXCONN
comma
multiline_comment|/* MaxConn */
DECL|enumerator|TCP_MIB_ACTIVEOPENS
id|TCP_MIB_ACTIVEOPENS
comma
multiline_comment|/* ActiveOpens */
DECL|enumerator|TCP_MIB_PASSIVEOPENS
id|TCP_MIB_PASSIVEOPENS
comma
multiline_comment|/* PassiveOpens */
DECL|enumerator|TCP_MIB_ATTEMPTFAILS
id|TCP_MIB_ATTEMPTFAILS
comma
multiline_comment|/* AttemptFails */
DECL|enumerator|TCP_MIB_ESTABRESETS
id|TCP_MIB_ESTABRESETS
comma
multiline_comment|/* EstabResets */
DECL|enumerator|TCP_MIB_CURRESTAB
id|TCP_MIB_CURRESTAB
comma
multiline_comment|/* CurrEstab */
DECL|enumerator|TCP_MIB_INSEGS
id|TCP_MIB_INSEGS
comma
multiline_comment|/* InSegs */
DECL|enumerator|TCP_MIB_OUTSEGS
id|TCP_MIB_OUTSEGS
comma
multiline_comment|/* OutSegs */
DECL|enumerator|TCP_MIB_RETRANSSEGS
id|TCP_MIB_RETRANSSEGS
comma
multiline_comment|/* RetransSegs */
DECL|enumerator|TCP_MIB_INERRS
id|TCP_MIB_INERRS
comma
multiline_comment|/* InErrs */
DECL|enumerator|TCP_MIB_OUTRSTS
id|TCP_MIB_OUTRSTS
comma
multiline_comment|/* OutRsts */
DECL|enumerator|__TCP_MIB_MAX
id|__TCP_MIB_MAX
)brace
suffix:semicolon
multiline_comment|/* udp mib definitions */
multiline_comment|/*&n; * RFC 1213:  MIB-II UDP group&n; * RFC 2013 (updates 1213):  SNMPv2-MIB-UDP&n; */
r_enum
(brace
DECL|enumerator|UDP_MIB_NUM
id|UDP_MIB_NUM
op_assign
l_int|0
comma
DECL|enumerator|UDP_MIB_INDATAGRAMS
id|UDP_MIB_INDATAGRAMS
comma
multiline_comment|/* InDatagrams */
DECL|enumerator|UDP_MIB_NOPORTS
id|UDP_MIB_NOPORTS
comma
multiline_comment|/* NoPorts */
DECL|enumerator|UDP_MIB_INERRORS
id|UDP_MIB_INERRORS
comma
multiline_comment|/* InErrors */
DECL|enumerator|UDP_MIB_OUTDATAGRAMS
id|UDP_MIB_OUTDATAGRAMS
comma
multiline_comment|/* OutDatagrams */
DECL|enumerator|__UDP_MIB_MAX
id|__UDP_MIB_MAX
)brace
suffix:semicolon
multiline_comment|/* sctp mib definitions */
multiline_comment|/*&n; * draft-ietf-sigtran-sctp-mib-07.txt&n; */
r_enum
(brace
DECL|enumerator|SCTP_MIB_NUM
id|SCTP_MIB_NUM
op_assign
l_int|0
comma
DECL|enumerator|SCTP_MIB_CURRESTAB
id|SCTP_MIB_CURRESTAB
comma
multiline_comment|/* CurrEstab */
DECL|enumerator|SCTP_MIB_ACTIVEESTABS
id|SCTP_MIB_ACTIVEESTABS
comma
multiline_comment|/* ActiveEstabs */
DECL|enumerator|SCTP_MIB_PASSIVEESTABS
id|SCTP_MIB_PASSIVEESTABS
comma
multiline_comment|/* PassiveEstabs */
DECL|enumerator|SCTP_MIB_ABORTEDS
id|SCTP_MIB_ABORTEDS
comma
multiline_comment|/* Aborteds */
DECL|enumerator|SCTP_MIB_SHUTDOWNS
id|SCTP_MIB_SHUTDOWNS
comma
multiline_comment|/* Shutdowns */
DECL|enumerator|SCTP_MIB_OUTOFBLUES
id|SCTP_MIB_OUTOFBLUES
comma
multiline_comment|/* OutOfBlues */
DECL|enumerator|SCTP_MIB_CHECKSUMERRORS
id|SCTP_MIB_CHECKSUMERRORS
comma
multiline_comment|/* ChecksumErrors */
DECL|enumerator|SCTP_MIB_OUTCTRLCHUNKS
id|SCTP_MIB_OUTCTRLCHUNKS
comma
multiline_comment|/* OutCtrlChunks */
DECL|enumerator|SCTP_MIB_OUTORDERCHUNKS
id|SCTP_MIB_OUTORDERCHUNKS
comma
multiline_comment|/* OutOrderChunks */
DECL|enumerator|SCTP_MIB_OUTUNORDERCHUNKS
id|SCTP_MIB_OUTUNORDERCHUNKS
comma
multiline_comment|/* OutUnorderChunks */
DECL|enumerator|SCTP_MIB_INCTRLCHUNKS
id|SCTP_MIB_INCTRLCHUNKS
comma
multiline_comment|/* InCtrlChunks */
DECL|enumerator|SCTP_MIB_INORDERCHUNKS
id|SCTP_MIB_INORDERCHUNKS
comma
multiline_comment|/* InOrderChunks */
DECL|enumerator|SCTP_MIB_INUNORDERCHUNKS
id|SCTP_MIB_INUNORDERCHUNKS
comma
multiline_comment|/* InUnorderChunks */
DECL|enumerator|SCTP_MIB_FRAGUSRMSGS
id|SCTP_MIB_FRAGUSRMSGS
comma
multiline_comment|/* FragUsrMsgs */
DECL|enumerator|SCTP_MIB_REASMUSRMSGS
id|SCTP_MIB_REASMUSRMSGS
comma
multiline_comment|/* ReasmUsrMsgs */
DECL|enumerator|SCTP_MIB_OUTSCTPPACKS
id|SCTP_MIB_OUTSCTPPACKS
comma
multiline_comment|/* OutSCTPPacks */
DECL|enumerator|SCTP_MIB_INSCTPPACKS
id|SCTP_MIB_INSCTPPACKS
comma
multiline_comment|/* InSCTPPacks */
DECL|enumerator|SCTP_MIB_RTOALGORITHM
id|SCTP_MIB_RTOALGORITHM
comma
multiline_comment|/* RtoAlgorithm */
DECL|enumerator|SCTP_MIB_RTOMIN
id|SCTP_MIB_RTOMIN
comma
multiline_comment|/* RtoMin */
DECL|enumerator|SCTP_MIB_RTOMAX
id|SCTP_MIB_RTOMAX
comma
multiline_comment|/* RtoMax */
DECL|enumerator|SCTP_MIB_RTOINITIAL
id|SCTP_MIB_RTOINITIAL
comma
multiline_comment|/* RtoInitial */
DECL|enumerator|SCTP_MIB_VALCOOKIELIFE
id|SCTP_MIB_VALCOOKIELIFE
comma
multiline_comment|/* ValCookieLife */
DECL|enumerator|SCTP_MIB_MAXINITRETR
id|SCTP_MIB_MAXINITRETR
comma
multiline_comment|/* MaxInitRetr */
DECL|enumerator|__SCTP_MIB_MAX
id|__SCTP_MIB_MAX
)brace
suffix:semicolon
multiline_comment|/* linux mib definitions */
r_enum
(brace
DECL|enumerator|LINUX_MIB_NUM
id|LINUX_MIB_NUM
op_assign
l_int|0
comma
DECL|enumerator|LINUX_MIB_SYNCOOKIESSENT
id|LINUX_MIB_SYNCOOKIESSENT
comma
multiline_comment|/* SyncookiesSent */
DECL|enumerator|LINUX_MIB_SYNCOOKIESRECV
id|LINUX_MIB_SYNCOOKIESRECV
comma
multiline_comment|/* SyncookiesRecv */
DECL|enumerator|LINUX_MIB_SYNCOOKIESFAILED
id|LINUX_MIB_SYNCOOKIESFAILED
comma
multiline_comment|/* SyncookiesFailed */
DECL|enumerator|LINUX_MIB_EMBRYONICRSTS
id|LINUX_MIB_EMBRYONICRSTS
comma
multiline_comment|/* EmbryonicRsts */
DECL|enumerator|LINUX_MIB_PRUNECALLED
id|LINUX_MIB_PRUNECALLED
comma
multiline_comment|/* PruneCalled */
DECL|enumerator|LINUX_MIB_RCVPRUNED
id|LINUX_MIB_RCVPRUNED
comma
multiline_comment|/* RcvPruned */
DECL|enumerator|LINUX_MIB_OFOPRUNED
id|LINUX_MIB_OFOPRUNED
comma
multiline_comment|/* OfoPruned */
DECL|enumerator|LINUX_MIB_OUTOFWINDOWICMPS
id|LINUX_MIB_OUTOFWINDOWICMPS
comma
multiline_comment|/* OutOfWindowIcmps */
DECL|enumerator|LINUX_MIB_LOCKDROPPEDICMPS
id|LINUX_MIB_LOCKDROPPEDICMPS
comma
multiline_comment|/* LockDroppedIcmps */
DECL|enumerator|LINUX_MIB_ARPFILTER
id|LINUX_MIB_ARPFILTER
comma
multiline_comment|/* ArpFilter */
DECL|enumerator|LINUX_MIB_TIMEWAITED
id|LINUX_MIB_TIMEWAITED
comma
multiline_comment|/* TimeWaited */
DECL|enumerator|LINUX_MIB_TIMEWAITRECYCLED
id|LINUX_MIB_TIMEWAITRECYCLED
comma
multiline_comment|/* TimeWaitRecycled */
DECL|enumerator|LINUX_MIB_TIMEWAITKILLED
id|LINUX_MIB_TIMEWAITKILLED
comma
multiline_comment|/* TimeWaitKilled */
DECL|enumerator|LINUX_MIB_PAWSPASSIVEREJECTED
id|LINUX_MIB_PAWSPASSIVEREJECTED
comma
multiline_comment|/* PAWSPassiveRejected */
DECL|enumerator|LINUX_MIB_PAWSACTIVEREJECTED
id|LINUX_MIB_PAWSACTIVEREJECTED
comma
multiline_comment|/* PAWSActiveRejected */
DECL|enumerator|LINUX_MIB_PAWSESTABREJECTED
id|LINUX_MIB_PAWSESTABREJECTED
comma
multiline_comment|/* PAWSEstabRejected */
DECL|enumerator|LINUX_MIB_DELAYEDACKS
id|LINUX_MIB_DELAYEDACKS
comma
multiline_comment|/* DelayedACKs */
DECL|enumerator|LINUX_MIB_DELAYEDACKLOCKED
id|LINUX_MIB_DELAYEDACKLOCKED
comma
multiline_comment|/* DelayedACKLocked */
DECL|enumerator|LINUX_MIB_DELAYEDACKLOST
id|LINUX_MIB_DELAYEDACKLOST
comma
multiline_comment|/* DelayedACKLost */
DECL|enumerator|LINUX_MIB_LISTENOVERFLOWS
id|LINUX_MIB_LISTENOVERFLOWS
comma
multiline_comment|/* ListenOverflows */
DECL|enumerator|LINUX_MIB_LISTENDROPS
id|LINUX_MIB_LISTENDROPS
comma
multiline_comment|/* ListenDrops */
DECL|enumerator|LINUX_MIB_TCPPREQUEUED
id|LINUX_MIB_TCPPREQUEUED
comma
multiline_comment|/* TCPPrequeued */
DECL|enumerator|LINUX_MIB_TCPDIRECTCOPYFROMBACKLOG
id|LINUX_MIB_TCPDIRECTCOPYFROMBACKLOG
comma
multiline_comment|/* TCPDirectCopyFromBacklog */
DECL|enumerator|LINUX_MIB_TCPDIRECTCOPYFROMPREQUEUE
id|LINUX_MIB_TCPDIRECTCOPYFROMPREQUEUE
comma
multiline_comment|/* TCPDirectCopyFromPrequeue */
DECL|enumerator|LINUX_MIB_TCPPREQUEUEDROPPED
id|LINUX_MIB_TCPPREQUEUEDROPPED
comma
multiline_comment|/* TCPPrequeueDropped */
DECL|enumerator|LINUX_MIB_TCPHPHITS
id|LINUX_MIB_TCPHPHITS
comma
multiline_comment|/* TCPHPHits */
DECL|enumerator|LINUX_MIB_TCPHPHITSTOUSER
id|LINUX_MIB_TCPHPHITSTOUSER
comma
multiline_comment|/* TCPHPHitsToUser */
DECL|enumerator|LINUX_MIB_TCPPUREACKS
id|LINUX_MIB_TCPPUREACKS
comma
multiline_comment|/* TCPPureAcks */
DECL|enumerator|LINUX_MIB_TCPHPACKS
id|LINUX_MIB_TCPHPACKS
comma
multiline_comment|/* TCPHPAcks */
DECL|enumerator|LINUX_MIB_TCPRENORECOVERY
id|LINUX_MIB_TCPRENORECOVERY
comma
multiline_comment|/* TCPRenoRecovery */
DECL|enumerator|LINUX_MIB_TCPSACKRECOVERY
id|LINUX_MIB_TCPSACKRECOVERY
comma
multiline_comment|/* TCPSackRecovery */
DECL|enumerator|LINUX_MIB_TCPSACKRENEGING
id|LINUX_MIB_TCPSACKRENEGING
comma
multiline_comment|/* TCPSACKReneging */
DECL|enumerator|LINUX_MIB_TCPFACKREORDER
id|LINUX_MIB_TCPFACKREORDER
comma
multiline_comment|/* TCPFACKReorder */
DECL|enumerator|LINUX_MIB_TCPSACKREORDER
id|LINUX_MIB_TCPSACKREORDER
comma
multiline_comment|/* TCPSACKReorder */
DECL|enumerator|LINUX_MIB_TCPRENOREORDER
id|LINUX_MIB_TCPRENOREORDER
comma
multiline_comment|/* TCPRenoReorder */
DECL|enumerator|LINUX_MIB_TCPTSREORDER
id|LINUX_MIB_TCPTSREORDER
comma
multiline_comment|/* TCPTSReorder */
DECL|enumerator|LINUX_MIB_TCPFULLUNDO
id|LINUX_MIB_TCPFULLUNDO
comma
multiline_comment|/* TCPFullUndo */
DECL|enumerator|LINUX_MIB_TCPPARTIALUNDO
id|LINUX_MIB_TCPPARTIALUNDO
comma
multiline_comment|/* TCPPartialUndo */
DECL|enumerator|LINUX_MIB_TCPDSACKUNDO
id|LINUX_MIB_TCPDSACKUNDO
comma
multiline_comment|/* TCPDSACKUndo */
DECL|enumerator|LINUX_MIB_TCPLOSSUNDO
id|LINUX_MIB_TCPLOSSUNDO
comma
multiline_comment|/* TCPLossUndo */
DECL|enumerator|LINUX_MIB_TCPLOSS
id|LINUX_MIB_TCPLOSS
comma
multiline_comment|/* TCPLoss */
DECL|enumerator|LINUX_MIB_TCPLOSTRETRANSMIT
id|LINUX_MIB_TCPLOSTRETRANSMIT
comma
multiline_comment|/* TCPLostRetransmit */
DECL|enumerator|LINUX_MIB_TCPRENOFAILURES
id|LINUX_MIB_TCPRENOFAILURES
comma
multiline_comment|/* TCPRenoFailures */
DECL|enumerator|LINUX_MIB_TCPSACKFAILURES
id|LINUX_MIB_TCPSACKFAILURES
comma
multiline_comment|/* TCPSackFailures */
DECL|enumerator|LINUX_MIB_TCPLOSSFAILURES
id|LINUX_MIB_TCPLOSSFAILURES
comma
multiline_comment|/* TCPLossFailures */
DECL|enumerator|LINUX_MIB_TCPFASTRETRANS
id|LINUX_MIB_TCPFASTRETRANS
comma
multiline_comment|/* TCPFastRetrans */
DECL|enumerator|LINUX_MIB_TCPFORWARDRETRANS
id|LINUX_MIB_TCPFORWARDRETRANS
comma
multiline_comment|/* TCPForwardRetrans */
DECL|enumerator|LINUX_MIB_TCPSLOWSTARTRETRANS
id|LINUX_MIB_TCPSLOWSTARTRETRANS
comma
multiline_comment|/* TCPSlowStartRetrans */
DECL|enumerator|LINUX_MIB_TCPTIMEOUTS
id|LINUX_MIB_TCPTIMEOUTS
comma
multiline_comment|/* TCPTimeouts */
DECL|enumerator|LINUX_MIB_TCPRENORECOVERYFAIL
id|LINUX_MIB_TCPRENORECOVERYFAIL
comma
multiline_comment|/* TCPRenoRecoveryFail */
DECL|enumerator|LINUX_MIB_TCPSACKRECOVERYFAIL
id|LINUX_MIB_TCPSACKRECOVERYFAIL
comma
multiline_comment|/* TCPSackRecoveryFail */
DECL|enumerator|LINUX_MIB_TCPSCHEDULERFAILED
id|LINUX_MIB_TCPSCHEDULERFAILED
comma
multiline_comment|/* TCPSchedulerFailed */
DECL|enumerator|LINUX_MIB_TCPRCVCOLLAPSED
id|LINUX_MIB_TCPRCVCOLLAPSED
comma
multiline_comment|/* TCPRcvCollapsed */
DECL|enumerator|LINUX_MIB_TCPDSACKOLDSENT
id|LINUX_MIB_TCPDSACKOLDSENT
comma
multiline_comment|/* TCPDSACKOldSent */
DECL|enumerator|LINUX_MIB_TCPDSACKOFOSENT
id|LINUX_MIB_TCPDSACKOFOSENT
comma
multiline_comment|/* TCPDSACKOfoSent */
DECL|enumerator|LINUX_MIB_TCPDSACKRECV
id|LINUX_MIB_TCPDSACKRECV
comma
multiline_comment|/* TCPDSACKRecv */
DECL|enumerator|LINUX_MIB_TCPDSACKOFORECV
id|LINUX_MIB_TCPDSACKOFORECV
comma
multiline_comment|/* TCPDSACKOfoRecv */
DECL|enumerator|LINUX_MIB_TCPABORTONSYN
id|LINUX_MIB_TCPABORTONSYN
comma
multiline_comment|/* TCPAbortOnSyn */
DECL|enumerator|LINUX_MIB_TCPABORTONDATA
id|LINUX_MIB_TCPABORTONDATA
comma
multiline_comment|/* TCPAbortOnData */
DECL|enumerator|LINUX_MIB_TCPABORTONCLOSE
id|LINUX_MIB_TCPABORTONCLOSE
comma
multiline_comment|/* TCPAbortOnClose */
DECL|enumerator|LINUX_MIB_TCPABORTONMEMORY
id|LINUX_MIB_TCPABORTONMEMORY
comma
multiline_comment|/* TCPAbortOnMemory */
DECL|enumerator|LINUX_MIB_TCPABORTONTIMEOUT
id|LINUX_MIB_TCPABORTONTIMEOUT
comma
multiline_comment|/* TCPAbortOnTimeout */
DECL|enumerator|LINUX_MIB_TCPABORTONLINGER
id|LINUX_MIB_TCPABORTONLINGER
comma
multiline_comment|/* TCPAbortOnLinger */
DECL|enumerator|LINUX_MIB_TCPABORTFAILED
id|LINUX_MIB_TCPABORTFAILED
comma
multiline_comment|/* TCPAbortFailed */
DECL|enumerator|LINUX_MIB_TCPMEMORYPRESSURES
id|LINUX_MIB_TCPMEMORYPRESSURES
comma
multiline_comment|/* TCPMemoryPressures */
DECL|enumerator|__LINUX_MIB_MAX
id|__LINUX_MIB_MAX
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_SNMP_H */
eof
