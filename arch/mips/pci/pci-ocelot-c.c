multiline_comment|/*&n; * Copyright 2002 Momentum Computer&n; * Author: Matthew Dharm &lt;mdharm@momenco.com&gt;&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mv64340.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * These functions and structures provide the BIOS scan and mapping of the PCI&n; * devices.&n; */
r_void
id|mv64340_board_pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|c
)paren
suffix:semicolon
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
)brace
)brace
suffix:semicolon
DECL|function|pcibios_fixup_bus
r_void
id|__init
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|c
)paren
(brace
id|mv64340_board_pcibios_fixup_bus
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Reset PCI I/O and PCI MEM values */
id|ioport_resource.start
op_assign
l_int|0xe0000000
suffix:semicolon
id|ioport_resource.end
op_assign
l_int|0xe0000000
op_plus
l_int|0x20000000
op_minus
l_int|1
suffix:semicolon
id|iomem_resource.start
op_assign
l_int|0xc0000000
suffix:semicolon
id|iomem_resource.end
op_assign
l_int|0xc0000000
op_plus
l_int|0x20000000
op_minus
l_int|1
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|0
comma
op_amp
id|mv64340_bus0_pci_ops
comma
l_int|NULL
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
l_int|1
comma
op_amp
id|mv64340_bus1_pci_ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
