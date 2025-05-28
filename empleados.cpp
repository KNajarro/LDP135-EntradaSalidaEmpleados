#include "empleados.h"
#include <iostream>
#include <fstream>

void agregarEmpleado() {
    Empleado e;
    std::cout << "Código: "; std::cin >> e.codigo;
    std::cin.ignore();
    std::cout << "Nombre: "; std::cin.getline(e.nombre, 50);
    std::cout << "DUI: "; std::cin.getline(e.dui, 12);
    std::cout << "Departamento: "; std::cin.getline(e.departamento, 30);
    std::cout << "Cargo: "; std::cin.getline(e.cargo, 30);
    e.activo = true;

    std::ofstream file("empleados.dat", std::ios::binary | std::ios::app);
    file.write(reinterpret_cast<char*>(&e), sizeof(Empleado));
    file.close();
    std::cout << "Empleado agregado.\n";
}

void listarEmpleados() {
    Empleado e;
    std::ifstream file("empleados.dat", std::ios::binary);
    while (file.read(reinterpret_cast<char*>(&e), sizeof(Empleado))) {
        if (e.activo) {
            std::cout << "Código: " << e.codigo << " | Nombre: " << e.nombre << "\n";
        }
    }
    file.close();
}
