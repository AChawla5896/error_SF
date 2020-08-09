#include <util/accumulators/Average.h>
#include <util/containers/GArray.h>
#include <util/containers/DArray.h>
#include <util/containers/FArray.h>

#include <iostream>
#include <iterator> 
#include <fstream>

using namespace std;
using namespace Util;

int main(){

   //string InFilename = "StructureFactor.dat"
   //string OutFilename = "AvgSF.dat"
   ifstream inFileName ("StructureFactor.dat");
   ifstream IOFileName ("StructureFactor.dat");
   ofstream outFileName ("AvgSF_full.dat");
   ofstream outFileName_comp ("AvgSF.dat");
   string line;

   int nMeasure = 25000;
   int const nStar = 84;
   // Also has the SF for time = 0
   int totLines = (nStar+1)*(nMeasure+1);

   // Create a std::vector, now this vector will be of type 
   // double and will be reading the file line by line. After 
   // every reading erase the line and then by using pushback 
   // fill the vector. Then by using end fill in SF by only the 
   // last value.
   //
   // You will also need a counter to keep track of iStar. 
   // After every 84 lines need to skip a line and also reset
   // counter to fill SF.


   // SF(iStar) is the Average object which should be used to 
   // get average and error on Star iStar
   FArray <Average, nStar> SF;
  
   // This basically denotes line number that is currently being
   // read from the file. The corresponding star value would be
   // iStar-1.
   int iStar = 1; 

   // reads array of double values from the text file
   std::vector<double> readLine;

 
   // setting precision for cout
   cout.precision(17);

   int counter = 1;

   while ( getline( inFileName, line ) ) {
      std::istringstream is( line );

      readLine.insert (readLine.begin(), std::istream_iterator<double>(is), 
                         std::istream_iterator<double>() );

      cout<<counter<<"\t"<< readLine.back() << endl;
  
      counter++;

      // add sample value to iStar-1 as counting over there starts
      // from 0
      SF [iStar-1].sample(readLine.back());

      iStar++;

      if ((iStar % (nStar+1)) == 0){

         // read blank line
         getline( inFileName, line );

         //Also reinitialize the value of iStar to 1
         iStar = 1;
 
      }

      readLine.clear();
   }

   inFileName.close();

   for (iStar = 1; iStar <= nStar; iStar++){

      getline( IOFileName, line );
      std::istringstream is( line );
      readLine.insert (readLine.begin(), std::istream_iterator<double>(is), 
                         std::istream_iterator<double>() );

      outFileName<<"\t"<<readLine[0]<<"\t"<<readLine[1]<<"\t"<<readLine[2]<<"\t"
                    <<std::endl;
      outFileName_comp<<"\t"<<readLine[0]<<"\t"<<readLine[1]<<"\t"<<readLine[2]<<"\t"
         <<readLine[3]<<"\t";

      readLine.clear();
  
      SF [iStar-1].output(outFileName);
      outFileName<<std::endl<<std::endl<<std::endl;

      outFileName_comp<<SF [iStar-1].average()<<"\t"<< SF [iStar-1].blockingError()
         <<std::endl;

   }


return 0;
}
