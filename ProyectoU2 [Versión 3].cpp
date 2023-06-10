#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

const int maxLevel = 100;

class Villages {
private:
    vector<vector<int>> adjacencyMatrix;
    unordered_map<string, int> vertexIndices;

public:
    void addVertex(const string& vertex) {
        if (vertexIndices.find(vertex) == vertexIndices.end()) {
            int index = vertexIndices.size();
            vertexIndices[vertex] = index;
            for (vector<int>& row : adjacencyMatrix) {
                row.resize(index + 1);
            }
            adjacencyMatrix.resize(index + 1, vector<int>(index + 1));
        }
    }

    void addEdge(const string& vertex1, const string& vertex2) {
        if (vertexIndices.find(vertex1) == vertexIndices.end() || vertexIndices.find(vertex2) == vertexIndices.end()) {
            cout << "Uno o ambos vertices no existen." << endl;
            return;
        }

        int index1 = vertexIndices[vertex1];
        int index2 = vertexIndices[vertex2];
        adjacencyMatrix[index1][index2] = 1;
        adjacencyMatrix[index2][index1] = 1;
    }

    void addEdgeWithWeight(const string& vertex1, const string& vertex2, int weight) {
        if (vertexIndices.find(vertex1) == vertexIndices.end() || vertexIndices.find(vertex2) == vertexIndices.end()) {
            cout << "Uno o ambos vertices no existen." << endl;
            return;
        }

        int index1 = vertexIndices[vertex1];
        int index2 = vertexIndices[vertex2];
        adjacencyMatrix[index1][index2] = weight;
        adjacencyMatrix[index2][index1] = weight;
    }

    void printAdjacencyMatrix() {
        for (const vector<int>& row : adjacencyMatrix) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    void printVertexIndices() {
        for (const auto& entry : vertexIndices) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }
};

class Guardian {
private:
    string name;
    int powerLevel;
    string mainMaster;
    string village;
    bool isMaster;
    int chosen;

public:
    Guardian(const string& name, int powerLevel, const string& mainMaster, const string& village)
    : name(name), powerLevel(powerLevel), mainMaster(mainMaster), village(village), isMaster(false), chosen(0) {}
    
    Guardian(const string& name, int powerLevel, const string& mainMaster, const string& village, int chosen)
    : name(name), powerLevel(powerLevel), mainMaster(mainMaster), village(village), isMaster(false), chosen(chosen) {}

    void printInfo() const {
	    cout << "Nombre: " << name << endl;
	    cout << "Nivel de poder: " << powerLevel << endl;
	    cout << "Maestro principal: " << mainMaster << endl;
	    cout << "Aldea: " << village << endl;
	    cout << "Estado: " << (isMaster ? "Maestro" : "Aprendiz") << endl;
	    cout << "Elegido: " << chosen << endl;
	    cout << endl;
	}

    string getName() const {
        return name;
    }
    
    int getPowerLevel() const {
        return powerLevel;
    }

    string getMainMaster() const {
        return mainMaster;
    }

    void setIsMaster(bool value) {
        isMaster = value;
    }
    
    bool getIsMaster() const {
        return isMaster;
    }
    
    string getVillage() const {
        return village;
    }
    
    void setChosen(int value) {
        chosen = value;
    }
    
};

class Guardians {
private:
    unordered_map<string, vector<Guardian>> guardiansByVillage;

public:
    void addGuardian(const string& village, const string& name, int powerLevel, const string& mainMaster) {
	    if (powerLevel > maxLevel) {
	        cout << "El nivel de poder del guardian '" << name << "' excede el limite maximo permitido." << endl;
	        return;
	    }
	
	    guardiansByVillage[village].emplace_back(name, powerLevel, mainMaster, village);
	}
	
