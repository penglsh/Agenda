#ifndef AGENDAUI_HPP
#define AGENDAUI_HPP

#include <iostream>
#include "AgendaService.hpp"

using namespace std;


class AgendaUI : public AgendaService
{
public:
	AgendaUI();
	~AgendaUI();

	// the loop after entering Agenda
	void OperationLoop();

	// the loop of logging
	void log_in();

	// register new user
	void reg();

	// log in successfully
	void myAgenda(const string &name, const string &password);
	
};

#endif