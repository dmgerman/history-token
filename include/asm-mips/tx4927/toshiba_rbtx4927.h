multiline_comment|/*&n; * Author: MontaVista Software, Inc.&n; *         source@mvista.com&n; *&n; * Copyright 2001-2002 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify it&n; *  under the terms of the GNU General Public License as published by the&n; *  Free Software Foundation; either version 2 of the License, or (at your&n; *  option) any later version.&n; *&n; *  THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.&n; *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,&n; *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS&n; *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND&n; *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR&n; *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE&n; *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_TX4927_TOSHIBA_RBTX4927_H
DECL|macro|__ASM_TX4927_TOSHIBA_RBTX4927_H
mdefine_line|#define __ASM_TX4927_TOSHIBA_RBTX4927_H
macro_line|#include &lt;asm/tx4927/tx4927.h&gt;
macro_line|#include &lt;asm/tx4927/tx4927_mips.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;asm/tx4927/tx4927_pci.h&gt;
macro_line|#endif
DECL|macro|TOSHIBA_RBTX4927_WR08
mdefine_line|#define TOSHIBA_RBTX4927_WR08(a,b) do { TX4927_WR08(a,b); wbflush(); } while ( 0 )
macro_line|#ifdef CONFIG_PCI
DECL|macro|TBTX4927_ISA_IO_OFFSET
mdefine_line|#define TBTX4927_ISA_IO_OFFSET TX4927_PCIIO
macro_line|#else
DECL|macro|TBTX4927_ISA_IO_OFFSET
mdefine_line|#define TBTX4927_ISA_IO_OFFSET 0
macro_line|#endif
DECL|macro|RBTX4927_SW_RESET_DO
mdefine_line|#define RBTX4927_SW_RESET_DO         0xbc00f000
DECL|macro|RBTX4927_SW_RESET_DO_SET
mdefine_line|#define RBTX4927_SW_RESET_DO_SET                0x01
DECL|macro|RBTX4927_SW_RESET_ENABLE
mdefine_line|#define RBTX4927_SW_RESET_ENABLE     0xbc00f002
DECL|macro|RBTX4927_SW_RESET_ENABLE_SET
mdefine_line|#define RBTX4927_SW_RESET_ENABLE_SET            0x01
DECL|macro|RBTX4927_RTL_8019_BASE
mdefine_line|#define RBTX4927_RTL_8019_BASE (0x1c020280-TBTX4927_ISA_IO_OFFSET)
DECL|macro|RBTX4927_RTL_8019_IRQ
mdefine_line|#define RBTX4927_RTL_8019_IRQ  (29)
macro_line|#endif /* __ASM_TX4927_TOSHIBA_RBTX4927_H */
eof