	void addGuardianPlayer(const string& village, const string& name, int powerLevel, const string& mainMaster, int chosen) {
	    if (powerLevel > maxLevel) {
	        cout << "El nivel de poder del guardian '" << name << "' excede el limite maximo permitido." << endl;
	        return;
	    }
	
	    guardiansByVillage[village].emplace_back(name, powerLevel, mainMaster, village, chosen);
	}

    void printGuardiansByVillage() {
        for (const auto& entry : guardiansByVillage) {
            const string& village = entry.first;
            const vector<Guardian>& guardians = entry.second;

            cout << "Aldea: " << village << endl;
            cout << "Cantidad de guardianes: " << guardians.size() << endl;

            for (const Guardian& guardian : guardians) {
                guardian.printInfo();
            }

            cout << "--------------------------------------------------" << endl;
        }
    }
    
    void printApprenticeGuardiansByVillage() {
	    for (const auto& entry : guardiansByVillage) {
	        const string& village = entry.first;
	        const vector<Guardian>& guardians = entry.second;
	
	        for (const Guardian& guardian : guardians) {
	            if (!guardian.getIsMaster()) {
	                cout << "\t\t\t\t    Nombre: " << guardian.getName() << endl;
	                cout << "\t\t\t\t    Nivel de poder: " << guardian.getPowerLevel() << endl;
	                cout << "\t\t\t\t    Maestro principal: " << guardian.getMainMaster() << endl;
	                cout << "\t\t\t\t    Aldea: " << guardian.getVillage() << endl;
	                cout << "\t\t\t\t    Estado: " << (guardian.getIsMaster() ? "Maestro" : "Aprendiz") << endl;
	                cout << endl;
	                cout << "\t\t\t\t    --------------------------------------------------" << endl;
	                
	            }
	        }	        
	    }
	}
    
    void checkGuardianStatus() {
	    for (auto& entry : guardiansByVillage) {
	        vector<Guardian>& guardians = entry.second;
	
	        for (Guardian& guardian : guardians) {
	            bool isMaster = false;
	
	            for (const auto& entry2 : guardiansByVillage) {
	                const vector<Guardian>& otherGuardians = entry2.second;
	
	                for (const Guardian& otherGuardian : otherGuardians) {
	                    if (otherGuardian.getMainMaster() == guardian.getName()) {
	                        isMaster = true;
	                        break;
	                    }
	                }
	
	                if (isMaster) {
	                    break;
	                }
	            }
	
	            if (isMaster) {
	                guardian.setIsMaster(true);
	            } else {
	                guardian.setIsMaster(false);
	            }
	        }
	    }
	}
	
	bool hasMaxLevelGuardian(const string& village) const {
	    const vector<Guardian>& guardians = guardiansByVillage.at(village);
	    for (const Guardian& guardian : guardians) {
	        if (guardian.getPowerLevel() == maxLevel) {
	            return true;
	        }
	    }
	    return false;
	}
	
	void printVillagesWithoutMaxLevelGuardian() {
	    for (const auto& entry : guardiansByVillage) {
	        const string& village = entry.first;
	        if (!hasMaxLevelGuardian(village)) {
	            cout << "\t\t\t\t    - " << village << endl;
	        }
	    }
	}
	
	bool isValidVillage(const string& village) const {
	    return guardiansByVillage.count(village) > 0;
	}
	
