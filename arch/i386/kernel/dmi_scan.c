macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/keyboard.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
DECL|struct|dmi_header
r_struct
id|dmi_header
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|length
id|u8
id|length
suffix:semicolon
DECL|member|handle
id|u16
id|handle
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|dmi_printk
mdefine_line|#define dmi_printk(x)
singleline_comment|//#define dmi_printk(x) printk x
DECL|function|dmi_string
r_static
r_char
op_star
id|__init
id|dmi_string
c_func
(paren
r_struct
id|dmi_header
op_star
id|dm
comma
id|u8
id|s
)paren
(brace
id|u8
op_star
id|bp
op_assign
(paren
id|u8
op_star
)paren
id|dm
suffix:semicolon
id|bp
op_add_assign
id|dm-&gt;length
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s
)paren
(brace
r_return
l_string|&quot;&quot;
suffix:semicolon
)brace
id|s
op_decrement
suffix:semicolon
r_while
c_loop
(paren
id|s
OG
l_int|0
)paren
(brace
id|bp
op_add_assign
id|strlen
c_func
(paren
id|bp
)paren
suffix:semicolon
id|bp
op_increment
suffix:semicolon
id|s
op_decrement
suffix:semicolon
)brace
r_return
id|bp
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;We have to be cautious here. We have seen BIOSes with DMI pointers&n; *&t;pointing to completely the wrong place for example&n; */
DECL|function|dmi_table
r_static
r_int
id|__init
id|dmi_table
c_func
(paren
id|u32
id|base
comma
r_int
id|len
comma
r_int
id|num
comma
r_void
(paren
op_star
id|decode
)paren
(paren
r_struct
id|dmi_header
op_star
)paren
)paren
(brace
id|u8
op_star
id|buf
suffix:semicolon
r_struct
id|dmi_header
op_star
id|dm
suffix:semicolon
id|u8
op_star
id|data
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
id|buf
op_assign
id|ioremap
c_func
(paren
id|base
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|data
op_assign
id|buf
suffix:semicolon
multiline_comment|/*&n; &t; *&t;Stop when we see al the items the table claimed to have&n; &t; *&t;OR we run off the end of the table (also happens)&n; &t; */
r_while
c_loop
(paren
id|i
OL
id|num
op_logical_and
(paren
id|data
op_minus
id|buf
)paren
OL
id|len
)paren
(brace
id|dm
op_assign
(paren
r_struct
id|dmi_header
op_star
)paren
id|data
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Avoid misparsing crud if the length of the last&n;&t; &t; *&t;record is crap &n;&t;&t; */
r_if
c_cond
(paren
(paren
id|data
op_minus
id|buf
op_plus
id|dm-&gt;length
)paren
op_ge
id|len
)paren
(brace
r_break
suffix:semicolon
)brace
id|decode
c_func
(paren
id|dm
)paren
suffix:semicolon
id|data
op_add_assign
id|dm-&gt;length
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Don&squot;t go off the end of the data if there is&n;&t; &t; *&t;stuff looking like string fill past the end&n;&t; &t; */
r_while
c_loop
(paren
(paren
id|data
op_minus
id|buf
)paren
OL
id|len
op_logical_and
(paren
op_star
id|data
op_logical_or
id|data
(braket
l_int|1
)braket
)paren
)paren
(brace
id|data
op_increment
suffix:semicolon
)brace
id|data
op_add_assign
l_int|2
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dmi_iterate
r_int
id|__init
id|dmi_iterate
c_func
(paren
r_void
(paren
op_star
id|decode
)paren
(paren
r_struct
id|dmi_header
op_star
)paren
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|20
)braket
suffix:semicolon
r_int
id|fp
op_assign
l_int|0xE0000L
suffix:semicolon
id|fp
op_sub_assign
l_int|16
suffix:semicolon
macro_line|#ifdef CONFIG_SIMNOW
multiline_comment|/*&n; &t; *&t;Skip on x86/64 with simnow. Will eventually go away&n; &t; *&t;If you see this ifdef in 2.6pre mail me !&n; &t; */
r_return
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|fp
OL
l_int|0xFFFFF
)paren
(brace
id|fp
op_add_assign
l_int|16
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|buf
comma
id|fp
comma
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|buf
comma
l_string|&quot;_DMI_&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
(brace
id|u16
id|num
op_assign
id|buf
(braket
l_int|13
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|12
)braket
suffix:semicolon
id|u16
id|len
op_assign
id|buf
(braket
l_int|7
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|6
)braket
suffix:semicolon
id|u32
id|base
op_assign
id|buf
(braket
l_int|11
)braket
op_lshift
l_int|24
op_or
id|buf
(braket
l_int|10
)braket
op_lshift
l_int|16
op_or
id|buf
(braket
l_int|9
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|8
)braket
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;DMI %d.%d present.&bslash;n&quot;
comma
id|buf
(braket
l_int|14
)braket
op_rshift
l_int|4
comma
id|buf
(braket
l_int|14
)braket
op_amp
l_int|0x0F
)paren
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;%d structures occupying %d bytes.&bslash;n&quot;
comma
id|buf
(braket
l_int|13
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|12
)braket
comma
id|buf
(braket
l_int|7
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|6
)braket
)paren
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;DMI table at 0x%08X.&bslash;n&quot;
comma
id|buf
(braket
l_int|11
)braket
op_lshift
l_int|24
op_or
id|buf
(braket
l_int|10
)braket
op_lshift
l_int|16
op_or
id|buf
(braket
l_int|9
)braket
op_lshift
l_int|8
op_or
id|buf
(braket
l_int|8
)braket
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmi_table
c_func
(paren
id|base
comma
id|len
comma
id|num
comma
id|decode
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_enum
(brace
DECL|enumerator|DMI_BIOS_VENDOR
id|DMI_BIOS_VENDOR
comma
DECL|enumerator|DMI_BIOS_VERSION
id|DMI_BIOS_VERSION
comma
DECL|enumerator|DMI_BIOS_DATE
id|DMI_BIOS_DATE
comma
DECL|enumerator|DMI_SYS_VENDOR
id|DMI_SYS_VENDOR
comma
DECL|enumerator|DMI_PRODUCT_NAME
id|DMI_PRODUCT_NAME
comma
DECL|enumerator|DMI_PRODUCT_VERSION
id|DMI_PRODUCT_VERSION
comma
DECL|enumerator|DMI_BOARD_VENDOR
id|DMI_BOARD_VENDOR
comma
DECL|enumerator|DMI_BOARD_NAME
id|DMI_BOARD_NAME
comma
DECL|enumerator|DMI_BOARD_VERSION
id|DMI_BOARD_VERSION
comma
DECL|enumerator|DMI_STRING_MAX
id|DMI_STRING_MAX
)brace
suffix:semicolon
DECL|variable|dmi_ident
r_static
r_char
op_star
id|dmi_ident
(braket
id|DMI_STRING_MAX
)braket
suffix:semicolon
multiline_comment|/*&n; *&t;Save a DMI string&n; */
DECL|function|dmi_save_ident
r_static
r_void
id|__init
id|dmi_save_ident
c_func
(paren
r_struct
id|dmi_header
op_star
id|dm
comma
r_int
id|slot
comma
r_int
id|string
)paren
(brace
r_char
op_star
id|d
op_assign
(paren
r_char
op_star
)paren
id|dm
suffix:semicolon
r_char
op_star
id|p
op_assign
id|dmi_string
c_func
(paren
id|dm
comma
id|d
(braket
id|string
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
op_logical_or
op_star
id|p
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmi_ident
(braket
id|slot
)braket
)paren
r_return
suffix:semicolon
id|dmi_ident
(braket
id|slot
)braket
op_assign
id|kmalloc
c_func
(paren
id|strlen
c_func
(paren
id|p
)paren
op_plus
l_int|1
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dmi_ident
(braket
id|slot
)braket
)paren
(brace
id|strcpy
c_func
(paren
id|dmi_ident
(braket
id|slot
)braket
comma
id|p
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dmi_save_ident: out of memory.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;DMI callbacks for problem boards&n; */
DECL|struct|dmi_strmatch
r_struct
id|dmi_strmatch
(brace
DECL|member|slot
id|u8
id|slot
suffix:semicolon
DECL|member|substr
r_char
op_star
id|substr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NONE
mdefine_line|#define NONE&t;255
DECL|struct|dmi_blacklist
r_struct
id|dmi_blacklist
(brace
DECL|member|callback
r_int
(paren
op_star
id|callback
)paren
(paren
r_struct
id|dmi_blacklist
op_star
)paren
suffix:semicolon
DECL|member|ident
r_char
op_star
id|ident
suffix:semicolon
DECL|member|matches
r_struct
id|dmi_strmatch
id|matches
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NO_MATCH
mdefine_line|#define NO_MATCH&t;{ NONE, NULL}
DECL|macro|MATCH
mdefine_line|#define MATCH(a,b)&t;{ a, b }
multiline_comment|/*&n; *&t;We have problems with IDE DMA on some platforms. In paticular the&n; *&t;KT7 series. On these it seems the newer BIOS has fixed them. The&n; *&t;rule needs to be improved to match specific BIOS revisions with&n; *&t;corruption problems&n; */
DECL|function|disable_ide_dma
r_static
id|__init
r_int
id|disable_ide_dma
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_IDE
r_extern
r_int
id|noautodma
suffix:semicolon
r_if
c_cond
(paren
id|noautodma
op_eq
l_int|0
)paren
(brace
id|noautodma
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s series board detected. Disabling IDE DMA.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Reboot options and system auto-detection code provided by&n; * Dell Computer Corporation so their systems &quot;just work&quot;. :-)&n; */
multiline_comment|/* &n; * Some machines require the &quot;reboot=b&quot;  commandline option, this quirk makes that automatic.&n; */
DECL|function|set_bios_reboot
r_static
id|__init
r_int
id|set_bios_reboot
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
r_extern
r_int
id|reboot_thru_bios
suffix:semicolon
r_if
c_cond
(paren
id|reboot_thru_bios
op_eq
l_int|0
)paren
(brace
id|reboot_thru_bios
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s series board detected. Selecting BIOS-method for reboots.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Some machines require the &quot;reboot=s&quot;  commandline option, this quirk makes that automatic.&n; */
DECL|function|set_smp_reboot
r_static
id|__init
r_int
id|set_smp_reboot
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_extern
r_int
id|reboot_smp
suffix:semicolon
r_if
c_cond
(paren
id|reboot_smp
op_eq
l_int|0
)paren
(brace
id|reboot_smp
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s series board detected. Selecting SMP-method for reboots.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Some machines require the &quot;reboot=b,s&quot;  commandline option, this quirk makes that automatic.&n; */
DECL|function|set_smp_bios_reboot
r_static
id|__init
r_int
id|set_smp_bios_reboot
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
id|set_smp_reboot
c_func
(paren
id|d
)paren
suffix:semicolon
id|set_bios_reboot
c_func
(paren
id|d
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Some bioses have a broken protected mode poweroff and need to use realmode&n; */
DECL|function|set_realmode_power_off
r_static
id|__init
r_int
id|set_realmode_power_off
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|apm_info.realmode_power_off
op_eq
l_int|0
)paren
(brace
id|apm_info.realmode_power_off
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s bios detected. Using realmode poweroff only.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Some laptops require interrupts to be enabled during APM calls &n; */
DECL|function|set_apm_ints
r_static
id|__init
r_int
id|set_apm_ints
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|apm_info.allow_ints
op_eq
l_int|0
)paren
(brace
id|apm_info.allow_ints
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s machine detected. Enabling interrupts during APM calls.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Some APM bioses corrupt memory or just plain do not work&n; */
DECL|function|apm_is_horked
r_static
id|__init
r_int
id|apm_is_horked
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|apm_info.disabled
op_eq
l_int|0
)paren
(brace
id|apm_info.disabled
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s machine detected. Disabling APM.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Check for clue free BIOS implementations who use&n; *  the following QA technique&n; *&n; *      [ Write BIOS Code ]&lt;------&n; *               |                ^&n; *      &lt; Does it Compile &gt;----N--&n; *               |Y               ^&n; *&t;&lt; Does it Boot Win98 &gt;-N--&n; *               |Y&n; *           [Ship It]&n; *&n; *&t;Phoenix A04  08/24/2000 is known bad (Dell Inspiron 5000e)&n; *&t;Phoenix A07  09/29/2000 is known good (Dell Inspiron 5000)&n; */
DECL|function|broken_apm_power
r_static
id|__init
r_int
id|broken_apm_power
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
id|apm_info.get_power_status_broken
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;BIOS strings suggest APM bugs, disabling power status reporting.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_SONYPI) || defined(CONFIG_SONYPI_MODULE)
multiline_comment|/*&n; * Check for a Sony Vaio system in order to enable the use of&n; * the sonypi driver (we don&squot;t want this driver to be used on&n; * other systems, even if they have the good PCI IDs).&n; *&n; * This one isn&squot;t a bug detect for those who asked, we simply want to&n; * activate Sony specific goodies like the camera and jogdial..&n; */
DECL|variable|is_sony_vaio_laptop
r_int
id|is_sony_vaio_laptop
suffix:semicolon
DECL|function|sony_vaio_laptop
r_static
id|__init
r_int
id|sony_vaio_laptop
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
r_if
c_cond
(paren
id|is_sony_vaio_laptop
op_eq
l_int|0
)paren
(brace
id|is_sony_vaio_laptop
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s laptop detected.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * This bios swaps the APM minute reporting bytes over (Many sony laptops&n; * have this problem).&n; */
DECL|function|swab_apm_power_in_minutes
r_static
id|__init
r_int
id|swab_apm_power_in_minutes
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
id|apm_info.get_power_status_swabinminutes
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;BIOS strings suggest APM reports battery life in minutes and wrong byte order.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The Intel 440GX hall of shame. &n; *&n; * On many (all we have checked) of these boxes the $PIRQ table is wrong.&n; * The MP1.4 table is right however and so SMP kernels tend to work. &n; */
DECL|function|broken_pirq
r_static
id|__init
r_int
id|broken_pirq
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; *** Possibly defective BIOS detected (irqtable)&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; *** Many BIOSes matching this signature have incorrect IRQ routing tables.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; *** If you see IRQ problems, in paticular SCSI resets and hangs at boot&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; *** contact your vendor and ask about updates.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot; *** Building an SMP kernel may evade the bug some of the time.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Some Bioses enable the PS/2 mouse (touchpad) at resume, even if it&n; * was disabled before the suspend. Linux gets terribly confused by that.&n; */
DECL|typedef|pm_kbd_func
r_typedef
r_void
(paren
id|pm_kbd_func
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pm_kbd_func
op_star
id|pm_kbd_request_override
suffix:semicolon
DECL|function|broken_ps2_resume
r_static
id|__init
r_int
id|broken_ps2_resume
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
macro_line|#ifdef CONFIG_VT
r_if
c_cond
(paren
id|pm_kbd_request_override
op_eq
l_int|NULL
)paren
(brace
id|pm_kbd_request_override
op_assign
id|pckbd_pm_resume
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s machine detected. Mousepad Resume Bug workaround enabled.&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Process the DMI blacklists&n; */
multiline_comment|/*&n; *&t;This will be expanded over time to force things like the APM &n; *&t;interrupt mask settings according to the laptop&n; */
DECL|variable|dmi_blacklist
r_static
id|__initdata
r_struct
id|dmi_blacklist
id|dmi_blacklist
(braket
)braket
op_assign
initialization_block
suffix:semicolon
multiline_comment|/*&n; *&t;Walk the blacklist table running matching functions until someone &n; *&t;returns 1 or we hit the end.&n; */
DECL|function|dmi_check_blacklist
r_static
id|__init
r_void
id|dmi_check_blacklist
c_func
(paren
r_void
)paren
(brace
r_struct
id|dmi_blacklist
op_star
id|d
suffix:semicolon
r_int
id|i
suffix:semicolon
id|d
op_assign
op_amp
id|dmi_blacklist
(braket
l_int|0
)braket
suffix:semicolon
r_while
c_loop
(paren
id|d-&gt;callback
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|s
op_assign
id|d-&gt;matches
(braket
id|i
)braket
dot
id|slot
suffix:semicolon
r_if
c_cond
(paren
id|s
op_eq
id|NONE
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmi_ident
(braket
id|s
)braket
op_logical_and
id|strstr
c_func
(paren
id|dmi_ident
(braket
id|s
)braket
comma
id|d-&gt;matches
(braket
id|i
)braket
dot
id|substr
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/* No match */
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d
op_member_access_from_pointer
id|callback
c_func
(paren
id|d
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|fail
suffix:colon
id|d
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Process a DMI table entry. Right now all we care about are the BIOS&n; *&t;and machine entries. For 2.5 we should pull the smbus controller info&n; *&t;out of here.&n; */
DECL|function|dmi_decode
r_static
r_void
id|__init
id|dmi_decode
c_func
(paren
r_struct
id|dmi_header
op_star
id|dm
)paren
(brace
id|u8
op_star
id|data
op_assign
(paren
id|u8
op_star
)paren
id|dm
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_switch
c_cond
(paren
id|dm-&gt;type
)paren
(brace
r_case
l_int|0
suffix:colon
id|p
op_assign
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;BIOS Vendor: %s&bslash;n&quot;
comma
id|p
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_BIOS_VENDOR
comma
l_int|4
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;BIOS Version: %s&bslash;n&quot;
comma
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|5
)braket
)paren
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_BIOS_VERSION
comma
l_int|5
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;BIOS Release: %s&bslash;n&quot;
comma
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|8
)braket
)paren
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_BIOS_DATE
comma
l_int|8
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p
op_assign
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;System Vendor: %s.&bslash;n&quot;
comma
id|p
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_SYS_VENDOR
comma
l_int|4
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Product Name: %s.&bslash;n&quot;
comma
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|5
)braket
)paren
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_PRODUCT_NAME
comma
l_int|5
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Version %s.&bslash;n&quot;
comma
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|6
)braket
)paren
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_PRODUCT_VERSION
comma
l_int|6
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Serial Number %s.&bslash;n&quot;
comma
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|7
)braket
)paren
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p
op_assign
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|4
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
)paren
(brace
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Board Vendor: %s.&bslash;n&quot;
comma
id|p
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_BOARD_VENDOR
comma
l_int|4
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Board Name: %s.&bslash;n&quot;
comma
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|5
)braket
)paren
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_BOARD_NAME
comma
l_int|5
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Board Version: %s.&bslash;n&quot;
comma
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|6
)braket
)paren
)paren
)paren
suffix:semicolon
id|dmi_save_ident
c_func
(paren
id|dm
comma
id|DMI_BOARD_VERSION
comma
l_int|6
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p
op_assign
id|dmi_string
c_func
(paren
id|dm
comma
id|data
(braket
l_int|8
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_logical_and
op_star
id|p
op_ne
l_char|&squot; &squot;
)paren
(brace
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Asset Tag: %s.&bslash;n&quot;
comma
id|p
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
DECL|function|dmi_scan_machine
r_static
r_int
id|__init
id|dmi_scan_machine
c_func
(paren
r_void
)paren
(brace
r_int
id|err
op_assign
id|dmi_iterate
c_func
(paren
id|dmi_decode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_eq
l_int|0
)paren
(brace
id|dmi_check_blacklist
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|variable|dmi_scan_machine
id|module_init
c_func
(paren
id|dmi_scan_machine
)paren
suffix:semicolon
eof
