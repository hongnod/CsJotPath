#ifndef DEFS_H
#define DEFS_H

#define VALUE_DIS 2
//#define TITLE_H  20
#define HEADER_H 32
#define TOOLBAR_H 32

#include <QtGui>
const int  metaWidth = 60;
const int  metaHeight = 40;

struct NODE;


enum NODETYPE
{
    ntPATH = 1, //a section represent path
    ntELEMENT, //A network element
    ntPORT   //A port
};
//Q_DECLARE_METATYPE(NODETYPE)

enum DIR
{
    dirFORWARD=1, //uni-direction same to "to"
    dirBACKWARD, //uni-direction reverse to "to"
    dirDUAL   //bidirection
};
//Q_DECLARE_METATYPE(DIR)

enum LINKTYPE
{
  ltCROSS = 1,  //Cross Connection
  ltJUMPER,   //Jumper line between two egress port
  ltSNC,    //Channel,pipe bring by cable connection
  ltCABLE,  //mainly fiber,port connection
  ltBIND,   //mainly for ether port binding to logical port
  ltPROTO, //Protocol driving connetion,such as VLAN
  ltRELATE  //For ELEMETN,SECTION relationship
};
//Q_DECLARE_METATYPE(LINKTYPE)

struct LINK
{

    NODE  *from = nullptr;
    NODE  *to = nullptr;
    DIR         dir;  //direction
    LINKTYPE    lt;   //link type
    QString     lkname;
    LINK& operator=(const LINK&) = default;
};
//Q_DECLARE_METATYPE(LINK)

struct NODE
{

    QString Name;
    NODETYPE type;
    int  childcount;
    int pos_row;
    int pos_col;
    int sz_row;
    int sz_col;
    QList<NODE *> children;
    QList<LINK> pre;
    QList<LINK> next;
    NODE& operator=(const NODE&) = default;
};
//Q_DECLARE_METATYPE(NODE)  //添加本行便于试用 QVariant


#endif // DEFS_H
