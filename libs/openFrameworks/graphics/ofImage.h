#pragma once


#include "ofFileUtils.h"
#include "ofTexture.h"
#include "ofPixels.h"
#include "ofBaseTypes.h"
#include "ofConstants.h"

enum ofImageQualityType {
	OF_IMAGE_QUALITY_BEST,
	OF_IMAGE_QUALITY_HIGH,
	OF_IMAGE_QUALITY_MEDIUM,
	OF_IMAGE_QUALITY_LOW,
	OF_IMAGE_QUALITY_WORST
};

//----------------------------------------------------
// FreeImage based stuff:
bool ofLoadImage(ofPixels & pix, string path);
bool ofLoadImage(ofPixels & pix, const ofBuffer & buffer);

bool ofLoadImage(ofFloatPixels & pix, string path);
bool ofLoadImage(ofFloatPixels & pix, const ofBuffer & buffer);

bool ofLoadImage(ofTexture & tex, string path);
bool ofLoadImage(ofTexture & tex, const ofBuffer & buffer);

void ofSaveImage(ofPixels & pix, string path, ofImageQualityType qualityLevel = OF_IMAGE_QUALITY_BEST);
void ofSaveImage(ofPixels & pix, ofBuffer & buffer, ofImageQualityType qualityLevel = OF_IMAGE_QUALITY_BEST);

void ofSaveImage(ofFloatPixels & pix, string path, ofImageQualityType qualityLevel = OF_IMAGE_QUALITY_BEST);
void ofSaveImage(ofFloatPixels & pix, ofBuffer & buffer, ofImageQualityType qualityLevel = OF_IMAGE_QUALITY_BEST);

// when we exit, we shut down ofImage
void ofCloseFreeImage();

//----------------------------------------------------
template<typename T>
class ofImage_ : public ofBaseImage_<T>{

	public :

		ofImage_();
		virtual ~ofImage_();

		ofImage_(const ofPixels_<T> & pix);
		ofImage_(const ofFile & file);
		ofImage_(const string & filename);

		// alloation / deallocation routines
		void 				allocate(int w, int h, ofImageType type);
		void 				clear();

		// default copy overwriting (for = or std::vector)
		ofImage_(const ofImage_<T>& mom);
		ofImage_<T>& operator= (const ofImage_<T>& mom);

		// copying:
		void 				clone(const ofImage_<T> &mom);

		// enable or disable using the texture of this image
		void 				setUseTexture(bool bUse);
		bool				isUsingTexture();

		//for getting a reference to the texture
		ofTexture & getTextureReference();

		// quick texture binding shortcut
		void bind();
		void unbind();

		// file loading / saving
		bool 				loadImage(string fileName);
		bool				loadImage(const ofBuffer & buffer);
		bool 				loadImage(const ofFile & file);
		void 				saveImage(string fileName, ofImageQualityType compressionLevel = OF_IMAGE_QUALITY_BEST);
		void 				saveImage(ofBuffer & buffer, ofImageQualityType compressionLevel = OF_IMAGE_QUALITY_BEST);
		void 				saveImage(const ofFile & file, ofImageQualityType compressionLevel = OF_IMAGE_QUALITY_BEST);

		//Sosolimited: texture compression and mipmaps
		void				setCompression(ofTexCompression compression);

		// getting the data
		T * 				getPixels();			// up to you to get this right
		ofPixels_<T> &	 	getPixelsRef();

		operator ofPixels_<T>&();

		ofColor getColor(int x, int y) const;

		// alter the image
		void setColor(int x, int y, ofColor color);
		void 				setFromPixels(const T * pixels, int w, int h, ofImageType type, bool bOrderIsRGB = true);
		void				setFromPixels(const ofPixels_<T> & pixels);
		void 				setImageType(ofImageType type);
		void 				resize(int newWidth, int newHeight);
		void 				grabScreen(int x, int y, int w, int h);		// grab pixels from opengl, using glreadpixels
		// this does an inplace crop. 
		// NOTE: this reallocates memory.
		void				crop(int x, int y, int w, int h); 
		// this does a crop from another image.
		// NOTE: this will reallocate memory if the image types are different, or if the w & h do not
		// equal this images w & h
		void				cropFrom(ofImage_<T> & otherImage, int x, int y, int w, int h);
		// perform rotation of 90 degress clockwise rotation amont times. 
		void				rotate90(int rotation);
		void				mirror(bool vertical, bool horizontal); 
	
	
	
		// if you've altered the pixels (e.g., from getPixels())
		// call update() to see a change (move the pixels to the texture)
		void update();

		//the anchor is the point the image is drawn around.
		//this can be useful if you want to rotate an image around a particular point.
        void				setAnchorPercent(float xPct, float yPct);	//set the anchor as a percentage of the image width/height ( 0.0-1.0 range )
        void				setAnchorPoint(float x, float y);				//set the anchor point in pixels
        void				resetAnchor();								//resets the anchor to (0, 0)

		// draw:
		void 				draw(const ofRectangle & r);
		void 				draw(const ofPoint & p, float w, float h);
		void 				draw(float x, float y, float w, float h);
		void 				draw(float x, float y, float z, float w, float h);
		void 				draw(const ofPoint & p);
		void 				draw(float x, float y);
		void 				draw(float x, float y, float z);

		float 				getHeight();
		float 				getWidth();
		bool 				bAllocated() {return pixels.isAllocated();};

		void				reloadTexture();

		int 				width, height, bpp;		// w,h, bits per pixel
		int					type;					// OF_IMAGE_GRAYSCALE, OF_IMAGE_COLOR, OF_IMAGE_COLOR_ALPHA

		ofImage_<T> & operator=(ofPixels_<T> & pixels);
	protected:
	
		void				changeTypeOfPixels(ofPixels_<T> &pix, ofImageType type);
		void				resizePixels(ofPixels_<T> &pix, int newWidth, int newHeight);

		ofPixels_<T>		pixels;
		bool				bUseTexture;
		ofTexture			tex;

};

typedef ofImage_<unsigned char> ofImage;
typedef ofImage_<float> ofFloatImage;



