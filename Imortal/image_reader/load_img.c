/* Big Header */

#include "load.h"


/** @todo doc && opti */
t_png	*png_reader(const char *path)
{
	FILE		*file = NULL;
	t_png		*png = NULL;
	int			y;

	file = fopen(path, "rb");
	if (!file)
		return (perror("png_reader cannot open the file"), NULL);
	png = calloc(1, sizeof(t_png));
	if (!png)
		return (perror("png_reader cannot allocate memory"), NULL);
	png->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png->png_ptr)
	{
		fclose(file);
		free(png);
		return (perror("png_reader cannot create read struct"), NULL);
	}
	png->info_ptr = png_create_info_struct(png->png_ptr);
	if (!png->info_ptr)
	{
		png_destroy_read_struct(&png->png_ptr, NULL, NULL);
		fclose(file);
		free(png);
		return (perror("png_reader cannot create info struct"), NULL);
	}

	png_init_io(png->png_ptr, file);
	png_read_info(png->png_ptr, png->info_ptr);
	png->width = png_get_image_width(png->png_ptr, png->info_ptr);
	png->height = png_get_image_height(png->png_ptr, png->info_ptr);

	png->bit_depth = png_get_bit_depth(png->png_ptr, png->info_ptr);
	if (png->bit_depth == 16)
		png_set_strip_16(png->png_ptr);

	png->color_type = png_get_color_type(png->png_ptr, png->info_ptr);
	if (png->color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png->png_ptr);
	if (png->color_type == PNG_COLOR_TYPE_GRAY && png->bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png->png_ptr);
	if (png->color_type == PNG_COLOR_TYPE_GRAY || png->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png->png_ptr);

	png->interlace_type = png_get_interlace_type(png->png_ptr, png->info_ptr);
	png->compression_type = png_get_compression_type(png->png_ptr, png->info_ptr);
	png->filter_method = png_get_filter_type(png->png_ptr, png->info_ptr);
	png->number_of_passes = png_set_interlace_handling(png->png_ptr);

	png->row_pointers = calloc(png->height, sizeof(png_bytep));
	if (!png->row_pointers)
	{
		png_destroy_read_struct(&png->png_ptr, &png->info_ptr, NULL);
		fclose(file);
		free(png);
		return (perror("png_reader cannot allocate memory"), NULL);
	}
	y = 0;
	while (y < png->height)
	{
		png->row_pointers[y] = calloc(1, png_get_rowbytes(png->png_ptr, png->info_ptr));
		if (!png->row_pointers[y])
		{
			png_destroy_read_struct(&png->png_ptr, &png->info_ptr, NULL);
			fclose(file);
			free(png->row_pointers);
			free(png);
			return (perror("png_reader cannot allocate memory"), NULL);
		}
		y++;
	}
	png_read_image(png->png_ptr, png->row_pointers);
	fclose(file);
	return (png);
}

void	free_png(t_png *png)
{
	int	y;

	if (!png)
		return ;
	y = 0;
	while (y < png->height)
	{
		free(png->row_pointers[y]);
		y++;
	}
	free(png->row_pointers);
	png_destroy_read_struct(&png->png_ptr, &png->info_ptr, NULL);
	free(png);
}

t_jpeg	*jpeg_reader(const char *path)
{
	FILE	*file = NULL;
	t_jpeg	*jpeg = NULL;
	int		y;

	file = fopen(path, "rb");
	if (!file)
		return (perror("jpeg_reader cannot open the file"), NULL);
	jpeg = (t_jpeg *)calloc(1, sizeof(t_jpeg));
	if (!jpeg)
		return (perror("jpeg_reader cannot allocate memory"), NULL);
	jpeg->cinfo.err = jpeg_std_error(&jpeg->jerr);
	jpeg_create_decompress(&jpeg->cinfo);
	jpeg_stdio_src(&jpeg->cinfo, file);
	jpeg_read_header(&jpeg->cinfo, TRUE);
	jpeg_start_decompress(&jpeg->cinfo);

	jpeg->width = jpeg->cinfo.output_width;
	jpeg->height = jpeg->cinfo.output_height;
	jpeg->bit_depth = jpeg->cinfo.output_components;
	jpeg->color_type = jpeg->cinfo.out_color_space;
	jpeg->buffer = (unsigned char *)calloc(jpeg->width * jpeg->height
											* jpeg->bit_depth, sizeof(unsigned char));
	if (!jpeg->buffer)
	{
		jpeg_finish_decompress(&jpeg->cinfo);
		jpeg_destroy_decompress(&jpeg->cinfo);
		fclose(file);
		free(jpeg);
		return (perror("jpeg_reader cannot allocate memory"), NULL);
	}
	y = 0;
	while (y < jpeg->height)
	{
		jpeg->row = jpeg_read_scanlines(&jpeg->cinfo, &jpeg->buffer, 1);
		if (jpeg->row != 1)
		{
			jpeg_finish_decompress(&jpeg->cinfo);
			jpeg_destroy_decompress(&jpeg->cinfo);
			fclose(file);
			free(jpeg->buffer);
			free(jpeg);
			return (perror("jpeg_reader cannot read scanlines"), NULL);
		}
		y++;
	}
	jpeg_finish_decompress(&jpeg->cinfo);
	jpeg_destroy_decompress(&jpeg->cinfo);
	fclose(file);
	return (jpeg);
}

void	*read_img(const char *path)
{
	(void)path;
	return (NULL);
}

int	main(void)
{
	t_png	*png = png_reader("test.png");
	t_jpeg	*jpeg = jpeg_reader("test.jpg");

	printf("png: %p\n", png);
	printf("jpeg: %p\n", jpeg);

	return (0);
}