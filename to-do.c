#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

Nodo *CrearTareaVacia();
void InsertarTarea(Nodo ** Start , Nodo *Nodoo);
Nodo * crearTarea(Tarea nuevaTarea);
void limpiarBuffer();
void mostrarTareas(Nodo *tarea);
Tarea BuscarTareaI(Nodo ** Start,int id);
Tarea BuscarTareaP(Nodo ** Start,char *clave);
void MoverTarea(Nodo **Start1,Nodo **Start2,int id);
void BuscarTareaPorID(Nodo ** Start1,Nodo ** Start2,int id);
void BuscarTareaPorNombre(Nodo ** Start1,Nodo ** Start2,char *clave);
void mostrarUnaTarea(Tarea tarea);


int main(){

    Nodo *TareasPendientes  = CrearTareaVacia(),*TareasRealizadas  = CrearTareaVacia();
    int control,IDTarea = 1000,duracion, cantCaracteres,id;
    Tarea nuevaTarea;
    char descripcion[120];

    /*
    Tarea T1 = {1000,"llll",43};
    Tarea T2 = {1001,"bbbb",23};
    Tarea T3 = {1002,"ooooo",87};
    Tarea T4 = {1003,"www",63};
    */
    do
    {
        printf("\nAgregando tarea ......\n");
        //duracion de la tarea
        do
        {
           printf("\nDuracion entre 10 a 100: ");
            scanf("%d",&duracion);
        } while (duracion<10 || duracion >100);
        nuevaTarea.Duracion = duracion;
        limpiarBuffer();

        //descripcion de la tarea
        printf("\nDescripcion: ");
        fgets(descripcion,sizeof(descripcion),stdin);

        //descripcion dianamico
        cantCaracteres = strlen(descripcion);
        nuevaTarea.Descripcion = (char *)malloc(sizeof(char)*cantCaracteres);
        strcpy(nuevaTarea.Descripcion,descripcion);
        descripcion[strcspn(descripcion,"\n")]='\0';

        //ID de la tarea
        nuevaTarea.TareaID = IDTarea;

        // se agrega una nueva tarea pendiente
        InsertarTarea(&TareasPendientes,crearTarea(nuevaTarea));

        printf("\nDesea agregar mas tareas? si = 1, no = 0 : ");
        scanf("%d",&control);
        limpiarBuffer();
        IDTarea++;
    } while (control == 1);
    /*
    InsertarTarea(&TareasPendientes,crearTarea(T1));
    InsertarTarea(&TareasRealizadas,crearTarea(T2));
    InsertarTarea(&TareasPendientes,crearTarea(T3));
    InsertarTarea(&TareasRealizadas,crearTarea(T4));
    */
    printf("\n-----Tareas pendientes -----");
    mostrarTareas(TareasPendientes);
    printf("\n-----Tareas realizadas -----");
    mostrarTareas(TareasRealizadas);

    //mueve tereas de pendientes a realizadas
    do
    {
        printf("\nIngrese el ID de la tarea a mover: ");
        scanf("%d",&id);
        limpiarBuffer();
        MoverTarea(&TareasPendientes,&TareasRealizadas,id);
        printf("\n-----Tareas pendientes -----");
        mostrarTareas(TareasPendientes);
        printf("\nDesea mover mas tareas?\n1 - si\n0 - no");
        scanf("%d",&control);
        limpiarBuffer();
    } while (control == 1);
    
    printf("\n-----Tareas realizadas -----");
    mostrarTareas(TareasRealizadas);
    printf("\n-----Tareas pendientes -----");
    mostrarTareas(TareasPendientes);

    //consulta de tareas
    do
    {
        printf("Consultar tareas por\n1 -ID\n2 -palabra clave\n");// ingresa las opciones a buscar
        scanf("%d",&control);
        limpiarBuffer();
    } while (control>2 || control<1);

    switch (control)
    {
    case 1://consulta de tareas por ID
        printf("\nIngrese el ID a buscar: ");
        scanf("%d",&id);
        limpiarBuffer();
        BuscarTareaPorID(&TareasPendientes,&TareasRealizadas,id);// busca en las dos listas
        break;
    case 2://consulta de tareas por clave
        printf("\nIngrese la palabra clave: ");
        fgets(descripcion,sizeof(descripcion),stdin);
        descripcion[strcspn(descripcion,"\n")]='\0';
        BuscarTareaPorNombre(&TareasPendientes,&TareasRealizadas,descripcion); // busca en las dos listas
        break;
    }

}

void limpiarBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF){}
}

void BuscarTareaPorNombre(Nodo ** Start1,Nodo ** Start2,char *clave){
    Tarea tareaEncontrada; 
    tareaEncontrada = BuscarTareaP(Start1,clave); //busca la tarea en la lista de pendientes
    if (tareaEncontrada.TareaID != -1)
    {
        mostrarUnaTarea(tareaEncontrada);
        printf("\nEs una tarea pendiente");
    }else{
        tareaEncontrada = BuscarTareaP(Start2,clave); //busca la tarea en la lista de realizadas
        if (tareaEncontrada.TareaID != -1)
        {
            mostrarUnaTarea(tareaEncontrada);
            printf("\nEs una tarea realizada");
        }else{
            printf("\nNo existe la tarea");
        }
    }
}

Nodo *CrearTareaVacia(){
    return NULL;
}

void InsertarTarea(Nodo ** Start , Nodo *Nodoo)
{
    Nodoo->Siguiente = *Start;
    *Start  = Nodoo ;
}

Nodo * crearTarea(Tarea nuevaTarea){
  Nodo * nodo = (Nodo *) malloc(sizeof(Nodo));
  nodo->T = nuevaTarea;
  nodo->Siguiente = NULL;
  return nodo;
}

void mostrarTareas(Nodo *tarea){
    Nodo * Aux = tarea;
    printf("\n");
    while (Aux)
    {
        printf("\nID : %d ", Aux->T.TareaID);
        printf("\nDuracion : %d ", Aux->T.Duracion);
        printf("\nDescripcion : %s\n", Aux->T.Descripcion);
        Aux = Aux->Siguiente;
    }

}

Tarea BuscarTareaI(Nodo ** Start,int id)
{
  Nodo * Aux = *Start;
  Tarea tareaPordefecto = {-1,"vacio",0};
  while (Aux && Aux->T.TareaID != id)
  {
    Aux = Aux->Siguiente;
  }
  if (Aux)
  {
    return Aux->T;
  }else{
    return tareaPordefecto;
  }
  
  
}
Tarea BuscarTareaP(Nodo ** Start,char *clave)
{
  Nodo * Aux = *Start;
  Tarea tareaPordefecto = {-1,"vacio",0};
  while (Aux && strstr(Aux->T.Descripcion,clave) == NULL)
  {
    Aux = Aux->Siguiente;
  }
  if (Aux)
  {
    return Aux->T;
  }else{
    return tareaPordefecto;
  }
  
  
}
void MoverTarea(Nodo **Start1,Nodo **Start2,int id){

    //se busca la tarea a mover
    Nodo ** aux1 = Start1;
    while (*aux1 && (*aux1)->T.TareaID != id)
    {
        aux1 = &(*aux1)->Siguiente;
    }
    if (*aux1)
    {
        //se elimina la tarea de la lista de tareas pendientes
        Nodo *temp = *aux1;  // Guardamos el nodo a cambiar de lista en una variable temporal.
        *aux1 = (*aux1)->Siguiente;  // Desvinculamos el nodo de la lista .

        //se carga a la lista de tareas realizadas
        temp->Siguiente =*Start2;
        *Start2 = temp;
        
        printf("Tarea movia a tareas realizadas\n");
    }else{
        printf("No se encontro la tarea\n");
    }
}

void BuscarTareaPorID(Nodo ** Start1,Nodo ** Start2,int id){
    Tarea tareaEncontrada; 
    tareaEncontrada = BuscarTareaI(Start1,id); //busca la tarea en la lista de pendientes
    if (tareaEncontrada.TareaID != -1)
    {
        mostrarUnaTarea(tareaEncontrada);
        printf("\nEs una tarea pendiente");
    }else{
        tareaEncontrada = BuscarTareaI(Start2,id); //busca la tarea en la lista de realizadas
        if (tareaEncontrada.TareaID != -1)
        {
            mostrarUnaTarea(tareaEncontrada);
            printf("\nEs una tarea realizada");
        }else{
            printf("\nNo existe la tarea");
        }
    }
}

void mostrarUnaTarea(Tarea tarea){
    printf("\nID : %d ", tarea.TareaID);
    printf("\nDuracion : %d ", tarea.Duracion);
    printf("\nDescripcion : %s\n", tarea.Descripcion);
}