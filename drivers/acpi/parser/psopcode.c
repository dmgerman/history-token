multiline_comment|/******************************************************************************&n; *&n; * Module Name: psopcode - Parser opcode information table&n; *              $Revision: 24 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          PARSER
id|MODULE_NAME
(paren
l_string|&quot;psopcode&quot;
)paren
DECL|macro|_UNK
mdefine_line|#define _UNK                        0x6B
multiline_comment|/*&n; * Reserved ASCII characters.  Do not use any of these for&n; * internal opcodes, since they are used to differentiate&n; * name strings from AML opcodes&n; */
DECL|macro|_ASC
mdefine_line|#define _ASC                        0x6C
DECL|macro|_NAM
mdefine_line|#define _NAM                        0x6C
DECL|macro|_PFX
mdefine_line|#define _PFX                        0x6D
DECL|macro|_UNKNOWN_OPCODE
mdefine_line|#define _UNKNOWN_OPCODE             0x02    /* An example unknown opcode */
DECL|macro|MAX_EXTENDED_OPCODE
mdefine_line|#define MAX_EXTENDED_OPCODE         0x87
DECL|macro|NUM_EXTENDED_OPCODE
mdefine_line|#define NUM_EXTENDED_OPCODE         MAX_EXTENDED_OPCODE + 1
DECL|macro|MAX_INTERNAL_OPCODE
mdefine_line|#define MAX_INTERNAL_OPCODE
DECL|macro|NUM_INTERNAL_OPCODE
mdefine_line|#define NUM_INTERNAL_OPCODE         MAX_INTERNAL_OPCODE + 1
multiline_comment|/*******************************************************************************&n; *&n; * NAME:        Acpi_gbl_Aml_op_info&n; *&n; * DESCRIPTION: Opcode table. Each entry contains &lt;opcode, type, name, operands&gt;&n; *              The name is a simple ascii string, the operand specifier is an&n; *              ascii string with one letter per operand.  The letter specifies&n; *              the operand type.&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Flags byte: 0-4 (5 bits) = Opcode Type&n; *             5   (1 bit)  = Has arguments flag&n; *             6-7 (2 bits) = Reserved&n; */
DECL|macro|AML_NO_ARGS
mdefine_line|#define AML_NO_ARGS         0
DECL|macro|AML_HAS_ARGS
mdefine_line|#define AML_HAS_ARGS        ACPI_OP_ARGS_MASK
multiline_comment|/*&n; * All AML opcodes and the parse-time arguments for each.  Used by the AML parser  Each list is compressed&n; * into a 32-bit number and stored in the master opcode table at the end of this file.&n; */
DECL|macro|ARGP_ZERO_OP
mdefine_line|#define ARGP_ZERO_OP                    ARG_NONE
DECL|macro|ARGP_ONE_OP
mdefine_line|#define ARGP_ONE_OP                     ARG_NONE
DECL|macro|ARGP_ALIAS_OP
mdefine_line|#define ARGP_ALIAS_OP                   ARGP_LIST2 (ARGP_NAMESTRING, ARGP_NAME)
DECL|macro|ARGP_NAME_OP
mdefine_line|#define ARGP_NAME_OP                    ARGP_LIST2 (ARGP_NAME,       ARGP_DATAOBJ)
DECL|macro|ARGP_BYTE_OP
mdefine_line|#define ARGP_BYTE_OP                    ARGP_LIST1 (ARGP_BYTEDATA)
DECL|macro|ARGP_WORD_OP
mdefine_line|#define ARGP_WORD_OP                    ARGP_LIST1 (ARGP_WORDDATA)
DECL|macro|ARGP_DWORD_OP
mdefine_line|#define ARGP_DWORD_OP                   ARGP_LIST1 (ARGP_DWORDDATA)
DECL|macro|ARGP_STRING_OP
mdefine_line|#define ARGP_STRING_OP                  ARGP_LIST1 (ARGP_CHARLIST)
DECL|macro|ARGP_SCOPE_OP
mdefine_line|#define ARGP_SCOPE_OP                   ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_TERMLIST)
DECL|macro|ARGP_BUFFER_OP
mdefine_line|#define ARGP_BUFFER_OP                  ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG,       ARGP_BYTELIST)
DECL|macro|ARGP_PACKAGE_OP
mdefine_line|#define ARGP_PACKAGE_OP                 ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_BYTEDATA,      ARGP_DATAOBJLIST)
DECL|macro|ARGP_METHOD_OP
mdefine_line|#define ARGP_METHOD_OP                  ARGP_LIST4 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,      ARGP_TERMLIST)
DECL|macro|ARGP_LOCAL0
mdefine_line|#define ARGP_LOCAL0                     ARG_NONE
DECL|macro|ARGP_LOCAL1
mdefine_line|#define ARGP_LOCAL1                     ARG_NONE
DECL|macro|ARGP_LOCAL2
mdefine_line|#define ARGP_LOCAL2                     ARG_NONE
DECL|macro|ARGP_LOCAL3
mdefine_line|#define ARGP_LOCAL3                     ARG_NONE
DECL|macro|ARGP_LOCAL4
mdefine_line|#define ARGP_LOCAL4                     ARG_NONE
DECL|macro|ARGP_LOCAL5
mdefine_line|#define ARGP_LOCAL5                     ARG_NONE
DECL|macro|ARGP_LOCAL6
mdefine_line|#define ARGP_LOCAL6                     ARG_NONE
DECL|macro|ARGP_LOCAL7
mdefine_line|#define ARGP_LOCAL7                     ARG_NONE
DECL|macro|ARGP_ARG0
mdefine_line|#define ARGP_ARG0                       ARG_NONE
DECL|macro|ARGP_ARG1
mdefine_line|#define ARGP_ARG1                       ARG_NONE
DECL|macro|ARGP_ARG2
mdefine_line|#define ARGP_ARG2                       ARG_NONE
DECL|macro|ARGP_ARG3
mdefine_line|#define ARGP_ARG3                       ARG_NONE
DECL|macro|ARGP_ARG4
mdefine_line|#define ARGP_ARG4                       ARG_NONE
DECL|macro|ARGP_ARG5
mdefine_line|#define ARGP_ARG5                       ARG_NONE
DECL|macro|ARGP_ARG6
mdefine_line|#define ARGP_ARG6                       ARG_NONE
DECL|macro|ARGP_STORE_OP
mdefine_line|#define ARGP_STORE_OP                   ARGP_LIST2 (ARGP_TERMARG,    ARGP_SUPERNAME)
DECL|macro|ARGP_REF_OF_OP
mdefine_line|#define ARGP_REF_OF_OP                  ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_ADD_OP
mdefine_line|#define ARGP_ADD_OP                     ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_CONCAT_OP
mdefine_line|#define ARGP_CONCAT_OP                  ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_SUBTRACT_OP
mdefine_line|#define ARGP_SUBTRACT_OP                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_INCREMENT_OP
mdefine_line|#define ARGP_INCREMENT_OP               ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_DECREMENT_OP
mdefine_line|#define ARGP_DECREMENT_OP               ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_MULTIPLY_OP
mdefine_line|#define ARGP_MULTIPLY_OP                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_DIVIDE_OP
mdefine_line|#define ARGP_DIVIDE_OP                  ARGP_LIST4 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET,    ARGP_TARGET)
DECL|macro|ARGP_SHIFT_LEFT_OP
mdefine_line|#define ARGP_SHIFT_LEFT_OP              ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_SHIFT_RIGHT_OP
mdefine_line|#define ARGP_SHIFT_RIGHT_OP             ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_BIT_AND_OP
mdefine_line|#define ARGP_BIT_AND_OP                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_BIT_NAND_OP
mdefine_line|#define ARGP_BIT_NAND_OP                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_BIT_OR_OP
mdefine_line|#define ARGP_BIT_OR_OP                  ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_BIT_NOR_OP
mdefine_line|#define ARGP_BIT_NOR_OP                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_BIT_XOR_OP
mdefine_line|#define ARGP_BIT_XOR_OP                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_BIT_NOT_OP
mdefine_line|#define ARGP_BIT_NOT_OP                 ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
DECL|macro|ARGP_FIND_SET_LEFT_BIT_OP
mdefine_line|#define ARGP_FIND_SET_LEFT_BIT_OP       ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
DECL|macro|ARGP_FIND_SET_RIGHT_BIT_OP
mdefine_line|#define ARGP_FIND_SET_RIGHT_BIT_OP      ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
DECL|macro|ARGP_DEREF_OF_OP
mdefine_line|#define ARGP_DEREF_OF_OP                ARGP_LIST1 (ARGP_TERMARG)
DECL|macro|ARGP_NOTIFY_OP
mdefine_line|#define ARGP_NOTIFY_OP                  ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_TERMARG)
DECL|macro|ARGP_SIZE_OF_OP
mdefine_line|#define ARGP_SIZE_OF_OP                 ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_INDEX_OP
mdefine_line|#define ARGP_INDEX_OP                   ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
DECL|macro|ARGP_MATCH_OP
mdefine_line|#define ARGP_MATCH_OP                   ARGP_LIST6 (ARGP_TERMARG,    ARGP_BYTEDATA,      ARGP_TERMARG,   ARGP_BYTEDATA,  ARGP_TERMARG,   ARGP_TERMARG)
DECL|macro|ARGP_DWORD_FIELD_OP
mdefine_line|#define ARGP_DWORD_FIELD_OP             ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
DECL|macro|ARGP_WORD_FIELD_OP
mdefine_line|#define ARGP_WORD_FIELD_OP              ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
DECL|macro|ARGP_BYTE_FIELD_OP
mdefine_line|#define ARGP_BYTE_FIELD_OP              ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
DECL|macro|ARGP_BIT_FIELD_OP
mdefine_line|#define ARGP_BIT_FIELD_OP               ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
DECL|macro|ARGP_TYPE_OP
mdefine_line|#define ARGP_TYPE_OP                    ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_LAND_OP
mdefine_line|#define ARGP_LAND_OP                    ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_LOR_OP
mdefine_line|#define ARGP_LOR_OP                     ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_LNOT_OP
mdefine_line|#define ARGP_LNOT_OP                    ARGP_LIST1 (ARGP_TERMARG)
DECL|macro|ARGP_LEQUAL_OP
mdefine_line|#define ARGP_LEQUAL_OP                  ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_LGREATER_OP
mdefine_line|#define ARGP_LGREATER_OP                ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_LLESS_OP
mdefine_line|#define ARGP_LLESS_OP                   ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_IF_OP
mdefine_line|#define ARGP_IF_OP                      ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG, ARGP_TERMLIST)
DECL|macro|ARGP_ELSE_OP
mdefine_line|#define ARGP_ELSE_OP                    ARGP_LIST2 (ARGP_PKGLENGTH,  ARGP_TERMLIST)
DECL|macro|ARGP_WHILE_OP
mdefine_line|#define ARGP_WHILE_OP                   ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG, ARGP_TERMLIST)
DECL|macro|ARGP_NOOP_OP
mdefine_line|#define ARGP_NOOP_OP                    ARG_NONE
DECL|macro|ARGP_RETURN_OP
mdefine_line|#define ARGP_RETURN_OP                  ARGP_LIST1 (ARGP_TERMARG)
DECL|macro|ARGP_BREAK_OP
mdefine_line|#define ARGP_BREAK_OP                   ARG_NONE
DECL|macro|ARGP_BREAK_POINT_OP
mdefine_line|#define ARGP_BREAK_POINT_OP             ARG_NONE
DECL|macro|ARGP_ONES_OP
mdefine_line|#define ARGP_ONES_OP                    ARG_NONE
DECL|macro|ARGP_MUTEX_OP
mdefine_line|#define ARGP_MUTEX_OP                   ARGP_LIST2 (ARGP_NAME,       ARGP_BYTEDATA)
DECL|macro|ARGP_EVENT_OP
mdefine_line|#define ARGP_EVENT_OP                   ARGP_LIST1 (ARGP_NAME)
DECL|macro|ARGP_COND_REF_OF_OP
mdefine_line|#define ARGP_COND_REF_OF_OP             ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_SUPERNAME)
DECL|macro|ARGP_CREATE_FIELD_OP
mdefine_line|#define ARGP_CREATE_FIELD_OP            ARGP_LIST4 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TERMARG,   ARGP_NAME)
DECL|macro|ARGP_LOAD_OP
mdefine_line|#define ARGP_LOAD_OP                    ARGP_LIST2 (ARGP_NAMESTRING, ARGP_SUPERNAME)
DECL|macro|ARGP_STALL_OP
mdefine_line|#define ARGP_STALL_OP                   ARGP_LIST1 (ARGP_TERMARG)
DECL|macro|ARGP_SLEEP_OP
mdefine_line|#define ARGP_SLEEP_OP                   ARGP_LIST1 (ARGP_TERMARG)
DECL|macro|ARGP_ACQUIRE_OP
mdefine_line|#define ARGP_ACQUIRE_OP                 ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_WORDDATA)
DECL|macro|ARGP_SIGNAL_OP
mdefine_line|#define ARGP_SIGNAL_OP                  ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_WAIT_OP
mdefine_line|#define ARGP_WAIT_OP                    ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_TERMARG)
DECL|macro|ARGP_RESET_OP
mdefine_line|#define ARGP_RESET_OP                   ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_RELEASE_OP
mdefine_line|#define ARGP_RELEASE_OP                 ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_FROM_BCD_OP
mdefine_line|#define ARGP_FROM_BCD_OP                ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
DECL|macro|ARGP_TO_BCD_OP
mdefine_line|#define ARGP_TO_BCD_OP                  ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
DECL|macro|ARGP_UNLOAD_OP
mdefine_line|#define ARGP_UNLOAD_OP                  ARGP_LIST1 (ARGP_SUPERNAME)
DECL|macro|ARGP_REVISION_OP
mdefine_line|#define ARGP_REVISION_OP                ARG_NONE
DECL|macro|ARGP_DEBUG_OP
mdefine_line|#define ARGP_DEBUG_OP                   ARG_NONE
DECL|macro|ARGP_FATAL_OP
mdefine_line|#define ARGP_FATAL_OP                   ARGP_LIST3 (ARGP_BYTEDATA,   ARGP_DWORDDATA,     ARGP_TERMARG)
DECL|macro|ARGP_REGION_OP
mdefine_line|#define ARGP_REGION_OP                  ARGP_LIST4 (ARGP_NAME,       ARGP_BYTEDATA,      ARGP_TERMARG,   ARGP_TERMARG)
DECL|macro|ARGP_DEF_FIELD_OP
mdefine_line|#define ARGP_DEF_FIELD_OP               ARGP_LIST4 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_BYTEDATA,  ARGP_FIELDLIST)
DECL|macro|ARGP_DEVICE_OP
mdefine_line|#define ARGP_DEVICE_OP                  ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_OBJLIST)
DECL|macro|ARGP_PROCESSOR_OP
mdefine_line|#define ARGP_PROCESSOR_OP               ARGP_LIST6 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,  ARGP_DWORDDATA, ARGP_BYTEDATA,  ARGP_OBJLIST)
DECL|macro|ARGP_POWER_RES_OP
mdefine_line|#define ARGP_POWER_RES_OP               ARGP_LIST5 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,  ARGP_WORDDATA,  ARGP_OBJLIST)
DECL|macro|ARGP_THERMAL_ZONE_OP
mdefine_line|#define ARGP_THERMAL_ZONE_OP            ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_OBJLIST)
DECL|macro|ARGP_INDEX_FIELD_OP
mdefine_line|#define ARGP_INDEX_FIELD_OP             ARGP_LIST5 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_NAMESTRING,ARGP_BYTEDATA,  ARGP_FIELDLIST)
DECL|macro|ARGP_BANK_FIELD_OP
mdefine_line|#define ARGP_BANK_FIELD_OP              ARGP_LIST6 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_NAMESTRING,ARGP_TERMARG,   ARGP_BYTEDATA,  ARGP_FIELDLIST)
DECL|macro|ARGP_LNOTEQUAL_OP
mdefine_line|#define ARGP_LNOTEQUAL_OP               ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_LLESSEQUAL_OP
mdefine_line|#define ARGP_LLESSEQUAL_OP              ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_LGREATEREQUAL_OP
mdefine_line|#define ARGP_LGREATEREQUAL_OP           ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
DECL|macro|ARGP_NAMEPATH_OP
mdefine_line|#define ARGP_NAMEPATH_OP                ARGP_LIST1 (ARGP_NAMESTRING)
DECL|macro|ARGP_METHODCALL_OP
mdefine_line|#define ARGP_METHODCALL_OP              ARGP_LIST1 (ARGP_NAMESTRING)
DECL|macro|ARGP_BYTELIST_OP
mdefine_line|#define ARGP_BYTELIST_OP                ARGP_LIST1 (ARGP_NAMESTRING)
DECL|macro|ARGP_RESERVEDFIELD_OP
mdefine_line|#define ARGP_RESERVEDFIELD_OP           ARGP_LIST1 (ARGP_NAMESTRING)
DECL|macro|ARGP_NAMEDFIELD_OP
mdefine_line|#define ARGP_NAMEDFIELD_OP              ARGP_LIST1 (ARGP_NAMESTRING)
DECL|macro|ARGP_ACCESSFIELD_OP
mdefine_line|#define ARGP_ACCESSFIELD_OP             ARGP_LIST1 (ARGP_NAMESTRING)
DECL|macro|ARGP_STATICSTRING_OP
mdefine_line|#define ARGP_STATICSTRING_OP            ARGP_LIST1 (ARGP_NAMESTRING)
multiline_comment|/*&n; * All AML opcodes and the runtime arguments for each.  Used by the AML interpreter  Each list is compressed&n; * into a 32-bit number and stored in the master opcode table at the end of this file.&n; *&n; * (Used by Acpi_aml_prep_operands procedure)&n; */
DECL|macro|ARGI_ZERO_OP
mdefine_line|#define ARGI_ZERO_OP                    ARG_NONE
DECL|macro|ARGI_ONE_OP
mdefine_line|#define ARGI_ONE_OP                     ARG_NONE
DECL|macro|ARGI_ALIAS_OP
mdefine_line|#define ARGI_ALIAS_OP                   ARGI_INVALID_OPCODE
DECL|macro|ARGI_NAME_OP
mdefine_line|#define ARGI_NAME_OP                    ARGI_INVALID_OPCODE
DECL|macro|ARGI_BYTE_OP
mdefine_line|#define ARGI_BYTE_OP                    ARGI_INVALID_OPCODE
DECL|macro|ARGI_WORD_OP
mdefine_line|#define ARGI_WORD_OP                    ARGI_INVALID_OPCODE
DECL|macro|ARGI_DWORD_OP
mdefine_line|#define ARGI_DWORD_OP                   ARGI_INVALID_OPCODE
DECL|macro|ARGI_STRING_OP
mdefine_line|#define ARGI_STRING_OP                  ARGI_INVALID_OPCODE
DECL|macro|ARGI_SCOPE_OP
mdefine_line|#define ARGI_SCOPE_OP                   ARGI_INVALID_OPCODE
DECL|macro|ARGI_BUFFER_OP
mdefine_line|#define ARGI_BUFFER_OP                  ARGI_INVALID_OPCODE
DECL|macro|ARGI_PACKAGE_OP
mdefine_line|#define ARGI_PACKAGE_OP                 ARGI_INVALID_OPCODE
DECL|macro|ARGI_METHOD_OP
mdefine_line|#define ARGI_METHOD_OP                  ARGI_INVALID_OPCODE
DECL|macro|ARGI_LOCAL0
mdefine_line|#define ARGI_LOCAL0                     ARG_NONE
DECL|macro|ARGI_LOCAL1
mdefine_line|#define ARGI_LOCAL1                     ARG_NONE
DECL|macro|ARGI_LOCAL2
mdefine_line|#define ARGI_LOCAL2                     ARG_NONE
DECL|macro|ARGI_LOCAL3
mdefine_line|#define ARGI_LOCAL3                     ARG_NONE
DECL|macro|ARGI_LOCAL4
mdefine_line|#define ARGI_LOCAL4                     ARG_NONE
DECL|macro|ARGI_LOCAL5
mdefine_line|#define ARGI_LOCAL5                     ARG_NONE
DECL|macro|ARGI_LOCAL6
mdefine_line|#define ARGI_LOCAL6                     ARG_NONE
DECL|macro|ARGI_LOCAL7
mdefine_line|#define ARGI_LOCAL7                     ARG_NONE
DECL|macro|ARGI_ARG0
mdefine_line|#define ARGI_ARG0                       ARG_NONE
DECL|macro|ARGI_ARG1
mdefine_line|#define ARGI_ARG1                       ARG_NONE
DECL|macro|ARGI_ARG2
mdefine_line|#define ARGI_ARG2                       ARG_NONE
DECL|macro|ARGI_ARG3
mdefine_line|#define ARGI_ARG3                       ARG_NONE
DECL|macro|ARGI_ARG4
mdefine_line|#define ARGI_ARG4                       ARG_NONE
DECL|macro|ARGI_ARG5
mdefine_line|#define ARGI_ARG5                       ARG_NONE
DECL|macro|ARGI_ARG6
mdefine_line|#define ARGI_ARG6                       ARG_NONE
DECL|macro|ARGI_STORE_OP
mdefine_line|#define ARGI_STORE_OP                   ARGI_LIST2 (ARGI_ANYTYPE,    ARGI_TARGETREF)
DECL|macro|ARGI_REF_OF_OP
mdefine_line|#define ARGI_REF_OF_OP                  ARGI_LIST1 (ARGI_REFERENCE)
DECL|macro|ARGI_ADD_OP
mdefine_line|#define ARGI_ADD_OP                     ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_CONCAT_OP
mdefine_line|#define ARGI_CONCAT_OP                  ARGI_LIST3 (ARGI_STRING,     ARGI_STRING,        ARGI_TARGETREF)
DECL|macro|ARGI_SUBTRACT_OP
mdefine_line|#define ARGI_SUBTRACT_OP                ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_INCREMENT_OP
mdefine_line|#define ARGI_INCREMENT_OP               ARGI_LIST1 (ARGI_REFERENCE)
DECL|macro|ARGI_DECREMENT_OP
mdefine_line|#define ARGI_DECREMENT_OP               ARGI_LIST1 (ARGI_REFERENCE)
DECL|macro|ARGI_MULTIPLY_OP
mdefine_line|#define ARGI_MULTIPLY_OP                ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_DIVIDE_OP
mdefine_line|#define ARGI_DIVIDE_OP                  ARGI_LIST4 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF,    ARGI_TARGETREF)
DECL|macro|ARGI_SHIFT_LEFT_OP
mdefine_line|#define ARGI_SHIFT_LEFT_OP              ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_SHIFT_RIGHT_OP
mdefine_line|#define ARGI_SHIFT_RIGHT_OP             ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_BIT_AND_OP
mdefine_line|#define ARGI_BIT_AND_OP                 ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_BIT_NAND_OP
mdefine_line|#define ARGI_BIT_NAND_OP                ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_BIT_OR_OP
mdefine_line|#define ARGI_BIT_OR_OP                  ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_BIT_NOR_OP
mdefine_line|#define ARGI_BIT_NOR_OP                 ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_BIT_XOR_OP
mdefine_line|#define ARGI_BIT_XOR_OP                 ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_BIT_NOT_OP
mdefine_line|#define ARGI_BIT_NOT_OP                 ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
DECL|macro|ARGI_FIND_SET_LEFT_BIT_OP
mdefine_line|#define ARGI_FIND_SET_LEFT_BIT_OP       ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
DECL|macro|ARGI_FIND_SET_RIGHT_BIT_OP
mdefine_line|#define ARGI_FIND_SET_RIGHT_BIT_OP      ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
DECL|macro|ARGI_DEREF_OF_OP
mdefine_line|#define ARGI_DEREF_OF_OP                ARGI_LIST1 (ARGI_REFERENCE)
DECL|macro|ARGI_NOTIFY_OP
mdefine_line|#define ARGI_NOTIFY_OP                  ARGI_LIST2 (ARGI_REFERENCE,  ARGI_NUMBER)
DECL|macro|ARGI_SIZE_OF_OP
mdefine_line|#define ARGI_SIZE_OF_OP                 ARGI_LIST1 (ARGI_DATAOBJECT)
DECL|macro|ARGI_INDEX_OP
mdefine_line|#define ARGI_INDEX_OP                   ARGI_LIST3 (ARGI_COMPLEXOBJ, ARGI_NUMBER,        ARGI_TARGETREF)
DECL|macro|ARGI_MATCH_OP
mdefine_line|#define ARGI_MATCH_OP                   ARGI_LIST6 (ARGI_PACKAGE,    ARGI_NUMBER,        ARGI_NUMBER,       ARGI_NUMBER,    ARGI_NUMBER,    ARGI_NUMBER)
DECL|macro|ARGI_DWORD_FIELD_OP
mdefine_line|#define ARGI_DWORD_FIELD_OP             ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_REFERENCE)
DECL|macro|ARGI_WORD_FIELD_OP
mdefine_line|#define ARGI_WORD_FIELD_OP              ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_REFERENCE)
DECL|macro|ARGI_BYTE_FIELD_OP
mdefine_line|#define ARGI_BYTE_FIELD_OP              ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_REFERENCE)
DECL|macro|ARGI_BIT_FIELD_OP
mdefine_line|#define ARGI_BIT_FIELD_OP               ARGI_LIST3 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_REFERENCE)
DECL|macro|ARGI_TYPE_OP
mdefine_line|#define ARGI_TYPE_OP                    ARGI_LIST1 (ARGI_ANYTYPE)
DECL|macro|ARGI_LAND_OP
mdefine_line|#define ARGI_LAND_OP                    ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
DECL|macro|ARGI_LOR_OP
mdefine_line|#define ARGI_LOR_OP                     ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
DECL|macro|ARGI_LNOT_OP
mdefine_line|#define ARGI_LNOT_OP                    ARGI_LIST1 (ARGI_NUMBER)
DECL|macro|ARGI_LEQUAL_OP
mdefine_line|#define ARGI_LEQUAL_OP                  ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
DECL|macro|ARGI_LGREATER_OP
mdefine_line|#define ARGI_LGREATER_OP                ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
DECL|macro|ARGI_LLESS_OP
mdefine_line|#define ARGI_LLESS_OP                   ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
DECL|macro|ARGI_IF_OP
mdefine_line|#define ARGI_IF_OP                      ARGI_INVALID_OPCODE
DECL|macro|ARGI_ELSE_OP
mdefine_line|#define ARGI_ELSE_OP                    ARGI_INVALID_OPCODE
DECL|macro|ARGI_WHILE_OP
mdefine_line|#define ARGI_WHILE_OP                   ARGI_INVALID_OPCODE
DECL|macro|ARGI_NOOP_OP
mdefine_line|#define ARGI_NOOP_OP                    ARG_NONE
DECL|macro|ARGI_RETURN_OP
mdefine_line|#define ARGI_RETURN_OP                  ARGI_INVALID_OPCODE
DECL|macro|ARGI_BREAK_OP
mdefine_line|#define ARGI_BREAK_OP                   ARG_NONE
DECL|macro|ARGI_BREAK_POINT_OP
mdefine_line|#define ARGI_BREAK_POINT_OP             ARG_NONE
DECL|macro|ARGI_ONES_OP
mdefine_line|#define ARGI_ONES_OP                    ARG_NONE
DECL|macro|ARGI_MUTEX_OP
mdefine_line|#define ARGI_MUTEX_OP                   ARGI_INVALID_OPCODE
DECL|macro|ARGI_EVENT_OP
mdefine_line|#define ARGI_EVENT_OP                   ARGI_INVALID_OPCODE
DECL|macro|ARGI_COND_REF_OF_OP
mdefine_line|#define ARGI_COND_REF_OF_OP             ARGI_LIST2 (ARGI_REFERENCE,  ARGI_TARGETREF)
DECL|macro|ARGI_CREATE_FIELD_OP
mdefine_line|#define ARGI_CREATE_FIELD_OP            ARGI_LIST4 (ARGI_BUFFER,     ARGI_NUMBER,        ARGI_NUMBER,       ARGI_REFERENCE)
DECL|macro|ARGI_LOAD_OP
mdefine_line|#define ARGI_LOAD_OP                    ARGI_LIST2 (ARGI_REGION,     ARGI_TARGETREF)
DECL|macro|ARGI_STALL_OP
mdefine_line|#define ARGI_STALL_OP                   ARGI_LIST1 (ARGI_NUMBER)
DECL|macro|ARGI_SLEEP_OP
mdefine_line|#define ARGI_SLEEP_OP                   ARGI_LIST1 (ARGI_NUMBER)
DECL|macro|ARGI_ACQUIRE_OP
mdefine_line|#define ARGI_ACQUIRE_OP                 ARGI_LIST2 (ARGI_MUTEX,      ARGI_NUMBER)
DECL|macro|ARGI_SIGNAL_OP
mdefine_line|#define ARGI_SIGNAL_OP                  ARGI_LIST1 (ARGI_EVENT)
DECL|macro|ARGI_WAIT_OP
mdefine_line|#define ARGI_WAIT_OP                    ARGI_LIST2 (ARGI_EVENT,      ARGI_NUMBER)
DECL|macro|ARGI_RESET_OP
mdefine_line|#define ARGI_RESET_OP                   ARGI_LIST1 (ARGI_EVENT)
DECL|macro|ARGI_RELEASE_OP
mdefine_line|#define ARGI_RELEASE_OP                 ARGI_LIST1 (ARGI_MUTEX)
DECL|macro|ARGI_FROM_BCD_OP
mdefine_line|#define ARGI_FROM_BCD_OP                ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
DECL|macro|ARGI_TO_BCD_OP
mdefine_line|#define ARGI_TO_BCD_OP                  ARGI_LIST2 (ARGI_NUMBER,     ARGI_TARGETREF)
DECL|macro|ARGI_UNLOAD_OP
mdefine_line|#define ARGI_UNLOAD_OP                  ARGI_LIST1 (ARGI_DDBHANDLE)
DECL|macro|ARGI_REVISION_OP
mdefine_line|#define ARGI_REVISION_OP                ARG_NONE
DECL|macro|ARGI_DEBUG_OP
mdefine_line|#define ARGI_DEBUG_OP                   ARG_NONE
DECL|macro|ARGI_FATAL_OP
mdefine_line|#define ARGI_FATAL_OP                   ARGI_LIST3 (ARGI_NUMBER,     ARGI_NUMBER,        ARGI_NUMBER)
DECL|macro|ARGI_REGION_OP
mdefine_line|#define ARGI_REGION_OP                  ARGI_LIST2 (ARGI_NUMBER,     ARGI_NUMBER)
DECL|macro|ARGI_DEF_FIELD_OP
mdefine_line|#define ARGI_DEF_FIELD_OP               ARGI_INVALID_OPCODE
DECL|macro|ARGI_DEVICE_OP
mdefine_line|#define ARGI_DEVICE_OP                  ARGI_INVALID_OPCODE
DECL|macro|ARGI_PROCESSOR_OP
mdefine_line|#define ARGI_PROCESSOR_OP               ARGI_INVALID_OPCODE
DECL|macro|ARGI_POWER_RES_OP
mdefine_line|#define ARGI_POWER_RES_OP               ARGI_INVALID_OPCODE
DECL|macro|ARGI_THERMAL_ZONE_OP
mdefine_line|#define ARGI_THERMAL_ZONE_OP            ARGI_INVALID_OPCODE
DECL|macro|ARGI_INDEX_FIELD_OP
mdefine_line|#define ARGI_INDEX_FIELD_OP             ARGI_INVALID_OPCODE
DECL|macro|ARGI_BANK_FIELD_OP
mdefine_line|#define ARGI_BANK_FIELD_OP              ARGI_INVALID_OPCODE
DECL|macro|ARGI_LNOTEQUAL_OP
mdefine_line|#define ARGI_LNOTEQUAL_OP               ARGI_INVALID_OPCODE
DECL|macro|ARGI_LLESSEQUAL_OP
mdefine_line|#define ARGI_LLESSEQUAL_OP              ARGI_INVALID_OPCODE
DECL|macro|ARGI_LGREATEREQUAL_OP
mdefine_line|#define ARGI_LGREATEREQUAL_OP           ARGI_INVALID_OPCODE
DECL|macro|ARGI_NAMEPATH_OP
mdefine_line|#define ARGI_NAMEPATH_OP                ARGI_INVALID_OPCODE
DECL|macro|ARGI_METHODCALL_OP
mdefine_line|#define ARGI_METHODCALL_OP              ARGI_INVALID_OPCODE
DECL|macro|ARGI_BYTELIST_OP
mdefine_line|#define ARGI_BYTELIST_OP                ARGI_INVALID_OPCODE
DECL|macro|ARGI_RESERVEDFIELD_OP
mdefine_line|#define ARGI_RESERVEDFIELD_OP           ARGI_INVALID_OPCODE
DECL|macro|ARGI_NAMEDFIELD_OP
mdefine_line|#define ARGI_NAMEDFIELD_OP              ARGI_INVALID_OPCODE
DECL|macro|ARGI_ACCESSFIELD_OP
mdefine_line|#define ARGI_ACCESSFIELD_OP             ARGI_INVALID_OPCODE
DECL|macro|ARGI_STATICSTRING_OP
mdefine_line|#define ARGI_STATICSTRING_OP            ARGI_INVALID_OPCODE
multiline_comment|/*&n; * Master Opcode information table.  A summary of everything we know about each opcode, all in one place.&n; */
DECL|variable|aml_op_info
r_static
id|ACPI_OPCODE_INFO
id|aml_op_info
(braket
)braket
op_assign
(brace
multiline_comment|/* Index          Opcode                                   Type                   Class                 Has Arguments?   Name                 Parser Args             Interpreter Args */
multiline_comment|/*  00 */
multiline_comment|/* AML_ZERO_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONSTANT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Zero_op&quot;
comma
id|ARGP_ZERO_OP
comma
id|ARGI_ZERO_OP
)paren
comma
multiline_comment|/*  01 */
multiline_comment|/* AML_ONE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONSTANT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;One_op&quot;
comma
id|ARGP_ONE_OP
comma
id|ARGI_ONE_OP
)paren
comma
multiline_comment|/*  02 */
multiline_comment|/* AML_ALIAS_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Alias&quot;
comma
id|ARGP_ALIAS_OP
comma
id|ARGI_ALIAS_OP
)paren
comma
multiline_comment|/*  03 */
multiline_comment|/* AML_NAME_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Name&quot;
comma
id|ARGP_NAME_OP
comma
id|ARGI_NAME_OP
)paren
comma
multiline_comment|/*  04 */
multiline_comment|/* AML_BYTE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LITERAL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Byte_const&quot;
comma
id|ARGP_BYTE_OP
comma
id|ARGI_BYTE_OP
)paren
comma
multiline_comment|/*  05 */
multiline_comment|/* AML_WORD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LITERAL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Word_const&quot;
comma
id|ARGP_WORD_OP
comma
id|ARGI_WORD_OP
)paren
comma
multiline_comment|/*  06 */
multiline_comment|/* AML_DWORD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LITERAL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Dword_const&quot;
comma
id|ARGP_DWORD_OP
comma
id|ARGI_DWORD_OP
)paren
comma
multiline_comment|/*  07 */
multiline_comment|/* AML_STRING_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LITERAL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;String&quot;
comma
id|ARGP_STRING_OP
comma
id|ARGI_STRING_OP
)paren
comma
multiline_comment|/*  08 */
multiline_comment|/* AML_SCOPE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Scope&quot;
comma
id|ARGP_SCOPE_OP
comma
id|ARGI_SCOPE_OP
)paren
comma
multiline_comment|/*  09 */
multiline_comment|/* AML_BUFFER_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DATA_TERM
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Buffer&quot;
comma
id|ARGP_BUFFER_OP
comma
id|ARGI_BUFFER_OP
)paren
comma
multiline_comment|/*  0A */
multiline_comment|/* AML_PACKAGE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DATA_TERM
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Package&quot;
comma
id|ARGP_PACKAGE_OP
comma
id|ARGI_PACKAGE_OP
)paren
comma
multiline_comment|/*  0B */
multiline_comment|/* AML_METHOD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Method&quot;
comma
id|ARGP_METHOD_OP
comma
id|ARGI_METHOD_OP
)paren
comma
multiline_comment|/*  0C */
multiline_comment|/* AML_LOCAL0 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local0&quot;
comma
id|ARGP_LOCAL0
comma
id|ARGI_LOCAL0
)paren
comma
multiline_comment|/*  0D */
multiline_comment|/* AML_LOCAL1 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local1&quot;
comma
id|ARGP_LOCAL1
comma
id|ARGI_LOCAL1
)paren
comma
multiline_comment|/*  0E */
multiline_comment|/* AML_LOCAL2 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local2&quot;
comma
id|ARGP_LOCAL2
comma
id|ARGI_LOCAL2
)paren
comma
multiline_comment|/*  0F */
multiline_comment|/* AML_LOCAL3 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local3&quot;
comma
id|ARGP_LOCAL3
comma
id|ARGI_LOCAL3
)paren
comma
multiline_comment|/*  10 */
multiline_comment|/* AML_LOCAL4 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local4&quot;
comma
id|ARGP_LOCAL4
comma
id|ARGI_LOCAL4
)paren
comma
multiline_comment|/*  11 */
multiline_comment|/* AML_LOCAL5 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local5&quot;
comma
id|ARGP_LOCAL5
comma
id|ARGI_LOCAL5
)paren
comma
multiline_comment|/*  12 */
multiline_comment|/* AML_LOCAL6 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local6&quot;
comma
id|ARGP_LOCAL6
comma
id|ARGI_LOCAL6
)paren
comma
multiline_comment|/*  13 */
multiline_comment|/* AML_LOCAL7 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LOCAL_VARIABLE
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Local7&quot;
comma
id|ARGP_LOCAL7
comma
id|ARGI_LOCAL7
)paren
comma
multiline_comment|/*  14 */
multiline_comment|/* AML_ARG0 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_ARGUMENT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Arg0&quot;
comma
id|ARGP_ARG0
comma
id|ARGI_ARG0
)paren
comma
multiline_comment|/*  15 */
multiline_comment|/* AML_ARG1 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_ARGUMENT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Arg1&quot;
comma
id|ARGP_ARG1
comma
id|ARGI_ARG1
)paren
comma
multiline_comment|/*  16 */
multiline_comment|/* AML_ARG2 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_ARGUMENT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Arg2&quot;
comma
id|ARGP_ARG2
comma
id|ARGI_ARG2
)paren
comma
multiline_comment|/*  17 */
multiline_comment|/* AML_ARG3 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_ARGUMENT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Arg3&quot;
comma
id|ARGP_ARG3
comma
id|ARGI_ARG3
)paren
comma
multiline_comment|/*  18 */
multiline_comment|/* AML_ARG4 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_ARGUMENT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Arg4&quot;
comma
id|ARGP_ARG4
comma
id|ARGI_ARG4
)paren
comma
multiline_comment|/*  19 */
multiline_comment|/* AML_ARG5 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_ARGUMENT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Arg5&quot;
comma
id|ARGP_ARG5
comma
id|ARGI_ARG5
)paren
comma
multiline_comment|/*  1_a */
multiline_comment|/* AML_ARG6 */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_ARGUMENT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Arg6&quot;
comma
id|ARGP_ARG6
comma
id|ARGI_ARG6
)paren
comma
multiline_comment|/*  1_b */
multiline_comment|/* AML_STORE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Store&quot;
comma
id|ARGP_STORE_OP
comma
id|ARGI_STORE_OP
)paren
comma
multiline_comment|/*  1_c */
multiline_comment|/* AML_REF_OF_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Ref_of&quot;
comma
id|ARGP_REF_OF_OP
comma
id|ARGI_REF_OF_OP
)paren
comma
multiline_comment|/*  1_d */
multiline_comment|/* AML_ADD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Add&quot;
comma
id|ARGP_ADD_OP
comma
id|ARGI_ADD_OP
)paren
comma
multiline_comment|/*  1_e */
multiline_comment|/* AML_CONCAT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Concat&quot;
comma
id|ARGP_CONCAT_OP
comma
id|ARGI_CONCAT_OP
)paren
comma
multiline_comment|/*  1_f */
multiline_comment|/* AML_SUBTRACT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Subtract&quot;
comma
id|ARGP_SUBTRACT_OP
comma
id|ARGI_SUBTRACT_OP
)paren
comma
multiline_comment|/*  20 */
multiline_comment|/* AML_INCREMENT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Increment&quot;
comma
id|ARGP_INCREMENT_OP
comma
id|ARGI_INCREMENT_OP
)paren
comma
multiline_comment|/*  21 */
multiline_comment|/* AML_DECREMENT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Decrement&quot;
comma
id|ARGP_DECREMENT_OP
comma
id|ARGI_DECREMENT_OP
)paren
comma
multiline_comment|/*  22 */
multiline_comment|/* AML_MULTIPLY_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Multiply&quot;
comma
id|ARGP_MULTIPLY_OP
comma
id|ARGI_MULTIPLY_OP
)paren
comma
multiline_comment|/*  23 */
multiline_comment|/* AML_DIVIDE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Divide&quot;
comma
id|ARGP_DIVIDE_OP
comma
id|ARGI_DIVIDE_OP
)paren
comma
multiline_comment|/*  24 */
multiline_comment|/* AML_SHIFT_LEFT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Shift_left&quot;
comma
id|ARGP_SHIFT_LEFT_OP
comma
id|ARGI_SHIFT_LEFT_OP
)paren
comma
multiline_comment|/*  25 */
multiline_comment|/* AML_SHIFT_RIGHT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Shift_right&quot;
comma
id|ARGP_SHIFT_RIGHT_OP
comma
id|ARGI_SHIFT_RIGHT_OP
)paren
comma
multiline_comment|/*  26 */
multiline_comment|/* AML_BIT_AND_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;And&quot;
comma
id|ARGP_BIT_AND_OP
comma
id|ARGI_BIT_AND_OP
)paren
comma
multiline_comment|/*  27 */
multiline_comment|/* AML_BIT_NAND_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;NAnd&quot;
comma
id|ARGP_BIT_NAND_OP
comma
id|ARGI_BIT_NAND_OP
)paren
comma
multiline_comment|/*  28 */
multiline_comment|/* AML_BIT_OR_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Or&quot;
comma
id|ARGP_BIT_OR_OP
comma
id|ARGI_BIT_OR_OP
)paren
comma
multiline_comment|/*  29 */
multiline_comment|/* AML_BIT_NOR_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;NOr&quot;
comma
id|ARGP_BIT_NOR_OP
comma
id|ARGI_BIT_NOR_OP
)paren
comma
multiline_comment|/*  2_a */
multiline_comment|/* AML_BIT_XOR_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;XOr&quot;
comma
id|ARGP_BIT_XOR_OP
comma
id|ARGI_BIT_XOR_OP
)paren
comma
multiline_comment|/*  2_b */
multiline_comment|/* AML_BIT_NOT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Not&quot;
comma
id|ARGP_BIT_NOT_OP
comma
id|ARGI_BIT_NOT_OP
)paren
comma
multiline_comment|/*  2_c */
multiline_comment|/* AML_FIND_SET_LEFT_BIT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Find_set_left_bit&quot;
comma
id|ARGP_FIND_SET_LEFT_BIT_OP
comma
id|ARGI_FIND_SET_LEFT_BIT_OP
)paren
comma
multiline_comment|/*  2_d */
multiline_comment|/* AML_FIND_SET_RIGHT_BIT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Find_set_right_bit&quot;
comma
id|ARGP_FIND_SET_RIGHT_BIT_OP
comma
id|ARGI_FIND_SET_RIGHT_BIT_OP
)paren
comma
multiline_comment|/*  2_e */
multiline_comment|/* AML_DEREF_OF_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Deref_of&quot;
comma
id|ARGP_DEREF_OF_OP
comma
id|ARGI_DEREF_OF_OP
)paren
comma
multiline_comment|/*  2_f */
multiline_comment|/* AML_NOTIFY_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC1
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Notify&quot;
comma
id|ARGP_NOTIFY_OP
comma
id|ARGI_NOTIFY_OP
)paren
comma
multiline_comment|/*  30 */
multiline_comment|/* AML_SIZE_OF_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Size_of&quot;
comma
id|ARGP_SIZE_OF_OP
comma
id|ARGI_SIZE_OF_OP
)paren
comma
multiline_comment|/*  31 */
multiline_comment|/* AML_INDEX_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_INDEX
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Index&quot;
comma
id|ARGP_INDEX_OP
comma
id|ARGI_INDEX_OP
)paren
comma
multiline_comment|/*  32 */
multiline_comment|/* AML_MATCH_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MATCH
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Match&quot;
comma
id|ARGP_MATCH_OP
comma
id|ARGI_MATCH_OP
)paren
comma
multiline_comment|/*  33 */
multiline_comment|/* AML_DWORD_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CREATE_FIELD
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Create_dWord_field&quot;
comma
id|ARGP_DWORD_FIELD_OP
comma
id|ARGI_DWORD_FIELD_OP
)paren
comma
multiline_comment|/*  34 */
multiline_comment|/* AML_WORD_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CREATE_FIELD
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Create_word_field&quot;
comma
id|ARGP_WORD_FIELD_OP
comma
id|ARGI_WORD_FIELD_OP
)paren
comma
multiline_comment|/*  35 */
multiline_comment|/* AML_BYTE_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CREATE_FIELD
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Create_byte_field&quot;
comma
id|ARGP_BYTE_FIELD_OP
comma
id|ARGI_BYTE_FIELD_OP
)paren
comma
multiline_comment|/*  36 */
multiline_comment|/* AML_BIT_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CREATE_FIELD
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Create_bit_field&quot;
comma
id|ARGP_BIT_FIELD_OP
comma
id|ARGI_BIT_FIELD_OP
)paren
comma
multiline_comment|/*  37 */
multiline_comment|/* AML_TYPE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Object_type&quot;
comma
id|ARGP_TYPE_OP
comma
id|ARGI_TYPE_OP
)paren
comma
multiline_comment|/*  38 */
multiline_comment|/* AML_LAND_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LAnd&quot;
comma
id|ARGP_LAND_OP
comma
id|ARGI_LAND_OP
)paren
comma
multiline_comment|/*  39 */
multiline_comment|/* AML_LOR_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LOr&quot;
comma
id|ARGP_LOR_OP
comma
id|ARGI_LOR_OP
)paren
comma
multiline_comment|/*  3_a */
multiline_comment|/* AML_LNOT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LNot&quot;
comma
id|ARGP_LNOT_OP
comma
id|ARGI_LNOT_OP
)paren
comma
multiline_comment|/*  3_b */
multiline_comment|/* AML_LEQUAL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LEqual&quot;
comma
id|ARGP_LEQUAL_OP
comma
id|ARGI_LEQUAL_OP
)paren
comma
multiline_comment|/*  3_c */
multiline_comment|/* AML_LGREATER_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LGreater&quot;
comma
id|ARGP_LGREATER_OP
comma
id|ARGI_LGREATER_OP
)paren
comma
multiline_comment|/*  3_d */
multiline_comment|/* AML_LLESS_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LLess&quot;
comma
id|ARGP_LLESS_OP
comma
id|ARGI_LLESS_OP
)paren
comma
multiline_comment|/*  3_e */
multiline_comment|/* AML_IF_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONTROL
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;If&quot;
comma
id|ARGP_IF_OP
comma
id|ARGI_IF_OP
)paren
comma
multiline_comment|/*  3_f */
multiline_comment|/* AML_ELSE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONTROL
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Else&quot;
comma
id|ARGP_ELSE_OP
comma
id|ARGI_ELSE_OP
)paren
comma
multiline_comment|/*  40 */
multiline_comment|/* AML_WHILE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONTROL
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;While&quot;
comma
id|ARGP_WHILE_OP
comma
id|ARGI_WHILE_OP
)paren
comma
multiline_comment|/*  41 */
multiline_comment|/* AML_NOOP_OP   */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONTROL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Noop&quot;
comma
id|ARGP_NOOP_OP
comma
id|ARGI_NOOP_OP
)paren
comma
multiline_comment|/*  42 */
multiline_comment|/* AML_RETURN_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONTROL
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Return&quot;
comma
id|ARGP_RETURN_OP
comma
id|ARGI_RETURN_OP
)paren
comma
multiline_comment|/*  43 */
multiline_comment|/* AML_BREAK_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONTROL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Break&quot;
comma
id|ARGP_BREAK_OP
comma
id|ARGI_BREAK_OP
)paren
comma
multiline_comment|/*  44 */
multiline_comment|/* AML_BREAK_POINT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONTROL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Break_point&quot;
comma
id|ARGP_BREAK_POINT_OP
comma
id|ARGI_BREAK_POINT_OP
)paren
comma
multiline_comment|/*  45 */
multiline_comment|/* AML_ONES_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONSTANT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Ones_op&quot;
comma
id|ARGP_ONES_OP
comma
id|ARGI_ONES_OP
)paren
comma
multiline_comment|/* Prefixed opcodes (Two-byte opcodes with a prefix op) */
multiline_comment|/*  46 */
multiline_comment|/* AML_MUTEX_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Mutex&quot;
comma
id|ARGP_MUTEX_OP
comma
id|ARGI_MUTEX_OP
)paren
comma
multiline_comment|/*  47 */
multiline_comment|/* AML_EVENT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Event&quot;
comma
id|ARGP_EVENT_OP
comma
id|ARGI_EVENT_OP
)paren
comma
multiline_comment|/*  48 */
multiline_comment|/* AML_COND_REF_OF_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Cond_ref_of&quot;
comma
id|ARGP_COND_REF_OF_OP
comma
id|ARGI_COND_REF_OF_OP
)paren
comma
multiline_comment|/*  49 */
multiline_comment|/* AML_CREATE_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CREATE_FIELD
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Create_field&quot;
comma
id|ARGP_CREATE_FIELD_OP
comma
id|ARGI_CREATE_FIELD_OP
)paren
comma
multiline_comment|/*  4_a */
multiline_comment|/* AML_LOAD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_RECONFIGURATION
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Load&quot;
comma
id|ARGP_LOAD_OP
comma
id|ARGI_LOAD_OP
)paren
comma
multiline_comment|/*  4_b */
multiline_comment|/* AML_STALL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC1
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Stall&quot;
comma
id|ARGP_STALL_OP
comma
id|ARGI_STALL_OP
)paren
comma
multiline_comment|/*  4_c */
multiline_comment|/* AML_SLEEP_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC1
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Sleep&quot;
comma
id|ARGP_SLEEP_OP
comma
id|ARGI_SLEEP_OP
)paren
comma
multiline_comment|/*  4_d */
multiline_comment|/* AML_ACQUIRE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_s
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Acquire&quot;
comma
id|ARGP_ACQUIRE_OP
comma
id|ARGI_ACQUIRE_OP
)paren
comma
multiline_comment|/*  4_e */
multiline_comment|/* AML_SIGNAL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC1
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Signal&quot;
comma
id|ARGP_SIGNAL_OP
comma
id|ARGI_SIGNAL_OP
)paren
comma
multiline_comment|/*  4_f */
multiline_comment|/* AML_WAIT_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_DYADIC2_s
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Wait&quot;
comma
id|ARGP_WAIT_OP
comma
id|ARGI_WAIT_OP
)paren
comma
multiline_comment|/*  50 */
multiline_comment|/* AML_RESET_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC1
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Reset&quot;
comma
id|ARGP_RESET_OP
comma
id|ARGI_RESET_OP
)paren
comma
multiline_comment|/*  51 */
multiline_comment|/* AML_RELEASE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC1
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Release&quot;
comma
id|ARGP_RELEASE_OP
comma
id|ARGI_RELEASE_OP
)paren
comma
multiline_comment|/*  52 */
multiline_comment|/* AML_FROM_BCD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;From_bCD&quot;
comma
id|ARGP_FROM_BCD_OP
comma
id|ARGI_FROM_BCD_OP
)paren
comma
multiline_comment|/*  53 */
multiline_comment|/* AML_TO_BCD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_MONADIC2_r
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;To_bCD&quot;
comma
id|ARGP_TO_BCD_OP
comma
id|ARGI_TO_BCD_OP
)paren
comma
multiline_comment|/*  54 */
multiline_comment|/* AML_UNLOAD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_RECONFIGURATION
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Unload&quot;
comma
id|ARGP_UNLOAD_OP
comma
id|ARGI_UNLOAD_OP
)paren
comma
multiline_comment|/*  55 */
multiline_comment|/* AML_REVISION_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONSTANT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Revision&quot;
comma
id|ARGP_REVISION_OP
comma
id|ARGI_REVISION_OP
)paren
comma
multiline_comment|/*  56 */
multiline_comment|/* AML_DEBUG_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_CONSTANT
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Debug&quot;
comma
id|ARGP_DEBUG_OP
comma
id|ARGI_DEBUG_OP
)paren
comma
multiline_comment|/*  57 */
multiline_comment|/* AML_FATAL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_FATAL
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Fatal&quot;
comma
id|ARGP_FATAL_OP
comma
id|ARGI_FATAL_OP
)paren
comma
multiline_comment|/*  58 */
multiline_comment|/* AML_REGION_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Op_region&quot;
comma
id|ARGP_REGION_OP
comma
id|ARGI_REGION_OP
)paren
comma
multiline_comment|/*  59 */
multiline_comment|/* AML_DEF_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Field&quot;
comma
id|ARGP_DEF_FIELD_OP
comma
id|ARGI_DEF_FIELD_OP
)paren
comma
multiline_comment|/*  5_a */
multiline_comment|/* AML_DEVICE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Device&quot;
comma
id|ARGP_DEVICE_OP
comma
id|ARGI_DEVICE_OP
)paren
comma
multiline_comment|/*  5_b */
multiline_comment|/* AML_PROCESSOR_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Processor&quot;
comma
id|ARGP_PROCESSOR_OP
comma
id|ARGI_PROCESSOR_OP
)paren
comma
multiline_comment|/*  5_c */
multiline_comment|/* AML_POWER_RES_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Power_res&quot;
comma
id|ARGP_POWER_RES_OP
comma
id|ARGI_POWER_RES_OP
)paren
comma
multiline_comment|/*  5_d */
multiline_comment|/* AML_THERMAL_ZONE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Thermal_zone&quot;
comma
id|ARGP_THERMAL_ZONE_OP
comma
id|ARGI_THERMAL_ZONE_OP
)paren
comma
multiline_comment|/*  5_e */
multiline_comment|/* AML_INDEX_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Index_field&quot;
comma
id|ARGP_INDEX_FIELD_OP
comma
id|ARGI_INDEX_FIELD_OP
)paren
comma
multiline_comment|/*  5_f */
multiline_comment|/* AML_BANK_FIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_NAMED_OBJECT
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Bank_field&quot;
comma
id|ARGP_BANK_FIELD_OP
comma
id|ARGI_BANK_FIELD_OP
)paren
comma
multiline_comment|/* Internal opcodes that map to invalid AML opcodes */
multiline_comment|/*  60 */
multiline_comment|/* AML_LNOTEQUAL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_BOGUS
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LNot_equal&quot;
comma
id|ARGP_LNOTEQUAL_OP
comma
id|ARGI_LNOTEQUAL_OP
)paren
comma
multiline_comment|/*  61 */
multiline_comment|/* AML_LLESSEQUAL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_BOGUS
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LLess_equal&quot;
comma
id|ARGP_LLESSEQUAL_OP
comma
id|ARGI_LLESSEQUAL_OP
)paren
comma
multiline_comment|/*  62 */
multiline_comment|/* AML_LGREATEREQUAL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_BOGUS
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;LGreater_equal&quot;
comma
id|ARGP_LGREATEREQUAL_OP
comma
id|ARGI_LGREATEREQUAL_OP
)paren
comma
multiline_comment|/*  63 */
multiline_comment|/* AML_NAMEPATH_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LITERAL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Name_path&quot;
comma
id|ARGP_NAMEPATH_OP
comma
id|ARGI_NAMEPATH_OP
)paren
comma
multiline_comment|/*  64 */
multiline_comment|/* AML_METHODCALL_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_METHOD_CALL
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;Method_call&quot;
comma
id|ARGP_METHODCALL_OP
comma
id|ARGI_METHODCALL_OP
)paren
comma
multiline_comment|/*  65 */
multiline_comment|/* AML_BYTELIST_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_LITERAL
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Byte_list&quot;
comma
id|ARGP_BYTELIST_OP
comma
id|ARGI_BYTELIST_OP
)paren
comma
multiline_comment|/*  66 */
multiline_comment|/* AML_RESERVEDFIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_BOGUS
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Reserved_field&quot;
comma
id|ARGP_RESERVEDFIELD_OP
comma
id|ARGI_RESERVEDFIELD_OP
)paren
comma
multiline_comment|/*  67 */
multiline_comment|/* AML_NAMEDFIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_BOGUS
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Named_field&quot;
comma
id|ARGP_NAMEDFIELD_OP
comma
id|ARGI_NAMEDFIELD_OP
)paren
comma
multiline_comment|/*  68 */
multiline_comment|/* AML_ACCESSFIELD_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_BOGUS
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Access_field&quot;
comma
id|ARGP_ACCESSFIELD_OP
comma
id|ARGI_ACCESSFIELD_OP
)paren
comma
multiline_comment|/*  69 */
multiline_comment|/* AML_STATICSTRING_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_BOGUS
op_or
id|AML_NO_ARGS
comma
l_string|&quot;Static_string&quot;
comma
id|ARGP_STATICSTRING_OP
comma
id|ARGI_STATICSTRING_OP
)paren
comma
multiline_comment|/*  6_a */
multiline_comment|/* AML_RETURN_VALUE_OP */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_OPCODE
op_or
id|OPTYPE_RETURN
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;[Return Value]&quot;
comma
id|ARG_NONE
comma
id|ARG_NONE
)paren
comma
multiline_comment|/*  6_b */
multiline_comment|/* UNKNOWN OPCODES */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_UNKNOWN
op_or
id|OPTYPE_BOGUS
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;UNKNOWN_OP!&quot;
comma
id|ARG_NONE
comma
id|ARG_NONE
)paren
comma
multiline_comment|/*  6_c */
multiline_comment|/* ASCII CHARACTERS */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_ASCII
op_or
id|OPTYPE_BOGUS
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;ASCII_ONLY!&quot;
comma
id|ARG_NONE
comma
id|ARG_NONE
)paren
comma
multiline_comment|/*  6_d */
multiline_comment|/* PREFIX CHARACTERS */
id|OP_INFO_ENTRY
(paren
id|ACPI_OP_TYPE_PREFIX
op_or
id|OPTYPE_BOGUS
op_or
id|AML_HAS_ARGS
comma
l_string|&quot;PREFIX_ONLY!&quot;
comma
id|ARG_NONE
comma
id|ARG_NONE
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This table is directly indexed by the opcodes, and returns an&n; * index into the table above&n; */
DECL|variable|aml_short_op_info_index
r_static
id|u8
id|aml_short_op_info_index
(braket
l_int|256
)braket
op_assign
(brace
multiline_comment|/*              0     1     2     3     4     5     6     7  */
multiline_comment|/* 0x00 */
l_int|0x00
comma
l_int|0x01
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
l_int|0x02
comma
id|_UNK
comma
multiline_comment|/* 0x08 */
l_int|0x03
comma
id|_UNK
comma
l_int|0x04
comma
l_int|0x05
comma
l_int|0x06
comma
l_int|0x07
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x10 */
l_int|0x08
comma
l_int|0x09
comma
l_int|0x0a
comma
id|_UNK
comma
l_int|0x0b
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x18 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x20 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x28 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
l_int|0x63
comma
id|_PFX
comma
id|_PFX
comma
multiline_comment|/* 0x30 */
l_int|0x67
comma
l_int|0x66
comma
l_int|0x68
comma
l_int|0x65
comma
l_int|0x69
comma
l_int|0x64
comma
l_int|0x6A
comma
id|_UNK
comma
multiline_comment|/* 0x38 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x40 */
id|_UNK
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
multiline_comment|/* 0x48 */
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
multiline_comment|/* 0x50 */
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
multiline_comment|/* 0x58 */
id|_ASC
comma
id|_ASC
comma
id|_ASC
comma
id|_UNK
comma
id|_PFX
comma
id|_UNK
comma
id|_PFX
comma
id|_ASC
comma
multiline_comment|/* 0x60 */
l_int|0x0c
comma
l_int|0x0d
comma
l_int|0x0e
comma
l_int|0x0f
comma
l_int|0x10
comma
l_int|0x11
comma
l_int|0x12
comma
l_int|0x13
comma
multiline_comment|/* 0x68 */
l_int|0x14
comma
l_int|0x15
comma
l_int|0x16
comma
l_int|0x17
comma
l_int|0x18
comma
l_int|0x19
comma
l_int|0x1a
comma
id|_UNK
comma
multiline_comment|/* 0x70 */
l_int|0x1b
comma
l_int|0x1c
comma
l_int|0x1d
comma
l_int|0x1e
comma
l_int|0x1f
comma
l_int|0x20
comma
l_int|0x21
comma
l_int|0x22
comma
multiline_comment|/* 0x78 */
l_int|0x23
comma
l_int|0x24
comma
l_int|0x25
comma
l_int|0x26
comma
l_int|0x27
comma
l_int|0x28
comma
l_int|0x29
comma
l_int|0x2a
comma
multiline_comment|/* 0x80 */
l_int|0x2b
comma
l_int|0x2c
comma
l_int|0x2d
comma
l_int|0x2e
comma
id|_UNK
comma
id|_UNK
comma
l_int|0x2f
comma
l_int|0x30
comma
multiline_comment|/* 0x88 */
l_int|0x31
comma
l_int|0x32
comma
l_int|0x33
comma
l_int|0x34
comma
l_int|0x35
comma
l_int|0x36
comma
l_int|0x37
comma
id|_UNK
comma
multiline_comment|/* 0x90 */
l_int|0x38
comma
l_int|0x39
comma
l_int|0x3a
comma
l_int|0x3b
comma
l_int|0x3c
comma
l_int|0x3d
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x98 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xA0 */
l_int|0x3e
comma
l_int|0x3f
comma
l_int|0x40
comma
l_int|0x41
comma
l_int|0x42
comma
l_int|0x43
comma
l_int|0x60
comma
l_int|0x61
comma
multiline_comment|/* 0xA8 */
l_int|0x62
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xB0 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xB8 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xC0 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xC8 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
l_int|0x44
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xD0 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xD8 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xE0 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xE8 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xF0 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0xF8 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
l_int|0x45
comma
)brace
suffix:semicolon
DECL|variable|aml_long_op_info_index
r_static
id|u8
id|aml_long_op_info_index
(braket
id|NUM_EXTENDED_OPCODE
)braket
op_assign
(brace
multiline_comment|/*              0     1     2     3     4     5     6     7  */
multiline_comment|/* 0x00 */
id|_UNK
comma
l_int|0x46
comma
l_int|0x47
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x08 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x10 */
id|_UNK
comma
id|_UNK
comma
l_int|0x48
comma
l_int|0x49
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x18 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x20 */
l_int|0x4a
comma
l_int|0x4b
comma
l_int|0x4c
comma
l_int|0x4d
comma
l_int|0x4e
comma
l_int|0x4f
comma
l_int|0x50
comma
l_int|0x51
comma
multiline_comment|/* 0x28 */
l_int|0x52
comma
l_int|0x53
comma
l_int|0x54
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x30 */
l_int|0x55
comma
l_int|0x56
comma
l_int|0x57
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x38 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x40 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x48 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x50 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x58 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x60 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x68 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x70 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x78 */
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
id|_UNK
comma
multiline_comment|/* 0x80 */
l_int|0x58
comma
l_int|0x59
comma
l_int|0x5a
comma
l_int|0x5b
comma
l_int|0x5c
comma
l_int|0x5d
comma
l_int|0x5e
comma
l_int|0x5f
comma
)brace
suffix:semicolon
multiline_comment|/*              0     1     2     3     4     5     6     7  */
multiline_comment|/* 0x00 */
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_opcode_info&n; *&n; * PARAMETERS:  Opcode              - The AML opcode&n; *&n; * RETURN:      A pointer to the info about the opcode.  NULL if the opcode was&n; *              not found in the table.&n; *&n; * DESCRIPTION: Find AML opcode description based on the opcode.&n; *              NOTE: This procedure must ALWAYS return a valid pointer!&n; *&n; ******************************************************************************/
id|ACPI_OPCODE_INFO
op_star
DECL|function|acpi_ps_get_opcode_info
id|acpi_ps_get_opcode_info
(paren
id|u16
id|opcode
)paren
(brace
id|ACPI_OPCODE_INFO
op_star
id|op_info
suffix:semicolon
id|u8
id|upper_opcode
suffix:semicolon
id|u8
id|lower_opcode
suffix:semicolon
multiline_comment|/* Split the 16-bit opcode into separate bytes */
id|upper_opcode
op_assign
(paren
id|u8
)paren
(paren
id|opcode
op_rshift
l_int|8
)paren
suffix:semicolon
id|lower_opcode
op_assign
(paren
id|u8
)paren
id|opcode
suffix:semicolon
multiline_comment|/* Default is &quot;unknown opcode&quot; */
id|op_info
op_assign
op_amp
id|aml_op_info
(braket
id|_UNK
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Detect normal 8-bit opcode or extended 16-bit opcode&n;&t; */
r_switch
c_cond
(paren
id|upper_opcode
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Simple (8-bit) opcode: 0-255, can&squot;t index beyond table  */
id|op_info
op_assign
op_amp
id|aml_op_info
(braket
id|aml_short_op_info_index
(braket
id|lower_opcode
)braket
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_EXTOP
suffix:colon
multiline_comment|/* Extended (16-bit, prefix+opcode) opcode */
r_if
c_cond
(paren
id|lower_opcode
op_le
id|MAX_EXTENDED_OPCODE
)paren
(brace
id|op_info
op_assign
op_amp
id|aml_op_info
(braket
id|aml_long_op_info_index
(braket
id|lower_opcode
)braket
)braket
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AML_LNOT_OP
suffix:colon
multiline_comment|/* This case is for the bogus opcodes LNOTEQUAL, LLESSEQUAL, LGREATEREQUAL */
multiline_comment|/* TBD: [Investigate] remove this case? */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Get the Op info pointer for this opcode */
r_return
(paren
id|op_info
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_opcode_name&n; *&n; * PARAMETERS:  Opcode              - The AML opcode&n; *&n; * RETURN:      A pointer to the name of the opcode (ASCII String)&n; *              Note: Never returns NULL.&n; *&n; * DESCRIPTION: Translate an opcode into a human-readable string&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_ps_get_opcode_name
id|acpi_ps_get_opcode_name
(paren
id|u16
id|opcode
)paren
(brace
id|ACPI_OPCODE_INFO
op_star
id|op
suffix:semicolon
id|op
op_assign
id|acpi_ps_get_opcode_info
(paren
id|opcode
)paren
suffix:semicolon
multiline_comment|/* Always guaranteed to return a valid pointer */
r_return
(paren
l_string|&quot;AE_NOT_CONFIGURED&quot;
)paren
suffix:semicolon
)brace
eof
