multiline_comment|/*&n; * sound/pas2_card.c&n; *&n; * Detection routine for the Pro Audio Spectrum cards.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;pas2.h&quot;
macro_line|#include &quot;sb.h&quot;
DECL|variable|dma_bits
r_static
r_int
r_char
id|dma_bits
(braket
)braket
op_assign
(brace
l_int|4
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|0
comma
l_int|5
comma
l_int|6
comma
l_int|7
)brace
suffix:semicolon
DECL|variable|irq_bits
r_static
r_int
r_char
id|irq_bits
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|0
comma
l_int|1
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|0
comma
l_int|10
comma
l_int|11
)brace
suffix:semicolon
DECL|variable|sb_irq_bits
r_static
r_int
r_char
id|sb_irq_bits
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x08
comma
l_int|0x10
comma
l_int|0x00
comma
l_int|0x18
comma
l_int|0x00
comma
l_int|0x20
comma
l_int|0x00
comma
l_int|0x08
comma
l_int|0x28
comma
l_int|0x30
comma
l_int|0x38
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|sb_dma_bits
r_static
r_int
r_char
id|sb_dma_bits
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x40
comma
l_int|0x80
comma
l_int|0xC0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * The Address Translation code is used to convert I/O register addresses to&n; * be relative to the given base -register&n; */
DECL|variable|translate_code
r_int
id|translate_code
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas_intr_mask
r_static
r_int
id|pas_intr_mask
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas_irq
r_static
r_int
id|pas_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas_sb_base
r_static
r_int
id|pas_sb_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|lock
id|spinlock_t
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
macro_line|#ifndef CONFIG_PAS_JOYSTICK
DECL|variable|joystick
r_static
r_int
id|joystick
op_assign
l_int|0
suffix:semicolon
macro_line|#else
DECL|variable|joystick
r_static
r_int
id|joystick
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SYMPHONY_PAS
DECL|variable|symphony
r_static
r_int
id|symphony
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|symphony
r_static
r_int
id|symphony
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#ifdef BROKEN_BUS_CLOCK
DECL|variable|broken_bus_clock
r_static
r_int
id|broken_bus_clock
op_assign
l_int|1
suffix:semicolon
macro_line|#else
DECL|variable|broken_bus_clock
r_static
r_int
id|broken_bus_clock
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|variable|cfg
r_static
r_struct
id|address_info
id|cfg
suffix:semicolon
DECL|variable|cfg2
r_static
r_struct
id|address_info
id|cfg2
suffix:semicolon
DECL|variable|pas_model
r_char
id|pas_model
op_assign
l_int|0
suffix:semicolon
DECL|variable|pas_model_names
r_static
r_char
op_star
id|pas_model_names
(braket
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;Pro AudioSpectrum+&quot;
comma
l_string|&quot;CDPC&quot;
comma
l_string|&quot;Pro AudioSpectrum 16&quot;
comma
l_string|&quot;Pro AudioSpectrum 16D&quot;
)brace
suffix:semicolon
multiline_comment|/*&n; * pas_read() and pas_write() are equivalents of inb and outb &n; * These routines perform the I/O address translation required&n; * to support other than the default base address&n; */
r_extern
r_void
id|mix_write
c_func
(paren
r_int
r_char
id|data
comma
r_int
id|ioaddr
)paren
suffix:semicolon
DECL|function|pas_read
r_int
r_char
id|pas_read
c_func
(paren
r_int
id|ioaddr
)paren
(brace
r_return
id|inb
c_func
(paren
id|ioaddr
op_plus
id|translate_code
)paren
suffix:semicolon
)brace
DECL|function|pas_write
r_void
id|pas_write
c_func
(paren
r_int
r_char
id|data
comma
r_int
id|ioaddr
)paren
(brace
id|outb
c_func
(paren
(paren
id|data
)paren
comma
id|ioaddr
op_plus
id|translate_code
)paren
suffix:semicolon
)brace
multiline_comment|/******************* Begin of the Interrupt Handler ********************/
DECL|function|pasintr
r_void
id|pasintr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|dummy
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|pas_read
c_func
(paren
l_int|0x0B89
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|status
comma
l_int|0x0B89
)paren
suffix:semicolon
multiline_comment|/* Clear interrupt */
r_if
c_cond
(paren
id|status
op_amp
l_int|0x08
)paren
(brace
id|pas_pcm_interrupt
c_func
(paren
id|status
comma
l_int|1
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
l_int|0x08
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x10
)paren
(brace
id|pas_midi_interrupt
c_func
(paren
)paren
suffix:semicolon
id|status
op_and_assign
op_complement
l_int|0x10
suffix:semicolon
)brace
)brace
DECL|function|pas_set_intr
r_int
id|pas_set_intr
c_func
(paren
r_int
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
r_return
l_int|0
suffix:semicolon
id|pas_intr_mask
op_or_assign
id|mask
suffix:semicolon
id|pas_write
c_func
(paren
id|pas_intr_mask
comma
l_int|0x0B8B
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pas_remove_intr
r_int
id|pas_remove_intr
c_func
(paren
r_int
id|mask
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|mask
)paren
r_return
l_int|0
suffix:semicolon
id|pas_intr_mask
op_and_assign
op_complement
id|mask
suffix:semicolon
id|pas_write
c_func
(paren
id|pas_intr_mask
comma
l_int|0x0B8B
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/******************* End of the Interrupt handler **********************/
multiline_comment|/******************* Begin of the Initialization Code ******************/
DECL|function|config_pas_hw
r_static
r_int
id|__init
id|config_pas_hw
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_char
id|ok
op_assign
l_int|1
suffix:semicolon
r_int
id|int_ptrs
suffix:semicolon
multiline_comment|/* scsi/sound interrupt pointers */
id|pas_irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x00
comma
l_int|0x0B8B
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x36
comma
l_int|0x138B
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x36
comma
l_int|0x1388
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0
comma
l_int|0x1388
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x74
comma
l_int|0x138B
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x74
comma
l_int|0x1389
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0
comma
l_int|0x1389
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x80
op_or
l_int|0x40
op_or
l_int|0x20
op_or
l_int|1
comma
l_int|0x0B8A
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x80
op_or
l_int|0x20
op_or
l_int|0x10
op_or
l_int|0x08
op_or
l_int|0x01
comma
l_int|0xF8A
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x01
op_or
l_int|0x02
op_or
l_int|0x04
op_or
l_int|0x10
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t; * |&n;&t;&t;&t;&t;&t;&t; * 0x80&n;&t;&t;&t;&t;&t;&t; */
comma
l_int|0xB88
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x80
op_or
id|joystick
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
comma
l_int|0xF388
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pas_irq
template_param
l_int|15
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAS16: Invalid IRQ %d&quot;
comma
id|pas_irq
)paren
suffix:semicolon
id|hw_config-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|int_ptrs
op_assign
id|pas_read
c_func
(paren
l_int|0xF38A
)paren
suffix:semicolon
id|int_ptrs
op_assign
(paren
id|int_ptrs
op_amp
l_int|0xf0
)paren
op_or
id|irq_bits
(braket
id|pas_irq
)braket
suffix:semicolon
id|pas_write
c_func
(paren
id|int_ptrs
comma
l_int|0xF38A
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|irq_bits
(braket
id|pas_irq
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAS16: Invalid IRQ %d&quot;
comma
id|pas_irq
)paren
suffix:semicolon
id|hw_config-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|pas_irq
comma
id|pasintr
comma
l_int|0
comma
l_string|&quot;PAS16&quot;
comma
id|hw_config
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAS16: Cannot allocate IRQ %d&bslash;n&quot;
comma
id|pas_irq
)paren
suffix:semicolon
id|hw_config-&gt;irq
op_assign
op_minus
l_int|1
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|hw_config-&gt;dma
template_param
l_int|7
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAS16: Invalid DMA selection %d&quot;
comma
id|hw_config-&gt;dma
)paren
suffix:semicolon
id|hw_config-&gt;dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|pas_write
c_func
(paren
id|dma_bits
(braket
id|hw_config-&gt;dma
)braket
comma
l_int|0xF389
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_bits
(braket
id|hw_config-&gt;dma
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAS16: Invalid DMA selection %d&quot;
comma
id|hw_config-&gt;dma
)paren
suffix:semicolon
id|hw_config-&gt;dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|sound_alloc_dma
c_func
(paren
id|hw_config-&gt;dma
comma
l_string|&quot;PAS16&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pas2_card.c: Can&squot;t allocate DMA channel&bslash;n&quot;
)paren
suffix:semicolon
id|hw_config-&gt;dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * This fixes the timing problems of the PAS due to the Symphony chipset&n;&t; * as per Media Vision.  Only define this if your PAS doesn&squot;t work correctly.&n;&t; */
r_if
c_cond
(paren
id|symphony
)paren
(brace
id|outb
c_func
(paren
(paren
l_int|0x05
)paren
comma
l_int|0xa8
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|0x60
)paren
comma
l_int|0xa9
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|broken_bus_clock
)paren
(brace
id|pas_write
c_func
(paren
l_int|0x01
op_or
l_int|0x10
op_or
l_int|0x20
op_or
l_int|0x04
comma
l_int|0x8388
)paren
suffix:semicolon
)brace
r_else
multiline_comment|/*&n;&t;&t; * pas_write(0x01, 0x8388);&n;&t;&t; */
id|pas_write
c_func
(paren
l_int|0x01
op_or
l_int|0x10
op_or
l_int|0x20
comma
l_int|0x8388
)paren
suffix:semicolon
id|pas_write
c_func
(paren
l_int|0x18
comma
l_int|0x838A
)paren
suffix:semicolon
multiline_comment|/* ??? */
id|pas_write
c_func
(paren
l_int|0x20
op_or
l_int|0x01
comma
l_int|0x0B8A
)paren
suffix:semicolon
multiline_comment|/* Mute off, filter = 17.897 kHz */
id|pas_write
c_func
(paren
l_int|8
comma
l_int|0xBF8A
)paren
suffix:semicolon
id|mix_write
c_func
(paren
l_int|0x80
op_or
l_int|5
comma
l_int|0x078B
)paren
suffix:semicolon
id|mix_write
c_func
(paren
l_int|5
comma
l_int|0x078B
)paren
suffix:semicolon
macro_line|#if !defined(DISABLE_SB_EMULATION)
(brace
r_struct
id|address_info
op_star
id|sb_config
suffix:semicolon
id|sb_config
op_assign
op_amp
id|cfg2
suffix:semicolon
r_if
c_cond
(paren
id|sb_config-&gt;io_base
)paren
(brace
r_int
r_char
id|irq_dma
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Turn on Sound Blaster compatibility&n;&t;&t;&t; * bit 1 = SB emulation&n;&t;&t;&t; * bit 0 = MPU401 emulation (CDPC only :-( )&n;&t;&t;&t; */
id|pas_write
c_func
(paren
l_int|0x02
comma
l_int|0xF788
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * &quot;Emulation address&quot;&n;&t;&t;&t; */
id|pas_write
c_func
(paren
(paren
id|sb_config-&gt;io_base
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
comma
l_int|0xF789
)paren
suffix:semicolon
id|pas_sb_base
op_assign
id|sb_config-&gt;io_base
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb_dma_bits
(braket
id|sb_config-&gt;dma
)braket
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAS16 Warning: Invalid SB DMA %d&bslash;n&bslash;n&quot;
comma
id|sb_config-&gt;dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb_irq_bits
(braket
id|sb_config-&gt;irq
)braket
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PAS16 Warning: Invalid SB IRQ %d&bslash;n&bslash;n&quot;
comma
id|sb_config-&gt;irq
)paren
suffix:semicolon
id|irq_dma
op_assign
id|sb_dma_bits
(braket
id|sb_config-&gt;dma
)braket
op_or
id|sb_irq_bits
(braket
id|sb_config-&gt;irq
)braket
suffix:semicolon
id|pas_write
c_func
(paren
id|irq_dma
comma
l_int|0xFB8A
)paren
suffix:semicolon
)brace
r_else
id|pas_write
c_func
(paren
l_int|0x00
comma
l_int|0xF788
)paren
suffix:semicolon
)brace
macro_line|#else
id|pas_write
c_func
(paren
l_int|0x00
comma
l_int|0xF788
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|ok
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PAS16: Driver not enabled&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
DECL|function|detect_pas_hw
r_static
r_int
id|__init
id|detect_pas_hw
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
r_char
id|board_id
comma
id|foo
suffix:semicolon
multiline_comment|/*&n;&t; * WARNING: Setting an option like W:1 or so that disables warm boot reset&n;&t; * of the card will screw up this detect code something fierce. Adding code&n;&t; * to handle this means possibly interfering with other cards on the bus if&n;&t; * you have something on base port 0x388. SO be forewarned.&n;&t; */
id|outb
c_func
(paren
(paren
l_int|0xBC
)paren
comma
l_int|0x9A01
)paren
suffix:semicolon
multiline_comment|/* Activate first board */
id|outb
c_func
(paren
(paren
id|hw_config-&gt;io_base
op_rshift
l_int|2
)paren
comma
l_int|0x9A01
)paren
suffix:semicolon
multiline_comment|/* Set base address */
id|translate_code
op_assign
id|hw_config-&gt;io_base
op_minus
l_int|0x388
suffix:semicolon
id|pas_write
c_func
(paren
l_int|1
comma
l_int|0xBF88
)paren
suffix:semicolon
multiline_comment|/* Select one wait states */
id|board_id
op_assign
id|pas_read
c_func
(paren
l_int|0x0B8B
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_id
op_eq
l_int|0xff
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * We probably have a PAS-series board, now check for a PAS16-series board&n;&t; * by trying to change the board revision bits. PAS16-series hardware won&squot;t&n;&t; * let you do this - the bits are read-only.&n;&t; */
id|foo
op_assign
id|board_id
op_xor
l_int|0xe0
suffix:semicolon
id|pas_write
c_func
(paren
id|foo
comma
l_int|0x0B8B
)paren
suffix:semicolon
id|foo
op_assign
id|pas_read
c_func
(paren
l_int|0x0B8B
)paren
suffix:semicolon
id|pas_write
c_func
(paren
id|board_id
comma
l_int|0x0B8B
)paren
suffix:semicolon
r_if
c_cond
(paren
id|board_id
op_ne
id|foo
)paren
r_return
l_int|0
suffix:semicolon
id|pas_model
op_assign
id|pas_read
c_func
(paren
l_int|0xFF88
)paren
suffix:semicolon
r_return
id|pas_model
suffix:semicolon
)brace
DECL|function|attach_pas_card
r_static
r_void
id|__init
id|attach_pas_card
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|pas_irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|detect_pas_hw
c_func
(paren
id|hw_config
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|pas_model
op_assign
id|pas_read
c_func
(paren
l_int|0xFF88
)paren
)paren
)paren
(brace
r_char
id|temp
(braket
l_int|100
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|temp
comma
l_string|&quot;%s rev %d&quot;
comma
id|pas_model_names
(braket
(paren
r_int
)paren
id|pas_model
)braket
comma
id|pas_read
c_func
(paren
l_int|0x2789
)paren
)paren
suffix:semicolon
id|conf_printf
c_func
(paren
id|temp
comma
id|hw_config
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|config_pas_hw
c_func
(paren
id|hw_config
)paren
)paren
(brace
id|pas_pcm_init
c_func
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#if !defined(MODULE) &amp;&amp; !defined(DISABLE_SB_EMULATION)
id|sb_dsp_disable_midi
c_func
(paren
id|pas_sb_base
)paren
suffix:semicolon
multiline_comment|/* No MIDI capability */
macro_line|#endif
id|pas_midi_init
c_func
(paren
)paren
suffix:semicolon
id|pas_init_mixer
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|probe_pas
r_static
r_inline
r_int
id|__init
id|probe_pas
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_return
id|detect_pas_hw
c_func
(paren
id|hw_config
)paren
suffix:semicolon
)brace
DECL|function|unload_pas
r_static
r_void
id|__exit
id|unload_pas
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_extern
r_int
id|pas_audiodev
suffix:semicolon
r_extern
r_int
id|pas2_mididev
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma
OG
l_int|0
)paren
id|sound_free_dma
c_func
(paren
id|hw_config-&gt;dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|0
)paren
id|free_irq
c_func
(paren
id|hw_config-&gt;irq
comma
id|hw_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pas_audiodev
op_ne
op_minus
l_int|1
)paren
(brace
id|sound_unload_mixerdev
c_func
(paren
id|audio_devs
(braket
id|pas_audiodev
)braket
op_member_access_from_pointer
id|mixer_dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pas2_mididev
op_ne
op_minus
l_int|1
)paren
(brace
id|sound_unload_mididev
c_func
(paren
id|pas2_mididev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pas_audiodev
op_ne
op_minus
l_int|1
)paren
(brace
id|sound_unload_audiodev
c_func
(paren
id|pas_audiodev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|io
r_static
r_int
id|__initdata
id|io
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|__initdata
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|dma
r_static
r_int
id|__initdata
id|dma
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|dma16
r_static
r_int
id|__initdata
id|dma16
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Set this for modules that need it */
DECL|variable|sb_io
r_static
r_int
id|__initdata
id|sb_io
op_assign
l_int|0
suffix:semicolon
DECL|variable|sb_irq
r_static
r_int
id|__initdata
id|sb_irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|sb_dma
r_static
r_int
id|__initdata
id|sb_dma
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|sb_dma16
r_static
r_int
id|__initdata
id|sb_dma16
op_assign
op_minus
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma16
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|sb_io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|sb_irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|sb_dma
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|sb_dma16
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|joystick
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|symphony
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|broken_bus_clock
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|init_pas2
r_static
r_int
id|__init
id|init_pas2
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Pro Audio Spectrum driver Copyright (C) by Hannu Savolainen 1993-1996&bslash;n&quot;
)paren
suffix:semicolon
id|cfg.io_base
op_assign
id|io
suffix:semicolon
id|cfg.irq
op_assign
id|irq
suffix:semicolon
id|cfg.dma
op_assign
id|dma
suffix:semicolon
id|cfg.dma2
op_assign
id|dma16
suffix:semicolon
id|cfg2.io_base
op_assign
id|sb_io
suffix:semicolon
id|cfg2.irq
op_assign
id|sb_irq
suffix:semicolon
id|cfg2.dma
op_assign
id|sb_dma
suffix:semicolon
id|cfg2.dma2
op_assign
id|sb_dma16
suffix:semicolon
r_if
c_cond
(paren
id|cfg.io_base
op_eq
op_minus
l_int|1
op_logical_or
id|cfg.dma
op_eq
op_minus
l_int|1
op_logical_or
id|cfg.irq
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;I/O, IRQ, DMA and type are mandatory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|probe_pas
c_func
(paren
op_amp
id|cfg
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|attach_pas_card
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_pas2
r_static
r_void
id|__exit
id|cleanup_pas2
c_func
(paren
r_void
)paren
(brace
id|unload_pas
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
)brace
DECL|variable|init_pas2
id|module_init
c_func
(paren
id|init_pas2
)paren
suffix:semicolon
DECL|variable|cleanup_pas2
id|module_exit
c_func
(paren
id|cleanup_pas2
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|setup_pas2
r_static
r_int
id|__init
id|setup_pas2
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* io, irq, dma, dma2, sb_io, sb_irq, sb_dma, sb_dma2 */
r_int
id|ints
(braket
l_int|9
)braket
suffix:semicolon
id|str
op_assign
id|get_options
c_func
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
id|io
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
id|irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
id|dma
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
id|dma16
op_assign
id|ints
(braket
l_int|4
)braket
suffix:semicolon
id|sb_io
op_assign
id|ints
(braket
l_int|5
)braket
suffix:semicolon
id|sb_irq
op_assign
id|ints
(braket
l_int|6
)braket
suffix:semicolon
id|sb_dma
op_assign
id|ints
(braket
l_int|7
)braket
suffix:semicolon
id|sb_dma16
op_assign
id|ints
(braket
l_int|8
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;pas2=&quot;
comma
id|setup_pas2
)paren
suffix:semicolon
macro_line|#endif
eof
