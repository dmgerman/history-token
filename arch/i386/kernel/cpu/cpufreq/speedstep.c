multiline_comment|/*&n; *  $Id: speedstep.c,v 1.50 2002/09/22 08:16:25 db Exp $&n; *&n; * (C) 2001  Dave Jones, Arjan van de ven.&n; * (C) 2002  Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *  Based upon reverse engineered information, and on Intel documentation&n; *  for chipsets ICH2-M and ICH3-M.&n; *&n; *  Many thanks to Ducrot Bruno for finding and fixing the last&n; *  &quot;missing link&quot; for ICH2-M/ICH3-M support, and to Thomas Winkler &n; *  for extensive testing.&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
multiline_comment|/*********************************************************************&n; *                        SPEEDSTEP - DEFINITIONS                    *&n; *********************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
DECL|variable|speedstep_driver
r_static
r_struct
id|cpufreq_driver
op_star
id|speedstep_driver
suffix:semicolon
multiline_comment|/* speedstep_chipset:&n; *   It is necessary to know which chipset is used. As accesses to &n; * this device occur at various places in this module, we need a &n; * static struct pci_dev * pointing to that device.&n; */
DECL|variable|speedstep_chipset
r_static
r_int
r_int
id|speedstep_chipset
suffix:semicolon
DECL|variable|speedstep_chipset_dev
r_static
r_struct
id|pci_dev
op_star
id|speedstep_chipset_dev
suffix:semicolon
DECL|macro|SPEEDSTEP_CHIPSET_ICH2M
mdefine_line|#define SPEEDSTEP_CHIPSET_ICH2M         0x00000002
DECL|macro|SPEEDSTEP_CHIPSET_ICH3M
mdefine_line|#define SPEEDSTEP_CHIPSET_ICH3M         0x00000003
multiline_comment|/* speedstep_processor&n; */
DECL|variable|speedstep_processor
r_static
r_int
r_int
id|speedstep_processor
suffix:semicolon
DECL|macro|SPEEDSTEP_PROCESSOR_PIII_C
mdefine_line|#define SPEEDSTEP_PROCESSOR_PIII_C      0x00000001  /* Coppermine core */
DECL|macro|SPEEDSTEP_PROCESSOR_PIII_T
mdefine_line|#define SPEEDSTEP_PROCESSOR_PIII_T      0x00000002  /* Tualatin core */
DECL|macro|SPEEDSTEP_PROCESSOR_P4M
mdefine_line|#define SPEEDSTEP_PROCESSOR_P4M         0x00000003  /* P4-M with 100 MHz FSB */
multiline_comment|/* speedstep_[low,high]_freq&n; *   There are only two frequency states for each processor. Values&n; * are in kHz for the time being.&n; */
DECL|variable|speedstep_low_freq
r_static
r_int
r_int
id|speedstep_low_freq
suffix:semicolon
DECL|variable|speedstep_high_freq
r_static
r_int
r_int
id|speedstep_high_freq
suffix:semicolon
DECL|macro|SPEEDSTEP_HIGH
mdefine_line|#define SPEEDSTEP_HIGH                  0x00000000
DECL|macro|SPEEDSTEP_LOW
mdefine_line|#define SPEEDSTEP_LOW                   0x00000001
multiline_comment|/* DEBUG&n; *   Define it if you want verbose debug output, e.g. for bug reporting&n; */
singleline_comment|//#define SPEEDSTEP_DEBUG
macro_line|#ifdef SPEEDSTEP_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0);
macro_line|#endif
multiline_comment|/*********************************************************************&n; *                    LOW LEVEL CHIPSET INTERFACE                    *&n; *********************************************************************/
multiline_comment|/**&n; * speedstep_get_state - read the current SpeedStep state&n; * @state: Speedstep state (SPEEDSTEP_LOW or SPEEDSTEP_HIGH)&n; *&n; *   Tries to read the SpeedStep state. Returns -EIO when there has been&n; * trouble to read the status or write to the control register, -EINVAL&n; * on an unsupported chipset, and zero on success.&n; */
DECL|function|speedstep_get_state
r_static
r_int
id|speedstep_get_state
(paren
r_int
r_int
op_star
id|state
)paren
(brace
id|u32
id|pmbase
suffix:semicolon
id|u8
id|value
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|speedstep_chipset_dev
op_logical_or
op_logical_neg
id|state
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|speedstep_chipset
)paren
(brace
r_case
id|SPEEDSTEP_CHIPSET_ICH2M
suffix:colon
r_case
id|SPEEDSTEP_CHIPSET_ICH3M
suffix:colon
multiline_comment|/* get PMBASE */
id|pci_read_config_dword
c_func
(paren
id|speedstep_chipset_dev
comma
l_int|0x40
comma
op_amp
id|pmbase
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmbase
op_amp
l_int|0x01
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|pmbase
op_and_assign
l_int|0xFFFFFFFE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmbase
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* read state */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|value
op_assign
id|inb
c_func
(paren
id|pmbase
op_plus
l_int|0x50
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: read at pmbase 0x%x + 0x50 returned 0x%x&bslash;n&quot;
comma
id|pmbase
comma
id|value
)paren
suffix:semicolon
op_star
id|state
op_assign
id|value
op_amp
l_int|0x01
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;cpufreq: setting CPU frequency on this chipset unsupported.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_set_state - set the SpeedStep state&n; * @state: new processor frequency state (SPEEDSTEP_LOW or SPEEDSTEP_HIGH)&n; *&n; *   Tries to change the SpeedStep state. &n; */
DECL|function|speedstep_set_state
r_static
r_void
id|speedstep_set_state
(paren
r_int
r_int
id|state
)paren
(brace
id|u32
id|pmbase
suffix:semicolon
id|u8
id|pm2_blk
suffix:semicolon
id|u8
id|value
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|oldstate
suffix:semicolon
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|speedstep_chipset_dev
op_logical_or
(paren
id|state
OG
l_int|0x1
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|speedstep_get_state
c_func
(paren
op_amp
id|oldstate
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|oldstate
op_eq
id|state
)paren
r_return
suffix:semicolon
id|freqs.old
op_assign
(paren
id|oldstate
op_eq
id|SPEEDSTEP_HIGH
)paren
ques
c_cond
id|speedstep_high_freq
suffix:colon
id|speedstep_low_freq
suffix:semicolon
id|freqs
dot
r_new
op_assign
(paren
id|state
op_eq
id|SPEEDSTEP_HIGH
)paren
ques
c_cond
id|speedstep_high_freq
suffix:colon
id|speedstep_low_freq
suffix:semicolon
id|freqs.cpu
op_assign
id|CPUFREQ_ALL_CPUS
suffix:semicolon
multiline_comment|/* speedstep.c is UP only driver */
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|speedstep_chipset
)paren
(brace
r_case
id|SPEEDSTEP_CHIPSET_ICH2M
suffix:colon
r_case
id|SPEEDSTEP_CHIPSET_ICH3M
suffix:colon
multiline_comment|/* get PMBASE */
id|pci_read_config_dword
c_func
(paren
id|speedstep_chipset_dev
comma
l_int|0x40
comma
op_amp
id|pmbase
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pmbase
op_amp
l_int|0x01
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpufreq: could not find speedstep register&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pmbase
op_and_assign
l_int|0xFFFFFFFE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmbase
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;cpufreq: could not find speedstep register&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* read state */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|value
op_assign
id|inb
c_func
(paren
id|pmbase
op_plus
l_int|0x50
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: read at pmbase 0x%x + 0x50 returned 0x%x&bslash;n&quot;
comma
id|pmbase
comma
id|value
)paren
suffix:semicolon
multiline_comment|/* write new state */
id|value
op_and_assign
l_int|0xFE
suffix:semicolon
id|value
op_or_assign
id|state
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: writing 0x%x to pmbase 0x%x + 0x50&bslash;n&quot;
comma
id|value
comma
id|pmbase
)paren
suffix:semicolon
multiline_comment|/* Disable IRQs */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable bus master arbitration */
id|pm2_blk
op_assign
id|inb
c_func
(paren
id|pmbase
op_plus
l_int|0x20
)paren
suffix:semicolon
id|pm2_blk
op_or_assign
l_int|0x01
suffix:semicolon
id|outb
c_func
(paren
id|pm2_blk
comma
(paren
id|pmbase
op_plus
l_int|0x20
)paren
)paren
suffix:semicolon
multiline_comment|/* Actual transition */
id|outb
c_func
(paren
id|value
comma
(paren
id|pmbase
op_plus
l_int|0x50
)paren
)paren
suffix:semicolon
multiline_comment|/* Restore bus master arbitration */
id|pm2_blk
op_and_assign
l_int|0xfe
suffix:semicolon
id|outb
c_func
(paren
id|pm2_blk
comma
(paren
id|pmbase
op_plus
l_int|0x20
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable IRQs */
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* check if transition was sucessful */
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|value
op_assign
id|inb
c_func
(paren
id|pmbase
op_plus
l_int|0x50
)paren
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: read at pmbase 0x%x + 0x50 returned 0x%x&bslash;n&quot;
comma
id|pmbase
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
(paren
id|value
op_amp
l_int|0x1
)paren
)paren
(brace
id|dprintk
(paren
id|KERN_INFO
l_string|&quot;cpufreq: change to %u MHz succeded&bslash;n&quot;
comma
(paren
id|freqs
dot
r_new
op_div
l_int|1000
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;cpufreq: change failed - I/O error&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
id|KERN_ERR
l_string|&quot;cpufreq: setting CPU frequency on this chipset unsupported.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_activate - activate SpeedStep control in the chipset&n; *&n; *   Tries to activate the SpeedStep status and control registers.&n; * Returns -EINVAL on an unsupported chipset, and zero on success.&n; */
DECL|function|speedstep_activate
r_static
r_int
id|speedstep_activate
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|speedstep_chipset_dev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|speedstep_chipset
)paren
(brace
r_case
id|SPEEDSTEP_CHIPSET_ICH2M
suffix:colon
r_case
id|SPEEDSTEP_CHIPSET_ICH3M
suffix:colon
(brace
id|u16
id|value
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|speedstep_chipset_dev
comma
l_int|0x00A0
comma
op_amp
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|value
op_amp
l_int|0x08
)paren
)paren
(brace
id|value
op_or_assign
l_int|0x08
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: activating SpeedStep (TM) registers&bslash;n&quot;
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|speedstep_chipset_dev
comma
l_int|0x00A0
comma
id|value
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;cpufreq: SpeedStep (TM) on this chipset unsupported.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_detect_chipset - detect the Southbridge which contains SpeedStep logic&n; *&n; *   Detects PIIX4, ICH2-M and ICH3-M so far. The pci_dev points to &n; * the LPC bridge / PM module which contains all power-management &n; * functions. Returns the SPEEDSTEP_CHIPSET_-number for the detected&n; * chipset, or zero on failure.&n; */
DECL|function|speedstep_detect_chipset
r_static
r_int
r_int
id|speedstep_detect_chipset
(paren
r_void
)paren
(brace
id|speedstep_chipset_dev
op_assign
id|pci_find_subsys
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801CA_12
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speedstep_chipset_dev
)paren
r_return
id|SPEEDSTEP_CHIPSET_ICH3M
suffix:semicolon
id|speedstep_chipset_dev
op_assign
id|pci_find_subsys
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801BA_10
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|speedstep_chipset_dev
)paren
(brace
multiline_comment|/* speedstep.c causes lockups on Dell Inspirons 8000 and&n;&t;&t; * 8100 which use a pretty old revision of the 82815 &n;&t;&t; * host brige. Abort on these systems.&n;&t;&t; */
r_static
r_struct
id|pci_dev
op_star
id|hostbridge
suffix:semicolon
id|u8
id|rev
op_assign
l_int|0
suffix:semicolon
id|hostbridge
op_assign
id|pci_find_subsys
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82815_MC
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hostbridge
)paren
r_return
id|SPEEDSTEP_CHIPSET_ICH2M
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|hostbridge
comma
id|PCI_REVISION_ID
comma
op_amp
id|rev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rev
OL
l_int|5
)paren
(brace
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: hostbrige does not support speedstep&bslash;n&quot;
)paren
suffix:semicolon
id|speedstep_chipset_dev
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|SPEEDSTEP_CHIPSET_ICH2M
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*********************************************************************&n; *                   LOW LEVEL PROCESSOR INTERFACE                   *&n; *********************************************************************/
multiline_comment|/**&n; * pentium3_get_frequency - get the core frequencies for PIIIs&n; *&n; *   Returns the core frequency of a Pentium III processor (in kHz)&n; */
DECL|function|pentium3_get_frequency
r_static
r_int
r_int
id|pentium3_get_frequency
(paren
r_void
)paren
(brace
multiline_comment|/* See table 14 of p3_ds.pdf and table 22 of 29834003.pdf */
r_struct
(brace
r_int
r_int
id|ratio
suffix:semicolon
multiline_comment|/* Frequency Multiplier (x10) */
id|u8
id|bitmap
suffix:semicolon
multiline_comment|/* power on configuration bits&n;&t;&t;&t;&t;&t;   [27, 25:22] (in MSR 0x2a) */
)brace
id|msr_decode_mult
(braket
)braket
op_assign
(brace
(brace
l_int|30
comma
l_int|0x01
)brace
comma
(brace
l_int|35
comma
l_int|0x05
)brace
comma
(brace
l_int|40
comma
l_int|0x02
)brace
comma
(brace
l_int|45
comma
l_int|0x06
)brace
comma
(brace
l_int|50
comma
l_int|0x00
)brace
comma
(brace
l_int|55
comma
l_int|0x04
)brace
comma
(brace
l_int|60
comma
l_int|0x0b
)brace
comma
(brace
l_int|65
comma
l_int|0x0f
)brace
comma
(brace
l_int|70
comma
l_int|0x09
)brace
comma
(brace
l_int|75
comma
l_int|0x0d
)brace
comma
(brace
l_int|80
comma
l_int|0x0a
)brace
comma
(brace
l_int|85
comma
l_int|0x26
)brace
comma
(brace
l_int|90
comma
l_int|0x20
)brace
comma
(brace
l_int|100
comma
l_int|0x2b
)brace
comma
(brace
l_int|0
comma
l_int|0xff
)brace
multiline_comment|/* error or unknown value */
)brace
suffix:semicolon
multiline_comment|/* PIII(-M) FSB settings: see table b1-b of 24547206.pdf */
r_struct
(brace
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* Front Side Bus speed in MHz */
id|u8
id|bitmap
suffix:semicolon
multiline_comment|/* power on configuration bits [18: 19]&n;&t;&t;&t;&t;&t;   (in MSR 0x2a) */
)brace
id|msr_decode_fsb
(braket
)braket
op_assign
(brace
(brace
l_int|66
comma
l_int|0x0
)brace
comma
(brace
l_int|100
comma
l_int|0x2
)brace
comma
(brace
l_int|133
comma
l_int|0x1
)brace
comma
(brace
l_int|0
comma
l_int|0xff
)brace
)brace
suffix:semicolon
id|u32
id|msr_lo
comma
id|msr_tmp
suffix:semicolon
r_int
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
suffix:semicolon
multiline_comment|/* read MSR 0x2a - we only need the low 32 bits */
id|rdmsr
c_func
(paren
id|MSR_IA32_EBL_CR_POWERON
comma
id|msr_lo
comma
id|msr_tmp
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: P3 - MSR_IA32_EBL_CR_POWERON: 0x%x 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_tmp
)paren
suffix:semicolon
id|msr_tmp
op_assign
id|msr_lo
suffix:semicolon
multiline_comment|/* decode the FSB */
id|msr_tmp
op_and_assign
l_int|0x00c0000
suffix:semicolon
id|msr_tmp
op_rshift_assign
l_int|18
suffix:semicolon
r_while
c_loop
(paren
id|msr_tmp
op_ne
id|msr_decode_fsb
(braket
id|i
)braket
dot
id|bitmap
)paren
(brace
r_if
c_cond
(paren
id|msr_decode_fsb
(braket
id|i
)braket
dot
id|bitmap
op_eq
l_int|0xff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/* decode the multiplier */
r_if
c_cond
(paren
(paren
id|c-&gt;x86_model
op_eq
l_int|0x08
)paren
op_logical_and
(paren
id|c-&gt;x86_mask
op_eq
l_int|0x01
)paren
)paren
multiline_comment|/* different on early Coppermine PIII */
id|msr_lo
op_and_assign
l_int|0x03c00000
suffix:semicolon
r_else
id|msr_lo
op_and_assign
l_int|0x0bc00000
suffix:semicolon
id|msr_lo
op_rshift_assign
l_int|22
suffix:semicolon
r_while
c_loop
(paren
id|msr_lo
op_ne
id|msr_decode_mult
(braket
id|j
)braket
dot
id|bitmap
)paren
(brace
r_if
c_cond
(paren
id|msr_decode_mult
(braket
id|j
)braket
dot
id|bitmap
op_eq
l_int|0xff
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
r_return
(paren
id|msr_decode_mult
(braket
id|j
)braket
dot
id|ratio
op_star
id|msr_decode_fsb
(braket
id|i
)braket
dot
id|value
op_star
l_int|100
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * pentium4_get_frequency - get the core frequency for P4-Ms&n; *&n; *   Should return the core frequency (in kHz) for P4-Ms. &n; */
DECL|function|pentium4_get_frequency
r_static
r_int
r_int
id|pentium4_get_frequency
c_func
(paren
r_void
)paren
(brace
id|u32
id|msr_lo
comma
id|msr_hi
suffix:semicolon
id|rdmsr
c_func
(paren
l_int|0x2c
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: P4 - MSR_EBC_FREQUENCY_ID: 0x%x 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
multiline_comment|/* First 12 bits seem to change a lot (0x511, 0x410 and 0x30f seen &n;&t; * yet). Next 12 bits always seem to be 0x300. If this is not true &n;&t; * on this CPU, complain. Last 8 bits are frequency (in 100MHz).&n;&t; */
r_if
c_cond
(paren
id|msr_hi
op_logical_or
(paren
(paren
id|msr_lo
op_amp
l_int|0x00FFF000
)paren
op_ne
l_int|0x300000
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: P4 - MSR_EBC_FREQUENCY_ID: 0x%x 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: problem in initialization. Please contact Dominik Brodowski&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: &lt;linux@brodo.de&gt; and attach this dmesg. Thanks in advance&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|msr_lo
op_rshift_assign
l_int|24
suffix:semicolon
r_return
(paren
id|msr_lo
op_star
l_int|100000
)paren
suffix:semicolon
)brace
multiline_comment|/** &n; * speedstep_detect_processor - detect Intel SpeedStep-capable processors.&n; *&n; *   Returns the SPEEDSTEP_PROCESSOR_-number for the detected chipset, &n; * or zero on failure.&n; */
DECL|function|speedstep_detect_processor
r_static
r_int
r_int
id|speedstep_detect_processor
(paren
r_void
)paren
(brace
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
id|cpu_data
suffix:semicolon
id|u32
id|ebx
suffix:semicolon
r_if
c_cond
(paren
(paren
id|c-&gt;x86_vendor
op_ne
id|X86_VENDOR_INTEL
)paren
op_logical_or
(paren
(paren
id|c-&gt;x86
op_ne
l_int|6
)paren
op_logical_and
(paren
id|c-&gt;x86
op_ne
l_int|0xF
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86
op_eq
l_int|0xF
)paren
(brace
multiline_comment|/* Intel Pentium 4 Mobile P4-M */
r_if
c_cond
(paren
id|c-&gt;x86_model
op_ne
l_int|2
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;x86_mask
op_ne
l_int|4
)paren
r_return
l_int|0
suffix:semicolon
id|ebx
op_assign
id|cpuid_ebx
c_func
(paren
l_int|0x00000001
)paren
suffix:semicolon
id|ebx
op_and_assign
l_int|0x000000FF
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ebx
op_ne
l_int|0x0e
)paren
op_logical_and
(paren
id|ebx
op_ne
l_int|0x0f
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|SPEEDSTEP_PROCESSOR_P4M
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|c-&gt;x86_model
)paren
(brace
r_case
l_int|0x0B
suffix:colon
multiline_comment|/* Intel PIII [Tualatin] */
multiline_comment|/* cpuid_ebx(1) is 0x04 for desktop PIII, &n;&t;&t;                   0x06 for mobile PIII-M */
id|ebx
op_assign
id|cpuid_ebx
c_func
(paren
l_int|0x00000001
)paren
suffix:semicolon
id|ebx
op_and_assign
l_int|0x000000FF
suffix:semicolon
r_if
c_cond
(paren
id|ebx
op_ne
l_int|0x06
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* So far all PIII-M processors support SpeedStep. See&n;&t;&t; * Intel&squot;s 24540633.pdf of August 2002 &n;&t;&t; */
r_return
id|SPEEDSTEP_PROCESSOR_PIII_T
suffix:semicolon
r_case
l_int|0x08
suffix:colon
multiline_comment|/* Intel PIII [Coppermine] */
multiline_comment|/* based on reverse-engineering information and&n;&t;&t; * some guessing. HANDLE WITH CARE! */
(brace
id|u32
id|msr_lo
comma
id|msr_hi
suffix:semicolon
multiline_comment|/* all mobile PIII Coppermines have FSB 100 MHz&n;&t;&t;&t; * ==&gt; sort out a few desktop PIIIs. */
id|rdmsr
c_func
(paren
id|MSR_IA32_EBL_CR_POWERON
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: Coppermine: MSR_IA32_EBL_Cr_POWERON is 0x%x, 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|msr_lo
op_and_assign
l_int|0x00c0000
suffix:semicolon
r_if
c_cond
(paren
id|msr_lo
op_ne
l_int|0x0080000
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* platform ID seems to be 0x00140000 */
id|rdmsr
c_func
(paren
id|MSR_IA32_PLATFORM_ID
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: Coppermine: MSR_IA32_PLATFORM ID is 0x%x, 0x%x&bslash;n&quot;
comma
id|msr_lo
comma
id|msr_hi
)paren
suffix:semicolon
id|msr_hi
op_assign
id|msr_lo
op_amp
l_int|0x001c0000
suffix:semicolon
r_if
c_cond
(paren
id|msr_hi
op_ne
l_int|0x00140000
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* and these bits seem to be either 00_b, 01_b or&n;&t;&t;&t; * 10_b but never 11_b */
id|msr_lo
op_and_assign
l_int|0x00030000
suffix:semicolon
r_if
c_cond
(paren
id|msr_lo
op_eq
l_int|0x0030000
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* let&squot;s hope this is correct... */
r_return
id|SPEEDSTEP_PROCESSOR_PIII_C
suffix:semicolon
)brace
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*********************************************************************&n; *                        HIGH LEVEL FUNCTIONS                       *&n; *********************************************************************/
multiline_comment|/**&n; * speedstep_detect_speeds - detects low and high CPU frequencies.&n; *&n; *   Detects the low and high CPU frequencies in kHz. Returns 0 on&n; * success or -EINVAL / -EIO on problems. &n; */
DECL|function|speedstep_detect_speeds
r_static
r_int
id|speedstep_detect_speeds
(paren
r_void
)paren
(brace
r_int
r_int
id|state
suffix:semicolon
r_int
r_int
id|low
op_assign
l_int|0
comma
id|high
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|result
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* read the current state */
id|result
op_assign
id|speedstep_get_state
c_func
(paren
op_amp
id|state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* save the correct value, and switch to other */
r_if
c_cond
(paren
id|state
op_eq
id|SPEEDSTEP_LOW
)paren
(brace
r_switch
c_cond
(paren
id|speedstep_processor
)paren
(brace
r_case
id|SPEEDSTEP_PROCESSOR_PIII_C
suffix:colon
r_case
id|SPEEDSTEP_PROCESSOR_PIII_T
suffix:colon
id|low
op_assign
id|pentium3_get_frequency
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEEDSTEP_PROCESSOR_P4M
suffix:colon
id|low
op_assign
id|pentium4_get_frequency
c_func
(paren
)paren
suffix:semicolon
)brace
id|speedstep_set_state
c_func
(paren
id|SPEEDSTEP_HIGH
)paren
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|speedstep_processor
)paren
(brace
r_case
id|SPEEDSTEP_PROCESSOR_PIII_C
suffix:colon
r_case
id|SPEEDSTEP_PROCESSOR_PIII_T
suffix:colon
id|high
op_assign
id|pentium3_get_frequency
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPEEDSTEP_PROCESSOR_P4M
suffix:colon
id|high
op_assign
id|pentium4_get_frequency
c_func
(paren
)paren
suffix:semicolon
)brace
id|speedstep_set_state
c_func
(paren
id|SPEEDSTEP_LOW
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|low
op_logical_or
op_logical_neg
id|high
op_logical_or
(paren
id|speedstep_low_freq
op_eq
id|speedstep_high_freq
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|speedstep_low_freq
op_assign
id|low
suffix:semicolon
id|speedstep_high_freq
op_assign
id|high
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_setpolicy - set a new CPUFreq policy&n; * @policy: new policy&n; *&n; * Sets a new CPUFreq policy.&n; */
DECL|function|speedstep_setpolicy
r_static
r_void
id|speedstep_setpolicy
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|speedstep_driver
op_logical_or
op_logical_neg
id|policy
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|policy-&gt;min
OG
id|speedstep_low_freq
)paren
id|speedstep_set_state
c_func
(paren
id|SPEEDSTEP_HIGH
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
id|policy-&gt;max
OL
id|speedstep_high_freq
)paren
id|speedstep_set_state
c_func
(paren
id|SPEEDSTEP_LOW
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* both frequency states are allowed */
r_if
c_cond
(paren
id|policy-&gt;policy
op_eq
id|CPUFREQ_POLICY_POWERSAVE
)paren
id|speedstep_set_state
c_func
(paren
id|SPEEDSTEP_LOW
)paren
suffix:semicolon
r_else
id|speedstep_set_state
c_func
(paren
id|SPEEDSTEP_HIGH
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/**&n; * speedstep_verify - verifies a new CPUFreq policy&n; * @freq: new policy&n; *&n; * Limit must be within speedstep_low_freq and speedstep_high_freq, with&n; * at least one border included.&n; */
DECL|function|speedstep_verify
r_static
r_void
id|speedstep_verify
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|policy
op_logical_or
op_logical_neg
id|speedstep_driver
op_logical_or
op_logical_neg
id|speedstep_low_freq
op_logical_or
op_logical_neg
id|speedstep_high_freq
)paren
r_return
suffix:semicolon
id|policy-&gt;cpu
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* UP only */
id|cpufreq_verify_within_limits
c_func
(paren
id|policy
comma
id|speedstep_low_freq
comma
id|speedstep_high_freq
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|policy-&gt;min
OG
id|speedstep_low_freq
)paren
op_logical_and
(paren
id|policy-&gt;max
OL
id|speedstep_high_freq
)paren
)paren
id|policy-&gt;max
op_assign
id|speedstep_high_freq
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_init - initializes the SpeedStep CPUFreq driver&n; *&n; *   Initializes the SpeedStep support. Returns -ENODEV on unsupported&n; * devices, -EINVAL on problems during initiatization, and zero on&n; * success.&n; */
DECL|function|speedstep_init
r_static
r_int
id|__init
id|speedstep_init
c_func
(paren
r_void
)paren
(brace
r_int
id|result
suffix:semicolon
r_int
r_int
id|speed
suffix:semicolon
r_struct
id|cpufreq_driver
op_star
id|driver
suffix:semicolon
multiline_comment|/* detect chipset */
id|speedstep_chipset
op_assign
id|speedstep_detect_chipset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* detect chipset */
r_if
c_cond
(paren
id|speedstep_chipset
)paren
id|speedstep_processor
op_assign
id|speedstep_detect_processor
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|speedstep_chipset
)paren
op_logical_or
(paren
op_logical_neg
id|speedstep_processor
)paren
)paren
(brace
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: Intel(R) SpeedStep(TM) for this %s not (yet) available.&bslash;n&quot;
comma
id|speedstep_processor
ques
c_cond
l_string|&quot;chipset&quot;
suffix:colon
l_string|&quot;processor&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: Intel(R) SpeedStep(TM) support $Revision: 1.50 $&bslash;n&quot;
)paren
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;cpufreq: chipset 0x%x - processor 0x%x&bslash;n&quot;
comma
id|speedstep_chipset
comma
id|speedstep_processor
)paren
suffix:semicolon
multiline_comment|/* activate speedstep support */
id|result
op_assign
id|speedstep_activate
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* detect low and high frequency */
id|speedstep_low_freq
op_assign
l_int|100000
suffix:semicolon
id|speedstep_high_freq
op_assign
l_int|200000
suffix:semicolon
id|result
op_assign
id|speedstep_detect_speeds
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
multiline_comment|/* get current speed setting */
id|result
op_assign
id|speedstep_get_state
c_func
(paren
op_amp
id|speed
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|speed
op_assign
(paren
id|speed
op_eq
id|SPEEDSTEP_LOW
)paren
ques
c_cond
id|speedstep_low_freq
suffix:colon
id|speedstep_high_freq
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: currently at %s speed setting - %i MHz&bslash;n&quot;
comma
(paren
id|speed
op_eq
id|speedstep_low_freq
)paren
ques
c_cond
l_string|&quot;low&quot;
suffix:colon
l_string|&quot;high&quot;
comma
(paren
id|speed
op_div
l_int|1000
)paren
)paren
suffix:semicolon
multiline_comment|/* initialization of main &quot;cpufreq&quot; code*/
id|driver
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cpufreq_driver
)paren
op_plus
id|NR_CPUS
op_star
r_sizeof
(paren
r_struct
id|cpufreq_policy
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|driver
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|driver-&gt;policy
op_assign
(paren
r_struct
id|cpufreq_policy
op_star
)paren
(paren
id|driver
op_plus
r_sizeof
(paren
r_struct
id|cpufreq_driver
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
id|driver-&gt;cpu_min_freq
op_assign
id|speedstep_low_freq
suffix:semicolon
id|driver-&gt;cpu_cur_freq
(braket
l_int|0
)braket
op_assign
id|speed
suffix:semicolon
macro_line|#endif
id|driver-&gt;verify
op_assign
op_amp
id|speedstep_verify
suffix:semicolon
id|driver-&gt;setpolicy
op_assign
op_amp
id|speedstep_setpolicy
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|cpu
op_assign
l_int|0
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|min
op_assign
id|speedstep_low_freq
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|max
op_assign
id|speedstep_high_freq
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|max_cpu_freq
op_assign
id|speedstep_high_freq
suffix:semicolon
id|driver-&gt;policy
(braket
l_int|0
)braket
dot
id|policy
op_assign
(paren
id|speed
op_eq
id|speedstep_low_freq
)paren
ques
c_cond
id|CPUFREQ_POLICY_POWERSAVE
suffix:colon
id|CPUFREQ_POLICY_PERFORMANCE
suffix:semicolon
id|result
op_assign
id|cpufreq_register
c_func
(paren
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|kfree
c_func
(paren
id|driver
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
id|speedstep_driver
op_assign
id|driver
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_exit - unregisters SpeedStep support&n; *&n; *   Unregisters SpeedStep support.&n; */
DECL|function|speedstep_exit
r_static
r_void
id|__exit
id|speedstep_exit
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|speedstep_driver
)paren
(brace
id|cpufreq_unregister
c_func
(paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|speedstep_driver
)paren
suffix:semicolon
)brace
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Dave Jones &lt;davej@suse.de&gt;, Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Speedstep driver for Intel mobile processors.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|speedstep_init
id|module_init
c_func
(paren
id|speedstep_init
)paren
suffix:semicolon
DECL|variable|speedstep_exit
id|module_exit
c_func
(paren
id|speedstep_exit
)paren
suffix:semicolon
eof
