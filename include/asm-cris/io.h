macro_line|#ifndef _ASM_CRIS_IO_H
DECL|macro|_ASM_CRIS_IO_H
mdefine_line|#define _ASM_CRIS_IO_H
macro_line|#include &lt;asm/page.h&gt;   /* for __va, __pa */
macro_line|#include &lt;asm/svinto.h&gt;
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Console I/O for simulated etrax100.  Use #ifdef so erroneous&n;   use will be evident. */
macro_line|#ifdef CONFIG_SVINTO_SIM
multiline_comment|/* Let&squot;s use the ucsim interface since it lets us do write(2, ...) */
DECL|macro|SIMCOUT
mdefine_line|#define SIMCOUT(s,len) asm (&quot;moveq 4,r9&bslash;n&bslash;tmoveq 2,r10&bslash;n&bslash;tmove.d %0,r11&bslash;n&bslash;tmove.d %1,r12&bslash;&n;&bslash;n&bslash;tpush irp&bslash;n&bslash;t.word 0xae3f&bslash;n&bslash;t.dword 0f&bslash;n&bslash;tjump -6809&bslash;n0:&bslash;n&bslash;tpop irp&quot; &bslash;&n;       : : &quot;rm&quot; (s), &quot;rm&quot; (len) : &quot;r9&quot;,&quot;r10&quot;,&quot;r11&quot;,&quot;r12&quot;,&quot;memory&quot;)
DECL|macro|TRACE_ON
mdefine_line|#define TRACE_ON() __extension__ &bslash;&n; ({ int _Foofoo; __asm__ volatile (&quot;bmod [%0],%0&quot; : &quot;=r&quot; (_Foofoo) : &quot;0&quot; &bslash;&n;&t;&t;&t;       (255)); _Foofoo; })
DECL|macro|TRACE_OFF
mdefine_line|#define TRACE_OFF() do { __asm__ volatile (&quot;bmod [%0],%0&quot; :: &quot;r&quot; (254)); } while (0)
DECL|macro|SIM_END
mdefine_line|#define SIM_END() do { __asm__ volatile (&quot;bmod [%0],%0&quot; :: &quot;r&quot; (28)); } while (0)
DECL|macro|CRIS_CYCLES
mdefine_line|#define CRIS_CYCLES() __extension__ &bslash;&n; ({ unsigned long c; asm (&quot;bmod [%1],%0&quot; : &quot;=r&quot; (c) : &quot;r&quot; (27)); c;})
macro_line|#else  /* ! defined CONFIG_SVINTO_SIM */
multiline_comment|/* FIXME: Is there a reliable cycle counter available in some chip?  Use&n;   that then. */
DECL|macro|CRIS_CYCLES
mdefine_line|#define CRIS_CYCLES() 0
macro_line|#endif /* ! defined CONFIG_SVINTO_SIM */
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
id|port_90000000_shadow
suffix:semicolon
multiline_comment|/* macro for setting regs through a shadow - &n; * r = register name (like R_PORT_PA_DATA)&n; * s = shadow name (like port_pa_data_shadow)&n; * b = bit number&n; * v = value (0 or 1)&n; */
DECL|macro|REG_SHADOW_SET
mdefine_line|#define REG_SHADOW_SET(r,s,b,v) *r = s = (s &amp; ~(1 &lt;&lt; b)) | ((v) &lt;&lt; b) 
multiline_comment|/* The LED&squot;s on various Etrax-based products are set differently. */
macro_line|#if defined(CONFIG_ETRAX_NO_LEDS) || defined(CONFIG_SVINTO_SIM)
DECL|macro|CONFIG_ETRAX_PA_LEDS
macro_line|#undef CONFIG_ETRAX_PA_LEDS
DECL|macro|CONFIG_ETRAX_PB_LEDS
macro_line|#undef CONFIG_ETRAX_PB_LEDS
DECL|macro|CONFIG_ETRAX_90000000_LEDS
macro_line|#undef CONFIG_ETRAX_90000000_LEDS
DECL|macro|LED_NETWORK_RX_SET
mdefine_line|#define LED_NETWORK_RX_SET(x)
DECL|macro|LED_NETWORK_TX_SET
mdefine_line|#define LED_NETWORK_TX_SET(x)
DECL|macro|LED_ACTIVE_SET
mdefine_line|#define LED_ACTIVE_SET(x)
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x)
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x)
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x)
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_PA_LEDS
DECL|macro|LED_NETWORK_RX_SET
mdefine_line|#define LED_NETWORK_RX_SET(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED1G, !x)
DECL|macro|LED_NETWORK_TX_SET
mdefine_line|#define LED_NETWORK_TX_SET(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED1R, !x)
DECL|macro|LED_ACTIVE_SET
mdefine_line|#define LED_ACTIVE_SET(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED2G, !x)
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED2G, !x)
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED2R, !x)
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED3R, !x)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PA_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED3G, !x) 
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_PB_LEDS
DECL|macro|LED_NETWORK_RX_SET
mdefine_line|#define LED_NETWORK_RX_SET(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED1G, !x)
DECL|macro|LED_NETWORK_TX_SET
mdefine_line|#define LED_NETWORK_TX_SET(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED1R, !x)
DECL|macro|LED_ACTIVE_SET
mdefine_line|#define LED_ACTIVE_SET(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED2G, !x)
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED2G, !x)
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pb_data_shadow, CONFIG_ETRAX_LED2R, !x)
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED3R, !x)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x) &bslash;&n;         REG_SHADOW_SET(R_PORT_PB_DATA, port_pa_data_shadow, CONFIG_ETRAX_LED3G, !x)     
macro_line|#endif
macro_line|#ifdef CONFIG_ETRAX_90000000_LEDS
multiline_comment|/* TODO: this won&squot;t work, need a vremap into kernel virtual memory of 90000000 */
DECL|macro|LED_PORT_90
mdefine_line|#define LED_PORT_90 (volatile unsigned long*)0x90000000
DECL|macro|LED_ACTIVE_SET
mdefine_line|#define LED_ACTIVE_SET(x) &bslash;&n;         REG_SHADOW_SET(LED_PORT_90, port_90000000_shadow, CONFIG_ETRAX_LED2G, !x)
DECL|macro|LED_NETWORK_RX_SET
mdefine_line|#define LED_NETWORK_RX_SET(x) &bslash;&n;         REG_SHADOW_SET(LED_PORT_90, port_90000000_shadow, CONFIG_ETRAX_LED1G, !x)
DECL|macro|LED_NETWORK_TX_SET
mdefine_line|#define LED_NETWORK_TX_SET(x) &bslash;&n;         REG_SHADOW_SET(LED_PORT_90, port_90000000_shadow, CONFIG_ETRAX_LED1R, !x)
DECL|macro|LED_ACTIVE_SET_G
mdefine_line|#define LED_ACTIVE_SET_G(x) &bslash;&n;         REG_SHADOW_SET(LED_PORT_90, port_90000000_shadow, CONFIG_ETRAX_LED2G, !x)
DECL|macro|LED_ACTIVE_SET_R
mdefine_line|#define LED_ACTIVE_SET_R(x) &bslash;&n;         REG_SHADOW_SET(LED_PORT_90, port_90000000_shadow, CONFIG_ETRAX_LED2R, !x)
DECL|macro|LED_DISK_WRITE
mdefine_line|#define LED_DISK_WRITE(x) &bslash;&n;         REG_SHADOW_SET(LED_PORT_90, port_90000000_shadow, CONFIG_ETRAX_LED3R, !x)
DECL|macro|LED_DISK_READ
mdefine_line|#define LED_DISK_READ(x) &bslash;&n;         REG_SHADOW_SET(LED_PORT_90, port_90000000_shadow, CONFIG_ETRAX_LED3G, !x)           
macro_line|#endif
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
DECL|function|virt_to_phys
r_static
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|__pa
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_static
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
id|__va
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|function|ioremap
r_extern
r_inline
r_void
op_star
id|ioremap
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|__ioremap
c_func
(paren
id|offset
comma
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IO bus memory addresses are also 1:1 with the physical address&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the CRIS architecture, we just read/write the&n; * memory location directly.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) (addr))
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile unsigned short *) (addr))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile unsigned int *) (addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) ((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) ((*(volatile unsigned short *) (addr)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) ((*(volatile unsigned int *) (addr)) = (b))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
multiline_comment|/*&n; * Again, CRIS does not require mem IO specific function.&n; */
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(a,b,c,d)&t;eth_copy_and_sum((a),(void *)(b),(c),(d))
multiline_comment|/* The following is junk needed for the arch-independant code but which&n; * we never use in the CRIS port&n; */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffff
DECL|macro|inb
mdefine_line|#define inb(x) (0)
DECL|macro|outb
mdefine_line|#define outb(x,y)
DECL|macro|outw
mdefine_line|#define outw(x,y)
DECL|macro|outl
mdefine_line|#define outl(x,y)
DECL|macro|insb
mdefine_line|#define insb(x,y,z)
DECL|macro|insw
mdefine_line|#define insw(x,y,z)
DECL|macro|insl
mdefine_line|#define insl(x,y,z)
DECL|macro|outsb
mdefine_line|#define outsb(x,y,z)
DECL|macro|outsw
mdefine_line|#define outsw(x,y,z)
DECL|macro|outsl
mdefine_line|#define outsl(x,y,z)
macro_line|#endif
eof
