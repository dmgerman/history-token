multiline_comment|/*&n; * FILE NAME ite_gpio.c&n; *&n; * BRIEF MODULE DESCRIPTION&n; *  API for ITE GPIO device.&n; *  Driver for ITE GPIO device.&n; *&n; *  Author: MontaVista Software, Inc.  &lt;source@mvista.com&gt;&n; *          Hai-Pao Fan &lt;haipao@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE&t;LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/it8172/it8172_int.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ite_gpio.h&gt;
DECL|macro|ite_gpio_base
mdefine_line|#define ite_gpio_base 0x14013800
DECL|macro|ITE_GPADR
mdefine_line|#define&t;ITE_GPADR&t;(*(volatile __u8 *)(0x14013800 + KSEG1))
DECL|macro|ITE_GPBDR
mdefine_line|#define&t;ITE_GPBDR&t;(*(volatile __u8 *)(0x14013808 + KSEG1))
DECL|macro|ITE_GPCDR
mdefine_line|#define&t;ITE_GPCDR&t;(*(volatile __u8 *)(0x14013810 + KSEG1))
DECL|macro|ITE_GPACR
mdefine_line|#define&t;ITE_GPACR&t;(*(volatile __u16 *)(0x14013802 + KSEG1))
DECL|macro|ITE_GPBCR
mdefine_line|#define&t;ITE_GPBCR&t;(*(volatile __u16 *)(0x1401380a + KSEG1))
DECL|macro|ITE_GPCCR
mdefine_line|#define&t;ITE_GPCCR&t;(*(volatile __u16 *)(0x14013812 + KSEG1))
DECL|macro|ITE_GPAICR
mdefine_line|#define ITE_GPAICR&t;(*(volatile __u16 *)(0x14013804 + KSEG1))
DECL|macro|ITE_GPBICR
mdefine_line|#define&t;ITE_GPBICR&t;(*(volatile __u16 *)(0x1401380c + KSEG1))
DECL|macro|ITE_GPCICR
mdefine_line|#define&t;ITE_GPCICR&t;(*(volatile __u16 *)(0x14013814 + KSEG1))
DECL|macro|ITE_GPAISR
mdefine_line|#define&t;ITE_GPAISR&t;(*(volatile __u8 *)(0x14013806 + KSEG1))
DECL|macro|ITE_GPBISR
mdefine_line|#define&t;ITE_GPBISR&t;(*(volatile __u8 *)(0x1401380e + KSEG1))
DECL|macro|ITE_GPCISR
mdefine_line|#define&t;ITE_GPCISR&t;(*(volatile __u8 *)(0x14013816 + KSEG1))
DECL|macro|ITE_GCR
mdefine_line|#define&t;ITE_GCR&t;&t;(*(volatile __u8 *)(0x14013818 + KSEG1))
DECL|macro|MAX_GPIO_LINE
mdefine_line|#define MAX_GPIO_LINE&t;&t;21
DECL|variable|ite_gpio_irq
r_static
r_int
id|ite_gpio_irq
op_assign
id|IT8172_GPIO_IRQ
suffix:semicolon
DECL|variable|ite_irq_counter
r_static
r_int
id|ite_irq_counter
(braket
id|MAX_GPIO_LINE
)braket
suffix:semicolon
DECL|variable|ite_gpio_wait
id|wait_queue_head_t
id|ite_gpio_wait
(braket
id|MAX_GPIO_LINE
)braket
suffix:semicolon
DECL|variable|ite_gpio_irq_pending
r_static
r_int
id|ite_gpio_irq_pending
(braket
id|MAX_GPIO_LINE
)braket
suffix:semicolon
DECL|variable|ite_gpio_debug
r_static
r_int
id|ite_gpio_debug
op_assign
l_int|0
suffix:semicolon
DECL|macro|DEB
mdefine_line|#define DEB(x)  if (ite_gpio_debug&gt;=1) x
DECL|function|ite_gpio_in
r_int
id|ite_gpio_in
c_func
(paren
id|__u32
id|device
comma
id|__u32
id|mask
comma
r_volatile
id|__u32
op_star
id|data
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;ite_gpio_in mask=0x%x&bslash;n&quot;
comma
id|mask
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|device
)paren
(brace
r_case
id|ITE_GPIO_PORTA
suffix:colon
id|ITE_GPACR
op_assign
(paren
id|__u16
)paren
id|mask
suffix:semicolon
multiline_comment|/* 0xffff */
op_star
id|data
op_assign
id|ITE_GPADR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTB
suffix:colon
id|ITE_GPBCR
op_assign
(paren
id|__u16
)paren
id|mask
suffix:semicolon
multiline_comment|/* 0xffff */
op_star
id|data
op_assign
id|ITE_GPBDR
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTC
suffix:colon
id|ITE_GPCCR
op_assign
(paren
id|__u16
)paren
id|mask
suffix:semicolon
multiline_comment|/* 0x03ff */
op_star
id|data
op_assign
id|ITE_GPCDR
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_out
r_int
id|ite_gpio_out
c_func
(paren
id|__u32
id|device
comma
id|__u32
id|mask
comma
id|__u32
id|data
)paren
(brace
r_switch
c_cond
(paren
id|device
)paren
(brace
r_case
id|ITE_GPIO_PORTA
suffix:colon
id|ITE_GPACR
op_assign
(paren
id|__u16
)paren
id|mask
suffix:semicolon
multiline_comment|/* 0x5555 */
id|ITE_GPADR
op_assign
(paren
id|__u8
)paren
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTB
suffix:colon
id|ITE_GPBCR
op_assign
(paren
id|__u16
)paren
id|mask
suffix:semicolon
multiline_comment|/* 0x5555 */
id|ITE_GPBDR
op_assign
(paren
id|__u8
)paren
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTC
suffix:colon
id|ITE_GPCCR
op_assign
(paren
id|__u16
)paren
id|mask
suffix:semicolon
multiline_comment|/* 0x0155 */
id|ITE_GPCDR
op_assign
(paren
id|__u8
)paren
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_int_ctrl
r_int
id|ite_gpio_int_ctrl
c_func
(paren
id|__u32
id|device
comma
id|__u32
id|mask
comma
id|__u32
id|data
)paren
(brace
r_switch
c_cond
(paren
id|device
)paren
(brace
r_case
id|ITE_GPIO_PORTA
suffix:colon
id|ITE_GPAICR
op_assign
(paren
id|ITE_GPAICR
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|data
op_amp
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTB
suffix:colon
id|ITE_GPBICR
op_assign
(paren
id|ITE_GPBICR
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|data
op_amp
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTC
suffix:colon
id|ITE_GPCICR
op_assign
(paren
id|ITE_GPCICR
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|data
op_amp
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_in_status
r_int
id|ite_gpio_in_status
c_func
(paren
id|__u32
id|device
comma
id|__u32
id|mask
comma
r_volatile
id|__u32
op_star
id|data
)paren
(brace
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|MAX_GPIO_LINE
OG
op_star
id|data
)paren
op_logical_and
(paren
op_star
id|data
op_ge
l_int|0
)paren
)paren
id|ret
op_assign
id|ite_gpio_irq_pending
(braket
op_star
id|data
)braket
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;ite_gpio_in_status %d ret=%d&bslash;n&quot;
comma
op_star
id|data
comma
id|ret
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|device
)paren
(brace
r_case
id|ITE_GPIO_PORTA
suffix:colon
op_star
id|data
op_assign
id|ITE_GPAISR
op_amp
id|mask
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTB
suffix:colon
op_star
id|data
op_assign
id|ITE_GPBISR
op_amp
id|mask
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTC
suffix:colon
op_star
id|data
op_assign
id|ITE_GPCISR
op_amp
id|mask
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ite_gpio_out_status
r_int
id|ite_gpio_out_status
c_func
(paren
id|__u32
id|device
comma
id|__u32
id|mask
comma
id|__u32
id|data
)paren
(brace
r_switch
c_cond
(paren
id|device
)paren
(brace
r_case
id|ITE_GPIO_PORTA
suffix:colon
id|ITE_GPAISR
op_assign
(paren
id|ITE_GPAISR
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|data
op_amp
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTB
suffix:colon
id|ITE_GPBISR
op_assign
(paren
id|ITE_GPBISR
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|data
op_amp
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTC
suffix:colon
id|ITE_GPCISR
op_assign
(paren
id|ITE_GPCISR
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|data
op_amp
id|mask
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_gen_ctrl
r_int
id|ite_gpio_gen_ctrl
c_func
(paren
id|__u32
id|device
comma
id|__u32
id|mask
comma
id|__u32
id|data
)paren
(brace
id|ITE_GCR
op_assign
(paren
id|ITE_GCR
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|data
op_amp
id|mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_int_wait
r_int
id|ite_gpio_int_wait
(paren
id|__u32
id|device
comma
id|__u32
id|mask
comma
id|__u32
id|data
)paren
(brace
r_int
id|i
comma
id|line
op_assign
l_int|0
comma
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|device
)paren
(brace
r_case
id|ITE_GPIO_PORTA
suffix:colon
id|line
op_assign
id|data
op_amp
id|mask
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTB
suffix:colon
id|line
op_assign
(paren
id|data
op_amp
id|mask
)paren
op_lshift
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_PORTC
suffix:colon
id|line
op_assign
(paren
id|data
op_amp
id|mask
)paren
op_lshift
l_int|16
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
id|MAX_GPIO_LINE
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|line
)paren
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
r_break
suffix:semicolon
)brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;wait device=0x%d mask=0x%x data=0x%x index %d&bslash;n&quot;
comma
id|device
comma
id|mask
comma
id|data
comma
id|i
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
op_amp
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ite_gpio_irq_pending
(braket
id|i
)braket
op_eq
l_int|1
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|ite_gpio_irq_pending
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|ite_gpio_wait
(braket
id|i
)braket
comma
l_int|3
op_star
id|HZ
)paren
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|ite_gpio_irq_pending
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|ite_gpio_in
id|EXPORT_SYMBOL
c_func
(paren
id|ite_gpio_in
)paren
suffix:semicolon
DECL|variable|ite_gpio_out
id|EXPORT_SYMBOL
c_func
(paren
id|ite_gpio_out
)paren
suffix:semicolon
DECL|variable|ite_gpio_int_ctrl
id|EXPORT_SYMBOL
c_func
(paren
id|ite_gpio_int_ctrl
)paren
suffix:semicolon
DECL|variable|ite_gpio_in_status
id|EXPORT_SYMBOL
c_func
(paren
id|ite_gpio_in_status
)paren
suffix:semicolon
DECL|variable|ite_gpio_out_status
id|EXPORT_SYMBOL
c_func
(paren
id|ite_gpio_out_status
)paren
suffix:semicolon
DECL|variable|ite_gpio_gen_ctrl
id|EXPORT_SYMBOL
c_func
(paren
id|ite_gpio_gen_ctrl
)paren
suffix:semicolon
DECL|variable|ite_gpio_int_wait
id|EXPORT_SYMBOL
c_func
(paren
id|ite_gpio_int_wait
)paren
suffix:semicolon
DECL|function|ite_gpio_open
r_static
r_int
id|ite_gpio_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_release
r_static
r_int
id|ite_gpio_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_ioctl
r_static
r_int
id|ite_gpio_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_static
r_struct
id|ite_gpio_ioctl_data
id|ioctl_data
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ioctl_data
comma
(paren
r_struct
id|ite_gpio_ioctl_data
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|ioctl_data
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ioctl_data.device
OL
id|ITE_GPIO_PORTA
)paren
op_logical_or
(paren
id|ioctl_data.device
OG
id|ITE_GPIO_PORTC
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|ITE_GPIO_IN
suffix:colon
r_if
c_cond
(paren
id|ite_gpio_in
c_func
(paren
id|ioctl_data.device
comma
id|ioctl_data.mask
comma
op_amp
id|ioctl_data.data
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ite_gpio_ioctl_data
op_star
)paren
id|arg
comma
op_amp
id|ioctl_data
comma
r_sizeof
(paren
id|ioctl_data
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_OUT
suffix:colon
r_return
id|ite_gpio_out
c_func
(paren
id|ioctl_data.device
comma
id|ioctl_data.mask
comma
id|ioctl_data.data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_INT_CTRL
suffix:colon
r_return
id|ite_gpio_int_ctrl
c_func
(paren
id|ioctl_data.device
comma
id|ioctl_data.mask
comma
id|ioctl_data.data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_IN_STATUS
suffix:colon
r_if
c_cond
(paren
id|ite_gpio_in_status
c_func
(paren
id|ioctl_data.device
comma
id|ioctl_data.mask
comma
op_amp
id|ioctl_data.data
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
r_struct
id|ite_gpio_ioctl_data
op_star
)paren
id|arg
comma
op_amp
id|ioctl_data
comma
r_sizeof
(paren
id|ioctl_data
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_OUT_STATUS
suffix:colon
r_return
id|ite_gpio_out_status
c_func
(paren
id|ioctl_data.device
comma
id|ioctl_data.mask
comma
id|ioctl_data.data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_GEN_CTRL
suffix:colon
r_return
id|ite_gpio_gen_ctrl
c_func
(paren
id|ioctl_data.device
comma
id|ioctl_data.mask
comma
id|ioctl_data.data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ITE_GPIO_INT_WAIT
suffix:colon
r_return
id|ite_gpio_int_wait
c_func
(paren
id|ioctl_data.device
comma
id|ioctl_data.mask
comma
id|ioctl_data.data
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_irq_handler
r_static
r_void
id|ite_gpio_irq_handler
c_func
(paren
r_int
id|this_irq
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
r_int
id|i
comma
id|line
suffix:semicolon
id|line
op_assign
id|ITE_GPCISR
op_amp
l_int|0x1f
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|4
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|line
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
op_increment
id|ite_irq_counter
(braket
id|i
op_plus
l_int|16
)braket
suffix:semicolon
id|ite_gpio_irq_pending
(braket
id|i
op_plus
l_int|16
)braket
op_assign
l_int|2
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|ite_gpio_wait
(braket
id|i
op_plus
l_int|16
)braket
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;interrupt 0x%x %d&bslash;n&quot;
comma
op_amp
id|ite_gpio_wait
(braket
id|i
op_plus
l_int|16
)braket
comma
id|i
op_plus
l_int|16
)paren
)paren
suffix:semicolon
id|ITE_GPCISR
op_assign
id|ITE_GPCISR
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|line
op_assign
id|ITE_GPBISR
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|line
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
op_increment
id|ite_irq_counter
(braket
id|i
op_plus
l_int|8
)braket
suffix:semicolon
id|ite_gpio_irq_pending
(braket
id|i
op_plus
l_int|8
)braket
op_assign
l_int|2
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|ite_gpio_wait
(braket
id|i
op_plus
l_int|8
)braket
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;interrupt 0x%x %d&bslash;n&quot;
comma
id|ITE_GPBISR
comma
id|i
op_plus
l_int|8
)paren
)paren
suffix:semicolon
id|ITE_GPBISR
op_assign
id|ITE_GPBISR
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|line
op_assign
id|ITE_GPAISR
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|line
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
op_increment
id|ite_irq_counter
(braket
id|i
)braket
suffix:semicolon
id|ite_gpio_irq_pending
(braket
id|i
)braket
op_assign
l_int|2
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|ite_gpio_wait
(braket
id|i
)braket
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;interrupt 0x%x %d&bslash;n&quot;
comma
id|ITE_GPAISR
comma
id|i
)paren
)paren
suffix:semicolon
id|ITE_GPAISR
op_assign
id|ITE_GPAISR
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
DECL|variable|ite_gpio_fops
r_static
r_struct
id|file_operations
id|ite_gpio_fops
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|ioctl
op_assign
id|ite_gpio_ioctl
comma
dot
id|open
op_assign
id|ite_gpio_open
comma
dot
id|release
op_assign
id|ite_gpio_release
comma
)brace
suffix:semicolon
DECL|variable|ite_gpio_miscdev
r_static
r_struct
id|miscdevice
id|ite_gpio_miscdev
op_assign
(brace
id|MISC_DYNAMIC_MINOR
comma
l_string|&quot;ite_gpio&quot;
comma
op_amp
id|ite_gpio_fops
)brace
suffix:semicolon
DECL|function|ite_gpio_init
r_int
id|__init
id|ite_gpio_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|misc_register
c_func
(paren
op_amp
id|ite_gpio_miscdev
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ite_gpio_base
comma
l_int|0x1c
comma
l_string|&quot;ITE GPIO&quot;
)paren
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|ite_gpio_miscdev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* initialize registers */
id|ITE_GPACR
op_assign
l_int|0xffff
suffix:semicolon
id|ITE_GPBCR
op_assign
l_int|0xffff
suffix:semicolon
id|ITE_GPCCR
op_assign
l_int|0xffff
suffix:semicolon
id|ITE_GPAICR
op_assign
l_int|0x00ff
suffix:semicolon
id|ITE_GPBICR
op_assign
l_int|0x00ff
suffix:semicolon
id|ITE_GPCICR
op_assign
l_int|0x00ff
suffix:semicolon
id|ITE_GCR
op_assign
l_int|0
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
id|MAX_GPIO_LINE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ite_gpio_irq_pending
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|ite_gpio_wait
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|ite_gpio_irq
comma
id|ite_gpio_irq_handler
comma
id|SA_SHIRQ
comma
l_string|&quot;gpio&quot;
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|ite_gpio_miscdev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ite_gpio_base
comma
l_int|0x1c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;GPIO at 0x%x (irq = %d)&bslash;n&quot;
comma
id|ite_gpio_base
comma
id|ite_gpio_irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ite_gpio_exit
r_static
r_void
id|__exit
id|ite_gpio_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|ite_gpio_miscdev
)paren
suffix:semicolon
)brace
DECL|variable|ite_gpio_init
id|module_init
c_func
(paren
id|ite_gpio_init
)paren
suffix:semicolon
DECL|variable|ite_gpio_exit
id|module_exit
c_func
(paren
id|ite_gpio_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
