/* project(demo3)
 * this project is used to show bgs and sdd
 * call method : ./demo3 the video frequences path  the video output path the bgsMethodId the shadowDetectionId
 * author:wangchuanjun
 */

/* bgs include files */
#include "package_bgs/FrameDifferenceBGS.h"
#include "package_bgs/StaticFrameDifferenceBGS.h"
#include "package_bgs/WeightedMovingMeanBGS.h"
#include "package_bgs/WeightedMovingVarianceBGS.h"
#include "package_bgs/MixtureOfGaussianV1BGS.h"
#include "package_bgs/MixtureOfGaussianV2BGS.h"
#include "package_bgs/AdaptiveBackgroundLearning.h"
#include "package_bgs/AdaptiveSelectiveBackgroundLearning.h"

#if CV_MAJOR_VERSION >= 2 && CV_MINOR_VERSION >= 4 && CV_SUBMINOR_VERSION >= 3
#include "package_bgs/GMG.h"
#endif

#include "package_bgs/dp/DPAdaptiveMedianBGS.h"
#include "package_bgs/dp/DPGrimsonGMMBGS.h"
#include "package_bgs/dp/DPZivkovicAGMMBGS.h"
#include "package_bgs/dp/DPMeanBGS.h"
#include "package_bgs/dp/DPWrenGABGS.h"
#include "package_bgs/dp/DPPratiMediodBGS.h"
#include "package_bgs/dp/DPEigenbackgroundBGS.h"
#include "package_bgs/dp/DPTextureBGS.h"

#include "package_bgs/tb/T2FGMM_UM.h"
#include "package_bgs/tb/T2FGMM_UV.h"
#include "package_bgs/tb/T2FMRF_UM.h"
#include "package_bgs/tb/T2FMRF_UV.h"
#include "package_bgs/tb/FuzzySugenoIntegral.h"
#include "package_bgs/tb/FuzzyChoquetIntegral.h"

#include "package_bgs/lb/LBSimpleGaussian.h"
#include "package_bgs/lb/LBFuzzyGaussian.h"
#include "package_bgs/lb/LBMixtureOfGaussians.h"
#include "package_bgs/lb/LBAdaptiveSOM.h"
#include "package_bgs/lb/LBFuzzyAdaptiveSOM.h"

#include "package_bgs/ck/LbpMrf.h"
#include "package_bgs/jmo/MultiLayerBGS.h"
// The PBAS algorithm was removed from BGSLibrary because it is
// based on patented algorithm ViBE
// http://www2.ulg.ac.be/telecom/research/vibe/
//#include "package_bgs/pt/PixelBasedAdaptiveSegmenter.h"
#include "package_bgs/av/VuMeter.h"
#include "package_bgs/ae/KDE.h"
#include "package_bgs/db/IndependentMultimodalBGS.h"
#include "package_bgs/sjn/SJN_MultiCueBGS.h"
#include "package_bgs/bl/SigmaDeltaBGS.h"

#include "package_bgs/pl/SuBSENSE.h"
#include "package_bgs/pl/LOBSTER.h"

/* shadowdetection include files */
#include "package_sdd/ChromacityShadRem.h"
#include "package_sdd/GeometryShadRem.h"
#include "package_sdd/LrTextureShadRem.h"
#include "package_sdd/PhysicalShadRem.h"
#include "package_sdd/SrTextureShadRem.h"

/* OpenCV include files */
#include <highgui.h>
#include <opencv2/opencv.hpp>

/* resource file load */
#include <videofolder/VideoFolder.h>

/* C++ include files */
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;
using namespace cv;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<uint, uint> imgRange; 

/* function claim */
void start(VideoFolder videoFolder, uint bgsMethodId);
void bgs(); //bgs method
void sdd(); //shadowdetection method
void output();	//show the output

int main(int argc, char ** argv){

	std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;

	if(argc != 4){
		cerr << "Usage : procedure frameFromPath FrameToPath sbgsMethodId" << endl;
		return 0;
	}

	const string videoPath = argv[1];
	const string binaryPath = argv[2];

	bool error = false;
	VideoFolder videoFolder(videoPath, binaryPath);

	try {
			videoFolder.readTemporalFile();
	} catch (const string &s) {
			error = true;
			cout << "An Exception Has Occured : " << s << "\n";
	}
	
	if( !error ){
		//define bgsMethodId
		string bgsMethodIdString = argv[3];
		const uint bgsMethodId = atoi(bgsMethodIdString.c_str());


		if(bgsMethodId < 1 || bgsMethodId >37){
			cerr << "BgsMethodId Incorrect!" << endl;
			return 0;
		}

		start(videoFolder, bgsMethodId);
		
		cout << "Processing Done..." << endl;
	}
	
	return 0;
}

