multiline_comment|/*&n; * &t;w1_log.h&n; *&n; * Copyright (c) 2004 Evgeniy Polyakov &lt;johnpol@2ka.mipt.ru&gt;&n; * &n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#ifndef __W1_LOG_H
DECL|macro|__W1_LOG_H
mdefine_line|#define __W1_LOG_H
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#ifdef W1_DEBUG
DECL|macro|assert
macro_line|#  define assert(expr) do {} while (0)
macro_line|#else
DECL|macro|assert
macro_line|#  define assert(expr) &bslash;&n;        if(unlikely(!(expr))) {&t;&t;&t;&t;        &bslash;&n;        printk(KERN_ERR &quot;Assertion failed! %s,%s,%s,line=%d&bslash;n&quot;,&t;&bslash;&n;        #expr,__FILE__,__FUNCTION__,__LINE__);&t;&t;        &bslash;&n;        }
macro_line|#endif
macro_line|#endif /* __W1_LOG_H */
eof
