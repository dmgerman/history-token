multiline_comment|/*&n; * Jaguar-ATX Board Register Definitions&n; *&n; * (C) 2002 Momentum Computer Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __JAGUAR_ATX_FPGA_H__
DECL|macro|__JAGUAR_ATX_FPGA_H__
mdefine_line|#define __JAGUAR_ATX_FPGA_H__
DECL|macro|JAGUAR_ATX_REG_BOARDREV
mdefine_line|#define JAGUAR_ATX_REG_BOARDREV&t;&t;0x0
DECL|macro|JAGUAR_ATX_REG_FPGA_REV
mdefine_line|#define JAGUAR_ATX_REG_FPGA_REV&t;&t;0x1
DECL|macro|JAGUAR_ATX_REG_FPGA_TYPE
mdefine_line|#define JAGUAR_ATX_REG_FPGA_TYPE&t;0x2
DECL|macro|JAGUAR_ATX_REG_RESET_STATUS
mdefine_line|#define JAGUAR_ATX_REG_RESET_STATUS&t;0x3
DECL|macro|JAGUAR_ATX_REG_BOARD_STATUS
mdefine_line|#define JAGUAR_ATX_REG_BOARD_STATUS&t;0x4
DECL|macro|JAGUAR_ATX_REG_RESERVED1
mdefine_line|#define JAGUAR_ATX_REG_RESERVED1&t;0x5
DECL|macro|JAGUAR_ATX_REG_SET
mdefine_line|#define JAGUAR_ATX_REG_SET&t;&t;0x6
DECL|macro|JAGUAR_ATX_REG_CLR
mdefine_line|#define JAGUAR_ATX_REG_CLR&t;&t;0x7
DECL|macro|JAGUAR_ATX_REG_EEPROM_MODE
mdefine_line|#define JAGUAR_ATX_REG_EEPROM_MODE&t;0x9
DECL|macro|JAGUAR_ATX_REG_RESERVED2
mdefine_line|#define JAGUAR_ATX_REG_RESERVED2&t;0xa
DECL|macro|JAGUAR_ATX_REG_RESERVED3
mdefine_line|#define JAGUAR_ATX_REG_RESERVED3&t;0xb
DECL|macro|JAGUAR_ATX_REG_RESERVED4
mdefine_line|#define JAGUAR_ATX_REG_RESERVED4&t;0xc
DECL|macro|JAGUAR_ATX_REG_PHY_INTSTAT
mdefine_line|#define JAGUAR_ATX_REG_PHY_INTSTAT&t;0xd
DECL|macro|JAGUAR_ATX_REG_RESERVED5
mdefine_line|#define JAGUAR_ATX_REG_RESERVED5&t;0xe
DECL|macro|JAGUAR_ATX_REG_RESERVED6
mdefine_line|#define JAGUAR_ATX_REG_RESERVED6&t;0xf
DECL|macro|JAGUAR_ATX_CS0_ADDR
mdefine_line|#define JAGUAR_ATX_CS0_ADDR&t;&t;0xfc000000L
r_extern
r_int
r_int
id|ja_fpga_base
suffix:semicolon
DECL|macro|JAGUAR_FPGA_WRITE
mdefine_line|#define JAGUAR_FPGA_WRITE(x,y) writeb(x, ja_fpga_base + JAGUAR_ATX_REG_##y)
DECL|macro|JAGUAR_FPGA_READ
mdefine_line|#define JAGUAR_FPGA_READ(x) readb(ja_fpga_base + JAGUAR_ATX_REG_##x)
macro_line|#endif
eof