void start(VideoFolder videoFolder, uint bgsMethodId){

	cout << "Processing Start..." << endl;
	const imgRange range = videoFolder.getRange();
	const uint beginIdx = range.first-10;
	const uint endIdx = range.second;

	cout << "Video Frame Range From " << beginIdx << " To " << endIdx  << endl;

	/* Background Subtraction Methods */
	IBGS *bgs;

	switch(bgsMethodId){

        /*** Default Package ***/
        case 1:
            bgs = new FrameDifferenceBGS;
            break;
        case 2:
            bgs = new StaticFrameDifferenceBGS;break;
        case 3:
            bgs = new WeightedMovingMeanBGS;break;
        case 4:
            bgs = new WeightedMovingVarianceBGS;break;
        case 5:
            bgs = new MixtureOfGaussianV1BGS;break;
        case 6:
            bgs = new MixtureOfGaussianV2BGS;break;
        case 7:
            bgs = new AdaptiveBackgroundLearning;break;
        case 8:
            bgs = new AdaptiveSelectiveBackgroundLearning;break;
        case 9:
            bgs = new GMG;break;

        /*** DP Package (thanks to Donovan Parks) ***/
        case 10:
            bgs = new DPAdaptiveMedianBGS;break;
        case 11:
            bgs = new DPGrimsonGMMBGS;break;
        case 12:
            bgs = new DPZivkovicAGMMBGS;break;
        case 13:
            bgs = new DPMeanBGS;break;
        case 14:
            bgs = new DPWrenGABGS;break;
        case 15:
            bgs = new DPPratiMediodBGS;break;
        case 16:
            bgs = new DPEigenbackgroundBGS;break;
        case 17:
            bgs = new DPTextureBGS;break;

        /*** TB Package (thanks to Thierry Bouwmans, Fida EL BAF and Zhenjie Zhao) ***/
        case 18:
            bgs = new T2FGMM_UM;break;
        case 19:
            bgs = new T2FGMM_UV;break;
        case 20:
            bgs = new T2FMRF_UM;break;
        case 21:
            bgs = new T2FMRF_UV;break;
        case 22:
            bgs = new FuzzySugenoIntegral;break;
        case 23:
            bgs = new FuzzyChoquetIntegral;break;

        /*** JMO Package (thanks to Jean-Marc Odobez) ***/
        case 24:
            bgs = new MultiLayerBGS;break;

        /*** PT Package (thanks to Martin Hofmann, Philipp Tiefenbacher and Gerhard Rigoll) ***/
        //case 25:
          //  bgs = new PixelBasedAdaptiveSegmenter;break;

        /*** LB Package (thanks to Laurence Bender) ***/
        case 25:
            bgs = new LBSimpleGaussian;break;
        case 26:
            bgs = new LBFuzzyGaussian;break;
        case 27:
            bgs = new LBMixtureOfGaussians;break;
        case 28:
            bgs = new LBAdaptiveSOM;break;
        case 29:
            bgs = new LBFuzzyAdaptiveSOM;break;

        /*** LBP-MRF Package (thanks to Csaba Kertész) ***/
        case 30:
            bgs = new LbpMrf;break;

        /*** AV Package (thanks to Lionel Robinault and Antoine Vacavant) ***/
        case 31:
            bgs = new VuMeter;break;

        /*** EG Package (thanks to Ahmed Elgammal) ***/
        case 32:
            bgs = new KDE;break;

        /*** DB Package (thanks to Domenico Daniele Bloisi) ***/
        case 33:
            bgs = new IndependentMultimodalBGS;break;

        /*** SJN Package (thanks to SeungJong Noh) ***/
        case 34:
            bgs = new SJN_MultiCueBGS;break;

        /*** BL Package (thanks to Benjamin Laugraud) ***/
        case 35:
            bgs = new SigmaDeltaBGS;break;

        /*** PL Package (thanks to Pierre-Luc) ***/
        case 36:
            bgs = new SuBSENSEBGS();break;
        case 37:
            bgs = new LOBSTERBGS();break;
        default:break;
    }

    // create shadow removers
	ChromacityShadRem chr;
	PhysicalShadRem phy;
	GeometryShadRem geo;
	SrTextureShadRem srTex;
	LrTextureShadRem lrTex;

	Mat img_input;
	Mat img_mask;
	Mat img_bgmodel;
	// matrices to store the masks after shadow removal
	cv::Mat chrMask, phyMask, geoMask, srTexMask, lrTexMask;


    for (uint t = beginIdx; t <= endIdx; ++t){
    		cout << t << " Frame Is Start Computing..." << endl;

    		const string imageFromPath = videoFolder.inputFrame(t);

		cout << "Using bgsMethodId: " << bgsMethodId << endl;	
	
		img_input = cv::imread(imageFromPath);

		if(!img_input.empty()){
			imshow("imput", img_input);
		}
		

		cout << "First -> Starting Bgs...." <<endl;
		bgs->process(img_input, img_mask, img_bgmodel); // by default, it shows automatically the foreground mask image
		cout << "First -> Bgs Stoped..." << endl; 

		if(!img_mask.empty()){
			imshow("bgs -> mask", img_mask);
		}

		if(!img_bgmodel.empty()){
			imshow("bgs -> bgmodel", img_bgmodel);
		}
		
		if(!img_mask.empty() && !img_bgmodel.empty()){
			cout << "Second -> Starting Sdd..." << endl;
			chr.removeShadows(img_input, img_mask, img_bgmodel, chrMask);
			phy.removeShadows(img_input, img_mask, img_bgmodel, phyMask);
			geo.removeShadows(img_input, img_mask, img_bgmodel, geoMask);
			srTex.removeShadows(img_input, img_mask, img_bgmodel, srTexMask);
			lrTex.removeShadows(img_input, img_mask, img_bgmodel, lrTexMask);
			cout << "Second -> Sdd stoped..." << endl;
			
			// show results
			cv::imshow("chr", chrMask);
			cv::imshow("phy", phyMask);
			cv::imshow("geo", geoMask);
			cv::imshow("srTex", srTexMask);
			cv::imshow("lrTex", lrTexMask);
		}	

		cvWaitKey(0);
		
    }

  	cvDestroyAllWindows();

}
