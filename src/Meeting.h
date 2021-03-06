#ifndef MEETING_H
#define MEETING_H
#include "Date.h"

class Meeting {
    public:
        Meeting();
        Meeting(string sponsor, string participator,
        Date startTime, Date endTime, string title);
        string getSponsor() const;
        void setSponsor(string sponsor);
        string getParticipator() const;
        void setParticipator(string participator);
        Date getStartDate() const;
        void setStartDate(Date startTime);
        Date getEndDate() const;
        void setEndDate(Date endTime);
        string getTitle() const;
        void setTitle(string title);
        friend bool operator<(const Meeting& m1, const Meeting& m2);
    private:
        string sponsor_;
        string participator_;
        Date startDate_;
        Date endDate_;
        string title_;
};

#endif

