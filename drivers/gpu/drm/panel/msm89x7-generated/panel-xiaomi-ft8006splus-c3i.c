// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2025 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct ft8006splus_c3i {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline
struct ft8006splus_c3i *to_ft8006splus_c3i(struct drm_panel *panel)
{
	return container_of(panel, struct ft8006splus_c3i, panel);
}

static void ft8006splus_c3i_reset(struct ft8006splus_c3i *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(5000, 6000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(45);
}

static int ft8006splus_c3i_on(struct ft8006splus_c3i *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8d, 0x5a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x91, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x05, 0x85, 0x82, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_DDB_START,
				     0x00, 0x46);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80,
				     0xe7, 0xce, 0xbc, 0xb5, 0xa7, 0xa1, 0x98,
				     0x93, 0x8c, 0x89, 0x84, 0x82, 0x00, 0x60,
				     0xf6, 0x6f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x90,
				     0xf6, 0x2f, 0xf3, 0xef, 0x6f, 0xbf, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x41, 0x5a, 0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80,
				     0x30, 0x4a, 0xf9, 0xdc, 0x7b, 0x0b, 0xad,
				     0x37, 0xb8, 0x68, 0x19, 0x6a, 0xba, 0x9a,
				     0xba, 0x7a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x90,
				     0xea, 0x19, 0x49, 0x68, 0x49, 0xe9, 0x19,
				     0x1a, 0x0a, 0xfa, 0x69, 0x9a, 0x2a, 0x9a,
				     0x79, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa0,
				     0x3a, 0xba, 0x19, 0x2a, 0xca, 0x09, 0xca,
				     0xa9, 0x88, 0x48, 0x48, 0x09);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_usleep_range(&dsi_ctx, 10000, 11000);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0eff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);

	return dsi_ctx.accum_err;
}

static int ft8006splus_c3i_off(struct ft8006splus_c3i *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_usleep_range(&dsi_ctx, 10000, 11000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x5a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x5a);
	mipi_dsi_msleep(&dsi_ctx, 150);

	return dsi_ctx.accum_err;
}

static int ft8006splus_c3i_prepare(struct drm_panel *panel)
{
	struct ft8006splus_c3i *ctx = to_ft8006splus_c3i(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ft8006splus_c3i_reset(ctx);

	ret = ft8006splus_c3i_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int ft8006splus_c3i_unprepare(struct drm_panel *panel)
{
	struct ft8006splus_c3i *ctx = to_ft8006splus_c3i(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = ft8006splus_c3i_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode ft8006splus_c3i_mode = {
	.clock = (720 + 80 + 16 + 60) * (1520 + 70 + 8 + 37) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 80,
	.hsync_end = 720 + 80 + 16,
	.htotal = 720 + 80 + 16 + 60,
	.vdisplay = 1520,
	.vsync_start = 1520 + 70,
	.vsync_end = 1520 + 70 + 8,
	.vtotal = 1520 + 70 + 8 + 37,
	.width_mm = 68,
	.height_mm = 143,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int ft8006splus_c3i_get_modes(struct drm_panel *panel,
				     struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &ft8006splus_c3i_mode);
}

static const struct drm_panel_funcs ft8006splus_c3i_panel_funcs = {
	.prepare = ft8006splus_c3i_prepare,
	.unprepare = ft8006splus_c3i_unprepare,
	.get_modes = ft8006splus_c3i_get_modes,
};

static int ft8006splus_c3i_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct ft8006splus_c3i *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct ft8006splus_c3i, panel,
				   &ft8006splus_c3i_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	ctx->panel.prepare_prev_first = true;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void ft8006splus_c3i_remove(struct mipi_dsi_device *dsi)
{
	struct ft8006splus_c3i *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id ft8006splus_c3i_of_match[] = {
	{ .compatible = "mdss,ft8006splus-c3i" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, ft8006splus_c3i_of_match);

static struct mipi_dsi_driver ft8006splus_c3i_driver = {
	.probe = ft8006splus_c3i_probe,
	.remove = ft8006splus_c3i_remove,
	.driver = {
		.name = "panel-ft8006splus-c3i",
		.of_match_table = ft8006splus_c3i_of_match,
	},
};
module_mipi_dsi_driver(ft8006splus_c3i_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for ft8006s hdplus c3i video mode dsi panel");
MODULE_LICENSE("GPL");
