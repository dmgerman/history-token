macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/crypto.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/route.h&gt;
multiline_comment|/* Organization of SPD aka &quot;XFRM rules&quot;&n;   ------------------------------------&n;&n;   Basic objects:&n;   - policy rule, struct xfrm_policy (=SPD entry)&n;   - bundle of transformations, struct dst_entry == struct xfrm_dst (=SA bundle)&n;   - instance of a transformer, struct xfrm_state (=SA)&n;   - template to clone xfrm_state, struct xfrm_tmpl&n;&n;   SPD is plain linear list of xfrm_policy rules, ordered by priority.&n;   (To be compatible with existing pfkeyv2 implementations,&n;   many rules with priority of 0x7fffffff are allowed to exist and&n;   such rules are ordered in an unpredictable way, thanks to bsd folks.)&n;&n;   Lookup is plain linear search until the first match with selector.&n;&n;   If &quot;action&quot; is &quot;block&quot;, then we prohibit the flow, otherwise:&n;   if &quot;xfrms_nr&quot; is zero, the flow passes untransformed. Otherwise,&n;   policy entry has list of up to XFRM_MAX_DEPTH transformations,&n;   described by templates xfrm_tmpl. Each template is resolved&n;   to a complete xfrm_state (see below) and we pack bundle of transformations&n;   to a dst_entry returned to requestor.&n;&n;   dst -. xfrm  .-&gt; xfrm_state #1&n;    |---. child .-&gt; dst -. xfrm .-&gt; xfrm_state #2&n;                     |---. child .-&gt; dst -. xfrm .-&gt; xfrm_state #3&n;                                      |---. child .-&gt; NULL&n;&n;   Bundles are cached at xrfm_policy struct (field -&gt;bundles).&n;&n;&n;   Resolution of xrfm_tmpl&n;   -----------------------&n;   Template contains:&n;   1. -&gt;mode&t;&t;Mode: transport or tunnel&n;   2. -&gt;id.proto&t;Protocol: AH/ESP/IPCOMP&n;   3. -&gt;id.daddr&t;Remote tunnel endpoint, ignored for transport mode.&n;      Q: allow to resolve security gateway?&n;   4. -&gt;id.spi          If not zero, static SPI.&n;   5. -&gt;saddr&t;&t;Local tunnel endpoint, ignored for transport mode.&n;   6. -&gt;algos&t;&t;List of allowed algos. Plain bitmask now.&n;      Q: ealgos, aalgos, calgos. What a mess...&n;   7. -&gt;share&t;&t;Sharing mode.&n;      Q: how to implement private sharing mode? To add struct sock* to&n;      flow id?&n;   8. -&gt;resolved&t;If template uniquely resolves to a static xfrm_state,&n;                        the reference is stores here.&n;&n;   Having this template we search through SAD searching for entries&n;   with appropriate mode/proto/algo, permitted by selector.&n;   If no appropriate entry found, it is requested from key manager.&n;&n;   PROBLEMS:&n;   Q: How to find all the bundles referring to a physical path for&n;      PMTU discovery? Seems, dst should contain list of all parents...&n;      and enter to infinite locking hierarchy disaster.&n;      No! It is easier, we will not search for them, let them find us.&n;      We add genid to each dst plus pointer to genid of raw IP route,&n;      pmtu disc will update pmtu on raw IP route and increase its genid.&n;      dst_check() will see this for top level and trigger resyncing&n;      metrics. Plus, it will be made via sk-&gt;dst_cache. Solved.&n; */
multiline_comment|/* Structure to encapsulate addresses. I do not want to use&n; * &quot;standard&quot; structure. My apologies. */
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|addr
id|u32
id|addr
suffix:semicolon
DECL|member|mask
id|u32
id|mask
suffix:semicolon
multiline_comment|/* Use unused bits to cache mask. */
DECL|member|a4
)brace
id|a4
suffix:semicolon
DECL|macro|xfrm4_addr
mdefine_line|#define xfrm4_addr a4.addr
DECL|macro|xfrm4_mask
mdefine_line|#define xfrm4_mask a4.mask
DECL|member|a6
id|u32
id|a6
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|xfrm_address_t
)brace
id|xfrm_address_t
suffix:semicolon
multiline_comment|/* Ident of a specific xfrm_state. It is used on input to lookup&n; * the state by (spi,daddr,ah/esp) or to store information about&n; * spi, protocol and tunnel address on output. */
DECL|struct|xfrm_id
r_struct
id|xfrm_id
(brace
DECL|member|daddr
id|xfrm_address_t
id|daddr
suffix:semicolon
DECL|member|spi
id|__u32
id|spi
suffix:semicolon
DECL|member|proto
id|__u8
id|proto
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Selector, used as selector both on policy rules (SPD) and SAs. */
DECL|struct|xfrm_selector
r_struct
id|xfrm_selector
(brace
DECL|member|daddr
id|xfrm_address_t
id|daddr
suffix:semicolon
DECL|member|saddr
id|xfrm_address_t
id|saddr
suffix:semicolon
DECL|member|dport
id|__u16
id|dport
suffix:semicolon
DECL|member|dport_mask
id|__u16
id|dport_mask
suffix:semicolon
DECL|member|sport
id|__u16
id|sport
suffix:semicolon
DECL|member|sport_mask
id|__u16
id|sport_mask
suffix:semicolon
DECL|member|prefixlen_d
id|__u8
id|prefixlen_d
suffix:semicolon
DECL|member|prefixlen_s
id|__u8
id|prefixlen_s
suffix:semicolon
DECL|member|proto
id|__u8
id|proto
suffix:semicolon
DECL|member|ifindex
r_int
id|ifindex
suffix:semicolon
DECL|member|user
id|uid_t
id|user
suffix:semicolon
DECL|member|owner
r_void
op_star
id|owner
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_lifetime_cfg
r_struct
id|xfrm_lifetime_cfg
(brace
DECL|member|soft_byte_limit
id|u64
id|soft_byte_limit
suffix:semicolon
DECL|member|hard_byte_limit
id|u64
id|hard_byte_limit
suffix:semicolon
DECL|member|soft_packet_limit
id|u64
id|soft_packet_limit
suffix:semicolon
DECL|member|hard_packet_limit
id|u64
id|hard_packet_limit
suffix:semicolon
DECL|member|soft_add_expires_seconds
id|u64
id|soft_add_expires_seconds
suffix:semicolon
DECL|member|hard_add_expires_seconds
id|u64
id|hard_add_expires_seconds
suffix:semicolon
DECL|member|soft_use_expires_seconds
id|u64
id|soft_use_expires_seconds
suffix:semicolon
DECL|member|hard_use_expires_seconds
id|u64
id|hard_use_expires_seconds
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_lifetime_cur
r_struct
id|xfrm_lifetime_cur
(brace
DECL|member|bytes
id|u64
id|bytes
suffix:semicolon
DECL|member|packets
id|u64
id|packets
suffix:semicolon
DECL|member|add_time
id|u64
id|add_time
suffix:semicolon
DECL|member|use_time
id|u64
id|use_time
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_replay_state
r_struct
id|xfrm_replay_state
(brace
DECL|member|oseq
id|u32
id|oseq
suffix:semicolon
DECL|member|seq
id|u32
id|seq
suffix:semicolon
DECL|member|bitmap
id|u32
id|bitmap
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_algo
r_struct
id|xfrm_algo
(brace
DECL|member|alg_name
r_char
id|alg_name
(braket
id|CRYPTO_MAX_ALG_NAME
)braket
suffix:semicolon
DECL|member|alg_key_len
r_int
id|alg_key_len
suffix:semicolon
multiline_comment|/* in bits */
DECL|member|alg_key
r_char
id|alg_key
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Full description of state of transformer. */
DECL|struct|xfrm_state
r_struct
id|xfrm_state
(brace
DECL|member|bydst
r_struct
id|list_head
id|bydst
suffix:semicolon
DECL|member|byspi
r_struct
id|list_head
id|byspi
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|id
r_struct
id|xfrm_id
id|id
suffix:semicolon
DECL|member|sel
r_struct
id|xfrm_selector
id|sel
suffix:semicolon
multiline_comment|/* Key manger bits */
r_struct
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|seq
id|u32
id|seq
suffix:semicolon
DECL|member|warn_bytes
id|u64
id|warn_bytes
suffix:semicolon
DECL|member|km
)brace
id|km
suffix:semicolon
multiline_comment|/* Parameters of this state. */
r_struct
(brace
DECL|member|mode
id|u8
id|mode
suffix:semicolon
DECL|member|replay_window
id|u8
id|replay_window
suffix:semicolon
DECL|member|aalgo
DECL|member|ealgo
DECL|member|calgo
id|u8
id|aalgo
comma
id|ealgo
comma
id|calgo
suffix:semicolon
DECL|member|reqid
id|u16
id|reqid
suffix:semicolon
DECL|member|saddr
id|xfrm_address_t
id|saddr
suffix:semicolon
DECL|member|header_len
r_int
id|header_len
suffix:semicolon
DECL|member|trailer_len
r_int
id|trailer_len
suffix:semicolon
DECL|member|props
)brace
id|props
suffix:semicolon
DECL|member|lft
r_struct
id|xfrm_lifetime_cfg
id|lft
suffix:semicolon
multiline_comment|/* Data for transformer */
DECL|member|aalg
r_struct
id|xfrm_algo
op_star
id|aalg
suffix:semicolon
DECL|member|ealg
r_struct
id|xfrm_algo
op_star
id|ealg
suffix:semicolon
DECL|member|calg
r_struct
id|xfrm_algo
op_star
id|calg
suffix:semicolon
multiline_comment|/* State for replay detection */
DECL|member|replay
r_struct
id|xfrm_replay_state
id|replay
suffix:semicolon
multiline_comment|/* Statistics */
r_struct
(brace
DECL|member|replay_window
id|u32
id|replay_window
suffix:semicolon
DECL|member|replay
id|u32
id|replay
suffix:semicolon
DECL|member|integrity_failed
id|u32
id|integrity_failed
suffix:semicolon
DECL|member|stats
)brace
id|stats
suffix:semicolon
DECL|member|curlft
r_struct
id|xfrm_lifetime_cur
id|curlft
suffix:semicolon
multiline_comment|/* Reference to data common to all the instances of this&n;&t; * transformer. */
DECL|member|type
r_struct
id|xfrm_type
op_star
id|type
suffix:semicolon
multiline_comment|/* Private data of this transformer, format is opaque,&n;&t; * interpreted by xfrm_type methods. */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|XFRM_STATE_VOID
id|XFRM_STATE_VOID
comma
DECL|enumerator|XFRM_STATE_ACQ
id|XFRM_STATE_ACQ
comma
DECL|enumerator|XFRM_STATE_VALID
id|XFRM_STATE_VALID
comma
DECL|enumerator|XFRM_STATE_ERROR
id|XFRM_STATE_ERROR
comma
DECL|enumerator|XFRM_STATE_EXPIRED
id|XFRM_STATE_EXPIRED
comma
DECL|enumerator|XFRM_STATE_DEAD
id|XFRM_STATE_DEAD
)brace
suffix:semicolon
DECL|struct|xfrm_type
r_struct
id|xfrm_type
(brace
DECL|member|description
r_char
op_star
id|description
suffix:semicolon
DECL|member|owner
r_struct
id|module
op_star
id|owner
suffix:semicolon
DECL|member|proto
id|__u8
id|proto
suffix:semicolon
DECL|member|init_state
r_int
(paren
op_star
id|init_state
)paren
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_void
op_star
id|args
)paren
suffix:semicolon
DECL|member|destructor
r_void
(paren
op_star
id|destructor
)paren
(paren
r_struct
id|xfrm_state
op_star
)paren
suffix:semicolon
DECL|member|input
r_int
(paren
op_star
id|input
)paren
(paren
r_struct
id|xfrm_state
op_star
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|member|output
r_int
(paren
op_star
id|output
)paren
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* Estimate maximal size of result of transformation of a dgram */
DECL|member|get_max_size
id|u32
(paren
op_star
id|get_max_size
)paren
(paren
r_struct
id|xfrm_state
op_star
comma
r_int
id|size
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|xfrm_register_type
c_func
(paren
r_struct
id|xfrm_type
op_star
id|type
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_unregister_type
c_func
(paren
r_struct
id|xfrm_type
op_star
id|type
)paren
suffix:semicolon
r_extern
r_struct
id|xfrm_type
op_star
id|xfrm_get_type
c_func
(paren
id|u8
id|proto
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_put_type
c_func
(paren
r_struct
id|xfrm_type
op_star
id|type
)paren
suffix:semicolon
DECL|struct|xfrm_tmpl
r_struct
id|xfrm_tmpl
(brace
multiline_comment|/* id in template is interpreted as:&n; * daddr - destination of tunnel, may be zero for transport mode.&n; * spi   - zero to acquire spi. Not zero if spi is static, then&n; *&t;   daddr must be fixed too.&n; * proto - AH/ESP/IPCOMP&n; */
DECL|member|id
r_struct
id|xfrm_id
id|id
suffix:semicolon
multiline_comment|/* Source address of tunnel. Ignored, if it is not a tunnel. */
DECL|member|saddr
id|xfrm_address_t
id|saddr
suffix:semicolon
DECL|member|reqid
id|__u16
id|reqid
suffix:semicolon
multiline_comment|/* Mode: transport/tunnel */
DECL|member|mode
id|__u8
id|mode
suffix:semicolon
multiline_comment|/* Sharing mode: unique, this session only, this user only etc. */
DECL|member|share
id|__u8
id|share
suffix:semicolon
multiline_comment|/* Bit mask of algos allowed for acquisition */
DECL|member|aalgos
id|__u32
id|aalgos
suffix:semicolon
DECL|member|ealgos
id|__u32
id|ealgos
suffix:semicolon
DECL|member|calgos
id|__u32
id|calgos
suffix:semicolon
multiline_comment|/* If template statically resolved, hold ref here */
DECL|member|resolved
r_struct
id|xfrm_state
op_star
id|resolved
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|XFRM_MAX_DEPTH
mdefine_line|#define XFRM_MAX_DEPTH&t;&t;3
r_enum
(brace
DECL|enumerator|XFRM_SHARE_ANY
id|XFRM_SHARE_ANY
comma
multiline_comment|/* No limitations */
DECL|enumerator|XFRM_SHARE_SESSION
id|XFRM_SHARE_SESSION
comma
multiline_comment|/* For this session only */
DECL|enumerator|XFRM_SHARE_USER
id|XFRM_SHARE_USER
comma
multiline_comment|/* For this user only */
DECL|enumerator|XFRM_SHARE_UNIQUE
id|XFRM_SHARE_UNIQUE
multiline_comment|/* Use once */
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|XFRM_POLICY_IN
id|XFRM_POLICY_IN
op_assign
l_int|0
comma
DECL|enumerator|XFRM_POLICY_OUT
id|XFRM_POLICY_OUT
op_assign
l_int|1
comma
DECL|enumerator|XFRM_POLICY_FWD
id|XFRM_POLICY_FWD
op_assign
l_int|2
comma
DECL|enumerator|XFRM_POLICY_MAX
id|XFRM_POLICY_MAX
op_assign
l_int|3
)brace
suffix:semicolon
DECL|struct|xfrm_policy
r_struct
id|xfrm_policy
(brace
DECL|member|next
r_struct
id|xfrm_policy
op_star
id|next
suffix:semicolon
multiline_comment|/* This lock only affects elements except for entry. */
DECL|member|lock
id|rwlock_t
id|lock
suffix:semicolon
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|priority
id|u32
id|priority
suffix:semicolon
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|member|selector
r_struct
id|xfrm_selector
id|selector
suffix:semicolon
DECL|member|lft
r_struct
id|xfrm_lifetime_cfg
id|lft
suffix:semicolon
DECL|member|curlft
r_struct
id|xfrm_lifetime_cur
id|curlft
suffix:semicolon
DECL|member|bundles
r_struct
id|dst_entry
op_star
id|bundles
suffix:semicolon
DECL|member|action
id|__u8
id|action
suffix:semicolon
DECL|macro|XFRM_POLICY_ALLOW
mdefine_line|#define XFRM_POLICY_ALLOW&t;0
DECL|macro|XFRM_POLICY_BLOCK
mdefine_line|#define XFRM_POLICY_BLOCK&t;1
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|macro|XFRM_POLICY_LOCALOK
mdefine_line|#define XFRM_POLICY_LOCALOK&t;1&t;/* Allow user to override global policy */
DECL|member|dead
id|__u8
id|dead
suffix:semicolon
DECL|member|xfrm_nr
id|__u8
id|xfrm_nr
suffix:semicolon
DECL|member|xfrm_vec
r_struct
id|xfrm_tmpl
id|xfrm_vec
(braket
id|XFRM_MAX_DEPTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_mgr
r_struct
id|xfrm_mgr
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|id
r_char
op_star
id|id
suffix:semicolon
DECL|member|notify
r_int
(paren
op_star
id|notify
)paren
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_int
id|event
)paren
suffix:semicolon
DECL|member|acquire
r_int
(paren
op_star
id|acquire
)paren
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_tmpl
op_star
comma
r_struct
id|xfrm_policy
op_star
id|xp
comma
r_int
id|dir
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|xfrm_register_km
c_func
(paren
r_struct
id|xfrm_mgr
op_star
id|km
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_unregister_km
c_func
(paren
r_struct
id|xfrm_mgr
op_star
id|km
)paren
suffix:semicolon
r_extern
r_struct
id|xfrm_policy
op_star
id|xfrm_policy_list
(braket
id|XFRM_POLICY_MAX
)braket
suffix:semicolon
DECL|function|xfrm_pol_hold
r_static
r_inline
r_void
id|xfrm_pol_hold
c_func
(paren
r_struct
id|xfrm_policy
op_star
id|policy
)paren
(brace
r_if
c_cond
(paren
id|policy
)paren
id|atomic_inc
c_func
(paren
op_amp
id|policy-&gt;refcnt
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__xfrm_policy_destroy
c_func
(paren
r_struct
id|xfrm_policy
op_star
id|policy
)paren
suffix:semicolon
DECL|function|xfrm_pol_put
r_static
r_inline
r_void
id|xfrm_pol_put
c_func
(paren
r_struct
id|xfrm_policy
op_star
id|policy
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|policy-&gt;refcnt
)paren
)paren
id|__xfrm_policy_destroy
c_func
(paren
id|policy
)paren
suffix:semicolon
)brace
r_extern
r_void
id|__xfrm_state_destroy
c_func
(paren
r_struct
id|xfrm_state
op_star
)paren
suffix:semicolon
DECL|function|xfrm_state_put
r_static
r_inline
r_void
id|xfrm_state_put
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|x-&gt;refcnt
)paren
)paren
id|__xfrm_state_destroy
c_func
(paren
id|x
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|xfrm4_selector_match
id|xfrm4_selector_match
c_func
(paren
r_struct
id|xfrm_selector
op_star
id|sel
comma
r_struct
id|flowi
op_star
id|fl
)paren
(brace
r_return
op_logical_neg
(paren
(paren
id|fl-&gt;fl4_dst
op_xor
id|sel-&gt;daddr.xfrm4_addr
)paren
op_amp
id|sel-&gt;daddr.xfrm4_mask
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|fl-&gt;uli_u.ports.dport
op_xor
id|sel-&gt;dport
)paren
op_amp
id|sel-&gt;dport_mask
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|fl-&gt;uli_u.ports.sport
op_xor
id|sel-&gt;sport
)paren
op_amp
id|sel-&gt;sport_mask
)paren
op_logical_and
(paren
id|fl-&gt;proto
op_eq
id|sel-&gt;proto
op_logical_or
op_logical_neg
id|sel-&gt;proto
)paren
op_logical_and
(paren
id|fl-&gt;oif
op_eq
id|sel-&gt;ifindex
op_logical_or
op_logical_neg
id|sel-&gt;ifindex
)paren
op_logical_and
op_logical_neg
(paren
(paren
id|fl-&gt;fl4_src
op_xor
id|sel-&gt;saddr.xfrm4_addr
)paren
op_amp
id|sel-&gt;saddr.xfrm4_mask
)paren
suffix:semicolon
)brace
multiline_comment|/* A struct encoding bundle of transformations to apply to some set of flow.&n; *&n; * dst-&gt;child points to the next element of bundle.&n; * dst-&gt;xfrm  points to an instanse of transformer.&n; *&n; * Due to unfortunate limitations of current routing cache, which we&n; * have no time to fix, it mirrors struct rtable and bound to the same&n; * routing key, including saddr,daddr. However, we can have many of&n; * bundles differing by session id. All the bundles grow from a parent&n; * policy rule.&n; */
DECL|struct|xfrm_dst
r_struct
id|xfrm_dst
(brace
r_union
(brace
DECL|member|next
r_struct
id|xfrm_dst
op_star
id|next
suffix:semicolon
DECL|member|dst
r_struct
id|dst_entry
id|dst
suffix:semicolon
DECL|member|rt
r_struct
id|rtable
id|rt
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sec_path
r_struct
id|sec_path
(brace
DECL|member|refcnt
id|atomic_t
id|refcnt
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|xvec
r_struct
id|xfrm_state
op_star
id|xvec
(braket
id|XFRM_MAX_DEPTH
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_struct
id|sec_path
op_star
DECL|function|secpath_get
id|secpath_get
c_func
(paren
r_struct
id|sec_path
op_star
id|sp
)paren
(brace
r_if
c_cond
(paren
id|sp
)paren
id|atomic_inc
c_func
(paren
op_amp
id|sp-&gt;refcnt
)paren
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
r_extern
r_void
id|__secpath_destroy
c_func
(paren
r_struct
id|sec_path
op_star
id|sp
)paren
suffix:semicolon
r_static
r_inline
r_void
DECL|function|secpath_put
id|secpath_put
c_func
(paren
r_struct
id|sec_path
op_star
id|sp
)paren
(brace
r_if
c_cond
(paren
id|sp
op_logical_and
id|atomic_dec_and_test
c_func
(paren
op_amp
id|sp-&gt;refcnt
)paren
)paren
id|__secpath_destroy
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
r_extern
r_int
id|__xfrm_policy_check
c_func
(paren
r_int
id|dir
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|function|xfrm_policy_check
r_static
r_inline
r_int
id|xfrm_policy_check
c_func
(paren
r_int
id|dir
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
op_logical_neg
id|xfrm_policy_list
(braket
id|dir
)braket
op_logical_or
(paren
id|skb-&gt;dst-&gt;flags
op_amp
id|DST_NOPOLICY
)paren
op_logical_or
id|__xfrm_policy_check
c_func
(paren
id|dir
comma
id|skb
)paren
suffix:semicolon
)brace
r_extern
r_int
id|__xfrm_route_forward
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|function|xfrm_route_forward
r_static
r_inline
r_int
id|xfrm_route_forward
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_return
op_logical_neg
id|xfrm_policy_list
(braket
id|XFRM_POLICY_OUT
)braket
op_logical_or
(paren
id|skb-&gt;dst-&gt;flags
op_amp
id|DST_NOXFRM
)paren
op_logical_or
id|__xfrm_route_forward
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
r_extern
r_void
id|xfrm_state_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_input_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_state_walk
c_func
(paren
id|u8
id|proto
comma
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|xfrm_state
op_star
comma
r_int
comma
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|xfrm_state
op_star
id|xfrm_state_alloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|xfrm_state
op_star
id|xfrm_state_find
c_func
(paren
id|u32
id|daddr
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|xfrm_tmpl
op_star
id|tmpl
comma
r_struct
id|xfrm_policy
op_star
id|pol
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_state_check_expire
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_state_insert
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_state_check_space
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_struct
id|xfrm_state
op_star
id|xfrm_state_lookup
c_func
(paren
id|u32
id|daddr
comma
id|u32
id|spi
comma
id|u8
id|proto
)paren
suffix:semicolon
r_extern
r_struct
id|xfrm_state
op_star
id|xfrm_find_acq_byseq
c_func
(paren
id|u32
id|seq
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_state_delete
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_state_flush
c_func
(paren
id|u8
id|proto
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_replay_check
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
id|u32
id|seq
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_replay_advance
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
id|u32
id|seq
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_check_selectors
c_func
(paren
r_struct
id|xfrm_state
op_star
op_star
id|x
comma
r_int
id|n
comma
r_struct
id|flowi
op_star
id|fl
)paren
suffix:semicolon
r_extern
r_int
id|xfrm4_rcv
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_struct
id|xfrm_policy
op_star
id|xfrm_policy_alloc
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|xfrm_policy_walk
c_func
(paren
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|xfrm_policy
op_star
comma
r_int
comma
r_int
comma
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
r_struct
id|xfrm_policy
op_star
id|xfrm_policy_lookup
c_func
(paren
r_int
id|dir
comma
r_struct
id|flowi
op_star
id|fl
)paren
suffix:semicolon
r_int
id|xfrm_policy_insert
c_func
(paren
r_int
id|dir
comma
r_struct
id|xfrm_policy
op_star
id|policy
comma
r_int
id|excl
)paren
suffix:semicolon
r_struct
id|xfrm_policy
op_star
id|xfrm_policy_delete
c_func
(paren
r_int
id|dir
comma
r_struct
id|xfrm_selector
op_star
id|sel
)paren
suffix:semicolon
r_struct
id|xfrm_policy
op_star
id|xfrm_policy_byid
c_func
(paren
r_int
id|dir
comma
id|u32
id|id
comma
r_int
r_delete
)paren
suffix:semicolon
r_void
id|xfrm_policy_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|xfrm_bundle_create
c_func
(paren
r_struct
id|xfrm_policy
op_star
id|policy
comma
r_struct
id|xfrm_state
op_star
op_star
id|xfrm
comma
r_struct
id|flowi
op_star
id|fl
comma
r_struct
id|dst_entry
op_star
op_star
id|dst_p
)paren
suffix:semicolon
r_void
id|xfrm_alloc_spi
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
id|u32
id|minspi
comma
id|u32
id|maxspi
)paren
suffix:semicolon
r_struct
id|xfrm_state
op_star
id|xfrm_find_acq
c_func
(paren
id|u8
id|mode
comma
id|u16
id|reqid
comma
id|u8
id|proto
comma
id|u32
id|daddr
comma
id|u32
id|saddr
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_policy_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|xfrm_policy_kill
c_func
(paren
r_struct
id|xfrm_policy
op_star
)paren
suffix:semicolon
r_extern
id|wait_queue_head_t
op_star
id|km_waitq
suffix:semicolon
r_extern
r_void
id|km_warn_expired
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
suffix:semicolon
r_extern
r_void
id|km_expired
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
)paren
suffix:semicolon
r_extern
r_int
id|km_query
c_func
(paren
r_struct
id|xfrm_state
op_star
id|x
comma
r_struct
id|xfrm_tmpl
op_star
comma
r_struct
id|xfrm_policy
op_star
id|pol
)paren
suffix:semicolon
eof
