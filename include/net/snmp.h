multiline_comment|/*&n; *&n; *&t;&t;SNMP MIB entries for the IP subsystem.&n; *&t;&t;&n; *&t;&t;Alan Cox &lt;gw4pts@gw4pts.ampr.org&gt;&n; *&n; *&t;&t;We don&squot;t chose to implement SNMP in the kernel (this would&n; *&t;&t;be silly as SNMP is a pain in the backside in places). We do&n; *&t;&t;however need to collect the MIB statistics and export them&n; *&t;&t;out of /proc (eventually)&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;&t;$Id: snmp.h,v 1.19 2001/06/14 13:40:46 davem Exp $&n; *&n; */
macro_line|#ifndef _SNMP_H
DECL|macro|_SNMP_H
mdefine_line|#define _SNMP_H
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/snmp.h&gt;
multiline_comment|/*&n; * Mibs are stored in array of unsigned long.&n; */
multiline_comment|/*&n; * struct snmp_mib{}&n; *  - list of entries for particular API (such as /proc/net/snmp)&n; *  - name of entries.&n; */
DECL|struct|snmp_mib
r_struct
id|snmp_mib
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|entry
r_int
id|entry
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SNMP_MIB_ITEM
mdefine_line|#define SNMP_MIB_ITEM(_name,_entry)&t;{&t;&bslash;&n;&t;.name = _name,&t;&t;&t;&t;&bslash;&n;&t;.entry = _entry,&t;&t;&t;&bslash;&n;}
DECL|macro|SNMP_MIB_SENTINEL
mdefine_line|#define SNMP_MIB_SENTINEL {&t;&bslash;&n;&t;.name = NULL,&t;&t;&bslash;&n;&t;.entry = 0,&t;&t;&bslash;&n;}
multiline_comment|/*&n; * We use all unsigned longs. Linux will soon be so reliable that even &n; * these will rapidly get too small 8-). Seriously consider the IpInReceives &n; * count on the 20Gb/s + networks people expect in a few years time!&n; */
multiline_comment|/* &n; * The rule for padding: &n; * Best is power of two because then the right structure can be found by a &n; * simple shift. The structure should be always cache line aligned.&n; * gcc needs n=alignto(cachelinesize, popcnt(sizeof(bla_mib))) shift/add &n; * instructions to emulate multiply in case it is not power-of-two. &n; * Currently n is always &lt;=3 for all sizes so simple cache line alignment &n; * is enough. &n; * &n; * The best solution would be a global CPU local area , especially on 64 &n; * and 128byte cacheline machine it makes a *lot* of sense -AK&n; */
DECL|macro|__SNMP_MIB_ALIGN__
mdefine_line|#define __SNMP_MIB_ALIGN__&t;____cacheline_aligned
multiline_comment|/* IPstats */
DECL|macro|IPSTATS_MIB_MAX
mdefine_line|#define IPSTATS_MIB_MAX&t;__IPSTATS_MIB_MAX
DECL|struct|ipstats_mib
r_struct
id|ipstats_mib
(brace
DECL|member|mibs
r_int
r_int
id|mibs
(braket
id|IPSTATS_MIB_MAX
)braket
suffix:semicolon
DECL|variable|__SNMP_MIB_ALIGN__
)brace
id|__SNMP_MIB_ALIGN__
suffix:semicolon
multiline_comment|/* ICMP */
DECL|macro|ICMP_MIB_DUMMY
mdefine_line|#define ICMP_MIB_DUMMY&t;__ICMP_MIB_MAX
DECL|macro|ICMP_MIB_MAX
mdefine_line|#define ICMP_MIB_MAX&t;(__ICMP_MIB_MAX + 1)
DECL|struct|icmp_mib
r_struct
id|icmp_mib
(brace
DECL|member|mibs
r_int
r_int
id|mibs
(braket
id|ICMP_MIB_MAX
)braket
suffix:semicolon
DECL|variable|__SNMP_MIB_ALIGN__
)brace
id|__SNMP_MIB_ALIGN__
suffix:semicolon
multiline_comment|/* ICMP6 (IPv6-ICMP) */
DECL|macro|ICMP6_MIB_MAX
mdefine_line|#define ICMP6_MIB_MAX&t;__ICMP6_MIB_MAX
DECL|struct|icmpv6_mib
r_struct
id|icmpv6_mib
(brace
DECL|member|mibs
r_int
r_int
id|mibs
(braket
id|ICMP6_MIB_MAX
)braket
suffix:semicolon
DECL|variable|__SNMP_MIB_ALIGN__
)brace
id|__SNMP_MIB_ALIGN__
suffix:semicolon
multiline_comment|/* TCP */
DECL|macro|TCP_MIB_MAX
mdefine_line|#define TCP_MIB_MAX&t;__TCP_MIB_MAX
DECL|struct|tcp_mib
r_struct
id|tcp_mib
(brace
DECL|member|mibs
r_int
r_int
id|mibs
(braket
id|TCP_MIB_MAX
)braket
suffix:semicolon
DECL|variable|__SNMP_MIB_ALIGN__
)brace
id|__SNMP_MIB_ALIGN__
suffix:semicolon
multiline_comment|/* UDP */
DECL|macro|UDP_MIB_MAX
mdefine_line|#define UDP_MIB_MAX&t;__UDP_MIB_MAX
DECL|struct|udp_mib
r_struct
id|udp_mib
(brace
DECL|member|mibs
r_int
r_int
id|mibs
(braket
id|UDP_MIB_MAX
)braket
suffix:semicolon
DECL|variable|__SNMP_MIB_ALIGN__
)brace
id|__SNMP_MIB_ALIGN__
suffix:semicolon
multiline_comment|/* SCTP */
DECL|macro|SCTP_MIB_MAX
mdefine_line|#define SCTP_MIB_MAX&t;__SCTP_MIB_MAX
DECL|struct|sctp_mib
r_struct
id|sctp_mib
(brace
DECL|member|mibs
r_int
r_int
id|mibs
(braket
id|SCTP_MIB_MAX
)braket
suffix:semicolon
DECL|variable|__SNMP_MIB_ALIGN__
)brace
id|__SNMP_MIB_ALIGN__
suffix:semicolon
multiline_comment|/* Linux */
DECL|macro|LINUX_MIB_MAX
mdefine_line|#define LINUX_MIB_MAX&t;__LINUX_MIB_MAX
DECL|struct|linux_mib
r_struct
id|linux_mib
(brace
DECL|member|mibs
r_int
r_int
id|mibs
(braket
id|LINUX_MIB_MAX
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * FIXME: On x86 and some other CPUs the split into user and softirq parts&n; * is not needed because addl $1,memory is atomic against interrupts (but &n; * atomic_inc would be overkill because of the lock cycles). Wants new &n; * nonlocked_atomic_inc() primitives -AK&n; */
DECL|macro|DEFINE_SNMP_STAT
mdefine_line|#define DEFINE_SNMP_STAT(type, name)&t;&bslash;&n;&t;__typeof__(type) *name[2]
DECL|macro|DECLARE_SNMP_STAT
mdefine_line|#define DECLARE_SNMP_STAT(type, name)&t;&bslash;&n;&t;extern __typeof__(type) *name[2]
DECL|macro|SNMP_STAT_BHPTR
mdefine_line|#define SNMP_STAT_BHPTR(name)&t;(name[0])
DECL|macro|SNMP_STAT_USRPTR
mdefine_line|#define SNMP_STAT_USRPTR(name)&t;(name[1])
DECL|macro|SNMP_INC_STATS_BH
mdefine_line|#define SNMP_INC_STATS_BH(mib, field) &t;&bslash;&n;&t;(per_cpu_ptr(mib[0], _smp_processor_id())-&gt;mibs[field]++)
DECL|macro|SNMP_INC_STATS_OFFSET_BH
mdefine_line|#define SNMP_INC_STATS_OFFSET_BH(mib, field, offset)&t;&bslash;&n;&t;(per_cpu_ptr(mib[0], _smp_processor_id())-&gt;mibs[field + (offset)]++)
DECL|macro|SNMP_INC_STATS_USER
mdefine_line|#define SNMP_INC_STATS_USER(mib, field) &bslash;&n;&t;(per_cpu_ptr(mib[1], _smp_processor_id())-&gt;mibs[field]++)
DECL|macro|SNMP_INC_STATS
mdefine_line|#define SNMP_INC_STATS(mib, field) &t;&bslash;&n;&t;(per_cpu_ptr(mib[!in_softirq()], _smp_processor_id())-&gt;mibs[field]++)
DECL|macro|SNMP_DEC_STATS
mdefine_line|#define SNMP_DEC_STATS(mib, field) &t;&bslash;&n;&t;(per_cpu_ptr(mib[!in_softirq()], _smp_processor_id())-&gt;mibs[field]--)
DECL|macro|SNMP_ADD_STATS_BH
mdefine_line|#define SNMP_ADD_STATS_BH(mib, field, addend) &t;&bslash;&n;&t;(per_cpu_ptr(mib[0], _smp_processor_id())-&gt;mibs[field] += addend)
DECL|macro|SNMP_ADD_STATS_USER
mdefine_line|#define SNMP_ADD_STATS_USER(mib, field, addend) &t;&bslash;&n;&t;(per_cpu_ptr(mib[1], _smp_processor_id())-&gt;mibs[field] += addend)
macro_line|#endif
eof
