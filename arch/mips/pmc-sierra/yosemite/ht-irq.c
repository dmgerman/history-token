multiline_comment|/*&n; * Copyright 2003 PMC-Sierra&n; * Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pci.h&gt;
multiline_comment|/*&n; * HT Bus fixup for the Titan&n; * XXX IRQ values need to change based on the board layout&n; */
DECL|function|titan_ht_pcibios_fixup_bus
r_void
id|__init
id|titan_ht_pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_bus
op_star
id|current_bus
op_assign
id|bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|devices
suffix:semicolon
r_struct
id|list_head
op_star
id|devices_link
suffix:semicolon
id|list_for_each
c_func
(paren
id|devices_link
comma
op_amp
(paren
id|current_bus-&gt;devices
)paren
)paren
(brace
id|devices
op_assign
id|pci_dev_b
c_func
(paren
id|devices_link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devices
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * PLX and SPKT related changes go here&n;&t; */
)brace
eof
