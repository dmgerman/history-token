multiline_comment|/*&n; * linux/arch/arm/mach-footbridge/ebsa285.c&n; *&n; * EBSA285 machine fixup&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &quot;common.h&quot;
id|MACHINE_START
c_func
(paren
id|EBSA285
comma
l_string|&quot;EBSA285&quot;
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
id|DC21285_ARMCSR_BASE
comma
l_int|0xfe000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x00000100
)paren
id|VIDEO
c_func
(paren
l_int|0x000a0000
comma
l_int|0x000bffff
)paren
id|MAPIO
c_func
(paren
id|footbridge_map_io
)paren
id|INITIRQ
c_func
(paren
id|footbridge_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|footbridge_timer
comma
id|MACHINE_END
eof
