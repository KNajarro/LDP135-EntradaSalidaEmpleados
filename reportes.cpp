#include "reportes.h"
#include "modelos.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

bool dentroDeRango(const char *fecha, const char *inicio, const char *fin)
{
    return std::strcmp(fecha, inicio) >= 0 && std::strcmp(fecha, fin) <= 0;
}

void reporteAsistenciaPorFechas()
{
    char desde[11], hasta[11];
    std::cout << "Ingrese fecha desde (YYYY-MM-DD): ";
    std::cin.getline(desde, 11);
    std::cout << "Ingrese fecha hasta (YYYY-MM-DD): ";
    std::cin.getline(hasta, 11);

    std::ifstream file("marcaciones.dat", std::ios::binary);
    Marcacion m;
    std::cout << "\n📆 Asistencia entre " << desde << " y " << hasta << ":\n";
    while (file.read(reinterpret_cast<char *>(&m), sizeof(Marcacion)))
    {
        if (dentroDeRango(m.fecha, desde, hasta))
        {
            std::cout << "Empleado: " << m.codigoEmpleado
                      << " | Fecha: " << m.fecha
                      << " | Entrada: " << m.horaEntrada
                      << " | Salida: " << m.horaSalida << "\n";
        }
    }
    file.close();
}

void reporteHorasTrabajadasPorEmpleado()
{
    std::ifstream file("marcaciones.dat", std::ios::binary);
    Marcacion m;
    int totalMinutos = 0;
    int codigo;
    std::cout << "Ingrese código de empleado: ";
    std::cin >> codigo;
    std::cin.ignore();

    while (file.read(reinterpret_cast<char *>(&m), sizeof(Marcacion)))
    {
        if (m.codigoEmpleado == codigo)
        {
            int entrada = std::stoi(std::string(m.horaEntrada).substr(0, 2)) * 60 + std::stoi(std::string(m.horaEntrada).substr(3, 2));
            int salida = std::stoi(std::string(m.horaSalida).substr(0, 2)) * 60 + std::stoi(std::string(m.horaSalida).substr(3, 2));
            int trabajado = salida - entrada + m.horasExtra;
            totalMinutos += trabajado;
        }
    }
    file.close();

    std::cout << "⏱️ Total trabajado: " << (totalMinutos / 60) << " horas y " << (totalMinutos % 60) << " minutos.\n";
}

void reporteAusenciasYRetardos()
{
    std::cout << "🔍 Este sistema requiere que compares contra una hora estándar de entrada.\n";
    std::cout << "Por ejemplo, podrías considerar 08:00 como la hora límite.\n";
    // Lógica básica:
    std::ifstream file("marcaciones.dat", std::ios::binary);
    Marcacion m;
    while (file.read(reinterpret_cast<char *>(&m), sizeof(Marcacion)))
    {
        if (std::strncmp(m.horaEntrada, "08:00", 5) > 0)
        {
            std::cout << "Empleado: " << m.codigoEmpleado
                      << " | Llegó tarde: " << m.fecha
                      << " a las " << m.horaEntrada << "\n";
        }
    }
    file.close();
}

void reportePermisosSolicitados()
{
    std::ifstream file("marcaciones.dat", std::ios::binary);
    Marcacion m;
    std::cout << "\n📄 Lista de permisos:\n";
    while (file.read(reinterpret_cast<char *>(&m), sizeof(Marcacion)))
    {
        if (m.permiso)
        {
            std::cout << "Empleado: " << m.codigoEmpleado
                      << " | Fecha: " << m.fecha
                      << " | Motivo: " << m.motivoPermiso << "\n";
        }
    }
    file.close();
}

void reporteHorasExtraAcumuladas()
{
    std::ifstream file("marcaciones.dat", std::ios::binary);
    Marcacion m;
    int total = 0;
    while (file.read(reinterpret_cast<char *>(&m), sizeof(Marcacion)))
    {
        total += m.horasExtra;
    }
    file.close();

    std::cout << "🧾 Total horas extra acumuladas: " << (total / 60) << "h " << (total % 60) << "m\n";
}
