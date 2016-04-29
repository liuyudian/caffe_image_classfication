/************************************************************************/
/* This source code is	free for both academic and industry use.         */
/* Some important information for better using the source code could be */
/* found in the project page: http://mmcheng.net/bing					*/
/************************************************************************/

#include "stdafx.h"
#include "Objectness.h"
#include "ValStructVec.h"
#include "CmShow.h"


// Uncomment line line 14 in Objectness.cpp to remove counting times of image reading.

void RunObjectness(CStr &resName, double base, int W, int NSS, int numPerSz, CStr &dataPath);

int main(int argc, char* argv[])
{
	//DataSetVOC::importImageNetBenchMark();
	//DataSetVOC::cvt2OpenCVYml("C:/WkDir/DetectionProposals/VOC2007/Annotations/");
	if(argc < 2){
		std::cerr << "Please pass the data path to as first argument" << std::endl;
		return 1;
	}

	//datapath:"/home/chigo/working/research/Bing/Objectness-master/IN2016_Test/"
	//datapath:"/home/chigo/working/research/Bing/Objectness-master/VOC2007/"
	CStr dataPath = argv[1];
	RunObjectness("WinRecall.m", 2, 8, 2, 130, dataPath);

	//Predict
	//Predict("WinRecall.m", 2, 8, 2, 130, dataPath);
	
	return 0;
}

void RunObjectness(CStr &resName, double base, int W, int NSS, int numPerSz, CStr &dataPath)
{
	srand(131);//srand((unsigned int)time(NULL));
	//omp_set_num_threads(16);
	DataSetVOC voc2007(dataPath); 
	voc2007.loadAnnotations();
	//voc2007.loadDataGenericOverCls();

	cout << "Dataset:'" << _S(voc2007.wkDir) << "' with " << voc2007.trainNum << " training and " << voc2007.testNum << " testing" << endl;
	cout << _S(resName) << " Base = " << base << ", W = " << W << ", NSS = " << NSS << ", perSz = " << numPerSz << endl;

	printf("Objectness Init...\n");
	Objectness objNess(voc2007, base, W, NSS);
	printf("Objectness Init end!!\n");
    
	vector<vector<Vec4i>> boxes;
	//objNess.getObjBndBoxesForTests(boxes, 250);
	objNess.getObjBndBoxesForTestFast(boxes, numPerSz);
	//objNess.getObjBndBoxesForTrainsEva(boxes, numPerSz);
	//objNess.getRandomBoxes(boxes);
	//objNess.evaluatePerClassRecall(boxes, resName, 2000);
	//objNess.illuTestReults(boxes);
}

/*
void Predict(CStr &resName, double base, int W, int NSS, int numPerSz, CStr &dataPath)
{
    srand((unsigned int)time(NULL));
    DataSetVOC voc2007(dataPath);

    Objectness objNess(voc2007, base, W, NSS);

    vector<vector<Vec4i>> boxesTests;

	string inputfile = "/home/chigo/image/test/test0313_1w/7387.jpg";
    objNess.Predict( inputfile, numPerSz );
}
*/

