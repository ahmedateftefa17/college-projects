/**
 * @Author  Ahmed Aatef Abdelwhab
 *          Faculty Of Engineering, Ain Shams University
 *          Computer and Systems Engineering, Electrical Department
 *          1st Year, 2nd semester
 * @Course  CSE121
 * @Date    Jun 2016
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

unsigned int const __Year_28__ = 365;
unsigned int const __MaxMonths_28__[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
unsigned int const __Year_29__ = 366;
unsigned int const __MaxMonths_29__[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

string eraseChar(string handle, char handleRemoveChar) {
	for (unsigned int stringIndex = 0; stringIndex < handle.length(); stringIndex++) 
		if (handle[stringIndex] == handleRemoveChar) handle.erase(handle.begin() + stringIndex);
	return handle;
}
string getString(string handle, char startChar, char endChar) {
	string result;
	for (unsigned int i = handle.find(startChar) + 1; i < handle.find(endChar); i++) result += handle[i];
	return result;
}
string replaceCharBetween(string handle, char startChar, char replaceChar, char replaceCharBy, char endChar) {
	for (unsigned int stringIndex = 0; stringIndex < handle.length(); stringIndex++)
		if (handle[stringIndex] == startChar)
			for (; handle[stringIndex] != endChar; stringIndex++)
				if (handle[stringIndex] == replaceChar) handle[stringIndex] = replaceCharBy;
	return handle;
}
vector<string> explodeString(string handle, char splittingChar) {
	vector<string> result;
	for (unsigned int stringIndex = 0, vectorIndex = 0; stringIndex < handle.length(); stringIndex++)
		if (handle[stringIndex] != splittingChar) {
			result.resize(vectorIndex + 1);
			result[vectorIndex] += handle[stringIndex];
		}
		else vectorIndex++;
	return result;
}
vector<vector<string>> explodeArray(vector<string> handle, char splittingChar) {
	vector<vector<string>> result;
	for (unsigned int vectorIndex = 0; vectorIndex < handle.size(); vectorIndex++) {
		result.resize(vectorIndex + 1);
		result[vectorIndex] = explodeString(handle[vectorIndex], splittingChar);
	}
	return result;
}

class Date {
	private:
		unsigned int day, month, year;
	public:
		Date() { this->day = 1, this->month = 1, this->year = 1970; /* 01/01/1970 Standard initial date */ }
		Date(string handleDate) {
			vector<string> handleDateArrayString_ = explodeString(handleDate, '/');
			this->day = atoi(handleDateArrayString_[0].c_str());
			this->month = atoi(handleDateArrayString_[1].c_str());
			this->year = atoi(handleDateArrayString_[2].c_str());
		}
		unsigned int getDay() { return this->day; }
		unsigned int getMonth() { return this->month; }
		unsigned int getYear() { return this->year; }
		string stringForm() { return to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);}
		bool yearIsLeap(unsigned int handleYear) {
			if ( (handleYear % 4 == 0 && handleYear % 100 != 0 ) || handleYear % 400 == 0) return true;
			return false;
		}
		unsigned int days() {
			unsigned int dateDays = 0;	// 01/01/1970 Standard Start date
			for (unsigned int i = 1970; i < this->year; i++)
				if (this->yearIsLeap(i)) dateDays += __Year_29__;
				else dateDays += __Year_28__;
			for (unsigned int i = 1; i < this->month; i++)
				if (this->yearIsLeap(i)) dateDays += __MaxMonths_29__[i];
				else dateDays += __MaxMonths_28__[i];
			dateDays += this->day;
			return dateDays;
		}
};
class Course {
	private:
		string id = "DEF000";
		string name = "Default Name";
		Date date = Date();
		string hall = "DEF1";
		vector<unsigned int> studentIds;
		unsigned int studentsNumber = 0;
		unsigned int minStudyDays = 999999999; // Not good enough but it works !
	public:
		Course() {
			this->id = "DEF000";
			this->name = "Default Name";
			this->date = Date();
			this->hall = "DEFA1";
		}
		Course(string handleId, string handleName, Date handleDate, string handleHall) {
			this->id = handleId;
			this->name = handleName;
			this->date = handleDate;
			this->hall = eraseChar(handleHall, ' ');
		}
		void addStudentId(unsigned int studentId) {
			this->studentIds.resize(this->studentIds.size() + 1);
			this->studentIds[this->studentIds.size() - 1] = studentId;
			studentsNumber = this->studentIds.size();
		}
		void setMinStudyDays(unsigned int handleMinStudyDays) { this->minStudyDays = handleMinStudyDays; }
		void setHall(string handle) { this->hall = handle; }
		void setDate(Date handle) { this->date = handle; }
		string getId() { return this->id; }
		string getName() { return this->name; }
		string getHall() { return this->hall; }
		Date getDate() { return this->date; }
		vector<unsigned int> getStudentIds() { return this->studentIds; }
		unsigned int getStudentsNumber() { return this->studentsNumber; }
		unsigned int getMinStudyDays() { return this->minStudyDays; }
};
class Student {
	private:
		unsigned int id;
		string name;
		vector<Course> courses;
		vector<unsigned int> studyDays;
	public:
		Student() {}
		Student(unsigned int handleId, string handleName, vector<Course> handleCourses) {
			this->id = handleId;
			this->name = handleName;
			this->courses = handleCourses;
		}
		void setStudyDays(unsigned int index, unsigned int days) {
			this->studyDays.resize(this->courses.size());
			this->studyDays[index] = days;
		}
		void setCourses(vector<Course> handleCourses) { this->courses = handleCourses; }
		unsigned int getId() { return this->id; }
		string getName() { return this->name; }
		vector<Course> getCourses() { return this->courses; }
		vector<unsigned int> getStudyDays() { return this->studyDays; }
};
class Controller {
	private:
	public:
		Controller() {}
		static void setCourseStudentsNumber(vector<Course> &handleCourses, vector<Student> handleStudents) {
			for (unsigned int i = 0; i < handleCourses.size(); i++)
				for (unsigned int j = 0; j < handleStudents.size(); j++)
					for (unsigned int k = 0; k < handleStudents[j].getCourses().size(); k++)
						if (handleCourses[i].getId() == handleStudents[j].getCourses()[k].getId())
							handleCourses[i].addStudentId(handleStudents[j].getId());
		}
		static void setStudentStudyDays(vector<Student> &handleStudents, vector<Date> handleDates) {
			for (unsigned int i = 0; i < handleStudents.size(); i++) {
				vector<Course> temp = handleStudents[i].getCourses();
				vector<Date> DatesSorted, Dates;
				Dates.resize(temp.size());
				for (unsigned int j = 0; j < temp.size(); j++)	Dates[j] = temp[j].getDate();
				DatesSorted = Controller::sortDates(Dates);
				handleStudents[i].setCourses(Controller::sortCourses(temp));
				handleStudents[i].setStudyDays(0, 7);
				for (unsigned int j = 1; j < handleStudents[i].getCourses().size(); j++)
					handleStudents[i].setStudyDays(j, Controller::getPeriod(DatesSorted[j], DatesSorted[j - 1]) - 1);
			}
		}
		static void setSameDayCourses(vector<Student> &handleStudents) {
			for (unsigned int i = 0; i < handleStudents.size(); i++)
				for (unsigned int j = 0; j < handleStudents[i].getCourses().size(); j++)
					if (handleStudents[i].getStudyDays()[j] == 4294967295) {
						handleStudents[i].setStudyDays(j, 0);
						handleStudents[i].setStudyDays(j - 1, 0);
					}
		}
		static void setCourseMinStudyDays(vector<Course> &handleCourses, vector<Student> handleStudents) {
			for (unsigned int i = 0; i < handleCourses.size(); i++)
				for (unsigned int j = 0; j < handleStudents.size(); j++)
					for (unsigned int k = 0; k < handleStudents[j].getCourses().size(); k++)
						if (handleStudents[j].getCourses()[k].getId() == handleCourses[i].getId() && handleStudents[j].getStudyDays()[k] < handleCourses[i].getMinStudyDays())
							handleCourses[i].setMinStudyDays(handleStudents[j].getStudyDays()[k]);
		}
		static Date getMinDate(vector<Date> handleDates) {
			Date minDate = handleDates[0];
			for (unsigned int i = 1; i < handleDates.size(); i++)
				if (handleDates[i].days() < minDate.days())
					minDate = handleDates[i];
			return minDate;
		}
		static Date getMaxDate(vector<Date> handleDates) {
			Date maxDate = handleDates[0];
			for (unsigned int i = 1; i < handleDates.size(); i++)
				if (handleDates[i].days() > maxDate.days())
					maxDate = handleDates[i];
			return maxDate;
		}
		static unsigned int getPeriod(Date maxDate, Date minDate) { return maxDate.days() - minDate.days(); }
		static vector<Date> getUniqDates(vector<Course> handleCourses) {
			vector<Date> uniqList;
			unsigned int uniqListIndex = 0;
			for (unsigned int i = 0; i < handleCourses.size(); i++) {
				bool repeated = false;
				for (unsigned int j = 0; j < uniqList.size(); j++) if (handleCourses[i].getDate().days() == uniqList[j].days()) repeated = true;
				if (repeated) continue;
				uniqList.resize(uniqListIndex + 1);
				uniqList[uniqListIndex] = handleCourses[i].getDate();
				uniqListIndex++;
			}
			return uniqList;
		}
		static vector<Date> sortDates(vector<Date> handleDates) {
			vector<Date> result(handleDates.size());
			unsigned int k = 0;
			while (handleDates.size() > 0){
				Date min = Controller::getMinDate(handleDates);
				unsigned int index;
				for (unsigned int i = 0; i < handleDates.size(); i++)
					if (handleDates[i].days() == min.days())
						index = i;
				handleDates.erase(handleDates.begin() + index);
				result[k] = min;
				k++;
			}
			return result;
		}
		static vector<Course> sortCourses(vector<Course> handleCourses) {
			vector<Course> sortedCourses(handleCourses.size());
			for (unsigned int i = 0, index = 0; i < handleCourses.size(); i++, index = 0) {
				Date min = handleCourses[index].getDate();
				for (unsigned int j = 0; j < handleCourses.size(); j++) {
					if (handleCourses[j].getDate().days() < min.days()) {
						index = j;
						min = handleCourses[j].getDate();
					}
				}
				sortedCourses[i] = handleCourses[index];
				handleCourses[index].setDate(Date("31/12/3520"));
			}
			return sortedCourses;
		}
		static vector<Date> getDates(Date startDate, Date endDate) {
			vector<Date> result(1);
			result[0] = (to_string(startDate.getDay()) + "/" + to_string(startDate.getMonth()) + "/" + to_string(startDate.getYear()));
			unsigned int resultDay = startDate.getDay(), resultMonth = startDate.getMonth(), resultYear = startDate.getYear();
			for (unsigned int i = 1; true; i++) {
				if (resultDay == endDate.getDay() && resultMonth == endDate.getMonth() && resultYear == endDate.getYear()) break;
				if (startDate.yearIsLeap(resultYear))
					if (resultDay < __MaxMonths_29__[resultMonth]) resultDay++;
					else if (resultMonth == 12) {
						resultMonth = 1;
						resultYear += 1;
						resultDay = 1;
					}
					else {
						resultMonth += 1;
						resultDay = 1;
					}
				else 
					if (resultDay < __MaxMonths_28__[resultMonth]) resultDay++;
					else if (resultMonth == 12) {
						resultMonth = 1;
						resultYear += 1;
						resultDay = 1;
					}
					else {
						resultMonth += 1;
						resultDay = 1;
					}
				result.resize(i + 1);
				result[i] = Date(to_string(resultDay) + "/" + to_string(resultMonth) + "/" + to_string(resultYear));
			}

			return result;
		}
		static vector<string> getUniqHalls(vector<Course> handleCourses) {
			vector<string> uniqList;
			unsigned int uniqListIndex = 0;
			for (unsigned int i = 0; i < handleCourses.size(); i++) {
				bool repeated = false;
				for (unsigned int j = 0; j < uniqList.size(); j++) if (handleCourses[i].getHall() == uniqList[j]) repeated = true;
				if (repeated) continue;
				uniqList.resize(uniqListIndex + 1);
				uniqList[uniqListIndex] = handleCourses[i].getHall();
				uniqListIndex++;
			}
			return uniqList;
		}
		static unsigned int getMinId(vector<Student> handleStudents) {
			unsigned int min = handleStudents[0].getId();
			for (unsigned int i = 1; i < handleStudents.size(); i++) if (handleStudents[i].getId() < min) min = handleStudents[i].getId();
			return min;
		}
		static unsigned int getMaxId(vector<Student> handleStudents) {
			unsigned int max = handleStudents[0].getId();
			for (unsigned int i = 1; i < handleStudents.size(); i++) if (handleStudents[i].getId() > max) max = handleStudents[i].getId();
			return max;
		}
		static vector<unsigned int> getDroppedIds(vector<Student> handleStudents) {
			unsigned int min = Controller::getMinId(handleStudents), max = Controller::getMaxId(handleStudents);
			vector<unsigned int> result;
			for (unsigned int i = min, k = 0; i < max; i++) {
				bool exist = false;
				for (unsigned int j = 0; j < handleStudents.size(); j++) if (handleStudents[j].getId() == i) exist = true;
				if (exist) continue;
				result.resize(k+1);
				result[k] = i;
				k++;
			}
			return result;
		}
		static Student getStudent(unsigned int handleId, vector<Student> handleStudents) {
			for (unsigned int i = 0; i < handleStudents.size(); i++) if (handleStudents[i].getId() == handleId) return handleStudents[i];
			return Student();
		}
		static vector<Course> getCourse(string handle, vector<Course> handleCourses) {
			vector<Course> result(0);
			handle = eraseChar(handle, ' ');
			for (unsigned int i = 0, k = 0; i < handleCourses.size(); i++){
				if (handleCourses[i].getId() == handle) {
					result.resize(k + 1);
					result[k] = handleCourses[i];
					k++;
				}
				else if (handleCourses[i].getName() == handle) {
					result.resize(k + 1);
					result[k] = handleCourses[i];
					k++;
				}
				else if (handleCourses[i].getHall() == handle) {
					result.resize(k + 1);
					result[k] = handleCourses[i];
					k++;
				}
				else if (handleCourses[i].getDate().stringForm() == handle) {
					result.resize(k + 1);
					result[k] = handleCourses[i];
					k++;
				}
			}
			return result;
		}
		static unsigned int getMinIndex(vector<unsigned int> handle) {
			unsigned int min = 0;
			for (unsigned int i = 1; i < handle.size(); i++) if(handle[i] < handle[min]) min = i;
			return min;
		}
		static unsigned int getMaxIndex(vector<unsigned int> handle) {
			unsigned int max = 0;
			for (unsigned int i = 1; i < handle.size(); i++) if (handle[i] > handle[max]) max = i;
			return max;
		}
};

