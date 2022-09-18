/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2021 MediaTek Inc.
 */

#ifndef __MFD_MT6368_CORE_H__
#define __MFD_MT6368_CORE_H__

#define MT6368_REG_WIDTH 8

enum mt6368_irq_top_status_shift {
	MT6368_BUCK_TOP = 0,
	MT6368_LDO_TOP,
	MT6368_PSC_TOP,
	MT6368_MISC_TOP,
	MT6368_HK_TOP,
	MT6368_SCK_TOP,
	MT6368_BM_TOP,
	MT6368_AUD_TOP,
};

enum mt6368_irq_numbers {
	MT6368_IRQ_VBUCK1_OC,
	MT6368_IRQ_VBUCK2_OC,
	MT6368_IRQ_VBUCK3_OC,
	MT6368_IRQ_VBUCK4_OC,
	MT6368_IRQ_VBUCK5_OC,
	MT6368_IRQ_VBUCK6_OC,
	MT6368_IRQ_VPA_OC,
	MT6368_IRQ_VSIM1_OC = 8,
	MT6368_IRQ_VSIM2_OC,
	MT6368_IRQ_VMDDR_OC,
	MT6368_IRQ_VMDDQ_OC,
	MT6368_IRQ_VUSB_OC,
	MT6368_IRQ_VAUX18_OC,
	MT6368_IRQ_VRF13_AIF_OC,
	MT6368_IRQ_VRF18_AIF_OC,
	MT6368_IRQ_VANT18_OC,
	MT6368_IRQ_VIBR_OC,
	MT6368_IRQ_VIO28_OC,
	MT6368_IRQ_VFP_OC,
	MT6368_IRQ_VTP_OC,
	MT6368_IRQ_VMCH_OC,
	MT6368_IRQ_VMC_OC,
	MT6368_IRQ_VAUD18_OC,
	MT6368_IRQ_VCN33_1_OC,
	MT6368_IRQ_VCN33_2_OC,
	MT6368_IRQ_VEFUSE_OC,
	MT6368_IRQ_RCS0 = 48,
	MT6368_IRQ_SPMI_CMD_ALERT,
	MT6368_IRQ_SPMI_P_CMD_ALERT,
	MT6368_IRQ_BM_PROTREG = 54,
	MT6368_IRQ_VRC_PROTREG,
	MT6368_IRQ_BUCK_PROTREG,
	MT6368_IRQ_LDO_PROTREG,
	MT6368_IRQ_PSC_PROTREG,
	MT6368_IRQ_PLT_PROTREG,
	MT6368_IRQ_HK_PROTREG,
	MT6368_IRQ_SCK_PROTREG,
	MT6368_IRQ_XPP_PROTREG,
	MT6368_IRQ_TOP_PROTREG,
	MT6368_IRQ_AUDIO = 96,
	MT6368_IRQ_ACCDET,
	MT6368_IRQ_ACCDET_EINT0,
	MT6368_IRQ_ACCDET_EINT1,
	MT6368_IRQ_NR = 100,
};

#define MT6368_IRQ_BUCK_BASE MT6368_IRQ_VBUCK1_OC
#define MT6368_IRQ_LDO_BASE MT6368_IRQ_VSIM1_OC
#define MT6368_IRQ_MISC_BASE MT6368_IRQ_RCS0
#define MT6368_IRQ_AUD_BASE MT6368_IRQ_AUDIO

#define MT6368_IRQ_BUCK_BITS \
	(MT6368_IRQ_VPA_OC - MT6368_IRQ_BUCK_BASE + 1)
#define MT6368_IRQ_LDO_BITS \
	(MT6368_IRQ_VEFUSE_OC - MT6368_IRQ_LDO_BASE + 1)
#define MT6368_IRQ_MISC_BITS \
	(MT6368_IRQ_TOP_PROTREG - MT6368_IRQ_MISC_BASE + 1)
#define MT6368_IRQ_AUD_BITS \
	(MT6368_IRQ_ACCDET_EINT1 - MT6368_IRQ_AUD_BASE + 1)

#define MT6368_TOP_GEN(sp) \
{ \
	.hwirq_base = MT6368_IRQ_##sp##_BASE, \
	.num_int_regs =	((MT6368_IRQ_##sp##_BITS - 1) / MT6368_REG_WIDTH) + 1, \
	.en_reg = MT6368_##sp##_TOP_INT_CON0, \
	.en_reg_shift = 0x3, \
	.sta_reg = MT6368_##sp##_TOP_INT_STATUS0, \
	.sta_reg_shift = 0x1, \
	.top_offset = MT6368_##sp##_TOP, \
}

#endif /* __MFD_MT6368_CORE_H__ */