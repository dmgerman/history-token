macro_line|#ifndef __ALPHA_GCT_H
DECL|macro|__ALPHA_GCT_H
mdefine_line|#define __ALPHA_GCT_H
DECL|typedef|gct_id
r_typedef
id|u64
id|gct_id
suffix:semicolon
DECL|typedef|gct6_handle
r_typedef
id|u64
id|gct6_handle
suffix:semicolon
DECL|struct|__gct6_node
r_typedef
r_struct
id|__gct6_node
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|subtype
id|u8
id|subtype
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|hd_extension
id|u32
id|hd_extension
suffix:semicolon
DECL|member|owner
id|gct6_handle
id|owner
suffix:semicolon
DECL|member|active_user
id|gct6_handle
id|active_user
suffix:semicolon
DECL|member|id
id|gct_id
id|id
suffix:semicolon
DECL|member|flags
id|u64
id|flags
suffix:semicolon
DECL|member|rev
id|u16
id|rev
suffix:semicolon
DECL|member|change_counter
id|u16
id|change_counter
suffix:semicolon
DECL|member|max_child
id|u16
id|max_child
suffix:semicolon
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|saved_owner
id|gct6_handle
id|saved_owner
suffix:semicolon
DECL|member|affinity
id|gct6_handle
id|affinity
suffix:semicolon
DECL|member|parent
id|gct6_handle
id|parent
suffix:semicolon
DECL|member|next
id|gct6_handle
id|next
suffix:semicolon
DECL|member|prev
id|gct6_handle
id|prev
suffix:semicolon
DECL|member|child
id|gct6_handle
id|child
suffix:semicolon
DECL|member|fw_flags
id|u64
id|fw_flags
suffix:semicolon
DECL|member|os_usage
id|u64
id|os_usage
suffix:semicolon
DECL|member|fru_id
id|u64
id|fru_id
suffix:semicolon
DECL|member|checksum
id|u32
id|checksum
suffix:semicolon
DECL|member|magic
id|u32
id|magic
suffix:semicolon
multiline_comment|/* &squot;GLXY&squot; */
DECL|typedef|gct6_node
)brace
id|gct6_node
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|subtype
id|u8
id|subtype
suffix:semicolon
DECL|member|callout
r_void
(paren
op_star
id|callout
)paren
(paren
id|gct6_node
op_star
)paren
suffix:semicolon
DECL|typedef|gct6_search_struct
)brace
id|gct6_search_struct
suffix:semicolon
DECL|macro|GCT_NODE_MAGIC
mdefine_line|#define GCT_NODE_MAGIC&t;  0x59584c47&t;/* &squot;GLXY&squot; */
multiline_comment|/* &n; * node types &n; */
DECL|macro|GCT_TYPE_HOSE
mdefine_line|#define GCT_TYPE_HOSE&t;&t;&t;0x0E
multiline_comment|/*&n; * node subtypes&n; */
DECL|macro|GCT_SUBTYPE_IO_PORT_MODULE
mdefine_line|#define GCT_SUBTYPE_IO_PORT_MODULE&t;0x2C
DECL|macro|GCT_NODE_PTR
mdefine_line|#define GCT_NODE_PTR(off) ((gct6_node *)((char *)hwrpb + &t;&t;&bslash;&n;&t;&t;&t;&t;&t; hwrpb-&gt;frut_offset + &t;&t;&bslash;&n;&t;&t;&t;&t;&t; (gct6_handle)(off)))&t;&t;&bslash;&n;
r_int
id|gct6_find_nodes
c_func
(paren
id|gct6_node
op_star
comma
id|gct6_search_struct
op_star
)paren
suffix:semicolon
macro_line|#endif /* __ALPHA_GCT_H */
eof
