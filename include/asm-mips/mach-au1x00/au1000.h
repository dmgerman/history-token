multiline_comment|/*&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;Include file for Alchemy Semiconductor&squot;s Au1k CPU.&n; *&n; * Copyright 2000,2001 MontaVista Software Inc.&n; * Author: MontaVista Software, Inc.&n; *         &t;ppopov@mvista.com or source@mvista.com&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/*&n;  * some definitions add by takuzo@sm.sony.co.jp and sato@sm.sony.co.jp&n;  */
macro_line|#ifndef _AU1000_H_
DECL|macro|_AU1000_H_
mdefine_line|#define _AU1000_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifndef _LANGUAGE_ASSEMBLY
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* cpu pipeline flush */
DECL|function|au_sync
r_void
r_static
r_inline
id|au_sync
c_func
(paren
r_void
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
)brace
DECL|function|au_sync_udelay
r_void
r_static
r_inline
id|au_sync_udelay
c_func
(paren
r_int
id|us
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|udelay
c_func
(paren
id|us
)paren
suffix:semicolon
)brace
DECL|function|au_sync_delay
r_void
r_static
r_inline
id|au_sync_delay
c_func
(paren
r_int
id|ms
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
id|mdelay
c_func
(paren
id|ms
)paren
suffix:semicolon
)brace
DECL|function|au_writeb
r_void
r_static
r_inline
id|au_writeb
c_func
(paren
id|u8
id|val
comma
r_int
id|reg
)paren
(brace
op_star
(paren
r_volatile
id|u8
op_star
)paren
(paren
id|reg
)paren
op_assign
id|val
suffix:semicolon
)brace
DECL|function|au_writew
r_void
r_static
r_inline
id|au_writew
c_func
(paren
id|u16
id|val
comma
r_int
id|reg
)paren
(brace
op_star
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|reg
)paren
op_assign
id|val
suffix:semicolon
)brace
DECL|function|au_writel
r_void
r_static
r_inline
id|au_writel
c_func
(paren
id|u32
id|val
comma
r_int
id|reg
)paren
(brace
op_star
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|reg
)paren
op_assign
id|val
suffix:semicolon
)brace
DECL|function|au_readb
r_static
r_inline
id|u8
id|au_readb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
(paren
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|au_readw
r_static
r_inline
id|u16
id|au_readw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
(paren
op_star
(paren
r_volatile
id|u16
op_star
)paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|au_readl
r_static
r_inline
id|u32
id|au_readl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
(paren
op_star
(paren
r_volatile
id|u32
op_star
)paren
id|port
)paren
suffix:semicolon
)brace
multiline_comment|/* These next three functions should be a generic part of the MIPS&n; * kernel (with the &squot;au_&squot; removed from the name) and selected for&n; * processors that support the instructions.&n; * Taken from PPC tree.  -- Dan&n; */
multiline_comment|/* Return the bit position of the most significant 1 bit in a word */
DECL|function|__ilog2
r_static
id|__inline__
r_int
id|__ilog2
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|lz
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;.set&bslash;tnoreorder&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tnoat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips32&bslash;n&bslash;t&quot;
l_string|&quot;clz&bslash;t%0,%1&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tat&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;treorder&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lz
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
)paren
suffix:semicolon
r_return
l_int|31
op_minus
id|lz
suffix:semicolon
)brace
DECL|function|au_ffz
r_static
id|__inline__
r_int
id|au_ffz
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_if
c_cond
(paren
(paren
id|x
op_assign
op_complement
id|x
)paren
op_eq
l_int|0
)paren
r_return
l_int|32
suffix:semicolon
r_return
id|__ilog2
c_func
(paren
id|x
op_amp
op_minus
id|x
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ffs: find first bit set. This is defined the same way as&n; * the libc and compiler builtin ffs routines, therefore&n; * differs in spirit from the above ffz (man ffs).&n; */
DECL|function|au_ffs
r_static
id|__inline__
r_int
id|au_ffs
c_func
(paren
r_int
id|x
)paren
(brace
r_return
id|__ilog2
c_func
(paren
id|x
op_amp
op_minus
id|x
)paren
op_plus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* arch/mips/au1000/common/clocks.c */
r_extern
r_void
id|set_au1x00_speed
c_func
(paren
r_int
r_int
id|new_freq
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_au1x00_speed
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_au1x00_uart_baud_base
c_func
(paren
r_int
r_int
id|new_baud_base
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_au1x00_uart_baud_base
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_au1x00_lcd_clock
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_au1x00_lcd_clock
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Every board describes its IRQ mapping with this table.&n; */
DECL|struct|au1xxx_irqmap
r_typedef
r_struct
id|au1xxx_irqmap
(brace
DECL|member|im_irq
r_int
id|im_irq
suffix:semicolon
DECL|member|im_type
r_int
id|im_type
suffix:semicolon
DECL|member|im_request
r_int
id|im_request
suffix:semicolon
DECL|typedef|au1xxx_irq_map_t
)brace
id|au1xxx_irq_map_t
suffix:semicolon
multiline_comment|/*&n; * init_IRQ looks for a table with this name.&n; */
r_extern
id|au1xxx_irq_map_t
id|au1xxx_irq_map
(braket
)braket
suffix:semicolon
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
macro_line|#ifdef CONFIG_PM
multiline_comment|/* no CP0 timer irq */
DECL|macro|ALLINTS
mdefine_line|#define ALLINTS (IE_IRQ0 | IE_IRQ1 | IE_IRQ2 | IE_IRQ3 | IE_IRQ4)
macro_line|#else
DECL|macro|ALLINTS
mdefine_line|#define ALLINTS (IE_IRQ0 | IE_IRQ1 | IE_IRQ2 | IE_IRQ3 | IE_IRQ4 | IE_IRQ5)
macro_line|#endif
multiline_comment|/* SDRAM Controller */
macro_line|#if defined(CONFIG_SOC_AU1000) || defined(CONFIG_SOC_AU1500) || defined(CONFIG_SOC_AU1100)
DECL|macro|MEM_SDMODE0
mdefine_line|#define MEM_SDMODE0                0xB4000000
DECL|macro|MEM_SDMODE1
mdefine_line|#define MEM_SDMODE1                0xB4000004
DECL|macro|MEM_SDMODE2
mdefine_line|#define MEM_SDMODE2                0xB4000008
DECL|macro|MEM_SDADDR0
mdefine_line|#define MEM_SDADDR0                0xB400000C
DECL|macro|MEM_SDADDR1
mdefine_line|#define MEM_SDADDR1                0xB4000010
DECL|macro|MEM_SDADDR2
mdefine_line|#define MEM_SDADDR2                0xB4000014
DECL|macro|MEM_SDREFCFG
mdefine_line|#define MEM_SDREFCFG               0xB4000018
DECL|macro|MEM_SDPRECMD
mdefine_line|#define MEM_SDPRECMD               0xB400001C
DECL|macro|MEM_SDAUTOREF
mdefine_line|#define MEM_SDAUTOREF              0xB4000020
DECL|macro|MEM_SDWRMD0
mdefine_line|#define MEM_SDWRMD0                0xB4000024
DECL|macro|MEM_SDWRMD1
mdefine_line|#define MEM_SDWRMD1                0xB4000028
DECL|macro|MEM_SDWRMD2
mdefine_line|#define MEM_SDWRMD2                0xB400002C
DECL|macro|MEM_SDSLEEP
mdefine_line|#define MEM_SDSLEEP                0xB4000030
DECL|macro|MEM_SDSMCKE
mdefine_line|#define MEM_SDSMCKE                0xB4000034
macro_line|#endif
multiline_comment|/* Static Bus Controller */
DECL|macro|MEM_STCFG0
mdefine_line|#define MEM_STCFG0                 0xB4001000
DECL|macro|MEM_STTIME0
mdefine_line|#define MEM_STTIME0                0xB4001004
DECL|macro|MEM_STADDR0
mdefine_line|#define MEM_STADDR0                0xB4001008
DECL|macro|MEM_STCFG1
mdefine_line|#define MEM_STCFG1                 0xB4001010
DECL|macro|MEM_STTIME1
mdefine_line|#define MEM_STTIME1                0xB4001014
DECL|macro|MEM_STADDR1
mdefine_line|#define MEM_STADDR1                0xB4001018
DECL|macro|MEM_STCFG2
mdefine_line|#define MEM_STCFG2                 0xB4001020
DECL|macro|MEM_STTIME2
mdefine_line|#define MEM_STTIME2                0xB4001024
DECL|macro|MEM_STADDR2
mdefine_line|#define MEM_STADDR2                0xB4001028
DECL|macro|MEM_STCFG3
mdefine_line|#define MEM_STCFG3                 0xB4001030
DECL|macro|MEM_STTIME3
mdefine_line|#define MEM_STTIME3                0xB4001034
DECL|macro|MEM_STADDR3
mdefine_line|#define MEM_STADDR3                0xB4001038
macro_line|#if defined(CONFIG_SOC_AU1550) || defined(CONFIG_SOC_AU1200)
DECL|macro|MEM_STNDCTL
mdefine_line|#define MEM_STNDCTL                0xB4001100
DECL|macro|MEM_STSTAT
mdefine_line|#define MEM_STSTAT                 0xB4001104
DECL|macro|MEM_STNAND_CMD
mdefine_line|#define MEM_STNAND_CMD                  (0x0)
DECL|macro|MEM_STNAND_ADDR
mdefine_line|#define MEM_STNAND_ADDR                 (0x4)
DECL|macro|MEM_STNAND_DATA
mdefine_line|#define MEM_STNAND_DATA                (0x20)
macro_line|#endif
multiline_comment|/* Interrupt Controller 0 */
DECL|macro|IC0_CFG0RD
mdefine_line|#define IC0_CFG0RD                 0xB0400040
DECL|macro|IC0_CFG0SET
mdefine_line|#define IC0_CFG0SET                0xB0400040
DECL|macro|IC0_CFG0CLR
mdefine_line|#define IC0_CFG0CLR                0xB0400044
DECL|macro|IC0_CFG1RD
mdefine_line|#define IC0_CFG1RD                 0xB0400048
DECL|macro|IC0_CFG1SET
mdefine_line|#define IC0_CFG1SET                0xB0400048
DECL|macro|IC0_CFG1CLR
mdefine_line|#define IC0_CFG1CLR                0xB040004C
DECL|macro|IC0_CFG2RD
mdefine_line|#define IC0_CFG2RD                 0xB0400050
DECL|macro|IC0_CFG2SET
mdefine_line|#define IC0_CFG2SET                0xB0400050
DECL|macro|IC0_CFG2CLR
mdefine_line|#define IC0_CFG2CLR                0xB0400054
DECL|macro|IC0_REQ0INT
mdefine_line|#define IC0_REQ0INT                0xB0400054
DECL|macro|IC0_SRCRD
mdefine_line|#define IC0_SRCRD                  0xB0400058
DECL|macro|IC0_SRCSET
mdefine_line|#define IC0_SRCSET                 0xB0400058
DECL|macro|IC0_SRCCLR
mdefine_line|#define IC0_SRCCLR                 0xB040005C
DECL|macro|IC0_REQ1INT
mdefine_line|#define IC0_REQ1INT                0xB040005C
DECL|macro|IC0_ASSIGNRD
mdefine_line|#define IC0_ASSIGNRD               0xB0400060
DECL|macro|IC0_ASSIGNSET
mdefine_line|#define IC0_ASSIGNSET              0xB0400060
DECL|macro|IC0_ASSIGNCLR
mdefine_line|#define IC0_ASSIGNCLR              0xB0400064
DECL|macro|IC0_WAKERD
mdefine_line|#define IC0_WAKERD                 0xB0400068
DECL|macro|IC0_WAKESET
mdefine_line|#define IC0_WAKESET                0xB0400068
DECL|macro|IC0_WAKECLR
mdefine_line|#define IC0_WAKECLR                0xB040006C
DECL|macro|IC0_MASKRD
mdefine_line|#define IC0_MASKRD                 0xB0400070
DECL|macro|IC0_MASKSET
mdefine_line|#define IC0_MASKSET                0xB0400070
DECL|macro|IC0_MASKCLR
mdefine_line|#define IC0_MASKCLR                0xB0400074
DECL|macro|IC0_RISINGRD
mdefine_line|#define IC0_RISINGRD               0xB0400078
DECL|macro|IC0_RISINGCLR
mdefine_line|#define IC0_RISINGCLR              0xB0400078
DECL|macro|IC0_FALLINGRD
mdefine_line|#define IC0_FALLINGRD              0xB040007C
DECL|macro|IC0_FALLINGCLR
mdefine_line|#define IC0_FALLINGCLR             0xB040007C
DECL|macro|IC0_TESTBIT
mdefine_line|#define IC0_TESTBIT                0xB0400080
multiline_comment|/* Interrupt Controller 1 */
DECL|macro|IC1_CFG0RD
mdefine_line|#define IC1_CFG0RD                 0xB1800040
DECL|macro|IC1_CFG0SET
mdefine_line|#define IC1_CFG0SET                0xB1800040
DECL|macro|IC1_CFG0CLR
mdefine_line|#define IC1_CFG0CLR                0xB1800044
DECL|macro|IC1_CFG1RD
mdefine_line|#define IC1_CFG1RD                 0xB1800048
DECL|macro|IC1_CFG1SET
mdefine_line|#define IC1_CFG1SET                0xB1800048
DECL|macro|IC1_CFG1CLR
mdefine_line|#define IC1_CFG1CLR                0xB180004C
DECL|macro|IC1_CFG2RD
mdefine_line|#define IC1_CFG2RD                 0xB1800050
DECL|macro|IC1_CFG2SET
mdefine_line|#define IC1_CFG2SET                0xB1800050
DECL|macro|IC1_CFG2CLR
mdefine_line|#define IC1_CFG2CLR                0xB1800054
DECL|macro|IC1_REQ0INT
mdefine_line|#define IC1_REQ0INT                0xB1800054
DECL|macro|IC1_SRCRD
mdefine_line|#define IC1_SRCRD                  0xB1800058
DECL|macro|IC1_SRCSET
mdefine_line|#define IC1_SRCSET                 0xB1800058
DECL|macro|IC1_SRCCLR
mdefine_line|#define IC1_SRCCLR                 0xB180005C
DECL|macro|IC1_REQ1INT
mdefine_line|#define IC1_REQ1INT                0xB180005C
DECL|macro|IC1_ASSIGNRD
mdefine_line|#define IC1_ASSIGNRD               0xB1800060
DECL|macro|IC1_ASSIGNSET
mdefine_line|#define IC1_ASSIGNSET              0xB1800060
DECL|macro|IC1_ASSIGNCLR
mdefine_line|#define IC1_ASSIGNCLR              0xB1800064
DECL|macro|IC1_WAKERD
mdefine_line|#define IC1_WAKERD                 0xB1800068
DECL|macro|IC1_WAKESET
mdefine_line|#define IC1_WAKESET                0xB1800068
DECL|macro|IC1_WAKECLR
mdefine_line|#define IC1_WAKECLR                0xB180006C
DECL|macro|IC1_MASKRD
mdefine_line|#define IC1_MASKRD                 0xB1800070
DECL|macro|IC1_MASKSET
mdefine_line|#define IC1_MASKSET                0xB1800070
DECL|macro|IC1_MASKCLR
mdefine_line|#define IC1_MASKCLR                0xB1800074
DECL|macro|IC1_RISINGRD
mdefine_line|#define IC1_RISINGRD               0xB1800078
DECL|macro|IC1_RISINGCLR
mdefine_line|#define IC1_RISINGCLR              0xB1800078
DECL|macro|IC1_FALLINGRD
mdefine_line|#define IC1_FALLINGRD              0xB180007C
DECL|macro|IC1_FALLINGCLR
mdefine_line|#define IC1_FALLINGCLR             0xB180007C
DECL|macro|IC1_TESTBIT
mdefine_line|#define IC1_TESTBIT                0xB1800080
multiline_comment|/* Interrupt Configuration Modes */
DECL|macro|INTC_INT_DISABLED
mdefine_line|#define INTC_INT_DISABLED                0
DECL|macro|INTC_INT_RISE_EDGE
mdefine_line|#define INTC_INT_RISE_EDGE             0x1
DECL|macro|INTC_INT_FALL_EDGE
mdefine_line|#define INTC_INT_FALL_EDGE             0x2
DECL|macro|INTC_INT_RISE_AND_FALL_EDGE
mdefine_line|#define INTC_INT_RISE_AND_FALL_EDGE    0x3
DECL|macro|INTC_INT_HIGH_LEVEL
mdefine_line|#define INTC_INT_HIGH_LEVEL            0x5
DECL|macro|INTC_INT_LOW_LEVEL
mdefine_line|#define INTC_INT_LOW_LEVEL             0x6
DECL|macro|INTC_INT_HIGH_AND_LOW_LEVEL
mdefine_line|#define INTC_INT_HIGH_AND_LOW_LEVEL    0x7
multiline_comment|/* Interrupt Numbers */
multiline_comment|/* Au1000 */
macro_line|#ifdef CONFIG_SOC_AU1000
DECL|macro|AU1000_UART0_INT
mdefine_line|#define AU1000_UART0_INT          0
DECL|macro|AU1000_UART1_INT
mdefine_line|#define AU1000_UART1_INT          1 /* au1000 */
DECL|macro|AU1000_UART2_INT
mdefine_line|#define AU1000_UART2_INT          2 /* au1000 */
DECL|macro|AU1000_UART3_INT
mdefine_line|#define AU1000_UART3_INT          3
DECL|macro|AU1000_SSI0_INT
mdefine_line|#define AU1000_SSI0_INT           4 /* au1000 */
DECL|macro|AU1000_SSI1_INT
mdefine_line|#define AU1000_SSI1_INT           5 /* au1000 */
DECL|macro|AU1000_DMA_INT_BASE
mdefine_line|#define AU1000_DMA_INT_BASE       6
DECL|macro|AU1000_TOY_INT
mdefine_line|#define AU1000_TOY_INT            14
DECL|macro|AU1000_TOY_MATCH0_INT
mdefine_line|#define AU1000_TOY_MATCH0_INT     15
DECL|macro|AU1000_TOY_MATCH1_INT
mdefine_line|#define AU1000_TOY_MATCH1_INT     16
DECL|macro|AU1000_TOY_MATCH2_INT
mdefine_line|#define AU1000_TOY_MATCH2_INT     17
DECL|macro|AU1000_RTC_INT
mdefine_line|#define AU1000_RTC_INT            18
DECL|macro|AU1000_RTC_MATCH0_INT
mdefine_line|#define AU1000_RTC_MATCH0_INT     19
DECL|macro|AU1000_RTC_MATCH1_INT
mdefine_line|#define AU1000_RTC_MATCH1_INT     20
DECL|macro|AU1000_RTC_MATCH2_INT
mdefine_line|#define AU1000_RTC_MATCH2_INT     21
DECL|macro|AU1000_IRDA_TX_INT
mdefine_line|#define AU1000_IRDA_TX_INT        22 /* au1000 */
DECL|macro|AU1000_IRDA_RX_INT
mdefine_line|#define AU1000_IRDA_RX_INT        23 /* au1000 */
DECL|macro|AU1000_USB_DEV_REQ_INT
mdefine_line|#define AU1000_USB_DEV_REQ_INT    24
DECL|macro|AU1000_USB_DEV_SUS_INT
mdefine_line|#define AU1000_USB_DEV_SUS_INT    25
DECL|macro|AU1000_USB_HOST_INT
mdefine_line|#define AU1000_USB_HOST_INT       26
DECL|macro|AU1000_ACSYNC_INT
mdefine_line|#define AU1000_ACSYNC_INT         27
DECL|macro|AU1000_MAC0_DMA_INT
mdefine_line|#define AU1000_MAC0_DMA_INT       28
DECL|macro|AU1000_MAC1_DMA_INT
mdefine_line|#define AU1000_MAC1_DMA_INT       29
DECL|macro|AU1000_I2S_UO_INT
mdefine_line|#define AU1000_I2S_UO_INT         30 /* au1000 */
DECL|macro|AU1000_AC97C_INT
mdefine_line|#define AU1000_AC97C_INT          31
DECL|macro|AU1000_GPIO_0
mdefine_line|#define AU1000_GPIO_0             32
DECL|macro|AU1000_GPIO_1
mdefine_line|#define AU1000_GPIO_1             33
DECL|macro|AU1000_GPIO_2
mdefine_line|#define AU1000_GPIO_2             34
DECL|macro|AU1000_GPIO_3
mdefine_line|#define AU1000_GPIO_3             35
DECL|macro|AU1000_GPIO_4
mdefine_line|#define AU1000_GPIO_4             36
DECL|macro|AU1000_GPIO_5
mdefine_line|#define AU1000_GPIO_5             37
DECL|macro|AU1000_GPIO_6
mdefine_line|#define AU1000_GPIO_6             38
DECL|macro|AU1000_GPIO_7
mdefine_line|#define AU1000_GPIO_7             39
DECL|macro|AU1000_GPIO_8
mdefine_line|#define AU1000_GPIO_8             40
DECL|macro|AU1000_GPIO_9
mdefine_line|#define AU1000_GPIO_9             41
DECL|macro|AU1000_GPIO_10
mdefine_line|#define AU1000_GPIO_10            42
DECL|macro|AU1000_GPIO_11
mdefine_line|#define AU1000_GPIO_11            43
DECL|macro|AU1000_GPIO_12
mdefine_line|#define AU1000_GPIO_12            44
DECL|macro|AU1000_GPIO_13
mdefine_line|#define AU1000_GPIO_13            45
DECL|macro|AU1000_GPIO_14
mdefine_line|#define AU1000_GPIO_14            46
DECL|macro|AU1000_GPIO_15
mdefine_line|#define AU1000_GPIO_15            47
DECL|macro|AU1000_GPIO_16
mdefine_line|#define AU1000_GPIO_16            48
DECL|macro|AU1000_GPIO_17
mdefine_line|#define AU1000_GPIO_17            49
DECL|macro|AU1000_GPIO_18
mdefine_line|#define AU1000_GPIO_18            50
DECL|macro|AU1000_GPIO_19
mdefine_line|#define AU1000_GPIO_19            51
DECL|macro|AU1000_GPIO_20
mdefine_line|#define AU1000_GPIO_20            52
DECL|macro|AU1000_GPIO_21
mdefine_line|#define AU1000_GPIO_21            53
DECL|macro|AU1000_GPIO_22
mdefine_line|#define AU1000_GPIO_22            54
DECL|macro|AU1000_GPIO_23
mdefine_line|#define AU1000_GPIO_23            55
DECL|macro|AU1000_GPIO_24
mdefine_line|#define AU1000_GPIO_24            56
DECL|macro|AU1000_GPIO_25
mdefine_line|#define AU1000_GPIO_25            57
DECL|macro|AU1000_GPIO_26
mdefine_line|#define AU1000_GPIO_26            58
DECL|macro|AU1000_GPIO_27
mdefine_line|#define AU1000_GPIO_27            59
DECL|macro|AU1000_GPIO_28
mdefine_line|#define AU1000_GPIO_28            60
DECL|macro|AU1000_GPIO_29
mdefine_line|#define AU1000_GPIO_29            61
DECL|macro|AU1000_GPIO_30
mdefine_line|#define AU1000_GPIO_30            62
DECL|macro|AU1000_GPIO_31
mdefine_line|#define AU1000_GPIO_31            63
DECL|macro|UART0_ADDR
mdefine_line|#define UART0_ADDR                0xB1100000
DECL|macro|UART1_ADDR
mdefine_line|#define UART1_ADDR                0xB1200000
DECL|macro|UART2_ADDR
mdefine_line|#define UART2_ADDR                0xB1300000
DECL|macro|UART3_ADDR
mdefine_line|#define UART3_ADDR                0xB1400000
DECL|macro|USB_OHCI_BASE
mdefine_line|#define USB_OHCI_BASE             0x10100000 
singleline_comment|// phys addr for ioremap
DECL|macro|USB_HOST_CONFIG
mdefine_line|#define USB_HOST_CONFIG           0xB017fffc
DECL|macro|AU1000_ETH0_BASE
mdefine_line|#define AU1000_ETH0_BASE      0xB0500000
DECL|macro|AU1000_ETH1_BASE
mdefine_line|#define AU1000_ETH1_BASE      0xB0510000
DECL|macro|AU1000_MAC0_ENABLE
mdefine_line|#define AU1000_MAC0_ENABLE       0xB0520000
DECL|macro|AU1000_MAC1_ENABLE
mdefine_line|#define AU1000_MAC1_ENABLE       0xB0520004
DECL|macro|NUM_ETH_INTERFACES
mdefine_line|#define NUM_ETH_INTERFACES 2
macro_line|#endif 
singleline_comment|// CONFIG_SOC_AU1000
multiline_comment|/* Au1500 */
macro_line|#ifdef CONFIG_SOC_AU1500
DECL|macro|AU1500_UART0_INT
mdefine_line|#define AU1500_UART0_INT          0
DECL|macro|AU1000_PCI_INTA
mdefine_line|#define AU1000_PCI_INTA           1 /* au1500 */
DECL|macro|AU1000_PCI_INTB
mdefine_line|#define AU1000_PCI_INTB           2 /* au1500 */
DECL|macro|AU1500_UART3_INT
mdefine_line|#define AU1500_UART3_INT          3
DECL|macro|AU1000_PCI_INTC
mdefine_line|#define AU1000_PCI_INTC           4 /* au1500 */
DECL|macro|AU1000_PCI_INTD
mdefine_line|#define AU1000_PCI_INTD           5 /* au1500 */
DECL|macro|AU1000_DMA_INT_BASE
mdefine_line|#define AU1000_DMA_INT_BASE       6
DECL|macro|AU1000_TOY_INT
mdefine_line|#define AU1000_TOY_INT            14
DECL|macro|AU1000_TOY_MATCH0_INT
mdefine_line|#define AU1000_TOY_MATCH0_INT     15
DECL|macro|AU1000_TOY_MATCH1_INT
mdefine_line|#define AU1000_TOY_MATCH1_INT     16
DECL|macro|AU1000_TOY_MATCH2_INT
mdefine_line|#define AU1000_TOY_MATCH2_INT     17
DECL|macro|AU1000_RTC_INT
mdefine_line|#define AU1000_RTC_INT            18
DECL|macro|AU1000_RTC_MATCH0_INT
mdefine_line|#define AU1000_RTC_MATCH0_INT     19
DECL|macro|AU1000_RTC_MATCH1_INT
mdefine_line|#define AU1000_RTC_MATCH1_INT     20
DECL|macro|AU1000_RTC_MATCH2_INT
mdefine_line|#define AU1000_RTC_MATCH2_INT     21
DECL|macro|AU1500_PCI_ERR_INT
mdefine_line|#define AU1500_PCI_ERR_INT        22
DECL|macro|AU1000_USB_DEV_REQ_INT
mdefine_line|#define AU1000_USB_DEV_REQ_INT    24
DECL|macro|AU1000_USB_DEV_SUS_INT
mdefine_line|#define AU1000_USB_DEV_SUS_INT    25
DECL|macro|AU1000_USB_HOST_INT
mdefine_line|#define AU1000_USB_HOST_INT       26
DECL|macro|AU1000_ACSYNC_INT
mdefine_line|#define AU1000_ACSYNC_INT         27
DECL|macro|AU1500_MAC0_DMA_INT
mdefine_line|#define AU1500_MAC0_DMA_INT       28
DECL|macro|AU1500_MAC1_DMA_INT
mdefine_line|#define AU1500_MAC1_DMA_INT       29
DECL|macro|AU1000_AC97C_INT
mdefine_line|#define AU1000_AC97C_INT          31
DECL|macro|AU1000_GPIO_0
mdefine_line|#define AU1000_GPIO_0             32
DECL|macro|AU1000_GPIO_1
mdefine_line|#define AU1000_GPIO_1             33
DECL|macro|AU1000_GPIO_2
mdefine_line|#define AU1000_GPIO_2             34
DECL|macro|AU1000_GPIO_3
mdefine_line|#define AU1000_GPIO_3             35
DECL|macro|AU1000_GPIO_4
mdefine_line|#define AU1000_GPIO_4             36
DECL|macro|AU1000_GPIO_5
mdefine_line|#define AU1000_GPIO_5             37
DECL|macro|AU1000_GPIO_6
mdefine_line|#define AU1000_GPIO_6             38
DECL|macro|AU1000_GPIO_7
mdefine_line|#define AU1000_GPIO_7             39
DECL|macro|AU1000_GPIO_8
mdefine_line|#define AU1000_GPIO_8             40
DECL|macro|AU1000_GPIO_9
mdefine_line|#define AU1000_GPIO_9             41
DECL|macro|AU1000_GPIO_10
mdefine_line|#define AU1000_GPIO_10            42
DECL|macro|AU1000_GPIO_11
mdefine_line|#define AU1000_GPIO_11            43
DECL|macro|AU1000_GPIO_12
mdefine_line|#define AU1000_GPIO_12            44
DECL|macro|AU1000_GPIO_13
mdefine_line|#define AU1000_GPIO_13            45
DECL|macro|AU1000_GPIO_14
mdefine_line|#define AU1000_GPIO_14            46
DECL|macro|AU1000_GPIO_15
mdefine_line|#define AU1000_GPIO_15            47
DECL|macro|AU1500_GPIO_200
mdefine_line|#define AU1500_GPIO_200           48
DECL|macro|AU1500_GPIO_201
mdefine_line|#define AU1500_GPIO_201           49
DECL|macro|AU1500_GPIO_202
mdefine_line|#define AU1500_GPIO_202           50
DECL|macro|AU1500_GPIO_203
mdefine_line|#define AU1500_GPIO_203           51
DECL|macro|AU1500_GPIO_20
mdefine_line|#define AU1500_GPIO_20            52
DECL|macro|AU1500_GPIO_204
mdefine_line|#define AU1500_GPIO_204           53
DECL|macro|AU1500_GPIO_205
mdefine_line|#define AU1500_GPIO_205           54
DECL|macro|AU1500_GPIO_23
mdefine_line|#define AU1500_GPIO_23            55
DECL|macro|AU1500_GPIO_24
mdefine_line|#define AU1500_GPIO_24            56
DECL|macro|AU1500_GPIO_25
mdefine_line|#define AU1500_GPIO_25            57
DECL|macro|AU1500_GPIO_26
mdefine_line|#define AU1500_GPIO_26            58
DECL|macro|AU1500_GPIO_27
mdefine_line|#define AU1500_GPIO_27            59
DECL|macro|AU1500_GPIO_28
mdefine_line|#define AU1500_GPIO_28            60
DECL|macro|AU1500_GPIO_206
mdefine_line|#define AU1500_GPIO_206           61
DECL|macro|AU1500_GPIO_207
mdefine_line|#define AU1500_GPIO_207           62
DECL|macro|AU1500_GPIO_208_215
mdefine_line|#define AU1500_GPIO_208_215       63
DECL|macro|UART0_ADDR
mdefine_line|#define UART0_ADDR                0xB1100000
DECL|macro|UART3_ADDR
mdefine_line|#define UART3_ADDR                0xB1400000
DECL|macro|USB_OHCI_BASE
mdefine_line|#define USB_OHCI_BASE             0x10100000 
singleline_comment|// phys addr for ioremap
DECL|macro|USB_HOST_CONFIG
mdefine_line|#define USB_HOST_CONFIG           0xB017fffc
DECL|macro|AU1500_ETH0_BASE
mdefine_line|#define AU1500_ETH0_BASE&t;  0xB1500000
DECL|macro|AU1500_ETH1_BASE
mdefine_line|#define AU1500_ETH1_BASE&t;  0xB1510000
DECL|macro|AU1500_MAC0_ENABLE
mdefine_line|#define AU1500_MAC0_ENABLE       0xB1520000
DECL|macro|AU1500_MAC1_ENABLE
mdefine_line|#define AU1500_MAC1_ENABLE       0xB1520004
DECL|macro|NUM_ETH_INTERFACES
mdefine_line|#define NUM_ETH_INTERFACES 2
macro_line|#endif 
singleline_comment|// CONFIG_SOC_AU1500
multiline_comment|/* Au1100 */
macro_line|#ifdef CONFIG_SOC_AU1100
DECL|macro|AU1100_UART0_INT
mdefine_line|#define AU1100_UART0_INT          0
DECL|macro|AU1100_UART1_INT
mdefine_line|#define AU1100_UART1_INT          1
DECL|macro|AU1100_SD_INT
mdefine_line|#define AU1100_SD_INT             2
DECL|macro|AU1100_UART3_INT
mdefine_line|#define AU1100_UART3_INT          3
DECL|macro|AU1000_SSI0_INT
mdefine_line|#define AU1000_SSI0_INT           4
DECL|macro|AU1000_SSI1_INT
mdefine_line|#define AU1000_SSI1_INT           5
DECL|macro|AU1000_DMA_INT_BASE
mdefine_line|#define AU1000_DMA_INT_BASE       6
DECL|macro|AU1000_TOY_INT
mdefine_line|#define AU1000_TOY_INT            14
DECL|macro|AU1000_TOY_MATCH0_INT
mdefine_line|#define AU1000_TOY_MATCH0_INT     15
DECL|macro|AU1000_TOY_MATCH1_INT
mdefine_line|#define AU1000_TOY_MATCH1_INT     16
DECL|macro|AU1000_TOY_MATCH2_INT
mdefine_line|#define AU1000_TOY_MATCH2_INT     17
DECL|macro|AU1000_RTC_INT
mdefine_line|#define AU1000_RTC_INT            18
DECL|macro|AU1000_RTC_MATCH0_INT
mdefine_line|#define AU1000_RTC_MATCH0_INT     19
DECL|macro|AU1000_RTC_MATCH1_INT
mdefine_line|#define AU1000_RTC_MATCH1_INT     20
DECL|macro|AU1000_RTC_MATCH2_INT
mdefine_line|#define AU1000_RTC_MATCH2_INT     21
DECL|macro|AU1000_IRDA_TX_INT
mdefine_line|#define AU1000_IRDA_TX_INT        22
DECL|macro|AU1000_IRDA_RX_INT
mdefine_line|#define AU1000_IRDA_RX_INT        23
DECL|macro|AU1000_USB_DEV_REQ_INT
mdefine_line|#define AU1000_USB_DEV_REQ_INT    24
DECL|macro|AU1000_USB_DEV_SUS_INT
mdefine_line|#define AU1000_USB_DEV_SUS_INT    25
DECL|macro|AU1000_USB_HOST_INT
mdefine_line|#define AU1000_USB_HOST_INT       26
DECL|macro|AU1000_ACSYNC_INT
mdefine_line|#define AU1000_ACSYNC_INT         27
DECL|macro|AU1100_MAC0_DMA_INT
mdefine_line|#define AU1100_MAC0_DMA_INT       28
DECL|macro|AU1100_GPIO_208_215
mdefine_line|#define&t;AU1100_GPIO_208_215&t;29
DECL|macro|AU1100_LCD_INT
mdefine_line|#define&t;AU1100_LCD_INT            30
DECL|macro|AU1000_AC97C_INT
mdefine_line|#define AU1000_AC97C_INT          31
DECL|macro|AU1000_GPIO_0
mdefine_line|#define AU1000_GPIO_0             32
DECL|macro|AU1000_GPIO_1
mdefine_line|#define AU1000_GPIO_1             33
DECL|macro|AU1000_GPIO_2
mdefine_line|#define AU1000_GPIO_2             34
DECL|macro|AU1000_GPIO_3
mdefine_line|#define AU1000_GPIO_3             35
DECL|macro|AU1000_GPIO_4
mdefine_line|#define AU1000_GPIO_4             36
DECL|macro|AU1000_GPIO_5
mdefine_line|#define AU1000_GPIO_5             37
DECL|macro|AU1000_GPIO_6
mdefine_line|#define AU1000_GPIO_6             38
DECL|macro|AU1000_GPIO_7
mdefine_line|#define AU1000_GPIO_7             39
DECL|macro|AU1000_GPIO_8
mdefine_line|#define AU1000_GPIO_8             40
DECL|macro|AU1000_GPIO_9
mdefine_line|#define AU1000_GPIO_9             41
DECL|macro|AU1000_GPIO_10
mdefine_line|#define AU1000_GPIO_10            42
DECL|macro|AU1000_GPIO_11
mdefine_line|#define AU1000_GPIO_11            43
DECL|macro|AU1000_GPIO_12
mdefine_line|#define AU1000_GPIO_12            44
DECL|macro|AU1000_GPIO_13
mdefine_line|#define AU1000_GPIO_13            45
DECL|macro|AU1000_GPIO_14
mdefine_line|#define AU1000_GPIO_14            46
DECL|macro|AU1000_GPIO_15
mdefine_line|#define AU1000_GPIO_15            47
DECL|macro|UART0_ADDR
mdefine_line|#define UART0_ADDR                0xB1100000
DECL|macro|UART1_ADDR
mdefine_line|#define UART1_ADDR                0xB1200000
DECL|macro|UART3_ADDR
mdefine_line|#define UART3_ADDR                0xB1400000
DECL|macro|USB_OHCI_BASE
mdefine_line|#define USB_OHCI_BASE             0x10100000 
singleline_comment|// phys addr for ioremap
DECL|macro|USB_HOST_CONFIG
mdefine_line|#define USB_HOST_CONFIG           0xB017fffc
DECL|macro|AU1100_ETH0_BASE
mdefine_line|#define AU1100_ETH0_BASE&t;  0xB0500000
DECL|macro|AU1100_MAC0_ENABLE
mdefine_line|#define AU1100_MAC0_ENABLE       0xB0520000
DECL|macro|NUM_ETH_INTERFACES
mdefine_line|#define NUM_ETH_INTERFACES 1
macro_line|#endif 
singleline_comment|// CONFIG_SOC_AU1100
macro_line|#ifdef CONFIG_SOC_AU1550
DECL|macro|AU1550_UART0_INT
mdefine_line|#define AU1550_UART0_INT          0
DECL|macro|AU1550_PCI_INTA
mdefine_line|#define AU1550_PCI_INTA           1
DECL|macro|AU1550_PCI_INTB
mdefine_line|#define AU1550_PCI_INTB           2
DECL|macro|AU1550_DDMA_INT
mdefine_line|#define AU1550_DDMA_INT           3
DECL|macro|AU1550_CRYPTO_INT
mdefine_line|#define AU1550_CRYPTO_INT         4
DECL|macro|AU1550_PCI_INTC
mdefine_line|#define AU1550_PCI_INTC           5
DECL|macro|AU1550_PCI_INTD
mdefine_line|#define AU1550_PCI_INTD           6
DECL|macro|AU1550_PCI_RST_INT
mdefine_line|#define AU1550_PCI_RST_INT        7
DECL|macro|AU1550_UART1_INT
mdefine_line|#define AU1550_UART1_INT          8
DECL|macro|AU1550_UART3_INT
mdefine_line|#define AU1550_UART3_INT          9
DECL|macro|AU1550_PSC0_INT
mdefine_line|#define AU1550_PSC0_INT           10
DECL|macro|AU1550_PSC1_INT
mdefine_line|#define AU1550_PSC1_INT           11
DECL|macro|AU1550_PSC2_INT
mdefine_line|#define AU1550_PSC2_INT           12
DECL|macro|AU1550_PSC3_INT
mdefine_line|#define AU1550_PSC3_INT           13
DECL|macro|AU1550_TOY_INT
mdefine_line|#define AU1550_TOY_INT&t;&t;&t;  14
DECL|macro|AU1550_TOY_MATCH0_INT
mdefine_line|#define AU1550_TOY_MATCH0_INT     15
DECL|macro|AU1550_TOY_MATCH1_INT
mdefine_line|#define AU1550_TOY_MATCH1_INT     16
DECL|macro|AU1550_TOY_MATCH2_INT
mdefine_line|#define AU1550_TOY_MATCH2_INT     17
DECL|macro|AU1550_RTC_INT
mdefine_line|#define AU1550_RTC_INT            18
DECL|macro|AU1550_RTC_MATCH0_INT
mdefine_line|#define AU1550_RTC_MATCH0_INT     19
DECL|macro|AU1550_RTC_MATCH1_INT
mdefine_line|#define AU1550_RTC_MATCH1_INT     20
DECL|macro|AU1550_RTC_MATCH2_INT
mdefine_line|#define AU1550_RTC_MATCH2_INT     21
DECL|macro|AU1550_NAND_INT
mdefine_line|#define AU1550_NAND_INT           23
DECL|macro|AU1550_USB_DEV_REQ_INT
mdefine_line|#define AU1550_USB_DEV_REQ_INT    24
DECL|macro|AU1550_USB_DEV_SUS_INT
mdefine_line|#define AU1550_USB_DEV_SUS_INT    25
DECL|macro|AU1550_USB_HOST_INT
mdefine_line|#define AU1550_USB_HOST_INT       26
DECL|macro|AU1000_USB_DEV_REQ_INT
mdefine_line|#define AU1000_USB_DEV_REQ_INT    AU1550_USB_DEV_REQ_INT
DECL|macro|AU1000_USB_DEV_SUS_INT
mdefine_line|#define AU1000_USB_DEV_SUS_INT    AU1550_USB_DEV_SUS_INT
DECL|macro|AU1000_USB_HOST_INT
mdefine_line|#define AU1000_USB_HOST_INT       AU1550_USB_HOST_INT
DECL|macro|AU1550_MAC0_DMA_INT
mdefine_line|#define AU1550_MAC0_DMA_INT       27
DECL|macro|AU1550_MAC1_DMA_INT
mdefine_line|#define AU1550_MAC1_DMA_INT       28
DECL|macro|AU1000_GPIO_0
mdefine_line|#define AU1000_GPIO_0             32
DECL|macro|AU1000_GPIO_1
mdefine_line|#define AU1000_GPIO_1             33
DECL|macro|AU1000_GPIO_2
mdefine_line|#define AU1000_GPIO_2             34
DECL|macro|AU1000_GPIO_3
mdefine_line|#define AU1000_GPIO_3             35
DECL|macro|AU1000_GPIO_4
mdefine_line|#define AU1000_GPIO_4             36
DECL|macro|AU1000_GPIO_5
mdefine_line|#define AU1000_GPIO_5             37
DECL|macro|AU1000_GPIO_6
mdefine_line|#define AU1000_GPIO_6             38
DECL|macro|AU1000_GPIO_7
mdefine_line|#define AU1000_GPIO_7             39
DECL|macro|AU1000_GPIO_8
mdefine_line|#define AU1000_GPIO_8             40
DECL|macro|AU1000_GPIO_9
mdefine_line|#define AU1000_GPIO_9             41
DECL|macro|AU1000_GPIO_10
mdefine_line|#define AU1000_GPIO_10            42
DECL|macro|AU1000_GPIO_11
mdefine_line|#define AU1000_GPIO_11            43
DECL|macro|AU1000_GPIO_12
mdefine_line|#define AU1000_GPIO_12            44
DECL|macro|AU1000_GPIO_13
mdefine_line|#define AU1000_GPIO_13            45
DECL|macro|AU1000_GPIO_14
mdefine_line|#define AU1000_GPIO_14            46
DECL|macro|AU1000_GPIO_15
mdefine_line|#define AU1000_GPIO_15            47
DECL|macro|AU1550_GPIO_200
mdefine_line|#define AU1550_GPIO_200           48
DECL|macro|AU1500_GPIO_201_205
mdefine_line|#define AU1500_GPIO_201_205       49&t;
singleline_comment|// Logical or of GPIO201:205
DECL|macro|AU1500_GPIO_16
mdefine_line|#define AU1500_GPIO_16            50
DECL|macro|AU1500_GPIO_17
mdefine_line|#define AU1500_GPIO_17            51
DECL|macro|AU1500_GPIO_20
mdefine_line|#define AU1500_GPIO_20            52
DECL|macro|AU1500_GPIO_21
mdefine_line|#define AU1500_GPIO_21            53
DECL|macro|AU1500_GPIO_22
mdefine_line|#define AU1500_GPIO_22            54
DECL|macro|AU1500_GPIO_23
mdefine_line|#define AU1500_GPIO_23            55
DECL|macro|AU1500_GPIO_24
mdefine_line|#define AU1500_GPIO_24            56
DECL|macro|AU1500_GPIO_25
mdefine_line|#define AU1500_GPIO_25            57
DECL|macro|AU1500_GPIO_26
mdefine_line|#define AU1500_GPIO_26            58
DECL|macro|AU1500_GPIO_27
mdefine_line|#define AU1500_GPIO_27            59
DECL|macro|AU1500_GPIO_28
mdefine_line|#define AU1500_GPIO_28            60
DECL|macro|AU1500_GPIO_206
mdefine_line|#define AU1500_GPIO_206           61
DECL|macro|AU1500_GPIO_207
mdefine_line|#define AU1500_GPIO_207           62
DECL|macro|AU1500_GPIO_208_218
mdefine_line|#define AU1500_GPIO_208_218       63&t;
singleline_comment|// Logical or of GPIO208:218
DECL|macro|UART0_ADDR
mdefine_line|#define UART0_ADDR                0xB1100000
DECL|macro|UART1_ADDR
mdefine_line|#define UART1_ADDR                0xB1200000
DECL|macro|UART3_ADDR
mdefine_line|#define UART3_ADDR                0xB1400000
DECL|macro|USB_OHCI_BASE
mdefine_line|#define USB_OHCI_BASE             0x14020000 
singleline_comment|// phys addr for ioremap
DECL|macro|USB_HOST_CONFIG
mdefine_line|#define USB_HOST_CONFIG           0xB4027ffc
DECL|macro|AU1550_ETH0_BASE
mdefine_line|#define AU1550_ETH0_BASE      0xB0500000
DECL|macro|AU1550_ETH1_BASE
mdefine_line|#define AU1550_ETH1_BASE      0xB0510000
DECL|macro|AU1550_MAC0_ENABLE
mdefine_line|#define AU1550_MAC0_ENABLE       0xB0520000
DECL|macro|AU1550_MAC1_ENABLE
mdefine_line|#define AU1550_MAC1_ENABLE       0xB0520004
DECL|macro|NUM_ETH_INTERFACES
mdefine_line|#define NUM_ETH_INTERFACES 2
macro_line|#endif 
singleline_comment|// CONFIG_SOC_AU1550
macro_line|#ifdef CONFIG_SOC_AU1200
DECL|macro|AU1200_UART0_INT
mdefine_line|#define AU1200_UART0_INT          0
DECL|macro|AU1200_SWT_INT
mdefine_line|#define AU1200_SWT_INT            1
DECL|macro|AU1200_SD_INT
mdefine_line|#define AU1200_SD_INT             2
DECL|macro|AU1200_DDMA_INT
mdefine_line|#define AU1200_DDMA_INT           3
DECL|macro|AU1200_MAE_BE_INT
mdefine_line|#define AU1200_MAE_BE_INT         4
DECL|macro|AU1200_GPIO_200
mdefine_line|#define AU1200_GPIO_200           5
DECL|macro|AU1200_GPIO_201
mdefine_line|#define AU1200_GPIO_201           6
DECL|macro|AU1200_GPIO_202
mdefine_line|#define AU1200_GPIO_202           7
DECL|macro|AU1200_UART1_INT
mdefine_line|#define AU1200_UART1_INT          8
DECL|macro|AU1200_MAE_FE_INT
mdefine_line|#define AU1200_MAE_FE_INT         9
DECL|macro|AU1200_PSC0_INT
mdefine_line|#define AU1200_PSC0_INT           10
DECL|macro|AU1200_PSC1_INT
mdefine_line|#define AU1200_PSC1_INT           11
DECL|macro|AU1200_AES_INT
mdefine_line|#define AU1200_AES_INT            12
DECL|macro|AU1200_CAMERA_INT
mdefine_line|#define AU1200_CAMERA_INT         13
DECL|macro|AU1200_TOY_INT
mdefine_line|#define AU1200_TOY_INT&t;&t;&t;  14
DECL|macro|AU1200_TOY_MATCH0_INT
mdefine_line|#define AU1200_TOY_MATCH0_INT     15
DECL|macro|AU1200_TOY_MATCH1_INT
mdefine_line|#define AU1200_TOY_MATCH1_INT     16
DECL|macro|AU1200_TOY_MATCH2_INT
mdefine_line|#define AU1200_TOY_MATCH2_INT     17
DECL|macro|AU1200_RTC_INT
mdefine_line|#define AU1200_RTC_INT            18
DECL|macro|AU1200_RTC_MATCH0_INT
mdefine_line|#define AU1200_RTC_MATCH0_INT     19
DECL|macro|AU1200_RTC_MATCH1_INT
mdefine_line|#define AU1200_RTC_MATCH1_INT     20
DECL|macro|AU1200_RTC_MATCH2_INT
mdefine_line|#define AU1200_RTC_MATCH2_INT     21
DECL|macro|AU1200_NAND_INT
mdefine_line|#define AU1200_NAND_INT           23
DECL|macro|AU1200_GPIO_204
mdefine_line|#define AU1200_GPIO_204           24
DECL|macro|AU1200_GPIO_205
mdefine_line|#define AU1200_GPIO_205           25
DECL|macro|AU1200_GPIO_206
mdefine_line|#define AU1200_GPIO_206           26
DECL|macro|AU1200_GPIO_207
mdefine_line|#define AU1200_GPIO_207           27
DECL|macro|AU1200_GPIO_208_215
mdefine_line|#define AU1200_GPIO_208_215       28 
singleline_comment|// Logical OR of 208:215
DECL|macro|AU1200_USB_INT
mdefine_line|#define AU1200_USB_INT            29
DECL|macro|AU1200_LCD_INT
mdefine_line|#define AU1200_LCD_INT            30
DECL|macro|AU1200_MAE_BOTH_INT
mdefine_line|#define AU1200_MAE_BOTH_INT       31
DECL|macro|AU1000_GPIO_0
mdefine_line|#define AU1000_GPIO_0             32
DECL|macro|AU1000_GPIO_1
mdefine_line|#define AU1000_GPIO_1             33
DECL|macro|AU1000_GPIO_2
mdefine_line|#define AU1000_GPIO_2             34
DECL|macro|AU1000_GPIO_3
mdefine_line|#define AU1000_GPIO_3             35
DECL|macro|AU1000_GPIO_4
mdefine_line|#define AU1000_GPIO_4             36
DECL|macro|AU1000_GPIO_5
mdefine_line|#define AU1000_GPIO_5             37
DECL|macro|AU1000_GPIO_6
mdefine_line|#define AU1000_GPIO_6             38
DECL|macro|AU1000_GPIO_7
mdefine_line|#define AU1000_GPIO_7             39
DECL|macro|AU1000_GPIO_8
mdefine_line|#define AU1000_GPIO_8             40
DECL|macro|AU1000_GPIO_9
mdefine_line|#define AU1000_GPIO_9             41
DECL|macro|AU1000_GPIO_10
mdefine_line|#define AU1000_GPIO_10            42
DECL|macro|AU1000_GPIO_11
mdefine_line|#define AU1000_GPIO_11            43
DECL|macro|AU1000_GPIO_12
mdefine_line|#define AU1000_GPIO_12            44
DECL|macro|AU1000_GPIO_13
mdefine_line|#define AU1000_GPIO_13            45
DECL|macro|AU1000_GPIO_14
mdefine_line|#define AU1000_GPIO_14            46
DECL|macro|AU1000_GPIO_15
mdefine_line|#define AU1000_GPIO_15            47
DECL|macro|AU1000_GPIO_16
mdefine_line|#define AU1000_GPIO_16            48
DECL|macro|AU1000_GPIO_17
mdefine_line|#define AU1000_GPIO_17            49
DECL|macro|AU1000_GPIO_18
mdefine_line|#define AU1000_GPIO_18            50
DECL|macro|AU1000_GPIO_19
mdefine_line|#define AU1000_GPIO_19            51
DECL|macro|AU1000_GPIO_20
mdefine_line|#define AU1000_GPIO_20            52
DECL|macro|AU1000_GPIO_21
mdefine_line|#define AU1000_GPIO_21            53
DECL|macro|AU1000_GPIO_22
mdefine_line|#define AU1000_GPIO_22            54
DECL|macro|AU1000_GPIO_23
mdefine_line|#define AU1000_GPIO_23            55
DECL|macro|AU1000_GPIO_24
mdefine_line|#define AU1000_GPIO_24            56
DECL|macro|AU1000_GPIO_25
mdefine_line|#define AU1000_GPIO_25            57
DECL|macro|AU1000_GPIO_26
mdefine_line|#define AU1000_GPIO_26            58
DECL|macro|AU1000_GPIO_27
mdefine_line|#define AU1000_GPIO_27            59
DECL|macro|AU1000_GPIO_28
mdefine_line|#define AU1000_GPIO_28            60
DECL|macro|AU1000_GPIO_29
mdefine_line|#define AU1000_GPIO_29            61
DECL|macro|AU1000_GPIO_30
mdefine_line|#define AU1000_GPIO_30            62
DECL|macro|AU1000_GPIO_31
mdefine_line|#define AU1000_GPIO_31            63
DECL|macro|UART0_ADDR
mdefine_line|#define UART0_ADDR                0xB1100000
DECL|macro|UART1_ADDR
mdefine_line|#define UART1_ADDR                0xB1200000
DECL|macro|USB_OHCI_BASE
mdefine_line|#define USB_OHCI_BASE             0x14020000 
singleline_comment|// phys addr for ioremap
DECL|macro|USB_HOST_CONFIG
mdefine_line|#define USB_HOST_CONFIG           0xB4027ffc
singleline_comment|// these are here for prototyping on au1550 (do not exist on au1200)
DECL|macro|AU1200_ETH0_BASE
mdefine_line|#define AU1200_ETH0_BASE      0xB0500000
DECL|macro|AU1200_ETH1_BASE
mdefine_line|#define AU1200_ETH1_BASE      0xB0510000
DECL|macro|AU1200_MAC0_ENABLE
mdefine_line|#define AU1200_MAC0_ENABLE       0xB0520000
DECL|macro|AU1200_MAC1_ENABLE
mdefine_line|#define AU1200_MAC1_ENABLE       0xB0520004
DECL|macro|NUM_ETH_INTERFACES
mdefine_line|#define NUM_ETH_INTERFACES 2
macro_line|#endif 
singleline_comment|// CONFIG_SOC_AU1200
DECL|macro|AU1000_LAST_INTC0_INT
mdefine_line|#define AU1000_LAST_INTC0_INT     31
DECL|macro|AU1000_MAX_INTR
mdefine_line|#define AU1000_MAX_INTR           63
multiline_comment|/* Programmable Counters 0 and 1 */
DECL|macro|SYS_BASE
mdefine_line|#define SYS_BASE                   0xB1900000
DECL|macro|SYS_COUNTER_CNTRL
mdefine_line|#define SYS_COUNTER_CNTRL          (SYS_BASE + 0x14)
DECL|macro|SYS_CNTRL_E1S
mdefine_line|#define SYS_CNTRL_E1S            (1&lt;&lt;23)
DECL|macro|SYS_CNTRL_T1S
mdefine_line|#define SYS_CNTRL_T1S            (1&lt;&lt;20)
DECL|macro|SYS_CNTRL_M21
mdefine_line|#define SYS_CNTRL_M21            (1&lt;&lt;19)
DECL|macro|SYS_CNTRL_M11
mdefine_line|#define SYS_CNTRL_M11            (1&lt;&lt;18)
DECL|macro|SYS_CNTRL_M01
mdefine_line|#define SYS_CNTRL_M01            (1&lt;&lt;17)
DECL|macro|SYS_CNTRL_C1S
mdefine_line|#define SYS_CNTRL_C1S            (1&lt;&lt;16)
DECL|macro|SYS_CNTRL_BP
mdefine_line|#define SYS_CNTRL_BP             (1&lt;&lt;14)
DECL|macro|SYS_CNTRL_EN1
mdefine_line|#define SYS_CNTRL_EN1            (1&lt;&lt;13)
DECL|macro|SYS_CNTRL_BT1
mdefine_line|#define SYS_CNTRL_BT1            (1&lt;&lt;12)
DECL|macro|SYS_CNTRL_EN0
mdefine_line|#define SYS_CNTRL_EN0            (1&lt;&lt;11)
DECL|macro|SYS_CNTRL_BT0
mdefine_line|#define SYS_CNTRL_BT0            (1&lt;&lt;10)
DECL|macro|SYS_CNTRL_E0
mdefine_line|#define SYS_CNTRL_E0             (1&lt;&lt;8)
DECL|macro|SYS_CNTRL_E0S
mdefine_line|#define SYS_CNTRL_E0S            (1&lt;&lt;7)
DECL|macro|SYS_CNTRL_32S
mdefine_line|#define SYS_CNTRL_32S            (1&lt;&lt;5)
DECL|macro|SYS_CNTRL_T0S
mdefine_line|#define SYS_CNTRL_T0S            (1&lt;&lt;4)
DECL|macro|SYS_CNTRL_M20
mdefine_line|#define SYS_CNTRL_M20            (1&lt;&lt;3)
DECL|macro|SYS_CNTRL_M10
mdefine_line|#define SYS_CNTRL_M10            (1&lt;&lt;2)
DECL|macro|SYS_CNTRL_M00
mdefine_line|#define SYS_CNTRL_M00            (1&lt;&lt;1)
DECL|macro|SYS_CNTRL_C0S
mdefine_line|#define SYS_CNTRL_C0S            (1&lt;&lt;0)
multiline_comment|/* Programmable Counter 0 Registers */
DECL|macro|SYS_TOYTRIM
mdefine_line|#define SYS_TOYTRIM                 (SYS_BASE + 0)
DECL|macro|SYS_TOYWRITE
mdefine_line|#define SYS_TOYWRITE                (SYS_BASE + 4)
DECL|macro|SYS_TOYMATCH0
mdefine_line|#define SYS_TOYMATCH0               (SYS_BASE + 8)
DECL|macro|SYS_TOYMATCH1
mdefine_line|#define SYS_TOYMATCH1               (SYS_BASE + 0xC)
DECL|macro|SYS_TOYMATCH2
mdefine_line|#define SYS_TOYMATCH2               (SYS_BASE + 0x10)
DECL|macro|SYS_TOYREAD
mdefine_line|#define SYS_TOYREAD                 (SYS_BASE + 0x40)
multiline_comment|/* Programmable Counter 1 Registers */
DECL|macro|SYS_RTCTRIM
mdefine_line|#define SYS_RTCTRIM                 (SYS_BASE + 0x44)
DECL|macro|SYS_RTCWRITE
mdefine_line|#define SYS_RTCWRITE                (SYS_BASE + 0x48)
DECL|macro|SYS_RTCMATCH0
mdefine_line|#define SYS_RTCMATCH0               (SYS_BASE + 0x4C)
DECL|macro|SYS_RTCMATCH1
mdefine_line|#define SYS_RTCMATCH1               (SYS_BASE + 0x50)
DECL|macro|SYS_RTCMATCH2
mdefine_line|#define SYS_RTCMATCH2               (SYS_BASE + 0x54)
DECL|macro|SYS_RTCREAD
mdefine_line|#define SYS_RTCREAD                 (SYS_BASE + 0x58)
multiline_comment|/* I2S Controller */
DECL|macro|I2S_DATA
mdefine_line|#define I2S_DATA                    0xB1000000
DECL|macro|I2S_DATA_MASK
mdefine_line|#define I2S_DATA_MASK        (0xffffff)
DECL|macro|I2S_CONFIG
mdefine_line|#define I2S_CONFIG                0xB1000004
DECL|macro|I2S_CONFIG_XU
mdefine_line|#define I2S_CONFIG_XU        (1&lt;&lt;25)
DECL|macro|I2S_CONFIG_XO
mdefine_line|#define I2S_CONFIG_XO        (1&lt;&lt;24)
DECL|macro|I2S_CONFIG_RU
mdefine_line|#define I2S_CONFIG_RU        (1&lt;&lt;23)
DECL|macro|I2S_CONFIG_RO
mdefine_line|#define I2S_CONFIG_RO        (1&lt;&lt;22)
DECL|macro|I2S_CONFIG_TR
mdefine_line|#define I2S_CONFIG_TR        (1&lt;&lt;21)
DECL|macro|I2S_CONFIG_TE
mdefine_line|#define I2S_CONFIG_TE        (1&lt;&lt;20)
DECL|macro|I2S_CONFIG_TF
mdefine_line|#define I2S_CONFIG_TF        (1&lt;&lt;19)
DECL|macro|I2S_CONFIG_RR
mdefine_line|#define I2S_CONFIG_RR        (1&lt;&lt;18)
DECL|macro|I2S_CONFIG_RE
mdefine_line|#define I2S_CONFIG_RE        (1&lt;&lt;17)
DECL|macro|I2S_CONFIG_RF
mdefine_line|#define I2S_CONFIG_RF        (1&lt;&lt;16)
DECL|macro|I2S_CONFIG_PD
mdefine_line|#define I2S_CONFIG_PD        (1&lt;&lt;11)
DECL|macro|I2S_CONFIG_LB
mdefine_line|#define I2S_CONFIG_LB        (1&lt;&lt;10)
DECL|macro|I2S_CONFIG_IC
mdefine_line|#define I2S_CONFIG_IC        (1&lt;&lt;9)
DECL|macro|I2S_CONFIG_FM_BIT
mdefine_line|#define I2S_CONFIG_FM_BIT    7
DECL|macro|I2S_CONFIG_FM_MASK
mdefine_line|#define I2S_CONFIG_FM_MASK     (0x3 &lt;&lt; I2S_CONFIG_FM_BIT)
DECL|macro|I2S_CONFIG_FM_I2S
mdefine_line|#define I2S_CONFIG_FM_I2S    (0x0 &lt;&lt; I2S_CONFIG_FM_BIT)
DECL|macro|I2S_CONFIG_FM_LJ
mdefine_line|#define I2S_CONFIG_FM_LJ     (0x1 &lt;&lt; I2S_CONFIG_FM_BIT)
DECL|macro|I2S_CONFIG_FM_RJ
mdefine_line|#define I2S_CONFIG_FM_RJ     (0x2 &lt;&lt; I2S_CONFIG_FM_BIT)
DECL|macro|I2S_CONFIG_TN
mdefine_line|#define I2S_CONFIG_TN        (1&lt;&lt;6)
DECL|macro|I2S_CONFIG_RN
mdefine_line|#define I2S_CONFIG_RN        (1&lt;&lt;5)
DECL|macro|I2S_CONFIG_SZ_BIT
mdefine_line|#define I2S_CONFIG_SZ_BIT    0
DECL|macro|I2S_CONFIG_SZ_MASK
mdefine_line|#define I2S_CONFIG_SZ_MASK     (0x1F &lt;&lt; I2S_CONFIG_SZ_BIT)
DECL|macro|I2S_CONTROL
mdefine_line|#define I2S_CONTROL                0xB1000008
DECL|macro|I2S_CONTROL_D
mdefine_line|#define I2S_CONTROL_D         (1&lt;&lt;1)
DECL|macro|I2S_CONTROL_CE
mdefine_line|#define I2S_CONTROL_CE        (1&lt;&lt;0)
multiline_comment|/* USB Host Controller */
DECL|macro|USB_OHCI_LEN
mdefine_line|#define USB_OHCI_LEN              0x00100000
multiline_comment|/* USB Device Controller */
DECL|macro|USBD_EP0RD
mdefine_line|#define USBD_EP0RD                0xB0200000
DECL|macro|USBD_EP0WR
mdefine_line|#define USBD_EP0WR                0xB0200004
DECL|macro|USBD_EP2WR
mdefine_line|#define USBD_EP2WR                0xB0200008
DECL|macro|USBD_EP3WR
mdefine_line|#define USBD_EP3WR                0xB020000C
DECL|macro|USBD_EP4RD
mdefine_line|#define USBD_EP4RD                0xB0200010
DECL|macro|USBD_EP5RD
mdefine_line|#define USBD_EP5RD                0xB0200014
DECL|macro|USBD_INTEN
mdefine_line|#define USBD_INTEN                0xB0200018
DECL|macro|USBD_INTSTAT
mdefine_line|#define USBD_INTSTAT              0xB020001C
DECL|macro|USBDEV_INT_SOF
mdefine_line|#define USBDEV_INT_SOF       (1&lt;&lt;12)
DECL|macro|USBDEV_INT_HF_BIT
mdefine_line|#define USBDEV_INT_HF_BIT    6
DECL|macro|USBDEV_INT_HF_MASK
mdefine_line|#define USBDEV_INT_HF_MASK   (0x3f &lt;&lt; USBDEV_INT_HF_BIT)
DECL|macro|USBDEV_INT_CMPLT_BIT
mdefine_line|#define USBDEV_INT_CMPLT_BIT  0
DECL|macro|USBDEV_INT_CMPLT_MASK
mdefine_line|#define USBDEV_INT_CMPLT_MASK (0x3f &lt;&lt; USBDEV_INT_CMPLT_BIT)
DECL|macro|USBD_CONFIG
mdefine_line|#define USBD_CONFIG               0xB0200020
DECL|macro|USBD_EP0CS
mdefine_line|#define USBD_EP0CS                0xB0200024
DECL|macro|USBD_EP2CS
mdefine_line|#define USBD_EP2CS                0xB0200028
DECL|macro|USBD_EP3CS
mdefine_line|#define USBD_EP3CS                0xB020002C
DECL|macro|USBD_EP4CS
mdefine_line|#define USBD_EP4CS                0xB0200030
DECL|macro|USBD_EP5CS
mdefine_line|#define USBD_EP5CS                0xB0200034
DECL|macro|USBDEV_CS_SU
mdefine_line|#define USBDEV_CS_SU         (1&lt;&lt;14)
DECL|macro|USBDEV_CS_NAK
mdefine_line|#define USBDEV_CS_NAK        (1&lt;&lt;13)
DECL|macro|USBDEV_CS_ACK
mdefine_line|#define USBDEV_CS_ACK        (1&lt;&lt;12)
DECL|macro|USBDEV_CS_BUSY
mdefine_line|#define USBDEV_CS_BUSY       (1&lt;&lt;11)
DECL|macro|USBDEV_CS_TSIZE_BIT
mdefine_line|#define USBDEV_CS_TSIZE_BIT  1
DECL|macro|USBDEV_CS_TSIZE_MASK
mdefine_line|#define USBDEV_CS_TSIZE_MASK (0x3ff &lt;&lt; USBDEV_CS_TSIZE_BIT)
DECL|macro|USBDEV_CS_STALL
mdefine_line|#define USBDEV_CS_STALL      (1&lt;&lt;0)
DECL|macro|USBD_EP0RDSTAT
mdefine_line|#define USBD_EP0RDSTAT            0xB0200040
DECL|macro|USBD_EP0WRSTAT
mdefine_line|#define USBD_EP0WRSTAT            0xB0200044
DECL|macro|USBD_EP2WRSTAT
mdefine_line|#define USBD_EP2WRSTAT            0xB0200048
DECL|macro|USBD_EP3WRSTAT
mdefine_line|#define USBD_EP3WRSTAT            0xB020004C
DECL|macro|USBD_EP4RDSTAT
mdefine_line|#define USBD_EP4RDSTAT            0xB0200050
DECL|macro|USBD_EP5RDSTAT
mdefine_line|#define USBD_EP5RDSTAT            0xB0200054
DECL|macro|USBDEV_FSTAT_FLUSH
mdefine_line|#define USBDEV_FSTAT_FLUSH     (1&lt;&lt;6)
DECL|macro|USBDEV_FSTAT_UF
mdefine_line|#define USBDEV_FSTAT_UF        (1&lt;&lt;5)
DECL|macro|USBDEV_FSTAT_OF
mdefine_line|#define USBDEV_FSTAT_OF        (1&lt;&lt;4)
DECL|macro|USBDEV_FSTAT_FCNT_BIT
mdefine_line|#define USBDEV_FSTAT_FCNT_BIT  0
DECL|macro|USBDEV_FSTAT_FCNT_MASK
mdefine_line|#define USBDEV_FSTAT_FCNT_MASK (0x0f &lt;&lt; USBDEV_FSTAT_FCNT_BIT)
DECL|macro|USBD_ENABLE
mdefine_line|#define USBD_ENABLE               0xB0200058
DECL|macro|USBDEV_ENABLE
mdefine_line|#define USBDEV_ENABLE (1&lt;&lt;1)
DECL|macro|USBDEV_CE
mdefine_line|#define USBDEV_CE     (1&lt;&lt;0)
multiline_comment|/* Ethernet Controllers  */
multiline_comment|/* 4 byte offsets from AU1000_ETH_BASE */
DECL|macro|MAC_CONTROL
mdefine_line|#define MAC_CONTROL                     0x0
DECL|macro|MAC_RX_ENABLE
mdefine_line|#define MAC_RX_ENABLE               (1&lt;&lt;2)
DECL|macro|MAC_TX_ENABLE
mdefine_line|#define MAC_TX_ENABLE               (1&lt;&lt;3)
DECL|macro|MAC_DEF_CHECK
mdefine_line|#define MAC_DEF_CHECK               (1&lt;&lt;5)
DECL|macro|MAC_SET_BL
mdefine_line|#define MAC_SET_BL(X)       (((X)&amp;0x3)&lt;&lt;6)
DECL|macro|MAC_AUTO_PAD
mdefine_line|#define MAC_AUTO_PAD                (1&lt;&lt;8)
DECL|macro|MAC_DISABLE_RETRY
mdefine_line|#define MAC_DISABLE_RETRY          (1&lt;&lt;10)
DECL|macro|MAC_DISABLE_BCAST
mdefine_line|#define MAC_DISABLE_BCAST          (1&lt;&lt;11)
DECL|macro|MAC_LATE_COL
mdefine_line|#define MAC_LATE_COL               (1&lt;&lt;12)
DECL|macro|MAC_HASH_MODE
mdefine_line|#define MAC_HASH_MODE              (1&lt;&lt;13)
DECL|macro|MAC_HASH_ONLY
mdefine_line|#define MAC_HASH_ONLY              (1&lt;&lt;15)
DECL|macro|MAC_PASS_ALL
mdefine_line|#define MAC_PASS_ALL               (1&lt;&lt;16)
DECL|macro|MAC_INVERSE_FILTER
mdefine_line|#define MAC_INVERSE_FILTER         (1&lt;&lt;17)
DECL|macro|MAC_PROMISCUOUS
mdefine_line|#define MAC_PROMISCUOUS            (1&lt;&lt;18)
DECL|macro|MAC_PASS_ALL_MULTI
mdefine_line|#define MAC_PASS_ALL_MULTI         (1&lt;&lt;19)
DECL|macro|MAC_FULL_DUPLEX
mdefine_line|#define MAC_FULL_DUPLEX            (1&lt;&lt;20)
DECL|macro|MAC_NORMAL_MODE
mdefine_line|#define MAC_NORMAL_MODE                 0
DECL|macro|MAC_INT_LOOPBACK
mdefine_line|#define MAC_INT_LOOPBACK           (1&lt;&lt;21)
DECL|macro|MAC_EXT_LOOPBACK
mdefine_line|#define MAC_EXT_LOOPBACK           (1&lt;&lt;22)
DECL|macro|MAC_DISABLE_RX_OWN
mdefine_line|#define MAC_DISABLE_RX_OWN         (1&lt;&lt;23)
DECL|macro|MAC_BIG_ENDIAN
mdefine_line|#define MAC_BIG_ENDIAN             (1&lt;&lt;30)
DECL|macro|MAC_RX_ALL
mdefine_line|#define MAC_RX_ALL                 (1&lt;&lt;31)
DECL|macro|MAC_ADDRESS_HIGH
mdefine_line|#define MAC_ADDRESS_HIGH                0x4
DECL|macro|MAC_ADDRESS_LOW
mdefine_line|#define MAC_ADDRESS_LOW                 0x8
DECL|macro|MAC_MCAST_HIGH
mdefine_line|#define MAC_MCAST_HIGH                  0xC
DECL|macro|MAC_MCAST_LOW
mdefine_line|#define MAC_MCAST_LOW                  0x10
DECL|macro|MAC_MII_CNTRL
mdefine_line|#define MAC_MII_CNTRL                  0x14
DECL|macro|MAC_MII_BUSY
mdefine_line|#define MAC_MII_BUSY                (1&lt;&lt;0)
DECL|macro|MAC_MII_READ
mdefine_line|#define MAC_MII_READ                     0
DECL|macro|MAC_MII_WRITE
mdefine_line|#define MAC_MII_WRITE               (1&lt;&lt;1)
DECL|macro|MAC_SET_MII_SELECT_REG
mdefine_line|#define MAC_SET_MII_SELECT_REG(X)   (((X)&amp;0x1f)&lt;&lt;6)
DECL|macro|MAC_SET_MII_SELECT_PHY
mdefine_line|#define MAC_SET_MII_SELECT_PHY(X)   (((X)&amp;0x1f)&lt;&lt;11)
DECL|macro|MAC_MII_DATA
mdefine_line|#define MAC_MII_DATA                   0x18
DECL|macro|MAC_FLOW_CNTRL
mdefine_line|#define MAC_FLOW_CNTRL                 0x1C
DECL|macro|MAC_FLOW_CNTRL_BUSY
mdefine_line|#define MAC_FLOW_CNTRL_BUSY         (1&lt;&lt;0)
DECL|macro|MAC_FLOW_CNTRL_ENABLE
mdefine_line|#define MAC_FLOW_CNTRL_ENABLE       (1&lt;&lt;1)
DECL|macro|MAC_PASS_CONTROL
mdefine_line|#define MAC_PASS_CONTROL            (1&lt;&lt;2)
DECL|macro|MAC_SET_PAUSE
mdefine_line|#define MAC_SET_PAUSE(X)        (((X)&amp;0xffff)&lt;&lt;16)
DECL|macro|MAC_VLAN1_TAG
mdefine_line|#define MAC_VLAN1_TAG                  0x20
DECL|macro|MAC_VLAN2_TAG
mdefine_line|#define MAC_VLAN2_TAG                  0x24
multiline_comment|/* Ethernet Controller Enable */
DECL|macro|MAC_EN_CLOCK_ENABLE
mdefine_line|#define MAC_EN_CLOCK_ENABLE         (1&lt;&lt;0)
DECL|macro|MAC_EN_RESET0
mdefine_line|#define MAC_EN_RESET0               (1&lt;&lt;1)
DECL|macro|MAC_EN_TOSS
mdefine_line|#define MAC_EN_TOSS                 (0&lt;&lt;2)
DECL|macro|MAC_EN_CACHEABLE
mdefine_line|#define MAC_EN_CACHEABLE            (1&lt;&lt;3)
DECL|macro|MAC_EN_RESET1
mdefine_line|#define MAC_EN_RESET1               (1&lt;&lt;4)
DECL|macro|MAC_EN_RESET2
mdefine_line|#define MAC_EN_RESET2               (1&lt;&lt;5)
DECL|macro|MAC_DMA_RESET
mdefine_line|#define MAC_DMA_RESET               (1&lt;&lt;6)
multiline_comment|/* Ethernet Controller DMA Channels */
DECL|macro|MAC0_TX_DMA_ADDR
mdefine_line|#define MAC0_TX_DMA_ADDR         0xB4004000
DECL|macro|MAC1_TX_DMA_ADDR
mdefine_line|#define MAC1_TX_DMA_ADDR         0xB4004200
multiline_comment|/* offsets from MAC_TX_RING_ADDR address */
DECL|macro|MAC_TX_BUFF0_STATUS
mdefine_line|#define MAC_TX_BUFF0_STATUS             0x0
DECL|macro|TX_FRAME_ABORTED
mdefine_line|#define TX_FRAME_ABORTED            (1&lt;&lt;0)
DECL|macro|TX_JAB_TIMEOUT
mdefine_line|#define TX_JAB_TIMEOUT              (1&lt;&lt;1)
DECL|macro|TX_NO_CARRIER
mdefine_line|#define TX_NO_CARRIER               (1&lt;&lt;2)
DECL|macro|TX_LOSS_CARRIER
mdefine_line|#define TX_LOSS_CARRIER             (1&lt;&lt;3)
DECL|macro|TX_EXC_DEF
mdefine_line|#define TX_EXC_DEF                  (1&lt;&lt;4)
DECL|macro|TX_LATE_COLL_ABORT
mdefine_line|#define TX_LATE_COLL_ABORT          (1&lt;&lt;5)
DECL|macro|TX_EXC_COLL
mdefine_line|#define TX_EXC_COLL                 (1&lt;&lt;6)
DECL|macro|TX_UNDERRUN
mdefine_line|#define TX_UNDERRUN                 (1&lt;&lt;7)
DECL|macro|TX_DEFERRED
mdefine_line|#define TX_DEFERRED                 (1&lt;&lt;8)
DECL|macro|TX_LATE_COLL
mdefine_line|#define TX_LATE_COLL                (1&lt;&lt;9)
DECL|macro|TX_COLL_CNT_MASK
mdefine_line|#define TX_COLL_CNT_MASK         (0xF&lt;&lt;10)
DECL|macro|TX_PKT_RETRY
mdefine_line|#define TX_PKT_RETRY               (1&lt;&lt;31)
DECL|macro|MAC_TX_BUFF0_ADDR
mdefine_line|#define MAC_TX_BUFF0_ADDR                0x4
DECL|macro|TX_DMA_ENABLE
mdefine_line|#define TX_DMA_ENABLE               (1&lt;&lt;0)
DECL|macro|TX_T_DONE
mdefine_line|#define TX_T_DONE                   (1&lt;&lt;1)
DECL|macro|TX_GET_DMA_BUFFER
mdefine_line|#define TX_GET_DMA_BUFFER(X)    (((X)&gt;&gt;2)&amp;0x3)
DECL|macro|MAC_TX_BUFF0_LEN
mdefine_line|#define MAC_TX_BUFF0_LEN                 0x8
DECL|macro|MAC_TX_BUFF1_STATUS
mdefine_line|#define MAC_TX_BUFF1_STATUS             0x10
DECL|macro|MAC_TX_BUFF1_ADDR
mdefine_line|#define MAC_TX_BUFF1_ADDR               0x14
DECL|macro|MAC_TX_BUFF1_LEN
mdefine_line|#define MAC_TX_BUFF1_LEN                0x18
DECL|macro|MAC_TX_BUFF2_STATUS
mdefine_line|#define MAC_TX_BUFF2_STATUS             0x20
DECL|macro|MAC_TX_BUFF2_ADDR
mdefine_line|#define MAC_TX_BUFF2_ADDR               0x24
DECL|macro|MAC_TX_BUFF2_LEN
mdefine_line|#define MAC_TX_BUFF2_LEN                0x28
DECL|macro|MAC_TX_BUFF3_STATUS
mdefine_line|#define MAC_TX_BUFF3_STATUS             0x30
DECL|macro|MAC_TX_BUFF3_ADDR
mdefine_line|#define MAC_TX_BUFF3_ADDR               0x34
DECL|macro|MAC_TX_BUFF3_LEN
mdefine_line|#define MAC_TX_BUFF3_LEN                0x38
DECL|macro|MAC0_RX_DMA_ADDR
mdefine_line|#define MAC0_RX_DMA_ADDR         0xB4004100
DECL|macro|MAC1_RX_DMA_ADDR
mdefine_line|#define MAC1_RX_DMA_ADDR         0xB4004300
multiline_comment|/* offsets from MAC_RX_RING_ADDR */
DECL|macro|MAC_RX_BUFF0_STATUS
mdefine_line|#define MAC_RX_BUFF0_STATUS              0x0
DECL|macro|RX_FRAME_LEN_MASK
mdefine_line|#define RX_FRAME_LEN_MASK           0x3fff
DECL|macro|RX_WDOG_TIMER
mdefine_line|#define RX_WDOG_TIMER              (1&lt;&lt;14)
DECL|macro|RX_RUNT
mdefine_line|#define RX_RUNT                    (1&lt;&lt;15)
DECL|macro|RX_OVERLEN
mdefine_line|#define RX_OVERLEN                 (1&lt;&lt;16)
DECL|macro|RX_COLL
mdefine_line|#define RX_COLL                    (1&lt;&lt;17)
DECL|macro|RX_ETHER
mdefine_line|#define RX_ETHER                   (1&lt;&lt;18)
DECL|macro|RX_MII_ERROR
mdefine_line|#define RX_MII_ERROR               (1&lt;&lt;19)
DECL|macro|RX_DRIBBLING
mdefine_line|#define RX_DRIBBLING               (1&lt;&lt;20)
DECL|macro|RX_CRC_ERROR
mdefine_line|#define RX_CRC_ERROR               (1&lt;&lt;21)
DECL|macro|RX_VLAN1
mdefine_line|#define RX_VLAN1                   (1&lt;&lt;22)
DECL|macro|RX_VLAN2
mdefine_line|#define RX_VLAN2                   (1&lt;&lt;23)
DECL|macro|RX_LEN_ERROR
mdefine_line|#define RX_LEN_ERROR               (1&lt;&lt;24)
DECL|macro|RX_CNTRL_FRAME
mdefine_line|#define RX_CNTRL_FRAME             (1&lt;&lt;25)
DECL|macro|RX_U_CNTRL_FRAME
mdefine_line|#define RX_U_CNTRL_FRAME           (1&lt;&lt;26)
DECL|macro|RX_MCAST_FRAME
mdefine_line|#define RX_MCAST_FRAME             (1&lt;&lt;27)
DECL|macro|RX_BCAST_FRAME
mdefine_line|#define RX_BCAST_FRAME             (1&lt;&lt;28)
DECL|macro|RX_FILTER_FAIL
mdefine_line|#define RX_FILTER_FAIL             (1&lt;&lt;29)
DECL|macro|RX_PACKET_FILTER
mdefine_line|#define RX_PACKET_FILTER           (1&lt;&lt;30)
DECL|macro|RX_MISSED_FRAME
mdefine_line|#define RX_MISSED_FRAME            (1&lt;&lt;31)
DECL|macro|RX_ERROR
mdefine_line|#define RX_ERROR (RX_WDOG_TIMER | RX_RUNT | RX_OVERLEN |  &bslash;&n;                    RX_COLL | RX_MII_ERROR | RX_CRC_ERROR | &bslash;&n;                    RX_LEN_ERROR | RX_U_CNTRL_FRAME | RX_MISSED_FRAME)
DECL|macro|MAC_RX_BUFF0_ADDR
mdefine_line|#define MAC_RX_BUFF0_ADDR                0x4
DECL|macro|RX_DMA_ENABLE
mdefine_line|#define RX_DMA_ENABLE               (1&lt;&lt;0)
DECL|macro|RX_T_DONE
mdefine_line|#define RX_T_DONE                   (1&lt;&lt;1)
DECL|macro|RX_GET_DMA_BUFFER
mdefine_line|#define RX_GET_DMA_BUFFER(X)    (((X)&gt;&gt;2)&amp;0x3)
DECL|macro|RX_SET_BUFF_ADDR
mdefine_line|#define RX_SET_BUFF_ADDR(X)     ((X)&amp;0xffffffc0)
DECL|macro|MAC_RX_BUFF1_STATUS
mdefine_line|#define MAC_RX_BUFF1_STATUS              0x10
DECL|macro|MAC_RX_BUFF1_ADDR
mdefine_line|#define MAC_RX_BUFF1_ADDR                0x14
DECL|macro|MAC_RX_BUFF2_STATUS
mdefine_line|#define MAC_RX_BUFF2_STATUS              0x20
DECL|macro|MAC_RX_BUFF2_ADDR
mdefine_line|#define MAC_RX_BUFF2_ADDR                0x24
DECL|macro|MAC_RX_BUFF3_STATUS
mdefine_line|#define MAC_RX_BUFF3_STATUS              0x30
DECL|macro|MAC_RX_BUFF3_ADDR
mdefine_line|#define MAC_RX_BUFF3_ADDR                0x34
multiline_comment|/* UARTS 0-3 */
DECL|macro|UART_BASE
mdefine_line|#define UART_BASE                 UART0_ADDR
DECL|macro|UART_DEBUG_BASE
mdefine_line|#define UART_DEBUG_BASE           UART3_ADDR
DECL|macro|UART_RX
mdefine_line|#define UART_RX&t;&t;0&t;/* Receive buffer */
DECL|macro|UART_TX
mdefine_line|#define UART_TX&t;&t;4&t;/* Transmit buffer */
DECL|macro|UART_IER
mdefine_line|#define UART_IER&t;8&t;/* Interrupt Enable Register */
DECL|macro|UART_IIR
mdefine_line|#define UART_IIR&t;0xC&t;/* Interrupt ID Register */
DECL|macro|UART_FCR
mdefine_line|#define UART_FCR&t;0x10&t;/* FIFO Control Register */
DECL|macro|UART_LCR
mdefine_line|#define UART_LCR&t;0x14&t;/* Line Control Register */
DECL|macro|UART_MCR
mdefine_line|#define UART_MCR&t;0x18&t;/* Modem Control Register */
DECL|macro|UART_LSR
mdefine_line|#define UART_LSR&t;0x1C&t;/* Line Status Register */
DECL|macro|UART_MSR
mdefine_line|#define UART_MSR&t;0x20&t;/* Modem Status Register */
DECL|macro|UART_CLK
mdefine_line|#define UART_CLK&t;0x28&t;/* Baud Rate Clock Divider */
DECL|macro|UART_MOD_CNTRL
mdefine_line|#define UART_MOD_CNTRL&t;0x100&t;/* Module Control */
DECL|macro|UART_FCR_ENABLE_FIFO
mdefine_line|#define UART_FCR_ENABLE_FIFO&t;0x01 /* Enable the FIFO */
DECL|macro|UART_FCR_CLEAR_RCVR
mdefine_line|#define UART_FCR_CLEAR_RCVR&t;0x02 /* Clear the RCVR FIFO */
DECL|macro|UART_FCR_CLEAR_XMIT
mdefine_line|#define UART_FCR_CLEAR_XMIT&t;0x04 /* Clear the XMIT FIFO */
DECL|macro|UART_FCR_DMA_SELECT
mdefine_line|#define UART_FCR_DMA_SELECT&t;0x08 /* For DMA applications */
DECL|macro|UART_FCR_TRIGGER_MASK
mdefine_line|#define UART_FCR_TRIGGER_MASK&t;0xF0 /* Mask for the FIFO trigger range */
DECL|macro|UART_FCR_R_TRIGGER_1
mdefine_line|#define UART_FCR_R_TRIGGER_1&t;0x00 /* Mask for receive trigger set at 1 */
DECL|macro|UART_FCR_R_TRIGGER_4
mdefine_line|#define UART_FCR_R_TRIGGER_4&t;0x40 /* Mask for receive trigger set at 4 */
DECL|macro|UART_FCR_R_TRIGGER_8
mdefine_line|#define UART_FCR_R_TRIGGER_8&t;0x80 /* Mask for receive trigger set at 8 */
DECL|macro|UART_FCR_R_TRIGGER_14
mdefine_line|#define UART_FCR_R_TRIGGER_14   0xA0 /* Mask for receive trigger set at 14 */
DECL|macro|UART_FCR_T_TRIGGER_0
mdefine_line|#define UART_FCR_T_TRIGGER_0&t;0x00 /* Mask for transmit trigger set at 0 */
DECL|macro|UART_FCR_T_TRIGGER_4
mdefine_line|#define UART_FCR_T_TRIGGER_4&t;0x10 /* Mask for transmit trigger set at 4 */
DECL|macro|UART_FCR_T_TRIGGER_8
mdefine_line|#define UART_FCR_T_TRIGGER_8    0x20 /* Mask for transmit trigger set at 8 */
DECL|macro|UART_FCR_T_TRIGGER_12
mdefine_line|#define UART_FCR_T_TRIGGER_12&t;0x30 /* Mask for transmit trigger set at 12 */
multiline_comment|/*&n; * These are the definitions for the Line Control Register&n; */
DECL|macro|UART_LCR_SBC
mdefine_line|#define UART_LCR_SBC&t;0x40&t;/* Set break control */
DECL|macro|UART_LCR_SPAR
mdefine_line|#define UART_LCR_SPAR&t;0x20&t;/* Stick parity (?) */
DECL|macro|UART_LCR_EPAR
mdefine_line|#define UART_LCR_EPAR&t;0x10&t;/* Even parity select */
DECL|macro|UART_LCR_PARITY
mdefine_line|#define UART_LCR_PARITY&t;0x08&t;/* Parity Enable */
DECL|macro|UART_LCR_STOP
mdefine_line|#define UART_LCR_STOP&t;0x04&t;/* Stop bits: 0=1 stop bit, 1= 2 stop bits */
DECL|macro|UART_LCR_WLEN5
mdefine_line|#define UART_LCR_WLEN5  0x00&t;/* Wordlength: 5 bits */
DECL|macro|UART_LCR_WLEN6
mdefine_line|#define UART_LCR_WLEN6  0x01&t;/* Wordlength: 6 bits */
DECL|macro|UART_LCR_WLEN7
mdefine_line|#define UART_LCR_WLEN7  0x02&t;/* Wordlength: 7 bits */
DECL|macro|UART_LCR_WLEN8
mdefine_line|#define UART_LCR_WLEN8  0x03&t;/* Wordlength: 8 bits */
multiline_comment|/*&n; * These are the definitions for the Line Status Register&n; */
DECL|macro|UART_LSR_TEMT
mdefine_line|#define UART_LSR_TEMT&t;0x40&t;/* Transmitter empty */
DECL|macro|UART_LSR_THRE
mdefine_line|#define UART_LSR_THRE&t;0x20&t;/* Transmit-hold-register empty */
DECL|macro|UART_LSR_BI
mdefine_line|#define UART_LSR_BI&t;0x10&t;/* Break interrupt indicator */
DECL|macro|UART_LSR_FE
mdefine_line|#define UART_LSR_FE&t;0x08&t;/* Frame error indicator */
DECL|macro|UART_LSR_PE
mdefine_line|#define UART_LSR_PE&t;0x04&t;/* Parity error indicator */
DECL|macro|UART_LSR_OE
mdefine_line|#define UART_LSR_OE&t;0x02&t;/* Overrun error indicator */
DECL|macro|UART_LSR_DR
mdefine_line|#define UART_LSR_DR&t;0x01&t;/* Receiver data ready */
multiline_comment|/*&n; * These are the definitions for the Interrupt Identification Register&n; */
DECL|macro|UART_IIR_NO_INT
mdefine_line|#define UART_IIR_NO_INT&t;0x01&t;/* No interrupts pending */
DECL|macro|UART_IIR_ID
mdefine_line|#define UART_IIR_ID&t;0x06&t;/* Mask for the interrupt ID */
DECL|macro|UART_IIR_MSI
mdefine_line|#define UART_IIR_MSI&t;0x00&t;/* Modem status interrupt */
DECL|macro|UART_IIR_THRI
mdefine_line|#define UART_IIR_THRI&t;0x02&t;/* Transmitter holding register empty */
DECL|macro|UART_IIR_RDI
mdefine_line|#define UART_IIR_RDI&t;0x04&t;/* Receiver data interrupt */
DECL|macro|UART_IIR_RLSI
mdefine_line|#define UART_IIR_RLSI&t;0x06&t;/* Receiver line status interrupt */
multiline_comment|/*&n; * These are the definitions for the Interrupt Enable Register&n; */
DECL|macro|UART_IER_MSI
mdefine_line|#define UART_IER_MSI&t;0x08&t;/* Enable Modem status interrupt */
DECL|macro|UART_IER_RLSI
mdefine_line|#define UART_IER_RLSI&t;0x04&t;/* Enable receiver line status interrupt */
DECL|macro|UART_IER_THRI
mdefine_line|#define UART_IER_THRI&t;0x02&t;/* Enable Transmitter holding register int. */
DECL|macro|UART_IER_RDI
mdefine_line|#define UART_IER_RDI&t;0x01&t;/* Enable receiver data interrupt */
multiline_comment|/*&n; * These are the definitions for the Modem Control Register&n; */
DECL|macro|UART_MCR_LOOP
mdefine_line|#define UART_MCR_LOOP&t;0x10&t;/* Enable loopback test mode */
DECL|macro|UART_MCR_OUT2
mdefine_line|#define UART_MCR_OUT2&t;0x08&t;/* Out2 complement */
DECL|macro|UART_MCR_OUT1
mdefine_line|#define UART_MCR_OUT1&t;0x04&t;/* Out1 complement */
DECL|macro|UART_MCR_RTS
mdefine_line|#define UART_MCR_RTS&t;0x02&t;/* RTS complement */
DECL|macro|UART_MCR_DTR
mdefine_line|#define UART_MCR_DTR&t;0x01&t;/* DTR complement */
multiline_comment|/*&n; * These are the definitions for the Modem Status Register&n; */
DECL|macro|UART_MSR_DCD
mdefine_line|#define UART_MSR_DCD&t;0x80&t;/* Data Carrier Detect */
DECL|macro|UART_MSR_RI
mdefine_line|#define UART_MSR_RI&t;0x40&t;/* Ring Indicator */
DECL|macro|UART_MSR_DSR
mdefine_line|#define UART_MSR_DSR&t;0x20&t;/* Data Set Ready */
DECL|macro|UART_MSR_CTS
mdefine_line|#define UART_MSR_CTS&t;0x10&t;/* Clear to Send */
DECL|macro|UART_MSR_DDCD
mdefine_line|#define UART_MSR_DDCD&t;0x08&t;/* Delta DCD */
DECL|macro|UART_MSR_TERI
mdefine_line|#define UART_MSR_TERI&t;0x04&t;/* Trailing edge ring indicator */
DECL|macro|UART_MSR_DDSR
mdefine_line|#define UART_MSR_DDSR&t;0x02&t;/* Delta DSR */
DECL|macro|UART_MSR_DCTS
mdefine_line|#define UART_MSR_DCTS&t;0x01&t;/* Delta CTS */
DECL|macro|UART_MSR_ANY_DELTA
mdefine_line|#define UART_MSR_ANY_DELTA 0x0F&t;/* Any of the delta bits! */
multiline_comment|/* SSIO */
DECL|macro|SSI0_STATUS
mdefine_line|#define SSI0_STATUS                0xB1600000
DECL|macro|SSI_STATUS_BF
mdefine_line|#define SSI_STATUS_BF              (1&lt;&lt;4)
DECL|macro|SSI_STATUS_OF
mdefine_line|#define SSI_STATUS_OF              (1&lt;&lt;3)
DECL|macro|SSI_STATUS_UF
mdefine_line|#define SSI_STATUS_UF              (1&lt;&lt;2)
DECL|macro|SSI_STATUS_D
mdefine_line|#define SSI_STATUS_D               (1&lt;&lt;1)
DECL|macro|SSI_STATUS_B
mdefine_line|#define SSI_STATUS_B               (1&lt;&lt;0)
DECL|macro|SSI0_INT
mdefine_line|#define SSI0_INT                   0xB1600004
DECL|macro|SSI_INT_OI
mdefine_line|#define SSI_INT_OI                 (1&lt;&lt;3)
DECL|macro|SSI_INT_UI
mdefine_line|#define SSI_INT_UI                 (1&lt;&lt;2)
DECL|macro|SSI_INT_DI
mdefine_line|#define SSI_INT_DI                 (1&lt;&lt;1)
DECL|macro|SSI0_INT_ENABLE
mdefine_line|#define SSI0_INT_ENABLE            0xB1600008
DECL|macro|SSI_INTE_OIE
mdefine_line|#define SSI_INTE_OIE               (1&lt;&lt;3)
DECL|macro|SSI_INTE_UIE
mdefine_line|#define SSI_INTE_UIE               (1&lt;&lt;2)
DECL|macro|SSI_INTE_DIE
mdefine_line|#define SSI_INTE_DIE               (1&lt;&lt;1)
DECL|macro|SSI0_CONFIG
mdefine_line|#define SSI0_CONFIG                0xB1600020
DECL|macro|SSI_CONFIG_AO
mdefine_line|#define SSI_CONFIG_AO              (1&lt;&lt;24)
DECL|macro|SSI_CONFIG_DO
mdefine_line|#define SSI_CONFIG_DO              (1&lt;&lt;23)
DECL|macro|SSI_CONFIG_ALEN_BIT
mdefine_line|#define SSI_CONFIG_ALEN_BIT        20
DECL|macro|SSI_CONFIG_ALEN_MASK
mdefine_line|#define SSI_CONFIG_ALEN_MASK       (0x7&lt;&lt;20)
DECL|macro|SSI_CONFIG_DLEN_BIT
mdefine_line|#define SSI_CONFIG_DLEN_BIT        16
DECL|macro|SSI_CONFIG_DLEN_MASK
mdefine_line|#define SSI_CONFIG_DLEN_MASK       (0x7&lt;&lt;16)
DECL|macro|SSI_CONFIG_DD
mdefine_line|#define SSI_CONFIG_DD              (1&lt;&lt;11)
DECL|macro|SSI_CONFIG_AD
mdefine_line|#define SSI_CONFIG_AD              (1&lt;&lt;10)
DECL|macro|SSI_CONFIG_BM_BIT
mdefine_line|#define SSI_CONFIG_BM_BIT          8
DECL|macro|SSI_CONFIG_BM_MASK
mdefine_line|#define SSI_CONFIG_BM_MASK         (0x3&lt;&lt;8)
DECL|macro|SSI_CONFIG_CE
mdefine_line|#define SSI_CONFIG_CE              (1&lt;&lt;7)
DECL|macro|SSI_CONFIG_DP
mdefine_line|#define SSI_CONFIG_DP              (1&lt;&lt;6)
DECL|macro|SSI_CONFIG_DL
mdefine_line|#define SSI_CONFIG_DL              (1&lt;&lt;5)
DECL|macro|SSI_CONFIG_EP
mdefine_line|#define SSI_CONFIG_EP              (1&lt;&lt;4)
DECL|macro|SSI0_ADATA
mdefine_line|#define SSI0_ADATA                 0xB1600024
DECL|macro|SSI_AD_D
mdefine_line|#define SSI_AD_D                   (1&lt;&lt;24)
DECL|macro|SSI_AD_ADDR_BIT
mdefine_line|#define SSI_AD_ADDR_BIT            16
DECL|macro|SSI_AD_ADDR_MASK
mdefine_line|#define SSI_AD_ADDR_MASK           (0xff&lt;&lt;16)
DECL|macro|SSI_AD_DATA_BIT
mdefine_line|#define SSI_AD_DATA_BIT            0
DECL|macro|SSI_AD_DATA_MASK
mdefine_line|#define SSI_AD_DATA_MASK           (0xfff&lt;&lt;0)
DECL|macro|SSI0_CLKDIV
mdefine_line|#define SSI0_CLKDIV                0xB1600028
DECL|macro|SSI0_CONTROL
mdefine_line|#define SSI0_CONTROL               0xB1600100
DECL|macro|SSI_CONTROL_CD
mdefine_line|#define SSI_CONTROL_CD             (1&lt;&lt;1)
DECL|macro|SSI_CONTROL_E
mdefine_line|#define SSI_CONTROL_E              (1&lt;&lt;0)
multiline_comment|/* SSI1 */
DECL|macro|SSI1_STATUS
mdefine_line|#define SSI1_STATUS                0xB1680000
DECL|macro|SSI1_INT
mdefine_line|#define SSI1_INT                   0xB1680004
DECL|macro|SSI1_INT_ENABLE
mdefine_line|#define SSI1_INT_ENABLE            0xB1680008
DECL|macro|SSI1_CONFIG
mdefine_line|#define SSI1_CONFIG                0xB1680020
DECL|macro|SSI1_ADATA
mdefine_line|#define SSI1_ADATA                 0xB1680024
DECL|macro|SSI1_CLKDIV
mdefine_line|#define SSI1_CLKDIV                0xB1680028
DECL|macro|SSI1_ENABLE
mdefine_line|#define SSI1_ENABLE                0xB1680100
multiline_comment|/*&n; * Register content definitions&n; */
DECL|macro|SSI_STATUS_BF
mdefine_line|#define SSI_STATUS_BF&t;&t;&t;&t;(1&lt;&lt;4)
DECL|macro|SSI_STATUS_OF
mdefine_line|#define SSI_STATUS_OF&t;&t;&t;&t;(1&lt;&lt;3)
DECL|macro|SSI_STATUS_UF
mdefine_line|#define SSI_STATUS_UF&t;&t;&t;&t;(1&lt;&lt;2)
DECL|macro|SSI_STATUS_D
mdefine_line|#define SSI_STATUS_D&t;&t;&t;&t;(1&lt;&lt;1)
DECL|macro|SSI_STATUS_B
mdefine_line|#define SSI_STATUS_B&t;&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/* SSI_INT */
DECL|macro|SSI_INT_OI
mdefine_line|#define SSI_INT_OI&t;&t;&t;&t;&t;(1&lt;&lt;3)
DECL|macro|SSI_INT_UI
mdefine_line|#define SSI_INT_UI&t;&t;&t;&t;&t;(1&lt;&lt;2)
DECL|macro|SSI_INT_DI
mdefine_line|#define SSI_INT_DI&t;&t;&t;&t;&t;(1&lt;&lt;1)
multiline_comment|/* SSI_INTEN */
DECL|macro|SSI_INTEN_OIE
mdefine_line|#define SSI_INTEN_OIE&t;&t;&t;&t;(1&lt;&lt;3)
DECL|macro|SSI_INTEN_UIE
mdefine_line|#define SSI_INTEN_UIE&t;&t;&t;&t;(1&lt;&lt;2)
DECL|macro|SSI_INTEN_DIE
mdefine_line|#define SSI_INTEN_DIE&t;&t;&t;&t;(1&lt;&lt;1)
DECL|macro|SSI_CONFIG_AO
mdefine_line|#define SSI_CONFIG_AO&t;&t;&t;&t;(1&lt;&lt;24)
DECL|macro|SSI_CONFIG_DO
mdefine_line|#define SSI_CONFIG_DO&t;&t;&t;&t;(1&lt;&lt;23)
DECL|macro|SSI_CONFIG_ALEN
mdefine_line|#define SSI_CONFIG_ALEN&t;&t;&t;&t;(7&lt;&lt;20)
DECL|macro|SSI_CONFIG_DLEN
mdefine_line|#define SSI_CONFIG_DLEN&t;&t;&t;&t;(15&lt;&lt;16)
DECL|macro|SSI_CONFIG_DD
mdefine_line|#define SSI_CONFIG_DD&t;&t;&t;&t;(1&lt;&lt;11)
DECL|macro|SSI_CONFIG_AD
mdefine_line|#define SSI_CONFIG_AD&t;&t;&t;&t;(1&lt;&lt;10)
DECL|macro|SSI_CONFIG_BM
mdefine_line|#define SSI_CONFIG_BM&t;&t;&t;&t;(3&lt;&lt;8)
DECL|macro|SSI_CONFIG_CE
mdefine_line|#define SSI_CONFIG_CE&t;&t;&t;&t;(1&lt;&lt;7)
DECL|macro|SSI_CONFIG_DP
mdefine_line|#define SSI_CONFIG_DP&t;&t;&t;&t;(1&lt;&lt;6)
DECL|macro|SSI_CONFIG_DL
mdefine_line|#define SSI_CONFIG_DL&t;&t;&t;&t;(1&lt;&lt;5)
DECL|macro|SSI_CONFIG_EP
mdefine_line|#define SSI_CONFIG_EP&t;&t;&t;&t;(1&lt;&lt;4)
DECL|macro|SSI_CONFIG_ALEN_N
mdefine_line|#define SSI_CONFIG_ALEN_N(N)&t;&t;((N-1)&lt;&lt;20)
DECL|macro|SSI_CONFIG_DLEN_N
mdefine_line|#define SSI_CONFIG_DLEN_N(N)&t;&t;((N-1)&lt;&lt;16)
DECL|macro|SSI_CONFIG_BM_HI
mdefine_line|#define SSI_CONFIG_BM_HI&t;&t;&t;(0&lt;&lt;8)
DECL|macro|SSI_CONFIG_BM_LO
mdefine_line|#define SSI_CONFIG_BM_LO&t;&t;&t;(1&lt;&lt;8)
DECL|macro|SSI_CONFIG_BM_CY
mdefine_line|#define SSI_CONFIG_BM_CY&t;&t;&t;(2&lt;&lt;8)
DECL|macro|SSI_ADATA_D
mdefine_line|#define SSI_ADATA_D&t;&t;&t;&t;&t;(1&lt;&lt;24)
DECL|macro|SSI_ADATA_ADDR
mdefine_line|#define SSI_ADATA_ADDR&t;&t;&t;&t;(0xFF&lt;&lt;16)
DECL|macro|SSI_ADATA_DATA
mdefine_line|#define SSI_ADATA_DATA&t;&t;&t;&t;(0x0FFF)
DECL|macro|SSI_ADATA_ADDR_N
mdefine_line|#define SSI_ADATA_ADDR_N(N)&t;&t;&t;(N&lt;&lt;16)
DECL|macro|SSI_ENABLE_CD
mdefine_line|#define SSI_ENABLE_CD&t;&t;&t;&t;(1&lt;&lt;1)
DECL|macro|SSI_ENABLE_E
mdefine_line|#define SSI_ENABLE_E&t;&t;&t;&t;(1&lt;&lt;0)
multiline_comment|/* IrDA Controller */
DECL|macro|IRDA_BASE
mdefine_line|#define IRDA_BASE                 0xB0300000
DECL|macro|IR_RING_PTR_STATUS
mdefine_line|#define IR_RING_PTR_STATUS        (IRDA_BASE+0x00)
DECL|macro|IR_RING_BASE_ADDR_H
mdefine_line|#define IR_RING_BASE_ADDR_H       (IRDA_BASE+0x04)
DECL|macro|IR_RING_BASE_ADDR_L
mdefine_line|#define IR_RING_BASE_ADDR_L       (IRDA_BASE+0x08)
DECL|macro|IR_RING_SIZE
mdefine_line|#define IR_RING_SIZE              (IRDA_BASE+0x0C)
DECL|macro|IR_RING_PROMPT
mdefine_line|#define IR_RING_PROMPT            (IRDA_BASE+0x10)
DECL|macro|IR_RING_ADDR_CMPR
mdefine_line|#define IR_RING_ADDR_CMPR         (IRDA_BASE+0x14)
DECL|macro|IR_INT_CLEAR
mdefine_line|#define IR_INT_CLEAR              (IRDA_BASE+0x18)
DECL|macro|IR_CONFIG_1
mdefine_line|#define IR_CONFIG_1               (IRDA_BASE+0x20)
DECL|macro|IR_RX_INVERT_LED
mdefine_line|#define IR_RX_INVERT_LED        (1&lt;&lt;0)
DECL|macro|IR_TX_INVERT_LED
mdefine_line|#define IR_TX_INVERT_LED        (1&lt;&lt;1)
DECL|macro|IR_ST
mdefine_line|#define IR_ST                   (1&lt;&lt;2)
DECL|macro|IR_SF
mdefine_line|#define IR_SF                   (1&lt;&lt;3)
DECL|macro|IR_SIR
mdefine_line|#define IR_SIR                  (1&lt;&lt;4)
DECL|macro|IR_MIR
mdefine_line|#define IR_MIR                  (1&lt;&lt;5)
DECL|macro|IR_FIR
mdefine_line|#define IR_FIR                  (1&lt;&lt;6)
DECL|macro|IR_16CRC
mdefine_line|#define IR_16CRC                (1&lt;&lt;7)
DECL|macro|IR_TD
mdefine_line|#define IR_TD                   (1&lt;&lt;8)
DECL|macro|IR_RX_ALL
mdefine_line|#define IR_RX_ALL               (1&lt;&lt;9)
DECL|macro|IR_DMA_ENABLE
mdefine_line|#define IR_DMA_ENABLE           (1&lt;&lt;10)
DECL|macro|IR_RX_ENABLE
mdefine_line|#define IR_RX_ENABLE            (1&lt;&lt;11)
DECL|macro|IR_TX_ENABLE
mdefine_line|#define IR_TX_ENABLE            (1&lt;&lt;12)
DECL|macro|IR_LOOPBACK
mdefine_line|#define IR_LOOPBACK             (1&lt;&lt;14)
DECL|macro|IR_SIR_MODE
mdefine_line|#define IR_SIR_MODE&t;          (IR_SIR | IR_DMA_ENABLE | &bslash;&n;&t;&t;                   IR_RX_ALL | IR_RX_ENABLE | IR_SF | IR_16CRC)
DECL|macro|IR_SIR_FLAGS
mdefine_line|#define IR_SIR_FLAGS              (IRDA_BASE+0x24)
DECL|macro|IR_ENABLE
mdefine_line|#define IR_ENABLE                 (IRDA_BASE+0x28)
DECL|macro|IR_RX_STATUS
mdefine_line|#define IR_RX_STATUS            (1&lt;&lt;9)
DECL|macro|IR_TX_STATUS
mdefine_line|#define IR_TX_STATUS            (1&lt;&lt;10)
DECL|macro|IR_READ_PHY_CONFIG
mdefine_line|#define IR_READ_PHY_CONFIG        (IRDA_BASE+0x2C)
DECL|macro|IR_WRITE_PHY_CONFIG
mdefine_line|#define IR_WRITE_PHY_CONFIG       (IRDA_BASE+0x30)
DECL|macro|IR_MAX_PKT_LEN
mdefine_line|#define IR_MAX_PKT_LEN            (IRDA_BASE+0x34)
DECL|macro|IR_RX_BYTE_CNT
mdefine_line|#define IR_RX_BYTE_CNT            (IRDA_BASE+0x38)
DECL|macro|IR_CONFIG_2
mdefine_line|#define IR_CONFIG_2               (IRDA_BASE+0x3C)
DECL|macro|IR_MODE_INV
mdefine_line|#define IR_MODE_INV             (1&lt;&lt;0)
DECL|macro|IR_ONE_PIN
mdefine_line|#define IR_ONE_PIN              (1&lt;&lt;1)
DECL|macro|IR_INTERFACE_CONFIG
mdefine_line|#define IR_INTERFACE_CONFIG       (IRDA_BASE+0x40)
multiline_comment|/* GPIO */
DECL|macro|SYS_PINFUNC
mdefine_line|#define SYS_PINFUNC               0xB190002C
DECL|macro|SYS_PF_USB
mdefine_line|#define SYS_PF_USB&t;&t;&t;(1&lt;&lt;15)&t;/* 2nd USB device/host */
DECL|macro|SYS_PF_U3
mdefine_line|#define SYS_PF_U3&t;&t;&t;(1&lt;&lt;14)&t;/* GPIO23/U3TXD */
DECL|macro|SYS_PF_U2
mdefine_line|#define SYS_PF_U2&t;&t;&t;(1&lt;&lt;13) /* GPIO22/U2TXD */
DECL|macro|SYS_PF_U1
mdefine_line|#define SYS_PF_U1&t;&t;&t;(1&lt;&lt;12) /* GPIO21/U1TXD */
DECL|macro|SYS_PF_SRC
mdefine_line|#define SYS_PF_SRC&t;&t;&t;(1&lt;&lt;11)&t;/* GPIO6/SROMCKE */
DECL|macro|SYS_PF_CK5
mdefine_line|#define SYS_PF_CK5&t;&t;&t;(1&lt;&lt;10)&t;/* GPIO3/CLK5 */
DECL|macro|SYS_PF_CK4
mdefine_line|#define SYS_PF_CK4&t;&t;&t;(1&lt;&lt;9)&t;/* GPIO2/CLK4 */
DECL|macro|SYS_PF_IRF
mdefine_line|#define SYS_PF_IRF&t;&t;&t;(1&lt;&lt;8)&t;/* GPIO15/IRFIRSEL */
DECL|macro|SYS_PF_UR3
mdefine_line|#define SYS_PF_UR3&t;&t;&t;(1&lt;&lt;7)&t;/* GPIO[14:9]/UART3 */
DECL|macro|SYS_PF_I2D
mdefine_line|#define SYS_PF_I2D&t;&t;&t;(1&lt;&lt;6)&t;/* GPIO8/I2SDI */
DECL|macro|SYS_PF_I2S
mdefine_line|#define SYS_PF_I2S&t;&t;&t;(1&lt;&lt;5)&t;/* I2S/GPIO[29:31] */
DECL|macro|SYS_PF_NI2
mdefine_line|#define SYS_PF_NI2&t;&t;&t;(1&lt;&lt;4)&t;/* NI2/GPIO[24:28] */
DECL|macro|SYS_PF_U0
mdefine_line|#define SYS_PF_U0&t;&t;&t;(1&lt;&lt;3)&t;/* U0TXD/GPIO20 */
DECL|macro|SYS_PF_RD
mdefine_line|#define SYS_PF_RD&t;&t;&t;(1&lt;&lt;2)&t;/* IRTXD/GPIO19 */
DECL|macro|SYS_PF_A97
mdefine_line|#define SYS_PF_A97&t;&t;&t;(1&lt;&lt;1)&t;/* AC97/SSL1 */
DECL|macro|SYS_PF_S0
mdefine_line|#define SYS_PF_S0&t;&t;&t;(1&lt;&lt;0)&t;/* SSI_0/GPIO[16:18] */
multiline_comment|/* Au1100 Only */
DECL|macro|SYS_PF_PC
mdefine_line|#define SYS_PF_PC&t;&t;&t;(1&lt;&lt;18)&t;/* PCMCIA/GPIO[207:204] */
DECL|macro|SYS_PF_LCD
mdefine_line|#define SYS_PF_LCD&t;&t;&t;(1&lt;&lt;17)&t;/* extern lcd/GPIO[203:200] */
DECL|macro|SYS_PF_CS
mdefine_line|#define SYS_PF_CS&t;&t;&t;(1&lt;&lt;16)&t;/* EXTCLK0/32khz to gpio2 */
DECL|macro|SYS_PF_EX0
mdefine_line|#define SYS_PF_EX0&t;&t;&t;(1&lt;&lt;9)&t;/* gpio2/clock */
multiline_comment|/* Au1550 Only.  Redefines lots of pins */
DECL|macro|SYS_PF_PSC2_MASK
mdefine_line|#define SYS_PF_PSC2_MASK&t;&t;(7 &lt;&lt; 17)
DECL|macro|SYS_PF_PSC2_AC97
mdefine_line|#define SYS_PF_PSC2_AC97&t;&t;(0)
DECL|macro|SYS_PF_PSC2_SPI
mdefine_line|#define SYS_PF_PSC2_SPI&t;&t;(0)
DECL|macro|SYS_PF_PSC2_I2S
mdefine_line|#define SYS_PF_PSC2_I2S&t;&t;(1 &lt;&lt; 17)
DECL|macro|SYS_PF_PSC2_SMBUS
mdefine_line|#define SYS_PF_PSC2_SMBUS&t;&t;(3 &lt;&lt; 17)
DECL|macro|SYS_PF_PSC2_GPIO
mdefine_line|#define SYS_PF_PSC2_GPIO&t;&t;(7 &lt;&lt; 17)
DECL|macro|SYS_PF_PSC3_MASK
mdefine_line|#define SYS_PF_PSC3_MASK&t;&t;(7 &lt;&lt; 20)
DECL|macro|SYS_PF_PSC3_AC97
mdefine_line|#define SYS_PF_PSC3_AC97&t;&t;(0)
DECL|macro|SYS_PF_PSC3_SPI
mdefine_line|#define SYS_PF_PSC3_SPI&t;&t;(0)
DECL|macro|SYS_PF_PSC3_I2S
mdefine_line|#define SYS_PF_PSC3_I2S&t;&t;(1 &lt;&lt; 20)
DECL|macro|SYS_PF_PSC3_SMBUS
mdefine_line|#define SYS_PF_PSC3_SMBUS&t;&t;(3 &lt;&lt; 20)
DECL|macro|SYS_PF_PSC3_GPIO
mdefine_line|#define SYS_PF_PSC3_GPIO&t;&t;(7 &lt;&lt; 20)
DECL|macro|SYS_PF_PSC1_S1
mdefine_line|#define SYS_PF_PSC1_S1&t;&t;(1 &lt;&lt; 1)
DECL|macro|SYS_PF_MUST_BE_SET
mdefine_line|#define SYS_PF_MUST_BE_SET&t;&t;((1 &lt;&lt; 5) | (1 &lt;&lt; 2))
DECL|macro|SYS_TRIOUTRD
mdefine_line|#define SYS_TRIOUTRD              0xB1900100
DECL|macro|SYS_TRIOUTCLR
mdefine_line|#define SYS_TRIOUTCLR             0xB1900100
DECL|macro|SYS_OUTPUTRD
mdefine_line|#define SYS_OUTPUTRD              0xB1900108
DECL|macro|SYS_OUTPUTSET
mdefine_line|#define SYS_OUTPUTSET             0xB1900108
DECL|macro|SYS_OUTPUTCLR
mdefine_line|#define SYS_OUTPUTCLR             0xB190010C
DECL|macro|SYS_PINSTATERD
mdefine_line|#define SYS_PINSTATERD            0xB1900110
DECL|macro|SYS_PININPUTEN
mdefine_line|#define SYS_PININPUTEN            0xB1900110
multiline_comment|/* GPIO2, Au1500, Au1550 only */
DECL|macro|GPIO2_BASE
mdefine_line|#define GPIO2_BASE                0xB1700000
DECL|macro|GPIO2_DIR
mdefine_line|#define GPIO2_DIR                 (GPIO2_BASE + 0)
DECL|macro|GPIO2_OUTPUT
mdefine_line|#define GPIO2_OUTPUT              (GPIO2_BASE + 8)
DECL|macro|GPIO2_PINSTATE
mdefine_line|#define GPIO2_PINSTATE            (GPIO2_BASE + 0xC)
DECL|macro|GPIO2_INTENABLE
mdefine_line|#define GPIO2_INTENABLE           (GPIO2_BASE + 0x10)
DECL|macro|GPIO2_ENABLE
mdefine_line|#define GPIO2_ENABLE              (GPIO2_BASE + 0x14)
multiline_comment|/* Power Management */
DECL|macro|SYS_SCRATCH0
mdefine_line|#define SYS_SCRATCH0              0xB1900018
DECL|macro|SYS_SCRATCH1
mdefine_line|#define SYS_SCRATCH1              0xB190001C
DECL|macro|SYS_WAKEMSK
mdefine_line|#define SYS_WAKEMSK               0xB1900034
DECL|macro|SYS_ENDIAN
mdefine_line|#define SYS_ENDIAN                0xB1900038
DECL|macro|SYS_POWERCTRL
mdefine_line|#define SYS_POWERCTRL             0xB190003C
DECL|macro|SYS_WAKESRC
mdefine_line|#define SYS_WAKESRC               0xB190005C
DECL|macro|SYS_SLPPWR
mdefine_line|#define SYS_SLPPWR                0xB1900078
DECL|macro|SYS_SLEEP
mdefine_line|#define SYS_SLEEP                 0xB190007C
multiline_comment|/* Clock Controller */
DECL|macro|SYS_FREQCTRL0
mdefine_line|#define SYS_FREQCTRL0             0xB1900020
DECL|macro|SYS_FC_FRDIV2_BIT
mdefine_line|#define SYS_FC_FRDIV2_BIT         22
DECL|macro|SYS_FC_FRDIV2_MASK
mdefine_line|#define SYS_FC_FRDIV2_MASK        (0xff &lt;&lt; SYS_FC_FRDIV2_BIT)
DECL|macro|SYS_FC_FE2
mdefine_line|#define SYS_FC_FE2                (1&lt;&lt;21)
DECL|macro|SYS_FC_FS2
mdefine_line|#define SYS_FC_FS2                (1&lt;&lt;20)
DECL|macro|SYS_FC_FRDIV1_BIT
mdefine_line|#define SYS_FC_FRDIV1_BIT         12
DECL|macro|SYS_FC_FRDIV1_MASK
mdefine_line|#define SYS_FC_FRDIV1_MASK        (0xff &lt;&lt; SYS_FC_FRDIV1_BIT)
DECL|macro|SYS_FC_FE1
mdefine_line|#define SYS_FC_FE1                (1&lt;&lt;11)
DECL|macro|SYS_FC_FS1
mdefine_line|#define SYS_FC_FS1                (1&lt;&lt;10)
DECL|macro|SYS_FC_FRDIV0_BIT
mdefine_line|#define SYS_FC_FRDIV0_BIT         2
DECL|macro|SYS_FC_FRDIV0_MASK
mdefine_line|#define SYS_FC_FRDIV0_MASK        (0xff &lt;&lt; SYS_FC_FRDIV0_BIT)
DECL|macro|SYS_FC_FE0
mdefine_line|#define SYS_FC_FE0                (1&lt;&lt;1)
DECL|macro|SYS_FC_FS0
mdefine_line|#define SYS_FC_FS0                (1&lt;&lt;0)
DECL|macro|SYS_FREQCTRL1
mdefine_line|#define SYS_FREQCTRL1             0xB1900024
DECL|macro|SYS_FC_FRDIV5_BIT
mdefine_line|#define SYS_FC_FRDIV5_BIT         22
DECL|macro|SYS_FC_FRDIV5_MASK
mdefine_line|#define SYS_FC_FRDIV5_MASK        (0xff &lt;&lt; SYS_FC_FRDIV5_BIT)
DECL|macro|SYS_FC_FE5
mdefine_line|#define SYS_FC_FE5                (1&lt;&lt;21)
DECL|macro|SYS_FC_FS5
mdefine_line|#define SYS_FC_FS5                (1&lt;&lt;20)
DECL|macro|SYS_FC_FRDIV4_BIT
mdefine_line|#define SYS_FC_FRDIV4_BIT         12
DECL|macro|SYS_FC_FRDIV4_MASK
mdefine_line|#define SYS_FC_FRDIV4_MASK        (0xff &lt;&lt; SYS_FC_FRDIV4_BIT)
DECL|macro|SYS_FC_FE4
mdefine_line|#define SYS_FC_FE4                (1&lt;&lt;11)
DECL|macro|SYS_FC_FS4
mdefine_line|#define SYS_FC_FS4                (1&lt;&lt;10)
DECL|macro|SYS_FC_FRDIV3_BIT
mdefine_line|#define SYS_FC_FRDIV3_BIT         2
DECL|macro|SYS_FC_FRDIV3_MASK
mdefine_line|#define SYS_FC_FRDIV3_MASK        (0xff &lt;&lt; SYS_FC_FRDIV3_BIT)
DECL|macro|SYS_FC_FE3
mdefine_line|#define SYS_FC_FE3                (1&lt;&lt;1)
DECL|macro|SYS_FC_FS3
mdefine_line|#define SYS_FC_FS3                (1&lt;&lt;0)
DECL|macro|SYS_CLKSRC
mdefine_line|#define SYS_CLKSRC                0xB1900028
DECL|macro|SYS_CS_ME1_BIT
mdefine_line|#define SYS_CS_ME1_BIT            27
DECL|macro|SYS_CS_ME1_MASK
mdefine_line|#define SYS_CS_ME1_MASK           (0x7&lt;&lt;SYS_CS_ME1_BIT)
DECL|macro|SYS_CS_DE1
mdefine_line|#define SYS_CS_DE1                (1&lt;&lt;26)
DECL|macro|SYS_CS_CE1
mdefine_line|#define SYS_CS_CE1                (1&lt;&lt;25)
DECL|macro|SYS_CS_ME0_BIT
mdefine_line|#define SYS_CS_ME0_BIT            22
DECL|macro|SYS_CS_ME0_MASK
mdefine_line|#define SYS_CS_ME0_MASK           (0x7&lt;&lt;SYS_CS_ME0_BIT)
DECL|macro|SYS_CS_DE0
mdefine_line|#define SYS_CS_DE0                (1&lt;&lt;21)
DECL|macro|SYS_CS_CE0
mdefine_line|#define SYS_CS_CE0                (1&lt;&lt;20)
DECL|macro|SYS_CS_MI2_BIT
mdefine_line|#define SYS_CS_MI2_BIT            17
DECL|macro|SYS_CS_MI2_MASK
mdefine_line|#define SYS_CS_MI2_MASK           (0x7&lt;&lt;SYS_CS_MI2_BIT)
DECL|macro|SYS_CS_DI2
mdefine_line|#define SYS_CS_DI2                (1&lt;&lt;16)
DECL|macro|SYS_CS_CI2
mdefine_line|#define SYS_CS_CI2                (1&lt;&lt;15)
DECL|macro|SYS_CS_MUH_BIT
mdefine_line|#define SYS_CS_MUH_BIT            12
DECL|macro|SYS_CS_MUH_MASK
mdefine_line|#define SYS_CS_MUH_MASK           (0x7&lt;&lt;SYS_CS_MUH_BIT)
DECL|macro|SYS_CS_DUH
mdefine_line|#define SYS_CS_DUH                (1&lt;&lt;11)
DECL|macro|SYS_CS_CUH
mdefine_line|#define SYS_CS_CUH                (1&lt;&lt;10)
DECL|macro|SYS_CS_MUD_BIT
mdefine_line|#define SYS_CS_MUD_BIT            7
DECL|macro|SYS_CS_MUD_MASK
mdefine_line|#define SYS_CS_MUD_MASK           (0x7&lt;&lt;SYS_CS_MUD_BIT)
DECL|macro|SYS_CS_DUD
mdefine_line|#define SYS_CS_DUD                (1&lt;&lt;6)
DECL|macro|SYS_CS_CUD
mdefine_line|#define SYS_CS_CUD                (1&lt;&lt;5)
DECL|macro|SYS_CS_MIR_BIT
mdefine_line|#define SYS_CS_MIR_BIT            2
DECL|macro|SYS_CS_MIR_MASK
mdefine_line|#define SYS_CS_MIR_MASK           (0x7&lt;&lt;SYS_CS_MIR_BIT)
DECL|macro|SYS_CS_DIR
mdefine_line|#define SYS_CS_DIR                (1&lt;&lt;1)
DECL|macro|SYS_CS_CIR
mdefine_line|#define SYS_CS_CIR                (1&lt;&lt;0)
DECL|macro|SYS_CS_MUX_AUX
mdefine_line|#define SYS_CS_MUX_AUX            0x1
DECL|macro|SYS_CS_MUX_FQ0
mdefine_line|#define SYS_CS_MUX_FQ0            0x2
DECL|macro|SYS_CS_MUX_FQ1
mdefine_line|#define SYS_CS_MUX_FQ1            0x3
DECL|macro|SYS_CS_MUX_FQ2
mdefine_line|#define SYS_CS_MUX_FQ2            0x4
DECL|macro|SYS_CS_MUX_FQ3
mdefine_line|#define SYS_CS_MUX_FQ3            0x5
DECL|macro|SYS_CS_MUX_FQ4
mdefine_line|#define SYS_CS_MUX_FQ4            0x6
DECL|macro|SYS_CS_MUX_FQ5
mdefine_line|#define SYS_CS_MUX_FQ5            0x7
DECL|macro|SYS_CPUPLL
mdefine_line|#define SYS_CPUPLL                0xB1900060
DECL|macro|SYS_AUXPLL
mdefine_line|#define SYS_AUXPLL                0xB1900064
multiline_comment|/* AC97 Controller */
DECL|macro|AC97C_CONFIG
mdefine_line|#define AC97C_CONFIG              0xB0000000
DECL|macro|AC97C_RECV_SLOTS_BIT
mdefine_line|#define AC97C_RECV_SLOTS_BIT  13
DECL|macro|AC97C_RECV_SLOTS_MASK
mdefine_line|#define AC97C_RECV_SLOTS_MASK (0x3ff &lt;&lt; AC97C_RECV_SLOTS_BIT)
DECL|macro|AC97C_XMIT_SLOTS_BIT
mdefine_line|#define AC97C_XMIT_SLOTS_BIT  3
DECL|macro|AC97C_XMIT_SLOTS_MASK
mdefine_line|#define AC97C_XMIT_SLOTS_MASK (0x3ff &lt;&lt; AC97C_XMIT_SLOTS_BIT)
DECL|macro|AC97C_SG
mdefine_line|#define AC97C_SG              (1&lt;&lt;2)
DECL|macro|AC97C_SYNC
mdefine_line|#define AC97C_SYNC            (1&lt;&lt;1)
DECL|macro|AC97C_RESET
mdefine_line|#define AC97C_RESET           (1&lt;&lt;0)
DECL|macro|AC97C_STATUS
mdefine_line|#define AC97C_STATUS              0xB0000004
DECL|macro|AC97C_XU
mdefine_line|#define AC97C_XU              (1&lt;&lt;11)
DECL|macro|AC97C_XO
mdefine_line|#define AC97C_XO              (1&lt;&lt;10)
DECL|macro|AC97C_RU
mdefine_line|#define AC97C_RU              (1&lt;&lt;9)
DECL|macro|AC97C_RO
mdefine_line|#define AC97C_RO              (1&lt;&lt;8)
DECL|macro|AC97C_READY
mdefine_line|#define AC97C_READY           (1&lt;&lt;7)
DECL|macro|AC97C_CP
mdefine_line|#define AC97C_CP              (1&lt;&lt;6)
DECL|macro|AC97C_TR
mdefine_line|#define AC97C_TR              (1&lt;&lt;5)
DECL|macro|AC97C_TE
mdefine_line|#define AC97C_TE              (1&lt;&lt;4)
DECL|macro|AC97C_TF
mdefine_line|#define AC97C_TF              (1&lt;&lt;3)
DECL|macro|AC97C_RR
mdefine_line|#define AC97C_RR              (1&lt;&lt;2)
DECL|macro|AC97C_RE
mdefine_line|#define AC97C_RE              (1&lt;&lt;1)
DECL|macro|AC97C_RF
mdefine_line|#define AC97C_RF              (1&lt;&lt;0)
DECL|macro|AC97C_DATA
mdefine_line|#define AC97C_DATA                0xB0000008
DECL|macro|AC97C_CMD
mdefine_line|#define AC97C_CMD                 0xB000000C
DECL|macro|AC97C_WD_BIT
mdefine_line|#define AC97C_WD_BIT          16
DECL|macro|AC97C_READ
mdefine_line|#define AC97C_READ            (1&lt;&lt;7)
DECL|macro|AC97C_INDEX_MASK
mdefine_line|#define AC97C_INDEX_MASK      0x7f
DECL|macro|AC97C_CNTRL
mdefine_line|#define AC97C_CNTRL               0xB0000010
DECL|macro|AC97C_RS
mdefine_line|#define AC97C_RS              (1&lt;&lt;1)
DECL|macro|AC97C_CE
mdefine_line|#define AC97C_CE              (1&lt;&lt;0)
multiline_comment|/* Secure Digital (SD) Controller */
DECL|macro|SD0_XMIT_FIFO
mdefine_line|#define SD0_XMIT_FIFO&t;0xB0600000
DECL|macro|SD0_RECV_FIFO
mdefine_line|#define SD0_RECV_FIFO&t;0xB0600004
DECL|macro|SD1_XMIT_FIFO
mdefine_line|#define SD1_XMIT_FIFO&t;0xB0680000
DECL|macro|SD1_RECV_FIFO
mdefine_line|#define SD1_RECV_FIFO&t;0xB0680004
macro_line|#if defined (CONFIG_SOC_AU1500) || defined(CONFIG_SOC_AU1550)
multiline_comment|/* Au1500 PCI Controller */
DECL|macro|Au1500_CFG_BASE
mdefine_line|#define Au1500_CFG_BASE           0xB4005000 
singleline_comment|// virtual, kseg0 addr
DECL|macro|Au1500_PCI_CMEM
mdefine_line|#define Au1500_PCI_CMEM           (Au1500_CFG_BASE + 0)
DECL|macro|Au1500_PCI_CFG
mdefine_line|#define Au1500_PCI_CFG            (Au1500_CFG_BASE + 4)
DECL|macro|PCI_ERROR
mdefine_line|#define PCI_ERROR ((1&lt;&lt;22) | (1&lt;&lt;23) | (1&lt;&lt;24) | (1&lt;&lt;25) | (1&lt;&lt;26) | (1&lt;&lt;27))
DECL|macro|Au1500_PCI_B2BMASK_CCH
mdefine_line|#define Au1500_PCI_B2BMASK_CCH    (Au1500_CFG_BASE + 8)
DECL|macro|Au1500_PCI_B2B0_VID
mdefine_line|#define Au1500_PCI_B2B0_VID       (Au1500_CFG_BASE + 0xC)
DECL|macro|Au1500_PCI_B2B1_ID
mdefine_line|#define Au1500_PCI_B2B1_ID        (Au1500_CFG_BASE + 0x10)
DECL|macro|Au1500_PCI_MWMASK_DEV
mdefine_line|#define Au1500_PCI_MWMASK_DEV     (Au1500_CFG_BASE + 0x14)
DECL|macro|Au1500_PCI_MWBASE_REV_CCL
mdefine_line|#define Au1500_PCI_MWBASE_REV_CCL (Au1500_CFG_BASE + 0x18)
DECL|macro|Au1500_PCI_ERR_ADDR
mdefine_line|#define Au1500_PCI_ERR_ADDR       (Au1500_CFG_BASE + 0x1C)
DECL|macro|Au1500_PCI_SPEC_INTACK
mdefine_line|#define Au1500_PCI_SPEC_INTACK    (Au1500_CFG_BASE + 0x20)
DECL|macro|Au1500_PCI_ID
mdefine_line|#define Au1500_PCI_ID             (Au1500_CFG_BASE + 0x100)
DECL|macro|Au1500_PCI_STATCMD
mdefine_line|#define Au1500_PCI_STATCMD        (Au1500_CFG_BASE + 0x104)
DECL|macro|Au1500_PCI_CLASSREV
mdefine_line|#define Au1500_PCI_CLASSREV       (Au1500_CFG_BASE + 0x108)
DECL|macro|Au1500_PCI_HDRTYPE
mdefine_line|#define Au1500_PCI_HDRTYPE        (Au1500_CFG_BASE + 0x10C)
DECL|macro|Au1500_PCI_MBAR
mdefine_line|#define Au1500_PCI_MBAR           (Au1500_CFG_BASE + 0x110)
DECL|macro|Au1500_PCI_HDR
mdefine_line|#define Au1500_PCI_HDR            0xB4005100 
singleline_comment|// virtual, kseg0 addr
multiline_comment|/* All of our structures, like pci resource, have 32 bit members.&n; * Drivers are expected to do an ioremap on the PCI MEM resource, but it&squot;s&n; * hard to store 0x4 0000 0000 in a 32 bit type.  We require a small patch&n; * to __ioremap to check for addresses between (u32)Au1500_PCI_MEM_START and&n; * (u32)Au1500_PCI_MEM_END and change those to the full 36 bit PCI MEM&n; * addresses.  For PCI IO, it&squot;s simpler because we get to do the ioremap&n; * ourselves and then adjust the device&squot;s resources.&n; */
DECL|macro|Au1500_EXT_CFG
mdefine_line|#define Au1500_EXT_CFG            0x600000000ULL
DECL|macro|Au1500_EXT_CFG_TYPE1
mdefine_line|#define Au1500_EXT_CFG_TYPE1      0x680000000ULL
DECL|macro|Au1500_PCI_IO_START
mdefine_line|#define Au1500_PCI_IO_START       0x500000000ULL
DECL|macro|Au1500_PCI_IO_END
mdefine_line|#define Au1500_PCI_IO_END         0x5000FFFFFULL
DECL|macro|Au1500_PCI_MEM_START
mdefine_line|#define Au1500_PCI_MEM_START      0x440000000ULL
DECL|macro|Au1500_PCI_MEM_END
mdefine_line|#define Au1500_PCI_MEM_END        0x44FFFFFFFULL
DECL|macro|PCI_IO_START
mdefine_line|#define PCI_IO_START    (Au1500_PCI_IO_START + 0x1000)
DECL|macro|PCI_IO_END
mdefine_line|#define PCI_IO_END      (Au1500_PCI_IO_END)
DECL|macro|PCI_MEM_START
mdefine_line|#define PCI_MEM_START   (Au1500_PCI_MEM_START)
DECL|macro|PCI_MEM_END
mdefine_line|#define PCI_MEM_END     (Au1500_PCI_MEM_END)
DECL|macro|PCI_FIRST_DEVFN
mdefine_line|#define PCI_FIRST_DEVFN (0&lt;&lt;3)
DECL|macro|PCI_LAST_DEVFN
mdefine_line|#define PCI_LAST_DEVFN  (19&lt;&lt;3)
DECL|macro|IOPORT_RESOURCE_START
mdefine_line|#define IOPORT_RESOURCE_START 0x00001000 /* skip legacy probing */
DECL|macro|IOPORT_RESOURCE_END
mdefine_line|#define IOPORT_RESOURCE_END   0xffffffff
DECL|macro|IOMEM_RESOURCE_START
mdefine_line|#define IOMEM_RESOURCE_START  0x10000000
DECL|macro|IOMEM_RESOURCE_END
mdefine_line|#define IOMEM_RESOURCE_END    0xffffffff
multiline_comment|/*&n;   * Borrowed from the PPC arch:&n;   * The following macro is used to lookup irqs in a standard table&n;   * format for those PPC systems that do not already have PCI&n;   * interrupts properly routed.&n;   */
multiline_comment|/* FIXME - double check this from asm-ppc/pci-bridge.h */
DECL|macro|PCI_IRQ_TABLE_LOOKUP
mdefine_line|#define PCI_IRQ_TABLE_LOOKUP                            &bslash;&n;  ({ long _ctl_ = -1;                                 &bslash;&n;      if (idsel &gt;= min_idsel &amp;&amp; idsel &lt;= max_idsel &amp;&amp; pin &lt;= irqs_per_slot)    &bslash;&n;&t;       _ctl_ = pci_irq_table[idsel - min_idsel][pin-1];               &bslash;&n;&t;&t;      _ctl_; })
macro_line|#else /* Au1000 and Au1100 */
multiline_comment|/* don&squot;t allow any legacy ports probing */
DECL|macro|IOPORT_RESOURCE_START
mdefine_line|#define IOPORT_RESOURCE_START 0x10000000;
DECL|macro|IOPORT_RESOURCE_END
mdefine_line|#define IOPORT_RESOURCE_END   0xffffffff
DECL|macro|IOMEM_RESOURCE_START
mdefine_line|#define IOMEM_RESOURCE_START  0x10000000
DECL|macro|IOMEM_RESOURCE_END
mdefine_line|#define IOMEM_RESOURCE_END    0xffffffff
macro_line|#ifdef CONFIG_MIPS_PB1000
DECL|macro|PCI_IO_START
mdefine_line|#define PCI_IO_START      0x10000000
DECL|macro|PCI_IO_END
mdefine_line|#define PCI_IO_END        0x1000ffff
DECL|macro|PCI_MEM_START
mdefine_line|#define PCI_MEM_START     0x18000000
DECL|macro|PCI_MEM_END
mdefine_line|#define PCI_MEM_END       0x18ffffff
DECL|macro|PCI_FIRST_DEVFN
mdefine_line|#define PCI_FIRST_DEVFN   0
DECL|macro|PCI_LAST_DEVFN
mdefine_line|#define PCI_LAST_DEVFN    1
macro_line|#else
multiline_comment|/* no PCI bus controller */
DECL|macro|PCI_IO_START
mdefine_line|#define PCI_IO_START    0
DECL|macro|PCI_IO_END
mdefine_line|#define PCI_IO_END      0
DECL|macro|PCI_MEM_START
mdefine_line|#define PCI_MEM_START   0
DECL|macro|PCI_MEM_END
mdefine_line|#define PCI_MEM_END     0 
DECL|macro|PCI_FIRST_DEVFN
mdefine_line|#define PCI_FIRST_DEVFN 0
DECL|macro|PCI_LAST_DEVFN
mdefine_line|#define PCI_LAST_DEVFN  0
macro_line|#endif
macro_line|#endif
multiline_comment|/* Processor information base on prid.&n; * Copied from PowerPC.&n; */
DECL|struct|cpu_spec
r_struct
id|cpu_spec
(brace
multiline_comment|/* CPU is matched via (PRID &amp; prid_mask) == prid_value */
DECL|member|prid_mask
r_int
r_int
id|prid_mask
suffix:semicolon
DECL|member|prid_value
r_int
r_int
id|prid_value
suffix:semicolon
DECL|member|cpu_name
r_char
op_star
id|cpu_name
suffix:semicolon
DECL|member|cpu_od
r_int
r_char
id|cpu_od
suffix:semicolon
multiline_comment|/* Set Config[OD] */
DECL|member|cpu_bclk
r_int
r_char
id|cpu_bclk
suffix:semicolon
multiline_comment|/* Enable BCLK switching */
)brace
suffix:semicolon
r_extern
r_struct
id|cpu_spec
id|cpu_specs
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|cpu_spec
op_star
id|cur_cpu_spec
(braket
)braket
suffix:semicolon
macro_line|#endif
eof
