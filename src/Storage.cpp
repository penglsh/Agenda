#include "Storage.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include "Date.hpp"
//#include "Path.hpp"
  //static std::shared_ptr<Storage> m_instance;
  //std::list<User> m_userList;
  //std::list<Meeting> m_meetingList;
  //bool m_dirty;
using namespace std;

std::shared_ptr<Storage> Storage::m_instance = nullptr;

Storage::Storage() {

	m_userList.erase(m_userList.begin(), m_userList.end());

	m_meetingList.erase(m_meetingList.begin(), m_meetingList.end());

	readFromFile();
	m_dirty = false;
}

bool Storage::readFromFile(void) {

	//cout << m_userList.size() << " " << m_meetingList.size() << endl;

	//cout << m_userList.size() << " " << m_meetingList.size() << endl;

	// users file 
	ifstream in_user("users.csv", ios::in);
	//ifstream in_user("users.txt", ios::in);
	//ifstream in_user(Path::userPath, ios::in);
	if (!in_user)
		return false;

	string str;
	string t_n;
	
	User tmp;

	//char t_n[20] = {}, t_pa = {}, t_e[20] = {}, t_ph = {};

	while(getline(in_user, str, '\n')) {
		stringstream ss;
		ss << str;

		// name,password,email,phone
		int flag = 0;
		while (getline(ss, t_n, ',')) {
			string t_str = "";

			for (unsigned i = 0; i < t_n.size(); i ++) {
				if (t_n[i] != '"' && t_n[i] != '\n' && t_n[i] != ',') {
					t_str += t_n[i];
				} 
			}

			if (flag == 0) {
				tmp.setName(t_str);
			}
			else if (flag == 1) {
				tmp.setPassword(t_str);
			}
			else if (flag == 2) {
				tmp.setEmail(t_str);
			}
			else {
				tmp.setPhone(t_str);
			}

			flag ++;
		}
		
		m_userList.push_back(tmp);
		flag = 0;
		//getchar();
	}
	in_user.close();

	/*for (auto i : m_userList) {
		cout << endl << i.getName() << " " << i.getPassword() << " " << i.getEmail() << " " << i.getPhone() << endl;
	}*/


	// meetings file
	//ifstream in_meeting("meetings.txt", ios::in);
	ifstream in_meeting("meetings.csv", ios::in);
	//ifstream in_meeting(Path::meetingPath, ios::in);
	if (!in_meeting)
		return false;

	string lineStr;
	string t_s;
	Meeting t_meet;
	vector<string> pars;
	Date s_time;
	Date e_time;

	int year = 0, month = 0, day = 0, hour = 0, minute = 0;

	while(getline(in_meeting, lineStr, '\n')) {
		stringstream ss1;
		ss1 << lineStr;

		// sponsor,participators,starttime.endtime,title
		int flag = 0;

		while(getline(ss1, t_s, ',')) {

			string t_str = "";
	
			for (unsigned i = 0; i < t_s.size(); i ++) {
				if (t_s[i] != '"' && t_s[i] != '\n' && t_s[i] != ',') {
					t_str += t_s[i];
				} 
			}

			if (flag == 0) {
				t_meet.setSponsor(t_str);
			}
			else if (flag == 1) {

				stringstream ss2;
				string tm;
				ss2 << t_str << endl;

				while(getline(ss2, tm, '&')) {

					string t_part = "";

					for (unsigned j = 0; j < tm.size(); j ++) {
						if (tm[j] != '\n' && tm[j] != '&') {
							t_part += tm[j];
						}
					}

					pars.push_back(t_part);
				}

				t_meet.setParticipator(pars);

				pars.erase(pars.begin(), pars.end());
			}
			else if (flag == 2) {

				char *str1 = (char *)t_s.data();

				sscanf(str1, "\"%d-%d-%d/%d:%d\"", &year, &month, &day, &hour, &minute);

				s_time.setYear(year);
				s_time.setMonth(month);
				s_time.setDay(day);
				s_time.setHour(hour);
				s_time.setMinute(minute);

				t_meet.setStartDate(s_time);
			}
			else if (flag == 3) {
				char *str2 = (char *)t_s.data();

				sscanf(str2, "\"%d-%d-%d/%d:%d\"", &year, &month, &day, &hour, &minute);

				e_time.setYear(year);
				e_time.setMonth(month);
				e_time.setDay(day);
				e_time.setHour(hour);
				e_time.setMinute(minute);

				t_meet.setEndDate(e_time);
			}
			else {
				t_meet.setTitle(t_str);
			}

			flag ++;

		}

		m_meetingList.push_back(t_meet);

		flag = 0;
		//getchar();
	}

	in_meeting.close();


	//cout << m_userList.size() << " " << m_meetingList.size() << endl;
	
	return true;
}

