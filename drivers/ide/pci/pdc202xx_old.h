macro_line|#ifndef PDC202XX_H
DECL|macro|PDC202XX_H
mdefine_line|#define PDC202XX_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
DECL|macro|DISPLAY_PDC202XX_TIMINGS
mdefine_line|#define DISPLAY_PDC202XX_TIMINGS
macro_line|#ifndef SPLIT_BYTE
DECL|macro|SPLIT_BYTE
mdefine_line|#define SPLIT_BYTE(B,H,L)&t;((H)=(B&gt;&gt;4), (L)=(B-((B&gt;&gt;4)&lt;&lt;4)))
macro_line|#endif
DECL|macro|PDC202XX_DEBUG_DRIVE_INFO
mdefine_line|#define PDC202XX_DEBUG_DRIVE_INFO&t;&t;0
DECL|macro|PDC202XX_DECODE_REGISTER_INFO
mdefine_line|#define PDC202XX_DECODE_REGISTER_INFO&t;&t;0
DECL|variable|pdc_quirk_drives
r_static
r_const
r_char
op_star
id|pdc_quirk_drives
(braket
)braket
op_assign
(brace
l_string|&quot;QUANTUM FIREBALLlct08 08&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KA6.4&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KA9.1&quot;
comma
l_string|&quot;QUANTUM FIREBALLP LM20.4&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KX13.6&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KX20.5&quot;
comma
l_string|&quot;QUANTUM FIREBALLP KX27.3&quot;
comma
l_string|&quot;QUANTUM FIREBALLP LM20.5&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|pdc202xx_pio_verbose
r_static
r_inline
id|u8
op_star
id|pdc202xx_pio_verbose
(paren
id|u32
id|drive_pci
)paren
(brace
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x000ff000
)paren
op_eq
l_int|0x000ff000
)paren
r_return
l_string|&quot;NOTSET&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00000401
)paren
op_eq
l_int|0x00000401
)paren
r_return
l_string|&quot;PIO 4&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00000602
)paren
op_eq
l_int|0x00000602
)paren
r_return
l_string|&quot;PIO 3&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00000803
)paren
op_eq
l_int|0x00000803
)paren
r_return
l_string|&quot;PIO 2&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00000C05
)paren
op_eq
l_int|0x00000C05
)paren
r_return
l_string|&quot;PIO 1&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00001309
)paren
op_eq
l_int|0x00001309
)paren
r_return
l_string|&quot;PIO 0&quot;
suffix:semicolon
r_return
l_string|&quot;PIO ?&quot;
suffix:semicolon
)brace
DECL|function|pdc202xx_dma_verbose
r_static
r_inline
id|u8
op_star
id|pdc202xx_dma_verbose
(paren
id|u32
id|drive_pci
)paren
(brace
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00036000
)paren
op_eq
l_int|0x00036000
)paren
r_return
l_string|&quot;MWDMA 2&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00046000
)paren
op_eq
l_int|0x00046000
)paren
r_return
l_string|&quot;MWDMA 1&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00056000
)paren
op_eq
l_int|0x00056000
)paren
r_return
l_string|&quot;MWDMA 0&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00056000
)paren
op_eq
l_int|0x00056000
)paren
r_return
l_string|&quot;SWDMA 2&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00068000
)paren
op_eq
l_int|0x00068000
)paren
r_return
l_string|&quot;SWDMA 1&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x000BC000
)paren
op_eq
l_int|0x000BC000
)paren
r_return
l_string|&quot;SWDMA 0&quot;
suffix:semicolon
r_return
l_string|&quot;PIO---&quot;
suffix:semicolon
)brace
DECL|function|pdc202xx_ultra_verbose
r_static
r_inline
id|u8
op_star
id|pdc202xx_ultra_verbose
(paren
id|u32
id|drive_pci
comma
id|u16
id|slow_cable
)paren
(brace
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x000ff000
)paren
op_eq
l_int|0x000ff000
)paren
r_return
l_string|&quot;NOTSET&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00012000
)paren
op_eq
l_int|0x00012000
)paren
r_return
(paren
id|slow_cable
)paren
ques
c_cond
l_string|&quot;UDMA 2&quot;
suffix:colon
l_string|&quot;UDMA 4&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00024000
)paren
op_eq
l_int|0x00024000
)paren
r_return
(paren
id|slow_cable
)paren
ques
c_cond
l_string|&quot;UDMA 1&quot;
suffix:colon
l_string|&quot;UDMA 3&quot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_pci
op_amp
l_int|0x00036000
)paren
op_eq
l_int|0x00036000
)paren
r_return
l_string|&quot;UDMA 0&quot;
suffix:semicolon
r_return
id|pdc202xx_dma_verbose
c_func
(paren
id|drive_pci
)paren
suffix:semicolon
)brace
multiline_comment|/* A Register */
DECL|macro|SYNC_ERRDY_EN
mdefine_line|#define&t;SYNC_ERRDY_EN&t;0xC0
DECL|macro|SYNC_IN
mdefine_line|#define&t;SYNC_IN&t;&t;0x80&t;/* control bit, different for master vs. slave drives */
DECL|macro|ERRDY_EN
mdefine_line|#define&t;ERRDY_EN&t;0x40&t;/* control bit, different for master vs. slave drives */
DECL|macro|IORDY_EN
mdefine_line|#define&t;IORDY_EN&t;0x20&t;/* PIO: IOREADY */
DECL|macro|PREFETCH_EN
mdefine_line|#define&t;PREFETCH_EN&t;0x10&t;/* PIO: PREFETCH */
DECL|macro|PA3
mdefine_line|#define&t;PA3&t;&t;0x08&t;/* PIO&quot;A&quot; timing */
DECL|macro|PA2
mdefine_line|#define&t;PA2&t;&t;0x04&t;/* PIO&quot;A&quot; timing */
DECL|macro|PA1
mdefine_line|#define&t;PA1&t;&t;0x02&t;/* PIO&quot;A&quot; timing */
DECL|macro|PA0
mdefine_line|#define&t;PA0&t;&t;0x01&t;/* PIO&quot;A&quot; timing */
multiline_comment|/* B Register */
DECL|macro|MB2
mdefine_line|#define&t;MB2&t;&t;0x80&t;/* DMA&quot;B&quot; timing */
DECL|macro|MB1
mdefine_line|#define&t;MB1&t;&t;0x40&t;/* DMA&quot;B&quot; timing */
DECL|macro|MB0
mdefine_line|#define&t;MB0&t;&t;0x20&t;/* DMA&quot;B&quot; timing */
DECL|macro|PB4
mdefine_line|#define&t;PB4&t;&t;0x10&t;/* PIO_FORCE 1:0 */
DECL|macro|PB3
mdefine_line|#define&t;PB3&t;&t;0x08&t;/* PIO&quot;B&quot; timing */&t;/* PIO flow Control mode */
DECL|macro|PB2
mdefine_line|#define&t;PB2&t;&t;0x04&t;/* PIO&quot;B&quot; timing */&t;/* PIO 4 */
DECL|macro|PB1
mdefine_line|#define&t;PB1&t;&t;0x02&t;/* PIO&quot;B&quot; timing */&t;/* PIO 3 half */
DECL|macro|PB0
mdefine_line|#define&t;PB0&t;&t;0x01&t;/* PIO&quot;B&quot; timing */&t;/* PIO 3 other half */
multiline_comment|/* C Register */
DECL|macro|IORDYp_NO_SPEED
mdefine_line|#define&t;IORDYp_NO_SPEED&t;0x4F
DECL|macro|SPEED_DIS
mdefine_line|#define&t;SPEED_DIS&t;0x0F
DECL|macro|DMARQp
mdefine_line|#define&t;DMARQp&t;&t;0x80
DECL|macro|IORDYp
mdefine_line|#define&t;IORDYp&t;&t;0x40
DECL|macro|DMAR_EN
mdefine_line|#define&t;DMAR_EN&t;&t;0x20
DECL|macro|DMAW_EN
mdefine_line|#define&t;DMAW_EN&t;&t;0x10
DECL|macro|MC3
mdefine_line|#define&t;MC3&t;&t;0x08&t;/* DMA&quot;C&quot; timing */
DECL|macro|MC2
mdefine_line|#define&t;MC2&t;&t;0x04&t;/* DMA&quot;C&quot; timing */
DECL|macro|MC1
mdefine_line|#define&t;MC1&t;&t;0x02&t;/* DMA&quot;C&quot; timing */
DECL|macro|MC0
mdefine_line|#define&t;MC0&t;&t;0x01&t;/* DMA&quot;C&quot; timing */
macro_line|#if PDC202XX_DECODE_REGISTER_INFO
DECL|macro|REG_A
mdefine_line|#define REG_A&t;&t;0x01
DECL|macro|REG_B
mdefine_line|#define REG_B&t;&t;0x02
DECL|macro|REG_C
mdefine_line|#define REG_C&t;&t;0x04
DECL|macro|REG_D
mdefine_line|#define REG_D&t;&t;0x08
DECL|function|decode_registers
r_static
r_void
id|decode_registers
(paren
id|u8
id|registers
comma
id|u8
id|value
)paren
(brace
id|u8
id|bit
op_assign
l_int|0
comma
id|bit1
op_assign
l_int|0
comma
id|bit2
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|registers
)paren
(brace
r_case
id|REG_A
suffix:colon
id|bit2
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;A Register &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x80
)paren
id|printk
c_func
(paren
l_string|&quot;SYNC_IN &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x40
)paren
id|printk
c_func
(paren
l_string|&quot;ERRDY_EN &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x20
)paren
id|printk
c_func
(paren
l_string|&quot;IORDY_EN &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
l_string|&quot;PREFETCH_EN &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x08
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PA3 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x08
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x04
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PA2 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x04
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x02
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PA1 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x02
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x01
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PA0 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x01
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PIO(A) = %d &quot;
comma
id|bit2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REG_B
suffix:colon
id|bit1
op_assign
l_int|0
suffix:semicolon
id|bit2
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;B Register &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x80
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MB2 &quot;
)paren
suffix:semicolon
id|bit1
op_or_assign
l_int|0x80
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x40
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MB1 &quot;
)paren
suffix:semicolon
id|bit1
op_or_assign
l_int|0x40
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x20
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MB0 &quot;
)paren
suffix:semicolon
id|bit1
op_or_assign
l_int|0x20
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;DMA(B) = %d &quot;
comma
id|bit1
op_rshift
l_int|5
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
l_string|&quot;PIO_FORCED/PB4 &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x08
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PB3 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x08
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x04
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PB2 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x04
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x02
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PB1 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x02
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x01
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PB0 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x01
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PIO(B) = %d &quot;
comma
id|bit2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REG_C
suffix:colon
id|bit2
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;C Register &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x80
)paren
id|printk
c_func
(paren
l_string|&quot;DMARQp &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x40
)paren
id|printk
c_func
(paren
l_string|&quot;IORDYp &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x20
)paren
id|printk
c_func
(paren
l_string|&quot;DMAR_EN &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x10
)paren
id|printk
c_func
(paren
l_string|&quot;DMAW_EN &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|value
op_amp
l_int|0x08
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MC3 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x08
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x04
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MC2 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x04
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x02
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MC1 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x02
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
op_amp
l_int|0x01
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MC0 &quot;
)paren
suffix:semicolon
id|bit2
op_or_assign
l_int|0x01
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;DMA(C) = %d &quot;
comma
id|bit2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REG_D
suffix:colon
id|printk
c_func
(paren
l_string|&quot;D Register &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n        %s &quot;
comma
(paren
id|registers
op_amp
id|REG_D
)paren
ques
c_cond
l_string|&quot;DP&quot;
suffix:colon
(paren
id|registers
op_amp
id|REG_C
)paren
ques
c_cond
l_string|&quot;CP&quot;
suffix:colon
(paren
id|registers
op_amp
id|REG_B
)paren
ques
c_cond
l_string|&quot;BP&quot;
suffix:colon
(paren
id|registers
op_amp
id|REG_A
)paren
ques
c_cond
l_string|&quot;AP&quot;
suffix:colon
l_string|&quot;ERROR&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|bit
op_assign
l_int|128
suffix:semicolon
id|bit
OG
l_int|0
suffix:semicolon
id|bit
op_div_assign
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
(paren
id|value
op_amp
id|bit
)paren
ques
c_cond
l_string|&quot;1&quot;
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* PDC202XX_DECODE_REGISTER_INFO */
DECL|macro|set_2regs
mdefine_line|#define set_2regs(a, b)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;hwif-&gt;OUTB((a + adj), indexreg);&t;&bslash;&n;&t;&t;hwif-&gt;OUTB(b, datareg);&t;&t;&t;&bslash;&n;&t;} while(0)
DECL|macro|set_ultra
mdefine_line|#define set_ultra(a, b, c)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x10,(a));&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x11,(b));&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x12,(c));&t;&t;&t;&bslash;&n;&t;} while(0)
DECL|macro|set_ata2
mdefine_line|#define set_ata2(a, b)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x0e,(a));&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x0f,(b));&t;&t;&t;&bslash;&n;&t;} while(0)
DECL|macro|set_pio
mdefine_line|#define set_pio(a, b, c)&t;&t;&t;&t;&bslash;&n;&t;do { &t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x0c,(a));&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x0d,(b));&t;&t;&t;&bslash;&n;&t;&t;set_2regs(0x13,(c));&t;&t;&t;&bslash;&n;&t;} while(0)
DECL|macro|DISPLAY_PDC202XX_TIMINGS
mdefine_line|#define DISPLAY_PDC202XX_TIMINGS
r_static
r_void
id|init_setup_pdc202ata4
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|ide_pci_device_t
op_star
id|d
)paren
suffix:semicolon
r_static
r_void
id|init_setup_pdc20265
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_setup_pdc202xx
c_func
(paren
r_struct
id|pci_dev
op_star
comma
id|ide_pci_device_t
op_star
)paren
suffix:semicolon
r_static
r_int
r_int
id|init_chipset_pdc202xx
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_hwif_pdc202xx
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|init_dma_pdc202xx
c_func
(paren
id|ide_hwif_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|variable|__devinitdata
r_static
id|ide_pci_device_t
id|pdc202xx_chipsets
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
multiline_comment|/* 0 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_PROMISE
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_PROMISE_20246
comma
dot
id|name
op_assign
l_string|&quot;PDC20246&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202ata4
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
macro_line|#ifdef CONFIG_PDC202XX_FORCE
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
macro_line|#else /* !CONFIG_PDC202XX_FORCE */
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|16
comma
)brace
comma
(brace
multiline_comment|/* 1 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_PROMISE
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_PROMISE_20262
comma
dot
id|name
op_assign
l_string|&quot;PDC20262&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202ata4
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
macro_line|#ifdef CONFIG_PDC202XX_FORCE
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
macro_line|#else /* !CONFIG_PDC202XX_FORCE */
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
)brace
comma
(brace
multiline_comment|/* 2 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_PROMISE
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_PROMISE_20263
comma
dot
id|name
op_assign
l_string|&quot;PDC20263&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202ata4
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
macro_line|#ifdef CONFIG_PDC202XX_FORCE
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
macro_line|#else /* !CONFIG_PDC202XX_FORCE */
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
)brace
comma
(brace
multiline_comment|/* 3 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_PROMISE
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_PROMISE_20265
comma
dot
id|name
op_assign
l_string|&quot;PDC20265&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc20265
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
macro_line|#ifdef CONFIG_PDC202XX_FORCE
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
macro_line|#else /* !CONFIG_PDC202XX_FORCE */
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
)brace
comma
(brace
multiline_comment|/* 4 */
dot
id|vendor
op_assign
id|PCI_VENDOR_ID_PROMISE
comma
dot
id|device
op_assign
id|PCI_DEVICE_ID_PROMISE_20267
comma
dot
id|name
op_assign
l_string|&quot;PDC20267&quot;
comma
dot
id|init_setup
op_assign
id|init_setup_pdc202xx
comma
dot
id|init_chipset
op_assign
id|init_chipset_pdc202xx
comma
dot
id|init_iops
op_assign
l_int|NULL
comma
dot
id|init_hwif
op_assign
id|init_hwif_pdc202xx
comma
dot
id|init_dma
op_assign
id|init_dma_pdc202xx
comma
dot
id|channels
op_assign
l_int|2
comma
dot
id|autodma
op_assign
id|AUTODMA
comma
macro_line|#ifdef CONFIG_PDC202XX_FORCE
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
)brace
comma
macro_line|#else /* !CONFIG_PDC202XX_FORCE */
dot
id|enablebits
op_assign
(brace
(brace
l_int|0x50
comma
l_int|0x02
comma
l_int|0x02
)brace
comma
(brace
l_int|0x50
comma
l_int|0x04
comma
l_int|0x04
)brace
)brace
comma
macro_line|#endif
dot
id|bootable
op_assign
id|OFF_BOARD
comma
dot
id|extra
op_assign
l_int|48
comma
)brace
comma
(brace
dot
id|vendor
op_assign
l_int|0
comma
dot
id|device
op_assign
l_int|0
comma
dot
id|channels
op_assign
l_int|0
comma
dot
id|bootable
op_assign
id|EOL
comma
)brace
)brace
suffix:semicolon
macro_line|#endif /* PDC202XX_H */
eof
