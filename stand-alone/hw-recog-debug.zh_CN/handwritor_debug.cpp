/* ===========================================================================
 *
 *       Filename:  handwritor_debug.cpp
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


#include "handwritor_debug.h"

#include <QtCore/QLocale>
#include <QtCore/QDebug>
#if (ID_QT_VERSION < 0x050000)
#	include <QtGui/QApplication>
#else
#	include <QtWidgets/QApplication>
#endif


/*
 * ===========================================================================
 * constructor and ~
 * ===========================================================================
 */
handwritor_debug::handwritor_debug (QWidget * parent) : QMainWindow(parent) {
	this->destroyed = false;
	fprintf(stderr, "%s +%d: %s\n", __FILE__, __LINE__, __func__);
	fflush(stderr);
	this->ui_setup();
	this->signal_connect();
} /* handwritor_debug::handwritor_debug */


int handwritor_debug::destroy (void) {
	if (destroyed) {
		return -1;
	}

	this->signal_disconnect();

	/*
	 * XXX-NOTE: in normal case: ui elemnets:
	 * 母控件析构时 会自动释放其子控件的内存
	 * => all in layout => delete all layout and central_widget is ok
	 */
	delete id_layout;
	delete idv_center_layout;
	delete confirm_layout;
	delete idv_master_layout;
	delete _idv_master_layout;
	delete central_widget;

	this->destroyed = true;

	return 0;
} /* handwritor_debug::destroy */


/*
 * release res and backup to origin
 */
void handwritor_debug::to_exit (void) {
	this->destroy();
} /* handwritor_debug::to_exit */
/*
 * ===========================================================================
 * end of constructor and ~
 * ===========================================================================
 */


/*
 * ===========================================================================
 * ui
 * ===========================================================================
 */
#define __STLST_EU \
	"background-color: #ffffff; color: #000000; border-radius: 8px"
#define __STLST_EP __STLST_EU
#define __STLST_TL \
	"color: #ff0000"
#define __STLST_UNL \
	"background-color: #ffffff; color: #000000; border-radius: 8px"
#define __STLST_UN \
	"background-color: #ffffff; color: #000000; font-weight: bold; " \
	"border-radius: 8px"
#define __STLST_PPT \
	"color: #ff0000; font-weight: bold; border-radius: 8px"
#define __STLST_PWL __STLST_UNL
#define __STLST_CLR \
	"background-color: #b22222; color: #000000; border-radius: 8px"
#define __STLST_CCL \
	"background-color: #ff0000; color: #000000; border-radius: 8px"
#define __STLST_LI \
	"background-color: #00ff00; color: #000000; border-radius: 8px"


