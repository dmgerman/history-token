multiline_comment|/*&n; * include/asm-ppc/spruce_serial.h&n; * &n; * Definitions for IBM Spruce reference board support&n; *&n; * Authors: Matt Porter and Johnnie Peters&n; *          mporter@mvista.com&n; *          jpeters@mvista.com&n; *&n; * Copyright 2000 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASMPPC_SPRUCE_SERIAL_H
DECL|macro|__ASMPPC_SPRUCE_SERIAL_H
mdefine_line|#define __ASMPPC_SPRUCE_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* This is where the serial ports exist */
DECL|macro|SPRUCE_SERIAL_1_ADDR
mdefine_line|#define SPRUCE_SERIAL_1_ADDR&t;0xff600300
DECL|macro|SPRUCE_SERIAL_2_ADDR
mdefine_line|#define SPRUCE_SERIAL_2_ADDR&t;0xff600400
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE  4
multiline_comment|/* Rate for the baud clock for the onboard serial chip */
macro_line|#ifndef CONFIG_SPRUCE_BAUD_33M
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  (30000000 / 4 / 16)
macro_line|#else
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD  (33000000 / 4 / 16)
macro_line|#endif
macro_line|#ifndef SERIAL_MAGIC_KEY
DECL|macro|kernel_debugger
mdefine_line|#define kernel_debugger ppc_kernel_debug
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_DETECT_IRQ
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST|ASYNC_AUTO_IRQ)
macro_line|#else
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF|ASYNC_SKIP_TEST)
macro_line|#endif
DECL|macro|STD_SERIAL_PORT_DFNS
mdefine_line|#define STD_SERIAL_PORT_DFNS &bslash;&n;        { 0, BASE_BAUD, SPRUCE_SERIAL_1_ADDR, 3, STD_COM_FLAGS,&t;/* ttyS0 */ &bslash;&n;&t;&t;iomem_base: (u8 *)SPRUCE_SERIAL_1_ADDR,&t;&t;&t;    &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },&t;&t;&t;&t;    &bslash;&n;        { 0, BASE_BAUD, SPRUCE_SERIAL_2_ADDR, 4, STD_COM_FLAGS,&t;/* ttyS1 */ &bslash;&n;&t;&t;iomem_base: (u8 *)SPRUCE_SERIAL_2_ADDR,&t;&t;&t;    &bslash;&n;&t;&t;io_type: SERIAL_IO_MEM },
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;        STD_SERIAL_PORT_DFNS
macro_line|#endif /* __ASMPPC_SPRUCE_SERIAL_H */
eof
