multiline_comment|/*&n; *  linux/arch/arm/mach-ebsa110/arch.c&n; *&n; *  Architecture specific fixups.&n; */
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
r_extern
r_void
id|ebsa110_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ebsa110_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|EBSA110
comma
l_string|&quot;EBSA110&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Russell King&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x00000000
comma
l_int|0xe0000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000400
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|0
)paren
id|DISABLE_PARPORT
c_func
(paren
l_int|2
)paren
id|SOFT_REBOOT
id|MAPIO
c_func
(paren
id|ebsa110_map_io
)paren
id|INITIRQ
c_func
(paren
id|ebsa110_init_irq
)paren
id|MACHINE_END
eof
