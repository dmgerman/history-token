multiline_comment|/*******************************************************************************&n;&n;This software program is available to you under a choice of one of two &n;licenses. You may choose to be licensed under either the GNU General Public &n;License 2.0, June 1991, available at http://www.fsf.org/copyleft/gpl.html, &n;or the Intel BSD + Patent License, the text of which follows:&n;&n;Recipient has requested a license and Intel Corporation (&quot;Intel&quot;) is willing&n;to grant a license for the software entitled Linux Base Driver for the &n;Intel(R) PRO/100 Family of Adapters (e100) (the &quot;Software&quot;) being provided &n;by Intel Corporation. The following definitions apply to this license:&n;&n;&quot;Licensed Patents&quot; means patent claims licensable by Intel Corporation which &n;are necessarily infringed by the use of sale of the Software alone or when &n;combined with the operating system referred to below.&n;&n;&quot;Recipient&quot; means the party to whom Intel delivers this Software.&n;&n;&quot;Licensee&quot; means Recipient and those third parties that receive a license to &n;any operating system available under the GNU General Public License 2.0 or &n;later.&n;&n;Copyright (c) 1999 - 2002 Intel Corporation.&n;All rights reserved.&n;&n;The license is provided to Recipient and Recipient&squot;s Licensees under the &n;following terms.&n;&n;Redistribution and use in source and binary forms of the Software, with or &n;without modification, are permitted provided that the following conditions &n;are met:&n;&n;Redistributions of source code of the Software may retain the above &n;copyright notice, this list of conditions and the following disclaimer.&n;&n;Redistributions in binary form of the Software may reproduce the above &n;copyright notice, this list of conditions and the following disclaimer in &n;the documentation and/or materials provided with the distribution.&n;&n;Neither the name of Intel Corporation nor the names of its contributors &n;shall be used to endorse or promote products derived from this Software &n;without specific prior written permission.&n;&n;Intel hereby grants Recipient and Licensees a non-exclusive, worldwide, &n;royalty-free patent license under Licensed Patents to make, use, sell, offer &n;to sell, import and otherwise transfer the Software, if any, in source code &n;and object code form. This license shall include changes to the Software &n;that are error corrections or other minor changes to the Software that do &n;not add functionality or features when the Software is incorporated in any &n;version of an operating system that has been distributed under the GNU &n;General Public License 2.0 or later. This patent license shall apply to the &n;combination of the Software and any operating system licensed under the GNU &n;General Public License 2.0 or later if, at the time Intel provides the &n;Software to Recipient, such addition of the Software to the then publicly &n;available versions of such operating systems available under the GNU General &n;Public License 2.0 or later (whether in gold, beta or alpha form) causes &n;such combination to be covered by the Licensed Patents. The patent license &n;shall not apply to any other combinations which include the Software. NO &n;hardware per se is licensed hereunder.&n;&n;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS &quot;AS IS&quot; &n;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE &n;IMPLIED WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE &n;ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR IT CONTRIBUTORS BE LIABLE FOR ANY &n;DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES &n;(INCLUDING, BUT NOT LIMITED, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; &n;ANY LOSS OF USE; DATA, OR PROFITS; OR BUSINESS INTERUPTION) HOWEVER CAUSED &n;AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY OR &n;TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE &n;OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n;*******************************************************************************&n;&n;Portions (C) 2002 Red Hat, Inc. under the terms of the GNU GPL v2.&n;&n;*******************************************************************************/
multiline_comment|/**********************************************************************&n;*                                                                     *&n;* INTEL CORPORATION                                                   *&n;*                                                                     *&n;* This software is supplied under the terms of the license included   *&n;* above.  All use of this driver must be in accordance with the terms *&n;* of that license.                                                    *&n;*                                                                     *&n;* Module Name:  e100_eeprom.c                                         *&n;*                                                                     *&n;* Abstract:     This module contains routines to read and write to a  *&n;*               serial EEPROM                                         *&n;*                                                                     *&n;* Environment:  This file is intended to be specific to the Linux     *&n;*               operating system.                                     *&n;*                                                                     *&n;**********************************************************************/
macro_line|#include &quot;e100.h&quot;
DECL|macro|CSR_EEPROM_CONTROL_FIELD
mdefine_line|#define CSR_EEPROM_CONTROL_FIELD(bdp) ((bdp)-&gt;scb-&gt;scb_eprm_cntrl)
DECL|macro|CSR_GENERAL_CONTROL2_FIELD
mdefine_line|#define CSR_GENERAL_CONTROL2_FIELD(bdp) &bslash;&n;&t;           ((bdp)-&gt;scb-&gt;scb_ext.d102_scb.scb_gen_ctrl2)
DECL|macro|EEPROM_STALL_TIME
mdefine_line|#define EEPROM_STALL_TIME&t;4
DECL|macro|EEPROM_CHECKSUM
mdefine_line|#define EEPROM_CHECKSUM&t;&t;((u16) 0xBABA)
DECL|macro|EEPROM_MAX_WORD_SIZE
mdefine_line|#define EEPROM_MAX_WORD_SIZE&t;256
r_void
id|e100_eeprom_cleanup
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
suffix:semicolon
id|u16
id|e100_eeprom_calculate_chksum
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_void
id|e100_eeprom_write_word
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|reg
comma
id|u16
id|data
)paren
suffix:semicolon
r_void
id|e100_eeprom_write_block
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|start
comma
id|u16
op_star
id|data
comma
id|u16
id|size
)paren
suffix:semicolon
id|u16
id|e100_eeprom_size
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
suffix:semicolon
id|u16
id|e100_eeprom_read
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|reg
)paren
suffix:semicolon
r_static
r_void
id|shift_out_bits
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|data
comma
id|u16
id|count
)paren
suffix:semicolon
r_static
id|u16
id|shift_in_bits
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_void
id|raise_clock
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
op_star
id|x
)paren
suffix:semicolon
r_static
r_void
id|lower_clock
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
op_star
id|x
)paren
suffix:semicolon
r_static
id|u16
id|eeprom_wait_cmd_done
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
suffix:semicolon
r_static
r_void
id|eeprom_stand_by
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
suffix:semicolon
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   eeprom_set_semaphore
singleline_comment|//
singleline_comment|// Description: This function set (write 1) Gamla EEPROM semaphore bit (bit 23 word 0x1C in the CSR).
singleline_comment|//
singleline_comment|// Arguments:
singleline_comment|//      Adapter                 - Adapter context
singleline_comment|//
singleline_comment|// Returns:  true if success
singleline_comment|//           else return false 
singleline_comment|//
singleline_comment|//----------------------------------------------------------------------------------------
r_inline
id|u8
DECL|function|eeprom_set_semaphore
id|eeprom_set_semaphore
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|data
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|expiration_time
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|100
op_plus
l_int|1
suffix:semicolon
r_do
(brace
singleline_comment|// Get current value of General Control 2
id|data
op_assign
id|readb
c_func
(paren
op_amp
id|CSR_GENERAL_CONTROL2_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
singleline_comment|// Set bit 23 word 0x1C in the CSR.
id|data
op_or_assign
id|SCB_GCR2_EEPROM_ACCESS_SEMAPHORE
suffix:semicolon
id|writeb
c_func
(paren
id|data
comma
op_amp
id|CSR_GENERAL_CONTROL2_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
singleline_comment|// Check to see if this bit set or not.
id|data
op_assign
id|readb
c_func
(paren
op_amp
id|CSR_GENERAL_CONTROL2_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|SCB_GCR2_EEPROM_ACCESS_SEMAPHORE
)paren
(brace
r_return
l_bool|true
suffix:semicolon
)brace
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|expiration_time
)paren
)paren
id|yield
c_func
(paren
)paren
suffix:semicolon
r_else
r_return
l_bool|false
suffix:semicolon
)brace
r_while
c_loop
(paren
l_bool|true
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   eeprom_reset_semaphore
singleline_comment|//
singleline_comment|// Description: This function reset (write 0) Gamla EEPROM semaphore bit 
singleline_comment|//              (bit 23 word 0x1C in the CSR).
singleline_comment|//
singleline_comment|// Arguments:  struct e100_private * adapter - Adapter context
singleline_comment|//----------------------------------------------------------------------------------------
r_inline
r_void
DECL|function|eeprom_reset_semaphore
id|eeprom_reset_semaphore
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|data
op_assign
l_int|0
suffix:semicolon
id|data
op_assign
id|readb
c_func
(paren
op_amp
id|CSR_GENERAL_CONTROL2_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|data
op_and_assign
op_complement
(paren
id|SCB_GCR2_EEPROM_ACCESS_SEMAPHORE
)paren
suffix:semicolon
id|writeb
c_func
(paren
id|data
comma
op_amp
id|CSR_GENERAL_CONTROL2_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   e100_eeprom_size
singleline_comment|//
singleline_comment|// Description: This routine determines the size of the EEPROM.  This value should be
singleline_comment|//              checked for validity - ie. is it too big or too small.  The size returned
singleline_comment|//              is then passed to the read/write functions.
singleline_comment|//
singleline_comment|// Returns:
singleline_comment|//      Size of the eeprom, or zero if an error occured
singleline_comment|//----------------------------------------------------------------------------------------
id|u16
DECL|function|e100_eeprom_size
id|e100_eeprom_size
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|x
comma
id|size
op_assign
l_int|1
suffix:semicolon
singleline_comment|// must be one to accumulate a product
singleline_comment|// if we&squot;ve already stored this data, read from memory
r_if
c_cond
(paren
id|adapter-&gt;eeprom_size
)paren
(brace
r_return
id|adapter-&gt;eeprom_size
suffix:semicolon
)brace
singleline_comment|// otherwise, read from the eeprom
singleline_comment|// Set EEPROM semaphore.
r_if
c_cond
(paren
id|adapter-&gt;rev_id
op_ge
id|D102_REV_ID
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|eeprom_set_semaphore
c_func
(paren
id|adapter
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// enable the eeprom by setting EECS.
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|EEDI
op_or
id|EEDO
op_or
id|EESK
)paren
suffix:semicolon
id|x
op_or_assign
id|EECS
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
singleline_comment|// write the read opcode
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|EEPROM_READ_OPCODE
comma
l_int|3
)paren
suffix:semicolon
singleline_comment|// experiment to discover the size of the eeprom.  request register zero
singleline_comment|// and wait for the eeprom to tell us it has accepted the entire address.
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
r_do
(brace
id|size
op_mul_assign
l_int|2
suffix:semicolon
singleline_comment|// each bit of address doubles eeprom size
id|x
op_or_assign
id|EEDO
suffix:semicolon
singleline_comment|// set bit to detect &quot;dummy zero&quot;
id|x
op_and_assign
op_complement
id|EEDI
suffix:semicolon
singleline_comment|// address consists of all zeros
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|EEPROM_STALL_TIME
)paren
suffix:semicolon
id|raise_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
)paren
suffix:semicolon
id|lower_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
)paren
suffix:semicolon
singleline_comment|// check for &quot;dummy zero&quot;
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|EEPROM_MAX_WORD_SIZE
)paren
(brace
id|size
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|x
op_amp
id|EEDO
)paren
suffix:semicolon
singleline_comment|// read in the value requested
(paren
r_void
)paren
id|shift_in_bits
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|e100_eeprom_cleanup
c_func
(paren
id|adapter
)paren
suffix:semicolon
singleline_comment|// Clear EEPROM Semaphore.
r_if
c_cond
(paren
id|adapter-&gt;rev_id
op_ge
id|D102_REV_ID
)paren
(brace
id|eeprom_reset_semaphore
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
r_return
id|size
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   eeprom_address_size
singleline_comment|//
singleline_comment|// Description: determines the number of bits in an address for the eeprom acceptable
singleline_comment|//              values are 64, 128, and 256
singleline_comment|// Arguments: size of the eeprom
singleline_comment|// Returns: bits in an address for that size eeprom
singleline_comment|//----------------------------------------------------------------------------------------
r_static
r_inline
r_int
DECL|function|eeprom_address_size
id|eeprom_address_size
c_func
(paren
id|u16
id|size
)paren
(brace
r_int
id|isize
op_assign
id|size
suffix:semicolon
r_return
(paren
id|ffs
c_func
(paren
id|isize
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   e100_eeprom_read
singleline_comment|//
singleline_comment|// Description: This routine serially reads one word out of the EEPROM.
singleline_comment|//
singleline_comment|// Arguments:
singleline_comment|//      adapter - our adapter context
singleline_comment|//      reg - EEPROM word to read.
singleline_comment|//
singleline_comment|// Returns:
singleline_comment|//      Contents of EEPROM word (reg).
singleline_comment|//----------------------------------------------------------------------------------------
id|u16
DECL|function|e100_eeprom_read
id|e100_eeprom_read
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|reg
)paren
(brace
id|u16
id|x
comma
id|data
comma
id|bits
suffix:semicolon
singleline_comment|// Set EEPROM semaphore.
r_if
c_cond
(paren
id|adapter-&gt;rev_id
op_ge
id|D102_REV_ID
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|eeprom_set_semaphore
c_func
(paren
id|adapter
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
singleline_comment|// eeprom size is initialized to zero
r_if
c_cond
(paren
op_logical_neg
id|adapter-&gt;eeprom_size
)paren
id|adapter-&gt;eeprom_size
op_assign
id|e100_eeprom_size
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|bits
op_assign
id|eeprom_address_size
c_func
(paren
id|adapter-&gt;eeprom_size
)paren
suffix:semicolon
singleline_comment|// select EEPROM, reset bits, set EECS
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|EEDI
op_or
id|EEDO
op_or
id|EESK
)paren
suffix:semicolon
id|x
op_or_assign
id|EECS
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
singleline_comment|// write the read opcode and register number in that order
singleline_comment|// The opcode is 3bits in length, reg is &squot;bits&squot; bits long
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|EEPROM_READ_OPCODE
comma
l_int|3
)paren
suffix:semicolon
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|reg
comma
id|bits
)paren
suffix:semicolon
singleline_comment|// Now read the data (16 bits) in from the selected EEPROM word
id|data
op_assign
id|shift_in_bits
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|e100_eeprom_cleanup
c_func
(paren
id|adapter
)paren
suffix:semicolon
singleline_comment|// Clear EEPROM Semaphore.
r_if
c_cond
(paren
id|adapter-&gt;rev_id
op_ge
id|D102_REV_ID
)paren
(brace
id|eeprom_reset_semaphore
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
r_return
id|data
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   shift_out_bits
singleline_comment|//
singleline_comment|// Description: This routine shifts data bits out to the EEPROM.
singleline_comment|//
singleline_comment|// Arguments:
singleline_comment|//      data - data to send to the EEPROM.
singleline_comment|//      count - number of data bits to shift out.
singleline_comment|//
singleline_comment|// Returns: (none)
singleline_comment|//----------------------------------------------------------------------------------------
r_static
r_void
DECL|function|shift_out_bits
id|shift_out_bits
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|data
comma
id|u16
id|count
)paren
(brace
id|u16
id|x
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|count
op_minus
l_int|1
)paren
suffix:semicolon
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|EEDO
op_or
id|EEDI
)paren
suffix:semicolon
r_do
(brace
id|x
op_and_assign
op_complement
id|EEDI
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
id|mask
)paren
id|x
op_or_assign
id|EEDI
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|readw
c_func
(paren
op_amp
(paren
id|adapter-&gt;scb-&gt;scb_status
)paren
)paren
suffix:semicolon
multiline_comment|/* flush command to card */
id|udelay
c_func
(paren
id|EEPROM_STALL_TIME
)paren
suffix:semicolon
id|raise_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
)paren
suffix:semicolon
id|lower_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
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
suffix:semicolon
id|x
op_and_assign
op_complement
id|EEDI
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   raise_clock
singleline_comment|//
singleline_comment|// Description: This routine raises the EEPROM&squot;s clock input (EESK)
singleline_comment|//
singleline_comment|// Arguments:
singleline_comment|//      x - Ptr to the EEPROM control register&squot;s current value
singleline_comment|//
singleline_comment|// Returns: (none)
singleline_comment|//----------------------------------------------------------------------------------------
r_void
DECL|function|raise_clock
id|raise_clock
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
op_star
id|x
)paren
(brace
op_star
id|x
op_assign
op_star
id|x
op_or
id|EESK
suffix:semicolon
id|writew
c_func
(paren
op_star
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|readw
c_func
(paren
op_amp
(paren
id|adapter-&gt;scb-&gt;scb_status
)paren
)paren
suffix:semicolon
multiline_comment|/* flush command to card */
id|udelay
c_func
(paren
id|EEPROM_STALL_TIME
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   lower_clock
singleline_comment|//
singleline_comment|// Description: This routine lower&squot;s the EEPROM&squot;s clock input (EESK)
singleline_comment|//
singleline_comment|// Arguments:
singleline_comment|//      x - Ptr to the EEPROM control register&squot;s current value
singleline_comment|//
singleline_comment|// Returns: (none)
singleline_comment|//----------------------------------------------------------------------------------------
r_void
DECL|function|lower_clock
id|lower_clock
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
op_star
id|x
)paren
(brace
op_star
id|x
op_assign
op_star
id|x
op_amp
op_complement
id|EESK
suffix:semicolon
id|writew
c_func
(paren
op_star
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|readw
c_func
(paren
op_amp
(paren
id|adapter-&gt;scb-&gt;scb_status
)paren
)paren
suffix:semicolon
multiline_comment|/* flush command to card */
id|udelay
c_func
(paren
id|EEPROM_STALL_TIME
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   shift_in_bits
singleline_comment|//
singleline_comment|// Description: This routine shifts data bits in from the EEPROM.
singleline_comment|//
singleline_comment|// Arguments:
singleline_comment|//
singleline_comment|// Returns:
singleline_comment|//      The contents of that particular EEPROM word
singleline_comment|//----------------------------------------------------------------------------------------
r_static
id|u16
DECL|function|shift_in_bits
id|shift_in_bits
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|x
comma
id|d
comma
id|i
suffix:semicolon
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|EEDO
op_or
id|EEDI
)paren
suffix:semicolon
id|d
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
id|d
op_lshift_assign
l_int|1
suffix:semicolon
id|raise_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
)paren
suffix:semicolon
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
id|EEDI
suffix:semicolon
r_if
c_cond
(paren
id|x
op_amp
id|EEDO
)paren
id|d
op_or_assign
l_int|1
suffix:semicolon
id|lower_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
)paren
suffix:semicolon
)brace
r_return
id|d
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   e100_eeprom_cleanup
singleline_comment|//
singleline_comment|// Description: This routine returns the EEPROM to an idle state
singleline_comment|//----------------------------------------------------------------------------------------
r_void
DECL|function|e100_eeprom_cleanup
id|e100_eeprom_cleanup
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|x
suffix:semicolon
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|EECS
op_or
id|EEDI
)paren
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|raise_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
)paren
suffix:semicolon
id|lower_clock
c_func
(paren
id|adapter
comma
op_amp
id|x
)paren
suffix:semicolon
)brace
singleline_comment|//**********************************************************************************
singleline_comment|// Procedure:   e100_eeprom_update_chksum
singleline_comment|//
singleline_comment|// Description: Calculates the checksum and writes it to the EEProm. 
singleline_comment|//              It calculates the checksum accroding to the formula: 
singleline_comment|//                              Checksum = 0xBABA - (sum of first 63 words).
singleline_comment|//
singleline_comment|//-----------------------------------------------------------------------------------
id|u16
DECL|function|e100_eeprom_calculate_chksum
id|e100_eeprom_calculate_chksum
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|idx
comma
id|xsum_index
comma
id|checksum
op_assign
l_int|0
suffix:semicolon
singleline_comment|// eeprom size is initialized to zero
r_if
c_cond
(paren
op_logical_neg
id|adapter-&gt;eeprom_size
)paren
id|adapter-&gt;eeprom_size
op_assign
id|e100_eeprom_size
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|xsum_index
op_assign
id|adapter-&gt;eeprom_size
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
id|xsum_index
suffix:semicolon
id|idx
op_increment
)paren
id|checksum
op_add_assign
id|e100_eeprom_read
c_func
(paren
id|adapter
comma
id|idx
)paren
suffix:semicolon
id|checksum
op_assign
id|EEPROM_CHECKSUM
op_minus
id|checksum
suffix:semicolon
r_return
id|checksum
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   e100_eeprom_write_word
singleline_comment|//
singleline_comment|// Description: This routine writes a word to a specific EEPROM location without.
singleline_comment|//              taking EEPROM semaphore and updating checksum. 
singleline_comment|//              Use e100_eeprom_write_block for the EEPROM update
singleline_comment|// Arguments: reg - The EEPROM word that we are going to write to.
singleline_comment|//            data - The data (word) that we are going to write to the EEPROM.
singleline_comment|//----------------------------------------------------------------------------------------
r_static
r_void
DECL|function|e100_eeprom_write_word
id|e100_eeprom_write_word
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|reg
comma
id|u16
id|data
)paren
(brace
id|u16
id|x
suffix:semicolon
id|u16
id|bits
suffix:semicolon
id|bits
op_assign
id|eeprom_address_size
c_func
(paren
id|adapter-&gt;eeprom_size
)paren
suffix:semicolon
multiline_comment|/* select EEPROM, mask off ASIC and reset bits, set EECS */
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|EEDI
op_or
id|EEDO
op_or
id|EESK
)paren
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|readw
c_func
(paren
op_amp
(paren
id|adapter-&gt;scb-&gt;scb_status
)paren
)paren
suffix:semicolon
multiline_comment|/* flush command to card */
id|udelay
c_func
(paren
id|EEPROM_STALL_TIME
)paren
suffix:semicolon
id|x
op_or_assign
id|EECS
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|EEPROM_EWEN_OPCODE
comma
l_int|5
)paren
suffix:semicolon
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|reg
comma
(paren
id|u16
)paren
(paren
id|bits
op_minus
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eeprom_wait_cmd_done
c_func
(paren
id|adapter
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* write the new word to the EEPROM &amp; send the write opcode the EEPORM */
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|EEPROM_WRITE_OPCODE
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* select which word in the EEPROM that we are writing to */
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|reg
comma
id|bits
)paren
suffix:semicolon
multiline_comment|/* write the data to the selected EEPROM word */
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|data
comma
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eeprom_wait_cmd_done
c_func
(paren
id|adapter
)paren
)paren
r_return
suffix:semicolon
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|EEPROM_EWDS_OPCODE
comma
l_int|5
)paren
suffix:semicolon
id|shift_out_bits
c_func
(paren
id|adapter
comma
id|reg
comma
(paren
id|u16
)paren
(paren
id|bits
op_minus
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eeprom_wait_cmd_done
c_func
(paren
id|adapter
)paren
)paren
r_return
suffix:semicolon
id|e100_eeprom_cleanup
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   e100_eeprom_write_block
singleline_comment|//
singleline_comment|// Description: This routine writes a block of words starting from specified EEPROM 
singleline_comment|//              location and updates checksum
singleline_comment|// Arguments: reg - The EEPROM word that we are going to write to.
singleline_comment|//            data - The data (word) that we are going to write to the EEPROM.
singleline_comment|//----------------------------------------------------------------------------------------
r_void
DECL|function|e100_eeprom_write_block
id|e100_eeprom_write_block
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
comma
id|u16
id|start
comma
id|u16
op_star
id|data
comma
id|u16
id|size
)paren
(brace
id|u16
id|checksum
suffix:semicolon
id|u16
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|adapter-&gt;eeprom_size
)paren
id|adapter-&gt;eeprom_size
op_assign
id|e100_eeprom_size
c_func
(paren
id|adapter
)paren
suffix:semicolon
singleline_comment|// Set EEPROM semaphore.
r_if
c_cond
(paren
id|adapter-&gt;rev_id
op_ge
id|D102_REV_ID
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|eeprom_set_semaphore
c_func
(paren
id|adapter
)paren
)paren
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|size
suffix:semicolon
id|i
op_increment
)paren
(brace
id|e100_eeprom_write_word
c_func
(paren
id|adapter
comma
id|start
op_plus
id|i
comma
id|data
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
singleline_comment|//Update checksum
id|checksum
op_assign
id|e100_eeprom_calculate_chksum
c_func
(paren
id|adapter
)paren
suffix:semicolon
id|e100_eeprom_write_word
c_func
(paren
id|adapter
comma
(paren
id|adapter-&gt;eeprom_size
op_minus
l_int|1
)paren
comma
id|checksum
)paren
suffix:semicolon
singleline_comment|// Clear EEPROM Semaphore.
r_if
c_cond
(paren
id|adapter-&gt;rev_id
op_ge
id|D102_REV_ID
)paren
(brace
id|eeprom_reset_semaphore
c_func
(paren
id|adapter
)paren
suffix:semicolon
)brace
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   eeprom_wait_cmd_done
singleline_comment|//
singleline_comment|// Description: This routine waits for the the EEPROM to finish its command.  
singleline_comment|//                              Specifically, it waits for EEDO (data out) to go high.
singleline_comment|// Returns:     true - If the command finished
singleline_comment|//              false - If the command never finished (EEDO stayed low)
singleline_comment|//----------------------------------------------------------------------------------------
r_static
id|u16
DECL|function|eeprom_wait_cmd_done
id|eeprom_wait_cmd_done
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|x
suffix:semicolon
r_int
r_int
id|expiration_time
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|100
op_plus
l_int|1
suffix:semicolon
id|eeprom_stand_by
c_func
(paren
id|adapter
)paren
suffix:semicolon
r_do
(brace
id|rmb
c_func
(paren
)paren
suffix:semicolon
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|x
op_amp
id|EEDO
)paren
r_return
l_bool|true
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|expiration_time
)paren
)paren
id|yield
c_func
(paren
)paren
suffix:semicolon
r_else
r_return
l_bool|false
suffix:semicolon
)brace
r_while
c_loop
(paren
l_bool|true
)paren
suffix:semicolon
)brace
singleline_comment|//----------------------------------------------------------------------------------------
singleline_comment|// Procedure:   eeprom_stand_by
singleline_comment|//
singleline_comment|// Description: This routine lowers the EEPROM chip select (EECS) for a few microseconds.
singleline_comment|//----------------------------------------------------------------------------------------
r_static
r_void
DECL|function|eeprom_stand_by
id|eeprom_stand_by
c_func
(paren
r_struct
id|e100_private
op_star
id|adapter
)paren
(brace
id|u16
id|x
suffix:semicolon
id|x
op_assign
id|readw
c_func
(paren
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|x
op_and_assign
op_complement
(paren
id|EECS
op_or
id|EESK
)paren
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|readw
c_func
(paren
op_amp
(paren
id|adapter-&gt;scb-&gt;scb_status
)paren
)paren
suffix:semicolon
multiline_comment|/* flush command to card */
id|udelay
c_func
(paren
id|EEPROM_STALL_TIME
)paren
suffix:semicolon
id|x
op_or_assign
id|EECS
suffix:semicolon
id|writew
c_func
(paren
id|x
comma
op_amp
id|CSR_EEPROM_CONTROL_FIELD
c_func
(paren
id|adapter
)paren
)paren
suffix:semicolon
id|readw
c_func
(paren
op_amp
(paren
id|adapter-&gt;scb-&gt;scb_status
)paren
)paren
suffix:semicolon
multiline_comment|/* flush command to card */
id|udelay
c_func
(paren
id|EEPROM_STALL_TIME
)paren
suffix:semicolon
)brace
eof
