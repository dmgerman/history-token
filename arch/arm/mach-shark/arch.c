multiline_comment|/*&n; *  linux/arch/arm/mach-shark/arch.c&n; *&n; *  Architecture specific stuff.&n; */
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
r_extern
r_void
id|shark_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|genarch_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|SHARK
comma
l_string|&quot;Shark&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Alexander Schulz&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x08000000
comma
l_int|0x40000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x08003000
)paren
id|MAPIO
c_func
(paren
id|shark_map_io
)paren
id|INITIRQ
c_func
(paren
id|genarch_init_irq
)paren
id|MACHINE_END
eof
