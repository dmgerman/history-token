multiline_comment|/* linux/include/asm-arm/arch-s3c2410/hardware.h&n; *&n; * (c) 2003 Simtec Electronics&n; *  Ben Dooks &lt;ben@simtec.co.uk&gt;&n; *&n; * S3C2410 - hardware&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * Changelog:&n; *  21-May-2003 BJD  Created file&n; *  06-Jun-2003 BJD  Added CPU frequency settings&n; *  03-Sep-2003 BJD  Linux v2.6 support&n; *  12-Mar-2004 BJD  Fixed include protection, fixed type of clock vars&n; *  14-Sep-2004 BJD  Added misccr and getpin to gpio&n; *  01-Oct-2004 BJD  Added the new gpio functions&n; *  16-Oct-2004 BJD  Removed the clock variables&n;*/
macro_line|#ifndef __ASM_ARCH_HARDWARE_H
DECL|macro|__ASM_ARCH_HARDWARE_H
mdefine_line|#define __ASM_ARCH_HARDWARE_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* external functions for GPIO support&n; *&n; * These allow various different clients to access the same GPIO&n; * registers without conflicting. If your driver only owns the entire&n; * GPIO register, then it is safe to ioremap/__raw_{read|write} to it.&n;*/
multiline_comment|/* s3c2410_gpio_cfgpin&n; *&n; * set the configuration of the given pin to the value passed.&n; *&n; * eg:&n; *    s3c2410_gpio_cfgpin(S3C2410_GPA0, S3C2410_GPA0_ADDR0);&n; *    s3c2410_gpio_cfgpin(S3C2410_GPE8, S3C2410_GPE8_SDDAT1);&n;*/
r_extern
r_void
id|s3c2410_gpio_cfgpin
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|function
)paren
suffix:semicolon
r_extern
r_int
r_int
id|s3c2410_gpio_getcfg
c_func
(paren
r_int
r_int
id|pin
)paren
suffix:semicolon
multiline_comment|/* s3c2410_gpio_getirq&n; *&n; * turn the given pin number into the corresponding IRQ number&n; *&n; * returns:&n; *&t;&lt; 0 = no interrupt for this pin&n; *&t;&gt;=0 = interrupt number for the pin&n;*/
r_extern
r_int
id|s3c2410_gpio_getirq
c_func
(paren
r_int
r_int
id|pin
)paren
suffix:semicolon
multiline_comment|/* s3c2410_gpio_irqfilter&n; *&n; * set the irq filtering on the given pin&n; *&n; * on = 0 =&gt; disable filtering&n; *      1 =&gt; enable filtering&n; *&n; * config = S3C2410_EINTFLT_PCLK or S3C2410_EINTFLT_EXTCLK orred with&n; *          width of filter (0 through 63)&n; *&n; *&n;*/
r_extern
r_int
id|s3c2410_gpio_irqfilter
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|on
comma
r_int
r_int
id|config
)paren
suffix:semicolon
multiline_comment|/* s3c2410_gpio_pullup&n; *&n; * configure the pull-up control on the given pin&n; *&n; * to = 1 =&gt; disable the pull-up&n; *      0 =&gt; enable the pull-up&n; *&n; * eg;&n; *&n; *   s3c2410_gpio_pullup(S3C2410_GPB0, 0);&n; *   s3c2410_gpio_pullup(S3C2410_GPE8, 0);&n;*/
r_extern
r_void
id|s3c2410_gpio_pullup
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|to
)paren
suffix:semicolon
r_extern
r_void
id|s3c2410_gpio_setpin
c_func
(paren
r_int
r_int
id|pin
comma
r_int
r_int
id|to
)paren
suffix:semicolon
r_extern
r_int
r_int
id|s3c2410_gpio_getpin
c_func
(paren
r_int
r_int
id|pin
)paren
suffix:semicolon
r_extern
r_int
r_int
id|s3c2410_modify_misccr
c_func
(paren
r_int
r_int
id|clr
comma
r_int
r_int
id|chg
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#include &lt;asm/sizes.h&gt;
macro_line|#include &lt;asm/arch/map.h&gt;
multiline_comment|/* machine specific hardware definitions should go after this */
multiline_comment|/* currently here until moved into config (todo) */
DECL|macro|CONFIG_NO_MULTIWORD_IO
mdefine_line|#define CONFIG_NO_MULTIWORD_IO
macro_line|#endif /* __ASM_ARCH_HARDWARE_H */
eof
