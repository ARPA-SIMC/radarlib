#include <radarlib/radar.hpp>
// Classe generica per passare da un generico OdimObject alla sua
// rappresentazione concreta.
//
// L'operatore () permette di invocare l'opportuno metodo visit(), mediante un
// dynamic_cast fatto sulla base del metodo OdimObject->getObject(). Se per caso
// non c'è coerenza tra tipo dichiarato dal suddetto metodo e la classe
// concreta (e.g. un PolarVolume che dice di essere un OBJECT_IMAGE), viene
// lanciata un'eccezione di tipo std::bad_cast.
//
//
class OdimVisitor {
 public:
	// Metodo per leggere un generico oggetto OdimObject.
	// Controlla di che tipo concreto è l'OdimObject passato e invoca l'opportuno
	// metodo visit(). Se non trova un tipo supportato, invoca visit(OdimObject&).
	void operator()(OdimH5v20::OdimObject* obj);
 protected:
	virtual void visit(OdimH5v20::OdimObject& obj);
	virtual void visit(OdimH5v20::PolarVolume& obj);
};

void OdimVisitor::operator()(OdimH5v20::OdimObject* obj) {
	// Leggo di che tipo è il mio oggetto
	const std::string& type = obj->getObject();

	// Aggiungo il supporto per i volumi polari.
	if (type == OdimH5v20::OBJECT_PVOL) {
		OdimH5v20::PolarVolume& o = dynamic_cast<OdimH5v20::PolarVolume&>(*obj);
		visit(o);
	}
	// Per aggiungere un nuovo tipo, basta che aggiungi un blocco "if" analogo
	// al precedente e un metodo visit() opportuno, e.g:
	// else if (type == OdimH5v20::OBJECT_IMAGE) {
	//	...
	// }

	// NOTA: sarebbe bello avere degli enum per i tipi di oggetto, in modo da
	// poter usare uno switch statement. Si potrebbe aggiungere alla radarlib una
	// classe che effettua la conversione da tipo sotto forma di stringa a tipo
	// enumerativo (e viceversa).

	// Se arrivo qui, vuol dire che non ho trovato nessun tipo supportato
	else {
		visit(*obj);
	}
}

// Di default, i metodi visit non fanno nulla.
void OdimVisitor::visit(OdimH5v20::OdimObject& obj) {}
void OdimVisitor::visit(OdimH5v20::PolarVolume& obj) {}

#include <iostream>
// Semplice implementazione
class ConcreteOdimVisitor : public OdimVisitor {
 private:
	std::ostream& out;
 public:
	ConcreteOdimVisitor(std::ostream& out) : out(out) {}
 protected:
	virtual void visit(OdimH5v20::OdimObject& obj) {
		throw std::logic_error("Tipo non supportato: " + obj.getObject());
	}
	virtual void visit(OdimH5v20::PolarVolume& obj) {
		out << "Trovato un volume polare" << std::endl;
	}
};

int main(int argc, const char** argv)
{
	ConcreteOdimVisitor visitor(std::cout);
	OdimH5v20::OdimFactory factory;
	OdimH5v20::OdimObject* object = factory.open(argv[1]);
	try {
		visitor(object);
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
