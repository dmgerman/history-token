multiline_comment|/***********************************************************************&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *              ahennessy@mvista.com&n; *&n; * include/asm-mips/jmr3927/pci.h&n; * Based on include/asm-mips/ddb5xxx/pci.h&n; *&n; * This file essentially defines the interface between board&n; * specific PCI code and MIPS common PCI code.  Should potentially put&n; * into include/asm/pci.h file.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; ***********************************************************************&n; */
macro_line|#ifndef __ASM_TX3927_PCI_H
DECL|macro|__ASM_TX3927__PCI_H
mdefine_line|#define __ASM_TX3927__PCI_H
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
multiline_comment|/*&n; * Each pci channel is a top-level PCI bus seem by CPU.  A machine  with&n; * multiple PCI channels may have multiple PCI host controllers or a&n; * single controller supporting multiple channels.&n; */
DECL|struct|pci_channel
r_struct
id|pci_channel
(brace
DECL|member|pci_ops
r_struct
id|pci_ops
op_star
id|pci_ops
suffix:semicolon
DECL|member|io_resource
r_struct
id|resource
op_star
id|io_resource
suffix:semicolon
DECL|member|mem_resource
r_struct
id|resource
op_star
id|mem_resource
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * each board defines an array of pci_channels, that ends with all NULL entry&n; */
r_extern
r_struct
id|pci_channel
id|mips_pci_channels
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * board supplied pci irq fixup routine&n; */
r_extern
r_void
id|pcibios_fixup_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif  /* __ASM_TX3927_PCI_H */
eof
