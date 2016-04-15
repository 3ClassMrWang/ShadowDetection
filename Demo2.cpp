/*
This file is part of BGSLibrary.

BGSLibrary is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BGSLibrary is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with BGSLibrary.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <opencv2/opencv.hpp>


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

#include "videofolder/VideoFolder.h"

#include <stdio.h>
#include <sys/timeb.h>
#include <fstream>
#include <sstream>
#include <iostream>

typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<uint, uint> imgRange;

using namespace std;

//background gs method
void bgs(const string &imageFromPath, const string &imageToPath, const string &bgmodelPath, const uint &bgsMethodId);
void start(VideoFolder videoFolder, uint bgsMethodId);

//算法计时
ull getSystemTime() {
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}

int main(int argc, char **argv)
{
  	std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;
  	if(argc != 4){
		cerr << "Usage : comparator path\\to\\video\\ path\\to\\binaryFolder\\ bgsMethodId" << endl;
		return 0;
	}

	cout << "Processing bgs..." << endl;
	
	const string videoPath = argv[1];
	const string binaryPath = argv[2];
	
	cout << "\n  videoPath : " << videoPath
				<< "\n  binaryPath : " << binaryPath << endl;
	
	bool error = false;
	VideoFolder videoFolder(videoPath, binaryPath);

	try {
			videoFolder.readTemporalFile();
	} catch (const string &s) {
			error = true;
			cout << "An exception has occured : " << s << "\n";
	}
	
	if( !error ){
		//define bgsMethodId
		string bgsMethodIdString = argv[3];
		uint bgsMethodId = atoi(bgsMethodIdString.c_str());

		
		start(videoFolder,bgsMethodId);
		
		cout << "bgs done!" << endl;
	}
	
	return 0;
}


void start(VideoFolder videoFolder, uint bgsMethodId){
	cout << "staring bgs..." << endl;
	const imgRange range = videoFolder.getRange();
	//注意：一定要略微扩大处理范围
	const uint fromIdx = range.first - 10;;
	const uint toIdx = range.second;
	const string runTimePath = videoFolder.runTimeFile();
	
	cout << "imgRange From " << fromIdx << " to " << toIdx << endl;

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

	ull allTime = 0;

	for (uint t = fromIdx; t <= toIdx; ++t){
		cout << "imgIdx " << t << endl;
		//bgs(videoFolder.inputFrame(t), videoFolder.binaryFrame(t), videoFolder.bgmodelFrame(t), bgsMethodId);
		const string imageFromPath = videoFolder.inputFrame(t);
		const string imageToPath = videoFolder.binaryFrame(t);
		const string bgmodelPath = videoFolder.bgmodelFrame(t);

		if(bgsMethodId < 1 || bgsMethodId > 37){
  		cerr << "bgsMethodId not found!" << endl;
  		return;
  		}

	  	cout << "bgsMethodId is " << bgsMethodId << endl;
	  	cout << "imageFromPath is " << imageFromPath << endl;
	  	cout << "imageToPath is " << imageToPath << endl;
	  	cout << "bgmodelPath is " << bgmodelPath << endl;

	 	cv::Mat img_input;
	 	cv::Mat img_mask;
	 	cv::Mat img_bgmodel;

		img_input = cv::imread(imageFromPath);

		cout << "starting bgs process..." << endl;
		
		ull begin = getSystemTime();
		bgs->process(img_input, img_mask, img_bgmodel); // by default, it shows automatically the foreground mask image
		ull end = getSystemTime();

		allTime += (end - begin);		
  
		cout << "single process done!" << endl; 

		//if(!img_mask.empty())
		//	cv::imshow("Foreground", img_mask);

		 //  do something
		    
		if(!img_mask.empty()){
		    cv::imwrite(imageToPath,img_mask);
		    cout << "save mask..." << endl;
		}


		if(!img_bgmodel.empty()){
		    cv::imwrite(bgmodelPath,img_bgmodel);
		    cout << "save bgmodel" << endl;
	    }
	}
	
	double averageTime = (allTime*1.0) / toIdx;
	ofstream ofile(runTimePath, ios::out);
	ofile << averageTime;
	ofile.close();
}
