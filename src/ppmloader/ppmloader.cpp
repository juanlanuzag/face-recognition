#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ppmloader.h"


/*
 * src = Image pointer
 * pt  = Image type
 *			PPM_LOADER_PIXEL_TYPE_RGB_8B:  Image is organized by rows with colors interleaved
 *			PPM_LOADER_PIXEL_TYPE_GRAY_XB: Image is organized by rows with no colors and X bits per pixel
*/
bool SavePPMFile(const char *filename, const void *src, int width, int height, PPM_LOADER_PIXEL_TYPE pt, const char* comments)
{
	if (filename == NULL || src == NULL)
	{
		return false;
	}

	FILE* fid = fopen(filename,"wb");
	if(!fid){
		printf("ERROR opening file %s\n",filename);
		return false;
	}
	int pix_size = 0;
	switch( pt )
	{
		case PPM_LOADER_PIXEL_TYPE_RGB_8B:
			fprintf(fid, "P6\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%i\n", width, height, 255);
			pix_size = 3; // 3 bytes
			break;
		case PPM_LOADER_PIXEL_TYPE_RGB_16B:
			fprintf(fid, "P6\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%i\n", width, height, 65535);
			pix_size = 3*2; // 6 bytes
			break;
		case PPM_LOADER_PIXEL_TYPE_RGB_32B:
			fprintf(fid, "P6\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%li\n", width, height, 4294967295);
			pix_size = 3*4; // 12 bytes
			break;
		case PPM_LOADER_PIXEL_TYPE_RGB_64B:
			fprintf(fid, "P6\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%li\n", width, height, 18446744073709551615U);
			pix_size = 3*8; // 24 bytes
			break;

		case PPM_LOADER_PIXEL_TYPE_GRAY_8B:
			fprintf(fid, "P5\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%i\n", width, height, 255);
			pix_size = 1; // 1 bytes
			break;
		case PPM_LOADER_PIXEL_TYPE_GRAY_16B:
			fprintf(fid, "P5\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%i\n", width, height, 65535);
			pix_size = 2; // 2 bytes
			break;
		case PPM_LOADER_PIXEL_TYPE_GRAY_32B:
			fprintf(fid, "P5\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%li\n", width, height, 4294967295);
			pix_size = 4; // 4 bytes
			break;
		case PPM_LOADER_PIXEL_TYPE_GRAY_64B:
			fprintf(fid, "P5\n");
			if (comments)
			{
				fprintf(fid,"#%s\n",comments);
			}
			fprintf(fid, "%i %i\n%li\n", width, height, 18446744073709551615U);
			pix_size = 8; // 8 bytes
			break;
		case PPM_LOADER_PIXEL_TYPE_INVALID:
			printf("ERROR invalid PPM_LOADER_PIXEL_TYPE\n");
			return false;
			break;
		default:
			printf("ERROR unrecognized PPM_LOADER_PIXEL_TYPE\n");
			return false;
			break;
	}
	int bytes_written = fwrite(src,1,width*height*pix_size,fid);
	bool ret = bytes_written == width*height*pix_size;

	fclose(fid);

	return ret;
}


