multiline_comment|/*&n; * BRIEF MODULE DESCRIPTION&n; *&t;Alchemy/AMD Au1x00 pci support.&n; *&n; * Copyright 2001,2002,2003 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  Support for all devices (greater than 16) added by David Gathright.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach-au1x00/au1000.h&gt;
DECL|macro|PCI_ACCESS_READ
mdefine_line|#define PCI_ACCESS_READ  0
DECL|macro|PCI_ACCESS_WRITE
mdefine_line|#define PCI_ACCESS_WRITE 1
DECL|function|config_access
r_static
r_int
id|config_access
c_func
(paren
r_int
r_char
id|access_type
comma
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
r_char
id|where
comma
id|u32
op_star
id|data
)paren
(brace
r_int
r_int
id|device
op_assign
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
suffix:semicolon
r_int
r_int
id|function
op_assign
id|PCI_FUNC
c_func
(paren
id|devfn
)paren
suffix:semicolon
r_int
r_int
id|config
comma
id|status
suffix:semicolon
r_int
r_int
id|cfg_addr
suffix:semicolon
r_if
c_cond
(paren
id|device
OG
l_int|19
)paren
(brace
op_star
id|data
op_assign
l_int|0xffffffff
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|au_writel
c_func
(paren
(paren
(paren
l_int|0x2000
op_lshift
l_int|16
)paren
op_or
(paren
id|au_readl
c_func
(paren
id|Au1500_PCI_STATCMD
)paren
op_amp
l_int|0xffff
)paren
)paren
comma
id|Au1500_PCI_STATCMD
)paren
suffix:semicolon
singleline_comment|//au_writel(au_readl(Au1500_PCI_CFG) &amp; ~PCI_ERROR, Au1500_PCI_CFG);
id|au_sync_udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* setup the config window */
r_if
c_cond
(paren
id|bus-&gt;number
op_eq
l_int|0
)paren
(brace
id|cfg_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|Au1500_EXT_CFG
op_or
(paren
(paren
l_int|1
op_lshift
id|device
)paren
op_lshift
l_int|11
)paren
comma
l_int|0x00100000
)paren
suffix:semicolon
)brace
r_else
(brace
id|cfg_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|Au1500_EXT_CFG_TYPE1
op_or
(paren
id|bus
op_member_access_from_pointer
id|number
op_lshift
l_int|16
)paren
op_or
(paren
id|device
op_lshift
l_int|11
)paren
comma
l_int|0x00100000
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cfg_addr
)paren
id|panic
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI unable to ioremap cfg space&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* setup the lower bits of the 36 bit address */
id|config
op_assign
id|cfg_addr
op_or
(paren
id|function
op_lshift
l_int|8
)paren
op_or
(paren
id|where
op_amp
op_complement
l_int|0x3
)paren
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|access_type
op_eq
id|PCI_ACCESS_WRITE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cfg write:  &quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;cfg read:  &quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;devfn %x, device %x func %x  &bslash;n&quot;
comma
id|devfn
comma
id|device
comma
id|function
)paren
suffix:semicolon
r_if
c_cond
(paren
id|access_type
op_eq
id|PCI_ACCESS_WRITE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;data %x&bslash;n&quot;
comma
op_star
id|data
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|access_type
op_eq
id|PCI_ACCESS_WRITE
)paren
(brace
id|au_writel
c_func
(paren
op_star
id|data
comma
id|config
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|data
op_assign
id|au_readl
c_func
(paren
id|config
)paren
suffix:semicolon
)brace
id|au_sync_udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/* unmap io space */
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|cfg_addr
)paren
suffix:semicolon
multiline_comment|/* check master abort */
id|status
op_assign
id|au_readl
c_func
(paren
id|Au1500_PCI_STATCMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|29
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;master abort&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|data
op_assign
l_int|0xffffffff
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|status
op_rshift
l_int|28
)paren
op_amp
l_int|0xf
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI ERR detected: status %x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
op_star
id|data
op_assign
l_int|0xffffffff
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;bios_successful: %x&bslash;n&quot;
comma
op_star
id|data
)paren
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
)brace
DECL|function|read_config_byte
r_static
r_int
id|read_config_byte
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
id|where
comma
id|u8
op_star
id|val
)paren
(brace
id|u32
id|data
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|config_access
c_func
(paren
id|PCI_ACCESS_READ
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|1
)paren
id|data
op_rshift_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|data
op_rshift_assign
l_int|16
suffix:semicolon
op_star
id|val
op_assign
id|data
op_amp
l_int|0xff
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|read_config_word
r_static
r_int
id|read_config_word
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
id|where
comma
id|u16
op_star
id|val
)paren
(brace
id|u32
id|data
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|config_access
c_func
(paren
id|PCI_ACCESS_READ
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
l_int|2
)paren
id|data
op_rshift_assign
l_int|16
suffix:semicolon
op_star
id|val
op_assign
id|data
op_amp
l_int|0xffff
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|read_config_dword
r_static
r_int
id|read_config_dword
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
id|where
comma
id|u32
op_star
id|val
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|config_access
c_func
(paren
id|PCI_ACCESS_READ
comma
id|bus
comma
id|devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
r_int
DECL|function|write_config_byte
id|write_config_byte
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
id|where
comma
id|u8
id|val
)paren
(brace
id|u32
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|config_access
c_func
(paren
id|PCI_ACCESS_READ
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|data
op_assign
(paren
id|data
op_amp
op_complement
(paren
l_int|0xff
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
)paren
op_or
(paren
id|val
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config_access
c_func
(paren
id|PCI_ACCESS_WRITE
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|write_config_word
id|write_config_word
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
id|where
comma
id|u16
id|val
)paren
(brace
id|u32
id|data
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|config_access
c_func
(paren
id|PCI_ACCESS_READ
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|data
op_assign
(paren
id|data
op_amp
op_complement
(paren
l_int|0xffff
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
)paren
op_or
(paren
id|val
op_lshift
(paren
(paren
id|where
op_amp
l_int|3
)paren
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|config_access
c_func
(paren
id|PCI_ACCESS_WRITE
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|data
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
r_static
r_int
DECL|function|write_config_dword
id|write_config_dword
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
id|where
comma
id|u32
id|val
)paren
(brace
r_if
c_cond
(paren
id|config_access
c_func
(paren
id|PCI_ACCESS_WRITE
comma
id|bus
comma
id|devfn
comma
id|where
comma
op_amp
id|val
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|config_read
r_static
r_int
id|config_read
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
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|read_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
(paren
id|u8
op_star
)paren
id|val
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
id|read_config_word
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
(paren
id|u16
op_star
)paren
id|val
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|read_config_dword
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|function|config_write
r_static
r_int
id|config_write
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
id|where
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
r_return
id|write_config_byte
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
(paren
id|u8
)paren
id|val
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
id|write_config_word
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
(paren
id|u16
)paren
id|val
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|write_config_dword
c_func
(paren
id|bus
comma
id|devfn
comma
id|where
comma
id|val
)paren
suffix:semicolon
)brace
)brace
DECL|variable|au1x_pci_ops
r_struct
id|pci_ops
id|au1x_pci_ops
op_assign
(brace
id|config_read
comma
id|config_write
)brace
suffix:semicolon
eof