int main() {
	// >> Initialization Main Variables
	string Courses, Students, Command;
	vector<string> Courses_, Students_, UniqHalls_;
	vector<vector<string>> Courses__, Students__;
	// >> Initialization Main Objects Arrys
	vector<Course> Courses_OV;
	vector<Student> Students_OV, tempStudent_;
	vector<Date> Dates_OV_Uniq, Dates_OV_Uniq_Sorted, tempDate_;
	// >> Get Data
	getline(cin, Courses);
	getline(cin, Students);
	// >> Check |NOT Necessary|
	if (Courses.length() == 0 || Students.length() == 0) return 1;
	// >> Construct Courses__
	Courses = getString(Courses, '[', ']');
	Courses_ = explodeString(Courses, ';');
	Courses__ = explodeArray(Courses_, ',');
	Courses_OV.resize(Courses__.size());
	// >> Construct Students__
	Students = getString(Students, '[', ']');
	Students = replaceCharBetween(Students, '(', ',', '&', ')');
	Students_ = explodeString(Students, ';');
	Students__ = explodeArray(Students_, ',');
	Students_OV.resize(Students__.size());
	// >> Check |NOT Necessary|
	for (unsigned int i = 0; i < Students__.size(); i++) if (Students__[i].size() != 3) return 2;
	for (unsigned int i = 0; i < Courses__.size(); i++) if (Courses__[i].size() != 4) return 3;
	// >> Construct Courses_OV
	for (unsigned int i = 0; i < Courses__.size(); i++) Courses_OV[i] = Course(Courses__[i][0], Courses__[i][1], Date(Courses__[i][2]), Courses__[i][3]);
	// >> Construct Students_OV
	for (unsigned int i = 0; i < Students__.size(); i++) {
		vector<string> tempString_ = explodeString(getString(Students__[i][2], '(', ')'), '&');
		vector<Course> tempCourse_(tempString_.size());
		for (unsigned int j = 0; j < tempString_.size(); j++)
			if (Controller::getCourse(tempString_[j], Courses_OV).size() !=0) tempCourse_[j] = Controller::getCourse(tempString_[j], Courses_OV)[0];
			else tempCourse_[j] = Course();
		Students_OV[i] = Student(unsigned(atoi(Students__[i][0].c_str())), Students__[i][1], tempCourse_);
	}
	// >> Get Dates_OV_Uniq
	Dates_OV_Uniq = Controller::getUniqDates(Courses_OV);
	Dates_OV_Uniq_Sorted = Controller::sortDates(Dates_OV_Uniq);
	// >> Get UniqHalls_
	UniqHalls_ = Controller::getUniqHalls(Courses_OV);
	// >> Setup a littel more information
	Controller::setCourseStudentsNumber(Courses_OV, Students_OV);
	Controller::setStudentStudyDays(Students_OV, Dates_OV_Uniq_Sorted);
	Controller::setSameDayCourses(Students_OV);
	Controller::setCourseMinStudyDays(Courses_OV, Students_OV);
	// >> START
	string CommandLine;
	getline(cin, CommandLine);
	vector<string> CommandLineArray;
	if (CommandLine.length() != 0) {
		CommandLineArray = explodeString(CommandLine, ' ');
		Command = CommandLineArray[0];
	}
	else Command = "EMPTY";
	// >> Looping
	while (Command != "Quit") {
		// >> Print Command's Result
		if (Command == "Number_Students") cout << Students__.size() << endl;
		else if (Command == "Number_Courses") cout << Courses__.size() << endl;
		else if (Command == "Number_Halls") cout << UniqHalls_.size() << endl;
		else if (Command == "Student_ID_Max") cout << Controller::getMaxId(Students_OV) << endl;
		else if (Command == "Student_ID_Min") cout << Controller::getMinId(Students_OV) << endl;
		else if (Command == "Students_Dropped_IDs")
			if (Controller::getDroppedIds(Students_OV).size() != 0)
				for (unsigned int i = 0; i < Controller::getDroppedIds(Students_OV).size(); i++)
					cout << Controller::getDroppedIds(Students_OV)[i] << endl;
			else cout << "none" << endl;
		else if (Command == "Exams_Start_Date") cout << Controller::getMinDate(Dates_OV_Uniq_Sorted).stringForm() << endl;
		else if (Command == "Exams_End_Date") cout << Controller::getMaxDate(Dates_OV_Uniq_Sorted).stringForm() << endl;
		else if (Command == "Exams_Period_InDays") cout << Controller::getPeriod(Controller::getMaxDate(Dates_OV_Uniq_Sorted), Controller::getMinDate(Dates_OV_Uniq_Sorted)) + 1 << endl;
		else if (Command == "Student_Courses") 
			if (Controller::getStudent(unsigned(atoi(CommandLineArray[1].c_str())), Students_OV).getCourses().size() != 0)
				for (unsigned int i = 0; i < Controller::getStudent(unsigned(atoi(CommandLineArray[1].c_str())), Students_OV).getCourses().size(); i++)
					cout << Controller::getStudent(unsigned(atoi(CommandLineArray[1].c_str())), Students_OV).getCourses()[i].getId() << endl;
			else cout << "none" << endl;
		else if (Command == "Course_Students")
			if (Controller::getCourse(CommandLineArray[1], Courses_OV)[0].getStudentIds().size() != 0)
				for (unsigned int i = 0; i <  Controller::getCourse(CommandLineArray[1], Courses_OV)[0].getStudentIds().size(); i++)
					cout << Controller::getCourse(CommandLineArray[1], Courses_OV)[0].getStudentIds()[i] << endl;
			else cout << "none" << endl;
		else if (Command == "List_Course_Students") {
			bool existsResult = false;
			for (unsigned int i = 0; i < Courses_OV.size(); i++)
				if (CommandLineArray[1] == "More" && Courses_OV[i].getStudentsNumber() > unsigned(atoi(CommandLineArray[2].c_str()))) {
					cout << Courses_OV[i].getId() << endl;
					existsResult = true;
				}
				else if (CommandLineArray[1] == "Less" && Courses_OV[i].getStudentsNumber() < unsigned(atoi(CommandLineArray[2].c_str()))) {
					cout << Courses_OV[i].getId() << endl;
					existsResult = true;
				}
				else if (CommandLineArray[1] == "Equal" && Courses_OV[i].getStudentsNumber() == unsigned(atoi(CommandLineArray[2].c_str()))) {
					cout << Courses_OV[i].getId() << endl;
					existsResult = true;
				}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_Student_Courses") {
			bool existsResult = false;
			for (unsigned int i = 0; i < Students_OV.size(); i++)
				if (CommandLineArray[1] == "More" && Students_OV[i].getCourses().size() > unsigned(atoi(CommandLineArray[2].c_str()))) {
					cout << Students_OV[i].getId() << endl;
					existsResult = true;
				}
				else if (CommandLineArray[1] == "Less" && Students_OV[i].getCourses().size() < unsigned(atoi(CommandLineArray[2].c_str()))) {
					cout << Students_OV[i].getId() << endl;
					existsResult = true;
				}
				else if (CommandLineArray[1] == "Equal" && Students_OV[i].getCourses().size() == unsigned(atoi(CommandLineArray[2].c_str()))) {
					cout << Students_OV[i].getId() << endl;
					existsResult = true;
				}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_Hall_Students") {
			string _InputHall, _InputDate;
			if (CommandLineArray.size() == 2) {
				_InputHall = explodeString(CommandLineArray[1], ',')[0];
				_InputDate = explodeString(CommandLineArray[1], ',')[1];
			}
			else if (CommandLineArray.size() == 3) {
				_InputHall = CommandLineArray[1];
				_InputHall = eraseChar(_InputHall, ',');
				_InputDate = CommandLineArray[2];
			}
			bool existsResult = false;
			for (unsigned int i = 0; i < Students_OV.size(); i++)
				if (Controller::getCourse(_InputHall, Controller::getCourse(_InputDate, Students_OV[i].getCourses())).size() != 0) {
					cout << Students_OV[i].getId() << endl;
					existsResult = true;
				}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_Hall_Students_InAnyday") {
			string _InputHall = CommandLineArray[1];
			bool existsResult = false;
			for (unsigned int i = 0; i < Students_OV.size(); i++)
				if (Controller::getCourse(_InputHall, Students_OV[i].getCourses()).size() != 0) {
					cout << Students_OV[i].getId() << endl;
					existsResult = true;
				}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_Day_Students_InAnyHall") {
			string _InputDate = CommandLineArray[1];
			bool existsResult = false;
			for (unsigned int i = 0; i < Students_OV.size(); i++)
				if (Controller::getCourse(_InputDate, Students_OV[i].getCourses()).size() != 0) {
					cout << Students_OV[i].getId() << endl;
					existsResult = true;
				}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_Exams") {
			string _InputDate = CommandLineArray[1];
			bool existsResult = false;
			for (unsigned int i = 0; i < Controller::getCourse(_InputDate, Courses_OV).size(); i++) {
				cout << Controller::getCourse(_InputDate, Courses_OV)[i].getId() << endl;
				existsResult = true;
			}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_StudyDays") {
			string StudentId, CourseId;
			if (CommandLineArray.size() == 2) {
				StudentId = explodeString(CommandLineArray[1], ',')[0];
				CourseId = explodeString(CommandLineArray[1], ',')[1];
			}
			else if (CommandLineArray.size() == 3) {
				StudentId = eraseChar(CommandLineArray[1], ',');
				CourseId = CommandLineArray[2];
			}
			for (unsigned int i = 0; i < Controller::getStudent(unsigned(atoi(StudentId.c_str())), Students_OV).getCourses().size(); i++)
				if (Controller::getStudent(unsigned(atoi(StudentId.c_str())), Students_OV).getCourses()[i].getId() == CourseId)
					cout << Controller::getStudent(unsigned(atoi(StudentId.c_str())), Students_OV).getStudyDays()[i] << endl;
		}
		else if (Command == "List_StudyDays_ForEveryStudent") {
			string CourseId = CommandLineArray[1];
			for (unsigned int i = 0; i < Students_OV.size(); i++)
				for (unsigned int j = 0; j < Controller::getStudent(Students_OV[i].getId(), Students_OV).getCourses().size(); j++)
					if (Controller::getStudent(Students_OV[i].getId(), Students_OV).getCourses()[j].getId() == CourseId)
						cout << Students_OV[i].getId() << " " << Controller::getStudent(Students_OV[i].getId(), Students_OV).getStudyDays()[j] << endl;
		}
		else if (Command == "List_StudyDays_ForEveryCourse") {
			unsigned int StudentId = unsigned(atoi(CommandLineArray[1].c_str()));
			for (unsigned int i = 0; i < Controller::getStudent(StudentId, Students_OV).getCourses().size(); i++)
				cout << Controller::getStudent(StudentId, Students_OV).getCourses()[i].getId() << " " 
				<< Controller::getStudent(StudentId, Students_OV).getStudyDays()[i] << endl;
		}
		else if (Command == "List_Minimum_Student_StudyDays") {
			unsigned int StudentId = unsigned(atoi(CommandLineArray[1].c_str()));
			unsigned int _Index = Controller::getMinIndex(Controller::getStudent(StudentId, Students_OV).getStudyDays());
			cout << Controller::getStudent(StudentId, Students_OV).getCourses()[_Index].getId() << " " 
				<< Controller::getStudent(StudentId, Students_OV).getStudyDays()[_Index] << endl;
		}
		else if (Command == "List_Minimum_Course_StudyDays") cout << Controller::getCourse(CommandLineArray[1], Courses_OV)[0].getMinStudyDays() << endl;
		else if (Command == "List_Minimum_StudyDays") {
			unsigned int _Index = 0;
			for (unsigned int i = 1; i < Courses_OV.size(); i++)
				if (Courses_OV[i].getMinStudyDays() < Courses_OV[_Index].getMinStudyDays()) _Index = i;
			cout << Courses_OV[_Index].getMinStudyDays() << endl;
		}
		else if (Command == "List_Exam_InSameDay") {
			unsigned int StudentId = unsigned(atoi(CommandLineArray[1].c_str()));
			bool existsResult = false, _FirstChain = true;
			for (unsigned int i = 1; i < Controller::getStudent(StudentId, Students_OV).getCourses().size(); i++)
				if (Controller::getStudent(StudentId, Students_OV).getCourses()[i].getDate().stringForm()
					== Controller::getStudent(StudentId, Students_OV).getCourses()[i - 1].getDate().stringForm()) {
					if (_FirstChain) {
						cout << Controller::getStudent(StudentId, Students_OV).getCourses()[i - 1].getId() << endl
							<< Controller::getStudent(StudentId, Students_OV).getCourses()[i].getId() << endl;
						_FirstChain = false;
					}
					else cout << Controller::getStudent(StudentId, Students_OV).getCourses()[i].getId() << endl;
					existsResult = true;
				}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_Exam_InSameDay_ForEveryStudent") {
			for (unsigned int k = 0; k < Students_OV.size(); k++) {
				bool existsResult = false, _FirstChain = true;
				string printedDate = "";
				cout << Students_OV[k].getId();
				for (unsigned int i = 1; i < Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses().size(); i++)
					if (Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses()[i].getDate().stringForm()
						== Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses()[i - 1].getDate().stringForm()) {
						if (printedDate != Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses()[i].getDate().stringForm() && printedDate != "") {
							_FirstChain = true;
						}
						if (_FirstChain) {
							cout << " " << Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses()[i - 1].getId()
								<< " " << Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses()[i].getId();
							_FirstChain = false;
							printedDate = Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses()[i].getDate().stringForm();
						}
						else cout << " " << Controller::getStudent(Students_OV[k].getId(), Students_OV).getCourses()[i].getId();
						existsResult = true;
					}
				if (!existsResult) cout << " none" << endl; else cout << endl;
			}
		}
		else if (Command == "List_Exam_InSameHall") {
			string Date = CommandLineArray[1];
			vector<Course> TempCOV = Courses_OV;
			bool existsResult = false, _FirstChain = true;
			for (unsigned int i = 0; i < TempCOV.size(); i++)
				for (unsigned int j = i + 1; j < TempCOV.size(); j++)
					if (TempCOV[i].getDate().stringForm() == Date && TempCOV[j].getDate().stringForm() == Date 
						&& TempCOV[i].getHall() == TempCOV[j].getHall() && TempCOV[j].getHall() != "TemP$#$ComparinG#$#HalL") {
						if (_FirstChain) {
							cout << TempCOV[i].getId() << endl << TempCOV[j].getId() << endl;
							_FirstChain = false;
						}
						else cout << TempCOV[j].getId() << endl;
						TempCOV[i].setHall("TemP$#$ComparinG#$#HalL");
						existsResult = true;
					}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "List_Exam_InSameHall_Simultaneously_InAnyDay") {
			for (unsigned int k = 0; k < Dates_OV_Uniq_Sorted.size(); k++) {
				vector<Course> TempCOV = Courses_OV;
				bool existsResult = false, _FirstChain = true;
				cout << Dates_OV_Uniq_Sorted[k].stringForm();
				for (unsigned int i = 0; i < TempCOV.size(); i++)
					for (unsigned int j = i + 1; j < TempCOV.size(); j++)
						if (TempCOV[i].getDate().stringForm() == Dates_OV_Uniq_Sorted[k].stringForm() && TempCOV[j].getDate().stringForm() == Dates_OV_Uniq_Sorted[k].stringForm()
							&& TempCOV[i].getHall() == TempCOV[j].getHall() && TempCOV[j].getHall() != "TemP$#$ComparinG#$#HalL") {
							if (_FirstChain) {
								cout << " " << TempCOV[i].getId() << " " << TempCOV[j].getId();
								_FirstChain = false;
							}
							else cout << " " << TempCOV[j].getId();
							TempCOV[i].setHall("TemP$#$ComparinG#$#HalL");
							existsResult = true;
						}
				if (!existsResult) cout << " none" << endl; else cout << endl;
			}
		}
		else if (Command == "Reschedule_Course_InSameHall_InDifferentDay") {
			string tempParameters;
			for (unsigned int i = 1; i < CommandLineArray.size(); i++) tempParameters += CommandLineArray[i];
			vector<string> tempString = explodeString(tempParameters, ',');
			string CourseId = tempString[0], StartDate = tempString[1], EndDate = tempString[2];
			vector<Date> _InputDates = Controller::getDates(Date(StartDate), Date(EndDate));
			Course _InputCourse = Controller::getCourse(CourseId, Courses_OV)[0];
			bool existsResult = false;
			vector<Course> tempCourses = Courses_OV;
			vector<Student> tempStudents = Students_OV;
			for (unsigned int i = 0; i < _InputDates.size(); i++) {
				// >> Construct tempCourses
				for (unsigned int j = 0; j < Courses__.size(); j++)
					if (Courses__[j][0] == _InputCourse.getId())
						tempCourses[j] = Course(Courses__[j][0], Courses__[j][1], _InputDates[i], Courses__[j][3]);
					else
						tempCourses[j] = Course(Courses__[j][0], Courses__[j][1], Date(Courses__[j][2]), Courses__[j][3]);
				// >> Construct tempStudents
				for (unsigned int j = 0; j < Students__.size(); j++) {
					vector<string> tempString_ = explodeString(getString(Students__[j][2], '(', ')'), '&');
					vector<Course> tempCourse_(tempString_.size());
					for (unsigned int k = 0; k < tempString_.size(); k++)
						if (Controller::getCourse(tempString_[k], tempCourses).size() != 0) tempCourse_[k] = Controller::getCourse(tempString_[k], tempCourses)[0];
						else tempCourse_[k] = Course();
						tempStudents[j] = Student(unsigned(atoi(Students__[j][0].c_str())), Students__[j][1], tempCourse_);
				}
				vector<Date> tempDates_OV_Uniq_Sorted = Controller::sortDates(Controller::getUniqDates(tempCourses));
				Controller::setCourseStudentsNumber(tempCourses, tempStudents);
				Controller::setStudentStudyDays(tempStudents, Dates_OV_Uniq_Sorted);
				Controller::setSameDayCourses(tempStudents);
				Controller::setCourseMinStudyDays(tempCourses, tempStudents);
				bool existCourseConflict = false;
				for (unsigned int j = 0; j < tempCourses.size(); j++)
					for (unsigned int k = 0; k < tempCourses.size(); k++)
						if (j != k && tempCourses[j].getDate().stringForm() == tempCourses[k].getDate().stringForm() && tempCourses[j].getHall() == tempCourses[k].getHall())
							existCourseConflict = true;
				bool existStudentConflict = false;
				for (unsigned int v = 0; v < tempStudents.size(); v++)
					for (unsigned int j = 0; j < tempStudents[v].getCourses().size(); j++)
						for (unsigned int k = 0; k < tempStudents[v].getCourses().size(); k++)
							if (j != k && tempStudents[v].getCourses()[j].getDate().stringForm() == tempStudents[v].getCourses()[k].getDate().stringForm())
								existCourseConflict = true;
				if (!existCourseConflict && !existStudentConflict) {
					cout << _InputDates[i].stringForm() << endl;
					existsResult = true;
					Courses_OV = tempCourses;
					Students_OV = tempStudents;
					break;
				}
			}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "Reschedule_Course_InSameDay_InDifferentHall") {
			Course _InputCourse = Controller::getCourse(CommandLineArray[1],Courses_OV)[0];
			bool existsResult = false;
			for (unsigned int i = 0; i < UniqHalls_.size(); i++) {
				_InputCourse.setHall(UniqHalls_[i]);
				bool existsConflict = false;
				for (unsigned int j = 0; j < Courses_OV.size(); j++)
					if (_InputCourse.getHall() == Courses_OV[j].getHall() && _InputCourse.getDate().stringForm() == Courses_OV[j].getDate().stringForm())
						existsConflict = true;
				if (!existsConflict) {
					cout << UniqHalls_[i] << endl;
					for (unsigned int j = 0; j < Courses_OV.size(); j++)
						if (Courses_OV[j].getId() == _InputCourse.getId())
							Courses_OV[j].setHall(_InputCourse.getHall());
					existsResult = true;
					break;
				}
			}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "Reschedule_Course_InSameHall_To_Reach_Minimum_StudyDays") {
			string tempParameters;
			for (unsigned int i = 1; i < CommandLineArray.size(); i++) tempParameters += CommandLineArray[i];
			vector<string> temp = explodeString(tempParameters, ',');
			string StartDate = temp[2], EndDate = temp[3];
			vector<Course> tempCourses = Courses_OV;
			vector<Student> tempStudents = Students_OV;
			vector<Date> _InputDates = Controller::getDates(Date(StartDate), Date(EndDate));
			Course _InputCourse = Controller::getCourse(temp[0], Courses_OV)[0];
			Date oldDate = Date();
			unsigned int  MinStudyDays = unsigned(atoi(temp[1].c_str()));
			bool existsResult = false;
			for (unsigned int i = 0; i < _InputDates.size(); i++) {
				// >> Construct tempCourses
				for (unsigned int j = 0; j < Courses__.size(); j++) 
					if (Courses__[j][0] == _InputCourse.getId())
						tempCourses[j] = Course(Courses__[j][0], Courses__[j][1], _InputDates[i], Courses__[j][3]);
					else 
						tempCourses[j] = Course(Courses__[j][0], Courses__[j][1], Date(Courses__[j][2]), Courses__[j][3]);
				// >> Construct tempStudents
				for (unsigned int j = 0; j < Students__.size(); j++) {
					vector<string> tempString_ = explodeString(getString(Students__[j][2], '(', ')'), '&');
					vector<Course> tempCourse_(tempString_.size());
					for (unsigned int k = 0; k < tempString_.size(); k++)
						if (Controller::getCourse(tempString_[k], tempCourses).size() != 0) tempCourse_[k] = Controller::getCourse(tempString_[k], tempCourses)[0];
						else tempCourse_[k] = Course();
						tempStudents[j] = Student(unsigned(atoi(Students__[j][0].c_str())), Students__[j][1], tempCourse_);
				}
				vector<Date> tempDates_OV_Uniq_Sorted = Controller::sortDates(Controller::getUniqDates(tempCourses));
				Controller::setCourseStudentsNumber(tempCourses, tempStudents);
				Controller::setStudentStudyDays(tempStudents, Dates_OV_Uniq_Sorted);
				Controller::setSameDayCourses(tempStudents);
				Controller::setCourseMinStudyDays(tempCourses, tempStudents);
				for (unsigned int j = 0; j < tempCourses.size(); j++)
					if (tempCourses[j].getMinStudyDays() >= MinStudyDays && tempCourses[j].getId() == _InputCourse.getId()) {
						existsResult = true;
						Courses_OV = tempCourses;
						Students_OV = tempStudents;
						cout << _InputDates[i].stringForm() << endl;
						break;
					}
				if (existsResult) break;
			}
			if (!existsResult) cout << "none" << endl;
		}
		else if (Command == "Show") {
			cout << "========================================================================================================\n";
			cout << "=============================================== COURSES ================================================\n";
			cout << "Course Code || Course Name || Date || Hall || Min Study Days || Students Number" << endl;
			cout << "----------------------------------------------------------------------\n";
			for (unsigned int i = 0; i < Courses_OV.size(); i++)
				cout << Courses_OV[i].getId() << " || " << Courses_OV[i].getName() << " || " << Courses_OV[i].getDate().stringForm() << " || " << Courses_OV[i].getHall()
					 << " || " << Courses_OV[i].getMinStudyDays() << " || " << Courses_OV[i].getStudentsNumber() << endl;
			cout << "=============================================== STUDENTS ===============================================\n";
			cout << "Student ID || Student Name || Courses (Study Days)" << endl;
			cout << "----------------------------------------------------------------------\n";
			for (unsigned int i = 0; i < Students_OV.size(); i++) {
				cout << Students_OV[i].getId() << " || " << Students_OV[i].getName() << " ||";
				for (unsigned int j = 0; j < Students_OV[i].getCourses().size(); j++)
					cout << " " << Students_OV[i].getCourses()[j].getId() << " (" << Students_OV[i].getStudyDays()[j] << ")";
				cout << endl;
			}
			cout << "========================================================================================================\n";
		}
		else if (Command == "EMPTY") cout << "Empty Command" << endl;
		else if (Command == "Reset") main();
		else cout << "Unknown Command!" << endl;
		// >> START Over
		getline(cin, CommandLine);
		if (CommandLine.length() != 0) {
			CommandLineArray = explodeString(CommandLine, ' ');
			Command = CommandLineArray[0];
		}
		else Command = "EMPTY";
	}
	// END
	cout << "Thanks!";
	return 0;
}
