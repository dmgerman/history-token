macro_line|#ifndef __LINUX_PKT_SCHED_H
DECL|macro|__LINUX_PKT_SCHED_H
mdefine_line|#define __LINUX_PKT_SCHED_H
multiline_comment|/* Logical priority bands not depending on specific packet scheduler.&n;   Every scheduler will map them to real traffic classes, if it has&n;   no more precise mechanism to classify packets.&n;&n;   These numbers have no special meaning, though their coincidence&n;   with obsolete IPv6 values is not occasional :-). New IPv6 drafts&n;   preferred full anarchy inspired by diffserv group.&n;&n;   Note: TC_PRIO_BESTEFFORT does not mean that it is the most unhappy&n;   class, actually, as rule it will be handled with more care than&n;   filler or even bulk.&n; */
DECL|macro|TC_PRIO_BESTEFFORT
mdefine_line|#define TC_PRIO_BESTEFFORT&t;&t;0
DECL|macro|TC_PRIO_FILLER
mdefine_line|#define TC_PRIO_FILLER&t;&t;&t;1
DECL|macro|TC_PRIO_BULK
mdefine_line|#define TC_PRIO_BULK&t;&t;&t;2
DECL|macro|TC_PRIO_INTERACTIVE_BULK
mdefine_line|#define TC_PRIO_INTERACTIVE_BULK&t;4
DECL|macro|TC_PRIO_INTERACTIVE
mdefine_line|#define TC_PRIO_INTERACTIVE&t;&t;6
DECL|macro|TC_PRIO_CONTROL
mdefine_line|#define TC_PRIO_CONTROL&t;&t;&t;7
DECL|macro|TC_PRIO_MAX
mdefine_line|#define TC_PRIO_MAX&t;&t;&t;15
multiline_comment|/* Generic queue statistics, available for all the elements.&n;   Particular schedulers may have also their private records.&n; */
DECL|struct|tc_stats
r_struct
id|tc_stats
(brace
DECL|member|bytes
id|__u64
id|bytes
suffix:semicolon
multiline_comment|/* NUmber of enqueues bytes */
DECL|member|packets
id|__u32
id|packets
suffix:semicolon
multiline_comment|/* Number of enqueued packets&t;*/
DECL|member|drops
id|__u32
id|drops
suffix:semicolon
multiline_comment|/* Packets dropped because of lack of resources */
DECL|member|overlimits
id|__u32
id|overlimits
suffix:semicolon
multiline_comment|/* Number of throttle events when this&n;&t;&t;&t;&t;&t; * flow goes out of allocated bandwidth */
DECL|member|bps
id|__u32
id|bps
suffix:semicolon
multiline_comment|/* Current flow byte rate */
DECL|member|pps
id|__u32
id|pps
suffix:semicolon
multiline_comment|/* Current flow packet rate */
DECL|member|qlen
id|__u32
id|qlen
suffix:semicolon
DECL|member|backlog
id|__u32
id|backlog
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_estimator
r_struct
id|tc_estimator
(brace
DECL|member|interval
r_int
r_char
id|interval
suffix:semicolon
DECL|member|ewma_log
r_int
r_char
id|ewma_log
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &quot;Handles&quot;&n;   ---------&n;&n;    All the traffic control objects have 32bit identifiers, or &quot;handles&quot;.&n;&n;    They can be considered as opaque numbers from user API viewpoint,&n;    but actually they always consist of two fields: major and&n;    minor numbers, which are interpreted by kernel specially,&n;    that may be used by applications, though not recommended.&n;&n;    F.e. qdisc handles always have minor number equal to zero,&n;    classes (or flows) have major equal to parent qdisc major, and&n;    minor uniquely identifying class inside qdisc.&n;&n;    Macros to manipulate handles:&n; */
DECL|macro|TC_H_MAJ_MASK
mdefine_line|#define TC_H_MAJ_MASK (0xFFFF0000U)
DECL|macro|TC_H_MIN_MASK
mdefine_line|#define TC_H_MIN_MASK (0x0000FFFFU)
DECL|macro|TC_H_MAJ
mdefine_line|#define TC_H_MAJ(h) ((h)&amp;TC_H_MAJ_MASK)
DECL|macro|TC_H_MIN
mdefine_line|#define TC_H_MIN(h) ((h)&amp;TC_H_MIN_MASK)
DECL|macro|TC_H_MAKE
mdefine_line|#define TC_H_MAKE(maj,min) (((maj)&amp;TC_H_MAJ_MASK)|((min)&amp;TC_H_MIN_MASK))
DECL|macro|TC_H_UNSPEC
mdefine_line|#define TC_H_UNSPEC&t;(0U)
DECL|macro|TC_H_ROOT
mdefine_line|#define TC_H_ROOT&t;(0xFFFFFFFFU)
DECL|macro|TC_H_INGRESS
mdefine_line|#define TC_H_INGRESS    (0xFFFFFFF1U)
DECL|struct|tc_ratespec
r_struct
id|tc_ratespec
(brace
DECL|member|cell_log
r_int
r_char
id|cell_log
suffix:semicolon
DECL|member|__reserved
r_int
r_char
id|__reserved
suffix:semicolon
DECL|member|feature
r_int
r_int
id|feature
suffix:semicolon
DECL|member|addend
r_int
id|addend
suffix:semicolon
DECL|member|mpu
r_int
r_int
id|mpu
suffix:semicolon
DECL|member|rate
id|__u32
id|rate
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* FIFO section */
DECL|struct|tc_fifo_qopt
r_struct
id|tc_fifo_qopt
(brace
DECL|member|limit
id|__u32
id|limit
suffix:semicolon
multiline_comment|/* Queue length: bytes for bfifo, packets for pfifo */
)brace
suffix:semicolon
multiline_comment|/* PRIO section */
DECL|macro|TCQ_PRIO_BANDS
mdefine_line|#define TCQ_PRIO_BANDS&t;16
DECL|struct|tc_prio_qopt
r_struct
id|tc_prio_qopt
(brace
DECL|member|bands
r_int
id|bands
suffix:semicolon
multiline_comment|/* Number of bands */
DECL|member|priomap
id|__u8
id|priomap
(braket
id|TC_PRIO_MAX
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Map: logical priority -&gt; PRIO band */
)brace
suffix:semicolon
multiline_comment|/* TBF section */
DECL|struct|tc_tbf_qopt
r_struct
id|tc_tbf_qopt
(brace
DECL|member|rate
r_struct
id|tc_ratespec
id|rate
suffix:semicolon
DECL|member|peakrate
r_struct
id|tc_ratespec
id|peakrate
suffix:semicolon
DECL|member|limit
id|__u32
id|limit
suffix:semicolon
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
DECL|member|mtu
id|__u32
id|mtu
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCA_TBF_UNSPEC
id|TCA_TBF_UNSPEC
comma
DECL|enumerator|TCA_TBF_PARMS
id|TCA_TBF_PARMS
comma
DECL|enumerator|TCA_TBF_RTAB
id|TCA_TBF_RTAB
comma
DECL|enumerator|TCA_TBF_PTAB
id|TCA_TBF_PTAB
comma
DECL|enumerator|__TCA_TBF_MAX
id|__TCA_TBF_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_TBF_MAX
mdefine_line|#define TCA_TBF_MAX (__TCA_TBF_MAX - 1)
multiline_comment|/* TEQL section */
multiline_comment|/* TEQL does not require any parameters */
multiline_comment|/* SFQ section */
DECL|struct|tc_sfq_qopt
r_struct
id|tc_sfq_qopt
(brace
DECL|member|quantum
r_int
id|quantum
suffix:semicolon
multiline_comment|/* Bytes per round allocated to flow */
DECL|member|perturb_period
r_int
id|perturb_period
suffix:semicolon
multiline_comment|/* Period of hash perturbation */
DECL|member|limit
id|__u32
id|limit
suffix:semicolon
multiline_comment|/* Maximal packets in queue */
DECL|member|divisor
r_int
id|divisor
suffix:semicolon
multiline_comment|/* Hash divisor  */
DECL|member|flows
r_int
id|flows
suffix:semicolon
multiline_comment|/* Maximal number of flows  */
)brace
suffix:semicolon
multiline_comment|/*&n; *  NOTE: limit, divisor and flows are hardwired to code at the moment.&n; *&n; *&t;limit=flows=128, divisor=1024;&n; *&n; *&t;The only reason for this is efficiency, it is possible&n; *&t;to change these parameters in compile time.&n; */
multiline_comment|/* RED section */
r_enum
(brace
DECL|enumerator|TCA_RED_UNSPEC
id|TCA_RED_UNSPEC
comma
DECL|enumerator|TCA_RED_PARMS
id|TCA_RED_PARMS
comma
DECL|enumerator|TCA_RED_STAB
id|TCA_RED_STAB
comma
DECL|enumerator|__TCA_RED_MAX
id|__TCA_RED_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_RED_MAX
mdefine_line|#define TCA_RED_MAX (__TCA_RED_MAX - 1)
DECL|struct|tc_red_qopt
r_struct
id|tc_red_qopt
(brace
DECL|member|limit
id|__u32
id|limit
suffix:semicolon
multiline_comment|/* HARD maximal queue length (bytes)&t;*/
DECL|member|qth_min
id|__u32
id|qth_min
suffix:semicolon
multiline_comment|/* Min average length threshold (bytes) */
DECL|member|qth_max
id|__u32
id|qth_max
suffix:semicolon
multiline_comment|/* Max average length threshold (bytes) */
DECL|member|Wlog
r_int
r_char
id|Wlog
suffix:semicolon
multiline_comment|/* log(W)&t;&t;*/
DECL|member|Plog
r_int
r_char
id|Plog
suffix:semicolon
multiline_comment|/* log(P_max/(qth_max-qth_min))&t;*/
DECL|member|Scell_log
r_int
r_char
id|Scell_log
suffix:semicolon
multiline_comment|/* cell size for idle damping */
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|macro|TC_RED_ECN
mdefine_line|#define TC_RED_ECN&t;1
)brace
suffix:semicolon
DECL|struct|tc_red_xstats
r_struct
id|tc_red_xstats
(brace
DECL|member|early
id|__u32
id|early
suffix:semicolon
multiline_comment|/* Early drops */
DECL|member|pdrop
id|__u32
id|pdrop
suffix:semicolon
multiline_comment|/* Drops due to queue limits */
DECL|member|other
id|__u32
id|other
suffix:semicolon
multiline_comment|/* Drops due to drop() calls */
DECL|member|marked
id|__u32
id|marked
suffix:semicolon
multiline_comment|/* Marked packets */
)brace
suffix:semicolon
multiline_comment|/* GRED section */
DECL|macro|MAX_DPs
mdefine_line|#define MAX_DPs 16
r_enum
(brace
DECL|enumerator|TCA_GRED_UNSPEC
id|TCA_GRED_UNSPEC
comma
DECL|enumerator|TCA_GRED_PARMS
id|TCA_GRED_PARMS
comma
DECL|enumerator|TCA_GRED_STAB
id|TCA_GRED_STAB
comma
DECL|enumerator|TCA_GRED_DPS
id|TCA_GRED_DPS
comma
DECL|enumerator|__TCA_GRED_MAX
id|__TCA_GRED_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_GRED_MAX
mdefine_line|#define TCA_GRED_MAX (__TCA_GRED_MAX - 1)
DECL|macro|TCA_SET_OFF
mdefine_line|#define TCA_SET_OFF TCA_GRED_PARMS
DECL|struct|tc_gred_qopt
r_struct
id|tc_gred_qopt
(brace
DECL|member|limit
id|__u32
id|limit
suffix:semicolon
multiline_comment|/* HARD maximal queue length (bytes)    &n;*/
DECL|member|qth_min
id|__u32
id|qth_min
suffix:semicolon
multiline_comment|/* Min average length threshold (bytes) &n;*/
DECL|member|qth_max
id|__u32
id|qth_max
suffix:semicolon
multiline_comment|/* Max average length threshold (bytes) &n;*/
DECL|member|DP
id|__u32
id|DP
suffix:semicolon
multiline_comment|/* upto 2^32 DPs */
DECL|member|backlog
id|__u32
id|backlog
suffix:semicolon
DECL|member|qave
id|__u32
id|qave
suffix:semicolon
DECL|member|forced
id|__u32
id|forced
suffix:semicolon
DECL|member|early
id|__u32
id|early
suffix:semicolon
DECL|member|other
id|__u32
id|other
suffix:semicolon
DECL|member|pdrop
id|__u32
id|pdrop
suffix:semicolon
DECL|member|Wlog
r_int
r_char
id|Wlog
suffix:semicolon
multiline_comment|/* log(W)               */
DECL|member|Plog
r_int
r_char
id|Plog
suffix:semicolon
multiline_comment|/* log(P_max/(qth_max-qth_min)) */
DECL|member|Scell_log
r_int
r_char
id|Scell_log
suffix:semicolon
multiline_comment|/* cell size for idle damping */
DECL|member|prio
id|__u8
id|prio
suffix:semicolon
multiline_comment|/* prio of this VQ */
DECL|member|packets
id|__u32
id|packets
suffix:semicolon
DECL|member|bytesin
id|__u32
id|bytesin
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* gred setup */
DECL|struct|tc_gred_sopt
r_struct
id|tc_gred_sopt
(brace
DECL|member|DPs
id|__u32
id|DPs
suffix:semicolon
DECL|member|def_DP
id|__u32
id|def_DP
suffix:semicolon
DECL|member|grio
id|__u8
id|grio
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* HTB section */
DECL|macro|TC_HTB_NUMPRIO
mdefine_line|#define TC_HTB_NUMPRIO&t;&t;8
DECL|macro|TC_HTB_MAXDEPTH
mdefine_line|#define TC_HTB_MAXDEPTH&t;&t;8
DECL|macro|TC_HTB_PROTOVER
mdefine_line|#define TC_HTB_PROTOVER&t;&t;3 /* the same as HTB and TC&squot;s major */
DECL|struct|tc_htb_opt
r_struct
id|tc_htb_opt
(brace
DECL|member|rate
r_struct
id|tc_ratespec
id|rate
suffix:semicolon
DECL|member|ceil
r_struct
id|tc_ratespec
id|ceil
suffix:semicolon
DECL|member|buffer
id|__u32
id|buffer
suffix:semicolon
DECL|member|cbuffer
id|__u32
id|cbuffer
suffix:semicolon
DECL|member|quantum
id|__u32
id|quantum
suffix:semicolon
DECL|member|level
id|__u32
id|level
suffix:semicolon
multiline_comment|/* out only */
DECL|member|prio
id|__u32
id|prio
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_htb_glob
r_struct
id|tc_htb_glob
(brace
DECL|member|version
id|__u32
id|version
suffix:semicolon
multiline_comment|/* to match HTB/TC */
DECL|member|rate2quantum
id|__u32
id|rate2quantum
suffix:semicolon
multiline_comment|/* bps-&gt;quantum divisor */
DECL|member|defcls
id|__u32
id|defcls
suffix:semicolon
multiline_comment|/* default class number */
DECL|member|debug
id|__u32
id|debug
suffix:semicolon
multiline_comment|/* debug flags */
multiline_comment|/* stats */
DECL|member|direct_pkts
id|__u32
id|direct_pkts
suffix:semicolon
multiline_comment|/* count of non shapped packets */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCA_HTB_UNSPEC
id|TCA_HTB_UNSPEC
comma
DECL|enumerator|TCA_HTB_PARMS
id|TCA_HTB_PARMS
comma
DECL|enumerator|TCA_HTB_INIT
id|TCA_HTB_INIT
comma
DECL|enumerator|TCA_HTB_CTAB
id|TCA_HTB_CTAB
comma
DECL|enumerator|TCA_HTB_RTAB
id|TCA_HTB_RTAB
comma
DECL|enumerator|__TCA_HTB_MAX
id|__TCA_HTB_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_HTB_MAX
mdefine_line|#define TCA_HTB_MAX (__TCA_HTB_MAX - 1)
DECL|struct|tc_htb_xstats
r_struct
id|tc_htb_xstats
(brace
DECL|member|lends
id|__u32
id|lends
suffix:semicolon
DECL|member|borrows
id|__u32
id|borrows
suffix:semicolon
DECL|member|giants
id|__u32
id|giants
suffix:semicolon
multiline_comment|/* too big packets (rate will not be accurate) */
DECL|member|tokens
id|__u32
id|tokens
suffix:semicolon
DECL|member|ctokens
id|__u32
id|ctokens
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* HFSC section */
DECL|struct|tc_hfsc_qopt
r_struct
id|tc_hfsc_qopt
(brace
DECL|member|defcls
id|__u16
id|defcls
suffix:semicolon
multiline_comment|/* default class */
)brace
suffix:semicolon
DECL|struct|tc_service_curve
r_struct
id|tc_service_curve
(brace
DECL|member|m1
id|__u32
id|m1
suffix:semicolon
multiline_comment|/* slope of the first segment in bps */
DECL|member|d
id|__u32
id|d
suffix:semicolon
multiline_comment|/* x-projection of the first segment in us */
DECL|member|m2
id|__u32
id|m2
suffix:semicolon
multiline_comment|/* slope of the second segment in bps */
)brace
suffix:semicolon
DECL|struct|tc_hfsc_stats
r_struct
id|tc_hfsc_stats
(brace
DECL|member|work
id|__u64
id|work
suffix:semicolon
multiline_comment|/* total work done */
DECL|member|rtwork
id|__u64
id|rtwork
suffix:semicolon
multiline_comment|/* work done by real-time criteria */
DECL|member|period
id|__u32
id|period
suffix:semicolon
multiline_comment|/* current period */
DECL|member|level
id|__u32
id|level
suffix:semicolon
multiline_comment|/* class level in hierarchy */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCA_HFSC_UNSPEC
id|TCA_HFSC_UNSPEC
comma
DECL|enumerator|TCA_HFSC_RSC
id|TCA_HFSC_RSC
comma
DECL|enumerator|TCA_HFSC_FSC
id|TCA_HFSC_FSC
comma
DECL|enumerator|TCA_HFSC_USC
id|TCA_HFSC_USC
comma
DECL|enumerator|__TCA_HFSC_MAX
id|__TCA_HFSC_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_HFSC_MAX
mdefine_line|#define TCA_HFSC_MAX (__TCA_HFSC_MAX - 1)
multiline_comment|/* CBQ section */
DECL|macro|TC_CBQ_MAXPRIO
mdefine_line|#define TC_CBQ_MAXPRIO&t;&t;8
DECL|macro|TC_CBQ_MAXLEVEL
mdefine_line|#define TC_CBQ_MAXLEVEL&t;&t;8
DECL|macro|TC_CBQ_DEF_EWMA
mdefine_line|#define TC_CBQ_DEF_EWMA&t;&t;5
DECL|struct|tc_cbq_lssopt
r_struct
id|tc_cbq_lssopt
(brace
DECL|member|change
r_int
r_char
id|change
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|macro|TCF_CBQ_LSS_BOUNDED
mdefine_line|#define TCF_CBQ_LSS_BOUNDED&t;1
DECL|macro|TCF_CBQ_LSS_ISOLATED
mdefine_line|#define TCF_CBQ_LSS_ISOLATED&t;2
DECL|member|ewma_log
r_int
r_char
id|ewma_log
suffix:semicolon
DECL|member|level
r_int
r_char
id|level
suffix:semicolon
DECL|macro|TCF_CBQ_LSS_FLAGS
mdefine_line|#define TCF_CBQ_LSS_FLAGS&t;1
DECL|macro|TCF_CBQ_LSS_EWMA
mdefine_line|#define TCF_CBQ_LSS_EWMA&t;2
DECL|macro|TCF_CBQ_LSS_MAXIDLE
mdefine_line|#define TCF_CBQ_LSS_MAXIDLE&t;4
DECL|macro|TCF_CBQ_LSS_MINIDLE
mdefine_line|#define TCF_CBQ_LSS_MINIDLE&t;8
DECL|macro|TCF_CBQ_LSS_OFFTIME
mdefine_line|#define TCF_CBQ_LSS_OFFTIME&t;0x10
DECL|macro|TCF_CBQ_LSS_AVPKT
mdefine_line|#define TCF_CBQ_LSS_AVPKT&t;0x20
DECL|member|maxidle
id|__u32
id|maxidle
suffix:semicolon
DECL|member|minidle
id|__u32
id|minidle
suffix:semicolon
DECL|member|offtime
id|__u32
id|offtime
suffix:semicolon
DECL|member|avpkt
id|__u32
id|avpkt
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_cbq_wrropt
r_struct
id|tc_cbq_wrropt
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|priority
r_int
r_char
id|priority
suffix:semicolon
DECL|member|cpriority
r_int
r_char
id|cpriority
suffix:semicolon
DECL|member|__reserved
r_int
r_char
id|__reserved
suffix:semicolon
DECL|member|allot
id|__u32
id|allot
suffix:semicolon
DECL|member|weight
id|__u32
id|weight
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_cbq_ovl
r_struct
id|tc_cbq_ovl
(brace
DECL|member|strategy
r_int
r_char
id|strategy
suffix:semicolon
DECL|macro|TC_CBQ_OVL_CLASSIC
mdefine_line|#define&t;TC_CBQ_OVL_CLASSIC&t;0
DECL|macro|TC_CBQ_OVL_DELAY
mdefine_line|#define&t;TC_CBQ_OVL_DELAY&t;1
DECL|macro|TC_CBQ_OVL_LOWPRIO
mdefine_line|#define&t;TC_CBQ_OVL_LOWPRIO&t;2
DECL|macro|TC_CBQ_OVL_DROP
mdefine_line|#define&t;TC_CBQ_OVL_DROP&t;&t;3
DECL|macro|TC_CBQ_OVL_RCLASSIC
mdefine_line|#define&t;TC_CBQ_OVL_RCLASSIC&t;4
DECL|member|priority2
r_int
r_char
id|priority2
suffix:semicolon
DECL|member|penalty
id|__u32
id|penalty
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_cbq_police
r_struct
id|tc_cbq_police
(brace
DECL|member|police
r_int
r_char
id|police
suffix:semicolon
DECL|member|__res1
r_int
r_char
id|__res1
suffix:semicolon
DECL|member|__res2
r_int
r_int
id|__res2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_cbq_fopt
r_struct
id|tc_cbq_fopt
(brace
DECL|member|split
id|__u32
id|split
suffix:semicolon
DECL|member|defmap
id|__u32
id|defmap
suffix:semicolon
DECL|member|defchange
id|__u32
id|defchange
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_cbq_xstats
r_struct
id|tc_cbq_xstats
(brace
DECL|member|borrows
id|__u32
id|borrows
suffix:semicolon
DECL|member|overactions
id|__u32
id|overactions
suffix:semicolon
DECL|member|avgidle
id|__s32
id|avgidle
suffix:semicolon
DECL|member|undertime
id|__s32
id|undertime
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|TCA_CBQ_UNSPEC
id|TCA_CBQ_UNSPEC
comma
DECL|enumerator|TCA_CBQ_LSSOPT
id|TCA_CBQ_LSSOPT
comma
DECL|enumerator|TCA_CBQ_WRROPT
id|TCA_CBQ_WRROPT
comma
DECL|enumerator|TCA_CBQ_FOPT
id|TCA_CBQ_FOPT
comma
DECL|enumerator|TCA_CBQ_OVL_STRATEGY
id|TCA_CBQ_OVL_STRATEGY
comma
DECL|enumerator|TCA_CBQ_RATE
id|TCA_CBQ_RATE
comma
DECL|enumerator|TCA_CBQ_RTAB
id|TCA_CBQ_RTAB
comma
DECL|enumerator|TCA_CBQ_POLICE
id|TCA_CBQ_POLICE
comma
DECL|enumerator|__TCA_CBQ_MAX
id|__TCA_CBQ_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_CBQ_MAX
mdefine_line|#define TCA_CBQ_MAX&t;(__TCA_CBQ_MAX - 1)
multiline_comment|/* dsmark section */
r_enum
(brace
DECL|enumerator|TCA_DSMARK_UNSPEC
id|TCA_DSMARK_UNSPEC
comma
DECL|enumerator|TCA_DSMARK_INDICES
id|TCA_DSMARK_INDICES
comma
DECL|enumerator|TCA_DSMARK_DEFAULT_INDEX
id|TCA_DSMARK_DEFAULT_INDEX
comma
DECL|enumerator|TCA_DSMARK_SET_TC_INDEX
id|TCA_DSMARK_SET_TC_INDEX
comma
DECL|enumerator|TCA_DSMARK_MASK
id|TCA_DSMARK_MASK
comma
DECL|enumerator|TCA_DSMARK_VALUE
id|TCA_DSMARK_VALUE
comma
DECL|enumerator|__TCA_DSMARK_MAX
id|__TCA_DSMARK_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_DSMARK_MAX
mdefine_line|#define TCA_DSMARK_MAX (__TCA_DSMARK_MAX - 1)
multiline_comment|/* ATM  section */
r_enum
(brace
DECL|enumerator|TCA_ATM_UNSPEC
id|TCA_ATM_UNSPEC
comma
DECL|enumerator|TCA_ATM_FD
id|TCA_ATM_FD
comma
multiline_comment|/* file/socket descriptor */
DECL|enumerator|TCA_ATM_PTR
id|TCA_ATM_PTR
comma
multiline_comment|/* pointer to descriptor - later */
DECL|enumerator|TCA_ATM_HDR
id|TCA_ATM_HDR
comma
multiline_comment|/* LL header */
DECL|enumerator|TCA_ATM_EXCESS
id|TCA_ATM_EXCESS
comma
multiline_comment|/* excess traffic class (0 for CLP)  */
DECL|enumerator|TCA_ATM_ADDR
id|TCA_ATM_ADDR
comma
multiline_comment|/* PVC address (for output only) */
DECL|enumerator|TCA_ATM_STATE
id|TCA_ATM_STATE
comma
multiline_comment|/* VC state (ATM_VS_*; for output only) */
DECL|enumerator|__TCA_ATM_MAX
id|__TCA_ATM_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_ATM_MAX
mdefine_line|#define TCA_ATM_MAX&t;(__TCA_ATM_MAX - 1)
multiline_comment|/* Network emulator */
r_enum
(brace
DECL|enumerator|TCA_NETEM_UNSPEC
id|TCA_NETEM_UNSPEC
comma
DECL|enumerator|TCA_NETEM_CORR
id|TCA_NETEM_CORR
comma
DECL|enumerator|TCA_NETEM_DELAY_DIST
id|TCA_NETEM_DELAY_DIST
comma
DECL|enumerator|__TCA_NETEM_MAX
id|__TCA_NETEM_MAX
comma
)brace
suffix:semicolon
DECL|macro|TCA_NETEM_MAX
mdefine_line|#define TCA_NETEM_MAX (__TCA_NETEM_MAX - 1)
DECL|struct|tc_netem_qopt
r_struct
id|tc_netem_qopt
(brace
DECL|member|latency
id|__u32
id|latency
suffix:semicolon
multiline_comment|/* added delay (us) */
DECL|member|limit
id|__u32
id|limit
suffix:semicolon
multiline_comment|/* fifo limit (packets) */
DECL|member|loss
id|__u32
id|loss
suffix:semicolon
multiline_comment|/* random packet loss (0=none ~0=100%) */
DECL|member|gap
id|__u32
id|gap
suffix:semicolon
multiline_comment|/* re-ordering gap (0 for delay all) */
DECL|member|duplicate
id|__u32
id|duplicate
suffix:semicolon
multiline_comment|/* random packet dup  (0=none ~0=100%) */
DECL|member|jitter
id|__u32
id|jitter
suffix:semicolon
multiline_comment|/* random jitter in latency (us) */
)brace
suffix:semicolon
DECL|struct|tc_netem_corr
r_struct
id|tc_netem_corr
(brace
DECL|member|delay_corr
id|__u32
id|delay_corr
suffix:semicolon
multiline_comment|/* delay correlation */
DECL|member|loss_corr
id|__u32
id|loss_corr
suffix:semicolon
multiline_comment|/* packet loss correlation */
DECL|member|dup_corr
id|__u32
id|dup_corr
suffix:semicolon
multiline_comment|/* duplicate correlation  */
)brace
suffix:semicolon
DECL|macro|NETEM_DIST_SCALE
mdefine_line|#define NETEM_DIST_SCALE&t;8192
macro_line|#endif
eof
