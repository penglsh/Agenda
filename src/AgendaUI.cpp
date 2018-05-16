#include "AgendaUI.hpp"
#include <cstdlib>
#include <iomanip>
#include <sstream>


AgendaUI::AgendaUI() {

}

AgendaUI::~AgendaUI() {

}

// the loop after entering Agenda
void AgendaUI::OperationLoop() {
	cout << "----------------------------------------Agenda----------------------------------------" << endl;
	cout << "Action :" << endl;
	cout << "l    - log in Agenda by user name and password" << endl;
	cout << "r    - register an Agenda account" << endl;
	cout << "q    - quit Agenda" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << "Agenda :~$ ";

	string order;
	cin >> order;
	cout << endl << endl;

	if (order == "l") {		// log in
		log_in();
	}
	else if (order == "r") {	// register
		reg();
	}
	else if (order == "q") {	// quit Agenda
		cout << "^_^ byebye! ^_^" << endl << endl << endl;
		exit(1);
	}
	else {	// give hints
		OperationLoop();
	}
}

// the loop of logging
void AgendaUI::log_in() {
	cout << "[log in] [username] [password]" << endl;
	cout << "[log in] ";

	string name, password;
	cin >> name >> password;

	if (AgendaService::userLogIn(name, password)) {
		cout << "[log in] succeed!" << endl << endl;

		// new entrance
		myAgenda(name, password);
	}

	else {

		cout << "[log in] Password error user doesn't exist" << endl << endl;

		// turn back to the beginning
		OperationLoop();
	}
}

// register new user
void AgendaUI::reg() {
	cout << "[register] [username] [password] [email] [phone]" << endl;
	cout << "[register] ";

	string name, password, email, phone;

	cin >> name >> password >> email >> phone;

	// register successfully
	if (AgendaService::userRegister(name, password, email, phone)) {
		cout << "[register] succeed!" << endl;

		// turn back to the beginning
		OperationLoop();

	}

	else {

		cout << "[register] This username has been registered!" << endl;

		// turn back to the beginning
		OperationLoop();
	}
}

