#include<iostream>
#include<string>
#include<stdio.h>
#include<sstream>
#include<vector>
#include <utility>

using namespace std;

/*Jeremy Chen
CS 340
Professor Svadlenka
Project 4
*/


int main() {
	//initilization
	bool input = true;
	int userInput = 0;
	//program description
	cout << "This is a best fit, contiguous memory allocator." << endl;
	cout << "Please enter './allocator_JChen' along with the initial memory block size" << endl;

	//counters
	double initialSize, initialSizeLeft, sizeCounter=0, sizeCounterAfter=0;
	//looped this so that if you make a mistake, you can try again
	while (input == true) {
		std::string str_1, maxSize;
		std::cin >> str_1 >> maxSize;
		if (str_1 == "./allocator_JChen") {
			initialSize = std::stoi(maxSize);
			initialSizeLeft = initialSize;
			input = false;
		}
		else {
			cout << "Wrong command, check spelling and try again" << endl;
		}


	}


	string command1, processName, memSize;
	double memSizeNum;
	string bestFit;
	double bestFitNum;
	string isFree;
	double bestFitIndex = -1;
	double tempMin, actualMin = 0;
	//used vectors for this because of its dynamic feature
	vector<pair<string, double>> arr;
	cin.ignore();
	//loop for user input prompts
	while (userInput == 0) {
		string command = "";
		cout << "allocator>";
		//used getline so it doesnt just take the first word
		std::getline(cin, command);
		//request command, std::string::npos checks for the word in the given user command
		if (command.find("RQ") != std::string::npos) {
			
			std::istringstream iss(command);
			iss >> command1 >> processName >> memSize;
			//user input was string so i changed it to double so i can put in vector
			// its double just in case
			memSizeNum = stod(memSize);
			//for the first rq. 
			if (arr.size() == 0) {

				if (memSizeNum > initialSizeLeft) {
					cout << "input memory exceeds block memory size. try again." << endl;
				}
				if (memSizeNum < initialSizeLeft) {
					arr.push_back(make_pair(processName, memSizeNum));
					initialSizeLeft = initialSizeLeft - memSizeNum;
				}
			}
			//if vector isnt empty, loop through vector to check for best fit partition
			else if (arr.size() > 0) {
				//loop through memory block by size
				for (int i = 0; i < arr.size(); i++) {
					isFree = arr[i].first;

					//check to see if the partition fits
					if (memSizeNum <= arr[i].second && ((isFree).compare("FREE") == 0)) {
						//if it fits, store it as temperary value to find smallest partition that fits. 
						tempMin = arr[i].second;
						if (actualMin == 0) {
							actualMin = arr[i].second;
							bestFitIndex = i;
						}
						if (tempMin < actualMin) {
							actualMin = tempMin;
							bestFitIndex = i;
						}

					}

				}
				actualMin = 0;
				//if we actually found a best fit partition, then...
				if (bestFitIndex != -1) {
					//insert
					arr.insert(arr.begin() + bestFitIndex, (make_pair(processName, memSizeNum)));
					initialSizeLeft = initialSizeLeft - memSizeNum;
					
					if ((arr[bestFitIndex + 1].second) - memSizeNum != 0) {
						arr[bestFitIndex + 1].second = arr[bestFitIndex + 1].second - memSizeNum;
					}
					else if ((arr[bestFitIndex + 1].second) - memSizeNum == 0) {
						arr.erase(arr.begin() + bestFitIndex + 1);
					}
				}
				else {
					arr.push_back(make_pair(processName, memSizeNum));
					initialSizeLeft = initialSizeLeft - memSizeNum;
				}
				//testing for me. easier for me to visualize table when coding
				/*for (int i = 0; i < arr.size(); i++) {
					cout << arr[i].first << " " << arr[i].second << endl;
				}
				cout << bestFitIndex << " " << initialSizeLeft << endl;
				bestFitIndex = -1;*/
				


			}
		

		}
		//release command. see npos explaination for request command.
		else if (command.find("RL") != std::string::npos) {
			std::istringstream iss(command);
			iss >> command1 >>processName;
			//just in case you try to release when no processes are in memory block
			if (arr.size() == 0) {
				cout << "no process is in block yet. Please run the program over again." << endl;
			}

			string tempStringValue;
			//loop through vector
			for (int i = 0; i < arr.size(); i++) {
				tempStringValue = arr[i].first;
				int tempValue1 = i;
				//try to find matching process as what you put into the command
				if (tempStringValue.compare(processName) == 0) {
					double tempNumValue = arr[i].second;
					//replacing process with free. The memory still exists but just is a hole
					arr.erase(arr.begin()+i );
					arr.insert(arr.begin()+i , (make_pair("FREE", tempNumValue)));
				}
			}
			//testing for me. easier for me to visualize table when coding
			/*for (int i = 0; i < arr.size(); i++) {
				cout << arr[i].first << " " << arr[i].second << endl;
			}
			cout << arr.size();*/
			
		}
		//compact command
		else if (command.find("C") != std::string::npos) {
			std::istringstream iss(command);
			iss >> command1;
			//just in case you try to compact if there are no holes
			if (arr.size() == 0) {
				cout << "no process is in block yet. Please run the program over again." << endl;
			}
			string tempStringValue;
			//loop through vector
			for (int i = 0; i < arr.size(); i++) {
				tempStringValue = arr[i].first;
				if (tempStringValue.compare("FREE") == 0) {
					double tempNumValue = arr[i].second;
					arr.erase(arr.begin() + i);
					initialSizeLeft = initialSizeLeft + tempNumValue;
				}
			}
			//testing for me. easier for me to visualize table when coding
			/*for (int i = 0; i < arr.size(); i++) {
				cout << arr[i].first << " " << arr[i].second << endl;
			}*/
			
			
		}//show table. 
		else if (command.find("STAT") != std::string::npos) {
			std::istringstream iss(command);
			iss >> command1;
			//loop through vector size
			for (int i = 0; i < arr.size(); i++) {
				sizeCounterAfter = sizeCounterAfter + arr[i].second;
				cout << "Addresses [" << sizeCounter << " : " << sizeCounterAfter<< "] Process " << arr[i].first << endl;
				sizeCounter = sizeCounter + arr[i].second;
				}
			//just the remainder or last memory partition block
			cout << "Addresses [" << sizeCounter << " : END] Process Free" << endl;
			sizeCounterAfter = 0;
			sizeCounter = 0;
		}
		//quit command
		else if (command.find("QUIT") != std::string::npos) {
			return 0;
		}
		//error throwing
		else { cout << "Invalid command input. Please put a correct command." << endl; }

	}
}