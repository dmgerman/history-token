multiline_comment|/*&n;* cycx_drv.c&t;Cyclom 2X Support Module.&n;*&n;*&t;&t;This module is a library of common hardware specific&n;*&t;&t;functions used by the Cyclades Cyclom 2X sync card.&n;*&n;* Author:&t;Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt;&n;*&n;* Copyright:&t;(c) 1998-2003 Arnaldo Carvalho de Melo&n;*&n;* Based on sdladrv.c by Gene Kozin &lt;genek@compuserve.com&gt;&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* 1999/11/11&t;acme&t;&t;set_current_state(TASK_INTERRUPTIBLE), code&n;*&t;&t;&t;&t;cleanup&n;* 1999/11/08&t;acme&t;&t;init_cyc2x deleted, doing nothing&n;* 1999/11/06&t;acme&t;&t;back to read[bw], write[bw] and memcpy_to and&n;*&t;&t;&t;&t;fromio to use dpmbase ioremaped&n;* 1999/10/26&t;acme&t;&t;use isa_read[bw], isa_write[bw] &amp; isa_memcpy_to&n;*&t;&t;&t;&t;&amp; fromio&n;* 1999/10/23&t;acme&t;&t;cleanup to only supports cyclom2x: all the other&n;*&t;&t;&t;&t;boards are no longer manufactured by cyclades,&n;*&t;&t;&t;&t;if someone wants to support them... be my guest!&n;* 1999/05/28    acme&t;&t;cycx_intack &amp; cycx_intde gone for good&n;* 1999/05/18&t;acme&t;&t;lots of unlogged work, submitting to Linus...&n;* 1999/01/03&t;acme&t;&t;more judicious use of data types&n;* 1999/01/03&t;acme&t;&t;judicious use of data types :&gt;&n;*&t;&t;&t;&t;cycx_inten trying to reset pending interrupts&n;*&t;&t;&t;&t;from cyclom 2x - I think this isn&squot;t the way to&n;*&t;&t;&t;&t;go, but for now...&n;* 1999/01/02&t;acme&t;&t;cycx_intack ok, I think there&squot;s nothing to do&n;*&t;&t;&t;&t;to ack an int in cycx_drv.c, only handle it in&n;*&t;&t;&t;&t;cyx_isr (or in the other protocols: cyp_isr,&n;*&t;&t;&t;&t;cyf_isr, when they get implemented.&n;* Dec 31, 1998&t;acme&t;&t;cycx_data_boot &amp; cycx_code_boot fixed, crossing&n;*&t;&t;&t;&t;fingers to see x25_configure in cycx_x25.c&n;*&t;&t;&t;&t;work... :)&n;* Dec 26, 1998&t;acme&t;&t;load implementation fixed, seems to work! :)&n;*&t;&t;&t;&t;cycx_2x_dpmbase_options with all the possible&n;*&t;&t;&t;&t;DPM addresses (20).&n;*&t;&t;&t;&t;cycx_intr implemented (test this!)&n;*&t;&t;&t;&t;general code cleanup&n;* Dec  8, 1998&t;Ivan Passos&t;Cyclom-2X firmware load implementation.&n;* Aug  8, 1998&t;acme&t;&t;Initial version.&n;*/
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* __init */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;&t;/* printk(), and other useful stuff */
macro_line|#include &lt;linux/stddef.h&gt;&t;/* offsetof(), etc. */
macro_line|#include &lt;linux/errno.h&gt;&t;/* return codes */
macro_line|#include &lt;linux/sched.h&gt;&t;/* for jiffies, HZ, etc. */
macro_line|#include &lt;linux/cycx_drv.h&gt;&t;/* API definitions */
macro_line|#include &lt;linux/cycx_cfm.h&gt;&t;/* CYCX firmware module definitions */
macro_line|#include &lt;linux/delay.h&gt;&t;/* udelay */
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* read[wl], write[wl], ioremap, iounmap */
DECL|macro|MOD_VERSION
mdefine_line|#define&t;MOD_VERSION&t;0
DECL|macro|MOD_RELEASE
mdefine_line|#define&t;MOD_RELEASE&t;6
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Arnaldo Carvalho de Melo&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Cyclom 2x Sync Card Driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/* Hardware-specific functions */
r_static
r_int
id|load_cyc2x
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
r_struct
id|cycx_firmware
op_star
id|cfm
comma
id|u32
id|len
)paren
suffix:semicolon
r_static
r_void
id|cycx_bootcfg
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
suffix:semicolon
r_static
r_int
id|reset_cyc2x
c_func
(paren
id|u32
id|addr
)paren
suffix:semicolon
r_static
r_int
id|detect_cyc2x
c_func
(paren
id|u32
id|addr
)paren
suffix:semicolon
multiline_comment|/* Miscellaneous functions */
r_static
r_void
id|delay_cycx
c_func
(paren
r_int
id|sec
)paren
suffix:semicolon
r_static
r_int
id|get_option_index
c_func
(paren
id|u32
op_star
id|optlist
comma
id|u32
id|optval
)paren
suffix:semicolon
r_static
id|u16
id|checksum
c_func
(paren
id|u8
op_star
id|buf
comma
id|u32
id|len
)paren
suffix:semicolon
DECL|macro|wait_cyc
mdefine_line|#define wait_cyc(addr) cycx_exec(addr + CMD_OFFSET)
multiline_comment|/* Global Data */
multiline_comment|/* private data */
DECL|variable|modname
r_static
r_char
id|modname
(braket
)braket
op_assign
l_string|&quot;cycx_drv&quot;
suffix:semicolon
DECL|variable|fullname
r_static
r_char
id|fullname
(braket
)braket
op_assign
l_string|&quot;Cyclom 2X Support Module&quot;
suffix:semicolon
DECL|variable|copyright
r_static
r_char
id|copyright
(braket
)braket
op_assign
l_string|&quot;(c) 1998-2003 Arnaldo Carvalho de Melo &quot;
l_string|&quot;&lt;acme@conectiva.com.br&gt;&quot;
suffix:semicolon
multiline_comment|/* Hardware configuration options.&n; * These are arrays of configuration options used by verification routines.&n; * The first element of each array is its size (i.e. number of options).&n; */
DECL|variable|cyc2x_dpmbase_options
r_static
id|u32
id|cyc2x_dpmbase_options
(braket
)braket
op_assign
(brace
l_int|20
comma
l_int|0xA0000
comma
l_int|0xA4000
comma
l_int|0xA8000
comma
l_int|0xAC000
comma
l_int|0xB0000
comma
l_int|0xB4000
comma
l_int|0xB8000
comma
l_int|0xBC000
comma
l_int|0xC0000
comma
l_int|0xC4000
comma
l_int|0xC8000
comma
l_int|0xCC000
comma
l_int|0xD0000
comma
l_int|0xD4000
comma
l_int|0xD8000
comma
l_int|0xDC000
comma
l_int|0xE0000
comma
l_int|0xE4000
comma
l_int|0xE8000
comma
l_int|0xEC000
)brace
suffix:semicolon
DECL|variable|cycx_2x_irq_options
r_static
id|u32
id|cycx_2x_irq_options
(braket
)braket
op_assign
(brace
l_int|7
comma
l_int|3
comma
l_int|5
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|15
)brace
suffix:semicolon
multiline_comment|/* Kernel Loadable Module Entry Points */
multiline_comment|/* Module &squot;insert&squot; entry point.&n; * o print announcement&n; * o initialize static data&n; *&n; * Return:&t;0&t;Ok&n; *&t;&t;&lt; 0&t;error.&n; * Context:&t;process */
DECL|function|cycx_drv_init
r_int
id|__init
id|cycx_drv_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s v%u.%u %s&bslash;n&quot;
comma
id|fullname
comma
id|MOD_VERSION
comma
id|MOD_RELEASE
comma
id|copyright
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Module &squot;remove&squot; entry point.&n; * o release all remaining system resources */
DECL|function|cycx_drv_cleanup
r_void
id|cycx_drv_cleanup
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* Kernel APIs */
multiline_comment|/* Set up adapter.&n; * o detect adapter type&n; * o verify hardware configuration options&n; * o check for hardware conflicts&n; * o set up adapter shared memory&n; * o test adapter memory&n; * o load firmware&n; * Return:&t;0&t;ok.&n; *&t;&t;&lt; 0&t;error */
DECL|variable|cycx_setup
id|EXPORT_SYMBOL
c_func
(paren
id|cycx_setup
)paren
suffix:semicolon
DECL|function|cycx_setup
r_int
id|cycx_setup
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
r_void
op_star
id|cfm
comma
id|u32
id|len
)paren
(brace
r_int
r_int
id|dpmbase
op_assign
id|hw-&gt;dpmbase
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Verify IRQ configuration options */
r_if
c_cond
(paren
op_logical_neg
id|get_option_index
c_func
(paren
id|cycx_2x_irq_options
comma
id|hw-&gt;irq
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: IRQ %d is illegal!&bslash;n&quot;
comma
id|modname
comma
id|hw-&gt;irq
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Setup adapter dual-port memory window and test memory */
r_if
c_cond
(paren
op_logical_neg
id|hw-&gt;dpmbase
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: you must specify the dpm address!&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|get_option_index
c_func
(paren
id|cyc2x_dpmbase_options
comma
id|hw-&gt;dpmbase
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: memory address 0x%lX is illegal!&bslash;n&quot;
comma
id|modname
comma
id|dpmbase
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|hw-&gt;dpmbase
op_assign
(paren
id|u32
)paren
id|ioremap
c_func
(paren
id|dpmbase
comma
id|CYCX_WINDOWSIZE
)paren
suffix:semicolon
id|hw-&gt;dpmsize
op_assign
id|CYCX_WINDOWSIZE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|detect_cyc2x
c_func
(paren
id|hw-&gt;dpmbase
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: adapter Cyclom 2X not found at &quot;
l_string|&quot;address 0x%lX!&bslash;n&quot;
comma
id|modname
comma
id|dpmbase
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: found Cyclom 2X card at address 0x%lX.&bslash;n&quot;
comma
id|modname
comma
id|dpmbase
)paren
suffix:semicolon
multiline_comment|/* Load firmware. If loader fails then shut down adapter */
id|err
op_assign
id|load_cyc2x
c_func
(paren
id|hw
comma
id|cfm
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|cycx_down
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/* shutdown adapter */
r_return
id|err
suffix:semicolon
)brace
DECL|variable|cycx_down
id|EXPORT_SYMBOL
c_func
(paren
id|cycx_down
)paren
suffix:semicolon
DECL|function|cycx_down
r_int
id|cycx_down
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
(brace
id|iounmap
c_func
(paren
(paren
id|u32
op_star
)paren
id|hw-&gt;dpmbase
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Enable interrupt generation.  */
DECL|variable|cycx_inten
id|EXPORT_SYMBOL
c_func
(paren
id|cycx_inten
)paren
suffix:semicolon
DECL|function|cycx_inten
r_void
id|cycx_inten
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
(brace
id|writeb
c_func
(paren
l_int|0
comma
id|hw-&gt;dpmbase
)paren
suffix:semicolon
)brace
multiline_comment|/* Generate an interrupt to adapter&squot;s CPU. */
DECL|variable|cycx_intr
id|EXPORT_SYMBOL
c_func
(paren
id|cycx_intr
)paren
suffix:semicolon
DECL|function|cycx_intr
r_void
id|cycx_intr
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
(brace
id|writew
c_func
(paren
l_int|0
comma
id|hw-&gt;dpmbase
op_plus
id|GEN_CYCX_INTR
)paren
suffix:semicolon
)brace
multiline_comment|/* Execute Adapter Command.&n; * o Set exec flag.&n; * o Busy-wait until flag is reset. */
DECL|variable|cycx_exec
id|EXPORT_SYMBOL
c_func
(paren
id|cycx_exec
)paren
suffix:semicolon
DECL|function|cycx_exec
r_int
id|cycx_exec
c_func
(paren
id|u32
id|addr
)paren
(brace
id|u16
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* wait till addr content is zeroed */
r_while
c_loop
(paren
id|readw
c_func
(paren
id|addr
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|i
OG
l_int|50
)paren
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Read absolute adapter memory.&n; * Transfer data from adapter&squot;s memory to data buffer. */
DECL|variable|cycx_peek
id|EXPORT_SYMBOL
c_func
(paren
id|cycx_peek
)paren
suffix:semicolon
DECL|function|cycx_peek
r_int
id|cycx_peek
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
id|u32
id|addr
comma
r_void
op_star
id|buf
comma
id|u32
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
l_int|1
)paren
op_star
(paren
id|u8
op_star
)paren
id|buf
op_assign
id|readb
c_func
(paren
id|hw-&gt;dpmbase
op_plus
id|addr
)paren
suffix:semicolon
r_else
id|memcpy_fromio
c_func
(paren
id|buf
comma
id|hw-&gt;dpmbase
op_plus
id|addr
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Write Absolute Adapter Memory.&n; * Transfer data from data buffer to adapter&squot;s memory. */
DECL|variable|cycx_poke
id|EXPORT_SYMBOL
c_func
(paren
id|cycx_poke
)paren
suffix:semicolon
DECL|function|cycx_poke
r_int
id|cycx_poke
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
id|u32
id|addr
comma
r_void
op_star
id|buf
comma
id|u32
id|len
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
l_int|1
)paren
id|writeb
c_func
(paren
op_star
(paren
id|u8
op_star
)paren
id|buf
comma
id|hw-&gt;dpmbase
op_plus
id|addr
)paren
suffix:semicolon
r_else
id|memcpy_toio
c_func
(paren
id|hw-&gt;dpmbase
op_plus
id|addr
comma
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Hardware-Specific Functions */
multiline_comment|/* Load Aux Routines */
multiline_comment|/* Reset board hardware.&n;   return 1 if memory exists at addr and 0 if not. */
DECL|function|memory_exists
r_static
r_int
id|memory_exists
c_func
(paren
id|u32
id|addr
)paren
(brace
r_int
id|tries
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|tries
OL
l_int|3
suffix:semicolon
id|tries
op_increment
)paren
(brace
id|writew
c_func
(paren
id|TEST_PATTERN
comma
id|addr
op_plus
l_int|0x10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|readw
c_func
(paren
id|addr
op_plus
l_int|0x10
)paren
op_eq
id|TEST_PATTERN
)paren
r_if
c_cond
(paren
id|readw
c_func
(paren
id|addr
op_plus
l_int|0x10
)paren
op_eq
id|TEST_PATTERN
)paren
r_return
l_int|1
suffix:semicolon
id|delay_cycx
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Load reset code. */
DECL|function|reset_load
r_static
r_void
id|reset_load
c_func
(paren
id|u32
id|addr
comma
id|u8
op_star
id|buffer
comma
id|u32
id|cnt
)paren
(brace
id|u32
id|pt_code
op_assign
id|addr
op_plus
id|RESET_OFFSET
suffix:semicolon
id|u16
id|i
suffix:semicolon
multiline_comment|/*, j; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cnt
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&t;&t;for (j = 0 ; j &lt; 50 ; j++); Delay - FIXME busy waiting... */
id|writeb
c_func
(paren
op_star
id|buffer
op_increment
comma
id|pt_code
op_increment
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Load buffer using boot interface.&n; * o copy data from buffer to Cyclom-X memory&n; * o wait for reset code to copy it to right portion of memory */
DECL|function|buffer_load
r_static
r_int
id|buffer_load
c_func
(paren
id|u32
id|addr
comma
id|u8
op_star
id|buffer
comma
id|u32
id|cnt
)paren
(brace
id|memcpy_toio
c_func
(paren
id|addr
op_plus
id|DATA_OFFSET
comma
id|buffer
comma
id|cnt
)paren
suffix:semicolon
id|writew
c_func
(paren
id|GEN_BOOT_DAT
comma
id|addr
op_plus
id|CMD_OFFSET
)paren
suffix:semicolon
r_return
id|wait_cyc
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up entry point and kick start Cyclom-X CPU. */
DECL|function|cycx_start
r_static
r_void
id|cycx_start
c_func
(paren
id|u32
id|addr
)paren
(brace
multiline_comment|/* put in 0x30 offset the jump instruction to the code entry point */
id|writeb
c_func
(paren
l_int|0xea
comma
id|addr
op_plus
l_int|0x30
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x00
comma
id|addr
op_plus
l_int|0x31
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xc4
comma
id|addr
op_plus
l_int|0x32
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x00
comma
id|addr
op_plus
l_int|0x33
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x00
comma
id|addr
op_plus
l_int|0x34
)paren
suffix:semicolon
multiline_comment|/* cmd to start executing code */
id|writew
c_func
(paren
id|GEN_START
comma
id|addr
op_plus
id|CMD_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/* Load and boot reset code. */
DECL|function|cycx_reset_boot
r_static
r_void
id|cycx_reset_boot
c_func
(paren
id|u32
id|addr
comma
id|u8
op_star
id|code
comma
id|u32
id|len
)paren
(brace
id|u32
id|pt_start
op_assign
id|addr
op_plus
id|START_OFFSET
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xea
comma
id|pt_start
op_increment
)paren
suffix:semicolon
multiline_comment|/* jmp to f000:3f00 */
id|writeb
c_func
(paren
l_int|0x00
comma
id|pt_start
op_increment
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xfc
comma
id|pt_start
op_increment
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0x00
comma
id|pt_start
op_increment
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xf0
comma
id|pt_start
)paren
suffix:semicolon
id|reset_load
c_func
(paren
id|addr
comma
id|code
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* 80186 was in hold, go */
id|writeb
c_func
(paren
l_int|0
comma
id|addr
op_plus
id|START_CPU
)paren
suffix:semicolon
id|delay_cycx
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Load data.bin file through boot (reset) interface. */
DECL|function|cycx_data_boot
r_static
r_int
id|cycx_data_boot
c_func
(paren
id|u32
id|addr
comma
id|u8
op_star
id|code
comma
id|u32
id|len
)paren
(brace
id|u32
id|pt_boot_cmd
op_assign
id|addr
op_plus
id|CMD_OFFSET
suffix:semicolon
id|u32
id|i
suffix:semicolon
multiline_comment|/* boot buffer lenght */
id|writew
c_func
(paren
id|CFM_LOAD_BUFSZ
comma
id|pt_boot_cmd
op_plus
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|writew
c_func
(paren
id|GEN_DEFPAR
comma
id|pt_boot_cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_cyc
c_func
(paren
id|addr
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|writew
c_func
(paren
l_int|0
comma
id|pt_boot_cmd
op_plus
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0x4000
comma
id|pt_boot_cmd
op_plus
l_int|2
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|writew
c_func
(paren
id|GEN_SET_SEG
comma
id|pt_boot_cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_cyc
c_func
(paren
id|addr
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_add_assign
id|CFM_LOAD_BUFSZ
)paren
r_if
c_cond
(paren
id|buffer_load
c_func
(paren
id|addr
comma
id|code
op_plus
id|i
comma
id|min_t
c_func
(paren
id|u32
comma
id|CFM_LOAD_BUFSZ
comma
(paren
id|len
op_minus
id|i
)paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error !!&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Load code.bin file through boot (reset) interface. */
DECL|function|cycx_code_boot
r_static
r_int
id|cycx_code_boot
c_func
(paren
id|u32
id|addr
comma
id|u8
op_star
id|code
comma
id|u32
id|len
)paren
(brace
id|u32
id|pt_boot_cmd
op_assign
id|addr
op_plus
id|CMD_OFFSET
suffix:semicolon
id|u32
id|i
suffix:semicolon
multiline_comment|/* boot buffer lenght */
id|writew
c_func
(paren
id|CFM_LOAD_BUFSZ
comma
id|pt_boot_cmd
op_plus
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|writew
c_func
(paren
id|GEN_DEFPAR
comma
id|pt_boot_cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_cyc
c_func
(paren
id|addr
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|writew
c_func
(paren
l_int|0x0000
comma
id|pt_boot_cmd
op_plus
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|writew
c_func
(paren
l_int|0xc400
comma
id|pt_boot_cmd
op_plus
l_int|2
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|writew
c_func
(paren
id|GEN_SET_SEG
comma
id|pt_boot_cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_cyc
c_func
(paren
id|addr
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|len
suffix:semicolon
id|i
op_add_assign
id|CFM_LOAD_BUFSZ
)paren
r_if
c_cond
(paren
id|buffer_load
c_func
(paren
id|addr
comma
id|code
op_plus
id|i
comma
id|min_t
c_func
(paren
id|u32
comma
id|CFM_LOAD_BUFSZ
comma
(paren
id|len
op_minus
id|i
)paren
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: Error !!&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Load adapter from the memory image of the CYCX firmware module.&n; * o verify firmware integrity and compatibility&n; * o start adapter up */
DECL|function|load_cyc2x
r_static
r_int
id|load_cyc2x
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
comma
r_struct
id|cycx_firmware
op_star
id|cfm
comma
id|u32
id|len
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_struct
id|cycx_fw_header
op_star
id|img_hdr
suffix:semicolon
id|u8
op_star
id|reset_image
comma
op_star
id|data_image
comma
op_star
id|code_image
suffix:semicolon
id|u32
id|pt_cycld
op_assign
id|hw-&gt;dpmbase
op_plus
l_int|0x400
suffix:semicolon
id|u16
id|cksum
suffix:semicolon
multiline_comment|/* Announce */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: firmware signature=&bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|modname
comma
id|cfm-&gt;signature
)paren
suffix:semicolon
multiline_comment|/* Verify firmware signature */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cfm-&gt;signature
comma
id|CFM_SIGNATURE
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s:load_cyc2x: not Cyclom-2X firmware!&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: firmware version=%u&bslash;n&quot;
comma
id|modname
comma
id|cfm-&gt;version
)paren
suffix:semicolon
multiline_comment|/* Verify firmware module format version */
r_if
c_cond
(paren
id|cfm-&gt;version
op_ne
id|CFM_VERSION
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s:%s: firmware format %u rejected! &quot;
l_string|&quot;Expecting %u.&bslash;n&quot;
comma
id|modname
comma
id|__FUNCTION__
comma
id|cfm-&gt;version
comma
id|CFM_VERSION
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Verify firmware module length and checksum */
id|cksum
op_assign
id|checksum
c_func
(paren
(paren
id|u8
op_star
)paren
op_amp
id|cfm-&gt;info
comma
r_sizeof
(paren
r_struct
id|cycx_fw_info
)paren
op_plus
id|cfm-&gt;info.codesize
)paren
suffix:semicolon
multiline_comment|/*&n;&t;FIXME cfm-&gt;info.codesize is off by 2&n;&t;if (((len - sizeof(struct cycx_firmware) - 1) != cfm-&gt;info.codesize) ||&n;*/
r_if
c_cond
(paren
id|cksum
op_ne
id|cfm-&gt;checksum
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s:%s: firmware corrupted!&bslash;n&quot;
comma
id|modname
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot; cdsize = 0x%x (expected 0x%lx)&bslash;n&quot;
comma
id|len
op_minus
r_sizeof
(paren
r_struct
id|cycx_firmware
)paren
op_minus
l_int|1
comma
id|cfm-&gt;info.codesize
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot; chksum = 0x%x (expected 0x%x)&bslash;n&quot;
comma
id|cksum
comma
id|cfm-&gt;checksum
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* If everything is ok, set reset, data and code pointers */
id|img_hdr
op_assign
(paren
r_struct
id|cycx_fw_header
op_star
)paren
(paren
(paren
(paren
id|u8
op_star
)paren
id|cfm
)paren
op_plus
r_sizeof
(paren
r_struct
id|cycx_firmware
)paren
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef FIRMWARE_DEBUG
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s:%s: image sizes&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|modname
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; reset=%lu&bslash;n&quot;
comma
id|img_hdr-&gt;reset_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  data=%lu&bslash;n&quot;
comma
id|img_hdr-&gt;data_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  code=%lu&bslash;n&quot;
comma
id|img_hdr-&gt;code_size
)paren
suffix:semicolon
macro_line|#endif
id|reset_image
op_assign
(paren
(paren
id|u8
op_star
)paren
id|img_hdr
)paren
op_plus
r_sizeof
(paren
r_struct
id|cycx_fw_header
)paren
suffix:semicolon
id|data_image
op_assign
id|reset_image
op_plus
id|img_hdr-&gt;reset_size
suffix:semicolon
id|code_image
op_assign
id|data_image
op_plus
id|img_hdr-&gt;data_size
suffix:semicolon
multiline_comment|/*---- Start load ----*/
multiline_comment|/* Announce */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: loading firmware %s (ID=%u)...&bslash;n&quot;
comma
id|modname
comma
id|cfm-&gt;descr
(braket
l_int|0
)braket
ques
c_cond
id|cfm-&gt;descr
suffix:colon
l_string|&quot;unknown firmware&quot;
comma
id|cfm-&gt;info.codeid
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Reset Cyclom hardware */
r_if
c_cond
(paren
op_logical_neg
id|reset_cyc2x
c_func
(paren
id|hw-&gt;dpmbase
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: dpm problem or board not found&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Load reset.bin */
id|cycx_reset_boot
c_func
(paren
id|hw-&gt;dpmbase
comma
id|reset_image
comma
id|img_hdr-&gt;reset_size
)paren
suffix:semicolon
multiline_comment|/* reset is waiting for boot */
id|writew
c_func
(paren
id|GEN_POWER_ON
comma
id|pt_cycld
)paren
suffix:semicolon
id|delay_cycx
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|3
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|readw
c_func
(paren
id|pt_cycld
)paren
)paren
r_goto
id|reset_loaded
suffix:semicolon
r_else
id|delay_cycx
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: reset not started.&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
id|reset_loaded
suffix:colon
multiline_comment|/* Load data.bin */
r_if
c_cond
(paren
id|cycx_data_boot
c_func
(paren
id|hw-&gt;dpmbase
comma
id|data_image
comma
id|img_hdr-&gt;data_size
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: cannot load data file.&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Load code.bin */
r_if
c_cond
(paren
id|cycx_code_boot
c_func
(paren
id|hw-&gt;dpmbase
comma
id|code_image
comma
id|img_hdr-&gt;code_size
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: cannot load code file.&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Prepare boot-time configuration data */
id|cycx_bootcfg
c_func
(paren
id|hw
)paren
suffix:semicolon
multiline_comment|/* kick-off CPU */
id|cycx_start
c_func
(paren
id|hw-&gt;dpmbase
)paren
suffix:semicolon
multiline_comment|/* Arthur Ganzert&squot;s tip: wait a while after the firmware loading...&n;&t;   seg abr 26 17:17:12 EST 1999 - acme */
id|delay_cycx
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: firmware loaded!&bslash;n&quot;
comma
id|modname
)paren
suffix:semicolon
multiline_comment|/* enable interrupts */
id|cycx_inten
c_func
(paren
id|hw
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Prepare boot-time firmware configuration data.&n; * o initialize configuration data area&n;   From async.doc - V_3.4.0 - 07/18/1994&n;   - As of now, only static buffers are available to the user.&n;     So, the bit VD_RXDIRC must be set in &squot;valid&squot;. That means that user&n;     wants to use the static transmission and reception buffers. */
DECL|function|cycx_bootcfg
r_static
r_void
id|cycx_bootcfg
c_func
(paren
r_struct
id|cycx_hw
op_star
id|hw
)paren
(brace
multiline_comment|/* use fixed buffers */
id|writeb
c_func
(paren
id|FIXED_BUFFERS
comma
id|hw-&gt;dpmbase
op_plus
id|CONF_OFFSET
)paren
suffix:semicolon
)brace
multiline_comment|/* Detect Cyclom 2x adapter.&n; *&t;Following tests are used to detect Cyclom 2x adapter:&n; *       to be completed based on the tests done below&n; *&t;Return 1 if detected o.k. or 0 if failed.&n; *&t;Note:&t;This test is destructive! Adapter will be left in shutdown&n; *&t;&t;state after the test. */
DECL|function|detect_cyc2x
r_static
r_int
id|detect_cyc2x
c_func
(paren
id|u32
id|addr
)paren
(brace
id|reset_cyc2x
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|memory_exists
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Miscellaneous */
multiline_comment|/* Get option&squot;s index into the options list.&n; *&t;Return option&squot;s index (1 .. N) or zero if option is invalid. */
DECL|function|get_option_index
r_static
r_int
id|get_option_index
c_func
(paren
id|u32
op_star
id|optlist
comma
id|u32
id|optval
)paren
(brace
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
op_le
id|optlist
(braket
l_int|0
)braket
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|optlist
(braket
id|i
)braket
op_eq
id|optval
)paren
r_return
id|i
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Reset adapter&squot;s CPU. */
DECL|function|reset_cyc2x
r_static
r_int
id|reset_cyc2x
c_func
(paren
id|u32
id|addr
)paren
(brace
id|writeb
c_func
(paren
l_int|0
comma
id|addr
op_plus
id|RST_ENABLE
)paren
suffix:semicolon
id|delay_cycx
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|writeb
c_func
(paren
l_int|0
comma
id|addr
op_plus
id|RST_DISABLE
)paren
suffix:semicolon
id|delay_cycx
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_return
id|memory_exists
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/* Delay */
DECL|function|delay_cycx
r_static
r_void
id|delay_cycx
c_func
(paren
r_int
id|sec
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|sec
op_star
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/* Calculate 16-bit CRC using CCITT polynomial. */
DECL|function|checksum
r_static
id|u16
id|checksum
c_func
(paren
id|u8
op_star
id|buf
comma
id|u32
id|len
)paren
(brace
id|u16
id|crc
op_assign
l_int|0
suffix:semicolon
id|u16
id|mask
comma
id|flag
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
suffix:semicolon
op_decrement
id|len
comma
op_increment
id|buf
)paren
r_for
c_loop
(paren
id|mask
op_assign
l_int|0x80
suffix:semicolon
id|mask
suffix:semicolon
id|mask
op_rshift_assign
l_int|1
)paren
(brace
id|flag
op_assign
(paren
id|crc
op_amp
l_int|0x8000
)paren
suffix:semicolon
id|crc
op_lshift_assign
l_int|1
suffix:semicolon
id|crc
op_or_assign
(paren
(paren
op_star
id|buf
op_amp
id|mask
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
id|crc
op_xor_assign
l_int|0x1021
suffix:semicolon
)brace
r_return
id|crc
suffix:semicolon
)brace
DECL|variable|cycx_drv_init
id|module_init
c_func
(paren
id|cycx_drv_init
)paren
suffix:semicolon
DECL|variable|cycx_drv_cleanup
id|module_exit
c_func
(paren
id|cycx_drv_cleanup
)paren
suffix:semicolon
multiline_comment|/* End */
eof
