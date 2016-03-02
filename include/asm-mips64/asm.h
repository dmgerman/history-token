multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997, 1999, 2001 by Ralf Baechle&n; * Copyright (C) 1999 by Silicon Graphics, Inc.&n; * Copyright (C) 2001 MIPS Technologies, Inc.&n; * Copyright (C) 2002  Maciej W. Rozycki&n; *&n; * Some useful macros for MIPS assembler code&n; *&n; * Some of the routines below contain useless nops that will be optimized&n; * away by gas in -O mode. These nops are however required to fill delay&n; * slots in noreorder mode.&n; */
macro_line|#ifndef&t;__ASM_ASM_H
DECL|macro|__ASM_ASM_H
mdefine_line|#define&t;__ASM_ASM_H
macro_line|#include &lt;asm/sgidefs.h&gt;
multiline_comment|/*&n; * PIC specific declarations&n; * Not used for the kernel but here seems to be the right place.&n; */
macro_line|#ifdef __PIC__
DECL|macro|CPRESTORE
mdefine_line|#define CPRESTORE(register)                             &bslash;&n;&t;&t;.cprestore register
DECL|macro|CPADD
mdefine_line|#define CPADD(register)                                 &bslash;&n;&t;&t;.cpadd&t;register
DECL|macro|CPLOAD
mdefine_line|#define CPLOAD(register)                                &bslash;&n;&t;&t;.cpload&t;register
macro_line|#else
DECL|macro|CPRESTORE
mdefine_line|#define CPRESTORE(register)
DECL|macro|CPADD
mdefine_line|#define CPADD(register)
DECL|macro|CPLOAD
mdefine_line|#define CPLOAD(register)
macro_line|#endif
multiline_comment|/*&n; * LEAF - declare leaf routine&n; */
DECL|macro|LEAF
mdefine_line|#define&t;LEAF(symbol)                                    &bslash;&n;&t;&t;.globl&t;symbol;                         &bslash;&n;&t;&t;.align&t;2;                              &bslash;&n;&t;&t;.type&t;symbol,@function;               &bslash;&n;&t;&t;.ent&t;symbol,0;                       &bslash;&n;symbol:&t;&t;.frame&t;sp,0,ra
multiline_comment|/*&n; * NESTED - declare nested routine entry point&n; */
DECL|macro|NESTED
mdefine_line|#define&t;NESTED(symbol, framesize, rpc)                  &bslash;&n;&t;&t;.globl&t;symbol;                         &bslash;&n;&t;&t;.align&t;2;                              &bslash;&n;&t;&t;.type&t;symbol,@function;               &bslash;&n;&t;&t;.ent&t;symbol,0;                       &bslash;&n;symbol:&t;&t;.frame&t;sp, framesize, rpc
multiline_comment|/*&n; * END - mark end of function&n; */
DECL|macro|END
mdefine_line|#define&t;END(function)                                   &bslash;&n;&t;&t;.end&t;function;&t;&t;        &bslash;&n;&t;&t;.size&t;function,.-function
multiline_comment|/*&n; * EXPORT - export definition of symbol&n; */
DECL|macro|EXPORT
mdefine_line|#define EXPORT(symbol)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.globl&t;symbol;                         &bslash;&n;symbol:
multiline_comment|/*&n; * FEXPORT - export definition of a function symbol&n; */
DECL|macro|FEXPORT
mdefine_line|#define FEXPORT(symbol)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;.globl&t;symbol;&t;&t;&t;&t;&bslash;&n;&t;&t;.type&t;symbol,@function;&t;&t;&bslash;&n;symbol:
multiline_comment|/*&n; * ABS - export absolute symbol&n; */
DECL|macro|ABS
mdefine_line|#define&t;ABS(symbol,value)                               &bslash;&n;&t;&t;.globl&t;symbol;                         &bslash;&n;symbol&t;&t;=&t;value
DECL|macro|PANIC
mdefine_line|#define&t;PANIC(msg)                                      &bslash;&n;&t;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;&t;.set&t;reorder;                        &bslash;&n;&t;&t;PTR_LA&t;a0,8f;                          &bslash;&n;&t;&t;jal&t;panic;                          &bslash;&n;9:&t;&t;b&t;9b;                             &bslash;&n;&t;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;&t;&t;TEXT(msg)
multiline_comment|/*&n; * Print formatted string&n; */
DECL|macro|PRINT
mdefine_line|#define PRINT(string)                                   &bslash;&n;&t;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;&t;.set&t;reorder;                        &bslash;&n;&t;&t;PTR_LA&t;a0,8f;                          &bslash;&n;&t;&t;jal&t;printk;                         &bslash;&n;&t;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;&t;&t;TEXT(string)
DECL|macro|TEXT
mdefine_line|#define&t;TEXT(msg)                                       &bslash;&n;&t;&t;.pushsection .data;&t;&t;&t;&bslash;&n;8:&t;&t;.asciiz&t;msg;                            &bslash;&n;&t;&t;.popsection;
multiline_comment|/*&n; * Build text tables&n; */
DECL|macro|TTABLE
mdefine_line|#define TTABLE(string)                                  &bslash;&n;&t;&t;.pushsection .text;&t;&t;&t;&bslash;&n;&t;&t;.word&t;1f;                             &bslash;&n;&t;&t;.popsection&t;&t;&t;&t;&bslash;&n;&t;&t;.pushsection .data;&t;&t;&t;&bslash;&n;1:&t;&t;.asciiz&t;string;                         &bslash;&n;&t;&t;.popsection
multiline_comment|/*&n; * MIPS IV pref instruction.&n; * Use with .set noreorder only!&n; *&n; * MIPS IV implementations are free to treat this as a nop.  The R5000&n; * is one of them.  So we should have an option not to use this instruction.&n; */
macro_line|#ifdef CONFIG_CPU_HAS_PREFETCH
DECL|macro|PREF
mdefine_line|#define PREF(hint,addr)                                 &bslash;&n;&t;&t;pref&t;hint,addr
DECL|macro|PREFX
mdefine_line|#define PREFX(hint,addr)                                &bslash;&n;&t;&t;prefx&t;hint,addr
macro_line|#else /* !CONFIG_CPU_HAS_PREFETCH */
DECL|macro|PREF
mdefine_line|#define PREF(hint,addr)
DECL|macro|PREFX
mdefine_line|#define PREFX(hint,addr)
macro_line|#endif /* !CONFIG_CPU_HAS_PREFETCH */
multiline_comment|/*&n; * MIPS ISA IV/V movn/movz instructions and equivalents for older CPUs.&n; */
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS1)
DECL|macro|MOVN
mdefine_line|#define MOVN(rd,rs,rt)                                  &bslash;&n;&t;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;&t;.set&t;reorder;&t;&t;&t;&bslash;&n;&t;&t;beqz&t;rt,9f;                          &bslash;&n;&t;&t;move&t;rd,rs;                          &bslash;&n;&t;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;9:
DECL|macro|MOVZ
mdefine_line|#define MOVZ(rd,rs,rt)                                  &bslash;&n;&t;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;&t;.set&t;reorder;&t;&t;&t;&bslash;&n;&t;&t;bnez&t;rt,9f;                          &bslash;&n;&t;&t;move&t;rd,rs;                          &bslash;&n;&t;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;9:
macro_line|#endif /* _MIPS_ISA == _MIPS_ISA_MIPS1 */
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS2) || (_MIPS_ISA == _MIPS_ISA_MIPS3)
DECL|macro|MOVN
mdefine_line|#define MOVN(rd,rs,rt)                                  &bslash;&n;&t;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;&t;.set&t;noreorder;&t;&t;&t;&bslash;&n;&t;&t;bnezl&t;rt,9f;                          &bslash;&n;&t;&t; move&t;rd,rs;                          &bslash;&n;&t;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;9:
DECL|macro|MOVZ
mdefine_line|#define MOVZ(rd,rs,rt)                                  &bslash;&n;&t;&t;.set&t;push;&t;&t;&t;&t;&bslash;&n;&t;&t;.set&t;noreorder;&t;&t;&t;&bslash;&n;&t;&t;beqzl&t;rt,9f;                          &bslash;&n;&t;&t; move&t;rd,rs;                          &bslash;&n;&t;&t;.set&t;pop;&t;&t;&t;&t;&bslash;&n;9:
macro_line|#endif /* (_MIPS_ISA == _MIPS_ISA_MIPS2) || (_MIPS_ISA == _MIPS_ISA_MIPS3) */
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS4 ) || (_MIPS_ISA == _MIPS_ISA_MIPS5) || &bslash;&n;    (_MIPS_ISA == _MIPS_ISA_MIPS32) || (_MIPS_ISA == _MIPS_ISA_MIPS64)
DECL|macro|MOVN
mdefine_line|#define MOVN(rd,rs,rt)                                  &bslash;&n;&t;&t;movn&t;rd,rs,rt
DECL|macro|MOVZ
mdefine_line|#define MOVZ(rd,rs,rt)                                  &bslash;&n;&t;&t;movz&t;rd,rs,rt
macro_line|#endif /* MIPS IV, MIPS V, MIPS32 or MIPS64 */
multiline_comment|/*&n; * Stack alignment&n; */
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS1) || (_MIPS_ISA == _MIPS_ISA_MIPS2) || &bslash;&n;    (_MIPS_ISA == _MIPS_ISA_MIPS32)
DECL|macro|ALSZ
mdefine_line|#define ALSZ&t;7
DECL|macro|ALMASK
mdefine_line|#define ALMASK&t;~7
macro_line|#endif
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS3) || (_MIPS_ISA == _MIPS_ISA_MIPS4) || &bslash;&n;    (_MIPS_ISA == _MIPS_ISA_MIPS5) || (_MIPS_ISA == _MIPS_ISA_MIPS64)
DECL|macro|ALSZ
mdefine_line|#define ALSZ&t;15
DECL|macro|ALMASK
mdefine_line|#define ALMASK&t;~15
macro_line|#endif
multiline_comment|/*&n; * Macros to handle different pointer/register sizes for 32/64-bit code&n; */
multiline_comment|/*&n; * Size of a register&n; */
macro_line|#ifdef __mips64
DECL|macro|SZREG
mdefine_line|#define SZREG&t;8
macro_line|#else
DECL|macro|SZREG
mdefine_line|#define SZREG&t;4
macro_line|#endif
multiline_comment|/*&n; * Use the following macros in assemblercode to load/store registers,&n; * pointers etc.&n; */
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS1) || (_MIPS_ISA == _MIPS_ISA_MIPS2) || &bslash;&n;    (_MIPS_ISA == _MIPS_ISA_MIPS32)
DECL|macro|REG_S
mdefine_line|#define REG_S&t;&t;sw
DECL|macro|REG_L
mdefine_line|#define REG_L&t;&t;lw
DECL|macro|REG_SUBU
mdefine_line|#define REG_SUBU&t;subu
DECL|macro|REG_ADDU
mdefine_line|#define REG_ADDU&t;addu
macro_line|#endif
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS3) || (_MIPS_ISA == _MIPS_ISA_MIPS4) || &bslash;&n;    (_MIPS_ISA == _MIPS_ISA_MIPS5) || (_MIPS_ISA == _MIPS_ISA_MIPS64)
DECL|macro|REG_S
mdefine_line|#define REG_S&t;&t;sd
DECL|macro|REG_L
mdefine_line|#define REG_L&t;&t;ld
DECL|macro|REG_SUBU
mdefine_line|#define REG_SUBU&t;dsubu
DECL|macro|REG_ADDU
mdefine_line|#define REG_ADDU&t;daddu
macro_line|#endif
multiline_comment|/*&n; * How to add/sub/load/store/shift C int variables.&n; */
macro_line|#if (_MIPS_SZINT == 32)
DECL|macro|INT_ADD
mdefine_line|#define INT_ADD&t;&t;add
DECL|macro|INT_ADDU
mdefine_line|#define INT_ADDU&t;addu
DECL|macro|INT_ADDI
mdefine_line|#define INT_ADDI&t;addi
DECL|macro|INT_ADDIU
mdefine_line|#define INT_ADDIU&t;addiu
DECL|macro|INT_SUB
mdefine_line|#define INT_SUB&t;&t;sub
DECL|macro|INT_SUBU
mdefine_line|#define INT_SUBU&t;subu
DECL|macro|INT_L
mdefine_line|#define INT_L&t;&t;lw
DECL|macro|INT_S
mdefine_line|#define INT_S&t;&t;sw
DECL|macro|INT_SLL
mdefine_line|#define INT_SLL&t;&t;sll
DECL|macro|INT_SLLV
mdefine_line|#define INT_SLLV&t;sllv
DECL|macro|INT_SRL
mdefine_line|#define INT_SRL&t;&t;srl
DECL|macro|INT_SRLV
mdefine_line|#define INT_SRLV&t;srlv
DECL|macro|INT_SRA
mdefine_line|#define INT_SRA&t;&t;sra
DECL|macro|INT_SRAV
mdefine_line|#define INT_SRAV&t;srav
macro_line|#endif
macro_line|#if (_MIPS_SZINT == 64)
DECL|macro|INT_ADD
mdefine_line|#define INT_ADD&t;&t;dadd
DECL|macro|INT_ADDU
mdefine_line|#define INT_ADDU&t;daddu
DECL|macro|INT_ADDI
mdefine_line|#define INT_ADDI&t;daddi
DECL|macro|INT_ADDIU
mdefine_line|#define INT_ADDIU&t;daddiu
DECL|macro|INT_SUB
mdefine_line|#define INT_SUB&t;&t;dsub
DECL|macro|INT_SUBU
mdefine_line|#define INT_SUBU&t;dsubu
DECL|macro|INT_L
mdefine_line|#define INT_L&t;&t;ld
DECL|macro|INT_S
mdefine_line|#define INT_S&t;&t;sd
DECL|macro|INT_SLL
mdefine_line|#define INT_SLL&t;&t;dsll
DECL|macro|INT_SLLV
mdefine_line|#define INT_SLLV&t;dsllv
DECL|macro|INT_SRL
mdefine_line|#define INT_SRL&t;&t;dsrl
DECL|macro|INT_SRLV
mdefine_line|#define INT_SRLV&t;dsrlv
DECL|macro|INT_SRA
mdefine_line|#define INT_SRA&t;&t;dsra
DECL|macro|INT_SRAV
mdefine_line|#define INT_SRAV&t;dsrav
macro_line|#endif
multiline_comment|/*&n; * How to add/sub/load/store/shift C long variables.&n; */
macro_line|#if (_MIPS_SZLONG == 32)
DECL|macro|LONG_ADD
mdefine_line|#define LONG_ADD&t;add
DECL|macro|LONG_ADDU
mdefine_line|#define LONG_ADDU&t;addu
DECL|macro|LONG_ADDI
mdefine_line|#define LONG_ADDI&t;addi
DECL|macro|LONG_ADDIU
mdefine_line|#define LONG_ADDIU&t;addiu
DECL|macro|LONG_SUB
mdefine_line|#define LONG_SUB&t;sub
DECL|macro|LONG_SUBU
mdefine_line|#define LONG_SUBU&t;subu
DECL|macro|LONG_L
mdefine_line|#define LONG_L&t;&t;lw
DECL|macro|LONG_S
mdefine_line|#define LONG_S&t;&t;sw
DECL|macro|LONG_SLL
mdefine_line|#define LONG_SLL&t;sll
DECL|macro|LONG_SLLV
mdefine_line|#define LONG_SLLV&t;sllv
DECL|macro|LONG_SRL
mdefine_line|#define LONG_SRL&t;srl
DECL|macro|LONG_SRLV
mdefine_line|#define LONG_SRLV&t;srlv
DECL|macro|LONG_SRA
mdefine_line|#define LONG_SRA&t;sra
DECL|macro|LONG_SRAV
mdefine_line|#define LONG_SRAV&t;srav
macro_line|#endif
macro_line|#if (_MIPS_SZLONG == 64)
DECL|macro|LONG_ADD
mdefine_line|#define LONG_ADD&t;dadd
DECL|macro|LONG_ADDU
mdefine_line|#define LONG_ADDU&t;daddu
DECL|macro|LONG_ADDI
mdefine_line|#define LONG_ADDI&t;daddi
DECL|macro|LONG_ADDIU
mdefine_line|#define LONG_ADDIU&t;daddiu
DECL|macro|LONG_SUB
mdefine_line|#define LONG_SUB&t;dsub
DECL|macro|LONG_SUBU
mdefine_line|#define LONG_SUBU&t;dsubu
DECL|macro|LONG_L
mdefine_line|#define LONG_L&t;&t;ld
DECL|macro|LONG_S
mdefine_line|#define LONG_S&t;&t;sd
DECL|macro|LONG_SLL
mdefine_line|#define LONG_SLL&t;dsll
DECL|macro|LONG_SLLV
mdefine_line|#define LONG_SLLV&t;dsllv
DECL|macro|LONG_SRL
mdefine_line|#define LONG_SRL&t;dsrl
DECL|macro|LONG_SRLV
mdefine_line|#define LONG_SRLV&t;dsrlv
DECL|macro|LONG_SRA
mdefine_line|#define LONG_SRA&t;dsra
DECL|macro|LONG_SRAV
mdefine_line|#define LONG_SRAV&t;dsrav
macro_line|#endif
multiline_comment|/*&n; * How to add/sub/load/store/shift pointers.&n; */
macro_line|#if (_MIPS_SZPTR == 32)
DECL|macro|PTR_ADD
mdefine_line|#define PTR_ADD&t;&t;add
DECL|macro|PTR_ADDU
mdefine_line|#define PTR_ADDU&t;addu
DECL|macro|PTR_ADDI
mdefine_line|#define PTR_ADDI&t;addi
DECL|macro|PTR_ADDIU
mdefine_line|#define PTR_ADDIU&t;addiu
DECL|macro|PTR_SUB
mdefine_line|#define PTR_SUB&t;&t;sub
DECL|macro|PTR_SUBU
mdefine_line|#define PTR_SUBU&t;subu
DECL|macro|PTR_L
mdefine_line|#define PTR_L&t;&t;lw
DECL|macro|PTR_S
mdefine_line|#define PTR_S&t;&t;sw
DECL|macro|PTR_LA
mdefine_line|#define PTR_LA&t;&t;la
DECL|macro|PTR_SLL
mdefine_line|#define PTR_SLL&t;&t;sll
DECL|macro|PTR_SLLV
mdefine_line|#define PTR_SLLV&t;sllv
DECL|macro|PTR_SRL
mdefine_line|#define PTR_SRL&t;&t;srl
DECL|macro|PTR_SRLV
mdefine_line|#define PTR_SRLV&t;srlv
DECL|macro|PTR_SRA
mdefine_line|#define PTR_SRA&t;&t;sra
DECL|macro|PTR_SRAV
mdefine_line|#define PTR_SRAV&t;srav
DECL|macro|PTR_SCALESHIFT
mdefine_line|#define PTR_SCALESHIFT&t;2
DECL|macro|PTR
mdefine_line|#define PTR&t;&t;.word
DECL|macro|PTRSIZE
mdefine_line|#define PTRSIZE&t;&t;4
DECL|macro|PTRLOG
mdefine_line|#define PTRLOG&t;&t;2
macro_line|#endif
macro_line|#if (_MIPS_SZPTR == 64)
DECL|macro|PTR_ADD
mdefine_line|#define PTR_ADD&t;&t;dadd
DECL|macro|PTR_ADDU
mdefine_line|#define PTR_ADDU&t;daddu
DECL|macro|PTR_ADDI
mdefine_line|#define PTR_ADDI&t;daddi
DECL|macro|PTR_ADDIU
mdefine_line|#define PTR_ADDIU&t;daddiu
DECL|macro|PTR_SUB
mdefine_line|#define PTR_SUB&t;&t;dsub
DECL|macro|PTR_SUBU
mdefine_line|#define PTR_SUBU&t;dsubu
DECL|macro|PTR_L
mdefine_line|#define PTR_L&t;&t;ld
DECL|macro|PTR_S
mdefine_line|#define PTR_S&t;&t;sd
DECL|macro|PTR_LA
mdefine_line|#define PTR_LA&t;&t;dla
DECL|macro|PTR_SLL
mdefine_line|#define PTR_SLL&t;&t;dsll
DECL|macro|PTR_SLLV
mdefine_line|#define PTR_SLLV&t;dsllv
DECL|macro|PTR_SRL
mdefine_line|#define PTR_SRL&t;&t;dsrl
DECL|macro|PTR_SRLV
mdefine_line|#define PTR_SRLV&t;dsrlv
DECL|macro|PTR_SRA
mdefine_line|#define PTR_SRA&t;&t;dsra
DECL|macro|PTR_SRAV
mdefine_line|#define PTR_SRAV&t;dsrav
DECL|macro|PTR_SCALESHIFT
mdefine_line|#define PTR_SCALESHIFT&t;3
DECL|macro|PTR
mdefine_line|#define PTR&t;&t;.dword
DECL|macro|PTRSIZE
mdefine_line|#define PTRSIZE&t;&t;8
DECL|macro|PTRLOG
mdefine_line|#define PTRLOG&t;&t;3
macro_line|#endif
multiline_comment|/*&n; * Some cp0 registers were extended to 64bit for MIPS III.&n; */
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS1) || (_MIPS_ISA == _MIPS_ISA_MIPS2) || &bslash;&n;    (_MIPS_ISA == _MIPS_ISA_MIPS32)
DECL|macro|MFC0
mdefine_line|#define MFC0&t;&t;mfc0
DECL|macro|MTC0
mdefine_line|#define MTC0&t;&t;mtc0
macro_line|#endif
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS3) || (_MIPS_ISA == _MIPS_ISA_MIPS4) || &bslash;&n;    (_MIPS_ISA == _MIPS_ISA_MIPS5) || (_MIPS_ISA == _MIPS_ISA_MIPS64)
DECL|macro|MFC0
mdefine_line|#define MFC0&t;&t;dmfc0
DECL|macro|MTC0
mdefine_line|#define MTC0&t;&t;dmtc0
macro_line|#endif
DECL|macro|SSNOP
mdefine_line|#define SSNOP&t;&t;sll zero,zero,1
macro_line|#endif /* __ASM_ASM_H */
eof
