multiline_comment|/*&n; * ibm_ocp_pci.h&n; *&n; *&t;This was derived from the ibm_ocp.h &n; *&n; * &t;Current Maintainer&n; *      Armin Kuster akuster@mvista.com&n; *      AUg, 2002 &n; *&n; *&n; * Copyright 2001-2002 MontaVista Softare Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_IBM_OCP_PCI_H__
DECL|macro|__ASM_IBM_OCP_PCI_H__
mdefine_line|#define __ASM_IBM_OCP_PCI_H__
multiline_comment|/* PCI 32 */
DECL|struct|pmm_regs
r_struct
id|pmm_regs
(brace
DECL|member|la
id|u32
id|la
suffix:semicolon
DECL|member|ma
id|u32
id|ma
suffix:semicolon
DECL|member|pcila
id|u32
id|pcila
suffix:semicolon
DECL|member|pciha
id|u32
id|pciha
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcil0_regs
r_typedef
r_struct
id|pcil0_regs
(brace
DECL|member|pmm
r_struct
id|pmm_regs
id|pmm
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ptm1ms
id|u32
id|ptm1ms
suffix:semicolon
DECL|member|ptm1la
id|u32
id|ptm1la
suffix:semicolon
DECL|member|ptm2ms
id|u32
id|ptm2ms
suffix:semicolon
DECL|member|ptm2la
id|u32
id|ptm2la
suffix:semicolon
DECL|typedef|pci0_t
)brace
id|pci0_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __ASM_IBM_OCP_PCI_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
