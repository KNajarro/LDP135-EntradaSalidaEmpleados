#include "marcaciones.h"
#include <iostream>
#include <fstream>
#include <cstring>

void registrarMarcacion() {
    Marcacion m;
    std::cout << "Código de Empleado: "; std::cin >> m.codigoEmpleado;
    std::cin.ignore();
    std::cout << "Fecha (YYYY-MM-DD): "; std::cin.getline(m.fecha, 11);
    std::cout << "Hora Entrada (HH:MM): "; std::cin.getline(m.horaEntrada, 6);
    std::cout << "Hora Salida (HH:MM): "; std::cin.getline(m.horaSalida, 6);
    std::cout << "Horas Extra (minutos): "; std::cin >> m.horasExtra;
    std::cout << "¿Tuvo permiso? (1=sí, 0=no): "; std::cin >> m.permiso;
    std::cin.ignore();
    if (m.permiso) {
        std::cout << "Motivo Permiso: "; std::cin.getline(m.motivoPermiso, 50);
    } else {
        strcpy(m.motivoPermiso, "Ninguno");
    }
    std::cout << "Observaciones: "; std::cin.getline(m.observaciones, 100);

    std::ofstream file("marcaciones.dat", std::ios::binary | std::ios::app);
    file.write(reinterpret_cast<char*>(&m), sizeof(Marcacion));
    file.close();
    std::cout << "Marcación registrada.\n";
}

void listarMarcaciones() {
    Marcacion m;
    std::ifstream file("marcaciones.dat", std::ios::binary);
    while (file.read(reinterpret_cast<char*>(&m), sizeof(Marcacion))) {
        std::cout << "Empleado: " << m.codigoEmpleado << " | Fecha: " << m.fecha << " | Entrada: " << m.horaEntrada << " | Salida: " << m.horaSalida << "\n";
    }
    file.close();
}
