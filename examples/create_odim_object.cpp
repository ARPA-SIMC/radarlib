/*===========================================================================*/
/*
/* Questo programma crea un odim object utilizzando le classi generiche Odimh5
/* Serve a far vedere come creare un oggetto, i gruppi datataset e i gruppi data
/* Siccome si sta scrivendo un oggetto generico, a parte gli attributi
/* obbligatori e quindi comuni a tutti gli oggetti, vengono utilizzate
/* le funzioni generiche di lettura e scrittura degli attributi
/*
/* La struttura dell'oggetto creato e' simile ad un volume polare
/* Alla fine utilizziamo un dumper per stampare a video il risultato
/*
/* Questo esempio e' simile a create_polar_volume.cpp
/*
/* Esempo di utilizzo:
/*	main.exe volume.h5
/*
/*===========================================================================*/


#include <iostream>

#include <radarlib/radar.hpp>
using namespace OdimH5v20;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <odimh5file>" << std::endl;
		return -1;
	}

	OdimFactory*		factory = NULL;
	OdimObject*		object	= NULL;
	OdimObjectDumper*	dumper	= NULL;

	try
	{
		/* creazione di una factory */
		factory		= new OdimFactory();

		/* creazione di un oggetto generico */
		object		= factory->create(argv[1]);

		/* what (valori obbligatori e comuni a tutti gli oggetti) */

		object->setObject("TIPO OGGETTO INVENTATO");
		object->setVersion(ModelVersion(100,100).toString());	/* numero inventato 100.100 */
		object->setDateTime(Radar::timeutils::getUTC());

		SourceInfo source;
		source.setComment("sorgente inventata");
		source.setCountry(100);
		source.setPlace("Italy");

		object->setSource(source);

		/* where */

		object->getWhere()->set(ATTRIBUTE_WHERE_LAT, 100.1);
		object->getWhere()->set(ATTRIBUTE_WHERE_LON, 100.2);
		object->getWhere()->set(ATTRIBUTE_WHERE_HEIGHT, 100.3);

		/* how */

		object->getHow()->set(ATTRIBUTE_HOW_TASK,	"task inventato");
		object->getHow()->set(ATTRIBUTE_HOW_STARTEPOCHS, (unsigned int)Radar::timeutils::getUTC());
		object->getHow()->set(ATTRIBUTE_HOW_ENDEPOCHS,	 (unsigned int)Radar::timeutils::getUTC()+ 3600);
		object->getHow()->set(ATTRIBUTE_HOW_SYSTEM,	 "sistema inventato");
		object->getHow()->set(ATTRIBUTE_HOW_SOFTWARE,	"software inventato");
		object->getHow()->set(ATTRIBUTE_HOW_SW_VERSION, "numero di versione inventato");
		object->getHow()->set(ATTRIBUTE_HOW_ZR_A,	.1);
		object->getHow()->set(ATTRIBUTE_HOW_ZR_B,	.2);
		object->getHow()->set(ATTRIBUTE_HOW_KR_A,	.3);
		object->getHow()->set(ATTRIBUTE_HOW_KR_B,	.4);
		object->getHow()->set(ATTRIBUTE_HOW_TASK,	true);

		object->getHow()->set("attributo intero inventato", (int)100);
		object->getHow()->set("attributo stringa inventato", "valore stringa inventato");

		for (int i=0; i<2; i++)
		{
			/* creazione di un dataset generico */
			OdimDataset* dataset =  object->createDataset();

			/* non tutti questi attributi hanno senso a livello di dataset, ma e' solo per fare un esempio */
			dataset->getWhat()->set(ATTRIBUTE_WHAT_PRODUCT,		"tipo di prodotto inventato");
			dataset->getWhat()->set(ATTRIBUTE_WHAT_PRODPAR,		"tipo di prodotto inventato");
			dataset->getWhat()->set(ATTRIBUTE_WHAT_QUANTITY,	"quantita' inventata");
			dataset->getWhat()->set(ATTRIBUTE_WHAT_STARTDATE,	"data inizio");
			dataset->getWhat()->set(ATTRIBUTE_WHAT_STARTTIME,	"ora inizio");
			dataset->getWhat()->set(ATTRIBUTE_WHAT_ENDDATE,		"data fine");
			dataset->getWhat()->set(ATTRIBUTE_WHAT_ENDTIME,		"ora fine");
			dataset->getWhat()->set(ATTRIBUTE_WHAT_NODATA,		1.);
			dataset->getWhat()->set(ATTRIBUTE_WHAT_UNDETECT,	2.);
			dataset->getWhat()->set(ATTRIBUTE_WHAT_OFFSET,		3.);
			dataset->getWhat()->set(ATTRIBUTE_WHAT_GAIN,		4.);

			dataset->getWhat()->set("attributo intero inventato", (int)100);
			dataset->getWhat()->set("attributo stringa inventato", "valore stringa inventato");

			for (int j=0; j<2; j++)
			{
				/* creazionne di un gruppo data generico */
				OdimData* data = dataset->createData();

				data->getWhat()->set(ATTRIBUTE_WHAT_QUANTITY,	PRODUCT_QUANTITY_WRAD);
				data->getWhat()->set(ATTRIBUTE_WHAT_NODATA,	1.);
				data->getWhat()->set(ATTRIBUTE_WHAT_UNDETECT,	2.);
				data->getWhat()->set(ATTRIBUTE_WHAT_OFFSET,	3.);
				data->getWhat()->set(ATTRIBUTE_WHAT_GAIN,	4.);

				data->getWhat()->set("attributo intero inventato", (int)100);
				data->getWhat()->set("attributo stringa inventato", "valore stringa inventato");

				/* creazione di una matrice di byte con dei valori stampabili */
				/* per comodita' usiamo dalle lettere maiuscole in su */
				RayMatrix<unsigned char> matrix(400,500);

				for (int i=0; i<400; i++)
					for (int j=0; j<500; j++)
						matrix.elem(i,j) = 65 + ((i * j) % 120);

				data->writeData(matrix);

				delete data;
			}

			delete dataset;
		}

		/* stampiamo a video il risultato */
		/* dumper = factory->getDumper(); */
		/* dumper->dump(object); */

		std::cout << "Esecuzione terminata" << std::endl;
	}
	catch (std::exception& stde)
	{
		std::cerr << "Errore di esecuzione: " << stde.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Errore sconociuto" << std::endl;
	}

	delete dumper;
	delete object;
	delete factory;

	return 0;
}












































