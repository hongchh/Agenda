#include <list>
#include <string>
#include <fstream>
#include <cstring>
#include <functional>
#include <algorithm>

#include "Storage.h"

Storage* Storage::instance_ = NULL;

Storage::Storage() {
    readFromFile("User.csv");
    readFromFile("Meeting.csv");
}

bool Storage::readFromFile(const char *fpath) {
    if (std::strcmp(fpath, "User.csv") == 0) {
        std::ifstream inFile(fpath);
        if (!inFile) return false;
        std::string line;
        bool firstLine = true;
        while (std::getline(inFile, line) && !inFile.eof()) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            if (line.size() == 0) continue;
            std::string name = "", password = "", email = "", phone = "";
            int i;
            line += ",\"";
            for (i = 1; !(line[i] == '\"' && line[i+1] == ','
                          && line[i+2] == '\"'); ++i)
                name += line[i];
            for (i += 3; !(line[i] == '\"' && line[i+1] == ','
                           && line[i+2] == '\"'); ++i)
                password += line[i];
            for (i += 3; !(line[i] == '\"' && line[i+1] == ','
                           && line[i+2] == '\"'); ++i)
                email += line[i];
            for (i += 3; !(line[i] == '\"' && line[i+1] == ','
                           && line[i+2] == '\"'); ++i)
                phone += line[i];
            User u(name, password, email, phone);
            userList_.push_back(u);
        }
        inFile.close();
        return true;
    } else if (std::strcmp(fpath, "Meeting.csv") == 0) {
        std::ifstream inFile(fpath);
        if (!inFile) return false;
        std::string line;
        bool firstLine = true;
        while (std::getline(inFile, line) && !inFile.eof()) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            if (line.size() == 0) continue;
            std::string sponsor = "", participator = "";
            std::string start = "", end = "", title = "";
            int i;
            line += ",\"";
            for (i = 1; !(line[i] == '\"' && line[i+1] == ','
                          && line[i+2] == '\"'); ++i)
                sponsor += line[i];
            for (i += 3; !(line[i] == '\"' && line[i+1] == ','
                           && line[i+2] == '\"'); ++i)
                participator += line[i];
            for (i += 3; !(line[i] == '\"' && line[i+1] == ','
                           && line[i+2] == '\"'); ++i)
                start += line[i];
            for (i += 3; !(line[i] == '\"' && line[i+1] == ','
                           && line[i+2] == '\"'); ++i)
                end += line[i];
            for (i += 3; !(line[i] == '\"' && line[i+1] == ','
                           && line[i+2] == '\"'); ++i)
                title += line[i];
            Date sd = Date::stringToDate(start);
            Date ed = Date::stringToDate(end);
            Meeting m(sponsor, participator, sd, ed, title);
            meetingList_.push_back(m);
        }
        inFile.close();
        return true;
    } else {
        return false;
    }
}

bool Storage::writeToFile(const char *fpath) {
    if (std::strcmp(fpath, "User.csv") == 0) {
        std::ofstream outFile(fpath);
        if (!outFile) return false;
        outFile << "\"name\",\"password\",\"email\",\"phone\"" << std::endl;
        for (std::list<User>::iterator i = userList_.begin();
             i != userList_.end(); ++i) {
            outFile << "\"" << i->getName() << "\",\""
                    << i->getPassword() << "\",\""
                    << i->getEmail() << "\",\""
                    << i->getPhone() << "\"" << std::endl;
        }
        outFile.close();
        return true;
    } else if (std::strcmp(fpath, "Meeting.csv") == 0) {
        std::ofstream outFile(fpath);
        if (!outFile) return false;
        outFile << "\"sponsor\",\"participator\",\"sdate\",\"edate\","
                << "\"title\"" << std::endl;
        for (std::list<Meeting>::iterator i = meetingList_.begin();
             i != meetingList_.end(); ++i) {
            outFile << "\"" << i->getSponsor() << "\",\""
                    << i->getParticipator() << "\",\""
                    << Date::dateToString(i->getStartDate()) << "\",\""
                    << Date::dateToString(i->getEndDate()) << "\",\""
                    << i->getTitle() << "\"" << std::endl;

        }
        outFile.close();
        return true;
    } else {
        return false;
    }
}

Storage* Storage::getInstance() {
    if (instance_ == NULL) instance_ = new Storage();
    return instance_;
}

Storage::~Storage() {
    sync();
    instance_ = NULL;
}

void Storage::createUser(const User& user) {
    userList_.push_back(user);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
    std::list<User> users;
    std::for_each(userList_.begin(), userList_.end(), [&](const User& user) {
        if (filter(user)) users.push_back(user);
    });
    return users;
}

int Storage::updateUser(std::function<bool(const User&)> filter,
            std::function<void(User&)> switcher) {
    int num = 0;
    std::for_each(userList_.begin(), userList_.end(), [&](User& user) {
        if (filter(user)) {
            switcher(user);
            ++num;
        }
    });
    return num;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
    int num = 0;
    for (std::list<User>::iterator i = userList_.begin();
         i != userList_.end(); ++i) {
        if (filter(*i)) {
            i = userList_.erase(i);
            --i;
            ++num;
        }
    }
    return num;
}

void Storage::createMeeting(const Meeting& meet) {
    meetingList_.push_back(meet);
}

std::list<Meeting> Storage::queryMeeting(
        std::function<bool(const Meeting&)> filter) {
    std::list<Meeting> meets;
    std::for_each(meetingList_.begin(), meetingList_.end(),
                 [&](const Meeting& meet) {
        if (filter(meet)) meets.push_back(meet);
    });
    return meets;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
        std::function<void(Meeting&)> switcher) {
    int num = 0;
    std::for_each(meetingList_.begin(), meetingList_.end(),
                  [&](Meeting& meet) {
        if (filter(meet)) {
            switcher(meet);
            ++num;
        }
    });
    return num;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
    int num = 0;
    for (std::list<Meeting>::iterator i = meetingList_.begin();
         i != meetingList_.end(); ++i) {
        if (filter(*i)) {
            i = meetingList_.erase(i);
            --i;
            ++num;
        }
    }
    return num;
}

bool Storage::sync() {
    return writeToFile("User.csv") && writeToFile("Meeting.csv");
}

