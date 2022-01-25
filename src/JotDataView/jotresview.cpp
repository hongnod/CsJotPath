
#include "jotresview.h"
#include "defs.h"
#include "jotrouteview.h"




JotResView::JotResView(QWidget *parent) : QWidget(parent)
{

     header  = new QHeaderView(Qt::Horizontal);

     //*This Part is used for test---Start
     QStandardItemModel *model = new QStandardItemModel(0,3);//Need only head,without data
     header->setFixedHeight(HEADER_H);

     header->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
     header->setModel(model);
     header->setVisible(true);

     //header->setMinimumSectionSize(2*metaWidth);
     header->resizeSection(0,metaWidth);
     header->setSectionResizeMode(QHeaderView::Fixed);
     model->setHeaderData(0,Qt::Horizontal,QString("序号"));
     model->setHeaderData(1,Qt::Horizontal,QString("拓扑"));
     model->setHeaderData(2,Qt::Horizontal,QString("名称"));
     //model->setHeaderData(3,Qt::Horizontal,"端口");

     NODE  A{"A",ntELEMENT,3,0,0,4,2};
     NODE  B{"B",ntELEMENT,2,4,1,3,1};
     NODE  C{"C",ntELEMENT,2,7,0,3,1};
     NODE  D{"D",ntELEMENT,2,10,1,3,1};
     NODE  E{"E",ntELEMENT,3,13,0,4,2};

     NODE  A1{"A1--just for tesing long text name,hahahahhahha",ntPORT,0,1,0,1,1};
     NODE  A2{"A2---测试一个更长的中文名字，看看是不是也可以应付得了，哈哈哈哈哈哈达到顶峰",ntPORT,0,2,0,1,1};
     NODE  A3{"A3",ntPORT,0,3,1,1,1};
     NODE  B1{"B1",ntPORT,0,5,1,1,1};
     NODE  B2{"B2",ntPORT,0,6,1,1,1};
     NODE  C1{"C1",ntPORT,0,8,0,1,1};
     NODE  C2{"C2",ntPORT,0,9,0,1,1};
     NODE  D1{"D1",ntPORT,0,11,1,1,1};
     NODE  D2{"D2",ntPORT,0,12,1,1,1};
     NODE  E1{"E1",ntPORT,0,14,0,1,1};
     NODE  E2{"E2",ntPORT,0,15,1,1,1};
     NODE  E3{"E3",ntPORT,0,16,0,1,1};
     QList<NODE> nodes;



     QList<LINK> lines;
     LINK AtoC{&A,&C,dirDUAL,ltRELATE,"AtoC"};
     LINK AtoB{&A,&B,dirDUAL,ltRELATE,"AtoB"};
     A.next <<AtoC <<AtoB;
     C.pre <<AtoC; B.pre<<AtoB;
     lines  <<AtoC <<AtoB;

     LINK BtoD{&B,&D,dirDUAL,ltRELATE,"BtoD"};
     B.next <<BtoD; D.pre <<BtoD;
     lines <<BtoD;

     LINK CtoE{&C,&E,dirDUAL,ltRELATE,"CtoE"};
     C.next <<CtoE; E.pre <<CtoE;
     lines <<CtoE;

     LINK DtoE{&D,&E,dirDUAL,ltRELATE,"DtoE"};
     D.next <<DtoE; E.pre <<DtoE;
     lines <<DtoE;

     LINK A1toA2{&A1,&A2,dirDUAL,ltCROSS,"A1toA2"};
     LINK A1toA3{&A1,&A3,dirDUAL,ltCROSS,"A1toA3"};
     A1.next <<A1toA2 <<A1toA3;
     A2.pre <<A1toA2; A3.pre <<A1toA3;
     lines <<A1toA2 <<A1toA3;

     LINK A2toC1{&A2,&C1,dirDUAL,ltSNC,"A2toC1"};
     A2.next <<A2toC1; C1.pre <<A2toC1;
     lines  <<A2toC1;
     LINK A3toB1{&A3,&B1,dirDUAL,ltSNC,"A3toB1"};
     A3.next <<A3toB1; B1.pre <<A3toB1;
     lines  <<A3toB1;

     LINK B1toB2{&B1,&B2,dirDUAL,ltCROSS,"B1toB2"};
     B1.next <<B1toB2; B2.pre <<B1toB2;
     lines <<B1toB2;

     LINK B2toD1{&B2,&D1,dirDUAL,ltSNC,"B2toD1"};
     B2.next <<B2toD1; D1.pre <<B2toD1;
     lines <<B2toD1;

     LINK C1toC2{&C1,&C2,dirDUAL,ltCROSS,"C1toC2"};
     C1.next <<C1toC2; C2.pre <<C1toC2;
     lines <<C1toC2;

     LINK C2toE1{&C2,&E1,dirDUAL,ltSNC,"C2toE1"};
     C2.next <<C2toE1; E1.pre <<C2toE1;
     lines  <<C2toE1;

     LINK D1toD2{&D1,&D2,dirDUAL,ltCROSS,"D1toD2"};
     D1.next <<D1toD2; D2.pre <<D1toD2;
     lines  <<D1toD2;

     LINK D2toE2{&D2,&E2,dirDUAL,ltSNC,"D2toE2"};
     D2.next <<D2toE2; E2.pre <<D2toE2;
     lines <<D2toE2;

     LINK E1toE3{&E1,&E3,dirDUAL,ltCROSS,"E1toE3"};
     E1.next <<E1toE3; E3.pre <<E1toE3;
     lines <<E1toE3;

     LINK E2toE3{&E2,&E3,dirDUAL,ltCROSS,"E2toE3"};
     E2.next <<E2toE3; E3.pre <<E2toE3;
     lines <<E2toE3;

     A.children <<&A1<<&A2 <<&A3;
     B.children <<&B1 <<&B2;
     C.children <<&C1 <<&C2;
     D.children <<&D1 <<&D2;
     E.children <<&E1 <<&E2 <<&E3;
     nodes <<A <<B <<C <<D <<E <<A1 <<A2 <<A3 <<B1 <<B2 <<C1 <<C2 <<D1 <<D2 <<E1 <<E2 <<E3;


 //*This Part is used for test---END
     qDebug() << QString("插入行数：").formatArg(model->rowCount());

     route = new JotRouteView();
     route->SetHeader(header);

     route->SetData(&nodes,&lines);
     route->DrawRoute();
     //NetPlanView  *plan = new NetPlanView();
     QVBoxLayout *vbox = new QVBoxLayout();//创建布局

     vbox->addWidget(header);
     vbox->addWidget(route);
     //vbox->addWidget(plan);

     vbox->setSpacing(0);  //设置间距与边缘空白
     vbox->setContentsMargins(0,0,0,0);
     setLayout(vbox);
     connect(route,&JotRouteView::sigHsliderMove,this,&JotResView::slotMoveHeader);
     connect(header,&QHeaderView::sectionResized,route, &JotRouteView::slotMoveWithHead);
             //sectionResized(int logicalIndex, int oldSize, int newSize)
}


void JotResView::slotMoveHeader(int val)
{
    header->setOffset(val);
}
