macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|sh_mv.mv_init_pci
op_ne
l_int|NULL
)paren
(brace
id|sh_mv
dot
id|mv_init_pci
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Haven&squot;t done anything here as yet */
DECL|function|pcibios_setup
r_char
op_star
id|__init
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|str
suffix:semicolon
)brace
multiline_comment|/* We don&squot;t have anything here to fixup */
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)brace
)brace
suffix:semicolon
eof
