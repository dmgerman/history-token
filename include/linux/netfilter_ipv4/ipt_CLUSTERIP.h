macro_line|#ifndef _IPT_CLUSTERIP_H_target
DECL|macro|_IPT_CLUSTERIP_H_target
mdefine_line|#define _IPT_CLUSTERIP_H_target
DECL|enum|clusterip_hashmode
r_enum
id|clusterip_hashmode
(brace
DECL|enumerator|CLUSTERIP_HASHMODE_SIP
id|CLUSTERIP_HASHMODE_SIP
op_assign
l_int|0
comma
DECL|enumerator|CLUSTERIP_HASHMODE_SIP_SPT
id|CLUSTERIP_HASHMODE_SIP_SPT
comma
DECL|enumerator|CLUSTERIP_HASHMODE_SIP_SPT_DPT
id|CLUSTERIP_HASHMODE_SIP_SPT_DPT
comma
)brace
suffix:semicolon
DECL|macro|CLUSTERIP_HASHMODE_MAX
mdefine_line|#define CLUSTERIP_HASHMODE_MAX CLUSTERIP_HASHMODE_SIP_SPT_DPT
DECL|macro|CLUSTERIP_MAX_NODES
mdefine_line|#define CLUSTERIP_MAX_NODES 16
DECL|macro|CLUSTERIP_FLAG_NEW
mdefine_line|#define CLUSTERIP_FLAG_NEW 0x00000001
r_struct
id|clusterip_config
suffix:semicolon
DECL|struct|ipt_clusterip_tgt_info
r_struct
id|ipt_clusterip_tgt_info
(brace
DECL|member|flags
id|u_int32_t
id|flags
suffix:semicolon
DECL|member|config
r_struct
id|clusterip_config
op_star
id|config
suffix:semicolon
multiline_comment|/* only relevant for new ones */
DECL|member|clustermac
id|u_int8_t
id|clustermac
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|num_total_nodes
id|u_int16_t
id|num_total_nodes
suffix:semicolon
DECL|member|num_local_nodes
id|u_int16_t
id|num_local_nodes
suffix:semicolon
DECL|member|local_nodes
id|u_int16_t
id|local_nodes
(braket
id|CLUSTERIP_MAX_NODES
)braket
suffix:semicolon
DECL|member|hash_mode
r_enum
id|clusterip_hashmode
id|hash_mode
suffix:semicolon
DECL|member|hash_initval
id|u_int32_t
id|hash_initval
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /*_IPT_CLUSTERIP_H_target*/
eof
