multiline_comment|/*&n; * OMAP clock interface&n; *&n; * Copyright (C) 2001 RidgeRun, Inc&n; * Written by Gordon McNutt &lt;gmcnutt@ridgerun.com&gt;&n; * Updated 2004 for Linux 2.6 by Tony Lindgren &lt;tony@atomide.com&gt;&n; *&n; * This program is free software; you can redistribute&t;it and/or modify it&n; * under  the terms of&t;the GNU General&t; Public License as published by the&n; * Free Software Foundation;  either version 2 of the  License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARM_CLOCKS_H
DECL|macro|__ASM_ARM_CLOCKS_H
mdefine_line|#define __ASM_ARM_CLOCKS_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* ARM_CKCTL bit shifts */
DECL|macro|PERDIV
mdefine_line|#define PERDIV&t;&t;&t;0
DECL|macro|LCDDIV
mdefine_line|#define LCDDIV&t;&t;&t;2
DECL|macro|ARMDIV
mdefine_line|#define ARMDIV&t;&t;&t;4
DECL|macro|DSPDIV
mdefine_line|#define DSPDIV&t;&t;&t;6
DECL|macro|TCDIV
mdefine_line|#define TCDIV&t;&t;&t;8
DECL|macro|DSPMMUDIV
mdefine_line|#define DSPMMUDIV&t;&t;10
DECL|macro|ARM_TIMXO
mdefine_line|#define ARM_TIMXO&t;&t;12
DECL|macro|EN_DSPCK
mdefine_line|#define EN_DSPCK&t;&t;13
DECL|macro|ARM_INTHCK_SEL
mdefine_line|#define ARM_INTHCK_SEL&t;&t;14 /* REVISIT: Where is this used? */
multiline_comment|/* ARM_IDLECT1 bit shifts */
DECL|macro|IDLWDT_ARM
mdefine_line|#define IDLWDT_ARM&t;0
DECL|macro|IDLXORP_ARM
mdefine_line|#define IDLXORP_ARM&t;1
DECL|macro|IDLPER_ARM
mdefine_line|#define IDLPER_ARM&t;2
DECL|macro|IDLLCD_ARM
mdefine_line|#define IDLLCD_ARM&t;3
DECL|macro|IDLLB_ARM
mdefine_line|#define IDLLB_ARM&t;4
DECL|macro|IDLHSAB_ARM
mdefine_line|#define IDLHSAB_ARM&t;5
DECL|macro|IDLIF_ARM
mdefine_line|#define IDLIF_ARM&t;6
DECL|macro|IDLDPLL_ARM
mdefine_line|#define IDLDPLL_ARM&t;7
DECL|macro|IDLAPI_ARM
mdefine_line|#define IDLAPI_ARM&t;8
DECL|macro|IDLTIM_ARM
mdefine_line|#define IDLTIM_ARM&t;9
DECL|macro|SETARM_IDLE
mdefine_line|#define SETARM_IDLE&t;11
multiline_comment|/* ARM_IDLECT2 bit shifts */
DECL|macro|EN_WDTCK
mdefine_line|#define EN_WDTCK&t;0
DECL|macro|EN_XORPCK
mdefine_line|#define EN_XORPCK&t;1
DECL|macro|EN_PERCK
mdefine_line|#define EN_PERCK&t;2
DECL|macro|EN_LCDCK
mdefine_line|#define EN_LCDCK&t;3
DECL|macro|EN_LBCK
mdefine_line|#define EN_LBCK&t;&t;4
DECL|macro|EN_HSABCK
mdefine_line|#define EN_HSABCK&t;5
DECL|macro|EN_APICK
mdefine_line|#define EN_APICK&t;6
DECL|macro|EN_TIMCK
mdefine_line|#define EN_TIMCK&t;7
DECL|macro|DMACK_REQ
mdefine_line|#define DMACK_REQ&t;8
DECL|macro|EN_GPIOCK
mdefine_line|#define EN_GPIOCK&t;9
DECL|macro|EN_LBFREECK
mdefine_line|#define EN_LBFREECK&t;10
multiline_comment|/*&n; * OMAP clocks&n; */
r_typedef
r_enum
(brace
multiline_comment|/* Fixed system clock */
DECL|enumerator|OMAP_CLKIN
id|OMAP_CLKIN
op_assign
l_int|0
comma
multiline_comment|/* DPLL1 */
DECL|enumerator|OMAP_CK_GEN1
DECL|enumerator|OMAP_CK_GEN2
DECL|enumerator|OMAP_CK_GEN3
id|OMAP_CK_GEN1
comma
id|OMAP_CK_GEN2
comma
id|OMAP_CK_GEN3
comma
multiline_comment|/* TC usually needs to be checked before anything else */
DECL|enumerator|OMAP_TC_CK
id|OMAP_TC_CK
comma
multiline_comment|/* CLKM1 */
DECL|enumerator|OMAP_ARM_CK
DECL|enumerator|OMAP_MPUPER_CK
DECL|enumerator|OMAP_ARM_GPIO_CK
DECL|enumerator|OMAP_MPUXOR_CK
id|OMAP_ARM_CK
comma
id|OMAP_MPUPER_CK
comma
id|OMAP_ARM_GPIO_CK
comma
id|OMAP_MPUXOR_CK
comma
DECL|enumerator|OMAP_MPUTIM_CK
DECL|enumerator|OMAP_MPUWD_CK
id|OMAP_MPUTIM_CK
comma
id|OMAP_MPUWD_CK
comma
multiline_comment|/* CLKM2 */
DECL|enumerator|OMAP_DSP_CK
DECL|enumerator|OMAP_DSPMMU_CK
id|OMAP_DSP_CK
comma
id|OMAP_DSPMMU_CK
comma
macro_line|#if 0
multiline_comment|/* Accessible only from the dsp */
id|OMAP_DSPPER_CK
comma
id|OMAP_GPIO_CK
comma
id|OMAP_DSPXOR_CK
comma
id|OMAP_DSPTIM_CK
comma
id|OMAP_DSPWD_CK
comma
id|OMAP_UART_CK
comma
macro_line|#endif
multiline_comment|/* CLKM3 */
DECL|enumerator|OMAP_DMA_CK
DECL|enumerator|OMAP_API_CK
DECL|enumerator|OMAP_HSAB_CK
DECL|enumerator|OMAP_LBFREE_CK
id|OMAP_DMA_CK
comma
id|OMAP_API_CK
comma
id|OMAP_HSAB_CK
comma
id|OMAP_LBFREE_CK
comma
DECL|enumerator|OMAP_LB_CK
DECL|enumerator|OMAP_LCD_CK
id|OMAP_LB_CK
comma
id|OMAP_LCD_CK
DECL|typedef|ck_t
)brace
id|ck_t
suffix:semicolon
r_typedef
r_enum
(brace
multiline_comment|/* Reset the MPU */
DECL|enumerator|OMAP_ARM_RST
id|OMAP_ARM_RST
comma
multiline_comment|/* Reset the DSP */
DECL|enumerator|OMAP_DSP_RST
id|OMAP_DSP_RST
comma
multiline_comment|/* Reset priority registers, EMIF config, and MPUI control logic */
DECL|enumerator|OMAP_API_RST
id|OMAP_API_RST
comma
multiline_comment|/* Reset DSP, MPU, and Peripherals */
DECL|enumerator|OMAP_SW_RST
id|OMAP_SW_RST
comma
DECL|typedef|reset_t
)brace
id|reset_t
suffix:semicolon
DECL|macro|OMAP_CK_MIN
mdefine_line|#define OMAP_CK_MIN&t;&t;&t;OMAP_CLKIN
DECL|macro|OMAP_CK_MAX
mdefine_line|#define OMAP_CK_MAX&t;&t;&t;OMAP_LCD_CK
macro_line|#if defined(CONFIG_OMAP_ARM_30MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;30
macro_line|#elif defined(CONFIG_OMAP_ARM_60MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;60
macro_line|#elif defined(CONFIG_OMAP_ARM_96MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;96
macro_line|#elif defined(CONFIG_OMAP_ARM_120MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;120
macro_line|#elif defined(CONFIG_OMAP_ARM_168MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;168
macro_line|#elif defined(CONFIG_OMAP_ARM_182MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;182
macro_line|#elif defined(CONFIG_OMAP_ARM_192MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;192
macro_line|#elif defined(CONFIG_OMAP_ARM_195MHZ)
DECL|macro|OMAP_CK_MAX_RATE
mdefine_line|#define OMAP_CK_MAX_RATE&t;&t;195
macro_line|#endif
DECL|macro|CK_DPLL_MASK
mdefine_line|#define CK_DPLL_MASK&t;&t;&t;0x0fe0
multiline_comment|/* Shared by CK and DSPC */
DECL|macro|MPUI_STROBE_MAX_1509
mdefine_line|#define MPUI_STROBE_MAX_1509&t;&t;24
DECL|macro|MPUI_STROBE_MAX_1510
mdefine_line|#define MPUI_STROBE_MAX_1510&t;&t;30
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Clock interface functions&n; * ----------------------------------------------------------------------------&n; */
multiline_comment|/*  Clock initialization.  */
r_int
id|init_ck
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * For some clocks you have a choice of which &quot;parent&quot; clocks they are derived&n; * from. Use this to select a &quot;parent&quot;. See the platform documentation for&n; * valid combinations.&n; */
r_int
id|ck_can_set_input
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_set_input
c_func
(paren
id|ck_t
id|ck
comma
id|ck_t
id|input
)paren
suffix:semicolon
r_int
id|ck_get_input
c_func
(paren
id|ck_t
id|ck
comma
id|ck_t
op_star
id|input
)paren
suffix:semicolon
multiline_comment|/*&n; * Use this to set a clock rate. If other clocks are derived from this one,&n; * their rates will all change too. If this is a derived clock and I can&squot;t&n; * change it to match your request unless I also change the parent clock, then&n; * tough luck -- I won&squot;t change the parent automatically. I&squot;ll return an error&n; * if I can&squot;t get the clock within 10% of what you want. Otherwise I&squot;ll return&n; * the value I actually set it to. If I have to switch parents to get the rate&n; * then I will do this automatically (since it only affects this clock and its&n; * descendants).&n; */
r_int
id|ck_can_set_rate
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_set_rate
c_func
(paren
id|ck_t
id|ck
comma
r_int
id|val_in_mhz
)paren
suffix:semicolon
r_int
id|ck_get_rate
c_func
(paren
id|ck_t
id|ck
)paren
suffix:semicolon
multiline_comment|/*&n; * Use this to get a bitmap of available rates for the clock. Caller allocates&n; *  the buffer and passes in the length. Clock module fills up to len bytes of&n; *  the buffer &amp; passes back actual bytes used.&n; */
r_int
id|ck_get_rates
c_func
(paren
id|ck_t
id|ck
comma
r_void
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_int
id|ck_valid_rate
c_func
(paren
r_int
id|rate
)paren
suffix:semicolon
multiline_comment|/*&n; * Idle a clock. What happens next depends on the clock ;). For example, if&n; * you idle the ARM_CK you might well end up in sleep mode on some platforms.&n; * If you try to idle a clock that doesn&squot;t support it I&squot;ll return an error.&n; * Note that idling a clock does not always take affect until certain h/w&n; * conditions are met. Consult the platform specs to learn more.&n; */
r_int
id|ck_can_idle
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_idle
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_activate
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_is_idle
c_func
(paren
id|ck_t
)paren
suffix:semicolon
multiline_comment|/*&n; * Enable/disable a clock. I&squot;ll return an error if the h/w doesn&squot;t support it.&n; * If you disable a clock being used by an active device then you probably&n; * just screwed it. YOU are responsible for making sure this doesn&squot;t happen.&n; */
r_int
id|ck_can_disable
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_enable
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_disable
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_int
id|ck_is_enabled
c_func
(paren
id|ck_t
)paren
suffix:semicolon
multiline_comment|/* Enable/reset ARM peripherals (remove/set reset signal) */
r_void
id|ck_enable_peripherals
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ck_reset_peripherals
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Generate/clear a MPU or DSP reset */
r_void
id|ck_generate_reset
c_func
(paren
id|reset_t
id|reset
)paren
suffix:semicolon
r_void
id|ck_release_from_reset
c_func
(paren
id|reset_t
id|reset
)paren
suffix:semicolon
multiline_comment|/* This gets a string representation of the clock&squot;s name. Useful for proc. */
r_char
op_star
id|ck_get_name
c_func
(paren
id|ck_t
)paren
suffix:semicolon
r_extern
r_void
id|start_mputimer1
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
