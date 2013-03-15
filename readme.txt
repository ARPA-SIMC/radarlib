
------------------------------------------------------------------------------
DESCRIZIONE
------------------------------------------------------------------------------

Sorgenti e script per la compilazione e l'installazione della libreria
relativa al formato OdimH5 con le estensioni per Arpa Emilia-Romagna.

------------------------------------------------------------------------------
DESCRIPTION
------------------------------------------------------------------------------

This package contain script and sources to compile and install the library.
It is to manage radar volume in ODIMH5 format (see OPERA_2008_03_WP2.1a_InformationModel_UML_2.0.pdf) and 
the extenstion to the ODIMH5 fomart to manage ARPA Emilia Romagna requirements.

------------------------------------------------------------------------------
DOCUMENTAZIONE
------------------------------------------------------------------------------

La directory "html" contiene la documentazione in formato Doxygen dei
della libreria e delle sue classi. Per visualizzarla basta aprire il file
"index.html" con un qualunque browser.

------------------------------------------------------------------------------
DOCUMENTATION
------------------------------------------------------------------------------

The lib is documented in DoxyGen. The documentation will be build during the make execution. 
The documentation will be installed where you define in the Make. To visualize it pleaze open the index.html file in a browser.

-------------------------------------------------------------------------------
COMPILAZIONE E INSTALLAZIONE
------------------------------------------------------------------------------

La libreria va compilata e installata in una directory dove il link e i 
compilatori possano trovarla. In genere la directory
per le installazioni fatte dagli utenti dovrebbe essere /usr/local.

0) se i file sono stati copiati da un sistema windows potrebbero esserci
   dei problemi con diritti e link simbolici ai file.
   Eseguire: autoreconf -vif

1) eseguire: ./configure
   Se dovessero mancare le librerie necessarie viene generato un errore.
   Per l'installazione delle dipendenze vedere le sezioni associate in basso.

2) eseguire: ./configure --prefix=/usr/local/

3) eseguire: make

4) eseguire come root: make install

4) eseguire come root: ldconfig 
   In questo modo si forza il sistema ad aggiornare le informazioni per il linker

Per poter compilare e linkare i programmi che usano la libreria
assicurarsi che la directory /usr/local sia inclusa tra le directory
dove il linker cerca le librerie shared.
Nel caso /usr/local non sia gia' tra le directory del linker
basta utilizzare le variabili d'ambiente:
	export LD_LIBRARY_PATH=/usr/local/:$LD_LIBRARY_PATH

-----------------------------------------------------------------------------
COMPILING AND INSTALLATION PROCEDURE 
------------------------------------------------------------------------------

   Briefly, the shell commands `./configure; make; make install' should
configure, build, and install this package.  The following
more-detailed instructions are generic.  Some packages provide this info in the 
`INSTALL' file but do not implement all of the features documented
below.  The lack of an optional feature in a given package is not
necessarily a bug.  More recommendations for GNU packages can be found
in *note Makefile Conventions: (standards)Makefile Conventions.

   The `configure' shell script attempts to guess correct values for
various system-dependent variables used during compilation.  It uses
those values to create a `Makefile' in each directory of the package.
It may also create one or more `.h' files containing system-dependent
definitions.  Finally, it creates a shell script `config.status' that
you can run in the future to recreate the current configuration, and a
file `config.log' containing compiler output (useful mainly for
debugging `configure').

   It can also use an optional file (typically called `config.cache'
and enabled with `--cache-file=config.cache' or simply `-C') that saves
the results of its tests to speed up reconfiguring.  Caching is
disabled by default to prevent problems with accidental use of stale
cache files.

   If you need to do unusual things to compile the package, please try
to figure out how `configure' could check whether to do them, and mail
diffs or instructions to the address given in the `README' so they can
be considered for the next release.  If you are using the cache, and at
some point `config.cache' contains results you don't want to keep, you
may remove or edit it.

   The file `configure.ac' (or `configure.in') is used to create
`configure' by a program called `autoconf'.  You need `configure.ac' if
you want to change it or regenerate `configure' using a newer version
of `autoconf'.

   The simplest way to compile this package is:

0) if you need to generate or regenerate the configure
   Type: autoreconf -vif

1) type: ./configure

     Running `configure' might take a while.  While running, it prints
     some messages telling which features it is checking for.

   If some libs are missing you will get an error messagge.
  If you want to specify an installation path  
  type : ./configure --prefix=/usr/local/

3) type: make to compile the package.

4) Type `make install' to install the programs and any data files and
   documentation.  When installing into a prefix owned by root, it is
   recommended that the package be configured and built as a regular
   user, and only the `make install' phase executed with root
   privileges.

Make sure that the lib will be installed where you can reach it.
To compile and link programs which use the lib you could add the path  of the lib
to the LD_LIBRARY_PATH variable

	export LD_LIBRARY_PATH=/usr/local/:$LD_LIBRARY_PATH

5) Often, you can also type `make uninstall' to remove the installed
   files again.  In practice, not all packages have tested that
   uninstallation works correctly, even though it is required by the
   GNU Coding Standards.
   
  By default, `make install' installs the package's commands under
`/usr/local/bin', include files under `/usr/local/include', etc.  You
can specify an installation prefix other than `/usr/local' by giving
`configure' the option `--prefix=PREFIX', where PREFIX must be an
absolute file name.

