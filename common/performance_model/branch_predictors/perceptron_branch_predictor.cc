// this is perceptron branch predictor

#include "simulator.h"
#include "perceptron_branch_predictor.h"

PerceptronBranchPredictor::PerceptronBranchPredictor(String name, core_id_t core_id)
	: BranchPredictor(name, core_id)

{
	// perceptronTable=  new int[size][HIST_LEN]; 
	yout = 0;
	// printf("size %u\n", size); 
	for(int  i=0; i < TABLE_SIZE ; i++){
		for(int j=0; j < HIST_LEN; j++){
			perceptronTable[i][j] = 0;
		}
	}
}

PerceptronBranchPredictor::~PerceptronBranchPredictor()
{
}

bool PerceptronBranchPredictor::predict(bool indirect, IntPtr ip, IntPtr target)
{
	//reset the prediction
	int perceptronIndex = ip % TABLE_SIZE;
	int prediction = 0;
	prediction = perceptronTable[perceptronIndex][0];
	for(int i=1; i < HIST_LEN + 1; i++){
		if(ghr[i - 1] == 1){
			prediction += perceptronTable[perceptronIndex][i];   
		}
		else{
			prediction -= perceptronTable[perceptronIndex][i]; 
		}
	}
	yout = abs(prediction); 

	if(prediction >= 0)
		return 1; 
	return 0; 

}

void PerceptronBranchPredictor::update(bool predicted, bool actual, bool indirect, IntPtr ip, IntPtr target)
{
	// for performance analysis
	updateCounters(predicted, actual);       
	//update the perceptron weight
	int t ;
	if(actual == 0){
		t = -1; 
	}
	else {
		t = 1; 
	}
	int perceptronIndex = ip % TABLE_SIZE; 	
	if((predicted != actual) || yout <= threshold){
		perceptronTable[perceptronIndex][0] = perceptronTable[perceptronIndex][0] + t;
		for(int i = 1; i < HIST_LEN + 1; i++){
			perceptronTable[perceptronIndex][i] = perceptronTable[perceptronIndex][i] + t  * ghr[i-1];
		}
	}	
	// update the global history table
	ghr = (ghr << 1);
	ghr.set(0, t); 
	
}
