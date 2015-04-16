/* ===========================================================================
 *
 *       Filename:  LineStroke.h
 *
 *    Description:  Line Stroke (笔画)
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


#if !defined(_LINESTROKE_H_)
#define _LINESTROKE_H_ (1)


#if !defined(ID_QT_VERSION)
#	error "ID_QT_VERSION NOT defined"
#endif

#include <QtCore/QPoint> /* QPoint */
#include <QtCore/QVector> /* QVector */


class LineStroke {
public: LineStroke (void) { segments = 0; }
public: LineStroke (const LineStroke& ls) {
	segments = ls.segments;
	foreach(QPoint * point, ls.points) {
	    QPoint * p = new QPoint((*point).x(), (*point).y());
	    points.append(p);
	} /* foreach */
} /* LineStroke */

public: ~LineStroke (void) {
    foreach(QPoint * point , points) {
		delete point;
    }
    points.clear();
    segments=0;
} /* ~LineStroke */

public: int segments;/* 包含有的段数目 */
public: QVector <QPoint *> points; //包含的用来构成笔画的点
};/* class LineStroke */

#endif /* !defined(_LINESTROKE_H_) */


/*
 * end of file LineStroke.h
 */
