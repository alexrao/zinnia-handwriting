/* ===========================================================================
 *
 *       Filename:  handwritor.cpp
 *
 *    Description:  handwritor (qt)
 *
 * - Mode: 644
 * - NOTE. NOT use "dos"
 * - Updated: TODO
 *
 *        Version:  1.0.0
 *        Created:  2015-04-16 10:13:08
 *       Revision:  1.0.0
 *       Compiler:  moc/g++
 *
 *         Author:  Yui Wong, email: yuiwong@126.com
 *   Organization:  ""
 *        License:  LGPLv3
 *
 *  This file is part of zinnia-handwriting.
 *
 *  zinnia-handwriting
 *  is free software: you can redistribute it
 *  and/or modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  zinnia-handwriting
 *  is distributed in the hope that it will be
 *  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with zinnia-handwriting.
 *  If not, see <http://www.gnu.org/licenses/>.
 *
 * ===========================================================================
 */


#include <iostream> /* std .. */
#include "handwritor.h" /* class handwritor */
#include <QPainter> /* QPainter */


handwritor::handwritor(QWidget* parent):QWidget(parent),allpage(0),index(0)
{
    recognizer= zinnia_recognizer_new();                           //注册引擎
    if (!zinnia_recognizer_open(recognizer,"handwriting-zh_CN.model")) {
        std::cerr << zinnia_recognizer_strerror(recognizer) << std::endl;
        return;
    }

    recogtimer.setInterval(1000);
    recogtimer.stop();
    connect(&recogtimer,SIGNAL(timeout()),this,SLOT(recognize()));


    LButtons[0]=new QPushButton(this);
    LButtons[0]->setGeometry(0,250,20,20);
    connect(LButtons[0],SIGNAL(clicked()),this,SLOT(chooseQchar()));

    LButtons[1]=new QPushButton(this);
    LButtons[1]->setGeometry(25,250,20,20);
    connect(LButtons[1],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[2]=new QPushButton(this);
    LButtons[2]->setGeometry(50,250,20,20);
    connect(LButtons[2],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[3]=new QPushButton(this);
    LButtons[3]->setGeometry(75,250,20,20);
    connect(LButtons[3],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[4]=new QPushButton(this);
    LButtons[4]->setGeometry(100,250,20,20);
    connect(LButtons[4],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[5]=new QPushButton(this);
    LButtons[5]->setGeometry(125,250,20,20);
    connect(LButtons[5],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[6]=new QPushButton(this);
    LButtons[6]->setGeometry(150,250,20,20);
    connect(LButtons[6],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[7]=new QPushButton(this);
    LButtons[7]->setGeometry(175,250,20,20);
    connect(LButtons[7],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[8]=new QPushButton(this);
    LButtons[8]->setGeometry(200,250,20,20);
    connect(LButtons[8],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    LButtons[9]=new QPushButton(this);
    LButtons[9]->setGeometry(225,250,20,20);
    connect(LButtons[9],SIGNAL(clicked()),this,SLOT(chooseQchar()));


    up=new QPushButton(tr("上"),this);
    up->setGeometry(250,250,20,20);
    connect(up,SIGNAL(clicked()),this,SLOT(turnpageup()));

    down=new QPushButton(tr("下"),this);
    connect(down,SIGNAL(clicked()),this,SLOT(turnpagedown()));
    down->setGeometry(275,250,20,20);
    genbuttonstate();
}

void handwritor::mousePressEvent(QMouseEvent *event)
{
    if(mouse_state==Choose)
    {
        strokes.clear();
        update();
    }
    mouse_state=Press;
    recogtimer.stop();

    foreach(QPoint* point,currentstroke.points)
        delete point;
    currentstroke.points.clear();

    currentstroke.segments=1;
    QPoint* point=new QPoint;
    point->setX(event->x());
    point->setY(event->y());
    currentstroke.points.append(point);
}
void handwritor::mouseMoveEvent(QMouseEvent *event)
{
    static int count=0;
    if (mouse_state == (Press|Move)) // 鼠标按下状态
    {
        QPoint* point=new QPoint;
        point->setX(event->x());
        point->setY(event->y());
        currentstroke.points.append(point);
        currentstroke.segments++;
    }
    mouse_state=Move;
    count++;
    if(count%10==0)
        update();
}

void handwritor::mouseReleaseEvent(QMouseEvent *event)
{
    if(mouse_state!=Move)
        return;
    append_stroke(currentstroke);
    update();
    mouse_state=Release;

    currentstroke.segments=0;
    foreach(QPoint* point,currentstroke.points)
        delete point;
    currentstroke.points.clear();

    recogtimer.start();
}

void handwritor::append_stroke(LineStroke& stroke)
{
    LineStroke s;
    s.segments=stroke.segments;
    if(stroke.segments)
    {
        for(int i=0;i<stroke.points.count();i++)
        {
            QPoint* point=new QPoint;
            point->setX(stroke.points[i]->x());
            point->setY(stroke.points[i]->y());
            s.points.append(point);
        }
        strokes.append(stroke);
    }
}
void handwritor::genbuttonstate()
{
    for(int i=0; i<10;i++)
    {
        LButtons[i]->hide();
        if(index<allpage)
        {
            if(index*10+i<dstr.count())
            {
                LButtons[i]->setText(dstr[index*10+i]);
                LButtons[i]->show();
            }
        }
    }

}

void handwritor::turnpageup()
{
    if(index>0)
        index--;
    genbuttonstate();
}

void handwritor::turnpagedown()
{
    if(index<allpage-1)
        index++;
    genbuttonstate();
}

void handwritor::chooseQchar()
{
    QPushButton* push=static_cast<QPushButton*>(sender());
    emit routestring(push->text()[0]);

}

void handwritor::stok2qchar()
{
    zinnia_result_t *result;
    LineStroke * l;
    character = zinnia_character_new();

    dstr.clear();
    zinnia_character_clear(character);
    zinnia_character_set_width(character, 250);
    zinnia_character_set_height(character, 250);


    for(int i=0;i<strokes.size();i++)
    {
        l = &strokes[i];

        for (int j= 0; j < (l->segments); j+=(l->segments/10+1))
        {
            l->points[j]->x(), l->points[j]->y() ;
         //   if(j>2)
         //       j=l->segments-1;
            zinnia_character_add(character, i, l->points[j]->x(), l->points[j]->y());
        }
    }

    result = zinnia_recognizer_classify(recognizer, character, 100);
    if (result == NULL)
    {
        fprintf(stderr, "%s\n", zinnia_recognizer_strerror(recognizer));
        zinnia_character_destroy(character);
      //zinnia_recognizer_destroy(recognizer);
        return ;
    }

    for (int i = 0; i < zinnia_result_size(result); ++i)
    {

        dstr.append(QString::fromUtf8(zinnia_result_value(result, i),3));

       // strcpy(c->charactor,zinnia_result_value(result, i));

        fprintf(stdout, "%s\t%f\n", zinnia_result_value(result, i),
                zinnia_result_score(result, i));
    }

    zinnia_result_destroy(result);
    zinnia_character_destroy(character);
    return;
}

void handwritor::recognize()
{
    recogtimer.stop();
    mouse_state=Choose;
    stok2qchar();
    strokes.clear();
    index=0;

    //向上取整,实现方法
    allpage=((dstr.count()%10)==0)?(dstr.count())/10:(dstr.count())/10+1;
    genbuttonstate();
    update();
}

void handwritor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawLine(0,125,250,125);
    painter.drawLine(125,0,125,250);
    QPen pen;
    pen.setWidth(4);
    painter.setPen(pen);

//    painter.save();

//    painter.restore();

    LineStroke *cl;
    //已经录入的笔画
    for (int i = 0; i < strokes.count() ; i++ )
    {
        cl =&strokes[i];

        for(int j = 0 ;j+4<cl->segments ; j+=4)
        {
            painter.drawLine((float)cl->points[j]->x() , (float)cl->points[j]->y(),(float)cl->points[j+4]->x(),(float)cl->points[j+4]->y());
        }
    }
    //当下笔画
    if ( currentstroke.segments &&currentstroke.points[0] )
    {

        for(int j = 0 ; j+4 < currentstroke.segments ; j+=4)
        {
            painter.drawLine((float)currentstroke.points[j]->x(), (float)currentstroke.points[j]->y(),
                             (float)currentstroke.points[j+4]->x(), (float)currentstroke.points[j+4]->y());
        }
    }
}


/*
 * end of file handwritor.cpp
 */
