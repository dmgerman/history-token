macro_line|#include &lt;asm/voyager.h&gt;
DECL|macro|VOYAGER_BIOS_INFO
mdefine_line|#define VOYAGER_BIOS_INFO ((struct voyager_bios_info *)(PARAM+0x40))
multiline_comment|/* Hook to call BIOS initialisation function */
multiline_comment|/* for voyager, pass the voyager BIOS/SUS info area to the detection &n; * routines */
DECL|macro|ARCH_SETUP
mdefine_line|#define ARCH_SETUP&t;voyager_detect(VOYAGER_BIOS_INFO);
eof
