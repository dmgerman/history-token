multiline_comment|/*&n; *&t;Industrial Computer Source WDT500/501 driver for Linux 1.3.x&n; *&n; *&t;(c) Copyright 1995&t;CymruNET Ltd&n; *&t;&t;&t;&t;Innovation Centre&n; *&t;&t;&t;&t;Singleton Park&n; *&t;&t;&t;&t;Swansea&n; *&t;&t;&t;&t;Wales&n; *&t;&t;&t;&t;UK&n; *&t;&t;&t;&t;SA2 8PP&n; *&n; *&t;http://www.cymru.net&n; *&n; *&t;This driver is provided under the GNU public license, incorporated&n; *&t;herein by reference. The driver is provided without warranty or &n; *&t;support.&n; *&n; *&t;Release 0.04.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|WDT_COUNT0
mdefine_line|#define WDT_COUNT0&t;&t;(io+0)
DECL|macro|WDT_COUNT1
mdefine_line|#define WDT_COUNT1&t;&t;(io+1)
DECL|macro|WDT_COUNT2
mdefine_line|#define WDT_COUNT2&t;&t;(io+2)
DECL|macro|WDT_CR
mdefine_line|#define WDT_CR&t;&t;&t;(io+3)
DECL|macro|WDT_SR
mdefine_line|#define WDT_SR&t;&t;&t;(io+4)&t;/* Start buzzer on PCI write */
DECL|macro|WDT_RT
mdefine_line|#define WDT_RT&t;&t;&t;(io+5)&t;/* Stop buzzer on PCI write */
DECL|macro|WDT_BUZZER
mdefine_line|#define WDT_BUZZER&t;&t;(io+6)&t;/* PCI only: rd=disable, wr=enable */
DECL|macro|WDT_DC
mdefine_line|#define WDT_DC&t;&t;&t;(io+7)
multiline_comment|/* The following are only on the PCI card, they&squot;re outside of I/O space on&n; * the ISA card: */
DECL|macro|WDT_CLOCK
mdefine_line|#define WDT_CLOCK&t;&t;(io+12)&t;/* COUNT2: rd=16.67MHz, wr=2.0833MHz */
multiline_comment|/* inverted opto isolated reset output: */
DECL|macro|WDT_OPTONOTRST
mdefine_line|#define WDT_OPTONOTRST&t;&t;(io+13)&t;/* wr=enable, rd=disable */
multiline_comment|/* opto isolated reset output: */
DECL|macro|WDT_OPTORST
mdefine_line|#define WDT_OPTORST&t;&t;(io+14)&t;/* wr=enable, rd=disable */
multiline_comment|/* programmable outputs: */
DECL|macro|WDT_PROGOUT
mdefine_line|#define WDT_PROGOUT&t;&t;(io+15)&t;/* wr=enable, rd=disable */
DECL|macro|WDC_SR_WCCR
mdefine_line|#define WDC_SR_WCCR&t;&t;1&t;/* Active low */
DECL|macro|WDC_SR_TGOOD
mdefine_line|#define WDC_SR_TGOOD&t;&t;2
DECL|macro|WDC_SR_ISOI0
mdefine_line|#define WDC_SR_ISOI0&t;&t;4
DECL|macro|WDC_SR_ISII1
mdefine_line|#define WDC_SR_ISII1&t;&t;8
DECL|macro|WDC_SR_FANGOOD
mdefine_line|#define WDC_SR_FANGOOD&t;&t;16
DECL|macro|WDC_SR_PSUOVER
mdefine_line|#define WDC_SR_PSUOVER&t;&t;32&t;/* Active low */
DECL|macro|WDC_SR_PSUUNDR
mdefine_line|#define WDC_SR_PSUUNDR&t;&t;64&t;/* Active low */
DECL|macro|WDC_SR_IRQ
mdefine_line|#define WDC_SR_IRQ&t;&t;128&t;/* Active low */
macro_line|#ifndef WDT_IS_PCI
multiline_comment|/*&n; *&t;Feature Map 1 is the active high inputs not supported on your card.&n; *&t;Feature Map 2 is the active low inputs not supported on your card.&n; */
macro_line|#ifdef CONFIG_WDT_501&t;&t;/* Full board */
macro_line|#ifdef CONFIG_WDT501_FAN&t;/* Full board, Fan has no tachometer */
DECL|macro|FEATUREMAP1
mdefine_line|#define FEATUREMAP1&t;&t;0
DECL|macro|WDT_OPTION_MASK
mdefine_line|#define WDT_OPTION_MASK&t;&t;(WDIOF_OVERHEAT|WDIOF_POWERUNDER|WDIOF_POWEROVER|WDIOF_EXTERN1|WDIOF_EXTERN2|WDIOF_FANFAULT)
macro_line|#else
DECL|macro|FEATUREMAP1
mdefine_line|#define FEATUREMAP1&t;&t;WDC_SR_FANGOOD
DECL|macro|WDT_OPTION_MASK
mdefine_line|#define WDT_OPTION_MASK&t;&t;(WDIOF_OVERHEAT|WDIOF_POWERUNDER|WDIOF_POWEROVER|WDIOF_EXTERN1|WDIOF_EXTERN2)
macro_line|#endif
DECL|macro|FEATUREMAP2
mdefine_line|#define FEATUREMAP2&t;&t;0
macro_line|#endif
macro_line|#ifndef CONFIG_WDT_501
DECL|macro|CONFIG_WDT_500
mdefine_line|#define CONFIG_WDT_500
macro_line|#endif
macro_line|#ifdef CONFIG_WDT_500&t;&t;/* Minimal board */
DECL|macro|FEATUREMAP1
mdefine_line|#define FEATUREMAP1&t;&t;(WDC_SR_TGOOD|WDC_SR_FANGOOD)
DECL|macro|FEATUREMAP2
mdefine_line|#define FEATUREMAP2&t;&t;(WDC_SR_PSUOVER|WDC_SR_PSUUNDR)
DECL|macro|WDT_OPTION_MASK
mdefine_line|#define WDT_OPTION_MASK&t;&t;(WDIOF_OVERHEAT)
macro_line|#endif
macro_line|#else
DECL|macro|FEATUREMAP1
mdefine_line|#define FEATUREMAP1&t;&t;(WDC_SR_TGOOD|WDC_SR_FANGOOD)
DECL|macro|FEATUREMAP2
mdefine_line|#define FEATUREMAP2&t;&t;(WDC_SR_PSUOVER|WDC_SR_PSUUNDR)
DECL|macro|WDT_OPTION_MASK
mdefine_line|#define WDT_OPTION_MASK&t;&t;(WDIOF_OVERHEAT)
macro_line|#endif
macro_line|#ifndef FEATUREMAP1
macro_line|#error &quot;Config option not set&quot;
macro_line|#endif
eof
