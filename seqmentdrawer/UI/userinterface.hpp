#pragma once

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include "../../GeneratedFiles/ui_userinterface.h"
#include "request.h"

class UserInterface : public QWidget
{
	Q_OBJECT

public:
	UserInterface(QWidget *parent = 0);
	~UserInterface();

	Request GetRequest();


protected:
	void Init();
	void ResetRequest();

	void SetLabelProperties();
	void SetInputLineProperties();
	void CreateHead();
	void CreatePlaneDetails();

private slots:
	void newsegment();
	void newwidth();
	
private:
	QWidget *window;
	QVBoxLayout* _mainLayout;

	QLabel * _label;
	QGroupBox *_strategy, *norms, *coords;

	QLabel * _x, *_y;
	QLabel * _x2, *_y2;
	QLineEdit * _xf, *_yf;
	QLineEdit * _xn, *_yn;

	QLabel * _widthText;
	QLineEdit * _width;
	QLabel * _unitText;
	QLineEdit * _unit;

	QVBoxLayout* head;
	QVBoxLayout* strategiesGroup;
	QHBoxLayout* plane_details;

	Request request;
};
