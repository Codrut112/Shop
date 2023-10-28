#include <QGroupBox>
#include <Qwidget>
#include <QtWidgets/qformlayout>
#include <QtWidgets/qlistwidget.h>
#include "service.h"
#include <qtimer.h>
#include <QTableWidget>
#include <qpushbutton.h>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include "observer.h"
#include "model.h"
#include "QTableView"
class CosGUI :public QWidget,public Observer {
private:
	Magazin&  mag;
	QHBoxLayout* mainLayout = new QHBoxLayout;
	QTableView* table = new QTableView;
	QListWidget* prodWidget = new QListWidget;
	QPushButton* adauga = new QPushButton("adauga random");
	QLineEdit* line = new QLineEdit;
	QPushButton* adauga_normal = new QPushButton("adauga");
	QLineEdit* line_nume = new QLineEdit;
	QLineEdit* fisier = new QLineEdit;
	QPushButton* save = new QPushButton("salveaza cos");
	QPushButton* goleste = new QPushButton("goleste cos");
	void Init();
	void Connect();
	void loadlist(const vector<Produs>& p);
	void update()override;

public:
	//constrictor
	CosGUI(Magazin& mag) :mag{ mag } {
		Init();
		Connect();
		loadlist(mag.get_all_cos());
	};
	~CosGUI() {
		this->mag.unregister_observer(this);
	}
};