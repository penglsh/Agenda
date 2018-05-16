#include "AgendaService.hpp"
#include <algorithm>

using namespace std;

AgendaService::AgendaService() : m_storage(nullptr){}

AgendaService::~AgendaService() {
	quitAgenda();
}

bool AgendaService::userLogIn(const std::string &userName, const std::string &password) {

	list<User> t_users = this -> listAllUsers();

	int flag = 0;
	for (auto i : t_users) {
		if (i.getName() == userName && i.getPassword() == password) {
			flag = 1;
		}
	}

	if (flag == 0) {
		return false;
	}

	return true;
}

bool AgendaService::userRegister(const std::string &userName, const std::string &password,
                    const std::string &email, const std::string &phone) {

	list<User> t_users = this -> listAllUsers();

	int flag = 0;
	for (auto i : t_users) {
		if (i.getName() == userName) {
			flag = 1;
		}
	}

	if (flag) {
		return false;
	}

	User t_user(userName, password, email, phone);

	m_storage -> createUser(t_user);

	return true;
}

bool AgendaService::deleteUser(const std::string &userName, const std::string &password) {

	list<User> t_users = this -> listAllUsers();

	int flag = 0;
	for (auto i : t_users) {
		if (i.getName() == userName && i.getPassword() == password) {
			flag = 1;
		}
	}

	if (flag == 0) {
		return false;
	}

	m_storage -> deleteUser([userName, password](const User &user) -> bool { return  user.getName() == userName && user.getPassword() == password; });

	return true;
}

std::list<User> AgendaService::listAllUsers(void) const {
	list<User> userList = m_storage -> queryUser([](const User &user) -> bool { return user.getName().size() != 0; });
	return userList;
}

bool AgendaService::createMeeting(const std::string &userName, const std::string &title,
                     const std::string &startDate, const std::string &endDate,
                     const std::vector<std::string> &participator) {

	if (startDate >= endDate) {
		return false;
	}

	list<Meeting> t_meets = meetingQuery(userName, title);
	list<Meeting> t_meets1 = meetingQuery(userName, startDate, endDate);

	if (t_meets.size() != 0 || t_meets1.size() != 0) {
		return false;
	}

	Meeting t_meet(userName, participator, startDate, endDate, title);

	m_storage -> createMeeting(t_meet);

	return true;

}

bool AgendaService::addMeetingParticipator(const std::string &userName,
                              const std::string &title,
                              const std::string &participator) {

	list<Meeting> t_meets = this -> meetingQuery(userName, title);

	auto size1 = t_meets.size();

	if (size1 == 0)
		return false;

	for (auto i : t_meets) {
		if (i.isParticipator(participator))
			return false;
	}

	for (auto &i : t_meets) {
		i.addParticipator(participator);
	}

	return true;

}


bool AgendaService::removeMeetingParticipator(const std::string &userName, const std::string &title, const std::string &participator) {

	list<Meeting> t_meets = this -> meetingQuery(userName, title);

	int flag = 0;
	for (auto &i : t_meets) {
		if (i.isParticipator(participator)) {
			i.removeParticipator(participator);
			flag = 1;
		}
	}

	if (flag)
		return true;
	return false;

}

bool AgendaService::quitMeeting(const std::string &userName, const std::string &title) {

	list<Meeting> t_meets = m_storage -> queryMeeting([title, userName](const Meeting &meet) -> bool { return (meet.getTitle() == title) && (meet.isParticipator(userName)); });

	auto size1 = t_meets.size();

	if (size1 == 0)
		return false;

	int flag = 0;

	for (auto &i : t_meets) {
		if (i.isParticipator(userName)) {
			i.removeParticipator(userName);
			flag = 1;
		}
	}

	if (flag)
		return true;

	return false;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &title) const {

	list<Meeting> t_meets = m_storage -> queryMeeting([userName, title](const Meeting &meet) -> bool { return meet.getSponsor() == userName && meet.getTitle() == title; });

 	return t_meets;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &startDate,
                                  const std::string &endDate) const {

	list<Meeting> t_meets = m_storage -> queryMeeting([userName, startDate, endDate](const Meeting &meet) -> bool { return meet.getSponsor() == userName && (meet.getStartDate() >= startDate ||
	meet.getEndDate() <= endDate); });

	return t_meets;

}

std::list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const {

	list<Meeting> t_meets = m_storage -> queryMeeting([userName](const Meeting &meet) -> bool { return (meet.getSponsor() == userName) || (meet.isParticipator(userName)); });

	return t_meets;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const {
	list<Meeting> t_meets = m_storage -> queryMeeting([userName](const Meeting &meet) -> bool { return meet.getSponsor() == userName; });

	return t_meets;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string &userName) const {

	list<Meeting> t_meets = m_storage -> queryMeeting([userName](const Meeting &meet) -> bool { return meet.isParticipator(userName); });

	return t_meets;
}

bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title) {

	list<Meeting> t_meets = this -> meetingQuery(userName, title);

	int size1 = t_meets.size();

	int size2 = m_storage -> deleteMeeting([userName, title](const Meeting &meet) -> bool { return meet.getSponsor() == userName && meet.getTitle() == title; });

	return size1 != size2;
}

bool AgendaService::deleteAllMeetings(const std::string &userName) {
	list<Meeting> t_meets = this -> listAllSponsorMeetings(userName);

	t_meets.erase(t_meets.begin(), t_meets.end());

	return t_meets.size() == 0;
}

void AgendaService::startAgenda(void) {
	m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
	m_storage = nullptr;
}