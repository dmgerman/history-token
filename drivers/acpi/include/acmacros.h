multiline_comment|/******************************************************************************&n; *&n; * Name: acmacros.h - C macros for the entire subsystem.&n; *       $Revision: 72 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACMACROS_H__
DECL|macro|__ACMACROS_H__
mdefine_line|#define __ACMACROS_H__
multiline_comment|/*&n; * Data manipulation macros&n; */
macro_line|#ifndef LODWORD
DECL|macro|LODWORD
mdefine_line|#define LODWORD(l)                      ((u32)(UINT64)(l))
macro_line|#endif
macro_line|#ifndef HIDWORD
DECL|macro|HIDWORD
mdefine_line|#define HIDWORD(l)                      ((u32)((((UINT64)(l)) &gt;&gt; 32) &amp; 0xFFFFFFFF))
macro_line|#endif
macro_line|#ifndef LOWORD
DECL|macro|LOWORD
mdefine_line|#define LOWORD(l)                       ((u16)(NATIVE_UINT)(l))
macro_line|#endif
macro_line|#ifndef HIWORD
DECL|macro|HIWORD
mdefine_line|#define HIWORD(l)                       ((u16)((((NATIVE_UINT)(l)) &gt;&gt; 16) &amp; 0xFFFF))
macro_line|#endif
macro_line|#ifndef LOBYTE
DECL|macro|LOBYTE
mdefine_line|#define LOBYTE(l)                       ((u8)(u16)(l))
macro_line|#endif
macro_line|#ifndef HIBYTE
DECL|macro|HIBYTE
mdefine_line|#define HIBYTE(l)                       ((u8)((((u16)(l)) &gt;&gt; 8) &amp; 0xFF))
macro_line|#endif
DECL|macro|BIT0
mdefine_line|#define BIT0(x)                         ((((x) &amp; 0x01) &gt; 0) ? 1 : 0)
DECL|macro|BIT1
mdefine_line|#define BIT1(x)                         ((((x) &amp; 0x02) &gt; 0) ? 1 : 0)
DECL|macro|BIT2
mdefine_line|#define BIT2(x)                         ((((x) &amp; 0x04) &gt; 0) ? 1 : 0)
DECL|macro|BIT3
mdefine_line|#define BIT3(x)                         ((((x) &amp; 0x08) &gt; 0) ? 1 : 0)
DECL|macro|BIT4
mdefine_line|#define BIT4(x)                         ((((x) &amp; 0x10) &gt; 0) ? 1 : 0)
DECL|macro|BIT5
mdefine_line|#define BIT5(x)                         ((((x) &amp; 0x20) &gt; 0) ? 1 : 0)
DECL|macro|BIT6
mdefine_line|#define BIT6(x)                         ((((x) &amp; 0x40) &gt; 0) ? 1 : 0)
DECL|macro|BIT7
mdefine_line|#define BIT7(x)                         ((((x) &amp; 0x80) &gt; 0) ? 1 : 0)
DECL|macro|LOW_BASE
mdefine_line|#define LOW_BASE(w)                     ((u16) ((w) &amp; 0x0000FFFF))
DECL|macro|MID_BASE
mdefine_line|#define MID_BASE(b)                     ((u8) (((b) &amp; 0x00FF0000) &gt;&gt; 16))
DECL|macro|HI_BASE
mdefine_line|#define HI_BASE(b)                      ((u8) (((b) &amp; 0xFF000000) &gt;&gt; 24))
DECL|macro|LOW_LIMIT
mdefine_line|#define LOW_LIMIT(w)                    ((u16) ((w) &amp; 0x0000FFFF))
DECL|macro|HI_LIMIT
mdefine_line|#define HI_LIMIT(b)                     ((u8) (((b) &amp; 0x00FF0000) &gt;&gt; 16))
macro_line|#ifdef _IA16
multiline_comment|/*&n; * For 16-bit addresses, we have to assume that the upper 32 bits&n; * are zero.&n; */
DECL|macro|ACPI_GET_ADDRESS
mdefine_line|#define ACPI_GET_ADDRESS(a)             ((a).lo)
DECL|macro|ACPI_STORE_ADDRESS
mdefine_line|#define ACPI_STORE_ADDRESS(a,b)         {(a).hi=0;(a).lo=(b);}
DECL|macro|ACPI_VALID_ADDRESS
mdefine_line|#define ACPI_VALID_ADDRESS(a)           ((a).hi | (a).lo)
macro_line|#else
multiline_comment|/*&n; * Full 64-bit address on 32-bit and 64-bit platforms&n; */
DECL|macro|ACPI_GET_ADDRESS
mdefine_line|#define ACPI_GET_ADDRESS(a)             (a)
DECL|macro|ACPI_STORE_ADDRESS
mdefine_line|#define ACPI_STORE_ADDRESS(a,b)         ((a)=(b))
DECL|macro|ACPI_VALID_ADDRESS
mdefine_line|#define ACPI_VALID_ADDRESS(a)           (a)
macro_line|#endif
multiline_comment|/*&n;  * Extract a byte of data using a pointer.  Any more than a byte and we&n;  * get into potential aligment issues -- see the STORE macros below&n;  */
DECL|macro|GET8
mdefine_line|#define GET8(addr)                      (*(u8*)(addr))
multiline_comment|/* Pointer arithmetic */
DECL|macro|POINTER_ADD
mdefine_line|#define POINTER_ADD(t,a,b)              (t *) ((NATIVE_UINT)(a) + (NATIVE_UINT)(b))
DECL|macro|POINTER_DIFF
mdefine_line|#define POINTER_DIFF(a,b)               ((u32) ((NATIVE_UINT)(a) - (NATIVE_UINT)(b)))
multiline_comment|/*&n; * Macros for moving data around to/from buffers that are possibly unaligned.&n; * If the hardware supports the transfer of unaligned data, just do the store.&n; * Otherwise, we have to move one byte at a time.&n; */
macro_line|#ifdef _HW_ALIGNMENT_SUPPORT
multiline_comment|/* The hardware supports unaligned transfers, just do the move */
DECL|macro|MOVE_UNALIGNED16_TO_16
mdefine_line|#define MOVE_UNALIGNED16_TO_16(d,s)     *(u16*)(d) = *(u16*)(s)
DECL|macro|MOVE_UNALIGNED32_TO_32
mdefine_line|#define MOVE_UNALIGNED32_TO_32(d,s)     *(u32*)(d) = *(u32*)(s)
DECL|macro|MOVE_UNALIGNED16_TO_32
mdefine_line|#define MOVE_UNALIGNED16_TO_32(d,s)     *(u32*)(d) = *(u16*)(s)
DECL|macro|MOVE_UNALIGNED64_TO_64
mdefine_line|#define MOVE_UNALIGNED64_TO_64(d,s)     *(UINT64*)(d) = *(UINT64*)(s)
macro_line|#else
multiline_comment|/*&n; * The hardware does not support unaligned transfers.  We must move the&n; * data one byte at a time.  These macros work whether the source or&n; * the destination (or both) is/are unaligned.&n; */
DECL|macro|MOVE_UNALIGNED16_TO_16
mdefine_line|#define MOVE_UNALIGNED16_TO_16(d,s)     {((u8 *)(d))[0] = ((u8 *)(s))[0];&bslash;&n;&t; ((u8 *)(d))[1] = ((u8 *)(s))[1];}
DECL|macro|MOVE_UNALIGNED32_TO_32
mdefine_line|#define MOVE_UNALIGNED32_TO_32(d,s)     {((u8 *)(d))[0] = ((u8 *)(s))[0];&bslash;&n;&t;&t;&t;  ((u8 *)(d))[1] = ((u8 *)(s))[1];&bslash;&n;&t;&t;&t;  ((u8 *)(d))[2] = ((u8 *)(s))[2];&bslash;&n;&t;&t;&t;  ((u8 *)(d))[3] = ((u8 *)(s))[3];}
DECL|macro|MOVE_UNALIGNED16_TO_32
mdefine_line|#define MOVE_UNALIGNED16_TO_32(d,s)     {(*(u32*)(d)) = 0; MOVE_UNALIGNED16_TO_16(d,s);}
DECL|macro|MOVE_UNALIGNED64_TO_64
mdefine_line|#define MOVE_UNALIGNED64_TO_64(d,s)     {((u8 *)(d))[0] = ((u8 *)(s))[0];&bslash;&n;&t;&t;&t;&t;&t;   ((u8 *)(d))[1] = ((u8 *)(s))[1];&bslash;&n;&t;&t;&t;&t;&t;   ((u8 *)(d))[2] = ((u8 *)(s))[2];&bslash;&n;&t;&t;&t;&t;&t;   ((u8 *)(d))[3] = ((u8 *)(s))[3];&bslash;&n;&t;&t;&t;&t;&t;   ((u8 *)(d))[4] = ((u8 *)(s))[4];&bslash;&n;&t;&t;&t;&t;&t;   ((u8 *)(d))[5] = ((u8 *)(s))[5];&bslash;&n;&t;&t;&t;&t;&t;   ((u8 *)(d))[6] = ((u8 *)(s))[6];&bslash;&n;&t;&t;&t;&t;&t;   ((u8 *)(d))[7] = ((u8 *)(s))[7];}
macro_line|#endif
multiline_comment|/*&n; * Fast power-of-two math macros for non-optimized compilers&n; */
DECL|macro|_DIV
mdefine_line|#define _DIV(value,power_of2)           ((u32) ((value) &gt;&gt; (power_of2)))
DECL|macro|_MUL
mdefine_line|#define _MUL(value,power_of2)           ((u32) ((value) &lt;&lt; (power_of2)))
DECL|macro|_MOD
mdefine_line|#define _MOD(value,divisor)             ((u32) ((value) &amp; ((divisor) -1)))
DECL|macro|DIV_2
mdefine_line|#define DIV_2(a)                        _DIV(a,1)
DECL|macro|MUL_2
mdefine_line|#define MUL_2(a)                        _MUL(a,1)
DECL|macro|MOD_2
mdefine_line|#define MOD_2(a)                        _MOD(a,2)
DECL|macro|DIV_4
mdefine_line|#define DIV_4(a)                        _DIV(a,2)
DECL|macro|MUL_4
mdefine_line|#define MUL_4(a)                        _MUL(a,2)
DECL|macro|MOD_4
mdefine_line|#define MOD_4(a)                        _MOD(a,4)
DECL|macro|DIV_8
mdefine_line|#define DIV_8(a)                        _DIV(a,3)
DECL|macro|MUL_8
mdefine_line|#define MUL_8(a)                        _MUL(a,3)
DECL|macro|MOD_8
mdefine_line|#define MOD_8(a)                        _MOD(a,8)
DECL|macro|DIV_16
mdefine_line|#define DIV_16(a)                       _DIV(a,4)
DECL|macro|MUL_16
mdefine_line|#define MUL_16(a)                       _MUL(a,4)
DECL|macro|MOD_16
mdefine_line|#define MOD_16(a)                       _MOD(a,16)
multiline_comment|/*&n; * Divide and Modulo&n; */
DECL|macro|ACPI_DIVIDE
mdefine_line|#define ACPI_DIVIDE(n,d)                ((n) / (d))
DECL|macro|ACPI_MODULO
mdefine_line|#define ACPI_MODULO(n,d)                ((n) % (d))
multiline_comment|/*&n; * Rounding macros (Power of two boundaries only)&n; */
DECL|macro|ROUND_DOWN
mdefine_line|#define ROUND_DOWN(value,boundary)      ((value) &amp; (~((boundary)-1)))
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(value,boundary)        (((value) + ((boundary)-1)) &amp; (~((boundary)-1)))
DECL|macro|ROUND_DOWN_TO_32_BITS
mdefine_line|#define ROUND_DOWN_TO_32_BITS(a)        ROUND_DOWN(a,4)
DECL|macro|ROUND_DOWN_TO_64_BITS
mdefine_line|#define ROUND_DOWN_TO_64_BITS(a)        ROUND_DOWN(a,8)
DECL|macro|ROUND_DOWN_TO_NATIVE_WORD
mdefine_line|#define ROUND_DOWN_TO_NATIVE_WORD(a)    ROUND_DOWN(a,ALIGNED_ADDRESS_BOUNDARY)
DECL|macro|ROUND_UP_TO_32_bITS
mdefine_line|#define ROUND_UP_TO_32_bITS(a)          ROUND_UP(a,4)
DECL|macro|ROUND_UP_TO_64_bITS
mdefine_line|#define ROUND_UP_TO_64_bITS(a)          ROUND_UP(a,8)
DECL|macro|ROUND_UP_TO_NATIVE_WORD
mdefine_line|#define ROUND_UP_TO_NATIVE_WORD(a)      ROUND_UP(a,ALIGNED_ADDRESS_BOUNDARY)
DECL|macro|ROUND_PTR_UP_TO_4
mdefine_line|#define ROUND_PTR_UP_TO_4(a,b)          ((b *)(((NATIVE_UINT)(a) + 3) &amp; ~3))
DECL|macro|ROUND_PTR_UP_TO_8
mdefine_line|#define ROUND_PTR_UP_TO_8(a,b)          ((b *)(((NATIVE_UINT)(a) + 7) &amp; ~7))
DECL|macro|ROUND_BITS_UP_TO_BYTES
mdefine_line|#define ROUND_BITS_UP_TO_BYTES(a)       DIV_8((a) + 7)
DECL|macro|ROUND_BITS_DOWN_TO_BYTES
mdefine_line|#define ROUND_BITS_DOWN_TO_BYTES(a)     DIV_8((a))
DECL|macro|ROUND_UP_TO_1_k
mdefine_line|#define ROUND_UP_TO_1_k(a)              (((a) + 1023) &gt;&gt; 10)
multiline_comment|/* Generic (non-power-of-two) rounding */
DECL|macro|ROUND_UP_TO
mdefine_line|#define ROUND_UP_TO(value,boundary)     (((value) + ((boundary)-1)) / (boundary))
multiline_comment|/*&n; * Bitmask creation&n; * Bit positions start at zero.&n; * MASK_BITS_ABOVE creates a mask starting AT the position and above&n; * MASK_BITS_BELOW creates a mask starting one bit BELOW the position&n; */
DECL|macro|MASK_BITS_ABOVE
mdefine_line|#define MASK_BITS_ABOVE(position)       (~(((u32)(-1)) &lt;&lt; ((u32) (position))))
DECL|macro|MASK_BITS_BELOW
mdefine_line|#define MASK_BITS_BELOW(position)       (((u32)(-1)) &lt;&lt; ((u32) (position)))
macro_line|#ifdef DEBUG_ASSERT
DECL|macro|DEBUG_ASSERT
macro_line|#undef DEBUG_ASSERT
macro_line|#endif
multiline_comment|/* Macros for GAS addressing */
DECL|macro|ACPI_PCI_DEVICE_MASK
mdefine_line|#define ACPI_PCI_DEVICE_MASK            (UINT64) 0x0000FFFF00000000
DECL|macro|ACPI_PCI_FUNCTION_MASK
mdefine_line|#define ACPI_PCI_FUNCTION_MASK          (UINT64) 0x00000000FFFF0000
DECL|macro|ACPI_PCI_REGISTER_MASK
mdefine_line|#define ACPI_PCI_REGISTER_MASK          (UINT64) 0x000000000000FFFF
DECL|macro|ACPI_PCI_FUNCTION
mdefine_line|#define ACPI_PCI_FUNCTION(a)            (u32) ((((a) &amp; ACPI_PCI_FUNCTION_MASK) &gt;&gt; 16))
DECL|macro|ACPI_PCI_DEVICE
mdefine_line|#define ACPI_PCI_DEVICE(a)              (u32) ((((a) &amp; ACPI_PCI_DEVICE_MASK) &gt;&gt; 32))
macro_line|#ifndef _IA16
DECL|macro|ACPI_PCI_REGISTER
mdefine_line|#define ACPI_PCI_REGISTER(a)            (u32) (((a) &amp; ACPI_PCI_REGISTER_MASK))
DECL|macro|ACPI_PCI_DEVFUN
mdefine_line|#define ACPI_PCI_DEVFUN(a)              (u32) ((ACPI_PCI_DEVICE(a) &lt;&lt; 16) | ACPI_PCI_FUNCTION(a))
macro_line|#else
DECL|macro|ACPI_PCI_REGISTER
mdefine_line|#define ACPI_PCI_REGISTER(a)            (u32) (((a) &amp; 0x0000FFFF))
DECL|macro|ACPI_PCI_DEVFUN
mdefine_line|#define ACPI_PCI_DEVFUN(a)              (u32) ((((a) &amp; 0xFFFF0000) &gt;&gt; 16))
macro_line|#endif
multiline_comment|/*&n; * An ACPI_HANDLE (which is actually an ACPI_NAMESPACE_NODE *) can appear in some contexts,&n; * such as on ap_obj_stack, where a pointer to an ACPI_OPERAND_OBJECT can also&n; * appear.  This macro is used to distinguish them.&n; *&n; * The Data_type field is the first field in both structures.&n; */
DECL|macro|VALID_DESCRIPTOR_TYPE
mdefine_line|#define VALID_DESCRIPTOR_TYPE(d,t)      (((ACPI_NAMESPACE_NODE *)d)-&gt;data_type == t)
multiline_comment|/* Macro to test the object type */
DECL|macro|IS_THIS_OBJECT_TYPE
mdefine_line|#define IS_THIS_OBJECT_TYPE(d,t)        (((ACPI_OPERAND_OBJECT  *)d)-&gt;common.type == (u8)t)
multiline_comment|/* Macro to check the table flags for SINGLE or MULTIPLE tables are allowed */
DECL|macro|IS_SINGLE_TABLE
mdefine_line|#define IS_SINGLE_TABLE(x)              (((x) &amp; 0x01) == ACPI_TABLE_SINGLE ? 1 : 0)
multiline_comment|/* Check if ACPI has been initialized properly */
DECL|macro|ACPI_IS_INITIALIZATION_COMPLETE
mdefine_line|#define ACPI_IS_INITIALIZATION_COMPLETE(s)  {if (acpi_gbl_root_node) s = AE_OK; else s=AE_NO_NAMESPACE;}
multiline_comment|/*&n; * Macro to check if a pointer is within an ACPI table.&n; * Parameter (a) is the pointer to check.  Parameter (b) must be defined&n; * as a pointer to an ACPI_TABLE_HEADER.  (b+1) then points past the header,&n; * and ((u8 *)b+b-&gt;Length) points one byte past the end of the table.&n; */
macro_line|#ifndef _IA16
DECL|macro|IS_IN_ACPI_TABLE
mdefine_line|#define IS_IN_ACPI_TABLE(a,b)           (((u8 *)(a) &gt;= (u8 *)(b + 1)) &amp;&amp;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;   ((u8 *)(a) &lt; ((u8 *)b + b-&gt;length)))
macro_line|#else
DECL|macro|IS_IN_ACPI_TABLE
mdefine_line|#define IS_IN_ACPI_TABLE(a,b)           (_segment)(a) == (_segment)(b) &amp;&amp;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; (((u8 *)(a) &gt;= (u8 *)(b + 1)) &amp;&amp;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; ((u8 *)(a) &lt; ((u8 *)b + b-&gt;length)))
macro_line|#endif
multiline_comment|/*&n; * Macros for the master AML opcode table&n; */
macro_line|#ifdef ACPI_DEBUG
DECL|macro|OP_INFO_ENTRY
mdefine_line|#define OP_INFO_ENTRY(flags,name,Pargs,Iargs)     {flags,Pargs,Iargs,name}
macro_line|#else
DECL|macro|OP_INFO_ENTRY
mdefine_line|#define OP_INFO_ENTRY(flags,name,Pargs,Iargs)     {flags,Pargs,Iargs}
macro_line|#endif
DECL|macro|ARG_TYPE_WIDTH
mdefine_line|#define ARG_TYPE_WIDTH                  5
DECL|macro|ARG_1
mdefine_line|#define ARG_1(x)                        ((u32)(x))
DECL|macro|ARG_2
mdefine_line|#define ARG_2(x)                        ((u32)(x) &lt;&lt; (1 * ARG_TYPE_WIDTH))
DECL|macro|ARG_3
mdefine_line|#define ARG_3(x)                        ((u32)(x) &lt;&lt; (2 * ARG_TYPE_WIDTH))
DECL|macro|ARG_4
mdefine_line|#define ARG_4(x)                        ((u32)(x) &lt;&lt; (3 * ARG_TYPE_WIDTH))
DECL|macro|ARG_5
mdefine_line|#define ARG_5(x)                        ((u32)(x) &lt;&lt; (4 * ARG_TYPE_WIDTH))
DECL|macro|ARG_6
mdefine_line|#define ARG_6(x)                        ((u32)(x) &lt;&lt; (5 * ARG_TYPE_WIDTH))
DECL|macro|ARGI_LIST1
mdefine_line|#define ARGI_LIST1(a)                   (ARG_1(a))
DECL|macro|ARGI_LIST2
mdefine_line|#define ARGI_LIST2(a,b)                 (ARG_1(b)|ARG_2(a))
DECL|macro|ARGI_LIST3
mdefine_line|#define ARGI_LIST3(a,b,c)               (ARG_1(c)|ARG_2(b)|ARG_3(a))
DECL|macro|ARGI_LIST4
mdefine_line|#define ARGI_LIST4(a,b,c,d)             (ARG_1(d)|ARG_2(c)|ARG_3(b)|ARG_4(a))
DECL|macro|ARGI_LIST5
mdefine_line|#define ARGI_LIST5(a,b,c,d,e)           (ARG_1(e)|ARG_2(d)|ARG_3(c)|ARG_4(b)|ARG_5(a))
DECL|macro|ARGI_LIST6
mdefine_line|#define ARGI_LIST6(a,b,c,d,e,f)         (ARG_1(f)|ARG_2(e)|ARG_3(d)|ARG_4(c)|ARG_5(b)|ARG_6(a))
DECL|macro|ARGP_LIST1
mdefine_line|#define ARGP_LIST1(a)                   (ARG_1(a))
DECL|macro|ARGP_LIST2
mdefine_line|#define ARGP_LIST2(a,b)                 (ARG_1(a)|ARG_2(b))
DECL|macro|ARGP_LIST3
mdefine_line|#define ARGP_LIST3(a,b,c)               (ARG_1(a)|ARG_2(b)|ARG_3(c))
DECL|macro|ARGP_LIST4
mdefine_line|#define ARGP_LIST4(a,b,c,d)             (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d))
DECL|macro|ARGP_LIST5
mdefine_line|#define ARGP_LIST5(a,b,c,d,e)           (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d)|ARG_5(e))
DECL|macro|ARGP_LIST6
mdefine_line|#define ARGP_LIST6(a,b,c,d,e,f)         (ARG_1(a)|ARG_2(b)|ARG_3(c)|ARG_4(d)|ARG_5(e)|ARG_6(f))
DECL|macro|GET_CURRENT_ARG_TYPE
mdefine_line|#define GET_CURRENT_ARG_TYPE(list)      (list &amp; ((u32) 0x1F))
DECL|macro|INCREMENT_ARG_LIST
mdefine_line|#define INCREMENT_ARG_LIST(list)        (list &gt;&gt;= ((u32) ARG_TYPE_WIDTH))
multiline_comment|/*&n; * Build a GAS structure from earlier ACPI table entries (V1.0 and 0.71 extensions)&n; *&n; * 1) Address space&n; * 2) Length in bytes -- convert to length in bits&n; * 3) Bit offset is zero&n; * 4) Reserved field is zero&n; * 5) Expand address to 64 bits&n; */
DECL|macro|ASL_BUILD_GAS_FROM_ENTRY
mdefine_line|#define ASL_BUILD_GAS_FROM_ENTRY(a,b,c,d)   {a.address_space_id = (u8) d;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; a.register_bit_width = (u8) MUL_8 (b);&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; a.register_bit_offset = 0;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; a.reserved = 0;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; ACPI_STORE_ADDRESS (a.address,c);}
multiline_comment|/* ACPI V1.0 entries -- address space is always I/O */
DECL|macro|ASL_BUILD_GAS_FROM_V1_ENTRY
mdefine_line|#define ASL_BUILD_GAS_FROM_V1_ENTRY(a,b,c)  ASL_BUILD_GAS_FROM_ENTRY(a,b,c,ACPI_ADR_SPACE_SYSTEM_IO)
multiline_comment|/*&n; * Reporting macros that are never compiled out&n; */
DECL|macro|PARAM_LIST
mdefine_line|#define PARAM_LIST(pl)                  pl
multiline_comment|/*&n; * Error reporting.  These versions add callers module and line#.  Since&n; * _THIS_MODULE gets compiled out when ACPI_DEBUG isn&squot;t defined, only&n; * use it in debug mode.&n; */
macro_line|#ifdef ACPI_DEBUG
DECL|macro|REPORT_INFO
mdefine_line|#define REPORT_INFO(fp)                 {_report_info(_THIS_MODULE,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
DECL|macro|REPORT_ERROR
mdefine_line|#define REPORT_ERROR(fp)                {_report_error(_THIS_MODULE,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
DECL|macro|REPORT_WARNING
mdefine_line|#define REPORT_WARNING(fp)              {_report_warning(_THIS_MODULE,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
macro_line|#else
DECL|macro|REPORT_INFO
mdefine_line|#define REPORT_INFO(fp)                 {_report_info(&quot;ACPI&quot;,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
DECL|macro|REPORT_ERROR
mdefine_line|#define REPORT_ERROR(fp)                {_report_error(&quot;ACPI&quot;,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
DECL|macro|REPORT_WARNING
mdefine_line|#define REPORT_WARNING(fp)              {_report_warning(&quot;ACPI&quot;,__LINE__,_COMPONENT); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
macro_line|#endif
multiline_comment|/* Error reporting.  These versions pass thru the module and line# */
DECL|macro|_REPORT_INFO
mdefine_line|#define _REPORT_INFO(a,b,c,fp)          {_report_info(a,b,c); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
DECL|macro|_REPORT_ERROR
mdefine_line|#define _REPORT_ERROR(a,b,c,fp)         {_report_error(a,b,c); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
DECL|macro|_REPORT_WARNING
mdefine_line|#define _REPORT_WARNING(a,b,c,fp)       {_report_warning(a,b,c); &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
multiline_comment|/* Buffer dump macros */
DECL|macro|DUMP_BUFFER
mdefine_line|#define DUMP_BUFFER(a,b)                acpi_ut_dump_buffer((u8 *)a,b,DB_BYTE_DISPLAY,_COMPONENT)
multiline_comment|/*&n; * Debug macros that are conditionally compiled&n; */
macro_line|#ifdef ACPI_DEBUG
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME(name)               static char *_THIS_MODULE = name;
multiline_comment|/*&n; * Function entry tracing.&n; * The first parameter should be the procedure name as a quoted string.  This is declared&n; * as a local string (&quot;_Proc_name) so that it can be also used by the function exit macros below.&n; */
DECL|macro|PROC_NAME
mdefine_line|#define PROC_NAME(a)                    char * _proc_name = a;
DECL|macro|FUNCTION_TRACE
mdefine_line|#define FUNCTION_TRACE(a)               char * _proc_name = a;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;function_trace(_THIS_MODULE,__LINE__,_COMPONENT,a)
DECL|macro|FUNCTION_TRACE_PTR
mdefine_line|#define FUNCTION_TRACE_PTR(a,b)         char * _proc_name = a;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;function_trace_ptr(_THIS_MODULE,__LINE__,_COMPONENT,a,(void *)b)
DECL|macro|FUNCTION_TRACE_U32
mdefine_line|#define FUNCTION_TRACE_U32(a,b)         char * _proc_name = a;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;function_trace_u32(_THIS_MODULE,__LINE__,_COMPONENT,a,(u32)b)
DECL|macro|FUNCTION_TRACE_STR
mdefine_line|#define FUNCTION_TRACE_STR(a,b)         char * _proc_name = a;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;function_trace_str(_THIS_MODULE,__LINE__,_COMPONENT,a,(NATIVE_CHAR *)b)
multiline_comment|/*&n; * Function exit tracing.&n; * WARNING: These macros include a return statement.  This is usually considered&n; * bad form, but having a separate exit macro is very ugly and difficult to maintain.&n; * One of the FUNCTION_TRACE macros above must be used in conjunction with these macros&n; * so that &quot;_Proc_name&quot; is defined.&n; */
DECL|macro|return_VOID
mdefine_line|#define return_VOID                     {function_exit(_THIS_MODULE,__LINE__,_COMPONENT,_proc_name);return;}
DECL|macro|return_ACPI_STATUS
mdefine_line|#define return_ACPI_STATUS(s)           {function_status_exit(_THIS_MODULE,__LINE__,_COMPONENT,_proc_name,s);return(s);}
DECL|macro|return_VALUE
mdefine_line|#define return_VALUE(s)                 {function_value_exit(_THIS_MODULE,__LINE__,_COMPONENT,_proc_name,s);return(s);}
DECL|macro|return_PTR
mdefine_line|#define return_PTR(s)                   {function_ptr_exit(_THIS_MODULE,__LINE__,_COMPONENT,_proc_name,(u8 *)s);return(s);}
multiline_comment|/* Conditional execution */
DECL|macro|DEBUG_EXEC
mdefine_line|#define DEBUG_EXEC(a)                   a
DECL|macro|NORMAL_EXEC
mdefine_line|#define NORMAL_EXEC(a)
DECL|macro|DEBUG_DEFINE
mdefine_line|#define DEBUG_DEFINE(a)                 a;
DECL|macro|DEBUG_ONLY_MEMBERS
mdefine_line|#define DEBUG_ONLY_MEMBERS(a)           a;
DECL|macro|_OPCODE_NAMES
mdefine_line|#define _OPCODE_NAMES
DECL|macro|_VERBOSE_STRUCTURES
mdefine_line|#define _VERBOSE_STRUCTURES
multiline_comment|/* Stack and buffer dumping */
DECL|macro|DUMP_STACK_ENTRY
mdefine_line|#define DUMP_STACK_ENTRY(a)             acpi_ex_dump_operand(a)
DECL|macro|DUMP_OPERANDS
mdefine_line|#define DUMP_OPERANDS(a,b,c,d,e)        acpi_ex_dump_operands(a,b,c,d,e,_THIS_MODULE,__LINE__)
DECL|macro|DUMP_ENTRY
mdefine_line|#define DUMP_ENTRY(a,b)                 acpi_ns_dump_entry (a,b)
DECL|macro|DUMP_TABLES
mdefine_line|#define DUMP_TABLES(a,b)                acpi_ns_dump_tables(a,b)
DECL|macro|DUMP_PATHNAME
mdefine_line|#define DUMP_PATHNAME(a,b,c,d)          acpi_ns_dump_pathname(a,b,c,d)
DECL|macro|DUMP_RESOURCE_LIST
mdefine_line|#define DUMP_RESOURCE_LIST(a)           acpi_rs_dump_resource_list(a)
DECL|macro|BREAK_MSG
mdefine_line|#define BREAK_MSG(a)                    acpi_os_breakpoint (a)
multiline_comment|/*&n; * Generate INT3 on ACPI_ERROR (Debug only!)&n; */
DECL|macro|ERROR_BREAK
mdefine_line|#define ERROR_BREAK
macro_line|#ifdef  ERROR_BREAK
DECL|macro|BREAK_ON_ERROR
mdefine_line|#define BREAK_ON_ERROR(lvl)             if ((lvl)&amp;ACPI_ERROR) acpi_os_breakpoint(&quot;Fatal error encountered&bslash;n&quot;)
macro_line|#else
DECL|macro|BREAK_ON_ERROR
mdefine_line|#define BREAK_ON_ERROR(lvl)
macro_line|#endif
multiline_comment|/*&n; * Master debug print macros&n; * Print iff:&n; *    1) Debug print for the current component is enabled&n; *    2) Debug error level or trace level for the print statement is enabled&n; *&n; */
DECL|macro|TEST_DEBUG_SWITCH
mdefine_line|#define TEST_DEBUG_SWITCH(lvl)          if (((lvl) &amp; acpi_dbg_level) &amp;&amp; (_COMPONENT &amp; acpi_dbg_layer))
DECL|macro|DEBUG_PRINT
mdefine_line|#define DEBUG_PRINT(lvl,fp)             TEST_DEBUG_SWITCH(lvl) {&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_prefix (_THIS_MODULE,__LINE__);&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;BREAK_ON_ERROR(lvl);}
DECL|macro|DEBUG_PRINTP
mdefine_line|#define DEBUG_PRINTP(lvl,fp)            TEST_DEBUG_SWITCH(lvl) {&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_prefix (_THIS_MODULE,__LINE__);&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw (&quot;%s: &quot;,_proc_name);&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;BREAK_ON_ERROR(lvl);}
DECL|macro|DEBUG_PRINT_RAW
mdefine_line|#define DEBUG_PRINT_RAW(lvl,fp)         TEST_DEBUG_SWITCH(lvl) {&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;debug_print_raw PARAM_LIST(fp);}
multiline_comment|/* Assert macros */
DECL|macro|ACPI_ASSERT
mdefine_line|#define ACPI_ASSERT(exp)                if(!(exp)) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_dbg_assert(#exp, __FILE__, __LINE__, &quot;Failed Assertion&quot;)
DECL|macro|DEBUG_ASSERT
mdefine_line|#define DEBUG_ASSERT(msg, exp)          if(!(exp)) &bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;acpi_os_dbg_assert(#exp, __FILE__, __LINE__, msg)
macro_line|#else
multiline_comment|/*&n; * This is the non-debug case -- make everything go away,&n; * leaving no executable debug code!&n; */
DECL|macro|MODULE_NAME
mdefine_line|#define MODULE_NAME(name)
DECL|macro|_THIS_MODULE
mdefine_line|#define _THIS_MODULE &quot;&quot;
DECL|macro|DEBUG_EXEC
mdefine_line|#define DEBUG_EXEC(a)
DECL|macro|NORMAL_EXEC
mdefine_line|#define NORMAL_EXEC(a)                  a;
DECL|macro|DEBUG_DEFINE
mdefine_line|#define DEBUG_DEFINE(a)
DECL|macro|DEBUG_ONLY_MEMBERS
mdefine_line|#define DEBUG_ONLY_MEMBERS(a)
DECL|macro|PROC_NAME
mdefine_line|#define PROC_NAME(a)
DECL|macro|FUNCTION_TRACE
mdefine_line|#define FUNCTION_TRACE(a)
DECL|macro|FUNCTION_TRACE_PTR
mdefine_line|#define FUNCTION_TRACE_PTR(a,b)
DECL|macro|FUNCTION_TRACE_U32
mdefine_line|#define FUNCTION_TRACE_U32(a,b)
DECL|macro|FUNCTION_TRACE_STR
mdefine_line|#define FUNCTION_TRACE_STR(a,b)
DECL|macro|FUNCTION_EXIT
mdefine_line|#define FUNCTION_EXIT
DECL|macro|FUNCTION_STATUS_EXIT
mdefine_line|#define FUNCTION_STATUS_EXIT(s)
DECL|macro|FUNCTION_VALUE_EXIT
mdefine_line|#define FUNCTION_VALUE_EXIT(s)
DECL|macro|DUMP_STACK_ENTRY
mdefine_line|#define DUMP_STACK_ENTRY(a)
DECL|macro|DUMP_OPERANDS
mdefine_line|#define DUMP_OPERANDS(a,b,c,d,e)
DECL|macro|DUMP_ENTRY
mdefine_line|#define DUMP_ENTRY(a,b)
DECL|macro|DUMP_TABLES
mdefine_line|#define DUMP_TABLES(a,b)
DECL|macro|DUMP_PATHNAME
mdefine_line|#define DUMP_PATHNAME(a,b,c,d)
DECL|macro|DUMP_RESOURCE_LIST
mdefine_line|#define DUMP_RESOURCE_LIST(a)
DECL|macro|DEBUG_PRINT
mdefine_line|#define DEBUG_PRINT(l,f)
DECL|macro|DEBUG_PRINTP
mdefine_line|#define DEBUG_PRINTP(l,f)
DECL|macro|DEBUG_PRINT_RAW
mdefine_line|#define DEBUG_PRINT_RAW(l,f)
DECL|macro|BREAK_MSG
mdefine_line|#define BREAK_MSG(a)
DECL|macro|return_VOID
mdefine_line|#define return_VOID                     return
DECL|macro|return_ACPI_STATUS
mdefine_line|#define return_ACPI_STATUS(s)           return(s)
DECL|macro|return_VALUE
mdefine_line|#define return_VALUE(s)                 return(s)
DECL|macro|return_PTR
mdefine_line|#define return_PTR(s)                   return(s)
DECL|macro|ACPI_ASSERT
mdefine_line|#define ACPI_ASSERT(exp)
DECL|macro|DEBUG_ASSERT
mdefine_line|#define DEBUG_ASSERT(msg, exp)
macro_line|#endif
multiline_comment|/*&n; * Some code only gets executed when the debugger is built in.&n; * Note that this is entirely independent of whether the&n; * DEBUG_PRINT stuff (set by ACPI_DEBUG) is on, or not.&n; */
macro_line|#ifdef ENABLE_DEBUGGER
DECL|macro|DEBUGGER_EXEC
mdefine_line|#define DEBUGGER_EXEC(a)                a
macro_line|#else
DECL|macro|DEBUGGER_EXEC
mdefine_line|#define DEBUGGER_EXEC(a)
macro_line|#endif
multiline_comment|/*&n; * For 16-bit code, we want to shrink some things even though&n; * we are using ACPI_DEBUG to get the debug output&n; */
macro_line|#ifdef _IA16
DECL|macro|DEBUG_ONLY_MEMBERS
macro_line|#undef DEBUG_ONLY_MEMBERS
DECL|macro|_VERBOSE_STRUCTURES
macro_line|#undef _VERBOSE_STRUCTURES
DECL|macro|DEBUG_ONLY_MEMBERS
mdefine_line|#define DEBUG_ONLY_MEMBERS(a)
macro_line|#endif
macro_line|#ifdef ACPI_DEBUG
multiline_comment|/*&n; * 1) Set name to blanks&n; * 2) Copy the object name&n; */
DECL|macro|ADD_OBJECT_NAME
mdefine_line|#define ADD_OBJECT_NAME(a,b)            MEMSET (a-&gt;common.name, &squot; &squot;, sizeof (a-&gt;common.name));&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;STRNCPY (a-&gt;common.name, acpi_gbl_ns_type_names[b], sizeof (a-&gt;common.name))
macro_line|#else
DECL|macro|ADD_OBJECT_NAME
mdefine_line|#define ADD_OBJECT_NAME(a,b)
macro_line|#endif
multiline_comment|/*&n; * Memory allocation tracking (DEBUG ONLY)&n; */
macro_line|#ifndef ACPI_DEBUG_TRACK_ALLOCATIONS
DECL|macro|acpi_ut_add_element_to_alloc_list
mdefine_line|#define acpi_ut_add_element_to_alloc_list(a,b,c,d,e,f)
DECL|macro|acpi_ut_delete_element_from_alloc_list
mdefine_line|#define acpi_ut_delete_element_from_alloc_list(a,b,c,d)
DECL|macro|acpi_ut_dump_current_allocations
mdefine_line|#define acpi_ut_dump_current_allocations(a,b)
DECL|macro|acpi_ut_dump_allocation_info
mdefine_line|#define acpi_ut_dump_allocation_info()
DECL|macro|DECREMENT_OBJECT_METRICS
mdefine_line|#define DECREMENT_OBJECT_METRICS(a)
DECL|macro|INCREMENT_OBJECT_METRICS
mdefine_line|#define INCREMENT_OBJECT_METRICS(a)
DECL|macro|INITIALIZE_ALLOCATION_METRICS
mdefine_line|#define INITIALIZE_ALLOCATION_METRICS()
DECL|macro|DECREMENT_NAME_TABLE_METRICS
mdefine_line|#define DECREMENT_NAME_TABLE_METRICS(a)
DECL|macro|INCREMENT_NAME_TABLE_METRICS
mdefine_line|#define INCREMENT_NAME_TABLE_METRICS(a)
macro_line|#else
DECL|macro|INITIALIZE_ALLOCATION_METRICS
mdefine_line|#define INITIALIZE_ALLOCATION_METRICS() &bslash;&n;&t;acpi_gbl_current_object_count = 0; &bslash;&n;&t;acpi_gbl_current_object_size = 0; &bslash;&n;&t;acpi_gbl_running_object_count = 0; &bslash;&n;&t;acpi_gbl_running_object_size = 0; &bslash;&n;&t;acpi_gbl_max_concurrent_object_count = 0; &bslash;&n;&t;acpi_gbl_max_concurrent_object_size = 0; &bslash;&n;&t;acpi_gbl_current_alloc_size = 0; &bslash;&n;&t;acpi_gbl_current_alloc_count = 0; &bslash;&n;&t;acpi_gbl_running_alloc_size = 0; &bslash;&n;&t;acpi_gbl_running_alloc_count = 0; &bslash;&n;&t;acpi_gbl_max_concurrent_alloc_size = 0; &bslash;&n;&t;acpi_gbl_max_concurrent_alloc_count = 0; &bslash;&n;&t;acpi_gbl_current_node_count = 0; &bslash;&n;&t;acpi_gbl_current_node_size = 0; &bslash;&n;&t;acpi_gbl_max_concurrent_node_count = 0
DECL|macro|DECREMENT_OBJECT_METRICS
mdefine_line|#define DECREMENT_OBJECT_METRICS(a) &bslash;&n;&t;acpi_gbl_current_object_count--; &bslash;&n;&t;acpi_gbl_current_object_size -= a
DECL|macro|INCREMENT_OBJECT_METRICS
mdefine_line|#define INCREMENT_OBJECT_METRICS(a) &bslash;&n;&t;acpi_gbl_current_object_count++; &bslash;&n;&t;acpi_gbl_running_object_count++; &bslash;&n;&t;if (acpi_gbl_max_concurrent_object_count &lt; acpi_gbl_current_object_count) &bslash;&n;&t;{ &bslash;&n;&t;&t;acpi_gbl_max_concurrent_object_count = acpi_gbl_current_object_count; &bslash;&n;&t;} &bslash;&n;&t;acpi_gbl_running_object_size += a; &bslash;&n;&t;acpi_gbl_current_object_size += a; &bslash;&n;&t;if (acpi_gbl_max_concurrent_object_size &lt; acpi_gbl_current_object_size) &bslash;&n;&t;{ &bslash;&n;&t;&t;acpi_gbl_max_concurrent_object_size = acpi_gbl_current_object_size; &bslash;&n;&t;}
DECL|macro|DECREMENT_NAME_TABLE_METRICS
mdefine_line|#define DECREMENT_NAME_TABLE_METRICS(a) &bslash;&n;&t;acpi_gbl_current_node_count--; &bslash;&n;&t;acpi_gbl_current_node_size -= (a)
DECL|macro|INCREMENT_NAME_TABLE_METRICS
mdefine_line|#define INCREMENT_NAME_TABLE_METRICS(a) &bslash;&n;&t;acpi_gbl_current_node_count++; &bslash;&n;&t;acpi_gbl_current_node_size+= (a); &bslash;&n;&t;if (acpi_gbl_max_concurrent_node_count &lt; acpi_gbl_current_node_count) &bslash;&n;&t;{ &bslash;&n;&t;&t;acpi_gbl_max_concurrent_node_count = acpi_gbl_current_node_count; &bslash;&n;&t;}
macro_line|#endif /* ACPI_DEBUG_TRACK_ALLOCATIONS */
macro_line|#endif /* ACMACROS_H */
eof
