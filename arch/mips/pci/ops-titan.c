multiline_comment|/*&n; * Copyright 2003 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; *  This program is free software; you can redistribute&t; it and/or modify it&n; *  under  the terms of&t; the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the&t;License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED&t;  ``AS&t;IS&squot;&squot; AND   ANY&t;EXPRESS OR IMPLIED&n; *  WARRANTIES,&t;  INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO&t;EVENT  SHALL   THE AUTHOR  BE&t; LIABLE FOR ANY&t;  DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED&t;  TO, PROCUREMENT OF  SUBSTITUTE GOODS&t;OR SERVICES; LOSS OF&n; *  USE, DATA,&t;OR PROFITS; OR&t;BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN&t; CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/titan_dep.h&gt;
multiline_comment|/*&n; * Titan PCI Config Read Byte&n; */
DECL|function|titan_read_config
r_static
r_int
id|titan_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|reg
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
(brace
r_int
id|dev
comma
id|busno
comma
id|func
suffix:semicolon
r_uint32
id|address_reg
comma
id|data_reg
suffix:semicolon
r_uint32
id|address
suffix:semicolon
id|busno
op_assign
id|bus-&gt;number
suffix:semicolon
id|dev
op_assign
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|func
op_assign
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|address_reg
op_assign
id|TITAN_PCI_0_CONFIG_ADDRESS
suffix:semicolon
id|data_reg
op_assign
id|TITAN_PCI_0_CONFIG_DATA
suffix:semicolon
id|address
op_assign
(paren
id|busno
op_lshift
l_int|16
)paren
op_or
(paren
id|dev
op_lshift
l_int|11
)paren
op_or
(paren
id|func
op_lshift
l_int|8
)paren
op_or
(paren
id|reg
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
suffix:semicolon
multiline_comment|/* start the configuration cycle */
id|TITAN_WRITE
c_func
(paren
id|address_reg
comma
id|address
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|TITAN_READ_8
c_func
(paren
id|data_reg
op_plus
(paren
id|reg
op_amp
l_int|0x3
)paren
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|TITAN_READ_16
c_func
(paren
id|data_reg
op_plus
(paren
id|reg
op_amp
l_int|0x2
)paren
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|TITAN_READ
c_func
(paren
id|data_reg
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
multiline_comment|/*&n; * Titan PCI Config Byte Write&n; */
DECL|function|titan_write_config
r_static
r_int
id|titan_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|reg
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
r_uint32
id|address_reg
comma
id|data_reg
comma
id|address
suffix:semicolon
r_int
id|dev
comma
id|busno
comma
id|func
suffix:semicolon
id|busno
op_assign
id|bus-&gt;number
suffix:semicolon
id|dev
op_assign
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|func
op_assign
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
suffix:semicolon
id|address_reg
op_assign
id|TITAN_PCI_0_CONFIG_ADDRESS
suffix:semicolon
id|data_reg
op_assign
id|TITAN_PCI_0_CONFIG_DATA
suffix:semicolon
id|address
op_assign
(paren
id|busno
op_lshift
l_int|16
)paren
op_or
(paren
id|dev
op_lshift
l_int|11
)paren
op_or
(paren
id|func
op_lshift
l_int|8
)paren
op_or
(paren
id|reg
op_amp
l_int|0xfc
)paren
op_or
l_int|0x80000000
suffix:semicolon
multiline_comment|/* start the configuration cycle */
id|TITAN_WRITE
c_func
(paren
id|address_reg
comma
id|address
)paren
suffix:semicolon
multiline_comment|/* write the data */
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|TITAN_WRITE_8
c_func
(paren
id|data_reg
op_plus
(paren
id|reg
op_amp
l_int|0x3
)paren
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|TITAN_WRITE_16
c_func
(paren
id|data_reg
op_plus
(paren
id|reg
op_amp
l_int|0x2
)paren
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|TITAN_WRITE
c_func
(paren
id|data_reg
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
multiline_comment|/*&n; * Titan PCI structure&n; */
DECL|variable|titan_pci_ops
r_struct
id|pci_ops
id|titan_pci_ops
op_assign
(brace
id|titan_read_config
comma
id|titan_write_config
comma
)brace
suffix:semicolon
DECL|function|pcibios_init
r_void
id|__init
id|pcibios_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* &n;&t; * XXX These values below need to change&n;&t; */
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
id|titan_pci_ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
