/* ===========================================================================
 *
 *       Filename:  handwritor.h
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


#if !defined(_HANDWRITOR_H_)
#define _HANDWRITOR_H_ (1)


#if !defined(ID_QT_VERSION)
#	error "ID_QT_VERSION NOT defined"
#endif

#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>

#if (ID_QT_VERSION < 0x050000)
#	include <QtGui/QWidget>
#	include <QtGui/QPushButton>
#	include <QtGui/QHBoxLayout>
#	include <QtGui/QVBoxLayout>
#else
#	include <QtWidgets/QWidget>
#	include <QtWidgets/QPushButton>
#	include <QtWidgets/QHBoxLayout>
#	include <QtWidgets/QVBoxLayout>
#endif

#include <zinnia.h> /* zinnia_character_t .. */
#include "LineStroke.h" /* class LineStroke */


typedef enum _hw_state_t {
	Press,
	Move,
	Release,
	Choose,/* 选择阶段 */
} hw_state_t;


#define HANDWRITOR_MODEL_DFT "handwriting-zh_CN.model"
#define HANDWRITOR_ERR_MIN (64)


class handwritor : public QWidget {
    Q_OBJECT

/* err min HANDWRITOR_ERR_MIN */
public: handwritor(int * ret, char * err, QWidget * focus,
	const char * model = 0, QWidget * parent = 0);
public: ~handwritor (void) { destroy(); }
public: int destroy(void);
public: bool is_destroyed (void) { return destroyed; }
private: bool destroyed;
private: static size_t writor_width_fixed;
private: static size_t writor_height_fixed;
private: static int writor_pen_w_fixed;

signals: void routestring(QChar c);/* 向其他窗口传递QChar */

/* evt */
public: void mouseMoveEvent(QMouseEvent * event);
public: void mousePressEvent(QMouseEvent * event);
public: void mouseReleaseEvent(QMouseEvent * event);
public: void paintEvent(QPaintEvent * event);

public: void genbuttonstate(void);
public: void stok2qchar(void);
public: void append_stroke(LineStroke& stroke);
public: hw_state_t mouse_state;

public: LineStroke currentstroke;
public: QVector<LineStroke>  strokes;
public: zinnia_character_t * character;
public: zinnia_recognizer_t * recognizer;

protected slots: void recognize(void);
protected slots: void turnpageup(void);
protected slots: void turnpagedown(void);
protected slots: void chooseQchar(void);

private: QVBoxLayout * master_layout;
private: QHBoxLayout * writor_layout;
private: QVBoxLayout * option_layout;
private: QHBoxLayout * candidate_layout;
private: QPushButton* candidate_btns[10];
	QPushButton *up;
	QPushButton *down;
	QTimer recogtimer;
	QStringList dstr;
	int index;
	int allpage;
}; /* class handwritor */


#endif /* !defined(_HANDWRITOR_H_) */


/*
 * end of file handwritor.h
 */
