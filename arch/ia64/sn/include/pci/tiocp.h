multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2003-2004 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_TIOCP_H
DECL|macro|_ASM_IA64_SN_PCI_TIOCP_H
mdefine_line|#define _ASM_IA64_SN_PCI_TIOCP_H
DECL|macro|TIOCP_HOST_INTR_ADDR
mdefine_line|#define TIOCP_HOST_INTR_ADDR            0x003FFFFFFFFFFFFFUL
DECL|macro|TIOCP_PCI64_CMDTYPE_MEM
mdefine_line|#define TIOCP_PCI64_CMDTYPE_MEM         (0x1ull &lt;&lt; 60)
multiline_comment|/*****************************************************************************&n; *********************** TIOCP MMR structure mapping ***************************&n; *****************************************************************************/
DECL|struct|tiocp
r_struct
id|tiocp
(brace
multiline_comment|/* 0x000000-0x00FFFF -- Local Registers */
multiline_comment|/* 0x000000-0x000057 -- (Legacy Widget Space) Configuration */
DECL|member|cp_id
r_uint64
id|cp_id
suffix:semicolon
multiline_comment|/* 0x000000 */
DECL|member|cp_stat
r_uint64
id|cp_stat
suffix:semicolon
multiline_comment|/* 0x000008 */
DECL|member|cp_err_upper
r_uint64
id|cp_err_upper
suffix:semicolon
multiline_comment|/* 0x000010 */
DECL|member|cp_err_lower
r_uint64
id|cp_err_lower
suffix:semicolon
multiline_comment|/* 0x000018 */
DECL|macro|cp_err
mdefine_line|#define cp_err cp_err_lower
DECL|member|cp_control
r_uint64
id|cp_control
suffix:semicolon
multiline_comment|/* 0x000020 */
DECL|member|cp_req_timeout
r_uint64
id|cp_req_timeout
suffix:semicolon
multiline_comment|/* 0x000028 */
DECL|member|cp_intr_upper
r_uint64
id|cp_intr_upper
suffix:semicolon
multiline_comment|/* 0x000030 */
DECL|member|cp_intr_lower
r_uint64
id|cp_intr_lower
suffix:semicolon
multiline_comment|/* 0x000038 */
DECL|macro|cp_intr
mdefine_line|#define cp_intr cp_intr_lower
DECL|member|cp_err_cmdword
r_uint64
id|cp_err_cmdword
suffix:semicolon
multiline_comment|/* 0x000040 */
DECL|member|_pad_000048
r_uint64
id|_pad_000048
suffix:semicolon
multiline_comment|/* 0x000048 */
DECL|member|cp_tflush
r_uint64
id|cp_tflush
suffix:semicolon
multiline_comment|/* 0x000050 */
multiline_comment|/* 0x000058-0x00007F -- Bridge-specific Configuration */
DECL|member|cp_aux_err
r_uint64
id|cp_aux_err
suffix:semicolon
multiline_comment|/* 0x000058 */
DECL|member|cp_resp_upper
r_uint64
id|cp_resp_upper
suffix:semicolon
multiline_comment|/* 0x000060 */
DECL|member|cp_resp_lower
r_uint64
id|cp_resp_lower
suffix:semicolon
multiline_comment|/* 0x000068 */
DECL|macro|cp_resp
mdefine_line|#define cp_resp cp_resp_lower
DECL|member|cp_tst_pin_ctrl
r_uint64
id|cp_tst_pin_ctrl
suffix:semicolon
multiline_comment|/* 0x000070 */
DECL|member|cp_addr_lkerr
r_uint64
id|cp_addr_lkerr
suffix:semicolon
multiline_comment|/* 0x000078 */
multiline_comment|/* 0x000080-0x00008F -- PMU &amp; MAP */
DECL|member|cp_dir_map
r_uint64
id|cp_dir_map
suffix:semicolon
multiline_comment|/* 0x000080 */
DECL|member|_pad_000088
r_uint64
id|_pad_000088
suffix:semicolon
multiline_comment|/* 0x000088 */
multiline_comment|/* 0x000090-0x00009F -- SSRAM */
DECL|member|cp_map_fault
r_uint64
id|cp_map_fault
suffix:semicolon
multiline_comment|/* 0x000090 */
DECL|member|_pad_000098
r_uint64
id|_pad_000098
suffix:semicolon
multiline_comment|/* 0x000098 */
multiline_comment|/* 0x0000A0-0x0000AF -- Arbitration */
DECL|member|cp_arb
r_uint64
id|cp_arb
suffix:semicolon
multiline_comment|/* 0x0000A0 */
DECL|member|_pad_0000A8
r_uint64
id|_pad_0000A8
suffix:semicolon
multiline_comment|/* 0x0000A8 */
multiline_comment|/* 0x0000B0-0x0000BF -- Number In A Can or ATE Parity Error */
DECL|member|cp_ate_parity_err
r_uint64
id|cp_ate_parity_err
suffix:semicolon
multiline_comment|/* 0x0000B0 */
DECL|member|_pad_0000B8
r_uint64
id|_pad_0000B8
suffix:semicolon
multiline_comment|/* 0x0000B8 */
multiline_comment|/* 0x0000C0-0x0000FF -- PCI/GIO */
DECL|member|cp_bus_timeout
r_uint64
id|cp_bus_timeout
suffix:semicolon
multiline_comment|/* 0x0000C0 */
DECL|member|cp_pci_cfg
r_uint64
id|cp_pci_cfg
suffix:semicolon
multiline_comment|/* 0x0000C8 */
DECL|member|cp_pci_err_upper
r_uint64
id|cp_pci_err_upper
suffix:semicolon
multiline_comment|/* 0x0000D0 */
DECL|member|cp_pci_err_lower
r_uint64
id|cp_pci_err_lower
suffix:semicolon
multiline_comment|/* 0x0000D8 */
DECL|macro|cp_pci_err
mdefine_line|#define cp_pci_err cp_pci_err_lower
DECL|member|_pad_0000E0
r_uint64
id|_pad_0000E0
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0000{E0..F8} */
multiline_comment|/* 0x000100-0x0001FF -- Interrupt */
DECL|member|cp_int_status
r_uint64
id|cp_int_status
suffix:semicolon
multiline_comment|/* 0x000100 */
DECL|member|cp_int_enable
r_uint64
id|cp_int_enable
suffix:semicolon
multiline_comment|/* 0x000108 */
DECL|member|cp_int_rst_stat
r_uint64
id|cp_int_rst_stat
suffix:semicolon
multiline_comment|/* 0x000110 */
DECL|member|cp_int_mode
r_uint64
id|cp_int_mode
suffix:semicolon
multiline_comment|/* 0x000118 */
DECL|member|cp_int_device
r_uint64
id|cp_int_device
suffix:semicolon
multiline_comment|/* 0x000120 */
DECL|member|cp_int_host_err
r_uint64
id|cp_int_host_err
suffix:semicolon
multiline_comment|/* 0x000128 */
DECL|member|cp_int_addr
r_uint64
id|cp_int_addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{30,,,68} */
DECL|member|cp_err_int_view
r_uint64
id|cp_err_int_view
suffix:semicolon
multiline_comment|/* 0x000170 */
DECL|member|cp_mult_int
r_uint64
id|cp_mult_int
suffix:semicolon
multiline_comment|/* 0x000178 */
DECL|member|cp_force_always
r_uint64
id|cp_force_always
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{80,,,B8} */
DECL|member|cp_force_pin
r_uint64
id|cp_force_pin
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{C0,,,F8} */
multiline_comment|/* 0x000200-0x000298 -- Device */
DECL|member|cp_device
r_uint64
id|cp_device
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{00,,,18} */
DECL|member|_pad_000220
r_uint64
id|_pad_000220
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{20,,,38} */
DECL|member|cp_wr_req_buf
r_uint64
id|cp_wr_req_buf
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{40,,,58} */
DECL|member|_pad_000260
r_uint64
id|_pad_000260
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{60,,,78} */
DECL|member|cp_rrb_map
r_uint64
id|cp_rrb_map
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0002{80,,,88} */
DECL|macro|cp_even_resp
mdefine_line|#define cp_even_resp cp_rrb_map[0]&t;&t;&t;/* 0x000280 */
DECL|macro|cp_odd_resp
mdefine_line|#define cp_odd_resp  cp_rrb_map[1]&t;&t;&t;/* 0x000288 */
DECL|member|cp_resp_status
r_uint64
id|cp_resp_status
suffix:semicolon
multiline_comment|/* 0x000290 */
DECL|member|cp_resp_clear
r_uint64
id|cp_resp_clear
suffix:semicolon
multiline_comment|/* 0x000298 */
DECL|member|_pad_0002A0
r_uint64
id|_pad_0002A0
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 0x0002{A0..F8} */
multiline_comment|/* 0x000300-0x0003F8 -- Buffer Address Match Registers */
r_struct
(brace
DECL|member|upper
r_uint64
id|upper
suffix:semicolon
multiline_comment|/* 0x0003{00,,,F0} */
DECL|member|lower
r_uint64
id|lower
suffix:semicolon
multiline_comment|/* 0x0003{08,,,F8} */
DECL|member|cp_buf_addr_match
)brace
id|cp_buf_addr_match
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 0x000400-0x0005FF -- Performance Monitor Registers (even only) */
r_struct
(brace
DECL|member|flush_w_touch
r_uint64
id|flush_w_touch
suffix:semicolon
multiline_comment|/* 0x000{400,,,5C0} */
DECL|member|flush_wo_touch
r_uint64
id|flush_wo_touch
suffix:semicolon
multiline_comment|/* 0x000{408,,,5C8} */
DECL|member|inflight
r_uint64
id|inflight
suffix:semicolon
multiline_comment|/* 0x000{410,,,5D0} */
DECL|member|prefetch
r_uint64
id|prefetch
suffix:semicolon
multiline_comment|/* 0x000{418,,,5D8} */
DECL|member|total_pci_retry
r_uint64
id|total_pci_retry
suffix:semicolon
multiline_comment|/* 0x000{420,,,5E0} */
DECL|member|max_pci_retry
r_uint64
id|max_pci_retry
suffix:semicolon
multiline_comment|/* 0x000{428,,,5E8} */
DECL|member|max_latency
r_uint64
id|max_latency
suffix:semicolon
multiline_comment|/* 0x000{430,,,5F0} */
DECL|member|clear_all
r_uint64
id|clear_all
suffix:semicolon
multiline_comment|/* 0x000{438,,,5F8} */
DECL|member|cp_buf_count
)brace
id|cp_buf_count
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x000600-0x0009FF -- PCI/X registers */
DECL|member|cp_pcix_bus_err_addr
r_uint64
id|cp_pcix_bus_err_addr
suffix:semicolon
multiline_comment|/* 0x000600 */
DECL|member|cp_pcix_bus_err_attr
r_uint64
id|cp_pcix_bus_err_attr
suffix:semicolon
multiline_comment|/* 0x000608 */
DECL|member|cp_pcix_bus_err_data
r_uint64
id|cp_pcix_bus_err_data
suffix:semicolon
multiline_comment|/* 0x000610 */
DECL|member|cp_pcix_pio_split_addr
r_uint64
id|cp_pcix_pio_split_addr
suffix:semicolon
multiline_comment|/* 0x000618 */
DECL|member|cp_pcix_pio_split_attr
r_uint64
id|cp_pcix_pio_split_attr
suffix:semicolon
multiline_comment|/* 0x000620 */
DECL|member|cp_pcix_dma_req_err_attr
r_uint64
id|cp_pcix_dma_req_err_attr
suffix:semicolon
multiline_comment|/* 0x000628 */
DECL|member|cp_pcix_dma_req_err_addr
r_uint64
id|cp_pcix_dma_req_err_addr
suffix:semicolon
multiline_comment|/* 0x000630 */
DECL|member|cp_pcix_timeout
r_uint64
id|cp_pcix_timeout
suffix:semicolon
multiline_comment|/* 0x000638 */
DECL|member|_pad_000640
r_uint64
id|_pad_000640
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* 0x000{640,,,6F8} */
multiline_comment|/* 0x000700-0x000737 -- Debug Registers */
DECL|member|cp_ct_debug_ctl
r_uint64
id|cp_ct_debug_ctl
suffix:semicolon
multiline_comment|/* 0x000700 */
DECL|member|cp_br_debug_ctl
r_uint64
id|cp_br_debug_ctl
suffix:semicolon
multiline_comment|/* 0x000708 */
DECL|member|cp_mux3_debug_ctl
r_uint64
id|cp_mux3_debug_ctl
suffix:semicolon
multiline_comment|/* 0x000710 */
DECL|member|cp_mux4_debug_ctl
r_uint64
id|cp_mux4_debug_ctl
suffix:semicolon
multiline_comment|/* 0x000718 */
DECL|member|cp_mux5_debug_ctl
r_uint64
id|cp_mux5_debug_ctl
suffix:semicolon
multiline_comment|/* 0x000720 */
DECL|member|cp_mux6_debug_ctl
r_uint64
id|cp_mux6_debug_ctl
suffix:semicolon
multiline_comment|/* 0x000728 */
DECL|member|cp_mux7_debug_ctl
r_uint64
id|cp_mux7_debug_ctl
suffix:semicolon
multiline_comment|/* 0x000730 */
DECL|member|_pad_000738
r_uint64
id|_pad_000738
(braket
l_int|89
)braket
suffix:semicolon
multiline_comment|/* 0x000{738,,,9F8} */
multiline_comment|/* 0x000A00-0x000BFF -- PCI/X Read&amp;Write Buffer */
r_struct
(brace
DECL|member|cp_buf_addr
r_uint64
id|cp_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{A00,,,AF0} */
DECL|member|cp_buf_attr
r_uint64
id|cp_buf_attr
suffix:semicolon
multiline_comment|/* 0X000{A08,,,AF8} */
DECL|member|cp_pcix_read_buf_64
)brace
id|cp_pcix_read_buf_64
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|cp_buf_addr
r_uint64
id|cp_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{B00,,,BE0} */
DECL|member|cp_buf_attr
r_uint64
id|cp_buf_attr
suffix:semicolon
multiline_comment|/* 0x000{B08,,,BE8} */
DECL|member|cp_buf_valid
r_uint64
id|cp_buf_valid
suffix:semicolon
multiline_comment|/* 0x000{B10,,,BF0} */
DECL|member|__pad1
r_uint64
id|__pad1
suffix:semicolon
multiline_comment|/* 0x000{B18,,,BF8} */
DECL|member|cp_pcix_write_buf_64
)brace
id|cp_pcix_write_buf_64
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* End of Local Registers -- Start of Address Map space */
DECL|member|_pad_000c00
r_char
id|_pad_000c00
(braket
l_int|0x010000
op_minus
l_int|0x000c00
)braket
suffix:semicolon
multiline_comment|/* 0x010000-0x011FF8 -- Internal ATE RAM (Auto Parity Generation) */
DECL|member|cp_int_ate_ram
r_uint64
id|cp_int_ate_ram
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* 0x010000-0x011FF8 */
DECL|member|_pad_012000
r_char
id|_pad_012000
(braket
l_int|0x14000
op_minus
l_int|0x012000
)braket
suffix:semicolon
multiline_comment|/* 0x014000-0x015FF8 -- Internal ATE RAM (Manual Parity Generation) */
DECL|member|cp_int_ate_ram_mp
r_uint64
id|cp_int_ate_ram_mp
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* 0x014000-0x015FF8 */
DECL|member|_pad_016000
r_char
id|_pad_016000
(braket
l_int|0x18000
op_minus
l_int|0x016000
)braket
suffix:semicolon
multiline_comment|/* 0x18000-0x197F8 -- TIOCP Write Request Ram */
DECL|member|cp_wr_req_lower
r_uint64
id|cp_wr_req_lower
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x18000 - 0x187F8 */
DECL|member|cp_wr_req_upper
r_uint64
id|cp_wr_req_upper
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x18800 - 0x18FF8 */
DECL|member|cp_wr_req_parity
r_uint64
id|cp_wr_req_parity
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x19000 - 0x197F8 */
DECL|member|_pad_019800
r_char
id|_pad_019800
(braket
l_int|0x1C000
op_minus
l_int|0x019800
)braket
suffix:semicolon
multiline_comment|/* 0x1C000-0x1EFF8 -- TIOCP Read Response Ram */
DECL|member|cp_rd_resp_lower
r_uint64
id|cp_rd_resp_lower
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* 0x1C000 - 0x1CFF8 */
DECL|member|cp_rd_resp_upper
r_uint64
id|cp_rd_resp_upper
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* 0x1D000 - 0x1DFF8 */
DECL|member|cp_rd_resp_parity
r_uint64
id|cp_rd_resp_parity
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* 0x1E000 - 0x1EFF8 */
DECL|member|_pad_01F000
r_char
id|_pad_01F000
(braket
l_int|0x20000
op_minus
l_int|0x01F000
)braket
suffix:semicolon
multiline_comment|/* 0x020000-0x021FFF -- Host Device (CP) Configuration Space (not used)  */
DECL|member|_pad_020000
r_char
id|_pad_020000
(braket
l_int|0x021000
op_minus
l_int|0x20000
)braket
suffix:semicolon
multiline_comment|/* 0x021000-0x027FFF -- PCI Device Configuration Spaces */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|0x1000
op_div
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0x02{0000,,,7FFF} */
DECL|member|s
r_uint16
id|s
(braket
l_int|0x1000
op_div
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x02{0000,,,7FFF} */
DECL|member|l
r_uint32
id|l
(braket
l_int|0x1000
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x02{0000,,,7FFF} */
DECL|member|d
r_uint64
id|d
(braket
l_int|0x1000
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x02{0000,,,7FFF} */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|0x100
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
r_uint16
id|s
(braket
l_int|0x100
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_uint32
id|l
(braket
l_int|0x100
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
r_uint64
id|d
(braket
l_int|0x100
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|f
)brace
id|f
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|cp_type0_cfg_dev
)brace
id|cp_type0_cfg_dev
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* 0x02{1000,,,7FFF} */
multiline_comment|/* 0x028000-0x028FFF -- PCI Type 1 Configuration Space */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|0x1000
op_div
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0x028000-0x029000 */
DECL|member|s
r_uint16
id|s
(braket
l_int|0x1000
op_div
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x028000-0x029000 */
DECL|member|l
r_uint32
id|l
(braket
l_int|0x1000
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x028000-0x029000 */
DECL|member|d
r_uint64
id|d
(braket
l_int|0x1000
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x028000-0x029000 */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|0x100
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
r_uint16
id|s
(braket
l_int|0x100
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_uint32
id|l
(braket
l_int|0x100
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
r_uint64
id|d
(braket
l_int|0x100
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|f
)brace
id|f
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|cp_type1_cfg
)brace
id|cp_type1_cfg
suffix:semicolon
multiline_comment|/* 0x028000-0x029000 */
DECL|member|_pad_029000
r_char
id|_pad_029000
(braket
l_int|0x030000
op_minus
l_int|0x029000
)braket
suffix:semicolon
multiline_comment|/* 0x030000-0x030007 -- PCI Interrupt Acknowledge Cycle */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|8
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
r_uint16
id|s
(braket
l_int|8
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_uint32
id|l
(braket
l_int|8
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
r_uint64
id|d
(braket
l_int|8
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|cp_pci_iack
)brace
id|cp_pci_iack
suffix:semicolon
multiline_comment|/* 0x030000-0x030007 */
DECL|member|_pad_030007
r_char
id|_pad_030007
(braket
l_int|0x040000
op_minus
l_int|0x030008
)braket
suffix:semicolon
multiline_comment|/* 0x040000-0x040007 -- PCIX Special Cycle */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|8
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
r_uint16
id|s
(braket
l_int|8
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_uint32
id|l
(braket
l_int|8
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
r_uint64
id|d
(braket
l_int|8
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|cp_pcix_cycle
)brace
id|cp_pcix_cycle
suffix:semicolon
multiline_comment|/* 0x040000-0x040007 */
DECL|member|_pad_040007
r_char
id|_pad_040007
(braket
l_int|0x200000
op_minus
l_int|0x040008
)braket
suffix:semicolon
multiline_comment|/* 0x200000-0x7FFFFF -- PCI/GIO Device Spaces */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|0x100000
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
r_uint16
id|s
(braket
l_int|0x100000
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_uint32
id|l
(braket
l_int|0x100000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
r_uint64
id|d
(braket
l_int|0x100000
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|cp_devio_raw
)brace
id|cp_devio_raw
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0x200000-0x7FFFFF */
DECL|macro|cp_devio
mdefine_line|#define cp_devio(n)  cp_devio_raw[((n)&lt;2)?(n*2):(n+2)]
DECL|member|_pad_800000
r_char
id|_pad_800000
(braket
l_int|0xA00000
op_minus
l_int|0x800000
)braket
suffix:semicolon
multiline_comment|/* 0xA00000-0xBFFFFF -- PCI/GIO Device Spaces w/flush  */
r_union
(brace
DECL|member|c
r_uint8
id|c
(braket
l_int|0x100000
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
r_uint16
id|s
(braket
l_int|0x100000
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_uint32
id|l
(braket
l_int|0x100000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
r_uint64
id|d
(braket
l_int|0x100000
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|cp_devio_raw_flush
)brace
id|cp_devio_raw_flush
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0xA00000-0xBFFFFF */
DECL|macro|cp_devio_flush
mdefine_line|#define cp_devio_flush(n)  cp_devio_raw_flush[((n)&lt;2)?(n*2):(n+2)]
)brace
suffix:semicolon
macro_line|#endif &t;/* _ASM_IA64_SN_PCI_TIOCP_H */
eof
