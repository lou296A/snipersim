// some portion of the code were inspire by https://github.com/taraeicher/PerceptronBranchPredictor
#ifndef PERCEPTRON_BRANCH_PREDICTOR_H
#define PERCEPTRON_BRANCH_PREDICTOR_H

#include "branch_predictor.h"
#include <bitset>
#include <vector>
#define HIST_LEN   59 
#define threshold 127
#define TABLE_SIZE 1024
class PerceptronBranchPredictor : public BranchPredictor
{
	public:
		PerceptronBranchPredictor(String name, core_id_t core_id);
		~PerceptronBranchPredictor();

		bool predict(bool indirect, IntPtr ip, IntPtr target);
		void update(bool predicted, bool actual, bool indirect, IntPtr ip, IntPtr target);

	private:
		int yout;
		std::bitset<HIST_LEN> ghr;   
		int perceptronTable[TABLE_SIZE][HIST_LEN+1];
};

#endif
