macro_line|#ifndef _LINUX_XFRM_H
DECL|macro|_LINUX_XFRM_H
mdefine_line|#define _LINUX_XFRM_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* All of the structures in this file may not change size as they are&n; * passed into the kernel from userspace via netlink sockets.&n; */
multiline_comment|/* Structure to encapsulate addresses. I do not want to use&n; * &quot;standard&quot; structure. My apologies.&n; */
r_typedef
r_union
(brace
DECL|member|a4
id|__u32
id|a4
suffix:semicolon
DECL|member|a6
id|__u32
id|a6
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|xfrm_address_t
)brace
id|xfrm_address_t
suffix:semicolon
multiline_comment|/* Ident of a specific xfrm_state. It is used on input to lookup&n; * the state by (spi,daddr,ah/esp) or to store information about&n; * spi, protocol and tunnel address on output.&n; */
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
)brace
suffix:semicolon
DECL|macro|XFRM_INF
mdefine_line|#define XFRM_INF (~(__u64)0)
DECL|struct|xfrm_lifetime_cfg
r_struct
id|xfrm_lifetime_cfg
(brace
DECL|member|soft_byte_limit
id|__u64
id|soft_byte_limit
suffix:semicolon
DECL|member|hard_byte_limit
id|__u64
id|hard_byte_limit
suffix:semicolon
DECL|member|soft_packet_limit
id|__u64
id|soft_packet_limit
suffix:semicolon
DECL|member|hard_packet_limit
id|__u64
id|hard_packet_limit
suffix:semicolon
DECL|member|soft_add_expires_seconds
id|__u64
id|soft_add_expires_seconds
suffix:semicolon
DECL|member|hard_add_expires_seconds
id|__u64
id|hard_add_expires_seconds
suffix:semicolon
DECL|member|soft_use_expires_seconds
id|__u64
id|soft_use_expires_seconds
suffix:semicolon
DECL|member|hard_use_expires_seconds
id|__u64
id|hard_use_expires_seconds
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_lifetime_cur
r_struct
id|xfrm_lifetime_cur
(brace
DECL|member|bytes
id|__u64
id|bytes
suffix:semicolon
DECL|member|packets
id|__u64
id|packets
suffix:semicolon
DECL|member|add_time
id|__u64
id|add_time
suffix:semicolon
DECL|member|use_time
id|__u64
id|use_time
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_replay_state
r_struct
id|xfrm_replay_state
(brace
DECL|member|oseq
id|__u32
id|oseq
suffix:semicolon
DECL|member|seq
id|__u32
id|seq
suffix:semicolon
DECL|member|bitmap
id|__u32
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
l_int|64
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
DECL|struct|xfrm_stats
r_struct
id|xfrm_stats
(brace
DECL|member|replay_window
id|__u32
id|replay_window
suffix:semicolon
DECL|member|replay
id|__u32
id|replay
suffix:semicolon
DECL|member|integrity_failed
id|__u32
id|integrity_failed
suffix:semicolon
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
multiline_comment|/* Netlink configuration messages.  */
DECL|macro|XFRM_MSG_BASE
mdefine_line|#define XFRM_MSG_BASE&t;&t;0x10
DECL|macro|XFRM_MSG_NEWSA
mdefine_line|#define XFRM_MSG_NEWSA&t;&t;(XFRM_MSG_BASE + 0)
DECL|macro|XFRM_MSG_DELSA
mdefine_line|#define XFRM_MSG_DELSA&t;&t;(XFRM_MSG_BASE + 1)
DECL|macro|XFRM_MSG_GETSA
mdefine_line|#define XFRM_MSG_GETSA&t;&t;(XFRM_MSG_BASE + 2)
DECL|macro|XFRM_MSG_NEWPOLICY
mdefine_line|#define XFRM_MSG_NEWPOLICY&t;(XFRM_MSG_BASE + 3)
DECL|macro|XFRM_MSG_DELPOLICY
mdefine_line|#define XFRM_MSG_DELPOLICY&t;(XFRM_MSG_BASE + 4)
DECL|macro|XFRM_MSG_GETPOLICY
mdefine_line|#define XFRM_MSG_GETPOLICY&t;(XFRM_MSG_BASE + 5)
DECL|macro|XFRM_MSG_ALLOCSPI
mdefine_line|#define XFRM_MSG_ALLOCSPI&t;(XFRM_MSG_BASE + 6)
DECL|macro|XFRM_MSG_ACQUIRE
mdefine_line|#define XFRM_MSG_ACQUIRE&t;(XFRM_MSG_BASE + 7)
DECL|macro|XFRM_MSG_EXPIRE
mdefine_line|#define XFRM_MSG_EXPIRE&t;&t;(XFRM_MSG_BASE + 8)
DECL|macro|XFRM_MSG_UPDPOLICY
mdefine_line|#define XFRM_MSG_UPDPOLICY&t;(XFRM_MSG_BASE + 9)
DECL|macro|XFRM_MSG_UPDSA
mdefine_line|#define XFRM_MSG_UPDSA&t;&t;(XFRM_MSG_BASE + 10)
DECL|macro|XFRM_MSG_POLEXPIRE
mdefine_line|#define XFRM_MSG_POLEXPIRE&t;(XFRM_MSG_BASE + 11)
DECL|macro|XFRM_MSG_MAX
mdefine_line|#define XFRM_MSG_MAX&t;&t;(XFRM_MSG_POLEXPIRE+1)
DECL|struct|xfrm_user_tmpl
r_struct
id|xfrm_user_tmpl
(brace
DECL|member|id
r_struct
id|xfrm_id
id|id
suffix:semicolon
DECL|member|saddr
id|xfrm_address_t
id|saddr
suffix:semicolon
DECL|member|reqid
id|__u32
id|reqid
suffix:semicolon
DECL|member|mode
id|__u8
id|mode
suffix:semicolon
DECL|member|share
id|__u8
id|share
suffix:semicolon
DECL|member|optional
id|__u8
id|optional
suffix:semicolon
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
)brace
suffix:semicolon
DECL|struct|xfrm_encap_tmpl
r_struct
id|xfrm_encap_tmpl
(brace
DECL|member|encap_type
id|__u16
id|encap_type
suffix:semicolon
DECL|member|encap_sport
id|__u16
id|encap_sport
suffix:semicolon
DECL|member|encap_dport
id|__u16
id|encap_dport
suffix:semicolon
DECL|member|encap_oa
id|xfrm_address_t
id|encap_oa
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Netlink message attributes.  */
DECL|enum|xfrm_attr_type_t
r_enum
id|xfrm_attr_type_t
(brace
DECL|enumerator|XFRMA_UNSPEC
id|XFRMA_UNSPEC
comma
DECL|enumerator|XFRMA_ALG_AUTH
id|XFRMA_ALG_AUTH
comma
multiline_comment|/* struct xfrm_algo */
DECL|enumerator|XFRMA_ALG_CRYPT
id|XFRMA_ALG_CRYPT
comma
multiline_comment|/* struct xfrm_algo */
DECL|enumerator|XFRMA_ALG_COMP
id|XFRMA_ALG_COMP
comma
multiline_comment|/* struct xfrm_algo */
DECL|enumerator|XFRMA_ENCAP
id|XFRMA_ENCAP
comma
multiline_comment|/* struct xfrm_algo + struct xfrm_encap_tmpl */
DECL|enumerator|XFRMA_TMPL
id|XFRMA_TMPL
comma
multiline_comment|/* 1 or more struct xfrm_user_tmpl */
DECL|macro|XFRMA_MAX
mdefine_line|#define XFRMA_MAX XFRMA_TMPL
)brace
suffix:semicolon
DECL|struct|xfrm_usersa_info
r_struct
id|xfrm_usersa_info
(brace
DECL|member|sel
r_struct
id|xfrm_selector
id|sel
suffix:semicolon
DECL|member|id
r_struct
id|xfrm_id
id|id
suffix:semicolon
DECL|member|saddr
id|xfrm_address_t
id|saddr
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
DECL|member|stats
r_struct
id|xfrm_stats
id|stats
suffix:semicolon
DECL|member|seq
id|__u32
id|seq
suffix:semicolon
DECL|member|reqid
id|__u32
id|reqid
suffix:semicolon
DECL|member|family
id|__u16
id|family
suffix:semicolon
DECL|member|mode
id|__u8
id|mode
suffix:semicolon
multiline_comment|/* 0=transport,1=tunnel */
DECL|member|replay_window
id|__u8
id|replay_window
suffix:semicolon
DECL|member|flags
id|__u8
id|flags
suffix:semicolon
DECL|macro|XFRM_STATE_NOECN
mdefine_line|#define XFRM_STATE_NOECN&t;1
)brace
suffix:semicolon
DECL|struct|xfrm_usersa_id
r_struct
id|xfrm_usersa_id
(brace
DECL|member|daddr
id|xfrm_address_t
id|daddr
suffix:semicolon
DECL|member|spi
id|__u32
id|spi
suffix:semicolon
DECL|member|family
id|__u16
id|family
suffix:semicolon
DECL|member|proto
id|__u8
id|proto
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_userspi_info
r_struct
id|xfrm_userspi_info
(brace
DECL|member|info
r_struct
id|xfrm_usersa_info
id|info
suffix:semicolon
DECL|member|min
id|__u32
id|min
suffix:semicolon
DECL|member|max
id|__u32
id|max
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_userpolicy_info
r_struct
id|xfrm_userpolicy_info
(brace
DECL|member|sel
r_struct
id|xfrm_selector
id|sel
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
DECL|member|priority
id|__u32
id|priority
suffix:semicolon
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|family
id|__u16
id|family
suffix:semicolon
DECL|member|dir
id|__u8
id|dir
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
DECL|member|share
id|__u8
id|share
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_userpolicy_id
r_struct
id|xfrm_userpolicy_id
(brace
DECL|member|sel
r_struct
id|xfrm_selector
id|sel
suffix:semicolon
DECL|member|index
id|__u32
id|index
suffix:semicolon
DECL|member|dir
id|__u8
id|dir
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_user_acquire
r_struct
id|xfrm_user_acquire
(brace
DECL|member|id
r_struct
id|xfrm_id
id|id
suffix:semicolon
DECL|member|saddr
id|xfrm_address_t
id|saddr
suffix:semicolon
DECL|member|sel
r_struct
id|xfrm_selector
id|sel
suffix:semicolon
DECL|member|policy
r_struct
id|xfrm_userpolicy_info
id|policy
suffix:semicolon
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
DECL|member|seq
id|__u32
id|seq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_user_expire
r_struct
id|xfrm_user_expire
(brace
DECL|member|state
r_struct
id|xfrm_usersa_info
id|state
suffix:semicolon
DECL|member|hard
id|__u8
id|hard
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|xfrm_user_polexpire
r_struct
id|xfrm_user_polexpire
(brace
DECL|member|pol
r_struct
id|xfrm_userpolicy_info
id|pol
suffix:semicolon
DECL|member|hard
id|__u8
id|hard
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|XFRMGRP_ACQUIRE
mdefine_line|#define XFRMGRP_ACQUIRE&t;&t;1
DECL|macro|XFRMGRP_EXPIRE
mdefine_line|#define XFRMGRP_EXPIRE&t;&t;2
macro_line|#endif /* _LINUX_XFRM_H */
eof
