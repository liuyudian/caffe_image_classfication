#pragma once
#include <string>
#include <vector>
#include <opencv/cv.h>
#include <sys/time.h>

using namespace cv;
using namespace std;

class API_COMMEN
{

/***********************************Common***********************************/
typedef unsigned char uchar;
typedef unsigned long long UInt64;

#define WIDTH 256
#define HEIGHT 256
#define BLOB_WIDTH 224
#define BLOB_HEIGHT 224
#define CHANNEL 3

#define BLOCKNUM 9
/***********************************public***********************************/
public:

	/// construct function 
    API_COMMEN();
    
	/// distruct function
	~API_COMMEN(void);

	/***********************************PadEnd*************************************/
	void PadEnd(char *szPath);

	/***********************************GetIDFromFilePath*************************************/
	long GetIDFromFilePath(const char *filepath);
	string GetStringIDFromFilePath(const char *filepath);

	/***********************************split***********************************/
	void split(const string& src, const string& separator, vector<string>& dest);

	/***********************************GetIDFromFilePath*************************************/
	void getRandomID( UInt64 &randomID );

	/***********************************loadWordDict*************************************/
	void loadWordDict(const char *filePath, vector< string > &labelWords);
	
	/***********************************Img_GetMutiRoi*************************************/
	int Img_GetMutiRoi( IplImage *MainBody, UInt64 ImageID, vector<Mat_<Vec3f> > &OutputImg );
	int Img_GetMutiRoi_ImageQuality( IplImage *MainBody, UInt64 ImageID, vector<Mat_<Vec3f> > &OutputImg );
	void Img_Get10MutiRoi( IplImage *MainBody, UInt64 ImageID, vector<Mat_<Vec3f> > &OutputImg );

	/***********************************Normalization*************************************/
	int Normal_MinMax( vector<float> inFeat, vector<float> &NormFeat );
	int Normal_L1( vector<float> inFeat, vector<float> &NormFeat );
	int Normal_L2( vector<float> inFeat, vector<float> &NormFeat );

	/***********************************Image Format Change*************************************/
	uchar* ipl2mat(IplImage* image);			//for matlab
	uchar* ipl2uchar(IplImage* image);		//for c/c++
	uchar* ipl2rgb(IplImage* image);	
	uchar* ipl2gray(IplImage* image);
	float* ipl2gray_f(IplImage* image);
	IplImage* uchar2ipl(uchar* bgr, int width, int height, int channel);			//for check img

	/***********************************Resize Image width && height*****************************/
	int GetReWH( int width, int height, float maxLen, int &rWidth, int &rHeight );
	int GetReWH_Minlen( int width, int height, float minLen, int &rWidth, int &rHeight );

	/***********************************ImgProcess_gaussianFilter*****************************/
	void ImgProcess_gaussianFilter(uchar* data, int width, int height, int channel);

	/***********************************Creat Sample**********************************/
	IplImage* RemoveWhitePart( IplImage *image, UInt64 ImageID );
	int CreatSample_LowContrast( IplImage *image, UInt64 ImageID, double gamma = 3.0 );
	int CreatSample_LowResolution( IplImage *image, UInt64 ImageID );
	int CreatSample_smooth( IplImage *image, UInt64 ImageID );
	int CreatSample_addGaussNoise( IplImage *image, UInt64 ImageID );

	/***********************************Extract Feat**********************************/
	int ExtractFeat_Blur( IplImage* pSrcImg, vector< float > &fBlur );				//5D
	int ExtractFeat_Constract( IplImage* pSrcImg, vector< float > &fContrast );	//4D
	double ExtractFeat_Constract_GetBlockDev(IplImage* ScaleImg);

/***********************************private***********************************/
private:

	/***********************************Img_hMirrorTrans*************************************/
	void Img_hMirrorTrans(const Mat &src, Mat &dst);

	/***********************************Creat Sample**********************************/
	int CreatSample_ImageAdjust( IplImage* src, IplImage* dst, double low, double high, double bottom, double top, double gamma ); 

	

};


/*=================================================*/
/**
 * @brief   program runtimer
 */
template<class T = double>
class RunTimer
{
	public:
	
	/*constructor*/
	RunTimer()
	:rt_start(0), rt_end(0)
	{}
	
	/*destructor*/
	~RunTimer()
	{}

	void start()
	{
		//rt_start = static_cast<T>(clock()) / CLOCKS_PER_SEC;
		//rt_end   = rt_start;
		gettimeofday(&tv_start, NULL);
		gettimeofday(&tv_end, NULL);
	}

	void end()
	{
		//rt_end = static_cast<T>(clock()) / CLOCKS_PER_SEC;
		gettimeofday(&tv_end, NULL);
	}

	T time()
	{
		//return (rt_end - rt_start);
		return static_cast<T>(timediff(&tv_start, &tv_end) / 1000000.0);
	}
	private:
	T rt_start;
	T rt_end;
	timeval tv_start;
	timeval tv_end;

	long long int timediff(timeval *start, timeval *end)
	{
		return (
				(end->tv_sec * 1000000 + end->tv_usec) -
				(start->tv_sec * 1000000 + start->tv_usec)
				);
	}
};/*RunTimer*/


	

