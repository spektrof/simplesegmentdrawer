#include "userinterface.hpp"

UserInterface::UserInterface(QWidget *parent)
	: QWidget(parent)
{
	window = new QWidget();
	_mainLayout = new QVBoxLayout();
	_label = new QLabel("Welcome to Segment Drawer Program", this);

	_strategy = new QGroupBox(tr("Segment details"),this);
	norms = new QGroupBox(tr("Width and Unit"));
	coords = new QGroupBox(tr("Points"));

	_x = new QLabel("X1", this);	_x2 = new QLabel("X2", this);
	_y = new QLabel("Y1", this); _y2 = new QLabel("Y2", this);

	_xf = new QLineEdit("-10.0", this);
	_yf = new QLineEdit("-5.0", this);

	_xn = new QLineEdit("3.0", this);
	_yn = new QLineEdit("-2.0", this);

	_widthText = new QLabel("Width:", this);
	_width = new QLineEdit("4.0", this);

	_unitText = new QLabel("Unit:", this);
	_unit = new QLineEdit("1", this);

	head = new QVBoxLayout;
    plane_details = new QHBoxLayout;

	Init();
}

UserInterface::~UserInterface()
{
	delete _label;

	delete _x;
	delete _y;

	delete _x2;
	delete _y2;

	delete _xf;
	delete _yf;

	delete _xn;
	delete _yn;

	delete _width;
	delete _widthText;

	delete norms;
	delete coords;
	delete _strategy;

	delete window;
	delete _mainLayout;
}

void UserInterface::Init() 
{
	window->setStyleSheet("background-color: #7ac5cd;");
	window->setFixedSize(400, 200);
	window->move(900, 200);
	//---------------------------------------
	SetLabelProperties();
	SetInputLineProperties();
	//---------------------------------------
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//------------------------------------------

	CreateHead();
	CreatePlaneDetails();

	//-----------------------------------------	
	mainLayout->addLayout(head);
	mainLayout->addWidget(_strategy);

	//_----------------------------------------- connects

	connect(_xf, SIGNAL(textChanged(const QString)), this, SLOT(newsegment()));	//küld eventet, a textedited nem küld
	connect(_yf, SIGNAL(textChanged(const QString)), this, SLOT(newsegment()));
	connect(_xn, SIGNAL(textChanged(const QString)), this, SLOT(newsegment()));
	connect(_yn, SIGNAL(textChanged(const QString)), this, SLOT(newsegment()));

	connect(_width, SIGNAL(textChanged(const QString)), this, SLOT(newwidth()));
	connect(_unit, SIGNAL(textChanged(const QString)), this, SLOT(newwidth()));

	//-------------------------------------------

	window->setLayout(mainLayout);
	window->show();
}

void UserInterface::newsegment()
{
	request._event = NEWSEGMENT;

	request.first = glm::vec2(_xf->text().toFloat(), _yf->text().toFloat());
	request.second = glm::vec2(_xn->text().toFloat(),_yn->text().toFloat());
}

void UserInterface::newwidth()
{
	request._event = NEWWIDTHORUNIT;

	request.width = _width->text().toFloat();
	request.units = _unit->text().toInt();
}

Request UserInterface::GetRequest() 
{
	if (request._event == NONE) return request;
	
	Request result(request); 

	ResetRequest();

	return result;
}

void UserInterface::ResetRequest() 
{
	request._event = NONE;
}

void UserInterface::SetLabelProperties()
{
	_label->setFont(QFont("Courier New", 12, QFont::Bold));
	_label->setMaximumHeight(25);

}

void UserInterface::SetInputLineProperties()
{
	_xf->setFixedWidth(25);
	_x->setFixedWidth(15);
	_yf->setFixedWidth(25);
	_y->setFixedWidth(15);
	_xn->setFixedWidth(25);
	_yn->setFixedWidth(25);
	_width->setFixedWidth(25);
	_unit->setFixedWidth(25);


	_xf->setStyleSheet("background-color: #bcee68;");
	_yf->setStyleSheet("background-color: #bcee68;");
	_xn->setStyleSheet("background-color: #bcee68;");
	_yn->setStyleSheet("background-color: #bcee68;");
	_width->setStyleSheet("background-color: #bcee68;");
	_unit->setStyleSheet("background-color: #bcee68;");

	_xn->setAlignment(Qt::AlignCenter);
	_yn->setAlignment(Qt::AlignCenter);
	_xf->setAlignment(Qt::AlignCenter);
	_yf->setAlignment(Qt::AlignCenter);
	_width->setAlignment(Qt::AlignCenter);
	_unit->setAlignment(Qt::AlignCenter);

	_width->setInputMask("00.0");
	_unit->setInputMask("000");

	request.first = glm::vec2(_xf->text().toFloat(), _yf->text().toFloat());
	request.second = glm::vec2(_xn->text().toFloat(), _yn->text().toFloat());
	request.width = _width->text().toFloat();
	request.units = _unit->text().toInt();
}

void UserInterface::CreateHead()
{
	head->addWidget(_label, 0, Qt::AlignHCenter);
	
	head->setSpacing(0);
	head->setMargin(0);
}

void UserInterface::CreatePlaneDetails()
{
	QHBoxLayout *left = new QHBoxLayout();
	QHBoxLayout *right = new QHBoxLayout();

	QVBoxLayout *coordnames = new QVBoxLayout();
	QVBoxLayout *coordnames2 = new QVBoxLayout();
	QVBoxLayout *coorddata = new QVBoxLayout();
	QVBoxLayout *coorddata2 = new QVBoxLayout();
	QHBoxLayout *w = new QHBoxLayout();
	QHBoxLayout *u = new QHBoxLayout();

	coordnames->addWidget(_x, 0, Qt::AlignCenter);
	coordnames->addWidget(_y, 0, Qt::AlignCenter);

	coordnames2->addWidget(_x2, 0, Qt::AlignCenter);
	coordnames2->addWidget(_y2, 0, Qt::AlignCenter);
	
	coorddata->addWidget(_xf, 0, Qt::AlignCenter);
	coorddata->addWidget(_yf, 0, Qt::AlignCenter);

	coorddata2->addWidget(_xn, 0, Qt::AlignCenter);
	coorddata2->addWidget(_yn, 0, Qt::AlignCenter);

	left->addLayout(coordnames);
	left->addLayout(coorddata);
	left->addLayout(coordnames2);
	left->addLayout(coorddata2);

	coords->setLayout(left);
	coords->setFixedSize(125, 100);

	w->addWidget(_widthText, 0, Qt::AlignCenter);
	w->addWidget(_width, 0, Qt::AlignCenter);
	u->addWidget(_unitText, 0, Qt::AlignCenter);
	u->addWidget(_unit, 0, Qt::AlignCenter);

	right->addLayout(w);
	right->addLayout(u);

	norms->setLayout(right);
	norms->setFixedSize(125, 100);

	plane_details->addWidget(coords);
	plane_details->addWidget(norms);

	_strategy->setLayout(plane_details);

}