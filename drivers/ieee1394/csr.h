macro_line|#ifndef _IEEE1394_CSR_H
DECL|macro|_IEEE1394_CSR_H
mdefine_line|#define _IEEE1394_CSR_H
DECL|macro|CSR_REGISTER_BASE
mdefine_line|#define CSR_REGISTER_BASE  0xfffff0000000ULL
multiline_comment|/* register offsets relative to CSR_REGISTER_BASE */
DECL|macro|CSR_STATE_CLEAR
mdefine_line|#define CSR_STATE_CLEAR           0x0
DECL|macro|CSR_STATE_SET
mdefine_line|#define CSR_STATE_SET             0x4
DECL|macro|CSR_NODE_IDS
mdefine_line|#define CSR_NODE_IDS              0x8
DECL|macro|CSR_RESET_START
mdefine_line|#define CSR_RESET_START           0xc
DECL|macro|CSR_SPLIT_TIMEOUT_HI
mdefine_line|#define CSR_SPLIT_TIMEOUT_HI      0x18
DECL|macro|CSR_SPLIT_TIMEOUT_LO
mdefine_line|#define CSR_SPLIT_TIMEOUT_LO      0x1c
DECL|macro|CSR_CYCLE_TIME
mdefine_line|#define CSR_CYCLE_TIME            0x200
DECL|macro|CSR_BUS_TIME
mdefine_line|#define CSR_BUS_TIME              0x204
DECL|macro|CSR_BUSY_TIMEOUT
mdefine_line|#define CSR_BUSY_TIMEOUT          0x210
DECL|macro|CSR_BUS_MANAGER_ID
mdefine_line|#define CSR_BUS_MANAGER_ID        0x21c
DECL|macro|CSR_BANDWIDTH_AVAILABLE
mdefine_line|#define CSR_BANDWIDTH_AVAILABLE   0x220
DECL|macro|CSR_CHANNELS_AVAILABLE_HI
mdefine_line|#define CSR_CHANNELS_AVAILABLE_HI 0x224
DECL|macro|CSR_CHANNELS_AVAILABLE_LO
mdefine_line|#define CSR_CHANNELS_AVAILABLE_LO 0x228
DECL|macro|CSR_CONFIG_ROM
mdefine_line|#define CSR_CONFIG_ROM            0x400
DECL|macro|CSR_CONFIG_ROM_END
mdefine_line|#define CSR_CONFIG_ROM_END        0x800
DECL|macro|CSR_FCP_COMMAND
mdefine_line|#define CSR_FCP_COMMAND           0xB00
DECL|macro|CSR_FCP_RESPONSE
mdefine_line|#define CSR_FCP_RESPONSE          0xD00
DECL|macro|CSR_FCP_END
mdefine_line|#define CSR_FCP_END               0xF00
DECL|macro|CSR_TOPOLOGY_MAP
mdefine_line|#define CSR_TOPOLOGY_MAP          0x1000
DECL|macro|CSR_TOPOLOGY_MAP_END
mdefine_line|#define CSR_TOPOLOGY_MAP_END      0x1400
DECL|macro|CSR_SPEED_MAP
mdefine_line|#define CSR_SPEED_MAP             0x2000
DECL|macro|CSR_SPEED_MAP_END
mdefine_line|#define CSR_SPEED_MAP_END         0x3000
DECL|struct|csr_control
r_struct
id|csr_control
(brace
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|state
id|quadlet_t
id|state
suffix:semicolon
DECL|member|node_ids
id|quadlet_t
id|node_ids
suffix:semicolon
DECL|member|split_timeout_hi
DECL|member|split_timeout_lo
id|quadlet_t
id|split_timeout_hi
comma
id|split_timeout_lo
suffix:semicolon
DECL|member|cycle_time
id|quadlet_t
id|cycle_time
suffix:semicolon
DECL|member|bus_time
id|quadlet_t
id|bus_time
suffix:semicolon
DECL|member|bus_manager_id
id|quadlet_t
id|bus_manager_id
suffix:semicolon
DECL|member|bandwidth_available
id|quadlet_t
id|bandwidth_available
suffix:semicolon
DECL|member|channels_available_hi
DECL|member|channels_available_lo
id|quadlet_t
id|channels_available_hi
comma
id|channels_available_lo
suffix:semicolon
DECL|member|rom
r_const
id|quadlet_t
op_star
id|rom
suffix:semicolon
DECL|member|rom_size
r_int
id|rom_size
suffix:semicolon
DECL|member|topology_map
id|quadlet_t
id|topology_map
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|speed_map
id|quadlet_t
id|speed_map
(braket
l_int|1024
)braket
suffix:semicolon
)brace
suffix:semicolon
r_void
id|init_csr
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _IEEE1394_CSR_H */
eof
