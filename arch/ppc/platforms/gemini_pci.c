macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;platforms/gemini.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
DECL|function|gemini_pcibios_fixup
r_void
id|__init
id|gemini_pcibios_fixup
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|for_each_pci_dev
c_func
(paren
id|dev
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
)paren
(brace
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_or_assign
(paren
l_int|0xfe
op_lshift
l_int|24
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_or_assign
(paren
l_int|0xfe
op_lshift
l_int|24
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/* The &quot;bootloader&quot; for Synergy boards does none of this for us, so we need to&n;   lay it all out ourselves... --Dan */
DECL|function|gemini_find_bridges
r_void
id|__init
id|gemini_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
id|ppc_md.pcibios_fixup
op_assign
id|gemini_pcibios_fixup
suffix:semicolon
id|hose
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
suffix:semicolon
id|setup_indirect_pci
c_func
(paren
id|hose
comma
l_int|0xfec00000
comma
l_int|0xfee00000
)paren
suffix:semicolon
)brace
eof
