multiline_comment|/* $Id: p1275.c,v 1.22 2001/10/18 09:40:00 davem Exp $&n; * p1275.c: Sun IEEE 1275 PROM low level interface routines&n; *&n; * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/spitfire.h&gt;
macro_line|#include &lt;asm/pstate.h&gt;
r_struct
(brace
DECL|member|prom_callback
r_int
id|prom_callback
suffix:semicolon
multiline_comment|/* 0x00 */
DECL|member|prom_cif_handler
r_void
(paren
op_star
id|prom_cif_handler
)paren
(paren
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* 0x08 */
DECL|member|prom_cif_stack
r_int
r_int
id|prom_cif_stack
suffix:semicolon
multiline_comment|/* 0x10 */
DECL|member|prom_args
r_int
r_int
id|prom_args
(braket
l_int|23
)braket
suffix:semicolon
multiline_comment|/* 0x18 */
DECL|member|prom_buffer
r_char
id|prom_buffer
(braket
l_int|3000
)braket
suffix:semicolon
DECL|variable|p1275buf
)brace
id|p1275buf
suffix:semicolon
r_extern
r_void
id|prom_world
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|function|prom_cif_interface
r_void
id|prom_cif_interface
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;mov&t;%0, %%o0&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%o0 + 0x010], %%o1&t;! prom_cif_stack&bslash;n&quot;
l_string|&quot;&t;save&t;%%o1, -0x190, %%sp&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%i0 + 0x008], %%l2&t;! prom_cif_handler&bslash;n&quot;
l_string|&quot;&t;rdpr&t;%%pstate, %%l4&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x15, %%pstate&t;! save alternate globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x0b0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x0b8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x0c0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x0c8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x0d0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x0d8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x0e0]&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x814, %%pstate&t;! save interrupt globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x0e8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x0f0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x0f8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x100]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x108]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x110]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x118]&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x14, %%pstate&t;! save normal globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x120]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x128]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x130]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x138]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x140]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x148]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x150]&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x414, %%pstate&t;! save mmu globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x158]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x160]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x168]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x170]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x178]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x180]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x188]&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g1, %%l0&t;&t;! also save to locals, so we can handle&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g2, %%l1&t;&t;! tlb faults later on, when accessing&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g3, %%l3&t;&t;! the stack.&bslash;n&quot;
l_string|&quot;&t;mov&t;%%g7, %%l5&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%l4, %1, %%pstate&t;! turn off interrupts&bslash;n&quot;
l_string|&quot;&t;call&t;%%l2&bslash;n&quot;
l_string|&quot;&t; add&t;%%i0, 0x018, %%o0&t;! prom_args&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x414, %%pstate&t;! restore mmu globals&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l0, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l1, %%g2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l3, %%g3&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l5, %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x14, %%pstate&t;! restore normal globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x120], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x128], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x130], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x138], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x140], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x148], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x150], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x814, %%pstate&t;! restore interrupt globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0e8], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0f0], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0f8], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x100], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x108], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x110], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x118], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x15, %%pstate&t;! restore alternate globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0b0], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0b8], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0c0], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0c8], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0d0], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0d8], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0e0], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%l4, 0, %%pstate&t;! restore original pstate&bslash;n&quot;
l_string|&quot;&t;ret&bslash;n&quot;
l_string|&quot;&t; restore&bslash;n&quot;
l_string|&quot;&t;&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|p1275buf
)paren
comma
l_string|&quot;i&quot;
(paren
id|PSTATE_IE
)paren
)paren
suffix:semicolon
)brace
DECL|function|prom_cif_callback
r_void
id|prom_cif_callback
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;&t;mov&t;%0, %%o1&bslash;n&quot;
l_string|&quot;&t;save&t;%%sp, -0x270, %%sp&bslash;n&quot;
l_string|&quot;&t;rdpr&t;%%pstate, %%l4&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x15, %%pstate&t;! save PROM alternate globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x0b0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x0b8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x0c0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x0c8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x0d0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x0d8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x0e0]&bslash;n&quot;
l_string|&quot;&t;&t;&t;&t;&t;! restore Linux alternate globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x190], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x198], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1a0], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1a8], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1b0], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1b8], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1c0], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x814, %%pstate&t;! save PROM interrupt globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x0e8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x0f0]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x0f8]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x100]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x108]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x110]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x118]&bslash;n&quot;
l_string|&quot;&t;&t;&t;&t;&t;! restore Linux interrupt globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1c8], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1d0], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1d8], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1e0], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1e8], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1f0], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x1f8], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x14, %%pstate&t;! save PROM normal globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x120]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x128]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x130]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x138]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x140]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x148]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x150]&bslash;n&quot;
l_string|&quot;&t;&t;&t;&t;&t;! restore Linux normal globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x200], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x208], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x210], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x218], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x220], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x228], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x230], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x414, %%pstate&t;! save PROM mmu globals&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g1, [%%sp + 2047 + 0x158]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g2, [%%sp + 2047 + 0x160]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g3, [%%sp + 2047 + 0x168]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g4, [%%sp + 2047 + 0x170]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g5, [%%sp + 2047 + 0x178]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g6, [%%sp + 2047 + 0x180]&bslash;n&quot;
l_string|&quot;&t;stx&t;%%g7, [%%sp + 2047 + 0x188]&bslash;n&quot;
l_string|&quot;&t;&t;&t;&t;&t;! restore Linux mmu globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x238], %%o0&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x240], %%o1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x248], %%l2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x250], %%l3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x258], %%l5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x260], %%l6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x268], %%l7&bslash;n&quot;
l_string|&quot;&t;&t;&t;&t;&t;! switch to Linux tba&bslash;n&quot;
l_string|&quot;&t;sethi&t;%%hi(sparc64_ttable_tl0), %%l1&bslash;n&quot;
l_string|&quot;&t;rdpr&t;%%tba, %%l0&t;&t;! save PROM tba&bslash;n&quot;
l_string|&quot;&t;mov&t;%%o0, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%o1, %%g2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g3&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l3, %%g4&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l5, %%g5&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l6, %%g6&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l7, %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%l1, %%tba&t;&t;! install Linux tba&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%l4, 0, %%pstate&t;! restore PSTATE&bslash;n&quot;
l_string|&quot;&t;call&t;prom_world&bslash;n&quot;
l_string|&quot;&t; mov&t;%%g0, %%o0&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%i1 + 0x000], %%l2&bslash;n&quot;
l_string|&quot;&t;call&t;%%l2&bslash;n&quot;
l_string|&quot;&t; mov&t;%%i0, %%o0&bslash;n&quot;
l_string|&quot;&t;mov&t;%%o0, %%l1&bslash;n&quot;
l_string|&quot;&t;call&t;prom_world&bslash;n&quot;
l_string|&quot;&t; or&t;%%g0, 1, %%o0&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x14, %%pstate&t;! interrupts off&bslash;n&quot;
l_string|&quot;&t;&t;&t;&t;&t;! restore PROM mmu globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x158], %%o0&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x160], %%o1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x168], %%l2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x170], %%l3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x178], %%l5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x180], %%l6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x188], %%l7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x414, %%pstate&t;! restore PROM mmu globals&bslash;n&quot;
l_string|&quot;&t;mov&t;%%o0, %%g1&bslash;n&quot;
l_string|&quot;&t;mov&t;%%o1, %%g2&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l2, %%g3&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l3, %%g4&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l5, %%g5&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l6, %%g6&bslash;n&quot;
l_string|&quot;&t;mov&t;%%l7, %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%l0, %%tba&t;&t;! restore PROM tba&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x14, %%pstate&t;! restore PROM normal globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x120], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x128], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x130], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x138], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x140], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x148], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x150], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x814, %%pstate&t;! restore PROM interrupt globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0e8], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0f0], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0f8], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x100], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x108], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x110], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x118], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%g0, 0x15, %%pstate&t;! restore PROM alternate globals&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0b0], %%g1&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0b8], %%g2&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0c0], %%g3&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0c8], %%g4&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0d0], %%g5&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0d8], %%g6&bslash;n&quot;
l_string|&quot;&t;ldx&t;[%%sp + 2047 + 0x0e0], %%g7&bslash;n&quot;
l_string|&quot;&t;wrpr&t;%%l4, 0, %%pstate&bslash;n&quot;
l_string|&quot;&t;ret&bslash;n&quot;
l_string|&quot;&t; restore %%l1, 0, %%o0&bslash;n&quot;
l_string|&quot;&t;&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|p1275buf
)paren
comma
l_string|&quot;i&quot;
(paren
id|PSTATE_PRIV
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This provides SMP safety on the p1275buf. prom_callback() drops this lock&n; * to allow recursuve acquisition.&n; */
DECL|variable|prom_entry_lock
id|spinlock_t
id|prom_entry_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|p1275_cmd
r_int
id|p1275_cmd
(paren
r_char
op_star
id|service
comma
r_int
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|nargs
comma
id|nrets
comma
id|i
suffix:semicolon
id|va_list
id|list
suffix:semicolon
r_int
id|attrs
comma
id|x
suffix:semicolon
r_int
id|ctx
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|p1275buf.prom_buffer
suffix:semicolon
id|ctx
op_assign
id|spitfire_get_primary_context
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx
)paren
(brace
id|flushw_user
(paren
)paren
suffix:semicolon
id|spitfire_set_primary_context
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|prom_entry_lock
comma
id|flags
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
l_int|0
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
multiline_comment|/* service */
id|strcpy
(paren
id|p
comma
id|service
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|strchr
(paren
id|p
comma
l_int|0
)paren
op_plus
l_int|8
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
l_int|1
)braket
op_assign
id|nargs
op_assign
(paren
id|fmt
op_amp
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* nargs */
id|p1275buf.prom_args
(braket
l_int|2
)braket
op_assign
id|nrets
op_assign
(paren
(paren
id|fmt
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
multiline_comment|/* nrets */
id|attrs
op_assign
id|fmt
op_rshift
l_int|8
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|fmt
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nargs
suffix:semicolon
id|i
op_increment
comma
id|attrs
op_rshift_assign
l_int|3
)paren
(brace
r_switch
c_cond
(paren
id|attrs
op_amp
l_int|0x7
)paren
(brace
r_case
id|P1275_ARG_NUMBER
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_64B
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_STRING
suffix:colon
id|strcpy
(paren
id|p
comma
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|strchr
(paren
id|p
comma
l_int|0
)paren
op_plus
l_int|8
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_BUF
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|p
op_plus
(paren
r_int
)paren
id|x
op_plus
l_int|7
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_BUF
suffix:colon
id|q
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
id|memcpy
(paren
id|p
comma
id|q
comma
(paren
r_int
)paren
id|x
)paren
suffix:semicolon
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
)paren
(paren
id|p
op_plus
(paren
r_int
)paren
id|x
op_plus
l_int|7
)paren
)paren
op_amp
op_complement
l_int|7
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
id|x
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_32B
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p
op_add_assign
l_int|32
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_FUNCTION
suffix:colon
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
id|prom_cif_callback
suffix:semicolon
id|p1275buf.prom_callback
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|prom_world
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|prom_cif_interface
c_func
(paren
)paren
suffix:semicolon
id|prom_world
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|attrs
op_assign
id|fmt
op_rshift
l_int|8
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|fmt
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nargs
suffix:semicolon
id|i
op_increment
comma
id|attrs
op_rshift_assign
l_int|3
)paren
(brace
r_switch
c_cond
(paren
id|attrs
op_amp
l_int|0x7
)paren
(brace
r_case
id|P1275_ARG_NUMBER
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_STRING
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_FUNCTION
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_IN_BUF
suffix:colon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
(paren
r_void
)paren
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_BUF
suffix:colon
id|p
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|x
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_int
)paren
suffix:semicolon
id|memcpy
(paren
id|p
comma
(paren
r_char
op_star
)paren
(paren
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
)paren
comma
(paren
r_int
)paren
id|x
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|attrs
op_rshift_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_case
id|P1275_ARG_OUT_32B
suffix:colon
id|p
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_char
op_star
)paren
suffix:semicolon
id|memcpy
(paren
id|p
comma
(paren
r_char
op_star
)paren
(paren
id|p1275buf.prom_args
(braket
id|i
op_plus
l_int|3
)braket
)paren
comma
l_int|32
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|list
)paren
suffix:semicolon
id|x
op_assign
id|p1275buf.prom_args
(braket
id|nargs
op_plus
l_int|3
)braket
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|prom_entry_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ctx
)paren
id|spitfire_set_primary_context
(paren
id|ctx
)paren
suffix:semicolon
r_return
id|x
suffix:semicolon
)brace
DECL|function|prom_cif_init
r_void
id|prom_cif_init
c_func
(paren
r_void
op_star
id|cif_handler
comma
r_void
op_star
id|cif_stack
)paren
(brace
id|p1275buf.prom_cif_handler
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_int
op_star
)paren
)paren
id|cif_handler
suffix:semicolon
id|p1275buf.prom_cif_stack
op_assign
(paren
r_int
r_int
)paren
id|cif_stack
suffix:semicolon
)brace
eof
