multiline_comment|/*&n; * Kernel Debugger Architecture Dependent POD functions.&n; *&n; * Copyright (C) 1999-2003 Silicon Graphics, Inc.  All Rights Reserved&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of version 2 of the GNU General Public License&n; * as published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it would be useful, but&n; * WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.&n; *&n; * Further, this software is distributed without any warranty that it is&n; * free of the rightful claim of any third person regarding infringement&n; * or the like.  Any license provided herein, whether implied or&n; * otherwise, applies only to this software file.  Patent licenses, if&n; * any, provided herein do not apply to combinations of this program with&n; * other software, or any other product whatsoever.&n; *&n; * You should have received a copy of the GNU General Public&n; * License along with this program; if not, write the Free Software&n; * Foundation, Inc., 59 Temple Place - Suite 330, Boston MA 02111-1307, USA.&n; *&n; * Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,&n; * Mountain View, CA  94043, or:&n; *&n; * http://www.sgi.com&n; *&n; * For further information regarding this notice, see:&n; *&n; * http://oss.sgi.com/projects/GenInfo/NoticeExplan&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kdb.h&gt;
singleline_comment|//#include &lt;linux/kdbprivate.h&gt;
multiline_comment|/**&n; * kdba_io - enter POD mode from kdb&n; * @argc: arg count&n; * @argv: arg values&n; * @envp: kdb env. vars&n; * @regs: current register state&n; *&n; * Enter POD mode from kdb using SGI SN specific SAL function call.&n; */
r_static
r_int
DECL|function|kdba_io
id|kdba_io
c_func
(paren
r_int
id|argc
comma
r_const
r_char
op_star
op_star
id|argv
comma
r_const
r_char
op_star
op_star
id|envp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|kdb_printf
c_func
(paren
l_string|&quot;kdba_io entered with addr 0x%p&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|regs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * kdba_io_init - register &squot;io&squot; command with kdb&n; *&n; * Register the &squot;io&squot; command with kdb at load time.&n; */
r_void
DECL|function|kdba_io_init
id|kdba_io_init
c_func
(paren
r_void
)paren
(brace
id|kdb_register
c_func
(paren
l_string|&quot;io&quot;
comma
id|kdba_io
comma
l_string|&quot;&lt;vaddr&gt;&quot;
comma
l_string|&quot;Display IO Contents&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * kdba_io_exit - unregister the &squot;io&squot; command&n; *&n; * Tell kdb that the &squot;io&squot; command is no longer available.&n; */
r_static
r_void
id|__exit
DECL|function|kdba_exit
id|kdba_exit
c_func
(paren
r_void
)paren
(brace
id|kdb_unregister
c_func
(paren
l_string|&quot;io&quot;
)paren
suffix:semicolon
)brace
eof
