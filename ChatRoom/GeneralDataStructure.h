#ifndef GENERALDATASTRUCTURE_H
#define GENERALDATASTRUCTURE_H
#endif // GENERALDATASTRUCTURE_H
#include <QString>

struct MemberInfo{
    int Sex;
    QString Name;
    char MacAddr[6];
    QString Number;
    QString Department;
    QString PersonalProfile;
};

struct GroupInfo{
    char ID[14];
    QString Name;
    QList<MemberInfo> Members;
};

enum MessageType{
    String,
    File,
    Image
};

struct Message{
    char Type;
    char ID[14];
    unsigned int Time;
    char Sender_MacAddr[6];
    char Recipient_MacAddr[6];
    QString Content;
};
