multiline_comment|/*******************************************************************************&n;&n;  &n;  Copyright(c) 1999 - 2004 Intel Corporation. All rights reserved.&n;  &n;  This program is free software; you can redistribute it and/or modify it &n;  under the terms of the GNU General Public License as published by the Free &n;  Software Foundation; either version 2 of the License, or (at your option) &n;  any later version.&n;  &n;  This program is distributed in the hope that it will be useful, but WITHOUT &n;  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or &n;  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for &n;  more details.&n;  &n;  You should have received a copy of the GNU General Public License along with&n;  this program; if not, write to the Free Software Foundation, Inc., 59 &n;  Temple Place - Suite 330, Boston, MA  02111-1307, USA.&n;  &n;  The full GNU General Public License is included in this distribution in the&n;  file called LICENSE.&n;  &n;  Contact Information:&n;  Linux NICS &lt;linux.nics@intel.com&gt;&n;  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497&n;&n;*******************************************************************************/
macro_line|#include &quot;ixgb_hw.h&quot;
macro_line|#include &quot;ixgb_ee.h&quot;
multiline_comment|/* Local prototypes */
r_static
r_uint16
id|ixgb_shift_in_bits
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_static
r_void
id|ixgb_shift_out_bits
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|data
comma
r_uint16
id|count
)paren
suffix:semicolon
r_static
r_void
id|ixgb_standby_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_static
id|boolean_t
id|ixgb_wait_eeprom_command
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
r_static
r_void
id|ixgb_cleanup_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
suffix:semicolon
multiline_comment|/******************************************************************************&n; * Raises the EEPROM&squot;s clock input.&n; *&n; * hw - Struct containing variables accessed by shared code&n; * eecd_reg - EECD&squot;s current value&n; *****************************************************************************/
r_static
r_void
DECL|function|ixgb_raise_clock
id|ixgb_raise_clock
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint32
op_star
id|eecd_reg
)paren
(brace
multiline_comment|/* Raise the clock input to the EEPROM (by setting the SK bit), and then&n;&t; *  wait 50 microseconds.&n;&t; */
op_star
id|eecd_reg
op_assign
op_star
id|eecd_reg
op_or
id|IXGB_EECD_SK
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
op_star
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Lowers the EEPROM&squot;s clock input.&n; *&n; * hw - Struct containing variables accessed by shared code&n; * eecd_reg - EECD&squot;s current value&n; *****************************************************************************/
r_static
r_void
DECL|function|ixgb_lower_clock
id|ixgb_lower_clock
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint32
op_star
id|eecd_reg
)paren
(brace
multiline_comment|/* Lower the clock input to the EEPROM (by clearing the SK bit), and then&n;&t; * wait 50 microseconds.&n;&t; */
op_star
id|eecd_reg
op_assign
op_star
id|eecd_reg
op_amp
op_complement
id|IXGB_EECD_SK
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
op_star
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Shift data bits out to the EEPROM.&n; *&n; * hw - Struct containing variables accessed by shared code&n; * data - data to send to the EEPROM&n; * count - number of bits to shift out&n; *****************************************************************************/
r_static
r_void
DECL|function|ixgb_shift_out_bits
id|ixgb_shift_out_bits
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|data
comma
r_uint16
id|count
)paren
(brace
r_uint32
id|eecd_reg
suffix:semicolon
r_uint32
id|mask
suffix:semicolon
multiline_comment|/* We need to shift &quot;count&quot; bits out to the EEPROM. So, value in the&n;&t; * &quot;data&quot; parameter will be shifted out to the EEPROM one bit at a time.&n;&t; * In order to do this, &quot;data&quot; must be broken down into bits.&n;&t; */
id|mask
op_assign
l_int|0x01
op_lshift
(paren
id|count
op_minus
l_int|1
)paren
suffix:semicolon
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
id|eecd_reg
op_and_assign
op_complement
(paren
id|IXGB_EECD_DO
op_or
id|IXGB_EECD_DI
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* A &quot;1&quot; is shifted out to the EEPROM by setting bit &quot;DI&quot; to a &quot;1&quot;,&n;&t;&t; * and then raising and then lowering the clock (the SK bit controls&n;&t;&t; * the clock input to the EEPROM).  A &quot;0&quot; is shifted out to the EEPROM&n;&t;&t; * by setting &quot;DI&quot; to &quot;0&quot; and then raising and then lowering the clock.&n;&t;&t; */
id|eecd_reg
op_and_assign
op_complement
id|IXGB_EECD_DI
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|mask
)paren
(brace
id|eecd_reg
op_or_assign
id|IXGB_EECD_DI
suffix:semicolon
)brace
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|ixgb_raise_clock
c_func
(paren
id|hw
comma
op_amp
id|eecd_reg
)paren
suffix:semicolon
id|ixgb_lower_clock
c_func
(paren
id|hw
comma
op_amp
id|eecd_reg
)paren
suffix:semicolon
id|mask
op_assign
id|mask
op_rshift
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|mask
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* We leave the &quot;DI&quot; bit set to &quot;0&quot; when we leave this routine. */
id|eecd_reg
op_and_assign
op_complement
id|IXGB_EECD_DI
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Shift data bits in from the EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *****************************************************************************/
r_static
r_uint16
DECL|function|ixgb_shift_in_bits
id|ixgb_shift_in_bits
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint32
id|eecd_reg
suffix:semicolon
r_uint32
id|i
suffix:semicolon
r_uint16
id|data
suffix:semicolon
multiline_comment|/* In order to read a register from the EEPROM, we need to shift 16 bits&n;&t; * in from the EEPROM. Bits are &quot;shifted in&quot; by raising the clock input to&n;&t; * the EEPROM (setting the SK bit), and then reading the value of the &quot;DO&quot;&n;&t; * bit.  During this &quot;shifting in&quot; process the &quot;DI&quot; bit should always be&n;&t; * clear..&n;&t; */
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
id|eecd_reg
op_and_assign
op_complement
(paren
id|IXGB_EECD_DO
op_or
id|IXGB_EECD_DI
)paren
suffix:semicolon
id|data
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|data
op_assign
id|data
op_lshift
l_int|1
suffix:semicolon
id|ixgb_raise_clock
c_func
(paren
id|hw
comma
op_amp
id|eecd_reg
)paren
suffix:semicolon
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
id|eecd_reg
op_and_assign
op_complement
(paren
id|IXGB_EECD_DI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eecd_reg
op_amp
id|IXGB_EECD_DO
)paren
(brace
id|data
op_or_assign
l_int|1
suffix:semicolon
)brace
id|ixgb_lower_clock
c_func
(paren
id|hw
comma
op_amp
id|eecd_reg
)paren
suffix:semicolon
)brace
r_return
id|data
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Prepares EEPROM for access&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Lowers EEPROM clock. Clears input pin. Sets the chip select pin. This&n; * function should be called before issuing a command to the EEPROM.&n; *****************************************************************************/
r_static
r_void
DECL|function|ixgb_setup_eeprom
id|ixgb_setup_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint32
id|eecd_reg
suffix:semicolon
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
multiline_comment|/*  Clear SK and DI  */
id|eecd_reg
op_and_assign
op_complement
(paren
id|IXGB_EECD_SK
op_or
id|IXGB_EECD_DI
)paren
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
multiline_comment|/*  Set CS  */
id|eecd_reg
op_or_assign
id|IXGB_EECD_CS
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Returns EEPROM to a &quot;standby&quot; state&n; *&n; * hw - Struct containing variables accessed by shared code&n; *****************************************************************************/
r_static
r_void
DECL|function|ixgb_standby_eeprom
id|ixgb_standby_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint32
id|eecd_reg
suffix:semicolon
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
multiline_comment|/*  Deselct EEPROM  */
id|eecd_reg
op_and_assign
op_complement
(paren
id|IXGB_EECD_CS
op_or
id|IXGB_EECD_SK
)paren
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/*  Clock high  */
id|eecd_reg
op_or_assign
id|IXGB_EECD_SK
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/*  Select EEPROM  */
id|eecd_reg
op_or_assign
id|IXGB_EECD_CS
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/*  Clock low  */
id|eecd_reg
op_and_assign
op_complement
id|IXGB_EECD_SK
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Raises then lowers the EEPROM&squot;s clock pin&n; *&n; * hw - Struct containing variables accessed by shared code&n; *****************************************************************************/
r_static
r_void
DECL|function|ixgb_clock_eeprom
id|ixgb_clock_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint32
id|eecd_reg
suffix:semicolon
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
multiline_comment|/*  Rising edge of clock  */
id|eecd_reg
op_or_assign
id|IXGB_EECD_SK
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
multiline_comment|/*  Falling edge of clock  */
id|eecd_reg
op_and_assign
op_complement
id|IXGB_EECD_SK
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Terminates a command by lowering the EEPROM&squot;s chip select pin&n; *&n; * hw - Struct containing variables accessed by shared code&n; *****************************************************************************/
r_static
r_void
DECL|function|ixgb_cleanup_eeprom
id|ixgb_cleanup_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint32
id|eecd_reg
suffix:semicolon
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
id|eecd_reg
op_and_assign
op_complement
(paren
id|IXGB_EECD_CS
op_or
id|IXGB_EECD_DI
)paren
suffix:semicolon
id|IXGB_WRITE_REG
c_func
(paren
id|hw
comma
id|EECD
comma
id|eecd_reg
)paren
suffix:semicolon
id|ixgb_clock_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Waits for the EEPROM to finish the current command.&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * The command is done when the EEPROM&squot;s data out pin goes high.&n; *&n; * Returns:&n; *      TRUE: EEPROM data pin is high before timeout.&n; *      FALSE:  Time expired.&n; *****************************************************************************/
r_static
id|boolean_t
DECL|function|ixgb_wait_eeprom_command
id|ixgb_wait_eeprom_command
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint32
id|eecd_reg
suffix:semicolon
r_uint32
id|i
suffix:semicolon
multiline_comment|/* Toggle the CS line.  This in effect tells to EEPROM to actually execute&n;&t; * the command in question.&n;&t; */
id|ixgb_standby_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/* Now read DO repeatedly until is high (equal to &squot;1&squot;).  The EEEPROM will&n;&t; * signal that the command has been completed by raising the DO signal.&n;&t; * If DO does not go high in 10 milliseconds, then error out.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|200
suffix:semicolon
id|i
op_increment
)paren
(brace
id|eecd_reg
op_assign
id|IXGB_READ_REG
c_func
(paren
id|hw
comma
id|EECD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eecd_reg
op_amp
id|IXGB_EECD_DO
)paren
(brace
r_return
(paren
id|TRUE
)paren
suffix:semicolon
)brace
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
)brace
id|ASSERT
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Verifies that the EEPROM has a valid checksum&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Reads the first 64 16 bit words of the EEPROM and sums the values read.&n; * If the the sum of the 64 16 bit words is 0xBABA, the EEPROM&squot;s checksum is&n; * valid.&n; *&n; * Returns:&n; *  TRUE: Checksum is valid&n; *  FALSE: Checksum is not valid.&n; *****************************************************************************/
id|boolean_t
DECL|function|ixgb_validate_eeprom_checksum
id|ixgb_validate_eeprom_checksum
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint16
id|checksum
op_assign
l_int|0
suffix:semicolon
r_uint16
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|EEPROM_CHECKSUM_REG
op_plus
l_int|1
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|checksum
op_add_assign
id|ixgb_read_eeprom
c_func
(paren
id|hw
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|checksum
op_eq
(paren
r_uint16
)paren
id|EEPROM_SUM
)paren
(brace
r_return
(paren
id|TRUE
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Calculates the EEPROM checksum and writes it to the EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Sums the first 63 16 bit words of the EEPROM. Subtracts the sum from 0xBABA.&n; * Writes the difference to word offset 63 of the EEPROM.&n; *****************************************************************************/
r_void
DECL|function|ixgb_update_eeprom_checksum
id|ixgb_update_eeprom_checksum
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint16
id|checksum
op_assign
l_int|0
suffix:semicolon
r_uint16
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|EEPROM_CHECKSUM_REG
suffix:semicolon
id|i
op_increment
)paren
(brace
id|checksum
op_add_assign
id|ixgb_read_eeprom
c_func
(paren
id|hw
comma
id|i
)paren
suffix:semicolon
)brace
id|checksum
op_assign
(paren
r_uint16
)paren
id|EEPROM_SUM
op_minus
id|checksum
suffix:semicolon
id|ixgb_write_eeprom
c_func
(paren
id|hw
comma
id|EEPROM_CHECKSUM_REG
comma
id|checksum
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Writes a 16 bit word to a given offset in the EEPROM.&n; *&n; * hw - Struct containing variables accessed by shared code&n; * reg - offset within the EEPROM to be written to&n; * data - 16 bit word to be writen to the EEPROM&n; *&n; * If ixgb_update_eeprom_checksum is not called after this function, the&n; * EEPROM will most likely contain an invalid checksum.&n; *&n; *****************************************************************************/
r_void
DECL|function|ixgb_write_eeprom
id|ixgb_write_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|offset
comma
r_uint16
id|data
)paren
(brace
multiline_comment|/*  Prepare the EEPROM for writing  */
id|ixgb_setup_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/*  Send the 9-bit EWEN (write enable) command to the EEPROM (5-bit opcode&n;&t; *  plus 4-bit dummy).  This puts the EEPROM into write/erase mode.&n;&t; */
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
id|EEPROM_EWEN_OPCODE
comma
l_int|5
)paren
suffix:semicolon
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/*  Prepare the EEPROM  */
id|ixgb_standby_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/*  Send the Write command (3-bit opcode + 6-bit addr)  */
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
id|EEPROM_WRITE_OPCODE
comma
l_int|3
)paren
suffix:semicolon
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
id|offset
comma
l_int|6
)paren
suffix:semicolon
multiline_comment|/*  Send the data  */
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
id|data
comma
l_int|16
)paren
suffix:semicolon
id|ixgb_wait_eeprom_command
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/*  Recover from write  */
id|ixgb_standby_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/* Send the 9-bit EWDS (write disable) command to the EEPROM (5-bit&n;&t; * opcode plus 4-bit dummy).  This takes the EEPROM out of write/erase&n;&t; * mode.&n;&t; */
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
id|EEPROM_EWDS_OPCODE
comma
l_int|5
)paren
suffix:semicolon
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/*  Done with writing  */
id|ixgb_cleanup_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Reads a 16 bit word from the EEPROM.&n; *&n; * hw - Struct containing variables accessed by shared code&n; * offset - offset of 16 bit word in the EEPROM to read&n; *&n; * Returns:&n; *  The 16-bit value read from the eeprom&n; *****************************************************************************/
r_uint16
DECL|function|ixgb_read_eeprom
id|ixgb_read_eeprom
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|offset
)paren
(brace
r_uint16
id|data
suffix:semicolon
multiline_comment|/*  Prepare the EEPROM for reading  */
id|ixgb_setup_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/*  Send the READ command (opcode + addr)  */
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
id|EEPROM_READ_OPCODE
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We have a 64 word EEPROM, there are 6 address bits&n;&t; */
id|ixgb_shift_out_bits
c_func
(paren
id|hw
comma
id|offset
comma
l_int|6
)paren
suffix:semicolon
multiline_comment|/*  Read the data  */
id|data
op_assign
id|ixgb_shift_in_bits
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/*  End this read operation  */
id|ixgb_standby_eeprom
c_func
(paren
id|hw
)paren
suffix:semicolon
r_return
(paren
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Reads eeprom and stores data in shared structure.&n; * Validates eeprom checksum and eeprom signature.&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *      TRUE: if eeprom read is successful&n; *      FALSE: otherwise.&n; *****************************************************************************/
id|boolean_t
DECL|function|ixgb_get_eeprom_data
id|ixgb_get_eeprom_data
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_uint16
id|i
suffix:semicolon
r_uint16
id|checksum
op_assign
l_int|0
suffix:semicolon
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
suffix:semicolon
id|DEBUGFUNC
c_func
(paren
l_string|&quot;ixgb_get_eeprom_data&quot;
)paren
suffix:semicolon
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
id|DEBUGOUT
c_func
(paren
l_string|&quot;ixgb_ee: Reading eeprom data&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IXGB_EEPROM_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_uint16
id|ee_data
suffix:semicolon
id|ee_data
op_assign
id|ixgb_read_eeprom
c_func
(paren
id|hw
comma
id|i
)paren
suffix:semicolon
id|checksum
op_add_assign
id|ee_data
suffix:semicolon
id|hw-&gt;eeprom
(braket
id|i
)braket
op_assign
id|le16_to_cpu
c_func
(paren
id|ee_data
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|checksum
op_ne
(paren
r_uint16
)paren
id|EEPROM_SUM
)paren
(brace
id|DEBUGOUT
c_func
(paren
l_string|&quot;ixgb_ee: Checksum invalid.&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|ee_map-&gt;init_ctrl_reg_1
op_amp
id|le16_to_cpu
c_func
(paren
id|EEPROM_ICW1_SIGNATURE_MASK
)paren
)paren
op_ne
id|le16_to_cpu
c_func
(paren
id|EEPROM_ICW1_SIGNATURE_VALID
)paren
)paren
(brace
id|DEBUGOUT
c_func
(paren
l_string|&quot;ixgb_ee: Signature invalid.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|FALSE
suffix:semicolon
)brace
r_return
id|TRUE
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * Local function to check if the eeprom signature is good&n; * If the eeprom signature is good, calls ixgb)get_eeprom_data.&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *      TRUE: eeprom signature was good and the eeprom read was successful&n; *      FALSE: otherwise.&n; ******************************************************************************/
r_static
id|boolean_t
DECL|function|ixgb_check_and_get_eeprom_data
id|ixgb_check_and_get_eeprom_data
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ee_map-&gt;init_ctrl_reg_1
op_amp
id|le16_to_cpu
c_func
(paren
id|EEPROM_ICW1_SIGNATURE_MASK
)paren
)paren
op_eq
id|le16_to_cpu
c_func
(paren
id|EEPROM_ICW1_SIGNATURE_VALID
)paren
)paren
(brace
r_return
(paren
id|TRUE
)paren
suffix:semicolon
)brace
r_else
(brace
r_return
id|ixgb_get_eeprom_data
c_func
(paren
id|hw
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/******************************************************************************&n; * return a word from the eeprom&n; *&n; * hw - Struct containing variables accessed by shared code&n; * index - Offset of eeprom word&n; *&n; * Returns:&n; *          Word at indexed offset in eeprom, if valid, 0 otherwise.&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_eeprom_word
id|ixgb_get_eeprom_word
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint16
id|index
)paren
(brace
r_if
c_cond
(paren
(paren
id|index
OL
id|IXGB_EEPROM_SIZE
)paren
op_logical_and
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
)paren
(brace
r_return
id|hw-&gt;eeprom
(braket
id|index
)braket
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the mac address from EEPROM&n; *&n; * hw       - Struct containing variables accessed by shared code&n; * mac_addr - Ethernet Address if EEPROM contents are valid, 0 otherwise&n; *&n; * Returns: None.&n; ******************************************************************************/
r_void
DECL|function|ixgb_get_ee_mac_addr
id|ixgb_get_ee_mac_addr
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
comma
r_uint8
op_star
id|mac_addr
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
id|DEBUGFUNC
c_func
(paren
l_string|&quot;ixgb_get_ee_mac_addr&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
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
id|IXGB_ETH_LENGTH_OF_ADDRESS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mac_addr
(braket
id|i
)braket
op_assign
id|ee_map-&gt;mac_addr
(braket
id|i
)braket
suffix:semicolon
id|DEBUGOUT2
c_func
(paren
l_string|&quot;mac(%d) = %.2X&bslash;n&quot;
comma
id|i
comma
id|mac_addr
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/******************************************************************************&n; * return the compatibility flags from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          compatibility flags if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_compatibility
id|ixgb_get_ee_compatibility
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;compatibility
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Printed Board Assembly number from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          PBA number if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint32
DECL|function|ixgb_get_ee_pba_number
id|ixgb_get_ee_pba_number
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
(paren
id|le16_to_cpu
c_func
(paren
id|hw-&gt;eeprom
(braket
id|EEPROM_PBA_1_2_REG
)braket
)paren
op_or
(paren
id|le16_to_cpu
c_func
(paren
id|hw-&gt;eeprom
(braket
id|EEPROM_PBA_3_4_REG
)braket
)paren
op_lshift
l_int|16
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Initialization Control Word 1 from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          Initialization Control Word 1 if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_init_ctrl_reg_1
id|ixgb_get_ee_init_ctrl_reg_1
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;init_ctrl_reg_1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Initialization Control Word 2 from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          Initialization Control Word 2 if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_init_ctrl_reg_2
id|ixgb_get_ee_init_ctrl_reg_2
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;init_ctrl_reg_2
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Subsystem Id from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          Subsystem Id if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_subsystem_id
id|ixgb_get_ee_subsystem_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;subsystem_id
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Sub Vendor Id from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          Sub Vendor Id if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_subvendor_id
id|ixgb_get_ee_subvendor_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;subvendor_id
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Device Id from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          Device Id if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_device_id
id|ixgb_get_ee_device_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;device_id
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Vendor Id from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          Device Id if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_vendor_id
id|ixgb_get_ee_vendor_id
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;vendor_id
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the Software Defined Pins Register from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          SDP Register if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint16
DECL|function|ixgb_get_ee_swdpins_reg
id|ixgb_get_ee_swdpins_reg
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;swdpins_reg
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the D3 Power Management Bits from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          D3 Power Management Bits if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint8
DECL|function|ixgb_get_ee_d3_power
id|ixgb_get_ee_d3_power
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;d3_power
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; * return the D0 Power Management Bits from EEPROM&n; *&n; * hw - Struct containing variables accessed by shared code&n; *&n; * Returns:&n; *          D0 Power Management Bits if EEPROM contents are valid, 0 otherwise&n; ******************************************************************************/
r_uint8
DECL|function|ixgb_get_ee_d0_power
id|ixgb_get_ee_d0_power
c_func
(paren
r_struct
id|ixgb_hw
op_star
id|hw
)paren
(brace
r_struct
id|ixgb_ee_map_type
op_star
id|ee_map
op_assign
(paren
r_struct
id|ixgb_ee_map_type
op_star
)paren
id|hw-&gt;eeprom
suffix:semicolon
r_if
c_cond
(paren
id|ixgb_check_and_get_eeprom_data
c_func
(paren
id|hw
)paren
op_eq
id|TRUE
)paren
(brace
r_return
id|ee_map-&gt;d0_power
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
