macro_line|#ifndef __PPC_DIV64
DECL|macro|__PPC_DIV64
mdefine_line|#define __PPC_DIV64
multiline_comment|/* Copyright 2001 PPC64 Team, IBM Corp&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|do_div
mdefine_line|#define do_div(n,base) ({ &bslash;&n;&t;int __res; &bslash;&n;&t;__res = ((unsigned long) (n)) % (unsigned) (base); &bslash;&n;&t;(n) = ((unsigned long) (n)) / (unsigned) (base); &bslash;&n;&t;__res; })
macro_line|#endif
eof
