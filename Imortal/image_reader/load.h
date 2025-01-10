#ifndef LOAD_H
# define LOAD_H

/*=- Header -=*/

// Library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include <jpeglib.h>

//local
//...

/*=- Define -=*/
//...

/*=- Typedef -=*/
//...

/*=- Macros -=*/
//...

/*=- Enums -=*/
//...

/*=- Structs -=*/

typedef struct s_png
{
	FILE		*file;
	png_structp	png_ptr;
	png_infop	info_ptr;
	png_bytep	*row_pointers;
	int			width;
	int			height;
	int			bit_depth;
	int			color_type;
	int			interlace_type;
	int			compression_type;
	int			filter_method;
	int			number_of_passes;
	int			row;
}				t_png;

typedef struct s_jpeg
{
	FILE		*file;
	struct jpeg_decompress_struct	cinfo;
	struct jpeg_error_mgr			jerr;
	unsigned char					*buffer;
	int								width;
	int								height;
	int								bit_depth;
	int								color_type;
	int								row;
}									t_jpeg;

/*=- Functions -=*/

t_png	*png_reader(const char *path);
void	free_png(t_png *png)


#endif //LOAD_H