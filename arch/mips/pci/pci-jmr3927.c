multiline_comment|/*&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *              ahennessy@mvista.com&n; *&n; * Copyright (C) 2000-2001 Toshiba Corporation&n; * Copyright (C) 2004 by Ralf Baechle (ralf@linux-mips.org)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/jmr3927/jmr3927.h&gt;
macro_line|#include &lt;asm/debug.h&gt;
DECL|variable|pci_io_resource
r_struct
id|resource
id|pci_io_resource
op_assign
(brace
l_string|&quot;IO MEM&quot;
comma
l_int|0x1000
comma
multiline_comment|/* reserve regacy I/O space */
l_int|0x1000
op_plus
id|JMR3927_PCIIO_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|pci_mem_resource
r_struct
id|resource
id|pci_mem_resource
op_assign
(brace
l_string|&quot;PCI MEM&quot;
comma
id|JMR3927_PCIMEM
comma
id|JMR3927_PCIMEM
op_plus
id|JMR3927_PCIMEM_SIZE
op_minus
l_int|1
comma
id|IORESOURCE_MEM
)brace
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|jmr3927_pci_ops
suffix:semicolon
DECL|variable|jmr3927_controller
r_struct
id|pci_controller
id|jmr3927_controller
op_assign
(brace
dot
id|pci_ops
op_assign
op_amp
id|jmr3927_pci_ops
comma
dot
id|io_resource
op_assign
op_amp
id|pci_io_resource
comma
dot
id|mem_resource
op_assign
op_amp
id|pci_mem_resource
comma
dot
id|mem_offset
op_assign
id|JMR3927_PCIMEM
suffix:semicolon
)brace
suffix:semicolon
eof
