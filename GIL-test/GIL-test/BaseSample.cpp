#include "BaseSample.h"
#include <boost/gil.hpp>

using namespace boost::gil;

BaseSample::BaseSample()
{
}


BaseSample::~BaseSample()
{
}


/*
void x_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
{
	assert(src.dimensions() == dst.dimensions());

	for (int y = 0; y < src.height(); ++y)
		for (int x = 1; x < src.width() - 1; ++x)
			dst(x, y) = (src(x - 1, y) - src(x + 1, y)) / 2;

}

void x_gradient2(const gray8c_view_t& src, const gray8s_view_t& dst)
{
	assert(src.dimensions() == dst.dimensions());

	for (int y = 0; y < src.height(); ++y)
	{
		gray8c_view_t::x_iterator src_it = src.row_begin(y);
		gray8s_view_t::x_iterator dst_it = dst.row_begin(y);

		for (int x = 1; x < src.width() - 1; ++x)
			dst_it[x] = (src_it[x - 1] - src_it[x + 1]) / 2;
	}
}

void y_gradient(const gray8c_view_t& src, const gray8s_view_t& dst)
{
	for (int x = 0; x < src.width(); ++x)
	{
		gray8c_view_t::y_iterator src_it = src.col_begin(x);
		gray8s_view_t::y_iterator dst_it = dst.col_begin(x);

		for (int y = 1; y < src.height() - 1; ++y)
			dst_it[y] = (src_it[y - 1] - src_it[y + 1]) / 2;
	}
}

void y_gradient2(const gray8c_view_t& src, const gray8s_view_t& dst)
{
	for (int y = 1; y < src.height() - 1; ++y)
	{
		gray8c_view_t::x_iterator src1_it = src.row_begin(y - 1);
		gray8c_view_t::x_iterator src2_it = src.row_begin(y + 1);
		gray8s_view_t::x_iterator dst_it = dst.row_begin(y);

		for (int x = 0; x < src.width(); ++x) {
			*dst_it = ((*src1_it) - (*src2_it)) / 2;
			++dst_it;
			++src1_it;
			++src2_it;
		}
	}
}

void y_gradient3(const gray8c_view_t& src, const gray8s_view_t& dst)
{
	gray8c_view_t::xy_locator src_loc = src.xy_at(0, 1);
	gray8c_view_t::xy_locator::cached_location_t above = src_loc.cache_location(0, -1);
	gray8c_view_t::xy_locator::cached_location_t below = src_loc.cache_location(0, 1);

	for (int y = 1; y < src.height() - 1; ++y)
	{
		gray8s_view_t::x_iterator dst_it = dst.row_begin(y);

		for (int x = 0; x < src.width(); ++x)
		{
			(*dst_it) = (src_loc[above] - src_loc[below]) / 2;
			++dst_it;
			++src_loc.x();
		}

		src_loc += point2<std::ptrdiff_t>(-src.width(), 1);
	}
}

void x_gradient_unguarded(const gray8c_view_t& src, const gray8s_view_t& dst)
{
	gray8c_view_t::iterator src_it = src.begin();
	for (gray8s_view_t::iterator dst_it = dst.begin(); dst_it != dst.end(); ++dst_it, ++src_it)
		*dst_it = (src_it.x()[-1] - src_it.x()[1]) / 2;
}

void x_gradient3(const gray8c_view_t& src, const gray8s_view_t& dst)
{
	assert(src.width() >= 2);
	x_gradient_unguarded(subimage_view(src, 1, 0, src.width() - 2, src.height()),
		subimage_view(dst, 1, 0, src.width() - 2, src.height()));
}

void x_gradient_rgb_luminosity(const rgb32fc_view_t& src, const gray8s_view_t& dst)
{
	x_gradient(color_converted_view<gray8_pixel_t>(src), dst);
}

template <typename SrcView, typename DstView>
void x_luminosity_gradient(const SrcView& src, const DstView& dst)
{
	//channel_type, color_space_type, channel_mapping_type, and num_channels
	typedef typename channel_type<DstView>::type d_channel_t;
	typedef typename channel_convert_to_unsigned<d_channel_t>::type channel_t;
	typedef pixel<channel_t, gray_layout_t>  gray_pixel_t;
	typedef image<gray_pixel_t, false>       gray_image_t;

	gray_image_t ccv_image(src.dimensions());
	copy_pixels(color_converted_view<gray_pixel_t>(src), view(ccv_image));
	x_gradient(const_view(ccv_image), dst);
}

// Calling with 16-bit grayscale data
void XGradientGray16_Gray32(const unsigned short* src_pixels, ptrdiff_t src_row_bytes, int w, int h, signed int* dst_pixels, ptrdiff_t dst_row_bytes)
{
	gray16c_view_t src = interleaved_view(w, h, (const gray16_pixel_t*)src_pixels, src_row_bytes);
	gray32s_view_t dst = interleaved_view(w, h, (gray32s_pixel_t*)dst_pixels, dst_row_bytes);
	x_gradient(src, dst);
}

// Calling with 8-bit RGB data into 16-bit BGR
void XGradientRGB8_BGR16(const unsigned char* src_pixels, ptrdiff_t src_row_bytes, int w, int h, signed short* dst_pixels, ptrdiff_t dst_row_bytes)
{
	rgb8c_view_t  src = interleaved_view(w, h, (const rgb8_pixel_t*)src_pixels, src_row_bytes);
	rgb16s_view_t dst = interleaved_view(w, h, (rgb16s_pixel_t*)dst_pixels, dst_row_bytes);
	x_gradient(src, dst);
}

// Either or both the source and the destination could be planar - the gradient code does not change
void XGradientPlanarRGB8_RGB32(const unsigned short* src_r, const unsigned short* src_g, const unsigned short* src_b, ptrdiff_t src_row_bytes, int w, int h, signed int* dst_pixels, ptrdiff_t dst_row_bytes)
{
	rgb16c_planar_view_t src = planar_rgb_view(w, h, src_r, src_g, src_b, src_row_bytes);
	rgb32s_view_t dst = interleaved_view(w, h, (rgb32s_pixel_t*)dst_pixels, dst_row_bytes);
	x_gradient(src, dst);
}

void ComputeXGradientGray8(const unsigned char* src_pixels, ptrdiff_t src_row_bytes, int w, int h, signed char* dst_pixels, ptrdiff_t dst_row_bytes)
{
	gray8c_view_t src = interleaved_view(w, h, (const gray8_pixel_t*)src_pixels, src_row_bytes);
	gray8s_view_t dst = interleaved_view(w, h, (gray8s_pixel_t*)dst_pixels, dst_row_bytes);
	x_gradient(src, dst);
}

*/