multiline_comment|/*&n; *  $Id: speedstep.c,v 1.68 2003/01/20 17:31:47 db Exp $&n; *&n; * (C) 2001  Dave Jones, Arjan van de ven.&n; * (C) 2002 - 2003  Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *  Based upon reverse engineered information, and on Intel documentation&n; *  for chipsets ICH2-M and ICH3-M.&n; *&n; *  Many thanks to Ducrot Bruno for finding and fixing the last&n; *  &quot;missing link&quot; for ICH2-M/ICH3-M support, and to Thomas Winkler &n; *  for extensive testing.&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
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
op_assign
l_int|0
suffix:semicolon
DECL|variable|speedstep_coppermine
r_static
r_int
id|speedstep_coppermine
op_assign
l_int|0
suffix:semicolon
DECL|macro|SPEEDSTEP_PROCESSOR_PIII_C
mdefine_line|#define SPEEDSTEP_PROCESSOR_PIII_C      0x00000001  /* Coppermine core */
DECL|macro|SPEEDSTEP_PROCESSOR_PIII_T
mdefine_line|#define SPEEDSTEP_PROCESSOR_PIII_T      0x00000002  /* Tualatin core */
DECL|macro|SPEEDSTEP_PROCESSOR_P4M
mdefine_line|#define SPEEDSTEP_PROCESSOR_P4M         0x00000003  /* P4-M with 100 MHz FSB */
multiline_comment|/* speedstep_[low,high]_freq&n; *   There are only two frequency states for each processor. Values&n; * are in kHz for the time being.&n; */
DECL|macro|SPEEDSTEP_HIGH
mdefine_line|#define SPEEDSTEP_HIGH                  0x00000000
DECL|macro|SPEEDSTEP_LOW
mdefine_line|#define SPEEDSTEP_LOW                   0x00000001
DECL|variable|speedstep_freqs
r_static
r_struct
id|cpufreq_frequency_table
id|speedstep_freqs
(braket
)braket
op_assign
(brace
(brace
id|SPEEDSTEP_HIGH
comma
l_int|0
)brace
comma
(brace
id|SPEEDSTEP_LOW
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
id|CPUFREQ_TABLE_END
)brace
comma
)brace
suffix:semicolon
DECL|macro|speedstep_low_freq
mdefine_line|#define speedstep_low_freq&t;speedstep_freqs[SPEEDSTEP_LOW].frequency
DECL|macro|speedstep_high_freq
mdefine_line|#define speedstep_high_freq&t;speedstep_freqs[SPEEDSTEP_HIGH].frequency
multiline_comment|/* DEBUG&n; *   Define it if you want verbose debug output, e.g. for bug reporting&n; */
singleline_comment|//#define SPEEDSTEP_DEBUG
macro_line|#ifdef SPEEDSTEP_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
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
r_int
r_int
id|flags
suffix:semicolon
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
id|local_irq_save
c_func
(paren
id|flags
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
id|local_irq_restore
c_func
(paren
id|flags
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
comma
r_int
id|notify
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
l_int|0
suffix:semicolon
multiline_comment|/* speedstep.c is UP only driver */
r_if
c_cond
(paren
id|notify
)paren
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
multiline_comment|/* Disable IRQs */
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* read state */
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
multiline_comment|/* check if transition was successful */
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
multiline_comment|/* Enable IRQs */
id|local_irq_restore
c_func
(paren
id|flags
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
l_string|&quot;cpufreq: change to %u MHz succeeded&bslash;n&quot;
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
r_if
c_cond
(paren
id|notify
)paren
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
l_string|&quot;cpufreq: hostbridge does not support speedstep&bslash;n&quot;
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
multiline_comment|/** &n; * speedstep_detect_processor - detect Intel SpeedStep-capable processors.&n; *&n; *   Returns the SPEEDSTEP_PROCESSOR_-number for the detected processor, &n; * or zero on failure.&n; */
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
(paren
id|c-&gt;x86_mask
op_ne
l_int|4
)paren
op_logical_and
(paren
id|c-&gt;x86_mask
op_ne
l_int|7
)paren
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
r_if
c_cond
(paren
id|speedstep_coppermine
)paren
r_return
id|SPEEDSTEP_PROCESSOR_PIII_C
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: in case this is a SpeedStep-capable Intel Pentium III Coppermine&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: processor, please pass the boot option or module parameter&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: `speedstep_coppermine=1` to the kernel. Thanks!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
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
id|flags
suffix:semicolon
r_int
r_int
id|state
suffix:semicolon
r_int
id|i
comma
id|result
suffix:semicolon
multiline_comment|/* Disable irqs for entire detection process */
id|local_irq_save
c_func
(paren
id|flags
)paren
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
id|speedstep_low_freq
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
id|speedstep_low_freq
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
comma
l_int|0
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
id|speedstep_high_freq
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
id|speedstep_high_freq
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
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|speedstep_low_freq
op_logical_or
op_logical_neg
id|speedstep_high_freq
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_setpolicy - set a new CPUFreq policy&n; * @policy: new policy&n; *&n; * Sets a new CPUFreq policy.&n; */
DECL|function|speedstep_target
r_static
r_int
id|speedstep_target
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
comma
r_int
r_int
id|target_freq
comma
r_int
r_int
id|relation
)paren
(brace
r_int
r_int
id|newstate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cpufreq_frequency_table_target
c_func
(paren
id|policy
comma
op_amp
id|speedstep_freqs
(braket
l_int|0
)braket
comma
id|target_freq
comma
id|relation
comma
op_amp
id|newstate
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|speedstep_set_state
c_func
(paren
id|newstate
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_verify - verifies a new CPUFreq policy&n; * @freq: new policy&n; *&n; * Limit must be within speedstep_low_freq and speedstep_high_freq, with&n; * at least one border included.&n; */
DECL|function|speedstep_verify
r_static
r_int
id|speedstep_verify
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_return
id|cpufreq_frequency_table_verify
c_func
(paren
id|policy
comma
op_amp
id|speedstep_freqs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
DECL|function|speedstep_cpu_init
r_static
r_int
id|speedstep_cpu_init
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|speed
suffix:semicolon
multiline_comment|/* capability check */
r_if
c_cond
(paren
id|policy-&gt;cpu
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* detect low and high frequency */
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
multiline_comment|/* cpuinfo and default policy values */
id|policy-&gt;policy
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
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_FREQ_24_API
id|speedstep_driver.cpu_cur_freq
(braket
id|policy-&gt;cpu
)braket
op_assign
id|speed
suffix:semicolon
macro_line|#endif
r_return
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
op_amp
id|speedstep_freqs
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
macro_line|#ifndef MODULE
multiline_comment|/**&n; * speedstep_setup  speedstep command line parameter parsing&n; *&n; * speedstep command line parameter.  Use:&n; *  speedstep_coppermine=1&n; * if the CPU in your notebook is a SpeedStep-capable Intel&n; * Pentium III Coppermine. These processors cannot be detected&n; * automatically, as Intel continues to consider the detection &n; * algorithm as proprietary material.&n; */
DECL|function|speedstep_setup
r_static
r_int
id|__init
id|speedstep_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|speedstep_coppermine
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|str
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;speedstep_coppermine=&quot;
comma
id|speedstep_setup
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|speedstep_driver
r_static
r_struct
id|cpufreq_driver
id|speedstep_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;speedstep&quot;
comma
dot
id|verify
op_assign
id|speedstep_verify
comma
dot
id|target
op_assign
id|speedstep_target
comma
dot
id|init
op_assign
id|speedstep_cpu_init
comma
)brace
suffix:semicolon
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
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: Intel(R) SpeedStep(TM) for this %s not (yet) available.&bslash;n&quot;
comma
id|speedstep_chipset
ques
c_cond
l_string|&quot;processor&quot;
suffix:colon
l_string|&quot;chipset&quot;
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
l_string|&quot;cpufreq: Intel(R) SpeedStep(TM) support $Revision: 1.68 $&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* activate speedstep support */
r_if
c_cond
(paren
id|speedstep_activate
c_func
(paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|cpufreq_register_driver
c_func
(paren
op_amp
id|speedstep_driver
)paren
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
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|speedstep_driver
)paren
suffix:semicolon
)brace
id|MODULE_PARM
(paren
id|speedstep_coppermine
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
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
