#ifndef QHWR_H
#define QHWR_H

#include <QtGui>
#include <QPoint>
#include <QVector>
#include <QStringList>
#include "zinnia.h"
class LineStroke
{
public:
    LineStroke() { segments=0;}
    LineStroke(const LineStroke& l1)
    {
        segments=l1.segments;
        foreach(QPoint* point ,l1.points)
        {
            QPoint* po=new QPoint((*point).x(),(*point).y());
            points.append(po);
        }
    }
    int		segments; //包含有的段数目
    QVector <QPoint*> points; //包含的用来构成笔画的点
    //    ~LineStroke() {
    //        foreach(QPoint* point , points)
    //        {
    //            delete point;
    //        }
    //        points.clear();
    //        segments=0;
    //    }

};
class QHWR : public QWidget
{
    enum EState
    {
        Press,
        Move,
        Release,
        Choose,    //选择阶段
    };
    Q_OBJECT
public:
    QHWR(QWidget* parent=0);
    void mouseMoveEvent (QMouseEvent * event);
    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);
    void paintEvent(QPaintEvent * event);
    void genbuttonstate();
    void stok2qchar();
    void append_stroke(LineStroke& stroke);
    EState mouse_state;
    LineStroke currentstroke;
    QVector<LineStroke>  strokes;
    zinnia_character_t *character;
    zinnia_recognizer_t *recognizer;
signals:
    void routestring(QChar);     //向其他窗口传递QChar
protected slots:
    void recognize();
    void turnpageup();
    void turnpagedown();
    void chooseQchar();
private:
    QPushButton* LButtons[10];
    QPushButton *up;
    QPushButton *down;
    QTimer recogtimer;
    QStringList dstr;
    int index;
    int allpage;
};

#endif // QHWR_H
