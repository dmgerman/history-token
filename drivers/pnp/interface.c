multiline_comment|/*&n; * interface.c - contains everything related to the user interface&n; *&n; * Some code, especially possible resource dumping is based on isapnp_proc.c (c) Jaroslav Kysela &lt;perex@suse.cz&gt;&n; * Copyright 2002 Adam Belay &lt;ambx1@neo.rr.com&gt;&n; *&n; */
macro_line|#include &lt;linux/pnp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;base.h&quot;
DECL|struct|pnp_info_buffer
r_struct
id|pnp_info_buffer
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
multiline_comment|/* pointer to begin of buffer */
DECL|member|curr
r_char
op_star
id|curr
suffix:semicolon
multiline_comment|/* current position in buffer */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* current size */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* total length of buffer */
DECL|member|stop
r_int
id|stop
suffix:semicolon
multiline_comment|/* stop flag */
DECL|member|error
r_int
id|error
suffix:semicolon
multiline_comment|/* error code */
)brace
suffix:semicolon
DECL|typedef|pnp_info_buffer_t
r_typedef
r_struct
id|pnp_info_buffer
id|pnp_info_buffer_t
suffix:semicolon
DECL|function|pnp_printf
r_int
id|pnp_printf
c_func
(paren
id|pnp_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|res
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;stop
op_logical_or
id|buffer-&gt;error
)paren
r_return
l_int|0
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|res
op_assign
id|vsnprintf
c_func
(paren
id|buffer-&gt;curr
comma
id|buffer-&gt;len
op_minus
id|buffer-&gt;size
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buffer-&gt;size
op_plus
id|res
op_ge
id|buffer-&gt;len
)paren
(brace
id|buffer-&gt;stop
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|buffer-&gt;curr
op_add_assign
id|res
suffix:semicolon
id|buffer-&gt;size
op_add_assign
id|res
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|pnp_print_port
r_static
r_void
id|pnp_print_port
c_func
(paren
id|pnp_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|space
comma
r_struct
id|pnp_port
op_star
id|port
)paren
(brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;%sport 0x%x-0x%x, align 0x%x, size 0x%x, %i-bit address decoding&bslash;n&quot;
comma
id|space
comma
id|port-&gt;min
comma
id|port-&gt;max
comma
id|port-&gt;align
ques
c_cond
(paren
id|port-&gt;align
op_minus
l_int|1
)paren
suffix:colon
l_int|0
comma
id|port-&gt;size
comma
id|port-&gt;flags
op_amp
id|PNP_PORT_FLAG_16BITADDR
ques
c_cond
l_int|16
suffix:colon
l_int|10
)paren
suffix:semicolon
)brace
DECL|function|pnp_print_irq
r_static
r_void
id|pnp_print_irq
c_func
(paren
id|pnp_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|space
comma
r_struct
id|pnp_irq
op_star
id|irq
)paren
(brace
r_int
id|first
op_assign
l_int|1
comma
id|i
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;%sirq &quot;
comma
id|space
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|irq-&gt;map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
(brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|first
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|2
op_logical_or
id|i
op_eq
l_int|9
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;2/9&quot;
)paren
suffix:semicolon
r_else
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;%i&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|irq-&gt;map
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;&lt;none&gt;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq-&gt;flags
op_amp
id|IORESOURCE_IRQ_HIGHEDGE
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; High-Edge&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq-&gt;flags
op_amp
id|IORESOURCE_IRQ_LOWEDGE
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; Low-Edge&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq-&gt;flags
op_amp
id|IORESOURCE_IRQ_HIGHLEVEL
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; High-Level&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq-&gt;flags
op_amp
id|IORESOURCE_IRQ_LOWLEVEL
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; Low-Level&quot;
)paren
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|pnp_print_dma
r_static
r_void
id|pnp_print_dma
c_func
(paren
id|pnp_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|space
comma
r_struct
id|pnp_dma
op_star
id|dma
)paren
(brace
r_int
id|first
op_assign
l_int|1
comma
id|i
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;%sdma &quot;
comma
id|space
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dma-&gt;map
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
(brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|first
op_assign
l_int|0
suffix:semicolon
)brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;%i&quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;map
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;&lt;none&gt;&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dma-&gt;flags
op_amp
id|IORESOURCE_DMA_TYPE_MASK
)paren
(brace
r_case
id|IORESOURCE_DMA_8BIT
suffix:colon
id|s
op_assign
l_string|&quot;8-bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IORESOURCE_DMA_8AND16BIT
suffix:colon
id|s
op_assign
l_string|&quot;8-bit&amp;16-bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|s
op_assign
l_string|&quot;16-bit&quot;
suffix:semicolon
)brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; %s&quot;
comma
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;flags
op_amp
id|IORESOURCE_DMA_MASTER
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; master&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;flags
op_amp
id|IORESOURCE_DMA_BYTE
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; byte-count&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;flags
op_amp
id|IORESOURCE_DMA_WORD
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; word-count&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dma-&gt;flags
op_amp
id|IORESOURCE_DMA_SPEED_MASK
)paren
(brace
r_case
id|IORESOURCE_DMA_TYPEA
suffix:colon
id|s
op_assign
l_string|&quot;type-A&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IORESOURCE_DMA_TYPEB
suffix:colon
id|s
op_assign
l_string|&quot;type-B&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IORESOURCE_DMA_TYPEF
suffix:colon
id|s
op_assign
l_string|&quot;type-F&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|s
op_assign
l_string|&quot;compatible&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; %s&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
)brace
DECL|function|pnp_print_mem
r_static
r_void
id|pnp_print_mem
c_func
(paren
id|pnp_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|space
comma
r_struct
id|pnp_mem
op_star
id|mem
)paren
(brace
r_char
op_star
id|s
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;%sMemory 0x%x-0x%x, align 0x%x, size 0x%x&quot;
comma
id|space
comma
id|mem-&gt;min
comma
id|mem-&gt;max
comma
id|mem-&gt;align
comma
id|mem-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|IORESOURCE_MEM_WRITEABLE
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;, writeable&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|IORESOURCE_MEM_CACHEABLE
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;, cacheable&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|IORESOURCE_MEM_RANGELENGTH
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;, range-length&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|IORESOURCE_MEM_SHADOWABLE
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;, shadowable&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|IORESOURCE_MEM_EXPANSIONROM
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;, expansion ROM&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|mem-&gt;flags
op_amp
id|IORESOURCE_MEM_TYPE_MASK
)paren
(brace
r_case
id|IORESOURCE_MEM_8BIT
suffix:colon
id|s
op_assign
l_string|&quot;8-bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IORESOURCE_MEM_8AND16BIT
suffix:colon
id|s
op_assign
l_string|&quot;8-bit&amp;16-bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IORESOURCE_MEM_32BIT
suffix:colon
id|s
op_assign
l_string|&quot;32-bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|s
op_assign
l_string|&quot;16-bit&quot;
suffix:semicolon
)brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;, %s&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
)brace
DECL|function|pnp_print_option
r_static
r_void
id|pnp_print_option
c_func
(paren
id|pnp_info_buffer_t
op_star
id|buffer
comma
r_char
op_star
id|space
comma
r_struct
id|pnp_option
op_star
id|option
comma
r_int
id|dep
)paren
(brace
r_char
op_star
id|s
suffix:semicolon
r_struct
id|pnp_port
op_star
id|port
suffix:semicolon
r_struct
id|pnp_irq
op_star
id|irq
suffix:semicolon
r_struct
id|pnp_dma
op_star
id|dma
suffix:semicolon
r_struct
id|pnp_mem
op_star
id|mem
suffix:semicolon
r_if
c_cond
(paren
id|dep
)paren
(brace
r_switch
c_cond
(paren
id|option-&gt;priority
)paren
(brace
r_case
id|PNP_RES_PRIORITY_PREFERRED
suffix:colon
id|s
op_assign
l_string|&quot;preferred&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_RES_PRIORITY_ACCEPTABLE
suffix:colon
id|s
op_assign
l_string|&quot;acceptable&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PNP_RES_PRIORITY_FUNCTIONAL
suffix:colon
id|s
op_assign
l_string|&quot;functional&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|s
op_assign
l_string|&quot;invalid&quot;
suffix:semicolon
)brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;Dependent: %02i - Priority %s&bslash;n&quot;
comma
id|dep
comma
id|s
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|port
op_assign
id|option-&gt;port
suffix:semicolon
id|port
suffix:semicolon
id|port
op_assign
id|port-&gt;next
)paren
id|pnp_print_port
c_func
(paren
id|buffer
comma
id|space
comma
id|port
)paren
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|option-&gt;irq
suffix:semicolon
id|irq
suffix:semicolon
id|irq
op_assign
id|irq-&gt;next
)paren
id|pnp_print_irq
c_func
(paren
id|buffer
comma
id|space
comma
id|irq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dma
op_assign
id|option-&gt;dma
suffix:semicolon
id|dma
suffix:semicolon
id|dma
op_assign
id|dma-&gt;next
)paren
id|pnp_print_dma
c_func
(paren
id|buffer
comma
id|space
comma
id|dma
)paren
suffix:semicolon
r_for
c_loop
(paren
id|mem
op_assign
id|option-&gt;mem
suffix:semicolon
id|mem
suffix:semicolon
id|mem
op_assign
id|mem-&gt;next
)paren
id|pnp_print_mem
c_func
(paren
id|buffer
comma
id|space
comma
id|mem
)paren
suffix:semicolon
)brace
DECL|function|pnp_show_options
r_static
id|ssize_t
id|pnp_show_options
c_func
(paren
r_struct
id|device
op_star
id|dmdev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dmdev
)paren
suffix:semicolon
r_struct
id|pnp_option
op_star
id|independent
op_assign
id|dev-&gt;independent
suffix:semicolon
r_struct
id|pnp_option
op_star
id|dependent
op_assign
id|dev-&gt;dependent
suffix:semicolon
r_int
id|ret
comma
id|dep
op_assign
l_int|1
suffix:semicolon
id|pnp_info_buffer_t
op_star
id|buffer
op_assign
(paren
id|pnp_info_buffer_t
op_star
)paren
id|pnp_alloc
c_func
(paren
r_sizeof
(paren
id|pnp_info_buffer_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|buffer-&gt;len
op_assign
id|PAGE_SIZE
suffix:semicolon
id|buffer-&gt;buffer
op_assign
id|buf
suffix:semicolon
id|buffer-&gt;curr
op_assign
id|buffer-&gt;buffer
suffix:semicolon
r_if
c_cond
(paren
id|independent
)paren
id|pnp_print_option
c_func
(paren
id|buffer
comma
l_string|&quot;&quot;
comma
id|independent
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dependent
)paren
(brace
id|pnp_print_option
c_func
(paren
id|buffer
comma
l_string|&quot;   &quot;
comma
id|dependent
comma
id|dep
)paren
suffix:semicolon
id|dependent
op_assign
id|dependent-&gt;next
suffix:semicolon
id|dep
op_increment
suffix:semicolon
)brace
id|ret
op_assign
(paren
id|buffer-&gt;curr
op_minus
id|buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|options
comma
id|S_IRUGO
comma
id|pnp_show_options
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|pnp_show_current_resources
r_static
id|ssize_t
id|pnp_show_current_resources
c_func
(paren
r_struct
id|device
op_star
id|dmdev
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dmdev
)paren
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
id|pnp_info_buffer_t
op_star
id|buffer
op_assign
(paren
id|pnp_info_buffer_t
op_star
)paren
id|pnp_alloc
c_func
(paren
r_sizeof
(paren
id|pnp_info_buffer_t
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|buffer-&gt;len
op_assign
id|PAGE_SIZE
suffix:semicolon
id|buffer-&gt;buffer
op_assign
id|buf
suffix:semicolon
id|buffer-&gt;curr
op_assign
id|buffer-&gt;buffer
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;state = &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;active
)paren
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;active&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;disabled&bslash;n&quot;
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
id|PNP_MAX_PORT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pnp_port_valid
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;io&quot;
)paren
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; 0x%lx-0x%lx &bslash;n&quot;
comma
id|pnp_port_start
c_func
(paren
id|dev
comma
id|i
)paren
comma
id|pnp_port_end
c_func
(paren
id|dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_MEM
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pnp_mem_valid
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;mem&quot;
)paren
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; 0x%lx-0x%lx &bslash;n&quot;
comma
id|pnp_mem_start
c_func
(paren
id|dev
comma
id|i
)paren
comma
id|pnp_mem_end
c_func
(paren
id|dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_IRQ
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pnp_irq_valid
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;irq&quot;
)paren
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; %ld &bslash;n&quot;
comma
id|pnp_irq
c_func
(paren
id|dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PNP_MAX_DMA
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pnp_dma_valid
c_func
(paren
id|dev
comma
id|i
)paren
)paren
(brace
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot;dma&quot;
)paren
suffix:semicolon
id|pnp_printf
c_func
(paren
id|buffer
comma
l_string|&quot; %ld &bslash;n&quot;
comma
id|pnp_dma
c_func
(paren
id|dev
comma
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
id|ret
op_assign
(paren
id|buffer-&gt;curr
op_minus
id|buf
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_extern
r_struct
id|semaphore
id|pnp_res_mutex
suffix:semicolon
r_static
id|ssize_t
DECL|function|pnp_set_current_resources
id|pnp_set_current_resources
c_func
(paren
r_struct
id|device
op_star
id|dmdev
comma
r_const
r_char
op_star
id|ubuf
comma
r_int
id|count
)paren
(brace
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dmdev
)paren
suffix:semicolon
r_char
op_star
id|buf
op_assign
(paren
r_void
op_star
)paren
id|ubuf
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;status
op_amp
id|PNP_ATTACHED
)paren
(brace
id|retval
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|pnp_info
c_func
(paren
l_string|&quot;Device %s cannot be configured because it is in use.&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;disable&quot;
comma
l_int|7
)paren
)paren
(brace
id|retval
op_assign
id|pnp_disable_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;activate&quot;
comma
l_int|8
)paren
)paren
(brace
id|retval
op_assign
id|pnp_activate_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;fill&quot;
comma
l_int|4
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;active
)paren
r_goto
id|done
suffix:semicolon
id|retval
op_assign
id|pnp_auto_config_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;auto&quot;
comma
l_int|4
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;active
)paren
r_goto
id|done
suffix:semicolon
id|pnp_init_resources
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
id|retval
op_assign
id|pnp_auto_config_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;clear&quot;
comma
l_int|5
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;active
)paren
r_goto
id|done
suffix:semicolon
id|pnp_init_resources
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;get&quot;
comma
l_int|3
)paren
)paren
(brace
id|down
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pnp_can_read
c_func
(paren
id|dev
)paren
)paren
id|dev-&gt;protocol
op_member_access_from_pointer
id|get
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;set&quot;
comma
l_int|3
)paren
)paren
(brace
r_int
id|nport
op_assign
l_int|0
comma
id|nmem
op_assign
l_int|0
comma
id|nirq
op_assign
l_int|0
comma
id|ndma
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;active
)paren
r_goto
id|done
suffix:semicolon
id|buf
op_add_assign
l_int|3
suffix:semicolon
id|pnp_init_resources
c_func
(paren
op_amp
id|dev-&gt;res
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;io&quot;
comma
l_int|2
)paren
)paren
(brace
id|buf
op_add_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
id|dev-&gt;res.port_resource
(braket
id|nport
)braket
dot
id|start
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buf
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|buf
op_add_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
id|dev-&gt;res.port_resource
(braket
id|nport
)braket
dot
id|end
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|dev-&gt;res.port_resource
(braket
id|nport
)braket
dot
id|end
op_assign
id|dev-&gt;res.port_resource
(braket
id|nport
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;res.port_resource
(braket
id|nport
)braket
dot
id|flags
op_assign
id|IORESOURCE_IO
suffix:semicolon
id|nport
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|nport
op_ge
id|PNP_MAX_PORT
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;mem&quot;
comma
l_int|3
)paren
)paren
(brace
id|buf
op_add_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
id|dev-&gt;res.mem_resource
(braket
id|nmem
)braket
dot
id|start
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buf
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|buf
op_add_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
id|dev-&gt;res.mem_resource
(braket
id|nmem
)braket
dot
id|end
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|dev-&gt;res.mem_resource
(braket
id|nmem
)braket
dot
id|end
op_assign
id|dev-&gt;res.mem_resource
(braket
id|nmem
)braket
dot
id|start
suffix:semicolon
id|dev-&gt;res.mem_resource
(braket
id|nmem
)braket
dot
id|flags
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|nmem
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|nmem
op_ge
id|PNP_MAX_MEM
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;irq&quot;
comma
l_int|3
)paren
)paren
(brace
id|buf
op_add_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
id|dev-&gt;res.irq_resource
(braket
id|nirq
)braket
dot
id|start
op_assign
id|dev-&gt;res.irq_resource
(braket
id|nirq
)braket
dot
id|end
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|dev-&gt;res.irq_resource
(braket
id|nirq
)braket
dot
id|flags
op_assign
id|IORESOURCE_IRQ
suffix:semicolon
id|nirq
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|nirq
op_ge
id|PNP_MAX_IRQ
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strnicmp
c_func
(paren
id|buf
comma
l_string|&quot;dma&quot;
comma
l_int|3
)paren
)paren
(brace
id|buf
op_add_assign
l_int|3
suffix:semicolon
r_while
c_loop
(paren
id|isspace
c_func
(paren
op_star
id|buf
)paren
)paren
op_increment
id|buf
suffix:semicolon
id|dev-&gt;res.dma_resource
(braket
id|ndma
)braket
dot
id|start
op_assign
id|dev-&gt;res.dma_resource
(braket
id|ndma
)braket
dot
id|end
op_assign
id|simple_strtoul
c_func
(paren
id|buf
comma
op_amp
id|buf
comma
l_int|0
)paren
suffix:semicolon
id|dev-&gt;res.dma_resource
(braket
id|ndma
)braket
dot
id|flags
op_assign
id|IORESOURCE_DMA
suffix:semicolon
id|ndma
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ndma
op_ge
id|PNP_MAX_DMA
)paren
r_break
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|pnp_res_mutex
)paren
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|done
suffix:colon
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|resources
comma
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|pnp_show_current_resources
comma
id|pnp_set_current_resources
)paren
suffix:semicolon
DECL|function|pnp_show_current_ids
r_static
id|ssize_t
id|pnp_show_current_ids
c_func
(paren
r_struct
id|device
op_star
id|dmdev
comma
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|str
op_assign
id|buf
suffix:semicolon
r_struct
id|pnp_dev
op_star
id|dev
op_assign
id|to_pnp_dev
c_func
(paren
id|dmdev
)paren
suffix:semicolon
r_struct
id|pnp_id
op_star
id|pos
op_assign
id|dev-&gt;id
suffix:semicolon
r_while
c_loop
(paren
id|pos
)paren
(brace
id|str
op_add_assign
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|pos-&gt;id
)paren
suffix:semicolon
id|pos
op_assign
id|pos-&gt;next
suffix:semicolon
)brace
r_return
(paren
id|str
op_minus
id|buf
)paren
suffix:semicolon
)brace
r_static
id|DEVICE_ATTR
c_func
(paren
id|id
comma
id|S_IRUGO
comma
id|pnp_show_current_ids
comma
l_int|NULL
)paren
suffix:semicolon
DECL|function|pnp_interface_attach_device
r_int
id|pnp_interface_attach_device
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
)paren
(brace
id|device_create_file
c_func
(paren
op_amp
id|dev-&gt;dev
comma
op_amp
id|dev_attr_options
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|dev-&gt;dev
comma
op_amp
id|dev_attr_resources
)paren
suffix:semicolon
id|device_create_file
c_func
(paren
op_amp
id|dev-&gt;dev
comma
op_amp
id|dev_attr_id
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
