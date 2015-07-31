#include <list>
#include <string>

#include "AgendaService.h"

AgendaService::AgendaService() {
    startAgenda();
}

AgendaService::~AgendaService() {
    quitAgenda();
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
    bool notFind = storage_->queryUser([&](const User& user)->bool {
        return user.getName() == userName && user.getPassword() == password;
    }).empty();
    return !notFind;
}

bool AgendaService::userRegister(std::string userName, std::string password,
                                 std::string email, std::string phone) {
    bool notFind = storage_->queryUser([&](const User& user)->bool {
        return user.getName() == userName;
    }).empty();
    if (notFind) {
        User u(userName, password, email, phone);
        storage_->createUser(u);
        storage_->sync();
        return true;
    } else {
        return false;
    }
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
    int delNum = storage_->deleteUser([&](const User& user)->bool {
        return (user.getName() == userName && user.getPassword() == password);
    });
    if (delNum == 0) {
        return false;
    } else {
        deleteAllMeetings(userName);
        storage_->sync();
        return true;
    }
}

std::list<User> AgendaService::listAllUsers() {
    return storage_->queryUser([&](const User& user)->bool {
        return true;
    });
}

bool AgendaService::createMeeting(std::string userName, std::string title,
      std::string participator, std::string startDate, std::string endDate) {
    if (startDate.size() != 16 || endDate.size() != 16)
        return false;
    bool sd = (startDate[0] >= '0' && startDate[0] <= '9' &&
               startDate[1] >= '0' && startDate[1] <= '9' &&
               startDate[2] >= '0' && startDate[2] <= '9' &&
               startDate[3] >= '0' && startDate[3] <= '9' &&
               startDate[5] >= '0' && startDate[5] <= '9' &&
               startDate[6] >= '0' && startDate[6] <= '9' &&
               startDate[8] >= '0' && startDate[8] <= '9' &&
               startDate[9] >= '0' && startDate[9] <= '9' &&
               startDate[11] >= '0' && startDate[11] <= '9' &&
               startDate[12] >= '0' && startDate[12] <= '9' &&
               startDate[14] >= '0' && startDate[14] <= '9' &&
               startDate[15] >= '0' && startDate[15] <= '9' &&
               startDate[4] == '-' && startDate[7] == '-' &&
               startDate[10] == '/' && startDate[13] == ':');
    bool ed = (endDate[0] >= '0' && endDate[0] <= '9' &&
               endDate[1] >= '0' && endDate[1] <= '9' &&
               endDate[2] >= '0' && endDate[2] <= '9' &&
               endDate[3] >= '0' && endDate[3] <= '9' &&
               endDate[5] >= '0' && endDate[5] <= '9' &&
               endDate[6] >= '0' && endDate[6] <= '9' &&
               endDate[8] >= '0' && endDate[8] <= '9' &&
               endDate[9] >= '0' && endDate[9] <= '9' &&
               endDate[11] >= '0' && endDate[11] <= '9' &&
               endDate[12] >= '0' && endDate[12] <= '9' &&
               endDate[14] >= '0' && endDate[14] <= '9' &&
               endDate[15] >= '0' && endDate[15] <= '9' &&
               endDate[4] == '-' && endDate[7] == '-' &&
               endDate[10] == '/' && endDate[13] == ':');
    if (!(sd && ed)) return false;
    Date startD = Date::stringToDate(startDate);
    Date endD = Date::stringToDate(endDate);
    if (!Date::isValid(startD) || !Date::isValid(endD))
        return false;
    if (startD >= endD) return false;
    if (userName == participator) return false;
    bool notFindSpo = storage_->queryUser([&](const User& user)->bool {
        return user.getName() == userName;
    }).empty();
    if (notFindSpo) return false;
    bool notFindPar = storage_->queryUser([&](const User& user)->bool {
        return user.getName() == participator;
    }).empty();
    if (notFindPar) return false;
    bool notFindMeet = storage_->queryMeeting([&](const Meeting& meet)->bool {
        return meet.getTitle() == title;
    }).empty();
    if (!notFindMeet) return false;
    bool isTimeSuit = storage_->queryMeeting([&](const Meeting& meet)->bool {
        if (meet.getSponsor() == userName ||
            meet.getParticipator() == userName) {
            Date s = meet.getStartDate();
            Date e = meet.getEndDate();
            if ((e > startD && s < startD) ||
                (e > endD && s < endD) ||
                (e <= endD && s >= startD)) return true;
            else return false;
        } else {
            return false;
        }
    }).empty();
    if (!isTimeSuit) return false;
    isTimeSuit = storage_->queryMeeting([&](const Meeting& meet)->bool {
        if (meet.getSponsor() == participator ||
            meet.getParticipator() == participator) {
            Date s = meet.getStartDate();
            Date e = meet.getEndDate();
            if ((e > startD && s < startD) ||
                (e > endD && s < endD) ||
                (e <= endD && s >= startD)) return true;
            else return false;
        } else {
            return false;
        }
    }).empty();
    if (!isTimeSuit) return false;
    Meeting m(userName, participator, startD, endD, title);
    storage_->createMeeting(m);
    storage_->sync();
    return true;
}

