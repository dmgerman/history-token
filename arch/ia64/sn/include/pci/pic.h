multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_PIC_H
DECL|macro|_ASM_IA64_SN_PCI_PIC_H
mdefine_line|#define _ASM_IA64_SN_PCI_PIC_H
multiline_comment|/*&n; * PIC AS DEVICE ZERO&n; * ------------------&n; *&n; * PIC handles PCI/X busses.  PCI/X requires that the &squot;bridge&squot; (i.e. PIC)&n; * be designated as &squot;device 0&squot;.   That is a departure from earlier SGI&n; * PCI bridges.  Because of that we use config space 1 to access the&n; * config space of the first actual PCI device on the bus. &n; * Here&squot;s what the PIC manual says:&n; *&n; *     The current PCI-X bus specification now defines that the parent&n; *     hosts bus bridge (PIC for example) must be device 0 on bus 0. PIC&n; *     reduced the total number of devices from 8 to 4 and removed the&n; *     device registers and windows, now only supporting devices 0,1,2, and&n; *     3. PIC did leave all 8 configuration space windows. The reason was&n; *     there was nothing to gain by removing them. Here in lies the problem.&n; *     The device numbering we do using 0 through 3 is unrelated to the device&n; *     numbering which PCI-X requires in configuration space. In the past we&n; *     correlated Configs pace and our device space 0 &lt;-&gt; 0, 1 &lt;-&gt; 1, etc.&n; *     PCI-X requires we start a 1, not 0 and currently the PX brick&n; *     does associate our:&n; * &n; *         device 0 with configuration space window 1,&n; *         device 1 with configuration space window 2, &n; *         device 2 with configuration space window 3,&n; *         device 3 with configuration space window 4.&n; *&n; * The net effect is that all config space access are off-by-one with &n; * relation to other per-slot accesses on the PIC.   &n; * Here is a table that shows some of that:&n; *&n; *                               Internal Slot#&n; *           |&n; *           |     0         1        2         3&n; * ----------|---------------------------------------&n; * config    |  0x21000   0x22000  0x23000   0x24000&n; *           |&n; * even rrb  |  0[0]      n/a      1[0]      n/a&t;[] == implied even/odd&n; *           |&n; * odd rrb   |  n/a       0[1]     n/a       1[1]&n; *           |&n; * int dev   |  00       01        10        11&n; *           |&n; * ext slot# |  1        2         3         4&n; * ----------|---------------------------------------&n; */
DECL|macro|PIC_ATE_TARGETID_SHFT
mdefine_line|#define PIC_ATE_TARGETID_SHFT           8
DECL|macro|PIC_HOST_INTR_ADDR
mdefine_line|#define PIC_HOST_INTR_ADDR              0x0000FFFFFFFFFFFFUL
DECL|macro|PIC_PCI64_ATTR_TARG_SHFT
mdefine_line|#define PIC_PCI64_ATTR_TARG_SHFT        60
multiline_comment|/*****************************************************************************&n; *********************** PIC MMR structure mapping ***************************&n; *****************************************************************************/
multiline_comment|/* NOTE: PIC WAR. PV#854697.  PIC does not allow writes just to [31:0]&n; * of a 64-bit register.  When writing PIC registers, always write the &n; * entire 64 bits.&n; */
DECL|struct|pic
r_struct
id|pic
(brace
multiline_comment|/* 0x000000-0x00FFFF -- Local Registers */
multiline_comment|/* 0x000000-0x000057 -- Standard Widget Configuration */
DECL|member|p_wid_id
r_uint64
id|p_wid_id
suffix:semicolon
multiline_comment|/* 0x000000 */
DECL|member|p_wid_stat
r_uint64
id|p_wid_stat
suffix:semicolon
multiline_comment|/* 0x000008 */
DECL|member|p_wid_err_upper
r_uint64
id|p_wid_err_upper
suffix:semicolon
multiline_comment|/* 0x000010 */
DECL|member|p_wid_err_lower
r_uint64
id|p_wid_err_lower
suffix:semicolon
multiline_comment|/* 0x000018 */
DECL|macro|p_wid_err
mdefine_line|#define p_wid_err p_wid_err_lower
DECL|member|p_wid_control
r_uint64
id|p_wid_control
suffix:semicolon
multiline_comment|/* 0x000020 */
DECL|member|p_wid_req_timeout
r_uint64
id|p_wid_req_timeout
suffix:semicolon
multiline_comment|/* 0x000028 */
DECL|member|p_wid_int_upper
r_uint64
id|p_wid_int_upper
suffix:semicolon
multiline_comment|/* 0x000030 */
DECL|member|p_wid_int_lower
r_uint64
id|p_wid_int_lower
suffix:semicolon
multiline_comment|/* 0x000038 */
DECL|macro|p_wid_int
mdefine_line|#define p_wid_int p_wid_int_lower
DECL|member|p_wid_err_cmdword
r_uint64
id|p_wid_err_cmdword
suffix:semicolon
multiline_comment|/* 0x000040 */
DECL|member|p_wid_llp
r_uint64
id|p_wid_llp
suffix:semicolon
multiline_comment|/* 0x000048 */
DECL|member|p_wid_tflush
r_uint64
id|p_wid_tflush
suffix:semicolon
multiline_comment|/* 0x000050 */
multiline_comment|/* 0x000058-0x00007F -- Bridge-specific Widget Configuration */
DECL|member|p_wid_aux_err
r_uint64
id|p_wid_aux_err
suffix:semicolon
multiline_comment|/* 0x000058 */
DECL|member|p_wid_resp_upper
r_uint64
id|p_wid_resp_upper
suffix:semicolon
multiline_comment|/* 0x000060 */
DECL|member|p_wid_resp_lower
r_uint64
id|p_wid_resp_lower
suffix:semicolon
multiline_comment|/* 0x000068 */
DECL|macro|p_wid_resp
mdefine_line|#define p_wid_resp p_wid_resp_lower
DECL|member|p_wid_tst_pin_ctrl
r_uint64
id|p_wid_tst_pin_ctrl
suffix:semicolon
multiline_comment|/* 0x000070 */
DECL|member|p_wid_addr_lkerr
r_uint64
id|p_wid_addr_lkerr
suffix:semicolon
multiline_comment|/* 0x000078 */
multiline_comment|/* 0x000080-0x00008F -- PMU &amp; MAP */
DECL|member|p_dir_map
r_uint64
id|p_dir_map
suffix:semicolon
multiline_comment|/* 0x000080 */
DECL|member|_pad_000088
r_uint64
id|_pad_000088
suffix:semicolon
multiline_comment|/* 0x000088 */
multiline_comment|/* 0x000090-0x00009F -- SSRAM */
DECL|member|p_map_fault
r_uint64
id|p_map_fault
suffix:semicolon
multiline_comment|/* 0x000090 */
DECL|member|_pad_000098
r_uint64
id|_pad_000098
suffix:semicolon
multiline_comment|/* 0x000098 */
multiline_comment|/* 0x0000A0-0x0000AF -- Arbitration */
DECL|member|p_arb
r_uint64
id|p_arb
suffix:semicolon
multiline_comment|/* 0x0000A0 */
DECL|member|_pad_0000A8
r_uint64
id|_pad_0000A8
suffix:semicolon
multiline_comment|/* 0x0000A8 */
multiline_comment|/* 0x0000B0-0x0000BF -- Number In A Can or ATE Parity Error */
DECL|member|p_ate_parity_err
r_uint64
id|p_ate_parity_err
suffix:semicolon
multiline_comment|/* 0x0000B0 */
DECL|member|_pad_0000B8
r_uint64
id|_pad_0000B8
suffix:semicolon
multiline_comment|/* 0x0000B8 */
multiline_comment|/* 0x0000C0-0x0000FF -- PCI/GIO */
DECL|member|p_bus_timeout
r_uint64
id|p_bus_timeout
suffix:semicolon
multiline_comment|/* 0x0000C0 */
DECL|member|p_pci_cfg
r_uint64
id|p_pci_cfg
suffix:semicolon
multiline_comment|/* 0x0000C8 */
DECL|member|p_pci_err_upper
r_uint64
id|p_pci_err_upper
suffix:semicolon
multiline_comment|/* 0x0000D0 */
DECL|member|p_pci_err_lower
r_uint64
id|p_pci_err_lower
suffix:semicolon
multiline_comment|/* 0x0000D8 */
DECL|macro|p_pci_err
mdefine_line|#define p_pci_err p_pci_err_lower
DECL|member|_pad_0000E0
r_uint64
id|_pad_0000E0
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0000{E0..F8} */
multiline_comment|/* 0x000100-0x0001FF -- Interrupt */
DECL|member|p_int_status
r_uint64
id|p_int_status
suffix:semicolon
multiline_comment|/* 0x000100 */
DECL|member|p_int_enable
r_uint64
id|p_int_enable
suffix:semicolon
multiline_comment|/* 0x000108 */
DECL|member|p_int_rst_stat
r_uint64
id|p_int_rst_stat
suffix:semicolon
multiline_comment|/* 0x000110 */
DECL|member|p_int_mode
r_uint64
id|p_int_mode
suffix:semicolon
multiline_comment|/* 0x000118 */
DECL|member|p_int_device
r_uint64
id|p_int_device
suffix:semicolon
multiline_comment|/* 0x000120 */
DECL|member|p_int_host_err
r_uint64
id|p_int_host_err
suffix:semicolon
multiline_comment|/* 0x000128 */
DECL|member|p_int_addr
r_uint64
id|p_int_addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{30,,,68} */
DECL|member|p_err_int_view
r_uint64
id|p_err_int_view
suffix:semicolon
multiline_comment|/* 0x000170 */
DECL|member|p_mult_int
r_uint64
id|p_mult_int
suffix:semicolon
multiline_comment|/* 0x000178 */
DECL|member|p_force_always
r_uint64
id|p_force_always
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{80,,,B8} */
DECL|member|p_force_pin
r_uint64
id|p_force_pin
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{C0,,,F8} */
multiline_comment|/* 0x000200-0x000298 -- Device */
DECL|member|p_device
r_uint64
id|p_device
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
DECL|member|p_wr_req_buf
r_uint64
id|p_wr_req_buf
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
DECL|member|p_rrb_map
r_uint64
id|p_rrb_map
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x0002{80,,,88} */
DECL|macro|p_even_resp
mdefine_line|#define p_even_resp p_rrb_map[0]&t;&t;&t;/* 0x000280 */
DECL|macro|p_odd_resp
mdefine_line|#define p_odd_resp  p_rrb_map[1]&t;&t;&t;/* 0x000288 */
DECL|member|p_resp_status
r_uint64
id|p_resp_status
suffix:semicolon
multiline_comment|/* 0x000290 */
DECL|member|p_resp_clear
r_uint64
id|p_resp_clear
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
DECL|member|p_buf_addr_match
)brace
id|p_buf_addr_match
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
DECL|member|p_buf_count
)brace
id|p_buf_count
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x000600-0x0009FF -- PCI/X registers */
DECL|member|p_pcix_bus_err_addr
r_uint64
id|p_pcix_bus_err_addr
suffix:semicolon
multiline_comment|/* 0x000600 */
DECL|member|p_pcix_bus_err_attr
r_uint64
id|p_pcix_bus_err_attr
suffix:semicolon
multiline_comment|/* 0x000608 */
DECL|member|p_pcix_bus_err_data
r_uint64
id|p_pcix_bus_err_data
suffix:semicolon
multiline_comment|/* 0x000610 */
DECL|member|p_pcix_pio_split_addr
r_uint64
id|p_pcix_pio_split_addr
suffix:semicolon
multiline_comment|/* 0x000618 */
DECL|member|p_pcix_pio_split_attr
r_uint64
id|p_pcix_pio_split_attr
suffix:semicolon
multiline_comment|/* 0x000620 */
DECL|member|p_pcix_dma_req_err_attr
r_uint64
id|p_pcix_dma_req_err_attr
suffix:semicolon
multiline_comment|/* 0x000628 */
DECL|member|p_pcix_dma_req_err_addr
r_uint64
id|p_pcix_dma_req_err_addr
suffix:semicolon
multiline_comment|/* 0x000630 */
DECL|member|p_pcix_timeout
r_uint64
id|p_pcix_timeout
suffix:semicolon
multiline_comment|/* 0x000638 */
DECL|member|_pad_000640
r_uint64
id|_pad_000640
(braket
l_int|120
)braket
suffix:semicolon
multiline_comment|/* 0x000{640,,,9F8} */
multiline_comment|/* 0x000A00-0x000BFF -- PCI/X Read&amp;Write Buffer */
r_struct
(brace
DECL|member|p_buf_addr
r_uint64
id|p_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{A00,,,AF0} */
DECL|member|p_buf_attr
r_uint64
id|p_buf_attr
suffix:semicolon
multiline_comment|/* 0X000{A08,,,AF8} */
DECL|member|p_pcix_read_buf_64
)brace
id|p_pcix_read_buf_64
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|p_buf_addr
r_uint64
id|p_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{B00,,,BE0} */
DECL|member|p_buf_attr
r_uint64
id|p_buf_attr
suffix:semicolon
multiline_comment|/* 0x000{B08,,,BE8} */
DECL|member|p_buf_valid
r_uint64
id|p_buf_valid
suffix:semicolon
multiline_comment|/* 0x000{B10,,,BF0} */
DECL|member|__pad1
r_uint64
id|__pad1
suffix:semicolon
multiline_comment|/* 0x000{B18,,,BF8} */
DECL|member|p_pcix_write_buf_64
)brace
id|p_pcix_write_buf_64
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
multiline_comment|/* 0x010000-0x011fff -- Internal ATE RAM (Auto Parity Generation) */
DECL|member|p_int_ate_ram
r_uint64
id|p_int_ate_ram
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* 0x010000-0x011fff */
multiline_comment|/* 0x012000-0x013fff -- Internal ATE RAM (Manual Parity Generation) */
DECL|member|p_int_ate_ram_mp
r_uint64
id|p_int_ate_ram_mp
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* 0x012000-0x013fff */
DECL|member|_pad_014000
r_char
id|_pad_014000
(braket
l_int|0x18000
op_minus
l_int|0x014000
)braket
suffix:semicolon
multiline_comment|/* 0x18000-0x197F8 -- PIC Write Request Ram */
DECL|member|p_wr_req_lower
r_uint64
id|p_wr_req_lower
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x18000 - 0x187F8 */
DECL|member|p_wr_req_upper
r_uint64
id|p_wr_req_upper
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x18800 - 0x18FF8 */
DECL|member|p_wr_req_parity
r_uint64
id|p_wr_req_parity
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x19000 - 0x197F8 */
DECL|member|_pad_019800
r_char
id|_pad_019800
(braket
l_int|0x20000
op_minus
l_int|0x019800
)braket
suffix:semicolon
multiline_comment|/* 0x020000-0x027FFF -- PCI Device Configuration Spaces */
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
DECL|member|p_type0_cfg_dev
)brace
id|p_type0_cfg_dev
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x02{0000,,,7FFF} */
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
DECL|member|p_type1_cfg
)brace
id|p_type1_cfg
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
DECL|member|p_pci_iack
)brace
id|p_pci_iack
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
multiline_comment|/* 0x040000-0x030007 -- PCIX Special Cycle */
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
DECL|member|p_pcix_cycle
)brace
id|p_pcix_cycle
suffix:semicolon
multiline_comment|/* 0x040000-0x040007 */
)brace
suffix:semicolon
macro_line|#endif                          /* _ASM_IA64_SN_PCI_PIC_H */
eof
