multiline_comment|/*&n; * sound/trix.c&n; *&n; * Low level driver for the MediaTrix AudioTrix Pro&n; * (MT-0002-PC Control Chip)&n; *&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; *&n; * Changes&n; *&t;Alan Cox&t;&t;Modularisation, cleanup.&n; *&t;Christoph Hellwig&t;Adapted to module_init/module_exit&n; *&t;Arnaldo C. de Melo&t;Got rid of attach_uart401&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;sb.h&quot;
macro_line|#include &quot;sound_firmware.h&quot;
macro_line|#include &quot;ad1848.h&quot;
macro_line|#include &quot;mpu401.h&quot;
macro_line|#include &quot;trix_boot.h&quot;
DECL|variable|kilroy_was_here
r_static
r_int
id|kilroy_was_here
suffix:semicolon
multiline_comment|/* Don&squot;t detect twice */
DECL|variable|sb_initialized
r_static
r_int
id|sb_initialized
suffix:semicolon
DECL|variable|mpu_initialized
r_static
r_int
id|mpu_initialized
suffix:semicolon
DECL|variable|trix_osp
r_static
r_int
op_star
id|trix_osp
suffix:semicolon
DECL|variable|mpu
r_static
r_int
id|mpu
suffix:semicolon
DECL|variable|joystick
r_static
r_int
id|joystick
suffix:semicolon
DECL|function|trix_read
r_static
r_int
r_char
id|trix_read
c_func
(paren
r_int
id|addr
)paren
(brace
id|outb
c_func
(paren
(paren
(paren
r_int
r_char
)paren
id|addr
)paren
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC address */
r_return
id|inb
c_func
(paren
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC data */
)brace
DECL|function|trix_write
r_static
r_void
id|trix_write
c_func
(paren
r_int
id|addr
comma
r_int
id|data
)paren
(brace
id|outb
c_func
(paren
(paren
(paren
r_int
r_char
)paren
id|addr
)paren
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC address */
id|outb
c_func
(paren
(paren
(paren
r_int
r_char
)paren
id|data
)paren
comma
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC data */
)brace
DECL|function|download_boot
r_static
r_void
id|download_boot
c_func
(paren
r_int
id|base
)paren
(brace
r_int
id|i
op_assign
l_int|0
comma
id|n
op_assign
id|trix_boot_len
suffix:semicolon
r_if
c_cond
(paren
id|trix_boot_len
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|trix_write
c_func
(paren
l_int|0xf8
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* ??????? */
id|outb
c_func
(paren
(paren
l_int|0x01
)paren
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Clear the internal data pointer */
id|outb
c_func
(paren
(paren
l_int|0x00
)paren
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Restart */
multiline_comment|/*&n;&t;   *  Write the boot code to the RAM upload/download register.&n;&t;   *  Each write increments the internal data pointer.&n;&t; */
id|outb
c_func
(paren
(paren
l_int|0x01
)paren
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Clear the internal data pointer */
id|outb
c_func
(paren
(paren
l_int|0x1A
)paren
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* Select RAM download/upload port */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
id|outb
c_func
(paren
(paren
id|trix_boot
(braket
id|i
)braket
)paren
comma
l_int|0x391
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|n
suffix:semicolon
id|i
OL
l_int|10016
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Clear up to first 16 bytes of data RAM */
id|outb
c_func
(paren
(paren
l_int|0x00
)paren
comma
l_int|0x391
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|0x00
)paren
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Reset */
id|outb
c_func
(paren
(paren
l_int|0x50
)paren
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* ?????? */
)brace
DECL|function|trix_set_wss_port
r_static
r_int
id|trix_set_wss_port
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
id|addr_bits
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
l_int|0x390
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Config port I/O conflict&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kilroy_was_here
)paren
multiline_comment|/* Already initialized */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|trix_read
c_func
(paren
l_int|0x15
)paren
op_ne
l_int|0x71
)paren
multiline_comment|/* No ASIC signature */
(brace
id|MDB
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;No AudioTrix ASIC signature found&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|kilroy_was_here
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Reset some registers.&n;&t; */
id|trix_write
c_func
(paren
l_int|0x13
comma
l_int|0
)paren
suffix:semicolon
id|trix_write
c_func
(paren
l_int|0x14
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Configure the ASIC to place the codec to the proper I/O location&n;&t; */
r_switch
c_cond
(paren
id|hw_config-&gt;io_base
)paren
(brace
r_case
l_int|0x530
suffix:colon
id|addr_bits
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x604
suffix:colon
id|addr_bits
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xE80
suffix:colon
id|addr_bits
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xF40
suffix:colon
id|addr_bits
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
id|trix_write
c_func
(paren
l_int|0x19
comma
(paren
id|trix_read
c_func
(paren
l_int|0x19
)paren
op_amp
l_int|0x03
)paren
op_or
id|addr_bits
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *    Probe and attach routines for the Windows Sound System mode of&n; *      AudioTrix Pro&n; */
DECL|function|probe_trix_wss
r_static
r_int
id|__init
id|probe_trix_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Check if the IO port returns valid signature. The original MS Sound&n;&t; * system returns 0x04 while some cards (AudioTrix Pro for example)&n;&t; * return 0x00.&n;&t; */
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|8
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: MSS I/O port conflict (%x)&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|trix_osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|trix_set_wss_port
c_func
(paren
id|hw_config
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|3
)paren
op_amp
l_int|0x3f
)paren
op_ne
l_int|0x00
)paren
(brace
id|MDB
c_func
(paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;No MSS signature detected on port 0x%x&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|11
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Bad WSS IRQ %d&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;dma
op_ne
l_int|0
op_logical_and
id|hw_config-&gt;dma
op_ne
l_int|1
op_logical_and
id|hw_config-&gt;dma
op_ne
l_int|3
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Bad WSS DMA %d&bslash;n&quot;
comma
id|hw_config-&gt;dma
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;dma2
op_ne
op_minus
l_int|1
op_logical_and
id|hw_config-&gt;dma2
op_ne
id|hw_config-&gt;dma
)paren
r_if
c_cond
(paren
id|hw_config-&gt;dma2
op_ne
l_int|0
op_logical_and
id|hw_config-&gt;dma2
op_ne
l_int|1
op_logical_and
id|hw_config-&gt;dma2
op_ne
l_int|3
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Bad capture DMA %d&bslash;n&quot;
comma
id|hw_config-&gt;dma2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check that DMA0 is not in use with a 8 bit board.&n;&t; */
r_if
c_cond
(paren
id|hw_config-&gt;dma
op_eq
l_int|0
op_logical_and
id|inb
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|3
)paren
op_amp
l_int|0x80
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Can&squot;t use DMA0 with a 8 bit card slot&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|7
op_logical_and
id|hw_config-&gt;irq
op_ne
l_int|9
op_logical_and
id|inb
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|3
)paren
op_amp
l_int|0x80
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Can&squot;t use IRQ%d with a 8 bit card slot&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ret
op_assign
id|ad1848_detect
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|4
comma
l_int|NULL
comma
id|hw_config-&gt;osp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
r_if
c_cond
(paren
id|joystick
op_eq
l_int|1
)paren
(brace
id|trix_write
c_func
(paren
l_int|0x15
comma
l_int|0x80
)paren
suffix:semicolon
)brace
id|request_region
c_func
(paren
l_int|0x390
comma
l_int|2
comma
l_string|&quot;AudioTrix&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|attach_trix_wss
r_static
r_void
id|__init
id|attach_trix_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_static
r_int
r_char
id|interrupt_bits
(braket
l_int|12
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x08
comma
l_int|0
comma
l_int|0x10
comma
l_int|0x18
comma
l_int|0x20
)brace
suffix:semicolon
r_char
id|bits
suffix:semicolon
r_static
r_int
r_char
id|dma_bits
(braket
l_int|4
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|3
)brace
suffix:semicolon
r_int
id|config_port
op_assign
id|hw_config-&gt;io_base
op_plus
l_int|0
suffix:semicolon
r_int
id|dma1
op_assign
id|hw_config-&gt;dma
comma
id|dma2
op_assign
id|hw_config-&gt;dma2
suffix:semicolon
r_int
id|old_num_mixers
op_assign
id|num_mixers
suffix:semicolon
id|trix_osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kilroy_was_here
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;AudioTrix: Attach called but not probed yet???&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set the IRQ and DMA addresses.&n;&t; */
id|bits
op_assign
id|interrupt_bits
(braket
id|hw_config-&gt;irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;AudioTrix: Bad IRQ (%d)&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|outb
c_func
(paren
(paren
id|bits
op_or
l_int|0x40
)paren
comma
id|config_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma2
op_eq
op_minus
l_int|1
op_logical_or
id|hw_config-&gt;dma2
op_eq
id|hw_config-&gt;dma
)paren
(brace
id|bits
op_or_assign
id|dma_bits
(braket
id|dma1
)braket
suffix:semicolon
id|dma2
op_assign
id|dma1
suffix:semicolon
)brace
r_else
(brace
r_int
r_char
id|tmp
suffix:semicolon
id|tmp
op_assign
id|trix_read
c_func
(paren
l_int|0x13
)paren
op_amp
op_complement
l_int|30
suffix:semicolon
id|trix_write
c_func
(paren
l_int|0x13
comma
id|tmp
op_or
l_int|0x80
op_or
(paren
id|dma1
op_lshift
l_int|4
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|trix_read
c_func
(paren
l_int|0x14
)paren
op_amp
op_complement
l_int|30
suffix:semicolon
id|trix_write
c_func
(paren
l_int|0x14
comma
id|tmp
op_or
l_int|0x80
op_or
(paren
id|dma2
op_lshift
l_int|4
)paren
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
(paren
id|bits
)paren
comma
id|config_port
)paren
suffix:semicolon
multiline_comment|/* Write IRQ+DMA setup */
id|hw_config-&gt;slots
(braket
l_int|0
)braket
op_assign
id|ad1848_init
c_func
(paren
l_string|&quot;AudioTrix Pro&quot;
comma
id|hw_config-&gt;io_base
op_plus
l_int|4
comma
id|hw_config-&gt;irq
comma
id|dma1
comma
id|dma2
comma
l_int|0
comma
id|hw_config-&gt;osp
comma
id|THIS_MODULE
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|4
comma
l_string|&quot;MSS config&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_mixers
OG
id|old_num_mixers
)paren
multiline_comment|/* Mixer got installed */
(brace
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE1
comma
id|SOUND_MIXER_LINE
)paren
suffix:semicolon
multiline_comment|/* Line in */
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE2
comma
id|SOUND_MIXER_CD
)paren
suffix:semicolon
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE3
comma
id|SOUND_MIXER_SYNTH
)paren
suffix:semicolon
multiline_comment|/* OPL4 */
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_SPEAKER
comma
id|SOUND_MIXER_ALTPCM
)paren
suffix:semicolon
multiline_comment|/* SB */
)brace
)brace
DECL|function|probe_trix_sb
r_static
r_int
id|__init
id|probe_trix_sb
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_int
r_char
id|conf
suffix:semicolon
r_extern
r_int
id|sb_be_quiet
suffix:semicolon
r_int
id|old_quiet
suffix:semicolon
r_static
r_int
r_char
id|irq_translate
(braket
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
op_minus
l_int|1
comma
l_int|3
)brace
suffix:semicolon
r_if
c_cond
(paren
id|trix_boot_len
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No boot code -&gt; no fun */
r_if
c_cond
(paren
op_logical_neg
id|kilroy_was_here
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* AudioTrix Pro has not been detected earlier */
r_if
c_cond
(paren
id|sb_initialized
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hw_config-&gt;io_base
op_amp
l_int|0xffffff8f
)paren
op_ne
l_int|0x200
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
l_int|7
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|irq_translate
(braket
id|tmp
)braket
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|hw_config-&gt;dma
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
l_int|1
op_logical_and
id|tmp
op_ne
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|16
comma
l_string|&quot;soundblaster&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: SB I/O port conflict (%x)&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|conf
op_assign
l_int|0x84
suffix:semicolon
multiline_comment|/* DMA and IRQ enable */
id|conf
op_or_assign
id|hw_config-&gt;io_base
op_amp
l_int|0x70
suffix:semicolon
multiline_comment|/* I/O address bits */
id|conf
op_or_assign
id|irq_translate
(braket
id|hw_config-&gt;irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma
op_eq
l_int|3
)paren
id|conf
op_or_assign
l_int|0x08
suffix:semicolon
id|trix_write
c_func
(paren
l_int|0x1b
comma
id|conf
)paren
suffix:semicolon
id|download_boot
c_func
(paren
id|hw_config-&gt;io_base
)paren
suffix:semicolon
id|sb_initialized
op_assign
l_int|1
suffix:semicolon
id|hw_config-&gt;name
op_assign
l_string|&quot;AudioTrix SB&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb_dsp_detect
c_func
(paren
id|hw_config
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
)paren
)paren
(brace
id|release_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|hw_config-&gt;driver_use_1
op_assign
id|SB_NO_MIDI
op_or
id|SB_NO_MIXER
op_or
id|SB_NO_RECORDING
suffix:semicolon
multiline_comment|/* Prevent false alarms */
id|old_quiet
op_assign
id|sb_be_quiet
suffix:semicolon
id|sb_be_quiet
op_assign
l_int|1
suffix:semicolon
id|sb_dsp_init
c_func
(paren
id|hw_config
comma
id|THIS_MODULE
)paren
suffix:semicolon
id|sb_be_quiet
op_assign
id|old_quiet
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|probe_trix_mpu
r_static
r_int
id|__init
id|probe_trix_mpu
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
id|conf
suffix:semicolon
r_static
r_int
id|irq_bits
(braket
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
op_minus
l_int|1
comma
l_int|4
comma
op_minus
l_int|1
comma
l_int|5
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kilroy_was_here
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Trix: WSS and SB modes must be initialized before MPU&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* AudioTrix Pro has not been detected earlier */
)brace
r_if
c_cond
(paren
op_logical_neg
id|sb_initialized
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Trix: SB mode must be initialized before MPU&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mpu_initialized
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Trix: MPU mode already initialized&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|9
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Bad MPU IRQ %d&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_bits
(braket
id|hw_config-&gt;irq
)braket
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;AudioTrix: Bad MPU IRQ %d&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|hw_config-&gt;io_base
)paren
(brace
r_case
l_int|0x330
suffix:colon
id|conf
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x370
suffix:colon
id|conf
op_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3b0
suffix:colon
id|conf
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3f0
suffix:colon
id|conf
op_assign
l_int|0x0c
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Invalid port */
)brace
id|conf
op_or_assign
id|irq_bits
(braket
id|hw_config-&gt;irq
)braket
op_lshift
l_int|4
suffix:semicolon
id|trix_write
c_func
(paren
l_int|0x19
comma
(paren
id|trix_read
c_func
(paren
l_int|0x19
)paren
op_amp
l_int|0x83
)paren
op_or
id|conf
)paren
suffix:semicolon
id|mpu_initialized
op_assign
l_int|1
suffix:semicolon
id|hw_config-&gt;name
op_assign
l_string|&quot;AudioTrix Pro&quot;
suffix:semicolon
r_return
id|probe_uart401
c_func
(paren
id|hw_config
comma
id|THIS_MODULE
)paren
suffix:semicolon
)brace
DECL|function|unload_trix_wss
r_static
r_void
id|__exit
id|unload_trix_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|dma2
op_assign
id|hw_config-&gt;dma2
suffix:semicolon
r_if
c_cond
(paren
id|dma2
op_eq
op_minus
l_int|1
)paren
id|dma2
op_assign
id|hw_config-&gt;dma
suffix:semicolon
id|release_region
c_func
(paren
l_int|0x390
comma
l_int|2
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|4
)paren
suffix:semicolon
id|ad1848_unload
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|4
comma
id|hw_config-&gt;irq
comma
id|hw_config-&gt;dma
comma
id|dma2
comma
l_int|0
)paren
suffix:semicolon
id|sound_unload_audiodev
c_func
(paren
id|hw_config-&gt;slots
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|function|unload_trix_mpu
r_static
r_inline
r_void
id|__exit
id|unload_trix_mpu
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|unload_uart401
c_func
(paren
id|hw_config
)paren
suffix:semicolon
)brace
DECL|function|unload_trix_sb
r_static
r_inline
r_void
id|__exit
id|unload_trix_sb
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|sb_dsp_unload
c_func
(paren
id|hw_config
comma
id|mpu
)paren
suffix:semicolon
)brace
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
DECL|variable|cfg_mpu
r_static
r_struct
id|address_info
id|cfg_mpu
suffix:semicolon
DECL|variable|sb
r_static
r_int
id|sb
suffix:semicolon
DECL|variable|fw_load
r_static
r_int
id|fw_load
suffix:semicolon
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
DECL|variable|dma2
r_static
r_int
id|__initdata
id|dma2
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
DECL|variable|sb_irq
r_static
r_int
id|__initdata
id|sb_irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mpu_io
r_static
r_int
id|__initdata
id|mpu_io
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mpu_irq
r_static
r_int
id|__initdata
id|mpu_irq
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
id|dma2
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
id|sb_dma
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
id|mpu_io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mpu_irq
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
DECL|function|init_trix
r_static
r_int
id|__init
id|init_trix
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;MediaTrix audio driver Copyright (C) by Hannu Savolainen 1993-1996&bslash;n&quot;
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
id|dma2
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
id|cfg_mpu.io_base
op_assign
id|mpu_io
suffix:semicolon
id|cfg_mpu.irq
op_assign
id|mpu_irq
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
id|cfg2.io_base
op_ne
op_minus
l_int|1
op_logical_and
(paren
id|cfg2.irq
op_eq
op_minus
l_int|1
op_logical_or
id|cfg2.dma
op_eq
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CONFIG_SB_IRQ and CONFIG_SB_DMA must be specified if SB_IO is set.&bslash;n&quot;
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
id|cfg_mpu.io_base
op_ne
op_minus
l_int|1
op_logical_and
id|cfg_mpu.irq
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CONFIG_MPU_IRQ must be specified if MPU_IO is set.&bslash;n&quot;
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
id|trix_boot
)paren
(brace
id|fw_load
op_assign
l_int|1
suffix:semicolon
id|trix_boot_len
op_assign
id|mod_firmware_load
c_func
(paren
l_string|&quot;/etc/sound/trxpro.bin&quot;
comma
(paren
r_char
op_star
op_star
)paren
op_amp
id|trix_boot
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|probe_trix_wss
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
id|attach_trix_wss
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *    We must attach in the right order to get the firmware&n;&t; *      loaded up in time.&n;&t; */
r_if
c_cond
(paren
id|cfg2.io_base
op_ne
op_minus
l_int|1
)paren
(brace
id|sb
op_assign
id|probe_trix_sb
c_func
(paren
op_amp
id|cfg2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cfg_mpu.io_base
op_ne
op_minus
l_int|1
)paren
id|mpu
op_assign
id|probe_trix_mpu
c_func
(paren
op_amp
id|cfg_mpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_trix
r_static
r_void
id|__exit
id|cleanup_trix
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|fw_load
op_logical_and
id|trix_boot
)paren
id|vfree
c_func
(paren
id|trix_boot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb
)paren
id|unload_trix_sb
c_func
(paren
op_amp
id|cfg2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpu
)paren
id|unload_trix_mpu
c_func
(paren
op_amp
id|cfg_mpu
)paren
suffix:semicolon
id|unload_trix_wss
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
)brace
DECL|variable|init_trix
id|module_init
c_func
(paren
id|init_trix
)paren
suffix:semicolon
DECL|variable|cleanup_trix
id|module_exit
c_func
(paren
id|cleanup_trix
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|setup_trix
r_static
r_int
id|__init
id|setup_trix
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* io, irq, dma, dma2, sb_io, sb_irq, sb_dma, mpu_io, mpu_irq */
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
id|dma2
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
l_int|6
)braket
suffix:semicolon
id|mpu_io
op_assign
id|ints
(braket
l_int|7
)braket
suffix:semicolon
id|mpu_irq
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
l_string|&quot;trix=&quot;
comma
id|setup_trix
)paren
suffix:semicolon
macro_line|#endif
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
