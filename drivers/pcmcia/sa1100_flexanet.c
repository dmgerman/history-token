multiline_comment|/*&n; * drivers/pcmcia/sa1100_flexanet.c&n; *&n; * PCMCIA implementation routines for Flexanet.&n; * by Jordi Colomer, 09/05/2001&n; *&n; * Yet to be defined.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/arch/pcmcia.h&gt;
multiline_comment|/*&n; * Socket initialization.&n; *&n; * Called by sa1100_pcmcia_driver_init on startup.&n; * Must return the number of slots.&n; *&n; */
DECL|function|flexanet_pcmcia_init
r_static
r_int
(def_block
id|flexanet_pcmcia_init
c_func
(paren
r_struct
id|pcmcia_init
op_star
id|init
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; * Socket shutdown&n; *&n; */
DECL|function|flexanet_pcmcia_shutdown
r_static
r_int
id|flexanet_pcmcia_shutdown
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the state of the sockets.&n; *&n; *  Sockets in Flexanet are 3.3V only, without BVD2.&n; *&n; */
DECL|function|flexanet_pcmcia_socket_state
r_static
r_int
(def_block
id|flexanet_pcmcia_socket_state
c_func
(paren
r_struct
id|pcmcia_state_array
op_star
id|state_array
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; * Return the IRQ information for a given socket number (the IRQ number)&n; *&n; */
DECL|function|flexanet_pcmcia_get_irq_info
r_static
r_int
(def_block
id|flexanet_pcmcia_get_irq_info
c_func
(paren
r_struct
id|pcmcia_irq_info
op_star
id|info
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; *&n; */
DECL|function|flexanet_pcmcia_configure_socket
r_static
r_int
id|flexanet_pcmcia_configure_socket
c_func
(paren
r_const
r_struct
id|pcmcia_configure
op_star
id|configure
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * The set of socket operations&n; *&n; */
DECL|variable|flexanet_pcmcia_ops
r_struct
id|pcmcia_low_level
id|flexanet_pcmcia_ops
op_assign
(brace
id|flexanet_pcmcia_init
comma
id|flexanet_pcmcia_shutdown
comma
id|flexanet_pcmcia_socket_state
comma
id|flexanet_pcmcia_get_irq_info
comma
id|flexanet_pcmcia_configure_socket
)brace
suffix:semicolon
eof