	void chooseApprenticeGuardian(Guardians& guardians) {
	    bool guardianFound = false;
	
	    while (!guardianFound) {
	        cout << "\t\t\t\t    Ingrese el nombre del guardian que desea elegir: ";
	        string guardianName;
	        cin >> guardianName;
	
	        // Recorrer todos los guardianes por aldea
	        for (auto& entry : guardians.guardiansByVillage) {
	            vector<Guardian>& guardians = entry.second;
	
	            // Buscar el guardián de tipo aprendiz por nombre y cambiar chosen a 1
	            for (Guardian& guardian : guardians) {
	                if (!guardian.getIsMaster() && guardian.getName() == guardianName) {
	                    guardian.setChosen(1);
	                    guardianFound = true;
	                    break;
	                }
	            }
	
	            if (guardianFound) {
	                break;
	            }
	        }
	
	        if (!guardianFound) {
	            cout << "\t\t\t\t    No se encontro ningun guardian aprendiz con ese nombre. Intentelo nuevamente." << endl;
	        }
	    }
	
	    cout << "\t\t\t\t    Guardian seleccionado exitosamente." << endl;
	}
	
};

string getValidVillage(const Guardians& guardians) {
    string village;
    bool isValid = false;
    
    cin.ignore();

    while (!isValid) {
        cout << "\t\t\t\t    Ingrese el nombre de la aldea: ";
        getline(cin, village);

        if (guardians.isValidVillage(village) && !guardians.hasMaxLevelGuardian(village)) {
            isValid = true;
        } else {
            cout << "\t\t\t\t    La aldea ingresada no es valida o ya tiene un guardian de nivel maximo. Por favor, intente nuevamente." << endl;
        }
    }

    return village;
}

int main() {

    Villages graph;
    Guardians guardians;
    string guardianName;

    ifstream file("Villages.csv");
    if (file) {
        string line;
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string village1, village2;
            getline(ss, village1, ',');
            getline(ss, village2, ',');
            graph.addVertex(village1);
            graph.addVertex(village2);
            graph.addEdge(village1, village2);
        }
        file.close();

    } else {
        cout << "Error al abrir el archivo Villages.csv." << endl;
    }

    ifstream file2("Guardians.csv");
	if (file2) {
	    string line;
	    getline(file2, line);
	    while (getline(file2, line)) {
	        stringstream ss(line);
	        string name, powerLevelStr, mainMaster, village;
	        getline(ss, name, ',');
	        getline(ss, powerLevelStr, ',');
	        getline(ss, mainMaster, ',');
	        getline(ss, village, ',');
	
	        int powerLevel = stoi(powerLevelStr);
	
	        graph.addVertex(village);
	        guardians.addGuardian(village, name, powerLevel, mainMaster);
	    }
	    file2.close();
	
	    guardians.checkGuardianStatus();
	
	    //graph.printAdjacencyMatrix();
	
	    //cout << "\nOrden de las villas:\n";
	    //graph.printVertexIndices();
	
	    //cout << "\nGuardianes por aldea:\n";
	    //guardians.printGuardiansByVillage();
	} else {
	    cout << "Error al abrir el archivo Guardians.csv." << endl;
	}

    // Presentación y sinopsis del juego
    cout << "******************************************************************** The Guardian Journey ******************************************************************" << endl;

    cout << "\t\t\t\t    En un mundo devastado por la guerra y la lucha constante existen los Guardianes. Los" << endl
         << "\t\t\t\t\t\t\t\t        Guardianes son heroes con habilidades y destrezas unicas que protegen a las aldeas a lo" << endl
         << "\t\t\t\t    largo de toda la tierra siendo estas los ultimos asentamientos de la humanidad." << endl << endl
         << "\t\t\t\t    Tesla es la capital de estas tierras y hoy corresponde a un farol en la oscuridad donde" << endl
         << "\t\t\t\t    abunda la prosperidad, el desarrollo tecnologico y entregan la mayor proteccion a lo largo" << endl
         << "\t\t\t\t    del nuevo mundo." << endl << endl
         << "\t\t\t\t    Cada ser humano tiene un poder interior que le permite definir su destino y elegir en una" << endl
         << "\t\t\t\t    de las cuatro facciones que existen hoy en dia, las cuales son; magos, vikingos," << endl
         << "\t\t\t\t    nigromantes y bestias. En ocasiones existen humanos con la posibilidad de desarrollar" << endl
         << "\t\t\t\t    habilidades de mas de una faccion lo que les permite ser grandes candidatos a recibir el" << endl
         << "\t\t\t\t    titulo de guardianes." << endl << endl
         << "\t\t\t\t    A los alrededores de Tesla se encuentran las aldeas que corresponden a asentamientos" << endl
         << "\t\t\t\t\t\t\t\t        que cumplen distintas funciones dentro de la gran organizacion de la humanidad y en cada" << endl
         << "\t\t\t\t    una de estas aldeas existen maestros, quienes ensenan las artes de los guardianes." << endl<< endl
         << "\t\t\t\t    El sueno de cada nino es convertirse en un Guardian y ganar el torneo, pero el viaje de un" << endl
         << "\t\t\t\t    aprendiz no es facil y su destino depende de las decisiones que tome a lo largo de este" << endl
         << "\t\t\t\t    recorrido." << endl << endl;

    cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
	
	// Objetivo y reglas
	cout << "**************************************************************** Objetivos y reglas del juego **************************************************************" << endl << endl;
	
	cout << "\t\t\t\t\t\t\t\t     |Objetivo del juego|" << endl << endl
		 << "\t\t\t\t    Tomaras el control de un aprendiz de guardian o crearas uno, con el cual deberas recorrer" << endl
	     << "\t\t\t\t    las aldeas de un vasto mundo en busca de derrotar al guardian mas poderoso ubicado en Tesla." << endl << endl
	     << "\t\t\t\t    Para lograr este objetivo, tendras que subir de nivel a traves de entrenamientos con los" << endl
	     << "\t\t\t\t    aprendices o maestros guardianes de las distintas aldeas. Todo con el unico fin de llegar a ser" << endl
	     << "\t\t\t\t    lo suficientemente fuerte como para enfrentarte y derrotar al guardián en Tesla, y coronarte" << endl
	     << "\t\t\t\t    como el mas poderoso de todos." << endl << endl;
	     
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
    
    cout << "\t\t\t\t\t\t\t\t      |Reglas del juego|" << endl << endl
	     << "\t\t\t\t    *Sistema de nivel*:" << endl << endl
	     << "\t\t\t\t      - El nivel maximo permitido es 100." << endl
	     << "\t\t\t\t      - Tu guardian comenzara con un nivel equivalente al 50% del nivel maximo." << endl
	     << "\t\t\t\t      - Visitar una aldea otorgara a tu guardian 1 nivel." << endl
	     << "\t\t\t\t      - Superar un entrenamiento con un aprendiz de la aldea otorgara a tu guardian 1 nivel." << endl
	     << "\t\t\t\t      - Superar el entrenamiento con un maestro de la aldea otorgara a tu guardian 2 niveles." << endl
	     << "\t\t\t\t      - La cantidad maxima de niveles que se pueden obtener de entrenamientos por aldea es 3." << endl
	     << "\t\t\t\t      - Tu guardian se considerara preparado cuando alcance el 90% del nivel maximo." << endl << endl;
	
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
	
	cout << "\t\t\t\t    *Sistema de entrenamientos*:" << endl << endl
	     << "\t\t\t\t      - Los entrenamientos consistiran en una serie de pruebas que tu guardian debera superar." << endl
	     << "\t\t\t\t      - La cantidad minima de pruebas en un entrenamiento con un guardian aprendiz es de 3." << endl
	     << "\t\t\t\t      - La cantidad minima de pruebas en un entrenamiento con un guardian maestro es de 5." << endl
	     << "\t\t\t\t      - Se anadira 1 prueba adicional al entrenamiento por cada 10 niveles menos que tenga tu guardian con el que entrene." << endl
	     << "\t\t\t\t      - Cada prueba consistira en lanzar un dado y adivinar si el resultado es par o impar." << endl
	     << "\t\t\t\t      - La cantidad de veces que tendras que adivinar el resultado del dado es igual al numero de pruebas." << endl
	     << "\t\t\t\t      - Completaras las pruebas si logras adivinar correctamente el resultado del dado, de lo contrario las fallaras." << endl
	     << "\t\t\t\t      - Un entrenamiento se considerara superado si el numero de pruebas completadas es mayor al numero de pruebas falladas." << endl
	     << "\t\t\t\t      - De lo contrario, se considerara como fallado." << endl << endl;
    	 
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
    
