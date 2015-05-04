// ttail.cc
// Řešení IJC-DU2, příklad b), 26.4.2015
// Autor: Radovan Sroka, FIT
// Přeloženo: g++ 4.8.2

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

#include <cstring>
#include <cstdlib>

using namespace std;

enum: int {
	N, PLUS_N
};

struct Params{
	istream* input;
	long long n;
	int mode;
};

Params params;
ifstream file;

void init(int argc, char const *argv[]){

	file.exceptions ( ifstream::failbit | ifstream::badbit );
	char * endptr = NULL;



	if (argc == 1){
		params.input = &cin;
		params.n = 10;
		params.mode = N;
	}

	else if (argc == 2){

		params.n = 10;
		params.mode = N;

		try{
			file.open(argv[1], ifstream::in);
			params.input = &file;
		}
		catch(ifstream::failure e){
			cerr << "Cannot open file" << endl;
			exit(1);
		}
	}


	else if (argc == 3){

		if (strcmp(argv[1], "-n") != 0){
			cerr << "Bad first parameter, must be -n" << endl;		
			exit(1);	
		}
		else {
			params.input = &cin;

			if (argv[2][0] == '+')
				params.mode = PLUS_N;
			else
				params.mode = N;
			
			params.n = strtoll(argv[2], &endptr, 10);
			if (*endptr != '\0'){
				cerr << "Parameter parse failed - conversion" << endl;
				exit(1);
			}
		}
	}
	

	else if (argc == 4){


		try{
			file.open(argv[3], ifstream::in);
			params.input = &file;
		}
		catch(ifstream::failure e){
			cerr << "Cannot open file" << endl;
			exit(1);
		}

		if (strcmp(argv[1], "-n") != 0){
			cerr << "Bad second parameter, must be -n" << endl;
			file.close();	
			exit(1);	
		}

		if (argv[2][0] == '+')
			params.mode = PLUS_N;
		else
			params.mode = N;

		params.n = strtoll(argv[2], &endptr, 10);
		if (*endptr != '\0'){
			cerr << "Parameter parse failed - conversion" << endl;
			file.close();
			exit(1);
		}
	}

	else {
		cerr << "Bad parameters" << endl;
		exit(1);
	}
}

void deinit(){
	try{
		file.close();
	}
	catch(ifstream:: failure e){}	
}

int plus_mode(){

	string buffer;
	params.input->exceptions(std::ifstream::failbit|std::ifstream::badbit);

	for (long long line = 1; 1 ; line++){
		try{
			getline(*params.input, buffer);
			if (line >= params.n)cout << buffer << endl;
		}
		catch(std::ifstream::failure e){
			break;
		}
	}

	return 0;
}

int normal_mode(){
	
	queue<string> fifo;

	params.input->exceptions(std::ifstream::failbit|std::ifstream::badbit);

	for (long long line = 1; 1 ; line++){
		try{
			string s;
			getline(*params.input, s);
			fifo.push(s);
			if (fifo.size() > static_cast<unsigned long long> (params.n))
				fifo.pop();
		}
		catch(std::ifstream::failure e){
			break;
		}
	}

	while(!fifo.empty()){
		cout << fifo.front() << endl;
		fifo.pop();
	}

	return 0;
}

int main(int argc, char const *argv[]){

	//ios::sync_with_stdio(false);


	init(argc, argv);


	if (params.n < 0){
		fprintf(stderr, "%s\n", "Number must be positive or zero");
		exit(1);
	}

	if (params.mode == 1){
		if (plus_mode()){
			deinit();
			exit(1);
		}
	}
	else if (params.mode == 0){ 
		if (normal_mode()){
			deinit();
			exit(1);
		}
	}

	deinit();
	return 0;
}