multiline_comment|/*&n; * include/asm-ppc/ppc4xx_pic.h&n; *&n; * Interrupt controller driver for PowerPC 4xx-based processors.&n; *&n; * Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; * Eugene Surovegin &lt;eugene.surovegin@zultys.com&gt; or &lt;ebs@ebshome.net&gt;&n; * Copyright (c) 2004 Zultys Technologies&n; *&n; * This program is free software; you can redistribute  it and/or modify it&n; * under  the terms of  the GNU General  Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; */
macro_line|#ifndef&t;__PPC4XX_PIC_H__
DECL|macro|__PPC4XX_PIC_H__
mdefine_line|#define&t;__PPC4XX_PIC_H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
multiline_comment|/* &quot;Fixed&quot; UIC settings (they are chip, not board specific),&n; * e.g. polarity/triggerring for internal interrupt sources.&n; *&n; * Platform port should provide NR_UICS-sized array named ppc4xx_core_uic_cfg&n; * with these &quot;fixed&quot; settings: .polarity contains exact value which will&n; * be written (masked with &quot;ext_irq_mask&quot;) into UICx_PR register,&n; * .triggering - to UICx_TR.&n; *&n; * Settings for external IRQs can be specified separately by the&n; * board support code. In this case properly sized array of unsigned&n; * char named ppc4xx_uic_ext_irq_cfg should be filled with correct&n; * values using IRQ_SENSE_XXXXX and IRQ_POLARITY_XXXXXXX defines.&n; *&n; * If these arrays aren&squot;t provided, UIC initialization code keeps firmware&n; * configuration. Also, ppc4xx_uic_ext_irq_cfg implies ppc4xx_core_uic_cfg&n; * is defined.&n; *&n; * Both ppc4xx_core_uic_cfg and ppc4xx_uic_ext_irq_cfg are declared as&n; * &quot;weak&quot; symbols in ppc4xx_pic.c&n; *&n; */
DECL|struct|ppc4xx_uic_settings
r_struct
id|ppc4xx_uic_settings
(brace
DECL|member|polarity
id|u32
id|polarity
suffix:semicolon
DECL|member|triggering
id|u32
id|triggering
suffix:semicolon
DECL|member|ext_irq_mask
id|u32
id|ext_irq_mask
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|ppc4xx_pic_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __PPC4XX_PIC_H__ */
eof
