multiline_comment|/*&n; *  include/asm-ppc/gemini.h&n; *&n; *&n; *  Onboard registers and descriptions for Synergy Microsystems&squot; &n; *  &quot;Gemini&quot; boards.&n; *&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __PPC_GEMINI_H
DECL|macro|__PPC_GEMINI_H
mdefine_line|#define __PPC_GEMINI_H
multiline_comment|/*  Registers  */
DECL|macro|GEMINI_SERIAL_B
mdefine_line|#define GEMINI_SERIAL_B     (0xffeffb00)
DECL|macro|GEMINI_SERIAL_A
mdefine_line|#define GEMINI_SERIAL_A     (0xffeffb08)
DECL|macro|GEMINI_USWITCH
mdefine_line|#define GEMINI_USWITCH      (0xffeffd00)
DECL|macro|GEMINI_BREV
mdefine_line|#define GEMINI_BREV         (0xffeffe00)
DECL|macro|GEMINI_BECO
mdefine_line|#define GEMINI_BECO         (0xffeffe08)
DECL|macro|GEMINI_FEAT
mdefine_line|#define GEMINI_FEAT         (0xffeffe10)
DECL|macro|GEMINI_BSTAT
mdefine_line|#define GEMINI_BSTAT        (0xffeffe18)
DECL|macro|GEMINI_CPUSTAT
mdefine_line|#define GEMINI_CPUSTAT      (0xffeffe20)
DECL|macro|GEMINI_L2CFG
mdefine_line|#define GEMINI_L2CFG        (0xffeffe30)
DECL|macro|GEMINI_MEMCFG
mdefine_line|#define GEMINI_MEMCFG       (0xffeffe38)
DECL|macro|GEMINI_FLROM
mdefine_line|#define GEMINI_FLROM        (0xffeffe40)
DECL|macro|GEMINI_P0PCI
mdefine_line|#define GEMINI_P0PCI        (0xffeffe48)
DECL|macro|GEMINI_FLWIN
mdefine_line|#define GEMINI_FLWIN        (0xffeffe50)
DECL|macro|GEMINI_P0INTMASK
mdefine_line|#define GEMINI_P0INTMASK    (0xffeffe60)
DECL|macro|GEMINI_P0INTAP
mdefine_line|#define GEMINI_P0INTAP      (0xffeffe68)
DECL|macro|GEMINI_PCIERR
mdefine_line|#define GEMINI_PCIERR       (0xffeffe70)
DECL|macro|GEMINI_LEDBASE
mdefine_line|#define GEMINI_LEDBASE      (0xffeffe80)
DECL|macro|GEMINI_RTC
mdefine_line|#define GEMINI_RTC          (0xffe9fff8)
DECL|macro|GEMINI_LEDS
mdefine_line|#define GEMINI_LEDS         8
DECL|macro|GEMINI_SWITCHES
mdefine_line|#define GEMINI_SWITCHES     8
multiline_comment|/* Flash ROM bit definitions */
DECL|macro|GEMINI_FLS_WEN
mdefine_line|#define GEMINI_FLS_WEN      (1&lt;&lt;0)
DECL|macro|GEMINI_FLS_JMP
mdefine_line|#define GEMINI_FLS_JMP      (1&lt;&lt;6)
DECL|macro|GEMINI_FLS_BOOT
mdefine_line|#define GEMINI_FLS_BOOT     (1&lt;&lt;7)
multiline_comment|/* Memory bit definitions */
DECL|macro|GEMINI_MEM_TYPE_MASK
mdefine_line|#define GEMINI_MEM_TYPE_MASK 0xc0
DECL|macro|GEMINI_MEM_SIZE_MASK
mdefine_line|#define GEMINI_MEM_SIZE_MASK 0x38
DECL|macro|GEMINI_MEM_BANK_MASK
mdefine_line|#define GEMINI_MEM_BANK_MASK 0x07
multiline_comment|/* L2 cache bit definitions */
DECL|macro|GEMINI_L2_SIZE_MASK
mdefine_line|#define GEMINI_L2_SIZE_MASK  0xc0
DECL|macro|GEMINI_L2_RATIO_MASK
mdefine_line|#define GEMINI_L2_RATIO_MASK 0x03
multiline_comment|/* Timebase register bit definitons */
DECL|macro|GEMINI_TIMEB0_EN
mdefine_line|#define GEMINI_TIMEB0_EN     (1&lt;&lt;0)
DECL|macro|GEMINI_TIMEB1_EN
mdefine_line|#define GEMINI_TIMEB1_EN     (1&lt;&lt;1)
DECL|macro|GEMINI_TIMEB2_EN
mdefine_line|#define GEMINI_TIMEB2_EN     (1&lt;&lt;2)
DECL|macro|GEMINI_TIMEB3_EN
mdefine_line|#define GEMINI_TIMEB3_EN     (1&lt;&lt;3)
multiline_comment|/* CPU status bit definitions */
DECL|macro|GEMINI_CPU_ID_MASK
mdefine_line|#define GEMINI_CPU_ID_MASK   0x03
DECL|macro|GEMINI_CPU_COUNT_MASK
mdefine_line|#define GEMINI_CPU_COUNT_MASK 0x0c
DECL|macro|GEMINI_CPU0_HALTED
mdefine_line|#define GEMINI_CPU0_HALTED   (1&lt;&lt;4)
DECL|macro|GEMINI_CPU1_HALTED
mdefine_line|#define GEMINI_CPU1_HALTED   (1&lt;&lt;5)
DECL|macro|GEMINI_CPU2_HALTED
mdefine_line|#define GEMINI_CPU2_HALTED   (1&lt;&lt;6)
DECL|macro|GEMINI_CPU3_HALTED
mdefine_line|#define GEMINI_CPU3_HALTED   (1&lt;&lt;7)
multiline_comment|/* Board status bit definitions */
DECL|macro|GEMINI_BRD_FAIL
mdefine_line|#define GEMINI_BRD_FAIL      (1&lt;&lt;0)   /* FAIL led is lit */
DECL|macro|GEMINI_BRD_BUS_MASK
mdefine_line|#define GEMINI_BRD_BUS_MASK  0x0c     /* PowerPC bus speed */
multiline_comment|/* Board family/feature bit descriptions */
DECL|macro|GEMINI_FEAT_HAS_FLASH
mdefine_line|#define GEMINI_FEAT_HAS_FLASH (1&lt;&lt;0)
DECL|macro|GEMINI_FEAT_HAS_ETH
mdefine_line|#define GEMINI_FEAT_HAS_ETH   (1&lt;&lt;1)
DECL|macro|GEMINI_FEAT_HAS_SCSI
mdefine_line|#define GEMINI_FEAT_HAS_SCSI  (1&lt;&lt;2)
DECL|macro|GEMINI_FEAT_HAS_P0
mdefine_line|#define GEMINI_FEAT_HAS_P0    (1&lt;&lt;3)
DECL|macro|GEMINI_FEAT_FAM_MASK
mdefine_line|#define GEMINI_FEAT_FAM_MASK  0xf0
multiline_comment|/* Mod/ECO bit definitions */
DECL|macro|GEMINI_ECO_LEVEL_MASK
mdefine_line|#define GEMINI_ECO_LEVEL_MASK 0x0f
DECL|macro|GEMINI_MOD_MASK
mdefine_line|#define GEMINI_MOD_MASK       0xf0
multiline_comment|/* Type/revision bit definitions */
DECL|macro|GEMINI_REV_MASK
mdefine_line|#define GEMINI_REV_MASK       0x0f
DECL|macro|GEMINI_TYPE_MASK
mdefine_line|#define GEMINI_TYPE_MASK      0xf0
multiline_comment|/* User switch definitions */
DECL|macro|GEMINI_SWITCH_VERBOSE
mdefine_line|#define GEMINI_SWITCH_VERBOSE    1     /* adds &quot;debug&quot; to boot cmd line */
DECL|macro|GEMINI_SWITCH_SINGLE_USER
mdefine_line|#define GEMINI_SWITCH_SINGLE_USER 7    /* boots into &quot;single-user&quot; mode */
DECL|macro|SGS_RTC_CONTROL
mdefine_line|#define SGS_RTC_CONTROL  0
DECL|macro|SGS_RTC_SECONDS
mdefine_line|#define SGS_RTC_SECONDS  1
DECL|macro|SGS_RTC_MINUTES
mdefine_line|#define SGS_RTC_MINUTES  2
DECL|macro|SGS_RTC_HOURS
mdefine_line|#define SGS_RTC_HOURS    3
DECL|macro|SGS_RTC_DAY
mdefine_line|#define SGS_RTC_DAY      4
DECL|macro|SGS_RTC_DAY_OF_MONTH
mdefine_line|#define SGS_RTC_DAY_OF_MONTH 5
DECL|macro|SGS_RTC_MONTH
mdefine_line|#define SGS_RTC_MONTH    6
DECL|macro|SGS_RTC_YEAR
mdefine_line|#define SGS_RTC_YEAR     7
DECL|macro|SGS_RTC_SET
mdefine_line|#define SGS_RTC_SET  0x80
DECL|macro|SGS_RTC_IS_STOPPED
mdefine_line|#define SGS_RTC_IS_STOPPED 0x80
DECL|macro|GRACKLE_CONFIG_ADDR_ADDR
mdefine_line|#define GRACKLE_CONFIG_ADDR_ADDR  (0xfec00000)
DECL|macro|GRACKLE_CONFIG_DATA_ADDR
mdefine_line|#define GRACKLE_CONFIG_DATA_ADDR  (0xfee00000)
DECL|macro|GEMINI_BOOT_INIT
mdefine_line|#define GEMINI_BOOT_INIT  (0xfff00100)
macro_line|#ifndef __ASSEMBLY__
DECL|function|grackle_write
r_static
r_inline
r_void
id|grackle_write
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|data
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot; stwbrx %1, 0, %0&bslash;n &bslash;&n;    sync&bslash;n &bslash;&n;    stwbrx %3, 0, %2&bslash;n &bslash;&n;    sync &quot;
suffix:colon
multiline_comment|/* no output */
suffix:colon
l_string|&quot;r&quot;
(paren
id|GRACKLE_CONFIG_ADDR_ADDR
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|GRACKLE_CONFIG_DATA_ADDR
)paren
comma
l_string|&quot;r&quot;
(paren
id|data
)paren
)paren
suffix:semicolon
)brace
DECL|function|grackle_read
r_static
r_inline
r_int
r_int
id|grackle_read
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot; stwbrx %1, 0, %2&bslash;n &bslash;&n;    sync&bslash;n &bslash;&n;    lwbrx %0, 0, %3&bslash;n &bslash;&n;    sync &quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;r&quot;
(paren
id|GRACKLE_CONFIG_ADDR_ADDR
)paren
comma
l_string|&quot;r&quot;
(paren
id|GRACKLE_CONFIG_DATA_ADDR
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|gemini_led_on
r_static
r_inline
r_void
id|gemini_led_on
c_func
(paren
r_int
id|led
)paren
(brace
r_if
c_cond
(paren
id|led
op_ge
l_int|0
op_logical_and
id|led
OL
id|GEMINI_LEDS
)paren
op_star
(paren
r_int
r_char
op_star
)paren
(paren
id|GEMINI_LEDBASE
op_plus
(paren
id|led
op_lshift
l_int|3
)paren
)paren
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|gemini_led_off
r_static
r_inline
r_void
id|gemini_led_off
c_func
(paren
r_int
id|led
)paren
(brace
r_if
c_cond
(paren
id|led
op_ge
l_int|0
op_logical_and
id|led
OL
id|GEMINI_LEDS
)paren
op_star
(paren
r_int
r_char
op_star
)paren
(paren
id|GEMINI_LEDBASE
op_plus
(paren
id|led
op_lshift
l_int|3
)paren
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|gemini_led_val
r_static
r_inline
r_int
id|gemini_led_val
c_func
(paren
r_int
id|led
)paren
(brace
r_int
id|val
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|led
op_ge
l_int|0
op_logical_and
id|led
OL
id|GEMINI_LEDS
)paren
id|val
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
(paren
id|GEMINI_LEDBASE
op_plus
(paren
id|led
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
r_return
(paren
id|val
op_amp
l_int|0x1
)paren
suffix:semicolon
)brace
multiline_comment|/* returns processor id from the board */
DECL|function|gemini_processor
r_static
r_inline
r_int
id|gemini_processor
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|cpu
op_assign
op_star
(paren
r_int
r_char
op_star
)paren
(paren
id|GEMINI_CPUSTAT
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
(paren
(paren
id|cpu
op_eq
l_int|0
)paren
ques
c_cond
l_int|4
suffix:colon
(paren
id|cpu
op_amp
id|GEMINI_CPU_ID_MASK
)paren
)paren
suffix:semicolon
)brace
r_extern
r_void
id|_gemini_reboot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gemini_prom_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|gemini_init_l2
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
