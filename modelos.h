#ifndef MODELOS_H
#define MODELOS_H

#include <string>

struct Empleado {
    int codigo;
    char nombre[50];
    char dui[12];
    char departamento[30];
    char cargo[30];
    bool activo;
};

struct Marcacion {
    int codigoEmpleado;
    char fecha[11];        // "YYYY-MM-DD"
    char horaEntrada[6];   // "HH:MM"
    char horaSalida[6];    // "HH:MM"
    int horasExtra;
    bool permiso;
    char motivoPermiso[50];
    char observaciones[100];
};

#endif
