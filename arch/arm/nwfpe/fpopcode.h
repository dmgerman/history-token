multiline_comment|/*&n;    NetWinder Floating Point Emulator&n;    (c) Rebel.com, 1998-1999&n;&n;    Direct questions, comments to Scott Bambrough &lt;scottb@netwinder.org&gt;&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef __FPOPCODE_H__
DECL|macro|__FPOPCODE_H__
mdefine_line|#define __FPOPCODE_H__
multiline_comment|/*&n;ARM Floating Point Instruction Classes&n;| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | &n;|c o n d|1 1 0 P|U|u|W|L|   Rn  |v|  Fd |0|0|0|1|  o f f s e t  | CPDT&n;|c o n d|1 1 0 P|U|w|W|L|   Rn  |x|  Fd |0|0|0|1|  o f f s e t  | CPDT&n;| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | &n;|c o n d|1 1 1 0|a|b|c|d|e|  Fn |j|  Fd |0|0|0|1|f|g|h|0|i|  Fm | CPDO&n;|c o n d|1 1 1 0|a|b|c|L|e|  Fn |   Rd  |0|0|0|1|f|g|h|1|i|  Fm | CPRT&n;|c o n d|1 1 1 0|a|b|c|1|e|  Fn |1|1|1|1|0|0|0|1|f|g|h|1|i|  Fm | comparisons&n;| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | &n;&n;CPDT&t;&t;data transfer instructions&n;&t;&t;LDF, STF, LFM, SFM&n;&t;&t;&n;CPDO&t;&t;dyadic arithmetic instructions&n;&t;&t;ADF, MUF, SUF, RSF, DVF, RDF,&n;&t;&t;POW, RPW, RMF, FML, FDV, FRD, POL&n;&n;CPDO&t;&t;monadic arithmetic instructions&n;&t;&t;MVF, MNF, ABS, RND, SQT, LOG, LGN, EXP,&n;&t;&t;SIN, COS, TAN, ASN, ACS, ATN, URD, NRM&n;&t;&t;&n;CPRT&t;&t;joint arithmetic/data transfer instructions&n;&t;&t;FIX (arithmetic followed by load/store)&n;&t;&t;FLT (load/store followed by arithmetic)&n;&t;&t;CMF, CNF CMFE, CNFE (comparisons)&n;&t;&t;WFS, RFS (write/read floating point status register)&n;&t;&t;WFC, RFC (write/read floating point control register)&n;&n;cond&t;&t;condition codes&n;P&t;&t;pre/post index bit: 0 = postindex, 1 = preindex&n;U&t;&t;up/down bit: 0 = stack grows down, 1 = stack grows up&n;W&t;&t;write back bit: 1 = update base register (Rn)&n;L&t;&t;load/store bit: 0 = store, 1 = load&n;Rn&t;&t;base register&n;Rd&t;&t;destination/source register&t;&t;&n;Fd&t;&t;floating point destination register&n;Fn&t;&t;floating point source register&n;Fm&t;&t;floating point source register or floating point constant&n;&n;uv&t;&t;transfer length (TABLE 1)&n;wx&t;&t;register count (TABLE 2)&n;abcd&t;&t;arithmetic opcode (TABLES 3 &amp; 4)&n;ef&t;&t;destination size (rounding precision) (TABLE 5)&n;gh&t;&t;rounding mode (TABLE 6)&n;j&t;&t;dyadic/monadic bit: 0 = dyadic, 1 = monadic&n;i &t;&t;constant bit: 1 = constant (TABLE 6)&n;*/
multiline_comment|/*&n;TABLE 1&n;+-------------------------+---+---+---------+---------+&n;|  Precision              | u | v | FPSR.EP | length  |&n;+-------------------------+---+---+---------+---------+&n;| Single                  | 0 &#xfffd; 0 |    x    | 1 words |&n;| Double                  | 1 &#xfffd; 1 |    x    | 2 words |&n;| Extended                | 1 &#xfffd; 1 |    x    | 3 words |&n;| Packed decimal          | 1 &#xfffd; 1 |    0    | 3 words |&n;| Expanded packed decimal | 1 &#xfffd; 1 |    1    | 4 words |&n;+-------------------------+---+---+---------+---------+&n;Note: x = don&squot;t care&n;*/
multiline_comment|/*&n;TABLE 2&n;+---+---+---------------------------------+&n;| w | x | Number of registers to transfer |&n;+---+---+---------------------------------+&n;| 0 &#xfffd; 1 |  1                              |&n;| 1 &#xfffd; 0 |  2                              |&n;| 1 &#xfffd; 1 |  3                              |&n;| 0 &#xfffd; 0 |  4                              |&n;+---+---+---------------------------------+&n;*/
multiline_comment|/*&n;TABLE 3: Dyadic Floating Point Opcodes&n;+---+---+---+---+----------+-----------------------+-----------------------+&n;| a | b | c | d | Mnemonic | Description           | Operation             |&n;+---+---+---+---+----------+-----------------------+-----------------------+&n;| 0 | 0 | 0 | 0 | ADF      | Add                   | Fd := Fn + Fm         |&n;| 0 | 0 | 0 | 1 | MUF      | Multiply              | Fd := Fn * Fm         |&n;| 0 | 0 | 1 | 0 | SUF      | Subtract              | Fd := Fn - Fm         |&n;| 0 | 0 | 1 | 1 | RSF      | Reverse subtract      | Fd := Fm - Fn         |&n;| 0 | 1 | 0 | 0 | DVF      | Divide                | Fd := Fn / Fm         |&n;| 0 | 1 | 0 | 1 | RDF      | Reverse divide        | Fd := Fm / Fn         |&n;| 0 | 1 | 1 | 0 | POW      | Power                 | Fd := Fn ^ Fm         |&n;| 0 | 1 | 1 | 1 | RPW      | Reverse power         | Fd := Fm ^ Fn         |&n;| 1 | 0 | 0 | 0 | RMF      | Remainder             | Fd := IEEE rem(Fn/Fm) |&n;| 1 | 0 | 0 | 1 | FML      | Fast Multiply         | Fd := Fn * Fm         |&n;| 1 | 0 | 1 | 0 | FDV      | Fast Divide           | Fd := Fn / Fm         |&n;| 1 | 0 | 1 | 1 | FRD      | Fast reverse divide   | Fd := Fm / Fn         |&n;| 1 | 1 | 0 | 0 | POL      | Polar angle (ArcTan2) | Fd := arctan2(Fn,Fm)  |&n;| 1 | 1 | 0 | 1 |          | undefined instruction | trap                  |&n;| 1 | 1 | 1 | 0 |          | undefined instruction | trap                  |&n;| 1 | 1 | 1 | 1 |          | undefined instruction | trap                  |&n;+---+---+---+---+----------+-----------------------+-----------------------+&n;Note: POW, RPW, POL are deprecated, and are available for backwards&n;      compatibility only.&n;*/
multiline_comment|/*&n;TABLE 4: Monadic Floating Point Opcodes&n;+---+---+---+---+----------+-----------------------+-----------------------+&n;| a | b | c | d | Mnemonic | Description           | Operation             |&n;+---+---+---+---+----------+-----------------------+-----------------------+&n;| 0 | 0 | 0 | 0 | MVF      | Move                  | Fd := Fm              |&n;| 0 | 0 | 0 | 1 | MNF      | Move negated          | Fd := - Fm            |&n;| 0 | 0 | 1 | 0 | ABS      | Absolute value        | Fd := abs(Fm)         |&n;| 0 | 0 | 1 | 1 | RND      | Round to integer      | Fd := int(Fm)         |&n;| 0 | 1 | 0 | 0 | SQT      | Square root           | Fd := sqrt(Fm)        |&n;| 0 | 1 | 0 | 1 | LOG      | Log base 10           | Fd := log10(Fm)       |&n;| 0 | 1 | 1 | 0 | LGN      | Log base e            | Fd := ln(Fm)          |&n;| 0 | 1 | 1 | 1 | EXP      | Exponent              | Fd := e ^ Fm          |&n;| 1 | 0 | 0 | 0 | SIN      | Sine                  | Fd := sin(Fm)         |&n;| 1 | 0 | 0 | 1 | COS      | Cosine                | Fd := cos(Fm)         |&n;| 1 | 0 | 1 | 0 | TAN      | Tangent               | Fd := tan(Fm)         |&n;| 1 | 0 | 1 | 1 | ASN      | Arc Sine              | Fd := arcsin(Fm)      |&n;| 1 | 1 | 0 | 0 | ACS      | Arc Cosine            | Fd := arccos(Fm)      |&n;| 1 | 1 | 0 | 1 | ATN      | Arc Tangent           | Fd := arctan(Fm)      |&n;| 1 | 1 | 1 | 0 | URD      | Unnormalized round    | Fd := int(Fm)         |&n;| 1 | 1 | 1 | 1 | NRM      | Normalize             | Fd := norm(Fm)        |&n;+---+---+---+---+----------+-----------------------+-----------------------+&n;Note: LOG, LGN, EXP, SIN, COS, TAN, ASN, ACS, ATN are deprecated, and are&n;      available for backwards compatibility only.&n;*/
multiline_comment|/*&n;TABLE 5&n;+-------------------------+---+---+&n;|  Rounding Precision     | e | f |&n;+-------------------------+---+---+&n;| IEEE Single precision   | 0 &#xfffd; 0 |&n;| IEEE Double precision   | 0 &#xfffd; 1 |&n;| IEEE Extended precision | 1 &#xfffd; 0 |&n;| undefined (trap)        | 1 &#xfffd; 1 |&n;+-------------------------+---+---+&n;*/
multiline_comment|/*&n;TABLE 5&n;+---------------------------------+---+---+&n;|  Rounding Mode                  | g | h |&n;+---------------------------------+---+---+&n;| Round to nearest (default)      | 0 &#xfffd; 0 |&n;| Round toward plus infinity      | 0 &#xfffd; 1 |&n;| Round toward negative infinity  | 1 &#xfffd; 0 |&n;| Round toward zero               | 1 &#xfffd; 1 |&n;+---------------------------------+---+---+&n;*/
multiline_comment|/*&n;===&n;=== Definitions for load and store instructions&n;===&n;*/
multiline_comment|/* bit masks */
DECL|macro|BIT_PREINDEX
mdefine_line|#define BIT_PREINDEX&t;0x01000000
DECL|macro|BIT_UP
mdefine_line|#define BIT_UP&t;&t;0x00800000
DECL|macro|BIT_WRITE_BACK
mdefine_line|#define BIT_WRITE_BACK&t;0x00200000
DECL|macro|BIT_LOAD
mdefine_line|#define BIT_LOAD&t;0x00100000
multiline_comment|/* masks for load/store */
DECL|macro|MASK_CPDT
mdefine_line|#define MASK_CPDT&t;&t;0x0c000000  /* data processing opcode */
DECL|macro|MASK_OFFSET
mdefine_line|#define MASK_OFFSET&t;&t;0x000000ff
DECL|macro|MASK_TRANSFER_LENGTH
mdefine_line|#define MASK_TRANSFER_LENGTH&t;0x00408000
DECL|macro|MASK_REGISTER_COUNT
mdefine_line|#define MASK_REGISTER_COUNT&t;MASK_TRANSFER_LENGTH
DECL|macro|MASK_COPROCESSOR
mdefine_line|#define MASK_COPROCESSOR&t;0x00000f00
multiline_comment|/* Tests for transfer length */
DECL|macro|TRANSFER_SINGLE
mdefine_line|#define TRANSFER_SINGLE&t;&t;0x00000000
DECL|macro|TRANSFER_DOUBLE
mdefine_line|#define TRANSFER_DOUBLE&t;&t;0x00008000
DECL|macro|TRANSFER_EXTENDED
mdefine_line|#define TRANSFER_EXTENDED&t;0x00400000
DECL|macro|TRANSFER_PACKED
mdefine_line|#define TRANSFER_PACKED&t;&t;MASK_TRANSFER_LENGTH
multiline_comment|/* Get the coprocessor number from the opcode. */
DECL|macro|getCoprocessorNumber
mdefine_line|#define getCoprocessorNumber(opcode)&t;((opcode &amp; MASK_COPROCESSOR) &gt;&gt; 8)
multiline_comment|/* Get the offset from the opcode. */
DECL|macro|getOffset
mdefine_line|#define getOffset(opcode)&t;&t;(opcode &amp; MASK_OFFSET)
multiline_comment|/* Tests for specific data transfer load/store opcodes. */
DECL|macro|TEST_OPCODE
mdefine_line|#define TEST_OPCODE(opcode,mask)&t;(((opcode) &amp; (mask)) == (mask))
DECL|macro|LOAD_OP
mdefine_line|#define LOAD_OP(opcode)   TEST_OPCODE((opcode),MASK_CPDT | BIT_LOAD)
DECL|macro|STORE_OP
mdefine_line|#define STORE_OP(opcode)  ((opcode &amp; (MASK_CPDT | BIT_LOAD)) == MASK_CPDT)
DECL|macro|LDF_OP
mdefine_line|#define LDF_OP(opcode)&t;(LOAD_OP(opcode) &amp;&amp; (getCoprocessorNumber(opcode) == 1))
DECL|macro|LFM_OP
mdefine_line|#define LFM_OP(opcode)&t;(LOAD_OP(opcode) &amp;&amp; (getCoprocessorNumber(opcode) == 2))
DECL|macro|STF_OP
mdefine_line|#define STF_OP(opcode)&t;(STORE_OP(opcode) &amp;&amp; (getCoprocessorNumber(opcode) == 1))
DECL|macro|SFM_OP
mdefine_line|#define SFM_OP(opcode)&t;(STORE_OP(opcode) &amp;&amp; (getCoprocessorNumber(opcode) == 2))
DECL|macro|PREINDEXED
mdefine_line|#define PREINDEXED(opcode)&t;&t;((opcode &amp; BIT_PREINDEX) != 0)
DECL|macro|POSTINDEXED
mdefine_line|#define POSTINDEXED(opcode)&t;&t;((opcode &amp; BIT_PREINDEX) == 0)
DECL|macro|BIT_UP_SET
mdefine_line|#define BIT_UP_SET(opcode)&t;&t;((opcode &amp; BIT_UP) != 0)
DECL|macro|BIT_UP_CLEAR
mdefine_line|#define BIT_UP_CLEAR(opcode)&t;&t;((opcode &amp; BIT_DOWN) == 0)
DECL|macro|WRITE_BACK
mdefine_line|#define WRITE_BACK(opcode)&t;&t;((opcode &amp; BIT_WRITE_BACK) != 0)
DECL|macro|LOAD
mdefine_line|#define LOAD(opcode)&t;&t;&t;((opcode &amp; BIT_LOAD) != 0)
DECL|macro|STORE
mdefine_line|#define STORE(opcode)&t;&t;&t;((opcode &amp; BIT_LOAD) == 0)
multiline_comment|/*&n;===&n;=== Definitions for arithmetic instructions&n;===&n;*/
multiline_comment|/* bit masks */
DECL|macro|BIT_MONADIC
mdefine_line|#define BIT_MONADIC&t;0x00008000
DECL|macro|BIT_CONSTANT
mdefine_line|#define BIT_CONSTANT&t;0x00000008
DECL|macro|CONSTANT_FM
mdefine_line|#define CONSTANT_FM(opcode)&t;&t;((opcode &amp; BIT_CONSTANT) != 0)
DECL|macro|MONADIC_INSTRUCTION
mdefine_line|#define MONADIC_INSTRUCTION(opcode)&t;((opcode &amp; BIT_MONADIC) != 0)
multiline_comment|/* instruction identification masks */
DECL|macro|MASK_CPDO
mdefine_line|#define MASK_CPDO&t;&t;0x0e000000  /* arithmetic opcode */
DECL|macro|MASK_ARITHMETIC_OPCODE
mdefine_line|#define MASK_ARITHMETIC_OPCODE&t;0x00f08000
DECL|macro|MASK_DESTINATION_SIZE
mdefine_line|#define MASK_DESTINATION_SIZE&t;0x00080080
multiline_comment|/* dyadic arithmetic opcodes. */
DECL|macro|ADF_CODE
mdefine_line|#define ADF_CODE&t;0x00000000
DECL|macro|MUF_CODE
mdefine_line|#define MUF_CODE&t;0x00100000
DECL|macro|SUF_CODE
mdefine_line|#define SUF_CODE&t;0x00200000
DECL|macro|RSF_CODE
mdefine_line|#define RSF_CODE&t;0x00300000
DECL|macro|DVF_CODE
mdefine_line|#define DVF_CODE&t;0x00400000
DECL|macro|RDF_CODE
mdefine_line|#define RDF_CODE&t;0x00500000
DECL|macro|POW_CODE
mdefine_line|#define POW_CODE&t;0x00600000
DECL|macro|RPW_CODE
mdefine_line|#define RPW_CODE&t;0x00700000
DECL|macro|RMF_CODE
mdefine_line|#define RMF_CODE&t;0x00800000
DECL|macro|FML_CODE
mdefine_line|#define FML_CODE&t;0x00900000
DECL|macro|FDV_CODE
mdefine_line|#define FDV_CODE&t;0x00a00000
DECL|macro|FRD_CODE
mdefine_line|#define FRD_CODE&t;0x00b00000
DECL|macro|POL_CODE
mdefine_line|#define POL_CODE&t;0x00c00000
multiline_comment|/* 0x00d00000 is an invalid dyadic arithmetic opcode */
multiline_comment|/* 0x00e00000 is an invalid dyadic arithmetic opcode */
multiline_comment|/* 0x00f00000 is an invalid dyadic arithmetic opcode */
multiline_comment|/* monadic arithmetic opcodes. */
DECL|macro|MVF_CODE
mdefine_line|#define MVF_CODE&t;0x00008000
DECL|macro|MNF_CODE
mdefine_line|#define MNF_CODE&t;0x00108000
DECL|macro|ABS_CODE
mdefine_line|#define ABS_CODE&t;0x00208000
DECL|macro|RND_CODE
mdefine_line|#define RND_CODE&t;0x00308000
DECL|macro|SQT_CODE
mdefine_line|#define SQT_CODE&t;0x00408000
DECL|macro|LOG_CODE
mdefine_line|#define LOG_CODE&t;0x00508000
DECL|macro|LGN_CODE
mdefine_line|#define LGN_CODE&t;0x00608000
DECL|macro|EXP_CODE
mdefine_line|#define EXP_CODE&t;0x00708000
DECL|macro|SIN_CODE
mdefine_line|#define SIN_CODE&t;0x00808000
DECL|macro|COS_CODE
mdefine_line|#define COS_CODE&t;0x00908000
DECL|macro|TAN_CODE
mdefine_line|#define TAN_CODE&t;0x00a08000
DECL|macro|ASN_CODE
mdefine_line|#define ASN_CODE&t;0x00b08000
DECL|macro|ACS_CODE
mdefine_line|#define ACS_CODE&t;0x00c08000
DECL|macro|ATN_CODE
mdefine_line|#define ATN_CODE&t;0x00d08000
DECL|macro|URD_CODE
mdefine_line|#define URD_CODE&t;0x00e08000
DECL|macro|NRM_CODE
mdefine_line|#define NRM_CODE&t;0x00f08000
multiline_comment|/*&n;===&n;=== Definitions for register transfer and comparison instructions&n;===&n;*/
DECL|macro|MASK_CPRT
mdefine_line|#define MASK_CPRT&t;&t;0x0e000010  /* register transfer opcode */
DECL|macro|MASK_CPRT_CODE
mdefine_line|#define MASK_CPRT_CODE&t;&t;0x00f00000
DECL|macro|FLT_CODE
mdefine_line|#define FLT_CODE&t;&t;0x00000000
DECL|macro|FIX_CODE
mdefine_line|#define FIX_CODE&t;&t;0x00100000
DECL|macro|WFS_CODE
mdefine_line|#define WFS_CODE&t;&t;0x00200000
DECL|macro|RFS_CODE
mdefine_line|#define RFS_CODE&t;&t;0x00300000
DECL|macro|WFC_CODE
mdefine_line|#define WFC_CODE&t;&t;0x00400000
DECL|macro|RFC_CODE
mdefine_line|#define RFC_CODE&t;&t;0x00500000
DECL|macro|CMF_CODE
mdefine_line|#define CMF_CODE&t;&t;0x00900000
DECL|macro|CNF_CODE
mdefine_line|#define CNF_CODE&t;&t;0x00b00000
DECL|macro|CMFE_CODE
mdefine_line|#define CMFE_CODE&t;&t;0x00d00000
DECL|macro|CNFE_CODE
mdefine_line|#define CNFE_CODE&t;&t;0x00f00000
multiline_comment|/*&n;===&n;=== Common definitions&n;===&n;*/
multiline_comment|/* register masks */
DECL|macro|MASK_Rd
mdefine_line|#define MASK_Rd&t;&t;0x0000f000
DECL|macro|MASK_Rn
mdefine_line|#define MASK_Rn&t;&t;0x000f0000
DECL|macro|MASK_Fd
mdefine_line|#define MASK_Fd&t;&t;0x00007000
DECL|macro|MASK_Fm
mdefine_line|#define MASK_Fm&t;&t;0x00000007
DECL|macro|MASK_Fn
mdefine_line|#define MASK_Fn&t;&t;0x00070000
multiline_comment|/* condition code masks */
DECL|macro|CC_MASK
mdefine_line|#define CC_MASK&t;&t;0xf0000000
DECL|macro|CC_NEGATIVE
mdefine_line|#define CC_NEGATIVE&t;0x80000000
DECL|macro|CC_ZERO
mdefine_line|#define CC_ZERO&t;&t;0x40000000
DECL|macro|CC_CARRY
mdefine_line|#define CC_CARRY&t;0x20000000
DECL|macro|CC_OVERFLOW
mdefine_line|#define CC_OVERFLOW&t;0x10000000
DECL|macro|CC_EQ
mdefine_line|#define CC_EQ&t;&t;0x00000000
DECL|macro|CC_NE
mdefine_line|#define CC_NE&t;&t;0x10000000
DECL|macro|CC_CS
mdefine_line|#define CC_CS&t;&t;0x20000000
DECL|macro|CC_HS
mdefine_line|#define CC_HS&t;&t;CC_CS
DECL|macro|CC_CC
mdefine_line|#define CC_CC&t;&t;0x30000000
DECL|macro|CC_LO
mdefine_line|#define CC_LO&t;&t;CC_CC
DECL|macro|CC_MI
mdefine_line|#define CC_MI&t;&t;0x40000000
DECL|macro|CC_PL
mdefine_line|#define CC_PL&t;&t;0x50000000
DECL|macro|CC_VS
mdefine_line|#define CC_VS&t;&t;0x60000000
DECL|macro|CC_VC
mdefine_line|#define CC_VC&t;&t;0x70000000
DECL|macro|CC_HI
mdefine_line|#define CC_HI&t;&t;0x80000000
DECL|macro|CC_LS
mdefine_line|#define CC_LS&t;&t;0x90000000
DECL|macro|CC_GE
mdefine_line|#define CC_GE&t;&t;0xa0000000
DECL|macro|CC_LT
mdefine_line|#define CC_LT&t;&t;0xb0000000
DECL|macro|CC_GT
mdefine_line|#define CC_GT&t;&t;0xc0000000
DECL|macro|CC_LE
mdefine_line|#define CC_LE&t;&t;0xd0000000
DECL|macro|CC_AL
mdefine_line|#define CC_AL&t;&t;0xe0000000
DECL|macro|CC_NV
mdefine_line|#define CC_NV&t;&t;0xf0000000
multiline_comment|/* rounding masks/values */
DECL|macro|MASK_ROUNDING_MODE
mdefine_line|#define MASK_ROUNDING_MODE&t;0x00000060
DECL|macro|ROUND_TO_NEAREST
mdefine_line|#define ROUND_TO_NEAREST&t;0x00000000
DECL|macro|ROUND_TO_PLUS_INFINITY
mdefine_line|#define ROUND_TO_PLUS_INFINITY&t;0x00000020
DECL|macro|ROUND_TO_MINUS_INFINITY
mdefine_line|#define ROUND_TO_MINUS_INFINITY&t;0x00000040
DECL|macro|ROUND_TO_ZERO
mdefine_line|#define ROUND_TO_ZERO&t;&t;0x00000060
DECL|macro|MASK_ROUNDING_PRECISION
mdefine_line|#define MASK_ROUNDING_PRECISION&t;0x00080080
DECL|macro|ROUND_SINGLE
mdefine_line|#define ROUND_SINGLE&t;&t;0x00000000
DECL|macro|ROUND_DOUBLE
mdefine_line|#define ROUND_DOUBLE&t;&t;0x00000080
DECL|macro|ROUND_EXTENDED
mdefine_line|#define ROUND_EXTENDED&t;&t;0x00080000
multiline_comment|/* Get the condition code from the opcode. */
DECL|macro|getCondition
mdefine_line|#define getCondition(opcode)&t;&t;(opcode &gt;&gt; 28)
multiline_comment|/* Get the source register from the opcode. */
DECL|macro|getRn
mdefine_line|#define getRn(opcode)&t;&t;&t;((opcode &amp; MASK_Rn) &gt;&gt; 16)
multiline_comment|/* Get the destination floating point register from the opcode. */
DECL|macro|getFd
mdefine_line|#define getFd(opcode)&t;&t;&t;((opcode &amp; MASK_Fd) &gt;&gt; 12)
multiline_comment|/* Get the first source floating point register from the opcode. */
DECL|macro|getFn
mdefine_line|#define getFn(opcode)&t;&t;((opcode &amp; MASK_Fn) &gt;&gt; 16)
multiline_comment|/* Get the second source floating point register from the opcode. */
DECL|macro|getFm
mdefine_line|#define getFm(opcode)&t;&t;(opcode &amp; MASK_Fm)
multiline_comment|/* Get the destination register from the opcode. */
DECL|macro|getRd
mdefine_line|#define getRd(opcode)&t;&t;((opcode &amp; MASK_Rd) &gt;&gt; 12)
multiline_comment|/* Get the rounding mode from the opcode. */
DECL|macro|getRoundingMode
mdefine_line|#define getRoundingMode(opcode)&t;&t;((opcode &amp; MASK_ROUNDING_MODE) &gt;&gt; 5)
id|float32
id|getSingleConstant
c_func
(paren
r_const
r_int
r_int
id|nIndex
)paren
suffix:semicolon
id|float64
id|getDoubleConstant
c_func
(paren
r_const
r_int
r_int
id|nIndex
)paren
suffix:semicolon
id|floatx80
id|getExtendedConstant
c_func
(paren
r_const
r_int
r_int
id|nIndex
)paren
suffix:semicolon
r_int
r_int
id|getRegisterCount
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
suffix:semicolon
r_int
r_int
id|getDestinationSize
c_func
(paren
r_const
r_int
r_int
id|opcode
)paren
suffix:semicolon
macro_line|#endif
eof
