multiline_comment|/*&n; * IEEE 1394 for Linux&n; *&n; * CSR implementation, iso/bus manager implementation.&n; *&n; * Copyright (C) 1999 Andreas E. Bombe&n; *               2002 Manfred Weihs &lt;weihs@ict.tuwien.ac.at&gt;&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; *&n; *&n; * Contributions:&n; *&n; * Manfred Weihs &lt;weihs@ict.tuwien.ac.at&gt;&n; *        configuration ROM manipulation&n; *&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/moduleparam.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &quot;ieee1394_types.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;ieee1394.h&quot;
macro_line|#include &quot;highlevel.h&quot;
multiline_comment|/* Module Parameters */
multiline_comment|/* this module parameter can be used to disable mapping of the FCP registers */
DECL|variable|fcp
r_static
r_int
id|fcp
op_assign
l_int|1
suffix:semicolon
id|module_param
c_func
(paren
id|fcp
comma
r_int
comma
l_int|0444
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|fcp
comma
l_string|&quot;Map FCP registers (default = 1, disable = 0).&quot;
)paren
suffix:semicolon
DECL|function|csr_crc16
r_static
id|u16
id|csr_crc16
c_func
(paren
r_int
op_star
id|data
comma
r_int
id|length
)paren
(brace
r_int
id|check
op_assign
l_int|0
comma
id|i
suffix:semicolon
r_int
id|shift
comma
id|sum
comma
id|next
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|length
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_for
c_loop
(paren
id|next
op_assign
id|check
comma
id|shift
op_assign
l_int|28
suffix:semicolon
id|shift
op_ge
l_int|0
suffix:semicolon
id|shift
op_sub_assign
l_int|4
)paren
(brace
id|sum
op_assign
(paren
(paren
id|next
op_rshift
l_int|12
)paren
op_xor
(paren
id|be32_to_cpu
c_func
(paren
op_star
id|data
)paren
op_rshift
id|shift
)paren
)paren
op_amp
l_int|0xf
suffix:semicolon
id|next
op_assign
(paren
id|next
op_lshift
l_int|4
)paren
op_xor
(paren
id|sum
op_lshift
l_int|12
)paren
op_xor
(paren
id|sum
op_lshift
l_int|5
)paren
op_xor
(paren
id|sum
)paren
suffix:semicolon
)brace
id|check
op_assign
id|next
op_amp
l_int|0xffff
suffix:semicolon
id|data
op_increment
suffix:semicolon
)brace
r_return
id|check
suffix:semicolon
)brace
DECL|function|host_reset
r_static
r_void
id|host_reset
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
id|host-&gt;csr.state
op_and_assign
l_int|0x300
suffix:semicolon
id|host-&gt;csr.bus_manager_id
op_assign
l_int|0x3f
suffix:semicolon
id|host-&gt;csr.bandwidth_available
op_assign
l_int|4915
suffix:semicolon
id|host-&gt;csr.channels_available_hi
op_assign
l_int|0xfffffffe
suffix:semicolon
multiline_comment|/* pre-alloc ch 31 per 1394a-2000 */
id|host-&gt;csr.channels_available_lo
op_assign
op_complement
l_int|0
suffix:semicolon
id|host-&gt;csr.broadcast_channel
op_assign
l_int|0x80000000
op_or
l_int|31
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;is_irm
)paren
(brace
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
(brace
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
l_int|2
comma
l_int|0xfffffffe
comma
op_complement
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|host-&gt;csr.node_ids
op_assign
id|host-&gt;node_id
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;is_root
)paren
(brace
multiline_comment|/* clear cmstr bit */
id|host-&gt;csr.state
op_and_assign
op_complement
l_int|0x100
suffix:semicolon
)brace
id|host-&gt;csr.topology_map
(braket
l_int|1
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|be32_to_cpu
c_func
(paren
id|host-&gt;csr.topology_map
(braket
l_int|1
)braket
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|host-&gt;csr.topology_map
(braket
l_int|2
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;node_count
op_lshift
l_int|16
op_or
id|host-&gt;selfid_count
)paren
suffix:semicolon
id|host-&gt;csr.topology_map
(braket
l_int|0
)braket
op_assign
id|cpu_to_be32
c_func
(paren
(paren
id|host-&gt;selfid_count
op_plus
l_int|2
)paren
op_lshift
l_int|16
op_or
id|csr_crc16
c_func
(paren
id|host-&gt;csr.topology_map
op_plus
l_int|1
comma
id|host-&gt;selfid_count
op_plus
l_int|2
)paren
)paren
suffix:semicolon
id|host-&gt;csr.speed_map
(braket
l_int|1
)braket
op_assign
id|cpu_to_be32
c_func
(paren
id|be32_to_cpu
c_func
(paren
id|host-&gt;csr.speed_map
(braket
l_int|1
)braket
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|host-&gt;csr.speed_map
(braket
l_int|0
)braket
op_assign
id|cpu_to_be32
c_func
(paren
l_int|0x3f1
op_lshift
l_int|16
op_or
id|csr_crc16
c_func
(paren
id|host-&gt;csr.speed_map
op_plus
l_int|1
comma
l_int|0x3f1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; * HI == seconds (bits 0:2)&n; * LO == fraction units of 1/8000 of a second, as per 1394 (bits 19:31)&n; *&n; * Convert to units and then to HZ, for comparison to jiffies.&n; *&n; * By default this will end up being 800 units, or 100ms (125usec per&n; * unit).&n; *&n; * NOTE: The spec says 1/8000, but also says we can compute based on 1/8192&n; * like CSR specifies. Should make our math less complex.&n; */
DECL|function|calculate_expire
r_static
r_inline
r_void
id|calculate_expire
c_func
(paren
r_struct
id|csr_control
op_star
id|csr
)paren
(brace
r_int
r_int
id|units
suffix:semicolon
multiline_comment|/* Take the seconds, and convert to units */
id|units
op_assign
(paren
r_int
r_int
)paren
(paren
id|csr-&gt;split_timeout_hi
op_amp
l_int|0x07
)paren
op_lshift
l_int|13
suffix:semicolon
multiline_comment|/* Add in the fractional units */
id|units
op_add_assign
(paren
r_int
r_int
)paren
(paren
id|csr-&gt;split_timeout_lo
op_rshift
l_int|19
)paren
suffix:semicolon
multiline_comment|/* Convert to jiffies */
id|csr-&gt;expire
op_assign
(paren
r_int
r_int
)paren
(paren
id|units
op_star
id|HZ
)paren
op_rshift
l_int|13UL
suffix:semicolon
multiline_comment|/* Just to keep from rounding low */
id|csr-&gt;expire
op_increment
suffix:semicolon
id|HPSB_VERBOSE
c_func
(paren
l_string|&quot;CSR: setting expire to %lu, HZ=%u&quot;
comma
id|csr-&gt;expire
comma
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|add_host
r_static
r_void
id|add_host
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
)paren
(brace
id|host-&gt;csr.lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|host-&gt;csr.rom_size
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|get_rom
c_func
(paren
id|host
comma
op_amp
id|host-&gt;csr.rom
)paren
suffix:semicolon
id|host-&gt;csr.rom_version
op_assign
l_int|0
suffix:semicolon
id|host-&gt;csr.state
op_assign
l_int|0
suffix:semicolon
id|host-&gt;csr.node_ids
op_assign
l_int|0
suffix:semicolon
id|host-&gt;csr.split_timeout_hi
op_assign
l_int|0
suffix:semicolon
id|host-&gt;csr.split_timeout_lo
op_assign
l_int|800
op_lshift
l_int|19
suffix:semicolon
id|calculate_expire
c_func
(paren
op_amp
id|host-&gt;csr
)paren
suffix:semicolon
id|host-&gt;csr.cycle_time
op_assign
l_int|0
suffix:semicolon
id|host-&gt;csr.bus_time
op_assign
l_int|0
suffix:semicolon
id|host-&gt;csr.bus_manager_id
op_assign
l_int|0x3f
suffix:semicolon
id|host-&gt;csr.bandwidth_available
op_assign
l_int|4915
suffix:semicolon
id|host-&gt;csr.channels_available_hi
op_assign
l_int|0xfffffffe
suffix:semicolon
multiline_comment|/* pre-alloc ch 31 per 1394a-2000 */
id|host-&gt;csr.channels_available_lo
op_assign
op_complement
l_int|0
suffix:semicolon
id|host-&gt;csr.broadcast_channel
op_assign
l_int|0x80000000
op_or
l_int|31
suffix:semicolon
r_if
c_cond
(paren
id|host-&gt;is_irm
)paren
(brace
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
(brace
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
l_int|2
comma
l_int|0xfffffffe
comma
op_complement
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|hpsb_update_config_rom
r_int
id|hpsb_update_config_rom
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_const
id|quadlet_t
op_star
id|new_rom
comma
r_int
id|size
comma
r_int
r_char
id|rom_version
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rom_version
op_ne
id|host-&gt;csr.rom_version
)paren
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|size
OG
(paren
id|CSR_CONFIG_ROM_SIZE
op_lshift
l_int|2
)paren
)paren
id|ret
op_assign
op_minus
l_int|2
suffix:semicolon
r_else
(brace
id|memcpy
c_func
(paren
id|host-&gt;csr.rom
comma
id|new_rom
comma
id|size
)paren
suffix:semicolon
id|host-&gt;csr.rom_size
op_assign
id|size
suffix:semicolon
id|host-&gt;csr.rom_version
op_increment
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|hpsb_get_config_rom
r_int
id|hpsb_get_config_rom
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
id|quadlet_t
op_star
id|buffer
comma
r_int
id|buffersize
comma
r_int
op_star
id|rom_size
comma
r_int
r_char
op_star
id|rom_version
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
op_star
id|rom_version
op_assign
id|host-&gt;csr.rom_version
suffix:semicolon
op_star
id|rom_size
op_assign
id|host-&gt;csr.rom_size
suffix:semicolon
r_if
c_cond
(paren
id|buffersize
OL
id|host-&gt;csr.rom_size
)paren
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
(brace
id|memcpy
c_func
(paren
id|buffer
comma
id|host-&gt;csr.rom
comma
id|host-&gt;csr.rom_size
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Read topology / speed maps and configuration ROM */
DECL|function|read_maps
r_static
r_int
id|read_maps
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|buffer
comma
id|u64
id|addr
comma
r_int
id|length
comma
id|u16
id|fl
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_const
r_char
op_star
id|src
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csraddr
OL
id|CSR_TOPOLOGY_MAP
)paren
(brace
r_if
c_cond
(paren
id|csraddr
op_plus
id|length
OG
id|CSR_CONFIG_ROM
op_plus
id|host-&gt;csr.rom_size
)paren
(brace
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
id|src
op_assign
(paren
(paren
r_char
op_star
)paren
id|host-&gt;csr.rom
)paren
op_plus
id|csraddr
op_minus
id|CSR_CONFIG_ROM
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|csraddr
OL
id|CSR_SPEED_MAP
)paren
(brace
id|src
op_assign
(paren
(paren
r_char
op_star
)paren
id|host-&gt;csr.topology_map
)paren
op_plus
id|csraddr
op_minus
id|CSR_TOPOLOGY_MAP
suffix:semicolon
)brace
r_else
(brace
id|src
op_assign
(paren
(paren
r_char
op_star
)paren
id|host-&gt;csr.speed_map
)paren
op_plus
id|csraddr
op_minus
id|CSR_SPEED_MAP
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|buffer
comma
id|src
comma
id|length
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
DECL|macro|out
mdefine_line|#define out if (--length == 0) break
DECL|function|read_regs
r_static
r_int
id|read_regs
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|buf
comma
id|u64
id|addr
comma
r_int
id|length
comma
id|u16
id|flags
)paren
(brace
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_int
id|oldcycle
suffix:semicolon
id|quadlet_t
id|ret
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csraddr
op_or
id|length
)paren
op_amp
l_int|0x3
)paren
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
id|length
op_div_assign
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|csraddr
)paren
(brace
r_case
id|CSR_STATE_CLEAR
suffix:colon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.state
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_STATE_SET
suffix:colon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.state
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_NODE_IDS
suffix:colon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.node_ids
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_RESET_START
suffix:colon
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
multiline_comment|/* address gap - handled by default below */
r_case
id|CSR_SPLIT_TIMEOUT_HI
suffix:colon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.split_timeout_hi
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_SPLIT_TIMEOUT_LO
suffix:colon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.split_timeout_lo
)paren
suffix:semicolon
id|out
suffix:semicolon
multiline_comment|/* address gap */
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
r_case
id|CSR_CYCLE_TIME
suffix:colon
id|oldcycle
op_assign
id|host-&gt;csr.cycle_time
suffix:semicolon
id|host-&gt;csr.cycle_time
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|devctl
c_func
(paren
id|host
comma
id|GET_CYCLE_COUNTER
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldcycle
OG
id|host-&gt;csr.cycle_time
)paren
(brace
multiline_comment|/* cycle time wrapped around */
id|host-&gt;csr.bus_time
op_add_assign
l_int|1
op_lshift
l_int|7
suffix:semicolon
)brace
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.cycle_time
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_BUS_TIME
suffix:colon
id|oldcycle
op_assign
id|host-&gt;csr.cycle_time
suffix:semicolon
id|host-&gt;csr.cycle_time
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|devctl
c_func
(paren
id|host
comma
id|GET_CYCLE_COUNTER
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|oldcycle
OG
id|host-&gt;csr.cycle_time
)paren
(brace
multiline_comment|/* cycle time wrapped around */
id|host-&gt;csr.bus_time
op_add_assign
(paren
l_int|1
op_lshift
l_int|7
)paren
suffix:semicolon
)brace
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.bus_time
op_or
(paren
id|host-&gt;csr.cycle_time
op_rshift
l_int|25
)paren
)paren
suffix:semicolon
id|out
suffix:semicolon
multiline_comment|/* address gap */
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
r_case
id|CSR_BUSY_TIMEOUT
suffix:colon
multiline_comment|/* not yet implemented */
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
r_case
id|CSR_BUS_MANAGER_ID
suffix:colon
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
id|ret
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|host-&gt;csr.bus_manager_id
suffix:semicolon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|ret
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_BANDWIDTH_AVAILABLE
suffix:colon
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
id|ret
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
l_int|1
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|host-&gt;csr.bandwidth_available
suffix:semicolon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|ret
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_CHANNELS_AVAILABLE_HI
suffix:colon
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
id|ret
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
l_int|2
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|host-&gt;csr.channels_available_hi
suffix:semicolon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|ret
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_CHANNELS_AVAILABLE_LO
suffix:colon
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
id|ret
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
l_int|3
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|host-&gt;csr.channels_available_lo
suffix:semicolon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|ret
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_BROADCAST_CHANNEL
suffix:colon
op_star
(paren
id|buf
op_increment
)paren
op_assign
id|cpu_to_be32
c_func
(paren
id|host-&gt;csr.broadcast_channel
)paren
suffix:semicolon
id|out
suffix:semicolon
multiline_comment|/* address gap to end - fall through to default */
r_default
suffix:colon
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
DECL|function|write_regs
r_static
r_int
id|write_regs
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
r_int
id|destid
comma
id|quadlet_t
op_star
id|data
comma
id|u64
id|addr
comma
r_int
id|length
comma
id|u16
id|flags
)paren
(brace
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|csraddr
op_or
id|length
)paren
op_amp
l_int|0x3
)paren
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
id|length
op_div_assign
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|csraddr
)paren
(brace
r_case
id|CSR_STATE_CLEAR
suffix:colon
multiline_comment|/* FIXME FIXME FIXME */
id|printk
c_func
(paren
l_string|&quot;doh, someone wants to mess with state clear&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_STATE_SET
suffix:colon
id|printk
c_func
(paren
l_string|&quot;doh, someone wants to mess with state set&bslash;n&quot;
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_NODE_IDS
suffix:colon
id|host-&gt;csr.node_ids
op_and_assign
id|NODE_MASK
op_lshift
l_int|16
suffix:semicolon
id|host-&gt;csr.node_ids
op_or_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|data
op_increment
)paren
)paren
op_amp
(paren
id|BUS_MASK
op_lshift
l_int|16
)paren
suffix:semicolon
id|host-&gt;node_id
op_assign
id|host-&gt;csr.node_ids
op_rshift
l_int|16
suffix:semicolon
id|host-&gt;driver
op_member_access_from_pointer
id|devctl
c_func
(paren
id|host
comma
id|SET_BUS_ID
comma
id|host-&gt;node_id
op_rshift
l_int|6
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_RESET_START
suffix:colon
multiline_comment|/* FIXME - perform command reset */
id|out
suffix:semicolon
multiline_comment|/* address gap */
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
r_case
id|CSR_SPLIT_TIMEOUT_HI
suffix:colon
id|host-&gt;csr.split_timeout_hi
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|data
op_increment
)paren
)paren
op_amp
l_int|0x00000007
suffix:semicolon
id|calculate_expire
c_func
(paren
op_amp
id|host-&gt;csr
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_SPLIT_TIMEOUT_LO
suffix:colon
id|host-&gt;csr.split_timeout_lo
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|data
op_increment
)paren
)paren
op_amp
l_int|0xfff80000
suffix:semicolon
id|calculate_expire
c_func
(paren
op_amp
id|host-&gt;csr
)paren
suffix:semicolon
id|out
suffix:semicolon
multiline_comment|/* address gap */
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
r_case
id|CSR_CYCLE_TIME
suffix:colon
multiline_comment|/* should only be set by cycle start packet, automatically */
id|host-&gt;csr.cycle_time
op_assign
id|be32_to_cpu
c_func
(paren
op_star
id|data
)paren
suffix:semicolon
id|host-&gt;driver
op_member_access_from_pointer
id|devctl
c_func
(paren
id|host
comma
id|SET_CYCLE_COUNTER
comma
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|data
op_increment
)paren
)paren
)paren
suffix:semicolon
id|out
suffix:semicolon
r_case
id|CSR_BUS_TIME
suffix:colon
id|host-&gt;csr.bus_time
op_assign
id|be32_to_cpu
c_func
(paren
op_star
(paren
id|data
op_increment
)paren
)paren
op_amp
l_int|0xffffff80
suffix:semicolon
id|out
suffix:semicolon
multiline_comment|/* address gap */
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
r_case
id|CSR_BUSY_TIMEOUT
suffix:colon
multiline_comment|/* not yet implemented */
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
r_case
id|CSR_BUS_MANAGER_ID
suffix:colon
r_case
id|CSR_BANDWIDTH_AVAILABLE
suffix:colon
r_case
id|CSR_CHANNELS_AVAILABLE_HI
suffix:colon
r_case
id|CSR_CHANNELS_AVAILABLE_LO
suffix:colon
multiline_comment|/* these are not writable, only lockable */
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
r_case
id|CSR_BROADCAST_CHANNEL
suffix:colon
multiline_comment|/* only the valid bit can be written */
id|host-&gt;csr.broadcast_channel
op_assign
(paren
id|host-&gt;csr.broadcast_channel
op_amp
op_complement
l_int|0x40000000
)paren
op_or
(paren
id|be32_to_cpu
c_func
(paren
op_star
id|data
)paren
op_amp
l_int|0x40000000
)paren
suffix:semicolon
id|out
suffix:semicolon
multiline_comment|/* address gap to end - fall through */
r_default
suffix:colon
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
DECL|macro|out
macro_line|#undef out
DECL|function|lock_regs
r_static
r_int
id|lock_regs
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|quadlet_t
op_star
id|store
comma
id|u64
id|addr
comma
id|quadlet_t
id|data
comma
id|quadlet_t
id|arg
comma
r_int
id|extcode
comma
id|u16
id|fl
)paren
(brace
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|quadlet_t
op_star
id|regptr
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|csraddr
op_amp
l_int|0x3
)paren
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|csraddr
template_param
id|CSR_CHANNELS_AVAILABLE_LO
op_logical_or
id|extcode
op_ne
id|EXTCODE_COMPARE_SWAP
)paren
r_goto
id|unsupported_lockreq
suffix:semicolon
id|data
op_assign
id|be32_to_cpu
c_func
(paren
id|data
)paren
suffix:semicolon
id|arg
op_assign
id|be32_to_cpu
c_func
(paren
id|arg
)paren
suffix:semicolon
multiline_comment|/* Is somebody releasing the broadcast_channel on us? */
r_if
c_cond
(paren
id|csraddr
op_eq
id|CSR_CHANNELS_AVAILABLE_HI
op_logical_and
(paren
id|data
op_amp
l_int|0x1
)paren
)paren
(brace
multiline_comment|/* Note: this is may not be the right way to handle&n;&t;&t; * the problem, so we should look into the proper way&n;&t;&t; * eventually. */
id|HPSB_WARN
c_func
(paren
l_string|&quot;Node [&quot;
id|NODE_BUS_FMT
l_string|&quot;] wants to release &quot;
l_string|&quot;broadcast channel 31.  Ignoring.&quot;
comma
id|NODE_BUS_ARGS
c_func
(paren
id|host
comma
id|nodeid
)paren
)paren
suffix:semicolon
id|data
op_and_assign
op_complement
l_int|0x1
suffix:semicolon
multiline_comment|/* keep broadcast channel allocated */
)brace
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
(brace
id|quadlet_t
id|old
suffix:semicolon
id|old
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
(paren
id|csraddr
op_minus
id|CSR_BUS_MANAGER_ID
)paren
op_rshift
l_int|2
comma
id|data
comma
id|arg
)paren
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|old
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|csraddr
)paren
(brace
r_case
id|CSR_BUS_MANAGER_ID
suffix:colon
id|regptr
op_assign
op_amp
id|host-&gt;csr.bus_manager_id
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
op_star
id|regptr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|regptr
op_eq
id|arg
)paren
op_star
id|regptr
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CSR_BANDWIDTH_AVAILABLE
suffix:colon
(brace
id|quadlet_t
id|bandwidth
suffix:semicolon
id|quadlet_t
id|old
suffix:semicolon
id|quadlet_t
r_new
suffix:semicolon
id|regptr
op_assign
op_amp
id|host-&gt;csr.bandwidth_available
suffix:semicolon
id|old
op_assign
op_star
id|regptr
suffix:semicolon
multiline_comment|/* bandwidth available algorithm adapted from IEEE 1394a-2000 spec */
r_if
c_cond
(paren
id|arg
OG
l_int|0x1fff
)paren
(brace
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|old
)paren
suffix:semicolon
multiline_comment|/* change nothing */
r_break
suffix:semicolon
)brace
id|data
op_and_assign
l_int|0x1fff
suffix:semicolon
r_if
c_cond
(paren
id|arg
op_ge
id|data
)paren
(brace
multiline_comment|/* allocate bandwidth */
id|bandwidth
op_assign
id|arg
op_minus
id|data
suffix:semicolon
r_if
c_cond
(paren
id|old
op_ge
id|bandwidth
)paren
(brace
r_new
op_assign
id|old
op_minus
id|bandwidth
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|arg
)paren
suffix:semicolon
op_star
id|regptr
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* deallocate bandwidth */
id|bandwidth
op_assign
id|data
op_minus
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|old
op_plus
id|bandwidth
OL
l_int|0x2000
)paren
(brace
r_new
op_assign
id|old
op_plus
id|bandwidth
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|arg
)paren
suffix:semicolon
op_star
id|regptr
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_case
id|CSR_CHANNELS_AVAILABLE_HI
suffix:colon
(brace
multiline_comment|/* Lock algorithm for CHANNELS_AVAILABLE as recommended by 1394a-2000 */
id|quadlet_t
id|affected_channels
op_assign
id|arg
op_xor
id|data
suffix:semicolon
id|regptr
op_assign
op_amp
id|host-&gt;csr.channels_available_hi
suffix:semicolon
r_if
c_cond
(paren
(paren
id|arg
op_amp
id|affected_channels
)paren
op_eq
(paren
op_star
id|regptr
op_amp
id|affected_channels
)paren
)paren
(brace
op_star
id|regptr
op_xor_assign
id|affected_channels
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
op_star
id|regptr
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|CSR_CHANNELS_AVAILABLE_LO
suffix:colon
(brace
multiline_comment|/* Lock algorithm for CHANNELS_AVAILABLE as recommended by 1394a-2000 */
id|quadlet_t
id|affected_channels
op_assign
id|arg
op_xor
id|data
suffix:semicolon
id|regptr
op_assign
op_amp
id|host-&gt;csr.channels_available_lo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|arg
op_amp
id|affected_channels
)paren
op_eq
(paren
op_star
id|regptr
op_amp
id|affected_channels
)paren
)paren
(brace
op_star
id|regptr
op_xor_assign
id|affected_channels
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|store
op_assign
id|cpu_to_be32
c_func
(paren
op_star
id|regptr
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
id|unsupported_lockreq
suffix:colon
r_switch
c_cond
(paren
id|csraddr
)paren
(brace
r_case
id|CSR_STATE_CLEAR
suffix:colon
r_case
id|CSR_STATE_SET
suffix:colon
r_case
id|CSR_RESET_START
suffix:colon
r_case
id|CSR_NODE_IDS
suffix:colon
r_case
id|CSR_SPLIT_TIMEOUT_HI
suffix:colon
r_case
id|CSR_SPLIT_TIMEOUT_LO
suffix:colon
r_case
id|CSR_CYCLE_TIME
suffix:colon
r_case
id|CSR_BUS_TIME
suffix:colon
r_case
id|CSR_BROADCAST_CHANNEL
suffix:colon
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
r_case
id|CSR_BUSY_TIMEOUT
suffix:colon
multiline_comment|/* not yet implemented - fall through */
r_default
suffix:colon
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
)brace
DECL|function|lock64_regs
r_static
r_int
id|lock64_regs
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
id|octlet_t
op_star
id|store
comma
id|u64
id|addr
comma
id|octlet_t
id|data
comma
id|octlet_t
id|arg
comma
r_int
id|extcode
comma
id|u16
id|fl
)paren
(brace
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|data
op_assign
id|be64_to_cpu
c_func
(paren
id|data
)paren
suffix:semicolon
id|arg
op_assign
id|be64_to_cpu
c_func
(paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csraddr
op_amp
l_int|0x3
)paren
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|csraddr
op_ne
id|CSR_CHANNELS_AVAILABLE
op_logical_or
id|extcode
op_ne
id|EXTCODE_COMPARE_SWAP
)paren
r_goto
id|unsupported_lock64req
suffix:semicolon
multiline_comment|/* Is somebody releasing the broadcast_channel on us? */
r_if
c_cond
(paren
id|csraddr
op_eq
id|CSR_CHANNELS_AVAILABLE_HI
op_logical_and
(paren
id|data
op_amp
l_int|0x100000000ULL
)paren
)paren
(brace
multiline_comment|/* Note: this is may not be the right way to handle&n;&t;&t; * the problem, so we should look into the proper way&n;                 * eventually. */
id|HPSB_WARN
c_func
(paren
l_string|&quot;Node [&quot;
id|NODE_BUS_FMT
l_string|&quot;] wants to release &quot;
l_string|&quot;broadcast channel 31.  Ignoring.&quot;
comma
id|NODE_BUS_ARGS
c_func
(paren
id|host
comma
id|nodeid
)paren
)paren
suffix:semicolon
id|data
op_and_assign
op_complement
l_int|0x100000000ULL
suffix:semicolon
multiline_comment|/* keep broadcast channel allocated */
)brace
r_if
c_cond
(paren
id|host-&gt;driver-&gt;hw_csr_reg
)paren
(brace
id|quadlet_t
id|data_hi
comma
id|data_lo
suffix:semicolon
id|quadlet_t
id|arg_hi
comma
id|arg_lo
suffix:semicolon
id|quadlet_t
id|old_hi
comma
id|old_lo
suffix:semicolon
id|data_hi
op_assign
id|data
op_rshift
l_int|32
suffix:semicolon
id|data_lo
op_assign
id|data
op_amp
l_int|0xFFFFFFFF
suffix:semicolon
id|arg_hi
op_assign
id|arg
op_rshift
l_int|32
suffix:semicolon
id|arg_lo
op_assign
id|arg
op_amp
l_int|0xFFFFFFFF
suffix:semicolon
id|old_hi
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
(paren
id|csraddr
op_minus
id|CSR_BUS_MANAGER_ID
)paren
op_rshift
l_int|2
comma
id|data_hi
comma
id|arg_hi
)paren
suffix:semicolon
id|old_lo
op_assign
id|host-&gt;driver
op_member_access_from_pointer
id|hw_csr_reg
c_func
(paren
id|host
comma
(paren
(paren
id|csraddr
op_plus
l_int|4
)paren
op_minus
id|CSR_BUS_MANAGER_ID
)paren
op_rshift
l_int|2
comma
id|data_lo
comma
id|arg_lo
)paren
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be64
c_func
(paren
(paren
(paren
id|octlet_t
)paren
id|old_hi
op_lshift
l_int|32
)paren
op_or
id|old_lo
)paren
suffix:semicolon
)brace
r_else
(brace
id|octlet_t
id|old
suffix:semicolon
id|octlet_t
id|affected_channels
op_assign
id|arg
op_xor
id|data
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
id|old
op_assign
(paren
(paren
id|octlet_t
)paren
id|host-&gt;csr.channels_available_hi
op_lshift
l_int|32
)paren
op_or
id|host-&gt;csr.channels_available_lo
suffix:semicolon
r_if
c_cond
(paren
(paren
id|arg
op_amp
id|affected_channels
)paren
op_eq
(paren
id|old
op_amp
id|affected_channels
)paren
)paren
(brace
id|host-&gt;csr.channels_available_hi
op_xor_assign
(paren
id|affected_channels
op_rshift
l_int|32
)paren
suffix:semicolon
id|host-&gt;csr.channels_available_lo
op_xor_assign
(paren
id|affected_channels
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
op_star
id|store
op_assign
id|cpu_to_be64
c_func
(paren
id|arg
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|store
op_assign
id|cpu_to_be64
c_func
(paren
id|old
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|host-&gt;csr.lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Is somebody erroneously releasing the broadcast_channel on us? */
r_if
c_cond
(paren
id|host-&gt;csr.channels_available_hi
op_amp
l_int|0x1
)paren
id|host-&gt;csr.channels_available_hi
op_and_assign
op_complement
l_int|0x1
suffix:semicolon
r_return
id|RCODE_COMPLETE
suffix:semicolon
id|unsupported_lock64req
suffix:colon
r_switch
c_cond
(paren
id|csraddr
)paren
(brace
r_case
id|CSR_STATE_CLEAR
suffix:colon
r_case
id|CSR_STATE_SET
suffix:colon
r_case
id|CSR_RESET_START
suffix:colon
r_case
id|CSR_NODE_IDS
suffix:colon
r_case
id|CSR_SPLIT_TIMEOUT_HI
suffix:colon
r_case
id|CSR_SPLIT_TIMEOUT_LO
suffix:colon
r_case
id|CSR_CYCLE_TIME
suffix:colon
r_case
id|CSR_BUS_TIME
suffix:colon
r_case
id|CSR_BUS_MANAGER_ID
suffix:colon
r_case
id|CSR_BROADCAST_CHANNEL
suffix:colon
r_case
id|CSR_BUSY_TIMEOUT
suffix:colon
r_case
id|CSR_BANDWIDTH_AVAILABLE
suffix:colon
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
r_default
suffix:colon
r_return
id|RCODE_ADDRESS_ERROR
suffix:semicolon
)brace
)brace
DECL|function|write_fcp
r_static
r_int
id|write_fcp
c_func
(paren
r_struct
id|hpsb_host
op_star
id|host
comma
r_int
id|nodeid
comma
r_int
id|dest
comma
id|quadlet_t
op_star
id|data
comma
id|u64
id|addr
comma
r_int
id|length
comma
id|u16
id|flags
)paren
(brace
r_int
id|csraddr
op_assign
id|addr
op_minus
id|CSR_REGISTER_BASE
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
l_int|512
)paren
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
r_switch
c_cond
(paren
id|csraddr
)paren
(brace
r_case
id|CSR_FCP_COMMAND
suffix:colon
id|highlevel_fcp_request
c_func
(paren
id|host
comma
id|nodeid
comma
l_int|0
comma
(paren
id|u8
op_star
)paren
id|data
comma
id|length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CSR_FCP_RESPONSE
suffix:colon
id|highlevel_fcp_request
c_func
(paren
id|host
comma
id|nodeid
comma
l_int|1
comma
(paren
id|u8
op_star
)paren
id|data
comma
id|length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|RCODE_TYPE_ERROR
suffix:semicolon
)brace
r_return
id|RCODE_COMPLETE
suffix:semicolon
)brace
DECL|variable|csr_highlevel
r_static
r_struct
id|hpsb_highlevel
id|csr_highlevel
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;standard registers&quot;
comma
dot
id|add_host
op_assign
id|add_host
comma
dot
id|host_reset
op_assign
id|host_reset
comma
)brace
suffix:semicolon
DECL|variable|map_ops
r_static
r_struct
id|hpsb_address_ops
id|map_ops
op_assign
(brace
dot
id|read
op_assign
id|read_maps
comma
)brace
suffix:semicolon
DECL|variable|fcp_ops
r_static
r_struct
id|hpsb_address_ops
id|fcp_ops
op_assign
(brace
dot
id|write
op_assign
id|write_fcp
comma
)brace
suffix:semicolon
DECL|variable|reg_ops
r_static
r_struct
id|hpsb_address_ops
id|reg_ops
op_assign
(brace
dot
id|read
op_assign
id|read_regs
comma
dot
id|write
op_assign
id|write_regs
comma
dot
id|lock
op_assign
id|lock_regs
comma
dot
id|lock64
op_assign
id|lock64_regs
comma
)brace
suffix:semicolon
DECL|function|init_csr
r_void
id|init_csr
c_func
(paren
r_void
)paren
(brace
id|hpsb_register_highlevel
c_func
(paren
op_amp
id|csr_highlevel
)paren
suffix:semicolon
id|hpsb_register_addrspace
c_func
(paren
op_amp
id|csr_highlevel
comma
op_amp
id|reg_ops
comma
id|CSR_REGISTER_BASE
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_CONFIG_ROM
)paren
suffix:semicolon
id|hpsb_register_addrspace
c_func
(paren
op_amp
id|csr_highlevel
comma
op_amp
id|map_ops
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_CONFIG_ROM
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_CONFIG_ROM_END
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fcp
)paren
(brace
id|hpsb_register_addrspace
c_func
(paren
op_amp
id|csr_highlevel
comma
op_amp
id|fcp_ops
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_FCP_COMMAND
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_FCP_END
)paren
suffix:semicolon
)brace
id|hpsb_register_addrspace
c_func
(paren
op_amp
id|csr_highlevel
comma
op_amp
id|map_ops
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_TOPOLOGY_MAP
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_TOPOLOGY_MAP_END
)paren
suffix:semicolon
id|hpsb_register_addrspace
c_func
(paren
op_amp
id|csr_highlevel
comma
op_amp
id|map_ops
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_SPEED_MAP
comma
id|CSR_REGISTER_BASE
op_plus
id|CSR_SPEED_MAP_END
)paren
suffix:semicolon
)brace
DECL|function|cleanup_csr
r_void
id|cleanup_csr
c_func
(paren
r_void
)paren
(brace
id|hpsb_unregister_highlevel
c_func
(paren
op_amp
id|csr_highlevel
)paren
suffix:semicolon
)brace
eof
