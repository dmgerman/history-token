multiline_comment|/*&n; * This software may be used and distributed according to the terms&n; * of the GNU General Public License, incorporated herein by reference.&n; *&n; */
macro_line|#ifndef _LINUX_ISDN_PPP_H
DECL|macro|_LINUX_ISDN_PPP_H
mdefine_line|#define _LINUX_ISDN_PPP_H
DECL|macro|CALLTYPE_INCOMING
mdefine_line|#define CALLTYPE_INCOMING 0x1
DECL|macro|CALLTYPE_OUTGOING
mdefine_line|#define CALLTYPE_OUTGOING 0x2
DECL|macro|CALLTYPE_CALLBACK
mdefine_line|#define CALLTYPE_CALLBACK 0x4
DECL|macro|IPPP_VERSION
mdefine_line|#define IPPP_VERSION    &quot;2.2.0&quot;
DECL|struct|pppcallinfo
r_struct
id|pppcallinfo
(brace
DECL|member|calltype
r_int
id|calltype
suffix:semicolon
DECL|member|local_num
r_int
r_char
id|local_num
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|remote_num
r_int
r_char
id|remote_num
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|charge_units
r_int
id|charge_units
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PPPIOCGCALLINFO
mdefine_line|#define PPPIOCGCALLINFO _IOWR(&squot;t&squot;,128,struct pppcallinfo)
DECL|macro|PPPIOCBUNDLE
mdefine_line|#define PPPIOCBUNDLE   _IOW(&squot;t&squot;,129,int)
DECL|macro|PPPIOCGMPFLAGS
mdefine_line|#define PPPIOCGMPFLAGS _IOR(&squot;t&squot;,130,int)
DECL|macro|PPPIOCSMPFLAGS
mdefine_line|#define PPPIOCSMPFLAGS _IOW(&squot;t&squot;,131,int)
DECL|macro|PPPIOCSMPMTU
mdefine_line|#define PPPIOCSMPMTU   _IOW(&squot;t&squot;,132,int)
DECL|macro|PPPIOCSMPMRU
mdefine_line|#define PPPIOCSMPMRU   _IOW(&squot;t&squot;,133,int)
DECL|macro|PPPIOCGCOMPRESSORS
mdefine_line|#define PPPIOCGCOMPRESSORS _IOR(&squot;t&squot;,134,unsigned long [8])
DECL|macro|PPPIOCSCOMPRESSOR
mdefine_line|#define PPPIOCSCOMPRESSOR _IOW(&squot;t&squot;,135,int)
DECL|macro|PPPIOCGIFNAME
mdefine_line|#define PPPIOCGIFNAME      _IOR(&squot;t&squot;,136, char [IFNAMSIZ] )
DECL|macro|SC_MP_PROT
mdefine_line|#define SC_MP_PROT       0x00000200
DECL|macro|SC_REJ_MP_PROT
mdefine_line|#define SC_REJ_MP_PROT   0x00000400
DECL|macro|SC_OUT_SHORT_SEQ
mdefine_line|#define SC_OUT_SHORT_SEQ 0x00000800
DECL|macro|SC_IN_SHORT_SEQ
mdefine_line|#define SC_IN_SHORT_SEQ  0x00004000
DECL|macro|SC_DECOMP_ON
mdefine_line|#define SC_DECOMP_ON&t;&t;0x01
DECL|macro|SC_COMP_ON
mdefine_line|#define SC_COMP_ON&t;&t;0x02
DECL|macro|SC_DECOMP_DISCARD
mdefine_line|#define SC_DECOMP_DISCARD&t;0x04
DECL|macro|SC_COMP_DISCARD
mdefine_line|#define SC_COMP_DISCARD&t;&t;0x08
DECL|macro|SC_LINK_DECOMP_ON
mdefine_line|#define SC_LINK_DECOMP_ON&t;0x10
DECL|macro|SC_LINK_COMP_ON
mdefine_line|#define SC_LINK_COMP_ON&t;&t;0x20
DECL|macro|SC_LINK_DECOMP_DISCARD
mdefine_line|#define SC_LINK_DECOMP_DISCARD&t;0x40
DECL|macro|SC_LINK_COMP_DISCARD
mdefine_line|#define SC_LINK_COMP_DISCARD&t;0x80
DECL|macro|ISDN_PPP_COMP_MAX_OPTIONS
mdefine_line|#define ISDN_PPP_COMP_MAX_OPTIONS 16
DECL|macro|IPPP_COMP_FLAG_XMIT
mdefine_line|#define IPPP_COMP_FLAG_XMIT 0x1
DECL|macro|IPPP_COMP_FLAG_LINK
mdefine_line|#define IPPP_COMP_FLAG_LINK 0x2
DECL|struct|isdn_ppp_comp_data
r_struct
id|isdn_ppp_comp_data
(brace
DECL|member|num
r_int
id|num
suffix:semicolon
DECL|member|options
r_int
r_char
id|options
(braket
id|ISDN_PPP_COMP_MAX_OPTIONS
)braket
suffix:semicolon
DECL|member|optlen
r_int
id|optlen
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
DECL|macro|DECOMP_ERR_NOMEM
mdefine_line|#define DECOMP_ERR_NOMEM&t;(-10)
DECL|macro|MP_END_FRAG
mdefine_line|#define MP_END_FRAG    0x40
DECL|macro|MP_BEGIN_FRAG
mdefine_line|#define MP_BEGIN_FRAG  0x80
DECL|macro|MP_MAX_QUEUE_LEN
mdefine_line|#define MP_MAX_QUEUE_LEN&t;16
multiline_comment|/*&n; * We need a way for the decompressor to influence the generation of CCP&n; * Reset-Requests in a variety of ways. The decompressor is already returning&n; * a lot of information (generated skb length, error conditions) so we use&n; * another parameter. This parameter is a pointer to a structure which is&n; * to be marked valid by the decompressor and only in this case is ever used.&n; * Furthermore, the only case where this data is used is when the decom-&n; * pressor returns DECOMP_ERROR.&n; *&n; * We use this same struct for the reset entry of the compressor to commu-&n; * nicate to its caller how to deal with sending of a Reset Ack. In this&n; * case, expra is not used, but other options still apply (suppressing&n; * sending with rsend, appending arbitrary data, etc).&n; */
DECL|macro|IPPP_RESET_MAXDATABYTES
mdefine_line|#define IPPP_RESET_MAXDATABYTES&t;32
DECL|struct|isdn_ppp_resetparams
r_struct
id|isdn_ppp_resetparams
(brace
DECL|member|valid
r_int
r_char
id|valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is this structure filled at all ? */
DECL|member|rsend
r_int
r_char
id|rsend
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Should we send one at all ? */
DECL|member|idval
r_int
r_char
id|idval
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is the id field valid ? */
DECL|member|dtval
r_int
r_char
id|dtval
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is the data field valid ? */
DECL|member|expra
r_int
r_char
id|expra
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* rw Is an Ack expected for this Req ? */
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
multiline_comment|/* wo Send CCP ResetReq with this id */
DECL|member|maxdlen
r_int
r_int
id|maxdlen
suffix:semicolon
multiline_comment|/* ro Max bytes to be stored in data field */
DECL|member|dlen
r_int
r_int
id|dlen
suffix:semicolon
multiline_comment|/* rw Bytes stored in data field */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* wo Data for ResetReq info field */
)brace
suffix:semicolon
multiline_comment|/*&n; * this is an &squot;old friend&squot; from ppp-comp.h under a new name &n; * check the original include for more information&n; */
DECL|struct|isdn_ppp_compressor
r_struct
id|isdn_ppp_compressor
(brace
DECL|member|next
DECL|member|prev
r_struct
id|isdn_ppp_compressor
op_star
id|next
comma
op_star
id|prev
suffix:semicolon
DECL|member|num
r_int
id|num
suffix:semicolon
multiline_comment|/* CCP compression protocol number */
DECL|member|alloc
r_void
op_star
(paren
op_star
id|alloc
)paren
(paren
r_struct
id|isdn_ppp_comp_data
op_star
)paren
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_void
op_star
id|state
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|isdn_ppp_comp_data
op_star
comma
r_int
id|unit
comma
r_int
id|debug
)paren
suffix:semicolon
multiline_comment|/* The reset entry needs to get more exact information about the&n;     ResetReq or ResetAck it was called with. The parameters are&n;     obvious. If reset is called without a Req or Ack frame which&n;     could be handed into it, code MUST be set to 0. Using rsparm,&n;     the reset entry can control if and how a ResetAck is returned. */
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
id|code
comma
r_int
r_char
id|id
comma
r_int
r_char
op_star
id|data
comma
r_int
id|len
comma
r_struct
id|isdn_ppp_resetparams
op_star
id|rsparm
)paren
suffix:semicolon
DECL|member|compress
r_int
(paren
op_star
id|compress
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|sk_buff
op_star
id|in
comma
r_struct
id|sk_buff
op_star
id|skb_out
comma
r_int
id|proto
)paren
suffix:semicolon
DECL|member|decompress
r_int
(paren
op_star
id|decompress
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|sk_buff
op_star
id|in
comma
r_struct
id|sk_buff
op_star
id|skb_out
comma
r_struct
id|isdn_ppp_resetparams
op_star
id|rsparm
)paren
suffix:semicolon
DECL|member|incomp
r_void
(paren
op_star
id|incomp
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|sk_buff
op_star
id|in
comma
r_int
id|proto
)paren
suffix:semicolon
DECL|member|stat
r_void
(paren
op_star
id|stat
)paren
(paren
r_void
op_star
id|state
comma
r_struct
id|compstat
op_star
id|stats
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|isdn_ppp_register_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_unregister_compressor
c_func
(paren
r_struct
id|isdn_ppp_compressor
op_star
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|seqerrs
r_int
r_int
id|seqerrs
suffix:semicolon
DECL|member|frame_drops
r_int
r_int
id|frame_drops
suffix:semicolon
DECL|member|overflows
r_int
r_int
id|overflows
suffix:semicolon
DECL|member|max_queue_len
r_int
r_int
id|max_queue_len
suffix:semicolon
DECL|typedef|isdn_mppp_stats
)brace
id|isdn_mppp_stats
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|mp_mrru
r_int
id|mp_mrru
suffix:semicolon
multiline_comment|/* unused                             */
DECL|member|frags
r_struct
id|sk_buff
op_star
id|frags
suffix:semicolon
multiline_comment|/* fragments sl list -- use skb-&gt;next */
DECL|member|frames
r_int
id|frames
suffix:semicolon
multiline_comment|/* number of frames in the frame list */
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
multiline_comment|/* last processed packet seq #: any packets&n;  &t;&t;&t;&t; * with smaller seq # will be dropped&n;&t;&t;&t;&t; * unconditionally */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|ref_ct
r_int
id|ref_ct
suffix:semicolon
multiline_comment|/* statistics */
DECL|member|stats
id|isdn_mppp_stats
id|stats
suffix:semicolon
DECL|typedef|ippp_bundle
)brace
id|ippp_bundle
suffix:semicolon
DECL|macro|IPPP_MAX_RQ_LEN
mdefine_line|#define IPPP_MAX_RQ_LEN     8
multiline_comment|/* The data structure for one CCP reset transaction */
DECL|enum|ippp_ccp_reset_states
r_enum
id|ippp_ccp_reset_states
(brace
DECL|enumerator|CCPResetIdle
id|CCPResetIdle
comma
DECL|enumerator|CCPResetSentReq
id|CCPResetSentReq
comma
DECL|enumerator|CCPResetRcvdReq
id|CCPResetRcvdReq
comma
DECL|enumerator|CCPResetSentAck
id|CCPResetSentAck
comma
DECL|enumerator|CCPResetRcvdAck
id|CCPResetRcvdAck
)brace
suffix:semicolon
DECL|struct|ippp_ccp_reset_state
r_struct
id|ippp_ccp_reset_state
(brace
DECL|member|state
r_enum
id|ippp_ccp_reset_states
id|state
suffix:semicolon
multiline_comment|/* State of this transaction */
DECL|member|ccp
r_struct
id|ippp_ccp
op_star
id|ccp
suffix:semicolon
multiline_comment|/* Backlink */
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
multiline_comment|/* id index */
DECL|member|ta
r_int
r_char
id|ta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* The timer is active (flag) */
DECL|member|expra
r_int
r_char
id|expra
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* We expect a ResetAck at all */
DECL|member|dlen
r_int
id|dlen
suffix:semicolon
multiline_comment|/* Databytes stored in data */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* For timeouts/retries */
multiline_comment|/* This is a hack but seems sufficient for the moment. We do not want&n;     to have this be yet another allocation for some bytes, it is more&n;     memory management overhead than the whole mess is worth. */
DECL|member|data
r_int
r_char
id|data
(braket
id|IPPP_RESET_MAXDATABYTES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The data structure keeping track of the currently outstanding CCP Reset&n;   transactions. */
DECL|struct|ippp_ccp_reset
r_struct
id|ippp_ccp_reset
(brace
DECL|member|rs
r_struct
id|ippp_ccp_reset_state
op_star
id|rs
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* One per possible id */
DECL|member|lastid
r_int
r_char
id|lastid
suffix:semicolon
multiline_comment|/* Last id allocated by the engine */
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_ISDN_PPP_H */
eof