int handwritor_debug::ui_setup (void) {
	QPalette palette;
	QFont font;
	QSpacerItem * spacer;

	/* obj name */
	if (this->objectName().isEmpty()) {
		this->setObjectName(QString::fromUtf8(CLASS_NAME_IV));
	}

	/*
	 * size
	 */
	/* this->setGeometry(0, 0, IDVERIFY_UI_WIDTH, IDVERIFY_UI_HEIGHT); */
	this->resize(IDVERIFY_UI_WIDTH, IDVERIFY_UI_HEIGHT);
	/* bg */
	this->setAutoFillBackground(true);
	/* rgba */
	palette.setColor(QPalette::Background, QColor(0x00, 0x00, 0xff, 0x80));
	this->setPalette(palette);
	/*
	 * locale
	 */
	this->setLocale(QLocale(QLocale::Chinese, QLocale::China));

	/* new central widget and to this */
	central_widget = new QWidget(this);
	central_widget->setObjectName(QString::fromUtf8("central_widget"));
	central_widget->setEnabled(true);
	central_widget->setLocale(QLocale(QLocale::Chinese, QLocale::China));


	/* master layout and master widget */
	_idv_master_layout = new QVBoxLayout(central_widget);
	_idv_master_layout->setObjectName(
		QString::fromUtf8("_idv_master_layout"));
	_idv_master_layout->setContentsMargins(0, 20, 0, 0);/* l, t, r, b */
	title = new QLabel(central_widget);
	title->setAlignment(Qt::AlignHCenter);
	font.setPixelSize(48);
	title->setFont(font);
	title->setStyleSheet(__STLST_TL);
	_idv_master_layout->addWidget(title);
	_idv_master_layout->setAlignment(title,
		Qt::AlignHCenter | Qt::AlignVCenter);
	idv_master_layout = new QHBoxLayout();
	idv_master_layout->setObjectName(QString::fromUtf8("idv_master_layout"));
	idv_master_layout->setContentsMargins(0, 0, 0, 0);/* l, t, r, b */
	_idv_master_layout->addLayout(idv_master_layout);

	/* left layout and left widget -- a spacer */
	spacer = new QSpacerItem(36, 24);
	idv_master_layout->addItem(spacer);

	/* center layout */
	idv_center_layout = new QVBoxLayout();
	idv_center_layout->setObjectName(QString::fromUtf8("idv_center_layout"));
	idv_center_layout->setContentsMargins(0, 0, 0, 20);

	spacer = new QSpacerItem(36, 24);
	idv_center_layout->addItem(spacer);/* XXX-1st */

	/* hwdbg layout and widget */
	id_layout = new QHBoxLayout();
	id_layout->setObjectName(QString::fromUtf8("id_layout"));
	/* un_layout->setContentsMargins(5, 0, 5, 0); */
	/* label for username */
	hwdbg_label = new QLabel(central_widget);
	hwdbg_label->setObjectName(QString::fromUtf8("hwdbg_label"));
	/* hwdbg_label->setMaximumWidth(256); */
	hwdbg_label->setMinimumHeight(36);
	hwdbg_label->setAlignment(Qt::AlignCenter);
	/* font */
	font.setPixelSize(24);
	hwdbg_label->setFont(font);
	hwdbg_label->setStyleSheet(__STLST_UNL);
	id_layout->addWidget(hwdbg_label);
	/* hwdbg */
	hwdbg = new QLineEdit(central_widget);
	hwdbg->setObjectName(QString::fromUtf8("hwdbg"));
	/* hwdbg->setMaximumWidth(320); */
	hwdbg->setMinimumHeight(36);
	hwdbg->setAlignment(Qt::AlignCenter);
	hwdbg->setFont(font);
	hwdbg->setStyleSheet(__STLST_UN);
	id_layout->addWidget(hwdbg);
	id_layout->setStretch(0, 1);
	id_layout->setStretch(1, 2);
	idv_center_layout->addLayout(id_layout, 1);/* XXX-2nd */
	idv_center_layout->setAlignment(id_layout, Qt::AlignHCenter);

	prompt = new QLabel(central_widget);
	prompt->setObjectName(QString::fromUtf8("prompt"));
	prompt->setStyleSheet(__STLST_PPT);
	prompt->setMinimumHeight(36);
	/* prompt->setMaximumHeight(48); */
	prompt->setAlignment(Qt::AlignCenter);
	prompt->setFont(font);
	idv_center_layout->addWidget(prompt);/* XXX-3rd */

	fprintf(stderr, "%s +%d: %s\n", __FILE__, __LINE__, __func__);
	fflush(stderr);
	// input = new handwritor(NULL, NULL, this->hwdbg, this->central_widget,
	input = new handwritor(NULL, NULL, this->hwdbg, NULL,
		NULL, NULL);
	fprintf(stderr, "%s +%d: %s\n", __FILE__, __LINE__, __func__);
	fflush(stderr);
	input->setObjectName(QString::fromUtf8("input"));
	idv_center_layout->addWidget(input);/* XXX-4th */
	idv_center_layout->setAlignment(input, Qt::AlignHCenter);

	spacer = new QSpacerItem(36, 24);
	idv_center_layout->addItem(spacer);/* XXX-5th */

	idv_center_layout->setStretch(0, 2);
	idv_center_layout->setStretch(1, 1);
	idv_center_layout->setStretch(2, 1);
	idv_center_layout->setStretch(3, 3);
	idv_center_layout->setStretch(4, 1);


	/* confirm layout and widget */
	confirm_layout = new QVBoxLayout();
	confirm_layout->setObjectName(QString::fromUtf8("confirm_layout"));
	confirm_layout->setContentsMargins(0, 0, 5, 0);
	spacer = new QSpacerItem(36, 24);
	confirm_layout->addItem(spacer);

	/* btn_clear */
	btn_clear = new QPushButton(central_widget);
	btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
	btn_clear->setFixedSize(IDVERIFY_UI_BTN_W, IDVERIFY_UI_BTN_H);
	btn_clear->setFont(font);
	btn_clear->setStyleSheet(__STLST_CLR);
	confirm_layout->addWidget(btn_clear);
	spacer = new QSpacerItem(36, 24);
	confirm_layout->addItem(spacer);

	/* btn_cancel */
	btn_cancel = new QPushButton(central_widget);
	btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));
	btn_cancel->setFixedSize(IDVERIFY_UI_BTN_W, IDVERIFY_UI_BTN_H);
	btn_cancel->setStyleSheet(__STLST_CCL);
	btn_cancel->setFont(font);
	confirm_layout->addWidget(btn_cancel);
	spacer = new QSpacerItem(36, 24);
	confirm_layout->addItem(spacer);

	confirm_layout->setStretch(0, 4);
	confirm_layout->setStretch(1, 1);
	confirm_layout->setStretch(2, 1);
	confirm_layout->setStretch(3, 1);
	confirm_layout->setStretch(4, 1);

	/* add all to master */
	/* idv_master_layout->addLayout(idv_left_layout, 0); */
	idv_master_layout->addLayout(idv_center_layout, 1);
	idv_master_layout->addLayout(confirm_layout, 2);
	idv_master_layout->setAlignment(idv_center_layout, Qt::AlignHCenter);
	idv_master_layout->setAlignment(confirm_layout, Qt::AlignHCenter);

	/*
	 * setup master layout
	 * w: 6
	 * h: 9
	 */
	idv_master_layout->setStretch(0, 1);
	idv_master_layout->setStretch(1, 4);
	idv_master_layout->setStretch(2, 1);
	_idv_master_layout->setStretch(0, 1);
	_idv_master_layout->setStretch(1, 8);

	this->setCentralWidget(central_widget);

	/* window title */
	ui_retranslate();

