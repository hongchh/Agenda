#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stdlib.h>

#include "AgendaUI.h"

AgendaUI::AgendaUI() {}

void AgendaUI::OperationLoop() {
    std::string userInput = "";
    while (userInput != "q") {
        system("clear");
        mainPage();
        std::cout << "\nAgenda : ~$ ";
        std::cin >> userInput;
        if (userInput == "l") userLogIn();
        else if (userInput == "r") userRegister();
        else if (userInput == "q") quitAgenda();
    }
}

void AgendaUI::mainPage() {
    std::cout << "\n\n";
    for (int i = 0; i < 20; ++i) std::cout << '-';
    std::cout << " Agenda ";
    for (int i = 0; i < 20; ++i) std::cout << '-';
    std::cout << "\n|Action :                                      |\n"
              << "| l  - log in Agenda by user name and password |\n"
              << "| r  - register an Agenda account              |\n"
              << "| q  - quit Agenda                             |\n";
    for (int i = 0; i < 48; ++i) std::cout << '-';
}

void AgendaUI::subPage() {
    std::cout << "\n\n";
    for (int i = 0; i < 20; ++i) std::cout << '-';
    std::cout << " Agenda ";
    for (int i = 0; i < 20; ++i) std::cout << '-';
    std::cout << "\n|Action :                                      |\n"
              << "| o    - log out Agenda                        |\n"
              << "| dc   - delete Agenda account                 |\n"
              << "| lu   - list all Agenda user                  |\n"
              << "| cm   - create a meeting                      |\n"
              << "| la   - list all meetings                     |\n"
              << "| las  - list all sponsor meetings             |\n"
              << "| lap  - list all participate meetings         |\n"
              << "| qm   - query meeting by title                |\n"
              << "| qt   - query meeting by time interval        |\n"
              << "| dm   - delete meeting by title               |\n"
              << "| da   - delete all meetings                   |\n"
              << "| up   - update your password                  |\n"
              << "| ue   - update your email                     |\n"
              << "| uph  - update your phone                     |\n"
              << "| ut   - update meeting title                  |\n";
    for (int i = 0; i < 48; ++i) std::cout << '-';
}

void AgendaUI::startAgenda() {
    bool quit = false;
    while (!quit) {
        system("clear");
        subPage();
        quit = executeOperation(getOperation());
    }
}

std::string AgendaUI::getOperation() {
    std::string userInput;
    std::cout << "\nAgenda : # ";
    std::cin >> userInput;
    return userInput;
}

bool AgendaUI::executeOperation(std::string op) {
    if (op == "o") {
        userLogOut();
        return true;
    } else if (op == "dc") {
        deleteUser();
        return true;
    } else if (op == "lu") {
        listAllUsers();
    } else if (op == "cm") {
        createMeeting();
    } else if (op == "la") {
        listAllMeetings();
    } else if (op == "las") {
        listAllSponsorMeetings();
    } else if (op == "lap") {
        listAllParticipateMeetings();
    } else if (op == "qm") {
        queryMeetingByTitle();
    } else if (op == "qt") {
        queryMeetingByTimeInterval();
    } else if (op == "dm") {
        deleteMeetingByTitle();
    } else if (op == "da") {
        deleteAllMeetings();
    } else if (op == "up") {
        updateUserPassword();
        return true;
    } else if (op == "ue") {
        updateUserEmail();
    } else if (op == "uph") {
        updateUserPhone();
    } else if (op == "ut") {
        updateMeetingTitle();
    } else {
        std::cout << "\nAgenda : # Invalid instruction!" << std::endl;
    }
    return false;
}

void AgendaUI::userLogIn() {
    system("clear");
    std::cout << "\n[log in] Please input user name.\n[user name]: ";
    std::cin >> userName_;
    std::cout << "\n[log in] Please input password.\n[password]: ";
    std::cin >> userPassword_;
    if (!agendaService_.userLogIn(userName_, userPassword_)) {
        std::cout << "[error] log in fail!\n[log in] "
                  << "User name not been registered or password wrong.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::string input;
        std::cin >> input;
        while (input != "back") {
            std::cout << "\nWrong instruction.\n"
                      << "\nPlease input \"back\" for back to main page: ";
            std::cin >> input;
        }
    } else {
        startAgenda();
    }
}

