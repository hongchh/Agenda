#include <string>
#include "Meeting.h"

Meeting::Meeting(): sponsor_(""), participator_(""),
                    startDate_(1000, 1, 1, 0, 0),
                    endDate_(1000, 1, 1, 0, 1), title_("") {}

Meeting::Meeting(std::string sponsor, std::string participator,
                 Date startTime, Date endTime,
                 std::string title): sponsor_(sponsor),
                 participator_(participator), startDate_(startTime),
                 endDate_(endTime), title_(title) {}

std::string Meeting::getSponsor() const {
    return sponsor_;
}

void Meeting::setSponsor(std::string sponsor) {
    sponsor_ = sponsor;
}

std::string Meeting::getParticipator() const {
    return participator_;
}

void Meeting::setParticipator(std::string participator) {
    participator_ = participator;
}

Date Meeting::getStartDate() const {
    return startDate_;
}

void Meeting::setStartDate(Date startTime) {
    startDate_ = startTime;
}

Date Meeting::getEndDate() const {
    return endDate_;
}

void Meeting::setEndDate(Date endTime) {
    endDate_ = endTime;
}

std::string Meeting::getTitle() const {
    return title_;
}

void Meeting::setTitle(std::string title) {
    title_ = title;
}

