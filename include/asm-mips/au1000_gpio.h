multiline_comment|/*&n; * FILE NAME au1000_gpio.h&n; *&n; * BRIEF MODULE DESCRIPTION&n; *&t;API to Alchemy Au1000 GPIO device.&n; *&n; *  Author: MontaVista Software, Inc.  &lt;source@mvista.com&gt;&n; *          Steve Longerbeam &lt;stevel@mvista.com&gt;&n; *&n; * Copyright 2001 MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute  it and/or modify it&n; *  under  the terms of  the GNU General  Public License as published by the&n; *  Free Software Foundation;  either version 2 of the  License, or (at your&n; *  option) any later version.&n; *&n; *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS&squot;&squot; AND   ANY  EXPRESS OR IMPLIED&n; *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF&n; *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN&n; *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,&n; *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF&n; *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT&n; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; *  You should have received a copy of the  GNU General Public License along&n; *  with this program; if not, write  to the Free Software Foundation, Inc.,&n; *  675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __AU1000_GPIO_H
DECL|macro|__AU1000_GPIO_H
mdefine_line|#define __AU1000_GPIO_H
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|AU1000GPIO_IOC_MAGIC
mdefine_line|#define AU1000GPIO_IOC_MAGIC &squot;A&squot;
DECL|macro|AU1000GPIO_IN
mdefine_line|#define AU1000GPIO_IN&t;&t;_IOR (AU1000GPIO_IOC_MAGIC, 0, int)
DECL|macro|AU1000GPIO_SET
mdefine_line|#define AU1000GPIO_SET&t;&t;_IOW (AU1000GPIO_IOC_MAGIC, 1, int)
DECL|macro|AU1000GPIO_CLEAR
mdefine_line|#define AU1000GPIO_CLEAR&t;_IOW (AU1000GPIO_IOC_MAGIC, 2, int)
DECL|macro|AU1000GPIO_OUT
mdefine_line|#define AU1000GPIO_OUT&t;&t;_IOW (AU1000GPIO_IOC_MAGIC, 3, int)
DECL|macro|AU1000GPIO_TRISTATE
mdefine_line|#define AU1000GPIO_TRISTATE&t;_IOW (AU1000GPIO_IOC_MAGIC, 4, int)
DECL|macro|AU1000GPIO_AVAIL_MASK
mdefine_line|#define AU1000GPIO_AVAIL_MASK&t;_IOR (AU1000GPIO_IOC_MAGIC, 5, int)
macro_line|#ifdef __KERNEL__
r_extern
id|u32
id|get_au1000_avail_gpio_mask
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|au1000gpio_tristate
c_func
(paren
id|u32
id|data
)paren
suffix:semicolon
r_extern
r_int
id|au1000gpio_in
c_func
(paren
id|u32
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|au1000gpio_set
c_func
(paren
id|u32
id|data
)paren
suffix:semicolon
r_extern
r_int
id|au1000gpio_clear
c_func
(paren
id|u32
id|data
)paren
suffix:semicolon
r_extern
r_int
id|au1000gpio_out
c_func
(paren
id|u32
id|data
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