Sharing Defaults
================

   If you want to set default values for `configure' scripts to share,
you can create a site shell script called `config.site' that gives
default values for variables like `CC', `cache_file', and `prefix'.
`configure' looks for `PREFIX/share/config.site' if it exists, then
`PREFIX/etc/config.site' if it exists.  Or, you can set the
`CONFIG_SITE' environment variable to the location of the site script.
A warning: not all `configure' scripts look for a site script.

----------------------------
DIPENDENZE
-----------------------------
 - hdf5 lib (utilizzata dalle classi relative a odimh5)
 - sz lib (libreria di compressione utilizzata da hdf5 lib)
 - z lib dev (utilizzata dalla classe wrapper nella libreria)

-----------------------------
LIBRERIA HDF5
-----------------------------

Installazione:

1) scaricare i sorgenti da: http://www.hdfgroup.org/ftp/HDF5/current/src/

2) eseguire: ./configure --prefix=/usr/local/ --enable-cxx --with-szlib
   --prefix serve ad installare la libreria nelle directory di sitema
   --enable-cxx abilita la compilazione delle classi C++ di HDF5
   --with-szlib si assicura di includere il supporto per i filtri basati su szlib

3) eseguire: make

4) eseguire come root: make install

5) eseguire come root: ldconfig 
   In questo modo si forza il sistema ad aggiornare le informazioni per il linker

Disinstallazione:

1) eseguire come root: make uninstall

-----------------------------
INSTALLAZIONE LIBRERIA SZ
-----------------------------

1) scaricare i sorgenti da: http://www.hdfgroup.org/ftp/lib-external/szip/2.1/src/

2) eseguire: ./configure --prefix=/usr/local/ 

3) eseguire: make 

4) eseguire come root: make install

5) eseguire come root: ldconfig 
   In questo modo si forza il sistema ad aggiornare le informazioni per il linker

---------------------------
INSTALLAZIONE LIBRERIA Z (development)
---------------------------

La libreria in teoria e' gia' presente nel sistema.
Quello che mancano sono gli header files necessari per la compilazione.

1) eseguire come root: apt-get install zlib1g-dev


-----------------------------
DEPENDENCY
-----------------------------
to compile and use the lib you need:
 - hdf5 lib 
 - sz lib 
 - z lib dev 

-----------------------------
LIB HDF5
-----------------------------
Installation :

1) donwload source code from da: http://www.hdfgroup.org/ftp/HDF5/current/src/
2) type: ./configure --prefix=/usr/local/ --enable-cxx --with-szlib
3) type make
4) (as root) type  make install

-----------------------------
LIB SZ
-----------------------------
1) download at : http://www.hdfgroup.org/ftp/lib-external/szip/2.1/src/
2) type : ./configure --prefix=/usr/local/ 
3) type : make 
4) as root type : make install

---------------------------
LIB Z (development)
---------------------------
Normally this lib is installed, yopu just nnet the headers to compile.
1) as root type : apt-get install zlib1g-dev


-----------------------------
FAQ 
-----------------------------

1) La libreria da errore di lettura!
   L'errore contiene "Unable to read odim data from HDF5 dataset: H5Dread failed".
   Che vuol dire?

   E' probabile che il file contenta qualcosa compresso con la libreria szlib,
   ma che la versione di HDF5 installata sulla macchina non sia stata compilata
   per includere il supporto a questa libreria.

   Un esempio di stack trace su standard output di tale errore e' il seguente:

	#000: H5Dio.c line 174 in H5Dread(): can't read data
	  major: Dataset
	  minor: Read failed
	#001: H5Dio.c line 404 in H5D_read(): can't read data
	  major: Dataset
 	  minor: Read failed
	#002: H5Dchunk.c line 1724 in H5D_chunk_read(): unable to read raw data chunk
	  major: Low-level I/O
	  minor: Read failed
	#003: H5Dchunk.c line 2737 in H5D_chunk_lock(): data pipeline read failed
	  major: Data filters
	  minor: Filter operation failed
	#004: H5Z.c line 1095 in H5Z_pipeline(): required filter is not registered
	  major: Data filters
	  minor: Read failed
	Unable to read odim data from HDF5 dataset: H5Dread failed

   Puo' capitare che succeda a distanza di tempo dalla messa in produzione
   se per esempio si e' in presenza di un file HDF5 proveniente da altri contesti 
   in cui la libreria szlib era stata usata.

   SOLUZIONE: reinstallare la libreria HDF5 assicurandosi di usare le opzioni
   indicate nella sezione dedicata all'installazione di HDF5.
   Se la libreria szlib non e' presente











