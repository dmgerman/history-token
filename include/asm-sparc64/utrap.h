multiline_comment|/* $Id: utrap.h,v 1.1 1997/10/14 16:21:31 jj Exp $&n; * include/asm-sparc64/utrap.h&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef __ASM_SPARC64_UTRAP_H
DECL|macro|__ASM_SPARC64_UTRAP_H
mdefine_line|#define __ASM_SPARC64_UTRAP_H
DECL|macro|UT_INSTRUCTION_EXCEPTION
mdefine_line|#define UT_INSTRUCTION_EXCEPTION&t;&t;1
DECL|macro|UT_INSTRUCTION_ERROR
mdefine_line|#define UT_INSTRUCTION_ERROR&t;&t;&t;2
DECL|macro|UT_INSTRUCTION_PROTECTION
mdefine_line|#define UT_INSTRUCTION_PROTECTION&t;&t;3
DECL|macro|UT_ILLTRAP_INSTRUCTION
mdefine_line|#define UT_ILLTRAP_INSTRUCTION&t;&t;&t;4
DECL|macro|UT_ILLEGAL_INSTRUCTION
mdefine_line|#define UT_ILLEGAL_INSTRUCTION&t;&t;&t;5
DECL|macro|UT_PRIVILEGED_OPCODE
mdefine_line|#define UT_PRIVILEGED_OPCODE&t;&t;&t;6
DECL|macro|UT_FP_DISABLED
mdefine_line|#define UT_FP_DISABLED&t;&t;&t;&t;7
DECL|macro|UT_FP_EXCEPTION_IEEE_754
mdefine_line|#define UT_FP_EXCEPTION_IEEE_754&t;&t;8
DECL|macro|UT_FP_EXCEPTION_OTHER
mdefine_line|#define UT_FP_EXCEPTION_OTHER&t;&t;&t;9
DECL|macro|UT_TAG_OVERVIEW
mdefine_line|#define UT_TAG_OVERVIEW&t;&t;&t;&t;10
DECL|macro|UT_DIVISION_BY_ZERO
mdefine_line|#define UT_DIVISION_BY_ZERO&t;&t;&t;11
DECL|macro|UT_DATA_EXCEPTION
mdefine_line|#define UT_DATA_EXCEPTION&t;&t;&t;12
DECL|macro|UT_DATA_ERROR
mdefine_line|#define UT_DATA_ERROR&t;&t;&t;&t;13
DECL|macro|UT_DATA_PROTECTION
mdefine_line|#define UT_DATA_PROTECTION&t;&t;&t;14
DECL|macro|UT_MEM_ADDRESS_NOT_ALIGNED
mdefine_line|#define UT_MEM_ADDRESS_NOT_ALIGNED&t;&t;15
DECL|macro|UT_PRIVILEGED_ACTION
mdefine_line|#define UT_PRIVILEGED_ACTION&t;&t;&t;16
DECL|macro|UT_ASYNC_DATA_ERROR
mdefine_line|#define UT_ASYNC_DATA_ERROR&t;&t;&t;17
DECL|macro|UT_TRAP_INSTRUCTION_16
mdefine_line|#define UT_TRAP_INSTRUCTION_16&t;&t;&t;18
DECL|macro|UT_TRAP_INSTRUCTION_17
mdefine_line|#define UT_TRAP_INSTRUCTION_17&t;&t;&t;19
DECL|macro|UT_TRAP_INSTRUCTION_18
mdefine_line|#define UT_TRAP_INSTRUCTION_18&t;&t;&t;20
DECL|macro|UT_TRAP_INSTRUCTION_19
mdefine_line|#define UT_TRAP_INSTRUCTION_19&t;&t;&t;21
DECL|macro|UT_TRAP_INSTRUCTION_20
mdefine_line|#define UT_TRAP_INSTRUCTION_20&t;&t;&t;22
DECL|macro|UT_TRAP_INSTRUCTION_21
mdefine_line|#define UT_TRAP_INSTRUCTION_21&t;&t;&t;23
DECL|macro|UT_TRAP_INSTRUCTION_22
mdefine_line|#define UT_TRAP_INSTRUCTION_22&t;&t;&t;24
DECL|macro|UT_TRAP_INSTRUCTION_23
mdefine_line|#define UT_TRAP_INSTRUCTION_23&t;&t;&t;25
DECL|macro|UT_TRAP_INSTRUCTION_24
mdefine_line|#define UT_TRAP_INSTRUCTION_24&t;&t;&t;26
DECL|macro|UT_TRAP_INSTRUCTION_25
mdefine_line|#define UT_TRAP_INSTRUCTION_25&t;&t;&t;27
DECL|macro|UT_TRAP_INSTRUCTION_26
mdefine_line|#define UT_TRAP_INSTRUCTION_26&t;&t;&t;28
DECL|macro|UT_TRAP_INSTRUCTION_27
mdefine_line|#define UT_TRAP_INSTRUCTION_27&t;&t;&t;29
DECL|macro|UT_TRAP_INSTRUCTION_28
mdefine_line|#define UT_TRAP_INSTRUCTION_28&t;&t;&t;30
DECL|macro|UT_TRAP_INSTRUCTION_29
mdefine_line|#define UT_TRAP_INSTRUCTION_29&t;&t;&t;31
DECL|macro|UT_TRAP_INSTRUCTION_30
mdefine_line|#define UT_TRAP_INSTRUCTION_30&t;&t;&t;32
DECL|macro|UT_TRAP_INSTRUCTION_31
mdefine_line|#define UT_TRAP_INSTRUCTION_31&t;&t;&t;33
DECL|macro|UTH_NOCHANGE
mdefine_line|#define&t;UTH_NOCHANGE&t;&t;&t;&t;(-1)
macro_line|#ifndef __ASSEMBLY__ 
DECL|typedef|utrap_entry_t
r_typedef
r_int
id|utrap_entry_t
suffix:semicolon
DECL|typedef|utrap_handler_t
r_typedef
r_void
op_star
id|utrap_handler_t
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* !(__ASM_SPARC64_PROCESSOR_H) */
eof
