multiline_comment|/*&n; * (C) 2001  Dave Jones, Arjan van de ven.&n; * (C) 2002 - 2003  Dominik Brodowski &lt;linux@brodo.de&gt;&n; *&n; *  Licensed under the terms of the GNU GPL License version 2.&n; *  Based upon reverse engineered information, and on Intel documentation&n; *  for chipsets ICH2-M and ICH3-M.&n; *&n; *  Many thanks to Ducrot Bruno for finding and fixing the last&n; *  &quot;missing link&quot; for ICH2-M/ICH3-M support, and to Thomas Winkler&n; *  for extensive testing.&n; *&n; *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*&n; */
multiline_comment|/*********************************************************************&n; *                        SPEEDSTEP - DEFINITIONS                    *&n; *********************************************************************/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;speedstep-lib.h&quot;
multiline_comment|/* speedstep_chipset:&n; *   It is necessary to know which chipset is used. As accesses to&n; * this device occur at various places in this module, we need a&n; * static struct pci_dev * pointing to that device.&n; */
DECL|variable|speedstep_chipset_dev
r_static
r_struct
id|pci_dev
op_star
id|speedstep_chipset_dev
suffix:semicolon
multiline_comment|/* speedstep_processor&n; */
DECL|variable|speedstep_processor
r_static
r_int
r_int
id|speedstep_processor
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *   There are only two frequency states for each processor. Values&n; * are in kHz for the time being.&n; */
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
multiline_comment|/* DEBUG&n; *   Define it if you want verbose debug output, e.g. for bug reporting&n; */
singleline_comment|//#define SPEEDSTEP_DEBUG
macro_line|#ifdef SPEEDSTEP_DEBUG
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) printk(msg)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(msg...) do { } while(0)
macro_line|#endif
multiline_comment|/**&n; * speedstep_set_state - set the SpeedStep state&n; * @state: new processor frequency state (SPEEDSTEP_LOW or SPEEDSTEP_HIGH)&n; *&n; *   Tries to change the SpeedStep state.&n; */
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
id|speedstep_get_processor_frequency
c_func
(paren
id|speedstep_processor
)paren
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
id|u16
id|value
op_assign
l_int|0
suffix:semicolon
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
multiline_comment|/**&n; * speedstep_detect_chipset - detect the Southbridge which contains SpeedStep logic&n; *&n; *   Detects ICH2-M, ICH3-M and ICH4-M so far. The pci_dev points to&n; * the LPC bridge / PM module which contains all power-management&n; * functions. Returns the SPEEDSTEP_CHIPSET_-number for the detected&n; * chipset, or zero on failure.&n; */
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
id|pci_get_subsys
c_func
(paren
id|PCI_VENDOR_ID_INTEL
comma
id|PCI_DEVICE_ID_INTEL_82801DB_12
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
l_int|4
suffix:semicolon
multiline_comment|/* 4-M */
id|speedstep_chipset_dev
op_assign
id|pci_get_subsys
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
l_int|3
suffix:semicolon
multiline_comment|/* 3-M */
id|speedstep_chipset_dev
op_assign
id|pci_get_subsys
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
multiline_comment|/* speedstep.c causes lockups on Dell Inspirons 8000 and&n;&t;&t; * 8100 which use a pretty old revision of the 82815&n;&t;&t; * host brige. Abort on these systems.&n;&t;&t; */
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
id|pci_get_subsys
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
l_int|2
suffix:semicolon
multiline_comment|/* 2-M */
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
id|pci_dev_put
c_func
(paren
id|hostbridge
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pci_dev_put
c_func
(paren
id|hostbridge
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
multiline_comment|/* 2-M */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|_speedstep_get
r_static
r_int
r_int
id|_speedstep_get
c_func
(paren
id|cpumask_t
id|cpus
)paren
(brace
r_int
r_int
id|speed
suffix:semicolon
id|cpumask_t
id|cpus_allowed
suffix:semicolon
id|cpus_allowed
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus
)paren
suffix:semicolon
id|speed
op_assign
id|speedstep_get_processor_frequency
c_func
(paren
id|speedstep_processor
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
)paren
suffix:semicolon
r_return
id|speed
suffix:semicolon
)brace
DECL|function|speedstep_get
r_static
r_int
r_int
id|speedstep_get
c_func
(paren
r_int
r_int
id|cpu
)paren
(brace
r_return
id|_speedstep_get
c_func
(paren
id|cpumask_of_cpu
c_func
(paren
id|cpu
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_target - set a new CPUFreq policy&n; * @policy: new policy&n; * @target_freq: the target frequency&n; * @relation: how that frequency relates to achieved frequency (CPUFREQ_RELATION_L or CPUFREQ_RELATION_H)&n; *&n; * Sets a new CPUFreq policy.&n; */
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
r_struct
id|cpufreq_freqs
id|freqs
suffix:semicolon
id|cpumask_t
id|cpus_allowed
suffix:semicolon
r_int
id|i
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
id|freqs.old
op_assign
id|_speedstep_get
c_func
(paren
id|policy-&gt;cpus
)paren
suffix:semicolon
id|freqs
dot
r_new
op_assign
id|speedstep_freqs
(braket
id|newstate
)braket
dot
id|frequency
suffix:semicolon
id|freqs.cpu
op_assign
id|policy-&gt;cpu
suffix:semicolon
multiline_comment|/* no transition necessary */
r_if
c_cond
(paren
id|freqs.old
op_eq
id|freqs
dot
r_new
)paren
r_return
l_int|0
suffix:semicolon
id|cpus_allowed
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|policy-&gt;cpus
)paren
(brace
id|freqs.cpu
op_assign
id|i
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_PRECHANGE
)paren
suffix:semicolon
)brace
multiline_comment|/* switch to physical CPU where state is to be changed */
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|policy-&gt;cpus
)paren
suffix:semicolon
id|speedstep_set_state
c_func
(paren
id|newstate
)paren
suffix:semicolon
multiline_comment|/* allow to be run on all CPUs */
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
)paren
suffix:semicolon
id|for_each_cpu_mask
c_func
(paren
id|i
comma
id|policy-&gt;cpus
)paren
(brace
id|freqs.cpu
op_assign
id|i
suffix:semicolon
id|cpufreq_notify_transition
c_func
(paren
op_amp
id|freqs
comma
id|CPUFREQ_POSTCHANGE
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; * speedstep_verify - verifies a new CPUFreq policy&n; * @policy: new policy&n; *&n; * Limit must be within speedstep_low_freq and speedstep_high_freq, with&n; * at least one border included.&n; */
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
id|cpumask_t
id|cpus_allowed
suffix:semicolon
multiline_comment|/* only run on CPU to be set, or on its sibling */
macro_line|#ifdef CONFIG_SMP
id|policy-&gt;cpus
op_assign
id|cpu_sibling_map
(braket
id|policy-&gt;cpu
)braket
suffix:semicolon
macro_line|#endif
id|cpus_allowed
op_assign
id|current-&gt;cpus_allowed
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|policy-&gt;cpus
)paren
suffix:semicolon
multiline_comment|/* detect low and high frequency */
id|result
op_assign
id|speedstep_get_freqs
c_func
(paren
id|speedstep_processor
comma
op_amp
id|speedstep_freqs
(braket
id|SPEEDSTEP_LOW
)braket
dot
id|frequency
comma
op_amp
id|speedstep_freqs
(braket
id|SPEEDSTEP_HIGH
)braket
dot
id|frequency
comma
op_amp
id|speedstep_set_state
)paren
suffix:semicolon
id|set_cpus_allowed
c_func
(paren
id|current
comma
id|cpus_allowed
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
id|speed
op_assign
id|_speedstep_get
c_func
(paren
id|policy-&gt;cpus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|speed
)paren
r_return
op_minus
id|EIO
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
id|speedstep_freqs
(braket
id|SPEEDSTEP_LOW
)braket
dot
id|frequency
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
id|policy-&gt;governor
op_assign
id|CPUFREQ_DEFAULT_GOVERNOR
suffix:semicolon
id|policy-&gt;cpuinfo.transition_latency
op_assign
id|CPUFREQ_ETERNAL
suffix:semicolon
id|policy-&gt;cur
op_assign
id|speed
suffix:semicolon
id|result
op_assign
id|cpufreq_frequency_table_cpuinfo
c_func
(paren
id|policy
comma
id|speedstep_freqs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
(paren
id|result
)paren
suffix:semicolon
id|cpufreq_frequency_table_get_attr
c_func
(paren
id|speedstep_freqs
comma
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|speedstep_cpu_exit
r_static
r_int
id|speedstep_cpu_exit
c_func
(paren
r_struct
id|cpufreq_policy
op_star
id|policy
)paren
(brace
id|cpufreq_frequency_table_put_attr
c_func
(paren
id|policy-&gt;cpu
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|speedstep_attr
r_static
r_struct
id|freq_attr
op_star
id|speedstep_attr
(braket
)braket
op_assign
(brace
op_amp
id|cpufreq_freq_attr_scaling_available_freqs
comma
l_int|NULL
comma
)brace
suffix:semicolon
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
l_string|&quot;speedstep-ich&quot;
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
dot
m_exit
op_assign
id|speedstep_cpu_exit
comma
dot
id|get
op_assign
id|speedstep_get
comma
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|attr
op_assign
id|speedstep_attr
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
multiline_comment|/* detect processor */
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
op_logical_neg
id|speedstep_processor
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* detect chipset */
r_if
c_cond
(paren
op_logical_neg
id|speedstep_detect_chipset
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;cpufreq: Intel(R) SpeedStep(TM) for this chipset not (yet) available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* activate speedstep support */
r_if
c_cond
(paren
id|speedstep_activate
c_func
(paren
)paren
)paren
(brace
id|pci_dev_put
c_func
(paren
id|speedstep_chipset_dev
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
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
id|pci_dev_put
c_func
(paren
id|speedstep_chipset_dev
)paren
suffix:semicolon
id|cpufreq_unregister_driver
c_func
(paren
op_amp
id|speedstep_driver
)paren
suffix:semicolon
)brace
id|MODULE_AUTHOR
(paren
l_string|&quot;Dave Jones &lt;davej@codemonkey.org.uk&gt;, Dominik Brodowski &lt;linux@brodo.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
(paren
l_string|&quot;Speedstep driver for Intel mobile processors on chipsets with ICH-M southbridges.&quot;
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
