multiline_comment|/* This file is automatically generated.  Do not edit. */
multiline_comment|/* FLASK */
DECL|struct|av_inherit
r_struct
id|av_inherit
(brace
DECL|member|tclass
id|u16
id|tclass
suffix:semicolon
DECL|member|common_pts
r_char
op_star
op_star
id|common_pts
suffix:semicolon
DECL|member|common_base
id|u32
id|common_base
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|av_inherit
r_static
r_struct
id|av_inherit
id|av_inherit
(braket
)braket
op_assign
(brace
(brace
id|SECCLASS_DIR
comma
id|common_file_perm_to_string
comma
l_int|0x00020000UL
)brace
comma
(brace
id|SECCLASS_FILE
comma
id|common_file_perm_to_string
comma
l_int|0x00020000UL
)brace
comma
(brace
id|SECCLASS_LNK_FILE
comma
id|common_file_perm_to_string
comma
l_int|0x00020000UL
)brace
comma
(brace
id|SECCLASS_CHR_FILE
comma
id|common_file_perm_to_string
comma
l_int|0x00020000UL
)brace
comma
(brace
id|SECCLASS_BLK_FILE
comma
id|common_file_perm_to_string
comma
l_int|0x00020000UL
)brace
comma
(brace
id|SECCLASS_SOCK_FILE
comma
id|common_file_perm_to_string
comma
l_int|0x00020000UL
)brace
comma
(brace
id|SECCLASS_FIFO_FILE
comma
id|common_file_perm_to_string
comma
l_int|0x00020000UL
)brace
comma
(brace
id|SECCLASS_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_TCP_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_UDP_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_RAWIP_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_NETLINK_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_PACKET_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_KEY_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_UNIX_STREAM_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_UNIX_DGRAM_SOCKET
comma
id|common_socket_perm_to_string
comma
l_int|0x00400000UL
)brace
comma
(brace
id|SECCLASS_IPC
comma
id|common_ipc_perm_to_string
comma
l_int|0x00000200UL
)brace
comma
(brace
id|SECCLASS_SEM
comma
id|common_ipc_perm_to_string
comma
l_int|0x00000200UL
)brace
comma
(brace
id|SECCLASS_MSGQ
comma
id|common_ipc_perm_to_string
comma
l_int|0x00000200UL
)brace
comma
(brace
id|SECCLASS_SHM
comma
id|common_ipc_perm_to_string
comma
l_int|0x00000200UL
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* FLASK */
eof
