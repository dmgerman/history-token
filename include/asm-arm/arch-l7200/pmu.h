multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-arm/arch-l7200/pmu.h&n; *&n; *   Registers and  helper functions for the L7200 Link-Up Systems&n; *   Power Management Unit (PMU).&n; *&n; *   (C) Copyright 2000, S A McConnell  (samcconn@cotw.com)&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/****************************************************************************/
DECL|macro|PMU_OFF
mdefine_line|#define PMU_OFF   0x00050000  /* Offset from IO_START to the PMU registers. */
multiline_comment|/* IO_START and IO_BASE are defined in hardware.h */
DECL|macro|PMU_START
mdefine_line|#define PMU_START (IO_START + PMU_OFF)  /* Physical addr. of the PMU reg. */
DECL|macro|PMU_BASE
mdefine_line|#define PMU_BASE  (IO_BASE  + PMU_OFF)  /* Virtual addr. of the PMU reg. */
multiline_comment|/* Define the PMU registers for use by device drivers and the kernel. */
r_typedef
r_struct
(brace
DECL|member|CURRENT
r_int
r_int
id|CURRENT
suffix:semicolon
multiline_comment|/* Current configuration register */
DECL|member|NEXT
r_int
r_int
id|NEXT
suffix:semicolon
multiline_comment|/* Next configuration register */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
DECL|member|RUN
r_int
r_int
id|RUN
suffix:semicolon
multiline_comment|/* Run configuration register */
DECL|member|COMM
r_int
r_int
id|COMM
suffix:semicolon
multiline_comment|/* Configuration command register */
DECL|member|SDRAM
r_int
r_int
id|SDRAM
suffix:semicolon
multiline_comment|/* SDRAM configuration bypass register */
DECL|typedef|pmu_interface
)brace
id|pmu_interface
suffix:semicolon
DECL|macro|PMU
mdefine_line|#define PMU ((volatile pmu_interface *)(PMU_BASE))
multiline_comment|/* Macro&squot;s for reading the common register fields. */
DECL|macro|GET_TRANSOP
mdefine_line|#define GET_TRANSOP(reg)  ((reg &gt;&gt; 25) &amp; 0x03) /* Bits 26-25 */
DECL|macro|GET_OSCEN
mdefine_line|#define GET_OSCEN(reg)    ((reg &gt;&gt; 16) &amp; 0x01)
DECL|macro|GET_OSCMUX
mdefine_line|#define GET_OSCMUX(reg)   ((reg &gt;&gt; 15) &amp; 0x01)
DECL|macro|GET_PLLMUL
mdefine_line|#define GET_PLLMUL(reg)   ((reg &gt;&gt;  9) &amp; 0x3f) /* Bits 14-9 */
DECL|macro|GET_PLLEN
mdefine_line|#define GET_PLLEN(reg)    ((reg &gt;&gt;  8) &amp; 0x01)
DECL|macro|GET_PLLMUX
mdefine_line|#define GET_PLLMUX(reg)   ((reg &gt;&gt;  7) &amp; 0x01)
DECL|macro|GET_BCLK_DIV
mdefine_line|#define GET_BCLK_DIV(reg) ((reg &gt;&gt;  3) &amp; 0x03) /* Bits 4-3 */
DECL|macro|GET_SDRB_SEL
mdefine_line|#define GET_SDRB_SEL(reg) ((reg &gt;&gt;  2) &amp; 0x01)
DECL|macro|GET_SDRF_SEL
mdefine_line|#define GET_SDRF_SEL(reg) ((reg &gt;&gt;  1) &amp; 0x01)
DECL|macro|GET_FASTBUS
mdefine_line|#define GET_FASTBUS(reg)  (reg &amp; 0x1)
multiline_comment|/* CFG_NEXT register */
DECL|macro|CFG_NEXT_CLOCKRECOVERY
mdefine_line|#define CFG_NEXT_CLOCKRECOVERY ((PMU-&gt;NEXT &gt;&gt; 18) &amp; 0x7f)   /* Bits 24-18 */
DECL|macro|CFG_NEXT_INTRET
mdefine_line|#define CFG_NEXT_INTRET        ((PMU-&gt;NEXT &gt;&gt; 17) &amp; 0x01)
DECL|macro|CFG_NEXT_SDR_STOP
mdefine_line|#define CFG_NEXT_SDR_STOP      ((PMU-&gt;NEXT &gt;&gt;  6) &amp; 0x01)
DECL|macro|CFG_NEXT_SYSCLKEN
mdefine_line|#define CFG_NEXT_SYSCLKEN      ((PMU-&gt;NEXT &gt;&gt;  5) &amp; 0x01)
multiline_comment|/* Useful field values that can be used to construct the&n; * CFG_NEXT and CFG_RUN registers.&n; */
DECL|macro|TRANSOP_NOP
mdefine_line|#define TRANSOP_NOP      0&lt;&lt;25  /* NOCHANGE_NOSTALL */
DECL|macro|NOCHANGE_STALL
mdefine_line|#define NOCHANGE_STALL   1&lt;&lt;25
DECL|macro|CHANGE_NOSTALL
mdefine_line|#define CHANGE_NOSTALL   2&lt;&lt;25
DECL|macro|CHANGE_STALL
mdefine_line|#define CHANGE_STALL     3&lt;&lt;25
DECL|macro|INTRET
mdefine_line|#define INTRET           1&lt;&lt;17
DECL|macro|OSCEN
mdefine_line|#define OSCEN            1&lt;&lt;16
DECL|macro|OSCMUX
mdefine_line|#define OSCMUX           1&lt;&lt;15
multiline_comment|/* PLL frequencies */
DECL|macro|PLLMUL_0
mdefine_line|#define PLLMUL_0         0&lt;&lt;9         /*  3.6864 MHz */
DECL|macro|PLLMUL_1
mdefine_line|#define PLLMUL_1         1&lt;&lt;9         /*  ?????? MHz */
DECL|macro|PLLMUL_5
mdefine_line|#define PLLMUL_5         5&lt;&lt;9         /*  18.432 MHz */
DECL|macro|PLLMUL_10
mdefine_line|#define PLLMUL_10       10&lt;&lt;9         /*  36.864 MHz */
DECL|macro|PLLMUL_18
mdefine_line|#define PLLMUL_18       18&lt;&lt;9         /*  ?????? MHz */
DECL|macro|PLLMUL_20
mdefine_line|#define PLLMUL_20       20&lt;&lt;9         /*  73.728 MHz */
DECL|macro|PLLMUL_32
mdefine_line|#define PLLMUL_32       32&lt;&lt;9         /*  ?????? MHz */
DECL|macro|PLLMUL_35
mdefine_line|#define PLLMUL_35       35&lt;&lt;9         /* 129.024 MHz */
DECL|macro|PLLMUL_36
mdefine_line|#define PLLMUL_36       36&lt;&lt;9         /*  ?????? MHz */
DECL|macro|PLLMUL_39
mdefine_line|#define PLLMUL_39       39&lt;&lt;9         /*  ?????? MHz */
DECL|macro|PLLMUL_40
mdefine_line|#define PLLMUL_40       40&lt;&lt;9         /* 147.456 MHz */
multiline_comment|/* Clock recovery times */
DECL|macro|CRCLOCK_1
mdefine_line|#define CRCLOCK_1        1&lt;&lt;18
DECL|macro|CRCLOCK_2
mdefine_line|#define CRCLOCK_2        2&lt;&lt;18
DECL|macro|CRCLOCK_4
mdefine_line|#define CRCLOCK_4        4&lt;&lt;18
DECL|macro|CRCLOCK_8
mdefine_line|#define CRCLOCK_8        8&lt;&lt;18
DECL|macro|CRCLOCK_16
mdefine_line|#define CRCLOCK_16      16&lt;&lt;18
DECL|macro|CRCLOCK_32
mdefine_line|#define CRCLOCK_32      32&lt;&lt;18
DECL|macro|CRCLOCK_63
mdefine_line|#define CRCLOCK_63      63&lt;&lt;18
DECL|macro|CRCLOCK_127
mdefine_line|#define CRCLOCK_127    127&lt;&lt;18
DECL|macro|PLLEN
mdefine_line|#define PLLEN            1&lt;&lt;8
DECL|macro|PLLMUX
mdefine_line|#define PLLMUX           1&lt;&lt;7
DECL|macro|SDR_STOP
mdefine_line|#define SDR_STOP         1&lt;&lt;6
DECL|macro|SYSCLKEN
mdefine_line|#define SYSCLKEN         1&lt;&lt;5
DECL|macro|BCLK_DIV_4
mdefine_line|#define BCLK_DIV_4       2&lt;&lt;3
DECL|macro|BCLK_DIV_2
mdefine_line|#define BCLK_DIV_2       1&lt;&lt;3
DECL|macro|BCLK_DIV_1
mdefine_line|#define BCLK_DIV_1       0&lt;&lt;3
DECL|macro|SDRB_SEL
mdefine_line|#define SDRB_SEL         1&lt;&lt;2
DECL|macro|SDRF_SEL
mdefine_line|#define SDRF_SEL         1&lt;&lt;1
DECL|macro|FASTBUS
mdefine_line|#define FASTBUS          1&lt;&lt;0
multiline_comment|/* CFG_SDRAM */
DECL|macro|SDRREFFQ
mdefine_line|#define SDRREFFQ         1&lt;&lt;0  /* Only if SDRSTOPRQ is not set. */
DECL|macro|SDRREFACK
mdefine_line|#define SDRREFACK        1&lt;&lt;1  /* Read-only */
DECL|macro|SDRSTOPRQ
mdefine_line|#define SDRSTOPRQ        1&lt;&lt;2  /* Only if SDRREFFQ is not set. */
DECL|macro|SDRSTOPACK
mdefine_line|#define SDRSTOPACK       1&lt;&lt;3  /* Read-only */
DECL|macro|PICEN
mdefine_line|#define PICEN            1&lt;&lt;4  /* Enable Co-procesor */
DECL|macro|PICTEST
mdefine_line|#define PICTEST          1&lt;&lt;5
DECL|macro|GET_SDRREFFQ
mdefine_line|#define GET_SDRREFFQ    ((PMU-&gt;SDRAM &gt;&gt; 0) &amp; 0x01)
DECL|macro|GET_SDRREFACK
mdefine_line|#define GET_SDRREFACK   ((PMU-&gt;SDRAM &gt;&gt; 1) &amp; 0x01) /* Read-only */
DECL|macro|GET_SDRSTOPRQ
mdefine_line|#define GET_SDRSTOPRQ   ((PMU-&gt;SDRAM &gt;&gt; 2) &amp; 0x01)
DECL|macro|GET_SDRSTOPACK
mdefine_line|#define GET_SDRSTOPACK  ((PMU-&gt;SDRAM &gt;&gt; 3) &amp; 0x01) /* Read-only */
DECL|macro|GET_PICEN
mdefine_line|#define GET_PICEN       ((PMU-&gt;SDRAM &gt;&gt; 4) &amp; 0x01)
DECL|macro|GET_PICTEST
mdefine_line|#define GET_PICTEST     ((PMU-&gt;SDRAM &gt;&gt; 5) &amp; 0x01)
eof