// log in successfully
void AgendaUI::myAgenda(const string &name, const string &password) {
	cout << "----------------------------------------Agenda----------------------------------------" << endl;
	cout << "Action :" << endl;
	cout << "o    - log out Agenda" << endl;
	cout << "dc   - delete Agenda account" << endl;
	cout << "lu   - list all Agenda users" << endl;
	cout << "cm   - create a meeting" << endl;
	cout << "amp  - add meeting participator" << endl;
	cout << "rmp  - remove meeting participator" << endl;
	cout << "rqm  - request to quit meeting" << endl;
	cout << "la   - list all meetings" << endl;
	cout << "las  - list all sponsor meetings" << endl;
	cout << "lap  - list sll participator meetings" << endl;
	cout << "qm   - query meeting by title" << endl;
	cout << "qt   - query meeting by time interval" << endl;
	cout << "dm   - delete meeting by title" << endl;
	cout << "da   - delete all meetings" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << endl << endl;

	cout << "Agenda@" << name << " :~# ";

	string order;

	cin >> order;

	cout << endl << endl;

	if (order == "o") { // log out
		OperationLoop();
	}
	else if (order == "dc") {	// delete account

		if (AgendaService::deleteUser(name, password)) {
			cout << "[delete agenda account] succeed!" << endl;
		}
	}
	else if (order == "lu") { // list all users
		cout << "[list all users]" << endl << endl;

		cout << left << setw(30) << "name" << setw(30) << "email" << setw(30) << "phone" << endl;

		list<User> userList = AgendaService::listAllUsers();

		for (auto i : userList) {
			cout << left << setw(30) << i.getName() << setw(30) << i.getEmail() << setw(30) << i.getPhone() << endl;
		}

		cout << endl;
	}
	else if (order == "cm") {
		cout << "[create meeting] [the number of participators]" << endl;
		cout << "[create meeting] ";

		int number = 0;
		cin >> number;
		int index = 1;
		std::vector<string> participator;

		while (number --) {
			cout << "[create meeting] [please enter the participator " << index << " ]" << endl;
			string t_par;
			cout << "[create meeting] ";
			cin >> t_par;

			participator.push_back(t_par);

			index ++;
		}

		cout << "[create meeting] [title] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
		cout << "[create meeting] ";
		string startTime, endTime, title;
		cin >> title >> startTime >> endTime;

		if (AgendaService::createMeeting(name, title, startTime, endTime, participator)) {
			cout << "[create meeting] succeed!" << endl;
		}
		else {
			cout << "[create meeting] error!" << endl;
		}
	}
	else if (order == "amp") {
		cout << "[add participator] [meeting title] [participator username]" << endl;
		cout << "[add participator] ";
		string title, username;
		cin >> title >> username;

		if (AgendaService::addMeetingParticipator(name, title, username)) {
			cout << "[add participator] succeed!" << endl;
		}
		else {
			cout << "[add participator] error!" << endl;
		}
	}
	else if (order == "rmp") {
		cout << "[remove participator] [meeting title] [participator username]" << endl;
		string title, username;
		cout << "[remove participator] ";
		cin >> title >> username;

		if (AgendaService::removeMeetingParticipator(name, title, username)) {
			cout << "[remove participator] succeed!" << endl;
		}
		else {
			cout << "[remove meeting] error!" << endl;
		}
	}
	else if (order == "rqm") {
		cout << "[quit meeting] [meeting title]" << endl;
		string title;
		cout << "[quit meeting] ";
		cin >> title;

		if (AgendaService::quitMeeting(name, title)) {
			cout << "[quit meeting] succeed!" << endl;
		}
		else {
			cout << "[quit meeting] error!" << endl;
		}
	}
	else if (order == "la") {
		cout << "[list all meetings]" << endl << endl;

		cout << left << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time" << setw(20) << "end time" << setw(20) << "participators" << endl;

		list<Meeting> meetList = AgendaService::listAllMeetings(name);

		for (auto &i : meetList) {
			cout << left << setw(20) << i.getTitle() << setw(20) << i.getSponsor();

			Date st = i.getStartDate();
			Date en = i.getEndDate();

			cout << left << setw(20) << Date::dateToString(st) << setw(20) << Date::dateToString(en);

			vector<string> participator = i.getParticipator();

			stringstream ss;

			for (unsigned j = 0; j < participator.size(); j ++) {
				if (j == 0) {
					ss << participator[j];
				}
				else {
					ss << "," << participator[j];
				}
			}

			string par_str = ss.str();

			cout << left << setw(20) << par_str << endl;
		}

	} 
	else if (order == "las") {
		cout << "[list all sponsor meetings]" << endl << endl;
		cout << left << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time" << setw(20) << "end time" << setw(20) << "participators" << endl;

		list<Meeting> meetList = AgendaService::listAllSponsorMeetings(name);

		for (auto &i : meetList) {
			cout << left << setw(20) << i.getTitle() << setw(20) << i.getSponsor();

			Date st = i.getStartDate();
			Date en = i.getEndDate();

			cout << left << setw(20) << Date::dateToString(st) << setw(20) << Date::dateToString(en);

			vector<string> participator = i.getParticipator();

			stringstream ss;

			for (unsigned j = 0; j < participator.size(); j ++) {
				if (j == 0) {
					ss << participator[j];
				}
				else {
					ss << "," << participator[j];
				}
			}

			string par_str = ss.str();

			cout << left << setw(20) << par_str << endl;
		}

	}
	else if (order == "lap") {
		cout << "[list all participator meetings]" << endl << endl;

		list<Meeting> meetList = AgendaService::listAllParticipateMeetings(name);

		cout << left << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time" << setw(20) << "end time" << setw(20) << "participators" << endl;
		for (auto &i : meetList) {
			cout << left << setw(20) << i.getTitle() << setw(20) << i.getSponsor();

			Date st = i.getStartDate();
			Date en = i.getEndDate();

			cout << left << setw(20) << Date::dateToString(st) << setw(20) << Date::dateToString(en);

			vector<string> participator = i.getParticipator();

			stringstream ss;

			for (unsigned j = 0; j < participator.size(); j ++) {
				if (j == 0) {
					ss << participator[j];
				}
				else {
					ss << "," << participator[j];
				}
			}

			string par_str = ss.str();

			cout << left << setw(20) << par_str << endl;
		}		
	}
	else if (order == "qm") {
		cout << "[query meeting] [title]" << endl;
		cout << "[query meeting] ";

		string title;
		cin >> title;

		list<Meeting> meetList = AgendaService::meetingQuery(name, title);

		cout << left << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time" << setw(20) << "end time" << setw(20) << "participators" << endl;
		for (auto &i : meetList) {
			cout << left << setw(20) << i.getTitle() << setw(20) << i.getSponsor();

			Date st = i.getStartDate();
			Date en = i.getEndDate();

			cout << left << setw(20) << Date::dateToString(st) << setw(20) << Date::dateToString(en);

			vector<string> participator = i.getParticipator();

			stringstream ss;

			for (unsigned j = 0; j < participator.size(); j ++) {
				if (j == 0) {
					ss << participator[j];
				}
				else {
					ss << "," << participator[j];
				}
			}

			string par_str = ss.str();

			cout << left << setw(20) << par_str << endl;
		}		
	}
	else if (order == "qt") {
		cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
		cout << "[query meeting] ";
		string ststr, enstr;
		cin >> ststr >> enstr;

		list<Meeting> meetList = AgendaService::meetingQuery(name, ststr, enstr);
		cout << left << setw(20) << "title" << setw(20) << "sponsor" << setw(20) << "start time" << setw(20) << "end time" << setw(20) << "participators" << endl;
		for (auto &i : meetList) {
			cout << left << setw(20) << i.getTitle() << setw(20) << i.getSponsor();

			Date st = i.getStartDate();
			Date en = i.getEndDate();

			cout << left << setw(20) << Date::dateToString(st) << setw(20) << Date::dateToString(en);

			vector<string> participator = i.getParticipator();

			stringstream ss;

			for (unsigned j = 0; j < participator.size(); j ++) {
				if (j == 0) {
					ss << participator[j];
				}
				else {
					ss << "," << participator[j];
				}
			}

			string par_str = ss.str();

			cout << left << setw(20) << par_str << endl;
		}	
	}
	else if (order == "dm") {
		cout << "[delete meeting] [title]" << endl;
		string title;
		cout << "[delete meeting] ";
		cin >> title;

		if (AgendaService::deleteMeeting(name, title)) {
			cout << "[delete meeting] succeed!" << endl;
		}
		else {
			cout << "[error] delete meeting fail!" << endl;
		}
	}
	else if (order == "da") {
		if (AgendaService::deleteAllMeetings(name)) {
			cout << "[delete all meeting] succeed!" << endl;
		}
	}

}