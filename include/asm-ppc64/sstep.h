multiline_comment|/*&n; * Copyright (C) 2004 Paul Mackerras &lt;paulus@au.ibm.com&gt;, IBM&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
r_struct
id|pt_regs
suffix:semicolon
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
