multiline_comment|/*&n; * linux/arch/arm/mach-footbridge/personal.c&n; *&n; * Personal server (Skiff) machine fixup&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &quot;common.h&quot;
id|MACHINE_START
c_func
(paren
id|PERSONAL_SERVER
comma
l_string|&quot;Compaq-PersonalServer&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Jamey Hicks / George France&quot;
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