void AgendaUI::userRegister() {
    system("clear");
    std::string userName, password, email, phone;
    std::cout << "\n[register] Please input user name.\n[user name]: ";
    std::cin >> userName;
    std::cout << "\n[register] Please input password.\n[password]: ";
    std::cin >> password;
    std::cout << "\n[register] Please input your email.\n[email]: ";
    std::cin >> email;
    std::cout << "\n[register] Please input your phone.\n[phone]: ";
    std::cin >> phone;
    if (!agendaService_.userRegister(userName, password, email, phone))
        std::cout << "[error] register fail!\n"
                  << "The user name has been registered.\n";
    else
        std::cout << "[register] succeed!\n";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::quitAgenda() {
    std::cout << "\nThank you for using Agenda. Good bye!\n" << std::endl;
}

void AgendaUI::userLogOut() {
    std::cout << "\nLog out successfully!\n"
              << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }

}

void AgendaUI::deleteUser() {
    system("clear");
    if (agendaService_.deleteUser(userName_, userPassword_)) {
        std::cout << "\n[delete Agenda account] succeed!" << std::endl;
    } else {
        std::cout << "\n[error] delete fail!" << std::endl;
    }
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::listAllUsers() {
    system("clear");
    std::cout << "\n[list all users]\n\n"
              << "name           email                    phone\n";
    std::list<User> ul = agendaService_.listAllUsers();
    std::for_each(ul.begin(), ul.end(), [&](const User& u) {
        std::cout << std::setiosflags(std::ios::left)
                  << std::setw(15) << u.getName()
                  << std::setw(25) << u.getEmail()
                  << std::setw(15)<< u.getPhone()
                  << std::endl;
    });
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::createMeeting() {
    system("clear");
    std::string title, par, st, et;
    std::cout << "\n[create meeting] Please input the title of meeting."
              << "\n[title]: ";
    std::cin >> title;
    std::cout << "\n[create meeting] Please input the meeting participator."
              << "\n[participator]: ";
    std::cin >> par;
    std::cout << "\n[create meeting] Please input the start time of meeting."
              << "\n[start time(yyyy-mm-dd/hh:mm)]: ";
    std::cin >> st;
    std::cout << "\n[create meeting] Please input the end time of meeting."
              << "\n[end time(yyyy-mm-dd/hh:mm)]: ";
    std::cin >> et;
    if (agendaService_.createMeeting(userName_, title, par, st, et))
        std::cout << "[create meeting] succeed!\n";
    else
        std::cout << "[error] create meeting fail!\n"
                  << "The meeting is already here "
                  << "or the time is not suitable.\n";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::listAllMeetings() {
    system("clear");
    std::cout << "\n[list all meetings]\n\n";
    std::list<Meeting> ml = agendaService_.listAllMeetings(userName_);
    printMeetings(ml);
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::listAllSponsorMeetings() {
    system("clear");
    std::cout << "\n[list all sponsor meetings]\n\n";
    std::list<Meeting> ml = agendaService_.listAllSponsorMeetings(userName_);
    printMeetings(ml);
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::listAllParticipateMeetings() {
    system("clear");
    std::cout << "\n[list all participate meetings]\n\n";
    std::list<Meeting> ml;
    ml = agendaService_.listAllParticipateMeetings(userName_);
    printMeetings(ml);
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::queryMeetingByTitle() {
    system("clear");
    std::cout << "\n[query meeting] Please input the meeting title."
              << "\n[title]: ";
    std::string title;
    std::cin >> title;
    std::list<Meeting> ml = agendaService_.meetingQuery(userName_, title);
    printMeetings(ml);
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::queryMeetingByTimeInterval() {
    system("clear");
    std::string st, et;
    std::cout << "\n[query meeting] Please input the start time."
              << "\n[start time(yyyy-mm-dd/hh:mm)]: ";
    std::cin >> st;
    std::cout << "\n[query meeting] Please input the end time."
              << "\n[end time(yyyy-mm-dd/hh:mm)]: ";
    std::cin >> et;
    std::list<Meeting> ml = agendaService_.meetingQuery(userName_, st, et);
    printMeetings(ml);
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::deleteMeetingByTitle() {
    system("clear");
    std::cout << "\n[delete meeting] Please input the title of meeting."
              << "\n[title]: ";
    std::string title;
    std::cin >> title;
    if (agendaService_.deleteMeeting(userName_, title))
        std::cout << "\n[delete meeting by title] succeed!\n";
    else
        std::cout << "\n[error] delete meeting fail!\n"
                  << "There is no such meeting.\n";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::deleteAllMeetings() {
    system("clear");
    if (agendaService_.deleteAllMeetings(userName_))
        std::cout << "\n[delete all meeting] succeed!\n";
    else
        std::cout << "\n[error] delete all meeting fail!";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::updateUserPassword() {
    system("clear");
    std::cout << "\n[update user password] Please input your new password.\n"
              << "\n[new password]: ";
    std::string newPassword;
    std::cin >> newPassword;
    if (agendaService_.updateUserPassword(userName_,
                       userPassword_, newPassword))
        std::cout << "\n[update user password] succeed!\n"
                  << "\nPlease come back to main page for relog in.\n";
    else
        std::cout << "\n[error] update password fail!";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::updateUserEmail() {
    system("clear");
    std::cout << "\n[update user email] Please input your new email.\n"
              << "\n[new email]: ";
    std::string newEmail;
    std::cin >> newEmail;
    if (agendaService_.updateUserEmail(userName_, userPassword_, newEmail))
        std::cout << "\n[update user email] succeed!\n";
    else
        std::cout << "\n[error] update email fail!";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::updateUserPhone() {
    system("clear");
    std::cout << "\n[update user phone] Please input your new phone.\n"
              << "\n[new phone]: ";
    std::string newPhone;
    std::cin >> newPhone;
    if (agendaService_.updateUserPhone(userName_, userPassword_, newPhone))
        std::cout << "\n[update user phone] succeed!\n";
    else
        std::cout << "\n[error] update phone fail!";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::updateMeetingTitle() {
    system("clear");
    std::cout << "\n[update meeting title] "
              << "Which meeting do you want to update?\n"
              << "\n[title of meeting]: ";
    std::string title;
    std::cin >> title;
    std::cout << "\n[update meeting title] Please input a new title."
              << "\n[new title]: ";
    std::string newTitle;
    std::cin >> newTitle;
    if (agendaService_.updateMeetingTitle(userName_, title, newTitle))
        std::cout << "\n[update meeting title] succeed!\n";
    else
        std::cout << "\n[error] update title fail.\n"
                  << "There is no such meeting "
                  << "or your are not the meeting sponsor.";
    std::cout << "\nPlease input \"back\" for back to main page: ";
    std::string input;
    std::cin >> input;
    while (input != "back") {
        std::cout << "\nWrong instruction.\n"
                  << "\nPlease input \"back\" for back to main page: ";
        std::cin >> input;
    }
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
    std::cout << "\ntitle     sponsor   "
              << "participator   start time        end time\n";
    std::for_each(meetings.begin(), meetings.end(), [&](const Meeting& m) {
        std::cout << std::setiosflags(std::ios::left)
                  << std::setw(10) << m.getTitle()
                  << std::setw(10) << m.getSponsor()
                  << std::setw(15) << m.getParticipator()
                  << std::setw(18)
                  << Date::dateToString(m.getStartDate())
                  << std::setw(18)
                  << Date::dateToString(m.getEndDate())
                  << std::endl;
    });
}

