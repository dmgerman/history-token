multiline_comment|/*&n; * BK Id: SCCS/s.ppc.h 1.5 05/17/01 18:14:23 cort&n; */
multiline_comment|/* ppc.h -- Header file for PowerPC opcode table&n;   Copyright 1994 Free Software Foundation, Inc.&n;   Written by Ian Lance Taylor, Cygnus Support&n;&n;This file is part of GDB, GAS, and the GNU binutils.&n;&n;GDB, GAS, and the GNU binutils are free software; you can redistribute&n;them and/or modify them under the terms of the GNU General Public&n;License as published by the Free Software Foundation; either version&n;1, or (at your option) any later version.&n;&n;GDB, GAS, and the GNU binutils are distributed in the hope that they&n;will be useful, but WITHOUT ANY WARRANTY; without even the implied&n;warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See&n;the GNU General Public License for more details.&n;&n;You should have received a copy of the GNU General Public License&n;along with this file; see the file COPYING.  If not, write to the Free&n;Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */
macro_line|#ifndef PPC_H
DECL|macro|PPC_H
mdefine_line|#define PPC_H
multiline_comment|/* The opcode table is an array of struct powerpc_opcode.  */
DECL|struct|powerpc_opcode
r_struct
id|powerpc_opcode
(brace
multiline_comment|/* The opcode name.  */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* The opcode itself.  Those bits which will be filled in with&n;     operands are zeroes.  */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:semicolon
multiline_comment|/* The opcode mask.  This is used by the disassembler.  This is a&n;     mask containing ones indicating those bits which must match the&n;     opcode field, and zeroes indicating those bits which need not&n;     match (and are presumably filled in by operands).  */
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
multiline_comment|/* One bit flags for the opcode.  These are used to indicate which&n;     specific processors support the instructions.  The defined values&n;     are listed below.  */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* An array of operand codes.  Each code is an index into the&n;     operand table.  They appear in the order which the operands must&n;     appear in assembly code, and are terminated by a zero.  */
DECL|member|operands
r_int
r_char
id|operands
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The table itself is sorted by major opcode number, and is otherwise&n;   in the order in which the disassembler should consider&n;   instructions.  */
r_extern
r_const
r_struct
id|powerpc_opcode
id|powerpc_opcodes
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|powerpc_num_opcodes
suffix:semicolon
multiline_comment|/* Values defined for the flags field of a struct powerpc_opcode.  */
multiline_comment|/* Opcode is defined for the PowerPC architecture.  */
DECL|macro|PPC_OPCODE_PPC
mdefine_line|#define PPC_OPCODE_PPC (01)
multiline_comment|/* Opcode is defined for the POWER (RS/6000) architecture.  */
DECL|macro|PPC_OPCODE_POWER
mdefine_line|#define PPC_OPCODE_POWER (02)
multiline_comment|/* Opcode is defined for the POWER2 (Rios 2) architecture.  */
DECL|macro|PPC_OPCODE_POWER2
mdefine_line|#define PPC_OPCODE_POWER2 (04)
multiline_comment|/* Opcode is only defined on 32 bit architectures.  */
DECL|macro|PPC_OPCODE_32
mdefine_line|#define PPC_OPCODE_32 (010)
multiline_comment|/* Opcode is only defined on 64 bit architectures.  */
DECL|macro|PPC_OPCODE_64
mdefine_line|#define PPC_OPCODE_64 (020)
multiline_comment|/* Opcode is supported by the Motorola PowerPC 601 processor.  The 601&n;   is assumed to support all PowerPC (PPC_OPCODE_PPC) instructions,&n;   but it also supports many additional POWER instructions.  */
DECL|macro|PPC_OPCODE_601
mdefine_line|#define PPC_OPCODE_601 (040)
multiline_comment|/* A macro to extract the major opcode from an instruction.  */
DECL|macro|PPC_OP
mdefine_line|#define PPC_OP(i) (((i) &gt;&gt; 26) &amp; 0x3f)
"&f;"
multiline_comment|/* The operands table is an array of struct powerpc_operand.  */
DECL|struct|powerpc_operand
r_struct
id|powerpc_operand
(brace
multiline_comment|/* The number of bits in the operand.  */
DECL|member|bits
r_int
id|bits
suffix:semicolon
multiline_comment|/* How far the operand is left shifted in the instruction.  */
DECL|member|shift
r_int
id|shift
suffix:semicolon
multiline_comment|/* Insertion function.  This is used by the assembler.  To insert an&n;     operand value into an instruction, check this field.&n;&n;     If it is NULL, execute&n;         i |= (op &amp; ((1 &lt;&lt; o-&gt;bits) - 1)) &lt;&lt; o-&gt;shift;&n;     (i is the instruction which we are filling in, o is a pointer to&n;     this structure, and op is the opcode value; this assumes twos&n;     complement arithmetic).&n;&n;     If this field is not NULL, then simply call it with the&n;     instruction and the operand value.  It will return the new value&n;     of the instruction.  If the ERRMSG argument is not NULL, then if&n;     the operand value is illegal, *ERRMSG will be set to a warning&n;     string (the operand will be inserted in any case).  If the&n;     operand value is legal, *ERRMSG will be unchanged (most operands&n;     can accept any value).  */
DECL|member|insert
r_int
r_int
(paren
op_star
id|insert
)paren
id|PARAMS
(paren
(paren
r_int
r_int
id|instruction
comma
r_int
id|op
comma
r_const
r_char
op_star
op_star
id|errmsg
)paren
)paren
suffix:semicolon
multiline_comment|/* Extraction function.  This is used by the disassembler.  To&n;     extract this operand type from an instruction, check this field.&n;&n;     If it is NULL, compute&n;         op = ((i) &gt;&gt; o-&gt;shift) &amp; ((1 &lt;&lt; o-&gt;bits) - 1);&n;&t; if ((o-&gt;flags &amp; PPC_OPERAND_SIGNED) != 0&n;&t;     &amp;&amp; (op &amp; (1 &lt;&lt; (o-&gt;bits - 1))) != 0)&n;&t;   op -= 1 &lt;&lt; o-&gt;bits;&n;     (i is the instruction, o is a pointer to this structure, and op&n;     is the result; this assumes twos complement arithmetic).&n;&n;     If this field is not NULL, then simply call it with the&n;     instruction value.  It will return the value of the operand.  If&n;     the INVALID argument is not NULL, *INVALID will be set to&n;     non-zero if this operand type can not actually be extracted from&n;     this operand (i.e., the instruction does not match).  If the&n;     operand is valid, *INVALID will not be changed.  */
DECL|member|extract
r_int
(paren
op_star
id|extract
)paren
id|PARAMS
(paren
(paren
r_int
r_int
id|instruction
comma
r_int
op_star
id|invalid
)paren
)paren
suffix:semicolon
multiline_comment|/* One bit syntax flags.  */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Elements in the table are retrieved by indexing with values from&n;   the operands field of the powerpc_opcodes table.  */
r_extern
r_const
r_struct
id|powerpc_operand
id|powerpc_operands
(braket
)braket
suffix:semicolon
multiline_comment|/* Values defined for the flags field of a struct powerpc_operand.  */
multiline_comment|/* This operand takes signed values.  */
DECL|macro|PPC_OPERAND_SIGNED
mdefine_line|#define PPC_OPERAND_SIGNED (01)
multiline_comment|/* This operand takes signed values, but also accepts a full positive&n;   range of values when running in 32 bit mode.  That is, if bits is&n;   16, it takes any value from -0x8000 to 0xffff.  In 64 bit mode,&n;   this flag is ignored.  */
DECL|macro|PPC_OPERAND_SIGNOPT
mdefine_line|#define PPC_OPERAND_SIGNOPT (02)
multiline_comment|/* This operand does not actually exist in the assembler input.  This&n;   is used to support extended mnemonics such as mr, for which two&n;   operands fields are identical.  The assembler should call the&n;   insert function with any op value.  The disassembler should call&n;   the extract function, ignore the return value, and check the value&n;   placed in the valid argument.  */
DECL|macro|PPC_OPERAND_FAKE
mdefine_line|#define PPC_OPERAND_FAKE (04)
multiline_comment|/* The next operand should be wrapped in parentheses rather than&n;   separated from this one by a comma.  This is used for the load and&n;   store instructions which want their operands to look like&n;       reg,displacement(reg)&n;   */
DECL|macro|PPC_OPERAND_PARENS
mdefine_line|#define PPC_OPERAND_PARENS (010)
multiline_comment|/* This operand may use the symbolic names for the CR fields, which&n;   are&n;       lt  0&t;gt  1&t;eq  2&t;so  3&t;un  3&n;       cr0 0&t;cr1 1&t;cr2 2&t;cr3 3&n;       cr4 4&t;cr5 5&t;cr6 6&t;cr7 7&n;   These may be combined arithmetically, as in cr2*4+gt.  These are&n;   only supported on the PowerPC, not the POWER.  */
DECL|macro|PPC_OPERAND_CR
mdefine_line|#define PPC_OPERAND_CR (020)
multiline_comment|/* This operand names a register.  The disassembler uses this to print&n;   register names with a leading &squot;r&squot;.  */
DECL|macro|PPC_OPERAND_GPR
mdefine_line|#define PPC_OPERAND_GPR (040)
multiline_comment|/* This operand names a floating point register.  The disassembler&n;   prints these with a leading &squot;f&squot;.  */
DECL|macro|PPC_OPERAND_FPR
mdefine_line|#define PPC_OPERAND_FPR (0100)
multiline_comment|/* This operand is a relative branch displacement.  The disassembler&n;   prints these symbolically if possible.  */
DECL|macro|PPC_OPERAND_RELATIVE
mdefine_line|#define PPC_OPERAND_RELATIVE (0200)
multiline_comment|/* This operand is an absolute branch address.  The disassembler&n;   prints these symbolically if possible.  */
DECL|macro|PPC_OPERAND_ABSOLUTE
mdefine_line|#define PPC_OPERAND_ABSOLUTE (0400)
multiline_comment|/* This operand is optional, and is zero if omitted.  This is used for&n;   the optional BF and L fields in the comparison instructions.  The&n;   assembler must count the number of operands remaining on the line,&n;   and the number of operands remaining for the opcode, and decide&n;   whether this operand is present or not.  The disassembler should&n;   print this operand out only if it is not zero.  */
DECL|macro|PPC_OPERAND_OPTIONAL
mdefine_line|#define PPC_OPERAND_OPTIONAL (01000)
multiline_comment|/* This flag is only used with PPC_OPERAND_OPTIONAL.  If this operand&n;   is omitted, then for the next operand use this operand value plus&n;   1, ignoring the next operand field for the opcode.  This wretched&n;   hack is needed because the Power rotate instructions can take&n;   either 4 or 5 operands.  The disassembler should print this operand&n;   out regardless of the PPC_OPERAND_OPTIONAL field.  */
DECL|macro|PPC_OPERAND_NEXT
mdefine_line|#define PPC_OPERAND_NEXT (02000)
multiline_comment|/* This operand should be regarded as a negative number for the&n;   purposes of overflow checking (i.e., the normal most negative&n;   number is disallowed and one more than the normal most positive&n;   number is allowed).  This flag will only be set for a signed&n;   operand.  */
DECL|macro|PPC_OPERAND_NEGATIVE
mdefine_line|#define PPC_OPERAND_NEGATIVE (04000)
"&f;"
multiline_comment|/* The POWER and PowerPC assemblers use a few macros.  We keep them&n;   with the operands table for simplicity.  The macro table is an&n;   array of struct powerpc_macro.  */
DECL|struct|powerpc_macro
r_struct
id|powerpc_macro
(brace
multiline_comment|/* The macro name.  */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* The number of operands the macro takes.  */
DECL|member|operands
r_int
r_int
id|operands
suffix:semicolon
multiline_comment|/* One bit flags for the opcode.  These are used to indicate which&n;     specific processors support the instructions.  The values are the&n;     same as those for the struct powerpc_opcode flags field.  */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* A format string to turn the macro into a normal instruction.&n;     Each %N in the string is replaced with operand number N (zero&n;     based).  */
DECL|member|format
r_const
r_char
op_star
id|format
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_const
r_struct
id|powerpc_macro
id|powerpc_macros
(braket
)braket
suffix:semicolon
r_extern
r_const
r_int
id|powerpc_num_macros
suffix:semicolon
macro_line|#endif /* PPC_H */
eof
