multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * bridge.h - bridge chip header file, derived from IRIX &lt;sys/PCI/bridge.h&gt;,&n; * revision 1.76.&n; *&n; * Copyright (C) 1996, 1999 Silcon Graphics, Inc.&n; * Copyright (C) 1999 Ralf Baechle (ralf@gnu.org)&n; */
macro_line|#ifndef _ASM_PCI_BRIDGE_H
DECL|macro|_ASM_PCI_BRIDGE_H
mdefine_line|#define _ASM_PCI_BRIDGE_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/xtalk/xwidget.h&gt;&t;&t;/* generic widget header */
multiline_comment|/* I/O page size */
DECL|macro|IOPFNSHIFT
mdefine_line|#define IOPFNSHIFT&t;&t;12&t;/* 4K per mapped page */
DECL|macro|IOPGSIZE
mdefine_line|#define IOPGSIZE&t;&t;(1 &lt;&lt; IOPFNSHIFT)
DECL|macro|IOPG
mdefine_line|#define IOPG(x)&t;&t;&t;((x) &gt;&gt; IOPFNSHIFT)
DECL|macro|IOPGOFF
mdefine_line|#define IOPGOFF(x)&t;&t;((x) &amp; (IOPGSIZE-1))
multiline_comment|/* Bridge RAM sizes */
DECL|macro|BRIDGE_ATE_RAM_SIZE
mdefine_line|#define BRIDGE_ATE_RAM_SIZE&t;0x00000400&t;/* 1kB ATE RAM */
DECL|macro|BRIDGE_CONFIG_BASE
mdefine_line|#define BRIDGE_CONFIG_BASE&t;0x20000
DECL|macro|BRIDGE_CONFIG1_BASE
mdefine_line|#define BRIDGE_CONFIG1_BASE&t;0x28000
DECL|macro|BRIDGE_CONFIG_END
mdefine_line|#define BRIDGE_CONFIG_END&t;0x30000
DECL|macro|BRIDGE_CONFIG_SLOT_SIZE
mdefine_line|#define BRIDGE_CONFIG_SLOT_SIZE 0x1000
DECL|macro|BRIDGE_SSRAM_512K
mdefine_line|#define BRIDGE_SSRAM_512K&t;0x00080000&t;/* 512kB */
DECL|macro|BRIDGE_SSRAM_128K
mdefine_line|#define BRIDGE_SSRAM_128K&t;0x00020000&t;/* 128kB */
DECL|macro|BRIDGE_SSRAM_64K
mdefine_line|#define BRIDGE_SSRAM_64K&t;0x00010000&t;/* 64kB */
DECL|macro|BRIDGE_SSRAM_0K
mdefine_line|#define BRIDGE_SSRAM_0K&t;&t;0x00000000&t;/* 0kB */
multiline_comment|/* ========================================================================&n; *    Bridge address map&n; */
macro_line|#if defined(_LANGUAGE_C) || defined(_LANGUAGE_C_PLUS_PLUS)
multiline_comment|/*&n; * All accesses to bridge hardware registers must be done&n; * using 32-bit loads and stores.&n; */
DECL|typedef|bridgereg_t
r_typedef
id|u32
id|bridgereg_t
suffix:semicolon
DECL|typedef|bridge_ate_t
r_typedef
id|u64
id|bridge_ate_t
suffix:semicolon
multiline_comment|/* pointers to bridge ATEs&n; * are always &quot;pointer to volatile&quot;&n; */
DECL|typedef|bridge_ate_p
r_typedef
r_volatile
id|bridge_ate_t
op_star
id|bridge_ate_p
suffix:semicolon
multiline_comment|/*&n; * It is generally preferred that hardware registers on the bridge&n; * are located from C code via this structure.&n; *&n; * Generated from Bridge spec dated 04oct95&n; */
DECL|struct|bridge_s
r_typedef
r_volatile
r_struct
id|bridge_s
(brace
multiline_comment|/* Local Registers&t;&t;&t;       0x000000-0x00FFFF */
multiline_comment|/* standard widget configuration&t;       0x000000-0x000057 */
DECL|member|b_widget
id|widget_cfg_t
id|b_widget
suffix:semicolon
multiline_comment|/* 0x000000 */
multiline_comment|/* helper fieldnames for accessing bridge widget */
DECL|macro|b_wid_id
mdefine_line|#define b_wid_id&t;&t;&t;b_widget.w_id
DECL|macro|b_wid_stat
mdefine_line|#define b_wid_stat&t;&t;&t;b_widget.w_status
DECL|macro|b_wid_err_upper
mdefine_line|#define b_wid_err_upper&t;&t;&t;b_widget.w_err_upper_addr
DECL|macro|b_wid_err_lower
mdefine_line|#define b_wid_err_lower&t;&t;&t;b_widget.w_err_lower_addr
DECL|macro|b_wid_control
mdefine_line|#define b_wid_control&t;&t;&t;b_widget.w_control
DECL|macro|b_wid_req_timeout
mdefine_line|#define b_wid_req_timeout&t;&t;b_widget.w_req_timeout
DECL|macro|b_wid_int_upper
mdefine_line|#define b_wid_int_upper&t;&t;&t;b_widget.w_intdest_upper_addr
DECL|macro|b_wid_int_lower
mdefine_line|#define b_wid_int_lower&t;&t;&t;b_widget.w_intdest_lower_addr
DECL|macro|b_wid_err_cmdword
mdefine_line|#define b_wid_err_cmdword&t;&t;b_widget.w_err_cmd_word
DECL|macro|b_wid_llp
mdefine_line|#define b_wid_llp&t;&t;&t;b_widget.w_llp_cfg
DECL|macro|b_wid_tflush
mdefine_line|#define b_wid_tflush&t;&t;&t;b_widget.w_tflush
multiline_comment|/* bridge-specific widget configuration&t;0x000058-0x00007F */
DECL|member|_pad_000058
id|bridgereg_t
id|_pad_000058
suffix:semicolon
DECL|member|b_wid_aux_err
id|bridgereg_t
id|b_wid_aux_err
suffix:semicolon
multiline_comment|/* 0x00005C */
DECL|member|_pad_000060
id|bridgereg_t
id|_pad_000060
suffix:semicolon
DECL|member|b_wid_resp_upper
id|bridgereg_t
id|b_wid_resp_upper
suffix:semicolon
multiline_comment|/* 0x000064 */
DECL|member|_pad_000068
id|bridgereg_t
id|_pad_000068
suffix:semicolon
DECL|member|b_wid_resp_lower
id|bridgereg_t
id|b_wid_resp_lower
suffix:semicolon
multiline_comment|/* 0x00006C */
DECL|member|_pad_000070
id|bridgereg_t
id|_pad_000070
suffix:semicolon
DECL|member|b_wid_tst_pin_ctrl
id|bridgereg_t
id|b_wid_tst_pin_ctrl
suffix:semicolon
multiline_comment|/* 0x000074 */
DECL|member|_pad_000078
id|bridgereg_t
id|_pad_000078
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* PMU &amp; Map 0x000080-0x00008F */
DECL|member|_pad_000080
id|bridgereg_t
id|_pad_000080
suffix:semicolon
DECL|member|b_dir_map
id|bridgereg_t
id|b_dir_map
suffix:semicolon
multiline_comment|/* 0x000084 */
DECL|member|_pad_000088
id|bridgereg_t
id|_pad_000088
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* SSRAM 0x000090-0x00009F */
DECL|member|_pad_000090
id|bridgereg_t
id|_pad_000090
suffix:semicolon
DECL|member|b_ram_perr
id|bridgereg_t
id|b_ram_perr
suffix:semicolon
multiline_comment|/* 0x000094 */
DECL|member|_pad_000098
id|bridgereg_t
id|_pad_000098
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Arbitration 0x0000A0-0x0000AF */
DECL|member|_pad_0000A0
id|bridgereg_t
id|_pad_0000A0
suffix:semicolon
DECL|member|b_arb
id|bridgereg_t
id|b_arb
suffix:semicolon
multiline_comment|/* 0x0000A4 */
DECL|member|_pad_0000A8
id|bridgereg_t
id|_pad_0000A8
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Number In A Can 0x0000B0-0x0000BF */
DECL|member|_pad_0000B0
id|bridgereg_t
id|_pad_0000B0
suffix:semicolon
DECL|member|b_nic
id|bridgereg_t
id|b_nic
suffix:semicolon
multiline_comment|/* 0x0000B4 */
DECL|member|_pad_0000B8
id|bridgereg_t
id|_pad_0000B8
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* PCI/GIO 0x0000C0-0x0000FF */
DECL|member|_pad_0000C0
id|bridgereg_t
id|_pad_0000C0
suffix:semicolon
DECL|member|b_bus_timeout
id|bridgereg_t
id|b_bus_timeout
suffix:semicolon
multiline_comment|/* 0x0000C4 */
DECL|macro|b_pci_bus_timeout
mdefine_line|#define b_pci_bus_timeout b_bus_timeout
DECL|member|_pad_0000C8
id|bridgereg_t
id|_pad_0000C8
suffix:semicolon
DECL|member|b_pci_cfg
id|bridgereg_t
id|b_pci_cfg
suffix:semicolon
multiline_comment|/* 0x0000CC */
DECL|member|_pad_0000D0
id|bridgereg_t
id|_pad_0000D0
suffix:semicolon
DECL|member|b_pci_err_upper
id|bridgereg_t
id|b_pci_err_upper
suffix:semicolon
multiline_comment|/* 0x0000D4 */
DECL|member|_pad_0000D8
id|bridgereg_t
id|_pad_0000D8
suffix:semicolon
DECL|member|b_pci_err_lower
id|bridgereg_t
id|b_pci_err_lower
suffix:semicolon
multiline_comment|/* 0x0000DC */
DECL|member|_pad_0000E0
id|bridgereg_t
id|_pad_0000E0
(braket
l_int|8
)braket
suffix:semicolon
DECL|macro|b_gio_err_lower
mdefine_line|#define b_gio_err_lower b_pci_err_lower
DECL|macro|b_gio_err_upper
mdefine_line|#define b_gio_err_upper b_pci_err_upper
multiline_comment|/* Interrupt 0x000100-0x0001FF */
DECL|member|_pad_000100
id|bridgereg_t
id|_pad_000100
suffix:semicolon
DECL|member|b_int_status
id|bridgereg_t
id|b_int_status
suffix:semicolon
multiline_comment|/* 0x000104 */
DECL|member|_pad_000108
id|bridgereg_t
id|_pad_000108
suffix:semicolon
DECL|member|b_int_enable
id|bridgereg_t
id|b_int_enable
suffix:semicolon
multiline_comment|/* 0x00010C */
DECL|member|_pad_000110
id|bridgereg_t
id|_pad_000110
suffix:semicolon
DECL|member|b_int_rst_stat
id|bridgereg_t
id|b_int_rst_stat
suffix:semicolon
multiline_comment|/* 0x000114 */
DECL|member|_pad_000118
id|bridgereg_t
id|_pad_000118
suffix:semicolon
DECL|member|b_int_mode
id|bridgereg_t
id|b_int_mode
suffix:semicolon
multiline_comment|/* 0x00011C */
DECL|member|_pad_000120
id|bridgereg_t
id|_pad_000120
suffix:semicolon
DECL|member|b_int_device
id|bridgereg_t
id|b_int_device
suffix:semicolon
multiline_comment|/* 0x000124 */
DECL|member|_pad_000128
id|bridgereg_t
id|_pad_000128
suffix:semicolon
DECL|member|b_int_host_err
id|bridgereg_t
id|b_int_host_err
suffix:semicolon
multiline_comment|/* 0x00012C */
r_struct
(brace
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
multiline_comment|/* 0x0001{30,,,68} */
DECL|member|addr
id|bridgereg_t
id|addr
suffix:semicolon
multiline_comment|/* 0x0001{34,,,6C} */
DECL|member|b_int_addr
)brace
id|b_int_addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x000130 */
DECL|member|_pad_000170
id|bridgereg_t
id|_pad_000170
(braket
l_int|36
)braket
suffix:semicolon
multiline_comment|/* Device 0x000200-0x0003FF */
r_struct
(brace
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
multiline_comment|/* 0x0002{00,,,38} */
DECL|member|reg
id|bridgereg_t
id|reg
suffix:semicolon
multiline_comment|/* 0x0002{04,,,3C} */
DECL|member|b_device
)brace
id|b_device
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x000200 */
r_struct
(brace
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
multiline_comment|/* 0x0002{40,,,78} */
DECL|member|reg
id|bridgereg_t
id|reg
suffix:semicolon
multiline_comment|/* 0x0002{44,,,7C} */
DECL|member|b_wr_req_buf
)brace
id|b_wr_req_buf
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x000240 */
r_struct
(brace
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
multiline_comment|/* 0x0002{80,,,88} */
DECL|member|reg
id|bridgereg_t
id|reg
suffix:semicolon
multiline_comment|/* 0x0002{84,,,8C} */
DECL|member|b_rrb_map
)brace
id|b_rrb_map
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x000280 */
DECL|macro|b_even_resp
mdefine_line|#define&t;b_even_resp&t;b_rrb_map[0].reg&t;&t;/* 0x000284 */
DECL|macro|b_odd_resp
mdefine_line|#define&t;b_odd_resp&t;b_rrb_map[1].reg&t;&t;/* 0x00028C */
DECL|member|_pad_000290
id|bridgereg_t
id|_pad_000290
suffix:semicolon
DECL|member|b_resp_status
id|bridgereg_t
id|b_resp_status
suffix:semicolon
multiline_comment|/* 0x000294 */
DECL|member|_pad_000298
id|bridgereg_t
id|_pad_000298
suffix:semicolon
DECL|member|b_resp_clear
id|bridgereg_t
id|b_resp_clear
suffix:semicolon
multiline_comment|/* 0x00029C */
DECL|member|_pad_0002A0
id|bridgereg_t
id|_pad_0002A0
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|_pad_000300
r_char
id|_pad_000300
(braket
l_int|0x10000
op_minus
l_int|0x000300
)braket
suffix:semicolon
multiline_comment|/* Internal Address Translation Entry RAM 0x010000-0x0103FF */
r_union
(brace
DECL|member|wr
id|bridge_ate_t
id|wr
suffix:semicolon
multiline_comment|/* write-only */
r_struct
(brace
DECL|member|_p_pad
id|bridgereg_t
id|_p_pad
suffix:semicolon
DECL|member|rd
id|bridgereg_t
id|rd
suffix:semicolon
multiline_comment|/* read-only */
DECL|member|hi
)brace
id|hi
suffix:semicolon
DECL|member|b_int_ate_ram
)brace
id|b_int_ate_ram
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|_pad_010400
r_char
id|_pad_010400
(braket
l_int|0x11000
op_minus
l_int|0x010400
)braket
suffix:semicolon
multiline_comment|/* Internal Address Translation Entry RAM LOW 0x011000-0x0113FF */
r_struct
(brace
DECL|member|_p_pad
id|bridgereg_t
id|_p_pad
suffix:semicolon
DECL|member|rd
id|bridgereg_t
id|rd
suffix:semicolon
multiline_comment|/* read-only */
DECL|member|b_int_ate_ram_lo
)brace
id|b_int_ate_ram_lo
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|_pad_011400
r_char
id|_pad_011400
(braket
l_int|0x20000
op_minus
l_int|0x011400
)braket
suffix:semicolon
multiline_comment|/* PCI Device Configuration Spaces 0x020000-0x027FFF */
r_union
(brace
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|u8
id|c
(braket
l_int|0x1000
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
id|u16
id|s
(braket
l_int|0x1000
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
id|u32
id|l
(braket
l_int|0x1000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
id|u64
id|d
(braket
l_int|0x1000
op_div
l_int|8
)braket
suffix:semicolon
r_union
(brace
DECL|member|c
id|u8
id|c
(braket
l_int|0x100
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
id|u16
id|s
(braket
l_int|0x100
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
id|u32
id|l
(braket
l_int|0x100
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
id|u64
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
DECL|member|b_type0_cfg_dev
)brace
id|b_type0_cfg_dev
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x020000 */
multiline_comment|/* PCI Type 1 Configuration Space 0x028000-0x028FFF */
r_union
(brace
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|u8
id|c
(braket
l_int|0x1000
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
id|u16
id|s
(braket
l_int|0x1000
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
id|u32
id|l
(braket
l_int|0x1000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
id|u64
id|d
(braket
l_int|0x1000
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|b_type1_cfg
)brace
id|b_type1_cfg
suffix:semicolon
multiline_comment|/* 0x028000-0x029000 */
DECL|member|_pad_029000
r_char
id|_pad_029000
(braket
l_int|0x007000
)braket
suffix:semicolon
multiline_comment|/* 0x029000-0x030000 */
multiline_comment|/* PCI Interrupt Acknowledge Cycle 0x030000 */
r_union
(brace
DECL|member|c
id|u8
id|c
(braket
l_int|8
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
id|u16
id|s
(braket
l_int|8
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
id|u32
id|l
(braket
l_int|8
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
id|u64
id|d
(braket
l_int|8
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|b_pci_iack
)brace
id|b_pci_iack
suffix:semicolon
multiline_comment|/* 0x030000 */
DECL|member|_pad_030007
id|u8
id|_pad_030007
(braket
l_int|0x04fff8
)braket
suffix:semicolon
multiline_comment|/* 0x030008-0x07FFFF */
multiline_comment|/* External Address Translation Entry RAM 0x080000-0x0FFFFF */
DECL|member|b_ext_ate_ram
id|bridge_ate_t
id|b_ext_ate_ram
(braket
l_int|0x10000
)braket
suffix:semicolon
multiline_comment|/* Reserved 0x100000-0x1FFFFF */
DECL|member|_pad_100000
r_char
id|_pad_100000
(braket
l_int|0x200000
op_minus
l_int|0x100000
)braket
suffix:semicolon
multiline_comment|/* PCI/GIO Device Spaces 0x200000-0xBFFFFF */
r_union
(brace
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|u8
id|c
(braket
l_int|0x100000
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
id|u16
id|s
(braket
l_int|0x100000
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
id|u32
id|l
(braket
l_int|0x100000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
id|u64
id|d
(braket
l_int|0x100000
op_div
l_int|8
)braket
suffix:semicolon
DECL|member|b_devio_raw
)brace
id|b_devio_raw
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* 0x200000 */
multiline_comment|/* b_devio macro is a bit strange; it reflects the&n;&t; * fact that the Bridge ASIC provides 2M for the&n;&t; * first two DevIO windows and 1M for the other six.&n;&t; */
DECL|macro|b_devio
mdefine_line|#define b_devio(n)&t;b_devio_raw[((n)&lt;2)?(n*2):(n+2)]
multiline_comment|/* External Flash Proms 1,0 0xC00000-0xFFFFFF */
r_union
(brace
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|u8
id|c
(braket
l_int|0x400000
op_div
l_int|1
)braket
suffix:semicolon
multiline_comment|/* read-only */
DECL|member|s
id|u16
id|s
(braket
l_int|0x400000
op_div
l_int|2
)braket
suffix:semicolon
multiline_comment|/* read-write */
DECL|member|l
id|u32
id|l
(braket
l_int|0x400000
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* read-only */
DECL|member|d
id|u64
id|d
(braket
l_int|0x400000
op_div
l_int|8
)braket
suffix:semicolon
multiline_comment|/* read-only */
DECL|member|b_external_flash
)brace
id|b_external_flash
suffix:semicolon
multiline_comment|/* 0xC00000 */
DECL|typedef|bridge_t
)brace
id|bridge_t
suffix:semicolon
multiline_comment|/*&n; * Field formats for Error Command Word and Auxillary Error Command Word&n; * of bridge.&n; */
DECL|struct|bridge_err_cmdword_s
r_typedef
r_struct
id|bridge_err_cmdword_s
(brace
r_union
(brace
DECL|member|cmd_word
id|u32
id|cmd_word
suffix:semicolon
r_struct
(brace
DECL|member|didn
id|u32
id|didn
suffix:colon
l_int|4
comma
multiline_comment|/* Destination ID */
DECL|member|sidn
id|sidn
suffix:colon
l_int|4
comma
multiline_comment|/* Source ID&t;  */
DECL|member|pactyp
id|pactyp
suffix:colon
l_int|4
comma
multiline_comment|/* Packet type&t;  */
DECL|member|tnum
id|tnum
suffix:colon
l_int|5
comma
multiline_comment|/* Trans Number&t;  */
DECL|member|coh
id|coh
suffix:colon
l_int|1
comma
multiline_comment|/* Coh Transacti  */
DECL|member|ds
id|ds
suffix:colon
l_int|2
comma
multiline_comment|/* Data size&t;  */
DECL|member|gbr
id|gbr
suffix:colon
l_int|1
comma
multiline_comment|/* GBR enable&t;  */
DECL|member|vbpm
id|vbpm
suffix:colon
l_int|1
comma
multiline_comment|/* VBPM message&t;  */
DECL|member|error
id|error
suffix:colon
l_int|1
comma
multiline_comment|/* Error occurred  */
DECL|member|barr
id|barr
suffix:colon
l_int|1
comma
multiline_comment|/* Barrier op&t;  */
DECL|member|rsvd
id|rsvd
suffix:colon
l_int|8
suffix:semicolon
DECL|member|berr_st
)brace
id|berr_st
suffix:semicolon
DECL|member|berr_un
)brace
id|berr_un
suffix:semicolon
DECL|typedef|bridge_err_cmdword_t
)brace
id|bridge_err_cmdword_t
suffix:semicolon
DECL|macro|berr_field
mdefine_line|#define berr_field&t;berr_un.berr_st
macro_line|#endif&t;/* LANGUAGE_C */
multiline_comment|/*&n; * The values of these macros can and should be crosschecked&n; * regularly against the offsets of the like-named fields&n; * within the &quot;bridge_t&quot; structure above.&n; */
multiline_comment|/* Byte offset macros for Bridge internal registers */
DECL|macro|BRIDGE_WID_ID
mdefine_line|#define BRIDGE_WID_ID&t;&t;WIDGET_ID
DECL|macro|BRIDGE_WID_STAT
mdefine_line|#define BRIDGE_WID_STAT&t;&t;WIDGET_STATUS
DECL|macro|BRIDGE_WID_ERR_UPPER
mdefine_line|#define BRIDGE_WID_ERR_UPPER&t;WIDGET_ERR_UPPER_ADDR
DECL|macro|BRIDGE_WID_ERR_LOWER
mdefine_line|#define BRIDGE_WID_ERR_LOWER&t;WIDGET_ERR_LOWER_ADDR
DECL|macro|BRIDGE_WID_CONTROL
mdefine_line|#define BRIDGE_WID_CONTROL&t;WIDGET_CONTROL
DECL|macro|BRIDGE_WID_REQ_TIMEOUT
mdefine_line|#define BRIDGE_WID_REQ_TIMEOUT&t;WIDGET_REQ_TIMEOUT
DECL|macro|BRIDGE_WID_INT_UPPER
mdefine_line|#define BRIDGE_WID_INT_UPPER&t;WIDGET_INTDEST_UPPER_ADDR
DECL|macro|BRIDGE_WID_INT_LOWER
mdefine_line|#define BRIDGE_WID_INT_LOWER&t;WIDGET_INTDEST_LOWER_ADDR
DECL|macro|BRIDGE_WID_ERR_CMDWORD
mdefine_line|#define BRIDGE_WID_ERR_CMDWORD&t;WIDGET_ERR_CMD_WORD
DECL|macro|BRIDGE_WID_LLP
mdefine_line|#define BRIDGE_WID_LLP&t;&t;WIDGET_LLP_CFG
DECL|macro|BRIDGE_WID_TFLUSH
mdefine_line|#define BRIDGE_WID_TFLUSH&t;WIDGET_TFLUSH
DECL|macro|BRIDGE_WID_AUX_ERR
mdefine_line|#define BRIDGE_WID_AUX_ERR&t;0x00005C&t;/* Aux Error Command Word */
DECL|macro|BRIDGE_WID_RESP_UPPER
mdefine_line|#define BRIDGE_WID_RESP_UPPER&t;0x000064&t;/* Response Buf Upper Addr */
DECL|macro|BRIDGE_WID_RESP_LOWER
mdefine_line|#define BRIDGE_WID_RESP_LOWER&t;0x00006C&t;/* Response Buf Lower Addr */
DECL|macro|BRIDGE_WID_TST_PIN_CTRL
mdefine_line|#define BRIDGE_WID_TST_PIN_CTRL 0x000074&t;/* Test pin control */
DECL|macro|BRIDGE_DIR_MAP
mdefine_line|#define BRIDGE_DIR_MAP&t;&t;0x000084&t;/* Direct Map reg */
DECL|macro|BRIDGE_RAM_PERR
mdefine_line|#define BRIDGE_RAM_PERR&t;&t;0x000094&t;/* SSRAM Parity Error */
DECL|macro|BRIDGE_ARB
mdefine_line|#define BRIDGE_ARB&t;&t;0x0000A4&t;/* Arbitration Priority reg */
DECL|macro|BRIDGE_NIC
mdefine_line|#define BRIDGE_NIC&t;&t;0x0000B4&t;/* Number In A Can */
DECL|macro|BRIDGE_BUS_TIMEOUT
mdefine_line|#define BRIDGE_BUS_TIMEOUT&t;0x0000C4&t;/* Bus Timeout Register */
DECL|macro|BRIDGE_PCI_BUS_TIMEOUT
mdefine_line|#define BRIDGE_PCI_BUS_TIMEOUT&t;BRIDGE_BUS_TIMEOUT
DECL|macro|BRIDGE_PCI_CFG
mdefine_line|#define BRIDGE_PCI_CFG&t;&t;0x0000CC&t;/* PCI Type 1 Config reg */
DECL|macro|BRIDGE_PCI_ERR_UPPER
mdefine_line|#define BRIDGE_PCI_ERR_UPPER&t;0x0000D4&t;/* PCI error Upper Addr */
DECL|macro|BRIDGE_PCI_ERR_LOWER
mdefine_line|#define BRIDGE_PCI_ERR_LOWER&t;0x0000DC&t;/* PCI error Lower Addr */
DECL|macro|BRIDGE_INT_STATUS
mdefine_line|#define BRIDGE_INT_STATUS&t;0x000104&t;/* Interrupt Status */
DECL|macro|BRIDGE_INT_ENABLE
mdefine_line|#define BRIDGE_INT_ENABLE&t;0x00010C&t;/* Interrupt Enables */
DECL|macro|BRIDGE_INT_RST_STAT
mdefine_line|#define BRIDGE_INT_RST_STAT&t;0x000114&t;/* Reset Intr Status */
DECL|macro|BRIDGE_INT_MODE
mdefine_line|#define BRIDGE_INT_MODE&t;&t;0x00011C&t;/* Interrupt Mode */
DECL|macro|BRIDGE_INT_DEVICE
mdefine_line|#define BRIDGE_INT_DEVICE&t;0x000124&t;/* Interrupt Device */
DECL|macro|BRIDGE_INT_HOST_ERR
mdefine_line|#define BRIDGE_INT_HOST_ERR&t;0x00012C&t;/* Host Error Field */
DECL|macro|BRIDGE_INT_ADDR0
mdefine_line|#define BRIDGE_INT_ADDR0&t;0x000134&t;/* Host Address Reg */
DECL|macro|BRIDGE_INT_ADDR_OFF
mdefine_line|#define BRIDGE_INT_ADDR_OFF&t;0x000008&t;/* Host Addr offset (1..7) */
DECL|macro|BRIDGE_INT_ADDR
mdefine_line|#define BRIDGE_INT_ADDR(x)&t;(BRIDGE_INT_ADDR0+(x)*BRIDGE_INT_ADDR_OFF)
DECL|macro|BRIDGE_DEVICE0
mdefine_line|#define BRIDGE_DEVICE0&t;&t;0x000204&t;/* Device 0 */
DECL|macro|BRIDGE_DEVICE_OFF
mdefine_line|#define BRIDGE_DEVICE_OFF&t;0x000008&t;/* Device offset (1..7) */
DECL|macro|BRIDGE_DEVICE
mdefine_line|#define BRIDGE_DEVICE(x)&t;(BRIDGE_DEVICE0+(x)*BRIDGE_DEVICE_OFF)
DECL|macro|BRIDGE_WR_REQ_BUF0
mdefine_line|#define BRIDGE_WR_REQ_BUF0&t;0x000244&t;/* Write Request Buffer 0 */
DECL|macro|BRIDGE_WR_REQ_BUF_OFF
mdefine_line|#define BRIDGE_WR_REQ_BUF_OFF&t;0x000008&t;/* Buffer Offset (1..7) */
DECL|macro|BRIDGE_WR_REQ_BUF
mdefine_line|#define BRIDGE_WR_REQ_BUF(x)&t;(BRIDGE_WR_REQ_BUF0+(x)*BRIDGE_WR_REQ_BUF_OFF)
DECL|macro|BRIDGE_EVEN_RESP
mdefine_line|#define BRIDGE_EVEN_RESP&t;0x000284&t;/* Even Device Response Buf */
DECL|macro|BRIDGE_ODD_RESP
mdefine_line|#define BRIDGE_ODD_RESP&t;&t;0x00028C&t;/* Odd Device Response Buf */
DECL|macro|BRIDGE_RESP_STATUS
mdefine_line|#define BRIDGE_RESP_STATUS&t;0x000294&t;/* Read Response Status reg */
DECL|macro|BRIDGE_RESP_CLEAR
mdefine_line|#define BRIDGE_RESP_CLEAR&t;0x00029C&t;/* Read Response Clear reg */
multiline_comment|/* Byte offset macros for Bridge I/O space */
DECL|macro|BRIDGE_ATE_RAM
mdefine_line|#define BRIDGE_ATE_RAM&t;&t;0x00010000&t;/* Internal Addr Xlat Ram */
DECL|macro|BRIDGE_TYPE0_CFG_DEV0
mdefine_line|#define BRIDGE_TYPE0_CFG_DEV0&t;0x00020000&t;/* Type 0 Cfg, Device 0 */
DECL|macro|BRIDGE_TYPE0_CFG_SLOT_OFF
mdefine_line|#define BRIDGE_TYPE0_CFG_SLOT_OFF&t;0x00001000&t;/* Type 0 Cfg Slot Offset (1..7) */
DECL|macro|BRIDGE_TYPE0_CFG_FUNC_OFF
mdefine_line|#define BRIDGE_TYPE0_CFG_FUNC_OFF&t;0x00000100&t;/* Type 0 Cfg Func Offset (1..7) */
DECL|macro|BRIDGE_TYPE0_CFG_DEV
mdefine_line|#define BRIDGE_TYPE0_CFG_DEV(s)&t;&t;(BRIDGE_TYPE0_CFG_DEV0+&bslash;&n;&t;&t;&t;&t;&t; (s)*BRIDGE_TYPE0_CFG_SLOT_OFF)
DECL|macro|BRIDGE_TYPE0_CFG_DEVF
mdefine_line|#define BRIDGE_TYPE0_CFG_DEVF(s,f)&t;(BRIDGE_TYPE0_CFG_DEV0+&bslash;&n;&t;&t;&t;&t;&t; (s)*BRIDGE_TYPE0_CFG_SLOT_OFF+&bslash;&n;&t;&t;&t;&t;&t; (f)*BRIDGE_TYPE0_CFG_FUNC_OFF)
DECL|macro|BRIDGE_TYPE1_CFG
mdefine_line|#define BRIDGE_TYPE1_CFG&t;0x00028000&t;/* Type 1 Cfg space */
DECL|macro|BRIDGE_PCI_IACK
mdefine_line|#define BRIDGE_PCI_IACK&t;&t;0x00030000&t;/* PCI Interrupt Ack */
DECL|macro|BRIDGE_EXT_SSRAM
mdefine_line|#define BRIDGE_EXT_SSRAM&t;0x00080000&t;/* Extern SSRAM (ATE) */
multiline_comment|/* Byte offset macros for Bridge device IO spaces */
DECL|macro|BRIDGE_DEV_CNT
mdefine_line|#define BRIDGE_DEV_CNT&t;&t;8&t;/* Up to 8 devices per bridge */
DECL|macro|BRIDGE_DEVIO0
mdefine_line|#define BRIDGE_DEVIO0&t;&t;0x00200000&t;/* Device IO 0 Addr */
DECL|macro|BRIDGE_DEVIO1
mdefine_line|#define BRIDGE_DEVIO1&t;&t;0x00400000&t;/* Device IO 1 Addr */
DECL|macro|BRIDGE_DEVIO2
mdefine_line|#define BRIDGE_DEVIO2&t;&t;0x00600000&t;/* Device IO 2 Addr */
DECL|macro|BRIDGE_DEVIO_OFF
mdefine_line|#define BRIDGE_DEVIO_OFF&t;0x00100000&t;/* Device IO Offset (3..7) */
DECL|macro|BRIDGE_DEVIO_2MB
mdefine_line|#define BRIDGE_DEVIO_2MB&t;0x00200000&t;/* Device IO Offset (0..1) */
DECL|macro|BRIDGE_DEVIO_1MB
mdefine_line|#define BRIDGE_DEVIO_1MB&t;0x00100000&t;/* Device IO Offset (2..7) */
DECL|macro|BRIDGE_DEVIO
mdefine_line|#define BRIDGE_DEVIO(x)&t;&t;((x)&lt;=1 ? BRIDGE_DEVIO0+(x)*BRIDGE_DEVIO_2MB : BRIDGE_DEVIO2+((x)-2)*BRIDGE_DEVIO_1MB)
DECL|macro|BRIDGE_EXTERNAL_FLASH
mdefine_line|#define BRIDGE_EXTERNAL_FLASH&t;0x00C00000&t;/* External Flash PROMS */
multiline_comment|/* ========================================================================&n; *    Bridge register bit field definitions&n; */
multiline_comment|/* Widget part number of bridge */
DECL|macro|BRIDGE_WIDGET_PART_NUM
mdefine_line|#define BRIDGE_WIDGET_PART_NUM&t;&t;0xc002
multiline_comment|/* Manufacturer of bridge */
DECL|macro|BRIDGE_WIDGET_MFGR_NUM
mdefine_line|#define BRIDGE_WIDGET_MFGR_NUM&t;&t;0x036
multiline_comment|/* Revision numbers for known Bridge revisions */
DECL|macro|BRIDGE_REV_A
mdefine_line|#define BRIDGE_REV_A&t;&t;&t;0x1
DECL|macro|BRIDGE_REV_B
mdefine_line|#define BRIDGE_REV_B&t;&t;&t;0x2
DECL|macro|BRIDGE_REV_C
mdefine_line|#define BRIDGE_REV_C&t;&t;&t;0x3
DECL|macro|BRIDGE_REV_D
mdefine_line|#define&t;BRIDGE_REV_D&t;&t;&t;0x4
multiline_comment|/* Bridge widget status register bits definition */
DECL|macro|BRIDGE_STAT_LLP_REC_CNT
mdefine_line|#define BRIDGE_STAT_LLP_REC_CNT&t;&t;(0xFFu &lt;&lt; 24)
DECL|macro|BRIDGE_STAT_LLP_TX_CNT
mdefine_line|#define BRIDGE_STAT_LLP_TX_CNT&t;&t;(0xFF &lt;&lt; 16)
DECL|macro|BRIDGE_STAT_FLASH_SELECT
mdefine_line|#define BRIDGE_STAT_FLASH_SELECT&t;(0x1 &lt;&lt; 6)
DECL|macro|BRIDGE_STAT_PCI_GIO_N
mdefine_line|#define BRIDGE_STAT_PCI_GIO_N&t;&t;(0x1 &lt;&lt; 5)
DECL|macro|BRIDGE_STAT_PENDING
mdefine_line|#define BRIDGE_STAT_PENDING&t;&t;(0x1F &lt;&lt; 0)
multiline_comment|/* Bridge widget control register bits definition */
DECL|macro|BRIDGE_CTRL_FLASH_WR_EN
mdefine_line|#define BRIDGE_CTRL_FLASH_WR_EN&t;&t;(0x1ul &lt;&lt; 31)
DECL|macro|BRIDGE_CTRL_EN_CLK50
mdefine_line|#define BRIDGE_CTRL_EN_CLK50&t;&t;(0x1 &lt;&lt; 30)
DECL|macro|BRIDGE_CTRL_EN_CLK40
mdefine_line|#define BRIDGE_CTRL_EN_CLK40&t;&t;(0x1 &lt;&lt; 29)
DECL|macro|BRIDGE_CTRL_EN_CLK33
mdefine_line|#define BRIDGE_CTRL_EN_CLK33&t;&t;(0x1 &lt;&lt; 28)
DECL|macro|BRIDGE_CTRL_RST
mdefine_line|#define BRIDGE_CTRL_RST(n)&t;&t;((n) &lt;&lt; 24)
DECL|macro|BRIDGE_CTRL_RST_MASK
mdefine_line|#define BRIDGE_CTRL_RST_MASK&t;&t;(BRIDGE_CTRL_RST(0xF))
DECL|macro|BRIDGE_CTRL_RST_PIN
mdefine_line|#define BRIDGE_CTRL_RST_PIN(x)&t;&t;(BRIDGE_CTRL_RST(0x1 &lt;&lt; (x)))
DECL|macro|BRIDGE_CTRL_IO_SWAP
mdefine_line|#define BRIDGE_CTRL_IO_SWAP&t;&t;(0x1 &lt;&lt; 23)
DECL|macro|BRIDGE_CTRL_MEM_SWAP
mdefine_line|#define BRIDGE_CTRL_MEM_SWAP&t;&t;(0x1 &lt;&lt; 22)
DECL|macro|BRIDGE_CTRL_PAGE_SIZE
mdefine_line|#define BRIDGE_CTRL_PAGE_SIZE&t;&t;(0x1 &lt;&lt; 21)
DECL|macro|BRIDGE_CTRL_SS_PAR_BAD
mdefine_line|#define BRIDGE_CTRL_SS_PAR_BAD&t;&t;(0x1 &lt;&lt; 20)
DECL|macro|BRIDGE_CTRL_SS_PAR_EN
mdefine_line|#define BRIDGE_CTRL_SS_PAR_EN&t;&t;(0x1 &lt;&lt; 19)
DECL|macro|BRIDGE_CTRL_SSRAM_SIZE
mdefine_line|#define BRIDGE_CTRL_SSRAM_SIZE(n)&t;((n) &lt;&lt; 17)
DECL|macro|BRIDGE_CTRL_SSRAM_SIZE_MASK
mdefine_line|#define BRIDGE_CTRL_SSRAM_SIZE_MASK&t;(BRIDGE_CTRL_SSRAM_SIZE(0x3))
DECL|macro|BRIDGE_CTRL_SSRAM_512K
mdefine_line|#define BRIDGE_CTRL_SSRAM_512K&t;&t;(BRIDGE_CTRL_SSRAM_SIZE(0x3))
DECL|macro|BRIDGE_CTRL_SSRAM_128K
mdefine_line|#define BRIDGE_CTRL_SSRAM_128K&t;&t;(BRIDGE_CTRL_SSRAM_SIZE(0x2))
DECL|macro|BRIDGE_CTRL_SSRAM_64K
mdefine_line|#define BRIDGE_CTRL_SSRAM_64K&t;&t;(BRIDGE_CTRL_SSRAM_SIZE(0x1))
DECL|macro|BRIDGE_CTRL_SSRAM_1K
mdefine_line|#define BRIDGE_CTRL_SSRAM_1K&t;&t;(BRIDGE_CTRL_SSRAM_SIZE(0x0))
DECL|macro|BRIDGE_CTRL_F_BAD_PKT
mdefine_line|#define BRIDGE_CTRL_F_BAD_PKT&t;&t;(0x1 &lt;&lt; 16)
DECL|macro|BRIDGE_CTRL_LLP_XBAR_CRD
mdefine_line|#define BRIDGE_CTRL_LLP_XBAR_CRD(n)&t;((n) &lt;&lt; 12)
DECL|macro|BRIDGE_CTRL_LLP_XBAR_CRD_MASK
mdefine_line|#define BRIDGE_CTRL_LLP_XBAR_CRD_MASK&t;(BRIDGE_CTRL_LLP_XBAR_CRD(0xf))
DECL|macro|BRIDGE_CTRL_CLR_RLLP_CNT
mdefine_line|#define BRIDGE_CTRL_CLR_RLLP_CNT&t;(0x1 &lt;&lt; 11)
DECL|macro|BRIDGE_CTRL_CLR_TLLP_CNT
mdefine_line|#define BRIDGE_CTRL_CLR_TLLP_CNT&t;(0x1 &lt;&lt; 10)
DECL|macro|BRIDGE_CTRL_SYS_END
mdefine_line|#define BRIDGE_CTRL_SYS_END&t;&t;(0x1 &lt;&lt; 9)
DECL|macro|BRIDGE_CTRL_MAX_TRANS
mdefine_line|#define BRIDGE_CTRL_MAX_TRANS(n)&t;((n) &lt;&lt; 4)
DECL|macro|BRIDGE_CTRL_MAX_TRANS_MASK
mdefine_line|#define BRIDGE_CTRL_MAX_TRANS_MASK&t;(BRIDGE_CTRL_MAX_TRANS(0x1f))
DECL|macro|BRIDGE_CTRL_WIDGET_ID
mdefine_line|#define BRIDGE_CTRL_WIDGET_ID(n)&t;((n) &lt;&lt; 0)
DECL|macro|BRIDGE_CTRL_WIDGET_ID_MASK
mdefine_line|#define BRIDGE_CTRL_WIDGET_ID_MASK&t;(BRIDGE_CTRL_WIDGET_ID(0xf))
multiline_comment|/* Bridge Response buffer Error Upper Register bit fields definition */
DECL|macro|BRIDGE_RESP_ERRUPPR_DEVNUM_SHFT
mdefine_line|#define BRIDGE_RESP_ERRUPPR_DEVNUM_SHFT (20)
DECL|macro|BRIDGE_RESP_ERRUPPR_DEVNUM_MASK
mdefine_line|#define BRIDGE_RESP_ERRUPPR_DEVNUM_MASK (0x7 &lt;&lt; BRIDGE_RESP_ERRUPPR_DEVNUM_SHFT)
DECL|macro|BRIDGE_RESP_ERRUPPR_BUFNUM_SHFT
mdefine_line|#define BRIDGE_RESP_ERRUPPR_BUFNUM_SHFT (16)
DECL|macro|BRIDGE_RESP_ERRUPPR_BUFNUM_MASK
mdefine_line|#define BRIDGE_RESP_ERRUPPR_BUFNUM_MASK (0xF &lt;&lt; BRIDGE_RESP_ERRUPPR_BUFNUM_SHFT)
DECL|macro|BRIDGE_RESP_ERRRUPPR_BUFMASK
mdefine_line|#define BRIDGE_RESP_ERRRUPPR_BUFMASK&t;(0xFFFF)
DECL|macro|BRIDGE_RESP_ERRUPPR_BUFNUM
mdefine_line|#define BRIDGE_RESP_ERRUPPR_BUFNUM(x)&t;&bslash;&n;&t;&t;&t;(((x) &amp; BRIDGE_RESP_ERRUPPR_BUFNUM_MASK) &gt;&gt; &bslash;&n;&t;&t;&t;&t;BRIDGE_RESP_ERRUPPR_BUFNUM_SHFT)
DECL|macro|BRIDGE_RESP_ERRUPPR_DEVICE
mdefine_line|#define BRIDGE_RESP_ERRUPPR_DEVICE(x)&t;&bslash;&n;&t;&t;&t;(((x) &amp;&t; BRIDGE_RESP_ERRUPPR_DEVNUM_MASK) &gt;&gt; &bslash;&n;&t;&t;&t;&t; BRIDGE_RESP_ERRUPPR_DEVNUM_SHFT)
multiline_comment|/* Bridge direct mapping register bits definition */
DECL|macro|BRIDGE_DIRMAP_W_ID_SHFT
mdefine_line|#define BRIDGE_DIRMAP_W_ID_SHFT&t;&t;20
DECL|macro|BRIDGE_DIRMAP_W_ID
mdefine_line|#define BRIDGE_DIRMAP_W_ID&t;&t;(0xf &lt;&lt; BRIDGE_DIRMAP_W_ID_SHFT)
DECL|macro|BRIDGE_DIRMAP_RMF_64
mdefine_line|#define BRIDGE_DIRMAP_RMF_64&t;&t;(0x1 &lt;&lt; 18)
DECL|macro|BRIDGE_DIRMAP_ADD512
mdefine_line|#define BRIDGE_DIRMAP_ADD512&t;&t;(0x1 &lt;&lt; 17)
DECL|macro|BRIDGE_DIRMAP_OFF
mdefine_line|#define BRIDGE_DIRMAP_OFF&t;&t;(0x1ffff &lt;&lt; 0)
DECL|macro|BRIDGE_DIRMAP_OFF_ADDRSHFT
mdefine_line|#define BRIDGE_DIRMAP_OFF_ADDRSHFT&t;(31)&t;/* lsbit of DIRMAP_OFF is xtalk address bit 31 */
multiline_comment|/* Bridge Arbitration register bits definition */
DECL|macro|BRIDGE_ARB_REQ_WAIT_TICK
mdefine_line|#define BRIDGE_ARB_REQ_WAIT_TICK(x)&t;((x) &lt;&lt; 16)
DECL|macro|BRIDGE_ARB_REQ_WAIT_TICK_MASK
mdefine_line|#define BRIDGE_ARB_REQ_WAIT_TICK_MASK&t;BRIDGE_ARB_REQ_WAIT_TICK(0x3)
DECL|macro|BRIDGE_ARB_REQ_WAIT_EN
mdefine_line|#define BRIDGE_ARB_REQ_WAIT_EN(x)&t;((x) &lt;&lt; 8)
DECL|macro|BRIDGE_ARB_REQ_WAIT_EN_MASK
mdefine_line|#define BRIDGE_ARB_REQ_WAIT_EN_MASK&t;BRIDGE_ARB_REQ_WAIT_EN(0xff)
DECL|macro|BRIDGE_ARB_FREEZE_GNT
mdefine_line|#define BRIDGE_ARB_FREEZE_GNT&t;&t;(1 &lt;&lt; 6)
DECL|macro|BRIDGE_ARB_HPRI_RING_B2
mdefine_line|#define BRIDGE_ARB_HPRI_RING_B2&t;&t;(1 &lt;&lt; 5)
DECL|macro|BRIDGE_ARB_HPRI_RING_B1
mdefine_line|#define BRIDGE_ARB_HPRI_RING_B1&t;&t;(1 &lt;&lt; 4)
DECL|macro|BRIDGE_ARB_HPRI_RING_B0
mdefine_line|#define BRIDGE_ARB_HPRI_RING_B0&t;&t;(1 &lt;&lt; 3)
DECL|macro|BRIDGE_ARB_LPRI_RING_B2
mdefine_line|#define BRIDGE_ARB_LPRI_RING_B2&t;&t;(1 &lt;&lt; 2)
DECL|macro|BRIDGE_ARB_LPRI_RING_B1
mdefine_line|#define BRIDGE_ARB_LPRI_RING_B1&t;&t;(1 &lt;&lt; 1)
DECL|macro|BRIDGE_ARB_LPRI_RING_B0
mdefine_line|#define BRIDGE_ARB_LPRI_RING_B0&t;&t;(1 &lt;&lt; 0)
multiline_comment|/* Bridge Bus time-out register bits definition */
DECL|macro|BRIDGE_BUS_PCI_RETRY_HLD
mdefine_line|#define BRIDGE_BUS_PCI_RETRY_HLD(x)&t;((x) &lt;&lt; 16)
DECL|macro|BRIDGE_BUS_PCI_RETRY_HLD_MASK
mdefine_line|#define BRIDGE_BUS_PCI_RETRY_HLD_MASK&t;BRIDGE_BUS_PCI_RETRY_HLD(0x1f)
DECL|macro|BRIDGE_BUS_GIO_TIMEOUT
mdefine_line|#define BRIDGE_BUS_GIO_TIMEOUT&t;&t;(1 &lt;&lt; 12)
DECL|macro|BRIDGE_BUS_PCI_RETRY_CNT
mdefine_line|#define BRIDGE_BUS_PCI_RETRY_CNT(x)&t;((x) &lt;&lt; 0)
DECL|macro|BRIDGE_BUS_PCI_RETRY_MASK
mdefine_line|#define BRIDGE_BUS_PCI_RETRY_MASK&t;BRIDGE_BUS_PCI_RETRY_CNT(0x3ff)
multiline_comment|/* Bridge interrupt status register bits definition */
DECL|macro|BRIDGE_ISR_MULTI_ERR
mdefine_line|#define BRIDGE_ISR_MULTI_ERR&t;&t;(0x1u &lt;&lt; 31)
DECL|macro|BRIDGE_ISR_PMU_ESIZE_FAULT
mdefine_line|#define BRIDGE_ISR_PMU_ESIZE_FAULT&t;(0x1 &lt;&lt; 30)
DECL|macro|BRIDGE_ISR_UNEXP_RESP
mdefine_line|#define BRIDGE_ISR_UNEXP_RESP&t;&t;(0x1 &lt;&lt; 29)
DECL|macro|BRIDGE_ISR_BAD_XRESP_PKT
mdefine_line|#define BRIDGE_ISR_BAD_XRESP_PKT&t;(0x1 &lt;&lt; 28)
DECL|macro|BRIDGE_ISR_BAD_XREQ_PKT
mdefine_line|#define BRIDGE_ISR_BAD_XREQ_PKT&t;&t;(0x1 &lt;&lt; 27)
DECL|macro|BRIDGE_ISR_RESP_XTLK_ERR
mdefine_line|#define BRIDGE_ISR_RESP_XTLK_ERR&t;(0x1 &lt;&lt; 26)
DECL|macro|BRIDGE_ISR_REQ_XTLK_ERR
mdefine_line|#define BRIDGE_ISR_REQ_XTLK_ERR&t;&t;(0x1 &lt;&lt; 25)
DECL|macro|BRIDGE_ISR_INVLD_ADDR
mdefine_line|#define BRIDGE_ISR_INVLD_ADDR&t;&t;(0x1 &lt;&lt; 24)
DECL|macro|BRIDGE_ISR_UNSUPPORTED_XOP
mdefine_line|#define BRIDGE_ISR_UNSUPPORTED_XOP&t;(0x1 &lt;&lt; 23)
DECL|macro|BRIDGE_ISR_XREQ_FIFO_OFLOW
mdefine_line|#define BRIDGE_ISR_XREQ_FIFO_OFLOW&t;(0x1 &lt;&lt; 22)
DECL|macro|BRIDGE_ISR_LLP_REC_SNERR
mdefine_line|#define BRIDGE_ISR_LLP_REC_SNERR&t;(0x1 &lt;&lt; 21)
DECL|macro|BRIDGE_ISR_LLP_REC_CBERR
mdefine_line|#define BRIDGE_ISR_LLP_REC_CBERR&t;(0x1 &lt;&lt; 20)
DECL|macro|BRIDGE_ISR_LLP_RCTY
mdefine_line|#define BRIDGE_ISR_LLP_RCTY&t;&t;(0x1 &lt;&lt; 19)
DECL|macro|BRIDGE_ISR_LLP_TX_RETRY
mdefine_line|#define BRIDGE_ISR_LLP_TX_RETRY&t;&t;(0x1 &lt;&lt; 18)
DECL|macro|BRIDGE_ISR_LLP_TCTY
mdefine_line|#define BRIDGE_ISR_LLP_TCTY&t;&t;(0x1 &lt;&lt; 17)
DECL|macro|BRIDGE_ISR_SSRAM_PERR
mdefine_line|#define BRIDGE_ISR_SSRAM_PERR&t;&t;(0x1 &lt;&lt; 16)
DECL|macro|BRIDGE_ISR_PCI_ABORT
mdefine_line|#define BRIDGE_ISR_PCI_ABORT&t;&t;(0x1 &lt;&lt; 15)
DECL|macro|BRIDGE_ISR_PCI_PARITY
mdefine_line|#define BRIDGE_ISR_PCI_PARITY&t;&t;(0x1 &lt;&lt; 14)
DECL|macro|BRIDGE_ISR_PCI_SERR
mdefine_line|#define BRIDGE_ISR_PCI_SERR&t;&t;(0x1 &lt;&lt; 13)
DECL|macro|BRIDGE_ISR_PCI_PERR
mdefine_line|#define BRIDGE_ISR_PCI_PERR&t;&t;(0x1 &lt;&lt; 12)
DECL|macro|BRIDGE_ISR_PCI_MST_TIMEOUT
mdefine_line|#define BRIDGE_ISR_PCI_MST_TIMEOUT&t;(0x1 &lt;&lt; 11)
DECL|macro|BRIDGE_ISR_GIO_MST_TIMEOUT
mdefine_line|#define BRIDGE_ISR_GIO_MST_TIMEOUT&t;BRIDGE_ISR_PCI_MST_TIMEOUT
DECL|macro|BRIDGE_ISR_PCI_RETRY_CNT
mdefine_line|#define BRIDGE_ISR_PCI_RETRY_CNT&t;(0x1 &lt;&lt; 10)
DECL|macro|BRIDGE_ISR_XREAD_REQ_TIMEOUT
mdefine_line|#define BRIDGE_ISR_XREAD_REQ_TIMEOUT&t;(0x1 &lt;&lt; 9)
DECL|macro|BRIDGE_ISR_GIO_B_ENBL_ERR
mdefine_line|#define BRIDGE_ISR_GIO_B_ENBL_ERR&t;(0x1 &lt;&lt; 8)
DECL|macro|BRIDGE_ISR_INT_MSK
mdefine_line|#define BRIDGE_ISR_INT_MSK&t;&t;(0xff &lt;&lt; 0)
DECL|macro|BRIDGE_ISR_INT
mdefine_line|#define BRIDGE_ISR_INT(x)&t;&t;(0x1 &lt;&lt; (x))
DECL|macro|BRIDGE_ISR_LINK_ERROR
mdefine_line|#define BRIDGE_ISR_LINK_ERROR&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_LLP_REC_SNERR|BRIDGE_ISR_LLP_REC_CBERR|&t;&bslash;&n;&t;&t; BRIDGE_ISR_LLP_RCTY|BRIDGE_ISR_LLP_TX_RETRY|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_LLP_TCTY)
DECL|macro|BRIDGE_ISR_PCIBUS_PIOERR
mdefine_line|#define BRIDGE_ISR_PCIBUS_PIOERR&t;&bslash;&n;&t;&t;(BRIDGE_ISR_PCI_MST_TIMEOUT|BRIDGE_ISR_PCI_ABORT)
DECL|macro|BRIDGE_ISR_PCIBUS_ERROR
mdefine_line|#define BRIDGE_ISR_PCIBUS_ERROR&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_PCIBUS_PIOERR|BRIDGE_ISR_PCI_PERR|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_PCI_SERR|BRIDGE_ISR_PCI_RETRY_CNT|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_PCI_PARITY)
DECL|macro|BRIDGE_ISR_XTALK_ERROR
mdefine_line|#define BRIDGE_ISR_XTALK_ERROR&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_XREAD_REQ_TIMEOUT|BRIDGE_ISR_XREQ_FIFO_OFLOW|&bslash;&n;&t;&t; BRIDGE_ISR_UNSUPPORTED_XOP|BRIDGE_ISR_INVLD_ADDR|&t;&bslash;&n;&t;&t; BRIDGE_ISR_REQ_XTLK_ERR|BRIDGE_ISR_RESP_XTLK_ERR|&t;&bslash;&n;&t;&t; BRIDGE_ISR_BAD_XREQ_PKT|BRIDGE_ISR_BAD_XRESP_PKT|&t;&bslash;&n;&t;&t; BRIDGE_ISR_UNEXP_RESP)
DECL|macro|BRIDGE_ISR_ERRORS
mdefine_line|#define BRIDGE_ISR_ERRORS&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_LINK_ERROR|BRIDGE_ISR_PCIBUS_ERROR|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_XTALK_ERROR|BRIDGE_ISR_SSRAM_PERR|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_PMU_ESIZE_FAULT)
multiline_comment|/*&n; * List of Errors which are fatal and kill the sytem&n; */
DECL|macro|BRIDGE_ISR_ERROR_FATAL
mdefine_line|#define BRIDGE_ISR_ERROR_FATAL&t;&t;&bslash;&n;&t;&t;((BRIDGE_ISR_XTALK_ERROR &amp; ~BRIDGE_ISR_XREAD_REQ_TIMEOUT)|&bslash;&n;&t;&t; BRIDGE_ISR_PCI_SERR|BRIDGE_ISR_PCI_PARITY )
DECL|macro|BRIDGE_ISR_ERROR_DUMP
mdefine_line|#define BRIDGE_ISR_ERROR_DUMP&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_PCIBUS_ERROR|BRIDGE_ISR_PMU_ESIZE_FAULT|&t;&bslash;&n;&t;&t; BRIDGE_ISR_XTALK_ERROR|BRIDGE_ISR_SSRAM_PERR)
multiline_comment|/* Bridge interrupt enable register bits definition */
DECL|macro|BRIDGE_IMR_UNEXP_RESP
mdefine_line|#define BRIDGE_IMR_UNEXP_RESP&t;&t;BRIDGE_ISR_UNEXP_RESP
DECL|macro|BRIDGE_IMR_PMU_ESIZE_FAULT
mdefine_line|#define BRIDGE_IMR_PMU_ESIZE_FAULT&t;BRIDGE_ISR_PMU_ESIZE_FAULT
DECL|macro|BRIDGE_IMR_BAD_XRESP_PKT
mdefine_line|#define BRIDGE_IMR_BAD_XRESP_PKT&t;BRIDGE_ISR_BAD_XRESP_PKT
DECL|macro|BRIDGE_IMR_BAD_XREQ_PKT
mdefine_line|#define BRIDGE_IMR_BAD_XREQ_PKT&t;&t;BRIDGE_ISR_BAD_XREQ_PKT
DECL|macro|BRIDGE_IMR_RESP_XTLK_ERR
mdefine_line|#define BRIDGE_IMR_RESP_XTLK_ERR&t;BRIDGE_ISR_RESP_XTLK_ERR
DECL|macro|BRIDGE_IMR_REQ_XTLK_ERR
mdefine_line|#define BRIDGE_IMR_REQ_XTLK_ERR&t;&t;BRIDGE_ISR_REQ_XTLK_ERR
DECL|macro|BRIDGE_IMR_INVLD_ADDR
mdefine_line|#define BRIDGE_IMR_INVLD_ADDR&t;&t;BRIDGE_ISR_INVLD_ADDR
DECL|macro|BRIDGE_IMR_UNSUPPORTED_XOP
mdefine_line|#define BRIDGE_IMR_UNSUPPORTED_XOP&t;BRIDGE_ISR_UNSUPPORTED_XOP
DECL|macro|BRIDGE_IMR_XREQ_FIFO_OFLOW
mdefine_line|#define BRIDGE_IMR_XREQ_FIFO_OFLOW&t;BRIDGE_ISR_XREQ_FIFO_OFLOW
DECL|macro|BRIDGE_IMR_LLP_REC_SNERR
mdefine_line|#define BRIDGE_IMR_LLP_REC_SNERR&t;BRIDGE_ISR_LLP_REC_SNERR
DECL|macro|BRIDGE_IMR_LLP_REC_CBERR
mdefine_line|#define BRIDGE_IMR_LLP_REC_CBERR&t;BRIDGE_ISR_LLP_REC_CBERR
DECL|macro|BRIDGE_IMR_LLP_RCTY
mdefine_line|#define BRIDGE_IMR_LLP_RCTY&t;&t;BRIDGE_ISR_LLP_RCTY
DECL|macro|BRIDGE_IMR_LLP_TX_RETRY
mdefine_line|#define BRIDGE_IMR_LLP_TX_RETRY&t;&t;BRIDGE_ISR_LLP_TX_RETRY
DECL|macro|BRIDGE_IMR_LLP_TCTY
mdefine_line|#define BRIDGE_IMR_LLP_TCTY&t;&t;BRIDGE_ISR_LLP_TCTY
DECL|macro|BRIDGE_IMR_SSRAM_PERR
mdefine_line|#define BRIDGE_IMR_SSRAM_PERR&t;&t;BRIDGE_ISR_SSRAM_PERR
DECL|macro|BRIDGE_IMR_PCI_ABORT
mdefine_line|#define BRIDGE_IMR_PCI_ABORT&t;&t;BRIDGE_ISR_PCI_ABORT
DECL|macro|BRIDGE_IMR_PCI_PARITY
mdefine_line|#define BRIDGE_IMR_PCI_PARITY&t;&t;BRIDGE_ISR_PCI_PARITY
DECL|macro|BRIDGE_IMR_PCI_SERR
mdefine_line|#define BRIDGE_IMR_PCI_SERR&t;&t;BRIDGE_ISR_PCI_SERR
DECL|macro|BRIDGE_IMR_PCI_PERR
mdefine_line|#define BRIDGE_IMR_PCI_PERR&t;&t;BRIDGE_ISR_PCI_PERR
DECL|macro|BRIDGE_IMR_PCI_MST_TIMEOUT
mdefine_line|#define BRIDGE_IMR_PCI_MST_TIMEOUT&t;BRIDGE_ISR_PCI_MST_TIMEOUT
DECL|macro|BRIDGE_IMR_GIO_MST_TIMEOUT
mdefine_line|#define BRIDGE_IMR_GIO_MST_TIMEOUT&t;BRIDGE_ISR_GIO_MST_TIMEOUT
DECL|macro|BRIDGE_IMR_PCI_RETRY_CNT
mdefine_line|#define BRIDGE_IMR_PCI_RETRY_CNT&t;BRIDGE_ISR_PCI_RETRY_CNT
DECL|macro|BRIDGE_IMR_XREAD_REQ_TIMEOUT
mdefine_line|#define BRIDGE_IMR_XREAD_REQ_TIMEOUT&t;BRIDGE_ISR_XREAD_REQ_TIMEOUT
DECL|macro|BRIDGE_IMR_GIO_B_ENBL_ERR
mdefine_line|#define BRIDGE_IMR_GIO_B_ENBL_ERR&t;BRIDGE_ISR_GIO_B_ENBL_ERR
DECL|macro|BRIDGE_IMR_INT_MSK
mdefine_line|#define BRIDGE_IMR_INT_MSK&t;&t;BRIDGE_ISR_INT_MSK
DECL|macro|BRIDGE_IMR_INT
mdefine_line|#define BRIDGE_IMR_INT(x)&t;&t;BRIDGE_ISR_INT(x)
multiline_comment|/* Bridge interrupt reset register bits definition */
DECL|macro|BRIDGE_IRR_MULTI_CLR
mdefine_line|#define BRIDGE_IRR_MULTI_CLR&t;&t;(0x1 &lt;&lt; 6)
DECL|macro|BRIDGE_IRR_CRP_GRP_CLR
mdefine_line|#define BRIDGE_IRR_CRP_GRP_CLR&t;&t;(0x1 &lt;&lt; 5)
DECL|macro|BRIDGE_IRR_RESP_BUF_GRP_CLR
mdefine_line|#define BRIDGE_IRR_RESP_BUF_GRP_CLR&t;(0x1 &lt;&lt; 4)
DECL|macro|BRIDGE_IRR_REQ_DSP_GRP_CLR
mdefine_line|#define BRIDGE_IRR_REQ_DSP_GRP_CLR&t;(0x1 &lt;&lt; 3)
DECL|macro|BRIDGE_IRR_LLP_GRP_CLR
mdefine_line|#define BRIDGE_IRR_LLP_GRP_CLR&t;&t;(0x1 &lt;&lt; 2)
DECL|macro|BRIDGE_IRR_SSRAM_GRP_CLR
mdefine_line|#define BRIDGE_IRR_SSRAM_GRP_CLR&t;(0x1 &lt;&lt; 1)
DECL|macro|BRIDGE_IRR_PCI_GRP_CLR
mdefine_line|#define BRIDGE_IRR_PCI_GRP_CLR&t;&t;(0x1 &lt;&lt; 0)
DECL|macro|BRIDGE_IRR_GIO_GRP_CLR
mdefine_line|#define BRIDGE_IRR_GIO_GRP_CLR&t;&t;(0x1 &lt;&lt; 0)
DECL|macro|BRIDGE_IRR_ALL_CLR
mdefine_line|#define BRIDGE_IRR_ALL_CLR&t;&t;0x7f
DECL|macro|BRIDGE_IRR_CRP_GRP
mdefine_line|#define BRIDGE_IRR_CRP_GRP&t;&t;(BRIDGE_ISR_UNEXP_RESP | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_XREQ_FIFO_OFLOW)
DECL|macro|BRIDGE_IRR_RESP_BUF_GRP
mdefine_line|#define BRIDGE_IRR_RESP_BUF_GRP&t;&t;(BRIDGE_ISR_BAD_XRESP_PKT | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_RESP_XTLK_ERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_XREAD_REQ_TIMEOUT)
DECL|macro|BRIDGE_IRR_REQ_DSP_GRP
mdefine_line|#define BRIDGE_IRR_REQ_DSP_GRP&t;&t;(BRIDGE_ISR_UNSUPPORTED_XOP | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_BAD_XREQ_PKT | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_REQ_XTLK_ERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_INVLD_ADDR)
DECL|macro|BRIDGE_IRR_LLP_GRP
mdefine_line|#define BRIDGE_IRR_LLP_GRP&t;&t;(BRIDGE_ISR_LLP_REC_SNERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_LLP_REC_CBERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_LLP_RCTY | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_LLP_TX_RETRY | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_LLP_TCTY)
DECL|macro|BRIDGE_IRR_SSRAM_GRP
mdefine_line|#define BRIDGE_IRR_SSRAM_GRP&t;&t;(BRIDGE_ISR_SSRAM_PERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_PMU_ESIZE_FAULT)
DECL|macro|BRIDGE_IRR_PCI_GRP
mdefine_line|#define BRIDGE_IRR_PCI_GRP&t;&t;(BRIDGE_ISR_PCI_ABORT | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_PCI_PARITY | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_PCI_SERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_PCI_PERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_PCI_MST_TIMEOUT | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_PCI_RETRY_CNT)
DECL|macro|BRIDGE_IRR_GIO_GRP
mdefine_line|#define BRIDGE_IRR_GIO_GRP&t;&t;(BRIDGE_ISR_GIO_B_ENBL_ERR | &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_ISR_GIO_MST_TIMEOUT)
multiline_comment|/* Bridge INT_DEV register bits definition */
DECL|macro|BRIDGE_INT_DEV_SHFT
mdefine_line|#define BRIDGE_INT_DEV_SHFT(n)&t;&t;((n)*3)
DECL|macro|BRIDGE_INT_DEV_MASK
mdefine_line|#define BRIDGE_INT_DEV_MASK(n)&t;&t;(0x7 &lt;&lt; BRIDGE_INT_DEV_SHFT(n))
DECL|macro|BRIDGE_INT_DEV_SET
mdefine_line|#define BRIDGE_INT_DEV_SET(_dev, _line) (_dev &lt;&lt; BRIDGE_INT_DEV_SHFT(_line))&t;
multiline_comment|/* Bridge interrupt(x) register bits definition */
DECL|macro|BRIDGE_INT_ADDR_HOST
mdefine_line|#define BRIDGE_INT_ADDR_HOST&t;&t;0x0003FF00
DECL|macro|BRIDGE_INT_ADDR_FLD
mdefine_line|#define BRIDGE_INT_ADDR_FLD&t;&t;0x000000FF
DECL|macro|BRIDGE_TMO_PCI_RETRY_HLD_MASK
mdefine_line|#define BRIDGE_TMO_PCI_RETRY_HLD_MASK&t;0x1f0000
DECL|macro|BRIDGE_TMO_GIO_TIMEOUT_MASK
mdefine_line|#define BRIDGE_TMO_GIO_TIMEOUT_MASK&t;0x001000
DECL|macro|BRIDGE_TMO_PCI_RETRY_CNT_MASK
mdefine_line|#define BRIDGE_TMO_PCI_RETRY_CNT_MASK&t;0x0003ff
DECL|macro|BRIDGE_TMO_PCI_RETRY_CNT_MAX
mdefine_line|#define BRIDGE_TMO_PCI_RETRY_CNT_MAX&t;0x3ff
multiline_comment|/*&n; * The NASID should be shifted by this amount and stored into the&n; * interrupt(x) register.&n; */
DECL|macro|BRIDGE_INT_ADDR_NASID_SHFT
mdefine_line|#define BRIDGE_INT_ADDR_NASID_SHFT&t;8
multiline_comment|/*&n; * The BRIDGE_INT_ADDR_DEST_IO bit should be set to send an interrupt to&n; * memory.&n; */
DECL|macro|BRIDGE_INT_ADDR_DEST_IO
mdefine_line|#define BRIDGE_INT_ADDR_DEST_IO&t;&t;(1 &lt;&lt; 17)
DECL|macro|BRIDGE_INT_ADDR_DEST_MEM
mdefine_line|#define BRIDGE_INT_ADDR_DEST_MEM&t;0
DECL|macro|BRIDGE_INT_ADDR_MASK
mdefine_line|#define BRIDGE_INT_ADDR_MASK&t;&t;(1 &lt;&lt; 17)
multiline_comment|/* Bridge device(x) register bits definition */
DECL|macro|BRIDGE_DEV_ERR_LOCK_EN
mdefine_line|#define BRIDGE_DEV_ERR_LOCK_EN&t;&t;0x10000000
DECL|macro|BRIDGE_DEV_PAGE_CHK_DIS
mdefine_line|#define BRIDGE_DEV_PAGE_CHK_DIS&t;&t;0x08000000
DECL|macro|BRIDGE_DEV_FORCE_PCI_PAR
mdefine_line|#define BRIDGE_DEV_FORCE_PCI_PAR&t;0x04000000
DECL|macro|BRIDGE_DEV_VIRTUAL_EN
mdefine_line|#define BRIDGE_DEV_VIRTUAL_EN&t;&t;0x02000000
DECL|macro|BRIDGE_DEV_PMU_WRGA_EN
mdefine_line|#define BRIDGE_DEV_PMU_WRGA_EN&t;&t;0x01000000
DECL|macro|BRIDGE_DEV_DIR_WRGA_EN
mdefine_line|#define BRIDGE_DEV_DIR_WRGA_EN&t;&t;0x00800000
DECL|macro|BRIDGE_DEV_DEV_SIZE
mdefine_line|#define BRIDGE_DEV_DEV_SIZE&t;&t;0x00400000
DECL|macro|BRIDGE_DEV_RT
mdefine_line|#define BRIDGE_DEV_RT&t;&t;&t;0x00200000
DECL|macro|BRIDGE_DEV_SWAP_PMU
mdefine_line|#define BRIDGE_DEV_SWAP_PMU&t;&t;0x00100000
DECL|macro|BRIDGE_DEV_SWAP_DIR
mdefine_line|#define BRIDGE_DEV_SWAP_DIR&t;&t;0x00080000
DECL|macro|BRIDGE_DEV_PREF
mdefine_line|#define BRIDGE_DEV_PREF&t;&t;&t;0x00040000
DECL|macro|BRIDGE_DEV_PRECISE
mdefine_line|#define BRIDGE_DEV_PRECISE&t;&t;0x00020000
DECL|macro|BRIDGE_DEV_COH
mdefine_line|#define BRIDGE_DEV_COH&t;&t;&t;0x00010000
DECL|macro|BRIDGE_DEV_BARRIER
mdefine_line|#define BRIDGE_DEV_BARRIER&t;&t;0x00008000
DECL|macro|BRIDGE_DEV_GBR
mdefine_line|#define BRIDGE_DEV_GBR&t;&t;&t;0x00004000
DECL|macro|BRIDGE_DEV_DEV_SWAP
mdefine_line|#define BRIDGE_DEV_DEV_SWAP&t;&t;0x00002000
DECL|macro|BRIDGE_DEV_DEV_IO_MEM
mdefine_line|#define BRIDGE_DEV_DEV_IO_MEM&t;&t;0x00001000
DECL|macro|BRIDGE_DEV_OFF_MASK
mdefine_line|#define BRIDGE_DEV_OFF_MASK&t;&t;0x00000fff
DECL|macro|BRIDGE_DEV_OFF_ADDR_SHFT
mdefine_line|#define BRIDGE_DEV_OFF_ADDR_SHFT&t;20
DECL|macro|BRIDGE_DEV_PMU_BITS
mdefine_line|#define BRIDGE_DEV_PMU_BITS&t;&t;(BRIDGE_DEV_PMU_WRGA_EN&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_SWAP_PMU)
DECL|macro|BRIDGE_DEV_D32_BITS
mdefine_line|#define BRIDGE_DEV_D32_BITS&t;&t;(BRIDGE_DEV_DIR_WRGA_EN&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_SWAP_DIR&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_PREF&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_PRECISE&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_COH&t;&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_BARRIER)
DECL|macro|BRIDGE_DEV_D64_BITS
mdefine_line|#define BRIDGE_DEV_D64_BITS&t;&t;(BRIDGE_DEV_DIR_WRGA_EN&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_SWAP_DIR&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_COH&t;&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_BARRIER)
multiline_comment|/* Bridge Error Upper register bit field definition */
DECL|macro|BRIDGE_ERRUPPR_DEVMASTER
mdefine_line|#define BRIDGE_ERRUPPR_DEVMASTER&t;(0x1 &lt;&lt; 20)&t;/* Device was master */
DECL|macro|BRIDGE_ERRUPPR_PCIVDEV
mdefine_line|#define BRIDGE_ERRUPPR_PCIVDEV&t;&t;(0x1 &lt;&lt; 19)&t;/* Virtual Req value */
DECL|macro|BRIDGE_ERRUPPR_DEVNUM_SHFT
mdefine_line|#define BRIDGE_ERRUPPR_DEVNUM_SHFT&t;(16)
DECL|macro|BRIDGE_ERRUPPR_DEVNUM_MASK
mdefine_line|#define BRIDGE_ERRUPPR_DEVNUM_MASK&t;(0x7 &lt;&lt; BRIDGE_ERRUPPR_DEVNUM_SHFT)
DECL|macro|BRIDGE_ERRUPPR_DEVICE
mdefine_line|#define BRIDGE_ERRUPPR_DEVICE(err)&t;(((err) &gt;&gt; BRIDGE_ERRUPPR_DEVNUM_SHFT) &amp; 0x7)
DECL|macro|BRIDGE_ERRUPPR_ADDRMASK
mdefine_line|#define BRIDGE_ERRUPPR_ADDRMASK&t;&t;(0xFFFF)
multiline_comment|/* Bridge interrupt mode register bits definition */
DECL|macro|BRIDGE_INTMODE_CLR_PKT_EN
mdefine_line|#define BRIDGE_INTMODE_CLR_PKT_EN(x)&t;(0x1 &lt;&lt; (x))
multiline_comment|/* this should be written to the xbow&squot;s link_control(x) register */
DECL|macro|BRIDGE_CREDIT
mdefine_line|#define BRIDGE_CREDIT&t;3
multiline_comment|/* RRB assignment register */
DECL|macro|BRIDGE_RRB_EN
mdefine_line|#define&t;BRIDGE_RRB_EN&t;0x8&t;/* after shifting down */
DECL|macro|BRIDGE_RRB_DEV
mdefine_line|#define&t;BRIDGE_RRB_DEV&t;0x7&t;/* after shifting down */
DECL|macro|BRIDGE_RRB_VDEV
mdefine_line|#define&t;BRIDGE_RRB_VDEV&t;0x4&t;/* after shifting down */
DECL|macro|BRIDGE_RRB_PDEV
mdefine_line|#define&t;BRIDGE_RRB_PDEV&t;0x3&t;/* after shifting down */
multiline_comment|/* RRB status register */
DECL|macro|BRIDGE_RRB_VALID
mdefine_line|#define&t;BRIDGE_RRB_VALID(r)&t;(0x00010000&lt;&lt;(r))
DECL|macro|BRIDGE_RRB_INUSE
mdefine_line|#define&t;BRIDGE_RRB_INUSE(r)&t;(0x00000001&lt;&lt;(r))
multiline_comment|/* RRB clear register */
DECL|macro|BRIDGE_RRB_CLEAR
mdefine_line|#define&t;BRIDGE_RRB_CLEAR(r)&t;(0x00000001&lt;&lt;(r))
multiline_comment|/* xbox system controller declarations */
DECL|macro|XBOX_BRIDGE_WID
mdefine_line|#define XBOX_BRIDGE_WID         8
DECL|macro|FLASH_PROM1_BASE
mdefine_line|#define FLASH_PROM1_BASE        0xE00000 /* To read the xbox sysctlr status */
DECL|macro|XBOX_RPS_EXISTS
mdefine_line|#define XBOX_RPS_EXISTS&t;&t;1 &lt;&lt; 6&t; /* RPS bit in status register */
DECL|macro|XBOX_RPS_FAIL
mdefine_line|#define XBOX_RPS_FAIL&t;&t;1 &lt;&lt; 4&t; /* RPS status bit in register */
multiline_comment|/* ========================================================================&n; */
multiline_comment|/*&n; * Macros for Xtalk to Bridge bus (PCI/GIO) PIO&n; * refer to section 4.2.1 of Bridge Spec for xtalk to PCI/GIO PIO mappings&n; */
multiline_comment|/* XTALK addresses that map into Bridge Bus addr space */
DECL|macro|BRIDGE_PIO32_XTALK_ALIAS_BASE
mdefine_line|#define BRIDGE_PIO32_XTALK_ALIAS_BASE&t;0x000040000000L
DECL|macro|BRIDGE_PIO32_XTALK_ALIAS_LIMIT
mdefine_line|#define BRIDGE_PIO32_XTALK_ALIAS_LIMIT&t;0x00007FFFFFFFL
DECL|macro|BRIDGE_PIO64_XTALK_ALIAS_BASE
mdefine_line|#define BRIDGE_PIO64_XTALK_ALIAS_BASE&t;0x000080000000L
DECL|macro|BRIDGE_PIO64_XTALK_ALIAS_LIMIT
mdefine_line|#define BRIDGE_PIO64_XTALK_ALIAS_LIMIT&t;0x0000BFFFFFFFL
DECL|macro|BRIDGE_PCIIO_XTALK_ALIAS_BASE
mdefine_line|#define BRIDGE_PCIIO_XTALK_ALIAS_BASE&t;0x000100000000L
DECL|macro|BRIDGE_PCIIO_XTALK_ALIAS_LIMIT
mdefine_line|#define BRIDGE_PCIIO_XTALK_ALIAS_LIMIT&t;0x0001FFFFFFFFL
multiline_comment|/* Ranges of PCI bus space that can be accessed via PIO from xtalk */
DECL|macro|BRIDGE_MIN_PIO_ADDR_MEM
mdefine_line|#define BRIDGE_MIN_PIO_ADDR_MEM&t;&t;0x00000000&t;/* 1G PCI memory space */
DECL|macro|BRIDGE_MAX_PIO_ADDR_MEM
mdefine_line|#define BRIDGE_MAX_PIO_ADDR_MEM&t;&t;0x3fffffff
DECL|macro|BRIDGE_MIN_PIO_ADDR_IO
mdefine_line|#define BRIDGE_MIN_PIO_ADDR_IO&t;&t;0x00000000&t;/* 4G PCI IO space */
DECL|macro|BRIDGE_MAX_PIO_ADDR_IO
mdefine_line|#define BRIDGE_MAX_PIO_ADDR_IO&t;&t;0xffffffff
multiline_comment|/* XTALK addresses that map into PCI addresses */
DECL|macro|BRIDGE_PCI_MEM32_BASE
mdefine_line|#define BRIDGE_PCI_MEM32_BASE&t;&t;BRIDGE_PIO32_XTALK_ALIAS_BASE
DECL|macro|BRIDGE_PCI_MEM32_LIMIT
mdefine_line|#define BRIDGE_PCI_MEM32_LIMIT&t;&t;BRIDGE_PIO32_XTALK_ALIAS_LIMIT
DECL|macro|BRIDGE_PCI_MEM64_BASE
mdefine_line|#define BRIDGE_PCI_MEM64_BASE&t;&t;BRIDGE_PIO64_XTALK_ALIAS_BASE
DECL|macro|BRIDGE_PCI_MEM64_LIMIT
mdefine_line|#define BRIDGE_PCI_MEM64_LIMIT&t;&t;BRIDGE_PIO64_XTALK_ALIAS_LIMIT
DECL|macro|BRIDGE_PCI_IO_BASE
mdefine_line|#define BRIDGE_PCI_IO_BASE&t;&t;BRIDGE_PCIIO_XTALK_ALIAS_BASE
DECL|macro|BRIDGE_PCI_IO_LIMIT
mdefine_line|#define BRIDGE_PCI_IO_LIMIT&t;&t;BRIDGE_PCIIO_XTALK_ALIAS_LIMIT
multiline_comment|/*&n; * Macros for Bridge bus (PCI/GIO) to Xtalk DMA&n; */
multiline_comment|/* Bridge Bus DMA addresses */
DECL|macro|BRIDGE_LOCAL_BASE
mdefine_line|#define BRIDGE_LOCAL_BASE&t;&t;0
DECL|macro|BRIDGE_DMA_MAPPED_BASE
mdefine_line|#define BRIDGE_DMA_MAPPED_BASE&t;&t;0x40000000
DECL|macro|BRIDGE_DMA_MAPPED_SIZE
mdefine_line|#define BRIDGE_DMA_MAPPED_SIZE&t;&t;0x40000000&t;/* 1G Bytes */
DECL|macro|BRIDGE_DMA_DIRECT_BASE
mdefine_line|#define BRIDGE_DMA_DIRECT_BASE&t;&t;0x80000000
DECL|macro|BRIDGE_DMA_DIRECT_SIZE
mdefine_line|#define BRIDGE_DMA_DIRECT_SIZE&t;&t;0x80000000&t;/* 2G Bytes */
DECL|macro|PCI32_LOCAL_BASE
mdefine_line|#define PCI32_LOCAL_BASE&t;&t;BRIDGE_LOCAL_BASE
multiline_comment|/* PCI addresses of regions decoded by Bridge for DMA */
DECL|macro|PCI32_MAPPED_BASE
mdefine_line|#define PCI32_MAPPED_BASE&t;&t;BRIDGE_DMA_MAPPED_BASE
DECL|macro|PCI32_DIRECT_BASE
mdefine_line|#define PCI32_DIRECT_BASE&t;&t;BRIDGE_DMA_DIRECT_BASE
DECL|macro|IS_PCI32_LOCAL
mdefine_line|#define IS_PCI32_LOCAL(x)&t;((ulong_t)(x) &lt; PCI32_MAPPED_BASE)
DECL|macro|IS_PCI32_MAPPED
mdefine_line|#define IS_PCI32_MAPPED(x)&t;((ulong_t)(x) &lt; PCI32_DIRECT_BASE &amp;&amp; &bslash;&n;&t;&t;&t;&t;&t;(ulong_t)(x) &gt;= PCI32_MAPPED_BASE)
DECL|macro|IS_PCI32_DIRECT
mdefine_line|#define IS_PCI32_DIRECT(x)&t;((ulong_t)(x) &gt;= PCI32_MAPPED_BASE)
DECL|macro|IS_PCI64
mdefine_line|#define IS_PCI64(x)&t;&t;((ulong_t)(x) &gt;= PCI64_BASE)
multiline_comment|/*&n; * The GIO address space.&n; */
multiline_comment|/* Xtalk to GIO PIO */
DECL|macro|BRIDGE_GIO_MEM32_BASE
mdefine_line|#define BRIDGE_GIO_MEM32_BASE&t;&t;BRIDGE_PIO32_XTALK_ALIAS_BASE
DECL|macro|BRIDGE_GIO_MEM32_LIMIT
mdefine_line|#define BRIDGE_GIO_MEM32_LIMIT&t;&t;BRIDGE_PIO32_XTALK_ALIAS_LIMIT
DECL|macro|GIO_LOCAL_BASE
mdefine_line|#define GIO_LOCAL_BASE&t;&t;&t;BRIDGE_LOCAL_BASE
multiline_comment|/* GIO addresses of regions decoded by Bridge for DMA */
DECL|macro|GIO_MAPPED_BASE
mdefine_line|#define GIO_MAPPED_BASE&t;&t;&t;BRIDGE_DMA_MAPPED_BASE
DECL|macro|GIO_DIRECT_BASE
mdefine_line|#define GIO_DIRECT_BASE&t;&t;&t;BRIDGE_DMA_DIRECT_BASE
DECL|macro|IS_GIO_LOCAL
mdefine_line|#define IS_GIO_LOCAL(x)&t;&t;((ulong_t)(x) &lt; GIO_MAPPED_BASE)
DECL|macro|IS_GIO_MAPPED
mdefine_line|#define IS_GIO_MAPPED(x)&t;((ulong_t)(x) &lt; GIO_DIRECT_BASE &amp;&amp; &bslash;&n;&t;&t;&t;&t;&t;(ulong_t)(x) &gt;= GIO_MAPPED_BASE)
DECL|macro|IS_GIO_DIRECT
mdefine_line|#define IS_GIO_DIRECT(x)&t;((ulong_t)(x) &gt;= GIO_MAPPED_BASE)
multiline_comment|/* PCI to xtalk mapping */
multiline_comment|/* given a DIR_OFF value and a pci/gio 32 bits direct address, determine&n; * which xtalk address is accessed&n; */
DECL|macro|BRIDGE_DIRECT_32_SEG_SIZE
mdefine_line|#define BRIDGE_DIRECT_32_SEG_SIZE&t;BRIDGE_DMA_DIRECT_SIZE
DECL|macro|BRIDGE_DIRECT_32_TO_XTALK
mdefine_line|#define BRIDGE_DIRECT_32_TO_XTALK(dir_off,adr)&t;&t;&bslash;&n;&t;((dir_off) * BRIDGE_DIRECT_32_SEG_SIZE +&t;&bslash;&n;&t;&t;((adr) &amp; (BRIDGE_DIRECT_32_SEG_SIZE - 1)) + PHYS_RAMBASE)
multiline_comment|/* 64-bit address attribute masks */
DECL|macro|PCI64_ATTR_TARG_MASK
mdefine_line|#define PCI64_ATTR_TARG_MASK&t;0xf000000000000000
DECL|macro|PCI64_ATTR_TARG_SHFT
mdefine_line|#define PCI64_ATTR_TARG_SHFT&t;60
DECL|macro|PCI64_ATTR_PREF
mdefine_line|#define PCI64_ATTR_PREF&t;&t;0x0800000000000000
DECL|macro|PCI64_ATTR_PREC
mdefine_line|#define PCI64_ATTR_PREC&t;&t;0x0400000000000000
DECL|macro|PCI64_ATTR_VIRTUAL
mdefine_line|#define PCI64_ATTR_VIRTUAL&t;0x0200000000000000
DECL|macro|PCI64_ATTR_BAR
mdefine_line|#define PCI64_ATTR_BAR&t;&t;0x0100000000000000
DECL|macro|PCI64_ATTR_RMF_MASK
mdefine_line|#define PCI64_ATTR_RMF_MASK&t;0x00ff000000000000
DECL|macro|PCI64_ATTR_RMF_SHFT
mdefine_line|#define PCI64_ATTR_RMF_SHFT&t;48
macro_line|#if LANGUAGE_C
multiline_comment|/* Address translation entry for mapped pci32 accesses */
DECL|union|ate_u
r_typedef
r_union
id|ate_u
(brace
DECL|member|ent
id|u64
id|ent
suffix:semicolon
DECL|struct|ate_s
r_struct
id|ate_s
(brace
DECL|member|rmf
id|u64
id|rmf
suffix:colon
l_int|16
suffix:semicolon
DECL|member|addr
id|u64
id|addr
suffix:colon
l_int|36
suffix:semicolon
DECL|member|targ
id|u64
id|targ
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved
id|u64
id|reserved
suffix:colon
l_int|3
suffix:semicolon
DECL|member|barrier
id|u64
id|barrier
suffix:colon
l_int|1
suffix:semicolon
DECL|member|prefetch
id|u64
id|prefetch
suffix:colon
l_int|1
suffix:semicolon
DECL|member|precise
id|u64
id|precise
suffix:colon
l_int|1
suffix:semicolon
DECL|member|coherent
id|u64
id|coherent
suffix:colon
l_int|1
suffix:semicolon
DECL|member|valid
id|u64
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|field
)brace
id|field
suffix:semicolon
DECL|typedef|ate_t
)brace
id|ate_t
suffix:semicolon
macro_line|#endif /* LANGUAGE_C */
DECL|macro|ATE_V
mdefine_line|#define ATE_V&t;&t;0x01
DECL|macro|ATE_CO
mdefine_line|#define ATE_CO&t;&t;0x02
DECL|macro|ATE_PREC
mdefine_line|#define ATE_PREC&t;0x04
DECL|macro|ATE_PREF
mdefine_line|#define ATE_PREF&t;0x08
DECL|macro|ATE_BAR
mdefine_line|#define ATE_BAR&t;&t;0x10
DECL|macro|ATE_PFNSHIFT
mdefine_line|#define ATE_PFNSHIFT&t;&t;12
DECL|macro|ATE_TIDSHIFT
mdefine_line|#define ATE_TIDSHIFT&t;&t;8
DECL|macro|ATE_RMFSHIFT
mdefine_line|#define ATE_RMFSHIFT&t;&t;48
DECL|macro|mkate
mdefine_line|#define mkate(xaddr, xid, attr) ((xaddr) &amp; 0x0000fffffffff000ULL) | &bslash;&n;&t;&t;&t;&t;((xid)&lt;&lt;ATE_TIDSHIFT) | &bslash;&n;&t;&t;&t;&t;(attr)
DECL|macro|BRIDGE_INTERNAL_ATES
mdefine_line|#define BRIDGE_INTERNAL_ATES&t;128
multiline_comment|/* ========================================================================&n; *    Linux pci bus mappings to sn physical id&squot;s&n; */
DECL|variable|bus_to_wid
r_int
r_char
id|bus_to_wid
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* widget id for linux pci bus */
DECL|variable|bus_to_nid
r_int
r_char
id|bus_to_nid
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* nasid for linux pci bus */
DECL|variable|num_bridges
r_int
r_char
id|num_bridges
suffix:semicolon
multiline_comment|/* number of bridges in the system */
macro_line|#endif /* _ASM_PCI_BRIDGE_H */
eof
