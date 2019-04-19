#ifndef GENERALDATASTRUCTURE_H
#define GENERALDATASTRUCTURE_H
#endif // GENERALDATASTRUCTURE_H
#include <QString>
#include <QIcon>
#include <QByteArray>

struct InfoCard{
    QIcon Icon;
    QString Name;
    QString Profile;
};

struct MemberInfoCard :public InfoCard{
    int             Sex;
    char            MacAddr[6];
    unsigned int    IpAddr;
    QString         PhoneNumber;
    QString         Department;
};

struct GroupInfoCard :public InfoCard{
    QList<MemberInfoCard> Members;
};

enum NetPackageType{
    GetMemberInfo = 100,
};

struct NetPackage{
    unsigned int    OrganizationNumber;
    unsigned char   StartTag;
    unsigned short  Type;
    QByteArray      Data;
    unsigned char   StartTag;
};

struct Message{
    char ID[14];
    unsigned int Time;
    QString Content;
};

