multiline_comment|/*&n; *&t;3COM &quot;EtherLink MC/32&quot; Descriptions&n; */
multiline_comment|/*&n; *&t;Registers&n; */
DECL|macro|HOST_CMD
mdefine_line|#define HOST_CMD&t;&t;0
DECL|macro|HOST_STATUS
mdefine_line|#define HOST_STATUS&t;&t;2
DECL|macro|HOST_STATUS_CRR
mdefine_line|#define&t;&t;HOST_STATUS_CRR&t;(1&lt;&lt;6)
DECL|macro|HOST_STATUS_CWR
mdefine_line|#define&t;&t;HOST_STATUS_CWR&t;(1&lt;&lt;5)
DECL|macro|HOST_CTRL
mdefine_line|#define HOST_CTRL&t;&t;6
DECL|macro|HOST_CTRL_ATTN
mdefine_line|#define&t;&t;HOST_CTRL_ATTN&t;(1&lt;&lt;7)
DECL|macro|HOST_CTRL_RESET
mdefine_line|#define &t;HOST_CTRL_RESET&t;(1&lt;&lt;6)
DECL|macro|HOST_CTRL_INTE
mdefine_line|#define &t;HOST_CTRL_INTE&t;(1&lt;&lt;2)
DECL|macro|HOST_RAMPAGE
mdefine_line|#define HOST_RAMPAGE&t;&t;8
DECL|struct|skb_header
r_struct
id|skb_header
(brace
id|u8
id|status
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u8
id|control
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u16
id|next
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Do not change! */
id|u16
id|length
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
id|u32
id|data
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|STATUS_MASK
mdefine_line|#define STATUS_MASK&t;0x0F
DECL|macro|COMPLETED
mdefine_line|#define COMPLETED&t;0x80
DECL|macro|COMPLETED_OK
mdefine_line|#define COMPLETED_OK&t;0x40
DECL|macro|BUFFER_BUSY
mdefine_line|#define BUFFER_BUSY&t;0x20
DECL|macro|CONTROL_EOP
mdefine_line|#define CONTROL_EOP&t;0x80&t;/* End Of Packet */
DECL|macro|CONTROL_EL
mdefine_line|#define CONTROL_EL&t;0x40&t;/* End of List */
DECL|macro|MCA_MC32_ID
mdefine_line|#define MCA_MC32_ID&t;0x0041&t;/* Our MCA ident */
eof
