multiline_comment|/* linux/include/asm-arm/arch-omap/tps65010.h&n; *&n; * Functions to access TPS65010 power management device.&n; *&n; * Copyright (C) 2004 Dirk Behme &lt;dirk.behme@de.bosch.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License as published by the&n; * Free Software Foundation; either version 2 of the License, or (at your&n; * option) any later version.&n; *&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND ANY EXPRESS OR IMPLIED&n; * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF&n; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN&n; * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,&n; * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT&n; * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF&n; * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON&n; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT&n; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF&n; * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.&n; *&n; * You should have received a copy of the  GNU General Public License along&n; * with this program; if not, write  to the Free Software Foundation, Inc.,&n; * 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef __ASM_ARCH_TPS65010_H
DECL|macro|__ASM_ARCH_TPS65010_H
mdefine_line|#define __ASM_ARCH_TPS65010_H
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Macros used by exported functions&n; * ----------------------------------------------------------------------------&n; */
DECL|macro|LED1
mdefine_line|#define LED1  1
DECL|macro|LED2
mdefine_line|#define LED2  2
DECL|macro|OFF
mdefine_line|#define OFF   0
DECL|macro|ON
mdefine_line|#define ON    1
DECL|macro|BLINK
mdefine_line|#define BLINK 2
DECL|macro|GPIO1
mdefine_line|#define GPIO1 1
DECL|macro|GPIO2
mdefine_line|#define GPIO2 2
DECL|macro|GPIO3
mdefine_line|#define GPIO3 3
DECL|macro|GPIO4
mdefine_line|#define GPIO4 4
DECL|macro|LOW
mdefine_line|#define LOW   0
DECL|macro|HIGH
mdefine_line|#define HIGH  1
multiline_comment|/*&n; * ----------------------------------------------------------------------------&n; * Exported functions&n; * ----------------------------------------------------------------------------&n; */
multiline_comment|/* Draw from VBUS:&n; *   0 mA -- DON&squot;T DRAW (might supply power instead)&n; * 100 mA -- usb unit load (slowest charge rate)&n; * 500 mA -- usb high power (fast battery charge)&n; */
r_extern
r_int
id|tps65010_set_vbus_draw
c_func
(paren
r_int
id|mA
)paren
suffix:semicolon
multiline_comment|/* tps65010_set_gpio_out_value parameter:&n; * gpio:  GPIO1, GPIO2, GPIO3 or GPIO4&n; * value: LOW or HIGH&n; */
r_extern
r_int
id|tps65010_set_gpio_out_value
c_func
(paren
r_int
id|gpio
comma
r_int
id|value
)paren
suffix:semicolon
multiline_comment|/* tps65010_set_led parameter:&n; * led:  LED1 or LED2&n; * mode: ON, OFF or BLINK&n; */
r_extern
r_int
id|tps65010_set_led
c_func
(paren
r_int
id|led
comma
r_int
id|mode
)paren
suffix:semicolon
multiline_comment|/* tps65010_set_low_pwr parameter:&n; * mode: ON or OFF&n; */
r_extern
r_int
id|tps65010_set_low_pwr
c_func
(paren
r_int
id|mode
)paren
suffix:semicolon
macro_line|#endif /*  __ASM_ARCH_TPS65010_H */
eof
