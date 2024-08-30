#pragma once
#include <QPixmap.h>
#include <QLabel.h>
#include <QWidget>
#include<QPushButton>
class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = nullptr);
	~Widget();
	void updateRoleAnimation();
	bool eventFilter(QObject *watched, QEvent *ev)override;
	void initBtn();
private:
	QLabel * roleLabel;
	qint8 curFrame;

	QPushButton *closeBtn;
	QPushButton *cutBtn;
	QPushButton *openBtn;

};