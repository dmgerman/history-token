macro_line|#ifndef __LINUX_PKT_CLS_H
DECL|macro|__LINUX_PKT_CLS_H
mdefine_line|#define __LINUX_PKT_CLS_H
macro_line|#include &lt;linux/pkt_sched.h&gt;
multiline_comment|/* I think i could have done better macros ; for now this is stolen from&n; * some arch/mips code - jhs&n;*/
DECL|macro|_TC_MAKE32
mdefine_line|#define _TC_MAKE32(x) ((x))
DECL|macro|_TC_MAKEMASK1
mdefine_line|#define _TC_MAKEMASK1(n) (_TC_MAKE32(1) &lt;&lt; _TC_MAKE32(n))
DECL|macro|_TC_MAKEMASK
mdefine_line|#define _TC_MAKEMASK(v,n) (_TC_MAKE32((_TC_MAKE32(1)&lt;&lt;(v))-1) &lt;&lt; _TC_MAKE32(n))
DECL|macro|_TC_MAKEVALUE
mdefine_line|#define _TC_MAKEVALUE(v,n) (_TC_MAKE32(v) &lt;&lt; _TC_MAKE32(n))
DECL|macro|_TC_GETVALUE
mdefine_line|#define _TC_GETVALUE(v,n,m) ((_TC_MAKE32(v) &amp; _TC_MAKE32(m)) &gt;&gt; _TC_MAKE32(n))
multiline_comment|/* verdict bit breakdown &n; *&n;bit 0: when set -&gt; this packet has been munged already&n;&n;bit 1: when set -&gt; It is ok to munge this packet&n;&n;bit 2,3,4,5: Reclassify counter - sort of reverse TTL - if exceeded&n;assume loop&n;&n;bit 6,7: Where this packet was last seen &n;0: Above the transmit example at the socket level&n;1: on the Ingress&n;2: on the Egress&n;&n;bit 8: when set --&gt; Request not to classify on ingress. &n;&n;bits 9,10,11: redirect counter -  redirect TTL. Loop avoidance&n;&n; *&n; * */
DECL|macro|TC_MUNGED
mdefine_line|#define TC_MUNGED          _TC_MAKEMASK1(0)
DECL|macro|SET_TC_MUNGED
mdefine_line|#define SET_TC_MUNGED(v)   ( TC_MUNGED | (v &amp; ~TC_MUNGED))
DECL|macro|CLR_TC_MUNGED
mdefine_line|#define CLR_TC_MUNGED(v)   ( v &amp; ~TC_MUNGED)
DECL|macro|TC_OK2MUNGE
mdefine_line|#define TC_OK2MUNGE        _TC_MAKEMASK1(1)
DECL|macro|SET_TC_OK2MUNGE
mdefine_line|#define SET_TC_OK2MUNGE(v)   ( TC_OK2MUNGE | (v &amp; ~TC_OK2MUNGE))
DECL|macro|CLR_TC_OK2MUNGE
mdefine_line|#define CLR_TC_OK2MUNGE(v)   ( v &amp; ~TC_OK2MUNGE)
DECL|macro|S_TC_VERD
mdefine_line|#define S_TC_VERD          _TC_MAKE32(2)
DECL|macro|M_TC_VERD
mdefine_line|#define M_TC_VERD          _TC_MAKEMASK(4,S_TC_VERD)
DECL|macro|G_TC_VERD
mdefine_line|#define G_TC_VERD(x)       _TC_GETVALUE(x,S_TC_VERD,M_TC_VERD)
DECL|macro|V_TC_VERD
mdefine_line|#define V_TC_VERD(x)       _TC_MAKEVALUE(x,S_TC_VERD)
DECL|macro|SET_TC_VERD
mdefine_line|#define SET_TC_VERD(v,n)   ((V_TC_VERD(n)) | (v &amp; ~M_TC_VERD))
DECL|macro|S_TC_FROM
mdefine_line|#define S_TC_FROM          _TC_MAKE32(6)
DECL|macro|M_TC_FROM
mdefine_line|#define M_TC_FROM          _TC_MAKEMASK(2,S_TC_FROM)
DECL|macro|G_TC_FROM
mdefine_line|#define G_TC_FROM(x)       _TC_GETVALUE(x,S_TC_FROM,M_TC_FROM)
DECL|macro|V_TC_FROM
mdefine_line|#define V_TC_FROM(x)       _TC_MAKEVALUE(x,S_TC_FROM)
DECL|macro|SET_TC_FROM
mdefine_line|#define SET_TC_FROM(v,n)   ((V_TC_FROM(n)) | (v &amp; ~M_TC_FROM))
DECL|macro|AT_STACK
mdefine_line|#define AT_STACK&t;0x0
DECL|macro|AT_INGRESS
mdefine_line|#define AT_INGRESS&t;0x1
DECL|macro|AT_EGRESS
mdefine_line|#define AT_EGRESS&t;0x2
DECL|macro|TC_NCLS
mdefine_line|#define TC_NCLS          _TC_MAKEMASK1(8)
DECL|macro|SET_TC_NCLS
mdefine_line|#define SET_TC_NCLS(v)   ( TC_NCLS | (v &amp; ~TC_NCLS))
DECL|macro|CLR_TC_NCLS
mdefine_line|#define CLR_TC_NCLS(v)   ( v &amp; ~TC_NCLS)
DECL|macro|S_TC_RTTL
mdefine_line|#define S_TC_RTTL          _TC_MAKE32(9)
DECL|macro|M_TC_RTTL
mdefine_line|#define M_TC_RTTL          _TC_MAKEMASK(3,S_TC_RTTL)
DECL|macro|G_TC_RTTL
mdefine_line|#define G_TC_RTTL(x)       _TC_GETVALUE(x,S_TC_RTTL,M_TC_RTTL)
DECL|macro|V_TC_RTTL
mdefine_line|#define V_TC_RTTL(x)       _TC_MAKEVALUE(x,S_TC_RTTL)
DECL|macro|SET_TC_RTTL
mdefine_line|#define SET_TC_RTTL(v,n)   ((V_TC_RTTL(n)) | (v &amp; ~M_TC_RTTL))
DECL|macro|S_TC_AT
mdefine_line|#define S_TC_AT          _TC_MAKE32(12)
DECL|macro|M_TC_AT
mdefine_line|#define M_TC_AT          _TC_MAKEMASK(2,S_TC_AT)
DECL|macro|G_TC_AT
mdefine_line|#define G_TC_AT(x)       _TC_GETVALUE(x,S_TC_AT,M_TC_AT)
DECL|macro|V_TC_AT
mdefine_line|#define V_TC_AT(x)       _TC_MAKEVALUE(x,S_TC_AT)
DECL|macro|SET_TC_AT
mdefine_line|#define SET_TC_AT(v,n)   ((V_TC_AT(n)) | (v &amp; ~M_TC_AT))
multiline_comment|/* Action attributes */
r_enum
(brace
DECL|enumerator|TCA_ACT_UNSPEC
id|TCA_ACT_UNSPEC
comma
DECL|enumerator|TCA_ACT_KIND
id|TCA_ACT_KIND
comma
DECL|enumerator|TCA_ACT_OPTIONS
id|TCA_ACT_OPTIONS
comma
DECL|enumerator|TCA_ACT_INDEX
id|TCA_ACT_INDEX
comma
DECL|enumerator|__TCA_ACT_MAX
id|__TCA_ACT_MAX
)brace
suffix:semicolon
DECL|macro|TCA_ACT_MAX
mdefine_line|#define TCA_ACT_MAX __TCA_ACT_MAX
DECL|macro|TCA_OLD_COMPAT
mdefine_line|#define TCA_OLD_COMPAT (TCA_ACT_MAX+1)
DECL|macro|TCA_ACT_MAX_PRIO
mdefine_line|#define TCA_ACT_MAX_PRIO 32
DECL|macro|TCA_ACT_BIND
mdefine_line|#define TCA_ACT_BIND&t;1
DECL|macro|TCA_ACT_NOBIND
mdefine_line|#define TCA_ACT_NOBIND&t;0
DECL|macro|TCA_ACT_UNBIND
mdefine_line|#define TCA_ACT_UNBIND&t;1
DECL|macro|TCA_ACT_NOUNBIND
mdefine_line|#define TCA_ACT_NOUNBIND&t;0
DECL|macro|TCA_ACT_REPLACE
mdefine_line|#define TCA_ACT_REPLACE&t;&t;1
DECL|macro|TCA_ACT_NOREPLACE
mdefine_line|#define TCA_ACT_NOREPLACE&t;0
DECL|macro|MAX_REC_LOOP
mdefine_line|#define MAX_REC_LOOP 4
DECL|macro|MAX_RED_LOOP
mdefine_line|#define MAX_RED_LOOP 4
DECL|macro|TC_ACT_UNSPEC
mdefine_line|#define TC_ACT_UNSPEC&t;(-1)
DECL|macro|TC_ACT_OK
mdefine_line|#define TC_ACT_OK&t;&t;0
DECL|macro|TC_ACT_RECLASSIFY
mdefine_line|#define TC_ACT_RECLASSIFY&t;1
DECL|macro|TC_ACT_SHOT
mdefine_line|#define TC_ACT_SHOT&t;&t;2
DECL|macro|TC_ACT_PIPE
mdefine_line|#define TC_ACT_PIPE&t;&t;3
DECL|macro|TC_ACT_STOLEN
mdefine_line|#define TC_ACT_STOLEN&t;&t;4
DECL|macro|TC_ACT_QUEUED
mdefine_line|#define TC_ACT_QUEUED&t;&t;5
DECL|macro|TC_ACT_REPEAT
mdefine_line|#define TC_ACT_REPEAT&t;&t;6
DECL|macro|TC_ACT_JUMP
mdefine_line|#define TC_ACT_JUMP&t;&t;0x10000000
multiline_comment|/* Action type identifiers*/
r_enum
(brace
DECL|enumerator|TCA_ID_UNSPEC
id|TCA_ID_UNSPEC
op_assign
l_int|0
comma
DECL|enumerator|TCA_ID_POLICE
id|TCA_ID_POLICE
op_assign
l_int|1
comma
multiline_comment|/* other actions go here */
DECL|enumerator|__TCA_ID_MAX
id|__TCA_ID_MAX
op_assign
l_int|255
)brace
suffix:semicolon
DECL|macro|TCA_ID_MAX
mdefine_line|#define TCA_ID_MAX __TCA_ID_MAX
DECL|struct|tc_police
r_struct
id|tc_police
(brace
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|action
r_int
id|action
suffix:semicolon
DECL|macro|TC_POLICE_UNSPEC
mdefine_line|#define TC_POLICE_UNSPEC&t;TC_ACT_UNSPEC
DECL|macro|TC_POLICE_OK
mdefine_line|#define TC_POLICE_OK&t;&t;TC_ACT_OK
DECL|macro|TC_POLICE_RECLASSIFY
mdefine_line|#define TC_POLICE_RECLASSIFY&t;TC_ACT_RECLASSIFY
DECL|macro|TC_POLICE_SHOT
mdefine_line|#define TC_POLICE_SHOT&t;&t;TC_ACT_SHOT
DECL|macro|TC_POLICE_PIPE
mdefine_line|#define TC_POLICE_PIPE&t;&t;TC_ACT_PIPE
DECL|member|limit
id|__u32
id|limit
suffix:semicolon
DECL|member|burst
id|__u32
id|burst
suffix:semicolon
DECL|member|mtu
id|__u32
id|mtu
suffix:semicolon
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
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
DECL|member|bindcnt
r_int
id|bindcnt
suffix:semicolon
DECL|member|capab
id|__u32
id|capab
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcf_t
r_struct
id|tcf_t
(brace
DECL|member|install
id|__u64
id|install
suffix:semicolon
DECL|member|lastuse
id|__u64
id|lastuse
suffix:semicolon
DECL|member|expires
id|__u64
id|expires
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_cnt
r_struct
id|tc_cnt
(brace
DECL|member|refcnt
r_int
id|refcnt
suffix:semicolon
DECL|member|bindcnt
r_int
id|bindcnt
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|tc_gen
mdefine_line|#define tc_gen &bslash;&n;&t;__u32                 index; &bslash;&n;&t;__u32                 capab; &bslash;&n;&t;int                   action; &bslash;&n;&t;int                   refcnt; &bslash;&n;&t;int                   bindcnt
r_enum
(brace
DECL|enumerator|TCA_POLICE_UNSPEC
id|TCA_POLICE_UNSPEC
comma
DECL|enumerator|TCA_POLICE_TBF
id|TCA_POLICE_TBF
comma
DECL|enumerator|TCA_POLICE_RATE
id|TCA_POLICE_RATE
comma
DECL|enumerator|TCA_POLICE_PEAKRATE
id|TCA_POLICE_PEAKRATE
comma
DECL|enumerator|TCA_POLICE_AVRATE
id|TCA_POLICE_AVRATE
comma
DECL|enumerator|TCA_POLICE_RESULT
id|TCA_POLICE_RESULT
comma
DECL|enumerator|__TCA_POLICE_MAX
id|__TCA_POLICE_MAX
DECL|macro|TCA_POLICE_RESULT
mdefine_line|#define TCA_POLICE_RESULT TCA_POLICE_RESULT
)brace
suffix:semicolon
DECL|macro|TCA_POLICE_MAX
mdefine_line|#define TCA_POLICE_MAX (__TCA_POLICE_MAX - 1)
multiline_comment|/* U32 filters */
DECL|macro|TC_U32_HTID
mdefine_line|#define TC_U32_HTID(h) ((h)&amp;0xFFF00000)
DECL|macro|TC_U32_USERHTID
mdefine_line|#define TC_U32_USERHTID(h) (TC_U32_HTID(h)&gt;&gt;20)
DECL|macro|TC_U32_HASH
mdefine_line|#define TC_U32_HASH(h) (((h)&gt;&gt;12)&amp;0xFF)
DECL|macro|TC_U32_NODE
mdefine_line|#define TC_U32_NODE(h) ((h)&amp;0xFFF)
DECL|macro|TC_U32_KEY
mdefine_line|#define TC_U32_KEY(h) ((h)&amp;0xFFFFF)
DECL|macro|TC_U32_UNSPEC
mdefine_line|#define TC_U32_UNSPEC&t;0
DECL|macro|TC_U32_ROOT
mdefine_line|#define TC_U32_ROOT&t;(0xFFF00000)
r_enum
(brace
DECL|enumerator|TCA_U32_UNSPEC
id|TCA_U32_UNSPEC
comma
DECL|enumerator|TCA_U32_CLASSID
id|TCA_U32_CLASSID
comma
DECL|enumerator|TCA_U32_HASH
id|TCA_U32_HASH
comma
DECL|enumerator|TCA_U32_LINK
id|TCA_U32_LINK
comma
DECL|enumerator|TCA_U32_DIVISOR
id|TCA_U32_DIVISOR
comma
DECL|enumerator|TCA_U32_SEL
id|TCA_U32_SEL
comma
DECL|enumerator|TCA_U32_POLICE
id|TCA_U32_POLICE
comma
DECL|enumerator|TCA_U32_ACT
id|TCA_U32_ACT
comma
DECL|enumerator|TCA_U32_INDEV
id|TCA_U32_INDEV
comma
DECL|enumerator|TCA_U32_PCNT
id|TCA_U32_PCNT
comma
DECL|enumerator|__TCA_U32_MAX
id|__TCA_U32_MAX
)brace
suffix:semicolon
DECL|macro|TCA_U32_MAX
mdefine_line|#define TCA_U32_MAX (__TCA_U32_MAX - 1)
DECL|struct|tc_u32_key
r_struct
id|tc_u32_key
(brace
DECL|member|mask
id|__u32
id|mask
suffix:semicolon
DECL|member|val
id|__u32
id|val
suffix:semicolon
DECL|member|off
r_int
id|off
suffix:semicolon
DECL|member|offmask
r_int
id|offmask
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_u32_sel
r_struct
id|tc_u32_sel
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|offshift
r_int
r_char
id|offshift
suffix:semicolon
DECL|member|nkeys
r_int
r_char
id|nkeys
suffix:semicolon
DECL|member|offmask
id|__u16
id|offmask
suffix:semicolon
DECL|member|off
id|__u16
id|off
suffix:semicolon
DECL|member|offoff
r_int
id|offoff
suffix:semicolon
DECL|member|hoff
r_int
id|hoff
suffix:semicolon
DECL|member|hmask
id|__u32
id|hmask
suffix:semicolon
DECL|member|keys
r_struct
id|tc_u32_key
id|keys
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_CLS_U32_PERF
DECL|struct|tc_u32_pcnt
r_struct
id|tc_u32_pcnt
(brace
DECL|member|rcnt
id|__u64
id|rcnt
suffix:semicolon
DECL|member|rhit
id|__u64
id|rhit
suffix:semicolon
DECL|member|kcnts
id|__u64
id|kcnts
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* Flags */
DECL|macro|TC_U32_TERMINAL
mdefine_line|#define TC_U32_TERMINAL&t;&t;1
DECL|macro|TC_U32_OFFSET
mdefine_line|#define TC_U32_OFFSET&t;&t;2
DECL|macro|TC_U32_VAROFFSET
mdefine_line|#define TC_U32_VAROFFSET&t;4
DECL|macro|TC_U32_EAT
mdefine_line|#define TC_U32_EAT&t;&t;8
DECL|macro|TC_U32_MAXDEPTH
mdefine_line|#define TC_U32_MAXDEPTH 8
multiline_comment|/* RSVP filter */
r_enum
(brace
DECL|enumerator|TCA_RSVP_UNSPEC
id|TCA_RSVP_UNSPEC
comma
DECL|enumerator|TCA_RSVP_CLASSID
id|TCA_RSVP_CLASSID
comma
DECL|enumerator|TCA_RSVP_DST
id|TCA_RSVP_DST
comma
DECL|enumerator|TCA_RSVP_SRC
id|TCA_RSVP_SRC
comma
DECL|enumerator|TCA_RSVP_PINFO
id|TCA_RSVP_PINFO
comma
DECL|enumerator|TCA_RSVP_POLICE
id|TCA_RSVP_POLICE
comma
DECL|enumerator|__TCA_RSVP_MAX
id|__TCA_RSVP_MAX
)brace
suffix:semicolon
DECL|macro|TCA_RSVP_MAX
mdefine_line|#define TCA_RSVP_MAX (__TCA_RSVP_MAX - 1 )
DECL|struct|tc_rsvp_gpi
r_struct
id|tc_rsvp_gpi
(brace
DECL|member|key
id|__u32
id|key
suffix:semicolon
DECL|member|mask
id|__u32
id|mask
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tc_rsvp_pinfo
r_struct
id|tc_rsvp_pinfo
(brace
DECL|member|dpi
r_struct
id|tc_rsvp_gpi
id|dpi
suffix:semicolon
DECL|member|spi
r_struct
id|tc_rsvp_gpi
id|spi
suffix:semicolon
DECL|member|protocol
id|__u8
id|protocol
suffix:semicolon
DECL|member|tunnelid
id|__u8
id|tunnelid
suffix:semicolon
DECL|member|tunnelhdr
id|__u8
id|tunnelhdr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ROUTE filter */
r_enum
(brace
DECL|enumerator|TCA_ROUTE4_UNSPEC
id|TCA_ROUTE4_UNSPEC
comma
DECL|enumerator|TCA_ROUTE4_CLASSID
id|TCA_ROUTE4_CLASSID
comma
DECL|enumerator|TCA_ROUTE4_TO
id|TCA_ROUTE4_TO
comma
DECL|enumerator|TCA_ROUTE4_FROM
id|TCA_ROUTE4_FROM
comma
DECL|enumerator|TCA_ROUTE4_IIF
id|TCA_ROUTE4_IIF
comma
DECL|enumerator|TCA_ROUTE4_POLICE
id|TCA_ROUTE4_POLICE
comma
DECL|enumerator|__TCA_ROUTE4_MAX
id|__TCA_ROUTE4_MAX
)brace
suffix:semicolon
DECL|macro|TCA_ROUTE4_MAX
mdefine_line|#define TCA_ROUTE4_MAX (__TCA_ROUTE4_MAX - 1)
multiline_comment|/* FW filter */
r_enum
(brace
DECL|enumerator|TCA_FW_UNSPEC
id|TCA_FW_UNSPEC
comma
DECL|enumerator|TCA_FW_CLASSID
id|TCA_FW_CLASSID
comma
DECL|enumerator|TCA_FW_POLICE
id|TCA_FW_POLICE
comma
DECL|enumerator|TCA_FW_INDEV
id|TCA_FW_INDEV
comma
multiline_comment|/*  used by CONFIG_NET_CLS_IND */
DECL|enumerator|TCA_FW_ACT
id|TCA_FW_ACT
comma
multiline_comment|/* used by CONFIG_NET_CLS_ACT */
DECL|enumerator|__TCA_FW_MAX
id|__TCA_FW_MAX
)brace
suffix:semicolon
DECL|macro|TCA_FW_MAX
mdefine_line|#define TCA_FW_MAX (__TCA_FW_MAX - 1)
multiline_comment|/* TC index filter */
r_enum
(brace
DECL|enumerator|TCA_TCINDEX_UNSPEC
id|TCA_TCINDEX_UNSPEC
comma
DECL|enumerator|TCA_TCINDEX_HASH
id|TCA_TCINDEX_HASH
comma
DECL|enumerator|TCA_TCINDEX_MASK
id|TCA_TCINDEX_MASK
comma
DECL|enumerator|TCA_TCINDEX_SHIFT
id|TCA_TCINDEX_SHIFT
comma
DECL|enumerator|TCA_TCINDEX_FALL_THROUGH
id|TCA_TCINDEX_FALL_THROUGH
comma
DECL|enumerator|TCA_TCINDEX_CLASSID
id|TCA_TCINDEX_CLASSID
comma
DECL|enumerator|TCA_TCINDEX_POLICE
id|TCA_TCINDEX_POLICE
comma
DECL|enumerator|__TCA_TCINDEX_MAX
id|__TCA_TCINDEX_MAX
)brace
suffix:semicolon
DECL|macro|TCA_TCINDEX_MAX
mdefine_line|#define TCA_TCINDEX_MAX     (__TCA_TCINDEX_MAX - 1)
macro_line|#endif
eof
