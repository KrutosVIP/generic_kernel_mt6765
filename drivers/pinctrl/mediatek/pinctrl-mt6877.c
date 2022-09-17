// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 MediaTek Inc.
 * Author: Andy Teng <andy.teng@mediatek.com>
 *
 */

#include "pinctrl-mtk-mt6877.h"
#include "pinctrl-paris.h"

/* MT6877 have multiple bases to program pin configuration listed as the below:
 * gpio:0x10005000,     iocfg_rm:0x11C20000, iocfg_rb:0x11C30000,
 * iocfg_bm:0x11D10000, iocfg_bl:0x11D30000, iocfg_br:0x11D40000,
 * iocfg_lm:0x11E20000, iocfg_rt:0x11EA0000, iocfg_tl:0x11F30000
 * _i_based could be used to indicate what base the pin should be mapped into.
 */

#define PIN_FIELD_BASE(s_pin, e_pin, i_base, s_addr, x_addrs, s_bit, x_bits) \
	PIN_FIELD_CALC(s_pin, e_pin, i_base, s_addr, x_addrs, s_bit, x_bits, \
		       32, 0)

#define PINS_FIELD_BASE(s_pin, e_pin, i_base, s_addr, x_addrs, s_bit, x_bits) \
	PIN_FIELD_CALC(s_pin, e_pin, i_base, s_addr, x_addrs, s_bit, x_bits,  \
		       32, 1)

static const struct mtk_pin_field_calc mt6877_pin_mode_range[] = {
	PIN_FIELD_BASE(0, 7, 0, 0x0300, 0x10, 0, 4),
	PIN_FIELD_BASE(8, 15, 0, 0x0310, 0x10, 0, 4),
	PIN_FIELD_BASE(16, 23, 0, 0x0320, 0x10, 0, 4),
	PIN_FIELD_BASE(24, 31, 0, 0x0330, 0x10, 0, 4),
	PIN_FIELD_BASE(32, 39, 0, 0x0340, 0x10, 0, 4),
	PIN_FIELD_BASE(40, 47, 0, 0x0350, 0x10, 0, 4),
	PIN_FIELD_BASE(48, 55, 0, 0x0360, 0x10, 0, 4),
	PIN_FIELD_BASE(56, 63, 0, 0x0370, 0x10, 0, 4),
	PIN_FIELD_BASE(64, 71, 0, 0x0380, 0x10, 0, 4),
	PIN_FIELD_BASE(72, 79, 0, 0x0390, 0x10, 0, 4),
	PIN_FIELD_BASE(80, 87, 0, 0x03a0, 0x10, 0, 4),
	PIN_FIELD_BASE(88, 95, 0, 0x03b0, 0x10, 0, 4),
	PIN_FIELD_BASE(96, 103, 0, 0x03c0, 0x10, 0, 4),
	PIN_FIELD_BASE(104, 111, 0, 0x03d0, 0x10, 0, 4),
	PIN_FIELD_BASE(112, 119, 0, 0x03e0, 0x10, 0, 4),
	PIN_FIELD_BASE(120, 127, 0, 0x03f0, 0x10, 0, 4),
	PIN_FIELD_BASE(128, 135, 0, 0x0400, 0x10, 0, 4),
	PIN_FIELD_BASE(136, 143, 0, 0x0410, 0x10, 0, 4),
	PIN_FIELD_BASE(144, 151, 0, 0x0420, 0x10, 0, 4),
	PIN_FIELD_BASE(152, 159, 0, 0x0430, 0x10, 0, 4),
	PIN_FIELD_BASE(160, 167, 0, 0x0440, 0x10, 0, 4),
	PIN_FIELD_BASE(168, 175, 0, 0x0450, 0x10, 0, 4),
	PIN_FIELD_BASE(176, 183, 0, 0x0460, 0x10, 0, 4),
	PIN_FIELD_BASE(184, 191, 0, 0x0470, 0x10, 0, 4),
	PIN_FIELD_BASE(192, 199, 0, 0x0480, 0x10, 0, 4),
	PIN_FIELD_BASE(200, 207, 0, 0x0490, 0x10, 0, 4),
	PIN_FIELD_BASE(208, 208, 0, 0x04a0, 0x10, 0, 4),
};

