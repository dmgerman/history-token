multiline_comment|/*&n;&t;ppc6lnx.c (c) 2001 Micro Solutions Inc.&n;&t;&t;Released under the terms of the GNU General Public license&n;&n;&t;ppc6lnx.c  is a par of the protocol driver for the Micro Solutions&n;&t;&t;&quot;BACKPACK&quot; parallel port IDE adapter&n;&t;&t;(Works on Series 6 drives)&n;&n;*/
singleline_comment|//***************************************************************************
singleline_comment|// PPC 6 Code in C sanitized for LINUX
singleline_comment|// Original x86 ASM by Ron, Converted to C by Clive
singleline_comment|//***************************************************************************
DECL|macro|port_stb
mdefine_line|#define port_stb&t;&t;&t;&t;&t;1
DECL|macro|port_afd
mdefine_line|#define port_afd&t;&t;&t;&t;&t;2
DECL|macro|cmd_stb
mdefine_line|#define cmd_stb&t;&t;&t;&t;&t;&t;port_afd
DECL|macro|port_init
mdefine_line|#define port_init&t;&t;&t;&t;&t;4
DECL|macro|data_stb
mdefine_line|#define data_stb&t;&t;&t;&t;&t;port_init
DECL|macro|port_sel
mdefine_line|#define port_sel&t;&t;&t;&t;&t;8
DECL|macro|port_int
mdefine_line|#define port_int&t;&t;&t;&t;&t;16
DECL|macro|port_dir
mdefine_line|#define port_dir&t;&t;&t;&t;&t;0x20
DECL|macro|ECR_EPP
mdefine_line|#define ECR_EPP&t;0x80
DECL|macro|ECR_BI
mdefine_line|#define ECR_BI&t;0x20
singleline_comment|//***************************************************************************
singleline_comment|//  60772 Commands
DECL|macro|ACCESS_REG
mdefine_line|#define ACCESS_REG&t;&t;&t;&t;0x00
DECL|macro|ACCESS_PORT
mdefine_line|#define ACCESS_PORT&t;&t;&t;&t;0x40
DECL|macro|ACCESS_READ
mdefine_line|#define ACCESS_READ&t;&t;&t;&t;0x00
DECL|macro|ACCESS_WRITE
mdefine_line|#define ACCESS_WRITE&t;&t;&t;0x20
singleline_comment|//  60772 Command Prefix
DECL|macro|CMD_PREFIX_SET
mdefine_line|#define CMD_PREFIX_SET&t;&t;0xe0&t;&t;
singleline_comment|// Special command that modifies the next command&squot;s operation
DECL|macro|CMD_PREFIX_RESET
mdefine_line|#define CMD_PREFIX_RESET&t;0xc0&t;&t;
singleline_comment|// Resets current cmd modifier reg bits
DECL|macro|PREFIX_IO16
mdefine_line|#define PREFIX_IO16&t;&t;&t;0x01&t;&t;
singleline_comment|// perform 16-bit wide I/O
DECL|macro|PREFIX_FASTWR
mdefine_line|#define PREFIX_FASTWR&t;&t;0x04&t;&t;
singleline_comment|// enable PPC mode fast-write
DECL|macro|PREFIX_BLK
mdefine_line|#define PREFIX_BLK&t;&t;&t;&t;0x08&t;&t;
singleline_comment|// enable block transfer mode
singleline_comment|// 60772 Registers
DECL|macro|REG_STATUS
mdefine_line|#define REG_STATUS&t;&t;&t;&t;0x00&t;&t;
singleline_comment|// status register
DECL|macro|STATUS_IRQA
mdefine_line|#define STATUS_IRQA&t;&t;&t;0x01&t;&t;
singleline_comment|// Peripheral IRQA line
DECL|macro|STATUS_EEPROM_DO
mdefine_line|#define STATUS_EEPROM_DO&t;0x40&t;&t;
singleline_comment|// Serial EEPROM data bit
DECL|macro|REG_VERSION
mdefine_line|#define REG_VERSION&t;&t;&t;&t;0x01&t;&t;
singleline_comment|// PPC version register (read)
DECL|macro|REG_HWCFG
mdefine_line|#define REG_HWCFG&t;&t;&t;&t;&t;0x02&t;&t;
singleline_comment|// Hardware Config register
DECL|macro|REG_RAMSIZE
mdefine_line|#define REG_RAMSIZE&t;&t;&t;&t;0x03&t;&t;
singleline_comment|// Size of RAM Buffer
DECL|macro|RAMSIZE_128K
mdefine_line|#define RAMSIZE_128K&t;&t;&t;0x02
DECL|macro|REG_EEPROM
mdefine_line|#define REG_EEPROM&t;&t;&t;&t;0x06&t;&t;
singleline_comment|// EEPROM control register
DECL|macro|EEPROM_SK
mdefine_line|#define EEPROM_SK&t;&t;&t;&t;0x01&t;&t;
singleline_comment|// eeprom SK bit
DECL|macro|EEPROM_DI
mdefine_line|#define EEPROM_DI&t;&t;&t;&t;0x02&t;&t;
singleline_comment|// eeprom DI bit
DECL|macro|EEPROM_CS
mdefine_line|#define EEPROM_CS&t;&t;&t;&t;0x04&t;&t;
singleline_comment|// eeprom CS bit
DECL|macro|EEPROM_EN
mdefine_line|#define EEPROM_EN&t;&t;&t;&t;0x08&t;&t;
singleline_comment|// eeprom output enable
DECL|macro|REG_BLKSIZE
mdefine_line|#define REG_BLKSIZE&t;&t;&t;&t;0x08&t;&t;
singleline_comment|// Block transfer len (24 bit)
singleline_comment|//***************************************************************************
DECL|struct|ppc_storage
r_typedef
r_struct
id|ppc_storage
(brace
DECL|member|lpt_addr
id|u16
id|lpt_addr
suffix:semicolon
singleline_comment|// LPT base address
DECL|member|ppc_id
id|u8
id|ppc_id
suffix:semicolon
DECL|member|mode
id|u8
id|mode
suffix:semicolon
singleline_comment|// operating mode
singleline_comment|// 0 = PPC Uni SW
singleline_comment|// 1 = PPC Uni FW
singleline_comment|// 2 = PPC Bi SW
singleline_comment|// 3 = PPC Bi FW
singleline_comment|// 4 = EPP Byte
singleline_comment|// 5 = EPP Word
singleline_comment|// 6 = EPP Dword
DECL|member|ppc_flags
id|u8
id|ppc_flags
suffix:semicolon
DECL|member|org_data
id|u8
id|org_data
suffix:semicolon
singleline_comment|// original LPT data port contents
DECL|member|org_ctrl
id|u8
id|org_ctrl
suffix:semicolon
singleline_comment|// original LPT control port contents
DECL|member|cur_ctrl
id|u8
id|cur_ctrl
suffix:semicolon
singleline_comment|// current control port contents
DECL|typedef|PPC
)brace
id|PPC
suffix:semicolon
singleline_comment|//***************************************************************************
singleline_comment|// ppc_flags
DECL|macro|fifo_wait
mdefine_line|#define fifo_wait&t;&t;&t;&t;&t;0x10
singleline_comment|//***************************************************************************
singleline_comment|// DONT CHANGE THESE LEST YOU BREAK EVERYTHING - BIT FIELD DEPENDENCIES
DECL|macro|PPCMODE_UNI_SW
mdefine_line|#define PPCMODE_UNI_SW&t;&t;0
DECL|macro|PPCMODE_UNI_FW
mdefine_line|#define PPCMODE_UNI_FW&t;&t;1
DECL|macro|PPCMODE_BI_SW
mdefine_line|#define PPCMODE_BI_SW&t;&t;&t;2
DECL|macro|PPCMODE_BI_FW
mdefine_line|#define PPCMODE_BI_FW&t;&t;&t;3
DECL|macro|PPCMODE_EPP_BYTE
mdefine_line|#define PPCMODE_EPP_BYTE&t;4
DECL|macro|PPCMODE_EPP_WORD
mdefine_line|#define PPCMODE_EPP_WORD&t;5
DECL|macro|PPCMODE_EPP_DWORD
mdefine_line|#define PPCMODE_EPP_DWORD&t;6
singleline_comment|//***************************************************************************
r_static
r_int
id|ppc6_select
c_func
(paren
id|PPC
op_star
id|ppc
)paren
suffix:semicolon
r_static
r_void
id|ppc6_deselect
c_func
(paren
id|PPC
op_star
id|ppc
)paren
suffix:semicolon
r_static
r_void
id|ppc6_send_cmd
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|cmd
)paren
suffix:semicolon
r_static
r_void
id|ppc6_wr_data_byte
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|data
)paren
suffix:semicolon
r_static
id|u8
id|ppc6_rd_data_byte
c_func
(paren
id|PPC
op_star
id|ppc
)paren
suffix:semicolon
r_static
id|u8
id|ppc6_rd_port
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
)paren
suffix:semicolon
r_static
r_void
id|ppc6_wr_port
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
comma
id|u8
id|data
)paren
suffix:semicolon
r_static
r_void
id|ppc6_rd_data_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
op_star
id|data
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|ppc6_wait_for_fifo
c_func
(paren
id|PPC
op_star
id|ppc
)paren
suffix:semicolon
r_static
r_void
id|ppc6_wr_data_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
op_star
id|data
comma
r_int
id|count
)paren
suffix:semicolon
r_static
r_void
id|ppc6_rd_port16_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
comma
id|u8
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
r_static
r_void
id|ppc6_wr_port16_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
comma
id|u8
op_star
id|data
comma
r_int
id|length
)paren
suffix:semicolon
r_static
r_void
id|ppc6_wr_extout
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|regdata
)paren
suffix:semicolon
r_static
r_int
id|ppc6_open
c_func
(paren
id|PPC
op_star
id|ppc
)paren
suffix:semicolon
r_static
r_void
id|ppc6_close
c_func
(paren
id|PPC
op_star
id|ppc
)paren
suffix:semicolon
singleline_comment|//***************************************************************************
DECL|function|ppc6_select
r_static
r_int
id|ppc6_select
c_func
(paren
id|PPC
op_star
id|ppc
)paren
(brace
id|u8
id|i
comma
id|j
comma
id|k
suffix:semicolon
id|i
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_amp
l_int|1
)paren
id|outb
c_func
(paren
id|i
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
suffix:semicolon
id|ppc-&gt;org_data
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|ppc-&gt;org_ctrl
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
op_amp
l_int|0x5F
suffix:semicolon
singleline_comment|// readback ctrl
id|ppc-&gt;cur_ctrl
op_assign
id|ppc-&gt;org_ctrl
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_sel
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc-&gt;org_data
op_eq
l_char|&squot;b&squot;
)paren
id|outb
c_func
(paren
l_char|&squot;x&squot;
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
l_char|&squot;b&squot;
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
l_char|&squot;p&squot;
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;ppc_id
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
op_complement
id|ppc-&gt;ppc_id
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_sel
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_assign
(paren
id|ppc-&gt;cur_ctrl
op_amp
id|port_int
)paren
op_or
id|port_init
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|i
op_assign
id|ppc-&gt;mode
op_amp
l_int|0x0C
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
id|i
op_assign
(paren
id|ppc-&gt;mode
op_amp
l_int|2
)paren
op_or
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|i
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_sel
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_afd
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|j
op_assign
(paren
(paren
id|i
op_amp
l_int|0x08
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|i
op_amp
l_int|0x07
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|k
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
op_amp
l_int|0xB8
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|k
)paren
(brace
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_afd
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|k
op_assign
(paren
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
op_amp
l_int|0xB8
)paren
op_xor
l_int|0xB8
suffix:semicolon
r_if
c_cond
(paren
id|j
op_eq
id|k
)paren
(brace
r_if
c_cond
(paren
id|i
op_amp
l_int|4
)paren
singleline_comment|// EPP
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
(paren
id|port_sel
op_or
id|port_init
)paren
suffix:semicolon
r_else
singleline_comment|// PPC/ECP
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_sel
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
id|ppc-&gt;org_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;org_data
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
singleline_comment|// FAIL
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_deselect
r_static
r_void
id|ppc6_deselect
c_func
(paren
id|PPC
op_star
id|ppc
)paren
(brace
r_if
c_cond
(paren
id|ppc-&gt;mode
op_amp
l_int|4
)paren
singleline_comment|// EPP
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_init
suffix:semicolon
r_else
singleline_comment|// PPC/ECP
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_sel
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;org_data
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|ppc-&gt;org_ctrl
op_or
id|port_sel
)paren
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;org_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_send_cmd
r_static
r_void
id|ppc6_send_cmd
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|cmd
)paren
(brace
r_switch
c_cond
(paren
id|ppc-&gt;mode
)paren
(brace
r_case
id|PPCMODE_UNI_SW
suffix:colon
r_case
id|PPCMODE_UNI_FW
suffix:colon
r_case
id|PPCMODE_BI_SW
suffix:colon
r_case
id|PPCMODE_BI_FW
suffix:colon
(brace
id|outb
c_func
(paren
id|cmd
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_xor_assign
id|cmd_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_BYTE
suffix:colon
r_case
id|PPCMODE_EPP_WORD
suffix:colon
r_case
id|PPCMODE_EPP_DWORD
suffix:colon
(brace
id|outb
c_func
(paren
id|cmd
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_wr_data_byte
r_static
r_void
id|ppc6_wr_data_byte
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|data
)paren
(brace
r_switch
c_cond
(paren
id|ppc-&gt;mode
)paren
(brace
r_case
id|PPCMODE_UNI_SW
suffix:colon
r_case
id|PPCMODE_UNI_FW
suffix:colon
r_case
id|PPCMODE_BI_SW
suffix:colon
r_case
id|PPCMODE_BI_FW
suffix:colon
(brace
id|outb
c_func
(paren
id|data
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_xor_assign
id|data_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_BYTE
suffix:colon
r_case
id|PPCMODE_EPP_WORD
suffix:colon
r_case
id|PPCMODE_EPP_DWORD
suffix:colon
(brace
id|outb
c_func
(paren
id|data
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_rd_data_byte
r_static
id|u8
id|ppc6_rd_data_byte
c_func
(paren
id|PPC
op_star
id|ppc
)paren
(brace
id|u8
id|data
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|ppc-&gt;mode
)paren
(brace
r_case
id|PPCMODE_UNI_SW
suffix:colon
r_case
id|PPCMODE_UNI_FW
suffix:colon
(brace
id|ppc-&gt;cur_ctrl
op_assign
(paren
id|ppc-&gt;cur_ctrl
op_amp
op_complement
id|port_stb
)paren
op_xor
id|data_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
id|data
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
suffix:semicolon
id|data
op_assign
(paren
(paren
id|data
op_amp
l_int|0x80
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|data
op_amp
l_int|0x38
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
id|data
op_or_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
op_amp
l_int|0xB8
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_BI_SW
suffix:colon
r_case
id|PPCMODE_BI_FW
suffix:colon
(brace
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_dir
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_assign
(paren
id|ppc-&gt;cur_ctrl
op_or
id|port_stb
)paren
op_xor
id|data_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|data
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_dir
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_BYTE
suffix:colon
r_case
id|PPCMODE_EPP_WORD
suffix:colon
r_case
id|PPCMODE_EPP_DWORD
suffix:colon
(brace
id|outb
c_func
(paren
(paren
id|ppc-&gt;cur_ctrl
op_or
id|port_dir
)paren
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|data
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|data
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_rd_port
r_static
id|u8
id|ppc6_rd_port
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
)paren
(brace
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
(paren
id|port
op_or
id|ACCESS_PORT
op_or
id|ACCESS_READ
)paren
)paren
suffix:semicolon
r_return
id|ppc6_rd_data_byte
c_func
(paren
id|ppc
)paren
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_wr_port
r_static
r_void
id|ppc6_wr_port
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
comma
id|u8
id|data
)paren
(brace
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
(paren
id|port
op_or
id|ACCESS_PORT
op_or
id|ACCESS_WRITE
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
id|data
)paren
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_rd_data_blk
r_static
r_void
id|ppc6_rd_data_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_switch
c_cond
(paren
id|ppc-&gt;mode
)paren
(brace
r_case
id|PPCMODE_UNI_SW
suffix:colon
r_case
id|PPCMODE_UNI_FW
suffix:colon
(brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|u8
id|d
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_assign
(paren
id|ppc-&gt;cur_ctrl
op_amp
op_complement
id|port_stb
)paren
op_xor
id|data_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
id|d
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
suffix:semicolon
id|d
op_assign
(paren
(paren
id|d
op_amp
l_int|0x80
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|d
op_amp
l_int|0x38
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
id|d
op_or_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
op_amp
l_int|0xB8
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|d
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_BI_SW
suffix:colon
r_case
id|PPCMODE_BI_FW
suffix:colon
(brace
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_dir
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_stb
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|ppc-&gt;cur_ctrl
op_xor_assign
id|data_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
op_star
id|data
op_increment
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_dir
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_BYTE
suffix:colon
(brace
id|outb
c_func
(paren
(paren
id|ppc-&gt;cur_ctrl
op_or
id|port_dir
)paren
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
r_while
c_loop
(paren
id|count
)paren
(brace
op_star
id|data
op_increment
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_WORD
suffix:colon
(brace
id|outb
c_func
(paren
(paren
id|ppc-&gt;cur_ctrl
op_or
id|port_dir
)paren
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
r_while
c_loop
(paren
id|count
OG
l_int|1
)paren
(brace
op_star
(paren
(paren
id|u16
op_star
)paren
id|data
)paren
op_assign
id|inw
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|data
op_add_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
(brace
op_star
id|data
op_increment
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_DWORD
suffix:colon
(brace
id|outb
c_func
(paren
(paren
id|ppc-&gt;cur_ctrl
op_or
id|port_dir
)paren
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
singleline_comment|// DELAY
r_while
c_loop
(paren
id|count
OG
l_int|3
)paren
(brace
op_star
(paren
(paren
id|u32
op_star
)paren
id|data
)paren
op_assign
id|inl
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|data
op_add_assign
l_int|4
suffix:semicolon
id|count
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
(brace
op_star
id|data
op_increment
op_assign
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_wait_for_fifo
r_static
r_void
id|ppc6_wait_for_fifo
c_func
(paren
id|PPC
op_star
id|ppc
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|ppc-&gt;ppc_flags
op_amp
id|fifo_wait
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
id|inb
c_func
(paren
id|ppc-&gt;lpt_addr
op_plus
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_wr_data_blk
r_static
r_void
id|ppc6_wr_data_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_switch
c_cond
(paren
id|ppc-&gt;mode
)paren
(brace
r_case
id|PPCMODE_UNI_SW
suffix:colon
r_case
id|PPCMODE_BI_SW
suffix:colon
(brace
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|outb
c_func
(paren
op_star
id|data
op_increment
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_xor_assign
id|data_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_UNI_FW
suffix:colon
r_case
id|PPCMODE_BI_FW
suffix:colon
(brace
id|u8
id|this
comma
id|last
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|CMD_PREFIX_SET
op_or
id|PREFIX_FASTWR
)paren
)paren
suffix:semicolon
id|ppc-&gt;cur_ctrl
op_or_assign
id|port_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|last
op_assign
op_star
id|data
suffix:semicolon
id|outb
c_func
(paren
id|last
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|this
op_assign
op_star
id|data
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|this
op_eq
id|last
)paren
(brace
id|ppc-&gt;cur_ctrl
op_xor_assign
id|data_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|this
comma
id|ppc-&gt;lpt_addr
)paren
suffix:semicolon
id|last
op_assign
id|this
suffix:semicolon
)brace
)brace
id|ppc-&gt;cur_ctrl
op_and_assign
op_complement
id|port_stb
suffix:semicolon
id|outb
c_func
(paren
id|ppc-&gt;cur_ctrl
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|2
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|CMD_PREFIX_RESET
op_or
id|PREFIX_FASTWR
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_BYTE
suffix:colon
(brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|outb
c_func
(paren
op_star
id|data
op_increment
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|ppc6_wait_for_fifo
c_func
(paren
id|ppc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_WORD
suffix:colon
(brace
r_while
c_loop
(paren
id|count
OG
l_int|1
)paren
(brace
id|outw
c_func
(paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|data
)paren
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|data
op_add_assign
l_int|2
suffix:semicolon
id|count
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|outb
c_func
(paren
op_star
id|data
op_increment
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|ppc6_wait_for_fifo
c_func
(paren
id|ppc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|PPCMODE_EPP_DWORD
suffix:colon
(brace
r_while
c_loop
(paren
id|count
OG
l_int|3
)paren
(brace
id|outl
c_func
(paren
op_star
(paren
(paren
id|u32
op_star
)paren
id|data
)paren
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|data
op_add_assign
l_int|4
suffix:semicolon
id|count
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
(brace
id|outb
c_func
(paren
op_star
id|data
op_increment
comma
id|ppc-&gt;lpt_addr
op_plus
l_int|4
)paren
suffix:semicolon
id|count
op_decrement
suffix:semicolon
)brace
id|ppc6_wait_for_fifo
c_func
(paren
id|ppc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_rd_port16_blk
r_static
r_void
id|ppc6_rd_port16_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
comma
id|u8
op_star
id|data
comma
r_int
id|length
)paren
(brace
id|length
op_assign
id|length
op_lshift
l_int|1
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|REG_BLKSIZE
op_or
id|ACCESS_REG
op_or
id|ACCESS_WRITE
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
id|length
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
(paren
id|length
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
l_int|0
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|CMD_PREFIX_SET
op_or
id|PREFIX_IO16
op_or
id|PREFIX_BLK
)paren
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
(paren
id|port
op_or
id|ACCESS_PORT
op_or
id|ACCESS_READ
)paren
)paren
suffix:semicolon
id|ppc6_rd_data_blk
c_func
(paren
id|ppc
comma
id|data
comma
id|length
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|CMD_PREFIX_RESET
op_or
id|PREFIX_IO16
op_or
id|PREFIX_BLK
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_wr_port16_blk
r_static
r_void
id|ppc6_wr_port16_blk
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|port
comma
id|u8
op_star
id|data
comma
r_int
id|length
)paren
(brace
id|length
op_assign
id|length
op_lshift
l_int|1
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|REG_BLKSIZE
op_or
id|ACCESS_REG
op_or
id|ACCESS_WRITE
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
id|length
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
(paren
id|length
op_rshift
l_int|8
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
l_int|0
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|CMD_PREFIX_SET
op_or
id|PREFIX_IO16
op_or
id|PREFIX_BLK
)paren
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
(paren
id|port
op_or
id|ACCESS_PORT
op_or
id|ACCESS_WRITE
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_blk
c_func
(paren
id|ppc
comma
id|data
comma
id|length
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|CMD_PREFIX_RESET
op_or
id|PREFIX_IO16
op_or
id|PREFIX_BLK
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_wr_extout
r_static
r_void
id|ppc6_wr_extout
c_func
(paren
id|PPC
op_star
id|ppc
comma
id|u8
id|regdata
)paren
(brace
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|REG_VERSION
op_or
id|ACCESS_REG
op_or
id|ACCESS_WRITE
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
(paren
id|u8
)paren
(paren
(paren
id|regdata
op_amp
l_int|0x03
)paren
op_lshift
l_int|6
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_open
r_static
r_int
id|ppc6_open
c_func
(paren
id|PPC
op_star
id|ppc
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|ppc6_select
c_func
(paren
id|ppc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|ppc-&gt;ppc_flags
op_and_assign
op_complement
id|fifo_wait
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|ACCESS_REG
op_or
id|ACCESS_WRITE
op_or
id|REG_RAMSIZE
)paren
)paren
suffix:semicolon
id|ppc6_wr_data_byte
c_func
(paren
id|ppc
comma
id|RAMSIZE_128K
)paren
suffix:semicolon
id|ppc6_send_cmd
c_func
(paren
id|ppc
comma
(paren
id|ACCESS_REG
op_or
id|ACCESS_READ
op_or
id|REG_VERSION
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ppc6_rd_data_byte
c_func
(paren
id|ppc
)paren
op_amp
l_int|0x3F
)paren
op_eq
l_int|0x0C
)paren
id|ppc-&gt;ppc_flags
op_or_assign
id|fifo_wait
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
DECL|function|ppc6_close
r_static
r_void
id|ppc6_close
c_func
(paren
id|PPC
op_star
id|ppc
)paren
(brace
id|ppc6_deselect
c_func
(paren
id|ppc
)paren
suffix:semicolon
)brace
singleline_comment|//***************************************************************************
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