    cout << "\t\t\t\t    *Sistema de viajes*:" << endl << endl
	     << "\t\t\t\t      - Tu guardian comenzara en la aldea que elegiste al crearlo o en la aldea que asignaste por defecto." << endl
	     << "\t\t\t\t      - Tu guardian podra viajar entre las distintas aldeas solo si estan conectadas entre si." << endl
	     << "\t\t\t\t      - Tu guardian se considerara preparado si logra visitar todas las aldeas excepto Tesla." << endl
	     << "\t\t\t\t      - Para viajar a Tesla tu guardian debe considerarse preparado." << endl << endl;

	cout << "\t\t\t\t    ";
	
	system("pause");
	
	cout << endl;
	
	cout << "\t\t\t\t    *Sistema de alquimia*:" << endl << endl
	     << "\t\t\t\t      - Se te permitira utilizar el sistema de alquimia para crear caminos entre las aldeas." << endl
	     << "\t\t\t\t      - Cada vez que utilices el sistema de alquimia, se reduciran entre 2 y 4 niveles de tu guardian." << endl << endl;
	
	cout << "\t\t\t\t    Recuerda tener en cuenta los sistemas anteriores y seguir las instrucciones que se te indiquen" << endl
	     << "\t\t\t\t    para asegurar el correcto funcionamiento del juego. Vamos a jugar!" << endl << endl;
    	 
	cout << "\t\t\t\t    ";

    system("pause");
    
    cout << endl;
    
    // Menu de inicio
	cout << "************************************************************************** Menu de inicio ******************************************************************" << endl << endl;
	
	cout << "\t\t\t\t    |Menu de inicio|" << endl << endl;
	
	// Pregunta al jugador si desea crear o elegir un guardián
	cout << "\t\t\t\t    Desea crear o elegir un guardian? (crear/elegir): ";
	string opcion;
	cin >> opcion;
	
	cout << endl;
	
	// Valida la opción ingresada por el jugador
	while (opcion != "crear" && opcion != "elegir") {
	    cout << "\t\t\t\t    Opcion invalida. Por favor, ingrese 'crear' o 'elegir': ";
	    cin >> opcion;
	    
	    cout << endl;
	}
	
	if (opcion == "crear") {
    // Solicita el nombre del guardián al jugador
	    cout << "\t\t\t\t    Ingrese el nombre del guardian: ";	    
	    cin >> guardianName;
	    cout << endl;
	
	    // Muestra las aldeas disponibles al jugador
	    cout << "\t\t\t\t    Aldeas disponibles:" << endl;
	    guardians.printVillagesWithoutMaxLevelGuardian();
	    cout << endl;
	
	    // Solicita la aldea del guardián al jugador
	    string village = getValidVillage(guardians);
	
	    // Crea el guardián con los datos ingresados por el jugador y lo agrega a la lista de guardianes
	    guardians.addGuardianPlayer(village, guardianName, maxLevel / 2, "", 1);
	    
	    //guardians.printGuardiansByVillage();
	}
	
	if (opcion == "elegir") {
	    cout << "\t\t\t\t    Guardianes Aprendices por Aldea:" << endl;
	    cout << endl;
	    guardians.printApprenticeGuardiansByVillage();
	    cout << endl;
	    guardians.chooseApprenticeGuardian(guardians);
	    
	    //guardians.printGuardiansByVillage();
	    
	}
	
	// Comienzo del juego
	cout << "********************************************************************** Comienzo del juego ******************************************************************" << endl << endl;
	
    return 0;

}