static const struct mtk_pin_field_calc mt6877_pin_dir_range[] = {
	PIN_FIELD_BASE(0, 31, 0, 0x0000, 0x10, 0, 1),
	PIN_FIELD_BASE(32, 63, 0, 0x0010, 0x10, 0, 1),
	PIN_FIELD_BASE(64, 95, 0, 0x0020, 0x10, 0, 1),
	PIN_FIELD_BASE(96, 127, 0, 0x0030, 0x10, 0, 1),
	PIN_FIELD_BASE(128, 159, 0, 0x0040, 0x10, 0, 1),
	PIN_FIELD_BASE(160, 191, 0, 0x0050, 0x10, 0, 1),
	PIN_FIELD_BASE(192, 208, 0, 0x0060, 0x10, 0, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_di_range[] = {
	PIN_FIELD_BASE(0, 31, 0, 0x0200, 0x10, 0, 1),
	PIN_FIELD_BASE(32, 63, 0, 0x0210, 0x10, 0, 1),
	PIN_FIELD_BASE(64, 95, 0, 0x0220, 0x10, 0, 1),
	PIN_FIELD_BASE(96, 127, 0, 0x0230, 0x10, 0, 1),
	PIN_FIELD_BASE(128, 159, 0, 0x0240, 0x10, 0, 1),
	PIN_FIELD_BASE(160, 191, 0, 0x0250, 0x10, 0, 1),
	PIN_FIELD_BASE(192, 208, 0, 0x0260, 0x10, 0, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_do_range[] = {
	PIN_FIELD_BASE(0, 31, 0, 0x0100, 0x10, 0, 1),
	PIN_FIELD_BASE(32, 63, 0, 0x0110, 0x10, 0, 1),
	PIN_FIELD_BASE(64, 95, 0, 0x0120, 0x10, 0, 1),
	PIN_FIELD_BASE(96, 127, 0, 0x0130, 0x10, 0, 1),
	PIN_FIELD_BASE(128, 159, 0, 0x0140, 0x10, 0, 1),
	PIN_FIELD_BASE(160, 191, 0, 0x0150, 0x10, 0, 1),
	PIN_FIELD_BASE(192, 208, 0, 0x0160, 0x10, 0, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_smt_range[] = {
	PINS_FIELD_BASE(0, 2, 5, 0x0100, 0x10, 20, 1),
	PIN_FIELD_BASE(3, 3, 5, 0x0100, 0x10, 18, 1),
	PINS_FIELD_BASE(4, 5, 5, 0x0100, 0x10, 19, 1),
	PINS_FIELD_BASE(6, 7, 5, 0x0100, 0x10, 14, 1),
	PIN_FIELD_BASE(8, 8, 5, 0x0100, 0x10, 12, 1),
	PINS_FIELD_BASE(9, 11, 5, 0x0100, 0x10, 17, 1),
	PINS_FIELD_BASE(12, 13, 6, 0x00b0, 0x10, 0, 1),
	PINS_FIELD_BASE(14, 15, 8, 0x00f0, 0x10, 12, 1),
	PINS_FIELD_BASE(16, 20, 3, 0x00f0, 0x10, 7, 1),
	PINS_FIELD_BASE(21, 22, 3, 0x00f0, 0x10, 3, 1),
	PIN_FIELD_BASE(23, 23, 3, 0x00f0, 0x10, 6, 1),
	PIN_FIELD_BASE(24, 24, 8, 0x00f0, 0x10, 10, 1),
	PIN_FIELD_BASE(25, 26, 8, 0x00f0, 0x10, 0, 1),
	PIN_FIELD_BASE(27, 27, 8, 0x00f0, 0x10, 11, 1),
	PIN_FIELD_BASE(28, 35, 8, 0x00f0, 0x10, 2, 1),
	PIN_FIELD_BASE(36, 37, 8, 0x00f0, 0x10, 14, 1),
	PINS_FIELD_BASE(38, 39, 8, 0x00f0, 0x10, 12, 1),
	PIN_FIELD_BASE(40, 40, 8, 0x00f0, 0x10, 13, 1),
	PINS_FIELD_BASE(41, 44, 6, 0x00b0, 0x10, 1, 1),
	PIN_FIELD_BASE(45, 45, 6, 0x00b0, 0x10, 5, 1),
	PINS_FIELD_BASE(46, 47, 6, 0x00b0, 0x10, 2, 1),
	PIN_FIELD_BASE(48, 48, 6, 0x00b0, 0x10, 3, 1),
	PIN_FIELD_BASE(49, 49, 6, 0x00b0, 0x10, 12, 1),
	PIN_FIELD_BASE(50, 51, 6, 0x00b0, 0x10, 3, 1),
	PINS_FIELD_BASE(52, 53, 6, 0x00b0, 0x10, 3, 1),
	PIN_FIELD_BASE(54, 54, 6, 0x00b0, 0x10, 5, 1),
	PINS_FIELD_BASE(55, 57, 6, 0x00b0, 0x10, 4, 1),
	PINS_FIELD_BASE(58, 59, 6, 0x00b0, 0x10, 2, 1),
	PIN_FIELD_BASE(60, 63, 6, 0x00b0, 0x10, 8, 1),
	PIN_FIELD_BASE(64, 65, 6, 0x00b0, 0x10, 6, 1),
	PINS_FIELD_BASE(66, 67, 4, 0x0090, 0x10, 11, 1),
	PINS_FIELD_BASE(68, 69, 4, 0x0090, 0x10, 10, 1),
	PIN_FIELD_BASE(70, 70, 4, 0x0090, 0x10, 1, 1),
	PINS_FIELD_BASE(71, 74, 4, 0x0090, 0x10, 2, 1),
	PINS_FIELD_BASE(75, 78, 4, 0x0090, 0x10, 3, 1),
	PINS_FIELD_BASE(79, 81, 4, 0x0090, 0x10, 4, 1),
	PINS_FIELD_BASE(82, 83, 4, 0x0090, 0x10, 9, 1),
	PINS_FIELD_BASE(84, 85, 4, 0x0090, 0x10, 8, 1),
	PIN_FIELD_BASE(86, 86, 4, 0x0090, 0x10, 1, 1),
	PIN_FIELD_BASE(87, 87, 4, 0x0090, 0x10, 4, 1),
	PINS_FIELD_BASE(88, 91, 4, 0x0090, 0x10, 5, 1),
	PINS_FIELD_BASE(92, 95, 4, 0x0090, 0x10, 6, 1),
	PINS_FIELD_BASE(96, 97, 4, 0x0090, 0x10, 7, 1),
	PIN_FIELD_BASE(98, 98, 4, 0x0090, 0x10, 0, 1),
	PIN_FIELD_BASE(99, 99, 3, 0x00f0, 0x10, 5, 1),
	PIN_FIELD_BASE(100, 100, 3, 0x00f0, 0x10, 9, 1),
	PIN_FIELD_BASE(101, 101, 4, 0x0090, 0x10, 0, 1),
	PIN_FIELD_BASE(102, 102, 3, 0x00f0, 0x10, 9, 1),
	PINS_FIELD_BASE(103, 104, 3, 0x00f0, 0x10, 8, 1),
	PIN_FIELD_BASE(105, 105, 3, 0x00f0, 0x10, 9, 1),
	PIN_FIELD_BASE(106, 106, 3, 0x00f0, 0x10, 6, 1),
	PINS_FIELD_BASE(107, 108, 3, 0x00f0, 0x10, 10, 1),
	PIN_FIELD_BASE(109, 110, 3, 0x00f0, 0x10, 1, 1),
	PIN_FIELD_BASE(111, 111, 5, 0x0100, 0x10, 13, 1),
	PIN_FIELD_BASE(112, 112, 3, 0x00f0, 0x10, 9, 1),
	PINS_FIELD_BASE(113, 114, 3, 0x00f0, 0x10, 13, 1),
	PIN_FIELD_BASE(115, 115, 3, 0x00f0, 0x10, 11, 1),
	PIN_FIELD_BASE(116, 118, 3, 0x00f0, 0x10, 10, 1),
	PIN_FIELD_BASE(119, 119, 3, 0x00f0, 0x10, 11, 1),
	PIN_FIELD_BASE(120, 120, 3, 0x00f0, 0x10, 4, 1),
	PIN_FIELD_BASE(121, 121, 3, 0x00f0, 0x10, 11, 1),
	PIN_FIELD_BASE(122, 122, 3, 0x00f0, 0x10, 10, 1),
	PINS_FIELD_BASE(123, 125, 3, 0x00f0, 0x10, 12, 1),
	PINS_FIELD_BASE(126, 127, 3, 0x00f0, 0x10, 13, 1),
	PIN_FIELD_BASE(128, 128, 5, 0x0100, 0x10, 19, 1),
	PIN_FIELD_BASE(129, 129, 5, 0x0100, 0x10, 18, 1),
	PIN_FIELD_BASE(130, 130, 5, 0x0100, 0x10, 23, 1),
	PIN_FIELD_BASE(131, 131, 3, 0x00f0, 0x10, 14, 1),
	PIN_FIELD_BASE(132, 133, 5, 0x0100, 0x10, 21, 1),
	PIN_FIELD_BASE(134, 134, 5, 0x0100, 0x10, 5, 1),
	PIN_FIELD_BASE(135, 135, 5, 0x0100, 0x10, 9, 1),
	PIN_FIELD_BASE(136, 136, 3, 0x00f0, 0x10, 0, 1),
	PIN_FIELD_BASE(137, 137, 5, 0x0100, 0x10, 10, 1),
	PIN_FIELD_BASE(138, 138, 5, 0x0100, 0x10, 15, 1),
	PIN_FIELD_BASE(139, 139, 5, 0x0100, 0x10, 14, 1),
	PIN_FIELD_BASE(140, 140, 5, 0x0100, 0x10, 19, 1),
	PIN_FIELD_BASE(141, 141, 5, 0x0100, 0x10, 18, 1),
	PIN_FIELD_BASE(142, 142, 3, 0x00f0, 0x10, 6, 1),
	PIN_FIELD_BASE(143, 143, 5, 0x0100, 0x10, 3, 1),
	PIN_FIELD_BASE(144, 144, 5, 0x0100, 0x10, 7, 1),
	PIN_FIELD_BASE(145, 145, 5, 0x0100, 0x10, 4, 1),
	PIN_FIELD_BASE(146, 146, 5, 0x0100, 0x10, 8, 1),
	PIN_FIELD_BASE(147, 147, 5, 0x0100, 0x10, 6, 1),
	PIN_FIELD_BASE(148, 148, 5, 0x0100, 0x10, 11, 1),
	PIN_FIELD_BASE(149, 153, 2, 0x0060, 0x10, 0, 1),
	PIN_FIELD_BASE(154, 154, 2, 0x0060, 0x10, 6, 1),
	PIN_FIELD_BASE(155, 155, 5, 0x0100, 0x10, 17, 1),
	PIN_FIELD_BASE(156, 156, 2, 0x0060, 0x10, 5, 1),
	PIN_FIELD_BASE(157, 157, 5, 0x0100, 0x10, 1, 1),
	PIN_FIELD_BASE(158, 158, 2, 0x0060, 0x10, 7, 1),
	PIN_FIELD_BASE(159, 159, 2, 0x0060, 0x10, 6, 1),
	PINS_FIELD_BASE(160, 161, 5, 0x0100, 0x10, 16, 1),
	PIN_FIELD_BASE(162, 162, 5, 0x0100, 0x10, 0, 1),
	PIN_FIELD_BASE(163, 163, 5, 0x0100, 0x10, 2, 1),
	PIN_FIELD_BASE(164, 164, 1, 0x00a0, 0x10, 1, 1),
	PIN_FIELD_BASE(165, 165, 1, 0x00a0, 0x10, 0, 1),
	PIN_FIELD_BASE(166, 166, 1, 0x00a0, 0x10, 5, 1),
	PIN_FIELD_BASE(167, 168, 1, 0x00a0, 0x10, 3, 1),
	PIN_FIELD_BASE(169, 169, 1, 0x00a0, 0x10, 2, 1),
	PIN_FIELD_BASE(170, 170, 1, 0x00a0, 0x10, 10, 1),
	PIN_FIELD_BASE(171, 171, 1, 0x00a0, 0x10, 9, 1),
	PIN_FIELD_BASE(172, 172, 1, 0x00a0, 0x10, 11, 1),
	PIN_FIELD_BASE(173, 173, 1, 0x00a0, 0x10, 8, 1),
	PIN_FIELD_BASE(174, 175, 1, 0x00a0, 0x10, 6, 1),
	PINS_FIELD_BASE(176, 177, 7, 0x00d0, 0x10, 10, 1),
	PINS_FIELD_BASE(178, 179, 7, 0x00d0, 0x10, 7, 1),
	PINS_FIELD_BASE(180, 181, 7, 0x00d0, 0x10, 10, 1),
	PINS_FIELD_BASE(182, 185, 7, 0x00d0, 0x10, 11, 1),
	PIN_FIELD_BASE(186, 187, 7, 0x00d0, 0x10, 12, 1),
	PIN_FIELD_BASE(188, 189, 7, 0x00d0, 0x10, 0, 1),
	PIN_FIELD_BASE(190, 190, 7, 0x00d0, 0x10, 6, 1),
	PIN_FIELD_BASE(191, 195, 7, 0x00d0, 0x10, 2, 1),
	PINS_FIELD_BASE(196, 206, 7, 0x00d0, 0x10, 8, 1),
	PINS_FIELD_BASE(207, 208, 7, 0x00d0, 0x10, 9, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_ies_range[] = {
	PIN_FIELD_BASE(0, 1, 5, 0x0070, 0x10, 15, 1),
	PIN_FIELD_BASE(2, 9, 5, 0x0070, 0x10, 19, 1),
	PIN_FIELD_BASE(10, 11, 5, 0x0070, 0x10, 17, 1),
	PIN_FIELD_BASE(12, 13, 6, 0x0060, 0x10, 10, 1),
	PIN_FIELD_BASE(14, 15, 8, 0x0050, 0x10, 2, 1),
	PIN_FIELD_BASE(16, 23, 3, 0x0040, 0x10, 2, 1),
	PIN_FIELD_BASE(24, 24, 8, 0x0050, 0x10, 15, 1),
	PIN_FIELD_BASE(25, 26, 8, 0x0050, 0x10, 5, 1),
	PIN_FIELD_BASE(27, 27, 8, 0x0050, 0x10, 16, 1),
	PIN_FIELD_BASE(28, 35, 8, 0x0050, 0x10, 7, 1),
	PIN_FIELD_BASE(36, 37, 8, 0x0050, 0x10, 17, 1),
	PIN_FIELD_BASE(38, 39, 8, 0x0050, 0x10, 0, 1),
	PIN_FIELD_BASE(40, 40, 8, 0x0050, 0x10, 4, 1),
	PIN_FIELD_BASE(41, 42, 6, 0x0060, 0x10, 12, 1),
	PIN_FIELD_BASE(43, 43, 6, 0x0060, 0x10, 15, 1),
	PIN_FIELD_BASE(44, 44, 6, 0x0060, 0x10, 14, 1),
	PIN_FIELD_BASE(45, 45, 6, 0x0060, 0x10, 16, 1),
	PIN_FIELD_BASE(46, 46, 6, 0x0060, 0x10, 18, 1),
	PIN_FIELD_BASE(47, 49, 6, 0x0060, 0x10, 24, 1),
	PIN_FIELD_BASE(50, 50, 6, 0x0060, 0x10, 0, 1),
	PIN_FIELD_BASE(51, 51, 6, 0x0060, 0x10, 9, 1),
	PIN_FIELD_BASE(52, 54, 6, 0x0060, 0x10, 4, 1),
	PIN_FIELD_BASE(55, 55, 6, 0x0060, 0x10, 8, 1),
	PIN_FIELD_BASE(56, 56, 6, 0x0060, 0x10, 7, 1),
	PIN_FIELD_BASE(57, 59, 6, 0x0060, 0x10, 1, 1),
	PIN_FIELD_BASE(60, 63, 6, 0x0060, 0x10, 20, 1),
	PIN_FIELD_BASE(64, 64, 6, 0x0060, 0x10, 17, 1),
	PIN_FIELD_BASE(65, 65, 6, 0x0060, 0x10, 19, 1),
	PIN_FIELD_BASE(66, 67, 4, 0x0020, 0x10, 30, 1),
	PIN_FIELD_BASE(68, 69, 4, 0x0020, 0x10, 28, 1),
	PIN_FIELD_BASE(70, 70, 4, 0x0020, 0x10, 23, 1),
	PIN_FIELD_BASE(71, 72, 4, 0x0020, 0x10, 0, 1),
	PIN_FIELD_BASE(73, 73, 4, 0x0020, 0x10, 12, 1),
	PIN_FIELD_BASE(74, 80, 4, 0x0020, 0x10, 15, 1),
	PIN_FIELD_BASE(81, 81, 4, 0x0020, 0x10, 2, 1),
	PIN_FIELD_BASE(82, 83, 4, 0x0020, 0x10, 26, 1),
	PIN_FIELD_BASE(84, 85, 4, 0x0020, 0x10, 24, 1),
	PIN_FIELD_BASE(86, 86, 4, 0x0020, 0x10, 22, 1),
	PIN_FIELD_BASE(87, 95, 4, 0x0020, 0x10, 3, 1),
	PIN_FIELD_BASE(96, 97, 4, 0x0020, 0x10, 13, 1),
	PIN_FIELD_BASE(98, 98, 4, 0x0030, 0x10, 0, 1),
	PIN_FIELD_BASE(99, 100, 3, 0x0050, 0x10, 4, 1),
	PIN_FIELD_BASE(101, 101, 4, 0x0030, 0x10, 1, 1),
	PIN_FIELD_BASE(102, 102, 3, 0x0040, 0x10, 19, 1),
	PIN_FIELD_BASE(103, 103, 3, 0x0040, 0x10, 16, 1),
	PIN_FIELD_BASE(104, 104, 3, 0x0040, 0x10, 18, 1),
	PIN_FIELD_BASE(105, 105, 3, 0x0040, 0x10, 10, 1),
	PIN_FIELD_BASE(106, 106, 3, 0x0040, 0x10, 17, 1),
	PIN_FIELD_BASE(107, 110, 3, 0x0040, 0x10, 25, 1),
	PIN_FIELD_BASE(111, 111, 5, 0x0070, 0x10, 31, 1),
	PIN_FIELD_BASE(112, 112, 3, 0x0040, 0x10, 0, 1),
	PIN_FIELD_BASE(113, 113, 3, 0x0040, 0x10, 23, 1),
	PIN_FIELD_BASE(114, 115, 3, 0x0040, 0x10, 21, 1),
	PIN_FIELD_BASE(116, 116, 3, 0x0040, 0x10, 20, 1),
	PIN_FIELD_BASE(117, 117, 3, 0x0040, 0x10, 14, 1),
	PIN_FIELD_BASE(118, 118, 3, 0x0040, 0x10, 11, 1),
	PIN_FIELD_BASE(119, 119, 3, 0x0040, 0x10, 13, 1),
	PIN_FIELD_BASE(120, 120, 3, 0x0040, 0x10, 15, 1),
	PIN_FIELD_BASE(121, 121, 3, 0x0040, 0x10, 12, 1),
	PIN_FIELD_BASE(122, 125, 3, 0x0050, 0x10, 0, 1),
	PIN_FIELD_BASE(126, 127, 3, 0x0040, 0x10, 29, 1),
	PIN_FIELD_BASE(128, 129, 5, 0x0080, 0x10, 1, 1),
	PIN_FIELD_BASE(130, 130, 5, 0x0080, 0x10, 4, 1),
	PIN_FIELD_BASE(131, 131, 3, 0x0040, 0x10, 31, 1),
	PIN_FIELD_BASE(132, 132, 5, 0x0080, 0x10, 0, 1),
	PIN_FIELD_BASE(133, 133, 5, 0x0080, 0x10, 3, 1),
	PIN_FIELD_BASE(134, 134, 5, 0x0070, 0x10, 8, 1),
	PIN_FIELD_BASE(135, 135, 5, 0x0070, 0x10, 12, 1),
	PIN_FIELD_BASE(136, 136, 3, 0x0040, 0x10, 1, 1),
	PIN_FIELD_BASE(137, 137, 5, 0x0070, 0x10, 13, 1),
	PIN_FIELD_BASE(138, 141, 5, 0x0070, 0x10, 27, 1),
	PIN_FIELD_BASE(142, 142, 3, 0x0040, 0x10, 24, 1),
	PIN_FIELD_BASE(143, 143, 5, 0x0070, 0x10, 6, 1),
	PIN_FIELD_BASE(144, 144, 5, 0x0070, 0x10, 10, 1),
	PIN_FIELD_BASE(145, 145, 5, 0x0070, 0x10, 7, 1),
	PIN_FIELD_BASE(146, 146, 5, 0x0070, 0x10, 11, 1),
	PIN_FIELD_BASE(147, 147, 5, 0x0070, 0x10, 9, 1),
	PIN_FIELD_BASE(148, 148, 5, 0x0070, 0x10, 14, 1),
	PIN_FIELD_BASE(149, 154, 2, 0x0020, 0x10, 0, 1),
	PIN_FIELD_BASE(155, 155, 5, 0x0070, 0x10, 2, 1),
	PIN_FIELD_BASE(156, 156, 2, 0x0020, 0x10, 6, 1),
	PIN_FIELD_BASE(157, 157, 5, 0x0070, 0x10, 3, 1),
	PIN_FIELD_BASE(158, 159, 2, 0x0020, 0x10, 7, 1),
	PIN_FIELD_BASE(160, 160, 5, 0x0070, 0x10, 0, 1),
	PIN_FIELD_BASE(161, 161, 5, 0x0070, 0x10, 4, 1),
	PIN_FIELD_BASE(162, 162, 5, 0x0070, 0x10, 1, 1),
	PIN_FIELD_BASE(163, 163, 5, 0x0070, 0x10, 5, 1),
	PIN_FIELD_BASE(164, 164, 1, 0x0020, 0x10, 1, 1),
	PIN_FIELD_BASE(165, 165, 1, 0x0020, 0x10, 0, 1),
	PIN_FIELD_BASE(166, 166, 1, 0x0020, 0x10, 5, 1),
	PIN_FIELD_BASE(167, 168, 1, 0x0020, 0x10, 3, 1),
	PIN_FIELD_BASE(169, 169, 1, 0x0020, 0x10, 2, 1),
	PIN_FIELD_BASE(170, 170, 1, 0x0020, 0x10, 10, 1),
	PIN_FIELD_BASE(171, 171, 1, 0x0020, 0x10, 9, 1),
	PIN_FIELD_BASE(172, 172, 1, 0x0020, 0x10, 11, 1),
	PIN_FIELD_BASE(173, 173, 1, 0x0020, 0x10, 8, 1),
	PIN_FIELD_BASE(174, 175, 1, 0x0020, 0x10, 6, 1),
	PIN_FIELD_BASE(176, 177, 7, 0x0050, 0x10, 21, 1),
	PIN_FIELD_BASE(178, 178, 7, 0x0050, 0x10, 31, 1),
	PIN_FIELD_BASE(179, 179, 7, 0x0050, 0x10, 29, 1),
	PIN_FIELD_BASE(180, 180, 7, 0x0060, 0x10, 0, 1),
	PIN_FIELD_BASE(181, 181, 7, 0x0050, 0x10, 30, 1),
	PIN_FIELD_BASE(182, 185, 7, 0x0050, 0x10, 25, 1),
	PIN_FIELD_BASE(186, 187, 7, 0x0050, 0x10, 23, 1),
	PIN_FIELD_BASE(188, 198, 7, 0x0050, 0x10, 0, 1),
	PIN_FIELD_BASE(199, 206, 7, 0x0050, 0x10, 13, 1),
	PIN_FIELD_BASE(207, 208, 7, 0x0050, 0x10, 11, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_pu_range[] = {
	PIN_FIELD_BASE(0, 1, 5, 0x00b0, 0x10, 15, 1),
	PIN_FIELD_BASE(2, 9, 5, 0x00b0, 0x10, 19, 1),
	PIN_FIELD_BASE(10, 11, 5, 0x00b0, 0x10, 17, 1),
	PIN_FIELD_BASE(12, 13, 6, 0x0080, 0x10, 10, 1),
	PIN_FIELD_BASE(14, 15, 8, 0x0080, 0x10, 2, 1),
	PIN_FIELD_BASE(16, 23, 3, 0x0090, 0x10, 2, 1),
	PIN_FIELD_BASE(36, 37, 8, 0x0080, 0x10, 5, 1),
	PIN_FIELD_BASE(38, 39, 8, 0x0080, 0x10, 0, 1),
	PIN_FIELD_BASE(40, 40, 8, 0x0080, 0x10, 4, 1),
	PIN_FIELD_BASE(41, 42, 6, 0x0080, 0x10, 12, 1),
	PIN_FIELD_BASE(43, 43, 6, 0x0080, 0x10, 15, 1),
	PIN_FIELD_BASE(44, 44, 6, 0x0080, 0x10, 14, 1),
	PIN_FIELD_BASE(45, 45, 6, 0x0080, 0x10, 16, 1),
	PIN_FIELD_BASE(46, 46, 6, 0x0080, 0x10, 18, 1),
	PIN_FIELD_BASE(47, 49, 6, 0x0080, 0x10, 24, 1),
	PIN_FIELD_BASE(50, 50, 6, 0x0080, 0x10, 0, 1),
	PIN_FIELD_BASE(51, 51, 6, 0x0080, 0x10, 9, 1),
	PIN_FIELD_BASE(52, 54, 6, 0x0080, 0x10, 4, 1),
	PIN_FIELD_BASE(55, 55, 6, 0x0080, 0x10, 8, 1),
	PIN_FIELD_BASE(56, 56, 6, 0x0080, 0x10, 7, 1),
	PIN_FIELD_BASE(57, 59, 6, 0x0080, 0x10, 1, 1),
	PIN_FIELD_BASE(60, 63, 6, 0x0080, 0x10, 20, 1),
	PIN_FIELD_BASE(64, 64, 6, 0x0080, 0x10, 17, 1),
	PIN_FIELD_BASE(65, 65, 6, 0x0080, 0x10, 19, 1),
	PIN_FIELD_BASE(66, 67, 4, 0x0060, 0x10, 30, 1),
	PIN_FIELD_BASE(68, 69, 4, 0x0060, 0x10, 28, 1),
	PIN_FIELD_BASE(70, 70, 4, 0x0060, 0x10, 23, 1),
	PIN_FIELD_BASE(71, 72, 4, 0x0060, 0x10, 0, 1),
	PIN_FIELD_BASE(73, 73, 4, 0x0060, 0x10, 12, 1),
	PIN_FIELD_BASE(74, 80, 4, 0x0060, 0x10, 15, 1),
	PIN_FIELD_BASE(81, 81, 4, 0x0060, 0x10, 2, 1),
	PIN_FIELD_BASE(82, 83, 4, 0x0060, 0x10, 26, 1),
	PIN_FIELD_BASE(84, 85, 4, 0x0060, 0x10, 24, 1),
	PIN_FIELD_BASE(86, 86, 4, 0x0060, 0x10, 22, 1),
	PIN_FIELD_BASE(87, 95, 4, 0x0060, 0x10, 3, 1),
	PIN_FIELD_BASE(96, 97, 4, 0x0060, 0x10, 13, 1),
	PIN_FIELD_BASE(98, 98, 4, 0x0070, 0x10, 0, 1),
	PIN_FIELD_BASE(99, 100, 3, 0x00a0, 0x10, 0, 1),
	PIN_FIELD_BASE(101, 101, 4, 0x0070, 0x10, 1, 1),
	PIN_FIELD_BASE(102, 102, 3, 0x0090, 0x10, 19, 1),
	PIN_FIELD_BASE(103, 103, 3, 0x0090, 0x10, 16, 1),
	PIN_FIELD_BASE(104, 104, 3, 0x0090, 0x10, 18, 1),
	PIN_FIELD_BASE(105, 105, 3, 0x0090, 0x10, 10, 1),
	PIN_FIELD_BASE(106, 106, 3, 0x0090, 0x10, 17, 1),
	PIN_FIELD_BASE(107, 110, 3, 0x0090, 0x10, 21, 1),
	PIN_FIELD_BASE(111, 111, 5, 0x00b0, 0x10, 31, 1),
	PIN_FIELD_BASE(112, 112, 3, 0x0090, 0x10, 0, 1),
	PIN_FIELD_BASE(117, 117, 3, 0x0090, 0x10, 14, 1),
	PIN_FIELD_BASE(118, 118, 3, 0x0090, 0x10, 11, 1),
	PIN_FIELD_BASE(119, 119, 3, 0x0090, 0x10, 13, 1),
	PIN_FIELD_BASE(120, 120, 3, 0x0090, 0x10, 15, 1),
	PIN_FIELD_BASE(121, 121, 3, 0x0090, 0x10, 12, 1),
	PIN_FIELD_BASE(122, 125, 3, 0x0090, 0x10, 28, 1),
	PIN_FIELD_BASE(126, 127, 3, 0x0090, 0x10, 25, 1),
	PIN_FIELD_BASE(128, 129, 5, 0x00c0, 0x10, 1, 1),
	PIN_FIELD_BASE(130, 130, 5, 0x00c0, 0x10, 4, 1),
	PIN_FIELD_BASE(131, 131, 3, 0x0090, 0x10, 27, 1),
	PIN_FIELD_BASE(132, 132, 5, 0x00c0, 0x10, 0, 1),
	PIN_FIELD_BASE(133, 133, 5, 0x00c0, 0x10, 3, 1),
	PIN_FIELD_BASE(134, 134, 5, 0x00b0, 0x10, 8, 1),
	PIN_FIELD_BASE(135, 135, 5, 0x00b0, 0x10, 12, 1),
	PIN_FIELD_BASE(136, 136, 3, 0x0090, 0x10, 1, 1),
	PIN_FIELD_BASE(137, 137, 5, 0x00b0, 0x10, 13, 1),
	PIN_FIELD_BASE(138, 141, 5, 0x00b0, 0x10, 27, 1),
	PIN_FIELD_BASE(142, 142, 3, 0x0090, 0x10, 20, 1),
	PIN_FIELD_BASE(143, 143, 5, 0x00b0, 0x10, 6, 1),
	PIN_FIELD_BASE(144, 144, 5, 0x00b0, 0x10, 10, 1),
	PIN_FIELD_BASE(145, 145, 5, 0x00b0, 0x10, 7, 1),
	PIN_FIELD_BASE(146, 146, 5, 0x00b0, 0x10, 11, 1),
	PIN_FIELD_BASE(147, 147, 5, 0x00b0, 0x10, 9, 1),
	PIN_FIELD_BASE(148, 148, 5, 0x00b0, 0x10, 14, 1),
	PIN_FIELD_BASE(149, 154, 2, 0x0040, 0x10, 0, 1),
	PIN_FIELD_BASE(155, 155, 5, 0x00b0, 0x10, 2, 1),
	PIN_FIELD_BASE(156, 156, 2, 0x0040, 0x10, 6, 1),
	PIN_FIELD_BASE(157, 157, 5, 0x00b0, 0x10, 3, 1),
	PIN_FIELD_BASE(158, 159, 2, 0x0040, 0x10, 7, 1),
	PIN_FIELD_BASE(160, 160, 5, 0x00b0, 0x10, 0, 1),
	PIN_FIELD_BASE(161, 161, 5, 0x00b0, 0x10, 4, 1),
	PIN_FIELD_BASE(162, 162, 5, 0x00b0, 0x10, 1, 1),
	PIN_FIELD_BASE(163, 163, 5, 0x00b0, 0x10, 5, 1),
	PIN_FIELD_BASE(176, 177, 7, 0x0090, 0x10, 21, 1),
	PIN_FIELD_BASE(178, 178, 7, 0x0090, 0x10, 31, 1),
	PIN_FIELD_BASE(179, 179, 7, 0x0090, 0x10, 29, 1),
	PIN_FIELD_BASE(180, 180, 7, 0x00a0, 0x10, 0, 1),
	PIN_FIELD_BASE(181, 181, 7, 0x0090, 0x10, 30, 1),
	PIN_FIELD_BASE(182, 185, 7, 0x0090, 0x10, 25, 1),
	PIN_FIELD_BASE(186, 187, 7, 0x0090, 0x10, 23, 1),
	PIN_FIELD_BASE(188, 198, 7, 0x0090, 0x10, 0, 1),
	PIN_FIELD_BASE(199, 206, 7, 0x0090, 0x10, 13, 1),
	PIN_FIELD_BASE(207, 208, 7, 0x0090, 0x10, 11, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_pd_range[] = {
	PIN_FIELD_BASE(0, 1, 5, 0x0090, 0x10, 15, 1),
	PIN_FIELD_BASE(2, 9, 5, 0x0090, 0x10, 19, 1),
	PIN_FIELD_BASE(10, 11, 5, 0x0090, 0x10, 17, 1),
	PIN_FIELD_BASE(12, 13, 6, 0x0070, 0x10, 10, 1),
	PIN_FIELD_BASE(14, 15, 8, 0x0060, 0x10, 2, 1),
	PIN_FIELD_BASE(16, 23, 3, 0x0060, 0x10, 2, 1),
	PIN_FIELD_BASE(36, 37, 8, 0x0060, 0x10, 5, 1),
	PIN_FIELD_BASE(38, 39, 8, 0x0060, 0x10, 0, 1),
	PIN_FIELD_BASE(40, 40, 8, 0x0060, 0x10, 4, 1),
	PIN_FIELD_BASE(41, 42, 6, 0x0070, 0x10, 12, 1),
	PIN_FIELD_BASE(43, 43, 6, 0x0070, 0x10, 15, 1),
	PIN_FIELD_BASE(44, 44, 6, 0x0070, 0x10, 14, 1),
	PIN_FIELD_BASE(45, 45, 6, 0x0070, 0x10, 16, 1),
	PIN_FIELD_BASE(46, 46, 6, 0x0070, 0x10, 18, 1),
	PIN_FIELD_BASE(47, 49, 6, 0x0070, 0x10, 24, 1),
	PIN_FIELD_BASE(50, 50, 6, 0x0070, 0x10, 0, 1),
	PIN_FIELD_BASE(51, 51, 6, 0x0070, 0x10, 9, 1),
	PIN_FIELD_BASE(52, 54, 6, 0x0070, 0x10, 4, 1),
	PIN_FIELD_BASE(55, 55, 6, 0x0070, 0x10, 8, 1),
	PIN_FIELD_BASE(56, 56, 6, 0x0070, 0x10, 7, 1),
	PIN_FIELD_BASE(57, 59, 6, 0x0070, 0x10, 1, 1),
	PIN_FIELD_BASE(60, 63, 6, 0x0070, 0x10, 20, 1),
	PIN_FIELD_BASE(64, 64, 6, 0x0070, 0x10, 17, 1),
	PIN_FIELD_BASE(65, 65, 6, 0x0070, 0x10, 19, 1),
	PIN_FIELD_BASE(66, 67, 4, 0x0040, 0x10, 30, 1),
	PIN_FIELD_BASE(68, 69, 4, 0x0040, 0x10, 28, 1),
	PIN_FIELD_BASE(70, 70, 4, 0x0040, 0x10, 23, 1),
	PIN_FIELD_BASE(71, 72, 4, 0x0040, 0x10, 0, 1),
	PIN_FIELD_BASE(73, 73, 4, 0x0040, 0x10, 12, 1),
	PIN_FIELD_BASE(74, 80, 4, 0x0040, 0x10, 15, 1),
	PIN_FIELD_BASE(81, 81, 4, 0x0040, 0x10, 2, 1),
	PIN_FIELD_BASE(82, 83, 4, 0x0040, 0x10, 26, 1),
	PIN_FIELD_BASE(84, 85, 4, 0x0040, 0x10, 24, 1),
	PIN_FIELD_BASE(86, 86, 4, 0x0040, 0x10, 22, 1),
	PIN_FIELD_BASE(87, 95, 4, 0x0040, 0x10, 3, 1),
	PIN_FIELD_BASE(96, 97, 4, 0x0040, 0x10, 13, 1),
	PIN_FIELD_BASE(98, 98, 4, 0x0050, 0x10, 0, 1),
	PIN_FIELD_BASE(99, 100, 3, 0x0070, 0x10, 0, 1),
	PIN_FIELD_BASE(101, 101, 4, 0x0050, 0x10, 1, 1),
	PIN_FIELD_BASE(102, 102, 3, 0x0060, 0x10, 19, 1),
	PIN_FIELD_BASE(103, 103, 3, 0x0060, 0x10, 16, 1),
	PIN_FIELD_BASE(104, 104, 3, 0x0060, 0x10, 18, 1),
	PIN_FIELD_BASE(105, 105, 3, 0x0060, 0x10, 10, 1),
	PIN_FIELD_BASE(106, 106, 3, 0x0060, 0x10, 17, 1),
	PIN_FIELD_BASE(107, 110, 3, 0x0060, 0x10, 21, 1),
	PIN_FIELD_BASE(111, 111, 5, 0x0090, 0x10, 31, 1),
	PIN_FIELD_BASE(112, 112, 3, 0x0060, 0x10, 0, 1),
	PIN_FIELD_BASE(117, 117, 3, 0x0060, 0x10, 14, 1),
	PIN_FIELD_BASE(118, 118, 3, 0x0060, 0x10, 11, 1),
	PIN_FIELD_BASE(119, 119, 3, 0x0060, 0x10, 13, 1),
	PIN_FIELD_BASE(120, 120, 3, 0x0060, 0x10, 15, 1),
	PIN_FIELD_BASE(121, 121, 3, 0x0060, 0x10, 12, 1),
	PIN_FIELD_BASE(122, 125, 3, 0x0060, 0x10, 28, 1),
	PIN_FIELD_BASE(126, 127, 3, 0x0060, 0x10, 25, 1),
	PIN_FIELD_BASE(128, 129, 5, 0x00a0, 0x10, 1, 1),
	PIN_FIELD_BASE(130, 130, 5, 0x00a0, 0x10, 4, 1),
	PIN_FIELD_BASE(131, 131, 3, 0x0060, 0x10, 27, 1),
	PIN_FIELD_BASE(132, 132, 5, 0x00a0, 0x10, 0, 1),
	PIN_FIELD_BASE(133, 133, 5, 0x00a0, 0x10, 3, 1),
	PIN_FIELD_BASE(134, 134, 5, 0x0090, 0x10, 8, 1),
	PIN_FIELD_BASE(135, 135, 5, 0x0090, 0x10, 12, 1),
	PIN_FIELD_BASE(136, 136, 3, 0x0060, 0x10, 1, 1),
	PIN_FIELD_BASE(137, 137, 5, 0x0090, 0x10, 13, 1),
	PIN_FIELD_BASE(138, 141, 5, 0x0090, 0x10, 27, 1),
	PIN_FIELD_BASE(142, 142, 3, 0x0060, 0x10, 20, 1),
	PIN_FIELD_BASE(143, 143, 5, 0x0090, 0x10, 6, 1),
	PIN_FIELD_BASE(144, 144, 5, 0x0090, 0x10, 10, 1),
	PIN_FIELD_BASE(145, 145, 5, 0x0090, 0x10, 7, 1),
	PIN_FIELD_BASE(146, 146, 5, 0x0090, 0x10, 11, 1),
	PIN_FIELD_BASE(147, 147, 5, 0x0090, 0x10, 9, 1),
	PIN_FIELD_BASE(148, 148, 5, 0x0090, 0x10, 14, 1),
	PIN_FIELD_BASE(149, 154, 2, 0x0030, 0x10, 0, 1),
	PIN_FIELD_BASE(155, 155, 5, 0x0090, 0x10, 2, 1),
	PIN_FIELD_BASE(156, 156, 2, 0x0030, 0x10, 6, 1),
	PIN_FIELD_BASE(157, 157, 5, 0x0090, 0x10, 3, 1),
	PIN_FIELD_BASE(158, 159, 2, 0x0030, 0x10, 7, 1),
	PIN_FIELD_BASE(160, 160, 5, 0x0090, 0x10, 0, 1),
	PIN_FIELD_BASE(161, 161, 5, 0x0090, 0x10, 4, 1),
	PIN_FIELD_BASE(162, 162, 5, 0x0090, 0x10, 1, 1),
	PIN_FIELD_BASE(163, 163, 5, 0x0090, 0x10, 5, 1),
	PIN_FIELD_BASE(176, 177, 7, 0x0070, 0x10, 21, 1),
	PIN_FIELD_BASE(178, 178, 7, 0x0070, 0x10, 31, 1),
	PIN_FIELD_BASE(179, 179, 7, 0x0070, 0x10, 29, 1),
	PIN_FIELD_BASE(180, 180, 7, 0x0080, 0x10, 0, 1),
	PIN_FIELD_BASE(181, 181, 7, 0x0070, 0x10, 30, 1),
	PIN_FIELD_BASE(182, 185, 7, 0x0070, 0x10, 25, 1),
	PIN_FIELD_BASE(186, 187, 7, 0x0070, 0x10, 23, 1),
	PIN_FIELD_BASE(188, 198, 7, 0x0070, 0x10, 0, 1),
	PIN_FIELD_BASE(199, 206, 7, 0x0070, 0x10, 13, 1),
	PIN_FIELD_BASE(207, 208, 7, 0x0070, 0x10, 11, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_drv_range[] = {
	PIN_FIELD_BASE(0, 6, 5, 0x0010, 0x10, 9, 3),
	PIN_FIELD_BASE(7, 8, 5, 0x0020, 0x10, 0, 3),
	PINS_FIELD_BASE(9, 11, 5, 0x0020, 0x10, 15, 3),
	PIN_FIELD_BASE(12, 13, 6, 0x0010, 0x10, 0, 3),
	PINS_FIELD_BASE(14, 15, 8, 0x0010, 0x10, 6, 3),
	PIN_FIELD_BASE(16, 22, 3, 0x0000, 0x10, 3, 3),
	PIN_FIELD_BASE(23, 23, 3, 0x0020, 0x10, 6, 3),
	PIN_FIELD_BASE(24, 24, 8, 0x0010, 0x10, 0, 3),
	PIN_FIELD_BASE(25, 26, 8, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(27, 27, 8, 0x0010, 0x10, 3, 3),
	PIN_FIELD_BASE(28, 35, 8, 0x0000, 0x10, 6, 3),
	PIN_FIELD_BASE(36, 37, 8, 0x0010, 0x10, 12, 3),
	PINS_FIELD_BASE(38, 39, 8, 0x0010, 0x10, 6, 3),
	PIN_FIELD_BASE(40, 40, 8, 0x0010, 0x10, 9, 3),
	PINS_FIELD_BASE(41, 44, 6, 0x0010, 0x10, 6, 3),
	PINS_FIELD_BASE(46, 48, 6, 0x0010, 0x10, 9, 3),
	PIN_FIELD_BASE(49, 49, 6, 0x0020, 0x10, 0, 3),
	PIN_FIELD_BASE(50, 50, 6, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(51, 51, 6, 0x0000, 0x10, 27, 3),
	PIN_FIELD_BASE(52, 54, 6, 0x0000, 0x10, 12, 3),
	PIN_FIELD_BASE(55, 55, 6, 0x0000, 0x10, 24, 3),
	PIN_FIELD_BASE(56, 56, 6, 0x0000, 0x10, 21, 3),
	PIN_FIELD_BASE(57, 59, 6, 0x0000, 0x10, 3, 3),
	PIN_FIELD_BASE(60, 63, 6, 0x0010, 0x10, 18, 3),
	PIN_FIELD_BASE(64, 65, 6, 0x0010, 0x10, 12, 3),
	PINS_FIELD_BASE(66, 67, 4, 0x0010, 0x10, 3, 3),
	PINS_FIELD_BASE(68, 69, 4, 0x0010, 0x10, 0, 3),
	PIN_FIELD_BASE(70, 70, 4, 0x0000, 0x10, 3, 3),
	PINS_FIELD_BASE(71, 74, 4, 0x0000, 0x10, 6, 3),
	PINS_FIELD_BASE(75, 78, 4, 0x0000, 0x10, 9, 3),
	PINS_FIELD_BASE(79, 81, 4, 0x0000, 0x10, 12, 3),
	PINS_FIELD_BASE(82, 83, 4, 0x0000, 0x10, 27, 3),
	PINS_FIELD_BASE(84, 85, 4, 0x0000, 0x10, 24, 3),
	PIN_FIELD_BASE(86, 86, 4, 0x0000, 0x10, 3, 3),
	PIN_FIELD_BASE(87, 87, 4, 0x0000, 0x10, 12, 3),
	PINS_FIELD_BASE(88, 91, 4, 0x0000, 0x10, 15, 3),
	PINS_FIELD_BASE(92, 95, 4, 0x0000, 0x10, 18, 3),
	PINS_FIELD_BASE(96, 97, 4, 0x0000, 0x10, 21, 3),
	PIN_FIELD_BASE(98, 98, 4, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(99, 99, 3, 0x0020, 0x10, 3, 3),
	PIN_FIELD_BASE(100, 100, 3, 0x0020, 0x10, 9, 3),
	PIN_FIELD_BASE(101, 101, 4, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(102, 102, 3, 0x0010, 0x10, 21, 3),
	PIN_FIELD_BASE(103, 103, 3, 0x0010, 0x10, 12, 3),
	PIN_FIELD_BASE(104, 104, 3, 0x0010, 0x10, 18, 3),
	PIN_FIELD_BASE(105, 105, 3, 0x0000, 0x10, 24, 3),
	PIN_FIELD_BASE(106, 106, 3, 0x0010, 0x10, 15, 3),
	PINS_FIELD_BASE(107, 108, 3, 0x0020, 0x10, 12, 3),
	PIN_FIELD_BASE(109, 110, 3, 0x0010, 0x10, 24, 3),
	PIN_FIELD_BASE(111, 111, 5, 0x0020, 0x10, 6, 3),
	PIN_FIELD_BASE(112, 112, 3, 0x0020, 0x10, 9, 3),
	PINS_FIELD_BASE(113, 114, 3, 0x0020, 0x10, 0, 3),
	PIN_FIELD_BASE(115, 115, 3, 0x0020, 0x10, 15, 3),
	PIN_FIELD_BASE(116, 116, 3, 0x0020, 0x10, 12, 3),
	PIN_FIELD_BASE(117, 117, 3, 0x0010, 0x10, 6, 3),
	PIN_FIELD_BASE(118, 118, 3, 0x0000, 0x10, 27, 3),
	PIN_FIELD_BASE(119, 119, 3, 0x0010, 0x10, 3, 3),
	PIN_FIELD_BASE(120, 120, 3, 0x0010, 0x10, 9, 3),
	PIN_FIELD_BASE(121, 121, 3, 0x0010, 0x10, 0, 3),
	PIN_FIELD_BASE(122, 122, 3, 0x0020, 0x10, 12, 3),
	PINS_FIELD_BASE(123, 125, 3, 0x0020, 0x10, 15, 3),
	PIN_FIELD_BASE(126, 127, 3, 0x0020, 0x10, 18, 3),
	PIN_FIELD_BASE(128, 128, 5, 0x0020, 0x10, 27, 3),
	PIN_FIELD_BASE(129, 129, 5, 0x0030, 0x10, 0, 3),
	PIN_FIELD_BASE(130, 130, 5, 0x0030, 0x10, 6, 3),
	PIN_FIELD_BASE(131, 131, 3, 0x0020, 0x10, 24, 3),
	PIN_FIELD_BASE(132, 132, 5, 0x0020, 0x10, 24, 3),
	PIN_FIELD_BASE(133, 133, 5, 0x0030, 0x10, 3, 3),
	PIN_FIELD_BASE(134, 134, 5, 0x0000, 0x10, 18, 3),
	PIN_FIELD_BASE(135, 135, 5, 0x0010, 0x10, 0, 3),
	PIN_FIELD_BASE(136, 136, 3, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(137, 137, 5, 0x0010, 0x10, 3, 3),
	PIN_FIELD_BASE(138, 139, 5, 0x0020, 0x10, 9, 3),
	PINS_FIELD_BASE(140, 141, 5, 0x0020, 0x10, 21, 3),
	PIN_FIELD_BASE(142, 142, 3, 0x0020, 0x10, 6, 3),
	PIN_FIELD_BASE(143, 143, 5, 0x0000, 0x10, 12, 3),
	PIN_FIELD_BASE(144, 144, 5, 0x0000, 0x10, 24, 3),
	PIN_FIELD_BASE(145, 145, 5, 0x0000, 0x10, 15, 3),
	PIN_FIELD_BASE(146, 146, 5, 0x0000, 0x10, 27, 3),
	PIN_FIELD_BASE(147, 147, 5, 0x0000, 0x10, 21, 3),
	PIN_FIELD_BASE(148, 148, 5, 0x0010, 0x10, 6, 3),
	PIN_FIELD_BASE(149, 154, 2, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(155, 155, 5, 0x0000, 0x10, 3, 3),
	PIN_FIELD_BASE(156, 156, 2, 0x0000, 0x10, 18, 3),
	PIN_FIELD_BASE(157, 157, 5, 0x0000, 0x10, 6, 3),
	PIN_FIELD_BASE(158, 159, 2, 0x0000, 0x10, 21, 3),
	PINS_FIELD_BASE(160, 161, 5, 0x0020, 0x10, 18, 3),
	PIN_FIELD_BASE(162, 162, 5, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(163, 163, 5, 0x0000, 0x10, 9, 3),
	PIN_FIELD_BASE(164, 164, 1, 0x0000, 0x10, 3, 3),
	PIN_FIELD_BASE(165, 165, 1, 0x0000, 0x10, 0, 3),
	PIN_FIELD_BASE(166, 166, 1, 0x0000, 0x10, 15, 3),
	PIN_FIELD_BASE(167, 168, 1, 0x0000, 0x10, 9, 3),
	PIN_FIELD_BASE(169, 169, 1, 0x0000, 0x10, 6, 3),
	PIN_FIELD_BASE(170, 170, 1, 0x0000, 0x10, 26, 2),
	PIN_FIELD_BASE(171, 171, 1, 0x0000, 0x10, 24, 2),
	PIN_FIELD_BASE(172, 172, 1, 0x0000, 0x10, 28, 2),
	PIN_FIELD_BASE(173, 173, 1, 0x0000, 0x10, 22, 2),
	PIN_FIELD_BASE(174, 175, 1, 0x0000, 0x10, 18, 2),
	PINS_FIELD_BASE(176, 177, 7, 0x0010, 0x10, 3, 3),
	PINS_FIELD_BASE(178, 179, 7, 0x0000, 0x10, 24, 3),
	PINS_FIELD_BASE(180, 181, 7, 0x0010, 0x10, 3, 3),
	PIN_FIELD_BASE(182, 185, 7, 0x0010, 0x10, 12, 3),
	PIN_FIELD_BASE(186, 187, 7, 0x0010, 0x10, 6, 3),
	PIN_FIELD_BASE(188, 195, 7, 0x0000, 0x10, 0, 3),
	PINS_FIELD_BASE(196, 206, 7, 0x0000, 0x10, 27, 3),
	PINS_FIELD_BASE(207, 208, 7, 0x0010, 0x10, 0, 3),
};

static const struct mtk_pin_field_calc mt6877_pin_pupd_range[] = {
	PIN_FIELD_BASE(24, 24, 8, 0x0070, 0x10, 10, 1),
	PIN_FIELD_BASE(25, 26, 8, 0x0070, 0x10, 0, 1),
	PIN_FIELD_BASE(27, 27, 8, 0x0070, 0x10, 11, 1),
	PIN_FIELD_BASE(28, 35, 8, 0x0070, 0x10, 2, 1),
	PIN_FIELD_BASE(113, 113, 3, 0x0080, 0x10, 3, 1),
	PIN_FIELD_BASE(114, 115, 3, 0x0080, 0x10, 1, 1),
	PIN_FIELD_BASE(116, 116, 3, 0x0080, 0x10, 0, 1),
	PIN_FIELD_BASE(164, 164, 1, 0x0040, 0x10, 1, 1),
	PIN_FIELD_BASE(165, 165, 1, 0x0040, 0x10, 0, 1),
	PIN_FIELD_BASE(166, 166, 1, 0x0040, 0x10, 5, 1),
	PIN_FIELD_BASE(167, 168, 1, 0x0040, 0x10, 3, 1),
	PIN_FIELD_BASE(169, 169, 1, 0x0040, 0x10, 2, 1),
	PIN_FIELD_BASE(170, 170, 1, 0x0040, 0x10, 10, 1),
	PIN_FIELD_BASE(171, 171, 1, 0x0040, 0x10, 9, 1),
	PIN_FIELD_BASE(172, 172, 1, 0x0040, 0x10, 11, 1),
	PIN_FIELD_BASE(173, 173, 1, 0x0040, 0x10, 8, 1),
	PIN_FIELD_BASE(174, 175, 1, 0x0040, 0x10, 6, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_r0_range[] = {
	PIN_FIELD_BASE(24, 24, 8, 0x0090, 0x10, 10, 1),
	PIN_FIELD_BASE(25, 26, 8, 0x0090, 0x10, 0, 1),
	PIN_FIELD_BASE(27, 27, 8, 0x0090, 0x10, 11, 1),
	PIN_FIELD_BASE(28, 35, 8, 0x0090, 0x10, 2, 1),
	PIN_FIELD_BASE(113, 113, 3, 0x00b0, 0x10, 3, 1),
	PIN_FIELD_BASE(114, 115, 3, 0x00b0, 0x10, 1, 1),
	PIN_FIELD_BASE(116, 116, 3, 0x00b0, 0x10, 0, 1),
	PIN_FIELD_BASE(164, 164, 1, 0x0050, 0x10, 1, 1),
	PIN_FIELD_BASE(165, 165, 1, 0x0050, 0x10, 0, 1),
	PIN_FIELD_BASE(166, 166, 1, 0x0050, 0x10, 5, 1),
	PIN_FIELD_BASE(167, 168, 1, 0x0050, 0x10, 3, 1),
	PIN_FIELD_BASE(169, 169, 1, 0x0050, 0x10, 2, 1),
	PIN_FIELD_BASE(170, 170, 1, 0x0050, 0x10, 10, 1),
	PIN_FIELD_BASE(171, 171, 1, 0x0050, 0x10, 9, 1),
	PIN_FIELD_BASE(172, 172, 1, 0x0050, 0x10, 11, 1),
	PIN_FIELD_BASE(173, 173, 1, 0x0050, 0x10, 8, 1),
	PIN_FIELD_BASE(174, 175, 1, 0x0050, 0x10, 6, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_r1_range[] = {
	PIN_FIELD_BASE(24, 24, 8, 0x00a0, 0x10, 10, 1),
	PIN_FIELD_BASE(25, 26, 8, 0x00a0, 0x10, 0, 1),
	PIN_FIELD_BASE(27, 27, 8, 0x00a0, 0x10, 11, 1),
	PIN_FIELD_BASE(28, 35, 8, 0x00a0, 0x10, 2, 1),
	PIN_FIELD_BASE(113, 113, 3, 0x00c0, 0x10, 3, 1),
	PIN_FIELD_BASE(114, 115, 3, 0x00c0, 0x10, 1, 1),
	PIN_FIELD_BASE(116, 116, 3, 0x00c0, 0x10, 0, 1),
	PIN_FIELD_BASE(164, 164, 1, 0x0060, 0x10, 1, 1),
	PIN_FIELD_BASE(165, 165, 1, 0x0060, 0x10, 0, 1),
	PIN_FIELD_BASE(166, 166, 1, 0x0060, 0x10, 5, 1),
	PIN_FIELD_BASE(167, 168, 1, 0x0060, 0x10, 3, 1),
	PIN_FIELD_BASE(169, 169, 1, 0x0060, 0x10, 2, 1),
	PIN_FIELD_BASE(170, 170, 1, 0x0060, 0x10, 10, 1),
	PIN_FIELD_BASE(171, 171, 1, 0x0060, 0x10, 9, 1),
	PIN_FIELD_BASE(172, 172, 1, 0x0060, 0x10, 11, 1),
	PIN_FIELD_BASE(173, 173, 1, 0x0060, 0x10, 8, 1),
	PIN_FIELD_BASE(174, 175, 1, 0x0060, 0x10, 6, 1),
};

static const struct mtk_pin_field_calc mt6877_pin_eh_range[] = {
	PIN_FIELD_BASE(36, 36, 8, 0x0030, 0x10, 0, 3),
	PIN_FIELD_BASE(37, 37, 8, 0x0030, 0x10, 3, 3),
	PIN_FIELD_BASE(60, 60, 6, 0x0030, 0x10, 6, 5),
	PIN_FIELD_BASE(61, 61, 6, 0x0030, 0x10, 11, 5),
	PIN_FIELD_BASE(62, 62, 6, 0x0030, 0x10, 16, 5),
	PIN_FIELD_BASE(63, 63, 6, 0x0030, 0x10, 21, 5),
	PIN_FIELD_BASE(64, 64, 6, 0x0030, 0x10, 0, 3),
	PIN_FIELD_BASE(65, 65, 6, 0x0030, 0x10, 3, 3),
	PIN_FIELD_BASE(130, 130, 5, 0x0050, 0x10, 3, 3),
	PIN_FIELD_BASE(131, 131, 3, 0x0030, 0x10, 3, 3),
	PIN_FIELD_BASE(132, 132, 5, 0x0040, 0x10, 27, 3),
	PIN_FIELD_BASE(133, 133, 5, 0x0050, 0x10, 0, 3),
	PIN_FIELD_BASE(134, 134, 5, 0x0040, 0x10, 6, 3),
	PIN_FIELD_BASE(135, 135, 5, 0x0040, 0x10, 18, 3),
	PIN_FIELD_BASE(136, 136, 3, 0x0030, 0x10, 0, 3),
	PIN_FIELD_BASE(137, 137, 5, 0x0040, 0x10, 21, 3),
	PIN_FIELD_BASE(143, 143, 5, 0x0040, 0x10, 0, 3),
	PIN_FIELD_BASE(144, 144, 5, 0x0040, 0x10, 12, 3),
	PIN_FIELD_BASE(145, 145, 5, 0x0040, 0x10, 3, 3),
	PIN_FIELD_BASE(146, 146, 5, 0x0040, 0x10, 15, 3),
	PIN_FIELD_BASE(147, 147, 5, 0x0040, 0x10, 9, 3),
	PIN_FIELD_BASE(148, 148, 5, 0x0040, 0x10, 24, 3),
	PIN_FIELD_BASE(149, 149, 2, 0x0010, 0x10, 0, 5),
	PIN_FIELD_BASE(150, 150, 2, 0x0010, 0x10, 5, 5),
	PIN_FIELD_BASE(151, 151, 2, 0x0010, 0x10, 10, 5),
	PIN_FIELD_BASE(152, 152, 2, 0x0010, 0x10, 15, 5),
	PIN_FIELD_BASE(153, 153, 2, 0x0010, 0x10, 20, 5),
	PIN_FIELD_BASE(186, 186, 7, 0x0030, 0x10, 0, 3),
	PIN_FIELD_BASE(187, 187, 7, 0x0030, 0x10, 3, 3),
};

static const struct mtk_eint_hw mt6877_eint_hw = {
	.port_mask = 7,
	.ports     = 7,
	.ap_num    = 128,
	.db_cnt    = 32,
};

static const struct mtk_pin_reg_calc mt6877_reg_cals[PINCTRL_PIN_REG_MAX] = {
	[PINCTRL_PIN_REG_MODE] = MTK_RANGE(mt6877_pin_mode_range),
	[PINCTRL_PIN_REG_DIR] = MTK_RANGE(mt6877_pin_dir_range),
	[PINCTRL_PIN_REG_DI] = MTK_RANGE(mt6877_pin_di_range),
	[PINCTRL_PIN_REG_DO] = MTK_RANGE(mt6877_pin_do_range),
	[PINCTRL_PIN_REG_SR] = MTK_RANGE(mt6877_pin_dir_range),
	[PINCTRL_PIN_REG_SMT] = MTK_RANGE(mt6877_pin_smt_range),
	[PINCTRL_PIN_REG_IES] = MTK_RANGE(mt6877_pin_ies_range),
	[PINCTRL_PIN_REG_PU] = MTK_RANGE(mt6877_pin_pu_range),
	[PINCTRL_PIN_REG_PD] = MTK_RANGE(mt6877_pin_pd_range),
	[PINCTRL_PIN_REG_DRV] = MTK_RANGE(mt6877_pin_drv_range),
	[PINCTRL_PIN_REG_PUPD] = MTK_RANGE(mt6877_pin_pupd_range),
	[PINCTRL_PIN_REG_R0] = MTK_RANGE(mt6877_pin_r0_range),
	[PINCTRL_PIN_REG_R1] = MTK_RANGE(mt6877_pin_r1_range),
	[PINCTRL_PIN_REG_DRV_EH] = MTK_RANGE(mt6877_pin_eh_range),
};

static const struct mtk_eh_pin_pinmux mt6877_eh_pin_pinmux_list[] = {
	/* pin number, pinmux number */
	{36, 1},
	{37, 1},
	{60, 2},
	{61, 2},
	{62, 2},
	{63, 2},
	{64, 1},
	{65, 1},
	{130, 1},
	{131, 1},
	{132, 1},
	{133, 1},
	{134, 1},
	{135, 1},
	{136, 1},
	{137, 1},
	{143, 1},
	{144, 1},
	{145, 1},
	{146, 1},
	{147, 1},
	{148, 1},
	{186, 1},
	{187, 1},
	{0xffff, 0}, /* indicate end of array */
};

static const struct mtk_pin_soc mt6877_data = {
	.reg_cal = mt6877_reg_cals,
	.pins = mtk_pins_mt6877,
	.npins = ARRAY_SIZE(mtk_pins_mt6877),
	.ngrps = ARRAY_SIZE(mtk_pins_mt6877),
	.eint_hw = &mt6877_eint_hw,
	.nfuncs = 8,
	.gpio_m = 0,
	.race_free_access = true,
	.eh_pin_pinmux = mt6877_eh_pin_pinmux_list,
	.bias_set_combo = mtk_pinconf_bias_set_combo,
	.bias_get_combo = mtk_pinconf_bias_get_combo,
	.drive_set = mtk_pinconf_drive_set_raw,
	.drive_get = mtk_pinconf_drive_get_raw,
	.adv_pull_get = mtk_pinconf_adv_pull_get,
	.adv_pull_set = mtk_pinconf_adv_pull_set,
	.adv_drive_get = mtk_pinconf_adv_drive_get,
	.adv_drive_set = mtk_pinconf_adv_drive_set,
};

static const struct of_device_id mt6877_pinctrl_of_match[] = {
	{ .compatible = "mediatek,mt6877-pinctrl", },
	{ }
};

static int mt6877_pinctrl_probe(struct platform_device *pdev)
{
	return mtk_paris_pinctrl_probe(pdev, &mt6877_data);
}

static struct platform_driver mt6877_pinctrl_driver = {
	.driver = {
		.name = "mt6877-pinctrl",
		.of_match_table = mt6877_pinctrl_of_match,
		.pm = &mtk_eint_pm_ops_v2,
	},
	.probe = mt6877_pinctrl_probe,
};

static int __init mt6877_pinctrl_init(void)
{
	return platform_driver_register(&mt6877_pinctrl_driver);
}
arch_initcall(mt6877_pinctrl_init);