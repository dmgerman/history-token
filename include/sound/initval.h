macro_line|#ifndef __SOUND_INITVAL_H
DECL|macro|__SOUND_INITVAL_H
mdefine_line|#define __SOUND_INITVAL_H
multiline_comment|/*&n; *  Init values for soundcard modules&n; *  Copyright (c) by Jaroslav Kysela &lt;perex@suse.cz&gt;&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; *&n; */
macro_line|#ifndef MODULE_GENERIC_STRING
macro_line|#ifdef MODULE
DECL|macro|MODULE_GENERIC_STRING
mdefine_line|#define MODULE_GENERIC_STRING(name, string) &bslash;&n;static const char __module_generic_string_##name [] &bslash;&n;  __attribute__ ((section(&quot;.modstring&quot;))) = #name &quot;=&quot; string;
macro_line|#else
DECL|macro|MODULE_GENERIC_STRING
mdefine_line|#define MODULE_GENERIC_STRING(name, string)
macro_line|#endif
macro_line|#endif
DECL|macro|MODULE_CLASSES
mdefine_line|#define MODULE_CLASSES(val) MODULE_GENERIC_STRING(info_classes, val)
DECL|macro|MODULE_DEVICES
mdefine_line|#define MODULE_DEVICES(val) MODULE_GENERIC_STRING(info_devices, val)
DECL|macro|MODULE_PARM_SYNTAX
mdefine_line|#define MODULE_PARM_SYNTAX(id, val) MODULE_GENERIC_STRING(info_parm_##id, val)
DECL|macro|SNDRV_AUTO_PORT
mdefine_line|#define SNDRV_AUTO_PORT&t;&t;0xffff
DECL|macro|SNDRV_AUTO_IRQ
mdefine_line|#define SNDRV_AUTO_IRQ&t;&t;0xffff
DECL|macro|SNDRV_AUTO_DMA
mdefine_line|#define SNDRV_AUTO_DMA&t;&t;0xffff
DECL|macro|SNDRV_AUTO_DMA_SIZE
mdefine_line|#define SNDRV_AUTO_DMA_SIZE&t;(0x7fffffff)
DECL|macro|SNDRV_DEFAULT_IDX1
mdefine_line|#define SNDRV_DEFAULT_IDX1&t;(-1)
DECL|macro|SNDRV_DEFAULT_STR1
mdefine_line|#define SNDRV_DEFAULT_STR1&t;NULL
DECL|macro|SNDRV_DEFAULT_ENABLE1
mdefine_line|#define SNDRV_DEFAULT_ENABLE1&t;1
DECL|macro|SNDRV_DEFAULT_PORT1
mdefine_line|#define SNDRV_DEFAULT_PORT1&t;SNDRV_AUTO_PORT
DECL|macro|SNDRV_DEFAULT_IRQ1
mdefine_line|#define SNDRV_DEFAULT_IRQ1&t;SNDRV_AUTO_IRQ
DECL|macro|SNDRV_DEFAULT_DMA1
mdefine_line|#define SNDRV_DEFAULT_DMA1&t;SNDRV_AUTO_DMA
DECL|macro|SNDRV_DEFAULT_DMA_SIZE1
mdefine_line|#define SNDRV_DEFAULT_DMA_SIZE1&t;SNDRV_AUTO_DMA_SIZE
DECL|macro|SNDRV_DEFAULT_PTR1
mdefine_line|#define SNDRV_DEFAULT_PTR1&t;SNDRV_DEFAULT_STR1
DECL|macro|SNDRV_DEFAULT_IDX
mdefine_line|#define SNDRV_DEFAULT_IDX&t;{ [0 ... (SNDRV_CARDS-1)] = -1 }
DECL|macro|SNDRV_DEFAULT_STR
mdefine_line|#define SNDRV_DEFAULT_STR&t;{ [0 ... (SNDRV_CARDS-1)] = NULL }
DECL|macro|SNDRV_DEFAULT_ENABLE
mdefine_line|#define SNDRV_DEFAULT_ENABLE&t;{ 1, [1 ... (SNDRV_CARDS-1)] = 0 }
DECL|macro|SNDRV_DEFAULT_ENABLE_PNP
mdefine_line|#define SNDRV_DEFAULT_ENABLE_PNP { [0 ... (SNDRV_CARDS-1)] = 1 }
macro_line|#ifdef __ISAPNP__
DECL|macro|SNDRV_DEFAULT_ENABLE_ISAPNP
mdefine_line|#define SNDRV_DEFAULT_ENABLE_ISAPNP SNDRV_DEFAULT_ENABLE_PNP
macro_line|#else
DECL|macro|SNDRV_DEFAULT_ENABLE_ISAPNP
mdefine_line|#define SNDRV_DEFAULT_ENABLE_ISAPNP SNDRV_DEFAULT_ENABLE
macro_line|#endif
DECL|macro|SNDRV_DEFAULT_PORT
mdefine_line|#define SNDRV_DEFAULT_PORT&t;{ SNDRV_AUTO_PORT, [1 ... (SNDRV_CARDS-1)] = -1 }
DECL|macro|SNDRV_DEFAULT_IRQ
mdefine_line|#define SNDRV_DEFAULT_IRQ&t;{ [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_IRQ }
DECL|macro|SNDRV_DEFAULT_DMA
mdefine_line|#define SNDRV_DEFAULT_DMA&t;{ [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_DMA }
DECL|macro|SNDRV_DEFAULT_DMA_SIZE
mdefine_line|#define SNDRV_DEFAULT_DMA_SIZE&t;{ [0 ... (SNDRV_CARDS-1)] = SNDRV_AUTO_DMA_SIZE }
DECL|macro|SNDRV_DEFAULT_PTR
mdefine_line|#define SNDRV_DEFAULT_PTR&t;SNDRV_DEFAULT_STR
DECL|macro|SNDRV_BOOLEAN_TRUE_DESC
mdefine_line|#define SNDRV_BOOLEAN_TRUE_DESC&t;&quot;allows:{{0,Disabled},{1,Enabled}},default:1,dialog:check&quot;
DECL|macro|SNDRV_BOOLEAN_FALSE_DESC
mdefine_line|#define SNDRV_BOOLEAN_FALSE_DESC &quot;allows:{{0,Disabled},{1,Enabled}},default:0,dialog:check&quot;
DECL|macro|SNDRV_ENABLED
mdefine_line|#define SNDRV_ENABLED&t;&t;&quot;enable:(snd_enable)&quot;
DECL|macro|SNDRV_INDEX_DESC
mdefine_line|#define SNDRV_INDEX_DESC&t;SNDRV_ENABLED &quot;,allows:{{0,7}},unique,skill:required,dialog:list&quot;
DECL|macro|SNDRV_ID_DESC
mdefine_line|#define SNDRV_ID_DESC&t;&t;SNDRV_ENABLED &quot;,unique&quot;
DECL|macro|SNDRV_ENABLE_DESC
mdefine_line|#define SNDRV_ENABLE_DESC&t;SNDRV_BOOLEAN_FALSE_DESC
DECL|macro|SNDRV_ISAPNP_DESC
mdefine_line|#define SNDRV_ISAPNP_DESC&t;SNDRV_ENABLED &quot;,&quot; SNDRV_BOOLEAN_TRUE_DESC
DECL|macro|SNDRV_DMA8_DESC
mdefine_line|#define SNDRV_DMA8_DESC&t;&t;SNDRV_ENABLED &quot;,allows:{{0,1},{3}},dialog:list&quot;
DECL|macro|SNDRV_DMA16_DESC
mdefine_line|#define SNDRV_DMA16_DESC&t;SNDRV_ENABLED &quot;,allows:{{5,7}},dialog:list&quot;
DECL|macro|SNDRV_DMA_DESC
mdefine_line|#define SNDRV_DMA_DESC&t;&t;SNDRV_ENABLED &quot;,allows:{{0,1},{3},{5,7}},dialog:list&quot;
DECL|macro|SNDRV_IRQ_DESC
mdefine_line|#define SNDRV_IRQ_DESC&t;&t;SNDRV_ENABLED &quot;,allows:{{5},{7},{9},{10,12},{14,15}},dialog:list&quot;
DECL|macro|SNDRV_DMA_SIZE_DESC
mdefine_line|#define SNDRV_DMA_SIZE_DESC&t;SNDRV_ENABLED &quot;,allows:{{4,128}},default:64,skill:advanced&quot;
DECL|macro|SNDRV_DMA8_SIZE_DESC
mdefine_line|#define SNDRV_DMA8_SIZE_DESC&t;SNDRV_ENABLED &quot;,allows:{{4, 64}},default:64,skill:advanced&quot;
DECL|macro|SNDRV_DMA16_SIZE_DESC
mdefine_line|#define SNDRV_DMA16_SIZE_DESC&t;SNDRV_ENABLED &quot;,allows:{{4,128}},default:64,skill:advanced&quot;
DECL|macro|SNDRV_PORT12_DESC
mdefine_line|#define SNDRV_PORT12_DESC&t;SNDRV_ENABLED &quot;,allows:{{0,0x3fff}},base:16&quot;
DECL|macro|SNDRV_PORT_DESC
mdefine_line|#define SNDRV_PORT_DESC&t;&t;SNDRV_ENABLED &quot;,allows:{{0,0xffff}},base:16&quot;
macro_line|#ifdef SNDRV_LEGACY_AUTO_PROBE
DECL|function|snd_legacy_auto_probe
r_static
r_int
id|snd_legacy_auto_probe
c_func
(paren
r_int
r_int
op_star
id|ports
comma
r_int
(paren
op_star
id|probe
)paren
(paren
r_int
r_int
id|port
)paren
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* number of detected cards */
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
op_star
id|ports
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|probe
c_func
(paren
op_star
id|ports
)paren
op_ge
l_int|0
)paren
id|result
op_increment
suffix:semicolon
id|ports
op_increment
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SNDRV_LEGACY_FIND_FREE_IOPORT
DECL|function|snd_legacy_find_free_ioport
r_static
r_int
id|snd_legacy_find_free_ioport
c_func
(paren
r_int
op_star
id|port_table
comma
r_int
id|size
)paren
(brace
r_while
c_loop
(paren
op_star
id|port_table
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|check_region
c_func
(paren
op_star
id|port_table
comma
id|size
)paren
)paren
r_return
op_star
id|port_table
suffix:semicolon
id|port_table
op_increment
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SNDRV_LEGACY_FIND_FREE_IRQ
DECL|function|snd_legacy_empty_irq_handler
r_static
r_void
id|snd_legacy_empty_irq_handler
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
id|regs
)paren
(brace
)brace
DECL|function|snd_legacy_find_free_irq
r_static
r_int
id|snd_legacy_find_free_irq
c_func
(paren
r_int
op_star
id|irq_table
)paren
(brace
r_while
c_loop
(paren
op_star
id|irq_table
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_irq
c_func
(paren
op_star
id|irq_table
comma
id|snd_legacy_empty_irq_handler
comma
id|SA_INTERRUPT
comma
l_string|&quot;ALSA Test IRQ&quot;
comma
(paren
r_void
op_star
)paren
id|irq_table
)paren
)paren
(brace
id|free_irq
c_func
(paren
op_star
id|irq_table
comma
(paren
r_void
op_star
)paren
id|irq_table
)paren
suffix:semicolon
r_return
op_star
id|irq_table
suffix:semicolon
)brace
id|irq_table
op_increment
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef SNDRV_LEGACY_FIND_FREE_DMA
DECL|function|snd_legacy_find_free_dma
r_static
r_int
id|snd_legacy_find_free_dma
c_func
(paren
r_int
op_star
id|dma_table
)paren
(brace
r_while
c_loop
(paren
op_star
id|dma_table
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_dma
c_func
(paren
op_star
id|dma_table
comma
l_string|&quot;ALSA Test DMA&quot;
)paren
)paren
(brace
id|free_dma
c_func
(paren
op_star
id|dma_table
)paren
suffix:semicolon
r_return
op_star
id|dma_table
suffix:semicolon
)brace
id|dma_table
op_increment
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(SNDRV_GET_ID) &amp;&amp; !defined(MODULE)
macro_line|#include &lt;linux/ctype.h&gt;
DECL|function|get_id
r_static
r_int
id|__init
id|get_id
c_func
(paren
r_char
op_star
op_star
id|str
comma
r_char
op_star
op_star
id|dst
)paren
(brace
r_char
op_star
id|s
comma
op_star
id|d
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|str
)paren
op_logical_or
op_logical_neg
(paren
op_star
op_star
id|str
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
op_star
id|str
suffix:semicolon
id|isalpha
c_func
(paren
op_star
id|s
)paren
op_logical_or
id|isdigit
c_func
(paren
op_star
id|s
)paren
op_logical_or
op_star
id|s
op_eq
l_char|&squot;_&squot;
suffix:semicolon
id|s
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
op_star
id|str
)paren
(brace
op_star
id|dst
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|s
op_minus
op_star
id|str
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d
op_assign
op_star
id|dst
)paren
op_ne
l_int|NULL
)paren
(brace
id|s
op_assign
op_star
id|str
suffix:semicolon
r_while
c_loop
(paren
id|isalpha
c_func
(paren
op_star
id|s
)paren
op_logical_or
id|isdigit
c_func
(paren
op_star
id|s
)paren
op_logical_or
op_star
id|s
op_eq
l_char|&squot;_&squot;
)paren
op_star
id|d
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
)brace
)brace
op_star
id|str
op_assign
id|s
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;,&squot;
)paren
(brace
(paren
op_star
id|str
)paren
op_increment
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* __SOUND_INITVAL_H */
eof
