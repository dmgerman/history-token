multiline_comment|/*&n; * ip22-ksyms.c: IP22 specific exports&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/sgi/mc.h&gt;
macro_line|#include &lt;asm/sgi/hpc3.h&gt;
macro_line|#include &lt;asm/sgi/ioc.h&gt;
macro_line|#include &lt;asm/sgi/ip22.h&gt;
DECL|variable|sgimc
id|EXPORT_SYMBOL
c_func
(paren
id|sgimc
)paren
suffix:semicolon
DECL|variable|hpc3c0
id|EXPORT_SYMBOL
c_func
(paren
id|hpc3c0
)paren
suffix:semicolon
DECL|variable|hpc3c1
id|EXPORT_SYMBOL
c_func
(paren
id|hpc3c1
)paren
suffix:semicolon
DECL|variable|sgioc
id|EXPORT_SYMBOL
c_func
(paren
id|sgioc
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|indy_volume_button
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|variable|indy_volume_button
id|EXPORT_SYMBOL
c_func
(paren
id|indy_volume_button
)paren
suffix:semicolon
DECL|variable|ip22_eeprom_read
id|EXPORT_SYMBOL
c_func
(paren
id|ip22_eeprom_read
)paren
suffix:semicolon
DECL|variable|ip22_nvram_read
id|EXPORT_SYMBOL
c_func
(paren
id|ip22_nvram_read
)paren
suffix:semicolon
eof
