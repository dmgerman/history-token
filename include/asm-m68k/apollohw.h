multiline_comment|/* apollohw.h : some structures to access apollo HW */
macro_line|#ifndef _ASMm68k_APOLLOHW_H_
DECL|macro|_ASMm68k_APOLLOHW_H_
mdefine_line|#define _ASMm68k_APOLLOHW_H_
multiline_comment|/*&n;   apollo models &n;*/
r_extern
id|u_long
id|apollo_model
suffix:semicolon
DECL|macro|APOLLO_UNKNOWN
mdefine_line|#define APOLLO_UNKNOWN (0)
DECL|macro|APOLLO_DN3000
mdefine_line|#define APOLLO_DN3000 (1)
DECL|macro|APOLLO_DN3010
mdefine_line|#define APOLLO_DN3010 (2)
DECL|macro|APOLLO_DN3500
mdefine_line|#define APOLLO_DN3500 (3)
DECL|macro|APOLLO_DN4000
mdefine_line|#define APOLLO_DN4000 (4)
DECL|macro|APOLLO_DN4500
mdefine_line|#define APOLLO_DN4500 (5)
multiline_comment|/* &n;   see scn2681 data sheet for more info. &n;   member names are read_write.&n;*/
DECL|macro|DECLARE_2681_FIELD
mdefine_line|#define DECLARE_2681_FIELD(x) unsigned char x; unsigned char dummy##x
DECL|struct|SCN2681
r_struct
id|SCN2681
(brace
id|DECLARE_2681_FIELD
c_func
(paren
id|mra
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|sra_csra
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|BRGtest_cra
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|rhra_thra
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|ipcr_acr
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|isr_imr
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|ctu_ctur
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|ctl_ctlr
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|mrb
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|srb_csrb
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|tst_crb
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|rhrb_thrb
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|reserved
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|ip_opcr
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|startCnt_setOutBit
)paren
suffix:semicolon
id|DECLARE_2681_FIELD
c_func
(paren
id|stopCnt_resetOutBit
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if 0
r_struct
id|mc146818
(brace
r_int
r_int
id|second1
suffix:colon
l_int|4
comma
id|second2
suffix:colon
l_int|4
comma
id|alarm_second1
suffix:colon
l_int|4
comma
id|alarm_second2
suffix:colon
l_int|4
comma
id|minute1
suffix:colon
l_int|4
comma
id|minute2
suffix:colon
l_int|4
comma
id|alarm_minute1
suffix:colon
l_int|4
comma
id|alarm_minute2
suffix:colon
l_int|4
suffix:semicolon
r_int
r_int
id|hours1
suffix:colon
l_int|4
comma
id|hours2
suffix:colon
l_int|4
comma
id|alarm_hours1
suffix:colon
l_int|4
comma
id|alarm_hours2
suffix:colon
l_int|4
comma
id|day_of_week1
suffix:colon
l_int|4
comma
id|day_of_week2
suffix:colon
l_int|4
comma
id|day_of_month1
suffix:colon
l_int|4
comma
id|day_of_month2
suffix:colon
l_int|4
suffix:semicolon
r_int
r_int
id|month1
suffix:colon
l_int|4
comma
id|month2
suffix:colon
l_int|4
comma
id|year1
suffix:colon
l_int|4
comma
id|year2
suffix:colon
l_int|4
comma
suffix:colon
l_int|16
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|mc146818
r_struct
id|mc146818
(brace
DECL|member|second
DECL|member|alarm_second
r_int
r_char
id|second
comma
id|alarm_second
suffix:semicolon
DECL|member|minute
DECL|member|alarm_minute
r_int
r_char
id|minute
comma
id|alarm_minute
suffix:semicolon
DECL|member|hours
DECL|member|alarm_hours
r_int
r_char
id|hours
comma
id|alarm_hours
suffix:semicolon
DECL|member|day_of_week
DECL|member|day_of_month
r_int
r_char
id|day_of_week
comma
id|day_of_month
suffix:semicolon
DECL|member|month
DECL|member|year
r_int
r_char
id|month
comma
id|year
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IO_BASE
mdefine_line|#define IO_BASE 0x80000000
r_extern
id|u_long
id|sio01_physaddr
suffix:semicolon
r_extern
id|u_long
id|sio23_physaddr
suffix:semicolon
r_extern
id|u_long
id|rtc_physaddr
suffix:semicolon
r_extern
id|u_long
id|pica_physaddr
suffix:semicolon
r_extern
id|u_long
id|picb_physaddr
suffix:semicolon
r_extern
id|u_long
id|cpuctrl_physaddr
suffix:semicolon
r_extern
id|u_long
id|timer_physaddr
suffix:semicolon
DECL|macro|SAU7_SIO01_PHYSADDR
mdefine_line|#define SAU7_SIO01_PHYSADDR 0x10400
DECL|macro|SAU7_SIO23_PHYSADDR
mdefine_line|#define SAU7_SIO23_PHYSADDR 0x10500
DECL|macro|SAU7_RTC_PHYSADDR
mdefine_line|#define SAU7_RTC_PHYSADDR 0x10900
DECL|macro|SAU7_PICA
mdefine_line|#define SAU7_PICA 0x11000
DECL|macro|SAU7_PICB
mdefine_line|#define SAU7_PICB 0x11100
DECL|macro|SAU7_CPUCTRL
mdefine_line|#define SAU7_CPUCTRL 0x10100
DECL|macro|SAU7_TIMER
mdefine_line|#define SAU7_TIMER 0x010800
DECL|macro|SAU8_SIO01_PHYSADDR
mdefine_line|#define SAU8_SIO01_PHYSADDR 0x8400
DECL|macro|SAU8_RTC_PHYSADDR
mdefine_line|#define SAU8_RTC_PHYSADDR 0x8900
DECL|macro|SAU8_PICA
mdefine_line|#define SAU8_PICA 0x9400
DECL|macro|SAU8_PICB
mdefine_line|#define SAU8_PICB 0x9500
DECL|macro|SAU8_CPUCTRL
mdefine_line|#define SAU8_CPUCTRL 0x8100
DECL|macro|SAU8_TIMER
mdefine_line|#define SAU8_TIMER 0x8800
DECL|macro|sio01
mdefine_line|#define sio01 ((*(volatile struct SCN2681 *)(IO_BASE + sio01_physaddr)))
DECL|macro|sio23
mdefine_line|#define sio23 ((*(volatile struct SCN2681 *)(IO_BASE + sio23_physaddr)))
DECL|macro|rtc
mdefine_line|#define rtc (((volatile struct mc146818 *)(IO_BASE + rtc_physaddr)))
DECL|macro|cpuctrl
mdefine_line|#define cpuctrl (*(volatile unsigned int *)(IO_BASE + cpuctrl_physaddr))
DECL|macro|pica
mdefine_line|#define pica (IO_BASE + pica_physaddr)
DECL|macro|picb
mdefine_line|#define picb (IO_BASE + picb_physaddr)
DECL|macro|timer
mdefine_line|#define timer (IO_BASE + timer_physaddr)&t;
DECL|macro|addr_xlat_map
mdefine_line|#define addr_xlat_map ((unsigned short *)(IO_BASE + 0x17000))
DECL|macro|isaIO2mem
mdefine_line|#define isaIO2mem(x) (((((x) &amp; 0x3f8)  &lt;&lt; 7) | (((x) &amp; 0xfc00) &gt;&gt; 6) | ((x) &amp; 0x7)) + 0x40000 + IO_BASE)
DECL|macro|inb
mdefine_line|#define inb(addr) (*((volatile unsigned char *)(addr)))
DECL|macro|outb
mdefine_line|#define outb(val,addr) (*((volatile unsigned char *)(addr)) = (val))
DECL|macro|inw
mdefine_line|#define inw(addr) (*((volatile unsigned short *)(addr)))
DECL|macro|outw
mdefine_line|#define outw(val,addr) (*((volatile unsigned short *)(addr)) = (val))
macro_line|#endif
eof
