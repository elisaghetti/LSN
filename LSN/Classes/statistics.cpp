#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include "random.h"
#include "statistics.h"

using namespace std;

statistics :: statistics(){}
// Default constructor, does not perform any action

statistics :: ~statistics(){}
// Default destructor, does not perform any action

 double statistics ::error (double av, double av2, int n){

   if (n==0) return 0;
   else return sqrt(double((av2-av*av)/n));
}

//AVERAGE

void statistics :: block_average(string file, vector <double> &block_ave){
  ifstream in(file);
  if (in.is_open()){
  
      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi

   double sum=0;

   for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

      double r;
      in>>r;
      sum += r;
   }
   block_ave.push_back(sum/N_elements);
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void statistics :: block_average(string file, string output){
  ifstream in(file);
  ofstream out(output);
  if (in.is_open()){
  
      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi

   double sum=0;

   for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

      double r;
      in>>r;
      sum += r;
   }
  out<<sum/N_elements<<endl;
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_average(string file, vector <double> &block_ave, vector <double> &block_ave2){
  ifstream in(file);
  if (in.is_open()){
  
      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi

   double sum=0;

   for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

      double r;
      in>>r;
      sum += r;
   }
   block_ave.push_back(sum/N_elements);
   block_ave2.push_back(block_ave[i]*block_ave[i]);
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_average_cumulative(string file, vector <double> &cumulative_ave){
    ifstream in(file);
  if (in.is_open()){
    

      double sum_prog = 0;

      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi

 double block_ave=0;
       double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
          sum += r;
        }
      block_ave=sum/N_elements;
      sum_prog+=block_ave;
      cumulative_ave.push_back(sum_prog/double(i+1));
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_average_cumulative(string file, string output){
    ifstream in(file);

    ofstream out(output);
  if (in.is_open()){
    

      double sum_prog = 0;

      
      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_ave=0;;
       double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
          sum += r;
        }
      block_ave=sum/N_elements;
      sum_prog+=block_ave;
      out<<sum_prog/double(i+1);
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void statistics :: block_average_cumulative(string file, vector <double> &cumulative_ave, vector <double> &cumulative_ave2){
    ifstream in(file);
  if (in.is_open()){
   

      double sum_prog = 0;
      double sum_prog2=0;

      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_ave=0;
        double block_ave2=0;
        double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
          sum += r;
        }
      block_ave=sum/N_elements;
      block_ave2=block_ave*block_ave;
      sum_prog+=block_ave;
      sum_prog2+= block_ave2;
      cumulative_ave.push_back(sum_prog/double(i+1));
      cumulative_ave2.push_back(sum_prog2/double(i+1));

    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_average2_cumulative(string file, string output){

    ifstream in(file);
    ofstream out(output);
  if (in.is_open()){
    

      double sum_prog = 0;
      double sum_prog2=0;

      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_ave=0;
        double block_ave2=0;
        double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
          sum += r;
        }
      block_ave=sum/N_elements;
      block_ave2=block_ave*block_ave;
      sum_prog+=block_ave;
      sum_prog2+= block_ave2;
      out<<sum_prog/double(i+1)<<"\t"<<sum_prog2/double(i+1)<<endl;

    
  }

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_average_err(string file, string output, string type){

ifstream in(file);
fstream out(output, ios::in | ios::out | ios::app); // Open in read/write mode with append
if (in.is_open()){
  if (out.peek() == EOF) cerr<<"Please include header in output file"<<endl;

  else{
    double sum_prog = 0;
    double sum_prog2 = 0;

    string line;
    while (getline(out, line)) {
      if (line.empty()) {  // Found first blank line
          break;
      }

      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_ave=0;
        double block_ave2=0;
        double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
          sum += r;
        }
       
        block_ave=sum/N_elements;
        block_ave2=block_ave*block_ave;

        sum_prog+=block_ave;
        sum_prog2+= block_ave2;

        double cumulative_ave=sum_prog/double(i+1);
        double cumulative_ave2= sum_prog2/double(i+1);

        double err = error(cumulative_ave,cumulative_ave2,i+1);

        out<<type<<"\t"<<sum_prog/double(i+1)<<"\t"<<err<<endl;

      }  
    
    }


  }

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_average_err(vector <double> data, string output,string type){

fstream out(output, ios::in | ios::out | ios::app); // Open in read/write mode with append

  if (out.peek() == EOF) cerr<<"Please include header in output file"<<endl;

  else{
    double sum_prog = 0;
    double sum_prog2 = 0;


      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_ave=0;
        double block_ave2=0;
        double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          r=data[j];
          sum += r;
        }
       
        block_ave=sum/N_elements;
        block_ave2=block_ave*block_ave;

        sum_prog+=block_ave;
        sum_prog2+= block_ave2;

        double cumulative_ave=sum_prog/double(i+1);
        double cumulative_ave2= sum_prog2/double(i+1);

        double err = error(cumulative_ave,cumulative_ave2,i+1);

        out<<type<<"\t"<<sum_prog/double(i+1)<<"\t"<<err<<endl;

      }  
    
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void statistics :: block_average_err_total(vector <double> data, double &mean, double &err){

    if (data.size() != N_blocks*N_elements) cerr<<"N of blocks doesn't match data"<<endl;
    else{
    double sum_prog = 0;
    double sum_prog2 = 0;

 double cumulative_ave=0;
  double cumulative_error=0;


      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_ave=0;
        double block_ave2=0;
        double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco
          int id=i*N_elements+j;
          double r;
          r=data[id];

          sum += r;
        }
       
        block_ave=sum/N_elements;
        block_ave2=block_ave*block_ave;

        sum_prog+=block_ave;

        sum_prog2+= block_ave2;

         cumulative_ave=sum_prog/double(i+1);
         
        double cumulative_ave2= sum_prog2/double(i+1);

       cumulative_error = error(cumulative_ave,cumulative_ave2,i+1);
      }  

      mean =cumulative_ave;

      err = cumulative_error;

    }

    }

////////////////////////////////////////////////////////////////////////////////////////////////////////
//VARIANCE
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_variance(string file, vector <double> &block_var){
  ifstream in(file);
  if (in.is_open()){
  
      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi

   double sum=0;

   for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

      double r;
      in>>r;
      sum += pow((r-0.5),2);
   }
   block_var.push_back(sum/N_elements);
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_variance(string file, vector <double> &block_var, vector <double> &block_var2){
  ifstream in(file);
  if (in.is_open()){
  
      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi

   double sum=0;

   for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

      double r;
      in>>r;
      sum +=pow((r-0.5),2);
   }
   block_var.push_back(sum/N_elements);
   block_var2.push_back(block_var[i]*block_var[i]);
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_variance_cumulative(string file, vector <double> &cumulative_var){
    ifstream in(file);
  if (in.is_open()){
    

      double sum_prog = 0;

      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi

 double block_var=0;
       double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
         sum += pow((r-0.5),2);
        }
      block_var=sum/N_elements;
      sum_prog+=block_var;
      cumulative_var.push_back(sum_prog/double(i+1));
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_variance_cumulative(string file, string output){
    ifstream in(file);

    ofstream out(output);
  if (in.is_open()){
    

      double sum_prog = 0;

      
      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_var=0;;
       double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
        sum += pow((r-0.5),2);
        }
      block_var=sum/N_elements;
      sum_prog+=block_var;
      out<<sum_prog/double(i+1);
    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void statistics :: block_variance_cumulative(string file, vector <double> &cumulative_var, vector <double> &cumulative_var2){
    ifstream in(file);
  if (in.is_open()){
   

      double sum_prog = 0;
      double sum_prog2=0;

      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_var=0;
        double block_var2=0;
        double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
           sum += pow((r-0.5),2);
        }
      block_var=sum/N_elements;
      block_var2=block_var*block_var;
      sum_prog+=block_var;
      sum_prog2+= block_var2;
      cumulative_var.push_back(sum_prog/double(i+1));
      cumulative_var2.push_back(sum_prog2/double(i+1));

    }
  

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_variance2_cumulative(string file, string output){

    ifstream in(file);
    ofstream out(output);
  if (in.is_open()){
    

      double sum_prog = 0;
      double sum_prog2=0;

      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_var=0;
        double block_var2=0;
        double sum=0;

        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
        sum += pow((r-0.5),2);
        }
      block_var=sum/N_elements;
      block_var2=block_var*block_var;
      sum_prog+=block_var;
      sum_prog2+= block_var2;
      out<<sum_prog/double(i+1)<<"\t"<<sum_prog2/double(i+1)<<endl;

    
  }

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void statistics :: block_variance_err(string file, string output){


    ifstream in(file);
    fstream out(output, ios::in | ios::out | ios::app); // Open in read/write mode with append

    if (in.is_open()) {
        double sum_prog = 0;
        double sum_prog2 = 0;

        // Ensure we start writing from the first blank line
        string line;
        while (getline(out, line)) {
            if (line.empty()) {  // Found first blank line
                break;
            }


      for(int i=0; i<N_blocks; i++){ //iterazione sui blocchi
        double block_var=0;
        double block_var2=0;
        double sum=0;

      
        for(int j=0; j<N_elements; j++){ //iterazione sugli elementidel blocco

          double r;
          in>>r;
          sum += pow((r-0.5),2);
        }
       
      block_var=sum/N_elements;
      block_var2=block_var*block_var;

      sum_prog+=block_var;
      sum_prog2+= block_var2;

      double cumulative_var=sum_prog/double(i+1);
      double cumulative_var2= sum_prog2/double(i+1);

      double err = error(cumulative_var,cumulative_var2,i+1);

      out<<"VAR"<<"\t"<<cumulative_var<<"\t"<<err<<endl;

    }
  }

}
else cerr<<"PROBLEM: data file not found"<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CHI SQUARED
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