#	if defined(MINGW32)
	/* always on top */
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
#	else
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	/* | Qt::X11BypassWindowManagerHint */
#	endif

#	if !defined(START_FULL_SCREEN)
	setWindowState(Qt::WindowMaximized);
#	endif

	/* final of ui setup */
	QMetaObject::connectSlotsByName(this);

	return 0;
} /* handwritor_debug:ui_setup */


void handwritor_debug::ui_retranslate (void) {
	this->setWindowTitle(QString::fromUtf8("中文手写测试"));
	this->hwdbg_label->setText(QString::fromUtf8("手写中文"));
	this->btn_clear->setText(QString::fromUtf8("清除"));
	this->btn_cancel->setText(QString::fromUtf8("取消"));
	this->title->setText(QString::fromUtf8(IVTITLE_GET_UTF8STR));
} /* handwritor_debug_ui::ui_retranslate */
/*
 * ===========================================================================
 * end of ui
 * ===========================================================================
 */


/*
 * ===========================================================================
 * evt
 * ===========================================================================
 */
void handwritor_debug::signal_connect (void) {
	QObject::connect(this->btn_clear, SIGNAL(clicked()), this,
		SLOT(handle_clear()));
	QObject::connect(this->btn_cancel, SIGNAL(clicked()), this,
		SLOT(handle_cancel()));
	QObject::connect(this->input, SIGNAL(key_generated(int)), this,
		SLOT(handle_clicked(int)));
} /* handwritor_debug::signal_connect */


void handwritor_debug::signal_disconnect (void) {
	QObject::disconnect(this->btn_clear, SIGNAL(clicked()), this,
		SLOT(handle_clear()));
	QObject::disconnect(this->btn_cancel, SIGNAL(clicked()), this,
		SLOT(handle_cancel()));
	QObject::disconnect(this->input, SIGNAL(key_generated(int)), this,
		SLOT(handle_clicked(int)));
} /* handwritor_debug::signal_disconnect */
/*
 * ===========================================================================
 * end of evt
 * ===========================================================================
 */


/*
 * ===========================================================================
 * handlers
 * ===========================================================================
 */
void handwritor_debug::handle_cancel (void) {
	this->to_exit();
} /* idh_launch::handle_cancel */


void handwritor_debug::handle_clear (void) {
	/*
	 * TODO: lock hwdbg first
	 */
	this->hwdbg->setText(QString(""));
	this->prompt->setText(QString::fromUtf8(""));
} /* idh_launch::handle_clear */


void handwritor_debug::closeEvent (QCloseEvent * evt) {
	this->to_exit();
} /* handwritor_debug::closeEvent */


void handwritor_debug::handle_clicked (int keyval) {
} /* handwritor_debug::handle_clicked */
/*
 * ===========================================================================
 * end of handlers
 * ===========================================================================
 */
/*
 * handwritor_debug.cpp
 */
