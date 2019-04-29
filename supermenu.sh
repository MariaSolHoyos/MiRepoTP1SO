#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
	red=`tput setaf 1`;
	green=`tput setaf 2`;
	bg_pink=`tput setab 199`;
	pink=`tput setaf 199`;
	white=`tput setaf 15`;
	reset=`tput sgr0`;
	bold=`tput setaf bold`;

#------------------------------------------------------
# TODO: Completar con su path
#------------------------------------------------------
proyectoActual="https://github.com/MariaSolHoyos/MiRepoTP1SO.git"


#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
       imprimir_encabezado "---- S  U  P  E  R     M  E  N U ----";
	
    echo -e "\t El proyecto actual es:";
    echo -e "\t $proyectoActual";
    
    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a. Ver estado del proyecto";
    echo -e "\t\t\t b. Guardar cambios";
    echo -e "\t\t\t c. Actualizar repositorio";
    echo -e "\t\t\t d. Abrir en terminal";        
    echo -e "\t\t\t e. Abrir en carpeta"; 
    echo -e "\t\t\t f. Obtener información de PCB"; 

    echo -e "";
    #EJERCICIO 2.1
    echo -e "\t\t\t g. Fork";
    echo -e "\t\t\t h. Agregar seguridad al sistema contra la Bomba Fork";
    echo -e "\t\t\t i. Interprete de Comandos Shell";
	
    echo -e "";
    #EJERCICIO 2.2
    echo -e "\t\t\t j. Exclusion Mutua";
    echo -e "\t\t\t k. Sincronizacion";

    echo "";
    #EJERCICIO 2.3
    echo -e "\t\t\t l. Paralelismo de Datos";
    echo -e "\t\t\t m. Paralelismo de Tareas";
    echo -e "\t\t\t n. Paralelismo de Tareas (Secuencial)";


    echo -e "\t\t\t q. Salir";
    echo "";
    echo -e "\t Escriba la opción y presione ENTER";
}

#------------------------------------------------------
# FUNCTIONES AUXILIARES
#------------------------------------------------------

imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t${pink}-------------------------------------\t${reset}";
    echo -e "\t\t${pink}$1\t\t${reset}";
    echo -e "\t\t${pink}-------------------------------------\t${reset}";
    echo "";
}

esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}

malaEleccion () {
    echo -e "Selección Inválida ..." ;
}

decidir () {
	echo $1;
	while true; do
		echo "desea ejecutar? (s/n)";
    		read respuesta;
    		case $respuesta in
        		[Nn]* ) break;;
       			[Ss]* ) eval $1
				break;;
        		* ) echo "Por favor tipear S/s ó N/n.";;
    		esac
	done
}

#------------------------------------------------------
# FUNCTIONES del MENU
#------------------------------------------------------
a_funcion () {
    	imprimir_encabezado "Opción a. Ver estado del proyecto";
	echo "---------------------------"        
	echo "¿Algo para comitear?" #Somthing to commit?"
	echo "Ver estado del proyecto"        
	decidir "git status $proyectoActual"

	echo "---------------------------"        
	echo "¿Hay cambios? (¿Hacer un pull?)" #?Incoming changes (need a pull)?"
	decidir "git fetch $proyectoActual"
	decidir "git log HEAD..origin/master --oneline "
}

b_funcion () {
       	imprimir_encabezado "Opción b. Guardar cambios";
	decidir "git add -A"
       	echo "Ingrese mensaje para el commit:";
       	read mensaje;
       	decidir "git commit -m \"$mensaje\"";
       	decidir "git push origin master";
}

c_funcion () {
      	imprimir_encabezado "\tOpción c. Actualizar repositorio";
      	decidir "git pull $proyectoActual";   	 
}


d_funcion () {
	imprimir_encabezado "Opción d. Abrir en terminal";        
	decidir "cd $proyectoActual; xterm &";
}

e_funcion () {
	imprimir_encabezado "Opción e. Abrir en carpeta";        
	decidir "gnome-open $proyectoActual &";
}

f_funcion () {
	imprimir_encabezado "Opción f. Obtener información de PCB";
	echo "Ingrese proceso del que desee obtener informacion"
	read proceso
	decidir "cat /proc/\"$proceso\"/status | grep Name; cat /proc/\"$proceso\"/status | grep Pid | grep -v Tracer; cat /proc/\"$proceso\"/status | grep State; cat /proc/\"$proceso\"/status | grep voluntary_ctxt_switches"
}

g_funcion () {
	imprimir_encabezado "Opción g. Fork";        
	decidir "./fork"; 
}

h_funcion (){
	imprimir_encabezado "Opción h. Agregar seguridad al sistema contra la Bomba Fork";
	echo "${red}$1El valor actual es de:${reset}$1";
        ulimit -u;
	echo"";
        decidir "ulimit -u 5";
}

i_funcion () {
	imprimir_encabezado "Opción i. Interprete de Comandos Shell";
	decidir "./interpreteComandosShell";
}

j_funcion () {
	imprimir_encabezado "Opción j. Exclusion Mutua";
	decidir "./exclusionMutua";
}

k_funcion () {
	imprimir_encabezado "Opción k. Sincronizacion";
	decidir "./sincronizacion";
}

l_funcion () {
	imprimir_encabezado "Opción l. Paralelismo de Datos";
	decidir "./paralelismoDeDatos";
}

m_funcion () {
	imprimir_encabezado "Opción m. Paralelismo de Tareas";
	decidir "./paralelismoDeTareas";
}

n_funcion () {
	imprimir_encabezado "Opción n. Paralelismo de Tareas (Secuencial)";
	decidir "./paralelismoDeTareas-Secuencial";
}

#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
        g|G) g_funcion;;
	h|H) h_funcion;;
	i|I) i_funcion;;
	j|J) j_funcion;;
	k|K) k_funcion;;
	l|L) l_funcion;;
	m|M) m_funcion;;
	n|N) n_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done
 
