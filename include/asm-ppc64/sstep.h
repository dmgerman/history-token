multiline_comment|/*&n; * Copyright (C) 2004 Paul Mackerras &lt;paulus@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
r_struct
id|pt_regs
suffix:semicolon
multiline_comment|/*&n; * We don&squot;t allow single-stepping an mtmsrd that would clear&n; * MSR_RI, since that would make the exception unrecoverable.&n; * Since we need to single-step to proceed from a breakpoint,&n; * we don&squot;t allow putting a breakpoint on an mtmsrd instruction.&n; * Similarly we don&squot;t allow breakpoints on rfid instructions.&n; * These macros tell us if an instruction is a mtmsrd or rfid.&n; */
DECL|macro|IS_MTMSRD
mdefine_line|#define IS_MTMSRD(instr)&t;(((instr) &amp; 0xfc0007fe) == 0x7c000164)
DECL|macro|IS_RFID
mdefine_line|#define IS_RFID(instr)&t;&t;(((instr) &amp; 0xfc0007fe) == 0x4c000024)
multiline_comment|/* Emulate instructions that cause a transfer of control. */
r_extern
r_int
id|emulate_step
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|instr
)paren
suffix:semicolon
eof
