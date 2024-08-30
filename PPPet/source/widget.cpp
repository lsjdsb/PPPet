#include "widget.h"
#include<QTimer>
#include<QGraphicsDropShadowEffect>
#include<QMouseEvent>
Widget::Widget(QWidget *parent)
	: QWidget(parent),
	roleLabel(new QLabel(this)),
	curFrame(0)
{
	setWindowFlags(Qt::WindowType::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);


	QTimer *updateTimer = new QTimer(this);
	updateTimer->setInterval(1000); // 1秒

   // 连接定时器的 timeout 信号到槽函数 
	connect(updateTimer, &QTimer::timeout, this, &Widget::updateRoleAnimation);
	updateTimer->start();
	initBtn();
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(200, 200, 200, 240));
	effect->setBlurRadius(5);
	this->setGraphicsEffect(effect);

	this->installEventFilter(this);
	
	roleLabel->resize(1000, 1000);
}

Widget::~Widget()
{
}

void Widget::updateRoleAnimation()
{
	QString qqs("background-repeat:no-repeat;");
	roleLabel->setStyleSheet(qqs+QString("background-image:url(:/resources/Work%1.png);").arg(curFrame));
	curFrame = (curFrame + 1) % 3;
}

bool Widget::eventFilter(QObject * watched, QEvent * ev)
{
	QMouseEvent *mouseev = static_cast<QMouseEvent*>(ev);
	static QPoint begpos;
	if (ev->type() == QEvent::MouseButtonPress)
	{
		begpos = mouseev->globalPos() - this->pos();
	}
	else if(ev->type() == QEvent::MouseMove && mouseev->buttons() & Qt::MouseButton::LeftButton)
	{
		this->move(mouseev->globalPos() - begpos);
	}
	return false;
}

void Widget::initBtn()
{
	closeBtn = new QPushButton(this);
	cutBtn = new QPushButton(this);
	openBtn = new QPushButton(this);


	closeBtn->setGeometry(800, 200, 64, 64);
	cutBtn->setGeometry(800, 300, 64, 64);
	openBtn->setGeometry(800, 400, 64, 64);

	closeBtn->setObjectName("closeBtn");
	closeBtn->setStyleSheet("background-image:url(:/resources/close.png);");
	cutBtn->setStyleSheet("background-image:url(:/resources/cut.png);");
	openBtn->setStyleSheet("background-image:url(:/resources/open.png);");
	this->setStyleSheet("QPushButton{background-color:rgb(64, 173, 250);border:none;border-radius:5px;}\
QPushButton#closeBtn:hover{background-color:rgb(240,0,0);}");

	connect(closeBtn, &QPushButton::pressed, this, &Widget::close);
	


}
