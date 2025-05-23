#ifndef __statistics__
#define __statistics__

#include <vector>
#include <string>

class statistics {

	private:
  //variables
		int N_blocks, N_elements; 

	public: //functions

	  // Default constructor
		statistics();
	  // Destructor
		~statistics();

//set number of blocks of data to use
		void SetN (int N, int M){
			N_blocks = N;
			N_elements = M;
		}

		int GetN_blocks (){
			return N_blocks;
		} 

		int GetN_elements (){
			return N_elements;
		} 

		double error (double av, double av2, int n);

		//AVERAGE


		void block_average(std::string file, std::vector <double> &block_ave);
		//calculates block average

		void block_average(std::string file, std::string output);
		//calculates block average and saves it in a file

		void block_average(std::string file, std::vector <double> &block_ave, std::vector <double> &block_ave2);
		//calculates block average and block average squared

		void block_average_cumulative(std::string file, std::vector <double> &cumulative_ave);
		//calculates cumulative block averages and saves it in a vector

		void block_average_cumulative(std::string file, std::string output);
		//calculates cumulative block averages and saves it in a file

		void block_average_cumulative(std::string file, std::vector <double> &cumulative_ave, std::vector <double> &cumulative_ave2);
		//calculates cumulative block averages and square averages and saves it in a vector

		void block_average2_cumulative(std::string file, std::string output);
		//calculates cumulative block averages and square averages and saves it in a file

		void block_average_err(std::string file, std::string output,std::string type);
		//calculates cumulative block averages and errors and saves it in a file

		void block_average_err(std::vector <double> data, std::string output,std::string type);
		//calculates cumulative block averages and errors and saves it in a file

		void block_average_err_total(std::vector <double> data,double &mean, double &err);


		//VARIANCE

		void block_variance(std::string file, std::vector <double> &block_ave);
		//calculates block average

		void block_variance(std::string file, std::vector <double> &block_ave, std::vector <double> &block_ave2);
		//calculates block average and block average squared

		void block_variance_cumulative(std::string file, std::vector <double> &cumulative_ave);
		//calculates cumulative block averages and saves it in a vector

		void block_variance_cumulative(std::string file, std::string output);
		//calculates cumulative block averages and saves it in a file

		void block_variance_cumulative(std::string file, std::vector <double> &cumulative_ave, std::vector <double> &cumulative_ave2);
		//calculates cumulative block averages and square averages and saves it in a vector

		void block_variance2_cumulative(std::string file, std::string output);
		//calculates cumulative block averages and square averages and saves it in a file

		void block_variance_err(std::string file, std::string output);
		//calculates cumulative block averages and errors and saves it in a file

};



#endif