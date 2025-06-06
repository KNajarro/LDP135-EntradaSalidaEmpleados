#include "empleados.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

bool existeEmpleado(int codigoBuscado)
{
    Empleado e;
    std::ifstream file("empleados.dat", std::ios::binary);
    while (file.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
    {
        if (e.codigo == codigoBuscado && e.activo)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void agregarEmpleado()
{
    Empleado e;
    int ultimoCodigo = 0;

    std::ifstream leer("empleados.dat", std::ios::binary);
    while (leer.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
    {
        if (e.codigo > ultimoCodigo)
        {
            ultimoCodigo = e.codigo;
        }
    }
    leer.close();

    int nuevoCodigo = ultimoCodigo + 1;
    std::cout << "Sugerencia de codigo: " << nuevoCodigo << "\n";
    std::cout << "Codigo (puede aceptar sugerencia): ";
    std::cin >> e.codigo;
    std::cin.ignore();

    std::cout << "Nombre: ";
    std::cin.getline(e.nombre, 50);
    std::cout << "DUI: ";
    std::cin.getline(e.dui, 12);
    std::cout << "Departamento: ";
    std::cin.getline(e.departamento, 30);
    std::cout << "Cargo: ";
    std::cin.getline(e.cargo, 30);
    e.activo = true;

    std::ofstream file("empleados.dat", std::ios::binary | std::ios::app);
    file.write(reinterpret_cast<char *>(&e), sizeof(Empleado));
    file.close();
    std::cout << "Empleado agregado.\n";
}

void listarEmpleados()
{
    Empleado e;
    std::ifstream file("empleados.dat", std::ios::binary);

    if (!file)
    {
        std::cout << "No se pudo abrir el archivo empleados.dat\n";
        return;
    }

    bool hayRegistros = false;

    std::cout << "+--------+-----------------------------+------------+\n";
    std::cout << "| Codigo | Nombre                      | Estado     |\n";
    std::cout << "+--------+-----------------------------+------------+\n";

    while (file.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
    {
        hayRegistros = true;
        std::cout << "| " << std::setw(6) << e.codigo
                  << " | " << std::setw(27) << e.nombre
                  << " | " << (e.activo ? "Activo   " : "Inactivo ") << " |\n";
    }

    std::cout << "+--------+-----------------------------+------------+\n";

    if (!hayRegistros)
    {
        std::cout << "No hay empleados registrados.\n";
    }

    file.close();
}

void editarEmpleado()
{
    int codigo;
    bool encontrado = false;
    Empleado e;

    std::fstream file("empleados.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!file)
    {
        std::cout << "Error al abrir el archivo.\n";
        return;
    }

    std::cout << "Ingrese el codigo del empleado a editar: ";
    std::cin >> codigo;
    std::cin.ignore();

    while (file.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
    {
        if (e.codigo == codigo && e.activo)
        {
            std::cout << "Empleado encontrado. Ingrese los nuevos datos:\n";
            std::cout << "Nombre: ";
            std::cin.getline(e.nombre, 50);
            std::cout << "DUI: ";
            std::cin.getline(e.dui, 12);
            std::cout << "Departamento: ";
            std::cin.getline(e.departamento, 30);
            std::cout << "Cargo: ";
            std::cin.getline(e.cargo, 30);

            file.seekp(-static_cast<std::streamoff>(sizeof(Empleado)), std::ios::cur);
            file.write(reinterpret_cast<char *>(&e), sizeof(Empleado));
            std::cout << "Empleado actualizado con éxito.\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        std::cout << "Empleado no encontrado o inactivo.\n";
    }

    file.close();
}

void eliminarEmpleadoLogico()
{
    int codigo;
    bool encontrado = false;
    Empleado e;

    std::fstream file("empleados.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!file)
    {
        std::cout << "Error al abrir el archivo.\n";
        return;
    }

    std::cout << "Ingrese el codigo del empleado a eliminar: ";
    std::cin >> codigo;
    std::cin.ignore();

    while (file.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
    {
        if (e.codigo == codigo && e.activo)
        {
            e.activo = false;
            file.seekp(-static_cast<std::streamoff>(sizeof(Empleado)), std::ios::cur);
            file.write(reinterpret_cast<char *>(&e), sizeof(Empleado));
            std::cout << "Empleado marcado como inactivo.\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        std::cout << "Empleado no encontrado o ya estaba inactivo.\n";
    }

    file.close();
}

void listarEmpleadosPorDepartamento()
{
    char depto[30];
    Empleado e;
    bool encontrado = false;

    std::cout << "Ingrese el nombre del departamento: ";
    std::cin.ignore();
    std::cin.getline(depto, 30);

    std::ifstream file("empleados.dat", std::ios::binary);
    if (!file)
    {
        std::cout << "No se pudo abrir el archivo.\n";
        return;
    }

    std::cout << "\nEmpleados en el departamento: " << depto << "\n";
    std::cout << "+--------+-----------------------------+\n";

    while (file.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
    {
        if (e.activo && std::strcmp(e.departamento, depto) == 0)
        {
            std::cout << "| " << std::setw(6) << e.codigo
                      << " | " << std::setw(27) << e.nombre << " |\n";
            encontrado = true;
        }
    }

    if (!encontrado)
    {
        std::cout << "No se encontraron empleados en ese departamento.\n";
    }

    file.close();
}
