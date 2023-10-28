#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "produs.h"


class MyTableModel :public QAbstractTableModel {
private:
	std::vector<Produs> produse;
public:
	MyTableModel(QObject* parent) :
		QAbstractTableModel(parent) {
	}

	int columns = 4;
	int rowCount(const QModelIndex& parent = QModelIndex())const  override {
		return produse.size();
}
	int columnCount(const QModelIndex& parent = QModelIndex())const  override {
		return columns;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto p= produse[index.row()];
		
			return QString::fromStdString(
				p.get_nume() + ": "
				+ p.get_producator()
				+ ": " + p.get_tip()
				+ ": " + std::to_string(p.get_price()));
		}
		return QVariant();

		


	}
	void setproduse(std:: vector<Produs> produse){
		this->produse = produse;
		auto topleft = createIndex(0, 0);
		auto bottomr = createIndex(rowCount(), columnCount());
		emit dataChanged(topleft, bottomr);
	}
};