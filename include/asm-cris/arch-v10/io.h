macro_line|#ifndef _ASM_ARCH_CRIS_IO_H
DECL|macro|_ASM_ARCH_CRIS_IO_H
mdefine_line|#define _ASM_ARCH_CRIS_IO_H
macro_line|#include &lt;asm/arch/svinto.h&gt;
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Etrax shadow registers - which live in arch/cris/kernel/shadows.c */
r_extern
r_int
r_int
id|port_g_data_shadow
suffix:semicolon
r_extern
r_int
r_char
id|port_pa_dir_shadow
suffix:semicolon
r_extern
r_int
r_char
id|port_pa_data_shadow
suffix:semicolon
r_extern
r_int
r_char
id|port_pb_i2c_shadow
suffix:semicolon
r_extern
r_int
r_char
id|port_pb_config_shadow
suffix:semicolon
r_extern
r_int
r_char
id|port_pb_dir_shadow
suffix:semicolon
r_extern
r_int
r_char
id|port_pb_data_shadow
suffix:semicolon
r_extern
r_int
r_int
id|r_timer_ctrl_shadow
suffix:semicolon
r_extern
r_int
r_int
id|port_cse1_shadow
suffix:semicolon
r_extern
r_int
r_int
id|port_csp0_shadow
suffix:semicolon
r_extern
r_int
r_int
id|port_csp4_shadow
suffix:semicolon
r_extern
r_volatile
r_int
r_int
op_star
id|port_cse1_addr
suffix:semicolon
r_extern
r_volatile
r_int
r_int
op_star
id|port_csp0_addr
suffix:semicolon
r_extern
r_volatile
r_int
r_int
op_star
id|port_csp4_addr
suffix:semicolon
multiline_comment|/* macro for setting regs through a shadow - &n; * r = register name (like R_PORT_PA_DATA)&n; * s = shadow name (like port_pa_data_shadow)&n; * b = bit number&n; * v = value (0 or 1)&n; */
DECL|macro|REG_SHADOW_SET
mdefine_line|#define REG_SHADOW_SET(r,s,b,v) *r = s = (s &amp; ~(1 &lt;&lt; (b))) | ((v) &lt;&lt; (b))
multiline_comment|/* The LED&squot;s on various Etrax-based products are set differently. */
macro_line|#if defined(CONFIG_ETRAX_NO_LEDS) || defined(CONFIG_SVINTO_SIM)
DECL|macro|CONFIG_ETRAX_PA_LEDS
macro_line|#undef CONFIG_ETRAX_PA_LEDS
DECL|macro|CONFIG_ETRAX_PB_LEDS
macro_line|#undef CONFIG_ETRAX_PB_LEDS
DECL|macro|CONFIG_ETRAX_CSP0_LEDS
macro_line|#undef CONFIG_ETRAX_CSP0_LEDS
DECL|macro|LED_NETWORK_SET_G
mdefine_line|#define LED_NETWORK_SET_G(x)
DECL|macro|LED_NETWORK_SET_R
mdefine_line|#define LED_NETWORK_SET_R(x)
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x)
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x)
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x)
macro_line|#endif
macro_line|#if !defined(CONFIG_ETRAX_CSP0_LEDS)
DECL|macro|LED_BIT_SET
mdefine_line|#define LED_BIT_SET(x)
DECL|macro|LED_BIT_CLR
mdefine_line|#define LED_BIT_CLR(x)
macro_line|#endif
DECL|macro|LED_OFF
mdefine_line|#define LED_OFF    0x00
DECL|macro|LED_GREEN
mdefine_line|#define LED_GREEN  0x01
DECL|macro|LED_RED
mdefine_line|#define LED_RED    0x02
DECL|macro|LED_ORANGE
mdefine_line|#define LED_ORANGE (LED_GREEN | LED_RED)
macro_line|#if CONFIG_ETRAX_LED1G == CONFIG_ETRAX_LED1R 
DECL|macro|LED_NETWORK_SET
mdefine_line|#define LED_NETWORK_SET(x)                          &bslash;&n;&t;do {                                        &bslash;&n;&t;&t;LED_NETWORK_SET_G((x) &amp; LED_GREEN); &bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|LED_NETWORK_SET
mdefine_line|#define LED_NETWORK_SET(x)                          &bslash;&n;&t;do {                                        &bslash;&n;&t;&t;LED_NETWORK_SET_G((x) &amp; LED_GREEN); &bslash;&n;&t;&t;LED_NETWORK_SET_R((x) &amp; LED_RED);   &bslash;&n;&t;} while (0)
macro_line|#endif
macro_line|#if CONFIG_ETRAX_LED2G == CONFIG_ETRAX_LED2R 
DECL|macro|LED_ACTIVE_SET
mdefine_line|#define LED_ACTIVE_SET(x)                           &bslash;&n;&t;do {                                        &bslash;&n;&t;&t;LED_ACTIVE_SET_G((x) &amp; LED_GREEN);  &bslash;&n;&t;} while (0)
macro_line|#else
DECL|macro|LED_ACTIVE_SET
mdefine_line|#define LED_ACTIVE_SET(x)                           &bslash;&n;&t;do {                                        &bslash;&n;&t;&t;LED_ACTIVE_SET_G((x) &amp; LED_GREEN);  &bslash;&n;&t;&t;LED_ACTIVE_SET_R((x) &amp; LED_RED);    &bslash;&n;&t;} while (0)
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_PA_LEDS
DECL|macro|LED_NETWORK_SET_G
mdefine_line|#define LED_NETWORK_SET_G(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED1G, !(x))
DECL|macro|LED_NETWORK_SET_R
mdefine_line|#define LED_NETWORK_SET_R(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED1R, !(x))
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED2G, !(x))
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED2R, !(x))
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x) &bslash;&n;         do{&bslash;&n;                REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED3G, !(x));&bslash;&n;                REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED3R, !(x));&bslash;&n;        }while(0)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED3G, !(x)) 
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_PB_LEDS
DECL|macro|LED_NETWORK_SET_G
mdefine_line|#define LED_NETWORK_SET_G(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED1G, !(x))
DECL|macro|LED_NETWORK_SET_R
mdefine_line|#define LED_NETWORK_SET_R(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED1R, !(x))
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED2G, !(x))
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED2R, !(x))
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x) &bslash;&n;        do{&bslash;&n;                REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED3G, !(x));&bslash;&n;                REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED3R, !(x));&bslash;&n;        }while(0)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED3G, !(x))     
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_CSP0_LEDS
DECL|macro|CONFIGURABLE_LEDS
mdefine_line|#define CONFIGURABLE_LEDS&bslash;&n;        ((1 &lt;&lt; CONFIG_ETRAX_LED1G ) | (1 &lt;&lt; CONFIG_ETRAX_LED1R ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED2G ) | (1 &lt;&lt; CONFIG_ETRAX_LED2R ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED3G ) | (1 &lt;&lt; CONFIG_ETRAX_LED3R ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED4G ) | (1 &lt;&lt; CONFIG_ETRAX_LED4R ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED5G ) | (1 &lt;&lt; CONFIG_ETRAX_LED5R ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED6G ) | (1 &lt;&lt; CONFIG_ETRAX_LED6R ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED7G ) | (1 &lt;&lt; CONFIG_ETRAX_LED7R ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED8Y ) | (1 &lt;&lt; CONFIG_ETRAX_LED9Y ) |&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED10Y ) |(1 &lt;&lt; CONFIG_ETRAX_LED11Y )|&bslash;&n;         (1 &lt;&lt; CONFIG_ETRAX_LED12R ))
DECL|macro|LED_NETWORK_SET_G
mdefine_line|#define LED_NETWORK_SET_G(x) &bslash;&n;         REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_LED1G, !(x))
DECL|macro|LED_NETWORK_SET_R
mdefine_line|#define LED_NETWORK_SET_R(x) &bslash;&n;         REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_LED1R, !(x))
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x) &bslash;&n;         REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_LED2G, !(x))
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x) &bslash;&n;         REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_LED2R, !(x))
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x) &bslash;&n;        do{&bslash;&n;                REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_LED3G, !(x));&bslash;&n;                REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_LED3R, !(x));&bslash;&n;        }while(0)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x) &bslash;&n;         REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_LED3G, !(x))
DECL|macro|LED_BIT_SET
mdefine_line|#define LED_BIT_SET(x)&bslash;&n;        do{&bslash;&n;                if((( 1 &lt;&lt; x) &amp; CONFIGURABLE_LEDS)  != 0)&bslash;&n;                       REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, x, 1);&bslash;&n;        }while(0)
DECL|macro|LED_BIT_CLR
mdefine_line|#define LED_BIT_CLR(x)&bslash;&n;        do{&bslash;&n;                if((( 1 &lt;&lt; x) &amp; CONFIGURABLE_LEDS)  != 0)&bslash;&n;                       REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, x, 0);&bslash;&n;        }while(0)
macro_line|#endif
macro_line|#
macro_line|#ifdef CONFIG_ETRAX_SOFT_SHUTDOWN
DECL|macro|SOFT_SHUTDOWN
mdefine_line|#define SOFT_SHUTDOWN() &bslash;&n;          REG_SHADOW_SET(port_csp0_addr, port_csp0_shadow, CONFIG_ETRAX_SHUTDOWN_BIT, 1)
macro_line|#else
DECL|macro|SOFT_SHUTDOWN
mdefine_line|#define SOFT_SHUTDOWN()
macro_line|#endif
multiline_comment|/* Console I/O for simulated etrax100.  Use #ifdef so erroneous&n;   use will be evident. */
macro_line|#ifdef CONFIG_SVINTO_SIM
multiline_comment|/* Let&squot;s use the ucsim interface since it lets us do write(2, ...) */
DECL|macro|SIMCOUT
mdefine_line|#define SIMCOUT(s,len)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  asm (&quot;moveq 4,$r9&t;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;moveq 2,$r10&t;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;move.d %0,$r11&t;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;move.d %1,$r12&t;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;push $irp&t;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;move 0f,$irp&t;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;jump -6809&t;&bslash;n&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;0:&t;&t;&bslash;n&bslash;t&quot;&t;&t;&t;&t;&t;&t;&bslash;&n;       &quot;pop $irp&quot;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;       : : &quot;rm&quot; (s), &quot;rm&quot; (len) : &quot;r9&quot;,&quot;r10&quot;,&quot;r11&quot;,&quot;r12&quot;,&quot;memory&quot;)
DECL|macro|TRACE_ON
mdefine_line|#define TRACE_ON() __extension__ &bslash;&n; ({ int _Foofoo; __asm__ volatile (&quot;bmod [%0],%0&quot; : &quot;=r&quot; (_Foofoo) : &quot;0&quot; &bslash;&n;&t;&t;&t;       (255)); _Foofoo; })
DECL|macro|TRACE_OFF
mdefine_line|#define TRACE_OFF() do { __asm__ volatile (&quot;bmod [%0],%0&quot; :: &quot;r&quot; (254)); } while (0)
DECL|macro|SIM_END
mdefine_line|#define SIM_END() do { __asm__ volatile (&quot;bmod [%0],%0&quot; :: &quot;r&quot; (28)); } while (0)
DECL|macro|CRIS_CYCLES
mdefine_line|#define CRIS_CYCLES() __extension__ &bslash;&n; ({ unsigned long c; asm (&quot;bmod [%1],%0&quot; : &quot;=r&quot; (c) : &quot;r&quot; (27)); c;})
macro_line|#endif /* ! defined CONFIG_SVINTO_SIM */
macro_line|#endif
eof
