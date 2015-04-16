/* ===========================================================================
 *
 *       Filename:  handwritor_debug.h
 *
 *    Description:  handwritor debug (qt)
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


#if !defined(_IDH_ID_VERIFY_H_)
#define _IDH_ID_VERIFY_H_ (1)

#if !defined(ID_QT_VERSION)
#	error "please define ID_QT_VERSION"
#endif

#if (ID_QT_VERSION < 0x050000)
# include <QtGui/QLabel>
# include <QtGui/QLineEdit>
# include <QtGui/QMainWindow>
# include <QtGui/QPushButton>
# include <QtGui/QVBoxLayout>
# include <QtGui/QWidget>
#else
# include <QtWidgets/QLabel>
# include <QtWidgets/QLineEdit>
# include <QtWidgets/QMainWindow>
# include <QtWidgets/QPushButton>
# include <QtWidgets/QVBoxLayout>
# include <QtWidgets/QWidget>
#endif


#include "handwritor.h"


#define CLASS_NAME_IV "handwritor_debug"
#define IDVERIFY_UI_WIDTH (1024)
#define IDVERIFY_UI_HEIGHT (768)
#define IDVERIFY_UI_BTN_W (164)
#define IDVERIFY_UI_BTN_H (64)


#define IVTITLE_GET_UTF8STR "手写输入中文\n"


class handwritor_debug : public QMainWindow {
	Q_OBJECT

public: explicit handwritor_debug(QWidget * parent = 0);
signals: int on_destroyed(QWidget * w, void * extra);
public: inline bool is_destroyed (void) { return destroyed; }
public: int destroy(void);
public: ~handwritor_debug(void) { destroy(); }
private: bool destroyed;

/*
 * release res and back to origin
 */
private: void to_exit(void);

/* ui */
private: int ui_setup(void);
private: void ui_retranslate(void);

/* signal */
private: void signal_connect(void);
private: void signal_disconnect(void);

/* handlers(slots) */
/*
 * XXX-NOTE: should connect finger verify to
 * "handle_login" -- TODO
 */
/* public slots: void handle_confirm(void); */
private slots: void handle_cancel(void);
private slots: void handle_clear(void);
private slots: void handle_clicked(int keyval);
protected: virtual void closeEvent(QCloseEvent * evt);

private: QWidget * central_widget;
private: QVBoxLayout * _idv_master_layout;
private: QHBoxLayout * idv_master_layout;
private: QVBoxLayout * idv_center_layout;
private: QHBoxLayout * id_layout;
private: QLabel * hwdbg_label;
private: QLabel * prompt;
private: QLineEdit * hwdbg;
private: QVBoxLayout * confirm_layout;
private: QPushButton * btn_cancel;
private: QPushButton * btn_clear;
private: handwritor * input;

private: QLabel * title;
};/* class handwritor_debug */


#endif /* if !defined(_IDH_ID_VERIFY_H_) */


/*
 * end of file handwritor_debug.h
 */
