multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 - 1997, 2000-2003 Silicon Graphics, Inc. All rights reserved.&n; */
macro_line|#ifndef _ASM_IA64_SN_PCI_PIC_H
DECL|macro|_ASM_IA64_SN_PCI_PIC_H
mdefine_line|#define _ASM_IA64_SN_PCI_PIC_H
multiline_comment|/*&n; * PIC AS DEVICE ZERO&n; * ------------------&n; *&n; * PIC handles PCI/X busses.  PCI/X requires that the &squot;bridge&squot; (i.e. PIC)&n; * be designated as &squot;device 0&squot;.   That is a departure from earlier SGI&n; * PCI bridges.  Because of that we use config space 1 to access the&n; * config space of the first actual PCI device on the bus. &n; * Here&squot;s what the PIC manual says:&n; *&n; *     The current PCI-X bus specification now defines that the parent&n; *     hosts bus bridge (PIC for example) must be device 0 on bus 0. PIC&n; *     reduced the total number of devices from 8 to 4 and removed the&n; *     device registers and windows, now only supporting devices 0,1,2, and&n; *     3. PIC did leave all 8 configuration space windows. The reason was&n; *     there was nothing to gain by removing them. Here in lies the problem.&n; *     The device numbering we do using 0 through 3 is unrelated to the device&n; *     numbering which PCI-X requires in configuration space. In the past we&n; *     correlated Configs pace and our device space 0 &lt;-&gt; 0, 1 &lt;-&gt; 1, etc.&n; *     PCI-X requires we start a 1, not 0 and currently the PX brick&n; *     does associate our:&n; * &n; *         device 0 with configuration space window 1,&n; *         device 1 with configuration space window 2, &n; *         device 2 with configuration space window 3,&n; *         device 3 with configuration space window 4.&n; *&n; * The net effect is that all config space access are off-by-one with &n; * relation to other per-slot accesses on the PIC.   &n; * Here is a table that shows some of that:&n; *&n; *                               Internal Slot#&n; *           |&n; *           |     0         1        2         3&n; * ----------|---------------------------------------&n; * config    |  0x21000   0x22000  0x23000   0x24000&n; *           |&n; * even rrb  |  0[0]      n/a      1[0]      n/a&t;[] == implied even/odd&n; *           |&n; * odd rrb   |  n/a       0[1]     n/a       1[1]&n; *           |&n; * int dev   |  00       01        10        11&n; *           |&n; * ext slot# |  1        2         3         4&n; * ----------|---------------------------------------&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/sn/xtalk/xwidget.h&gt;&t;/* generic widget header */
macro_line|#else
macro_line|#include &lt;xtalk/xwidget.h&gt;
macro_line|#endif
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
DECL|typedef|picate_t
r_typedef
r_uint64
id|picate_t
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *********************** PIC MMR structure mapping ***************************&n; *****************************************************************************/
multiline_comment|/* NOTE: PIC WAR. PV#854697.  PIC does not allow writes just to [31:0]&n; * of a 64-bit register.  When writing PIC registers, always write the &n; * entire 64 bits.&n; */
DECL|struct|pic_s
r_typedef
r_volatile
r_struct
id|pic_s
(brace
multiline_comment|/* 0x000000-0x00FFFF -- Local Registers */
multiline_comment|/* 0x000000-0x000057 -- Standard Widget Configuration */
DECL|member|p_wid_id
id|picreg_t
id|p_wid_id
suffix:semicolon
multiline_comment|/* 0x000000 */
DECL|member|p_wid_stat
id|picreg_t
id|p_wid_stat
suffix:semicolon
multiline_comment|/* 0x000008 */
DECL|member|p_wid_err_upper
id|picreg_t
id|p_wid_err_upper
suffix:semicolon
multiline_comment|/* 0x000010 */
DECL|member|p_wid_err_lower
id|picreg_t
id|p_wid_err_lower
suffix:semicolon
multiline_comment|/* 0x000018 */
DECL|macro|p_wid_err
mdefine_line|#define p_wid_err p_wid_err_lower
DECL|member|p_wid_control
id|picreg_t
id|p_wid_control
suffix:semicolon
multiline_comment|/* 0x000020 */
DECL|member|p_wid_req_timeout
id|picreg_t
id|p_wid_req_timeout
suffix:semicolon
multiline_comment|/* 0x000028 */
DECL|member|p_wid_int_upper
id|picreg_t
id|p_wid_int_upper
suffix:semicolon
multiline_comment|/* 0x000030 */
DECL|member|p_wid_int_lower
id|picreg_t
id|p_wid_int_lower
suffix:semicolon
multiline_comment|/* 0x000038 */
DECL|macro|p_wid_int
mdefine_line|#define p_wid_int p_wid_int_lower
DECL|member|p_wid_err_cmdword
id|picreg_t
id|p_wid_err_cmdword
suffix:semicolon
multiline_comment|/* 0x000040 */
DECL|member|p_wid_llp
id|picreg_t
id|p_wid_llp
suffix:semicolon
multiline_comment|/* 0x000048 */
DECL|member|p_wid_tflush
id|picreg_t
id|p_wid_tflush
suffix:semicolon
multiline_comment|/* 0x000050 */
multiline_comment|/* 0x000058-0x00007F -- Bridge-specific Widget Configuration */
DECL|member|p_wid_aux_err
id|picreg_t
id|p_wid_aux_err
suffix:semicolon
multiline_comment|/* 0x000058 */
DECL|member|p_wid_resp_upper
id|picreg_t
id|p_wid_resp_upper
suffix:semicolon
multiline_comment|/* 0x000060 */
DECL|member|p_wid_resp_lower
id|picreg_t
id|p_wid_resp_lower
suffix:semicolon
multiline_comment|/* 0x000068 */
DECL|macro|p_wid_resp
mdefine_line|#define p_wid_resp p_wid_resp_lower
DECL|member|p_wid_tst_pin_ctrl
id|picreg_t
id|p_wid_tst_pin_ctrl
suffix:semicolon
multiline_comment|/* 0x000070 */
DECL|member|p_wid_addr_lkerr
id|picreg_t
id|p_wid_addr_lkerr
suffix:semicolon
multiline_comment|/* 0x000078 */
multiline_comment|/* 0x000080-0x00008F -- PMU &amp; MAP */
DECL|member|p_dir_map
id|picreg_t
id|p_dir_map
suffix:semicolon
multiline_comment|/* 0x000080 */
DECL|member|_pad_000088
id|picreg_t
id|_pad_000088
suffix:semicolon
multiline_comment|/* 0x000088 */
multiline_comment|/* 0x000090-0x00009F -- SSRAM */
DECL|member|p_map_fault
id|picreg_t
id|p_map_fault
suffix:semicolon
multiline_comment|/* 0x000090 */
DECL|member|_pad_000098
id|picreg_t
id|_pad_000098
suffix:semicolon
multiline_comment|/* 0x000098 */
multiline_comment|/* 0x0000A0-0x0000AF -- Arbitration */
DECL|member|p_arb
id|picreg_t
id|p_arb
suffix:semicolon
multiline_comment|/* 0x0000A0 */
DECL|member|_pad_0000A8
id|picreg_t
id|_pad_0000A8
suffix:semicolon
multiline_comment|/* 0x0000A8 */
multiline_comment|/* 0x0000B0-0x0000BF -- Number In A Can or ATE Parity Error */
DECL|member|p_ate_parity_err
id|picreg_t
id|p_ate_parity_err
suffix:semicolon
multiline_comment|/* 0x0000B0 */
DECL|member|_pad_0000B8
id|picreg_t
id|_pad_0000B8
suffix:semicolon
multiline_comment|/* 0x0000B8 */
multiline_comment|/* 0x0000C0-0x0000FF -- PCI/GIO */
DECL|member|p_bus_timeout
id|picreg_t
id|p_bus_timeout
suffix:semicolon
multiline_comment|/* 0x0000C0 */
DECL|member|p_pci_cfg
id|picreg_t
id|p_pci_cfg
suffix:semicolon
multiline_comment|/* 0x0000C8 */
DECL|member|p_pci_err_upper
id|picreg_t
id|p_pci_err_upper
suffix:semicolon
multiline_comment|/* 0x0000D0 */
DECL|member|p_pci_err_lower
id|picreg_t
id|p_pci_err_lower
suffix:semicolon
multiline_comment|/* 0x0000D8 */
DECL|macro|p_pci_err
mdefine_line|#define p_pci_err p_pci_err_lower
DECL|member|_pad_0000E0
id|picreg_t
id|_pad_0000E0
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0000{E0..F8} */
multiline_comment|/* 0x000100-0x0001FF -- Interrupt */
DECL|member|p_int_status
id|picreg_t
id|p_int_status
suffix:semicolon
multiline_comment|/* 0x000100 */
DECL|member|p_int_enable
id|picreg_t
id|p_int_enable
suffix:semicolon
multiline_comment|/* 0x000108 */
DECL|member|p_int_rst_stat
id|picreg_t
id|p_int_rst_stat
suffix:semicolon
multiline_comment|/* 0x000110 */
DECL|member|p_int_mode
id|picreg_t
id|p_int_mode
suffix:semicolon
multiline_comment|/* 0x000118 */
DECL|member|p_int_device
id|picreg_t
id|p_int_device
suffix:semicolon
multiline_comment|/* 0x000120 */
DECL|member|p_int_host_err
id|picreg_t
id|p_int_host_err
suffix:semicolon
multiline_comment|/* 0x000128 */
DECL|member|p_int_addr
id|picreg_t
id|p_int_addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{30,,,68} */
DECL|member|p_err_int_view
id|picreg_t
id|p_err_int_view
suffix:semicolon
multiline_comment|/* 0x000170 */
DECL|member|p_mult_int
id|picreg_t
id|p_mult_int
suffix:semicolon
multiline_comment|/* 0x000178 */
DECL|member|p_force_always
id|picreg_t
id|p_force_always
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{80,,,B8} */
DECL|member|p_force_pin
id|picreg_t
id|p_force_pin
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x0001{C0,,,F8} */
multiline_comment|/* 0x000200-0x000298 -- Device */
DECL|member|p_device
id|picreg_t
id|p_device
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{00,,,18} */
DECL|member|_pad_000220
id|picreg_t
id|_pad_000220
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{20,,,38} */
DECL|member|p_wr_req_buf
id|picreg_t
id|p_wr_req_buf
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{40,,,58} */
DECL|member|_pad_000260
id|picreg_t
id|_pad_000260
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x0002{60,,,78} */
DECL|member|p_rrb_map
id|picreg_t
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
id|picreg_t
id|p_resp_status
suffix:semicolon
multiline_comment|/* 0x000290 */
DECL|member|p_resp_clear
id|picreg_t
id|p_resp_clear
suffix:semicolon
multiline_comment|/* 0x000298 */
DECL|member|_pad_0002A0
id|picreg_t
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
id|picreg_t
id|upper
suffix:semicolon
multiline_comment|/* 0x0003{00,,,F0} */
DECL|member|lower
id|picreg_t
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
id|picreg_t
id|flush_w_touch
suffix:semicolon
multiline_comment|/* 0x000{400,,,5C0} */
DECL|member|flush_wo_touch
id|picreg_t
id|flush_wo_touch
suffix:semicolon
multiline_comment|/* 0x000{408,,,5C8} */
DECL|member|inflight
id|picreg_t
id|inflight
suffix:semicolon
multiline_comment|/* 0x000{410,,,5D0} */
DECL|member|prefetch
id|picreg_t
id|prefetch
suffix:semicolon
multiline_comment|/* 0x000{418,,,5D8} */
DECL|member|total_pci_retry
id|picreg_t
id|total_pci_retry
suffix:semicolon
multiline_comment|/* 0x000{420,,,5E0} */
DECL|member|max_pci_retry
id|picreg_t
id|max_pci_retry
suffix:semicolon
multiline_comment|/* 0x000{428,,,5E8} */
DECL|member|max_latency
id|picreg_t
id|max_latency
suffix:semicolon
multiline_comment|/* 0x000{430,,,5F0} */
DECL|member|clear_all
id|picreg_t
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
id|picreg_t
id|p_pcix_bus_err_addr
suffix:semicolon
multiline_comment|/* 0x000600 */
DECL|member|p_pcix_bus_err_attr
id|picreg_t
id|p_pcix_bus_err_attr
suffix:semicolon
multiline_comment|/* 0x000608 */
DECL|member|p_pcix_bus_err_data
id|picreg_t
id|p_pcix_bus_err_data
suffix:semicolon
multiline_comment|/* 0x000610 */
DECL|member|p_pcix_pio_split_addr
id|picreg_t
id|p_pcix_pio_split_addr
suffix:semicolon
multiline_comment|/* 0x000618 */
DECL|member|p_pcix_pio_split_attr
id|picreg_t
id|p_pcix_pio_split_attr
suffix:semicolon
multiline_comment|/* 0x000620 */
DECL|member|p_pcix_dma_req_err_attr
id|picreg_t
id|p_pcix_dma_req_err_attr
suffix:semicolon
multiline_comment|/* 0x000628 */
DECL|member|p_pcix_dma_req_err_addr
id|picreg_t
id|p_pcix_dma_req_err_addr
suffix:semicolon
multiline_comment|/* 0x000630 */
DECL|member|p_pcix_timeout
id|picreg_t
id|p_pcix_timeout
suffix:semicolon
multiline_comment|/* 0x000638 */
DECL|member|_pad_000640
id|picreg_t
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
id|picreg_t
id|p_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{A00,,,AF0} */
DECL|member|p_buf_attr
id|picreg_t
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
id|picreg_t
id|p_buf_addr
suffix:semicolon
multiline_comment|/* 0x000{B00,,,BE0} */
DECL|member|p_buf_attr
id|picreg_t
id|p_buf_attr
suffix:semicolon
multiline_comment|/* 0x000{B08,,,BE8} */
DECL|member|p_buf_valid
id|picreg_t
id|p_buf_valid
suffix:semicolon
multiline_comment|/* 0x000{B10,,,BF0} */
DECL|member|__pad1
id|picreg_t
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
id|picate_t
id|p_int_ate_ram
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* 0x010000-0x011fff */
multiline_comment|/* 0x012000-0x013fff -- Internal ATE RAM (Manual Parity Generation) */
DECL|member|p_int_ate_ram_mp
id|picate_t
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
id|picreg_t
id|p_wr_req_lower
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x18000 - 0x187F8 */
DECL|member|p_wr_req_upper
id|picreg_t
id|p_wr_req_upper
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* 0x18800 - 0x18FF8 */
DECL|member|p_wr_req_parity
id|picreg_t
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
DECL|typedef|pic_t
)brace
id|pic_t
suffix:semicolon
macro_line|#endif                          /* _ASM_IA64_SN_PCI_PIC_H */
eof
