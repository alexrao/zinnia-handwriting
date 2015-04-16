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
#include <QtCore/QDebug>
#include <QtGui/QPainter> /* QPainter */


size_t handwritor::writor_width_fixed = 400;
size_t handwritor::writor_height_fixed = 400;
int handwritor::writor_pen_w_fixed = 4;


#define __STLST_AL \
	"background-color: #87cefa; color: #ff0000; font-weight: bold; " \
	"border-radius: 8px"


handwritor::handwritor (int * ret, char * err, QWidget * focus,
	const char * model, QWidget * parent)
	: QWidget(parent), allpage(0), index(0) {
	int i, open_result;
	char errstr[HANDWRITOR_ERR_MIN];
	QSpacerItem * spacer;
	QPalette palette;
	QFont font;

	this->destroyed = false;

	this->writor_layout = NULL;
	this->option_layout = NULL;
	this->candidate_layout = NULL;

	this->recognizer = NULL;
	this->recognizer = zinnia_recognizer_new();/* create recognizer engine */
	/* open model */
	if (model) {
		open_result = zinnia_recognizer_open(this->recognizer, model);
	} else {
		open_result = zinnia_recognizer_open(this->recognizer,
			HANDWRITOR_MODEL_DFT);
	}
	if (! open_result) {
		memset(errstr, 0, HANDWRITOR_ERR_MIN);
		strncpy(errstr, zinnia_recognizer_strerror(this->recognizer),
			HANDWRITOR_ERR_MIN - 1);
		if (err) {
			strncpy(err, errstr, HANDWRITOR_ERR_MIN - 1);
		}
		if (ret) {
			*ret = -1;/* zinnia_recognizer_open fail */
		}
		std::cerr << errstr << std::endl;
		goto fail_return;
	} /* ! open_result */

	/* ready to recognize */
	recogtimer.setInterval(1000);
	recogtimer.stop();
	QObject::connect(&recogtimer, SIGNAL(timeout()), this, SLOT(recognize()));

	/* writor */
	this->setContentsMargins(0, 0, 0, 0);
	this->setFixedSize(writor_width_fixed, writor_height_fixed);
	this->setAutoFillBackground(true);
	palette.setColor(QPalette::Background, QColor(0xff, 0xff, 0xff));
	this->setPalette(palette);

	master_layout= new QVBoxLayout(this);

	this->writor_layout = new QHBoxLayout();
	this->writor_layout->setContentsMargins(0, 0, 0, 0);

	spacer = new QSpacerItem(handwritor::writor_width_fixed - 64 - 10,
		handwritor::writor_height_fixed - 64 - 10);
	this->writor_layout->addItem(spacer);

	this->option_layout = new QVBoxLayout();
	this->option_layout->setContentsMargins(0, 0, 0, 0);

	spacer = new QSpacerItem(36, 24);
	this->option_layout->addItem(spacer);

	this->up = new QPushButton(tr("<<"), this);
	this->up->setFixedSize(36, 36);
	font.setPixelSize(14);
	this->up->setFont(font);
	this->up->setStyleSheet(__STLST_AL);
	this->option_layout->addWidget(this->up);

	spacer = new QSpacerItem(36, 24);
	this->option_layout->addItem(spacer);

	this->down = new QPushButton(tr(">>"), this);
	this->down->setFixedSize(36, 36);
	this->down->setFont(font);
	this->down->setStyleSheet(__STLST_AL);
	this->option_layout->addWidget(this->down);

	spacer = new QSpacerItem(36, 24);
	this->option_layout->addItem(spacer);

	this->option_layout->setAlignment(this->up,
		Qt::AlignRight | Qt::AlignVCenter);
	this->option_layout->setAlignment(this->down,
		Qt::AlignRight | Qt::AlignVCenter);
	this->option_layout->setStretch(0, 1);
	this->option_layout->setStretch(1, 1);
	this->option_layout->setStretch(2, 1);
	this->option_layout->setStretch(3, 1);
	this->option_layout->setStretch(4, 1);

	/*
	this->option_layout->setStretch(0, 7);
	this->option_layout->setStretch(1, 1);
	*/

	this->candidate_layout = new QHBoxLayout();
	this->candidate_layout->setContentsMargins(5, 0, 5, 0);
	/* ready candidate_btns */
	for (i = 0; i < 10; ++i) {
		candidate_btns[i] = new QPushButton(this);
		candidate_btns[i]->setFixedSize(36, 36);
		candidate_btns[i]->setFont(font);
		candidate_btns[i]->setStyleSheet(__STLST_AL);
		this->candidate_layout->addWidget(candidate_btns[i]);
	}

	this->writor_layout->addLayout(this->option_layout);
	this->writor_layout->setAlignment(this->option_layout, Qt::AlignCenter);

	master_layout->addLayout(this->writor_layout, 0);
	master_layout->addLayout(this->candidate_layout, 1);

	for (i = 0; i < 10; ++i) {
		this->candidate_layout->setAlignment(candidate_btns[i],
			Qt::AlignHCenter);
	}

	for (i = 0; i < 10; ++i) {
		QObject::connect(candidate_btns[i], SIGNAL(clicked()), this,
		SLOT(chooseQchar()));
	}
	QObject::connect(up, SIGNAL(clicked()), this, SLOT(turnpageup()));
	QObject::connect(down, SIGNAL(clicked()), this, SLOT(turnpagedown()));

	this->genbuttonstate();

	return;

fail_return:
	this->destroy();

} /* handwritor::handwritor */


