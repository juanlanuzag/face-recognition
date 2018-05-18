#ifndef __PPMPLOADER_H__
#define __PPMLOADER_H__

#include <string>
#include <vector>

using namespace std;

typedef unsigned char uchar;

typedef
enum _PPM_LOADER_PIXEL_TYPE {
	PPM_LOADER_PIXEL_TYPE_INVALID = -1,
	PPM_LOADER_PIXEL_TYPE_RGB_8B = 0,
	PPM_LOADER_PIXEL_TYPE_RGB_16B = ( PPM_LOADER_PIXEL_TYPE_RGB_8B + 1 ),
	PPM_LOADER_PIXEL_TYPE_RGB_32B = ( PPM_LOADER_PIXEL_TYPE_RGB_16B + 1 ),
	PPM_LOADER_PIXEL_TYPE_RGB_64B = ( PPM_LOADER_PIXEL_TYPE_RGB_32B + 1 ),
	PPM_LOADER_PIXEL_TYPE_GRAY_8B = ( PPM_LOADER_PIXEL_TYPE_RGB_64B + 1 ),
	PPM_LOADER_PIXEL_TYPE_GRAY_16B = ( PPM_LOADER_PIXEL_TYPE_GRAY_8B + 1 ),
	PPM_LOADER_PIXEL_TYPE_GRAY_32B = ( PPM_LOADER_PIXEL_TYPE_GRAY_16B + 1 ),
	PPM_LOADER_PIXEL_TYPE_GRAY_64B = ( PPM_LOADER_PIXEL_TYPE_GRAY_32B + 1 )
} PPM_LOADER_PIXEL_TYPE;


struct PGMImage {
	PGMImage();

	~PGMImage();

	void load(string file);

	void save(string file, string comments);

	vector<double> data_to_vec();

	int width;
	int height;
	uchar* data;
	PPM_LOADER_PIXEL_TYPE pt;

// Para acceder al pixel i,j , hacer data[i*width + j]
};

void save_img_from_vec(string filename, vector<double> vec);
vector<double> imgvec_from_filepath(string file); 


bool LoadPPMFile(uchar** data, int *width, int *height, PPM_LOADER_PIXEL_TYPE* pt, const char *filename);
bool SavePPMFile(const char *filename, const void *src, int width, int height, PPM_LOADER_PIXEL_TYPE pt, const char* comments = NULL);

#endif //__PPMLOADER_H__
