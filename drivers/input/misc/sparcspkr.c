multiline_comment|/*&n; *  Driver for PC-speaker like devices found on various Sparc systems.&n; *&n; *  Copyright (c) 2002 Vojtech Pavlik&n; *  Copyright (c) 2002 David S. Miller (davem@redhat.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
macro_line|#ifdef CONFIG_SPARC64
macro_line|#include &lt;asm/isa.h&gt;
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David S. Miller &lt;davem@redhat.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PC Speaker beeper driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|beep_iobase
r_static
r_int
r_int
id|beep_iobase
suffix:semicolon
DECL|variable|sparcspkr_isa_name
r_static
r_char
op_star
id|sparcspkr_isa_name
op_assign
l_string|&quot;Sparc ISA Speaker&quot;
suffix:semicolon
DECL|variable|sparcspkr_ebus_name
r_static
r_char
op_star
id|sparcspkr_ebus_name
op_assign
l_string|&quot;Sparc EBUS Speaker&quot;
suffix:semicolon
DECL|variable|sparcspkr_phys
r_static
r_char
op_star
id|sparcspkr_phys
op_assign
l_string|&quot;sparc/input0&quot;
suffix:semicolon
DECL|variable|sparcspkr_dev
r_static
r_struct
id|input_dev
id|sparcspkr_dev
suffix:semicolon
DECL|variable|beep_lock
id|spinlock_t
id|beep_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|init_sparcspkr_struct
r_static
r_void
id|__init
id|init_sparcspkr_struct
c_func
(paren
r_void
)paren
(brace
id|sparcspkr_dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_SND
)paren
suffix:semicolon
id|sparcspkr_dev.sndbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|SND_BELL
)paren
op_or
id|BIT
c_func
(paren
id|SND_TONE
)paren
suffix:semicolon
id|sparcspkr_dev.phys
op_assign
id|sparcspkr_phys
suffix:semicolon
id|sparcspkr_dev.id.bustype
op_assign
id|BUS_ISA
suffix:semicolon
id|sparcspkr_dev.id.vendor
op_assign
l_int|0x001f
suffix:semicolon
id|sparcspkr_dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|sparcspkr_dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
)brace
DECL|function|ebus_spkr_event
r_static
r_int
id|ebus_spkr_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|EV_SND
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|SND_BELL
suffix:colon
r_if
c_cond
(paren
id|value
)paren
id|value
op_assign
l_int|1000
suffix:semicolon
r_case
id|SND_TONE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
OG
l_int|20
op_logical_and
id|value
OL
l_int|32767
)paren
id|count
op_assign
l_int|1193182
op_div
id|value
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|beep_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* EBUS speaker only has on/off state, the frequency does not&n;&t; * appear to be programmable.&n;&t; */
r_if
c_cond
(paren
id|count
)paren
(brace
r_if
c_cond
(paren
id|beep_iobase
op_amp
l_int|0x2UL
)paren
id|outb
c_func
(paren
l_int|1
comma
id|beep_iobase
)paren
suffix:semicolon
r_else
id|outl
c_func
(paren
l_int|1
comma
id|beep_iobase
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|beep_iobase
op_amp
l_int|0x2UL
)paren
id|outb
c_func
(paren
l_int|0
comma
id|beep_iobase
)paren
suffix:semicolon
r_else
id|outl
c_func
(paren
l_int|0
comma
id|beep_iobase
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|beep_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_ebus_beep
r_static
r_int
id|__init
id|init_ebus_beep
c_func
(paren
r_struct
id|linux_ebus_device
op_star
id|edev
)paren
(brace
id|beep_iobase
op_assign
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|init_sparcspkr_struct
c_func
(paren
)paren
suffix:semicolon
id|sparcspkr_dev.name
op_assign
id|sparcspkr_ebus_name
suffix:semicolon
id|sparcspkr_dev.event
op_assign
id|ebus_spkr_event
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|sparcspkr_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s&bslash;n&quot;
comma
id|sparcspkr_ebus_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SPARC64
DECL|function|isa_spkr_event
r_static
r_int
id|isa_spkr_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_int
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|EV_SND
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|SND_BELL
suffix:colon
r_if
c_cond
(paren
id|value
)paren
id|value
op_assign
l_int|1000
suffix:semicolon
r_case
id|SND_TONE
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|value
OG
l_int|20
op_logical_and
id|value
OL
l_int|32767
)paren
id|count
op_assign
l_int|1193182
op_div
id|value
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|beep_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
)paren
(brace
multiline_comment|/* enable counter 2 */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|beep_iobase
op_plus
l_int|0x61
)paren
op_or
l_int|3
comma
id|beep_iobase
op_plus
l_int|0x61
)paren
suffix:semicolon
multiline_comment|/* set command for counter 2, 2 byte write */
id|outb
c_func
(paren
l_int|0xB6
comma
id|beep_iobase
op_plus
l_int|0x43
)paren
suffix:semicolon
multiline_comment|/* select desired HZ */
id|outb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|beep_iobase
op_plus
l_int|0x42
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|count
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|beep_iobase
op_plus
l_int|0x42
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* disable counter 2 */
id|outb
c_func
(paren
id|inb_p
c_func
(paren
id|beep_iobase
op_plus
l_int|0x61
)paren
op_amp
l_int|0xFC
comma
id|beep_iobase
op_plus
l_int|0x61
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|beep_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_isa_beep
r_static
r_int
id|__init
id|init_isa_beep
c_func
(paren
r_struct
id|isa_device
op_star
id|isa_dev
)paren
(brace
id|beep_iobase
op_assign
id|isa_dev-&gt;resource.start
suffix:semicolon
id|init_sparcspkr_struct
c_func
(paren
)paren
suffix:semicolon
id|sparcspkr_dev.name
op_assign
id|sparcspkr_isa_name
suffix:semicolon
id|sparcspkr_dev.event
op_assign
id|isa_spkr_event
suffix:semicolon
id|sparcspkr_dev.id.bustype
op_assign
id|BUS_ISA
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|sparcspkr_dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s&bslash;n&quot;
comma
id|sparcspkr_isa_name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sparcspkr_init
r_static
r_int
id|__init
id|sparcspkr_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|linux_ebus
op_star
id|ebus
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef CONFIG_SPARC64
r_struct
id|isa_bridge
op_star
id|isa_br
suffix:semicolon
r_struct
id|isa_device
op_star
id|isa_dev
suffix:semicolon
macro_line|#endif
id|for_each_ebus
c_func
(paren
id|ebus
)paren
(brace
id|for_each_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
l_string|&quot;beep&quot;
)paren
)paren
r_return
id|init_ebus_beep
c_func
(paren
id|edev
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SPARC64
id|for_each_isa
c_func
(paren
id|isa_br
)paren
(brace
id|for_each_isadev
c_func
(paren
id|isa_dev
comma
id|isa_br
)paren
(brace
multiline_comment|/* A hack, the beep device&squot;s base lives in&n;&t;&t;&t; * the DMA isa node.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|isa_dev-&gt;prom_name
comma
l_string|&quot;dma&quot;
)paren
)paren
r_return
id|init_isa_beep
c_func
(paren
id|isa_dev
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|sparcspkr_exit
r_static
r_void
id|__exit
id|sparcspkr_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|sparcspkr_dev
)paren
suffix:semicolon
)brace
DECL|variable|sparcspkr_init
id|module_init
c_func
(paren
id|sparcspkr_init
)paren
suffix:semicolon
DECL|variable|sparcspkr_exit
id|module_exit
c_func
(paren
id|sparcspkr_exit
)paren
suffix:semicolon
eof