multiline_comment|/* include/asm-sh/dc_sysasic.h&n; *&n; * Definitions for the Dreamcast System ASIC and related peripherals.&n; *&n; * Copyright (c) 2001 M. R. Brown &lt;mrbrown@linuxdc.org&gt;&n; *&n; * This file is part of the LinuxDC project (www.linuxdc.org)&n; *&n; * Released under the terms of the GNU GPL v2.0.&n; *&n; */
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/* Hardware events -&n;&n;   Each of these events correspond to a bit within the Event Mask Registers/&n;   Event Status Registers.  Because of the virtual IRQ numbering scheme, a&n;   base offset must be used when calculating the virtual IRQ that each event&n;   takes.&n;*/
DECL|macro|HW_EVENT_IRQ_BASE
mdefine_line|#define HW_EVENT_IRQ_BASE  OFFCHIP_IRQ_BASE /* 48 */
multiline_comment|/* IRQ 13 */
DECL|macro|HW_EVENT_VSYNC
mdefine_line|#define HW_EVENT_VSYNC     (HW_EVENT_IRQ_BASE +  5) /* VSync */
DECL|macro|HW_EVENT_MAPLE_DMA
mdefine_line|#define HW_EVENT_MAPLE_DMA (HW_EVENT_IRQ_BASE + 12) /* Maple DMA complete */
DECL|macro|HW_EVENT_GDROM_DMA
mdefine_line|#define HW_EVENT_GDROM_DMA (HW_EVENT_IRQ_BASE + 14) /* GD-ROM DMA complete */
multiline_comment|/* IRQ 11 */
DECL|macro|HW_EVENT_GDROM_CMD
mdefine_line|#define HW_EVENT_GDROM_CMD (HW_EVENT_IRQ_BASE + 32) /* GD-ROM cmd. complete */
DECL|macro|HW_EVENT_AICA_SYS
mdefine_line|#define HW_EVENT_AICA_SYS  (HW_EVENT_IRQ_BASE + 33) /* AICA-related */
DECL|macro|HW_EVENT_EXTERNAL
mdefine_line|#define HW_EVENT_EXTERNAL  (HW_EVENT_IRQ_BASE + 35) /* Ext. (expansion) */
DECL|macro|HW_EVENT_IRQ_MAX
mdefine_line|#define HW_EVENT_IRQ_MAX (HW_EVENT_IRQ_BASE + 95)
eof
