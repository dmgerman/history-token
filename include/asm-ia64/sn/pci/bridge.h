multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_PCI_BRIDGE_H
DECL|macro|_ASM_SN_PCI_BRIDGE_H
mdefine_line|#define _ASM_SN_PCI_BRIDGE_H
multiline_comment|/*&n; * bridge.h - header file for bridge chip and bridge portion of xbridge chip&n; *&n; * Also including offsets for unique PIC registers.&n; * The PIC asic is a follow-on to Xbridge and most of its registers are&n; * identical to those of Xbridge.  PIC is different than Xbridge in that&n; * it will accept 64 bit register access and that, in some cases, data&n; * is kept in bits 63:32.   PIC registers that are identical to Xbridge&n; * may be accessed identically to the Xbridge registers, allowing for lots&n; * of code reuse.  Here are the access rules as described in the PIC&n; * manual:&n; * &n; * &t;o Read a word on a DW boundary returns D31:00 of reg.&n; * &t;o Read a DW on a DW boundary returns D63:00 of reg.&n; * &t;o Write a word on a DW boundary loads D31:00 of reg.&n; * &t;o Write a DW on a DW boundary loads D63:00 of reg.&n; * &t;o No support for word boundary access that is not double word&n; *           aligned.&n; * &n; * So we can reuse a lot of bridge_s for PIC.  In bridge_s are included&n; * #define tags and unions for 64 bit access to PIC registers.&n; * For a detailed PIC register layout see pic.h.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;
macro_line|#include &lt;asm/sn/pci/pic.h&gt;
r_extern
r_int
id|io_get_sh_swapper
c_func
(paren
id|nasid_t
)paren
suffix:semicolon
DECL|macro|BRIDGE_REG_GET32
mdefine_line|#define BRIDGE_REG_GET32(reg) &bslash;&n;                __swab32( *(volatile uint32_t *) (((uint64_t)reg)^4) )
DECL|macro|BRIDGE_REG_SET32
mdefine_line|#define BRIDGE_REG_SET32(reg) &bslash;&n;                *(volatile uint32_t *) (((uint64_t)reg)^4)
multiline_comment|/* I/O page size */
macro_line|#if _PAGESZ == 4096
DECL|macro|IOPFNSHIFT
mdefine_line|#define IOPFNSHIFT&t;&t;12&t;/* 4K per mapped page */
macro_line|#else
DECL|macro|IOPFNSHIFT
mdefine_line|#define IOPFNSHIFT&t;&t;14&t;/* 16K per mapped page */
macro_line|#endif&t;&t;&t;&t;/* _PAGESZ */
DECL|macro|IOPGSIZE
mdefine_line|#define IOPGSIZE&t;&t;(1 &lt;&lt; IOPFNSHIFT)
DECL|macro|IOPG
mdefine_line|#define IOPG(x)&t;&t;&t;((x) &gt;&gt; IOPFNSHIFT)
DECL|macro|IOPGOFF
mdefine_line|#define IOPGOFF(x)&t;&t;((x) &amp; (IOPGSIZE-1))
multiline_comment|/* Bridge RAM sizes */
DECL|macro|BRIDGE_INTERNAL_ATES
mdefine_line|#define BRIDGE_INTERNAL_ATES&t;128
DECL|macro|XBRIDGE_INTERNAL_ATES
mdefine_line|#define XBRIDGE_INTERNAL_ATES&t;1024
DECL|macro|BRIDGE_ATE_RAM_SIZE
mdefine_line|#define BRIDGE_ATE_RAM_SIZE     (BRIDGE_INTERNAL_ATES&lt;&lt;3)&t;/* 1kB ATE */
DECL|macro|XBRIDGE_ATE_RAM_SIZE
mdefine_line|#define XBRIDGE_ATE_RAM_SIZE    (XBRIDGE_INTERNAL_ATES&lt;&lt;3)&t;/* 8kB ATE */
DECL|macro|PIC_WR_REQ_BUFSIZE
mdefine_line|#define PIC_WR_REQ_BUFSIZE      256
DECL|macro|BRIDGE_CONFIG_BASE
mdefine_line|#define BRIDGE_CONFIG_BASE&t;0x20000&t;&t;/* start of bridge&squot;s */
multiline_comment|/* map to each device&squot;s */
multiline_comment|/* config space */
DECL|macro|BRIDGE_CONFIG1_BASE
mdefine_line|#define BRIDGE_CONFIG1_BASE&t;0x28000&t;&t;/* type 1 device config space */
DECL|macro|BRIDGE_CONFIG_END
mdefine_line|#define BRIDGE_CONFIG_END&t;0x30000
DECL|macro|BRIDGE_CONFIG_SLOT_SIZE
mdefine_line|#define BRIDGE_CONFIG_SLOT_SIZE 0x1000&t;&t;/* each map == 4k */
DECL|macro|BRIDGE_SSRAM_512K
mdefine_line|#define BRIDGE_SSRAM_512K&t;0x00080000&t;/* 512kB */
DECL|macro|BRIDGE_SSRAM_128K
mdefine_line|#define BRIDGE_SSRAM_128K&t;0x00020000&t;/* 128kB */
DECL|macro|BRIDGE_SSRAM_64K
mdefine_line|#define BRIDGE_SSRAM_64K&t;0x00010000&t;/* 64kB */
DECL|macro|BRIDGE_SSRAM_0K
mdefine_line|#define BRIDGE_SSRAM_0K&t;&t;0x00000000&t;/* 0kB */
multiline_comment|/* ========================================================================&n; *    Bridge address map&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
multiline_comment|/*&n; * All accesses to bridge hardware registers must be done&n; * using 32-bit loads and stores.&n; */
DECL|typedef|bridgereg_t
r_typedef
r_uint32
id|bridgereg_t
suffix:semicolon
DECL|typedef|bridge_ate_t
r_typedef
r_uint64
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
multiline_comment|/*&n; * pic_widget_cfg_s is a local definition of widget_cfg_t but with&n; * a union of 64bit &amp; 32bit registers, since PIC has 64bit widget&n; * registers but BRIDGE and XBRIDGE have 32bit.&t; PIC registers that&n; * have valid bits (ie. not just reserved) in the upper 32bits are&n; * defined as a union so we can access them as 64bit for PIC and&n; * as 32bit for BRIDGE and XBRIDGE.&n; */
DECL|struct|pic_widget_cfg_s
r_typedef
r_volatile
r_struct
id|pic_widget_cfg_s
(brace
DECL|member|_b_wid_id
id|bridgereg_t
id|_b_wid_id
suffix:semicolon
multiline_comment|/* 0x000004 */
DECL|member|_pad_000000
id|bridgereg_t
id|_pad_000000
suffix:semicolon
r_union
(brace
DECL|member|_p_wid_stat
id|picreg_t
id|_p_wid_stat
suffix:semicolon
multiline_comment|/* 0x000008 */
r_struct
(brace
DECL|member|_b_wid_stat
id|bridgereg_t
id|_b_wid_stat
suffix:semicolon
multiline_comment|/* 0x00000C */
DECL|member|_b_pad_000008
id|bridgereg_t
id|_b_pad_000008
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_wid_stat
)brace
id|u_wid_stat
suffix:semicolon
DECL|macro|__p_wid_stat_64
mdefine_line|#define __p_wid_stat_64 u_wid_stat._p_wid_stat
DECL|macro|__b_wid_stat
mdefine_line|#define __b_wid_stat u_wid_stat._b._b_wid_stat
DECL|member|_b_wid_err_upper
id|bridgereg_t
id|_b_wid_err_upper
suffix:semicolon
multiline_comment|/* 0x000014 */
DECL|member|_pad_000010
id|bridgereg_t
id|_pad_000010
suffix:semicolon
r_union
(brace
DECL|member|_p_wid_err_lower
id|picreg_t
id|_p_wid_err_lower
suffix:semicolon
multiline_comment|/* 0x000018 */
r_struct
(brace
DECL|member|_b_wid_err_lower
id|bridgereg_t
id|_b_wid_err_lower
suffix:semicolon
multiline_comment|/* 0x00001C */
DECL|member|_b_pad_000018
id|bridgereg_t
id|_b_pad_000018
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_wid_err_lower
)brace
id|u_wid_err_lower
suffix:semicolon
DECL|macro|__p_wid_err_64
mdefine_line|#define __p_wid_err_64 u_wid_err_lower._p_wid_err_lower
DECL|macro|__b_wid_err_lower
mdefine_line|#define __b_wid_err_lower u_wid_err_lower._b._b_wid_err_lower
r_union
(brace
DECL|member|_p_wid_control
id|picreg_t
id|_p_wid_control
suffix:semicolon
multiline_comment|/* 0x000020 */
r_struct
(brace
DECL|member|_b_wid_control
id|bridgereg_t
id|_b_wid_control
suffix:semicolon
multiline_comment|/* 0x000024 */
DECL|member|_b_pad_000020
id|bridgereg_t
id|_b_pad_000020
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_wid_control
)brace
id|u_wid_control
suffix:semicolon
DECL|macro|__p_wid_control_64
mdefine_line|#define __p_wid_control_64 u_wid_control._p_wid_control
DECL|macro|__b_wid_control
mdefine_line|#define __b_wid_control u_wid_control._b._b_wid_control
DECL|member|_b_wid_req_timeout
id|bridgereg_t
id|_b_wid_req_timeout
suffix:semicolon
multiline_comment|/* 0x00002C */
DECL|member|_pad_000028
id|bridgereg_t
id|_pad_000028
suffix:semicolon
DECL|member|_b_wid_int_upper
id|bridgereg_t
id|_b_wid_int_upper
suffix:semicolon
multiline_comment|/* 0x000034 */
DECL|member|_pad_000030
id|bridgereg_t
id|_pad_000030
suffix:semicolon
r_union
(brace
DECL|member|_p_wid_int_lower
id|picreg_t
id|_p_wid_int_lower
suffix:semicolon
multiline_comment|/* 0x000038 */
r_struct
(brace
DECL|member|_b_wid_int_lower
id|bridgereg_t
id|_b_wid_int_lower
suffix:semicolon
multiline_comment|/* 0x00003C */
DECL|member|_b_pad_000038
id|bridgereg_t
id|_b_pad_000038
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_wid_int_lower
)brace
id|u_wid_int_lower
suffix:semicolon
DECL|macro|__p_wid_int_64
mdefine_line|#define __p_wid_int_64 u_wid_int_lower._p_wid_int_lower
DECL|macro|__b_wid_int_lower
mdefine_line|#define __b_wid_int_lower u_wid_int_lower._b._b_wid_int_lower
DECL|member|_b_wid_err_cmdword
id|bridgereg_t
id|_b_wid_err_cmdword
suffix:semicolon
multiline_comment|/* 0x000044 */
DECL|member|_pad_000040
id|bridgereg_t
id|_pad_000040
suffix:semicolon
DECL|member|_b_wid_llp
id|bridgereg_t
id|_b_wid_llp
suffix:semicolon
multiline_comment|/* 0x00004C */
DECL|member|_pad_000048
id|bridgereg_t
id|_pad_000048
suffix:semicolon
DECL|member|_b_wid_tflush
id|bridgereg_t
id|_b_wid_tflush
suffix:semicolon
multiline_comment|/* 0x000054 */
DECL|member|_pad_000050
id|bridgereg_t
id|_pad_000050
suffix:semicolon
DECL|typedef|pic_widget_cfg_t
)brace
id|pic_widget_cfg_t
suffix:semicolon
multiline_comment|/*&n; * BRIDGE, XBRIDGE, PIC register definitions.  NOTE: Prior to PIC, registers&n; * were a 32bit quantity and double word aligned (and only accessible as a&n; * 32bit word.  PIC registers are 64bits and accessible as words or double&n; * words.  PIC registers that have valid bits (ie. not just reserved) in the&n; * upper 32bits are defined as a union of one 64bit picreg_t and two 32bit&n; * bridgereg_t so we can access them both ways.&n; *&n; * It is generally preferred that hardware registers on the bridge are&n; * located from C code via this structure.&n; *&n; * Generated from Bridge spec dated 04oct95&n; */
DECL|struct|bridge_s
r_typedef
r_volatile
r_struct
id|bridge_s
(brace
multiline_comment|/* 0x000000-0x00FFFF -- Local Registers */
multiline_comment|/* 0x000000-0x000057 -- Standard Widget Configuration */
r_union
(brace
DECL|member|xtalk_widget_def
id|widget_cfg_t
id|xtalk_widget_def
suffix:semicolon
multiline_comment|/* 0x000000 */
DECL|member|local_widget_def
id|pic_widget_cfg_t
id|local_widget_def
suffix:semicolon
multiline_comment|/* 0x000000 */
DECL|member|u_wid
)brace
id|u_wid
suffix:semicolon
multiline_comment|/* 32bit widget register access via the widget_cfg_t */
DECL|macro|b_widget
mdefine_line|#define b_widget u_wid.xtalk_widget_def
multiline_comment|/* 32bit widget register access via the pic_widget_cfg_t */
DECL|macro|b_wid_id
mdefine_line|#define b_wid_id u_wid.local_widget_def._b_wid_id
DECL|macro|b_wid_stat
mdefine_line|#define b_wid_stat u_wid.local_widget_def.__b_wid_stat
DECL|macro|b_wid_err_upper
mdefine_line|#define b_wid_err_upper u_wid.local_widget_def._b_wid_err_upper
DECL|macro|b_wid_err_lower
mdefine_line|#define b_wid_err_lower u_wid.local_widget_def.__b_wid_err_lower
DECL|macro|b_wid_control
mdefine_line|#define b_wid_control u_wid.local_widget_def.__b_wid_control
DECL|macro|b_wid_req_timeout
mdefine_line|#define b_wid_req_timeout u_wid.local_widget_def._b_wid_req_timeout
DECL|macro|b_wid_int_upper
mdefine_line|#define b_wid_int_upper u_wid.local_widget_def._b_wid_int_upper
DECL|macro|b_wid_int_lower
mdefine_line|#define b_wid_int_lower u_wid.local_widget_def.__b_wid_int_lower
DECL|macro|b_wid_err_cmdword
mdefine_line|#define b_wid_err_cmdword u_wid.local_widget_def._b_wid_err_cmdword
DECL|macro|b_wid_llp
mdefine_line|#define b_wid_llp u_wid.local_widget_def._b_wid_llp
DECL|macro|b_wid_tflush
mdefine_line|#define b_wid_tflush u_wid.local_widget_def._b_wid_tflush
multiline_comment|/* 64bit widget register access via the pic_widget_cfg_t */
DECL|macro|p_wid_stat_64
mdefine_line|#define p_wid_stat_64 u_wid.local_widget_def.__p_wid_stat_64
DECL|macro|p_wid_err_64
mdefine_line|#define p_wid_err_64 u_wid.local_widget_def.__p_wid_err_64
DECL|macro|p_wid_control_64
mdefine_line|#define p_wid_control_64 u_wid.local_widget_def.__p_wid_control_64
DECL|macro|p_wid_int_64
mdefine_line|#define p_wid_int_64 u_wid.local_widget_def.__p_wid_int_64
multiline_comment|/* 0x000058-0x00007F -- Bridge-specific Widget Configuration */
DECL|member|b_wid_aux_err
id|bridgereg_t
id|b_wid_aux_err
suffix:semicolon
multiline_comment|/* 0x00005C */
DECL|member|_pad_000058
id|bridgereg_t
id|_pad_000058
suffix:semicolon
DECL|member|b_wid_resp_upper
id|bridgereg_t
id|b_wid_resp_upper
suffix:semicolon
multiline_comment|/* 0x000064 */
DECL|member|_pad_000060
id|bridgereg_t
id|_pad_000060
suffix:semicolon
r_union
(brace
DECL|member|_p_wid_resp_lower
id|picreg_t
id|_p_wid_resp_lower
suffix:semicolon
multiline_comment|/* 0x000068 */
r_struct
(brace
DECL|member|_b_wid_resp_lower
id|bridgereg_t
id|_b_wid_resp_lower
suffix:semicolon
multiline_comment|/* 0x00006C */
DECL|member|_b_pad_000068
id|bridgereg_t
id|_b_pad_000068
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_wid_resp_lower
)brace
id|u_wid_resp_lower
suffix:semicolon
DECL|macro|p_wid_resp_64
mdefine_line|#define p_wid_resp_64 u_wid_resp_lower._p_wid_resp_lower
DECL|macro|b_wid_resp_lower
mdefine_line|#define b_wid_resp_lower u_wid_resp_lower._b._b_wid_resp_lower
DECL|member|b_wid_tst_pin_ctrl
id|bridgereg_t
id|b_wid_tst_pin_ctrl
suffix:semicolon
multiline_comment|/* 0x000074 */
DECL|member|_pad_000070
id|bridgereg_t
id|_pad_000070
suffix:semicolon
r_union
(brace
DECL|member|_p_addr_lkerr
id|picreg_t
id|_p_addr_lkerr
suffix:semicolon
multiline_comment|/* 0x000078 */
r_struct
(brace
DECL|member|_b_pad_00007C
id|bridgereg_t
id|_b_pad_00007C
suffix:semicolon
DECL|member|_b_pad_000078
id|bridgereg_t
id|_b_pad_000078
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_addr_lkerr
)brace
id|u_addr_lkerr
suffix:semicolon
DECL|macro|p_addr_lkerr_64
mdefine_line|#define p_addr_lkerr_64 u_addr_lkerr._p_addr_lkerr
multiline_comment|/* 0x000080-0x00008F -- PMU */
DECL|member|b_dir_map
id|bridgereg_t
id|b_dir_map
suffix:semicolon
multiline_comment|/* 0x000084 */
DECL|member|_pad_000080
id|bridgereg_t
id|_pad_000080
suffix:semicolon
DECL|member|_pad_00008C
id|bridgereg_t
id|_pad_00008C
suffix:semicolon
DECL|member|_pad_000088
id|bridgereg_t
id|_pad_000088
suffix:semicolon
multiline_comment|/* 0x000090-0x00009F -- SSRAM */
DECL|member|b_ram_perr_or_map_fault
id|bridgereg_t
id|b_ram_perr_or_map_fault
suffix:semicolon
multiline_comment|/* 0x000094 */
DECL|member|_pad_000090
id|bridgereg_t
id|_pad_000090
suffix:semicolon
DECL|macro|b_ram_perr
mdefine_line|#define b_ram_perr  b_ram_perr_or_map_fault     /* Bridge */
DECL|macro|b_map_fault
mdefine_line|#define b_map_fault b_ram_perr_or_map_fault     /* Xbridge &amp; PIC */
DECL|member|_pad_00009C
id|bridgereg_t
id|_pad_00009C
suffix:semicolon
DECL|member|_pad_000098
id|bridgereg_t
id|_pad_000098
suffix:semicolon
multiline_comment|/* 0x0000A0-0x0000AF -- Arbitration */
DECL|member|b_arb
id|bridgereg_t
id|b_arb
suffix:semicolon
multiline_comment|/* 0x0000A4 */
DECL|member|_pad_0000A0
id|bridgereg_t
id|_pad_0000A0
suffix:semicolon
DECL|member|_pad_0000AC
id|bridgereg_t
id|_pad_0000AC
suffix:semicolon
DECL|member|_pad_0000A8
id|bridgereg_t
id|_pad_0000A8
suffix:semicolon
multiline_comment|/* 0x0000B0-0x0000BF -- Number In A Can or ATE Parity Error */
r_union
(brace
DECL|member|_p_ate_parity_err
id|picreg_t
id|_p_ate_parity_err
suffix:semicolon
multiline_comment|/* 0x0000B0 */
r_struct
(brace
DECL|member|_b_nic
id|bridgereg_t
id|_b_nic
suffix:semicolon
multiline_comment|/* 0x0000B4 */
DECL|member|_b_pad_0000B0
id|bridgereg_t
id|_b_pad_0000B0
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_ate_parity_err_or_nic
)brace
id|u_ate_parity_err_or_nic
suffix:semicolon
DECL|macro|p_ate_parity_err_64
mdefine_line|#define p_ate_parity_err_64 u_ate_parity_err_or_nic._p_ate_parity_err
DECL|macro|b_nic
mdefine_line|#define b_nic u_ate_parity_err_or_nic._b._b_nic
DECL|member|_pad_0000BC
id|bridgereg_t
id|_pad_0000BC
suffix:semicolon
DECL|member|_pad_0000B8
id|bridgereg_t
id|_pad_0000B8
suffix:semicolon
multiline_comment|/* 0x0000C0-0x0000FF -- PCI/GIO */
DECL|member|b_bus_timeout
id|bridgereg_t
id|b_bus_timeout
suffix:semicolon
multiline_comment|/* 0x0000C4 */
DECL|member|_pad_0000C0
id|bridgereg_t
id|_pad_0000C0
suffix:semicolon
DECL|macro|b_pci_bus_timeout
mdefine_line|#define b_pci_bus_timeout b_bus_timeout
DECL|member|b_pci_cfg
id|bridgereg_t
id|b_pci_cfg
suffix:semicolon
multiline_comment|/* 0x0000CC */
DECL|member|_pad_0000C8
id|bridgereg_t
id|_pad_0000C8
suffix:semicolon
DECL|member|b_pci_err_upper
id|bridgereg_t
id|b_pci_err_upper
suffix:semicolon
multiline_comment|/* 0x0000D4 */
DECL|member|_pad_0000D0
id|bridgereg_t
id|_pad_0000D0
suffix:semicolon
DECL|macro|b_gio_err_upper
mdefine_line|#define b_gio_err_upper b_pci_err_upper
r_union
(brace
DECL|member|_p_pci_err_lower
id|picreg_t
id|_p_pci_err_lower
suffix:semicolon
multiline_comment|/* 0x0000D8 */
r_struct
(brace
DECL|member|_b_pci_err_lower
id|bridgereg_t
id|_b_pci_err_lower
suffix:semicolon
multiline_comment|/* 0x0000DC */
DECL|member|_b_pad_0000D8
id|bridgereg_t
id|_b_pad_0000D8
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_pci_err_lower
)brace
id|u_pci_err_lower
suffix:semicolon
DECL|macro|p_pci_err_64
mdefine_line|#define p_pci_err_64 u_pci_err_lower._p_pci_err_lower
DECL|macro|b_pci_err_lower
mdefine_line|#define b_pci_err_lower u_pci_err_lower._b._b_pci_err_lower
DECL|macro|b_gio_err_lower
mdefine_line|#define b_gio_err_lower b_pci_err_lower
DECL|member|_pad_0000E0
id|bridgereg_t
id|_pad_0000E0
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x000100-0x0001FF -- Interrupt */
r_union
(brace
DECL|member|_p_int_status
id|picreg_t
id|_p_int_status
suffix:semicolon
multiline_comment|/* 0x000100 */
r_struct
(brace
DECL|member|_b_int_status
id|bridgereg_t
id|_b_int_status
suffix:semicolon
multiline_comment|/* 0x000104 */
DECL|member|_b_pad_000100
id|bridgereg_t
id|_b_pad_000100
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_int_status
)brace
id|u_int_status
suffix:semicolon
DECL|macro|p_int_status_64
mdefine_line|#define p_int_status_64 u_int_status._p_int_status
DECL|macro|b_int_status
mdefine_line|#define b_int_status u_int_status._b._b_int_status
r_union
(brace
DECL|member|_p_int_enable
id|picreg_t
id|_p_int_enable
suffix:semicolon
multiline_comment|/* 0x000108 */
r_struct
(brace
DECL|member|_b_int_enable
id|bridgereg_t
id|_b_int_enable
suffix:semicolon
multiline_comment|/* 0x00010C */
DECL|member|_b_pad_000108
id|bridgereg_t
id|_b_pad_000108
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_int_enable
)brace
id|u_int_enable
suffix:semicolon
DECL|macro|p_int_enable_64
mdefine_line|#define p_int_enable_64 u_int_enable._p_int_enable
DECL|macro|b_int_enable
mdefine_line|#define b_int_enable u_int_enable._b._b_int_enable
r_union
(brace
DECL|member|_p_int_rst_stat
id|picreg_t
id|_p_int_rst_stat
suffix:semicolon
multiline_comment|/* 0x000110 */
r_struct
(brace
DECL|member|_b_int_rst_stat
id|bridgereg_t
id|_b_int_rst_stat
suffix:semicolon
multiline_comment|/* 0x000114 */
DECL|member|_b_pad_000110
id|bridgereg_t
id|_b_pad_000110
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_int_rst_stat
)brace
id|u_int_rst_stat
suffix:semicolon
DECL|macro|p_int_rst_stat_64
mdefine_line|#define p_int_rst_stat_64 u_int_rst_stat._p_int_rst_stat
DECL|macro|b_int_rst_stat
mdefine_line|#define b_int_rst_stat u_int_rst_stat._b._b_int_rst_stat
DECL|member|b_int_mode
id|bridgereg_t
id|b_int_mode
suffix:semicolon
multiline_comment|/* 0x00011C */
DECL|member|_pad_000118
id|bridgereg_t
id|_pad_000118
suffix:semicolon
DECL|member|b_int_device
id|bridgereg_t
id|b_int_device
suffix:semicolon
multiline_comment|/* 0x000124 */
DECL|member|_pad_000120
id|bridgereg_t
id|_pad_000120
suffix:semicolon
DECL|member|b_int_host_err
id|bridgereg_t
id|b_int_host_err
suffix:semicolon
multiline_comment|/* 0x00012C */
DECL|member|_pad_000128
id|bridgereg_t
id|_pad_000128
suffix:semicolon
r_union
(brace
DECL|member|_p_int_addr
id|picreg_t
id|_p_int_addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{30,,,68} */
r_struct
(brace
DECL|member|addr
id|bridgereg_t
id|addr
suffix:semicolon
multiline_comment|/* 0x0001{34,,,6C} */
DECL|member|_b_pad
id|bridgereg_t
id|_b_pad
suffix:semicolon
DECL|member|_b
)brace
id|_b
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|u_int_addr
)brace
id|u_int_addr
suffix:semicolon
DECL|macro|p_int_addr_64
mdefine_line|#define p_int_addr_64 u_int_addr._p_int_addr
DECL|macro|b_int_addr
mdefine_line|#define b_int_addr u_int_addr._b
r_union
(brace
DECL|member|_p_err_int_view
id|picreg_t
id|_p_err_int_view
suffix:semicolon
multiline_comment|/* 0x000170 */
r_struct
(brace
DECL|member|_b_err_int_view
id|bridgereg_t
id|_b_err_int_view
suffix:semicolon
multiline_comment|/* 0x000174 */
DECL|member|_b_pad_000170
id|bridgereg_t
id|_b_pad_000170
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_err_int_view
)brace
id|u_err_int_view
suffix:semicolon
DECL|macro|p_err_int_view_64
mdefine_line|#define p_err_int_view_64 u_err_int_view._p_err_int_view
DECL|macro|b_err_int_view
mdefine_line|#define b_err_int_view u_err_int_view._b._b_err_int_view
r_union
(brace
DECL|member|_p_mult_int
id|picreg_t
id|_p_mult_int
suffix:semicolon
multiline_comment|/* 0x000178 */
r_struct
(brace
DECL|member|_b_mult_int
id|bridgereg_t
id|_b_mult_int
suffix:semicolon
multiline_comment|/* 0x00017C */
DECL|member|_b_pad_000178
id|bridgereg_t
id|_b_pad_000178
suffix:semicolon
DECL|member|_b
)brace
id|_b
suffix:semicolon
DECL|member|u_mult_int
)brace
id|u_mult_int
suffix:semicolon
DECL|macro|p_mult_int_64
mdefine_line|#define p_mult_int_64 u_mult_int._p_mult_int
DECL|macro|b_mult_int
mdefine_line|#define b_mult_int u_mult_int._b._b_mult_int
r_struct
(brace
DECL|member|intr
id|bridgereg_t
id|intr
suffix:semicolon
multiline_comment|/* 0x0001{84,,,BC} */
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
DECL|member|b_force_always
)brace
id|b_force_always
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
DECL|member|intr
id|bridgereg_t
id|intr
suffix:semicolon
multiline_comment|/* 0x0001{C4,,,FC} */
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
DECL|member|b_force_pin
)brace
id|b_force_pin
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x000200-0x0003FF -- Device */
r_struct
(brace
DECL|member|reg
id|bridgereg_t
id|reg
suffix:semicolon
multiline_comment|/* 0x0002{04,,,3C} */
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
DECL|member|b_device
)brace
id|b_device
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
DECL|member|reg
id|bridgereg_t
id|reg
suffix:semicolon
multiline_comment|/* 0x0002{44,,,7C} */
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
DECL|member|b_wr_req_buf
)brace
id|b_wr_req_buf
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
DECL|member|reg
id|bridgereg_t
id|reg
suffix:semicolon
multiline_comment|/* 0x0002{84,,,8C} */
DECL|member|__pad
id|bridgereg_t
id|__pad
suffix:semicolon
DECL|member|b_rrb_map
)brace
id|b_rrb_map
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|b_even_resp
mdefine_line|#define b_even_resp&t;b_rrb_map[0].reg&t;    /* 0x000284 */
DECL|macro|b_odd_resp
mdefine_line|#define b_odd_resp&t;b_rrb_map[1].reg&t;    /* 0x00028C */
DECL|member|b_resp_status
id|bridgereg_t
id|b_resp_status
suffix:semicolon
multiline_comment|/* 0x000294 */
DECL|member|_pad_000290
id|bridgereg_t
id|_pad_000290
suffix:semicolon
DECL|member|b_resp_clear
id|bridgereg_t
id|b_resp_clear
suffix:semicolon
multiline_comment|/* 0x00029C */
DECL|member|_pad_000298
id|bridgereg_t
id|_pad_000298
suffix:semicolon
DECL|member|_pad_0002A0
id|bridgereg_t
id|_pad_0002A0
(braket
l_int|24
)braket
suffix:semicolon
multiline_comment|/* Xbridge/PIC only */
r_union
(brace
r_struct
(brace
DECL|member|lower
id|picreg_t
id|lower
suffix:semicolon
multiline_comment|/* 0x0003{08,,,F8} */
DECL|member|upper
id|picreg_t
id|upper
suffix:semicolon
multiline_comment|/* 0x0003{00,,,F0} */
DECL|member|_p
)brace
id|_p
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|upper
id|bridgereg_t
id|upper
suffix:semicolon
multiline_comment|/* 0x0003{04,,,F4} */
DECL|member|_b_pad1
id|bridgereg_t
id|_b_pad1
suffix:semicolon
DECL|member|lower
id|bridgereg_t
id|lower
suffix:semicolon
multiline_comment|/* 0x0003{0C,,,FC} */
DECL|member|_b_pad2
id|bridgereg_t
id|_b_pad2
suffix:semicolon
DECL|member|_b
)brace
id|_b
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|u_buf_addr_match
)brace
id|u_buf_addr_match
suffix:semicolon
DECL|macro|p_buf_addr_match_64
mdefine_line|#define p_buf_addr_match_64 u_buf_addr_match._p
DECL|macro|b_buf_addr_match
mdefine_line|#define b_buf_addr_match u_buf_addr_match._b
multiline_comment|/* 0x000400-0x0005FF -- Performance Monitor Registers (even only) */
r_struct
(brace
DECL|member|flush_w_touch
id|bridgereg_t
id|flush_w_touch
suffix:semicolon
multiline_comment|/* 0x000{404,,,5C4} */
DECL|member|__pad1
id|bridgereg_t
id|__pad1
suffix:semicolon
DECL|member|flush_wo_touch
id|bridgereg_t
id|flush_wo_touch
suffix:semicolon
multiline_comment|/* 0x000{40C,,,5CC} */
DECL|member|__pad2
id|bridgereg_t
id|__pad2
suffix:semicolon
DECL|member|inflight
id|bridgereg_t
id|inflight
suffix:semicolon
multiline_comment|/* 0x000{414,,,5D4} */
DECL|member|__pad3
id|bridgereg_t
id|__pad3
suffix:semicolon
DECL|member|prefetch
id|bridgereg_t
id|prefetch
suffix:semicolon
multiline_comment|/* 0x000{41C,,,5DC} */
DECL|member|__pad4
id|bridgereg_t
id|__pad4
suffix:semicolon
DECL|member|total_pci_retry
id|bridgereg_t
id|total_pci_retry
suffix:semicolon
multiline_comment|/* 0x000{424,,,5E4} */
DECL|member|__pad5
id|bridgereg_t
id|__pad5
suffix:semicolon
DECL|member|max_pci_retry
id|bridgereg_t
id|max_pci_retry
suffix:semicolon
multiline_comment|/* 0x000{42C,,,5EC} */
DECL|member|__pad6
id|bridgereg_t
id|__pad6
suffix:semicolon
DECL|member|max_latency
id|bridgereg_t
id|max_latency
suffix:semicolon
multiline_comment|/* 0x000{434,,,5F4} */
DECL|member|__pad7
id|bridgereg_t
id|__pad7
suffix:semicolon
DECL|member|clear_all
id|bridgereg_t
id|clear_all
suffix:semicolon
multiline_comment|/* 0x000{43C,,,5FC} */
DECL|member|__pad8
id|bridgereg_t
id|__pad8
suffix:semicolon
DECL|member|b_buf_count
)brace
id|b_buf_count
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*&n;     * &quot;PCI/X registers that are specific to PIC&quot;.   See pic.h.&n;     */
multiline_comment|/* 0x000600-0x0009FF -- PCI/X registers */
DECL|member|p_pcix_bus_err_addr_64
id|picreg_t
id|p_pcix_bus_err_addr_64
suffix:semicolon
multiline_comment|/* 0x000600 */
DECL|member|p_pcix_bus_err_attr_64
id|picreg_t
id|p_pcix_bus_err_attr_64
suffix:semicolon
multiline_comment|/* 0x000608 */
DECL|member|p_pcix_bus_err_data_64
id|picreg_t
id|p_pcix_bus_err_data_64
suffix:semicolon
multiline_comment|/* 0x000610 */
DECL|member|p_pcix_pio_split_addr_64
id|picreg_t
id|p_pcix_pio_split_addr_64
suffix:semicolon
multiline_comment|/* 0x000618 */
DECL|member|p_pcix_pio_split_attr_64
id|picreg_t
id|p_pcix_pio_split_attr_64
suffix:semicolon
multiline_comment|/* 0x000620 */
DECL|member|p_pcix_dma_req_err_attr_64
id|picreg_t
id|p_pcix_dma_req_err_attr_64
suffix:semicolon
multiline_comment|/* 0x000628 */
DECL|member|p_pcix_dma_req_err_addr_64
id|picreg_t
id|p_pcix_dma_req_err_addr_64
suffix:semicolon
multiline_comment|/* 0x000630 */
DECL|member|p_pcix_timeout_64
id|picreg_t
id|p_pcix_timeout_64
suffix:semicolon
multiline_comment|/* 0x000638 */
DECL|member|_pad_000600
id|picreg_t
id|_pad_000600
(braket
l_int|120
)braket
suffix:semicolon
multiline_comment|/* 0x000A00-0x000BFF -- PCI/X Read&amp;Write Buffer */
r_struct
(brace
DECL|member|p_buf_attr
id|picreg_t
id|p_buf_attr
suffix:semicolon
multiline_comment|/* 0X000{A08,,,AF8} */
DECL|member|p_buf_addr
id|picreg_t
id|p_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{A00,,,AF0} */
DECL|member|p_pcix_read_buf_64
)brace
id|p_pcix_read_buf_64
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|p_buf_attr
id|picreg_t
id|p_buf_attr
suffix:semicolon
multiline_comment|/* 0x000{B08,,,BE8} */
DECL|member|p_buf_addr
id|picreg_t
id|p_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{B00,,,BE0} */
DECL|member|__pad1
id|picreg_t
id|__pad1
suffix:semicolon
multiline_comment|/* 0x000{B18,,,BF8} */
DECL|member|p_buf_valid
id|picreg_t
id|p_buf_valid
suffix:semicolon
multiline_comment|/* 0x000{B10,,,BF0} */
DECL|member|p_pcix_write_buf_64
)brace
id|p_pcix_write_buf_64
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* &n;     * end &quot;PCI/X registers that are specific to PIC&quot;&n;     */
DECL|member|_pad_000c00
r_char
id|_pad_000c00
(braket
l_int|0x010000
op_minus
l_int|0x000c00
)braket
suffix:semicolon
multiline_comment|/* 0x010000-0x011fff -- Internal Address Translation Entry RAM */
multiline_comment|/*&n;     * Xbridge and PIC have 1024 internal ATE&squot;s and the Bridge has 128.&n;     * Make enough room for the Xbridge/PIC ATE&squot;s and depend on runtime&n;     * checks to limit access to bridge ATE&squot;s.&n;     *&n;     * In [X]bridge the internal ATE Ram is writen as double words only,&n;     * but due to internal design issues it is read back as single words. &n;     * i.e:&n;     *   b_int_ate_ram[index].hi.rd &lt;&lt; 32 | xb_int_ate_ram_lo[index].rd&n;     */
r_union
(brace
DECL|member|wr
id|bridge_ate_t
id|wr
suffix:semicolon
multiline_comment|/* write-only */
multiline_comment|/* 0x01{0000,,,1FF8} */
r_struct
(brace
DECL|member|rd
id|bridgereg_t
id|rd
suffix:semicolon
multiline_comment|/* read-only */
multiline_comment|/* 0x01{0004,,,1FFC} */
DECL|member|_p_pad
id|bridgereg_t
id|_p_pad
suffix:semicolon
DECL|member|hi
)brace
id|hi
suffix:semicolon
DECL|member|b_int_ate_ram
)brace
id|b_int_ate_ram
(braket
id|XBRIDGE_INTERNAL_ATES
)braket
suffix:semicolon
DECL|macro|b_int_ate_ram_lo
mdefine_line|#define b_int_ate_ram_lo(idx) b_int_ate_ram[idx+512].hi.rd
multiline_comment|/* 0x012000-0x013fff -- Internal Address Translation Entry RAM LOW */
r_struct
(brace
DECL|member|rd
id|bridgereg_t
id|rd
suffix:semicolon
multiline_comment|/* read-only */
multiline_comment|/* 0x01{2004,,,3FFC} */
DECL|member|_p_pad
id|bridgereg_t
id|_p_pad
suffix:semicolon
DECL|member|xb_int_ate_ram_lo
)brace
id|xb_int_ate_ram_lo
(braket
id|XBRIDGE_INTERNAL_ATES
)braket
suffix:semicolon
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
multiline_comment|/* 0x18000 - 0x187F8 */
DECL|member|p_wr_req_lower
id|picreg_t
id|p_wr_req_lower
(braket
id|PIC_WR_REQ_BUFSIZE
)braket
suffix:semicolon
multiline_comment|/* 0x18800 - 0x18FF8 */
DECL|member|p_wr_req_upper
id|picreg_t
id|p_wr_req_upper
(braket
id|PIC_WR_REQ_BUFSIZE
)braket
suffix:semicolon
multiline_comment|/* 0x19000 - 0x197F8 */
DECL|member|p_wr_req_parity
id|picreg_t
id|p_wr_req_parity
(braket
id|PIC_WR_REQ_BUFSIZE
)braket
suffix:semicolon
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
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|uchar_t
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
id|uchar_t
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
DECL|member|b_type0_cfg_dev
)brace
id|b_type0_cfg_dev
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x02{0000,,,7FFF} */
multiline_comment|/* 0x028000-0x028FFF -- PCI Type 1 Configuration Space */
r_union
(brace
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|uchar_t
id|c
(braket
l_int|0x1000
op_div
l_int|1
)braket
suffix:semicolon
DECL|member|s
r_uint16
id|s
(braket
l_int|0x1000
op_div
l_int|2
)braket
suffix:semicolon
DECL|member|l
r_uint32
id|l
(braket
l_int|0x1000
op_div
l_int|4
)braket
suffix:semicolon
DECL|member|d
r_uint64
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
id|uchar_t
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
multiline_comment|/* 0x030000-0x030007 -- PCI Interrupt Acknowledge Cycle */
r_union
(brace
DECL|member|c
id|uchar_t
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
DECL|member|b_pci_iack
)brace
id|b_pci_iack
suffix:semicolon
multiline_comment|/* 0x030000-0x030007 */
DECL|member|_pad_030007
id|uchar_t
id|_pad_030007
(braket
l_int|0x04fff8
)braket
suffix:semicolon
multiline_comment|/* 0x030008-0x07FFFF */
multiline_comment|/* 0x080000-0x0FFFFF -- External Address Translation Entry RAM */
DECL|member|b_ext_ate_ram
id|bridge_ate_t
id|b_ext_ate_ram
(braket
l_int|0x10000
)braket
suffix:semicolon
multiline_comment|/* 0x100000-0x1FFFFF -- Reserved */
DECL|member|_pad_100000
r_char
id|_pad_100000
(braket
l_int|0x200000
op_minus
l_int|0x100000
)braket
suffix:semicolon
multiline_comment|/* 0x200000-0xBFFFFF -- PCI/GIO Device Spaces */
r_union
(brace
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|uchar_t
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
DECL|member|b_devio_raw
)brace
id|b_devio_raw
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* b_devio macro is a bit strange; it reflects the&n;     * fact that the Bridge ASIC provides 2M for the&n;     * first two DevIO windows and 1M for the other six.&n;     */
DECL|macro|b_devio
mdefine_line|#define b_devio(n)&t;b_devio_raw[((n)&lt;2)?(n*2):(n+2)]
multiline_comment|/* 0xC00000-0xFFFFFF -- External Flash Proms 1,0 */
r_union
(brace
multiline_comment|/* make all access sizes available. */
DECL|member|c
id|uchar_t
id|c
(braket
l_int|0x400000
op_div
l_int|1
)braket
suffix:semicolon
multiline_comment|/* read-only */
DECL|member|s
r_uint16
id|s
(braket
l_int|0x400000
op_div
l_int|2
)braket
suffix:semicolon
multiline_comment|/* read-write */
DECL|member|l
r_uint32
id|l
(braket
l_int|0x400000
op_div
l_int|4
)braket
suffix:semicolon
multiline_comment|/* read-only */
DECL|member|d
r_uint64
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
DECL|typedef|bridge_t
)brace
id|bridge_t
suffix:semicolon
DECL|macro|berr_field
mdefine_line|#define berr_field&t;berr_un.berr_st
macro_line|#endif&t;&t;&t;&t;/* __ASSEMBLY__ */
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
multiline_comment|/* Bridge has SSRAM Parity Error and Xbridge has Map Fault here */
DECL|macro|BRIDGE_RAM_PERR
mdefine_line|#define BRIDGE_RAM_PERR &t;0x000094&t;/* SSRAM Parity Error */
DECL|macro|BRIDGE_MAP_FAULT
mdefine_line|#define BRIDGE_MAP_FAULT&t;0x000094&t;/* Map Fault */
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
DECL|macro|BRIDGE_INT_VIEW
mdefine_line|#define BRIDGE_INT_VIEW&t;&t;0x000174&t;/* Interrupt view */
DECL|macro|BRIDGE_MULTIPLE_INT
mdefine_line|#define BRIDGE_MULTIPLE_INT&t;0x00017c&t;/* Multiple interrupt occurred */
DECL|macro|BRIDGE_FORCE_ALWAYS0
mdefine_line|#define BRIDGE_FORCE_ALWAYS0&t;0x000184&t;/* Force an interrupt (always)*/
DECL|macro|BRIDGE_FORCE_ALWAYS_OFF
mdefine_line|#define BRIDGE_FORCE_ALWAYS_OFF 0x000008&t;/* Force Always offset */
DECL|macro|BRIDGE_FORCE_ALWAYS
mdefine_line|#define BRIDGE_FORCE_ALWAYS(x)  (BRIDGE_FORCE_ALWAYS0+(x)*BRIDGE_FORCE_ALWAYS_OFF)
DECL|macro|BRIDGE_FORCE_PIN0
mdefine_line|#define BRIDGE_FORCE_PIN0&t;0x0001c4&t;/* Force an interrupt */
DECL|macro|BRIDGE_FORCE_PIN_OFF
mdefine_line|#define BRIDGE_FORCE_PIN_OFF &t;0x000008&t;/* Force Pin offset */
DECL|macro|BRIDGE_FORCE_PIN
mdefine_line|#define BRIDGE_FORCE_PIN(x)  (BRIDGE_FORCE_PIN0+(x)*BRIDGE_FORCE_PIN_OFF)
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
DECL|macro|BRIDGE_BUF_ADDR_UPPER0
mdefine_line|#define BRIDGE_BUF_ADDR_UPPER0&t;0x000304
DECL|macro|BRIDGE_BUF_ADDR_UPPER_OFF
mdefine_line|#define BRIDGE_BUF_ADDR_UPPER_OFF 0x000010&t;/* PCI Buffer Upper Offset */
DECL|macro|BRIDGE_BUF_ADDR_UPPER
mdefine_line|#define BRIDGE_BUF_ADDR_UPPER(x) (BRIDGE_BUF_ADDR_UPPER0+(x)*BRIDGE_BUF_ADDR_UPPER_OFF)
DECL|macro|BRIDGE_BUF_ADDR_LOWER0
mdefine_line|#define BRIDGE_BUF_ADDR_LOWER0&t;0x00030c
DECL|macro|BRIDGE_BUF_ADDR_LOWER_OFF
mdefine_line|#define BRIDGE_BUF_ADDR_LOWER_OFF 0x000010&t;/* PCI Buffer Upper Offset */
DECL|macro|BRIDGE_BUF_ADDR_LOWER
mdefine_line|#define BRIDGE_BUF_ADDR_LOWER(x) (BRIDGE_BUF_ADDR_LOWER0+(x)*BRIDGE_BUF_ADDR_LOWER_OFF)
multiline_comment|/* &n; * Performance Monitor Registers.&n; *&n; * The Performance registers are those registers which are associated with&n; * monitoring the performance of PCI generated reads to the host environ&n; * ment. Because of the size of the register file only the even registers&n; * were instrumented.&n; */
DECL|macro|BRIDGE_BUF_OFF
mdefine_line|#define BRIDGE_BUF_OFF 0x40
DECL|macro|BRIDGE_BUF_NEXT
mdefine_line|#define BRIDGE_BUF_NEXT(base, off) (base+((off)*BRIDGE_BUF_OFF))
multiline_comment|/*&n; * Buffer (x) Flush Count with Data Touch Register.&n; *&n; * This counter is incremented each time the corresponding response buffer&n; * is flushed after at least a single data element in the buffer is used.&n; * A word write to this address clears the count.&n; */
DECL|macro|BRIDGE_BUF_0_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_0_FLUSH_TOUCH  0x000404
DECL|macro|BRIDGE_BUF_2_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_2_FLUSH_TOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_TOUCH, 1)
DECL|macro|BRIDGE_BUF_4_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_4_FLUSH_TOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_TOUCH, 2)
DECL|macro|BRIDGE_BUF_6_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_6_FLUSH_TOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_TOUCH, 3)
DECL|macro|BRIDGE_BUF_8_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_8_FLUSH_TOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_TOUCH, 4)
DECL|macro|BRIDGE_BUF_10_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_10_FLUSH_TOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_TOUCH, 5)
DECL|macro|BRIDGE_BUF_12_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_12_FLUSH_TOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_TOUCH, 6)
DECL|macro|BRIDGE_BUF_14_FLUSH_TOUCH
mdefine_line|#define BRIDGE_BUF_14_FLUSH_TOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_TOUCH, 7)
multiline_comment|/*&n; * Buffer (x) Flush Count w/o Data Touch Register&n; *&n; * This counter is incremented each time the corresponding response buffer&n; * is flushed without any data element in the buffer being used. A word&n; * write to this address clears the count.&n; */
DECL|macro|BRIDGE_BUF_0_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_0_FLUSH_NOTOUCH  0x00040c
DECL|macro|BRIDGE_BUF_2_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_2_FLUSH_NOTOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_NOTOUCH, 1)
DECL|macro|BRIDGE_BUF_4_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_4_FLUSH_NOTOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_NOTOUCH, 2)
DECL|macro|BRIDGE_BUF_6_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_6_FLUSH_NOTOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_NOTOUCH, 3)
DECL|macro|BRIDGE_BUF_8_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_8_FLUSH_NOTOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_NOTOUCH, 4)
DECL|macro|BRIDGE_BUF_10_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_10_FLUSH_NOTOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_NOTOUCH, 5)
DECL|macro|BRIDGE_BUF_12_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_12_FLUSH_NOTOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_NOTOUCH, 6)
DECL|macro|BRIDGE_BUF_14_FLUSH_NOTOUCH
mdefine_line|#define BRIDGE_BUF_14_FLUSH_NOTOUCH  BRIDGE_BUF_NEXT(BRIDGE_BUF_0_FLUSH_NOTOUCH, 7)
multiline_comment|/*&n; * Buffer (x) Request in Flight Count Register&n; *&n; * This counter is incremented on each bus clock while the request is in&n; * flight. A word write to this address clears the count.&n; */
DECL|macro|BRIDGE_BUF_0_INFLIGHT
mdefine_line|#define BRIDGE_BUF_0_INFLIGHT&t; 0x000414
DECL|macro|BRIDGE_BUF_2_INFLIGHT
mdefine_line|#define BRIDGE_BUF_2_INFLIGHT    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_INFLIGHT, 1)
DECL|macro|BRIDGE_BUF_4_INFLIGHT
mdefine_line|#define BRIDGE_BUF_4_INFLIGHT    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_INFLIGHT, 2)
DECL|macro|BRIDGE_BUF_6_INFLIGHT
mdefine_line|#define BRIDGE_BUF_6_INFLIGHT    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_INFLIGHT, 3)
DECL|macro|BRIDGE_BUF_8_INFLIGHT
mdefine_line|#define BRIDGE_BUF_8_INFLIGHT    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_INFLIGHT, 4)
DECL|macro|BRIDGE_BUF_10_INFLIGHT
mdefine_line|#define BRIDGE_BUF_10_INFLIGHT   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_INFLIGHT, 5)
DECL|macro|BRIDGE_BUF_12_INFLIGHT
mdefine_line|#define BRIDGE_BUF_12_INFLIGHT   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_INFLIGHT, 6)
DECL|macro|BRIDGE_BUF_14_INFLIGHT
mdefine_line|#define BRIDGE_BUF_14_INFLIGHT   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_INFLIGHT, 7)
multiline_comment|/*&n; * Buffer (x) Prefetch Request Count Register&n; *&n; * This counter is incremented each time the request using this buffer was&n; * generated from the prefetcher. A word write to this address clears the&n; * count.&n; */
DECL|macro|BRIDGE_BUF_0_PREFETCH
mdefine_line|#define BRIDGE_BUF_0_PREFETCH&t; 0x00041C
DECL|macro|BRIDGE_BUF_2_PREFETCH
mdefine_line|#define BRIDGE_BUF_2_PREFETCH    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PREFETCH, 1)
DECL|macro|BRIDGE_BUF_4_PREFETCH
mdefine_line|#define BRIDGE_BUF_4_PREFETCH    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PREFETCH, 2)
DECL|macro|BRIDGE_BUF_6_PREFETCH
mdefine_line|#define BRIDGE_BUF_6_PREFETCH    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PREFETCH, 3)
DECL|macro|BRIDGE_BUF_8_PREFETCH
mdefine_line|#define BRIDGE_BUF_8_PREFETCH    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PREFETCH, 4)
DECL|macro|BRIDGE_BUF_10_PREFETCH
mdefine_line|#define BRIDGE_BUF_10_PREFETCH   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PREFETCH, 5)
DECL|macro|BRIDGE_BUF_12_PREFETCH
mdefine_line|#define BRIDGE_BUF_12_PREFETCH   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PREFETCH, 6)
DECL|macro|BRIDGE_BUF_14_PREFETCH
mdefine_line|#define BRIDGE_BUF_14_PREFETCH   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PREFETCH, 7)
multiline_comment|/*&n; * Buffer (x) Total PCI Retry Count Register&n; *&n; * This counter is incremented each time a PCI bus retry occurs and the ad&n; * dress matches the tag for the selected buffer. The buffer must also has&n; * this request in-flight. A word write to this address clears the count.&n; */
DECL|macro|BRIDGE_BUF_0_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_0_PCI_RETRY&t; 0x000424
DECL|macro|BRIDGE_BUF_2_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_2_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PCI_RETRY, 1)
DECL|macro|BRIDGE_BUF_4_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_4_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PCI_RETRY, 2)
DECL|macro|BRIDGE_BUF_6_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_6_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PCI_RETRY, 3)
DECL|macro|BRIDGE_BUF_8_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_8_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PCI_RETRY, 4)
DECL|macro|BRIDGE_BUF_10_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_10_PCI_RETRY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PCI_RETRY, 5)
DECL|macro|BRIDGE_BUF_12_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_12_PCI_RETRY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PCI_RETRY, 6)
DECL|macro|BRIDGE_BUF_14_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_14_PCI_RETRY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_PCI_RETRY, 7)
multiline_comment|/*&n; * Buffer (x) Max PCI Retry Count Register&n; *&n; * This counter is contains the maximum retry count for a single request&n; * which was in-flight for this buffer. A word write to this address&n; * clears the count.&n; */
DECL|macro|BRIDGE_BUF_0_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_0_MAX_PCI_RETRY&t; 0x00042C
DECL|macro|BRIDGE_BUF_2_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_2_MAX_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_PCI_RETRY, 1)
DECL|macro|BRIDGE_BUF_4_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_4_MAX_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_PCI_RETRY, 2)
DECL|macro|BRIDGE_BUF_6_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_6_MAX_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_PCI_RETRY, 3)
DECL|macro|BRIDGE_BUF_8_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_8_MAX_PCI_RETRY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_PCI_RETRY, 4)
DECL|macro|BRIDGE_BUF_10_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_10_MAX_PCI_RETRY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_PCI_RETRY, 5)
DECL|macro|BRIDGE_BUF_12_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_12_MAX_PCI_RETRY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_PCI_RETRY, 6)
DECL|macro|BRIDGE_BUF_14_MAX_PCI_RETRY
mdefine_line|#define BRIDGE_BUF_14_MAX_PCI_RETRY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_PCI_RETRY, 7)
multiline_comment|/*&n; * Buffer (x) Max Latency Count Register&n; *&n; * This counter is contains the maximum count (in bus clocks) for a single&n; * request which was in-flight for this buffer. A word write to this&n; * address clears the count.&n; */
DECL|macro|BRIDGE_BUF_0_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_0_MAX_LATENCY&t; 0x000434
DECL|macro|BRIDGE_BUF_2_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_2_MAX_LATENCY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_LATENCY, 1)
DECL|macro|BRIDGE_BUF_4_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_4_MAX_LATENCY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_LATENCY, 2)
DECL|macro|BRIDGE_BUF_6_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_6_MAX_LATENCY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_LATENCY, 3)
DECL|macro|BRIDGE_BUF_8_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_8_MAX_LATENCY    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_LATENCY, 4)
DECL|macro|BRIDGE_BUF_10_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_10_MAX_LATENCY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_LATENCY, 5)
DECL|macro|BRIDGE_BUF_12_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_12_MAX_LATENCY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_LATENCY, 6)
DECL|macro|BRIDGE_BUF_14_MAX_LATENCY
mdefine_line|#define BRIDGE_BUF_14_MAX_LATENCY   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_MAX_LATENCY, 7)
multiline_comment|/*&n; * Buffer (x) Clear All Register&n; *&n; * Any access to this register clears all the count values for the (x)&n; * registers.&n; */
DECL|macro|BRIDGE_BUF_0_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_0_CLEAR_ALL&t; 0x00043C
DECL|macro|BRIDGE_BUF_2_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_2_CLEAR_ALL    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_CLEAR_ALL, 1)
DECL|macro|BRIDGE_BUF_4_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_4_CLEAR_ALL    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_CLEAR_ALL, 2)
DECL|macro|BRIDGE_BUF_6_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_6_CLEAR_ALL    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_CLEAR_ALL, 3)
DECL|macro|BRIDGE_BUF_8_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_8_CLEAR_ALL    BRIDGE_BUF_NEXT(BRIDGE_BUF_0_CLEAR_ALL, 4)
DECL|macro|BRIDGE_BUF_10_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_10_CLEAR_ALL   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_CLEAR_ALL, 5)
DECL|macro|BRIDGE_BUF_12_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_12_CLEAR_ALL   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_CLEAR_ALL, 6)
DECL|macro|BRIDGE_BUF_14_CLEAR_ALL
mdefine_line|#define BRIDGE_BUF_14_CLEAR_ALL   BRIDGE_BUF_NEXT(BRIDGE_BUF_0_CLEAR_ALL, 7)
multiline_comment|/* end of Performance Monitor Registers */
multiline_comment|/* Byte offset macros for Bridge I/O space.&n; *&n; * NOTE: Where applicable please use the PCIBR_xxx or PCIBRIDGE_xxx&n; * macros (below) as they will handle [X]Bridge and PIC. For example,&n; * PCIBRIDGE_TYPE0_CFG_DEV0() vs BRIDGE_TYPE0_CFG_DEV0&n; */
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
macro_line|#ifndef __ASSEMBLY__
DECL|macro|BRIDGE_DEVIO
mdefine_line|#define BRIDGE_DEVIO(x)&t;&t;((x)&lt;=1 ? BRIDGE_DEVIO0+(x)*BRIDGE_DEVIO_2MB : BRIDGE_DEVIO2+((x)-2)*BRIDGE_DEVIO_1MB)
multiline_comment|/*&n; * The device space macros for PIC are more complicated because the PIC has&n; * two PCI/X bridges under the same widget.  For PIC bus 0, the addresses are&n; * basically the same as for the [X]Bridge.  For PIC bus 1, the addresses are&n; * offset by 0x800000.   Here are two sets of macros.  They are &n; * &quot;PCIBRIDGE_xxx&quot; that return the address based on the supplied bus number&n; * and also equivalent &quot;PCIBR_xxx&quot; macros that may be used with a&n; * pcibr_soft_s structure.   Both should work with all bridges.&n; */
DECL|macro|PIC_BUS1_OFFSET
mdefine_line|#define PIC_BUS1_OFFSET 0x800000
DECL|macro|PCIBRIDGE_TYPE0_CFG_DEV0
mdefine_line|#define PCIBRIDGE_TYPE0_CFG_DEV0(busnum) &bslash;&n;    ((busnum) ? BRIDGE_TYPE0_CFG_DEV0 + PIC_BUS1_OFFSET : &bslash;&n;                    BRIDGE_TYPE0_CFG_DEV0)
DECL|macro|PCIBRIDGE_TYPE1_CFG
mdefine_line|#define PCIBRIDGE_TYPE1_CFG(busnum) &bslash;&n;    ((busnum) ? BRIDGE_TYPE1_CFG + PIC_BUS1_OFFSET : BRIDGE_TYPE1_CFG)
DECL|macro|PCIBRIDGE_TYPE0_CFG_DEV
mdefine_line|#define PCIBRIDGE_TYPE0_CFG_DEV(busnum, s) &bslash;&n;        (PCIBRIDGE_TYPE0_CFG_DEV0(busnum)+&bslash;&n;        (s)*BRIDGE_TYPE0_CFG_SLOT_OFF)
DECL|macro|PCIBRIDGE_TYPE0_CFG_DEVF
mdefine_line|#define PCIBRIDGE_TYPE0_CFG_DEVF(busnum, s, f) &bslash;&n;        (PCIBRIDGE_TYPE0_CFG_DEV0(busnum)+&bslash;&n;        (s)*BRIDGE_TYPE0_CFG_SLOT_OFF+&bslash;&n;        (f)*BRIDGE_TYPE0_CFG_FUNC_OFF)
DECL|macro|PCIBRIDGE_DEVIO0
mdefine_line|#define PCIBRIDGE_DEVIO0(busnum) ((busnum) ? &bslash;&n;        (BRIDGE_DEVIO0 + PIC_BUS1_OFFSET) : BRIDGE_DEVIO0)
DECL|macro|PCIBRIDGE_DEVIO1
mdefine_line|#define PCIBRIDGE_DEVIO1(busnum) ((busnum) ? &bslash;&n;        (BRIDGE_DEVIO1 + PIC_BUS1_OFFSET) : BRIDGE_DEVIO1)
DECL|macro|PCIBRIDGE_DEVIO2
mdefine_line|#define PCIBRIDGE_DEVIO2(busnum) ((busnum) ? &bslash;&n;        (BRIDGE_DEVIO2 + PIC_BUS1_OFFSET) : BRIDGE_DEVIO2)
DECL|macro|PCIBRIDGE_DEVIO
mdefine_line|#define PCIBRIDGE_DEVIO(busnum, x) &bslash;&n;    ((x)&lt;=1 ? PCIBRIDGE_DEVIO0(busnum)+(x)*BRIDGE_DEVIO_2MB : &bslash;&n;        PCIBRIDGE_DEVIO2(busnum)+((x)-2)*BRIDGE_DEVIO_1MB)
DECL|macro|PCIBR_BRIDGE_DEVIO0
mdefine_line|#define PCIBR_BRIDGE_DEVIO0(ps)     PCIBRIDGE_DEVIO0((ps)-&gt;bs_busnum)
DECL|macro|PCIBR_BRIDGE_DEVIO1
mdefine_line|#define PCIBR_BRIDGE_DEVIO1(ps)     PCIBRIDGE_DEVIO1((ps)-&gt;bs_busnum)
DECL|macro|PCIBR_BRIDGE_DEVIO2
mdefine_line|#define PCIBR_BRIDGE_DEVIO2(ps)     PCIBRIDGE_DEVIO2((ps)-&gt;bs_busnum)
DECL|macro|PCIBR_BRIDGE_DEVIO
mdefine_line|#define PCIBR_BRIDGE_DEVIO(ps, s)   PCIBRIDGE_DEVIO((ps)-&gt;bs_busnum, s)
DECL|macro|PCIBR_TYPE1_CFG
mdefine_line|#define PCIBR_TYPE1_CFG(ps)         PCIBRIDGE_TYPE1_CFG((ps)-&gt;bs_busnum)
DECL|macro|PCIBR_BUS_TYPE0_CFG_DEV0
mdefine_line|#define PCIBR_BUS_TYPE0_CFG_DEV0(ps) PCIBR_TYPE0_CFG_DEV(ps, 0)
DECL|macro|PCIBR_TYPE0_CFG_DEV
mdefine_line|#define PCIBR_TYPE0_CFG_DEV(ps, s) &bslash;&n;    ((IS_PIC_SOFT(ps)) ? PCIBRIDGE_TYPE0_CFG_DEV((ps)-&gt;bs_busnum, s+1) : &bslash;&n;&t;&t;  &t;     PCIBRIDGE_TYPE0_CFG_DEV((ps)-&gt;bs_busnum, s))
DECL|macro|PCIBR_BUS_TYPE0_CFG_DEVF
mdefine_line|#define PCIBR_BUS_TYPE0_CFG_DEVF(ps,s,f) &bslash;&n;    ((IS_PIC_SOFT(ps)) ? PCIBRIDGE_TYPE0_CFG_DEVF((ps)-&gt;bs_busnum,(s+1),f) : &bslash;&n;&t;&t;&t;     PCIBRIDGE_TYPE0_CFG_DEVF((ps)-&gt;bs_busnum,s,f))
macro_line|#endif&t;&t;&t;&t;/* LANGUAGE_C */
DECL|macro|BRIDGE_EXTERNAL_FLASH
mdefine_line|#define BRIDGE_EXTERNAL_FLASH&t;0x00C00000&t;/* External Flash PROMS */
multiline_comment|/* ========================================================================&n; *    Bridge register bit field definitions&n; */
multiline_comment|/* Widget part number of bridge */
DECL|macro|BRIDGE_WIDGET_PART_NUM
mdefine_line|#define BRIDGE_WIDGET_PART_NUM&t;&t;0xc002
DECL|macro|XBRIDGE_WIDGET_PART_NUM
mdefine_line|#define XBRIDGE_WIDGET_PART_NUM&t;&t;0xd002
multiline_comment|/* Manufacturer of bridge */
DECL|macro|BRIDGE_WIDGET_MFGR_NUM
mdefine_line|#define BRIDGE_WIDGET_MFGR_NUM&t;&t;0x036
DECL|macro|XBRIDGE_WIDGET_MFGR_NUM
mdefine_line|#define XBRIDGE_WIDGET_MFGR_NUM&t;&t;0x024
multiline_comment|/* Revision numbers for known [X]Bridge revisions */
DECL|macro|BRIDGE_REV_A
mdefine_line|#define BRIDGE_REV_A&t;&t;&t;0x1
DECL|macro|BRIDGE_REV_B
mdefine_line|#define BRIDGE_REV_B&t;&t;&t;0x2
DECL|macro|BRIDGE_REV_C
mdefine_line|#define BRIDGE_REV_C&t;&t;&t;0x3
DECL|macro|BRIDGE_REV_D
mdefine_line|#define&t;BRIDGE_REV_D&t;&t;&t;0x4
DECL|macro|XBRIDGE_REV_A
mdefine_line|#define XBRIDGE_REV_A&t;&t;&t;0x1
DECL|macro|XBRIDGE_REV_B
mdefine_line|#define XBRIDGE_REV_B&t;&t;&t;0x2
multiline_comment|/* macros to determine bridge type. &squot;wid&squot; == widget identification */
DECL|macro|IS_BRIDGE
mdefine_line|#define IS_BRIDGE(wid) (XWIDGET_PART_NUM(wid) == BRIDGE_WIDGET_PART_NUM &amp;&amp; &bslash;&n;&t;&t;&t;XWIDGET_MFG_NUM(wid) == BRIDGE_WIDGET_MFGR_NUM)
DECL|macro|IS_XBRIDGE
mdefine_line|#define IS_XBRIDGE(wid) (XWIDGET_PART_NUM(wid) == XBRIDGE_WIDGET_PART_NUM &amp;&amp; &bslash;&n;&t;&t;&t;XWIDGET_MFG_NUM(wid) == XBRIDGE_WIDGET_MFGR_NUM)
DECL|macro|IS_PIC_BUS0
mdefine_line|#define IS_PIC_BUS0(wid) (XWIDGET_PART_NUM(wid) == PIC_WIDGET_PART_NUM_BUS0 &amp;&amp; &bslash;&n;&t;&t;&t;XWIDGET_MFG_NUM(wid) == PIC_WIDGET_MFGR_NUM)
DECL|macro|IS_PIC_BUS1
mdefine_line|#define IS_PIC_BUS1(wid) (XWIDGET_PART_NUM(wid) == PIC_WIDGET_PART_NUM_BUS1 &amp;&amp; &bslash;&n;&t;&t;&t;XWIDGET_MFG_NUM(wid) == PIC_WIDGET_MFGR_NUM)
DECL|macro|IS_PIC_BRIDGE
mdefine_line|#define IS_PIC_BRIDGE(wid) (IS_PIC_BUS0(wid) || IS_PIC_BUS1(wid))
multiline_comment|/* Part + Rev numbers allows distinction and acscending sequence */
DECL|macro|BRIDGE_PART_REV_A
mdefine_line|#define BRIDGE_PART_REV_A&t;(BRIDGE_WIDGET_PART_NUM &lt;&lt; 4 | BRIDGE_REV_A)
DECL|macro|BRIDGE_PART_REV_B
mdefine_line|#define BRIDGE_PART_REV_B&t;(BRIDGE_WIDGET_PART_NUM &lt;&lt; 4 | BRIDGE_REV_B)
DECL|macro|BRIDGE_PART_REV_C
mdefine_line|#define BRIDGE_PART_REV_C&t;(BRIDGE_WIDGET_PART_NUM &lt;&lt; 4 | BRIDGE_REV_C)
DECL|macro|BRIDGE_PART_REV_D
mdefine_line|#define&t;BRIDGE_PART_REV_D&t;(BRIDGE_WIDGET_PART_NUM &lt;&lt; 4 | BRIDGE_REV_D)
DECL|macro|XBRIDGE_PART_REV_A
mdefine_line|#define XBRIDGE_PART_REV_A&t;(XBRIDGE_WIDGET_PART_NUM &lt;&lt; 4 | XBRIDGE_REV_A)
DECL|macro|XBRIDGE_PART_REV_B
mdefine_line|#define XBRIDGE_PART_REV_B&t;(XBRIDGE_WIDGET_PART_NUM &lt;&lt; 4 | XBRIDGE_REV_B)
multiline_comment|/* Bridge widget status register bits definition */
DECL|macro|PIC_STAT_PCIX_SPEED
mdefine_line|#define PIC_STAT_PCIX_SPEED             (0x3ull &lt;&lt; 34)
DECL|macro|PIC_STAT_PCIX_ACTIVE
mdefine_line|#define PIC_STAT_PCIX_ACTIVE            (0x1ull &lt;&lt; 33)
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
DECL|macro|PIC_CTRL_NO_SNOOP
mdefine_line|#define PIC_CTRL_NO_SNOOP&t;&t;(0x1ull &lt;&lt; 62)
DECL|macro|PIC_CTRL_RELAX_ORDER
mdefine_line|#define PIC_CTRL_RELAX_ORDER&t;&t;(0x1ull &lt;&lt; 61)
DECL|macro|PIC_CTRL_BUS_NUM
mdefine_line|#define PIC_CTRL_BUS_NUM(x)&t;&t;((unsigned long long)(x) &lt;&lt; 48)
DECL|macro|PIC_CTRL_BUS_NUM_MASK
mdefine_line|#define PIC_CTRL_BUS_NUM_MASK&t;&t;(PIC_CTRL_BUS_NUM(0xff))
DECL|macro|PIC_CTRL_DEV_NUM
mdefine_line|#define PIC_CTRL_DEV_NUM(x)&t;&t;((unsigned long long)(x) &lt;&lt; 43)
DECL|macro|PIC_CTRL_DEV_NUM_MASK
mdefine_line|#define PIC_CTRL_DEV_NUM_MASK&t;&t;(PIC_CTRL_DEV_NUM(0x1f))
DECL|macro|PIC_CTRL_FUN_NUM
mdefine_line|#define PIC_CTRL_FUN_NUM(x)&t;&t;((unsigned long long)(x) &lt;&lt; 40)
DECL|macro|PIC_CTRL_FUN_NUM_MASK
mdefine_line|#define PIC_CTRL_FUN_NUM_MASK&t;&t;(PIC_CTRL_FUN_NUM(0x7))
DECL|macro|PIC_CTRL_PAR_EN_REQ
mdefine_line|#define PIC_CTRL_PAR_EN_REQ&t;&t;(0x1ull &lt;&lt; 29)
DECL|macro|PIC_CTRL_PAR_EN_RESP
mdefine_line|#define PIC_CTRL_PAR_EN_RESP&t;&t;(0x1ull &lt;&lt; 30)
DECL|macro|PIC_CTRL_PAR_EN_ATE
mdefine_line|#define PIC_CTRL_PAR_EN_ATE&t;&t;(0x1ull &lt;&lt; 31)
DECL|macro|BRIDGE_CTRL_FLASH_WR_EN
mdefine_line|#define BRIDGE_CTRL_FLASH_WR_EN&t;&t;(0x1ul &lt;&lt; 31)   /* bridge only */
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
DECL|macro|BRIDGE_CTRL_PCI_SPEED
mdefine_line|#define BRIDGE_CTRL_PCI_SPEED&t;&t;(0x3 &lt;&lt; 4)
DECL|macro|BRIDGE_CTRL_BUS_SPEED
mdefine_line|#define BRIDGE_CTRL_BUS_SPEED(n)        ((n) &lt;&lt; 4)
DECL|macro|BRIDGE_CTRL_BUS_SPEED_MASK
mdefine_line|#define BRIDGE_CTRL_BUS_SPEED_MASK      (BRIDGE_CTRL_BUS_SPEED(0x3))
DECL|macro|BRIDGE_CTRL_BUS_SPEED_33
mdefine_line|#define BRIDGE_CTRL_BUS_SPEED_33        0x00
DECL|macro|BRIDGE_CTRL_BUS_SPEED_66
mdefine_line|#define BRIDGE_CTRL_BUS_SPEED_66        0x10
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
DECL|macro|PIC_ISR_PCIX_SPLIT_MSG_PE
mdefine_line|#define PIC_ISR_PCIX_SPLIT_MSG_PE&t;(0x1ull &lt;&lt; 45)
DECL|macro|PIC_ISR_PCIX_SPLIT_EMSG
mdefine_line|#define PIC_ISR_PCIX_SPLIT_EMSG&t;&t;(0x1ull &lt;&lt; 44)
DECL|macro|PIC_ISR_PCIX_SPLIT_TO
mdefine_line|#define PIC_ISR_PCIX_SPLIT_TO&t;&t;(0x1ull &lt;&lt; 43)
DECL|macro|PIC_ISR_PCIX_UNEX_COMP
mdefine_line|#define PIC_ISR_PCIX_UNEX_COMP&t;&t;(0x1ull &lt;&lt; 42)
DECL|macro|PIC_ISR_INT_RAM_PERR
mdefine_line|#define PIC_ISR_INT_RAM_PERR&t;&t;(0x1ull &lt;&lt; 41)
DECL|macro|PIC_ISR_PCIX_ARB_ERR
mdefine_line|#define PIC_ISR_PCIX_ARB_ERR&t;&t;(0x1ull &lt;&lt; 40)
DECL|macro|PIC_ISR_PCIX_REQ_TOUT
mdefine_line|#define PIC_ISR_PCIX_REQ_TOUT&t;&t;(0x1ull &lt;&lt; 39)
DECL|macro|PIC_ISR_PCIX_TABORT
mdefine_line|#define PIC_ISR_PCIX_TABORT&t;&t;(0x1ull &lt;&lt; 38)
DECL|macro|PIC_ISR_PCIX_PERR
mdefine_line|#define PIC_ISR_PCIX_PERR&t;&t;(0x1ull &lt;&lt; 37)
DECL|macro|PIC_ISR_PCIX_SERR
mdefine_line|#define PIC_ISR_PCIX_SERR&t;&t;(0x1ull &lt;&lt; 36)
DECL|macro|PIC_ISR_PCIX_MRETRY
mdefine_line|#define PIC_ISR_PCIX_MRETRY&t;&t;(0x1ull &lt;&lt; 35)
DECL|macro|PIC_ISR_PCIX_MTOUT
mdefine_line|#define PIC_ISR_PCIX_MTOUT&t;&t;(0x1ull &lt;&lt; 34)
DECL|macro|PIC_ISR_PCIX_DA_PARITY
mdefine_line|#define PIC_ISR_PCIX_DA_PARITY&t;&t;(0x1ull &lt;&lt; 33)
DECL|macro|PIC_ISR_PCIX_AD_PARITY
mdefine_line|#define PIC_ISR_PCIX_AD_PARITY&t;&t;(0x1ull &lt;&lt; 32)
DECL|macro|BRIDGE_ISR_MULTI_ERR
mdefine_line|#define BRIDGE_ISR_MULTI_ERR&t;&t;(0x1u &lt;&lt; 31)&t;/* bridge only */
DECL|macro|BRIDGE_ISR_PMU_ESIZE_FAULT
mdefine_line|#define BRIDGE_ISR_PMU_ESIZE_FAULT&t;(0x1 &lt;&lt; 30)&t;/* bridge only */
DECL|macro|BRIDGE_ISR_PAGE_FAULT
mdefine_line|#define BRIDGE_ISR_PAGE_FAULT&t;&t;(0x1 &lt;&lt; 30)&t;/* xbridge only */
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
mdefine_line|#define BRIDGE_ISR_PCIBUS_PIOERR&t;&bslash;&n;&t;&t;(BRIDGE_ISR_PCI_MST_TIMEOUT|BRIDGE_ISR_PCI_ABORT|&t;&bslash;&n;&t;&t; PIC_ISR_PCIX_MTOUT|PIC_ISR_PCIX_TABORT)
DECL|macro|BRIDGE_ISR_PCIBUS_ERROR
mdefine_line|#define BRIDGE_ISR_PCIBUS_ERROR&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_PCIBUS_PIOERR|BRIDGE_ISR_PCI_PERR|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_PCI_SERR|BRIDGE_ISR_PCI_RETRY_CNT|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_PCI_PARITY|PIC_ISR_PCIX_PERR|&t;&t;&bslash;&n;&t;&t; PIC_ISR_PCIX_SERR|PIC_ISR_PCIX_MRETRY|&t;&t;&t;&bslash;&n;&t;&t; PIC_ISR_PCIX_AD_PARITY|PIC_ISR_PCIX_DA_PARITY|&t;&t;&bslash;&n;&t;&t; PIC_ISR_PCIX_REQ_TOUT|PIC_ISR_PCIX_UNEX_COMP|&t;&t;&bslash;&n;&t;&t; PIC_ISR_PCIX_SPLIT_TO|PIC_ISR_PCIX_SPLIT_EMSG|&t;&t;&bslash;&n;&t;&t; PIC_ISR_PCIX_SPLIT_MSG_PE)
DECL|macro|BRIDGE_ISR_XTALK_ERROR
mdefine_line|#define BRIDGE_ISR_XTALK_ERROR&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_XREAD_REQ_TIMEOUT|BRIDGE_ISR_XREQ_FIFO_OFLOW|&bslash;&n;&t;&t; BRIDGE_ISR_UNSUPPORTED_XOP|BRIDGE_ISR_INVLD_ADDR|&t;&bslash;&n;&t;&t; BRIDGE_ISR_REQ_XTLK_ERR|BRIDGE_ISR_RESP_XTLK_ERR|&t;&bslash;&n;&t;&t; BRIDGE_ISR_BAD_XREQ_PKT|BRIDGE_ISR_BAD_XRESP_PKT|&t;&bslash;&n;&t;&t; BRIDGE_ISR_UNEXP_RESP)
DECL|macro|BRIDGE_ISR_ERRORS
mdefine_line|#define BRIDGE_ISR_ERRORS&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_LINK_ERROR|BRIDGE_ISR_PCIBUS_ERROR|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_XTALK_ERROR|BRIDGE_ISR_SSRAM_PERR|&t;&t;&bslash;&n;&t;&t; BRIDGE_ISR_PMU_ESIZE_FAULT|PIC_ISR_INT_RAM_PERR)
multiline_comment|/*&n; * List of Errors which are fatal and kill the sytem&n; */
DECL|macro|BRIDGE_ISR_ERROR_FATAL
mdefine_line|#define BRIDGE_ISR_ERROR_FATAL&t;&t;&bslash;&n;&t;&t;((BRIDGE_ISR_XTALK_ERROR &amp; ~BRIDGE_ISR_XREAD_REQ_TIMEOUT)|&bslash;&n;&t;&t; BRIDGE_ISR_PCI_SERR|BRIDGE_ISR_PCI_PARITY|&t;&t;  &bslash;&n;&t;&t; PIC_ISR_PCIX_SERR|PIC_ISR_PCIX_AD_PARITY|&t;&t;  &bslash;&n;&t;&t; PIC_ISR_PCIX_DA_PARITY|&t;&t;&t;&t;  &bslash;&n;&t;&t; PIC_ISR_INT_RAM_PERR|PIC_ISR_PCIX_SPLIT_MSG_PE )
DECL|macro|BRIDGE_ISR_ERROR_DUMP
mdefine_line|#define BRIDGE_ISR_ERROR_DUMP&t;&t;&bslash;&n;&t;&t;(BRIDGE_ISR_PCIBUS_ERROR|BRIDGE_ISR_PMU_ESIZE_FAULT|&t;&bslash;&n;&t;&t; BRIDGE_ISR_XTALK_ERROR|BRIDGE_ISR_SSRAM_PERR|&t;&t;&bslash;&n;&t;&t; PIC_ISR_PCIX_ARB_ERR|PIC_ISR_INT_RAM_PERR)
multiline_comment|/* Bridge interrupt enable register bits definition */
DECL|macro|PIC_IMR_PCIX_SPLIT_MSG_PE
mdefine_line|#define PIC_IMR_PCIX_SPLIT_MSG_PE&t;PIC_ISR_PCIX_SPLIT_MSG_PE
DECL|macro|PIC_IMR_PCIX_SPLIT_EMSG
mdefine_line|#define PIC_IMR_PCIX_SPLIT_EMSG&t;&t;PIC_ISR_PCIX_SPLIT_EMSG
DECL|macro|PIC_IMR_PCIX_SPLIT_TO
mdefine_line|#define PIC_IMR_PCIX_SPLIT_TO&t;&t;PIC_ISR_PCIX_SPLIT_TO
DECL|macro|PIC_IMR_PCIX_UNEX_COMP
mdefine_line|#define PIC_IMR_PCIX_UNEX_COMP&t;&t;PIC_ISR_PCIX_UNEX_COMP
DECL|macro|PIC_IMR_INT_RAM_PERR
mdefine_line|#define PIC_IMR_INT_RAM_PERR&t;&t;PIC_ISR_INT_RAM_PERR
DECL|macro|PIC_IMR_PCIX_ARB_ERR
mdefine_line|#define PIC_IMR_PCIX_ARB_ERR&t;&t;PIC_ISR_PCIX_ARB_ERR
DECL|macro|PIC_IMR_PCIX_REQ_TOUR
mdefine_line|#define PIC_IMR_PCIX_REQ_TOUR&t;&t;PIC_ISR_PCIX_REQ_TOUT
DECL|macro|PIC_IMR_PCIX_TABORT
mdefine_line|#define PIC_IMR_PCIX_TABORT&t;&t;PIC_ISR_PCIX_TABORT
DECL|macro|PIC_IMR_PCIX_PERR
mdefine_line|#define PIC_IMR_PCIX_PERR&t;&t;PIC_ISR_PCIX_PERR
DECL|macro|PIC_IMR_PCIX_SERR
mdefine_line|#define PIC_IMR_PCIX_SERR&t;&t;PIC_ISR_PCIX_SERR
DECL|macro|PIC_IMR_PCIX_MRETRY
mdefine_line|#define PIC_IMR_PCIX_MRETRY&t;&t;PIC_ISR_PCIX_MRETRY
DECL|macro|PIC_IMR_PCIX_MTOUT
mdefine_line|#define PIC_IMR_PCIX_MTOUT&t;&t;PIC_ISR_PCIX_MTOUT
DECL|macro|PIC_IMR_PCIX_DA_PARITY
mdefine_line|#define PIC_IMR_PCIX_DA_PARITY&t;&t;PIC_ISR_PCIX_DA_PARITY
DECL|macro|PIC_IMR_PCIX_AD_PARITY
mdefine_line|#define PIC_IMR_PCIX_AD_PARITY&t;&t;PIC_ISR_PCIX_AD_PARITY
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
multiline_comment|/* &n; * Bridge interrupt reset register bits definition.  Note, PIC can&n; * reset indiviual error interrupts, BRIDGE &amp; XBRIDGE can only do &n; * groups of them.&n; */
DECL|macro|PIC_IRR_PCIX_SPLIT_MSG_PE
mdefine_line|#define PIC_IRR_PCIX_SPLIT_MSG_PE&t;PIC_ISR_PCIX_SPLIT_MSG_PE
DECL|macro|PIC_IRR_PCIX_SPLIT_EMSG
mdefine_line|#define PIC_IRR_PCIX_SPLIT_EMSG&t;&t;PIC_ISR_PCIX_SPLIT_EMSG
DECL|macro|PIC_IRR_PCIX_SPLIT_TO
mdefine_line|#define PIC_IRR_PCIX_SPLIT_TO&t;&t;PIC_ISR_PCIX_SPLIT_TO
DECL|macro|PIC_IRR_PCIX_UNEX_COMP
mdefine_line|#define PIC_IRR_PCIX_UNEX_COMP&t;&t;PIC_ISR_PCIX_UNEX_COMP
DECL|macro|PIC_IRR_INT_RAM_PERR
mdefine_line|#define PIC_IRR_INT_RAM_PERR&t;&t;PIC_ISR_INT_RAM_PERR
DECL|macro|PIC_IRR_PCIX_ARB_ERR
mdefine_line|#define PIC_IRR_PCIX_ARB_ERR&t;&t;PIC_ISR_PCIX_ARB_ERR
DECL|macro|PIC_IRR_PCIX_REQ_TOUT
mdefine_line|#define PIC_IRR_PCIX_REQ_TOUT&t;&t;PIC_ISR_PCIX_REQ_TOUT
DECL|macro|PIC_IRR_PCIX_TABORT
mdefine_line|#define PIC_IRR_PCIX_TABORT&t;&t;PIC_ISR_PCIX_TABORT
DECL|macro|PIC_IRR_PCIX_PERR
mdefine_line|#define PIC_IRR_PCIX_PERR&t;&t;PIC_ISR_PCIX_PERR
DECL|macro|PIC_IRR_PCIX_SERR
mdefine_line|#define PIC_IRR_PCIX_SERR&t;&t;PIC_ISR_PCIX_SERR
DECL|macro|PIC_IRR_PCIX_MRETRY
mdefine_line|#define PIC_IRR_PCIX_MRETRY&t;&t;PIC_ISR_PCIX_MRETRY
DECL|macro|PIC_IRR_PCIX_MTOUT
mdefine_line|#define PIC_IRR_PCIX_MTOUT&t;&t;PIC_ISR_PCIX_MTOUT
DECL|macro|PIC_IRR_PCIX_DA_PARITY
mdefine_line|#define PIC_IRR_PCIX_DA_PARITY&t;&t;PIC_ISR_PCIX_DA_PARITY
DECL|macro|PIC_IRR_PCIX_AD_PARITY
mdefine_line|#define PIC_IRR_PCIX_AD_PARITY&t;&t;PIC_ISR_PCIX_AD_PARITY
DECL|macro|PIC_IRR_PAGE_FAULT
mdefine_line|#define PIC_IRR_PAGE_FAULT&t;&t;BRIDGE_ISR_PAGE_FAULT
DECL|macro|PIC_IRR_UNEXP_RESP
mdefine_line|#define PIC_IRR_UNEXP_RESP&t;&t;BRIDGE_ISR_UNEXP_RESP
DECL|macro|PIC_IRR_BAD_XRESP_PKT
mdefine_line|#define PIC_IRR_BAD_XRESP_PKT&t;&t;BRIDGE_ISR_BAD_XRESP_PKT
DECL|macro|PIC_IRR_BAD_XREQ_PKT
mdefine_line|#define PIC_IRR_BAD_XREQ_PKT&t;&t;BRIDGE_ISR_BAD_XREQ_PKT
DECL|macro|PIC_IRR_RESP_XTLK_ERR
mdefine_line|#define PIC_IRR_RESP_XTLK_ERR&t;&t;BRIDGE_ISR_RESP_XTLK_ERR
DECL|macro|PIC_IRR_REQ_XTLK_ERR
mdefine_line|#define PIC_IRR_REQ_XTLK_ERR&t;&t;BRIDGE_ISR_REQ_XTLK_ERR
DECL|macro|PIC_IRR_INVLD_ADDR
mdefine_line|#define PIC_IRR_INVLD_ADDR&t;&t;BRIDGE_ISR_INVLD_ADDR
DECL|macro|PIC_IRR_UNSUPPORTED_XOP
mdefine_line|#define PIC_IRR_UNSUPPORTED_XOP&t;&t;BRIDGE_ISR_UNSUPPORTED_XOP
DECL|macro|PIC_IRR_XREQ_FIFO_OFLOW
mdefine_line|#define PIC_IRR_XREQ_FIFO_OFLOW&t;&t;BRIDGE_ISR_XREQ_FIFO_OFLOW
DECL|macro|PIC_IRR_LLP_REC_SNERR
mdefine_line|#define PIC_IRR_LLP_REC_SNERR&t;&t;BRIDGE_ISR_LLP_REC_SNERR
DECL|macro|PIC_IRR_LLP_REC_CBERR
mdefine_line|#define PIC_IRR_LLP_REC_CBERR&t;&t;BRIDGE_ISR_LLP_REC_CBERR
DECL|macro|PIC_IRR_LLP_RCTY
mdefine_line|#define PIC_IRR_LLP_RCTY&t;&t;BRIDGE_ISR_LLP_RCTY
DECL|macro|PIC_IRR_LLP_TX_RETRY
mdefine_line|#define PIC_IRR_LLP_TX_RETRY&t;&t;BRIDGE_ISR_LLP_TX_RETRY
DECL|macro|PIC_IRR_LLP_TCTY
mdefine_line|#define PIC_IRR_LLP_TCTY&t;&t;BRIDGE_ISR_LLP_TCTY
DECL|macro|PIC_IRR_PCI_ABORT
mdefine_line|#define PIC_IRR_PCI_ABORT&t;&t;BRIDGE_ISR_PCI_ABORT
DECL|macro|PIC_IRR_PCI_PARITY
mdefine_line|#define PIC_IRR_PCI_PARITY&t;&t;BRIDGE_ISR_PCI_PARITY
DECL|macro|PIC_IRR_PCI_SERR
mdefine_line|#define PIC_IRR_PCI_SERR&t;&t;BRIDGE_ISR_PCI_SERR
DECL|macro|PIC_IRR_PCI_PERR
mdefine_line|#define PIC_IRR_PCI_PERR&t;&t;BRIDGE_ISR_PCI_PERR
DECL|macro|PIC_IRR_PCI_MST_TIMEOUT
mdefine_line|#define PIC_IRR_PCI_MST_TIMEOUT&t;&t;BRIDGE_ISR_PCI_MST_TIMEOUT
DECL|macro|PIC_IRR_PCI_RETRY_CNT
mdefine_line|#define PIC_IRR_PCI_RETRY_CNT&t;&t;BRIDGE_ISR_PCI_RETRY_CNT
DECL|macro|PIC_IRR_XREAD_REQ_TIMEOUT
mdefine_line|#define PIC_IRR_XREAD_REQ_TIMEOUT&t;BRIDGE_ISR_XREAD_REQ_TIMEOUT
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
DECL|macro|PIC_IRR_RAM_GRP
mdefine_line|#define PIC_IRR_RAM_GRP&t;&t;&t;PIC_ISR_INT_RAM_PERR
DECL|macro|PIC_PCIX_GRP_CLR
mdefine_line|#define PIC_PCIX_GRP_CLR&t;&t;(PIC_IRR_PCIX_AD_PARITY | &bslash;&n;&t;&t;&t;&t;&t; PIC_IRR_PCIX_DA_PARITY | &bslash;&n;&t;&t;&t;&t;&t; PIC_IRR_PCIX_MTOUT | &bslash;&n;&t;&t;&t;&t;&t; PIC_IRR_PCIX_MRETRY | &bslash;&n;&t;&t;&t;&t;&t; PIC_IRR_PCIX_SERR | &bslash;&n;&t;&t;&t;&t;&t; PIC_IRR_PCIX_PERR | &bslash;&n;&t;&t;&t;&t;&t; PIC_IRR_PCIX_TABORT | &bslash;&n;&t;&t;&t;&t;&t; PIC_ISR_PCIX_REQ_TOUT | &bslash;&n;&t;&t;&t;&t;&t; PIC_ISR_PCIX_UNEX_COMP | &bslash;&n;&t;&t;&t;&t;&t; PIC_ISR_PCIX_SPLIT_TO | &bslash;&n;&t;&t;&t;&t;&t; PIC_ISR_PCIX_SPLIT_EMSG | &bslash;&n;&t;&t;&t;&t;&t; PIC_ISR_PCIX_SPLIT_MSG_PE)
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
multiline_comment|/* PIC interrupt(x) register bits definition */
DECL|macro|PIC_INT_ADDR_FLD
mdefine_line|#define PIC_INT_ADDR_FLD                0x00FF000000000000
DECL|macro|PIC_INT_ADDR_HOST
mdefine_line|#define PIC_INT_ADDR_HOST               0x0000FFFFFFFFFFFF
DECL|macro|BRIDGE_TMO_PCI_RETRY_HLD_MASK
mdefine_line|#define BRIDGE_TMO_PCI_RETRY_HLD_MASK&t;0x1f0000
DECL|macro|BRIDGE_TMO_GIO_TIMEOUT_MASK
mdefine_line|#define BRIDGE_TMO_GIO_TIMEOUT_MASK&t;0x001000
DECL|macro|BRIDGE_TMO_PCI_RETRY_CNT_MASK
mdefine_line|#define BRIDGE_TMO_PCI_RETRY_CNT_MASK&t;0x0003ff
DECL|macro|BRIDGE_TMO_PCI_RETRY_CNT_MAX
mdefine_line|#define BRIDGE_TMO_PCI_RETRY_CNT_MAX&t;0x3ff
multiline_comment|/* Bridge device(x) register bits definition */
DECL|macro|BRIDGE_DEV_ERR_LOCK_EN
mdefine_line|#define BRIDGE_DEV_ERR_LOCK_EN&t;&t;(1ull &lt;&lt; 28)
DECL|macro|BRIDGE_DEV_PAGE_CHK_DIS
mdefine_line|#define BRIDGE_DEV_PAGE_CHK_DIS&t;&t;(1ull &lt;&lt; 27)
DECL|macro|BRIDGE_DEV_FORCE_PCI_PAR
mdefine_line|#define BRIDGE_DEV_FORCE_PCI_PAR&t;(1ull &lt;&lt; 26)
DECL|macro|BRIDGE_DEV_VIRTUAL_EN
mdefine_line|#define BRIDGE_DEV_VIRTUAL_EN&t;&t;(1ull &lt;&lt; 25)
DECL|macro|BRIDGE_DEV_PMU_WRGA_EN
mdefine_line|#define BRIDGE_DEV_PMU_WRGA_EN&t;&t;(1ull &lt;&lt; 24)
DECL|macro|BRIDGE_DEV_DIR_WRGA_EN
mdefine_line|#define BRIDGE_DEV_DIR_WRGA_EN&t;&t;(1ull &lt;&lt; 23)
DECL|macro|BRIDGE_DEV_DEV_SIZE
mdefine_line|#define BRIDGE_DEV_DEV_SIZE&t;&t;(1ull &lt;&lt; 22)
DECL|macro|BRIDGE_DEV_RT
mdefine_line|#define BRIDGE_DEV_RT&t;&t;&t;(1ull &lt;&lt; 21)
DECL|macro|BRIDGE_DEV_SWAP_PMU
mdefine_line|#define BRIDGE_DEV_SWAP_PMU&t;&t;(1ull &lt;&lt; 20)
DECL|macro|BRIDGE_DEV_SWAP_DIR
mdefine_line|#define BRIDGE_DEV_SWAP_DIR&t;&t;(1ull &lt;&lt; 19)
DECL|macro|BRIDGE_DEV_PREF
mdefine_line|#define BRIDGE_DEV_PREF&t;&t;&t;(1ull &lt;&lt; 18)
DECL|macro|BRIDGE_DEV_PRECISE
mdefine_line|#define BRIDGE_DEV_PRECISE&t;&t;(1ull &lt;&lt; 17)
DECL|macro|BRIDGE_DEV_COH
mdefine_line|#define BRIDGE_DEV_COH&t;&t;&t;(1ull &lt;&lt; 16)
DECL|macro|BRIDGE_DEV_BARRIER
mdefine_line|#define BRIDGE_DEV_BARRIER&t;&t;(1ull &lt;&lt; 15)
DECL|macro|BRIDGE_DEV_GBR
mdefine_line|#define BRIDGE_DEV_GBR&t;&t;&t;(1ull &lt;&lt; 14)
DECL|macro|BRIDGE_DEV_DEV_SWAP
mdefine_line|#define BRIDGE_DEV_DEV_SWAP&t;&t;(1ull &lt;&lt; 13)
DECL|macro|BRIDGE_DEV_DEV_IO_MEM
mdefine_line|#define BRIDGE_DEV_DEV_IO_MEM&t;&t;(1ull &lt;&lt; 12)
DECL|macro|BRIDGE_DEV_OFF_MASK
mdefine_line|#define BRIDGE_DEV_OFF_MASK&t;&t;0x00000fff
DECL|macro|BRIDGE_DEV_OFF_ADDR_SHFT
mdefine_line|#define BRIDGE_DEV_OFF_ADDR_SHFT&t;20
DECL|macro|XBRIDGE_DEV_PMU_BITS
mdefine_line|#define XBRIDGE_DEV_PMU_BITS&t;&t;BRIDGE_DEV_PMU_WRGA_EN
DECL|macro|BRIDGE_DEV_PMU_BITS
mdefine_line|#define BRIDGE_DEV_PMU_BITS&t;&t;(BRIDGE_DEV_PMU_WRGA_EN&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_SWAP_PMU)
DECL|macro|BRIDGE_DEV_D32_BITS
mdefine_line|#define BRIDGE_DEV_D32_BITS&t;&t;(BRIDGE_DEV_DIR_WRGA_EN&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_SWAP_DIR&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_PREF&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_PRECISE&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_COH&t;&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_BARRIER)
DECL|macro|XBRIDGE_DEV_D64_BITS
mdefine_line|#define XBRIDGE_DEV_D64_BITS&t;&t;(BRIDGE_DEV_DIR_WRGA_EN&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_COH&t;&t;&t;| &bslash;&n;&t;&t;&t;&t;&t; BRIDGE_DEV_BARRIER)
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
mdefine_line|#define&t;BRIDGE_RRB_VDEV&t;0x4&t;/* after shifting down, 2 virtual channels */
DECL|macro|BRIDGE_RRB_PDEV
mdefine_line|#define&t;BRIDGE_RRB_PDEV&t;0x3&t;/* after shifting down, 8 devices */
DECL|macro|PIC_RRB_EN
mdefine_line|#define&t;PIC_RRB_EN&t;0x8&t;/* after shifting down */
DECL|macro|PIC_RRB_DEV
mdefine_line|#define&t;PIC_RRB_DEV&t;0x7&t;/* after shifting down */
DECL|macro|PIC_RRB_VDEV
mdefine_line|#define&t;PIC_RRB_VDEV&t;0x6&t;/* after shifting down, 4 virtual channels */
DECL|macro|PIC_RRB_PDEV
mdefine_line|#define&t;PIC_RRB_PDEV&t;0x1&t;/* after shifting down, 4 devices */
multiline_comment|/* RRB status register */
DECL|macro|BRIDGE_RRB_VALID
mdefine_line|#define&t;BRIDGE_RRB_VALID(r)&t;(0x00010000&lt;&lt;(r))
DECL|macro|BRIDGE_RRB_INUSE
mdefine_line|#define&t;BRIDGE_RRB_INUSE(r)&t;(0x00000001&lt;&lt;(r))
multiline_comment|/* RRB clear register */
DECL|macro|BRIDGE_RRB_CLEAR
mdefine_line|#define&t;BRIDGE_RRB_CLEAR(r)&t;(0x00000001&lt;&lt;(r))
multiline_comment|/* Defines for the virtual channels so we don&squot;t hardcode 0-3 within code */
DECL|macro|VCHAN0
mdefine_line|#define VCHAN0&t;0&t;/* virtual channel 0 (ie. the &quot;normal&quot; channel) */
DECL|macro|VCHAN1
mdefine_line|#define VCHAN1&t;1&t;/* virtual channel 1 */
DECL|macro|VCHAN2
mdefine_line|#define VCHAN2&t;2&t;/* virtual channel 2 - PIC only */
DECL|macro|VCHAN3
mdefine_line|#define VCHAN3&t;3&t;/* virtual channel 3 - PIC only */
multiline_comment|/* PIC: PCI-X Read Buffer Attribute Register (RBAR) */
DECL|macro|NUM_RBAR
mdefine_line|#define NUM_RBAR 16&t;/* number of RBAR registers */
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
multiline_comment|/*&n; * Macros for Xtalk to Bridge bus (PCI) PIO&n; * refer to section 5.2.1 Figure 4 of the &quot;PCI Interface Chip (PIC) Volume II&n; * Programmer&squot;s Reference&quot; (Revision 0.8 as of this writing).&n; *&n; * These are PIC bridge specific.  A separate set of macros was defined&n; * because PIC deviates from Bridge/Xbridge by not supporting a big-window&n; * alias for PCI I/O space, and also redefines XTALK addresses&n; * 0x0000C0000000L and 0x000100000000L to be PCI MEM aliases for the second&n; * bus.&n; */
multiline_comment|/* XTALK addresses that map into PIC Bridge Bus addr space */
DECL|macro|PICBRIDGE0_PIO32_XTALK_ALIAS_BASE
mdefine_line|#define PICBRIDGE0_PIO32_XTALK_ALIAS_BASE&t;0x000040000000L
DECL|macro|PICBRIDGE0_PIO32_XTALK_ALIAS_LIMIT
mdefine_line|#define PICBRIDGE0_PIO32_XTALK_ALIAS_LIMIT&t;0x00007FFFFFFFL
DECL|macro|PICBRIDGE0_PIO64_XTALK_ALIAS_BASE
mdefine_line|#define PICBRIDGE0_PIO64_XTALK_ALIAS_BASE&t;0x000080000000L
DECL|macro|PICBRIDGE0_PIO64_XTALK_ALIAS_LIMIT
mdefine_line|#define PICBRIDGE0_PIO64_XTALK_ALIAS_LIMIT&t;0x0000BFFFFFFFL
DECL|macro|PICBRIDGE1_PIO32_XTALK_ALIAS_BASE
mdefine_line|#define PICBRIDGE1_PIO32_XTALK_ALIAS_BASE&t;0x0000C0000000L
DECL|macro|PICBRIDGE1_PIO32_XTALK_ALIAS_LIMIT
mdefine_line|#define PICBRIDGE1_PIO32_XTALK_ALIAS_LIMIT&t;0x0000FFFFFFFFL
DECL|macro|PICBRIDGE1_PIO64_XTALK_ALIAS_BASE
mdefine_line|#define PICBRIDGE1_PIO64_XTALK_ALIAS_BASE&t;0x000100000000L
DECL|macro|PICBRIDGE1_PIO64_XTALK_ALIAS_LIMIT
mdefine_line|#define PICBRIDGE1_PIO64_XTALK_ALIAS_LIMIT&t;0x00013FFFFFFFL
multiline_comment|/* XTALK addresses that map into PCI addresses */
DECL|macro|PICBRIDGE0_PCI_MEM32_BASE
mdefine_line|#define PICBRIDGE0_PCI_MEM32_BASE&t;PICBRIDGE0_PIO32_XTALK_ALIAS_BASE
DECL|macro|PICBRIDGE0_PCI_MEM32_LIMIT
mdefine_line|#define PICBRIDGE0_PCI_MEM32_LIMIT&t;PICBRIDGE0_PIO32_XTALK_ALIAS_LIMIT
DECL|macro|PICBRIDGE0_PCI_MEM64_BASE
mdefine_line|#define PICBRIDGE0_PCI_MEM64_BASE&t;PICBRIDGE0_PIO64_XTALK_ALIAS_BASE
DECL|macro|PICBRIDGE0_PCI_MEM64_LIMIT
mdefine_line|#define PICBRIDGE0_PCI_MEM64_LIMIT&t;PICBRIDGE0_PIO64_XTALK_ALIAS_LIMIT
DECL|macro|PICBRIDGE1_PCI_MEM32_BASE
mdefine_line|#define PICBRIDGE1_PCI_MEM32_BASE&t;PICBRIDGE1_PIO32_XTALK_ALIAS_BASE
DECL|macro|PICBRIDGE1_PCI_MEM32_LIMIT
mdefine_line|#define PICBRIDGE1_PCI_MEM32_LIMIT&t;PICBRIDGE1_PIO32_XTALK_ALIAS_LIMIT
DECL|macro|PICBRIDGE1_PCI_MEM64_BASE
mdefine_line|#define PICBRIDGE1_PCI_MEM64_BASE&t;PICBRIDGE1_PIO64_XTALK_ALIAS_BASE
DECL|macro|PICBRIDGE1_PCI_MEM64_LIMIT
mdefine_line|#define PICBRIDGE1_PCI_MEM64_LIMIT&t;PICBRIDGE1_PIO64_XTALK_ALIAS_LIMIT
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
macro_line|#ifndef __ASSEMBLY__
DECL|macro|IS_PCI32_LOCAL
mdefine_line|#define IS_PCI32_LOCAL(x)&t;((uint64_t)(x) &lt; PCI32_MAPPED_BASE)
DECL|macro|IS_PCI32_MAPPED
mdefine_line|#define IS_PCI32_MAPPED(x)&t;((uint64_t)(x) &lt; PCI32_DIRECT_BASE &amp;&amp; &bslash;&n;&t;&t;&t;&t;&t;(uint64_t)(x) &gt;= PCI32_MAPPED_BASE)
DECL|macro|IS_PCI32_DIRECT
mdefine_line|#define IS_PCI32_DIRECT(x)&t;((uint64_t)(x) &gt;= PCI32_MAPPED_BASE)
DECL|macro|IS_PCI64
mdefine_line|#define IS_PCI64(x)&t;&t;((uint64_t)(x) &gt;= PCI64_BASE)
macro_line|#endif&t;&t;&t;&t;/* __ASSEMBLY__ */
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
macro_line|#ifndef __ASSEMBLY__
DECL|macro|IS_GIO_LOCAL
mdefine_line|#define IS_GIO_LOCAL(x)&t;&t;((uint64_t)(x) &lt; GIO_MAPPED_BASE)
DECL|macro|IS_GIO_MAPPED
mdefine_line|#define IS_GIO_MAPPED(x)&t;((uint64_t)(x) &lt; GIO_DIRECT_BASE &amp;&amp; &bslash;&n;&t;&t;&t;&t;&t;(uint64_t)(x) &gt;= GIO_MAPPED_BASE)
DECL|macro|IS_GIO_DIRECT
mdefine_line|#define IS_GIO_DIRECT(x)&t;((uint64_t)(x) &gt;= GIO_MAPPED_BASE)
macro_line|#endif&t;&t;&t;&t;/* __ASSEMBLY__ */
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
mdefine_line|#define PCI64_ATTR_PREF&t;&t;(1ull &lt;&lt; 59)
DECL|macro|PCI64_ATTR_PREC
mdefine_line|#define PCI64_ATTR_PREC&t;&t;(1ull &lt;&lt; 58)
DECL|macro|PCI64_ATTR_VIRTUAL
mdefine_line|#define PCI64_ATTR_VIRTUAL&t;(1ull &lt;&lt; 57)
DECL|macro|PCI64_ATTR_BAR
mdefine_line|#define PCI64_ATTR_BAR&t;&t;(1ull &lt;&lt; 56)
DECL|macro|PCI64_ATTR_SWAP
mdefine_line|#define PCI64_ATTR_SWAP&t;&t;(1ull &lt;&lt; 55)
DECL|macro|PCI64_ATTR_RMF_MASK
mdefine_line|#define PCI64_ATTR_RMF_MASK&t;0x00ff000000000000
DECL|macro|PCI64_ATTR_RMF_SHFT
mdefine_line|#define PCI64_ATTR_RMF_SHFT&t;48
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Address translation entry for mapped pci32 accesses */
DECL|union|ate_u
r_typedef
r_union
id|ate_u
(brace
DECL|member|ent
r_uint64
id|ent
suffix:semicolon
DECL|struct|xb_ate_s
r_struct
id|xb_ate_s
(brace
multiline_comment|/* xbridge */
DECL|member|uint64_t
r_uint64
suffix:colon
l_int|16
suffix:semicolon
DECL|member|addr
r_uint64
id|addr
suffix:colon
l_int|36
suffix:semicolon
DECL|member|targ
r_uint64
id|targ
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved
r_uint64
id|reserved
suffix:colon
l_int|2
suffix:semicolon
DECL|member|swap
r_uint64
id|swap
suffix:colon
l_int|1
suffix:semicolon
DECL|member|barrier
r_uint64
id|barrier
suffix:colon
l_int|1
suffix:semicolon
DECL|member|prefetch
r_uint64
id|prefetch
suffix:colon
l_int|1
suffix:semicolon
DECL|member|precise
r_uint64
id|precise
suffix:colon
l_int|1
suffix:semicolon
DECL|member|coherent
r_uint64
id|coherent
suffix:colon
l_int|1
suffix:semicolon
DECL|member|valid
r_uint64
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|xb_field
)brace
id|xb_field
suffix:semicolon
DECL|struct|ate_s
r_struct
id|ate_s
(brace
multiline_comment|/* bridge */
DECL|member|rmf
r_uint64
id|rmf
suffix:colon
l_int|16
suffix:semicolon
DECL|member|addr
r_uint64
id|addr
suffix:colon
l_int|36
suffix:semicolon
DECL|member|targ
r_uint64
id|targ
suffix:colon
l_int|4
suffix:semicolon
DECL|member|reserved
r_uint64
id|reserved
suffix:colon
l_int|3
suffix:semicolon
DECL|member|barrier
r_uint64
id|barrier
suffix:colon
l_int|1
suffix:semicolon
DECL|member|prefetch
r_uint64
id|prefetch
suffix:colon
l_int|1
suffix:semicolon
DECL|member|precise
r_uint64
id|precise
suffix:colon
l_int|1
suffix:semicolon
DECL|member|coherent
r_uint64
id|coherent
suffix:colon
l_int|1
suffix:semicolon
DECL|member|valid
r_uint64
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
macro_line|#endif&t;&t;&t;&t;/* __ASSEMBLY__ */
DECL|macro|ATE_V
mdefine_line|#define ATE_V&t;&t;(1 &lt;&lt; 0)
DECL|macro|ATE_CO
mdefine_line|#define ATE_CO&t;&t;(1 &lt;&lt; 1)
DECL|macro|ATE_PREC
mdefine_line|#define ATE_PREC&t;(1 &lt;&lt; 2)
DECL|macro|ATE_PREF
mdefine_line|#define ATE_PREF&t;(1 &lt;&lt; 3)
DECL|macro|ATE_BAR
mdefine_line|#define ATE_BAR&t;&t;(1 &lt;&lt; 4)
DECL|macro|ATE_SWAP
mdefine_line|#define ATE_SWAP        (1 &lt;&lt; 5)
DECL|macro|ATE_PFNSHIFT
mdefine_line|#define ATE_PFNSHIFT&t;&t;12
DECL|macro|ATE_TIDSHIFT
mdefine_line|#define ATE_TIDSHIFT&t;&t;8
DECL|macro|ATE_RMFSHIFT
mdefine_line|#define ATE_RMFSHIFT&t;&t;48
DECL|macro|mkate
mdefine_line|#define mkate(xaddr, xid, attr) ((xaddr) &amp; 0x0000fffffffff000ULL) | &bslash;&n;&t;&t;&t;&t;((xid)&lt;&lt;ATE_TIDSHIFT) | &bslash;&n;&t;&t;&t;&t;(attr)
multiline_comment|/*&n; * for xbridge, bit 29 of the pci address is the swap bit */
DECL|macro|ATE_SWAPSHIFT
mdefine_line|#define ATE_SWAPSHIFT&t;&t;29
DECL|macro|ATE_SWAP_ON
mdefine_line|#define ATE_SWAP_ON(x)&t;&t;((x) |= (1 &lt;&lt; ATE_SWAPSHIFT))
DECL|macro|ATE_SWAP_OFF
mdefine_line|#define ATE_SWAP_OFF(x)&t;&t;((x) &amp;= ~(1 &lt;&lt; ATE_SWAPSHIFT))
multiline_comment|/* extern declarations */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* ========================================================================&n; */
macro_line|#ifdef&t;MACROFIELD_LINE
multiline_comment|/*&n; * This table forms a relation between the byte offset macros normally&n; * used for ASM coding and the calculated byte offsets of the fields&n; * in the C structure.&n; *&n; * See bridge_check.c and bridge_html.c for further details.&n; */
macro_line|#ifndef MACROFIELD_LINE_BITFIELD
DECL|macro|MACROFIELD_LINE_BITFIELD
mdefine_line|#define MACROFIELD_LINE_BITFIELD(m)&t;/* ignored */
macro_line|#endif
DECL|variable|bridge_macrofield
r_struct
id|macrofield_s
id|bridge_macrofield
(braket
)braket
op_assign
(brace
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_ID
comma
id|b_wid_id
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_REV_NUM
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_PART_NUM
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_MFG_NUM
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_STAT
comma
id|b_wid_stat
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_STAT_LLP_REC_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_STAT_LLP_TX_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_STAT_FLASH_SELECT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_STAT_PCI_GIO_N
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_STAT_PENDING
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_ERR_UPPER
comma
id|b_wid_err_upper
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_ERR_LOWER
comma
id|b_wid_err_lower
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_CONTROL
comma
id|b_wid_control
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_FLASH_WR_EN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_EN_CLK50
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_EN_CLK40
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_EN_CLK33
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_RST_MASK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_IO_SWAP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_MEM_SWAP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_PAGE_SIZE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_SS_PAR_BAD
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_SS_PAR_EN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_SSRAM_SIZE_MASK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_F_BAD_PKT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_LLP_XBAR_CRD_MASK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_CLR_RLLP_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_CLR_TLLP_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_SYS_END
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_MAX_TRANS_MASK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_CTRL_WIDGET_ID_MASK
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_REQ_TIMEOUT
comma
id|b_wid_req_timeout
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_INT_UPPER
comma
id|b_wid_int_upper
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_INT_VECTOR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_TARGET_ID
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_UPP_ADDR
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_INT_LOWER
comma
id|b_wid_int_lower
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_ERR_CMDWORD
comma
id|b_wid_err_cmdword
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_DIDN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_SIDN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_PACTYP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_TNUM
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_COHERENT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_DS
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_GBR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_VBPM
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_ERROR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_BARRIER
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_LLP
comma
id|b_wid_llp
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_LLP_MAXRETRY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_LLP_NULLTIMEOUT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|WIDGET_LLP_MAXBURST
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_TFLUSH
comma
id|b_wid_tflush
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_AUX_ERR
comma
id|b_wid_aux_err
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_RESP_UPPER
comma
id|b_wid_resp_upper
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_RESP_LOWER
comma
id|b_wid_resp_lower
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WID_TST_PIN_CTRL
comma
id|b_wid_tst_pin_ctrl
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DIR_MAP
comma
id|b_dir_map
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DIRMAP_W_ID
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DIRMAP_RMF_64
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DIRMAP_ADD512
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DIRMAP_OFF
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_RAM_PERR
comma
id|b_ram_perr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_ARB
comma
id|b_arb
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_REQ_WAIT_TICK_MASK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_REQ_WAIT_EN_MASK
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_FREEZE_GNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_HPRI_RING_B2
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_HPRI_RING_B1
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_HPRI_RING_B0
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_LPRI_RING_B2
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_LPRI_RING_B1
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ARB_LPRI_RING_B0
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_NIC
comma
id|b_nic
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_PCI_BUS_TIMEOUT
comma
id|b_pci_bus_timeout
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_PCI_CFG
comma
id|b_pci_cfg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_PCI_ERR_UPPER
comma
id|b_pci_err_upper
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_PCI_ERR_LOWER
comma
id|b_pci_err_lower
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_STATUS
comma
id|b_int_status
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_MULTI_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_PMU_ESIZE_FAULT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_UNEXP_RESP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_BAD_XRESP_PKT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_BAD_XREQ_PKT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_RESP_XTLK_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_REQ_XTLK_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_INVLD_ADDR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_UNSUPPORTED_XOP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_XREQ_FIFO_OFLOW
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_LLP_REC_SNERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_LLP_REC_CBERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_LLP_RCTY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_LLP_TX_RETRY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_LLP_TCTY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_SSRAM_PERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_PCI_ABORT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_PCI_PARITY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_PCI_SERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_PCI_PERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_PCI_MST_TIMEOUT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_PCI_RETRY_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_XREAD_REQ_TIMEOUT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_GIO_B_ENBL_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_ISR_INT_MSK
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ENABLE
comma
id|b_int_enable
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_UNEXP_RESP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_PMU_ESIZE_FAULT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_BAD_XRESP_PKT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_BAD_XREQ_PKT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_RESP_XTLK_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_REQ_XTLK_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_INVLD_ADDR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_UNSUPPORTED_XOP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_XREQ_FIFO_OFLOW
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_LLP_REC_SNERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_LLP_REC_CBERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_LLP_RCTY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_LLP_TX_RETRY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_LLP_TCTY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_SSRAM_PERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_PCI_ABORT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_PCI_PARITY
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_PCI_SERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_PCI_PERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_PCI_MST_TIMEOUT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_PCI_RETRY_CNT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_XREAD_REQ_TIMEOUT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_GIO_B_ENBL_ERR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IMR_INT_MSK
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_RST_STAT
comma
id|b_int_rst_stat
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_ALL_CLR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_MULTI_CLR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_CRP_GRP_CLR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_RESP_BUF_GRP_CLR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_REQ_DSP_GRP_CLR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_LLP_GRP_CLR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_SSRAM_GRP_CLR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_IRR_PCI_GRP_CLR
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_MODE
comma
id|b_int_mode
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|7
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|6
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|5
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|4
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|3
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|2
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|1
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INTMODE_CLR_PKT_EN
c_func
(paren
l_int|0
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_DEVICE
comma
id|b_int_device
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|7
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|6
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|5
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|4
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|3
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|2
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|1
)paren
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_DEV_MASK
c_func
(paren
l_int|0
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_HOST_ERR
comma
id|b_int_host_err
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_ADDR_HOST
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_INT_ADDR_FLD
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR0
comma
id|b_int_addr
(braket
l_int|0
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|0
)paren
comma
id|b_int_addr
(braket
l_int|0
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|1
)paren
comma
id|b_int_addr
(braket
l_int|1
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|2
)paren
comma
id|b_int_addr
(braket
l_int|2
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|3
)paren
comma
id|b_int_addr
(braket
l_int|3
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|4
)paren
comma
id|b_int_addr
(braket
l_int|4
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|5
)paren
comma
id|b_int_addr
(braket
l_int|5
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|6
)paren
comma
id|b_int_addr
(braket
l_int|6
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_INT_ADDR
c_func
(paren
l_int|7
)paren
comma
id|b_int_addr
(braket
l_int|7
)braket
dot
id|addr
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE0
comma
id|b_device
(braket
l_int|0
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_ERR_LOCK_EN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_PAGE_CHK_DIS
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_FORCE_PCI_PAR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_VIRTUAL_EN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_PMU_WRGA_EN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_DIR_WRGA_EN
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_DEV_SIZE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_RT
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_SWAP_PMU
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_SWAP_DIR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_PREF
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_PRECISE
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_COH
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_BARRIER
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_GBR
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_DEV_SWAP
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_DEV_IO_MEM
)paren
id|MACROFIELD_LINE_BITFIELD
c_func
(paren
id|BRIDGE_DEV_OFF_MASK
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|0
)paren
comma
id|b_device
(braket
l_int|0
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|1
)paren
comma
id|b_device
(braket
l_int|1
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|2
)paren
comma
id|b_device
(braket
l_int|2
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|3
)paren
comma
id|b_device
(braket
l_int|3
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|4
)paren
comma
id|b_device
(braket
l_int|4
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|5
)paren
comma
id|b_device
(braket
l_int|5
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|6
)paren
comma
id|b_device
(braket
l_int|6
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVICE
c_func
(paren
l_int|7
)paren
comma
id|b_device
(braket
l_int|7
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF0
comma
id|b_wr_req_buf
(braket
l_int|0
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|0
)paren
comma
id|b_wr_req_buf
(braket
l_int|0
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|1
)paren
comma
id|b_wr_req_buf
(braket
l_int|1
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|2
)paren
comma
id|b_wr_req_buf
(braket
l_int|2
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|3
)paren
comma
id|b_wr_req_buf
(braket
l_int|3
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|4
)paren
comma
id|b_wr_req_buf
(braket
l_int|4
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|5
)paren
comma
id|b_wr_req_buf
(braket
l_int|5
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|6
)paren
comma
id|b_wr_req_buf
(braket
l_int|6
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_WR_REQ_BUF
c_func
(paren
l_int|7
)paren
comma
id|b_wr_req_buf
(braket
l_int|7
)braket
dot
id|reg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_EVEN_RESP
comma
id|b_even_resp
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_ODD_RESP
comma
id|b_odd_resp
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_RESP_STATUS
comma
id|b_resp_status
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_RESP_CLEAR
comma
id|b_resp_clear
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_ATE_RAM
comma
id|b_int_ate_ram
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV0
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|0
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|0
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|1
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|1
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|2
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|2
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|3
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|3
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|4
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|4
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|5
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|5
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|6
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|6
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEV
c_func
(paren
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|0
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|0
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|1
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|1
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|2
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|2
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|3
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|3
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|4
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|4
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|5
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|5
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|6
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|6
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE0_CFG_DEVF
c_func
(paren
l_int|7
comma
l_int|7
)paren
comma
id|b_type0_cfg_dev
(braket
l_int|7
)braket
dot
id|f
(braket
l_int|7
)braket
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_TYPE1_CFG
comma
id|b_type1_cfg
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_PCI_IACK
comma
id|b_pci_iack
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_EXT_SSRAM
comma
id|b_ext_ate_ram
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO0
comma
id|b_devio
c_func
(paren
l_int|0
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|0
)paren
comma
id|b_devio
c_func
(paren
l_int|0
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|1
)paren
comma
id|b_devio
c_func
(paren
l_int|1
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|2
)paren
comma
id|b_devio
c_func
(paren
l_int|2
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|3
)paren
comma
id|b_devio
c_func
(paren
l_int|3
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|4
)paren
comma
id|b_devio
c_func
(paren
l_int|4
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|5
)paren
comma
id|b_devio
c_func
(paren
l_int|5
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|6
)paren
comma
id|b_devio
c_func
(paren
l_int|6
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_DEVIO
c_func
(paren
l_int|7
)paren
comma
id|b_devio
c_func
(paren
l_int|7
)paren
)paren
id|MACROFIELD_LINE
c_func
(paren
id|BRIDGE_EXTERNAL_FLASH
comma
id|b_external_flash
)paren
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __cplusplus
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif&t;&t;&t;&t;/* C or C++ */ 
macro_line|#endif                          /* _ASM_SN_PCI_BRIDGE_H */
eof
