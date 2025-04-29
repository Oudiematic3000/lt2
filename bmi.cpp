// KJN - it is good practice to insert comment about intended use, context, contributors, etc
// This is a program intended to output the BMIs of a list of individuals given their weights and heights in a data file as input.
// The program is originally authored by Ken Nixon and Moris Scofield Mukwayi for the purpose of a lab test on 29/04/2025
// Modified by Ariel Oudmayer as per the lab test's instructions and with use of doctest as a testing framework.

#include <iostream>
#include <fstream>
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <cmath>

using namespace std;

double ounces2pounds(int x)
{
    return((double)x/16); //Ounce to pound conversion is 16 ounces to 1 pound. Return type changed to double for precision.
}

TEST_CASE("testing ounces2pounds function"){
    CHECK(ounces2pounds(16)==1);
    CHECK(ounces2pounds(8)==0.5);
    CHECK(ounces2pounds(1)==0.0625);
    CHECK(ounces2pounds(0)==0);
    CHECK(ounces2pounds(55)==3.4375);
}

int stones2pounds(int x)
{
    return(x*14);
}

TEST_CASE("testing stones2pounds function"){
    CHECK(stones2pounds(1)==14);
    CHECK(stones2pounds(8)==112);
    CHECK(stones2pounds(0)==0);
    CHECK(stones2pounds(999)==13986);
}

double weight2kg(int stones, int pounds, int ounces)
{
    return (stones2pounds(stones)+pounds+ounces2pounds(ounces))/2.2;
}

TEST_CASE("testing weight2kg function") {
    CHECK(weight2kg(1,1,1) == doctest::Approx(6.84659));//Approx used because of floating point precision errors when comparing doubles.
    CHECK(weight2kg(0,0,0) == 0);
    CHECK(weight2kg(1,0,16) == doctest::Approx(6.81818)); 
}

double height2metres(int feet, int inches)
{
    double nFeet=(double)inches/12;
    return(((double)feet+nFeet)/3.28);  //Need to add inches after converting them to feet. ints casted to double for precision. Conversion ratio 3.82 => 3.28 .
}

TEST_CASE("testing height2metres function") {
    CHECK(height2metres(1,12) == doctest::Approx(0.609756));
    CHECK(height2metres(0,0) == 0);
}

char categorise(double kg, double metre)
{
    if(metre==0){char cat='D'; return(cat);} //Error handling for height of 0.
    double bmi = kg/(metre*metre);  // BMI equation is weight divided by height squared.
    char cat;
    if (bmi<19)
        cat='A';
    else if (bmi<25)    //Category B is not less than 19 but less than 25
        cat='B';
    else if (bmi<30)    //Category C is not less than 25 but less than 30
        cat='C';
    else
        cat='D';
    return(cat);
}

TEST_CASE("testing categorise function") {
    CHECK(categorise(0,0) == 'D');
    CHECK(categorise(44,1.68) == 'A');
    CHECK(categorise(64,1.73) == 'B');
    CHECK(categorise(70,1.65) == 'C');
    CHECK(categorise(101,1.7) == 'D');
    CHECK(categorise(999,0.5) == 'D');
}

void process_data(char* input_file, char* output_file)
{
    ifstream f_in;
    ofstream f_out;
    string data;
    string person_id;
    int pounds, stones, ounces, feet, inches;
    double kg, m;
    int cat;

    f_in.open(input_file,ios::in);
    f_out.open(output_file,ofstream::out);
    while (!f_in.eof())
    {
    	f_in >> person_id >> stones >> pounds >> ounces >> feet >> inches;
        kg=weight2kg(int(stones),int(pounds),int(ounces)); 
        m =height2metres(int(feet),int(inches));
        cat=categorise(kg,m);
	f_out << person_id << " " << cat << endl;
    }
    f_in.close();
    f_out.close();
}
        
int main(int argc, char *argv[])
{
    doctest::Context context;
    int res = context.run();
    if(context.shouldExit())return res;
    // KJN - Need to check that 3 arguments were supplied upon execution
    if(argc!=3){
        cout<<"Program requires 3 arguments."<<endl;
        cout<<"Usage: ./<fileName> <inputFile> <outputFile>"<<endl;
        return 1;
    }
    process_data(argv[1], argv[2]);
    return res;   
}
