#include <boost/gil.hpp>
#include <boost/gil/extension/io/jpeg/old.hpp>

using namespace boost::gil;

//GIL allows us to abstract out such per-channel operations
template <typename Out>
struct halfdiff_cast_channels {
	template <typename T> Out operator()(const T& in1, const T& in2) const {
		return Out((in2 - in1) / 2);
	}
};

template <typename SrcView, typename DstView>
void x_gradient(const SrcView& src, const DstView& dst) {

	assert(src.dimensions() == dst.dimensions());

	gil_function_requires<ImageViewConcept<SrcView> >();
	gil_function_requires<MutableImageViewConcept<DstView> >();
	gil_function_requires<ColorSpacesCompatibleConcept<typename color_space_type<SrcView>::type, typename color_space_type<DstView>::type> >();

	typedef typename channel_type<DstView>::type dst_channel_t;

	for (int y = 0; y < src.height(); ++y) {
		typename SrcView::x_iterator src_it = src.row_begin(y);
		typename DstView::x_iterator dst_it = dst.row_begin(y);

		/*
		for (int c = 0; c < num_channels<SrcView>::value; ++c)
			dst_it[x][c] = (src_it[x - 1][c] - src_it[x + 1][c]) / 2;
		*/

		for (int x = 1; x < src.width() - 1; ++x) {
			//static_transform is an example of a channel-level GIL algorithm
			// Other such algorithms are static_generate, static_fill and static_for_each
			static_transform(src_it[x - 1], src_it[x + 1], dst_it[x], halfdiff_cast_channels<dst_channel_t>());
		}
	}
}

template <typename SrcView, typename DstView>
void y_gradient(const SrcView& src, const DstView& dst)
{
	x_gradient(rotated90ccw_view(src), rotated90ccw_view(dst));
}

//compute the gradient of the N-th channel of a color image
//nth_channel_view is a view transformation function that takes any view and returns a single-channel (grayscale) view of its N-th channel
template <typename SrcView, typename DstView>
void nth_channel_x_gradient(const SrcView& src, int n, const DstView& dst)
{
	x_gradient(nth_channel_view(src, n), dst);
}

template <typename SrcView, typename DstView>
void x_luminosity_gradient(const SrcView& src, const DstView& dst) {
	typedef pixel<typename channel_type<SrcView>::type, gray_layout_t> gray_pixel_t;
	x_gradient(color_converted_view<gray_pixel_t>(src), dst);
}

int main() {
	rgb8_image_t img;
	jpeg_read_image("test.jpg", img);

	gray8s_image_t img_out1(img.dimensions());
	fill_pixels(view(img_out1), gray8s_image_t::value_type(0));

	x_luminosity_gradient(const_view(img), view(img_out1));
	jpeg_write_view("out-x_gradient.jpg", color_converted_view<gray8_pixel_t>(const_view(img_out1)));

	//use second channel of source image and even pixels both horizon and verticl.
	auto imgnth = nth_channel_view(subsampled_view(view(img), 2, 2), 1);

	gray8s_image_t img_out2(imgnth.dimensions());
	fill_pixels(view(img_out2), gray8s_image_t::value_type(0));

	x_gradient(imgnth, view(img_out2));
	jpeg_write_view("out-nth_channel_sub.jpg", color_converted_view<gray8_pixel_t>(const_view(img_out2)));
	
	point_t dims(200, 200);

	gray8s_image_t img2(dims);
	fill_pixels(view(img2), rgb8_image_t::value_type(11));
	jpeg_write_view("out-gray.jpg", color_converted_view<gray8_pixel_t>(const_view(img2)));

	return 0;
}