multiline_comment|/*****************************************************************************&n;* sdladrv.h&t;SDLA Support Module.  Kernel API Definitions.&n;*&n;* Author: &t;Gideon Hack&t;&n;*&n;* Copyright:&t;(c) 1995-2000 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jun 02, 1999 &t;Gideon Hack&t;Added support for the S514 PCI adapter.&n;* Dec 11, 1996&t;Gene Kozin&t;Complete overhaul.&n;* Oct 17, 1996&t;Gene Kozin&t;Minor bug fixes.&n;* Jun 12, 1996&t;Gene Kozin &t;Added support for S503 card.&n;* Dec 06, 1995&t;Gene Kozin&t;Initial version.&n;*****************************************************************************/
macro_line|#ifndef&t;_SDLADRV_H
DECL|macro|_SDLADRV_H
mdefine_line|#define&t;_SDLADRV_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(a,b,c) (((a) &lt;&lt; 16) + ((b) &lt;&lt; 8) + (c))
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,0)
DECL|macro|LINUX_2_4
mdefine_line|#define LINUX_2_4&t;
macro_line|#elif LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
DECL|macro|LINUX_2_1
mdefine_line|#define LINUX_2_1
macro_line|#else
DECL|macro|LINUX_2_0
mdefine_line|#define LINUX_2_0
macro_line|#endif
DECL|macro|SDLA_MAXIORANGE
mdefine_line|#define&t;SDLA_MAXIORANGE&t;4&t;/* maximum I/O port range */
DECL|macro|SDLA_WINDOWSIZE
mdefine_line|#define&t;SDLA_WINDOWSIZE&t;0x2000&t;/* default dual-port memory window size */
multiline_comment|/****** Data Structures *****************************************************/
multiline_comment|/*----------------------------------------------------------------------------&n; * Adapter hardware configuration. Pointer to this structure is passed to all&n; * APIs.&n; */
DECL|struct|sdlahw
r_typedef
r_struct
id|sdlahw
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* adapter type */
DECL|member|fwid
r_int
id|fwid
suffix:semicolon
multiline_comment|/* firmware ID */
DECL|member|port
r_int
id|port
suffix:semicolon
multiline_comment|/* adapter I/O port base */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* interrupt request level */
DECL|member|S514_cpu_no
r_char
id|S514_cpu_no
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* PCI CPU Number */
DECL|member|S514_slot_no
r_int
r_char
id|S514_slot_no
suffix:semicolon
multiline_comment|/* PCI Slot Number */
DECL|member|auto_pci_cfg
r_char
id|auto_pci_cfg
suffix:semicolon
multiline_comment|/* Autodetect PCI Slot */
macro_line|#if defined(LINUX_2_1) || defined(LINUX_2_4)
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
multiline_comment|/* PCI device */
macro_line|#else
DECL|member|pci_bus
r_int
r_char
id|pci_bus
suffix:semicolon
multiline_comment|/* PCI bus number */
DECL|member|pci_dev_func
r_int
r_char
id|pci_dev_func
suffix:semicolon
multiline_comment|/* PCI device/function number */
macro_line|#endif
DECL|member|dpmbase
r_void
op_star
id|dpmbase
suffix:semicolon
multiline_comment|/* dual-port memory base */
DECL|member|dpmsize
r_int
id|dpmsize
suffix:semicolon
multiline_comment|/* dual-port memory size */
DECL|member|pclk
r_int
id|pclk
suffix:semicolon
multiline_comment|/* CPU clock rate, kHz */
DECL|member|memory
r_int
r_int
id|memory
suffix:semicolon
multiline_comment|/* memory size */
DECL|member|vector
r_int
r_int
id|vector
suffix:semicolon
multiline_comment|/* local offset of the DPM window */
DECL|member|io_range
r_int
id|io_range
suffix:semicolon
multiline_comment|/* I/O port range */
DECL|member|regs
r_int
r_char
id|regs
(braket
id|SDLA_MAXIORANGE
)braket
suffix:semicolon
multiline_comment|/* was written to registers */
DECL|member|reserved
r_int
id|reserved
(braket
l_int|5
)braket
suffix:semicolon
DECL|typedef|sdlahw_t
)brace
id|sdlahw_t
suffix:semicolon
multiline_comment|/****** Function Prototypes *************************************************/
r_extern
r_int
id|sdla_setup
(paren
id|sdlahw_t
op_star
id|hw
comma
r_void
op_star
id|sfm
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|sdla_down
(paren
id|sdlahw_t
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_int
id|sdla_inten
(paren
id|sdlahw_t
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_int
id|sdla_intde
(paren
id|sdlahw_t
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_int
id|sdla_intack
(paren
id|sdlahw_t
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_void
id|S514_intack
(paren
id|sdlahw_t
op_star
id|hw
comma
id|u32
id|int_status
)paren
suffix:semicolon
r_extern
r_void
id|read_S514_int_stat
(paren
id|sdlahw_t
op_star
id|hw
comma
id|u32
op_star
id|int_status
)paren
suffix:semicolon
r_extern
r_int
id|sdla_intr
(paren
id|sdlahw_t
op_star
id|hw
)paren
suffix:semicolon
r_extern
r_int
id|sdla_mapmem
(paren
id|sdlahw_t
op_star
id|hw
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|sdla_peek
(paren
id|sdlahw_t
op_star
id|hw
comma
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|sdla_poke
(paren
id|sdlahw_t
op_star
id|hw
comma
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|sdla_exec
(paren
r_void
op_star
id|opflag
)paren
suffix:semicolon
r_extern
r_int
id|wanpipe_hw_probe
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;/* _SDLADRV_H */
eof
