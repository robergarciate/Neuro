AUTORES:
	Roberto Garcia Teodoro
	Marcio Valdemaro Garcia Roque

Nota Importante: Es necesario tener el analizador léxico 'flex' instalado para poder leer los ficheros.
Este analizador puede ser instalado facilmente en distribuciones de linux mediante el comando "sudo apt-get install flex"

McCulloch-Pits:
	Programa que ejecuta la red neuornal requerida dada una entrada:
	
	./mcCulloch-Pits {-f file}

	-f file: el fichero de entrada debe tener el siguiente formato "010001"...
		Es decir caracteres seguidos de una longuitud minima de 6 y una longuitud
		multiplo de 3.

	Ejemplo:
	./mcCulloch-Pits -f entrada.txt


Perceptron y Adaline:

	Programa que  entrena o clasifica unos datos medaniante una red neuronal
	de adaline o perceptron.

	./perceptron-adaline {-fin file }  {-a | -p}
	{-train num} {-test num} {-tasa num} {-etapas num} 
	[-clasificar -fclasf file [-fout file]]
	[-tolerancia num] [-iniAleat] [-interPrd | -interSum]

	-a: utiliza una red neuronan de adaline.

	-clasificar: cambia el modo de funcionamiento del programa para 
		que en vez de hacer train y test haga train y clasifique la
		informacion de un fichero que se le especifique en la opcion 
		-fclasf file

	-etapas: especifica el numero de etapas con el que se va a entrenar
		 la red neuronal, num sera el numero de etapas.

	-fclasf: especifica el fichero que se va clasificar, siendo este file.

	-fin: easpecifica el fichero que se va utilizar para hacer train y test,
		siendo este file.

	-fout: se requiere que este en modo clasificaccion, escribe en un fichero
		las predicciones hechas para la informacion recibida, el fichero de salida
		es file.

	-iniAleat: iniciliza los pesos y los umbrales de activacion a un valor entre
		-0.5 y 0.5, si no esta activo estos seran 0.

	-interPrd: reliza interpolacion mediante producto, ver documentacion
		para mas informacion.

	-interSum: realiza interpolacion mediante suma, ver documentacion.

	-p: utiliza una red neuronal de tipo perceptron.

	-tasa: especifica la tasa de aprendizaje.

	-test: especifica el tanto por ciento de datos que iran a test, este valor
		tiene que se mayor que 0.0 y menor o igual a 1.0.
		Si se quiere calsificar un archvio establecer este valor a 1.

	-tolerancia: establece la tolerancia de parada de una red de adaline.


	-test: especifica el tanto por ciento de datos que iran a train, este valor
		tiene que se mayor que 0.0 y menor o igual a 1.0.
		Si se quiere calsificar un archvio establecer este valor a 1.


	NOTAS:

		Las sumas de train y test tienen que ser 1.0 exacto o que tanto train como
		test sean 1.0, sino no ejecutara.

		Si no se establecen valores de train y test estos se estableceran automaticamente
		a 0.65 y 0.35.

		Si no se establece la tasa de aprendizaje se establecera a 0.1.

		Si no se establece la tolerancia se establecera a tasa/10.

	EJEMPLOS:

		./perceptron-adaline -a -fin bases-de-datos-p1/problema_real2.txt


		./perceptron-adaline -a -test 0.1 -train 0.9 -tasa 0.001 -tolerancia 0.01 -fin bases-de-datos-p1/problema_real2.txt 


		./perceptron-adaline -p -clasificar -fclasf bases-de-datos-p1/problema_real2_no _etiquetados.txt  -fin bases-de-datos-p1/problema_real2.txt -fout clasificacio.data


		./perceptron-adaline -p -interPrd -fin bases-de-datos-p1/problema_real2.txt
