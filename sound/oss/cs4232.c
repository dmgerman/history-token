multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; *&t;cs4232.c&n; *&n; * The low level driver for Crystal CS4232 based cards. The CS4232 is&n; * a PnP compatible chip which contains a CS4231A codec, SB emulation,&n; * a MPU401 compatible MIDI port, joystick and synthesizer and IDE CD-ROM &n; * interfaces. This is just a temporary driver until full PnP support&n; * gets implemented. Just the WSS codec, FM synth and the MIDI ports are&n; * supported. Other interfaces are left uninitialized.&n; *&n; * ifdef ...WAVEFRONT...&n; * &n; *   Support is provided for initializing the WaveFront synth&n; *   interface as well, which is logical device #4. Note that if&n; *   you have a Tropez+ card, you probably don&squot;t need to setup&n; *   the CS4232-supported MIDI interface, since it corresponds to&n; *   the internal 26-pin header that&squot;s hard to access. Using this&n; *   requires an additional IRQ, a resource none too plentiful in&n; *   this environment. Just don&squot;t set module parameters mpuio and&n; *   mpuirq, and the MIDI port will be left uninitialized. You can&n; *   still use the ICS2115 hosted MIDI interface which corresponds&n; *   to the 9-pin D connector on the back of the card.&n; *&n; * endif  ...WAVEFRONT...&n; *&n; * Supported chips are:&n; *      CS4232&n; *      CS4236&n; *      CS4236B&n; *&n; * Note: You will need a PnP config setup to initialise some CS4232 boards&n; * anyway.&n; *&n; * Changes&n; *&t;Alan Cox&t;&t;Modularisation, Basic cleanups.&n; *      Paul Barton-Davis&t;Separated MPU configuration, added&n; *                                       Tropez+ (WaveFront) support&n; *&t;Christoph Hellwig&t;Adapted to module_init/module_exit,&n; * &t;&t;&t;&t;&t;simple cleanups&n; * &t;Arnaldo C. de Melo&t;got rid of attach_uart401&n; *&t;Bartlomiej Zolnierkiewicz&n; *&t;&t;&t;&t;Added some __init/__initdata/__exit&n; *&t;Marcus Meissner&t;&t;Added ISA PnP support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;cs4232.h&quot;
macro_line|#include &quot;ad1848.h&quot;
macro_line|#include &quot;mpu401.h&quot;
DECL|macro|KEY_PORT
mdefine_line|#define KEY_PORT&t;0x279&t;/* Same as LPT1 status port */
DECL|macro|CSN_NUM
mdefine_line|#define CSN_NUM&t;&t;0x99&t;/* Just a random number */
DECL|function|CS_OUT
r_static
r_void
id|CS_OUT
c_func
(paren
r_int
r_char
id|a
)paren
(brace
id|outb
c_func
(paren
id|a
comma
id|KEY_PORT
)paren
suffix:semicolon
)brace
DECL|macro|CS_OUT2
mdefine_line|#define CS_OUT2(a, b)&t;&t;{CS_OUT(a);CS_OUT(b);}
DECL|macro|CS_OUT3
mdefine_line|#define CS_OUT3(a, b, c)&t;{CS_OUT(a);CS_OUT(b);CS_OUT(c);}
DECL|variable|mpu_base
DECL|variable|mpu_irq
r_static
r_int
id|mpu_base
op_assign
l_int|0
comma
id|mpu_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|synth_base
DECL|variable|synth_irq
r_static
r_int
id|synth_base
op_assign
l_int|0
comma
id|synth_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|mpu_detected
r_static
r_int
id|mpu_detected
op_assign
l_int|0
suffix:semicolon
DECL|function|probe_cs4232_mpu
r_int
id|probe_cs4232_mpu
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
multiline_comment|/*&n;&t; *&t;Just write down the config values.&n;&t; */
id|mpu_base
op_assign
id|hw_config-&gt;io_base
suffix:semicolon
id|mpu_irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|crystal_key
r_static
r_int
r_char
id|crystal_key
(braket
)braket
op_assign
multiline_comment|/* A 32 byte magic key sequence */
(brace
l_int|0x96
comma
l_int|0x35
comma
l_int|0x9a
comma
l_int|0xcd
comma
l_int|0xe6
comma
l_int|0xf3
comma
l_int|0x79
comma
l_int|0xbc
comma
l_int|0x5e
comma
l_int|0xaf
comma
l_int|0x57
comma
l_int|0x2b
comma
l_int|0x15
comma
l_int|0x8a
comma
l_int|0xc5
comma
l_int|0xe2
comma
l_int|0xf1
comma
l_int|0xf8
comma
l_int|0x7c
comma
l_int|0x3e
comma
l_int|0x9f
comma
l_int|0x4f
comma
l_int|0x27
comma
l_int|0x13
comma
l_int|0x09
comma
l_int|0x84
comma
l_int|0x42
comma
l_int|0xa1
comma
l_int|0xd0
comma
l_int|0x68
comma
l_int|0x34
comma
l_int|0x1a
)brace
suffix:semicolon
DECL|function|sleep
r_static
r_void
id|sleep
c_func
(paren
r_int
id|howlong
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|howlong
)paren
suffix:semicolon
)brace
DECL|function|probe_cs4232
r_int
id|probe_cs4232
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
comma
r_int
id|isapnp_configured
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
r_int
id|base
op_assign
id|hw_config-&gt;io_base
comma
id|irq
op_assign
id|hw_config-&gt;irq
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
multiline_comment|/*&n;&t; * Verify that the I/O port range is free.&n;&t; */
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|base
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs4232.c: I/O port 0x%03x not free&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ad1848_detect
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|NULL
comma
id|hw_config-&gt;osp
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* The card is already active */
)brace
r_if
c_cond
(paren
id|isapnp_configured
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs4232.c: ISA PnP configured, but not detected?&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * This version of the driver doesn&squot;t use the PnP method when configuring&n;&t; * the card but a simplified method defined by Crystal. This means that&n;&t; * just one CS4232 compatible device can exist on the system. Also this&n;&t; * method conflicts with possible PnP support in the OS. For this reason &n;&t; * driver is just a temporary kludge.&n;&t; *&n;&t; * Also the Cirrus/Crystal method doesnt always work. Try ISA PnP first ;)&n;&t; */
multiline_comment|/*&n;&t; * Repeat initialization few times since it doesn&squot;t always succeed in&n;&t; * first time.&n;&t; */
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
l_int|4
suffix:semicolon
id|n
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Wake up the card by sending a 32 byte Crystal key to the key port.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
id|CS_OUT
c_func
(paren
id|crystal_key
(braket
id|i
)braket
)paren
suffix:semicolon
id|sleep
c_func
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Now set the CSN (Card Select Number).&n;&t;&t; */
id|CS_OUT2
c_func
(paren
l_int|0x06
comma
id|CSN_NUM
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Then set some config bytes. First logical device 0 &n;&t;&t; */
id|CS_OUT2
c_func
(paren
l_int|0x15
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Select logical device 0 (WSS/SB/FM) */
id|CS_OUT3
c_func
(paren
l_int|0x47
comma
(paren
id|base
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|base
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* WSS base */
r_if
c_cond
(paren
id|check_region
c_func
(paren
l_int|0x388
comma
l_int|4
)paren
)paren
multiline_comment|/* Not free */
id|CS_OUT3
c_func
(paren
l_int|0x48
comma
l_int|0x00
comma
l_int|0x00
)paren
multiline_comment|/* FM base off */
r_else
id|CS_OUT3
c_func
(paren
l_int|0x48
comma
l_int|0x03
comma
l_int|0x88
)paren
suffix:semicolon
multiline_comment|/* FM base 0x388 */
id|CS_OUT3
c_func
(paren
l_int|0x42
comma
l_int|0x00
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* SB base off */
id|CS_OUT2
c_func
(paren
l_int|0x22
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* SB+WSS IRQ */
id|CS_OUT2
c_func
(paren
l_int|0x2a
comma
id|dma1
)paren
suffix:semicolon
multiline_comment|/* SB+WSS DMA */
r_if
c_cond
(paren
id|dma2
op_ne
op_minus
l_int|1
)paren
id|CS_OUT2
c_func
(paren
l_int|0x25
comma
id|dma2
)paren
multiline_comment|/* WSS DMA2 */
r_else
id|CS_OUT2
c_func
(paren
l_int|0x25
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* No WSS DMA2 */
id|CS_OUT2
c_func
(paren
l_int|0x33
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Activate logical dev 0 */
id|sleep
c_func
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Initialize logical device 3 (MPU)&n;&t;&t; */
r_if
c_cond
(paren
id|mpu_base
op_ne
l_int|0
op_logical_and
id|mpu_irq
op_ne
l_int|0
)paren
(brace
id|CS_OUT2
c_func
(paren
l_int|0x15
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Select logical device 3 (MPU) */
id|CS_OUT3
c_func
(paren
l_int|0x47
comma
(paren
id|mpu_base
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|mpu_base
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* MPU base */
id|CS_OUT2
c_func
(paren
l_int|0x22
comma
id|mpu_irq
)paren
suffix:semicolon
multiline_comment|/* MPU IRQ */
id|CS_OUT2
c_func
(paren
l_int|0x33
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Activate logical dev 3 */
)brace
r_if
c_cond
(paren
id|synth_base
op_ne
l_int|0
)paren
(brace
id|CS_OUT2
(paren
l_int|0x15
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* logical device 4 (WaveFront) */
id|CS_OUT3
(paren
l_int|0x47
comma
(paren
id|synth_base
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|synth_base
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* base */
id|CS_OUT2
(paren
l_int|0x22
comma
id|synth_irq
)paren
suffix:semicolon
multiline_comment|/* IRQ */
id|CS_OUT2
(paren
l_int|0x33
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Activate logical dev 4 */
)brace
multiline_comment|/*&n;&t;&t; * Finally activate the chip&n;&t;&t; */
id|CS_OUT
c_func
(paren
l_int|0x79
)paren
suffix:semicolon
id|sleep
c_func
(paren
id|HZ
op_div
l_int|5
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Then try to detect the codec part of the chip&n;&t;&t; */
r_if
c_cond
(paren
id|ad1848_detect
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|NULL
comma
id|hw_config-&gt;osp
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|sleep
c_func
(paren
id|HZ
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|attach_cs4232
r_void
id|attach_cs4232
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|base
op_assign
id|hw_config-&gt;io_base
comma
id|irq
op_assign
id|hw_config-&gt;irq
comma
id|dma1
op_assign
id|hw_config-&gt;dma
comma
id|dma2
op_assign
id|hw_config-&gt;dma2
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
op_minus
l_int|1
op_logical_or
id|irq
op_eq
op_minus
l_int|1
op_logical_or
id|dma1
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs4232: dma, irq and io must be set.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|dma1
suffix:semicolon
id|hw_config-&gt;slots
(braket
l_int|0
)braket
op_assign
id|ad1848_init
c_func
(paren
l_string|&quot;Crystal audio controller&quot;
comma
id|base
comma
id|irq
comma
id|dma1
comma
multiline_comment|/* Playback DMA */
id|dma2
comma
multiline_comment|/* Capture DMA */
l_int|0
comma
id|hw_config-&gt;osp
comma
id|THIS_MODULE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;slots
(braket
l_int|0
)braket
op_ne
op_minus
l_int|1
op_logical_and
id|audio_devs
(braket
id|hw_config-&gt;slots
(braket
l_int|0
)braket
)braket
op_member_access_from_pointer
id|mixer_dev
op_ne
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Assume the mixer map is as suggested in the CS4232 databook */
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE1
comma
id|SOUND_MIXER_LINE
)paren
suffix:semicolon
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
multiline_comment|/* FM synth */
)brace
r_if
c_cond
(paren
id|mpu_base
op_ne
l_int|0
op_logical_and
id|mpu_irq
op_ne
l_int|0
)paren
(brace
r_static
r_struct
id|address_info
id|hw_config2
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Ensure it&squot;s initialized */
id|hw_config2.io_base
op_assign
id|mpu_base
suffix:semicolon
id|hw_config2.irq
op_assign
id|mpu_irq
suffix:semicolon
id|hw_config2.dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.dma2
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.always_detect
op_assign
l_int|0
suffix:semicolon
id|hw_config2.name
op_assign
l_int|NULL
suffix:semicolon
id|hw_config2.driver_use_1
op_assign
l_int|0
suffix:semicolon
id|hw_config2.driver_use_2
op_assign
l_int|0
suffix:semicolon
id|hw_config2.card_subtype
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|probe_uart401
c_func
(paren
op_amp
id|hw_config2
comma
id|THIS_MODULE
)paren
)paren
(brace
id|mpu_detected
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|mpu_base
op_assign
id|mpu_irq
op_assign
l_int|0
suffix:semicolon
)brace
id|hw_config-&gt;slots
(braket
l_int|1
)braket
op_assign
id|hw_config2.slots
(braket
l_int|1
)braket
suffix:semicolon
)brace
)brace
DECL|function|unload_cs4232
r_static
r_void
id|unload_cs4232
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|base
op_assign
id|hw_config-&gt;io_base
comma
id|irq
op_assign
id|hw_config-&gt;irq
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
id|dma1
suffix:semicolon
id|ad1848_unload
c_func
(paren
id|base
comma
id|irq
comma
id|dma1
comma
multiline_comment|/* Playback DMA */
id|dma2
comma
multiline_comment|/* Capture DMA */
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
r_if
c_cond
(paren
id|mpu_base
op_ne
l_int|0
op_logical_and
id|mpu_irq
op_ne
l_int|0
op_logical_and
id|mpu_detected
)paren
(brace
r_static
r_struct
id|address_info
id|hw_config2
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Ensure it&squot;s initialized */
id|hw_config2.io_base
op_assign
id|mpu_base
suffix:semicolon
id|hw_config2.irq
op_assign
id|mpu_irq
suffix:semicolon
id|hw_config2.dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.dma2
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.always_detect
op_assign
l_int|0
suffix:semicolon
id|hw_config2.name
op_assign
l_int|NULL
suffix:semicolon
id|hw_config2.driver_use_1
op_assign
l_int|0
suffix:semicolon
id|hw_config2.driver_use_2
op_assign
l_int|0
suffix:semicolon
id|hw_config2.card_subtype
op_assign
l_int|0
suffix:semicolon
id|hw_config2.slots
(braket
l_int|1
)braket
op_assign
id|hw_config-&gt;slots
(braket
l_int|1
)braket
suffix:semicolon
id|unload_uart401
c_func
(paren
op_amp
id|hw_config2
)paren
suffix:semicolon
)brace
)brace
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
DECL|variable|mpuio
r_static
r_int
id|__initdata
id|mpuio
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mpuirq
r_static
r_int
id|__initdata
id|mpuirq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|synthio
r_static
r_int
id|__initdata
id|synthio
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|synthirq
r_static
r_int
id|__initdata
id|synthirq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|isapnp
r_static
r_int
id|__initdata
id|isapnp
op_assign
l_int|1
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CS4232 based soundcard driver&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Hannu Savolainen, Paul Barton-Davis&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;base I/O port for AD1848&quot;
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
id|MODULE_PARM_DESC
c_func
(paren
id|irq
comma
l_string|&quot;IRQ for AD1848 chip&quot;
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
id|MODULE_PARM_DESC
c_func
(paren
id|dma
comma
l_string|&quot;8 bit DMA for AD1848 chip&quot;
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
id|MODULE_PARM_DESC
c_func
(paren
id|dma2
comma
l_string|&quot;16 bit DMA for AD1848 chip&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mpuio
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mpuio
comma
l_string|&quot;MPU 401 base address&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mpuirq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mpuirq
comma
l_string|&quot;MPU 401 IRQ&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|synthio
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|synthio
comma
l_string|&quot;Maui WaveTable base I/O port&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|synthirq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|synthirq
comma
l_string|&quot;Maui WaveTable IRQ&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|isapnp
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|isapnp
comma
l_string|&quot;Enable ISAPnP probing (default 1)&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Install a CS4232 based card. Need to have ad1848 and mpu401&n; *&t;loaded ready.&n; */
multiline_comment|/* All cs4232 based cards have the main ad1848 card either as CSC0000 or&n; * CSC0100. */
DECL|variable|cs4232_pnp_table
r_static
r_const
r_struct
id|pnp_device_id
id|cs4232_pnp_table
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
l_string|&quot;CSC0100&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;CSC0000&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* Guillemot Turtlebeach something appears to be cs4232 compatible&n;&t; * (untested) */
(brace
dot
id|id
op_assign
l_string|&quot;GIM0100&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
(brace
dot
id|id
op_assign
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pnp
comma
id|cs4232_pnp_table
)paren
suffix:semicolon
DECL|function|cs4232_pnp_probe
r_static
r_int
id|cs4232_pnp_probe
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|dev_id
)paren
(brace
r_struct
id|address_info
op_star
id|isapnpcfg
suffix:semicolon
id|isapnpcfg
op_assign
(paren
r_struct
id|address_info
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|isapnpcfg
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|isapnpcfg
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|isapnpcfg-&gt;irq
op_assign
id|pnp_irq
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|isapnpcfg-&gt;dma
op_assign
id|pnp_dma
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|isapnpcfg-&gt;dma2
op_assign
id|pnp_dma
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|isapnpcfg-&gt;io_base
op_assign
id|pnp_port_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|probe_cs4232
c_func
(paren
id|isapnpcfg
comma
id|TRUE
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cs4232: ISA PnP card found, but not detected?&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|isapnpcfg
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|attach_cs4232
c_func
(paren
id|isapnpcfg
)paren
suffix:semicolon
id|pnp_set_drvdata
c_func
(paren
id|dev
comma
id|isapnpcfg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cs4232_pnp_remove
r_static
r_void
id|cs4232_pnp_remove
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
r_struct
id|address_info
op_star
id|cfg
op_assign
id|pnp_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfg
)paren
(brace
id|unload_cs4232
c_func
(paren
id|cfg
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|cfg
)paren
suffix:semicolon
)brace
)brace
DECL|variable|cs4232_driver
r_static
r_struct
id|pnp_driver
id|cs4232_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;cs4232&quot;
comma
dot
id|id_table
op_assign
id|cs4232_pnp_table
comma
dot
id|probe
op_assign
id|cs4232_pnp_probe
comma
dot
id|remove
op_assign
id|cs4232_pnp_remove
comma
)brace
suffix:semicolon
DECL|function|init_cs4232
r_static
r_int
id|__init
id|init_cs4232
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SOUND_WAVEFRONT_MODULE
r_if
c_cond
(paren
id|synthio
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cs4232: set synthio and synthirq to use the wavefront facilities.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|synth_base
op_assign
id|synthio
suffix:semicolon
id|synth_irq
op_assign
id|synthirq
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|synthio
op_ne
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cs4232: wavefront support not enabled in this driver.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
id|cfg.irq
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|isapnp
op_logical_and
(paren
id|pnp_register_driver
c_func
(paren
op_amp
id|cs4232_driver
)paren
OG
l_int|0
)paren
)paren
r_return
l_int|0
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
l_string|&quot;cs4232: Must set io, irq and dma.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
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
op_minus
l_int|1
suffix:semicolon
id|cfg_mpu.irq
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|mpuio
op_ne
op_minus
l_int|1
op_logical_and
id|mpuirq
op_ne
op_minus
l_int|1
)paren
(brace
id|cfg_mpu.io_base
op_assign
id|mpuio
suffix:semicolon
id|cfg_mpu.irq
op_assign
id|mpuirq
suffix:semicolon
id|probe_cs4232_mpu
c_func
(paren
op_amp
id|cfg_mpu
)paren
suffix:semicolon
multiline_comment|/* Bug always returns 0 not OK -- AC */
)brace
r_if
c_cond
(paren
id|probe_cs4232
c_func
(paren
op_amp
id|cfg
comma
id|FALSE
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|attach_cs4232
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
DECL|function|cleanup_cs4232
r_static
r_void
id|__exit
id|cleanup_cs4232
c_func
(paren
r_void
)paren
(brace
id|pnp_unregister_driver
c_func
(paren
op_amp
id|cs4232_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfg.irq
op_ne
op_minus
l_int|1
)paren
id|unload_cs4232
c_func
(paren
op_amp
id|cfg
)paren
suffix:semicolon
multiline_comment|/* Unloads global MPU as well, if needed */
)brace
DECL|variable|init_cs4232
id|module_init
c_func
(paren
id|init_cs4232
)paren
suffix:semicolon
DECL|variable|cleanup_cs4232
id|module_exit
c_func
(paren
id|cleanup_cs4232
)paren
suffix:semicolon
macro_line|#ifndef MODULE
DECL|function|setup_cs4232
r_static
r_int
id|__init
id|setup_cs4232
c_func
(paren
r_char
op_star
id|str
)paren
(brace
multiline_comment|/* io, irq, dma, dma2 mpuio, mpuirq*/
r_int
id|ints
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* If we have isapnp cards, no need for options */
r_if
c_cond
(paren
id|pnp_register_driver
c_func
(paren
op_amp
id|cs4232_driver
)paren
OG
l_int|0
)paren
r_return
l_int|1
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
id|mpuio
op_assign
id|ints
(braket
l_int|5
)braket
suffix:semicolon
id|mpuirq
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
l_string|&quot;cs4232=&quot;
comma
id|setup_cs4232
)paren
suffix:semicolon
macro_line|#endif
eof
