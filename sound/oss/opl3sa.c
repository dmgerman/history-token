multiline_comment|/*&n; * sound/opl3sa.c&n; *&n; * Low level driver for Yamaha YMF701B aka OPL3-SA chip&n; * &n; *&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; *&n; * Changes:&n; *&t;Alan Cox&t;&t;Modularisation&n; *&t;Christoph Hellwig&t;Adapted to module_init/module_exit&n; *&t;Arnaldo C. de Melo&t;got rid of attach_uart401&n; *&n; * FIXME:&n; * &t;Check for install of mpu etc is wrong, should check result of the mss stuff&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|SB_OK
macro_line|#undef  SB_OK
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;ad1848.h&quot;
macro_line|#include &quot;mpu401.h&quot;
macro_line|#ifdef SB_OK
macro_line|#include &quot;sb.h&quot;
DECL|variable|sb_initialized
r_static
r_int
id|sb_initialized
suffix:semicolon
macro_line|#endif
r_static
id|DEFINE_SPINLOCK
c_func
(paren
id|lock
)paren
suffix:semicolon
DECL|function|opl3sa_read
r_static
r_int
r_char
id|opl3sa_read
c_func
(paren
r_int
id|addr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|tmp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|0x1d
)paren
comma
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* password */
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
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* address */
id|tmp
op_assign
id|inb
c_func
(paren
l_int|0xf87
)paren
suffix:semicolon
multiline_comment|/* data */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|opl3sa_write
r_static
r_void
id|opl3sa_write
c_func
(paren
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|0x1d
)paren
comma
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* password */
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
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* address */
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
l_int|0xf87
)paren
suffix:semicolon
multiline_comment|/* data */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|opl3sa_detect
r_static
r_int
id|__init
id|opl3sa_detect
c_func
(paren
r_void
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|tmp
op_assign
id|opl3sa_read
c_func
(paren
l_int|0x01
)paren
)paren
op_amp
l_int|0xc4
)paren
op_ne
l_int|0x04
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA detect error 1 (%x)&bslash;n&quot;
comma
id|opl3sa_read
c_func
(paren
l_int|0x01
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* return 0; */
)brace
multiline_comment|/*&n;&t; * Check that the password feature has any effect&n;&t; */
r_if
c_cond
(paren
id|inb
c_func
(paren
l_int|0xf87
)paren
op_eq
id|tmp
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA detect failed 2 (%x/%x)&bslash;n&quot;
comma
id|tmp
comma
id|inb
c_func
(paren
l_int|0xf87
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_assign
(paren
id|opl3sa_read
c_func
(paren
l_int|0x04
)paren
op_amp
l_int|0xe0
)paren
op_rshift
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
l_int|0
op_logical_and
id|tmp
op_ne
l_int|1
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA detect failed 3 (%d)&bslash;n&quot;
comma
id|tmp
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA mode %x detected&bslash;n&quot;
comma
id|tmp
)paren
)paren
suffix:semicolon
id|opl3sa_write
c_func
(paren
l_int|0x01
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable MSS */
id|opl3sa_write
c_func
(paren
l_int|0x02
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable SB */
id|opl3sa_write
c_func
(paren
l_int|0x03
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable MPU */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *    Probe and attach routines for the Windows Sound System mode of&n; *     OPL3-SA&n; */
DECL|function|probe_opl3sa_wss
r_static
r_int
id|__init
id|probe_opl3sa_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_struct
id|resource
op_star
id|ports
)paren
(brace
r_int
r_char
id|tmp
op_assign
l_int|0x24
suffix:semicolon
multiline_comment|/* WSS enable */
multiline_comment|/*&n;&t; * Check if the IO port returns valid signature. The original MS Sound&n;&t; * system returns 0x04 while some cards (OPL3-SA for example)&n;&t; * return 0x00.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|opl3sa_detect
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;OSS: OPL3-SA chip not found&bslash;n&quot;
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
l_int|0x530
suffix:colon
id|tmp
op_or_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe80
suffix:colon
id|tmp
op_or_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf40
suffix:colon
id|tmp
op_or_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x604
suffix:colon
id|tmp
op_or_assign
l_int|0x18
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;OSS: Unsupported OPL3-SA/WSS base %x&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|opl3sa_write
c_func
(paren
l_int|0x01
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* WSS setup register */
r_return
id|probe_ms_sound
c_func
(paren
id|hw_config
comma
id|ports
)paren
suffix:semicolon
)brace
DECL|function|attach_opl3sa_wss
r_static
r_void
id|__init
id|attach_opl3sa_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_struct
id|resource
op_star
id|ports
)paren
(brace
r_int
id|nm
op_assign
id|num_mixers
suffix:semicolon
multiline_comment|/* FIXME */
id|attach_ms_sound
c_func
(paren
id|hw_config
comma
id|ports
comma
id|THIS_MODULE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_mixers
OG
id|nm
)paren
multiline_comment|/* A mixer was installed */
(brace
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE1
comma
id|SOUND_MIXER_CD
)paren
suffix:semicolon
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE2
comma
id|SOUND_MIXER_SYNTH
)paren
suffix:semicolon
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE3
comma
id|SOUND_MIXER_LINE
)paren
suffix:semicolon
)brace
)brace
DECL|function|probe_opl3sa_mpu
r_static
r_int
id|__init
id|probe_opl3sa_mpu
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
r_char
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
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|1
comma
op_minus
l_int|1
comma
l_int|2
comma
op_minus
l_int|1
comma
l_int|3
comma
l_int|4
)brace
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|10
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;OPL3-SA: Bad MPU IRQ %d&bslash;n&quot;
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
l_string|&quot;OPL3-SA: Bad MPU IRQ %d&bslash;n&quot;
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
l_int|0x332
suffix:colon
id|conf
op_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x334
suffix:colon
id|conf
op_assign
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x300
suffix:colon
id|conf
op_assign
l_int|0x60
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
l_int|0x83
suffix:semicolon
multiline_comment|/* MPU &amp; OPL3 (synth) &amp; game port enable */
id|conf
op_or_assign
id|irq_bits
(braket
id|hw_config-&gt;irq
)braket
op_lshift
l_int|2
suffix:semicolon
id|opl3sa_write
c_func
(paren
l_int|0x03
comma
id|conf
)paren
suffix:semicolon
id|hw_config-&gt;name
op_assign
l_string|&quot;OPL3-SA (MPU401)&quot;
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
DECL|function|unload_opl3sa_wss
r_static
r_void
id|__exit
id|unload_opl3sa_wss
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
l_int|0xf86
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
DECL|function|unload_opl3sa_mpu
r_static
r_inline
r_void
id|__exit
id|unload_opl3sa_mpu
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
macro_line|#ifdef SB_OK
DECL|function|unload_opl3sa_sb
r_static
r_inline
r_void
id|__exit
id|unload_opl3sa_sb
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
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|found_mpu
r_static
r_int
id|found_mpu
suffix:semicolon
DECL|variable|cfg
r_static
r_struct
id|address_info
id|cfg
suffix:semicolon
DECL|variable|cfg_mpu
r_static
r_struct
id|address_info
id|cfg_mpu
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
id|module_param
c_func
(paren
id|io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|irq
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|dma
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|dma2
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|mpu_io
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
id|module_param
c_func
(paren
id|mpu_irq
comma
r_int
comma
l_int|0
)paren
suffix:semicolon
DECL|function|init_opl3sa
r_static
r_int
id|__init
id|init_opl3sa
c_func
(paren
r_void
)paren
(brace
r_struct
id|resource
op_star
id|ports
suffix:semicolon
r_if
c_cond
(paren
id|io
op_eq
op_minus
l_int|1
op_logical_or
id|irq
op_eq
op_minus
l_int|1
op_logical_or
id|dma
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;opl3sa: dma, irq and io must be set.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|cfg_mpu.io_base
op_assign
id|mpu_io
suffix:semicolon
id|cfg_mpu.irq
op_assign
id|mpu_irq
suffix:semicolon
id|ports
op_assign
id|request_region
c_func
(paren
id|io
op_plus
l_int|4
comma
l_int|4
comma
l_string|&quot;ad1848&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ports
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
l_int|0xf86
comma
l_int|2
comma
l_string|&quot;OPL3-SA&quot;
)paren
)paren
multiline_comment|/* Control port is busy */
(brace
id|release_region
c_func
(paren
id|io
op_plus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
l_int|4
comma
l_string|&quot;WSS config&quot;
)paren
)paren
(brace
id|release_region
c_func
(paren
l_int|0x86
comma
l_int|2
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
op_plus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|probe_opl3sa_wss
c_func
(paren
op_amp
id|cfg
comma
id|ports
)paren
op_eq
l_int|0
)paren
(brace
id|release_region
c_func
(paren
l_int|0xf86
comma
l_int|2
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|4
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
op_plus
l_int|4
comma
l_int|4
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|found_mpu
op_assign
id|probe_opl3sa_mpu
c_func
(paren
op_amp
id|cfg_mpu
)paren
suffix:semicolon
id|attach_opl3sa_wss
c_func
(paren
op_amp
id|cfg
comma
id|ports
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_opl3sa
r_static
r_void
id|__exit
id|cleanup_opl3sa
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|found_mpu
)paren
(brace
id|unload_opl3sa_mpu
c_func
(paren
op_amp
id|cfg_mpu
)paren
suffix:semicolon
)brace
id|unload_opl3sa_wss
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
)brace
DECL|variable|init_opl3sa
id|module_init
c_func
(paren
id|init_opl3sa
)paren
suffix:semicolon
DECL|variable|cleanup_opl3sa
id|module_exit
c_func
(paren
id|cleanup_opl3sa
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|setup_opl3sa
r_static
r_int
id|__init
id|setup_opl3sa
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* io, irq, dma, dma2, mpu_io, mpu_irq */
r_int
id|ints
(braket
l_int|7
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
id|mpu_io
op_assign
id|ints
(braket
l_int|5
)braket
suffix:semicolon
id|mpu_irq
op_assign
id|ints
(braket
l_int|6
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;opl3sa=&quot;
comma
id|setup_opl3sa
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