bool Storage::writeToFile(void) {
	// user file
	//ofstream out_user("users.txt", ios::out);
	ofstream out_user("users.csv", ios::out);
	//ofstream out_user(Path::userPath, ios::out);
	if (!out_user) {
		//m_dirty = false;
		return false;
	}

	// name,password,email,phone
	/*for (auto i : m_userList) {

		out_user << "\"" << i.getName() << "\"" << ",";
		out_user << "\"" << i.getPassword() << "\"" << ",";
		out_user << "\"" << i.getEmail() << "\"" << ","; 
		out_user << "\"" << i.getPhone() << "\"";
		out_user << endl;
	}*/

	for (auto be = m_userList.cbegin(); be != m_userList.cend(); be ++) {

		out_user << "\"" << (*be).getName() << "\"" << ',';
		out_user << "\"" << (*be).getPassword() << "\"" << ',';
		out_user << "\"" << (*be).getEmail() << "\"" << ','; 
		out_user << "\"" << (*be).getPhone() << "\"";
		out_user << endl;

	}

	out_user.close();
	//m_dirty = true;

	//ofstream out_meet("meetings.txt", ios::out);
	ofstream out_meet("meetings.csv", ios::out);
	//ofstream out_meet(Path::meetingPath, ios::out);
	if (!out_meet) {
		//m_dirty = false;
		return false;
	}
	// sponsor,participators,starttime,endtime,title
	/*for (auto i : m_meetingList) {

		auto v = i.getParticipator();

		stringstream ss;

		int len = v.size();

		for (int j = 0; j < len; j ++) {
			if (j == len - 1) {
				ss << v[j];
			}
			else {
				ss << v[j] << "&";
			}
		}

		string t_s = ss.str();

		Date s_time = i.getStartDate();
		Date e_time = i.getEndDate();

		out_meet << "\"" << i.getSponsor() << "\"" << ",";
		out_meet << "\"" << t_s << "\"" << ",";
		out_meet << "\"" << s_time.dateToString(s_time) << "\"" << ","; 
		out_meet << "\"" << e_time.dateToString(e_time) << "\"" << ",";
		out_meet << "\"" << i.getTitle() << "\"";
		out_meet << endl;

	}*/

	for (auto it = m_meetingList.cbegin(); it != m_meetingList.cend(); it ++) {

		auto v = (*it).getParticipator();

		stringstream ss;

		int len = v.size();

		for (int j = 0; j < len; j ++) {
			if (j == len - 1) {
				ss << v[j];
			}
			else {
				ss << v[j] << '&';
			}
		}

		string t_s = ss.str();

		Date s_time = (*it).getStartDate();
		Date e_time = (*it).getEndDate();

		out_meet << "\"" << (*it).getSponsor() << "\"" << ',';
		out_meet << "\"" << t_s << "\"" << ",";
		out_meet << "\"" << s_time.dateToString(s_time) << "\"" << ','; 
		out_meet << "\"" << e_time.dateToString(e_time) << "\"" << ',';
		out_meet << "\"" << (*it).getTitle() << "\"";
		out_meet << endl;
	}

	out_meet.close();

	//m_dirty = true;

	//m_userList.erase(m_userList.begin(), m_userList.end());
	//m_meetingList.erase(m_meetingList.begin(), m_meetingList.end());
	return true;
}

std::shared_ptr<Storage> Storage::getInstance(void) {
	if (m_instance == nullptr) {		// m_instance is nullptr, create it 
		m_instance = (shared_ptr<Storage>)new Storage();
	}
	return m_instance;
}

Storage::~Storage() {
	sync();
}

void Storage::createUser(const User &t_user) {

	m_userList.push_back(t_user);
	m_dirty = true;
	//writeToFile();
}

std::list<User> Storage::queryUser(std::function<bool(const User &t)> filter) const {
	list<User> tmp;
	//readFromFile();
	//cout << m_userList.size() << endl;

	if (m_userList.size() == 0) {
		return tmp;
	}

	for (auto i : m_userList) {
		if (filter(i)) {
			tmp.push_back(i);
		}
	}

	return tmp;
}

int Storage::updateUser(std::function<bool(const User &t)> filter,
                 std::function<void(User &)> switcher) {

	int count = 0;

	for (auto i : m_userList) {
		if (filter(i)) {
			switcher(i);
			count ++;
		}
	}

	m_dirty = true;

	return count;
}

int Storage::deleteUser(std::function<bool(const User &t)> filter) {
	
	list<User>::iterator it;

	int count = 0;

	for (auto be = m_userList.begin(); be != m_userList.end(); be ++) {
		if (filter(*be)) {
			it = be;
			it = m_userList.erase(it);
			count ++;
		}
	}

	m_dirty = true;

	return count;
}

void Storage::createMeeting(const Meeting &t_meeting) {

	m_meetingList.push_back(t_meeting);
	//writeToFile();
	m_dirty = true;
}

std::list<Meeting> Storage::queryMeeting(
      std::function<bool(const Meeting &m)> filter) const {

	list<Meeting> tmp;
	//readFromFile();

	for (auto i : m_meetingList) {
		if (filter(i)) {

			//cout << i.getParticipator().size() << endl;
			tmp.push_back(i);
		}
	}
	return tmp;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                    std::function<void(Meeting &)> switcher) {
	int count = 0;
	for (auto &i : m_meetingList) {
		if (filter(i)) {
			switcher(i);
			count ++;
		}
	}

	m_dirty = true;

	return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &t)> filter) {
	
	list<Meeting>::iterator it;
	int count = 0;

	for (auto be = m_meetingList.begin(); be != m_meetingList.end(); be ++) {
		if (filter(*be)) {
			it = be;
			it = m_meetingList.erase(it);
			count ++;
		}
	}

	m_dirty = true;
	return count;
}

bool Storage::sync(void) {
	if (m_dirty) {
		writeToFile();
		m_dirty = false;
		return true;
	}

	return false;
}