multiline_comment|/*&n; * arch/ppc/platforms/cpci690.h&n; *&n; * Definitions for Force CPCI690&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2003 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
multiline_comment|/*&n; * The GT64260 has 2 PCI buses each with 1 window from the CPU bus to&n; * PCI I/O space and 4 windows from the CPU bus to PCI MEM space.&n; */
macro_line|#ifndef __PPC_PLATFORMS_CPCI690_H
DECL|macro|__PPC_PLATFORMS_CPCI690_H
mdefine_line|#define __PPC_PLATFORMS_CPCI690_H
multiline_comment|/*&n; * Define bd_t to pass in the MAC addresses used by the GT64260&squot;s enet ctlrs.&n; */
DECL|macro|CPCI690_BI_MAGIC
mdefine_line|#define&t;CPCI690_BI_MAGIC&t;&t;0xFE8765DC
DECL|struct|board_info
r_typedef
r_struct
id|board_info
(brace
DECL|member|bi_magic
id|u32
id|bi_magic
suffix:semicolon
DECL|member|bi_enetaddr
id|u8
id|bi_enetaddr
(braket
l_int|3
)braket
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
multiline_comment|/* PCI bus Resource setup */
DECL|macro|CPCI690_PCI0_MEM_START_PROC_ADDR
mdefine_line|#define CPCI690_PCI0_MEM_START_PROC_ADDR&t;0x80000000
DECL|macro|CPCI690_PCI0_MEM_START_PCI_HI_ADDR
mdefine_line|#define CPCI690_PCI0_MEM_START_PCI_HI_ADDR&t;0x00000000
DECL|macro|CPCI690_PCI0_MEM_START_PCI_LO_ADDR
mdefine_line|#define CPCI690_PCI0_MEM_START_PCI_LO_ADDR&t;0x80000000
DECL|macro|CPCI690_PCI0_MEM_SIZE
mdefine_line|#define CPCI690_PCI0_MEM_SIZE&t;&t;&t;0x10000000
DECL|macro|CPCI690_PCI0_IO_START_PROC_ADDR
mdefine_line|#define CPCI690_PCI0_IO_START_PROC_ADDR&t;&t;0xa0000000
DECL|macro|CPCI690_PCI0_IO_START_PCI_ADDR
mdefine_line|#define CPCI690_PCI0_IO_START_PCI_ADDR&t;&t;0x00000000
DECL|macro|CPCI690_PCI0_IO_SIZE
mdefine_line|#define CPCI690_PCI0_IO_SIZE&t;&t;&t;0x01000000
DECL|macro|CPCI690_PCI1_MEM_START_PROC_ADDR
mdefine_line|#define CPCI690_PCI1_MEM_START_PROC_ADDR&t;0x90000000
DECL|macro|CPCI690_PCI1_MEM_START_PCI_HI_ADDR
mdefine_line|#define CPCI690_PCI1_MEM_START_PCI_HI_ADDR&t;0x00000000
DECL|macro|CPCI690_PCI1_MEM_START_PCI_LO_ADDR
mdefine_line|#define CPCI690_PCI1_MEM_START_PCI_LO_ADDR&t;0x90000000
DECL|macro|CPCI690_PCI1_MEM_SIZE
mdefine_line|#define CPCI690_PCI1_MEM_SIZE&t;&t;&t;0x10000000
DECL|macro|CPCI690_PCI1_IO_START_PROC_ADDR
mdefine_line|#define CPCI690_PCI1_IO_START_PROC_ADDR&t;&t;0xa1000000
DECL|macro|CPCI690_PCI1_IO_START_PCI_ADDR
mdefine_line|#define CPCI690_PCI1_IO_START_PCI_ADDR&t;&t;0x01000000
DECL|macro|CPCI690_PCI1_IO_SIZE
mdefine_line|#define CPCI690_PCI1_IO_SIZE&t;&t;&t;0x01000000
multiline_comment|/* Board Registers */
DECL|macro|CPCI690_BR_BASE
mdefine_line|#define&t;CPCI690_BR_BASE&t;&t;&t;&t;0xf0000000
DECL|macro|CPCI690_BR_SIZE_ACTUAL
mdefine_line|#define&t;CPCI690_BR_SIZE_ACTUAL&t;&t;&t;0x8
DECL|macro|CPCI690_BR_SIZE
mdefine_line|#define&t;CPCI690_BR_SIZE&t;&t;&t;max(GT64260_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;CPCI690_BR_SIZE_ACTUAL)
DECL|macro|CPCI690_BR_LED_CNTL
mdefine_line|#define&t;CPCI690_BR_LED_CNTL&t;&t;&t;0x00
DECL|macro|CPCI690_BR_SW_RESET
mdefine_line|#define&t;CPCI690_BR_SW_RESET&t;&t;&t;0x01
DECL|macro|CPCI690_BR_MISC_STATUS
mdefine_line|#define&t;CPCI690_BR_MISC_STATUS&t;&t;&t;0x02
DECL|macro|CPCI690_BR_SWITCH_STATUS
mdefine_line|#define&t;CPCI690_BR_SWITCH_STATUS&t;&t;0x03
DECL|macro|CPCI690_BR_MEM_CTLR
mdefine_line|#define&t;CPCI690_BR_MEM_CTLR&t;&t;&t;0x04
DECL|macro|CPCI690_BR_LAST_RESET_1
mdefine_line|#define&t;CPCI690_BR_LAST_RESET_1&t;&t;&t;0x05
DECL|macro|CPCI690_BR_LAST_RESET_2
mdefine_line|#define&t;CPCI690_BR_LAST_RESET_2&t;&t;&t;0x06
DECL|macro|CPCI690_TODC_BASE
mdefine_line|#define&t;CPCI690_TODC_BASE&t;&t;&t;0xf0100000
DECL|macro|CPCI690_TODC_SIZE_ACTUAL
mdefine_line|#define&t;CPCI690_TODC_SIZE_ACTUAL&t;&t;0x8000 /* Size or NVRAM + RTC */
DECL|macro|CPCI690_TODC_SIZE
mdefine_line|#define&t;CPCI690_TODC_SIZE&t;&t;max(GT64260_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;CPCI690_TODC_SIZE_ACTUAL)
DECL|macro|CPCI690_MAC_OFFSET
mdefine_line|#define&t;CPCI690_MAC_OFFSET&t;&t;&t;0x7c10 /* MAC in RTC NVRAM */
DECL|macro|CPCI690_IPMI_BASE
mdefine_line|#define&t;CPCI690_IPMI_BASE&t;&t;&t;0xf0200000
DECL|macro|CPCI690_IPMI_SIZE_ACTUAL
mdefine_line|#define&t;CPCI690_IPMI_SIZE_ACTUAL&t;&t;0x10 /* 16 bytes of IPMI */
DECL|macro|CPCI690_IPMI_SIZE
mdefine_line|#define&t;CPCI690_IPMI_SIZE&t;&t;max(GT64260_WINDOW_SIZE_MIN,&t;&bslash;&n;&t;&t;&t;&t;&t;&t;CPCI690_IPMI_SIZE_ACTUAL)
macro_line|#endif /* __PPC_PLATFORMS_CPCI690_H */
eof
