multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_SN_PCI_PIC_H
DECL|macro|_ASM_SN_PCI_PIC_H
mdefine_line|#define _ASM_SN_PCI_PIC_H
multiline_comment|/*&n; * The PIC ASIC is a follow-on to the Bridge and Xbridge ASICs.&n; * It shares many of the same registers as those chips and therefore&n; * the primary structure for the PIC will be bridge_s as defined&n; * in irix/kern/sys/PCI/bridge.h.   This file is intended as a complement&n; * to bridge.h, which includes this file.  &n; */
multiline_comment|/*&n; * PIC AS DEVICE ZERO&n; * ------------------&n; *&n; * PIC handles PCI/X busses.  PCI/X requires that the &squot;bridge&squot; (i.e. PIC)&n; * be designated as &squot;device 0&squot;.   That is a departure from earlier SGI&n; * PCI bridges.  Because of that we use config space 1 to access the&n; * config space of the first actual PCI device on the bus. &n; * Here&squot;s what the PIC manual says:&n; *&n; *     The current PCI-X bus specification now defines that the parent&n; *     hosts bus bridge (PIC for example) must be device 0 on bus 0. PIC&n; *     reduced the total number of devices from 8 to 4 and removed the&n; *     device registers and windows, now only supporting devices 0,1,2, and&n; *     3. PIC did leave all 8 configuration space windows. The reason was&n; *     there was nothing to gain by removing them. Here in lies the problem.&n; *     The device numbering we do using 0 through 3 is unrelated to the device&n; *     numbering which PCI-X requires in configuration space. In the past we&n; *     correlated Configs pace and our device space 0 &lt;-&gt; 0, 1 &lt;-&gt; 1, etc.&n; *     PCI-X requires we start a 1, not 0 and currently the PX brick&n; *     does associate our:&n; * &n; *         device 0 with configuration space window 1,&n; *         device 1 with configuration space window 2, &n; *         device 2 with configuration space window 3,&n; *         device 3 with configuration space window 4.&n; *&n; * The net effect is that all config space access are off-by-one with &n; * relation to other per-slot accesses on the PIC.   &n; * Here is a table that shows some of that:&n; *&n; *                               Internal Slot#&n; *           |&n; *           |     0         1        2         3&n; * ----------|---------------------------------------&n; * config    |  0x21000   0x22000  0x23000   0x24000&n; *           |&n; * even rrb  |  0[0]      n/a      1[0]      n/a&t;[] == implied even/odd&n; *           |&n; * odd rrb   |  n/a       0[1]     n/a       1[1]&n; *           |&n; * int dev   |  00       01        10        11&n; *           |&n; * ext slot# |  1        2         3         4&n; * ----------|---------------------------------------&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
singleline_comment|// #include &lt;sys/types.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
multiline_comment|/*********************************************************************&n; *    bus provider function table&n; *&n; *&t;Normally, this table is only handed off explicitly&n; *&t;during provider initialization, and the PCI generic&n; *&t;layer will stash a pointer to it in the vertex; however,&n; *&t;exporting it explicitly enables a performance hack in&n; *&t;the generic PCI provider where if we know at compile&n; *&t;time that the only possible PCI provider is a&n; *&t;pcibr, we can go directly to this ops table.&n; */
r_extern
id|pciio_provider_t
id|pci_pic_provider
suffix:semicolon
multiline_comment|/*********************************************************************&n; * misc defines&n; *&n; */
DECL|macro|PIC_WIDGET_PART_NUM_BUS0
mdefine_line|#define PIC_WIDGET_PART_NUM_BUS0 0xd102
DECL|macro|PIC_WIDGET_PART_NUM_BUS1
mdefine_line|#define PIC_WIDGET_PART_NUM_BUS1 0xd112
DECL|macro|PIC_WIDGET_MFGR_NUM
mdefine_line|#define PIC_WIDGET_MFGR_NUM 0x24
DECL|macro|PIC_WIDGET_REV_A
mdefine_line|#define PIC_WIDGET_REV_A  0x1
DECL|macro|IS_PIC_PART_REV_A
mdefine_line|#define IS_PIC_PART_REV_A(rev) &bslash;&n;&t;((rev == (PIC_WIDGET_PART_NUM_BUS0 &lt;&lt; 4 | PIC_WIDGET_REV_A)) || &bslash;&n;&t;(rev == (PIC_WIDGET_PART_NUM_BUS1 &lt;&lt; 4 | PIC_WIDGET_REV_A)))
multiline_comment|/*********************************************************************&n; * register offset defines&n; *&n; */
multiline_comment|/* Identification Register  -- read-only */
DECL|macro|PIC_IDENTIFICATION
mdefine_line|#define PIC_IDENTIFICATION 0x00000000
multiline_comment|/* Status Register  -- read-only */
DECL|macro|PIC_STATUS
mdefine_line|#define PIC_STATUS 0x00000008
multiline_comment|/* Upper Address Holding Register Bus Side Errors  -- read-only */
DECL|macro|PIC_UPPER_ADDR_REG_BUS_SIDE_ERRS
mdefine_line|#define PIC_UPPER_ADDR_REG_BUS_SIDE_ERRS 0x00000010
multiline_comment|/* Lower Address Holding Register Bus Side Errors  -- read-only */
DECL|macro|PIC_LOWER_ADDR_REG_BUS_SIDE_ERRS
mdefine_line|#define PIC_LOWER_ADDR_REG_BUS_SIDE_ERRS 0x00000018
multiline_comment|/* Control Register  -- read/write */
DECL|macro|PIC_CONTROL
mdefine_line|#define PIC_CONTROL 0x00000020
multiline_comment|/* PCI Request Time-out Value Register  -- read/write */
DECL|macro|PIC_PCI_REQ_TIME_OUT_VALUE
mdefine_line|#define PIC_PCI_REQ_TIME_OUT_VALUE 0x00000028
multiline_comment|/* Interrupt Destination Upper Address Register  -- read/write */
DECL|macro|PIC_INTR_DEST_UPPER_ADDR
mdefine_line|#define PIC_INTR_DEST_UPPER_ADDR 0x00000030
multiline_comment|/* Interrupt Destination Lower Address Register  -- read/write */
DECL|macro|PIC_INTR_DEST_LOWER_ADDR
mdefine_line|#define PIC_INTR_DEST_LOWER_ADDR 0x00000038
multiline_comment|/* Command Word Holding Register Bus Side  -- read-only */
DECL|macro|PIC_CMD_WORD_REG_BUS_SIDE
mdefine_line|#define PIC_CMD_WORD_REG_BUS_SIDE 0x00000040
multiline_comment|/* LLP Configuration Register (Bus 0 Only)  -- read/write */
DECL|macro|PIC_LLP_CFG_REG_
mdefine_line|#define PIC_LLP_CFG_REG_(BUS_0_ONLY) 0x00000048
multiline_comment|/* PCI Target Flush Register  -- read-only */
DECL|macro|PIC_PCI_TARGET_FLUSH
mdefine_line|#define PIC_PCI_TARGET_FLUSH 0x00000050
multiline_comment|/* Command Word Holding Register Link Side  -- read-only */
DECL|macro|PIC_CMD_WORD_REG_LINK_SIDE
mdefine_line|#define PIC_CMD_WORD_REG_LINK_SIDE 0x00000058
multiline_comment|/* Response Buffer Error Upper Address Holding  -- read-only */
DECL|macro|PIC_RESP_BUF_ERR_UPPER_ADDR_
mdefine_line|#define PIC_RESP_BUF_ERR_UPPER_ADDR_ 0x00000060
multiline_comment|/* Response Buffer Error Lower Address Holding  -- read-only */
DECL|macro|PIC_RESP_BUF_ERR_LOWER_ADDR_
mdefine_line|#define PIC_RESP_BUF_ERR_LOWER_ADDR_ 0x00000068
multiline_comment|/* Test Pin Control Register  -- read/write */
DECL|macro|PIC_TEST_PIN_CONTROL
mdefine_line|#define PIC_TEST_PIN_CONTROL 0x00000070
multiline_comment|/* Address Holding Register Link Side Errors  -- read-only */
DECL|macro|PIC_ADDR_REG_LINK_SIDE_ERRS
mdefine_line|#define PIC_ADDR_REG_LINK_SIDE_ERRS 0x00000078
multiline_comment|/* Direct Map Register  -- read/write */
DECL|macro|PIC_DIRECT_MAP
mdefine_line|#define PIC_DIRECT_MAP 0x00000080
multiline_comment|/* PCI Map Fault Address Register  -- read-only */
DECL|macro|PIC_PCI_MAP_FAULT_ADDR
mdefine_line|#define PIC_PCI_MAP_FAULT_ADDR 0x00000090
multiline_comment|/* Arbitration Priority Register  -- read/write */
DECL|macro|PIC_ARBITRATION_PRIORITY
mdefine_line|#define PIC_ARBITRATION_PRIORITY 0x000000A0
multiline_comment|/* Internal Ram Parity Error Register  -- read-only */
DECL|macro|PIC_INTERNAL_RAM_PARITY_ERR
mdefine_line|#define PIC_INTERNAL_RAM_PARITY_ERR 0x000000B0
multiline_comment|/* PCI Time-out Register  -- read/write */
DECL|macro|PIC_PCI_TIME_OUT
mdefine_line|#define PIC_PCI_TIME_OUT 0x000000C0
multiline_comment|/* PCI Type 1 Configuration Register  -- read/write */
DECL|macro|PIC_PCI_TYPE_1_CFG
mdefine_line|#define PIC_PCI_TYPE_1_CFG 0x000000C8
multiline_comment|/* PCI Bus Error Upper Address Holding Register  -- read-only */
DECL|macro|PIC_PCI_BUS_ERR_UPPER_ADDR_
mdefine_line|#define PIC_PCI_BUS_ERR_UPPER_ADDR_ 0x000000D0
multiline_comment|/* PCI Bus Error Lower Address Holding Register  -- read-only */
DECL|macro|PIC_PCI_BUS_ERR_LOWER_ADDR_
mdefine_line|#define PIC_PCI_BUS_ERR_LOWER_ADDR_ 0x000000D8
multiline_comment|/* PCIX Error Address Register  -- read-only */
DECL|macro|PIC_PCIX_ERR_ADDR
mdefine_line|#define PIC_PCIX_ERR_ADDR 0x000000E0
multiline_comment|/* PCIX Error Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_ERR_ATTRIBUTE
mdefine_line|#define PIC_PCIX_ERR_ATTRIBUTE 0x000000E8
multiline_comment|/* PCIX Error Data Register  -- read-only */
DECL|macro|PIC_PCIX_ERR_DATA
mdefine_line|#define PIC_PCIX_ERR_DATA 0x000000F0
multiline_comment|/* PCIX Read Request Timeout Error Register  -- read-only */
DECL|macro|PIC_PCIX_READ_REQ_TIMEOUT_ERR
mdefine_line|#define PIC_PCIX_READ_REQ_TIMEOUT_ERR 0x000000F8
multiline_comment|/* Interrupt Status Register  -- read-only */
DECL|macro|PIC_INTR_STATUS
mdefine_line|#define PIC_INTR_STATUS 0x00000100
multiline_comment|/* Interrupt Enable Register  -- read/write */
DECL|macro|PIC_INTR_ENABLE
mdefine_line|#define PIC_INTR_ENABLE 0x00000108
multiline_comment|/* Reset Interrupt Status Register  -- write-only */
DECL|macro|PIC_RESET_INTR_STATUS
mdefine_line|#define PIC_RESET_INTR_STATUS 0x00000110
multiline_comment|/* Interrupt Mode Register  -- read/write */
DECL|macro|PIC_INTR_MODE
mdefine_line|#define PIC_INTR_MODE 0x00000118
multiline_comment|/* Interrupt Device Register  -- read/write */
DECL|macro|PIC_INTR_DEVICE
mdefine_line|#define PIC_INTR_DEVICE 0x00000120
multiline_comment|/* Host Error Field Register  -- read/write */
DECL|macro|PIC_HOST_ERR_FIELD
mdefine_line|#define PIC_HOST_ERR_FIELD 0x00000128
multiline_comment|/* Interrupt Pin 0 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_0_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_0_HOST_ADDR 0x00000130
multiline_comment|/* Interrupt Pin 1 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_1_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_1_HOST_ADDR 0x00000138
multiline_comment|/* Interrupt Pin 2 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_2_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_2_HOST_ADDR 0x00000140
multiline_comment|/* Interrupt Pin 3 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_3_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_3_HOST_ADDR 0x00000148
multiline_comment|/* Interrupt Pin 4 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_4_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_4_HOST_ADDR 0x00000150
multiline_comment|/* Interrupt Pin 5 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_5_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_5_HOST_ADDR 0x00000158
multiline_comment|/* Interrupt Pin 6 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_6_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_6_HOST_ADDR 0x00000160
multiline_comment|/* Interrupt Pin 7 Host Address Register  -- read/write */
DECL|macro|PIC_INTR_PIN_7_HOST_ADDR
mdefine_line|#define PIC_INTR_PIN_7_HOST_ADDR 0x00000168
multiline_comment|/* Error Interrupt View Register  -- read-only */
DECL|macro|PIC_ERR_INTR_VIEW
mdefine_line|#define PIC_ERR_INTR_VIEW 0x00000170
multiline_comment|/* Multiple Interrupt Register  -- read-only */
DECL|macro|PIC_MULTIPLE_INTR
mdefine_line|#define PIC_MULTIPLE_INTR 0x00000178
multiline_comment|/* Force Always Interrupt 0 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_0
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_0 0x00000180
multiline_comment|/* Force Always Interrupt 1 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_1
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_1 0x00000188
multiline_comment|/* Force Always Interrupt 2 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_2
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_2 0x00000190
multiline_comment|/* Force Always Interrupt 3 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_3
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_3 0x00000198
multiline_comment|/* Force Always Interrupt 4 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_4
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_4 0x000001A0
multiline_comment|/* Force Always Interrupt 5 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_5
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_5 0x000001A8
multiline_comment|/* Force Always Interrupt 6 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_6
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_6 0x000001B0
multiline_comment|/* Force Always Interrupt 7 Register  -- write-only */
DECL|macro|PIC_FORCE_ALWAYS_INTR_7
mdefine_line|#define PIC_FORCE_ALWAYS_INTR_7 0x000001B8
multiline_comment|/* Force w/Pin Interrupt 0 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_0
mdefine_line|#define PIC_FORCE_PIN_INTR_0 0x000001C0
multiline_comment|/* Force w/Pin Interrupt 1 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_1
mdefine_line|#define PIC_FORCE_PIN_INTR_1 0x000001C8
multiline_comment|/* Force w/Pin Interrupt 2 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_2
mdefine_line|#define PIC_FORCE_PIN_INTR_2 0x000001D0
multiline_comment|/* Force w/Pin Interrupt 3 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_3
mdefine_line|#define PIC_FORCE_PIN_INTR_3 0x000001D8
multiline_comment|/* Force w/Pin Interrupt 4 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_4
mdefine_line|#define PIC_FORCE_PIN_INTR_4 0x000001E0
multiline_comment|/* Force w/Pin Interrupt 5 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_5
mdefine_line|#define PIC_FORCE_PIN_INTR_5 0x000001E8
multiline_comment|/* Force w/Pin Interrupt 6 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_6
mdefine_line|#define PIC_FORCE_PIN_INTR_6 0x000001F0
multiline_comment|/* Force w/Pin Interrupt 7 Register  -- write-only */
DECL|macro|PIC_FORCE_PIN_INTR_7
mdefine_line|#define PIC_FORCE_PIN_INTR_7 0x000001F8
multiline_comment|/* Device 0 Register  -- read/write */
DECL|macro|PIC_DEVICE_0
mdefine_line|#define PIC_DEVICE_0 0x00000200
multiline_comment|/* Device 1 Register  -- read/write */
DECL|macro|PIC_DEVICE_1
mdefine_line|#define PIC_DEVICE_1 0x00000208
multiline_comment|/* Device 2 Register  -- read/write */
DECL|macro|PIC_DEVICE_2
mdefine_line|#define PIC_DEVICE_2 0x00000210
multiline_comment|/* Device 3 Register  -- read/write */
DECL|macro|PIC_DEVICE_3
mdefine_line|#define PIC_DEVICE_3 0x00000218
multiline_comment|/* Device 0 Write Request Buffer Register  -- read-only */
DECL|macro|PIC_DEVICE_0_WRITE_REQ_BUF
mdefine_line|#define PIC_DEVICE_0_WRITE_REQ_BUF 0x00000240
multiline_comment|/* Device 1 Write Request Buffer Register  -- read-only */
DECL|macro|PIC_DEVICE_1_WRITE_REQ_BUF
mdefine_line|#define PIC_DEVICE_1_WRITE_REQ_BUF 0x00000248
multiline_comment|/* Device 2 Write Request Buffer Register  -- read-only */
DECL|macro|PIC_DEVICE_2_WRITE_REQ_BUF
mdefine_line|#define PIC_DEVICE_2_WRITE_REQ_BUF 0x00000250
multiline_comment|/* Device 3 Write Request Buffer Register  -- read-only */
DECL|macro|PIC_DEVICE_3_WRITE_REQ_BUF
mdefine_line|#define PIC_DEVICE_3_WRITE_REQ_BUF 0x00000258
multiline_comment|/* Even Device Response Buffer Register  -- read/write */
DECL|macro|PIC_EVEN_DEVICE_RESP_BUF
mdefine_line|#define PIC_EVEN_DEVICE_RESP_BUF 0x00000280
multiline_comment|/* Odd Device Response Buffer Register  -- read/write */
DECL|macro|PIC_ODD_DEVICE_RESP_BUF
mdefine_line|#define PIC_ODD_DEVICE_RESP_BUF 0x00000288
multiline_comment|/* Read Response Buffer Status Register  -- read-only */
DECL|macro|PIC_READ_RESP_BUF_STATUS
mdefine_line|#define PIC_READ_RESP_BUF_STATUS 0x00000290
multiline_comment|/* Read Response Buffer Clear Register  -- write-only */
DECL|macro|PIC_READ_RESP_BUF_CLEAR
mdefine_line|#define PIC_READ_RESP_BUF_CLEAR 0x00000298
multiline_comment|/* PCI RR 0 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_0_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_0_UPPER_ADDR_MATCH 0x00000300
multiline_comment|/* PCI RR 0 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_0_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_0_LOWER_ADDR_MATCH 0x00000308
multiline_comment|/* PCI RR 1 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_1_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_1_UPPER_ADDR_MATCH 0x00000310
multiline_comment|/* PCI RR 1 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_1_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_1_LOWER_ADDR_MATCH 0x00000318
multiline_comment|/* PCI RR 2 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_2_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_2_UPPER_ADDR_MATCH 0x00000320
multiline_comment|/* PCI RR 2 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_2_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_2_LOWER_ADDR_MATCH 0x00000328
multiline_comment|/* PCI RR 3 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_3_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_3_UPPER_ADDR_MATCH 0x00000330
multiline_comment|/* PCI RR 3 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_3_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_3_LOWER_ADDR_MATCH 0x00000338
multiline_comment|/* PCI RR 4 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_4_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_4_UPPER_ADDR_MATCH 0x00000340
multiline_comment|/* PCI RR 4 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_4_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_4_LOWER_ADDR_MATCH 0x00000348
multiline_comment|/* PCI RR 5 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_5_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_5_UPPER_ADDR_MATCH 0x00000350
multiline_comment|/* PCI RR 5 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_5_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_5_LOWER_ADDR_MATCH 0x00000358
multiline_comment|/* PCI RR 6 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_6_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_6_UPPER_ADDR_MATCH 0x00000360
multiline_comment|/* PCI RR 6 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_6_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_6_LOWER_ADDR_MATCH 0x00000368
multiline_comment|/* PCI RR 7 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_7_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_7_UPPER_ADDR_MATCH 0x00000370
multiline_comment|/* PCI RR 7 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_7_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_7_LOWER_ADDR_MATCH 0x00000378
multiline_comment|/* PCI RR 8 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_8_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_8_UPPER_ADDR_MATCH 0x00000380
multiline_comment|/* PCI RR 8 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_8_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_8_LOWER_ADDR_MATCH 0x00000388
multiline_comment|/* PCI RR 9 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_9_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_9_UPPER_ADDR_MATCH 0x00000390
multiline_comment|/* PCI RR 9 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_9_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_9_LOWER_ADDR_MATCH 0x00000398
multiline_comment|/* PCI RR 10 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_10_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_10_UPPER_ADDR_MATCH 0x000003A0
multiline_comment|/* PCI RR 10 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_10_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_10_LOWER_ADDR_MATCH 0x000003A8
multiline_comment|/* PCI RR 11 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_11_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_11_UPPER_ADDR_MATCH 0x000003B0
multiline_comment|/* PCI RR 11 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_11_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_11_LOWER_ADDR_MATCH 0x000003B8
multiline_comment|/* PCI RR 12 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_12_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_12_UPPER_ADDR_MATCH 0x000003C0
multiline_comment|/* PCI RR 12 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_12_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_12_LOWER_ADDR_MATCH 0x000003C8
multiline_comment|/* PCI RR 13 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_13_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_13_UPPER_ADDR_MATCH 0x000003D0
multiline_comment|/* PCI RR 13 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_13_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_13_LOWER_ADDR_MATCH 0x000003D8
multiline_comment|/* PCI RR 14 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_14_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_14_UPPER_ADDR_MATCH 0x000003E0
multiline_comment|/* PCI RR 14 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_14_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_14_LOWER_ADDR_MATCH 0x000003E8
multiline_comment|/* PCI RR 15 Upper Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_15_UPPER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_15_UPPER_ADDR_MATCH 0x000003F0
multiline_comment|/* PCI RR 15 Lower Address Match Register  -- read-only */
DECL|macro|PIC_PCI_RR_15_LOWER_ADDR_MATCH
mdefine_line|#define PIC_PCI_RR_15_LOWER_ADDR_MATCH 0x000003F8
multiline_comment|/* Buffer 0 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_0_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_0_FLUSH_CNT_WITH_DATA_TOUCH 0x00000400
multiline_comment|/* Buffer 0 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_0_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_0_FLUSH_CNT_W_O_DATA_TOUCH 0x00000408
multiline_comment|/* Buffer 0 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_0_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_0_REQ_IN_FLIGHT_CNT 0x00000410
multiline_comment|/* Buffer 0 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_0_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_0_PREFETCH_REQ_CNT 0x00000418
multiline_comment|/* Buffer 0 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_0_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_0_TOTAL_PCI_RETRY_CNT 0x00000420
multiline_comment|/* Buffer 0 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_0_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_0_MAX_PCI_RETRY_CNT 0x00000428
multiline_comment|/* Buffer 0 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_0_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_0_MAX_LATENCY_CNT 0x00000430
multiline_comment|/* Buffer 0 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_0_CLEAR_ALL
mdefine_line|#define PIC_BUF_0_CLEAR_ALL 0x00000438
multiline_comment|/* Buffer 2 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_2_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_2_FLUSH_CNT_WITH_DATA_TOUCH 0x00000440
multiline_comment|/* Buffer 2 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_2_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_2_FLUSH_CNT_W_O_DATA_TOUCH 0x00000448
multiline_comment|/* Buffer 2 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_2_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_2_REQ_IN_FLIGHT_CNT 0x00000450
multiline_comment|/* Buffer 2 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_2_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_2_PREFETCH_REQ_CNT 0x00000458
multiline_comment|/* Buffer 2 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_2_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_2_TOTAL_PCI_RETRY_CNT 0x00000460
multiline_comment|/* Buffer 2 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_2_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_2_MAX_PCI_RETRY_CNT 0x00000468
multiline_comment|/* Buffer 2 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_2_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_2_MAX_LATENCY_CNT 0x00000470
multiline_comment|/* Buffer 2 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_2_CLEAR_ALL
mdefine_line|#define PIC_BUF_2_CLEAR_ALL 0x00000478
multiline_comment|/* Buffer 4 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_4_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_4_FLUSH_CNT_WITH_DATA_TOUCH 0x00000480
multiline_comment|/* Buffer 4 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_4_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_4_FLUSH_CNT_W_O_DATA_TOUCH 0x00000488
multiline_comment|/* Buffer 4 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_4_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_4_REQ_IN_FLIGHT_CNT 0x00000490
multiline_comment|/* Buffer 4 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_4_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_4_PREFETCH_REQ_CNT 0x00000498
multiline_comment|/* Buffer 4 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_4_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_4_TOTAL_PCI_RETRY_CNT 0x000004A0
multiline_comment|/* Buffer 4 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_4_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_4_MAX_PCI_RETRY_CNT 0x000004A8
multiline_comment|/* Buffer 4 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_4_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_4_MAX_LATENCY_CNT 0x000004B0
multiline_comment|/* Buffer 4 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_4_CLEAR_ALL
mdefine_line|#define PIC_BUF_4_CLEAR_ALL 0x000004B8
multiline_comment|/* Buffer 6 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_6_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_6_FLUSH_CNT_WITH_DATA_TOUCH 0x000004C0
multiline_comment|/* Buffer 6 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_6_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_6_FLUSH_CNT_W_O_DATA_TOUCH 0x000004C8
multiline_comment|/* Buffer 6 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_6_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_6_REQ_IN_FLIGHT_CNT 0x000004D0
multiline_comment|/* Buffer 6 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_6_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_6_PREFETCH_REQ_CNT 0x000004D8
multiline_comment|/* Buffer 6 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_6_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_6_TOTAL_PCI_RETRY_CNT 0x000004E0
multiline_comment|/* Buffer 6 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_6_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_6_MAX_PCI_RETRY_CNT 0x000004E8
multiline_comment|/* Buffer 6 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_6_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_6_MAX_LATENCY_CNT 0x000004F0
multiline_comment|/* Buffer 6 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_6_CLEAR_ALL
mdefine_line|#define PIC_BUF_6_CLEAR_ALL 0x000004F8
multiline_comment|/* Buffer 8 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_8_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_8_FLUSH_CNT_WITH_DATA_TOUCH 0x00000500
multiline_comment|/* Buffer 8 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_8_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_8_FLUSH_CNT_W_O_DATA_TOUCH 0x00000508
multiline_comment|/* Buffer 8 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_8_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_8_REQ_IN_FLIGHT_CNT 0x00000510
multiline_comment|/* Buffer 8 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_8_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_8_PREFETCH_REQ_CNT 0x00000518
multiline_comment|/* Buffer 8 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_8_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_8_TOTAL_PCI_RETRY_CNT 0x00000520
multiline_comment|/* Buffer 8 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_8_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_8_MAX_PCI_RETRY_CNT 0x00000528
multiline_comment|/* Buffer 8 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_8_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_8_MAX_LATENCY_CNT 0x00000530
multiline_comment|/* Buffer 8 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_8_CLEAR_ALL
mdefine_line|#define PIC_BUF_8_CLEAR_ALL 0x00000538
multiline_comment|/* Buffer 10 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_10_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_10_FLUSH_CNT_WITH_DATA_TOUCH 0x00000540
multiline_comment|/* Buffer 10 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_10_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_10_FLUSH_CNT_W_O_DATA_TOUCH 0x00000548
multiline_comment|/* Buffer 10 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_10_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_10_REQ_IN_FLIGHT_CNT 0x00000550
multiline_comment|/* Buffer 10 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_10_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_10_PREFETCH_REQ_CNT 0x00000558
multiline_comment|/* Buffer 10 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_10_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_10_TOTAL_PCI_RETRY_CNT 0x00000560
multiline_comment|/* Buffer 10 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_10_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_10_MAX_PCI_RETRY_CNT 0x00000568
multiline_comment|/* Buffer 10 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_10_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_10_MAX_LATENCY_CNT 0x00000570
multiline_comment|/* Buffer 10 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_10_CLEAR_ALL
mdefine_line|#define PIC_BUF_10_CLEAR_ALL 0x00000578
multiline_comment|/* Buffer 12 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_12_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_12_FLUSH_CNT_WITH_DATA_TOUCH 0x00000580
multiline_comment|/* Buffer 12 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_12_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_12_FLUSH_CNT_W_O_DATA_TOUCH 0x00000588
multiline_comment|/* Buffer 12 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_12_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_12_REQ_IN_FLIGHT_CNT 0x00000590
multiline_comment|/* Buffer 12 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_12_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_12_PREFETCH_REQ_CNT 0x00000598
multiline_comment|/* Buffer 12 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_12_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_12_TOTAL_PCI_RETRY_CNT 0x000005A0
multiline_comment|/* Buffer 12 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_12_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_12_MAX_PCI_RETRY_CNT 0x000005A8
multiline_comment|/* Buffer 12 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_12_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_12_MAX_LATENCY_CNT 0x000005B0
multiline_comment|/* Buffer 12 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_12_CLEAR_ALL
mdefine_line|#define PIC_BUF_12_CLEAR_ALL 0x000005B8
multiline_comment|/* Buffer 14 Flush Count with Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_14_FLUSH_CNT_WITH_DATA_TOUCH
mdefine_line|#define PIC_BUF_14_FLUSH_CNT_WITH_DATA_TOUCH 0x000005C0
multiline_comment|/* Buffer 14 Flush Count w/o Data Touch Register  -- read/write */
DECL|macro|PIC_BUF_14_FLUSH_CNT_W_O_DATA_TOUCH
mdefine_line|#define PIC_BUF_14_FLUSH_CNT_W_O_DATA_TOUCH 0x000005C8
multiline_comment|/* Buffer 14 Request in Flight Count Register  -- read/write */
DECL|macro|PIC_BUF_14_REQ_IN_FLIGHT_CNT
mdefine_line|#define PIC_BUF_14_REQ_IN_FLIGHT_CNT 0x000005D0
multiline_comment|/* Buffer 14 Prefetch Request Count Register  -- read/write */
DECL|macro|PIC_BUF_14_PREFETCH_REQ_CNT
mdefine_line|#define PIC_BUF_14_PREFETCH_REQ_CNT 0x000005D8
multiline_comment|/* Buffer 14 Total PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_14_TOTAL_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_14_TOTAL_PCI_RETRY_CNT 0x000005E0
multiline_comment|/* Buffer 14 Max PCI Retry Count Register  -- read/write */
DECL|macro|PIC_BUF_14_MAX_PCI_RETRY_CNT
mdefine_line|#define PIC_BUF_14_MAX_PCI_RETRY_CNT 0x000005E8
multiline_comment|/* Buffer 14 Max Latency Count Register  -- read/write */
DECL|macro|PIC_BUF_14_MAX_LATENCY_CNT
mdefine_line|#define PIC_BUF_14_MAX_LATENCY_CNT 0x000005F0
multiline_comment|/* Buffer 14 Clear All Register  -- read/write */
DECL|macro|PIC_BUF_14_CLEAR_ALL
mdefine_line|#define PIC_BUF_14_CLEAR_ALL 0x000005F8
multiline_comment|/* PCIX Read Buffer 0 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_0_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_0_ADDR 0x00000A00
multiline_comment|/* PCIX Read Buffer 0 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_0_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_0_ATTRIBUTE 0x00000A08
multiline_comment|/* PCIX Read Buffer 1 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_1_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_1_ADDR 0x00000A10
multiline_comment|/* PCIX Read Buffer 1 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_1_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_1_ATTRIBUTE 0x00000A18
multiline_comment|/* PCIX Read Buffer 2 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_2_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_2_ADDR 0x00000A20
multiline_comment|/* PCIX Read Buffer 2 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_2_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_2_ATTRIBUTE 0x00000A28
multiline_comment|/* PCIX Read Buffer 3 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_3_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_3_ADDR 0x00000A30
multiline_comment|/* PCIX Read Buffer 3 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_3_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_3_ATTRIBUTE 0x00000A38
multiline_comment|/* PCIX Read Buffer 4 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_4_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_4_ADDR 0x00000A40
multiline_comment|/* PCIX Read Buffer 4 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_4_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_4_ATTRIBUTE 0x00000A48
multiline_comment|/* PCIX Read Buffer 5 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_5_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_5_ADDR 0x00000A50
multiline_comment|/* PCIX Read Buffer 5 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_5_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_5_ATTRIBUTE 0x00000A58
multiline_comment|/* PCIX Read Buffer 6 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_6_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_6_ADDR 0x00000A60
multiline_comment|/* PCIX Read Buffer 6 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_6_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_6_ATTRIBUTE 0x00000A68
multiline_comment|/* PCIX Read Buffer 7 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_7_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_7_ADDR 0x00000A70
multiline_comment|/* PCIX Read Buffer 7 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_7_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_7_ATTRIBUTE 0x00000A78
multiline_comment|/* PCIX Read Buffer 8 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_8_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_8_ADDR 0x00000A80
multiline_comment|/* PCIX Read Buffer 8 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_8_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_8_ATTRIBUTE 0x00000A88
multiline_comment|/* PCIX Read Buffer 9 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_9_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_9_ADDR 0x00000A90
multiline_comment|/* PCIX Read Buffer 9 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_9_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_9_ATTRIBUTE 0x00000A98
multiline_comment|/* PCIX Read Buffer 10 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_10_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_10_ADDR 0x00000AA0
multiline_comment|/* PCIX Read Buffer 10 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_10_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_10_ATTRIBUTE 0x00000AA8
multiline_comment|/* PCIX Read Buffer 11 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_11_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_11_ADDR 0x00000AB0
multiline_comment|/* PCIX Read Buffer 11 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_11_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_11_ATTRIBUTE 0x00000AB8
multiline_comment|/* PCIX Read Buffer 12 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_12_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_12_ADDR 0x00000AC0
multiline_comment|/* PCIX Read Buffer 12 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_12_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_12_ATTRIBUTE 0x00000AC8
multiline_comment|/* PCIX Read Buffer 13 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_13_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_13_ADDR 0x00000AD0
multiline_comment|/* PCIX Read Buffer 13 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_13_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_13_ATTRIBUTE 0x00000AD8
multiline_comment|/* PCIX Read Buffer 14 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_14_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_14_ADDR 0x00000AE0
multiline_comment|/* PCIX Read Buffer 14 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_14_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_14_ATTRIBUTE 0x00000AE8
multiline_comment|/* PCIX Read Buffer 15 Address Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_15_ADDR
mdefine_line|#define PIC_PCIX_READ_BUF_15_ADDR 0x00000AF0
multiline_comment|/* PCIX Read Buffer 15 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_READ_BUF_15_ATTRIBUTE
mdefine_line|#define PIC_PCIX_READ_BUF_15_ATTRIBUTE 0x00000AF8
multiline_comment|/* PCIX Write Buffer 0 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_0_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_0_ADDR 0x00000B00
multiline_comment|/* PCIX Write Buffer 0 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_0_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_0_ATTRIBUTE 0x00000B08
multiline_comment|/* PCIX Write Buffer 0 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_0_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_0_VALID 0x00000B10
multiline_comment|/* PCIX Write Buffer 1 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_1_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_1_ADDR 0x00000B20
multiline_comment|/* PCIX Write Buffer 1 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_1_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_1_ATTRIBUTE 0x00000B28
multiline_comment|/* PCIX Write Buffer 1 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_1_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_1_VALID 0x00000B30
multiline_comment|/* PCIX Write Buffer 2 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_2_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_2_ADDR 0x00000B40
multiline_comment|/* PCIX Write Buffer 2 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_2_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_2_ATTRIBUTE 0x00000B48
multiline_comment|/* PCIX Write Buffer 2 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_2_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_2_VALID 0x00000B50
multiline_comment|/* PCIX Write Buffer 3 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_3_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_3_ADDR 0x00000B60
multiline_comment|/* PCIX Write Buffer 3 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_3_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_3_ATTRIBUTE 0x00000B68
multiline_comment|/* PCIX Write Buffer 3 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_3_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_3_VALID 0x00000B70
multiline_comment|/* PCIX Write Buffer 4 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_4_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_4_ADDR 0x00000B80
multiline_comment|/* PCIX Write Buffer 4 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_4_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_4_ATTRIBUTE 0x00000B88
multiline_comment|/* PCIX Write Buffer 4 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_4_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_4_VALID 0x00000B90
multiline_comment|/* PCIX Write Buffer 5 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_5_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_5_ADDR 0x00000BA0
multiline_comment|/* PCIX Write Buffer 5 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_5_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_5_ATTRIBUTE 0x00000BA8
multiline_comment|/* PCIX Write Buffer 5 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_5_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_5_VALID 0x00000BB0
multiline_comment|/* PCIX Write Buffer 6 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_6_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_6_ADDR 0x00000BC0
multiline_comment|/* PCIX Write Buffer 6 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_6_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_6_ATTRIBUTE 0x00000BC8
multiline_comment|/* PCIX Write Buffer 6 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_6_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_6_VALID 0x00000BD0
multiline_comment|/* PCIX Write Buffer 7 Address Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_7_ADDR
mdefine_line|#define PIC_PCIX_WRITE_BUF_7_ADDR 0x00000BE0
multiline_comment|/* PCIX Write Buffer 7 Attribute Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_7_ATTRIBUTE
mdefine_line|#define PIC_PCIX_WRITE_BUF_7_ATTRIBUTE 0x00000BE8
multiline_comment|/* PCIX Write Buffer 7 Valid Register  -- read-only */
DECL|macro|PIC_PCIX_WRITE_BUF_7_VALID
mdefine_line|#define PIC_PCIX_WRITE_BUF_7_VALID 0x00000BF0
multiline_comment|/*********************************************************************&n; * misc typedefs&n; *&n; */
DECL|typedef|picreg_t
r_typedef
r_uint64
id|picreg_t
suffix:semicolon
multiline_comment|/*********************************************************************&n; * PIC register structures&n; *&n; */
multiline_comment|/*&n; * Identification Register&n; *&n; * The Identification register is a read only register used by the host CPU&n; * during configuration to determine the type of the widget. The format is&n; * the same as defined in IEEE 1149.1 JTAG Device Identification Register.&n; */
DECL|union|pic_id_reg_u
r_typedef
r_union
id|pic_id_reg_u
(brace
DECL|member|pic_id_reg_regval
id|picreg_t
id|pic_id_reg_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|rev_num
id|picreg_t
id|rev_num
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 31:28 */
DECL|member|part_num
id|picreg_t
id|part_num
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 27:12 */
DECL|member|mfg_num
id|picreg_t
id|mfg_num
suffix:colon
l_int|11
suffix:semicolon
multiline_comment|/* 11:1 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0:0 */
DECL|member|pic_id_reg_fld_s
)brace
id|pic_id_reg_fld_s
suffix:semicolon
DECL|typedef|pic_id_reg_u_t
)brace
id|pic_id_reg_u_t
suffix:semicolon
multiline_comment|/*&n; * Status Register&n; *&n; * The status register is a read register which holds status information of the&n; * Bus Subsection.&n; */
DECL|union|pic_stat_reg_u
r_typedef
r_union
id|pic_stat_reg_u
(brace
DECL|member|pic_stat_reg_regval
id|picreg_t
id|pic_stat_reg_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|28
suffix:semicolon
multiline_comment|/* 63:36 */
DECL|member|pci_x_speed
id|picreg_t
id|pci_x_speed
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 35:34 */
DECL|member|pci_x_active
id|picreg_t
id|pci_x_active
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 33:33 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 32:32 */
DECL|member|llp_rec_cnt
id|picreg_t
id|llp_rec_cnt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|member|llp_tx_cnt
id|picreg_t
id|llp_tx_cnt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|rx_credit_cnt
id|picreg_t
id|rx_credit_cnt
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 15:12 */
DECL|member|tx_credit_cnt
id|picreg_t
id|tx_credit_cnt
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 11:8 */
DECL|member|pci_misc_input
id|picreg_t
id|pci_misc_input
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_stat_reg_fld_s
)brace
id|pic_stat_reg_fld_s
suffix:semicolon
DECL|typedef|pic_stat_reg_u_t
)brace
id|pic_stat_reg_u_t
suffix:semicolon
multiline_comment|/*&n; * Upper Address Holding Register Bus Side Errors&n; *&n; * The upper address holding register is a read only register which contains&n; * the upper 16-bits of the address when certain error occurs (see error cases&n; * chapter). Subsequent errors are not logged until the error is cleared. The&n; * last logged value is held until the group is cleared and enabled.&n; */
DECL|union|pic_upper_bus_err_u
r_typedef
r_union
id|pic_upper_bus_err_u
(brace
DECL|member|pic_upper_bus_err_regval
id|picreg_t
id|pic_upper_bus_err_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_upper_bus_err_fld_s
)brace
id|pic_upper_bus_err_fld_s
suffix:semicolon
DECL|typedef|pic_upper_bus_err_u_t
)brace
id|pic_upper_bus_err_u_t
suffix:semicolon
multiline_comment|/*&n; * Lower Address Holding Register Bus Side Errors&n; *&n; * The lower address holding register is a read only register which contains&n; * the address which either can be accessed as a word or double word. Sub-&n; * sequent errors are not logged until the error is cleared. The last logged&n; * value is held until the group is cleared and enabled.&n; */
DECL|union|pic_lower_bus_err_u
r_typedef
r_union
id|pic_lower_bus_err_u
(brace
DECL|member|pic_lower_bus_err_regval
id|picreg_t
id|pic_lower_bus_err_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 63:48 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 47:32 */
DECL|member|low_addr
id|picreg_t
id|low_addr
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 31:0 */
DECL|member|pic_lower_bus_err_fld_s
)brace
id|pic_lower_bus_err_fld_s
suffix:semicolon
DECL|typedef|pic_lower_bus_err_u_t
)brace
id|pic_lower_bus_err_u_t
suffix:semicolon
multiline_comment|/*&n; * Control Register&n; *&n; * The control register is a read/write register which holds control informa-&n; * tion for the bus subsection.&n; */
DECL|union|pic_control_reg_u
r_typedef
r_union
id|pic_control_reg_u
(brace
DECL|member|pic_control_reg_regval
id|picreg_t
id|pic_control_reg_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 31:28 */
DECL|member|rst_pin_n
id|picreg_t
id|rst_pin_n
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 27:24 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|mem_swap
id|picreg_t
id|mem_swap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22:22 */
DECL|member|page_size
id|picreg_t
id|page_size
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 20:17 */
DECL|member|f_bad_pkt
id|picreg_t
id|f_bad_pkt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|llp_xbar_crd
id|picreg_t
id|llp_xbar_crd
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 15:12 */
DECL|member|clr_rllp_cnt
id|picreg_t
id|clr_rllp_cnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|clr_tllp_cnt
id|picreg_t
id|clr_tllp_cnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|sys_end
id|picreg_t
id|sys_end
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 8:6 */
DECL|member|pci_speed
id|picreg_t
id|pci_speed
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 5:4 */
DECL|member|widget_id
id|picreg_t
id|widget_id
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 3:0 */
DECL|member|pic_control_reg_fld_s
)brace
id|pic_control_reg_fld_s
suffix:semicolon
DECL|typedef|pic_control_reg_u_t
)brace
id|pic_control_reg_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI/PCI-X Request Time-out Value Register&n; *&n; * This register contains the reload value for the response timer. The request&n; * timer counts every 960 nS (32 PCI clocks)&n; */
DECL|union|pic_pci_req_to_u
r_typedef
r_union
id|pic_pci_req_to_u
(brace
DECL|member|pic_pci_req_to_regval
id|picreg_t
id|pic_pci_req_to_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* 31:20 */
DECL|member|time_out
id|picreg_t
id|time_out
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* 19:0 */
DECL|member|pic_pci_req_to_fld_s
)brace
id|pic_pci_req_to_fld_s
suffix:semicolon
DECL|typedef|pic_pci_req_to_u_t
)brace
id|pic_pci_req_to_u_t
suffix:semicolon
multiline_comment|/*&n; * Interrupt Destination Upper Address Register&n; *&n; * The interrupt destination upper address register is a read/write register&n; * containing the upper 16-bits of address of the host to which the interrupt&n; * is targeted. In addition the target ID is also contained in this register for&n; * use in Crosstalk mode.&n; */
DECL|union|pic_int_desc_upper_u
r_typedef
r_union
id|pic_int_desc_upper_u
(brace
DECL|member|pic_int_desc_upper_regval
id|picreg_t
id|pic_int_desc_upper_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* 31:20 */
DECL|member|target_id
id|picreg_t
id|target_id
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 19:16 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_int_desc_upper_fld_s
)brace
id|pic_int_desc_upper_fld_s
suffix:semicolon
DECL|typedef|pic_int_desc_upper_u_t
)brace
id|pic_int_desc_upper_u_t
suffix:semicolon
multiline_comment|/*&n; * Interrupt Destination Lower Address Register&n; *&n; * The interrupt destination lower address register is a read/write register&n; * which contains the entire address of the host to which the interrupt is tar-&n; * geted. In addition the target ID is also contained in this register for use in&n; * Crosstalk mode.&n; */
DECL|union|pic_int_desc_lower_u
r_typedef
r_union
id|pic_int_desc_lower_u
(brace
DECL|member|pic_int_desc_lower_regval
id|picreg_t
id|pic_int_desc_lower_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* 63:52 */
DECL|member|target_id
id|picreg_t
id|target_id
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 51:48 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 47:32 */
DECL|member|low_addr
id|picreg_t
id|low_addr
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 31:0 */
DECL|member|pic_int_desc_lower_fld_s
)brace
id|pic_int_desc_lower_fld_s
suffix:semicolon
DECL|typedef|pic_int_desc_lower_u_t
)brace
id|pic_int_desc_lower_u_t
suffix:semicolon
multiline_comment|/*&n; * Command Word Holding Register Bus Side Errors&n; *&n; * The command word holding is a read register that holds the command&n; * word of a Crosstalk packet when errors occur on the link side (see error&n; * chapter). Errors are indicated with error bits in the interrupt status regis-&n; * ter. Subsequent errors are not logged until the interrupt is cleared..&n; */
DECL|union|pic_cmd_word_bus_err_u
r_typedef
r_union
id|pic_cmd_word_bus_err_u
(brace
DECL|member|pic_cmd_word_bus_err_regval
id|picreg_t
id|pic_cmd_word_bus_err_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|didn
id|picreg_t
id|didn
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 31:28 */
DECL|member|sidn
id|picreg_t
id|sidn
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 27:24 */
DECL|member|pactyp
id|picreg_t
id|pactyp
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 23:20 */
DECL|member|tnum
id|picreg_t
id|tnum
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 19:15 */
DECL|member|coherent
id|picreg_t
id|coherent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|ds
id|picreg_t
id|ds
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 13:12 */
DECL|member|gbr
id|picreg_t
id|gbr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|vbpm
id|picreg_t
id|vbpm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|error
id|picreg_t
id|error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|barrier
id|picreg_t
id|barrier
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8:8 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_cmd_word_bus_err_fld_s
)brace
id|pic_cmd_word_bus_err_fld_s
suffix:semicolon
DECL|typedef|pic_cmd_word_bus_err_u_t
)brace
id|pic_cmd_word_bus_err_u_t
suffix:semicolon
multiline_comment|/*&n; * LLP Configuration Register&n; *&n; * This register contains the configuration information for the LLP modules&n; * and is only valid on bus 0 side.&n; */
DECL|union|pic_llp_cfg_u
r_typedef
r_union
id|pic_llp_cfg_u
(brace
DECL|member|pic_llp_cfg_regval
id|picreg_t
id|pic_llp_cfg_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 31:26 */
DECL|member|llp_maxretry
id|picreg_t
id|llp_maxretry
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* 25:16 */
DECL|member|llp_nulltimeout
id|picreg_t
id|llp_nulltimeout
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 15:10 */
DECL|member|llp_maxburst
id|picreg_t
id|llp_maxburst
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* 9:0 */
DECL|member|pic_llp_cfg_fld_s
)brace
id|pic_llp_cfg_fld_s
suffix:semicolon
DECL|typedef|pic_llp_cfg_u_t
)brace
id|pic_llp_cfg_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI/PCI-X Target Flush Register&n; *&n; * When read, this register will return a 0x00 after all previous transfers to&n; * the PCI bus subsection have completed.&n; */
multiline_comment|/*&n; * Command Word Holding Register Link Side Errors&n; *&n; * The command word holding is a read-only register that holds the com-&n; * mand word of a Crosstalk packet when request fifo overflow or unexpect-&n; * ed response errors occur. Errors are indicated with error bits in the&n; * interrupt status register. Subsequent errors are not logged until this inter-&n; * rupt is cleared.&n; */
DECL|union|pic_cmd_word_link_err_u
r_typedef
r_union
id|pic_cmd_word_link_err_u
(brace
DECL|member|pic_cmd_word_link_err_regval
id|picreg_t
id|pic_cmd_word_link_err_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|didn
id|picreg_t
id|didn
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 31:28 */
DECL|member|sidn
id|picreg_t
id|sidn
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 27:24 */
DECL|member|pactyp
id|picreg_t
id|pactyp
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 23:20 */
DECL|member|tnum
id|picreg_t
id|tnum
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 19:15 */
DECL|member|coherent
id|picreg_t
id|coherent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|ds
id|picreg_t
id|ds
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 13:12 */
DECL|member|gbr
id|picreg_t
id|gbr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|vbpm
id|picreg_t
id|vbpm
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|error
id|picreg_t
id|error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|barrier
id|picreg_t
id|barrier
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8:8 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_cmd_word_link_err_fld_s
)brace
id|pic_cmd_word_link_err_fld_s
suffix:semicolon
DECL|typedef|pic_cmd_word_link_err_u_t
)brace
id|pic_cmd_word_link_err_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Response Buffer Error Upper Address Holding Reg&n; *&n; * The response buffer error upper address holding register is a read only&n; * register which contains the upper 16-bits of the address when error asso-&n; * ciated with response buffer entries occur. Subsequent errors are not&n; * logged until the interrupt is cleared.&n; */
DECL|union|pic_pci_rbuf_err_upper_u
r_typedef
r_union
id|pic_pci_rbuf_err_upper_u
(brace
DECL|member|pic_pci_rbuf_err_upper_regval
id|picreg_t
id|pic_pci_rbuf_err_upper_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* 31:23 */
DECL|member|dev_num
id|picreg_t
id|dev_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 22:20 */
DECL|member|buff_num
id|picreg_t
id|buff_num
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 19:16 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_pci_rbuf_err_upper_fld_s
)brace
id|pic_pci_rbuf_err_upper_fld_s
suffix:semicolon
DECL|typedef|pic_pci_rbuf_err_upper_u_t
)brace
id|pic_pci_rbuf_err_upper_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Response Buffer Error Lower Address Holding Reg&n; *&n; * The response buffer error lower address holding register is a read only&n; * register which contains the address of the error associated with response&n; * buffer entries. Subsequent errors are not logged until the interrupt is&n; * cleared.&n; */
DECL|union|pic_pci_rbuf_err_lower_u
r_typedef
r_union
id|pic_pci_rbuf_err_lower_u
(brace
DECL|member|pic_pci_rbuf_err_lower_regval
id|picreg_t
id|pic_pci_rbuf_err_lower_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* 63:55 */
DECL|member|dev_num
id|picreg_t
id|dev_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 54:52 */
DECL|member|buff_num
id|picreg_t
id|buff_num
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 51:48 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 47:32 */
DECL|member|low_addr
id|picreg_t
id|low_addr
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 31:0 */
DECL|member|pic_pci_rbuf_err_lower_fld_s
)brace
id|pic_pci_rbuf_err_lower_fld_s
suffix:semicolon
DECL|typedef|pic_pci_rbuf_err_lower_u_t
)brace
id|pic_pci_rbuf_err_lower_u_t
suffix:semicolon
multiline_comment|/*&n; * Test Pin Control Register&n; *&n; * This register selects the output function and value to the four test pins on&n; * the PIC .&n; */
DECL|union|pic_test_pin_cntl_u
r_typedef
r_union
id|pic_test_pin_cntl_u
(brace
DECL|member|pic_test_pin_cntl_regval
id|picreg_t
id|pic_test_pin_cntl_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|member|tdata_out
id|picreg_t
id|tdata_out
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|sel_tpin_7
id|picreg_t
id|sel_tpin_7
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 15:14 */
DECL|member|sel_tpin_6
id|picreg_t
id|sel_tpin_6
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 13:12 */
DECL|member|sel_tpin_5
id|picreg_t
id|sel_tpin_5
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 11:10 */
DECL|member|sel_tpin_4
id|picreg_t
id|sel_tpin_4
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 9:8 */
DECL|member|sel_tpin_3
id|picreg_t
id|sel_tpin_3
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 7:6 */
DECL|member|sel_tpin_2
id|picreg_t
id|sel_tpin_2
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 5:4 */
DECL|member|sel_tpin_1
id|picreg_t
id|sel_tpin_1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 3:2 */
DECL|member|sel_tpin_0
id|picreg_t
id|sel_tpin_0
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 1:0 */
DECL|member|pic_test_pin_cntl_fld_s
)brace
id|pic_test_pin_cntl_fld_s
suffix:semicolon
DECL|typedef|pic_test_pin_cntl_u_t
)brace
id|pic_test_pin_cntl_u_t
suffix:semicolon
multiline_comment|/*&n; * Address Holding Register Link Side Errors&n; *&n; * The address holding register is a read only register which contains the ad-&n; * dress which either can be accessed as a word or double word. Subsequent&n; * errors are not logged until the error is cleared. The last logged value is&n; * held until the group is cleared and enabled.&n; */
DECL|union|pic_p_addr_lkerr_u
r_typedef
r_union
id|pic_p_addr_lkerr_u
(brace
DECL|member|pic_p_addr_lkerr_regval
id|picreg_t
id|pic_p_addr_lkerr_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 63:48 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 47:32 */
DECL|member|low_addr
id|picreg_t
id|low_addr
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 31:0 */
DECL|member|pic_p_addr_lkerr_fld_s
)brace
id|pic_p_addr_lkerr_fld_s
suffix:semicolon
DECL|typedef|pic_p_addr_lkerr_u_t
)brace
id|pic_p_addr_lkerr_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Direct Mapping Register&n; *&n; * This register is used to relocate a 2 GByte region for PCI to Crosstalk&n; * transfers.&n; */
DECL|union|pic_p_dir_map_u
r_typedef
r_union
id|pic_p_dir_map_u
(brace
DECL|member|pic_p_dir_map_regval
id|picreg_t
id|pic_p_dir_map_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|member|dir_w_id
id|picreg_t
id|dir_w_id
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 23:20 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 19:18 */
DECL|member|dir_add512
id|picreg_t
id|dir_add512
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17:17 */
DECL|member|dir_off
id|picreg_t
id|dir_off
suffix:colon
l_int|17
suffix:semicolon
multiline_comment|/* 16:0 */
DECL|member|pic_p_dir_map_fld_s
)brace
id|pic_p_dir_map_fld_s
suffix:semicolon
DECL|typedef|pic_p_dir_map_u_t
)brace
id|pic_p_dir_map_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Page Map Fault Address Register&n; *&n; * This register contains the address and device number when a page map&n; * fault occurred.&n; */
DECL|union|pic_p_map_fault_u
r_typedef
r_union
id|pic_p_map_fault_u
(brace
DECL|member|pic_p_map_fault_regval
id|picreg_t
id|pic_p_map_fault_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* 31:22 */
DECL|member|pci_addr
id|picreg_t
id|pci_addr
suffix:colon
l_int|18
suffix:semicolon
multiline_comment|/* 21:4 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 3:3 */
DECL|member|pci_dev_num
id|picreg_t
id|pci_dev_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 2:0 */
DECL|member|pic_p_map_fault_fld_s
)brace
id|pic_p_map_fault_fld_s
suffix:semicolon
DECL|typedef|pic_p_map_fault_u_t
)brace
id|pic_p_map_fault_u_t
suffix:semicolon
multiline_comment|/*&n; * Arbitration Register&n; *&n; * This register defines the priority and bus time out timing in PCI bus arbi-&n; * tration.&n; */
DECL|union|pic_p_arb_u
r_typedef
r_union
id|pic_p_arb_u
(brace
DECL|member|pic_p_arb_regval
id|picreg_t
id|pic_p_arb_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|member|dev_broke
id|picreg_t
id|dev_broke
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 23:20 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 19:18 */
DECL|member|req_wait_tick
id|picreg_t
id|req_wait_tick
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 17:16 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 15:12 */
DECL|member|req_wait_en
id|picreg_t
id|req_wait_en
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 11:8 */
DECL|member|disarb
id|picreg_t
id|disarb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 7:7 */
DECL|member|freeze_gnt
id|picreg_t
id|freeze_gnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 6:6 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 5:5 */
DECL|member|en_bridge_hi
id|picreg_t
id|en_bridge_hi
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 4:3 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 2:2 */
DECL|member|en_bridge_lo
id|picreg_t
id|en_bridge_lo
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 1:0 */
DECL|member|pic_p_arb_fld_s
)brace
id|pic_p_arb_fld_s
suffix:semicolon
DECL|typedef|pic_p_arb_u_t
)brace
id|pic_p_arb_u_t
suffix:semicolon
multiline_comment|/*&n; * Internal Ram Parity Error Register&n; *&n; * This register logs information about parity errors on internal ram access.&n; */
DECL|union|pic_p_ram_perr_u
r_typedef
r_union
id|pic_p_ram_perr_u
(brace
DECL|member|pic_p_ram_perr_regval
id|picreg_t
id|pic_p_ram_perr_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 63:58 */
DECL|member|ate_err_addr
id|picreg_t
id|ate_err_addr
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* 57:48 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* 47:41 */
DECL|member|rd_resp_err_addr
id|picreg_t
id|rd_resp_err_addr
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* 40:32 */
DECL|member|wrt_resp_err_addr
id|picreg_t
id|wrt_resp_err_addr
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 23:22 */
DECL|member|ate_err
id|picreg_t
id|ate_err
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|rd_resp_err
id|picreg_t
id|rd_resp_err
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|wrt_resp_err
id|picreg_t
id|wrt_resp_err
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|dbe_ate
id|picreg_t
id|dbe_ate
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 18:16 */
DECL|member|dbe_rd
id|picreg_t
id|dbe_rd
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 15:8 */
DECL|member|dbe_wrt
id|picreg_t
id|dbe_wrt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_p_ram_perr_fld_s
)brace
id|pic_p_ram_perr_fld_s
suffix:semicolon
DECL|typedef|pic_p_ram_perr_u_t
)brace
id|pic_p_ram_perr_u_t
suffix:semicolon
multiline_comment|/*&n; * Time-out Register&n; *&n; * This register determines retry hold off and max retries allowed for PIO&n; * accesses to PCI/PCI-X.&n; */
DECL|union|pic_p_bus_timeout_u
r_typedef
r_union
id|pic_p_bus_timeout_u
(brace
DECL|member|pic_p_bus_timeout_regval
id|picreg_t
id|pic_p_bus_timeout_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|11
suffix:semicolon
multiline_comment|/* 31:21 */
DECL|member|pci_retry_hld
id|picreg_t
id|pci_retry_hld
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 20:16 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 15:10 */
DECL|member|pci_retry_cnt
id|picreg_t
id|pci_retry_cnt
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* 9:0 */
DECL|member|pic_p_bus_timeout_fld_s
)brace
id|pic_p_bus_timeout_fld_s
suffix:semicolon
DECL|typedef|pic_p_bus_timeout_u_t
)brace
id|pic_p_bus_timeout_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI/PCI-X Type 1 Configuration Register&n; *&n; * This register is use during accesses to the PCI/PCI-X type 1 configuration&n; * space. The bits in this register are used to supplement the address during&n; * the configuration cycle to select the correct secondary bus and device.&n; */
DECL|union|pic_type1_cfg_u
r_typedef
r_union
id|pic_type1_cfg_u
(brace
DECL|member|pic_type1_cfg_regval
id|picreg_t
id|pic_type1_cfg_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|member|bus_num
id|picreg_t
id|bus_num
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|dev_num
id|picreg_t
id|dev_num
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 15:11 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|11
suffix:semicolon
multiline_comment|/* 10:0 */
DECL|member|pic_type1_cfg_fld_s
)brace
id|pic_type1_cfg_fld_s
suffix:semicolon
DECL|typedef|pic_type1_cfg_u_t
)brace
id|pic_type1_cfg_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Bus Error Upper Address Holding Register&n; *&n; * This register holds the value of the upper address on the PCI Bus when an&n; * error occurs.&n; */
DECL|union|pic_p_pci_err_upper_u
r_typedef
r_union
id|pic_p_pci_err_upper_u
(brace
DECL|member|pic_p_pci_err_upper_regval
id|picreg_t
id|pic_p_pci_err_upper_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 31:28 */
DECL|member|pci_xtalk_did
id|picreg_t
id|pci_xtalk_did
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 27:24 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 23:22 */
DECL|member|pci_dac
id|picreg_t
id|pci_dac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|pci_dev_master
id|picreg_t
id|pci_dev_master
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|pci_vdev
id|picreg_t
id|pci_vdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|pci_dev_num
id|picreg_t
id|pci_dev_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 18:16 */
DECL|member|pci_uaddr_err
id|picreg_t
id|pci_uaddr_err
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_p_pci_err_upper_fld_s
)brace
id|pic_p_pci_err_upper_fld_s
suffix:semicolon
DECL|typedef|pic_p_pci_err_upper_u_t
)brace
id|pic_p_pci_err_upper_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Bus Error Lower Address Holding Register&n; *&n; * This register holds the value of the lower address on the PCI Bus when an&n; * error occurs.&n; */
DECL|union|pic_p_pci_err_lower_u
r_typedef
r_union
id|pic_p_pci_err_lower_u
(brace
DECL|member|pic_p_pci_err_lower_regval
id|picreg_t
id|pic_p_pci_err_lower_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 63:60 */
DECL|member|pci_xtalk_did
id|picreg_t
id|pci_xtalk_did
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 59:56 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 55:54 */
DECL|member|pci_dac
id|picreg_t
id|pci_dac
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 53:53 */
DECL|member|pci_dev_master
id|picreg_t
id|pci_dev_master
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 52:52 */
DECL|member|pci_vdev
id|picreg_t
id|pci_vdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 51:51 */
DECL|member|pci_dev_num
id|picreg_t
id|pci_dev_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 50:48 */
DECL|member|pci_uaddr_err
id|picreg_t
id|pci_uaddr_err
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 47:32 */
DECL|member|pci_laddr_err
id|picreg_t
id|pci_laddr_err
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 31:0 */
DECL|member|pic_p_pci_err_lower_fld_s
)brace
id|pic_p_pci_err_lower_fld_s
suffix:semicolon
DECL|typedef|pic_p_pci_err_lower_u_t
)brace
id|pic_p_pci_err_lower_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Error Address Register&n; *&n; * This register contains the address on the PCI-X bus when an error oc-&n; * curred.&n; */
DECL|union|pic_p_pcix_err_addr_u
r_typedef
r_union
id|pic_p_pcix_err_addr_u
(brace
DECL|member|pic_p_pcix_err_addr_regval
id|picreg_t
id|pic_p_pcix_err_addr_regval
suffix:semicolon
r_struct
(brace
DECL|member|pcix_err_addr
id|picreg_t
id|pcix_err_addr
suffix:colon
l_int|64
suffix:semicolon
multiline_comment|/* 63:0 */
DECL|member|pic_p_pcix_err_addr_fld_s
)brace
id|pic_p_pcix_err_addr_fld_s
suffix:semicolon
DECL|typedef|pic_p_pcix_err_addr_u_t
)brace
id|pic_p_pcix_err_addr_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Error Attribute Register&n; *&n; * This register contains the attribute data on the PCI-X bus when an error&n; * occurred.&n; */
DECL|union|pic_p_pcix_err_attr_u
r_typedef
r_union
id|pic_p_pcix_err_attr_u
(brace
DECL|member|pic_p_pcix_err_attr_regval
id|picreg_t
id|pic_p_pcix_err_attr_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 63:48 */
DECL|member|bus_cmd
id|picreg_t
id|bus_cmd
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 47:44 */
DECL|member|byte_cnt
id|picreg_t
id|byte_cnt
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* 43:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|ns
id|picreg_t
id|ns
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|ro
id|picreg_t
id|ro
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|tag
id|picreg_t
id|tag
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 28:24 */
DECL|member|bus_num
id|picreg_t
id|bus_num
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|dev_num
id|picreg_t
id|dev_num
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 15:11 */
DECL|member|fun_num
id|picreg_t
id|fun_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 10:8 */
DECL|member|l_byte_cnt
id|picreg_t
id|l_byte_cnt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_p_pcix_err_attr_fld_s
)brace
id|pic_p_pcix_err_attr_fld_s
suffix:semicolon
DECL|typedef|pic_p_pcix_err_attr_u_t
)brace
id|pic_p_pcix_err_attr_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Error Data Register&n; *&n; * This register contains the Data on the PCI-X bus when an error occurred.&n; */
DECL|union|pic_p_pcix_err_data_u
r_typedef
r_union
id|pic_p_pcix_err_data_u
(brace
DECL|member|pic_p_pcix_err_data_regval
id|picreg_t
id|pic_p_pcix_err_data_regval
suffix:semicolon
r_struct
(brace
DECL|member|pcix_err_data
id|picreg_t
id|pcix_err_data
suffix:colon
l_int|64
suffix:semicolon
multiline_comment|/* 63:0 */
DECL|member|pic_p_pcix_err_data_fld_s
)brace
id|pic_p_pcix_err_data_fld_s
suffix:semicolon
DECL|typedef|pic_p_pcix_err_data_u_t
)brace
id|pic_p_pcix_err_data_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Read Request Timeout Error Register&n; *&n; * This register contains a pointer into the PCI-X read data structure.&n; */
DECL|union|pic_p_pcix_read_req_to_u
r_typedef
r_union
id|pic_p_pcix_read_req_to_u
(brace
DECL|member|pic_p_pcix_read_req_to_regval
id|picreg_t
id|pic_p_pcix_read_req_to_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|55
suffix:semicolon
multiline_comment|/* 63:9 */
DECL|member|rd_buff_loc
id|picreg_t
id|rd_buff_loc
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 8:4 */
DECL|member|rd_buff_struct
id|picreg_t
id|rd_buff_struct
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 3:0 */
DECL|member|pic_p_pcix_read_req_to_fld_s
)brace
id|pic_p_pcix_read_req_to_fld_s
suffix:semicolon
DECL|typedef|pic_p_pcix_read_req_to_u_t
)brace
id|pic_p_pcix_read_req_to_u_t
suffix:semicolon
multiline_comment|/*&n; * INT_STATUS Register&n; *&n; * This is the current interrupt status register which maintains the current&n; * status of all the interrupting devices which generated a n interrupt. This&n; * register is read only and all the bits are active high. A high bit at&n; * INT_STATE means the corresponding INT_N pin has been asserted&n; * (low).&n; */
DECL|union|pic_p_int_status_u
r_typedef
r_union
id|pic_p_int_status_u
(brace
DECL|member|pic_p_int_status_regval
id|picreg_t
id|pic_p_int_status_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|22
suffix:semicolon
multiline_comment|/* 63:42 */
DECL|member|int_ram_perr
id|picreg_t
id|int_ram_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 41:41 */
DECL|member|bus_arb_broke
id|picreg_t
id|bus_arb_broke
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 40:40 */
DECL|member|pci_x_req_tout
id|picreg_t
id|pci_x_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 39:39 */
DECL|member|pci_x_tabort
id|picreg_t
id|pci_x_tabort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 38:38 */
DECL|member|pci_x_perr
id|picreg_t
id|pci_x_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 37:37 */
DECL|member|pci_x_serr
id|picreg_t
id|pci_x_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 36:36 */
DECL|member|pci_x_mretry
id|picreg_t
id|pci_x_mretry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 35:35 */
DECL|member|pci_x_mtout
id|picreg_t
id|pci_x_mtout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 34:34 */
DECL|member|pci_x_da_parity
id|picreg_t
id|pci_x_da_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 33:33 */
DECL|member|pci_x_ad_parity
id|picreg_t
id|pci_x_ad_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 32:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|pmu_page_fault
id|picreg_t
id|pmu_page_fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|unexpected_resp
id|picreg_t
id|unexpected_resp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|bad_xresp_packet
id|picreg_t
id|bad_xresp_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|bad_xreq_packet
id|picreg_t
id|bad_xreq_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|resp_xtalk_error
id|picreg_t
id|resp_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26:26 */
DECL|member|req_xtalk_error
id|picreg_t
id|req_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25:25 */
DECL|member|invalid_access
id|picreg_t
id|invalid_access
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|unsupported_xop
id|picreg_t
id|unsupported_xop
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|xreq_fifo_oflow
id|picreg_t
id|xreq_fifo_oflow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22:22 */
DECL|member|llp_rec_snerror
id|picreg_t
id|llp_rec_snerror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|llp_rec_cberror
id|picreg_t
id|llp_rec_cberror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|llp_rcty
id|picreg_t
id|llp_rcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|llp_tx_retry
id|picreg_t
id|llp_tx_retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18:18 */
DECL|member|llp_tcty
id|picreg_t
id|llp_tcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17:17 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|pci_abort
id|picreg_t
id|pci_abort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|pci_parity
id|picreg_t
id|pci_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|pci_serr
id|picreg_t
id|pci_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 13:13 */
DECL|member|pci_perr
id|picreg_t
id|pci_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|pci_master_tout
id|picreg_t
id|pci_master_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|pci_retry_cnt
id|picreg_t
id|pci_retry_cnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|xread_req_tout
id|picreg_t
id|xread_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8:8 */
DECL|member|int_state
id|picreg_t
id|int_state
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_p_int_status_fld_s
)brace
id|pic_p_int_status_fld_s
suffix:semicolon
DECL|typedef|pic_p_int_status_u_t
)brace
id|pic_p_int_status_u_t
suffix:semicolon
multiline_comment|/*&n; * Interrupt Enable Register&n; *&n; * This register enables the reporting of interrupt to the host. Each bit in this&n; * register corresponds to the same bit in Interrupt Status register. All bits&n; * are zero after reset.&n; */
DECL|union|pic_p_int_enable_u
r_typedef
r_union
id|pic_p_int_enable_u
(brace
DECL|member|pic_p_int_enable_regval
id|picreg_t
id|pic_p_int_enable_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|22
suffix:semicolon
multiline_comment|/* 63:42 */
DECL|member|en_int_ram_perr
id|picreg_t
id|en_int_ram_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 41:41 */
DECL|member|en_bus_arb_broke
id|picreg_t
id|en_bus_arb_broke
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 40:40 */
DECL|member|en_pci_x_req_tout
id|picreg_t
id|en_pci_x_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 39:39 */
DECL|member|en_pci_x_tabort
id|picreg_t
id|en_pci_x_tabort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 38:38 */
DECL|member|en_pci_x_perr
id|picreg_t
id|en_pci_x_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 37:37 */
DECL|member|en_pci_x_serr
id|picreg_t
id|en_pci_x_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 36:36 */
DECL|member|en_pci_x_mretry
id|picreg_t
id|en_pci_x_mretry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 35:35 */
DECL|member|en_pci_x_mtout
id|picreg_t
id|en_pci_x_mtout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 34:34 */
DECL|member|en_pci_x_da_parity
id|picreg_t
id|en_pci_x_da_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 33:33 */
DECL|member|en_pci_x_ad_parity
id|picreg_t
id|en_pci_x_ad_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 32:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|en_pmu_page_fault
id|picreg_t
id|en_pmu_page_fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|en_unexpected_resp
id|picreg_t
id|en_unexpected_resp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|en_bad_xresp_packet
id|picreg_t
id|en_bad_xresp_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|en_bad_xreq_packet
id|picreg_t
id|en_bad_xreq_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|en_resp_xtalk_error
id|picreg_t
id|en_resp_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26:26 */
DECL|member|en_req_xtalk_error
id|picreg_t
id|en_req_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25:25 */
DECL|member|en_invalid_access
id|picreg_t
id|en_invalid_access
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|en_unsupported_xop
id|picreg_t
id|en_unsupported_xop
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|en_xreq_fifo_oflow
id|picreg_t
id|en_xreq_fifo_oflow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22:22 */
DECL|member|en_llp_rec_snerror
id|picreg_t
id|en_llp_rec_snerror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|en_llp_rec_cberror
id|picreg_t
id|en_llp_rec_cberror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|en_llp_rcty
id|picreg_t
id|en_llp_rcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|en_llp_tx_retry
id|picreg_t
id|en_llp_tx_retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18:18 */
DECL|member|en_llp_tcty
id|picreg_t
id|en_llp_tcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17:17 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|en_pci_abort
id|picreg_t
id|en_pci_abort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|en_pci_parity
id|picreg_t
id|en_pci_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|en_pci_serr
id|picreg_t
id|en_pci_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 13:13 */
DECL|member|en_pci_perr
id|picreg_t
id|en_pci_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|en_pci_master_tout
id|picreg_t
id|en_pci_master_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|en_pci_retry_cnt
id|picreg_t
id|en_pci_retry_cnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|en_xread_req_tout
id|picreg_t
id|en_xread_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8:8 */
DECL|member|en_int_state
id|picreg_t
id|en_int_state
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_p_int_enable_fld_s
)brace
id|pic_p_int_enable_fld_s
suffix:semicolon
DECL|typedef|pic_p_int_enable_u_t
)brace
id|pic_p_int_enable_u_t
suffix:semicolon
multiline_comment|/*&n; * Reset Interrupt Register&n; *&n; * A write of a &quot;1&quot; clears the bit and rearms the error registers. Writes also&n; * clear the error view register.&n; */
DECL|union|pic_p_int_rst_u
r_typedef
r_union
id|pic_p_int_rst_u
(brace
DECL|member|pic_p_int_rst_regval
id|picreg_t
id|pic_p_int_rst_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|22
suffix:semicolon
multiline_comment|/* 63:42 */
DECL|member|logv_int_ram_perr
id|picreg_t
id|logv_int_ram_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 41:41 */
DECL|member|logv_bus_arb_broke
id|picreg_t
id|logv_bus_arb_broke
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 40:40 */
DECL|member|logv_pci_x_req_tout
id|picreg_t
id|logv_pci_x_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 39:39 */
DECL|member|logv_pci_x_tabort
id|picreg_t
id|logv_pci_x_tabort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 38:38 */
DECL|member|logv_pci_x_perr
id|picreg_t
id|logv_pci_x_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 37:37 */
DECL|member|logv_pci_x_serr
id|picreg_t
id|logv_pci_x_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 36:36 */
DECL|member|logv_pci_x_mretry
id|picreg_t
id|logv_pci_x_mretry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 35:35 */
DECL|member|logv_pci_x_mtout
id|picreg_t
id|logv_pci_x_mtout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 34:34 */
DECL|member|logv_pci_x_da_parity
id|picreg_t
id|logv_pci_x_da_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 33:33 */
DECL|member|logv_pci_x_ad_parity
id|picreg_t
id|logv_pci_x_ad_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 32:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|logv_pmu_page_fault
id|picreg_t
id|logv_pmu_page_fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|logv_unexpected_resp
id|picreg_t
id|logv_unexpected_resp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|logv_bad_xresp_packet
id|picreg_t
id|logv_bad_xresp_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|logv_bad_xreq_packet
id|picreg_t
id|logv_bad_xreq_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|logv_resp_xtalk_error
id|picreg_t
id|logv_resp_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26:26 */
DECL|member|logv_req_xtalk_error
id|picreg_t
id|logv_req_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25:25 */
DECL|member|logv_invalid_access
id|picreg_t
id|logv_invalid_access
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|logv_unsupported_xop
id|picreg_t
id|logv_unsupported_xop
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|logv_xreq_fifo_oflow
id|picreg_t
id|logv_xreq_fifo_oflow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22:22 */
DECL|member|logv_llp_rec_snerror
id|picreg_t
id|logv_llp_rec_snerror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|logv_llp_rec_cberror
id|picreg_t
id|logv_llp_rec_cberror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|logv_llp_rcty
id|picreg_t
id|logv_llp_rcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|logv_llp_tx_retry
id|picreg_t
id|logv_llp_tx_retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18:18 */
DECL|member|logv_llp_tcty
id|picreg_t
id|logv_llp_tcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17:17 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|logv_pci_abort
id|picreg_t
id|logv_pci_abort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|logv_pci_parity
id|picreg_t
id|logv_pci_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|logv_pci_serr
id|picreg_t
id|logv_pci_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 13:13 */
DECL|member|logv_pci_perr
id|picreg_t
id|logv_pci_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|logv_pci_master_tout
id|picreg_t
id|logv_pci_master_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|logv_pci_retry_cnt
id|picreg_t
id|logv_pci_retry_cnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|logv_xread_req_tout
id|picreg_t
id|logv_xread_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 8:7 */
DECL|member|multi_clr
id|picreg_t
id|multi_clr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 6:6 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 5:0 */
DECL|member|pic_p_int_rst_fld_s
)brace
id|pic_p_int_rst_fld_s
suffix:semicolon
DECL|typedef|pic_p_int_rst_u_t
)brace
id|pic_p_int_rst_u_t
suffix:semicolon
multiline_comment|/*&n; * Interrupt Mode Register&n; *&n; * This register defines the interrupting mode of the INT_N pins.&n; */
DECL|union|pic_p_int_mode_u
r_typedef
r_union
id|pic_p_int_mode_u
(brace
DECL|member|pic_p_int_mode_regval
id|picreg_t
id|pic_p_int_mode_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* 31:8 */
DECL|member|en_clr_pkt
id|picreg_t
id|en_clr_pkt
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_p_int_mode_fld_s
)brace
id|pic_p_int_mode_fld_s
suffix:semicolon
DECL|typedef|pic_p_int_mode_u_t
)brace
id|pic_p_int_mode_u_t
suffix:semicolon
multiline_comment|/*&n; * Interrupt Device Select Register&n; *&n; * This register associates interrupt pins with devices thus allowing buffer&n; * management (flushing) when a device interrupt occurs.&n; */
DECL|union|pic_p_int_device_u
r_typedef
r_union
id|pic_p_int_device_u
(brace
DECL|member|pic_p_int_device_regval
id|picreg_t
id|pic_p_int_device_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 31:24 */
DECL|member|int7_dev
id|picreg_t
id|int7_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 23:21 */
DECL|member|int6_dev
id|picreg_t
id|int6_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 20:18 */
DECL|member|int5_dev
id|picreg_t
id|int5_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 17:15 */
DECL|member|int4_dev
id|picreg_t
id|int4_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 14:12 */
DECL|member|int3_dev
id|picreg_t
id|int3_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 11:9 */
DECL|member|int2_dev
id|picreg_t
id|int2_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 8:6 */
DECL|member|int1_dev
id|picreg_t
id|int1_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 5:3 */
DECL|member|int0_dev
id|picreg_t
id|int0_dev
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 2:0 */
DECL|member|pic_p_int_device_fld_s
)brace
id|pic_p_int_device_fld_s
suffix:semicolon
DECL|typedef|pic_p_int_device_u_t
)brace
id|pic_p_int_device_u_t
suffix:semicolon
multiline_comment|/*&n; * Host Error Interrupt Field Register&n; *&n; * This register tells which bit location in the host&squot;s Interrupt Status register&n; * to set or reset when any error condition happens.&n; */
DECL|union|pic_p_int_host_err_u
r_typedef
r_union
id|pic_p_int_host_err_u
(brace
DECL|member|pic_p_int_host_err_regval
id|picreg_t
id|pic_p_int_host_err_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* 31:8 */
DECL|member|bridge_err_fld
id|picreg_t
id|bridge_err_fld
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_p_int_host_err_fld_s
)brace
id|pic_p_int_host_err_fld_s
suffix:semicolon
DECL|typedef|pic_p_int_host_err_u_t
)brace
id|pic_p_int_host_err_u_t
suffix:semicolon
multiline_comment|/*&n; * Interrupt (x) Host Address Register&n; *&n; * This register allow different host address to be assigned to each interrupt&n; * pin and the bit in the host.&n; */
DECL|union|pic_p_int_addr_u
r_typedef
r_union
id|pic_p_int_addr_u
(brace
DECL|member|pic_p_int_addr_regval
id|picreg_t
id|pic_p_int_addr_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 63:56 */
DECL|member|int_fld
id|picreg_t
id|int_fld
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 55:48 */
DECL|member|int_addr
id|picreg_t
id|int_addr
suffix:colon
l_int|48
suffix:semicolon
multiline_comment|/* 47:0 */
DECL|member|pic_p_int_addr_fld_s
)brace
id|pic_p_int_addr_fld_s
suffix:semicolon
DECL|typedef|pic_p_int_addr_u_t
)brace
id|pic_p_int_addr_u_t
suffix:semicolon
multiline_comment|/*&n; * Error Interrupt View Register&n; *&n; * This register contains the view of which interrupt occur even if they are&n; * not currently enabled. The group clear is used to clear these bits just like&n; * the interrupt status register bits.&n; */
DECL|union|pic_p_err_int_view_u
r_typedef
r_union
id|pic_p_err_int_view_u
(brace
DECL|member|pic_p_err_int_view_regval
id|picreg_t
id|pic_p_err_int_view_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|22
suffix:semicolon
multiline_comment|/* 63:42 */
DECL|member|int_ram_perr
id|picreg_t
id|int_ram_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 41:41 */
DECL|member|bus_arb_broke
id|picreg_t
id|bus_arb_broke
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 40:40 */
DECL|member|pci_x_req_tout
id|picreg_t
id|pci_x_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 39:39 */
DECL|member|pci_x_tabort
id|picreg_t
id|pci_x_tabort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 38:38 */
DECL|member|pci_x_perr
id|picreg_t
id|pci_x_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 37:37 */
DECL|member|pci_x_serr
id|picreg_t
id|pci_x_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 36:36 */
DECL|member|pci_x_mretry
id|picreg_t
id|pci_x_mretry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 35:35 */
DECL|member|pci_x_mtout
id|picreg_t
id|pci_x_mtout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 34:34 */
DECL|member|pci_x_da_parity
id|picreg_t
id|pci_x_da_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 33:33 */
DECL|member|pci_x_ad_parity
id|picreg_t
id|pci_x_ad_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 32:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|pmu_page_fault
id|picreg_t
id|pmu_page_fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|unexpected_resp
id|picreg_t
id|unexpected_resp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|bad_xresp_packet
id|picreg_t
id|bad_xresp_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|bad_xreq_packet
id|picreg_t
id|bad_xreq_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|resp_xtalk_error
id|picreg_t
id|resp_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26:26 */
DECL|member|req_xtalk_error
id|picreg_t
id|req_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25:25 */
DECL|member|invalid_access
id|picreg_t
id|invalid_access
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|unsupported_xop
id|picreg_t
id|unsupported_xop
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|xreq_fifo_oflow
id|picreg_t
id|xreq_fifo_oflow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22:22 */
DECL|member|llp_rec_snerror
id|picreg_t
id|llp_rec_snerror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|llp_rec_cberror
id|picreg_t
id|llp_rec_cberror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|llp_rcty
id|picreg_t
id|llp_rcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|llp_tx_retry
id|picreg_t
id|llp_tx_retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18:18 */
DECL|member|llp_tcty
id|picreg_t
id|llp_tcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17:17 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|pci_abort
id|picreg_t
id|pci_abort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|pci_parity
id|picreg_t
id|pci_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|pci_serr
id|picreg_t
id|pci_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 13:13 */
DECL|member|pci_perr
id|picreg_t
id|pci_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|pci_master_tout
id|picreg_t
id|pci_master_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|pci_retry_cnt
id|picreg_t
id|pci_retry_cnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|xread_req_tout
id|picreg_t
id|xread_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* 8:0 */
DECL|member|pic_p_err_int_view_fld_s
)brace
id|pic_p_err_int_view_fld_s
suffix:semicolon
DECL|typedef|pic_p_err_int_view_u_t
)brace
id|pic_p_err_int_view_u_t
suffix:semicolon
multiline_comment|/*&n; * Multiple Interrupt Register&n; *&n; * This register indicates if any interrupt occurs more than once without be-&n; * ing cleared.&n; */
DECL|union|pic_p_mult_int_u
r_typedef
r_union
id|pic_p_mult_int_u
(brace
DECL|member|pic_p_mult_int_regval
id|picreg_t
id|pic_p_mult_int_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|22
suffix:semicolon
multiline_comment|/* 63:42 */
DECL|member|int_ram_perr
id|picreg_t
id|int_ram_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 41:41 */
DECL|member|bus_arb_broke
id|picreg_t
id|bus_arb_broke
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 40:40 */
DECL|member|pci_x_req_tout
id|picreg_t
id|pci_x_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 39:39 */
DECL|member|pci_x_tabort
id|picreg_t
id|pci_x_tabort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 38:38 */
DECL|member|pci_x_perr
id|picreg_t
id|pci_x_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 37:37 */
DECL|member|pci_x_serr
id|picreg_t
id|pci_x_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 36:36 */
DECL|member|pci_x_mretry
id|picreg_t
id|pci_x_mretry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 35:35 */
DECL|member|pci_x_mtout
id|picreg_t
id|pci_x_mtout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 34:34 */
DECL|member|pci_x_da_parity
id|picreg_t
id|pci_x_da_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 33:33 */
DECL|member|pci_x_ad_parity
id|picreg_t
id|pci_x_ad_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 32:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|pmu_page_fault
id|picreg_t
id|pmu_page_fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|unexpected_resp
id|picreg_t
id|unexpected_resp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|bad_xresp_packet
id|picreg_t
id|bad_xresp_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|bad_xreq_packet
id|picreg_t
id|bad_xreq_packet
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|resp_xtalk_error
id|picreg_t
id|resp_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26:26 */
DECL|member|req_xtalk_error
id|picreg_t
id|req_xtalk_error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25:25 */
DECL|member|invalid_access
id|picreg_t
id|invalid_access
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|unsupported_xop
id|picreg_t
id|unsupported_xop
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|xreq_fifo_oflow
id|picreg_t
id|xreq_fifo_oflow
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22:22 */
DECL|member|llp_rec_snerror
id|picreg_t
id|llp_rec_snerror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|llp_rec_cberror
id|picreg_t
id|llp_rec_cberror
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|llp_rcty
id|picreg_t
id|llp_rcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|llp_tx_retry
id|picreg_t
id|llp_tx_retry
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18:18 */
DECL|member|llp_tcty
id|picreg_t
id|llp_tcty
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17:17 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|pci_abort
id|picreg_t
id|pci_abort
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|pci_parity
id|picreg_t
id|pci_parity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|pci_serr
id|picreg_t
id|pci_serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 13:13 */
DECL|member|pci_perr
id|picreg_t
id|pci_perr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|pci_master_tout
id|picreg_t
id|pci_master_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|pci_retry_cnt
id|picreg_t
id|pci_retry_cnt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 10:10 */
DECL|member|xread_req_tout
id|picreg_t
id|xread_req_tout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 9:9 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8:8 */
DECL|member|int_state
id|picreg_t
id|int_state
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 7:0 */
DECL|member|pic_p_mult_int_fld_s
)brace
id|pic_p_mult_int_fld_s
suffix:semicolon
DECL|typedef|pic_p_mult_int_u_t
)brace
id|pic_p_mult_int_u_t
suffix:semicolon
multiline_comment|/*&n; * Force Always Interrupt (x) Register&n; *&n; * A write to this data independent write only register will force a set inter-&n; * rupt to occur as if the interrupt line had transitioned. If the interrupt line&n; * is already active an addition set interrupt packet is set. All buffer flush op-&n; * erations also occur on this operation.&n; */
multiline_comment|/*&n; * Force Interrupt (x) Register&n; *&n; * A write to this data independent write only register in conjunction with&n; * the assertion of the corresponding interrupt line will force a set interrupt&n; * to occur as if the interrupt line had transitioned. The interrupt line must&n; * be active for this operation to generate a set packet, otherwise the write&n; * PIO is ignored. All buffer flush operations also occur when the set packet&n; * is sent on this operation.&n; */
multiline_comment|/*&n; * Device Registers&n; *&n; * The Device registers contain device specific and mapping information.&n; */
DECL|union|pic_device_reg_u
r_typedef
r_union
id|pic_device_reg_u
(brace
DECL|member|pic_device_reg_regval
id|picreg_t
id|pic_device_reg_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 31:30 */
DECL|member|en_virtual1
id|picreg_t
id|en_virtual1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|en_error_lock
id|picreg_t
id|en_error_lock
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|en_page_chk
id|picreg_t
id|en_page_chk
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|force_pci_par
id|picreg_t
id|force_pci_par
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26:26 */
DECL|member|en_virtual0
id|picreg_t
id|en_virtual0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25:25 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|dir_wrt_gen
id|picreg_t
id|dir_wrt_gen
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|dev_size
id|picreg_t
id|dev_size
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 22:22 */
DECL|member|real_time
id|picreg_t
id|real_time
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 21:21 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|swap_direct
id|picreg_t
id|swap_direct
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|prefetch
id|picreg_t
id|prefetch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 18:18 */
DECL|member|precise
id|picreg_t
id|precise
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 17:17 */
DECL|member|coherent
id|picreg_t
id|coherent
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|barrier
id|picreg_t
id|barrier
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|gbr
id|picreg_t
id|gbr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 14:14 */
DECL|member|dev_swap
id|picreg_t
id|dev_swap
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 13:13 */
DECL|member|dev_io_mem
id|picreg_t
id|dev_io_mem
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|dev_off
id|picreg_t
id|dev_off
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* 11:0 */
DECL|member|pic_device_reg_fld_s
)brace
id|pic_device_reg_fld_s
suffix:semicolon
DECL|typedef|pic_device_reg_u_t
)brace
id|pic_device_reg_u_t
suffix:semicolon
multiline_comment|/*&n; * Device (x) Write Request Buffer Flush&n; *&n; * When read, this register will return a 0x00 after the write buffer associat-&n; * ed with the device has been flushed. (PCI Only)&n; */
multiline_comment|/*&n; * Even Device Read Response Buffer Register (PCI Only)&n; *&n; * This register is use to allocate the read response buffers for the even num-&n; * bered devices. (0,2)&n; */
DECL|union|pic_p_even_resp_u
r_typedef
r_union
id|pic_p_even_resp_u
(brace
DECL|member|pic_p_even_resp_regval
id|picreg_t
id|pic_p_even_resp_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|buff_14_en
id|picreg_t
id|buff_14_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|buff_14_vdev
id|picreg_t
id|buff_14_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 30:29 */
DECL|member|buff_14_pdev
id|picreg_t
id|buff_14_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|buff_12_en
id|picreg_t
id|buff_12_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|buff_12_vdev
id|picreg_t
id|buff_12_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 26:25 */
DECL|member|buff_12_pdev
id|picreg_t
id|buff_12_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|buff_10_en
id|picreg_t
id|buff_10_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|buff_10_vdev
id|picreg_t
id|buff_10_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 22:21 */
DECL|member|buff_10_pdev
id|picreg_t
id|buff_10_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|buff_8_en
id|picreg_t
id|buff_8_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|buff_8_vdev
id|picreg_t
id|buff_8_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 18:17 */
DECL|member|buff_8_pdev
id|picreg_t
id|buff_8_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|buff_6_en
id|picreg_t
id|buff_6_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|buff_6_vdev
id|picreg_t
id|buff_6_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 14:13 */
DECL|member|buff_6_pdev
id|picreg_t
id|buff_6_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|buff_4_en
id|picreg_t
id|buff_4_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|buff_4_vdev
id|picreg_t
id|buff_4_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 10:9 */
DECL|member|buff_4_pdev
id|picreg_t
id|buff_4_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8:8 */
DECL|member|buff_2_en
id|picreg_t
id|buff_2_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 7:7 */
DECL|member|buff_2_vdev
id|picreg_t
id|buff_2_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 6:5 */
DECL|member|buff_2_pdev
id|picreg_t
id|buff_2_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 4:4 */
DECL|member|buff_0_en
id|picreg_t
id|buff_0_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 3:3 */
DECL|member|buff_0_vdev
id|picreg_t
id|buff_0_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 2:1 */
DECL|member|buff_0_pdev
id|picreg_t
id|buff_0_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0:0 */
DECL|member|pic_p_even_resp_fld_s
)brace
id|pic_p_even_resp_fld_s
suffix:semicolon
DECL|typedef|pic_p_even_resp_u_t
)brace
id|pic_p_even_resp_u_t
suffix:semicolon
multiline_comment|/*&n; * Odd Device Read Response Buffer Register (PCI Only)&n; *&n; * This register is use to allocate the read response buffers for the odd num-&n; * bered devices. (1,3))&n; */
DECL|union|pic_p_odd_resp_u
r_typedef
r_union
id|pic_p_odd_resp_u
(brace
DECL|member|pic_p_odd_resp_regval
id|picreg_t
id|pic_p_odd_resp_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|buff_15_en
id|picreg_t
id|buff_15_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|buff_15_vdev
id|picreg_t
id|buff_15_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 30:29 */
DECL|member|buff_15_pdev
id|picreg_t
id|buff_15_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|buff_13_en
id|picreg_t
id|buff_13_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|buff_13_vdev
id|picreg_t
id|buff_13_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 26:25 */
DECL|member|buff_13_pdev
id|picreg_t
id|buff_13_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|buff_11_en
id|picreg_t
id|buff_11_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 23:23 */
DECL|member|buff_11_vdev
id|picreg_t
id|buff_11_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 22:21 */
DECL|member|buff_11_pdev
id|picreg_t
id|buff_11_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 20:20 */
DECL|member|buff_9_en
id|picreg_t
id|buff_9_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 19:19 */
DECL|member|buff_9_vdev
id|picreg_t
id|buff_9_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 18:17 */
DECL|member|buff_9_pdev
id|picreg_t
id|buff_9_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 16:16 */
DECL|member|buff_7_en
id|picreg_t
id|buff_7_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 15:15 */
DECL|member|buff_7_vdev
id|picreg_t
id|buff_7_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 14:13 */
DECL|member|buff_7_pdev
id|picreg_t
id|buff_7_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 12:12 */
DECL|member|buff_5_en
id|picreg_t
id|buff_5_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 11:11 */
DECL|member|buff_5_vdev
id|picreg_t
id|buff_5_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 10:9 */
DECL|member|buff_5_pdev
id|picreg_t
id|buff_5_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 8:8 */
DECL|member|buff_3_en
id|picreg_t
id|buff_3_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 7:7 */
DECL|member|buff_3_vdev
id|picreg_t
id|buff_3_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 6:5 */
DECL|member|buff_3_pdev
id|picreg_t
id|buff_3_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 4:4 */
DECL|member|buff_1_en
id|picreg_t
id|buff_1_en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 3:3 */
DECL|member|buff_1_vdev
id|picreg_t
id|buff_1_vdev
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 2:1 */
DECL|member|buff_1_pdev
id|picreg_t
id|buff_1_pdev
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0:0 */
DECL|member|pic_p_odd_resp_fld_s
)brace
id|pic_p_odd_resp_fld_s
suffix:semicolon
DECL|typedef|pic_p_odd_resp_u_t
)brace
id|pic_p_odd_resp_u_t
suffix:semicolon
multiline_comment|/*&n; * Read Response Buffer Status Register (PCI Only)&n; *&n; * This read only register contains the current response buffer status.&n; */
DECL|union|pic_p_resp_status_u
r_typedef
r_union
id|pic_p_resp_status_u
(brace
DECL|member|pic_p_resp_status_regval
id|picreg_t
id|pic_p_resp_status_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|rrb_valid
id|picreg_t
id|rrb_valid
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|rrb_inuse
id|picreg_t
id|rrb_inuse
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_p_resp_status_fld_s
)brace
id|pic_p_resp_status_fld_s
suffix:semicolon
DECL|typedef|pic_p_resp_status_u_t
)brace
id|pic_p_resp_status_u_t
suffix:semicolon
multiline_comment|/*&n; * Read Response Buffer Clear Register (PCI Only)&n; *&n; * A write to this register clears the current contents of the buffer.&n; */
DECL|union|pic_p_resp_clear_u
r_typedef
r_union
id|pic_p_resp_clear_u
(brace
DECL|member|pic_p_resp_clear_regval
id|picreg_t
id|pic_p_resp_clear_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|rrb_clear
id|picreg_t
id|rrb_clear
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_p_resp_clear_fld_s
)brace
id|pic_p_resp_clear_fld_s
suffix:semicolon
DECL|typedef|pic_p_resp_clear_u_t
)brace
id|pic_p_resp_clear_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Read Response Buffer (x) Upper Address Match&n; *&n; * The PCI Bridge read response buffer upper address register is a read only&n; * register which contains the upper 16-bits of the address and status used to&n; * select the buffer for a PCI transaction.&n; */
DECL|union|pic_p_buf_upper_addr_match_u
r_typedef
r_union
id|pic_p_buf_upper_addr_match_u
(brace
DECL|member|pic_p_buf_upper_addr_match_regval
id|picreg_t
id|pic_p_buf_upper_addr_match_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|filled
id|picreg_t
id|filled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|armed
id|picreg_t
id|armed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|flush
id|picreg_t
id|flush
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|xerr
id|picreg_t
id|xerr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 28:28 */
DECL|member|pkterr
id|picreg_t
id|pkterr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 27:27 */
DECL|member|timeout
id|picreg_t
id|timeout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 26:26 */
DECL|member|prefetch
id|picreg_t
id|prefetch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 25:25 */
DECL|member|precise
id|picreg_t
id|precise
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 24:24 */
DECL|member|dw_be
id|picreg_t
id|dw_be
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_p_buf_upper_addr_match_fld_s
)brace
id|pic_p_buf_upper_addr_match_fld_s
suffix:semicolon
DECL|typedef|pic_p_buf_upper_addr_match_u_t
)brace
id|pic_p_buf_upper_addr_match_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Read Response Buffer (x) Lower Address Match&n; *&n; * The PCI Bridge read response buffer lower address Match register is a&n; * read only register which contains the address and status used to select the&n; * buffer for a PCI transaction.&n; */
DECL|union|pic_p_buf_lower_addr_match_u
r_typedef
r_union
id|pic_p_buf_lower_addr_match_u
(brace
DECL|member|pic_p_buf_lower_addr_match_regval
id|picreg_t
id|pic_p_buf_lower_addr_match_regval
suffix:semicolon
r_struct
(brace
DECL|member|filled
id|picreg_t
id|filled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 63:63 */
DECL|member|armed
id|picreg_t
id|armed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 62:62 */
DECL|member|flush
id|picreg_t
id|flush
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 61:61 */
DECL|member|xerr
id|picreg_t
id|xerr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 60:60 */
DECL|member|pkterr
id|picreg_t
id|pkterr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 59:59 */
DECL|member|timeout
id|picreg_t
id|timeout
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 58:58 */
DECL|member|prefetch
id|picreg_t
id|prefetch
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 57:57 */
DECL|member|precise
id|picreg_t
id|precise
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 56:56 */
DECL|member|dw_be
id|picreg_t
id|dw_be
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 55:48 */
DECL|member|upp_addr
id|picreg_t
id|upp_addr
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 47:32 */
DECL|member|low_addr
id|picreg_t
id|low_addr
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 31:0 */
DECL|member|pic_p_buf_lower_addr_match_fld_s
)brace
id|pic_p_buf_lower_addr_match_fld_s
suffix:semicolon
DECL|typedef|pic_p_buf_lower_addr_match_u_t
)brace
id|pic_p_buf_lower_addr_match_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Flush Count with Data Touch Register&n; *&n; * This counter is incremented each time the corresponding response buffer&n; * is flushed after at least a single data element in the buffer is used. A word&n; * write to this address clears the count.&n; */
DECL|union|pic_flush_w_touch_u
r_typedef
r_union
id|pic_flush_w_touch_u
(brace
DECL|member|pic_flush_w_touch_regval
id|picreg_t
id|pic_flush_w_touch_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|touch_cnt
id|picreg_t
id|touch_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_flush_w_touch_fld_s
)brace
id|pic_flush_w_touch_fld_s
suffix:semicolon
DECL|typedef|pic_flush_w_touch_u_t
)brace
id|pic_flush_w_touch_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Flush Count w/o Data Touch Register&n; *&n; * This counter is incremented each time the corresponding response buffer&n; * is flushed without any data element in the buffer being used. A word&n; * write to this address clears the count.&n; */
DECL|union|pic_flush_wo_touch_u
r_typedef
r_union
id|pic_flush_wo_touch_u
(brace
DECL|member|pic_flush_wo_touch_regval
id|picreg_t
id|pic_flush_wo_touch_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|notouch_cnt
id|picreg_t
id|notouch_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_flush_wo_touch_fld_s
)brace
id|pic_flush_wo_touch_fld_s
suffix:semicolon
DECL|typedef|pic_flush_wo_touch_u_t
)brace
id|pic_flush_wo_touch_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Request in Flight Count Register&n; *&n; * This counter is incremented on each bus clock while the request is in-&n; * flight. A word write to this address clears the count. ]&n; */
DECL|union|pic_inflight_u
r_typedef
r_union
id|pic_inflight_u
(brace
DECL|member|pic_inflight_regval
id|picreg_t
id|pic_inflight_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|inflight_cnt
id|picreg_t
id|inflight_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_inflight_fld_s
)brace
id|pic_inflight_fld_s
suffix:semicolon
DECL|typedef|pic_inflight_u_t
)brace
id|pic_inflight_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Prefetch Request Count Register&n; *&n; * This counter is incremented each time the request using this buffer was&n; * generated from the prefetcher. A word write to this address clears the&n; * count.&n; */
DECL|union|pic_prefetch_u
r_typedef
r_union
id|pic_prefetch_u
(brace
DECL|member|pic_prefetch_regval
id|picreg_t
id|pic_prefetch_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|prefetch_cnt
id|picreg_t
id|prefetch_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_prefetch_fld_s
)brace
id|pic_prefetch_fld_s
suffix:semicolon
DECL|typedef|pic_prefetch_u_t
)brace
id|pic_prefetch_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Total PCI Retry Count Register&n; *&n; * This counter is incremented each time a PCI bus retry occurs and the ad-&n; * dress matches the tag for the selected buffer. The buffer must also has this&n; * request in-flight. A word write to this address clears the count.&n; */
DECL|union|pic_total_pci_retry_u
r_typedef
r_union
id|pic_total_pci_retry_u
(brace
DECL|member|pic_total_pci_retry_regval
id|picreg_t
id|pic_total_pci_retry_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|retry_cnt
id|picreg_t
id|retry_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_total_pci_retry_fld_s
)brace
id|pic_total_pci_retry_fld_s
suffix:semicolon
DECL|typedef|pic_total_pci_retry_u_t
)brace
id|pic_total_pci_retry_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Max PCI Retry Count Register&n; *&n; * This counter is contains the maximum retry count for a single request&n; * which was in-flight for this buffer. A word write to this address clears the&n; * count.&n; */
DECL|union|pic_max_pci_retry_u
r_typedef
r_union
id|pic_max_pci_retry_u
(brace
DECL|member|pic_max_pci_retry_regval
id|picreg_t
id|pic_max_pci_retry_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|max_retry_cnt
id|picreg_t
id|max_retry_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_max_pci_retry_fld_s
)brace
id|pic_max_pci_retry_fld_s
suffix:semicolon
DECL|typedef|pic_max_pci_retry_u_t
)brace
id|pic_max_pci_retry_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Max Latency Count Register&n; *&n; * This counter is contains the maximum count (in bus clocks) for a single&n; * request which was in-flight for this buffer. A word write to this address&n; * clears the count.&n; */
DECL|union|pic_max_latency_u
r_typedef
r_union
id|pic_max_latency_u
(brace
DECL|member|pic_max_latency_regval
id|picreg_t
id|pic_max_latency_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 31:16 */
DECL|member|max_latency_cnt
id|picreg_t
id|max_latency_cnt
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 15:0 */
DECL|member|pic_max_latency_fld_s
)brace
id|pic_max_latency_fld_s
suffix:semicolon
DECL|typedef|pic_max_latency_u_t
)brace
id|pic_max_latency_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI Buffer (x) Clear All Register&n; *&n; * Any access to this register clears all the count values for the (x) registers.&n; */
multiline_comment|/*&n; * PCI-X Registers&n; *&n; * This register contains the address in the read buffer structure. There are&n; * 16 read buffer structures.&n; */
DECL|union|pic_rd_buf_addr_u
r_typedef
r_union
id|pic_rd_buf_addr_u
(brace
DECL|member|pic_rd_buf_addr_regval
id|picreg_t
id|pic_rd_buf_addr_regval
suffix:semicolon
r_struct
(brace
DECL|member|pcix_err_addr
id|picreg_t
id|pcix_err_addr
suffix:colon
l_int|64
suffix:semicolon
multiline_comment|/* 63:0 */
DECL|member|pic_rd_buf_addr_fld_s
)brace
id|pic_rd_buf_addr_fld_s
suffix:semicolon
DECL|typedef|pic_rd_buf_addr_u_t
)brace
id|pic_rd_buf_addr_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Read Buffer (x) Attribute Register&n; *&n; * This register contains the attribute data in the read buffer structure. There&n; * are  16 read buffer structures.&n; */
DECL|union|pic_px_read_buf_attr_u
r_typedef
r_union
id|pic_px_read_buf_attr_u
(brace
DECL|member|pic_px_read_buf_attr_regval
id|picreg_t
id|pic_px_read_buf_attr_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 63:48 */
DECL|member|bus_cmd
id|picreg_t
id|bus_cmd
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 47:44 */
DECL|member|byte_cnt
id|picreg_t
id|byte_cnt
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* 43:32 */
DECL|member|entry_valid
id|picreg_t
id|entry_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|ns
id|picreg_t
id|ns
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|ro
id|picreg_t
id|ro
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|tag
id|picreg_t
id|tag
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 28:24 */
DECL|member|bus_num
id|picreg_t
id|bus_num
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|dev_num
id|picreg_t
id|dev_num
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 15:11 */
DECL|member|fun_num
id|picreg_t
id|fun_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 10:8 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 7:6 */
DECL|member|f_buffer_index
id|picreg_t
id|f_buffer_index
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 5:0 */
DECL|member|pic_px_read_buf_attr_fld_s
)brace
id|pic_px_read_buf_attr_fld_s
suffix:semicolon
DECL|typedef|pic_px_read_buf_attr_u_t
)brace
id|pic_px_read_buf_attr_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Write Buffer (x) Address Register&n; *&n; * This register contains the address in the write buffer structure. There are&n; * 8 write buffer structures.&n; */
DECL|union|pic_px_write_buf_addr_u
r_typedef
r_union
id|pic_px_write_buf_addr_u
(brace
DECL|member|pic_px_write_buf_addr_regval
id|picreg_t
id|pic_px_write_buf_addr_regval
suffix:semicolon
r_struct
(brace
DECL|member|pcix_err_addr
id|picreg_t
id|pcix_err_addr
suffix:colon
l_int|64
suffix:semicolon
multiline_comment|/* 63:0 */
DECL|member|pic_px_write_buf_addr_fld_s
)brace
id|pic_px_write_buf_addr_fld_s
suffix:semicolon
DECL|typedef|pic_px_write_buf_addr_u_t
)brace
id|pic_px_write_buf_addr_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Write Buffer (x) Attribute Register&n; *&n; * This register contains the attribute data in the write buffer structure.&n; * There are 8 write buffer structures.&n; */
DECL|union|pic_px_write_buf_attr_u
r_typedef
r_union
id|pic_px_write_buf_attr_u
(brace
DECL|member|pic_px_write_buf_attr_regval
id|picreg_t
id|pic_px_write_buf_attr_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* 63:48 */
DECL|member|bus_cmd
id|picreg_t
id|bus_cmd
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* 47:44 */
DECL|member|byte_cnt
id|picreg_t
id|byte_cnt
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* 43:32 */
DECL|member|entry_valid
id|picreg_t
id|entry_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 31:31 */
DECL|member|ns
id|picreg_t
id|ns
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 30:30 */
DECL|member|ro
id|picreg_t
id|ro
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 29:29 */
DECL|member|tag
id|picreg_t
id|tag
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 28:24 */
DECL|member|bus_num
id|picreg_t
id|bus_num
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 23:16 */
DECL|member|dev_num
id|picreg_t
id|dev_num
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* 15:11 */
DECL|member|fun_num
id|picreg_t
id|fun_num
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 10:8 */
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 7:6 */
DECL|member|f_buffer_index
id|picreg_t
id|f_buffer_index
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* 5:0 */
DECL|member|pic_px_write_buf_attr_fld_s
)brace
id|pic_px_write_buf_attr_fld_s
suffix:semicolon
DECL|typedef|pic_px_write_buf_attr_u_t
)brace
id|pic_px_write_buf_attr_u_t
suffix:semicolon
multiline_comment|/*&n; * PCI-X Write Buffer (x) Valid Register&n; *&n; * This register contains the valid or inuse cache lines for this buffer struc-&n; * ture.&n; */
DECL|union|pic_px_write_buf_valid_u
r_typedef
r_union
id|pic_px_write_buf_valid_u
(brace
DECL|member|pic_px_write_buf_valid_regval
id|picreg_t
id|pic_px_write_buf_valid_regval
suffix:semicolon
r_struct
(brace
DECL|member|picreg_t
id|picreg_t
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 63:32 */
DECL|member|wrt_valid_buff
id|picreg_t
id|wrt_valid_buff
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* 31:0 */
DECL|member|pic_px_write_buf_valid_fld_s
)brace
id|pic_px_write_buf_valid_fld_s
suffix:semicolon
DECL|typedef|pic_px_write_buf_valid_u_t
)brace
id|pic_px_write_buf_valid_u_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __ASSEMBLY__ */
macro_line|#endif                          /* _ASM_SN_PCI_PIC_H */
eof
