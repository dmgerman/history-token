multiline_comment|/*&n;** macints.h -- Macintosh Linux interrupt handling structs and prototypes&n;**&n;** Copyright 1997 by Michael Schmitz&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;*/
macro_line|#ifndef _ASM_MACINTS_H_
DECL|macro|_ASM_MACINTS_H_
mdefine_line|#define _ASM_MACINTS_H_
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* Setting this prints debugging info for unclaimed interrupts */
DECL|macro|DEBUG_SPURIOUS
mdefine_line|#define DEBUG_SPURIOUS
multiline_comment|/* Setting this prints debugging info on each autovector interrupt */
multiline_comment|/* #define DEBUG_IRQS */
multiline_comment|/* Setting this prints debugging info on each Nubus interrupt */
multiline_comment|/* #define DEBUG_NUBUS_INT */
multiline_comment|/* Setting this prints debugging info on irqs as they enabled and disabled. */
multiline_comment|/* #define DEBUG_IRQUSE */
multiline_comment|/*&n; * Base IRQ number for all Mac68K interrupt sources. Each source&n; * has eight indexes (base -&gt; base+7).&n; */
DECL|macro|VIA1_SOURCE_BASE
mdefine_line|#define VIA1_SOURCE_BASE&t;8
DECL|macro|VIA2_SOURCE_BASE
mdefine_line|#define VIA2_SOURCE_BASE&t;16
DECL|macro|MAC_SCC_SOURCE_BASE
mdefine_line|#define MAC_SCC_SOURCE_BASE&t;24
DECL|macro|PSC3_SOURCE_BASE
mdefine_line|#define PSC3_SOURCE_BASE&t;24
DECL|macro|PSC4_SOURCE_BASE
mdefine_line|#define PSC4_SOURCE_BASE&t;32
DECL|macro|PSC5_SOURCE_BASE
mdefine_line|#define PSC5_SOURCE_BASE&t;40
DECL|macro|PSC6_SOURCE_BASE
mdefine_line|#define PSC6_SOURCE_BASE&t;48
DECL|macro|NUBUS_SOURCE_BASE
mdefine_line|#define NUBUS_SOURCE_BASE&t;56
DECL|macro|BABOON_SOURCE_BASE
mdefine_line|#define BABOON_SOURCE_BASE&t;64
multiline_comment|/*&n; * Maximum IRQ number is BABOON_SOURCE_BASE + 7,&n; * giving us IRQs up through 71&n; */
DECL|macro|NUM_MAC_SOURCES
mdefine_line|#define NUM_MAC_SOURCES&t;&t;72
multiline_comment|/* &n; * clean way to separate IRQ into its source and index&n; */
DECL|macro|IRQ_SRC
mdefine_line|#define IRQ_SRC(irq)&t;(irq &gt;&gt; 3)
DECL|macro|IRQ_IDX
mdefine_line|#define&t;IRQ_IDX(irq)&t;(irq &amp; 7)
DECL|macro|IRQ_SPURIOUS
mdefine_line|#define&t;IRQ_SPURIOUS      (0)
multiline_comment|/* auto-vector interrupts */
DECL|macro|IRQ_AUTO_1
mdefine_line|#define IRQ_AUTO_1        (1)
DECL|macro|IRQ_AUTO_2
mdefine_line|#define IRQ_AUTO_2        (2)
DECL|macro|IRQ_AUTO_3
mdefine_line|#define IRQ_AUTO_3        (3)
DECL|macro|IRQ_AUTO_4
mdefine_line|#define IRQ_AUTO_4        (4)
DECL|macro|IRQ_AUTO_5
mdefine_line|#define IRQ_AUTO_5        (5)
DECL|macro|IRQ_AUTO_6
mdefine_line|#define IRQ_AUTO_6        (6)
DECL|macro|IRQ_AUTO_7
mdefine_line|#define IRQ_AUTO_7        (7)
multiline_comment|/* VIA1 interrupts */
DECL|macro|IRQ_VIA1_0
mdefine_line|#define IRQ_VIA1_0&t;  (8)&t;&t;/* one second int. */
DECL|macro|IRQ_VIA1_1
mdefine_line|#define IRQ_VIA1_1        (9)&t;&t;/* VBlank int. */
DECL|macro|IRQ_MAC_VBL
mdefine_line|#define IRQ_MAC_VBL&t;  IRQ_VIA1_1
DECL|macro|IRQ_VIA1_2
mdefine_line|#define IRQ_VIA1_2 &t;  (10)&t;&t;/* ADB SR shifts complete */
DECL|macro|IRQ_MAC_ADB
mdefine_line|#define IRQ_MAC_ADB&t;  IRQ_VIA1_2
DECL|macro|IRQ_MAC_ADB_SR
mdefine_line|#define IRQ_MAC_ADB_SR&t;  IRQ_VIA1_2
DECL|macro|IRQ_VIA1_3
mdefine_line|#define IRQ_VIA1_3&t;  (11)&t;&t;/* ADB SR CB2 ?? */
DECL|macro|IRQ_MAC_ADB_SD
mdefine_line|#define IRQ_MAC_ADB_SD&t;  IRQ_VIA1_3
DECL|macro|IRQ_VIA1_4
mdefine_line|#define IRQ_VIA1_4        (12)&t;&t;/* ADB SR ext. clock pulse */
DECL|macro|IRQ_MAC_ADB_CL
mdefine_line|#define IRQ_MAC_ADB_CL&t;  IRQ_VIA1_4
DECL|macro|IRQ_VIA1_5
mdefine_line|#define IRQ_VIA1_5&t;  (13)
DECL|macro|IRQ_MAC_TIMER_2
mdefine_line|#define IRQ_MAC_TIMER_2&t;  IRQ_VIA1_5
DECL|macro|IRQ_VIA1_6
mdefine_line|#define IRQ_VIA1_6&t;  (14)
DECL|macro|IRQ_MAC_TIMER_1
mdefine_line|#define IRQ_MAC_TIMER_1&t;  IRQ_VIA1_6
DECL|macro|IRQ_VIA1_7
mdefine_line|#define IRQ_VIA1_7        (15)
multiline_comment|/* VIA2/RBV interrupts */
DECL|macro|IRQ_VIA2_0
mdefine_line|#define IRQ_VIA2_0&t;  (16)
DECL|macro|IRQ_MAC_SCSIDRQ
mdefine_line|#define IRQ_MAC_SCSIDRQ&t;  IRQ_VIA2_0
DECL|macro|IRQ_VIA2_1
mdefine_line|#define IRQ_VIA2_1        (17)
DECL|macro|IRQ_MAC_NUBUS
mdefine_line|#define IRQ_MAC_NUBUS&t;  IRQ_VIA2_1
DECL|macro|IRQ_VIA2_2
mdefine_line|#define IRQ_VIA2_2 &t;  (18)
DECL|macro|IRQ_VIA2_3
mdefine_line|#define IRQ_VIA2_3&t;  (19)
DECL|macro|IRQ_MAC_SCSI
mdefine_line|#define IRQ_MAC_SCSI&t;  IRQ_VIA2_3
DECL|macro|IRQ_VIA2_4
mdefine_line|#define IRQ_VIA2_4        (20)
DECL|macro|IRQ_VIA2_5
mdefine_line|#define IRQ_VIA2_5&t;  (21)
DECL|macro|IRQ_VIA2_6
mdefine_line|#define IRQ_VIA2_6&t;  (22)
DECL|macro|IRQ_VIA2_7
mdefine_line|#define IRQ_VIA2_7        (23)
multiline_comment|/* Level 3 (PSC, AV Macs only) interrupts */
DECL|macro|IRQ_PSC3_0
mdefine_line|#define IRQ_PSC3_0&t;  (24)
DECL|macro|IRQ_MAC_MACE
mdefine_line|#define IRQ_MAC_MACE&t;  IRQ_PSC3_0
DECL|macro|IRQ_PSC3_1
mdefine_line|#define IRQ_PSC3_1&t;  (25)
DECL|macro|IRQ_PSC3_2
mdefine_line|#define IRQ_PSC3_2&t;  (26)
DECL|macro|IRQ_PSC3_3
mdefine_line|#define IRQ_PSC3_3&t;  (27)
multiline_comment|/* Level 4 (SCC) interrupts */
DECL|macro|IRQ_SCC
mdefine_line|#define IRQ_SCC &t;     (32)
DECL|macro|IRQ_SCCA
mdefine_line|#define IRQ_SCCA&t;     (33)
DECL|macro|IRQ_SCCB
mdefine_line|#define IRQ_SCCB&t;     (34)
macro_line|#if 0 /* FIXME: are there multiple interrupt conditions on the SCC ?? */
multiline_comment|/* SCC interrupts */
mdefine_line|#define IRQ_SCCB_TX&t;     (32)
mdefine_line|#define IRQ_SCCB_STAT&t;     (33)
mdefine_line|#define IRQ_SCCB_RX&t;     (34)
mdefine_line|#define IRQ_SCCB_SPCOND&t;     (35)
mdefine_line|#define IRQ_SCCA_TX&t;     (36)
mdefine_line|#define IRQ_SCCA_STAT&t;     (37)
mdefine_line|#define IRQ_SCCA_RX&t;     (38)
mdefine_line|#define IRQ_SCCA_SPCOND&t;     (39)
macro_line|#endif
multiline_comment|/* Level 4 (PSC, AV Macs only) interrupts */
DECL|macro|IRQ_PSC4_0
mdefine_line|#define IRQ_PSC4_0&t;  (32)
DECL|macro|IRQ_PSC4_1
mdefine_line|#define IRQ_PSC4_1&t;  (33)
DECL|macro|IRQ_PSC4_2
mdefine_line|#define IRQ_PSC4_2&t;  (34)
DECL|macro|IRQ_PSC4_3
mdefine_line|#define IRQ_PSC4_3&t;  (35)
DECL|macro|IRQ_MAC_MACE_DMA
mdefine_line|#define IRQ_MAC_MACE_DMA  IRQ_PSC4_3
multiline_comment|/* Level 5 (PSC, AV Macs only) interrupts */
DECL|macro|IRQ_PSC5_0
mdefine_line|#define IRQ_PSC5_0&t;  (40)
DECL|macro|IRQ_PSC5_1
mdefine_line|#define IRQ_PSC5_1&t;  (41)
DECL|macro|IRQ_PSC5_2
mdefine_line|#define IRQ_PSC5_2&t;  (42)
DECL|macro|IRQ_PSC5_3
mdefine_line|#define IRQ_PSC5_3&t;  (43)
multiline_comment|/* Level 6 (PSC, AV Macs only) interrupts */
DECL|macro|IRQ_PSC6_0
mdefine_line|#define IRQ_PSC6_0&t;  (48)
DECL|macro|IRQ_PSC6_1
mdefine_line|#define IRQ_PSC6_1&t;  (49)
DECL|macro|IRQ_PSC6_2
mdefine_line|#define IRQ_PSC6_2&t;  (50)
DECL|macro|IRQ_PSC6_3
mdefine_line|#define IRQ_PSC6_3&t;  (51)
multiline_comment|/* Nubus interrupts (cascaded to VIA2) */
DECL|macro|IRQ_NUBUS_9
mdefine_line|#define IRQ_NUBUS_9&t;  (56)
DECL|macro|IRQ_NUBUS_A
mdefine_line|#define IRQ_NUBUS_A&t;  (57)
DECL|macro|IRQ_NUBUS_B
mdefine_line|#define IRQ_NUBUS_B&t;  (58)
DECL|macro|IRQ_NUBUS_C
mdefine_line|#define IRQ_NUBUS_C&t;  (59)
DECL|macro|IRQ_NUBUS_D
mdefine_line|#define IRQ_NUBUS_D&t;  (60)
DECL|macro|IRQ_NUBUS_E
mdefine_line|#define IRQ_NUBUS_E&t;  (61)
DECL|macro|IRQ_NUBUS_F
mdefine_line|#define IRQ_NUBUS_F&t;  (62)
multiline_comment|/* Baboon interrupts (cascaded to nubus slot $C) */
DECL|macro|IRQ_BABOON_0
mdefine_line|#define IRQ_BABOON_0&t;  (64)
DECL|macro|IRQ_BABOON_1
mdefine_line|#define IRQ_BABOON_1&t;  (65)
DECL|macro|IRQ_BABOON_2
mdefine_line|#define IRQ_BABOON_2&t;  (66)
DECL|macro|IRQ_BABOON_3
mdefine_line|#define IRQ_BABOON_3&t;  (67)
DECL|macro|SLOT2IRQ
mdefine_line|#define SLOT2IRQ(x)&t;  (x + 47)
DECL|macro|IRQ2SLOT
mdefine_line|#define IRQ2SLOT(x)&t;  (x - 47)
DECL|macro|INT_CLK
mdefine_line|#define INT_CLK   24576&t;    /* CLK while int_clk =2.456MHz and divide = 100 */
DECL|macro|INT_TICKS
mdefine_line|#define INT_TICKS 246&t;    /* to make sched_time = 99.902... HZ */
r_extern
id|irq_node_t
op_star
id|mac_irq_list
(braket
id|NUM_MAC_SOURCES
)braket
suffix:semicolon
r_extern
r_void
id|mac_do_irq_list
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* asm/macints.h */
eof