// Remember to free data
bool LoadPPMFile(uchar** data, int *width, int *height, PPM_LOADER_PIXEL_TYPE* pt, const char *filename)
{
	if (data == NULL || width== NULL || height == NULL || pt == NULL || filename == NULL)
	{
		return false;
	}
	// Open file
	FILE* fid = fopen(filename, "rb");
	if (!fid) {
		printf("PPM load error: file access denied %s\n", filename);
		return false;
	}
	// Read PPM/PGM header P5/P6
	int channels = 0;
	char line[256];
    char *ptr;
	fgets(line, 256, fid);

	if ( line[0]=='P' && line[1]=='5' ) {
		channels = 1;
	} else if ( line[0]=='P' && line[1]=='6' ) {
		channels = 3;
	} else {
		printf("Wrong image type\n");
		return false;
	}

  if (line[2] == '\n') {
    // fgets(line, 256, fid);

    // Parse comments
    fgets(line, 256, fid);
    while(line[0]=='#')
      fgets(line, 256, fid);

    ptr = line;
  } else
    ptr = line + 3;

  // Read dimensions
  *width = strtol(ptr, &ptr, 10);
  *height = strtol(ptr, &ptr, 10);
  if(ptr == NULL || *ptr == '\n'){
    fgets(line, 256, fid);
    ptr = line;
  }

	// Read pixel depth
  int levels = strtol(ptr, &ptr, 10);
  int pixel_depth = 0;
	if (channels==3 && (levels == 255)) {
		*pt = PPM_LOADER_PIXEL_TYPE_RGB_8B;
		pixel_depth = 1;
	}else if (channels==3 && levels == 65535) {
		*pt = PPM_LOADER_PIXEL_TYPE_RGB_16B;
		pixel_depth = 2;
	} else if (channels==3 && levels == 4294967295) {
		*pt = PPM_LOADER_PIXEL_TYPE_RGB_32B;
		pixel_depth = 4;
	} else if (channels==3 && levels == 18446744073709551615U) {
		*pt = PPM_LOADER_PIXEL_TYPE_RGB_64B;
		pixel_depth = 8;
	}else if (levels == 255) {
		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_8B;
		pixel_depth = 1;
	}else if (levels == 65535) {
		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_16B;
		pixel_depth = 2;
	} else if (levels == 4294967295) {
		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_32B;
		pixel_depth = 4;
	} else if (levels == 18446744073709551615U) {
		*pt = PPM_LOADER_PIXEL_TYPE_GRAY_64B;
		pixel_depth = 8;
	} else {
		printf("ERROR: Wrong number of levels\n");
		return false;
	}

	// Read raw data from file
	int size = (*width) * (*height) * channels * pixel_depth;
	*data = new uchar[size];
	fread(*data, 1, size, fid);
	fclose(fid);

	return true;
}



PGMImage::PGMImage()
	: width(0), height(0), data(NULL), pt(PPM_LOADER_PIXEL_TYPE_INVALID) {};

PGMImage::~PGMImage() {
	delete [] data;
	data = NULL;
}

void PGMImage::load(string filename) {

	bool ret = LoadPPMFile(&data, &width, &height, &pt, filename.c_str());
    if (!ret || width == 0|| height == 0|| pt!=PPM_LOADER_PIXEL_TYPE_GRAY_8B) {
      	cerr << "Image Loading failed" << endl;
    }
}


void PGMImage::save(string filename, string comments) {
	bool ret = SavePPMFile(filename.c_str(),data,width,height,PPM_LOADER_PIXEL_TYPE_GRAY_8B, comments.c_str());
	if (!ret) {
	  cerr << "Image save failed" << endl;
	}
}


vector<double> PGMImage::data_to_vec() {
	int len = width * height;
	vector<double> res(len, 0);
	for (int i = 0; i < len; i++){
		double elem = (double)(data[i]);
		res[i] = elem >= 0 ? elem : 256 + elem;
    }
	return res;
}

vector<double> imgvec_from_filepath(string file) {
	PGMImage img;
	img.load(file);
	return  img.data_to_vec();
}

void save_img_from_vec(string filename, vector<double> vec) {
	double max = -1e10;
	double min = 1e10;
	for (unsigned int i=0; i < vec.size(); i++) {
		if (max <= vec[i]) max= vec[i];
		if (min > vec[i]) min= vec[i];
	}
	PGMImage img;
	img.pt=PPM_LOADER_PIXEL_TYPE_GRAY_8B;
	img.data = new uchar[vec.size()];
	for (unsigned int i=0; i < vec.size(); i++) {
		img.data[i] = (uchar)(255 * (vec[i] - min)/(max - min));
	}
	if (vec.size() == 10304 ) {
		img.width = 92;
		img.height = 112;
	} else {
		img.width = 23;
		img.height = 28;
	}
	img.save(filename, "soy un autovector");


}