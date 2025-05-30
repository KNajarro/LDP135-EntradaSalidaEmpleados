#include <iostream>
#include "empleados.h"
#include "marcaciones.h"
#include "reportes.h"

void mostrarEncabezado()
{
    std::cout << "\033[1;36m";
    std::cout << "╔════════════════════════════════════════════════╗\n";
    std::cout << "║       SISTEMA DE CONTROL DE ASISTENCIA        ║\n";
    std::cout << "║               Empresa: LogicTime              ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    std::cout << "\033[0m";
}

void mostrarMenu()
{
    std::cout << "\n\033[1;33m";
    std::cout << "╔═════════════════════ MENÚ PRINCIPAL ═══════════════════╗\n";
    std::cout << "║ 1. ➕ Agregar Empleado                                  ║\n";
    std::cout << "║ 2. 📋 Listar Empleados                                  ║\n";
    std::cout << "║ 3. 🕒 Registrar Marcación                               ║\n";
    std::cout << "║ 4. 📑 Listar Marcaciones                                ║\n";
    std::cout << "║ 5. 📊 Reportes                                          ║\n";
    std::cout << "║ 0. 🚪 Salir del sistema                                 ║\n";
    std::cout << "╚═════════════════════════════════════════════════════════╝\n";
    std::cout << "\033[0m";
    std::cout << "Seleccione una opción: ";
}

void mostrarSubmenuReportes()
{
    std::cout << "\n\033[1;35m";
    std::cout << "╔═════════════════════ MENÚ DE REPORTES ══════════════════╗\n";
    std::cout << "║ 1. 📆 Asistencia por rango de fechas                    ║\n";
    std::cout << "║ 2. ⏱️ Horas trabajadas por empleado                     ║\n";
    std::cout << "║ 3. 🕗 Ausencias o llegadas tardías                      ║\n";
    std::cout << "║ 4. 📝 Listado de permisos solicitados                   ║\n";
    std::cout << "║ 5. 🧾 Resumen de horas extra acumuladas                ║\n";
    std::cout << "║ 0. 🔙 Volver al menú principal                          ║\n";
    std::cout << "╚═════════════════════════════════════════════════════════╝\n";
    std::cout << "\033[0m";
    std::cout << "Seleccione un reporte: ";
}

int main()
{
    int opcion;
    do
    {
        mostrarEncabezado();
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore();

        std::cout << "\n\033[1;34m-------------------------------------------\033[0m\n";

        switch (opcion)
        {
        case 1:
            agregarEmpleado();
            break;
        case 2:
            listarEmpleados();
            break;
        case 3:
            registrarMarcacion();
            break;
        case 4:
            listarMarcaciones();
            break;
        case 5:
        {
            int r;
            do
            {
                mostrarSubmenuReportes();
                std::cin >> r;
                std::cin.ignore();

                std::cout << "\n\033[1;34m-------------------------------------------\033[0m\n";
                switch (r)
                {
                case 1:
                    reporteAsistenciaPorFechas();
                    break;
                case 2:
                    reporteHorasTrabajadasPorEmpleado();
                    break;
                case 3:
                    reporteAusenciasYRetardos();
                    break;
                case 4:
                    reportePermisosSolicitados();
                    break;
                case 5:
                    reporteHorasExtraAcumuladas();
                    break;
                case 0:
                    std::cout << "Volviendo al menú principal...\n";
                    break;
                default:
                    std::cout << "\033[1;31mOpción inválida.\033[0m\n";
                }
                std::cout << "\033[1;34m-------------------------------------------\033[0m\n\n";
                if (r != 0)
                {
                    std::cout << "Presione [ENTER] para continuar...";
                    std::cin.get();
                    system("clear");
                }

            } while (r != 0);
            break;
        }
        case 0:
            std::cout << "\033[1;31mSaliendo del sistema... ¡Hasta pronto!\033[0m\n";
            break;
        default:
            std::cout << "\033[1;31mOpción inválida. Intente de nuevo.\033[0m\n";
        }

        if (opcion != 0 && opcion != 5)
        {
            std::cout << "\033[1;34m-------------------------------------------\033[0m\n\n";
            std::cout << "Presione [ENTER] para continuar...";
            std::cin.get();
            system("clear");
        }

    } while (opcion != 0);

    return 0;
}
