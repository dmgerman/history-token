macro_line|#ifndef _IEEE1394_CSR_H
DECL|macro|_IEEE1394_CSR_H
mdefine_line|#define _IEEE1394_CSR_H
macro_line|#ifdef CONFIG_PREEMPT
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#endif
macro_line|#include &quot;csr1212.h&quot;
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
DECL|macro|CSR_CHANNELS_AVAILABLE
mdefine_line|#define CSR_CHANNELS_AVAILABLE    0x224
DECL|macro|CSR_CHANNELS_AVAILABLE_HI
mdefine_line|#define CSR_CHANNELS_AVAILABLE_HI 0x224
DECL|macro|CSR_CHANNELS_AVAILABLE_LO
mdefine_line|#define CSR_CHANNELS_AVAILABLE_LO 0x228
DECL|macro|CSR_BROADCAST_CHANNEL
mdefine_line|#define CSR_BROADCAST_CHANNEL     0x234
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
multiline_comment|/* IEEE 1394 bus specific Configuration ROM Key IDs */
DECL|macro|IEEE1394_KV_ID_POWER_REQUIREMENTS
mdefine_line|#define IEEE1394_KV_ID_POWER_REQUIREMENTS (0x30)
multiline_comment|/* IEEE 1394 Bus Inforamation Block specifics */
DECL|macro|CSR_BUS_INFO_SIZE
mdefine_line|#define CSR_BUS_INFO_SIZE (5 * sizeof(quadlet_t))
DECL|macro|CSR_IRMC_SHIFT
mdefine_line|#define CSR_IRMC_SHIFT 31
DECL|macro|CSR_CMC_SHIFT
mdefine_line|#define CSR_CMC_SHIFT  30
DECL|macro|CSR_ISC_SHIFT
mdefine_line|#define CSR_ISC_SHIFT  29
DECL|macro|CSR_BMC_SHIFT
mdefine_line|#define CSR_BMC_SHIFT  28
DECL|macro|CSR_PMC_SHIFT
mdefine_line|#define CSR_PMC_SHIFT  27
DECL|macro|CSR_CYC_CLK_ACC_SHIFT
mdefine_line|#define CSR_CYC_CLK_ACC_SHIFT 16
DECL|macro|CSR_MAX_REC_SHIFT
mdefine_line|#define CSR_MAX_REC_SHIFT 12
DECL|macro|CSR_MAX_ROM_SHIFT
mdefine_line|#define CSR_MAX_ROM_SHIFT 8
DECL|macro|CSR_GENERATION_SHIFT
mdefine_line|#define CSR_GENERATION_SHIFT 4
DECL|macro|CSR_SET_BUS_INFO_GENERATION
mdefine_line|#define CSR_SET_BUS_INFO_GENERATION(csr, gen)&t;&t;&t;&t;&bslash;&n;&t;((csr)-&gt;bus_info_data[2] =&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_to_be32((be32_to_cpu((csr)-&gt;bus_info_data[2]) &amp;&t;&bslash;&n;&t;&t;&t;     ~(0xf &lt;&lt; CSR_GENERATION_SHIFT)) |          &bslash;&n;&t;&t;&t;    (gen) &lt;&lt; CSR_GENERATION_SHIFT))
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
DECL|member|expire
r_int
r_int
id|expire
suffix:semicolon
singleline_comment|// Calculated from split_timeout
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
DECL|member|broadcast_channel
id|quadlet_t
id|broadcast_channel
suffix:semicolon
multiline_comment|/* Bus Info */
DECL|member|guid_hi
DECL|member|guid_lo
id|quadlet_t
id|guid_hi
comma
id|guid_lo
suffix:semicolon
DECL|member|cyc_clk_acc
id|u8
id|cyc_clk_acc
suffix:semicolon
DECL|member|max_rec
id|u8
id|max_rec
suffix:semicolon
DECL|member|max_rom
id|u8
id|max_rom
suffix:semicolon
DECL|member|generation
id|u8
id|generation
suffix:semicolon
multiline_comment|/* Only use values between 0x2 and 0xf */
DECL|member|lnk_spd
id|u8
id|lnk_spd
suffix:semicolon
DECL|member|gen_timestamp
r_int
r_int
id|gen_timestamp
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|rom
r_struct
id|csr1212_csr
op_star
id|rom
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
r_extern
r_struct
id|csr1212_bus_ops
id|csr_bus_ops
suffix:semicolon
r_int
id|init_csr
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cleanup_csr
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _IEEE1394_CSR_H */
eof