bool AgendaService::updateUserPassword(std::string userName,
                      std::string password, std::string newPassword) {
    int updateNum = storage_->updateUser([&](const User& u)->bool {
        return u.getName() == userName && u.getPassword() == password;
    }, [&](User& u) { u.setPassword(newPassword); });
    if (updateNum == 0) {
        return false;
    } else {
        storage_->sync();
        return true;
    }
}

bool AgendaService::updateUserEmail(std::string userName,
                      std::string password, std::string email) {
    int updateNum = storage_->updateUser([&](const User& u)->bool {
        return u.getName() == userName && u.getPassword() == password;
    }, [&](User& u) { u.setEmail(email); });
    if (updateNum == 0) {
        return false;
    } else {
        storage_->sync();
        return true;
    }
}

bool AgendaService::updateUserPhone(std::string userName,
                      std::string password, std::string phone) {
    int updateNum = storage_->updateUser([&](const User& u)->bool {
        return u.getName() == userName && u.getPassword() == password;
    }, [&](User& u) { u.setPhone(phone); });
    if (updateNum == 0) {
        return false;
    } else {
        storage_->sync();
        return true;
    }
}


std::list<Meeting> AgendaService::meetingQuery(std::string userName,
                                               std::string title) {
    return storage_->queryMeeting([&](const Meeting& meet)->bool {
        return (meet.getSponsor() == userName ||
                meet.getParticipator() == userName) &&
                meet.getTitle() == title;
    });
}

std::list<Meeting> AgendaService::meetingQuery(std::string userName,
            std::string startDate, std::string endDate) {
    std::list<Meeting> ml;
    if (startDate.size() != 16 || endDate.size() != 16)
        return ml;
    if (!Date::isValid(Date::stringToDate(startDate)) ||
        !Date::isValid(Date::stringToDate(endDate)))
        return ml;
    return storage_->queryMeeting([&](const Meeting& meet)->bool {
        return ((meet.getSponsor() == userName ||
                 meet.getParticipator() == userName) &&
               ((meet.getStartDate() >= Date::stringToDate(startDate) &&
                meet.getEndDate() <= Date::stringToDate(endDate)) ||
                (meet.getStartDate() >= Date::stringToDate(startDate) &&
                 meet.getStartDate() <= Date::stringToDate(endDate)) ||
                (meet.getEndDate() >= Date::stringToDate(startDate) &&
                 meet.getEndDate() <= Date::stringToDate(endDate))));
    });
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting& meet)->bool {
        return meet.getSponsor() == userName ||
               meet.getParticipator() == userName;
    });
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
    return storage_->queryMeeting([&](const Meeting& meet)->bool {
        return meet.getSponsor() == userName;
    });
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(
                                           std::string userName) {
    return storage_->queryMeeting([&](const Meeting& meet)->bool {
        return meet.getParticipator() == userName;
    });
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
    int delNum = storage_->deleteMeeting([&](const Meeting& meet)->bool {
        return meet.getSponsor() == userName &&
               meet.getTitle() == title;
    });
    if (delNum == 0) {
        return false;
    } else {
        storage_->sync();
        return true;
    }
}

bool AgendaService::deleteAllMeetings(std::string userName) {
    int delNum = storage_->deleteMeeting([&](const Meeting& meet)->bool {
        return meet.getSponsor() == userName ||
               meet.getParticipator() == userName;
    });
    if (delNum == 0) {
        return false;
    } else {
        storage_->sync();
        return true;
    }
}

bool AgendaService::updateMeetingTitle(std::string userName, std::string title,
                                       std::string newTitle) {
    int updateNum = storage_->updateMeeting([&](const Meeting& m)->bool {
        return m.getSponsor() == userName && m.getTitle() == title;
    }, [&](Meeting& m) { m.setTitle(newTitle); });
    if (updateNum == 0) {
        return false;
    } else {
        storage_->sync();
        return true;
    }
}

void AgendaService::startAgenda() {
    storage_ = Storage::getInstance();
}

void AgendaService::quitAgenda() {
    if (storage_ != NULL) delete storage_;
    storage_ = NULL;
}

