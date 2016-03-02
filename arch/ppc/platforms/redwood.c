multiline_comment|/*&n; *&n; *    Copyright 2000-2001 MontaVista Software Inc.&n; *      Completed implementation.&n; *      Author: MontaVista Software, Inc.  &lt;source@mvista.com&gt;&n; *              Frank Rowand &lt;frank_rowand@mvista.com&gt;&n; *&n; *    Module name: redwood.c&n; *&n; *    Description:&n; *&n; *      History:  11/09/2001 - Armin&n; *      added board_init to add in additional instuctions needed during platfrom_init&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
r_void
id|__init
DECL|function|board_setup_arch
id|board_setup_arch
c_func
(paren
r_void
)paren
(brace
)brace
r_void
id|__init
DECL|function|board_io_mapping
id|board_io_mapping
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|io_block_mapping
c_func
(paren
id|OAKNET_IO_VADDR
comma
id|OAKNET_IO_PADDR
comma
id|OAKNET_IO_SIZE
comma
id|_PAGE_IO
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|board_setup_irq
id|board_setup_irq
c_func
(paren
r_void
)paren
(brace
)brace
r_void
id|__init
DECL|function|board_init
id|board_init
c_func
(paren
r_void
)paren
(brace
)brace
eof
