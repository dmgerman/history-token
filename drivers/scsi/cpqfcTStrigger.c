singleline_comment|// Routine to trigger Finisar GTA analyzer. Runs of GPIO2
singleline_comment|// NOTE: DEBUG ONLY! Could interfere with FCMNGR/Miniport operation
singleline_comment|// since it writes directly to the Tachyon board.  This function
singleline_comment|// developed for Compaq HBA Tachyon TS v1.2 (Rev X5 PCB)
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|TriggerHBA
r_void
id|TriggerHBA
c_func
(paren
r_void
op_star
id|IOBaseUpper
comma
r_int
id|Print
)paren
(brace
id|__u32
r_int
id|value
suffix:semicolon
singleline_comment|// get initial value in hopes of not modifying any other GPIO line
id|IOBaseUpper
op_add_assign
l_int|0x188
suffix:semicolon
singleline_comment|// TachTL/TS Control reg
id|value
op_assign
id|readl
c_func
(paren
id|IOBaseUpper
)paren
suffix:semicolon
singleline_comment|// set HIGH to trigger external analyzer (tested on Dolche Finisar 1Gb GTA)
singleline_comment|// The Finisar anaylzer triggers on low-to-high TTL transition
id|value
op_or_assign
l_int|0x01
suffix:semicolon
singleline_comment|// set bit 0
id|writel
c_func
(paren
id|value
comma
id|IOBaseUpper
)paren
suffix:semicolon
r_if
c_cond
(paren
id|Print
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; -GPIO0 set- &quot;
)paren
suffix:semicolon
)brace
)brace
eof
