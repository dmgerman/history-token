multiline_comment|/*&n; * linux/arch/arm/mach-omap/board-osk.c&n; *&n; * Board specific init for OMAP5912 OSK&n; *&n; * Written by Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/clocks.h&gt;
macro_line|#include &lt;asm/arch/gpio.h&gt;
macro_line|#include &lt;asm/arch/fpga.h&gt;
macro_line|#include &lt;asm/arch/usb.h&gt;
macro_line|#include &lt;asm/arch/serial.h&gt;
macro_line|#include &quot;common.h&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|osk5912_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OMAP_OSK_NOR_FLASH_BASE
comma
id|OMAP_OSK_NOR_FLASH_START
comma
id|OMAP_OSK_NOR_FLASH_SIZE
comma
id|MT_DEVICE
)brace
comma
)brace
suffix:semicolon
DECL|variable|osk_serial_ports
r_static
r_int
id|__initdata
id|osk_serial_ports
(braket
id|OMAP_MAX_NR_PORTS
)braket
op_assign
(brace
l_int|1
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|osk5912_smc91x_resources
r_static
r_struct
id|resource
id|osk5912_smc91x_resources
(braket
)braket
op_assign
(brace
(braket
l_int|0
)braket
op_assign
(brace
dot
id|start
op_assign
id|OMAP_OSK_ETHR_START
comma
multiline_comment|/* Physical */
dot
id|end
op_assign
id|OMAP_OSK_ETHR_START
op_plus
id|SZ_4K
comma
dot
id|flags
op_assign
id|IORESOURCE_MEM
comma
)brace
comma
(braket
l_int|1
)braket
op_assign
(brace
dot
id|start
op_assign
l_int|0
comma
multiline_comment|/* Really GPIO 0 */
dot
id|end
op_assign
l_int|0
comma
dot
id|flags
op_assign
id|IORESOURCE_IRQ
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|osk5912_smc91x_device
r_static
r_struct
id|platform_device
id|osk5912_smc91x_device
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;smc91x&quot;
comma
dot
id|id
op_assign
l_int|0
comma
dot
id|num_resources
op_assign
id|ARRAY_SIZE
c_func
(paren
id|osk5912_smc91x_resources
)paren
comma
dot
id|resource
op_assign
id|osk5912_smc91x_resources
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|platform_device
op_star
id|osk5912_devices
(braket
)braket
id|__initdata
op_assign
(brace
op_amp
id|osk5912_smc91x_device
comma
)brace
suffix:semicolon
DECL|function|osk_init_irq
r_void
id|osk_init_irq
c_func
(paren
r_void
)paren
(brace
id|omap_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|omap_usb_config
id|osk_usb_config
id|__initdata
op_assign
(brace
multiline_comment|/* has usb host and device, but no Mini-AB port */
dot
id|register_host
op_assign
l_int|1
comma
dot
id|hmc_mode
op_assign
l_int|16
comma
dot
id|pins
(braket
l_int|0
)braket
op_assign
l_int|2
comma
)brace
suffix:semicolon
DECL|variable|osk_config
r_static
r_struct
id|omap_board_config_kernel
id|osk_config
(braket
)braket
op_assign
(brace
(brace
id|OMAP_TAG_USB
comma
op_amp
id|osk_usb_config
)brace
comma
)brace
suffix:semicolon
DECL|function|osk_init
r_static
r_void
id|__init
id|osk_init
c_func
(paren
r_void
)paren
(brace
id|platform_add_devices
c_func
(paren
id|osk5912_devices
comma
id|ARRAY_SIZE
c_func
(paren
id|osk5912_devices
)paren
)paren
suffix:semicolon
id|omap_board_config
op_assign
id|osk_config
suffix:semicolon
id|omap_board_config_size
op_assign
id|ARRAY_SIZE
c_func
(paren
id|osk_config
)paren
suffix:semicolon
)brace
DECL|function|osk_map_io
r_static
r_void
id|__init
id|osk_map_io
c_func
(paren
r_void
)paren
(brace
id|omap_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|osk5912_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|osk5912_io_desc
)paren
)paren
suffix:semicolon
id|omap_serial_init
c_func
(paren
id|osk_serial_ports
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|OMAP_OSK
comma
l_string|&quot;TI-OSK&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x10000000
comma
l_int|0xfff00000
comma
l_int|0xfef00000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x10000100
)paren
id|MAPIO
c_func
(paren
id|osk_map_io
)paren
id|INITIRQ
c_func
(paren
id|osk_init_irq
)paren
id|INIT_MACHINE
c_func
(paren
id|osk_init
)paren
dot
id|timer
op_assign
op_amp
id|omap_timer
comma
id|MACHINE_END
eof
