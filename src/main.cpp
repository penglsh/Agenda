#include "Meeting.hpp"
#include "Storage.hpp"
#include <iostream>
#include <vector>
#include "AgendaService.hpp"
#include "AgendaUI.hpp"
#include <algorithm>
using namespace std;

int main() {
	
	AgendaUI it;

	string t_s = "shiyang";
	vector<string> t_p;
	t_p.push_back("gg");
	t_p.push_back("jj");

	Date st(2017, 2, 23, 12, 45);
	Date en(2017, 2, 23, 14, 0);

	Date d1(201, 2, 2, 2, 2);
	cout << "1" << endl;
	cout << d1.dateToString(d1) << endl;
	cout << "0" << "?" << d1.isValid(d1) << endl;

	

	Date d2(2016, 2, 29, 2, 4);
	cout << endl << "2" << endl;
	cout << d2.dateToString(d2) << endl;
	cout << "1" << "?" << d2.isValid(d2) << endl;



	Date d3(2016, 2, 29, 0, 23);
	cout << endl << "3" << endl;
	cout << d3.dateToString(d3) << endl;
	cout << "1" << "?" << d3.isValid(d3) << endl;

	Date d4(2016, 2, 29, 0, 0);
	cout << endl << "4" << endl;
	cout << d4.dateToString(d4) << endl;
	cout << "1" << "?" << d4.isValid(d4) << endl;


	Date d5(2017, 2, 29, 0, 0);
	cout << endl << "5" << endl;
	cout << d5.dateToString(d5) << endl;
	cout << "0" << "?" << d5.isValid(d5) << endl;

	Date d6(2017, 2, 28, 0, 0);
	cout << endl << "6" << endl;
	cout << d6.dateToString(d6) << endl;
	cout << "1" << "?" << d6.isValid(d6) << endl;

	Date d7(2017, 0, 29, 0, 0);
	cout << endl << "7" << endl;
	cout << d7.dateToString(d7) << endl;
	cout << "0" << "?" << d7.isValid(d7) << endl;



	string title = "dajia";

	Meeting meet(t_s, t_p, st, en, title);

	Meeting met(meet);

	cout << meet.getSponsor() << endl;

	std::vector<string> v = meet.getParticipator();

	string t_s1 = "kk";
	meet.setSponsor(t_s1);

	t_p.push_back("zz");
	meet.setParticipator(t_p);

	meet.addParticipator("ll");

	meet.removeParticipator("gg");

	Date t = meet.getStartDate();

	Date p = meet.getEndDate();

	cout << t.dateToString(t) << endl;
	cout << p.dateToString(p) << endl;


	Date st1("2017-5-30/23:23");

	meet.setStartDate(d4);

	Date end("2017-6-1/20:23");

	meet.setEndDate(d3);

	cout << meet.getTitle() << endl;
	meet.setTitle("kandianying");

	User user("penglsh", "123456", "123@qq.com", "134234");


	//Storage *ptr;

	cout << "-----------------------" << endl;

	shared_ptr<Storage> ptr1 = Storage::getInstance();
	
	//ptr1 -> createUser(user);

	User user1("jiyang", "1234", "aaa@mail", "135");

	//ptr1 -> createUser(user1);

	//ptr1 -> createMeeting(meet);
	//ptr1 -> createMeeting(met);
	//ptr1 -> sync();

	list<User> list1 = ptr1 -> queryUser([](const User &user) -> bool { return user.getName().size() != 0; });
	//cout << "-----------------------" << endl;

	list<Meeting> list2 = ptr1 -> queryMeeting([](const Meeting &meet) -> bool { return meet.getSponsor().size() != 0; });


	//cout << list1.size() << " " << list2.size() << endl;

	for (auto i = list1.cbegin(); i != list1.cend(); i ++) {
		cout << (*i).getName() << " " << (*i).getEmail() << " " << (*i).getPhone() << endl;
	}

	for (auto i = list2.begin(); i != list2.end(); i ++) {
		cout << (*i).getSponsor() << " ";

		vector<string> list3 = (*i).getParticipator();

		//cout << (*i).getParticipator().size() << endl;

		auto be = list3.begin();

		//cout << list3.size() << endl;

		for (unsigned j = 0; j < list3.size(); j ++) {
			if (j == 0) {
				cout << (*be);
			}
			else {
				cout << "&" << (*be);
			}
			be ++;
		}
		cout << " ";

		list3.erase(list3.begin(), list3.end());
		//cout << list3.size() << endl;

		//cout << "-----------------------" << endl;

		Date sta = (*i).getStartDate();
		Date ent = (*i).getEndDate();

		cout << sta.dateToString(sta) << " " << ent.dateToString(ent) << " ";

		cout << (*i).getTitle() << endl;

	}

	it.OperationLoop();

	return 0;
}
