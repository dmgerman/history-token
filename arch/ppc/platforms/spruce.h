multiline_comment|/*&n; * include/asm-ppc/platforms/spruce.h&n; * &n; * Definitions for IBM Spruce reference board support&n; *&n; * Authors: Matt Porter and Johnnie Peters&n; *          mporter@mvista.com&n; *          jpeters@mvista.com&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR   IMPLIED&n; * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT,  INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_SPRUCE_H__
DECL|macro|__ASM_SPRUCE_H__
mdefine_line|#define __ASM_SPRUCE_H__
DECL|macro|SPRUCE_PCI_CONFIG_ADDR
mdefine_line|#define SPRUCE_PCI_CONFIG_ADDR&t;0xfec00000
DECL|macro|SPRUCE_PCI_CONFIG_DATA
mdefine_line|#define SPRUCE_PCI_CONFIG_DATA&t;0xfec00004
DECL|macro|SPRUCE_PCI_PHY_IO_BASE
mdefine_line|#define SPRUCE_PCI_PHY_IO_BASE&t;0xf8000000
DECL|macro|SPRUCE_PCI_IO_BASE
mdefine_line|#define SPRUCE_PCI_IO_BASE&t;SPRUCE_PCI_PHY_IO_BASE
DECL|macro|SPRUCE_PCI_SYS_MEM_BASE
mdefine_line|#define SPRUCE_PCI_SYS_MEM_BASE&t;0x00000000
DECL|macro|SPRUCE_PCI_LOWER_MEM
mdefine_line|#define SPRUCE_PCI_LOWER_MEM&t;0x80000000
DECL|macro|SPRUCE_PCI_UPPER_MEM
mdefine_line|#define SPRUCE_PCI_UPPER_MEM&t;0x9fffffff
DECL|macro|SPRUCE_PCI_LOWER_IO
mdefine_line|#define SPRUCE_PCI_LOWER_IO&t;0x00000000
DECL|macro|SPRUCE_PCI_UPPER_IO
mdefine_line|#define SPRUCE_PCI_UPPER_IO&t;0x03ffffff
DECL|macro|SPRUCE_ISA_IO_BASE
mdefine_line|#define&t;SPRUCE_ISA_IO_BASE&t;SPRUCE_PCI_IO_BASE
DECL|macro|SPRUCE_MEM_SIZE
mdefine_line|#define SPRUCE_MEM_SIZE&t;&t;0x04000000
DECL|macro|SPRUCE_BUS_SPEED
mdefine_line|#define SPRUCE_BUS_SPEED&t;66666667
DECL|macro|SPRUCE_SERIAL_1_ADDR
mdefine_line|#define SPRUCE_SERIAL_1_ADDR&t;0xff600300
DECL|macro|SPRUCE_SERIAL_2_ADDR
mdefine_line|#define SPRUCE_SERIAL_2_ADDR&t;0xff600400
DECL|macro|SPRUCE_NVRAM_BASE_ADDR
mdefine_line|#define SPRUCE_NVRAM_BASE_ADDR&t;0xff800000
DECL|macro|SPRUCE_RTC_BASE_ADDR
mdefine_line|#define SPRUCE_RTC_BASE_ADDR&t;SPRUCE_NVRAM_BASE_ADDR
DECL|macro|KEYBOARD_IRQ
mdefine_line|#define KEYBOARD_IRQ    22
DECL|macro|AUX_IRQ
mdefine_line|#define AUX_IRQ &t;21
r_int
r_char
id|spruce_read_keyb_data
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_char
id|spruce_read_keyb_status
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|kbd_read_input
mdefine_line|#define kbd_read_input  spruce_read_keyb_data
DECL|macro|kbd_read_status
mdefine_line|#define kbd_read_status spruce_read_keyb_status
DECL|macro|kbd_write_output
mdefine_line|#define kbd_write_output(val) *((unsigned char *)0xff810000) = (char)val
DECL|macro|kbd_write_command
mdefine_line|#define kbd_write_command(val) *((unsigned char *)0xff810001) = (char)val
macro_line|#endif /* __ASM_SPRUCE_H__ */
macro_line|#endif /* __KERNEL__ */
eof
