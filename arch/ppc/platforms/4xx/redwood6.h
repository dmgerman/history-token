multiline_comment|/*&n; * &t;Author: MontaVista Software, Inc.&n; *          Armin Kuster&n; *&n; *    Module name: redwood6.h&n; *&n; *    Description:&n; *      Macros, definitions, and data structures specific to the IBM PowerPC&n; *      STBx25xx &quot;Redwood6&quot; evaluation board.&n; *&n; *    Copyright 2002 MontaVista Software Inc.&n; * &t;Author: MontaVista Software, Inc.&n; *          Armin Kuster&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_REDWOOD5_H__
DECL|macro|__ASM_REDWOOD5_H__
mdefine_line|#define __ASM_REDWOOD5_H__
multiline_comment|/* Redwood6 has an STBx25xx core */
macro_line|#include &lt;platforms/4xx/ibmstbx25.h&gt;
macro_line|#ifndef __ASSEMBLY__
DECL|struct|board_info
r_typedef
r_struct
id|board_info
(brace
DECL|member|bi_s_version
r_int
r_char
id|bi_s_version
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Version of this structure */
DECL|member|bi_r_version
r_int
r_char
id|bi_r_version
(braket
l_int|30
)braket
suffix:semicolon
multiline_comment|/* Version of the IBM ROM */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* DRAM installed, in bytes */
DECL|member|bi_dummy
r_int
r_int
id|bi_dummy
suffix:semicolon
multiline_comment|/* field shouldn&squot;t exist */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Ethernet MAC address */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Processor speed, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus speed, in Hz */
DECL|member|bi_tbfreq
r_int
r_int
id|bi_tbfreq
suffix:semicolon
multiline_comment|/* Software timebase freq */
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* !__ASSEMBLY__ */
DECL|macro|SMC91111_BASE_ADDR
mdefine_line|#define SMC91111_BASE_ADDR&t;0xf2030300
DECL|macro|SMC91111_IRQ
mdefine_line|#define SMC91111_IRQ&t;&t;27
DECL|macro|IDE_XLINUX_MUX_BASE
mdefine_line|#define IDE_XLINUX_MUX_BASE        0xf2040000
DECL|macro|IDE_DMA_ADDR
mdefine_line|#define IDE_DMA_ADDR&t;0xfce00000
macro_line|#ifdef MAX_HWIFS
DECL|macro|MAX_HWIFS
macro_line|#undef MAX_HWIFS
macro_line|#endif
DECL|macro|MAX_HWIFS
mdefine_line|#define MAX_HWIFS&t;&t;1
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;0
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD&t;&t;1267200
DECL|macro|PPC4xx_MACHINE_NAME
mdefine_line|#define PPC4xx_MACHINE_NAME&t;&quot;IBM Redwood6&quot;
macro_line|#endif&t;&t;&t;&t;/* __ASM_REDWOOD5_H__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
eof
