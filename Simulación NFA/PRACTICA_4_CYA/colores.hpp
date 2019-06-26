#pragma once

#ifndef _COLORS_ // El preprocesador puede comprobar si la etiqueta ha sido definida 
                 //y si está definida el código que sigue al #ifdef se incluirá en el
                 //paquete que se envía al compilador. Esta inclusión acaba cuando el p
                 //reprocesador encuentra la sentencia: #endif

#define _COLORS_ //crea una macro, que es la asociación de un identificador o identificador
                 //parametrizado con una cadena de token. Una vez definida la macro, el 
                 //compilador puede sustituir la cadena de token para cada aparición del
                 //identificador del archivo de código fuente.


/* FOREGROUND */

#define RST  "\x1B[0m" // Define RST

#define KRED  "\x1B[31m"    //Define KRED que será el color rojo

#define KGRN  "\x1B[32m"    //Define KGRN que será el color verde

#define KYEL  "\x1B[33m"    //Define KYEL que será el color amarillo

#define KBLU  "\x1B[34m"    //Define KBLU que será el color azuñ

#define KMAG  "\x1B[35m"    //Define KMAG que será el color magenta

#define KCYN  "\x1B[36m"    //Define KCYN que será el color cian

#define KWHT  "\x1B[37m"    //Define KWHT que será el color blanco


#define FRED(x) KRED x RST 

#define FGRN(x) KGRN x RST

#define FYEL(x) KYEL x RST

#define FBLU(x) KBLU x RST

#define FMAG(x) KMAG x RST

#define FCYN(x) KCYN x RST

#define FWHT(x) KWHT x RST


#define BOLD(x) "\x1B[1m" x RST //Negrita

#define UNDL(x) "\x1B[4m" x RST //Subrayado




#endif  