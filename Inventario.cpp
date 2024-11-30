#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>


using namespace std;

void menu()
{
	cout<<" \t|-------------------------------------------|\n";
    cout<<" \t|          INVENTARIO DE PRODUCTOS          |\n";
    cout<<" \t|-------------------------------------------|\n";
    cout<<" \t|  1. AGREGAR PRODUCTO                      |\n";
    cout<<" \t|  2. ELIMINAR PRODUCTO                     |\n";
    cout<<" \t|  3. MODIFICAR PRODUCTO                    |\n";
	cout<<" \t|  4. MOSTRAR PRODUCTO                      |\n";
	cout<<" \t|  5. BUSCAR PRODUCTO                       |\n";
	cout<<" \t|  6. EXPORTAR INVENTARIO A CSV             |\n";
	cout<<" \t|  7. SALIR                                 |\n";
    cout<<" \t|-------------------------------------------|\n";
    cout<<"\n\t Ingrese una opcion: ";
}

struct Producto
{
    int id;
    string nombre;
    int cantidad;
    double precio;
    Producto* siguiente;
};

class Inventario
{
private:
    Producto* cabeza;

    Producto* buscarProductoPorId(int id)
	{
        Producto* actual = cabeza;
        while (actual != NULL && actual->id != id)
		{
            actual = actual->siguiente;
        }
        return actual;
    }

    void intercambiar(Producto* a, Producto* b)
	{
        swap(a->id, b->id);
        swap(a->nombre, b->nombre);
        swap(a->cantidad, b->cantidad);
        swap(a->precio, b->precio);
    }

public:
    Inventario() : cabeza(NULL) {}

    void agregarProducto(int id, string nombre, int cantidad, double precio)
	{
        Producto* nuevo = new Producto
		{
			id, nombre, cantidad, precio, NULL
		};

        if (!cabeza || cabeza->cantidad > cantidad)
		{
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } else{
            Producto* actual = cabeza;
            while (actual->siguiente && actual->siguiente->cantidad <= cantidad)
			{
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        cout <<"Producto agregado con exito.\n";
    }

    void eliminarProducto(int id)
	{
        if (!cabeza)
		{
            cout <<"El inventario esta vacio.\n";
            return;
        }

        if (cabeza->id == id)
		{
            Producto* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cout <<"Producto eliminado.\n";
            return;
        }

        Producto* actual = cabeza;
        while (actual->siguiente && actual->siguiente->id != id)
		{
            actual = actual->siguiente;
        }

        if (actual->siguiente)
		{
            Producto* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            cout <<"Producto eliminado.\n";
        } else{
            cout <<"El producto no se encontro.\n";
        }
    }

    void modificarProducto(int id, int nuevaCantidad, double nuevoPrecio)
	{
        Producto* producto = buscarProductoPorId(id);
        if (producto)
		{
            producto->cantidad = nuevaCantidad;
            producto->precio = nuevoPrecio;
            cout <<"Producto modificado con exito.\n";
        } else{
            cout <<"El producto no se encontro.\n";
        }
    }

    void mostrarProductos()
	{
        if (!cabeza) {
            cout <<"El inventario esta vacio.\n";
            return;
        }

        Producto* actual = cabeza;
        cout << left <<setw(10) <<"ID" <<setw(20) <<"Nombre"
             << setw(10) <<"Cantidad" <<setw(10) <<"Precio" <<endl;
        while (actual)
		{
            cout <<left <<setw(10) <<actual->id <<setw(20) <<actual->nombre
                 <<setw(10) <<actual->cantidad <<setw(12) <<actual->precio <<endl;
            if (actual->cantidad < 10)
			{
                cout <<"**Alerta!: Stock bajo**\n\n";
            }
            actual = actual->siguiente;
        }
    }

    void buscarProducto(int id)
	{
        Producto* producto = buscarProductoPorId(id);
        if (producto)
		{
            cout <<"Producto encontrado:\n";
            cout <<"ID: " <<producto->id <<"\n"
                 <<"Nombre: " <<producto->nombre <<"\n"
                 <<"Cantidad: " <<producto->cantidad <<"\n"
                 <<"Precio: $" <<producto->precio <<endl;
        } else
		{
            cout <<"El producto no se encontro.\n";
        }
    }
    
    // Exportar los datos a un archivos CSV
    void exportarCSV(const string& nombreArchivo)
    {
    	ofstream archivo("nombreArchivo");
    	
    	if(!archivo.is_open())
    	{
    		cout <<"El archivo no se pudo abrir.\n";
    		return;
		}
		archivo <<"INVENTARIO\n"; // Encabezado CSV
		
		Producto* actual = cabeza;
		while(actual)
		{
			archivo 
			    <<"================================" <<endl
			    <<"ID: " <<actual->id << endl
			    <<"Nombre: " <<actual->nombre <<endl
			    <<"Cantidad: " <<actual->cantidad <<endl
			    <<"Precio: " <<actual->precio <<endl;
			actual = actual->siguiente;
		}
		archivo.close();
		cout <<"Inventario a sido exportado a " <<nombreArchivo <<"con exito.\n";
	}

    ~Inventario()
	{
        while (cabeza)
		{
            Producto* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

int main()
{
	system("color 04");
	
    Inventario inventario;
    int opcion;
	string nombreArchivo;

    do {
    	menu();
		cin>>opcion;
        switch (opcion)
		{
            case 1:
			{
                int id, cantidad;
                double precio;
                string nombre;
                cout <<"Ingrese el ID: ";
                cin >>id;
                cin.ignore();
                cout <<"Ingrese el nombre: ";
                getline(cin, nombre);
                cout <<"Ingrese la cantidad: ";
                cin >>cantidad;
                cout <<"Ingrese el precio: ";
                cin >>precio;
                inventario.agregarProducto(id, nombre, cantidad, precio);
                break;
            }
            case 2:
			{
                int id;
                cout <<"Ingrese el ID del producto a eliminar: ";
                cin >>id;
                inventario.eliminarProducto(id);
                break;
            }
            case 3:
			{
                int id, nuevaCantidad;
                double nuevoPrecio;
                cout <<"Ingrese el ID del producto a modificar: ";
                cin >>id;
                cout <<"Ingrese una nueva cantidad: ";
                cin >>nuevaCantidad;
                cout <<"Ingrese el nuevo precio: ";
                cin >>nuevoPrecio;
                inventario.modificarProducto(id, nuevaCantidad, nuevoPrecio);
                break;
            }
            case 4:
                inventario.mostrarProductos();
                break;
            case 5: 
			{
                int id;
                cout <<"Ingrese el ID del producto a buscar: ";
                cin >>id;
                inventario.buscarProducto(id);
                break;
            }
            case 6: 
			{
				string nombArchivo;
                cout <<"Ingrese el nombre del archivo, incluya .csv: ";
                cin >> nombreArchivo;
                inventario.exportarCSV(nombreArchivo);
                break;
            }
            case 7:
                cout <<"Saliendo del programa...\n";
                break;
            default:
                cout <<"Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}
