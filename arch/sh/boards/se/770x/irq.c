multiline_comment|/* $Id: irq.c,v 1.1.2.2 2002/10/29 00:56:09 lethal Exp $&n; * &n; * linux/arch/sh/boards/se/770x/irq.c&n; *&n; * Copyright (C) 2000  Kazumoto Kojima&n; *&n; * Hitachi SolutionEngine Support.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hitachi_se.h&gt;
multiline_comment|/*&n; * Initialize IRQ setting&n; */
DECL|function|init_se_IRQ
r_void
id|__init
id|init_se_IRQ
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;         * Super I/O (Just mimic PC):&n;         *  1: keyboard&n;         *  3: serial 0&n;         *  4: serial 1&n;         *  5: printer&n;         *  6: floppy&n;         *  8: rtc&n;         * 12: mouse&n;         * 14: ide0&n;         */
id|make_ipr_irq
c_func
(paren
l_int|14
comma
id|BCR_ILCRA
comma
l_int|2
comma
l_int|0x0f
op_minus
l_int|14
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|12
comma
id|BCR_ILCRA
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|12
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|8
comma
id|BCR_ILCRB
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|8
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|6
comma
id|BCR_ILCRC
comma
l_int|3
comma
l_int|0x0f
op_minus
l_int|6
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|5
comma
id|BCR_ILCRC
comma
l_int|2
comma
l_int|0x0f
op_minus
l_int|5
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|4
comma
id|BCR_ILCRC
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|4
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|3
comma
id|BCR_ILCRC
comma
l_int|0
comma
l_int|0x0f
op_minus
l_int|3
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|1
comma
id|BCR_ILCRD
comma
l_int|3
comma
l_int|0x0f
op_minus
l_int|1
)paren
suffix:semicolon
id|make_ipr_irq
c_func
(paren
l_int|10
comma
id|BCR_ILCRD
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|10
)paren
suffix:semicolon
multiline_comment|/* LAN */
id|make_ipr_irq
c_func
(paren
l_int|0
comma
id|BCR_ILCRE
comma
l_int|3
comma
l_int|0x0f
op_minus
l_int|0
)paren
suffix:semicolon
multiline_comment|/* PCIRQ3 */
id|make_ipr_irq
c_func
(paren
l_int|11
comma
id|BCR_ILCRE
comma
l_int|2
comma
l_int|0x0f
op_minus
l_int|11
)paren
suffix:semicolon
multiline_comment|/* PCIRQ2 */
id|make_ipr_irq
c_func
(paren
l_int|9
comma
id|BCR_ILCRE
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|9
)paren
suffix:semicolon
multiline_comment|/* PCIRQ1 */
id|make_ipr_irq
c_func
(paren
l_int|7
comma
id|BCR_ILCRE
comma
l_int|0
comma
l_int|0x0f
op_minus
l_int|7
)paren
suffix:semicolon
multiline_comment|/* PCIRQ0 */
multiline_comment|/* #2, #13 are allocated for SLOT IRQ #1 and #2 (for now) */
multiline_comment|/* NOTE: #2 and #13 are not used on PC */
id|make_ipr_irq
c_func
(paren
l_int|13
comma
id|BCR_ILCRG
comma
l_int|1
comma
l_int|0x0f
op_minus
l_int|13
)paren
suffix:semicolon
multiline_comment|/* SLOTIRQ2 */
id|make_ipr_irq
c_func
(paren
l_int|2
comma
id|BCR_ILCRG
comma
l_int|0
comma
l_int|0x0f
op_minus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* SLOTIRQ1 */
)brace
eof
