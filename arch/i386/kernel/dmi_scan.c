macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/acpi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/dmi.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
DECL|variable|dmi_broken
r_int
r_int
id|dmi_broken
suffix:semicolon
DECL|variable|dmi_broken
id|EXPORT_SYMBOL
c_func
(paren
id|dmi_broken
)paren
suffix:semicolon
DECL|variable|es7000_plat
r_int
id|es7000_plat
op_assign
l_int|0
suffix:semicolon
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
DECL|macro|DMI_DEBUG
macro_line|#undef DMI_DEBUG
macro_line|#ifdef DMI_DEBUG
DECL|macro|dmi_printk
mdefine_line|#define dmi_printk(x) printk x
macro_line|#else
DECL|macro|dmi_printk
mdefine_line|#define dmi_printk(x)
macro_line|#endif
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
op_logical_and
op_star
id|bp
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
l_int|0
suffix:semicolon
id|buf
op_assign
id|bt_ioremap
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
multiline_comment|/*&n; &t; *&t;Stop when we see all the items the table claimed to have&n; &t; *&t;OR we run off the end of the table (also happens)&n; &t; */
r_while
c_loop
(paren
id|i
OL
id|num
op_logical_and
id|data
op_minus
id|buf
op_plus
r_sizeof
(paren
r_struct
id|dmi_header
)paren
op_le
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
multiline_comment|/*&n;&t;&t; *  We want to know the total length (formated area and strings)&n;&t;&t; *  before decoding to make sure we won&squot;t run off the table in&n;&t;&t; *  dmi_decode or dmi_string&n;&t;&t; */
id|data
op_add_assign
id|dm-&gt;length
suffix:semicolon
r_while
c_loop
(paren
id|data
op_minus
id|buf
OL
id|len
op_minus
l_int|1
op_logical_and
(paren
id|data
(braket
l_int|0
)braket
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
r_if
c_cond
(paren
id|data
op_minus
id|buf
OL
id|len
op_minus
l_int|1
)paren
(brace
id|decode
c_func
(paren
id|dm
)paren
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
id|bt_iounmap
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dmi_checksum
r_inline
r_static
r_int
id|__init
id|dmi_checksum
c_func
(paren
id|u8
op_star
id|buf
)paren
(brace
id|u8
id|sum
op_assign
l_int|0
suffix:semicolon
r_int
id|a
suffix:semicolon
r_for
c_loop
(paren
id|a
op_assign
l_int|0
suffix:semicolon
id|a
OL
l_int|15
suffix:semicolon
id|a
op_increment
)paren
(brace
id|sum
op_add_assign
id|buf
(braket
id|a
)braket
suffix:semicolon
)brace
r_return
(paren
id|sum
op_eq
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|dmi_iterate
r_static
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
id|u8
id|buf
(braket
l_int|15
)braket
suffix:semicolon
id|u32
id|fp
op_assign
l_int|0xF0000
suffix:semicolon
r_while
c_loop
(paren
id|fp
OL
l_int|0xFFFFF
)paren
(brace
id|isa_memcpy_fromio
c_func
(paren
id|buf
comma
id|fp
comma
l_int|15
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
op_logical_and
id|dmi_checksum
c_func
(paren
id|buf
)paren
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
multiline_comment|/*&n;&t;&t;&t; * DMI version 0.0 means that the real version is taken from&n;&t;&t;&t; * the SMBIOS version, which we don&squot;t know at this point.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|buf
(braket
l_int|14
)braket
op_ne
l_int|0
)paren
(brace
id|printk
c_func
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
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;DMI present.&bslash;n&quot;
)paren
suffix:semicolon
id|dmi_printk
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;%d structures occupying %d bytes.&bslash;n&quot;
comma
id|num
comma
id|len
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
id|base
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
id|fp
op_add_assign
l_int|16
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
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
id|alloc_bootmem
c_func
(paren
id|strlen
c_func
(paren
id|p
)paren
op_plus
l_int|1
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
multiline_comment|/*&n; * Ugly compatibility crap.&n; */
DECL|macro|dmi_blacklist
mdefine_line|#define dmi_blacklist&t;dmi_system_id
DECL|macro|NO_MATCH
mdefine_line|#define NO_MATCH&t;{ DMI_NONE, NULL}
DECL|macro|MATCH
mdefine_line|#define MATCH&t;&t;DMI_MATCH
multiline_comment|/*&n; * Some machines, usually laptops, can&squot;t handle an enabled local APIC.&n; * The symptoms include hangs or reboots when suspending or resuming,&n; * attaching or detaching the power cord, or entering BIOS setup screens&n; * through magic key sequences.&n; */
DECL|function|local_apic_kills_bios
r_static
r_int
id|__init
id|local_apic_kills_bios
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
r_extern
r_int
id|enable_local_apic
suffix:semicolon
r_if
c_cond
(paren
id|enable_local_apic
op_eq
l_int|0
)paren
(brace
id|enable_local_apic
op_assign
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s with broken BIOS detected. &quot;
l_string|&quot;Refusing to enable the local APIC.&bslash;n&quot;
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
multiline_comment|/*&n; * Toshiba keyboard likes to repeat keys when they are not repeated.&n; */
DECL|function|broken_toshiba_keyboard
r_static
id|__init
r_int
id|broken_toshiba_keyboard
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
id|KERN_WARNING
l_string|&quot;Toshiba with broken keyboard detected. If your keyboard sometimes generates 3 keypresses instead of one, see http://davyd.ucc.asn.au/projects/toshiba/README&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Toshiba fails to preserve interrupts over S1&n; */
DECL|function|init_ints_after_s1
r_static
id|__init
r_int
id|init_ints_after_s1
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
id|KERN_WARNING
l_string|&quot;Toshiba with broken S1 detected.&bslash;n&quot;
)paren
suffix:semicolon
id|dmi_broken
op_or_assign
id|BROKEN_INIT_AFTER_S1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_SLEEP
DECL|function|reset_videomode_after_s3
r_static
id|__init
r_int
id|reset_videomode_after_s3
c_func
(paren
r_struct
id|dmi_blacklist
op_star
id|d
)paren
(brace
multiline_comment|/* See acpi_wakeup.S */
r_extern
r_int
id|acpi_video_flags
suffix:semicolon
id|acpi_video_flags
op_or_assign
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef&t;CONFIG_ACPI_BOOT
r_extern
r_int
id|acpi_force
suffix:semicolon
DECL|function|dmi_disable_acpi
r_static
id|__init
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
r_int
id|dmi_disable_acpi
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
op_logical_neg
id|acpi_force
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s detected: acpi off&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
id|disable_acpi
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Warning: DMI blacklist says broken, but acpi forced&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Limit ACPI to CPU enumeration for HT&n; */
DECL|function|force_acpi_ht
r_static
id|__init
id|__attribute__
c_func
(paren
(paren
id|unused
)paren
)paren
r_int
id|force_acpi_ht
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
op_logical_neg
id|acpi_force
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s detected: force use of acpi=ht&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
id|disable_acpi
c_func
(paren
)paren
suffix:semicolon
id|acpi_ht
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;Warning: acpi=force overrules DMI blacklist: acpi=ht&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * early nForce2 reference BIOS shipped with a&n; * bogus ACPI IRQ0 -&gt; pin2 interrupt override -- ignore it&n; */
DECL|function|ignore_timer_override
r_static
id|__init
r_int
id|ignore_timer_override
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
id|acpi_skip_timer_override
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s detected: BIOS IRQ0 pin2 override&quot;
l_string|&quot; will be ignored&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
id|acpi_skip_timer_override
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef&t;CONFIG_ACPI_PCI
DECL|function|disable_acpi_irq
r_static
id|__init
r_int
id|disable_acpi_irq
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
op_logical_neg
id|acpi_force
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s detected: force use of acpi=noirq&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
id|acpi_noirq_set
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disable_acpi_pci
r_static
id|__init
r_int
id|disable_acpi_pci
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
op_logical_neg
id|acpi_force
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;%s detected: force use of pci=noacpi&bslash;n&quot;
comma
id|d-&gt;ident
)paren
suffix:semicolon
id|acpi_disable_pci
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
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
macro_line|#ifdef&t;CONFIG_ACPI_BOOT
DECL|macro|ACPI_BLACKLIST_CUTOFF_YEAR
mdefine_line|#define&t;ACPI_BLACKLIST_CUTOFF_YEAR&t;2001
r_if
c_cond
(paren
id|dmi_ident
(braket
id|DMI_BIOS_DATE
)braket
)paren
(brace
r_char
op_star
id|s
op_assign
id|strrchr
c_func
(paren
id|dmi_ident
(braket
id|DMI_BIOS_DATE
)braket
comma
l_char|&squot;/&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
(brace
r_int
id|year
comma
id|disable
op_assign
l_int|0
suffix:semicolon
id|s
op_increment
suffix:semicolon
id|year
op_assign
id|simple_strtoul
c_func
(paren
id|s
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|year
op_ge
l_int|1000
)paren
id|disable
op_assign
id|year
OL
id|ACPI_BLACKLIST_CUTOFF_YEAR
suffix:semicolon
r_else
r_if
c_cond
(paren
id|year
OL
l_int|1
op_logical_or
(paren
id|year
OG
l_int|90
op_logical_and
id|year
op_le
l_int|99
)paren
)paren
id|disable
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|disable
op_logical_and
op_logical_neg
id|acpi_force
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;ACPI disabled because your bios is from %s and too old&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;You can enable it with acpi=force&bslash;n&quot;
)paren
suffix:semicolon
id|disable_acpi
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif
id|dmi_check_system
c_func
(paren
id|dmi_blacklist
)paren
suffix:semicolon
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
macro_line|#ifdef DMI_DEBUG
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
macro_line|#endif
r_switch
c_cond
(paren
id|dm-&gt;type
)paren
(brace
r_case
l_int|0
suffix:colon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;BIOS Vendor: %s&bslash;n&quot;
comma
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
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;System Vendor: %s&bslash;n&quot;
comma
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
l_string|&quot;Product Name: %s&bslash;n&quot;
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
l_string|&quot;Version: %s&bslash;n&quot;
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
l_string|&quot;Serial Number: %s&bslash;n&quot;
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
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|dmi_printk
c_func
(paren
(paren
l_string|&quot;Board Vendor: %s&bslash;n&quot;
comma
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
l_string|&quot;Board Name: %s&bslash;n&quot;
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
l_string|&quot;Board Version: %s&bslash;n&quot;
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
r_break
suffix:semicolon
)brace
)brace
DECL|function|dmi_scan_machine
r_void
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
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;DMI not present.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;dmi_check_system - check system DMI data&n; *&t;@list: array of dmi_system_id structures to match against&n; *&n; *&t;Walk the blacklist table running matching functions until someone&n; *&t;returns non zero or we hit the end. Callback function is called for&n; *&t;each successfull match. Returns the number of matches.&n; */
DECL|function|dmi_check_system
r_int
id|dmi_check_system
c_func
(paren
r_struct
id|dmi_system_id
op_star
id|list
)paren
(brace
r_int
id|i
comma
id|count
op_assign
l_int|0
suffix:semicolon
r_struct
id|dmi_system_id
op_star
id|d
op_assign
id|list
suffix:semicolon
r_while
c_loop
(paren
id|d-&gt;ident
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
id|ARRAY_SIZE
c_func
(paren
id|d-&gt;matches
)paren
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
id|DMI_NONE
)paren
r_continue
suffix:semicolon
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
r_continue
suffix:semicolon
multiline_comment|/* No match */
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d-&gt;callback
op_logical_and
id|d
op_member_access_from_pointer
id|callback
c_func
(paren
id|d
)paren
)paren
r_break
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|fail
suffix:colon
id|d
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|variable|dmi_check_system
id|EXPORT_SYMBOL
c_func
(paren
id|dmi_check_system
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;dmi_get_system_info - return DMI data value&n; *&t;@field: data index (see enum dmi_filed)&n; *&n; *&t;Returns one DMI data value, can be used to perform&n; *&t;complex DMI data checks.&n; */
DECL|function|dmi_get_system_info
r_char
op_star
id|dmi_get_system_info
c_func
(paren
r_int
id|field
)paren
(brace
r_return
id|dmi_ident
(braket
id|field
)braket
suffix:semicolon
)brace
DECL|variable|dmi_get_system_info
id|EXPORT_SYMBOL
c_func
(paren
id|dmi_get_system_info
)paren
suffix:semicolon
eof
