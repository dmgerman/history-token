multiline_comment|/*&n; * Author: Florian Schirmer &lt;jolt@tuxbox.org&gt;&n; *&n; * 2002 (c) Florian Schirmer &lt;jolt@tuxbox.org&gt; This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#ifndef _PPC_SYSLIB_M8XX_WDT_H
DECL|macro|_PPC_SYSLIB_M8XX_WDT_H
mdefine_line|#define _PPC_SYSLIB_M8XX_WDT_H
r_extern
r_void
id|m8xx_wdt_handler_install
c_func
(paren
id|bd_t
op_star
id|binfo
)paren
suffix:semicolon
r_extern
r_int
id|m8xx_wdt_get_timeout
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|m8xx_wdt_reset
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* _PPC_SYSLIB_M8XX_WDT_H */
eof
