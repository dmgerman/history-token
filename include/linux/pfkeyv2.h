multiline_comment|/* PF_KEY user interface, this is defined by rfc2367 so&n; * do not make arbitrary modifications or else this header&n; * file will not be compliant.&n; */
macro_line|#ifndef _LINUX_PFKEY2_H
DECL|macro|_LINUX_PFKEY2_H
mdefine_line|#define _LINUX_PFKEY2_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|PF_KEY_V2
mdefine_line|#define PF_KEY_V2&t;&t;2
DECL|macro|PFKEYV2_REVISION
mdefine_line|#define PFKEYV2_REVISION&t;199806L
DECL|struct|sadb_msg
r_struct
id|sadb_msg
(brace
DECL|member|sadb_msg_version
r_uint8
id|sadb_msg_version
suffix:semicolon
DECL|member|sadb_msg_type
r_uint8
id|sadb_msg_type
suffix:semicolon
DECL|member|sadb_msg_errno
r_uint8
id|sadb_msg_errno
suffix:semicolon
DECL|member|sadb_msg_satype
r_uint8
id|sadb_msg_satype
suffix:semicolon
DECL|member|sadb_msg_len
r_uint16
id|sadb_msg_len
suffix:semicolon
DECL|member|sadb_msg_reserved
r_uint16
id|sadb_msg_reserved
suffix:semicolon
DECL|member|sadb_msg_seq
r_uint32
id|sadb_msg_seq
suffix:semicolon
DECL|member|sadb_msg_pid
r_uint32
id|sadb_msg_pid
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_msg) == 16 */
DECL|struct|sadb_ext
r_struct
id|sadb_ext
(brace
DECL|member|sadb_ext_len
r_uint16
id|sadb_ext_len
suffix:semicolon
DECL|member|sadb_ext_type
r_uint16
id|sadb_ext_type
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_ext) == 4 */
DECL|struct|sadb_sa
r_struct
id|sadb_sa
(brace
DECL|member|sadb_sa_len
r_uint16
id|sadb_sa_len
suffix:semicolon
DECL|member|sadb_sa_exttype
r_uint16
id|sadb_sa_exttype
suffix:semicolon
DECL|member|sadb_sa_spi
r_uint32
id|sadb_sa_spi
suffix:semicolon
DECL|member|sadb_sa_replay
r_uint8
id|sadb_sa_replay
suffix:semicolon
DECL|member|sadb_sa_state
r_uint8
id|sadb_sa_state
suffix:semicolon
DECL|member|sadb_sa_auth
r_uint8
id|sadb_sa_auth
suffix:semicolon
DECL|member|sadb_sa_encrypt
r_uint8
id|sadb_sa_encrypt
suffix:semicolon
DECL|member|sadb_sa_flags
r_uint32
id|sadb_sa_flags
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_sa) == 16 */
DECL|struct|sadb_lifetime
r_struct
id|sadb_lifetime
(brace
DECL|member|sadb_lifetime_len
r_uint16
id|sadb_lifetime_len
suffix:semicolon
DECL|member|sadb_lifetime_exttype
r_uint16
id|sadb_lifetime_exttype
suffix:semicolon
DECL|member|sadb_lifetime_allocations
r_uint32
id|sadb_lifetime_allocations
suffix:semicolon
DECL|member|sadb_lifetime_bytes
r_uint64
id|sadb_lifetime_bytes
suffix:semicolon
DECL|member|sadb_lifetime_addtime
r_uint64
id|sadb_lifetime_addtime
suffix:semicolon
DECL|member|sadb_lifetime_usetime
r_uint64
id|sadb_lifetime_usetime
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_lifetime) == 32 */
DECL|struct|sadb_address
r_struct
id|sadb_address
(brace
DECL|member|sadb_address_len
r_uint16
id|sadb_address_len
suffix:semicolon
DECL|member|sadb_address_exttype
r_uint16
id|sadb_address_exttype
suffix:semicolon
DECL|member|sadb_address_proto
r_uint8
id|sadb_address_proto
suffix:semicolon
DECL|member|sadb_address_prefixlen
r_uint8
id|sadb_address_prefixlen
suffix:semicolon
DECL|member|sadb_address_reserved
r_uint16
id|sadb_address_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_address) == 8 */
DECL|struct|sadb_key
r_struct
id|sadb_key
(brace
DECL|member|sadb_key_len
r_uint16
id|sadb_key_len
suffix:semicolon
DECL|member|sadb_key_exttype
r_uint16
id|sadb_key_exttype
suffix:semicolon
DECL|member|sadb_key_bits
r_uint16
id|sadb_key_bits
suffix:semicolon
DECL|member|sadb_key_reserved
r_uint16
id|sadb_key_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_key) == 8 */
DECL|struct|sadb_ident
r_struct
id|sadb_ident
(brace
DECL|member|sadb_ident_len
r_uint16
id|sadb_ident_len
suffix:semicolon
DECL|member|sadb_ident_exttype
r_uint16
id|sadb_ident_exttype
suffix:semicolon
DECL|member|sadb_ident_type
r_uint16
id|sadb_ident_type
suffix:semicolon
DECL|member|sadb_ident_reserved
r_uint16
id|sadb_ident_reserved
suffix:semicolon
DECL|member|sadb_ident_id
r_uint64
id|sadb_ident_id
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_ident) == 16 */
DECL|struct|sadb_sens
r_struct
id|sadb_sens
(brace
DECL|member|sadb_sens_len
r_uint16
id|sadb_sens_len
suffix:semicolon
DECL|member|sadb_sens_exttype
r_uint16
id|sadb_sens_exttype
suffix:semicolon
DECL|member|sadb_sens_dpd
r_uint32
id|sadb_sens_dpd
suffix:semicolon
DECL|member|sadb_sens_sens_level
r_uint8
id|sadb_sens_sens_level
suffix:semicolon
DECL|member|sadb_sens_sens_len
r_uint8
id|sadb_sens_sens_len
suffix:semicolon
DECL|member|sadb_sens_integ_level
r_uint8
id|sadb_sens_integ_level
suffix:semicolon
DECL|member|sadb_sens_integ_len
r_uint8
id|sadb_sens_integ_len
suffix:semicolon
DECL|member|sadb_sens_reserved
r_uint32
id|sadb_sens_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_sens) == 16 */
multiline_comment|/* followed by:&n;&t;uint64_t&t;sadb_sens_bitmap[sens_len];&n;&t;uint64_t&t;sadb_integ_bitmap[integ_len];  */
DECL|struct|sadb_prop
r_struct
id|sadb_prop
(brace
DECL|member|sadb_prop_len
r_uint16
id|sadb_prop_len
suffix:semicolon
DECL|member|sadb_prop_exttype
r_uint16
id|sadb_prop_exttype
suffix:semicolon
DECL|member|sadb_prop_replay
r_uint8
id|sadb_prop_replay
suffix:semicolon
DECL|member|sadb_prop_reserved
r_uint8
id|sadb_prop_reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_prop) == 8 */
multiline_comment|/* followed by:&n;&t;struct sadb_comb sadb_combs[(sadb_prop_len +&n;&t;&t;sizeof(uint64_t) - sizeof(struct sadb_prop)) /&n;&t;&t;sizeof(strut sadb_comb)]; */
DECL|struct|sadb_comb
r_struct
id|sadb_comb
(brace
DECL|member|sadb_comb_auth
r_uint8
id|sadb_comb_auth
suffix:semicolon
DECL|member|sadb_comb_encrypt
r_uint8
id|sadb_comb_encrypt
suffix:semicolon
DECL|member|sadb_comb_flags
r_uint16
id|sadb_comb_flags
suffix:semicolon
DECL|member|sadb_comb_auth_minbits
r_uint16
id|sadb_comb_auth_minbits
suffix:semicolon
DECL|member|sadb_comb_auth_maxbits
r_uint16
id|sadb_comb_auth_maxbits
suffix:semicolon
DECL|member|sadb_comb_encrypt_minbits
r_uint16
id|sadb_comb_encrypt_minbits
suffix:semicolon
DECL|member|sadb_comb_encrypt_maxbits
r_uint16
id|sadb_comb_encrypt_maxbits
suffix:semicolon
DECL|member|sadb_comb_reserved
r_uint32
id|sadb_comb_reserved
suffix:semicolon
DECL|member|sadb_comb_soft_allocations
r_uint32
id|sadb_comb_soft_allocations
suffix:semicolon
DECL|member|sadb_comb_hard_allocations
r_uint32
id|sadb_comb_hard_allocations
suffix:semicolon
DECL|member|sadb_comb_soft_bytes
r_uint64
id|sadb_comb_soft_bytes
suffix:semicolon
DECL|member|sadb_comb_hard_bytes
r_uint64
id|sadb_comb_hard_bytes
suffix:semicolon
DECL|member|sadb_comb_soft_addtime
r_uint64
id|sadb_comb_soft_addtime
suffix:semicolon
DECL|member|sadb_comb_hard_addtime
r_uint64
id|sadb_comb_hard_addtime
suffix:semicolon
DECL|member|sadb_comb_soft_usetime
r_uint64
id|sadb_comb_soft_usetime
suffix:semicolon
DECL|member|sadb_comb_hard_usetime
r_uint64
id|sadb_comb_hard_usetime
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_comb) == 72 */
DECL|struct|sadb_supported
r_struct
id|sadb_supported
(brace
DECL|member|sadb_supported_len
r_uint16
id|sadb_supported_len
suffix:semicolon
DECL|member|sadb_supported_exttype
r_uint16
id|sadb_supported_exttype
suffix:semicolon
DECL|member|sadb_supported_reserved
r_uint32
id|sadb_supported_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_supported) == 8 */
multiline_comment|/* followed by:&n;&t;struct sadb_alg sadb_algs[(sadb_supported_len +&n;&t;&t;sizeof(uint64_t) - sizeof(struct sadb_supported)) /&n;&t;&t;sizeof(struct sadb_alg)]; */
DECL|struct|sadb_alg
r_struct
id|sadb_alg
(brace
DECL|member|sadb_alg_id
r_uint8
id|sadb_alg_id
suffix:semicolon
DECL|member|sadb_alg_ivlen
r_uint8
id|sadb_alg_ivlen
suffix:semicolon
DECL|member|sadb_alg_minbits
r_uint16
id|sadb_alg_minbits
suffix:semicolon
DECL|member|sadb_alg_maxbits
r_uint16
id|sadb_alg_maxbits
suffix:semicolon
DECL|member|sadb_alg_reserved
r_uint16
id|sadb_alg_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_alg) == 8 */
DECL|struct|sadb_spirange
r_struct
id|sadb_spirange
(brace
DECL|member|sadb_spirange_len
r_uint16
id|sadb_spirange_len
suffix:semicolon
DECL|member|sadb_spirange_exttype
r_uint16
id|sadb_spirange_exttype
suffix:semicolon
DECL|member|sadb_spirange_min
r_uint32
id|sadb_spirange_min
suffix:semicolon
DECL|member|sadb_spirange_max
r_uint32
id|sadb_spirange_max
suffix:semicolon
DECL|member|sadb_spirange_reserved
r_uint32
id|sadb_spirange_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_spirange) == 16 */
DECL|struct|sadb_x_kmprivate
r_struct
id|sadb_x_kmprivate
(brace
DECL|member|sadb_x_kmprivate_len
r_uint16
id|sadb_x_kmprivate_len
suffix:semicolon
DECL|member|sadb_x_kmprivate_exttype
r_uint16
id|sadb_x_kmprivate_exttype
suffix:semicolon
DECL|member|sadb_x_kmprivate_reserved
id|u_int32_t
id|sadb_x_kmprivate_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_x_kmprivate) == 8 */
DECL|struct|sadb_x_sa2
r_struct
id|sadb_x_sa2
(brace
DECL|member|sadb_x_sa2_len
r_uint16
id|sadb_x_sa2_len
suffix:semicolon
DECL|member|sadb_x_sa2_exttype
r_uint16
id|sadb_x_sa2_exttype
suffix:semicolon
DECL|member|sadb_x_sa2_mode
r_uint8
id|sadb_x_sa2_mode
suffix:semicolon
DECL|member|sadb_x_sa2_reserved1
r_uint8
id|sadb_x_sa2_reserved1
suffix:semicolon
DECL|member|sadb_x_sa2_reserved2
r_uint16
id|sadb_x_sa2_reserved2
suffix:semicolon
DECL|member|sadb_x_sa2_sequence
r_uint32
id|sadb_x_sa2_sequence
suffix:semicolon
DECL|member|sadb_x_sa2_reqid
r_uint32
id|sadb_x_sa2_reqid
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_x_sa2) == 16 */
DECL|struct|sadb_x_policy
r_struct
id|sadb_x_policy
(brace
DECL|member|sadb_x_policy_len
r_uint16
id|sadb_x_policy_len
suffix:semicolon
DECL|member|sadb_x_policy_exttype
r_uint16
id|sadb_x_policy_exttype
suffix:semicolon
DECL|member|sadb_x_policy_type
r_uint16
id|sadb_x_policy_type
suffix:semicolon
DECL|member|sadb_x_policy_dir
r_uint8
id|sadb_x_policy_dir
suffix:semicolon
DECL|member|sadb_x_policy_reserved
r_uint8
id|sadb_x_policy_reserved
suffix:semicolon
DECL|member|sadb_x_policy_id
r_uint32
id|sadb_x_policy_id
suffix:semicolon
DECL|member|sadb_x_policy_reserved2
r_uint32
id|sadb_x_policy_reserved2
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_x_policy) == 16 */
DECL|struct|sadb_x_ipsecrequest
r_struct
id|sadb_x_ipsecrequest
(brace
DECL|member|sadb_x_ipsecrequest_len
r_uint16
id|sadb_x_ipsecrequest_len
suffix:semicolon
DECL|member|sadb_x_ipsecrequest_proto
r_uint16
id|sadb_x_ipsecrequest_proto
suffix:semicolon
DECL|member|sadb_x_ipsecrequest_mode
r_uint8
id|sadb_x_ipsecrequest_mode
suffix:semicolon
DECL|member|sadb_x_ipsecrequest_level
r_uint8
id|sadb_x_ipsecrequest_level
suffix:semicolon
DECL|member|sadb_x_ipsecrequest_reserved1
r_uint16
id|sadb_x_ipsecrequest_reserved1
suffix:semicolon
DECL|member|sadb_x_ipsecrequest_reqid
r_uint32
id|sadb_x_ipsecrequest_reqid
suffix:semicolon
DECL|member|sadb_x_ipsecrequest_reserved2
r_uint32
id|sadb_x_ipsecrequest_reserved2
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_x_ipsecrequest) == 16 */
multiline_comment|/* This defines the TYPE of Nat Traversal in use.  Currently only one&n; * type of NAT-T is supported, draft-ietf-ipsec-udp-encaps-06&n; */
DECL|struct|sadb_x_nat_t_type
r_struct
id|sadb_x_nat_t_type
(brace
DECL|member|sadb_x_nat_t_type_len
r_uint16
id|sadb_x_nat_t_type_len
suffix:semicolon
DECL|member|sadb_x_nat_t_type_exttype
r_uint16
id|sadb_x_nat_t_type_exttype
suffix:semicolon
DECL|member|sadb_x_nat_t_type_type
r_uint8
id|sadb_x_nat_t_type_type
suffix:semicolon
DECL|member|sadb_x_nat_t_type_reserved
r_uint8
id|sadb_x_nat_t_type_reserved
(braket
l_int|3
)braket
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_x_nat_t_type) == 8 */
multiline_comment|/* Pass a NAT Traversal port (Source or Dest port) */
DECL|struct|sadb_x_nat_t_port
r_struct
id|sadb_x_nat_t_port
(brace
DECL|member|sadb_x_nat_t_port_len
r_uint16
id|sadb_x_nat_t_port_len
suffix:semicolon
DECL|member|sadb_x_nat_t_port_exttype
r_uint16
id|sadb_x_nat_t_port_exttype
suffix:semicolon
DECL|member|sadb_x_nat_t_port_port
r_uint16
id|sadb_x_nat_t_port_port
suffix:semicolon
DECL|member|sadb_x_nat_t_port_reserved
r_uint16
id|sadb_x_nat_t_port_reserved
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* sizeof(struct sadb_x_nat_t_port) == 8 */
multiline_comment|/* Message types */
DECL|macro|SADB_RESERVED
mdefine_line|#define SADB_RESERVED&t;&t;0
DECL|macro|SADB_GETSPI
mdefine_line|#define SADB_GETSPI&t;&t;1
DECL|macro|SADB_UPDATE
mdefine_line|#define SADB_UPDATE&t;&t;2
DECL|macro|SADB_ADD
mdefine_line|#define SADB_ADD&t;&t;3
DECL|macro|SADB_DELETE
mdefine_line|#define SADB_DELETE&t;&t;4
DECL|macro|SADB_GET
mdefine_line|#define SADB_GET&t;&t;5
DECL|macro|SADB_ACQUIRE
mdefine_line|#define SADB_ACQUIRE&t;&t;6
DECL|macro|SADB_REGISTER
mdefine_line|#define SADB_REGISTER&t;&t;7
DECL|macro|SADB_EXPIRE
mdefine_line|#define SADB_EXPIRE&t;&t;8
DECL|macro|SADB_FLUSH
mdefine_line|#define SADB_FLUSH&t;&t;9
DECL|macro|SADB_DUMP
mdefine_line|#define SADB_DUMP&t;&t;10
DECL|macro|SADB_X_PROMISC
mdefine_line|#define SADB_X_PROMISC&t;&t;11
DECL|macro|SADB_X_PCHANGE
mdefine_line|#define SADB_X_PCHANGE&t;&t;12
DECL|macro|SADB_X_SPDUPDATE
mdefine_line|#define SADB_X_SPDUPDATE&t;13
DECL|macro|SADB_X_SPDADD
mdefine_line|#define SADB_X_SPDADD&t;&t;14
DECL|macro|SADB_X_SPDDELETE
mdefine_line|#define SADB_X_SPDDELETE&t;15
DECL|macro|SADB_X_SPDGET
mdefine_line|#define SADB_X_SPDGET&t;&t;16
DECL|macro|SADB_X_SPDACQUIRE
mdefine_line|#define SADB_X_SPDACQUIRE&t;17
DECL|macro|SADB_X_SPDDUMP
mdefine_line|#define SADB_X_SPDDUMP&t;&t;18
DECL|macro|SADB_X_SPDFLUSH
mdefine_line|#define SADB_X_SPDFLUSH&t;&t;19
DECL|macro|SADB_X_SPDSETIDX
mdefine_line|#define SADB_X_SPDSETIDX&t;20
DECL|macro|SADB_X_SPDEXPIRE
mdefine_line|#define SADB_X_SPDEXPIRE&t;21
DECL|macro|SADB_X_SPDDELETE2
mdefine_line|#define SADB_X_SPDDELETE2&t;22
DECL|macro|SADB_X_NAT_T_NEW_MAPPING
mdefine_line|#define SADB_X_NAT_T_NEW_MAPPING&t;23
DECL|macro|SADB_MAX
mdefine_line|#define SADB_MAX&t;&t;23
multiline_comment|/* Security Association flags */
DECL|macro|SADB_SAFLAGS_PFS
mdefine_line|#define SADB_SAFLAGS_PFS&t;1
DECL|macro|SADB_SAFLAGS_NOECN
mdefine_line|#define SADB_SAFLAGS_NOECN&t;0x80000000
multiline_comment|/* Security Association states */
DECL|macro|SADB_SASTATE_LARVAL
mdefine_line|#define SADB_SASTATE_LARVAL&t;0
DECL|macro|SADB_SASTATE_MATURE
mdefine_line|#define SADB_SASTATE_MATURE&t;1
DECL|macro|SADB_SASTATE_DYING
mdefine_line|#define SADB_SASTATE_DYING&t;2
DECL|macro|SADB_SASTATE_DEAD
mdefine_line|#define SADB_SASTATE_DEAD&t;3
DECL|macro|SADB_SASTATE_MAX
mdefine_line|#define SADB_SASTATE_MAX&t;3
multiline_comment|/* Security Association types */
DECL|macro|SADB_SATYPE_UNSPEC
mdefine_line|#define SADB_SATYPE_UNSPEC&t;0
DECL|macro|SADB_SATYPE_AH
mdefine_line|#define SADB_SATYPE_AH&t;&t;2
DECL|macro|SADB_SATYPE_ESP
mdefine_line|#define SADB_SATYPE_ESP&t;&t;3
DECL|macro|SADB_SATYPE_RSVP
mdefine_line|#define SADB_SATYPE_RSVP&t;5
DECL|macro|SADB_SATYPE_OSPFV2
mdefine_line|#define SADB_SATYPE_OSPFV2&t;6
DECL|macro|SADB_SATYPE_RIPV2
mdefine_line|#define SADB_SATYPE_RIPV2&t;7
DECL|macro|SADB_SATYPE_MIP
mdefine_line|#define SADB_SATYPE_MIP&t;&t;8
DECL|macro|SADB_X_SATYPE_IPCOMP
mdefine_line|#define SADB_X_SATYPE_IPCOMP&t;9
DECL|macro|SADB_SATYPE_MAX
mdefine_line|#define SADB_SATYPE_MAX&t;&t;9
multiline_comment|/* Authentication algorithms */
DECL|macro|SADB_AALG_NONE
mdefine_line|#define SADB_AALG_NONE&t;&t;&t;0
DECL|macro|SADB_AALG_MD5HMAC
mdefine_line|#define SADB_AALG_MD5HMAC&t;&t;2
DECL|macro|SADB_AALG_SHA1HMAC
mdefine_line|#define SADB_AALG_SHA1HMAC&t;&t;3
DECL|macro|SADB_X_AALG_SHA2_256HMAC
mdefine_line|#define SADB_X_AALG_SHA2_256HMAC&t;5
DECL|macro|SADB_X_AALG_SHA2_384HMAC
mdefine_line|#define SADB_X_AALG_SHA2_384HMAC&t;6
DECL|macro|SADB_X_AALG_SHA2_512HMAC
mdefine_line|#define SADB_X_AALG_SHA2_512HMAC&t;7
DECL|macro|SADB_X_AALG_RIPEMD160HMAC
mdefine_line|#define SADB_X_AALG_RIPEMD160HMAC&t;8
DECL|macro|SADB_X_AALG_NULL
mdefine_line|#define SADB_X_AALG_NULL&t;&t;251&t;/* kame */
DECL|macro|SADB_AALG_MAX
mdefine_line|#define SADB_AALG_MAX&t;&t;&t;251
multiline_comment|/* Encryption algorithms */
DECL|macro|SADB_EALG_NONE
mdefine_line|#define SADB_EALG_NONE&t;&t;&t;0
DECL|macro|SADB_EALG_DESCBC
mdefine_line|#define SADB_EALG_DESCBC&t;&t;2
DECL|macro|SADB_EALG_3DESCBC
mdefine_line|#define SADB_EALG_3DESCBC&t;&t;3
DECL|macro|SADB_X_EALG_CASTCBC
mdefine_line|#define SADB_X_EALG_CASTCBC&t;&t;6
DECL|macro|SADB_X_EALG_BLOWFISHCBC
mdefine_line|#define SADB_X_EALG_BLOWFISHCBC&t;&t;7
DECL|macro|SADB_EALG_NULL
mdefine_line|#define SADB_EALG_NULL&t;&t;&t;11
DECL|macro|SADB_X_EALG_AESCBC
mdefine_line|#define SADB_X_EALG_AESCBC&t;&t;12
DECL|macro|SADB_EALG_MAX
mdefine_line|#define SADB_EALG_MAX                   253 /* last EALG */
multiline_comment|/* private allocations should use 249-255 (RFC2407) */
DECL|macro|SADB_X_EALG_SERPENTCBC
mdefine_line|#define SADB_X_EALG_SERPENTCBC  252     /* draft-ietf-ipsec-ciph-aes-cbc-00 */
DECL|macro|SADB_X_EALG_TWOFISHCBC
mdefine_line|#define SADB_X_EALG_TWOFISHCBC  253     /* draft-ietf-ipsec-ciph-aes-cbc-00 */
multiline_comment|/* Compression algorithms */
DECL|macro|SADB_X_CALG_NONE
mdefine_line|#define SADB_X_CALG_NONE&t;&t;0
DECL|macro|SADB_X_CALG_OUI
mdefine_line|#define SADB_X_CALG_OUI&t;&t;&t;1
DECL|macro|SADB_X_CALG_DEFLATE
mdefine_line|#define SADB_X_CALG_DEFLATE&t;&t;2
DECL|macro|SADB_X_CALG_LZS
mdefine_line|#define SADB_X_CALG_LZS&t;&t;&t;3
DECL|macro|SADB_X_CALG_LZJH
mdefine_line|#define SADB_X_CALG_LZJH&t;&t;4
DECL|macro|SADB_X_CALG_MAX
mdefine_line|#define SADB_X_CALG_MAX&t;&t;&t;4
multiline_comment|/* Extension Header values */
DECL|macro|SADB_EXT_RESERVED
mdefine_line|#define SADB_EXT_RESERVED&t;&t;0
DECL|macro|SADB_EXT_SA
mdefine_line|#define SADB_EXT_SA&t;&t;&t;1
DECL|macro|SADB_EXT_LIFETIME_CURRENT
mdefine_line|#define SADB_EXT_LIFETIME_CURRENT&t;2
DECL|macro|SADB_EXT_LIFETIME_HARD
mdefine_line|#define SADB_EXT_LIFETIME_HARD&t;&t;3
DECL|macro|SADB_EXT_LIFETIME_SOFT
mdefine_line|#define SADB_EXT_LIFETIME_SOFT&t;&t;4
DECL|macro|SADB_EXT_ADDRESS_SRC
mdefine_line|#define SADB_EXT_ADDRESS_SRC&t;&t;5
DECL|macro|SADB_EXT_ADDRESS_DST
mdefine_line|#define SADB_EXT_ADDRESS_DST&t;&t;6
DECL|macro|SADB_EXT_ADDRESS_PROXY
mdefine_line|#define SADB_EXT_ADDRESS_PROXY&t;&t;7
DECL|macro|SADB_EXT_KEY_AUTH
mdefine_line|#define SADB_EXT_KEY_AUTH&t;&t;8
DECL|macro|SADB_EXT_KEY_ENCRYPT
mdefine_line|#define SADB_EXT_KEY_ENCRYPT&t;&t;9
DECL|macro|SADB_EXT_IDENTITY_SRC
mdefine_line|#define SADB_EXT_IDENTITY_SRC&t;&t;10
DECL|macro|SADB_EXT_IDENTITY_DST
mdefine_line|#define SADB_EXT_IDENTITY_DST&t;&t;11
DECL|macro|SADB_EXT_SENSITIVITY
mdefine_line|#define SADB_EXT_SENSITIVITY&t;&t;12
DECL|macro|SADB_EXT_PROPOSAL
mdefine_line|#define SADB_EXT_PROPOSAL&t;&t;13
DECL|macro|SADB_EXT_SUPPORTED_AUTH
mdefine_line|#define SADB_EXT_SUPPORTED_AUTH&t;&t;14
DECL|macro|SADB_EXT_SUPPORTED_ENCRYPT
mdefine_line|#define SADB_EXT_SUPPORTED_ENCRYPT&t;15
DECL|macro|SADB_EXT_SPIRANGE
mdefine_line|#define SADB_EXT_SPIRANGE&t;&t;16
DECL|macro|SADB_X_EXT_KMPRIVATE
mdefine_line|#define SADB_X_EXT_KMPRIVATE&t;&t;17
DECL|macro|SADB_X_EXT_POLICY
mdefine_line|#define SADB_X_EXT_POLICY&t;&t;18
DECL|macro|SADB_X_EXT_SA2
mdefine_line|#define SADB_X_EXT_SA2&t;&t;&t;19
multiline_comment|/* The next four entries are for setting up NAT Traversal */
DECL|macro|SADB_X_EXT_NAT_T_TYPE
mdefine_line|#define SADB_X_EXT_NAT_T_TYPE&t;&t;20
DECL|macro|SADB_X_EXT_NAT_T_SPORT
mdefine_line|#define SADB_X_EXT_NAT_T_SPORT&t;&t;21
DECL|macro|SADB_X_EXT_NAT_T_DPORT
mdefine_line|#define SADB_X_EXT_NAT_T_DPORT&t;&t;22
DECL|macro|SADB_X_EXT_NAT_T_OA
mdefine_line|#define SADB_X_EXT_NAT_T_OA&t;&t;23
DECL|macro|SADB_EXT_MAX
mdefine_line|#define SADB_EXT_MAX&t;&t;&t;23
multiline_comment|/* Identity Extension values */
DECL|macro|SADB_IDENTTYPE_RESERVED
mdefine_line|#define SADB_IDENTTYPE_RESERVED&t;0
DECL|macro|SADB_IDENTTYPE_PREFIX
mdefine_line|#define SADB_IDENTTYPE_PREFIX&t;1
DECL|macro|SADB_IDENTTYPE_FQDN
mdefine_line|#define SADB_IDENTTYPE_FQDN&t;2
DECL|macro|SADB_IDENTTYPE_USERFQDN
mdefine_line|#define SADB_IDENTTYPE_USERFQDN&t;3
DECL|macro|SADB_IDENTTYPE_MAX
mdefine_line|#define SADB_IDENTTYPE_MAX&t;3
macro_line|#endif /* !(_LINUX_PFKEY2_H) */
eof
