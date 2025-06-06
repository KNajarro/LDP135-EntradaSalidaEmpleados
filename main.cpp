#include <iostream>
#include "empleados.h"
#include "marcaciones.h"
#include "reportes.h"

void editarEmpleado();
void eliminarEmpleadoLogico();
void listarEmpleadosPorDepartamento();

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarEncabezado()
{
    std::cout << "+------------------------------------------+\n";
    std::cout << "|      SISTEMA DE CONTROL DE ASISTENCIA    |\n";
    std::cout << "|             Empresa: LogicTime           |\n";
    std::cout << "+------------------------------------------+\n";
}

void mostrarMenu()
{
    std::cout << "\n";
    std::cout << "+--------------------- MENU PRINCIPAL ---------------------+\n";
    std::cout << "| 1. Agregar Empleado                                       |\n";
    std::cout << "| 2. Listar Empleados                                       |\n";
    std::cout << "| 3. Editar Empleado                                        |\n";
    std::cout << "| 4. Eliminar Empleado                                      |\n";
    std::cout << "| 5. Listar por Departamento                                |\n";
    std::cout << "| 6. Registrar Marcacion                                    |\n";
    std::cout << "| 7. Listar Marcaciones                                     |\n";
    std::cout << "| 8. Reportes                                               |\n";
    std::cout << "| 0. Salir del sistema                                      |\n";
    std::cout << "+-----------------------------------------------------------+\n";
    std::cout << "Seleccione una opcion: ";
}

void mostrarSubmenuReportes()
{
    std::cout << "\n";
    std::cout << "+-------------------- MENU DE REPORTES ---------------------+\n";
    std::cout << "| 1. Asistencia por rango de fechas                         |\n";
    std::cout << "| 2. Horas trabajadas por empleado                          |\n";
    std::cout << "| 3. Ausencias o llegadas tardias                           |\n";
    std::cout << "| 4. Listado de permisos solicitados                        |\n";
    std::cout << "| 5. Resumen de horas extra acumuladas                      |\n";
    std::cout << "| 0. Volver al menu principal                               |\n";
    std::cout << "+-----------------------------------------------------------+\n";
    std::cout << "Seleccione un reporte: ";
}

int main()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    int opcion;
    do
    {
        mostrarEncabezado();
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore();

        std::cout << "\n-----------------------------------------------------------\n";

        switch (opcion)
        {
        case 1:
            agregarEmpleado();
            break;
        case 2:
            listarEmpleados();
            break;
        case 3:
            editarEmpleado();
            break;
        case 4:
            eliminarEmpleadoLogico();
            break;
        case 5:
            listarEmpleadosPorDepartamento();
            break;
        case 6:
            registrarMarcacion();
            break;
        case 7:
            listarMarcaciones();
            break;
        case 8:
        {
            int r;
            do
            {
                mostrarSubmenuReportes();
                std::cin >> r;
                std::cin.ignore();

                std::cout << "\n-----------------------------------------------------------\n";
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
                    std::cout << "Volviendo al menu principal...\n";
                    break;
                default:
                    std::cout << "Opcion invalida.\n";
                }
                std::cout << "-----------------------------------------------------------\n\n";
                if (r != 0)
                {
                    std::cout << "Presione [ENTER] para continuar...";
                    std::cin.get();
                    limpiarPantalla();
                }
            } while (r != 0);
            break;
        }
        case 0:
            std::cout << "Saliendo del sistema... Hasta pronto!\n";
            break;
        default:
            std::cout << "Opcion invalida. Intente de nuevo.\n";
        }

        if (opcion != 0 && opcion != 8)
        {
            std::cout << "-----------------------------------------------------------\n\n";
            std::cout << "Presione [ENTER] para continuar...";
            std::cin.get();
            limpiarPantalla();
        }

    } while (opcion != 0);

    return 0;
}
