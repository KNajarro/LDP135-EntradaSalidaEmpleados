#include "marcaciones.h"
#include "empleados.h"
#include "modelos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <iomanip>

bool existeEmpleado(int codigoBuscado);

void mostrarEmpleadosActivos()
{
    Empleado e;
    std::ifstream file("empleados.dat", std::ios::binary);

    std::cout << "\n+----------+-----------------------------+\n";
    std::cout << "| Codigo   | Nombre                      |\n";
    std::cout << "+----------+-----------------------------+\n";

    while (file.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
    {
        if (e.activo)
        {
            std::cout << "| " << std::setw(8) << e.codigo
                      << " | " << std::setw(27) << e.nombre << " |\n";
        }
    }

    std::cout << "+----------+-----------------------------+\n\n";
    file.close();
}

void registrarMarcacion()
{
    Marcacion m;
    bool valido = false;

    mostrarEmpleadosActivos();

    do
    {
        std::cout << "Ingrese el codigo de un empleado activo: ";
        std::cin >> m.codigoEmpleado;
        std::cin.ignore();

        if (existeEmpleado(m.codigoEmpleado))
        {
            valido = true;
        }
        else
        {
            std::cout << "Ese codigo no pertenece a ningun empleado activo. Intente de nuevo.\n";
        }
    } while (!valido);

    std::cout << "Fecha (dd/mm/aaaa): ";
    std::cin.getline(m.fecha, 11);
    std::cout << "Hora Entrada (HH:MM): ";
    std::cin.getline(m.horaEntrada, 6);
    std::cout << "Hora Salida (HH:MM): ";
    std::cin.getline(m.horaSalida, 6);
    std::cout << "Horas Extra (minutos): ";
    std::cin >> m.horasExtra;
    std::cout << "¿Tuvo permiso? (1=si, 0=no): ";
    std::cin >> m.permiso;
    std::cin.ignore();

    if (m.permiso)
    {
        std::cout << "Motivo Permiso: ";
        std::cin.getline(m.motivoPermiso, 50);
    }
    else
    {
        strcpy(m.motivoPermiso, "Ninguno");
    }

    std::cout << "Observaciones: ";
    std::cin.getline(m.observaciones, 100);

    std::ofstream file("marcaciones.dat", std::ios::binary | std::ios::app);
    file.write(reinterpret_cast<char *>(&m), sizeof(Marcacion));
    file.close();

    std::cout << "Marcacion registrada.\n";
}

void listarMarcaciones()
{
    Marcacion m;
    Empleado e;
    std::ifstream marcFile("marcaciones.dat", std::ios::binary);
    std::ifstream empFile("empleados.dat", std::ios::binary);

    if (!marcFile || !empFile)
    {
        std::cout << "No se pudo abrir uno de los archivos.\n";
        return;
    }

    std::cout << "+----------+-----------------------------+------------+------------+------------+\n";
    std::cout << "| Codigo   | Nombre                      | Fecha      | Entrada    | Salida     |\n";
    std::cout << "+----------+-----------------------------+------------+------------+------------+\n";

    while (marcFile.read(reinterpret_cast<char *>(&m), sizeof(Marcacion)))
    {
        empFile.clear();
        empFile.seekg(0);
        bool encontrado = false;

        while (empFile.read(reinterpret_cast<char *>(&e), sizeof(Empleado)))
        {
            if (e.codigo == m.codigoEmpleado)
            {
                encontrado = true;
                break;
            }
        }

        std::cout << "| " << std::setw(8) << m.codigoEmpleado
                  << " | " << std::setw(27) << (encontrado ? e.nombre : "Desconocido")
                  << " | " << std::setw(10) << m.fecha
                  << " | " << std::setw(10) << m.horaEntrada
                  << " | " << std::setw(10) << m.horaSalida << " |\n";
    }

    std::cout << "+----------+-----------------------------+------------+------------+------------+\n";

    marcFile.close();
    empFile.close();
}