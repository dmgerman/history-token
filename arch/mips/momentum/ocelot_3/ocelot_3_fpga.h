multiline_comment|/*&n; * Ocelot-3 Board Register Definitions&n; *&n; * (C) 2002 Momentum Computer Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Louis Hamilton, Red Hat, Inc.&n; *    hamilton@redhat.com  [MIPS64 modifications]&n; *&n; * Copyright (C) 2004 MontaVista Software Inc.&n; * Author: Manish Lachwani, mlachwani@mvista.com&n; */
macro_line|#ifndef __OCELOT_3_FPGA_H__
DECL|macro|__OCELOT_3_FPGA_H__
mdefine_line|#define __OCELOT_3_FPGA_H__
DECL|macro|OCELOT_3_REG_BOARDREV
mdefine_line|#define OCELOT_3_REG_BOARDREV&t;&t;0x0
DECL|macro|OCELOT_3_REG_FPGA_REV
mdefine_line|#define OCELOT_3_REG_FPGA_REV&t;&t;0x1
DECL|macro|OCELOT_3_REG_FPGA_TYPE
mdefine_line|#define OCELOT_3_REG_FPGA_TYPE&t;&t;0x2
DECL|macro|OCELOT_3_REG_RESET_STATUS
mdefine_line|#define OCELOT_3_REG_RESET_STATUS&t;0x3
DECL|macro|OCELOT_3_REG_BOARD_STATUS
mdefine_line|#define OCELOT_3_REG_BOARD_STATUS&t;0x4
DECL|macro|OCELOT_3_REG_CPCI_ID
mdefine_line|#define OCELOT_3_REG_CPCI_ID&t;&t;0x5
DECL|macro|OCELOT_3_REG_SET
mdefine_line|#define OCELOT_3_REG_SET&t;&t;0x6
DECL|macro|OCELOT_3_REG_CLR
mdefine_line|#define OCELOT_3_REG_CLR&t;&t;0x7
DECL|macro|OCELOT_3_REG_EEPROM_MODE
mdefine_line|#define OCELOT_3_REG_EEPROM_MODE&t;0x9
DECL|macro|OCELOT_3_REG_INTMASK
mdefine_line|#define OCELOT_3_REG_INTMASK&t;&t;0xa
DECL|macro|OCELOT_3_REG_INTSTAT
mdefine_line|#define OCELOT_3_REG_INTSTAT&t;&t;0xb
DECL|macro|OCELOT_3_REG_UART_INTMASK
mdefine_line|#define OCELOT_3_REG_UART_INTMASK&t;0xc
DECL|macro|OCELOT_3_REG_UART_INTSTAT
mdefine_line|#define OCELOT_3_REG_UART_INTSTAT&t;0xd
DECL|macro|OCELOT_3_REG_INTSET
mdefine_line|#define OCELOT_3_REG_INTSET&t;&t;0xe
DECL|macro|OCELOT_3_REG_INTCLR
mdefine_line|#define OCELOT_3_REG_INTCLR&t;&t;0xf
r_extern
r_int
r_int
id|ocelot_fpga_base
suffix:semicolon
DECL|macro|OCELOT_FPGA_WRITE
mdefine_line|#define OCELOT_FPGA_WRITE(x, y) writeb(x, ocelot_fpga_base + OCELOT_3_REG_##y)
DECL|macro|OCELOT_FPGA_READ
mdefine_line|#define OCELOT_FPGA_READ(x) readb(ocelot_fpga_base + OCELOT_3_REG_##x)
macro_line|#endif
eof
