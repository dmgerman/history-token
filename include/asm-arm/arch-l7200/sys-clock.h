multiline_comment|/****************************************************************************/
multiline_comment|/*&n; *  linux/include/asm-arm/arch-l7200/sys-clock.h&n; *&n; *   Registers and  helper functions for the L7200 Link-Up Systems&n; *   System clocks.&n; *&n; *   (C) Copyright 2000, S A McConnell  (samcconn@cotw.com)&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/****************************************************************************/
DECL|macro|SYS_CLOCK_OFF
mdefine_line|#define SYS_CLOCK_OFF   0x00050030  /* Offset from IO_START. */
multiline_comment|/* IO_START and IO_BASE are defined in hardware.h */
DECL|macro|SYS_CLOCK_START
mdefine_line|#define SYS_CLOCK_START (IO_START + SYS_CLCOK_OFF)  /* Physical address */
DECL|macro|SYS_CLOCK_BASE
mdefine_line|#define SYS_CLOCK_BASE  (IO_BASE  + SYS_CLOCK_OFF)  /* Virtual address  */
multiline_comment|/* Define the interface to the SYS_CLOCK */
r_typedef
r_struct
(brace
DECL|member|ENABLE
r_int
r_int
id|ENABLE
suffix:semicolon
DECL|member|ESYNC
r_int
r_int
id|ESYNC
suffix:semicolon
DECL|member|SELECT
r_int
r_int
id|SELECT
suffix:semicolon
DECL|typedef|sys_clock_interface
)brace
id|sys_clock_interface
suffix:semicolon
DECL|macro|SYS_CLOCK
mdefine_line|#define SYS_CLOCK   ((volatile sys_clock_interface *)(SYS_CLOCK_BASE))
singleline_comment|//#define CLOCK_EN    (*(volatile unsigned long *)(PMU_BASE+CLOCK_EN_OFF))
singleline_comment|//#define CLOCK_ESYNC (*(volatile unsigned long *)(PMU_BASE+CLOCK_ESYNC_OFF))
singleline_comment|//#define CLOCK_SEL   (*(volatile unsigned long *)(PMU_BASE+CLOCK_SEL_OFF))
multiline_comment|/* SYS_CLOCK -&gt; ENABLE */
DECL|macro|SYN_EN
mdefine_line|#define SYN_EN          1&lt;&lt;0
DECL|macro|B18M_EN
mdefine_line|#define B18M_EN         1&lt;&lt;1
DECL|macro|CLK3M6_EN
mdefine_line|#define CLK3M6_EN       1&lt;&lt;2
DECL|macro|BUART_EN
mdefine_line|#define BUART_EN        1&lt;&lt;3
DECL|macro|CLK18MU_EN
mdefine_line|#define CLK18MU_EN      1&lt;&lt;4
DECL|macro|FIR_EN
mdefine_line|#define FIR_EN          1&lt;&lt;5
DECL|macro|MIRN_EN
mdefine_line|#define MIRN_EN         1&lt;&lt;6
DECL|macro|UARTM_EN
mdefine_line|#define UARTM_EN        1&lt;&lt;7
DECL|macro|SIBADC_EN
mdefine_line|#define SIBADC_EN       1&lt;&lt;8
DECL|macro|ALTD_EN
mdefine_line|#define ALTD_EN         1&lt;&lt;9
DECL|macro|CLCLK_EN
mdefine_line|#define CLCLK_EN        1&lt;&lt;10
multiline_comment|/* SYS_CLOCK -&gt; SELECT */
DECL|macro|CLK18M_DIV
mdefine_line|#define CLK18M_DIV      1&lt;&lt;0
DECL|macro|MIR_SEL
mdefine_line|#define MIR_SEL         1&lt;&lt;1
DECL|macro|SSP_SEL
mdefine_line|#define SSP_SEL         1&lt;&lt;4
DECL|macro|MM_DIV
mdefine_line|#define MM_DIV          1&lt;&lt;5
DECL|macro|MM_SEL
mdefine_line|#define MM_SEL          1&lt;&lt;6
DECL|macro|ADC_SEL_2
mdefine_line|#define ADC_SEL_2       0&lt;&lt;7
DECL|macro|ADC_SEL_4
mdefine_line|#define ADC_SEL_4       1&lt;&lt;7
DECL|macro|ADC_SEL_8
mdefine_line|#define ADC_SEL_8       3&lt;&lt;7
DECL|macro|ADC_SEL_16
mdefine_line|#define ADC_SEL_16      7&lt;&lt;7
DECL|macro|ADC_SEL_32
mdefine_line|#define ADC_SEL_32      0x0f&lt;&lt;7
DECL|macro|ADC_SEL_64
mdefine_line|#define ADC_SEL_64      0x1f&lt;&lt;7
DECL|macro|ADC_SEL_128
mdefine_line|#define ADC_SEL_128     0x3f&lt;&lt;7
DECL|macro|ALTD_SEL
mdefine_line|#define ALTD_SEL        1&lt;&lt;13
eof
