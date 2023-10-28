#pragma once
#include "produs.h"
#include "repo.h"
#include "repo_virtual.h"
class ActiuneUndo {
public :
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo()=default;
};

class UndoAdauga :public ActiuneUndo {
private:
	Produs produs_adaugat;
	Repo_virtual& rep;
public:
	UndoAdauga(Repo_virtual& rep, const Produs& produs_adaugat) :rep{ rep }, produs_adaugat{ produs_adaugat }{}
	void doUndo() override {
		rep.sterge(produs_adaugat.get_nume());}
};

class UndoSterge :public ActiuneUndo {
private :
	Produs produs_sters;
	Repo_virtual& rep;
public:
     UndoSterge(Repo_virtual& rep,const Produs& produs_sters):rep{rep},produs_sters{produs_sters}{}
	 void doUndo() override {
		 rep.store(produs_sters);
}
};


class UndoModifica :public ActiuneUndo {
private:
	Produs produs_modificat;
	Repo_virtual& rep;
public:
	UndoModifica(Repo_virtual& rep, Produs& produs_modificat) :rep{ rep }, produs_modificat{ produs_modificat } {  }

	void doUndo() override
	{
		
		rep.modifica(produs_modificat.get_nume(), produs_modificat);
}

};