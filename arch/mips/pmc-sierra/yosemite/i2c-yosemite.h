multiline_comment|/*&n; *  arch/mips/pmc-sierra/yosemite/i2c-yosemite.h&n; *&n; *  Copyright (C) 2003 PMC-Sierra Inc.&n; *  Author: Manish Lachwani (lachwani@pmc-sierra.com)&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __I2C_YOSEMITE_H
DECL|macro|__I2C_YOSEMITE_H
mdefine_line|#define __I2C_YOSEMITE_H
multiline_comment|/* Read and Write operations to the chip */
DECL|macro|TITAN_I2C_BASE
mdefine_line|#define TITAN_I2C_BASE&t;&t;&t;0xbb000000&t;/* XXX Needs to change */
DECL|macro|TITAN_I2C_WRITE
mdefine_line|#define&t;TITAN_I2C_WRITE(offset, data)&t;&bslash;&n;&t;&t;&t;&t;&t;*(volatile unsigned long *)(TITAN_I2C_BASE + offset) = data
DECL|macro|TITAN_I2C_READ
mdefine_line|#define&t;TITAN_I2C_READ(offset) *(volatile unsigned long *)(TITAN_I2C_BASE + offset)
multiline_comment|/* Local constansts*/
DECL|macro|TITAN_I2C_MAX_FILTER
mdefine_line|#define TITAN_I2C_MAX_FILTER            15
DECL|macro|TITAN_I2C_MAX_CLK
mdefine_line|#define TITAN_I2C_MAX_CLK               1023
DECL|macro|TITAN_I2C_MAX_ARBF
mdefine_line|#define TITAN_I2C_MAX_ARBF              15
DECL|macro|TITAN_I2C_MAX_NAK
mdefine_line|#define TITAN_I2C_MAX_NAK               15
DECL|macro|TITAN_I2C_MAX_MASTERCODE
mdefine_line|#define TITAN_I2C_MAX_MASTERCODE        7
DECL|macro|TITAN_I2C_MAX_WORDS_PER_RW
mdefine_line|#define TITAN_I2C_MAX_WORDS_PER_RW      4
DECL|macro|TITAN_I2C_MAX_POLL
mdefine_line|#define TITAN_I2C_MAX_POLL&t;&t;100
multiline_comment|/* Registers used for I2C work */
DECL|macro|TITAN_I2C_SCMB_CONTROL
mdefine_line|#define TITAN_I2C_SCMB_CONTROL&t;&t;0x0180&t;/* SCMB Control */
DECL|macro|TITAN_I2C_SCMB_CLOCK_A
mdefine_line|#define TITAN_I2C_SCMB_CLOCK_A&t;&t;0x0184&t;/* SCMB Clock A */
DECL|macro|TITAN_I2C_SCMB_CLOCK_B
mdefine_line|#define TITAN_I2C_SCMB_CLOCK_B&t;&t;0x0188&t;/* SCMB Clock B */
DECL|macro|TITAN_I2C_CONFIG
mdefine_line|#define&t;TITAN_I2C_CONFIG&t;&t;0x01A0&t;/* I2C Config */
DECL|macro|TITAN_I2C_COMMAND
mdefine_line|#define TITAN_I2C_COMMAND&t;&t;0x01A4&t;/* I2C Command */
DECL|macro|TITAN_I2C_SLAVE_ADDRESS
mdefine_line|#define&t;TITAN_I2C_SLAVE_ADDRESS&t;&t;0x01A8&t;/* I2C Slave Address */
DECL|macro|TITAN_I2C_DATA
mdefine_line|#define TITAN_I2C_DATA&t;&t;&t;0x01AC&t;/* I2C Data [15:0] */
DECL|macro|TITAN_I2C_INTERRUPTS
mdefine_line|#define TITAN_I2C_INTERRUPTS&t;&t;0x01BC&t;/* I2C Interrupts */
multiline_comment|/* Error */
DECL|macro|TITAN_I2C_ERR_ARB_LOST
mdefine_line|#define&t;TITAN_I2C_ERR_ARB_LOST&t;&t;(-9220)
DECL|macro|TITAN_I2C_ERR_NO_RESP
mdefine_line|#define&t;TITAN_I2C_ERR_NO_RESP&t;&t;(-9221)
DECL|macro|TITAN_I2C_ERR_DATA_COLLISION
mdefine_line|#define&t;TITAN_I2C_ERR_DATA_COLLISION&t;(-9222)
DECL|macro|TITAN_I2C_ERR_TIMEOUT
mdefine_line|#define&t;TITAN_I2C_ERR_TIMEOUT&t;&t;(-9223)
DECL|macro|TITAN_I2C_ERR_OK
mdefine_line|#define&t;TITAN_I2C_ERR_OK&t;&t;0
multiline_comment|/* I2C Command Type */
r_typedef
r_enum
(brace
DECL|enumerator|TITAN_I2C_CMD_WRITE
id|TITAN_I2C_CMD_WRITE
op_assign
l_int|0
comma
DECL|enumerator|TITAN_I2C_CMD_READ
id|TITAN_I2C_CMD_READ
op_assign
l_int|1
comma
DECL|enumerator|TITAN_I2C_CMD_READ_WRITE
id|TITAN_I2C_CMD_READ_WRITE
op_assign
l_int|2
DECL|typedef|titan_i2c_cmd_type
)brace
id|titan_i2c_cmd_type
suffix:semicolon
multiline_comment|/* I2C structures */
r_typedef
r_struct
(brace
DECL|member|filtera
r_int
id|filtera
suffix:semicolon
multiline_comment|/* Register 0x0184, bits 15 - 12 */
DECL|member|clka
r_int
id|clka
suffix:semicolon
multiline_comment|/* Register 0x0184, bits 9 - 0 */
DECL|member|filterb
r_int
id|filterb
suffix:semicolon
multiline_comment|/* Register 0x0188, bits 15 - 12 */
DECL|member|clkb
r_int
id|clkb
suffix:semicolon
multiline_comment|/* Register 0x0188, bits 9 - 0 */
DECL|typedef|titan_i2c_config
)brace
id|titan_i2c_config
suffix:semicolon
multiline_comment|/* I2C command type */
r_typedef
r_struct
(brace
DECL|member|type
id|titan_i2c_cmd_type
id|type
suffix:semicolon
multiline_comment|/* Type of command */
DECL|member|num_arb
r_int
id|num_arb
suffix:semicolon
multiline_comment|/* Register 0x01a0, bits 15 - 12 */
DECL|member|num_nak
r_int
id|num_nak
suffix:semicolon
multiline_comment|/* Register 0x01a0, bits 11 - 8 */
DECL|member|addr_size
r_int
id|addr_size
suffix:semicolon
multiline_comment|/* Register 0x01a0, bit 7 */
DECL|member|mst_code
r_int
id|mst_code
suffix:semicolon
multiline_comment|/* Register 0x01a0, bits 6 - 4 */
DECL|member|arb_en
r_int
id|arb_en
suffix:semicolon
multiline_comment|/* Register 0x01a0, bit 1 */
DECL|member|speed
r_int
id|speed
suffix:semicolon
multiline_comment|/* Register 0x01a0, bit 0 */
DECL|member|slave_addr
r_int
id|slave_addr
suffix:semicolon
multiline_comment|/* Register 0x01a8 */
DECL|member|write_size
r_int
id|write_size
suffix:semicolon
multiline_comment|/* Register 0x01a4, bits 10 - 8 */
DECL|member|data
r_int
r_int
op_star
id|data
suffix:semicolon
multiline_comment|/* Register 0x01ac */
DECL|typedef|titan_i2c_command
)brace
id|titan_i2c_command
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __I2C_YOSEMITE_H */
eof