int handwritor::destroy (void) {
	if (destroyed) {
		return -1;
	}

	if (this->candidate_layout) {
		QHBoxLayout * d = this->candidate_layout;
		this->candidate_layout = NULL;
		delete d;
	}

	if (this->option_layout) {
		QVBoxLayout * d = this->option_layout;
		this->option_layout = NULL;
		delete d;
	}

	if (this->writor_layout) {
		QHBoxLayout * d = this->writor_layout;
		this->writor_layout = NULL;
		delete d;
	}

	if (this->master_layout) {
		QVBoxLayout * d = this->master_layout;
		this->master_layout = NULL;
		delete d;
	}

	if (this->recognizer) {
		zinnia_recognizer_t * d = this->recognizer;
		this->recognizer = NULL;
		(void)zinnia_recognizer_close(d);
		(void)zinnia_recognizer_destroy(d);
	}

	this->destroyed = true;
	return 0;
} /* handwritor::destroy */


void handwritor::mousePressEvent(QMouseEvent *event) {
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

void handwritor::genbuttonstate (void) {
	this->up->hide();
	this->down->hide();
    for (int i=0; i<10;i++) {
        candidate_btns[i]->hide();
        if (index<allpage) {
            if (index * 10 + i < dstr.count()) {
                candidate_btns[i]->setText(dstr[index * 10+i]);
                candidate_btns[i]->show();
				this->up->show();
				this->down->show();
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

void handwritor::chooseQchar (void) {
	static QString chose;

	/*
    QPushButton* push=static_cast<QPushButton *>(sender());
    emit routestring(push->text()[0]);
	*/

	QPushButton * b = static_cast<QPushButton *>(sender());
	chose.clear();
	chose = b->text();
    emit routestring(chose[0]);
	// std::cout << "SELECTED:" << chose.toLocal8Bit().data() << std::endl;
	fprintf(stdout, "SELECTED: %s\n", chose.toUtf8().data());
	fflush(stdout);

	this->up->hide();
	this->down->hide();
    for (int i=0; i<10;i++) {
        candidate_btns[i]->hide();
    }
} /* handwritor::chooseQchar */

void handwritor::stok2qchar()
{
    zinnia_result_t *result;
    LineStroke * l;
    character = zinnia_character_new();

    dstr.clear();
    zinnia_character_clear(character);
    zinnia_character_set_width(character, writor_width_fixed);
    zinnia_character_set_height(character, writor_height_fixed);

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

	/*
	painter.drawLine(0, 125, 250, 125);
	painter.drawLine(125, 0, 125, 250);
	*/
	/* - */
    QPen pen_b;
	pen_b.setStyle(Qt::DotLine);
    painter.setPen(pen_b);
	painter.drawLine(0, handwritor::writor_height_fixed/2,
		handwritor::writor_width_fixed, handwritor::writor_height_fixed/2);
	/* | */
	painter.drawLine(handwritor::writor_width_fixed/2, 0,
		handwritor::writor_width_fixed/2, handwritor::writor_height_fixed);

    QPen pen;
    pen.setWidth(handwritor::writor_pen_w_fixed);
    painter.setPen(pen);

	// painter.save();
	// painter.restore();

    LineStroke *cl;
    // 已经录入的笔画
    for (int i = 0; i < strokes.count() ; i++ ) {
        cl =&strokes[i];

        for(int j = 0 ;j+4 < cl->segments ; j += 4) {
            painter.drawLine((float)cl->points[j]->x(),
				(float)cl->points[j]->y(),
				(float)cl->points[j+4]->x(),
				(float)cl->points[j+4]->y());
        }
    }

    // 当下笔画
    if (currentstroke.segments &&currentstroke.points[0]) {
        for (int j = 0 ; j+4 < currentstroke.segments ; j+=4) {
            painter.drawLine((float)currentstroke.points[j]->x(),
				(float)currentstroke.points[j]->y(),
				(float)currentstroke.points[j+4]->x(),
				(float)currentstroke.points[j+4]->y());
        }
    }
}


/*
 * end of file handwritor.cpp
 */
