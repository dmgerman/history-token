multiline_comment|/*&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 2001 Silicon Graphics, Inc.  All rights reserved.&n;*/
macro_line|#ifndef _ASM_IA64_SN_NAG_H
DECL|macro|_ASM_IA64_SN_NAG_H
mdefine_line|#define _ASM_IA64_SN_NAG_H
DECL|macro|NAG
mdefine_line|#define NAG(mesg...) &bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;static unsigned int how_broken = 1;&t;&t;&t;&t;&t;&bslash;&n;&t;static unsigned int threshold = 1;&t;&t;&t;&t;&t;&bslash;&n;&t;if (how_broken == threshold) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (threshold &lt; 10000)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;threshold *= 10;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if (how_broken &gt; 1)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(KERN_WARNING &quot;%u times: &quot;, how_broken);&t;&t;&bslash;&n;&t;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;printk(KERN_WARNING);&t;&t;&t;&t;&t;&bslash;&n;&t;&t;printk(mesg);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;how_broken++;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* _ASM_IA64_SN_NAG_H */
eof
